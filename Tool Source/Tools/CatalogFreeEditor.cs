// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.CatalogFreeEditor
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
  public class CatalogFreeEditor : Form
  {
    public static Connection connection = new Connection();
    private string Host = CatalogFreeEditor.connection.Settings.SqlHost;
    private string User = CatalogFreeEditor.connection.Settings.SqlUser;
    private string Password = CatalogFreeEditor.connection.Settings.SqlPassword;
    private string Database = CatalogFreeEditor.connection.Settings.SqlDatabase;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    private Encoding encoding = Encoding.GetEncoding("ISO-8859-1");
    private ASCIIEncoding _Enc = new ASCIIEncoding();
    public string _ClientPath = CatalogFreeEditor.connection.Settings.ClientPath;
    private string Episode = ItemEditor2.connection.Settings.Episode;
    public List<string> MenuList = new List<string>();
    public List<string> MenuListSearch = new List<string>();
    public string rowName = "a_ctid";
    public string CategoryHide = "0";
    public string SortCategoryValue = "-1";
    public string SwitchCheckBox = "-1";
    public string[] menuArray = new string[2]
    {
      "a_ctid",
      "a_ctname"
    };
    private string language = ItemEditor2.connection.Settings.Language;
    public string[] menuArrayGER = new string[2]
    {
      "a_ctid",
      "a_ctname_ger"
    };
    public string[] menuArrayRUS = new string[2]
    {
      "a_ctid",
      "a_ctname_rus"
    };
    public string[] menuArrayESP = new string[2]
    {
      "a_ctid",
      "a_ctname_spn"
    };
    public string[] menuArrayTHA = new string[2]
    {
      "a_ctid",
      "a_ctname_tld"
    };
    public string[] menuArrayUSA = new string[2]
    {
      "a_ctid",
      "a_ctname_usa"
    };
    public string[] menuArrayBRA = new string[2]
    {
      "a_ctid",
      "a_ctname_brz"
    };
    private int tmpFlag = 0;
    private int tmpLimit = 0;
    private ExportLodHandle exportLodHandle = new ExportLodHandle();
    private IContainer components = (IContainer) null;
    public string name;
    public int index;
    public string test2;
    private MenuStrip menuStrip1;
    private ToolStripMenuItem fileExportToolStripMenuItem;
    private ToolStripMenuItem exportlodToolStripMenuItem;
    private ListBox listBox1;
    private TextBox textBox1;
    private TextBox textBox2;
    private TextBox textBox3;
    private TextBox textBox4;
    private TextBox textBox5;
    private TextBox textBox6;
    private Label label1;
    private Label label2;
    private Label label3;
    private Label label5;
    private Label label6;
    private TextBox textBox7;
    private TextBox textBox8;
    private Label label8;
    private Label label9;
    private TextBox textBox9;
    private TextBox textBox10;
    private TextBox textBox11;
    private Label label4;
    private Label label10;
    private Label label11;
    private Label label12;
    private GroupBox groupBox1;
    private GroupBox groupBox2;
    private GroupBox groupBox4;
    private DataGridView dgItems;
    private ToolStrip toolStrip2;
    private ToolStripButton btnAddItems;
    private ToolStripSeparator toolStripSeparator6;
    private ToolStripButton btnSaveSelected;
    private GroupBox groupBox3;
    private Button button1;
    private Button button3;
    private GroupBox groupBox5;
    private Label label7;
    private TextBox textBox12;
    private DataGridViewImageColumn Column7;
    private DataGridViewTextBoxColumn Column1;
    private DataGridViewTextBoxColumn Column2;
    private DataGridViewTextBoxColumn Column3;
    private DataGridViewTextBoxColumn Column4;
    private DataGridViewTextBoxColumn Column5;
    private DataGridViewTextBoxColumn Column6;
    private DataGridViewTextBoxColumn Column8;
    private DataGridViewTextBoxColumn Column9;
    private Button button2;
    private ToolStripSeparator toolStripSeparator1;
    private GroupBox groupBox6;
    private CheckedListBox clbFlagTest;
    private Button btnShowCat1;
    private Button button4;
    private Button button5;
    private Button button6;
    private Button button7;
    private Button button8;
    private Button button9;
    private GroupBox groupBox7;
    private Button button10;
    private StatusStrip statusStrip1;
    private ToolStripStatusLabel toolStripStatusLabel1;
    private GroupBox groupBox8;
    private CheckedListBox checkedListBox1;
    private GroupBox groupBox9;
    private CheckedListBox checkedListBox2;
    private Button button11;
    private CheckBox checkBox1;
    private Label label13;
    private ToolStripButton btnDelete;
    private ToolStripButton btnUpdateName;
    private Button button12;
    private ToolStripSeparator toolStripSeparator2;
    private TextBox tbLimit;
    private string namee;
    private Label label113;
    private Label lblLang;
    private CheckBox cbEnabled;
    private Button button13;
    public string descrr;

    private void LoadLangAtStartup()
    {
      if (this.language == "GER")
        this.lblLang.Text = "German";
      else if (this.language == "POL")
        this.lblLang.Text = "Polish";
      else if (this.language == "BRA")
        this.lblLang.Text = "Brasilian";
      else if (this.language == "RUS")
        this.lblLang.Text = "Russian";
      else if (this.language == "FRA")
        this.lblLang.Text = "French";
      else if (this.language == "ESP")
        this.lblLang.Text = "Spanish";
      else if (this.language == "MEX")
        this.lblLang.Text = "Mex";
      else if (this.language == "THA")
        this.lblLang.Text = "Thai";
      else if (this.language == "ITA")
        this.lblLang.Text = "Italian";
      else if (this.language == "USA")
        this.lblLang.Text = "English";
      else
        this.lblLang.Text = "";
    }

    public string StringFromLanguage()
    {
      if (this.language == "GER")
      {
        this.namee = "a_ctname_ger";
        return this.namee;
      }
      if (this.language == "RUS")
      {
        this.namee = "a_ctname_rus";
        return this.namee;
      }
      if (this.language == "ESP")
      {
        this.namee = "a_ctname_spn";
        return this.namee;
      }
      if (this.language == "BRA")
      {
        this.namee = "a_ctname_brz";
        return this.namee;
      }
      if (this.language == "THA")
      {
        this.namee = "a_ctname_tld";
        return this.namee;
      }
      if (!(this.language == "USA"))
        return (string) null;
      this.namee = "a_ctname_usa";
      return this.namee;
    }

    public string DescrFromLanguage()
    {
      if (this.language == "GER")
      {
        this.descrr = "a_ctdesc_ger";
        return this.descrr;
      }
      if (this.language == "POL")
      {
        this.descrr = "a_ctdesc_pld";
        return this.descrr;
      }
      if (this.language == "BRA")
      {
        this.descrr = "a_ctdesc_brz";
        return this.descrr;
      }
      if (this.language == "RUS")
      {
        this.descrr = "a_ctdesc_rus";
        return this.descrr;
      }
      if (this.language == "FRA")
      {
        this.descrr = "a_ctdesc_frc";
        return this.descrr;
      }
      if (this.language == "ESP")
      {
        this.descrr = "a_ctdesc_spn";
        return this.descrr;
      }
      if (this.language == "THA")
      {
        this.descrr = "a_ctdesc_tld";
        return this.descrr;
      }
      if (!(this.language == "USA"))
        return (string) null;
      this.descrr = "a_ctdesc_usa";
      return this.descrr;
    }

    public CatalogFreeEditor() => this.InitializeComponent();

    public void SearchList(string searchString)
    {
      string Query = "select a_ctid, a_ctname from t_catalogfree WHERE a_ctname_tld LIKE '%" + searchString + "%' ORDER BY a_ctid;";
      if (this.language == "THA")
      {
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayTHA, this.Host, this.User, this.Password, this.Database, Query);
      }
      else
      {
        searchString = searchString.Replace("\\", "\\\\").Replace("'", "\\'");
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, "select a_ctid, a_ctname from t_catalogfree WHERE a_ctname LIKE '%" + searchString + "%' ORDER BY a_ctid;");
      }
    }

    public void SortCategory(string category)
    {
      string Query = "select a_ctid, a_ctname_tld from t_catalogfree WHERE a_category ='" + category + "'";
      if (this.language == "THA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayTHA, this.Host, this.User, this.Password, this.Database, Query);
      else
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, "select a_ctid, a_ctname from t_catalogfree WHERE a_category ='" + category + "'");
    }

    public void LoadListBox()
    {
      this.listBox1.SelectedIndex = -1;
      this.MenuList.Clear();
      this.namee = this.StringFromLanguage();
      string Query = "select a_ctid, " + this.namee + " from t_catalogfree ORDER BY a_ctid;";
      if (this.language == "GER")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayGER, this.Host, this.User, this.Password, this.Database, Query);
      else if (this.language == "RUS")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayRUS, this.Host, this.User, this.Password, this.Database, Query);
      else if (this.language == "ESP")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayESP, this.Host, this.User, this.Password, this.Database, Query);
      else if (this.language == "BRA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayBRA, this.Host, this.User, this.Password, this.Database, Query);
      else if (this.language == "THA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayTHA, this.Host, this.User, this.Password, this.Database, Query);
      else if (this.language == "USA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayUSA, this.Host, this.User, this.Password, this.Database, Query);
      else
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, "select a_ctid, a_ctname from t_catalogfree ORDER BY a_ctid;");
    }

    public Bitmap CropImage(Bitmap source, Rectangle section)
    {
      Bitmap bitmap = new Bitmap(section.Width, section.Height);
      Graphics.FromImage((Image) bitmap).DrawImage((Image) source, 0, 0, section, GraphicsUnit.Pixel);
      return bitmap;
    }

    private void Exporter_Catalog_Load(object sender, EventArgs e)
    {
      this.listBox1.Items.Clear();
      this.LoadStartUp();
      this.LoadListBox();
      this.LoadLangAtStartup();
    }

    public void LoadMisc()
    {
      string text1 = this.textBox3.Text;
      string text2 = this.textBox4.Text;
      for (int index = 0; index < this.checkedListBox1.Items.Count; ++index)
      {
        int num = this.checkedListBox1.FindString(text1);
        if (index == num)
          this.checkedListBox1.SetItemChecked(index, true);
      }
      for (int index = 0; index < this.checkedListBox2.Items.Count; ++index)
      {
        int num = this.checkedListBox2.FindString(text2);
        if (index == num)
          this.checkedListBox2.SetItemChecked(index, true);
      }
      this.tbLimit.Text = this.tmpLimit.ToString();
    }

    public void LoadStartUp()
    {
      this.checkedListBox1.Items.AddRange(new object[9]
      {
        (object) "0 - none",
        (object) "999 - Credit Shop",
        (object) "10000 - Hot & New",
        (object) "20000 - Platinium",
        (object) "30000 - Disposable",
        (object) "40000 - Costume",
        (object) "50000 - Pet",
        (object) "60000 - Service",
        (object) "70000 - Package"
      });
      this.checkedListBox2.Items.AddRange(new object[31]
      {
        (object) "0 - none",
        (object) "10000 - Hot & New none",
        (object) "10100 - Hot & New",
        (object) "10200 - Hot & New discount",
        (object) "10300 - Hot & New hot",
        (object) "20000 - Platinium none",
        (object) "30000 - Disposable none",
        (object) "30100 - Disposable character grow",
        (object) "30200 - Disposable ability buildup",
        (object) "30300 - Disposable potion",
        (object) "40000 - Equip none",
        (object) "40100 - Equip equipment",
        (object) "40200 - Equip buildup",
        (object) "40300 - Equip costume",
        (object) "50000 - Avatar none",
        (object) "50100 - Avatar pet",
        (object) "50200 - Avatar mercenary",
        (object) "60000 - Service none",
        (object) "60100 - Service conentience",
        (object) "60200 - Service etc",
        (object) "70000 - Package none",
        (object) "70100 - Package boosters",
        (object) "70200 - Package enhancements",
        (object) "70300 - Package potions",
        (object) "70400 - Package vanity",
        (object) "70500 - Package upgrade",
        (object) "70600 - Package pets",
        (object) "70700 - Package mercenary",
        (object) "70800 - Package convenience",
        (object) "70900 - Package others",
        (object) "90000 - Old Goods"
      });
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
      this.dgItems.Rows.Clear();
      if (this.listBox1.SelectedIndex != -1)
        this.textBox1.Text = this.GetIndex().ToString();
      string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, " select * from t_catalogfree WHERE a_ctid ='" + this.textBox1.Text + "';", new string[23]
      {
        "a_ctid",
        "a_ctname",
        "a_category",
        "a_type",
        "a_subtype",
        "a_cash",
        "a_ctdesc",
        "a_mileage",
        "a_enable",
        "a_flag",
        "a_icon",
        "a_ctname_tld",
        "a_ctdesc_tld",
        "a_ctname_usa",
        "a_ctdesc_usa",
        "a_ctname_ger",
        "a_ctdesc_ger",
        "a_ctname_spn",
        "a_ctdesc_spn",
        "a_ctname_rus",
        "a_ctdesc_rus",
        "a_ctname_brz",
        "a_ctdesc_brz"
      });
      this.textBox1.Text = strArray[0];
      this.textBox3.Text = strArray[2];
      this.textBox4.Text = strArray[3];
      this.textBox5.Text = strArray[4];
      this.textBox6.Text = strArray[5];
      this.textBox8.Text = strArray[7];
      this.textBox9.Text = strArray[8];
      this.textBox10.Text = strArray[9];
      this.textBox11.Text = strArray[10];
      this.textBox2.Text = strArray[1];
      this.textBox7.Text = strArray[6];
      if (this.language == "USA")
      {
        this.textBox2.Text = strArray[13];
        this.textBox7.Text = strArray[14];
      }
      else if (this.language == "RUS")
      {
        this.textBox2.Text = strArray[19];
        this.textBox7.Text = strArray[20];
      }
      else if (this.language == "THA")
      {
        this.textBox2.Text = strArray[11];
        this.textBox7.Text = strArray[12];
      }
      else if (this.language == "ESP")
      {
        this.textBox2.Text = strArray[17];
        this.textBox7.Text = strArray[18];
      }
      else if (this.language == "BRA")
      {
        this.textBox2.Text = strArray[21];
        this.textBox7.Text = strArray[22];
      }
      else if (this.language == "GER")
      {
        this.textBox2.Text = strArray[15];
        this.textBox7.Text = strArray[16];
      }
      else if (this.language != "GER" && this.language != "POL" && this.language != "BRA" && this.language != "RUS" && this.language != "FRA" && this.language != "ESP" && this.language != "MEX" && this.language != "THA" && this.language != "ITA" && this.language != "USA")
      {
        this.textBox2.Text = strArray[1];
        this.textBox7.Text = strArray[6];
      }
      this.ShowFlag(int.Parse(strArray[9]));
      this.ShowCategory(int.Parse(strArray[2]));
      this.dgItems.Rows.Clear();
      this.LoadDG();
      this.LoadMisc();
      this.SplitLimitFromFlag(int.Parse(strArray[9]));
    }

    private void ShowCategory(int CategoryID)
    {
    }

    private void toolStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
    {
    }

    private void button1_Click(object sender, EventArgs e)
    {
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_catalogfree DEFAULT VALUES");
      this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, "select * from t_catalogfree ORDER BY a_ctid;");
      this.listBox1.SelectedIndex = this.listBox1.Items.Count - 1;
      this.LoadListBox();
    }

    private void button3_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want to Delete Catalog ID " + this.textBox1.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      int selectedIndex = this.listBox1.SelectedIndex;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_catalogfree WHERE a_ctid = '" + this.textBox1.Text + "'");
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_ct_itemfree WHERE a_ctid = '" + this.textBox1.Text + "'");
      this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, "select * from t_catalogfree ORDER BY a_ctid;");
      this.listBox1.SelectedIndex = selectedIndex - 1;
      this.LoadListBox();
      int num = (int) new CustomMessage("Deleted").ShowDialog();
    }

    private void btnAddItems_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_ct_itemfree (a_ctid, a_item_idx, a_item_num) VALUES (" + this.textBox1.Text + "," + itemPicker.ItemIndex.ToString() + ", '1')");
      this.dgItems.Rows.Clear();
      this.LoadDG();
      this.textBox11.Text = itemPicker.ItemIndex.ToString();
    }

    public void LoadDG()
    {
      this.toolStripStatusLabel1.Text = "Load Items ...";
      string str1 = " select * from t_ct_itemfree WHERE a_ctid ='" + this.textBox1.Text + "' ORDER BY a_index;";
      string[] strArray = new string[6]
      {
        "a_ctid",
        "a_item_idx",
        "a_item_flag",
        "a_item_plus",
        "a_item_option",
        "a_item_num"
      };
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
        string str8 = mySqlDataReader.GetValue(6).ToString();
        int int32 = Convert.ToInt32(str4);
        this.dgItems.Rows.Add((object) this.databaseHandle.IconFast(int32), (object) str4, (object) this.databaseHandle.ItemNameFast(int32), (object) str8, (object) str6, (object) str7, (object) str5, (object) str2, (object) str3);
      }
      mySqlConnection.Close();
      this.toolStripStatusLabel1.Text = "Ready";
    }

    private void btnCopy_Click(object sender, EventArgs e)
    {
    }

    private void dgItems_CellContentClick(object sender, DataGridViewCellEventArgs e)
    {
    }

    private void dgItems_CellClick(object sender, DataGridViewCellEventArgs e)
    {
      if (e.RowIndex < 0)
        return;
      this.textBox11.Text = this.dgItems.Rows[e.RowIndex].Cells["Column1"].Value.ToString();
    }

    private void btnSaveSelected_Click(object sender, EventArgs e)
    {
      DataGridViewRow row = this.dgItems.Rows[this.dgItems.CurrentRow.Index];
      string str1 = Convert.ToString(row.Cells["Column1"].Value);
      Convert.ToString(row.Cells["Column2"].Value);
      string str2 = Convert.ToString(row.Cells["Column3"].Value);
      string str3 = Convert.ToString(row.Cells["Column4"].Value);
      string str4 = Convert.ToString(row.Cells["Column5"].Value);
      string str5 = Convert.ToString(row.Cells["Column6"].Value);
      string str6 = Convert.ToString(row.Cells["Column8"].Value);
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_ct_itemfree SET a_ctid = '" + Convert.ToString(row.Cells["Column9"].Value) + "', a_item_idx = '" + str1 + "', a_item_flag = '" + str5 + "', a_item_plus = '" + str3 + "', a_item_option = '" + str4 + "', a_item_num = '" + str2 + "' WHERE a_index ='" + str6 + "'");
      this.dgItems.Rows.Clear();
      this.LoadDG();
    }

    private void button2_Click(object sender, EventArgs e)
    {
      if (this.language == "THA")
      {
        this.descrr = this.DescrFromLanguage();
        this.namee = this.StringFromLanguage();
        this.textBox2.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        string str1 = this.textBox2.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        this.textBox7.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        string str2 = this.textBox7.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_catalogfree SET " + this.namee + " = '" + str1 + "', a_ctname ='" + str1 + "', a_ctdesc ='" + str2 + "', a_category = '" + this.textBox3.Text + "', a_type = '" + this.textBox4.Text + "', a_subtype = '" + this.textBox5.Text + "', a_cash = '" + this.textBox6.Text + "', " + this.descrr + " = '" + str2 + "', a_mileage = '" + this.textBox8.Text + "', a_enable = '" + this.textBox9.Text + "', a_flag = '" + this.textBox10.Text + "', a_icon = '" + this.textBox11.Text + "' WHERE a_ctid = '" + this.textBox1.Text + "'");
      }
      else if (this.language == "USA")
      {
        this.descrr = this.DescrFromLanguage();
        this.namee = this.StringFromLanguage();
        this.textBox2.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        string str3 = this.textBox2.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        this.textBox7.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        string str4 = this.textBox7.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_catalogfree SET a_ctname = '" + str3 + "', a_ctname_ger = '" + str3 + "', a_ctname_spn = '" + str3 + "', " + this.namee + " = '" + str3 + "', a_category = '" + this.textBox3.Text + "', a_type = '" + this.textBox4.Text + "', a_subtype = '" + this.textBox5.Text + "', a_cash = '" + this.textBox6.Text + "', a_ctdesc = '" + str4 + "', a_ctdesc_ger = '" + str4 + "', a_ctdesc_spn = '" + str4 + "', " + this.descrr + " = '" + str4 + "', a_mileage = '" + this.textBox8.Text + "', a_enable = '" + this.textBox9.Text + "', a_flag = '" + this.textBox10.Text + "', a_icon = '" + this.textBox11.Text + "' WHERE a_ctid = '" + this.textBox1.Text + "'");
      }
      else
      {
        this.descrr = this.DescrFromLanguage();
        this.namee = this.StringFromLanguage();
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_catalogfree SET " + this.namee + " = '" + this.textBox2.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_category = '" + this.textBox3.Text + "', a_type = '" + this.textBox4.Text + "', a_subtype = '" + this.textBox5.Text + "', a_cash = '" + this.textBox6.Text + "', " + this.descrr + " = '" + this.textBox7.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_mileage = '" + this.textBox8.Text + "', a_enable = '" + this.textBox9.Text + "', a_flag = '" + this.textBox10.Text + "', a_icon = '" + this.textBox11.Text + "' WHERE a_ctid = '" + this.textBox1.Text + "'");
      }
      int selectedIndex = this.listBox1.SelectedIndex;
      if (this.textBox12.Text != "")
        this.SearchList(this.textBox12.Text);
      else if (this.SortCategoryValue == "-1")
        this.LoadListBox();
      else
        this.SortCategory(this.SortCategoryValue);
      this.listBox1.SelectedIndex = selectedIndex;
    }

    private void exportlodToolStripMenuItem_Click(object sender, EventArgs e)
    {
      this.exportLodHandle.ExportCatalog_V4();
    }

    public bool SearchString(string s) => s.ToUpper().Contains(this.textBox12.Text.ToUpper());

    private void textBox12_TextChanged(object sender, EventArgs e)
    {
      if (this.language == "GER")
      {
        this.listBox1.DataSource = (object) this.databaseHandle.SearchListCatalog(this.textBox12.Text, this.menuArrayGER, "t_catalogfree");
      }
      else
      {
        if (this.language == "POL")
          return;
        if (this.language == "BRA")
          this.listBox1.DataSource = (object) this.databaseHandle.SearchListCatalog(this.textBox12.Text, this.menuArrayBRA, "t_catalogfree");
        else if (this.language == "RUS")
        {
          this.listBox1.DataSource = (object) this.databaseHandle.SearchListCatalog(this.textBox12.Text, this.menuArrayRUS, "t_catalogfree");
        }
        else
        {
          if (this.language == "FRA")
            return;
          if (this.language == "ESP")
          {
            this.listBox1.DataSource = (object) this.databaseHandle.SearchListCatalog(this.textBox12.Text, this.menuArrayESP, "t_catalogfree");
          }
          else
          {
            if (this.language == "MEX")
              return;
            if (this.language == "THA")
            {
              this.listBox1.DataSource = (object) this.databaseHandle.SearchListCatalog(this.textBox12.Text, this.menuArrayTHA, "t_catalogfree");
            }
            else
            {
              if (this.language == "ITA")
                return;
              if (this.language == "USA")
                this.listBox1.DataSource = (object) this.databaseHandle.SearchListCatalog(this.textBox12.Text, this.menuArrayUSA, "t_catalogfree");
              else
                this.listBox1.DataSource = (object) this.databaseHandle.SearchListCatalog(this.textBox12.Text, this.menuArray, "t_catalogfree");
            }
          }
        }
      }
    }

    private void clbFlagTest_SelectedIndexChanged(object sender, EventArgs e)
    {
      int num = 0;
      for (int index = 0; index < this.clbFlagTest.Items.Count; ++index)
      {
        if (this.clbFlagTest.GetItemChecked(index))
          num += 1 << index;
        this.textBox10.Text = num.ToString();
      }
    }

    private void ShowFlag(int flag)
    {
      for (int index = 0; index < this.clbFlagTest.Items.Count; ++index)
      {
        if ((flag & 1 << index) != 0)
          this.clbFlagTest.SetItemChecked(index, true);
        else
          this.clbFlagTest.SetItemChecked(index, false);
      }
    }

    private void clbFlagTest_MouseUp(object sender, MouseEventArgs e)
    {
      int num1 = 0;
      for (int index = 0; index < this.clbFlagTest.Items.Count; ++index)
      {
        if (this.clbFlagTest.GetItemChecked(index))
          num1 += 1 << index;
        int num2 = (int) MessageBox.Show(num1.ToString());
      }
    }

    private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
    }

    private void textBox3_TextChanged(object sender, EventArgs e)
    {
    }

    private void btnShowCat1_Click(object sender, EventArgs e)
    {
      this.SortCategory("10000");
      this.SortCategoryValue = "10000";
    }

    private void button4_Click(object sender, EventArgs e)
    {
      this.SortCategory("20000");
      this.SortCategoryValue = "20000";
    }

    private void button5_Click(object sender, EventArgs e)
    {
      this.SortCategory("30000");
      this.SortCategoryValue = "30000";
    }

    private void button6_Click(object sender, EventArgs e)
    {
      this.SortCategory("40000");
      this.SortCategoryValue = "40000";
    }

    private void button7_Click(object sender, EventArgs e)
    {
      this.SortCategory("50000");
      this.SortCategoryValue = "50000";
    }

    private void groupBox7_Enter(object sender, EventArgs e)
    {
    }

    private void button8_Click(object sender, EventArgs e)
    {
      this.SortCategory("60000");
      this.SortCategoryValue = "60000";
    }

    private void button9_Click(object sender, EventArgs e)
    {
      this.SortCategory("70000");
      this.SortCategoryValue = "70000";
    }

    private void button10_Click(object sender, EventArgs e)
    {
      this.LoadListBox();
      this.SortCategoryValue = "-1";
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

    private void checkedListBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      string comboBox = "";
      foreach (object checkedItem in this.checkedListBox1.CheckedItems)
        comboBox = checkedItem.ToString();
      this.textBox3.Text = this.GetIndexByComboBox(comboBox).ToString();
    }

    private void checkedListBox1_ItemCheck(object sender, ItemCheckEventArgs e)
    {
      if (this.checkedListBox1.CheckedItems.Count != 1)
        return;
      if (e.CurrentValue == CheckState.Checked)
      {
        e.NewValue = CheckState.Checked;
      }
      else
      {
        int checkedIndex = this.checkedListBox1.CheckedIndices[0];
        this.checkedListBox1.ItemCheck -= new ItemCheckEventHandler(this.checkedListBox1_ItemCheck);
        this.checkedListBox1.SetItemChecked(checkedIndex, false);
        this.checkedListBox1.ItemCheck += new ItemCheckEventHandler(this.checkedListBox1_ItemCheck);
      }
    }

    private void checkedListBox2_ItemCheck(object sender, ItemCheckEventArgs e)
    {
      if (this.checkedListBox2.CheckedItems.Count != 1)
        return;
      if (e.CurrentValue == CheckState.Checked)
      {
        e.NewValue = CheckState.Checked;
      }
      else
      {
        int checkedIndex = this.checkedListBox2.CheckedIndices[0];
        this.checkedListBox2.ItemCheck -= new ItemCheckEventHandler(this.checkedListBox2_ItemCheck);
        this.checkedListBox2.SetItemChecked(checkedIndex, false);
        this.checkedListBox2.ItemCheck += new ItemCheckEventHandler(this.checkedListBox2_ItemCheck);
      }
    }

    private void checkedListBox2_SelectedIndexChanged(object sender, EventArgs e)
    {
      string comboBox = "";
      foreach (object checkedItem in this.checkedListBox2.CheckedItems)
        comboBox = checkedItem.ToString();
      this.textBox4.Text = this.GetIndexByComboBox(comboBox).ToString();
      this.textBox5.Text = this.GetIndexByComboBox(comboBox).ToString();
    }

    private void groupBox8_Enter(object sender, EventArgs e)
    {
    }

    private void button11_Click(object sender, EventArgs e)
    {
      this.SortCategory("999");
      this.SortCategoryValue = "999";
    }

    private void checkBox1_CheckedChanged(object sender, EventArgs e) => this.SwitchCheckBox = "1";

    private void textBox13_TextChanged(object sender, EventArgs e)
    {
      int.TryParse(this.tbLimit.Text, out this.tmpLimit);
      this.textBox10.Text = this.JoinLimitWithFlag().ToString();
    }

    private void SplitLimitFromFlag(int flag)
    {
      this.tmpFlag = 0;
      this.tmpLimit = 0;
      for (int index = 0; index < 10; ++index)
      {
        if ((flag & 1 << index) != 0)
          this.tmpFlag += 1 << index;
      }
      for (int index = 10; index < 32; ++index)
      {
        if ((flag & 1 << index) != 0)
          this.tmpLimit += 1 << index - 10;
      }
    }

    private void cbEnabled_CheckedChanged(object sender, EventArgs e)
    {
      if (this.cbEnabled.Checked)
      {
        this.cbEnabled.BackColor = Color.Chartreuse;
        this.textBox9.Text = "1";
      }
      else
      {
        if (this.cbEnabled.Checked)
          return;
        this.cbEnabled.BackColor = Color.Red;
        this.textBox9.Text = "0";
      }
    }

    private void textBox9_TextChanged(object sender, EventArgs e)
    {
      if (this.textBox9.Text == "1")
      {
        this.cbEnabled.Checked = true;
      }
      else
      {
        if (!(this.textBox9.Text == "0"))
          return;
        this.cbEnabled.Checked = false;
      }
    }

    private void textBox9_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox9.BackColor = Color.LightBlue;
    }

    private int JoinLimitWithFlag()
    {
      this.tmpLimit = Convert.ToInt32(this.tbLimit.Text);
      return this.tmpFlag | this.tmpLimit << 10;
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
      this.listBox1 = new ListBox();
      this.textBox1 = new TextBox();
      this.textBox2 = new TextBox();
      this.textBox3 = new TextBox();
      this.textBox4 = new TextBox();
      this.textBox5 = new TextBox();
      this.textBox6 = new TextBox();
      this.label1 = new Label();
      this.label2 = new Label();
      this.label3 = new Label();
      this.label5 = new Label();
      this.label6 = new Label();
      this.textBox7 = new TextBox();
      this.textBox8 = new TextBox();
      this.label8 = new Label();
      this.label9 = new Label();
      this.textBox9 = new TextBox();
      this.textBox10 = new TextBox();
      this.textBox11 = new TextBox();
      this.label4 = new Label();
      this.label10 = new Label();
      this.label11 = new Label();
      this.label12 = new Label();
      this.groupBox1 = new GroupBox();
      this.cbEnabled = new CheckBox();
      this.groupBox2 = new GroupBox();
      this.button13 = new Button();
      this.label13 = new Label();
      this.tbLimit = new TextBox();
      this.groupBox4 = new GroupBox();
      this.dgItems = new DataGridView();
      this.Column7 = new DataGridViewImageColumn();
      this.Column1 = new DataGridViewTextBoxColumn();
      this.Column2 = new DataGridViewTextBoxColumn();
      this.Column3 = new DataGridViewTextBoxColumn();
      this.Column4 = new DataGridViewTextBoxColumn();
      this.Column5 = new DataGridViewTextBoxColumn();
      this.Column6 = new DataGridViewTextBoxColumn();
      this.Column8 = new DataGridViewTextBoxColumn();
      this.Column9 = new DataGridViewTextBoxColumn();
      this.toolStrip2 = new ToolStrip();
      this.btnSaveSelected = new ToolStripButton();
      this.toolStripSeparator1 = new ToolStripSeparator();
      this.btnAddItems = new ToolStripButton();
      this.toolStripSeparator6 = new ToolStripSeparator();
      this.btnDelete = new ToolStripButton();
      this.toolStripSeparator2 = new ToolStripSeparator();
      this.btnUpdateName = new ToolStripButton();
      this.groupBox3 = new GroupBox();
      this.button12 = new Button();
      this.button3 = new Button();
      this.button1 = new Button();
      this.groupBox5 = new GroupBox();
      this.label7 = new Label();
      this.textBox12 = new TextBox();
      this.button2 = new Button();
      this.groupBox6 = new GroupBox();
      this.clbFlagTest = new CheckedListBox();
      this.btnShowCat1 = new Button();
      this.button4 = new Button();
      this.button5 = new Button();
      this.button6 = new Button();
      this.button7 = new Button();
      this.button8 = new Button();
      this.button9 = new Button();
      this.button10 = new Button();
      this.groupBox7 = new GroupBox();
      this.button11 = new Button();
      this.statusStrip1 = new StatusStrip();
      this.toolStripStatusLabel1 = new ToolStripStatusLabel();
      this.groupBox8 = new GroupBox();
      this.checkedListBox1 = new CheckedListBox();
      this.groupBox9 = new GroupBox();
      this.checkedListBox2 = new CheckedListBox();
      this.checkBox1 = new CheckBox();
      this.label113 = new Label();
      this.lblLang = new Label();
      this.menuStrip1.SuspendLayout();
      this.groupBox1.SuspendLayout();
      this.groupBox2.SuspendLayout();
      this.groupBox4.SuspendLayout();
      ((ISupportInitialize) this.dgItems).BeginInit();
      this.toolStrip2.SuspendLayout();
      this.groupBox3.SuspendLayout();
      this.groupBox5.SuspendLayout();
      this.groupBox6.SuspendLayout();
      this.groupBox7.SuspendLayout();
      this.statusStrip1.SuspendLayout();
      this.groupBox8.SuspendLayout();
      this.groupBox9.SuspendLayout();
      this.SuspendLayout();
      this.menuStrip1.AllowMerge = false;
      this.menuStrip1.BackColor = SystemColors.ButtonHighlight;
      this.menuStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.fileExportToolStripMenuItem
      });
      this.menuStrip1.Location = new Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new Size(1146, 24);
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
      this.exportlodToolStripMenuItem.Size = new Size(131, 22);
      this.exportlodToolStripMenuItem.Text = "Export .lod";
      this.exportlodToolStripMenuItem.Click += new EventHandler(this.exportlodToolStripMenuItem_Click);
      this.listBox1.FormattingEnabled = true;
      this.listBox1.Location = new Point(6, 14);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new Size(249, 472);
      this.listBox1.TabIndex = 1;
      this.listBox1.SelectedIndexChanged += new EventHandler(this.listBox1_SelectedIndexChanged);
      this.textBox1.BorderStyle = BorderStyle.FixedSingle;
      this.textBox1.Location = new Point(72, 57);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(64, 20);
      this.textBox1.TabIndex = 2;
      this.textBox2.BorderStyle = BorderStyle.FixedSingle;
      this.textBox2.Location = new Point(72, 83);
      this.textBox2.Name = "textBox2";
      this.textBox2.Size = new Size(205, 20);
      this.textBox2.TabIndex = 3;
      this.textBox3.BorderStyle = BorderStyle.FixedSingle;
      this.textBox3.Location = new Point(220, 17);
      this.textBox3.Name = "textBox3";
      this.textBox3.Size = new Size(89, 20);
      this.textBox3.TabIndex = 3;
      this.textBox3.TextChanged += new EventHandler(this.textBox3_TextChanged);
      this.textBox4.BorderStyle = BorderStyle.FixedSingle;
      this.textBox4.Location = new Point(75, 43);
      this.textBox4.Name = "textBox4";
      this.textBox4.Size = new Size(68, 20);
      this.textBox4.TabIndex = 4;
      this.textBox5.BorderStyle = BorderStyle.FixedSingle;
      this.textBox5.Location = new Point(656, 4);
      this.textBox5.Name = "textBox5";
      this.textBox5.Size = new Size(68, 20);
      this.textBox5.TabIndex = 5;
      this.textBox5.Visible = false;
      this.textBox6.BorderStyle = BorderStyle.FixedSingle;
      this.textBox6.Location = new Point(75, 17);
      this.textBox6.Name = "textBox6";
      this.textBox6.Size = new Size(68, 20);
      this.textBox6.TabIndex = 6;
      this.label1.AutoSize = true;
      this.label1.Location = new Point(9, 59);
      this.label1.Name = "label1";
      this.label1.Size = new Size(60, 13);
      this.label1.TabIndex = 7;
      this.label1.Text = "Catalog ID:";
      this.label2.AutoSize = true;
      this.label2.Location = new Point(9, 85);
      this.label2.Name = "label2";
      this.label2.Size = new Size(38, 13);
      this.label2.TabIndex = 8;
      this.label2.Text = "Name:";
      this.label3.AutoSize = true;
      this.label3.Location = new Point(9, 111);
      this.label3.Name = "label3";
      this.label3.Size = new Size(35, 13);
      this.label3.TabIndex = 9;
      this.label3.Text = "Desc:";
      this.label5.AutoSize = true;
      this.label5.Location = new Point(160, 59);
      this.label5.Name = "label5";
      this.label5.Size = new Size(47, 13);
      this.label5.TabIndex = 10;
      this.label5.Text = "Mileage:";
      this.label6.AutoSize = true;
      this.label6.Location = new Point(16, 19);
      this.label6.Name = "label6";
      this.label6.Size = new Size(34, 13);
      this.label6.TabIndex = 11;
      this.label6.Text = "Price:";
      this.textBox7.BorderStyle = BorderStyle.FixedSingle;
      this.textBox7.Location = new Point(72, 109);
      this.textBox7.Multiline = true;
      this.textBox7.Name = "textBox7";
      this.textBox7.Size = new Size(205, 145);
      this.textBox7.TabIndex = 13;
      this.textBox8.BorderStyle = BorderStyle.FixedSingle;
      this.textBox8.Location = new Point(209, 57);
      this.textBox8.Name = "textBox8";
      this.textBox8.Size = new Size(68, 20);
      this.textBox8.TabIndex = 13;
      this.label8.AutoSize = true;
      this.label8.Location = new Point(162, 19);
      this.label8.Name = "label8";
      this.label8.Size = new Size(52, 13);
      this.label8.TabIndex = 14;
      this.label8.Text = "Category:";
      this.label9.AutoSize = true;
      this.label9.Location = new Point(174, 45);
      this.label9.Name = "label9";
      this.label9.Size = new Size(30, 13);
      this.label9.TabIndex = 15;
      this.label9.Text = "Flag:";
      this.textBox9.BorderStyle = BorderStyle.FixedSingle;
      this.textBox9.Location = new Point(72, 31);
      this.textBox9.Name = "textBox9";
      this.textBox9.Size = new Size(64, 20);
      this.textBox9.TabIndex = 16;
      this.textBox9.TextChanged += new EventHandler(this.textBox9_TextChanged);
      this.textBox9.KeyPress += new KeyPressEventHandler(this.textBox9_KeyPress);
      this.textBox10.BorderStyle = BorderStyle.FixedSingle;
      this.textBox10.Location = new Point(220, 43);
      this.textBox10.Name = "textBox10";
      this.textBox10.Size = new Size(89, 20);
      this.textBox10.TabIndex = 17;
      this.textBox11.BorderStyle = BorderStyle.FixedSingle;
      this.textBox11.Location = new Point(220, 69);
      this.textBox11.Name = "textBox11";
      this.textBox11.Size = new Size(89, 20);
      this.textBox11.TabIndex = 18;
      this.label4.AutoSize = true;
      this.label4.Location = new Point(9, 33);
      this.label4.Name = "label4";
      this.label4.Size = new Size(43, 13);
      this.label4.TabIndex = 19;
      this.label4.Text = "Enable:";
      this.label10.AutoSize = true;
      this.label10.Location = new Point(16, 45);
      this.label10.Name = "label10";
      this.label10.Size = new Size(34, 13);
      this.label10.TabIndex = 20;
      this.label10.Text = "Type:";
      this.label11.AutoSize = true;
      this.label11.Location = new Point(597, 8);
      this.label11.Name = "label11";
      this.label11.Size = new Size(53, 13);
      this.label11.TabIndex = 21;
      this.label11.Text = "SubType:";
      this.label11.Visible = false;
      this.label12.AutoSize = true;
      this.label12.Location = new Point(174, 71);
      this.label12.Name = "label12";
      this.label12.Size = new Size(31, 13);
      this.label12.TabIndex = 22;
      this.label12.Text = "Icon:";
      this.groupBox1.Controls.Add((Control) this.cbEnabled);
      this.groupBox1.Controls.Add((Control) this.textBox8);
      this.groupBox1.Controls.Add((Control) this.textBox1);
      this.groupBox1.Controls.Add((Control) this.textBox2);
      this.groupBox1.Controls.Add((Control) this.label1);
      this.groupBox1.Controls.Add((Control) this.label2);
      this.groupBox1.Controls.Add((Control) this.label4);
      this.groupBox1.Controls.Add((Control) this.label3);
      this.groupBox1.Controls.Add((Control) this.textBox7);
      this.groupBox1.Controls.Add((Control) this.textBox9);
      this.groupBox1.Controls.Add((Control) this.label5);
      this.groupBox1.Location = new Point(282, 30);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(290, 277);
      this.groupBox1.TabIndex = 23;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Main";
      this.cbEnabled.AutoSize = true;
      this.cbEnabled.BackColor = Color.Chartreuse;
      this.cbEnabled.Location = new Point(154, 31);
      this.cbEnabled.Name = "cbEnabled";
      this.cbEnabled.Size = new Size(65, 17);
      this.cbEnabled.TabIndex = 88;
      this.cbEnabled.Text = "Enabled";
      this.cbEnabled.UseVisualStyleBackColor = false;
      this.cbEnabled.CheckedChanged += new EventHandler(this.cbEnabled_CheckedChanged);
      this.groupBox2.Controls.Add((Control) this.button13);
      this.groupBox2.Controls.Add((Control) this.label13);
      this.groupBox2.Controls.Add((Control) this.tbLimit);
      this.groupBox2.Controls.Add((Control) this.label12);
      this.groupBox2.Controls.Add((Control) this.textBox3);
      this.groupBox2.Controls.Add((Control) this.textBox4);
      this.groupBox2.Controls.Add((Control) this.textBox6);
      this.groupBox2.Controls.Add((Control) this.label10);
      this.groupBox2.Controls.Add((Control) this.label6);
      this.groupBox2.Controls.Add((Control) this.textBox11);
      this.groupBox2.Controls.Add((Control) this.label8);
      this.groupBox2.Controls.Add((Control) this.textBox10);
      this.groupBox2.Controls.Add((Control) this.label9);
      this.groupBox2.Location = new Point(581, 30);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new Size(342, 98);
      this.groupBox2.TabIndex = 24;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "Misc";
      this.button13.Image = (Image) Resources.search__5_;
      this.button13.Location = new Point(313, 66);
      this.button13.Name = "button13";
      this.button13.Size = new Size(24, 24);
      this.button13.TabIndex = 26;
      this.button13.UseVisualStyleBackColor = true;
      this.button13.Click += new EventHandler(this.button13_Click);
      this.label13.AutoSize = true;
      this.label13.Location = new Point(16, 71);
      this.label13.Name = "label13";
      this.label13.Size = new Size(31, 13);
      this.label13.TabIndex = 24;
      this.label13.Text = "Limit:";
      this.tbLimit.BorderStyle = BorderStyle.FixedSingle;
      this.tbLimit.Location = new Point(75, 69);
      this.tbLimit.Name = "tbLimit";
      this.tbLimit.Size = new Size(68, 20);
      this.tbLimit.TabIndex = 23;
      this.tbLimit.TextChanged += new EventHandler(this.textBox13_TextChanged);
      this.groupBox4.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left;
      this.groupBox4.Controls.Add((Control) this.dgItems);
      this.groupBox4.Controls.Add((Control) this.toolStrip2);
      this.groupBox4.Location = new Point(282, 313);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Size = new Size(644, 350);
      this.groupBox4.TabIndex = 25;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "Items";
      this.dgItems.AllowUserToAddRows = false;
      this.dgItems.AllowUserToDeleteRows = false;
      this.dgItems.BackgroundColor = SystemColors.Control;
      this.dgItems.BorderStyle = BorderStyle.None;
      this.dgItems.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dgItems.Columns.AddRange((DataGridViewColumn) this.Column7, (DataGridViewColumn) this.Column1, (DataGridViewColumn) this.Column2, (DataGridViewColumn) this.Column3, (DataGridViewColumn) this.Column4, (DataGridViewColumn) this.Column5, (DataGridViewColumn) this.Column6, (DataGridViewColumn) this.Column8, (DataGridViewColumn) this.Column9);
      this.dgItems.Dock = DockStyle.Fill;
      this.dgItems.EnableHeadersVisualStyles = false;
      this.dgItems.Location = new Point(3, 16);
      this.dgItems.Name = "dgItems";
      this.dgItems.RowHeadersVisible = false;
      this.dgItems.RowTemplate.Height = 32;
      this.dgItems.Size = new Size(638, 306);
      this.dgItems.TabIndex = 0;
      this.dgItems.CellContentClick += new DataGridViewCellEventHandler(this.dgItems_CellContentClick);
      this.Column7.HeaderText = "";
      this.Column7.Name = "Column7";
      this.Column7.Width = 32;
      this.Column1.HeaderText = "ID";
      this.Column1.Name = "Column1";
      this.Column1.Width = 60;
      this.Column2.HeaderText = "Name";
      this.Column2.Name = "Column2";
      this.Column2.ReadOnly = true;
      this.Column2.Width = 300;
      this.Column3.HeaderText = "Amount";
      this.Column3.Name = "Column3";
      this.Column3.Width = 75;
      this.Column4.HeaderText = "Plus";
      this.Column4.Name = "Column4";
      this.Column4.Width = 50;
      this.Column5.HeaderText = "Level";
      this.Column5.Name = "Column5";
      this.Column5.Width = 50;
      this.Column6.HeaderText = "Flag";
      this.Column6.Name = "Column6";
      this.Column6.Width = 50;
      this.Column8.HeaderText = "Index";
      this.Column8.Name = "Column8";
      this.Column8.Visible = false;
      this.Column9.HeaderText = "CatalogID";
      this.Column9.Name = "Column9";
      this.Column9.Visible = false;
      this.toolStrip2.Dock = DockStyle.Bottom;
      this.toolStrip2.GripStyle = ToolStripGripStyle.Hidden;
      this.toolStrip2.Items.AddRange(new ToolStripItem[7]
      {
        (ToolStripItem) this.btnSaveSelected,
        (ToolStripItem) this.toolStripSeparator1,
        (ToolStripItem) this.btnAddItems,
        (ToolStripItem) this.toolStripSeparator6,
        (ToolStripItem) this.btnDelete,
        (ToolStripItem) this.toolStripSeparator2,
        (ToolStripItem) this.btnUpdateName
      });
      this.toolStrip2.Location = new Point(3, 322);
      this.toolStrip2.Name = "toolStrip2";
      this.toolStrip2.Size = new Size(638, 25);
      this.toolStrip2.TabIndex = 1;
      this.toolStrip2.Text = "toolStrip2";
      this.btnSaveSelected.DisplayStyle = ToolStripItemDisplayStyle.Text;
      this.btnSaveSelected.ImageTransparentColor = Color.Magenta;
      this.btnSaveSelected.Name = "btnSaveSelected";
      this.btnSaveSelected.Size = new Size(62, 22);
      this.btnSaveSelected.Text = "Save Item";
      this.btnSaveSelected.Click += new EventHandler(this.btnSaveSelected_Click);
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
      this.btnDelete.DisplayStyle = ToolStripItemDisplayStyle.Text;
      this.btnDelete.ImageTransparentColor = Color.Magenta;
      this.btnDelete.Name = "btnDelete";
      this.btnDelete.Size = new Size(91, 22);
      this.btnDelete.Text = "Delete Selected";
      this.btnDelete.Click += new EventHandler(this.btnDelete_Click);
      this.toolStripSeparator2.Name = "toolStripSeparator2";
      this.toolStripSeparator2.Size = new Size(6, 25);
      this.btnUpdateName.DisplayStyle = ToolStripItemDisplayStyle.Text;
      this.btnUpdateName.ImageTransparentColor = Color.Magenta;
      this.btnUpdateName.Name = "btnUpdateName";
      this.btnUpdateName.Size = new Size(135, 22);
      this.btnUpdateName.Text = "Update Name and Desc";
      this.btnUpdateName.Click += new EventHandler(this.btnUpdateName_Click);
      this.groupBox3.Controls.Add((Control) this.button12);
      this.groupBox3.Controls.Add((Control) this.button3);
      this.groupBox3.Controls.Add((Control) this.button1);
      this.groupBox3.Controls.Add((Control) this.listBox1);
      this.groupBox3.Location = new Point(15, 176);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Size = new Size(261, 531);
      this.groupBox3.TabIndex = 29;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "Package";
      this.button12.FlatStyle = FlatStyle.Flat;
      this.button12.Location = new Point(94, 494);
      this.button12.Name = "button12";
      this.button12.Size = new Size(75, 23);
      this.button12.TabIndex = 5;
      this.button12.Text = "Copy";
      this.button12.UseVisualStyleBackColor = true;
      this.button12.Click += new EventHandler(this.button12_Click);
      this.button3.FlatStyle = FlatStyle.Flat;
      this.button3.Location = new Point(175, 494);
      this.button3.Name = "button3";
      this.button3.Size = new Size(68, 23);
      this.button3.TabIndex = 4;
      this.button3.Text = "Delete";
      this.button3.UseVisualStyleBackColor = true;
      this.button3.Click += new EventHandler(this.button3_Click);
      this.button1.FlatStyle = FlatStyle.Flat;
      this.button1.Location = new Point(18, 494);
      this.button1.Name = "button1";
      this.button1.Size = new Size(70, 23);
      this.button1.TabIndex = 2;
      this.button1.Text = "Add";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.groupBox5.Controls.Add((Control) this.label7);
      this.groupBox5.Controls.Add((Control) this.textBox12);
      this.groupBox5.Location = new Point(15, 30);
      this.groupBox5.Name = "groupBox5";
      this.groupBox5.Size = new Size(261, 51);
      this.groupBox5.TabIndex = 30;
      this.groupBox5.TabStop = false;
      this.groupBox5.Text = "Search";
      this.label7.AutoSize = true;
      this.label7.Location = new Point(16, 21);
      this.label7.Name = "label7";
      this.label7.Size = new Size(31, 13);
      this.label7.TabIndex = 21;
      this.label7.Text = "Text:";
      this.textBox12.BorderStyle = BorderStyle.FixedSingle;
      this.textBox12.Location = new Point(53, 19);
      this.textBox12.Name = "textBox12";
      this.textBox12.Size = new Size(202, 20);
      this.textBox12.TabIndex = 20;
      this.textBox12.TextChanged += new EventHandler(this.textBox12_TextChanged);
      this.button2.FlatStyle = FlatStyle.Flat;
      this.button2.Location = new Point(1034, 670);
      this.button2.Name = "button2";
      this.button2.Size = new Size(100, 23);
      this.button2.TabIndex = 5;
      this.button2.Text = "Save";
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.groupBox6.Controls.Add((Control) this.clbFlagTest);
      this.groupBox6.Location = new Point(578, 134);
      this.groupBox6.Name = "groupBox6";
      this.groupBox6.Size = new Size(167, 173);
      this.groupBox6.TabIndex = 31;
      this.groupBox6.TabStop = false;
      this.groupBox6.Text = "Flag";
      this.clbFlagTest.BackColor = SystemColors.Control;
      this.clbFlagTest.BorderStyle = BorderStyle.None;
      this.clbFlagTest.CheckOnClick = true;
      this.clbFlagTest.ColumnWidth = 75;
      this.clbFlagTest.Dock = DockStyle.Fill;
      this.clbFlagTest.Items.AddRange(new object[10]
      {
        (object) "New",
        (object) "Popular",
        (object) "Discount",
        (object) "Best Item 1",
        (object) "Best Item 2",
        (object) "Best Item 3",
        (object) "Best Item 4",
        (object) "Best Item 5",
        (object) "Reserved1",
        (object) "Reserved2"
      });
      this.clbFlagTest.Location = new Point(3, 16);
      this.clbFlagTest.MultiColumn = true;
      this.clbFlagTest.Name = "clbFlagTest";
      this.clbFlagTest.Size = new Size(161, 154);
      this.clbFlagTest.TabIndex = 14;
      this.clbFlagTest.SelectedIndexChanged += new EventHandler(this.clbFlagTest_SelectedIndexChanged);
      this.btnShowCat1.BackgroundImage = (Image) Resources._1;
      this.btnShowCat1.BackgroundImageLayout = ImageLayout.Zoom;
      this.btnShowCat1.FlatStyle = FlatStyle.Flat;
      this.btnShowCat1.Location = new Point(6, 19);
      this.btnShowCat1.Name = "btnShowCat1";
      this.btnShowCat1.Size = new Size(25, 25);
      this.btnShowCat1.TabIndex = 19;
      this.btnShowCat1.UseVisualStyleBackColor = true;
      this.btnShowCat1.Click += new EventHandler(this.btnShowCat1_Click);
      this.button4.BackgroundImage = (Image) Resources._2;
      this.button4.BackgroundImageLayout = ImageLayout.Zoom;
      this.button4.FlatStyle = FlatStyle.Flat;
      this.button4.Location = new Point(43, 19);
      this.button4.Name = "button4";
      this.button4.Size = new Size(25, 25);
      this.button4.TabIndex = 32;
      this.button4.UseVisualStyleBackColor = true;
      this.button4.Click += new EventHandler(this.button4_Click);
      this.button5.BackgroundImage = (Image) Resources._3;
      this.button5.BackgroundImageLayout = ImageLayout.Zoom;
      this.button5.FlatStyle = FlatStyle.Flat;
      this.button5.Location = new Point(78, 19);
      this.button5.Name = "button5";
      this.button5.Size = new Size(25, 25);
      this.button5.TabIndex = 33;
      this.button5.UseVisualStyleBackColor = true;
      this.button5.Click += new EventHandler(this.button5_Click);
      this.button6.BackgroundImage = (Image) Resources._4;
      this.button6.BackgroundImageLayout = ImageLayout.Zoom;
      this.button6.FlatStyle = FlatStyle.Flat;
      this.button6.Location = new Point(116, 19);
      this.button6.Name = "button6";
      this.button6.Size = new Size(25, 25);
      this.button6.TabIndex = 34;
      this.button6.UseVisualStyleBackColor = true;
      this.button6.Click += new EventHandler(this.button6_Click);
      this.button7.BackgroundImage = (Image) Resources._5;
      this.button7.BackgroundImageLayout = ImageLayout.Zoom;
      this.button7.FlatStyle = FlatStyle.Flat;
      this.button7.Location = new Point(154, 19);
      this.button7.Name = "button7";
      this.button7.Size = new Size(25, 25);
      this.button7.TabIndex = 35;
      this.button7.UseVisualStyleBackColor = true;
      this.button7.Click += new EventHandler(this.button7_Click);
      this.button8.BackgroundImage = (Image) Resources._6;
      this.button8.BackgroundImageLayout = ImageLayout.Zoom;
      this.button8.FlatStyle = FlatStyle.Flat;
      this.button8.Location = new Point(191, 19);
      this.button8.Name = "button8";
      this.button8.Size = new Size(25, 25);
      this.button8.TabIndex = 36;
      this.button8.UseVisualStyleBackColor = true;
      this.button8.Click += new EventHandler(this.button8_Click);
      this.button9.BackgroundImage = (Image) Resources._7;
      this.button9.BackgroundImageLayout = ImageLayout.Zoom;
      this.button9.FlatStyle = FlatStyle.Flat;
      this.button9.Location = new Point(227, 19);
      this.button9.Name = "button9";
      this.button9.Size = new Size(25, 25);
      this.button9.TabIndex = 37;
      this.button9.UseVisualStyleBackColor = true;
      this.button9.Click += new EventHandler(this.button9_Click);
      this.button10.BackgroundImageLayout = ImageLayout.Zoom;
      this.button10.FlatStyle = FlatStyle.Flat;
      this.button10.Location = new Point(6, 50);
      this.button10.Name = "button10";
      this.button10.Size = new Size(110, 25);
      this.button10.TabIndex = 38;
      this.button10.Text = "All";
      this.button10.UseVisualStyleBackColor = true;
      this.button10.Click += new EventHandler(this.button10_Click);
      this.groupBox7.Controls.Add((Control) this.button11);
      this.groupBox7.Controls.Add((Control) this.button10);
      this.groupBox7.Controls.Add((Control) this.btnShowCat1);
      this.groupBox7.Controls.Add((Control) this.button9);
      this.groupBox7.Controls.Add((Control) this.button4);
      this.groupBox7.Controls.Add((Control) this.button8);
      this.groupBox7.Controls.Add((Control) this.button5);
      this.groupBox7.Controls.Add((Control) this.button7);
      this.groupBox7.Controls.Add((Control) this.button6);
      this.groupBox7.Location = new Point(15, 87);
      this.groupBox7.Name = "groupBox7";
      this.groupBox7.Size = new Size(261, 83);
      this.groupBox7.TabIndex = 2;
      this.groupBox7.TabStop = false;
      this.groupBox7.Text = "Category";
      this.groupBox7.Enter += new EventHandler(this.groupBox7_Enter);
      this.button11.BackgroundImageLayout = ImageLayout.Zoom;
      this.button11.FlatStyle = FlatStyle.Flat;
      this.button11.Location = new Point(130, 50);
      this.button11.Name = "button11";
      this.button11.Size = new Size(122, 25);
      this.button11.TabIndex = 39;
      this.button11.Text = "Credit Shop";
      this.button11.UseVisualStyleBackColor = true;
      this.button11.Click += new EventHandler(this.button11_Click);
      this.statusStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.toolStripStatusLabel1
      });
      this.statusStrip1.Location = new Point(0, 710);
      this.statusStrip1.Name = "statusStrip1";
      this.statusStrip1.Size = new Size(1146, 22);
      this.statusStrip1.TabIndex = 49;
      this.statusStrip1.Text = "statusStrip1";
      this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
      this.toolStripStatusLabel1.Size = new Size(39, 17);
      this.toolStripStatusLabel1.Text = "Ready";
      this.groupBox8.Controls.Add((Control) this.checkedListBox1);
      this.groupBox8.Location = new Point(751, 134);
      this.groupBox8.Name = "groupBox8";
      this.groupBox8.Padding = new Padding(5);
      this.groupBox8.Size = new Size(175, 173);
      this.groupBox8.TabIndex = 50;
      this.groupBox8.TabStop = false;
      this.groupBox8.Text = "Category";
      this.groupBox8.Enter += new EventHandler(this.groupBox8_Enter);
      this.checkedListBox1.BackColor = SystemColors.Control;
      this.checkedListBox1.BorderStyle = BorderStyle.None;
      this.checkedListBox1.CheckOnClick = true;
      this.checkedListBox1.Dock = DockStyle.Fill;
      this.checkedListBox1.FormattingEnabled = true;
      this.checkedListBox1.Location = new Point(5, 18);
      this.checkedListBox1.MultiColumn = true;
      this.checkedListBox1.Name = "checkedListBox1";
      this.checkedListBox1.Size = new Size(165, 150);
      this.checkedListBox1.TabIndex = 0;
      this.checkedListBox1.ItemCheck += new ItemCheckEventHandler(this.checkedListBox1_ItemCheck);
      this.checkedListBox1.SelectedIndexChanged += new EventHandler(this.checkedListBox1_SelectedIndexChanged);
      this.groupBox9.Controls.Add((Control) this.checkedListBox2);
      this.groupBox9.Location = new Point(929, 30);
      this.groupBox9.Name = "groupBox9";
      this.groupBox9.Padding = new Padding(5);
      this.groupBox9.Size = new Size(205, 634);
      this.groupBox9.TabIndex = 51;
      this.groupBox9.TabStop = false;
      this.groupBox9.Text = "Type/Subtype";
      this.checkedListBox2.BackColor = SystemColors.Control;
      this.checkedListBox2.BorderStyle = BorderStyle.None;
      this.checkedListBox2.CheckOnClick = true;
      this.checkedListBox2.Dock = DockStyle.Fill;
      this.checkedListBox2.FormattingEnabled = true;
      this.checkedListBox2.Location = new Point(5, 18);
      this.checkedListBox2.Name = "checkedListBox2";
      this.checkedListBox2.Size = new Size(195, 611);
      this.checkedListBox2.TabIndex = 0;
      this.checkedListBox2.ItemCheck += new ItemCheckEventHandler(this.checkedListBox2_ItemCheck);
      this.checkedListBox2.SelectedIndexChanged += new EventHandler(this.checkedListBox2_SelectedIndexChanged);
      this.checkBox1.AutoSize = true;
      this.checkBox1.BackColor = SystemColors.ButtonHighlight;
      this.checkBox1.Location = new Point(992, 4);
      this.checkBox1.Name = "checkBox1";
      this.checkBox1.Size = new Size(139, 17);
      this.checkBox1.TabIndex = 23;
      this.checkBox1.Text = "SwitchCategoryOnSave";
      this.checkBox1.UseVisualStyleBackColor = false;
      this.checkBox1.CheckedChanged += new EventHandler(this.checkBox1_CheckedChanged);
      this.label113.AutoSize = true;
      this.label113.BackColor = SystemColors.ControlLightLight;
      this.label113.Font = new Font("Microsoft Sans Serif", 9.75f, FontStyle.Bold, GraphicsUnit.Point, (byte) 0);
      this.label113.Location = new Point(748, 6);
      this.label113.Name = "label113";
      this.label113.Size = new Size(154, 16);
      this.label113.TabIndex = 52;
      this.label113.Text = "Current Language is :";
      this.lblLang.AutoSize = true;
      this.lblLang.ForeColor = Color.LawnGreen;
      this.lblLang.Location = new Point(908, 6);
      this.lblLang.Name = "lblLang";
      this.lblLang.Size = new Size(31, 13);
      this.lblLang.TabIndex = 53;
      this.lblLang.Text = "Lang";
      this.ClientSize = new Size(1146, 732);
      this.Controls.Add((Control) this.lblLang);
      this.Controls.Add((Control) this.label113);
      this.Controls.Add((Control) this.textBox5);
      this.Controls.Add((Control) this.checkBox1);
      this.Controls.Add((Control) this.groupBox9);
      this.Controls.Add((Control) this.groupBox8);
      this.Controls.Add((Control) this.label11);
      this.Controls.Add((Control) this.statusStrip1);
      this.Controls.Add((Control) this.groupBox7);
      this.Controls.Add((Control) this.groupBox6);
      this.Controls.Add((Control) this.button2);
      this.Controls.Add((Control) this.groupBox5);
      this.Controls.Add((Control) this.groupBox3);
      this.Controls.Add((Control) this.groupBox4);
      this.Controls.Add((Control) this.groupBox2);
      this.Controls.Add((Control) this.groupBox1);
      this.Controls.Add((Control) this.menuStrip1);
      this.MainMenuStrip = this.menuStrip1;
      this.MaximizeBox = false;
      this.MinimizeBox = false;
      this.Name = nameof (CatalogFreeEditor);
      this.Text = "Catalog Editor";
      this.Load += new EventHandler(this.Exporter_Catalog_Load);
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.groupBox2.ResumeLayout(false);
      this.groupBox2.PerformLayout();
      this.groupBox4.ResumeLayout(false);
      this.groupBox4.PerformLayout();
      ((ISupportInitialize) this.dgItems).EndInit();
      this.toolStrip2.ResumeLayout(false);
      this.toolStrip2.PerformLayout();
      this.groupBox3.ResumeLayout(false);
      this.groupBox5.ResumeLayout(false);
      this.groupBox5.PerformLayout();
      this.groupBox6.ResumeLayout(false);
      this.groupBox7.ResumeLayout(false);
      this.statusStrip1.ResumeLayout(false);
      this.statusStrip1.PerformLayout();
      this.groupBox8.ResumeLayout(false);
      this.groupBox9.ResumeLayout(false);
      this.ResumeLayout(false);
      this.PerformLayout();
    }

    private void btnDelete_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want to Delete Item ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_ct_itemfree WHERE a_index ='" + Convert.ToString(this.dgItems.Rows[this.dgItems.CurrentRow.Index].Cells["Column8"].Value) + "'");
      this.dgItems.Rows.Clear();
      this.LoadDG();
    }

    private int GetID()
    {
      int result = -1;
      int.TryParse(this.listBox1.Text.Split(' ')[0], out result);
      return result;
    }

    private void btnUpdateName_Click(object sender, EventArgs e)
    {
      int ItemID = Convert.ToInt32(this.dgItems.Rows[0].Cells[1].Value);
      if (ItemID == -1)
        return;
      ticon ticon = IconList.List.Find((Predicate<ticon>) (p => p.ItemID.Equals(ItemID)));
      if (ticon == null)
        return;
      Convert.ToInt32(this.dgItems.Rows[0].Cells[1].Value);
      this.textBox2.Text = ticon.Name;
      this.textBox7.Text = ticon.Desc;
      this.button2_Click(sender, e);
    }

    private void button12_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want to Copy Item ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DROP TABLE IF EXISTS tempTable;CREATE TEMPORARY TABLE tempTable ENGINE=MyISAM SELECT * FROM t_catalogfree WHERE a_ctid=" + this.textBox1.Text + ";SELECT a_ctid FROM tempTable;UPDATE tempTable SET a_ctid=(SELECT a_ctid from t_catalogfree ORDER BY a_ctid DESC LIMIT 1)+1; SELECT a_ctid FROM tempTable;INSERT INTO t_catalogfree SELECT * FROM tempTable;");
      int num = (int) new CustomMessage("Copying Complete").ShowDialog();
      this.LoadListBox();
      this.listBox1.SelectedIndex = this.listBox1.Items.Count - 1;
    }

    private void button13_Click(object sender, EventArgs e)
    {
      this.textBox11.Text = "0";
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox11.Text = itemPicker.ItemIndex.ToString();
    }
  }
}
