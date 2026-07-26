using SlimDX;
using SlimDX.Direct3D9;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Windows.Forms;

// Helper to enable 3D preview for MobEditor forms by using reflection
// This avoids modifying the large MobEditor source file.
public static class MobEditor3DManager
{
    private static Timer _timer;
    private static Dictionary<Form, string> _lastSmc = new Dictionary<Form, string>();

    // Per-form cache of the last raw smcPath input we processed (textbox value).
    // Used to short-circuit Timer_Tick when nothing has changed and avoid
    // re-running the recursive Directory.EnumerateFiles scans every 30ms.
    private static readonly Dictionary<Form, string> _lastInputSmc = new Dictionary<Form, string>();

    // Tracks (form, fullSmcPath) pairs that have already been handed to
    // MakeLCModelsOnForm so the timer never re-enters that expensive method
    // on every tick when the previous attempt produced no models.
    private static readonly HashSet<string> _attempted =
        new HashSet<string>(StringComparer.OrdinalIgnoreCase);

    // One-time index of every file under each clientRoot\Data directory,
    // keyed by lowercase filename. Built lazily on first use and reused for
    // the rest of the process, eliminating the repeated full-tree scans
    // (Directory.EnumerateFiles ... SearchOption.AllDirectories) that were
    // dominating CPU in MakeLCModelsOnForm.
    private static readonly Dictionary<string, Dictionary<string, List<string>>> _dataRootIndex =
        new Dictionary<string, Dictionary<string, List<string>>>(StringComparer.OrdinalIgnoreCase);

    private static Dictionary<string, List<string>> GetDataRootIndex(string dataRoot)
    {
        if (string.IsNullOrEmpty(dataRoot)) return null;
        Dictionary<string, List<string>> idx;
        if (_dataRootIndex.TryGetValue(dataRoot, out idx)) return idx;
        idx = new Dictionary<string, List<string>>(StringComparer.OrdinalIgnoreCase);
        try
        {
            if (Directory.Exists(dataRoot))
            {
                foreach (var file in Directory.EnumerateFiles(dataRoot, "*", SearchOption.AllDirectories))
                {
                    string fn = Path.GetFileName(file);
                    if (string.IsNullOrEmpty(fn)) continue;
                    List<string> bucket;
                    if (!idx.TryGetValue(fn, out bucket))
                    {
                        bucket = new List<string>(1);
                        idx[fn] = bucket;
                    }
                    bucket.Add(file);
                }
            }
        }
        catch (Exception ex) { Log("GetDataRootIndex failed for " + dataRoot + ": " + ex.Message); }
        _dataRootIndex[dataRoot] = idx;
        Log($"Indexed {idx.Count} unique filenames under {dataRoot}");
        return idx;
    }

    // Resolve an SMC token by looking inside the file index for either
    // <root> or <root>\Data. Used to replace the per-tick recursive
    // Directory.EnumerateFiles scans that were dominating Timer_Tick CPU.
    private static string ResolveSmcFromIndex(string root, string smcPath, string fallback)
    {
        if (string.IsNullOrEmpty(root) || string.IsNullOrEmpty(smcPath)) return fallback;
        try
        {
            string token = NormalizeName(smcPath);
            string smcWithExt = smcPath.EndsWith(".smc", StringComparison.OrdinalIgnoreCase) ? smcPath : smcPath + ".smc";
            string fileOnly = Path.GetFileName(smcWithExt);

            string[] roots = new[] { root, Path.Combine(root, "Data") };
            foreach (var r in roots)
            {
                var index = GetDataRootIndex(r);
                if (index == null || index.Count == 0) continue;

                // exact filename match (O(1))
                List<string> matches;
                if (!string.IsNullOrEmpty(fileOnly) && index.TryGetValue(fileOnly, out matches) && matches.Count > 0)
                {
                    Log("Found SMC by filename index: " + matches[0]);
                    return matches[0];
                }

                // fuzzy match limited to .smc keys
                foreach (var kv in index)
                {
                    if (!string.Equals(Path.GetExtension(kv.Key), ".smc", StringComparison.OrdinalIgnoreCase)) continue;
                    var name = Path.GetFileNameWithoutExtension(kv.Key);
                    if (string.IsNullOrEmpty(name)) continue;
                    var n = NormalizeName(name);
                    if (n.Contains(token) || token.Contains(n))
                    {
                        Log("Found SMC by fuzzy index: " + kv.Value[0]);
                        return kv.Value[0];
                    }
                }
            }
        }
        catch (Exception ex) { Log("ResolveSmcFromIndex failed: " + ex.Message); }
        return fallback;
    }

    // Global cache mapping a raw smcPath input -> resolved full path (or null
    // when it could not be resolved). This guarantees the expensive recursive
    // file system enumeration runs at most once per unique input string.
    private static readonly Dictionary<string, string> _resolveCache =
        new Dictionary<string, string>(StringComparer.OrdinalIgnoreCase);

    // simple file logger to help diagnose why 3D preview is empty
    private static readonly object _logLock = new object();
    private static void Log(string msg)
    {
        try
        {
            string path = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "MobEditor3DManager.log");
            lock (_logLock)
            {
                File.AppendAllText(path, DateTime.Now.ToString("o") + " - " + msg + Environment.NewLine);
            }
        }
        catch { }
    }

    // Log a message only once per key to avoid spamming repeated diagnostics
    private static readonly HashSet<string> _onceLogged = new HashSet<string>(StringComparer.OrdinalIgnoreCase);
    private static void LogOnce(string key, string msg)
    {
        try
        {
            lock (_logLock)
            {
                if (_onceLogged.Contains(key)) return;
                _onceLogged.Add(key);
                string path = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "MobEditor3DManager.log");
                File.AppendAllText(path, DateTime.Now.ToString("o") + " - " + msg + Environment.NewLine);
            }
        }
        catch { }
    }

    static MobEditor3DManager()
    {
        _timer = new Timer();
        _timer.Interval = 30; // ~33 FPS
        _timer.Tick += Timer_Tick;
        _timer.Start();
        Log("MobEditor3DManager started");
    }

    private static void Timer_Tick(object sender, EventArgs e)
    {
        try
        {
            foreach (Form f in Application.OpenForms)
            {
                if (f == null) continue;
                Type t = f.GetType();
                if (t.Name != "MobEditor")
                    continue;

                Panel panel = (Panel)GetFieldOrProp(f, "panel3DView") as Panel;
                if (panel == null) continue;

                CheckBox chk3D = (CheckBox)GetFieldOrProp(f, "chk3D");
                if (chk3D != null && !chk3D.Checked)
                    continue;

                Device device = (Device)GetFieldOrProp(f, "_Device");
                if (device == null)
                {
                    Log("Initializing device for form " + f.Name);
                    InitializeDeviceOnForm(f, panel);
                    device = (Device)GetFieldOrProp(f, "_Device");
                    if (device == null)
                        Log("Device still null after InitializeDeviceOnForm");
                    else
                        Log("Device initialized");
                }

                // detect SMC path change
                string smcPath = null;
                var tb = GetFieldOrProp(f, "textBox3") as TextBox;
                if (tb != null) smcPath = tb.Text;
                if (string.IsNullOrEmpty(smcPath))
                {
                    var smcField = GetFieldOrProp(f, "_smcPath") as string;
                    if (smcField != null) smcPath = smcField;
                }

                if (!string.IsNullOrEmpty(smcPath))
                {
                    string full = smcPath;
                    string clientPath = null;

                    // Fast path: if we've already resolved this exact input string before,
                    // reuse the result instead of re-running the recursive Directory scans.
                    // Cached value of null means "tried and failed" — still skip rescanning.
                    string cachedFull;
                    bool hasCached = _resolveCache.TryGetValue(smcPath, out cachedFull);
                    if (hasCached)
                    {
                        if (cachedFull != null) full = cachedFull;
                    }
                    else if (!Path.IsPathRooted(full))
                    {
                        clientPath = GetFieldOrProp(f, "_ClientPath") as string;
                        // try common combinations
                        if (!string.IsNullOrEmpty(clientPath))
                        {
                            string cand = Path.Combine(clientPath, smcPath);
                            if (File.Exists(cand)) full = cand;
                            else
                            {
                                cand = Path.Combine(clientPath, "Data", smcPath);
                                if (File.Exists(cand)) full = cand;
                                else
                                {
                                    cand = Path.Combine(clientPath, smcPath + ".smc");
                                    if (File.Exists(cand)) full = cand;
                                }
                            }

                            // if not found directly, search the cached file index
                            if (full == smcPath)
                            {
                                full = ResolveSmcFromIndex(clientPath, smcPath, full);
                            }
                        }
                        else
                        {
                            // try reading ClientPath from config file if form doesn't have it
                            var cfgClient = ReadClientPathFromConfig();
                            if (!string.IsNullOrEmpty(cfgClient))
                            {
                                clientPath = cfgClient;
                                try { Log("Using ClientPath from config: " + clientPath); } catch { }
                                string cand = Path.Combine(clientPath, smcPath);
                                if (File.Exists(cand)) full = cand;
                                else
                                {
                                    cand = Path.Combine(clientPath, "Data", smcPath);
                                    if (File.Exists(cand)) full = cand;
                                    else
                                    {
                                        cand = Path.Combine(clientPath, smcPath + ".smc");
                                        if (File.Exists(cand)) full = cand;
                                    }
                                }

                                if (full == smcPath)
                                {
                                    full = ResolveSmcFromIndex(clientPath, smcPath, full);
                                }
                            }
                        }

                        // if still not resolved, try application base and common data folders
                        if (full == smcPath)
                        {
                            string baseDir = AppDomain.CurrentDomain.BaseDirectory;
                            string[] tryRoots = new string[] { baseDir, Path.Combine(baseDir, "Data"), Path.Combine(baseDir, "Data", "monster") };
                            foreach (var root in tryRoots)
                            {
                                try
                                {
                                    if (string.IsNullOrEmpty(root) || !Directory.Exists(root)) continue;
                                    // direct combinations
                                    string cand2 = Path.Combine(root, smcPath);
                                    if (File.Exists(cand2)) { full = cand2; break; }
                                    cand2 = Path.Combine(root, smcPath + ".smc");
                                    if (File.Exists(cand2)) { full = cand2; break; }
                                }
                                catch { }
                            }
                            if (full == smcPath)
                            {
                                full = ResolveSmcFromIndex(baseDir, smcPath, full);
                            }
                        }
                    }

                    // Persist the resolution result (success or failure) so the
                    // expensive Directory.EnumerateFiles scans never re-run for
                    // this input string on subsequent timer ticks.
                    if (!hasCached)
                    {
                        _resolveCache[smcPath] = (full != smcPath && File.Exists(full)) ? full : null;
                    }

                    string prev = null;
                    _lastSmc.TryGetValue(f, out prev);
                    string attemptKey = f.GetHashCode().ToString() + "|" + (full ?? "");
                    if (prev != full && File.Exists(full))
                    {
                        _lastSmc[f] = full;
                        _attempted.Add(attemptKey);
                        Log("New SMC detected for form " + f.Name + ": " + full);
                        MakeLCModelsOnForm(f, full);
                    }
                    else
                    {
                        // Log helpful diagnostics when smc path is present but file not handled
                        if (!File.Exists(full))
                        {
                            Log($"SMC file not found: '{full}' (smcPath='{smcPath}', clientPath='{clientPath}')");
                        }
                        else if (prev == full)
                        {
                            // already processed same path
                            // but if the form has no models (previous attempt failed), try again once
                            var models = GetFieldOrProp(f, "_Models") as System.Collections.IEnumerable;
                            bool hasModels = false;
                            if (models != null)
                            {
                                foreach (var _ in models) { hasModels = true; break; }
                            }
                            if (!hasModels && !_attempted.Contains(attemptKey))
                            {
                                _attempted.Add(attemptKey);
                                Log($"SMC previously loaded but _Models empty for form {f.Name}, retrying MakeLCModelsOnForm for: {full}");
                                MakeLCModelsOnForm(f, full);
                            }
                            else if (hasModels)
                            {
                                // do not spam log but record once
                                var seenKey = "__3d_logged_smc_seen_" + f.GetHashCode();
                                var seen = GetFieldOrProp(f, seenKey);
                                if (seen == null)
                                {
                                    Log($"SMC already loaded for form {f.Name}: {full}");
                                    SetField(f, seenKey, true);
                                }
                            }
                        }
                    }
                }

                // render
                RenderOnForm(f);
            }
        }
        catch (Exception ex)
        {
            Log("Timer_Tick exception: " + ex.Message);
            // swallow any errors to not break host app
        }
    }

    private static object GetFieldOrProp(object target, string name)
    {
        if (target == null) return null;
        Type t = target.GetType();
        FieldInfo fi = t.GetField(name, BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.Public);
        if (fi != null) return fi.GetValue(target);
        PropertyInfo pi = t.GetProperty(name, BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.Public);
        if (pi != null) return pi.GetValue(target);
        return null;
    }

    private static void SetField(object target, string name, object value)
    {
        Type t = target.GetType();
        FieldInfo fi = t.GetField(name, BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.Public);
        if (fi != null) fi.SetValue(target, value);
        else
        {
            PropertyInfo pi = t.GetProperty(name, BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.Public);
            if (pi != null && pi.CanWrite) pi.SetValue(target, value);
        }
    }

    private static void InitializeDeviceOnForm(Form f, Panel panel)
    {
        try
        {
            var direct3D = new Direct3D();
            PresentParameters pp = new PresentParameters();
            pp.SwapEffect = SwapEffect.Discard;
            pp.DeviceWindowHandle = panel.Handle;
            pp.Windowed = true;
            pp.BackBufferWidth = Math.Max(1, panel.Width);
            pp.BackBufferHeight = Math.Max(1, panel.Height);
            pp.BackBufferFormat = Format.A8R8G8B8;
            pp.EnableAutoDepthStencil = true;
            pp.AutoDepthStencilFormat = Format.D24X8;

            Device device = new Device(direct3D, 0, DeviceType.Hardware, panel.Handle,
                CreateFlags.HardwareVertexProcessing | CreateFlags.Multithreaded | CreateFlags.FpuPreserve,
                pp);

            device.SetRenderState(RenderState.CullMode, Cull.None);
            device.SetRenderState(RenderState.FillMode, FillMode.Solid);
            device.SetRenderState(RenderState.Lighting, false);

            SetField(f, "_Direct3D", direct3D);
            SetField(f, "_Device", device);

            MethodInfo cam = f.GetType().GetMethod("CameraPositioning", BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.Public);
            if (cam != null) cam.Invoke(f, null);
        }
        catch (Exception ex)
        {
            Log("InitializeDeviceOnForm exception: " + ex.Message);
        }
    }

    private static Type GetTypeByName(string name)
    {
        foreach (var asm in AppDomain.CurrentDomain.GetAssemblies())
        {
            try
            {
                var t = asm.GetType(name, false, true);
                if (t != null) return t;
            }
            catch { }
        }
        return null;
    }

    private static void MakeLCModelsOnForm(Form f, string smcFile)
    {
        try
        {
            Log("MakeLCModelsOnForm starting for file: " + smcFile);
            Type smcReaderType = GetTypeByName("SMCEditor3.SMCReader") ?? GetTypeByName("SMCEditor4.SMCReader") ?? GetTypeByName("SMCEditor3.SMCReader");
            if (smcReaderType == null)
            {
                Log("SMCReader type not found");
                return;
            }
            MethodInfo readMethod = smcReaderType.GetMethod("ReadFile", BindingFlags.Static | BindingFlags.Public);
            if (readMethod == null)
            {
                Log("SMCReader.ReadFile method not found");
                return;
            }

            var smcListObj = readMethod.Invoke(null, new object[] { smcFile });
            if (!(smcListObj is System.Collections.IEnumerable smcList))
            {
                Log("SMCReader.ReadFile returned null or non-enumerable");
                return;
            }

            var device = (Device)GetFieldOrProp(f, "_Device");
            if (device == null)
            {
                Log("Device is null in MakeLCModelsOnForm");
                return;
            }

            // determine client root once
            string clientRootGlobal = GetFieldOrProp(f, "_ClientPath") as string ?? ReadClientPathFromConfig() ?? GetClientPathFromConnection();
            if (string.IsNullOrEmpty(clientRootGlobal))
            {
                try
                {
                    // try to infer client root from the smc file path by finding the 'Data' path segment
                    var dir = Path.GetDirectoryName(smcFile);
                    while (!string.IsNullOrEmpty(dir))
                    {
                        var name = Path.GetFileName(dir);
                        if (string.Equals(name, "Data", StringComparison.OrdinalIgnoreCase))
                        {
                            var parent = Directory.GetParent(dir);
                            if (parent != null)
                            {
                                clientRootGlobal = parent.FullName;
                                Log("Inferred client root from smc file: " + clientRootGlobal);
                            }
                            break;
                        }
                        try { dir = Directory.GetParent(dir)?.FullName; } catch { dir = null; }
                    }
                }
                catch { }
            }
            if (!string.IsNullOrEmpty(clientRootGlobal)) Log("Client root for mesh resolution: " + clientRootGlobal);

            var modelsList = new List<object>();

            Type lcmType = GetTypeByName("LcDevPack_TeamDamonA.LCMeshReader") ?? GetTypeByName("LCMeshReader");
            MethodInfo lcmRead = lcmType?.GetMethod("ReadFile", BindingFlags.Static | BindingFlags.Public);
            FieldInfo pMeshField = lcmType?.GetField("pMesh", BindingFlags.Static | BindingFlags.Public);
            if (lcmRead == null) Log("LCMeshReader.ReadFile not found");
            if (pMeshField == null) Log("LCMeshReader.pMesh field not found");

            // prepare typed list for tMesh if possible
            Type tMeshType = GetTypeByName("LcDevPack_TeamDamonA.tMesh") ?? GetTypeByName("tMesh");
            object typedModelsList = null;
            MethodInfo typedModelsAdd = null;
            PropertyInfo typedModelsCountProp = null;
            if (tMeshType != null)
            {
                var listType = typeof(System.Collections.Generic.List<>).MakeGenericType(tMeshType);
                typedModelsList = Activator.CreateInstance(listType);
                typedModelsAdd = listType.GetMethod("Add");
                typedModelsCountProp = listType.GetProperty("Count");
            }
            else
            {
                typedModelsList = modelsList; // fallback
            }

            int smcCount = 0;
            foreach (var smcObj in smcList)
            {
                smcCount++;
                var fileNameObj = GetValue(smcObj, "FileName") ?? GetValue(smcObj, "fileName");
                string meshFile = fileNameObj as string;
                if (string.IsNullOrEmpty(meshFile))
                {
                    Log($"smc entry #{smcCount} has empty FileName");
                    continue;
                }

                bool ok = false;
                string meshFull = meshFile;
                if (lcmRead != null)
                {
                    try
                     {
                         // If meshFile looks client-root-relative (starts with Data\), try client root first and skip smcDir
                         bool looksClientRelative = meshFile.StartsWith("Data\\", StringComparison.OrdinalIgnoreCase) || meshFile.IndexOf("\\Data\\", StringComparison.OrdinalIgnoreCase) >= 0;
                         if (looksClientRelative && !string.IsNullOrEmpty(clientRootGlobal))
                         {
                            var candClient = Path.Combine(clientRootGlobal, meshFile);
                            Log("Trying candidate (clientRoot + meshFile): " + candClient);
                            if (File.Exists(candClient)) meshFull = candClient;
                            else
                            {
                                var alt = Path.Combine(clientRootGlobal, meshFile.TrimStart(Path.DirectorySeparatorChar, Path.AltDirectorySeparatorChar));
                                Log("Trying candidate (clientRoot + trimmed meshFile): " + alt);
                                if (File.Exists(alt)) meshFull = alt;
                                else
                                {
                                    var candClientData = Path.Combine(clientRootGlobal, "Data", meshFile);
                                    Log("Trying candidate (clientRoot/Data + meshFile): " + candClientData);
                                    if (File.Exists(candClientData)) meshFull = candClientData;
                                }
                            }
                         }

                        // if still unresolved and meshFile is not client-relative, try smc directory
                        if (meshFull == meshFile)
                        {
                            if (!looksClientRelative)
                            {
                                var smcDir = Path.GetDirectoryName(smcFile);
                                if (!string.IsNullOrEmpty(smcDir))
                                {
                                    var cand = Path.Combine(smcDir, meshFile);
                                    Log("Trying candidate (smcDir): " + cand);
                                    if (File.Exists(cand)) meshFull = cand;
                                }
                            }
                        }

                        // next try client root general combinations (if not already tried)
                        if (meshFull == meshFile && !string.IsNullOrEmpty(clientRootGlobal))
                        {
                            var cand = Path.Combine(clientRootGlobal, meshFile);
                            Log("Trying candidate (clientRoot general): " + cand);
                            if (File.Exists(cand)) meshFull = cand;
                            else
                            {
                                cand = Path.Combine(clientRootGlobal, "Data", meshFile);
                                Log("Trying candidate (clientRoot/Data general): " + cand);
                                if (File.Exists(cand)) meshFull = cand;
                            }
                        }

                        // finally, try a recursive search under clientRoot only (avoid using app base)
                        if ((meshFull == meshFile || !File.Exists(meshFull)) && !string.IsNullOrEmpty(clientRootGlobal))
                        {
                            try
                            {
                                string filenameOnly = Path.GetFileName(meshFile);
                                string token = NormalizeName(Path.GetFileNameWithoutExtension(meshFile));
                                var dataRoot = Path.Combine(clientRootGlobal, "Data");
                                Log("Searching client dataRoot: " + dataRoot);
                                var index = GetDataRootIndex(dataRoot);
                                if (index != null && index.Count > 0)
                                {
                                    // exact / case-insensitive filename match (one O(1) lookup)
                                    List<string> matches;
                                    if (index.TryGetValue(filenameOnly, out matches) && matches.Count > 0)
                                    {
                                        Log("Found by filename index: " + matches[0]);
                                        meshFull = matches[0];
                                    }

                                    // fuzzy fallback: scan the index keys (in-memory) instead of the file system
                                    if (meshFull == meshFile)
                                    {
                                        string[] fuzzyExts = new[] { ".bm", ".bs", ".tex" };
                                        foreach (var ext in fuzzyExts)
                                        {
                                            foreach (var kv in index)
                                            {
                                                var name = Path.GetFileNameWithoutExtension(kv.Key);
                                                if (string.IsNullOrEmpty(name)) continue;
                                                if (!string.Equals(Path.GetExtension(kv.Key), ext, StringComparison.OrdinalIgnoreCase)) continue;
                                                var n = NormalizeName(name);
                                                if (n.Contains(token) || token.Contains(n))
                                                {
                                                    Log("Found by fuzzy " + ext + ": " + kv.Value[0]);
                                                    meshFull = kv.Value[0];
                                                    break;
                                                }
                                            }
                                            if (meshFull != meshFile) break;
                                        }
                                    }
                                }
                            }
                            catch (Exception ex) { Log("mesh recursive search failed: " + ex.Message); }
                        }

                        if (!Path.IsPathRooted(meshFull) || !File.Exists(meshFull))
                        {
                            Log("Could not resolve meshFile to existing path, skipping LCMeshReader for: " + meshFile + " (resolved candidate: " + meshFull + ")");
                            ok = false;
                        }
                        else
                        {
                            Log("Resolved meshFile to: " + meshFull);
                            ok = (bool)lcmRead.Invoke(null, new object[] { meshFull });
                        }
                    }
                    catch (Exception ex)
                    {
                        Log("LCMeshReader.ReadFile threw: " + ex.Message + " for " + meshFile + " (resolved candidate: " + meshFull + ")");
                        ok = false;
                    }
                }
                 if (!ok)
                 {
                     Log("LCMeshReader.ReadFile returned false for " + meshFile);
                     continue;
                 }

                var pMesh = pMeshField?.GetValue(null);
                if (pMesh == null)
                {
                    Log("pMesh is null after reading " + meshFile);
                    continue;
                }

                var verts = (Array)GetValue(pMesh, "Vertices");
                var normals = (Array)GetValue(pMesh, "Normals");
                var uvMaps = GetValue(pMesh, "UVMaps") as Array;
                var objects = (Array)GetValue(pMesh, "Objects");

                if (verts == null || normals == null || objects == null)
                {
                    Log("pMesh data incomplete for " + meshFile);
                    continue;
                }

                int objIndex = 0;
                for (int oi = 0; oi < objects.Length; ++oi)
                {
                    var obj = objects.GetValue(oi);
                    int toVert = Convert.ToInt32(GetValue(obj, "ToVert"));
                    int fromVert = Convert.ToInt32(GetValue(obj, "FromVert"));

                    MethodInfo getFaces = obj.GetType().GetMethod("GetFaces", BindingFlags.Instance | BindingFlags.Public);
                    short[] faces = getFaces?.Invoke(obj, null) as short[];
                    if (faces == null || faces.Length == 0) continue;

                    int vertexCount = toVert;
                    Mesh mesh = new Mesh(device, faces.Length / 3, vertexCount, MeshFlags.Managed, VertexFormat.PositionNormal | VertexFormat.Texture1);

                    // build raw vertex bytes (float32 x 8 per vertex => 32 bytes)
                    int vsize = 32;
                    byte[] vbytes = new byte[vertexCount * vsize];
                    for (int vi = 0; vi < vertexCount; ++vi)
                    {
                        int vertIndex = fromVert + vi;
                        var v = verts.GetValue(vertIndex);
                        var n = normals.GetValue(vertIndex);
                        float px = Convert.ToSingle(GetValue(v, "X"));
                        float py = Convert.ToSingle(GetValue(v, "Y"));
                        float pz = Convert.ToSingle(GetValue(v, "Z"));
                        float nx = Convert.ToSingle(GetValue(n, "X"));
                        float ny = Convert.ToSingle(GetValue(n, "Y"));
                        float nz = Convert.ToSingle(GetValue(n, "Z"));
                        float tu = 0f, tv = 0f;
                        try
                        {
                            if (uvMaps != null && uvMaps.Length > 0)
                            {
                                var uv0 = uvMaps.GetValue(0);
                                var coords = (Array)GetValue(uv0, "Coords");
                                var uv = coords.GetValue(vertIndex);
                                tu = Convert.ToSingle(GetValue(uv, "U"));
                                tv = Convert.ToSingle(GetValue(uv, "V"));
                            }
                        }
                        catch { }

                        int baseIndex = vi * vsize;
                        Buffer.BlockCopy(BitConverter.GetBytes(px), 0, vbytes, baseIndex + 0, 4);
                        Buffer.BlockCopy(BitConverter.GetBytes(py), 0, vbytes, baseIndex + 4, 4);
                        Buffer.BlockCopy(BitConverter.GetBytes(pz), 0, vbytes, baseIndex + 8, 4);
                        Buffer.BlockCopy(BitConverter.GetBytes(nx), 0, vbytes, baseIndex + 12, 4);
                        Buffer.BlockCopy(BitConverter.GetBytes(ny), 0, vbytes, baseIndex + 16, 4);
                        Buffer.BlockCopy(BitConverter.GetBytes(nz), 0, vbytes, baseIndex + 20, 4);
                        Buffer.BlockCopy(BitConverter.GetBytes(tu), 0, vbytes, baseIndex + 24, 4);
                        Buffer.BlockCopy(BitConverter.GetBytes(tv), 0, vbytes, baseIndex + 28, 4);
                    }

                    using (var ds = mesh.VertexBuffer.Lock(0, vbytes.Length, LockFlags.None))
                    {
                        ds.Write(vbytes, 0, vbytes.Length);
                        mesh.VertexBuffer.Unlock();
                    }

                    byte[] ib = new byte[faces.Length * 2];
                    for (int fi = 0; fi < faces.Length; ++fi)
                    {
                        short s = faces[fi];
                        Buffer.BlockCopy(BitConverter.GetBytes(s), 0, ib, fi * 2, 2);
                    }
                    using (var ds = mesh.IndexBuffer.Lock(0, ib.Length, LockFlags.None))
                    {
                        ds.Write(ib, 0, ib.Length);
                        mesh.IndexBuffer.Unlock();
                    }

                    mesh.GenerateAdjacency(0.5f);
                    mesh.ComputeNormals();

                    // texture retrieval (best-effort)
                    Texture tex = null;
                    try
                    {
                        // 1) try to get texture info from the original smc entry (smcObj)
                        try
                        {
                            var smcObjectsList = GetValue(smcObj, "Object") as System.Collections.IEnumerable ?? GetValue(smcObj, "Objects") as System.Collections.IEnumerable;
                            if (smcObjectsList != null)
                            {
                                int idx = 0;
                                foreach (var so in smcObjectsList)
                                {
                                    if (idx == oi)
                                    {
                                        // try common name/file fields
                                        string texPathCandidate = GetValue(so, "FileName") as string ?? GetValue(so, "fileName") as string
                                            ?? GetValue(so, "File") as string ?? GetValue(so, "file") as string
                                            ?? GetValue(so, "Path") as string ?? GetValue(so, "path") as string
                                            ?? GetValue(so, "TextureFile") as string ?? GetValue(so, "textureFile") as string
                                            ?? GetValue(so, "TextureName") as string ?? GetValue(so, "textureName") as string
                                            ?? GetValue(so, "InternalName") as string ?? GetValue(so, "internalName") as string
                                            ?? GetValue(so, "Name") as string ?? GetValue(so, "name") as string;
                                        if (!string.IsNullOrEmpty(texPathCandidate))
                                        {
                                            // Resolve relative paths
                                            string resolved = texPathCandidate;
                                            // log candidate before resolution
                                            try { Log($"texPathCandidate: '{texPathCandidate}' (smcEntry #{smcCount} objIndex {oi})"); } catch { }
                                            if (!Path.IsPathRooted(resolved))
                                            {
                                                // prefer client root
                                                if (!string.IsNullOrEmpty(clientRootGlobal))
                                                {
                                                    var cand = Path.Combine(clientRootGlobal, resolved);
                                                    if (File.Exists(cand)) resolved = cand;
                                                    else
                                                    {
                                                        cand = Path.Combine(clientRootGlobal, "Data", resolved);
                                                        if (File.Exists(cand)) resolved = cand;
                                                    }
                                                }

                                                // try relative to mesh folder
                                                if (resolved == texPathCandidate)
                                                {
                                                    try
                                                    {
                                                        var meshDir = Path.GetDirectoryName(meshFull) ?? Path.GetDirectoryName(smcFile);
                                                        if (!string.IsNullOrEmpty(meshDir))
                                                        {
                                                            var cand2 = Path.Combine(meshDir, resolved);
                                                            if (File.Exists(cand2)) resolved = cand2;
                                                        }
                                                    }
                                                    catch { }
                                                }

                                                // if still not absolute, try searching client Data for matching filename
                                                if (!Path.IsPathRooted(resolved) || !File.Exists(resolved))
                                                {
                                                    try
                                                    {
                                                        var fileOnly = Path.GetFileName(resolved);
                                                        if (!string.IsNullOrEmpty(fileOnly) && !string.IsNullOrEmpty(clientRootGlobal))
                                                        {
                                                            var dataRoot = Path.Combine(clientRootGlobal, "Data");
                                                            var index = GetDataRootIndex(dataRoot);
                                                            List<string> matches;
                                                            if (index != null && index.TryGetValue(fileOnly, out matches) && matches.Count > 0)
                                                            {
                                                                resolved = matches[0];
                                                            }
                                                        }
                                                    }
                                                    catch { }
                                                }

                                            }

                                            // diagnostic: log resolved candidate and existence
                                            try { Log($"Resolved texture: '{resolved}' exists:{(Path.IsPathRooted(resolved) && File.Exists(resolved))} ext:{Path.GetExtension(resolved)} (smcEntry #{smcCount} objIndex {oi})"); } catch { }

                                            if (Path.IsPathRooted(resolved) && File.Exists(resolved))
                                            {
                                                try
                                                {
                                                    Log("Attempting texture load: " + resolved);
                                                    // if file is .tex (game format) try alternate common image extensions in same folder
                                                    var ext = Path.GetExtension(resolved)?.ToLowerInvariant();
                                                    if (ext == ".tex")
                                                    {
                                                        string dir = Path.GetDirectoryName(resolved);
                                                        string nameNoExt = Path.GetFileNameWithoutExtension(resolved);
                                                        string[] altExts = new[] { ".dds", ".png", ".jpg", ".bmp" };
                                                        foreach (var ae in altExts)
                                                        {
                                                            try
                                                            {
                                                                var candAlt = Path.Combine(dir, nameNoExt + ae);
                                                                Log("Trying alternate texture: " + candAlt);
                                                                if (File.Exists(candAlt))
                                                                {
                                                                    try
                                                                    {
                                                                        tex = Texture.FromFile(device, candAlt);
                                                                        Log("Loaded alternate texture: " + candAlt);
                                                                        break;
                                                                    }
                                                                    catch (Exception e) { Log("Alternate texture load failed: " + e.Message); }
                                                                }
                                                            }
                                                            catch (Exception e) { Log("Alternate candidate check failed: " + e.Message); }
                                                        }
                                                    }

                                                    if (tex == null)
                                                    {
                                                        tex = Texture.FromFile(device, resolved);
                                                        Log("Loaded texture from smcObject: " + resolved);
                                                    }
                                                }
                                                catch (Exception texEx)
                                                {
                                                    Log("Failed to create texture from file " + resolved + ": " + texEx.Message);
                                                    // if original was .tex, try alternates in parent dir
                                                    try
                                                    {
                                                        var ext = Path.GetExtension(resolved)?.ToLowerInvariant();
                                                        var dir = Path.GetDirectoryName(resolved);
                                                        var nameNoExt = Path.GetFileNameWithoutExtension(resolved);
                                                        string[] altExts = new[] { ".dds", ".png", ".jpg", ".bmp" };
                                                        foreach (var ae in altExts)
                                                        {
                                                            var candAlt = Path.Combine(dir ?? clientRootGlobal, nameNoExt + ae);
                                                            Log("Trying fallback alternate texture: " + candAlt);
                                                            if (File.Exists(candAlt))
                                                            {
                                                                try { tex = Texture.FromFile(device, candAlt); Log("Loaded fallback alternate texture: " + candAlt); break; } catch (Exception e) { Log("Fallback alt load failed: " + e.Message); }
                                                            }
                                                        }
                                                    }
                                                    catch { }
                                                }
                                            }
                                            else
                                            {
                                                Log("Resolved texture path is not rooted or does not exist: " + resolved);
                                            }
                                        }
                                        break;
                                    }
                                    idx++;
                                }
                            }
                        }
                        catch (Exception) { }

                        // 2) fallback: try to use texture info embedded in mesh object's Textures entries
                        if (tex == null)
                        {
                            var textures = GetValue(obj, "Textures") as Array;
                            if (textures != null && textures.Length > 0)
                            {
                                var texObj = textures.GetValue(0);
                                var internalNameBytes = (byte[])GetValue(texObj, "InternalName") ?? (byte[])GetValue(texObj, "internalName");
                                string token = null;
                                try
                                {
                                    if (internalNameBytes != null)
                                    {
                                        token = System.Text.Encoding.ASCII.GetString(internalNameBytes).Trim('\0', ' ');
                                        if (string.IsNullOrEmpty(token)) token = System.Text.Encoding.Default.GetString(internalNameBytes).Trim('\0', ' ');
                                    }
                                }
                                catch { }

                                if (!string.IsNullOrEmpty(token) && !string.IsNullOrEmpty(clientRootGlobal))
                                {
                                    var dataRoot = Path.Combine(clientRootGlobal, "Data");
                                    var index = GetDataRootIndex(dataRoot);
                                    if (index != null && index.Count > 0)
                                    {
                                        string normToken = NormalizeName(token);
                                        string[] exts = new[] { ".tex", ".dds", ".png", ".jpg", ".bmp" };
                                        foreach (var ext in exts)
                                        {
                                            foreach (var kv in index)
                                            {
                                                if (!string.Equals(Path.GetExtension(kv.Key), ext, StringComparison.OrdinalIgnoreCase)) continue;
                                                var name = Path.GetFileNameWithoutExtension(kv.Key);
                                                if (string.Equals(name, token, StringComparison.OrdinalIgnoreCase) || NormalizeName(name).Contains(normToken))
                                                {
                                                    try { tex = Texture.FromFile(device, kv.Value[0]); Log("Loaded texture by token: " + kv.Value[0]); break; }
                                                    catch { }
                                                }
                                            }
                                            if (tex != null) break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    catch (Exception ex)
                    {
                        Log("Texture retrieval failed: " + ex.Message);
                    }

                    // create tMesh instance and add to typed list
                    if (tMeshType != null)
                    {
                        object tmeshObj = Activator.CreateInstance(tMeshType, new object[] { mesh, tex });
                        try
                        {
                            if (typedModelsAdd != null)
                                typedModelsAdd.Invoke(typedModelsList, new object[] { tmeshObj });
                            else
                                modelsList.Add(tmeshObj);
                            objIndex++;
                        }
                        catch (Exception ex) { Log("Failed to add tMesh to typed list: " + ex.Message); }
                    }
                }
                Log($"Processed smc entry #{smcCount}, created {objIndex} meshes from it");
            }

            int totalCreated = 0;
            try
            {
                if (typedModelsCountProp != null)
                    totalCreated = (int)typedModelsCountProp.GetValue(typedModelsList);
                else if (modelsList != null)
                    totalCreated = modelsList.Count;
            }
            catch { }

            Log("Total meshes created: " + totalCreated);
            // set field _Models to the typed list when available
            SetField(f, "_Models", typedModelsList ?? (object)modelsList);
            SetField(f, "_Zoom", 10f);
        }
        catch (Exception ex)
        {
            Log("MakeLCModelsOnForm exception: " + ex.Message);
        }
    }

    private static void RenderOnForm(Form f)
    {
        try
        {
            Device device = (Device)GetFieldOrProp(f, "_Device");
            if (device == null)
            {
                // nothing to render
                return;
            }
            Panel panel = (Panel)GetFieldOrProp(f, "panel3DView");
            if (panel == null) return;
            var models = GetFieldOrProp(f, "_Models") as System.Collections.IEnumerable;
            float zoom = Convert.ToSingle(GetFieldOrProp(f, "_Zoom") ?? 10f);
            float leftRight = Convert.ToSingle(GetFieldOrProp(f, "_LeftRight") ?? 0f);
            float upDown = Convert.ToSingle(GetFieldOrProp(f, "_UpDown") ?? 0f);
            float rotation = Convert.ToSingle(GetFieldOrProp(f, "_Rotation") ?? 0f);

            device.Viewport = new Viewport(0, 0, Math.Max(1, panel.Width), Math.Max(1, panel.Height));
            device.Clear(ClearFlags.ZBuffer | ClearFlags.Target, new Color4(System.Drawing.Color.FromKnownColor(System.Drawing.KnownColor.Control)), 1f, 0);
            device.BeginScene();
            device.SetTransform(TransformState.View, Matrix.LookAtLH(new Vector3(0, 0, zoom), new Vector3(leftRight, upDown, 0), new Vector3(0, 1f, 0)));
            device.SetTransform(TransformState.World, Matrix.RotationYawPitchRoll(rotation, 0f, 0f));

            if (models == null)
            {
                // log once that there are no models
                var seen = GetFieldOrProp(f, "__3d_logged_no_models");
                if (seen == null)
                {
                    Log("RenderOnForm: _Models is null or empty for form " + f.Name);
                    SetField(f, "__3d_logged_no_models", true);
                }
            }
            else
            {
                int count = 0;
                foreach (var _ in models) count++;
                // log first time we actually have models
                var seenOk = GetFieldOrProp(f, "__3d_logged_models_count");
                if (count > 0 && seenOk == null)
                {
                    Log($"RenderOnForm: rendering {count} model(s) on form " + f.Name);
                    SetField(f, "__3d_logged_models_count", true);
                }

                foreach (var m in models)
                {
                    try
                    {
                        var mesh = m.GetType().GetField("MeshData", BindingFlags.Instance | BindingFlags.Public)?.GetValue(m);
                        var tex = m.GetType().GetField("TexData", BindingFlags.Instance | BindingFlags.Public)?.GetValue(m) as BaseTexture;
                        if (tex != null) device.SetTexture(0, tex);
                        if (mesh != null)
                        {
                            MethodInfo draw = mesh.GetType().GetMethod("DrawSubset");
                            for (int s = 0; s < 1000; ++s)
                            {
                                try { draw.Invoke(mesh, new object[] { s }); }
                                catch { break; }
                            }
                        }
                    }
                    catch (Exception ex)
                    {
                        Log("Render loop exception: " + ex.Message);
                    }
                }
            }

            device.EndScene();
            device.Present();

            float rot = rotation - 0.03f;
            SetField(f, "_Rotation", rot);
        }
        catch (Exception ex)
        {
            Log("RenderOnForm exception: " + ex.Message);
        }
    }

    private static object GetValue(object obj, string name)
    {
        if (obj == null) return null;
        var t = obj.GetType();
        var fi = t.GetField(name, BindingFlags.Instance | BindingFlags.Public | BindingFlags.NonPublic);
        if (fi != null) return fi.GetValue(obj);
        var pi = t.GetProperty(name, BindingFlags.Instance | BindingFlags.Public | BindingFlags.NonPublic);
        if (pi != null) return pi.GetValue(obj);
        return null;
    }

    // Public wrapper so other code (like MobEditor) can call into the manager easily
    public static void LoadSmcForForm(Form f, string smcFile)
    {
        try
        {
            MakeLCModelsOnForm(f, smcFile);
        }
        catch (Exception ex)
        {
            Log("LoadSmcForForm exception: " + ex.Message);
        }
    }

    private static string ReadClientPathFromConfig()
    {
        try
        {
            string baseDir = AppDomain.CurrentDomain.BaseDirectory;

            // check common Config folder first (the app uses Config\Settings.cfg)
            string cfgInConfig = Path.Combine(baseDir, "Config", "Settings.cfg");
            if (File.Exists(cfgInConfig))
            {
                try
                {
                    foreach (var line in File.ReadAllLines(cfgInConfig))
                    {
                        if (string.IsNullOrWhiteSpace(line)) continue;
                        var idx = line.IndexOf('=');
                        if (idx <= 0) continue;
                        string key = line.Substring(0, idx).Trim();
                        string val = line.Substring(idx + 1).Trim().Trim('"');
                        if (string.Equals(key, "ClientPath", StringComparison.OrdinalIgnoreCase) && !string.IsNullOrEmpty(val))
                        {
                            try { Log("Read ClientPath from config " + cfgInConfig + " => " + val); } catch { }
                            return val;
                        }
                    }
                }
                catch { }
            }

            string[] candidates = new[] { "settings.cfg", "Settings.cfg", "config.ini", "Settings.ini", "config.txt" };

            // walk up directories to find a config file (covers cases where exe is in bin/Debug and config is in project root)
            string dir = baseDir.TrimEnd(Path.DirectorySeparatorChar, Path.AltDirectorySeparatorChar);
            for (int depth = 0; depth < 6 && !string.IsNullOrEmpty(dir); depth++)
            {
                foreach (var name in candidates)
                {
                    string p = Path.Combine(dir, name);
                    if (!File.Exists(p)) continue;
                    foreach (var line in File.ReadAllLines(p))
                    {
                        if (string.IsNullOrWhiteSpace(line)) continue;
                        var idx = line.IndexOf('=');
                        if (idx <= 0) continue;
                        string key = line.Substring(0, idx).Trim();
                        string val = line.Substring(idx + 1).Trim().Trim('"');
                        if (string.Equals(key, "ClientPath", StringComparison.OrdinalIgnoreCase) && !string.IsNullOrEmpty(val))
                        {
                            try { Log("Read ClientPath from config " + p + " => " + val); } catch { }
                            return val;
                        }
                    }
                }

                // move to parent
                try { dir = Directory.GetParent(dir)?.FullName; } catch { dir = null; }
                if (string.IsNullOrEmpty(dir)) break;
            }
        }
        catch { }
        return null;
    }

    private static string GetClientPathFromConnection()
    {
        try
        {
            // try types by known names
            Type connType = GetTypeByName("LcDevPack_TeamDamonA.Connection") ?? GetTypeByName("Connection");
            if (connType == null) return null;
            // static field 'connection'
            var connField = connType.GetField("connection", BindingFlags.Static | BindingFlags.Public | BindingFlags.NonPublic);
            object connInstance = null;
            if (connField != null) connInstance = connField.GetValue(null);
            else
            {
                // try property
                var connProp = connType.GetProperty("connection", BindingFlags.Static | BindingFlags.Public | BindingFlags.NonPublic);
                if (connProp != null) connInstance = connProp.GetValue(null);
            }
            if (connInstance == null) return null;
            var settings = connInstance.GetType().GetProperty("Settings", BindingFlags.Instance | BindingFlags.Public | BindingFlags.NonPublic)?.GetValue(connInstance)
                ?? connInstance.GetType().GetField("Settings", BindingFlags.Instance | BindingFlags.Public | BindingFlags.NonPublic)?.GetValue(connInstance);
            if (settings == null) return null;
            var clientPath = settings.GetType().GetProperty("ClientPath", BindingFlags.Instance | BindingFlags.Public | BindingFlags.NonPublic)?.GetValue(settings)
                ?? settings.GetType().GetField("ClientPath", BindingFlags.Instance | BindingFlags.Public | BindingFlags.NonPublic)?.GetValue(settings);
            if (clientPath is string s && !string.IsNullOrEmpty(s))
            {
                try { Log("ClientPath read from Connection.settings: " + s); } catch { }
                return s;
            }
        }
        catch (Exception ex) { Log("GetClientPathFromConnection failed: " + ex.Message); }
        return null;
    }

    private static string NormalizeName(string s)
    {
        if (string.IsNullOrEmpty(s)) return string.Empty;
        var sb = new System.Text.StringBuilder();
        foreach (char c in s.ToLowerInvariant())
        {
            if (char.IsLetterOrDigit(c)) sb.Append(c);
        }
        return sb.ToString();
    }
}
