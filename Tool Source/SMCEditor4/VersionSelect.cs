// Decompiled with JetBrains decompiler
// Type: SMCEditor3.VersionSelect
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

#nullable disable
namespace SMCEditor3
{
  public class VersionSelect : Form
  {
    private IContainer components = (IContainer) null;
    private Button btnCancel;
    private Button btnOk;
    private RadioButton chkEp1;
    private RadioButton chkEp2;
    private Label label1;
    public int Version;

    public VersionSelect() => this.InitializeComponent();

    private void btnOk_Click(object sender, EventArgs e)
    {
      if (this.chkEp1.Checked)
        this.Version = 2008;
      else
        this.Version = 2012;
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
      this.SuspendLayout();
      this.label1.AutoSize = true;
      this.label1.Location = new Point(3, 9);
      this.label1.Name = "label1";
      this.label1.Size = new Size(142, 13);
      this.label1.TabIndex = 0;
      this.label1.Text = "Выберите версию клиента";
      this.chkEp2.AutoSize = true;
      this.chkEp2.Checked = true;
      this.chkEp2.Location = new Point(33, 44);
      this.chkEp2.Name = "chkEp2";
      this.chkEp2.Size = new Size(71, 17);
      this.chkEp2.TabIndex = 1;
      this.chkEp2.TabStop = true;
      this.chkEp2.Text = "Эпизод 2";
      this.chkEp2.UseVisualStyleBackColor = true;
      this.chkEp1.AutoSize = true;
      this.chkEp1.Location = new Point(33, 67);
      this.chkEp1.Name = "chkEp1";
      this.chkEp1.Size = new Size(71, 17);
      this.chkEp1.TabIndex = 2;
      this.chkEp1.Text = "Эпизод 1";
      this.chkEp1.UseVisualStyleBackColor = true;
      this.btnCancel.Dock = DockStyle.Bottom;
      this.btnCancel.Location = new Point(0, 125);
      this.btnCancel.Name = "btnCancel";
      this.btnCancel.Size = new Size(148, 23);
      this.btnCancel.TabIndex = 3;
      this.btnCancel.Text = "&Отмена";
      this.btnCancel.UseVisualStyleBackColor = true;
      this.btnOk.Dock = DockStyle.Bottom;
      this.btnOk.Location = new Point(0, 102);
      this.btnOk.Name = "btnOk";
      this.btnOk.Size = new Size(148, 23);
      this.btnOk.TabIndex = 4;
      this.btnOk.Text = "&Ok";
      this.btnOk.UseVisualStyleBackColor = true;
      this.btnOk.Click += new EventHandler(this.btnOk_Click);
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.ClientSize = new Size(148, 148);
      this.Controls.Add((Control) this.btnOk);
      this.Controls.Add((Control) this.btnCancel);
      this.Controls.Add((Control) this.chkEp1);
      this.Controls.Add((Control) this.chkEp2);
      this.Controls.Add((Control) this.label1);
      this.Name = nameof (VersionSelect);
      this.Text = "Выбор версии клиента";
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
