// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare
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
namespace LcDevPack_TeamDamonA.ItemStringCompare
{
  public class ItemStringCompare : Form
  {
    public static Connection connection = new Connection();
    private string Host = LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.connection.Settings.SqlHost;
    private string User = LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.connection.Settings.SqlUser;
    private string Password = LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.connection.Settings.SqlPassword;
    private string Database = LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.connection.Settings.SqlDatabase;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    public string _ClientPath = LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.connection.Settings.ClientPath;
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
    private string country;
    public static string namee;
    public static string descrr;
    private string language = LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.connection.Settings.Language;
    public string[] menuArray = new string[2]
    {
      "a_index",
      "a_name"
    };
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
    private TextBox textBox4;
    private TextBox textBox7;
    public string[] menuArrayITA = new string[2]
    {
      "a_index",
      "a_name_ita"
    };
    private GroupBox groupBox5;
    private TextBox textBox1;
    private Label label7;
    private GroupBox groupBox2;
    private GroupBox groupBox3;
    private ListBox listBox2;
    private GroupBox groupBox4;
    private Button button8;
    private TextBox textBox2;
    private TextBox textBox3;
    private Label label3;
    private Label label4;
    private ComboBox comboBox1;
    private TextBox textBox8;
    private Label label5;
    public string[] menuArrayUSA = new string[2]
    {
      "a_index",
      "a_name_usa"
    };

    private string DescrFromLanguage()
    {
      if (this.language == "GER")
      {
        LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.descrr = "a_descr_ger";
        return LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.descrr;
      }
      if (this.language == "POL")
      {
        LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.descrr = "a_descr_pld";
        return LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.descrr;
      }
      if (this.language == "BRA")
      {
        LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.descrr = "a_descr_brz";
        return LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.descrr;
      }
      if (this.language == "RUS")
      {
        LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.descrr = "a_descr_rus";
        return LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.descrr;
      }
      if (this.language == "FRA")
      {
        LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.descrr = "a_descr_frc";
        return LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.descrr;
      }
      if (this.language == "ESP")
      {
        LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.descrr = "a_descr_spn";
        return LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.descrr;
      }
      if (this.language == "MEX")
      {
        LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.descrr = "a_descr_mex";
        return LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.descrr;
      }
      if (this.language == "THA")
      {
        LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.descrr = "a_descr_thai";
        return LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.descrr;
      }
      if (this.language == "ITA")
      {
        LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.descrr = "a_descr_ita";
        return LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.descrr;
      }
      if (!(this.language == "USA"))
        return (string) null;
      LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.descrr = "a_descr_usa";
      return LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.descrr;
    }

    public ItemStringCompare()
    {
      this.InitializeComponent();
      this.LoadListBox();
      this.LoadListBox2();
    }

    private string StringFromLanguage()
    {
      if (this.language == "GER")
      {
        LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee = "a_name_ger";
        return LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee;
      }
      if (this.language == "POL")
      {
        LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee = "a_name_pld";
        return LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee;
      }
      if (this.language == "BRA")
      {
        LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee = "a_name_brz";
        return LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee;
      }
      if (this.language == "RUS")
      {
        LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee = "a_name_rus";
        return LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee;
      }
      if (this.language == "FRA")
      {
        LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee = "a_name_frc";
        return LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee;
      }
      if (this.language == "ESP")
      {
        LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee = "a_name_spn";
        return LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee;
      }
      if (this.language == "MEX")
      {
        LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee = "a_name_mex";
        return LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee;
      }
      if (this.language == "THA")
      {
        LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee = "a_name_thai";
        return LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee;
      }
      if (this.language == "ITA")
      {
        LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee = "a_name_ita";
        return LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee;
      }
      if (!(this.language == "USA"))
        return (string) null;
      LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee = "a_name_usa";
      return LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee;
    }

    public void SearchList(string searchString)
    {
      LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee = this.StringFromLanguage();
      string Query = "select a_index, " + LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee + " from t_item WHERE " + LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee + " LIKE '%" + searchString + "%' ORDER BY a_index;";
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
      LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee = this.StringFromLanguage();
      LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.descrr = this.DescrFromLanguage();
      string Query = "SELECT a_index, " + LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee + " FROM t_item ORDER BY a_index;";
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

    private void LoadListBox2()
    {
      this.listBox1.SelectedIndex = -1;
      this.MenuList.Clear();
      LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee = this.StringFromLanguage();
      this.listBox2.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayUSA, this.Host, this.User, this.Password, this.Database, "SELECT a_index, a_name_usa FROM t_item ORDER BY a_index;");
      for (int index = 0; index < this.listBox2.Items.Count; ++index)
        this.MenuList.Add(this.listBox2.Items[index].ToString());
      this.listBox2.DataSource = (object) this.MenuList;
    }

    private void LoadListBoxTHAI()
    {
      this.listBox1.SelectedIndex = -1;
      this.MenuList.Clear();
      LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee = this.StringFromLanguage();
      this.listBox2.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayTHA, this.Host, this.User, this.Password, this.Database, "SELECT a_index, a_name_thai FROM t_item ORDER BY a_index;");
      for (int index = 0; index < this.listBox2.Items.Count; ++index)
        this.MenuList.Add(this.listBox2.Items[index].ToString());
      this.listBox2.DataSource = (object) this.MenuList;
    }

    private void LoadListBoxUSA()
    {
      this.listBox1.SelectedIndex = -1;
      this.MenuList.Clear();
      LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee = this.StringFromLanguage();
      this.listBox2.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayUSA, this.Host, this.User, this.Password, this.Database, "SELECT a_index, a_name_usa FROM t_item ORDER BY a_index;");
      for (int index = 0; index < this.listBox2.Items.Count; ++index)
        this.MenuList.Add(this.listBox2.Items[index].ToString());
      this.listBox2.DataSource = (object) this.MenuList;
    }

    private void LoadListBoxGER()
    {
      this.listBox1.SelectedIndex = -1;
      this.MenuList.Clear();
      LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee = this.StringFromLanguage();
      this.listBox2.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayGER, this.Host, this.User, this.Password, this.Database, "SELECT a_index, a_name_ger FROM t_item ORDER BY a_index;");
      for (int index = 0; index < this.listBox2.Items.Count; ++index)
        this.MenuList.Add(this.listBox2.Items[index].ToString());
      this.listBox2.DataSource = (object) this.MenuList;
    }

    private void LoadListBoxESP()
    {
      this.listBox1.SelectedIndex = -1;
      this.MenuList.Clear();
      LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee = this.StringFromLanguage();
      this.listBox2.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayESP, this.Host, this.User, this.Password, this.Database, "SELECT a_index, a_name_spn FROM t_item ORDER BY a_index;");
      for (int index = 0; index < this.listBox2.Items.Count; ++index)
        this.MenuList.Add(this.listBox2.Items[index].ToString());
      this.listBox2.DataSource = (object) this.MenuList;
    }

    private void LoadListBoxBRA()
    {
      this.listBox1.SelectedIndex = -1;
      this.MenuList.Clear();
      LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee = this.StringFromLanguage();
      this.listBox2.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayBRA, this.Host, this.User, this.Password, this.Database, "SELECT a_index, a_name_brz FROM t_item ORDER BY a_index;");
      for (int index = 0; index < this.listBox2.Items.Count; ++index)
        this.MenuList.Add(this.listBox2.Items[index].ToString());
      this.listBox2.DataSource = (object) this.MenuList;
    }

    private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (this.comboBox1.SelectedIndex == 0)
        this.LoadListBoxTHAI();
      if (this.comboBox1.SelectedIndex == 1)
        this.LoadListBoxUSA();
      if (this.comboBox1.SelectedIndex == 2)
        this.LoadListBoxGER();
      if (this.comboBox1.SelectedIndex == 3)
        this.LoadListBoxESP();
      if (this.comboBox1.SelectedIndex == 4)
        this.LoadListBoxBRA();
      if (this.comboBox1.SelectedIndex != 5)
        ;
      if (this.comboBox1.SelectedIndex != 6)
        ;
      if (this.comboBox1.SelectedIndex != 7)
        ;
      if (this.comboBox1.SelectedIndex != 8)
        ;
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
      LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee = this.StringFromLanguage();
      LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.descrr = this.DescrFromLanguage();
      this.ClearBox();
      if (this.listBox1.SelectedIndex != -1)
        this.textBox6.Text = this.GetIndex().ToString();
      string Query = "select a_index, " + LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee + "," + LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.descrr + " FROM t_item WHERE a_index ='" + this.textBox6.Text + "';";
      string[] rows = new string[3]
      {
        "a_index",
        LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee,
        LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.descrr
      };
      Query.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'");
      string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query, rows);
      this.textBox6.Text = strArray[0];
      this.textBox2.Text = strArray[0];
      this.textBox5.Text = strArray[1];
      this.textBox4.Text = strArray[2];
    }

    private void listBox2_SelectedIndexChanged(object sender, EventArgs e)
    {
      LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee = this.StringFromLanguage();
      this.ClearBox();
      if (this.listBox1.SelectedIndex != -1)
        this.textBox6.Text = this.GetIndex().ToString();
      if (this.comboBox1.SelectedIndex == 0)
      {
        string Query = "select a_index, a_name_thai, a_descr_thai FROM t_item WHERE a_index ='" + this.textBox6.Text + "';";
        string[] rows = new string[3]
        {
          "a_index",
          "a_name_thai",
          "a_descr_thai"
        };
        Query.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'");
        string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query, rows);
        this.textBox2.Text = strArray[0];
        this.textBox6.Text = strArray[0];
        this.textBox3.Text = strArray[1];
        this.textBox7.Text = strArray[2];
      }
      else if (this.comboBox1.SelectedIndex == 1)
      {
        string Query = "select a_index, a_name_usa, a_descr_usa FROM t_item WHERE a_index ='" + this.textBox6.Text + "';";
        string[] rows = new string[3]
        {
          "a_index",
          "a_name_usa",
          "a_descr_usa"
        };
        Query.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'");
        string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query, rows);
        this.textBox2.Text = strArray[0];
        this.textBox6.Text = strArray[0];
        this.textBox3.Text = strArray[1];
        this.textBox7.Text = strArray[2];
      }
      else if (this.comboBox1.SelectedIndex == 2)
      {
        string Query = "select a_index, a_name_ger, a_descr_ger FROM t_item WHERE a_index ='" + this.textBox6.Text + "';";
        string[] rows = new string[3]
        {
          "a_index",
          "a_name_ger",
          "a_descr_ger"
        };
        Query.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'");
        string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query, rows);
        this.textBox2.Text = strArray[0];
        this.textBox6.Text = strArray[0];
        this.textBox3.Text = strArray[1];
        this.textBox7.Text = strArray[2];
      }
      else if (this.comboBox1.SelectedIndex == 3)
      {
        string Query = "select a_index, a_name_spn, a_descr_spn FROM t_item WHERE a_index ='" + this.textBox6.Text + "';";
        string[] rows = new string[3]
        {
          "a_index",
          "a_name_spn",
          "a_descr_spn"
        };
        Query.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'");
        string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query, rows);
        this.textBox2.Text = strArray[0];
        this.textBox6.Text = strArray[0];
        this.textBox3.Text = strArray[1];
        this.textBox7.Text = strArray[2];
      }
      else if (this.comboBox1.SelectedIndex == 4)
      {
        string Query = "select a_index, a_name_brz, a_descr_brz FROM t_item WHERE a_index ='" + this.textBox6.Text + "';";
        string[] rows = new string[3]
        {
          "a_index",
          "a_name_brz",
          "a_descr_brz"
        };
        Query.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'");
        string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query, rows);
        this.textBox2.Text = strArray[0];
        this.textBox6.Text = strArray[0];
        this.textBox3.Text = strArray[1];
        this.textBox7.Text = strArray[2];
      }
      else
      {
        string Query = "select a_index, a_name_usa, a_descr_usa FROM t_item WHERE a_index ='" + this.textBox6.Text + "';";
        string[] rows = new string[3]
        {
          "a_index",
          "a_name_usa",
          "a_descr_usa"
        };
        Query.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'");
        string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query, rows);
        this.textBox2.Text = strArray[0];
        this.textBox6.Text = strArray[0];
        this.textBox3.Text = strArray[1];
        this.textBox7.Text = strArray[2];
      }
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
      LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee = this.StringFromLanguage();
      string str1 = this.textBox5.Text.Replace("'", "\\'").Replace("\"", "\\\"");
      string str2 = this.textBox4.Text.Replace("'", "\\'").Replace("\"", "\\\"");
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_item SET " + LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee + "  = '" + str1 + "', " + LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.descrr + "  = '" + str2 + "' WHERE a_index = '" + this.textBox6.Text + "'");
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
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_item (" + LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee + ") VALUES ('New String')");
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
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DROP TABLE IF EXISTS tempTable;CREATE TEMPORARY TABLE tempTable ENGINE=MEMORY SELECT * FROM t_item WHERE a_index=" + this.textBox6.Text + ";SELECT a_index FROM tempTable;UPDATE tempTable SET a_index=(SELECT a_index from t_item ORDER BY a_index DESC LIMIT 1)+1; SELECT a_index FROM tempTable;INSERT INTO t_item SELECT * FROM tempTable;");
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
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_item WHERE a_index = '" + this.textBox6.Text + "'");
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
      this.groupBox3 = new GroupBox();
      this.listBox2 = new ListBox();
      this.groupBox4 = new GroupBox();
      this.button8 = new Button();
      this.textBox2 = new TextBox();
      this.textBox3 = new TextBox();
      this.label3 = new Label();
      this.label4 = new Label();
      this.comboBox1 = new ComboBox();
      this.textBox8 = new TextBox();
      this.label5 = new Label();
      this.textBox4 = new TextBox();
      this.textBox7 = new TextBox();
      this.groupBox1.SuspendLayout();
      this.groupBox5.SuspendLayout();
      this.groupBox2.SuspendLayout();
      this.groupBox3.SuspendLayout();
      this.groupBox4.SuspendLayout();
      this.SuspendLayout();
      this.groupBox1.Controls.Add((Control) this.textBox4);
      this.groupBox1.Controls.Add((Control) this.button1);
      this.groupBox1.Controls.Add((Control) this.textBox6);
      this.groupBox1.Controls.Add((Control) this.textBox5);
      this.groupBox1.Controls.Add((Control) this.label2);
      this.groupBox1.Controls.Add((Control) this.label1);
      this.groupBox1.Location = new Point(16, 386);
      this.groupBox1.Margin = new Padding(4);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Padding = new Padding(4);
      this.groupBox1.Size = new Size(637, 223);
      this.groupBox1.TabIndex = 2;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "String Edit";
      this.button1.BackColor = Color.LightCyan;
      this.button1.FlatStyle = FlatStyle.Flat;
      this.button1.Image = (Image) Resources._08;
      this.button1.ImageAlign = ContentAlignment.MiddleLeft;
      this.button1.Location = new Point(517, 182);
      this.button1.Margin = new Padding(4);
      this.button1.Name = "button1";
      this.button1.Size = new Size(96, 33);
      this.button1.TabIndex = 7;
      this.button1.Text = "      Save";
      this.button1.UseVisualStyleBackColor = false;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.textBox6.Enabled = false;
      this.textBox6.Location = new Point(19, 39);
      this.textBox6.Margin = new Padding(4);
      this.textBox6.Name = "textBox6";
      this.textBox6.Size = new Size(64, 22);
      this.textBox6.TabIndex = 4;
      this.textBox6.TextChanged += new EventHandler(this.textBox6_TextChanged);
      this.textBox5.Location = new Point(104, 39);
      this.textBox5.Margin = new Padding(4);
      this.textBox5.Name = "textBox5";
      this.textBox5.Size = new Size(509, 22);
      this.textBox5.TabIndex = 3;
      this.textBox5.TextChanged += new EventHandler(this.textBox5_TextChanged);
      this.label2.AutoSize = true;
      this.label2.Location = new Point(100, 20);
      this.label2.Margin = new Padding(4, 0, 4, 0);
      this.label2.Name = "label2";
      this.label2.Size = new Size(44, 16);
      this.label2.TabIndex = 1;
      this.label2.Text = "String:";
      this.label1.AutoSize = true;
      this.label1.Location = new Point(15, 20);
      this.label1.Margin = new Padding(4, 0, 4, 0);
      this.label1.Name = "label1";
      this.label1.Size = new Size(42, 16);
      this.label1.TabIndex = 0;
      this.label1.Text = "Index:";
      this.listBox1.FormattingEnabled = true;
      this.listBox1.ItemHeight = 16;
      this.listBox1.Location = new Point(8, 21);
      this.listBox1.Margin = new Padding(4);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new Size(621, 260);
      this.listBox1.TabIndex = 7;
      this.listBox1.SelectedIndexChanged += new EventHandler(this.listBox1_SelectedIndexChanged);
      this.groupBox5.Controls.Add((Control) this.textBox1);
      this.groupBox5.Controls.Add((Control) this.label7);
      this.groupBox5.Location = new Point(16, 15);
      this.groupBox5.Margin = new Padding(4);
      this.groupBox5.Name = "groupBox5";
      this.groupBox5.Padding = new Padding(4);
      this.groupBox5.Size = new Size(356, 60);
      this.groupBox5.TabIndex = 33;
      this.groupBox5.TabStop = false;
      this.groupBox5.Text = "Search";
      this.textBox1.BorderStyle = BorderStyle.FixedSingle;
      this.textBox1.Location = new Point(57, 23);
      this.textBox1.Margin = new Padding(4);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(287, 22);
      this.textBox1.TabIndex = 83;
      this.textBox1.TextChanged += new EventHandler(this.textBox1_TextChanged);
      this.label7.AutoSize = true;
      this.label7.Location = new Point(8, 26);
      this.label7.Margin = new Padding(4, 0, 4, 0);
      this.label7.Name = "label7";
      this.label7.Size = new Size(36, 16);
      this.label7.TabIndex = 21;
      this.label7.Text = "Text:";
      this.groupBox2.Controls.Add((Control) this.listBox1);
      this.groupBox2.Location = new Point(16, 82);
      this.groupBox2.Margin = new Padding(4);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Padding = new Padding(4);
      this.groupBox2.Size = new Size(637, 297);
      this.groupBox2.TabIndex = 34;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "String";
      this.groupBox3.Controls.Add((Control) this.listBox2);
      this.groupBox3.Location = new Point(670, 82);
      this.groupBox3.Margin = new Padding(4);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Padding = new Padding(4);
      this.groupBox3.Size = new Size(637, 297);
      this.groupBox3.TabIndex = 36;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "String";
      this.listBox2.FormattingEnabled = true;
      this.listBox2.ItemHeight = 16;
      this.listBox2.Location = new Point(8, 21);
      this.listBox2.Margin = new Padding(4);
      this.listBox2.Name = "listBox2";
      this.listBox2.Size = new Size(621, 260);
      this.listBox2.TabIndex = 7;
      this.listBox2.SelectedIndexChanged += new EventHandler(this.listBox2_SelectedIndexChanged);
      this.groupBox4.Controls.Add((Control) this.textBox7);
      this.groupBox4.Controls.Add((Control) this.button8);
      this.groupBox4.Controls.Add((Control) this.textBox2);
      this.groupBox4.Controls.Add((Control) this.textBox3);
      this.groupBox4.Controls.Add((Control) this.label3);
      this.groupBox4.Controls.Add((Control) this.label4);
      this.groupBox4.Location = new Point(670, 386);
      this.groupBox4.Margin = new Padding(4);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Padding = new Padding(4);
      this.groupBox4.Size = new Size(637, 223);
      this.groupBox4.TabIndex = 35;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "String Edit";
      this.button8.BackColor = Color.LightCyan;
      this.button8.FlatStyle = FlatStyle.Flat;
      this.button8.Image = (Image) Resources._08;
      this.button8.ImageAlign = ContentAlignment.MiddleLeft;
      this.button8.Location = new Point(517, 182);
      this.button8.Margin = new Padding(4);
      this.button8.Name = "button8";
      this.button8.Size = new Size(96, 33);
      this.button8.TabIndex = 7;
      this.button8.Text = "      Save";
      this.button8.UseVisualStyleBackColor = false;
      this.button8.Click += new EventHandler(this.button8_Click);
      this.textBox2.Enabled = false;
      this.textBox2.Location = new Point(19, 39);
      this.textBox2.Margin = new Padding(4);
      this.textBox2.Name = "textBox2";
      this.textBox2.Size = new Size(64, 22);
      this.textBox2.TabIndex = 4;
      this.textBox3.Location = new Point(104, 39);
      this.textBox3.Margin = new Padding(4);
      this.textBox3.Name = "textBox3";
      this.textBox3.Size = new Size(509, 22);
      this.textBox3.TabIndex = 3;
      this.label3.AutoSize = true;
      this.label3.Location = new Point(100, 20);
      this.label3.Margin = new Padding(4, 0, 4, 0);
      this.label3.Name = "label3";
      this.label3.Size = new Size(44, 16);
      this.label3.TabIndex = 1;
      this.label3.Text = "String:";
      this.label4.AutoSize = true;
      this.label4.Location = new Point(15, 20);
      this.label4.Margin = new Padding(4, 0, 4, 0);
      this.label4.Name = "label4";
      this.label4.Size = new Size(42, 16);
      this.label4.TabIndex = 0;
      this.label4.Text = "Index:";
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
      this.comboBox1.Location = new Point(671, 48);
      this.comboBox1.Margin = new Padding(4);
      this.comboBox1.Name = "comboBox1";
      this.comboBox1.Size = new Size(160, 24);
      this.comboBox1.TabIndex = 70;
      this.comboBox1.SelectedIndexChanged += new EventHandler(this.comboBox1_SelectedIndexChanged);
      this.textBox8.Enabled = false;
      this.textBox8.Location = new Point(734, 21);
      this.textBox8.Margin = new Padding(4);
      this.textBox8.Name = "textBox8";
      this.textBox8.Size = new Size(64, 22);
      this.textBox8.TabIndex = 69;
      this.label5.AutoSize = true;
      this.label5.Location = new Point(667, 29);
      this.label5.Margin = new Padding(4, 0, 4, 0);
      this.label5.Name = "label5";
      this.label5.Size = new Size(55, 16);
      this.label5.TabIndex = 68;
      this.label5.Text = "Country:";
      this.textBox4.BorderStyle = BorderStyle.FixedSingle;
      this.textBox4.Location = new Point(103, 68);
      this.textBox4.Multiline = true;
      this.textBox4.Name = "textBox4";
      this.textBox4.Size = new Size(510, 80);
      this.textBox4.TabIndex = 68;
      this.textBox7.BorderStyle = BorderStyle.FixedSingle;
      this.textBox7.Location = new Point(104, 68);
      this.textBox7.Multiline = true;
      this.textBox7.Name = "textBox7";
      this.textBox7.Size = new Size(510, 80);
      this.textBox7.TabIndex = 69;
      this.AutoScaleDimensions = new SizeF(8f, 16f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(1320, 622);
      this.Controls.Add((Control) this.comboBox1);
      this.Controls.Add((Control) this.textBox8);
      this.Controls.Add((Control) this.label5);
      this.Controls.Add((Control) this.groupBox3);
      this.Controls.Add((Control) this.groupBox4);
      this.Controls.Add((Control) this.groupBox2);
      this.Controls.Add((Control) this.groupBox5);
      this.Controls.Add((Control) this.groupBox1);
      this.FormBorderStyle = FormBorderStyle.Fixed3D;
      this.Margin = new Padding(4);
      this.MaximizeBox = false;
      this.Name = nameof (ItemStringCompare);
      this.Text = "LastChaos Item String Compare";
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.groupBox5.ResumeLayout(false);
      this.groupBox5.PerformLayout();
      this.groupBox2.ResumeLayout(false);
      this.groupBox3.ResumeLayout(false);
      this.groupBox4.ResumeLayout(false);
      this.groupBox4.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();
    }

    private void button8_Click(object sender, EventArgs e)
    {
      LcDevPack_TeamDamonA.ItemStringCompare.ItemStringCompare.namee = this.StringFromLanguage();
      if (this.comboBox1.SelectedIndex == 0)
      {
        string str = this.textBox7.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_item SET a_name_thai = '" + this.textBox3.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_descr_thai = '" + str + "' WHERE a_index = '" + this.textBox2.Text + "'");
      }
      if (this.comboBox1.SelectedIndex == 1)
      {
        string str = this.textBox7.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_item SET a_name_usa = '" + this.textBox3.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_descr_usa = '" + str + "' WHERE a_index = '" + this.textBox2.Text + "'");
      }
      if (this.comboBox1.SelectedIndex == 2)
      {
        string str = this.textBox7.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_item SET a_name_ger = '" + this.textBox3.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_descr_ger = '" + str + "' WHERE a_index = '" + this.textBox2.Text + "'");
      }
      if (this.comboBox1.SelectedIndex == 3)
      {
        string str = this.textBox7.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_item SET a_name_spn = '" + this.textBox3.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_descr_spn = '" + str + "' WHERE a_index = '" + this.textBox2.Text + "'");
      }
      if (this.comboBox1.SelectedIndex == 4)
      {
        string str = this.textBox7.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_item SET a_name_brz = '" + this.textBox3.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_descr_brz = '" + str + "' WHERE a_index = '" + this.textBox2.Text + "'");
      }
      else
      {
        string str = this.textBox7.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_item SET a_name_usa = '" + this.textBox3.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_descr_usa = '" + str + "' WHERE a_index = '" + this.textBox2.Text + "'");
      }
      int num = (int) MessageBox.Show("Update", "Completed", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
      int selectedIndex = this.listBox1.SelectedIndex;
      if (this.textBox1.Text != "")
        this.SearchList(this.textBox1.Text);
      else if (this.comboBox1.SelectedIndex == 0)
        this.LoadListBoxTHAI();
      else if (this.comboBox1.SelectedIndex == 1)
        this.LoadListBoxUSA();
      else if (this.comboBox1.SelectedIndex == 2)
        this.LoadListBoxGER();
      else if (this.comboBox1.SelectedIndex == 3)
        this.LoadListBoxESP();
      else if (this.comboBox1.SelectedIndex == 4)
        this.LoadListBoxBRA();
      else
        this.LoadListBox2();
      this.listBox2.SelectedIndex = selectedIndex;
    }
  }
}
