// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.SetItem.SetitemEditor
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using MySqlConnector;
using StringExporter;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.SetItem
{
  public class SetitemEditor : Form
  {
    public static Connection connection = new Connection();
    public static int MaxOptionLevel;
    private string Host = SetitemEditor.connection.Settings.SqlHost;
    private string User = SetitemEditor.connection.Settings.SqlUser;
    private string Password = SetitemEditor.connection.Settings.SqlPassword;
    private string Database = SetitemEditor.connection.Settings.SqlDatabase;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    public string rowName = "a_set_idx";
    public string[] menuArray = new string[2]
    {
      "a_set_idx",
      "a_set_name_usa"
    };
    private string language = ItemEditor2.connection.Settings.Language;
    public string[] menuArrayGER = new string[2]
    {
      "a_set_idx",
      "a_set_name_ger"
    };
    public string[] menuArrayPOL = new string[2]
    {
      "a_set_idx",
      "a_set_name_pld"
    };
    public string[] menuArrayBRA = new string[2]
    {
      "a_set_idx",
      "a_set_name_brz"
    };
    public string[] menuArrayRUS = new string[2]
    {
      "a_set_idx",
      "a_set_name_rus"
    };
    public string[] menuArrayFRA = new string[2]
    {
      "a_set_idx",
      "a_set_name_frc"
    };
    public string[] menuArrayESP = new string[2]
    {
      "a_set_idx",
      "a_set_name_spn"
    };
    public string[] menuArrayMEX = new string[2]
    {
      "a_set_idx",
      "a_set_name_mex"
    };
    public string[] menuArrayTHA = new string[2]
    {
      "a_set_idx",
      "a_set_name_thai"
    };
    public string[] menuArrayITA = new string[2]
    {
      "a_set_idx",
      "a_set_name_ita"
    };
    public string[] menuArrayUSA = new string[2]
    {
      "a_set_idx",
      "a_set_name_usa"
    };
    private GroupBox groupBox5;
    private DataGridView dgOption;
    private ToolStrip toolStrip1;
    private ToolStripButton BtnSaveOption;
    private ToolStripSeparator toolStripSeparator2;
    private ToolStripSeparator toolStripSeparator3;
    private ToolStripButton BtnDeleteOption;
    private DataGridViewTextBoxColumn ID;
    private DataGridViewTextBoxColumn Type;
    private DataGridViewTextBoxColumn ItemType;
    private DataGridViewImageColumn Icon;
    private DataGridViewTextBoxColumn ItemID;
    private DataGridViewTextBoxColumn ItemName;
    private DataGridViewTextBoxColumn OldItem;
    private DataGridViewTextBoxColumn SetID;
    private DataGridViewTextBoxColumn OptionIndex;
    private DataGridViewTextBoxColumn Parts;
    private DataGridViewTextBoxColumn OptionType;
    private DataGridViewTextBoxColumn OptionSkillID;
    private DataGridViewTextBoxColumn Level;
    private DataGridViewTextBoxColumn OptionSkillName;
    private DataGridViewTextBoxColumn OptionCount;
    private DataGridViewImageColumn dataGridViewImageColumn1;
    private CheckBox cbEnabled;
    private Label label6;
    private Label label7;
    private Label label8;
    private ComboBox comboBox2;
    private string namee;
    private ExportLodHandle exportLodHandle = new ExportLodHandle();
    private IContainer components = (IContainer) null;
    public string name;
    public int index;
    public string test2;
    public List<string> lArrayItemID;
    public List<string> lArrayParts;
    public List<string> lArrayType;
    public List<string> lArrayOptionID;
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
    private TextBox textBox1;
    private TextBox textBox2;
    private TextBox textBox3;
    private TextBox textBox4;
    private TextBox textBox5;
    private Label label3;
    private Label label2;
    private Label label1;
    private Label label5;
    private Label label4;
    private GroupBox groupBox4;
    private DataGridView dgItems;
    private ToolStrip toolStrip2;
    private ToolStripButton btnSaveSelected;
    private ToolStripSeparator toolStripSeparator1;
    private ToolStripButton btnAddOption;
    private ToolStripSeparator toolStripSeparator6;
    private Button button2;
    private ToolStripMenuItem saveToolStripMenuItem;
    private ToolStripMenuItem exportStrOptionlodToolStripMenuItem;

    public string StringFromLanguage()
    {
      if (this.language == "GER")
      {
        this.namee = "a_set_name_ger";
        return this.namee;
      }
      if (this.language == "POL")
      {
        this.namee = "a_set_name_pld";
        return this.namee;
      }
      if (this.language == "BRA")
      {
        this.namee = "a_set_name_brz";
        return this.namee;
      }
      if (this.language == "RUS")
      {
        this.namee = "a_set_name_rus";
        return this.namee;
      }
      if (this.language == "FRA")
      {
        this.namee = "a_set_name_frc";
        return this.namee;
      }
      if (this.language == "ESP")
      {
        this.namee = "a_set_name_spn";
        return this.namee;
      }
      if (this.language == "MEX")
      {
        this.namee = "a_set_name_mex";
        return this.namee;
      }
      if (this.language == "THA")
      {
        this.namee = "a_set_name_thai";
        return this.namee;
      }
      if (this.language == "ITA")
      {
        this.namee = "a_set_name_ita";
        return this.namee;
      }
      if (!(this.language == "USA"))
        return (string) null;
      this.namee = "a_set_name_usa";
      return this.namee;
    }

    public SetitemEditor() => this.InitializeComponent();

    private void LoadListBox()
    {
      if (this.language == "THA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayTHA, this.Host, this.User, this.Password, this.Database, "select * from t_set_item ORDER BY a_set_idx;");
      else
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, "select * from t_set_item ORDER BY a_set_idx;");
    }

    private void Exporter_Option_Load(object sender, EventArgs e) => this.LoadListBox();

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
      string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, " select * from t_set_item WHERE a_set_idx ='" + this.textBox1.Text + "';", new string[5]
      {
        "a_set_idx",
        "a_enable",
        this.namee ?? "",
        "a_job",
        "a_option_count"
      });
      this.textBox1.Text = strArray[0];
      this.textBox2.Text = strArray[1];
      this.textBox3.Text = strArray[2];
      this.textBox4.Text = strArray[3];
      this.textBox5.Text = strArray[4];
      this.dgItems.Rows.Clear();
      this.dgOption.Rows.Clear();
      this.comboBox2.SelectedIndex = this.comboBox2.FindString(this.textBox4.Text);
      this.LoadDG();
      this.LoadDG2();
    }

    public void LoadDG()
    {
      string str1 = "SELECT a_set_idx, a_item_idx FROM t_set_item WHERE a_set_idx ='" + this.textBox1.Text + "'";
      MySqlConnection mySqlConnection = new MySqlConnection("datasource=" + this.Host + ";Port=3306;User ID="  + this.User + ";Password=" + this.Password + ";Database=" + this.Database + ";Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;");
      MySqlCommand command = mySqlConnection.CreateCommand();
      command.CommandText = str1;
      mySqlConnection.Open();
      MySqlDataReader mySqlDataReader = command.ExecuteReader();
      while (mySqlDataReader.Read())
      {
        string str2 = mySqlDataReader.GetValue(0).ToString();
        string[] strArray1 = mySqlDataReader.GetValue(1).ToString().Split(' ');
        string[] strArray2 = new string[1000];
        string[] strArray3 = new string[1000];
        int index1 = 0;
        this.lArrayItemID = new List<string>();
        foreach (string str3 in strArray1)
        {
          strArray2[index1] = str3;
          this.lArrayItemID.Add(str3);
          ++index1;
        }
        int count = this.lArrayItemID.Count;
        for (int index2 = 0; index2 < count; ++index2)
        {
          switch (index2)
          {
            case 0:
              string str4 = "Helmet";
              this.dgItems.Rows.Add((object) str2, (object) (index2 + 1), (object) str4, (object) this.databaseHandle.IconFast(Convert.ToInt32(this.lArrayItemID[index2])), (object) this.lArrayItemID[index2], (object) this.databaseHandle.ItemNameFast(Convert.ToInt32(this.lArrayItemID[index2])));
              break;
            case 1:
              string str5 = "Shirt";
              this.dgItems.Rows.Add((object) str2, (object) (index2 + 1), (object) str5, (object) this.databaseHandle.IconFast(Convert.ToInt32(this.lArrayItemID[index2])), (object) this.lArrayItemID[index2], (object) this.databaseHandle.ItemNameFast(Convert.ToInt32(this.lArrayItemID[index2])));
              break;
            case 2:
              string str6 = "Weapon";
              this.dgItems.Rows.Add((object) str2, (object) (index2 + 1), (object) str6, (object) this.databaseHandle.IconFast(Convert.ToInt32(this.lArrayItemID[index2])), (object) this.lArrayItemID[index2], (object) this.databaseHandle.ItemNameFast(Convert.ToInt32(this.lArrayItemID[index2])));
              break;
            case 3:
              string str7 = "Pants";
              this.dgItems.Rows.Add((object) str2, (object) (index2 + 1), (object) str7, (object) this.databaseHandle.IconFast(Convert.ToInt32(this.lArrayItemID[index2])), (object) this.lArrayItemID[index2], (object) this.databaseHandle.ItemNameFast(Convert.ToInt32(this.lArrayItemID[index2])));
              break;
            case 4:
              string str8 = "Shield";
              this.dgItems.Rows.Add((object) str2, (object) (index2 + 1), (object) str8, (object) this.databaseHandle.IconFast(Convert.ToInt32(this.lArrayItemID[index2])), (object) this.lArrayItemID[index2], (object) this.databaseHandle.ItemNameFast(Convert.ToInt32(this.lArrayItemID[index2])));
              break;
            case 5:
              string str9 = "Gloves";
              this.dgItems.Rows.Add((object) str2, (object) (index2 + 1), (object) str9, (object) this.databaseHandle.IconFast(Convert.ToInt32(this.lArrayItemID[index2])), (object) this.lArrayItemID[index2], (object) this.databaseHandle.ItemNameFast(Convert.ToInt32(this.lArrayItemID[index2])));
              break;
            case 6:
              string str10 = "Boots";
              this.dgItems.Rows.Add((object) str2, (object) (index2 + 1), (object) str10, (object) this.databaseHandle.IconFast(Convert.ToInt32(this.lArrayItemID[index2])), (object) this.lArrayItemID[index2], (object) this.databaseHandle.ItemNameFast(Convert.ToInt32(this.lArrayItemID[index2])));
              break;
            case 7:
              string str11 = "Acc1";
              this.dgItems.Rows.Add((object) str2, (object) (index2 + 1), (object) str11, (object) this.databaseHandle.IconFast(Convert.ToInt32(this.lArrayItemID[index2])), (object) this.lArrayItemID[index2], (object) this.databaseHandle.ItemNameFast(Convert.ToInt32(this.lArrayItemID[index2])));
              break;
            case 8:
              string str12 = "Acc2";
              this.dgItems.Rows.Add((object) str2, (object) (index2 + 1), (object) str12, (object) this.databaseHandle.IconFast(Convert.ToInt32(this.lArrayItemID[index2])), (object) this.lArrayItemID[index2], (object) this.databaseHandle.ItemNameFast(Convert.ToInt32(this.lArrayItemID[index2])));
              break;
            case 9:
              string str13 = "Acc3";
              this.dgItems.Rows.Add((object) str2, (object) (index2 + 1), (object) str13, (object) this.databaseHandle.IconFast(Convert.ToInt32(this.lArrayItemID[index2])), (object) this.lArrayItemID[index2], (object) this.databaseHandle.ItemNameFast(Convert.ToInt32(this.lArrayItemID[index2])));
              break;
            case 10:
              string str14 = "Pet";
              this.dgItems.Rows.Add((object) str2, (object) (index2 + 1), (object) str14, (object) this.databaseHandle.IconFast(Convert.ToInt32(this.lArrayItemID[index2])), (object) this.lArrayItemID[index2], (object) this.databaseHandle.ItemNameFast(Convert.ToInt32(this.lArrayItemID[index2])));
              break;
            case 11:
              string str15 = "Wing";
              this.dgItems.Rows.Add((object) str2, (object) (index2 + 1), (object) str15, (object) this.databaseHandle.IconFast(Convert.ToInt32(this.lArrayItemID[index2])), (object) this.lArrayItemID[index2], (object) this.databaseHandle.ItemNameFast(Convert.ToInt32(this.lArrayItemID[index2])));
              break;
          }
        }
      }
      mySqlConnection.Close();
    }

    public void LoadDG2()
    {
      string str1 = "SELECT a_set_idx, a_wear_count, a_option_type, a_option_idx, a_option_level,a_option_count FROM t_set_item WHERE a_set_idx ='" + this.textBox1.Text + "'";
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
        string str5 = mySqlDataReader.GetValue(3).ToString();
        string str6 = mySqlDataReader.GetValue(4).ToString();
        string str7 = mySqlDataReader.GetValue(5).ToString();
        int int32 = Convert.ToInt32(mySqlDataReader.GetValue(5));
        string[] strArray1 = str3.Split(' ');
        string[] strArray2 = str4.Split(' ');
        string[] strArray3 = new string[1000];
        string[] strArray4 = new string[1000];
        string[] strArray5 = str5.Split(' ');
        string[] strArray6 = str6.Split(' ');
        string[] strArray7 = new string[1000];
        string[] strArray8 = new string[1000];
        int index1 = 0;
        int index2 = 0;
        int index3 = 0;
        int index4 = 0;
        this.lArrayParts = new List<string>();
        this.lArrayType = new List<string>();
        this.lArrayOptionID = new List<string>();
        this.lArrayLevel = new List<string>();
        foreach (string str8 in strArray1)
        {
          strArray3[index1] = str8;
          this.lArrayParts.Add(str8);
          ++index1;
        }
        foreach (string str9 in strArray2)
        {
          strArray4[index2] = str9;
          this.lArrayType.Add(str9);
          ++index2;
        }
        foreach (string str10 in strArray5)
        {
          strArray7[index3] = str10;
          this.lArrayOptionID.Add(str10);
          ++index3;
        }
        foreach (string str11 in strArray6)
        {
          strArray8[index4] = str11;
          this.lArrayLevel.Add(str11);
          ++index4;
        }
        int num = int32;
        for (int index5 = 0; index5 < num; ++index5)
        {
          switch (int.Parse(this.lArrayType[index5]))
          {
            case 0:
              string str12 = this.databaseHandle.OptionNameFast(int.Parse(this.lArrayOptionID[index5]));
              this.dgOption.Rows.Add((object) str2, (object) (index5 + 1), (object) this.lArrayParts[index5], (object) this.lArrayType[index5], (object) this.lArrayOptionID[index5], (object) this.lArrayLevel[index5], (object) str12, (object) str7, (object) this.databaseHandle.IconFast(19));
              break;
            case 1:
              string str13 = this.databaseHandle.SkillNameFast(int.Parse(this.lArrayOptionID[index5]));
              this.dgOption.Rows.Add((object) str2, (object) (index5 + 1), (object) this.lArrayParts[index5], (object) this.lArrayType[index5], (object) this.lArrayOptionID[index5], (object) this.lArrayLevel[index5], (object) str13, (object) str7, (object) this.databaseHandle.SkillsFast(Convert.ToInt32(this.lArrayOptionID[index5])));
              break;
            default:
              string str14 = "Seal";
              this.dgOption.Rows.Add((object) str2, (object) (index5 + 1), (object) this.lArrayParts[index5], (object) this.lArrayType[index5], (object) this.lArrayOptionID[index5], (object) this.lArrayLevel[index5], (object) str14, (object) str7);
              break;
          }
        }
      }
      mySqlConnection.Close();
    }

    private void btnSaveSelected_Click(object sender, EventArgs e)
    {
      int index1 = this.dgItems.CurrentRow.Index;
      DataGridViewRow row = this.dgItems.Rows[this.dgItems.CurrentRow.Index];
      string str1 = Convert.ToString(row.Cells["ID"].Value);
      string s = Convert.ToString(row.Cells["Type"].Value);
      string str2 = Convert.ToString(row.Cells["ItemID"].Value);
      this.lArrayItemID[int.Parse(s) - 1] = str2;
      string str3 = "";
      int count = this.lArrayItemID.Count;
      for (int index2 = 0; index2 < count; ++index2)
        str3 = index2 != count - 1 ? str3 + this.lArrayItemID[index2].ToString() + " " : str3 + this.lArrayItemID[index2].ToString();
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_set_item SET a_item_idx = '" + str3 + "' WHERE a_set_idx = '" + str1 + "'");
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

    private void BtnSaveOption_Click(object sender, EventArgs e)
    {
      int index1 = this.dgOption.CurrentRow.Index;
      DataGridViewRow row = this.dgOption.Rows[index1];
      string str1 = Convert.ToString(row.Cells["SetID"].Value);
      string s = Convert.ToString(row.Cells["OptionIndex"].Value);
      string str2 = Convert.ToString(row.Cells["Parts"].Value);
      string str3 = Convert.ToString(row.Cells["OptionType"].Value);
      string str4 = Convert.ToString(row.Cells["OptionSkillID"].Value);
      string str5 = Convert.ToString(row.Cells["Level"].Value);
      int index2 = int.Parse(s) - 1;
      this.lArrayParts[index2] = str2;
      this.lArrayType[index2] = str3;
      this.lArrayOptionID[index2] = str4;
      this.lArrayLevel[index2] = str5;
      string str6 = "";
      string str7 = "";
      string str8 = "";
      string str9 = "";
      int count = this.lArrayParts.Count;
      for (int index3 = 0; index3 < count; ++index3)
      {
        if (index3 == count - 1)
        {
          str6 += this.lArrayParts[index3].ToString();
          str7 += this.lArrayType[index3].ToString();
          str8 += this.lArrayOptionID[index3].ToString();
          str9 += this.lArrayLevel[index3].ToString();
        }
        else
        {
          str6 = str6 + this.lArrayParts[index3].ToString() + " ";
          str7 = str7 + this.lArrayType[index3].ToString() + " ";
          str8 = str8 + this.lArrayOptionID[index3].ToString() + " ";
          str9 = str9 + this.lArrayLevel[index3].ToString() + " ";
        }
      }
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_set_item SET a_wear_count = '" + str6 + "', a_option_type = '" + str7 + "', a_option_idx = '" + str8 + "', a_option_level = '" + str9 + "'  WHERE a_set_idx = '" + str1 + "'");
      this.dgOption.Rows.Clear();
      this.LoadDG2();
      try
      {
        this.dgOption.Rows[index1].Selected = true;
        this.dgOption.FirstDisplayedScrollingRowIndex = index1;
      }
      catch
      {
        int num = (int) MessageBox.Show("You must select a Item", "Error");
      }
    }

    private void btnAddOption_Click(object sender, EventArgs e)
    {
      DataGridViewRow row = this.dgOption.Rows[this.dgOption.CurrentRow.Index];
      string str = Convert.ToString(row.Cells["SetID"].Value);
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_set_item SET a_option_count = '" + (Convert.ToInt32(Convert.ToString(row.Cells["OptionCount"].Value)) + 1).ToString() + "' WHERE a_set_idx = '" + str + "'");
      this.dgOption.Rows.Clear();
      this.LoadDG2();
    }

    private void BtnDeleteOption_Click(object sender, EventArgs e)
    {
      DataGridViewRow row = this.dgOption.Rows[this.dgOption.CurrentRow.Index];
      string str = Convert.ToString(row.Cells["SetID"].Value);
      int num = Convert.ToInt32(Convert.ToString(row.Cells["OptionCount"].Value)) + 1;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_set_item SET a_wear_count = '2 0 0 0 0 0 0 0 0 0 0', a_option_type = '0 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1', a_option_idx = '0 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1', a_option_level = '0 0 0 0 0 0 0 0 0 0 0', a_option_count = '1'  WHERE a_set_idx = '" + str + "'");
      this.dgOption.Rows.Clear();
      this.LoadDG2();
    }

    private void button2_Click(object sender, EventArgs e)
    {
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_set_item SET a_enable = '" + this.textBox2.Text + "', " + this.namee + " = '" + this.textBox3.Text + "', a_job = '" + this.textBox4.Text + "'WHERE a_set_idx = '" + this.textBox1.Text + "'");
      int selectedIndex = this.listBox1.SelectedIndex;
      this.LoadListBox();
      this.listBox1.SelectedIndex = selectedIndex;
    }

    private void button1_Click(object sender, EventArgs e)
    {
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_set_item (" + this.namee + " , a_job, a_enable, a_item_idx, a_option_count, a_wear_count, a_option_type, a_option_idx, a_option_level) VALUES('NewSet','0','1','-1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1','1','2 0 0 0 0 0 0 0 0 0 0','0 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1','0 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1','0 0 0 0 0 0 0 0 0 0 0')");
      this.LoadListBox();
      this.listBox1.SelectedIndex = this.listBox1.Items.Count - 1;
    }

    private void button3_Click(object sender, EventArgs e)
    {
      int selectedIndex = this.listBox1.SelectedIndex;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_set_item WHERE a_set_idx = '" + this.textBox1.Text + "'");
      this.LoadListBox();
      this.listBox1.SelectedIndex = selectedIndex - 1;
    }

    private void exportlodToolStripMenuItem_Click(object sender, EventArgs e)
    {
      new LodExporter.LodExporter().Show();
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

    private void exportStrOptionlodToolStripMenuItem_Click(object sender, EventArgs e)
    {
      new FormExport().Show();
    }

    private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox4.Text = this.GetIndexByComboBox(this.comboBox2.Text).ToString();
    }

    private void comboBox2_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.comboBox2.BackColor = Color.Pink;
      this.textBox4.BackColor = Color.Pink;
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
      this.fileExportToolStripMenuItem = new ToolStripMenuItem();
      this.exportlodToolStripMenuItem = new ToolStripMenuItem();
      this.exportStrOptionlodToolStripMenuItem = new ToolStripMenuItem();
      this.saveToolStripMenuItem = new ToolStripMenuItem();
      this.groupBox3 = new GroupBox();
      this.button3 = new Button();
      this.button1 = new Button();
      this.listBox1 = new ListBox();
      this.button2 = new Button();
      this.groupBox1 = new GroupBox();
      this.textBox4 = new TextBox();
      this.cbEnabled = new CheckBox();
      this.label4 = new Label();
      this.label3 = new Label();
      this.label2 = new Label();
      this.label1 = new Label();
      this.textBox3 = new TextBox();
      this.textBox1 = new TextBox();
      this.textBox2 = new TextBox();
      this.textBox5 = new TextBox();
      this.label5 = new Label();
      this.groupBox4 = new GroupBox();
      this.dgItems = new DataGridView();
      this.ID = new DataGridViewTextBoxColumn();
      this.Type = new DataGridViewTextBoxColumn();
      this.ItemType = new DataGridViewTextBoxColumn();
      this.Icon = new DataGridViewImageColumn();
      this.ItemID = new DataGridViewTextBoxColumn();
      this.ItemName = new DataGridViewTextBoxColumn();
      this.OldItem = new DataGridViewTextBoxColumn();
      this.toolStrip2 = new ToolStrip();
      this.btnSaveSelected = new ToolStripButton();
      this.toolStripSeparator1 = new ToolStripSeparator();
      this.toolStripSeparator6 = new ToolStripSeparator();
      this.groupBox5 = new GroupBox();
      this.dgOption = new DataGridView();
      this.SetID = new DataGridViewTextBoxColumn();
      this.OptionIndex = new DataGridViewTextBoxColumn();
      this.Parts = new DataGridViewTextBoxColumn();
      this.OptionType = new DataGridViewTextBoxColumn();
      this.OptionSkillID = new DataGridViewTextBoxColumn();
      this.Level = new DataGridViewTextBoxColumn();
      this.OptionSkillName = new DataGridViewTextBoxColumn();
      this.OptionCount = new DataGridViewTextBoxColumn();
      this.dataGridViewImageColumn1 = new DataGridViewImageColumn();
      this.toolStrip1 = new ToolStrip();
      this.BtnSaveOption = new ToolStripButton();
      this.toolStripSeparator2 = new ToolStripSeparator();
      this.btnAddOption = new ToolStripButton();
      this.toolStripSeparator3 = new ToolStripSeparator();
      this.BtnDeleteOption = new ToolStripButton();
      this.label6 = new Label();
      this.label7 = new Label();
      this.label8 = new Label();
      this.comboBox2 = new ComboBox();
      this.menuStrip1.SuspendLayout();
      this.groupBox3.SuspendLayout();
      this.groupBox1.SuspendLayout();
      this.groupBox4.SuspendLayout();
      ((ISupportInitialize) this.dgItems).BeginInit();
      this.toolStrip2.SuspendLayout();
      this.groupBox5.SuspendLayout();
      ((ISupportInitialize) this.dgOption).BeginInit();
      this.toolStrip1.SuspendLayout();
      this.SuspendLayout();
      this.menuStrip1.AllowMerge = false;
      this.menuStrip1.BackColor = SystemColors.ButtonHighlight;
      this.menuStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.fileExportToolStripMenuItem
      });
      this.menuStrip1.Location = new Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new Size(1089, 24);
      this.menuStrip1.TabIndex = 0;
      this.menuStrip1.Text = "menuStrip1";
      this.fileExportToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[3]
      {
        (ToolStripItem) this.exportlodToolStripMenuItem,
        (ToolStripItem) this.exportStrOptionlodToolStripMenuItem,
        (ToolStripItem) this.saveToolStripMenuItem
      });
      this.fileExportToolStripMenuItem.Enabled = false;
      this.fileExportToolStripMenuItem.Name = "fileExportToolStripMenuItem";
      this.fileExportToolStripMenuItem.Size = new Size(74, 20);
      this.fileExportToolStripMenuItem.Text = "File Export";
      this.exportlodToolStripMenuItem.Name = "exportlodToolStripMenuItem";
      this.exportlodToolStripMenuItem.Size = new Size(181, 22);
      this.exportlodToolStripMenuItem.Text = "Export option.lod";
      this.exportlodToolStripMenuItem.Click += new EventHandler(this.exportlodToolStripMenuItem_Click);
      this.exportStrOptionlodToolStripMenuItem.Name = "exportStrOptionlodToolStripMenuItem";
      this.exportStrOptionlodToolStripMenuItem.Size = new Size(181, 22);
      this.exportStrOptionlodToolStripMenuItem.Text = "Export strOption.lod";
      this.exportStrOptionlodToolStripMenuItem.Click += new EventHandler(this.exportStrOptionlodToolStripMenuItem_Click);
      this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
      this.saveToolStripMenuItem.Size = new Size(181, 22);
      this.saveToolStripMenuItem.Text = "Save";
      this.saveToolStripMenuItem.Click += new EventHandler(this.saveToolStripMenuItem_Click);
      this.groupBox3.Controls.Add((Control) this.button3);
      this.groupBox3.Controls.Add((Control) this.button1);
      this.groupBox3.Controls.Add((Control) this.listBox1);
      this.groupBox3.Controls.Add((Control) this.button2);
      this.groupBox3.Location = new Point(12, 27);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Size = new Size(237, 537);
      this.groupBox3.TabIndex = 32;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "Set";
      this.button3.FlatStyle = FlatStyle.Flat;
      this.button3.Location = new Point(170, 508);
      this.button3.Name = "button3";
      this.button3.Size = new Size(61, 23);
      this.button3.TabIndex = 4;
      this.button3.Text = "Delete";
      this.button3.UseVisualStyleBackColor = true;
      this.button3.Click += new EventHandler(this.button3_Click);
      this.button1.FlatStyle = FlatStyle.Flat;
      this.button1.Location = new Point(6, 508);
      this.button1.Name = "button1";
      this.button1.Size = new Size(75, 23);
      this.button1.TabIndex = 2;
      this.button1.Text = "Add";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.listBox1.FormattingEnabled = true;
      this.listBox1.Location = new Point(6, 14);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new Size(225, 485);
      this.listBox1.TabIndex = 1;
      this.listBox1.SelectedIndexChanged += new EventHandler(this.listBox1_SelectedIndexChanged);
      this.button2.FlatStyle = FlatStyle.Flat;
      this.button2.Location = new Point(87, 508);
      this.button2.Name = "button2";
      this.button2.Size = new Size(77, 23);
      this.button2.TabIndex = 45;
      this.button2.Text = "Save";
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.groupBox1.Controls.Add((Control) this.comboBox2);
      this.groupBox1.Controls.Add((Control) this.textBox4);
      this.groupBox1.Controls.Add((Control) this.cbEnabled);
      this.groupBox1.Controls.Add((Control) this.label4);
      this.groupBox1.Controls.Add((Control) this.label3);
      this.groupBox1.Controls.Add((Control) this.label2);
      this.groupBox1.Controls.Add((Control) this.label1);
      this.groupBox1.Controls.Add((Control) this.textBox3);
      this.groupBox1.Controls.Add((Control) this.textBox1);
      this.groupBox1.Controls.Add((Control) this.textBox2);
      this.groupBox1.Location = new Point((int) byte.MaxValue, 27);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(409, 80);
      this.groupBox1.TabIndex = 33;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Main";
      this.textBox4.BorderStyle = BorderStyle.FixedSingle;
      this.textBox4.Location = new Point(368, 49);
      this.textBox4.Name = "textBox4";
      this.textBox4.Size = new Size(35, 20);
      this.textBox4.TabIndex = 38;
      this.cbEnabled.AutoSize = true;
      this.cbEnabled.BackColor = Color.Chartreuse;
      this.cbEnabled.Location = new Point(193, 19);
      this.cbEnabled.Name = "cbEnabled";
      this.cbEnabled.Size = new Size(65, 17);
      this.cbEnabled.TabIndex = 89;
      this.cbEnabled.Text = "Enabled";
      this.cbEnabled.UseVisualStyleBackColor = false;
      this.cbEnabled.CheckedChanged += new EventHandler(this.cbEnabled_CheckedChanged);
      this.label4.AutoSize = true;
      this.label4.Location = new Point(200, 51);
      this.label4.Name = "label4";
      this.label4.Size = new Size(27, 13);
      this.label4.TabIndex = 41;
      this.label4.Text = "Job:";
      this.label3.AutoSize = true;
      this.label3.Location = new Point(6, 51);
      this.label3.Name = "label3";
      this.label3.Size = new Size(38, 13);
      this.label3.TabIndex = 41;
      this.label3.Text = "Name:";
      this.label2.AutoSize = true;
      this.label2.Location = new Point(102, 21);
      this.label2.Name = "label2";
      this.label2.Size = new Size(43, 13);
      this.label2.TabIndex = 39;
      this.label2.Text = "Enable:";
      this.label2.Click += new EventHandler(this.label2_Click);
      this.label1.AutoSize = true;
      this.label1.Location = new Point(6, 21);
      this.label1.Name = "label1";
      this.label1.Size = new Size(36, 13);
      this.label1.TabIndex = 38;
      this.label1.Text = "Index:";
      this.textBox3.BorderStyle = BorderStyle.FixedSingle;
      this.textBox3.Location = new Point(48, 49);
      this.textBox3.Name = "textBox3";
      this.textBox3.Size = new Size(146, 20);
      this.textBox3.TabIndex = 37;
      this.textBox1.BorderStyle = BorderStyle.FixedSingle;
      this.textBox1.Location = new Point(48, 19);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(41, 20);
      this.textBox1.TabIndex = 35;
      this.textBox2.BorderStyle = BorderStyle.FixedSingle;
      this.textBox2.Location = new Point(150, 19);
      this.textBox2.Name = "textBox2";
      this.textBox2.Size = new Size(34, 20);
      this.textBox2.TabIndex = 36;
      this.textBox2.TextChanged += new EventHandler(this.textBox2_TextChanged);
      this.textBox2.KeyPress += new KeyPressEventHandler(this.textBox2_KeyPress);
      this.textBox5.BorderStyle = BorderStyle.FixedSingle;
      this.textBox5.Enabled = false;
      this.textBox5.Location = new Point(739, 1);
      this.textBox5.Name = "textBox5";
      this.textBox5.Size = new Size(44, 20);
      this.textBox5.TabIndex = 39;
      this.label5.AutoSize = true;
      this.label5.Location = new Point(668, 4);
      this.label5.Name = "label5";
      this.label5.Size = new Size(72, 13);
      this.label5.TabIndex = 42;
      this.label5.Text = "Option Count:";
      this.groupBox4.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left;
      this.groupBox4.Controls.Add((Control) this.dgItems);
      this.groupBox4.Controls.Add((Control) this.toolStrip2);
      this.groupBox4.Location = new Point((int) byte.MaxValue, 113);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Size = new Size(409, 388);
      this.groupBox4.TabIndex = 44;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "Set Item List";
      this.dgItems.AllowUserToAddRows = false;
      this.dgItems.AllowUserToDeleteRows = false;
      this.dgItems.BackgroundColor = SystemColors.Control;
      this.dgItems.BorderStyle = BorderStyle.None;
      this.dgItems.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dgItems.Columns.AddRange((DataGridViewColumn) this.ID, (DataGridViewColumn) this.Type, (DataGridViewColumn) this.ItemType, (DataGridViewColumn) this.Icon, (DataGridViewColumn) this.ItemID, (DataGridViewColumn) this.ItemName, (DataGridViewColumn) this.OldItem);
      this.dgItems.Dock = DockStyle.Fill;
      this.dgItems.EnableHeadersVisualStyles = false;
      this.dgItems.Location = new Point(3, 16);
      this.dgItems.Name = "dgItems";
      this.dgItems.RowHeadersVisible = false;
      this.dgItems.RowTemplate.Height = 25;
      this.dgItems.ScrollBars = ScrollBars.None;
      this.dgItems.Size = new Size(403, 344);
      this.dgItems.TabIndex = 0;
      this.ID.HeaderText = "ID";
      this.ID.Name = "ID";
      this.ID.Visible = false;
      this.ID.Width = 60;
      this.Type.HeaderText = "Kind";
      this.Type.Name = "Type";
      this.Type.Width = 50;
      this.ItemType.HeaderText = "ItemType";
      this.ItemType.Name = "ItemType";
      this.ItemType.Width = 70;
      this.Icon.HeaderText = "Icon";
      this.Icon.Name = "Icon";
      this.Icon.Width = 32;
      this.ItemID.HeaderText = "ItemID";
      this.ItemID.Name = "ItemID";
      this.ItemID.Width = 70;
      this.ItemName.HeaderText = "Name";
      this.ItemName.Name = "ItemName";
      this.ItemName.Width = 225;
      this.OldItem.HeaderText = "OldItem";
      this.OldItem.Name = "OldItem";
      this.OldItem.Visible = false;
      this.toolStrip2.Dock = DockStyle.Bottom;
      this.toolStrip2.GripStyle = ToolStripGripStyle.Hidden;
      this.toolStrip2.Items.AddRange(new ToolStripItem[3]
      {
        (ToolStripItem) this.btnSaveSelected,
        (ToolStripItem) this.toolStripSeparator1,
        (ToolStripItem) this.toolStripSeparator6
      });
      this.toolStrip2.Location = new Point(3, 360);
      this.toolStrip2.Name = "toolStrip2";
      this.toolStrip2.Size = new Size(403, 25);
      this.toolStrip2.TabIndex = 1;
      this.toolStrip2.Text = "toolStrip2";
      this.btnSaveSelected.DisplayStyle = ToolStripItemDisplayStyle.Text;
      this.btnSaveSelected.ImageTransparentColor = Color.Magenta;
      this.btnSaveSelected.Name = "btnSaveSelected";
      this.btnSaveSelected.Size = new Size(82, 22);
      this.btnSaveSelected.Text = "Save Selected";
      this.btnSaveSelected.Click += new EventHandler(this.btnSaveSelected_Click);
      this.toolStripSeparator1.Name = "toolStripSeparator1";
      this.toolStripSeparator1.Size = new Size(6, 25);
      this.toolStripSeparator6.Name = "toolStripSeparator6";
      this.toolStripSeparator6.Size = new Size(6, 25);
      this.groupBox5.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left;
      this.groupBox5.Controls.Add((Control) this.dgOption);
      this.groupBox5.Controls.Add((Control) this.toolStrip1);
      this.groupBox5.Location = new Point(673, 113);
      this.groupBox5.Name = "groupBox5";
      this.groupBox5.Size = new Size(409, 388);
      this.groupBox5.TabIndex = 48;
      this.groupBox5.TabStop = false;
      this.groupBox5.Text = "Option";
      this.dgOption.AllowUserToAddRows = false;
      this.dgOption.AllowUserToDeleteRows = false;
      this.dgOption.BackgroundColor = SystemColors.Control;
      this.dgOption.BorderStyle = BorderStyle.None;
      this.dgOption.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dgOption.Columns.AddRange((DataGridViewColumn) this.SetID, (DataGridViewColumn) this.OptionIndex, (DataGridViewColumn) this.Parts, (DataGridViewColumn) this.OptionType, (DataGridViewColumn) this.OptionSkillID, (DataGridViewColumn) this.Level, (DataGridViewColumn) this.OptionSkillName, (DataGridViewColumn) this.OptionCount, (DataGridViewColumn) this.dataGridViewImageColumn1);
      this.dgOption.Dock = DockStyle.Fill;
      this.dgOption.EnableHeadersVisualStyles = false;
      this.dgOption.Location = new Point(3, 16);
      this.dgOption.Name = "dgOption";
      this.dgOption.RowHeadersVisible = false;
      this.dgOption.RowTemplate.Height = 25;
      this.dgOption.Size = new Size(403, 344);
      this.dgOption.TabIndex = 0;
      this.SetID.HeaderText = "ID";
      this.SetID.Name = "SetID";
      this.SetID.Visible = false;
      this.SetID.Width = 50;
      this.OptionIndex.HeaderText = "Index";
      this.OptionIndex.Name = "OptionIndex";
      this.OptionIndex.Visible = false;
      this.OptionIndex.Width = 50;
      this.Parts.HeaderText = "Parts";
      this.Parts.Name = "Parts";
      this.Parts.Width = 50;
      this.OptionType.HeaderText = "Type";
      this.OptionType.Name = "OptionType";
      this.OptionType.Width = 50;
      this.OptionSkillID.HeaderText = "Opion/Skill ID";
      this.OptionSkillID.Name = "OptionSkillID";
      this.OptionSkillID.Width = 80;
      this.Level.HeaderText = "Level";
      this.Level.Name = "Level";
      this.Level.Width = 40;
      this.OptionSkillName.HeaderText = "Name";
      this.OptionSkillName.Name = "OptionSkillName";
      this.OptionSkillName.Width = 150;
      this.OptionCount.HeaderText = "Count";
      this.OptionCount.Name = "OptionCount";
      this.OptionCount.Visible = false;
      this.dataGridViewImageColumn1.HeaderText = "";
      this.dataGridViewImageColumn1.Name = "dataGridViewImageColumn1";
      this.dataGridViewImageColumn1.Width = 32;
      this.toolStrip1.Dock = DockStyle.Bottom;
      this.toolStrip1.GripStyle = ToolStripGripStyle.Hidden;
      this.toolStrip1.Items.AddRange(new ToolStripItem[5]
      {
        (ToolStripItem) this.BtnSaveOption,
        (ToolStripItem) this.toolStripSeparator2,
        (ToolStripItem) this.btnAddOption,
        (ToolStripItem) this.toolStripSeparator3,
        (ToolStripItem) this.BtnDeleteOption
      });
      this.toolStrip1.Location = new Point(3, 360);
      this.toolStrip1.Name = "toolStrip1";
      this.toolStrip1.Size = new Size(403, 25);
      this.toolStrip1.TabIndex = 1;
      this.toolStrip1.Text = "toolStrip1";
      this.BtnSaveOption.DisplayStyle = ToolStripItemDisplayStyle.Text;
      this.BtnSaveOption.ImageTransparentColor = Color.Magenta;
      this.BtnSaveOption.Name = "BtnSaveOption";
      this.BtnSaveOption.Size = new Size(82, 22);
      this.BtnSaveOption.Text = "Save Selected";
      this.BtnSaveOption.Click += new EventHandler(this.BtnSaveOption_Click);
      this.toolStripSeparator2.Name = "toolStripSeparator2";
      this.toolStripSeparator2.Size = new Size(6, 25);
      this.btnAddOption.DisplayStyle = ToolStripItemDisplayStyle.Text;
      this.btnAddOption.ImageTransparentColor = Color.Magenta;
      this.btnAddOption.Name = "btnAddOption";
      this.btnAddOption.Size = new Size(73, 22);
      this.btnAddOption.Text = "Add Option";
      this.btnAddOption.Click += new EventHandler(this.btnAddOption_Click);
      this.toolStripSeparator3.Name = "toolStripSeparator3";
      this.toolStripSeparator3.Size = new Size(6, 25);
      this.BtnDeleteOption.DisplayStyle = ToolStripItemDisplayStyle.Text;
      this.BtnDeleteOption.ImageTransparentColor = Color.Magenta;
      this.BtnDeleteOption.Name = "BtnDeleteOption";
      this.BtnDeleteOption.Size = new Size(39, 22);
      this.BtnDeleteOption.Text = "Reset";
      this.BtnDeleteOption.Click += new EventHandler(this.BtnDeleteOption_Click);
      this.label6.AutoSize = true;
      this.label6.Location = new Point(752, 41);
      this.label6.Name = "label6";
      this.label6.Size = new Size(325, 13);
      this.label6.TabIndex = 50;
      this.label6.Text = "[Job Type]* Titan = 0 , Knight = 1, Healer = 2, Mage = 3, Rouge = 4";
      this.label7.AutoSize = true;
      this.label7.Location = new Point(815, 58);
      this.label7.Name = "label7";
      this.label7.Size = new Size(209, 13);
      this.label7.TabIndex = 51;
      this.label7.Text = "Sorcerer = 5 , Night Shadow = 6 , All = 999";
      this.label8.AutoSize = true;
      this.label8.Location = new Point(723, 101);
      this.label8.Name = "label8";
      this.label8.Size = new Size(209, 13);
      this.label8.TabIndex = 52;
      this.label8.Text = "[Option Type] * 0 = Seal Option, 1 = Skill Id";
      this.comboBox2.FlatStyle = FlatStyle.Flat;
      this.comboBox2.FormattingEnabled = true;
      this.comboBox2.Location = new Point(231, 48);
      this.comboBox2.Name = "comboBox2";
      this.comboBox2.Size = new Size(131, 21);
      this.comboBox2.TabIndex = 96;
      this.comboBox2.Items.AddRange(new object[10]
      {
        (object) "0 - Titan",
        (object) "1 - Knight",
        (object) "2 - Healer",
        (object) "3 - Mage",
        (object) "4 - Rouge",
        (object) "5 - Sorcerer",
        (object) "6 - Night Shadow",
        (object) "7 - Ex-rouge",
        (object) "8 - Arch-Mage",
        (object) "999 - All"
      });
      this.comboBox2.SelectedIndexChanged += new EventHandler(this.comboBox2_SelectedIndexChanged);
      this.comboBox2.SelectionChangeCommitted += new EventHandler(this.comboBox2_SelectionChangeCommitted);
      this.ClientSize = new Size(1089, 576);
      this.Controls.Add((Control) this.label8);
      this.Controls.Add((Control) this.label7);
      this.Controls.Add((Control) this.label6);
      this.Controls.Add((Control) this.textBox5);
      this.Controls.Add((Control) this.label5);
      this.Controls.Add((Control) this.groupBox5);
      this.Controls.Add((Control) this.groupBox4);
      this.Controls.Add((Control) this.groupBox1);
      this.Controls.Add((Control) this.groupBox3);
      this.Controls.Add((Control) this.menuStrip1);
      this.MainMenuStrip = this.menuStrip1;
      this.Name = nameof (SetitemEditor);
      this.Text = "SetItem Editor";
      this.Load += new EventHandler(this.Exporter_Option_Load);
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.groupBox3.ResumeLayout(false);
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.groupBox4.ResumeLayout(false);
      this.groupBox4.PerformLayout();
      ((ISupportInitialize) this.dgItems).EndInit();
      this.toolStrip2.ResumeLayout(false);
      this.toolStrip2.PerformLayout();
      this.groupBox5.ResumeLayout(false);
      this.groupBox5.PerformLayout();
      ((ISupportInitialize) this.dgOption).EndInit();
      this.toolStrip1.ResumeLayout(false);
      this.toolStrip1.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();
    }

    private void tbMaxOption_TextChanged(object sender, EventArgs e)
    {
    }

    private void saveToolStripMenuItem_Click(object sender, EventArgs e)
    {
      this.exportLodHandle.ExportOption_V4();
    }

    private void label2_Click(object sender, EventArgs e)
    {
    }

    private void cbEnabled_CheckedChanged(object sender, EventArgs e)
    {
      if (this.cbEnabled.Checked)
      {
        this.cbEnabled.BackColor = Color.Chartreuse;
        this.textBox2.Text = "1";
      }
      else
      {
        if (this.cbEnabled.Checked)
          return;
        this.cbEnabled.BackColor = Color.Red;
        this.textBox2.Text = "0";
      }
    }

    private void textBox2_TextChanged(object sender, EventArgs e)
    {
      if (this.textBox2.Text == "1")
      {
        this.cbEnabled.Checked = true;
      }
      else
      {
        if (!(this.textBox2.Text == "0"))
          return;
        this.cbEnabled.Checked = false;
      }
    }

    private void textBox2_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox2.BackColor = Color.LightBlue;
    }
  }
}
