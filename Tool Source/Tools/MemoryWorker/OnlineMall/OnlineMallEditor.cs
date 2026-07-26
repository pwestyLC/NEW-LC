// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.OnlineMall.OnlineMall
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
using System.Text;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.OnlineMall
{
  public class OnlineMall : Form
  {
    public static Connection connection = new Connection();
    private string Host = LcDevPack_TeamDamonA.Tools.MemoryWorker.OnlineMall.OnlineMall.connection.Settings.SqlHost;
    private string User = LcDevPack_TeamDamonA.Tools.MemoryWorker.OnlineMall.OnlineMall.connection.Settings.SqlUser;
    private string Password = LcDevPack_TeamDamonA.Tools.MemoryWorker.OnlineMall.OnlineMall.connection.Settings.SqlPassword;
    private string Database = LcDevPack_TeamDamonA.Tools.MemoryWorker.OnlineMall.OnlineMall.connection.Settings.SqlDatabase;
    private string DB_Auth = LcDevPack_TeamDamonA.Tools.MemoryWorker.OnlineMall.OnlineMall.connection.Settings.SqlDbAuth;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    public string _ClientPath = LcDevPack_TeamDamonA.Tools.MemoryWorker.OnlineMall.OnlineMall.connection.Settings.ClientPath;
    public string rowName = "id";
    public List<string> MenuList = new List<string>();
    public List<string> MenuListSearch = new List<string>();
    private DataTable table = new DataTable();
    private DataTable table2 = new DataTable();
    private MySqlCommand command;
    private MySqlDataAdapter adapter;
    private BindingManagerBase managerBase;
    private BindingManagerBase managerBase2;
    private MySqlCommandBuilder builder;
    private string language = LcDevPack_TeamDamonA.Tools.MemoryWorker.OnlineMall.OnlineMall.connection.Settings.Language;
    private IContainer components = (IContainer) null;
    private MySqlDataAdapter sda;
    private BindingSource bSource;
    private DataTable dbdataset;
    private MenuStrip menuStrip1;
    private ToolStripMenuItem menüToolStripMenuItem;
    private ToolStripMenuItem exitToolStripMenuItem;
    private GroupBox groupBox1;
    private TextBox textBox1;
    private TextBox textBox2;
    private TextBox textBox3;
    private TextBox textBox4;
    private Button button1;
    private TextBox textBox6;
    private TextBox textBox5;
    private Label label2;
    private Label label1;
    private TextBox textBox7;
    private TextBox textBox8;
    private Label label4;
    private ListBox listBox1;
    private Button button3;
    private Button button4;
    private ComboBox comboBox1;
    private TextBox textBox9;
    private TextBox textBox10;
    private Label label5;
    private Label label7;
    private TextBox textBox11;
    private Panel panel3DView;
    private Button button5;
    private TextBox textBox12;
    private Label label8;
    private TextBox textBox13;
    private Label label9;
    private Label label11;
    private Label label10;
    private Button button2;
    private TextBox textBox15;
    private TextBox textBox14;
    private string country;
    public string[] menuArray = new string[2]
    {
      "id",
      "title"
    };
    public string[] menuArrayGER = new string[2]
    {
      "id",
      "title"
    };
    public string[] menuArrayPOL = new string[2]
    {
      "id",
      "title"
    };
    public string[] menuArrayBRA = new string[2]
    {
      "id",
      "title"
    };
    public string[] menuArrayRUS = new string[2]
    {
      "id",
      "title"
    };
    public string[] menuArrayFRA = new string[2]
    {
      "id",
      "title"
    };
    public string[] menuArrayESP = new string[2]
    {
      "id",
      "title"
    };
    public string[] menuArrayMEX = new string[2]
    {
      "id",
      "title"
    };
    public string[] menuArrayTHA = new string[2]
    {
      "id",
      "title"
    };
    public string[] menuArrayITA = new string[2]
    {
      "id",
      "title"
    };
    public string[] menuArrayUSA = new string[2]
    {
      "id",
      "title"
    };

    public string NationCode()
    {
      if (this.language == "GER")
      {
        this.country = "13";
        return this.country;
      }
      if (this.language == "POL")
      {
        this.country = "16";
        return this.country;
      }
      if (this.language == "BRA")
      {
        this.country = "10";
        return this.country;
      }
      if (this.language == "RUS")
      {
        this.country = "17";
        return this.country;
      }
      if (this.language == "FRA")
      {
        this.country = "15";
        return this.country;
      }
      if (this.language == "ESP")
      {
        this.country = "14";
        return this.country;
      }
      if (this.language == "MEX")
      {
        this.country = "20";
        return this.country;
      }
      if (this.language == "THA")
      {
        this.country = "4";
        return this.country;
      }
      if (this.language == "ITA")
      {
        this.country = "19";
        return this.country;
      }
      if (!(this.language == "USA"))
        return (string) null;
      this.country = "9";
      return this.country;
    }

    public OnlineMall()
    {
      this.InitializeComponent();
      this.LoadListBox();
    }

    private void IniRead()
    {
      IniFile iniFile = new IniFile(Application.StartupPath + "\\Config\\Settings.cfg");
      this.textBox2.Text = iniFile.IniReadValue("## MYSQL", "SQL_HOST");
      this.textBox3.Text = iniFile.IniReadValue("## MYSQL", "SQL_USER");
      this.textBox4.Text = iniFile.IniReadValue("## MYSQL", "SQL_PASSWORD");
      this.textBox5.Text = iniFile.IniReadValue("## MYSQL", "SQL_DATABASE");
      this.textBox9.Text = iniFile.IniReadValue("## MYSQL", "SQL_DB_AUTH");
    }

    private void LoadListBox()
    {
      OnlineMallList.List.Clear();
      OnlineMallList.Import();
      this.listBox1.SelectedIndex = -1;
      this.MenuList.Clear();
      this.country = this.NationCode();
      string Query = "SELECT id, title, description, price, item_code, cat_name FROM lastchaos_bundles_time ORDER BY id;";
      if (this.language == "GER")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayGER, this.Host, this.User, this.Password, this.DB_Auth, "select id, title, description, price, item_code, cat_name FROM lastchaos_bundles_time ORDER BY id;");
      else if (this.language == "BRA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayBRA, this.Host, this.User, this.Password, this.DB_Auth, "select id, title, description, price, item_code, cat_name FROM lastchaos_bundles_time ORDER BY id;");
      else if (this.language == "RUS")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayRUS, this.Host, this.User, this.Password, this.DB_Auth, "select id, title, description, price, item_code, cat_name FROM lastchaos_bundles_time ORDER BY id;");
      else if (this.language == "ESP")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayESP, this.Host, this.User, this.Password, this.DB_Auth, "select id, title, description, price, item_code, cat_name FROM lastchaos_bundles_time ORDER BY id;");
      else if (this.language == "MEX")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayMEX, this.Host, this.User, this.Password, this.DB_Auth, "select id, title, description, price, item_code, cat_name FROM lastchaos_bundles_time ORDER BY id;");
      else if (this.language == "THA")
      {
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayTHA, this.Host, this.User, this.Password, this.DB_Auth, Query);
        for (int index = 0; index < this.listBox1.Items.Count; ++index)
          this.MenuList.Add(OnlineMallList.List[index].ItemID.ToString() + " - " + OnlineMallList.List[index].Name.ToString());
        this.listBox1.DataSource = (object) this.MenuList;
      }
      else if (this.language == "ITA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayITA, this.Host, this.User, this.Password, this.DB_Auth, "select id, title, description, price, item_code, cat_name FROM lastchaos_bundles_time ORDER BY id;");
      else if (this.language == "USA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayUSA, this.Host, this.User, this.Password, this.DB_Auth, "select id, title, description, price, item_code, cat_name FROM lastchaos_bundles_time ORDER BY id;");
      else
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.DB_Auth, "select id, title, description, price, item_code, cat_name FROM lastchaos_bundles_time ORDER BY id;");
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
      this.ClearBox();
      if (this.listBox1.SelectedIndex != -1)
        this.textBox6.Text = this.GetIndex().ToString();
      string Query = "select id, title, description, price, item_code, cat_name FROM lastchaos_bundles_time WHERE id ='" + this.textBox6.Text + "';";
      string[] rows = new string[6]
      {
        "id",
        "title",
        "description",
        "price",
        "item_code",
        "cat_name"
      };
      Query.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'");
      string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.DB_Auth, Query, rows);
      this.textBox6.Text = strArray[0];
      this.textBox5.Text = strArray[1];
      this.textBox11.Text = strArray[2];
      this.textBox13.Text = strArray[3];
      this.textBox10.Text = strArray[4];
      this.textBox8.Text = strArray[5];
      if (this.textBox8.Text == "Featured")
        this.comboBox1.SelectedIndex = 0;
      if (this.textBox8.Text == "Platinum")
        this.comboBox1.SelectedIndex = 1;
      if (this.textBox8.Text == "Boosts")
        this.comboBox1.SelectedIndex = 2;
      if (this.textBox8.Text == "Avatar")
        this.comboBox1.SelectedIndex = 3;
      if (this.textBox8.Text == "Pets")
        this.comboBox1.SelectedIndex = 4;
      if (this.textBox8.Text == "Misc")
        this.comboBox1.SelectedIndex = 5;
      if (this.textBox8.Text == "Package")
        this.comboBox1.SelectedIndex = 6;
      if (this.textBox8.Text == "Premium")
        this.comboBox1.SelectedIndex = 7;
      if (this.language == "THA")
      {
        int ItemID = this.GetID();
        if (ItemID == -1)
          return;
        tOnlineCatalog tOnlineCatalog = OnlineMallList.List.Find((Predicate<tOnlineCatalog>) (p => p.ItemID.Equals(ItemID)));
        if (tOnlineCatalog == null)
          return;
        this.textBox5.Text = tOnlineCatalog.Name;
        this.textBox11.Text = tOnlineCatalog.Desc;
      }
      else
        this.textBox5.Text = strArray[1];
    }

    private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (this.comboBox1.SelectedIndex == 0)
        this.textBox8.Text = "Featured";
      if (this.comboBox1.SelectedIndex == 1)
        this.textBox8.Text = "Platinum";
      if (this.comboBox1.SelectedIndex == 2)
        this.textBox8.Text = "Boosts";
      if (this.comboBox1.SelectedIndex == 3)
        this.textBox8.Text = "Avatar";
      if (this.comboBox1.SelectedIndex == 4)
        this.textBox8.Text = "Pets";
      if (this.comboBox1.SelectedIndex == 5)
        this.textBox8.Text = "Misc";
      if (this.comboBox1.SelectedIndex == 6)
        this.textBox8.Text = "Package";
      if (this.comboBox1.SelectedIndex != 7)
        return;
      this.textBox8.Text = "Premium";
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
      if (this.language == "THA")
      {
        this.country = this.NationCode();
        string s1 = this.textBox5.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        string str1 = Encoding.GetEncoding("iso-8859-1").GetString(Encoding.GetEncoding("TIS-620").GetBytes(s1));
        string s2 = this.textBox11.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        string str2 = Encoding.GetEncoding("iso-8859-1").GetString(Encoding.GetEncoding("TIS-620").GetBytes(s2));
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.DB_Auth, "UPDATE lastchaos_bundles_time SET title = '" + str1 + "', description = '" + str2 + "', item_code = '" + this.textBox10.Text + "', price = '" + this.textBox13.Text + "', cat_name = '" + this.textBox8.Text + "' WHERE id = '" + this.textBox6.Text + "'");
        OnlineMallList.List.Clear();
        OnlineMallList.Import();
      }
      else if (this.language == "USA")
      {
        this.country = this.NationCode();
        string s3 = this.textBox5.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        string str3 = Encoding.GetEncoding("iso-8859-1").GetString(Encoding.GetEncoding("TIS-620").GetBytes(s3));
        string s4 = this.textBox11.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        string str4 = Encoding.GetEncoding("iso-8859-1").GetString(Encoding.GetEncoding("TIS-620").GetBytes(s4));
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.DB_Auth, "UPDATE lastchaos_bundles_time SET title = '" + str3 + "', description = '" + str4 + "', item_code = '" + this.textBox10.Text + "', price = '" + this.textBox13.Text + "', cat_name = '" + this.textBox8.Text + "' WHERE id = '" + this.textBox6.Text + "'");
        OnlineMallList.List.Clear();
        OnlineMallList.Import();
      }
      else
      {
        this.country = this.NationCode();
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.DB_Auth, "UPDATE lastchaos_bundles_time SET title = '" + this.textBox5.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', description = '" + this.textBox11.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', item_code = '" + this.textBox10.Text + "', price = '" + this.textBox13.Text + "', cat_name = '" + this.textBox8.Text + "' WHERE id = '" + this.textBox6.Text + "'");
      }
      int num = (int) MessageBox.Show("Update", "Completed", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
      int selectedIndex = this.listBox1.SelectedIndex;
      this.LoadListBox();
      this.listBox1.SelectedIndex = selectedIndex;
    }

    private void button3_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want copy to New Item mall Index " + this.textBox6.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      if (this.textBox5.Text.Trim().Length <= 0 || this.textBox8.Text.Trim().Length <= 0)
      {
        int num1 = (int) MessageBox.Show("please add Data", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.DB_Auth, "DROP TABLE IF EXISTS tempTable;CREATE TEMPORARY TABLE tempTable ENGINE=MEMORY SELECT * FROM lastchaos_bundles_time WHERE id=" + this.textBox6.Text + ";SELECT id FROM tempTable;UPDATE tempTable SET id=(SELECT id from lastchaos_bundles_time ORDER BY id DESC LIMIT 1)+1; SELECT id FROM tempTable;INSERT INTO lastchaos_bundles_time SELECT * FROM tempTable;");
        int num2 = (int) MessageBox.Show("Successful copy", "Completed", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
        OnlineMallList.List.Clear();
        OnlineMallList.Import();
        int selectedIndex = this.listBox1.SelectedIndex;
        this.LoadListBox();
        this.listBox1.SelectedIndex = selectedIndex + 1;
      }
    }

    private void button4_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want to Delete Item mall " + this.textBox6.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      int selectedIndex = this.listBox1.SelectedIndex;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.DB_Auth, "DELETE FROM lastchaos_bundles_time WHERE id = '" + this.textBox6.Text + "'");
      OnlineMallList.List.Clear();
      OnlineMallList.Import();
      this.LoadListBox();
      this.listBox1.SelectedIndex = selectedIndex - 1;
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
      this.exitToolStripMenuItem = new ToolStripMenuItem();
      this.groupBox1 = new GroupBox();
      this.button2 = new Button();
      this.label11 = new Label();
      this.label10 = new Label();
      this.textBox13 = new TextBox();
      this.label9 = new Label();
      this.textBox12 = new TextBox();
      this.label8 = new Label();
      this.button5 = new Button();
      this.panel3DView = new Panel();
      this.label7 = new Label();
      this.textBox11 = new TextBox();
      this.textBox10 = new TextBox();
      this.label5 = new Label();
      this.comboBox1 = new ComboBox();
      this.button4 = new Button();
      this.button3 = new Button();
      this.label4 = new Label();
      this.button1 = new Button();
      this.textBox6 = new TextBox();
      this.textBox5 = new TextBox();
      this.label2 = new Label();
      this.label1 = new Label();
      this.textBox8 = new TextBox();
      this.textBox1 = new TextBox();
      this.textBox2 = new TextBox();
      this.textBox3 = new TextBox();
      this.textBox4 = new TextBox();
      this.textBox7 = new TextBox();
      this.listBox1 = new ListBox();
      this.textBox9 = new TextBox();
      this.textBox14 = new TextBox();
      this.textBox15 = new TextBox();
      this.menuStrip1.SuspendLayout();
      this.groupBox1.SuspendLayout();
      this.SuspendLayout();
      this.menuStrip1.BackColor = Color.Transparent;
      this.menuStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.menüToolStripMenuItem
      });
      this.menuStrip1.Location = new Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new Size(965, 24);
      this.menuStrip1.TabIndex = 0;
      this.menuStrip1.Text = "menuStrip1";
      this.menüToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.exitToolStripMenuItem
      });
      this.menüToolStripMenuItem.Name = "menüToolStripMenuItem";
      this.menüToolStripMenuItem.Size = new Size(50, 20);
      this.menüToolStripMenuItem.Text = "Menü";
      this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
      this.exitToolStripMenuItem.Size = new Size(93, 22);
      this.exitToolStripMenuItem.Text = "Exit";
      this.exitToolStripMenuItem.Click += new EventHandler(this.exitToolStripMenuItem_Click);
      this.groupBox1.Controls.Add((Control) this.textBox15);
      this.groupBox1.Controls.Add((Control) this.textBox14);
      this.groupBox1.Controls.Add((Control) this.button2);
      this.groupBox1.Controls.Add((Control) this.label11);
      this.groupBox1.Controls.Add((Control) this.label10);
      this.groupBox1.Controls.Add((Control) this.textBox13);
      this.groupBox1.Controls.Add((Control) this.label9);
      this.groupBox1.Controls.Add((Control) this.textBox12);
      this.groupBox1.Controls.Add((Control) this.label8);
      this.groupBox1.Controls.Add((Control) this.button5);
      this.groupBox1.Controls.Add((Control) this.panel3DView);
      this.groupBox1.Controls.Add((Control) this.label7);
      this.groupBox1.Controls.Add((Control) this.textBox11);
      this.groupBox1.Controls.Add((Control) this.textBox10);
      this.groupBox1.Controls.Add((Control) this.label5);
      this.groupBox1.Controls.Add((Control) this.comboBox1);
      this.groupBox1.Controls.Add((Control) this.button4);
      this.groupBox1.Controls.Add((Control) this.button3);
      this.groupBox1.Controls.Add((Control) this.label4);
      this.groupBox1.Controls.Add((Control) this.button1);
      this.groupBox1.Controls.Add((Control) this.textBox6);
      this.groupBox1.Controls.Add((Control) this.textBox5);
      this.groupBox1.Controls.Add((Control) this.label2);
      this.groupBox1.Controls.Add((Control) this.label1);
      this.groupBox1.Location = new Point(496, 27);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(457, 293);
      this.groupBox1.TabIndex = 2;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Item Information";
      this.button2.BackColor = Color.Violet;
      this.button2.FlatStyle = FlatStyle.Flat;
      this.button2.Image = (Image) Resources._08;
      this.button2.ImageAlign = ContentAlignment.MiddleLeft;
      this.button2.Location = new Point(318, 94);
      this.button2.Name = "button2";
      this.button2.Size = new Size(133, 27);
      this.button2.TabIndex = 82;
      this.button2.Text = "      Update Name+Desc";
      this.button2.UseVisualStyleBackColor = false;
      this.button2.Visible = false;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.label11.AutoSize = true;
      this.label11.Location = new Point(11, 128);
      this.label11.Name = "label11";
      this.label11.Size = new Size(80, 13);
      this.label11.TabIndex = 81;
      this.label11.Text = "Selected Desc:";
      this.label11.Visible = false;
      this.label10.AutoSize = true;
      this.label10.Location = new Point(11, 105);
      this.label10.Name = "label10";
      this.label10.Size = new Size(83, 13);
      this.label10.TabIndex = 80;
      this.label10.Text = "Selected Name:";
      this.label10.Visible = false;
      this.textBox13.Location = new Point(374, 68);
      this.textBox13.Name = "textBox13";
      this.textBox13.Size = new Size(77, 20);
      this.textBox13.TabIndex = 78;
      this.label9.AutoSize = true;
      this.label9.Location = new Point(340, 71);
      this.label9.Name = "label9";
      this.label9.Size = new Size(34, 13);
      this.label9.TabIndex = 77;
      this.label9.Text = "Price:";
      this.textBox12.Enabled = false;
      this.textBox12.Location = new Point(254, 68);
      this.textBox12.Name = "textBox12";
      this.textBox12.Size = new Size(77, 20);
      this.textBox12.TabIndex = 76;
      this.textBox12.Visible = false;
      this.label8.AutoSize = true;
      this.label8.Location = new Point(220, 71);
      this.label8.Name = "label8";
      this.label8.Size = new Size(28, 13);
      this.label8.TabIndex = 75;
      this.label8.Text = "Q'ty:";
      this.label8.Visible = false;
      this.button5.Image = (Image) Resources.search__5_;
      this.button5.Location = new Point(185, 66);
      this.button5.Name = "button5";
      this.button5.Size = new Size(30, 27);
      this.button5.TabIndex = 74;
      this.button5.UseVisualStyleBackColor = true;
      this.button5.Click += new EventHandler(this.button5_Click);
      this.panel3DView.Location = new Point(147, 63);
      this.panel3DView.Name = "panel3DView";
      this.panel3DView.Size = new Size(32, 32);
      this.panel3DView.TabIndex = 73;
      this.label7.AutoSize = true;
      this.label7.Location = new Point(23, 206);
      this.label7.Name = "label7";
      this.label7.Size = new Size(35, 13);
      this.label7.TabIndex = 72;
      this.label7.Text = "Desc:";
      this.textBox11.Location = new Point(64, 188);
      this.textBox11.Multiline = true;
      this.textBox11.Name = "textBox11";
      this.textBox11.Size = new Size(346, 57);
      this.textBox11.TabIndex = 70;
      this.textBox10.Enabled = false;
      this.textBox10.Location = new Point(64, 68);
      this.textBox10.Name = "textBox10";
      this.textBox10.Size = new Size(77, 20);
      this.textBox10.TabIndex = 69;
      this.textBox10.TextChanged += new EventHandler(this.textBox10_TextChanged);
      this.label5.AutoSize = true;
      this.label5.Location = new Point(0, 71);
      this.label5.Name = "label5";
      this.label5.Size = new Size(66, 13);
      this.label5.TabIndex = 68;
      this.label5.Text = "Item Mall ID:";
      this.comboBox1.FormattingEnabled = true;
      this.comboBox1.Items.AddRange(new object[8]
      {
        (object) "Featured",
        (object) "Platinum",
        (object) "Boosts",
        (object) "Avatar",
        (object) "Pets",
        (object) "Misc",
        (object) "Package",
        (object) "Premium"
      });
      this.comboBox1.Location = new Point(218, 31);
      this.comboBox1.Name = "comboBox1";
      this.comboBox1.Size = new Size(121, 21);
      this.comboBox1.TabIndex = 67;
      this.comboBox1.SelectedIndexChanged += new EventHandler(this.comboBox1_SelectedIndexChanged);
      this.button4.BackColor = Color.LightCoral;
      this.button4.FlatStyle = FlatStyle.Flat;
      this.button4.Image = (Image) Resources.delete;
      this.button4.ImageAlign = ContentAlignment.MiddleLeft;
      this.button4.Location = new Point(366, (int) byte.MaxValue);
      this.button4.Name = "button4";
      this.button4.Size = new Size(77, 27);
      this.button4.TabIndex = 66;
      this.button4.Text = "    Delete";
      this.button4.UseVisualStyleBackColor = false;
      this.button4.Click += new EventHandler(this.button4_Click);
      this.button3.BackColor = Color.Gold;
      this.button3.FlatStyle = FlatStyle.Flat;
      this.button3.Image = (Image) Resources.control_add_blue;
      this.button3.ImageAlign = ContentAlignment.MiddleLeft;
      this.button3.Location = new Point(14, (int) byte.MaxValue);
      this.button3.Name = "button3";
      this.button3.Size = new Size(87, 27);
      this.button3.TabIndex = 11;
      this.button3.Text = "    Add Copy";
      this.button3.UseVisualStyleBackColor = false;
      this.button3.Click += new EventHandler(this.button3_Click);
      this.label4.AutoSize = true;
      this.label4.Location = new Point(166, 34);
      this.label4.Name = "label4";
      this.label4.Size = new Size(46, 13);
      this.label4.TabIndex = 9;
      this.label4.Text = "Catalog:";
      this.button1.BackColor = Color.LightCyan;
      this.button1.FlatStyle = FlatStyle.Flat;
      this.button1.Image = (Image) Resources._08;
      this.button1.ImageAlign = ContentAlignment.MiddleLeft;
      this.button1.Location = new Point(107, (int) byte.MaxValue);
      this.button1.Name = "button1";
      this.button1.Size = new Size(72, 27);
      this.button1.TabIndex = 7;
      this.button1.Text = "      Update";
      this.button1.UseVisualStyleBackColor = false;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.textBox6.Enabled = false;
      this.textBox6.Location = new Point(65, 31);
      this.textBox6.Name = "textBox6";
      this.textBox6.Size = new Size(76, 20);
      this.textBox6.TabIndex = 4;
      this.textBox6.TextChanged += new EventHandler(this.textBox6_TextChanged);
      this.textBox5.Location = new Point(64, 155);
      this.textBox5.Multiline = true;
      this.textBox5.Name = "textBox5";
      this.textBox5.Size = new Size(346, 24);
      this.textBox5.TabIndex = 3;
      this.textBox5.TextChanged += new EventHandler(this.textBox5_TextChanged);
      this.label2.AutoSize = true;
      this.label2.Location = new Point(20, 158);
      this.label2.Name = "label2";
      this.label2.Size = new Size(38, 13);
      this.label2.TabIndex = 1;
      this.label2.Text = "Name:";
      this.label1.AutoSize = true;
      this.label1.Location = new Point(23, 34);
      this.label1.Name = "label1";
      this.label1.Size = new Size(36, 13);
      this.label1.TabIndex = 0;
      this.label1.Text = "Index:";
      this.textBox8.Enabled = false;
      this.textBox8.Location = new Point(665, 4);
      this.textBox8.Name = "textBox8";
      this.textBox8.Size = new Size(121, 20);
      this.textBox8.TabIndex = 10;
      this.textBox8.Visible = false;
      this.textBox1.Location = new Point(632, 370);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(100, 20);
      this.textBox1.TabIndex = 3;
      this.textBox1.Visible = false;
      this.textBox2.Location = new Point(525, 370);
      this.textBox2.Name = "textBox2";
      this.textBox2.Size = new Size(100, 20);
      this.textBox2.TabIndex = 4;
      this.textBox2.Visible = false;
      this.textBox3.Location = new Point(631, 344);
      this.textBox3.Name = "textBox3";
      this.textBox3.Size = new Size(100, 20);
      this.textBox3.TabIndex = 5;
      this.textBox3.Visible = false;
      this.textBox4.Location = new Point(525, 344);
      this.textBox4.Name = "textBox4";
      this.textBox4.Size = new Size(100, 20);
      this.textBox4.TabIndex = 6;
      this.textBox4.Visible = false;
      this.textBox7.Location = new Point(525, 396);
      this.textBox7.Name = "textBox7";
      this.textBox7.Size = new Size(100, 20);
      this.textBox7.TabIndex = 6;
      this.textBox7.Visible = false;
      this.listBox1.FormattingEnabled = true;
      this.listBox1.Location = new Point(12, 27);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new Size(478, 394);
      this.listBox1.TabIndex = 7;
      this.listBox1.SelectedIndexChanged += new EventHandler(this.listBox1_SelectedIndexChanged);
      this.textBox9.Location = new Point(632, 396);
      this.textBox9.Name = "textBox9";
      this.textBox9.Size = new Size(100, 20);
      this.textBox9.TabIndex = 8;
      this.textBox9.Visible = false;
      this.textBox14.Enabled = false;
      this.textBox14.Location = new Point(100, 102);
      this.textBox14.Name = "textBox14";
      this.textBox14.Size = new Size(212, 20);
      this.textBox14.TabIndex = 83;
      this.textBox14.Visible = false;
      this.textBox15.Enabled = false;
      this.textBox15.Location = new Point(100, 125);
      this.textBox15.Name = "textBox15";
      this.textBox15.Size = new Size(351, 20);
      this.textBox15.TabIndex = 84;
      this.textBox15.Visible = false;
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(965, 432);
      this.Controls.Add((Control) this.textBox9);
      this.Controls.Add((Control) this.listBox1);
      this.Controls.Add((Control) this.textBox7);
      this.Controls.Add((Control) this.textBox4);
      this.Controls.Add((Control) this.textBox3);
      this.Controls.Add((Control) this.textBox8);
      this.Controls.Add((Control) this.textBox2);
      this.Controls.Add((Control) this.textBox1);
      this.Controls.Add((Control) this.groupBox1);
      this.Controls.Add((Control) this.menuStrip1);
      this.FormBorderStyle = FormBorderStyle.Fixed3D;
      this.MainMenuStrip = this.menuStrip1;
      this.MaximizeBox = false;
      this.Name = nameof (OnlineMall);
      this.Text = "LastChaos Online Mall Editor";
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();
    }

    private void button5_Click(object sender, EventArgs e)
    {
      this.textBox10.Text = "0";
      CatalogPicker catalogPicker = new CatalogPicker();
      if (catalogPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox10.Text = catalogPicker.ItemIndex.ToString();
      int ItemID = int.Parse(this.textBox10.Text);
      if (ItemID == -1)
        return;
      tCatalog tCatalog = CatalogList.List.Find((Predicate<tCatalog>) (p => p.ItemID.Equals(ItemID)));
      if (tCatalog == null)
        return;
      this.textBox5.Text = tCatalog.Name;
      this.textBox11.Text = tCatalog.Desc;
    }

    private void textBox10_TextChanged(object sender, EventArgs e)
    {
    }

    private void button2_Click(object sender, EventArgs e)
    {
      int ItemID = int.Parse(this.textBox10.Text);
      if (ItemID == -1)
        return;
      tCatalog tCatalog = CatalogList.List.Find((Predicate<tCatalog>) (p => p.ItemID.Equals(ItemID)));
      if (tCatalog == null)
        return;
      this.textBox5.Text = tCatalog.Name;
      this.textBox11.Text = tCatalog.Desc;
    }
  }
}
