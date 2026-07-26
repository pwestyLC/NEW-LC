// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.LCMeshReader
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System.IO;
using System.Text;

#nullable disable
namespace LcDevPack_TeamDamonA
{
  public class LCMeshReader
  {
    private static ASCIIEncoding Enc = new ASCIIEncoding();
    public static string OpenedFile = "";
    public static tMeshContainer pMesh;

    // Helper to safely read length-prefixed byte[] from file and avoid negative/invalid lengths
    private static byte[] ReadBytesSafe(BinaryReader b)
    {
      try
      {
        int len = b.ReadInt32();
        long remaining = b.BaseStream.Length - b.BaseStream.Position;
        if (len < 0 || len > remaining) return new byte[0];
        return b.ReadBytes(len);
      }
      catch
      {
        return new byte[0];
      }
    }

    public static bool ReadFile(string FileName)
    {
      LCMeshReader.OpenedFile = FileName;
      LCMeshReader.pMesh = new tMeshContainer();
      BinaryReader b = new BinaryReader((Stream) new FileStream(FileName, FileMode.Open, FileAccess.Read, FileShare.Read));
      LCMeshReader.pMesh.HeaderInfo = new tHeaderInfo();
      LCMeshReader.pMesh.HeaderInfo.Format = b.ReadBytes(4);
      LCMeshReader.pMesh.HeaderInfo.Version = b.ReadInt32();
      LCMeshReader.pMesh.HeaderInfo.MeshDataSize = b.ReadInt32();
      LCMeshReader.pMesh.HeaderInfo.MeshCount = b.ReadUInt32();
      LCMeshReader.pMesh.HeaderInfo.VertexCount = b.ReadUInt32();
      LCMeshReader.pMesh.HeaderInfo.JointCount = b.ReadUInt32();
      LCMeshReader.pMesh.HeaderInfo.TextureMaps = b.ReadUInt32();
      LCMeshReader.pMesh.HeaderInfo.NormalCount = b.ReadUInt32();
      LCMeshReader.pMesh.HeaderInfo.ObjCount = b.ReadUInt32();
      LCMeshReader.pMesh.HeaderInfo.UnknownCount = b.ReadUInt32();
      // safe read for filename
      LCMeshReader.pMesh.FileName = ReadBytesSafe(b);
      LCMeshReader.pMesh.Scale = b.ReadSingle();
      LCMeshReader.pMesh.Value1 = b.ReadUInt32();
      LCMeshReader.pMesh.FilePath = FileName;
      bool flag = false;
      if (LCMeshReader.pMesh.HeaderInfo.Version == 16)
      {
        if (LCMeshReader.ReadV10(b, b.BaseStream.Position))
          flag = true;
      }
      else if (LCMeshReader.pMesh.HeaderInfo.Version == 17 && LCMeshReader.ReadV11(b, b.BaseStream.Position))
        flag = true;
      b.Close();
      return flag;
    }

    private static bool ReadV10(BinaryReader b, long Pos)
    {
      tHeaderInfo tHeaderInfo = new tHeaderInfo();
      tHeaderInfo headerInfo = LCMeshReader.pMesh.HeaderInfo;
      headerInfo.NormalCount = LCMeshReader.pMesh.HeaderInfo.UnknownCount;
      headerInfo.JointCount = LCMeshReader.pMesh.HeaderInfo.NormalCount;
      headerInfo.UnknownCount = LCMeshReader.pMesh.HeaderInfo.TextureMaps;
      headerInfo.ObjCount = LCMeshReader.pMesh.HeaderInfo.ObjCount;
      headerInfo.TextureMaps = LCMeshReader.pMesh.HeaderInfo.JointCount;
      LCMeshReader.pMesh.HeaderInfo = headerInfo;
      LCMeshReader.pMesh.Vertices = new tVertex3f[(int) LCMeshReader.pMesh.HeaderInfo.VertexCount];
      for (int index = 0; (long) index < (long) LCMeshReader.pMesh.HeaderInfo.VertexCount; ++index)
        LCMeshReader.pMesh.Vertices[index] = new tVertex3f(b.ReadSingle(), b.ReadSingle(), b.ReadSingle());
      LCMeshReader.pMesh.Normals = new tVertex3f[(int) LCMeshReader.pMesh.HeaderInfo.VertexCount];
      for (int index = 0; (long) index < (long) LCMeshReader.pMesh.HeaderInfo.VertexCount; ++index)
        LCMeshReader.pMesh.Normals[index] = new tVertex3f(b.ReadSingle(), b.ReadSingle(), b.ReadSingle());
      if (LCMeshReader.pMesh.HeaderInfo.TextureMaps > 0U)
      {
        LCMeshReader.pMesh.UVMaps = new tMeshUVMap[(int) LCMeshReader.pMesh.HeaderInfo.TextureMaps];
        // fixed loop comparison (decompiler introduced wrong '>');
        for (int index1 = 0; (long) index1 < (long) LCMeshReader.pMesh.HeaderInfo.TextureMaps; ++index1)
        {
          LCMeshReader.pMesh.UVMaps[index1] = new tMeshUVMap();
          LCMeshReader.pMesh.UVMaps[index1].Name = ReadBytesSafe(b);
          LCMeshReader.pMesh.UVMaps[index1].Coords = new tTextCoord[(int) LCMeshReader.pMesh.HeaderInfo.VertexCount];
          for (int index2 = 0; (long) index2 < (long) LCMeshReader.pMesh.HeaderInfo.VertexCount; ++index2)
            LCMeshReader.pMesh.UVMaps[index1].Coords[index2] = new tTextCoord(b.ReadSingle(), b.ReadSingle());
        }
      }
      LCMeshReader.pMesh.Objects = new tMeshObject[(int) LCMeshReader.pMesh.HeaderInfo.ObjCount];
      for (int index3 = 0; (long) index3 < (long) LCMeshReader.pMesh.HeaderInfo.ObjCount; ++index3)
      {
        tMeshObject tMeshObject = new tMeshObject()
        {
          MaterialName = ReadBytesSafe(b),
          Value1 = b.ReadUInt32(),
          FromVert = b.ReadUInt32(),
          ToVert = b.ReadUInt32(),
          FaceCount = b.ReadUInt32()
        };
        tMeshObject.Faces = new tFace[(int) tMeshObject.FaceCount];
        for (int index4 = 0; (long) index4 < (long) tMeshObject.FaceCount; ++index4)
          tMeshObject.Faces[index4] = new tFace(b.ReadInt16(), b.ReadInt16(), b.ReadInt16());
        tMeshObject.JValue = b.ReadUInt32();
        tMeshObject.JData = new byte[(int) tMeshObject.JValue];
        for (int index5 = 0; (long) index5 < (long) tMeshObject.JValue; ++index5)
          tMeshObject.JData[index5] = b.ReadByte();
        tMeshObject.ShaderFlag = b.ReadUInt32();
        if (tMeshObject.ShaderFlag > 0U)
        {
          tMeshObject.ShaderInfo = new tMeshShaderInfo();
          tMeshObject.ShaderInfo.cParam1 = b.ReadUInt32();
          tMeshObject.ShaderInfo.cParamFloats = b.ReadUInt32();
          tMeshObject.ShaderInfo.cTextureUnits = b.ReadUInt32();
          tMeshObject.ShaderInfo.cParam2 = b.ReadUInt32();
          tMeshObject.ShaderInfo = new tMeshShaderInfo()
          {
            cTextureUnits = tMeshObject.ShaderInfo.cParam1,
            cParamFloats = tMeshObject.ShaderInfo.cParamFloats,
            cParam1 = tMeshObject.ShaderInfo.cParam2,
            cParam2 = tMeshObject.ShaderInfo.cTextureUnits
          };
          tMeshObject.ShaderData = new tMeshShaderData();
          tMeshObject.ShaderData.ShaderName = ReadBytesSafe(b);
          tMeshObject.Textures = new tMeshTexture[(int) tMeshObject.ShaderInfo.cTextureUnits];
          for (int index6 = 0; (long) index6 < (long) tMeshObject.ShaderInfo.cTextureUnits; ++index6)
            tMeshObject.Textures[index6] = new tMeshTexture(ReadBytesSafe(b));
          if (tMeshObject.ShaderInfo.cParam1 > 0U)
            tMeshObject.ShaderData.Param1 = new uint[(int) tMeshObject.ShaderInfo.cParam1];
          if (tMeshObject.ShaderInfo.cParamFloats > 0U)
            tMeshObject.ShaderData.ParamFloats = new float[(int) tMeshObject.ShaderInfo.cParamFloats];
          if (tMeshObject.ShaderInfo.cParam2 > 0U)
            tMeshObject.ShaderData.Param2 = new uint[(int) tMeshObject.ShaderInfo.cParam2];
          tMeshObject.ShaderData.cParam0 = b.ReadUInt32();
          for (int index7 = 0; (long) index7 < (long) tMeshObject.ShaderInfo.cParam2; ++index7)
            tMeshObject.ShaderData.Param2[index7] = b.ReadUInt32();
          for (int index8 = 0; (long) index8 < (long) tMeshObject.ShaderInfo.cParamFloats; ++index8)
            tMeshObject.ShaderData.ParamFloats[index8] = b.ReadSingle();
          for (int index9 = 0; (long) index9 < (long) tMeshObject.ShaderInfo.cParam1; ++index9)
            tMeshObject.ShaderData.Param1[index9] = b.ReadUInt32();
          LCMeshReader.pMesh.Objects[index3] = tMeshObject;
        }
      }
      LCMeshReader.pMesh.Weights = new tMeshJointWeights[(int) LCMeshReader.pMesh.HeaderInfo.JointCount];
      for (int index10 = 0; (long) index10 < (long) LCMeshReader.pMesh.HeaderInfo.JointCount; ++index10)
      {
        LCMeshReader.pMesh.Weights[index10] = new tMeshJointWeights();
        LCMeshReader.pMesh.Weights[index10].JointName = ReadBytesSafe(b);
        LCMeshReader.pMesh.Weights[index10].Count = b.ReadUInt32();
        LCMeshReader.pMesh.Weights[index10].WeightsMap = new tMeshWeightsMap[(int) LCMeshReader.pMesh.Weights[index10].Count];
        for (int index11 = 0; (long) index11 < (long) LCMeshReader.pMesh.Weights[index10].Count; ++index11)
          LCMeshReader.pMesh.Weights[index10].WeightsMap[index11] = new tMeshWeightsMap(b.ReadInt32(), b.ReadSingle());
      }
      LCMeshReader.pMesh.MorphMap = new tMeshMorphMap[(int) LCMeshReader.pMesh.HeaderInfo.VertexCount];
      for (int index = 0; (long) index < (long) LCMeshReader.pMesh.HeaderInfo.VertexCount; ++index)
        LCMeshReader.pMesh.MorphMap[index] = new tMeshMorphMap(b.ReadBytes(4), b.ReadBytes(4));
      return b.BaseStream.Position == (long) (LCMeshReader.pMesh.HeaderInfo.MeshDataSize + 8);
    }

    private static bool ReadV11(BinaryReader b, long Pos)
    {
      b.BaseStream.Position = Pos;
      Decoder.Reset();
      LCMeshReader.pMesh.HeaderInfo.MeshCount = Decoder.Decode(LCMeshReader.pMesh.HeaderInfo.MeshCount);
      LCMeshReader.pMesh.HeaderInfo.VertexCount = Decoder.Decode(LCMeshReader.pMesh.HeaderInfo.VertexCount);
      LCMeshReader.pMesh.HeaderInfo.JointCount = Decoder.Decode(LCMeshReader.pMesh.HeaderInfo.JointCount);
      LCMeshReader.pMesh.HeaderInfo.TextureMaps = Decoder.Decode(LCMeshReader.pMesh.HeaderInfo.TextureMaps);
      LCMeshReader.pMesh.HeaderInfo.NormalCount = Decoder.Decode(LCMeshReader.pMesh.HeaderInfo.NormalCount);
      LCMeshReader.pMesh.HeaderInfo.ObjCount = Decoder.Decode(LCMeshReader.pMesh.HeaderInfo.ObjCount);
      LCMeshReader.pMesh.HeaderInfo.UnknownCount = Decoder.Decode(LCMeshReader.pMesh.HeaderInfo.UnknownCount);
      LCMeshReader.pMesh.Value1 = Decoder.Decode(LCMeshReader.pMesh.Value1);
      LCMeshReader.pMesh.Vertices = new tVertex3f[(int) LCMeshReader.pMesh.HeaderInfo.VertexCount];
      for (int index = 0; (long) index < (long) LCMeshReader.pMesh.HeaderInfo.VertexCount; ++index)
        LCMeshReader.pMesh.Vertices[index] = new tVertex3f(b.ReadSingle(), b.ReadSingle(), b.ReadSingle());
      LCMeshReader.pMesh.Normals = new tVertex3f[(int) LCMeshReader.pMesh.HeaderInfo.NormalCount];
      for (int index = 0; (long) index < (long) LCMeshReader.pMesh.HeaderInfo.NormalCount; ++index)
        LCMeshReader.pMesh.Normals[index] = new tVertex3f(b.ReadSingle(), b.ReadSingle(), b.ReadSingle());
      if (LCMeshReader.pMesh.HeaderInfo.TextureMaps > 0U)
      {
        LCMeshReader.pMesh.UVMaps = new tMeshUVMap[(int) LCMeshReader.pMesh.HeaderInfo.TextureMaps];
        for (int index1 = 0; (long) index1 < (long) LCMeshReader.pMesh.HeaderInfo.TextureMaps; ++index1)
        {
          tMeshUVMap tMeshUvMap = new tMeshUVMap();
          tMeshUvMap.Name = ReadBytesSafe(b);
          tMeshUvMap.Coords = new tTextCoord[(int) LCMeshReader.pMesh.HeaderInfo.VertexCount];
          for (int index2 = 0; (long) index2 < (long) LCMeshReader.pMesh.HeaderInfo.VertexCount; ++index2)
            tMeshUvMap.Coords[index2] = new tTextCoord(b.ReadSingle(), b.ReadSingle());
          LCMeshReader.pMesh.UVMaps[index1] = tMeshUvMap;
        }
      }
      LCMeshReader.pMesh.Objects = new tMeshObject[(int) LCMeshReader.pMesh.HeaderInfo.ObjCount];
      for (int index3 = 0; (long) index3 < (long) LCMeshReader.pMesh.HeaderInfo.ObjCount; ++index3)
      {
        tMeshObject tMeshObject = new tMeshObject()
        {
          FromVert = Decoder.Decode(b.ReadUInt32()),
          ToVert = Decoder.Decode(b.ReadUInt32()),
          FaceCount = Decoder.Decode(b.ReadUInt32())
        };
        tMeshObject.Faces = new tFace[(int) tMeshObject.FaceCount];
        for (int index4 = 0; (long) index4 < (long) tMeshObject.FaceCount; ++index4)
          tMeshObject.Faces[index4] = new tFace(b.ReadInt16(), b.ReadInt16(), b.ReadInt16());
        tMeshObject.MaterialName = ReadBytesSafe(b);
        tMeshObject.Value1 = Decoder.Decode(b.ReadUInt32());
        tMeshObject.JValue = Decoder.Decode(b.ReadUInt32());
        tMeshObject.JData = new byte[(int) tMeshObject.JValue];
        for (int index5 = 0; (long) index5 < (long) tMeshObject.JValue; ++index5)
          tMeshObject.JData[index5] = b.ReadByte();
        tMeshObject.ShaderFlag = Decoder.Decode(b.ReadUInt32());
        if (tMeshObject.ShaderFlag > 0U)
        {
          tMeshObject.ShaderInfo = new tMeshShaderInfo();
          tMeshObject.ShaderInfo.cParam1 = Decoder.Decode(b.ReadUInt32());
          tMeshObject.ShaderInfo.cParamFloats = Decoder.Decode(b.ReadUInt32());
          tMeshObject.ShaderInfo.cTextureUnits = Decoder.Decode(b.ReadUInt32());
          tMeshObject.ShaderInfo.cParam2 = Decoder.Decode(b.ReadUInt32());
          tMeshObject.ShaderData = new tMeshShaderData();
          tMeshObject.ShaderData.ShaderName = ReadBytesSafe(b);
          tMeshObject.Textures = new tMeshTexture[(int) tMeshObject.ShaderInfo.cTextureUnits];
          for (int index6 = 0; (long) index6 < (long) tMeshObject.ShaderInfo.cTextureUnits; ++index6)
          {
            tMeshObject.Textures[index6] = new tMeshTexture();
            tMeshObject.Textures[index6].InternalName = ReadBytesSafe(b);
          }
          if (tMeshObject.ShaderInfo.cParam2 > 0U)
            tMeshObject.ShaderData.Param1 = new uint[(int) tMeshObject.ShaderInfo.cParam1];
          if (tMeshObject.ShaderInfo.cParamFloats > 0U)
            tMeshObject.ShaderData.ParamFloats = new float[(int) tMeshObject.ShaderInfo.cParamFloats];
          if (tMeshObject.ShaderInfo.cParam1 > 0U)
            tMeshObject.ShaderData.Param2 = new uint[(int) tMeshObject.ShaderInfo.cParam2];
          tMeshObject.ShaderData.cParam0 = Decoder.Decode(b.ReadUInt32());
          for (int index7 = 0; (long) index7 < (long) tMeshObject.ShaderInfo.cParam2; ++index7)
            tMeshObject.ShaderData.Param2[index7] = Decoder.Decode(b.ReadUInt32());
          for (int index8 = 0; (long) index8 < (long) tMeshObject.ShaderInfo.cParamFloats; ++index8)
            tMeshObject.ShaderData.ParamFloats[index8] = b.ReadSingle();
          for (int index9 = 0; (long) index9 < (long) tMeshObject.ShaderInfo.cParam1; ++index9)
            tMeshObject.ShaderData.Param1[index9] = Decoder.Decode(b.ReadUInt32());
        }
        LCMeshReader.pMesh.Objects[index3] = tMeshObject;
      }
      LCMeshReader.pMesh.Weights = new tMeshJointWeights[(int) LCMeshReader.pMesh.HeaderInfo.JointCount];
      for (int index10 = 0; (long) index10 < (long) LCMeshReader.pMesh.HeaderInfo.JointCount; ++index10)
      {
        LCMeshReader.pMesh.Weights[index10] = new tMeshJointWeights();
        LCMeshReader.pMesh.Weights[index10].JointName = ReadBytesSafe(b);
        LCMeshReader.pMesh.Weights[index10].Count = Decoder.Decode(b.ReadUInt32());
        LCMeshReader.pMesh.Weights[index10].WeightsMap = new tMeshWeightsMap[(int) LCMeshReader.pMesh.Weights[index10].Count];
        for (int index11 = 0; (long) index11 < (long) LCMeshReader.pMesh.Weights[index10].Count; ++index11)
          LCMeshReader.pMesh.Weights[index10].WeightsMap[index11] = new tMeshWeightsMap(b.ReadInt32(), b.ReadSingle());
      }
      LCMeshReader.pMesh.MorphMap = new tMeshMorphMap[(int) LCMeshReader.pMesh.HeaderInfo.VertexCount];
      for (int index = 0; (long) index < (long) LCMeshReader.pMesh.HeaderInfo.VertexCount; ++index)
        LCMeshReader.pMesh.MorphMap[index] = new tMeshMorphMap(b.ReadBytes(4), b.ReadBytes(4));
      Pos = b.BaseStream.Position;
      return Pos == (long) (LCMeshReader.pMesh.HeaderInfo.MeshDataSize + 8);
    }
  }
}
