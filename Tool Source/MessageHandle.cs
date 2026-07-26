// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.MessageHandle
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA
{
  public class MessageHandle
  {
    public void SuccessFileMessage()
    {
      int num = (int) MessageBox.Show("Your file success saved!", "Success");
    }

    public void FailedFileMessage()
    {
      int num = (int) MessageBox.Show("Your file can't saved!", "Failed");
    }

    public void WelcomeMessage()
    {
      int num = (int) MessageBox.Show("This program use the ExportLod DLL by DamonA.", "Welcome devloper!");
    }
  }
}
