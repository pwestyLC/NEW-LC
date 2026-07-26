// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.IconPickerSkill
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools
{
  public class IconPickerSkill : Form
  {
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    private IContainer components = (IContainer) null;
    private ComboBox comboBox1;
    private PictureBox pictureBox1;
    private GroupBox groupBox1;
    private PictureBox SelectedIcon;
    private Button button1;
    private Button button2;

    public int TexID { get; set; }

    public int TexColumn { get; set; }

    public int TexRow { get; set; }

    public int OldItemBtnSelect { get; set; }

    public IconPickerSkill() => this.InitializeComponent();

    private void IconPicker_Load(object sender, EventArgs e)
    {
      string[] files = Directory.GetFiles("icons");
      for (int index = 0; index < ((IEnumerable<string>) files).Count<string>(); ++index)
      {
        string[] source = files[index].Split('\\');
        if (((IEnumerable<string>) source).Count<string>() == 2 && source[1].ToLower().Contains("skillbtn"))
          this.comboBox1.Items.Add((object) Path.GetFileNameWithoutExtension(files[index]));
      }
      if (this.comboBox1.Items.Count > 0)
        this.comboBox1.SelectedIndex = 0;
      this.comboBox1.SelectedItem = (object) ("SkillBtn" + this.OldItemBtnSelect.ToString());
    }

    private void pictureBox1_MouseClick(object sender, MouseEventArgs e)
    {
      int x = e.X;
      int y = e.Y;
      this.TexID = Convert.ToInt32(this.comboBox1.SelectedItem.ToString().Remove(0, 8));
      this.TexRow = (int) Math.Floor((double) y / 32.0);
      this.TexColumn = (int) Math.Floor((double) x / 32.0);
      this.SelectedIcon.Image = (Image) this.databaseHandle.IconSkill1(this.TexID, this.TexRow, this.TexColumn);
    }

    private void pictureBox1_Click(object sender, EventArgs e)
    {
    }

    private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.pictureBox1.Image = Image.FromFile("icons/" + this.comboBox1.SelectedItem?.ToString() + ".png");
    }

    private void button1_Click(object sender, EventArgs e) => this.DialogResult = DialogResult.OK;

    private void button2_Click(object sender, EventArgs e)
    {
      this.DialogResult = DialogResult.Cancel;
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (IconPickerSkill));
      this.comboBox1 = new ComboBox();
      this.pictureBox1 = new PictureBox();
      this.groupBox1 = new GroupBox();
      this.SelectedIcon = new PictureBox();
      this.button1 = new Button();
      this.button2 = new Button();
      ((ISupportInitialize) this.pictureBox1).BeginInit();
      this.groupBox1.SuspendLayout();
      ((ISupportInitialize) this.SelectedIcon).BeginInit();
      this.SuspendLayout();
      this.comboBox1.FlatStyle = FlatStyle.Flat;
      this.comboBox1.FormattingEnabled = true;
      this.comboBox1.Location = new Point(12, 12);
      this.comboBox1.Name = "comboBox1";
      this.comboBox1.Size = new Size(232, 21);
      this.comboBox1.TabIndex = 0;
      this.comboBox1.SelectedIndexChanged += new EventHandler(this.comboBox1_SelectedIndexChanged);
      this.pictureBox1.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox1.Location = new Point(250, 12);
      this.pictureBox1.Name = "pictureBox1";
      this.pictureBox1.Size = new Size(512, 512);
      this.pictureBox1.TabIndex = 1;
      this.pictureBox1.TabStop = false;
      this.pictureBox1.Click += new EventHandler(this.pictureBox1_Click);
      this.pictureBox1.MouseClick += new MouseEventHandler(this.pictureBox1_MouseClick);
      this.groupBox1.Controls.Add((Control) this.SelectedIcon);
      this.groupBox1.Location = new Point(69, 194);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(100, 100);
      this.groupBox1.TabIndex = 6;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Selected Icon";
      this.SelectedIcon.BorderStyle = BorderStyle.FixedSingle;
      this.SelectedIcon.Location = new Point(34, 37);
      this.SelectedIcon.Name = "SelectedIcon";
      this.SelectedIcon.Size = new Size(32, 32);
      this.SelectedIcon.SizeMode = PictureBoxSizeMode.StretchImage;
      this.SelectedIcon.TabIndex = 0;
      this.SelectedIcon.TabStop = false;
      this.button1.Location = new Point(38, 300);
      this.button1.Name = "button1";
      this.button1.Size = new Size(75, 23);
      this.button1.TabIndex = 7;
      this.button1.Text = "OK";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.button2.Location = new Point(119, 300);
      this.button2.Name = "button2";
      this.button2.Size = new Size(75, 23);
      this.button2.TabIndex = 8;
      this.button2.Text = "Cancel";
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.ClientSize = new Size(775, 560);
      this.Controls.Add((Control) this.button2);
      this.Controls.Add((Control) this.button1);
      this.Controls.Add((Control) this.groupBox1);
      this.Controls.Add((Control) this.pictureBox1);
      this.Controls.Add((Control) this.comboBox1);
      this.Icon = (Icon) componentResourceManager.GetObject("$this.Icon");
      this.Name = nameof (IconPickerSkill);
      this.Text = "IconPicker";
      this.Load += new EventHandler(this.IconPicker_Load);
      ((ISupportInitialize) this.pictureBox1).EndInit();
      this.groupBox1.ResumeLayout(false);
      ((ISupportInitialize) this.SelectedIcon).EndInit();
      this.ResumeLayout(false);
    }
  }
}
