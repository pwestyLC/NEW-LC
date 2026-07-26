// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.IconPickerAffinity
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using LcDevPack_TeamDamonA.Tools.MemoryWorker.Affinity_EP4_By_Assasin;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker
{
  public class IconPickerAffinity : Form
  {
    private IContainer components = (IContainer) null;
    private PictureBox SelectedIcon;
    private Label label1;
    private ComboBox IconFileCombo;
    private Button button2;
    private Button button1;
    private PictureBox IconBox;

    public IconPickerAffinity()
    {
      this.InitializeComponent();
      string[] files = Directory.GetFiles("icons");
      for (int index = 0; index < ((IEnumerable<string>) files).Count<string>(); ++index)
      {
        string[] source = files[index].Split('\\');
        if (((IEnumerable<string>) source).Count<string>() == 2 && source[1].ToLower().Contains("skillbtn"))
          this.IconFileCombo.Items.Add((object) Path.GetFileNameWithoutExtension(files[index]));
      }
      if (this.IconFileCombo.Items.Count > 0)
        this.IconFileCombo.SelectedIndex = 0;
      this.IconFileCombo.SelectedItem = (object) "SkillBtn0";
    }

    private void IconPickerAffinity_Load(object sender, EventArgs e)
    {
    }

    public int TexColumn { get; set; }

    public int TexID { get; set; }

    public int TexRow { get; set; }

    private void IconBox_MouseClick(object sender, MouseEventArgs e)
    {
      int x = e.X;
      int y = e.Y;
      this.TexID = Convert.ToInt32(this.IconFileCombo.SelectedItem.ToString().Remove(0, 8));
      this.TexRow = (int) Math.Floor((double) y / 32.0);
      this.TexColumn = (int) Math.Floor((double) x / 32.0);
      this.SelectedIcon.Image = (Image) Affinity_EP4.AffinityIcons(this.TexID, this.TexRow, this.TexColumn);
    }

    private void IconFileCombo_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.IconBox.Image = Image.FromFile("icons\\" + this.IconFileCombo.SelectedItem?.ToString() + ".png");
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      this.SelectedIcon = new PictureBox();
      this.label1 = new Label();
      this.IconFileCombo = new ComboBox();
      this.button2 = new Button();
      this.button1 = new Button();
      this.IconBox = new PictureBox();
      ((ISupportInitialize) this.SelectedIcon).BeginInit();
      ((ISupportInitialize) this.IconBox).BeginInit();
      this.SuspendLayout();
      this.SelectedIcon.BorderStyle = BorderStyle.FixedSingle;
      this.SelectedIcon.Location = new Point(239, 6);
      this.SelectedIcon.Name = "SelectedIcon";
      this.SelectedIcon.Size = new Size(32, 32);
      this.SelectedIcon.SizeMode = PictureBoxSizeMode.StretchImage;
      this.SelectedIcon.TabIndex = 0;
      this.SelectedIcon.TabStop = false;
      this.label1.AutoSize = true;
      this.label1.Location = new Point(12, 9);
      this.label1.Name = "label1";
      this.label1.Size = new Size(47, 13);
      this.label1.TabIndex = 15;
      this.label1.Text = "Icon File";
      this.IconFileCombo.FormattingEnabled = true;
      this.IconFileCombo.Location = new Point(76, 6);
      this.IconFileCombo.Name = "IconFileCombo";
      this.IconFileCombo.Size = new Size(157, 21);
      this.IconFileCombo.TabIndex = 14;
      this.IconFileCombo.SelectedIndexChanged += new EventHandler(this.IconFileCombo_SelectedIndexChanged);
      this.button2.DialogResult = DialogResult.OK;
      this.button2.Location = new Point(277, 12);
      this.button2.Name = "button2";
      this.button2.Size = new Size(75, 23);
      this.button2.TabIndex = 13;
      this.button2.Text = "Cancel";
      this.button2.UseVisualStyleBackColor = true;
      this.button1.DialogResult = DialogResult.OK;
      this.button1.Location = new Point(358, 12);
      this.button1.Name = "button1";
      this.button1.Size = new Size(75, 23);
      this.button1.TabIndex = 12;
      this.button1.Text = "OK";
      this.button1.UseVisualStyleBackColor = true;
      this.IconBox.BorderStyle = BorderStyle.FixedSingle;
      this.IconBox.Location = new Point(12, 41);
      this.IconBox.Name = "IconBox";
      this.IconBox.Size = new Size(1024, 512);
      this.IconBox.TabIndex = 17;
      this.IconBox.TabStop = false;
      this.IconBox.MouseClick += new MouseEventHandler(this.IconBox_MouseClick);
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(1045, 563);
      this.Controls.Add((Control) this.SelectedIcon);
      this.Controls.Add((Control) this.IconBox);
      this.Controls.Add((Control) this.label1);
      this.Controls.Add((Control) this.IconFileCombo);
      this.Controls.Add((Control) this.button2);
      this.Controls.Add((Control) this.button1);
      this.Name = nameof (IconPickerAffinity);
      this.Text = nameof (IconPickerAffinity);
      this.Load += new EventHandler(this.IconPickerAffinity_Load);
      ((ISupportInitialize) this.SelectedIcon).EndInit();
      ((ISupportInitialize) this.IconBox).EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
