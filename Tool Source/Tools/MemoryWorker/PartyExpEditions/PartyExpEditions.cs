// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.PartyExpEditions.PartyExpEditions
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
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.PartyExpEditions
{
  public class PartyExpEditions : Form
  {
    public static Connection connection = new Connection();
    private string Host = LcDevPack_TeamDamonA.Tools.MemoryWorker.PartyExpEditions.PartyExpEditions.connection.Settings.SqlHost;
    private string User = LcDevPack_TeamDamonA.Tools.MemoryWorker.PartyExpEditions.PartyExpEditions.connection.Settings.SqlUser;
    private string Password = LcDevPack_TeamDamonA.Tools.MemoryWorker.PartyExpEditions.PartyExpEditions.connection.Settings.SqlPassword;
    private string Database = LcDevPack_TeamDamonA.Tools.MemoryWorker.PartyExpEditions.PartyExpEditions.connection.Settings.SqlDatabase;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    private ExportLodHandle exportLodHandle = new ExportLodHandle();
    private IContainer components = (IContainer) null;
    private MySqlDataAdapter sda;
    private BindingSource bSource;
    private DataTable dbdataset;
    private MenuStrip menuStrip1;
    private ToolStripMenuItem menüToolStripMenuItem;
    private ToolStripMenuItem loadFromDatabaseToolStripMenuItem;
    private ToolStripMenuItem exitToolStripMenuItem;
    private TextBox textBox1;
    private TextBox textBox2;
    private TextBox textBox3;
    private TextBox textBox4;
    private TextBox textBox7;
    private GroupBox Boss1_npc;
    private Button bt_boss1;
    private TextBox Boss1_name;
    private TextBox Boss_id1;
    private PictureBox pc_npc;
    private Label label7;
    private Label label8;
    private GroupBox groupBox4;
    private TextBox a_need_item_count;
    private Label label9;
    private Button bt_needitem;
    private TextBox need_item_name;
    private TextBox a_need_item_idx;
    private PictureBox pictureBox2;
    private Label label10;
    private Label label11;
    private GroupBox groupBox2;
    private TextBox index;
    private Label label21;
    private GroupBox groupBox7;
    private Button bt_update;
    private Button bt_refresh;
    private GroupBox groupBox3;
    private CheckBox checkBox5;
    private CheckBox checkBox4;
    private CheckBox checkBox3;
    private CheckBox checkBox2;
    private CheckBox checkBox1;
    private TextBox r_t_id5_count;
    private Label label18;
    private Button bt_r_t_id5;
    private TextBox r_t_id5_name;
    private TextBox r_t_id5;
    private PictureBox pictureBox7;
    private TextBox r_t_id4_count;
    private Label label15;
    private Button bt_r_t_id4;
    private TextBox r_t_id4_name;
    private TextBox r_t_id4;
    private PictureBox pictureBox6;
    private TextBox r_t_id3_count;
    private Label label12;
    private Button bt_r_t_id3;
    private TextBox r_t_id3_name;
    private TextBox r_t_id3;
    private PictureBox pictureBox5;
    private TextBox r_t_id2_count;
    private Label label13;
    private Button bt_r_t_id2;
    private TextBox r_t_id2_name;
    private TextBox r_t_id2;
    private PictureBox pictureBox4;
    private TextBox r_t_id1_count;
    private Label label14;
    private Button bt_r_t_id1;
    private TextBox r_t_id1_name;
    private TextBox r_t_id1;
    private PictureBox pictureBox3;
    private Label label19;
    private Label label20;
    private Label label16;
    private Label label17;
    private Label label24;
    private Label label25;
    private Label label26;
    private Label label27;
    private Label label28;
    private ListBox listBox1;
    private Label label29;
    public List<string> MenuList = new List<string>();
    private TextBox Zone_Id;
    private Label label1;
    private TextBox Type;
    private Label label5;
    private TextBox CP;
    private Label label4;
    private TextBox Level;
    private Label label3;
    private TextBox Difficulty;
    private Label label2;
    private TextBox DominationPoint;
    private Label label31;
    private TextBox Domination1;
    private Label label30;
    private TextBox Domination0;
    private Label label6;
    private TextBox Info;
    private Label label32;
    private PictureBox pictureBox8;
    private PictureBox pictureBox1;
    private Button bt_boss3;
    private TextBox Boss3_name;
    private TextBox Boss_id3;
    private Label label33;
    private Label label34;
    private Button bt_boss2;
    private TextBox Boss2_name;
    private TextBox Boss_id2;
    private Label label22;
    private Label label23;
    private GroupBox groupBox1;
    private Button bt_title;
    private TextBox Title_name;
    private TextBox Title_Id;
    private PictureBox pictureBox9;
    private Label label36;
    private Label label37;
    private GroupBox groupBox5;
    private TextBox Box_Count;
    private Label label38;
    private Button bt_box;
    private TextBox Box_name;
    private TextBox Box_Id;
    private PictureBox pictureBox10;
    private Label label39;
    private Label label40;
    private Label label43;
    private Label label42;
    private Label label41;
    private TextBox Party_member;
    private Label label35;
    private TextBox Time;
    private Label label44;
    public string[] menuArray = new string[2]
    {
      "a_index",
      "a_zonetid"
    };

    public PartyExpEditions()
    {
      this.InitializeComponent();
      this.LoadListBox();
    }

    private void configToolStripMenuItem_Click(object sender, EventArgs e)
    {
    }

    private void IniRead()
    {
      IniFile iniFile = new IniFile(Application.StartupPath + "\\Config\\Settings.cfg");
      this.textBox1.Text = iniFile.IniReadValue("## MYSQL", "SQL_HOST");
      this.textBox2.Text = iniFile.IniReadValue("## MYSQL", "SQL_USER");
      this.textBox3.Text = iniFile.IniReadValue("## MYSQL", "SQL_PASSWORD");
      this.textBox4.Text = iniFile.IniReadValue("## MYSQL", "SQL_DATABASE");
    }

    private void SelectDB2()
    {
      this.listBox1.SelectedIndex = -1;
      this.MenuList.Clear();
            string connectionString =
                $"Server={Host};Port=3306;User ID={User};Password={Password};Database={Database};" +
                "SslMode=Preferred;TlsVersion=Tls12;";

            this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, "SELECT * FROM t_cloud_partyexpedition_config ORDER BY a_index ASC;");
      for (int index = 0; index < this.listBox1.Items.Count; ++index)
        this.MenuList.Add(this.listBox1.Items[index].ToString() + "-");
      this.listBox1.DataSource = (object) this.MenuList;
      this.listBox1.SelectedIndex = -1;
    }

    private void LoadListBox()
    {
      this.IniRead();
      this.SelectDB2();
    }

    private void ListBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
            string connectionString =
                      $"Server={Host};Port=3306;User ID={User};Password={Password};Database={Database};" +
                      "SslMode=Preferred;TlsVersion=Tls12;";
            string cmdText = "select * FROM t_cloud_partyexpedition_config WHERE a_index ='" + this.listBox1.Text + "';";
      MySqlConnection connection = new MySqlConnection(connectionString);
      MySqlCommand mySqlCommand = new MySqlCommand(cmdText, connection);
      try
      {
        connection.Open();
        MySqlDataReader mySqlDataReader = mySqlCommand.ExecuteReader();
        while (mySqlDataReader.Read())
        {
          int int32 = mySqlDataReader.GetInt32("a_index");
          string str1 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("a_zonetid");
          string str2 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("a_difficulty");
          string str3 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("a_level");
          string str4 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("a_cp");
          string str5 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("a_need_item_idx");
          string str6 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("a_need_item_count");
          string str7 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("a_member_need");
          string str8 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("a_time");
          string str9 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("a_reward_item_idx");
          string str10 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("a_reward_item_count");
          string str11 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("a_reward_item_idx1");
          string str12 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("a_reward_item_count1");
          string str13 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("a_reward_item_idx2");
          string str14 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("a_reward_item_count2");
          string str15 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("a_reward_item_idx3");
          string str16 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("a_reward_item_count3");
          string str17 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("a_reward_item_idx4");
          string str18 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("a_reward_item_count4");
          string str19 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("a_tittle_reward");
          string str20 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("a_box_reward");
          string str21 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("a_box_count");
          string str22 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("a_boss_idx1");
          string str23 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("a_boss_idx2");
          string str24 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("a_boss_idx3");
          string str25 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("a_domination0");
          string str26 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("a_domination1");
          string str27 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("a_domination_point");
          string str28 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("a_type");
          string str29 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("a_info");
          string str30 = int32.ToString();
          this.index.Text = str1;
          this.Zone_Id.Text = str2;
          this.Difficulty.Text = str3;
          this.Level.Text = str4;
          this.CP.Text = str5;
          this.a_need_item_idx.Text = str6;
          this.a_need_item_count.Text = str7;
          this.Party_member.Text = str8;
          this.Time.Text = str9;
          this.r_t_id1.Text = str10;
          this.r_t_id1_count.Text = str11;
          this.r_t_id2.Text = str12;
          this.r_t_id2_count.Text = str13;
          this.r_t_id3.Text = str14;
          this.r_t_id3_count.Text = str15;
          this.r_t_id4.Text = str16;
          this.r_t_id4_count.Text = str17;
          this.r_t_id5.Text = str18;
          this.r_t_id5_count.Text = str19;
          this.Title_Id.Text = str20;
          this.Box_Id.Text = str21;
          this.Box_Count.Text = str22;
          this.Boss_id1.Text = str23;
          this.Boss_id2.Text = str24;
          this.Boss_id3.Text = str25;
          this.Domination0.Text = str26;
          this.Domination1.Text = str27;
          this.DominationPoint.Text = str28;
          this.Type.Text = str29;
          this.Info.Text = str30;
        }
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message);
      }
      connection.Close();
    }

    private void loadFromDatabaseToolStripMenuItem_Click(object sender, EventArgs e)
    {
      this.IniRead();
      this.SelectDB2();
    }

    private void textBox6_TextChanged(object sender, EventArgs e)
    {
    }

    private void tb_reward_id_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox2.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.a_need_item_idx.Text.Trim()));
      this.need_item_name.Text = this.databaseHandle.ItemNameFast(int.Parse(this.a_need_item_idx.Text.Trim()));
    }

    private void tx_npc_id_TextChanged(object sender, EventArgs e)
    {
      this.pc_npc.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.Boss_id1.Text.Trim()));
      this.Boss1_name.Text = this.databaseHandle.MobNameFast(int.Parse(this.Boss_id1.Text.Trim()));
    }

    private void r_t_id1_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox3.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.r_t_id1.Text.Trim()));
      this.r_t_id1_name.Text = this.databaseHandle.ItemNameFast(int.Parse(this.r_t_id1.Text.Trim()));
    }

    private void r_t_id2_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox4.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.r_t_id2.Text.Trim()));
      this.r_t_id2_name.Text = this.databaseHandle.ItemNameFast(int.Parse(this.r_t_id2.Text.Trim()));
    }

    private void r_t_id3_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox5.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.r_t_id3.Text.Trim()));
      this.r_t_id3_name.Text = this.databaseHandle.ItemNameFast(int.Parse(this.r_t_id3.Text.Trim()));
    }

    private void r_t_id4_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox6.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.r_t_id4.Text.Trim()));
      this.r_t_id4_name.Text = this.databaseHandle.ItemNameFast(int.Parse(this.r_t_id4.Text.Trim()));
    }

    private void r_t_id5_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox7.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.r_t_id5.Text.Trim()));
      this.r_t_id5_name.Text = this.databaseHandle.ItemNameFast(int.Parse(this.r_t_id5.Text.Trim()));
    }

    private void exitToolStripMenuItem_Click(object sender, EventArgs e) => this.Close();

    private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
    {
      int num = (int) MessageBox.Show("LastChaos Exchange Editor By inwshadow !", "About", MessageBoxButtons.OK, MessageBoxIcon.Asterisk, MessageBoxDefaultButton.Button2);
    }

    private void button9_Click(object sender, EventArgs e)
    {
      this.IniRead();
      int selectedIndex = this.listBox1.SelectedIndex;
      MySqlConnection connection = new MySqlConnection("datasource=" + this.textBox1.Text + ";port=3306;username=" + this.textBox2.Text + ";password=" + this.textBox3.Text);
      MySqlCommand mySqlCommand = new MySqlCommand("UPDATE " + this.textBox4.Text + ".t_item_exchange SET  a_npc_index='" + this.Boss_id1.Text + "', result_itemIndex='" + this.a_need_item_idx.Text + "', result_itemCount='" + this.a_need_item_count.Text + "', source_itemIndex0='" + this.r_t_id1.Text + "', source_itemCount0='" + this.r_t_id1_count.Text + "', source_itemIndex1='" + this.r_t_id2.Text + "', source_itemCount1='" + this.r_t_id2_count.Text + "', source_itemIndex2='" + this.r_t_id3.Text + "', source_itemCount2='" + this.r_t_id3_count.Text + "', source_itemIndex3='" + this.r_t_id4.Text + "', source_itemCount3='" + this.r_t_id4_count.Text + "', source_itemIndex4='" + this.r_t_id5.Text + "', source_itemCount4='" + this.r_t_id5_count.Text + "' WHERE a_index='" + this.index.Text + "'", connection);
      try
      {
        connection.Open();
        MySqlDataReader mySqlDataReader = mySqlCommand.ExecuteReader();
        int num = (int) MessageBox.Show("Your Item is Saved!");
        while (mySqlDataReader.Read())
          ;
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message);
      }
      this.SelectDB2();
      this.listBox1.SelectedIndex = selectedIndex;
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      this.menuStrip1 = new MenuStrip();
      this.menüToolStripMenuItem = new ToolStripMenuItem();
      this.loadFromDatabaseToolStripMenuItem = new ToolStripMenuItem();
      this.exitToolStripMenuItem = new ToolStripMenuItem();
      this.textBox1 = new TextBox();
      this.textBox2 = new TextBox();
      this.textBox3 = new TextBox();
      this.textBox4 = new TextBox();
      this.textBox7 = new TextBox();
      this.Boss1_npc = new GroupBox();
      this.label43 = new Label();
      this.label42 = new Label();
      this.label41 = new Label();
      this.pictureBox8 = new PictureBox();
      this.pictureBox1 = new PictureBox();
      this.bt_boss3 = new Button();
      this.Boss3_name = new TextBox();
      this.Boss_id3 = new TextBox();
      this.label33 = new Label();
      this.label34 = new Label();
      this.bt_boss2 = new Button();
      this.Boss2_name = new TextBox();
      this.Boss_id2 = new TextBox();
      this.label22 = new Label();
      this.label23 = new Label();
      this.bt_boss1 = new Button();
      this.Boss1_name = new TextBox();
      this.Boss_id1 = new TextBox();
      this.pc_npc = new PictureBox();
      this.label7 = new Label();
      this.label8 = new Label();
      this.groupBox4 = new GroupBox();
      this.a_need_item_count = new TextBox();
      this.label9 = new Label();
      this.bt_needitem = new Button();
      this.need_item_name = new TextBox();
      this.a_need_item_idx = new TextBox();
      this.pictureBox2 = new PictureBox();
      this.label10 = new Label();
      this.label11 = new Label();
      this.groupBox2 = new GroupBox();
      this.Time = new TextBox();
      this.label44 = new Label();
      this.Party_member = new TextBox();
      this.label35 = new Label();
      this.Info = new TextBox();
      this.label32 = new Label();
      this.DominationPoint = new TextBox();
      this.label31 = new Label();
      this.Domination1 = new TextBox();
      this.label30 = new Label();
      this.Domination0 = new TextBox();
      this.label6 = new Label();
      this.Type = new TextBox();
      this.label5 = new Label();
      this.CP = new TextBox();
      this.label4 = new Label();
      this.Level = new TextBox();
      this.label3 = new Label();
      this.Difficulty = new TextBox();
      this.label2 = new Label();
      this.Zone_Id = new TextBox();
      this.label1 = new Label();
      this.index = new TextBox();
      this.label21 = new Label();
      this.groupBox7 = new GroupBox();
      this.bt_refresh = new Button();
      this.bt_update = new Button();
      this.groupBox3 = new GroupBox();
      this.checkBox5 = new CheckBox();
      this.checkBox4 = new CheckBox();
      this.checkBox3 = new CheckBox();
      this.checkBox2 = new CheckBox();
      this.checkBox1 = new CheckBox();
      this.r_t_id5_count = new TextBox();
      this.label18 = new Label();
      this.bt_r_t_id5 = new Button();
      this.r_t_id5_name = new TextBox();
      this.r_t_id5 = new TextBox();
      this.pictureBox7 = new PictureBox();
      this.r_t_id4_count = new TextBox();
      this.label15 = new Label();
      this.bt_r_t_id4 = new Button();
      this.r_t_id4_name = new TextBox();
      this.r_t_id4 = new TextBox();
      this.pictureBox6 = new PictureBox();
      this.r_t_id3_count = new TextBox();
      this.label12 = new Label();
      this.bt_r_t_id3 = new Button();
      this.r_t_id3_name = new TextBox();
      this.r_t_id3 = new TextBox();
      this.pictureBox5 = new PictureBox();
      this.r_t_id2_count = new TextBox();
      this.label13 = new Label();
      this.bt_r_t_id2 = new Button();
      this.r_t_id2_name = new TextBox();
      this.r_t_id2 = new TextBox();
      this.pictureBox4 = new PictureBox();
      this.r_t_id1_count = new TextBox();
      this.label14 = new Label();
      this.bt_r_t_id1 = new Button();
      this.r_t_id1_name = new TextBox();
      this.r_t_id1 = new TextBox();
      this.pictureBox3 = new PictureBox();
      this.label19 = new Label();
      this.label20 = new Label();
      this.label16 = new Label();
      this.label17 = new Label();
      this.label24 = new Label();
      this.label25 = new Label();
      this.label26 = new Label();
      this.label27 = new Label();
      this.label28 = new Label();
      this.label29 = new Label();
      this.listBox1 = new ListBox();
      this.groupBox1 = new GroupBox();
      this.bt_title = new Button();
      this.Title_name = new TextBox();
      this.Title_Id = new TextBox();
      this.pictureBox9 = new PictureBox();
      this.label36 = new Label();
      this.label37 = new Label();
      this.groupBox5 = new GroupBox();
      this.Box_Count = new TextBox();
      this.label38 = new Label();
      this.bt_box = new Button();
      this.Box_name = new TextBox();
      this.Box_Id = new TextBox();
      this.pictureBox10 = new PictureBox();
      this.label39 = new Label();
      this.label40 = new Label();
      this.menuStrip1.SuspendLayout();
      this.Boss1_npc.SuspendLayout();
      ((ISupportInitialize) this.pictureBox8).BeginInit();
      ((ISupportInitialize) this.pictureBox1).BeginInit();
      ((ISupportInitialize) this.pc_npc).BeginInit();
      this.groupBox4.SuspendLayout();
      ((ISupportInitialize) this.pictureBox2).BeginInit();
      this.groupBox2.SuspendLayout();
      this.groupBox7.SuspendLayout();
      this.groupBox3.SuspendLayout();
      ((ISupportInitialize) this.pictureBox7).BeginInit();
      ((ISupportInitialize) this.pictureBox6).BeginInit();
      ((ISupportInitialize) this.pictureBox5).BeginInit();
      ((ISupportInitialize) this.pictureBox4).BeginInit();
      ((ISupportInitialize) this.pictureBox3).BeginInit();
      this.groupBox1.SuspendLayout();
      ((ISupportInitialize) this.pictureBox9).BeginInit();
      this.groupBox5.SuspendLayout();
      ((ISupportInitialize) this.pictureBox10).BeginInit();
      this.SuspendLayout();
      this.menuStrip1.BackColor = Color.Transparent;
      this.menuStrip1.ImageScalingSize = new Size(20, 20);
      this.menuStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.menüToolStripMenuItem
      });
      this.menuStrip1.Location = new Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new Size(1228, 28);
      this.menuStrip1.TabIndex = 0;
      this.menuStrip1.Text = "menuStrip1";
      this.menüToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[2]
      {
        (ToolStripItem) this.loadFromDatabaseToolStripMenuItem,
        (ToolStripItem) this.exitToolStripMenuItem
      });
      this.menüToolStripMenuItem.Name = "menüToolStripMenuItem";
      this.menüToolStripMenuItem.Size = new Size(69, 24);
      this.menüToolStripMenuItem.Text = "MySQL";
      this.loadFromDatabaseToolStripMenuItem.Name = "loadFromDatabaseToolStripMenuItem";
      this.loadFromDatabaseToolStripMenuItem.Size = new Size(230, 26);
      this.loadFromDatabaseToolStripMenuItem.Text = "Load From Database";
      this.loadFromDatabaseToolStripMenuItem.Click += new EventHandler(this.loadFromDatabaseToolStripMenuItem_Click);
      this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
      this.exitToolStripMenuItem.Size = new Size(230, 26);
      this.exitToolStripMenuItem.Text = "Exit";
      this.exitToolStripMenuItem.Click += new EventHandler(this.exitToolStripMenuItem_Click);
      this.textBox1.Location = new Point(430, 767);
      this.textBox1.Margin = new Padding(4);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(132, 22);
      this.textBox1.TabIndex = 3;
      this.textBox1.Visible = false;
      this.textBox2.Location = new Point(568, 735);
      this.textBox2.Margin = new Padding(4);
      this.textBox2.Name = "textBox2";
      this.textBox2.Size = new Size(132, 22);
      this.textBox2.TabIndex = 4;
      this.textBox2.Visible = false;
      this.textBox3.Location = new Point(283, 747);
      this.textBox3.Margin = new Padding(4);
      this.textBox3.Name = "textBox3";
      this.textBox3.Size = new Size(132, 22);
      this.textBox3.TabIndex = 5;
      this.textBox3.Visible = false;
      this.textBox4.Location = new Point(430, 735);
      this.textBox4.Margin = new Padding(4);
      this.textBox4.Name = "textBox4";
      this.textBox4.Size = new Size(132, 22);
      this.textBox4.TabIndex = 6;
      this.textBox4.Visible = false;
      this.textBox7.Location = new Point(567, 767);
      this.textBox7.Margin = new Padding(4);
      this.textBox7.Name = "textBox7";
      this.textBox7.Size = new Size(132, 22);
      this.textBox7.TabIndex = 6;
      this.textBox7.Visible = false;
      this.Boss1_npc.BackColor = Color.Snow;
      this.Boss1_npc.Controls.Add((Control) this.label43);
      this.Boss1_npc.Controls.Add((Control) this.label42);
      this.Boss1_npc.Controls.Add((Control) this.label41);
      this.Boss1_npc.Controls.Add((Control) this.pictureBox8);
      this.Boss1_npc.Controls.Add((Control) this.pictureBox1);
      this.Boss1_npc.Controls.Add((Control) this.bt_boss3);
      this.Boss1_npc.Controls.Add((Control) this.Boss3_name);
      this.Boss1_npc.Controls.Add((Control) this.Boss_id3);
      this.Boss1_npc.Controls.Add((Control) this.label33);
      this.Boss1_npc.Controls.Add((Control) this.label34);
      this.Boss1_npc.Controls.Add((Control) this.bt_boss2);
      this.Boss1_npc.Controls.Add((Control) this.Boss2_name);
      this.Boss1_npc.Controls.Add((Control) this.Boss_id2);
      this.Boss1_npc.Controls.Add((Control) this.label22);
      this.Boss1_npc.Controls.Add((Control) this.label23);
      this.Boss1_npc.Controls.Add((Control) this.bt_boss1);
      this.Boss1_npc.Controls.Add((Control) this.Boss1_name);
      this.Boss1_npc.Controls.Add((Control) this.Boss_id1);
      this.Boss1_npc.Controls.Add((Control) this.pc_npc);
      this.Boss1_npc.Controls.Add((Control) this.label7);
      this.Boss1_npc.Controls.Add((Control) this.label8);
      this.Boss1_npc.Location = new Point(763, 389);
      this.Boss1_npc.Margin = new Padding(4);
      this.Boss1_npc.Name = "Boss1_npc";
      this.Boss1_npc.Padding = new Padding(4);
      this.Boss1_npc.Size = new Size(457, 328);
      this.Boss1_npc.TabIndex = 7;
      this.Boss1_npc.TabStop = false;
      this.Boss1_npc.Text = "BOSS Information";
      this.label43.AutoSize = true;
      this.label43.ForeColor = Color.Coral;
      this.label43.Location = new Point(18, 222);
      this.label43.Margin = new Padding(4, 0, 4, 0);
      this.label43.Name = "label43";
      this.label43.Size = new Size(75, 16);
      this.label43.TabIndex = 32;
      this.label43.Text = "BOSS No.3";
      this.label42.AutoSize = true;
      this.label42.ForeColor = Color.OrangeRed;
      this.label42.Location = new Point(18, 121);
      this.label42.Margin = new Padding(4, 0, 4, 0);
      this.label42.Name = "label42";
      this.label42.Size = new Size(75, 16);
      this.label42.TabIndex = 31;
      this.label42.Text = "BOSS No.2";
      this.label41.AutoSize = true;
      this.label41.ForeColor = Color.Red;
      this.label41.Location = new Point(18, 19);
      this.label41.Margin = new Padding(4, 0, 4, 0);
      this.label41.Name = "label41";
      this.label41.Size = new Size(75, 16);
      this.label41.TabIndex = 30;
      this.label41.Text = "BOSS No.1";
      this.pictureBox8.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox8.Location = new Point(15, 242);
      this.pictureBox8.Margin = new Padding(4);
      this.pictureBox8.Name = "pictureBox8";
      this.pictureBox8.Size = new Size(55, 49);
      this.pictureBox8.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pictureBox8.TabIndex = 29;
      this.pictureBox8.TabStop = false;
      this.pictureBox1.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox1.Location = new Point(15, 141);
      this.pictureBox1.Margin = new Padding(4);
      this.pictureBox1.Name = "pictureBox1";
      this.pictureBox1.Size = new Size(55, 49);
      this.pictureBox1.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pictureBox1.TabIndex = 28;
      this.pictureBox1.TabStop = false;
      this.bt_boss3.Image = (Image) Resources.search__5_;
      this.bt_boss3.Location = new Point(343, 237);
      this.bt_boss3.Margin = new Padding(4);
      this.bt_boss3.Name = "bt_boss3";
      this.bt_boss3.Size = new Size(40, 33);
      this.bt_boss3.TabIndex = 22;
      this.bt_boss3.UseVisualStyleBackColor = true;
      this.Boss3_name.Enabled = false;
      this.Boss3_name.Location = new Point(138, 279);
      this.Boss3_name.Margin = new Padding(4);
      this.Boss3_name.Name = "Boss3_name";
      this.Boss3_name.Size = new Size(261, 22);
      this.Boss3_name.TabIndex = 24;
      this.Boss_id3.Enabled = false;
      this.Boss_id3.Location = new Point(138, 242);
      this.Boss_id3.Margin = new Padding(4);
      this.Boss_id3.Name = "Boss_id3";
      this.Boss_id3.Size = new Size(121, 22);
      this.Boss_id3.TabIndex = 23;
      this.label33.AutoSize = true;
      this.label33.Location = new Point(78, 284);
      this.label33.Margin = new Padding(4, 0, 4, 0);
      this.label33.Name = "label33";
      this.label33.Size = new Size(50, 16);
      this.label33.TabIndex = 26;
      this.label33.Text = "Name :";
      this.label34.AutoSize = true;
      this.label34.Location = new Point(78, 247);
      this.label34.Margin = new Padding(4, 0, 4, 0);
      this.label34.Name = "label34";
      this.label34.Size = new Size(29, 16);
      this.label34.TabIndex = 25;
      this.label34.Text = "ID : ";
      this.bt_boss2.Image = (Image) Resources.search__5_;
      this.bt_boss2.Location = new Point(345, 131);
      this.bt_boss2.Margin = new Padding(4);
      this.bt_boss2.Name = "bt_boss2";
      this.bt_boss2.Size = new Size(40, 33);
      this.bt_boss2.TabIndex = 16;
      this.bt_boss2.UseVisualStyleBackColor = true;
      this.Boss2_name.Enabled = false;
      this.Boss2_name.Location = new Point(140, 173);
      this.Boss2_name.Margin = new Padding(4);
      this.Boss2_name.Name = "Boss2_name";
      this.Boss2_name.Size = new Size(261, 22);
      this.Boss2_name.TabIndex = 18;
      this.Boss_id2.Enabled = false;
      this.Boss_id2.Location = new Point(140, 136);
      this.Boss_id2.Margin = new Padding(4);
      this.Boss_id2.Name = "Boss_id2";
      this.Boss_id2.Size = new Size(121, 22);
      this.Boss_id2.TabIndex = 17;
      this.label22.AutoSize = true;
      this.label22.Location = new Point(80, 178);
      this.label22.Margin = new Padding(4, 0, 4, 0);
      this.label22.Name = "label22";
      this.label22.Size = new Size(50, 16);
      this.label22.TabIndex = 20;
      this.label22.Text = "Name :";
      this.label23.AutoSize = true;
      this.label23.Location = new Point(80, 141);
      this.label23.Margin = new Padding(4, 0, 4, 0);
      this.label23.Name = "label23";
      this.label23.Size = new Size(29, 16);
      this.label23.TabIndex = 19;
      this.label23.Text = "ID : ";
      this.bt_boss1.Image = (Image) Resources.search__5_;
      this.bt_boss1.Location = new Point(345, 31);
      this.bt_boss1.Margin = new Padding(4);
      this.bt_boss1.Name = "bt_boss1";
      this.bt_boss1.Size = new Size(40, 33);
      this.bt_boss1.TabIndex = 0;
      this.bt_boss1.UseVisualStyleBackColor = true;
      this.bt_boss1.Click += new EventHandler(this.bt_npc_Click);
      this.Boss1_name.Enabled = false;
      this.Boss1_name.Location = new Point(140, 73);
      this.Boss1_name.Margin = new Padding(4);
      this.Boss1_name.Name = "Boss1_name";
      this.Boss1_name.Size = new Size(261, 22);
      this.Boss1_name.TabIndex = 12;
      this.Boss_id1.Enabled = false;
      this.Boss_id1.Location = new Point(140, 36);
      this.Boss_id1.Margin = new Padding(4);
      this.Boss_id1.Name = "Boss_id1";
      this.Boss_id1.Size = new Size(121, 22);
      this.Boss_id1.TabIndex = 11;
      this.Boss_id1.TextChanged += new EventHandler(this.tx_npc_id_TextChanged);
      this.pc_npc.BorderStyle = BorderStyle.FixedSingle;
      this.pc_npc.Location = new Point(15, 42);
      this.pc_npc.Margin = new Padding(4);
      this.pc_npc.Name = "pc_npc";
      this.pc_npc.Size = new Size(55, 49);
      this.pc_npc.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pc_npc.TabIndex = 9;
      this.pc_npc.TabStop = false;
      this.label7.AutoSize = true;
      this.label7.Location = new Point(80, 78);
      this.label7.Margin = new Padding(4, 0, 4, 0);
      this.label7.Name = "label7";
      this.label7.Size = new Size(50, 16);
      this.label7.TabIndex = 14;
      this.label7.Text = "Name :";
      this.label8.AutoSize = true;
      this.label8.Location = new Point(80, 41);
      this.label8.Margin = new Padding(4, 0, 4, 0);
      this.label8.Name = "label8";
      this.label8.Size = new Size(29, 16);
      this.label8.TabIndex = 13;
      this.label8.Text = "ID : ";
      this.groupBox4.BackColor = Color.Linen;
      this.groupBox4.Controls.Add((Control) this.a_need_item_count);
      this.groupBox4.Controls.Add((Control) this.label9);
      this.groupBox4.Controls.Add((Control) this.bt_needitem);
      this.groupBox4.Controls.Add((Control) this.need_item_name);
      this.groupBox4.Controls.Add((Control) this.a_need_item_idx);
      this.groupBox4.Controls.Add((Control) this.pictureBox2);
      this.groupBox4.Controls.Add((Control) this.label10);
      this.groupBox4.Controls.Add((Control) this.label11);
      this.groupBox4.Location = new Point(291, 112);
      this.groupBox4.Margin = new Padding(4);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Padding = new Padding(4);
      this.groupBox4.Size = new Size(457, 119);
      this.groupBox4.TabIndex = 9;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "Need Item";
      this.a_need_item_count.Location = new Point(290, 32);
      this.a_need_item_count.Margin = new Padding(4);
      this.a_need_item_count.Name = "a_need_item_count";
      this.a_need_item_count.Size = new Size(97, 22);
      this.a_need_item_count.TabIndex = 19;
      this.label9.AutoSize = true;
      this.label9.Location = new Point(242, 38);
      this.label9.Margin = new Padding(4, 0, 4, 0);
      this.label9.Name = "label9";
      this.label9.Size = new Size(39, 16);
      this.label9.TabIndex = 18;
      this.label9.Text = "Q'ty : ";
      this.bt_needitem.Image = (Image) Resources.search__5_;
      this.bt_needitem.Location = new Point(405, 27);
      this.bt_needitem.Margin = new Padding(4);
      this.bt_needitem.Name = "bt_needitem";
      this.bt_needitem.Size = new Size(40, 33);
      this.bt_needitem.TabIndex = 13;
      this.bt_needitem.UseVisualStyleBackColor = true;
      this.bt_needitem.Click += new EventHandler(this.button5_Click);
      this.need_item_name.Enabled = false;
      this.need_item_name.Location = new Point(148, 71);
      this.need_item_name.Margin = new Padding(4);
      this.need_item_name.Name = "need_item_name";
      this.need_item_name.Size = new Size(297, 22);
      this.need_item_name.TabIndex = 15;
      this.a_need_item_idx.Enabled = false;
      this.a_need_item_idx.Location = new Point(150, 34);
      this.a_need_item_idx.Margin = new Padding(4);
      this.a_need_item_idx.Name = "a_need_item_idx";
      this.a_need_item_idx.Size = new Size(85, 22);
      this.a_need_item_idx.TabIndex = 14;
      this.a_need_item_idx.TextChanged += new EventHandler(this.tb_reward_id_TextChanged);
      this.pictureBox2.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox2.Location = new Point(15, 42);
      this.pictureBox2.Margin = new Padding(4);
      this.pictureBox2.Name = "pictureBox2";
      this.pictureBox2.Size = new Size(55, 49);
      this.pictureBox2.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pictureBox2.TabIndex = 10;
      this.pictureBox2.TabStop = false;
      this.label10.AutoSize = true;
      this.label10.Location = new Point(80, 75);
      this.label10.Margin = new Padding(4, 0, 4, 0);
      this.label10.Name = "label10";
      this.label10.Size = new Size(50, 16);
      this.label10.TabIndex = 17;
      this.label10.Text = "Name :";
      this.label11.AutoSize = true;
      this.label11.Location = new Point(80, 39);
      this.label11.Margin = new Padding(4, 0, 4, 0);
      this.label11.Name = "label11";
      this.label11.Size = new Size(29, 16);
      this.label11.TabIndex = 16;
      this.label11.Text = "ID : ";
      this.groupBox2.BackColor = Color.Lavender;
      this.groupBox2.Controls.Add((Control) this.Time);
      this.groupBox2.Controls.Add((Control) this.label44);
      this.groupBox2.Controls.Add((Control) this.Party_member);
      this.groupBox2.Controls.Add((Control) this.label35);
      this.groupBox2.Controls.Add((Control) this.Info);
      this.groupBox2.Controls.Add((Control) this.label32);
      this.groupBox2.Controls.Add((Control) this.DominationPoint);
      this.groupBox2.Controls.Add((Control) this.label31);
      this.groupBox2.Controls.Add((Control) this.Domination1);
      this.groupBox2.Controls.Add((Control) this.label30);
      this.groupBox2.Controls.Add((Control) this.Domination0);
      this.groupBox2.Controls.Add((Control) this.label6);
      this.groupBox2.Controls.Add((Control) this.Type);
      this.groupBox2.Controls.Add((Control) this.label5);
      this.groupBox2.Controls.Add((Control) this.CP);
      this.groupBox2.Controls.Add((Control) this.label4);
      this.groupBox2.Controls.Add((Control) this.Level);
      this.groupBox2.Controls.Add((Control) this.label3);
      this.groupBox2.Controls.Add((Control) this.Difficulty);
      this.groupBox2.Controls.Add((Control) this.label2);
      this.groupBox2.Controls.Add((Control) this.Zone_Id);
      this.groupBox2.Controls.Add((Control) this.label1);
      this.groupBox2.Controls.Add((Control) this.index);
      this.groupBox2.Controls.Add((Control) this.label21);
      this.groupBox2.Location = new Point(292, 13);
      this.groupBox2.Margin = new Padding(4);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Padding = new Padding(4);
      this.groupBox2.Size = new Size(928, 91);
      this.groupBox2.TabIndex = 24;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "Party Dungeon Information";
      this.Time.Location = new Point(632, 59);
      this.Time.Margin = new Padding(4);
      this.Time.Name = "Time";
      this.Time.Size = new Size(65, 22);
      this.Time.TabIndex = 42;
      this.label44.AutoSize = true;
      this.label44.Location = new Point(583, 62);
      this.label44.Margin = new Padding(4, 0, 4, 0);
      this.label44.Name = "label44";
      this.label44.Size = new Size(47, 16);
      this.label44.TabIndex = 41;
      this.label44.Text = "Time : ";
      this.Party_member.Location = new Point(510, 59);
      this.Party_member.Margin = new Padding(4);
      this.Party_member.Name = "Party_member";
      this.Party_member.Size = new Size(65, 22);
      this.Party_member.TabIndex = 40;
      this.label35.AutoSize = true;
      this.label35.Location = new Point(402, 62);
      this.label35.Margin = new Padding(4, 0, 4, 0);
      this.label35.Name = "label35";
      this.label35.Size = new Size(100, 16);
      this.label35.TabIndex = 39;
      this.label35.Text = "Party Member : ";
      this.Info.Location = new Point(747, 59);
      this.Info.Margin = new Padding(4);
      this.Info.Name = "Info";
      this.Info.Size = new Size(172, 22);
      this.Info.TabIndex = 38;
      this.label32.AutoSize = true;
      this.label32.Location = new Point(704, 62);
      this.label32.Margin = new Padding(4, 0, 4, 0);
      this.label32.Name = "label32";
      this.label32.Size = new Size(37, 16);
      this.label32.TabIndex = 37;
      this.label32.Text = "Info : ";
      this.DominationPoint.Location = new Point(854, 19);
      this.DominationPoint.Margin = new Padding(4);
      this.DominationPoint.Name = "DominationPoint";
      this.DominationPoint.Size = new Size(65, 22);
      this.DominationPoint.TabIndex = 36;
      this.DominationPoint.TextChanged += new EventHandler(this.textBox23_TextChanged);
      this.label31.AutoSize = true;
      this.label31.Location = new Point(728, 23);
      this.label31.Margin = new Padding(4, 0, 4, 0);
      this.label31.Name = "label31";
      this.label31.Size = new Size(118, 16);
      this.label31.TabIndex = 35;
      this.label31.Text = "domination_point : ";
      this.Domination1.Location = new Point(655, 20);
      this.Domination1.Margin = new Padding(4);
      this.Domination1.Name = "Domination1";
      this.Domination1.Size = new Size(65, 22);
      this.Domination1.TabIndex = 34;
      this.label30.AutoSize = true;
      this.label30.Location = new Point(565, 25);
      this.label30.Margin = new Padding(4, 0, 4, 0);
      this.label30.Name = "label30";
      this.label30.Size = new Size(89, 16);
      this.label30.TabIndex = 33;
      this.label30.Text = "domination1 : ";
      this.Domination0.Location = new Point(492, 20);
      this.Domination0.Margin = new Padding(4);
      this.Domination0.Name = "Domination0";
      this.Domination0.Size = new Size(65, 22);
      this.Domination0.TabIndex = 32;
      this.label6.AutoSize = true;
      this.label6.Location = new Point(402, 26);
      this.label6.Margin = new Padding(4, 0, 4, 0);
      this.label6.Name = "label6";
      this.label6.Size = new Size(89, 16);
      this.label6.TabIndex = 31;
      this.label6.Text = "domination0 : ";
      this.Type.Enabled = false;
      this.Type.Location = new Point(329, 23);
      this.Type.Margin = new Padding(4);
      this.Type.Name = "Type";
      this.Type.Size = new Size(65, 22);
      this.Type.TabIndex = 29;
      this.Type.TextAlign = HorizontalAlignment.Center;
      this.label5.AutoSize = true;
      this.label5.Location = new Point(272, 26);
      this.label5.Margin = new Padding(4, 0, 4, 0);
      this.label5.Name = "label5";
      this.label5.Size = new Size(48, 16);
      this.label5.TabIndex = 30;
      this.label5.Text = "Type : ";
      this.CP.Location = new Point(329, 59);
      this.CP.Margin = new Padding(4);
      this.CP.Name = "CP";
      this.CP.Size = new Size(65, 22);
      this.CP.TabIndex = 28;
      this.label4.AutoSize = true;
      this.label4.Location = new Point(286, 62);
      this.label4.Margin = new Padding(4, 0, 4, 0);
      this.label4.Name = "label4";
      this.label4.Size = new Size(34, 16);
      this.label4.TabIndex = 27;
      this.label4.Text = "CP : ";
      this.Level.Enabled = false;
      this.Level.Location = new Point(205, 62);
      this.Level.Margin = new Padding(4);
      this.Level.Name = "Level";
      this.Level.Size = new Size(57, 22);
      this.Level.TabIndex = 25;
      this.Level.TextAlign = HorizontalAlignment.Center;
      this.label3.AutoSize = true;
      this.label3.Location = new Point(152, 65);
      this.label3.Margin = new Padding(4, 0, 4, 0);
      this.label3.Name = "label3";
      this.label3.Size = new Size(49, 16);
      this.label3.TabIndex = 26;
      this.label3.Text = "Level : ";
      this.Difficulty.Enabled = false;
      this.Difficulty.Location = new Point(205, 26);
      this.Difficulty.Margin = new Padding(4);
      this.Difficulty.Name = "Difficulty";
      this.Difficulty.Size = new Size(57, 22);
      this.Difficulty.TabIndex = 23;
      this.Difficulty.TextAlign = HorizontalAlignment.Center;
      this.label2.AutoSize = true;
      this.label2.Location = new Point(136, 29);
      this.label2.Margin = new Padding(4, 0, 4, 0);
      this.label2.Name = "label2";
      this.label2.Size = new Size(65, 16);
      this.label2.TabIndex = 24;
      this.label2.Text = "Difficulty : ";
      this.Zone_Id.Enabled = false;
      this.Zone_Id.Location = new Point(71, 62);
      this.Zone_Id.Margin = new Padding(4);
      this.Zone_Id.Name = "Zone_Id";
      this.Zone_Id.Size = new Size(57, 22);
      this.Zone_Id.TabIndex = 21;
      this.Zone_Id.TextAlign = HorizontalAlignment.Center;
      this.label1.AutoSize = true;
      this.label1.Location = new Point(3, 65);
      this.label1.Margin = new Padding(4, 0, 4, 0);
      this.label1.Name = "label1";
      this.label1.Size = new Size(61, 16);
      this.label1.TabIndex = 22;
      this.label1.Text = "Zone Id : ";
      this.index.Enabled = false;
      this.index.Location = new Point(71, 29);
      this.index.Margin = new Padding(4);
      this.index.Name = "index";
      this.index.Size = new Size(57, 22);
      this.index.TabIndex = 19;
      this.index.TextAlign = HorizontalAlignment.Center;
      this.label21.AutoSize = true;
      this.label21.Location = new Point(15, 32);
      this.label21.Margin = new Padding(4, 0, 4, 0);
      this.label21.Name = "label21";
      this.label21.Size = new Size(48, 16);
      this.label21.TabIndex = 20;
      this.label21.Text = "Index : ";
      this.groupBox7.Controls.Add((Control) this.bt_refresh);
      this.groupBox7.Controls.Add((Control) this.bt_update);
      this.groupBox7.Location = new Point(763, 735);
      this.groupBox7.Margin = new Padding(4);
      this.groupBox7.Name = "groupBox7";
      this.groupBox7.Padding = new Padding(4);
      this.groupBox7.Size = new Size(457, 64);
      this.groupBox7.TabIndex = 25;
      this.groupBox7.TabStop = false;
      this.groupBox7.Text = "Working";
      this.bt_refresh.BackColor = Color.MistyRose;
      this.bt_refresh.FlatStyle = FlatStyle.Flat;
      this.bt_refresh.Image = (Image) Resources.refresh;
      this.bt_refresh.ImageAlign = ContentAlignment.MiddleLeft;
      this.bt_refresh.Location = new Point(290, 21);
      this.bt_refresh.Margin = new Padding(4);
      this.bt_refresh.Name = "bt_refresh";
      this.bt_refresh.Size = new Size(108, 33);
      this.bt_refresh.TabIndex = 11;
      this.bt_refresh.Text = "    Reset";
      this.bt_refresh.UseVisualStyleBackColor = false;
      this.bt_refresh.Click += new EventHandler(this.bt_refresh_Click);
      this.bt_update.BackColor = Color.LightCyan;
      this.bt_update.FlatStyle = FlatStyle.Flat;
      this.bt_update.Image = (Image) Resources._08;
      this.bt_update.ImageAlign = ContentAlignment.MiddleLeft;
      this.bt_update.Location = new Point(97, 21);
      this.bt_update.Margin = new Padding(4);
      this.bt_update.Name = "bt_update";
      this.bt_update.Size = new Size(108, 33);
      this.bt_update.TabIndex = 12;
      this.bt_update.Text = "   Update";
      this.bt_update.UseVisualStyleBackColor = false;
      this.bt_update.Click += new EventHandler(this.button9_Click);
      this.groupBox3.BackColor = Color.Honeydew;
      this.groupBox3.Controls.Add((Control) this.checkBox5);
      this.groupBox3.Controls.Add((Control) this.checkBox4);
      this.groupBox3.Controls.Add((Control) this.checkBox3);
      this.groupBox3.Controls.Add((Control) this.checkBox2);
      this.groupBox3.Controls.Add((Control) this.checkBox1);
      this.groupBox3.Controls.Add((Control) this.r_t_id5_count);
      this.groupBox3.Controls.Add((Control) this.label18);
      this.groupBox3.Controls.Add((Control) this.bt_r_t_id5);
      this.groupBox3.Controls.Add((Control) this.r_t_id5_name);
      this.groupBox3.Controls.Add((Control) this.r_t_id5);
      this.groupBox3.Controls.Add((Control) this.pictureBox7);
      this.groupBox3.Controls.Add((Control) this.r_t_id4_count);
      this.groupBox3.Controls.Add((Control) this.label15);
      this.groupBox3.Controls.Add((Control) this.bt_r_t_id4);
      this.groupBox3.Controls.Add((Control) this.r_t_id4_name);
      this.groupBox3.Controls.Add((Control) this.r_t_id4);
      this.groupBox3.Controls.Add((Control) this.pictureBox6);
      this.groupBox3.Controls.Add((Control) this.r_t_id3_count);
      this.groupBox3.Controls.Add((Control) this.label12);
      this.groupBox3.Controls.Add((Control) this.bt_r_t_id3);
      this.groupBox3.Controls.Add((Control) this.r_t_id3_name);
      this.groupBox3.Controls.Add((Control) this.r_t_id3);
      this.groupBox3.Controls.Add((Control) this.pictureBox5);
      this.groupBox3.Controls.Add((Control) this.r_t_id2_count);
      this.groupBox3.Controls.Add((Control) this.label13);
      this.groupBox3.Controls.Add((Control) this.bt_r_t_id2);
      this.groupBox3.Controls.Add((Control) this.r_t_id2_name);
      this.groupBox3.Controls.Add((Control) this.r_t_id2);
      this.groupBox3.Controls.Add((Control) this.pictureBox4);
      this.groupBox3.Controls.Add((Control) this.r_t_id1_count);
      this.groupBox3.Controls.Add((Control) this.label14);
      this.groupBox3.Controls.Add((Control) this.bt_r_t_id1);
      this.groupBox3.Controls.Add((Control) this.r_t_id1_name);
      this.groupBox3.Controls.Add((Control) this.r_t_id1);
      this.groupBox3.Controls.Add((Control) this.pictureBox3);
      this.groupBox3.Controls.Add((Control) this.label19);
      this.groupBox3.Controls.Add((Control) this.label20);
      this.groupBox3.Controls.Add((Control) this.label16);
      this.groupBox3.Controls.Add((Control) this.label17);
      this.groupBox3.Controls.Add((Control) this.label24);
      this.groupBox3.Controls.Add((Control) this.label25);
      this.groupBox3.Controls.Add((Control) this.label26);
      this.groupBox3.Controls.Add((Control) this.label27);
      this.groupBox3.Controls.Add((Control) this.label28);
      this.groupBox3.Controls.Add((Control) this.label29);
      this.groupBox3.Location = new Point(291, 239);
      this.groupBox3.Margin = new Padding(4);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Padding = new Padding(4);
      this.groupBox3.Size = new Size(457, 478);
      this.groupBox3.TabIndex = 26;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "Reward Items";
      this.checkBox5.AutoSize = true;
      this.checkBox5.Location = new Point(15, 381);
      this.checkBox5.Margin = new Padding(4);
      this.checkBox5.Name = "checkBox5";
      this.checkBox5.Size = new Size(138, 20);
      this.checkBox5.TabIndex = 69;
      this.checkBox5.Text = "Item Reward No. 5";
      this.checkBox5.UseVisualStyleBackColor = true;
      this.checkBox4.AutoSize = true;
      this.checkBox4.Location = new Point(15, 287);
      this.checkBox4.Margin = new Padding(4);
      this.checkBox4.Name = "checkBox4";
      this.checkBox4.Size = new Size(138, 20);
      this.checkBox4.TabIndex = 68;
      this.checkBox4.Text = "Item Reward No. 4";
      this.checkBox4.UseVisualStyleBackColor = true;
      this.checkBox3.AutoSize = true;
      this.checkBox3.Location = new Point(10, 194);
      this.checkBox3.Margin = new Padding(4);
      this.checkBox3.Name = "checkBox3";
      this.checkBox3.Size = new Size(138, 20);
      this.checkBox3.TabIndex = 67;
      this.checkBox3.Text = "Item Reward No. 3";
      this.checkBox3.UseVisualStyleBackColor = true;
      this.checkBox2.AutoSize = true;
      this.checkBox2.Location = new Point(9, 109);
      this.checkBox2.Margin = new Padding(4);
      this.checkBox2.Name = "checkBox2";
      this.checkBox2.Size = new Size(138, 20);
      this.checkBox2.TabIndex = 66;
      this.checkBox2.Text = "Item Reward No. 2";
      this.checkBox2.UseVisualStyleBackColor = true;
      this.checkBox1.AutoSize = true;
      this.checkBox1.Location = new Point(9, 22);
      this.checkBox1.Margin = new Padding(4);
      this.checkBox1.Name = "checkBox1";
      this.checkBox1.Size = new Size(138, 20);
      this.checkBox1.TabIndex = 65;
      this.checkBox1.Text = "Item Reward No. 1";
      this.checkBox1.UseVisualStyleBackColor = true;
      this.r_t_id5_count.Location = new Point(306, 401);
      this.r_t_id5_count.Margin = new Padding(4);
      this.r_t_id5_count.Name = "r_t_id5_count";
      this.r_t_id5_count.Size = new Size(87, 22);
      this.r_t_id5_count.TabIndex = 59;
      this.label18.AutoSize = true;
      this.label18.Location = new Point(249, 406);
      this.label18.Margin = new Padding(4, 0, 4, 0);
      this.label18.Name = "label18";
      this.label18.Size = new Size(39, 16);
      this.label18.TabIndex = 58;
      this.label18.Text = "Q'ty : ";
      this.bt_r_t_id5.BackgroundImage = (Image) Resources.search__5_;
      this.bt_r_t_id5.BackgroundImageLayout = ImageLayout.None;
      this.bt_r_t_id5.Location = new Point(399, 398);
      this.bt_r_t_id5.Margin = new Padding(4);
      this.bt_r_t_id5.Name = "bt_r_t_id5";
      this.bt_r_t_id5.Size = new Size(36, 31);
      this.bt_r_t_id5.TabIndex = 53;
      this.bt_r_t_id5.UseVisualStyleBackColor = true;
      this.bt_r_t_id5.Click += new EventHandler(this.button7_Click);
      this.r_t_id5_name.Enabled = false;
      this.r_t_id5_name.Location = new Point(154, 437);
      this.r_t_id5_name.Margin = new Padding(4);
      this.r_t_id5_name.Name = "r_t_id5_name";
      this.r_t_id5_name.Size = new Size(297, 22);
      this.r_t_id5_name.TabIndex = 55;
      this.r_t_id5.Enabled = false;
      this.r_t_id5.Location = new Point(154, 401);
      this.r_t_id5.Margin = new Padding(4);
      this.r_t_id5.Name = "r_t_id5";
      this.r_t_id5.Size = new Size(87, 22);
      this.r_t_id5.TabIndex = 54;
      this.r_t_id5.TextChanged += new EventHandler(this.r_t_id5_TextChanged);
      this.pictureBox7.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox7.Location = new Point(15, 409);
      this.pictureBox7.Margin = new Padding(4);
      this.pictureBox7.Name = "pictureBox7";
      this.pictureBox7.Size = new Size(55, 49);
      this.pictureBox7.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pictureBox7.TabIndex = 52;
      this.pictureBox7.TabStop = false;
      this.r_t_id4_count.Location = new Point(306, 308);
      this.r_t_id4_count.Margin = new Padding(4);
      this.r_t_id4_count.Name = "r_t_id4_count";
      this.r_t_id4_count.Size = new Size(87, 22);
      this.r_t_id4_count.TabIndex = 51;
      this.label15.AutoSize = true;
      this.label15.Location = new Point(248, 313);
      this.label15.Margin = new Padding(4, 0, 4, 0);
      this.label15.Name = "label15";
      this.label15.Size = new Size(39, 16);
      this.label15.TabIndex = 50;
      this.label15.Text = "Q'ty : ";
      this.bt_r_t_id4.BackgroundImage = (Image) Resources.search__5_;
      this.bt_r_t_id4.BackgroundImageLayout = ImageLayout.None;
      this.bt_r_t_id4.Location = new Point(399, 299);
      this.bt_r_t_id4.Margin = new Padding(4);
      this.bt_r_t_id4.Name = "bt_r_t_id4";
      this.bt_r_t_id4.Size = new Size(36, 31);
      this.bt_r_t_id4.TabIndex = 45;
      this.bt_r_t_id4.UseVisualStyleBackColor = true;
      this.bt_r_t_id4.Click += new EventHandler(this.button10_Click);
      this.r_t_id4_name.Enabled = false;
      this.r_t_id4_name.Location = new Point(154, 344);
      this.r_t_id4_name.Margin = new Padding(4);
      this.r_t_id4_name.Name = "r_t_id4_name";
      this.r_t_id4_name.Size = new Size(297, 22);
      this.r_t_id4_name.TabIndex = 47;
      this.r_t_id4.Enabled = false;
      this.r_t_id4.Location = new Point(154, 308);
      this.r_t_id4.Margin = new Padding(4);
      this.r_t_id4.Name = "r_t_id4";
      this.r_t_id4.Size = new Size(87, 22);
      this.r_t_id4.TabIndex = 46;
      this.r_t_id4.TextChanged += new EventHandler(this.r_t_id4_TextChanged);
      this.pictureBox6.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox6.Location = new Point(15, 315);
      this.pictureBox6.Margin = new Padding(4);
      this.pictureBox6.Name = "pictureBox6";
      this.pictureBox6.Size = new Size(55, 49);
      this.pictureBox6.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pictureBox6.TabIndex = 44;
      this.pictureBox6.TabStop = false;
      this.r_t_id3_count.Location = new Point(302, 215);
      this.r_t_id3_count.Margin = new Padding(4);
      this.r_t_id3_count.Name = "r_t_id3_count";
      this.r_t_id3_count.Size = new Size(87, 22);
      this.r_t_id3_count.TabIndex = 43;
      this.label12.AutoSize = true;
      this.label12.Location = new Point(245, 220);
      this.label12.Margin = new Padding(4, 0, 4, 0);
      this.label12.Name = "label12";
      this.label12.Size = new Size(39, 16);
      this.label12.TabIndex = 42;
      this.label12.Text = "Q'ty : ";
      this.bt_r_t_id3.BackgroundImage = (Image) Resources.search__5_;
      this.bt_r_t_id3.BackgroundImageLayout = ImageLayout.None;
      this.bt_r_t_id3.Location = new Point(395, 211);
      this.bt_r_t_id3.Margin = new Padding(4);
      this.bt_r_t_id3.Name = "bt_r_t_id3";
      this.bt_r_t_id3.Size = new Size(36, 31);
      this.bt_r_t_id3.TabIndex = 37;
      this.bt_r_t_id3.UseVisualStyleBackColor = true;
      this.bt_r_t_id3.Click += new EventHandler(this.button13_Click);
      this.r_t_id3_name.Enabled = false;
      this.r_t_id3_name.Location = new Point(150, 251);
      this.r_t_id3_name.Margin = new Padding(4);
      this.r_t_id3_name.Name = "r_t_id3_name";
      this.r_t_id3_name.Size = new Size(297, 22);
      this.r_t_id3_name.TabIndex = 39;
      this.r_t_id3.Enabled = false;
      this.r_t_id3.Location = new Point(150, 215);
      this.r_t_id3.Margin = new Padding(4);
      this.r_t_id3.Name = "r_t_id3";
      this.r_t_id3.Size = new Size(87, 22);
      this.r_t_id3.TabIndex = 38;
      this.r_t_id3.TextChanged += new EventHandler(this.r_t_id3_TextChanged);
      this.pictureBox5.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox5.Location = new Point(11, 222);
      this.pictureBox5.Margin = new Padding(4);
      this.pictureBox5.Name = "pictureBox5";
      this.pictureBox5.Size = new Size(55, 49);
      this.pictureBox5.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pictureBox5.TabIndex = 36;
      this.pictureBox5.TabStop = false;
      this.r_t_id2_count.Location = new Point(300, 130);
      this.r_t_id2_count.Margin = new Padding(4);
      this.r_t_id2_count.Name = "r_t_id2_count";
      this.r_t_id2_count.Size = new Size(87, 22);
      this.r_t_id2_count.TabIndex = 35;
      this.label13.AutoSize = true;
      this.label13.Location = new Point(242, 135);
      this.label13.Margin = new Padding(4, 0, 4, 0);
      this.label13.Name = "label13";
      this.label13.Size = new Size(39, 16);
      this.label13.TabIndex = 34;
      this.label13.Text = "Q'ty : ";
      this.bt_r_t_id2.BackgroundImage = (Image) Resources.search__5_;
      this.bt_r_t_id2.BackgroundImageLayout = ImageLayout.None;
      this.bt_r_t_id2.Location = new Point(393, 128);
      this.bt_r_t_id2.Margin = new Padding(4);
      this.bt_r_t_id2.Name = "bt_r_t_id2";
      this.bt_r_t_id2.Size = new Size(36, 31);
      this.bt_r_t_id2.TabIndex = 29;
      this.bt_r_t_id2.UseVisualStyleBackColor = true;
      this.bt_r_t_id2.Click += new EventHandler(this.button14_Click);
      this.r_t_id2_name.Enabled = false;
      this.r_t_id2_name.Location = new Point(148, 166);
      this.r_t_id2_name.Margin = new Padding(4);
      this.r_t_id2_name.Name = "r_t_id2_name";
      this.r_t_id2_name.Size = new Size(297, 22);
      this.r_t_id2_name.TabIndex = 31;
      this.r_t_id2.Enabled = false;
      this.r_t_id2.Location = new Point(148, 130);
      this.r_t_id2.Margin = new Padding(4);
      this.r_t_id2.Name = "r_t_id2";
      this.r_t_id2.Size = new Size(87, 22);
      this.r_t_id2.TabIndex = 30;
      this.r_t_id2.TextChanged += new EventHandler(this.r_t_id2_TextChanged);
      this.pictureBox4.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox4.Location = new Point(9, 137);
      this.pictureBox4.Margin = new Padding(4);
      this.pictureBox4.Name = "pictureBox4";
      this.pictureBox4.Size = new Size(55, 49);
      this.pictureBox4.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pictureBox4.TabIndex = 28;
      this.pictureBox4.TabStop = false;
      this.r_t_id1_count.Location = new Point(300, 43);
      this.r_t_id1_count.Margin = new Padding(4);
      this.r_t_id1_count.Name = "r_t_id1_count";
      this.r_t_id1_count.Size = new Size(87, 22);
      this.r_t_id1_count.TabIndex = 27;
      this.label14.AutoSize = true;
      this.label14.Location = new Point(243, 48);
      this.label14.Margin = new Padding(4, 0, 4, 0);
      this.label14.Name = "label14";
      this.label14.Size = new Size(39, 16);
      this.label14.TabIndex = 26;
      this.label14.Text = "Q'ty : ";
      this.bt_r_t_id1.BackgroundImage = (Image) Resources.search__5_;
      this.bt_r_t_id1.BackgroundImageLayout = ImageLayout.None;
      this.bt_r_t_id1.Location = new Point(393, 41);
      this.bt_r_t_id1.Margin = new Padding(4);
      this.bt_r_t_id1.Name = "bt_r_t_id1";
      this.bt_r_t_id1.Size = new Size(36, 31);
      this.bt_r_t_id1.TabIndex = 21;
      this.bt_r_t_id1.UseVisualStyleBackColor = true;
      this.bt_r_t_id1.Click += new EventHandler(this.button15_Click);
      this.r_t_id1_name.Enabled = false;
      this.r_t_id1_name.Location = new Point(148, 79);
      this.r_t_id1_name.Margin = new Padding(4);
      this.r_t_id1_name.Name = "r_t_id1_name";
      this.r_t_id1_name.Size = new Size(297, 22);
      this.r_t_id1_name.TabIndex = 23;
      this.r_t_id1.Enabled = false;
      this.r_t_id1.Location = new Point(148, 43);
      this.r_t_id1.Margin = new Padding(4);
      this.r_t_id1.Name = "r_t_id1";
      this.r_t_id1.Size = new Size(87, 22);
      this.r_t_id1.TabIndex = 22;
      this.r_t_id1.TextChanged += new EventHandler(this.r_t_id1_TextChanged);
      this.pictureBox3.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox3.Location = new Point(9, 50);
      this.pictureBox3.Margin = new Padding(4);
      this.pictureBox3.Name = "pictureBox3";
      this.pictureBox3.Size = new Size(55, 49);
      this.pictureBox3.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pictureBox3.TabIndex = 20;
      this.pictureBox3.TabStop = false;
      this.label19.AutoSize = true;
      this.label19.Location = new Point(81, 442);
      this.label19.Margin = new Padding(4, 0, 4, 0);
      this.label19.Name = "label19";
      this.label19.Size = new Size(50, 16);
      this.label19.TabIndex = 57;
      this.label19.Text = "Name :";
      this.label20.AutoSize = true;
      this.label20.Location = new Point(81, 406);
      this.label20.Margin = new Padding(4, 0, 4, 0);
      this.label20.Name = "label20";
      this.label20.Size = new Size(29, 16);
      this.label20.TabIndex = 56;
      this.label20.Text = "ID : ";
      this.label16.AutoSize = true;
      this.label16.Location = new Point(80, 349);
      this.label16.Margin = new Padding(4, 0, 4, 0);
      this.label16.Name = "label16";
      this.label16.Size = new Size(50, 16);
      this.label16.TabIndex = 49;
      this.label16.Text = "Name :";
      this.label17.AutoSize = true;
      this.label17.Location = new Point(80, 313);
      this.label17.Margin = new Padding(4, 0, 4, 0);
      this.label17.Name = "label17";
      this.label17.Size = new Size(29, 16);
      this.label17.TabIndex = 48;
      this.label17.Text = "ID : ";
      this.label24.AutoSize = true;
      this.label24.Location = new Point(77, 256);
      this.label24.Margin = new Padding(4, 0, 4, 0);
      this.label24.Name = "label24";
      this.label24.Size = new Size(50, 16);
      this.label24.TabIndex = 41;
      this.label24.Text = "Name :";
      this.label25.AutoSize = true;
      this.label25.Location = new Point(77, 220);
      this.label25.Margin = new Padding(4, 0, 4, 0);
      this.label25.Name = "label25";
      this.label25.Size = new Size(29, 16);
      this.label25.TabIndex = 40;
      this.label25.Text = "ID : ";
      this.label26.AutoSize = true;
      this.label26.Location = new Point(74, 171);
      this.label26.Margin = new Padding(4, 0, 4, 0);
      this.label26.Name = "label26";
      this.label26.Size = new Size(50, 16);
      this.label26.TabIndex = 33;
      this.label26.Text = "Name :";
      this.label27.AutoSize = true;
      this.label27.Location = new Point(74, 135);
      this.label27.Margin = new Padding(4, 0, 4, 0);
      this.label27.Name = "label27";
      this.label27.Size = new Size(29, 16);
      this.label27.TabIndex = 32;
      this.label27.Text = "ID : ";
      this.label28.AutoSize = true;
      this.label28.Location = new Point(75, 84);
      this.label28.Margin = new Padding(4, 0, 4, 0);
      this.label28.Name = "label28";
      this.label28.Size = new Size(50, 16);
      this.label28.TabIndex = 25;
      this.label28.Text = "Name :";
      this.label29.AutoSize = true;
      this.label29.Location = new Point(75, 48);
      this.label29.Margin = new Padding(4, 0, 4, 0);
      this.label29.Name = "label29";
      this.label29.Size = new Size(29, 16);
      this.label29.TabIndex = 24;
      this.label29.Text = "ID : ";
      this.listBox1.FormattingEnabled = true;
      this.listBox1.ItemHeight = 16;
      this.listBox1.Location = new Point(16, 39);
      this.listBox1.Margin = new Padding(4);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new Size(265, 676);
      this.listBox1.TabIndex = 27;
      this.listBox1.SelectedIndexChanged += new EventHandler(this.ListBox1_SelectedIndexChanged);
      this.groupBox1.BackColor = Color.LightSteelBlue;
      this.groupBox1.Controls.Add((Control) this.bt_title);
      this.groupBox1.Controls.Add((Control) this.Title_name);
      this.groupBox1.Controls.Add((Control) this.Title_Id);
      this.groupBox1.Controls.Add((Control) this.pictureBox9);
      this.groupBox1.Controls.Add((Control) this.label36);
      this.groupBox1.Controls.Add((Control) this.label37);
      this.groupBox1.Location = new Point(763, 112);
      this.groupBox1.Margin = new Padding(4);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Padding = new Padding(4);
      this.groupBox1.Size = new Size(457, 119);
      this.groupBox1.TabIndex = 28;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Title Item";
      this.bt_title.Image = (Image) Resources.search__5_;
      this.bt_title.Location = new Point(405, 27);
      this.bt_title.Margin = new Padding(4);
      this.bt_title.Name = "bt_title";
      this.bt_title.Size = new Size(40, 33);
      this.bt_title.TabIndex = 13;
      this.bt_title.UseVisualStyleBackColor = true;
      this.Title_name.Enabled = false;
      this.Title_name.Location = new Point(148, 71);
      this.Title_name.Margin = new Padding(4);
      this.Title_name.Name = "Title_name";
      this.Title_name.Size = new Size(297, 22);
      this.Title_name.TabIndex = 15;
      this.Title_Id.Enabled = false;
      this.Title_Id.Location = new Point(150, 34);
      this.Title_Id.Margin = new Padding(4);
      this.Title_Id.Name = "Title_Id";
      this.Title_Id.Size = new Size(85, 22);
      this.Title_Id.TabIndex = 14;
      this.pictureBox9.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox9.Location = new Point(15, 42);
      this.pictureBox9.Margin = new Padding(4);
      this.pictureBox9.Name = "pictureBox9";
      this.pictureBox9.Size = new Size(55, 49);
      this.pictureBox9.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pictureBox9.TabIndex = 10;
      this.pictureBox9.TabStop = false;
      this.label36.AutoSize = true;
      this.label36.Location = new Point(80, 75);
      this.label36.Margin = new Padding(4, 0, 4, 0);
      this.label36.Name = "label36";
      this.label36.Size = new Size(50, 16);
      this.label36.TabIndex = 17;
      this.label36.Text = "Name :";
      this.label37.AutoSize = true;
      this.label37.Location = new Point(80, 39);
      this.label37.Margin = new Padding(4, 0, 4, 0);
      this.label37.Name = "label37";
      this.label37.Size = new Size(29, 16);
      this.label37.TabIndex = 16;
      this.label37.Text = "ID : ";
      this.groupBox5.BackColor = Color.LightYellow;
      this.groupBox5.Controls.Add((Control) this.Box_Count);
      this.groupBox5.Controls.Add((Control) this.label38);
      this.groupBox5.Controls.Add((Control) this.bt_box);
      this.groupBox5.Controls.Add((Control) this.Box_name);
      this.groupBox5.Controls.Add((Control) this.Box_Id);
      this.groupBox5.Controls.Add((Control) this.pictureBox10);
      this.groupBox5.Controls.Add((Control) this.label39);
      this.groupBox5.Controls.Add((Control) this.label40);
      this.groupBox5.Location = new Point(763, 249);
      this.groupBox5.Margin = new Padding(4);
      this.groupBox5.Name = "groupBox5";
      this.groupBox5.Padding = new Padding(4);
      this.groupBox5.Size = new Size(457, 119);
      this.groupBox5.TabIndex = 29;
      this.groupBox5.TabStop = false;
      this.groupBox5.Text = "Box Item";
      this.Box_Count.Location = new Point(290, 32);
      this.Box_Count.Margin = new Padding(4);
      this.Box_Count.Name = "Box_Count";
      this.Box_Count.Size = new Size(97, 22);
      this.Box_Count.TabIndex = 19;
      this.label38.AutoSize = true;
      this.label38.Location = new Point(242, 38);
      this.label38.Margin = new Padding(4, 0, 4, 0);
      this.label38.Name = "label38";
      this.label38.Size = new Size(39, 16);
      this.label38.TabIndex = 18;
      this.label38.Text = "Q'ty : ";
      this.bt_box.Image = (Image) Resources.search__5_;
      this.bt_box.Location = new Point(405, 27);
      this.bt_box.Margin = new Padding(4);
      this.bt_box.Name = "bt_box";
      this.bt_box.Size = new Size(40, 33);
      this.bt_box.TabIndex = 13;
      this.bt_box.UseVisualStyleBackColor = true;
      this.Box_name.Enabled = false;
      this.Box_name.Location = new Point(148, 71);
      this.Box_name.Margin = new Padding(4);
      this.Box_name.Name = "Box_name";
      this.Box_name.Size = new Size(297, 22);
      this.Box_name.TabIndex = 15;
      this.Box_Id.Enabled = false;
      this.Box_Id.Location = new Point(150, 34);
      this.Box_Id.Margin = new Padding(4);
      this.Box_Id.Name = "Box_Id";
      this.Box_Id.Size = new Size(85, 22);
      this.Box_Id.TabIndex = 14;
      this.pictureBox10.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox10.Location = new Point(15, 42);
      this.pictureBox10.Margin = new Padding(4);
      this.pictureBox10.Name = "pictureBox10";
      this.pictureBox10.Size = new Size(55, 49);
      this.pictureBox10.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pictureBox10.TabIndex = 10;
      this.pictureBox10.TabStop = false;
      this.label39.AutoSize = true;
      this.label39.Location = new Point(80, 75);
      this.label39.Margin = new Padding(4, 0, 4, 0);
      this.label39.Name = "label39";
      this.label39.Size = new Size(50, 16);
      this.label39.TabIndex = 17;
      this.label39.Text = "Name :";
      this.label40.AutoSize = true;
      this.label40.Location = new Point(80, 39);
      this.label40.Margin = new Padding(4, 0, 4, 0);
      this.label40.Name = "label40";
      this.label40.Size = new Size(29, 16);
      this.label40.TabIndex = 16;
      this.label40.Text = "ID : ";
      this.AutoScaleDimensions = new SizeF(8f, 16f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.BackColor = Color.White;
      this.ClientSize = new Size(1228, 802);
      this.Controls.Add((Control) this.groupBox5);
      this.Controls.Add((Control) this.groupBox1);
      this.Controls.Add((Control) this.listBox1);
      this.Controls.Add((Control) this.groupBox3);
      this.Controls.Add((Control) this.groupBox7);
      this.Controls.Add((Control) this.groupBox2);
      this.Controls.Add((Control) this.groupBox4);
      this.Controls.Add((Control) this.Boss1_npc);
      this.Controls.Add((Control) this.textBox7);
      this.Controls.Add((Control) this.textBox4);
      this.Controls.Add((Control) this.textBox3);
      this.Controls.Add((Control) this.textBox2);
      this.Controls.Add((Control) this.textBox1);
      this.Controls.Add((Control) this.menuStrip1);
      this.FormBorderStyle = FormBorderStyle.Fixed3D;
      this.MainMenuStrip = this.menuStrip1;
      this.Margin = new Padding(4);
      this.MaximizeBox = false;
      this.Name = nameof (PartyExpEditions);
      this.Text = "LastChaos Party Dungeon Editor";
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.Boss1_npc.ResumeLayout(false);
      this.Boss1_npc.PerformLayout();
      ((ISupportInitialize) this.pictureBox8).EndInit();
      ((ISupportInitialize) this.pictureBox1).EndInit();
      ((ISupportInitialize) this.pc_npc).EndInit();
      this.groupBox4.ResumeLayout(false);
      this.groupBox4.PerformLayout();
      ((ISupportInitialize) this.pictureBox2).EndInit();
      this.groupBox2.ResumeLayout(false);
      this.groupBox2.PerformLayout();
      this.groupBox7.ResumeLayout(false);
      this.groupBox3.ResumeLayout(false);
      this.groupBox3.PerformLayout();
      ((ISupportInitialize) this.pictureBox7).EndInit();
      ((ISupportInitialize) this.pictureBox6).EndInit();
      ((ISupportInitialize) this.pictureBox5).EndInit();
      ((ISupportInitialize) this.pictureBox4).EndInit();
      ((ISupportInitialize) this.pictureBox3).EndInit();
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      ((ISupportInitialize) this.pictureBox9).EndInit();
      this.groupBox5.ResumeLayout(false);
      this.groupBox5.PerformLayout();
      ((ISupportInitialize) this.pictureBox10).EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();
    }

    private void button11_Click(object sender, EventArgs e)
    {
      this.exportLodHandle.ExportExChange_V4();
    }

    private void button5_Click(object sender, EventArgs e)
    {
      this.a_need_item_idx.Text = "0";
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.a_need_item_idx.Text = itemPicker.ItemIndex.ToString();
    }

    private void bt_npc_Click(object sender, EventArgs e)
    {
      this.Boss_id1.Text = "0";
      MobPicker mobPicker = new MobPicker();
      if (mobPicker.ShowDialog() != DialogResult.OK)
        return;
      this.Boss_id1.Text = mobPicker.MobIndex.ToString();
    }

    private void button15_Click(object sender, EventArgs e)
    {
      this.r_t_id1.Text = "0";
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.r_t_id1.Text = itemPicker.ItemIndex.ToString();
    }

    private void button14_Click(object sender, EventArgs e)
    {
      this.r_t_id2.Text = "0";
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.r_t_id2.Text = itemPicker.ItemIndex.ToString();
    }

    private void button13_Click(object sender, EventArgs e)
    {
      this.r_t_id3.Text = "0";
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.r_t_id3.Text = itemPicker.ItemIndex.ToString();
    }

    private void button10_Click(object sender, EventArgs e)
    {
      this.r_t_id4.Text = "0";
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.r_t_id4.Text = itemPicker.ItemIndex.ToString();
    }

    private void button7_Click(object sender, EventArgs e)
    {
      this.r_t_id5.Text = "0";
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.r_t_id5.Text = itemPicker.ItemIndex.ToString();
    }

    private void bt_refresh_Click(object sender, EventArgs e)
    {
      this.index.Text = "";
      this.Boss_id1.Text = "0";
      this.a_need_item_idx.Text = "0";
      this.a_need_item_count.Text = "0";
      this.r_t_id1.Text = "0";
      this.r_t_id1_count.Text = "0";
      this.r_t_id2.Text = "0";
      this.r_t_id2_count.Text = "0";
      this.r_t_id3.Text = "0";
      this.r_t_id3_count.Text = "0";
      this.r_t_id4.Text = "0";
      this.r_t_id4_count.Text = "0";
      this.r_t_id5.Text = "0";
      this.r_t_id5_count.Text = "0";
    }

    private void settingToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (new LcDevPack_TeamDamonA.Tools.Settings().ShowDialog() == DialogResult.OK)
        ;
    }

    private void textBox23_TextChanged(object sender, EventArgs e)
    {
    }
  }
}
