// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.pwObject
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

#nullable disable
namespace LcDevPack_TeamDamonA
{
  public class pwObject
  {
    public pwBoneIndex[] BoneIndex { get; set; }

    public byte[] ExtraData { get; set; }

    public pwFaces[] Faces { get; set; }

    public int FaceVertsCount { get; set; }

    public int MaterialIndex { get; set; }

    public byte[] MeshName { get; set; }

    public pwNormal[] Normals { get; set; }

    public int TextureIndex { get; set; }

    public pwUV[] UVs { get; set; }

    public int VertexCount { get; set; }

    public pwVertexWeight[] VertexWeight { get; set; }

    public pwVertex[] Vertices { get; set; }
  }
}
