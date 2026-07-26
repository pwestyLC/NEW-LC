// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Types
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System.Collections.Generic;

#nullable disable
namespace LcDevPack_TeamDamonA
{
  public class Types
  {
    public static string[] JobSubTypes(int Type)
    {
      List<string> stringList = new List<string>();
      switch (Type)
      {
        case 0:
          stringList.Add("0 - None");
          stringList.Add("1 - Highlander");
          stringList.Add("2 - Warmaster");
          break;
        case 1:
          stringList.Add("0 - None");
          stringList.Add("1 - Royal");
          stringList.Add("2 - Templar");
          break;
        case 2:
          stringList.Add("0 - None");
          stringList.Add("1 - Archer");
          stringList.Add("2 - Cleric");
          break;
        case 3:
          stringList.Add("0 - None");
          stringList.Add("1 - Wizard");
          stringList.Add("2 - Witch");
          break;
        case 4:
          stringList.Add("0 - None");
          stringList.Add("1 - Assasin");
          stringList.Add("2 - Ranger");
          break;
        case 5:
          stringList.Add("0 - None");
          stringList.Add("1 - Elementalist");
          stringList.Add("2 - Specialist");
          break;
        case 6:
          stringList.Add("0 - None");
          stringList.Add("1 - NightShadow");
          stringList.Add("2 - NightShadow2");
          break;
        case 7:
          stringList.Add("0 - None");
          stringList.Add("1 - Ex-Assasin");
          stringList.Add("2 - Ex-Ranger");
          break;
        case 8:
          stringList.Add("0 - None");
          stringList.Add("1 - Ex-Wizard");
          stringList.Add("2 - Ex-Witch");
          break;
        default:
          stringList.Add("-1 - Unknown");
          break;
      }
      return stringList.ToArray();
    }
  }
}
