// Decompiled with JetBrains decompiler
// Type: MapDtaRead.Error
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

#nullable disable
namespace MapDtaRead
{
  public class Error : Form
  {
    private IContainer components;
    private RichTextBox richTextBox1;

    public Error(string Msg)
    {
      this.InitializeComponent();
      this.richTextBox1.Text = Msg;
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      this.richTextBox1 = new RichTextBox();
      this.SuspendLayout();
      this.richTextBox1.Location = new Point(5, 9);
      this.richTextBox1.Name = "richTextBox1";
      this.richTextBox1.Size = new Size(598, 326);
      this.richTextBox1.TabIndex = 0;
      this.richTextBox1.Text = "";
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(607, 339);
      this.Controls.Add((Control) this.richTextBox1);
      this.Name = nameof (Error);
      this.Text = nameof (Error);
      this.ResumeLayout(false);
    }
  }
}
