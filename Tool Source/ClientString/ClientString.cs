// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.ClientString.ClientStringTool
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
namespace LcDevPack_TeamDamonA.ClientString
{
  public class ClientStringTool : Form
  {
    public static Connection connection = new Connection();
    private string Host => ClientStringTool.connection.Settings.SqlHost;
    private string User => ClientStringTool.connection.Settings.SqlUser;
    private string Password => ClientStringTool.connection.Settings.SqlPassword;
        private string Database => ClientStringTool.connection.Settings.SqlDatabase;
        private DatabaseHandle databaseHandle = new DatabaseHandle();
        public string _ClientPath => ClientStringTool.connection.Settings.ClientPath;
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
    private TextBox textBox6;
    private TextBox textBox5;
    private Label label2;
    private Label label1;
    private ListBox listBox1;
    private Button button3;
    private Button button4;
    private string country;
    public static string namee;
    private string language => ClientStringTool.connection.Settings.Language;

    public string[] menuArray = new string[2]
    {
      "a_index",
      "a_string"
    };
    public string[] menuArrayGER = new string[2]
    {
      "a_index",
      "a_string_ger"
    };
    public string[] menuArrayPOL = new string[2]
    {
      "a_index",
      "a_string_pld"
    };
    public string[] menuArrayBRA = new string[2]
    {
      "a_index",
      "a_string_brz"
    };
    public string[] menuArrayRUS = new string[2]
    {
      "a_index",
      "a_string_rus"
    };
    public string[] menuArrayFRA = new string[2]
    {
      "a_index",
      "a_string_frc"
    };
    public string[] menuArrayESP = new string[2]
    {
      "a_index",
      "a_string_spn"
    };
    public string[] menuArrayMEX = new string[2]
    {
      "a_index",
      "a_string_mex"
    };
    public string[] menuArrayTHA = new string[2]
    {
      "a_index",
      "a_string_thai"
    };
    public string[] menuArrayITA = new string[2]
    {
      "a_index",
      "a_string_ita"
    };
    private Button button2;
    private GroupBox groupBox5;
    private TextBox textBox1;
    private Label label7;
    private GroupBox groupBox2;
    public string[] menuArrayUSA = new string[2]
    {
      "a_index",
      "a_string_usa"
    };

    public ClientStringTool()
    {
      this.InitializeComponent();
      this.LoadListBox();
    }

    private string StringFromLanguage()
    {
      if (this.language == "GER")
      {
        ClientStringTool.namee = "a_string_ger";
        return ClientStringTool.namee;
      }
      if (this.language == "POL")
      {
        ClientStringTool.namee = "a_string_pld";
        return ClientStringTool.namee;
      }
      if (this.language == "BRA")
      {
        ClientStringTool.namee = "a_string_brz";
        return ClientStringTool.namee;
      }
      if (this.language == "RUS")
      {
        ClientStringTool.namee = "a_string_rus";
        return ClientStringTool.namee;
      }
      if (this.language == "FRA")
      {
        ClientStringTool.namee = "a_string_frc";
        return ClientStringTool.namee;
      }
      if (this.language == "ESP")
      {
        ClientStringTool.namee = "a_string_spn";
        return ClientStringTool.namee;
      }
      if (this.language == "MEX")
      {
        ClientStringTool.namee = "a_string_mex";
        return ClientStringTool.namee;
      }
      if (this.language == "THA")
      {
        ClientStringTool.namee = "a_string_thai";
        return ClientStringTool.namee;
      }
      if (this.language == "ITA")
      {
        ClientStringTool.namee = "a_string_ita";
        return ClientStringTool.namee;
      }
      if (!(this.language == "USA"))
        return (string) null;
      ClientStringTool.namee = "a_string_usa";
      return ClientStringTool.namee;
    }

    public void SearchList(string searchString)
    {
      ClientStringTool.namee = this.StringFromLanguage();
      string Query = "select a_index, " + ClientStringTool.namee + " from t_string WHERE " + ClientStringTool.namee + " LIKE '%" + searchString + "%' ORDER BY a_index;";
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
      ClientStringTool.namee = this.StringFromLanguage();
      string Query = "SELECT a_index, " + ClientStringTool.namee + " FROM t_string ORDER BY a_index;";
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
      ClientStringTool.namee = this.StringFromLanguage();
      this.ClearBox();
      if (this.listBox1.SelectedIndex != -1)
        this.textBox6.Text = this.GetIndex().ToString();
      string Query = "select a_index, " + ClientStringTool.namee + " FROM t_string WHERE a_index ='" + this.textBox6.Text + "';";
      string[] rows = new string[2]
      {
        "a_index",
        ClientStringTool.namee
      };
      Query.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'");
      string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query, rows);
      this.textBox6.Text = strArray[0];
      this.textBox5.Text = strArray[1];
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
      ClientStringTool.namee = this.StringFromLanguage();
      this.textBox5.Text.Replace("'", "\\'").Replace("\"", "\\\"");
      string str = this.textBox5.Text.Replace("'", "\\'").Replace("\"", "\\\"");
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_string SET " + ClientStringTool.namee + "  = '" + str + "' WHERE a_index = '" + this.textBox6.Text + "'");
      int num = (int) MessageBox.Show("Update", "Completed", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
      int selectedIndex = this.listBox1.SelectedIndex;
      if (this.textBox1.Text != "")
        this.SearchList(this.textBox1.Text);
      else
        this.LoadListBox();
      this.listBox1.SelectedIndex = selectedIndex;
    }

    private void button2_Click(object sender, EventArgs e)
    {
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_string (" + ClientStringTool.namee + ") VALUES ('New String')");
      this.LoadListBox();
      this.listBox1.SelectedIndex = this.listBox1.Items.Count - 1;
    }

    private void button3_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want copy to New Index " + this.textBox6.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      if (this.textBox5.Text.Trim().Length <= 0)
      {
        int num1 = (int) MessageBox.Show("please add Data", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DROP TABLE IF EXISTS tempTable;CREATE TEMPORARY TABLE tempTable ENGINE=MEMORY SELECT * FROM t_string WHERE a_index=" + this.textBox6.Text + ";SELECT a_index FROM tempTable;UPDATE tempTable SET a_index=(SELECT a_index from t_string ORDER BY a_index DESC LIMIT 1)+1; SELECT a_index FROM tempTable;INSERT INTO t_string SELECT * FROM tempTable;");
        int num2 = (int) MessageBox.Show("Successful copy", "Completed", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
        this.LoadListBox();
        this.listBox1.SelectedIndex = this.listBox1.Items.Count - 1;
      }
    }

    private void button4_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want to Delete String " + this.textBox6.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      int selectedIndex = this.listBox1.SelectedIndex;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_string WHERE a_index = '" + this.textBox6.Text + "'");
      this.LoadListBox();
      this.listBox1.SelectedIndex = selectedIndex - 1;
    }

    public bool SearchString(string s) => s.ToUpper().Contains(this.textBox1.Text.ToUpper());

    private void textBox1_TextChanged(object sender, EventArgs e)
    {
      this.MenuListSearch = this.MenuList.FindAll(new Predicate<string>(this.SearchString));
      this.listBox1.DataSource = (object) this.MenuListSearch;
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
      this.button2 = new Button();
      this.button4 = new Button();
      this.button3 = new Button();
      this.button1 = new Button();
      this.textBox6 = new TextBox();
      this.textBox5 = new TextBox();
      this.label2 = new Label();
      this.label1 = new Label();
      this.listBox1 = new ListBox();
      this.groupBox5 = new GroupBox();
      this.textBox1 = new TextBox();
      this.label7 = new Label();
      this.groupBox2 = new GroupBox();
      this.groupBox1.SuspendLayout();
      this.groupBox5.SuspendLayout();
      this.groupBox2.SuspendLayout();
      this.SuspendLayout();
      this.groupBox1.Controls.Add((Control) this.button2);
      this.groupBox1.Controls.Add((Control) this.button4);
      this.groupBox1.Controls.Add((Control) this.button3);
      this.groupBox1.Controls.Add((Control) this.button1);
      this.groupBox1.Controls.Add((Control) this.textBox6);
      this.groupBox1.Controls.Add((Control) this.textBox5);
      this.groupBox1.Controls.Add((Control) this.label2);
      this.groupBox1.Controls.Add((Control) this.label1);
      this.groupBox1.Location = new Point(12, 314);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(478, 116);
      this.groupBox1.TabIndex = 2;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "String Edit";
      this.button2.BackColor = Color.Gold;
      this.button2.FlatStyle = FlatStyle.Flat;
      this.button2.Image = (Image) Resources.control_add_blue;
      this.button2.ImageAlign = ContentAlignment.MiddleLeft;
      this.button2.Location = new Point(11, 73);
      this.button2.Name = "button2";
      this.button2.Size = new Size(77, 27);
      this.button2.TabIndex = 67;
      this.button2.Text = "    Add";
      this.button2.UseVisualStyleBackColor = false;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.button4.BackColor = Color.LightCoral;
      this.button4.FlatStyle = FlatStyle.Flat;
      this.button4.Image = (Image) Resources.delete;
      this.button4.ImageAlign = ContentAlignment.MiddleLeft;
      this.button4.Location = new Point(355, 73);
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
      this.button3.Location = new Point(94, 73);
      this.button3.Name = "button3";
      this.button3.Size = new Size(87, 27);
      this.button3.TabIndex = 11;
      this.button3.Text = "    Add Copy";
      this.button3.UseVisualStyleBackColor = false;
      this.button3.Click += new EventHandler(this.button3_Click);
      this.button1.BackColor = Color.LightCyan;
      this.button1.FlatStyle = FlatStyle.Flat;
      this.button1.Image = (Image) Resources._08;
      this.button1.ImageAlign = ContentAlignment.MiddleLeft;
      this.button1.Location = new Point(187, 73);
      this.button1.Name = "button1";
      this.button1.Size = new Size(72, 27);
      this.button1.TabIndex = 7;
      this.button1.Text = "      Save";
      this.button1.UseVisualStyleBackColor = false;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.textBox6.Enabled = false;
      this.textBox6.Location = new Point(14, 32);
      this.textBox6.Name = "textBox6";
      this.textBox6.Size = new Size(49, 20);
      this.textBox6.TabIndex = 4;
      this.textBox6.TextChanged += new EventHandler(this.textBox6_TextChanged);
      this.textBox5.Location = new Point(78, 32);
      this.textBox5.Name = "textBox5";
      this.textBox5.Size = new Size(383, 20);
      this.textBox5.TabIndex = 3;
      this.textBox5.TextChanged += new EventHandler(this.textBox5_TextChanged);
      this.label2.AutoSize = true;
      this.label2.Location = new Point(75, 16);
      this.label2.Name = "label2";
      this.label2.Size = new Size(37, 13);
      this.label2.TabIndex = 1;
      this.label2.Text = "String:";
      this.label1.AutoSize = true;
      this.label1.Location = new Point(11, 16);
      this.label1.Name = "label1";
      this.label1.Size = new Size(36, 13);
      this.label1.TabIndex = 0;
      this.label1.Text = "Index:";
      this.listBox1.FormattingEnabled = true;
      this.listBox1.Location = new Point(6, 17);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new Size(467, 212);
      this.listBox1.TabIndex = 7;
      this.listBox1.SelectedIndexChanged += new EventHandler(this.listBox1_SelectedIndexChanged);
      this.groupBox5.Controls.Add((Control) this.textBox1);
      this.groupBox5.Controls.Add((Control) this.label7);
      this.groupBox5.Location = new Point(12, 12);
      this.groupBox5.Name = "groupBox5";
      this.groupBox5.Size = new Size(267, 49);
      this.groupBox5.TabIndex = 33;
      this.groupBox5.TabStop = false;
      this.groupBox5.Text = "Search";
      this.textBox1.BorderStyle = BorderStyle.FixedSingle;
      this.textBox1.Location = new Point(43, 19);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(216, 20);
      this.textBox1.TabIndex = 83;
      this.textBox1.TextChanged += new EventHandler(this.textBox1_TextChanged);
      this.label7.AutoSize = true;
      this.label7.Location = new Point(6, 21);
      this.label7.Name = "label7";
      this.label7.Size = new Size(31, 13);
      this.label7.TabIndex = 21;
      this.label7.Text = "Text:";
      this.groupBox2.Controls.Add((Control) this.listBox1);
      this.groupBox2.Location = new Point(12, 67);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new Size(478, 241);
      this.groupBox2.TabIndex = 34;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "String";
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(498, 432);
      this.Controls.Add((Control) this.groupBox2);
      this.Controls.Add((Control) this.groupBox5);
      this.Controls.Add((Control) this.groupBox1);
      this.FormBorderStyle = FormBorderStyle.Fixed3D;
      this.MaximizeBox = false;
      this.Name = nameof (ClientStringTool);
      this.Text = "LastChaos Client String Editor";
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.groupBox5.ResumeLayout(false);
      this.groupBox5.PerformLayout();
      this.groupBox2.ResumeLayout(false);
      this.ResumeLayout(false);
    }
  }
}
