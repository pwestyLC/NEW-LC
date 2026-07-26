// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.PetEditor.Open_Lod
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using LcDevPack_TeamDamonA.Tools.MemoryWorker.Item;
using System.Collections.Generic;
using System.IO;
using System.Text;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.PetEditor
{
  public class Open_Lod
  {
    public string _ClientPath = LcDevPack_TeamDamonA.Tools.MobEditor.connection.Settings.ClientPath;
    public static List<ItemContainer> ItemList = new List<ItemContainer>();

    internal static void ReadItem(string itemsource)
    {
      using (BinaryReader binaryReader = new BinaryReader((Stream) File.Open(itemsource, FileMode.Open)))
      {
        binaryReader.ReadInt32();
        while (binaryReader.BaseStream.Position < binaryReader.BaseStream.Length)
        {
          if (binaryReader.BaseStream.Length - 25L > binaryReader.BaseStream.Position)
          {
            ItemContainer itemContainer = new ItemContainer();
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
            itemContainer.Smc = Encoding.GetEncoding("ISO-8859-1").GetString(binaryReader.ReadBytes(64));
            itemContainer.Effect1 = Encoding.GetEncoding("ISO-8859-1").GetString(binaryReader.ReadBytes(32));
            itemContainer.Effect2 = Encoding.GetEncoding("ISO-8859-1").GetString(binaryReader.ReadBytes(32));
            itemContainer.Effect3 = Encoding.GetEncoding("ISO-8859-1").GetString(binaryReader.ReadBytes(32));
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
            Open_Lod.ItemList.Add(itemContainer);
          }
          else
            binaryReader.BaseStream.Position = binaryReader.BaseStream.Length;
        }
      }
    }
  }
}
