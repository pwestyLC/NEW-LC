// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.Affinity_EP4_By_Assasin.tAffinity
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System.Collections.Generic;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.Affinity_EP4_By_Assasin
{
  public class tAffinity
  {
    public List<tAffinityNpc> Npcs = new List<tAffinityNpc>();
    public List<tAffinityWork> Work = new List<tAffinityWork>();
    public List<tAffinityRewardItem> Items = new List<tAffinityRewardItem>();
    public int a_index;
    public int a_texture_id;
    public int a_texture_row;
    public int a_texture_col;
    public int a_needitemidx;
    public int a_needitemcount;
    public int a_needlevel;
    public int a_affinity_idx;
    public int a_affinity_value;
    public string a_name_usa;
    public int NpcCount;
    public int WorkItemCount;
    public int WorkMonsterCount;
    public int WorkQuestCount;
    public int ItemCount;
    public int a_nas;
    public bool a_enable;
    public int a_maxvalue;

    public string MakeList { get; set; }
  }
}
