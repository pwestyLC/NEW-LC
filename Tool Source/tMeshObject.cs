// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.tMeshObject
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System.Collections.Generic;
using System.Linq;

#nullable disable
namespace LcDevPack_TeamDamonA
{
  public class tMeshObject
  {
    public uint FaceCount { get; set; }

    public tFace[] Faces { get; set; }

    public uint FromVert { get; set; }

    public byte[] JData { get; set; }

    public uint JValue { get; set; }

    public byte[] MaterialName { get; set; }

    public tMeshShaderData ShaderData { get; set; }

    public uint ShaderFlag { get; set; }

    public tMeshShaderInfo ShaderInfo { get; set; }

    public tMeshTexture[] Textures { get; set; }

    public uint ToVert { get; set; }

    public uint Value1 { get; set; }

    public short[] GetFaces()
    {
      List<short> shortList = new List<short>();
      for (int index = 0; index < ((IEnumerable<tFace>) this.Faces).Count<tFace>(); ++index)
      {
        shortList.Add(this.Faces[index].A);
        shortList.Add(this.Faces[index].B);
        shortList.Add(this.Faces[index].C);
      }
      return shortList.ToArray();
    }
  }
}
