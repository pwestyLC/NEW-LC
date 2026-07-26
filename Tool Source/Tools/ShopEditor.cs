// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.ShopEditor
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using LcDevPack_TeamDamonA.Properties;
using MySqlConnector;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools
{
  public class ShopEditor : Form
  {
    public static Connection connection = new Connection();
    private string Host = ShopEditor.connection.Settings.SqlHost;
    private string User = ShopEditor.connection.Settings.SqlUser;
    private string Password = ShopEditor.connection.Settings.SqlPassword;
    private string Database = ShopEditor.connection.Settings.SqlDatabase;
    private string language = ShopEditor.connection.Settings.Language;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    public string rowName = "a_keeper_idx";
    public List<string> MenuList = new List<string>();
    public List<string> MenuListSearch = new List<string>();
    private ASCIIEncoding _Enc = new ASCIIEncoding();
    private string namee;
    public string[] menuArray = new string[2]
    {
      "a_keeper_idx",
      "a_name"
    };
    public string[] menuArrayGER = new string[2]
    {
      "a_keeper_idx",
      "a_name_ger"
    };
    public string[] menuArrayPOL = new string[2]
    {
      "a_keeper_idx",
      "a_name_pld"
    };
    public string[] menuArrayBRA = new string[2]
    {
      "a_keeper_idx",
      "a_name_brz"
    };
    public string[] menuArrayRUS = new string[2]
    {
      "a_keeper_idx",
      "a_name_rus"
    };
    public string[] menuArrayFRA = new string[2]
    {
      "a_keeper_idx",
      "a_name_frc"
    };
    public string[] menuArrayMEX = new string[2]
    {
      "a_keeper_idx",
      "a_name_mex"
    };
    public string[] menuArrayTHA = new string[2]
    {
      "a_keeper_idx",
      "a_name_thai"
    };
    public string[] menuArrayITA = new string[2]
    {
      "a_keeper_idx",
      "a_name_ita"
    };
    private ToolStripMenuItem saveToolStripMenuItem;
    public string[] menuArrayUSA = new string[2]
    {
      "a_keeper_idx",
      "a_name_usa"
    };
    private ExportLodHandle exportLodHandle = new ExportLodHandle();
    private IContainer components = (IContainer) null;
    public string name;
    public int index;
    public string test2;
    private MenuStrip menuStrip1;
    private ToolStripMenuItem exportToolStripMenuItem;
    private ToolStripMenuItem exportlodToolStripMenuItem;
    private GroupBox groupBox3;
    private Button button3;
    private Button button1;
    private ListBox listBox1;
    private TextBox textBox1;
    private TextBox textBox2;
    private TextBox textBox3;
    private TextBox textBox4;
    private TextBox textBox5;
    private TextBox textBox6;
    private TextBox textBox9;
    private GroupBox groupBox1;
    private Label label5;
    private Label label4;
    private Label label3;
    private Label label2;
    private Label label1;
    private GroupBox groupBox2;
    private Label label10;
    private Label label8;
    private GroupBox groupBox4;
    private DataGridView dgItems;
    private ToolStrip toolStrip2;
    private ToolStripButton btnAddItems;
    private ToolStripSeparator toolStripSeparator6;
    private ToolStripButton toolStripButton1;
    private Button button2;
    private ToolStripButton btnDeleteSelected;
    private ToolStripSeparator toolStripSeparator1;
    private StatusStrip statusStrip1;
    private ToolStripStatusLabel toolStripStatusLabel1;
    private TextBox textBox11;
    private DataGridViewTextBoxColumn Column5;
    private DataGridViewTextBoxColumn Column4;
    private DataGridViewTextBoxColumn Column3;
    private DataGridViewTextBoxColumn Column2;
    private DataGridViewTextBoxColumn Column1;
    private Label label9;
    private Label label7;
    private Label label6;
    private TextBox textBox10;
    private TextBox textBox7;
    private TextBox textBox8;
    private Label label11;
    private TextBox textBox12;
    private TextBox textBox13;
    private Label label12;
    private Button button15;
    private DataGridViewImageColumn Column7;

    public string StringFromLanguage()
    {
      if (this.language == "GER")
      {
        this.namee = "a_name_ger";
        return this.namee;
      }
      if (this.language == "POL")
      {
        this.namee = "a_name_pld";
        return this.namee;
      }
      if (this.language == "BRA")
      {
        this.namee = "a_name_brz";
        return this.namee;
      }
      if (this.language == "RUS")
      {
        this.namee = "a_name_rus";
        return this.namee;
      }
      if (this.language == "FRA")
      {
        this.namee = "a_name_frc";
        return this.namee;
      }
      if (this.language == "MEX")
      {
        this.namee = "a_name_mex";
        return this.namee;
      }
      if (this.language == "THA")
      {
        this.namee = "a_name_thai";
        return this.namee;
      }
      if (this.language == "ITA")
      {
        this.namee = "a_name_ita";
        return this.namee;
      }
      if (!(this.language == "USA"))
        return (string) null;
      this.namee = "a_name_usa";
      return this.namee;
    }

    public ShopEditor() => this.InitializeComponent();

    private void LoadListBox()
    {
      this.listBox1.SelectedIndex = -1;
      this.MenuList.Clear();
      this.namee = this.StringFromLanguage();
      string Query = "SELECT a_keeper_idx, " + this.namee + " FROM t_shop ORDER BY a_keeper_idx;";
      if (this.language == "GER")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayGER, this.Host, this.User, this.Password, this.Database, "select a_keeper_idx, a_name_ger from t_shop ORDER BY a_keeper_idx;");
      else if (this.language == "BRA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayBRA, this.Host, this.User, this.Password, this.Database, "select a_keeper_idx, a_name_brz from t_shop ORDER BY a_keeper_idx;");
      else if (this.language == "RUS")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayRUS, this.Host, this.User, this.Password, this.Database, "select a_keeper_idx, a_name_rus from t_shop ORDER BY a_keeper_idx;");
      else if (this.language == "MEX")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayMEX, this.Host, this.User, this.Password, this.Database, "select a_keeper_idx, a_name_mex from t_shop ORDER BY a_keeper_idx;");
      else if (this.language == "THA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayTHA, this.Host, this.User, this.Password, this.Database, Query);
      else if (this.language == "ITA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayITA, this.Host, this.User, this.Password, this.Database, "select a_keeper_idx, a_name_ita from t_shop ORDER BY a_keeper_idx;");
      else if (this.language == "USA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayUSA, this.Host, this.User, this.Password, this.Database, "select a_keeper_idx, a_name_usa from t_shop ORDER BY a_keeper_idx;");
      else
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, "select a_keeper_idx, a_name from t_shop ORDER BY a_keeper_idx;");
    }

    private void Exporter_Shop_Load(object sender, EventArgs e) => this.LoadListBox();

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
      int.TryParse(this.textBox1.Text.Split(' ')[0], out result);
      return result;
    }

    private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (this.listBox1.SelectedIndex != -1)
        this.textBox1.Text = this.GetIndex().ToString();
      string Query = "  select * from t_shop WHERE a_keeper_idx ='" + this.textBox1.Text + "';";
      string[] rows = new string[17]
      {
        "a_keeper_idx",
        "a_zone_num",
        "a_name",
        "a_sell_rate",
        "a_buy_rate",
        "a_pos_x",
        "a_pos_z",
        "a_pos_h",
        "a_pos_r",
        "a_y_layer",
        "a_name_ita",
        "a_name_usa",
        "a_name_rus",
        "a_name_thai",
        "a_name_brz",
        "a_name_ger",
        "a_name_mex"
      };
      Query.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'");
      string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query, rows);
      this.textBox1.Text = strArray[0];
      this.textBox11.Text = strArray[0];
      if (this.language == "USA")
        this.textBox3.Text = strArray[11];
      else if (this.language == "ITA")
        this.textBox3.Text = strArray[10];
      else if (this.language == "RUS")
        this.textBox3.Text = strArray[12];
      else if (this.language == "THA")
      {
        this.textBox3.Text = strArray[13];
        this.textBox12.Text = strArray[0];
      }
      else if (this.language == "ESP")
        this.textBox3.Text = strArray[14];
      else if (this.language == "BRA")
        this.textBox3.Text = strArray[15];
      else if (this.language == "GER")
        this.textBox3.Text = strArray[16];
      else if (this.language == "MEX")
        this.textBox3.Text = strArray[17];
      else if (this.language != "GER" && this.language != "POL" && this.language != "BRA" && this.language != "RUS" && this.language != "FRA" && this.language != "ESP" && this.language != "MEX" && this.language != "THA" && this.language != "ITA" && this.language != "USA")
        this.textBox3.Text = strArray[2];
      this.textBox2.Text = strArray[1];
      this.textBox4.Text = strArray[3];
      this.textBox5.Text = strArray[4];
      this.textBox6.Text = strArray[5];
      this.textBox7.Text = strArray[6];
      this.textBox8.Text = strArray[7];
      this.textBox9.Text = strArray[8];
      this.textBox10.Text = strArray[9];
      this.dgItems.Rows.Clear();
      this.LoadDG();
    }

    public void LoadDG()
    {
      this.toolStripStatusLabel1.Text = "Load Items ...";
      string str1 = "SELECT * FROM t_shopitem WHERE a_keeper_idx ='" + this.textBox1.Text + "'";
      MySqlConnection mySqlConnection = new MySqlConnection("datasource=" + this.Host + ";Port=3306;User ID="  + this.User + ";Password=" + this.Password + ";Database=" + this.Database + ";Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;");
      MySqlCommand command = mySqlConnection.CreateCommand();
      command.CommandText = str1;
      mySqlConnection.Open();
      MySqlDataReader mySqlDataReader = command.ExecuteReader();
      while (mySqlDataReader.Read())
      {
        string str2 = mySqlDataReader.GetValue(0).ToString();
        string str3 = mySqlDataReader.GetValue(1).ToString();
        string str4 = mySqlDataReader.GetValue(2).ToString();
        string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, "SELECT a_name, a_texture_id, a_texture_row, a_texture_col from t_item WHERE a_index ='" + str3 + "';", new string[4]
        {
          "a_name",
          "a_texture_id",
          "a_texture_row",
          "a_texture_col"
        });
        string str5 = this.databaseHandle.ItemNameFast(Convert.ToInt32(str3));
        string str6 = strArray[0];
        this.dgItems.Rows.Add((object) this.databaseHandle.IconItem(Convert.ToInt32(strArray[1]), Convert.ToInt32(strArray[2]), Convert.ToInt32(strArray[3])), (object) str3, (object) str5, (object) str4, (object) str2, (object) str3);
      }
      mySqlConnection.Close();
      this.toolStripStatusLabel1.Text = "Ready";
    }

    private void dgItems_CellContentClick(object sender, DataGridViewCellEventArgs e)
    {
    }

    private void button2_Click(object sender, EventArgs e)
    {
      if (this.language == "THA")
      {
        this.namee = this.StringFromLanguage();
        this.textBox3.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_shop SET a_keeper_idx = '" + this.textBox1.Text + "', a_zone_num = '" + this.textBox2.Text + "'," + this.namee + "= '" + this.textBox3.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_sell_rate = '" + this.textBox4.Text + "', a_buy_rate = '" + this.textBox5.Text + "', a_pos_x = '" + this.textBox6.Text + "', a_pos_z = '" + this.textBox7.Text + "', a_pos_h = '" + this.textBox8.Text + "', a_pos_r = '" + this.textBox9.Text + "', a_y_layer = '" + this.textBox10.Text + "' WHERE a_keeper_idx = '" + this.textBox11.Text + "'");
      }
      else if (this.language == "USA")
      {
        this.namee = this.StringFromLanguage();
        this.textBox3.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_shop SET a_keeper_idx = '" + this.textBox1.Text + "', a_zone_num = '" + this.textBox2.Text + "', a_name = '" + this.textBox3.Text + "'," + this.namee + "= '" + this.textBox3.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_sell_rate = '" + this.textBox4.Text + "', a_buy_rate = '" + this.textBox5.Text + "', a_pos_x = '" + this.textBox6.Text + "', a_pos_z = '" + this.textBox7.Text + "', a_pos_h = '" + this.textBox8.Text + "', a_pos_r = '" + this.textBox9.Text + "', a_y_layer = '" + this.textBox10.Text + "' WHERE a_keeper_idx = '" + this.textBox11.Text + "'");
      }
      else
      {
        this.namee = this.StringFromLanguage();
        string str = this.textBox3.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        this.textBox3.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_shop SET a_keeper_idx = '" + this.textBox1.Text + "', a_zone_num = '" + this.textBox2.Text + "'," + this.namee + "= '" + str + "', a_sell_rate = '" + this.textBox4.Text + "', a_buy_rate = '" + this.textBox5.Text + "', a_pos_x = '" + this.textBox6.Text + "', a_pos_z = '" + this.textBox7.Text + "', a_pos_h = '" + this.textBox8.Text + "', a_pos_r = '" + this.textBox9.Text + "', a_y_layer = '" + this.textBox10.Text + "' WHERE a_keeper_idx = '" + this.textBox11.Text + "'");
      }
      int selectedIndex = this.listBox1.SelectedIndex;
      this.LoadListBox();
      this.listBox1.SelectedIndex = selectedIndex;
    }

    private void button1_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want copy to New Shop Index " + this.textBox12.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      if (this.textBox12.Text.Trim().Length <= 0)
      {
        int num1 = (int) MessageBox.Show("please add shop NPC", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DROP TABLE IF EXISTS tempTable;CREATE TEMPORARY TABLE tempTable ENGINE=MEMORY SELECT * FROM t_shop WHERE a_keeper_idx=" + this.textBox1.Text + ";SELECT a_keeper_idx FROM tempTable;UPDATE tempTable SET a_keeper_idx=" + this.textBox12.Text + ";INSERT INTO t_shop SELECT * FROM tempTable;");
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_shopitem (a_keeper_idx, a_item_idx) VALUES (" + this.textBox12.Text + ", 85 )");
        int num2 = (int) MessageBox.Show("Successful copy", "Completed", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
        this.LoadListBox();
        this.listBox1.SelectedIndex = this.listBox1.Items.Count - 1;
      }
    }

    private void button3_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want to Delete Shop " + this.textBox1.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      int selectedIndex = this.listBox1.SelectedIndex;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_shop WHERE a_keeper_idx = '" + this.textBox1.Text + "'");
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_shopitem WHERE a_keeper_idx = '" + this.textBox1.Text + "'");
      this.LoadListBox();
      this.listBox1.SelectedIndex = selectedIndex - 1;
    }

    private void exportlodToolStripMenuItem_Click(object sender, EventArgs e)
    {
      new LodExporter.LodExporter().Show();
    }

    private void btnAddItems_Click(object sender, EventArgs e)
    {
      int index = this.dgItems.CurrentRow.Index;
      DataGridViewRow row = this.dgItems.Rows[this.dgItems.CurrentRow.Index];
      try
      {
        ItemPicker itemPicker = new ItemPicker();
        if (itemPicker.ShowDialog() != DialogResult.OK)
          return;
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_shopitem (a_keeper_idx, a_item_idx) VALUES (" + this.textBox1.Text + "," + itemPicker.ItemIndex.ToString() + ")");
      }
      catch
      {
        int num = (int) MessageBox.Show("Duplicated ItemID isn't allowed.", "Error");
      }
      this.dgItems.Rows.Clear();
      this.LoadDG();
      this.dgItems.Rows[index].Selected = true;
      this.dgItems.FirstDisplayedScrollingRowIndex = index;
    }

    private void toolStripButton1_Click(object sender, EventArgs e)
    {
      int index = this.dgItems.CurrentRow.Index - 1;
      DataGridViewRow row = this.dgItems.Rows[this.dgItems.CurrentRow.Index];
      if (this.dgItems.CurrentRow.Index < 0)
      {
        int num = (int) MessageBox.Show("You need select Item", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        if (MessageBox.Show("Do you want to Delete Item  ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
          return;
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_shopitem WHERE a_keeper_idx ='" + Convert.ToString(row.Cells["Column4"].Value) + "' AND a_item_idx = '" + Convert.ToString(row.Cells["Column1"].Value) + "'");
        this.dgItems.Rows.Clear();
        this.LoadDG();
        if (index == -1)
          return;
        this.dgItems.Rows[index].Selected = true;
        this.dgItems.FirstDisplayedScrollingRowIndex = index;
      }
    }

    private void btnDeleteSelected_Click(object sender, EventArgs e)
    {
      DataGridViewRow row = this.dgItems.Rows[this.dgItems.CurrentRow.Index];
      string str1 = Convert.ToString(row.Cells["Column4"].Value);
      string str2 = Convert.ToString(row.Cells["Column1"].Value);
      string str3 = Convert.ToString(row.Cells["Column3"].Value);
      string str4 = Convert.ToString(row.Cells["Column5"].Value);
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_shopitem SET a_item_idx = '" + str2 + "', a_national = '" + str3 + "' WHERE a_keeper_idx = '" + str1 + "' AND a_item_idx = '" + str4 + "'");
      this.dgItems.Rows.Clear();
      this.LoadDG();
    }

    private void dgItems_CellEndEdit(object sender, DataGridViewCellEventArgs e)
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
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (ShopEditor));
      this.menuStrip1 = new MenuStrip();
      this.exportToolStripMenuItem = new ToolStripMenuItem();
      this.exportlodToolStripMenuItem = new ToolStripMenuItem();
      this.groupBox3 = new GroupBox();
      this.listBox1 = new ListBox();
      this.button3 = new Button();
      this.button1 = new Button();
      this.textBox1 = new TextBox();
      this.textBox2 = new TextBox();
      this.textBox3 = new TextBox();
      this.textBox4 = new TextBox();
      this.textBox5 = new TextBox();
      this.textBox6 = new TextBox();
      this.textBox9 = new TextBox();
      this.groupBox1 = new GroupBox();
      this.textBox11 = new TextBox();
      this.label5 = new Label();
      this.label4 = new Label();
      this.label3 = new Label();
      this.label2 = new Label();
      this.label1 = new Label();
      this.groupBox2 = new GroupBox();
      this.label10 = new Label();
      this.label9 = new Label();
      this.label8 = new Label();
      this.label7 = new Label();
      this.label6 = new Label();
      this.textBox10 = new TextBox();
      this.textBox7 = new TextBox();
      this.textBox8 = new TextBox();
      this.groupBox4 = new GroupBox();
      this.dgItems = new DataGridView();
      this.Column7 = new DataGridViewImageColumn();
      this.Column1 = new DataGridViewTextBoxColumn();
      this.Column2 = new DataGridViewTextBoxColumn();
      this.Column3 = new DataGridViewTextBoxColumn();
      this.Column4 = new DataGridViewTextBoxColumn();
      this.Column5 = new DataGridViewTextBoxColumn();
      this.toolStrip2 = new ToolStrip();
      this.btnDeleteSelected = new ToolStripButton();
      this.toolStripSeparator1 = new ToolStripSeparator();
      this.btnAddItems = new ToolStripButton();
      this.toolStripSeparator6 = new ToolStripSeparator();
      this.toolStripButton1 = new ToolStripButton();
      this.button2 = new Button();
      this.statusStrip1 = new StatusStrip();
      this.toolStripStatusLabel1 = new ToolStripStatusLabel();
      this.label11 = new Label();
      this.textBox12 = new TextBox();
      this.textBox13 = new TextBox();
      this.label12 = new Label();
      this.button15 = new Button();
      this.saveToolStripMenuItem = new ToolStripMenuItem();
      this.menuStrip1.SuspendLayout();
      this.groupBox3.SuspendLayout();
      this.groupBox1.SuspendLayout();
      this.groupBox2.SuspendLayout();
      this.groupBox4.SuspendLayout();
      ((ISupportInitialize) this.dgItems).BeginInit();
      this.toolStrip2.SuspendLayout();
      this.statusStrip1.SuspendLayout();
      this.SuspendLayout();
      this.menuStrip1.AllowMerge = false;
      this.menuStrip1.BackColor = SystemColors.ButtonHighlight;
      this.menuStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.exportToolStripMenuItem
      });
      this.menuStrip1.Location = new Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new Size(816, 24);
      this.menuStrip1.TabIndex = 0;
      this.menuStrip1.Text = "menuStrip1";
      this.exportToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[2]
      {
        (ToolStripItem) this.exportlodToolStripMenuItem,
        (ToolStripItem) this.saveToolStripMenuItem
      });
      this.exportToolStripMenuItem.Name = "exportToolStripMenuItem";
      this.exportToolStripMenuItem.Size = new Size(74, 20);
      this.exportToolStripMenuItem.Text = "File Export";
      this.exportlodToolStripMenuItem.Name = "exportlodToolStripMenuItem";
      this.exportlodToolStripMenuItem.Size = new Size(152, 22);
      this.exportlodToolStripMenuItem.Text = "Export .lod";
      this.exportlodToolStripMenuItem.Click += new EventHandler(this.exportlodToolStripMenuItem_Click);
      this.groupBox3.Controls.Add((Control) this.listBox1);
      this.groupBox3.Location = new Point(12, 27);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Size = new Size(237, 446);
      this.groupBox3.TabIndex = 30;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "Shop NPC";
      this.listBox1.FormattingEnabled = true;
      this.listBox1.Location = new Point(6, 14);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new Size(225, 420);
      this.listBox1.TabIndex = 1;
      this.listBox1.SelectedIndexChanged += new EventHandler(this.listBox1_SelectedIndexChanged);
      this.button3.FlatStyle = FlatStyle.Flat;
      this.button3.Location = new Point(12, 479);
      this.button3.Name = "button3";
      this.button3.Size = new Size(100, 23);
      this.button3.TabIndex = 4;
      this.button3.Text = "Delete";
      this.button3.UseVisualStyleBackColor = true;
      this.button3.Click += new EventHandler(this.button3_Click);
      this.button1.FlatStyle = FlatStyle.Flat;
      this.button1.Location = new Point(143, 479);
      this.button1.Name = "button1";
      this.button1.Size = new Size(100, 23);
      this.button1.TabIndex = 2;
      this.button1.Text = "Add";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.textBox1.BorderStyle = BorderStyle.FixedSingle;
      this.textBox1.Location = new Point(79, 23);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(50, 20);
      this.textBox1.TabIndex = 31;
      this.textBox2.BorderStyle = BorderStyle.FixedSingle;
      this.textBox2.Location = new Point(204, 23);
      this.textBox2.Name = "textBox2";
      this.textBox2.Size = new Size(50, 20);
      this.textBox2.TabIndex = 32;
      this.textBox3.BorderStyle = BorderStyle.FixedSingle;
      this.textBox3.Location = new Point(79, 52);
      this.textBox3.Name = "textBox3";
      this.textBox3.Size = new Size(175, 20);
      this.textBox3.TabIndex = 33;
      this.textBox4.BorderStyle = BorderStyle.FixedSingle;
      this.textBox4.Location = new Point(79, 78);
      this.textBox4.Name = "textBox4";
      this.textBox4.Size = new Size(50, 20);
      this.textBox4.TabIndex = 34;
      this.textBox5.BorderStyle = BorderStyle.FixedSingle;
      this.textBox5.Location = new Point(204, 78);
      this.textBox5.Name = "textBox5";
      this.textBox5.Size = new Size(50, 20);
      this.textBox5.TabIndex = 35;
      this.textBox6.BorderStyle = BorderStyle.FixedSingle;
      this.textBox6.Location = new Point(59, 23);
      this.textBox6.Name = "textBox6";
      this.textBox6.Size = new Size(50, 20);
      this.textBox6.TabIndex = 40;
      this.textBox9.BorderStyle = BorderStyle.FixedSingle;
      this.textBox9.Location = new Point(59, 52);
      this.textBox9.Name = "textBox9";
      this.textBox9.Size = new Size(50, 20);
      this.textBox9.TabIndex = 37;
      this.groupBox1.Controls.Add((Control) this.textBox11);
      this.groupBox1.Controls.Add((Control) this.label5);
      this.groupBox1.Controls.Add((Control) this.label4);
      this.groupBox1.Controls.Add((Control) this.label3);
      this.groupBox1.Controls.Add((Control) this.label2);
      this.groupBox1.Controls.Add((Control) this.textBox2);
      this.groupBox1.Controls.Add((Control) this.label1);
      this.groupBox1.Controls.Add((Control) this.textBox1);
      this.groupBox1.Controls.Add((Control) this.textBox3);
      this.groupBox1.Controls.Add((Control) this.textBox4);
      this.groupBox1.Controls.Add((Control) this.textBox5);
      this.groupBox1.Location = new Point((int) byte.MaxValue, 27);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(266, 137);
      this.groupBox1.TabIndex = 41;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Main";
      this.textBox11.BorderStyle = BorderStyle.FixedSingle;
      this.textBox11.Location = new Point(79, 0);
      this.textBox11.Name = "textBox11";
      this.textBox11.Size = new Size(50, 20);
      this.textBox11.TabIndex = 39;
      this.textBox11.Visible = false;
      this.label5.AutoSize = true;
      this.label5.Location = new Point(144, 82);
      this.label5.Name = "label5";
      this.label5.Size = new Size(54, 13);
      this.label5.TabIndex = 38;
      this.label5.Text = "Buy Rate:";
      this.label4.AutoSize = true;
      this.label4.Location = new Point(6, 80);
      this.label4.Name = "label4";
      this.label4.Size = new Size(53, 13);
      this.label4.TabIndex = 37;
      this.label4.Text = "Sell Rate:";
      this.label3.AutoSize = true;
      this.label3.Location = new Point(6, 54);
      this.label3.Name = "label3";
      this.label3.Size = new Size(38, 13);
      this.label3.TabIndex = 36;
      this.label3.Text = "Name:";
      this.label2.AutoSize = true;
      this.label2.Location = new Point(144, 25);
      this.label2.Name = "label2";
      this.label2.Size = new Size(35, 13);
      this.label2.TabIndex = 1;
      this.label2.Text = "Zone:";
      this.label1.AutoSize = true;
      this.label1.Location = new Point(6, 25);
      this.label1.Name = "label1";
      this.label1.Size = new Size(36, 13);
      this.label1.TabIndex = 0;
      this.label1.Text = "Index:";
      this.groupBox2.Controls.Add((Control) this.label10);
      this.groupBox2.Controls.Add((Control) this.label9);
      this.groupBox2.Controls.Add((Control) this.label8);
      this.groupBox2.Controls.Add((Control) this.label7);
      this.groupBox2.Controls.Add((Control) this.label6);
      this.groupBox2.Controls.Add((Control) this.textBox6);
      this.groupBox2.Controls.Add((Control) this.textBox10);
      this.groupBox2.Controls.Add((Control) this.textBox9);
      this.groupBox2.Controls.Add((Control) this.textBox7);
      this.groupBox2.Controls.Add((Control) this.textBox8);
      this.groupBox2.Location = new Point(527, 27);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new Size(278, 112);
      this.groupBox2.TabIndex = 42;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "Position";
      this.label10.AutoSize = true;
      this.label10.Location = new Point(7, 25);
      this.label10.Name = "label10";
      this.label10.Size = new Size(38, 13);
      this.label10.TabIndex = 44;
      this.label10.Text = "Pos X:";
      this.label9.AutoSize = true;
      this.label9.Location = new Point(142, 25);
      this.label9.Name = "label9";
      this.label9.Size = new Size(38, 13);
      this.label9.TabIndex = 43;
      this.label9.Text = "Pos Z:";
      this.label8.AutoSize = true;
      this.label8.Location = new Point(6, 54);
      this.label8.Name = "label8";
      this.label8.Size = new Size(39, 13);
      this.label8.TabIndex = 42;
      this.label8.Text = "Pos H:";
      this.label7.AutoSize = true;
      this.label7.Location = new Point(142, 54);
      this.label7.Name = "label7";
      this.label7.Size = new Size(39, 13);
      this.label7.TabIndex = 41;
      this.label7.Text = "Pos R:";
      this.label6.AutoSize = true;
      this.label6.Location = new Point(7, 82);
      this.label6.Name = "label6";
      this.label6.Size = new Size(46, 13);
      this.label6.TabIndex = 39;
      this.label6.Text = "Y Layer:";
      this.textBox10.BorderStyle = BorderStyle.FixedSingle;
      this.textBox10.Location = new Point(59, 78);
      this.textBox10.Name = "textBox10";
      this.textBox10.Size = new Size(50, 20);
      this.textBox10.TabIndex = 36;
      this.textBox7.BorderStyle = BorderStyle.FixedSingle;
      this.textBox7.Location = new Point(214, 23);
      this.textBox7.Name = "textBox7";
      this.textBox7.Size = new Size(50, 20);
      this.textBox7.TabIndex = 39;
      this.textBox8.BorderStyle = BorderStyle.FixedSingle;
      this.textBox8.Location = new Point(214, 52);
      this.textBox8.Name = "textBox8";
      this.textBox8.Size = new Size(50, 20);
      this.textBox8.TabIndex = 38;
      this.groupBox4.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left;
      this.groupBox4.Controls.Add((Control) this.dgItems);
      this.groupBox4.Controls.Add((Control) this.toolStrip2);
      this.groupBox4.Location = new Point((int) byte.MaxValue, 170);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Size = new Size(550, 291);
      this.groupBox4.TabIndex = 43;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "Items";
      this.dgItems.AllowUserToAddRows = false;
      this.dgItems.AllowUserToDeleteRows = false;
      this.dgItems.BackgroundColor = SystemColors.Control;
      this.dgItems.BorderStyle = BorderStyle.None;
      this.dgItems.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dgItems.Columns.AddRange((DataGridViewColumn) this.Column7, (DataGridViewColumn) this.Column1, (DataGridViewColumn) this.Column2, (DataGridViewColumn) this.Column3, (DataGridViewColumn) this.Column4, (DataGridViewColumn) this.Column5);
      this.dgItems.Dock = DockStyle.Fill;
      this.dgItems.EnableHeadersVisualStyles = false;
      this.dgItems.Location = new Point(3, 16);
      this.dgItems.Name = "dgItems";
      this.dgItems.RowHeadersVisible = false;
      this.dgItems.RowTemplate.Height = 32;
      this.dgItems.Size = new Size(544, 247);
      this.dgItems.TabIndex = 0;
      this.dgItems.CellContentClick += new DataGridViewCellEventHandler(this.dgItems_CellContentClick);
      this.dgItems.CellEndEdit += new DataGridViewCellEventHandler(this.dgItems_CellEndEdit);
      this.Column7.HeaderText = "";
      this.Column7.Name = "Column7";
      this.Column7.Width = 32;
      this.Column1.HeaderText = "ID";
      this.Column1.Name = "Column1";
      this.Column1.Width = 136;
      this.Column2.HeaderText = "Name";
      this.Column2.Name = "Column2";
      this.Column2.ReadOnly = true;
      this.Column2.Width = 135;
      this.Column3.HeaderText = "National";
      this.Column3.Name = "Column3";
      this.Column3.Width = 136;
      this.Column4.HeaderText = "ShopID";
      this.Column4.Name = "Column4";
      this.Column4.Visible = false;
      this.Column4.Width = 50;
      this.Column5.HeaderText = "OldItemID";
      this.Column5.Name = "Column5";
      this.Column5.Visible = false;
      this.toolStrip2.Dock = DockStyle.Bottom;
      this.toolStrip2.GripStyle = ToolStripGripStyle.Hidden;
      this.toolStrip2.Items.AddRange(new ToolStripItem[5]
      {
        (ToolStripItem) this.btnDeleteSelected,
        (ToolStripItem) this.toolStripSeparator1,
        (ToolStripItem) this.btnAddItems,
        (ToolStripItem) this.toolStripSeparator6,
        (ToolStripItem) this.toolStripButton1
      });
      this.toolStrip2.Location = new Point(3, 263);
      this.toolStrip2.Name = "toolStrip2";
      this.toolStrip2.Size = new Size(544, 25);
      this.toolStrip2.TabIndex = 1;
      this.toolStrip2.Text = "toolStrip2";
      this.btnDeleteSelected.DisplayStyle = ToolStripItemDisplayStyle.Text;
      this.btnDeleteSelected.ImageTransparentColor = Color.Magenta;
      this.btnDeleteSelected.Name = "btnDeleteSelected";
      this.btnDeleteSelected.Size = new Size(62, 22);
      this.btnDeleteSelected.Text = "Save Item";
      this.btnDeleteSelected.Click += new EventHandler(this.btnDeleteSelected_Click);
      this.toolStripSeparator1.Name = "toolStripSeparator1";
      this.toolStripSeparator1.Size = new Size(6, 25);
      this.btnAddItems.DisplayStyle = ToolStripItemDisplayStyle.Text;
      this.btnAddItems.ImageTransparentColor = Color.Magenta;
      this.btnAddItems.Name = "btnAddItems";
      this.btnAddItems.Size = new Size(60, 22);
      this.btnAddItems.Text = "Add Item";
      this.btnAddItems.Click += new EventHandler(this.btnAddItems_Click);
      this.toolStripSeparator6.Name = "toolStripSeparator6";
      this.toolStripSeparator6.Size = new Size(6, 25);
      this.toolStripButton1.DisplayStyle = ToolStripItemDisplayStyle.Text;
      this.toolStripButton1.ImageTransparentColor = Color.Magenta;
      this.toolStripButton1.Name = "toolStripButton1";
      this.toolStripButton1.Size = new Size(91, 22);
      this.toolStripButton1.Text = "Delete Selected";
      this.toolStripButton1.Click += new EventHandler(this.toolStripButton1_Click);
      this.button2.FlatStyle = FlatStyle.Flat;
      this.button2.Location = new Point(705, 479);
      this.button2.Name = "button2";
      this.button2.Size = new Size(100, 23);
      this.button2.TabIndex = 44;
      this.button2.Text = "Save";
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.statusStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.toolStripStatusLabel1
      });
      this.statusStrip1.Location = new Point(0, 509);
      this.statusStrip1.Name = "statusStrip1";
      this.statusStrip1.Size = new Size(816, 22);
      this.statusStrip1.TabIndex = 49;
      this.statusStrip1.Text = "statusStrip1";
      this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
      this.toolStripStatusLabel1.Size = new Size(39, 17);
      this.toolStripStatusLabel1.Text = "Ready";
      this.label11.AutoSize = true;
      this.label11.Location = new Point(249, 483);
      this.label11.Name = "label11";
      this.label11.Size = new Size(85, 13);
      this.label11.TabIndex = 50;
      this.label11.Text = "New Shop NPC:";
      this.textBox12.Location = new Point(337, 480);
      this.textBox12.Name = "textBox12";
      this.textBox12.Size = new Size(69, 20);
      this.textBox12.TabIndex = 51;
      this.textBox12.TextChanged += new EventHandler(this.textBox12_TextChanged);
      this.textBox13.Location = new Point(521, 479);
      this.textBox13.Name = "textBox13";
      this.textBox13.Size = new Size(145, 20);
      this.textBox13.TabIndex = 53;
      this.label12.AutoSize = true;
      this.label12.Location = new Point(449, 483);
      this.label12.Name = "label12";
      this.label12.Size = new Size(66, 13);
      this.label12.TabIndex = 52;
      this.label12.Text = "Shop Name:";
      this.button15.BackgroundImage = (Image) Resources.search__5_;
      this.button15.BackgroundImageLayout = ImageLayout.None;
      this.button15.Location = new Point(412, 477);
      this.button15.Name = "button15";
      this.button15.Size = new Size(27, 25);
      this.button15.TabIndex = 54;
      this.button15.UseVisualStyleBackColor = true;
      this.button15.Click += new EventHandler(this.button15_Click);
      this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
      this.saveToolStripMenuItem.Size = new Size(152, 22);
      this.saveToolStripMenuItem.Text = "Save";
      this.saveToolStripMenuItem.Click += new EventHandler(this.saveToolStripMenuItem_Click);
      this.ClientSize = new Size(816, 531);
      this.Controls.Add((Control) this.button15);
      this.Controls.Add((Control) this.textBox13);
      this.Controls.Add((Control) this.label12);
      this.Controls.Add((Control) this.textBox12);
      this.Controls.Add((Control) this.button3);
      this.Controls.Add((Control) this.label11);
      this.Controls.Add((Control) this.statusStrip1);
      this.Controls.Add((Control) this.button1);
      this.Controls.Add((Control) this.button2);
      this.Controls.Add((Control) this.groupBox4);
      this.Controls.Add((Control) this.groupBox2);
      this.Controls.Add((Control) this.groupBox1);
      this.Controls.Add((Control) this.groupBox3);
      this.Controls.Add((Control) this.menuStrip1);
      this.Icon = (Icon) componentResourceManager.GetObject("$this.Icon");
      this.MainMenuStrip = this.menuStrip1;
      this.MaximizeBox = false;
      this.Name = nameof (ShopEditor);
      this.Text = "Shop Editor";
      this.Load += new EventHandler(this.Exporter_Shop_Load);
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.groupBox3.ResumeLayout(false);
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.groupBox2.ResumeLayout(false);
      this.groupBox2.PerformLayout();
      this.groupBox4.ResumeLayout(false);
      this.groupBox4.PerformLayout();
      ((ISupportInitialize) this.dgItems).EndInit();
      this.toolStrip2.ResumeLayout(false);
      this.toolStrip2.PerformLayout();
      this.statusStrip1.ResumeLayout(false);
      this.statusStrip1.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();
    }

    private void button15_Click(object sender, EventArgs e)
    {
      this.textBox12.Text = "0";
      MobPicker mobPicker = new MobPicker();
      if (mobPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox12.Text = mobPicker.MobIndex.ToString();
    }

    private void textBox12_TextChanged(object sender, EventArgs e)
    {
      this.textBox13.Text = this.databaseHandle.MobNameFast(int.Parse(this.textBox12.Text.Trim()));
      this.textBox3.Text = this.databaseHandle.MobNameFast(int.Parse(this.textBox12.Text.Trim()));
    }

    private void saveToolStripMenuItem_Click(object sender, EventArgs e)
    {
      this.exportLodHandle.ExportShop_V4();
    }
  }
}
