// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.AssasinPL_Read_Need_Lod.Client_Lod
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
  public class Client_Lod
  {
    public static List<Client> ClientList = new List<Client>();
    private static byte[] key;

    public static string GetNameFromID(int StringID)
    {
      int index = Client_Lod.ClientList.FindIndex((Predicate<Client>) (p => p.ClientID.Equals(StringID)));
      return index == -1 ? "None" : Client_Lod.ClientList[index].ClientName;
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
            Client_Lod.ClientList.Add(new Client()
            {
              ClientID = binaryReader.ReadInt32(),
              ClientName = Encoding.GetEncoding("Windows-874").GetString(binaryReader.ReadBytes(binaryReader.ReadInt32()))
            });
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
