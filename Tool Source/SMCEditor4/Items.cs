// Decompiled with JetBrains decompiler
// Type: SMCEditor3.Items
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using FieryLib.IO;
using FieryLib.Models;
using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Drawing;

#nullable disable
namespace SMCEditor3
{
  internal class Items
  {
    public static string[] itemFiles = new string[3]
    {
      "itemAll_rus.lod",
      "itemAll_ger.lod",
      "itemAll.lod"
    };
    public static List<ItemAllLod> ItemList = new List<ItemAllLod>();
    public static List<StrModel> NameItem = new List<StrModel>();
    public static List<string> Menu = new List<string>();

    public static string GetNameFromID(int ItemID)
    {
      int index = Items.ItemList.FindIndex((Predicate<ItemAllLod>) (p => p.ItemID.Equals(ItemID)));
      return index != -1 ? Items.NameItem[index].m_name : "None";
    }

    public static string GetTooltipText(int ItemID)
    {
      string tooltipText = "";
      int index = Items.ItemList.FindIndex((Predicate<ItemAllLod>) (p => p.ItemID.Equals(ItemID)));
      if (index != -1)
        tooltipText = Items.NameItem[index].m_name + "\r\n\r\n" + Items.NameItem[index].m_descs[0];
      return tooltipText;
    }

    public static Bitmap Icon(object Item)
    {
      int ItemID = 0;
      int.TryParse(Item.ToString(), out ItemID);
      int num1 = 0;
      int num2 = 0;
      int num3 = 0;
      int index = Items.ItemList.FindIndex((Predicate<ItemAllLod>) (p => p.ItemID.Equals(ItemID)));
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

    public static void LoadFromFile(string FileName, string Filestr, string smc)
    {
      Items.ItemList = LodReader.ReadLod<ItemAllLod>(FileName);
      Items.NameItem = StrLoader.LoadStringFile(StrFileType.ITEM, Filestr);
      Items.SaveReg(FileName, Filestr, smc);
    }

    private static void SaveReg(string a, string b, string c)
    {
      RegistryKey subKey1 = Registry.CurrentUser.CreateSubKey("[R]Developer");
      subKey1.SetValue("Creator", (object) "RomeoST");
      using (RegistryKey subKey2 = subKey1.CreateSubKey("SMCLC"))
      {
        subKey2.SetValue("Path", (object) a);
        subKey2.SetValue("PathSMC", (object) c);
        subKey2.SetValue("PathName", (object) b);
      }
    }
  }
}
