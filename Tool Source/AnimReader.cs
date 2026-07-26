// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.AnimReader
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

#nullable disable
namespace LcDevPack_TeamDamonA
{
  internal class AnimReader
  {
    public static cAnimFile ReadFile(string FileName)
    {
      ASCIIEncoding asciiEncoding = new ASCIIEncoding();
      cAnimFile cAnimFile = new cAnimFile();
      using (BinaryReader binaryReader = new BinaryReader((Stream) File.Open(FileName, FileMode.Open)))
      {
        binaryReader.ReadBytes(4);
        cAnimFile.Header = new cAnimHeader();
        cAnimFile.Header.Version = binaryReader.ReadInt32();
        cAnimFile.Header.AnimCount = binaryReader.ReadInt32();
        cAnimFile.Animation = new cAnimation[cAnimFile.Header.AnimCount];
        for (int index1 = 0; index1 < cAnimFile.Header.AnimCount; ++index1)
        {
          cAnimation cAnimation = new cAnimation()
          {
            SkaPath = asciiEncoding.GetString(binaryReader.ReadBytes(binaryReader.ReadInt32())),
            AnimeName = asciiEncoding.GetString(binaryReader.ReadBytes(binaryReader.ReadInt32())),
            fps = binaryReader.ReadSingle(),
            last_frame = binaryReader.ReadInt32(),
            extra_val1 = binaryReader.ReadInt32(),
            extra_val2 = binaryReader.ReadInt32(),
            extra_val3 = binaryReader.ReadInt32(),
            JointCount = binaryReader.ReadInt32()
          };
          cAnimation.BoneAnim = new cJointAnim[cAnimation.JointCount];
          for (int index2 = 0; index2 < cAnimation.JointCount; ++index2)
          {
            cJointAnim cJointAnim = new cJointAnim();
            cJointAnim.JointName = asciiEncoding.GetString(binaryReader.ReadBytes(binaryReader.ReadInt32()));
            float[] numArray = new float[12];
            for (int index3 = 0; index3 < 12; ++index3)
              numArray[index3] = binaryReader.ReadSingle();
            cJointAnim.PositionCount = binaryReader.ReadInt32();
            cJointAnim.Positions = new cPositionKeyFrame[cJointAnim.PositionCount];
            for (int index4 = 0; index4 < cJointAnim.PositionCount; ++index4)
              cJointAnim.Positions[index4] = new cPositionKeyFrame(binaryReader.ReadInt16(), binaryReader.ReadInt16(), binaryReader.ReadSingle(), binaryReader.ReadSingle(), binaryReader.ReadSingle());
            cJointAnim.RotationCount = binaryReader.ReadInt32();
            cJointAnim.Rotations = new cRotationKeyFrame[cJointAnim.RotationCount];
            for (int index5 = 0; index5 < cJointAnim.RotationCount; ++index5)
              cJointAnim.Rotations[index5] = new cRotationKeyFrame(binaryReader.ReadInt16(), binaryReader.ReadInt16(), binaryReader.ReadSingle(), binaryReader.ReadSingle(), binaryReader.ReadSingle(), binaryReader.ReadSingle());
            cJointAnim.Unknown = binaryReader.ReadSingle();
            cAnimation.BoneAnim[index2] = cJointAnim;
          }
          cAnimFile.Animation[index1] = cAnimation;
          cAnimFile.Animation[index1].EndData = binaryReader.ReadInt32();
        }
      }
      return cAnimFile;
    }

    public static bool WriteFile(cAnimFile animData, string FileName)
    {
      try
      {
        float[] numArray = new float[12]
        {
          1f,
          0.0f,
          0.0f,
          0.0f,
          0.0f,
          1f,
          0.0f,
          0.0f,
          0.0f,
          0.0f,
          1f,
          0.0f
        };
        ASCIIEncoding asciiEncoding = new ASCIIEncoding();
        using (BinaryWriter binaryWriter = new BinaryWriter((Stream) File.Create(FileName)))
        {
          binaryWriter.Write(asciiEncoding.GetBytes("ANIM"));
          binaryWriter.Write(animData.Header.Version);
          binaryWriter.Write(animData.Header.AnimCount);
          for (int index1 = 0; index1 < ((IEnumerable<cAnimation>) animData.Animation).Count<cAnimation>(); ++index1)
          {
            cAnimation cAnimation = animData.Animation[index1];
            binaryWriter.Write(asciiEncoding.GetBytes(cAnimation.SkaPath).Length);
            binaryWriter.Write(asciiEncoding.GetBytes(cAnimation.SkaPath));
            binaryWriter.Write(asciiEncoding.GetBytes(cAnimation.AnimeName).Length);
            binaryWriter.Write(asciiEncoding.GetBytes(cAnimation.AnimeName));
            binaryWriter.Write(cAnimation.fps);
            binaryWriter.Write(cAnimation.last_frame);
            binaryWriter.Write(cAnimation.extra_val1);
            binaryWriter.Write(cAnimation.extra_val2);
            binaryWriter.Write(cAnimation.extra_val3);
            binaryWriter.Write(((IEnumerable<cJointAnim>) cAnimation.BoneAnim).Count<cJointAnim>());
            for (int index2 = 0; index2 < ((IEnumerable<cJointAnim>) cAnimation.BoneAnim).Count<cJointAnim>(); ++index2)
            {
              cJointAnim cJointAnim = cAnimation.BoneAnim[index2];
              binaryWriter.Write(asciiEncoding.GetBytes(cJointAnim.JointName).Length);
              binaryWriter.Write(asciiEncoding.GetBytes(cJointAnim.JointName));
              for (int index3 = 0; index3 < 12; ++index3)
                binaryWriter.Write(numArray[index3]);
              binaryWriter.Write(((IEnumerable<cPositionKeyFrame>) cJointAnim.Positions).Count<cPositionKeyFrame>());
              for (int index4 = 0; index4 < ((IEnumerable<cPositionKeyFrame>) cJointAnim.Positions).Count<cPositionKeyFrame>(); ++index4)
              {
                cPositionKeyFrame position = cJointAnim.Positions[index4];
                binaryWriter.Write(position.Frame);
                binaryWriter.Write(position.Flags);
                binaryWriter.Write(position.x);
                binaryWriter.Write(position.y);
                binaryWriter.Write(position.z);
              }
              binaryWriter.Write(((IEnumerable<cRotationKeyFrame>) cJointAnim.Rotations).Count<cRotationKeyFrame>());
              for (int index5 = 0; index5 < ((IEnumerable<cRotationKeyFrame>) cJointAnim.Rotations).Count<cRotationKeyFrame>(); ++index5)
              {
                cRotationKeyFrame rotation = cJointAnim.Rotations[index5];
                binaryWriter.Write(rotation.Frame);
                binaryWriter.Write(rotation.Flags);
                binaryWriter.Write(rotation.w);
                binaryWriter.Write(rotation.x);
                binaryWriter.Write(rotation.y);
                binaryWriter.Write(rotation.z);
              }
              binaryWriter.Write(cJointAnim.Unknown);
            }
            binaryWriter.Write(cAnimation.EndData);
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
