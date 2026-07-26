// Decompiled with JetBrains decompiler
// Type: MapDtaRead.LoadFile
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System;
using System.Collections.Generic;
using System.IO;

#nullable disable
namespace MapDtaRead
{
  internal class LoadFile
  {
    public static List<MapDataS> MapShit = new List<MapDataS>();

    public static void LoadFromFile(string Filename)
    {
      try
      {
        LoadFile.MapShit.Clear();
        using (BinaryReader binaryReader = new BinaryReader((Stream) File.Open(Filename, FileMode.Open)))
        {
          int num = binaryReader.ReadInt32();
          while (binaryReader.BaseStream.Position < binaryReader.BaseStream.Length)
          {
            for (int index1 = 0; index1 < num; ++index1)
            {
              MapDataS mapDataS = new MapDataS();
              mapDataS.DetailZones = new List<MapDetail>();
              mapDataS.SubData = new List<SubZones>();
              mapDataS.NpcData = new List<NpcData>();
              mapDataS.nIndex = binaryReader.ReadInt32();
              mapDataS.sbLayer = binaryReader.ReadSByte();
              mapDataS.nLeft = binaryReader.ReadInt32();
              mapDataS.nTop = binaryReader.ReadInt32();
              mapDataS.nRight = binaryReader.ReadInt32();
              mapDataS.nBottom = binaryReader.ReadInt32();
              mapDataS.fRatio = binaryReader.ReadSingle();
              mapDataS.unknown = binaryReader.ReadInt64();
              mapDataS.sbDetailCount = binaryReader.ReadSByte();
              for (int index2 = 0; index2 < (int) mapDataS.sbDetailCount; ++index2)
                mapDataS.DetailZones.Add(new MapDetail()
                {
                  nSelLeft = binaryReader.ReadInt32(),
                  nSelTop = binaryReader.ReadInt32(),
                  nSelRight = binaryReader.ReadInt32(),
                  nSelBottom = binaryReader.ReadInt32(),
                  nLeft = binaryReader.ReadInt32(),
                  nTop = binaryReader.ReadInt32(),
                  nRight = binaryReader.ReadInt32(),
                  nBottom = binaryReader.ReadInt32(),
                  fX = binaryReader.ReadSingle(),
                  fZ = binaryReader.ReadSingle(),
                  fRatio = binaryReader.ReadSingle()
                });
              mapDataS.sbSubZoneCount = binaryReader.ReadSByte();
              for (int index3 = 0; index3 < (int) mapDataS.sbSubZoneCount; ++index3)
                mapDataS.SubData.Add(new SubZones()
                {
                  nIndex = binaryReader.ReadInt32(),
                  fX = binaryReader.ReadSingle(),
                  fZ = binaryReader.ReadSingle(),
                  sbtype = binaryReader.ReadSByte()
                });
              mapDataS.NpcCount = binaryReader.ReadInt32();
              for (int index4 = 0; index4 < mapDataS.NpcCount; ++index4)
                mapDataS.NpcData.Add(new NpcData()
                {
                  nIndex = binaryReader.ReadInt32(),
                  Unknown = binaryReader.ReadInt32(),
                  fX = binaryReader.ReadSingle(),
                  fZ = binaryReader.ReadSingle()
                });
              LoadFile.MapShit.Add(mapDataS);
            }
          }
        }
      }
      catch (Exception ex)
      {
        int num = (int) new Error(ex.Message + "\n \n" + ex.StackTrace + "\n \n" + LoadFile.MapShit.Count.ToString()).ShowDialog();
      }
    }
  }
}
