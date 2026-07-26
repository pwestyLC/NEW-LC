// Decompiled with JetBrains decompiler
// Type: SMCEditor4.Items
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Text;

#nullable disable
namespace SMCEditor4
{
  internal class Items
  {
    public static string ISO = "windows-874";
    public static string[] itemFiles = new string[3]
    {
      "itemAll_usa.lod",
      "itemAll_ger.lod",
      "itemAll.lod"
    };
    public static List<ItemContainer> ItemList = new List<ItemContainer>();
    public static List<string> Menu = new List<string>();
    public static string[] stringFiles = new string[1]
    {
      "strItem_us.lod"
    };
    public static List<StringContainer> StringList = new List<StringContainer>();
    public static int Version;

    public static string GetNameFromID(int ItemID)
    {
      int index = Items.StringList.FindIndex((Predicate<StringContainer>) (p => p.Index.Equals(ItemID)));
      return index != -1 ? Encoding.GetEncoding(Items.ISO).GetString(Items.StringList[index].name) : "None";
    }

    public static string GetTooltipText(int ItemID)
    {
      string tooltipText = "";
      int index = Items.ItemList.FindIndex((Predicate<ItemContainer>) (p => p.ItemID.Equals(ItemID)));
      if (index != -1)
        tooltipText = Items.ItemList[index].Name + "\r\n\r\n" + Items.ItemList[index].Description;
      return tooltipText;
    }

    public static Bitmap Icon(object Item)
    {
      int ItemID = 0;
      int.TryParse(Item.ToString(), out ItemID);
      int num1 = 0;
      int num2 = 0;
      int num3 = 0;
      int index = Items.ItemList.FindIndex((Predicate<ItemContainer>) (p => p.ItemID.Equals(ItemID)));
      if (index != -1)
      {
        num1 = Items.ItemList[index].TexID;
        num2 = Items.ItemList[index].TexRow;
        num3 = Items.ItemList[index].TexCol;
      }
      Image image = Image.FromFile("Images/ItemBtn" + num1.ToString() + ".png");
      Bitmap bitmap = new Bitmap(42, 42);
      Graphics graphics = Graphics.FromImage((Image) bitmap);
      int y = num2 * 32;
      Rectangle srcRect = new Rectangle(num3 * 32, y, 64, 64);
      graphics.DrawImage(image, 0, 0, srcRect, GraphicsUnit.Pixel);
      graphics.Dispose();
      return bitmap;
    }

    public static Bitmap Icon(int ID, int Row, int Col)
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

    public static bool LoadFromFile(string FileName)
    {
      ASCIIEncoding asciiEncoding = new ASCIIEncoding();
      using (BinaryReader binaryReader = new BinaryReader((Stream) File.Open(FileName, FileMode.Open)))
      {
        binaryReader.ReadInt32();
        while (binaryReader.BaseStream.Position < binaryReader.BaseStream.Length)
        {
          ItemContainer itemContainer = new ItemContainer();
          if (Items.Version == 2015)
          {
            itemContainer.ItemID = binaryReader.ReadInt32();
            itemContainer.JobFlag = binaryReader.ReadInt32();
            itemContainer.Weight = binaryReader.ReadInt32();
            itemContainer.Fame = binaryReader.ReadInt32();
            itemContainer.Level = binaryReader.ReadInt32();
            itemContainer.flag2015 = binaryReader.ReadInt64();
            itemContainer.MaxUse = binaryReader.ReadInt32();
            itemContainer.Type = binaryReader.ReadInt32();
            itemContainer.SubType = binaryReader.ReadInt32();
            int[] numArray1 = new int[10];
            int[] numArray2 = new int[10];
            for (int index = 0; index < 10; ++index)
            {
              numArray1[index] = binaryReader.ReadInt32();
              numArray2[index] = binaryReader.ReadInt32();
            }
            itemContainer.needitem = numArray1;
            itemContainer.needprob = numArray2;
            itemContainer.Need_SSkill1_Id = binaryReader.ReadInt32();
            itemContainer.Need_SSkill1_Level = binaryReader.ReadInt32();
            itemContainer.Need_SSkill2_Id = binaryReader.ReadInt32();
            itemContainer.Need_SSkill2_Level = binaryReader.ReadInt32();
            itemContainer.TexID = binaryReader.ReadInt32();
            itemContainer.TexRow = binaryReader.ReadInt32();
            itemContainer.TexCol = binaryReader.ReadInt32();
            itemContainer.Num0 = binaryReader.ReadInt32();
            itemContainer.Num1 = binaryReader.ReadInt32();
            itemContainer.Num2 = binaryReader.ReadInt32();
            itemContainer.Num3 = binaryReader.ReadInt32();
            itemContainer.Price = binaryReader.ReadInt32();
            itemContainer.Random0 = binaryReader.ReadInt32();
            itemContainer.Random1 = binaryReader.ReadInt32();
            itemContainer.Random2 = binaryReader.ReadInt32();
            itemContainer.Random3 = binaryReader.ReadInt32();
            itemContainer.Random4 = binaryReader.ReadInt32();
            itemContainer.Smc = Encoding.GetEncoding(Items.ISO).GetString(binaryReader.ReadBytes(64)).Replace("\0", string.Empty);
            itemContainer.Effect1 = Encoding.GetEncoding(Items.ISO).GetString(binaryReader.ReadBytes(32));
            itemContainer.Effect2 = Encoding.GetEncoding(Items.ISO).GetString(binaryReader.ReadBytes(32));
            itemContainer.Effect3 = Encoding.GetEncoding(Items.ISO).GetString(binaryReader.ReadBytes(32));
            itemContainer.OtherID = binaryReader.ReadInt32();
            itemContainer.Print = binaryReader.ReadInt32();
            itemContainer.rareidx = new int[10];
            itemContainer.rarechance = new int[10];
            for (int index = 0; index < 10; ++index)
              itemContainer.rareidx[index] = binaryReader.ReadInt32();
            for (int index = 0; index < 10; ++index)
              itemContainer.rarechance[index] = binaryReader.ReadInt32();
            itemContainer.RvR_Value = binaryReader.ReadInt32();
            itemContainer.RvR_Grade = binaryReader.ReadInt32();
            itemContainer.Fortune = binaryReader.ReadInt32();
            itemContainer.Set = (int) binaryReader.ReadByte();
          }
          if (Items.Version == 2012 || Items.Version == 2013)
          {
            itemContainer.ItemID = binaryReader.ReadInt32();
            itemContainer.Name = asciiEncoding.GetString(binaryReader.ReadBytes(binaryReader.ReadInt32()));
            itemContainer.JobFlag = binaryReader.ReadInt32();
            itemContainer.Weight = binaryReader.ReadInt32();
            itemContainer.MaxUse = binaryReader.ReadInt32();
            itemContainer.Level = binaryReader.ReadInt32();
            itemContainer.Flag = binaryReader.ReadInt32();
            itemContainer.Position = binaryReader.ReadInt32();
            itemContainer.Type = binaryReader.ReadInt32();
            itemContainer.SubType = binaryReader.ReadInt32();
            int[] numArray3 = new int[10];
            int[] numArray4 = new int[10];
            for (int index = 0; index < 10; ++index)
            {
              numArray3[index] = binaryReader.ReadInt32();
              numArray4[index] = binaryReader.ReadInt32();
            }
            itemContainer.CraftItemID = numArray3;
            itemContainer.CraftItemAmount = numArray4;
            itemContainer.Need_SSkill1_Id = binaryReader.ReadInt32();
            itemContainer.Need_SSkill1_Level = binaryReader.ReadInt32();
            itemContainer.Need_SSkill2_Id = binaryReader.ReadInt32();
            itemContainer.Need_SSkill2_Level = binaryReader.ReadInt32();
            itemContainer.Num0 = binaryReader.ReadInt32();
            itemContainer.Num1 = binaryReader.ReadInt32();
            itemContainer.Num2 = binaryReader.ReadInt32();
            itemContainer.Num3 = binaryReader.ReadInt32();
            itemContainer.Price = binaryReader.ReadInt32();
            itemContainer.Smc = asciiEncoding.GetString(binaryReader.ReadBytes(binaryReader.ReadInt32()));
            itemContainer.TexID = binaryReader.ReadInt32();
            itemContainer.TexRow = binaryReader.ReadInt32();
            itemContainer.TexCol = binaryReader.ReadInt32();
            itemContainer.Description = asciiEncoding.GetString(binaryReader.ReadBytes(binaryReader.ReadInt32()));
            itemContainer.Effect1 = asciiEncoding.GetString(binaryReader.ReadBytes(binaryReader.ReadInt32()));
            itemContainer.Effect2 = asciiEncoding.GetString(binaryReader.ReadBytes(binaryReader.ReadInt32()));
            itemContainer.Effect3 = asciiEncoding.GetString(binaryReader.ReadBytes(binaryReader.ReadInt32()));
            itemContainer.Set1 = binaryReader.ReadInt32();
            itemContainer.Set2 = binaryReader.ReadInt32();
            itemContainer.Set3 = binaryReader.ReadInt32();
            itemContainer.Set4 = binaryReader.ReadInt32();
            itemContainer.Set5 = binaryReader.ReadInt32();
            itemContainer.RareOption = binaryReader.ReadInt32();
            itemContainer.RareChance = binaryReader.ReadInt32();
            if (Items.Version == 2013)
            {
              int num = binaryReader.ReadInt32();
              binaryReader.BaseStream.Position += (long) (num * 16);
            }
          }
          if (Items.Version == 2008)
          {
            itemContainer.ItemID = binaryReader.ReadInt32();
            itemContainer.Name = asciiEncoding.GetString(binaryReader.ReadBytes(binaryReader.ReadInt32()));
            itemContainer.JobFlag = binaryReader.ReadInt32();
            itemContainer.Weight = binaryReader.ReadInt32();
            itemContainer.MaxUse = binaryReader.ReadInt32();
            itemContainer.Level = binaryReader.ReadInt32();
            itemContainer.Flag = binaryReader.ReadInt32();
            itemContainer.Position = binaryReader.ReadInt32();
            itemContainer.Type = binaryReader.ReadInt32();
            itemContainer.SubType = binaryReader.ReadInt32();
            int[] numArray5 = new int[10];
            int[] numArray6 = new int[10];
            for (int index = 0; index < 10; ++index)
            {
              numArray5[index] = binaryReader.ReadInt32();
              numArray6[index] = binaryReader.ReadInt32();
            }
            itemContainer.CraftItemID = numArray5;
            itemContainer.CraftItemAmount = numArray6;
            itemContainer.Need_SSkill1_Id = binaryReader.ReadInt32();
            itemContainer.Need_SSkill1_Level = binaryReader.ReadInt32();
            itemContainer.Need_SSkill2_Id = binaryReader.ReadInt32();
            itemContainer.Need_SSkill2_Level = binaryReader.ReadInt32();
            itemContainer.Num0 = binaryReader.ReadInt32();
            itemContainer.Num1 = binaryReader.ReadInt32();
            itemContainer.Num2 = binaryReader.ReadInt32();
            itemContainer.Num3 = binaryReader.ReadInt32();
            itemContainer.Price = binaryReader.ReadInt32();
            itemContainer.Smc = asciiEncoding.GetString(binaryReader.ReadBytes(binaryReader.ReadInt32()));
            itemContainer.TexID = binaryReader.ReadInt32();
            itemContainer.TexRow = binaryReader.ReadInt32();
            itemContainer.TexCol = binaryReader.ReadInt32();
            itemContainer.Description = asciiEncoding.GetString(binaryReader.ReadBytes(binaryReader.ReadInt32()));
            itemContainer.Effect1 = asciiEncoding.GetString(binaryReader.ReadBytes(binaryReader.ReadInt32()));
            itemContainer.Set1 = binaryReader.ReadInt32();
            itemContainer.Set2 = binaryReader.ReadInt32();
            itemContainer.Set3 = binaryReader.ReadInt32();
            itemContainer.Set4 = binaryReader.ReadInt32();
          }
          if (Items.Version == 2005)
          {
            itemContainer.ItemID = binaryReader.ReadInt32();
            itemContainer.Name = asciiEncoding.GetString(binaryReader.ReadBytes(binaryReader.ReadInt32()));
            itemContainer.JobFlag = binaryReader.ReadInt32();
            itemContainer.Weight = binaryReader.ReadInt32();
            itemContainer.Level = binaryReader.ReadInt32();
            itemContainer.Flag = binaryReader.ReadInt32();
            itemContainer.Position = binaryReader.ReadInt32();
            itemContainer.Type = binaryReader.ReadInt32();
            itemContainer.SubType = binaryReader.ReadInt32();
            int[] numArray7 = new int[10];
            int[] numArray8 = new int[10];
            for (int index = 0; index < 10; ++index)
            {
              numArray7[index] = binaryReader.ReadInt32();
              numArray8[index] = binaryReader.ReadInt32();
            }
            itemContainer.CraftItemID = numArray7;
            itemContainer.CraftItemAmount = numArray8;
            itemContainer.Need_SSkill1_Id = binaryReader.ReadInt32();
            itemContainer.Need_SSkill1_Level = binaryReader.ReadInt32();
            itemContainer.Need_SSkill2_Id = binaryReader.ReadInt32();
            itemContainer.Need_SSkill2_Level = binaryReader.ReadInt32();
            itemContainer.Num0 = binaryReader.ReadInt32();
            itemContainer.Num1 = binaryReader.ReadInt32();
            itemContainer.Num2 = binaryReader.ReadInt32();
            itemContainer.Num3 = binaryReader.ReadInt32();
            itemContainer.Price = binaryReader.ReadInt32();
            itemContainer.Smc = asciiEncoding.GetString(binaryReader.ReadBytes(binaryReader.ReadInt32()));
            itemContainer.TexID = binaryReader.ReadInt32();
            itemContainer.TexRow = binaryReader.ReadInt32();
            itemContainer.TexCol = binaryReader.ReadInt32();
            itemContainer.Description = asciiEncoding.GetString(binaryReader.ReadBytes(binaryReader.ReadInt32()));
          }
          if (binaryReader.BaseStream.Length - binaryReader.BaseStream.Position == 8L)
            binaryReader.BaseStream.Position += 8L;
          Items.ItemList.Add(itemContainer);
          if (binaryReader.BaseStream.Length - binaryReader.BaseStream.Position == 8L)
            binaryReader.BaseStream.Position += 8L;
        }
      }
      return true;
    }

    public static bool LoadSTRFromFile(string FileName)
    {
      ASCIIEncoding asciiEncoding = new ASCIIEncoding();
      using (BinaryReader binaryReader = new BinaryReader((Stream) File.Open(FileName, FileMode.Open)))
      {
        binaryReader.ReadInt32();
        binaryReader.ReadInt32();
        while (binaryReader.BaseStream.Position < binaryReader.BaseStream.Length)
        {
          StringContainer stringContainer = new StringContainer();
          stringContainer.Index = binaryReader.ReadInt32();
          stringContainer.name = binaryReader.ReadBytes(binaryReader.ReadInt32());
          stringContainer.descr = binaryReader.ReadBytes(binaryReader.ReadInt32());
          Items.StringList.Add(stringContainer);
          Items.Menu.Add(stringContainer.Index.ToString() + " - " + Encoding.GetEncoding(Items.ISO).GetString(stringContainer.name));
        }
      }
      return true;
    }
  }
}
