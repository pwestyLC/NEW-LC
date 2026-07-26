// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.MakeItem.MakeItemEditor
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using LcDevPack_TeamDamonA.Properties;
using MySqlConnector;
using StringExporter;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.MakeItem
{
  public class MakeItemEditor : Form
  {
    public static Connection connection = new Connection();
    public static int MaxOptionLevel;
    private string Host = MakeItemEditor.connection.Settings.SqlHost;
    private string User = MakeItemEditor.connection.Settings.SqlUser;
    private string Password = MakeItemEditor.connection.Settings.SqlPassword;
    private string Database = MakeItemEditor.connection.Settings.SqlDatabase;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
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
    private CheckBox cbEnabled;
    private PictureBox pictureBox7;
    private Button button4;
    private TextBox ItemID;
    private Label label6;
    private Label label3;
    private TextBox textBox3;
    private GroupBox groupBox2;
    private ComboBox CbSubType6;
    private ComboBox CbSubType5;
    private ComboBox CbSubType4;
    private ComboBox CbSubtype3;
    private ComboBox CbSubtype2;
    private ComboBox CbSubtype1;
    private ComboBox comboBox1;
    private TextBox textBox7;
    private Label label8;
    private TextBox textBox8;
    private Label label9;
    private ComboBox comboBox2;
    private Label label10;
    private TextBox textBox9;
    private Label label7;
    private TextBox textBox6;
    private Label label5;
    private TextBox textBox5;
    private DataGridViewTextBoxColumn ID;
    private DataGridViewTextBoxColumn StuffIndex;
    private DataGridViewTextBoxColumn ItemType;
    private DataGridViewImageColumn Icon;
    private DataGridViewTextBoxColumn ItemName;
    private DataGridViewTextBoxColumn ItemCount;
    private Button button5;
    private ToolStripSplitButton Reset;
    private string namee;
    private ExportLodHandle exportLodHandle = new ExportLodHandle();
    private IContainer components = (IContainer) null;
    public string name;
    public int index;
    public string test2;
    public List<string> lArrayItemID;
    public List<string> lArrayParts;
    public List<string> lArrayCout;
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
    private TextBox textBox4;
    private Label label2;
    private Label label1;
    private Label label4;
    private GroupBox groupBox4;
    private DataGridView dgItems;
    private ToolStrip toolStrip2;
    private ToolStripButton btnSaveSelected;
    private ToolStripSeparator toolStripSeparator1;
    private ToolStripSeparator toolStripSeparator6;
    private Button button2;

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

    public MakeItemEditor() => this.InitializeComponent();

    private void LoadStartUp()
    {
      this.comboBox1.Items.AddRange(new object[7]
      {
        (object) "-1 - None",
        (object) "656 - Armor 1",
        (object) "657 - Armor 2",
        (object) "658 - Weapon 1",
        (object) "659 - Weapon 2",
        (object) "660 - Potion, ect",
        (object) "767 - Unknown"
      });
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
      this.CbSubtype1.Items.AddRange(new object[4]
      {
        (object) "-1 - None",
        (object) "0 - Helm",
        (object) "1 - Shirt",
        (object) "3 - Gloves"
      });
      this.CbSubtype2.Items.AddRange(new object[5]
      {
        (object) "-1 - None",
        (object) "2 - Pants",
        (object) "4 - Boots",
        (object) "5 - Shield",
        (object) "6 - Wing"
      });
      this.CbSubtype3.Items.AddRange(new object[8]
      {
        (object) "-1 - None",
        (object) "1 - X-Bow",
        (object) "2 - Staff",
        (object) "4 - Axe",
        (object) "11 - Dual Swords",
        (object) "12 - Scepter",
        (object) "14 - Fallarm",
        (object) "15 - NS Weapon"
      });
      this.CbSubType4.Items.AddRange(new object[7]
      {
        (object) "-1 - None",
        (object) "0 - Single Sword",
        (object) "3 - Big Sword",
        (object) "5 - Wand",
        (object) "6 - Bow",
        (object) "7 - Dagger",
        (object) "13 - Scythe"
      });
      this.CbSubType5.Items.AddRange(new object[4]
      {
        (object) "-1 - None",
        (object) "2 - Books, Scrolls",
        (object) "6 - Potions",
        (object) "4 - Quest, Event, Upgrade"
      });
      this.CbSubType6.Items.AddRange(new object[1]
      {
        (object) "-1 - Unkown"
      });
    }

    public static string[] SubTypes(int Type)
    {
      List<string> stringList = new List<string>();
      switch (Type)
      {
        case -1:
          stringList.Add("-1 - None");
          break;
        case 656:
          stringList.Add("-1 - None");
          stringList.Add("0 - Helm");
          stringList.Add("1 - Shirt");
          stringList.Add("3 - Gloves");
          break;
        case 657:
          stringList.Add("-1 - None");
          stringList.Add("2 - Pants");
          stringList.Add("4 - Boots");
          stringList.Add("5 - Shield");
          stringList.Add("6 - Wing");
          break;
        case 658:
          stringList.Add("-1 - None");
          stringList.Add("1 - X-Bow");
          stringList.Add("2 - Staff");
          stringList.Add("4 - Axe");
          stringList.Add("11 - Dual Swords");
          stringList.Add("5 - Wand");
          stringList.Add("14 - Fallarm");
          stringList.Add("15 - NS Weapon");
          break;
        case 659:
          stringList.Add("-1 - None");
          stringList.Add("0 - Single Sword");
          stringList.Add("3 - Big Sword");
          stringList.Add("5 - Wand");
          stringList.Add("6 - Bow");
          stringList.Add("7 - Dagger");
          stringList.Add("13 - Scythe");
          break;
        case 660:
          stringList.Add("-1 - None");
          stringList.Add("2 - Books, Scrolls");
          stringList.Add("6 - Potions");
          stringList.Add("4 - Quest, Event, Upgrade");
          break;
        case 767:
          stringList.Add("-1 - Unknown");
          break;
        default:
          stringList.Add("-1 - Unknown");
          break;
      }
      return stringList.ToArray();
    }

    public void SelectBoxes()
    {
      int num1 = this.comboBox1.FindString(this.textBox7.Text);
      int num2 = this.comboBox2.FindString(this.textBox4.Text);
      int num3 = this.CbSubtype1.FindString(this.textBox8.Text);
      int num4 = this.CbSubtype2.FindString(this.textBox8.Text);
      int num5 = this.CbSubtype3.FindString(this.textBox8.Text);
      int num6 = this.CbSubType4.FindString(this.textBox8.Text);
      int num7 = this.CbSubType5.FindString(this.textBox8.Text);
      int num8 = this.CbSubType6.FindString(this.textBox8.Text);
      this.comboBox1.SelectedIndex = num1;
      this.comboBox2.SelectedIndex = num2;
      this.CbSubtype1.SelectedIndex = num3;
      this.CbSubtype2.SelectedIndex = num4;
      this.CbSubtype3.SelectedIndex = num5;
      this.CbSubType4.SelectedIndex = num6;
      this.CbSubType5.SelectedIndex = num7;
      this.CbSubType6.SelectedIndex = num8;
    }

    private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox7.Text = this.GetIndexByComboBox(this.comboBox1.Text).ToString();
      if (this.textBox7.Text == "-1")
      {
        this.CbSubType6.Visible = true;
        this.CbSubtype1.Visible = false;
        this.CbSubtype2.Visible = false;
        this.CbSubtype3.Visible = false;
        this.CbSubType4.Visible = false;
        this.CbSubType5.Visible = false;
      }
      else if (this.textBox7.Text == "656")
      {
        this.CbSubType6.Visible = false;
        this.CbSubtype1.Visible = true;
        this.CbSubtype2.Visible = false;
        this.CbSubtype3.Visible = false;
        this.CbSubType4.Visible = false;
        this.CbSubType5.Visible = false;
        this.CbSubType6.Visible = false;
      }
      else if (this.textBox7.Text == "657")
      {
        this.CbSubType6.Visible = false;
        this.CbSubtype1.Visible = false;
        this.CbSubtype2.Visible = true;
        this.CbSubtype3.Visible = false;
        this.CbSubType4.Visible = false;
        this.CbSubType5.Visible = false;
        this.CbSubType6.Visible = false;
      }
      else if (this.textBox7.Text == "658")
      {
        this.CbSubType6.Visible = false;
        this.CbSubtype1.Visible = false;
        this.CbSubtype2.Visible = false;
        this.CbSubtype3.Visible = true;
        this.CbSubType4.Visible = false;
        this.CbSubType5.Visible = false;
        this.CbSubType6.Visible = false;
      }
      else if (this.textBox7.Text == "659")
      {
        this.CbSubType6.Visible = false;
        this.CbSubtype1.Visible = false;
        this.CbSubtype2.Visible = false;
        this.CbSubtype3.Visible = false;
        this.CbSubType4.Visible = true;
        this.CbSubType5.Visible = false;
        this.CbSubType6.Visible = false;
      }
      else if (this.textBox7.Text == "660")
      {
        this.CbSubType6.Visible = false;
        this.CbSubtype1.Visible = false;
        this.CbSubtype2.Visible = false;
        this.CbSubtype3.Visible = false;
        this.CbSubType4.Visible = false;
        this.CbSubType5.Visible = true;
        this.CbSubType6.Visible = false;
      }
      else
      {
        if (this.textBox7.Text == "767")
          return;
        this.CbSubtype1.Visible = false;
        this.CbSubtype2.Visible = false;
        this.CbSubtype3.Visible = false;
        this.CbSubType4.Visible = false;
        this.CbSubType5.Visible = false;
        this.CbSubType6.Visible = true;
      }
    }

    private void comboBox1_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.comboBox1.BackColor = Color.Pink;
      this.textBox2.BackColor = Color.Pink;
    }

    private void LoadListBox()
    {
      if (this.language == "THA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayTHA, this.Host, this.User, this.Password, this.Database, "select * from t_factory_item ORDER BY a_index;");
      else
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, "select * from t_factory_item ORDER BY a_index;");
    }

    private void Exporter_Option_Load(object sender, EventArgs e)
    {
      this.LoadListBox();
      this.LoadStartUp();
      this.SelectBoxes();
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

    private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox4.Text = this.GetIndexByComboBox(this.comboBox2.Text).ToString();
    }

    private void comboBox2_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.comboBox2.BackColor = Color.Pink;
      this.textBox4.BackColor = Color.Pink;
    }

    private void CbSubtype1_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (!(this.textBox7.Text == "656"))
        return;
      this.textBox8.Text = this.GetIndexByComboBox(this.CbSubtype1.Text).ToString();
    }

    private void CbSubtype1_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.CbSubtype1.BackColor = Color.Pink;
      this.textBox8.BackColor = Color.Pink;
    }

    private void CbSubtype2_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (!(this.textBox7.Text == "657"))
        return;
      this.textBox8.Text = this.GetIndexByComboBox(this.CbSubtype2.Text).ToString();
    }

    private void CbSubtype2_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.CbSubtype2.BackColor = Color.Pink;
      this.textBox8.BackColor = Color.Pink;
    }

    private void CbSubtype3_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (!(this.textBox7.Text == "658"))
        return;
      this.textBox8.Text = this.GetIndexByComboBox(this.CbSubtype3.Text).ToString();
    }

    private void CbSubtype3_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.CbSubtype3.BackColor = Color.Pink;
      this.textBox8.BackColor = Color.Pink;
    }

    private void CbSubType4_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (!(this.textBox7.Text == "659"))
        return;
      this.textBox8.Text = this.GetIndexByComboBox(this.CbSubType4.Text).ToString();
    }

    private void CbSubType4_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.CbSubType4.BackColor = Color.Pink;
      this.textBox8.BackColor = Color.Pink;
    }

    private void CbSubType5_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (!(this.textBox7.Text == "660"))
        return;
      this.textBox8.Text = this.GetIndexByComboBox(this.CbSubType5.Text).ToString();
    }

    private void CbSubType5_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.CbSubType5.BackColor = Color.Pink;
      this.textBox8.BackColor = Color.Pink;
    }

    private void CbSubType6_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (!(this.textBox7.Text == "767"))
        return;
      this.textBox8.Text = this.GetIndexByComboBox(this.CbSubType6.Text).ToString();
    }

    private void CbSubType6_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.CbSubType6.BackColor = Color.Pink;
      this.textBox8.BackColor = Color.Pink;
    }

    private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.namee = this.StringFromLanguage();
      if (this.listBox1.SelectedIndex != -1)
        this.textBox1.Text = this.GetIndex().ToString();
      string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, " select * from t_factory_item WHERE a_index ='" + this.textBox1.Text + "';", new string[12]
      {
        "a_index",
        this.namee ?? "",
        "a_job",
        "a_enable",
        "a_seal_type",
        "a_item_type",
        "a_item_idx",
        "a_make_exp",
        "a_need_exp",
        "a_nas",
        "a_stuff",
        "a_stuff_cnt"
      });
      this.textBox1.Text = strArray[0];
      this.textBox2.Text = strArray[3];
      this.textBox3.Text = strArray[1];
      this.textBox4.Text = strArray[2];
      this.textBox7.Text = strArray[4];
      this.textBox8.Text = strArray[5];
      this.textBox5.Text = strArray[7];
      this.textBox6.Text = strArray[8];
      this.textBox9.Text = strArray[9];
      this.ItemID.Text = strArray[6];
      this.dgItems.Rows.Clear();
      this.LoadDG();
      this.SelectBoxes();
    }

    public void LoadDG()
    {
      string str1 = "SELECT a_index, a_stuff, a_stuff_cnt FROM t_factory_item WHERE a_index ='" + this.textBox1.Text + "'";
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
        this.lArrayItemID = new List<string>();
        this.lArrayCout = new List<string>();
        foreach (string str5 in strArray1)
        {
          strArray3[index1] = str5;
          this.lArrayItemID.Add(str5);
          ++index1;
        }
        foreach (string str6 in strArray2)
        {
          strArray4[index2] = str6;
          this.lArrayCout.Add(str6);
          ++index2;
        }
        int num = 5;
        for (int index3 = 0; index3 < num; ++index3)
          this.dgItems.Rows.Add((object) str2, (object) (index3 + 1), (object) this.lArrayItemID[index3], (object) this.databaseHandle.IconFast(Convert.ToInt32(this.lArrayItemID[index3])), (object) this.databaseHandle.ItemNameFast(Convert.ToInt32(this.lArrayItemID[index3])), (object) this.lArrayCout[index3]);
      }
      mySqlConnection.Close();
    }

    private void btnSaveSelected_Click(object sender, EventArgs e)
    {
      int index1 = this.dgItems.CurrentRow.Index;
      DataGridViewRow row = this.dgItems.Rows[this.dgItems.CurrentRow.Index];
      string str1 = Convert.ToString(row.Cells["ID"].Value);
      string s = Convert.ToString(row.Cells["StuffIndex"].Value);
      string str2 = Convert.ToString(row.Cells["ItemType"].Value);
      string str3 = Convert.ToString(row.Cells["ItemCount"].Value);
      int index2 = int.Parse(s) - 1;
      this.lArrayCout[index2] = str3;
      this.lArrayItemID[index2] = str2;
      string str4 = "";
      string str5 = "";
      int count = this.lArrayItemID.Count;
      for (int index3 = 0; index3 < count; ++index3)
        str4 = index3 != count - 1 ? str4 + this.lArrayItemID[index3].ToString() + " " : str4 + this.lArrayItemID[index3].ToString() + " ";
      for (int index4 = 0; index4 < count; ++index4)
        str5 = index4 != count - 1 ? str5 + this.lArrayCout[index4].ToString() + " " : str5 + this.lArrayCout[index4].ToString() + " ";
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_factory_item SET a_stuff = '" + str4 + "',a_stuff_cnt = '" + str5 + "' WHERE a_index = '" + str1 + "'");
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
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_factory_item SET a_enable = '" + this.textBox2.Text + "', " + this.namee + " = '" + this.textBox3.Text + "', a_job = '" + this.textBox4.Text + "', a_seal_type = '" + this.textBox7.Text + "', a_item_type = '" + this.textBox8.Text + "', a_item_idx = '" + this.ItemID.Text + "', a_make_exp = '" + this.textBox5.Text + "', a_need_exp = '" + this.textBox6.Text + "', a_nas = '" + this.textBox9.Text + "' WHERE a_index = '" + this.textBox1.Text + "'");
      int selectedIndex = this.listBox1.SelectedIndex;
      this.LoadListBox();
      this.listBox1.SelectedIndex = selectedIndex;
    }

    private void button1_Click(object sender, EventArgs e)
    {
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_factory_item (" + this.namee + " , a_job, a_enable, a_seal_type, a_item_type, a_item_idx, a_make_exp, a_need_exp, a_nas, a_stuff, a_stuff_cnt) VALUES('NewItem','0','1','660','6','3775','1','1','100','-1 -1 -1 -1 -1' ,'0 0 0 0 0')");
      this.LoadListBox();
      this.listBox1.SelectedIndex = this.listBox1.Items.Count - 1;
    }

    private void button3_Click(object sender, EventArgs e)
    {
      int selectedIndex = this.listBox1.SelectedIndex;
      if (MessageBox.Show("Do you want Delete Index " + (this.listBox1.SelectedIndex + 1).ToString() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_factory_item WHERE a_index = '" + this.textBox1.Text + "'");
      this.LoadListBox();
      this.listBox1.SelectedIndex = selectedIndex - 1;
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

    private void exportlodToolStripMenuItem_Click(object sender, EventArgs e)
    {
      this.exportLodHandle.ExportMakeItem_V4();
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

    private void ItemID_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox7.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.ItemID.Text.Trim()));
      this.textBox3.Text = this.databaseHandle.ItemNameFast(int.Parse(this.ItemID.Text.Trim()));
    }

    private void InitializeComponent()
    {
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (MakeItemEditor));
      this.menuStrip1 = new MenuStrip();
      this.fileExportToolStripMenuItem = new ToolStripMenuItem();
      this.exportlodToolStripMenuItem = new ToolStripMenuItem();
      this.groupBox3 = new GroupBox();
      this.button5 = new Button();
      this.button3 = new Button();
      this.button1 = new Button();
      this.listBox1 = new ListBox();
      this.button2 = new Button();
      this.groupBox1 = new GroupBox();
      this.label10 = new Label();
      this.textBox9 = new TextBox();
      this.label7 = new Label();
      this.textBox6 = new TextBox();
      this.label5 = new Label();
      this.textBox5 = new TextBox();
      this.comboBox2 = new ComboBox();
      this.groupBox2 = new GroupBox();
      this.CbSubType6 = new ComboBox();
      this.CbSubType5 = new ComboBox();
      this.CbSubType4 = new ComboBox();
      this.CbSubtype3 = new ComboBox();
      this.CbSubtype2 = new ComboBox();
      this.CbSubtype1 = new ComboBox();
      this.comboBox1 = new ComboBox();
      this.textBox7 = new TextBox();
      this.label8 = new Label();
      this.textBox8 = new TextBox();
      this.label9 = new Label();
      this.pictureBox7 = new PictureBox();
      this.button4 = new Button();
      this.ItemID = new TextBox();
      this.label6 = new Label();
      this.cbEnabled = new CheckBox();
      this.label4 = new Label();
      this.label3 = new Label();
      this.label2 = new Label();
      this.textBox4 = new TextBox();
      this.label1 = new Label();
      this.textBox3 = new TextBox();
      this.textBox1 = new TextBox();
      this.textBox2 = new TextBox();
      this.groupBox4 = new GroupBox();
      this.dgItems = new DataGridView();
      this.ID = new DataGridViewTextBoxColumn();
      this.StuffIndex = new DataGridViewTextBoxColumn();
      this.ItemType = new DataGridViewTextBoxColumn();
      this.Icon = new DataGridViewImageColumn();
      this.ItemName = new DataGridViewTextBoxColumn();
      this.ItemCount = new DataGridViewTextBoxColumn();
      this.toolStrip2 = new ToolStrip();
      this.btnSaveSelected = new ToolStripButton();
      this.toolStripSeparator1 = new ToolStripSeparator();
      this.toolStripSeparator6 = new ToolStripSeparator();
      this.Reset = new ToolStripSplitButton();
      this.menuStrip1.SuspendLayout();
      this.groupBox3.SuspendLayout();
      this.groupBox1.SuspendLayout();
      this.groupBox2.SuspendLayout();
      ((ISupportInitialize) this.pictureBox7).BeginInit();
      this.groupBox4.SuspendLayout();
      ((ISupportInitialize) this.dgItems).BeginInit();
      this.toolStrip2.SuspendLayout();
      this.SuspendLayout();
      this.menuStrip1.AllowMerge = false;
      this.menuStrip1.BackColor = SystemColors.ButtonHighlight;
      this.menuStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.fileExportToolStripMenuItem
      });
      this.menuStrip1.Location = new Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new Size(831, 24);
      this.menuStrip1.TabIndex = 0;
      this.menuStrip1.Text = "menuStrip1";
      this.fileExportToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.exportlodToolStripMenuItem
      });
      this.fileExportToolStripMenuItem.Name = "fileExportToolStripMenuItem";
      this.fileExportToolStripMenuItem.Size = new Size(74, 20);
      this.fileExportToolStripMenuItem.Text = "File Export";
      this.exportlodToolStripMenuItem.Name = "exportlodToolStripMenuItem";
      this.exportlodToolStripMenuItem.Size = new Size(184, 22);
      this.exportlodToolStripMenuItem.Text = "Export MakeItem.lod";
      this.exportlodToolStripMenuItem.Click += new EventHandler(this.exportlodToolStripMenuItem_Click);
      this.groupBox3.Controls.Add((Control) this.button5);
      this.groupBox3.Controls.Add((Control) this.button3);
      this.groupBox3.Controls.Add((Control) this.button1);
      this.groupBox3.Controls.Add((Control) this.listBox1);
      this.groupBox3.Location = new Point(12, 27);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Size = new Size(237, 537);
      this.groupBox3.TabIndex = 32;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "Set";
      this.button5.FlatStyle = FlatStyle.Flat;
      this.button5.Location = new Point(89, 508);
      this.button5.Name = "button5";
      this.button5.Size = new Size(75, 23);
      this.button5.TabIndex = 46;
      this.button5.Text = "Add Copy";
      this.button5.UseVisualStyleBackColor = true;
      this.button5.Click += new EventHandler(this.button5_Click);
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
      this.button2.Location = new Point(727, 535);
      this.button2.Name = "button2";
      this.button2.Size = new Size(77, 23);
      this.button2.TabIndex = 45;
      this.button2.Text = "Save";
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.groupBox1.Controls.Add((Control) this.label10);
      this.groupBox1.Controls.Add((Control) this.textBox9);
      this.groupBox1.Controls.Add((Control) this.label7);
      this.groupBox1.Controls.Add((Control) this.textBox6);
      this.groupBox1.Controls.Add((Control) this.label5);
      this.groupBox1.Controls.Add((Control) this.textBox5);
      this.groupBox1.Controls.Add((Control) this.comboBox2);
      this.groupBox1.Controls.Add((Control) this.groupBox2);
      this.groupBox1.Controls.Add((Control) this.pictureBox7);
      this.groupBox1.Controls.Add((Control) this.button4);
      this.groupBox1.Controls.Add((Control) this.ItemID);
      this.groupBox1.Controls.Add((Control) this.label6);
      this.groupBox1.Controls.Add((Control) this.cbEnabled);
      this.groupBox1.Controls.Add((Control) this.label4);
      this.groupBox1.Controls.Add((Control) this.label3);
      this.groupBox1.Controls.Add((Control) this.label2);
      this.groupBox1.Controls.Add((Control) this.textBox4);
      this.groupBox1.Controls.Add((Control) this.label1);
      this.groupBox1.Controls.Add((Control) this.textBox3);
      this.groupBox1.Controls.Add((Control) this.textBox1);
      this.groupBox1.Controls.Add((Control) this.textBox2);
      this.groupBox1.Location = new Point((int) byte.MaxValue, 27);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(565, 190);
      this.groupBox1.TabIndex = 33;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Attributes";
      this.label10.AutoSize = true;
      this.label10.Location = new Point(46, 149);
      this.label10.Name = "label10";
      this.label10.Size = new Size(29, 13);
      this.label10.TabIndex = 101;
      this.label10.Text = "Nas:";
      this.textBox9.BorderStyle = BorderStyle.FixedSingle;
      this.textBox9.Location = new Point(81, 147);
      this.textBox9.Name = "textBox9";
      this.textBox9.Size = new Size(164, 20);
      this.textBox9.TabIndex = 100;
      this.label7.AutoSize = true;
      this.label7.Location = new Point(15, 121);
      this.label7.Name = "label7";
      this.label7.Size = new Size(60, 13);
      this.label7.TabIndex = 99;
      this.label7.Text = "Need EXP:";
      this.textBox6.BorderStyle = BorderStyle.FixedSingle;
      this.textBox6.Location = new Point(81, 119);
      this.textBox6.Name = "textBox6";
      this.textBox6.Size = new Size(164, 20);
      this.textBox6.TabIndex = 98;
      this.label5.AutoSize = true;
      this.label5.Location = new Point(44, 92);
      this.label5.Name = "label5";
      this.label5.Size = new Size(31, 13);
      this.label5.TabIndex = 97;
      this.label5.Text = "EXP:";
      this.textBox5.BorderStyle = BorderStyle.FixedSingle;
      this.textBox5.Location = new Point(81, 90);
      this.textBox5.Name = "textBox5";
      this.textBox5.Size = new Size(164, 20);
      this.textBox5.TabIndex = 96;
      this.comboBox2.FlatStyle = FlatStyle.Flat;
      this.comboBox2.FormattingEnabled = true;
      this.comboBox2.Location = new Point(48, 47);
      this.comboBox2.Name = "comboBox2";
      this.comboBox2.Size = new Size(156, 21);
      this.comboBox2.TabIndex = 95;
      this.comboBox2.SelectedIndexChanged += new EventHandler(this.comboBox2_SelectedIndexChanged);
      this.comboBox2.SelectionChangeCommitted += new EventHandler(this.comboBox2_SelectionChangeCommitted);
      this.groupBox2.Controls.Add((Control) this.CbSubType6);
      this.groupBox2.Controls.Add((Control) this.CbSubType5);
      this.groupBox2.Controls.Add((Control) this.CbSubType4);
      this.groupBox2.Controls.Add((Control) this.CbSubtype3);
      this.groupBox2.Controls.Add((Control) this.CbSubtype2);
      this.groupBox2.Controls.Add((Control) this.CbSubtype1);
      this.groupBox2.Controls.Add((Control) this.comboBox1);
      this.groupBox2.Controls.Add((Control) this.textBox7);
      this.groupBox2.Controls.Add((Control) this.label8);
      this.groupBox2.Controls.Add((Control) this.textBox8);
      this.groupBox2.Controls.Add((Control) this.label9);
      this.groupBox2.Location = new Point(264, 14);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new Size(291, 91);
      this.groupBox2.TabIndex = 94;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "Factory Type";
      this.CbSubType6.FlatStyle = FlatStyle.Flat;
      this.CbSubType6.FormattingEnabled = true;
      this.CbSubType6.Location = new Point(70, 54);
      this.CbSubType6.Name = "CbSubType6";
      this.CbSubType6.Size = new Size(173, 21);
      this.CbSubType6.TabIndex = 48;
      this.CbSubType6.SelectedIndexChanged += new EventHandler(this.CbSubType6_SelectedIndexChanged);
      this.CbSubType6.SelectionChangeCommitted += new EventHandler(this.CbSubType6_SelectionChangeCommitted);
      this.CbSubType5.FlatStyle = FlatStyle.Flat;
      this.CbSubType5.FormattingEnabled = true;
      this.CbSubType5.Location = new Point(70, 54);
      this.CbSubType5.Name = "CbSubType5";
      this.CbSubType5.Size = new Size(173, 21);
      this.CbSubType5.TabIndex = 47;
      this.CbSubType5.SelectedIndexChanged += new EventHandler(this.CbSubType5_SelectedIndexChanged);
      this.CbSubType5.SelectionChangeCommitted += new EventHandler(this.CbSubType5_SelectionChangeCommitted);
      this.CbSubType4.FlatStyle = FlatStyle.Flat;
      this.CbSubType4.FormattingEnabled = true;
      this.CbSubType4.Location = new Point(70, 54);
      this.CbSubType4.Name = "CbSubType4";
      this.CbSubType4.Size = new Size(173, 21);
      this.CbSubType4.TabIndex = 45;
      this.CbSubType4.SelectedIndexChanged += new EventHandler(this.CbSubType4_SelectedIndexChanged);
      this.CbSubType4.SelectionChangeCommitted += new EventHandler(this.CbSubType4_SelectionChangeCommitted);
      this.CbSubtype3.FlatStyle = FlatStyle.Flat;
      this.CbSubtype3.FormattingEnabled = true;
      this.CbSubtype3.Location = new Point(70, 54);
      this.CbSubtype3.Name = "CbSubtype3";
      this.CbSubtype3.Size = new Size(173, 21);
      this.CbSubtype3.TabIndex = 44;
      this.CbSubtype3.SelectedIndexChanged += new EventHandler(this.CbSubtype3_SelectedIndexChanged);
      this.CbSubtype3.SelectionChangeCommitted += new EventHandler(this.CbSubtype3_SelectionChangeCommitted);
      this.CbSubtype2.FlatStyle = FlatStyle.Flat;
      this.CbSubtype2.FormattingEnabled = true;
      this.CbSubtype2.Location = new Point(70, 54);
      this.CbSubtype2.Name = "CbSubtype2";
      this.CbSubtype2.Size = new Size(173, 21);
      this.CbSubtype2.TabIndex = 43;
      this.CbSubtype2.SelectedIndexChanged += new EventHandler(this.CbSubtype2_SelectedIndexChanged);
      this.CbSubtype2.SelectionChangeCommitted += new EventHandler(this.CbSubtype2_SelectionChangeCommitted);
      this.CbSubtype1.FlatStyle = FlatStyle.Flat;
      this.CbSubtype1.FormattingEnabled = true;
      this.CbSubtype1.Location = new Point(70, 54);
      this.CbSubtype1.Name = "CbSubtype1";
      this.CbSubtype1.Size = new Size(173, 21);
      this.CbSubtype1.TabIndex = 42;
      this.CbSubtype1.SelectedIndexChanged += new EventHandler(this.CbSubtype1_SelectedIndexChanged);
      this.CbSubtype1.SelectionChangeCommitted += new EventHandler(this.CbSubtype1_SelectionChangeCommitted);
      this.comboBox1.FlatStyle = FlatStyle.Flat;
      this.comboBox1.FormattingEnabled = true;
      this.comboBox1.Location = new Point(70, 20);
      this.comboBox1.Name = "comboBox1";
      this.comboBox1.Size = new Size(173, 21);
      this.comboBox1.TabIndex = 35;
      this.comboBox1.SelectedIndexChanged += new EventHandler(this.comboBox1_SelectedIndexChanged);
      this.comboBox1.SelectionChangeCommitted += new EventHandler(this.comboBox1_SelectionChangeCommitted);
      this.textBox7.BorderStyle = BorderStyle.FixedSingle;
      this.textBox7.Location = new Point((int) byte.MaxValue, 22);
      this.textBox7.Name = "textBox7";
      this.textBox7.Size = new Size(30, 20);
      this.textBox7.TabIndex = 2;
      this.label8.AutoSize = true;
      this.label8.Location = new Point(14, 56);
      this.label8.Name = "label8";
      this.label8.Size = new Size(53, 13);
      this.label8.TabIndex = 9;
      this.label8.Text = "SubType:";
      this.textBox8.BorderStyle = BorderStyle.FixedSingle;
      this.textBox8.Location = new Point((int) byte.MaxValue, 56);
      this.textBox8.Name = "textBox8";
      this.textBox8.Size = new Size(30, 20);
      this.textBox8.TabIndex = 3;
      this.label9.AutoSize = true;
      this.label9.Location = new Point(14, 22);
      this.label9.Name = "label9";
      this.label9.Size = new Size(34, 13);
      this.label9.TabIndex = 8;
      this.label9.Text = "Type:";
      this.pictureBox7.Location = new Point(279, 117);
      this.pictureBox7.Name = "pictureBox7";
      this.pictureBox7.Size = new Size(32, 32);
      this.pictureBox7.TabIndex = 93;
      this.pictureBox7.TabStop = false;
      this.button4.BackgroundImageLayout = ImageLayout.None;
      this.button4.Image = (Image) Resources.search__5_;
      this.button4.Location = new Point(460, 119);
      this.button4.Name = "button4";
      this.button4.Size = new Size(27, 25);
      this.button4.TabIndex = 92;
      this.button4.UseVisualStyleBackColor = true;
      this.button4.Click += new EventHandler(this.button4_Click);
      this.ItemID.Enabled = false;
      this.ItemID.Location = new Point(362, 121);
      this.ItemID.Multiline = true;
      this.ItemID.Name = "ItemID";
      this.ItemID.Size = new Size(92, 21);
      this.ItemID.TabIndex = 91;
      this.ItemID.TextChanged += new EventHandler(this.ItemID_TextChanged);
      this.label6.AutoSize = true;
      this.label6.Location = new Point(317, 124);
      this.label6.Name = "label6";
      this.label6.Size = new Size(44, 13);
      this.label6.TabIndex = 90;
      this.label6.Text = "Item ID:";
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
      this.label4.Location = new Point(15, 50);
      this.label4.Name = "label4";
      this.label4.Size = new Size(27, 13);
      this.label4.TabIndex = 41;
      this.label4.Text = "Job:";
      this.label3.AutoSize = true;
      this.label3.Location = new Point(270, 157);
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
      this.textBox4.BorderStyle = BorderStyle.FixedSingle;
      this.textBox4.Location = new Point(210, 47);
      this.textBox4.Name = "textBox4";
      this.textBox4.Size = new Size(35, 20);
      this.textBox4.TabIndex = 38;
      this.label1.AutoSize = true;
      this.label1.Location = new Point(6, 21);
      this.label1.Name = "label1";
      this.label1.Size = new Size(36, 13);
      this.label1.TabIndex = 38;
      this.label1.Text = "Index:";
      this.textBox3.BorderStyle = BorderStyle.FixedSingle;
      this.textBox3.Location = new Point(312, 155);
      this.textBox3.Name = "textBox3";
      this.textBox3.Size = new Size(210, 20);
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
      this.groupBox4.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left;
      this.groupBox4.Controls.Add((Control) this.dgItems);
      this.groupBox4.Controls.Add((Control) this.toolStrip2);
      this.groupBox4.Location = new Point(264, 223);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Size = new Size(462, 303);
      this.groupBox4.TabIndex = 44;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "Stuff";
      this.dgItems.AllowUserToAddRows = false;
      this.dgItems.AllowUserToDeleteRows = false;
      this.dgItems.BackgroundColor = SystemColors.Control;
      this.dgItems.BorderStyle = BorderStyle.None;
      this.dgItems.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dgItems.Columns.AddRange((DataGridViewColumn) this.ID, (DataGridViewColumn) this.StuffIndex, (DataGridViewColumn) this.ItemType, (DataGridViewColumn) this.Icon, (DataGridViewColumn) this.ItemName, (DataGridViewColumn) this.ItemCount);
      this.dgItems.Dock = DockStyle.Fill;
      this.dgItems.EnableHeadersVisualStyles = false;
      this.dgItems.Location = new Point(3, 16);
      this.dgItems.Name = "dgItems";
      this.dgItems.RowHeadersVisible = false;
      this.dgItems.RowTemplate.Height = 25;
      this.dgItems.ScrollBars = ScrollBars.None;
      this.dgItems.Size = new Size(456, 259);
      this.dgItems.TabIndex = 0;
      this.ID.HeaderText = "ID";
      this.ID.Name = "ID";
      this.ID.Visible = false;
      this.ID.Width = 60;
      this.StuffIndex.HeaderText = "No.";
      this.StuffIndex.Name = "StuffIndex";
      this.StuffIndex.Width = 50;
      this.ItemType.HeaderText = "ItemId";
      this.ItemType.Name = "ItemType";
      this.ItemType.Width = 70;
      this.Icon.HeaderText = "Icon";
      this.Icon.Name = "Icon";
      this.Icon.Width = 32;
      this.ItemName.HeaderText = "Name";
      this.ItemName.Name = "ItemName";
      this.ItemName.Width = 225;
      this.ItemCount.HeaderText = "Count";
      this.ItemCount.Name = "ItemCount";
      this.ItemCount.Width = 70;
      this.toolStrip2.Dock = DockStyle.Bottom;
      this.toolStrip2.GripStyle = ToolStripGripStyle.Hidden;
      this.toolStrip2.Items.AddRange(new ToolStripItem[4]
      {
        (ToolStripItem) this.btnSaveSelected,
        (ToolStripItem) this.toolStripSeparator1,
        (ToolStripItem) this.toolStripSeparator6,
        (ToolStripItem) this.Reset
      });
      this.toolStrip2.Location = new Point(3, 275);
      this.toolStrip2.Name = "toolStrip2";
      this.toolStrip2.Size = new Size(456, 25);
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
      this.Reset.BackColor = SystemColors.Control;
      this.Reset.DisplayStyle = ToolStripItemDisplayStyle.Text;
      this.Reset.Image = (Image) componentResourceManager.GetObject("Reset.Image");
      this.Reset.ImageTransparentColor = Color.Magenta;
      this.Reset.Name = "Reset";
      this.Reset.Size = new Size(51, 22);
      this.Reset.Text = "Reset";
      this.Reset.ButtonClick += new EventHandler(this.Reset_ButtonClick);
      this.ClientSize = new Size(831, 576);
      this.Controls.Add((Control) this.groupBox4);
      this.Controls.Add((Control) this.groupBox1);
      this.Controls.Add((Control) this.groupBox3);
      this.Controls.Add((Control) this.button2);
      this.Controls.Add((Control) this.menuStrip1);
      this.MainMenuStrip = this.menuStrip1;
      this.Name = nameof (MakeItemEditor);
      this.Text = "MakeItem Editor";
      this.Load += new EventHandler(this.Exporter_Option_Load);
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.groupBox3.ResumeLayout(false);
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.groupBox2.ResumeLayout(false);
      this.groupBox2.PerformLayout();
      ((ISupportInitialize) this.pictureBox7).EndInit();
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

    private void button4_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.ItemID.Text = itemPicker.ItemIndex.ToString();
    }

    private void button5_Click(object sender, EventArgs e)
    {
      int selectedIndex = this.listBox1.SelectedIndex;
      if (MessageBox.Show("Do you want Copy Index " + (this.listBox1.SelectedIndex + 1).ToString() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      if (this.ItemID.Text.Trim().Length <= 0)
      {
        int num1 = (int) MessageBox.Show("No data to select", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DROP TABLE IF EXISTS tempTable;CREATE TEMPORARY TABLE tempTable ENGINE=MEMORY SELECT * FROM t_factory_item WHERE a_index=" + this.textBox1.Text + ";SELECT a_index FROM tempTable;UPDATE tempTable SET a_index=(SELECT a_index from t_factory_item ORDER BY a_index DESC LIMIT 1)+1; SELECT a_index FROM tempTable;INSERT INTO t_factory_item SELECT * FROM tempTable;");
        int num2 = (int) MessageBox.Show("Successful copy", "Completed", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
        this.LoadListBox();
        this.listBox1.SelectedIndex = this.listBox1.Items.Count - 1;
      }
    }

    private void Reset_ButtonClick(object sender, EventArgs e)
    {
      int selectedIndex = this.listBox1.SelectedIndex;
      int num = this.listBox1.SelectedIndex + 1;
      string str = Convert.ToString(this.dgItems.Rows[this.dgItems.CurrentRow.Index].Cells["ID"].Value);
      if (MessageBox.Show("Do you want Reset " + num.ToString() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_factory_item SET a_stuff = '-1 -1 -1 -1 -1', a_stuff_cnt = '0 0 0 0 0'  WHERE a_index = '" + str + "'");
      this.dgItems.Rows.Clear();
      this.LoadDG();
    }
  }
}
