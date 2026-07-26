// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.OptionEditor
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using MySqlConnector;
using StringExporter;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools
{
  public class OptionEditor : Form
  {
    public static Connection connection = new Connection();
    public static int MaxOptionLevel;
    private string Host = OptionEditor.connection.Settings.SqlHost;
    private string User = OptionEditor.connection.Settings.SqlUser;
    private string Password = OptionEditor.connection.Settings.SqlPassword;
    private string Database = OptionEditor.connection.Settings.SqlDatabase;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    private MessageHandle messageHandle = new MessageHandle();
    public string rowName = "a_index";
    public string[] menuArray = new string[2]
    {
      "a_index",
      "a_name_usa"
    };
    private string language = ItemEditor2.connection.Settings.Language;
    public string[] menuArrayGER = new string[2]
    {
      "a_index",
      "a_name_ger"
    };
    public string[] menuArrayPOL = new string[2]
    {
      "a_index",
      "a_name_pld"
    };
    public string[] menuArrayBRA = new string[2]
    {
      "a_index",
      "a_name_brz"
    };
    public string[] menuArrayRUS = new string[2]
    {
      "a_index",
      "a_name_rus"
    };
    public string[] menuArrayFRA = new string[2]
    {
      "a_index",
      "a_name_frc"
    };
    public string[] menuArrayESP = new string[2]
    {
      "a_index",
      "a_name_spn"
    };
    public string[] menuArrayMEX = new string[2]
    {
      "a_index",
      "a_name_mex"
    };
    public string[] menuArrayTHA = new string[2]
    {
      "a_index",
      "a_name_thai"
    };
    public string[] menuArrayITA = new string[2]
    {
      "a_index",
      "a_name_ita"
    };
    public string[] menuArrayUSA = new string[2]
    {
      "a_index",
      "a_name_usa"
    };
    private string namee;
    private ExportLodHandle exportLodHandle = new ExportLodHandle();
    private IContainer components = (IContainer) null;
    public string name;
    public int index;
    public string test2;
    public List<string> lArrayLevel;
    public List<string> lArrayProb;
    private MenuStrip menuStrip1;
    private ToolStripMenuItem fileExportToolStripMenuItem;
    private ToolStripMenuItem exportlodToolStripMenuItem;
    private GroupBox groupBox3;
    private Button button3;
    private Button button1;
    private ListBox listBox1;
    private GroupBox groupBox1;
    private GroupBox groupBox2;
    private TextBox textBox1;
    private TextBox textBox2;
    private TextBox textBox3;
    private TextBox textBox4;
    private TextBox textBox5;
    private TextBox textBox6;
    private Label label3;
    private Label label2;
    private Label label1;
    private Label label5;
    private Label label4;
    private Label label6;
    private GroupBox groupBox4;
    private DataGridView dgItems;
    private ToolStrip toolStrip2;
    private ToolStripButton btnDeleteSelected;
    private ToolStripSeparator toolStripSeparator1;
    private ToolStripButton btnAddItems;
    private ToolStripSeparator toolStripSeparator6;
    private ToolStripButton toolStripButton1;
    private Button button2;
    private DataGridViewTextBoxColumn ID;
    private DataGridViewTextBoxColumn Count;
    private DataGridViewTextBoxColumn Level;
    private DataGridViewTextBoxColumn Prob;
    private TextBox tbMaxOption;
    private Label label7;
    private ToolStripMenuItem saveToolStripMenuItem;
    private ToolStripMenuItem exportStrOptionlodToolStripMenuItem;

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
      if (this.language == "ESP")
      {
        this.namee = "a_name_spn";
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

    public OptionEditor() => this.InitializeComponent();

    private void LoadListBox()
    {
      if (this.language == "THA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayTHA, this.Host, this.User, this.Password, this.Database, "select * from t_option ORDER BY a_index;");
      else
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, "select * from t_option ORDER BY a_index;");
    }

    private void Exporter_Option_Load(object sender, EventArgs e)
    {
      OptionEditor.MaxOptionLevel = Convert.ToInt32(this.tbMaxOption.Text);
      this.LoadListBox();
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

    private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.namee = this.StringFromLanguage();
      if (this.listBox1.SelectedIndex != -1)
        this.textBox1.Text = this.GetIndex().ToString();
      string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, " select * from t_option WHERE a_index ='" + this.textBox1.Text + "';", new string[6]
      {
        "a_index",
        "a_type",
        this.namee ?? "",
        "a_weapon_type",
        "a_wear_type",
        "a_accessory_type"
      });
      this.textBox1.Text = strArray[0];
      this.textBox2.Text = strArray[1];
      this.textBox3.Text = strArray[2];
      this.textBox4.Text = strArray[3];
      this.textBox5.Text = strArray[4];
      this.textBox6.Text = strArray[5];
      this.dgItems.Rows.Clear();
      this.LoadDG();
    }

    public void LoadDG()
    {
      string str1 = "SELECT a_index, a_level, a_prob FROM t_option WHERE a_index ='" + this.textBox1.Text + "'";
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
        string[] strArray1 = str3.Split(' ');
        string[] strArray2 = str4.Split(' ');
        string[] strArray3 = new string[1000];
        string[] strArray4 = new string[1000];
        int index1 = 0;
        int index2 = 0;
        this.lArrayLevel = new List<string>();
        this.lArrayProb = new List<string>();
        foreach (string str5 in strArray1)
        {
          strArray3[index1] = str5;
          this.lArrayLevel.Add(str5);
          ++index1;
        }
        foreach (string str6 in strArray2)
        {
          strArray4[index2] = str6;
          this.lArrayProb.Add(str6);
          ++index2;
        }
        int count = this.lArrayLevel.Count;
        for (int index3 = 0; index3 < count; ++index3)
          this.dgItems.Rows.Add((object) str2, (object) (index3 + 1), (object) this.lArrayLevel[index3], (object) this.lArrayProb[index3]);
        this.tbMaxOption.Text = Convert.ToString(count);
      }
      mySqlConnection.Close();
    }

    private void btnDeleteSelected_Click(object sender, EventArgs e)
    {
      int index1 = this.dgItems.CurrentRow.Index;
      DataGridViewRow row = this.dgItems.Rows[this.dgItems.CurrentRow.Index];
      string str1 = Convert.ToString(row.Cells["ID"].Value);
      string s = Convert.ToString(row.Cells["Count"].Value);
      string str2 = Convert.ToString(row.Cells["Level"].Value);
      string str3 = Convert.ToString(row.Cells["Prob"].Value);
      int index2 = int.Parse(s) - 1;
      this.lArrayLevel[index2] = str2;
      this.lArrayProb[index2] = str3;
      string str4 = "";
      string str5 = "";
      int count = this.lArrayLevel.Count;
      for (int index3 = 0; index3 < count; ++index3)
      {
        if (index3 == count - 1)
        {
          str4 += this.lArrayLevel[index3].ToString();
          str5 += this.lArrayProb[index3].ToString();
        }
        else
        {
          str4 = str4 + this.lArrayLevel[index3].ToString() + " ";
          str5 = str5 + this.lArrayProb[index3].ToString() + " ";
        }
      }
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_option SET a_level = '" + str4 + "', a_prob = '" + str5 + "' WHERE a_index = '" + str1 + "'");
      this.dgItems.Rows.Clear();
      this.LoadDG();
      try
      {
        this.dgItems.Rows[index1].Selected = true;
        this.dgItems.FirstDisplayedScrollingRowIndex = index1;
      }
      catch
      {
        int num = (int) MessageBox.Show("You must select a Item", "Error");
      }
    }

    private void btnAddItems_Click(object sender, EventArgs e)
    {
      string s = Convert.ToString(this.dgItems.Rows[this.dgItems.CurrentRow.Index].Cells["ID"].Value);
      int.Parse(s);
      string str1 = "";
      string str2 = "";
      int count = this.lArrayLevel.Count;
      for (int index = 0; index < count; ++index)
      {
        str1 = str1 + this.lArrayLevel[index].ToString() + " ";
        str2 = str2 + this.lArrayProb[index].ToString() + " ";
      }
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_option SET a_level = '" + str1 + "0', a_prob = '" + str2 + "0' WHERE a_index = '" + s + "'");
      this.dgItems.Rows.Clear();
      this.LoadDG();
      int index1 = this.dgItems.Rows.Count - 1;
      this.dgItems.Rows[index1].Selected = true;
      this.dgItems.FirstDisplayedScrollingRowIndex = index1;
    }

    private void toolStripButton1_Click(object sender, EventArgs e)
    {
      int index1 = this.dgItems.CurrentRow.Index - 1;
      DataGridViewRow row = this.dgItems.Rows[this.dgItems.CurrentRow.Index];
      string str1 = Convert.ToString(row.Cells["ID"].Value);
      string s = Convert.ToString(row.Cells["Count"].Value);
      string str2 = Convert.ToString(row.Cells["Level"].Value);
      string str3 = Convert.ToString(row.Cells["Prob"].Value);
      int index2 = int.Parse(s) - 1;
      this.lArrayLevel[index2] = str2;
      this.lArrayProb[index2] = str3;
      this.lArrayLevel.RemoveAt(index2);
      this.lArrayProb.RemoveAt(index2);
      string str4 = "";
      string str5 = "";
      int count = this.lArrayLevel.Count;
      for (int index3 = 0; index3 < count; ++index3)
      {
        if (index3 == count - 1)
        {
          str4 += this.lArrayLevel[index3].ToString();
          str5 += this.lArrayProb[index3].ToString();
        }
        else
        {
          str4 = str4 + this.lArrayLevel[index3].ToString() + " ";
          str5 = str5 + this.lArrayProb[index3].ToString() + " ";
        }
      }
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_option SET a_level = '" + str4 + "', a_prob = '" + str5 + "' WHERE a_index = '" + str1 + "'");
      this.dgItems.Rows.Clear();
      this.LoadDG();
      try
      {
        this.dgItems.Rows[index1].Selected = true;
        this.dgItems.FirstDisplayedScrollingRowIndex = index1;
      }
      catch
      {
        int num = (int) MessageBox.Show("You must select a Item", "Error");
      }
    }

    private void button2_Click(object sender, EventArgs e)
    {
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_option SET a_type = '" + this.textBox2.Text + "', " + this.namee + " = '" + this.textBox3.Text + "', a_weapon_type = '" + this.textBox4.Text + "', a_wear_type = '" + this.textBox5.Text + "', a_accessory_type = '" + this.textBox6.Text + "' WHERE a_index = '" + this.textBox1.Text + "'");
      int selectedIndex = this.listBox1.SelectedIndex;
      this.LoadListBox();
      this.listBox1.SelectedIndex = selectedIndex;
    }

    private void button1_Click(object sender, EventArgs e)
    {
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_option (a_level, a_prob) VALUES('0','0')");
      this.LoadListBox();
      this.listBox1.SelectedIndex = this.listBox1.Items.Count - 1;
    }

    private void button3_Click(object sender, EventArgs e)
    {
      int selectedIndex = this.listBox1.SelectedIndex;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_option WHERE a_index = '" + this.textBox1.Text + "'");
      this.LoadListBox();
      this.listBox1.SelectedIndex = selectedIndex - 1;
    }

    private void exportlodToolStripMenuItem_Click(object sender, EventArgs e)
    {
      this.ExportOption_New();
    }

    public void ExportOption_New()
    {
      SaveFileDialog saveFileDialog = new SaveFileDialog();
      saveFileDialog.Filter = "File option.lod|option*.lod";
      saveFileDialog.FileName = "option.lod";
      saveFileDialog.Title = "Save option.lod file";
      if (saveFileDialog.ShowDialog() != DialogResult.OK)
        return;
      BinaryWriter binaryWriter = new BinaryWriter((Stream) File.Create(saveFileDialog.FileName));
      int num1 = this.databaseHandle.CountByRow(this.Host, this.User, this.Password, this.Database, "SELECT COUNT(*) FROM t_option");
      string str1 = "SELECT * FROM t_option ORDER BY a_index";
      MySqlConnection mySqlConnection = new MySqlConnection("datasource=" + this.Host + ";Port=3306;User ID="  + this.User + ";Password=" + this.Password + ";Database=" + this.Database + ";Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;");
      MySqlCommand command = mySqlConnection.CreateCommand();
      command.CommandText = str1;
      mySqlConnection.Open();
      MySqlDataReader mySqlDataReader = command.ExecuteReader();
      binaryWriter.Write(num1);
      while (mySqlDataReader.Read())
      {
        int ordinal1 = mySqlDataReader.GetOrdinal("a_index");
        string s1 = mySqlDataReader.GetString(ordinal1);
        binaryWriter.Write(int.Parse(s1));
        int ordinal2 = mySqlDataReader.GetOrdinal("a_type");
        string s2 = mySqlDataReader.GetString(ordinal2);
        binaryWriter.Write(int.Parse(s2));
        int ordinal3 = mySqlDataReader.GetOrdinal("a_level");
        string[] strArray = mySqlDataReader.GetString(ordinal3).Split(' ');
        int int32 = Convert.ToInt32(this.tbMaxOption.Text);
        int[] numArray = new int[int32];
        int index1 = 0;
        foreach (string str2 in strArray)
        {
          if (str2 != "")
          {
            numArray[index1] = Convert.ToInt32(str2);
            ++index1;
          }
        }
        int num2 = int32;
        for (int index2 = 0; index2 < num2; ++index2)
          binaryWriter.Write(numArray[index2]);
      }
      mySqlConnection.Close();
      binaryWriter.Close();
      this.messageHandle.SuccessFileMessage();
    }

    private void exportStrOptionlodToolStripMenuItem_Click(object sender, EventArgs e)
    {
      new FormExport().Show();
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (OptionEditor));
      this.menuStrip1 = new MenuStrip();
      this.fileExportToolStripMenuItem = new ToolStripMenuItem();
      this.exportlodToolStripMenuItem = new ToolStripMenuItem();
      this.exportStrOptionlodToolStripMenuItem = new ToolStripMenuItem();
      this.saveToolStripMenuItem = new ToolStripMenuItem();
      this.groupBox3 = new GroupBox();
      this.button3 = new Button();
      this.button1 = new Button();
      this.listBox1 = new ListBox();
      this.groupBox1 = new GroupBox();
      this.label3 = new Label();
      this.label2 = new Label();
      this.label1 = new Label();
      this.textBox3 = new TextBox();
      this.textBox1 = new TextBox();
      this.textBox2 = new TextBox();
      this.groupBox2 = new GroupBox();
      this.textBox6 = new TextBox();
      this.label6 = new Label();
      this.textBox5 = new TextBox();
      this.label5 = new Label();
      this.textBox4 = new TextBox();
      this.label4 = new Label();
      this.groupBox4 = new GroupBox();
      this.dgItems = new DataGridView();
      this.ID = new DataGridViewTextBoxColumn();
      this.Count = new DataGridViewTextBoxColumn();
      this.Level = new DataGridViewTextBoxColumn();
      this.Prob = new DataGridViewTextBoxColumn();
      this.toolStrip2 = new ToolStrip();
      this.btnDeleteSelected = new ToolStripButton();
      this.toolStripSeparator1 = new ToolStripSeparator();
      this.btnAddItems = new ToolStripButton();
      this.toolStripSeparator6 = new ToolStripSeparator();
      this.toolStripButton1 = new ToolStripButton();
      this.button2 = new Button();
      this.tbMaxOption = new TextBox();
      this.label7 = new Label();
      this.menuStrip1.SuspendLayout();
      this.groupBox3.SuspendLayout();
      this.groupBox1.SuspendLayout();
      this.groupBox2.SuspendLayout();
      this.groupBox4.SuspendLayout();
      ((ISupportInitialize) this.dgItems).BeginInit();
      this.toolStrip2.SuspendLayout();
      this.SuspendLayout();
      this.menuStrip1.AllowMerge = false;
      this.menuStrip1.BackColor = SystemColors.ButtonHighlight;
      this.menuStrip1.ImageScalingSize = new Size(20, 20);
      this.menuStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.fileExportToolStripMenuItem
      });
      this.menuStrip1.Location = new Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new Size(800, 28);
      this.menuStrip1.TabIndex = 0;
      this.menuStrip1.Text = "menuStrip1";
      this.fileExportToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[3]
      {
        (ToolStripItem) this.exportlodToolStripMenuItem,
        (ToolStripItem) this.exportStrOptionlodToolStripMenuItem,
        (ToolStripItem) this.saveToolStripMenuItem
      });
      this.fileExportToolStripMenuItem.Name = "fileExportToolStripMenuItem";
      this.fileExportToolStripMenuItem.Size = new Size(93, 24);
      this.fileExportToolStripMenuItem.Text = "File Export";
      this.exportlodToolStripMenuItem.Name = "exportlodToolStripMenuItem";
      this.exportlodToolStripMenuItem.Size = new Size(226, 26);
      this.exportlodToolStripMenuItem.Text = "Export option.lod";
      this.exportlodToolStripMenuItem.Click += new EventHandler(this.exportlodToolStripMenuItem_Click);
      this.exportStrOptionlodToolStripMenuItem.Name = "exportStrOptionlodToolStripMenuItem";
      this.exportStrOptionlodToolStripMenuItem.Size = new Size(226, 26);
      this.exportStrOptionlodToolStripMenuItem.Text = "Export strOption.lod";
      this.exportStrOptionlodToolStripMenuItem.Click += new EventHandler(this.exportStrOptionlodToolStripMenuItem_Click);
      this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
      this.saveToolStripMenuItem.Size = new Size(226, 26);
      this.saveToolStripMenuItem.Text = "Save";
      this.saveToolStripMenuItem.Click += new EventHandler(this.saveToolStripMenuItem_Click);
      this.groupBox3.Controls.Add((Control) this.button3);
      this.groupBox3.Controls.Add((Control) this.button1);
      this.groupBox3.Controls.Add((Control) this.listBox1);
      this.groupBox3.Location = new Point(12, 27);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Size = new Size(237, 475);
      this.groupBox3.TabIndex = 32;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "Options";
      this.button3.FlatStyle = FlatStyle.Flat;
      this.button3.Location = new Point(131, 446);
      this.button3.Name = "button3";
      this.button3.Size = new Size(100, 23);
      this.button3.TabIndex = 4;
      this.button3.Text = "Delete";
      this.button3.UseVisualStyleBackColor = true;
      this.button3.Click += new EventHandler(this.button3_Click);
      this.button1.FlatStyle = FlatStyle.Flat;
      this.button1.Location = new Point(6, 446);
      this.button1.Name = "button1";
      this.button1.Size = new Size(100, 23);
      this.button1.TabIndex = 2;
      this.button1.Text = "Add";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.listBox1.FormattingEnabled = true;
      this.listBox1.ItemHeight = 16;
      this.listBox1.Location = new Point(6, 14);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new Size(225, 420);
      this.listBox1.TabIndex = 1;
      this.listBox1.SelectedIndexChanged += new EventHandler(this.listBox1_SelectedIndexChanged);
      this.groupBox1.Controls.Add((Control) this.label3);
      this.groupBox1.Controls.Add((Control) this.label2);
      this.groupBox1.Controls.Add((Control) this.label1);
      this.groupBox1.Controls.Add((Control) this.textBox3);
      this.groupBox1.Controls.Add((Control) this.textBox1);
      this.groupBox1.Controls.Add((Control) this.textBox2);
      this.groupBox1.Location = new Point((int) byte.MaxValue, 27);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(264, 80);
      this.groupBox1.TabIndex = 33;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Main";
      this.label3.AutoSize = true;
      this.label3.Location = new Point(6, 51);
      this.label3.Name = "label3";
      this.label3.Size = new Size(49, 17);
      this.label3.TabIndex = 41;
      this.label3.Text = "Name:";
      this.label2.AutoSize = true;
      this.label2.Location = new Point(111, 21);
      this.label2.Name = "label2";
      this.label2.Size = new Size(44, 17);
      this.label2.TabIndex = 39;
      this.label2.Text = "Type:";
      this.label1.AutoSize = true;
      this.label1.Location = new Point(6, 21);
      this.label1.Name = "label1";
      this.label1.Size = new Size(45, 17);
      this.label1.TabIndex = 38;
      this.label1.Text = "Index:";
      this.textBox3.BorderStyle = BorderStyle.FixedSingle;
      this.textBox3.Location = new Point(48, 49);
      this.textBox3.Name = "textBox3";
      this.textBox3.Size = new Size(210, 22);
      this.textBox3.TabIndex = 37;
      this.textBox1.BorderStyle = BorderStyle.FixedSingle;
      this.textBox1.Location = new Point(48, 19);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(41, 22);
      this.textBox1.TabIndex = 35;
      this.textBox2.BorderStyle = BorderStyle.FixedSingle;
      this.textBox2.Location = new Point(151, 19);
      this.textBox2.Name = "textBox2";
      this.textBox2.Size = new Size(41, 22);
      this.textBox2.TabIndex = 36;
      this.groupBox2.Controls.Add((Control) this.textBox6);
      this.groupBox2.Controls.Add((Control) this.label6);
      this.groupBox2.Controls.Add((Control) this.textBox5);
      this.groupBox2.Controls.Add((Control) this.label5);
      this.groupBox2.Controls.Add((Control) this.textBox4);
      this.groupBox2.Controls.Add((Control) this.label4);
      this.groupBox2.Location = new Point(525, 27);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new Size(261, 80);
      this.groupBox2.TabIndex = 34;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "Type";
      this.textBox6.BorderStyle = BorderStyle.FixedSingle;
      this.textBox6.Location = new Point(87, 49);
      this.textBox6.Name = "textBox6";
      this.textBox6.Size = new Size(44, 22);
      this.textBox6.TabIndex = 40;
      this.label6.AutoSize = true;
      this.label6.Location = new Point(6, 51);
      this.label6.Name = "label6";
      this.label6.Size = new Size(109, 17);
      this.label6.TabIndex = 43;
      this.label6.Text = "AccessoryType:";
      this.textBox5.BorderStyle = BorderStyle.FixedSingle;
      this.textBox5.Location = new Point(211, 19);
      this.textBox5.Name = "textBox5";
      this.textBox5.Size = new Size(44, 22);
      this.textBox5.TabIndex = 39;
      this.label5.AutoSize = true;
      this.label5.Location = new Point(145, 21);
      this.label5.Name = "label5";
      this.label5.Size = new Size(78, 17);
      this.label5.TabIndex = 42;
      this.label5.Text = "WearType:";
      this.textBox4.BorderStyle = BorderStyle.FixedSingle;
      this.textBox4.Location = new Point(87, 19);
      this.textBox4.Name = "textBox4";
      this.textBox4.Size = new Size(44, 22);
      this.textBox4.TabIndex = 38;
      this.label4.AutoSize = true;
      this.label4.Location = new Point(6, 21);
      this.label4.Name = "label4";
      this.label4.Size = new Size(97, 17);
      this.label4.TabIndex = 41;
      this.label4.Text = "WeaponType:";
      this.groupBox4.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left;
      this.groupBox4.Controls.Add((Control) this.dgItems);
      this.groupBox4.Controls.Add((Control) this.toolStrip2);
      this.groupBox4.Location = new Point((int) byte.MaxValue, 113);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Size = new Size(531, 348);
      this.groupBox4.TabIndex = 44;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "Seals";
      this.dgItems.AllowUserToAddRows = false;
      this.dgItems.AllowUserToDeleteRows = false;
      this.dgItems.BackgroundColor = SystemColors.Control;
      this.dgItems.BorderStyle = BorderStyle.None;
      this.dgItems.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dgItems.Columns.AddRange((DataGridViewColumn) this.ID, (DataGridViewColumn) this.Count, (DataGridViewColumn) this.Level, (DataGridViewColumn) this.Prob);
      this.dgItems.Dock = DockStyle.Fill;
      this.dgItems.EnableHeadersVisualStyles = false;
      this.dgItems.Location = new Point(3, 18);
      this.dgItems.Name = "dgItems";
      this.dgItems.RowHeadersVisible = false;
      this.dgItems.RowHeadersWidth = 51;
      this.dgItems.RowTemplate.Height = 25;
      this.dgItems.Size = new Size(525, 300);
      this.dgItems.TabIndex = 0;
      this.ID.HeaderText = "ID";
      this.ID.MinimumWidth = 6;
      this.ID.Name = "ID";
      this.ID.Visible = false;
      this.ID.Width = 60;
      this.Count.HeaderText = "Level";
      this.Count.MinimumWidth = 6;
      this.Count.Name = "Count";
      this.Count.Width = 50;
      this.Level.HeaderText = "Value";
      this.Level.MinimumWidth = 6;
      this.Level.Name = "Level";
      this.Level.Width = 225;
      this.Prob.HeaderText = "Prob";
      this.Prob.MinimumWidth = 6;
      this.Prob.Name = "Prob";
      this.Prob.Width = 225;
      this.toolStrip2.Dock = DockStyle.Bottom;
      this.toolStrip2.GripStyle = ToolStripGripStyle.Hidden;
      this.toolStrip2.ImageScalingSize = new Size(20, 20);
      this.toolStrip2.Items.AddRange(new ToolStripItem[5]
      {
        (ToolStripItem) this.btnDeleteSelected,
        (ToolStripItem) this.toolStripSeparator1,
        (ToolStripItem) this.btnAddItems,
        (ToolStripItem) this.toolStripSeparator6,
        (ToolStripItem) this.toolStripButton1
      });
      this.toolStrip2.Location = new Point(3, 318);
      this.toolStrip2.Name = "toolStrip2";
      this.toolStrip2.Size = new Size(525, 27);
      this.toolStrip2.TabIndex = 1;
      this.toolStrip2.Text = "toolStrip2";
      this.btnDeleteSelected.DisplayStyle = ToolStripItemDisplayStyle.Text;
      this.btnDeleteSelected.ImageTransparentColor = Color.Magenta;
      this.btnDeleteSelected.Name = "btnDeleteSelected";
      this.btnDeleteSelected.Size = new Size(82, 24);
      this.btnDeleteSelected.Text = "Save Level";
      this.btnDeleteSelected.Click += new EventHandler(this.btnDeleteSelected_Click);
      this.toolStripSeparator1.Name = "toolStripSeparator1";
      this.toolStripSeparator1.Size = new Size(6, 27);
      this.btnAddItems.DisplayStyle = ToolStripItemDisplayStyle.Text;
      this.btnAddItems.ImageTransparentColor = Color.Magenta;
      this.btnAddItems.Name = "btnAddItems";
      this.btnAddItems.Size = new Size(79, 24);
      this.btnAddItems.Text = "Add Level";
      this.btnAddItems.Click += new EventHandler(this.btnAddItems_Click);
      this.toolStripSeparator6.Name = "toolStripSeparator6";
      this.toolStripSeparator6.Size = new Size(6, 27);
      this.toolStripButton1.DisplayStyle = ToolStripItemDisplayStyle.Text;
      this.toolStripButton1.ImageTransparentColor = Color.Magenta;
      this.toolStripButton1.Name = "toolStripButton1";
      this.toolStripButton1.Size = new Size(118, 24);
      this.toolStripButton1.Text = "Delete Selected";
      this.toolStripButton1.Click += new EventHandler(this.toolStripButton1_Click);
      this.button2.FlatStyle = FlatStyle.Flat;
      this.button2.Location = new Point(686, 473);
      this.button2.Name = "button2";
      this.button2.Size = new Size(100, 23);
      this.button2.TabIndex = 45;
      this.button2.Text = "Save";
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.tbMaxOption.BorderStyle = BorderStyle.FixedSingle;
      this.tbMaxOption.Location = new Point(758, 1);
      this.tbMaxOption.Name = "tbMaxOption";
      this.tbMaxOption.Size = new Size(41, 22);
      this.tbMaxOption.TabIndex = 46;
      this.tbMaxOption.Text = "36";
      this.tbMaxOption.TextAlign = HorizontalAlignment.Center;
      this.tbMaxOption.TextChanged += new EventHandler(this.tbMaxOption_TextChanged);
      this.label7.AutoSize = true;
      this.label7.BackColor = SystemColors.ButtonHighlight;
      this.label7.Location = new Point(609, 4);
      this.label7.Name = "label7";
      this.label7.Size = new Size(121, 17);
      this.label7.TabIndex = 47;
      this.label7.Text = "Max Option Level:";
      this.ClientSize = new Size(800, 512);
      this.Controls.Add((Control) this.label7);
      this.Controls.Add((Control) this.tbMaxOption);
      this.Controls.Add((Control) this.button2);
      this.Controls.Add((Control) this.groupBox4);
      this.Controls.Add((Control) this.groupBox2);
      this.Controls.Add((Control) this.groupBox1);
      this.Controls.Add((Control) this.groupBox3);
      this.Controls.Add((Control) this.menuStrip1);
      this.Icon = (Icon) componentResourceManager.GetObject("$this.Icon");
      this.MainMenuStrip = this.menuStrip1;
      this.Name = nameof (OptionEditor);
      this.Text = "Option Editor";
      this.Load += new EventHandler(this.Exporter_Option_Load);
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
      this.ResumeLayout(false);
      this.PerformLayout();
    }

    private void tbMaxOption_TextChanged(object sender, EventArgs e)
    {
      OptionEditor.MaxOptionLevel = Convert.ToInt32(this.tbMaxOption.Text);
    }

    private void saveToolStripMenuItem_Click(object sender, EventArgs e)
    {
      this.exportLodHandle.ExportOption_V4();
    }
  }
}
