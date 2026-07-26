// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.TextEditor
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools
{
  public class TextEditor : Form
  {
    private string FileName;
    private IContainer components = (IContainer) null;
    private RichTextBox RTbSMC;
    private Button btnSave;
    private Button BtnClose;

    public TextEditor(string FileName)
    {
      this.InitializeComponent();
      FileName = FileName;
      if (!File.Exists(FileName))
        return;
      this.RTbSMC.Text = File.ReadAllText(FileName);
      this.RTbSMC.Select(0, 0);
      this.Text = FileName;
    }

    private void BtnClose_Click(object sender, EventArgs e) => this.Close();

    private void btnSave_Click(object sender, EventArgs e)
    {
      File.WriteAllText(this.Text, this.RTbSMC.Text);
      int num = (int) new CustomMessage("Saved").ShowDialog();
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (TextEditor));
      this.RTbSMC = new RichTextBox();
      this.btnSave = new Button();
      this.BtnClose = new Button();
      this.SuspendLayout();
      this.RTbSMC.BackColor = Color.RoyalBlue;
      this.RTbSMC.BorderStyle = BorderStyle.FixedSingle;
      this.RTbSMC.Font = new Font("Consolas", 9.75f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.RTbSMC.ForeColor = Color.White;
      this.RTbSMC.Location = new Point(12, 12);
      this.RTbSMC.Name = "RTbSMC";
      this.RTbSMC.Size = new Size(725, 346);
      this.RTbSMC.TabIndex = 0;
      this.RTbSMC.Text = "";
      this.btnSave.Location = new Point(12, 364);
      this.btnSave.Name = "btnSave";
      this.btnSave.Size = new Size(101, 23);
      this.btnSave.TabIndex = 1;
      this.btnSave.Text = "Save File";
      this.btnSave.UseVisualStyleBackColor = true;
      this.btnSave.Click += new EventHandler(this.btnSave_Click);
      this.BtnClose.Location = new Point(662, 365);
      this.BtnClose.Name = "BtnClose";
      this.BtnClose.Size = new Size(75, 23);
      this.BtnClose.TabIndex = 2;
      this.BtnClose.Text = "Close";
      this.BtnClose.UseVisualStyleBackColor = true;
      this.BtnClose.Click += new EventHandler(this.BtnClose_Click);
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(749, 395);
      this.Controls.Add((Control) this.BtnClose);
      this.Controls.Add((Control) this.btnSave);
      this.Controls.Add((Control) this.RTbSMC);
      this.Icon = (Icon) componentResourceManager.GetObject("$this.Icon");
      this.MaximizeBox = false;
      this.MinimizeBox = false;
      this.Name = nameof (TextEditor);
      this.StartPosition = FormStartPosition.CenterScreen;
      this.Text = nameof (TextEditor);
      this.ResumeLayout(false);
    }
  }
}
