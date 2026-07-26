// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.ItemSearch
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA
{
  public class ItemSearch : Form
  {
    public static Connection connection = new Connection();
    private string Host = ItemSearch.connection.Settings.SqlHost;
    private string User = ItemSearch.connection.Settings.SqlUser;
    private string Password = ItemSearch.connection.Settings.SqlPassword;
    private string Database = ItemSearch.connection.Settings.SqlDatabase;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    public string rowName = "a_index";
    public string[] menuArray = new string[2]
    {
      "a_index",
      "a_name"
    };
    public string[] SearchMenu = new string[2]
    {
      "a_index",
      "a_name"
    };
    public List<string> MenuList = new List<string>();
    public List<string> MenuListSearch = new List<string>();
    private IContainer components = (IContainer) null;
    public string name;
    public int index;
    public string test2;
    public string varf2;
    private ListBox listBox1;
    private Button button1;
    private TextBox textBox1;
    private Button button2;
    private Button button3;
    private RichTextBox richTextBox1;
    private TextBox textBox2;
    private PictureBox pictureBox1;
    private GroupBox groupBox1;
    private TextBox textBox3;
    private Label label1;
    private TextBox textBox4;
    private TextBox textBox5;
    private TextBox textBox6;

    public ItemSearch() => this.InitializeComponent();

    public int GetIndex()
    {
      try
      {
        return Convert.ToInt32(this.listBox1.Text.Split(' ')[0]);
      }
      catch
      {
        return 0;
      }
    }

    private void LoadListBox()
    {
      this.MenuList.Clear();
      this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, "select a_index, a_name from t_item ORDER BY a_index;");
      for (int index = 0; index < this.listBox1.Items.Count; ++index)
        this.MenuList.Add(this.listBox1.Items[index].ToString());
      this.listBox1.DataSource = (object) this.MenuList;
    }

    public void SearchList(string searchString)
    {
      searchString = searchString.Replace("\\", "\\\\").Replace("'", "\\'");
      string lower = searchString.ToLower();
      string upper = searchString.ToUpper();
      string str = "";
      if (searchString.Length > 1)
        str = char.ToUpper(searchString[0]).ToString() + searchString.Substring(1);
      this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, "select a_index, a_name from t_item WHERE a_name LIKE '%" + searchString + "%' OR a_index LIKE '%" + searchString + "%' OR a_name LIKE '%" + lower + "%' OR a_index  LIKE '%" + lower + "%' OR a_name LIKE '%" + upper + "%' OR a_index LIKE '%" + upper + "%' OR a_name LIKE '%" + str + "%' OR a_index LIKE '%" + str + "%' ORDER BY a_index;");
    }

    private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (this.listBox1.SelectedIndex != -1)
        this.textBox1.Text = this.GetIndex().ToString();
      string Query = " select a_index , a_type_idx , a_subtype_idx , a_enable , a_name , a_descr , a_job_flag , a_flag , a_wearing , a_num_0 , a_num_1 , a_num_2, a_num_3 , a_num_4 , a_level , a_level2 , a_weight , a_price , a_max_use , a_drop_prob_10 , a_need_item0 , a_need_item1 , a_need_item2 , a_need_item3 , a_need_item4 , a_need_item5 , a_need_item6 , a_need_item7 , a_need_item8 , a_need_item9 , a_need_item_count0 , a_need_item_count1 , a_need_item_count2 , a_need_item_count3 , a_need_item_count4 , a_need_item_count5 , a_need_item_count6 , a_need_item_count7 , a_need_item_count8 , a_need_item_count9 , a_need_sskill , a_need_sskill_level , a_need_sskill2 , a_need_sskill_level2 , a_zone_flag , a_file_smc , a_texture_id , a_texture_row , a_texture_col , b_todo_delete , a_set_0 , a_set_1 , a_set_2 , a_set_3 , a_set_4 , a_set , a_grade , a_fame , a_rare_index_0 , a_rare_index_1 , a_rare_index_2 , a_rare_index_3 , a_rare_index_4 , a_rare_index_5 , a_rare_index_6 , a_rare_index_7 , a_rare_index_8 , a_rare_index_9 , a_rare_prob_0 , a_rare_prob_1 , a_rare_prob_2 , a_rare_prob_3 , a_rare_prob_4 , a_rare_prob_5 , a_rare_prob_6 , a_rare_prob_7 , a_rare_prob_8 , a_rare_prob_9 , a_effect_name, a_attack_effect_name, a_damage_effect_name, a_quest_trigger_count , a_quest_trigger_ids , a_origin_variation1 , a_origin_variation2 , a_origin_variation3 , a_origin_variation4 , a_origin_variation5 , a_origin_variation6 , a_rvr_value , a_rvr_grade , a_durability , a_castle_war from t_item WHERE a_index ='" + this.textBox1.Text + "';";
      string[] rows = new string[93]
      {
        "a_index",
        "a_type_idx",
        "a_subtype_idx",
        "a_enable",
        "a_name",
        "a_descr",
        "a_job_flag",
        "a_flag",
        "a_wearing",
        "a_num_0",
        "a_num_1",
        "a_num_2",
        "a_num_3",
        "a_num_4",
        "a_level",
        "a_level2",
        "a_weight",
        "a_price",
        "a_max_use",
        "a_drop_prob_10",
        "a_need_item0",
        "a_need_item1",
        "a_need_item2",
        "a_need_item3",
        "a_need_item4",
        "a_need_item5",
        "a_need_item6",
        "a_need_item7",
        "a_need_item8",
        "a_need_item9",
        "a_need_item_count0",
        "a_need_item_count1",
        "a_need_item_count2",
        "a_need_item_count3",
        "a_need_item_count4",
        "a_need_item_count5",
        "a_need_item_count6",
        "a_need_item_count7",
        "a_need_item_count8",
        "a_need_item_count9",
        "a_need_sskill",
        "a_need_sskill_level",
        "a_need_sskill2",
        "a_need_sskill_level2",
        "a_zone_flag",
        "a_file_smc",
        "a_texture_id",
        "a_texture_row",
        "a_texture_col",
        "b_todo_delete",
        "a_set_0",
        "a_set_1",
        "a_set_2",
        "a_set_3",
        "a_set_4",
        "a_set",
        "a_grade",
        "a_fame",
        "a_rare_index_0",
        "a_rare_index_1",
        "a_rare_index_2",
        "a_rare_index_3",
        "a_rare_index_4",
        "a_rare_index_5",
        "a_rare_index_6",
        "a_rare_index_7",
        "a_rare_index_8",
        "a_rare_index_9",
        "a_rare_prob_0",
        "a_rare_prob_1",
        "a_rare_prob_2",
        "a_rare_prob_3",
        "a_rare_prob_4",
        "a_rare_prob_5",
        "a_rare_prob_6",
        "a_rare_prob_7",
        "a_rare_prob_8",
        "a_rare_prob_9",
        "a_effect_name",
        "a_attack_effect_name",
        "a_damage_effect_name",
        "a_quest_trigger_count",
        "a_quest_trigger_ids",
        "a_origin_variation1",
        "a_origin_variation2",
        "a_origin_variation3",
        "a_origin_variation4",
        "a_origin_variation5",
        "a_origin_variation6",
        "a_rvr_value",
        "a_rvr_grade",
        "a_durability",
        "a_castle_war"
      };
      Query.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'");
      string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query, rows);
      this.richTextBox1.Text = strArray[5];
      this.textBox4.Text = strArray[46];
      this.textBox5.Text = strArray[47];
      this.textBox6.Text = strArray[48];
      try
      {
        this.pictureBox1.Image = (Image) this.databaseHandle.IconItem(int.Parse(this.textBox4.Text), int.Parse(this.textBox5.Text), int.Parse(this.textBox6.Text));
      }
      catch
      {
      }
    }

    private void button1_Click(object sender, EventArgs e) => this.varf2 = this.textBox1.Text;

    private void button2_Click(object sender, EventArgs e) => this.varf2 = this.textBox2.Text;

    private void button3_Click(object sender, EventArgs e) => this.Close();

    public bool SearchString(string s) => s.ToUpper().Contains(this.textBox3.Text.ToUpper());

    private void textBox3_TextChanged(object sender, EventArgs e)
    {
      this.MenuListSearch = this.MenuList.FindAll(new Predicate<string>(this.SearchString));
      this.listBox1.DataSource = (object) this.MenuListSearch;
    }

    private void ItemSearch_Load(object sender, EventArgs e) => this.LoadListBox();

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (ItemSearch));
      this.listBox1 = new ListBox();
      this.textBox1 = new TextBox();
      this.button1 = new Button();
      this.button2 = new Button();
      this.button3 = new Button();
      this.richTextBox1 = new RichTextBox();
      this.textBox2 = new TextBox();
      this.pictureBox1 = new PictureBox();
      this.groupBox1 = new GroupBox();
      this.textBox3 = new TextBox();
      this.label1 = new Label();
      this.textBox4 = new TextBox();
      this.textBox5 = new TextBox();
      this.textBox6 = new TextBox();
      ((ISupportInitialize) this.pictureBox1).BeginInit();
      this.groupBox1.SuspendLayout();
      this.SuspendLayout();
      this.listBox1.FormattingEnabled = true;
      this.listBox1.Location = new Point(12, 78);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new Size(214, 355);
      this.listBox1.TabIndex = 0;
      this.listBox1.SelectedIndexChanged += new EventHandler(this.listBox1_SelectedIndexChanged);
      this.textBox1.Location = new Point(232, 413);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(26, 20);
      this.textBox1.TabIndex = 1;
      this.textBox1.Visible = false;
      this.button1.Location = new Point(22, 445);
      this.button1.Name = "button1";
      this.button1.Size = new Size(52, 23);
      this.button1.TabIndex = 2;
      this.button1.Text = "Pick";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.button2.Location = new Point(92, 445);
      this.button2.Name = "button2";
      this.button2.Size = new Size(52, 23);
      this.button2.TabIndex = 3;
      this.button2.Text = "No Item";
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.button3.Location = new Point(164, 445);
      this.button3.Name = "button3";
      this.button3.Size = new Size(52, 23);
      this.button3.TabIndex = 4;
      this.button3.Text = "Close";
      this.button3.UseVisualStyleBackColor = true;
      this.button3.Click += new EventHandler(this.button3_Click);
      this.richTextBox1.Location = new Point(68, 474);
      this.richTextBox1.Name = "richTextBox1";
      this.richTextBox1.ReadOnly = true;
      this.richTextBox1.Size = new Size(158, 112);
      this.richTextBox1.TabIndex = 5;
      this.richTextBox1.Text = "";
      this.textBox2.Location = new Point(232, 381);
      this.textBox2.Name = "textBox2";
      this.textBox2.Size = new Size(15, 20);
      this.textBox2.TabIndex = 6;
      this.textBox2.Text = "-1";
      this.textBox2.Visible = false;
      this.pictureBox1.BackColor = SystemColors.ButtonHighlight;
      this.pictureBox1.BackgroundImageLayout = ImageLayout.None;
      this.pictureBox1.Location = new Point(12, 504);
      this.pictureBox1.Name = "pictureBox1";
      this.pictureBox1.Size = new Size(50, 58);
      this.pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
      this.pictureBox1.TabIndex = 7;
      this.pictureBox1.TabStop = false;
      this.groupBox1.Controls.Add((Control) this.textBox3);
      this.groupBox1.Controls.Add((Control) this.label1);
      this.groupBox1.Location = new Point(12, 12);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(214, 56);
      this.groupBox1.TabIndex = 8;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Search";
      this.textBox3.BorderStyle = BorderStyle.FixedSingle;
      this.textBox3.Location = new Point(44, 24);
      this.textBox3.Name = "textBox3";
      this.textBox3.Size = new Size(160, 20);
      this.textBox3.TabIndex = 1;
      this.textBox3.TextChanged += new EventHandler(this.textBox3_TextChanged);
      this.label1.AutoSize = true;
      this.label1.Location = new Point(7, 27);
      this.label1.Name = "label1";
      this.label1.Size = new Size(31, 13);
      this.label1.TabIndex = 0;
      this.label1.Text = "Text:";
      this.textBox4.Location = new Point(232, 188);
      this.textBox4.Name = "textBox4";
      this.textBox4.Size = new Size(33, 20);
      this.textBox4.TabIndex = 9;
      this.textBox4.Visible = false;
      this.textBox5.Location = new Point(232, 214);
      this.textBox5.Name = "textBox5";
      this.textBox5.Size = new Size(33, 20);
      this.textBox5.TabIndex = 10;
      this.textBox5.Visible = false;
      this.textBox6.Location = new Point(232, 240);
      this.textBox6.Name = "textBox6";
      this.textBox6.Size = new Size(33, 20);
      this.textBox6.TabIndex = 11;
      this.textBox6.Visible = false;
      this.ClientSize = new Size(231, 601);
      this.Controls.Add((Control) this.textBox6);
      this.Controls.Add((Control) this.textBox5);
      this.Controls.Add((Control) this.textBox4);
      this.Controls.Add((Control) this.groupBox1);
      this.Controls.Add((Control) this.pictureBox1);
      this.Controls.Add((Control) this.textBox2);
      this.Controls.Add((Control) this.richTextBox1);
      this.Controls.Add((Control) this.button3);
      this.Controls.Add((Control) this.button2);
      this.Controls.Add((Control) this.button1);
      this.Controls.Add((Control) this.textBox1);
      this.Controls.Add((Control) this.listBox1);
      this.Icon = (Icon) componentResourceManager.GetObject("$this.Icon");
      this.MaximizeBox = false;
      this.MinimizeBox = false;
      this.Name = nameof (ItemSearch);
      this.Text = "Item Search";
      this.Load += new EventHandler(this.ItemSearch_Load);
      ((ISupportInitialize) this.pictureBox1).EndInit();
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
