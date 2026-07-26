// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.AssasinPL_Read_Need_Lod.Quest_Lod
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.AssasinPL_Read_Need_Lod
{
  public class Quest_Lod
  {
    public static List<Quest> QuestList = new List<Quest>();
    private static byte[] key;

    public static string GetNameFromID(int QuestID)
    {
      int index = Quest_Lod.QuestList.FindIndex((Predicate<Quest>) (p => p.QuestIndex.Equals(QuestID)));
      return index == -1 ? "None" : Quest_Lod.QuestList[index].QuestName;
    }

    public static string GetTooltipText(int QuestID)
    {
      string tooltipText = "";
      int index = Quest_Lod.QuestList.FindIndex((Predicate<Quest>) (p => p.QuestIndex.Equals(QuestID)));
      if (index != -1)
        tooltipText = Quest_Lod.QuestList[index].QuestName.ToString() + "\r\n\r\n" + Quest_Lod.QuestList[index].QuestNPCStory?.ToString() + "\r\n\r\n" + Quest_Lod.QuestList[index].QuestCompleteResponse?.ToString() + "\r\n\r\n" + Quest_Lod.QuestList[index].QuestInfo?.ToString();
      return tooltipText;
    }

    public static bool LoadFromFile(string FileName)
    {
      ASCIIEncoding asciiEncoding = new ASCIIEncoding();
      try
      {
        using (BinaryReader binaryReader = new BinaryReader((Stream) File.Open(FileName, FileMode.Open)))
        {
          binaryReader.ReadInt32();
          while (binaryReader.BaseStream.Position < binaryReader.BaseStream.Length)
          {
            Quest quest = new Quest();
            quest.QuestIndex = binaryReader.ReadInt32();
            quest.Type1 = binaryReader.ReadInt32();
            quest.Type2 = binaryReader.ReadInt32();
            quest.StartType = binaryReader.ReadInt32();
            quest.StartNpc = binaryReader.ReadInt32();
            quest.PrizeNpc = binaryReader.ReadInt32();
            quest.PrequestNum = binaryReader.ReadInt32();
            quest.StartNpcZoneNum = binaryReader.ReadInt32();
            quest.PrizeNpcZoneNum = binaryReader.ReadInt32();
            quest.NeedExp = binaryReader.ReadInt32();
            quest.NeedMinLevel = binaryReader.ReadInt32();
            quest.NeedMaxLevel = binaryReader.ReadInt32();
            quest.NeedJob = binaryReader.ReadInt32();
            quest.NeedMinPinalty = binaryReader.ReadInt32();
            quest.NeedMaxPinalty = binaryReader.ReadInt32();
            int[] numArray1 = new int[5];
            int[] numArray2 = new int[5];
            for (int index = 0; index < 5; ++index)
            {
              numArray1[index] = binaryReader.ReadInt32();
              numArray2[index] = binaryReader.ReadInt32();
            }
            quest.NeedItemsIdx = numArray1;
            quest.NeedItemsCount = numArray2;
            quest.NeedRvRType = binaryReader.ReadInt32();
            quest.NeedRvrGrade = binaryReader.ReadInt32();
            int[] numArray3 = new int[3];
            int[] numArray4 = new int[3];
            int[] numArray5 = new int[3];
            for (int index = 0; index < 3; ++index)
            {
              numArray3[index] = binaryReader.ReadInt32();
              numArray4[index] = binaryReader.ReadInt32();
              numArray5[index] = binaryReader.ReadInt32();
            }
            quest.ConditionType = numArray3;
            quest.ConditionIndex = numArray4;
            quest.ConditionNum = numArray5;
            int[] numArray6 = new int[4];
            int[] numArray7 = new int[4];
            int[] numArray8 = new int[4];
            for (int index = 0; index < 4; ++index)
            {
              numArray6[index] = binaryReader.ReadInt32();
              numArray7[index] = binaryReader.ReadInt32();
              numArray8[index] = binaryReader.ReadInt32();
            }
            quest.ConditionData0 = numArray6;
            quest.ConditionData1 = numArray7;
            quest.ConditionData2 = numArray8;
            int[] numArray9 = new int[5];
            int[] numArray10 = new int[5];
            for (int index = 0; index < 5; ++index)
            {
              numArray9[index] = binaryReader.ReadInt32();
              numArray10[index] = binaryReader.ReadInt32();
            }
            quest.PrizeType = numArray9;
            quest.PrizeIndex = numArray10;
            long[] numArray11 = new long[5];
            for (long index = 0; index < 5L; ++index)
              numArray11[index] = binaryReader.ReadInt64();
            quest.PrizeData = numArray11;
            quest.OptionPrize = binaryReader.ReadInt32();
            int[] numArray12 = new int[7];
            int[] numArray13 = new int[7];
            int[] numArray14 = new int[7];
            int[] numArray15 = new int[7];
            for (int index = 0; index < 7; ++index)
            {
              numArray12[index] = binaryReader.ReadInt32();
              numArray13[index] = binaryReader.ReadInt32();
              numArray14[index] = binaryReader.ReadInt32();
              numArray15[index] = binaryReader.ReadInt32();
            }
            quest.OptionPrizeType = numArray12;
            quest.OptionPrizeIndex = numArray13;
            quest.OptionPrizeData = numArray14;
            quest.OptionPrizePlus = numArray15;
            quest.PartyScale = binaryReader.ReadInt32();
            quest.OnlyOptionPrize = binaryReader.ReadInt32();
            Quest_Lod.QuestList.Add(quest);
            if (binaryReader.BaseStream.Length - binaryReader.BaseStream.Position == 8L)
              Quest_Lod.key = binaryReader.ReadBytes(8);
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
            int index = Quest_Lod.QuestList.FindIndex((Predicate<Quest>) (p => p.QuestIndex.Equals(ID)));
            string str1 = Encoding.GetEncoding("Windows-874").GetString(binaryReader.ReadBytes(binaryReader.ReadInt32()));
            string str2 = Encoding.GetEncoding("Windows-874").GetString(binaryReader.ReadBytes(binaryReader.ReadInt32()));
            string str3 = Encoding.GetEncoding("Windows-874").GetString(binaryReader.ReadBytes(binaryReader.ReadInt32()));
            string str4 = Encoding.GetEncoding("Windows-874").GetString(binaryReader.ReadBytes(binaryReader.ReadInt32()));
            if (index != -1)
            {
              Quest_Lod.QuestList[index].QuestName = str1;
              Quest_Lod.QuestList[index].QuestNPCStory = str2;
              Quest_Lod.QuestList[index].QuestCompleteResponse = str3;
              Quest_Lod.QuestList[index].QuestInfo = str4;
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
