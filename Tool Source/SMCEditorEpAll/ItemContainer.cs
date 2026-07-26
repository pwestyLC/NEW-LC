// Decompiled with JetBrains decompiler
// Type: SMCEditor4.ItemContainer
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

#nullable disable
namespace SMCEditor4
{
  public class ItemContainer
  {
    public int EditFlag;

    public object Clone() => this.MemberwiseClone();

    public int[] CraftItemAmount { get; set; }

    public int[] CraftItemID { get; set; }

    public string Description { get; set; }

    public string Effect1 { get; set; }

    public string Effect2 { get; set; }

    public string Effect3 { get; set; }

    public int Fame { get; set; }

    public int Flag { get; set; }

    public long flag2015 { get; set; }

    public int Fortune { get; set; }

    public int ItemID { get; set; }

    public int JobFlag { get; set; }

    public int Level { get; set; }

    public int MaxUse { get; set; }

    public string Name { get; set; }

    public int Need_SSkill1_Id { get; set; }

    public int Need_SSkill1_Level { get; set; }

    public int Need_SSkill2_Id { get; set; }

    public int Need_SSkill2_Level { get; set; }

    public int[] needitem { get; set; }

    public int[] needprob { get; set; }

    public int Num0 { get; set; }

    public int Num1 { get; set; }

    public int Num2 { get; set; }

    public int Num3 { get; set; }

    public int OtherID { get; set; }

    public int Position { get; set; }

    public int Price { get; set; }

    public int Print { get; set; }

    public int Random0 { get; set; }

    public int Random1 { get; set; }

    public int Random2 { get; set; }

    public int Random3 { get; set; }

    public int Random4 { get; set; }

    public int[] rarechance { get; set; }

    public int RareChance { get; set; }

    public int[] rareidx { get; set; }

    public int RareOption { get; set; }

    public int RvR_Grade { get; set; }

    public int RvR_Value { get; set; }

    public int Set { get; set; }

    public int Set1 { get; set; }

    public int Set2 { get; set; }

    public int Set3 { get; set; }

    public int Set4 { get; set; }

    public int Set5 { get; set; }

    public string Smc { get; set; }

    public int SubType { get; set; }

    public int TexCol { get; set; }

    public int TexID { get; set; }

    public int TexRow { get; set; }

    public int Type { get; set; }

    public int Weight { get; set; }
  }
}
