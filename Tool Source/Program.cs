// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Program
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System;
using System.Windows.Forms;
using System.Runtime.CompilerServices;

#nullable disable
namespace LcDevPack_TeamDamonA
{
  internal static class Program
  {
    [STAThread]
    private static void Main()
    {
      Application.EnableVisualStyles();
      Application.SetCompatibleTextRenderingDefault(false);

      // Ensure MobEditor3DManager static constructor runs so the 3D manager starts its timer
      try
      {
          RuntimeHelpers.RunClassConstructor(typeof(MobEditor3DManager).TypeHandle);
      }
      catch { }

      Application.Run((Form) new LcDevPack_TeamDamonA.Main());
    }
  }
}
