// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.CustomMessage
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools
{
  public class CustomMessage : Form
  {
    private int tickCount;
    private IContainer components = (IContainer) null;
    private Label label1;
    private Timer timer1;

    public CustomMessage(string Text)
    {
      this.InitializeComponent();
      this.label1.Text = Text;
    }

    private void timer1_Tick(object sender, EventArgs e)
    {
      ++this.tickCount;
      if (this.tickCount <= 30)
        return;
      this.Opacity -= 0.0350000001490116;
      if (this.Opacity > 0.0)
        return;
      this.Close();
    }

    private void CustomMessage_Load(object sender, EventArgs e) => this.timer1.Enabled = true;

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      this.components = (IContainer) new System.ComponentModel.Container();
      this.label1 = new Label();
      this.timer1 = new Timer(this.components);
      this.SuspendLayout();
      this.label1.BackColor = Color.Gold;
      this.label1.Dock = DockStyle.Fill;
      this.label1.Font = new Font("Microsoft Sans Serif", 18f, FontStyle.Bold, GraphicsUnit.Point, (byte) 0);
      this.label1.Location = new Point(0, 0);
      this.label1.Name = "label1";
      this.label1.Size = new Size(417, 113);
      this.label1.TabIndex = 1;
      this.label1.Text = "Done !";
      this.label1.TextAlign = ContentAlignment.MiddleCenter;
      this.label1.UseWaitCursor = true;
      this.timer1.Interval = 10;
      this.timer1.Tick += new EventHandler(this.timer1_Tick);
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.BackColor = Color.Gold;
      this.ClientSize = new Size(417, 113);
      this.ControlBox = false;
      this.Controls.Add((Control) this.label1);
      this.FormBorderStyle = FormBorderStyle.None;
      this.Name = nameof (CustomMessage);
      this.ShowIcon = false;
      this.ShowInTaskbar = false;
      this.StartPosition = FormStartPosition.CenterScreen;
      this.TopMost = true;
      this.UseWaitCursor = true;
      this.Load += new EventHandler(this.CustomMessage_Load);
      this.ResumeLayout(false);
    }
  }
}
