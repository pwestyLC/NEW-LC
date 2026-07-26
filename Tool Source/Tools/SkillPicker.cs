// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.SkillPicker
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
  public class SkillPicker : Form
  {
    public int SkillIndex = -1;
    public List<string> MenuList = new List<string>();
    public List<string> MenuListSearch = new List<string>();
    private IContainer components = (IContainer) null;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    public string[] menuArray = new string[2]
    {
      "a_index",
      "a_name_usa"
    };
    private string Host = SkillEditor.connection.Settings.SqlHost;
    private string User = SkillEditor.connection.Settings.SqlUser;
    private string Password = SkillEditor.connection.Settings.SqlPassword;
    private string Database = SkillEditor.connection.Settings.SqlDatabase;
    private GroupBox groupBox1;
    private TextBox textBox1;
    private GroupBox groupBox2;
    private ListBox listBox1;
    private GroupBox groupBox3;
    private TextBox tbSkillName;
    private TextBox tbSkillDesc;
    private Button btnNone;
    private Button btnSelect;
    private Button btnClose;
    private GroupBox gbSort;
    private CheckedListBox ClbSort;
    private Label label2;
    private Label label1;
    private TextBox textBox2;
    private PictureBox pictureBox1;
    public string mSortJob = "-1";

    public SkillPicker() => this.InitializeComponent();

    private void SkillPicker_Load(object sender, EventArgs e)
    {
      this.LoadStartup();
      this.MenuList.Clear();
      for (int index = 0; index < IconSkill.List.Count<SkillIcon>(); ++index)
        this.MenuList.Add(IconSkill.List[index].SkillID.ToString() + " - " + IconSkill.List[index].Name.ToString());
      this.listBox1.DataSource = (object) this.MenuList;
    }

    private void LoadStartup()
    {
      this.ClbSort.Items.AddRange(new object[14]
      {
        (object) "-1 - All",
        (object) "0 - Titan",
        (object) "1 - Knight",
        (object) "2 - Healer",
        (object) "3 - Mage",
        (object) "4 - Rogue",
        (object) "5 - Sorcerer",
        (object) "6 - NightShadow",
        (object) "7 - Ex-Rogue",
        (object) "8 - Ex-Mage",
        (object) "9 - Nothing",
        (object) "10 - Pet",
        (object) "11 - APet",
        (object) "999 - All"
      });
    }

    private int GetID()
    {
      int result = -1;
      int.TryParse(this.listBox1.Text.Split(' ')[0], out result);
      return result;
    }

    private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      int SkillID = this.GetID();
      if (SkillID == -1)
        return;
      SkillIcon skillIcon = IconSkill.List.Find((Predicate<SkillIcon>) (g => g.SkillID.Equals(SkillID)));
      if (skillIcon == null)
        return;
      this.SkillIndex = skillIcon.SkillID;
      this.tbSkillName.Text = skillIcon.Name;
      this.tbSkillDesc.Text = skillIcon.Desc;
      this.textBox2.Text = skillIcon.Tooltip;
      this.pictureBox1.Image = (Image) new DatabaseHandle().SkillsFast(skillIcon.SkillID);
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

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (SkillPicker));
      this.groupBox1 = new GroupBox();
      this.textBox1 = new TextBox();
      this.groupBox2 = new GroupBox();
      this.btnNone = new Button();
      this.btnSelect = new Button();
      this.listBox1 = new ListBox();
      this.groupBox3 = new GroupBox();
      this.tbSkillDesc = new TextBox();
      this.tbSkillName = new TextBox();
      this.pictureBox1 = new PictureBox();
      this.btnClose = new Button();
      this.gbSort = new GroupBox();
      this.ClbSort = new CheckedListBox();
      this.textBox2 = new TextBox();
      this.label1 = new Label();
      this.label2 = new Label();
      this.groupBox1.SuspendLayout();
      this.groupBox2.SuspendLayout();
      this.groupBox3.SuspendLayout();
      ((ISupportInitialize) this.pictureBox1).BeginInit();
      this.gbSort.SuspendLayout();
      this.SuspendLayout();
      this.groupBox1.Controls.Add((Control) this.textBox1);
      this.groupBox1.Location = new Point(12, 12);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(490, 52);
      this.groupBox1.TabIndex = 0;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Search";
      this.textBox1.BorderStyle = BorderStyle.FixedSingle;
      this.textBox1.Location = new Point(6, 19);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(450, 20);
      this.textBox1.TabIndex = 1;
      this.textBox1.TextChanged += new EventHandler(this.textBox1_TextChanged);
      this.groupBox2.Controls.Add((Control) this.btnNone);
      this.groupBox2.Controls.Add((Control) this.btnSelect);
      this.groupBox2.Controls.Add((Control) this.listBox1);
      this.groupBox2.Location = new Point(12, 70);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new Size(226, 363);
      this.groupBox2.TabIndex = 1;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "Skills";
      this.btnNone.FlatStyle = FlatStyle.Flat;
      this.btnNone.Location = new Point(99, 334);
      this.btnNone.Name = "btnNone";
      this.btnNone.Size = new Size(63, 23);
      this.btnNone.TabIndex = 4;
      this.btnNone.Text = "None";
      this.btnNone.UseVisualStyleBackColor = true;
      this.btnNone.Click += new EventHandler(this.btnNone_Click);
      this.btnSelect.FlatStyle = FlatStyle.Flat;
      this.btnSelect.Location = new Point(6, 334);
      this.btnSelect.Name = "btnSelect";
      this.btnSelect.Size = new Size(87, 23);
      this.btnSelect.TabIndex = 3;
      this.btnSelect.Text = "Select";
      this.btnSelect.UseVisualStyleBackColor = true;
      this.btnSelect.Click += new EventHandler(this.btnSelect_Click);
      this.listBox1.FormattingEnabled = true;
      this.listBox1.Location = new Point(6, 19);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new Size(205, 303);
      this.listBox1.TabIndex = 0;
      this.listBox1.SelectedIndexChanged += new EventHandler(this.listBox1_SelectedIndexChanged);
      this.groupBox3.Controls.Add((Control) this.label2);
      this.groupBox3.Controls.Add((Control) this.label1);
      this.groupBox3.Controls.Add((Control) this.textBox2);
      this.groupBox3.Controls.Add((Control) this.tbSkillDesc);
      this.groupBox3.Controls.Add((Control) this.tbSkillName);
      this.groupBox3.Controls.Add((Control) this.pictureBox1);
      this.groupBox3.Location = new Point(244, 70);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Size = new Size(258, 132);
      this.groupBox3.TabIndex = 2;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "Preview";
      this.tbSkillDesc.BackColor = SystemColors.Control;
      this.tbSkillDesc.BorderStyle = BorderStyle.FixedSingle;
      this.tbSkillDesc.Location = new Point(53, 83);
      this.tbSkillDesc.Multiline = true;
      this.tbSkillDesc.Name = "tbSkillDesc";
      this.tbSkillDesc.ReadOnly = true;
      this.tbSkillDesc.Size = new Size(195, 20);
      this.tbSkillDesc.TabIndex = 2;
      this.tbSkillName.BackColor = SystemColors.Control;
      this.tbSkillName.BorderStyle = BorderStyle.FixedSingle;
      this.tbSkillName.Location = new Point(73, 20);
      this.tbSkillName.Name = "tbSkillName";
      this.tbSkillName.ReadOnly = true;
      this.tbSkillName.Size = new Size(151, 20);
      this.tbSkillName.TabIndex = 1;
      this.pictureBox1.BackColor = SystemColors.ButtonHighlight;
      this.pictureBox1.Location = new Point(6, 19);
      this.pictureBox1.Name = "pictureBox1";
      this.pictureBox1.Size = new Size(50, 58);
      this.pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
      this.pictureBox1.TabIndex = 0;
      this.pictureBox1.TabStop = false;
      this.btnClose.FlatStyle = FlatStyle.Flat;
      this.btnClose.Location = new Point(180, 404);
      this.btnClose.Name = "btnClose";
      this.btnClose.Size = new Size(52, 23);
      this.btnClose.TabIndex = 5;
      this.btnClose.Text = "Close";
      this.btnClose.UseVisualStyleBackColor = true;
      this.btnClose.Click += new EventHandler(this.btnClose_Click);
      this.gbSort.Controls.Add((Control) this.ClbSort);
      this.gbSort.Location = new Point(250, 208);
      this.gbSort.Name = "gbSort";
      this.gbSort.Size = new Size(252, 225);
      this.gbSort.TabIndex = 6;
      this.gbSort.TabStop = false;
      this.gbSort.Text = "Sort";
      this.ClbSort.BackColor = SystemColors.Control;
      this.ClbSort.BorderStyle = BorderStyle.None;
      this.ClbSort.CheckOnClick = true;
      this.ClbSort.FormattingEnabled = true;
      this.ClbSort.Location = new Point(15, 19);
      this.ClbSort.MultiColumn = true;
      this.ClbSort.Name = "ClbSort";
      this.ClbSort.Size = new Size(231, 135);
      this.ClbSort.TabIndex = 0;
      this.ClbSort.ItemCheck += new ItemCheckEventHandler(this.ClbSort_ItemCheck);
      this.ClbSort.SelectedIndexChanged += new EventHandler(this.ClbSort_SelectedIndexChanged);
      this.textBox2.BackColor = SystemColors.Control;
      this.textBox2.BorderStyle = BorderStyle.FixedSingle;
      this.textBox2.Location = new Point(53, 106);
      this.textBox2.Multiline = true;
      this.textBox2.Name = "textBox2";
      this.textBox2.ReadOnly = true;
      this.textBox2.Size = new Size(195, 20);
      this.textBox2.TabIndex = 3;
      this.label1.AutoSize = true;
      this.label1.Location = new Point(10, 85);
      this.label1.Name = "label1";
      this.label1.Size = new Size(35, 13);
      this.label1.TabIndex = 4;
      this.label1.Text = "Desc:";
      this.label2.AutoSize = true;
      this.label2.Location = new Point(3, 108);
      this.label2.Name = "label2";
      this.label2.Size = new Size(42, 13);
      this.label2.TabIndex = 5;
      this.label2.Text = "Tooltip:";
      this.ClientSize = new Size(504, 445);
      this.Controls.Add((Control) this.gbSort);
      this.Controls.Add((Control) this.btnClose);
      this.Controls.Add((Control) this.groupBox3);
      this.Controls.Add((Control) this.groupBox2);
      this.Controls.Add((Control) this.groupBox1);
      this.Icon = (Icon) componentResourceManager.GetObject("$this.Icon");
      this.Name = nameof (SkillPicker);
      this.StartPosition = FormStartPosition.CenterParent;
      this.Text = "Skill Picker";
      this.Load += new EventHandler(this.SkillPicker_Load);
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.groupBox2.ResumeLayout(false);
      this.groupBox3.ResumeLayout(false);
      this.groupBox3.PerformLayout();
      ((ISupportInitialize) this.pictureBox1).EndInit();
      this.gbSort.ResumeLayout(false);
      this.ResumeLayout(false);
    }

    private void LoadListBox()
    {
      this.listBox1.SelectedIndex = -1;
      this.MenuList.Clear();
      string Query = "SELECT a_index, a_name_usa FROM t_skill WHERE a_job ='" + this.mSortJob + "' ORDER BY a_index;";
      if (this.mSortJob == "-1")
        Query = "SELECT a_index, a_name_usa FROM t_skill ORDER BY a_index;";
      this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, Query);
      for (int index = 0; index < this.listBox1.Items.Count; ++index)
        this.MenuList.Add(this.listBox1.Items[index].ToString());
      this.listBox1.DataSource = (object) this.MenuList;
      this.listBox1.SelectedIndex = -1;
    }

    public bool SearchString(string s) => s.ToUpper().Contains(this.textBox1.Text.ToUpper());

    private void btnSelect_Click(object sender, EventArgs e) => this.DialogResult = DialogResult.OK;

    private void btnNone_Click(object sender, EventArgs e)
    {
      this.SkillIndex = -1;
      this.DialogResult = DialogResult.OK;
    }

    private void btnClose_Click(object sender, EventArgs e) => this.Close();

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

    private void textBox1_TextChanged(object sender, EventArgs e)
    {
      this.MenuListSearch = this.MenuList.FindAll(new Predicate<string>(this.SearchString));
      this.listBox1.DataSource = (object) this.MenuListSearch;
    }
  }
}
