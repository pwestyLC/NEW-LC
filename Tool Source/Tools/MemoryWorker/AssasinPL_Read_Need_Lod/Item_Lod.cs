// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.AssasinPL_Read_Need_Lod.Item_Lod
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Text;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.AssasinPL_Read_Need_Lod
{
  public class Item_Lod
  {
    public static List<ItemContainer> ItemList = new List<ItemContainer>();
    private static byte[] key;

    public static string GetNameFromID(int ItemID)
    {
      int index = Item_Lod.ItemList.FindIndex((Predicate<ItemContainer>) (p => p.ItemID.Equals(ItemID)));
      if (index == -1)
        return "None";
      return Item_Lod.ItemList[index].Type != 0 && Item_Lod.ItemList[index].Type != 1 ? Item_Lod.ItemList[index].Name : Item_Lod.ItemList[index].Name + " (Lv" + Item_Lod.ItemList[index].Level.ToString() + ")";
    }

    public static string GetTooltipText(int ItemID)
    {
      string tooltipText = "";
      int index = Item_Lod.ItemList.FindIndex((Predicate<ItemContainer>) (p => p.ItemID.Equals(ItemID)));
      if (index != -1)
        tooltipText = Item_Lod.ItemList[index].Name.ToString() + "\r\n\r\n" + Item_Lod.ItemList[index].Description?.ToString();
      return tooltipText;
    }

    public static Bitmap Icon(object Item)
    {
      int ItemID = 0;
      int.TryParse(Item.ToString(), out ItemID);
      int num1 = 0;
      int num2 = 0;
      int num3 = 0;
      int index = Item_Lod.ItemList.FindIndex((Predicate<ItemContainer>) (p => p.ItemID.Equals(ItemID)));
      if (index != -1)
      {
        num1 = Item_Lod.ItemList[index].TexID;
        num2 = Item_Lod.ItemList[index].TexRow;
        num3 = Item_Lod.ItemList[index].TexCol;
      }
      Image image = Image.FromFile("icons/ItemBtn" + num1.ToString() + ".png");
      Bitmap bitmap = new Bitmap(32, 32);
      Graphics graphics = Graphics.FromImage((Image) bitmap);
      int y = num2 * 32;
      Rectangle srcRect = new Rectangle(num3 * 32, y, 32, 32);
      graphics.DrawImage(image, 0, 0, srcRect, GraphicsUnit.Pixel);
      graphics.Dispose();
      return bitmap;
    }

    public static Bitmap Icon(int ID, int Row, int Col)
    {
      Image image = Image.FromFile("icons/ItemBtn" + ID.ToString() + ".png");
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
      Encoding.GetEncoding("windows-1251");
      try
      {
        using (BinaryReader binaryReader = new BinaryReader((Stream) File.Open(FileName, FileMode.Open)))
        {
          binaryReader.ReadInt32();
          while (binaryReader.BaseStream.Position < binaryReader.BaseStream.Length)
          {
            ItemContainer itemContainer = new ItemContainer();
            if (binaryReader.BaseStream.Length - 25L > binaryReader.BaseStream.Position)
            {
              itemContainer.ItemID = binaryReader.ReadInt32();
              itemContainer.JobFlag = binaryReader.ReadInt32();
              itemContainer.Weight = binaryReader.ReadInt32();
              itemContainer.MaxUse = binaryReader.ReadInt32();
              itemContainer.Level = binaryReader.ReadInt32();
              itemContainer.Flag = binaryReader.ReadInt64();
              itemContainer.Position = binaryReader.ReadInt32();
              itemContainer.Type = binaryReader.ReadInt32();
              itemContainer.SubType = binaryReader.ReadInt32();
              int[] numArray1 = new int[10];
              int[] numArray2 = new int[10];
              for (int index = 0; index < 10; ++index)
              {
                numArray1[index] = binaryReader.ReadInt32();
                numArray2[index] = binaryReader.ReadInt32();
              }
              itemContainer.CraftItemID = numArray1;
              itemContainer.CraftItemAmount = numArray2;
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
              itemContainer.Set1 = binaryReader.ReadInt32();
              itemContainer.Set2 = binaryReader.ReadInt32();
              itemContainer.Set3 = binaryReader.ReadInt32();
              itemContainer.Set4 = binaryReader.ReadInt32();
              itemContainer.Set5 = binaryReader.ReadInt32();
              itemContainer.Smc = Encoding.GetEncoding("Windows-874").GetString(binaryReader.ReadBytes(64));
              itemContainer.Effect1 = Encoding.GetEncoding("Windows-874").GetString(binaryReader.ReadBytes(32));
              itemContainer.Effect2 = Encoding.GetEncoding("Windows-874").GetString(binaryReader.ReadBytes(32));
              itemContainer.Effect3 = Encoding.GetEncoding("Windows-874").GetString(binaryReader.ReadBytes(32));
              itemContainer.JewelOptionType = binaryReader.ReadInt32();
              itemContainer.JewelOptionLevel = binaryReader.ReadInt32();
              int[] numArray3 = new int[10];
              int[] numArray4 = new int[10];
              for (int index = 0; index < 10; ++index)
                numArray3[index] = binaryReader.ReadInt32();
              for (int index = 0; index < 10; ++index)
                numArray4[index] = binaryReader.ReadInt32();
              itemContainer.rareOptionType = numArray3;
              itemContainer.rareOptionChance = numArray4;
              itemContainer.syndicate_type = binaryReader.ReadInt32();
              itemContainer.syndicate_grade = binaryReader.ReadInt32();
              itemContainer.fortuneIndex = binaryReader.ReadInt32();
              itemContainer.castleWar = (int) binaryReader.ReadByte();
              Item_Lod.ItemList.Add(itemContainer);
            }
            else
              binaryReader.BaseStream.Position = binaryReader.BaseStream.Length;
            if (binaryReader.BaseStream.Length - binaryReader.BaseStream.Position == 8L)
              Item_Lod.key = binaryReader.ReadBytes(8);
          }
        }
        return true;
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.ToString());
        return false;
      }
    }

    public static bool LoadFromFileName(string FileNameName)
    {
      ASCIIEncoding asciiEncoding = new ASCIIEncoding();
      try
      {
        using (BinaryReader binaryReader = new BinaryReader((Stream) File.Open(FileNameName, FileMode.Open)))
        {
          binaryReader.ReadInt32();
          binaryReader.ReadInt32();
          while (binaryReader.BaseStream.Position < binaryReader.BaseStream.Length)
          {
            int ID = binaryReader.ReadInt32();
            int index = Item_Lod.ItemList.FindIndex((Predicate<ItemContainer>) (p => p.ItemID.Equals(ID)));
            string str1 = Encoding.GetEncoding("Windows-874").GetString(binaryReader.ReadBytes(binaryReader.ReadInt32()));
            string str2 = Encoding.GetEncoding("Windows-874").GetString(binaryReader.ReadBytes(binaryReader.ReadInt32()));
            if (index != -1)
            {
              Item_Lod.ItemList[index].Name = str1;
              Item_Lod.ItemList[index].Description = str2;
            }
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
