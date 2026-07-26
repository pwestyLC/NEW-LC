// Decompiled with JetBrains decompiler
// Type: SMCEditor3.SMCReader
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System.Collections.Generic;
using System.IO;
using System.Linq;

#nullable disable
namespace SMCEditor3
{
  internal class SMCReader
  {
    public static List<smcMesh> ReadFile(string FileName)
    {
      string[] source = Path.GetDirectoryName(FileName).Split('\\');
      string str1 = "";
      bool flag = true;
      for (int index = 0; index < ((IEnumerable<string>) source).Count<string>(); ++index)
      {
        if (source[index].ToUpper() == "DATA")
          flag = false;
        if (flag)
          str1 = str1 + source[index] + "\\";
      }
      List<string> list = ((IEnumerable<string>) File.ReadAllLines(FileName)).ToList<string>();
      string MeshName = "";
      foreach (string str2 in list)
      {
        if (str2.Contains("NAME"))
          MeshName = str2.Split('"')[1].Trim();
      }
      for (int index = list.Count<string>() - 1; index >= 0; --index)
      {
        list[index] = list[index].Trim();
        list[index] = list[index].Replace("TFNM", "");
        if (list[index].Contains("{") || list[index].Contains("}") || list[index].Contains(",") || list[index].Contains("NAME") || list[index].Contains("COLISION") || list[index].Contains("TEXTURES") || list[index].Contains("ANIM") || list[index].Contains("SKELETON"))
          list.RemoveAt(index);
      }
      int index1 = -1;
      List<smcMesh> smcMeshList = new List<smcMesh>();
      for (int index2 = 0; index2 < list.Count<string>(); ++index2)
      {
        try
        {
          if (list[index2].Substring(0, 4) == "MESH")
          {
            ++index1;
            string[] strArray = list[index2].Split('"');
            smcMeshList.Add(new smcMesh(strArray[1], MeshName));
          }
          else
          {
            string[] strArray = list[index2].Split('"');
            smcMeshList[index1].Object.Add(new smcObject(strArray[1], strArray[3]));
          }
        }
        catch
        {
        }
      }
      return smcMeshList;
    }
  }
}
