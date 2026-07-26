// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.ItemPicker2
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools
{
  public class ItemPicker2 : Form
  {
    public List<string> MenuList = new List<string>();
    public List<string> MenuListSearch = new List<string>();
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    private string Host = SkillEditor.connection.Settings.SqlHost;
    private string User = SkillEditor.connection.Settings.SqlUser;
    private string Password = SkillEditor.connection.Settings.SqlPassword;
    private string Database = SkillEditor.connection.Settings.SqlDatabase;
    public string[] menuArray = new string[2]
    {
      "a_index",
      "a_name_usa"
    };
    public int ItemIndex = -1;
    public int ItemAmount = -1;
    private IContainer components = (IContainer) null;
    private GroupBox groupBox1;
    private TextBox textBox1;
    private GroupBox groupBox2;
    private Button button2;
    private Button button1;
    private Button button3;
    private GroupBox groupBox3;
    private PictureBox pictureBox1;
    private TextBox textBox3;
    private CheckedListBox ClbSort;
    private GroupBox groupBox4;
    private TextBox textBox2;
    private CheckedListBox listBox1;
    private TextBox tbAmount;
    private Label label1;
    public string mSortJob = "-1";

    public ItemPicker2() => this.InitializeComponent();

    private void LoadStartup()
    {
      this.ClbSort.Items.AddRange(new object[8]
      {
        (object) "-1 - All",
        (object) "1 - Titan",
        (object) "2 - Knight",
        (object) "4 - Healer",
        (object) "264 - Mage",
        (object) "144 - Rogue",
        (object) "32 - Sorcerer",
        (object) "64 - NightShadow"
      });
    }

    private void ItemPicker_Load(object sender, EventArgs e)
    {
      this.LoadStartup();
      this.MenuList.Clear();
      this.listBox1.BeginUpdate();
      for (int index = 0; index < IconList.List.Count<ticon>(); ++index)
        this.listBox1.Items.Add((object) (IconList.List[index].ItemID.ToString() + " - " + IconList.List[index].Name.ToString()));
      this.listBox1.EndUpdate();
    }

    public bool SearchString(string s) => s.ToUpper().Contains(this.textBox1.Text.ToUpper());

    private int GetID()
    {
      int result = -1;
      int.TryParse(this.listBox1.Text.Split(' ')[0], out result);
      return result;
    }

    private void textBox1_TextChanged(object sender, EventArgs e)
    {
      this.listBox1.Items.Clear();
      int num = IconList.List.Count<ticon>();
      this.listBox1.BeginUpdate();
      for (int index = 0; index < num; ++index)
      {
        if ((IconList.List[index].ItemID.ToString() + " - " + IconList.List[index].Name.ToString()).ToLower().Contains(this.textBox1.Text.ToLower()))
          this.listBox1.Items.Add((object) (IconList.List[index].ItemID.ToString() + " - " + IconList.List[index].Name.ToString()));
      }
      this.listBox1.EndUpdate();
      int count = this.listBox1.Items.Count;
      if (count <= 0)
        return;
      this.listBox1.BeginUpdate();
      for (int index = 0; index < count; ++index)
      {
        string str = this.listBox1.Items[index].ToString();
        if (str.Length > 3)
          Convert.ToInt32(str.Split('-')[0]);
      }
      this.listBox1.EndUpdate();
    }

    private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      int ItemID = this.GetID();
      if (ItemID == -1)
        return;
      ticon ticon = IconList.List.Find((Predicate<ticon>) (p => p.ItemID.Equals(ItemID)));
      if (ticon == null)
        return;
      this.ItemIndex = ticon.ItemID;
      this.textBox2.Text = ticon.Name;
      this.textBox3.Text = ticon.Desc;
      this.pictureBox1.Image = (Image) new DatabaseHandle().IconFast(ticon.ItemID);
    }

    private void button1_Click(object sender, EventArgs e) => this.DialogResult = DialogResult.OK;

    private void button2_Click(object sender, EventArgs e)
    {
      this.ItemIndex = -1;
      this.ItemAmount = -1;
      this.DialogResult = DialogResult.OK;
    }

    private void button3_Click(object sender, EventArgs e) => this.Close();

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    public int GetIndexByComboBox(string comboBox)
    {
      try
      {
        return Convert.ToInt32(comboBox.Split(' ')[0]);
      }
      catch
      {
        return 0;
      }
    }

    private void LoadListBox()
    {
      this.listBox1.SelectedIndex = -1;
      this.MenuList.Clear();
      string Query = "SELECT a_index, a_name_usa FROM t_item WHERE a_job_flag ='" + this.mSortJob + "' ORDER BY a_index;";
      if (this.mSortJob == "-1")
        Query = "SELECT a_index, a_name_usa FROM t_item ORDER BY a_index;";
      this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, Query);
      this.listBox1.BeginUpdate();
      for (int index = 0; index < this.listBox1.Items.Count; ++index)
        this.MenuList.Add(this.listBox1.Items[index].ToString());
      this.listBox1.EndUpdate();
      this.listBox1.DataSource = (object) this.MenuList;
      this.listBox1.SelectedIndex = -1;
    }

    private void InitializeComponent()
    {
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (ItemPicker2));
      this.groupBox1 = new GroupBox();
      this.textBox1 = new TextBox();
      this.groupBox2 = new GroupBox();
      this.listBox1 = new CheckedListBox();
      this.button3 = new Button();
      this.button2 = new Button();
      this.button1 = new Button();
      this.groupBox3 = new GroupBox();
      this.textBox3 = new TextBox();
      this.textBox2 = new TextBox();
      this.pictureBox1 = new PictureBox();
      this.ClbSort = new CheckedListBox();
      this.groupBox4 = new GroupBox();
      this.tbAmount = new TextBox();
      this.label1 = new Label();
      this.groupBox1.SuspendLayout();
      this.groupBox2.SuspendLayout();
      this.groupBox3.SuspendLayout();
      ((ISupportInitialize) this.pictureBox1).BeginInit();
      this.groupBox4.SuspendLayout();
      this.SuspendLayout();
      this.groupBox1.Controls.Add((Control) this.textBox1);
      this.groupBox1.Location = new Point(12, 12);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(465, 52);
      this.groupBox1.TabIndex = 1;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Search";
      this.textBox1.BorderStyle = BorderStyle.FixedSingle;
      this.textBox1.Location = new Point(6, 19);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(450, 20);
      this.textBox1.TabIndex = 0;
      this.textBox1.TextChanged += new EventHandler(this.textBox1_TextChanged);
      this.groupBox2.Controls.Add((Control) this.listBox1);
      this.groupBox2.Controls.Add((Control) this.button3);
      this.groupBox2.Controls.Add((Control) this.button2);
      this.groupBox2.Controls.Add((Control) this.button1);
      this.groupBox2.Location = new Point(12, 70);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new Size(226, 363);
      this.groupBox2.TabIndex = 2;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "Items";
      this.listBox1.FormattingEnabled = true;
      this.listBox1.Location = new Point(6, 19);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new Size(214, 304);
      this.listBox1.TabIndex = 4;
      this.listBox1.ItemCheck += new ItemCheckEventHandler(this.listBox1_ItemCheck);
      this.listBox1.SelectedIndexChanged += new EventHandler(this.listBox1_SelectedIndexChanged_1);
      this.button3.FlatStyle = FlatStyle.Flat;
      this.button3.Location = new Point(165, 328);
      this.button3.Name = "button3";
      this.button3.Size = new Size(46, 23);
      this.button3.TabIndex = 3;
      this.button3.Text = "Close";
      this.button3.UseVisualStyleBackColor = true;
      this.button3.Click += new EventHandler(this.button3_Click);
      this.button2.FlatStyle = FlatStyle.Flat;
      this.button2.Location = new Point(104, 328);
      this.button2.Name = "button2";
      this.button2.Size = new Size(55, 23);
      this.button2.TabIndex = 2;
      this.button2.Text = "None";
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.button1.FlatStyle = FlatStyle.Flat;
      this.button1.Location = new Point(6, 328);
      this.button1.Name = "button1";
      this.button1.Size = new Size(92, 23);
      this.button1.TabIndex = 1;
      this.button1.Text = "Pick";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.groupBox3.Controls.Add((Control) this.textBox3);
      this.groupBox3.Controls.Add((Control) this.textBox2);
      this.groupBox3.Controls.Add((Control) this.pictureBox1);
      this.groupBox3.Location = new Point(244, 70);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Size = new Size(233, 132);
      this.groupBox3.TabIndex = 3;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "Preview";
      this.textBox3.BorderStyle = BorderStyle.FixedSingle;
      this.textBox3.Location = new Point(62, 45);
      this.textBox3.Multiline = true;
      this.textBox3.Name = "textBox3";
      this.textBox3.ReadOnly = true;
      this.textBox3.Size = new Size(162, 68);
      this.textBox3.TabIndex = 9;
      this.textBox2.BorderStyle = BorderStyle.FixedSingle;
      this.textBox2.Location = new Point(62, 19);
      this.textBox2.Name = "textBox2";
      this.textBox2.ReadOnly = true;
      this.textBox2.Size = new Size(162, 20);
      this.textBox2.TabIndex = 4;
      this.pictureBox1.BackColor = SystemColors.ButtonHighlight;
      this.pictureBox1.BackgroundImageLayout = ImageLayout.None;
      this.pictureBox1.Location = new Point(6, 19);
      this.pictureBox1.Name = "pictureBox1";
      this.pictureBox1.Size = new Size(50, 58);
      this.pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
      this.pictureBox1.TabIndex = 8;
      this.pictureBox1.TabStop = false;
      this.ClbSort.BackColor = SystemColors.Control;
      this.ClbSort.BorderStyle = BorderStyle.None;
      this.ClbSort.CheckOnClick = true;
      this.ClbSort.FormattingEnabled = true;
      this.ClbSort.Location = new Point(6, 19);
      this.ClbSort.MultiColumn = true;
      this.ClbSort.Name = "ClbSort";
      this.ClbSort.Size = new Size(221, 135);
      this.ClbSort.TabIndex = 4;
      this.ClbSort.ItemCheck += new ItemCheckEventHandler(this.ClbSort_ItemCheck);
      this.ClbSort.SelectedIndexChanged += new EventHandler(this.ClbSort_SelectedIndexChanged);
      this.groupBox4.Controls.Add((Control) this.ClbSort);
      this.groupBox4.Location = new Point(244, 208);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Size = new Size(233, 158);
      this.groupBox4.TabIndex = 5;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "Sort";
      this.tbAmount.Location = new Point(306, 373);
      this.tbAmount.Name = "tbAmount";
      this.tbAmount.Size = new Size(100, 20);
      this.tbAmount.TabIndex = 9;
      this.tbAmount.Text = "1";
      this.label1.AutoSize = true;
      this.label1.Location = new Point(254, 376);
      this.label1.Name = "label1";
      this.label1.Size = new Size(46, 13);
      this.label1.TabIndex = 8;
      this.label1.Text = "Amount:";
      this.ClientSize = new Size(483, 445);
      this.Controls.Add((Control) this.tbAmount);
      this.Controls.Add((Control) this.label1);
      this.Controls.Add((Control) this.groupBox4);
      this.Controls.Add((Control) this.groupBox3);
      this.Controls.Add((Control) this.groupBox2);
      this.Controls.Add((Control) this.groupBox1);
      this.Icon = (Icon) componentResourceManager.GetObject("$this.Icon");
      this.MaximizeBox = false;
      this.Name = nameof (ItemPicker2);
      this.StartPosition = FormStartPosition.CenterParent;
      this.Text = "Item Picker";
      this.Load += new EventHandler(this.ItemPicker_Load);
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.groupBox2.ResumeLayout(false);
      this.groupBox3.ResumeLayout(false);
      this.groupBox3.PerformLayout();
      ((ISupportInitialize) this.pictureBox1).EndInit();
      this.groupBox4.ResumeLayout(false);
      this.ResumeLayout(false);
      this.PerformLayout();
    }

    private void ClbSort_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.mSortJob = this.GetIndexByComboBox(this.ClbSort.Text).ToString();
      if (!(this.ClbSort.Text == "1"))
        return;
      this.LoadListBox();
    }

    private void ClbSort_ItemCheck(object sender, ItemCheckEventArgs e)
    {
      if (e.NewValue == CheckState.Checked && this.ClbSort.CheckedItems.Count > 0)
      {
        this.ClbSort.ItemCheck -= new ItemCheckEventHandler(this.ClbSort_ItemCheck);
        this.ClbSort.SetItemChecked(this.ClbSort.CheckedIndices[0], false);
        this.ClbSort.ItemCheck += new ItemCheckEventHandler(this.ClbSort_ItemCheck);
      }
      this.mSortJob = this.GetIndexByComboBox(this.ClbSort.Text).ToString();
      this.LoadListBox();
    }

    private void listBox1_SelectedIndexChanged_1(object sender, EventArgs e)
    {
      int ItemID = this.GetID();
      if (ItemID == -1)
        return;
      ticon ticon = IconList.List.Find((Predicate<ticon>) (p => p.ItemID.Equals(ItemID)));
      if (ticon == null)
        return;
      this.ItemIndex = ticon.ItemID;
      this.textBox2.Text = ticon.Name;
      this.textBox3.Text = ticon.Desc;
      this.pictureBox1.Image = (Image) new DatabaseHandle().IconFast(ticon.ItemID);
    }

    private void listBox1_ItemCheck(object sender, ItemCheckEventArgs e)
    {
      int id = this.GetID();
      if (id == -1 || e.NewValue != CheckState.Checked)
        return;
      ItemPicker2_items itemPicker2Items = new ItemPicker2_items();
      itemPicker2Items.ID = id;
      if (this.tbAmount.Text == "")
        itemPicker2Items.Amount = 1;
      else
        itemPicker2Items.Amount = Convert.ToInt32(this.tbAmount.Text);
    }
  }
}
