// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.NewExchange.ExchangeEditor
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
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.NewExchange
{
  public class ExchangeEditor : Form
  {
    public static Connection connection = new Connection();
    private string Host = ExchangeEditor.connection.Settings.SqlHost;
    private string User = ExchangeEditor.connection.Settings.SqlUser;
    private string Password = ExchangeEditor.connection.Settings.SqlPassword;
    private string Database = ExchangeEditor.connection.Settings.SqlDatabase;
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
    private GroupBox gb_npc;
    private Panel panel3DView;
    private Button bt_npc;
    private TextBox tx_npc_name;
    private TextBox tx_npc_id;
    private PictureBox pc_npc;
    private Label label7;
    private Label label8;
    private GroupBox groupBox4;
    private TextBox tb_reward_qty;
    private Label label9;
    private Button button5;
    private TextBox tb_reward_name;
    private TextBox tb_reward_id;
    private PictureBox pictureBox2;
    private Label label10;
    private Label label11;
    private GroupBox groupBox2;
    private TextBox t_exchange_id;
    private Label label21;
    private GroupBox groupBox7;
    private Button button6;
    private Button button9;
    private Button bt_refresh;
    private Button button12;
    private Button button8;
    private Button button11;
    private GroupBox groupBox3;
    private GroupBox groupBox5;
    private TextBox a_name;
    private Label label23;
    private TextBox a_desc;
    private Label label22;
    private CheckBox checkBox5;
    private CheckBox checkBox4;
    private CheckBox checkBox3;
    private CheckBox checkBox2;
    private CheckBox checkBox1;
    private TextBox textBox18;
    private Label label18;
    private Button button7;
    private TextBox textBox19;
    private TextBox r_t_id5;
    private PictureBox pictureBox7;
    private TextBox textBox15;
    private Label label15;
    private Button button10;
    private TextBox textBox16;
    private TextBox r_t_id4;
    private PictureBox pictureBox6;
    private TextBox textBox12;
    private Label label12;
    private Button button13;
    private TextBox textBox13;
    private TextBox r_t_id3;
    private PictureBox pictureBox5;
    private TextBox textBox14;
    private Label label13;
    private Button button14;
    private TextBox textBox17;
    private TextBox r_t_id2;
    private PictureBox pictureBox4;
    private TextBox textBox20;
    private Label label14;
    private Button button15;
    private TextBox textBox21;
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
    public string[] menuArray = new string[2]
    {
      "a_index",
      "a_npc_index"
    };

    public ExchangeEditor()
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

            this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, "SELECT * FROM t_item_exchange WHERE a_enable = 1 ORDER BY a_index ASC;");
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
            string cmdText = "select * FROM t_item_exchange WHERE a_index ='" + this.listBox1.Text + "';";
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
          int32 = mySqlDataReader.GetInt32("result_itemIndex");
          string str2 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("a_npc_index");
          string str3 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("result_itemCount");
          string str4 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("source_itemIndex0");
          string str5 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("source_itemIndex1");
          string str6 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("source_itemIndex2");
          string str7 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("source_itemIndex3");
          string str8 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("source_itemIndex4");
          string str9 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("source_itemCount0");
          string str10 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("source_itemCount1");
          string str11 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("source_itemCount2");
          string str12 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("source_itemCount3");
          string str13 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("source_itemCount4");
          string str14 = int32.ToString();
          this.t_exchange_id.Text = str1;
          this.tb_reward_id.Text = str2;
          this.tx_npc_id.Text = str3;
          this.tb_reward_qty.Text = str4;
          this.r_t_id1.Text = str5;
          this.r_t_id2.Text = str6;
          this.r_t_id3.Text = str7;
          this.r_t_id4.Text = str8;
          this.r_t_id5.Text = str9;
          this.textBox20.Text = str10;
          this.textBox14.Text = str11;
          this.textBox12.Text = str12;
          this.textBox15.Text = str13;
          this.textBox18.Text = str14;
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
      this.pictureBox2.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.tb_reward_id.Text.Trim()));
      this.tb_reward_name.Text = this.databaseHandle.ItemNameFast(int.Parse(this.tb_reward_id.Text.Trim()));
    }

    private void tx_npc_id_TextChanged(object sender, EventArgs e)
    {
      this.pc_npc.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.tx_npc_id.Text.Trim()));
      this.tx_npc_name.Text = this.databaseHandle.MobNameFast(int.Parse(this.tx_npc_id.Text.Trim()));
    }

    private void r_t_id1_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox3.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.r_t_id1.Text.Trim()));
      this.textBox21.Text = this.databaseHandle.ItemNameFast(int.Parse(this.r_t_id1.Text.Trim()));
    }

    private void r_t_id2_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox4.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.r_t_id2.Text.Trim()));
      this.textBox17.Text = this.databaseHandle.ItemNameFast(int.Parse(this.r_t_id2.Text.Trim()));
    }

    private void r_t_id3_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox5.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.r_t_id3.Text.Trim()));
      this.textBox13.Text = this.databaseHandle.ItemNameFast(int.Parse(this.r_t_id3.Text.Trim()));
    }

    private void r_t_id4_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox6.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.r_t_id4.Text.Trim()));
      this.textBox16.Text = this.databaseHandle.ItemNameFast(int.Parse(this.r_t_id4.Text.Trim()));
    }

    private void r_t_id5_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox7.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.r_t_id5.Text.Trim()));
      this.textBox19.Text = this.databaseHandle.ItemNameFast(int.Parse(this.r_t_id5.Text.Trim()));
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
      MySqlCommand mySqlCommand = new MySqlCommand("UPDATE " + this.textBox4.Text + ".t_item_exchange SET  a_npc_index='" + this.tx_npc_id.Text + "', result_itemIndex='" + this.tb_reward_id.Text + "', result_itemCount='" + this.tb_reward_qty.Text + "', source_itemIndex0='" + this.r_t_id1.Text + "', source_itemCount0='" + this.textBox20.Text + "', source_itemIndex1='" + this.r_t_id2.Text + "', source_itemCount1='" + this.textBox14.Text + "', source_itemIndex2='" + this.r_t_id3.Text + "', source_itemCount2='" + this.textBox12.Text + "', source_itemIndex3='" + this.r_t_id4.Text + "', source_itemCount3='" + this.textBox15.Text + "', source_itemIndex4='" + this.r_t_id5.Text + "', source_itemCount4='" + this.textBox18.Text + "' WHERE a_index='" + this.t_exchange_id.Text + "'", connection);
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
      this.gb_npc = new GroupBox();
      this.panel3DView = new Panel();
      this.bt_npc = new Button();
      this.tx_npc_name = new TextBox();
      this.tx_npc_id = new TextBox();
      this.pc_npc = new PictureBox();
      this.label7 = new Label();
      this.label8 = new Label();
      this.groupBox4 = new GroupBox();
      this.tb_reward_qty = new TextBox();
      this.label9 = new Label();
      this.button5 = new Button();
      this.tb_reward_name = new TextBox();
      this.tb_reward_id = new TextBox();
      this.pictureBox2 = new PictureBox();
      this.label10 = new Label();
      this.label11 = new Label();
      this.groupBox2 = new GroupBox();
      this.t_exchange_id = new TextBox();
      this.label21 = new Label();
      this.groupBox7 = new GroupBox();
      this.button6 = new Button();
      this.bt_refresh = new Button();
      this.button12 = new Button();
      this.button8 = new Button();
      this.button9 = new Button();
      this.button11 = new Button();
      this.groupBox3 = new GroupBox();
      this.groupBox5 = new GroupBox();
      this.a_name = new TextBox();
      this.label23 = new Label();
      this.a_desc = new TextBox();
      this.label22 = new Label();
      this.checkBox5 = new CheckBox();
      this.checkBox4 = new CheckBox();
      this.checkBox3 = new CheckBox();
      this.checkBox2 = new CheckBox();
      this.checkBox1 = new CheckBox();
      this.textBox18 = new TextBox();
      this.label18 = new Label();
      this.button7 = new Button();
      this.textBox19 = new TextBox();
      this.r_t_id5 = new TextBox();
      this.pictureBox7 = new PictureBox();
      this.textBox15 = new TextBox();
      this.label15 = new Label();
      this.button10 = new Button();
      this.textBox16 = new TextBox();
      this.r_t_id4 = new TextBox();
      this.pictureBox6 = new PictureBox();
      this.textBox12 = new TextBox();
      this.label12 = new Label();
      this.button13 = new Button();
      this.textBox13 = new TextBox();
      this.r_t_id3 = new TextBox();
      this.pictureBox5 = new PictureBox();
      this.textBox14 = new TextBox();
      this.label13 = new Label();
      this.button14 = new Button();
      this.textBox17 = new TextBox();
      this.r_t_id2 = new TextBox();
      this.pictureBox4 = new PictureBox();
      this.textBox20 = new TextBox();
      this.label14 = new Label();
      this.button15 = new Button();
      this.textBox21 = new TextBox();
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
      this.menuStrip1.SuspendLayout();
      this.gb_npc.SuspendLayout();
      ((ISupportInitialize) this.pc_npc).BeginInit();
      this.groupBox4.SuspendLayout();
      ((ISupportInitialize) this.pictureBox2).BeginInit();
      this.groupBox2.SuspendLayout();
      this.groupBox7.SuspendLayout();
      this.groupBox3.SuspendLayout();
      this.groupBox5.SuspendLayout();
      ((ISupportInitialize) this.pictureBox7).BeginInit();
      ((ISupportInitialize) this.pictureBox6).BeginInit();
      ((ISupportInitialize) this.pictureBox5).BeginInit();
      ((ISupportInitialize) this.pictureBox4).BeginInit();
      ((ISupportInitialize) this.pictureBox3).BeginInit();
      this.SuspendLayout();
      this.menuStrip1.BackColor = Color.Transparent;
      this.menuStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.menüToolStripMenuItem
      });
      this.menuStrip1.Location = new Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new Size(975, 24);
      this.menuStrip1.TabIndex = 0;
      this.menuStrip1.Text = "menuStrip1";
      this.menüToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[2]
      {
        (ToolStripItem) this.loadFromDatabaseToolStripMenuItem,
        (ToolStripItem) this.exitToolStripMenuItem
      });
      this.menüToolStripMenuItem.Name = "menüToolStripMenuItem";
      this.menüToolStripMenuItem.Size = new Size(57, 20);
      this.menüToolStripMenuItem.Text = "MySQL";
      this.loadFromDatabaseToolStripMenuItem.Name = "loadFromDatabaseToolStripMenuItem";
      this.loadFromDatabaseToolStripMenuItem.Size = new Size(182, 22);
      this.loadFromDatabaseToolStripMenuItem.Text = "Load From Database";
      this.loadFromDatabaseToolStripMenuItem.Click += new EventHandler(this.loadFromDatabaseToolStripMenuItem_Click);
      this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
      this.exitToolStripMenuItem.Size = new Size(182, 22);
      this.exitToolStripMenuItem.Text = "Exit";
      this.exitToolStripMenuItem.Click += new EventHandler(this.exitToolStripMenuItem_Click);
      this.textBox1.Location = new Point(219, 484);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(100, 20);
      this.textBox1.TabIndex = 3;
      this.textBox1.Visible = false;
      this.textBox2.Location = new Point(334, 458);
      this.textBox2.Name = "textBox2";
      this.textBox2.Size = new Size(100, 20);
      this.textBox2.TabIndex = 4;
      this.textBox2.Visible = false;
      this.textBox3.Location = new Point(441, 458);
      this.textBox3.Name = "textBox3";
      this.textBox3.Size = new Size(100, 20);
      this.textBox3.TabIndex = 5;
      this.textBox3.Visible = false;
      this.textBox4.Location = new Point(219, 458);
      this.textBox4.Name = "textBox4";
      this.textBox4.Size = new Size(100, 20);
      this.textBox4.TabIndex = 6;
      this.textBox4.Visible = false;
      this.textBox7.Location = new Point(332, 484);
      this.textBox7.Name = "textBox7";
      this.textBox7.Size = new Size(100, 20);
      this.textBox7.TabIndex = 6;
      this.textBox7.Visible = false;
      this.gb_npc.BackColor = Color.Snow;
      this.gb_npc.Controls.Add((Control) this.panel3DView);
      this.gb_npc.Controls.Add((Control) this.bt_npc);
      this.gb_npc.Controls.Add((Control) this.tx_npc_name);
      this.gb_npc.Controls.Add((Control) this.tx_npc_id);
      this.gb_npc.Controls.Add((Control) this.pc_npc);
      this.gb_npc.Controls.Add((Control) this.label7);
      this.gb_npc.Controls.Add((Control) this.label8);
      this.gb_npc.Location = new Point(633, 91);
      this.gb_npc.Name = "gb_npc";
      this.gb_npc.Size = new Size(314, 97);
      this.gb_npc.TabIndex = 7;
      this.gb_npc.TabStop = false;
      this.gb_npc.Text = "NPC Information";
      this.panel3DView.Location = new Point(6, 31);
      this.panel3DView.Name = "panel3DView";
      this.panel3DView.Size = new Size(48, 45);
      this.panel3DView.TabIndex = 15;
      this.bt_npc.Image = (Image) Resources.search__5_;
      this.bt_npc.Location = new Point(259, 25);
      this.bt_npc.Name = "bt_npc";
      this.bt_npc.Size = new Size(30, 27);
      this.bt_npc.TabIndex = 0;
      this.bt_npc.UseVisualStyleBackColor = true;
      this.bt_npc.Click += new EventHandler(this.bt_npc_Click);
      this.tx_npc_name.Enabled = false;
      this.tx_npc_name.Location = new Point(105, 59);
      this.tx_npc_name.Name = "tx_npc_name";
      this.tx_npc_name.Size = new Size(197, 20);
      this.tx_npc_name.TabIndex = 12;
      this.tx_npc_id.Enabled = false;
      this.tx_npc_id.Location = new Point(105, 29);
      this.tx_npc_id.Name = "tx_npc_id";
      this.tx_npc_id.Size = new Size(92, 20);
      this.tx_npc_id.TabIndex = 11;
      this.tx_npc_id.TextChanged += new EventHandler(this.tx_npc_id_TextChanged);
      this.pc_npc.BorderStyle = BorderStyle.FixedSingle;
      this.pc_npc.Location = new Point(11, 34);
      this.pc_npc.Name = "pc_npc";
      this.pc_npc.Size = new Size(42, 40);
      this.pc_npc.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pc_npc.TabIndex = 9;
      this.pc_npc.TabStop = false;
      this.label7.AutoSize = true;
      this.label7.Location = new Point(60, 63);
      this.label7.Name = "label7";
      this.label7.Size = new Size(41, 13);
      this.label7.TabIndex = 14;
      this.label7.Text = "Name :";
      this.label8.AutoSize = true;
      this.label8.Location = new Point(60, 33);
      this.label8.Name = "label8";
      this.label8.Size = new Size(27, 13);
      this.label8.TabIndex = 13;
      this.label8.Text = "ID : ";
      this.groupBox4.BackColor = Color.Linen;
      this.groupBox4.Controls.Add((Control) this.tb_reward_qty);
      this.groupBox4.Controls.Add((Control) this.label9);
      this.groupBox4.Controls.Add((Control) this.button5);
      this.groupBox4.Controls.Add((Control) this.tb_reward_name);
      this.groupBox4.Controls.Add((Control) this.tb_reward_id);
      this.groupBox4.Controls.Add((Control) this.pictureBox2);
      this.groupBox4.Controls.Add((Control) this.label10);
      this.groupBox4.Controls.Add((Control) this.label11);
      this.groupBox4.Location = new Point(218, 91);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Size = new Size(409, 97);
      this.groupBox4.TabIndex = 9;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "Reward Item";
      this.tb_reward_qty.Location = new Point(254, 28);
      this.tb_reward_qty.Name = "tb_reward_qty";
      this.tb_reward_qty.Size = new Size(78, 20);
      this.tb_reward_qty.TabIndex = 19;
      this.label9.AutoSize = true;
      this.label9.Location = new Point(211, 32);
      this.label9.Name = "label9";
      this.label9.Size = new Size(34, 13);
      this.label9.TabIndex = 18;
      this.label9.Text = "Q'ty : ";
      this.button5.Image = (Image) Resources.search__5_;
      this.button5.Location = new Point(360, 24);
      this.button5.Name = "button5";
      this.button5.Size = new Size(30, 27);
      this.button5.TabIndex = 13;
      this.button5.UseVisualStyleBackColor = true;
      this.button5.Click += new EventHandler(this.button5_Click);
      this.tb_reward_name.Enabled = false;
      this.tb_reward_name.Location = new Point(115, 57);
      this.tb_reward_name.Name = "tb_reward_name";
      this.tb_reward_name.Size = new Size(288, 20);
      this.tb_reward_name.TabIndex = 15;
      this.tb_reward_id.Enabled = false;
      this.tb_reward_id.Location = new Point(115, 28);
      this.tb_reward_id.Name = "tb_reward_id";
      this.tb_reward_id.Size = new Size(78, 20);
      this.tb_reward_id.TabIndex = 14;
      this.tb_reward_id.TextChanged += new EventHandler(this.tb_reward_id_TextChanged);
      this.pictureBox2.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox2.Location = new Point(11, 34);
      this.pictureBox2.Name = "pictureBox2";
      this.pictureBox2.Size = new Size(42, 40);
      this.pictureBox2.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pictureBox2.TabIndex = 10;
      this.pictureBox2.TabStop = false;
      this.label10.AutoSize = true;
      this.label10.Location = new Point(60, 61);
      this.label10.Name = "label10";
      this.label10.Size = new Size(41, 13);
      this.label10.TabIndex = 17;
      this.label10.Text = "Name :";
      this.label11.AutoSize = true;
      this.label11.Location = new Point(60, 32);
      this.label11.Name = "label11";
      this.label11.Size = new Size(27, 13);
      this.label11.TabIndex = 16;
      this.label11.Text = "ID : ";
      this.groupBox2.Controls.Add((Control) this.t_exchange_id);
      this.groupBox2.Controls.Add((Control) this.label21);
      this.groupBox2.Location = new Point(12, 33);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new Size(131, 52);
      this.groupBox2.TabIndex = 24;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "Exchange Information";
      this.t_exchange_id.Enabled = false;
      this.t_exchange_id.Location = new Point(56, 23);
      this.t_exchange_id.Name = "t_exchange_id";
      this.t_exchange_id.Size = new Size(69, 20);
      this.t_exchange_id.TabIndex = 19;
      this.t_exchange_id.TextAlign = HorizontalAlignment.Center;
      this.label21.AutoSize = true;
      this.label21.Location = new Point(6, 26);
      this.label21.Name = "label21";
      this.label21.Size = new Size(51, 13);
      this.label21.TabIndex = 20;
      this.label21.Text = "Exc. ID : ";
      this.groupBox7.Controls.Add((Control) this.button6);
      this.groupBox7.Controls.Add((Control) this.bt_refresh);
      this.groupBox7.Controls.Add((Control) this.button12);
      this.groupBox7.Controls.Add((Control) this.button8);
      this.groupBox7.Location = new Point(151, 33);
      this.groupBox7.Name = "groupBox7";
      this.groupBox7.Size = new Size(494, 52);
      this.groupBox7.TabIndex = 25;
      this.groupBox7.TabStop = false;
      this.groupBox7.Text = "Working";
      this.button6.BackColor = Color.Plum;
      this.button6.FlatStyle = FlatStyle.Flat;
      this.button6.Image = (Image) Resources.control_add_blue;
      this.button6.ImageAlign = ContentAlignment.MiddleLeft;
      this.button6.Location = new Point(112, 18);
      this.button6.Name = "button6";
      this.button6.Size = new Size(96, 27);
      this.button6.TabIndex = 15;
      this.button6.Text = "     Add Copy ";
      this.button6.UseVisualStyleBackColor = false;
      this.button6.Click += new EventHandler(this.button6_Click);
      this.bt_refresh.BackColor = Color.MistyRose;
      this.bt_refresh.FlatStyle = FlatStyle.Flat;
      this.bt_refresh.Image = (Image) Resources.refresh;
      this.bt_refresh.ImageAlign = ContentAlignment.MiddleLeft;
      this.bt_refresh.Location = new Point(335, 17);
      this.bt_refresh.Name = "bt_refresh";
      this.bt_refresh.Size = new Size(81, 27);
      this.bt_refresh.TabIndex = 11;
      this.bt_refresh.Text = "    Reset";
      this.bt_refresh.UseVisualStyleBackColor = false;
      this.bt_refresh.Click += new EventHandler(this.bt_refresh_Click);
      this.button12.BackColor = Color.LightCoral;
      this.button12.FlatStyle = FlatStyle.Flat;
      this.button12.Image = (Image) Resources.delete;
      this.button12.ImageAlign = ContentAlignment.MiddleLeft;
      this.button12.Location = new Point(226, 17);
      this.button12.Name = "button12";
      this.button12.Size = new Size(81, 27);
      this.button12.TabIndex = 11;
      this.button12.Text = "    Delete";
      this.button12.UseVisualStyleBackColor = false;
      this.button12.Click += new EventHandler(this.button12_Click);
      this.button8.BackColor = Color.Honeydew;
      this.button8.FlatStyle = FlatStyle.Flat;
      this.button8.Image = (Image) Resources.control_add_blue;
      this.button8.ImageAlign = ContentAlignment.MiddleLeft;
      this.button8.Location = new Point(13, 18);
      this.button8.Name = "button8";
      this.button8.Size = new Size(81, 27);
      this.button8.TabIndex = 11;
      this.button8.Text = "     Add New";
      this.button8.UseVisualStyleBackColor = false;
      this.button8.Click += new EventHandler(this.button8_Click);
      this.button9.BackColor = Color.LightCyan;
      this.button9.FlatStyle = FlatStyle.Flat;
      this.button9.Image = (Image) Resources._08;
      this.button9.ImageAlign = ContentAlignment.MiddleLeft;
      this.button9.Location = new Point(578, 464);
      this.button9.Name = "button9";
      this.button9.Size = new Size(81, 27);
      this.button9.TabIndex = 12;
      this.button9.Text = "   Update";
      this.button9.UseVisualStyleBackColor = false;
      this.button9.Click += new EventHandler(this.button9_Click);
      this.button11.BackColor = Color.White;
      this.button11.FlatStyle = FlatStyle.Flat;
      this.button11.Image = (Image) Resources.FOLDER05;
      this.button11.ImageAlign = ContentAlignment.MiddleLeft;
      this.button11.Location = new Point(683, 464);
      this.button11.Name = "button11";
      this.button11.Size = new Size(89, 27);
      this.button11.TabIndex = 14;
      this.button11.Text = "  Export";
      this.button11.UseVisualStyleBackColor = false;
      this.button11.Click += new EventHandler(this.button11_Click);
      this.groupBox3.BackColor = Color.Honeydew;
      this.groupBox3.Controls.Add((Control) this.groupBox5);
      this.groupBox3.Controls.Add((Control) this.checkBox5);
      this.groupBox3.Controls.Add((Control) this.checkBox4);
      this.groupBox3.Controls.Add((Control) this.checkBox3);
      this.groupBox3.Controls.Add((Control) this.checkBox2);
      this.groupBox3.Controls.Add((Control) this.checkBox1);
      this.groupBox3.Controls.Add((Control) this.textBox18);
      this.groupBox3.Controls.Add((Control) this.label18);
      this.groupBox3.Controls.Add((Control) this.button7);
      this.groupBox3.Controls.Add((Control) this.textBox19);
      this.groupBox3.Controls.Add((Control) this.r_t_id5);
      this.groupBox3.Controls.Add((Control) this.pictureBox7);
      this.groupBox3.Controls.Add((Control) this.textBox15);
      this.groupBox3.Controls.Add((Control) this.label15);
      this.groupBox3.Controls.Add((Control) this.button10);
      this.groupBox3.Controls.Add((Control) this.textBox16);
      this.groupBox3.Controls.Add((Control) this.r_t_id4);
      this.groupBox3.Controls.Add((Control) this.pictureBox6);
      this.groupBox3.Controls.Add((Control) this.textBox12);
      this.groupBox3.Controls.Add((Control) this.label12);
      this.groupBox3.Controls.Add((Control) this.button13);
      this.groupBox3.Controls.Add((Control) this.textBox13);
      this.groupBox3.Controls.Add((Control) this.r_t_id3);
      this.groupBox3.Controls.Add((Control) this.pictureBox5);
      this.groupBox3.Controls.Add((Control) this.textBox14);
      this.groupBox3.Controls.Add((Control) this.label13);
      this.groupBox3.Controls.Add((Control) this.button14);
      this.groupBox3.Controls.Add((Control) this.textBox17);
      this.groupBox3.Controls.Add((Control) this.r_t_id2);
      this.groupBox3.Controls.Add((Control) this.pictureBox4);
      this.groupBox3.Controls.Add((Control) this.textBox20);
      this.groupBox3.Controls.Add((Control) this.label14);
      this.groupBox3.Controls.Add((Control) this.button15);
      this.groupBox3.Controls.Add((Control) this.textBox21);
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
      this.groupBox3.Location = new Point(218, 194);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Size = new Size(733, 258);
      this.groupBox3.TabIndex = 26;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "Exchange Items";
      this.groupBox5.Controls.Add((Control) this.a_name);
      this.groupBox5.Controls.Add((Control) this.label23);
      this.groupBox5.Controls.Add((Control) this.a_desc);
      this.groupBox5.Controls.Add((Control) this.label22);
      this.groupBox5.Location = new Point(357, 168);
      this.groupBox5.Name = "groupBox5";
      this.groupBox5.Size = new Size(371, 81);
      this.groupBox5.TabIndex = 74;
      this.groupBox5.TabStop = false;
      this.groupBox5.Text = "Other Content : ";
      this.a_name.Enabled = false;
      this.a_name.Location = new Point(87, 20);
      this.a_name.Name = "a_name";
      this.a_name.Size = new Size(258, 20);
      this.a_name.TabIndex = 70;
      this.label23.AutoSize = true;
      this.label23.Location = new Point(15, 51);
      this.label23.Name = "label23";
      this.label23.Size = new Size(66, 13);
      this.label23.TabIndex = 73;
      this.label23.Text = "Description :";
      this.a_desc.Enabled = false;
      this.a_desc.Location = new Point(88, 47);
      this.a_desc.Name = "a_desc";
      this.a_desc.Size = new Size(258, 20);
      this.a_desc.TabIndex = 71;
      this.label22.AutoSize = true;
      this.label22.Location = new Point(14, 23);
      this.label22.Name = "label22";
      this.label22.Size = new Size(41, 13);
      this.label22.TabIndex = 72;
      this.label22.Text = "Name :";
      this.checkBox5.AutoSize = true;
      this.checkBox5.Location = new Point(7, 180);
      this.checkBox5.Name = "checkBox5";
      this.checkBox5.Size = new Size(115, 17);
      this.checkBox5.TabIndex = 69;
      this.checkBox5.Text = "Item Require No. 5";
      this.checkBox5.UseVisualStyleBackColor = true;
      this.checkBox4.AutoSize = true;
      this.checkBox4.Location = new Point(381, 96);
      this.checkBox4.Name = "checkBox4";
      this.checkBox4.Size = new Size(115, 17);
      this.checkBox4.TabIndex = 68;
      this.checkBox4.Text = "Item Require No. 4";
      this.checkBox4.UseVisualStyleBackColor = true;
      this.checkBox3.AutoSize = true;
      this.checkBox3.Location = new Point(6, 96);
      this.checkBox3.Name = "checkBox3";
      this.checkBox3.Size = new Size(115, 17);
      this.checkBox3.TabIndex = 67;
      this.checkBox3.Text = "Item Require No. 3";
      this.checkBox3.UseVisualStyleBackColor = true;
      this.checkBox2.AutoSize = true;
      this.checkBox2.Location = new Point(381, 18);
      this.checkBox2.Name = "checkBox2";
      this.checkBox2.Size = new Size(115, 17);
      this.checkBox2.TabIndex = 66;
      this.checkBox2.Text = "Item Require No. 2";
      this.checkBox2.UseVisualStyleBackColor = true;
      this.checkBox1.AutoSize = true;
      this.checkBox1.Location = new Point(7, 18);
      this.checkBox1.Name = "checkBox1";
      this.checkBox1.Size = new Size(115, 17);
      this.checkBox1.TabIndex = 65;
      this.checkBox1.Text = "Item Require No. 1";
      this.checkBox1.UseVisualStyleBackColor = true;
      this.textBox18.Location = new Point(225, 197);
      this.textBox18.Name = "textBox18";
      this.textBox18.Size = new Size(66, 20);
      this.textBox18.TabIndex = 59;
      this.label18.AutoSize = true;
      this.label18.Location = new Point(182, 201);
      this.label18.Name = "label18";
      this.label18.Size = new Size(34, 13);
      this.label18.TabIndex = 58;
      this.label18.Text = "Q'ty : ";
      this.button7.BackgroundImage = (Image) Resources.search__5_;
      this.button7.BackgroundImageLayout = ImageLayout.None;
      this.button7.Location = new Point(295, 194);
      this.button7.Name = "button7";
      this.button7.Size = new Size(27, 25);
      this.button7.TabIndex = 53;
      this.button7.UseVisualStyleBackColor = true;
      this.button7.Click += new EventHandler(this.button7_Click);
      this.textBox19.Enabled = false;
      this.textBox19.Location = new Point(111, 226);
      this.textBox19.Name = "textBox19";
      this.textBox19.Size = new Size(224, 20);
      this.textBox19.TabIndex = 55;
      this.r_t_id5.Enabled = false;
      this.r_t_id5.Location = new Point(111, 197);
      this.r_t_id5.Name = "r_t_id5";
      this.r_t_id5.Size = new Size(66, 20);
      this.r_t_id5.TabIndex = 54;
      this.r_t_id5.TextChanged += new EventHandler(this.r_t_id5_TextChanged);
      this.pictureBox7.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox7.Location = new Point(7, 203);
      this.pictureBox7.Name = "pictureBox7";
      this.pictureBox7.Size = new Size(42, 40);
      this.pictureBox7.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pictureBox7.TabIndex = 52;
      this.pictureBox7.TabStop = false;
      this.textBox15.Location = new Point(599, 113);
      this.textBox15.Name = "textBox15";
      this.textBox15.Size = new Size(66, 20);
      this.textBox15.TabIndex = 51;
      this.label15.AutoSize = true;
      this.label15.Location = new Point(556, 117);
      this.label15.Name = "label15";
      this.label15.Size = new Size(34, 13);
      this.label15.TabIndex = 50;
      this.label15.Text = "Q'ty : ";
      this.button10.BackgroundImage = (Image) Resources.search__5_;
      this.button10.BackgroundImageLayout = ImageLayout.None;
      this.button10.Location = new Point(669, 106);
      this.button10.Name = "button10";
      this.button10.Size = new Size(27, 25);
      this.button10.TabIndex = 45;
      this.button10.UseVisualStyleBackColor = true;
      this.button10.Click += new EventHandler(this.button10_Click);
      this.textBox16.Enabled = false;
      this.textBox16.Location = new Point(485, 142);
      this.textBox16.Name = "textBox16";
      this.textBox16.Size = new Size(224, 20);
      this.textBox16.TabIndex = 47;
      this.r_t_id4.Enabled = false;
      this.r_t_id4.Location = new Point(485, 113);
      this.r_t_id4.Name = "r_t_id4";
      this.r_t_id4.Size = new Size(66, 20);
      this.r_t_id4.TabIndex = 46;
      this.r_t_id4.TextChanged += new EventHandler(this.r_t_id4_TextChanged);
      this.pictureBox6.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox6.Location = new Point(381, 119);
      this.pictureBox6.Name = "pictureBox6";
      this.pictureBox6.Size = new Size(42, 40);
      this.pictureBox6.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pictureBox6.TabIndex = 44;
      this.pictureBox6.TabStop = false;
      this.textBox12.Location = new Point(225, 113);
      this.textBox12.Name = "textBox12";
      this.textBox12.Size = new Size(66, 20);
      this.textBox12.TabIndex = 43;
      this.label12.AutoSize = true;
      this.label12.Location = new Point(182, 117);
      this.label12.Name = "label12";
      this.label12.Size = new Size(34, 13);
      this.label12.TabIndex = 42;
      this.label12.Text = "Q'ty : ";
      this.button13.BackgroundImage = (Image) Resources.search__5_;
      this.button13.BackgroundImageLayout = ImageLayout.None;
      this.button13.Location = new Point(295, 110);
      this.button13.Name = "button13";
      this.button13.Size = new Size(27, 25);
      this.button13.TabIndex = 37;
      this.button13.UseVisualStyleBackColor = true;
      this.button13.Click += new EventHandler(this.button13_Click);
      this.textBox13.Enabled = false;
      this.textBox13.Location = new Point(111, 142);
      this.textBox13.Name = "textBox13";
      this.textBox13.Size = new Size(224, 20);
      this.textBox13.TabIndex = 39;
      this.r_t_id3.Enabled = false;
      this.r_t_id3.Location = new Point(111, 113);
      this.r_t_id3.Name = "r_t_id3";
      this.r_t_id3.Size = new Size(66, 20);
      this.r_t_id3.TabIndex = 38;
      this.r_t_id3.TextChanged += new EventHandler(this.r_t_id3_TextChanged);
      this.pictureBox5.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox5.Location = new Point(7, 119);
      this.pictureBox5.Name = "pictureBox5";
      this.pictureBox5.Size = new Size(42, 40);
      this.pictureBox5.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pictureBox5.TabIndex = 36;
      this.pictureBox5.TabStop = false;
      this.textBox14.Location = new Point(599, 35);
      this.textBox14.Name = "textBox14";
      this.textBox14.Size = new Size(66, 20);
      this.textBox14.TabIndex = 35;
      this.label13.AutoSize = true;
      this.label13.Location = new Point(556, 39);
      this.label13.Name = "label13";
      this.label13.Size = new Size(34, 13);
      this.label13.TabIndex = 34;
      this.label13.Text = "Q'ty : ";
      this.button14.BackgroundImage = (Image) Resources.search__5_;
      this.button14.BackgroundImageLayout = ImageLayout.None;
      this.button14.Location = new Point(669, 33);
      this.button14.Name = "button14";
      this.button14.Size = new Size(27, 25);
      this.button14.TabIndex = 29;
      this.button14.UseVisualStyleBackColor = true;
      this.button14.Click += new EventHandler(this.button14_Click);
      this.textBox17.Enabled = false;
      this.textBox17.Location = new Point(485, 64);
      this.textBox17.Name = "textBox17";
      this.textBox17.Size = new Size(224, 20);
      this.textBox17.TabIndex = 31;
      this.r_t_id2.Enabled = false;
      this.r_t_id2.Location = new Point(485, 35);
      this.r_t_id2.Name = "r_t_id2";
      this.r_t_id2.Size = new Size(66, 20);
      this.r_t_id2.TabIndex = 30;
      this.r_t_id2.TextChanged += new EventHandler(this.r_t_id2_TextChanged);
      this.pictureBox4.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox4.Location = new Point(381, 41);
      this.pictureBox4.Name = "pictureBox4";
      this.pictureBox4.Size = new Size(42, 40);
      this.pictureBox4.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pictureBox4.TabIndex = 28;
      this.pictureBox4.TabStop = false;
      this.textBox20.Location = new Point(225, 35);
      this.textBox20.Name = "textBox20";
      this.textBox20.Size = new Size(66, 20);
      this.textBox20.TabIndex = 27;
      this.label14.AutoSize = true;
      this.label14.Location = new Point(182, 39);
      this.label14.Name = "label14";
      this.label14.Size = new Size(34, 13);
      this.label14.TabIndex = 26;
      this.label14.Text = "Q'ty : ";
      this.button15.BackgroundImage = (Image) Resources.search__5_;
      this.button15.BackgroundImageLayout = ImageLayout.None;
      this.button15.Location = new Point(295, 33);
      this.button15.Name = "button15";
      this.button15.Size = new Size(27, 25);
      this.button15.TabIndex = 21;
      this.button15.UseVisualStyleBackColor = true;
      this.button15.Click += new EventHandler(this.button15_Click);
      this.textBox21.Enabled = false;
      this.textBox21.Location = new Point(111, 64);
      this.textBox21.Name = "textBox21";
      this.textBox21.Size = new Size(224, 20);
      this.textBox21.TabIndex = 23;
      this.r_t_id1.Enabled = false;
      this.r_t_id1.Location = new Point(111, 35);
      this.r_t_id1.Name = "r_t_id1";
      this.r_t_id1.Size = new Size(66, 20);
      this.r_t_id1.TabIndex = 22;
      this.r_t_id1.TextChanged += new EventHandler(this.r_t_id1_TextChanged);
      this.pictureBox3.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox3.Location = new Point(7, 41);
      this.pictureBox3.Name = "pictureBox3";
      this.pictureBox3.Size = new Size(42, 40);
      this.pictureBox3.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pictureBox3.TabIndex = 20;
      this.pictureBox3.TabStop = false;
      this.label19.AutoSize = true;
      this.label19.Location = new Point(56, 230);
      this.label19.Name = "label19";
      this.label19.Size = new Size(41, 13);
      this.label19.TabIndex = 57;
      this.label19.Text = "Name :";
      this.label20.AutoSize = true;
      this.label20.Location = new Point(56, 201);
      this.label20.Name = "label20";
      this.label20.Size = new Size(27, 13);
      this.label20.TabIndex = 56;
      this.label20.Text = "ID : ";
      this.label16.AutoSize = true;
      this.label16.Location = new Point(430, 146);
      this.label16.Name = "label16";
      this.label16.Size = new Size(41, 13);
      this.label16.TabIndex = 49;
      this.label16.Text = "Name :";
      this.label17.AutoSize = true;
      this.label17.Location = new Point(430, 117);
      this.label17.Name = "label17";
      this.label17.Size = new Size(27, 13);
      this.label17.TabIndex = 48;
      this.label17.Text = "ID : ";
      this.label24.AutoSize = true;
      this.label24.Location = new Point(56, 146);
      this.label24.Name = "label24";
      this.label24.Size = new Size(41, 13);
      this.label24.TabIndex = 41;
      this.label24.Text = "Name :";
      this.label25.AutoSize = true;
      this.label25.Location = new Point(56, 117);
      this.label25.Name = "label25";
      this.label25.Size = new Size(27, 13);
      this.label25.TabIndex = 40;
      this.label25.Text = "ID : ";
      this.label26.AutoSize = true;
      this.label26.Location = new Point(430, 68);
      this.label26.Name = "label26";
      this.label26.Size = new Size(41, 13);
      this.label26.TabIndex = 33;
      this.label26.Text = "Name :";
      this.label27.AutoSize = true;
      this.label27.Location = new Point(430, 39);
      this.label27.Name = "label27";
      this.label27.Size = new Size(27, 13);
      this.label27.TabIndex = 32;
      this.label27.Text = "ID : ";
      this.label28.AutoSize = true;
      this.label28.Location = new Point(56, 68);
      this.label28.Name = "label28";
      this.label28.Size = new Size(41, 13);
      this.label28.TabIndex = 25;
      this.label28.Text = "Name :";
      this.label29.AutoSize = true;
      this.label29.Location = new Point(56, 39);
      this.label29.Name = "label29";
      this.label29.Size = new Size(27, 13);
      this.label29.TabIndex = 24;
      this.label29.Text = "ID : ";
      this.listBox1.FormattingEnabled = true;
      this.listBox1.Location = new Point(12, 97);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new Size(200, 394);
      this.listBox1.TabIndex = 27;
      this.listBox1.SelectedIndexChanged += new EventHandler(this.ListBox1_SelectedIndexChanged);
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.BackColor = Color.White;
      this.ClientSize = new Size(975, 508);
      this.Controls.Add((Control) this.listBox1);
      this.Controls.Add((Control) this.groupBox3);
      this.Controls.Add((Control) this.button9);
      this.Controls.Add((Control) this.groupBox7);
      this.Controls.Add((Control) this.groupBox2);
      this.Controls.Add((Control) this.button11);
      this.Controls.Add((Control) this.groupBox4);
      this.Controls.Add((Control) this.gb_npc);
      this.Controls.Add((Control) this.textBox7);
      this.Controls.Add((Control) this.textBox4);
      this.Controls.Add((Control) this.textBox3);
      this.Controls.Add((Control) this.textBox2);
      this.Controls.Add((Control) this.textBox1);
      this.Controls.Add((Control) this.menuStrip1);
      this.FormBorderStyle = FormBorderStyle.Fixed3D;
      this.MainMenuStrip = this.menuStrip1;
      this.MaximizeBox = false;
      this.Name = nameof (ExchangeEditor);
      this.Text = "LastChaos Exchange Editor";
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.gb_npc.ResumeLayout(false);
      this.gb_npc.PerformLayout();
      ((ISupportInitialize) this.pc_npc).EndInit();
      this.groupBox4.ResumeLayout(false);
      this.groupBox4.PerformLayout();
      ((ISupportInitialize) this.pictureBox2).EndInit();
      this.groupBox2.ResumeLayout(false);
      this.groupBox2.PerformLayout();
      this.groupBox7.ResumeLayout(false);
      this.groupBox3.ResumeLayout(false);
      this.groupBox3.PerformLayout();
      this.groupBox5.ResumeLayout(false);
      this.groupBox5.PerformLayout();
      ((ISupportInitialize) this.pictureBox7).EndInit();
      ((ISupportInitialize) this.pictureBox6).EndInit();
      ((ISupportInitialize) this.pictureBox5).EndInit();
      ((ISupportInitialize) this.pictureBox4).EndInit();
      ((ISupportInitialize) this.pictureBox3).EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();
    }

    private void button11_Click(object sender, EventArgs e)
    {
      this.exportLodHandle.ExportExChange_V4();
    }

    private void button5_Click(object sender, EventArgs e)
    {
      this.tb_reward_id.Text = "0";
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.tb_reward_id.Text = itemPicker.ItemIndex.ToString();
    }

    private void bt_npc_Click(object sender, EventArgs e)
    {
      this.tx_npc_id.Text = "0";
      MobPicker mobPicker = new MobPicker();
      if (mobPicker.ShowDialog() != DialogResult.OK)
        return;
      this.tx_npc_id.Text = mobPicker.MobIndex.ToString();
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
      this.t_exchange_id.Text = "";
      this.tx_npc_id.Text = "0";
      this.tb_reward_id.Text = "0";
      this.tb_reward_qty.Text = "0";
      this.r_t_id1.Text = "0";
      this.textBox20.Text = "0";
      this.r_t_id2.Text = "0";
      this.textBox14.Text = "0";
      this.r_t_id3.Text = "0";
      this.textBox12.Text = "0";
      this.r_t_id4.Text = "0";
      this.textBox15.Text = "0";
      this.r_t_id5.Text = "0";
      this.textBox18.Text = "0";
    }

    private void button12_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want to delete " + this.tb_reward_name.Text.Trim() + " ?", "Please confirm delete.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      if (this.t_exchange_id.Text.Trim().Length <= 0)
      {
        int num = (int) MessageBox.Show("No data to delete in select item to delete first", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "delete from t_item_exchange where a_index = " + this.t_exchange_id.Text.Trim());
        this.SelectDB2();
        this.listBox1.SelectedIndex = this.listBox1.Items.Count - 1;
      }
    }

    private void button6_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want copy to New From Index " + this.t_exchange_id.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      if (this.t_exchange_id.Text.Trim().Length <= 0)
      {
        int num1 = (int) MessageBox.Show("No data to select", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DROP TABLE IF EXISTS tempTable;CREATE TEMPORARY TABLE tempTable ENGINE=MEMORY SELECT * FROM t_item_exchange WHERE a_index=" + this.t_exchange_id.Text + ";SELECT a_index FROM tempTable;UPDATE tempTable SET a_index=(SELECT a_index from t_item_exchange ORDER BY a_index DESC LIMIT 1)+1; SELECT a_index FROM tempTable;INSERT INTO t_item_exchange SELECT * FROM tempTable;");
        int num2 = (int) MessageBox.Show("Successful copy", "Completed", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
        this.SelectDB2();
        this.listBox1.SelectedIndex = this.listBox1.Items.Count - 1;
      }
    }

    private void button8_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want add New " + this.t_exchange_id.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      if (this.t_exchange_id.Text.Trim().Length <= 0)
      {
        int num1 = (int) MessageBox.Show("No data to select", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_item_exchange DEFAULT VALUES");
        int num2 = (int) MessageBox.Show("Successful add new", "Completed", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
        this.SelectDB2();
        this.listBox1.SelectedIndex = this.listBox1.Items.Count - 1;
      }
    }

    private void settingToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (new LcDevPack_TeamDamonA.Tools.Settings().ShowDialog() == DialogResult.OK)
        ;
    }
  }
}
