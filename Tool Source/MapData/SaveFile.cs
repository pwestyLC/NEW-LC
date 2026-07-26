// Decompiled with JetBrains decompiler
// Type: MapDtaRead.SaveFile
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System;
using System.IO;

#nullable disable
namespace MapDtaRead
{
  internal class SaveFile
  {
    public static void SaveToFile(string Filename)
    {
      try
      {
        using (BinaryWriter binaryWriter = new BinaryWriter((Stream) File.Create(Filename)))
        {
          binaryWriter.Write(Convert.ToInt32(LoadFile.MapShit.Count));
          for (int index1 = 0; index1 < LoadFile.MapShit.Count; ++index1)
          {
            binaryWriter.Write(LoadFile.MapShit[index1].nIndex);
            binaryWriter.Write(LoadFile.MapShit[index1].sbLayer);
            binaryWriter.Write(LoadFile.MapShit[index1].nLeft);
            binaryWriter.Write(LoadFile.MapShit[index1].nTop);
            binaryWriter.Write(LoadFile.MapShit[index1].nRight);
            binaryWriter.Write(LoadFile.MapShit[index1].nBottom);
            binaryWriter.Write(LoadFile.MapShit[index1].fRatio);
            binaryWriter.Write(LoadFile.MapShit[index1].unknown);
            if (LoadFile.MapShit[index1].sbDetailCount > (sbyte) 0)
            {
              binaryWriter.Write(Convert.ToSByte(LoadFile.MapShit[index1].DetailZones.Count));
              for (int index2 = 0; index2 < LoadFile.MapShit[index1].DetailZones.Count; ++index2)
              {
                binaryWriter.Write(LoadFile.MapShit[index1].DetailZones[index2].nSelLeft);
                binaryWriter.Write(LoadFile.MapShit[index1].DetailZones[index2].nSelTop);
                binaryWriter.Write(LoadFile.MapShit[index1].DetailZones[index2].nSelRight);
                binaryWriter.Write(LoadFile.MapShit[index1].DetailZones[index2].nSelBottom);
                binaryWriter.Write(LoadFile.MapShit[index1].DetailZones[index2].nLeft);
                binaryWriter.Write(LoadFile.MapShit[index1].DetailZones[index2].nTop);
                binaryWriter.Write(LoadFile.MapShit[index1].DetailZones[index2].nRight);
                binaryWriter.Write(LoadFile.MapShit[index1].DetailZones[index2].nBottom);
                binaryWriter.Write(LoadFile.MapShit[index1].DetailZones[index2].fX);
                binaryWriter.Write(LoadFile.MapShit[index1].DetailZones[index2].fZ);
                binaryWriter.Write(LoadFile.MapShit[index1].DetailZones[index2].fRatio);
              }
            }
            else
            {
              sbyte num = 0;
              binaryWriter.Write(num);
            }
            if (LoadFile.MapShit[index1].sbSubZoneCount > (sbyte) 0)
            {
              binaryWriter.Write(Convert.ToSByte(LoadFile.MapShit[index1].SubData.Count));
              for (int index3 = 0; index3 < LoadFile.MapShit[index1].SubData.Count; ++index3)
              {
                binaryWriter.Write(LoadFile.MapShit[index1].SubData[index3].nIndex);
                binaryWriter.Write(LoadFile.MapShit[index1].SubData[index3].fX);
                binaryWriter.Write(LoadFile.MapShit[index1].SubData[index3].fZ);
                binaryWriter.Write(LoadFile.MapShit[index1].SubData[index3].sbtype);
              }
            }
            else
            {
              sbyte num = 0;
              binaryWriter.Write(num);
            }
            if (LoadFile.MapShit[index1].NpcCount > 0)
            {
              binaryWriter.Write(Convert.ToInt32(LoadFile.MapShit[index1].NpcData.Count));
              for (int index4 = 0; index4 < LoadFile.MapShit[index1].NpcData.Count; ++index4)
              {
                binaryWriter.Write(Convert.ToInt32(LoadFile.MapShit[index1].NpcData[index4].nIndex));
                binaryWriter.Write(LoadFile.MapShit[index1].NpcData[index4].Unknown);
                binaryWriter.Write(LoadFile.MapShit[index1].NpcData[index4].fX);
                binaryWriter.Write(LoadFile.MapShit[index1].NpcData[index4].fZ);
              }
            }
            else
            {
              int num = 0;
              binaryWriter.Write(num);
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
