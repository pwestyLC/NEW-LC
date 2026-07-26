// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using LcDevPack_TeamDamonA.Properties;
using MySqlConnector;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige
{
  public class Prestige : Form
  {
    public static Connection connection = new Connection();
    private string Host = LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.connection.Settings.SqlHost;
    private string User = LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.connection.Settings.SqlUser;
    private string Password = LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.connection.Settings.SqlPassword;
    private string Database = LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.connection.Settings.SqlDatabase;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    public string _ClientPath = LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.connection.Settings.ClientPath;
    public string rowName = "a_index";
    public List<string> MenuList = new List<string>();
    public List<string> MenuListSearch = new List<string>();
    private DataTable table = new DataTable();
    private DataTable table2 = new DataTable();
    private MySqlCommand command;
    private MySqlDataAdapter adapter;
    private BindingManagerBase managerBase;
    private BindingManagerBase managerBase2;
    private MySqlCommandBuilder builder;
    private IContainer components = (IContainer) null;
    private MySqlDataAdapter sda;
    private BindingSource bSource;
    private DataTable dbdataset;
    private GroupBox groupBox1;
    private Button button1;
    private Label label2;
    private Label label1;
    private ListBox listBox1;
    private string country;
    public static string namee;
    private string language = LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.connection.Settings.Language;
    public string[] menuArray = new string[2]
    {
      "a_index",
      "a_name"
    };
    public string[] menuArrayGER = new string[2]
    {
      "a_index",
      "a_name"
    };
    public string[] menuArrayPOL = new string[2]
    {
      "a_index",
      "a_name"
    };
    public string[] menuArrayBRA = new string[2]
    {
      "a_index",
      "a_name"
    };
    public string[] menuArrayRUS = new string[2]
    {
      "a_index",
      "a_name"
    };
    public string[] menuArrayFRA = new string[2]
    {
      "a_index",
      "a_name"
    };
    public string[] menuArrayESP = new string[2]
    {
      "a_index",
      "a_name"
    };
    public string[] menuArrayMEX = new string[2]
    {
      "a_index",
      "a_name"
    };
    public string[] menuArrayTHA = new string[2]
    {
      "a_index",
      "a_name"
    };
    public string[] menuArrayITA = new string[2]
    {
      "a_index",
      "a_name"
    };
    private GroupBox groupBox5;
    private TextBox textBox1;
    private Label label7;
    private GroupBox groupBox2;
    private TextBox textBox2;
    private Label label3;
    private GroupBox groupBox4;
    private TextBox tb_reward_qty;
    private Label label9;
    private Button button5;
    private TextBox tb_reward_name;
    private TextBox tb_reward_id;
    private PictureBox pictureBox2;
    private Label label10;
    private Label label11;
    private Label label15;
    private Label label4;
    private Label label5;
    private GroupBox groupBox3;
    private TextBox textBox3;
    private Label label6;
    private Button button2;
    private TextBox textBox4;
    private TextBox textBox7;
    private PictureBox pictureBox1;
    private Label label8;
    private Label label12;
    private Label label13;
    private Label label14;
    private TextBox textBox12;
    private GroupBox groupBox6;
    private TextBox textBox8;
    private TextBox textBox6;
    private TextBox textBox5;
    private TextBox textBox9;
    private TextBox textBox10;
    private TextBox textBox13;
    private Label label17;
    private TextBox textBox11;
    private Label label16;
    public string[] menuArrayUSA = new string[2]
    {
      "a_index",
      "a_name"
    };

    public Prestige()
    {
      this.InitializeComponent();
      this.LoadListBox();
    }

    private string StringFromLanguage()
    {
      if (this.language == "GER")
      {
        LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.namee = "a_name";
        return LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.namee;
      }
      if (this.language == "POL")
      {
        LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.namee = "a_name";
        return LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.namee;
      }
      if (this.language == "BRA")
      {
        LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.namee = "a_name";
        return LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.namee;
      }
      if (this.language == "RUS")
      {
        LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.namee = "a_name";
        return LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.namee;
      }
      if (this.language == "FRA")
      {
        LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.namee = "a_name";
        return LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.namee;
      }
      if (this.language == "ESP")
      {
        LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.namee = "a_name";
        return LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.namee;
      }
      if (this.language == "MEX")
      {
        LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.namee = "a_name";
        return LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.namee;
      }
      if (this.language == "THA")
      {
        LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.namee = "a_name";
        return LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.namee;
      }
      if (this.language == "ITA")
      {
        LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.namee = "a_name";
        return LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.namee;
      }
      if (!(this.language == "USA"))
        return (string) null;
      LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.namee = "a_name";
      return LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.namee;
    }

    public void SearchList(string searchString)
    {
      LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.namee = this.StringFromLanguage();
      string Query = "select a_index, " + LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.namee + " from t_prestige WHERE " + LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.namee + " LIKE '%" + searchString + "%' ORDER BY a_index;";
      if (this.language == "GER")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayGER, this.Host, this.User, this.Password, this.Database, Query);
      else if (this.language == "BRA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayBRA, this.Host, this.User, this.Password, this.Database, Query);
      else if (this.language == "RUS")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayRUS, this.Host, this.User, this.Password, this.Database, Query);
      else if (this.language == "ESP")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayESP, this.Host, this.User, this.Password, this.Database, Query);
      else if (this.language == "MEX")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayMEX, this.Host, this.User, this.Password, this.Database, Query);
      else if (this.language == "THA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayTHA, this.Host, this.User, this.Password, this.Database, Query);
      else if (this.language == "ITA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayITA, this.Host, this.User, this.Password, this.Database, Query);
      else if (this.language == "USA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayUSA, this.Host, this.User, this.Password, this.Database, Query);
      else
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, Query);
    }

    private void LoadListBox()
    {
      this.listBox1.SelectedIndex = -1;
      this.MenuList.Clear();
      LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.namee = this.StringFromLanguage();
      string Query = "SELECT a_index," + LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.namee + " FROM t_prestige ORDER BY a_index;";
      if (this.language == "GER")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayGER, this.Host, this.User, this.Password, this.Database, Query);
      else if (this.language == "BRA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayBRA, this.Host, this.User, this.Password, this.Database, Query);
      else if (this.language == "RUS")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayRUS, this.Host, this.User, this.Password, this.Database, Query);
      else if (this.language == "ESP")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayESP, this.Host, this.User, this.Password, this.Database, Query);
      else if (this.language == "MEX")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayMEX, this.Host, this.User, this.Password, this.Database, Query);
      else if (this.language == "THA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayTHA, this.Host, this.User, this.Password, this.Database, Query);
      else if (this.language == "ITA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayITA, this.Host, this.User, this.Password, this.Database, Query);
      else if (this.language == "USA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayUSA, this.Host, this.User, this.Password, this.Database, Query);
      else
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, Query);
      for (int index = 0; index < this.listBox1.Items.Count; ++index)
        this.MenuList.Add(this.listBox1.Items[index].ToString());
      this.listBox1.DataSource = (object) this.MenuList;
    }

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

    private int GetID()
    {
      int result = -1;
      int.TryParse(this.textBox6.Text.Split(' ')[0], out result);
      return result;
    }

    private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.namee = this.StringFromLanguage();
      this.ClearBox();
      if (this.listBox1.SelectedIndex != -1)
        this.textBox5.Text = this.GetIndex().ToString();
      string Query = "select a_index, " + LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.namee + ", a_points, a_premium_points, a_level, a_season FROM t_prestige WHERE a_index ='" + this.textBox5.Text + "';";
      string[] rows = new string[6]
      {
        "a_index",
        LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.namee,
        "a_level",
        "a_points",
        "a_premium_points",
        "a_season"
      };
      Query.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'");
      string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query, rows);
      this.textBox5.Text = strArray[0];
      this.textBox6.Text = strArray[1];
      this.textBox2.Text = strArray[2];
      this.textBox9.Text = strArray[3];
      this.textBox10.Text = strArray[4];
      this.textBox8.Text = strArray[5];
    }

    private void Reward_List(object sender, EventArgs e)
    {
      LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.namee = this.StringFromLanguage();
      this.ClearBox();
      if (this.listBox1.SelectedIndex != -1)
        this.textBox2.Text = this.GetIndex().ToString();
      string Query = "select a_index, a_prestige_idx, a_item_idx, a_item_count, a_premium_item_idx, a_premium_item_count FROM t_prestige_reward WHERE a_prestige_idx ='" + this.textBox2.Text + "';";
      string[] rows = new string[6]
      {
        "a_index",
        "a_prestige_idx",
        "a_item_idx",
        "a_item_count",
        "a_premium_item_idx",
        "a_premium_item_count"
      };
      Query.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'");
      string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query, rows);
      this.textBox11.Text = strArray[0];
      this.textBox13.Text = strArray[1];
      this.tb_reward_id.Text = strArray[2];
      this.tb_reward_qty.Text = strArray[3];
      this.textBox7.Text = strArray[4];
      this.textBox3.Text = strArray[5];
    }

    private void ClearBox()
    {
    }

    private void textBox6_TextChanged(object sender, EventArgs e)
    {
    }

    private void textBox5_TextChanged(object sender, EventArgs e)
    {
    }

    private void exitToolStripMenuItem_Click(object sender, EventArgs e) => this.Close();

    private void button1_Click(object sender, EventArgs e)
    {
      LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.namee = this.StringFromLanguage();
      string str = this.textBox6.Text.Replace("'", "\\'").Replace("\"", "\\\"");
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_prestige SET " + LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige.namee + "  = '" + str + "', a_points = '" + this.textBox9.Text + "', a_premium_points = '" + this.textBox10.Text + "', a_season = '" + this.textBox8.Text + "' WHERE a_index = '" + this.textBox5.Text + "'");
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_prestige_reward SET a_item_idx  = '" + this.tb_reward_id.Text + "', a_item_count = '" + this.tb_reward_qty.Text + "', a_premium_item_idx = '" + this.textBox7.Text + "',  a_premium_item_count = '" + this.textBox3.Text + "' WHERE a_index = '" + this.textBox11.Text + "'");
      int num = (int) MessageBox.Show("Update", "Completed", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
      int selectedIndex = this.listBox1.SelectedIndex;
      if (this.textBox1.Text != "")
        this.SearchList(this.textBox1.Text);
      else
        this.LoadListBox();
      this.listBox1.SelectedIndex = selectedIndex;
    }

    public bool SearchString(string s) => s.ToUpper().Contains(this.textBox1.Text.ToUpper());

    private void textBox1_TextChanged(object sender, EventArgs e)
    {
      this.MenuListSearch = this.MenuList.FindAll(new Predicate<string>(this.SearchString));
      this.listBox1.DataSource = (object) this.MenuListSearch;
    }

    private void tb_reward_id_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox2.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.tb_reward_id.Text.Trim()));
      this.tb_reward_name.Text = this.databaseHandle.ItemNameFast(int.Parse(this.tb_reward_id.Text.Trim()));
    }

    private void textBox7_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox1.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox7.Text.Trim()));
      this.textBox4.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox7.Text.Trim()));
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      this.groupBox1 = new GroupBox();
      this.textBox8 = new TextBox();
      this.textBox6 = new TextBox();
      this.textBox5 = new TextBox();
      this.label15 = new Label();
      this.textBox2 = new TextBox();
      this.label3 = new Label();
      this.label2 = new Label();
      this.label1 = new Label();
      this.button1 = new Button();
      this.listBox1 = new ListBox();
      this.groupBox5 = new GroupBox();
      this.textBox1 = new TextBox();
      this.label7 = new Label();
      this.groupBox2 = new GroupBox();
      this.groupBox4 = new GroupBox();
      this.tb_reward_qty = new TextBox();
      this.textBox12 = new TextBox();
      this.label9 = new Label();
      this.button5 = new Button();
      this.tb_reward_name = new TextBox();
      this.tb_reward_id = new TextBox();
      this.pictureBox2 = new PictureBox();
      this.label10 = new Label();
      this.label11 = new Label();
      this.label4 = new Label();
      this.label5 = new Label();
      this.groupBox3 = new GroupBox();
      this.textBox3 = new TextBox();
      this.label6 = new Label();
      this.button2 = new Button();
      this.textBox4 = new TextBox();
      this.textBox7 = new TextBox();
      this.pictureBox1 = new PictureBox();
      this.label8 = new Label();
      this.label12 = new Label();
      this.label13 = new Label();
      this.label14 = new Label();
      this.groupBox6 = new GroupBox();
      this.textBox13 = new TextBox();
      this.label17 = new Label();
      this.textBox11 = new TextBox();
      this.label16 = new Label();
      this.textBox10 = new TextBox();
      this.textBox9 = new TextBox();
      this.groupBox1.SuspendLayout();
      this.groupBox5.SuspendLayout();
      this.groupBox2.SuspendLayout();
      this.groupBox4.SuspendLayout();
      ((ISupportInitialize) this.pictureBox2).BeginInit();
      this.groupBox3.SuspendLayout();
      ((ISupportInitialize) this.pictureBox1).BeginInit();
      this.groupBox6.SuspendLayout();
      this.SuspendLayout();
      this.groupBox1.Controls.Add((Control) this.textBox8);
      this.groupBox1.Controls.Add((Control) this.textBox6);
      this.groupBox1.Controls.Add((Control) this.textBox5);
      this.groupBox1.Controls.Add((Control) this.label15);
      this.groupBox1.Controls.Add((Control) this.textBox2);
      this.groupBox1.Controls.Add((Control) this.label3);
      this.groupBox1.Controls.Add((Control) this.label2);
      this.groupBox1.Controls.Add((Control) this.label1);
      this.groupBox1.Location = new Point(248, 13);
      this.groupBox1.Margin = new Padding(4);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Padding = new Padding(4);
      this.groupBox1.Size = new Size(351, 100);
      this.groupBox1.TabIndex = 2;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Info";
      this.textBox8.Location = new Point(97, 70);
      this.textBox8.Margin = new Padding(4);
      this.textBox8.Name = "textBox8";
      this.textBox8.Size = new Size(62, 22);
      this.textBox8.TabIndex = 17;
      this.textBox6.Location = new Point(174, 39);
      this.textBox6.Margin = new Padding(4);
      this.textBox6.Name = "textBox6";
      this.textBox6.Size = new Size(169, 22);
      this.textBox6.TabIndex = 16;
      this.textBox5.Enabled = false;
      this.textBox5.Location = new Point(15, 40);
      this.textBox5.Margin = new Padding(4);
      this.textBox5.Name = "textBox5";
      this.textBox5.Size = new Size(74, 22);
      this.textBox5.TabIndex = 15;
      this.label15.AutoSize = true;
      this.label15.Location = new Point(26, 73);
      this.label15.Margin = new Padding(4, 0, 4, 0);
      this.label15.Name = "label15";
      this.label15.Size = new Size(57, 16);
      this.label15.TabIndex = 7;
      this.label15.Text = "Season:";
      this.textBox2.Location = new Point(97, 39);
      this.textBox2.Margin = new Padding(4);
      this.textBox2.Name = "textBox2";
      this.textBox2.Size = new Size(62, 22);
      this.textBox2.TabIndex = 6;
      this.label3.AutoSize = true;
      this.label3.Location = new Point(93, 20);
      this.label3.Margin = new Padding(4, 0, 4, 0);
      this.label3.Name = "label3";
      this.label3.Size = new Size(43, 16);
      this.label3.TabIndex = 5;
      this.label3.Text = "Level:";
      this.label2.AutoSize = true;
      this.label2.Location = new Point(171, 19);
      this.label2.Margin = new Padding(4, 0, 4, 0);
      this.label2.Name = "label2";
      this.label2.Size = new Size(47, 16);
      this.label2.TabIndex = 1;
      this.label2.Text = "Name:";
      this.label1.AutoSize = true;
      this.label1.Location = new Point(15, 20);
      this.label1.Margin = new Padding(4, 0, 4, 0);
      this.label1.Name = "label1";
      this.label1.Size = new Size(42, 16);
      this.label1.TabIndex = 0;
      this.label1.Text = "Index:";
      this.button1.BackColor = Color.LightCyan;
      this.button1.FlatStyle = FlatStyle.Flat;
      this.button1.Image = (Image) Resources._08;
      this.button1.ImageAlign = ContentAlignment.MiddleLeft;
      this.button1.Location = new Point(495, 553);
      this.button1.Margin = new Padding(4);
      this.button1.Name = "button1";
      this.button1.Size = new Size(96, 33);
      this.button1.TabIndex = 7;
      this.button1.Text = "      Save";
      this.button1.UseVisualStyleBackColor = false;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.listBox1.FormattingEnabled = true;
      this.listBox1.ItemHeight = 16;
      this.listBox1.Location = new Point(8, 21);
      this.listBox1.Margin = new Padding(4);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new Size(200, 388);
      this.listBox1.TabIndex = 7;
      this.listBox1.SelectedIndexChanged += new EventHandler(this.listBox1_SelectedIndexChanged);
      this.listBox1.SelectedIndexChanged += new EventHandler(this.Reward_List);
      this.groupBox5.Controls.Add((Control) this.textBox1);
      this.groupBox5.Controls.Add((Control) this.label7);
      this.groupBox5.Location = new Point(16, 15);
      this.groupBox5.Margin = new Padding(4);
      this.groupBox5.Name = "groupBox5";
      this.groupBox5.Padding = new Padding(4);
      this.groupBox5.Size = new Size(224, 60);
      this.groupBox5.TabIndex = 33;
      this.groupBox5.TabStop = false;
      this.groupBox5.Text = "Search";
      this.textBox1.BorderStyle = BorderStyle.FixedSingle;
      this.textBox1.Location = new Point(57, 23);
      this.textBox1.Margin = new Padding(4);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(157, 22);
      this.textBox1.TabIndex = 83;
      this.textBox1.TextChanged += new EventHandler(this.textBox1_TextChanged);
      this.label7.AutoSize = true;
      this.label7.Location = new Point(8, 26);
      this.label7.Margin = new Padding(4, 0, 4, 0);
      this.label7.Name = "label7";
      this.label7.Size = new Size(36, 16);
      this.label7.TabIndex = 21;
      this.label7.Text = "Text:";
      this.groupBox2.Controls.Add((Control) this.listBox1);
      this.groupBox2.Location = new Point(16, 82);
      this.groupBox2.Margin = new Padding(4);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Padding = new Padding(4);
      this.groupBox2.Size = new Size(214, 422);
      this.groupBox2.TabIndex = 34;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "Battle Pass Level";
      this.groupBox4.BackColor = Color.Linen;
      this.groupBox4.Controls.Add((Control) this.tb_reward_qty);
      this.groupBox4.Controls.Add((Control) this.textBox12);
      this.groupBox4.Controls.Add((Control) this.label9);
      this.groupBox4.Controls.Add((Control) this.button5);
      this.groupBox4.Controls.Add((Control) this.tb_reward_name);
      this.groupBox4.Controls.Add((Control) this.tb_reward_id);
      this.groupBox4.Controls.Add((Control) this.pictureBox2);
      this.groupBox4.Controls.Add((Control) this.label10);
      this.groupBox4.Controls.Add((Control) this.label11);
      this.groupBox4.Location = new Point(24, 103);
      this.groupBox4.Margin = new Padding(4);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Padding = new Padding(4);
      this.groupBox4.Size = new Size(354, 124);
      this.groupBox4.TabIndex = 35;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "Reward Item";
      this.tb_reward_qty.Location = new Point(115, 53);
      this.tb_reward_qty.Margin = new Padding(4);
      this.tb_reward_qty.Name = "tb_reward_qty";
      this.tb_reward_qty.Size = new Size(74, 22);
      this.tb_reward_qty.TabIndex = 19;
      this.textBox12.Enabled = false;
      this.textBox12.Location = new Point(258, 20);
      this.textBox12.Margin = new Padding(4);
      this.textBox12.Name = "textBox12";
      this.textBox12.Size = new Size(74, 22);
      this.textBox12.TabIndex = 43;
      this.label9.AutoSize = true;
      this.label9.Location = new Point(74, 56);
      this.label9.Margin = new Padding(4, 0, 4, 0);
      this.label9.Name = "label9";
      this.label9.Size = new Size(39, 16);
      this.label9.TabIndex = 18;
      this.label9.Text = "Q'ty : ";
      this.button5.Image = (Image) Resources.search__5_;
      this.button5.Location = new Point(196, 15);
      this.button5.Margin = new Padding(4);
      this.button5.Name = "button5";
      this.button5.Size = new Size(40, 33);
      this.button5.TabIndex = 13;
      this.button5.UseVisualStyleBackColor = true;
      this.button5.Click += new EventHandler(this.button5_Click);
      this.tb_reward_name.Enabled = false;
      this.tb_reward_name.Location = new Point(115, 94);
      this.tb_reward_name.Margin = new Padding(4);
      this.tb_reward_name.Name = "tb_reward_name";
      this.tb_reward_name.Size = new Size(228, 22);
      this.tb_reward_name.TabIndex = 15;
      this.tb_reward_id.Enabled = false;
      this.tb_reward_id.Location = new Point(114, 20);
      this.tb_reward_id.Margin = new Padding(4);
      this.tb_reward_id.Name = "tb_reward_id";
      this.tb_reward_id.Size = new Size(74, 22);
      this.tb_reward_id.TabIndex = 14;
      this.tb_reward_id.TextChanged += new EventHandler(this.tb_reward_id_TextChanged);
      this.pictureBox2.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox2.Location = new Point(15, 23);
      this.pictureBox2.Margin = new Padding(4);
      this.pictureBox2.Name = "pictureBox2";
      this.pictureBox2.Size = new Size(55, 49);
      this.pictureBox2.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pictureBox2.TabIndex = 10;
      this.pictureBox2.TabStop = false;
      this.label10.AutoSize = true;
      this.label10.Location = new Point(57, 94);
      this.label10.Margin = new Padding(4, 0, 4, 0);
      this.label10.Name = "label10";
      this.label10.Size = new Size(50, 16);
      this.label10.TabIndex = 17;
      this.label10.Text = "Name :";
      this.label11.AutoSize = true;
      this.label11.Location = new Point(78, 23);
      this.label11.Margin = new Padding(4, 0, 4, 0);
      this.label11.Name = "label11";
      this.label11.Size = new Size(29, 16);
      this.label11.TabIndex = 16;
      this.label11.Text = "ID : ";
      this.label4.AutoSize = true;
      this.label4.Location = new Point(24, 74);
      this.label4.Margin = new Padding(4, 0, 4, 0);
      this.label4.Name = "label4";
      this.label4.Size = new Size(59, 16);
      this.label4.TabIndex = 36;
      this.label4.Text = "[Normal]";
      this.label5.AutoSize = true;
      this.label5.Location = new Point(24, 240);
      this.label5.Margin = new Padding(4, 0, 4, 0);
      this.label5.Name = "label5";
      this.label5.Size = new Size(68, 16);
      this.label5.TabIndex = 38;
      this.label5.Text = "[Premium]";
      this.groupBox3.BackColor = Color.Linen;
      this.groupBox3.Controls.Add((Control) this.textBox3);
      this.groupBox3.Controls.Add((Control) this.label6);
      this.groupBox3.Controls.Add((Control) this.button2);
      this.groupBox3.Controls.Add((Control) this.textBox4);
      this.groupBox3.Controls.Add((Control) this.textBox7);
      this.groupBox3.Controls.Add((Control) this.pictureBox1);
      this.groupBox3.Controls.Add((Control) this.label8);
      this.groupBox3.Controls.Add((Control) this.label12);
      this.groupBox3.Location = new Point(24, 269);
      this.groupBox3.Margin = new Padding(4);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Padding = new Padding(4);
      this.groupBox3.Size = new Size(354, 124);
      this.groupBox3.TabIndex = 37;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "Reward Item";
      this.textBox3.Location = new Point(115, 53);
      this.textBox3.Margin = new Padding(4);
      this.textBox3.Name = "textBox3";
      this.textBox3.Size = new Size(74, 22);
      this.textBox3.TabIndex = 19;
      this.label6.AutoSize = true;
      this.label6.Location = new Point(74, 56);
      this.label6.Margin = new Padding(4, 0, 4, 0);
      this.label6.Name = "label6";
      this.label6.Size = new Size(39, 16);
      this.label6.TabIndex = 18;
      this.label6.Text = "Q'ty : ";
      this.button2.Image = (Image) Resources.search__5_;
      this.button2.Location = new Point(196, 15);
      this.button2.Margin = new Padding(4);
      this.button2.Name = "button2";
      this.button2.Size = new Size(40, 33);
      this.button2.TabIndex = 13;
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Click += new EventHandler(this.button2_Click_1);
      this.textBox4.Enabled = false;
      this.textBox4.Location = new Point(115, 94);
      this.textBox4.Margin = new Padding(4);
      this.textBox4.Name = "textBox4";
      this.textBox4.Size = new Size(228, 22);
      this.textBox4.TabIndex = 15;
      this.textBox7.Enabled = false;
      this.textBox7.Location = new Point(114, 20);
      this.textBox7.Margin = new Padding(4);
      this.textBox7.Name = "textBox7";
      this.textBox7.Size = new Size(74, 22);
      this.textBox7.TabIndex = 14;
      this.textBox7.TextChanged += new EventHandler(this.textBox7_TextChanged);
      this.pictureBox1.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox1.Location = new Point(15, 23);
      this.pictureBox1.Margin = new Padding(4);
      this.pictureBox1.Name = "pictureBox1";
      this.pictureBox1.Size = new Size(55, 49);
      this.pictureBox1.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pictureBox1.TabIndex = 10;
      this.pictureBox1.TabStop = false;
      this.label8.AutoSize = true;
      this.label8.Location = new Point(57, 96);
      this.label8.Margin = new Padding(4, 0, 4, 0);
      this.label8.Name = "label8";
      this.label8.Size = new Size(50, 16);
      this.label8.TabIndex = 17;
      this.label8.Text = "Name :";
      this.label12.AutoSize = true;
      this.label12.Location = new Point(78, 23);
      this.label12.Margin = new Padding(4, 0, 4, 0);
      this.label12.Name = "label12";
      this.label12.Size = new Size(29, 16);
      this.label12.TabIndex = 16;
      this.label12.Text = "ID : ";
      this.label13.AutoSize = true;
      this.label13.Location = new Point(102, 240);
      this.label13.Margin = new Padding(4, 0, 4, 0);
      this.label13.Name = "label13";
      this.label13.Size = new Size(46, 16);
      this.label13.TabIndex = 40;
      this.label13.Text = "Point : ";
      this.label14.AutoSize = true;
      this.label14.Location = new Point(102, 74);
      this.label14.Margin = new Padding(4, 0, 4, 0);
      this.label14.Name = "label14";
      this.label14.Size = new Size(46, 16);
      this.label14.TabIndex = 42;
      this.label14.Text = "Point : ";
      this.groupBox6.Controls.Add((Control) this.textBox13);
      this.groupBox6.Controls.Add((Control) this.label17);
      this.groupBox6.Controls.Add((Control) this.textBox11);
      this.groupBox6.Controls.Add((Control) this.label16);
      this.groupBox6.Controls.Add((Control) this.textBox10);
      this.groupBox6.Controls.Add((Control) this.textBox9);
      this.groupBox6.Controls.Add((Control) this.label4);
      this.groupBox6.Controls.Add((Control) this.groupBox4);
      this.groupBox6.Controls.Add((Control) this.groupBox3);
      this.groupBox6.Controls.Add((Control) this.label14);
      this.groupBox6.Controls.Add((Control) this.label5);
      this.groupBox6.Controls.Add((Control) this.label13);
      this.groupBox6.Location = new Point(248, (int) sbyte.MaxValue);
      this.groupBox6.Margin = new Padding(4);
      this.groupBox6.Name = "groupBox6";
      this.groupBox6.Padding = new Padding(4);
      this.groupBox6.Size = new Size(392, 418);
      this.groupBox6.TabIndex = 43;
      this.groupBox6.TabStop = false;
      this.groupBox6.Text = "Reward";
      this.textBox13.Enabled = false;
      this.textBox13.Location = new Point(279, 23);
      this.textBox13.Margin = new Padding(4);
      this.textBox13.Name = "textBox13";
      this.textBox13.Size = new Size(74, 22);
      this.textBox13.TabIndex = 47;
      this.label17.AutoSize = true;
      this.label17.Location = new Point(217, 26);
      this.label17.Margin = new Padding(4, 0, 4, 0);
      this.label17.Name = "label17";
      this.label17.Size = new Size(54, 16);
      this.label17.TabIndex = 48;
      this.label17.Text = "BP Idx : ";
      this.textBox11.Enabled = false;
      this.textBox11.Location = new Point(117, 23);
      this.textBox11.Margin = new Padding(4);
      this.textBox11.Name = "textBox11";
      this.textBox11.Size = new Size(74, 22);
      this.textBox11.TabIndex = 45;
      this.label16.AutoSize = true;
      this.label16.Location = new Point(61, 26);
      this.label16.Margin = new Padding(4, 0, 4, 0);
      this.label16.Name = "label16";
      this.label16.Size = new Size(48, 16);
      this.label16.TabIndex = 46;
      this.label16.Text = "Index : ";
      this.textBox10.Location = new Point(156, 237);
      this.textBox10.Margin = new Padding(4);
      this.textBox10.Name = "textBox10";
      this.textBox10.Size = new Size(169, 22);
      this.textBox10.TabIndex = 44;
      this.textBox9.Location = new Point(156, 71);
      this.textBox9.Margin = new Padding(4);
      this.textBox9.Name = "textBox9";
      this.textBox9.Size = new Size(169, 22);
      this.textBox9.TabIndex = 43;
      this.AutoScaleDimensions = new SizeF(8f, 16f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(653, 599);
      this.Controls.Add((Control) this.groupBox6);
      this.Controls.Add((Control) this.button1);
      this.Controls.Add((Control) this.groupBox2);
      this.Controls.Add((Control) this.groupBox5);
      this.Controls.Add((Control) this.groupBox1);
      this.FormBorderStyle = FormBorderStyle.Fixed3D;
      this.Margin = new Padding(4);
      this.MaximizeBox = false;
      this.Name = nameof (Prestige);
      this.Text = "LastChaos Prestige Editor";
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.groupBox5.ResumeLayout(false);
      this.groupBox5.PerformLayout();
      this.groupBox2.ResumeLayout(false);
      this.groupBox4.ResumeLayout(false);
      this.groupBox4.PerformLayout();
      ((ISupportInitialize) this.pictureBox2).EndInit();
      this.groupBox3.ResumeLayout(false);
      this.groupBox3.PerformLayout();
      ((ISupportInitialize) this.pictureBox1).EndInit();
      this.groupBox6.ResumeLayout(false);
      this.groupBox6.PerformLayout();
      this.ResumeLayout(false);
    }

    private void button5_Click(object sender, EventArgs e)
    {
      this.tb_reward_id.Text = "0";
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.tb_reward_id.Text = itemPicker.ItemIndex.ToString();
    }

    private void button2_Click_1(object sender, EventArgs e)
    {
      this.textBox7.Text = "0";
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox7.Text = itemPicker.ItemIndex.ToString();
    }
  }
}
