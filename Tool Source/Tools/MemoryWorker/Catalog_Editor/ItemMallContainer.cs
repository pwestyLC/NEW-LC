// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.Catalog_Editor.ItemMallContainer
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System.Collections.Generic;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.Catalog_Editor
{
  public class ItemMallContainer
  {
    public int Cat { get; set; }

    public int data4 { get; set; }

    public int data5 { get; set; }

    public byte[] descr { get; set; }

    public byte Enabled { get; set; }

    public int ItemIcon { get; set; }

    public List<tMallItem> Items { get; set; }

    public byte[] Name { get; set; }

    public int PackID { get; set; }

    public int PkgAmount { get; set; }

    public int Price { get; set; }
  }
}
