// Decompiled with JetBrains decompiler
// Type: UTIL.INI
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System.Runtime.InteropServices;
using System.Text;

#nullable disable
namespace UTIL
{
  internal class INI
  {
    private string iniPath;

    public INI(string path) => this.iniPath = path;

    [DllImport("kernel32.dll")]
    private static extern int GetPrivateProfileString(
      string section,
      string key,
      string def,
      StringBuilder retVal,
      int size,
      string filePath);

    [DllImport("kernel32.dll")]
    private static extern long WritePrivateProfileString(
      string section,
      string key,
      string val,
      string filePath);

    public string GetIniValue(string Section, string Key)
    {
      StringBuilder retVal = new StringBuilder((int) byte.MaxValue);
      INI.GetPrivateProfileString(Section, Key, "", retVal, (int) byte.MaxValue, this.iniPath);
      return retVal.ToString();
    }

    public void SetIniValue(string Section, string Key, string Value)
    {
      INI.WritePrivateProfileString(Section, Key, Value, this.iniPath);
    }
  }
}
