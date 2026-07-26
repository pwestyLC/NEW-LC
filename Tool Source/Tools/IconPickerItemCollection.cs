// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.IconPickerItemCollection
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
  public class IconPickerItemCollection : Form
  {
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    private IContainer components = (IContainer) null;
    private GroupBox groupBox1;
    private PictureBox SelectedIcon;
    private PictureBox pictureBox1;
    private ComboBox comboBox1;
    private Button button2;
    private Button button1;

    public int TexID { get; set; }

    public int TexColumn { get; set; }

    public int TexRow { get; set; }

    public int OldItemBtnSelect { get; set; }

    public IconPickerItemCollection() => this.InitializeComponent();

    private void IconPickerItemCollection_Load(object sender, EventArgs e)
    {
      string[] files = Directory.GetFiles("icons");
      for (int index = 0; index < ((IEnumerable<string>) files).Count<string>(); ++index)
      {
        string[] source = files[index].Split('\\');
        if (((IEnumerable<string>) source).Count<string>() == 2 && source[1].ToLower().Contains("itemcollection"))
          this.comboBox1.Items.Add((object) Path.GetFileNameWithoutExtension(files[index]));
      }
      if (this.comboBox1.Items.Count > 0)
        this.comboBox1.SelectedIndex = 0;
      this.comboBox1.SelectedItem = (object) ("ItemCollectionBtn" + this.OldItemBtnSelect.ToString());
    }

    private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      Image image = Image.FromFile("icons/" + this.comboBox1.SelectedItem?.ToString() + ".png");
      this.pictureBox1.SizeMode = PictureBoxSizeMode.Normal;
      this.pictureBox1.Image = image;
    }

    private void button1_Click(object sender, EventArgs e) => this.DialogResult = DialogResult.OK;

    private void button2_Click(object sender, EventArgs e)
    {
      this.DialogResult = DialogResult.Cancel;
    }

    private void pictureBox1_MouseClick(object sender, MouseEventArgs e)
    {
      float num = 60f;
      int x = e.X;
      int y = e.Y;
      this.TexID = Convert.ToInt32(this.comboBox1.SelectedItem.ToString().Remove(0, 17));
      this.TexRow = (int) Math.Floor((double) y / (double) num);
      this.TexColumn = (int) Math.Floor((double) x / (double) num);
      this.SelectedIcon.Image = (Image) this.databaseHandle.IconItemCollection(this.TexID, this.TexRow, this.TexColumn);
    }

    private void pictureBox1_Click(object sender, EventArgs e)
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
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (IconPickerItemCollection));
      this.groupBox1 = new GroupBox();
      this.SelectedIcon = new PictureBox();
      this.pictureBox1 = new PictureBox();
      this.comboBox1 = new ComboBox();
      this.button2 = new Button();
      this.button1 = new Button();
      this.groupBox1.SuspendLayout();
      ((ISupportInitialize) this.SelectedIcon).BeginInit();
      ((ISupportInitialize) this.pictureBox1).BeginInit();
      this.SuspendLayout();
      this.groupBox1.Controls.Add((Control) this.SelectedIcon);
      this.groupBox1.Location = new Point(63, 194);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(100, 100);
      this.groupBox1.TabIndex = 11;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Selected Icon";
      this.SelectedIcon.BorderStyle = BorderStyle.FixedSingle;
      this.SelectedIcon.Location = new Point(18, 19);
      this.SelectedIcon.Name = "SelectedIcon";
      this.SelectedIcon.Size = new Size(60, 60);
      this.SelectedIcon.SizeMode = PictureBoxSizeMode.StretchImage;
      this.SelectedIcon.TabIndex = 0;
      this.SelectedIcon.TabStop = false;
      this.pictureBox1.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox1.Location = new Point(244, 12);
      this.pictureBox1.Name = "pictureBox1";
      this.pictureBox1.Size = new Size(512, 512);
      this.pictureBox1.TabIndex = 10;
      this.pictureBox1.TabStop = false;
      this.pictureBox1.Click += new EventHandler(this.pictureBox1_Click);
      this.pictureBox1.MouseClick += new MouseEventHandler(this.pictureBox1_MouseClick);
      this.comboBox1.FlatStyle = FlatStyle.Flat;
      this.comboBox1.FormattingEnabled = true;
      this.comboBox1.Items.AddRange(new object[1]
      {
        (object) "ItemCollectionBtn1"
      });
      this.comboBox1.Location = new Point(6, 12);
      this.comboBox1.Name = "comboBox1";
      this.comboBox1.Size = new Size(232, 21);
      this.comboBox1.TabIndex = 9;
      this.comboBox1.SelectedIndexChanged += new EventHandler(this.comboBox1_SelectedIndexChanged);
      this.button2.Location = new Point(113, 300);
      this.button2.Name = "button2";
      this.button2.Size = new Size(75, 23);
      this.button2.TabIndex = 13;
      this.button2.Text = "Cancel";
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.button1.Location = new Point(32, 300);
      this.button1.Name = "button1";
      this.button1.Size = new Size(75, 23);
      this.button1.TabIndex = 12;
      this.button1.Text = "OK";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.ClientSize = new Size(769, 537);
      this.Controls.Add((Control) this.groupBox1);
      this.Controls.Add((Control) this.pictureBox1);
      this.Controls.Add((Control) this.comboBox1);
      this.Controls.Add((Control) this.button2);
      this.Controls.Add((Control) this.button1);
      this.Icon = (Icon) componentResourceManager.GetObject("$this.Icon");
      this.Name = nameof (IconPickerItemCollection);
      this.Text = nameof (IconPickerItemCollection);
      this.Load += new EventHandler(this.IconPickerItemCollection_Load);
      this.groupBox1.ResumeLayout(false);
      ((ISupportInitialize) this.SelectedIcon).EndInit();
      ((ISupportInitialize) this.pictureBox1).EndInit();
      this.ResumeLayout(false);
    }
  }
}
