// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.SkillEditorV1
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools
{
  public class SkillEditorV1 : Form
  {
    public static Connection connection = new Connection();
    private string Host = SkillEditorV1.connection.Settings.SqlHost;
    private string User = SkillEditorV1.connection.Settings.SqlUser;
    private string Password = SkillEditorV1.connection.Settings.SqlPassword;
    private string Database = SkillEditorV1.connection.Settings.SqlDatabase;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    public string rowName = "a_index";
    private string Episode = SkillEditorV1.connection.Settings.Episode;
    public string[] menuArray = new string[2]
    {
      "a_index",
      "a_name_usa"
    };
    public string[] menuArray2 = new string[2]
    {
      "a_type",
      "a_name_usa"
    };
    public string[] menuArray3 = new string[1]{ "a_level" };
    public string[] menuArray4 = new string[1]{ "a_level" };
    public string[] SearchMenu = new string[2]
    {
      "a_index",
      "a_name_usa"
    };
    public List<string> MenuList = new List<string>();
    public List<string> MenuListSearch = new List<string>();
    public List<string> MenuList2 = new List<string>();
    public List<string> MenuListSearch2 = new List<string>();
    public string mSortJob = "-1";
    public string mSortJob2 = "-1";
    private ExportLodHandle exportLodhandle = new ExportLodHandle();
    private IContainer components = (IContainer) null;
    public string name;
    public int index;
    public string test2;
    public const int AW_ACTIVATE = 131072;
    public const int AW_HIDE = 65536;
    public const int AW_BLEND = 524288;
    public const int AW_CENTER = 16;
    public const int AW_SLIDE = 262144;
    public const int AW_HOR_POSITIVE = 1;
    public const int AW_HOR_NEGATIVE = 2;
    private MenuStrip menuStrip1;
    private ToolStripMenuItem fileExportToolStripMenuItem;
    private GroupBox groupBox3;
    private Button button3;
    private Button button1;
    private ListBox listBox1;
    private GroupBox groupBox5;
    private Label label7;
    private TabControl tabControl1;
    private TabPage tabPage1;
    private Button button2;
    private GroupBox groupBox1;
    private GroupBox groupBox2;
    private TextBox textBox2;
    private TextBox textBox3;
    private Label label2;
    private TextBox textBox1;
    private Label label1;
    private ComboBox comboBox1;
    private ComboBox comboBox2;
    private ComboBox comboBox3;
    private ComboBox comboBox6;
    private ComboBox comboBox5;
    private ComboBox comboBox4;
    private ComboBox comboBox13;
    private ComboBox comboBox12;
    private ComboBox comboBox11;
    private ComboBox comboBox10;
    private ComboBox comboBox9;
    private ComboBox comboBox8;
    private ComboBox comboBox7;
    private ComboBox comboBox14;
    private Label label3;
    private Label label5;
    private TextBox textBox4;
    private TextBox textBox5;
    private Label label6;
    private TextBox textBox6;
    private GroupBox groupBox4;
    private Label label8;
    private ComboBox comboBox15;
    private TextBox textBox7;
    private GroupBox groupBox6;
    private TabPage tabPage4;
    private TextBox textBox8;
    private Label label9;
    private Label label16;
    private TextBox textBox14;
    private Label label15;
    private TextBox textBox13;
    private TextBox textBox9;
    private Label label14;
    private Label label11;
    private TextBox textBox12;
    private TextBox textBox10;
    private Label label13;
    private Label label12;
    private TextBox textBox11;
    private TextBox textBox15;
    private GroupBox groupBox9;
    private Label label17;
    private ComboBox comboBox16;
    private TextBox textBox16;
    private GroupBox groupBox10;
    private ComboBox comboBox17;
    private Label label18;
    private TextBox textBox17;
    private Label label19;
    private ComboBox comboBox18;
    private TextBox textBox18;
    private TextBox textBox19;
    private GroupBox groupBox11;
    private Label label22;
    private Label label21;
    private Label label20;
    private TextBox textBox21;
    private TextBox textBox20;
    private TextBox textBox22;
    private TextBox textBox23;
    private TextBox textBox24;
    private Label label25;
    private Label label24;
    private Label label23;
    private TextBox textBox25;
    private Label label26;
    private ToolStripMenuItem exportSkilllodToolStripMenuItem;
    private ToolStripMenuItem exportStrSkillsusalodToolStripMenuItem;
    private TextBox textBox26;
    private Label label4;
    private Label label27;
    private TextBox textBox28;
    private Label label10;
    private TextBox textBox27;
    private TextBox textBox29;
    private GroupBox groupBox8;
    private TextBox textBox30;
    private Label label28;
    private TextBox textBox31;
    private Label label29;
    private TextBox textBox32;
    private Label label30;
    private Label label31;
    private TabPage tabPage3;
    private GroupBox groupBox12;
    private GroupBox groupBox13;
    private TextBox textBox33;
    private TextBox textBox35;
    private TextBox textBox34;
    private Label label34;
    private Label label33;
    private Label label32;
    private GroupBox groupBox14;
    private Label label35;
    private Label label36;
    private Label label37;
    private GroupBox groupBox20;
    private Label label64;
    private Label label65;
    private Label label66;
    private Label label67;
    private Label label68;
    private Label label69;
    private GroupBox groupBox19;
    private Label label63;
    private Label label62;
    private Label label61;
    private Label label60;
    private Label label59;
    private Label label58;
    private GroupBox groupBox18;
    private Label label52;
    private Label label53;
    private Label label54;
    private Label label55;
    private Label label56;
    private Label label57;
    private GroupBox groupBox17;
    private Label label51;
    private Label label50;
    private Label label49;
    private Label label48;
    private Label label47;
    private Label label46;
    private GroupBox groupBox16;
    private Label label42;
    private Label label43;
    private Label label44;
    private Label label45;
    private GroupBox groupBox15;
    private Label label41;
    private Label label40;
    private Label label39;
    private Label label38;
    private TextBox textBox36;
    private TextBox textBox37;
    private TextBox textBox39;
    private TextBox textBox38;
    private TextBox textBox40;
    private TextBox textBox41;
    private TextBox textBox42;
    private TextBox textBox43;
    private TextBox textBox45;
    private TextBox textBox44;
    private TextBox textBox46;
    private TextBox textBox47;
    private TextBox textBox48;
    private TextBox textBox51;
    private TextBox textBox50;
    private TextBox textBox49;
    private GroupBox groupBox21;
    private Label label70;
    private TextBox textBox52;
    private Label label71;
    private TextBox textBox53;
    private TextBox textBox54;
    private TextBox textBox55;
    private Label label72;
    private GroupBox groupBox22;
    private Label label73;
    private LinkLabel linkLabel1;
    private Label label75;
    private Label label74;
    private TextBox textBox57;
    private TextBox textBox56;
    private PictureBox pictureBox1;
    private TextBox textBox58;
    private TextBox textBox59;
    private TextBox textBox60;
    private TextBox textBox61;
    private TextBox textBox62;
    private TextBox textBox63;
    private TextBox textBox64;
    private TextBox textBox65;
    private TextBox textBox66;
    private TextBox textBox70;
    private TextBox textBox69;
    private TextBox textBox68;
    private TextBox textBox67;
    private TextBox textBox71;
    private TextBox textBox76;
    private TextBox textBox75;
    private TextBox textBox74;
    private TextBox textBox73;
    private TextBox textBox72;
    private TextBox textBox77;
    private TextBox textBox203;
    private Label label76;
    private Label label77;
    private TextBox textBox78;
    private TextBox textBox79;
    private PictureBox pictureBox2;
    private Label label78;
    private Label label79;
    private Label label80;
    private Label label81;
    private TextBox textBox80;
    private PictureBox pictureBox3;
    private TextBox textBox81;
    private Label label82;
    private Label label83;
    private TextBox textBox82;
    private TextBox textBox83;
    private Label label84;
    private TabPage tabPage2;
    private TextBox textBox84;
    private Label label85;
    private Label label86;
    private TextBox textBox85;
    private Label label88;
    private TextBox textBox87;
    private Label label87;
    private TextBox textBox86;
    private GroupBox groupBox23;
    private Label label89;
    private TextBox textBox88;
    private TextBox textBox89;
    private Label label90;
    private TextBox textBox90;
    private Label label91;
    private TextBox textBox91;
    private Label label92;
    private PictureBox pictureBox4;
    private Label label93;
    private TextBox textBox92;
    private Label label95;
    private TextBox textBox94;
    private PictureBox pictureBox5;
    private Label label94;
    private TextBox textBox93;
    private TextBox textBox95;
    private GroupBox groupBox25;
    private Label label96;
    private TextBox textBox96;
    private Label label97;
    private PictureBox pictureBox6;
    private Label label98;
    private TextBox textBox97;
    private TextBox textBox98;
    private Label label99;
    private TextBox textBox102;
    private Label label103;
    private PictureBox pictureBox8;
    private Label label102;
    private TextBox textBox101;
    private TextBox textBox100;
    private Label label101;
    private PictureBox pictureBox7;
    private Label label100;
    private TextBox textBox99;
    private PictureBox pictureBox11;
    private TextBox textBox107;
    private Label label106;
    private PictureBox pictureBox10;
    private TextBox textBox105;
    private Label label105;
    private TextBox textBox103;
    private Label label104;
    private Label label107;
    private TextBox textBox104;
    private Label label108;
    private TextBox textBox106;
    private Label label109;
    private TextBox textBox108;
    private GroupBox groupBox26;
    private Label label110;
    private TextBox textBox109;
    private Label label115;
    private TextBox textBox114;
    private Label label114;
    private TextBox textBox113;
    private Label label113;
    private TextBox textBox112;
    private Label label112;
    private TextBox textBox111;
    private Label label111;
    private TextBox textBox110;
    private GroupBox groupBox27;
    private TextBox textBox120;
    private Label label121;
    private TextBox textBox119;
    private Label label120;
    private TextBox textBox118;
    private Label label119;
    private TextBox textBox117;
    private Label label118;
    private TextBox textBox116;
    private Label label117;
    private TextBox textBox115;
    private Label label116;
    private Label label125;
    private Label label124;
    private Label label123;
    private Label label122;
    private GroupBox groupBox28;
    private TextBox textBox121;
    private TextBox textBox122;
    private TextBox textBox123;
    private TextBox textBox124;
    private TextBox textBox125;
    private Label label126;
    private Label label127;
    private TextBox textBox126;
    private TextBox textBox127;
    private TextBox textBox128;
    private Label label129;
    private Label label128;
    private TextBox textBox129;
    private TextBox textBox130;
    private TextBox textBox131;
    private TextBox textBox132;
    private TextBox textBox136;
    private TextBox textBox133;
    private TextBox textBox134;
    private TextBox textBox135;
    private TextBox textBox137;
    private TextBox textBox138;
    private TextBox textBox139;
    private TextBox textBox140;
    private TextBox textBox144;
    private TextBox textBox141;
    private TextBox textBox142;
    private TextBox textBox143;
    private TextBox textBox148;
    private TextBox textBox145;
    private TextBox textBox146;
    private TextBox textBox147;
    private TextBox textBox149;
    private TextBox textBox150;
    private TextBox textBox151;
    private TextBox textBox152;
    private Label label135;
    private PictureBox pictureBox9;
    private TextBox textBox153;
    private TextBox textBox154;
    private TextBox textBox155;
    private TextBox textBox156;
    private Label label136;
    private TextBox textBox157;
    private TextBox textBox158;
    private TextBox textBox159;
    private Label label137;
    private TextBox textBox160;
    private ComboBox comboBox19;
    private ComboBox comboBox20;
    private Label label139;
    private Label label138;
    private ToolTip toolTip1;
    private Button button6;
    private GroupBox groupBox7;
    private Button button5;
    private Button button4;
    private ListBox listBox2;
    private GroupBox groupBox30;
    private TabControl tabControl2;
    private TabPage tabPage5;
    private Label label130;

    public SkillEditorV1() => this.InitializeComponent();

    private void LoadListBox()
    {
      this.MenuList.Clear();
      string Query = "SELECT a_index, a_name_usa FROM t_skill WHERE a_job ='" + this.mSortJob + "' AND a_job2 ='" + this.mSortJob2 + "' ORDER BY a_index;";
      if (this.mSortJob == "-1")
        Query = "SELECT a_index, a_name_usa FROM t_skill ORDER BY a_index;";
      if (this.mSortJob2 == "-1" && this.mSortJob != "-1")
        Query = "SELECT a_index, a_name_usa FROM t_skill WHERE a_job ='" + this.mSortJob + "' ORDER BY a_index;";
      if (this.mSortJob2 == "-1" && this.mSortJob == "-1")
        Query = "SELECT a_index, a_name_usa FROM t_skill ORDER BY a_index;";
      this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, Query);
      for (int index = 0; index < this.listBox1.Items.Count; ++index)
        this.MenuList.Add(this.listBox1.Items[index].ToString());
      this.listBox1.DataSource = (object) this.MenuList;
    }

    private void LoadListBox2()
    {
      this.MenuList2.Clear();
      this.listBox2.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray4, this.Host, this.User, this.Password, this.Database, "select a_level from t_skillLevel WHERE a_index ='" + this.textBox1.Text + "';");
      for (int index = 0; index < this.listBox2.Items.Count; ++index)
        this.MenuList2.Add(this.listBox2.Items[index].ToString());
      this.listBox2.DataSource = (object) this.MenuList2;
    }

    public void SearchList(string searchString)
    {
      searchString = searchString.Replace("\\", "\\\\").Replace("'", "\\'");
      string lower = searchString.ToLower();
      string upper = searchString.ToUpper();
      string str = "";
      if (searchString.Length > 1)
        str = char.ToUpper(searchString[0]).ToString() + searchString.Substring(1);
      this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_usa from t_skill WHERE a_name_usa LIKE '%" + searchString + "%' OR a_index LIKE '%" + searchString + "%' OR a_name_usa LIKE '%" + lower + "%' OR a_index  LIKE '%" + lower + "%' OR a_name_usa LIKE '%" + upper + "%' OR a_index LIKE '%" + upper + "%' OR a_name_usa LIKE '%" + str + "%' OR a_index LIKE '%" + str + "%' ORDER BY a_index;");
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
        this.textBox1.Text = this.GetIndex().ToString();
      string Query = " select a_index , a_job , a_job2 , a_name_usa , a_client_description_usa , a_type , a_flag , a_maxLevel , a_appRange , a_fireRange , a_fireRange2 , a_minRange , a_targetType, a_targetNum , a_useState , a_useWeaponType0 , a_useWeaponType1 , a_use_needWearingType , a_useMagicIndex1 , a_useMagicIndex2 , a_useMagicIndex3 , a_useMagicLevel1 , a_useMagicLevel2 , a_useMagicLevel3 , a_appState , a_appWeaponType0 , a_appWeaponType1 , a_app_needWearingType , a_readyTime , a_stillTime , a_fireTime , a_reuseTime , a_cd_ra , a_cd_re , a_cd_sa , a_cd_fa , a_cd_fe0 , a_cd_fe1 , a_cd_fe2 , a_cd_fot , a_cd_fos , a_cd_ox , a_cd_oz , a_cd_oh , a_cd_oc , a_cd_fdc , a_cd_fd0 , a_cd_fd1 , a_cd_fd2 , a_cd_fd3 , a_cd_dd , a_cd_fe_after , a_cd_fe_after2 , a_client_tooltip_usa , a_client_icon_texid , a_client_icon_row , a_client_icon_col , a_cd_ra2 , a_cd_re2 , a_cd_sa2 , a_cd_fa2 , a_cd_fe3 , a_cd_fe4 , a_cd_fe5 , a_cd_fot2 , a_cd_fos2 , a_cd_ox2 , a_cd_oz2 , a_cd_oh2 , a_cd_oc2 , a_cd_fdc2 , a_cd_fd4 , a_cd_fd5 , a_cd_fd6 , a_cd_fd7 , a_cd_dd2 , a_selfparam , a_targetparam , a_soul_consum , a_summon_idx , a_sorcerer_flag , a_apet_index , a_allowzone from t_skill WHERE a_index ='" + this.textBox1.Text + "';";
      string[] rows = new string[83]
      {
        "a_index",
        "a_job",
        "a_job2",
        "a_name_usa",
        "a_client_description_usa",
        "a_type",
        "a_flag",
        "a_maxLevel",
        "a_appRange",
        "a_fireRange",
        "a_fireRange2",
        "a_minRange",
        "a_targetType",
        "a_targetNum",
        "a_useState",
        "a_useWeaponType0",
        "a_useWeaponType1",
        "a_use_needWearingType",
        "a_useMagicIndex1",
        "a_useMagicIndex2",
        "a_useMagicIndex3",
        "a_useMagicLevel1",
        "a_useMagicLevel2",
        "a_useMagicLevel3",
        "a_appState",
        "a_appWeaponType0",
        "a_appWeaponType1",
        "a_app_needWearingType",
        "a_readyTime",
        "a_stillTime",
        "a_fireTime",
        "a_reuseTime",
        "a_cd_ra",
        "a_cd_re",
        "a_cd_sa",
        "a_cd_fa",
        "a_cd_fe0",
        "a_cd_fe1",
        "a_cd_fe2",
        "a_cd_fot",
        "a_cd_fos",
        "a_cd_ox",
        "a_cd_oz",
        "a_cd_oh",
        "a_cd_oc",
        "a_cd_fdc",
        "a_cd_fd0",
        "a_cd_fd1",
        "a_cd_fd2",
        "a_cd_fd3",
        "a_cd_dd",
        "a_cd_fe_after",
        "a_cd_fe_after2",
        "a_client_tooltip_usa",
        "a_client_icon_texid",
        "a_client_icon_row",
        "a_client_icon_col",
        "a_cd_ra2",
        "a_cd_re2",
        "a_cd_sa2",
        "a_cd_fa2",
        "a_cd_fe3",
        "a_cd_fe4",
        "a_cd_fe5",
        "a_cd_fot2",
        "a_cd_fos2",
        "a_cd_ox2",
        "a_cd_oz2",
        "a_cd_oh2",
        "a_cd_oc2",
        "a_cd_fdc2",
        "a_cd_fd4",
        "a_cd_fd5",
        "a_cd_fd6",
        "a_cd_fd7",
        "a_cd_dd2",
        "a_selfparam",
        "a_targetparam",
        "a_soul_consum",
        "a_summon_idx",
        "a_sorcerer_flag",
        "a_apet_index",
        "a_allowzone"
      };
      Query.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'");
      string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query, rows);
      this.textBox1.Text = strArray[0];
      this.textBox2.Text = strArray[1];
      this.textBox3.Text = strArray[2];
      this.textBox4.Text = strArray[3];
      this.textBox5.Text = strArray[4];
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
      this.SelectBoxes();
      this.IconItem();
      this.IconSkill();
      this.ClearPicture();
      try
      {
        this.pictureBox1.Image = (Image) this.databaseHandle.IconSkill1(int.Parse(this.textBox55.Text), int.Parse(this.textBox56.Text), int.Parse(this.textBox57.Text));
      }
      catch
      {
      }
      this.LoadListBox2();
    }

    private void ClearPicture()
    {
      if (this.textBox129.Text == "")
        this.pictureBox4.Image = (Image) null;
      if (this.textBox133.Text == "")
        this.pictureBox5.Image = (Image) null;
      if (this.textBox137.Text == "")
        this.pictureBox6.Image = (Image) null;
      if (this.textBox141.Text == "")
        this.pictureBox7.Image = (Image) null;
      if (this.textBox145.Text == "")
        this.pictureBox8.Image = (Image) null;
      if (this.textBox150.Text == "")
        this.pictureBox9.Image = (Image) null;
      if (this.textBox153.Text == "")
        this.pictureBox10.Image = (Image) null;
      if (!(this.textBox157.Text == ""))
        return;
      this.pictureBox11.Image = (Image) null;
    }

    private void IconSkill()
    {
      string Query1 = "select a_index, a_client_icon_texid, a_client_icon_row, a_client_icon_col, a_name_usa from t_skill WHERE a_index ='" + this.textBox97.Text + "';";
      string Query2 = "select a_index, a_client_icon_texid, a_client_icon_row, a_client_icon_col, a_name_usa from t_skill WHERE a_index ='" + this.textBox99.Text + "';";
      string Query3 = "select a_index, a_client_icon_texid, a_client_icon_row, a_client_icon_col, a_name_usa from t_skill WHERE a_index ='" + this.textBox101.Text + "';";
      string[] rows1 = new string[5]
      {
        "a_index",
        "a_client_icon_texid",
        "a_client_icon_row",
        "a_client_icon_col",
        "a_name_usa"
      };
      string[] rows2 = new string[5]
      {
        "a_index",
        "a_client_icon_texid",
        "a_client_icon_row",
        "a_client_icon_col",
        "a_name_usa"
      };
      string[] rows3 = new string[5]
      {
        "a_index",
        "a_client_icon_texid",
        "a_client_icon_row",
        "a_client_icon_col",
        "a_name_usa"
      };
      Query1.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'");
      string[] strArray1 = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query1, rows1);
      string[] strArray2 = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query2, rows2);
      string[] strArray3 = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query3, rows3);
      this.textBox140.Text = strArray1[0];
      this.textBox137.Text = strArray1[1];
      this.textBox138.Text = strArray1[2];
      this.textBox139.Text = strArray1[3];
      this.textBox144.Text = strArray2[0];
      this.textBox141.Text = strArray2[1];
      this.textBox142.Text = strArray2[2];
      this.textBox143.Text = strArray2[3];
      this.textBox148.Text = strArray3[0];
      this.textBox145.Text = strArray3[1];
      this.textBox146.Text = strArray3[2];
      this.textBox147.Text = strArray3[3];
    }

    private void IconItem()
    {
      string Query1 = "select a_index, a_texture_id, a_texture_row, a_texture_col, a_name_usa from t_item WHERE a_index ='" + this.textBox91.Text + "';";
      string Query2 = "select a_index, a_texture_id, a_texture_row, a_texture_col, a_name_usa from t_item WHERE a_index ='" + this.textBox93.Text + "';";
      string Query3 = "select a_index, a_texture_id, a_texture_row, a_texture_col, a_name_usa from t_item WHERE a_index ='" + this.textBox103.Text + "';";
      string Query4 = "select a_index, a_texture_id, a_texture_row, a_texture_col, a_name_usa from t_item WHERE a_index ='" + this.textBox105.Text + "';";
      string Query5 = "select a_index, a_texture_id, a_texture_row, a_texture_col, a_name_usa from t_item WHERE a_index ='" + this.textBox107.Text + "';";
      string[] rows1 = new string[5]
      {
        "a_index",
        "a_texture_id",
        "a_texture_row",
        "a_texture_col",
        "a_name_usa"
      };
      string[] rows2 = new string[5]
      {
        "a_index",
        "a_texture_id",
        "a_texture_row",
        "a_texture_col",
        "a_name_usa"
      };
      string[] rows3 = new string[5]
      {
        "a_index",
        "a_texture_id",
        "a_texture_row",
        "a_texture_col",
        "a_name_usa"
      };
      string[] rows4 = new string[5]
      {
        "a_index",
        "a_texture_id",
        "a_texture_row",
        "a_texture_col",
        "a_name_usa"
      };
      string[] rows5 = new string[5]
      {
        "a_index",
        "a_texture_id",
        "a_texture_row",
        "a_texture_col",
        "a_name_usa"
      };
      Query1.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'");
      string[] strArray1 = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query1, rows1);
      string[] strArray2 = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query2, rows2);
      string[] strArray3 = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query3, rows3);
      string[] strArray4 = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query4, rows4);
      string[] strArray5 = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query5, rows5);
      this.textBox132.Text = strArray1[0];
      this.textBox129.Text = strArray1[1];
      this.textBox130.Text = strArray1[2];
      this.textBox131.Text = strArray1[3];
      this.textBox136.Text = strArray2[0];
      this.textBox133.Text = strArray2[1];
      this.textBox134.Text = strArray2[2];
      this.textBox135.Text = strArray2[3];
      this.textBox149.Text = strArray3[0];
      this.textBox150.Text = strArray3[1];
      this.textBox151.Text = strArray3[2];
      this.textBox152.Text = strArray3[3];
      this.textBox156.Text = strArray4[0];
      this.textBox153.Text = strArray4[1];
      this.textBox154.Text = strArray4[2];
      this.textBox155.Text = strArray4[3];
      this.textBox160.Text = strArray5[0];
      this.textBox157.Text = strArray5[1];
      this.textBox158.Text = strArray5[2];
      this.textBox159.Text = strArray5[3];
    }

    private void SelectBoxes()
    {
      int num1 = this.comboBox1.FindString(this.textBox2.Text);
      int num2 = this.comboBox2.FindString(this.textBox3.Text);
      int num3 = this.comboBox3.FindString(this.textBox3.Text);
      int num4 = this.comboBox4.FindString(this.textBox3.Text);
      int num5 = this.comboBox5.FindString(this.textBox3.Text);
      int num6 = this.comboBox6.FindString(this.textBox3.Text);
      int num7 = this.comboBox7.FindString(this.textBox3.Text);
      int num8 = this.comboBox8.FindString(this.textBox3.Text);
      int num9 = this.comboBox9.FindString(this.textBox3.Text);
      int num10 = this.comboBox10.FindString(this.textBox3.Text);
      int num11 = this.comboBox11.FindString(this.textBox3.Text);
      int num12 = this.comboBox12.FindString(this.textBox3.Text);
      int num13 = this.comboBox13.FindString(this.textBox3.Text);
      int num14 = this.comboBox14.FindString(this.textBox3.Text);
      int num15 = this.comboBox15.FindString(this.textBox6.Text);
      int num16 = this.comboBox16.FindString(this.textBox13.Text);
      int num17 = this.comboBox17.FindString(this.textBox16.Text);
      int num18 = this.comboBox18.FindString(this.textBox17.Text);
      this.comboBox1.SelectedIndex = num1;
      this.comboBox2.SelectedIndex = num2;
      this.comboBox3.SelectedIndex = num3;
      this.comboBox4.SelectedIndex = num4;
      this.comboBox5.SelectedIndex = num5;
      this.comboBox6.SelectedIndex = num6;
      this.comboBox7.SelectedIndex = num7;
      this.comboBox8.SelectedIndex = num8;
      this.comboBox9.SelectedIndex = num9;
      this.comboBox10.SelectedIndex = num10;
      this.comboBox11.SelectedIndex = num11;
      this.comboBox12.SelectedIndex = num12;
      this.comboBox13.SelectedIndex = num13;
      this.comboBox14.SelectedIndex = num14;
      this.comboBox15.SelectedIndex = num15;
      this.comboBox16.SelectedIndex = num16;
      this.comboBox17.SelectedIndex = num17;
      this.comboBox18.SelectedIndex = num18;
    }

    private void button2_Click(object sender, EventArgs e)
    {
      string str1 = "UPDATE t_skill SET a_index = '" + this.textBox1.Text + "', a_job = '" + this.textBox2.Text + "', a_job2 = '" + this.textBox3.Text + "', ";
      string str2 = this.textBox4.Text.Replace("'", "\\'").Replace("\"", "\\\"");
      string Query = str1 + "a_name = '" + str2 + "', a_name_usa = '" + str2 + "', a_client_description_usa = '" + this.textBox5.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_type = '" + this.textBox6.Text + "',a_flag= '" + this.textBox7.Text + "',a_maxLevel = '" + this.textBox8.Text + "',a_appRange = '" + this.textBox9.Text + "',a_fireRange = '" + this.textBox10.Text + "',a_fireRange2 = '" + this.textBox11.Text + "',a_minRange = '" + this.textBox12.Text + "',a_targetType = '" + this.textBox13.Text + "',a_targetNum = '" + this.textBox14.Text + "',a_useState = '" + this.textBox15.Text + "',a_useWeaponType0 = '" + this.textBox16.Text + "',a_useWeaponType1 = '" + this.textBox17.Text + "',a_use_needWearingType = '" + this.textBox18.Text + "',a_useMagicIndex1 = '" + this.textBox19.Text + "',a_useMagicIndex2 = '" + this.textBox20.Text + "',a_useMagicIndex3 = '" + this.textBox21.Text + "',a_useMagicLevel1 = '" + this.textBox22.Text + "',a_useMagicLevel2 = '" + this.textBox23.Text + "',a_useMagicLevel3 = '" + this.textBox24.Text + "',a_appState = '" + this.textBox25.Text + "',a_appWeaponType0 = '" + this.textBox26.Text + "',a_appWeaponType1 = '" + this.textBox27.Text + "',a_app_needWearingType = '" + this.textBox28.Text + "',a_readyTime = '" + this.textBox29.Text + "',a_stillTime = '" + this.textBox30.Text + "',a_fireTime = '" + this.textBox31.Text + "',a_reuseTime = '" + this.textBox32.Text + "',a_cd_ra = '" + this.textBox33.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "',a_cd_re = '" + this.textBox34.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "',a_cd_sa = '" + this.textBox35.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "',a_cd_fa = '" + this.textBox36.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "',a_cd_fe0 = '" + this.textBox37.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "',a_cd_fe1 = '" + this.textBox38.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "',a_cd_fe2 = '" + this.textBox39.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "',a_cd_fot = '" + this.textBox40.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "',a_cd_fos = '" + this.textBox41.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "',a_cd_ox = '" + this.textBox42.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "',a_cd_oz = '" + this.textBox43.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "',a_cd_oh = '" + this.textBox44.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "',a_cd_oc = '" + this.textBox45.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "',a_cd_fdc = '" + this.textBox46.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "',a_cd_fd0 = '" + this.textBox47.Text.Replace(",", ".") + "',a_cd_fd1 = '" + this.textBox48.Text.Replace(",", ".") + "',a_cd_fd2 = '" + this.textBox49.Text.Replace(",", ".") + "',a_cd_fd3 = '" + this.textBox50.Text.Replace(",", ".") + "',a_cd_dd = '" + this.textBox51.Text + "',a_cd_fe_after = '" + this.textBox52.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "',a_cd_fe_after2 = '" + this.textBox53.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "',a_client_tooltip_usa = '" + this.textBox54.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "',a_client_icon_texid = '" + this.textBox55.Text + "',a_client_icon_row = '" + this.textBox56.Text + "',a_client_icon_col = '" + this.textBox57.Text + "',a_cd_ra2 = '" + this.textBox58.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "',a_cd_re2 = '" + this.textBox59.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "',a_cd_sa2 = '" + this.textBox60.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "',a_cd_fa2 = '" + this.textBox61.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "',a_cd_fe3 = '" + this.textBox62.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "',a_cd_fe4 = '" + this.textBox63.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "',a_cd_fe5 = '" + this.textBox64.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "',a_cd_fot2 = '" + this.textBox65.Text + "',a_cd_fos2 = '" + this.textBox66.Text + "',a_cd_ox2 = '" + this.textBox67.Text + "',a_cd_oz2 = '" + this.textBox68.Text + "',a_cd_oh2 = '" + this.textBox69.Text + "',a_cd_oc2 = '" + this.textBox70.Text + "',a_cd_fdc2 = '" + this.textBox71.Text + "',a_cd_fd4 = '" + this.textBox72.Text.Replace(",", ".") + "',a_cd_fd5 = '" + this.textBox73.Text.Replace(",", ".") + "',a_cd_fd6 = '" + this.textBox74.Text.Replace(",", ".") + "',a_cd_fd7 = '" + this.textBox75.Text.Replace(",", ".") + "',a_cd_dd2 = '" + this.textBox76.Text + "',a_selfparam = '" + this.textBox77.Text + "',a_targetparam = '" + this.textBox78.Text + "',a_soul_consum = '" + this.textBox79.Text + "',a_summon_idx = '" + this.textBox80.Text + "',a_sorcerer_flag = '" + this.textBox81.Text + "',a_apet_index = '" + this.textBox82.Text + "',a_allowzone = '" + this.textBox83.Text + "' WHERE a_index = '" + this.textBox1.Text + "'";
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, Query);
      Console.WriteLine(Query);
      this.label130.Text = "Update Skill Succesfully!";
      this.label130.ForeColor = Color.Lime;
      this.label130.Visible = true;
      int selectedIndex = this.listBox1.SelectedIndex;
      if (this.textBox203.Text != "")
        this.SearchList(this.textBox203.Text);
      else
        this.LoadListBox();
      this.listBox1.SelectedIndex = selectedIndex;
    }

    private void button1_Click(object sender, EventArgs e)
    {
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_skill DEFAULT VALUES");
      this.LoadListBox();
      this.listBox1.SelectedIndex = this.listBox1.Items.Count - 2;
    }

    private void button3_Click(object sender, EventArgs e)
    {
      int selectedIndex = this.listBox1.SelectedIndex;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_skill WHERE a_index = '" + this.textBox1.Text + "'");
      this.LoadListBox();
      this.listBox1.SelectedIndex = selectedIndex - 1;
    }

    private void LoadStartUp()
    {
      this.comboBox19.Items.AddRange(new object[14]
      {
        (object) "-1 - All",
        (object) "0 - Titan",
        (object) "1 - Knight",
        (object) "2 - Healer",
        (object) "3 - Mage",
        (object) "4 - Rogue",
        (object) "5 - Sorcerer",
        (object) "6 - NightShadow",
        (object) "7 - Ex-Rogue",
        (object) "8 - Ex-Mage",
        (object) "9 - Nothing",
        (object) "10 - Pet",
        (object) "11 - APet",
        (object) "999 - All"
      });
      this.comboBox1.Items.AddRange(new object[13]
      {
        (object) "0 - Titan",
        (object) "1 - Knight",
        (object) "2 - Healer",
        (object) "3 - Mage",
        (object) "4 - Rogue",
        (object) "5 - Sorcerer",
        (object) "6 - Night Shadow",
        (object) "7 - Ex-Rogue",
        (object) "8 - Archmage",
        (object) "9 - Nothing",
        (object) "10 - Pet",
        (object) "11 - APet",
        (object) "999 - All"
      });
      this.comboBox2.Items.AddRange(new object[3]
      {
        (object) "0 - None",
        (object) "1 - Higlander",
        (object) "2 - Warmaster"
      });
      this.comboBox3.Items.AddRange(new object[3]
      {
        (object) "0 - None",
        (object) "1 - Royal",
        (object) "2 - Templar"
      });
      this.comboBox4.Items.AddRange(new object[3]
      {
        (object) "0 - None",
        (object) "1 - Archer",
        (object) "2 - Cleric"
      });
      this.comboBox5.Items.AddRange(new object[3]
      {
        (object) "0 - None",
        (object) "1 - Wizard",
        (object) "2 - Witch"
      });
      this.comboBox6.Items.AddRange(new object[3]
      {
        (object) "0 - None",
        (object) "1 - Assasin",
        (object) "2 - Ranger"
      });
      this.comboBox7.Items.AddRange(new object[3]
      {
        (object) "0 - None",
        (object) "1 - Elementalist",
        (object) "2 - Specialist"
      });
      this.comboBox8.Items.AddRange(new object[2]
      {
        (object) "0 - None",
        (object) "1 - NightShadow"
      });
      this.comboBox9.Items.AddRange(new object[3]
      {
        (object) "0 - None",
        (object) "1 - Ex-Assasin",
        (object) "2 - Ex-Ranger"
      });
      this.comboBox10.Items.AddRange(new object[3]
      {
        (object) "0 - None",
        (object) "1 - Arch-Wizard",
        (object) "2 - Arch-Witch"
      });
      this.comboBox11.Items.AddRange(new object[1]
      {
        (object) "0 - None"
      });
      this.comboBox12.Items.AddRange(new object[5]
      {
        (object) "0 - None",
        (object) "1 - Horse",
        (object) "2 - Dragon",
        (object) "3 - Horse Mount",
        (object) "4 - Dragon Mount"
      });
      this.comboBox13.Items.AddRange(new object[5]
      {
        (object) "0 - None",
        (object) "1 - Human",
        (object) "2 - Beast",
        (object) "3 - Unknown",
        (object) "4 - Unknown"
      });
      this.comboBox14.Items.AddRange(new object[1]
      {
        (object) "0 - None"
      });
      this.comboBox15.Items.AddRange(new object[10]
      {
        (object) "0 - Melee",
        (object) "1 - Range",
        (object) "2 - Magic",
        (object) "3 - Passive",
        (object) "4 - Pet Command",
        (object) "5 - Pet Skill Passive",
        (object) "6 - Pet Skill Active",
        (object) "7 - Guild Skill Passive",
        (object) "8 - Seal",
        (object) "9 - Summon Skill"
      });
      this.comboBox16.Items.AddRange(new object[12]
      {
        (object) "0 - Self One",
        (object) "1 - Self Range",
        (object) "2 - Target One",
        (object) "3 - Target Range",
        (object) "4 - Party One",
        (object) "5 - Party All",
        (object) "6 - Target D120",
        (object) "7 - Target Rect",
        (object) "8 - Elemental One",
        (object) "9 - Guild All",
        (object) "10 - Guild One",
        (object) "11 - Guild Self Range"
      });
      this.comboBox17.Items.AddRange(new object[17]
      {
        (object) "-1",
        (object) "0 - Weapon Night",
        (object) "1 - Weapon Crossbow",
        (object) "2 - Weapon Staff",
        (object) "3 - Weapon Big Sword",
        (object) "4 - Weapon Axe",
        (object) "5 - Weapon Short Staff",
        (object) "6 - Weapon Bow",
        (object) "7 - Weapon ShortGum",
        (object) "8 - Weapon Mining",
        (object) "9 - Weapon Gathering",
        (object) "10 - Weapon Charge",
        (object) "11 - Weapon Two Sword",
        (object) "12 - Weapon Wand",
        (object) "13 - Weapon Scythe",
        (object) "14 - Weapon Polearm",
        (object) "15 - Weapon Soul"
      });
      this.comboBox18.Items.AddRange(new object[17]
      {
        (object) "-1",
        (object) "0 - Weapon Night",
        (object) "1 - Weapon Crossbow",
        (object) "2 - Weapon Staff",
        (object) "3 - Weapon Big Sword",
        (object) "4 - Weapon Axe",
        (object) "5 - Weapon Short Staff",
        (object) "6 - Weapon Bow",
        (object) "7 - Weapon ShortGum",
        (object) "8 - Weapon Mining",
        (object) "9 - Weapon Gathering",
        (object) "10 - Weapon Charge",
        (object) "11 - Weapon Two Sword",
        (object) "12 - Weapon Wand",
        (object) "13 - Weapon Scythe",
        (object) "14 - Weapon Polearm",
        (object) "15 - Weapon Soul"
      });
    }

    private void textBox12_TextChanged(object sender, EventArgs e)
    {
    }

    private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox2.Text = this.GetIndexByComboBox(this.comboBox1.Text).ToString();
      if (this.textBox2.Text == "0")
      {
        this.comboBox2.Visible = true;
        this.comboBox3.Visible = false;
        this.comboBox4.Visible = false;
        this.comboBox5.Visible = false;
        this.comboBox6.Visible = false;
        this.comboBox7.Visible = false;
        this.comboBox8.Visible = false;
        this.comboBox9.Visible = false;
        this.comboBox10.Visible = false;
        this.comboBox11.Visible = false;
        this.comboBox12.Visible = false;
        this.comboBox13.Visible = false;
        this.comboBox14.Visible = false;
      }
      else if (this.textBox2.Text == "1")
      {
        this.comboBox2.Visible = false;
        this.comboBox3.Visible = true;
        this.comboBox4.Visible = false;
        this.comboBox5.Visible = false;
        this.comboBox6.Visible = false;
        this.comboBox7.Visible = false;
        this.comboBox8.Visible = false;
        this.comboBox9.Visible = false;
        this.comboBox10.Visible = false;
        this.comboBox11.Visible = false;
        this.comboBox12.Visible = false;
        this.comboBox13.Visible = false;
        this.comboBox14.Visible = false;
      }
      else if (this.textBox2.Text == "2")
      {
        this.comboBox2.Visible = false;
        this.comboBox3.Visible = false;
        this.comboBox4.Visible = true;
        this.comboBox5.Visible = false;
        this.comboBox6.Visible = false;
        this.comboBox7.Visible = false;
        this.comboBox8.Visible = false;
        this.comboBox9.Visible = false;
        this.comboBox10.Visible = false;
        this.comboBox11.Visible = false;
        this.comboBox12.Visible = false;
        this.comboBox13.Visible = false;
        this.comboBox14.Visible = false;
      }
      else if (this.textBox2.Text == "3")
      {
        this.comboBox2.Visible = false;
        this.comboBox3.Visible = false;
        this.comboBox4.Visible = false;
        this.comboBox5.Visible = true;
        this.comboBox6.Visible = false;
        this.comboBox7.Visible = false;
        this.comboBox8.Visible = false;
        this.comboBox9.Visible = false;
        this.comboBox10.Visible = false;
        this.comboBox11.Visible = false;
        this.comboBox12.Visible = false;
        this.comboBox13.Visible = false;
        this.comboBox14.Visible = false;
      }
      else if (this.textBox2.Text == "4")
      {
        this.comboBox4.Visible = false;
        this.comboBox5.Visible = false;
        this.comboBox6.Visible = true;
        this.comboBox7.Visible = false;
        this.comboBox8.Visible = false;
        this.comboBox9.Visible = false;
        this.comboBox10.Visible = false;
        this.comboBox11.Visible = false;
        this.comboBox12.Visible = false;
        this.comboBox13.Visible = false;
        this.comboBox14.Visible = false;
        this.comboBox2.Visible = false;
        this.comboBox3.Visible = false;
      }
      else if (this.textBox2.Text == "5")
      {
        this.comboBox2.Visible = false;
        this.comboBox3.Visible = false;
        this.comboBox4.Visible = false;
        this.comboBox5.Visible = false;
        this.comboBox6.Visible = false;
        this.comboBox7.Visible = true;
        this.comboBox8.Visible = false;
        this.comboBox9.Visible = false;
        this.comboBox10.Visible = false;
        this.comboBox11.Visible = false;
        this.comboBox12.Visible = false;
        this.comboBox13.Visible = false;
        this.comboBox14.Visible = false;
      }
      else if (this.textBox2.Text == "6")
      {
        this.comboBox2.Visible = false;
        this.comboBox3.Visible = false;
        this.comboBox4.Visible = false;
        this.comboBox5.Visible = false;
        this.comboBox6.Visible = false;
        this.comboBox7.Visible = false;
        this.comboBox8.Visible = true;
        this.comboBox9.Visible = false;
        this.comboBox10.Visible = false;
        this.comboBox11.Visible = false;
        this.comboBox12.Visible = false;
        this.comboBox13.Visible = false;
        this.comboBox14.Visible = false;
      }
      else if (this.textBox2.Text == "7")
      {
        this.comboBox2.Visible = false;
        this.comboBox3.Visible = false;
        this.comboBox4.Visible = false;
        this.comboBox5.Visible = false;
        this.comboBox6.Visible = false;
        this.comboBox7.Visible = false;
        this.comboBox8.Visible = false;
        this.comboBox9.Visible = true;
        this.comboBox10.Visible = false;
        this.comboBox11.Visible = false;
        this.comboBox12.Visible = false;
        this.comboBox13.Visible = false;
        this.comboBox14.Visible = false;
      }
      else if (this.textBox2.Text == "8")
      {
        this.comboBox2.Visible = false;
        this.comboBox3.Visible = false;
        this.comboBox4.Visible = false;
        this.comboBox5.Visible = false;
        this.comboBox6.Visible = false;
        this.comboBox7.Visible = false;
        this.comboBox8.Visible = false;
        this.comboBox9.Visible = false;
        this.comboBox10.Visible = true;
        this.comboBox11.Visible = false;
        this.comboBox12.Visible = false;
        this.comboBox13.Visible = false;
        this.comboBox14.Visible = false;
      }
      else if (this.textBox2.Text == "9")
      {
        this.comboBox2.Visible = false;
        this.comboBox3.Visible = false;
        this.comboBox4.Visible = false;
        this.comboBox5.Visible = false;
        this.comboBox6.Visible = false;
        this.comboBox7.Visible = false;
        this.comboBox8.Visible = false;
        this.comboBox9.Visible = false;
        this.comboBox10.Visible = false;
        this.comboBox11.Visible = true;
        this.comboBox12.Visible = false;
        this.comboBox13.Visible = false;
        this.comboBox14.Visible = false;
      }
      else if (this.textBox2.Text == "10")
      {
        this.comboBox2.Visible = false;
        this.comboBox3.Visible = false;
        this.comboBox4.Visible = false;
        this.comboBox5.Visible = false;
        this.comboBox6.Visible = false;
        this.comboBox7.Visible = false;
        this.comboBox8.Visible = false;
        this.comboBox9.Visible = false;
        this.comboBox10.Visible = false;
        this.comboBox11.Visible = false;
        this.comboBox12.Visible = true;
        this.comboBox13.Visible = false;
        this.comboBox14.Visible = false;
      }
      else if (this.textBox2.Text == "11")
      {
        this.comboBox2.Visible = false;
        this.comboBox3.Visible = false;
        this.comboBox4.Visible = false;
        this.comboBox5.Visible = false;
        this.comboBox6.Visible = false;
        this.comboBox7.Visible = false;
        this.comboBox8.Visible = false;
        this.comboBox9.Visible = false;
        this.comboBox10.Visible = false;
        this.comboBox11.Visible = false;
        this.comboBox12.Visible = false;
        this.comboBox13.Visible = true;
        this.comboBox14.Visible = false;
      }
      else
      {
        if (!(this.textBox2.Text == "999"))
          return;
        this.comboBox2.Visible = false;
        this.comboBox3.Visible = false;
        this.comboBox4.Visible = false;
        this.comboBox5.Visible = false;
        this.comboBox6.Visible = false;
        this.comboBox7.Visible = false;
        this.comboBox8.Visible = false;
        this.comboBox9.Visible = false;
        this.comboBox10.Visible = false;
        this.comboBox11.Visible = false;
        this.comboBox12.Visible = false;
        this.comboBox13.Visible = false;
        this.comboBox14.Visible = true;
      }
    }

    private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox3.Text = this.GetIndexByComboBox(this.comboBox2.Text).ToString();
    }

    private void comboBox3_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox3.Text = this.GetIndexByComboBox(this.comboBox3.Text).ToString();
    }

    private void comboBox4_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox3.Text = this.GetIndexByComboBox(this.comboBox4.Text).ToString();
    }

    private void comboBox5_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox3.Text = this.GetIndexByComboBox(this.comboBox5.Text).ToString();
    }

    private void comboBox6_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox3.Text = this.GetIndexByComboBox(this.comboBox6.Text).ToString();
    }

    private void comboBox7_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox3.Text = this.GetIndexByComboBox(this.comboBox7.Text).ToString();
    }

    private void comboBox8_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox3.Text = this.GetIndexByComboBox(this.comboBox8.Text).ToString();
    }

    private void comboBox9_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox3.Text = this.GetIndexByComboBox(this.comboBox9.Text).ToString();
    }

    private void comboBox10_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox3.Text = this.GetIndexByComboBox(this.comboBox10.Text).ToString();
    }

    private void comboBox11_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox3.Text = this.GetIndexByComboBox(this.comboBox11.Text).ToString();
    }

    private void comboBox12_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox3.Text = this.GetIndexByComboBox(this.comboBox12.Text).ToString();
    }

    private void comboBox13_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox3.Text = this.GetIndexByComboBox(this.comboBox13.Text).ToString();
    }

    private void comboBox14_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox3.Text = this.GetIndexByComboBox(this.comboBox14.Text).ToString();
    }

    private void comboBox15_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox6.Text = this.GetIndexByComboBox(this.comboBox15.Text).ToString();
    }

    private void comboBox16_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox13.Text = this.GetIndexByComboBox(this.comboBox16.Text).ToString();
    }

    private void comboBox17_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox16.Text = this.GetIndexByComboBox(this.comboBox17.Text).ToString();
    }

    private void comboBox18_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox17.Text = this.GetIndexByComboBox(this.comboBox18.Text).ToString();
    }

    private void exportSkilllodToolStripMenuItem_Click(object sender, EventArgs e)
    {
      this.exportLodhandle.ExportSkillAll_V4();
    }

    private void linkLabel1_LinkClicked_1(object sender, LinkLabelLinkClickedEventArgs e)
    {
      IconPickerSkill iconPickerSkill = new IconPickerSkill();
      iconPickerSkill.OldItemBtnSelect = Convert.ToInt32(this.textBox55.Text);
      if (iconPickerSkill.ShowDialog() != DialogResult.OK)
        return;
      this.textBox55.Text = iconPickerSkill.TexID.ToString();
      this.textBox57.Text = iconPickerSkill.TexColumn.ToString();
      this.textBox56.Text = iconPickerSkill.TexRow.ToString();
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_skill SET a_client_icon_texid = '" + this.textBox55.Text + "', a_client_icon_row = '" + this.textBox56.Text + "', a_client_icon_col = '" + this.textBox57.Text + "' WHERE a_index = '" + this.textBox1.Text + "'");
      int selectedIndex = this.listBox1.SelectedIndex;
      this.LoadListBox();
      this.listBox1.SelectedIndex = selectedIndex;
    }

    public bool SearchString(string s) => s.ToUpper().Contains(this.textBox203.Text.ToUpper());

    private void textBox203_TextChanged(object sender, EventArgs e)
    {
      this.MenuListSearch = this.MenuList.FindAll(new Predicate<string>(this.SearchString));
      this.listBox1.DataSource = (object) this.MenuListSearch;
    }

    private void Form4_Load(object sender, EventArgs e)
    {
      this.LoadStartUp();
      this.IconItem();
      this.IconSkill();
      this.comboBox19.SelectedIndex = 0;
      this.LoadListBox();
      this.LoadListBox2();
      this.SelectBoxes();
      this.tabControl1.TabPages.Remove(this.tabPage2);
    }

    private void pictureBox2_Click(object sender, EventArgs e)
    {
      FlagBuilder flagBuilder = new FlagBuilder();
      flagBuilder.flagSmall = Convert.ToInt32(this.textBox7.Text);
      flagBuilder.flagBuilderType = "skills";
      if (flagBuilder.ShowDialog() != DialogResult.OK)
        return;
      this.textBox7.Text = flagBuilder.flagSmall.ToString();
    }

    private void pictureBox2_MouseMove(object sender, MouseEventArgs e)
    {
      this.pictureBox2.Size = new Size(26, 26);
    }

    private void pictureBox2_MouseLeave(object sender, EventArgs e)
    {
      this.pictureBox2.Size = new Size(23, 28);
    }

    private void pictureBox3_MouseMove(object sender, MouseEventArgs e)
    {
      this.pictureBox3.Size = new Size(26, 26);
    }

    private void pictureBox3_MouseLeave(object sender, EventArgs e)
    {
      this.pictureBox3.Size = new Size(23, 28);
    }

    private void listBox2_SelectedIndexChanged(object sender, EventArgs e)
    {
      string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, "SELECT * FROM t_skillLevel WHERE a_index ='" + this.textBox1.Text + "' AND a_level = '" + this.listBox2.SelectedItem.ToString() + "';", new string[45]
      {
        "a_index",
        "a_level",
        "a_needHP",
        "a_needMP",
        "a_needGP",
        "a_durtime",
        "a_dummypower",
        "a_needItemIndex1",
        "a_needItemCount1",
        "a_needItemIndex2",
        "a_needItemCount2",
        "a_learnLevel",
        "a_learnSP",
        "a_learnSkillIndex1",
        "a_learnSkillLevel1",
        "a_learnSkillIndex2",
        "a_learnSkillLevel2",
        "a_learnSkillIndex3",
        "a_learnSkillLevel3",
        "a_learnItemIndex1",
        "a_learnItemCount1",
        "a_learnItemIndex2",
        "a_learnItemCount2",
        "a_learnItemIndex3",
        "a_learnItemCount3",
        "a_appMagicIndex1",
        "a_appMagicLevel1",
        "a_appMagicIndex2",
        "a_appMagicLevel2",
        "a_appMagicIndex3",
        "a_appMagicLevel3",
        "a_magicIndex1",
        "a_magicLevel1",
        "a_magicIndex2",
        "a_magicLevel2",
        "a_magicIndex3",
        "a_magicLevel3",
        "a_learnstr",
        "a_learndex",
        "a_learnint",
        "a_learncon",
        "a_hate",
        "a_learnGP",
        "a_use_count",
        "a_targetNum"
      });
      this.textBox84.Text = strArray[0];
      this.textBox85.Text = strArray[1];
      this.textBox86.Text = strArray[2];
      this.textBox87.Text = strArray[3];
      this.textBox88.Text = strArray[4];
      this.textBox89.Text = strArray[5];
      this.textBox90.Text = strArray[6];
      this.textBox91.Text = strArray[7];
      this.textBox92.Text = strArray[8];
      this.textBox93.Text = strArray[9];
      this.textBox94.Text = strArray[10];
      this.textBox95.Text = strArray[11];
      this.textBox96.Text = strArray[12];
      this.textBox97.Text = strArray[13];
      this.textBox98.Text = strArray[14];
      this.textBox99.Text = strArray[15];
      this.textBox100.Text = strArray[16];
      this.textBox101.Text = strArray[17];
      this.textBox102.Text = strArray[18];
      this.textBox103.Text = strArray[19];
      this.textBox104.Text = strArray[20];
      this.textBox105.Text = strArray[21];
      this.textBox106.Text = strArray[22];
      this.textBox107.Text = strArray[23];
      this.textBox108.Text = strArray[24];
      this.textBox109.Text = strArray[25];
      this.textBox110.Text = strArray[26];
      this.textBox111.Text = strArray[27];
      this.textBox112.Text = strArray[28];
      this.textBox113.Text = strArray[29];
      this.textBox114.Text = strArray[30];
      this.textBox115.Text = strArray[31];
      this.textBox116.Text = strArray[32];
      this.textBox117.Text = strArray[33];
      this.textBox118.Text = strArray[34];
      this.textBox119.Text = strArray[35];
      this.textBox120.Text = strArray[36];
      this.textBox121.Text = strArray[37];
      this.textBox122.Text = strArray[38];
      this.textBox123.Text = strArray[39];
      this.textBox124.Text = strArray[40];
      this.textBox125.Text = strArray[41];
      this.textBox126.Text = strArray[42];
      this.textBox127.Text = strArray[43];
      this.textBox128.Text = strArray[44];
      this.IconSkill();
      this.IconItem();
      this.ClearPicture();
      try
      {
        this.pictureBox4.Image = (Image) this.databaseHandle.IconItem(int.Parse(this.textBox129.Text), int.Parse(this.textBox130.Text), int.Parse(this.textBox131.Text));
        this.pictureBox5.Image = (Image) this.databaseHandle.IconItem(int.Parse(this.textBox133.Text), int.Parse(this.textBox134.Text), int.Parse(this.textBox135.Text));
      }
      catch
      {
      }
      try
      {
        this.pictureBox6.Image = (Image) this.databaseHandle.IconSkill1(int.Parse(this.textBox137.Text), int.Parse(this.textBox138.Text), int.Parse(this.textBox139.Text));
        this.pictureBox7.Image = (Image) this.databaseHandle.IconSkill1(int.Parse(this.textBox141.Text), int.Parse(this.textBox142.Text), int.Parse(this.textBox143.Text));
        this.pictureBox8.Image = (Image) this.databaseHandle.IconSkill1(int.Parse(this.textBox145.Text), int.Parse(this.textBox146.Text), int.Parse(this.textBox147.Text));
      }
      catch
      {
      }
      try
      {
        this.pictureBox9.Image = (Image) this.databaseHandle.IconItem(int.Parse(this.textBox150.Text), int.Parse(this.textBox151.Text), int.Parse(this.textBox152.Text));
        this.pictureBox10.Image = (Image) this.databaseHandle.IconItem(int.Parse(this.textBox153.Text), int.Parse(this.textBox154.Text), int.Parse(this.textBox155.Text));
        this.pictureBox11.Image = (Image) this.databaseHandle.IconItem(int.Parse(this.textBox157.Text), int.Parse(this.textBox158.Text), int.Parse(this.textBox159.Text));
      }
      catch
      {
      }
    }

    private void comboBox19_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.comboBox20.Items.Clear();
      string str = this.GetIndexByComboBox(this.comboBox19.Text).ToString();
      this.comboBox20.Items.AddRange((object[]) Types.JobSubTypes(Convert.ToInt32(str)));
      this.comboBox20.SelectedIndex = 0;
      this.mSortJob = str;
      this.LoadListBox();
    }

    private void comboBox20_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.mSortJob2 = this.GetIndexByComboBox(this.comboBox20.Text).ToString();
      this.LoadListBox();
    }

    private void pictureBox4_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox91.Text = itemPicker.ItemIndex.ToString();
    }

    private void pictureBox5_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox93.Text = itemPicker.ItemIndex.ToString();
    }

    private void pictureBox9_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox103.Text = itemPicker.ItemIndex.ToString();
    }

    private void pictureBox10_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox105.Text = itemPicker.ItemIndex.ToString();
    }

    private void pictureBox11_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox107.Text = itemPicker.ItemIndex.ToString();
    }

    private void button4_Click(object sender, EventArgs e)
    {
    }

    private void menuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
    {
    }

    private void button5_Click(object sender, EventArgs e)
    {
    }

    [DllImport("user32.dll", CharSet = CharSet.Auto)]
    public static extern int AnimateWindow(IntPtr hwand, int dwTime, int dwFlags);

    private void button6_Click(object sender, EventArgs e)
    {
      string Query = "UPDATE t_skillLevel SET a_needHP = '" + this.textBox86.Text + "',a_needMP = '" + this.textBox87.Text + "',a_needGP = '" + this.textBox88.Text + "',a_durtime = '" + this.textBox89.Text + "',a_dummypower = '" + this.textBox90.Text + "',a_needItemIndex1 = '" + this.textBox91.Text + "',a_needItemCount1 = '" + this.textBox92.Text + "',a_needItemIndex2 = '" + this.textBox93.Text + "',a_needItemCount2 = '" + this.textBox94.Text + "',a_learnLevel = '" + this.textBox95.Text + "',a_learnSP = '" + this.textBox96.Text + "',a_learnSkillIndex1 = '" + this.textBox97.Text + "',a_learnSkillLevel1 = '" + this.textBox98.Text + "',a_learnSkillIndex2 = '" + this.textBox99.Text + "',a_learnSkillLevel2 = '" + this.textBox100.Text + "',a_learnSkillIndex3 = '" + this.textBox101.Text + "',a_learnSkillLevel3 = '" + this.textBox102.Text + "',a_learnItemIndex1 = '" + this.textBox103.Text + "',a_learnItemCount1 = '" + this.textBox104.Text + "',a_learnItemIndex2 = '" + this.textBox105.Text + "',a_learnItemCount2 = '" + this.textBox106.Text + "',a_learnItemIndex3 = '" + this.textBox107.Text + "',a_learnItemCount3 = '" + this.textBox108.Text + "',a_appMagicIndex1 = '" + this.textBox109.Text + "',a_appMagicLevel1 = '" + this.textBox110.Text + "',a_appMagicIndex2 = '" + this.textBox111.Text + "',a_appMagicLevel2 = '" + this.textBox112.Text + "',a_appMagicIndex3 = '" + this.textBox113.Text + "',a_appMagicLevel3 = '" + this.textBox114.Text + "',a_magicIndex1 = '" + this.textBox115.Text + "',a_magicLevel1 = '" + this.textBox116.Text + "',a_magicIndex2 = '" + this.textBox117.Text + "',a_magicLevel2 = '" + this.textBox118.Text + "',a_magicIndex3 = '" + this.textBox119.Text + "',a_magicLevel3 = '" + this.textBox120.Text + "',a_learnstr = '" + this.textBox121.Text + "',a_learndex = '" + this.textBox122.Text + "',a_learnint = '" + this.textBox123.Text + "',a_learncon = '" + this.textBox124.Text + "',a_hate = '" + this.textBox125.Text + "',a_learnGP = '" + this.textBox126.Text + "',a_use_count = '" + this.textBox127.Text + "',a_targetNum = '" + this.textBox128.Text + "'WHERE a_index = '" + this.textBox1.Text + "' AND a_level = '" + this.textBox85.Text + "'";
      Console.WriteLine(Query);
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, Query);
      this.LoadListBox2();
      this.label130.Text = "Save level succesfully!";
      this.label130.ForeColor = Color.Lime;
      this.label130.Visible = true;
      this.listBox2.SelectedIndex = this.listBox2.SelectedIndex;
    }

    private void button4_Click_1(object sender, EventArgs e)
    {
      string Query = "INSERT INTO t_skillLevel (a_index, a_level) VALUES ('" + this.textBox1.Text + "', '" + Convert.ToString(this.listBox2.Items.Count + 1) + "')";
      Console.WriteLine(Query);
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, Query);
      this.LoadListBox2();
      this.listBox2.SelectedIndex = this.listBox2.Items.Count - 1;
    }

    private void button5_Click_1(object sender, EventArgs e)
    {
      string Query = "DELETE FROM t_skillLevel WHERE a_index = '" + this.textBox1.Text + "' AND a_level ='" + this.textBox85.Text + "'";
      Console.WriteLine(Query);
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, Query);
      this.LoadListBox2();
      this.listBox2.SelectedIndex = this.listBox2.Items.Count - 1;
    }

    private void pictureBox6_Click(object sender, EventArgs e)
    {
      SkillPicker skillPicker = new SkillPicker();
      if (skillPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox97.Text = skillPicker.SkillIndex.ToString();
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
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (SkillEditorV1));
      this.menuStrip1 = new MenuStrip();
      this.fileExportToolStripMenuItem = new ToolStripMenuItem();
      this.exportSkilllodToolStripMenuItem = new ToolStripMenuItem();
      this.exportStrSkillsusalodToolStripMenuItem = new ToolStripMenuItem();
      this.groupBox3 = new GroupBox();
      this.button3 = new Button();
      this.button1 = new Button();
      this.listBox1 = new ListBox();
      this.groupBox5 = new GroupBox();
      this.label139 = new Label();
      this.label138 = new Label();
      this.comboBox19 = new ComboBox();
      this.comboBox20 = new ComboBox();
      this.textBox203 = new TextBox();
      this.label7 = new Label();
      this.tabControl1 = new TabControl();
      this.tabPage1 = new TabPage();
      this.tabControl2 = new TabControl();
      this.tabPage5 = new TabPage();
      this.groupBox26 = new GroupBox();
      this.label115 = new Label();
      this.textBox114 = new TextBox();
      this.label114 = new Label();
      this.textBox113 = new TextBox();
      this.label113 = new Label();
      this.textBox112 = new TextBox();
      this.label112 = new Label();
      this.textBox111 = new TextBox();
      this.label111 = new Label();
      this.textBox110 = new TextBox();
      this.label110 = new Label();
      this.textBox109 = new TextBox();
      this.groupBox30 = new GroupBox();
      this.textBox128 = new TextBox();
      this.textBox85 = new TextBox();
      this.label129 = new Label();
      this.label86 = new Label();
      this.textBox89 = new TextBox();
      this.label90 = new Label();
      this.textBox90 = new TextBox();
      this.label91 = new Label();
      this.groupBox25 = new GroupBox();
      this.label128 = new Label();
      this.textBox127 = new TextBox();
      this.label127 = new Label();
      this.textBox126 = new TextBox();
      this.label126 = new Label();
      this.textBox125 = new TextBox();
      this.groupBox28 = new GroupBox();
      this.textBox124 = new TextBox();
      this.textBox123 = new TextBox();
      this.textBox122 = new TextBox();
      this.textBox121 = new TextBox();
      this.label125 = new Label();
      this.label124 = new Label();
      this.label123 = new Label();
      this.label122 = new Label();
      this.label109 = new Label();
      this.textBox108 = new TextBox();
      this.label108 = new Label();
      this.textBox106 = new TextBox();
      this.label107 = new Label();
      this.textBox104 = new TextBox();
      this.textBox107 = new TextBox();
      this.label106 = new Label();
      this.textBox105 = new TextBox();
      this.label105 = new Label();
      this.textBox103 = new TextBox();
      this.label104 = new Label();
      this.textBox102 = new TextBox();
      this.label103 = new Label();
      this.label102 = new Label();
      this.textBox101 = new TextBox();
      this.textBox100 = new TextBox();
      this.label101 = new Label();
      this.label100 = new Label();
      this.textBox99 = new TextBox();
      this.textBox98 = new TextBox();
      this.label99 = new Label();
      this.label98 = new Label();
      this.textBox97 = new TextBox();
      this.label97 = new Label();
      this.textBox96 = new TextBox();
      this.label96 = new Label();
      this.textBox95 = new TextBox();
      this.pictureBox6 = new PictureBox();
      this.pictureBox7 = new PictureBox();
      this.pictureBox8 = new PictureBox();
      this.pictureBox9 = new PictureBox();
      this.pictureBox10 = new PictureBox();
      this.pictureBox11 = new PictureBox();
      this.groupBox27 = new GroupBox();
      this.textBox120 = new TextBox();
      this.label121 = new Label();
      this.textBox119 = new TextBox();
      this.label120 = new Label();
      this.textBox118 = new TextBox();
      this.label119 = new Label();
      this.textBox117 = new TextBox();
      this.label118 = new Label();
      this.textBox116 = new TextBox();
      this.label117 = new Label();
      this.textBox115 = new TextBox();
      this.label116 = new Label();
      this.groupBox23 = new GroupBox();
      this.label95 = new Label();
      this.textBox94 = new TextBox();
      this.pictureBox5 = new PictureBox();
      this.label94 = new Label();
      this.textBox93 = new TextBox();
      this.label93 = new Label();
      this.textBox92 = new TextBox();
      this.pictureBox4 = new PictureBox();
      this.label92 = new Label();
      this.textBox91 = new TextBox();
      this.label89 = new Label();
      this.textBox88 = new TextBox();
      this.textBox87 = new TextBox();
      this.label88 = new Label();
      this.textBox86 = new TextBox();
      this.label87 = new Label();
      this.groupBox7 = new GroupBox();
      this.button5 = new Button();
      this.button4 = new Button();
      this.listBox2 = new ListBox();
      this.textBox136 = new TextBox();
      this.textBox132 = new TextBox();
      this.groupBox22 = new GroupBox();
      this.pictureBox1 = new PictureBox();
      this.linkLabel1 = new LinkLabel();
      this.label75 = new Label();
      this.label74 = new Label();
      this.textBox57 = new TextBox();
      this.textBox56 = new TextBox();
      this.label73 = new Label();
      this.textBox55 = new TextBox();
      this.groupBox21 = new GroupBox();
      this.textBox52 = new TextBox();
      this.label70 = new Label();
      this.groupBox8 = new GroupBox();
      this.label31 = new Label();
      this.textBox32 = new TextBox();
      this.label30 = new Label();
      this.textBox31 = new TextBox();
      this.label29 = new Label();
      this.textBox30 = new TextBox();
      this.label28 = new Label();
      this.textBox29 = new TextBox();
      this.groupBox11 = new GroupBox();
      this.textBox22 = new TextBox();
      this.textBox23 = new TextBox();
      this.textBox24 = new TextBox();
      this.label25 = new Label();
      this.label24 = new Label();
      this.label23 = new Label();
      this.label22 = new Label();
      this.label21 = new Label();
      this.label20 = new Label();
      this.textBox21 = new TextBox();
      this.textBox19 = new TextBox();
      this.textBox20 = new TextBox();
      this.groupBox10 = new GroupBox();
      this.label19 = new Label();
      this.comboBox18 = new ComboBox();
      this.textBox17 = new TextBox();
      this.comboBox17 = new ComboBox();
      this.label18 = new Label();
      this.textBox16 = new TextBox();
      this.groupBox9 = new GroupBox();
      this.label26 = new Label();
      this.label17 = new Label();
      this.textBox14 = new TextBox();
      this.textBox13 = new TextBox();
      this.comboBox16 = new ComboBox();
      this.groupBox6 = new GroupBox();
      this.pictureBox3 = new PictureBox();
      this.label82 = new Label();
      this.textBox81 = new TextBox();
      this.pictureBox2 = new PictureBox();
      this.label78 = new Label();
      this.textBox7 = new TextBox();
      this.groupBox4 = new GroupBox();
      this.textBox25 = new TextBox();
      this.textBox15 = new TextBox();
      this.label16 = new Label();
      this.label8 = new Label();
      this.textBox6 = new TextBox();
      this.label15 = new Label();
      this.comboBox15 = new ComboBox();
      this.textBox9 = new TextBox();
      this.label14 = new Label();
      this.label11 = new Label();
      this.textBox12 = new TextBox();
      this.textBox10 = new TextBox();
      this.label13 = new Label();
      this.label12 = new Label();
      this.textBox11 = new TextBox();
      this.groupBox2 = new GroupBox();
      this.textBox82 = new TextBox();
      this.label83 = new Label();
      this.comboBox1 = new ComboBox();
      this.label2 = new Label();
      this.label3 = new Label();
      this.textBox2 = new TextBox();
      this.comboBox14 = new ComboBox();
      this.textBox3 = new TextBox();
      this.comboBox3 = new ComboBox();
      this.comboBox5 = new ComboBox();
      this.comboBox10 = new ComboBox();
      this.comboBox13 = new ComboBox();
      this.comboBox9 = new ComboBox();
      this.comboBox11 = new ComboBox();
      this.comboBox2 = new ComboBox();
      this.comboBox6 = new ComboBox();
      this.comboBox7 = new ComboBox();
      this.comboBox4 = new ComboBox();
      this.comboBox12 = new ComboBox();
      this.comboBox8 = new ComboBox();
      this.groupBox1 = new GroupBox();
      this.textBox54 = new TextBox();
      this.label71 = new Label();
      this.label6 = new Label();
      this.textBox5 = new TextBox();
      this.label5 = new Label();
      this.textBox4 = new TextBox();
      this.textBox1 = new TextBox();
      this.label1 = new Label();
      this.tabPage3 = new TabPage();
      this.groupBox12 = new GroupBox();
      this.groupBox20 = new GroupBox();
      this.textBox76 = new TextBox();
      this.textBox75 = new TextBox();
      this.textBox74 = new TextBox();
      this.textBox73 = new TextBox();
      this.textBox72 = new TextBox();
      this.textBox71 = new TextBox();
      this.label64 = new Label();
      this.label65 = new Label();
      this.label66 = new Label();
      this.label67 = new Label();
      this.label68 = new Label();
      this.label69 = new Label();
      this.groupBox19 = new GroupBox();
      this.textBox51 = new TextBox();
      this.textBox50 = new TextBox();
      this.textBox49 = new TextBox();
      this.textBox48 = new TextBox();
      this.textBox47 = new TextBox();
      this.textBox46 = new TextBox();
      this.label63 = new Label();
      this.label62 = new Label();
      this.label61 = new Label();
      this.label60 = new Label();
      this.label59 = new Label();
      this.label58 = new Label();
      this.groupBox18 = new GroupBox();
      this.textBox70 = new TextBox();
      this.textBox69 = new TextBox();
      this.textBox68 = new TextBox();
      this.textBox67 = new TextBox();
      this.textBox66 = new TextBox();
      this.textBox65 = new TextBox();
      this.label52 = new Label();
      this.label53 = new Label();
      this.label54 = new Label();
      this.label55 = new Label();
      this.label56 = new Label();
      this.label57 = new Label();
      this.groupBox17 = new GroupBox();
      this.textBox45 = new TextBox();
      this.textBox44 = new TextBox();
      this.textBox43 = new TextBox();
      this.textBox42 = new TextBox();
      this.textBox41 = new TextBox();
      this.textBox40 = new TextBox();
      this.label51 = new Label();
      this.label50 = new Label();
      this.label49 = new Label();
      this.label48 = new Label();
      this.label47 = new Label();
      this.label46 = new Label();
      this.groupBox16 = new GroupBox();
      this.textBox64 = new TextBox();
      this.textBox63 = new TextBox();
      this.textBox62 = new TextBox();
      this.textBox59 = new TextBox();
      this.label42 = new Label();
      this.label43 = new Label();
      this.label44 = new Label();
      this.label45 = new Label();
      this.groupBox15 = new GroupBox();
      this.textBox39 = new TextBox();
      this.textBox38 = new TextBox();
      this.textBox37 = new TextBox();
      this.textBox34 = new TextBox();
      this.label41 = new Label();
      this.label40 = new Label();
      this.label39 = new Label();
      this.label38 = new Label();
      this.groupBox14 = new GroupBox();
      this.textBox61 = new TextBox();
      this.textBox60 = new TextBox();
      this.textBox58 = new TextBox();
      this.label35 = new Label();
      this.label36 = new Label();
      this.label37 = new Label();
      this.groupBox13 = new GroupBox();
      this.textBox36 = new TextBox();
      this.textBox35 = new TextBox();
      this.label34 = new Label();
      this.label33 = new Label();
      this.label32 = new Label();
      this.textBox33 = new TextBox();
      this.tabPage2 = new TabPage();
      this.textBox160 = new TextBox();
      this.textBox156 = new TextBox();
      this.textBox157 = new TextBox();
      this.textBox159 = new TextBox();
      this.textBox153 = new TextBox();
      this.textBox154 = new TextBox();
      this.textBox155 = new TextBox();
      this.textBox149 = new TextBox();
      this.textBox150 = new TextBox();
      this.textBox151 = new TextBox();
      this.textBox152 = new TextBox();
      this.textBox158 = new TextBox();
      this.textBox145 = new TextBox();
      this.textBox146 = new TextBox();
      this.textBox147 = new TextBox();
      this.label137 = new Label();
      this.textBox141 = new TextBox();
      this.textBox142 = new TextBox();
      this.textBox143 = new TextBox();
      this.label136 = new Label();
      this.textBox129 = new TextBox();
      this.textBox133 = new TextBox();
      this.textBox137 = new TextBox();
      this.textBox138 = new TextBox();
      this.textBox139 = new TextBox();
      this.textBox84 = new TextBox();
      this.textBox134 = new TextBox();
      this.textBox135 = new TextBox();
      this.label85 = new Label();
      this.textBox130 = new TextBox();
      this.textBox131 = new TextBox();
      this.label135 = new Label();
      this.textBox148 = new TextBox();
      this.textBox140 = new TextBox();
      this.textBox144 = new TextBox();
      this.tabPage4 = new TabPage();
      this.label84 = new Label();
      this.textBox83 = new TextBox();
      this.label81 = new Label();
      this.textBox80 = new TextBox();
      this.label80 = new Label();
      this.label79 = new Label();
      this.textBox8 = new TextBox();
      this.label9 = new Label();
      this.textBox79 = new TextBox();
      this.label77 = new Label();
      this.textBox18 = new TextBox();
      this.textBox78 = new TextBox();
      this.label76 = new Label();
      this.textBox77 = new TextBox();
      this.label72 = new Label();
      this.label27 = new Label();
      this.textBox28 = new TextBox();
      this.textBox53 = new TextBox();
      this.label10 = new Label();
      this.textBox27 = new TextBox();
      this.label4 = new Label();
      this.textBox26 = new TextBox();
      this.button6 = new Button();
      this.button2 = new Button();
      this.toolTip1 = new ToolTip(this.components);
      this.label130 = new Label();
      this.menuStrip1.SuspendLayout();
      this.groupBox3.SuspendLayout();
      this.groupBox5.SuspendLayout();
      this.tabControl1.SuspendLayout();
      this.tabPage1.SuspendLayout();
      this.tabControl2.SuspendLayout();
      this.tabPage5.SuspendLayout();
      this.groupBox26.SuspendLayout();
      this.groupBox30.SuspendLayout();
      this.groupBox25.SuspendLayout();
      this.groupBox28.SuspendLayout();
      ((ISupportInitialize) this.pictureBox6).BeginInit();
      ((ISupportInitialize) this.pictureBox7).BeginInit();
      ((ISupportInitialize) this.pictureBox8).BeginInit();
      ((ISupportInitialize) this.pictureBox9).BeginInit();
      ((ISupportInitialize) this.pictureBox10).BeginInit();
      ((ISupportInitialize) this.pictureBox11).BeginInit();
      this.groupBox27.SuspendLayout();
      this.groupBox23.SuspendLayout();
      ((ISupportInitialize) this.pictureBox5).BeginInit();
      ((ISupportInitialize) this.pictureBox4).BeginInit();
      this.groupBox7.SuspendLayout();
      this.groupBox22.SuspendLayout();
      ((ISupportInitialize) this.pictureBox1).BeginInit();
      this.groupBox21.SuspendLayout();
      this.groupBox8.SuspendLayout();
      this.groupBox11.SuspendLayout();
      this.groupBox10.SuspendLayout();
      this.groupBox9.SuspendLayout();
      this.groupBox6.SuspendLayout();
      ((ISupportInitialize) this.pictureBox3).BeginInit();
      ((ISupportInitialize) this.pictureBox2).BeginInit();
      this.groupBox4.SuspendLayout();
      this.groupBox2.SuspendLayout();
      this.groupBox1.SuspendLayout();
      this.tabPage3.SuspendLayout();
      this.groupBox12.SuspendLayout();
      this.groupBox20.SuspendLayout();
      this.groupBox19.SuspendLayout();
      this.groupBox18.SuspendLayout();
      this.groupBox17.SuspendLayout();
      this.groupBox16.SuspendLayout();
      this.groupBox15.SuspendLayout();
      this.groupBox14.SuspendLayout();
      this.groupBox13.SuspendLayout();
      this.tabPage2.SuspendLayout();
      this.tabPage4.SuspendLayout();
      this.SuspendLayout();
      this.menuStrip1.AllowMerge = false;
      this.menuStrip1.BackColor = SystemColors.ControlLightLight;
      this.menuStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.fileExportToolStripMenuItem
      });
      this.menuStrip1.Location = new Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new Size(1346, 24);
      this.menuStrip1.TabIndex = 0;
      this.menuStrip1.Text = "menuStrip1";
      this.menuStrip1.ItemClicked += new ToolStripItemClickedEventHandler(this.menuStrip1_ItemClicked);
      this.fileExportToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[2]
      {
        (ToolStripItem) this.exportSkilllodToolStripMenuItem,
        (ToolStripItem) this.exportStrSkillsusalodToolStripMenuItem
      });
      this.fileExportToolStripMenuItem.Name = "fileExportToolStripMenuItem";
      this.fileExportToolStripMenuItem.Size = new Size(73, 20);
      this.fileExportToolStripMenuItem.Text = "File Export";
      this.exportSkilllodToolStripMenuItem.Name = "exportSkilllodToolStripMenuItem";
      this.exportSkilllodToolStripMenuItem.Size = new Size(192, 22);
      this.exportSkilllodToolStripMenuItem.Text = "Export skills.lod";
      this.exportSkilllodToolStripMenuItem.Click += new EventHandler(this.exportSkilllodToolStripMenuItem_Click);
      this.exportStrSkillsusalodToolStripMenuItem.Name = "exportStrSkillsusalodToolStripMenuItem";
      this.exportStrSkillsusalodToolStripMenuItem.Size = new Size(192, 22);
      this.exportStrSkillsusalodToolStripMenuItem.Text = "Export strSkills_usa.lod";
      this.groupBox3.Controls.Add((Control) this.button3);
      this.groupBox3.Controls.Add((Control) this.button1);
      this.groupBox3.Controls.Add((Control) this.listBox1);
      this.groupBox3.Location = new Point(12, 140);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Size = new Size(265, 547);
      this.groupBox3.TabIndex = 31;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "Skills";
      this.button3.FlatStyle = FlatStyle.Flat;
      this.button3.Font = new Font("Microsoft Sans Serif", 8.25f, FontStyle.Bold, GraphicsUnit.Point, (byte) 0);
      this.button3.Location = new Point(133, 510);
      this.button3.Name = "button3";
      this.button3.Size = new Size(126, 31);
      this.button3.TabIndex = 4;
      this.button3.Text = "Delete";
      this.button3.UseVisualStyleBackColor = true;
      this.button3.Click += new EventHandler(this.button3_Click);
      this.button1.FlatStyle = FlatStyle.Flat;
      this.button1.Font = new Font("Microsoft Sans Serif", 8.25f, FontStyle.Bold, GraphicsUnit.Point, (byte) 0);
      this.button1.Location = new Point(6, 510);
      this.button1.Name = "button1";
      this.button1.Size = new Size(121, 31);
      this.button1.TabIndex = 2;
      this.button1.Text = "Add";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.listBox1.FormattingEnabled = true;
      this.listBox1.Location = new Point(6, 19);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new Size(253, 485);
      this.listBox1.TabIndex = 1;
      this.listBox1.SelectedIndexChanged += new EventHandler(this.listBox1_SelectedIndexChanged);
      this.groupBox5.Controls.Add((Control) this.label139);
      this.groupBox5.Controls.Add((Control) this.label138);
      this.groupBox5.Controls.Add((Control) this.comboBox19);
      this.groupBox5.Controls.Add((Control) this.comboBox20);
      this.groupBox5.Controls.Add((Control) this.textBox203);
      this.groupBox5.Controls.Add((Control) this.label7);
      this.groupBox5.Location = new Point(12, 27);
      this.groupBox5.Name = "groupBox5";
      this.groupBox5.Size = new Size(265, 107);
      this.groupBox5.TabIndex = 32;
      this.groupBox5.TabStop = false;
      this.groupBox5.Text = "Search";
      this.label139.AutoSize = true;
      this.label139.Location = new Point(6, 76);
      this.label139.Name = "label139";
      this.label139.Size = new Size(27, 13);
      this.label139.TabIndex = 52;
      this.label139.Text = "Job:";
      this.label138.AutoSize = true;
      this.label138.Location = new Point(6, 51);
      this.label138.Name = "label138";
      this.label138.Size = new Size(35, 13);
      this.label138.TabIndex = 51;
      this.label138.Text = "Class:";
      this.comboBox19.FlatStyle = FlatStyle.Flat;
      this.comboBox19.FormattingEnabled = true;
      this.comboBox19.Location = new Point(43, 46);
      this.comboBox19.Name = "comboBox19";
      this.comboBox19.Size = new Size(204, 21);
      this.comboBox19.TabIndex = 50;
      this.comboBox19.SelectedIndexChanged += new EventHandler(this.comboBox19_SelectedIndexChanged);
      this.comboBox20.FlatStyle = FlatStyle.Flat;
      this.comboBox20.FormattingEnabled = true;
      this.comboBox20.Location = new Point(43, 73);
      this.comboBox20.Name = "comboBox20";
      this.comboBox20.Size = new Size(204, 21);
      this.comboBox20.TabIndex = 49;
      this.comboBox20.SelectedIndexChanged += new EventHandler(this.comboBox20_SelectedIndexChanged);
      this.textBox203.BorderStyle = BorderStyle.FixedSingle;
      this.textBox203.Location = new Point(43, 18);
      this.textBox203.Name = "textBox203";
      this.textBox203.Size = new Size(204, 20);
      this.textBox203.TabIndex = 22;
      this.textBox203.TextChanged += new EventHandler(this.textBox203_TextChanged);
      this.label7.AutoSize = true;
      this.label7.Location = new Point(6, 21);
      this.label7.Name = "label7";
      this.label7.Size = new Size(31, 13);
      this.label7.TabIndex = 21;
      this.label7.Text = "Text:";
      this.tabControl1.Controls.Add((Control) this.tabPage1);
      this.tabControl1.Controls.Add((Control) this.tabPage3);
      this.tabControl1.Controls.Add((Control) this.tabPage2);
      this.tabControl1.Controls.Add((Control) this.tabPage4);
      this.tabControl1.Location = new Point(283, 27);
      this.tabControl1.Name = "tabControl1";
      this.tabControl1.SelectedIndex = 0;
      this.tabControl1.Size = new Size(1049, 624);
      this.tabControl1.TabIndex = 33;
      this.tabPage1.BorderStyle = BorderStyle.FixedSingle;
      this.tabPage1.Controls.Add((Control) this.tabControl2);
      this.tabPage1.Controls.Add((Control) this.textBox136);
      this.tabPage1.Controls.Add((Control) this.textBox132);
      this.tabPage1.Controls.Add((Control) this.groupBox22);
      this.tabPage1.Controls.Add((Control) this.groupBox21);
      this.tabPage1.Controls.Add((Control) this.groupBox8);
      this.tabPage1.Controls.Add((Control) this.groupBox11);
      this.tabPage1.Controls.Add((Control) this.groupBox10);
      this.tabPage1.Controls.Add((Control) this.groupBox9);
      this.tabPage1.Controls.Add((Control) this.groupBox6);
      this.tabPage1.Controls.Add((Control) this.groupBox4);
      this.tabPage1.Controls.Add((Control) this.groupBox2);
      this.tabPage1.Controls.Add((Control) this.groupBox1);
      this.tabPage1.Location = new Point(4, 22);
      this.tabPage1.Name = "tabPage1";
      this.tabPage1.Padding = new Padding(3);
      this.tabPage1.Size = new Size(1041, 598);
      this.tabPage1.TabIndex = 0;
      this.tabPage1.Text = "Basic";
      this.tabControl2.Controls.Add((Control) this.tabPage5);
      this.tabControl2.Location = new Point(2, 333);
      this.tabControl2.Name = "tabControl2";
      this.tabControl2.SelectedIndex = 0;
      this.tabControl2.Size = new Size(1035, 261);
      this.tabControl2.TabIndex = 0;
      this.tabPage5.BackColor = SystemColors.Control;
      this.tabPage5.Controls.Add((Control) this.groupBox26);
      this.tabPage5.Controls.Add((Control) this.groupBox30);
      this.tabPage5.Controls.Add((Control) this.groupBox25);
      this.tabPage5.Controls.Add((Control) this.groupBox27);
      this.tabPage5.Controls.Add((Control) this.groupBox23);
      this.tabPage5.Controls.Add((Control) this.groupBox7);
      this.tabPage5.Location = new Point(4, 22);
      this.tabPage5.Name = "tabPage5";
      this.tabPage5.Padding = new Padding(3);
      this.tabPage5.Size = new Size(1027, 235);
      this.tabPage5.TabIndex = 0;
      this.tabPage5.Text = "Skill Levels";
      this.groupBox26.Controls.Add((Control) this.label115);
      this.groupBox26.Controls.Add((Control) this.textBox114);
      this.groupBox26.Controls.Add((Control) this.label114);
      this.groupBox26.Controls.Add((Control) this.textBox113);
      this.groupBox26.Controls.Add((Control) this.label113);
      this.groupBox26.Controls.Add((Control) this.textBox112);
      this.groupBox26.Controls.Add((Control) this.label112);
      this.groupBox26.Controls.Add((Control) this.textBox111);
      this.groupBox26.Controls.Add((Control) this.label111);
      this.groupBox26.Controls.Add((Control) this.textBox110);
      this.groupBox26.Controls.Add((Control) this.label110);
      this.groupBox26.Controls.Add((Control) this.textBox109);
      this.groupBox26.Location = new Point(834, 8);
      this.groupBox26.Name = "groupBox26";
      this.groupBox26.Size = new Size(187, 93);
      this.groupBox26.TabIndex = 15;
      this.groupBox26.TabStop = false;
      this.groupBox26.Text = "App Magic Index";
      this.label115.AutoSize = true;
      this.label115.Location = new Point(98, 68);
      this.label115.Name = "label115";
      this.label115.Size = new Size(36, 13);
      this.label115.TabIndex = 11;
      this.label115.Text = "Level:";
      this.textBox114.BorderStyle = BorderStyle.FixedSingle;
      this.textBox114.Location = new Point(140, 64);
      this.textBox114.Name = "textBox114";
      this.textBox114.Size = new Size(40, 20);
      this.textBox114.TabIndex = 10;
      this.label114.AutoSize = true;
      this.label114.Location = new Point(8, 68);
      this.label114.Name = "label114";
      this.label114.Size = new Size(36, 13);
      this.label114.TabIndex = 9;
      this.label114.Text = "Index:";
      this.textBox113.BorderStyle = BorderStyle.FixedSingle;
      this.textBox113.Location = new Point(48, 64);
      this.textBox113.Name = "textBox113";
      this.textBox113.Size = new Size(38, 20);
      this.textBox113.TabIndex = 8;
      this.label113.AutoSize = true;
      this.label113.Location = new Point(98, 42);
      this.label113.Name = "label113";
      this.label113.Size = new Size(36, 13);
      this.label113.TabIndex = 7;
      this.label113.Text = "Level:";
      this.textBox112.BorderStyle = BorderStyle.FixedSingle;
      this.textBox112.Location = new Point(140, 40);
      this.textBox112.Name = "textBox112";
      this.textBox112.Size = new Size(40, 20);
      this.textBox112.TabIndex = 6;
      this.label112.AutoSize = true;
      this.label112.Location = new Point(6, 42);
      this.label112.Name = "label112";
      this.label112.Size = new Size(36, 13);
      this.label112.TabIndex = 5;
      this.label112.Text = "Index:";
      this.textBox111.BorderStyle = BorderStyle.FixedSingle;
      this.textBox111.Location = new Point(48, 40);
      this.textBox111.Name = "textBox111";
      this.textBox111.Size = new Size(38, 20);
      this.textBox111.TabIndex = 4;
      this.label111.AutoSize = true;
      this.label111.Location = new Point(98, 16);
      this.label111.Name = "label111";
      this.label111.Size = new Size(36, 13);
      this.label111.TabIndex = 3;
      this.label111.Text = "Level:";
      this.textBox110.BorderStyle = BorderStyle.FixedSingle;
      this.textBox110.Location = new Point(140, 14);
      this.textBox110.Name = "textBox110";
      this.textBox110.Size = new Size(40, 20);
      this.textBox110.TabIndex = 2;
      this.label110.AutoSize = true;
      this.label110.Location = new Point(6, 16);
      this.label110.Name = "label110";
      this.label110.Size = new Size(36, 13);
      this.label110.TabIndex = 1;
      this.label110.Text = "Index:";
      this.textBox109.BorderStyle = BorderStyle.FixedSingle;
      this.textBox109.Location = new Point(48, 14);
      this.textBox109.Name = "textBox109";
      this.textBox109.Size = new Size(38, 20);
      this.textBox109.TabIndex = 0;
      this.groupBox30.Controls.Add((Control) this.textBox128);
      this.groupBox30.Controls.Add((Control) this.textBox85);
      this.groupBox30.Controls.Add((Control) this.label129);
      this.groupBox30.Controls.Add((Control) this.label86);
      this.groupBox30.Controls.Add((Control) this.textBox89);
      this.groupBox30.Controls.Add((Control) this.label90);
      this.groupBox30.Controls.Add((Control) this.textBox90);
      this.groupBox30.Controls.Add((Control) this.label91);
      this.groupBox30.Location = new Point(134, 6);
      this.groupBox30.Name = "groupBox30";
      this.groupBox30.Size = new Size(229, 83);
      this.groupBox30.TabIndex = 60;
      this.groupBox30.TabStop = false;
      this.groupBox30.Text = "Basic";
      this.textBox128.BorderStyle = BorderStyle.FixedSingle;
      this.textBox128.Location = new Point(172, 21);
      this.textBox128.Name = "textBox128";
      this.textBox128.Size = new Size(51, 20);
      this.textBox128.TabIndex = 57;
      this.textBox85.BorderStyle = BorderStyle.FixedSingle;
      this.textBox85.Location = new Point(71, 21);
      this.textBox85.Name = "textBox85";
      this.textBox85.Size = new Size(28, 20);
      this.textBox85.TabIndex = 3;
      this.label129.AutoSize = true;
      this.label129.Location = new Point(125, 23);
      this.label129.Name = "label129";
      this.label129.Size = new Size(41, 13);
      this.label129.TabIndex = 56;
      this.label129.Text = "Target:";
      this.label86.AutoSize = true;
      this.label86.Location = new Point(6, 23);
      this.label86.Name = "label86";
      this.label86.Size = new Size(36, 13);
      this.label86.TabIndex = 4;
      this.label86.Text = "Level:";
      this.textBox89.BorderStyle = BorderStyle.FixedSingle;
      this.textBox89.Location = new Point(172, 48);
      this.textBox89.Name = "textBox89";
      this.textBox89.Size = new Size(51, 20);
      this.textBox89.TabIndex = 11;
      this.label90.AutoSize = true;
      this.label90.Location = new Point(125, 50);
      this.label90.Name = "label90";
      this.label90.Size = new Size(33, 13);
      this.label90.TabIndex = 12;
      this.label90.Text = "Dure:";
      this.textBox90.BorderStyle = BorderStyle.FixedSingle;
      this.textBox90.Location = new Point(54, 48);
      this.textBox90.Name = "textBox90";
      this.textBox90.Size = new Size(62, 20);
      this.textBox90.TabIndex = 14;
      this.label91.AutoSize = true;
      this.label91.Location = new Point(6, 50);
      this.label91.Name = "label91";
      this.label91.Size = new Size(40, 13);
      this.label91.TabIndex = 13;
      this.label91.Text = "Power:";
      this.groupBox25.Controls.Add((Control) this.label128);
      this.groupBox25.Controls.Add((Control) this.textBox127);
      this.groupBox25.Controls.Add((Control) this.label127);
      this.groupBox25.Controls.Add((Control) this.textBox126);
      this.groupBox25.Controls.Add((Control) this.label126);
      this.groupBox25.Controls.Add((Control) this.textBox125);
      this.groupBox25.Controls.Add((Control) this.groupBox28);
      this.groupBox25.Controls.Add((Control) this.label109);
      this.groupBox25.Controls.Add((Control) this.textBox108);
      this.groupBox25.Controls.Add((Control) this.label108);
      this.groupBox25.Controls.Add((Control) this.textBox106);
      this.groupBox25.Controls.Add((Control) this.label107);
      this.groupBox25.Controls.Add((Control) this.textBox104);
      this.groupBox25.Controls.Add((Control) this.textBox107);
      this.groupBox25.Controls.Add((Control) this.label106);
      this.groupBox25.Controls.Add((Control) this.textBox105);
      this.groupBox25.Controls.Add((Control) this.label105);
      this.groupBox25.Controls.Add((Control) this.textBox103);
      this.groupBox25.Controls.Add((Control) this.label104);
      this.groupBox25.Controls.Add((Control) this.textBox102);
      this.groupBox25.Controls.Add((Control) this.label103);
      this.groupBox25.Controls.Add((Control) this.label102);
      this.groupBox25.Controls.Add((Control) this.textBox101);
      this.groupBox25.Controls.Add((Control) this.textBox100);
      this.groupBox25.Controls.Add((Control) this.label101);
      this.groupBox25.Controls.Add((Control) this.label100);
      this.groupBox25.Controls.Add((Control) this.textBox99);
      this.groupBox25.Controls.Add((Control) this.textBox98);
      this.groupBox25.Controls.Add((Control) this.label99);
      this.groupBox25.Controls.Add((Control) this.label98);
      this.groupBox25.Controls.Add((Control) this.textBox97);
      this.groupBox25.Controls.Add((Control) this.label97);
      this.groupBox25.Controls.Add((Control) this.textBox96);
      this.groupBox25.Controls.Add((Control) this.label96);
      this.groupBox25.Controls.Add((Control) this.textBox95);
      this.groupBox25.Controls.Add((Control) this.pictureBox6);
      this.groupBox25.Controls.Add((Control) this.pictureBox7);
      this.groupBox25.Controls.Add((Control) this.pictureBox8);
      this.groupBox25.Controls.Add((Control) this.pictureBox9);
      this.groupBox25.Controls.Add((Control) this.pictureBox10);
      this.groupBox25.Controls.Add((Control) this.pictureBox11);
      this.groupBox25.Location = new Point(134, 116);
      this.groupBox25.Name = "groupBox25";
      this.groupBox25.Size = new Size(880, 113);
      this.groupBox25.TabIndex = 14;
      this.groupBox25.TabStop = false;
      this.groupBox25.Text = "Needed to Learn Skill";
      this.label128.AutoSize = true;
      this.label128.Location = new Point(10, 84);
      this.label128.Name = "label128";
      this.label128.Size = new Size(57, 13);
      this.label128.TabIndex = 55;
      this.label128.Text = "UseCount:";
      this.textBox127.BorderStyle = BorderStyle.FixedSingle;
      this.textBox127.Location = new Point(77, 82);
      this.textBox127.Name = "textBox127";
      this.textBox127.Size = new Size(100, 20);
      this.textBox127.TabIndex = 54;
      this.label127.AutoSize = true;
      this.label127.Location = new Point(97, 60);
      this.label127.Name = "label127";
      this.label127.Size = new Size(25, 13);
      this.label127.TabIndex = 53;
      this.label127.Text = "GP:";
      this.textBox126.BorderStyle = BorderStyle.FixedSingle;
      this.textBox126.Location = new Point(128, 58);
      this.textBox126.Name = "textBox126";
      this.textBox126.Size = new Size(49, 20);
      this.textBox126.TabIndex = 52;
      this.label126.AutoSize = true;
      this.label126.Location = new Point(10, 62);
      this.label126.Name = "label126";
      this.label126.Size = new Size(33, 13);
      this.label126.TabIndex = 51;
      this.label126.Text = "Hate:";
      this.textBox125.BorderStyle = BorderStyle.FixedSingle;
      this.textBox125.Location = new Point(52, 56);
      this.textBox125.Name = "textBox125";
      this.textBox125.Size = new Size(29, 20);
      this.textBox125.TabIndex = 50;
      this.groupBox28.Controls.Add((Control) this.textBox124);
      this.groupBox28.Controls.Add((Control) this.textBox123);
      this.groupBox28.Controls.Add((Control) this.textBox122);
      this.groupBox28.Controls.Add((Control) this.textBox121);
      this.groupBox28.Controls.Add((Control) this.label125);
      this.groupBox28.Controls.Add((Control) this.label124);
      this.groupBox28.Controls.Add((Control) this.label123);
      this.groupBox28.Controls.Add((Control) this.label122);
      this.groupBox28.Location = new Point(700, 7);
      this.groupBox28.Name = "groupBox28";
      this.groupBox28.Size = new Size(154, 97);
      this.groupBox28.TabIndex = 49;
      this.groupBox28.TabStop = false;
      this.groupBox28.Text = "Stats Needed";
      this.textBox124.BorderStyle = BorderStyle.FixedSingle;
      this.textBox124.Location = new Point(119, 52);
      this.textBox124.Name = "textBox124";
      this.textBox124.Size = new Size(28, 20);
      this.textBox124.TabIndex = 7;
      this.textBox123.BorderStyle = BorderStyle.FixedSingle;
      this.textBox123.Location = new Point(42, 52);
      this.textBox123.Name = "textBox123";
      this.textBox123.Size = new Size(28, 20);
      this.textBox123.TabIndex = 6;
      this.textBox122.BorderStyle = BorderStyle.FixedSingle;
      this.textBox122.Location = new Point(120, 26);
      this.textBox122.Name = "textBox122";
      this.textBox122.Size = new Size(28, 20);
      this.textBox122.TabIndex = 5;
      this.textBox121.BorderStyle = BorderStyle.FixedSingle;
      this.textBox121.Location = new Point(42, 27);
      this.textBox121.Name = "textBox121";
      this.textBox121.Size = new Size(28, 20);
      this.textBox121.TabIndex = 4;
      this.label125.AutoSize = true;
      this.label125.Location = new Point(85, 56);
      this.label125.Name = "label125";
      this.label125.Size = new Size(32, 13);
      this.label125.TabIndex = 3;
      this.label125.Text = "Cont:";
      this.label124.AutoSize = true;
      this.label124.Location = new Point(8, 56);
      this.label124.Name = "label124";
      this.label124.Size = new Size(22, 13);
      this.label124.TabIndex = 2;
      this.label124.Text = "Int:";
      this.label123.AutoSize = true;
      this.label123.Location = new Point(85, 30);
      this.label123.Name = "label123";
      this.label123.Size = new Size(29, 13);
      this.label123.TabIndex = 1;
      this.label123.Text = "Dex:";
      this.label122.AutoSize = true;
      this.label122.Location = new Point(7, 30);
      this.label122.Name = "label122";
      this.label122.Size = new Size(23, 13);
      this.label122.TabIndex = 0;
      this.label122.Text = "Str:";
      this.label109.AutoSize = true;
      this.label109.Location = new Point(474, 86);
      this.label109.Name = "label109";
      this.label109.Size = new Size(26, 13);
      this.label109.TabIndex = 48;
      this.label109.Text = "Cnt:";
      this.textBox108.BorderStyle = BorderStyle.FixedSingle;
      this.textBox108.Location = new Point(504, 84);
      this.textBox108.Name = "textBox108";
      this.textBox108.Size = new Size(157, 20);
      this.textBox108.TabIndex = 47;
      this.label108.AutoSize = true;
      this.label108.Location = new Point(477, 60);
      this.label108.Name = "label108";
      this.label108.Size = new Size(26, 13);
      this.label108.TabIndex = 46;
      this.label108.Text = "Cnt:";
      this.textBox106.BorderStyle = BorderStyle.FixedSingle;
      this.textBox106.Location = new Point(504, 58);
      this.textBox106.Name = "textBox106";
      this.textBox106.Size = new Size(157, 20);
      this.textBox106.TabIndex = 45;
      this.label107.AutoSize = true;
      this.label107.Location = new Point(477, 35);
      this.label107.Name = "label107";
      this.label107.Size = new Size(26, 13);
      this.label107.TabIndex = 44;
      this.label107.Text = "Cnt:";
      this.textBox104.BorderStyle = BorderStyle.FixedSingle;
      this.textBox104.Location = new Point(504, 32);
      this.textBox104.Name = "textBox104";
      this.textBox104.Size = new Size(157, 20);
      this.textBox104.TabIndex = 43;
      this.textBox107.BorderStyle = BorderStyle.FixedSingle;
      this.textBox107.Location = new Point(428, 84);
      this.textBox107.Name = "textBox107";
      this.textBox107.Size = new Size(43, 20);
      this.textBox107.TabIndex = 41;
      this.label106.AutoSize = true;
      this.label106.Location = new Point(393, 86);
      this.label106.Name = "label106";
      this.label106.Size = new Size(30, 13);
      this.label106.TabIndex = 40;
      this.label106.Text = "Item:";
      this.textBox105.BorderStyle = BorderStyle.FixedSingle;
      this.textBox105.Location = new Point(428, 58);
      this.textBox105.Name = "textBox105";
      this.textBox105.Size = new Size(43, 20);
      this.textBox105.TabIndex = 38;
      this.label105.AutoSize = true;
      this.label105.Location = new Point(393, 60);
      this.label105.Name = "label105";
      this.label105.Size = new Size(30, 13);
      this.label105.TabIndex = 37;
      this.label105.Text = "Item:";
      this.textBox103.BorderStyle = BorderStyle.FixedSingle;
      this.textBox103.Location = new Point(428, 32);
      this.textBox103.Name = "textBox103";
      this.textBox103.Size = new Size(43, 20);
      this.textBox103.TabIndex = 35;
      this.label104.AutoSize = true;
      this.label104.Location = new Point(393, 34);
      this.label104.Name = "label104";
      this.label104.Size = new Size(30, 13);
      this.label104.TabIndex = 34;
      this.label104.Text = "Item:";
      this.textBox102.BorderStyle = BorderStyle.FixedSingle;
      this.textBox102.Location = new Point(314, 80);
      this.textBox102.Name = "textBox102";
      this.textBox102.Size = new Size(26, 20);
      this.textBox102.TabIndex = 33;
      this.label103.AutoSize = true;
      this.label103.Location = new Point(280, 81);
      this.label103.Name = "label103";
      this.label103.Size = new Size(28, 13);
      this.label103.TabIndex = 32;
      this.label103.Text = "LvL:";
      this.label102.AutoSize = true;
      this.label102.Location = new Point(189, 82);
      this.label102.Name = "label102";
      this.label102.Size = new Size(38, 13);
      this.label102.TabIndex = 30;
      this.label102.Text = "Skill 3:";
      this.textBox101.BorderStyle = BorderStyle.FixedSingle;
      this.textBox101.Location = new Point(233, 79);
      this.textBox101.Name = "textBox101";
      this.textBox101.Size = new Size(32, 20);
      this.textBox101.TabIndex = 29;
      this.textBox100.BorderStyle = BorderStyle.FixedSingle;
      this.textBox100.Location = new Point(314, 53);
      this.textBox100.Name = "textBox100";
      this.textBox100.Size = new Size(26, 20);
      this.textBox100.TabIndex = 28;
      this.label101.AutoSize = true;
      this.label101.Location = new Point(280, 55);
      this.label101.Name = "label101";
      this.label101.Size = new Size(28, 13);
      this.label101.TabIndex = 27;
      this.label101.Text = "LvL:";
      this.label100.AutoSize = true;
      this.label100.Location = new Point(189, 55);
      this.label100.Name = "label100";
      this.label100.Size = new Size(38, 13);
      this.label100.TabIndex = 25;
      this.label100.Text = "Skill 2:";
      this.textBox99.BorderStyle = BorderStyle.FixedSingle;
      this.textBox99.Location = new Point(232, 53);
      this.textBox99.Name = "textBox99";
      this.textBox99.Size = new Size(33, 20);
      this.textBox99.TabIndex = 24;
      this.textBox98.BorderStyle = BorderStyle.FixedSingle;
      this.textBox98.Location = new Point(314, 27);
      this.textBox98.Name = "textBox98";
      this.textBox98.Size = new Size(26, 20);
      this.textBox98.TabIndex = 23;
      this.label99.AutoSize = true;
      this.label99.Location = new Point(280, 31);
      this.label99.Name = "label99";
      this.label99.Size = new Size(31, 13);
      this.label99.TabIndex = 22;
      this.label99.Text = "LvL.:";
      this.label98.AutoSize = true;
      this.label98.Location = new Point(189, 31);
      this.label98.Name = "label98";
      this.label98.Size = new Size(38, 13);
      this.label98.TabIndex = 17;
      this.label98.Text = "Skill 1:";
      this.textBox97.BorderStyle = BorderStyle.FixedSingle;
      this.textBox97.Location = new Point(233, 27);
      this.textBox97.Name = "textBox97";
      this.textBox97.Size = new Size(32, 20);
      this.textBox97.TabIndex = 16;
      this.label97.AutoSize = true;
      this.label97.Location = new Point(98, 34);
      this.label97.Name = "label97";
      this.label97.Size = new Size(24, 13);
      this.label97.TabIndex = 15;
      this.label97.Text = "SP:";
      this.textBox96.BorderStyle = BorderStyle.FixedSingle;
      this.textBox96.Location = new Point(128, 32);
      this.textBox96.Name = "textBox96";
      this.textBox96.Size = new Size(49, 20);
      this.textBox96.TabIndex = 14;
      this.label96.AutoSize = true;
      this.label96.Location = new Point(10, 34);
      this.label96.Name = "label96";
      this.label96.Size = new Size(36, 13);
      this.label96.TabIndex = 0;
      this.label96.Text = "Level:";
      this.textBox95.BorderStyle = BorderStyle.FixedSingle;
      this.textBox95.Location = new Point(52, 30);
      this.textBox95.Name = "textBox95";
      this.textBox95.Size = new Size(29, 20);
      this.textBox95.TabIndex = 13;
      this.pictureBox6.BackColor = SystemColors.Control;
      this.pictureBox6.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox6.Cursor = Cursors.Hand;
      this.pictureBox6.Location = new Point(346, 27);
      this.pictureBox6.Name = "pictureBox6";
      this.pictureBox6.Size = new Size(20, 20);
      this.pictureBox6.SizeMode = PictureBoxSizeMode.Zoom;
      this.pictureBox6.TabIndex = 21;
      this.pictureBox6.TabStop = false;
      this.toolTip1.SetToolTip((Control) this.pictureBox6, "Select Skill");
      this.pictureBox6.Click += new EventHandler(this.pictureBox6_Click);
      this.pictureBox7.BackColor = SystemColors.Control;
      this.pictureBox7.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox7.Cursor = Cursors.Hand;
      this.pictureBox7.Location = new Point(346, 53);
      this.pictureBox7.Name = "pictureBox7";
      this.pictureBox7.Size = new Size(20, 20);
      this.pictureBox7.SizeMode = PictureBoxSizeMode.Zoom;
      this.pictureBox7.TabIndex = 26;
      this.pictureBox7.TabStop = false;
      this.toolTip1.SetToolTip((Control) this.pictureBox7, "Select Skill");
      this.pictureBox8.BackColor = SystemColors.Control;
      this.pictureBox8.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox8.Cursor = Cursors.Hand;
      this.pictureBox8.Location = new Point(346, 80);
      this.pictureBox8.Name = "pictureBox8";
      this.pictureBox8.Size = new Size(20, 20);
      this.pictureBox8.SizeMode = PictureBoxSizeMode.Zoom;
      this.pictureBox8.TabIndex = 31;
      this.pictureBox8.TabStop = false;
      this.toolTip1.SetToolTip((Control) this.pictureBox8, "Select Skill");
      this.pictureBox9.BackColor = SystemColors.Control;
      this.pictureBox9.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox9.Cursor = Cursors.Hand;
      this.pictureBox9.Location = new Point(666, 32);
      this.pictureBox9.Name = "pictureBox9";
      this.pictureBox9.Size = new Size(20, 20);
      this.pictureBox9.SizeMode = PictureBoxSizeMode.Zoom;
      this.pictureBox9.TabIndex = 36;
      this.pictureBox9.TabStop = false;
      this.toolTip1.SetToolTip((Control) this.pictureBox9, "Select Item");
      this.pictureBox9.Click += new EventHandler(this.pictureBox9_Click);
      this.pictureBox10.BackColor = SystemColors.Control;
      this.pictureBox10.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox10.Cursor = Cursors.Hand;
      this.pictureBox10.Location = new Point(666, 58);
      this.pictureBox10.Name = "pictureBox10";
      this.pictureBox10.Size = new Size(20, 20);
      this.pictureBox10.SizeMode = PictureBoxSizeMode.Zoom;
      this.pictureBox10.TabIndex = 39;
      this.pictureBox10.TabStop = false;
      this.toolTip1.SetToolTip((Control) this.pictureBox10, "Select Item");
      this.pictureBox10.Click += new EventHandler(this.pictureBox10_Click);
      this.pictureBox11.BackColor = SystemColors.Control;
      this.pictureBox11.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox11.Cursor = Cursors.Hand;
      this.pictureBox11.Location = new Point(666, 84);
      this.pictureBox11.Name = "pictureBox11";
      this.pictureBox11.Size = new Size(20, 20);
      this.pictureBox11.SizeMode = PictureBoxSizeMode.Zoom;
      this.pictureBox11.TabIndex = 42;
      this.pictureBox11.TabStop = false;
      this.toolTip1.SetToolTip((Control) this.pictureBox11, "Select Item");
      this.pictureBox11.Click += new EventHandler(this.pictureBox11_Click);
      this.groupBox27.Controls.Add((Control) this.textBox120);
      this.groupBox27.Controls.Add((Control) this.label121);
      this.groupBox27.Controls.Add((Control) this.textBox119);
      this.groupBox27.Controls.Add((Control) this.label120);
      this.groupBox27.Controls.Add((Control) this.textBox118);
      this.groupBox27.Controls.Add((Control) this.label119);
      this.groupBox27.Controls.Add((Control) this.textBox117);
      this.groupBox27.Controls.Add((Control) this.label118);
      this.groupBox27.Controls.Add((Control) this.textBox116);
      this.groupBox27.Controls.Add((Control) this.label117);
      this.groupBox27.Controls.Add((Control) this.textBox115);
      this.groupBox27.Controls.Add((Control) this.label116);
      this.groupBox27.Location = new Point(623, 6);
      this.groupBox27.Name = "groupBox27";
      this.groupBox27.Size = new Size(205, 95);
      this.groupBox27.TabIndex = 16;
      this.groupBox27.TabStop = false;
      this.groupBox27.Text = "Magic Index";
      this.textBox120.BorderStyle = BorderStyle.FixedSingle;
      this.textBox120.Location = new Point(147, 68);
      this.textBox120.Name = "textBox120";
      this.textBox120.Size = new Size(21, 20);
      this.textBox120.TabIndex = 11;
      this.label121.AutoSize = true;
      this.label121.Location = new Point(99, 68);
      this.label121.Name = "label121";
      this.label121.Size = new Size(36, 13);
      this.label121.TabIndex = 10;
      this.label121.Text = "Level:";
      this.textBox119.BorderStyle = BorderStyle.FixedSingle;
      this.textBox119.Location = new Point(51, 66);
      this.textBox119.Name = "textBox119";
      this.textBox119.Size = new Size(36, 20);
      this.textBox119.TabIndex = 9;
      this.label120.AutoSize = true;
      this.label120.Location = new Point(9, 70);
      this.label120.Name = "label120";
      this.label120.Size = new Size(36, 13);
      this.label120.TabIndex = 8;
      this.label120.Text = "Index:";
      this.textBox118.BorderStyle = BorderStyle.FixedSingle;
      this.textBox118.Location = new Point(147, 42);
      this.textBox118.Name = "textBox118";
      this.textBox118.Size = new Size(21, 20);
      this.textBox118.TabIndex = 7;
      this.label119.AutoSize = true;
      this.label119.Location = new Point(99, 42);
      this.label119.Name = "label119";
      this.label119.Size = new Size(36, 13);
      this.label119.TabIndex = 6;
      this.label119.Text = "Level:";
      this.textBox117.BorderStyle = BorderStyle.FixedSingle;
      this.textBox117.Location = new Point(51, 42);
      this.textBox117.Name = "textBox117";
      this.textBox117.Size = new Size(36, 20);
      this.textBox117.TabIndex = 5;
      this.label118.AutoSize = true;
      this.label118.Location = new Point(9, 45);
      this.label118.Name = "label118";
      this.label118.Size = new Size(36, 13);
      this.label118.TabIndex = 4;
      this.label118.Text = "Index:";
      this.textBox116.BorderStyle = BorderStyle.FixedSingle;
      this.textBox116.Location = new Point(147, 16);
      this.textBox116.Name = "textBox116";
      this.textBox116.Size = new Size(21, 20);
      this.textBox116.TabIndex = 3;
      this.label117.AutoSize = true;
      this.label117.Location = new Point(99, 18);
      this.label117.Name = "label117";
      this.label117.Size = new Size(36, 13);
      this.label117.TabIndex = 2;
      this.label117.Text = "Level:";
      this.textBox115.BorderStyle = BorderStyle.FixedSingle;
      this.textBox115.Location = new Point(51, 16);
      this.textBox115.Name = "textBox115";
      this.textBox115.Size = new Size(36, 20);
      this.textBox115.TabIndex = 1;
      this.label116.AutoSize = true;
      this.label116.Location = new Point(9, 18);
      this.label116.Name = "label116";
      this.label116.Size = new Size(36, 13);
      this.label116.TabIndex = 0;
      this.label116.Text = "Index:";
      this.groupBox23.Controls.Add((Control) this.label95);
      this.groupBox23.Controls.Add((Control) this.textBox94);
      this.groupBox23.Controls.Add((Control) this.pictureBox5);
      this.groupBox23.Controls.Add((Control) this.label94);
      this.groupBox23.Controls.Add((Control) this.textBox93);
      this.groupBox23.Controls.Add((Control) this.label93);
      this.groupBox23.Controls.Add((Control) this.textBox92);
      this.groupBox23.Controls.Add((Control) this.pictureBox4);
      this.groupBox23.Controls.Add((Control) this.label92);
      this.groupBox23.Controls.Add((Control) this.textBox91);
      this.groupBox23.Controls.Add((Control) this.label89);
      this.groupBox23.Controls.Add((Control) this.textBox88);
      this.groupBox23.Controls.Add((Control) this.textBox87);
      this.groupBox23.Controls.Add((Control) this.label88);
      this.groupBox23.Controls.Add((Control) this.textBox86);
      this.groupBox23.Controls.Add((Control) this.label87);
      this.groupBox23.Location = new Point(371, 6);
      this.groupBox23.Name = "groupBox23";
      this.groupBox23.Size = new Size(246, 113);
      this.groupBox23.TabIndex = 9;
      this.groupBox23.TabStop = false;
      this.groupBox23.Text = "Needed to Cast Skill";
      this.label95.AutoSize = true;
      this.label95.Location = new Point(160, 86);
      this.label95.Name = "label95";
      this.label95.Size = new Size(26, 13);
      this.label95.TabIndex = 20;
      this.label95.Text = "Cnt:";
      this.textBox94.BorderStyle = BorderStyle.FixedSingle;
      this.textBox94.Location = new Point(192, 84);
      this.textBox94.Name = "textBox94";
      this.textBox94.Size = new Size(43, 20);
      this.textBox94.TabIndex = 19;
      this.pictureBox5.BackColor = SystemColors.Control;
      this.pictureBox5.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox5.Cursor = Cursors.Hand;
      this.pictureBox5.Location = new Point(122, 13);
      this.pictureBox5.Name = "pictureBox5";
      this.pictureBox5.Size = new Size(32, 32);
      this.pictureBox5.TabIndex = 18;
      this.pictureBox5.TabStop = false;
      this.toolTip1.SetToolTip((Control) this.pictureBox5, "Select Item");
      this.pictureBox5.Click += new EventHandler(this.pictureBox5_Click);
      this.label94.AutoSize = true;
      this.label94.Location = new Point(160, 16);
      this.label94.Name = "label94";
      this.label94.Size = new Size(30, 13);
      this.label94.TabIndex = 17;
      this.label94.Text = "Item:";
      this.textBox93.BorderStyle = BorderStyle.FixedSingle;
      this.textBox93.Location = new Point(192, 13);
      this.textBox93.Name = "textBox93";
      this.textBox93.Size = new Size(43, 20);
      this.textBox93.TabIndex = 16;
      this.label93.AutoSize = true;
      this.label93.Location = new Point(160, 39);
      this.label93.Name = "label93";
      this.label93.Size = new Size(26, 13);
      this.label93.TabIndex = 15;
      this.label93.Text = "Cnt:";
      this.textBox92.BorderStyle = BorderStyle.FixedSingle;
      this.textBox92.Location = new Point(192, 37);
      this.textBox92.Name = "textBox92";
      this.textBox92.Size = new Size(43, 20);
      this.textBox92.TabIndex = 14;
      this.pictureBox4.BackColor = SystemColors.Control;
      this.pictureBox4.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox4.Cursor = Cursors.Hand;
      this.pictureBox4.Location = new Point(122, 63);
      this.pictureBox4.Name = "pictureBox4";
      this.pictureBox4.Size = new Size(32, 32);
      this.pictureBox4.TabIndex = 13;
      this.pictureBox4.TabStop = false;
      this.toolTip1.SetToolTip((Control) this.pictureBox4, "Select Item");
      this.pictureBox4.Click += new EventHandler(this.pictureBox4_Click);
      this.label92.AutoSize = true;
      this.label92.Location = new Point(160, 63);
      this.label92.Name = "label92";
      this.label92.Size = new Size(30, 13);
      this.label92.TabIndex = 12;
      this.label92.Text = "Item:";
      this.textBox91.BorderStyle = BorderStyle.FixedSingle;
      this.textBox91.Location = new Point(192, 61);
      this.textBox91.Name = "textBox91";
      this.textBox91.Size = new Size(43, 20);
      this.textBox91.TabIndex = 11;
      this.label89.AutoSize = true;
      this.label89.Location = new Point(5, 82);
      this.label89.Name = "label89";
      this.label89.Size = new Size(25, 13);
      this.label89.TabIndex = 10;
      this.label89.Text = "GP:";
      this.textBox88.BorderStyle = BorderStyle.FixedSingle;
      this.textBox88.Location = new Point(36, 79);
      this.textBox88.Name = "textBox88";
      this.textBox88.Size = new Size(66, 20);
      this.textBox88.TabIndex = 9;
      this.textBox87.BorderStyle = BorderStyle.FixedSingle;
      this.textBox87.Location = new Point(37, 50);
      this.textBox87.Name = "textBox87";
      this.textBox87.Size = new Size(65, 20);
      this.textBox87.TabIndex = 7;
      this.label88.AutoSize = true;
      this.label88.Location = new Point(5, 52);
      this.label88.Name = "label88";
      this.label88.Size = new Size(26, 13);
      this.label88.TabIndex = 8;
      this.label88.Text = "MP:";
      this.textBox86.BorderStyle = BorderStyle.FixedSingle;
      this.textBox86.Location = new Point(37, 23);
      this.textBox86.Name = "textBox86";
      this.textBox86.Size = new Size(65, 20);
      this.textBox86.TabIndex = 5;
      this.label87.AutoSize = true;
      this.label87.Location = new Point(6, 26);
      this.label87.Name = "label87";
      this.label87.Size = new Size(25, 13);
      this.label87.TabIndex = 6;
      this.label87.Text = "HP:";
      this.groupBox7.Controls.Add((Control) this.button5);
      this.groupBox7.Controls.Add((Control) this.button4);
      this.groupBox7.Controls.Add((Control) this.listBox2);
      this.groupBox7.Location = new Point(6, 5);
      this.groupBox7.Name = "groupBox7";
      this.groupBox7.Size = new Size(122, 224);
      this.groupBox7.TabIndex = 59;
      this.groupBox7.TabStop = false;
      this.groupBox7.Text = "Levels";
      this.button5.FlatStyle = FlatStyle.Flat;
      this.button5.Location = new Point(62, 46);
      this.button5.Name = "button5";
      this.button5.Size = new Size(51, 22);
      this.button5.TabIndex = 2;
      this.button5.Text = "Delete";
      this.button5.UseVisualStyleBackColor = true;
      this.button5.Click += new EventHandler(this.button5_Click_1);
      this.button4.FlatStyle = FlatStyle.Flat;
      this.button4.Location = new Point(62, 19);
      this.button4.Name = "button4";
      this.button4.Size = new Size(52, 22);
      this.button4.TabIndex = 1;
      this.button4.Text = "Add";
      this.button4.UseVisualStyleBackColor = true;
      this.button4.Click += new EventHandler(this.button4_Click_1);
      this.listBox2.FormattingEnabled = true;
      this.listBox2.Location = new Point(6, 19);
      this.listBox2.Name = "listBox2";
      this.listBox2.Size = new Size(50, 199);
      this.listBox2.TabIndex = 0;
      this.listBox2.SelectedIndexChanged += new EventHandler(this.listBox2_SelectedIndexChanged);
      this.textBox136.Location = new Point(949, 307);
      this.textBox136.Name = "textBox136";
      this.textBox136.Size = new Size(30, 20);
      this.textBox136.TabIndex = 24;
      this.textBox136.Visible = false;
      this.textBox132.Location = new Point(931, 348);
      this.textBox132.Name = "textBox132";
      this.textBox132.Size = new Size(30, 20);
      this.textBox132.TabIndex = 22;
      this.textBox132.Visible = false;
      this.groupBox22.Controls.Add((Control) this.pictureBox1);
      this.groupBox22.Controls.Add((Control) this.linkLabel1);
      this.groupBox22.Controls.Add((Control) this.label75);
      this.groupBox22.Controls.Add((Control) this.label74);
      this.groupBox22.Controls.Add((Control) this.textBox57);
      this.groupBox22.Controls.Add((Control) this.textBox56);
      this.groupBox22.Controls.Add((Control) this.label73);
      this.groupBox22.Controls.Add((Control) this.textBox55);
      this.groupBox22.Location = new Point(9, 240);
      this.groupBox22.Name = "groupBox22";
      this.groupBox22.Size = new Size(207, 87);
      this.groupBox22.TabIndex = 57;
      this.groupBox22.TabStop = false;
      this.groupBox22.Text = "Icon";
      this.pictureBox1.BackColor = SystemColors.Control;
      this.pictureBox1.Location = new Point(140, 15);
      this.pictureBox1.Name = "pictureBox1";
      this.pictureBox1.Size = new Size(40, 40);
      this.pictureBox1.SizeMode = PictureBoxSizeMode.Zoom;
      this.pictureBox1.TabIndex = 63;
      this.pictureBox1.TabStop = false;
      this.linkLabel1.AutoSize = true;
      this.linkLabel1.Location = new Point(128, 61);
      this.linkLabel1.Name = "linkLabel1";
      this.linkLabel1.Size = new Size(61, 13);
      this.linkLabel1.TabIndex = 62;
      this.linkLabel1.TabStop = true;
      this.linkLabel1.Text = "Icon Picker";
      this.linkLabel1.LinkClicked += new LinkLabelLinkClickedEventHandler(this.linkLabel1_LinkClicked_1);
      this.label75.AutoSize = true;
      this.label75.Location = new Point(8, 63);
      this.label75.Name = "label75";
      this.label75.Size = new Size(25, 13);
      this.label75.TabIndex = 60;
      this.label75.Text = "Col:";
      this.label74.AutoSize = true;
      this.label74.Location = new Point(8, 39);
      this.label74.Name = "label74";
      this.label74.Size = new Size(32, 13);
      this.label74.TabIndex = 59;
      this.label74.Text = "Row:";
      this.textBox57.BorderStyle = BorderStyle.FixedSingle;
      this.textBox57.Location = new Point(42, 59);
      this.textBox57.Name = "textBox57";
      this.textBox57.Size = new Size(41, 20);
      this.textBox57.TabIndex = 58;
      this.textBox56.BorderStyle = BorderStyle.FixedSingle;
      this.textBox56.Location = new Point(42, 35);
      this.textBox56.Name = "textBox56";
      this.textBox56.Size = new Size(41, 20);
      this.textBox56.TabIndex = 57;
      this.label73.AutoSize = true;
      this.label73.Location = new Point(8, 14);
      this.label73.Name = "label73";
      this.label73.Size = new Size(21, 13);
      this.label73.TabIndex = 56;
      this.label73.Text = "ID:";
      this.textBox55.BorderStyle = BorderStyle.FixedSingle;
      this.textBox55.Location = new Point(42, 10);
      this.textBox55.Name = "textBox55";
      this.textBox55.Size = new Size(41, 20);
      this.textBox55.TabIndex = 55;
      this.groupBox21.Controls.Add((Control) this.textBox52);
      this.groupBox21.Controls.Add((Control) this.label70);
      this.groupBox21.Location = new Point(356, 204);
      this.groupBox21.Name = "groupBox21";
      this.groupBox21.Size = new Size(288, 42);
      this.groupBox21.TabIndex = 49;
      this.groupBox21.TabStop = false;
      this.groupBox21.Text = "Skill Effect";
      this.textBox52.BorderStyle = BorderStyle.FixedSingle;
      this.textBox52.Location = new Point(49, 14);
      this.textBox52.Name = "textBox52";
      this.textBox52.Size = new Size(185, 20);
      this.textBox52.TabIndex = 1;
      this.label70.AutoSize = true;
      this.label70.Location = new Point(6, 16);
      this.label70.Name = "label70";
      this.label70.Size = new Size(38, 13);
      this.label70.TabIndex = 0;
      this.label70.Text = "Effect:";
      this.groupBox8.Controls.Add((Control) this.label31);
      this.groupBox8.Controls.Add((Control) this.textBox32);
      this.groupBox8.Controls.Add((Control) this.label30);
      this.groupBox8.Controls.Add((Control) this.textBox31);
      this.groupBox8.Controls.Add((Control) this.label29);
      this.groupBox8.Controls.Add((Control) this.textBox30);
      this.groupBox8.Controls.Add((Control) this.label28);
      this.groupBox8.Controls.Add((Control) this.textBox29);
      this.groupBox8.Location = new Point(6, 160);
      this.groupBox8.Name = "groupBox8";
      this.groupBox8.Size = new Size(342, 74);
      this.groupBox8.TabIndex = 48;
      this.groupBox8.TabStop = false;
      this.groupBox8.Text = "Timings";
      this.label31.AutoSize = true;
      this.label31.Location = new Point(156, 44);
      this.label31.Name = "label31";
      this.label31.Size = new Size(57, 13);
      this.label31.TabIndex = 54;
      this.label31.Text = "Cool Time:";
      this.textBox32.BorderStyle = BorderStyle.FixedSingle;
      this.textBox32.Location = new Point(219, 40);
      this.textBox32.Name = "textBox32";
      this.textBox32.Size = new Size(52, 20);
      this.textBox32.TabIndex = 53;
      this.label30.AutoSize = true;
      this.label30.Location = new Point(156, 19);
      this.label30.Name = "label30";
      this.label30.Size = new Size(53, 13);
      this.label30.TabIndex = 52;
      this.label30.Text = "Fire Time:";
      this.textBox31.BorderStyle = BorderStyle.FixedSingle;
      this.textBox31.Location = new Point(219, 14);
      this.textBox31.Name = "textBox31";
      this.textBox31.Size = new Size(52, 20);
      this.textBox31.TabIndex = 51;
      this.label29.AutoSize = true;
      this.label29.Location = new Point(8, 44);
      this.label29.Name = "label29";
      this.label29.Size = new Size(55, 13);
      this.label29.TabIndex = 50;
      this.label29.Text = "Skill Time:";
      this.textBox30.BorderStyle = BorderStyle.FixedSingle;
      this.textBox30.Location = new Point(79, 42);
      this.textBox30.Name = "textBox30";
      this.textBox30.Size = new Size(52, 20);
      this.textBox30.TabIndex = 49;
      this.label28.AutoSize = true;
      this.label28.Location = new Point(6, 22);
      this.label28.Name = "label28";
      this.label28.Size = new Size(67, 13);
      this.label28.TabIndex = 48;
      this.label28.Text = "Ready Time:";
      this.textBox29.BorderStyle = BorderStyle.FixedSingle;
      this.textBox29.Location = new Point(79, 17);
      this.textBox29.Name = "textBox29";
      this.textBox29.Size = new Size(52, 20);
      this.textBox29.TabIndex = 47;
      this.groupBox11.Controls.Add((Control) this.textBox22);
      this.groupBox11.Controls.Add((Control) this.textBox23);
      this.groupBox11.Controls.Add((Control) this.textBox24);
      this.groupBox11.Controls.Add((Control) this.label25);
      this.groupBox11.Controls.Add((Control) this.label24);
      this.groupBox11.Controls.Add((Control) this.label23);
      this.groupBox11.Controls.Add((Control) this.label22);
      this.groupBox11.Controls.Add((Control) this.label21);
      this.groupBox11.Controls.Add((Control) this.label20);
      this.groupBox11.Controls.Add((Control) this.textBox21);
      this.groupBox11.Controls.Add((Control) this.textBox19);
      this.groupBox11.Controls.Add((Control) this.textBox20);
      this.groupBox11.Location = new Point(651, 160);
      this.groupBox11.Name = "groupBox11";
      this.groupBox11.Size = new Size(247, 86);
      this.groupBox11.TabIndex = 46;
      this.groupBox11.TabStop = false;
      this.groupBox11.Text = "Magic Level";
      this.textBox22.BorderStyle = BorderStyle.FixedSingle;
      this.textBox22.Location = new Point(201, 14);
      this.textBox22.Name = "textBox22";
      this.textBox22.Size = new Size(35, 20);
      this.textBox22.TabIndex = 54;
      this.textBox23.BorderStyle = BorderStyle.FixedSingle;
      this.textBox23.Location = new Point(201, 60);
      this.textBox23.Name = "textBox23";
      this.textBox23.Size = new Size(35, 20);
      this.textBox23.TabIndex = 52;
      this.textBox24.BorderStyle = BorderStyle.FixedSingle;
      this.textBox24.Location = new Point(201, 37);
      this.textBox24.Name = "textBox24";
      this.textBox24.Size = new Size(35, 20);
      this.textBox24.TabIndex = 53;
      this.label25.AutoSize = true;
      this.label25.Location = new Point(138, 66);
      this.label25.Name = "label25";
      this.label25.Size = new Size(36, 13);
      this.label25.TabIndex = 51;
      this.label25.Text = "Level:";
      this.label24.AutoSize = true;
      this.label24.Location = new Point(137, 39);
      this.label24.Name = "label24";
      this.label24.Size = new Size(36, 13);
      this.label24.TabIndex = 50;
      this.label24.Text = "Level:";
      this.label23.AutoSize = true;
      this.label23.Location = new Point(138, 16);
      this.label23.Name = "label23";
      this.label23.Size = new Size(36, 13);
      this.label23.TabIndex = 49;
      this.label23.Text = "Level:";
      this.label22.AutoSize = true;
      this.label22.Location = new Point(6, 66);
      this.label22.Name = "label22";
      this.label22.Size = new Size(36, 13);
      this.label22.TabIndex = 48;
      this.label22.Text = "Index:";
      this.label21.AutoSize = true;
      this.label21.Location = new Point(6, 39);
      this.label21.Name = "label21";
      this.label21.Size = new Size(36, 13);
      this.label21.TabIndex = 47;
      this.label21.Text = "Index:";
      this.label20.AutoSize = true;
      this.label20.Location = new Point(5, 16);
      this.label20.Name = "label20";
      this.label20.Size = new Size(36, 13);
      this.label20.TabIndex = 46;
      this.label20.Text = "Index:";
      this.textBox21.BorderStyle = BorderStyle.FixedSingle;
      this.textBox21.Location = new Point(48, 63);
      this.textBox21.Name = "textBox21";
      this.textBox21.Size = new Size(35, 20);
      this.textBox21.TabIndex = 45;
      this.textBox19.BorderStyle = BorderStyle.FixedSingle;
      this.textBox19.Location = new Point(48, 14);
      this.textBox19.Name = "textBox19";
      this.textBox19.Size = new Size(35, 20);
      this.textBox19.TabIndex = 43;
      this.textBox20.BorderStyle = BorderStyle.FixedSingle;
      this.textBox20.Location = new Point(48, 37);
      this.textBox20.Name = "textBox20";
      this.textBox20.Size = new Size(35, 20);
      this.textBox20.TabIndex = 44;
      this.groupBox10.Controls.Add((Control) this.label19);
      this.groupBox10.Controls.Add((Control) this.comboBox18);
      this.groupBox10.Controls.Add((Control) this.textBox17);
      this.groupBox10.Controls.Add((Control) this.comboBox17);
      this.groupBox10.Controls.Add((Control) this.label18);
      this.groupBox10.Controls.Add((Control) this.textBox16);
      this.groupBox10.Location = new Point(356, 110);
      this.groupBox10.Name = "groupBox10";
      this.groupBox10.Size = new Size(288, 85);
      this.groupBox10.TabIndex = 41;
      this.groupBox10.TabStop = false;
      this.groupBox10.Text = "Weapon Type";
      this.label19.AutoSize = true;
      this.label19.Location = new Point(5, 57);
      this.label19.Name = "label19";
      this.label19.Size = new Size(43, 13);
      this.label19.TabIndex = 45;
      this.label19.Text = "Type 2:";
      this.comboBox18.FlatStyle = FlatStyle.Flat;
      this.comboBox18.FormattingEnabled = true;
      this.comboBox18.Location = new Point(54, 54);
      this.comboBox18.Name = "comboBox18";
      this.comboBox18.Size = new Size(180, 21);
      this.comboBox18.TabIndex = 44;
      this.comboBox18.SelectedIndexChanged += new EventHandler(this.comboBox18_SelectedIndexChanged);
      this.textBox17.BorderStyle = BorderStyle.FixedSingle;
      this.textBox17.Location = new Point(249, 55);
      this.textBox17.Name = "textBox17";
      this.textBox17.Size = new Size(22, 20);
      this.textBox17.TabIndex = 43;
      this.textBox17.Visible = false;
      this.comboBox17.FlatStyle = FlatStyle.Flat;
      this.comboBox17.FormattingEnabled = true;
      this.comboBox17.Location = new Point(55, 27);
      this.comboBox17.Name = "comboBox17";
      this.comboBox17.Size = new Size(180, 21);
      this.comboBox17.TabIndex = 42;
      this.comboBox17.SelectedIndexChanged += new EventHandler(this.comboBox17_SelectedIndexChanged);
      this.label18.AutoSize = true;
      this.label18.Location = new Point(6, 30);
      this.label18.Name = "label18";
      this.label18.Size = new Size(43, 13);
      this.label18.TabIndex = 41;
      this.label18.Text = "Type 1:";
      this.textBox16.BorderStyle = BorderStyle.FixedSingle;
      this.textBox16.Location = new Point(249, 27);
      this.textBox16.Name = "textBox16";
      this.textBox16.Size = new Size(22, 20);
      this.textBox16.TabIndex = 40;
      this.textBox16.Visible = false;
      this.groupBox9.Controls.Add((Control) this.label26);
      this.groupBox9.Controls.Add((Control) this.label17);
      this.groupBox9.Controls.Add((Control) this.textBox14);
      this.groupBox9.Controls.Add((Control) this.textBox13);
      this.groupBox9.Controls.Add((Control) this.comboBox16);
      this.groupBox9.Location = new Point(402, 245);
      this.groupBox9.Name = "groupBox9";
      this.groupBox9.Size = new Size(348, 50);
      this.groupBox9.TabIndex = 37;
      this.groupBox9.TabStop = false;
      this.groupBox9.Text = "Target";
      this.label26.AutoSize = true;
      this.label26.Location = new Point(245, 27);
      this.label26.Name = "label26";
      this.label26.Size = new Size(46, 13);
      this.label26.TabIndex = 39;
      this.label26.Text = "Amount:";
      this.label17.AutoSize = true;
      this.label17.Location = new Point(6, 26);
      this.label17.Name = "label17";
      this.label17.Size = new Size(68, 13);
      this.label17.TabIndex = 38;
      this.label17.Text = "Target Type:";
      this.textBox14.BorderStyle = BorderStyle.FixedSingle;
      this.textBox14.Location = new Point(297, 22);
      this.textBox14.Name = "textBox14";
      this.textBox14.Size = new Size(34, 20);
      this.textBox14.TabIndex = 37;
      this.textBox13.BorderStyle = BorderStyle.FixedSingle;
      this.textBox13.Location = new Point(218, 22);
      this.textBox13.Name = "textBox13";
      this.textBox13.Size = new Size(17, 20);
      this.textBox13.TabIndex = 35;
      this.textBox13.Visible = false;
      this.comboBox16.FlatStyle = FlatStyle.Flat;
      this.comboBox16.FormattingEnabled = true;
      this.comboBox16.Location = new Point(80, 21);
      this.comboBox16.Name = "comboBox16";
      this.comboBox16.Size = new Size(130, 21);
      this.comboBox16.TabIndex = 36;
      this.comboBox16.SelectedIndexChanged += new EventHandler(this.comboBox16_SelectedIndexChanged);
      this.groupBox6.Controls.Add((Control) this.pictureBox3);
      this.groupBox6.Controls.Add((Control) this.label82);
      this.groupBox6.Controls.Add((Control) this.textBox81);
      this.groupBox6.Controls.Add((Control) this.pictureBox2);
      this.groupBox6.Controls.Add((Control) this.label78);
      this.groupBox6.Controls.Add((Control) this.textBox7);
      this.groupBox6.Location = new Point(222, 242);
      this.groupBox6.Name = "groupBox6";
      this.groupBox6.Size = new Size(174, 85);
      this.groupBox6.TabIndex = 22;
      this.groupBox6.TabStop = false;
      this.groupBox6.Text = "Flags Skill";
      this.pictureBox3.BackgroundImage = (Image) componentResourceManager.GetObject("pictureBox3.BackgroundImage");
      this.pictureBox3.BackgroundImageLayout = ImageLayout.Zoom;
      this.pictureBox3.Cursor = Cursors.Hand;
      this.pictureBox3.InitialImage = (Image) null;
      this.pictureBox3.Location = new Point(139, 53);
      this.pictureBox3.Name = "pictureBox3";
      this.pictureBox3.Size = new Size(23, 28);
      this.pictureBox3.TabIndex = 26;
      this.pictureBox3.TabStop = false;
      this.toolTip1.SetToolTip((Control) this.pictureBox3, "Sorc Flag Builder");
      this.pictureBox3.MouseLeave += new EventHandler(this.pictureBox3_MouseLeave);
      this.pictureBox3.MouseMove += new MouseEventHandler(this.pictureBox3_MouseMove);
      this.label82.AutoSize = true;
      this.label82.Location = new Point(6, 57);
      this.label82.Name = "label82";
      this.label82.Size = new Size(55, 13);
      this.label82.TabIndex = 25;
      this.label82.Text = "Sorc Flag:";
      this.textBox81.BackColor = Color.White;
      this.textBox81.BorderStyle = BorderStyle.FixedSingle;
      this.textBox81.Location = new Point(67, 55);
      this.textBox81.Name = "textBox81";
      this.textBox81.Size = new Size(66, 20);
      this.textBox81.TabIndex = 24;
      this.pictureBox2.BackgroundImage = (Image) componentResourceManager.GetObject("pictureBox2.BackgroundImage");
      this.pictureBox2.BackgroundImageLayout = ImageLayout.Zoom;
      this.pictureBox2.Cursor = Cursors.Hand;
      this.pictureBox2.InitialImage = (Image) null;
      this.pictureBox2.Location = new Point(139, 19);
      this.pictureBox2.Name = "pictureBox2";
      this.pictureBox2.Size = new Size(23, 28);
      this.pictureBox2.TabIndex = 23;
      this.pictureBox2.TabStop = false;
      this.toolTip1.SetToolTip((Control) this.pictureBox2, "Skill Flag Builder");
      this.pictureBox2.Click += new EventHandler(this.pictureBox2_Click);
      this.pictureBox2.MouseLeave += new EventHandler(this.pictureBox2_MouseLeave);
      this.pictureBox2.MouseMove += new MouseEventHandler(this.pictureBox2_MouseMove);
      this.label78.AutoSize = true;
      this.label78.Location = new Point(9, 28);
      this.label78.Name = "label78";
      this.label78.Size = new Size(52, 13);
      this.label78.TabIndex = 22;
      this.label78.Text = "Skill Flag:";
      this.textBox7.BackColor = Color.White;
      this.textBox7.BorderStyle = BorderStyle.FixedSingle;
      this.textBox7.Location = new Point(67, 26);
      this.textBox7.Name = "textBox7";
      this.textBox7.Size = new Size(66, 20);
      this.textBox7.TabIndex = 21;
      this.groupBox4.Controls.Add((Control) this.textBox25);
      this.groupBox4.Controls.Add((Control) this.textBox15);
      this.groupBox4.Controls.Add((Control) this.label16);
      this.groupBox4.Controls.Add((Control) this.label8);
      this.groupBox4.Controls.Add((Control) this.textBox6);
      this.groupBox4.Controls.Add((Control) this.label15);
      this.groupBox4.Controls.Add((Control) this.comboBox15);
      this.groupBox4.Controls.Add((Control) this.textBox9);
      this.groupBox4.Controls.Add((Control) this.label14);
      this.groupBox4.Controls.Add((Control) this.label11);
      this.groupBox4.Controls.Add((Control) this.textBox12);
      this.groupBox4.Controls.Add((Control) this.textBox10);
      this.groupBox4.Controls.Add((Control) this.label13);
      this.groupBox4.Controls.Add((Control) this.label12);
      this.groupBox4.Controls.Add((Control) this.textBox11);
      this.groupBox4.Location = new Point(651, 8);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Size = new Size(343, 145);
      this.groupBox4.TabIndex = 20;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "Other";
      this.textBox25.BorderStyle = BorderStyle.FixedSingle;
      this.textBox25.Location = new Point(294, 53);
      this.textBox25.Name = "textBox25";
      this.textBox25.Size = new Size(34, 20);
      this.textBox25.TabIndex = 47;
      this.textBox15.BorderStyle = BorderStyle.FixedSingle;
      this.textBox15.Location = new Point(294, 105);
      this.textBox15.Name = "textBox15";
      this.textBox15.Size = new Size(34, 20);
      this.textBox15.TabIndex = 30;
      this.label16.AutoSize = true;
      this.label16.Location = new Point(221, 57);
      this.label16.Name = "label16";
      this.label16.Size = new Size(57, 13);
      this.label16.TabIndex = 38;
      this.label16.Text = "App State:";
      this.label8.AutoSize = true;
      this.label8.Location = new Point(7, 24);
      this.label8.Name = "label8";
      this.label8.Size = new Size(34, 13);
      this.label8.TabIndex = 21;
      this.label8.Text = "Type:";
      this.textBox6.BorderStyle = BorderStyle.FixedSingle;
      this.textBox6.Location = new Point(294, 20);
      this.textBox6.Name = "textBox6";
      this.textBox6.Size = new Size(34, 20);
      this.textBox6.TabIndex = 19;
      this.textBox6.Visible = false;
      this.label15.AutoSize = true;
      this.label15.Location = new Point(221, 111);
      this.label15.Name = "label15";
      this.label15.Size = new Size(57, 13);
      this.label15.TabIndex = 36;
      this.label15.Text = "Use State:";
      this.comboBox15.FlatStyle = FlatStyle.Flat;
      this.comboBox15.FormattingEnabled = true;
      this.comboBox15.Location = new Point(50, 19);
      this.comboBox15.Name = "comboBox15";
      this.comboBox15.Size = new Size(235, 21);
      this.comboBox15.TabIndex = 0;
      this.comboBox15.SelectedIndexChanged += new EventHandler(this.comboBox15_SelectedIndexChanged);
      this.textBox9.BorderStyle = BorderStyle.FixedSingle;
      this.textBox9.Location = new Point(294, 79);
      this.textBox9.Name = "textBox9";
      this.textBox9.Size = new Size(34, 20);
      this.textBox9.TabIndex = 27;
      this.label14.AutoSize = true;
      this.label14.Location = new Point(10, 108);
      this.label14.Name = "label14";
      this.label14.Size = new Size(72, 13);
      this.label14.TabIndex = 34;
      this.label14.Text = "Soul Consum:";
      this.label11.AutoSize = true;
      this.label11.Location = new Point(221, 82);
      this.label11.Name = "label11";
      this.label11.Size = new Size(64, 13);
      this.label11.TabIndex = 28;
      this.label11.Text = "App Range:";
      this.textBox12.BackColor = SystemColors.Window;
      this.textBox12.BorderStyle = BorderStyle.FixedSingle;
      this.textBox12.Location = new Point(88, 105);
      this.textBox12.Name = "textBox12";
      this.textBox12.Size = new Size(34, 20);
      this.textBox12.TabIndex = 33;
      this.textBox10.BorderStyle = BorderStyle.FixedSingle;
      this.textBox10.Location = new Point(88, 53);
      this.textBox10.Name = "textBox10";
      this.textBox10.Size = new Size(34, 20);
      this.textBox10.TabIndex = 29;
      this.label13.AutoSize = true;
      this.label13.Location = new Point(11, 83);
      this.label13.Name = "label13";
      this.label13.Size = new Size(71, 13);
      this.label13.TabIndex = 32;
      this.label13.Text = "Fire Range 2:";
      this.label12.AutoSize = true;
      this.label12.Location = new Point(10, 57);
      this.label12.Name = "label12";
      this.label12.Size = new Size(71, 13);
      this.label12.TabIndex = 30;
      this.label12.Text = "Fire Range 1:";
      this.textBox11.BorderStyle = BorderStyle.FixedSingle;
      this.textBox11.Location = new Point(88, 79);
      this.textBox11.Name = "textBox11";
      this.textBox11.Size = new Size(34, 20);
      this.textBox11.TabIndex = 31;
      this.groupBox2.Controls.Add((Control) this.textBox82);
      this.groupBox2.Controls.Add((Control) this.label83);
      this.groupBox2.Controls.Add((Control) this.comboBox1);
      this.groupBox2.Controls.Add((Control) this.label2);
      this.groupBox2.Controls.Add((Control) this.label3);
      this.groupBox2.Controls.Add((Control) this.textBox2);
      this.groupBox2.Controls.Add((Control) this.comboBox14);
      this.groupBox2.Controls.Add((Control) this.textBox3);
      this.groupBox2.Controls.Add((Control) this.comboBox3);
      this.groupBox2.Controls.Add((Control) this.comboBox5);
      this.groupBox2.Controls.Add((Control) this.comboBox10);
      this.groupBox2.Controls.Add((Control) this.comboBox13);
      this.groupBox2.Controls.Add((Control) this.comboBox9);
      this.groupBox2.Controls.Add((Control) this.comboBox11);
      this.groupBox2.Controls.Add((Control) this.comboBox2);
      this.groupBox2.Controls.Add((Control) this.comboBox6);
      this.groupBox2.Controls.Add((Control) this.comboBox7);
      this.groupBox2.Controls.Add((Control) this.comboBox4);
      this.groupBox2.Controls.Add((Control) this.comboBox12);
      this.groupBox2.Controls.Add((Control) this.comboBox8);
      this.groupBox2.Location = new Point(356, 7);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new Size(288, 99);
      this.groupBox2.TabIndex = 11;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "Character and Job";
      this.textBox82.BorderStyle = BorderStyle.FixedSingle;
      this.textBox82.Location = new Point(69, 70);
      this.textBox82.Name = "textBox82";
      this.textBox82.Size = new Size(76, 20);
      this.textBox82.TabIndex = 52;
      this.label83.AutoSize = true;
      this.label83.Location = new Point(16, 74);
      this.label83.Name = "label83";
      this.label83.Size = new Size(47, 13);
      this.label83.TabIndex = 51;
      this.label83.Text = "Pet IDX:";
      this.comboBox1.FlatStyle = FlatStyle.Flat;
      this.comboBox1.FormattingEnabled = true;
      this.comboBox1.Location = new Point(49, 16);
      this.comboBox1.Name = "comboBox1";
      this.comboBox1.Size = new Size(174, 21);
      this.comboBox1.TabIndex = 35;
      this.comboBox1.SelectedIndexChanged += new EventHandler(this.comboBox1_SelectedIndexChanged);
      this.label2.AutoSize = true;
      this.label2.Location = new Point(12, 19);
      this.label2.Name = "label2";
      this.label2.Size = new Size(35, 13);
      this.label2.TabIndex = 8;
      this.label2.Text = "Class:";
      this.label3.AutoSize = true;
      this.label3.Location = new Point(16, 46);
      this.label3.Name = "label3";
      this.label3.Size = new Size(27, 13);
      this.label3.TabIndex = 50;
      this.label3.Text = "Job:";
      this.textBox2.BorderStyle = BorderStyle.FixedSingle;
      this.textBox2.Location = new Point(230, 17);
      this.textBox2.Name = "textBox2";
      this.textBox2.Size = new Size(26, 20);
      this.textBox2.TabIndex = 2;
      this.textBox2.Visible = false;
      this.comboBox14.FlatStyle = FlatStyle.Flat;
      this.comboBox14.FormattingEnabled = true;
      this.comboBox14.Location = new Point(49, 44);
      this.comboBox14.Name = "comboBox14";
      this.comboBox14.Size = new Size(174, 21);
      this.comboBox14.TabIndex = 49;
      this.comboBox14.SelectedIndexChanged += new EventHandler(this.comboBox14_SelectedIndexChanged);
      this.textBox3.BorderStyle = BorderStyle.FixedSingle;
      this.textBox3.Location = new Point(230, 45);
      this.textBox3.Name = "textBox3";
      this.textBox3.Size = new Size(26, 20);
      this.textBox3.TabIndex = 3;
      this.textBox3.Visible = false;
      this.comboBox3.FlatStyle = FlatStyle.Flat;
      this.comboBox3.FormattingEnabled = true;
      this.comboBox3.Location = new Point(49, 44);
      this.comboBox3.Name = "comboBox3";
      this.comboBox3.Size = new Size(174, 21);
      this.comboBox3.TabIndex = 37;
      this.comboBox3.SelectedIndexChanged += new EventHandler(this.comboBox3_SelectedIndexChanged);
      this.comboBox5.FlatStyle = FlatStyle.Flat;
      this.comboBox5.FormattingEnabled = true;
      this.comboBox5.Location = new Point(49, 44);
      this.comboBox5.Name = "comboBox5";
      this.comboBox5.Size = new Size(174, 21);
      this.comboBox5.TabIndex = 38;
      this.comboBox5.SelectedIndexChanged += new EventHandler(this.comboBox5_SelectedIndexChanged);
      this.comboBox10.FlatStyle = FlatStyle.Flat;
      this.comboBox10.FormattingEnabled = true;
      this.comboBox10.Location = new Point(49, 44);
      this.comboBox10.Name = "comboBox10";
      this.comboBox10.Size = new Size(174, 21);
      this.comboBox10.TabIndex = 43;
      this.comboBox10.SelectedIndexChanged += new EventHandler(this.comboBox10_SelectedIndexChanged);
      this.comboBox13.FlatStyle = FlatStyle.Flat;
      this.comboBox13.FormattingEnabled = true;
      this.comboBox13.Location = new Point(49, 44);
      this.comboBox13.Name = "comboBox13";
      this.comboBox13.Size = new Size(174, 21);
      this.comboBox13.TabIndex = 46;
      this.comboBox13.SelectedIndexChanged += new EventHandler(this.comboBox13_SelectedIndexChanged);
      this.comboBox9.FlatStyle = FlatStyle.Flat;
      this.comboBox9.FormattingEnabled = true;
      this.comboBox9.Location = new Point(49, 44);
      this.comboBox9.Name = "comboBox9";
      this.comboBox9.Size = new Size(174, 21);
      this.comboBox9.TabIndex = 42;
      this.comboBox9.SelectedIndexChanged += new EventHandler(this.comboBox9_SelectedIndexChanged);
      this.comboBox11.FlatStyle = FlatStyle.Flat;
      this.comboBox11.FormattingEnabled = true;
      this.comboBox11.Location = new Point(49, 44);
      this.comboBox11.Name = "comboBox11";
      this.comboBox11.Size = new Size(174, 21);
      this.comboBox11.TabIndex = 44;
      this.comboBox11.SelectedIndexChanged += new EventHandler(this.comboBox11_SelectedIndexChanged);
      this.comboBox2.FlatStyle = FlatStyle.Flat;
      this.comboBox2.FormattingEnabled = true;
      this.comboBox2.Location = new Point(49, 44);
      this.comboBox2.Name = "comboBox2";
      this.comboBox2.Size = new Size(174, 21);
      this.comboBox2.TabIndex = 36;
      this.comboBox2.SelectedIndexChanged += new EventHandler(this.comboBox2_SelectedIndexChanged);
      this.comboBox6.FlatStyle = FlatStyle.Flat;
      this.comboBox6.FormattingEnabled = true;
      this.comboBox6.Location = new Point(49, 44);
      this.comboBox6.Name = "comboBox6";
      this.comboBox6.Size = new Size(174, 21);
      this.comboBox6.TabIndex = 39;
      this.comboBox6.SelectedIndexChanged += new EventHandler(this.comboBox6_SelectedIndexChanged);
      this.comboBox7.FlatStyle = FlatStyle.Flat;
      this.comboBox7.FormattingEnabled = true;
      this.comboBox7.Location = new Point(49, 44);
      this.comboBox7.Name = "comboBox7";
      this.comboBox7.Size = new Size(174, 21);
      this.comboBox7.TabIndex = 40;
      this.comboBox7.SelectedIndexChanged += new EventHandler(this.comboBox7_SelectedIndexChanged);
      this.comboBox4.FlatStyle = FlatStyle.Flat;
      this.comboBox4.FormattingEnabled = true;
      this.comboBox4.Location = new Point(49, 44);
      this.comboBox4.Name = "comboBox4";
      this.comboBox4.Size = new Size(174, 21);
      this.comboBox4.TabIndex = 37;
      this.comboBox4.SelectedIndexChanged += new EventHandler(this.comboBox4_SelectedIndexChanged);
      this.comboBox12.FlatStyle = FlatStyle.Flat;
      this.comboBox12.FormattingEnabled = true;
      this.comboBox12.Location = new Point(49, 44);
      this.comboBox12.Name = "comboBox12";
      this.comboBox12.Size = new Size(174, 21);
      this.comboBox12.TabIndex = 45;
      this.comboBox12.SelectedIndexChanged += new EventHandler(this.comboBox12_SelectedIndexChanged);
      this.comboBox8.FlatStyle = FlatStyle.Flat;
      this.comboBox8.FormattingEnabled = true;
      this.comboBox8.Location = new Point(49, 44);
      this.comboBox8.Name = "comboBox8";
      this.comboBox8.Size = new Size(174, 21);
      this.comboBox8.TabIndex = 41;
      this.comboBox8.SelectedIndexChanged += new EventHandler(this.comboBox8_SelectedIndexChanged);
      this.groupBox1.Controls.Add((Control) this.textBox54);
      this.groupBox1.Controls.Add((Control) this.label71);
      this.groupBox1.Controls.Add((Control) this.label6);
      this.groupBox1.Controls.Add((Control) this.textBox5);
      this.groupBox1.Controls.Add((Control) this.label5);
      this.groupBox1.Controls.Add((Control) this.textBox4);
      this.groupBox1.Controls.Add((Control) this.textBox1);
      this.groupBox1.Controls.Add((Control) this.label1);
      this.groupBox1.Location = new Point(6, 6);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(342, 147);
      this.groupBox1.TabIndex = 0;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Basic";
      this.textBox54.BorderStyle = BorderStyle.FixedSingle;
      this.textBox54.Location = new Point(56, 113);
      this.textBox54.Name = "textBox54";
      this.textBox54.Size = new Size(273, 20);
      this.textBox54.TabIndex = 52;
      this.label71.AutoSize = true;
      this.label71.Location = new Point(8, 115);
      this.label71.Name = "label71";
      this.label71.Size = new Size(42, 13);
      this.label71.TabIndex = 51;
      this.label71.Text = "Tooltip:";
      this.label6.AutoSize = true;
      this.label6.Location = new Point(11, 73);
      this.label6.Name = "label6";
      this.label6.Size = new Size(38, 13);
      this.label6.TabIndex = 20;
      this.label6.Text = "Descr:";
      this.textBox5.BorderStyle = BorderStyle.FixedSingle;
      this.textBox5.Location = new Point(55, 71);
      this.textBox5.Multiline = true;
      this.textBox5.Name = "textBox5";
      this.textBox5.Size = new Size(273, 36);
      this.textBox5.TabIndex = 19;
      this.label5.AutoSize = true;
      this.label5.Location = new Point(13, 47);
      this.label5.Name = "label5";
      this.label5.Size = new Size(38, 13);
      this.label5.TabIndex = 10;
      this.label5.Text = "Name:";
      this.textBox4.BorderStyle = BorderStyle.FixedSingle;
      this.textBox4.Location = new Point(55, 45);
      this.textBox4.Name = "textBox4";
      this.textBox4.Size = new Size(273, 20);
      this.textBox4.TabIndex = 9;
      this.textBox1.BorderStyle = BorderStyle.FixedSingle;
      this.textBox1.Location = new Point(55, 19);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(51, 20);
      this.textBox1.TabIndex = 1;
      this.label1.AutoSize = true;
      this.label1.Location = new Point(11, 22);
      this.label1.Name = "label1";
      this.label1.Size = new Size(36, 13);
      this.label1.TabIndex = 7;
      this.label1.Text = "Index:";
      this.tabPage3.BackColor = SystemColors.Control;
      this.tabPage3.Controls.Add((Control) this.groupBox12);
      this.tabPage3.Location = new Point(4, 22);
      this.tabPage3.Name = "tabPage3";
      this.tabPage3.Size = new Size(1041, 598);
      this.tabPage3.TabIndex = 3;
      this.tabPage3.Text = "Graphic";
      this.groupBox12.Controls.Add((Control) this.groupBox20);
      this.groupBox12.Controls.Add((Control) this.groupBox19);
      this.groupBox12.Controls.Add((Control) this.groupBox18);
      this.groupBox12.Controls.Add((Control) this.groupBox17);
      this.groupBox12.Controls.Add((Control) this.groupBox16);
      this.groupBox12.Controls.Add((Control) this.groupBox15);
      this.groupBox12.Controls.Add((Control) this.groupBox14);
      this.groupBox12.Controls.Add((Control) this.groupBox13);
      this.groupBox12.Location = new Point(3, 3);
      this.groupBox12.Name = "groupBox12";
      this.groupBox12.Size = new Size(717, 550);
      this.groupBox12.TabIndex = 57;
      this.groupBox12.TabStop = false;
      this.groupBox12.Text = "Animation & Effect";
      this.groupBox20.Controls.Add((Control) this.textBox76);
      this.groupBox20.Controls.Add((Control) this.textBox75);
      this.groupBox20.Controls.Add((Control) this.textBox74);
      this.groupBox20.Controls.Add((Control) this.textBox73);
      this.groupBox20.Controls.Add((Control) this.textBox72);
      this.groupBox20.Controls.Add((Control) this.textBox71);
      this.groupBox20.Controls.Add((Control) this.label64);
      this.groupBox20.Controls.Add((Control) this.label65);
      this.groupBox20.Controls.Add((Control) this.label66);
      this.groupBox20.Controls.Add((Control) this.label67);
      this.groupBox20.Controls.Add((Control) this.label68);
      this.groupBox20.Controls.Add((Control) this.label69);
      this.groupBox20.Location = new Point(334, 422);
      this.groupBox20.Name = "groupBox20";
      this.groupBox20.Size = new Size(252, 118);
      this.groupBox20.TabIndex = 64;
      this.groupBox20.TabStop = false;
      this.groupBox20.Text = "Fire Object Delay 2";
      this.textBox76.BorderStyle = BorderStyle.FixedSingle;
      this.textBox76.Location = new Point(172, 29);
      this.textBox76.Name = "textBox76";
      this.textBox76.Size = new Size(65, 20);
      this.textBox76.TabIndex = 11;
      this.textBox75.BorderStyle = BorderStyle.FixedSingle;
      this.textBox75.Location = new Point(172, 89);
      this.textBox75.Name = "textBox75";
      this.textBox75.Size = new Size(65, 20);
      this.textBox75.TabIndex = 10;
      this.textBox74.BorderStyle = BorderStyle.FixedSingle;
      this.textBox74.Location = new Point(172, 58);
      this.textBox74.Name = "textBox74";
      this.textBox74.Size = new Size(65, 20);
      this.textBox74.TabIndex = 9;
      this.textBox73.BorderStyle = BorderStyle.FixedSingle;
      this.textBox73.Location = new Point(53, 89);
      this.textBox73.Name = "textBox73";
      this.textBox73.Size = new Size(65, 20);
      this.textBox73.TabIndex = 8;
      this.textBox72.BorderStyle = BorderStyle.FixedSingle;
      this.textBox72.Location = new Point(53, 58);
      this.textBox72.Name = "textBox72";
      this.textBox72.Size = new Size(65, 20);
      this.textBox72.TabIndex = 7;
      this.textBox71.BorderStyle = BorderStyle.FixedSingle;
      this.textBox71.Location = new Point(53, 29);
      this.textBox71.Name = "textBox71";
      this.textBox71.Size = new Size(65, 20);
      this.textBox71.TabIndex = 6;
      this.label64.AutoSize = true;
      this.label64.Location = new Point(135, 91);
      this.label64.Name = "label64";
      this.label64.Size = new Size(16, 13);
      this.label64.TabIndex = 5;
      this.label64.Text = "3:";
      this.label65.AutoSize = true;
      this.label65.Location = new Point(135, 60);
      this.label65.Name = "label65";
      this.label65.Size = new Size(16, 13);
      this.label65.TabIndex = 4;
      this.label65.Text = "2:";
      this.label66.AutoSize = true;
      this.label66.Location = new Point(9, 91);
      this.label66.Name = "label66";
      this.label66.Size = new Size(16, 13);
      this.label66.TabIndex = 3;
      this.label66.Text = "1:";
      this.label67.AutoSize = true;
      this.label67.Location = new Point(9, 60);
      this.label67.Name = "label67";
      this.label67.Size = new Size(16, 13);
      this.label67.TabIndex = 2;
      this.label67.Text = "0:";
      this.label68.AutoSize = true;
      this.label68.Location = new Point(135, 31);
      this.label68.Name = "label68";
      this.label68.Size = new Size(32, 13);
      this.label68.TabIndex = 1;
      this.label68.Text = "Dest:";
      this.label69.AutoSize = true;
      this.label69.Location = new Point(9, 31);
      this.label69.Name = "label69";
      this.label69.Size = new Size(38, 13);
      this.label69.TabIndex = 0;
      this.label69.Text = "Count:";
      this.groupBox19.Controls.Add((Control) this.textBox51);
      this.groupBox19.Controls.Add((Control) this.textBox50);
      this.groupBox19.Controls.Add((Control) this.textBox49);
      this.groupBox19.Controls.Add((Control) this.textBox48);
      this.groupBox19.Controls.Add((Control) this.textBox47);
      this.groupBox19.Controls.Add((Control) this.textBox46);
      this.groupBox19.Controls.Add((Control) this.label63);
      this.groupBox19.Controls.Add((Control) this.label62);
      this.groupBox19.Controls.Add((Control) this.label61);
      this.groupBox19.Controls.Add((Control) this.label60);
      this.groupBox19.Controls.Add((Control) this.label59);
      this.groupBox19.Controls.Add((Control) this.label58);
      this.groupBox19.Location = new Point(34, 422);
      this.groupBox19.Name = "groupBox19";
      this.groupBox19.Size = new Size(250, 118);
      this.groupBox19.TabIndex = 63;
      this.groupBox19.TabStop = false;
      this.groupBox19.Text = "Fire Object Delay 1";
      this.textBox51.BorderStyle = BorderStyle.FixedSingle;
      this.textBox51.Location = new Point(172, 29);
      this.textBox51.Name = "textBox51";
      this.textBox51.Size = new Size(65, 20);
      this.textBox51.TabIndex = 76;
      this.textBox50.BorderStyle = BorderStyle.FixedSingle;
      this.textBox50.Location = new Point(172, 89);
      this.textBox50.Name = "textBox50";
      this.textBox50.Size = new Size(65, 20);
      this.textBox50.TabIndex = 75;
      this.textBox49.BorderStyle = BorderStyle.FixedSingle;
      this.textBox49.Location = new Point(172, 58);
      this.textBox49.Name = "textBox49";
      this.textBox49.Size = new Size(65, 20);
      this.textBox49.TabIndex = 74;
      this.textBox48.BorderStyle = BorderStyle.FixedSingle;
      this.textBox48.Location = new Point(53, 89);
      this.textBox48.Name = "textBox48";
      this.textBox48.Size = new Size(65, 20);
      this.textBox48.TabIndex = 73;
      this.textBox47.BorderStyle = BorderStyle.FixedSingle;
      this.textBox47.Location = new Point(53, 58);
      this.textBox47.Name = "textBox47";
      this.textBox47.Size = new Size(65, 20);
      this.textBox47.TabIndex = 72;
      this.textBox46.BorderStyle = BorderStyle.FixedSingle;
      this.textBox46.Location = new Point(53, 29);
      this.textBox46.Name = "textBox46";
      this.textBox46.Size = new Size(65, 20);
      this.textBox46.TabIndex = 71;
      this.label63.AutoSize = true;
      this.label63.Location = new Point(139, 91);
      this.label63.Name = "label63";
      this.label63.Size = new Size(16, 13);
      this.label63.TabIndex = 5;
      this.label63.Text = "3:";
      this.label62.AutoSize = true;
      this.label62.Location = new Point(139, 60);
      this.label62.Name = "label62";
      this.label62.Size = new Size(16, 13);
      this.label62.TabIndex = 4;
      this.label62.Text = "2:";
      this.label61.AutoSize = true;
      this.label61.Location = new Point(9, 91);
      this.label61.Name = "label61";
      this.label61.Size = new Size(16, 13);
      this.label61.TabIndex = 3;
      this.label61.Text = "1:";
      this.label60.AutoSize = true;
      this.label60.Location = new Point(9, 60);
      this.label60.Name = "label60";
      this.label60.Size = new Size(16, 13);
      this.label60.TabIndex = 2;
      this.label60.Text = "0:";
      this.label59.AutoSize = true;
      this.label59.Location = new Point(139, 31);
      this.label59.Name = "label59";
      this.label59.Size = new Size(32, 13);
      this.label59.TabIndex = 1;
      this.label59.Text = "Dest:";
      this.label58.AutoSize = true;
      this.label58.Location = new Point(9, 31);
      this.label58.Name = "label58";
      this.label58.Size = new Size(38, 13);
      this.label58.TabIndex = 0;
      this.label58.Text = "Count:";
      this.groupBox18.Controls.Add((Control) this.textBox70);
      this.groupBox18.Controls.Add((Control) this.textBox69);
      this.groupBox18.Controls.Add((Control) this.textBox68);
      this.groupBox18.Controls.Add((Control) this.textBox67);
      this.groupBox18.Controls.Add((Control) this.textBox66);
      this.groupBox18.Controls.Add((Control) this.textBox65);
      this.groupBox18.Controls.Add((Control) this.label52);
      this.groupBox18.Controls.Add((Control) this.label53);
      this.groupBox18.Controls.Add((Control) this.label54);
      this.groupBox18.Controls.Add((Control) this.label55);
      this.groupBox18.Controls.Add((Control) this.label56);
      this.groupBox18.Controls.Add((Control) this.label57);
      this.groupBox18.Location = new Point(331, 287);
      this.groupBox18.Name = "groupBox18";
      this.groupBox18.Size = new Size((int) byte.MaxValue, 128);
      this.groupBox18.TabIndex = 62;
      this.groupBox18.TabStop = false;
      this.groupBox18.Text = "Fire Object 2";
      this.textBox70.BorderStyle = BorderStyle.FixedSingle;
      this.textBox70.Location = new Point(172, 94);
      this.textBox70.Name = "textBox70";
      this.textBox70.Size = new Size(65, 20);
      this.textBox70.TabIndex = 11;
      this.textBox69.BorderStyle = BorderStyle.FixedSingle;
      this.textBox69.Location = new Point(48, 94);
      this.textBox69.Name = "textBox69";
      this.textBox69.Size = new Size(65, 20);
      this.textBox69.TabIndex = 10;
      this.textBox68.BorderStyle = BorderStyle.FixedSingle;
      this.textBox68.Location = new Point(172, 64);
      this.textBox68.Name = "textBox68";
      this.textBox68.Size = new Size(65, 20);
      this.textBox68.TabIndex = 9;
      this.textBox67.BorderStyle = BorderStyle.FixedSingle;
      this.textBox67.Location = new Point(48, 64);
      this.textBox67.Name = "textBox67";
      this.textBox67.Size = new Size(65, 20);
      this.textBox67.TabIndex = 8;
      this.textBox66.BorderStyle = BorderStyle.FixedSingle;
      this.textBox66.Location = new Point(172, 31);
      this.textBox66.Name = "textBox66";
      this.textBox66.Size = new Size(65, 20);
      this.textBox66.TabIndex = 7;
      this.textBox65.BorderStyle = BorderStyle.FixedSingle;
      this.textBox65.Location = new Point(48, 31);
      this.textBox65.Name = "textBox65";
      this.textBox65.Size = new Size(65, 20);
      this.textBox65.TabIndex = 6;
      this.label52.AutoSize = true;
      this.label52.Location = new Point(124, 96);
      this.label52.Name = "label52";
      this.label52.Size = new Size(38, 13);
      this.label52.TabIndex = 5;
      this.label52.Text = "Coord:";
      this.label53.AutoSize = true;
      this.label53.Location = new Point(124, 66);
      this.label53.Name = "label53";
      this.label53.Size = new Size(17, 13);
      this.label53.TabIndex = 4;
      this.label53.Text = "Z:";
      this.label54.AutoSize = true;
      this.label54.Location = new Point(124, 34);
      this.label54.Name = "label54";
      this.label54.Size = new Size(41, 13);
      this.label54.TabIndex = 3;
      this.label54.Text = "Speed:";
      this.label55.AutoSize = true;
      this.label55.Location = new Point(8, 96);
      this.label55.Name = "label55";
      this.label55.Size = new Size(18, 13);
      this.label55.TabIndex = 2;
      this.label55.Text = "H:";
      this.label56.AutoSize = true;
      this.label56.Location = new Point(8, 66);
      this.label56.Name = "label56";
      this.label56.Size = new Size(17, 13);
      this.label56.TabIndex = 1;
      this.label56.Text = "X:";
      this.label57.AutoSize = true;
      this.label57.Location = new Point(8, 34);
      this.label57.Name = "label57";
      this.label57.Size = new Size(34, 13);
      this.label57.TabIndex = 0;
      this.label57.Text = "Type:";
      this.groupBox17.Controls.Add((Control) this.textBox45);
      this.groupBox17.Controls.Add((Control) this.textBox44);
      this.groupBox17.Controls.Add((Control) this.textBox43);
      this.groupBox17.Controls.Add((Control) this.textBox42);
      this.groupBox17.Controls.Add((Control) this.textBox41);
      this.groupBox17.Controls.Add((Control) this.textBox40);
      this.groupBox17.Controls.Add((Control) this.label51);
      this.groupBox17.Controls.Add((Control) this.label50);
      this.groupBox17.Controls.Add((Control) this.label49);
      this.groupBox17.Controls.Add((Control) this.label48);
      this.groupBox17.Controls.Add((Control) this.label47);
      this.groupBox17.Controls.Add((Control) this.label46);
      this.groupBox17.Location = new Point(34, 287);
      this.groupBox17.Name = "groupBox17";
      this.groupBox17.Size = new Size(250, 128);
      this.groupBox17.TabIndex = 61;
      this.groupBox17.TabStop = false;
      this.groupBox17.Text = "Fire Object 1";
      this.textBox45.BorderStyle = BorderStyle.FixedSingle;
      this.textBox45.Location = new Point(172, 94);
      this.textBox45.Name = "textBox45";
      this.textBox45.Size = new Size(65, 20);
      this.textBox45.TabIndex = 70;
      this.textBox44.BorderStyle = BorderStyle.FixedSingle;
      this.textBox44.Location = new Point(48, 94);
      this.textBox44.Name = "textBox44";
      this.textBox44.Size = new Size(65, 20);
      this.textBox44.TabIndex = 69;
      this.textBox43.BorderStyle = BorderStyle.FixedSingle;
      this.textBox43.Location = new Point(172, 64);
      this.textBox43.Name = "textBox43";
      this.textBox43.Size = new Size(65, 20);
      this.textBox43.TabIndex = 68;
      this.textBox42.BorderStyle = BorderStyle.FixedSingle;
      this.textBox42.Location = new Point(48, 64);
      this.textBox42.Name = "textBox42";
      this.textBox42.Size = new Size(65, 20);
      this.textBox42.TabIndex = 67;
      this.textBox41.BorderStyle = BorderStyle.FixedSingle;
      this.textBox41.Location = new Point(172, 31);
      this.textBox41.Name = "textBox41";
      this.textBox41.Size = new Size(65, 20);
      this.textBox41.TabIndex = 66;
      this.textBox40.BorderStyle = BorderStyle.FixedSingle;
      this.textBox40.Location = new Point(48, 31);
      this.textBox40.Name = "textBox40";
      this.textBox40.Size = new Size(65, 20);
      this.textBox40.TabIndex = 65;
      this.label51.AutoSize = true;
      this.label51.Location = new Point(124, 96);
      this.label51.Name = "label51";
      this.label51.Size = new Size(38, 13);
      this.label51.TabIndex = 5;
      this.label51.Text = "Coord:";
      this.label50.AutoSize = true;
      this.label50.Location = new Point(124, 66);
      this.label50.Name = "label50";
      this.label50.Size = new Size(17, 13);
      this.label50.TabIndex = 4;
      this.label50.Text = "Z:";
      this.label49.AutoSize = true;
      this.label49.Location = new Point(124, 34);
      this.label49.Name = "label49";
      this.label49.Size = new Size(41, 13);
      this.label49.TabIndex = 3;
      this.label49.Text = "Speed:";
      this.label48.AutoSize = true;
      this.label48.Location = new Point(8, 96);
      this.label48.Name = "label48";
      this.label48.Size = new Size(18, 13);
      this.label48.TabIndex = 2;
      this.label48.Text = "H:";
      this.label47.AutoSize = true;
      this.label47.Location = new Point(8, 66);
      this.label47.Name = "label47";
      this.label47.Size = new Size(17, 13);
      this.label47.TabIndex = 1;
      this.label47.Text = "X:";
      this.label46.AutoSize = true;
      this.label46.Location = new Point(8, 34);
      this.label46.Name = "label46";
      this.label46.Size = new Size(34, 13);
      this.label46.TabIndex = 0;
      this.label46.Text = "Type:";
      this.groupBox16.Controls.Add((Control) this.textBox64);
      this.groupBox16.Controls.Add((Control) this.textBox63);
      this.groupBox16.Controls.Add((Control) this.textBox62);
      this.groupBox16.Controls.Add((Control) this.textBox59);
      this.groupBox16.Controls.Add((Control) this.label42);
      this.groupBox16.Controls.Add((Control) this.label43);
      this.groupBox16.Controls.Add((Control) this.label44);
      this.groupBox16.Controls.Add((Control) this.label45);
      this.groupBox16.Location = new Point(334, 132);
      this.groupBox16.Name = "groupBox16";
      this.groupBox16.Size = new Size(252, 150);
      this.groupBox16.TabIndex = 60;
      this.groupBox16.TabStop = false;
      this.groupBox16.Text = "Effect 2";
      this.textBox64.BorderStyle = BorderStyle.FixedSingle;
      this.textBox64.Location = new Point(53, 119);
      this.textBox64.Name = "textBox64";
      this.textBox64.Size = new Size(169, 20);
      this.textBox64.TabIndex = 69;
      this.textBox63.BorderStyle = BorderStyle.FixedSingle;
      this.textBox63.Location = new Point(53, 92);
      this.textBox63.Name = "textBox63";
      this.textBox63.Size = new Size(169, 20);
      this.textBox63.TabIndex = 68;
      this.textBox62.BorderStyle = BorderStyle.FixedSingle;
      this.textBox62.Location = new Point(53, 64);
      this.textBox62.Name = "textBox62";
      this.textBox62.Size = new Size(169, 20);
      this.textBox62.TabIndex = 67;
      this.textBox59.BorderStyle = BorderStyle.FixedSingle;
      this.textBox59.Location = new Point(53, 32);
      this.textBox59.Name = "textBox59";
      this.textBox59.Size = new Size(169, 20);
      this.textBox59.TabIndex = 66;
      this.label42.AutoSize = true;
      this.label42.Location = new Point(6, 121);
      this.label42.Name = "label42";
      this.label42.Size = new Size(36, 13);
      this.label42.TabIndex = 3;
      this.label42.Text = "Fire 3:";
      this.label43.AutoSize = true;
      this.label43.Location = new Point(6, 94);
      this.label43.Name = "label43";
      this.label43.Size = new Size(36, 13);
      this.label43.TabIndex = 2;
      this.label43.Text = "Fire 2:";
      this.label44.AutoSize = true;
      this.label44.Location = new Point(6, 66);
      this.label44.Name = "label44";
      this.label44.Size = new Size(36, 13);
      this.label44.TabIndex = 1;
      this.label44.Text = "Fire 1:";
      this.label45.AutoSize = true;
      this.label45.Location = new Point(6, 34);
      this.label45.Name = "label45";
      this.label45.Size = new Size(41, 13);
      this.label45.TabIndex = 0;
      this.label45.Text = "Ready:";
      this.groupBox15.Controls.Add((Control) this.textBox39);
      this.groupBox15.Controls.Add((Control) this.textBox38);
      this.groupBox15.Controls.Add((Control) this.textBox37);
      this.groupBox15.Controls.Add((Control) this.textBox34);
      this.groupBox15.Controls.Add((Control) this.label41);
      this.groupBox15.Controls.Add((Control) this.label40);
      this.groupBox15.Controls.Add((Control) this.label39);
      this.groupBox15.Controls.Add((Control) this.label38);
      this.groupBox15.Location = new Point(34, 132);
      this.groupBox15.Name = "groupBox15";
      this.groupBox15.Size = new Size(250, 150);
      this.groupBox15.TabIndex = 59;
      this.groupBox15.TabStop = false;
      this.groupBox15.Text = "Effect 1";
      this.textBox39.BorderStyle = BorderStyle.FixedSingle;
      this.textBox39.Location = new Point(53, 119);
      this.textBox39.Name = "textBox39";
      this.textBox39.Size = new Size(169, 20);
      this.textBox39.TabIndex = 65;
      this.textBox38.BorderStyle = BorderStyle.FixedSingle;
      this.textBox38.Location = new Point(53, 92);
      this.textBox38.Name = "textBox38";
      this.textBox38.Size = new Size(169, 20);
      this.textBox38.TabIndex = 64;
      this.textBox37.BorderStyle = BorderStyle.FixedSingle;
      this.textBox37.Location = new Point(53, 64);
      this.textBox37.Name = "textBox37";
      this.textBox37.Size = new Size(169, 20);
      this.textBox37.TabIndex = 63;
      this.textBox34.BorderStyle = BorderStyle.FixedSingle;
      this.textBox34.Location = new Point(53, 32);
      this.textBox34.Name = "textBox34";
      this.textBox34.Size = new Size(169, 20);
      this.textBox34.TabIndex = 60;
      this.label41.AutoSize = true;
      this.label41.Location = new Point(6, 121);
      this.label41.Name = "label41";
      this.label41.Size = new Size(36, 13);
      this.label41.TabIndex = 3;
      this.label41.Text = "Fire 3:";
      this.label40.AutoSize = true;
      this.label40.Location = new Point(6, 94);
      this.label40.Name = "label40";
      this.label40.Size = new Size(36, 13);
      this.label40.TabIndex = 2;
      this.label40.Text = "Fire 2:";
      this.label39.AutoSize = true;
      this.label39.Location = new Point(6, 66);
      this.label39.Name = "label39";
      this.label39.Size = new Size(36, 13);
      this.label39.TabIndex = 1;
      this.label39.Text = "Fire 1:";
      this.label38.AutoSize = true;
      this.label38.Location = new Point(6, 34);
      this.label38.Name = "label38";
      this.label38.Size = new Size(41, 13);
      this.label38.TabIndex = 0;
      this.label38.Text = "Ready:";
      this.groupBox14.Controls.Add((Control) this.textBox61);
      this.groupBox14.Controls.Add((Control) this.textBox60);
      this.groupBox14.Controls.Add((Control) this.textBox58);
      this.groupBox14.Controls.Add((Control) this.label35);
      this.groupBox14.Controls.Add((Control) this.label36);
      this.groupBox14.Controls.Add((Control) this.label37);
      this.groupBox14.Location = new Point(334, 18);
      this.groupBox14.Name = "groupBox14";
      this.groupBox14.Size = new Size(252, 108);
      this.groupBox14.TabIndex = 58;
      this.groupBox14.TabStop = false;
      this.groupBox14.Text = "Animations 2";
      this.textBox61.BorderStyle = BorderStyle.FixedSingle;
      this.textBox61.Location = new Point(53, 82);
      this.textBox61.Name = "textBox61";
      this.textBox61.Size = new Size(169, 20);
      this.textBox61.TabIndex = 68;
      this.textBox60.BorderStyle = BorderStyle.FixedSingle;
      this.textBox60.Location = new Point(53, 56);
      this.textBox60.Name = "textBox60";
      this.textBox60.Size = new Size(169, 20);
      this.textBox60.TabIndex = 67;
      this.textBox58.BorderStyle = BorderStyle.FixedSingle;
      this.textBox58.Location = new Point(53, 30);
      this.textBox58.Name = "textBox58";
      this.textBox58.Size = new Size(169, 20);
      this.textBox58.TabIndex = 63;
      this.label35.AutoSize = true;
      this.label35.Location = new Point(6, 82);
      this.label35.Name = "label35";
      this.label35.Size = new Size(27, 13);
      this.label35.TabIndex = 64;
      this.label35.Text = "Fire:";
      this.label36.AutoSize = true;
      this.label36.Location = new Point(6, 58);
      this.label36.Name = "label36";
      this.label36.Size = new Size(26, 13);
      this.label36.TabIndex = 63;
      this.label36.Text = "Still:";
      this.label37.AutoSize = true;
      this.label37.Location = new Point(6, 32);
      this.label37.Name = "label37";
      this.label37.Size = new Size(41, 13);
      this.label37.TabIndex = 62;
      this.label37.Text = "Ready:";
      this.groupBox13.Controls.Add((Control) this.textBox36);
      this.groupBox13.Controls.Add((Control) this.textBox35);
      this.groupBox13.Controls.Add((Control) this.label34);
      this.groupBox13.Controls.Add((Control) this.label33);
      this.groupBox13.Controls.Add((Control) this.label32);
      this.groupBox13.Controls.Add((Control) this.textBox33);
      this.groupBox13.Location = new Point(34, 18);
      this.groupBox13.Name = "groupBox13";
      this.groupBox13.Size = new Size(250, 108);
      this.groupBox13.TabIndex = 57;
      this.groupBox13.TabStop = false;
      this.groupBox13.Text = "Animations 1";
      this.textBox36.BorderStyle = BorderStyle.FixedSingle;
      this.textBox36.Location = new Point(53, 82);
      this.textBox36.Name = "textBox36";
      this.textBox36.Size = new Size(169, 20);
      this.textBox36.TabIndex = 62;
      this.textBox35.BorderStyle = BorderStyle.FixedSingle;
      this.textBox35.Location = new Point(53, 56);
      this.textBox35.Name = "textBox35";
      this.textBox35.Size = new Size(169, 20);
      this.textBox35.TabIndex = 61;
      this.label34.AutoSize = true;
      this.label34.Location = new Point(6, 82);
      this.label34.Name = "label34";
      this.label34.Size = new Size(27, 13);
      this.label34.TabIndex = 59;
      this.label34.Text = "Fire:";
      this.label33.AutoSize = true;
      this.label33.Location = new Point(6, 58);
      this.label33.Name = "label33";
      this.label33.Size = new Size(26, 13);
      this.label33.TabIndex = 58;
      this.label33.Text = "Still:";
      this.label32.AutoSize = true;
      this.label32.Location = new Point(6, 32);
      this.label32.Name = "label32";
      this.label32.Size = new Size(41, 13);
      this.label32.TabIndex = 57;
      this.label32.Text = "Ready:";
      this.textBox33.BorderStyle = BorderStyle.FixedSingle;
      this.textBox33.Location = new Point(53, 30);
      this.textBox33.Name = "textBox33";
      this.textBox33.Size = new Size(169, 20);
      this.textBox33.TabIndex = 56;
      this.tabPage2.BackColor = SystemColors.Control;
      this.tabPage2.Controls.Add((Control) this.textBox160);
      this.tabPage2.Controls.Add((Control) this.textBox156);
      this.tabPage2.Controls.Add((Control) this.textBox157);
      this.tabPage2.Controls.Add((Control) this.textBox159);
      this.tabPage2.Controls.Add((Control) this.textBox153);
      this.tabPage2.Controls.Add((Control) this.textBox154);
      this.tabPage2.Controls.Add((Control) this.textBox155);
      this.tabPage2.Controls.Add((Control) this.textBox149);
      this.tabPage2.Controls.Add((Control) this.textBox150);
      this.tabPage2.Controls.Add((Control) this.textBox151);
      this.tabPage2.Controls.Add((Control) this.textBox152);
      this.tabPage2.Controls.Add((Control) this.textBox158);
      this.tabPage2.Controls.Add((Control) this.textBox145);
      this.tabPage2.Controls.Add((Control) this.textBox146);
      this.tabPage2.Controls.Add((Control) this.textBox147);
      this.tabPage2.Controls.Add((Control) this.label137);
      this.tabPage2.Controls.Add((Control) this.textBox141);
      this.tabPage2.Controls.Add((Control) this.textBox142);
      this.tabPage2.Controls.Add((Control) this.textBox143);
      this.tabPage2.Controls.Add((Control) this.label136);
      this.tabPage2.Controls.Add((Control) this.textBox129);
      this.tabPage2.Controls.Add((Control) this.textBox133);
      this.tabPage2.Controls.Add((Control) this.textBox137);
      this.tabPage2.Controls.Add((Control) this.textBox138);
      this.tabPage2.Controls.Add((Control) this.textBox139);
      this.tabPage2.Controls.Add((Control) this.textBox84);
      this.tabPage2.Controls.Add((Control) this.textBox134);
      this.tabPage2.Controls.Add((Control) this.textBox135);
      this.tabPage2.Controls.Add((Control) this.label85);
      this.tabPage2.Controls.Add((Control) this.textBox130);
      this.tabPage2.Controls.Add((Control) this.textBox131);
      this.tabPage2.Controls.Add((Control) this.label135);
      this.tabPage2.Controls.Add((Control) this.textBox148);
      this.tabPage2.Controls.Add((Control) this.textBox140);
      this.tabPage2.Controls.Add((Control) this.textBox144);
      this.tabPage2.Location = new Point(4, 22);
      this.tabPage2.Name = "tabPage2";
      this.tabPage2.Size = new Size(1041, 598);
      this.tabPage2.TabIndex = 4;
      this.tabPage2.Text = "Levels";
      this.textBox160.Location = new Point(602, 215);
      this.textBox160.Name = "textBox160";
      this.textBox160.Size = new Size(30, 20);
      this.textBox160.TabIndex = 70;
      this.textBox156.Location = new Point(602, 166);
      this.textBox156.Name = "textBox156";
      this.textBox156.Size = new Size(30, 20);
      this.textBox156.TabIndex = 66;
      this.textBox157.Location = new Point(860, 325);
      this.textBox157.Name = "textBox157";
      this.textBox157.Size = new Size(26, 20);
      this.textBox157.TabIndex = 55;
      this.textBox159.Location = new Point(934, 325);
      this.textBox159.Name = "textBox159";
      this.textBox159.Size = new Size(26, 20);
      this.textBox159.TabIndex = 57;
      this.textBox153.Location = new Point(860, 292);
      this.textBox153.Name = "textBox153";
      this.textBox153.Size = new Size(26, 20);
      this.textBox153.TabIndex = 52;
      this.textBox154.Location = new Point(902, 291);
      this.textBox154.Name = "textBox154";
      this.textBox154.Size = new Size(26, 20);
      this.textBox154.TabIndex = 53;
      this.textBox155.Location = new Point(934, 285);
      this.textBox155.Name = "textBox155";
      this.textBox155.Size = new Size(26, 20);
      this.textBox155.TabIndex = 54;
      this.textBox149.Location = new Point(602, 120);
      this.textBox149.Name = "textBox149";
      this.textBox149.Size = new Size(30, 20);
      this.textBox149.TabIndex = 63;
      this.textBox150.Location = new Point(860, 259);
      this.textBox150.Name = "textBox150";
      this.textBox150.Size = new Size(26, 20);
      this.textBox150.TabIndex = 49;
      this.textBox151.Location = new Point(902, 259);
      this.textBox151.Name = "textBox151";
      this.textBox151.Size = new Size(26, 20);
      this.textBox151.TabIndex = 50;
      this.textBox152.Location = new Point(934, 259);
      this.textBox152.Name = "textBox152";
      this.textBox152.Size = new Size(26, 20);
      this.textBox152.TabIndex = 51;
      this.textBox158.Location = new Point(902, 325);
      this.textBox158.Name = "textBox158";
      this.textBox158.Size = new Size(26, 20);
      this.textBox158.TabIndex = 56;
      this.textBox145.Location = new Point(870, 225);
      this.textBox145.Name = "textBox145";
      this.textBox145.Size = new Size(26, 20);
      this.textBox145.TabIndex = 46;
      this.textBox146.Location = new Point(902, 225);
      this.textBox146.Name = "textBox146";
      this.textBox146.Size = new Size(26, 20);
      this.textBox146.TabIndex = 47;
      this.textBox147.Location = new Point(934, 225);
      this.textBox147.Name = "textBox147";
      this.textBox147.Size = new Size(26, 20);
      this.textBox147.TabIndex = 48;
      this.label137.AutoSize = true;
      this.label137.ForeColor = Color.Purple;
      this.label137.Location = new Point(200, 259);
      this.label137.Name = "label137";
      this.label137.Size = new Size(47, 13);
      this.label137.TabIndex = 69;
      this.label137.Text = "label137";
      this.textBox141.Location = new Point(860, 191);
      this.textBox141.Name = "textBox141";
      this.textBox141.Size = new Size(26, 20);
      this.textBox141.TabIndex = 43;
      this.textBox142.Location = new Point(902, 191);
      this.textBox142.Name = "textBox142";
      this.textBox142.Size = new Size(26, 20);
      this.textBox142.TabIndex = 44;
      this.textBox143.Location = new Point(934, 191);
      this.textBox143.Name = "textBox143";
      this.textBox143.Size = new Size(26, 20);
      this.textBox143.TabIndex = 45;
      this.label136.AutoSize = true;
      this.label136.ForeColor = Color.Purple;
      this.label136.Location = new Point(200, 215);
      this.label136.Name = "label136";
      this.label136.Size = new Size(47, 13);
      this.label136.TabIndex = 67;
      this.label136.Text = "label136";
      this.textBox129.Location = new Point(870, 81);
      this.textBox129.Name = "textBox129";
      this.textBox129.Size = new Size(26, 20);
      this.textBox129.TabIndex = 21;
      this.textBox133.Location = new Point(870, 116);
      this.textBox133.Name = "textBox133";
      this.textBox133.Size = new Size(26, 20);
      this.textBox133.TabIndex = 37;
      this.textBox137.Location = new Point(860, 153);
      this.textBox137.Name = "textBox137";
      this.textBox137.Size = new Size(26, 20);
      this.textBox137.TabIndex = 40;
      this.textBox138.Location = new Point(902, 153);
      this.textBox138.Name = "textBox138";
      this.textBox138.Size = new Size(26, 20);
      this.textBox138.TabIndex = 41;
      this.textBox139.Location = new Point(934, 153);
      this.textBox139.Name = "textBox139";
      this.textBox139.Size = new Size(26, 20);
      this.textBox139.TabIndex = 42;
      this.textBox84.Location = new Point(757, 54);
      this.textBox84.Name = "textBox84";
      this.textBox84.Size = new Size(35, 20);
      this.textBox84.TabIndex = 1;
      this.textBox134.Location = new Point(902, 116);
      this.textBox134.Name = "textBox134";
      this.textBox134.Size = new Size(26, 20);
      this.textBox134.TabIndex = 38;
      this.textBox135.Location = new Point(934, 113);
      this.textBox135.Name = "textBox135";
      this.textBox135.Size = new Size(26, 20);
      this.textBox135.TabIndex = 39;
      this.label85.AutoSize = true;
      this.label85.Location = new Point(715, 57);
      this.label85.Name = "label85";
      this.label85.Size = new Size(36, 13);
      this.label85.TabIndex = 2;
      this.label85.Text = "Index:";
      this.textBox130.Location = new Point(902, 81);
      this.textBox130.Name = "textBox130";
      this.textBox130.Size = new Size(26, 20);
      this.textBox130.TabIndex = 35;
      this.textBox131.Location = new Point(934, 80);
      this.textBox131.Name = "textBox131";
      this.textBox131.Size = new Size(26, 20);
      this.textBox131.TabIndex = 36;
      this.label135.AutoSize = true;
      this.label135.ForeColor = Color.Purple;
      this.label135.Location = new Point(200, 166);
      this.label135.Name = "label135";
      this.label135.Size = new Size(47, 13);
      this.label135.TabIndex = 65;
      this.label135.Text = "label135";
      this.textBox148.Location = new Point(762, 207);
      this.textBox148.Name = "textBox148";
      this.textBox148.Size = new Size(30, 20);
      this.textBox148.TabIndex = 60;
      this.textBox148.Visible = false;
      this.textBox140.Location = new Point(762, 119);
      this.textBox140.Name = "textBox140";
      this.textBox140.Size = new Size(30, 20);
      this.textBox140.TabIndex = 27;
      this.textBox140.Visible = false;
      this.textBox144.Location = new Point(762, 163);
      this.textBox144.Name = "textBox144";
      this.textBox144.Size = new Size(30, 20);
      this.textBox144.TabIndex = 57;
      this.textBox144.Visible = false;
      this.tabPage4.BackColor = SystemColors.Control;
      this.tabPage4.Controls.Add((Control) this.label84);
      this.tabPage4.Controls.Add((Control) this.textBox83);
      this.tabPage4.Controls.Add((Control) this.label81);
      this.tabPage4.Controls.Add((Control) this.textBox80);
      this.tabPage4.Controls.Add((Control) this.label80);
      this.tabPage4.Controls.Add((Control) this.label79);
      this.tabPage4.Controls.Add((Control) this.textBox8);
      this.tabPage4.Controls.Add((Control) this.label9);
      this.tabPage4.Controls.Add((Control) this.textBox79);
      this.tabPage4.Controls.Add((Control) this.label77);
      this.tabPage4.Controls.Add((Control) this.textBox18);
      this.tabPage4.Controls.Add((Control) this.textBox78);
      this.tabPage4.Controls.Add((Control) this.label76);
      this.tabPage4.Controls.Add((Control) this.textBox77);
      this.tabPage4.Controls.Add((Control) this.label72);
      this.tabPage4.Controls.Add((Control) this.label27);
      this.tabPage4.Controls.Add((Control) this.textBox28);
      this.tabPage4.Controls.Add((Control) this.textBox53);
      this.tabPage4.Controls.Add((Control) this.label10);
      this.tabPage4.Controls.Add((Control) this.textBox27);
      this.tabPage4.Controls.Add((Control) this.label4);
      this.tabPage4.Controls.Add((Control) this.textBox26);
      this.tabPage4.Location = new Point(4, 22);
      this.tabPage4.Name = "tabPage4";
      this.tabPage4.Size = new Size(1041, 598);
      this.tabPage4.TabIndex = 2;
      this.tabPage4.Text = "Other";
      this.label84.AutoSize = true;
      this.label84.Location = new Point(96, 376);
      this.label84.Name = "label84";
      this.label84.Size = new Size(66, 13);
      this.label84.TabIndex = 70;
      this.label84.Text = "a_allowzone";
      this.textBox83.Location = new Point(170, 369);
      this.textBox83.Name = "textBox83";
      this.textBox83.Size = new Size(100, 20);
      this.textBox83.TabIndex = 69;
      this.label81.AutoSize = true;
      this.label81.Location = new Point(209, 187);
      this.label81.Name = "label81";
      this.label81.Size = new Size(77, 13);
      this.label81.TabIndex = 66;
      this.label81.Text = "a_summon_idx";
      this.textBox80.Location = new Point(290, 184);
      this.textBox80.Name = "textBox80";
      this.textBox80.Size = new Size(100, 20);
      this.textBox80.TabIndex = 65;
      this.label80.AutoSize = true;
      this.label80.Location = new Point(508, 81);
      this.label80.Name = "label80";
      this.label80.Size = new Size(81, 13);
      this.label80.TabIndex = 64;
      this.label80.Text = "a_soul_consum";
      this.label79.AutoSize = true;
      this.label79.Location = new Point(508, 55);
      this.label79.Name = "label79";
      this.label79.Size = new Size(130, 13);
      this.label79.TabIndex = 63;
      this.label79.Text = "a_use_needWearingType";
      this.textBox8.BorderStyle = BorderStyle.FixedSingle;
      this.textBox8.Location = new Point(647, 16);
      this.textBox8.Name = "textBox8";
      this.textBox8.Size = new Size(46, 20);
      this.textBox8.TabIndex = 24;
      this.label9.AutoSize = true;
      this.label9.Location = new Point(577, 18);
      this.label9.Name = "label9";
      this.label9.Size = new Size(64, 13);
      this.label9.TabIndex = 25;
      this.label9.Text = "a_maxLevel";
      this.textBox79.Location = new Point(593, 78);
      this.textBox79.Name = "textBox79";
      this.textBox79.Size = new Size(100, 20);
      this.textBox79.TabIndex = 62;
      this.label77.AutoSize = true;
      this.label77.Location = new Point(18, 219);
      this.label77.Name = "label77";
      this.label77.Size = new Size(75, 13);
      this.label77.TabIndex = 61;
      this.label77.Text = "a_targetparam";
      this.textBox18.BackColor = Color.Red;
      this.textBox18.Location = new Point(644, 52);
      this.textBox18.Name = "textBox18";
      this.textBox18.Size = new Size(49, 20);
      this.textBox18.TabIndex = 42;
      this.textBox78.Location = new Point(99, 212);
      this.textBox78.Name = "textBox78";
      this.textBox78.Size = new Size(58, 20);
      this.textBox78.TabIndex = 60;
      this.label76.AutoSize = true;
      this.label76.Location = new Point(29, 174);
      this.label76.Name = "label76";
      this.label76.Size = new Size(64, 13);
      this.label76.TabIndex = 59;
      this.label76.Text = "a_selfparam";
      this.textBox77.Location = new Point(99, 170);
      this.textBox77.Name = "textBox77";
      this.textBox77.Size = new Size(58, 20);
      this.textBox77.TabIndex = 58;
      this.label72.AutoSize = true;
      this.label72.Location = new Point(29, 137);
      this.label72.Name = "label72";
      this.label72.Size = new Size(64, 13);
      this.label72.TabIndex = 56;
      this.label72.Text = "a_cd_after2";
      this.label27.AutoSize = true;
      this.label27.Location = new Point(27, 104);
      this.label27.Name = "label27";
      this.label27.Size = new Size(108, 13);
      this.label27.TabIndex = 54;
      this.label27.Text = "a_appWeaponType1";
      this.textBox28.Location = new Point(153, 97);
      this.textBox28.Name = "textBox28";
      this.textBox28.Size = new Size(100, 20);
      this.textBox28.TabIndex = 53;
      this.textBox53.BorderStyle = BorderStyle.FixedSingle;
      this.textBox53.Location = new Point(99, 135);
      this.textBox53.Name = "textBox53";
      this.textBox53.Size = new Size(58, 20);
      this.textBox53.TabIndex = 52;
      this.label10.AutoSize = true;
      this.label10.Location = new Point(27, 72);
      this.label10.Name = "label10";
      this.label10.Size = new Size(108, 13);
      this.label10.TabIndex = 52;
      this.label10.Text = "a_appWeaponType0";
      this.textBox27.Location = new Point(153, 65);
      this.textBox27.Name = "textBox27";
      this.textBox27.Size = new Size(100, 20);
      this.textBox27.TabIndex = 51;
      this.label4.AutoSize = true;
      this.label4.Location = new Point(27, 36);
      this.label4.Name = "label4";
      this.label4.Size = new Size(62, 13);
      this.label4.TabIndex = 50;
      this.label4.Text = "a_appState";
      this.textBox26.Location = new Point(99, 33);
      this.textBox26.Name = "textBox26";
      this.textBox26.Size = new Size(100, 20);
      this.textBox26.TabIndex = 49;
      this.button6.FlatStyle = FlatStyle.Flat;
      this.button6.Font = new Font("Microsoft Sans Serif", 8.25f, FontStyle.Bold, GraphicsUnit.Point, (byte) 0);
      this.button6.Location = new Point(1083, 653);
      this.button6.Name = "button6";
      this.button6.Size = new Size(100, 31);
      this.button6.TabIndex = 58;
      this.button6.Text = "Save Level";
      this.button6.UseVisualStyleBackColor = true;
      this.button6.Click += new EventHandler(this.button6_Click);
      this.button2.FlatStyle = FlatStyle.Flat;
      this.button2.Font = new Font("Microsoft Sans Serif", 8.25f, FontStyle.Bold, GraphicsUnit.Point, (byte) 0);
      this.button2.Location = new Point(1189, 653);
      this.button2.Name = "button2";
      this.button2.Size = new Size(143, 31);
      this.button2.TabIndex = 34;
      this.button2.Text = "Save Skill";
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.toolTip1.AutoPopDelay = 5000;
      this.toolTip1.InitialDelay = 500;
      this.toolTip1.ReshowDelay = 100;
      this.toolTip1.ToolTipTitle = "Information";
      this.label130.AutoSize = true;
      this.label130.Font = new Font("Calibri", 12f, FontStyle.Bold, GraphicsUnit.Point, (byte) 0);
      this.label130.Location = new Point(286, 658);
      this.label130.Name = "label130";
      this.label130.Size = new Size(66, 19);
      this.label130.TabIndex = 59;
      this.label130.Text = "label130";
      this.label130.Visible = false;
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(1346, 691);
      this.Controls.Add((Control) this.label130);
      this.Controls.Add((Control) this.button6);
      this.Controls.Add((Control) this.button2);
      this.Controls.Add((Control) this.tabControl1);
      this.Controls.Add((Control) this.groupBox5);
      this.Controls.Add((Control) this.groupBox3);
      this.Controls.Add((Control) this.menuStrip1);
      this.FormBorderStyle = FormBorderStyle.FixedDialog;
      this.MainMenuStrip = this.menuStrip1;
      this.MaximizeBox = false;
      this.Name = "Skill_EditorV1";
      this.StartPosition = FormStartPosition.CenterScreen;
      this.Text = "Skill Editor EP4V1";
      this.Load += new EventHandler(this.Form4_Load);
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.groupBox3.ResumeLayout(false);
      this.groupBox5.ResumeLayout(false);
      this.groupBox5.PerformLayout();
      this.tabControl1.ResumeLayout(false);
      this.tabPage1.ResumeLayout(false);
      this.tabPage1.PerformLayout();
      this.tabControl2.ResumeLayout(false);
      this.tabPage5.ResumeLayout(false);
      this.groupBox26.ResumeLayout(false);
      this.groupBox26.PerformLayout();
      this.groupBox30.ResumeLayout(false);
      this.groupBox30.PerformLayout();
      this.groupBox25.ResumeLayout(false);
      this.groupBox25.PerformLayout();
      this.groupBox28.ResumeLayout(false);
      this.groupBox28.PerformLayout();
      ((ISupportInitialize) this.pictureBox6).EndInit();
      ((ISupportInitialize) this.pictureBox7).EndInit();
      ((ISupportInitialize) this.pictureBox8).EndInit();
      ((ISupportInitialize) this.pictureBox9).EndInit();
      ((ISupportInitialize) this.pictureBox10).EndInit();
      ((ISupportInitialize) this.pictureBox11).EndInit();
      this.groupBox27.ResumeLayout(false);
      this.groupBox27.PerformLayout();
      this.groupBox23.ResumeLayout(false);
      this.groupBox23.PerformLayout();
      ((ISupportInitialize) this.pictureBox5).EndInit();
      ((ISupportInitialize) this.pictureBox4).EndInit();
      this.groupBox7.ResumeLayout(false);
      this.groupBox22.ResumeLayout(false);
      this.groupBox22.PerformLayout();
      ((ISupportInitialize) this.pictureBox1).EndInit();
      this.groupBox21.ResumeLayout(false);
      this.groupBox21.PerformLayout();
      this.groupBox8.ResumeLayout(false);
      this.groupBox8.PerformLayout();
      this.groupBox11.ResumeLayout(false);
      this.groupBox11.PerformLayout();
      this.groupBox10.ResumeLayout(false);
      this.groupBox10.PerformLayout();
      this.groupBox9.ResumeLayout(false);
      this.groupBox9.PerformLayout();
      this.groupBox6.ResumeLayout(false);
      this.groupBox6.PerformLayout();
      ((ISupportInitialize) this.pictureBox3).EndInit();
      ((ISupportInitialize) this.pictureBox2).EndInit();
      this.groupBox4.ResumeLayout(false);
      this.groupBox4.PerformLayout();
      this.groupBox2.ResumeLayout(false);
      this.groupBox2.PerformLayout();
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.tabPage3.ResumeLayout(false);
      this.groupBox12.ResumeLayout(false);
      this.groupBox20.ResumeLayout(false);
      this.groupBox20.PerformLayout();
      this.groupBox19.ResumeLayout(false);
      this.groupBox19.PerformLayout();
      this.groupBox18.ResumeLayout(false);
      this.groupBox18.PerformLayout();
      this.groupBox17.ResumeLayout(false);
      this.groupBox17.PerformLayout();
      this.groupBox16.ResumeLayout(false);
      this.groupBox16.PerformLayout();
      this.groupBox15.ResumeLayout(false);
      this.groupBox15.PerformLayout();
      this.groupBox14.ResumeLayout(false);
      this.groupBox14.PerformLayout();
      this.groupBox13.ResumeLayout(false);
      this.groupBox13.PerformLayout();
      this.tabPage2.ResumeLayout(false);
      this.tabPage2.PerformLayout();
      this.tabPage4.ResumeLayout(false);
      this.tabPage4.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
