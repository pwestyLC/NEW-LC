// Decompiled with JetBrains decompiler
// Type: SMCEditor4.Smc
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;

#nullable disable
namespace SMCEditor4
{
  internal class Smc
  {
    public static List<string> Menu;
    public static string openedFile;
    public static List<tSmcRecords> SMCFile;

    public static void MakeList()
    {
      for (int index = 0; index < Smc.SMCFile.Count<tSmcRecords>(); ++index)
        Smc.Menu.Add(Smc.SMCFile[index].ID.ToString() + " - " + Items.GetNameFromID(Smc.SMCFile[index].ID));
    }

    public static bool ReadFile(string FileName)
    {
      Smc.openedFile = FileName;
      ASCIIEncoding asciiEncoding = new ASCIIEncoding();
      try
      {
        Smc.Menu = new List<string>();
        Smc.SMCFile = new List<tSmcRecords>();
        using (BinaryReader binaryReader = new BinaryReader((Stream) new MemoryStream(File.ReadAllBytes(FileName))))
        {
          binaryReader.ReadInt32();
          binaryReader.ReadInt32();
          binaryReader.ReadInt32();
          while (binaryReader.BaseStream.Position < binaryReader.BaseStream.Length)
          {
            int num1 = binaryReader.ReadInt32();
            if (num1 != 0)
            {
              tSmcRecords tSmcRecords = new tSmcRecords()
              {
                ID = num1 - 1,
                Name = asciiEncoding.GetString(binaryReader.ReadBytes((int) binaryReader.ReadInt16())),
                Models = new List<tModels>(),
                haveData = true
              };
              int num2 = binaryReader.ReadInt32();
              for (int index1 = 0; index1 < num2; ++index1)
              {
                tModels tModels = new tModels()
                {
                  ModelID = binaryReader.ReadInt32(),
                  ModelFile = asciiEncoding.GetString(binaryReader.ReadBytes((int) binaryReader.ReadInt16())),
                  Textures = new List<tTextures>()
                };
                int num3 = binaryReader.ReadInt32();
                for (int index2 = 0; index2 < num3; ++index2)
                {
                  tTextures tTextures = new tTextures()
                  {
                    TexID = index2 + 1,
                    TextureName = asciiEncoding.GetString(binaryReader.ReadBytes((int) binaryReader.ReadInt16())),
                    TextureFile = asciiEncoding.GetString(binaryReader.ReadBytes((int) binaryReader.ReadInt16()))
                  };
                  tModels.Textures.Add(tTextures);
                }
                tSmcRecords.Models.Add(tModels);
              }
              Smc.SMCFile.Add(tSmcRecords);
            }
          }
          binaryReader.Close();
        }
        return true;
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.ToString());
        return false;
      }
    }

    public static List<tSmcRecords> ReadFile2(string FileName)
    {
      List<tSmcRecords> tSmcRecordsList = new List<tSmcRecords>();
      ASCIIEncoding asciiEncoding = new ASCIIEncoding();
      using (BinaryReader binaryReader = new BinaryReader((Stream) File.Open(FileName, FileMode.Open)))
      {
        binaryReader.ReadInt32();
        binaryReader.ReadInt32();
        binaryReader.ReadInt32();
        while (binaryReader.BaseStream.Position < binaryReader.BaseStream.Length)
        {
          int num1 = binaryReader.ReadInt32();
          if (num1 != 0)
          {
            tSmcRecords tSmcRecords = new tSmcRecords()
            {
              ID = num1 - 1,
              Name = asciiEncoding.GetString(binaryReader.ReadBytes((int) binaryReader.ReadInt16())),
              Models = new List<tModels>(),
              haveData = true
            };
            int num2 = binaryReader.ReadInt32();
            for (int index1 = 0; index1 < num2; ++index1)
            {
              tModels tModels = new tModels()
              {
                ModelID = binaryReader.ReadInt32(),
                ModelFile = asciiEncoding.GetString(binaryReader.ReadBytes((int) binaryReader.ReadInt16())),
                Textures = new List<tTextures>()
              };
              int num3 = binaryReader.ReadInt32();
              for (int index2 = 0; index2 < num3; ++index2)
              {
                tTextures tTextures = new tTextures()
                {
                  TexID = index2 + 1,
                  TextureName = asciiEncoding.GetString(binaryReader.ReadBytes((int) binaryReader.ReadInt16())),
                  TextureFile = asciiEncoding.GetString(binaryReader.ReadBytes((int) binaryReader.ReadInt16()))
                };
                tModels.Textures.Add(tTextures);
              }
              tSmcRecords.Models.Add(tModels);
            }
            tSmcRecordsList.Add(tSmcRecords);
          }
        }
      }
      return tSmcRecordsList;
    }

    public static bool WriteFile(string FileName)
    {
      try
      {
        ASCIIEncoding asciiEncoding = new ASCIIEncoding();
        using (BinaryWriter binaryWriter = new BinaryWriter((Stream) File.Create(FileName)))
        {
          binaryWriter.Write(Smc.SMCFile.Max<tSmcRecords>((Func<tSmcRecords, int>) (p => p.ID)) + 1);
          binaryWriter.Write(0);
          binaryWriter.Write(0);
          for (int ItemID = Smc.SMCFile.Min<tSmcRecords>((Func<tSmcRecords, int>) (p => p.ID)); ItemID <= Smc.SMCFile.Max<tSmcRecords>((Func<tSmcRecords, int>) (p => p.ID)); ItemID++)
          {
            int index1 = Smc.SMCFile.FindIndex((Predicate<tSmcRecords>) (p => p.ID.Equals(ItemID)));
            if (index1 != -1)
            {
              tSmcRecords tSmcRecords = Smc.SMCFile[index1];
              binaryWriter.Write(tSmcRecords.ID + 1);
              binaryWriter.Write((short) asciiEncoding.GetBytes(tSmcRecords.Name).Length);
              binaryWriter.Write(asciiEncoding.GetBytes(tSmcRecords.Name));
              binaryWriter.Write(tSmcRecords.Models.Count<tModels>());
              for (int index2 = 0; index2 < tSmcRecords.Models.Count<tModels>(); ++index2)
              {
                tModels model = tSmcRecords.Models[index2];
                binaryWriter.Write(model.ModelID);
                binaryWriter.Write((short) asciiEncoding.GetBytes(model.ModelFile).Length);
                binaryWriter.Write(asciiEncoding.GetBytes(model.ModelFile));
                binaryWriter.Write(model.Textures.Count<tTextures>());
                for (int index3 = 0; index3 < model.Textures.Count<tTextures>(); ++index3)
                {
                  tTextures texture = model.Textures[index3];
                  binaryWriter.Write((short) asciiEncoding.GetBytes(texture.TextureName).Length);
                  binaryWriter.Write(asciiEncoding.GetBytes(texture.TextureName));
                  binaryWriter.Write((short) asciiEncoding.GetBytes(texture.TextureFile).Length);
                  binaryWriter.Write(asciiEncoding.GetBytes(texture.TextureFile));
                }
              }
            }
            else
              binaryWriter.Write(0);
          }
          binaryWriter.Close();
        }
        return true;
      }
      catch
      {
        return false;
      }
    }
  }
}
