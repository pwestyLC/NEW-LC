// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.Catalog_Editor.itemAll
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System;
using System.Collections.Generic;
using System.Drawing;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.Catalog_Editor
{
  internal class itemAll
  {
    public static List<itemAll.t_ItemAll> ItemList = new List<itemAll.t_ItemAll>();
    public static List<string> Menu = new List<string>();
    public static int Version = 2012;
    private static byte[] key;

    public static Bitmap Icon(object Item)
    {
      try
      {
        int ItemID = 0;
        int.TryParse(Item.ToString(), out ItemID);
        int num1 = 0;
        int num2 = 0;
        int num3 = 0;
        int index = itemAll.ItemList.FindIndex((Predicate<itemAll.t_ItemAll>) (p => p.ItemID.Equals(ItemID)));
        if (index != -1)
        {
          num1 = itemAll.ItemList[index].TexID;
          num2 = itemAll.ItemList[index].TexRow;
          num3 = itemAll.ItemList[index].TexCol;
        }
        Image image = Image.FromFile("Images/ItemBtn" + num1.ToString() + ".png");
        Bitmap bitmap = new Bitmap(32, 32);
        Graphics graphics = Graphics.FromImage((Image) bitmap);
        int y = num2 * 32;
        Rectangle srcRect = new Rectangle(num3 * 32, y, 32, 32);
        graphics.DrawImage(image, 0, 0, srcRect, GraphicsUnit.Pixel);
        graphics.Dispose();
        return bitmap;
      }
      catch
      {
        return (Bitmap) null;
      }
    }

    public static Bitmap Icon1(int ID, int Row, int Col)
    {
      try
      {
        Image image = Image.FromFile("Images/ItemBtn" + ID.ToString() + ".png");
        Bitmap bitmap = new Bitmap(42, 42);
        Graphics graphics = Graphics.FromImage((Image) bitmap);
        int y = Row * 32;
        Rectangle srcRect = new Rectangle(Col * 32, y, 64, 64);
        graphics.DrawImage(image, 0, 0, srcRect, GraphicsUnit.Pixel);
        graphics.Dispose();
        return bitmap;
      }
      catch
      {
        return (Bitmap) null;
      }
    }

    public class t_ItemAll
    {
      public int EditFlag;
      public string Name;
      public string Descr;
      public int[] CraftItemAmount;
      public int[] CraftItemID;
      public int[] rareOptionType;
      public int[] rareOptionChance;
      public string Effect1;
      public string Effect2;
      public string Effect3;
      public long Flag;
      public int ItemID;
      public int JobFlag;
      public int Level;
      public int MaxUse;
      public int Need_SSkill1_Id;
      public int Need_SSkill1_Level;
      public int Need_SSkill2_Id;
      public int Need_SSkill2_Level;
      public int Num0;
      public int Num1;
      public int Num2;
      public int Num3;
      public int Position;
      public int Price;
      public int RareChance;
      public int RareOption;
      public int Set1;
      public int Set2;
      public int Set3;
      public int Set4;
      public int Set5;
      public string Smc;
      public int SubType;
      public int TexCol;
      public int TexID;
      public int TexRow;
      public int Type;
      public int Weight;
      public int syndicate_type;
      public int fortuneIndex;
      public int castleWar;
      public int syndicate_grade;
      public int JewelOptionLevel;
      public int JewelOptionType;
    }
  }
}
