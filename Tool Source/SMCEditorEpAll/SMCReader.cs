// Decompiled with JetBrains decompiler
// Type: SMCEditor4.SMCReader
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System.Collections.Generic;
using System.IO;
using System.Linq;

#nullable disable
namespace SMCEditor4
{
  internal class SMCReader
  {
    public static List<smcMesh> ReadFile(string FileName)
    {
      string[] source1 = Path.GetDirectoryName(FileName).Split('\\');
      string str1 = "";
      bool flag = true;
      for (int index = 0; index < ((IEnumerable<string>) source1).Count<string>(); ++index)
      {
        if (source1[index].ToUpper() == "DATA")
          flag = false;
        if (flag)
          str1 = str1 + source1[index] + "\\";
      }
      List<string> source2 = !File.Exists(FileName) ? new List<string>() : ((IEnumerable<string>) File.ReadAllLines(FileName)).ToList<string>();
      string MeshName = "";
      foreach (string str2 in source2)
      {
        if (str2.Contains("NAME"))
          MeshName = str2.Split('"')[1].Trim();
      }
      for (int index = source2.Count<string>() - 1; index >= 0; --index)
      {
        source2[index] = source2[index].Trim();
        source2[index] = source2[index].Replace("TFNM", "");
        if (source2[index].Contains("{") || source2[index].Contains("}") || source2[index].Contains(",") || source2[index].Contains("NAME") || source2[index].Contains("COLISION") || source2[index].Contains("TEXTURES") || source2[index].Contains("ANIM") || source2[index].Contains("SKELETON"))
          source2.RemoveAt(index);
      }
      int index1 = -1;
      List<smcMesh> smcMeshList = new List<smcMesh>();
      for (int index2 = 0; index2 < source2.Count<string>(); ++index2)
      {
        try
        {
          if (source2[index2].Substring(0, 4) == "MESH")
          {
            ++index1;
            string[] strArray = source2[index2].Split('"');
            smcMeshList.Add(new smcMesh(strArray[1], MeshName));
          }
          else
          {
            string[] strArray = source2[index2].Split('"');
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
