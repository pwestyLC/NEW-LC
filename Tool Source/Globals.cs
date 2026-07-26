// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Globals
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

#nullable disable
namespace LcDevPack_TeamDamonA
{
  public class Globals
  {
    public static string Name = "LastChaos Tool Pack";
    public static string DebugRelease = "R";
    public static string Version = "2.0" + EditorInformation.Editor_Release.Length.ToString() + "." + EditorInformation.Editor_Beta.Length.ToString() + EditorInformation.Editor_Alpha.Length.ToString() + Globals.DebugRelease;
    public static bool Console = false;
  }
}
