// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.OX.OX
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
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.OX
{
  public class OX : Form
  {
    public static Connection connection = new Connection();
    private string Host = LcDevPack_TeamDamonA.Tools.MemoryWorker.OX.OX.connection.Settings.SqlHost;
    private string User = LcDevPack_TeamDamonA.Tools.MemoryWorker.OX.OX.connection.Settings.SqlUser;
    private string Password = LcDevPack_TeamDamonA.Tools.MemoryWorker.OX.OX.connection.Settings.SqlPassword;
    private string Database = LcDevPack_TeamDamonA.Tools.MemoryWorker.OX.OX.connection.Settings.SqlDatabase;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    public string _ClientPath = LcDevPack_TeamDamonA.Tools.MemoryWorker.OX.OX.connection.Settings.ClientPath;
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
    private string language = LcDevPack_TeamDamonA.Tools.MemoryWorker.OX.OX.connection.Settings.Language;
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
    private RadioButton radioButton2;
    private RadioButton radioButton1;
    private TextBox textBox6;
    private TextBox textBox5;
    private Label label3;
    private Label label2;
    private Label label1;
    private TextBox textBox7;
    private TextBox textBox8;
    private Label label4;
    private ListBox listBox1;
    private Button button3;
    private Button button4;
    private ComboBox comboBox1;
    private string country;
    public string[] menuArray = new string[2]
    {
      "a_index",
      "a_question"
    };
    public string[] menuArrayGER = new string[2]
    {
      "a_index",
      "a_question"
    };
    public string[] menuArrayPOL = new string[2]
    {
      "a_index",
      "a_question"
    };
    public string[] menuArrayBRA = new string[2]
    {
      "a_index",
      "a_question"
    };
    public string[] menuArrayRUS = new string[2]
    {
      "a_index",
      "a_question"
    };
    public string[] menuArrayFRA = new string[2]
    {
      "a_index",
      "a_question"
    };
    public string[] menuArrayESP = new string[2]
    {
      "a_index",
      "a_question"
    };
    public string[] menuArrayMEX = new string[2]
    {
      "a_index",
      "a_question"
    };
    public string[] menuArrayTHA = new string[2]
    {
      "a_index",
      "a_question"
    };
    public string[] menuArrayITA = new string[2]
    {
      "a_index",
      "a_question"
    };
    public string[] menuArrayUSA = new string[2]
    {
      "a_index",
      "a_question"
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

    public OX()
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
    }

    private void LoadListBox()
    {
      this.listBox1.SelectedIndex = -1;
      this.MenuList.Clear();
      this.country = this.NationCode();
      string Query = "SELECT a_index, a_question, a_answer, a_country FROM t_oxquiz ORDER BY a_index;";
      if (this.language == "GER")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayGER, this.Host, this.User, this.Password, this.Database, "select a_index, a_question, a_answer, a_country FROM t_oxquiz ORDER BY a_index;");
      else if (this.language == "BRA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayBRA, this.Host, this.User, this.Password, this.Database, "select a_index, a_question, a_answer, a_country FROM t_oxquiz ORDER BY a_index;");
      else if (this.language == "RUS")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayRUS, this.Host, this.User, this.Password, this.Database, "select a_index, a_question, a_answer, a_country FROM t_oxquiz ORDER BY a_index;");
      else if (this.language == "ESP")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayESP, this.Host, this.User, this.Password, this.Database, "select a_index, a_question, a_answer, a_country FROM t_oxquiz ORDER BY a_index;");
      else if (this.language == "MEX")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayMEX, this.Host, this.User, this.Password, this.Database, "select a_index, a_question, a_answer, a_country FROM t_oxquiz ORDER BY a_index;");
      else if (this.language == "THA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayTHA, this.Host, this.User, this.Password, this.Database, Query);
      else if (this.language == "ITA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayITA, this.Host, this.User, this.Password, this.Database, "select a_index, a_question, a_answer, a_country FROM t_oxquiz ORDER BY a_index;");
      else if (this.language == "USA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayUSA, this.Host, this.User, this.Password, this.Database, "select a_index, a_question, a_answer, a_country FROM t_oxquiz ORDER BY a_index;");
      else
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, "select a_index, a_question, a_answer, a_country FROM t_oxquiz ORDER BY a_index;");
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
      string Query = "select a_index, a_question, a_answer, a_country FROM t_oxquiz WHERE a_index ='" + this.textBox6.Text + "';";
      string[] rows = new string[4]
      {
        "a_index",
        "a_question",
        "a_answer",
        "a_country"
      };
      Query.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'");
      string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query, rows);
      this.textBox6.Text = strArray[0];
      this.textBox5.Text = strArray[1];
      this.textBox7.Text = strArray[2];
      this.textBox8.Text = strArray[3];
      if (this.textBox7.Text == "O")
        this.radioButton1.Checked = true;
      if (this.textBox7.Text == "X")
        this.radioButton2.Checked = true;
      if (this.textBox8.Text == "4")
        this.comboBox1.SelectedIndex = 0;
      if (this.textBox8.Text == "9")
        this.comboBox1.SelectedIndex = 1;
      if (this.textBox8.Text == "13")
        this.comboBox1.SelectedIndex = 2;
      if (this.textBox8.Text == "14")
        this.comboBox1.SelectedIndex = 3;
      if (this.textBox8.Text == "10")
        this.comboBox1.SelectedIndex = 4;
      if (this.textBox8.Text == "15")
        this.comboBox1.SelectedIndex = 5;
      if (this.textBox8.Text == "16")
        this.comboBox1.SelectedIndex = 6;
      if (this.textBox8.Text == "17")
        this.comboBox1.SelectedIndex = 7;
      if (this.textBox8.Text == "20")
        this.comboBox1.SelectedIndex = 8;
      else
        this.textBox5.Text = strArray[1];
    }

    private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (this.comboBox1.SelectedIndex == 0)
        this.textBox8.Text = "4";
      if (this.comboBox1.SelectedIndex == 1)
        this.textBox8.Text = "9";
      if (this.comboBox1.SelectedIndex == 2)
        this.textBox8.Text = "13";
      if (this.comboBox1.SelectedIndex == 3)
        this.textBox8.Text = "14";
      if (this.comboBox1.SelectedIndex == 4)
        this.textBox8.Text = "10";
      if (this.comboBox1.SelectedIndex == 5)
        this.textBox8.Text = "15";
      if (this.comboBox1.SelectedIndex == 6)
        this.textBox8.Text = "16";
      if (this.comboBox1.SelectedIndex == 7)
        this.textBox8.Text = "17";
      if (this.comboBox1.SelectedIndex != 8)
        return;
      this.textBox8.Text = "20";
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
        this.textBox5.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_oxquiz SET a_question = '" + this.textBox5.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_answer = '" + this.textBox7.Text + "',a_country = '" + this.textBox8.Text + "' WHERE a_index = '" + this.textBox6.Text + "'");
      }
      else if (this.language == "USA")
      {
        this.country = this.NationCode();
        this.textBox5.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_oxquiz SET a_question = '" + this.textBox5.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_answer = '" + this.textBox7.Text + "',a_country = '" + this.textBox8.Text + "' WHERE a_index = '" + this.textBox6.Text + "'");
      }
      else
      {
        this.country = this.NationCode();
        this.textBox5.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_oxquiz SET a_question = '" + this.textBox5.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_answer = '" + this.textBox7.Text + "',a_country = '" + this.textBox8.Text + "' WHERE a_index = '" + this.textBox6.Text + "'");
      }
      int num = (int) MessageBox.Show("Update", "Completed", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
      int selectedIndex = this.listBox1.SelectedIndex;
      this.LoadListBox();
      this.listBox1.SelectedIndex = selectedIndex;
    }

    private void button3_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want copy to New Quiz Index " + this.textBox6.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      if (this.textBox5.Text.Trim().Length <= 0 || this.textBox8.Text.Trim().Length <= 0)
      {
        int num1 = (int) MessageBox.Show("please add Data", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DROP TABLE IF EXISTS tempTable;CREATE TEMPORARY TABLE tempTable ENGINE=MEMORY SELECT * FROM t_oxquiz WHERE a_index=" + this.textBox6.Text + ";SELECT a_index FROM tempTable;UPDATE tempTable SET a_index=(SELECT a_index from t_oxquiz ORDER BY a_index DESC LIMIT 1)+1; SELECT a_index FROM tempTable;INSERT INTO t_oxquiz SELECT * FROM tempTable;");
        int num2 = (int) MessageBox.Show("Successful copy", "Completed", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
        int selectedIndex = this.listBox1.SelectedIndex;
        this.LoadListBox();
        this.listBox1.SelectedIndex = selectedIndex + 1;
      }
    }

    private void button4_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want to Delete Quiz " + this.textBox6.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      int selectedIndex = this.listBox1.SelectedIndex;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_oxquiz WHERE a_index = '" + this.textBox6.Text + "'");
      this.LoadListBox();
      this.listBox1.SelectedIndex = selectedIndex - 1;
    }

    private void radioButton1_CheckedChanged(object sender, EventArgs e)
    {
      if (this.radioButton1.Checked)
      {
        this.textBox7.Text = "O";
      }
      else
      {
        if (this.radioButton1.Checked)
          return;
        this.textBox7.Clear();
      }
    }

    private void radioButton2_CheckedChanged(object sender, EventArgs e)
    {
      if (this.radioButton2.Checked)
      {
        this.textBox7.Text = "X";
      }
      else
      {
        if (this.radioButton2.Checked)
          return;
        this.textBox7.Clear();
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
      this.menuStrip1 = new MenuStrip();
      this.menüToolStripMenuItem = new ToolStripMenuItem();
      this.exitToolStripMenuItem = new ToolStripMenuItem();
      this.groupBox1 = new GroupBox();
      this.button4 = new Button();
      this.button3 = new Button();
      this.textBox8 = new TextBox();
      this.label4 = new Label();
      this.button1 = new Button();
      this.radioButton2 = new RadioButton();
      this.radioButton1 = new RadioButton();
      this.textBox6 = new TextBox();
      this.textBox5 = new TextBox();
      this.label3 = new Label();
      this.label2 = new Label();
      this.label1 = new Label();
      this.textBox1 = new TextBox();
      this.textBox2 = new TextBox();
      this.textBox3 = new TextBox();
      this.textBox4 = new TextBox();
      this.textBox7 = new TextBox();
      this.listBox1 = new ListBox();
      this.comboBox1 = new ComboBox();
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
      this.groupBox1.Controls.Add((Control) this.comboBox1);
      this.groupBox1.Controls.Add((Control) this.button4);
      this.groupBox1.Controls.Add((Control) this.button3);
      this.groupBox1.Controls.Add((Control) this.textBox8);
      this.groupBox1.Controls.Add((Control) this.label4);
      this.groupBox1.Controls.Add((Control) this.button1);
      this.groupBox1.Controls.Add((Control) this.radioButton2);
      this.groupBox1.Controls.Add((Control) this.radioButton1);
      this.groupBox1.Controls.Add((Control) this.textBox6);
      this.groupBox1.Controls.Add((Control) this.textBox5);
      this.groupBox1.Controls.Add((Control) this.label3);
      this.groupBox1.Controls.Add((Control) this.label2);
      this.groupBox1.Controls.Add((Control) this.label1);
      this.groupBox1.Location = new Point(496, 27);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(457, 277);
      this.groupBox1.TabIndex = 2;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Change OX Questions";
      this.button4.BackColor = Color.LightCoral;
      this.button4.FlatStyle = FlatStyle.Flat;
      this.button4.Image = (Image) Resources.delete;
      this.button4.ImageAlign = ContentAlignment.MiddleLeft;
      this.button4.Location = new Point(366, 244);
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
      this.button3.Location = new Point(14, 244);
      this.button3.Name = "button3";
      this.button3.Size = new Size(87, 27);
      this.button3.TabIndex = 11;
      this.button3.Text = "    Add Copy";
      this.button3.UseVisualStyleBackColor = false;
      this.button3.Click += new EventHandler(this.button3_Click);
      this.textBox8.Enabled = false;
      this.textBox8.Location = new Point(128, 10);
      this.textBox8.Name = "textBox8";
      this.textBox8.Size = new Size(49, 20);
      this.textBox8.TabIndex = 10;
      this.label4.AutoSize = true;
      this.label4.Location = new Point(78, 16);
      this.label4.Name = "label4";
      this.label4.Size = new Size(46, 13);
      this.label4.TabIndex = 9;
      this.label4.Text = "Country:";
      this.button1.BackColor = Color.LightCyan;
      this.button1.FlatStyle = FlatStyle.Flat;
      this.button1.Image = (Image) Resources._08;
      this.button1.ImageAlign = ContentAlignment.MiddleLeft;
      this.button1.Location = new Point(107, 244);
      this.button1.Name = "button1";
      this.button1.Size = new Size(72, 27);
      this.button1.TabIndex = 7;
      this.button1.Text = "      Update";
      this.button1.UseVisualStyleBackColor = false;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.radioButton2.AutoSize = true;
      this.radioButton2.Location = new Point(53, 214);
      this.radioButton2.Name = "radioButton2";
      this.radioButton2.Size = new Size(32, 17);
      this.radioButton2.TabIndex = 6;
      this.radioButton2.TabStop = true;
      this.radioButton2.Text = "X";
      this.radioButton2.UseVisualStyleBackColor = true;
      this.radioButton2.CheckedChanged += new EventHandler(this.radioButton2_CheckedChanged);
      this.radioButton1.AutoSize = true;
      this.radioButton1.Location = new Point(14, 214);
      this.radioButton1.Name = "radioButton1";
      this.radioButton1.Size = new Size(33, 17);
      this.radioButton1.TabIndex = 5;
      this.radioButton1.TabStop = true;
      this.radioButton1.Text = "O";
      this.radioButton1.UseVisualStyleBackColor = true;
      this.radioButton1.CheckedChanged += new EventHandler(this.radioButton1_CheckedChanged);
      this.textBox6.Enabled = false;
      this.textBox6.Location = new Point(14, 32);
      this.textBox6.Name = "textBox6";
      this.textBox6.Size = new Size(49, 20);
      this.textBox6.TabIndex = 4;
      this.textBox6.TextChanged += new EventHandler(this.textBox6_TextChanged);
      this.textBox5.Location = new Point(14, 71);
      this.textBox5.Multiline = true;
      this.textBox5.Name = "textBox5";
      this.textBox5.Size = new Size(429, 124);
      this.textBox5.TabIndex = 3;
      this.textBox5.TextChanged += new EventHandler(this.textBox5_TextChanged);
      this.label3.AutoSize = true;
      this.label3.Location = new Point(11, 198);
      this.label3.Name = "label3";
      this.label3.Size = new Size(45, 13);
      this.label3.TabIndex = 2;
      this.label3.Text = "Answer:";
      this.label2.AutoSize = true;
      this.label2.Location = new Point(11, 55);
      this.label2.Name = "label2";
      this.label2.Size = new Size(52, 13);
      this.label2.TabIndex = 1;
      this.label2.Text = "Question:";
      this.label1.AutoSize = true;
      this.label1.Location = new Point(11, 16);
      this.label1.Name = "label1";
      this.label1.Size = new Size(36, 13);
      this.label1.TabIndex = 0;
      this.label1.Text = "Index:";
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
      this.comboBox1.FormattingEnabled = true;
      this.comboBox1.Items.AddRange(new object[9]
      {
        (object) "THA",
        (object) "USA",
        (object) "GER",
        (object) "ESP",
        (object) "BRA",
        (object) "FRA",
        (object) "POL",
        (object) "RUS",
        (object) "MEX"
      });
      this.comboBox1.Location = new Point(81, 32);
      this.comboBox1.Name = "comboBox1";
      this.comboBox1.Size = new Size(121, 21);
      this.comboBox1.TabIndex = 67;
      this.comboBox1.SelectedIndexChanged += new EventHandler(this.comboBox1_SelectedIndexChanged);
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(965, 432);
      this.Controls.Add((Control) this.listBox1);
      this.Controls.Add((Control) this.textBox7);
      this.Controls.Add((Control) this.textBox4);
      this.Controls.Add((Control) this.textBox3);
      this.Controls.Add((Control) this.textBox2);
      this.Controls.Add((Control) this.textBox1);
      this.Controls.Add((Control) this.groupBox1);
      this.Controls.Add((Control) this.menuStrip1);
      this.FormBorderStyle = FormBorderStyle.Fixed3D;
      this.MainMenuStrip = this.menuStrip1;
      this.MaximizeBox = false;
      this.Name = nameof (OX);
      this.Text = "LastChaos OX Quiz Editor";
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
