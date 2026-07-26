// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.Catalog_Editor.strItem
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System;
using System.Collections.Generic;
using System.IO;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.Catalog_Editor
{
  internal class strItem
  {
    public static List<strItem.t_strItem> ItemList = new List<strItem.t_strItem>();
    public static List<string> Menu_STRITEM = new List<string>();
    public static int Version = 2012;
    private static byte[] key;
    public static int Total;
    private static int LastID;

    public static string GetNameFromID(int unk0)
    {
      int index = strItem.ItemList.FindIndex((Predicate<strItem.t_strItem>) (p => p.QuestID.Equals(unk0)));
      return index == -1 ? "None" : (strItem.ItemList[index].QuestName != "" ? strItem.ItemList[index].QuestName : strItem.ItemList[index].QuestName);
    }

    public static string GetDescrFromID(int unk0)
    {
      int index = strItem.ItemList.FindIndex((Predicate<strItem.t_strItem>) (p => p.QuestID.Equals(unk0)));
      return index == -1 ? "None" : (strItem.ItemList[index].Descr_1 != "" ? strItem.ItemList[index].Descr_1 : strItem.ItemList[index].Descr_1);
    }

    public static void SendEdit(int unk0, string unk1)
    {
      int index = strItem.ItemList.FindIndex((Predicate<strItem.t_strItem>) (p => p.QuestID.Equals(unk0)));
      if (index == -1)
        return;
      strItem.ItemList[index].QuestName = unk1;
    }

    public static void Add(int unk0)
    {
      if (strItem.ItemList.FindIndex((Predicate<strItem.t_strItem>) (p => p.QuestID.Equals(unk0))) != -1)
        return;
      strItem.t_strItem tStrItem = new strItem.t_strItem();
      tStrItem.QuestID = unk0;
      tStrItem.QuestName = "";
      tStrItem.Descr_1 = "";
      strItem.ItemList.Add(tStrItem);
      strItem.Menu_STRITEM.Add(tStrItem.QuestID.ToString() + " - " + tStrItem.QuestName);
      ++strItem.LastID;
      ++strItem.Total;
    }

    public static bool LoadFromFile(string FileName)
    {
      try
      {
        strItem.Total = 0;
        strItem.LastID = 0;
        using (BinaryReader binaryReader = new BinaryReader((Stream) File.Open(FileName, FileMode.Open)))
        {
          binaryReader.ReadInt32();
          binaryReader.ReadInt32();
          while (binaryReader.BaseStream.Position < binaryReader.BaseStream.Length)
          {
            strItem.t_strItem tStrItem = new strItem.t_strItem();
            tStrItem.QuestID = binaryReader.ReadInt32();
            tStrItem.QuestName = Form2.encoding.GetString(binaryReader.ReadBytes(binaryReader.ReadInt32()));
            tStrItem.Descr_1 = Form2.encoding.GetString(binaryReader.ReadBytes(binaryReader.ReadInt32()));
            strItem.ItemList.Add(tStrItem);
            ++strItem.Total;
            strItem.LastID = tStrItem.QuestID;
            strItem.Menu_STRITEM.Add(tStrItem.QuestID.ToString() + " - " + tStrItem.QuestName);
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

    public static bool SaveFile(string FileName)
    {
      try
      {
        BinaryWriter binaryWriter = new BinaryWriter((Stream) File.Create(FileName));
        binaryWriter.Write(strItem.Total);
        binaryWriter.Write(strItem.LastID);
        for (int index = 0; index < strItem.Total; ++index)
        {
          binaryWriter.Write(strItem.ItemList[index].QuestID);
          binaryWriter.Write(Form2.encoding.GetBytes(strItem.ItemList[index].QuestName).Length);
          binaryWriter.Write(Form2.encoding.GetBytes(strItem.ItemList[index].QuestName));
          binaryWriter.Write(Form2.encoding.GetBytes(strItem.ItemList[index].Descr_1).Length);
          binaryWriter.Write(Form2.encoding.GetBytes(strItem.ItemList[index].Descr_1));
        }
        binaryWriter.Close();
        return true;
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.ToString());
        return false;
      }
    }

    public class t_strItem
    {
      public int QuestID;
      public string QuestName;
      public string Descr_1;

      public object Clone() => this.MemberwiseClone();
    }
  }
}
