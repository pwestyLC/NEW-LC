// Decompiled with JetBrains decompiler
// Type: SMCEditor4.VersionSelect
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

#nullable disable
namespace SMCEditor4
{
  public class VersionSelect : Form
  {
    private Button btnCancel;
    private Button btnOk;
    private RadioButton chkEp1;
    private RadioButton chkEp2;
    private RadioButton chkEp3;
    private IContainer components;
    private Label label1;
    private RadioButton rbtn2015;
    public int Version;

    public VersionSelect() => this.InitializeComponent();

    private void btnOk_Click(object sender, EventArgs e)
    {
      if (this.rbtn2015.Checked)
        this.Version = 2015;
      else if (this.chkEp1.Checked)
        this.Version = 2008;
      else if (this.chkEp3.Checked)
        this.Version = 2013;
      else
        this.Version = 2012;
    }

    private void chkEp1_CheckedChanged(object sender, EventArgs e)
    {
    }

    private void chkEp3_CheckedChanged(object sender, EventArgs e)
    {
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      this.label1 = new Label();
      this.chkEp2 = new RadioButton();
      this.chkEp1 = new RadioButton();
      this.btnCancel = new Button();
      this.btnOk = new Button();
      this.chkEp3 = new RadioButton();
      this.rbtn2015 = new RadioButton();
      this.SuspendLayout();
      this.label1.AutoSize = true;
      this.label1.Location = new Point(13, 13);
      this.label1.Name = "label1";
      this.label1.Size = new Size(125, 13);
      this.label1.TabIndex = 0;
      this.label1.Text = "Select your client version";
      this.chkEp2.AutoSize = true;
      this.chkEp2.Location = new Point(34, 82);
      this.chkEp2.Name = "chkEp2";
      this.chkEp2.Size = new Size(72, 17);
      this.chkEp2.TabIndex = 1;
      this.chkEp2.Text = "Episode 2";
      this.chkEp2.UseVisualStyleBackColor = true;
      this.chkEp1.AutoSize = true;
      this.chkEp1.Location = new Point(34, 105);
      this.chkEp1.Name = "chkEp1";
      this.chkEp1.Size = new Size(72, 17);
      this.chkEp1.TabIndex = 2;
      this.chkEp1.Text = "Episode 1";
      this.chkEp1.UseVisualStyleBackColor = true;
      this.chkEp1.CheckedChanged += new EventHandler(this.chkEp1_CheckedChanged);
      this.btnCancel.DialogResult = DialogResult.Cancel;
      this.btnCancel.Dock = DockStyle.Bottom;
      this.btnCancel.Location = new Point(0, 154);
      this.btnCancel.Name = "btnCancel";
      this.btnCancel.Size = new Size(148, 23);
      this.btnCancel.TabIndex = 3;
      this.btnCancel.Text = "&Cancel";
      this.btnCancel.UseVisualStyleBackColor = true;
      this.btnOk.DialogResult = DialogResult.OK;
      this.btnOk.Dock = DockStyle.Bottom;
      this.btnOk.Location = new Point(0, 131);
      this.btnOk.Name = "btnOk";
      this.btnOk.Size = new Size(148, 23);
      this.btnOk.TabIndex = 4;
      this.btnOk.Text = "&Ok";
      this.btnOk.UseVisualStyleBackColor = true;
      this.btnOk.Click += new EventHandler(this.btnOk_Click);
      this.chkEp3.AutoSize = true;
      this.chkEp3.Location = new Point(34, 59);
      this.chkEp3.Name = "chkEp3";
      this.chkEp3.Size = new Size(72, 17);
      this.chkEp3.TabIndex = 5;
      this.chkEp3.TabStop = true;
      this.chkEp3.Text = "Episode 3";
      this.chkEp3.UseVisualStyleBackColor = true;
      this.chkEp3.CheckedChanged += new EventHandler(this.chkEp3_CheckedChanged);
      this.rbtn2015.AutoSize = true;
      this.rbtn2015.Checked = true;
      this.rbtn2015.Location = new Point(34, 36);
      this.rbtn2015.Name = "rbtn2015";
      this.rbtn2015.Size = new Size(72, 17);
      this.rbtn2015.TabIndex = 6;
      this.rbtn2015.TabStop = true;
      this.rbtn2015.Text = "Episode 4";
      this.rbtn2015.UseVisualStyleBackColor = true;
      this.ClientSize = new Size(148, 177);
      this.Controls.Add((Control) this.rbtn2015);
      this.Controls.Add((Control) this.chkEp3);
      this.Controls.Add((Control) this.btnOk);
      this.Controls.Add((Control) this.btnCancel);
      this.Controls.Add((Control) this.chkEp1);
      this.Controls.Add((Control) this.chkEp2);
      this.Controls.Add((Control) this.label1);
      this.Name = nameof (VersionSelect);
      this.Text = nameof (VersionSelect);
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
