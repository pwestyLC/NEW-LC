// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.Item.Items
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.Item
{
  internal class Items
  {
    public static string ISO = "ISO-8859-1";

    public static Bitmap Icon(object Item)
    {
      int ItemID = 0;
      int.TryParse(Item.ToString(), out ItemID);
      int num1 = 0;
      int num2 = 0;
      int num3 = 0;
      int index = ItemAll.ItemList.FindIndex((Predicate<ItemContainer>) (p => p.ItemID.Equals(ItemID)));
      if (index != -1)
      {
        num1 = ItemAll.ItemList[index].TexID;
        num2 = ItemAll.ItemList[index].TexRow;
        num3 = ItemAll.ItemList[index].TexCol;
      }
      Image image = Image.FromFile("icons/ItemBtn" + num1.ToString() + ".png");
      Bitmap bitmap = new Bitmap(32, 32);
      Graphics graphics = Graphics.FromImage((Image) bitmap);
      int y = num2 * 32;
      Rectangle srcRect = new Rectangle(num3 * 32, y, 64, 64);
      graphics.DrawImage(image, 0, 0, srcRect, GraphicsUnit.Pixel);
      graphics.Dispose();
      return bitmap;
    }

    public static Bitmap Icon(int ID, int Row, int Col)
    {
      Image image = Image.FromFile("icons/ItemBtn" + ID.ToString() + ".png");
      Bitmap bitmap = new Bitmap(32, 32);
      Graphics graphics = Graphics.FromImage((Image) bitmap);
      int y = Row * 32;
      Rectangle srcRect = new Rectangle(Col * 32, y, 64, 64);
      graphics.DrawImage(image, 0, 0, srcRect, GraphicsUnit.Pixel);
      graphics.Dispose();
      return bitmap;
    }

    public static string GetNameFromID(object ItemID)
    {
      int Item = -1;
      int.TryParse(ItemID.ToString(), out Item);
      string nameFromId = "";
      int index = ItemAll.ItemList.FindIndex((Predicate<ItemContainer>) (p => p.ItemID.Equals(Item)));
      if (index != -1)
        nameFromId = ItemAll.ItemList[index].Name;
      return nameFromId;
    }

    public static string GetTooltipText(int ItemID)
    {
      string tooltipText = "";
      int index = ItemAll.ItemList.FindIndex((Predicate<ItemContainer>) (p => p.ItemID.Equals(ItemID)));
      if (index != -1)
        tooltipText = ItemAll.ItemList[index].Name + "\r\n\r\n" + ItemAll.ItemList[index].Description;
      return tooltipText;
    }

    public static bool SaveFile(string FileName)
    {
      bool flag;
      try
      {
        List<int> SortedIDs = new List<int>();
        for (int index = 0; index < ItemAll.ItemList.Count<ItemContainer>(); ++index)
        {
          if (ItemAll.ItemList[index].EditFlag != 3)
            SortedIDs.Add(ItemAll.ItemList[index].ItemID);
        }
        SortedIDs.Sort();
        MemoryStream output = new MemoryStream();
        BinaryWriter binaryWriter = new BinaryWriter((Stream) output);
        binaryWriter.Write(ItemAll.ItemList.Max<ItemContainer>((Func<ItemContainer, int>) (p => p.ItemID)));
        for (int a = 0; a < SortedIDs.Count<int>(); ++a)
        {
          int index1 = ItemAll.ItemList.FindIndex((Predicate<ItemContainer>) (p => p.ItemID.Equals(SortedIDs[a])));
          if (index1 != -1)
          {
            binaryWriter.Write(ItemAll.ItemList[index1].ItemID);
            binaryWriter.Write(ItemAll.ItemList[index1].JobFlag);
            binaryWriter.Write(ItemAll.ItemList[index1].Weight);
            binaryWriter.Write(ItemAll.ItemList[index1].MaxUse);
            binaryWriter.Write(ItemAll.ItemList[index1].Level);
            binaryWriter.Write(ItemAll.ItemList[index1].Flag);
            binaryWriter.Write(ItemAll.ItemList[index1].Position);
            binaryWriter.Write(ItemAll.ItemList[index1].Type);
            binaryWriter.Write(ItemAll.ItemList[index1].SubType);
            for (int index2 = 0; index2 < 10; ++index2)
            {
              binaryWriter.Write(ItemAll.ItemList[index1].CraftItemID[index2]);
              binaryWriter.Write(ItemAll.ItemList[index1].CraftItemAmount[index2]);
            }
            binaryWriter.Write(ItemAll.ItemList[index1].Need_SSkill1_Id);
            binaryWriter.Write(ItemAll.ItemList[index1].Need_SSkill1_Level);
            binaryWriter.Write(ItemAll.ItemList[index1].Need_SSkill2_Id);
            binaryWriter.Write(ItemAll.ItemList[index1].Need_SSkill2_Level);
            binaryWriter.Write(ItemAll.ItemList[index1].TexID);
            binaryWriter.Write(ItemAll.ItemList[index1].TexRow);
            binaryWriter.Write(ItemAll.ItemList[index1].TexCol);
            binaryWriter.Write(ItemAll.ItemList[index1].Num0);
            binaryWriter.Write(ItemAll.ItemList[index1].Num1);
            binaryWriter.Write(ItemAll.ItemList[index1].Num2);
            binaryWriter.Write(ItemAll.ItemList[index1].Num3);
            binaryWriter.Write(ItemAll.ItemList[index1].Price);
            binaryWriter.Write(ItemAll.ItemList[index1].Set1);
            binaryWriter.Write(ItemAll.ItemList[index1].Set2);
            binaryWriter.Write(ItemAll.ItemList[index1].Set3);
            binaryWriter.Write(ItemAll.ItemList[index1].Set4);
            binaryWriter.Write(ItemAll.ItemList[index1].Set5);
            string smc = ItemAll.ItemList[index1].Smc;
            byte[] buffer1 = new byte[64];
            int length1 = smc.Length > 64 ? 64 : smc.Length;
            Encoding.UTF8.GetBytes(smc.Substring(0, length1)).CopyTo((Array) buffer1, 0);
            binaryWriter.Write(buffer1);
            string effect1 = ItemAll.ItemList[index1].Effect1;
            byte[] buffer2 = new byte[32];
            int length2 = effect1.Length > 32 ? 32 : effect1.Length;
            Encoding.UTF8.GetBytes(effect1.Substring(0, length2)).CopyTo((Array) buffer2, 0);
            binaryWriter.Write(buffer2);
            string effect2 = ItemAll.ItemList[index1].Effect2;
            byte[] buffer3 = new byte[32];
            int length3 = effect2.Length > 32 ? 32 : effect2.Length;
            Encoding.UTF8.GetBytes(effect2.Substring(0, length3)).CopyTo((Array) buffer3, 0);
            binaryWriter.Write(buffer3);
            string effect3 = ItemAll.ItemList[index1].Effect3;
            byte[] buffer4 = new byte[32];
            int num = effect3.Length > 32 ? 32 : effect3.Length;
            Encoding.UTF8.GetBytes(effect3.Substring(0, length3)).CopyTo((Array) buffer4, 0);
            binaryWriter.Write(buffer4);
            binaryWriter.Write(ItemAll.ItemList[index1].JewelOptionType);
            binaryWriter.Write(ItemAll.ItemList[index1].JewelOptionLevel);
            for (int index3 = 0; index3 < 10; ++index3)
              binaryWriter.Write(ItemAll.ItemList[index1].rareOptionType[index3]);
            for (int index4 = 0; index4 < 10; ++index4)
              binaryWriter.Write(ItemAll.ItemList[index1].rareOptionChance[index4]);
            binaryWriter.Write(ItemAll.ItemList[index1].syndicate_type);
            binaryWriter.Write(ItemAll.ItemList[index1].syndicate_grade);
            binaryWriter.Write(ItemAll.ItemList[index1].fortuneIndex);
            binaryWriter.Write(ItemAll.ItemList[index1].castleWar);
          }
        }
        File.WriteAllBytes(FileName, output.ToArray());
        binaryWriter.Close();
        output.Close();
        flag = true;
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.ToString());
        flag = false;
      }
      return flag;
    }

    public static string[] SubTypes(int Type)
    {
      List<string> stringList = new List<string>();
      switch (Type)
      {
        case 0:
          stringList.Add("IWEAPON_NIGHT");
          stringList.Add("IWEAPON_CROSSBOW");
          stringList.Add("IWEAPON_STAFF");
          stringList.Add("IWEAPON_BIGSWORD");
          stringList.Add("IWEAPON_AXE");
          stringList.Add("IWEAPON_SHORTSTAFF");
          stringList.Add("IWEAPON_BOW");
          stringList.Add("IWEAPON_SHORTGUM");
          stringList.Add("IWEAPON_MINING");
          stringList.Add("IWEAPON_GATHERING");
          stringList.Add("IWEAPON_CHARGE");
          stringList.Add("IWEAPON_TWOSWORD");
          stringList.Add("IWEAPON_WAND");
          stringList.Add("IWEAPON_SCYTHE");
          stringList.Add("IWEAPON_POLEARM");
          stringList.Add("IWEAPON_SOUL");
          break;
        case 1:
          stringList.Add("IWEAR_HELMET");
          stringList.Add("IWEAR_ARMOR");
          stringList.Add("IWEAR_PANTS");
          stringList.Add("IWEAR_GLOVE");
          stringList.Add("IWEAR_SHOES");
          stringList.Add("IWEAR_SHIELD");
          stringList.Add("IWEAR_BACKWING");
          stringList.Add("IWEAR_SUIT");
          break;
        case 2:
          stringList.Add("IONCE_WARP");
          stringList.Add("IONCE_PROCESS_DOC");
          stringList.Add("IONCE_MAKE_TYPE_DOC");
          stringList.Add("IONCE_BOX");
          stringList.Add("IONCE_MAKE_POTION_DOC");
          stringList.Add("IONCE_CHANGE_DOC");
          stringList.Add("IONCE_QUEST_SCROLL");
          stringList.Add("IONCE_CASH");
          stringList.Add("IONCE_SUMMON");
          stringList.Add("IONCE_ETC");
          stringList.Add("IONCE_TARGET");
          stringList.Add("IONCE_TITLE");
          stringList.Add("IONCE_REWARD_PACKAGE");
          stringList.Add("IONCE_JUMPING_POTION");
          stringList.Add("IONCE_EXTEND_CHARACTER_SLOT");
          stringList.Add("IONCE_SERVER_TRANS");
          stringList.Add("IONCE_REMOTE_EXPRESS");
          break;
        case 3:
          stringList.Add("ITEM_BULLET_ATTACK");
          stringList.Add("ITEM_BULLET_MANA");
          stringList.Add("ITEM_BULLET_ARROW");
          break;
        case 4:
          stringList.Add("IETC_QUEST");
          stringList.Add("IETC_EVENT");
          stringList.Add("IETC_SKILLUP");
          stringList.Add("IETC_UPGRADE");
          stringList.Add("IETC_MATERIAL");
          stringList.Add("IETC_MONEY");
          stringList.Add("IETC_PRODUCT");
          stringList.Add("IETC_PROCESS");
          stringList.Add("IETC_OPTION");
          stringList.Add("IETC_SAMPLE");
          stringList.Add("IETC_TEXTURE");
          stringList.Add("IETC_MIX_TYPE1");
          stringList.Add("IETC_MIX_TYPE2");
          stringList.Add("IETC_MIX_TYPE3");
          stringList.Add("IETC_PET_AI");
          stringList.Add("IETC_QUEST_TRIGGER");
          stringList.Add("IETC_JEWEL");
          stringList.Add("IETC_STABILIZER");
          stringList.Add("IETC_PROCESS_SCROLL");
          stringList.Add("IETC_MONSTER_MERCENARY_CARD");
          stringList.Add("IETC_GUILD_MARK");
          stringList.Add("IETC_REFORMER");
          stringList.Add("IETC_CHAOSJEWEL");
          stringList.Add("IETC_FUNCTIONS");
          break;
        case 5:
          stringList.Add("IACCESSORY_CHARM");
          stringList.Add("IACCESSORY_MAGICSTONE");
          stringList.Add("IACCESSORY_LIGHTSTONE");
          stringList.Add("IACCESSORY_EARING");
          stringList.Add("IACCESSORY_RING");
          stringList.Add("IACCESSORY_NECKLACE");
          stringList.Add("IACCESSORY_PET");
          stringList.Add("IACCESSORY_ATTACK_PET");
          break;
        case 6:
          stringList.Add("IPOTION_STATE");
          stringList.Add("IPOTION_HP");
          stringList.Add("IPOTION_MP");
          stringList.Add("IPOTION_DUAL");
          stringList.Add("IPOTION_STAT");
          stringList.Add("IPOTION_ETC");
          stringList.Add("IPOTION_UP");
          stringList.Add("IPOTION_TEARS");
          stringList.Add("IPOTION_CRYSTAL");
          stringList.Add("IPOTION_NPC_PORTAL");
          stringList.Add("IPOTION_HP_SPEEDUP");
          stringList.Add("IPOTION_MP_SPEEDUP");
          stringList.Add("IPOTION_PET_HP");
          stringList.Add("IPOTION_PET_SPEEDUP");
          break;
        default:
          stringList.Add("");
          break;
      }
      return stringList.ToArray();
    }
  }
}
