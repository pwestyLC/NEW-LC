// Decompiled with JetBrains decompiler
// Type: MapDtaRead.MapDataS
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System.Collections.Generic;

#nullable disable
namespace MapDtaRead
{
  internal class MapDataS
  {
    public int ZoneID { get; set; }

    public int nIndex { get; set; }

    public sbyte sbLayer { get; set; }

    public int nLeft { get; set; }

    public int nTop { get; set; }

    public int nRight { get; set; }

    public int nBottom { get; set; }

    public float fRatio { get; set; }

    public long unknown { get; set; }

    public sbyte sbDetailCount { get; set; }

    public sbyte sbSubZoneCount { get; set; }

    public int NpcCount { get; set; }

    public List<MapDetail> DetailZones { get; set; }

    public List<SubZones> SubData { get; set; }

    public List<MapDtaRead.NpcData> NpcData { get; set; }
  }
}
