// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.AssasinPL_Read_Need_Lod.Skill_Lod
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
  public class Skill_Lod
  {
    public static List<SkillsLod> SkillList = new List<SkillsLod>();

    public static bool LoadFromFile(string FileName)
    {
      Encoding encoding = Encoding.GetEncoding("windows-1251");
      try
      {
        using (BinaryReader binaryReader = new BinaryReader((Stream) File.Open(FileName, FileMode.Open)))
        {
          binaryReader.ReadInt32();
          while (binaryReader.BaseStream.Position < binaryReader.BaseStream.Length - 8L)
          {
            SkillsLod skillsLod = new SkillsLod();
            skillsLod.SkillIndex = binaryReader.ReadInt32();
            skillsLod.Job = binaryReader.ReadInt32();
            skillsLod.Job2 = binaryReader.ReadInt32();
            skillsLod.PetIndex = binaryReader.ReadInt32();
            skillsLod.Type = binaryReader.ReadByte();
            skillsLod.Flag = binaryReader.ReadInt64();
            skillsLod.SorcererFlag = binaryReader.ReadInt32();
            skillsLod.MaxLevel = binaryReader.ReadByte();
            skillsLod.AppRange = binaryReader.ReadSingle();
            skillsLod.FireRange = binaryReader.ReadSingle();
            skillsLod.FireRange2 = binaryReader.ReadSingle();
            skillsLod.TargetType = binaryReader.ReadByte();
            skillsLod.UseState = binaryReader.ReadInt32();
            skillsLod.UseWeaponType0 = binaryReader.ReadInt32();
            skillsLod.UseWeaponType1 = binaryReader.ReadInt32();
            skillsLod.UseMagicIndex1 = binaryReader.ReadInt32();
            skillsLod.UseMagicLevel1 = binaryReader.ReadByte();
            skillsLod.UseMagicIndex2 = binaryReader.ReadInt32();
            skillsLod.UseMagicLevel2 = binaryReader.ReadByte();
            skillsLod.UseMagicIndex3 = binaryReader.ReadInt32();
            skillsLod.UseMagicLevel3 = binaryReader.ReadByte();
            skillsLod.SoulConsum = binaryReader.ReadInt32();
            skillsLod.AppState = binaryReader.ReadInt32();
            skillsLod.ReadyTime = binaryReader.ReadInt32();
            skillsLod.StillTime = binaryReader.ReadInt32();
            skillsLod.FireTime = binaryReader.ReadInt32();
            skillsLod.ReuseTime = binaryReader.ReadInt32();
            skillsLod.A_ReadyAnimation = encoding.GetString(binaryReader.ReadBytes((int) binaryReader.ReadByte()));
            skillsLod.A_ReadyEffect = encoding.GetString(binaryReader.ReadBytes((int) binaryReader.ReadByte()));
            skillsLod.A_StillAnimation = encoding.GetString(binaryReader.ReadBytes((int) binaryReader.ReadByte()));
            skillsLod.A_FireAnimation = encoding.GetString(binaryReader.ReadBytes((int) binaryReader.ReadByte()));
            skillsLod.A_FireEffect1 = encoding.GetString(binaryReader.ReadBytes((int) binaryReader.ReadByte()));
            skillsLod.A_FireEffect2 = encoding.GetString(binaryReader.ReadBytes((int) binaryReader.ReadByte()));
            skillsLod.A_FireEffect3 = encoding.GetString(binaryReader.ReadBytes((int) binaryReader.ReadByte()));
            skillsLod.A_FireObjectType = binaryReader.ReadByte();
            skillsLod.A_FireObjectSpeed = binaryReader.ReadSingle();
            skillsLod.A_FireObjectX = binaryReader.ReadSingle();
            skillsLod.A_FireObjectZ = binaryReader.ReadSingle();
            skillsLod.A_FireObjectH = binaryReader.ReadSingle();
            skillsLod.A_FireObjectCoord = binaryReader.ReadByte();
            skillsLod.A_FireObjectDelayCount = binaryReader.ReadByte();
            skillsLod.A_FireObjectDelay0 = binaryReader.ReadSingle();
            skillsLod.A_FireObjectDelay1 = binaryReader.ReadSingle();
            skillsLod.A_FireObjectDelay2 = binaryReader.ReadSingle();
            skillsLod.A_FireObjectDelay3 = binaryReader.ReadSingle();
            skillsLod.A_FireDestAnimation = binaryReader.ReadSingle();
            skillsLod.B_ReadyAnimation = encoding.GetString(binaryReader.ReadBytes((int) binaryReader.ReadByte()));
            skillsLod.B_ReadyEffect = encoding.GetString(binaryReader.ReadBytes((int) binaryReader.ReadByte()));
            skillsLod.B_StillAnimation = encoding.GetString(binaryReader.ReadBytes((int) binaryReader.ReadByte()));
            skillsLod.B_FireAnimation = encoding.GetString(binaryReader.ReadBytes((int) binaryReader.ReadByte()));
            skillsLod.B_FireEffect1 = encoding.GetString(binaryReader.ReadBytes((int) binaryReader.ReadByte()));
            skillsLod.B_FireEffect2 = encoding.GetString(binaryReader.ReadBytes((int) binaryReader.ReadByte()));
            skillsLod.B_FireEffect3 = encoding.GetString(binaryReader.ReadBytes((int) binaryReader.ReadByte()));
            skillsLod.B_FireObjectType = binaryReader.ReadByte();
            skillsLod.B_FireObjectSpeed = binaryReader.ReadSingle();
            skillsLod.B_FireObjectX = binaryReader.ReadSingle();
            skillsLod.B_FireObjectZ = binaryReader.ReadSingle();
            skillsLod.B_FireObjectH = binaryReader.ReadSingle();
            skillsLod.B_FireObjectCoord = binaryReader.ReadByte();
            skillsLod.B_FireObjectDelayCount = binaryReader.ReadByte();
            skillsLod.B_FireObjectDelay0 = binaryReader.ReadSingle();
            skillsLod.B_FireObjectDelay1 = binaryReader.ReadSingle();
            skillsLod.B_FireObjectDelay2 = binaryReader.ReadSingle();
            skillsLod.B_FireObjectDelay3 = binaryReader.ReadSingle();
            skillsLod.B_FireDestAnimation = binaryReader.ReadSingle();
            skillsLod.ExtraEffect = encoding.GetString(binaryReader.ReadBytes((int) binaryReader.ReadByte()));
            skillsLod.IconId = binaryReader.ReadInt32();
            skillsLod.IconRow = binaryReader.ReadInt32();
            skillsLod.IconCol = binaryReader.ReadInt32();
            List<SkillLevel> skillLevelList = new List<SkillLevel>();
            for (int index = 0; index < (int) skillsLod.MaxLevel; ++index)
              skillLevelList.Add(new SkillLevel()
              {
                NeedHP = binaryReader.ReadInt32(),
                NeedMP = binaryReader.ReadInt32(),
                NeedGP = binaryReader.ReadInt32(),
                DurationTime = binaryReader.ReadInt32(),
                DummyPower = binaryReader.ReadInt32(),
                NeedItemIndex1 = binaryReader.ReadInt32(),
                NeedItemCount1 = binaryReader.ReadInt32(),
                NeedItemIndex2 = binaryReader.ReadInt32(),
                NeedItemCount2 = binaryReader.ReadInt32(),
                LearnLevel = binaryReader.ReadInt32(),
                LearnSP = binaryReader.ReadInt32(),
                LearnSkillIndex1 = binaryReader.ReadInt32(),
                LearnSkillLevel1 = binaryReader.ReadByte(),
                LearnSkillIndex2 = binaryReader.ReadInt32(),
                LearnSkillLevel2 = binaryReader.ReadByte(),
                LearnSkillIndex3 = binaryReader.ReadInt32(),
                LearnSkillLevel3 = binaryReader.ReadByte(),
                LearnItemIndex1 = binaryReader.ReadInt32(),
                LearnItemCount1 = binaryReader.ReadInt32(),
                LearnItemIndex2 = binaryReader.ReadInt32(),
                LearnItemCount2 = binaryReader.ReadInt32(),
                LearnItemIndex3 = binaryReader.ReadInt32(),
                LearnItemCount3 = binaryReader.ReadInt32(),
                LearnSTR = binaryReader.ReadInt32(),
                LearnDEX = binaryReader.ReadInt32(),
                LearnINT = binaryReader.ReadInt32(),
                LearnCON = binaryReader.ReadInt32(),
                AppMagicIndex1 = binaryReader.ReadInt32(),
                AppMagicLevel1 = binaryReader.ReadByte(),
                AppMagicIndex2 = binaryReader.ReadInt32(),
                AppMagicLevel2 = binaryReader.ReadByte(),
                AppMagicIndex3 = binaryReader.ReadInt32(),
                AppMagicLevel3 = binaryReader.ReadByte(),
                MagicIndex1 = binaryReader.ReadInt32(),
                MagicLevel1 = binaryReader.ReadByte(),
                MagicIndex2 = binaryReader.ReadInt32(),
                MagicLevel2 = binaryReader.ReadByte(),
                MagicIndex3 = binaryReader.ReadInt32(),
                MagicLevel3 = binaryReader.ReadByte(),
                LearnGP = binaryReader.ReadInt32(),
                AttackSubType = binaryReader.ReadByte(),
                AttackPower = binaryReader.ReadByte(),
                DefenceSubType = binaryReader.ReadByte(),
                DefencePower = binaryReader.ReadByte(),
                TargetNum = binaryReader.ReadInt32()
              });
            skillsLod.SkillLevels = skillLevelList.ToArray();
            Skill_Lod.SkillList.Add(skillsLod);
          }
          return true;
        }
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
            int index = Skill_Lod.SkillList.FindIndex((Predicate<SkillsLod>) (p => p.SkillIndex.Equals(ID)));
            string str1 = Encoding.GetEncoding("Windows-874").GetString(binaryReader.ReadBytes(binaryReader.ReadInt32()));
            string str2 = Encoding.GetEncoding("Windows-874").GetString(binaryReader.ReadBytes(binaryReader.ReadInt32()));
            string str3 = Encoding.GetEncoding("Windows-874").GetString(binaryReader.ReadBytes(binaryReader.ReadInt32()));
            if (index != -1)
            {
              Skill_Lod.SkillList[index].SkillName = str1;
              Skill_Lod.SkillList[index].SkillDesc1 = str2;
              Skill_Lod.SkillList[index].SkillDesc2 = str3;
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
