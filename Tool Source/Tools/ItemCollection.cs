// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.ItemCollection
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using LcDevPack_TeamDamonA.Properties;
using LcDevPack_TeamDamonA.Tools.MemoryWorker;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools
{
  public class ItemCollection : Form
  {
    public static Connection connection = new Connection();
    public string Host = ItemCollection.connection.Settings.SqlHost;
    public string User = ItemCollection.connection.Settings.SqlUser;
    public string Password = ItemCollection.connection.Settings.SqlPassword;
    public string Database = ItemCollection.connection.Settings.SqlDatabase;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    public string[] _needType = new string[6];
    public string[] menuArray = new string[2]
    {
      "a_theme",
      "a_theme_string"
    };
    private string language = ItemCollection.connection.Settings.Language;
    public string[] menuArrayGER = new string[2]
    {
      "a_theme",
      "a_theme_string_ger"
    };
    public string[] menuArrayRUS = new string[2]
    {
      "a_theme",
      "a_theme_string_rus"
    };
    public string[] menuArrayESP = new string[2]
    {
      "a_theme",
      "a_theme_string_spn"
    };
    public string[] menuArrayTHA = new string[2]
    {
      "a_theme",
      "a_theme_string_tld"
    };
    public string[] menuArrayUSA = new string[2]
    {
      "a_theme",
      "a_theme_string_usa"
    };
    public string[] menuArrayBRA = new string[2]
    {
      "a_theme",
      "a_theme_string_brz"
    };
    public string[] SearchMenu = new string[2]
    {
      "a_theme",
      "a_theme_string"
    };
    public List<string> MenuList = new List<string>();
    public List<string> MenuListSearch = new List<string>();
    private IContainer components = (IContainer) null;
    public int _index;
    public string _enable;
    public string _category;
    public string _texFileID;
    public string _texRow;
    public string _texCol;
    public string _resultType;
    public bool doesCollectionExist;
    private GroupBox groupBox5;
    private Label label7;
    private TextBox textBox1;
    private GroupBox groupBox3;
    private Button btnCopy;
    private Button btnDelete;
    private Button btnAdd;
    private ListBox listBox1;
    private Button button2;
    private GroupBox groupBox1;
    private Label label6;
    private TextBox TbTheme;
    private Label label5;
    private Label label1;
    private TextBox TbThemeString;
    private TextBox TbDescrString;
    private GroupBox groupBox2;
    private GroupBox groupBox4;
    private Label label4;
    private CheckBox checkBox1;
    private ComboBox comboBox1;
    private GroupBox groupBox7;
    private Button btnSave;
    private PictureBox pictureBox1;
    private LinkLabel linkLabel1;
    private GroupBox groupBox6;
    private TextBox TbNeedIndex1;
    private ComboBox comboBox2;
    private TextBox TbNeedCount1;
    private Label label2;
    private Label label8;
    private Label label3;
    private GroupBox groupBox8;
    private TextBox TbNeedCount2;
    private ComboBox comboBox3;
    private TextBox TbNeedIndex2;
    private Label label9;
    private Label label10;
    private Label label11;
    private GroupBox groupBox12;
    private TextBox TbNeedCount6;
    private ComboBox comboBox7;
    private TextBox TbNeedIndex6;
    private Label label21;
    private Label label22;
    private Label label23;
    private GroupBox groupBox11;
    private TextBox TbNeedCount5;
    private ComboBox comboBox6;
    private TextBox TbNeedIndex5;
    private Label label18;
    private Label label19;
    private Label label20;
    private GroupBox groupBox10;
    private TextBox TbNeedCount4;
    private ComboBox comboBox5;
    private TextBox TbNeedIndex4;
    private Label label15;
    private Label label16;
    private Label label17;
    private GroupBox groupBox9;
    private TextBox TbNeedCount3;
    private ComboBox comboBox4;
    private TextBox TbNeedIndex3;
    private Label label12;
    private Label label13;
    private Label label14;
    private TextBox TbResultCount;
    private ComboBox comboBox8;
    private TextBox TbResultIndex;
    private Label label26;
    private Label label24;
    private Label label25;
    private PictureBox pbNeed5;
    private PictureBox pbNeed4;
    private PictureBox pbNeed3;
    private PictureBox pbNeed2;
    private PictureBox pbNeed1;
    private PictureBox pbNeed6;
    private PictureBox pbResult;
    private TextBox tbResultType;
    private Label lblResultType;
    private TextBox tbNeed6;
    private TextBox tbNeed5;
    private TextBox tbNeed4;
    private TextBox tbNeed3;
    private TextBox tbNeed2;
    private TextBox tbNeed1;
    private TextBox tbCategory;
    private Label lblCount;
    private TextBox TbCollectionExist;
    private Button button1;
    private Label lblStatus;
    private TextBox TbId;
    private TextBox TbCol;
    private TextBox TbRow;
    private PictureBox PbSelectID6;
    private PictureBox PbSelectID5;
    private PictureBox PbSelectID4;
    private PictureBox PbSelectID3;
    private PictureBox PbSelectID2;
    private PictureBox PbSelectID1;
    private PictureBox PbResultItemIdx;
    private ToolTip toolTip2;
    private ToolTip toolTip1;
    private string namee;
    public string descrr;

    public string StringFromLanguage()
    {
      if (this.language == "GER")
      {
        this.namee = "a_theme_string_ger";
        return this.namee;
      }
      if (this.language == "RUS")
      {
        this.namee = "a_theme_string_rus";
        return this.namee;
      }
      if (this.language == "ESP")
      {
        this.namee = "a_theme_string_spn";
        return this.namee;
      }
      if (this.language == "BRA")
      {
        this.namee = "a_theme_string_brz";
        return this.namee;
      }
      if (this.language == "THA")
      {
        this.namee = "a_theme_string_thai";
        return this.namee;
      }
      if (!(this.language == "USA"))
        return (string) null;
      this.namee = "a_theme_string_usa";
      return this.namee;
    }

    public string DescrFromLanguage()
    {
      if (this.language == "GER")
      {
        this.descrr = "a_desc_string_ger";
        return this.descrr;
      }
      if (this.language == "POL")
      {
        this.descrr = "a_desc_string_pld";
        return this.descrr;
      }
      if (this.language == "BRA")
      {
        this.descrr = "a_desc_string_brz";
        return this.descrr;
      }
      if (this.language == "RUS")
      {
        this.descrr = "a_desc_string_rus";
        return this.descrr;
      }
      if (this.language == "FRA")
      {
        this.descrr = "a_desc_string_frc";
        return this.descrr;
      }
      if (this.language == "ESP")
      {
        this.descrr = "a_desc_string_spn";
        return this.descrr;
      }
      if (this.language == "THA")
      {
        this.descrr = "a_desc_string_thai";
        return this.descrr;
      }
      if (!(this.language == "USA"))
        return (string) null;
      this.descrr = "a_desc_string_usa";
      return this.descrr;
    }

    public ItemCollection() => this.InitializeComponent();

    private void IsCollectionInDB()
    {
      foreach (DataRow row in (InternalDataCollectionBase) mySQL.GetFromQuery("select a_theme FROM t_item_collection WHERE a_theme ='" + this.TbTheme.Text + "';").Rows)
      {
        this.TbCollectionExist.Text = Convert.ToString(row["a_theme"]);
        if (this.TbCollectionExist.Text != null || this.TbCollectionExist.Text != "")
        {
          this.doesCollectionExist = true;
        }
        else
        {
          this.TbCollectionExist.Text = "";
          this.doesCollectionExist = false;
        }
      }
    }

    public void ItemCollection_Import()
    {
      this.namee = this.StringFromLanguage();
      this.descrr = this.DescrFromLanguage();
      AllLists.tItemCollect_MenuData.Clear();
      LoadFromDatabase.LoadFromDatabaseSQL = "SELECT * FROM t_item_collection ORDER BY a_theme";
      foreach (DataRow row in (InternalDataCollectionBase) mySQL.GetFromQuery(LoadFromDatabase.LoadFromDatabaseSQL).Rows)
      {
        tItemCollection tItemCollection = new tItemCollection();
        tItemCollection.a_theme = Convert.ToInt32(row["a_theme"]);
        tItemCollection.a_category = Convert.ToInt32(row["a_category"]);
        tItemCollection.a_theme_string = Convert.ToString(row[this.namee ?? ""]);
        tItemCollection.a_descr_string = Convert.ToString(row[this.descrr ?? ""]);
        tItemCollection.a_enable = Convert.ToBoolean(row["a_enable"]);
        tItemCollection.a_id = Convert.ToInt32(row["a_id"]);
        tItemCollection.a_row = Convert.ToInt32(row["a_row"]);
        tItemCollection.a_col = Convert.ToInt32(row["a_col"]);
        tItemCollection.a_need1_type = Convert.ToInt32(row["a_need1_type"]);
        tItemCollection.a_need1_index = Convert.ToInt32(row["a_need1_index"]);
        tItemCollection.a_need1_num = Convert.ToInt32(row["a_need1_num"]);
        tItemCollection.a_need2_type = Convert.ToInt32(row["a_need2_type"]);
        tItemCollection.a_need2_index = Convert.ToInt32(row["a_need2_index"]);
        tItemCollection.a_need2_num = Convert.ToInt32(row["a_need2_num"]);
        tItemCollection.a_need3_type = Convert.ToInt32(row["a_need3_type"]);
        tItemCollection.a_need3_index = Convert.ToInt32(row["a_need3_index"]);
        tItemCollection.a_need3_num = Convert.ToInt32(row["a_need3_num"]);
        tItemCollection.a_need4_type = Convert.ToInt32(row["a_need4_type"]);
        tItemCollection.a_need4_index = Convert.ToInt32(row["a_need4_index"]);
        tItemCollection.a_need4_num = Convert.ToInt32(row["a_need4_num"]);
        tItemCollection.a_need5_type = Convert.ToInt32(row["a_need5_type"]);
        tItemCollection.a_need5_index = Convert.ToInt32(row["a_need5_index"]);
        tItemCollection.a_need5_num = Convert.ToInt32(row["a_need5_num"]);
        tItemCollection.a_need6_type = Convert.ToInt32(row["a_need6_type"]);
        tItemCollection.a_need6_index = Convert.ToInt32(row["a_need6_index"]);
        tItemCollection.a_need6_num = Convert.ToInt32(row["a_need6_num"]);
        tItemCollection.a_result_type = Convert.ToInt32(row["a_result_type"]);
        tItemCollection.a_result_index = Convert.ToInt32(row["a_result_index"]);
        tItemCollection.a_result_num = Convert.ToInt32(row["a_result_num"]);
        AllLists.tItemCollect_MenuData.Add(tItemCollection);
        AllLists.tItemCollect_Menu.Add(tItemCollection.a_theme.ToString() + " - " + tItemCollection.a_theme_string.ToString());
      }
    }

    private void ItemCollection_Load(object sender, EventArgs e)
    {
      mySQL.SetConnection();
      this.ItemCollection_Import();
      this.lblCount.Text = "Collection Count: " + AllLists.tItemCollect_MenuData.Count<tItemCollection>().ToString();
      this.LoadStartUpCombo();
      this.RefreshAll();
      this.SelectBoxes();
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

    private int GetID()
    {
      int result = -1;
      int.TryParse(this.listBox1.Text.Split(' ')[0], out result);
      return result;
    }

    private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      int CollectionIDx = this.GetID();
      if (CollectionIDx == -1)
        return;
      tItemCollection tItemCollection = AllLists.tItemCollect_MenuData.Find((Predicate<tItemCollection>) (p => p.a_theme.Equals(CollectionIDx)));
      if (tItemCollection == null)
        return;
      this.TbCollectionExist.Text = "";
      this.TbTheme.Text = tItemCollection.a_theme.ToString();
      this.TbThemeString.Text = tItemCollection.a_theme_string.ToString();
      this.TbDescrString.Text = tItemCollection.a_descr_string.ToString();
      this._enable = tItemCollection.a_enable.ToString();
      this._category = tItemCollection.a_category.ToString();
      this._texFileID = tItemCollection.a_id.ToString();
      this._texRow = tItemCollection.a_row.ToString();
      this._texCol = tItemCollection.a_col.ToString();
      this.TbId.Text = tItemCollection.a_id.ToString();
      this.TbRow.Text = tItemCollection.a_row.ToString();
      this.TbCol.Text = tItemCollection.a_col.ToString();
      this.tbNeed1.Text = tItemCollection.a_need1_type.ToString();
      this.TbNeedIndex1.Text = tItemCollection.a_need1_index.ToString();
      this.TbNeedCount1.Text = tItemCollection.a_need1_num.ToString();
      this.tbNeed2.Text = tItemCollection.a_need2_type.ToString();
      this.TbNeedIndex2.Text = tItemCollection.a_need2_index.ToString();
      this.TbNeedCount2.Text = tItemCollection.a_need2_num.ToString();
      this.tbNeed3.Text = tItemCollection.a_need3_type.ToString();
      this.TbNeedIndex3.Text = tItemCollection.a_need3_index.ToString();
      this.TbNeedCount3.Text = tItemCollection.a_need3_num.ToString();
      this.tbNeed4.Text = tItemCollection.a_need4_type.ToString();
      this.TbNeedIndex4.Text = tItemCollection.a_need4_index.ToString();
      this.TbNeedCount4.Text = tItemCollection.a_need4_num.ToString();
      this.tbNeed5.Text = tItemCollection.a_need5_type.ToString();
      this.TbNeedIndex5.Text = tItemCollection.a_need5_index.ToString();
      this.TbNeedCount5.Text = tItemCollection.a_need5_num.ToString();
      this.tbNeed6.Text = tItemCollection.a_need6_type.ToString();
      this.TbNeedIndex6.Text = tItemCollection.a_need6_index.ToString();
      this.TbNeedCount6.Text = tItemCollection.a_need6_num.ToString();
      this.tbResultType.Text = tItemCollection.a_result_type.ToString();
      this.TbResultIndex.Text = tItemCollection.a_result_index.ToString();
      this.TbResultCount.Text = tItemCollection.a_result_num.ToString();
      this.tbCategory.Text = tItemCollection.a_category.ToString();
      this.pictureBox1.Image = (Image) this.databaseHandle.IconItemCollection(int.Parse(this.TbId.Text), int.Parse(this.TbRow.Text), int.Parse(this.TbCol.Text));
      this.IsCollectionInDB();
      this.SelectBoxes();
      this.SetPublicValues();
      this.SetIcons();
    }

    private void SetPublicValues()
    {
      if (this._enable == "True")
      {
        this.checkBox1.Checked = true;
        this.checkBox1.BackColor = Color.Lime;
      }
      else
      {
        this.checkBox1.Checked = false;
        this.checkBox1.BackColor = Color.Red;
      }
    }

    private void RefreshAll()
    {
      this.listBox1.Items.Clear();
      List<int> SortedIDs = new List<int>();
      for (int index = 0; index < AllLists.tItemCollect_MenuData.Count<tItemCollection>(); ++index)
        SortedIDs.Add(AllLists.tItemCollect_MenuData[index].a_theme);
      SortedIDs.Sort();
      for (int a = 0; a < SortedIDs.Count<int>(); a++)
      {
        int index = AllLists.tItemCollect_MenuData.FindIndex((Predicate<tItemCollection>) (p => p.a_theme.Equals(SortedIDs[a])));
        if (index != -1)
          this.listBox1.Items.Add((object) (AllLists.tItemCollect_MenuData[index].a_theme.ToString() + " - " + AllLists.tItemCollect_MenuData[index].a_theme_string));
      }
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

    public bool SearchString(string s) => s.ToUpper().Contains(this.textBox1.Text.ToUpper());

    private void textBox1_TextChanged(object sender, EventArgs e)
    {
      this.MenuListSearch = this.MenuList.FindAll(new Predicate<string>(this.SearchString));
      this.listBox1.DataSource = (object) this.MenuListSearch;
    }

    private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
    {
      this.TbId.Text = "0";
      this.TbRow.Text = "0";
      this.TbCol.Text = "0";
      IconPickerItemCollection pickerItemCollection = new IconPickerItemCollection();
      if (pickerItemCollection.ShowDialog() != DialogResult.OK)
        return;
      TextBox tbId = this.TbId;
      int num = pickerItemCollection.TexID;
      string str1 = num.ToString();
      tbId.Text = str1;
      TextBox tbRow = this.TbRow;
      num = pickerItemCollection.TexRow;
      string str2 = num.ToString();
      tbRow.Text = str2;
      TextBox tbCol = this.TbCol;
      num = pickerItemCollection.TexColumn;
      string str3 = num.ToString();
      tbCol.Text = str3;
      this.pictureBox1.Image = (Image) this.databaseHandle.IconItemCollection(int.Parse(this.TbId.Text), int.Parse(this.TbRow.Text), int.Parse(this.TbCol.Text));
    }

    private void SetIcons()
    {
      if (this.TbNeedIndex1.Text != "" && this.tbNeed1.Text == "1")
        this.pbNeed1.Image = (Image) this.databaseHandle.IconFast(Convert.ToInt32(this.TbNeedIndex1.Text));
      if (this.tbNeed1.Text != "1")
        this.pbNeed1.Image = (Image) null;
      if (this.TbNeedIndex2.Text != "" && this.tbNeed2.Text == "1")
        this.pbNeed2.Image = (Image) this.databaseHandle.IconFast(Convert.ToInt32(this.TbNeedIndex2.Text));
      if (this.tbNeed2.Text != "1")
        this.pbNeed2.Image = (Image) null;
      if (this.TbNeedIndex3.Text != "" && this.tbNeed3.Text == "1")
        this.pbNeed3.Image = (Image) this.databaseHandle.IconFast(Convert.ToInt32(this.TbNeedIndex3.Text));
      if (this.tbNeed3.Text != "1")
        this.pbNeed3.Image = (Image) null;
      if (this.TbNeedIndex4.Text != "" && this.tbNeed4.Text == "1")
        this.pbNeed4.Image = (Image) this.databaseHandle.IconFast(Convert.ToInt32(this.TbNeedIndex4.Text));
      if (this.tbNeed4.Text != "1")
        this.pbNeed4.Image = (Image) null;
      if (this.TbNeedIndex5.Text != "" && this.tbNeed5.Text == "1")
        this.pbNeed5.Image = (Image) this.databaseHandle.IconFast(Convert.ToInt32(this.TbNeedIndex5.Text));
      if (this.tbNeed5.Text != "1")
        this.pbNeed5.Image = (Image) null;
      if (this.tbResultType.Text == "1")
        this.pbResult.Image = (Image) this.databaseHandle.IconFast(Convert.ToInt32(this.TbResultIndex.Text));
      else
        this.pbResult.Image = (Image) null;
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      this.components = (IContainer) new System.ComponentModel.Container();
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (ItemCollection));
      this.groupBox5 = new GroupBox();
      this.label7 = new Label();
      this.textBox1 = new TextBox();
      this.groupBox3 = new GroupBox();
      this.btnCopy = new Button();
      this.btnDelete = new Button();
      this.btnAdd = new Button();
      this.listBox1 = new ListBox();
      this.button2 = new Button();
      this.groupBox1 = new GroupBox();
      this.checkBox1 = new CheckBox();
      this.label6 = new Label();
      this.TbTheme = new TextBox();
      this.label5 = new Label();
      this.label1 = new Label();
      this.TbThemeString = new TextBox();
      this.TbDescrString = new TextBox();
      this.groupBox2 = new GroupBox();
      this.groupBox12 = new GroupBox();
      this.PbSelectID6 = new PictureBox();
      this.tbNeed6 = new TextBox();
      this.pbNeed6 = new PictureBox();
      this.TbNeedCount6 = new TextBox();
      this.comboBox7 = new ComboBox();
      this.TbNeedIndex6 = new TextBox();
      this.label21 = new Label();
      this.label22 = new Label();
      this.label23 = new Label();
      this.groupBox11 = new GroupBox();
      this.PbSelectID5 = new PictureBox();
      this.tbNeed5 = new TextBox();
      this.pbNeed5 = new PictureBox();
      this.TbNeedCount5 = new TextBox();
      this.comboBox6 = new ComboBox();
      this.TbNeedIndex5 = new TextBox();
      this.label18 = new Label();
      this.label19 = new Label();
      this.label20 = new Label();
      this.groupBox10 = new GroupBox();
      this.PbSelectID4 = new PictureBox();
      this.tbNeed4 = new TextBox();
      this.pbNeed4 = new PictureBox();
      this.TbNeedCount4 = new TextBox();
      this.comboBox5 = new ComboBox();
      this.TbNeedIndex4 = new TextBox();
      this.label15 = new Label();
      this.label16 = new Label();
      this.label17 = new Label();
      this.groupBox9 = new GroupBox();
      this.PbSelectID3 = new PictureBox();
      this.tbNeed3 = new TextBox();
      this.pbNeed3 = new PictureBox();
      this.TbNeedCount3 = new TextBox();
      this.comboBox4 = new ComboBox();
      this.TbNeedIndex3 = new TextBox();
      this.label12 = new Label();
      this.label13 = new Label();
      this.label14 = new Label();
      this.groupBox8 = new GroupBox();
      this.PbSelectID2 = new PictureBox();
      this.tbNeed2 = new TextBox();
      this.pbNeed2 = new PictureBox();
      this.TbNeedCount2 = new TextBox();
      this.comboBox3 = new ComboBox();
      this.TbNeedIndex2 = new TextBox();
      this.label9 = new Label();
      this.label10 = new Label();
      this.label11 = new Label();
      this.groupBox6 = new GroupBox();
      this.PbSelectID1 = new PictureBox();
      this.tbNeed1 = new TextBox();
      this.pbNeed1 = new PictureBox();
      this.TbNeedIndex1 = new TextBox();
      this.comboBox2 = new ComboBox();
      this.TbNeedCount1 = new TextBox();
      this.label2 = new Label();
      this.label8 = new Label();
      this.label3 = new Label();
      this.groupBox4 = new GroupBox();
      this.tbCategory = new TextBox();
      this.comboBox1 = new ComboBox();
      this.label4 = new Label();
      this.groupBox7 = new GroupBox();
      this.PbResultItemIdx = new PictureBox();
      this.pbResult = new PictureBox();
      this.TbResultCount = new TextBox();
      this.comboBox8 = new ComboBox();
      this.TbResultIndex = new TextBox();
      this.label26 = new Label();
      this.label24 = new Label();
      this.label25 = new Label();
      this.btnSave = new Button();
      this.linkLabel1 = new LinkLabel();
      this.pictureBox1 = new PictureBox();
      this.toolTip1 = new ToolTip(this.components);
      this.tbResultType = new TextBox();
      this.lblResultType = new Label();
      this.lblCount = new Label();
      this.TbCollectionExist = new TextBox();
      this.button1 = new Button();
      this.lblStatus = new Label();
      this.TbId = new TextBox();
      this.TbCol = new TextBox();
      this.TbRow = new TextBox();
      this.toolTip2 = new ToolTip(this.components);
      this.groupBox5.SuspendLayout();
      this.groupBox3.SuspendLayout();
      this.groupBox1.SuspendLayout();
      this.groupBox2.SuspendLayout();
      this.groupBox12.SuspendLayout();
      ((ISupportInitialize) this.PbSelectID6).BeginInit();
      ((ISupportInitialize) this.pbNeed6).BeginInit();
      this.groupBox11.SuspendLayout();
      ((ISupportInitialize) this.PbSelectID5).BeginInit();
      ((ISupportInitialize) this.pbNeed5).BeginInit();
      this.groupBox10.SuspendLayout();
      ((ISupportInitialize) this.PbSelectID4).BeginInit();
      ((ISupportInitialize) this.pbNeed4).BeginInit();
      this.groupBox9.SuspendLayout();
      ((ISupportInitialize) this.PbSelectID3).BeginInit();
      ((ISupportInitialize) this.pbNeed3).BeginInit();
      this.groupBox8.SuspendLayout();
      ((ISupportInitialize) this.PbSelectID2).BeginInit();
      ((ISupportInitialize) this.pbNeed2).BeginInit();
      this.groupBox6.SuspendLayout();
      ((ISupportInitialize) this.PbSelectID1).BeginInit();
      ((ISupportInitialize) this.pbNeed1).BeginInit();
      this.groupBox4.SuspendLayout();
      this.groupBox7.SuspendLayout();
      ((ISupportInitialize) this.PbResultItemIdx).BeginInit();
      ((ISupportInitialize) this.pbResult).BeginInit();
      ((ISupportInitialize) this.pictureBox1).BeginInit();
      this.SuspendLayout();
      this.groupBox5.Controls.Add((Control) this.label7);
      this.groupBox5.Controls.Add((Control) this.textBox1);
      this.groupBox5.Location = new Point(12, 12);
      this.groupBox5.Name = "groupBox5";
      this.groupBox5.Size = new Size(265, 49);
      this.groupBox5.TabIndex = 33;
      this.groupBox5.TabStop = false;
      this.groupBox5.Text = "Search";
      this.label7.AutoSize = true;
      this.label7.Location = new Point(6, 21);
      this.label7.Name = "label7";
      this.label7.Size = new Size(31, 13);
      this.label7.TabIndex = 21;
      this.label7.Text = "Text:";
      this.textBox1.BorderStyle = BorderStyle.FixedSingle;
      this.textBox1.Location = new Point(53, 19);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(206, 20);
      this.textBox1.TabIndex = 20;
      this.textBox1.TextChanged += new EventHandler(this.textBox1_TextChanged);
      this.groupBox3.Controls.Add((Control) this.btnCopy);
      this.groupBox3.Controls.Add((Control) this.btnDelete);
      this.groupBox3.Controls.Add((Control) this.btnAdd);
      this.groupBox3.Controls.Add((Control) this.listBox1);
      this.groupBox3.Location = new Point(12, 67);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Size = new Size(265, 467);
      this.groupBox3.TabIndex = 34;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "Items";
      this.btnCopy.BackColor = Color.Gainsboro;
      this.btnCopy.FlatStyle = FlatStyle.Flat;
      this.btnCopy.Location = new Point(94, 434);
      this.btnCopy.Name = "btnCopy";
      this.btnCopy.Size = new Size(70, 23);
      this.btnCopy.TabIndex = 5;
      this.btnCopy.Text = "Copy";
      this.btnCopy.UseVisualStyleBackColor = false;
      this.btnCopy.Click += new EventHandler(this.btnCopy_Click);
      this.btnDelete.BackColor = Color.Gainsboro;
      this.btnDelete.FlatStyle = FlatStyle.Flat;
      this.btnDelete.Location = new Point(170, 434);
      this.btnDelete.Name = "btnDelete";
      this.btnDelete.Size = new Size(86, 23);
      this.btnDelete.TabIndex = 4;
      this.btnDelete.Text = "Delete";
      this.btnDelete.UseVisualStyleBackColor = false;
      this.btnDelete.Click += new EventHandler(this.btnDelete_Click);
      this.btnAdd.BackColor = Color.Gainsboro;
      this.btnAdd.FlatStyle = FlatStyle.Flat;
      this.btnAdd.Location = new Point(3, 434);
      this.btnAdd.Name = "btnAdd";
      this.btnAdd.Size = new Size(85, 23);
      this.btnAdd.TabIndex = 2;
      this.btnAdd.Text = "Add";
      this.btnAdd.UseVisualStyleBackColor = false;
      this.btnAdd.Click += new EventHandler(this.btnAdd_Click);
      this.listBox1.FormattingEnabled = true;
      this.listBox1.Location = new Point(6, 19);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new Size(253, 407);
      this.listBox1.TabIndex = 1;
      this.listBox1.SelectedIndexChanged += new EventHandler(this.listBox1_SelectedIndexChanged);
      this.button2.FlatStyle = FlatStyle.Flat;
      this.button2.Location = new Point(947, 597);
      this.button2.Name = "button2";
      this.button2.Size = new Size(100, 23);
      this.button2.TabIndex = 35;
      this.button2.Text = "Save";
      this.button2.UseVisualStyleBackColor = true;
      this.groupBox1.Controls.Add((Control) this.checkBox1);
      this.groupBox1.Controls.Add((Control) this.label6);
      this.groupBox1.Controls.Add((Control) this.TbTheme);
      this.groupBox1.Controls.Add((Control) this.label5);
      this.groupBox1.Controls.Add((Control) this.label1);
      this.groupBox1.Controls.Add((Control) this.TbThemeString);
      this.groupBox1.Controls.Add((Control) this.TbDescrString);
      this.groupBox1.Location = new Point(283, 12);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(315, 166);
      this.groupBox1.TabIndex = 36;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Basic";
      this.checkBox1.AutoSize = true;
      this.checkBox1.Location = new Point(134, 20);
      this.checkBox1.Name = "checkBox1";
      this.checkBox1.Size = new Size(59, 17);
      this.checkBox1.TabIndex = 41;
      this.checkBox1.Text = "Enable";
      this.checkBox1.UseVisualStyleBackColor = true;
      this.label6.AutoSize = true;
      this.label6.Location = new Point(11, 73);
      this.label6.Name = "label6";
      this.label6.Size = new Size(35, 13);
      this.label6.TabIndex = 12;
      this.label6.Text = "Desc:";
      this.TbTheme.BorderStyle = BorderStyle.FixedSingle;
      this.TbTheme.Location = new Point(67, 19);
      this.TbTheme.Name = "TbTheme";
      this.TbTheme.Size = new Size(51, 20);
      this.TbTheme.TabIndex = 1;
      this.label5.AutoSize = true;
      this.label5.Location = new Point(11, 47);
      this.label5.Name = "label5";
      this.label5.Size = new Size(38, 13);
      this.label5.TabIndex = 11;
      this.label5.Text = "Name:";
      this.label1.AutoSize = true;
      this.label1.Location = new Point(11, 21);
      this.label1.Name = "label1";
      this.label1.Size = new Size(36, 13);
      this.label1.TabIndex = 7;
      this.label1.Text = "Index:";
      this.TbThemeString.BorderStyle = BorderStyle.FixedSingle;
      this.TbThemeString.Location = new Point(67, 45);
      this.TbThemeString.Name = "TbThemeString";
      this.TbThemeString.Size = new Size(242, 20);
      this.TbThemeString.TabIndex = 5;
      this.TbDescrString.BorderStyle = BorderStyle.FixedSingle;
      this.TbDescrString.Location = new Point(67, 71);
      this.TbDescrString.Multiline = true;
      this.TbDescrString.Name = "TbDescrString";
      this.TbDescrString.Size = new Size(242, 83);
      this.TbDescrString.TabIndex = 6;
      this.groupBox2.Controls.Add((Control) this.groupBox12);
      this.groupBox2.Controls.Add((Control) this.groupBox11);
      this.groupBox2.Controls.Add((Control) this.groupBox10);
      this.groupBox2.Controls.Add((Control) this.groupBox9);
      this.groupBox2.Controls.Add((Control) this.groupBox8);
      this.groupBox2.Controls.Add((Control) this.groupBox6);
      this.groupBox2.Location = new Point(283, 184);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new Size(610, 252);
      this.groupBox2.TabIndex = 37;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "Need Items";
      this.groupBox12.Controls.Add((Control) this.PbSelectID6);
      this.groupBox12.Controls.Add((Control) this.tbNeed6);
      this.groupBox12.Controls.Add((Control) this.pbNeed6);
      this.groupBox12.Controls.Add((Control) this.TbNeedCount6);
      this.groupBox12.Controls.Add((Control) this.comboBox7);
      this.groupBox12.Controls.Add((Control) this.TbNeedIndex6);
      this.groupBox12.Controls.Add((Control) this.label21);
      this.groupBox12.Controls.Add((Control) this.label22);
      this.groupBox12.Controls.Add((Control) this.label23);
      this.groupBox12.Location = new Point(354, 132);
      this.groupBox12.Name = "groupBox12";
      this.groupBox12.Size = new Size(168, 107);
      this.groupBox12.TabIndex = 7;
      this.groupBox12.TabStop = false;
      this.groupBox12.Text = "Need 6";
      this.PbSelectID6.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbSelectID6.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbSelectID6.Location = new Point(97, 43);
      this.PbSelectID6.Name = "PbSelectID6";
      this.PbSelectID6.Size = new Size(22, 22);
      this.PbSelectID6.TabIndex = 117;
      this.PbSelectID6.TabStop = false;
      this.PbSelectID6.Click += new EventHandler(this.PbSelectID6_Click);
      this.tbNeed6.Location = new Point(132, 20);
      this.tbNeed6.Name = "tbNeed6";
      this.tbNeed6.Size = new Size(31, 20);
      this.tbNeed6.TabIndex = 104;
      this.pbNeed6.BackColor = SystemColors.ButtonHighlight;
      this.pbNeed6.BorderStyle = BorderStyle.FixedSingle;
      this.pbNeed6.Cursor = Cursors.Default;
      this.pbNeed6.Location = new Point(131, 62);
      this.pbNeed6.Name = "pbNeed6";
      this.pbNeed6.Size = new Size(32, 32);
      this.pbNeed6.SizeMode = PictureBoxSizeMode.StretchImage;
      this.pbNeed6.TabIndex = 100;
      this.pbNeed6.TabStop = false;
      this.pbNeed6.MouseHover += new EventHandler(this.pbNeed6_MouseHover);
      this.TbNeedCount6.BorderStyle = BorderStyle.FixedSingle;
      this.TbNeedCount6.Location = new Point(46, 74);
      this.TbNeedCount6.Name = "TbNeedCount6";
      this.TbNeedCount6.Size = new Size(46, 20);
      this.TbNeedCount6.TabIndex = 5;
      this.comboBox7.FlatStyle = FlatStyle.Flat;
      this.comboBox7.FormattingEnabled = true;
      this.comboBox7.Location = new Point(46, 19);
      this.comboBox7.Name = "comboBox7";
      this.comboBox7.Size = new Size(85, 21);
      this.comboBox7.TabIndex = 0;
      this.comboBox7.SelectedIndexChanged += new EventHandler(this.comboBox7_SelectedIndexChanged);
      this.TbNeedIndex6.BorderStyle = BorderStyle.FixedSingle;
      this.TbNeedIndex6.Location = new Point(46, 46);
      this.TbNeedIndex6.Name = "TbNeedIndex6";
      this.TbNeedIndex6.Size = new Size(46, 20);
      this.TbNeedIndex6.TabIndex = 4;
      this.TbNeedIndex6.TextChanged += new EventHandler(this.TbNeedIndex6_TextChanged);
      this.label21.AutoSize = true;
      this.label21.Location = new Point(6, 21);
      this.label21.Name = "label21";
      this.label21.Size = new Size(34, 13);
      this.label21.TabIndex = 1;
      this.label21.Text = "Type:";
      this.label22.AutoSize = true;
      this.label22.Location = new Point(6, 76);
      this.label22.Name = "label22";
      this.label22.Size = new Size(38, 13);
      this.label22.TabIndex = 3;
      this.label22.Text = "Count:";
      this.label23.AutoSize = true;
      this.label23.Location = new Point(6, 47);
      this.label23.Name = "label23";
      this.label23.Size = new Size(36, 13);
      this.label23.TabIndex = 2;
      this.label23.Text = "Index:";
      this.groupBox11.Controls.Add((Control) this.PbSelectID5);
      this.groupBox11.Controls.Add((Control) this.tbNeed5);
      this.groupBox11.Controls.Add((Control) this.pbNeed5);
      this.groupBox11.Controls.Add((Control) this.TbNeedCount5);
      this.groupBox11.Controls.Add((Control) this.comboBox6);
      this.groupBox11.Controls.Add((Control) this.TbNeedIndex5);
      this.groupBox11.Controls.Add((Control) this.label18);
      this.groupBox11.Controls.Add((Control) this.label19);
      this.groupBox11.Controls.Add((Control) this.label20);
      this.groupBox11.Location = new Point(184, 132);
      this.groupBox11.Name = "groupBox11";
      this.groupBox11.Size = new Size(168, 107);
      this.groupBox11.TabIndex = 10;
      this.groupBox11.TabStop = false;
      this.groupBox11.Text = "Need 5";
      this.PbSelectID5.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbSelectID5.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbSelectID5.Location = new Point(96, 43);
      this.PbSelectID5.Name = "PbSelectID5";
      this.PbSelectID5.Size = new Size(22, 22);
      this.PbSelectID5.TabIndex = 114;
      this.PbSelectID5.TabStop = false;
      this.PbSelectID5.Click += new EventHandler(this.PbSelectID5_Click);
      this.tbNeed5.Location = new Point(132, 20);
      this.tbNeed5.Name = "tbNeed5";
      this.tbNeed5.Size = new Size(31, 20);
      this.tbNeed5.TabIndex = 103;
      this.pbNeed5.BackColor = SystemColors.ButtonHighlight;
      this.pbNeed5.BorderStyle = BorderStyle.FixedSingle;
      this.pbNeed5.Cursor = Cursors.Default;
      this.pbNeed5.Location = new Point(131, 62);
      this.pbNeed5.Name = "pbNeed5";
      this.pbNeed5.Size = new Size(32, 32);
      this.pbNeed5.SizeMode = PictureBoxSizeMode.StretchImage;
      this.pbNeed5.TabIndex = 102;
      this.pbNeed5.TabStop = false;
      this.pbNeed5.MouseHover += new EventHandler(this.pbNeed5_MouseHover);
      this.TbNeedCount5.BorderStyle = BorderStyle.FixedSingle;
      this.TbNeedCount5.Location = new Point(46, 74);
      this.TbNeedCount5.Name = "TbNeedCount5";
      this.TbNeedCount5.Size = new Size(46, 20);
      this.TbNeedCount5.TabIndex = 5;
      this.comboBox6.FlatStyle = FlatStyle.Flat;
      this.comboBox6.FormattingEnabled = true;
      this.comboBox6.Location = new Point(46, 19);
      this.comboBox6.Name = "comboBox6";
      this.comboBox6.Size = new Size(85, 21);
      this.comboBox6.TabIndex = 0;
      this.comboBox6.SelectedIndexChanged += new EventHandler(this.comboBox6_SelectedIndexChanged);
      this.TbNeedIndex5.BorderStyle = BorderStyle.FixedSingle;
      this.TbNeedIndex5.Location = new Point(46, 45);
      this.TbNeedIndex5.Name = "TbNeedIndex5";
      this.TbNeedIndex5.Size = new Size(46, 20);
      this.TbNeedIndex5.TabIndex = 4;
      this.TbNeedIndex5.TextChanged += new EventHandler(this.TbNeedIndex5_TextChanged);
      this.label18.AutoSize = true;
      this.label18.Location = new Point(6, 21);
      this.label18.Name = "label18";
      this.label18.Size = new Size(34, 13);
      this.label18.TabIndex = 1;
      this.label18.Text = "Type:";
      this.label19.AutoSize = true;
      this.label19.Location = new Point(6, 76);
      this.label19.Name = "label19";
      this.label19.Size = new Size(38, 13);
      this.label19.TabIndex = 3;
      this.label19.Text = "Count:";
      this.label20.AutoSize = true;
      this.label20.Location = new Point(6, 47);
      this.label20.Name = "label20";
      this.label20.Size = new Size(36, 13);
      this.label20.TabIndex = 2;
      this.label20.Text = "Index:";
      this.groupBox10.Controls.Add((Control) this.PbSelectID4);
      this.groupBox10.Controls.Add((Control) this.tbNeed4);
      this.groupBox10.Controls.Add((Control) this.pbNeed4);
      this.groupBox10.Controls.Add((Control) this.TbNeedCount4);
      this.groupBox10.Controls.Add((Control) this.comboBox5);
      this.groupBox10.Controls.Add((Control) this.TbNeedIndex4);
      this.groupBox10.Controls.Add((Control) this.label15);
      this.groupBox10.Controls.Add((Control) this.label16);
      this.groupBox10.Controls.Add((Control) this.label17);
      this.groupBox10.Location = new Point(14, 132);
      this.groupBox10.Name = "groupBox10";
      this.groupBox10.Size = new Size(168, 107);
      this.groupBox10.TabIndex = 9;
      this.groupBox10.TabStop = false;
      this.groupBox10.Text = "Need 4";
      this.PbSelectID4.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbSelectID4.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbSelectID4.Location = new Point(95, 43);
      this.PbSelectID4.Name = "PbSelectID4";
      this.PbSelectID4.Size = new Size(22, 22);
      this.PbSelectID4.TabIndex = 113;
      this.PbSelectID4.TabStop = false;
      this.PbSelectID4.Click += new EventHandler(this.PbSelectID4_Click);
      this.tbNeed4.Location = new Point(133, 20);
      this.tbNeed4.Name = "tbNeed4";
      this.tbNeed4.Size = new Size(31, 20);
      this.tbNeed4.TabIndex = 102;
      this.pbNeed4.BackColor = SystemColors.ButtonHighlight;
      this.pbNeed4.BorderStyle = BorderStyle.FixedSingle;
      this.pbNeed4.Cursor = Cursors.Default;
      this.pbNeed4.Location = new Point(132, 62);
      this.pbNeed4.Name = "pbNeed4";
      this.pbNeed4.Size = new Size(32, 32);
      this.pbNeed4.SizeMode = PictureBoxSizeMode.StretchImage;
      this.pbNeed4.TabIndex = 101;
      this.pbNeed4.TabStop = false;
      this.pbNeed4.MouseHover += new EventHandler(this.pbNeed4_MouseHover);
      this.TbNeedCount4.BorderStyle = BorderStyle.FixedSingle;
      this.TbNeedCount4.Location = new Point(46, 74);
      this.TbNeedCount4.Name = "TbNeedCount4";
      this.TbNeedCount4.Size = new Size(46, 20);
      this.TbNeedCount4.TabIndex = 5;
      this.comboBox5.FlatStyle = FlatStyle.Flat;
      this.comboBox5.FormattingEnabled = true;
      this.comboBox5.Location = new Point(46, 19);
      this.comboBox5.Name = "comboBox5";
      this.comboBox5.Size = new Size(85, 21);
      this.comboBox5.TabIndex = 0;
      this.comboBox5.SelectedIndexChanged += new EventHandler(this.comboBox5_SelectedIndexChanged);
      this.TbNeedIndex4.BorderStyle = BorderStyle.FixedSingle;
      this.TbNeedIndex4.Location = new Point(45, 45);
      this.TbNeedIndex4.Name = "TbNeedIndex4";
      this.TbNeedIndex4.Size = new Size(46, 20);
      this.TbNeedIndex4.TabIndex = 4;
      this.TbNeedIndex4.TextChanged += new EventHandler(this.TextBox16_TextChanged);
      this.label15.AutoSize = true;
      this.label15.Location = new Point(6, 21);
      this.label15.Name = "label15";
      this.label15.Size = new Size(34, 13);
      this.label15.TabIndex = 1;
      this.label15.Text = "Type:";
      this.label16.AutoSize = true;
      this.label16.Location = new Point(6, 76);
      this.label16.Name = "label16";
      this.label16.Size = new Size(38, 13);
      this.label16.TabIndex = 3;
      this.label16.Text = "Count:";
      this.label17.AutoSize = true;
      this.label17.Location = new Point(6, 47);
      this.label17.Name = "label17";
      this.label17.Size = new Size(36, 13);
      this.label17.TabIndex = 2;
      this.label17.Text = "Index:";
      this.groupBox9.Controls.Add((Control) this.PbSelectID3);
      this.groupBox9.Controls.Add((Control) this.tbNeed3);
      this.groupBox9.Controls.Add((Control) this.pbNeed3);
      this.groupBox9.Controls.Add((Control) this.TbNeedCount3);
      this.groupBox9.Controls.Add((Control) this.comboBox4);
      this.groupBox9.Controls.Add((Control) this.TbNeedIndex3);
      this.groupBox9.Controls.Add((Control) this.label12);
      this.groupBox9.Controls.Add((Control) this.label13);
      this.groupBox9.Controls.Add((Control) this.label14);
      this.groupBox9.Location = new Point(356, 19);
      this.groupBox9.Name = "groupBox9";
      this.groupBox9.Size = new Size(168, 107);
      this.groupBox9.TabIndex = 8;
      this.groupBox9.TabStop = false;
      this.groupBox9.Text = "Need 3";
      this.PbSelectID3.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbSelectID3.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbSelectID3.Location = new Point(98, 43);
      this.PbSelectID3.Name = "PbSelectID3";
      this.PbSelectID3.Size = new Size(22, 22);
      this.PbSelectID3.TabIndex = 116;
      this.PbSelectID3.TabStop = false;
      this.PbSelectID3.Click += new EventHandler(this.PbSelectID3_Click);
      this.tbNeed3.Location = new Point(131, 19);
      this.tbNeed3.Name = "tbNeed3";
      this.tbNeed3.Size = new Size(31, 20);
      this.tbNeed3.TabIndex = 103;
      this.pbNeed3.BackColor = SystemColors.ButtonHighlight;
      this.pbNeed3.BorderStyle = BorderStyle.FixedSingle;
      this.pbNeed3.Cursor = Cursors.Default;
      this.pbNeed3.Location = new Point(130, 62);
      this.pbNeed3.Name = "pbNeed3";
      this.pbNeed3.Size = new Size(32, 32);
      this.pbNeed3.SizeMode = PictureBoxSizeMode.StretchImage;
      this.pbNeed3.TabIndex = 100;
      this.pbNeed3.TabStop = false;
      this.pbNeed3.MouseHover += new EventHandler(this.pbNeed3_MouseHover);
      this.TbNeedCount3.BorderStyle = BorderStyle.FixedSingle;
      this.TbNeedCount3.Location = new Point(46, 74);
      this.TbNeedCount3.Name = "TbNeedCount3";
      this.TbNeedCount3.Size = new Size(46, 20);
      this.TbNeedCount3.TabIndex = 5;
      this.comboBox4.FlatStyle = FlatStyle.Flat;
      this.comboBox4.FormattingEnabled = true;
      this.comboBox4.Location = new Point(46, 19);
      this.comboBox4.Name = "comboBox4";
      this.comboBox4.Size = new Size(85, 21);
      this.comboBox4.TabIndex = 0;
      this.comboBox4.SelectedIndexChanged += new EventHandler(this.comboBox4_SelectedIndexChanged);
      this.TbNeedIndex3.BorderStyle = BorderStyle.FixedSingle;
      this.TbNeedIndex3.Location = new Point(46, 45);
      this.TbNeedIndex3.Name = "TbNeedIndex3";
      this.TbNeedIndex3.Size = new Size(46, 20);
      this.TbNeedIndex3.TabIndex = 4;
      this.TbNeedIndex3.TextChanged += new EventHandler(this.TextBox14_TextChanged);
      this.label12.AutoSize = true;
      this.label12.Location = new Point(6, 21);
      this.label12.Name = "label12";
      this.label12.Size = new Size(34, 13);
      this.label12.TabIndex = 1;
      this.label12.Text = "Type:";
      this.label13.AutoSize = true;
      this.label13.Location = new Point(6, 76);
      this.label13.Name = "label13";
      this.label13.Size = new Size(38, 13);
      this.label13.TabIndex = 3;
      this.label13.Text = "Count:";
      this.label14.AutoSize = true;
      this.label14.Location = new Point(6, 47);
      this.label14.Name = "label14";
      this.label14.Size = new Size(36, 13);
      this.label14.TabIndex = 2;
      this.label14.Text = "Index:";
      this.groupBox8.Controls.Add((Control) this.PbSelectID2);
      this.groupBox8.Controls.Add((Control) this.tbNeed2);
      this.groupBox8.Controls.Add((Control) this.pbNeed2);
      this.groupBox8.Controls.Add((Control) this.TbNeedCount2);
      this.groupBox8.Controls.Add((Control) this.comboBox3);
      this.groupBox8.Controls.Add((Control) this.TbNeedIndex2);
      this.groupBox8.Controls.Add((Control) this.label9);
      this.groupBox8.Controls.Add((Control) this.label10);
      this.groupBox8.Controls.Add((Control) this.label11);
      this.groupBox8.Location = new Point(185, 19);
      this.groupBox8.Name = "groupBox8";
      this.groupBox8.Size = new Size(168, 107);
      this.groupBox8.TabIndex = 7;
      this.groupBox8.TabStop = false;
      this.groupBox8.Text = "Need 2";
      this.PbSelectID2.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbSelectID2.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbSelectID2.Location = new Point(95, 45);
      this.PbSelectID2.Name = "PbSelectID2";
      this.PbSelectID2.Size = new Size(22, 22);
      this.PbSelectID2.TabIndex = 115;
      this.PbSelectID2.TabStop = false;
      this.PbSelectID2.Click += new EventHandler(this.PbSelectID2_Click);
      this.tbNeed2.Location = new Point(131, 19);
      this.tbNeed2.Name = "tbNeed2";
      this.tbNeed2.Size = new Size(31, 20);
      this.tbNeed2.TabIndex = 102;
      this.pbNeed2.BackColor = SystemColors.ButtonHighlight;
      this.pbNeed2.BorderStyle = BorderStyle.FixedSingle;
      this.pbNeed2.Cursor = Cursors.Default;
      this.pbNeed2.Location = new Point(130, 62);
      this.pbNeed2.Name = "pbNeed2";
      this.pbNeed2.Size = new Size(32, 32);
      this.pbNeed2.SizeMode = PictureBoxSizeMode.StretchImage;
      this.pbNeed2.TabIndex = 100;
      this.pbNeed2.TabStop = false;
      this.pbNeed2.MouseHover += new EventHandler(this.pbNeed2_MouseHover);
      this.TbNeedCount2.BorderStyle = BorderStyle.FixedSingle;
      this.TbNeedCount2.Location = new Point(46, 74);
      this.TbNeedCount2.Name = "TbNeedCount2";
      this.TbNeedCount2.Size = new Size(46, 20);
      this.TbNeedCount2.TabIndex = 5;
      this.comboBox3.FlatStyle = FlatStyle.Flat;
      this.comboBox3.FormattingEnabled = true;
      this.comboBox3.Location = new Point(46, 19);
      this.comboBox3.Name = "comboBox3";
      this.comboBox3.Size = new Size(85, 21);
      this.comboBox3.TabIndex = 0;
      this.comboBox3.SelectedIndexChanged += new EventHandler(this.comboBox3_SelectedIndexChanged);
      this.TbNeedIndex2.BorderStyle = BorderStyle.FixedSingle;
      this.TbNeedIndex2.Location = new Point(46, 45);
      this.TbNeedIndex2.Name = "TbNeedIndex2";
      this.TbNeedIndex2.Size = new Size(46, 20);
      this.TbNeedIndex2.TabIndex = 4;
      this.TbNeedIndex2.TextChanged += new EventHandler(this.TextBox12_TextChanged);
      this.label9.AutoSize = true;
      this.label9.Location = new Point(6, 21);
      this.label9.Name = "label9";
      this.label9.Size = new Size(34, 13);
      this.label9.TabIndex = 1;
      this.label9.Text = "Type:";
      this.label10.AutoSize = true;
      this.label10.Location = new Point(6, 76);
      this.label10.Name = "label10";
      this.label10.Size = new Size(38, 13);
      this.label10.TabIndex = 3;
      this.label10.Text = "Count:";
      this.label11.AutoSize = true;
      this.label11.Location = new Point(6, 47);
      this.label11.Name = "label11";
      this.label11.Size = new Size(36, 13);
      this.label11.TabIndex = 2;
      this.label11.Text = "Index:";
      this.groupBox6.Controls.Add((Control) this.PbSelectID1);
      this.groupBox6.Controls.Add((Control) this.tbNeed1);
      this.groupBox6.Controls.Add((Control) this.pbNeed1);
      this.groupBox6.Controls.Add((Control) this.TbNeedIndex1);
      this.groupBox6.Controls.Add((Control) this.comboBox2);
      this.groupBox6.Controls.Add((Control) this.TbNeedCount1);
      this.groupBox6.Controls.Add((Control) this.label2);
      this.groupBox6.Controls.Add((Control) this.label8);
      this.groupBox6.Controls.Add((Control) this.label3);
      this.groupBox6.Location = new Point(14, 19);
      this.groupBox6.Name = "groupBox6";
      this.groupBox6.Size = new Size(168, 107);
      this.groupBox6.TabIndex = 6;
      this.groupBox6.TabStop = false;
      this.groupBox6.Text = "Need 1";
      this.PbSelectID1.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbSelectID1.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbSelectID1.Location = new Point(97, 45);
      this.PbSelectID1.Name = "PbSelectID1";
      this.PbSelectID1.Size = new Size(22, 22);
      this.PbSelectID1.TabIndex = 112;
      this.PbSelectID1.TabStop = false;
      this.PbSelectID1.Click += new EventHandler(this.PbSelectID1_Click);
      this.tbNeed1.Location = new Point(133, 20);
      this.tbNeed1.Name = "tbNeed1";
      this.tbNeed1.Size = new Size(31, 20);
      this.tbNeed1.TabIndex = 101;
      this.pbNeed1.BackColor = SystemColors.ButtonHighlight;
      this.pbNeed1.BorderStyle = BorderStyle.FixedSingle;
      this.pbNeed1.Cursor = Cursors.Default;
      this.pbNeed1.Location = new Point(132, 62);
      this.pbNeed1.Name = "pbNeed1";
      this.pbNeed1.Size = new Size(32, 32);
      this.pbNeed1.SizeMode = PictureBoxSizeMode.StretchImage;
      this.pbNeed1.TabIndex = 99;
      this.pbNeed1.TabStop = false;
      this.pbNeed1.MouseHover += new EventHandler(this.pbNeed1_MouseHover);
      this.TbNeedIndex1.BorderStyle = BorderStyle.FixedSingle;
      this.TbNeedIndex1.Location = new Point(46, 45);
      this.TbNeedIndex1.Name = "TbNeedIndex1";
      this.TbNeedIndex1.Size = new Size(45, 20);
      this.TbNeedIndex1.TabIndex = 5;
      this.TbNeedIndex1.TextChanged += new EventHandler(this.TextBox6_TextChanged);
      this.comboBox2.FlatStyle = FlatStyle.Flat;
      this.comboBox2.FormattingEnabled = true;
      this.comboBox2.Location = new Point(46, 19);
      this.comboBox2.Name = "comboBox2";
      this.comboBox2.Size = new Size(85, 21);
      this.comboBox2.TabIndex = 0;
      this.comboBox2.SelectedIndexChanged += new EventHandler(this.comboBox2_SelectedIndexChanged);
      this.TbNeedCount1.BorderStyle = BorderStyle.FixedSingle;
      this.TbNeedCount1.Location = new Point(46, 74);
      this.TbNeedCount1.Name = "TbNeedCount1";
      this.TbNeedCount1.Size = new Size(45, 20);
      this.TbNeedCount1.TabIndex = 4;
      this.label2.AutoSize = true;
      this.label2.Location = new Point(6, 21);
      this.label2.Name = "label2";
      this.label2.Size = new Size(34, 13);
      this.label2.TabIndex = 1;
      this.label2.Text = "Type:";
      this.label8.AutoSize = true;
      this.label8.Location = new Point(6, 76);
      this.label8.Name = "label8";
      this.label8.Size = new Size(38, 13);
      this.label8.TabIndex = 3;
      this.label8.Text = "Count:";
      this.label3.AutoSize = true;
      this.label3.Location = new Point(6, 47);
      this.label3.Name = "label3";
      this.label3.Size = new Size(36, 13);
      this.label3.TabIndex = 2;
      this.label3.Text = "Index:";
      this.groupBox4.Controls.Add((Control) this.tbCategory);
      this.groupBox4.Controls.Add((Control) this.comboBox1);
      this.groupBox4.Controls.Add((Control) this.label4);
      this.groupBox4.Location = new Point(604, 86);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Size = new Size(299, 49);
      this.groupBox4.TabIndex = 40;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "Category";
      this.tbCategory.Location = new Point((int) byte.MaxValue, 17);
      this.tbCategory.Name = "tbCategory";
      this.tbCategory.Size = new Size(43, 20);
      this.tbCategory.TabIndex = 104;
      this.comboBox1.FlatStyle = FlatStyle.Flat;
      this.comboBox1.FormattingEnabled = true;
      this.comboBox1.Location = new Point(64, 16);
      this.comboBox1.Name = "comboBox1";
      this.comboBox1.Size = new Size(186, 21);
      this.comboBox1.TabIndex = 40;
      this.comboBox1.SelectedIndexChanged += new EventHandler(this.comboBox1_SelectedIndexChanged);
      this.comboBox1.SelectionChangeCommitted += new EventHandler(this.comboBox1_SelectionChangeCommitted);
      this.label4.AutoSize = true;
      this.label4.Location = new Point(6, 19);
      this.label4.Name = "label4";
      this.label4.Size = new Size(52, 13);
      this.label4.TabIndex = 39;
      this.label4.Text = "Category:";
      this.groupBox7.Controls.Add((Control) this.PbResultItemIdx);
      this.groupBox7.Controls.Add((Control) this.pbResult);
      this.groupBox7.Controls.Add((Control) this.TbResultCount);
      this.groupBox7.Controls.Add((Control) this.comboBox8);
      this.groupBox7.Controls.Add((Control) this.TbResultIndex);
      this.groupBox7.Controls.Add((Control) this.label26);
      this.groupBox7.Controls.Add((Control) this.label24);
      this.groupBox7.Controls.Add((Control) this.label25);
      this.groupBox7.Location = new Point(283, 442);
      this.groupBox7.Name = "groupBox7";
      this.groupBox7.Size = new Size(524, 53);
      this.groupBox7.TabIndex = 42;
      this.groupBox7.TabStop = false;
      this.groupBox7.Text = "Result";
      this.PbResultItemIdx.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbResultItemIdx.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbResultItemIdx.Location = new Point(270, 18);
      this.PbResultItemIdx.Name = "PbResultItemIdx";
      this.PbResultItemIdx.Size = new Size(22, 22);
      this.PbResultItemIdx.TabIndex = 114;
      this.PbResultItemIdx.TabStop = false;
      this.PbResultItemIdx.Click += new EventHandler(this.PbResultItemIdx_Click);
      this.pbResult.BackColor = SystemColors.ButtonHighlight;
      this.pbResult.BorderStyle = BorderStyle.FixedSingle;
      this.pbResult.Cursor = Cursors.Default;
      this.pbResult.Location = new Point(485, 15);
      this.pbResult.Name = "pbResult";
      this.pbResult.Size = new Size(32, 32);
      this.pbResult.SizeMode = PictureBoxSizeMode.StretchImage;
      this.pbResult.TabIndex = 101;
      this.pbResult.TabStop = false;
      this.pbResult.MouseHover += new EventHandler(this.pbResult_MouseHover);
      this.TbResultCount.BorderStyle = BorderStyle.FixedSingle;
      this.TbResultCount.Location = new Point(385, 19);
      this.TbResultCount.Name = "TbResultCount";
      this.TbResultCount.Size = new Size(85, 20);
      this.TbResultCount.TabIndex = 5;
      this.comboBox8.FlatStyle = FlatStyle.Flat;
      this.comboBox8.FormattingEnabled = true;
      this.comboBox8.Location = new Point(46, 19);
      this.comboBox8.Name = "comboBox8";
      this.comboBox8.Size = new Size(85, 21);
      this.comboBox8.TabIndex = 0;
      this.comboBox8.SelectedIndexChanged += new EventHandler(this.comboBox8_SelectedIndexChanged);
      this.TbResultIndex.BorderStyle = BorderStyle.FixedSingle;
      this.TbResultIndex.Location = new Point(179, 19);
      this.TbResultIndex.Name = "TbResultIndex";
      this.TbResultIndex.Size = new Size(85, 20);
      this.TbResultIndex.TabIndex = 4;
      this.TbResultIndex.TextChanged += new EventHandler(this.TextBox18_TextChanged);
      this.label26.AutoSize = true;
      this.label26.Location = new Point(137, 22);
      this.label26.Name = "label26";
      this.label26.Size = new Size(36, 13);
      this.label26.TabIndex = 2;
      this.label26.Text = "Index:";
      this.label24.AutoSize = true;
      this.label24.Location = new Point(6, 21);
      this.label24.Name = "label24";
      this.label24.Size = new Size(34, 13);
      this.label24.TabIndex = 1;
      this.label24.Text = "Type:";
      this.label25.AutoSize = true;
      this.label25.Location = new Point(341, 22);
      this.label25.Name = "label25";
      this.label25.Size = new Size(38, 13);
      this.label25.TabIndex = 3;
      this.label25.Text = "Count:";
      this.btnSave.BackColor = Color.Gainsboro;
      this.btnSave.FlatStyle = FlatStyle.Flat;
      this.btnSave.Location = new Point(683, 507);
      this.btnSave.Name = "btnSave";
      this.btnSave.Size = new Size(85, 23);
      this.btnSave.TabIndex = 6;
      this.btnSave.Text = "Save";
      this.btnSave.UseVisualStyleBackColor = false;
      this.btnSave.Click += new EventHandler(this.btnSave_Click);
      this.linkLabel1.AutoSize = true;
      this.linkLabel1.LinkColor = Color.Blue;
      this.linkLabel1.Location = new Point(665, 57);
      this.linkLabel1.Name = "linkLabel1";
      this.linkLabel1.Size = new Size(61, 13);
      this.linkLabel1.TabIndex = 98;
      this.linkLabel1.TabStop = true;
      this.linkLabel1.Text = "Icon Picker";
      this.linkLabel1.LinkClicked += new LinkLabelLinkClickedEventHandler(this.linkLabel1_LinkClicked);
      this.pictureBox1.BackColor = SystemColors.ButtonHighlight;
      this.pictureBox1.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox1.Cursor = Cursors.Default;
      this.pictureBox1.Location = new Point(604, 19);
      this.pictureBox1.Name = "pictureBox1";
      this.pictureBox1.Size = new Size(58, 58);
      this.pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
      this.pictureBox1.TabIndex = 96;
      this.pictureBox1.TabStop = false;
      this.tbResultType.Location = new Point(341, 503);
      this.tbResultType.Name = "tbResultType";
      this.tbResultType.Size = new Size(73, 20);
      this.tbResultType.TabIndex = 99;
      this.tbResultType.Visible = false;
      this.lblResultType.AutoSize = true;
      this.lblResultType.Location = new Point(292, 507);
      this.lblResultType.Name = "lblResultType";
      this.lblResultType.Size = new Size(44, 13);
      this.lblResultType.TabIndex = 100;
      this.lblResultType.Text = "ResultT";
      this.lblResultType.Visible = false;
      this.lblCount.AutoSize = true;
      this.lblCount.Font = new Font("Microsoft Sans Serif", 9.75f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.lblCount.ForeColor = Color.Blue;
      this.lblCount.Location = new Point(19, 537);
      this.lblCount.Name = "lblCount";
      this.lblCount.Size = new Size(0, 16);
      this.lblCount.TabIndex = 101;
      this.TbCollectionExist.Location = new Point(613, 141);
      this.TbCollectionExist.Name = "TbCollectionExist";
      this.TbCollectionExist.Size = new Size(23, 20);
      this.TbCollectionExist.TabIndex = 102;
      this.TbCollectionExist.Visible = false;
      this.button1.BackColor = Color.Gainsboro;
      this.button1.FlatStyle = FlatStyle.Flat;
      this.button1.Location = new Point(797, 507);
      this.button1.Name = "button1";
      this.button1.Size = new Size(105, 23);
      this.button1.TabIndex = 103;
      this.button1.Text = "Save And Next";
      this.button1.UseVisualStyleBackColor = false;
      this.lblStatus.AutoSize = true;
      this.lblStatus.Font = new Font("Microsoft Sans Serif", 9.75f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.lblStatus.ForeColor = Color.Blue;
      this.lblStatus.Location = new Point(367, 537);
      this.lblStatus.Name = "lblStatus";
      this.lblStatus.Size = new Size(0, 16);
      this.lblStatus.TabIndex = 104;
      this.TbId.Location = new Point(699, 25);
      this.TbId.Name = "TbId";
      this.TbId.Size = new Size(27, 20);
      this.TbId.TabIndex = 105;
      this.TbCol.Location = new Point(732, 25);
      this.TbCol.Name = "TbCol";
      this.TbCol.Size = new Size(27, 20);
      this.TbCol.TabIndex = 106;
      this.TbRow.Location = new Point(765, 26);
      this.TbRow.Name = "TbRow";
      this.TbRow.Size = new Size(27, 20);
      this.TbRow.TabIndex = 107;
      this.ClientSize = new Size(905, 561);
      this.Controls.Add((Control) this.TbRow);
      this.Controls.Add((Control) this.TbCol);
      this.Controls.Add((Control) this.TbId);
      this.Controls.Add((Control) this.lblStatus);
      this.Controls.Add((Control) this.button1);
      this.Controls.Add((Control) this.TbCollectionExist);
      this.Controls.Add((Control) this.lblCount);
      this.Controls.Add((Control) this.lblResultType);
      this.Controls.Add((Control) this.tbResultType);
      this.Controls.Add((Control) this.linkLabel1);
      this.Controls.Add((Control) this.btnSave);
      this.Controls.Add((Control) this.groupBox7);
      this.Controls.Add((Control) this.pictureBox1);
      this.Controls.Add((Control) this.groupBox4);
      this.Controls.Add((Control) this.groupBox2);
      this.Controls.Add((Control) this.groupBox1);
      this.Controls.Add((Control) this.button2);
      this.Controls.Add((Control) this.groupBox3);
      this.Controls.Add((Control) this.groupBox5);
      this.Icon = (Icon) componentResourceManager.GetObject("$this.Icon");
      this.Name = nameof (ItemCollection);
      this.Text = nameof (ItemCollection);
      this.Load += new EventHandler(this.ItemCollection_Load);
      this.groupBox5.ResumeLayout(false);
      this.groupBox5.PerformLayout();
      this.groupBox3.ResumeLayout(false);
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.groupBox2.ResumeLayout(false);
      this.groupBox12.ResumeLayout(false);
      this.groupBox12.PerformLayout();
      ((ISupportInitialize) this.PbSelectID6).EndInit();
      ((ISupportInitialize) this.pbNeed6).EndInit();
      this.groupBox11.ResumeLayout(false);
      this.groupBox11.PerformLayout();
      ((ISupportInitialize) this.PbSelectID5).EndInit();
      ((ISupportInitialize) this.pbNeed5).EndInit();
      this.groupBox10.ResumeLayout(false);
      this.groupBox10.PerformLayout();
      ((ISupportInitialize) this.PbSelectID4).EndInit();
      ((ISupportInitialize) this.pbNeed4).EndInit();
      this.groupBox9.ResumeLayout(false);
      this.groupBox9.PerformLayout();
      ((ISupportInitialize) this.PbSelectID3).EndInit();
      ((ISupportInitialize) this.pbNeed3).EndInit();
      this.groupBox8.ResumeLayout(false);
      this.groupBox8.PerformLayout();
      ((ISupportInitialize) this.PbSelectID2).EndInit();
      ((ISupportInitialize) this.pbNeed2).EndInit();
      this.groupBox6.ResumeLayout(false);
      this.groupBox6.PerformLayout();
      ((ISupportInitialize) this.PbSelectID1).EndInit();
      ((ISupportInitialize) this.pbNeed1).EndInit();
      this.groupBox4.ResumeLayout(false);
      this.groupBox4.PerformLayout();
      this.groupBox7.ResumeLayout(false);
      this.groupBox7.PerformLayout();
      ((ISupportInitialize) this.PbResultItemIdx).EndInit();
      ((ISupportInitialize) this.pbResult).EndInit();
      ((ISupportInitialize) this.pictureBox1).EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();
    }

    private void LoadStartUpCombo()
    {
      this.comboBox1.Items.AddRange(new object[4]
      {
        (object) "1 - The greatest hero",
        (object) "2 - The alchemy of all creation",
        (object) "3 - The richest trader",
        (object) "4 - The courageous adventurer"
      });
      this.comboBox2.Items.AddRange(new object[3]
      {
        (object) "0 - NONE",
        (object) "1 - ITEM",
        (object) "2 - THEME"
      });
      this.comboBox3.Items.AddRange(new object[3]
      {
        (object) "0 - NONE",
        (object) "1 - ITEM",
        (object) "2 - THEME"
      });
      this.comboBox4.Items.AddRange(new object[3]
      {
        (object) "0 - NONE",
        (object) "1 - ITEM",
        (object) "2 - THEME"
      });
      this.comboBox5.Items.AddRange(new object[3]
      {
        (object) "0 - NONE",
        (object) "1 - ITEM",
        (object) "2 - THEME"
      });
      this.comboBox6.Items.AddRange(new object[3]
      {
        (object) "0 - NONE",
        (object) "1 - ITEM",
        (object) "2 - THEME"
      });
      this.comboBox7.Items.AddRange(new object[3]
      {
        (object) "0 - NONE",
        (object) "1 - ITEM",
        (object) "2 - THEME"
      });
      this.comboBox8.Items.AddRange(new object[4]
      {
        (object) "1 - ITEM",
        (object) "2 - GOLD",
        (object) "3 - EXP",
        (object) "4 - SP"
      });
    }

    private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.tbCategory.Text = this.GetIndexByComboBox(this.comboBox1.Text).ToString();
    }

    private void SelectBoxes()
    {
      int num1 = this.comboBox1.FindString(this.tbCategory.Text);
      int num2 = this.comboBox2.FindString(this.tbNeed1.Text);
      int num3 = this.comboBox3.FindString(this.tbNeed2.Text);
      int num4 = this.comboBox4.FindString(this.tbNeed3.Text);
      int num5 = this.comboBox5.FindString(this.tbNeed4.Text);
      int num6 = this.comboBox6.FindString(this.tbNeed5.Text);
      int num7 = this.comboBox7.FindString(this.tbNeed6.Text);
      int num8 = this.comboBox8.FindString(this.tbResultType.Text);
      this.comboBox1.SelectedIndex = num1;
      this.comboBox2.SelectedIndex = num2;
      this.comboBox3.SelectedIndex = num3;
      this.comboBox4.SelectedIndex = num4;
      this.comboBox5.SelectedIndex = num5;
      this.comboBox6.SelectedIndex = num6;
      this.comboBox7.SelectedIndex = num7;
      this.comboBox8.SelectedIndex = num8;
    }

    private void comboBox1_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.comboBox1.BackColor = Color.Pink;
    }

    private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.tbNeed1.Text = this.GetIndexByComboBox(this.comboBox2.Text).ToString();
    }

    private void comboBox3_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.tbNeed2.Text = this.GetIndexByComboBox(this.comboBox3.Text).ToString();
    }

    private void comboBox4_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.tbNeed3.Text = this.GetIndexByComboBox(this.comboBox4.Text).ToString();
    }

    private void comboBox5_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.tbNeed4.Text = this.GetIndexByComboBox(this.comboBox5.Text).ToString();
    }

    private void comboBox6_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.tbNeed5.Text = this.GetIndexByComboBox(this.comboBox6.Text).ToString();
    }

    private void comboBox7_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.tbNeed6.Text = this.GetIndexByComboBox(this.comboBox7.Text).ToString();
    }

    private void comboBox8_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.tbResultType.Text = this.GetIndexByComboBox(this.comboBox8.Text).ToString();
    }

    private void btnSave_Click(object sender, EventArgs e)
    {
      int ThemeID = this.GetID();
      int index = AllLists.tItemCollect_MenuData.FindIndex((Predicate<tItemCollection>) (p => p.a_theme.Equals(ThemeID)));
      if (index == -1)
        return;
      string menu = AllLists.tItemCollect_MenuData[index].Menu;
      AllLists.tItemCollect_MenuData[index].a_theme = int.Parse(this.TbTheme.Text);
      AllLists.tItemCollect_MenuData[index].a_enable = this.checkBox1.Checked;
      int num1 = AllLists.tItemCollect_MenuData[index].a_enable != Convert.ToBoolean("true") ? 0 : 1;
      AllLists.tItemCollect_MenuData[index].a_category = int.Parse(this.tbCategory.Text);
      this.comboBox1.SelectedIndex = AllLists.tItemCollect_MenuData[index].a_category - 1;
      AllLists.tItemCollect_MenuData[index].a_theme_string = Convert.ToString(this.TbThemeString.Text);
      AllLists.tItemCollect_MenuData[index].a_descr_string = Convert.ToString(this.TbDescrString.Text);
      AllLists.tItemCollect_MenuData[index].a_id = int.Parse(this.TbId.Text);
      AllLists.tItemCollect_MenuData[index].a_col = int.Parse(this.TbCol.Text);
      AllLists.tItemCollect_MenuData[index].a_row = int.Parse(this.TbRow.Text);
      AllLists.tItemCollect_MenuData[index].a_need1_type = int.Parse(this.tbNeed1.Text);
      AllLists.tItemCollect_MenuData[index].a_need1_index = int.Parse(this.TbNeedIndex1.Text);
      AllLists.tItemCollect_MenuData[index].a_need1_num = int.Parse(this.TbNeedCount1.Text);
      AllLists.tItemCollect_MenuData[index].a_need2_type = int.Parse(this.tbNeed2.Text);
      AllLists.tItemCollect_MenuData[index].a_need2_index = int.Parse(this.TbNeedIndex2.Text);
      AllLists.tItemCollect_MenuData[index].a_need2_num = int.Parse(this.TbNeedCount2.Text);
      AllLists.tItemCollect_MenuData[index].a_need3_type = int.Parse(this.tbNeed3.Text);
      AllLists.tItemCollect_MenuData[index].a_need3_index = int.Parse(this.TbNeedIndex3.Text);
      AllLists.tItemCollect_MenuData[index].a_need3_num = int.Parse(this.TbNeedCount3.Text);
      AllLists.tItemCollect_MenuData[index].a_need4_type = int.Parse(this.tbNeed4.Text);
      AllLists.tItemCollect_MenuData[index].a_need4_index = int.Parse(this.TbNeedIndex4.Text);
      AllLists.tItemCollect_MenuData[index].a_need4_num = int.Parse(this.TbNeedCount4.Text);
      AllLists.tItemCollect_MenuData[index].a_need5_type = int.Parse(this.tbNeed5.Text);
      AllLists.tItemCollect_MenuData[index].a_need5_index = int.Parse(this.TbNeedIndex5.Text);
      AllLists.tItemCollect_MenuData[index].a_need5_num = int.Parse(this.TbNeedCount5.Text);
      AllLists.tItemCollect_MenuData[index].a_need6_type = int.Parse(this.tbNeed6.Text);
      AllLists.tItemCollect_MenuData[index].a_need6_index = int.Parse(this.TbNeedIndex6.Text);
      AllLists.tItemCollect_MenuData[index].a_need6_num = int.Parse(this.TbNeedCount6.Text);
      AllLists.tItemCollect_MenuData[index].a_result_type = int.Parse(this.tbResultType.Text);
      AllLists.tItemCollect_MenuData[index].a_result_index = int.Parse(this.TbResultIndex.Text);
      AllLists.tItemCollect_MenuData[index].a_result_num = int.Parse(this.TbResultCount.Text);
      AllLists.tItemCollect_MenuData[index].Menu = AllLists.tItemCollect_MenuData[index].a_theme.ToString() + " - " + AllLists.tItemCollect_MenuData[index].a_theme_string;
      this.listBox1.Items[this.listBox1.SelectedIndex] = (object) AllLists.tItemCollect_MenuData[index].Menu;
      this.listBox1.SelectedItem = (object) AllLists.tItemCollect_MenuData[index].Menu;
      this.doesCollectionExist = false;
      this.IsCollectionInDB();
      if (this.doesCollectionExist)
      {
        mySQL.UpdateQuery("UPDATE t_item_collection SET a_theme = '" + AllLists.tItemCollect_MenuData[index].a_theme.ToString() + "',a_enable ='" + AllLists.tItemCollect_MenuData[index].a_enable.ToString() + "',a_category ='" + AllLists.tItemCollect_MenuData[index].a_category.ToString() + "',a_theme_string ='" + AllLists.tItemCollect_MenuData[index].a_theme_string + "',a_desc_string = '" + AllLists.tItemCollect_MenuData[index].a_descr_string + "',a_id ='" + AllLists.tItemCollect_MenuData[index].a_id.ToString() + "',a_row = '" + AllLists.tItemCollect_MenuData[index].a_row.ToString() + "',a_col = '" + AllLists.tItemCollect_MenuData[index].a_col.ToString() + "', a_need1_type = '" + AllLists.tItemCollect_MenuData[index].a_need1_type.ToString() + "',a_need1_num = '" + AllLists.tItemCollect_MenuData[index].a_need1_num.ToString() + "',a_need1_index = '" + AllLists.tItemCollect_MenuData[index].a_need1_index.ToString() + "',a_need2_type = '" + AllLists.tItemCollect_MenuData[index].a_need2_type.ToString() + "',a_need2_index = '" + AllLists.tItemCollect_MenuData[index].a_need2_index.ToString() + "',a_need2_num = '" + AllLists.tItemCollect_MenuData[index].a_need2_num.ToString() + "',a_need3_type = '" + AllLists.tItemCollect_MenuData[index].a_need3_type.ToString() + "',a_need3_index = '" + AllLists.tItemCollect_MenuData[index].a_need3_index.ToString() + "',a_need3_num = '" + AllLists.tItemCollect_MenuData[index].a_need3_num.ToString() + "',a_need4_type = '" + AllLists.tItemCollect_MenuData[index].a_need4_type.ToString() + "',a_need4_index = '" + AllLists.tItemCollect_MenuData[index].a_need4_index.ToString() + "',a_need4_num = '" + AllLists.tItemCollect_MenuData[index].a_need4_num.ToString() + "',a_need5_type = '" + AllLists.tItemCollect_MenuData[index].a_need5_type.ToString() + "',a_need5_index = '" + AllLists.tItemCollect_MenuData[index].a_need5_index.ToString() + "',a_need5_num = '" + AllLists.tItemCollect_MenuData[index].a_need5_num.ToString() + "',a_need6_type = '" + AllLists.tItemCollect_MenuData[index].a_need6_type.ToString() + "',a_need6_index = '" + AllLists.tItemCollect_MenuData[index].a_need6_index.ToString() + "',a_need6_num = '" + AllLists.tItemCollect_MenuData[index].a_need6_num.ToString() + "',a_result_type = '" + AllLists.tItemCollect_MenuData[index].a_result_type.ToString() + "',a_result_index = '" + AllLists.tItemCollect_MenuData[index].a_result_index.ToString() + "',a_result_num = '" + AllLists.tItemCollect_MenuData[index].a_result_num.ToString() + "'WHERE a_theme ='" + AllLists.tItemCollect_MenuData[index].a_theme.ToString() + "';");
        this.lblStatus.Text = "Saved Pet : " + AllLists.tItemCollect_MenuData[index].Menu;
        int num2 = (int) new CustomMessage("Updated Pet").ShowDialog();
      }
      else if (!this.doesCollectionExist)
      {
        mySQL.UpdateQuery(string.Format("INSERT INTO t_item_collection (a_theme, a_category, a_theme_string,\r\n                            a_desc_string, a_enable, a_id, a_row, a_col, a_need1_type, a_need1_index, \r\n                            a_need1_num, a_need2_type, a_need2_index, a_need2_num, a_need3_type, \r\n                            a_need3_index, a_need3_num, a_need4_type, a_need4_index, a_need4_num, a_need5_type,\r\n                            a_need5_index, a_need5_num, a_need6_type, a_need6_index,\r\n                            a_need6_num, a_result_type, a_result_index, a_result_num)\r\n                            VALUES ({0}, {1}, '{2}','{3}',{4},{5},{6},{7},{8},{9},{10},{11},{12},{13},{14},{15},{16},{17},{18},{19},{20},{21},{22},{23},{24},{25},{26},{27},{28} )", (object) AllLists.tItemCollect_MenuData[index].a_theme, (object) AllLists.tItemCollect_MenuData[index].a_category, (object) AllLists.tItemCollect_MenuData[index].a_theme_string, (object) AllLists.tItemCollect_MenuData[index].a_descr_string, (object) AllLists.tItemCollect_MenuData[index].a_enable, (object) AllLists.tItemCollect_MenuData[index].a_id, (object) AllLists.tItemCollect_MenuData[index].a_row, (object) AllLists.tItemCollect_MenuData[index].a_col, (object) AllLists.tItemCollect_MenuData[index].a_need1_type, (object) AllLists.tItemCollect_MenuData[index].a_need1_index, (object) AllLists.tItemCollect_MenuData[index].a_need1_num, (object) AllLists.tItemCollect_MenuData[index].a_need2_type, (object) AllLists.tItemCollect_MenuData[index].a_need2_index, (object) AllLists.tItemCollect_MenuData[index].a_need2_num, (object) AllLists.tItemCollect_MenuData[index].a_need3_type, (object) AllLists.tItemCollect_MenuData[index].a_need3_index, (object) AllLists.tItemCollect_MenuData[index].a_need3_num, (object) AllLists.tItemCollect_MenuData[index].a_need4_type, (object) AllLists.tItemCollect_MenuData[index].a_need4_index, (object) AllLists.tItemCollect_MenuData[index].a_need4_num, (object) AllLists.tItemCollect_MenuData[index].a_need5_type, (object) AllLists.tItemCollect_MenuData[index].a_need5_index, (object) AllLists.tItemCollect_MenuData[index].a_need5_num, (object) AllLists.tItemCollect_MenuData[index].a_need6_type, (object) AllLists.tItemCollect_MenuData[index].a_need6_index, (object) AllLists.tItemCollect_MenuData[index].a_need6_num, (object) AllLists.tItemCollect_MenuData[index].a_result_type, (object) AllLists.tItemCollect_MenuData[index].a_result_index, (object) AllLists.tItemCollect_MenuData[index].a_result_num));
        this.lblStatus.Text = "Inserted Collection : " + AllLists.tItemCollect_MenuData[index].Menu;
        int num3 = (int) new CustomMessage("Inserted Collection").ShowDialog();
      }
    }

    private void btnAdd_Click(object sender, EventArgs e)
    {
      int num = AllLists.tItemCollect_MenuData.Max<tItemCollection>((System.Func<tItemCollection, int>) (p => p.a_theme)) + 1;
      tItemCollection tItemCollection = new tItemCollection()
      {
        a_theme = num,
        a_theme_string = "New Collection",
        a_descr_string = "",
        a_category = 1,
        a_enable = true,
        a_id = 1,
        a_row = 0,
        a_col = 1
      };
      tItemCollection.a_id = 1;
      tItemCollection.a_need1_type = 0;
      tItemCollection.a_need1_index = 0;
      tItemCollection.a_need1_num = 0;
      tItemCollection.a_need2_type = 0;
      tItemCollection.a_need2_index = 0;
      tItemCollection.a_need2_num = 0;
      tItemCollection.a_need3_type = 0;
      tItemCollection.a_need3_index = 0;
      tItemCollection.a_need3_num = 0;
      tItemCollection.a_need4_type = 0;
      tItemCollection.a_need4_index = 0;
      tItemCollection.a_need4_num = 0;
      tItemCollection.a_need5_type = 0;
      tItemCollection.a_need5_index = 0;
      tItemCollection.a_need5_num = 0;
      tItemCollection.a_need6_type = 0;
      tItemCollection.a_need6_index = 0;
      tItemCollection.a_need6_num = 0;
      tItemCollection.a_result_type = 1;
      tItemCollection.a_result_index = 19;
      tItemCollection.a_result_num = 1;
      this.SetPublicValues();
      AllLists.tItemCollect_MenuData.Add(tItemCollection);
      AllLists.tItemCollect_Menu.Add(tItemCollection.a_theme.ToString() + " - " + tItemCollection.a_theme_string);
      this.lblCount.Text = "Collection Count: " + AllLists.tItemCollect_MenuData.Count<tItemCollection>().ToString();
      this.RefreshAll();
      this.listBox1.SelectedIndex = this.listBox1.Items.Count - 1;
    }

    private void btnCopy_Click(object sender, EventArgs e)
    {
      int CollectionID = this.GetID();
      int num = AllLists.tItemCollect_MenuData.Max<tItemCollection>((System.Func<tItemCollection, int>) (p => p.a_theme)) + 1;
      tItemCollection tItemCollection = AllLists.tItemCollect_MenuData.Find((Predicate<tItemCollection>) (p => p.a_theme.Equals(CollectionID))).Clone();
      tItemCollection.a_theme = num;
      tItemCollection.a_theme_string += " (copy)";
      tItemCollection.Menu = tItemCollection.a_theme.ToString() + " - " + tItemCollection.a_theme_string;
      this.TbCollectionExist.Text = "";
      AllLists.tItemCollect_MenuData.Add(tItemCollection);
      this.lblCount.Text = "Collection Count: " + AllLists.tItemCollect_MenuData.Count<tItemCollection>().ToString();
      this.RefreshAll();
      this.listBox1.SelectedIndex = this.listBox1.Items.Count - 1;
    }

    private void btnDelete_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Are u sure u want to delete this entire collection?\r\nThe action cannot be undone", "Delete Collection", MessageBoxButtons.YesNo) != DialogResult.Yes)
        return;
      int CollectionID = this.GetID();
      int selectedIndex = this.listBox1.SelectedIndex;
      AllLists.tItemCollect_MenuData.RemoveAll((Predicate<tItemCollection>) (p => p.a_theme.Equals(CollectionID)));
      mySQL.UpdateQuery("DELETE FROM t_item_collection WHERE a_theme ='" + CollectionID.ToString() + "';");
      int num = (int) new CustomMessage("Deleted :o").ShowDialog();
      this.RefreshAll();
      this.lblCount.Text = "Collection Count: " + AllLists.tItemCollect_MenuData.Count<tItemCollection>().ToString();
      this.listBox1.SelectedIndex = selectedIndex - 1;
    }

    private void TextBox6_TextChanged(object sender, EventArgs e)
    {
      if (this.TbNeedIndex1.Text != "" && this.tbNeed1.Text == "1")
        this.pbNeed1.Image = (Image) this.databaseHandle.IconFast(Convert.ToInt32(this.TbNeedIndex1.Text));
      if (!(this.tbNeed1.Text != "1"))
        return;
      this.pbNeed1.Image = (Image) null;
    }

    private void TextBox12_TextChanged(object sender, EventArgs e)
    {
      if (this.TbNeedIndex2.Text != "" && this.tbNeed2.Text == "1")
        this.pbNeed2.Image = (Image) this.databaseHandle.IconFast(Convert.ToInt32(this.TbNeedIndex2.Text));
      if (!(this.tbNeed2.Text != "1"))
        return;
      this.pbNeed2.Image = (Image) null;
    }

    private void TextBox14_TextChanged(object sender, EventArgs e)
    {
      if (this.TbNeedIndex3.Text != "" && this.tbNeed3.Text == "1")
        this.pbNeed3.Image = (Image) this.databaseHandle.IconFast(Convert.ToInt32(this.TbNeedIndex3.Text));
      if (!(this.tbNeed3.Text != "1"))
        return;
      this.pbNeed3.Image = (Image) null;
    }

    private void TextBox16_TextChanged(object sender, EventArgs e)
    {
      if (this.TbNeedIndex4.Text != "" && this.tbNeed4.Text == "1")
        this.pbNeed4.Image = (Image) this.databaseHandle.IconFast(Convert.ToInt32(this.TbNeedIndex4.Text));
      if (!(this.tbNeed4.Text != "1"))
        return;
      this.pbNeed4.Image = (Image) null;
    }

    private void TextBox18_TextChanged(object sender, EventArgs e)
    {
      if (this.tbResultType.Text == "1")
        this.pbResult.Image = (Image) this.databaseHandle.IconFast(Convert.ToInt32(this.TbResultIndex.Text));
      else
        this.pbResult.Image = (Image) null;
    }

    private void PbResultItemIdx_Click(object sender, EventArgs e)
    {
      if (int.Parse(this.tbResultType.Text) == 1)
      {
        ItemPicker itemPicker = new ItemPicker();
        if (itemPicker.ShowDialog() != DialogResult.OK)
          return;
        this.TbResultIndex.Text = Convert.ToString(itemPicker.ItemIndex);
        this.TbResultCount.Text = Convert.ToString(itemPicker.ItemAmount);
      }
      else if (int.Parse(this.tbResultType.Text) == 1)
        ;
    }

    private void PbSelectID1_Click(object sender, EventArgs e)
    {
      if (int.Parse(this.tbNeed1.Text) == 1)
      {
        ItemPicker itemPicker = new ItemPicker();
        if (itemPicker.ShowDialog() != DialogResult.OK)
          return;
        this.TbNeedIndex1.Text = Convert.ToString(itemPicker.ItemIndex);
        this.TbNeedCount1.Text = Convert.ToString(itemPicker.ItemAmount);
      }
      else if (int.Parse(this.tbNeed1.Text) == 1)
        ;
    }

    private void PbSelectID2_Click(object sender, EventArgs e)
    {
      if (int.Parse(this.tbNeed2.Text) == 1)
      {
        ItemPicker itemPicker = new ItemPicker();
        if (itemPicker.ShowDialog() != DialogResult.OK)
          return;
        this.TbNeedIndex2.Text = Convert.ToString(itemPicker.ItemIndex);
        this.TbNeedCount2.Text = Convert.ToString(itemPicker.ItemAmount);
      }
      else if (int.Parse(this.tbNeed2.Text) == 1)
        ;
    }

    private void PbSelectID3_Click(object sender, EventArgs e)
    {
      if (int.Parse(this.tbNeed3.Text) == 1)
      {
        ItemPicker itemPicker = new ItemPicker();
        if (itemPicker.ShowDialog() != DialogResult.OK)
          return;
        this.TbNeedIndex3.Text = Convert.ToString(itemPicker.ItemIndex);
        this.TbNeedCount3.Text = Convert.ToString(itemPicker.ItemAmount);
      }
      else if (int.Parse(this.tbNeed3.Text) == 1)
        ;
    }

    private void PbSelectID4_Click(object sender, EventArgs e)
    {
      if (int.Parse(this.tbNeed4.Text) == 1)
      {
        ItemPicker itemPicker = new ItemPicker();
        if (itemPicker.ShowDialog() != DialogResult.OK)
          return;
        this.TbNeedIndex4.Text = Convert.ToString(itemPicker.ItemIndex);
        this.TbNeedCount4.Text = Convert.ToString(itemPicker.ItemAmount);
      }
      else if (int.Parse(this.tbNeed4.Text) == 1)
        ;
    }

    private void PbSelectID5_Click(object sender, EventArgs e)
    {
      if (int.Parse(this.tbNeed5.Text) == 1)
      {
        ItemPicker itemPicker = new ItemPicker();
        if (itemPicker.ShowDialog() != DialogResult.OK)
          return;
        this.TbNeedIndex5.Text = Convert.ToString(itemPicker.ItemIndex);
        this.TbNeedCount5.Text = Convert.ToString(itemPicker.ItemAmount);
      }
      else if (int.Parse(this.tbNeed5.Text) == 1)
        ;
    }

    private void PbSelectID6_Click(object sender, EventArgs e)
    {
      if (int.Parse(this.tbNeed6.Text) == 1)
      {
        ItemPicker itemPicker = new ItemPicker();
        if (itemPicker.ShowDialog() != DialogResult.OK)
          return;
        this.TbNeedIndex6.Text = Convert.ToString(itemPicker.ItemIndex);
        this.TbNeedCount6.Text = Convert.ToString(itemPicker.ItemAmount);
      }
      else if (int.Parse(this.tbNeed6.Text) == 1)
        ;
    }

    private void TbNeedIndex5_TextChanged(object sender, EventArgs e)
    {
      if (this.TbNeedIndex5.Text != "" && this.tbNeed5.Text == "1")
        this.pbNeed5.Image = (Image) this.databaseHandle.IconFast(Convert.ToInt32(this.TbNeedIndex5.Text));
      if (!(this.tbNeed5.Text != "1"))
        return;
      this.pbNeed5.Image = (Image) null;
    }

    private void TbNeedIndex6_TextChanged(object sender, EventArgs e)
    {
      if (this.TbNeedIndex6.Text != "" && this.tbNeed6.Text == "1")
        this.pbNeed6.Image = (Image) this.databaseHandle.IconFast(Convert.ToInt32(this.TbNeedIndex6.Text));
      if (!(this.tbNeed6.Text != "1"))
        return;
      this.pbNeed6.Image = (Image) null;
    }

    private void pbNeed1_MouseHover(object sender, EventArgs e)
    {
      if (!(this.tbNeed1.Text == "1"))
        return;
      this.toolTip1.SetToolTip((Control) this.pbNeed1, this.databaseHandle.ItemNameFast(int.Parse(this.TbNeedIndex1.Text)));
    }

    private void pbNeed2_MouseHover(object sender, EventArgs e)
    {
      if (!(this.tbNeed2.Text == "1"))
        return;
      this.toolTip1.SetToolTip((Control) this.pbNeed2, this.databaseHandle.ItemNameFast(int.Parse(this.TbNeedIndex2.Text)));
    }

    private void pbNeed3_MouseHover(object sender, EventArgs e)
    {
      if (!(this.tbNeed3.Text == "1"))
        return;
      this.toolTip1.SetToolTip((Control) this.pbNeed3, this.databaseHandle.ItemNameFast(int.Parse(this.TbNeedIndex3.Text)));
    }

    private void pbNeed4_MouseHover(object sender, EventArgs e)
    {
      if (!(this.tbNeed4.Text == "1"))
        return;
      this.toolTip1.SetToolTip((Control) this.pbNeed4, this.databaseHandle.ItemNameFast(int.Parse(this.TbNeedIndex4.Text)));
    }

    private void pbNeed5_MouseHover(object sender, EventArgs e)
    {
      if (!(this.tbNeed5.Text == "1"))
        return;
      this.toolTip1.SetToolTip((Control) this.pbNeed5, this.databaseHandle.ItemNameFast(int.Parse(this.TbNeedIndex5.Text)));
    }

    private void pbNeed6_MouseHover(object sender, EventArgs e)
    {
      if (!(this.tbNeed6.Text == "1"))
        return;
      this.toolTip1.SetToolTip((Control) this.pbNeed6, this.databaseHandle.ItemNameFast(int.Parse(this.TbNeedIndex6.Text)));
    }

    private void pbResult_MouseHover(object sender, EventArgs e)
    {
      if (!(this.tbResultType.Text == "1"))
        return;
      this.toolTip1.SetToolTip((Control) this.pbResult, this.databaseHandle.ItemNameFast(int.Parse(this.TbResultIndex.Text)));
    }
  }
}
