// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MobPicker
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using SlimDX;
using SlimDX.Direct3D9;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools
{
  public class MobPicker : Form
  {
    public List<string> MenuList = new List<string>();
    public List<string> MenuListSearch = new List<string>();
    public static Connection connection = new Connection();
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    private string Host = SkillEditor.connection.Settings.SqlHost;
    private string User = SkillEditor.connection.Settings.SqlUser;
    private string Password = SkillEditor.connection.Settings.SqlPassword;
    private string Database = SkillEditor.connection.Settings.SqlDatabase;
    public string _ClientPath = SkillEditor.connection.Settings.ClientPath;
    public string[] menuArray = new string[2]
    {
      "a_index",
      "a_name_usa"
    };
    public Direct3D _Direct3D;
    public Device _Device;
    public float _Zoom;
    public float _LeftRight;
    public float _Rotation;
    public float _UpDown = -1f;
    public List<tMesh> _Models;
    public int MobIndex = -1;
    private ASCIIEncoding _Enc = new ASCIIEncoding();
    private IContainer components = (IContainer) null;
    private ListBox listBox1;
    private GroupBox groupBox1;
    private TextBox textBox1;
    private GroupBox groupBox2;
    private Button button3;
    private Button button2;
    private Button button1;
    private GroupBox groupBox3;
    private TextBox textBox2;
    private Label label1;
    private GroupBox groupBox20;
    private CheckBox chk3D;
    private TrackBar slideLeftRight;
    private TrackBar slideUpDown;
    private TrackBar slideZoom;
    private Panel panel3DView;
    private TextBox textBox3;
    private Label lblSmc;
    private Timer timer1;

    public MobPicker() => this.InitializeComponent();

    private void MobPicker_Load(object sender, EventArgs e)
    {
      this.MenuList.Clear();
      for (int index = 0; index < NpcList.List.Count<tNpc>(); ++index)
        this.MenuList.Add(NpcList.List[index].ItemID.ToString() + " - " + NpcList.List[index].Name.ToString());
      this.listBox1.DataSource = (object) this.MenuList;
      this.InitializeDevice();
    }

    private void MakeLCModels(string SMCFile)
    {
      List<float> source1 = new List<float>();
      List<float> source2 = new List<float>();
      List<float> source3 = new List<float>();
      List<float> floatList1 = new List<float>();
      List<float> floatList2 = new List<float>();
      List<float> floatList3 = new List<float>();
      this._Models = new List<tMesh>();
      try
      {
        List<smcMesh> source4 = SMCReader.ReadFile(SMCFile);
        for (int index1 = 0; index1 < source4.Count<smcMesh>(); ++index1)
        {
          if (LCMeshReader.ReadFile(source4[index1].FileName))
          {
            tMeshContainer pMesh = LCMeshReader.pMesh;
            source1.Add(((IEnumerable<tVertex3f>) pMesh.Vertices).Max<tVertex3f>((Func<tVertex3f, float>) (p => p.X)));
            source2.Add(((IEnumerable<tVertex3f>) pMesh.Vertices).Max<tVertex3f>((Func<tVertex3f, float>) (p => p.Y)));
            source3.Add(((IEnumerable<tVertex3f>) pMesh.Vertices).Max<tVertex3f>((Func<tVertex3f, float>) (p => p.Z)));
            floatList1.Add(((IEnumerable<tVertex3f>) pMesh.Vertices).Min<tVertex3f>((Func<tVertex3f, float>) (p => p.X)));
            floatList2.Add(((IEnumerable<tVertex3f>) pMesh.Vertices).Min<tVertex3f>((Func<tVertex3f, float>) (p => p.Y)));
            floatList3.Add(((IEnumerable<tVertex3f>) pMesh.Vertices).Min<tVertex3f>((Func<tVertex3f, float>) (p => p.Z)));
            for (int index2 = 0; index2 < ((IEnumerable<tMeshObject>) pMesh.Objects).Count<tMeshObject>(); ++index2)
            {
              int toVert = (int) pMesh.Objects[index2].ToVert;
              int faceCount = (int) pMesh.Objects[index2].FaceCount;
              short[] faces = pMesh.Objects[index2].GetFaces();
              CustomVertex.PositionNormalTextured[] positionNormalTexturedArray = new CustomVertex.PositionNormalTextured[toVert];
              int fromVert = (int) pMesh.Objects[index2].FromVert;
              for (int index3 = 0; (long) index3 < (long) pMesh.Objects[index2].ToVert; ++index3)
              {
                positionNormalTexturedArray[index3].Position = new Vector3(pMesh.Vertices[fromVert].X, pMesh.Vertices[fromVert].Y, pMesh.Vertices[fromVert].Z);
                positionNormalTexturedArray[index3].Normal = new Vector3(pMesh.Normals[fromVert].X, pMesh.Normals[fromVert].Y, pMesh.Normals[fromVert].Z);
                try
                {
                  positionNormalTexturedArray[index3].Texture = new Vector2(pMesh.UVMaps[0].Coords[fromVert].U, pMesh.UVMaps[0].Coords[fromVert].V);
                }
                catch
                {
                  positionNormalTexturedArray[index3].Texture = new Vector2(0.0f, 0.0f);
                }
                ++fromVert;
              }
              VertexBuffer vertexBuffer = new VertexBuffer(this._Device, ((IEnumerable<CustomVertex.PositionNormalTextured>) positionNormalTexturedArray).Count<CustomVertex.PositionNormalTextured>() * 32, Usage.None, VertexFormat.PositionNormal | VertexFormat.Texture1, Pool.Default);
              Mesh mesh = new Mesh(this._Device, ((IEnumerable<short>) faces).Count<short>() / 3, ((IEnumerable<CustomVertex.PositionNormalTextured>) positionNormalTexturedArray).Count<CustomVertex.PositionNormalTextured>(), MeshFlags.Managed, VertexFormat.PositionNormal | VertexFormat.Texture1);
              DataStream dataStream1;
              using (dataStream1 = mesh.VertexBuffer.Lock(0, ((IEnumerable<CustomVertex.PositionNormalTextured>) positionNormalTexturedArray).Count<CustomVertex.PositionNormalTextured>() * 32, LockFlags.None))
              {
                dataStream1.WriteRange<CustomVertex.PositionNormalTextured>(positionNormalTexturedArray);
                mesh.VertexBuffer.Unlock();
              }
              DataStream dataStream2;
              using (dataStream2 = mesh.IndexBuffer.Lock(0, ((IEnumerable<short>) faces).Count<short>() * 2, LockFlags.None))
              {
                dataStream2.WriteRange<short>(faces);
                mesh.IndexBuffer.Unlock();
              }
              if (((IEnumerable<tMeshJointWeights>) pMesh.Weights).Count<tMeshJointWeights>() != 0)
              {
                string[] strArray = new string[((IEnumerable<tMeshJointWeights>) pMesh.Weights).Count<tMeshJointWeights>()];
                List<int>[] source5 = new List<int>[((IEnumerable<tMeshJointWeights>) pMesh.Weights).Count<tMeshJointWeights>()];
                List<float>[] floatListArray = new List<float>[((IEnumerable<tMeshJointWeights>) pMesh.Weights).Count<tMeshJointWeights>()];
                for (int index4 = 0; index4 < ((IEnumerable<tMeshJointWeights>) pMesh.Weights).Count<tMeshJointWeights>(); ++index4)
                {
                  strArray[index4] = this._Enc.GetString(pMesh.Weights[index4].JointName);
                  source5[index4] = new List<int>();
                  floatListArray[index4] = new List<float>();
                  for (int index5 = 0; index5 < ((IEnumerable<tMeshWeightsMap>) pMesh.Weights[index4].WeightsMap).Count<tMeshWeightsMap>(); ++index5)
                  {
                    source5[index4].Add(pMesh.Weights[index4].WeightsMap[index5].Index);
                    floatListArray[index4].Add(pMesh.Weights[index4].WeightsMap[index5].Weight);
                  }
                }
                mesh.SkinInfo = new SkinInfo(((IEnumerable<CustomVertex.PositionNormalTextured>) positionNormalTexturedArray).Count<CustomVertex.PositionNormalTextured>(), VertexFormat.PositionNormal | VertexFormat.Texture1, (int) pMesh.HeaderInfo.JointCount);
                for (int bone = 0; bone < ((IEnumerable<List<int>>) source5).Count<List<int>>(); ++bone)
                {
                  mesh.SkinInfo.SetBoneName(bone, strArray[bone]);
                  mesh.SkinInfo.SetBoneInfluence(bone, source5[bone].ToArray(), floatListArray[bone].ToArray());
                }
              }
              mesh.GenerateAdjacency(0.5f);
              mesh.ComputeNormals();
              Texture texture = (Texture) null;
              string objName = this._Enc.GetString(pMesh.Objects[index2].Textures[0].InternalName);
              int index6 = source4[index1].Object.FindIndex((Predicate<smcObject>) (x => x.Name.Equals(objName)));
              if (index6 != -1)
                texture = this.GetTextureFromFile(source4[index1].Object[index6].Texture);
              this._Models.Add(new tMesh(mesh, texture));
            }
          }
        }
      }
      catch
      {
      }
      try
      {
        this._Zoom = ((IEnumerable<float>) new float[3]
        {
          source1.Max(),
          source2.Max(),
          source3.Max()
        }).Max() * 3f;
      }
      catch
      {
      }
      this.slideZoom.Value = (int) this._Zoom * 100;
    }

    private void InitializeDevice()
    {
      this._Direct3D = new Direct3D();
      Direct3D direct3D = this._Direct3D;
      int adapter = 0;
      int num1 = 1;
      IntPtr handle1 = this.Handle;
      int num2 = 32;
      PresentParameters[] presentParametersArray = new PresentParameters[1];
      int index = 0;
      PresentParameters presentParameters = new PresentParameters();
      presentParameters.SwapEffect = SwapEffect.Discard;
      IntPtr handle2 = this.panel3DView.Handle;
      presentParameters.DeviceWindowHandle = handle2;
      int num3 = 1;
      presentParameters.Windowed = num3 != 0;
      int width = this.panel3DView.Width;
      presentParameters.BackBufferWidth = width;
      int height = this.panel3DView.Height;
      presentParameters.BackBufferHeight = height;
      int num4 = 21;
      presentParameters.BackBufferFormat = (SlimDX.Direct3D9.Format) num4;
      presentParametersArray[index] = presentParameters;
      this._Device = new Device(direct3D, adapter, (DeviceType) num1, handle1, (CreateFlags) num2, presentParametersArray);
      this._Device.SetRenderState<Cull>(RenderState.CullMode, Cull.None);
      this._Device.SetRenderState<FillMode>(RenderState.FillMode, FillMode.Solid);
      this._Device.SetRenderState(RenderState.Lighting, false);
      this.CameraPositioning();
    }

    private void CameraPositioning()
    {
      this._Device.SetTransform(TransformState.Projection, Matrix.PerspectiveFovLH(100f, 1f, 1f, 450f));
      this._Device.SetTransform(TransformState.View, Matrix.LookAtLH(new Vector3(0.0f, 0.0f, -5f), new Vector3(0.0f, 0.0f, 0.0f), new Vector3(0.0f, 1f, 0.0f)));
      this._Device.SetTransform(TransformState.World, Matrix.RotationYawPitchRoll(0.0f, 0.0f, 0.0f));
    }

    private void Render()
    {
      this._Device.Viewport = new Viewport(0, 0, this.panel3DView.Width, this.panel3DView.Height);
      this._Device.Clear(ClearFlags.ZBuffer | ClearFlags.Target, new Color4(Color.FromKnownColor(KnownColor.Control)), 1f, 0);
      this._Device.BeginScene();
      this._Device.SetTransform(TransformState.View, Matrix.LookAtLH(new Vector3(0.0f, 0.0f, this._Zoom), new Vector3(this._LeftRight, this._UpDown, 0.0f), new Vector3(0.0f, 1f, 0.0f)));
      this._Device.SetTransform(TransformState.World, Matrix.RotationYawPitchRoll(this._Rotation, 3.1f, 0.0f));
      if (this._Models != null && this._Models.Count<tMesh>() != 0)
      {
        for (int index = 0; index < this._Models.Count<tMesh>(); ++index)
        {
          if (this._Models[index].TexData != null)
            this._Device.SetTexture(0, (BaseTexture) this._Models[index].TexData);
          for (int subset = 0; subset < 1000; ++subset)
            this._Models[index].MeshData.DrawSubset(subset);
        }
      }
      this._Device.EndScene();
      this._Device.Present();
      this._Rotation -= 0.03f;
    }

    private SlimDX.Direct3D9.Format ConvFormat(texFormat tFormat)
    {
      SlimDX.Direct3D9.Format format = SlimDX.Direct3D9.Format.Unknown;
      switch (tFormat)
      {
        case texFormat.RGB:
          return SlimDX.Direct3D9.Format.R8G8B8;
        case texFormat.ARGB:
          return SlimDX.Direct3D9.Format.A8R8G8B8;
        case texFormat.DXT1:
          return SlimDX.Direct3D9.Format.Dxt1;
        case texFormat.DXT3:
          return SlimDX.Direct3D9.Format.Dxt3;
        default:
          return format;
      }
    }

    private Texture BuildTexture(byte[] imageData, SlimDX.Direct3D9.Format imageFormat, int width, int height)
    {
      switch (imageFormat)
      {
        case SlimDX.Direct3D9.Format.R8G8B8:
          MemoryStream memoryStream1;
          using (memoryStream1 = new MemoryStream())
          {
            Tex.makeRGB8(imageData, width, height).Save((Stream) memoryStream1, ImageFormat.Bmp);
            memoryStream1.Write(imageData, 0, imageData.Length);
            memoryStream1.Position = 0L;
            return Texture.FromStream(this._Device, (Stream) memoryStream1, width, height, 0, Usage.SoftwareProcessing, SlimDX.Direct3D9.Format.A8B8G8R8, Pool.Default, SlimDX.Direct3D9.Filter.None, SlimDX.Direct3D9.Filter.None, 0);
          }
        case SlimDX.Direct3D9.Format.A8R8G8B8:
          MemoryStream memoryStream2;
          using (memoryStream2 = new MemoryStream())
          {
            Tex.makeRGB(imageData, width, height).Save((Stream) memoryStream2, ImageFormat.Bmp);
            memoryStream2.Write(imageData, 0, imageData.Length);
            memoryStream2.Position = 0L;
            return Texture.FromStream(this._Device, (Stream) memoryStream2, width, height, 0, Usage.SoftwareProcessing, SlimDX.Direct3D9.Format.A8B8G8R8, Pool.Default, SlimDX.Direct3D9.Filter.None, SlimDX.Direct3D9.Filter.None, 0);
          }
        default:
          Texture texture = new Texture(this._Device, width, height, 0, Usage.None, imageFormat, Pool.Managed);
          using (Stream data = (Stream) texture.LockRectangle(0, LockFlags.None).Data)
          {
            data.Write(imageData, 0, ((IEnumerable<byte>) imageData).Count<byte>());
            texture.UnlockRectangle(0);
          }
          return texture;
      }
    }

    private Texture GetTextureFromFile(string FileName)
    {
      Texture textureFromFile = (Texture) null;
      if (File.Exists(FileName))
      {
        Tex.ReadFile(FileName);
        SlimDX.Direct3D9.Format imageFormat = this.ConvFormat(Tex.GetFormat());
        textureFromFile = this.BuildTexture(Tex.lcTex.imageData[0], imageFormat, (int) Tex.lcTex.Header.Width, (int) Tex.lcTex.Header.Height);
      }
      return textureFromFile;
    }

    public bool SearchString(string s) => s.ToUpper().Contains(this.textBox1.Text.ToUpper());

    public int GetIndexByComboBox(string comboBox)
    {
      try
      {
        return Convert.ToInt32(comboBox.Split(' ')[0]);
      }
      catch
      {
        return 0;
      }
    }

    private int GetID()
    {
      int result = -1;
      int.TryParse(this.listBox1.Text.Split(' ')[0], out result);
      return result;
    }

    private void textBox1_TextChanged(object sender, EventArgs e)
    {
      this.MenuListSearch = this.MenuList.FindAll(new Predicate<string>(this.SearchString));
      this.listBox1.DataSource = (object) this.MenuListSearch;
    }

    private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      int MobIndex = this.GetID();
      if (MobIndex == -1)
        return;
      tNpc tNpc = NpcList.List.Find((Predicate<tNpc>) (p => p.ItemID.Equals(MobIndex)));
      if (tNpc == null)
        return;
      MobIndex = tNpc.ItemID;
      this.textBox2.Text = tNpc.Name;
      this.textBox3.Text = tNpc.SMCPath;
      if (!this.chk3D.Checked || !File.Exists(this._ClientPath + this.textBox3.Text))
        return;
      Console.WriteLine("Create Model > " + this._ClientPath + this.textBox3.Text);
      this.MakeLCModels(this._ClientPath + this.textBox3.Text);
    }

    private void button1_Click(object sender, EventArgs e)
    {
      this.DialogResult = DialogResult.OK;
      this.MobIndex = this.GetID();
    }

    private void button2_Click(object sender, EventArgs e)
    {
      this.MobIndex = -1;
      this.DialogResult = DialogResult.OK;
    }

    private void button3_Click(object sender, EventArgs e) => this.Close();

    private void timer1_Tick(object sender, EventArgs e) => this.Render();

    private void slideZoom_Scroll(object sender, EventArgs e)
    {
      this._Zoom = (float) this.slideZoom.Value / 100f;
    }

    private void slideUpDown_Scroll(object sender, EventArgs e)
    {
      this._UpDown = (float) this.slideUpDown.Value / 1000f;
    }

    private void slideLeftRight_Scroll(object sender, EventArgs e)
    {
      this._LeftRight = (float) this.slideLeftRight.Value / 1000f;
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      this.components = (IContainer) new System.ComponentModel.Container();
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (MobPicker));
      this.listBox1 = new ListBox();
      this.groupBox1 = new GroupBox();
      this.textBox1 = new TextBox();
      this.groupBox2 = new GroupBox();
      this.button3 = new Button();
      this.button2 = new Button();
      this.button1 = new Button();
      this.groupBox3 = new GroupBox();
      this.label1 = new Label();
      this.textBox2 = new TextBox();
      this.groupBox20 = new GroupBox();
      this.chk3D = new CheckBox();
      this.slideLeftRight = new TrackBar();
      this.slideUpDown = new TrackBar();
      this.slideZoom = new TrackBar();
      this.panel3DView = new Panel();
      this.textBox3 = new TextBox();
      this.lblSmc = new Label();
      this.timer1 = new Timer(this.components);
      this.groupBox1.SuspendLayout();
      this.groupBox2.SuspendLayout();
      this.groupBox3.SuspendLayout();
      this.groupBox20.SuspendLayout();
      this.slideLeftRight.BeginInit();
      this.slideUpDown.BeginInit();
      this.slideZoom.BeginInit();
      this.SuspendLayout();
      this.listBox1.FormattingEnabled = true;
      this.listBox1.Location = new Point(6, 19);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new Size(205, 303);
      this.listBox1.TabIndex = 0;
      this.listBox1.SelectedIndexChanged += new EventHandler(this.listBox1_SelectedIndexChanged);
      this.groupBox1.Controls.Add((Control) this.textBox1);
      this.groupBox1.Location = new Point(11, 34);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(505, 52);
      this.groupBox1.TabIndex = 6;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Search";
      this.textBox1.BorderStyle = BorderStyle.FixedSingle;
      this.textBox1.Location = new Point(6, 19);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(482, 20);
      this.textBox1.TabIndex = 0;
      this.textBox1.TextChanged += new EventHandler(this.textBox1_TextChanged);
      this.groupBox2.Controls.Add((Control) this.button3);
      this.groupBox2.Controls.Add((Control) this.button2);
      this.groupBox2.Controls.Add((Control) this.button1);
      this.groupBox2.Controls.Add((Control) this.listBox1);
      this.groupBox2.Location = new Point(11, 92);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new Size(226, 363);
      this.groupBox2.TabIndex = 7;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "Npcs";
      this.button3.FlatStyle = FlatStyle.Flat;
      this.button3.Location = new Point(165, 328);
      this.button3.Name = "button3";
      this.button3.Size = new Size(46, 23);
      this.button3.TabIndex = 3;
      this.button3.Text = "Close";
      this.button3.UseVisualStyleBackColor = true;
      this.button3.Click += new EventHandler(this.button3_Click);
      this.button2.FlatStyle = FlatStyle.Flat;
      this.button2.Location = new Point(104, 328);
      this.button2.Name = "button2";
      this.button2.Size = new Size(55, 23);
      this.button2.TabIndex = 2;
      this.button2.Text = "None";
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.button1.FlatStyle = FlatStyle.Flat;
      this.button1.Location = new Point(6, 328);
      this.button1.Name = "button1";
      this.button1.Size = new Size(92, 23);
      this.button1.TabIndex = 1;
      this.button1.Text = "Pick";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.groupBox3.Controls.Add((Control) this.label1);
      this.groupBox3.Controls.Add((Control) this.textBox2);
      this.groupBox3.Location = new Point(243, 92);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Size = new Size(273, 57);
      this.groupBox3.TabIndex = 8;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "Preview";
      this.label1.AutoSize = true;
      this.label1.Location = new Point(4, 24);
      this.label1.Name = "label1";
      this.label1.Size = new Size(58, 13);
      this.label1.TabIndex = 5;
      this.label1.Text = "Npc Name";
      this.textBox2.BorderStyle = BorderStyle.FixedSingle;
      this.textBox2.Location = new Point(64, 20);
      this.textBox2.Name = "textBox2";
      this.textBox2.ReadOnly = true;
      this.textBox2.Size = new Size(192, 20);
      this.textBox2.TabIndex = 4;
      this.groupBox20.Controls.Add((Control) this.chk3D);
      this.groupBox20.Controls.Add((Control) this.slideLeftRight);
      this.groupBox20.Controls.Add((Control) this.slideUpDown);
      this.groupBox20.Controls.Add((Control) this.slideZoom);
      this.groupBox20.Controls.Add((Control) this.panel3DView);
      this.groupBox20.Location = new Point(243, 155);
      this.groupBox20.Name = "groupBox20";
      this.groupBox20.Size = new Size(279, 313);
      this.groupBox20.TabIndex = 53;
      this.groupBox20.TabStop = false;
      this.groupBox20.Text = "3D View";
      this.chk3D.AutoSize = true;
      this.chk3D.Checked = true;
      this.chk3D.CheckState = CheckState.Checked;
      this.chk3D.FlatStyle = FlatStyle.Flat;
      this.chk3D.Location = new Point(180, 0);
      this.chk3D.Name = "chk3D";
      this.chk3D.Size = new Size(99, 17);
      this.chk3D.TabIndex = 38;
      this.chk3D.Text = "Enable 3D View";
      this.chk3D.UseVisualStyleBackColor = true;
      this.slideLeftRight.AutoSize = false;
      this.slideLeftRight.Location = new Point(188, 284);
      this.slideLeftRight.Maximum = 10000;
      this.slideLeftRight.Minimum = -10000;
      this.slideLeftRight.Name = "slideLeftRight";
      this.slideLeftRight.Size = new Size(85, 25);
      this.slideLeftRight.TabIndex = 3;
      this.slideLeftRight.TickStyle = TickStyle.None;
      this.slideLeftRight.Scroll += new EventHandler(this.slideLeftRight_Scroll);
      this.slideUpDown.AutoSize = false;
      this.slideUpDown.Location = new Point(95, 284);
      this.slideUpDown.Maximum = 10000;
      this.slideUpDown.Minimum = -10000;
      this.slideUpDown.Name = "slideUpDown";
      this.slideUpDown.Size = new Size(85, 25);
      this.slideUpDown.TabIndex = 2;
      this.slideUpDown.TickStyle = TickStyle.None;
      this.slideUpDown.Scroll += new EventHandler(this.slideUpDown_Scroll);
      this.slideZoom.AutoSize = false;
      this.slideZoom.Location = new Point(7, 284);
      this.slideZoom.Maximum = 10000;
      this.slideZoom.Minimum = -10000;
      this.slideZoom.Name = "slideZoom";
      this.slideZoom.Size = new Size(85, 25);
      this.slideZoom.TabIndex = 1;
      this.slideZoom.TickStyle = TickStyle.None;
      this.slideZoom.Scroll += new EventHandler(this.slideZoom_Scroll);
      this.panel3DView.Location = new Point(7, 20);
      this.panel3DView.Name = "panel3DView";
      this.panel3DView.Size = new Size(266, 258);
      this.panel3DView.TabIndex = 0;
      this.textBox3.BorderStyle = BorderStyle.FixedSingle;
      this.textBox3.Location = new Point(46, 479);
      this.textBox3.Name = "textBox3";
      this.textBox3.Size = new Size(476, 20);
      this.textBox3.TabIndex = 1;
      this.lblSmc.AutoSize = true;
      this.lblSmc.Location = new Point(7, 483);
      this.lblSmc.Name = "lblSmc";
      this.lblSmc.Size = new Size(33, 13);
      this.lblSmc.TabIndex = 54;
      this.lblSmc.Text = "SMC:";
      this.timer1.Enabled = true;
      this.timer1.Interval = 1;
      this.timer1.Tick += new EventHandler(this.timer1_Tick);
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(527, 511);
      this.Controls.Add((Control) this.lblSmc);
      this.Controls.Add((Control) this.textBox3);
      this.Controls.Add((Control) this.groupBox20);
      this.Controls.Add((Control) this.groupBox1);
      this.Controls.Add((Control) this.groupBox2);
      this.Controls.Add((Control) this.groupBox3);
      this.Icon = (Icon) componentResourceManager.GetObject("$this.Icon");
      this.Name = nameof (MobPicker);
      this.Text = "NPCPicker";
      this.Load += new EventHandler(this.MobPicker_Load);
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.groupBox2.ResumeLayout(false);
      this.groupBox3.ResumeLayout(false);
      this.groupBox3.PerformLayout();
      this.groupBox20.ResumeLayout(false);
      this.groupBox20.PerformLayout();
      this.slideLeftRight.EndInit();
      this.slideUpDown.EndInit();
      this.slideZoom.EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
