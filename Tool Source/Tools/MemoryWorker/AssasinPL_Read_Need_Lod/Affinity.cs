// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.AssasinPL_Read_Need_Lod.Affinity
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using LcDevPack_TeamDamonA.Tools.MemoryWorker.Affinity_EP4_By_Assasin;
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.AssasinPL_Read_Need_Lod
{
  public class Affinity
  {
    public static string ISO = "Windows-874";

    public static bool ReadAffinity(string affinityFilePath)
    {
      Encoding.GetEncoding(Affinity.ISO);
      try
      {
        using (BinaryReader binaryReader = new BinaryReader((Stream) File.Open(affinityFilePath, FileMode.Open)))
        {
          binaryReader.ReadInt32();
          while (binaryReader.BaseStream.Position < binaryReader.BaseStream.Length)
          {
            tAffinity tAffinity = new tAffinity();
            tAffinity.a_index = binaryReader.ReadInt32();
            tAffinity.a_texture_id = binaryReader.ReadInt32();
            tAffinity.a_texture_row = binaryReader.ReadInt32();
            tAffinity.a_texture_col = binaryReader.ReadInt32();
            tAffinity.a_needitemidx = binaryReader.ReadInt32();
            tAffinity.a_needitemcount = binaryReader.ReadInt32();
            tAffinity.a_needlevel = binaryReader.ReadInt32();
            tAffinity.a_affinity_idx = binaryReader.ReadInt32();
            tAffinity.a_affinity_value = binaryReader.ReadInt32();
            tAffinity.NpcCount = binaryReader.ReadInt32();
            for (int index = 0; index < tAffinity.NpcCount; ++index)
              tAffinity.Npcs.Add(new tAffinityNpc()
              {
                a_npcidx = binaryReader.ReadInt32(),
                a_flag = binaryReader.ReadInt32(),
                a_string_idx = binaryReader.ReadInt32(),
                a_affinity_idx = tAffinity.a_index,
                a_use_point = 0,
                a_enable = true
              });
            tAffinity.WorkItemCount = binaryReader.ReadInt32();
            for (int index = 0; index < tAffinity.WorkItemCount; ++index)
              tAffinity.Work.Add(new tAffinityWork()
              {
                a_type_idx = binaryReader.ReadInt32(),
                a_value = binaryReader.ReadInt32(),
                a_work_type = 0,
                a_enable = true,
                a_affinity_idx = tAffinity.a_index
              });
            tAffinity.WorkMonsterCount = binaryReader.ReadInt32();
            for (int index = 0; index < tAffinity.WorkMonsterCount; ++index)
              tAffinity.Work.Add(new tAffinityWork()
              {
                a_type_idx = binaryReader.ReadInt32(),
                a_value = binaryReader.ReadInt32(),
                a_id = binaryReader.ReadInt32(),
                a_row = binaryReader.ReadInt32(),
                a_col = binaryReader.ReadInt32(),
                a_work_type = 1,
                a_enable = true,
                a_affinity_idx = tAffinity.a_index
              });
            tAffinity.WorkQuestCount = binaryReader.ReadInt32();
            for (int index = 0; index < tAffinity.WorkQuestCount; ++index)
              tAffinity.Work.Add(new tAffinityWork()
              {
                a_type_idx = binaryReader.ReadInt32(),
                a_value = binaryReader.ReadInt32(),
                a_work_type = 2,
                a_enable = true,
                a_affinity_idx = tAffinity.a_index
              });
            int index1 = tAffinity.Npcs.FindIndex((Predicate<tAffinityNpc>) (p => !Convert.ToBoolean(p.a_flag & 4)));
            if (index1 == -1)
              index1 = tAffinity.Npcs.FindIndex((Predicate<tAffinityNpc>) (p => Convert.ToBoolean(p.a_flag & 1) && Convert.ToBoolean(p.a_flag & 2) && Convert.ToBoolean(p.a_flag & 8)));
            tAffinity.ItemCount = binaryReader.ReadInt32();
            for (int index2 = 0; index2 < tAffinity.ItemCount; ++index2)
              tAffinity.Items.Add(new tAffinityRewardItem()
              {
                a_itemidx = binaryReader.ReadInt32(),
                a_allow_point = binaryReader.ReadInt32(),
                a_npcidx = tAffinity.Npcs[index1].a_npcidx,
                a_flag = 0,
                a_count = 0,
                a_exp = 0,
                a_sp = 0,
                a_needpclevel = 0,
                a_needitemidx = 0,
                a_needitemcount = 0
              });
            Affinity_EP4.AffinityList.Add(tAffinity);
          }
          binaryReader.Close();
        }
        return true;
      }
      catch (Exception ex)
      {
        List<tAffinity> affinityList = Affinity_EP4.AffinityList;
        return false;
      }
    }

    public static bool ReadAffinityString(string AffinityString)
    {
      ASCIIEncoding asciiEncoding = new ASCIIEncoding();
      try
      {
        using (BinaryReader binaryReader = new BinaryReader((Stream) File.Open(AffinityString, FileMode.Open)))
        {
          binaryReader.ReadInt32();
          binaryReader.ReadInt32();
          while (binaryReader.BaseStream.Position < binaryReader.BaseStream.Length)
          {
            int ID = binaryReader.ReadInt32();
            int index = Affinity_EP4.AffinityList.FindIndex((Predicate<tAffinity>) (p => p.a_index.Equals(ID)));
            string str = Encoding.GetEncoding("Windows-874").GetString(binaryReader.ReadBytes(binaryReader.ReadInt32()));
            if (index != -1)
              Affinity_EP4.AffinityList[index].a_name_usa = str;
          }
          binaryReader.Close();
          binaryReader.Dispose();
        }
        return true;
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.ToString());
        return false;
      }
    }
  }
}
