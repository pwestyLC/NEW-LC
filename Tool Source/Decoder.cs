// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Decoder
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System;

#nullable disable
namespace LcDevPack_TeamDamonA
{
  public class Decoder
  {
    private static byte[] XorCode;

    public static uint Decode(uint Code)
    {
      byte[] numArray = new byte[4];
      byte[] bytes = BitConverter.GetBytes(Code);
      for (int index = 0; index < 4; ++index)
      {
        bytes[index] = (byte) ((uint) bytes[index] ^ (uint) Decoder.XorCode[index]);
        Decoder.XorCode[index] = (byte) ((uint) Decoder.XorCode[index] + 89U);
      }
      return BitConverter.ToUInt32(bytes, 0);
    }

    public static void Reset()
    {
      Decoder.XorCode = new byte[4]
      {
        (byte) 101,
        (byte) 72,
        (byte) 53,
        (byte) 30
      };
    }
  }
}
