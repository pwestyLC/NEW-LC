// Decompiled with JetBrains decompiler
// Type: SMCEditor4.tSmcRecords
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System.Collections.Generic;

#nullable disable
namespace SMCEditor4
{
  public class tSmcRecords
  {
    public object Clone() => this.MemberwiseClone();

    public bool haveData { get; set; }

    public int ID { get; set; }

    public List<tModels> Models { get; set; }

    public string Name { get; set; }
  }
}
