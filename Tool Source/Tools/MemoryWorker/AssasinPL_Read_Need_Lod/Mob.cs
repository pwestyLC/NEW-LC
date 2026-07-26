// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.AssasinPL_Read_Need_Lod.Mob_Lod
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
  public class Mob_Lod
  {
    public static List<Mob> MobList = new List<Mob>();
    private static byte[] key;
    public static List<string> Menu = new List<string>();
    public static List<string> MenuList = new List<string>();

    public static string GetNameFromID(int MobID)
    {
      int index = Mob_Lod.MobList.FindIndex((Predicate<Mob>) (p => p.NpcID.Equals(MobID)));
      return index == -1 ? "None" : Mob_Lod.MobList[index].NpcName;
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
            Mob mob = new Mob();
            mob.NpcID = binaryReader.ReadInt32();
            mob.Level = binaryReader.ReadInt32();
            mob.HP = binaryReader.ReadInt32();
            mob.MP = binaryReader.ReadInt32();
            mob.Flag = binaryReader.ReadInt32();
            mob.Flag1 = binaryReader.ReadInt32();
            mob.AttackSpeed = binaryReader.ReadInt32();
            mob.WalkSpeed = binaryReader.ReadSingle();
            mob.RunSpeed = binaryReader.ReadSingle();
            mob.Scale = binaryReader.ReadSingle();
            mob.AttackArea = binaryReader.ReadSingle();
            mob.Size = binaryReader.ReadSingle();
            mob.SkillMaster = binaryReader.ReadInt16();
            int[] numArray = new int[5];
            for (int index = 0; index < 5; ++index)
              numArray[index] = binaryReader.ReadInt32();
            mob.SkillEffects = numArray;
            mob.AttackType = binaryReader.ReadByte();
            mob.DelayCount = binaryReader.ReadByte();
            mob.Delay0 = binaryReader.ReadSingle();
            mob.Delay1 = binaryReader.ReadSingle();
            mob.Delay2 = binaryReader.ReadSingle();
            mob.Delay3 = binaryReader.ReadSingle();
            mob.FireObject = binaryReader.ReadByte();
            mob.FireSpeed = binaryReader.ReadSingle();
            mob.SkillId1 = binaryReader.ReadInt32();
            mob.SkillLevel1 = binaryReader.ReadByte();
            mob.SkillId2 = binaryReader.ReadInt32();
            mob.SkillLevel2 = binaryReader.ReadByte();
            mob.RvRValue = binaryReader.ReadInt32();
            mob.RvRGrade = binaryReader.ReadInt32();
            mob.Bound = binaryReader.ReadInt32();
            mob.SMC = Encoding.GetEncoding("Windows-874").GetString(binaryReader.ReadBytes(128));
            mob.Idle = Encoding.GetEncoding("Windows-874").GetString(binaryReader.ReadBytes(64));
            mob.Walk = Encoding.GetEncoding("Windows-874").GetString(binaryReader.ReadBytes(64));
            mob.Damage = Encoding.GetEncoding("Windows-874").GetString(binaryReader.ReadBytes(64));
            mob.Attack = Encoding.GetEncoding("Windows-874").GetString(binaryReader.ReadBytes(64));
            mob.Die = Encoding.GetEncoding("Windows-874").GetString(binaryReader.ReadBytes(64));
            mob.Run = Encoding.GetEncoding("Windows-874").GetString(binaryReader.ReadBytes(64));
            mob.Idle2 = Encoding.GetEncoding("Windows-874").GetString(binaryReader.ReadBytes(64));
            mob.Attack2 = Encoding.GetEncoding("Windows-874").GetString(binaryReader.ReadBytes(64));
            mob.FireEffect0 = Encoding.GetEncoding("Windows-874").GetString(binaryReader.ReadBytes(64));
            mob.FireEffect1 = Encoding.GetEncoding("Windows-874").GetString(binaryReader.ReadBytes(64));
            mob.FireEffect2 = Encoding.GetEncoding("Windows-874").GetString(binaryReader.ReadBytes(64));
            Mob_Lod.MobList.Add(mob);
            if (binaryReader.BaseStream.Length - binaryReader.BaseStream.Position == 8L)
              Mob_Lod.key = binaryReader.ReadBytes(8);
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
            int index = Mob_Lod.MobList.FindIndex((Predicate<Mob>) (p => p.NpcID.Equals(ID)));
            string str1 = Encoding.GetEncoding("Windows-874").GetString(binaryReader.ReadBytes(binaryReader.ReadInt32()));
            string str2 = Encoding.GetEncoding("Windows-874").GetString(binaryReader.ReadBytes(binaryReader.ReadInt32()));
            if (index != -1)
            {
              Mob_Lod.MobList[index].NpcName = str1;
              Mob_Lod.MobList[index].NpcDesc = str2;
              Mob_Lod.Menu.Add(index.ToString() + " " + str1);
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
