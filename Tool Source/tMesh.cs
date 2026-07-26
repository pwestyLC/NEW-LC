// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.tMesh
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using SlimDX.Direct3D9;

#nullable disable
namespace LcDevPack_TeamDamonA
{
  public class tMesh
  {
    public Mesh MeshData;
    public Texture TexData;

    public tMesh(Mesh mesh, Texture texture)
    {
      this.MeshData = mesh;
      this.TexData = texture;
    }
  }
}
