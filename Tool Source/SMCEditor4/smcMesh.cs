// Decompiled with JetBrains decompiler
// Type: SMCEditor3.smcMesh
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System.Collections.Generic;

#nullable disable
namespace SMCEditor3
{
  internal struct smcMesh(string FileName, string MeshName)
  {
    public string FileName = FileName;
    public List<smcObject> Object = new List<smcObject>();
    public string meshname = MeshName;
  }
}
