// Decompiled with JetBrains decompiler
// Type: String_Editor.VersionSelect
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

#nullable disable
namespace String_Editor
{
  public class VersionSelect : Form
  {
    private IContainer components = (IContainer) null;
    private Button button2;
    private Button button1;
    private Label label1;
    private RadioButton rbEp2;
    private RadioButton rbEp3;
    public int Version;

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      this.button2 = new Button();
      this.button1 = new Button();
      this.label1 = new Label();
      this.rbEp2 = new RadioButton();
      this.rbEp3 = new RadioButton();
      this.SuspendLayout();
      this.button2.DialogResult = DialogResult.Cancel;
      this.button2.Location = new Point(101, 61);
      this.button2.Name = "button2";
      this.button2.Size = new Size(75, 23);
      this.button2.TabIndex = 11;
      this.button2.Text = "Cancelar";
      this.button2.UseVisualStyleBackColor = true;
      this.button1.DialogResult = DialogResult.OK;
      this.button1.Location = new Point(101, 32);
      this.button1.Name = "button1";
      this.button1.Size = new Size(75, 23);
      this.button1.TabIndex = 10;
      this.button1.Text = "OK";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.label1.AutoSize = true;
      this.label1.Location = new Point(12, 9);
      this.label1.Name = "label1";
      this.label1.Size = new Size(158, 13);
      this.label1.TabIndex = 9;
      this.label1.Text = "Selecione a versão do ItemALL ";
      this.rbEp2.Checked = true;
      this.rbEp2.Location = new Point(27, 35);
      this.rbEp2.Name = "rbEp2";
      this.rbEp2.Size = new Size(45, 17);
      this.rbEp2.TabIndex = 6;
      this.rbEp2.Text = "EP2";
      this.rbEp2.UseVisualStyleBackColor = true;
      this.rbEp3.Location = new Point(27, 64);
      this.rbEp3.Name = "rbEp3";
      this.rbEp3.Size = new Size(45, 17);
      this.rbEp3.TabIndex = 6;
      this.rbEp3.Text = "EP3";
      this.rbEp3.UseVisualStyleBackColor = true;
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(191, 105);
      this.Controls.Add((Control) this.button2);
      this.Controls.Add((Control) this.button1);
      this.Controls.Add((Control) this.label1);
      this.Controls.Add((Control) this.rbEp3);
      this.Controls.Add((Control) this.rbEp2);
      this.FormBorderStyle = FormBorderStyle.FixedToolWindow;
      this.Name = nameof (VersionSelect);
      this.StartPosition = FormStartPosition.CenterParent;
      this.Text = nameof (VersionSelect);
      this.ResumeLayout(false);
      this.PerformLayout();
    }

    public VersionSelect() => this.InitializeComponent();

    private void button1_Click(object sender, EventArgs e)
    {
      if (this.rbEp2.Checked)
        this.Version = 2012;
      else
        this.Version = 2015;
    }
  }
}
