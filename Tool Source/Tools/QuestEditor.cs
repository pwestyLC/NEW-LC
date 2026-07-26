// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.QuestEditor
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using LcDevPack_TeamDamonA.Properties;
using StringExporter;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools
{
  public class QuestEditor : Form
  {
    public static Connection connection = new Connection();
    private string Host = QuestEditor.connection.Settings.SqlHost;
    private string User = QuestEditor.connection.Settings.SqlUser;
    private string Password = QuestEditor.connection.Settings.SqlPassword;
    private string Database = QuestEditor.connection.Settings.SqlDatabase;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    private ExportLodHandle exportLodHandle = new ExportLodHandle();
    public string rowName = "a_index";
    public string[] menuArray = new string[2]
    {
      "a_index",
      "a_name"
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
    public string adesc = "";
    public string aname = "";
    public string desc;
    public string adesc2 = "";
    public string adesc3 = "";
    public string desc2;
    private Label label112;
    private Label label111;
    private Label label110;
    private Label label113;
    private Label lblLang;
    private ComboBox CbRvRGrade;
    private ComboBox CbRvrType;
    private ComboBox CbRvRGrade1;
    private Button BtnCopy;
    private PictureBox PbPItem5;
    private PictureBox PbPItem4;
    private PictureBox PbPItem3;
    private PictureBox PbPItem2;
    private PictureBox PbPItem1;
    private PictureBox PbItem7;
    private PictureBox PbItem6;
    private PictureBox PbItem5;
    private PictureBox PbItem4;
    private PictureBox PbItem3;
    private PictureBox PbItem2;
    private PictureBox PbItem1;
    private PictureBox PbCond1;
    private PictureBox PbCond2;
    private PictureBox PbCond3;
    private TextBox tbItemDesc5;
    private TextBox tbItemDesc4;
    private TextBox tbItemDesc3;
    private TextBox tbItemDesc2;
    private TextBox tbItemDesc1;
    private TextBox TbPrize2ItemDesc1;
    private TextBox TbPrize2ItemDesc2;
    private TextBox TbPrize2ItemDesc3;
    private TextBox TbPrize2ItemDesc4;
    private TextBox TbPrize2ItemDesc5;
    private TextBox TbPrize2ItemDesc6;
    private TextBox TbPrize2ItemDesc7;
    public string desc3;
    private TextBox TbObj1;
    private TextBox TbObj2;
    private TextBox TbObj3;
    private TextBox TbObjNpc3;
    private PictureBox PbNpcID3;
    private TextBox TbObjNpc2;
    private PictureBox PbNpcID2;
    private TextBox TbObjNpc1;
    private PictureBox PbNpcID1;
    private TextBox TbObj1Npc3;
    private PictureBox PbObj1NpcID3;
    private TextBox TbObj1Npc2;
    private PictureBox PbObj1NpcID2;
    private TextBox TbObj1Npc1;
    private PictureBox PbObj1NpcID1;
    private Label label116;
    private TextBox TbObj2Npc3;
    private PictureBox PbObj2NpcID3;
    private TextBox TbObj2Npc2;
    private PictureBox PbObj2NpcID2;
    private TextBox TbObj2Npc1;
    private PictureBox PbObj2NpcID1;
    private Label label115;
    private Label label114;
    private Label label118;
    private Label label117;
    private TextBox TbEndNpcName;
    private TextBox TbStartNpcName;
    private PictureBox PbItemNeed5;
    private PictureBox PbItemNeed4;
    private PictureBox PbItemNeed3;
    private PictureBox PbItemNeed2;
    private PictureBox PbItemNeed1;
    private TextBox TbNeedName5;
    private TextBox TbNeedName4;
    private TextBox TbNeedName3;
    private TextBox TbNeedName2;
    private TextBox TbNeedName1;
    private PictureBox PbEndNPCItem;
    private PictureBox PbStartItemNPC;
    private Label label119;
    private PictureBox pictureBox1;
    private Label label120;
    private Label label121;
    private PictureBox pictureBox2;
    private Label label122;
    private PictureBox pictureBox3;
    private CheckBox cbEnabled;
    private Button btnSaveAndNext;
    private PictureBox pictureBox10;
    private PictureBox pictureBox9;
    private PictureBox pictureBox8;
    private PictureBox pictureBox7;
    private PictureBox pictureBox6;
    private PictureBox pictureBox5;
    private PictureBox pictureBox4;
    private TextBox TbFileCol;
    private TextBox tbFileRow;
    private TextBox tbFileID;
    private PictureBox pictureBox15;
    private PictureBox pictureBox14;
    private PictureBox pictureBox13;
    private PictureBox pictureBox12;
    private PictureBox pictureBox11;
    public string nameholder1;
    private ExportLodHandle exportLodhandle = new ExportLodHandle();
    private IContainer components = (IContainer) null;
    public string name;
    public int index;
    public string test2;
    private MenuStrip menuStrip1;
    private ToolStripMenuItem fileExportToolStripMenuItem;
    private GroupBox groupBox3;
    private Button button3;
    private Button button1;
    private ListBox listBox1;
    private GroupBox groupBox5;
    private Label label7;
    private TextBox textBox12;
    private TabControl tabControl1;
    private TabPage tabPage1;
    private TextBox textBox2;
    private Label label3;
    private Label label2;
    private Label label6;
    private TextBox textBox1;
    private Label label5;
    private Label label1;
    private TextBox textBox6;
    private TextBox textBox10;
    private Label label11;
    private Label label12;
    private Label label13;
    private TextBox textBox13;
    private Label label10;
    private Label label46;
    private Label label47;
    private Label label54;
    private Label label52;
    private Label label59;
    private TabPage Page2;
    private TextBox textBox5;
    private GroupBox groupBox1;
    private TextBox textBox21;
    private Label label85;
    private Label label93;
    private TextBox textBox20;
    private TextBox textBox23;
    private Label label22;
    private TextBox textBox22;
    private Label label23;
    private GroupBox groupBox4;
    private TextBox textBox19;
    private TextBox textBox17;
    private Label label14;
    private Label label92;
    private TextBox textBox16;
    private Label label91;
    private Label label18;
    private TextBox textBox18;
    private TextBox textBox14;
    private Label label15;
    private Label label16;
    private Label label4;
    private TextBox textBox24;
    private TextBox textBox25;
    private Label label37;
    private TextBox textBox44;
    private Label label38;
    private Label label39;
    private Label label40;
    private TextBox textBox45;
    private TextBox textBox46;
    private TextBox textBox47;
    private Label label32;
    private TextBox textBox39;
    private Label label33;
    private Label label35;
    private Label label36;
    private TextBox textBox40;
    private TextBox textBox42;
    private TextBox textBox43;
    private Label label34;
    private TextBox textBox41;
    private GroupBox groupBox6;
    private Label label17;
    private Label label19;
    private Label label20;
    private Label label26;
    private TextBox textBox32;
    private Label label27;
    private TextBox textBox31;
    private Label label28;
    private Label label25;
    private TextBox textBox33;
    private Label label24;
    private TextBox textBox34;
    private Label label21;
    private TextBox textBox35;
    private Label label29;
    private Label label30;
    private Label label31;
    private TextBox textBox36;
    private TextBox textBox37;
    private TextBox textBox38;
    private TextBox textBox48;
    private TextBox textBox54;
    private TextBox textBox55;
    private TextBox textBox56;
    private TextBox textBox57;
    private TextBox textBox58;
    private Label label48;
    private Label label49;
    private Label label50;
    private Label label51;
    private Label label53;
    private Label label45;
    private Label label44;
    private Label label43;
    private Label label42;
    private Label label41;
    private TextBox textBox59;
    private TextBox textBox60;
    private TextBox textBox61;
    private TextBox textBox62;
    private TextBox textBox63;
    private Label label60;
    private Label label58;
    private Label label57;
    private Label label56;
    private Label label55;
    private Label label96;
    private Label label95;
    private Label label104;
    private TextBox textBox104;
    private ComboBox comboBox2;
    private ComboBox comboBox1;
    private GroupBox groupBox9;
    private ComboBox comboBox3;
    private GroupBox groupBox10;
    private ComboBox comboBox4;
    private Label label98;
    private GroupBox groupBox11;
    private ComboBox comboBox5;
    private Button button6;
    private Button button5;
    private TabControl tabControl2;
    private TabPage tabPage2;
    private TabPage tabPage4;
    private TabPage tabPage3;
    private TabPage tabPage5;
    private ComboBox comboBox6;
    private GroupBox groupBox2;
    private ComboBox comboBox7;
    private GroupBox groupBox12;
    private ComboBox comboBox8;
    private TabControl tabControl3;
    private TabPage tabPage8;
    private TabPage tabPage9;
    private ComboBox comboBox13;
    private ComboBox comboBox12;
    private ComboBox comboBox11;
    private ComboBox comboBox10;
    private ComboBox comboBox9;
    private TextBox textBox86;
    private TextBox textBox87;
    private TextBox textBox92;
    private Label label83;
    private Label label90;
    private Label label84;
    private Label label89;
    private TextBox textBox88;
    private Label label88;
    private TextBox textBox89;
    private Label label87;
    private TextBox textBox90;
    private Label label86;
    private TextBox textBox91;
    private TextBox textBox72;
    private TextBox textBox73;
    private Label label69;
    private Label label70;
    private TextBox textBox74;
    private TextBox textBox75;
    private TextBox textBox76;
    private TextBox textBox77;
    private TextBox textBox78;
    private Label label71;
    private Label label72;
    private Label label73;
    private Label label74;
    private Label label75;
    private TextBox textBox79;
    private TextBox textBox80;
    private Label label76;
    private Label label77;
    private TextBox textBox81;
    private TextBox textBox82;
    private TextBox textBox83;
    private TextBox textBox84;
    private TextBox textBox85;
    private Label label78;
    private Label label79;
    private Label label80;
    private Label label81;
    private Label label82;
    private ComboBox comboBox20;
    private ComboBox comboBox19;
    private ComboBox comboBox18;
    private ComboBox comboBox17;
    private ComboBox comboBox16;
    private ComboBox comboBox15;
    private ComboBox comboBox14;
    private Label label67;
    private Label label68;
    private Label label66;
    private Label label65;
    private Label label64;
    private Label label63;
    private Label label62;
    private ComboBox comboBox22;
    private ComboBox comboBox21;
    private TextBox textBox4;
    private TextBox textBox3;
    private TextBox textBox7;
    private TextBox textBox11;
    private TextBox textBox9;
    private TextBox textBox98;
    private Label label106;
    private Label label105;
    private Label label107;
    private Label label108;
    private Label label109;
    private TextBox textBox15;
    private TextBox textBox28;
    private TextBox textBox29;
    private TextBox textBox30;
    private TextBox textBox53;
    private TextBox textBox52;
    private TextBox textBox51;
    private TextBox textBox50;
    private TextBox textBox49;
    private TextBox textBox65;
    private TextBox textBox66;
    private TextBox textBox67;
    private TextBox textBox71;
    private TextBox textBox68;
    private TextBox textBox70;
    private TextBox textBox69;
    private TextBox textBox93;
    private Label label94;
    private TextBox textBox64;
    private Label label61;
    private Button button7;
    private RichTextBox richTextBox1;
    private RichTextBox richTextBox3;
    private RichTextBox richTextBox2;
    public TextBox textBox8;
    private TabPage tabPage7;
    private GroupBox groupBox7;
    private TextBox textBox103;
    private Label label103;
    private TextBox textBox102;
    private Label label102;
    private Label label99;
    private TextBox textBox100;
    private TextBox textBox97;
    private Label label97;
    private TextBox textBox101;
    private Label label101;
    private TextBox textBox99;
    private Label label100;
    private GroupBox groupBox8;
    private Label label8;
    private Label label9;
    private TextBox textBox26;
    private TextBox textBox27;
    private ToolStripMenuItem exportToolStripMenuItem;
    private ToolStripMenuItem exportStrQuestToolStripMenuItem;

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
      {
        this.namee = "a_name";
        return this.namee;
      }
      this.namee = "a_name_usa";
      return this.namee;
    }

    public string DescrFromLanguage()
    {
      if (this.language == "GER")
      {
        this.desc = "a_desc_ger";
        return this.desc;
      }
      if (this.language == "POL")
      {
        this.desc = "a_desc_pld";
        return this.desc;
      }
      if (this.language == "BRA")
      {
        this.desc = "a_desc_brz";
        return this.desc;
      }
      if (this.language == "RUS")
      {
        this.desc = "a_desc_rus";
        return this.desc;
      }
      if (this.language == "FRA")
      {
        this.desc = "a_desc_frc";
        return this.desc;
      }
      if (this.language == "ESP")
      {
        this.desc = "a_desc_spn";
        return this.desc;
      }
      if (this.language == "MEX")
      {
        this.desc = "a_desc_mex";
        return this.desc;
      }
      if (this.language == "THA")
      {
        this.desc = "a_desc_thai";
        return this.desc;
      }
      if (this.language == "ITA")
      {
        this.desc = "a_desc_ita";
        return this.desc;
      }
      if (!(this.language == "USA"))
      {
        this.desc = "a_desc";
        return this.desc;
      }
      this.desc = "a_desc_usa";
      return this.desc;
    }

    public string Descr2FromLanguage()
    {
      if (this.language == "GER")
      {
        this.desc2 = "a_desc2_ger";
        return this.desc2;
      }
      if (this.language == "POL")
      {
        this.desc2 = "a_desc2_pld";
        return this.desc2;
      }
      if (this.language == "BRA")
      {
        this.desc2 = "a_desc2_brz";
        return this.desc2;
      }
      if (this.language == "RUS")
      {
        this.desc2 = "a_desc2_rus";
        return this.desc2;
      }
      if (this.language == "FRA")
      {
        this.desc2 = "a_desc2_frc";
        return this.desc2;
      }
      if (this.language == "ESP")
      {
        this.desc2 = "a_desc2_spn";
        return this.desc2;
      }
      if (this.language == "MEX")
      {
        this.desc2 = "a_desc2_mex";
        return this.desc2;
      }
      if (this.language == "THA")
      {
        this.desc2 = "a_desc2_thai";
        return this.desc2;
      }
      if (this.language == "ITA")
      {
        this.desc2 = "a_desc2_ita";
        return this.desc2;
      }
      if (!(this.language == "USA"))
      {
        this.desc2 = "a_desc2";
        return this.desc2;
      }
      this.desc2 = "a_desc2_usa";
      return this.desc2;
    }

    public string Descr3FromLanguage()
    {
      if (this.language == "GER")
      {
        this.desc3 = "a_desc3_ger";
        return this.desc3;
      }
      if (this.language == "POL")
      {
        this.desc3 = "a_desc3_pld";
        return this.desc3;
      }
      if (this.language == "BRA")
      {
        this.desc3 = "a_desc3_brz";
        return this.desc3;
      }
      if (this.language == "RUS")
      {
        this.desc3 = "a_desc3_rus";
        return this.desc3;
      }
      if (this.language == "FRA")
      {
        this.desc3 = "a_desc3_frc";
        return this.desc3;
      }
      if (this.language == "ESP")
      {
        this.desc3 = "a_desc3_spn";
        return this.desc3;
      }
      if (this.language == "MEX")
      {
        this.desc3 = "a_desc3_mex";
        return this.desc3;
      }
      if (this.language == "THA")
      {
        this.desc3 = "a_desc3_thai";
        return this.desc3;
      }
      if (this.language == "ITA")
      {
        this.desc3 = "a_desc3_ita";
        return this.desc3;
      }
      if (!(this.language == "USA"))
      {
        this.desc3 = "a_desc3";
        return this.desc3;
      }
      this.desc3 = "a_desc3_usa";
      return this.desc3;
    }

    public QuestEditor() => this.InitializeComponent();

    private void LoadListBox()
    {
      if (this.language == "GER")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayGER, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_ger from t_quest ORDER BY a_index;");
      else if (this.language == "POL")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayPOL, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_pld from t_quest ORDER BY a_index;");
      else if (this.language == "BRA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayBRA, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_brz from t_quest ORDER BY a_index;");
      else if (this.language == "RUS")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayRUS, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_rus from t_quest ORDER BY a_index;");
      else if (this.language == "FRA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayFRA, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_frc from t_quest ORDER BY a_index;");
      else if (this.language == "ESP")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayESP, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_spn from t_quest ORDER BY a_index;");
      else if (this.language == "MEX")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayMEX, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_mex from t_quest ORDER BY a_index;");
      else if (this.language == "THA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayTHA, this.Host, this.User, this.Password, this.Database, "select a_index, CONVERT(a_name_thai USING tis620) as a_name_thai from t_quest ORDER BY a_index;");
      else if (this.language == "ITA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayITA, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_ita from t_quest ORDER BY a_index;");
      else if (this.language == "USA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayUSA, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_usa from t_quest ORDER BY a_index;");
      else
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, "select a_index, a_name from t_quest ORDER BY a_index;");
    }

    public void SearchList(string searchString)
    {
      searchString = searchString.Replace("\\", "\\\\").Replace("'", "\\'");
      string lower = searchString.ToLower();
      string upper = searchString.ToUpper();
      string str = "";
      if (searchString.Length > 1)
        str = char.ToUpper(searchString[0]).ToString() + searchString.Substring(1);
      if (this.language == "GER")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayGER, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_ger from t_quest WHERE a_name_ger LIKE '%" + searchString + "%' OR a_index LIKE '%" + searchString + "%' OR a_name_ger LIKE '%" + lower + "%' OR a_index  LIKE '%" + lower + "%' OR a_name_ger LIKE '%" + upper + "%' OR a_index LIKE '%" + upper + "%' OR a_name_ger LIKE '%" + str + "%' OR a_index LIKE '%" + str + "%' ORDER BY a_index;");
      else if (this.language == "POL")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayPOL, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_pld from t_quest WHERE a_name_pld LIKE '%" + searchString + "%' OR a_index LIKE '%" + searchString + "%' OR a_name_pld LIKE '%" + lower + "%' OR a_index  LIKE '%" + lower + "%' OR a_name_pld LIKE '%" + upper + "%' OR a_index LIKE '%" + upper + "%' OR a_name_pld LIKE '%" + str + "%' OR a_index LIKE '%" + str + "%' ORDER BY a_index;");
      else if (this.language == "BRA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayBRA, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_brz from t_quest WHERE a_name_brz LIKE '%" + searchString + "%' OR a_index LIKE '%" + searchString + "%' OR a_name_brz LIKE '%" + lower + "%' OR a_index  LIKE '%" + lower + "%' OR a_name_brz LIKE '%" + upper + "%' OR a_index LIKE '%" + upper + "%' OR a_name_brz LIKE '%" + str + "%' OR a_index LIKE '%" + str + "%' ORDER BY a_index;");
      else if (this.language == "RUS")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayRUS, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_rus from t_quest WHERE a_name_rus LIKE '%" + searchString + "%' OR a_index LIKE '%" + searchString + "%' OR a_name_rus LIKE '%" + lower + "%' OR a_index  LIKE '%" + lower + "%' OR a_name_rus LIKE '%" + upper + "%' OR a_index LIKE '%" + upper + "%' OR a_name_rus LIKE '%" + str + "%' OR a_index LIKE '%" + str + "%' ORDER BY a_index;");
      else if (this.language == "FRA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayFRA, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_frc from t_quest WHERE a_name_frc LIKE '%" + searchString + "%' OR a_index LIKE '%" + searchString + "%' OR a_name_frc LIKE '%" + lower + "%' OR a_index  LIKE '%" + lower + "%' OR a_name_frc LIKE '%" + upper + "%' OR a_index LIKE '%" + upper + "%' OR a_name_frc LIKE '%" + str + "%' OR a_index LIKE '%" + str + "%' ORDER BY a_index;");
      else if (this.language == "ESP")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayESP, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_spn from t_quest WHERE a_name_spn LIKE '%" + searchString + "%' OR a_index LIKE '%" + searchString + "%' OR a_name_spn LIKE '%" + lower + "%' OR a_index  LIKE '%" + lower + "%' OR a_name_spn LIKE '%" + upper + "%' OR a_index LIKE '%" + upper + "%' OR a_name_spn LIKE '%" + str + "%' OR a_index LIKE '%" + str + "%' ORDER BY a_index;");
      else if (this.language == "MEX")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayMEX, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_mex from t_quest WHERE a_name_mex LIKE '%" + searchString + "%' OR a_index LIKE '%" + searchString + "%' OR a_name_mex LIKE '%" + lower + "%' OR a_index  LIKE '%" + lower + "%' OR a_name_mex LIKE '%" + upper + "%' OR a_index LIKE '%" + upper + "%' OR a_name_mex LIKE '%" + str + "%' OR a_index LIKE '%" + str + "%' ORDER BY a_index;");
      else if (this.language == "THA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayTHA, this.Host, this.User, this.Password, this.Database, "select a_index, CONVERT(a_name_thai USING utf8) as a_name_thai from t_quest WHERE a_name_thai LIKE '%" + searchString + "%' OR a_index LIKE '%" + searchString + "%' OR a_name_thai LIKE '%" + lower + "%' OR a_index  LIKE '%" + lower + "%' OR a_name_thai LIKE '%" + upper + "%' OR a_index LIKE '%" + upper + "%' OR a_name_thai LIKE '%" + str + "%' OR a_index LIKE '%" + str + "%' ORDER BY a_index;");
      else if (this.language == "ITA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayITA, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_ita from t_quest WHERE a_name_ita LIKE '%" + searchString + "%' OR a_index LIKE '%" + searchString + "%' OR a_name_ita LIKE '%" + lower + "%' OR a_index  LIKE '%" + lower + "%' OR a_name_ita LIKE '%" + upper + "%' OR a_index LIKE '%" + upper + "%' OR a_name_ita LIKE '%" + str + "%' OR a_index LIKE '%" + str + "%' ORDER BY a_index;");
      else if (this.language == "USA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayUSA, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_usa from t_quest WHERE a_name_usa LIKE '%" + searchString + "%' OR a_index LIKE '%" + searchString + "%' OR a_name_usa LIKE '%" + lower + "%' OR a_index  LIKE '%" + lower + "%' OR a_name_usa LIKE '%" + upper + "%' OR a_index LIKE '%" + upper + "%' OR a_name_usa LIKE '%" + str + "%' OR a_index LIKE '%" + str + "%' ORDER BY a_index;");
      else
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, "select a_index, a_name from t_quest WHERE a_name LIKE '%" + searchString + "%' OR a_index LIKE '%" + searchString + "%' OR a_name LIKE '%" + lower + "%' OR a_index  LIKE '%" + lower + "%' OR a_name LIKE '%" + upper + "%' OR a_index LIKE '%" + upper + "%' OR a_name LIKE '%" + str + "%' OR a_index LIKE '%" + str + "%' ORDER BY a_index;");
    }

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

    private void Form3_Load(object sender, EventArgs e)
    {
      this.LoadListBox();
      this.LoadStartUp();
      this.SelectBoxes();
      this.LoadLangAtStartup();
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

    private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (this.listBox1.SelectedIndex != -1)
        this.tbItemDesc1.Text = "";
      this.tbItemDesc2.Text = "";
      this.tbItemDesc3.Text = "";
      this.tbItemDesc4.Text = "";
      this.tbItemDesc5.Text = "";
      this.TbPrize2ItemDesc1.Text = "";
      this.TbPrize2ItemDesc2.Text = "";
      this.TbPrize2ItemDesc3.Text = "";
      this.TbPrize2ItemDesc4.Text = "";
      this.TbPrize2ItemDesc5.Text = "";
      this.TbPrize2ItemDesc6.Text = "";
      this.TbPrize2ItemDesc7.Text = "";
      this.TbObj1.Text = "";
      this.TbObj2.Text = "";
      this.TbObj3.Text = "";
      this.TbObjNpc1.Text = "";
      this.TbObjNpc2.Text = "";
      this.TbObjNpc3.Text = "";
      this.TbObj1Npc1.Text = "";
      this.TbObj1Npc2.Text = "";
      this.TbObj1Npc3.Text = "";
      this.TbObj2Npc1.Text = "";
      this.TbObj2Npc2.Text = "";
      this.TbObj2Npc3.Text = "";
      this.TbStartNpcName.Text = "";
      this.TbEndNpcName.Text = "";
      this.TbNeedName1.Text = "";
      this.TbNeedName2.Text = "";
      this.TbNeedName3.Text = "";
      this.TbNeedName4.Text = "";
      this.TbNeedName5.Text = "";
      this.textBox2.BackColor = Color.White;
      this.textBox2.BackColor = Color.White;
      this.textBox5.BackColor = Color.White;
      this.textBox6.BackColor = Color.White;
      this.textBox8.BackColor = Color.White;
      this.textBox10.BackColor = Color.White;
      this.textBox12.BackColor = Color.White;
      this.textBox13.BackColor = Color.White;
      this.textBox14.BackColor = Color.White;
      this.textBox16.BackColor = Color.White;
      this.textBox17.BackColor = Color.White;
      this.textBox18.BackColor = Color.White;
      this.textBox19.BackColor = Color.White;
      this.textBox20.BackColor = Color.White;
      this.textBox21.BackColor = Color.White;
      this.textBox22.BackColor = Color.White;
      this.textBox23.BackColor = Color.White;
      this.textBox24.BackColor = Color.White;
      this.textBox25.BackColor = Color.White;
      this.textBox26.BackColor = Color.White;
      this.textBox27.BackColor = Color.White;
      this.textBox31.BackColor = Color.White;
      this.textBox32.BackColor = Color.White;
      this.textBox33.BackColor = Color.White;
      this.textBox34.BackColor = Color.White;
      this.textBox35.BackColor = Color.White;
      this.textBox36.BackColor = Color.White;
      this.textBox37.BackColor = Color.White;
      this.textBox38.BackColor = Color.White;
      this.textBox39.BackColor = Color.White;
      this.textBox40.BackColor = Color.White;
      this.textBox41.BackColor = Color.White;
      this.textBox42.BackColor = Color.White;
      this.textBox43.BackColor = Color.White;
      this.textBox44.BackColor = Color.White;
      this.textBox45.BackColor = Color.White;
      this.textBox46.BackColor = Color.White;
      this.textBox47.BackColor = Color.White;
      this.textBox48.BackColor = Color.White;
      this.textBox54.BackColor = Color.White;
      this.textBox55.BackColor = Color.White;
      this.textBox56.BackColor = Color.White;
      this.textBox57.BackColor = Color.White;
      this.textBox58.BackColor = Color.White;
      this.textBox59.BackColor = Color.White;
      this.textBox60.BackColor = Color.White;
      this.textBox61.BackColor = Color.White;
      this.textBox62.BackColor = Color.White;
      this.textBox63.BackColor = Color.White;
      this.textBox64.BackColor = Color.White;
      this.textBox72.BackColor = Color.White;
      this.textBox73.BackColor = Color.White;
      this.textBox74.BackColor = Color.White;
      this.textBox75.BackColor = Color.White;
      this.textBox76.BackColor = Color.White;
      this.textBox77.BackColor = Color.White;
      this.textBox78.BackColor = Color.White;
      this.textBox79.BackColor = Color.White;
      this.textBox80.BackColor = Color.White;
      this.textBox81.BackColor = Color.White;
      this.textBox82.BackColor = Color.White;
      this.textBox83.BackColor = Color.White;
      this.textBox84.BackColor = Color.White;
      this.textBox85.BackColor = Color.White;
      this.textBox86.BackColor = Color.White;
      this.textBox87.BackColor = Color.White;
      this.textBox88.BackColor = Color.White;
      this.textBox89.BackColor = Color.White;
      this.textBox90.BackColor = Color.White;
      this.textBox91.BackColor = Color.White;
      this.textBox92.BackColor = Color.White;
      this.textBox93.BackColor = Color.White;
      this.richTextBox1.BackColor = Color.White;
      this.richTextBox2.BackColor = Color.White;
      this.richTextBox3.BackColor = Color.White;
      this.textBox97.BackColor = Color.White;
      this.textBox99.BackColor = Color.White;
      this.textBox100.BackColor = Color.White;
      this.textBox101.BackColor = Color.White;
      this.textBox102.BackColor = Color.White;
      this.textBox103.BackColor = Color.White;
      this.textBox104.BackColor = Color.White;
      this.comboBox1.BackColor = Color.White;
      this.comboBox2.BackColor = Color.White;
      this.comboBox3.BackColor = Color.White;
      this.comboBox4.BackColor = Color.White;
      this.comboBox5.BackColor = Color.White;
      this.comboBox6.BackColor = Color.White;
      this.comboBox7.BackColor = Color.White;
      this.comboBox8.BackColor = Color.White;
      this.comboBox9.BackColor = Color.White;
      this.comboBox10.BackColor = Color.White;
      this.comboBox11.BackColor = Color.White;
      this.comboBox12.BackColor = Color.White;
      this.comboBox13.BackColor = Color.White;
      this.comboBox14.BackColor = Color.White;
      this.comboBox15.BackColor = Color.White;
      this.comboBox16.BackColor = Color.White;
      this.comboBox17.BackColor = Color.White;
      this.comboBox18.BackColor = Color.White;
      this.comboBox19.BackColor = Color.White;
      this.comboBox20.BackColor = Color.White;
      this.comboBox21.BackColor = Color.White;
      this.comboBox22.BackColor = Color.White;
      this.textBox1.Text = this.GetIndex().ToString();
      string Query = " select a_index , a_name , a_type1 , a_type2 , a_enable , a_prequest_num , a_start_type , a_start_data , a_start_npc_zone_num , a_prize_npc , a_prize_npc_zone_num , a_need_exp , a_need_min_level , a_need_max_level , a_need_job , a_need_item0 , a_need_item1 , a_need_item2 , a_need_item3 , a_need_item4 , a_need_item_count0 , a_need_item_count1 , a_need_item_count2 , a_need_item_count3 , a_need_item_count4 , a_need_rvr_type , a_need_rvr_grade , a_condition0_type , a_condition1_type , a_condition2_type , a_condition0_index , a_condition1_index , a_condition2_index , a_condition0_num , a_condition1_num , a_condition2_num , a_condition0_data0 , a_condition0_data1 , a_condition0_data2 , a_condition0_data3 , a_condition1_data0 , a_condition1_data1 , a_condition1_data2 , a_condition1_data3 , a_condition2_data0 , a_condition2_data1 , a_condition2_data2 , a_condition2_data3 , a_prize_type0 , a_prize_type1 , a_prize_type2 , a_prize_type3 , a_prize_type4 , a_prize_index0 , a_prize_index1 , a_prize_index2 , a_prize_index3 , a_prize_index4 , a_prize_data0 , a_prize_data1 , a_prize_data2 , a_prize_data3 , a_prize_data4 , a_option_prize , a_opt_prize_type0 , a_opt_prize_type1 , a_opt_prize_type2 , a_opt_prize_type3 , a_opt_prize_type4 , a_opt_prize_type5 , a_opt_prize_type6 , a_opt_prize_index0 , a_opt_prize_index1 , a_opt_prize_index2 , a_opt_prize_index3 , a_opt_prize_index4 , a_opt_prize_index5 , a_opt_prize_index6 , a_opt_prize_data0 , a_opt_prize_data1 , a_opt_prize_data2 , a_opt_prize_data3 , a_opt_prize_data4 , a_opt_prize_data5 , a_opt_prize_data6 , a_opt_prize_plus0 , a_opt_prize_plus1 , a_opt_prize_plus2 , a_opt_prize_plus3 , a_opt_prize_plus4 , a_opt_prize_plus5 , a_opt_prize_plus6 , a_only_opt_prize , a_desc_usa , a_desc2_usa , a_desc3_usa , a_failvalue , a_partyscale , a_start_give_item , a_start_give_kindcount , a_start_give_numcount , a_start_trigger_id , a_quest_flag, a_name_ger, a_desc_ger, a_desc2_ger, a_desc3_ger, a_name_rus, a_desc_rus, a_desc2_rus, a_desc3_rus, a_name_thai, a_desc_thai, a_desc2_thai, a_desc3_thai, a_name_frc, a_desc_frc, a_desc2_frc, a_desc3_frc, a_name_mex, a_desc_mex, a_desc2_mex, a_desc3_mex, a_name_brz, a_desc_brz, a_desc2_brz, a_desc3_brz, a_name_spn, a_desc_spn, a_desc2_spn, a_desc3_spn, a_name_ita, a_desc_ita, a_desc2_ita, a_desc3_ita, a_name_pld, a_desc_pld, a_desc2_pld, a_desc3_pld, a_name_usa from t_quest WHERE a_index ='" + this.textBox1.Text + "';";
      string[] rows = new string[140]
      {
        "a_index",
        "a_name",
        "a_type1",
        "a_type2",
        "a_enable",
        "a_prequest_num",
        "a_start_type",
        "a_start_data",
        "a_start_npc_zone_num",
        "a_prize_npc",
        "a_prize_npc_zone_num",
        "a_need_exp",
        "a_need_min_level",
        "a_need_max_level",
        "a_need_job",
        "a_need_item0",
        "a_need_item1",
        "a_need_item2",
        "a_need_item3",
        "a_need_item4",
        "a_need_item_count0",
        "a_need_item_count1",
        "a_need_item_count2",
        "a_need_item_count3",
        "a_need_item_count4",
        "a_need_rvr_type",
        "a_need_rvr_grade",
        "a_condition0_type",
        "a_condition1_type",
        "a_condition2_type",
        "a_condition0_index",
        "a_condition1_index",
        "a_condition2_index",
        "a_condition0_num",
        "a_condition1_num",
        "a_condition2_num",
        "a_condition0_data0",
        "a_condition0_data1",
        "a_condition0_data2",
        "a_condition0_data3",
        "a_condition1_data0",
        "a_condition1_data1",
        "a_condition1_data2",
        "a_condition1_data3",
        "a_condition2_data0",
        "a_condition2_data1",
        "a_condition2_data2",
        "a_condition2_data3",
        "a_prize_type0",
        "a_prize_type1",
        "a_prize_type2",
        "a_prize_type3",
        "a_prize_type4",
        "a_prize_index0",
        "a_prize_index1",
        "a_prize_index2",
        "a_prize_index3",
        "a_prize_index4",
        "a_prize_data0",
        "a_prize_data1",
        "a_prize_data2",
        "a_prize_data3",
        "a_prize_data4",
        "a_option_prize",
        "a_opt_prize_type0",
        "a_opt_prize_type1",
        "a_opt_prize_type2",
        "a_opt_prize_type3",
        "a_opt_prize_type4",
        "a_opt_prize_type5",
        "a_opt_prize_type6",
        "a_opt_prize_index0",
        "a_opt_prize_index1",
        "a_opt_prize_index2",
        "a_opt_prize_index3",
        "a_opt_prize_index4",
        "a_opt_prize_index5",
        "a_opt_prize_index6",
        "a_opt_prize_data0",
        "a_opt_prize_data1",
        "a_opt_prize_data2",
        "a_opt_prize_data3",
        "a_opt_prize_data4",
        "a_opt_prize_data5",
        "a_opt_prize_data6",
        "a_opt_prize_plus0",
        "a_opt_prize_plus1",
        "a_opt_prize_plus2",
        "a_opt_prize_plus3",
        "a_opt_prize_plus4",
        "a_opt_prize_plus5",
        "a_opt_prize_plus6",
        "a_only_opt_prize",
        "a_desc_usa",
        "a_desc2_usa",
        "a_desc3_usa",
        "a_failvalue",
        "a_partyscale",
        "a_start_give_item",
        "a_start_give_kindcount",
        "a_start_give_numcount",
        "a_start_trigger_id",
        "a_quest_flag",
        "a_name_ger",
        "a_desc_ger",
        "a_desc2_ger",
        "a_desc3_ger",
        "a_name_rus",
        "a_desc_rus",
        "a_desc2_rus",
        "a_desc3_rus",
        "a_name_thai",
        "a_desc_thai",
        "a_desc2_thai",
        "a_desc3_thai",
        "a_name_frc",
        "a_desc_frc",
        "a_desc2_frc",
        "a_desc3_frc",
        "a_name_mex",
        "a_desc_mex",
        "a_desc2_mex",
        "a_desc3_mex",
        "a_name_brz",
        "a_desc_brz",
        "a_desc2_brz",
        "a_desc3_brz",
        "a_name_spn",
        "a_desc_spn",
        "a_desc2_spn",
        "a_desc3_spn",
        "a_name_ita",
        "a_desc_ita",
        "a_desc2_ita",
        "a_desc3_ita",
        "a_name_pld",
        "a_desc_pld",
        "a_desc2_pld",
        "a_desc3_pld",
        "a_name_usa"
      };
      Query.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'");
      string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query, rows);
      this.textBox1.Text = strArray[0];
      this.textBox3.Text = strArray[2];
      this.textBox4.Text = strArray[3];
      this.textBox5.Text = strArray[4];
      if (this.textBox5.Text == "1")
      {
        this.cbEnabled.BackColor = Color.Chartreuse;
        this.cbEnabled.Checked = true;
      }
      else if (this.textBox5.Text == "0")
      {
        this.cbEnabled.BackColor = Color.Red;
        this.cbEnabled.Checked = false;
      }
      this.textBox6.Text = strArray[5];
      this.textBox7.Text = strArray[6];
      this.textBox8.Text = strArray[7];
      this.textBox9.Text = strArray[8];
      this.textBox10.Text = strArray[9];
      this.textBox11.Text = strArray[10];
      this.textBox12.Text = strArray[11];
      this.textBox13.Text = strArray[12];
      this.textBox14.Text = strArray[13];
      this.textBox15.Text = strArray[14];
      this.textBox16.Text = strArray[15];
      this.textBox17.Text = strArray[16];
      this.textBox18.Text = strArray[17];
      this.textBox19.Text = strArray[18];
      this.textBox20.Text = strArray[19];
      this.textBox21.Text = strArray[20];
      this.textBox22.Text = strArray[21];
      this.textBox23.Text = strArray[22];
      this.textBox24.Text = strArray[23];
      this.textBox25.Text = strArray[24];
      this.textBox26.Text = strArray[25];
      this.textBox27.Text = strArray[26];
      this.textBox28.Text = strArray[27];
      this.textBox29.Text = strArray[28];
      this.textBox30.Text = strArray[29];
      this.textBox31.Text = strArray[30];
      this.textBox32.Text = strArray[31];
      this.textBox33.Text = strArray[32];
      this.textBox34.Text = strArray[33];
      this.textBox35.Text = strArray[34];
      this.textBox36.Text = strArray[35];
      this.textBox37.Text = strArray[36];
      this.textBox38.Text = strArray[37];
      this.textBox39.Text = strArray[38];
      this.textBox40.Text = strArray[39];
      this.textBox41.Text = strArray[40];
      this.textBox42.Text = strArray[41];
      this.textBox43.Text = strArray[42];
      this.textBox44.Text = strArray[43];
      this.textBox45.Text = strArray[44];
      this.textBox46.Text = strArray[45];
      this.textBox47.Text = strArray[46];
      this.textBox48.Text = strArray[47];
      this.textBox49.Text = strArray[48];
      this.textBox50.Text = strArray[49];
      this.textBox51.Text = strArray[50];
      this.textBox52.Text = strArray[51];
      this.textBox53.Text = strArray[52];
      this.textBox54.Text = strArray[53];
      this.textBox55.Text = strArray[54];
      this.textBox56.Text = strArray[55];
      this.textBox57.Text = strArray[56];
      this.textBox58.Text = strArray[57];
      this.textBox59.Text = strArray[58];
      this.textBox60.Text = strArray[59];
      this.textBox61.Text = strArray[60];
      this.textBox62.Text = strArray[61];
      this.textBox63.Text = strArray[62];
      this.textBox64.Text = strArray[63];
      this.textBox65.Text = strArray[64];
      this.textBox66.Text = strArray[65];
      this.textBox67.Text = strArray[66];
      this.textBox68.Text = strArray[67];
      this.textBox69.Text = strArray[68];
      this.textBox70.Text = strArray[69];
      this.textBox71.Text = strArray[70];
      this.textBox72.Text = strArray[71];
      this.textBox73.Text = strArray[72];
      this.textBox74.Text = strArray[73];
      this.textBox75.Text = strArray[74];
      this.textBox76.Text = strArray[75];
      this.textBox77.Text = strArray[76];
      this.textBox78.Text = strArray[77];
      this.textBox79.Text = strArray[78];
      this.textBox80.Text = strArray[79];
      this.textBox81.Text = strArray[80];
      this.textBox82.Text = strArray[81];
      this.textBox83.Text = strArray[82];
      this.textBox84.Text = strArray[83];
      this.textBox85.Text = strArray[84];
      this.textBox86.Text = strArray[85];
      this.textBox87.Text = strArray[86];
      this.textBox88.Text = strArray[87];
      this.textBox89.Text = strArray[88];
      this.textBox90.Text = strArray[89];
      this.textBox91.Text = strArray[90];
      this.textBox92.Text = strArray[91];
      this.textBox93.Text = strArray[92];
      if (this.language == "FRA")
      {
        this.textBox2.Text = strArray[115];
        this.richTextBox1.Text = strArray[116];
        this.richTextBox2.Text = strArray[117];
        this.richTextBox3.Text = strArray[118];
      }
      else if (this.language == "USA")
      {
        this.textBox2.Text = strArray[139];
        this.richTextBox1.Text = strArray[93];
        this.richTextBox2.Text = strArray[94];
        this.richTextBox3.Text = strArray[95];
      }
      else if (this.language == "ITA")
      {
        this.textBox2.Text = strArray[131];
        this.richTextBox1.Text = strArray[132];
        this.richTextBox2.Text = strArray[133];
        this.richTextBox3.Text = strArray[134];
      }
      else if (this.language == "RUS")
      {
        this.textBox2.Text = strArray[107];
        this.richTextBox1.Text = strArray[108];
        this.richTextBox2.Text = strArray[109];
        this.richTextBox3.Text = strArray[110];
      }
      else if (this.language == "THA")
      {
        this.textBox2.Text = strArray[111];
        this.richTextBox1.Text = strArray[112];
        this.richTextBox2.Text = strArray[113];
        this.richTextBox3.Text = strArray[114];
      }
      else if (this.language == "POL")
      {
        this.textBox2.Text = strArray[135];
        this.richTextBox1.Text = strArray[136];
        this.richTextBox2.Text = strArray[137];
        this.richTextBox3.Text = strArray[138];
      }
      else if (this.language == "ESP")
      {
        this.textBox2.Text = strArray[(int) sbyte.MaxValue];
        this.richTextBox1.Text = strArray[128];
        this.richTextBox2.Text = strArray[129];
        this.richTextBox3.Text = strArray[130];
      }
      else if (this.language == "BRA")
      {
        this.textBox2.Text = strArray[123];
        this.richTextBox1.Text = strArray[124];
        this.richTextBox2.Text = strArray[125];
        this.richTextBox3.Text = strArray[126];
      }
      else if (this.language == "GER")
      {
        this.textBox2.Text = strArray[103];
        this.richTextBox1.Text = strArray[104];
        this.richTextBox2.Text = strArray[105];
        this.richTextBox3.Text = strArray[106];
      }
      else if (this.language == "MEX")
      {
        this.textBox2.Text = strArray[119];
        this.richTextBox1.Text = strArray[120];
        this.richTextBox2.Text = strArray[121];
        this.richTextBox3.Text = strArray[122];
      }
      else if (this.language != "GER" && this.language != "POL" && this.language != "BRA" && this.language != "RUS" && this.language != "FRA" && this.language != "ESP" && this.language != "MEX" && this.language != "THA" && this.language != "ITA" && this.language != "USA")
      {
        this.textBox2.Text = strArray[1];
        this.richTextBox1.Text = strArray[93];
        this.richTextBox2.Text = strArray[94];
        this.richTextBox3.Text = strArray[95];
      }
      this.textBox97.Text = strArray[96];
      this.textBox98.Text = strArray[97];
      this.textBox99.Text = strArray[98];
      this.textBox100.Text = strArray[99];
      this.textBox101.Text = strArray[100];
      this.textBox102.Text = strArray[101];
      this.textBox103.Text = strArray[102];
      this.SelectMobItemNames();
      this.SelectBoxes();
    }

    private void Iconsource_ITEMS()
    {
      string Query = "select a_index, a_texture_id, a_texture_row, a_texture_col FROM t_item WHERE a_index ='" + this.tbFileID.Text + "';";
      string str1 = "select a_index, a_texture_id, a_texture_row, a_texture_col FROM t_item WHERE a_index ='" + this.tbFileID.Text + "';";
      string str2 = "select a_index, a_texture_id, a_texture_row, a_texture_col FROM t_item WHERE a_index ='" + this.tbFileID.Text + "';";
      string str3 = "select a_index, a_texture_id, a_texture_row, a_texture_col FROM t_item WHERE a_index ='" + this.tbFileID.Text + "';";
      string str4 = "select a_index, a_texture_id, a_texture_row, a_texture_col FROM t_item WHERE a_index ='" + this.tbFileID.Text + "';";
      string str5 = "select a_index, a_texture_id, a_texture_row, a_texture_col FROM t_item WHERE a_index ='" + this.tbFileID.Text + "';";
      string str6 = "select a_index, a_texture_id, a_texture_row, a_texture_col FROM t_item WHERE a_index ='" + this.tbFileID.Text + "';";
      string str7 = "select a_index, a_texture_id, a_texture_row, a_texture_col FROM t_item WHERE a_index ='" + this.tbFileID.Text + "';";
      string str8 = "select a_index, a_texture_id, a_texture_row, a_texture_col FROM t_item WHERE a_index ='" + this.tbFileID.Text + "';";
      string str9 = "select a_index, a_texture_id, a_texture_row, a_texture_col FROM t_item WHERE a_index ='" + this.tbFileID.Text + "';";
      string str10 = "select a_index, a_texture_id, a_texture_row, a_texture_col FROM t_item WHERE a_index ='" + this.tbFileID.Text + "';";
      string str11 = "select a_index, a_texture_id, a_texture_row, a_texture_col FROM t_item WHERE a_index ='" + this.tbFileID.Text + "';";
      string[] rows = new string[4]
      {
        "a_index",
        "a_texture_id",
        "a_texture_row",
        "a_texture_col"
      };
      Query.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'");
      string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query, rows);
      this.tbFileID.Text = strArray[1];
      this.tbFileRow.Text = strArray[2];
      this.TbFileCol.Text = strArray[3];
    }

    private void SelectMobItemNames()
    {
      if (this.textBox72.Text != "0")
        this.TbPrize2ItemDesc1.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox72.Text));
      if (this.textBox73.Text != "0")
        this.TbPrize2ItemDesc2.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox73.Text));
      if (this.textBox74.Text != "0")
        this.TbPrize2ItemDesc3.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox74.Text));
      if (this.textBox75.Text != "0")
        this.TbPrize2ItemDesc4.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox75.Text));
      if (this.textBox76.Text != "0")
        this.TbPrize2ItemDesc5.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox76.Text));
      if (this.textBox77.Text != "0")
        this.TbPrize2ItemDesc6.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox77.Text));
      if (this.textBox78.Text != "0")
        this.TbPrize2ItemDesc7.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox78.Text));
      if (this.textBox54.Text != "0")
        this.tbItemDesc1.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox54.Text));
      if (this.textBox55.Text != "0")
        this.tbItemDesc2.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox55.Text));
      if (this.textBox56.Text != "0")
        this.tbItemDesc3.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox56.Text));
      if (this.textBox57.Text != "0")
        this.tbItemDesc4.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox57.Text));
      if (this.textBox58.Text != "0")
        this.tbItemDesc5.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox58.Text));
      if (this.textBox31.Text != "0" && this.textBox28.Text != "0" && this.textBox28.Text != "3" && this.textBox28.Text != "4" && this.textBox28.Text != "6" && this.textBox28.Text != "7" && this.textBox28.Text != "8" || this.textBox28.Text == "1" || this.textBox28.Text == "2" || this.textBox28.Text == "5")
      {
        this.TbObj1.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox31.Text));
        this.TbObj1.ForeColor = Color.RoyalBlue;
      }
      if (this.textBox32.Text != "0" && this.textBox29.Text != "0" && this.textBox29.Text != "3" && this.textBox29.Text != "4" && this.textBox29.Text != "6" && this.textBox29.Text != "7" && this.textBox29.Text != "8" || this.textBox29.Text == "1" || this.textBox29.Text == "2" || this.textBox29.Text == "5")
      {
        this.TbObj2.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox32.Text));
        this.TbObj2.ForeColor = Color.RoyalBlue;
      }
      if (this.textBox33.Text != "0" && this.textBox30.Text != "0" && this.textBox30.Text != "3" && this.textBox30.Text != "4" && this.textBox30.Text != "6" && this.textBox30.Text != "7" && this.textBox30.Text != "8" || this.textBox30.Text == "1" || this.textBox30.Text == "2" || this.textBox30.Text == "5")
      {
        this.TbObj3.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox33.Text));
        this.TbObj3.ForeColor = Color.RoyalBlue;
      }
      if (this.textBox31.Text != "0" && this.textBox28.Text == "0")
      {
        this.TbObj1.Text = this.databaseHandle.MobNameFast(Convert.ToInt32(this.textBox31.Text));
        this.TbObj1.ForeColor = Color.Red;
      }
      if (this.textBox32.Text != "0" && this.textBox29.Text == "0")
      {
        this.TbObj2.Text = this.databaseHandle.MobNameFast(Convert.ToInt32(this.textBox32.Text));
        this.TbObj2.ForeColor = Color.Red;
      }
      if (this.textBox33.Text != "0" && this.textBox30.Text == "0")
      {
        this.TbObj3.Text = this.databaseHandle.MobNameFast(Convert.ToInt32(this.textBox33.Text));
        this.TbObj3.ForeColor = Color.Red;
      }
      if (this.textBox45.Text != "0")
        this.TbObjNpc1.Text = this.databaseHandle.MobNameFast(Convert.ToInt32(this.textBox45.Text));
      if (this.textBox46.Text != "0")
        this.TbObjNpc2.Text = this.databaseHandle.MobNameFast(Convert.ToInt32(this.textBox46.Text));
      if (this.textBox47.Text != "0")
        this.TbObjNpc3.Text = this.databaseHandle.MobNameFast(Convert.ToInt32(this.textBox47.Text));
      if (this.textBox37.Text != "0")
        this.TbObj1Npc1.Text = this.databaseHandle.MobNameFast(Convert.ToInt32(this.textBox37.Text));
      if (this.textBox38.Text != "0")
        this.TbObj1Npc2.Text = this.databaseHandle.MobNameFast(Convert.ToInt32(this.textBox38.Text));
      if (this.textBox39.Text != "0")
        this.TbObj1Npc3.Text = this.databaseHandle.MobNameFast(Convert.ToInt32(this.textBox39.Text));
      if (this.textBox41.Text != "0")
        this.TbObj2Npc1.Text = this.databaseHandle.MobNameFast(Convert.ToInt32(this.textBox41.Text));
      if (this.textBox42.Text != "0")
        this.TbObj2Npc2.Text = this.databaseHandle.MobNameFast(Convert.ToInt32(this.textBox42.Text));
      if (this.textBox43.Text != "0")
        this.TbObj2Npc3.Text = this.databaseHandle.MobNameFast(Convert.ToInt32(this.textBox43.Text));
      if (this.textBox7.Text == "0" && this.textBox8.Text != "0" && this.textBox8.Text != "-1")
      {
        this.TbStartNpcName.Text = this.databaseHandle.MobNameFast(Convert.ToInt32(this.textBox8.Text));
        this.TbStartNpcName.ForeColor = Color.LimeGreen;
      }
      if (this.textBox10.Text != "0" && this.textBox10.Text != "-1")
        this.TbEndNpcName.Text = this.databaseHandle.MobNameFast(Convert.ToInt32(this.textBox10.Text));
      if (this.textBox7.Text == "1")
      {
        this.TbStartNpcName.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox8.Text));
        this.TbStartNpcName.ForeColor = Color.RoyalBlue;
      }
      if (this.textBox16.Text != "-1")
        this.TbNeedName1.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox16.Text));
      if (this.textBox17.Text != "-1")
        this.TbNeedName2.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox17.Text));
      if (this.textBox18.Text != "-1")
        this.TbNeedName3.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox18.Text));
      if (this.textBox19.Text != "-1")
        this.TbNeedName4.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox19.Text));
      if (!(this.textBox20.Text != "-1"))
        return;
      this.TbNeedName5.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox20.Text));
    }

    private void SelectBoxes()
    {
      int num1 = this.comboBox1.FindString(this.textBox3.Text);
      int num2 = this.comboBox2.FindString(this.textBox4.Text);
      int num3 = this.comboBox5.FindString(this.textBox7.Text);
      int num4 = this.comboBox21.FindString(this.textBox9.Text);
      int num5 = this.comboBox22.FindString(this.textBox11.Text);
      int num6 = this.comboBox4.FindString(this.textBox98.Text);
      int num7 = this.comboBox3.FindString(this.textBox15.Text);
      int num8 = this.comboBox6.FindString(this.textBox28.Text);
      int num9 = this.comboBox7.FindString(this.textBox29.Text);
      int num10 = this.comboBox8.FindString(this.textBox30.Text);
      int num11 = this.comboBox9.FindString(this.textBox49.Text);
      int num12 = this.comboBox10.FindString(this.textBox50.Text);
      int num13 = this.comboBox11.FindString(this.textBox51.Text);
      int num14 = this.comboBox12.FindString(this.textBox52.Text);
      int num15 = this.comboBox13.FindString(this.textBox53.Text);
      int num16 = this.comboBox14.FindString(this.textBox65.Text);
      int num17 = this.comboBox15.FindString(this.textBox66.Text);
      int num18 = this.comboBox16.FindString(this.textBox67.Text);
      int num19 = this.comboBox17.FindString(this.textBox68.Text);
      int num20 = this.comboBox18.FindString(this.textBox69.Text);
      int num21 = this.comboBox19.FindString(this.textBox70.Text);
      int num22 = this.comboBox20.FindString(this.textBox71.Text);
      int num23 = this.CbRvrType.FindString(this.textBox26.Text);
      int num24 = this.CbRvRGrade.FindString(this.textBox27.Text);
      int num25 = this.CbRvRGrade1.FindString(this.textBox27.Text);
      this.comboBox1.SelectedIndex = num1;
      this.comboBox2.SelectedIndex = num2;
      this.comboBox5.SelectedIndex = num3;
      this.comboBox21.SelectedIndex = num4;
      this.comboBox22.SelectedIndex = num5;
      this.comboBox4.SelectedIndex = num6;
      this.comboBox3.SelectedIndex = num7;
      this.comboBox6.SelectedIndex = num8;
      this.comboBox7.SelectedIndex = num9;
      this.comboBox8.SelectedIndex = num10;
      this.comboBox9.SelectedIndex = num11;
      this.comboBox10.SelectedIndex = num12;
      this.comboBox11.SelectedIndex = num13;
      this.comboBox12.SelectedIndex = num14;
      this.comboBox13.SelectedIndex = num15;
      this.comboBox14.SelectedIndex = num16;
      this.comboBox15.SelectedIndex = num17;
      this.comboBox16.SelectedIndex = num18;
      this.comboBox17.SelectedIndex = num19;
      this.comboBox18.SelectedIndex = num20;
      this.comboBox19.SelectedIndex = num21;
      this.comboBox20.SelectedIndex = num22;
      this.CbRvrType.SelectedIndex = num23;
      this.CbRvRGrade.SelectedIndex = num24;
      this.CbRvRGrade1.SelectedIndex = num25;
    }

    private void button2_Click(object sender, EventArgs e)
    {
      string str1 = "UPDATE t_quest SET a_index = '" + this.textBox1.Text + "', ";
      string str2 = this.textBox2.Text.Replace("'", "\\'").Replace("\"", "\\\"");
      string str3 = str1 + "a_name = '" + str2 + "', a_name_usa = '" + str2 + "', a_type1 = '" + this.textBox3.Text + "', a_type2 = '" + this.textBox4.Text + "', a_enable = '" + this.textBox5.Text + "', a_prequest_num = '" + this.textBox6.Text + "', a_start_type = '" + this.textBox7.Text + "', a_start_data = '" + this.textBox8.Text + "', a_start_npc_zone_num = '" + this.textBox9.Text + "', a_prize_npc = '" + this.textBox10.Text + "', a_prize_npc_zone_num = '" + this.textBox11.Text + "', a_need_exp = '" + this.textBox12.Text + "', a_need_min_level = '" + this.textBox13.Text + "', a_need_max_level = '" + this.textBox14.Text + "', a_need_job = '" + this.textBox15.Text + "', a_need_item0 = '" + this.textBox16.Text + "', a_need_item1 = '" + this.textBox17.Text + "', a_need_item2 = '" + this.textBox18.Text + "', a_need_item3 = '" + this.textBox19.Text + "', a_need_item4 = '" + this.textBox20.Text + "', a_need_item_count0 = '" + this.textBox21.Text + "', a_need_item_count1 = '" + this.textBox22.Text + "', a_need_item_count2 = '" + this.textBox23.Text + "', a_need_item_count3 = '" + this.textBox24.Text + "', a_need_item_count4 = '" + this.textBox25.Text + "', a_need_rvr_type = '" + this.textBox26.Text + "', a_need_rvr_grade = '" + this.textBox27.Text + "', a_condition0_type = '" + this.textBox28.Text + "', a_condition1_type = '" + this.textBox29.Text + "', a_condition2_type = '" + this.textBox30.Text + "', a_condition0_index = '" + this.textBox31.Text + "', a_condition1_index = '" + this.textBox32.Text + "', a_condition2_index = '" + this.textBox33.Text + "', a_condition0_num = '" + this.textBox34.Text + "', a_condition1_num = '" + this.textBox35.Text + "', a_condition2_num = '" + this.textBox36.Text + "', a_condition0_data0 = '" + this.textBox37.Text + "', a_condition0_data1 = '" + this.textBox38.Text + "', a_condition0_data2 = '" + this.textBox39.Text + "', a_condition0_data3 = '" + this.textBox40.Text + "', a_condition1_data0 = '" + this.textBox41.Text + "', a_condition1_data1 = '" + this.textBox42.Text + "', a_condition1_data2 = '" + this.textBox43.Text + "', a_condition1_data3 = '" + this.textBox44.Text + "', a_condition2_data0 = '" + this.textBox45.Text + "', a_condition2_data1 = '" + this.textBox46.Text + "', a_condition2_data2 = '" + this.textBox47.Text + "', a_condition2_data3 = '" + this.textBox48.Text + "', a_prize_type0 = '" + this.textBox49.Text + "', a_prize_type1 = '" + this.textBox50.Text + "', a_prize_type2 = '" + this.textBox51.Text + "', a_prize_type3 = '" + this.textBox52.Text + "', a_prize_type4 = '" + this.textBox53.Text + "', a_prize_index0 = '" + this.textBox54.Text + "', a_prize_index1 = '" + this.textBox55.Text + "', a_prize_index2 = '" + this.textBox56.Text + "', a_prize_index3 = '" + this.textBox57.Text + "', a_prize_index4 = '" + this.textBox58.Text + "', a_prize_data0 = '" + this.textBox59.Text + "', a_prize_data1 = '" + this.textBox60.Text + "', a_prize_data2 = '" + this.textBox61.Text + "', a_prize_data3 = '" + this.textBox62.Text + "', a_prize_data4 = '" + this.textBox63.Text + "', a_option_prize = '" + this.textBox64.Text + "', a_opt_prize_type0 = '" + this.textBox65.Text + "', a_opt_prize_type1 = '" + this.textBox66.Text + "', a_opt_prize_type2 = '" + this.textBox67.Text + "', a_opt_prize_type3 = '" + this.textBox68.Text + "', a_opt_prize_type4 = '" + this.textBox69.Text + "', a_opt_prize_type5 = '" + this.textBox70.Text + "', a_opt_prize_type6 = '" + this.textBox71.Text + "', a_opt_prize_index0 = '" + this.textBox72.Text + "', a_opt_prize_index1 = '" + this.textBox73.Text + "', a_opt_prize_index2 = '" + this.textBox74.Text + "', a_opt_prize_index3 = '" + this.textBox75.Text + "', a_opt_prize_index4 = '" + this.textBox76.Text + "', a_opt_prize_index5 = '" + this.textBox77.Text + "', a_opt_prize_index6 = '" + this.textBox78.Text + "', a_opt_prize_data0 = '" + this.textBox79.Text + "', a_opt_prize_data1 = '" + this.textBox80.Text + "', a_opt_prize_data2 = '" + this.textBox81.Text + "', a_opt_prize_data3 = '" + this.textBox82.Text + "', a_opt_prize_data4 = '" + this.textBox83.Text + "', a_opt_prize_data5 = '" + this.textBox84.Text + "', a_opt_prize_data6 = '" + this.textBox85.Text + "', a_opt_prize_plus0 = '" + this.textBox86.Text + "', a_opt_prize_plus1 = '" + this.textBox87.Text + "', a_opt_prize_plus2 = '" + this.textBox88.Text + "', a_opt_prize_plus3 = '" + this.textBox89.Text + "', a_opt_prize_plus4 = '" + this.textBox90.Text + "', a_opt_prize_plus5 = '" + this.textBox91.Text + "', a_opt_prize_plus6 = '" + this.textBox92.Text + "', a_only_opt_prize = '" + this.textBox93.Text + "', ";
      string str4 = this.richTextBox1.Text.Replace("'", "\\'").Replace("\"", "\\\"");
      string str5 = this.richTextBox2.Text.Replace("'", "\\'").Replace("\"", "\\\"");
      string str6 = this.richTextBox3.Text.Replace("'", "\\'").Replace("\"", "\\\"");
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, str3 + "a_desc_usa = '" + str4 + "', a_desc2_usa = '" + str5 + "', a_desc3_usa = '" + str6 + "', a_failvalue = '" + this.textBox97.Text + "', a_partyscale = '" + this.textBox98.Text + "', a_start_give_item = '" + this.textBox99.Text + "', a_start_give_kindcount = '" + this.textBox100.Text + "', a_start_give_numcount = '" + this.textBox101.Text + "', a_start_trigger_id = '" + this.textBox102.Text + "', a_quest_flag = '" + this.textBox103.Text + "' WHERE a_index = '" + this.textBox1.Text + "'");
      int selectedIndex = this.listBox1.SelectedIndex;
      if (this.textBox104.Text != "")
        this.SearchList(this.textBox104.Text);
      else
        this.LoadListBox();
      this.listBox1.SelectedIndex = selectedIndex;
      this.textBox2.BackColor = Color.White;
      this.textBox2.BackColor = Color.White;
      this.textBox5.BackColor = Color.White;
      this.textBox6.BackColor = Color.White;
      this.textBox8.BackColor = Color.White;
      this.textBox10.BackColor = Color.White;
      this.textBox12.BackColor = Color.White;
      this.textBox13.BackColor = Color.White;
      this.textBox14.BackColor = Color.White;
      this.textBox16.BackColor = Color.White;
      this.textBox17.BackColor = Color.White;
      this.textBox18.BackColor = Color.White;
      this.textBox19.BackColor = Color.White;
      this.textBox20.BackColor = Color.White;
      this.textBox21.BackColor = Color.White;
      this.textBox22.BackColor = Color.White;
      this.textBox23.BackColor = Color.White;
      this.textBox24.BackColor = Color.White;
      this.textBox25.BackColor = Color.White;
      this.textBox26.BackColor = Color.White;
      this.textBox27.BackColor = Color.White;
      this.textBox31.BackColor = Color.White;
      this.textBox32.BackColor = Color.White;
      this.textBox33.BackColor = Color.White;
      this.textBox34.BackColor = Color.White;
      this.textBox35.BackColor = Color.White;
      this.textBox36.BackColor = Color.White;
      this.textBox37.BackColor = Color.White;
      this.textBox38.BackColor = Color.White;
      this.textBox39.BackColor = Color.White;
      this.textBox40.BackColor = Color.White;
      this.textBox41.BackColor = Color.White;
      this.textBox42.BackColor = Color.White;
      this.textBox43.BackColor = Color.White;
      this.textBox44.BackColor = Color.White;
      this.textBox45.BackColor = Color.White;
      this.textBox46.BackColor = Color.White;
      this.textBox47.BackColor = Color.White;
      this.textBox48.BackColor = Color.White;
      this.textBox54.BackColor = Color.White;
      this.textBox55.BackColor = Color.White;
      this.textBox56.BackColor = Color.White;
      this.textBox57.BackColor = Color.White;
      this.textBox58.BackColor = Color.White;
      this.textBox59.BackColor = Color.White;
      this.textBox60.BackColor = Color.White;
      this.textBox61.BackColor = Color.White;
      this.textBox62.BackColor = Color.White;
      this.textBox63.BackColor = Color.White;
      this.textBox64.BackColor = Color.White;
      this.textBox72.BackColor = Color.White;
      this.textBox73.BackColor = Color.White;
      this.textBox74.BackColor = Color.White;
      this.textBox75.BackColor = Color.White;
      this.textBox76.BackColor = Color.White;
      this.textBox77.BackColor = Color.White;
      this.textBox78.BackColor = Color.White;
      this.textBox79.BackColor = Color.White;
      this.textBox80.BackColor = Color.White;
      this.textBox81.BackColor = Color.White;
      this.textBox82.BackColor = Color.White;
      this.textBox83.BackColor = Color.White;
      this.textBox84.BackColor = Color.White;
      this.textBox85.BackColor = Color.White;
      this.textBox86.BackColor = Color.White;
      this.textBox87.BackColor = Color.White;
      this.textBox88.BackColor = Color.White;
      this.textBox89.BackColor = Color.White;
      this.textBox90.BackColor = Color.White;
      this.textBox91.BackColor = Color.White;
      this.textBox92.BackColor = Color.White;
      this.textBox93.BackColor = Color.White;
      this.richTextBox1.BackColor = Color.White;
      this.richTextBox2.BackColor = Color.White;
      this.richTextBox3.BackColor = Color.White;
      this.textBox97.BackColor = Color.White;
      this.textBox99.BackColor = Color.White;
      this.textBox100.BackColor = Color.White;
      this.textBox101.BackColor = Color.White;
      this.textBox102.BackColor = Color.White;
      this.textBox103.BackColor = Color.White;
      this.textBox104.BackColor = Color.White;
      this.comboBox1.BackColor = Color.White;
      this.comboBox2.BackColor = Color.White;
      this.comboBox3.BackColor = Color.White;
      this.comboBox4.BackColor = Color.White;
      this.comboBox5.BackColor = Color.White;
      this.comboBox6.BackColor = Color.White;
      this.comboBox7.BackColor = Color.White;
      this.comboBox8.BackColor = Color.White;
      this.comboBox9.BackColor = Color.White;
      this.comboBox10.BackColor = Color.White;
      this.comboBox11.BackColor = Color.White;
      this.comboBox12.BackColor = Color.White;
      this.comboBox13.BackColor = Color.White;
      this.comboBox14.BackColor = Color.White;
      this.comboBox15.BackColor = Color.White;
      this.comboBox16.BackColor = Color.White;
      this.comboBox17.BackColor = Color.White;
      this.comboBox18.BackColor = Color.White;
      this.comboBox19.BackColor = Color.White;
      this.comboBox20.BackColor = Color.White;
      this.comboBox21.BackColor = Color.White;
      this.comboBox22.BackColor = Color.White;
    }

    private void button1_Click(object sender, EventArgs e)
    {
      string Query = "INSERT INTO t_quest () VALUES ()";
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, Query);
      Console.WriteLine(Query);
      this.LoadListBox();
      this.listBox1.SelectedIndex = this.listBox1.Items.Count - 1;
      this.textBox5.Text = "1";
    }

    private void button3_Click(object sender, EventArgs e)
    {
      int selectedIndex = this.listBox1.SelectedIndex;
      string Query = "DELETE FROM t_quest WHERE a_index = '" + this.textBox1.Text + "'";
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, Query);
      Console.WriteLine(Query);
      this.LoadListBox();
      this.listBox1.SelectedIndex = selectedIndex - 1;
      int num = (int) new CustomMessage("Deleted :O").ShowDialog();
    }

    private void LoadStartUp()
    {
      this.comboBox1.Items.AddRange(new object[13]
      {
        (object) "0 - Repeat",
        (object) "1 - Collection",
        (object) "2 - Delivery",
        (object) "3 - Defeat",
        (object) "4 - Save",
        (object) "5 - Mining Experience",
        (object) "6 - Gathering Experience",
        (object) "7 - Charge Experience",
        (object) "8 - Process Experience",
        (object) "9 - Make Experience",
        (object) "10 - Tutorial",
        (object) "11 - PK",
        (object) "12 - Search"
      });
      this.comboBox2.Items.AddRange(new object[6]
      {
        (object) "0 - Can do only once",
        (object) "1 - Repeat unlimited times",
        (object) "2 - Once a day",
        (object) "3 - [Unknown 3]",
        (object) "4 - [Unknown 4]",
        (object) "5 - [Unknown 5]"
      });
      this.comboBox3.Items.AddRange(new object[10]
      {
        (object) "-1  All",
        (object) "0 - Titan",
        (object) "1 - Knight",
        (object) "2 - Healer",
        (object) "3 - Mage",
        (object) "4 - Rogue",
        (object) "5 - Sorcerer",
        (object) "6 - Night Shadow",
        (object) "7 - Ex-Rogue",
        (object) "8 - ArchMage"
      });
      this.comboBox4.Items.AddRange(new object[3]
      {
        (object) "0 - Personal",
        (object) "1 - Party",
        (object) "2 - Battle Group"
      });
      this.comboBox5.Items.AddRange(new object[4]
      {
        (object) "0 - NPC",
        (object) "1 - Item",
        (object) "2 - Level",
        (object) "3 - Area"
      });
      this.comboBox6.Items.AddRange(new object[10]
      {
        (object) "-1",
        (object) "0 - Kill Mob",
        (object) "1 - Collect Item",
        (object) "2 - Have Item",
        (object) "3 - PC",
        (object) "4 - Area",
        (object) "5 - Item Use",
        (object) "6 - Trigger",
        (object) "7 - Castle Dratan",
        (object) "8 - Castle Merac"
      });
      this.comboBox7.Items.AddRange(new object[10]
      {
        (object) "-1",
        (object) "0 - Kill Mob",
        (object) "1 - Collect Item",
        (object) "2 - Have Item",
        (object) "3 - PC",
        (object) "4 - Area",
        (object) "5 - Item Use",
        (object) "6 - Trigger",
        (object) "7 - Castle Dratan",
        (object) "8 - Castle Merac"
      });
      this.comboBox8.Items.AddRange(new object[10]
      {
        (object) "-1",
        (object) "0 - Kill Mob",
        (object) "1 - Collect Item",
        (object) "2 - Have Item",
        (object) "3 - PC",
        (object) "4 - Area",
        (object) "5 - Item Use",
        (object) "6 - Trigger",
        (object) "7 - Castle Dratan",
        (object) "8 - Castle Merac"
      });
      this.comboBox9.Items.AddRange(new object[9]
      {
        (object) "-1",
        (object) "0 - Item",
        (object) "1 - Gold ",
        (object) "2 - Exp",
        (object) "3 - SP",
        (object) "4 - Skill",
        (object) "5 - Special Skill",
        (object) "6 - Stat Point",
        (object) "7 - RVRPOINT"
      });
      this.comboBox10.Items.AddRange(new object[9]
      {
        (object) "-1",
        (object) "0 - Item",
        (object) "1 - Gold ",
        (object) "2 - Exp",
        (object) "3 - SP",
        (object) "4 - Skill",
        (object) "5 - Special Skill",
        (object) "6 - Stat Point",
        (object) "7 - RVRPOINT"
      });
      this.comboBox11.Items.AddRange(new object[9]
      {
        (object) "-1",
        (object) "0 - Item",
        (object) "1 - Gold ",
        (object) "2 - Exp",
        (object) "3 - SP",
        (object) "4 - Skill",
        (object) "5 - Special Skill",
        (object) "6 - Stat Point",
        (object) "7 - RVRPOINT"
      });
      this.comboBox12.Items.AddRange(new object[9]
      {
        (object) "-1",
        (object) "0 - Item",
        (object) "1 - Gold ",
        (object) "2 - Exp",
        (object) "3 - SP",
        (object) "4 - Skill",
        (object) "5 - Special Skill",
        (object) "6 - Stat Point",
        (object) "7 - RVRPOINT"
      });
      this.comboBox13.Items.AddRange(new object[9]
      {
        (object) "-1",
        (object) "0 - Item",
        (object) "1 - Gold ",
        (object) "2 - Exp",
        (object) "3 - SP",
        (object) "4 - Skill",
        (object) "5 - Special Skill",
        (object) "6 - Stat Point",
        (object) "7 - RVRPOINT"
      });
      this.comboBox14.Items.AddRange(new object[9]
      {
        (object) "-1",
        (object) "0 - Item",
        (object) "1 - Gold ",
        (object) "2 - Exp",
        (object) "3 - SP",
        (object) "4 - Skill",
        (object) "5 - Special Skill",
        (object) "6 - Stat Point",
        (object) "7 - RVRPOINT"
      });
      this.comboBox15.Items.AddRange(new object[9]
      {
        (object) "-1",
        (object) "0 - Item",
        (object) "1 - Gold ",
        (object) "2 - Exp",
        (object) "3 - SP",
        (object) "4 - Skill",
        (object) "5 - Special Skill",
        (object) "6 - Stat Point",
        (object) "7 - RVRPOINT"
      });
      this.comboBox16.Items.AddRange(new object[9]
      {
        (object) "-1",
        (object) "0 - Item",
        (object) "1 - Gold ",
        (object) "2 - Exp",
        (object) "3 - SP",
        (object) "4 - Skill",
        (object) "5 - Special Skill",
        (object) "6 - Stat Point",
        (object) "7 - RVRPOINT"
      });
      this.comboBox17.Items.AddRange(new object[9]
      {
        (object) "-1",
        (object) "0 - Item",
        (object) "1 - Gold ",
        (object) "2 - Exp",
        (object) "3 - SP",
        (object) "4 - Skill",
        (object) "5 - Special Skill",
        (object) "6 - Stat Point",
        (object) "7 - RVRPOINT"
      });
      this.comboBox18.Items.AddRange(new object[9]
      {
        (object) "-1",
        (object) "0 - Item",
        (object) "1 - Gold ",
        (object) "2 - Exp",
        (object) "3 - SP",
        (object) "4 - Skill",
        (object) "5 - Special Skill",
        (object) "6 - Stat Point",
        (object) "7 - RVRPOINT"
      });
      this.comboBox19.Items.AddRange(new object[9]
      {
        (object) "-1",
        (object) "0 - Item",
        (object) "1 - Gold ",
        (object) "2 - Exp",
        (object) "3 - SP",
        (object) "4 - Skill",
        (object) "5 - Special Skill",
        (object) "6 - Stat Point",
        (object) "7 - RVRPOINT"
      });
      this.comboBox20.Items.AddRange(new object[9]
      {
        (object) "-1",
        (object) "0 - Item",
        (object) "1 - Gold ",
        (object) "2 - Exp",
        (object) "3 - SP",
        (object) "4 - Skill",
        (object) "5 - Special Skill",
        (object) "6 - Stat Point",
        (object) "7 - RVRPOINT"
      });
      this.CbRvrType.Items.AddRange(new object[3]
      {
        (object) "0 - None",
        (object) "1 - KAILUX",
        (object) "2 - DEALERMOON"
      });
      this.CbRvRGrade.Items.AddRange(new object[10]
      {
        (object) "0 - None",
        (object) "1 - SQUIRE",
        (object) "2 - KNIGHT",
        (object) "3 - GENTOR",
        (object) "4 - HONORISE",
        (object) "5 - BARONE",
        (object) "6 - VISCONTE",
        (object) "7 - CONTE",
        (object) "8 - BARONE",
        (object) "9 - MARQUISE"
      });
      this.CbRvRGrade1.Items.AddRange(new object[6]
      {
        (object) "0 - None",
        (object) "1 - NEOPTYE",
        (object) "2 - ZELATOR",
        (object) "3 - THEORICUS",
        (object) "4 - PHILOSOPHUS",
        (object) "5 - ADEPTUS"
      });
    }

    private void exportStrItemlodToolStripMenuItem1_Click(object sender, EventArgs e)
    {
      int num = (int) MessageBox.Show("Comming Soon");
    }

    private void fileExportToolStripMenuItem_Click(object sender, EventArgs e)
    {
    }

    private void textBox104_TextChanged(object sender, EventArgs e)
    {
      if (this.language == "GER")
        this.listBox1.DataSource = (object) this.databaseHandle.SearchList(this.textBox104.Text, this.menuArrayGER, "t_quest");
      else if (this.language == "POL")
        this.listBox1.DataSource = (object) this.databaseHandle.SearchList(this.textBox104.Text, this.menuArrayPOL, "t_quest");
      else if (this.language == "BRA")
        this.listBox1.DataSource = (object) this.databaseHandle.SearchList(this.textBox104.Text, this.menuArrayBRA, "t_quest");
      else if (this.language == "RUS")
        this.listBox1.DataSource = (object) this.databaseHandle.SearchList(this.textBox104.Text, this.menuArrayRUS, "t_quest");
      else if (this.language == "FRA")
        this.listBox1.DataSource = (object) this.databaseHandle.SearchList(this.textBox104.Text, this.menuArrayFRA, "t_quest");
      else if (this.language == "ESP")
        this.listBox1.DataSource = (object) this.databaseHandle.SearchList(this.textBox104.Text, this.menuArrayESP, "t_quest");
      else if (this.language == "MEX")
        this.listBox1.DataSource = (object) this.databaseHandle.SearchList(this.textBox104.Text, this.menuArrayMEX, "t_quest");
      else if (this.language == "THA")
        this.listBox1.DataSource = (object) this.databaseHandle.SearchList(this.textBox104.Text, this.menuArrayTHA, "t_quest");
      else if (this.language == "ITA")
        this.listBox1.DataSource = (object) this.databaseHandle.SearchList(this.textBox104.Text, this.menuArrayITA, "t_quest");
      else if (this.language == "USA")
        this.listBox1.DataSource = (object) this.databaseHandle.SearchList(this.textBox104.Text, this.menuArrayUSA, "t_quest");
      else
        this.listBox1.DataSource = (object) this.databaseHandle.SearchList(this.textBox104.Text, this.menuArray, "t_quest");
    }

    private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
    {
      int num1 = (int) MessageBox.Show("Quest Editor by kravens, THANKS to DamonA for help with all!", "Created by:");
      int num2 = (int) MessageBox.Show("If you wanna more tools contact with kravens. Skype: Choke1996", "Information");
    }

    private void getAlFromDBToolStripMenuItem_Click(object sender, EventArgs e)
    {
    }

    private void button5_Click(object sender, EventArgs e)
    {
      int num = (int) MessageBox.Show("ID Map where quest Start.", "Help");
    }

    private void button6_Click(object sender, EventArgs e)
    {
      int num = (int) MessageBox.Show("ID Map where quest End.", "Help");
    }

    private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox4.Text = this.GetIndexByComboBox(this.comboBox2.Text).ToString();
    }

    private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox3.Text = this.GetIndexByComboBox(this.comboBox1.Text).ToString();
    }

    private void comboBox3_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox15.Text = this.GetIndexByComboBox(this.comboBox3.Text).ToString();
    }

    private void comboBox4_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox98.Text = this.GetIndexByComboBox(this.comboBox4.Text).ToString();
    }

    private void comboBox21_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox9.Text = this.GetIndexByComboBox(this.comboBox21.Text).ToString();
    }

    private void comboBox22_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox11.Text = this.GetIndexByComboBox(this.comboBox22.Text).ToString();
    }

    private void comboBox5_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox7.Text = this.GetIndexByComboBox(this.comboBox5.Text).ToString();
    }

    private void comboBox6_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox28.Text = this.GetIndexByComboBox(this.comboBox6.Text).ToString();
    }

    private void comboBox7_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox29.Text = this.GetIndexByComboBox(this.comboBox7.Text).ToString();
    }

    private void comboBox8_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox30.Text = this.GetIndexByComboBox(this.comboBox8.Text).ToString();
    }

    private void comboBox9_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox49.Text = this.GetIndexByComboBox(this.comboBox9.Text).ToString();
    }

    private void comboBox10_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox50.Text = this.GetIndexByComboBox(this.comboBox10.Text).ToString();
    }

    private void comboBox11_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox51.Text = this.GetIndexByComboBox(this.comboBox11.Text).ToString();
    }

    private void comboBox12_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox52.Text = this.GetIndexByComboBox(this.comboBox12.Text).ToString();
    }

    private void comboBox13_SelectedIndexChanged_1(object sender, EventArgs e)
    {
      this.textBox53.Text = this.GetIndexByComboBox(this.comboBox13.Text).ToString();
    }

    private void comboBox14_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox65.Text = this.GetIndexByComboBox(this.comboBox14.Text).ToString();
    }

    private void comboBox15_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox66.Text = this.GetIndexByComboBox(this.comboBox15.Text).ToString();
    }

    private void comboBox16_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox67.Text = this.GetIndexByComboBox(this.comboBox16.Text).ToString();
    }

    private void comboBox17_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox68.Text = this.GetIndexByComboBox(this.comboBox17.Text).ToString();
    }

    private void comboBox18_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox69.Text = this.GetIndexByComboBox(this.comboBox18.Text).ToString();
    }

    private void comboBox19_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox70.Text = this.GetIndexByComboBox(this.comboBox19.Text).ToString();
    }

    private void comboBox20_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox71.Text = this.GetIndexByComboBox(this.comboBox20.Text).ToString();
    }

    private void button7_Click(object sender, EventArgs e)
    {
      this.namee = this.StringFromLanguage();
      this.desc = this.DescrFromLanguage();
      this.desc2 = this.Descr2FromLanguage();
      this.desc3 = this.Descr3FromLanguage();
      string str1 = "UPDATE t_quest SET a_index = '" + this.textBox1.Text + "', ";
      string str2 = this.textBox2.Text.Replace("'", "\\'").Replace("\"", "\\\"");
      string str3 = str1 + "a_name = '" + str2 + "', " + this.namee + " = '" + str2 + "', a_type1 = '" + this.textBox3.Text + "', a_type2 = '" + this.textBox4.Text + "', a_enable = '" + this.textBox5.Text + "', a_prequest_num = '" + this.textBox6.Text + "', a_start_type = '" + this.textBox7.Text + "', a_start_data = '" + this.textBox8.Text + "', a_start_npc_zone_num = '" + this.textBox9.Text + "', a_prize_npc = '" + this.textBox10.Text + "', a_prize_npc_zone_num = '" + this.textBox11.Text + "', a_need_exp = '" + this.textBox12.Text + "', a_need_min_level = '" + this.textBox13.Text + "', a_need_max_level = '" + this.textBox14.Text + "', a_need_job = '" + this.textBox15.Text + "', a_need_item0 = '" + this.textBox16.Text + "', a_need_item1 = '" + this.textBox17.Text + "', a_need_item2 = '" + this.textBox18.Text + "', a_need_item3 = '" + this.textBox19.Text + "', a_need_item4 = '" + this.textBox20.Text + "', a_need_item_count0 = '" + this.textBox21.Text + "', a_need_item_count1 = '" + this.textBox22.Text + "', a_need_item_count2 = '" + this.textBox23.Text + "', a_need_item_count3 = '" + this.textBox24.Text + "', a_need_item_count4 = '" + this.textBox25.Text + "', a_need_rvr_type = '" + this.textBox26.Text + "', a_need_rvr_grade = '" + this.textBox27.Text + "', a_condition0_type = '" + this.textBox28.Text + "', a_condition1_type = '" + this.textBox29.Text + "', a_condition2_type = '" + this.textBox30.Text + "', a_condition0_index = '" + this.textBox31.Text + "', a_condition1_index = '" + this.textBox32.Text + "', a_condition2_index = '" + this.textBox33.Text + "', a_condition0_num = '" + this.textBox34.Text + "', a_condition1_num = '" + this.textBox35.Text + "', a_condition2_num = '" + this.textBox36.Text + "', a_condition0_data0 = '" + this.textBox37.Text + "', a_condition0_data1 = '" + this.textBox38.Text + "', a_condition0_data2 = '" + this.textBox39.Text + "', a_condition0_data3 = '" + this.textBox40.Text + "', a_condition1_data0 = '" + this.textBox41.Text + "', a_condition1_data1 = '" + this.textBox42.Text + "', a_condition1_data2 = '" + this.textBox43.Text + "', a_condition1_data3 = '" + this.textBox44.Text + "', a_condition2_data0 = '" + this.textBox45.Text + "', a_condition2_data1 = '" + this.textBox46.Text + "', a_condition2_data2 = '" + this.textBox47.Text + "', a_condition2_data3 = '" + this.textBox48.Text + "', a_prize_type0 = '" + this.textBox49.Text + "', a_prize_type1 = '" + this.textBox50.Text + "', a_prize_type2 = '" + this.textBox51.Text + "', a_prize_type3 = '" + this.textBox52.Text + "', a_prize_type4 = '" + this.textBox53.Text + "', a_prize_index0 = '" + this.textBox54.Text + "', a_prize_index1 = '" + this.textBox55.Text + "', a_prize_index2 = '" + this.textBox56.Text + "', a_prize_index3 = '" + this.textBox57.Text + "', a_prize_index4 = '" + this.textBox58.Text + "', a_prize_data0 = '" + this.textBox59.Text + "', a_prize_data1 = '" + this.textBox60.Text + "', a_prize_data2 = '" + this.textBox61.Text + "', a_prize_data3 = '" + this.textBox62.Text + "', a_prize_data4 = '" + this.textBox63.Text + "', a_option_prize = '" + this.textBox64.Text + "', a_opt_prize_type0 = '" + this.textBox65.Text + "', a_opt_prize_type1 = '" + this.textBox66.Text + "', a_opt_prize_type2 = '" + this.textBox67.Text + "', a_opt_prize_type3 = '" + this.textBox68.Text + "', a_opt_prize_type4 = '" + this.textBox69.Text + "', a_opt_prize_type5 = '" + this.textBox70.Text + "', a_opt_prize_type6 = '" + this.textBox71.Text + "', a_opt_prize_index0 = '" + this.textBox72.Text + "', a_opt_prize_index1 = '" + this.textBox73.Text + "', a_opt_prize_index2 = '" + this.textBox74.Text + "', a_opt_prize_index3 = '" + this.textBox75.Text + "', a_opt_prize_index4 = '" + this.textBox76.Text + "', a_opt_prize_index5 = '" + this.textBox77.Text + "', a_opt_prize_index6 = '" + this.textBox78.Text + "', a_opt_prize_data0 = '" + this.textBox79.Text + "', a_opt_prize_data1 = '" + this.textBox80.Text + "', a_opt_prize_data2 = '" + this.textBox81.Text + "', a_opt_prize_data3 = '" + this.textBox82.Text + "', a_opt_prize_data4 = '" + this.textBox83.Text + "', a_opt_prize_data5 = '" + this.textBox84.Text + "', a_opt_prize_data6 = '" + this.textBox85.Text + "', a_opt_prize_plus0 = '" + this.textBox86.Text + "', a_opt_prize_plus1 = '" + this.textBox87.Text + "', a_opt_prize_plus2 = '" + this.textBox88.Text + "', a_opt_prize_plus3 = '" + this.textBox89.Text + "', a_opt_prize_plus4 = '" + this.textBox90.Text + "', a_opt_prize_plus5 = '" + this.textBox91.Text + "', a_opt_prize_plus6 = '" + this.textBox92.Text + "', a_only_opt_prize = '" + this.textBox93.Text + "', ";
      string str4 = this.richTextBox1.Text.Replace("'", "\\'").Replace("\"", "\\\"");
      string str5 = this.richTextBox2.Text.Replace("'", "\\'").Replace("\"", "\\\"");
      string str6 = this.richTextBox3.Text.Replace("'", "\\'").Replace("\"", "\\\"");
      string Query = str3 + "a_desc = '" + str4 + "', a_desc2 = '" + str5 + "', a_desc3 = '" + str6 + "', " + this.desc + " = '" + str4 + "', " + this.desc2 + " = '" + str5 + "', " + this.desc3 + " = '" + str6 + "', a_failvalue = '" + this.textBox97.Text + "', a_partyscale = '" + this.textBox98.Text + "', a_start_give_item = '" + this.textBox99.Text + "', a_start_give_kindcount = '" + this.textBox100.Text + "', a_start_give_numcount = '" + this.textBox101.Text + "', a_start_trigger_id = '" + this.textBox102.Text + "', a_quest_flag = '" + this.textBox103.Text + "' WHERE a_index = '" + this.textBox1.Text + "'";
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, Query);
      Console.WriteLine(Query);
      int selectedIndex = this.listBox1.SelectedIndex;
      if (this.textBox104.Text != "")
        this.SearchList(this.textBox104.Text);
      else
        this.LoadListBox();
      this.listBox1.SelectedIndex = selectedIndex;
      this.textBox2.BackColor = Color.White;
      this.textBox2.BackColor = Color.White;
      this.textBox5.BackColor = Color.White;
      this.textBox6.BackColor = Color.White;
      this.textBox8.BackColor = Color.White;
      this.textBox10.BackColor = Color.White;
      this.textBox12.BackColor = Color.White;
      this.textBox13.BackColor = Color.White;
      this.textBox14.BackColor = Color.White;
      this.textBox16.BackColor = Color.White;
      this.textBox17.BackColor = Color.White;
      this.textBox18.BackColor = Color.White;
      this.textBox19.BackColor = Color.White;
      this.textBox20.BackColor = Color.White;
      this.textBox21.BackColor = Color.White;
      this.textBox22.BackColor = Color.White;
      this.textBox23.BackColor = Color.White;
      this.textBox24.BackColor = Color.White;
      this.textBox25.BackColor = Color.White;
      this.textBox26.BackColor = Color.White;
      this.textBox27.BackColor = Color.White;
      this.textBox31.BackColor = Color.White;
      this.textBox32.BackColor = Color.White;
      this.textBox33.BackColor = Color.White;
      this.textBox34.BackColor = Color.White;
      this.textBox35.BackColor = Color.White;
      this.textBox36.BackColor = Color.White;
      this.textBox37.BackColor = Color.White;
      this.textBox38.BackColor = Color.White;
      this.textBox39.BackColor = Color.White;
      this.textBox40.BackColor = Color.White;
      this.textBox41.BackColor = Color.White;
      this.textBox42.BackColor = Color.White;
      this.textBox43.BackColor = Color.White;
      this.textBox44.BackColor = Color.White;
      this.textBox45.BackColor = Color.White;
      this.textBox46.BackColor = Color.White;
      this.textBox47.BackColor = Color.White;
      this.textBox48.BackColor = Color.White;
      this.textBox54.BackColor = Color.White;
      this.textBox55.BackColor = Color.White;
      this.textBox56.BackColor = Color.White;
      this.textBox57.BackColor = Color.White;
      this.textBox58.BackColor = Color.White;
      this.textBox59.BackColor = Color.White;
      this.textBox60.BackColor = Color.White;
      this.textBox61.BackColor = Color.White;
      this.textBox62.BackColor = Color.White;
      this.textBox63.BackColor = Color.White;
      this.textBox64.BackColor = Color.White;
      this.textBox72.BackColor = Color.White;
      this.textBox73.BackColor = Color.White;
      this.textBox74.BackColor = Color.White;
      this.textBox75.BackColor = Color.White;
      this.textBox76.BackColor = Color.White;
      this.textBox77.BackColor = Color.White;
      this.textBox78.BackColor = Color.White;
      this.textBox79.BackColor = Color.White;
      this.textBox80.BackColor = Color.White;
      this.textBox81.BackColor = Color.White;
      this.textBox82.BackColor = Color.White;
      this.textBox83.BackColor = Color.White;
      this.textBox84.BackColor = Color.White;
      this.textBox85.BackColor = Color.White;
      this.textBox86.BackColor = Color.White;
      this.textBox87.BackColor = Color.White;
      this.textBox88.BackColor = Color.White;
      this.textBox89.BackColor = Color.White;
      this.textBox90.BackColor = Color.White;
      this.textBox91.BackColor = Color.White;
      this.textBox92.BackColor = Color.White;
      this.textBox93.BackColor = Color.White;
      this.richTextBox1.BackColor = Color.White;
      this.richTextBox2.BackColor = Color.White;
      this.richTextBox3.BackColor = Color.White;
      this.textBox97.BackColor = Color.White;
      this.textBox99.BackColor = Color.White;
      this.textBox100.BackColor = Color.White;
      this.textBox101.BackColor = Color.White;
      this.textBox102.BackColor = Color.White;
      this.textBox103.BackColor = Color.White;
      this.textBox104.BackColor = Color.White;
      this.comboBox1.BackColor = Color.White;
      this.comboBox2.BackColor = Color.White;
      this.comboBox3.BackColor = Color.White;
      this.comboBox4.BackColor = Color.White;
      this.comboBox5.BackColor = Color.White;
      this.comboBox6.BackColor = Color.White;
      this.comboBox7.BackColor = Color.White;
      this.comboBox8.BackColor = Color.White;
      this.comboBox9.BackColor = Color.White;
      this.comboBox10.BackColor = Color.White;
      this.comboBox11.BackColor = Color.White;
      this.comboBox12.BackColor = Color.White;
      this.comboBox13.BackColor = Color.White;
      this.comboBox14.BackColor = Color.White;
      this.comboBox15.BackColor = Color.White;
      this.comboBox16.BackColor = Color.White;
      this.comboBox17.BackColor = Color.White;
      this.comboBox18.BackColor = Color.White;
      this.comboBox19.BackColor = Color.White;
      this.comboBox20.BackColor = Color.White;
      this.comboBox21.BackColor = Color.White;
      this.comboBox22.BackColor = Color.White;
      int num = (int) new CustomMessage("Done :)").ShowDialog();
    }

    private void textBox2_KeyDown(object sender, KeyEventArgs e)
    {
      this.textBox2.BackColor = Color.LightSteelBlue;
    }

    private void richTextBox1_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.richTextBox1.BackColor = Color.LightBlue;
    }

    private void richTextBox2_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.richTextBox2.BackColor = Color.LightBlue;
    }

    private void richTextBox3_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.richTextBox3.BackColor = Color.LightBlue;
    }

    private void textBox5_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox5.BackColor = Color.LightBlue;
    }

    private void textBox16_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox16.BackColor = Color.LightBlue;
    }

    private void textBox17_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox17.BackColor = Color.LightBlue;
    }

    private void textBox18_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox18.BackColor = Color.LightBlue;
    }

    private void textBox19_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox19.BackColor = Color.LightBlue;
    }

    private void textBox20_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox20.BackColor = Color.LightBlue;
    }

    private void textBox21_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox21.BackColor = Color.LightBlue;
    }

    private void textBox22_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox22.BackColor = Color.LightBlue;
    }

    private void textBox23_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox23.BackColor = Color.LightBlue;
    }

    private void textBox24_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox24.BackColor = Color.LightBlue;
    }

    private void textBox25_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox25.BackColor = Color.LightBlue;
    }

    private void textBox13_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox13.BackColor = Color.LightBlue;
    }

    private void textBox14_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox14.BackColor = Color.LightBlue;
    }

    private void textBox12_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox12.BackColor = Color.LightBlue;
    }

    private void textBox6_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox6.BackColor = Color.LightBlue;
    }

    private void textBox8_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox8.BackColor = Color.LightBlue;
    }

    private void textBox10_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox10.BackColor = Color.LightBlue;
    }

    private void textBox31_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox31.BackColor = Color.LightBlue;
    }

    private void textBox34_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox34.BackColor = Color.LightBlue;
    }

    private void textBox37_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox37.BackColor = Color.LightBlue;
    }

    private void textBox38_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox38.BackColor = Color.LightBlue;
    }

    private void textBox39_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox39.BackColor = Color.LightBlue;
    }

    private void textBox40_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox40.BackColor = Color.LightBlue;
    }

    private void textBox32_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox32.BackColor = Color.LightBlue;
    }

    private void textBox35_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox35.BackColor = Color.LightBlue;
    }

    private void textBox41_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox41.BackColor = Color.LightBlue;
    }

    private void textBox42_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox42.BackColor = Color.LightBlue;
    }

    private void textBox43_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox43.BackColor = Color.LightBlue;
    }

    private void textBox44_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox44.BackColor = Color.LightBlue;
    }

    private void textBox33_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox33.BackColor = Color.LightBlue;
    }

    private void textBox36_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox36.BackColor = Color.LightBlue;
    }

    private void textBox45_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox45.BackColor = Color.LightBlue;
    }

    private void textBox46_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox46.BackColor = Color.LightBlue;
    }

    private void textBox47_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox47.BackColor = Color.LightBlue;
    }

    private void textBox48_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox48.BackColor = Color.LightBlue;
    }

    private void textBox54_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox54.BackColor = Color.LightBlue;
    }

    private void textBox55_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox55.BackColor = Color.LightBlue;
    }

    private void textBox56_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox56.BackColor = Color.LightBlue;
    }

    private void textBox57_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox57.BackColor = Color.LightBlue;
    }

    private void textBox58_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox58.BackColor = Color.LightBlue;
    }

    private void textBox59_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox59.BackColor = Color.LightBlue;
    }

    private void textBox60_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox60.BackColor = Color.LightBlue;
    }

    private void textBox61_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox61.BackColor = Color.LightBlue;
    }

    private void textBox62_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox62.BackColor = Color.LightBlue;
    }

    private void textBox63_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox63.BackColor = Color.LightBlue;
    }

    private void textBox72_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox72.BackColor = Color.LightBlue;
    }

    private void textBox73_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox73.BackColor = Color.LightBlue;
    }

    private void textBox74_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox74.BackColor = Color.LightBlue;
    }

    private void textBox75_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox75.BackColor = Color.LightBlue;
    }

    private void textBox76_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox76.BackColor = Color.LightBlue;
    }

    private void textBox77_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox77.BackColor = Color.LightBlue;
    }

    private void textBox78_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox78.BackColor = Color.LightBlue;
    }

    private void textBox79_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox79.BackColor = Color.LightBlue;
    }

    private void textBox80_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox80.BackColor = Color.LightBlue;
    }

    private void textBox81_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox81.BackColor = Color.LightBlue;
    }

    private void textBox82_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox82.BackColor = Color.LightBlue;
    }

    private void textBox83_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox83.BackColor = Color.LightBlue;
    }

    private void textBox84_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox84.BackColor = Color.LightBlue;
    }

    private void textBox85_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox85.BackColor = Color.LightBlue;
    }

    private void textBox86_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox86.BackColor = Color.LightBlue;
    }

    private void textBox87_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox87.BackColor = Color.LightBlue;
    }

    private void textBox88_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox88.BackColor = Color.LightBlue;
    }

    private void textBox89_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox89.BackColor = Color.LightBlue;
    }

    private void textBox90_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox90.BackColor = Color.LightBlue;
    }

    private void textBox91_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox91.BackColor = Color.LightBlue;
    }

    private void textBox92_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox92.BackColor = Color.LightBlue;
    }

    private void textBox64_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox64.BackColor = Color.LightBlue;
    }

    private void textBox93_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox93.BackColor = Color.LightBlue;
    }

    private void textBox102_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox102.BackColor = Color.LightBlue;
    }

    private void textBox97_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox97.BackColor = Color.LightBlue;
    }

    private void textBox103_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox103.BackColor = Color.LightBlue;
    }

    private void textBox99_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox99.BackColor = Color.LightBlue;
    }

    private void textBox26_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox26.BackColor = Color.LightBlue;
    }

    private void textBox100_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox100.BackColor = Color.LightBlue;
    }

    private void textBox27_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox27.BackColor = Color.LightBlue;
    }

    private void textBox101_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.textBox101.BackColor = Color.LightBlue;
    }

    private void comboBox1_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.comboBox1.BackColor = Color.LightBlue;
    }

    private void comboBox2_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.comboBox2.BackColor = Color.LightBlue;
    }

    private void comboBox3_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.comboBox3.BackColor = Color.LightBlue;
    }

    private void comboBox4_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.comboBox4.BackColor = Color.LightBlue;
    }

    private void comboBox5_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.comboBox5.BackColor = Color.LightBlue;
    }

    private void comboBox6_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.comboBox6.BackColor = Color.LightBlue;
    }

    private void comboBox7_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.comboBox7.BackColor = Color.LightBlue;
    }

    private void comboBox8_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.comboBox8.BackColor = Color.LightBlue;
    }

    private void comboBox9_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.comboBox9.BackColor = Color.LightBlue;
    }

    private void comboBox10_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.comboBox10.BackColor = Color.LightBlue;
    }

    private void comboBox11_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.comboBox11.BackColor = Color.LightBlue;
    }

    private void comboBox12_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.comboBox12.BackColor = Color.LightBlue;
    }

    private void comboBox13_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.comboBox13.BackColor = Color.LightBlue;
    }

    private void comboBox14_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.comboBox14.BackColor = Color.LightBlue;
    }

    private void comboBox15_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.comboBox15.BackColor = Color.LightBlue;
    }

    private void comboBox16_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.comboBox16.BackColor = Color.LightBlue;
    }

    private void comboBox17_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.comboBox17.BackColor = Color.LightBlue;
    }

    private void comboBox18_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.comboBox18.BackColor = Color.LightBlue;
    }

    private void comboBox19_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.comboBox19.BackColor = Color.LightBlue;
    }

    private void comboBox20_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.comboBox20.BackColor = Color.LightBlue;
    }

    private void comboBox21_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.comboBox21.BackColor = Color.LightBlue;
    }

    private void comboBox22_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.comboBox22.BackColor = Color.LightBlue;
    }

    private void exportToolStripMenuItem_Click(object sender, EventArgs e)
    {
      new LodExporter.LodExporter().Show();
    }

    private void exportStrQuestToolStripMenuItem_Click(object sender, EventArgs e)
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
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (QuestEditor));
      this.menuStrip1 = new MenuStrip();
      this.fileExportToolStripMenuItem = new ToolStripMenuItem();
      this.exportToolStripMenuItem = new ToolStripMenuItem();
      this.exportStrQuestToolStripMenuItem = new ToolStripMenuItem();
      this.groupBox3 = new GroupBox();
      this.BtnCopy = new Button();
      this.button3 = new Button();
      this.button1 = new Button();
      this.listBox1 = new ListBox();
      this.groupBox5 = new GroupBox();
      this.textBox104 = new TextBox();
      this.label7 = new Label();
      this.textBox12 = new TextBox();
      this.tabControl1 = new TabControl();
      this.tabPage1 = new TabPage();
      this.groupBox8 = new GroupBox();
      this.CbRvRGrade1 = new ComboBox();
      this.CbRvRGrade = new ComboBox();
      this.CbRvrType = new ComboBox();
      this.textBox27 = new TextBox();
      this.textBox26 = new TextBox();
      this.label9 = new Label();
      this.label8 = new Label();
      this.label109 = new Label();
      this.textBox15 = new TextBox();
      this.label108 = new Label();
      this.label107 = new Label();
      this.label106 = new Label();
      this.label105 = new Label();
      this.textBox98 = new TextBox();
      this.textBox11 = new TextBox();
      this.textBox9 = new TextBox();
      this.textBox7 = new TextBox();
      this.textBox4 = new TextBox();
      this.textBox3 = new TextBox();
      this.groupBox11 = new GroupBox();
      this.PbEndNPCItem = new PictureBox();
      this.PbStartItemNPC = new PictureBox();
      this.label118 = new Label();
      this.label117 = new Label();
      this.TbEndNpcName = new TextBox();
      this.TbStartNpcName = new TextBox();
      this.button6 = new Button();
      this.button5 = new Button();
      this.comboBox22 = new ComboBox();
      this.comboBox21 = new ComboBox();
      this.label12 = new Label();
      this.comboBox5 = new ComboBox();
      this.label59 = new Label();
      this.label47 = new Label();
      this.textBox10 = new TextBox();
      this.label10 = new Label();
      this.label11 = new Label();
      this.textBox8 = new TextBox();
      this.textBox6 = new TextBox();
      this.label46 = new Label();
      this.groupBox10 = new GroupBox();
      this.comboBox4 = new ComboBox();
      this.label98 = new Label();
      this.groupBox9 = new GroupBox();
      this.comboBox3 = new ComboBox();
      this.label14 = new Label();
      this.label52 = new Label();
      this.textBox14 = new TextBox();
      this.textBox13 = new TextBox();
      this.label54 = new Label();
      this.label13 = new Label();
      this.comboBox2 = new ComboBox();
      this.comboBox1 = new ComboBox();
      this.groupBox4 = new GroupBox();
      this.PbItemNeed5 = new PictureBox();
      this.PbItemNeed4 = new PictureBox();
      this.PbItemNeed3 = new PictureBox();
      this.PbItemNeed2 = new PictureBox();
      this.PbItemNeed1 = new PictureBox();
      this.TbNeedName5 = new TextBox();
      this.TbNeedName4 = new TextBox();
      this.TbNeedName3 = new TextBox();
      this.TbNeedName2 = new TextBox();
      this.TbNeedName1 = new TextBox();
      this.label4 = new Label();
      this.textBox25 = new TextBox();
      this.textBox24 = new TextBox();
      this.textBox21 = new TextBox();
      this.textBox19 = new TextBox();
      this.label85 = new Label();
      this.textBox17 = new TextBox();
      this.label93 = new Label();
      this.label92 = new Label();
      this.textBox16 = new TextBox();
      this.textBox20 = new TextBox();
      this.label91 = new Label();
      this.label18 = new Label();
      this.textBox23 = new TextBox();
      this.label22 = new Label();
      this.textBox18 = new TextBox();
      this.textBox22 = new TextBox();
      this.label15 = new Label();
      this.label23 = new Label();
      this.label16 = new Label();
      this.groupBox1 = new GroupBox();
      this.cbEnabled = new CheckBox();
      this.label112 = new Label();
      this.label111 = new Label();
      this.label110 = new Label();
      this.richTextBox3 = new RichTextBox();
      this.richTextBox2 = new RichTextBox();
      this.richTextBox1 = new RichTextBox();
      this.label104 = new Label();
      this.label96 = new Label();
      this.label95 = new Label();
      this.textBox2 = new TextBox();
      this.label6 = new Label();
      this.label5 = new Label();
      this.textBox1 = new TextBox();
      this.label1 = new Label();
      this.textBox5 = new TextBox();
      this.label3 = new Label();
      this.label2 = new Label();
      this.tabPage3 = new TabPage();
      this.tabControl2 = new TabControl();
      this.tabPage2 = new TabPage();
      this.TbObj1 = new TextBox();
      this.PbCond1 = new PictureBox();
      this.textBox28 = new TextBox();
      this.groupBox2 = new GroupBox();
      this.TbObj1Npc3 = new TextBox();
      this.PbObj1NpcID3 = new PictureBox();
      this.TbObj1Npc2 = new TextBox();
      this.PbObj1NpcID2 = new PictureBox();
      this.TbObj1Npc1 = new TextBox();
      this.PbObj1NpcID1 = new PictureBox();
      this.label116 = new Label();
      this.label31 = new Label();
      this.label29 = new Label();
      this.label30 = new Label();
      this.textBox37 = new TextBox();
      this.textBox38 = new TextBox();
      this.textBox39 = new TextBox();
      this.textBox40 = new TextBox();
      this.label34 = new Label();
      this.comboBox6 = new ComboBox();
      this.label17 = new Label();
      this.textBox31 = new TextBox();
      this.label25 = new Label();
      this.textBox34 = new TextBox();
      this.label28 = new Label();
      this.tabPage4 = new TabPage();
      this.TbObj2 = new TextBox();
      this.PbCond2 = new PictureBox();
      this.textBox29 = new TextBox();
      this.groupBox12 = new GroupBox();
      this.TbObj2Npc3 = new TextBox();
      this.PbObj2NpcID3 = new PictureBox();
      this.TbObj2Npc2 = new TextBox();
      this.PbObj2NpcID2 = new PictureBox();
      this.TbObj2Npc1 = new TextBox();
      this.PbObj2NpcID1 = new PictureBox();
      this.label115 = new Label();
      this.label36 = new Label();
      this.label35 = new Label();
      this.label32 = new Label();
      this.textBox44 = new TextBox();
      this.label33 = new Label();
      this.textBox41 = new TextBox();
      this.textBox42 = new TextBox();
      this.textBox43 = new TextBox();
      this.comboBox7 = new ComboBox();
      this.label19 = new Label();
      this.textBox32 = new TextBox();
      this.label27 = new Label();
      this.label24 = new Label();
      this.textBox35 = new TextBox();
      this.tabPage5 = new TabPage();
      this.TbObj3 = new TextBox();
      this.PbCond3 = new PictureBox();
      this.textBox30 = new TextBox();
      this.label26 = new Label();
      this.comboBox8 = new ComboBox();
      this.textBox36 = new TextBox();
      this.textBox33 = new TextBox();
      this.label21 = new Label();
      this.label20 = new Label();
      this.groupBox6 = new GroupBox();
      this.label114 = new Label();
      this.TbObjNpc3 = new TextBox();
      this.PbNpcID3 = new PictureBox();
      this.TbObjNpc2 = new TextBox();
      this.PbNpcID2 = new PictureBox();
      this.TbObjNpc1 = new TextBox();
      this.PbNpcID1 = new PictureBox();
      this.textBox46 = new TextBox();
      this.textBox48 = new TextBox();
      this.textBox47 = new TextBox();
      this.label37 = new Label();
      this.textBox45 = new TextBox();
      this.label40 = new Label();
      this.label38 = new Label();
      this.label39 = new Label();
      this.Page2 = new TabPage();
      this.TbFileCol = new TextBox();
      this.tbFileRow = new TextBox();
      this.tbFileID = new TextBox();
      this.tabControl3 = new TabControl();
      this.tabPage8 = new TabPage();
      this.pictureBox15 = new PictureBox();
      this.pictureBox14 = new PictureBox();
      this.pictureBox13 = new PictureBox();
      this.pictureBox12 = new PictureBox();
      this.pictureBox11 = new PictureBox();
      this.tbItemDesc5 = new TextBox();
      this.tbItemDesc4 = new TextBox();
      this.tbItemDesc3 = new TextBox();
      this.tbItemDesc2 = new TextBox();
      this.tbItemDesc1 = new TextBox();
      this.PbPItem5 = new PictureBox();
      this.PbPItem4 = new PictureBox();
      this.PbPItem3 = new PictureBox();
      this.PbPItem2 = new PictureBox();
      this.PbPItem1 = new PictureBox();
      this.comboBox13 = new ComboBox();
      this.textBox59 = new TextBox();
      this.comboBox12 = new ComboBox();
      this.textBox63 = new TextBox();
      this.textBox60 = new TextBox();
      this.comboBox11 = new ComboBox();
      this.textBox61 = new TextBox();
      this.textBox58 = new TextBox();
      this.textBox62 = new TextBox();
      this.comboBox10 = new ComboBox();
      this.label60 = new Label();
      this.label48 = new Label();
      this.label58 = new Label();
      this.comboBox9 = new ComboBox();
      this.label55 = new Label();
      this.textBox57 = new TextBox();
      this.label57 = new Label();
      this.label45 = new Label();
      this.label56 = new Label();
      this.label44 = new Label();
      this.label49 = new Label();
      this.label43 = new Label();
      this.textBox56 = new TextBox();
      this.label42 = new Label();
      this.label41 = new Label();
      this.label50 = new Label();
      this.label53 = new Label();
      this.textBox55 = new TextBox();
      this.textBox54 = new TextBox();
      this.label51 = new Label();
      this.tabPage9 = new TabPage();
      this.pictureBox10 = new PictureBox();
      this.pictureBox9 = new PictureBox();
      this.pictureBox8 = new PictureBox();
      this.pictureBox7 = new PictureBox();
      this.pictureBox6 = new PictureBox();
      this.pictureBox5 = new PictureBox();
      this.pictureBox4 = new PictureBox();
      this.TbPrize2ItemDesc1 = new TextBox();
      this.TbPrize2ItemDesc2 = new TextBox();
      this.TbPrize2ItemDesc3 = new TextBox();
      this.TbPrize2ItemDesc4 = new TextBox();
      this.TbPrize2ItemDesc5 = new TextBox();
      this.TbPrize2ItemDesc6 = new TextBox();
      this.TbPrize2ItemDesc7 = new TextBox();
      this.PbItem7 = new PictureBox();
      this.PbItem6 = new PictureBox();
      this.PbItem5 = new PictureBox();
      this.PbItem4 = new PictureBox();
      this.PbItem3 = new PictureBox();
      this.PbItem2 = new PictureBox();
      this.PbItem1 = new PictureBox();
      this.textBox93 = new TextBox();
      this.label94 = new Label();
      this.textBox64 = new TextBox();
      this.label61 = new Label();
      this.comboBox20 = new ComboBox();
      this.comboBox19 = new ComboBox();
      this.comboBox18 = new ComboBox();
      this.comboBox17 = new ComboBox();
      this.comboBox16 = new ComboBox();
      this.comboBox15 = new ComboBox();
      this.comboBox14 = new ComboBox();
      this.label67 = new Label();
      this.label68 = new Label();
      this.label66 = new Label();
      this.label65 = new Label();
      this.label64 = new Label();
      this.label63 = new Label();
      this.label62 = new Label();
      this.textBox79 = new TextBox();
      this.textBox80 = new TextBox();
      this.label76 = new Label();
      this.label77 = new Label();
      this.textBox81 = new TextBox();
      this.textBox82 = new TextBox();
      this.textBox83 = new TextBox();
      this.textBox84 = new TextBox();
      this.textBox85 = new TextBox();
      this.label78 = new Label();
      this.label79 = new Label();
      this.label80 = new Label();
      this.label81 = new Label();
      this.label82 = new Label();
      this.textBox72 = new TextBox();
      this.textBox73 = new TextBox();
      this.label69 = new Label();
      this.label70 = new Label();
      this.textBox74 = new TextBox();
      this.textBox75 = new TextBox();
      this.textBox76 = new TextBox();
      this.textBox77 = new TextBox();
      this.textBox78 = new TextBox();
      this.label71 = new Label();
      this.label72 = new Label();
      this.label73 = new Label();
      this.label74 = new Label();
      this.label75 = new Label();
      this.textBox86 = new TextBox();
      this.textBox87 = new TextBox();
      this.textBox92 = new TextBox();
      this.label83 = new Label();
      this.label90 = new Label();
      this.label84 = new Label();
      this.label89 = new Label();
      this.textBox88 = new TextBox();
      this.label88 = new Label();
      this.textBox89 = new TextBox();
      this.label87 = new Label();
      this.textBox90 = new TextBox();
      this.label86 = new Label();
      this.textBox91 = new TextBox();
      this.textBox69 = new TextBox();
      this.textBox70 = new TextBox();
      this.textBox68 = new TextBox();
      this.textBox65 = new TextBox();
      this.textBox71 = new TextBox();
      this.textBox67 = new TextBox();
      this.textBox53 = new TextBox();
      this.textBox66 = new TextBox();
      this.textBox52 = new TextBox();
      this.textBox49 = new TextBox();
      this.textBox51 = new TextBox();
      this.textBox50 = new TextBox();
      this.tabPage7 = new TabPage();
      this.groupBox7 = new GroupBox();
      this.textBox103 = new TextBox();
      this.label103 = new Label();
      this.textBox102 = new TextBox();
      this.label102 = new Label();
      this.label99 = new Label();
      this.textBox100 = new TextBox();
      this.textBox97 = new TextBox();
      this.label97 = new Label();
      this.textBox101 = new TextBox();
      this.label101 = new Label();
      this.textBox99 = new TextBox();
      this.label100 = new Label();
      this.button7 = new Button();
      this.label113 = new Label();
      this.lblLang = new Label();
      this.label119 = new Label();
      this.pictureBox1 = new PictureBox();
      this.label120 = new Label();
      this.label121 = new Label();
      this.pictureBox2 = new PictureBox();
      this.label122 = new Label();
      this.pictureBox3 = new PictureBox();
      this.btnSaveAndNext = new Button();
      this.menuStrip1.SuspendLayout();
      this.groupBox3.SuspendLayout();
      this.groupBox5.SuspendLayout();
      this.tabControl1.SuspendLayout();
      this.tabPage1.SuspendLayout();
      this.groupBox8.SuspendLayout();
      this.groupBox11.SuspendLayout();
      ((ISupportInitialize) this.PbEndNPCItem).BeginInit();
      ((ISupportInitialize) this.PbStartItemNPC).BeginInit();
      this.groupBox10.SuspendLayout();
      this.groupBox9.SuspendLayout();
      this.groupBox4.SuspendLayout();
      ((ISupportInitialize) this.PbItemNeed5).BeginInit();
      ((ISupportInitialize) this.PbItemNeed4).BeginInit();
      ((ISupportInitialize) this.PbItemNeed3).BeginInit();
      ((ISupportInitialize) this.PbItemNeed2).BeginInit();
      ((ISupportInitialize) this.PbItemNeed1).BeginInit();
      this.groupBox1.SuspendLayout();
      this.tabPage3.SuspendLayout();
      this.tabControl2.SuspendLayout();
      this.tabPage2.SuspendLayout();
      ((ISupportInitialize) this.PbCond1).BeginInit();
      this.groupBox2.SuspendLayout();
      ((ISupportInitialize) this.PbObj1NpcID3).BeginInit();
      ((ISupportInitialize) this.PbObj1NpcID2).BeginInit();
      ((ISupportInitialize) this.PbObj1NpcID1).BeginInit();
      this.tabPage4.SuspendLayout();
      ((ISupportInitialize) this.PbCond2).BeginInit();
      this.groupBox12.SuspendLayout();
      ((ISupportInitialize) this.PbObj2NpcID3).BeginInit();
      ((ISupportInitialize) this.PbObj2NpcID2).BeginInit();
      ((ISupportInitialize) this.PbObj2NpcID1).BeginInit();
      this.tabPage5.SuspendLayout();
      ((ISupportInitialize) this.PbCond3).BeginInit();
      this.groupBox6.SuspendLayout();
      ((ISupportInitialize) this.PbNpcID3).BeginInit();
      ((ISupportInitialize) this.PbNpcID2).BeginInit();
      ((ISupportInitialize) this.PbNpcID1).BeginInit();
      this.Page2.SuspendLayout();
      this.tabControl3.SuspendLayout();
      this.tabPage8.SuspendLayout();
      ((ISupportInitialize) this.pictureBox15).BeginInit();
      ((ISupportInitialize) this.pictureBox14).BeginInit();
      ((ISupportInitialize) this.pictureBox13).BeginInit();
      ((ISupportInitialize) this.pictureBox12).BeginInit();
      ((ISupportInitialize) this.pictureBox11).BeginInit();
      ((ISupportInitialize) this.PbPItem5).BeginInit();
      ((ISupportInitialize) this.PbPItem4).BeginInit();
      ((ISupportInitialize) this.PbPItem3).BeginInit();
      ((ISupportInitialize) this.PbPItem2).BeginInit();
      ((ISupportInitialize) this.PbPItem1).BeginInit();
      this.tabPage9.SuspendLayout();
      ((ISupportInitialize) this.pictureBox10).BeginInit();
      ((ISupportInitialize) this.pictureBox9).BeginInit();
      ((ISupportInitialize) this.pictureBox8).BeginInit();
      ((ISupportInitialize) this.pictureBox7).BeginInit();
      ((ISupportInitialize) this.pictureBox6).BeginInit();
      ((ISupportInitialize) this.pictureBox5).BeginInit();
      ((ISupportInitialize) this.pictureBox4).BeginInit();
      ((ISupportInitialize) this.PbItem7).BeginInit();
      ((ISupportInitialize) this.PbItem6).BeginInit();
      ((ISupportInitialize) this.PbItem5).BeginInit();
      ((ISupportInitialize) this.PbItem4).BeginInit();
      ((ISupportInitialize) this.PbItem3).BeginInit();
      ((ISupportInitialize) this.PbItem2).BeginInit();
      ((ISupportInitialize) this.PbItem1).BeginInit();
      this.tabPage7.SuspendLayout();
      this.groupBox7.SuspendLayout();
      ((ISupportInitialize) this.pictureBox1).BeginInit();
      ((ISupportInitialize) this.pictureBox2).BeginInit();
      ((ISupportInitialize) this.pictureBox3).BeginInit();
      this.SuspendLayout();
      this.menuStrip1.AllowMerge = false;
      this.menuStrip1.BackColor = SystemColors.ControlLightLight;
      this.menuStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.fileExportToolStripMenuItem
      });
      this.menuStrip1.Location = new Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new Size(1056, 24);
      this.menuStrip1.TabIndex = 0;
      this.menuStrip1.Text = "menuStrip1";
      this.fileExportToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[2]
      {
        (ToolStripItem) this.exportToolStripMenuItem,
        (ToolStripItem) this.exportStrQuestToolStripMenuItem
      });
      this.fileExportToolStripMenuItem.Name = "fileExportToolStripMenuItem";
      this.fileExportToolStripMenuItem.Size = new Size(74, 20);
      this.fileExportToolStripMenuItem.Text = "File Export";
      this.fileExportToolStripMenuItem.Click += new EventHandler(this.fileExportToolStripMenuItem_Click);
      this.exportToolStripMenuItem.Name = "exportToolStripMenuItem";
      this.exportToolStripMenuItem.Size = new Size(192, 22);
      this.exportToolStripMenuItem.Text = "Export  questAll.lod";
      this.exportToolStripMenuItem.Click += new EventHandler(this.exportToolStripMenuItem_Click);
      this.exportStrQuestToolStripMenuItem.Name = "exportStrQuestToolStripMenuItem";
      this.exportStrQuestToolStripMenuItem.Size = new Size(192, 22);
      this.exportStrQuestToolStripMenuItem.Text = "Export strQuest_us.lod";
      this.exportStrQuestToolStripMenuItem.Click += new EventHandler(this.exportStrQuestToolStripMenuItem_Click);
      this.groupBox3.Controls.Add((Control) this.BtnCopy);
      this.groupBox3.Controls.Add((Control) this.button3);
      this.groupBox3.Controls.Add((Control) this.button1);
      this.groupBox3.Controls.Add((Control) this.listBox1);
      this.groupBox3.Location = new Point(12, 82);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Size = new Size(265, 581);
      this.groupBox3.TabIndex = 31;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "Quest";
      this.BtnCopy.FlatStyle = FlatStyle.Flat;
      this.BtnCopy.Location = new Point(91, 546);
      this.BtnCopy.Name = "BtnCopy";
      this.BtnCopy.Size = new Size(82, 23);
      this.BtnCopy.TabIndex = 5;
      this.BtnCopy.Text = "Copy";
      this.BtnCopy.UseVisualStyleBackColor = true;
      this.BtnCopy.Click += new EventHandler(this.BtnCopy_Click);
      this.button3.FlatStyle = FlatStyle.Flat;
      this.button3.Location = new Point(176, 546);
      this.button3.Name = "button3";
      this.button3.Size = new Size(83, 23);
      this.button3.TabIndex = 4;
      this.button3.Text = "Delete";
      this.button3.UseVisualStyleBackColor = true;
      this.button3.Click += new EventHandler(this.button3_Click);
      this.button1.FlatStyle = FlatStyle.Flat;
      this.button1.Location = new Point(6, 546);
      this.button1.Name = "button1";
      this.button1.Size = new Size(82, 23);
      this.button1.TabIndex = 2;
      this.button1.Text = "Add New";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.listBox1.FormattingEnabled = true;
      this.listBox1.Location = new Point(6, 19);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new Size(253, 524);
      this.listBox1.TabIndex = 1;
      this.listBox1.SelectedIndexChanged += new EventHandler(this.listBox1_SelectedIndexChanged);
      this.groupBox5.Controls.Add((Control) this.textBox104);
      this.groupBox5.Controls.Add((Control) this.label7);
      this.groupBox5.Location = new Point(12, 27);
      this.groupBox5.Name = "groupBox5";
      this.groupBox5.Size = new Size(265, 49);
      this.groupBox5.TabIndex = 32;
      this.groupBox5.TabStop = false;
      this.groupBox5.Text = "Search";
      this.textBox104.BorderStyle = BorderStyle.FixedSingle;
      this.textBox104.Location = new Point(43, 19);
      this.textBox104.Name = "textBox104";
      this.textBox104.Size = new Size(216, 20);
      this.textBox104.TabIndex = 83;
      this.textBox104.TextChanged += new EventHandler(this.textBox104_TextChanged);
      this.label7.AutoSize = true;
      this.label7.Location = new Point(6, 21);
      this.label7.Name = "label7";
      this.label7.Size = new Size(31, 13);
      this.label7.TabIndex = 21;
      this.label7.Text = "Text:";
      this.textBox12.BorderStyle = BorderStyle.FixedSingle;
      this.textBox12.Location = new Point(66, 65);
      this.textBox12.Name = "textBox12";
      this.textBox12.Size = new Size(207, 20);
      this.textBox12.TabIndex = 20;
      this.textBox12.KeyPress += new KeyPressEventHandler(this.textBox12_KeyPress);
      this.tabControl1.Controls.Add((Control) this.tabPage1);
      this.tabControl1.Controls.Add((Control) this.tabPage3);
      this.tabControl1.Controls.Add((Control) this.Page2);
      this.tabControl1.Controls.Add((Control) this.tabPage7);
      this.tabControl1.Location = new Point(283, 27);
      this.tabControl1.Name = "tabControl1";
      this.tabControl1.SelectedIndex = 0;
      this.tabControl1.Size = new Size(773, 636);
      this.tabControl1.TabIndex = 33;
      this.tabPage1.BorderStyle = BorderStyle.FixedSingle;
      this.tabPage1.Controls.Add((Control) this.groupBox8);
      this.tabPage1.Controls.Add((Control) this.label109);
      this.tabPage1.Controls.Add((Control) this.textBox15);
      this.tabPage1.Controls.Add((Control) this.label108);
      this.tabPage1.Controls.Add((Control) this.label107);
      this.tabPage1.Controls.Add((Control) this.label106);
      this.tabPage1.Controls.Add((Control) this.label105);
      this.tabPage1.Controls.Add((Control) this.textBox98);
      this.tabPage1.Controls.Add((Control) this.textBox11);
      this.tabPage1.Controls.Add((Control) this.textBox9);
      this.tabPage1.Controls.Add((Control) this.textBox7);
      this.tabPage1.Controls.Add((Control) this.textBox4);
      this.tabPage1.Controls.Add((Control) this.textBox3);
      this.tabPage1.Controls.Add((Control) this.groupBox11);
      this.tabPage1.Controls.Add((Control) this.groupBox10);
      this.tabPage1.Controls.Add((Control) this.groupBox9);
      this.tabPage1.Controls.Add((Control) this.comboBox2);
      this.tabPage1.Controls.Add((Control) this.comboBox1);
      this.tabPage1.Controls.Add((Control) this.groupBox4);
      this.tabPage1.Controls.Add((Control) this.groupBox1);
      this.tabPage1.Controls.Add((Control) this.label3);
      this.tabPage1.Controls.Add((Control) this.label2);
      this.tabPage1.Location = new Point(4, 22);
      this.tabPage1.Name = "tabPage1";
      this.tabPage1.Padding = new Padding(3);
      this.tabPage1.Size = new Size(765, 610);
      this.tabPage1.TabIndex = 0;
      this.tabPage1.Text = "Basic";
      this.groupBox8.Controls.Add((Control) this.CbRvRGrade1);
      this.groupBox8.Controls.Add((Control) this.CbRvRGrade);
      this.groupBox8.Controls.Add((Control) this.CbRvrType);
      this.groupBox8.Controls.Add((Control) this.textBox27);
      this.groupBox8.Controls.Add((Control) this.textBox26);
      this.groupBox8.Controls.Add((Control) this.label9);
      this.groupBox8.Controls.Add((Control) this.label8);
      this.groupBox8.Location = new Point(485, 427);
      this.groupBox8.Name = "groupBox8";
      this.groupBox8.Size = new Size(260, 94);
      this.groupBox8.TabIndex = 102;
      this.groupBox8.TabStop = false;
      this.groupBox8.Text = "RvR Type";
      this.CbRvRGrade1.FormattingEnabled = true;
      this.CbRvRGrade1.Location = new Point(81, 57);
      this.CbRvRGrade1.Name = "CbRvRGrade1";
      this.CbRvRGrade1.Size = new Size(102, 21);
      this.CbRvRGrade1.TabIndex = 240;
      this.CbRvRGrade1.SelectedIndexChanged += new EventHandler(this.CbRvRGrade1_SelectedIndexChanged);
      this.CbRvRGrade1.SelectionChangeCommitted += new EventHandler(this.CbRvRGrade1_SelectionChangeCommitted);
      this.CbRvRGrade.FormattingEnabled = true;
      this.CbRvRGrade.Location = new Point(81, 57);
      this.CbRvRGrade.Name = "CbRvRGrade";
      this.CbRvRGrade.Size = new Size(102, 21);
      this.CbRvRGrade.TabIndex = 239;
      this.CbRvRGrade.SelectedIndexChanged += new EventHandler(this.CbRvRGrade_SelectedIndexChanged);
      this.CbRvrType.FormattingEnabled = true;
      this.CbRvrType.Location = new Point(81, 29);
      this.CbRvrType.Name = "CbRvrType";
      this.CbRvrType.Size = new Size(102, 21);
      this.CbRvrType.TabIndex = 238;
      this.CbRvrType.SelectedIndexChanged += new EventHandler(this.CbRvrType_SelectedIndexChanged);
      this.CbRvrType.SelectionChangeCommitted += new EventHandler(this.CbRvrType_SelectionChangeCommitted);
      this.textBox27.BorderStyle = BorderStyle.FixedSingle;
      this.textBox27.Location = new Point(198, 59);
      this.textBox27.Name = "textBox27";
      this.textBox27.Size = new Size(57, 20);
      this.textBox27.TabIndex = 237;
      this.textBox27.KeyPress += new KeyPressEventHandler(this.textBox27_KeyPress);
      this.textBox26.BorderStyle = BorderStyle.FixedSingle;
      this.textBox26.Location = new Point(198, 29);
      this.textBox26.Name = "textBox26";
      this.textBox26.Size = new Size(57, 20);
      this.textBox26.TabIndex = 236;
      this.textBox26.KeyPress += new KeyPressEventHandler(this.textBox26_KeyPress);
      this.label9.AutoSize = true;
      this.label9.Location = new Point(8, 60);
      this.label9.Name = "label9";
      this.label9.Size = new Size(64, 13);
      this.label9.TabIndex = 235;
      this.label9.Text = "RvR Grade:";
      this.label8.AutoSize = true;
      this.label8.Location = new Point(8, 32);
      this.label8.Name = "label8";
      this.label8.Size = new Size(59, 13);
      this.label8.TabIndex = 234;
      this.label8.Text = "RvR Type:";
      this.label109.AutoSize = true;
      this.label109.Location = new Point(691, 180);
      this.label109.Name = "label109";
      this.label109.Size = new Size(24, 13);
      this.label109.TabIndex = 101;
      this.label109.Text = "Job";
      this.label109.Visible = false;
      this.textBox15.Location = new Point(631, 177);
      this.textBox15.Name = "textBox15";
      this.textBox15.Size = new Size(50, 20);
      this.textBox15.TabIndex = 100;
      this.textBox15.Visible = false;
      this.label108.AutoSize = true;
      this.label108.Location = new Point(692, 156);
      this.label108.Name = "label108";
      this.label108.Size = new Size(39, 13);
      this.label108.TabIndex = 99;
      this.label108.Text = "QType";
      this.label108.Visible = false;
      this.label107.AutoSize = true;
      this.label107.Location = new Point(692, 79);
      this.label107.Name = "label107";
      this.label107.Size = new Size(37, 13);
      this.label107.TabIndex = 98;
      this.label107.Text = "SFrom";
      this.label107.Visible = false;
      this.label106.AutoSize = true;
      this.label106.Location = new Point(692, 130);
      this.label106.Name = "label106";
      this.label106.Size = new Size(28, 13);
      this.label106.TabIndex = 97;
      this.label106.Text = "Map";
      this.label106.Visible = false;
      this.label105.AutoSize = true;
      this.label105.Location = new Point(692, 104);
      this.label105.Name = "label105";
      this.label105.Size = new Size(28, 13);
      this.label105.TabIndex = 96;
      this.label105.Text = "Map";
      this.label105.Visible = false;
      this.textBox98.Location = new Point(631, 153);
      this.textBox98.Name = "textBox98";
      this.textBox98.Size = new Size(50, 20);
      this.textBox98.TabIndex = 95;
      this.textBox98.Visible = false;
      this.textBox11.Location = new Point(631, (int) sbyte.MaxValue);
      this.textBox11.Name = "textBox11";
      this.textBox11.Size = new Size(50, 20);
      this.textBox11.TabIndex = 94;
      this.textBox11.Visible = false;
      this.textBox9.Location = new Point(631, 101);
      this.textBox9.Name = "textBox9";
      this.textBox9.Size = new Size(50, 20);
      this.textBox9.TabIndex = 93;
      this.textBox9.Visible = false;
      this.textBox7.Location = new Point(631, 76);
      this.textBox7.Name = "textBox7";
      this.textBox7.Size = new Size(50, 20);
      this.textBox7.TabIndex = 92;
      this.textBox7.Visible = false;
      this.textBox4.Location = new Point(701, 41);
      this.textBox4.Name = "textBox4";
      this.textBox4.Size = new Size(50, 20);
      this.textBox4.TabIndex = 91;
      this.textBox4.Visible = false;
      this.textBox3.Location = new Point(701, 10);
      this.textBox3.Name = "textBox3";
      this.textBox3.Size = new Size(50, 20);
      this.textBox3.TabIndex = 90;
      this.textBox3.Visible = false;
      this.groupBox11.Controls.Add((Control) this.PbEndNPCItem);
      this.groupBox11.Controls.Add((Control) this.PbStartItemNPC);
      this.groupBox11.Controls.Add((Control) this.label118);
      this.groupBox11.Controls.Add((Control) this.label117);
      this.groupBox11.Controls.Add((Control) this.TbEndNpcName);
      this.groupBox11.Controls.Add((Control) this.TbStartNpcName);
      this.groupBox11.Controls.Add((Control) this.button6);
      this.groupBox11.Controls.Add((Control) this.button5);
      this.groupBox11.Controls.Add((Control) this.comboBox22);
      this.groupBox11.Controls.Add((Control) this.comboBox21);
      this.groupBox11.Controls.Add((Control) this.label12);
      this.groupBox11.Controls.Add((Control) this.comboBox5);
      this.groupBox11.Controls.Add((Control) this.label59);
      this.groupBox11.Controls.Add((Control) this.label47);
      this.groupBox11.Controls.Add((Control) this.textBox10);
      this.groupBox11.Controls.Add((Control) this.label10);
      this.groupBox11.Controls.Add((Control) this.label11);
      this.groupBox11.Controls.Add((Control) this.textBox8);
      this.groupBox11.Controls.Add((Control) this.textBox6);
      this.groupBox11.Controls.Add((Control) this.label46);
      this.groupBox11.Location = new Point(338, 242);
      this.groupBox11.Name = "groupBox11";
      this.groupBox11.Size = new Size(407, 175);
      this.groupBox11.TabIndex = 87;
      this.groupBox11.TabStop = false;
      this.groupBox11.Text = "Start and Finish Quest";
      this.PbEndNPCItem.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbEndNPCItem.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbEndNPCItem.Location = new Point(136, 118);
      this.PbEndNPCItem.Name = "PbEndNPCItem";
      this.PbEndNPCItem.Size = new Size(22, 22);
      this.PbEndNPCItem.TabIndex = 117;
      this.PbEndNPCItem.TabStop = false;
      this.PbEndNPCItem.Click += new EventHandler(this.PbEndNPCItem_Click);
      this.PbStartItemNPC.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbStartItemNPC.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbStartItemNPC.Location = new Point(136, 73);
      this.PbStartItemNPC.Name = "PbStartItemNPC";
      this.PbStartItemNPC.Size = new Size(22, 22);
      this.PbStartItemNPC.TabIndex = 116;
      this.PbStartItemNPC.TabStop = false;
      this.PbStartItemNPC.Click += new EventHandler(this.PbStartItemNPC_Click);
      this.label118.AutoSize = true;
      this.label118.Location = new Point(6, 147);
      this.label118.Name = "label118";
      this.label118.Size = new Size(85, 13);
      this.label118.TabIndex = 109;
      this.label118.Text = "End NPC Name:";
      this.label117.AutoSize = true;
      this.label117.Location = new Point(6, 102);
      this.label117.Name = "label117";
      this.label117.Size = new Size(88, 13);
      this.label117.TabIndex = 108;
      this.label117.Text = "Start NPC Name:";
      this.TbEndNpcName.BackColor = SystemColors.Menu;
      this.TbEndNpcName.BorderStyle = BorderStyle.FixedSingle;
      this.TbEndNpcName.Font = new Font("Microsoft Sans Serif", 8.25f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.TbEndNpcName.ForeColor = Color.LimeGreen;
      this.TbEndNpcName.Location = new Point(94, 144);
      this.TbEndNpcName.Name = "TbEndNpcName";
      this.TbEndNpcName.ReadOnly = true;
      this.TbEndNpcName.Size = new Size(195, 20);
      this.TbEndNpcName.TabIndex = 107;
      this.TbStartNpcName.BackColor = SystemColors.Menu;
      this.TbStartNpcName.BorderStyle = BorderStyle.FixedSingle;
      this.TbStartNpcName.Font = new Font("Microsoft Sans Serif", 8.25f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.TbStartNpcName.ForeColor = Color.LimeGreen;
      this.TbStartNpcName.Location = new Point(95, 98);
      this.TbStartNpcName.Name = "TbStartNpcName";
      this.TbStartNpcName.ReadOnly = true;
      this.TbStartNpcName.Size = new Size(195, 20);
      this.TbStartNpcName.TabIndex = 106;
      this.button6.Location = new Point(376, 120);
      this.button6.Name = "button6";
      this.button6.Size = new Size(27, 23);
      this.button6.TabIndex = 54;
      this.button6.Text = "?";
      this.button6.UseVisualStyleBackColor = true;
      this.button6.Click += new EventHandler(this.button6_Click);
      this.button5.Location = new Point(376, 71);
      this.button5.Name = "button5";
      this.button5.Size = new Size(27, 23);
      this.button5.TabIndex = 53;
      this.button5.Text = "?";
      this.button5.UseVisualStyleBackColor = true;
      this.button5.Click += new EventHandler(this.button5_Click);
      this.comboBox22.FlatStyle = FlatStyle.Popup;
      this.comboBox22.FormattingEnabled = true;
      this.comboBox22.Items.AddRange(new object[47]
      {
        (object) "0 - Juno",
        (object) "1 - Belfist",
        (object) "2 - Dungeon",
        (object) "3 - Dungeon 2",
        (object) "4 - Dratan",
        (object) "5 - Single Dungeon 2",
        (object) "6 - Start Map",
        (object) "7 - Merac",
        (object) "8 - Guild Hall",
        (object) "9 - Dungeon 3",
        (object) "10 - Single Dungeon 3",
        (object) "11 - Single Dungeon 4",
        (object) "12 - P Dungeon 1",
        (object) "13 - Dungeon 3 PVP",
        (object) "14 - Room OX",
        (object) "15 - Eghea",
        (object) "16 - Eghea PK",
        (object) "17 - Lust Turm 1-7",
        (object) "18 - Lust Turm 8",
        (object) "19 - Lust Turm 9",
        (object) "20 - Lust Turm 10",
        (object) "21 - Tomb",
        (object) "22 - Monster Combo",
        (object) "23 - Strayana",
        (object) "24 - PK Turment",
        (object) "25 - Cube",
        (object) "26 - Dragsaal",
        (object) "27 - Cave",
        (object) "28 - Cave",
        (object) "29 - Kristall Mine",
        (object) "30 - Mystische Schlucht ",
        (object) "31 - Eghea Cave",
        (object) "32 - MoonShine",
        (object) "33 - Chapel 1",
        (object) "34 - Chapel 2",
        (object) "35 - Chapel 3",
        (object) "36 - Akan Temple",
        (object) "37 - Triva Canyon",
        (object) "38 - Royal Rumble PK",
        (object) "39 - Tarian",
        (object) "40 -  Bloodymir",
        (object) "41 - Tarian Dungeon",
        (object) "42 - Alber",
        (object) "43 - Berusium",
        (object) "44 - Aden",
        (object) "45 - SereneLand",
        (object) "46 - Extreme Streiana"
      });
      this.comboBox22.Location = new Point(230, 120);
      this.comboBox22.Name = "comboBox22";
      this.comboBox22.Size = new Size(140, 21);
      this.comboBox22.TabIndex = 52;
      this.comboBox22.SelectedIndexChanged += new EventHandler(this.comboBox22_SelectedIndexChanged);
      this.comboBox22.SelectionChangeCommitted += new EventHandler(this.comboBox22_SelectionChangeCommitted);
      this.comboBox21.FlatStyle = FlatStyle.Popup;
      this.comboBox21.FormattingEnabled = true;
      this.comboBox21.Items.AddRange(new object[47]
      {
        (object) "0 - Juno",
        (object) "1 - Belfist",
        (object) "2 - Dungeon",
        (object) "3 - Dungeon 2",
        (object) "4 - Dratan",
        (object) "5 - Single Dungeon 2",
        (object) "6 - Start Map",
        (object) "7 - Merac",
        (object) "8 - Guild Hall",
        (object) "9 - Dungeon 3",
        (object) "10 - Single Dungeon 3",
        (object) "11 - Single Dungeon 4",
        (object) "12 - P Dungeon 1",
        (object) "13 - Dungeon 3 PVP",
        (object) "14 - Room OX",
        (object) "15 - Eghea",
        (object) "16 - Eghea PK",
        (object) "17 - Lust Turm 1-7",
        (object) "18 - Lust Turm 8",
        (object) "19 - Lust Turm 9",
        (object) "20 - Lust Turm 10",
        (object) "21 - Tomb",
        (object) "22 - Monster Combo",
        (object) "23 - Strayana",
        (object) "24 - PK Turment",
        (object) "25 - Cube",
        (object) "26 - Dragsaal",
        (object) "27 - Cave",
        (object) "28 - Cave",
        (object) "29 - Kristall Mine",
        (object) "30 - Mystische Schlucht ",
        (object) "31 - Eghea Cave",
        (object) "32 - MoonShine",
        (object) "33 - Chapel 1",
        (object) "34 - Chapel 2",
        (object) "35 - Chapel 3",
        (object) "36 - Akan Temple",
        (object) "37 - Triva Canyon",
        (object) "38 - Royal Rumble PK",
        (object) "39 - Tarian",
        (object) "40 -  Bloodymir",
        (object) "41 - Tarian Dungeon",
        (object) "42 - Alber",
        (object) "43 - Berusium",
        (object) "44 - Aden",
        (object) "45 - SereneLand",
        (object) "46 - Extreme Streiana"
      });
      this.comboBox21.Location = new Point(230, 71);
      this.comboBox21.Name = "comboBox21";
      this.comboBox21.Size = new Size(140, 21);
      this.comboBox21.TabIndex = 51;
      this.comboBox21.SelectedIndexChanged += new EventHandler(this.comboBox21_SelectedIndexChanged);
      this.comboBox21.SelectionChangeCommitted += new EventHandler(this.comboBox21_SelectionChangeCommitted);
      this.label12.AutoSize = true;
      this.label12.Location = new Point(164, 123);
      this.label12.Name = "label12";
      this.label12.Size = new Size(60, 13);
      this.label12.TabIndex = 17;
      this.label12.Text = "Zone NPC:";
      this.comboBox5.FlatStyle = FlatStyle.Popup;
      this.comboBox5.FormattingEnabled = true;
      this.comboBox5.Location = new Point(70, 29);
      this.comboBox5.Name = "comboBox5";
      this.comboBox5.Size = new Size(64, 21);
      this.comboBox5.TabIndex = 36;
      this.comboBox5.SelectedIndexChanged += new EventHandler(this.comboBox5_SelectedIndexChanged);
      this.comboBox5.SelectionChangeCommitted += new EventHandler(this.comboBox5_SelectionChangeCommitted);
      this.label59.AutoSize = true;
      this.label59.Location = new Point(164, 75);
      this.label59.Name = "label59";
      this.label59.Size = new Size(60, 13);
      this.label59.TabIndex = 50;
      this.label59.Text = "Zone NPC:";
      this.label47.AutoSize = true;
      this.label47.Location = new Point(6, 34);
      this.label47.Name = "label47";
      this.label47.Size = new Size(58, 13);
      this.label47.TabIndex = 35;
      this.label47.Text = "Start From:";
      this.textBox10.BorderStyle = BorderStyle.FixedSingle;
      this.textBox10.Location = new Point(70, 119);
      this.textBox10.Name = "textBox10";
      this.textBox10.Size = new Size(64, 20);
      this.textBox10.TabIndex = 14;
      this.textBox10.KeyPress += new KeyPressEventHandler(this.textBox10_KeyPress);
      this.label10.AutoSize = true;
      this.label10.Location = new Point(146, 34);
      this.label10.Name = "label10";
      this.label10.Size = new Size(81, 13);
      this.label10.TabIndex = 17;
      this.label10.Text = "Need Quest ID:";
      this.label11.AutoSize = true;
      this.label11.Location = new Point(6, 123);
      this.label11.Name = "label11";
      this.label11.Size = new Size(54, 13);
      this.label11.TabIndex = 15;
      this.label11.Text = "End NPC:";
      this.textBox8.BorderStyle = BorderStyle.FixedSingle;
      this.textBox8.Location = new Point(70, 73);
      this.textBox8.Name = "textBox8";
      this.textBox8.Size = new Size(64, 20);
      this.textBox8.TabIndex = 14;
      this.textBox8.KeyPress += new KeyPressEventHandler(this.textBox8_KeyPress);
      this.textBox6.BorderStyle = BorderStyle.FixedSingle;
      this.textBox6.Location = new Point(233, 29);
      this.textBox6.Name = "textBox6";
      this.textBox6.Size = new Size(62, 20);
      this.textBox6.TabIndex = 6;
      this.textBox6.KeyPress += new KeyPressEventHandler(this.textBox6_KeyPress);
      this.label46.AutoSize = true;
      this.label46.Location = new Point(6, 75);
      this.label46.Name = "label46";
      this.label46.Size = new Size(57, 13);
      this.label46.TabIndex = 35;
      this.label46.Text = "Start NPC:";
      this.groupBox10.Controls.Add((Control) this.comboBox4);
      this.groupBox10.Controls.Add((Control) this.label98);
      this.groupBox10.Location = new Point(338, 196);
      this.groupBox10.Name = "groupBox10";
      this.groupBox10.Size = new Size(287, 40);
      this.groupBox10.TabIndex = 86;
      this.groupBox10.TabStop = false;
      this.comboBox4.FlatStyle = FlatStyle.Popup;
      this.comboBox4.FormattingEnabled = true;
      this.comboBox4.Location = new Point(84, 13);
      this.comboBox4.Name = "comboBox4";
      this.comboBox4.Size = new Size(189, 21);
      this.comboBox4.TabIndex = 1;
      this.comboBox4.SelectedIndexChanged += new EventHandler(this.comboBox4_SelectedIndexChanged);
      this.comboBox4.SelectionChangeCommitted += new EventHandler(this.comboBox4_SelectionChangeCommitted);
      this.label98.AutoSize = true;
      this.label98.Location = new Point(13, 16);
      this.label98.Name = "label98";
      this.label98.Size = new Size(65, 13);
      this.label98.TabIndex = 0;
      this.label98.Text = "Quest Type:";
      this.groupBox9.Controls.Add((Control) this.comboBox3);
      this.groupBox9.Controls.Add((Control) this.textBox12);
      this.groupBox9.Controls.Add((Control) this.label14);
      this.groupBox9.Controls.Add((Control) this.label52);
      this.groupBox9.Controls.Add((Control) this.textBox14);
      this.groupBox9.Controls.Add((Control) this.textBox13);
      this.groupBox9.Controls.Add((Control) this.label54);
      this.groupBox9.Controls.Add((Control) this.label13);
      this.groupBox9.Location = new Point(338, 67);
      this.groupBox9.Name = "groupBox9";
      this.groupBox9.Size = new Size(287, 130);
      this.groupBox9.TabIndex = 85;
      this.groupBox9.TabStop = false;
      this.groupBox9.Text = "Character Stuff";
      this.comboBox3.FlatStyle = FlatStyle.Popup;
      this.comboBox3.FormattingEnabled = true;
      this.comboBox3.Location = new Point(66, 98);
      this.comboBox3.Name = "comboBox3";
      this.comboBox3.Size = new Size(121, 21);
      this.comboBox3.TabIndex = 62;
      this.comboBox3.SelectedIndexChanged += new EventHandler(this.comboBox3_SelectedIndexChanged);
      this.comboBox3.SelectionChangeCommitted += new EventHandler(this.comboBox3_SelectionChangeCommitted);
      this.label14.AutoSize = true;
      this.label14.Location = new Point(27, 102);
      this.label14.Name = "label14";
      this.label14.Size = new Size(27, 13);
      this.label14.TabIndex = 60;
      this.label14.Text = "Job:";
      this.label52.AutoSize = true;
      this.label52.Location = new Point(6, 34);
      this.label52.Name = "label52";
      this.label52.Size = new Size(56, 13);
      this.label52.TabIndex = 45;
      this.label52.Text = "Min Level:";
      this.textBox14.BorderStyle = BorderStyle.FixedSingle;
      this.textBox14.Location = new Point(211, 32);
      this.textBox14.Name = "textBox14";
      this.textBox14.Size = new Size(62, 20);
      this.textBox14.TabIndex = 59;
      this.textBox14.KeyPress += new KeyPressEventHandler(this.textBox14_KeyPress);
      this.textBox13.BorderStyle = BorderStyle.FixedSingle;
      this.textBox13.Location = new Point(66, 32);
      this.textBox13.Name = "textBox13";
      this.textBox13.Size = new Size(62, 20);
      this.textBox13.TabIndex = 18;
      this.textBox13.KeyPress += new KeyPressEventHandler(this.textBox13_KeyPress);
      this.label54.AutoSize = true;
      this.label54.Location = new Point(146, 34);
      this.label54.Name = "label54";
      this.label54.Size = new Size(59, 13);
      this.label54.TabIndex = 49;
      this.label54.Text = "Max Level:";
      this.label13.AutoSize = true;
      this.label13.Location = new Point(27, 69);
      this.label13.Name = "label13";
      this.label13.Size = new Size(31, 13);
      this.label13.TabIndex = 19;
      this.label13.Text = "EXP:";
      this.comboBox2.FlatStyle = FlatStyle.Popup;
      this.comboBox2.FormattingEnabled = true;
      this.comboBox2.Location = new Point(388, 40);
      this.comboBox2.Name = "comboBox2";
      this.comboBox2.Size = new Size(307, 21);
      this.comboBox2.TabIndex = 84;
      this.comboBox2.SelectedIndexChanged += new EventHandler(this.comboBox2_SelectedIndexChanged);
      this.comboBox2.SelectionChangeCommitted += new EventHandler(this.comboBox2_SelectionChangeCommitted);
      this.comboBox1.FlatStyle = FlatStyle.Popup;
      this.comboBox1.FormattingEnabled = true;
      this.comboBox1.Location = new Point(388, 10);
      this.comboBox1.Name = "comboBox1";
      this.comboBox1.Size = new Size(307, 21);
      this.comboBox1.TabIndex = 83;
      this.comboBox1.SelectedIndexChanged += new EventHandler(this.comboBox1_SelectedIndexChanged);
      this.comboBox1.SelectionChangeCommitted += new EventHandler(this.comboBox1_SelectionChangeCommitted);
      this.groupBox4.Controls.Add((Control) this.PbItemNeed5);
      this.groupBox4.Controls.Add((Control) this.PbItemNeed4);
      this.groupBox4.Controls.Add((Control) this.PbItemNeed3);
      this.groupBox4.Controls.Add((Control) this.PbItemNeed2);
      this.groupBox4.Controls.Add((Control) this.PbItemNeed1);
      this.groupBox4.Controls.Add((Control) this.TbNeedName5);
      this.groupBox4.Controls.Add((Control) this.TbNeedName4);
      this.groupBox4.Controls.Add((Control) this.TbNeedName3);
      this.groupBox4.Controls.Add((Control) this.TbNeedName2);
      this.groupBox4.Controls.Add((Control) this.TbNeedName1);
      this.groupBox4.Controls.Add((Control) this.label4);
      this.groupBox4.Controls.Add((Control) this.textBox25);
      this.groupBox4.Controls.Add((Control) this.textBox24);
      this.groupBox4.Controls.Add((Control) this.textBox21);
      this.groupBox4.Controls.Add((Control) this.textBox19);
      this.groupBox4.Controls.Add((Control) this.label85);
      this.groupBox4.Controls.Add((Control) this.textBox17);
      this.groupBox4.Controls.Add((Control) this.label93);
      this.groupBox4.Controls.Add((Control) this.label92);
      this.groupBox4.Controls.Add((Control) this.textBox16);
      this.groupBox4.Controls.Add((Control) this.textBox20);
      this.groupBox4.Controls.Add((Control) this.label91);
      this.groupBox4.Controls.Add((Control) this.label18);
      this.groupBox4.Controls.Add((Control) this.textBox23);
      this.groupBox4.Controls.Add((Control) this.label22);
      this.groupBox4.Controls.Add((Control) this.textBox18);
      this.groupBox4.Controls.Add((Control) this.textBox22);
      this.groupBox4.Controls.Add((Control) this.label15);
      this.groupBox4.Controls.Add((Control) this.label23);
      this.groupBox4.Controls.Add((Control) this.label16);
      this.groupBox4.Location = new Point(2, 427);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Size = new Size(480, 179);
      this.groupBox4.TabIndex = 77;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "Need Items";
      this.PbItemNeed5.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbItemNeed5.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbItemNeed5.Location = new Point(309, 149);
      this.PbItemNeed5.Name = "PbItemNeed5";
      this.PbItemNeed5.Size = new Size(22, 22);
      this.PbItemNeed5.TabIndex = 115;
      this.PbItemNeed5.TabStop = false;
      this.PbItemNeed5.Click += new EventHandler(this.PbItemNeed5_Click);
      this.PbItemNeed4.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbItemNeed4.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbItemNeed4.Location = new Point(308, 121);
      this.PbItemNeed4.Name = "PbItemNeed4";
      this.PbItemNeed4.Size = new Size(22, 22);
      this.PbItemNeed4.TabIndex = 114;
      this.PbItemNeed4.TabStop = false;
      this.PbItemNeed4.Click += new EventHandler(this.PbItemNeed4_Click);
      this.PbItemNeed3.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbItemNeed3.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbItemNeed3.Location = new Point(309, 91);
      this.PbItemNeed3.Name = "PbItemNeed3";
      this.PbItemNeed3.Size = new Size(22, 22);
      this.PbItemNeed3.TabIndex = 113;
      this.PbItemNeed3.TabStop = false;
      this.PbItemNeed3.Click += new EventHandler(this.PbItemNeed3_Click);
      this.PbItemNeed2.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbItemNeed2.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbItemNeed2.Location = new Point(308, 60);
      this.PbItemNeed2.Name = "PbItemNeed2";
      this.PbItemNeed2.Size = new Size(22, 22);
      this.PbItemNeed2.TabIndex = 112;
      this.PbItemNeed2.TabStop = false;
      this.PbItemNeed2.Click += new EventHandler(this.PbItemNeed2_Click);
      this.PbItemNeed1.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbItemNeed1.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbItemNeed1.Location = new Point(308, 30);
      this.PbItemNeed1.Name = "PbItemNeed1";
      this.PbItemNeed1.Size = new Size(22, 22);
      this.PbItemNeed1.TabIndex = 111;
      this.PbItemNeed1.TabStop = false;
      this.PbItemNeed1.Click += new EventHandler(this.PbItemNeed1_Click);
      this.TbNeedName5.BackColor = SystemColors.Menu;
      this.TbNeedName5.BorderStyle = BorderStyle.FixedSingle;
      this.TbNeedName5.ForeColor = Color.RoyalBlue;
      this.TbNeedName5.Location = new Point(119, 151);
      this.TbNeedName5.Name = "TbNeedName5";
      this.TbNeedName5.ReadOnly = true;
      this.TbNeedName5.Size = new Size(185, 20);
      this.TbNeedName5.TabIndex = 91;
      this.TbNeedName4.BackColor = SystemColors.Menu;
      this.TbNeedName4.BorderStyle = BorderStyle.FixedSingle;
      this.TbNeedName4.ForeColor = Color.RoyalBlue;
      this.TbNeedName4.Location = new Point(118, 121);
      this.TbNeedName4.Name = "TbNeedName4";
      this.TbNeedName4.ReadOnly = true;
      this.TbNeedName4.Size = new Size(185, 20);
      this.TbNeedName4.TabIndex = 90;
      this.TbNeedName3.BackColor = SystemColors.Menu;
      this.TbNeedName3.BorderStyle = BorderStyle.FixedSingle;
      this.TbNeedName3.ForeColor = Color.RoyalBlue;
      this.TbNeedName3.Location = new Point(118, 91);
      this.TbNeedName3.Name = "TbNeedName3";
      this.TbNeedName3.ReadOnly = true;
      this.TbNeedName3.Size = new Size(185, 20);
      this.TbNeedName3.TabIndex = 89;
      this.TbNeedName2.BackColor = SystemColors.Menu;
      this.TbNeedName2.BorderStyle = BorderStyle.FixedSingle;
      this.TbNeedName2.ForeColor = Color.RoyalBlue;
      this.TbNeedName2.Location = new Point(118, 60);
      this.TbNeedName2.Name = "TbNeedName2";
      this.TbNeedName2.ReadOnly = true;
      this.TbNeedName2.Size = new Size(185, 20);
      this.TbNeedName2.TabIndex = 88;
      this.TbNeedName1.BackColor = SystemColors.Menu;
      this.TbNeedName1.BorderStyle = BorderStyle.FixedSingle;
      this.TbNeedName1.ForeColor = Color.RoyalBlue;
      this.TbNeedName1.Location = new Point(117, 30);
      this.TbNeedName1.Name = "TbNeedName1";
      this.TbNeedName1.ReadOnly = true;
      this.TbNeedName1.Size = new Size(185, 20);
      this.TbNeedName1.TabIndex = 87;
      this.label4.AutoSize = true;
      this.label4.Location = new Point(336, 151);
      this.label4.Name = "label4";
      this.label4.Size = new Size(75, 13);
      this.label4.TabIndex = 76;
      this.label4.Text = "Item Amount4:";
      this.textBox25.BorderStyle = BorderStyle.FixedSingle;
      this.textBox25.Location = new Point(418, 151);
      this.textBox25.Name = "textBox25";
      this.textBox25.Size = new Size(58, 20);
      this.textBox25.TabIndex = 80;
      this.textBox25.KeyPress += new KeyPressEventHandler(this.textBox25_KeyPress);
      this.textBox24.BorderStyle = BorderStyle.FixedSingle;
      this.textBox24.Location = new Point(418, 119);
      this.textBox24.Name = "textBox24";
      this.textBox24.Size = new Size(58, 20);
      this.textBox24.TabIndex = 75;
      this.textBox24.KeyPress += new KeyPressEventHandler(this.textBox24_KeyPress);
      this.textBox21.BorderStyle = BorderStyle.FixedSingle;
      this.textBox21.Location = new Point(418, 29);
      this.textBox21.Name = "textBox21";
      this.textBox21.Size = new Size(58, 20);
      this.textBox21.TabIndex = 72;
      this.textBox21.KeyPress += new KeyPressEventHandler(this.textBox21_KeyPress);
      this.textBox19.BorderStyle = BorderStyle.FixedSingle;
      this.textBox19.Location = new Point(50, 119);
      this.textBox19.Name = "textBox19";
      this.textBox19.Size = new Size(62, 20);
      this.textBox19.TabIndex = 68;
      this.textBox19.KeyPress += new KeyPressEventHandler(this.textBox19_KeyPress);
      this.label85.AutoSize = true;
      this.label85.Location = new Point(336, 34);
      this.label85.Name = "label85";
      this.label85.Size = new Size(75, 13);
      this.label85.TabIndex = 73;
      this.label85.Text = "Item Amount0:";
      this.textBox17.BorderStyle = BorderStyle.FixedSingle;
      this.textBox17.Location = new Point(50, 59);
      this.textBox17.Name = "textBox17";
      this.textBox17.Size = new Size(62, 20);
      this.textBox17.TabIndex = 65;
      this.textBox17.KeyPress += new KeyPressEventHandler(this.textBox17_KeyPress);
      this.label93.AutoSize = true;
      this.label93.Location = new Point(336, 63);
      this.label93.Name = "label93";
      this.label93.Size = new Size(75, 13);
      this.label93.TabIndex = 74;
      this.label93.Text = "Item Amount1:";
      this.label92.AutoSize = true;
      this.label92.Location = new Point(2, 123);
      this.label92.Name = "label92";
      this.label92.Size = new Size(44, 13);
      this.label92.TabIndex = 70;
      this.label92.Text = "Item ID:";
      this.textBox16.BorderStyle = BorderStyle.FixedSingle;
      this.textBox16.Location = new Point(50, 29);
      this.textBox16.Name = "textBox16";
      this.textBox16.Size = new Size(62, 20);
      this.textBox16.TabIndex = 63;
      this.textBox16.KeyPress += new KeyPressEventHandler(this.textBox16_KeyPress);
      this.textBox20.BorderStyle = BorderStyle.FixedSingle;
      this.textBox20.Location = new Point(50, 151);
      this.textBox20.Name = "textBox20";
      this.textBox20.Size = new Size(62, 20);
      this.textBox20.TabIndex = 71;
      this.textBox20.KeyPress += new KeyPressEventHandler(this.textBox20_KeyPress);
      this.label91.AutoSize = true;
      this.label91.Location = new Point(2, 63);
      this.label91.Name = "label91";
      this.label91.Size = new Size(44, 13);
      this.label91.TabIndex = 69;
      this.label91.Text = "Item ID:";
      this.label18.AutoSize = true;
      this.label18.Location = new Point(2, 151);
      this.label18.Name = "label18";
      this.label18.Size = new Size(44, 13);
      this.label18.TabIndex = 67;
      this.label18.Text = "Item ID:";
      this.textBox23.BorderStyle = BorderStyle.FixedSingle;
      this.textBox23.Location = new Point(418, 89);
      this.textBox23.Name = "textBox23";
      this.textBox23.Size = new Size(58, 20);
      this.textBox23.TabIndex = 40;
      this.textBox23.KeyPress += new KeyPressEventHandler(this.textBox23_KeyPress);
      this.label22.AutoSize = true;
      this.label22.Location = new Point(336, 93);
      this.label22.Name = "label22";
      this.label22.Size = new Size(75, 13);
      this.label22.TabIndex = 39;
      this.label22.Text = "Item Amount2:";
      this.textBox18.BorderStyle = BorderStyle.FixedSingle;
      this.textBox18.Location = new Point(50, 89);
      this.textBox18.Name = "textBox18";
      this.textBox18.Size = new Size(62, 20);
      this.textBox18.TabIndex = 66;
      this.textBox18.KeyPress += new KeyPressEventHandler(this.textBox18_KeyPress);
      this.textBox22.BorderStyle = BorderStyle.FixedSingle;
      this.textBox22.Location = new Point(418, 59);
      this.textBox22.Name = "textBox22";
      this.textBox22.Size = new Size(58, 20);
      this.textBox22.TabIndex = 38;
      this.textBox22.KeyPress += new KeyPressEventHandler(this.textBox22_KeyPress);
      this.label15.AutoSize = true;
      this.label15.Location = new Point(2, 34);
      this.label15.Name = "label15";
      this.label15.Size = new Size(44, 13);
      this.label15.TabIndex = 62;
      this.label15.Text = "Item ID:";
      this.label23.AutoSize = true;
      this.label23.Location = new Point(336, 123);
      this.label23.Name = "label23";
      this.label23.Size = new Size(75, 13);
      this.label23.TabIndex = 41;
      this.label23.Text = "Item Amount3:";
      this.label16.AutoSize = true;
      this.label16.Location = new Point(2, 93);
      this.label16.Name = "label16";
      this.label16.Size = new Size(44, 13);
      this.label16.TabIndex = 64;
      this.label16.Text = "Item ID:";
      this.groupBox1.Controls.Add((Control) this.cbEnabled);
      this.groupBox1.Controls.Add((Control) this.label112);
      this.groupBox1.Controls.Add((Control) this.label111);
      this.groupBox1.Controls.Add((Control) this.label110);
      this.groupBox1.Controls.Add((Control) this.richTextBox3);
      this.groupBox1.Controls.Add((Control) this.richTextBox2);
      this.groupBox1.Controls.Add((Control) this.richTextBox1);
      this.groupBox1.Controls.Add((Control) this.label104);
      this.groupBox1.Controls.Add((Control) this.label96);
      this.groupBox1.Controls.Add((Control) this.label95);
      this.groupBox1.Controls.Add((Control) this.textBox2);
      this.groupBox1.Controls.Add((Control) this.label6);
      this.groupBox1.Controls.Add((Control) this.label5);
      this.groupBox1.Controls.Add((Control) this.textBox1);
      this.groupBox1.Controls.Add((Control) this.label1);
      this.groupBox1.Controls.Add((Control) this.textBox5);
      this.groupBox1.Location = new Point(4, 2);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(328, 415);
      this.groupBox1.TabIndex = 54;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Basic";
      this.cbEnabled.AutoSize = true;
      this.cbEnabled.BackColor = Color.Chartreuse;
      this.cbEnabled.Location = new Point(102, 18);
      this.cbEnabled.Name = "cbEnabled";
      this.cbEnabled.Size = new Size(65, 17);
      this.cbEnabled.TabIndex = 84;
      this.cbEnabled.Text = "Enabled";
      this.cbEnabled.UseVisualStyleBackColor = false;
      this.cbEnabled.CheckedChanged += new EventHandler(this.cbEnabled_CheckedChanged);
      this.label112.AutoSize = true;
      this.label112.Font = new Font("Microsoft Sans Serif", 9.75f, FontStyle.Bold, GraphicsUnit.Point, (byte) 0);
      this.label112.Location = new Point(7, 340);
      this.label112.Name = "label112";
      this.label112.Size = new Size(48, 16);
      this.label112.TabIndex = 83;
      this.label112.Text = "Desc:";
      this.label111.AutoSize = true;
      this.label111.Font = new Font("Microsoft Sans Serif", 9.75f, FontStyle.Bold, GraphicsUnit.Point, (byte) 0);
      this.label111.Location = new Point(7, 124);
      this.label111.Name = "label111";
      this.label111.Size = new Size(48, 16);
      this.label111.TabIndex = 82;
      this.label111.Text = "Desc:";
      this.label110.AutoSize = true;
      this.label110.Font = new Font("Microsoft Sans Serif", 9.75f, FontStyle.Bold, GraphicsUnit.Point, (byte) 0);
      this.label110.Location = new Point(3, 230);
      this.label110.Name = "label110";
      this.label110.Size = new Size(48, 16);
      this.label110.TabIndex = 81;
      this.label110.Text = "Desc:";
      this.richTextBox3.Location = new Point(58, 297);
      this.richTextBox3.Name = "richTextBox3";
      this.richTextBox3.ScrollBars = RichTextBoxScrollBars.ForcedVertical;
      this.richTextBox3.Size = new Size(264, 101);
      this.richTextBox3.TabIndex = 80;
      this.richTextBox3.Text = "";
      this.richTextBox3.KeyPress += new KeyPressEventHandler(this.richTextBox3_KeyPress);
      this.richTextBox2.Location = new Point(58, 190);
      this.richTextBox2.Name = "richTextBox2";
      this.richTextBox2.ScrollBars = RichTextBoxScrollBars.ForcedVertical;
      this.richTextBox2.Size = new Size(264, 101);
      this.richTextBox2.TabIndex = 79;
      this.richTextBox2.Text = "";
      this.richTextBox2.KeyPress += new KeyPressEventHandler(this.richTextBox2_KeyPress);
      this.richTextBox1.BorderStyle = BorderStyle.FixedSingle;
      this.richTextBox1.DetectUrls = false;
      this.richTextBox1.Location = new Point(58, 83);
      this.richTextBox1.Name = "richTextBox1";
      this.richTextBox1.ScrollBars = RichTextBoxScrollBars.ForcedVertical;
      this.richTextBox1.Size = new Size(264, 101);
      this.richTextBox1.TabIndex = 78;
      this.richTextBox1.Text = "";
      this.richTextBox1.KeyPress += new KeyPressEventHandler(this.richTextBox1_KeyPress);
      this.label104.AutoSize = true;
      this.label104.Location = new Point(11, 18);
      this.label104.Name = "label104";
      this.label104.Size = new Size(43, 13);
      this.label104.TabIndex = 42;
      this.label104.Text = "Enable:";
      this.label96.AutoSize = true;
      this.label96.Font = new Font("Microsoft Sans Serif", 9.75f, FontStyle.Bold, GraphicsUnit.Point, (byte) 0);
      this.label96.Location = new Point(5, 314);
      this.label96.Name = "label96";
      this.label96.Size = new Size(48, 16);
      this.label96.TabIndex = 41;
      this.label96.Text = "Cond:";
      this.label95.AutoSize = true;
      this.label95.Font = new Font("Microsoft Sans Serif", 9.75f, FontStyle.Bold, GraphicsUnit.Point, (byte) 0);
      this.label95.Location = new Point(-3, 207);
      this.label95.Name = "label95";
      this.label95.Size = new Size(65, 16);
      this.label95.TabIndex = 40;
      this.label95.Text = "Reward:";
      this.textBox2.BackColor = Color.White;
      this.textBox2.BorderStyle = BorderStyle.FixedSingle;
      this.textBox2.Location = new Point(58, 48);
      this.textBox2.Name = "textBox2";
      this.textBox2.Size = new Size(253, 20);
      this.textBox2.TabIndex = 2;
      this.textBox2.KeyDown += new KeyEventHandler(this.textBox2_KeyDown);
      this.label6.AutoSize = true;
      this.label6.Font = new Font("Microsoft Sans Serif", 9.75f, FontStyle.Bold, GraphicsUnit.Point, (byte) 0);
      this.label6.Location = new Point(6, 102);
      this.label6.Name = "label6";
      this.label6.Size = new Size(44, 16);
      this.label6.TabIndex = 12;
      this.label6.Text = "Start:";
      this.label5.AutoSize = true;
      this.label5.Location = new Point(11, 50);
      this.label5.Name = "label5";
      this.label5.Size = new Size(38, 13);
      this.label5.TabIndex = 11;
      this.label5.Text = "Name:";
      this.textBox1.BorderStyle = BorderStyle.FixedSingle;
      this.textBox1.Location = new Point(260, 19);
      this.textBox1.Name = "textBox1";
      this.textBox1.ReadOnly = true;
      this.textBox1.Size = new Size(51, 20);
      this.textBox1.TabIndex = 1;
      this.label1.AutoSize = true;
      this.label1.Location = new Point(213, 21);
      this.label1.Name = "label1";
      this.label1.Size = new Size(36, 13);
      this.label1.TabIndex = 7;
      this.label1.Text = "Index:";
      this.textBox5.BorderStyle = BorderStyle.FixedSingle;
      this.textBox5.Location = new Point(60, 16);
      this.textBox5.Name = "textBox5";
      this.textBox5.Size = new Size(35, 20);
      this.textBox5.TabIndex = 4;
      this.textBox5.TextChanged += new EventHandler(this.textBox5_TextChanged);
      this.textBox5.KeyPress += new KeyPressEventHandler(this.textBox5_KeyPress);
      this.label3.AutoSize = true;
      this.label3.Location = new Point(342, 43);
      this.label3.Name = "label3";
      this.label3.Size = new Size(40, 13);
      this.label3.TabIndex = 9;
      this.label3.Text = "Type2:";
      this.label2.AutoSize = true;
      this.label2.Location = new Point(342, 13);
      this.label2.Name = "label2";
      this.label2.Size = new Size(40, 13);
      this.label2.TabIndex = 8;
      this.label2.Text = "Type1:";
      this.tabPage3.Controls.Add((Control) this.tabControl2);
      this.tabPage3.Location = new Point(4, 22);
      this.tabPage3.Name = "tabPage3";
      this.tabPage3.Size = new Size(765, 610);
      this.tabPage3.TabIndex = 2;
      this.tabPage3.Text = "Condition";
      this.tabControl2.Appearance = TabAppearance.Buttons;
      this.tabControl2.Controls.Add((Control) this.tabPage2);
      this.tabControl2.Controls.Add((Control) this.tabPage4);
      this.tabControl2.Controls.Add((Control) this.tabPage5);
      this.tabControl2.Location = new Point(3, 3);
      this.tabControl2.Name = "tabControl2";
      this.tabControl2.SelectedIndex = 0;
      this.tabControl2.Size = new Size(742, 362);
      this.tabControl2.SizeMode = TabSizeMode.Fixed;
      this.tabControl2.TabIndex = 47;
      this.tabPage2.Controls.Add((Control) this.TbObj1);
      this.tabPage2.Controls.Add((Control) this.PbCond1);
      this.tabPage2.Controls.Add((Control) this.textBox28);
      this.tabPage2.Controls.Add((Control) this.groupBox2);
      this.tabPage2.Controls.Add((Control) this.comboBox6);
      this.tabPage2.Controls.Add((Control) this.label17);
      this.tabPage2.Controls.Add((Control) this.textBox31);
      this.tabPage2.Controls.Add((Control) this.label25);
      this.tabPage2.Controls.Add((Control) this.textBox34);
      this.tabPage2.Controls.Add((Control) this.label28);
      this.tabPage2.Location = new Point(4, 25);
      this.tabPage2.Name = "tabPage2";
      this.tabPage2.Padding = new Padding(3);
      this.tabPage2.Size = new Size(734, 333);
      this.tabPage2.TabIndex = 0;
      this.tabPage2.Text = "Objetive 1";
      this.tabPage2.UseVisualStyleBackColor = true;
      this.TbObj1.BackColor = SystemColors.Menu;
      this.TbObj1.BorderStyle = BorderStyle.FixedSingle;
      this.TbObj1.Location = new Point(162, 47);
      this.TbObj1.Name = "TbObj1";
      this.TbObj1.ReadOnly = true;
      this.TbObj1.Size = new Size(195, 20);
      this.TbObj1.TabIndex = 87;
      this.PbCond1.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbCond1.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbCond1.Location = new Point(360, 47);
      this.PbCond1.Name = "PbCond1";
      this.PbCond1.Size = new Size(22, 22);
      this.PbCond1.TabIndex = 78;
      this.PbCond1.TabStop = false;
      this.PbCond1.Click += new EventHandler(this.PbCond1_Click);
      this.textBox28.Location = new Point(178, 13);
      this.textBox28.Name = "textBox28";
      this.textBox28.Size = new Size(62, 20);
      this.textBox28.TabIndex = 38;
      this.textBox28.Visible = false;
      this.groupBox2.Controls.Add((Control) this.TbObj1Npc3);
      this.groupBox2.Controls.Add((Control) this.PbObj1NpcID3);
      this.groupBox2.Controls.Add((Control) this.TbObj1Npc2);
      this.groupBox2.Controls.Add((Control) this.PbObj1NpcID2);
      this.groupBox2.Controls.Add((Control) this.TbObj1Npc1);
      this.groupBox2.Controls.Add((Control) this.PbObj1NpcID1);
      this.groupBox2.Controls.Add((Control) this.label116);
      this.groupBox2.Controls.Add((Control) this.label31);
      this.groupBox2.Controls.Add((Control) this.label29);
      this.groupBox2.Controls.Add((Control) this.label30);
      this.groupBox2.Controls.Add((Control) this.textBox37);
      this.groupBox2.Controls.Add((Control) this.textBox38);
      this.groupBox2.Controls.Add((Control) this.textBox39);
      this.groupBox2.Controls.Add((Control) this.textBox40);
      this.groupBox2.Controls.Add((Control) this.label34);
      this.groupBox2.Location = new Point(9, 87);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new Size(719, 158);
      this.groupBox2.TabIndex = 37;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "NPC Quest Item";
      this.TbObj1Npc3.BackColor = SystemColors.Menu;
      this.TbObj1Npc3.BorderStyle = BorderStyle.FixedSingle;
      this.TbObj1Npc3.ForeColor = Color.Red;
      this.TbObj1Npc3.Location = new Point(172, 82);
      this.TbObj1Npc3.Name = "TbObj1Npc3";
      this.TbObj1Npc3.ReadOnly = true;
      this.TbObj1Npc3.Size = new Size(195, 20);
      this.TbObj1Npc3.TabIndex = 109;
      this.PbObj1NpcID3.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbObj1NpcID3.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbObj1NpcID3.Location = new Point(370, 82);
      this.PbObj1NpcID3.Name = "PbObj1NpcID3";
      this.PbObj1NpcID3.Size = new Size(22, 22);
      this.PbObj1NpcID3.TabIndex = 108;
      this.PbObj1NpcID3.TabStop = false;
      this.PbObj1NpcID3.Click += new EventHandler(this.PbObj1NpcID3_Click);
      this.TbObj1Npc2.BackColor = SystemColors.Menu;
      this.TbObj1Npc2.BorderStyle = BorderStyle.FixedSingle;
      this.TbObj1Npc2.ForeColor = Color.Red;
      this.TbObj1Npc2.Location = new Point(172, 56);
      this.TbObj1Npc2.Name = "TbObj1Npc2";
      this.TbObj1Npc2.ReadOnly = true;
      this.TbObj1Npc2.Size = new Size(195, 20);
      this.TbObj1Npc2.TabIndex = 107;
      this.PbObj1NpcID2.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbObj1NpcID2.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbObj1NpcID2.Location = new Point(370, 56);
      this.PbObj1NpcID2.Name = "PbObj1NpcID2";
      this.PbObj1NpcID2.Size = new Size(22, 22);
      this.PbObj1NpcID2.TabIndex = 106;
      this.PbObj1NpcID2.TabStop = false;
      this.PbObj1NpcID2.Click += new EventHandler(this.PbObj1NpcID2_Click);
      this.TbObj1Npc1.BackColor = SystemColors.Menu;
      this.TbObj1Npc1.BorderStyle = BorderStyle.FixedSingle;
      this.TbObj1Npc1.ForeColor = Color.Red;
      this.TbObj1Npc1.Location = new Point(172, 30);
      this.TbObj1Npc1.Name = "TbObj1Npc1";
      this.TbObj1Npc1.ReadOnly = true;
      this.TbObj1Npc1.Size = new Size(195, 20);
      this.TbObj1Npc1.TabIndex = 105;
      this.PbObj1NpcID1.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbObj1NpcID1.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbObj1NpcID1.Location = new Point(370, 30);
      this.PbObj1NpcID1.Name = "PbObj1NpcID1";
      this.PbObj1NpcID1.Size = new Size(22, 22);
      this.PbObj1NpcID1.TabIndex = 104;
      this.PbObj1NpcID1.TabStop = false;
      this.PbObj1NpcID1.Click += new EventHandler(this.PbObj1NpcID1_Click);
      this.label116.AutoSize = true;
      this.label116.Font = new Font("Microsoft Sans Serif", 9.75f, FontStyle.Bold, GraphicsUnit.Point, (byte) 0);
      this.label116.Location = new Point(205, 117);
      this.label116.Name = "label116";
      this.label116.Size = new Size(105, 16);
      this.label116.TabIndex = 103;
      this.label116.Text = "10,000 = 100%";
      this.label31.AutoSize = true;
      this.label31.Location = new Point(14, 34);
      this.label31.Name = "label31";
      this.label31.Size = new Size(46, 13);
      this.label31.TabIndex = 22;
      this.label31.Text = "NPC ID:";
      this.label29.AutoSize = true;
      this.label29.Location = new Point(14, 85);
      this.label29.Name = "label29";
      this.label29.Size = new Size(46, 13);
      this.label29.TabIndex = 24;
      this.label29.Text = "NPC ID:";
      this.label30.AutoSize = true;
      this.label30.Location = new Point(14, 60);
      this.label30.Name = "label30";
      this.label30.Size = new Size(46, 13);
      this.label30.TabIndex = 23;
      this.label30.Text = "NPC ID:";
      this.textBox37.BorderStyle = BorderStyle.FixedSingle;
      this.textBox37.Location = new Point(66, 30);
      this.textBox37.Name = "textBox37";
      this.textBox37.Size = new Size(100, 20);
      this.textBox37.TabIndex = 20;
      this.textBox37.KeyPress += new KeyPressEventHandler(this.textBox37_KeyPress);
      this.textBox38.BorderStyle = BorderStyle.FixedSingle;
      this.textBox38.Location = new Point(66, 56);
      this.textBox38.Name = "textBox38";
      this.textBox38.Size = new Size(100, 20);
      this.textBox38.TabIndex = 19;
      this.textBox38.KeyPress += new KeyPressEventHandler(this.textBox38_KeyPress);
      this.textBox39.BorderStyle = BorderStyle.FixedSingle;
      this.textBox39.Location = new Point(66, 81);
      this.textBox39.Name = "textBox39";
      this.textBox39.Size = new Size(100, 20);
      this.textBox39.TabIndex = 36;
      this.textBox39.KeyPress += new KeyPressEventHandler(this.textBox39_KeyPress);
      this.textBox40.BorderStyle = BorderStyle.FixedSingle;
      this.textBox40.Location = new Point(99, 114);
      this.textBox40.Name = "textBox40";
      this.textBox40.Size = new Size(100, 20);
      this.textBox40.TabIndex = 32;
      this.textBox40.KeyPress += new KeyPressEventHandler(this.textBox40_KeyPress);
      this.label34.AutoSize = true;
      this.label34.Location = new Point(14, 117);
      this.label34.Name = "label34";
      this.label34.Size = new Size(79, 13);
      this.label34.TabIndex = 29;
      this.label34.Text = "Percent to Get:";
      this.comboBox6.FlatStyle = FlatStyle.Popup;
      this.comboBox6.FormattingEnabled = true;
      this.comboBox6.Location = new Point(46, 12);
      this.comboBox6.Name = "comboBox6";
      this.comboBox6.Size = new Size(121, 21);
      this.comboBox6.TabIndex = 4;
      this.comboBox6.SelectedIndexChanged += new EventHandler(this.comboBox6_SelectedIndexChanged);
      this.comboBox6.SelectionChangeCommitted += new EventHandler(this.comboBox6_SelectionChangeCommitted);
      this.label17.AutoSize = true;
      this.label17.Location = new Point(6, 15);
      this.label17.Name = "label17";
      this.label17.Size = new Size(34, 13);
      this.label17.TabIndex = 3;
      this.label17.Text = "Type:";
      this.textBox31.BorderStyle = BorderStyle.FixedSingle;
      this.textBox31.Location = new Point(56, 47);
      this.textBox31.Name = "textBox31";
      this.textBox31.Size = new Size(100, 20);
      this.textBox31.TabIndex = 8;
      this.textBox31.KeyPress += new KeyPressEventHandler(this.textBox31_KeyPress);
      this.label25.AutoSize = true;
      this.label25.Location = new Point(6, 50);
      this.label25.Name = "label25";
      this.label25.Size = new Size(44, 13);
      this.label25.TabIndex = 10;
      this.label25.Text = "Item ID:";
      this.textBox34.BorderStyle = BorderStyle.FixedSingle;
      this.textBox34.Location = new Point(440, 49);
      this.textBox34.Name = "textBox34";
      this.textBox34.Size = new Size(100, 20);
      this.textBox34.TabIndex = 14;
      this.textBox34.KeyPress += new KeyPressEventHandler(this.textBox34_KeyPress);
      this.label28.AutoSize = true;
      this.label28.Location = new Point(388, 52);
      this.label28.Name = "label28";
      this.label28.Size = new Size(46, 13);
      this.label28.TabIndex = 16;
      this.label28.Text = "Amount:";
      this.tabPage4.Controls.Add((Control) this.TbObj2);
      this.tabPage4.Controls.Add((Control) this.PbCond2);
      this.tabPage4.Controls.Add((Control) this.textBox29);
      this.tabPage4.Controls.Add((Control) this.groupBox12);
      this.tabPage4.Controls.Add((Control) this.comboBox7);
      this.tabPage4.Controls.Add((Control) this.label19);
      this.tabPage4.Controls.Add((Control) this.textBox32);
      this.tabPage4.Controls.Add((Control) this.label27);
      this.tabPage4.Controls.Add((Control) this.label24);
      this.tabPage4.Controls.Add((Control) this.textBox35);
      this.tabPage4.Location = new Point(4, 25);
      this.tabPage4.Name = "tabPage4";
      this.tabPage4.Padding = new Padding(3);
      this.tabPage4.Size = new Size(734, 333);
      this.tabPage4.TabIndex = 1;
      this.tabPage4.Text = "Objetive 2";
      this.tabPage4.UseVisualStyleBackColor = true;
      this.TbObj2.BackColor = SystemColors.Menu;
      this.TbObj2.BorderStyle = BorderStyle.FixedSingle;
      this.TbObj2.Location = new Point(162, 47);
      this.TbObj2.Name = "TbObj2";
      this.TbObj2.ReadOnly = true;
      this.TbObj2.Size = new Size(195, 20);
      this.TbObj2.TabIndex = 88;
      this.PbCond2.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbCond2.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbCond2.Location = new Point(360, 47);
      this.PbCond2.Name = "PbCond2";
      this.PbCond2.Size = new Size(22, 22);
      this.PbCond2.TabIndex = 78;
      this.PbCond2.TabStop = false;
      this.PbCond2.Click += new EventHandler(this.PbCond2_Click);
      this.textBox29.Location = new Point(178, 13);
      this.textBox29.Name = "textBox29";
      this.textBox29.Size = new Size(62, 20);
      this.textBox29.TabIndex = 45;
      this.textBox29.Visible = false;
      this.groupBox12.Controls.Add((Control) this.TbObj2Npc3);
      this.groupBox12.Controls.Add((Control) this.PbObj2NpcID3);
      this.groupBox12.Controls.Add((Control) this.TbObj2Npc2);
      this.groupBox12.Controls.Add((Control) this.PbObj2NpcID2);
      this.groupBox12.Controls.Add((Control) this.TbObj2Npc1);
      this.groupBox12.Controls.Add((Control) this.PbObj2NpcID1);
      this.groupBox12.Controls.Add((Control) this.label115);
      this.groupBox12.Controls.Add((Control) this.label36);
      this.groupBox12.Controls.Add((Control) this.label35);
      this.groupBox12.Controls.Add((Control) this.label32);
      this.groupBox12.Controls.Add((Control) this.textBox44);
      this.groupBox12.Controls.Add((Control) this.label33);
      this.groupBox12.Controls.Add((Control) this.textBox41);
      this.groupBox12.Controls.Add((Control) this.textBox42);
      this.groupBox12.Controls.Add((Control) this.textBox43);
      this.groupBox12.Location = new Point(9, 87);
      this.groupBox12.Name = "groupBox12";
      this.groupBox12.Size = new Size(719, 158);
      this.groupBox12.TabIndex = 18;
      this.groupBox12.TabStop = false;
      this.groupBox12.Text = "NPC Quest Item";
      this.TbObj2Npc3.BackColor = SystemColors.Menu;
      this.TbObj2Npc3.BorderStyle = BorderStyle.FixedSingle;
      this.TbObj2Npc3.ForeColor = Color.Red;
      this.TbObj2Npc3.Location = new Point(172, 82);
      this.TbObj2Npc3.Name = "TbObj2Npc3";
      this.TbObj2Npc3.ReadOnly = true;
      this.TbObj2Npc3.Size = new Size(195, 20);
      this.TbObj2Npc3.TabIndex = 109;
      this.PbObj2NpcID3.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbObj2NpcID3.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbObj2NpcID3.Location = new Point(370, 82);
      this.PbObj2NpcID3.Name = "PbObj2NpcID3";
      this.PbObj2NpcID3.Size = new Size(22, 22);
      this.PbObj2NpcID3.TabIndex = 108;
      this.PbObj2NpcID3.TabStop = false;
      this.PbObj2NpcID3.Click += new EventHandler(this.PbObj2NpcID3_Click);
      this.TbObj2Npc2.BackColor = SystemColors.Menu;
      this.TbObj2Npc2.BorderStyle = BorderStyle.FixedSingle;
      this.TbObj2Npc2.ForeColor = Color.Red;
      this.TbObj2Npc2.Location = new Point(172, 56);
      this.TbObj2Npc2.Name = "TbObj2Npc2";
      this.TbObj2Npc2.ReadOnly = true;
      this.TbObj2Npc2.Size = new Size(195, 20);
      this.TbObj2Npc2.TabIndex = 107;
      this.PbObj2NpcID2.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbObj2NpcID2.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbObj2NpcID2.Location = new Point(370, 56);
      this.PbObj2NpcID2.Name = "PbObj2NpcID2";
      this.PbObj2NpcID2.Size = new Size(22, 22);
      this.PbObj2NpcID2.TabIndex = 106;
      this.PbObj2NpcID2.TabStop = false;
      this.PbObj2NpcID2.Click += new EventHandler(this.PbObj2NpcID2_Click);
      this.TbObj2Npc1.BackColor = SystemColors.Menu;
      this.TbObj2Npc1.BorderStyle = BorderStyle.FixedSingle;
      this.TbObj2Npc1.ForeColor = Color.Red;
      this.TbObj2Npc1.Location = new Point(172, 30);
      this.TbObj2Npc1.Name = "TbObj2Npc1";
      this.TbObj2Npc1.ReadOnly = true;
      this.TbObj2Npc1.Size = new Size(195, 20);
      this.TbObj2Npc1.TabIndex = 105;
      this.PbObj2NpcID1.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbObj2NpcID1.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbObj2NpcID1.Location = new Point(370, 30);
      this.PbObj2NpcID1.Name = "PbObj2NpcID1";
      this.PbObj2NpcID1.Size = new Size(22, 22);
      this.PbObj2NpcID1.TabIndex = 104;
      this.PbObj2NpcID1.TabStop = false;
      this.PbObj2NpcID1.Click += new EventHandler(this.PbObj2NpcID1_Click);
      this.label115.AutoSize = true;
      this.label115.Font = new Font("Microsoft Sans Serif", 9.75f, FontStyle.Bold, GraphicsUnit.Point, (byte) 0);
      this.label115.Location = new Point(205, 117);
      this.label115.Name = "label115";
      this.label115.Size = new Size(105, 16);
      this.label115.TabIndex = 103;
      this.label115.Text = "10,000 = 100%";
      this.label36.AutoSize = true;
      this.label36.Location = new Point(14, 34);
      this.label36.Name = "label36";
      this.label36.Size = new Size(46, 13);
      this.label36.TabIndex = 33;
      this.label36.Text = "NPC ID:";
      this.label35.AutoSize = true;
      this.label35.Location = new Point(14, 60);
      this.label35.Name = "label35";
      this.label35.Size = new Size(46, 13);
      this.label35.TabIndex = 34;
      this.label35.Text = "NPC ID:";
      this.label32.AutoSize = true;
      this.label32.Location = new Point(14, 117);
      this.label32.Name = "label32";
      this.label32.Size = new Size(79, 13);
      this.label32.TabIndex = 37;
      this.label32.Text = "Percent to Get:";
      this.textBox44.BorderStyle = BorderStyle.FixedSingle;
      this.textBox44.Location = new Point(99, 114);
      this.textBox44.Name = "textBox44";
      this.textBox44.Size = new Size(100, 20);
      this.textBox44.TabIndex = 44;
      this.textBox44.KeyPress += new KeyPressEventHandler(this.textBox44_KeyPress);
      this.label33.AutoSize = true;
      this.label33.Location = new Point(14, 85);
      this.label33.Name = "label33";
      this.label33.Size = new Size(46, 13);
      this.label33.TabIndex = 35;
      this.label33.Text = "NPC ID:";
      this.textBox41.BorderStyle = BorderStyle.FixedSingle;
      this.textBox41.Location = new Point(66, 30);
      this.textBox41.Name = "textBox41";
      this.textBox41.Size = new Size(100, 20);
      this.textBox41.TabIndex = 26;
      this.textBox41.KeyPress += new KeyPressEventHandler(this.textBox41_KeyPress);
      this.textBox42.BorderStyle = BorderStyle.FixedSingle;
      this.textBox42.Location = new Point(66, 56);
      this.textBox42.Name = "textBox42";
      this.textBox42.Size = new Size(100, 20);
      this.textBox42.TabIndex = 31;
      this.textBox42.KeyPress += new KeyPressEventHandler(this.textBox42_KeyPress);
      this.textBox43.BorderStyle = BorderStyle.FixedSingle;
      this.textBox43.Location = new Point(66, 81);
      this.textBox43.Name = "textBox43";
      this.textBox43.Size = new Size(100, 20);
      this.textBox43.TabIndex = 30;
      this.textBox43.KeyPress += new KeyPressEventHandler(this.textBox43_KeyPress);
      this.comboBox7.FlatStyle = FlatStyle.Popup;
      this.comboBox7.FormattingEnabled = true;
      this.comboBox7.Location = new Point(46, 12);
      this.comboBox7.Name = "comboBox7";
      this.comboBox7.Size = new Size(121, 21);
      this.comboBox7.TabIndex = 5;
      this.comboBox7.SelectedIndexChanged += new EventHandler(this.comboBox7_SelectedIndexChanged);
      this.comboBox7.SelectionChangeCommitted += new EventHandler(this.comboBox7_SelectionChangeCommitted);
      this.label19.AutoSize = true;
      this.label19.Location = new Point(6, 15);
      this.label19.Name = "label19";
      this.label19.Size = new Size(34, 13);
      this.label19.TabIndex = 4;
      this.label19.Text = "Type:";
      this.textBox32.BorderStyle = BorderStyle.FixedSingle;
      this.textBox32.Location = new Point(56, 47);
      this.textBox32.Name = "textBox32";
      this.textBox32.Size = new Size(100, 20);
      this.textBox32.TabIndex = 7;
      this.textBox32.KeyPress += new KeyPressEventHandler(this.textBox32_KeyPress);
      this.label27.AutoSize = true;
      this.label27.Location = new Point(388, 52);
      this.label27.Name = "label27";
      this.label27.Size = new Size(46, 13);
      this.label27.TabIndex = 17;
      this.label27.Text = "Amount:";
      this.label24.AutoSize = true;
      this.label24.Location = new Point(6, 50);
      this.label24.Name = "label24";
      this.label24.Size = new Size(44, 13);
      this.label24.TabIndex = 11;
      this.label24.Text = "Item ID:";
      this.textBox35.BorderStyle = BorderStyle.FixedSingle;
      this.textBox35.Location = new Point(440, 49);
      this.textBox35.Name = "textBox35";
      this.textBox35.Size = new Size(100, 20);
      this.textBox35.TabIndex = 13;
      this.textBox35.KeyPress += new KeyPressEventHandler(this.textBox35_KeyPress);
      this.tabPage5.Controls.Add((Control) this.TbObj3);
      this.tabPage5.Controls.Add((Control) this.PbCond3);
      this.tabPage5.Controls.Add((Control) this.textBox30);
      this.tabPage5.Controls.Add((Control) this.label26);
      this.tabPage5.Controls.Add((Control) this.comboBox8);
      this.tabPage5.Controls.Add((Control) this.textBox36);
      this.tabPage5.Controls.Add((Control) this.textBox33);
      this.tabPage5.Controls.Add((Control) this.label21);
      this.tabPage5.Controls.Add((Control) this.label20);
      this.tabPage5.Controls.Add((Control) this.groupBox6);
      this.tabPage5.Location = new Point(4, 25);
      this.tabPage5.Name = "tabPage5";
      this.tabPage5.Size = new Size(734, 333);
      this.tabPage5.TabIndex = 2;
      this.tabPage5.Text = "Objetive 3";
      this.tabPage5.UseVisualStyleBackColor = true;
      this.TbObj3.BackColor = SystemColors.Menu;
      this.TbObj3.BorderStyle = BorderStyle.FixedSingle;
      this.TbObj3.Location = new Point(162, 47);
      this.TbObj3.Name = "TbObj3";
      this.TbObj3.ReadOnly = true;
      this.TbObj3.Size = new Size(195, 20);
      this.TbObj3.TabIndex = 89;
      this.PbCond3.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbCond3.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbCond3.Location = new Point(360, 47);
      this.PbCond3.Name = "PbCond3";
      this.PbCond3.Size = new Size(22, 22);
      this.PbCond3.TabIndex = 78;
      this.PbCond3.TabStop = false;
      this.PbCond3.Click += new EventHandler(this.PbCond3_Click);
      this.textBox30.Location = new Point(178, 13);
      this.textBox30.Name = "textBox30";
      this.textBox30.Size = new Size(62, 20);
      this.textBox30.TabIndex = 46;
      this.textBox30.Visible = false;
      this.label26.AutoSize = true;
      this.label26.Location = new Point(388, 52);
      this.label26.Name = "label26";
      this.label26.Size = new Size(46, 13);
      this.label26.TabIndex = 18;
      this.label26.Text = "Amount:";
      this.comboBox8.FlatStyle = FlatStyle.Popup;
      this.comboBox8.FormattingEnabled = true;
      this.comboBox8.Location = new Point(46, 12);
      this.comboBox8.Name = "comboBox8";
      this.comboBox8.Size = new Size(121, 21);
      this.comboBox8.TabIndex = 7;
      this.comboBox8.SelectedIndexChanged += new EventHandler(this.comboBox8_SelectedIndexChanged);
      this.comboBox8.SelectionChangeCommitted += new EventHandler(this.comboBox8_SelectionChangeCommitted);
      this.textBox36.BorderStyle = BorderStyle.FixedSingle;
      this.textBox36.Location = new Point(440, 49);
      this.textBox36.Name = "textBox36";
      this.textBox36.Size = new Size(100, 20);
      this.textBox36.TabIndex = 21;
      this.textBox36.KeyPress += new KeyPressEventHandler(this.textBox36_KeyPress);
      this.textBox33.BorderStyle = BorderStyle.FixedSingle;
      this.textBox33.Location = new Point(56, 47);
      this.textBox33.Name = "textBox33";
      this.textBox33.Size = new Size(100, 20);
      this.textBox33.TabIndex = 15;
      this.textBox33.KeyPress += new KeyPressEventHandler(this.textBox33_KeyPress);
      this.label21.AutoSize = true;
      this.label21.Location = new Point(6, 50);
      this.label21.Name = "label21";
      this.label21.Size = new Size(44, 13);
      this.label21.TabIndex = 12;
      this.label21.Text = "Item ID:";
      this.label20.AutoSize = true;
      this.label20.Location = new Point(6, 15);
      this.label20.Name = "label20";
      this.label20.Size = new Size(34, 13);
      this.label20.TabIndex = 6;
      this.label20.Text = "Type:";
      this.groupBox6.Controls.Add((Control) this.label114);
      this.groupBox6.Controls.Add((Control) this.TbObjNpc3);
      this.groupBox6.Controls.Add((Control) this.PbNpcID3);
      this.groupBox6.Controls.Add((Control) this.TbObjNpc2);
      this.groupBox6.Controls.Add((Control) this.PbNpcID2);
      this.groupBox6.Controls.Add((Control) this.TbObjNpc1);
      this.groupBox6.Controls.Add((Control) this.PbNpcID1);
      this.groupBox6.Controls.Add((Control) this.textBox46);
      this.groupBox6.Controls.Add((Control) this.textBox48);
      this.groupBox6.Controls.Add((Control) this.textBox47);
      this.groupBox6.Controls.Add((Control) this.label37);
      this.groupBox6.Controls.Add((Control) this.textBox45);
      this.groupBox6.Controls.Add((Control) this.label40);
      this.groupBox6.Controls.Add((Control) this.label38);
      this.groupBox6.Controls.Add((Control) this.label39);
      this.groupBox6.Location = new Point(9, 87);
      this.groupBox6.Name = "groupBox6";
      this.groupBox6.Size = new Size(719, 158);
      this.groupBox6.TabIndex = 25;
      this.groupBox6.TabStop = false;
      this.groupBox6.Text = "NPC Quest Item";
      this.label114.AutoSize = true;
      this.label114.Font = new Font("Microsoft Sans Serif", 9.75f, FontStyle.Bold, GraphicsUnit.Point, (byte) 0);
      this.label114.Location = new Point(205, 117);
      this.label114.Name = "label114";
      this.label114.Size = new Size(105, 16);
      this.label114.TabIndex = 103;
      this.label114.Text = "10,000 = 100%";
      this.TbObjNpc3.BackColor = SystemColors.Menu;
      this.TbObjNpc3.BorderStyle = BorderStyle.FixedSingle;
      this.TbObjNpc3.ForeColor = Color.Red;
      this.TbObjNpc3.Location = new Point(172, 82);
      this.TbObjNpc3.Name = "TbObjNpc3";
      this.TbObjNpc3.ReadOnly = true;
      this.TbObjNpc3.Size = new Size(195, 20);
      this.TbObjNpc3.TabIndex = 95;
      this.PbNpcID3.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbNpcID3.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbNpcID3.Location = new Point(370, 82);
      this.PbNpcID3.Name = "PbNpcID3";
      this.PbNpcID3.Size = new Size(22, 22);
      this.PbNpcID3.TabIndex = 94;
      this.PbNpcID3.TabStop = false;
      this.PbNpcID3.Click += new EventHandler(this.PbNpcID3_Click);
      this.TbObjNpc2.BackColor = SystemColors.Menu;
      this.TbObjNpc2.BorderStyle = BorderStyle.FixedSingle;
      this.TbObjNpc2.ForeColor = Color.Red;
      this.TbObjNpc2.Location = new Point(172, 56);
      this.TbObjNpc2.Name = "TbObjNpc2";
      this.TbObjNpc2.ReadOnly = true;
      this.TbObjNpc2.Size = new Size(195, 20);
      this.TbObjNpc2.TabIndex = 93;
      this.PbNpcID2.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbNpcID2.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbNpcID2.Location = new Point(370, 56);
      this.PbNpcID2.Name = "PbNpcID2";
      this.PbNpcID2.Size = new Size(22, 22);
      this.PbNpcID2.TabIndex = 92;
      this.PbNpcID2.TabStop = false;
      this.PbNpcID2.Click += new EventHandler(this.PbNpcID2_Click);
      this.TbObjNpc1.BackColor = SystemColors.Menu;
      this.TbObjNpc1.BorderStyle = BorderStyle.FixedSingle;
      this.TbObjNpc1.ForeColor = Color.Red;
      this.TbObjNpc1.Location = new Point(172, 30);
      this.TbObjNpc1.Name = "TbObjNpc1";
      this.TbObjNpc1.ReadOnly = true;
      this.TbObjNpc1.Size = new Size(195, 20);
      this.TbObjNpc1.TabIndex = 91;
      this.PbNpcID1.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbNpcID1.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbNpcID1.Location = new Point(370, 30);
      this.PbNpcID1.Name = "PbNpcID1";
      this.PbNpcID1.Size = new Size(22, 22);
      this.PbNpcID1.TabIndex = 90;
      this.PbNpcID1.TabStop = false;
      this.PbNpcID1.Click += new EventHandler(this.PbNpcID1_Click);
      this.textBox46.BorderStyle = BorderStyle.FixedSingle;
      this.textBox46.Location = new Point(66, 56);
      this.textBox46.Name = "textBox46";
      this.textBox46.Size = new Size(100, 20);
      this.textBox46.TabIndex = 39;
      this.textBox46.KeyPress += new KeyPressEventHandler(this.textBox46_KeyPress);
      this.textBox48.BorderStyle = BorderStyle.FixedSingle;
      this.textBox48.Location = new Point(99, 114);
      this.textBox48.Name = "textBox48";
      this.textBox48.Size = new Size(100, 20);
      this.textBox48.TabIndex = 46;
      this.textBox48.KeyPress += new KeyPressEventHandler(this.textBox48_KeyPress);
      this.textBox47.BorderStyle = BorderStyle.FixedSingle;
      this.textBox47.Location = new Point(66, 81);
      this.textBox47.Name = "textBox47";
      this.textBox47.Size = new Size(100, 20);
      this.textBox47.TabIndex = 38;
      this.textBox47.KeyPress += new KeyPressEventHandler(this.textBox47_KeyPress);
      this.label37.AutoSize = true;
      this.label37.Location = new Point(14, 117);
      this.label37.Name = "label37";
      this.label37.Size = new Size(79, 13);
      this.label37.TabIndex = 45;
      this.label37.Text = "Percent to Get:";
      this.textBox45.BorderStyle = BorderStyle.FixedSingle;
      this.textBox45.Location = new Point(66, 30);
      this.textBox45.Name = "textBox45";
      this.textBox45.Size = new Size(100, 20);
      this.textBox45.TabIndex = 40;
      this.textBox45.KeyPress += new KeyPressEventHandler(this.textBox45_KeyPress);
      this.label40.AutoSize = true;
      this.label40.Location = new Point(14, 34);
      this.label40.Name = "label40";
      this.label40.Size = new Size(46, 13);
      this.label40.TabIndex = 41;
      this.label40.Text = "NPC ID:";
      this.label38.AutoSize = true;
      this.label38.Location = new Point(14, 85);
      this.label38.Name = "label38";
      this.label38.Size = new Size(46, 13);
      this.label38.TabIndex = 43;
      this.label38.Text = "NPC ID:";
      this.label39.AutoSize = true;
      this.label39.Location = new Point(14, 60);
      this.label39.Name = "label39";
      this.label39.Size = new Size(46, 13);
      this.label39.TabIndex = 42;
      this.label39.Text = "NPC ID:";
      this.Page2.BackColor = SystemColors.Control;
      this.Page2.Controls.Add((Control) this.TbFileCol);
      this.Page2.Controls.Add((Control) this.tbFileRow);
      this.Page2.Controls.Add((Control) this.tbFileID);
      this.Page2.Controls.Add((Control) this.tabControl3);
      this.Page2.Controls.Add((Control) this.textBox69);
      this.Page2.Controls.Add((Control) this.textBox70);
      this.Page2.Controls.Add((Control) this.textBox68);
      this.Page2.Controls.Add((Control) this.textBox65);
      this.Page2.Controls.Add((Control) this.textBox71);
      this.Page2.Controls.Add((Control) this.textBox67);
      this.Page2.Controls.Add((Control) this.textBox53);
      this.Page2.Controls.Add((Control) this.textBox66);
      this.Page2.Controls.Add((Control) this.textBox52);
      this.Page2.Controls.Add((Control) this.textBox49);
      this.Page2.Controls.Add((Control) this.textBox51);
      this.Page2.Controls.Add((Control) this.textBox50);
      this.Page2.Location = new Point(4, 22);
      this.Page2.Name = "Page2";
      this.Page2.Size = new Size(765, 610);
      this.Page2.TabIndex = 5;
      this.Page2.Text = "Prize";
      this.TbFileCol.Location = new Point(85, 543);
      this.TbFileCol.Name = "TbFileCol";
      this.TbFileCol.Size = new Size(41, 20);
      this.TbFileCol.TabIndex = 217;
      this.TbFileCol.Visible = false;
      this.tbFileRow.Location = new Point(85, 517);
      this.tbFileRow.Name = "tbFileRow";
      this.tbFileRow.Size = new Size(41, 20);
      this.tbFileRow.TabIndex = 216;
      this.tbFileRow.Visible = false;
      this.tbFileID.Location = new Point(85, 491);
      this.tbFileID.Name = "tbFileID";
      this.tbFileID.Size = new Size(41, 20);
      this.tbFileID.TabIndex = 215;
      this.tbFileID.Visible = false;
      this.tabControl3.Appearance = TabAppearance.Buttons;
      this.tabControl3.Controls.Add((Control) this.tabPage8);
      this.tabControl3.Controls.Add((Control) this.tabPage9);
      this.tabControl3.Location = new Point(3, 3);
      this.tabControl3.Name = "tabControl3";
      this.tabControl3.SelectedIndex = 0;
      this.tabControl3.Size = new Size(757, 434);
      this.tabControl3.SizeMode = TabSizeMode.Fixed;
      this.tabControl3.TabIndex = 72;
      this.tabPage8.Controls.Add((Control) this.pictureBox15);
      this.tabPage8.Controls.Add((Control) this.pictureBox14);
      this.tabPage8.Controls.Add((Control) this.pictureBox13);
      this.tabPage8.Controls.Add((Control) this.pictureBox12);
      this.tabPage8.Controls.Add((Control) this.pictureBox11);
      this.tabPage8.Controls.Add((Control) this.tbItemDesc5);
      this.tabPage8.Controls.Add((Control) this.tbItemDesc4);
      this.tabPage8.Controls.Add((Control) this.tbItemDesc3);
      this.tabPage8.Controls.Add((Control) this.tbItemDesc2);
      this.tabPage8.Controls.Add((Control) this.tbItemDesc1);
      this.tabPage8.Controls.Add((Control) this.PbPItem5);
      this.tabPage8.Controls.Add((Control) this.PbPItem4);
      this.tabPage8.Controls.Add((Control) this.PbPItem3);
      this.tabPage8.Controls.Add((Control) this.PbPItem2);
      this.tabPage8.Controls.Add((Control) this.PbPItem1);
      this.tabPage8.Controls.Add((Control) this.comboBox13);
      this.tabPage8.Controls.Add((Control) this.textBox59);
      this.tabPage8.Controls.Add((Control) this.comboBox12);
      this.tabPage8.Controls.Add((Control) this.textBox63);
      this.tabPage8.Controls.Add((Control) this.textBox60);
      this.tabPage8.Controls.Add((Control) this.comboBox11);
      this.tabPage8.Controls.Add((Control) this.textBox61);
      this.tabPage8.Controls.Add((Control) this.textBox58);
      this.tabPage8.Controls.Add((Control) this.textBox62);
      this.tabPage8.Controls.Add((Control) this.comboBox10);
      this.tabPage8.Controls.Add((Control) this.label60);
      this.tabPage8.Controls.Add((Control) this.label48);
      this.tabPage8.Controls.Add((Control) this.label58);
      this.tabPage8.Controls.Add((Control) this.comboBox9);
      this.tabPage8.Controls.Add((Control) this.label55);
      this.tabPage8.Controls.Add((Control) this.textBox57);
      this.tabPage8.Controls.Add((Control) this.label57);
      this.tabPage8.Controls.Add((Control) this.label45);
      this.tabPage8.Controls.Add((Control) this.label56);
      this.tabPage8.Controls.Add((Control) this.label44);
      this.tabPage8.Controls.Add((Control) this.label49);
      this.tabPage8.Controls.Add((Control) this.label43);
      this.tabPage8.Controls.Add((Control) this.textBox56);
      this.tabPage8.Controls.Add((Control) this.label42);
      this.tabPage8.Controls.Add((Control) this.label41);
      this.tabPage8.Controls.Add((Control) this.label50);
      this.tabPage8.Controls.Add((Control) this.label53);
      this.tabPage8.Controls.Add((Control) this.textBox55);
      this.tabPage8.Controls.Add((Control) this.textBox54);
      this.tabPage8.Controls.Add((Control) this.label51);
      this.tabPage8.Location = new Point(4, 25);
      this.tabPage8.Name = "tabPage8";
      this.tabPage8.Padding = new Padding(3);
      this.tabPage8.Size = new Size(749, 405);
      this.tabPage8.TabIndex = 0;
      this.tabPage8.Text = "Prize 1";
      this.tabPage8.UseVisualStyleBackColor = true;
      this.pictureBox15.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox15.Location = new Point(325, 162);
      this.pictureBox15.Name = "pictureBox15";
      this.pictureBox15.Size = new Size(25, 25);
      this.pictureBox15.TabIndex = 241;
      this.pictureBox15.TabStop = false;
      this.pictureBox14.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox14.Location = new Point(325, 125);
      this.pictureBox14.Name = "pictureBox14";
      this.pictureBox14.Size = new Size(25, 25);
      this.pictureBox14.TabIndex = 240;
      this.pictureBox14.TabStop = false;
      this.pictureBox13.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox13.Location = new Point(325, 88);
      this.pictureBox13.Name = "pictureBox13";
      this.pictureBox13.Size = new Size(25, 25);
      this.pictureBox13.TabIndex = 239;
      this.pictureBox13.TabStop = false;
      this.pictureBox12.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox12.Location = new Point(325, 51);
      this.pictureBox12.Name = "pictureBox12";
      this.pictureBox12.Size = new Size(25, 25);
      this.pictureBox12.TabIndex = 238;
      this.pictureBox12.TabStop = false;
      this.pictureBox11.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox11.Location = new Point(325, 14);
      this.pictureBox11.Name = "pictureBox11";
      this.pictureBox11.Size = new Size(25, 25);
      this.pictureBox11.TabIndex = 237;
      this.pictureBox11.TabStop = false;
      this.tbItemDesc5.BackColor = SystemColors.Menu;
      this.tbItemDesc5.BorderStyle = BorderStyle.FixedSingle;
      this.tbItemDesc5.ForeColor = Color.RoyalBlue;
      this.tbItemDesc5.Location = new Point(361, 162);
      this.tbItemDesc5.Name = "tbItemDesc5";
      this.tbItemDesc5.ReadOnly = true;
      this.tbItemDesc5.Size = new Size(185, 20);
      this.tbItemDesc5.TabIndex = 82;
      this.tbItemDesc4.BackColor = SystemColors.Menu;
      this.tbItemDesc4.BorderStyle = BorderStyle.FixedSingle;
      this.tbItemDesc4.ForeColor = Color.RoyalBlue;
      this.tbItemDesc4.Location = new Point(361, 125);
      this.tbItemDesc4.Name = "tbItemDesc4";
      this.tbItemDesc4.ReadOnly = true;
      this.tbItemDesc4.Size = new Size(185, 20);
      this.tbItemDesc4.TabIndex = 83;
      this.tbItemDesc3.BackColor = SystemColors.Menu;
      this.tbItemDesc3.BorderStyle = BorderStyle.FixedSingle;
      this.tbItemDesc3.ForeColor = Color.RoyalBlue;
      this.tbItemDesc3.Location = new Point(361, 88);
      this.tbItemDesc3.Name = "tbItemDesc3";
      this.tbItemDesc3.ReadOnly = true;
      this.tbItemDesc3.Size = new Size(185, 20);
      this.tbItemDesc3.TabIndex = 84;
      this.tbItemDesc2.BackColor = SystemColors.Menu;
      this.tbItemDesc2.BorderStyle = BorderStyle.FixedSingle;
      this.tbItemDesc2.ForeColor = Color.RoyalBlue;
      this.tbItemDesc2.Location = new Point(361, 51);
      this.tbItemDesc2.Name = "tbItemDesc2";
      this.tbItemDesc2.ReadOnly = true;
      this.tbItemDesc2.Size = new Size(185, 20);
      this.tbItemDesc2.TabIndex = 85;
      this.tbItemDesc1.BackColor = SystemColors.Menu;
      this.tbItemDesc1.BorderStyle = BorderStyle.FixedSingle;
      this.tbItemDesc1.ForeColor = Color.RoyalBlue;
      this.tbItemDesc1.Location = new Point(361, 14);
      this.tbItemDesc1.Name = "tbItemDesc1";
      this.tbItemDesc1.ReadOnly = true;
      this.tbItemDesc1.Size = new Size(185, 20);
      this.tbItemDesc1.TabIndex = 86;
      this.PbPItem5.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbPItem5.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbPItem5.Location = new Point(552, 161);
      this.PbPItem5.Name = "PbPItem5";
      this.PbPItem5.Size = new Size(22, 22);
      this.PbPItem5.TabIndex = 81;
      this.PbPItem5.TabStop = false;
      this.PbPItem5.Click += new EventHandler(this.PbPItem5_Click);
      this.PbPItem4.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbPItem4.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbPItem4.Location = new Point(552, 124);
      this.PbPItem4.Name = "PbPItem4";
      this.PbPItem4.Size = new Size(22, 22);
      this.PbPItem4.TabIndex = 80;
      this.PbPItem4.TabStop = false;
      this.PbPItem4.Click += new EventHandler(this.PbPItem4_Click);
      this.PbPItem3.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbPItem3.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbPItem3.Location = new Point(552, 87);
      this.PbPItem3.Name = "PbPItem3";
      this.PbPItem3.Size = new Size(22, 22);
      this.PbPItem3.TabIndex = 79;
      this.PbPItem3.TabStop = false;
      this.PbPItem3.Click += new EventHandler(this.PbPItem3_Click);
      this.PbPItem2.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbPItem2.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbPItem2.Location = new Point(552, 50);
      this.PbPItem2.Name = "PbPItem2";
      this.PbPItem2.Size = new Size(22, 22);
      this.PbPItem2.TabIndex = 78;
      this.PbPItem2.TabStop = false;
      this.PbPItem2.Click += new EventHandler(this.PbPItem2_Click);
      this.PbPItem1.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbPItem1.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbPItem1.Location = new Point(552, 13);
      this.PbPItem1.Name = "PbPItem1";
      this.PbPItem1.Size = new Size(22, 22);
      this.PbPItem1.TabIndex = 77;
      this.PbPItem1.TabStop = false;
      this.PbPItem1.Click += new EventHandler(this.PbPItem1_Click);
      this.comboBox13.FlatStyle = FlatStyle.Popup;
      this.comboBox13.FormattingEnabled = true;
      this.comboBox13.Location = new Point(46, 162);
      this.comboBox13.Name = "comboBox13";
      this.comboBox13.Size = new Size(91, 21);
      this.comboBox13.TabIndex = 9;
      this.comboBox13.SelectedIndexChanged += new EventHandler(this.comboBox13_SelectedIndexChanged_1);
      this.comboBox13.SelectionChangeCommitted += new EventHandler(this.comboBox13_SelectionChangeCommitted);
      this.textBox59.BorderStyle = BorderStyle.FixedSingle;
      this.textBox59.Location = new Point(633, 14);
      this.textBox59.Name = "textBox59";
      this.textBox59.Size = new Size(100, 20);
      this.textBox59.TabIndex = 71;
      this.textBox59.KeyPress += new KeyPressEventHandler(this.textBox59_KeyPress);
      this.comboBox12.FlatStyle = FlatStyle.Popup;
      this.comboBox12.FormattingEnabled = true;
      this.comboBox12.Location = new Point(46, 125);
      this.comboBox12.Name = "comboBox12";
      this.comboBox12.Size = new Size(91, 21);
      this.comboBox12.TabIndex = 8;
      this.comboBox12.SelectedIndexChanged += new EventHandler(this.comboBox12_SelectedIndexChanged);
      this.comboBox12.SelectionChangeCommitted += new EventHandler(this.comboBox12_SelectionChangeCommitted);
      this.textBox63.BorderStyle = BorderStyle.FixedSingle;
      this.textBox63.Location = new Point(633, 162);
      this.textBox63.Name = "textBox63";
      this.textBox63.Size = new Size(100, 20);
      this.textBox63.TabIndex = 67;
      this.textBox63.KeyPress += new KeyPressEventHandler(this.textBox63_KeyPress);
      this.textBox60.BorderStyle = BorderStyle.FixedSingle;
      this.textBox60.Location = new Point(633, 51);
      this.textBox60.Name = "textBox60";
      this.textBox60.Size = new Size(100, 20);
      this.textBox60.TabIndex = 70;
      this.textBox60.KeyPress += new KeyPressEventHandler(this.textBox60_KeyPress);
      this.comboBox11.FlatStyle = FlatStyle.Popup;
      this.comboBox11.FormattingEnabled = true;
      this.comboBox11.Location = new Point(46, 88);
      this.comboBox11.Name = "comboBox11";
      this.comboBox11.Size = new Size(91, 21);
      this.comboBox11.TabIndex = 7;
      this.comboBox11.SelectedIndexChanged += new EventHandler(this.comboBox11_SelectedIndexChanged);
      this.comboBox11.SelectionChangeCommitted += new EventHandler(this.comboBox11_SelectionChangeCommitted);
      this.textBox61.BorderStyle = BorderStyle.FixedSingle;
      this.textBox61.Location = new Point(633, 88);
      this.textBox61.Name = "textBox61";
      this.textBox61.Size = new Size(100, 20);
      this.textBox61.TabIndex = 69;
      this.textBox61.KeyPress += new KeyPressEventHandler(this.textBox61_KeyPress);
      this.textBox58.BorderStyle = BorderStyle.FixedSingle;
      this.textBox58.Location = new Point(216, 162);
      this.textBox58.Name = "textBox58";
      this.textBox58.Size = new Size(100, 20);
      this.textBox58.TabIndex = 57;
      this.textBox58.KeyPress += new KeyPressEventHandler(this.textBox58_KeyPress);
      this.textBox62.BorderStyle = BorderStyle.FixedSingle;
      this.textBox62.Location = new Point(633, 125);
      this.textBox62.Name = "textBox62";
      this.textBox62.Size = new Size(100, 20);
      this.textBox62.TabIndex = 68;
      this.textBox62.KeyPress += new KeyPressEventHandler(this.textBox62_KeyPress);
      this.comboBox10.FlatStyle = FlatStyle.Popup;
      this.comboBox10.FormattingEnabled = true;
      this.comboBox10.Location = new Point(46, 51);
      this.comboBox10.Name = "comboBox10";
      this.comboBox10.Size = new Size(91, 21);
      this.comboBox10.TabIndex = 6;
      this.comboBox10.SelectedIndexChanged += new EventHandler(this.comboBox10_SelectedIndexChanged);
      this.comboBox10.SelectionChangeCommitted += new EventHandler(this.comboBox10_SelectionChangeCommitted);
      this.label60.AutoSize = true;
      this.label60.Location = new Point(581, 165);
      this.label60.Name = "label60";
      this.label60.Size = new Size(46, 13);
      this.label60.TabIndex = 66;
      this.label60.Text = "Amount:";
      this.label48.AutoSize = true;
      this.label48.Location = new Point(165, 166);
      this.label48.Name = "label48";
      this.label48.Size = new Size(44, 13);
      this.label48.TabIndex = 56;
      this.label48.Text = "Item ID:";
      this.label58.AutoSize = true;
      this.label58.Location = new Point(581, 128);
      this.label58.Name = "label58";
      this.label58.Size = new Size(46, 13);
      this.label58.TabIndex = 65;
      this.label58.Text = "Amount:";
      this.comboBox9.FlatStyle = FlatStyle.Popup;
      this.comboBox9.FormattingEnabled = true;
      this.comboBox9.Location = new Point(46, 14);
      this.comboBox9.Name = "comboBox9";
      this.comboBox9.Size = new Size(91, 21);
      this.comboBox9.TabIndex = 5;
      this.comboBox9.SelectedIndexChanged += new EventHandler(this.comboBox9_SelectedIndexChanged);
      this.comboBox9.SelectionChangeCommitted += new EventHandler(this.comboBox9_SelectionChangeCommitted);
      this.label55.AutoSize = true;
      this.label55.Location = new Point(581, 18);
      this.label55.Name = "label55";
      this.label55.Size = new Size(46, 13);
      this.label55.TabIndex = 62;
      this.label55.Text = "Amount:";
      this.textBox57.BorderStyle = BorderStyle.FixedSingle;
      this.textBox57.Location = new Point(216, 125);
      this.textBox57.Name = "textBox57";
      this.textBox57.Size = new Size(100, 20);
      this.textBox57.TabIndex = 58;
      this.textBox57.KeyPress += new KeyPressEventHandler(this.textBox57_KeyPress);
      this.label57.AutoSize = true;
      this.label57.Location = new Point(581, 92);
      this.label57.Name = "label57";
      this.label57.Size = new Size(46, 13);
      this.label57.TabIndex = 64;
      this.label57.Text = "Amount:";
      this.label45.AutoSize = true;
      this.label45.Location = new Point(6, 165);
      this.label45.Name = "label45";
      this.label45.Size = new Size(34, 13);
      this.label45.TabIndex = 4;
      this.label45.Text = "Type:";
      this.label56.AutoSize = true;
      this.label56.Location = new Point(581, 55);
      this.label56.Name = "label56";
      this.label56.Size = new Size(46, 13);
      this.label56.TabIndex = 63;
      this.label56.Text = "Amount:";
      this.label44.AutoSize = true;
      this.label44.Location = new Point(6, 128);
      this.label44.Name = "label44";
      this.label44.Size = new Size(34, 13);
      this.label44.TabIndex = 3;
      this.label44.Text = "Type:";
      this.label49.AutoSize = true;
      this.label49.Location = new Point(165, 129);
      this.label49.Name = "label49";
      this.label49.Size = new Size(44, 13);
      this.label49.TabIndex = 55;
      this.label49.Text = "Item ID:";
      this.label43.AutoSize = true;
      this.label43.Location = new Point(6, 92);
      this.label43.Name = "label43";
      this.label43.Size = new Size(34, 13);
      this.label43.TabIndex = 2;
      this.label43.Text = "Type:";
      this.textBox56.BorderStyle = BorderStyle.FixedSingle;
      this.textBox56.Location = new Point(216, 88);
      this.textBox56.Name = "textBox56";
      this.textBox56.Size = new Size(100, 20);
      this.textBox56.TabIndex = 59;
      this.textBox56.KeyPress += new KeyPressEventHandler(this.textBox56_KeyPress);
      this.label42.AutoSize = true;
      this.label42.Location = new Point(6, 55);
      this.label42.Name = "label42";
      this.label42.Size = new Size(34, 13);
      this.label42.TabIndex = 1;
      this.label42.Text = "Type:";
      this.label41.AutoSize = true;
      this.label41.Location = new Point(6, 18);
      this.label41.Name = "label41";
      this.label41.Size = new Size(34, 13);
      this.label41.TabIndex = 0;
      this.label41.Text = "Type:";
      this.label50.AutoSize = true;
      this.label50.Location = new Point(165, 93);
      this.label50.Name = "label50";
      this.label50.Size = new Size(44, 13);
      this.label50.TabIndex = 54;
      this.label50.Text = "Item ID:";
      this.label53.AutoSize = true;
      this.label53.Location = new Point(165, 19);
      this.label53.Name = "label53";
      this.label53.Size = new Size(44, 13);
      this.label53.TabIndex = 52;
      this.label53.Text = "Item ID:";
      this.textBox55.BorderStyle = BorderStyle.FixedSingle;
      this.textBox55.Location = new Point(216, 51);
      this.textBox55.Name = "textBox55";
      this.textBox55.Size = new Size(100, 20);
      this.textBox55.TabIndex = 60;
      this.textBox55.KeyPress += new KeyPressEventHandler(this.textBox55_KeyPress);
      this.textBox54.BorderStyle = BorderStyle.FixedSingle;
      this.textBox54.Location = new Point(216, 14);
      this.textBox54.Name = "textBox54";
      this.textBox54.Size = new Size(100, 20);
      this.textBox54.TabIndex = 61;
      this.textBox54.KeyPress += new KeyPressEventHandler(this.textBox54_KeyPress);
      this.label51.AutoSize = true;
      this.label51.Location = new Point(165, 56);
      this.label51.Name = "label51";
      this.label51.Size = new Size(44, 13);
      this.label51.TabIndex = 53;
      this.label51.Text = "Item ID:";
      this.tabPage9.Controls.Add((Control) this.pictureBox10);
      this.tabPage9.Controls.Add((Control) this.pictureBox9);
      this.tabPage9.Controls.Add((Control) this.pictureBox8);
      this.tabPage9.Controls.Add((Control) this.pictureBox7);
      this.tabPage9.Controls.Add((Control) this.pictureBox6);
      this.tabPage9.Controls.Add((Control) this.pictureBox5);
      this.tabPage9.Controls.Add((Control) this.pictureBox4);
      this.tabPage9.Controls.Add((Control) this.TbPrize2ItemDesc1);
      this.tabPage9.Controls.Add((Control) this.TbPrize2ItemDesc2);
      this.tabPage9.Controls.Add((Control) this.TbPrize2ItemDesc3);
      this.tabPage9.Controls.Add((Control) this.TbPrize2ItemDesc4);
      this.tabPage9.Controls.Add((Control) this.TbPrize2ItemDesc5);
      this.tabPage9.Controls.Add((Control) this.TbPrize2ItemDesc6);
      this.tabPage9.Controls.Add((Control) this.TbPrize2ItemDesc7);
      this.tabPage9.Controls.Add((Control) this.PbItem7);
      this.tabPage9.Controls.Add((Control) this.PbItem6);
      this.tabPage9.Controls.Add((Control) this.PbItem5);
      this.tabPage9.Controls.Add((Control) this.PbItem4);
      this.tabPage9.Controls.Add((Control) this.PbItem3);
      this.tabPage9.Controls.Add((Control) this.PbItem2);
      this.tabPage9.Controls.Add((Control) this.PbItem1);
      this.tabPage9.Controls.Add((Control) this.textBox93);
      this.tabPage9.Controls.Add((Control) this.label94);
      this.tabPage9.Controls.Add((Control) this.textBox64);
      this.tabPage9.Controls.Add((Control) this.label61);
      this.tabPage9.Controls.Add((Control) this.comboBox20);
      this.tabPage9.Controls.Add((Control) this.comboBox19);
      this.tabPage9.Controls.Add((Control) this.comboBox18);
      this.tabPage9.Controls.Add((Control) this.comboBox17);
      this.tabPage9.Controls.Add((Control) this.comboBox16);
      this.tabPage9.Controls.Add((Control) this.comboBox15);
      this.tabPage9.Controls.Add((Control) this.comboBox14);
      this.tabPage9.Controls.Add((Control) this.label67);
      this.tabPage9.Controls.Add((Control) this.label68);
      this.tabPage9.Controls.Add((Control) this.label66);
      this.tabPage9.Controls.Add((Control) this.label65);
      this.tabPage9.Controls.Add((Control) this.label64);
      this.tabPage9.Controls.Add((Control) this.label63);
      this.tabPage9.Controls.Add((Control) this.label62);
      this.tabPage9.Controls.Add((Control) this.textBox79);
      this.tabPage9.Controls.Add((Control) this.textBox80);
      this.tabPage9.Controls.Add((Control) this.label76);
      this.tabPage9.Controls.Add((Control) this.label77);
      this.tabPage9.Controls.Add((Control) this.textBox81);
      this.tabPage9.Controls.Add((Control) this.textBox82);
      this.tabPage9.Controls.Add((Control) this.textBox83);
      this.tabPage9.Controls.Add((Control) this.textBox84);
      this.tabPage9.Controls.Add((Control) this.textBox85);
      this.tabPage9.Controls.Add((Control) this.label78);
      this.tabPage9.Controls.Add((Control) this.label79);
      this.tabPage9.Controls.Add((Control) this.label80);
      this.tabPage9.Controls.Add((Control) this.label81);
      this.tabPage9.Controls.Add((Control) this.label82);
      this.tabPage9.Controls.Add((Control) this.textBox72);
      this.tabPage9.Controls.Add((Control) this.textBox73);
      this.tabPage9.Controls.Add((Control) this.label69);
      this.tabPage9.Controls.Add((Control) this.label70);
      this.tabPage9.Controls.Add((Control) this.textBox74);
      this.tabPage9.Controls.Add((Control) this.textBox75);
      this.tabPage9.Controls.Add((Control) this.textBox76);
      this.tabPage9.Controls.Add((Control) this.textBox77);
      this.tabPage9.Controls.Add((Control) this.textBox78);
      this.tabPage9.Controls.Add((Control) this.label71);
      this.tabPage9.Controls.Add((Control) this.label72);
      this.tabPage9.Controls.Add((Control) this.label73);
      this.tabPage9.Controls.Add((Control) this.label74);
      this.tabPage9.Controls.Add((Control) this.label75);
      this.tabPage9.Controls.Add((Control) this.textBox86);
      this.tabPage9.Controls.Add((Control) this.textBox87);
      this.tabPage9.Controls.Add((Control) this.textBox92);
      this.tabPage9.Controls.Add((Control) this.label83);
      this.tabPage9.Controls.Add((Control) this.label90);
      this.tabPage9.Controls.Add((Control) this.label84);
      this.tabPage9.Controls.Add((Control) this.label89);
      this.tabPage9.Controls.Add((Control) this.textBox88);
      this.tabPage9.Controls.Add((Control) this.label88);
      this.tabPage9.Controls.Add((Control) this.textBox89);
      this.tabPage9.Controls.Add((Control) this.label87);
      this.tabPage9.Controls.Add((Control) this.textBox90);
      this.tabPage9.Controls.Add((Control) this.label86);
      this.tabPage9.Controls.Add((Control) this.textBox91);
      this.tabPage9.Location = new Point(4, 25);
      this.tabPage9.Name = "tabPage9";
      this.tabPage9.Padding = new Padding(3);
      this.tabPage9.Size = new Size(749, 405);
      this.tabPage9.TabIndex = 1;
      this.tabPage9.Text = "Prize 2";
      this.tabPage9.UseVisualStyleBackColor = true;
      this.pictureBox10.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox10.Location = new Point(252, 241);
      this.pictureBox10.Name = "pictureBox10";
      this.pictureBox10.Size = new Size(25, 25);
      this.pictureBox10.TabIndex = 242;
      this.pictureBox10.TabStop = false;
      this.pictureBox9.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox9.Location = new Point(252, 205);
      this.pictureBox9.Name = "pictureBox9";
      this.pictureBox9.Size = new Size(25, 25);
      this.pictureBox9.TabIndex = 241;
      this.pictureBox9.TabStop = false;
      this.pictureBox8.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox8.Location = new Point(252, 169);
      this.pictureBox8.Name = "pictureBox8";
      this.pictureBox8.Size = new Size(25, 25);
      this.pictureBox8.TabIndex = 240;
      this.pictureBox8.TabStop = false;
      this.pictureBox7.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox7.Location = new Point(252, 134);
      this.pictureBox7.Name = "pictureBox7";
      this.pictureBox7.Size = new Size(25, 25);
      this.pictureBox7.TabIndex = 239;
      this.pictureBox7.TabStop = false;
      this.pictureBox6.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox6.Location = new Point(252, 98);
      this.pictureBox6.Name = "pictureBox6";
      this.pictureBox6.Size = new Size(25, 25);
      this.pictureBox6.TabIndex = 238;
      this.pictureBox6.TabStop = false;
      this.pictureBox5.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox5.Location = new Point(252, 61);
      this.pictureBox5.Name = "pictureBox5";
      this.pictureBox5.Size = new Size(25, 25);
      this.pictureBox5.TabIndex = 237;
      this.pictureBox5.TabStop = false;
      this.pictureBox4.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox4.Location = new Point(252, 25);
      this.pictureBox4.Name = "pictureBox4";
      this.pictureBox4.Size = new Size(25, 25);
      this.pictureBox4.TabIndex = 236;
      this.pictureBox4.TabStop = false;
      this.TbPrize2ItemDesc1.BackColor = SystemColors.Menu;
      this.TbPrize2ItemDesc1.BorderStyle = BorderStyle.FixedSingle;
      this.TbPrize2ItemDesc1.ForeColor = Color.RoyalBlue;
      this.TbPrize2ItemDesc1.Location = new Point(291, 25);
      this.TbPrize2ItemDesc1.Name = "TbPrize2ItemDesc1";
      this.TbPrize2ItemDesc1.ReadOnly = true;
      this.TbPrize2ItemDesc1.Size = new Size(168, 20);
      this.TbPrize2ItemDesc1.TabIndex = 235;
      this.TbPrize2ItemDesc2.BackColor = SystemColors.Menu;
      this.TbPrize2ItemDesc2.BorderStyle = BorderStyle.FixedSingle;
      this.TbPrize2ItemDesc2.ForeColor = Color.RoyalBlue;
      this.TbPrize2ItemDesc2.Location = new Point(291, 61);
      this.TbPrize2ItemDesc2.Name = "TbPrize2ItemDesc2";
      this.TbPrize2ItemDesc2.ReadOnly = true;
      this.TbPrize2ItemDesc2.Size = new Size(168, 20);
      this.TbPrize2ItemDesc2.TabIndex = 234;
      this.TbPrize2ItemDesc3.BackColor = SystemColors.Menu;
      this.TbPrize2ItemDesc3.BorderStyle = BorderStyle.FixedSingle;
      this.TbPrize2ItemDesc3.ForeColor = Color.RoyalBlue;
      this.TbPrize2ItemDesc3.Location = new Point(291, 96);
      this.TbPrize2ItemDesc3.Name = "TbPrize2ItemDesc3";
      this.TbPrize2ItemDesc3.ReadOnly = true;
      this.TbPrize2ItemDesc3.Size = new Size(168, 20);
      this.TbPrize2ItemDesc3.TabIndex = 233;
      this.TbPrize2ItemDesc4.BackColor = SystemColors.Menu;
      this.TbPrize2ItemDesc4.BorderStyle = BorderStyle.FixedSingle;
      this.TbPrize2ItemDesc4.ForeColor = Color.RoyalBlue;
      this.TbPrize2ItemDesc4.Location = new Point(291, 133);
      this.TbPrize2ItemDesc4.Name = "TbPrize2ItemDesc4";
      this.TbPrize2ItemDesc4.ReadOnly = true;
      this.TbPrize2ItemDesc4.Size = new Size(168, 20);
      this.TbPrize2ItemDesc4.TabIndex = 232;
      this.TbPrize2ItemDesc5.BackColor = SystemColors.Menu;
      this.TbPrize2ItemDesc5.BorderStyle = BorderStyle.FixedSingle;
      this.TbPrize2ItemDesc5.ForeColor = Color.RoyalBlue;
      this.TbPrize2ItemDesc5.Location = new Point(291, 169);
      this.TbPrize2ItemDesc5.Name = "TbPrize2ItemDesc5";
      this.TbPrize2ItemDesc5.ReadOnly = true;
      this.TbPrize2ItemDesc5.Size = new Size(168, 20);
      this.TbPrize2ItemDesc5.TabIndex = 231;
      this.TbPrize2ItemDesc6.BackColor = SystemColors.Menu;
      this.TbPrize2ItemDesc6.BorderStyle = BorderStyle.FixedSingle;
      this.TbPrize2ItemDesc6.ForeColor = Color.RoyalBlue;
      this.TbPrize2ItemDesc6.Location = new Point(291, 205);
      this.TbPrize2ItemDesc6.Name = "TbPrize2ItemDesc6";
      this.TbPrize2ItemDesc6.ReadOnly = true;
      this.TbPrize2ItemDesc6.Size = new Size(168, 20);
      this.TbPrize2ItemDesc6.TabIndex = 230;
      this.TbPrize2ItemDesc7.BackColor = SystemColors.Menu;
      this.TbPrize2ItemDesc7.BorderStyle = BorderStyle.FixedSingle;
      this.TbPrize2ItemDesc7.ForeColor = Color.RoyalBlue;
      this.TbPrize2ItemDesc7.Location = new Point(291, 241);
      this.TbPrize2ItemDesc7.Name = "TbPrize2ItemDesc7";
      this.TbPrize2ItemDesc7.ReadOnly = true;
      this.TbPrize2ItemDesc7.Size = new Size(168, 20);
      this.TbPrize2ItemDesc7.TabIndex = 229;
      this.PbItem7.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbItem7.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbItem7.Location = new Point(462, 241);
      this.PbItem7.Name = "PbItem7";
      this.PbItem7.Size = new Size(22, 22);
      this.PbItem7.TabIndex = 228;
      this.PbItem7.TabStop = false;
      this.PbItem7.Click += new EventHandler(this.PbItem7_Click);
      this.PbItem6.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbItem6.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbItem6.Location = new Point(462, 207);
      this.PbItem6.Name = "PbItem6";
      this.PbItem6.Size = new Size(22, 22);
      this.PbItem6.TabIndex = 227;
      this.PbItem6.TabStop = false;
      this.PbItem6.Click += new EventHandler(this.PbItem6_Click);
      this.PbItem5.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbItem5.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbItem5.Location = new Point(462, 170);
      this.PbItem5.Name = "PbItem5";
      this.PbItem5.Size = new Size(22, 22);
      this.PbItem5.TabIndex = 226;
      this.PbItem5.TabStop = false;
      this.PbItem5.Click += new EventHandler(this.PbItem5_Click);
      this.PbItem4.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbItem4.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbItem4.Location = new Point(462, 134);
      this.PbItem4.Name = "PbItem4";
      this.PbItem4.Size = new Size(22, 22);
      this.PbItem4.TabIndex = 225;
      this.PbItem4.TabStop = false;
      this.PbItem4.Click += new EventHandler(this.PbItem4_Click);
      this.PbItem3.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbItem3.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbItem3.Location = new Point(462, 98);
      this.PbItem3.Name = "PbItem3";
      this.PbItem3.Size = new Size(22, 22);
      this.PbItem3.TabIndex = 224;
      this.PbItem3.TabStop = false;
      this.PbItem3.Click += new EventHandler(this.PbItem3_Click);
      this.PbItem2.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbItem2.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbItem2.Location = new Point(462, 62);
      this.PbItem2.Name = "PbItem2";
      this.PbItem2.Size = new Size(22, 22);
      this.PbItem2.TabIndex = 223;
      this.PbItem2.TabStop = false;
      this.PbItem2.Click += new EventHandler(this.PbItem2_Click);
      this.PbItem1.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbItem1.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbItem1.Location = new Point(462, 25);
      this.PbItem1.Name = "PbItem1";
      this.PbItem1.Size = new Size(22, 22);
      this.PbItem1.TabIndex = 222;
      this.PbItem1.TabStop = false;
      this.PbItem1.Click += new EventHandler(this.PbItem1_Click);
      this.textBox93.BorderStyle = BorderStyle.FixedSingle;
      this.textBox93.Location = new Point(511, 309);
      this.textBox93.Name = "textBox93";
      this.textBox93.Size = new Size(100, 20);
      this.textBox93.TabIndex = 221;
      this.textBox93.KeyPress += new KeyPressEventHandler(this.textBox93_KeyPress);
      this.label94.AutoSize = true;
      this.label94.Location = new Point(391, 313);
      this.label94.Name = "label94";
      this.label94.Size = new Size(77, 13);
      this.label94.TabIndex = 220;
      this.label94.Text = "Only Opt Prize:";
      this.textBox64.BorderStyle = BorderStyle.FixedSingle;
      this.textBox64.Location = new Point(197, 309);
      this.textBox64.Name = "textBox64";
      this.textBox64.Size = new Size(100, 20);
      this.textBox64.TabIndex = 218;
      this.textBox64.KeyPress += new KeyPressEventHandler(this.textBox64_KeyPress);
      this.label61.AutoSize = true;
      this.label61.Location = new Point(93, 313);
      this.label61.Name = "label61";
      this.label61.Size = new Size(67, 13);
      this.label61.TabIndex = 219;
      this.label61.Text = "Option Prize:";
      this.comboBox20.FlatStyle = FlatStyle.Popup;
      this.comboBox20.FormattingEnabled = true;
      this.comboBox20.Location = new Point(46, 243);
      this.comboBox20.Name = "comboBox20";
      this.comboBox20.Size = new Size(81, 21);
      this.comboBox20.TabIndex = 207;
      this.comboBox20.SelectedIndexChanged += new EventHandler(this.comboBox20_SelectedIndexChanged);
      this.comboBox20.SelectionChangeCommitted += new EventHandler(this.comboBox20_SelectionChangeCommitted);
      this.comboBox19.FlatStyle = FlatStyle.Popup;
      this.comboBox19.FormattingEnabled = true;
      this.comboBox19.Location = new Point(46, 207);
      this.comboBox19.Name = "comboBox19";
      this.comboBox19.Size = new Size(81, 21);
      this.comboBox19.TabIndex = 206;
      this.comboBox19.SelectedIndexChanged += new EventHandler(this.comboBox19_SelectedIndexChanged);
      this.comboBox19.SelectionChangeCommitted += new EventHandler(this.comboBox19_SelectionChangeCommitted);
      this.comboBox18.FlatStyle = FlatStyle.Popup;
      this.comboBox18.FormattingEnabled = true;
      this.comboBox18.Location = new Point(46, 171);
      this.comboBox18.Name = "comboBox18";
      this.comboBox18.Size = new Size(81, 21);
      this.comboBox18.TabIndex = 205;
      this.comboBox18.SelectedIndexChanged += new EventHandler(this.comboBox18_SelectedIndexChanged);
      this.comboBox18.SelectionChangeCommitted += new EventHandler(this.comboBox18_SelectionChangeCommitted);
      this.comboBox17.FlatStyle = FlatStyle.Popup;
      this.comboBox17.FormattingEnabled = true;
      this.comboBox17.Location = new Point(46, 135);
      this.comboBox17.Name = "comboBox17";
      this.comboBox17.Size = new Size(81, 21);
      this.comboBox17.TabIndex = 204;
      this.comboBox17.SelectedIndexChanged += new EventHandler(this.comboBox17_SelectedIndexChanged);
      this.comboBox17.SelectionChangeCommitted += new EventHandler(this.comboBox17_SelectionChangeCommitted);
      this.comboBox16.FlatStyle = FlatStyle.Popup;
      this.comboBox16.FormattingEnabled = true;
      this.comboBox16.Location = new Point(46, 98);
      this.comboBox16.Name = "comboBox16";
      this.comboBox16.Size = new Size(81, 21);
      this.comboBox16.TabIndex = 203;
      this.comboBox16.SelectedIndexChanged += new EventHandler(this.comboBox16_SelectedIndexChanged);
      this.comboBox16.SelectionChangeCommitted += new EventHandler(this.comboBox16_SelectionChangeCommitted);
      this.comboBox15.FlatStyle = FlatStyle.Popup;
      this.comboBox15.FormattingEnabled = true;
      this.comboBox15.Location = new Point(46, 63);
      this.comboBox15.Name = "comboBox15";
      this.comboBox15.Size = new Size(81, 21);
      this.comboBox15.TabIndex = 202;
      this.comboBox15.SelectedIndexChanged += new EventHandler(this.comboBox15_SelectedIndexChanged);
      this.comboBox15.SelectionChangeCommitted += new EventHandler(this.comboBox15_SelectionChangeCommitted);
      this.comboBox14.FlatStyle = FlatStyle.Popup;
      this.comboBox14.FormattingEnabled = true;
      this.comboBox14.Location = new Point(46, 27);
      this.comboBox14.Name = "comboBox14";
      this.comboBox14.Size = new Size(81, 21);
      this.comboBox14.TabIndex = 201;
      this.comboBox14.SelectedIndexChanged += new EventHandler(this.comboBox14_SelectedIndexChanged);
      this.comboBox14.SelectionChangeCommitted += new EventHandler(this.comboBox14_SelectionChangeCommitted);
      this.label67.AutoSize = true;
      this.label67.Location = new Point(6, 246);
      this.label67.Name = "label67";
      this.label67.Size = new Size(34, 13);
      this.label67.TabIndex = 200;
      this.label67.Text = "Type:";
      this.label68.AutoSize = true;
      this.label68.Location = new Point(6, 210);
      this.label68.Name = "label68";
      this.label68.Size = new Size(34, 13);
      this.label68.TabIndex = 199;
      this.label68.Text = "Type:";
      this.label66.AutoSize = true;
      this.label66.Location = new Point(6, 174);
      this.label66.Name = "label66";
      this.label66.Size = new Size(34, 13);
      this.label66.TabIndex = 194;
      this.label66.Text = "Type:";
      this.label65.AutoSize = true;
      this.label65.Location = new Point(6, 138);
      this.label65.Name = "label65";
      this.label65.Size = new Size(34, 13);
      this.label65.TabIndex = 193;
      this.label65.Text = "Type:";
      this.label64.AutoSize = true;
      this.label64.Location = new Point(6, 102);
      this.label64.Name = "label64";
      this.label64.Size = new Size(34, 13);
      this.label64.TabIndex = 192;
      this.label64.Text = "Type:";
      this.label63.AutoSize = true;
      this.label63.Location = new Point(6, 66);
      this.label63.Name = "label63";
      this.label63.Size = new Size(34, 13);
      this.label63.TabIndex = 191;
      this.label63.Text = "Type:";
      this.label62.AutoSize = true;
      this.label62.Location = new Point(6, 30);
      this.label62.Name = "label62";
      this.label62.Size = new Size(34, 13);
      this.label62.TabIndex = 190;
      this.label62.Text = "Type:";
      this.textBox79.BorderStyle = BorderStyle.FixedSingle;
      this.textBox79.Location = new Point(544, 27);
      this.textBox79.Name = "textBox79";
      this.textBox79.Size = new Size(85, 20);
      this.textBox79.TabIndex = 188;
      this.textBox79.KeyPress += new KeyPressEventHandler(this.textBox79_KeyPress);
      this.textBox80.BorderStyle = BorderStyle.FixedSingle;
      this.textBox80.Location = new Point(544, 63);
      this.textBox80.Name = "textBox80";
      this.textBox80.Size = new Size(85, 20);
      this.textBox80.TabIndex = 187;
      this.textBox80.KeyPress += new KeyPressEventHandler(this.textBox80_KeyPress);
      this.label76.AutoSize = true;
      this.label76.Location = new Point(490, 246);
      this.label76.Name = "label76";
      this.label76.Size = new Size(46, 13);
      this.label76.TabIndex = 186;
      this.label76.Text = "Amount:";
      this.label77.AutoSize = true;
      this.label77.Location = new Point(490, 210);
      this.label77.Name = "label77";
      this.label77.Size = new Size(46, 13);
      this.label77.TabIndex = 185;
      this.label77.Text = "Amount:";
      this.textBox81.BorderStyle = BorderStyle.FixedSingle;
      this.textBox81.Location = new Point(544, 98);
      this.textBox81.Name = "textBox81";
      this.textBox81.Size = new Size(85, 20);
      this.textBox81.TabIndex = 184;
      this.textBox81.KeyPress += new KeyPressEventHandler(this.textBox81_KeyPress);
      this.textBox82.BorderStyle = BorderStyle.FixedSingle;
      this.textBox82.Location = new Point(544, 135);
      this.textBox82.Name = "textBox82";
      this.textBox82.Size = new Size(85, 20);
      this.textBox82.TabIndex = 183;
      this.textBox82.KeyPress += new KeyPressEventHandler(this.textBox82_KeyPress);
      this.textBox83.BorderStyle = BorderStyle.FixedSingle;
      this.textBox83.Location = new Point(544, 171);
      this.textBox83.Name = "textBox83";
      this.textBox83.Size = new Size(85, 20);
      this.textBox83.TabIndex = 182;
      this.textBox83.KeyPress += new KeyPressEventHandler(this.textBox83_KeyPress);
      this.textBox84.BorderStyle = BorderStyle.FixedSingle;
      this.textBox84.Location = new Point(544, 207);
      this.textBox84.Name = "textBox84";
      this.textBox84.Size = new Size(85, 20);
      this.textBox84.TabIndex = 181;
      this.textBox84.KeyPress += new KeyPressEventHandler(this.textBox84_KeyPress);
      this.textBox85.BorderStyle = BorderStyle.FixedSingle;
      this.textBox85.Location = new Point(544, 243);
      this.textBox85.Name = "textBox85";
      this.textBox85.Size = new Size(85, 20);
      this.textBox85.TabIndex = 175;
      this.textBox85.KeyPress += new KeyPressEventHandler(this.textBox85_KeyPress);
      this.label78.AutoSize = true;
      this.label78.Location = new Point(490, 174);
      this.label78.Name = "label78";
      this.label78.Size = new Size(46, 13);
      this.label78.TabIndex = 180;
      this.label78.Text = "Amount:";
      this.label79.AutoSize = true;
      this.label79.Location = new Point(490, 138);
      this.label79.Name = "label79";
      this.label79.Size = new Size(46, 13);
      this.label79.TabIndex = 179;
      this.label79.Text = "Amount:";
      this.label80.AutoSize = true;
      this.label80.Location = new Point(490, 102);
      this.label80.Name = "label80";
      this.label80.Size = new Size(46, 13);
      this.label80.TabIndex = 178;
      this.label80.Text = "Amount:";
      this.label81.AutoSize = true;
      this.label81.Location = new Point(490, 66);
      this.label81.Name = "label81";
      this.label81.Size = new Size(46, 13);
      this.label81.TabIndex = 177;
      this.label81.Text = "Amount:";
      this.label82.AutoSize = true;
      this.label82.Location = new Point(490, 30);
      this.label82.Name = "label82";
      this.label82.Size = new Size(46, 13);
      this.label82.TabIndex = 176;
      this.label82.Text = "Amount:";
      this.textBox72.BorderStyle = BorderStyle.FixedSingle;
      this.textBox72.Location = new Point(189, 27);
      this.textBox72.Name = "textBox72";
      this.textBox72.Size = new Size(53, 20);
      this.textBox72.TabIndex = 174;
      this.textBox72.KeyPress += new KeyPressEventHandler(this.textBox72_KeyPress);
      this.textBox73.BorderStyle = BorderStyle.FixedSingle;
      this.textBox73.Location = new Point(189, 63);
      this.textBox73.Name = "textBox73";
      this.textBox73.Size = new Size(53, 20);
      this.textBox73.TabIndex = 173;
      this.textBox73.KeyPress += new KeyPressEventHandler(this.textBox73_KeyPress);
      this.label69.AutoSize = true;
      this.label69.Location = new Point(635, 246);
      this.label69.Name = "label69";
      this.label69.Size = new Size(56, 13);
      this.label69.TabIndex = 172;
      this.label69.Text = "Prize Plus:";
      this.label70.AutoSize = true;
      this.label70.Location = new Point(635, 210);
      this.label70.Name = "label70";
      this.label70.Size = new Size(56, 13);
      this.label70.TabIndex = 171;
      this.label70.Text = "Prize Plus:";
      this.textBox74.BorderStyle = BorderStyle.FixedSingle;
      this.textBox74.Location = new Point(189, 98);
      this.textBox74.Name = "textBox74";
      this.textBox74.Size = new Size(53, 20);
      this.textBox74.TabIndex = 170;
      this.textBox74.KeyPress += new KeyPressEventHandler(this.textBox74_KeyPress);
      this.textBox75.BorderStyle = BorderStyle.FixedSingle;
      this.textBox75.Location = new Point(189, 135);
      this.textBox75.Name = "textBox75";
      this.textBox75.Size = new Size(53, 20);
      this.textBox75.TabIndex = 169;
      this.textBox75.KeyPress += new KeyPressEventHandler(this.textBox75_KeyPress);
      this.textBox76.BorderStyle = BorderStyle.FixedSingle;
      this.textBox76.Location = new Point(189, 171);
      this.textBox76.Name = "textBox76";
      this.textBox76.Size = new Size(53, 20);
      this.textBox76.TabIndex = 168;
      this.textBox76.KeyPress += new KeyPressEventHandler(this.textBox76_KeyPress);
      this.textBox77.BorderStyle = BorderStyle.FixedSingle;
      this.textBox77.Location = new Point(189, 207);
      this.textBox77.Name = "textBox77";
      this.textBox77.Size = new Size(53, 20);
      this.textBox77.TabIndex = 167;
      this.textBox77.KeyPress += new KeyPressEventHandler(this.textBox77_KeyPress);
      this.textBox78.BorderStyle = BorderStyle.FixedSingle;
      this.textBox78.Location = new Point(189, 243);
      this.textBox78.Name = "textBox78";
      this.textBox78.Size = new Size(53, 20);
      this.textBox78.TabIndex = 161;
      this.textBox78.KeyPress += new KeyPressEventHandler(this.textBox78_KeyPress);
      this.label71.AutoSize = true;
      this.label71.Location = new Point(635, 174);
      this.label71.Name = "label71";
      this.label71.Size = new Size(56, 13);
      this.label71.TabIndex = 166;
      this.label71.Text = "Prize Plus:";
      this.label72.AutoSize = true;
      this.label72.Location = new Point(635, 138);
      this.label72.Name = "label72";
      this.label72.Size = new Size(56, 13);
      this.label72.TabIndex = 165;
      this.label72.Text = "Prize Plus:";
      this.label73.AutoSize = true;
      this.label73.Location = new Point(635, 102);
      this.label73.Name = "label73";
      this.label73.Size = new Size(56, 13);
      this.label73.TabIndex = 164;
      this.label73.Text = "Prize Plus:";
      this.label74.AutoSize = true;
      this.label74.Location = new Point(635, 66);
      this.label74.Name = "label74";
      this.label74.Size = new Size(56, 13);
      this.label74.TabIndex = 163;
      this.label74.Text = "Prize Plus:";
      this.label75.AutoSize = true;
      this.label75.Location = new Point(635, 30);
      this.label75.Name = "label75";
      this.label75.Size = new Size(56, 13);
      this.label75.TabIndex = 162;
      this.label75.Text = "Prize Plus:";
      this.textBox86.BorderStyle = BorderStyle.FixedSingle;
      this.textBox86.Location = new Point(700, 27);
      this.textBox86.Name = "textBox86";
      this.textBox86.Size = new Size(41, 20);
      this.textBox86.TabIndex = 113;
      this.textBox86.KeyPress += new KeyPressEventHandler(this.textBox86_KeyPress);
      this.textBox87.BorderStyle = BorderStyle.FixedSingle;
      this.textBox87.Location = new Point(700, 63);
      this.textBox87.Name = "textBox87";
      this.textBox87.Size = new Size(41, 20);
      this.textBox87.TabIndex = 112;
      this.textBox87.KeyPress += new KeyPressEventHandler(this.textBox87_KeyPress);
      this.textBox92.BorderStyle = BorderStyle.FixedSingle;
      this.textBox92.Location = new Point(700, 243);
      this.textBox92.Name = "textBox92";
      this.textBox92.Size = new Size(41, 20);
      this.textBox92.TabIndex = 100;
      this.textBox92.KeyPress += new KeyPressEventHandler(this.textBox92_KeyPress);
      this.label83.AutoSize = true;
      this.label83.Location = new Point(140, 246);
      this.label83.Name = "label83";
      this.label83.Size = new Size(44, 13);
      this.label83.TabIndex = 111;
      this.label83.Text = "Item ID:";
      this.label90.AutoSize = true;
      this.label90.Location = new Point(140, 30);
      this.label90.Name = "label90";
      this.label90.Size = new Size(44, 13);
      this.label90.TabIndex = 101;
      this.label90.Text = "Item ID:";
      this.label84.AutoSize = true;
      this.label84.Location = new Point(140, 210);
      this.label84.Name = "label84";
      this.label84.Size = new Size(44, 13);
      this.label84.TabIndex = 110;
      this.label84.Text = "Item ID:";
      this.label89.AutoSize = true;
      this.label89.Location = new Point(140, 66);
      this.label89.Name = "label89";
      this.label89.Size = new Size(44, 13);
      this.label89.TabIndex = 102;
      this.label89.Text = "Item ID:";
      this.textBox88.BorderStyle = BorderStyle.FixedSingle;
      this.textBox88.Location = new Point(700, 98);
      this.textBox88.Name = "textBox88";
      this.textBox88.Size = new Size(41, 20);
      this.textBox88.TabIndex = 109;
      this.textBox88.KeyPress += new KeyPressEventHandler(this.textBox88_KeyPress);
      this.label88.AutoSize = true;
      this.label88.Location = new Point(140, 102);
      this.label88.Name = "label88";
      this.label88.Size = new Size(44, 13);
      this.label88.TabIndex = 103;
      this.label88.Text = "Item ID:";
      this.textBox89.BorderStyle = BorderStyle.FixedSingle;
      this.textBox89.Location = new Point(700, 135);
      this.textBox89.Name = "textBox89";
      this.textBox89.Size = new Size(41, 20);
      this.textBox89.TabIndex = 108;
      this.textBox89.KeyPress += new KeyPressEventHandler(this.textBox89_KeyPress);
      this.label87.AutoSize = true;
      this.label87.Location = new Point(140, 138);
      this.label87.Name = "label87";
      this.label87.Size = new Size(44, 13);
      this.label87.TabIndex = 104;
      this.label87.Text = "Item ID:";
      this.textBox90.BorderStyle = BorderStyle.FixedSingle;
      this.textBox90.Location = new Point(700, 171);
      this.textBox90.Name = "textBox90";
      this.textBox90.Size = new Size(41, 20);
      this.textBox90.TabIndex = 107;
      this.textBox90.KeyPress += new KeyPressEventHandler(this.textBox90_KeyPress);
      this.label86.AutoSize = true;
      this.label86.Location = new Point(140, 174);
      this.label86.Name = "label86";
      this.label86.Size = new Size(44, 13);
      this.label86.TabIndex = 105;
      this.label86.Text = "Item ID:";
      this.textBox91.BorderStyle = BorderStyle.FixedSingle;
      this.textBox91.Location = new Point(700, 207);
      this.textBox91.Name = "textBox91";
      this.textBox91.Size = new Size(41, 20);
      this.textBox91.TabIndex = 106;
      this.textBox91.KeyPress += new KeyPressEventHandler(this.textBox91_KeyPress);
      this.textBox69.Location = new Point(38, 543);
      this.textBox69.Name = "textBox69";
      this.textBox69.Size = new Size(41, 20);
      this.textBox69.TabIndex = 211;
      this.textBox69.Visible = false;
      this.textBox70.Location = new Point(85, 439);
      this.textBox70.Name = "textBox70";
      this.textBox70.Size = new Size(41, 20);
      this.textBox70.TabIndex = 210;
      this.textBox70.Visible = false;
      this.textBox68.Location = new Point(38, 517);
      this.textBox68.Name = "textBox68";
      this.textBox68.Size = new Size(41, 20);
      this.textBox68.TabIndex = 212;
      this.textBox68.Visible = false;
      this.textBox65.Location = new Point(38, 439);
      this.textBox65.Name = "textBox65";
      this.textBox65.Size = new Size(41, 20);
      this.textBox65.TabIndex = 214;
      this.textBox65.Visible = false;
      this.textBox71.Location = new Point(85, 465);
      this.textBox71.Name = "textBox71";
      this.textBox71.Size = new Size(41, 20);
      this.textBox71.TabIndex = 209;
      this.textBox71.Visible = false;
      this.textBox67.Location = new Point(38, 491);
      this.textBox67.Name = "textBox67";
      this.textBox67.Size = new Size(41, 20);
      this.textBox67.TabIndex = 208;
      this.textBox67.Visible = false;
      this.textBox53.Location = new Point(132, 585);
      this.textBox53.Name = "textBox53";
      this.textBox53.Size = new Size(56, 20);
      this.textBox53.TabIndex = 76;
      this.textBox53.Visible = false;
      this.textBox66.Location = new Point(38, 465);
      this.textBox66.Name = "textBox66";
      this.textBox66.Size = new Size(41, 20);
      this.textBox66.TabIndex = 213;
      this.textBox66.Visible = false;
      this.textBox52.Location = new Point(132, 546);
      this.textBox52.Name = "textBox52";
      this.textBox52.Size = new Size(56, 20);
      this.textBox52.TabIndex = 75;
      this.textBox52.Visible = false;
      this.textBox49.Location = new Point(132, 439);
      this.textBox49.Name = "textBox49";
      this.textBox49.Size = new Size(56, 20);
      this.textBox49.TabIndex = 72;
      this.textBox49.Visible = false;
      this.textBox51.Location = new Point(132, 509);
      this.textBox51.Name = "textBox51";
      this.textBox51.Size = new Size(56, 20);
      this.textBox51.TabIndex = 74;
      this.textBox51.Visible = false;
      this.textBox50.Location = new Point(132, 474);
      this.textBox50.Name = "textBox50";
      this.textBox50.Size = new Size(56, 20);
      this.textBox50.TabIndex = 73;
      this.textBox50.Visible = false;
      this.tabPage7.BackColor = SystemColors.Control;
      this.tabPage7.Controls.Add((Control) this.groupBox7);
      this.tabPage7.Location = new Point(4, 22);
      this.tabPage7.Name = "tabPage7";
      this.tabPage7.Padding = new Padding(3);
      this.tabPage7.Size = new Size(765, 610);
      this.tabPage7.TabIndex = 6;
      this.tabPage7.Text = "Other";
      this.groupBox7.Controls.Add((Control) this.textBox103);
      this.groupBox7.Controls.Add((Control) this.label103);
      this.groupBox7.Controls.Add((Control) this.textBox102);
      this.groupBox7.Controls.Add((Control) this.label102);
      this.groupBox7.Controls.Add((Control) this.label99);
      this.groupBox7.Controls.Add((Control) this.textBox100);
      this.groupBox7.Controls.Add((Control) this.textBox97);
      this.groupBox7.Controls.Add((Control) this.label97);
      this.groupBox7.Controls.Add((Control) this.textBox101);
      this.groupBox7.Controls.Add((Control) this.label101);
      this.groupBox7.Controls.Add((Control) this.textBox99);
      this.groupBox7.Controls.Add((Control) this.label100);
      this.groupBox7.Location = new Point(6, 6);
      this.groupBox7.Name = "groupBox7";
      this.groupBox7.Size = new Size(389, 248);
      this.groupBox7.TabIndex = 91;
      this.groupBox7.TabStop = false;
      this.groupBox7.Text = "Other";
      this.textBox103.BorderStyle = BorderStyle.FixedSingle;
      this.textBox103.Location = new Point(123, 181);
      this.textBox103.Name = "textBox103";
      this.textBox103.Size = new Size(83, 20);
      this.textBox103.TabIndex = 241;
      this.label103.AutoSize = true;
      this.label103.Location = new Point(7, 184);
      this.label103.Name = "label103";
      this.label103.Size = new Size(61, 13);
      this.label103.TabIndex = 240;
      this.label103.Text = "Quest Flag:";
      this.textBox102.BorderStyle = BorderStyle.FixedSingle;
      this.textBox102.Location = new Point(123, 148);
      this.textBox102.Name = "textBox102";
      this.textBox102.Size = new Size(83, 20);
      this.textBox102.TabIndex = 239;
      this.label102.AutoSize = true;
      this.label102.Location = new Point(7, 152);
      this.label102.Name = "label102";
      this.label102.Size = new Size(82, 13);
      this.label102.TabIndex = 238;
      this.label102.Text = "Start Trigger ID:";
      this.label99.AutoSize = true;
      this.label99.Location = new Point(7, 93);
      this.label99.Name = "label99";
      this.label99.Size = new Size(109, 13);
      this.label99.TabIndex = 237;
      this.label99.Text = "Start Give KindCount:";
      this.textBox100.BorderStyle = BorderStyle.FixedSingle;
      this.textBox100.Location = new Point(123, 86);
      this.textBox100.Name = "textBox100";
      this.textBox100.Size = new Size(100, 20);
      this.textBox100.TabIndex = 236;
      this.textBox97.BorderStyle = BorderStyle.FixedSingle;
      this.textBox97.Location = new Point(123, 116);
      this.textBox97.Name = "textBox97";
      this.textBox97.Size = new Size(100, 20);
      this.textBox97.TabIndex = 235;
      this.label97.AutoSize = true;
      this.label97.Location = new Point(7, 123);
      this.label97.Name = "label97";
      this.label97.Size = new Size(56, 13);
      this.label97.TabIndex = 234;
      this.label97.Text = "Fail Value:";
      this.textBox101.BorderStyle = BorderStyle.FixedSingle;
      this.textBox101.Location = new Point(123, 56);
      this.textBox101.Name = "textBox101";
      this.textBox101.Size = new Size(100, 20);
      this.textBox101.TabIndex = 221;
      this.label101.AutoSize = true;
      this.label101.Location = new Point(7, 60);
      this.label101.Name = "label101";
      this.label101.Size = new Size(82, 13);
      this.label101.TabIndex = 220;
      this.label101.Text = "Start Give Num:";
      this.textBox99.BorderStyle = BorderStyle.FixedSingle;
      this.textBox99.Location = new Point(123, 25);
      this.textBox99.Name = "textBox99";
      this.textBox99.Size = new Size(100, 20);
      this.textBox99.TabIndex = 219;
      this.label100.AutoSize = true;
      this.label100.Location = new Point(7, 32);
      this.label100.Name = "label100";
      this.label100.Size = new Size(80, 13);
      this.label100.TabIndex = 216;
      this.label100.Text = "Start Give Item:";
      this.button7.FlatStyle = FlatStyle.Flat;
      this.button7.Location = new Point(837, 665);
      this.button7.Name = "button7";
      this.button7.Size = new Size(100, 28);
      this.button7.TabIndex = 37;
      this.button7.Text = "Save";
      this.button7.UseVisualStyleBackColor = true;
      this.button7.Click += new EventHandler(this.button7_Click);
      this.label113.AutoSize = true;
      this.label113.BackColor = SystemColors.ControlLightLight;
      this.label113.Font = new Font("Microsoft Sans Serif", 9.75f, FontStyle.Bold, GraphicsUnit.Point, (byte) 0);
      this.label113.Location = new Point(784, 5);
      this.label113.Name = "label113";
      this.label113.Size = new Size(154, 16);
      this.label113.TabIndex = 38;
      this.label113.Text = "Current Language is :";
      this.lblLang.AutoSize = true;
      this.lblLang.BackColor = SystemColors.ControlLightLight;
      this.lblLang.Font = new Font("Microsoft Sans Serif", 9.75f, FontStyle.Bold, GraphicsUnit.Point, (byte) 0);
      this.lblLang.ForeColor = Color.Chartreuse;
      this.lblLang.Location = new Point(941, 6);
      this.lblLang.Name = "lblLang";
      this.lblLang.Size = new Size(0, 16);
      this.lblLang.TabIndex = 103;
      this.label119.AutoSize = true;
      this.label119.BackColor = SystemColors.Control;
      this.label119.Location = new Point(12, 665);
      this.label119.Name = "label119";
      this.label119.Size = new Size(52, 13);
      this.label119.TabIndex = 104;
      this.label119.Text = "ColorKey:";
      this.pictureBox1.BackColor = Color.LimeGreen;
      this.pictureBox1.Location = new Point(96, 665);
      this.pictureBox1.Name = "pictureBox1";
      this.pictureBox1.Size = new Size(20, 15);
      this.pictureBox1.TabIndex = 105;
      this.pictureBox1.TabStop = false;
      this.label120.AutoSize = true;
      this.label120.BackColor = SystemColors.Control;
      this.label120.Location = new Point(62, 665);
      this.label120.Name = "label120";
      this.label120.Size = new Size(32, 13);
      this.label120.TabIndex = 106;
      this.label120.Text = "NPC:";
      this.label121.AutoSize = true;
      this.label121.BackColor = SystemColors.Control;
      this.label121.Location = new Point(118, 665);
      this.label121.Name = "label121";
      this.label121.Size = new Size(34, 13);
      this.label121.TabIndex = 108;
      this.label121.Text = "MOB:";
      this.pictureBox2.BackColor = Color.Red;
      this.pictureBox2.Location = new Point(154, 665);
      this.pictureBox2.Name = "pictureBox2";
      this.pictureBox2.Size = new Size(20, 15);
      this.pictureBox2.TabIndex = 107;
      this.pictureBox2.TabStop = false;
      this.label122.AutoSize = true;
      this.label122.BackColor = SystemColors.Control;
      this.label122.Location = new Point(182, 665);
      this.label122.Name = "label122";
      this.label122.Size = new Size(36, 13);
      this.label122.TabIndex = 110;
      this.label122.Text = "ITEM:";
      this.pictureBox3.BackColor = Color.RoyalBlue;
      this.pictureBox3.Location = new Point(218, 665);
      this.pictureBox3.Name = "pictureBox3";
      this.pictureBox3.Size = new Size(20, 15);
      this.pictureBox3.TabIndex = 109;
      this.pictureBox3.TabStop = false;
      this.btnSaveAndNext.FlatStyle = FlatStyle.Flat;
      this.btnSaveAndNext.Location = new Point(952, 665);
      this.btnSaveAndNext.Name = "btnSaveAndNext";
      this.btnSaveAndNext.Size = new Size(100, 28);
      this.btnSaveAndNext.TabIndex = 111;
      this.btnSaveAndNext.Text = "Save and Next";
      this.btnSaveAndNext.UseVisualStyleBackColor = true;
      this.btnSaveAndNext.Click += new EventHandler(this.btnSaveAndNext_Click);
      this.ClientSize = new Size(1056, 699);
      this.Controls.Add((Control) this.btnSaveAndNext);
      this.Controls.Add((Control) this.label122);
      this.Controls.Add((Control) this.pictureBox3);
      this.Controls.Add((Control) this.label121);
      this.Controls.Add((Control) this.pictureBox2);
      this.Controls.Add((Control) this.label120);
      this.Controls.Add((Control) this.pictureBox1);
      this.Controls.Add((Control) this.label119);
      this.Controls.Add((Control) this.lblLang);
      this.Controls.Add((Control) this.label113);
      this.Controls.Add((Control) this.tabControl1);
      this.Controls.Add((Control) this.groupBox5);
      this.Controls.Add((Control) this.groupBox3);
      this.Controls.Add((Control) this.menuStrip1);
      this.Controls.Add((Control) this.button7);
      this.Icon = (Icon) componentResourceManager.GetObject("$this.Icon");
      this.MainMenuStrip = this.menuStrip1;
      this.MaximizeBox = false;
      this.Name = nameof (QuestEditor);
      this.StartPosition = FormStartPosition.CenterScreen;
      this.Text = "Quest Editor EP4";
      this.Load += new EventHandler(this.Form3_Load);
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.groupBox3.ResumeLayout(false);
      this.groupBox5.ResumeLayout(false);
      this.groupBox5.PerformLayout();
      this.tabControl1.ResumeLayout(false);
      this.tabPage1.ResumeLayout(false);
      this.tabPage1.PerformLayout();
      this.groupBox8.ResumeLayout(false);
      this.groupBox8.PerformLayout();
      this.groupBox11.ResumeLayout(false);
      this.groupBox11.PerformLayout();
      ((ISupportInitialize) this.PbEndNPCItem).EndInit();
      ((ISupportInitialize) this.PbStartItemNPC).EndInit();
      this.groupBox10.ResumeLayout(false);
      this.groupBox10.PerformLayout();
      this.groupBox9.ResumeLayout(false);
      this.groupBox9.PerformLayout();
      this.groupBox4.ResumeLayout(false);
      this.groupBox4.PerformLayout();
      ((ISupportInitialize) this.PbItemNeed5).EndInit();
      ((ISupportInitialize) this.PbItemNeed4).EndInit();
      ((ISupportInitialize) this.PbItemNeed3).EndInit();
      ((ISupportInitialize) this.PbItemNeed2).EndInit();
      ((ISupportInitialize) this.PbItemNeed1).EndInit();
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.tabPage3.ResumeLayout(false);
      this.tabControl2.ResumeLayout(false);
      this.tabPage2.ResumeLayout(false);
      this.tabPage2.PerformLayout();
      ((ISupportInitialize) this.PbCond1).EndInit();
      this.groupBox2.ResumeLayout(false);
      this.groupBox2.PerformLayout();
      ((ISupportInitialize) this.PbObj1NpcID3).EndInit();
      ((ISupportInitialize) this.PbObj1NpcID2).EndInit();
      ((ISupportInitialize) this.PbObj1NpcID1).EndInit();
      this.tabPage4.ResumeLayout(false);
      this.tabPage4.PerformLayout();
      ((ISupportInitialize) this.PbCond2).EndInit();
      this.groupBox12.ResumeLayout(false);
      this.groupBox12.PerformLayout();
      ((ISupportInitialize) this.PbObj2NpcID3).EndInit();
      ((ISupportInitialize) this.PbObj2NpcID2).EndInit();
      ((ISupportInitialize) this.PbObj2NpcID1).EndInit();
      this.tabPage5.ResumeLayout(false);
      this.tabPage5.PerformLayout();
      ((ISupportInitialize) this.PbCond3).EndInit();
      this.groupBox6.ResumeLayout(false);
      this.groupBox6.PerformLayout();
      ((ISupportInitialize) this.PbNpcID3).EndInit();
      ((ISupportInitialize) this.PbNpcID2).EndInit();
      ((ISupportInitialize) this.PbNpcID1).EndInit();
      this.Page2.ResumeLayout(false);
      this.Page2.PerformLayout();
      this.tabControl3.ResumeLayout(false);
      this.tabPage8.ResumeLayout(false);
      this.tabPage8.PerformLayout();
      ((ISupportInitialize) this.pictureBox15).EndInit();
      ((ISupportInitialize) this.pictureBox14).EndInit();
      ((ISupportInitialize) this.pictureBox13).EndInit();
      ((ISupportInitialize) this.pictureBox12).EndInit();
      ((ISupportInitialize) this.pictureBox11).EndInit();
      ((ISupportInitialize) this.PbPItem5).EndInit();
      ((ISupportInitialize) this.PbPItem4).EndInit();
      ((ISupportInitialize) this.PbPItem3).EndInit();
      ((ISupportInitialize) this.PbPItem2).EndInit();
      ((ISupportInitialize) this.PbPItem1).EndInit();
      this.tabPage9.ResumeLayout(false);
      this.tabPage9.PerformLayout();
      ((ISupportInitialize) this.pictureBox10).EndInit();
      ((ISupportInitialize) this.pictureBox9).EndInit();
      ((ISupportInitialize) this.pictureBox8).EndInit();
      ((ISupportInitialize) this.pictureBox7).EndInit();
      ((ISupportInitialize) this.pictureBox6).EndInit();
      ((ISupportInitialize) this.pictureBox5).EndInit();
      ((ISupportInitialize) this.pictureBox4).EndInit();
      ((ISupportInitialize) this.PbItem7).EndInit();
      ((ISupportInitialize) this.PbItem6).EndInit();
      ((ISupportInitialize) this.PbItem5).EndInit();
      ((ISupportInitialize) this.PbItem4).EndInit();
      ((ISupportInitialize) this.PbItem3).EndInit();
      ((ISupportInitialize) this.PbItem2).EndInit();
      ((ISupportInitialize) this.PbItem1).EndInit();
      this.tabPage7.ResumeLayout(false);
      this.groupBox7.ResumeLayout(false);
      this.groupBox7.PerformLayout();
      ((ISupportInitialize) this.pictureBox1).EndInit();
      ((ISupportInitialize) this.pictureBox2).EndInit();
      ((ISupportInitialize) this.pictureBox3).EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();
    }

    private void CbRvrType_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox26.Text = this.CbRvrType.SelectedIndex.ToString();
      if (this.textBox26.Text == "1")
      {
        this.CbRvRGrade.Visible = true;
        this.CbRvRGrade1.Visible = false;
      }
      else
      {
        if (!(this.textBox26.Text == "2"))
          return;
        this.CbRvRGrade.Visible = false;
        this.CbRvRGrade1.Visible = true;
      }
    }

    private void CbRvRGrade1_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (!(this.textBox26.Text == "2"))
        return;
      this.textBox27.Text = this.GetIndexByComboBox(this.CbRvRGrade1.Text).ToString();
    }

    private void CbRvRGrade_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (!(this.textBox26.Text == "2"))
        return;
      this.textBox27.Text = this.GetIndexByComboBox(this.CbRvRGrade.Text).ToString();
    }

    private void BtnCopy_Click(object sender, EventArgs e)
    {
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DROP TABLE IF EXISTS tempTable;CREATE TEMPORARY TABLE tempTable ENGINE=MyISAM SELECT * FROM t_quest WHERE a_index=" + this.textBox1.Text + ";SELECT a_index FROM tempTable;UPDATE tempTable SET a_index=(SELECT a_index from t_quest ORDER BY a_index DESC LIMIT 1)+1; SELECT a_index FROM tempTable;INSERT INTO t_quest SELECT * FROM tempTable;");
      this.LoadListBox();
      this.listBox1.SelectedIndex = this.listBox1.Items.Count - 1;
      int num = (int) new CustomMessage("Copying Complete").ShowDialog();
    }

    private void PbItem1_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox72.Text = itemPicker.ItemIndex.ToString();
      this.TbPrize2ItemDesc1.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox72.Text));
      this.textBox72.BackColor = Color.LightBlue;
    }

    private void PbItem2_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox73.Text = itemPicker.ItemIndex.ToString();
      this.TbPrize2ItemDesc2.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox73.Text));
      this.textBox73.BackColor = Color.LightBlue;
    }

    private void PbItem3_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox74.Text = itemPicker.ItemIndex.ToString();
      this.TbPrize2ItemDesc3.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox74.Text));
      this.textBox74.BackColor = Color.LightBlue;
    }

    private void PbItem4_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox75.Text = itemPicker.ItemIndex.ToString();
      this.TbPrize2ItemDesc4.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox75.Text));
      this.textBox75.BackColor = Color.LightBlue;
    }

    private void PbItem5_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox76.Text = itemPicker.ItemIndex.ToString();
      this.TbPrize2ItemDesc5.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox76.Text));
      this.textBox76.BackColor = Color.LightBlue;
    }

    private void PbItem6_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox77.Text = itemPicker.ItemIndex.ToString();
      this.TbPrize2ItemDesc6.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox77.Text));
      this.textBox77.BackColor = Color.LightBlue;
    }

    private void PbItem7_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox78.Text = itemPicker.ItemIndex.ToString();
      this.TbPrize2ItemDesc7.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox78.Text));
      this.textBox78.BackColor = Color.LightBlue;
    }

    private void PbPItem1_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox54.Text = itemPicker.ItemIndex.ToString();
      this.tbItemDesc1.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox54.Text));
      this.textBox54.BackColor = Color.LightBlue;
    }

    private void PbPItem2_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox55.Text = itemPicker.ItemIndex.ToString();
      this.tbItemDesc2.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox55.Text));
      this.textBox55.BackColor = Color.LightBlue;
    }

    private void PbPItem3_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox56.Text = itemPicker.ItemIndex.ToString();
      this.tbItemDesc3.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox56.Text));
      this.textBox56.BackColor = Color.LightBlue;
    }

    private void PbPItem4_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox57.Text = itemPicker.ItemIndex.ToString();
      this.tbItemDesc4.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox57.Text));
      this.textBox57.BackColor = Color.LightBlue;
    }

    private void PbPItem5_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox58.Text = itemPicker.ItemIndex.ToString();
      this.tbItemDesc5.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox58.Text));
      this.textBox58.BackColor = Color.LightBlue;
    }

    private void PbCond1_Click(object sender, EventArgs e)
    {
      if (this.textBox28.Text == "0")
      {
        MobPicker mobPicker = new MobPicker();
        if (mobPicker.ShowDialog() != DialogResult.OK)
          return;
        this.textBox31.Text = mobPicker.MobIndex.ToString();
        this.TbObj1.Text = this.databaseHandle.MobNameFast(Convert.ToInt32(this.textBox31.Text));
        this.textBox31.BackColor = Color.LightBlue;
      }
      else
      {
        ItemPicker itemPicker = new ItemPicker();
        if (itemPicker.ShowDialog() != DialogResult.OK)
          return;
        this.textBox31.Text = itemPicker.ItemIndex.ToString();
        this.TbObj1.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox31.Text));
        this.textBox31.BackColor = Color.LightBlue;
      }
    }

    private void PbCond2_Click(object sender, EventArgs e)
    {
      if (this.textBox28.Text == "0")
      {
        MobPicker mobPicker = new MobPicker();
        if (mobPicker.ShowDialog() != DialogResult.OK)
          return;
        this.textBox32.Text = mobPicker.MobIndex.ToString();
        this.TbObj2.Text = this.databaseHandle.MobNameFast(Convert.ToInt32(this.textBox32.Text));
        this.textBox32.BackColor = Color.LightBlue;
      }
      else
      {
        ItemPicker itemPicker = new ItemPicker();
        if (itemPicker.ShowDialog() != DialogResult.OK)
          return;
        this.textBox32.Text = itemPicker.ItemIndex.ToString();
        this.TbObj2.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox32.Text));
        this.textBox32.BackColor = Color.LightBlue;
      }
    }

    private void PbCond3_Click(object sender, EventArgs e)
    {
      if (this.textBox28.Text == "0")
      {
        MobPicker mobPicker = new MobPicker();
        if (mobPicker.ShowDialog() != DialogResult.OK)
          return;
        this.textBox33.Text = mobPicker.MobIndex.ToString();
        this.TbObj3.Text = this.databaseHandle.MobNameFast(Convert.ToInt32(this.textBox33.Text));
        this.textBox33.BackColor = Color.LightBlue;
      }
      else
      {
        ItemPicker itemPicker = new ItemPicker();
        if (itemPicker.ShowDialog() != DialogResult.OK)
          return;
        this.textBox33.Text = itemPicker.ItemIndex.ToString();
        this.TbObj3.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox33.Text));
        this.textBox33.BackColor = Color.LightBlue;
      }
    }

    private void PbNpcID1_Click(object sender, EventArgs e)
    {
      MobPicker mobPicker = new MobPicker();
      if (mobPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox45.Text = mobPicker.MobIndex.ToString();
      this.TbObjNpc1.Text = this.databaseHandle.MobNameFast(Convert.ToInt32(this.textBox45.Text));
      this.textBox45.BackColor = Color.LightBlue;
    }

    private void PbNpcID2_Click(object sender, EventArgs e)
    {
      MobPicker mobPicker = new MobPicker();
      if (mobPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox46.Text = mobPicker.MobIndex.ToString();
      this.TbObjNpc2.Text = this.databaseHandle.MobNameFast(Convert.ToInt32(this.textBox46.Text));
      this.textBox46.BackColor = Color.LightBlue;
    }

    private void PbNpcID3_Click(object sender, EventArgs e)
    {
      MobPicker mobPicker = new MobPicker();
      if (mobPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox47.Text = mobPicker.MobIndex.ToString();
      this.TbObjNpc3.Text = this.databaseHandle.MobNameFast(Convert.ToInt32(this.textBox47.Text));
      this.textBox47.BackColor = Color.LightBlue;
    }

    private void PbObj1NpcID1_Click(object sender, EventArgs e)
    {
      MobPicker mobPicker = new MobPicker();
      if (mobPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox37.Text = mobPicker.MobIndex.ToString();
      this.TbObj1Npc1.Text = this.databaseHandle.MobNameFast(Convert.ToInt32(this.textBox37.Text));
      this.textBox37.BackColor = Color.LightBlue;
    }

    private void PbObj1NpcID2_Click(object sender, EventArgs e)
    {
      MobPicker mobPicker = new MobPicker();
      if (mobPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox38.Text = mobPicker.MobIndex.ToString();
      this.TbObj1Npc2.Text = this.databaseHandle.MobNameFast(Convert.ToInt32(this.textBox38.Text));
      this.textBox38.BackColor = Color.LightBlue;
    }

    private void PbObj1NpcID3_Click(object sender, EventArgs e)
    {
      MobPicker mobPicker = new MobPicker();
      if (mobPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox39.Text = mobPicker.MobIndex.ToString();
      this.TbObj1Npc3.Text = this.databaseHandle.MobNameFast(Convert.ToInt32(this.textBox39.Text));
      this.textBox39.BackColor = Color.LightBlue;
    }

    private void PbObj2NpcID1_Click(object sender, EventArgs e)
    {
      MobPicker mobPicker = new MobPicker();
      if (mobPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox41.Text = mobPicker.MobIndex.ToString();
      this.TbObj2Npc1.Text = this.databaseHandle.MobNameFast(Convert.ToInt32(this.textBox41.Text));
      this.textBox41.BackColor = Color.LightBlue;
    }

    private void PbObj2NpcID2_Click(object sender, EventArgs e)
    {
      MobPicker mobPicker = new MobPicker();
      if (mobPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox42.Text = mobPicker.MobIndex.ToString();
      this.TbObj2Npc2.Text = this.databaseHandle.MobNameFast(Convert.ToInt32(this.textBox42.Text));
      this.textBox42.BackColor = Color.LightBlue;
    }

    private void PbObj2NpcID3_Click(object sender, EventArgs e)
    {
      MobPicker mobPicker = new MobPicker();
      if (mobPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox43.Text = mobPicker.MobIndex.ToString();
      this.TbObj2Npc3.Text = this.databaseHandle.MobNameFast(Convert.ToInt32(this.textBox43.Text));
      this.textBox43.BackColor = Color.LightBlue;
    }

    private void PbStartItemNPC_Click(object sender, EventArgs e)
    {
      if (this.textBox7.Text == "0")
      {
        MobPicker mobPicker = new MobPicker();
        if (mobPicker.ShowDialog() != DialogResult.OK)
          return;
        this.textBox8.Text = mobPicker.MobIndex.ToString();
        this.TbEndNpcName.Text = this.databaseHandle.MobNameFast(Convert.ToInt32(this.textBox8.Text));
        this.textBox8.BackColor = Color.LightBlue;
      }
      else
      {
        if (!(this.textBox7.Text == "1"))
          return;
        ItemPicker itemPicker = new ItemPicker();
        if (itemPicker.ShowDialog() != DialogResult.OK)
          return;
        this.textBox8.Text = itemPicker.ItemIndex.ToString();
        this.TbEndNpcName.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox8.Text));
        this.textBox8.BackColor = Color.LightBlue;
      }
    }

    private void PbEndNPCItem_Click(object sender, EventArgs e)
    {
      MobPicker mobPicker = new MobPicker();
      if (mobPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox10.Text = mobPicker.MobIndex.ToString();
      this.TbEndNpcName.Text = this.databaseHandle.MobNameFast(Convert.ToInt32(this.textBox10.Text));
      this.textBox10.BackColor = Color.LightBlue;
    }

    private void PbItemNeed1_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox16.Text = itemPicker.ItemIndex.ToString();
      this.TbNeedName1.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox16.Text));
      this.textBox16.BackColor = Color.LightBlue;
    }

    private void PbItemNeed2_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox17.Text = itemPicker.ItemIndex.ToString();
      this.TbNeedName2.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox17.Text));
      this.textBox17.BackColor = Color.LightBlue;
    }

    private void PbItemNeed3_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox18.Text = itemPicker.ItemIndex.ToString();
      this.TbNeedName3.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox18.Text));
      this.textBox18.BackColor = Color.LightBlue;
    }

    private void PbItemNeed4_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox19.Text = itemPicker.ItemIndex.ToString();
      this.TbNeedName4.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox19.Text));
      this.textBox19.BackColor = Color.LightBlue;
    }

    private void PbItemNeed5_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox20.Text = itemPicker.ItemIndex.ToString();
      this.TbNeedName5.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox20.Text));
      this.textBox20.BackColor = Color.LightBlue;
    }

    private void cbEnabled_CheckedChanged(object sender, EventArgs e)
    {
      if (this.cbEnabled.Checked)
      {
        this.cbEnabled.BackColor = Color.Chartreuse;
        this.textBox5.Text = "1";
      }
      else
      {
        if (this.cbEnabled.Checked)
          return;
        this.cbEnabled.BackColor = Color.Red;
        this.textBox5.Text = "0";
      }
    }

    private void textBox5_TextChanged(object sender, EventArgs e)
    {
      if (this.textBox5.Text == "1")
      {
        this.cbEnabled.Checked = true;
      }
      else
      {
        if (!(this.textBox5.Text == "0"))
          return;
        this.cbEnabled.Checked = false;
      }
    }

    private void btnSaveAndNext_Click(object sender, EventArgs e)
    {
      this.namee = this.StringFromLanguage();
      this.desc = this.DescrFromLanguage();
      this.desc2 = this.Descr2FromLanguage();
      this.desc3 = this.Descr3FromLanguage();
      string str1 = "UPDATE t_quest SET a_index = '" + this.textBox1.Text + "', ";
      string str2 = this.textBox2.Text.Replace("'", "\\'").Replace("\"", "\\\"");
      string str3 = str1 + "a_name = '" + str2 + "', " + this.namee + " = '" + str2 + "', a_type1 = '" + this.textBox3.Text + "', a_type2 = '" + this.textBox4.Text + "', a_enable = '" + this.textBox5.Text + "', a_prequest_num = '" + this.textBox6.Text + "', a_start_type = '" + this.textBox7.Text + "', a_start_data = '" + this.textBox8.Text + "', a_start_npc_zone_num = '" + this.textBox9.Text + "', a_prize_npc = '" + this.textBox10.Text + "', a_prize_npc_zone_num = '" + this.textBox11.Text + "', a_need_exp = '" + this.textBox12.Text + "', a_need_min_level = '" + this.textBox13.Text + "', a_need_max_level = '" + this.textBox14.Text + "', a_need_job = '" + this.textBox15.Text + "', a_need_item0 = '" + this.textBox16.Text + "', a_need_item1 = '" + this.textBox17.Text + "', a_need_item2 = '" + this.textBox18.Text + "', a_need_item3 = '" + this.textBox19.Text + "', a_need_item4 = '" + this.textBox20.Text + "', a_need_item_count0 = '" + this.textBox21.Text + "', a_need_item_count1 = '" + this.textBox22.Text + "', a_need_item_count2 = '" + this.textBox23.Text + "', a_need_item_count3 = '" + this.textBox24.Text + "', a_need_item_count4 = '" + this.textBox25.Text + "', a_need_rvr_type = '" + this.textBox26.Text + "', a_need_rvr_grade = '" + this.textBox27.Text + "', a_condition0_type = '" + this.textBox28.Text + "', a_condition1_type = '" + this.textBox29.Text + "', a_condition2_type = '" + this.textBox30.Text + "', a_condition0_index = '" + this.textBox31.Text + "', a_condition1_index = '" + this.textBox32.Text + "', a_condition2_index = '" + this.textBox33.Text + "', a_condition0_num = '" + this.textBox34.Text + "', a_condition1_num = '" + this.textBox35.Text + "', a_condition2_num = '" + this.textBox36.Text + "', a_condition0_data0 = '" + this.textBox37.Text + "', a_condition0_data1 = '" + this.textBox38.Text + "', a_condition0_data2 = '" + this.textBox39.Text + "', a_condition0_data3 = '" + this.textBox40.Text + "', a_condition1_data0 = '" + this.textBox41.Text + "', a_condition1_data1 = '" + this.textBox42.Text + "', a_condition1_data2 = '" + this.textBox43.Text + "', a_condition1_data3 = '" + this.textBox44.Text + "', a_condition2_data0 = '" + this.textBox45.Text + "', a_condition2_data1 = '" + this.textBox46.Text + "', a_condition2_data2 = '" + this.textBox47.Text + "', a_condition2_data3 = '" + this.textBox48.Text + "', a_prize_type0 = '" + this.textBox49.Text + "', a_prize_type1 = '" + this.textBox50.Text + "', a_prize_type2 = '" + this.textBox51.Text + "', a_prize_type3 = '" + this.textBox52.Text + "', a_prize_type4 = '" + this.textBox53.Text + "', a_prize_index0 = '" + this.textBox54.Text + "', a_prize_index1 = '" + this.textBox55.Text + "', a_prize_index2 = '" + this.textBox56.Text + "', a_prize_index3 = '" + this.textBox57.Text + "', a_prize_index4 = '" + this.textBox58.Text + "', a_prize_data0 = '" + this.textBox59.Text + "', a_prize_data1 = '" + this.textBox60.Text + "', a_prize_data2 = '" + this.textBox61.Text + "', a_prize_data3 = '" + this.textBox62.Text + "', a_prize_data4 = '" + this.textBox63.Text + "', a_option_prize = '" + this.textBox64.Text + "', a_opt_prize_type0 = '" + this.textBox65.Text + "', a_opt_prize_type1 = '" + this.textBox66.Text + "', a_opt_prize_type2 = '" + this.textBox67.Text + "', a_opt_prize_type3 = '" + this.textBox68.Text + "', a_opt_prize_type4 = '" + this.textBox69.Text + "', a_opt_prize_type5 = '" + this.textBox70.Text + "', a_opt_prize_type6 = '" + this.textBox71.Text + "', a_opt_prize_index0 = '" + this.textBox72.Text + "', a_opt_prize_index1 = '" + this.textBox73.Text + "', a_opt_prize_index2 = '" + this.textBox74.Text + "', a_opt_prize_index3 = '" + this.textBox75.Text + "', a_opt_prize_index4 = '" + this.textBox76.Text + "', a_opt_prize_index5 = '" + this.textBox77.Text + "', a_opt_prize_index6 = '" + this.textBox78.Text + "', a_opt_prize_data0 = '" + this.textBox79.Text + "', a_opt_prize_data1 = '" + this.textBox80.Text + "', a_opt_prize_data2 = '" + this.textBox81.Text + "', a_opt_prize_data3 = '" + this.textBox82.Text + "', a_opt_prize_data4 = '" + this.textBox83.Text + "', a_opt_prize_data5 = '" + this.textBox84.Text + "', a_opt_prize_data6 = '" + this.textBox85.Text + "', a_opt_prize_plus0 = '" + this.textBox86.Text + "', a_opt_prize_plus1 = '" + this.textBox87.Text + "', a_opt_prize_plus2 = '" + this.textBox88.Text + "', a_opt_prize_plus3 = '" + this.textBox89.Text + "', a_opt_prize_plus4 = '" + this.textBox90.Text + "', a_opt_prize_plus5 = '" + this.textBox91.Text + "', a_opt_prize_plus6 = '" + this.textBox92.Text + "', a_only_opt_prize = '" + this.textBox93.Text + "', ";
      string str4 = this.richTextBox1.Text.Replace("'", "\\'").Replace("\"", "\\\"");
      string str5 = this.richTextBox2.Text.Replace("'", "\\'").Replace("\"", "\\\"");
      string str6 = this.richTextBox3.Text.Replace("'", "\\'").Replace("\"", "\\\"");
      string Query = str3 + "a_desc = '" + str4 + "', a_desc2 = '" + str5 + "', a_desc3 = '" + str6 + "', " + this.desc + " = '" + str4 + "', " + this.desc2 + " = '" + str5 + "', " + this.desc3 + " = '" + str6 + "', a_failvalue = '" + this.textBox97.Text + "', a_partyscale = '" + this.textBox98.Text + "', a_start_give_item = '" + this.textBox99.Text + "', a_start_give_kindcount = '" + this.textBox100.Text + "', a_start_give_numcount = '" + this.textBox101.Text + "', a_start_trigger_id = '" + this.textBox102.Text + "', a_quest_flag = '" + this.textBox103.Text + "' WHERE a_index = '" + this.textBox1.Text + "'";
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, Query);
      Console.WriteLine(Query);
      int selectedIndex = this.listBox1.SelectedIndex;
      int num1 = this.listBox1.SelectedIndex + 1;
      if (this.textBox104.Text != "")
        this.SearchList(this.textBox104.Text);
      else
        this.LoadListBox();
      if (selectedIndex + 1 >= this.listBox1.Items.Count)
        this.listBox1.SelectedIndex = selectedIndex;
      else
        this.listBox1.SelectedIndex = num1;
      this.textBox2.BackColor = Color.White;
      this.textBox2.BackColor = Color.White;
      this.textBox5.BackColor = Color.White;
      this.textBox6.BackColor = Color.White;
      this.textBox8.BackColor = Color.White;
      this.textBox10.BackColor = Color.White;
      this.textBox12.BackColor = Color.White;
      this.textBox13.BackColor = Color.White;
      this.textBox14.BackColor = Color.White;
      this.textBox16.BackColor = Color.White;
      this.textBox17.BackColor = Color.White;
      this.textBox18.BackColor = Color.White;
      this.textBox19.BackColor = Color.White;
      this.textBox20.BackColor = Color.White;
      this.textBox21.BackColor = Color.White;
      this.textBox22.BackColor = Color.White;
      this.textBox23.BackColor = Color.White;
      this.textBox24.BackColor = Color.White;
      this.textBox25.BackColor = Color.White;
      this.textBox26.BackColor = Color.White;
      this.textBox27.BackColor = Color.White;
      this.textBox31.BackColor = Color.White;
      this.textBox32.BackColor = Color.White;
      this.textBox33.BackColor = Color.White;
      this.textBox34.BackColor = Color.White;
      this.textBox35.BackColor = Color.White;
      this.textBox36.BackColor = Color.White;
      this.textBox37.BackColor = Color.White;
      this.textBox38.BackColor = Color.White;
      this.textBox39.BackColor = Color.White;
      this.textBox40.BackColor = Color.White;
      this.textBox41.BackColor = Color.White;
      this.textBox42.BackColor = Color.White;
      this.textBox43.BackColor = Color.White;
      this.textBox44.BackColor = Color.White;
      this.textBox45.BackColor = Color.White;
      this.textBox46.BackColor = Color.White;
      this.textBox47.BackColor = Color.White;
      this.textBox48.BackColor = Color.White;
      this.textBox54.BackColor = Color.White;
      this.textBox55.BackColor = Color.White;
      this.textBox56.BackColor = Color.White;
      this.textBox57.BackColor = Color.White;
      this.textBox58.BackColor = Color.White;
      this.textBox59.BackColor = Color.White;
      this.textBox60.BackColor = Color.White;
      this.textBox61.BackColor = Color.White;
      this.textBox62.BackColor = Color.White;
      this.textBox63.BackColor = Color.White;
      this.textBox64.BackColor = Color.White;
      this.textBox72.BackColor = Color.White;
      this.textBox73.BackColor = Color.White;
      this.textBox74.BackColor = Color.White;
      this.textBox75.BackColor = Color.White;
      this.textBox76.BackColor = Color.White;
      this.textBox77.BackColor = Color.White;
      this.textBox78.BackColor = Color.White;
      this.textBox79.BackColor = Color.White;
      this.textBox80.BackColor = Color.White;
      this.textBox81.BackColor = Color.White;
      this.textBox82.BackColor = Color.White;
      this.textBox83.BackColor = Color.White;
      this.textBox84.BackColor = Color.White;
      this.textBox85.BackColor = Color.White;
      this.textBox86.BackColor = Color.White;
      this.textBox87.BackColor = Color.White;
      this.textBox88.BackColor = Color.White;
      this.textBox89.BackColor = Color.White;
      this.textBox90.BackColor = Color.White;
      this.textBox91.BackColor = Color.White;
      this.textBox92.BackColor = Color.White;
      this.textBox93.BackColor = Color.White;
      this.richTextBox1.BackColor = Color.White;
      this.richTextBox2.BackColor = Color.White;
      this.richTextBox3.BackColor = Color.White;
      this.textBox97.BackColor = Color.White;
      this.textBox99.BackColor = Color.White;
      this.textBox100.BackColor = Color.White;
      this.textBox101.BackColor = Color.White;
      this.textBox102.BackColor = Color.White;
      this.textBox103.BackColor = Color.White;
      this.textBox104.BackColor = Color.White;
      this.comboBox1.BackColor = Color.White;
      this.comboBox2.BackColor = Color.White;
      this.comboBox3.BackColor = Color.White;
      this.comboBox4.BackColor = Color.White;
      this.comboBox5.BackColor = Color.White;
      this.comboBox6.BackColor = Color.White;
      this.comboBox7.BackColor = Color.White;
      this.comboBox8.BackColor = Color.White;
      this.comboBox9.BackColor = Color.White;
      this.comboBox10.BackColor = Color.White;
      this.comboBox11.BackColor = Color.White;
      this.comboBox12.BackColor = Color.White;
      this.comboBox13.BackColor = Color.White;
      this.comboBox14.BackColor = Color.White;
      this.comboBox15.BackColor = Color.White;
      this.comboBox16.BackColor = Color.White;
      this.comboBox17.BackColor = Color.White;
      this.comboBox18.BackColor = Color.White;
      this.comboBox19.BackColor = Color.White;
      this.comboBox20.BackColor = Color.White;
      this.comboBox21.BackColor = Color.White;
      this.comboBox22.BackColor = Color.White;
      int num2 = (int) new CustomMessage("Done :)").ShowDialog();
    }

    private void CbRvrType_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.CbRvrType.BackColor = Color.LightBlue;
    }

    private void CbRvRGrade1_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.CbRvRGrade.BackColor = Color.LightBlue;
    }
  }
}
