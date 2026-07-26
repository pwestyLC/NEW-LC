// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MobEditor
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using MySqlConnector;
using SlimDX;
using SlimDX.Direct3D9;
using StringExporter;
using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools
{
  public class MobEditor : Form
  {
    public static Connection connection = new Connection();
    private string Host = MobEditor.connection.Settings.SqlHost;
    private string User = MobEditor.connection.Settings.SqlUser;
    private string Password = MobEditor.connection.Settings.SqlPassword;
    private string Database = MobEditor.connection.Settings.SqlDatabase;
    private string language = MobEditor.connection.Settings.Language;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    private ExportLodHandle exportLodHandle = new ExportLodHandle();
    public List<string> MenuList = new List<string>();
    public List<string> MenuListSearch = new List<string>();
    public string rowName = nameof (a_index);
    public string[] menuArray = new string[2]
    {
      nameof (a_index),
      "a_name"
    };
    public string[] menuArrayGER = new string[2]
    {
      nameof (a_index),
      "a_name_ger"
    };
    public string[] menuArrayPOL = new string[2]
    {
      nameof (a_index),
      "a_name_pld"
    };
    public string[] menuArrayBRA = new string[2]
    {
      nameof (a_index),
      "a_name_brz"
    };
    public string[] menuArrayRUS = new string[2]
    {
      nameof (a_index),
      "a_name_rus"
    };
    public string[] menuArrayFRA = new string[2]
    {
      nameof (a_index),
      "a_name_frc"
    };
    public string[] menuArrayESP = new string[2]
    {
      nameof (a_index),
      "a_name_spn"
    };
    public string[] menuArrayMEX = new string[2]
    {
      nameof (a_index),
      "a_name_mex"
    };
    public string[] menuArrayTHA = new string[2]
    {
      nameof (a_index),
      "a_name_thai"
    };
    public string[] menuArrayITA = new string[2]
    {
      nameof (a_index),
      "a_name_ita"
    };
    public string[] menuArrayUSA = new string[2]
    {
      nameof (a_index),
      "a_name_usa"
    };
    public string adescr = "";
    public string aname = "";
    public float _UpDown = -1f;
    private ASCIIEncoding _Enc = new ASCIIEncoding();
    public string _ClientPath = MobEditor.connection.Settings.ClientPath;
    private IContainer components = (IContainer) null;
    private string namee;
    private Label label42;
    private Label lblLang;
    private CheckBox cbEnabled;
    private Button btnSaveAndNext;
    private Button BtnClearDrop;
    public string descrr;
    public string name;
    public int index;
    public Direct3D _Direct3D;
    public Device _Device;
    public float _Zoom;
    public float _LeftRight;
    public float _Rotation;
    public List<tMesh> _Models;
    private MenuStrip menuStrip1;
    private GroupBox groupBox3;
    private Button button3;
    private Button button1;
    private ListBox listBox1;
    private GroupBox groupBox5;
    private Label label7;
    private TabControl tabControl1;
    private TabPage tabPage1;
    private TabPage tabPage2;
    private Button button2;
    private ToolStripMenuItem exportMobAlllodToolStripMenuItem;
    private GroupBox groupBox1;
    private Label label3;
    private Label label2;
    private Label label5;
    private TextBox textBox200;
    private TextBox textBox3;
    private TextBox textBox2;
    private TextBox textBox4;
    private TextBox textBox5;
    private Label label4;
    private TextBox textBox6;
    private Label label6;
    private TextBox textBox7;
    private Label label8;
    private Label label9;
    private TextBox textBox9;
    private TextBox textBox8;
    private Label label10;
    private TextBox textBox10;
    private Label label11;
    private TextBox textBox14;
    private Label label15;
    private TextBox textBox16;
    private Label label17;
    private GroupBox groupBox7;
    private TextBox textBox22;
    private Label label23;
    private TextBox textBox19;
    private Label label22;
    private TextBox textBox20;
    private Label label21;
    private TextBox textBox21;
    private Label label20;
    private GroupBox groupBox8;
    private TextBox textBox24;
    private Label label25;
    private TextBox textBox23;
    private Label label24;
    private GroupBox groupBox9;
    private Label label27;
    private Label label26;
    private TextBox textBox25;
    private TextBox textBox26;
    private Label label28;
    private TextBox textBox27;
    private Label label29;
    private TextBox textBox28;
    private TextBox textBox29;
    private Label label31;
    private TextBox textBox30;
    private Label label30;
    private TextBox textBox31;
    private ComboBox comboBox1;
    private TextBox textBox32;
    private Label label32;
    private Label label33;
    private GroupBox groupBox10;
    private TextBox textBox34;
    private Label label35;
    private TextBox textBox33;
    private Label label34;
    private TextBox textBox35;
    private Label label37;
    private TextBox textBox36;
    private Label label36;
    private TextBox textBox1;
    private Label label1;
    private GroupBox groupBox2;
    private Label label41;
    private Label label40;
    private Label label39;
    private Label label38;
    private TextBox textBox40;
    private TextBox textBox37;
    private TextBox textBox39;
    private TextBox textBox38;
    private TabPage tabPage4;
    private TextBox textBox60;
    private TextBox textBox59;
    private TextBox textBox58;
    private TextBox textBox57;
    private TextBox textBox56;
    private TextBox textBox55;
    private TextBox textBox54;
    private TextBox textBox53;
    private TextBox textBox52;
    private TextBox textBox51;
    private TextBox textBox50;
    private TextBox textBox49;
    private TextBox textBox48;
    private TextBox textBox47;
    private TextBox textBox46;
    private TextBox textBox45;
    private TextBox textBox44;
    private TextBox textBox43;
    private TextBox textBox42;
    private TextBox textBox41;
    private TextBox textBox61;
    private TextBox textBox78;
    private TextBox textBox77;
    private TextBox textBox76;
    private TextBox textBox75;
    private TextBox textBox74;
    private TextBox textBox73;
    private TextBox textBox72;
    private TextBox textBox71;
    private TextBox textBox70;
    private TextBox textBox69;
    private TextBox textBox68;
    private TextBox textBox67;
    private TextBox textBox66;
    private TextBox textBox65;
    private TextBox textBox64;
    private TextBox textBox63;
    private TextBox textBox62;
    private TextBox textBox80;
    private TextBox textBox79;
    private TextBox textBox81;
    private TextBox textBox82;
    private GroupBox groupBox11;
    private Label label46;
    private Label label45;
    private Label label44;
    private TextBox textBox83;
    private GroupBox groupBox12;
    private Label label51;
    private Label label50;
    private Label label49;
    private Label label48;
    private Label label47;
    private TextBox textBox88;
    private TextBox textBox84;
    private TextBox textBox87;
    private TextBox textBox85;
    private TextBox textBox86;
    private Label label52;
    private TextBox textBox89;
    private GroupBox groupBox13;
    private Label label53;
    private TextBox textBox97;
    private TextBox textBox96;
    private TextBox textBox95;
    private TextBox textBox94;
    private TextBox textBox93;
    private TextBox textBox92;
    private TextBox textBox91;
    private TextBox textBox90;
    private Label label54;
    private Label label55;
    private Label label57;
    private Label label56;
    private Label label58;
    private Label label59;
    private Label label60;
    private TextBox textBox98;
    private Label label61;
    private GroupBox groupBox16;
    private Label label73;
    private ComboBox comboBox2;
    private TextBox textBox110;
    private Label label75;
    private TextBox textBox112;
    private Label label74;
    private TextBox textBox111;
    private TextBox textBox114;
    private Label label76;
    private TextBox textBox113;
    private TextBox textBox115;
    private Label label78;
    private Label label77;
    private TabPage tabPage6;
    private TextBox textBox117;
    private TextBox textBox116;
    private Label label80;
    private Label label79;
    private TextBox textBox118;
    private Label label81;
    private Label label82;
    private TextBox textBox119;
    private TextBox textBox121;
    private Label label83;
    private TextBox textBox120;
    private Label label84;
    private Label label85;
    private TextBox textBox123;
    private TextBox textBox122;
    private Label label86;
    private Label label88;
    private TextBox textBox125;
    private TextBox textBox124;
    private Label label87;
    private Label label89;
    private TextBox textBox126;
    private Label label93;
    private TextBox textBox130;
    private Label label92;
    private TextBox textBox129;
    private Label label91;
    private TextBox textBox128;
    private Label label90;
    private TextBox textBox127;
    private TabPage tabPage7;
    private TextBox textBox141;
    private TextBox textBox140;
    private TextBox textBox139;
    private TextBox textBox138;
    private TextBox textBox137;
    private TextBox textBox136;
    private TextBox textBox135;
    private TextBox textBox134;
    private TextBox textBox133;
    private TextBox textBox132;
    private TextBox textBox131;
    private TextBox textBox150;
    private TextBox textBox149;
    private TextBox textBox148;
    private TextBox textBox147;
    private TextBox textBox146;
    private TextBox textBox145;
    private TextBox textBox144;
    private TextBox textBox143;
    private TextBox textBox142;
    private TextBox textBox170;
    private TextBox textBox169;
    private TextBox textBox168;
    private TextBox textBox167;
    private TextBox textBox166;
    private TextBox textBox165;
    private TextBox textBox164;
    private TextBox textBox163;
    private TextBox textBox162;
    private TextBox textBox161;
    private TextBox textBox160;
    private TextBox textBox159;
    private TextBox textBox158;
    private TextBox textBox157;
    private TextBox textBox156;
    private TextBox textBox155;
    private TextBox textBox154;
    private TextBox textBox153;
    private TextBox textBox152;
    private TextBox textBox151;
    private GroupBox groupBox17;
    private TextBox textBox174;
    private TextBox textBox173;
    private Label label137;
    private Label label136;
    private TextBox textBox176;
    private Label label139;
    private TextBox textBox175;
    private Label label138;
    private TextBox textBox172;
    private Label label135;
    private TextBox textBox171;
    private Label label134;
    private GroupBox groupBox6;
    private Label label16;
    private TextBox textBox15;
    private Label label14;
    private TextBox textBox13;
    private GroupBox groupBox4;
    private Label label18;
    private Label label13;
    private TextBox textBox11;
    private TextBox textBox17;
    private Label label12;
    private TextBox textBox12;
    private Label label62;
    private TextBox textBox99;
    private Label label19;
    private TextBox textBox18;
    private ToolStripMenuItem exportMobAlllodToolStripMenuItem1;
    private ToolStripMenuItem strNpcNamelodToolStripMenuItem;
    private GroupBox groupBox18;
    private DataGridView dataGridView1;
    private GroupBox groupBox19;
    private DataGridViewImageColumn Column5;
    private DataGridViewTextBoxColumn Column6;
    private DataGridViewTextBoxColumn Column7;
    private DataGridViewTextBoxColumn Column8;
    private DataGridView dataGridView2;
    private DataGridViewTextBoxColumn Column4;
    private DataGridViewTextBoxColumn Column3;
    private DataGridViewTextBoxColumn Column2;
    private DataGridViewImageColumn Column1;
    private PictureBox pictureBox23;
    private PictureBox pictureBox1;
    private GroupBox groupBox15;
    private Label label70;
    private Label label69;
    private TextBox textBox107;
    private TextBox textBox106;
    private TextBox textBox105;
    private Label label68;
    private GroupBox groupBox14;
    private Label label72;
    private TextBox textBox109;
    private Label label71;
    private TextBox textBox108;
    private TextBox textBox104;
    private TextBox textBox103;
    private TextBox textBox102;
    private TextBox textBox101;
    private TextBox textBox100;
    private Label label67;
    private Label label63;
    private Label label66;
    private Label label64;
    private Label label65;
    private GroupBox groupBox20;
    private CheckBox chk3D;
    private TrackBar slideLeftRight;
    private TrackBar slideUpDown;
    private TrackBar slideZoom;
    private Panel panel3DView;
    private BackgroundWorker backgroundWorker1;
    private Timer timer1;
    private TabPage tabPage3;
    private TabPage tabPage5;
    private TabPage tabPage8;
    private Button BtnAniAttack2;
    private Button btnAniIdle2;
    private Button btnAniRun;
    private Button btnAniDie;
    private Button BtnAniAttack1;
    private Button BtnAniDam;
    private Button BtnAniWalk;
    private Button BtnAniIdle;
    private Button BtnReadSmc;
    private ToolStripMenuItem mYSQLToolStripMenuItem;
    private ToolStripMenuItem massEditToolStripMenuItem;
    private TabPage tabPage9;
    private CheckedListBox clbExtra;
    private TextBox tbExtraFlag;
    private TextBox tbZoneFlag;
    private Label label43;
    private Label label94;
    private CheckedListBox clbZone;
    private ToolStripMenuItem exportZoneFlaglodToolStripMenuItem;
    private DataGridView dgRaidItems;
    private GroupBox groupBox22;
    private GroupBox groupBox21;
    private Label label95;
    private TextBox textBox178;
    private TextBox textBox177;
    private Label label96;
    private TextBox textBox180;
    private Label label98;
    private TextBox textBox179;
    private Label label97;
    private TextBox textBox183;
    private Label label101;
    private TextBox textBox182;
    private Label label100;
    private TextBox textBox181;
    private Label label99;
    private PictureBox pictureBox7;
    private Button button5;
    private Button button18;
    private Button button19;
    private Button button6;
    private Button button17;
    private Button button7;
    private PictureBox pictureBox2;
    private TextBox textBox184;
    private Label label102;
    private TextBox textBox185;
    private Label label103;
    private Button button14;
    private PictureBox pictureBox10;
    private TextBox textBox198;
    private Label label116;
    private TextBox textBox199;
    private Label label117;
    private Button button13;
    private PictureBox pictureBox9;
    private TextBox textBox196;
    private Label label114;
    private TextBox textBox197;
    private Label label115;
    private Button button12;
    private PictureBox pictureBox8;
    private TextBox textBox194;
    private Label label112;
    private TextBox textBox195;
    private Label label113;
    private Button button11;
    private PictureBox pictureBox6;
    private TextBox textBox192;
    private Label label110;
    private TextBox textBox193;
    private Label label111;
    private Button button10;
    private PictureBox pictureBox5;
    private TextBox textBox190;
    private Label label108;
    private TextBox textBox191;
    private Label label109;
    private Button button9;
    private PictureBox pictureBox4;
    private TextBox textBox188;
    private Label label106;
    private TextBox textBox189;
    private Label label107;
    private Button button8;
    private PictureBox pictureBox3;
    private TextBox textBox186;
    private Label label104;
    private TextBox textBox187;
    private Label label105;
    private Button button15;
    private PictureBox pictureBox11;
    private TextBox textBox201;
    private Label label118;
    private TextBox textBox202;
    private Label label119;
    private Button button23;
    private PictureBox pictureBox16;
    private TextBox textBox211;
    private Label label128;
    private TextBox textBox212;
    private Label label129;
    private Button button22;
    private PictureBox pictureBox15;
    private TextBox textBox209;
    private Label label126;
    private TextBox textBox210;
    private Label label127;
    private Button button21;
    private PictureBox pictureBox14;
    private TextBox textBox207;
    private Label label124;
    private TextBox textBox208;
    private Label label125;
    private Button button20;
    private PictureBox pictureBox13;
    private TextBox textBox205;
    private Label label122;
    private TextBox textBox206;
    private Label label123;
    private Button button16;
    private PictureBox pictureBox12;
    private TextBox textBox203;
    private Label label120;
    private TextBox textBox204;
    private Label label121;
    private TextBox textBox214;
    private Label label131;
    private TextBox textBox213;
    private Label label130;
    private TextBox textBox217;
    private Label label140;
    private TextBox textBox216;
    private Label label133;
    private TextBox textBox215;
    private Label label132;
    private DataGridViewImageColumn Icon;
    private DataGridViewTextBoxColumn a_index;
    private DataGridViewTextBoxColumn a_npc_index;
    private DataGridViewTextBoxColumn a_item_index;
    private DataGridViewTextBoxColumn ItemName;
    private DataGridViewTextBoxColumn a_count;
    private DataGridViewTextBoxColumn a_prob;
    private DataGridViewTextBoxColumn a_flag;
    private DataGridViewTextBoxColumn a_spec_item_index1;
    private DataGridViewTextBoxColumn a_spec_item_index2;
    private DataGridViewTextBoxColumn a_spec_item_index3;
    private DataGridViewTextBoxColumn a_spec_item_index4;
    private DataGridViewTextBoxColumn a_spec_item_index5;
    private DataGridViewTextBoxColumn a_spec_item_index6;
    private DataGridViewTextBoxColumn a_spec_item_index7;
    private DataGridViewTextBoxColumn a_spec_item_index8;
    private DataGridViewTextBoxColumn a_spec_item_index9;
    private DataGridViewTextBoxColumn a_spec_item_index10;
    private DataGridViewTextBoxColumn a_spec_item_index11;
    private DataGridViewTextBoxColumn a_spec_item_index12;
    private DataGridViewTextBoxColumn a_spec_item_index13;
    private DataGridViewTextBoxColumn a_spec_item_index14;
    private DataGridViewTextBoxColumn a_spec_min;
    private DataGridViewTextBoxColumn a_spec_max;
    private DataGridViewTextBoxColumn a_spec_count;
    private DataGridViewTextBoxColumn a_spec_prob;
    private DataGridViewTextBoxColumn a_spec_flag;
    private TextBox textBox221;
    private TextBox textBox220;
    private TextBox textBox219;
    private TextBox textBox218;
    private Button button24;
    private DataGridView dgDropAllItems;
    private GroupBox groupBox23;
    private Button button25;
    private PictureBox pictureBox17;
    private TextBox textBox222;
    private Label label141;
    private Label label144;
    private TextBox textBox226;
    private Label label145;
    private Label label143;
    private TextBox textBox224;
    private Button button27;
    private Button button28;
    private TextBox textBox223;
    private Label label142;
    private Label label146;
    private DataGridViewImageColumn IconRaid;
    private DataGridViewTextBoxColumn a_npc_idx;
    private DataGridViewTextBoxColumn a_item_idx;
    private DataGridViewTextBoxColumn name_raid;
    private DataGridViewTextBoxColumn a_prob_raid;
    private DataGridViewTextBoxColumn Count;
    private GroupBox groupBox31;
    private TextBox textBox245;
    private Label label177;
    private Label label178;
    private TextBox textBox246;
    private Label label179;
    private Label label180;
    private Label label181;
    private Button button34;
    private TextBox textBox247;
    private PictureBox pictureBox25;
    private GroupBox groupBox30;
    private TextBox textBox242;
    private Label label172;
    private Label label173;
    private TextBox textBox243;
    private Label label174;
    private Label label175;
    private Label label176;
    private Button button33;
    private TextBox textBox244;
    private PictureBox pictureBox24;
    private GroupBox groupBox29;
    private TextBox textBox239;
    private Label label167;
    private Label label168;
    private TextBox textBox240;
    private Label label169;
    private Label label170;
    private Label label171;
    private Button button32;
    private TextBox textBox241;
    private PictureBox pictureBox22;
    private GroupBox groupBox28;
    private TextBox textBox236;
    private Label label162;
    private Label label163;
    private TextBox textBox237;
    private Label label164;
    private Label label165;
    private Label label166;
    private Button button31;
    private TextBox textBox238;
    private PictureBox pictureBox21;
    private GroupBox groupBox27;
    private TextBox textBox233;
    private Label label157;
    private Label label158;
    private TextBox textBox234;
    private Label label159;
    private Label label160;
    private Label label161;
    private Button button30;
    private TextBox textBox235;
    private PictureBox pictureBox20;
    private GroupBox groupBox26;
    private TextBox textBox230;
    private Label label152;
    private Label label153;
    private TextBox textBox231;
    private Label label154;
    private Label label155;
    private Label label156;
    private Button button29;
    private TextBox textBox232;
    private PictureBox pictureBox19;
    private GroupBox groupBox25;
    private TextBox textBox227;
    private Label label147;
    private Label label148;
    private TextBox textBox228;
    private Label label149;
    private Label label150;
    private Label label151;
    private Button button26;
    private TextBox textBox229;
    private PictureBox pictureBox18;
    private GroupBox groupBox24;
    private GroupBox groupBox32;
    private TextBox textBox248;
    private Label label182;
    private Label label183;
    private TextBox textBox249;
    private Label label184;
    private Label label185;
    private Label label186;
    private Button button35;
    private TextBox textBox250;
    private PictureBox pictureBox26;
    private GroupBox groupBox35;
    private TextBox textBox257;
    private Label label197;
    private Label label198;
    private TextBox textBox258;
    private Label label199;
    private Label label200;
    private Label label201;
    private Button button38;
    private TextBox textBox259;
    private PictureBox pictureBox29;
    private GroupBox groupBox36;
    private TextBox textBox260;
    private Label label202;
    private Label label203;
    private TextBox textBox261;
    private Label label204;
    private Label label205;
    private Label label206;
    private Button button39;
    private TextBox textBox262;
    private PictureBox pictureBox30;
    private GroupBox groupBox37;
    private TextBox textBox263;
    private Label label207;
    private Label label208;
    private TextBox textBox264;
    private Label label209;
    private Label label210;
    private Label label211;
    private Button button40;
    private TextBox textBox265;
    private PictureBox pictureBox31;
    private GroupBox groupBox38;
    private TextBox textBox266;
    private Label label212;
    private Label label213;
    private TextBox textBox267;
    private Label label214;
    private Label label215;
    private Label label216;
    private Button button41;
    private TextBox textBox268;
    private PictureBox pictureBox32;
    private GroupBox groupBox39;
    private TextBox textBox269;
    private Label label217;
    private Label label218;
    private TextBox textBox270;
    private Label label219;
    private Label label220;
    private Label label221;
    private Button button42;
    private TextBox textBox271;
    private PictureBox pictureBox33;
    private GroupBox groupBox40;
    private TextBox textBox272;
    private Label label222;
    private Label label223;
    private TextBox textBox273;
    private Label label224;
    private Label label225;
    private Label label226;
    private Button button43;
    private TextBox textBox274;
    private PictureBox pictureBox34;
    private GroupBox groupBox41;
    private TextBox textBox275;
    private Label label227;
    private Label label228;
    private TextBox textBox276;
    private Label label229;
    private Label label230;
    private Label label231;
    private Button button44;
    private TextBox textBox277;
    private PictureBox pictureBox35;
    private GroupBox groupBox33;
    private TextBox textBox225;
    private Label label187;
    private Label label188;
    private TextBox textBox251;
    private Label label189;
    private Label label190;
    private Label label191;
    private Button button36;
    private TextBox textBox252;
    private PictureBox pictureBox27;
    private Label label192;
    private Label label193;
    private ToolStripMenuItem exportDropNpclodToolStripMenuItem;
    private Button button4;

    private void IniRead()
    {
      IniFile iniFile = new IniFile(Application.StartupPath + "\\Config\\Settings.cfg");
      this.textBox218.Text = iniFile.IniReadValue("## MYSQL", "SQL_HOST");
      this.textBox219.Text = iniFile.IniReadValue("## MYSQL", "SQL_USER");
      this.textBox220.Text = iniFile.IniReadValue("## MYSQL", "SQL_PASSWORD");
      this.textBox221.Text = iniFile.IniReadValue("## MYSQL", "SQL_DATABASE");
    }

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

    public string DescrFromLanguage()
    {
      if (this.language == "GER")
      {
        this.descrr = "a_descr_ger";
        return this.descrr;
      }
      if (this.language == "POL")
      {
        this.descrr = "a_descr_pld";
        return this.descrr;
      }
      if (this.language == "BRA")
      {
        this.descrr = "a_descr_brz";
        return this.descrr;
      }
      if (this.language == "RUS")
      {
        this.descrr = "a_descr_rus";
        return this.descrr;
      }
      if (this.language == "FRA")
      {
        this.descrr = "a_descr_frc";
        return this.descrr;
      }
      if (this.language == "ESP")
      {
        this.descrr = "a_descr_spn";
        return this.descrr;
      }
      if (this.language == "MEX")
      {
        this.descrr = "a_descr_mex";
        return this.descrr;
      }
      if (this.language == "THA")
      {
        this.descrr = "a_descr_thai";
        return this.descrr;
      }
      if (this.language == "ITA")
      {
        this.descrr = "a_descr_ita";
        return this.descrr;
      }
      if (!(this.language == "USA"))
        return (string) null;
      this.descrr = "a_descr_usa";
      return this.descrr;
    }

    public MobEditor() => this.InitializeComponent();

    private void LoadListBox()
    {
      this.listBox1.SelectedIndex = -1;
      this.MenuList.Clear();
      this.namee = this.StringFromLanguage();
      string str = "SELECT a_index, " + this.namee + " FROM t_npc ORDER BY a_index;";
      if (this.language == "GER")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayGER, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_ger from t_npc ORDER BY a_index;");
      else if (this.language == "POL")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayPOL, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_pld from t_npc ORDER BY a_index;");
      else if (this.language == "BRA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayBRA, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_brz from t_npc ORDER BY a_index;");
      else if (this.language == "RUS")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayRUS, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_rus from t_npc ORDER BY a_index;");
      else if (this.language == "FRA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayFRA, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_frc from t_npc ORDER BY a_index;");
      else if (this.language == "ESP")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayESP, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_spn from t_npc ORDER BY a_index;");
      else if (this.language == "MEX")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayMEX, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_mex from t_npc ORDER BY a_index;");
      else if (this.language == "THA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayTHA, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_thai from t_npc ORDER BY a_index;");
      else if (this.language == "ITA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayITA, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_ita from t_npc ORDER BY a_index;");
      else if (this.language == "USA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayUSA, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_usa from t_npc ORDER BY a_index;");
      else
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, "select a_index, a_name from t_npc ORDER BY a_index;");
    }

    private void AniFind(object sender, EventArgs e)
    {
      string str1 = Path.GetDirectoryName(this._ClientPath).Replace("Data", "").Replace("data", "");
      if (File.Exists(str1 + "\\" + this.textBox89.Text))
      {
        foreach (string readAllLine in File.ReadAllLines(str1 + "\\" + this.textBox89.Text))
        {
          if (readAllLine.Contains("ANIMSET"))
          {
            string str2 = str1 + "\\" + readAllLine.Split('"')[1];
            if (File.Exists(str2))
            {
              Animation_Picker animationPicker = (Animation_Picker) null;
              switch ((sender as Button).Name)
              {
                case "BtnAniAttack1":
                  animationPicker = new Animation_Picker(str2, "Attack");
                  break;
                case "BtnAniAttack2":
                  animationPicker = new Animation_Picker(str2, "Attack2");
                  break;
                case "BtnAniDam":
                  animationPicker = new Animation_Picker(str2, "Damage");
                  break;
                case "BtnAniIdle":
                  animationPicker = new Animation_Picker(str2, "Idle");
                  break;
                case "BtnAniWalk":
                  animationPicker = new Animation_Picker(str2, "Walk");
                  break;
                case "btnAniDie":
                  animationPicker = new Animation_Picker(str2, "Die");
                  break;
                case "btnAniIdle2":
                  animationPicker = new Animation_Picker(str2, "Idle2");
                  break;
                case "btnAniRun":
                  animationPicker = new Animation_Picker(str2, "Run");
                  break;
                default:
                  int num = (int) MessageBox.Show("Not found : " + (sender as Button).Name);
                  break;
              }
              if (animationPicker.ShowDialog() == DialogResult.OK)
              {
                switch ((sender as Button).Name)
                {
                  case "BtnAniAttack1":
                    this.textBox93.Text = animationPicker.Animation;
                    continue;
                  case "BtnAniAttack2":
                    this.textBox97.Text = animationPicker.Animation;
                    continue;
                  case "BtnAniDam":
                    this.textBox92.Text = animationPicker.Animation;
                    continue;
                  case "BtnAniIdle":
                    this.textBox91.Text = animationPicker.Animation;
                    continue;
                  case "BtnAniWalk":
                    this.textBox90.Text = animationPicker.Animation;
                    continue;
                  case "btnAniDie":
                    this.textBox94.Text = animationPicker.Animation;
                    continue;
                  case "btnAniIdle2":
                    this.textBox96.Text = animationPicker.Animation;
                    continue;
                  case "btnAniRun":
                    this.textBox95.Text = animationPicker.Animation;
                    continue;
                  default:
                    continue;
                }
              }
            }
            else
            {
              int num1 = (int) new CustomMessage("Not Found :" + str2).ShowDialog();
            }
          }
        }
      }
      else
        new CustomMessage("SMC File not found").Show();
    }

    public void SearchList(string searchString)
    {
      searchString = searchString.Replace("\\", "\\\\").Replace("'", "\\'");
      string lower = searchString.ToLower();
      string upper = searchString.ToUpper();
      string str = "";
            string query =
        "SELECT a_index, a_name_thai FROM t_npc " +
        "WHERE a_name_thai LIKE @search " +
        "OR a_index LIKE @search " +
        "OR a_name_thai LIKE @lower " +
        "OR a_index LIKE @lower " +
        "OR a_name_thai LIKE @upper " +
        "OR a_index LIKE @upper " +
        "OR a_name_thai LIKE @str " +
        "OR a_index LIKE @str " +
        "ORDER BY a_index;";
            if (searchString.Length > 1)
        str = char.ToUpper(searchString[0]).ToString() + searchString.Substring(1);
      if (this.language == "GER")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayGER, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_ger from t_npc WHERE a_name_ger LIKE '%" + searchString + "%' OR a_index LIKE '%" + searchString + "%' OR a_name_ger LIKE '%" + lower + "%' OR a_index  LIKE '%" + lower + "%' OR a_name_ger LIKE '%" + upper + "%' OR a_index LIKE '%" + upper + "%' OR a_name_ger LIKE '%" + str + "%' OR a_index LIKE '%" + str + "%' ORDER BY a_index;");
      else if (this.language == "POL")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayPOL, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_pld from t_npc WHERE a_name_pld LIKE '%" + searchString + "%' OR a_index LIKE '%" + searchString + "%' OR a_name_pld LIKE '%" + lower + "%' OR a_index  LIKE '%" + lower + "%' OR a_name_pld LIKE '%" + upper + "%' OR a_index LIKE '%" + upper + "%' OR a_name_pld LIKE '%" + str + "%' OR a_index LIKE '%" + str + "%' ORDER BY a_index;");
      else if (this.language == "BRA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayBRA, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_brz from t_npc WHERE a_name_brz LIKE '%" + searchString + "%' OR a_index LIKE '%" + searchString + "%' OR a_name_brz LIKE '%" + lower + "%' OR a_index  LIKE '%" + lower + "%' OR a_name_brz LIKE '%" + upper + "%' OR a_index LIKE '%" + upper + "%' OR a_name_brz LIKE '%" + str + "%' OR a_index LIKE '%" + str + "%' ORDER BY a_index;");
      else if (this.language == "RUS")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayRUS, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_rus from t_npc WHERE a_name_rus LIKE '%" + searchString + "%' OR a_index LIKE '%" + searchString + "%' OR a_name_rus LIKE '%" + lower + "%' OR a_index  LIKE '%" + lower + "%' OR a_name_rus LIKE '%" + upper + "%' OR a_index LIKE '%" + upper + "%' OR a_name_rus LIKE '%" + str + "%' OR a_index LIKE '%" + str + "%' ORDER BY a_index;");
      else if (this.language == "FRA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayFRA, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_frc from t_npc WHERE a_name_frc LIKE '%" + searchString + "%' OR a_index LIKE '%" + searchString + "%' OR a_name_frc LIKE '%" + lower + "%' OR a_index  LIKE '%" + lower + "%' OR a_name_frc LIKE '%" + upper + "%' OR a_index LIKE '%" + upper + "%' OR a_name_frc LIKE '%" + str + "%' OR a_index LIKE '%" + str + "%' ORDER BY a_index;");
      else if (this.language == "ESP")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayESP, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_spn from t_npc WHERE a_name_spn LIKE '%" + searchString + "%' OR a_index LIKE '%" + searchString + "%' OR a_name_spn LIKE '%" + lower + "%' OR a_index  LIKE '%" + lower + "%' OR a_name_spn LIKE '%" + upper + "%' OR a_index LIKE '%" + upper + "%' OR a_name_spn LIKE '%" + str + "%' OR a_index LIKE '%" + str + "%' ORDER BY a_index;");
      else if (this.language == "MEX")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayMEX, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_mex from t_npc WHERE a_name_mex LIKE '%" + searchString + "%' OR a_index LIKE '%" + searchString + "%' OR a_name_mex LIKE '%" + lower + "%' OR a_index  LIKE '%" + lower + "%' OR a_name_mex LIKE '%" + upper + "%' OR a_index LIKE '%" + upper + "%' OR a_name_mex LIKE '%" + str + "%' OR a_index LIKE '%" + str + "%' ORDER BY a_index;");
      else if (this.language == "THA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayTHA, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_thai from t_npc WHERE a_name_thai LIKE '%" + searchString + "%' OR a_index LIKE '%" + searchString + "%' OR a_name_thai LIKE '%" + lower + "%' OR a_index  LIKE '%" + lower + "%' OR a_name_thai LIKE '%" + upper + "%' OR a_index LIKE '%" + upper + "%' OR a_name_thai LIKE '%" + str + "%' OR a_index LIKE '%" + str + "%' ORDER BY a_index;");
      else if (this.language == "ITA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayITA, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_ita from t_npc WHERE a_name_ita LIKE '%" + searchString + "%' OR a_index LIKE '%" + searchString + "%' OR a_name_ita LIKE '%" + lower + "%' OR a_index  LIKE '%" + lower + "%' OR a_name_ita LIKE '%" + upper + "%' OR a_index LIKE '%" + upper + "%' OR a_name_ita LIKE '%" + str + "%' OR a_index LIKE '%" + str + "%' ORDER BY a_index;");
      else if (this.language == "USA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayUSA, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_usa from t_npc WHERE a_name_usa LIKE '%" + searchString + "%' OR a_index LIKE '%" + searchString + "%' OR a_name_usa LIKE '%" + lower + "%' OR a_index  LIKE '%" + lower + "%' OR a_name_usa LIKE '%" + upper + "%' OR a_index LIKE '%" + upper + "%' OR a_name_usa LIKE '%" + str + "%' OR a_index LIKE '%" + str + "%' ORDER BY a_index;");
      else
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, "select a_index, a_name from t_npc WHERE a_name LIKE '%" + searchString + "%' OR a_index LIKE '%" + searchString + "%' OR a_name LIKE '%" + lower + "%' OR a_index  LIKE '%" + lower + "%' OR a_name LIKE '%" + upper + "%' OR a_index LIKE '%" + upper + "%' OR a_name LIKE '%" + str + "%' OR a_index LIKE '%" + str + "%' ORDER BY a_index;");
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

    public int GetItemIndex()
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

    private int GetID()
    {
      int result = -1;
      int.TryParse(this.textBox1.Text.Split(' ')[0], out result);
      return result;
    }

    private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (this.listBox1.SelectedIndex != -1)
        this.textBox1.Text = this.GetIndex().ToString();
      string Query = " select a_index , a_enable , a_name , a_descr , a_level , a_family , a_skillmaster , a_flag , a_flag1 , a_state_flag , a_exp , a_prize , a_sight , a_size , a_move_area , a_attack_area , a_skill_point , a_sskill_master , a_str , a_dex , a_int , a_con , a_attack , a_magic , a_defense , a_resist , a_attacklevel , a_defenselevel , a_hp , a_mp , a_attackType , a_attackSpeed , a_recover_hp , a_recover_mp , a_walk_speed , a_run_speed , a_skill0 , a_skill1 , a_skill2 , a_skill3 , a_item_0 , a_item_1 , a_item_2 , a_item_3 , a_item_4 , a_item_5 , a_item_6 , a_item_7 , a_item_8 , a_item_9 , a_item_10 , a_item_11 , a_item_12 , a_item_13 , a_item_14 , a_item_15 , a_item_16 , a_item_17 , a_item_18 , a_item_19 , a_item_percent_0 , a_item_percent_1 , a_item_percent_2 , a_item_percent_3 , a_item_percent_4 , a_item_percent_5 , a_item_percent_6 , a_item_percent_7 , a_item_percent_8 , a_item_percent_9 , a_item_percent_10 , a_item_percent_11 , a_item_percent_12 , a_item_percent_13 , a_item_percent_14 , a_item_percent_15 , a_item_percent_16 , a_item_percent_17 , a_item_percent_18 , a_item_percent_19 , a_minplus , a_maxplus , a_probplus , a_product0 , a_product1 , a_product2 , a_product3 , a_product4 , a_file_smc , a_motion_walk , a_motion_idle , a_motion_dam , a_motion_attack , a_motion_die , a_motion_run , a_motion_idle2 , a_motion_attack2 , a_scale , a_attribute , a_fireDelayCount , a_fireDelay0 , a_fireDelay1 , a_fireDelay2 , a_fireDelay3 , a_fireEffect0 , a_fireEffect1 , a_fireEffect2 , a_fireObject , a_fireSpeed , a_aitype , a_aiflag , a_aileader_flag , a_ai_summonHp , a_aileader_idx , a_aileader_count , a_crafting_category , a_productIndex , a_hit , a_dodge, a_magicavoid , a_job_attribute , a_npc_choice_trigger_count , a_npc_choice_trigger_ids , a_npc_kill_trigger_count , a_npc_kill_trigger_ids , a_createprob , a_socketprob_0 , a_socketprob_1 , a_socketprob_2 , a_socketprob_3 , a_jewel_0 , a_jewel_1 , a_jewel_2 , a_jewel_3 , a_jewel_4 , a_jewel_5 , a_jewel_6 , a_jewel_7 , a_jewel_8 , a_jewel_9 , a_jewel_10 , a_jewel_11 , a_jewel_12 , a_jewel_13 , a_jewel_14 , a_jewel_15 , a_jewel_16 , a_jewel_17 , a_jewel_18 , a_jewel_19 , a_jewel_percent_0 , a_jewel_percent_1 , a_jewel_percent_2 , a_jewel_percent_3 , a_jewel_percent_4 , a_jewel_percent_5 , a_jewel_percent_6 , a_jewel_percent_7 , a_jewel_percent_8 , a_jewel_percent_9 , a_jewel_percent_10 , a_jewel_percent_11 , a_jewel_percent_12 , a_jewel_percent_13 , a_jewel_percent_14 , a_jewel_percent_15 , a_jewel_percent_16 , a_jewel_percent_17 , a_jewel_percent_18 , a_jewel_percent_19 , a_zone_flag , a_extra_flag , a_rvr_value , a_rvr_grade , a_bound , a_lifetime, a_name_frc, a_name_ita, a_name_usa, a_name_rus,  a_name_thai, a_name_pld, a_name_spn, a_name_brz, a_name_ger, a_descr_frc, a_descr_ita, a_descr_usa, a_descr_rus, a_descr_thai, a_descr_pld, a_descr_spn, a_descr_brz, a_descr_ger, a_name_mex, a_descr_mex  from t_npc WHERE a_index ='" + this.textBox1.Text + "';";
      string[] rows = new string[196]
      {
        "a_index",
        "a_enable",
        "a_name",
        "a_descr",
        "a_level",
        "a_family",
        "a_skillmaster",
        "a_flag",
        "a_flag1",
        "a_state_flag",
        "a_exp",
        "a_prize",
        "a_sight",
        "a_size",
        "a_move_area",
        "a_attack_area",
        "a_skill_point",
        "a_sskill_master",
        "a_str",
        "a_dex",
        "a_int",
        "a_con",
        "a_attack",
        "a_magic",
        "a_defense",
        "a_resist",
        "a_attacklevel",
        "a_defenselevel",
        "a_hp",
        "a_mp",
        "a_attackType",
        "a_attackSpeed",
        "a_recover_hp",
        "a_recover_mp",
        "a_walk_speed",
        "a_run_speed",
        "a_skill0",
        "a_skill1",
        "a_skill2",
        "a_skill3",
        "a_item_0",
        "a_item_1",
        "a_item_2",
        "a_item_3",
        "a_item_4",
        "a_item_5",
        "a_item_6",
        "a_item_7",
        "a_item_8",
        "a_item_9",
        "a_item_10",
        "a_item_11",
        "a_item_12",
        "a_item_13",
        "a_item_14",
        "a_item_15",
        "a_item_16",
        "a_item_17",
        "a_item_18",
        "a_item_19",
        "a_item_percent_0",
        "a_item_percent_1",
        "a_item_percent_2",
        "a_item_percent_3",
        "a_item_percent_4",
        "a_item_percent_5",
        "a_item_percent_6",
        "a_item_percent_7",
        "a_item_percent_8",
        "a_item_percent_9",
        "a_item_percent_10",
        "a_item_percent_11",
        "a_item_percent_12",
        "a_item_percent_13",
        "a_item_percent_14",
        "a_item_percent_15",
        "a_item_percent_16",
        "a_item_percent_17",
        "a_item_percent_18",
        "a_item_percent_19",
        "a_minplus",
        "a_maxplus",
        "a_probplus",
        "a_product0",
        "a_product1",
        "a_product2",
        "a_product3",
        "a_product4",
        "a_file_smc",
        "a_motion_walk",
        "a_motion_idle",
        "a_motion_dam",
        "a_motion_attack",
        "a_motion_die",
        "a_motion_run",
        "a_motion_idle2",
        "a_motion_attack2",
        "a_scale",
        "a_attribute",
        "a_fireDelayCount",
        "a_fireDelay0",
        "a_fireDelay1",
        "a_fireDelay2",
        "a_fireDelay3",
        "a_fireEffect0",
        "a_fireEffect1",
        "a_fireEffect2",
        "a_fireObject",
        "a_fireSpeed",
        "a_aitype",
        "a_aiflag",
        "a_aileader_flag",
        "a_ai_summonHp",
        "a_aileader_idx",
        "a_aileader_count",
        "a_crafting_category",
        "a_productIndex",
        "a_hit",
        "a_dodge",
        "a_magicavoid",
        "a_job_attribute",
        "a_npc_choice_trigger_count",
        "a_npc_choice_trigger_ids",
        "a_npc_kill_trigger_count",
        "a_npc_kill_trigger_ids",
        "a_createprob",
        "a_socketprob_0",
        "a_socketprob_1",
        "a_socketprob_2",
        "a_socketprob_3",
        "a_jewel_0",
        "a_jewel_1",
        "a_jewel_2",
        "a_jewel_3",
        "a_jewel_4",
        "a_jewel_5",
        "a_jewel_6",
        "a_jewel_7",
        "a_jewel_8",
        "a_jewel_9",
        "a_jewel_10",
        "a_jewel_11",
        "a_jewel_12",
        "a_jewel_13",
        "a_jewel_14",
        "a_jewel_15",
        "a_jewel_16",
        "a_jewel_17",
        "a_jewel_18",
        "a_jewel_19",
        "a_jewel_percent_0",
        "a_jewel_percent_1",
        "a_jewel_percent_2",
        "a_jewel_percent_3",
        "a_jewel_percent_4",
        "a_jewel_percent_5",
        "a_jewel_percent_6",
        "a_jewel_percent_7",
        "a_jewel_percent_8",
        "a_jewel_percent_9",
        "a_jewel_percent_10",
        "a_jewel_percent_11",
        "a_jewel_percent_12",
        "a_jewel_percent_13",
        "a_jewel_percent_14",
        "a_jewel_percent_15",
        "a_jewel_percent_16",
        "a_jewel_percent_17",
        "a_jewel_percent_18",
        "a_jewel_percent_19",
        "a_zone_flag",
        "a_extra_flag",
        "a_rvr_value",
        "a_rvr_grade",
        "a_bound",
        "a_lifetime",
        "a_name_frc",
        "a_name_ita",
        "a_name_usa",
        "a_name_rus",
        "a_name_thai",
        "a_name_pld",
        "a_name_spn",
        "a_name_brz",
        "a_name_ger",
        "a_descr_frc",
        "a_descr_ita",
        "a_descr_usa",
        "a_descr_rus",
        "a_descr_thai",
        "a_descr_pld",
        "a_descr_spn",
        "a_descr_brz",
        "a_descr_ger",
        "a_name_mex",
        "a_descr_mex"
      };
      Query.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'");
      string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query, rows);
      if (this.chk3D.Checked && File.Exists(this._ClientPath + strArray[88]))
      {
        Console.WriteLine("Create Model > " + this._ClientPath + strArray[88]);
        this.MakeLCModels(this._ClientPath + strArray[88]);
      }
      this.textBox1.Text = strArray[0];
      this.textBox2.Text = strArray[1];
      if (this.textBox2.Text == "0")
      {
        this.cbEnabled.BackColor = Color.Red;
        this.cbEnabled.Checked = false;
      }
      else if (this.textBox2.Text == "1")
      {
        this.cbEnabled.BackColor = Color.Chartreuse;
        this.cbEnabled.Checked = true;
      }
      if (this.language == "FRA")
      {
        this.textBox3.Text = strArray[176];
        this.textBox4.Text = strArray[185];
      }
      else if (this.language == "USA")
      {
        this.textBox3.Text = strArray[178];
        this.textBox4.Text = strArray[187];
      }
      else if (this.language == "ITA")
      {
        this.textBox3.Text = strArray[177];
        this.textBox4.Text = strArray[186];
      }
      else if (this.language == "RUS")
      {
        this.textBox3.Text = strArray[179];
        this.textBox4.Text = strArray[188];
      }
      else if (this.language == "THA")
      {
        this.textBox3.Text = strArray[180];
        this.textBox4.Text = strArray[189];
      }
      else if (this.language == "POL")
      {
        this.textBox3.Text = strArray[181];
        this.textBox4.Text = strArray[190];
      }
      else if (this.language == "ESP")
      {
        this.textBox3.Text = strArray[182];
        this.textBox4.Text = strArray[191];
      }
      else if (this.language == "BRA")
      {
        this.textBox3.Text = strArray[183];
        this.textBox4.Text = strArray[192];
      }
      else if (this.language == "GER")
      {
        this.textBox3.Text = strArray[184];
        this.textBox4.Text = strArray[193];
      }
      else if (this.language == "MEX")
      {
        this.textBox3.Text = strArray[194];
        this.textBox4.Text = strArray[195];
      }
      else if (this.language != "GER" && this.language != "POL" && this.language != "BRA" && this.language != "RUS" && this.language != "FRA" && this.language != "ESP" && this.language != "MEX" && this.language != "THA" && this.language != "ITA" && this.language != "USA")
      {
        this.textBox3.Text = strArray[2];
        this.textBox4.Text = strArray[3];
      }
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
      this.textBox94.Text = strArray[93];
      this.textBox95.Text = strArray[94];
      this.textBox96.Text = strArray[95];
      this.textBox97.Text = strArray[96];
      this.textBox98.Text = strArray[97];
      this.textBox99.Text = strArray[98];
      this.textBox100.Text = strArray[99];
      this.textBox101.Text = strArray[100];
      this.textBox102.Text = strArray[101];
      this.textBox103.Text = strArray[102];
      this.textBox104.Text = strArray[103];
      this.textBox105.Text = strArray[104];
      this.textBox106.Text = strArray[105];
      this.textBox107.Text = strArray[106];
      this.textBox108.Text = strArray[107];
      this.textBox109.Text = strArray[108];
      this.textBox110.Text = strArray[109];
      this.textBox111.Text = strArray[110];
      this.textBox112.Text = strArray[111];
      this.textBox113.Text = strArray[112];
      this.textBox114.Text = strArray[113];
      this.textBox115.Text = strArray[114];
      this.textBox116.Text = strArray[115];
      this.textBox117.Text = strArray[116];
      this.textBox118.Text = strArray[117];
      this.textBox119.Text = strArray[118];
      this.textBox120.Text = strArray[119];
      this.textBox121.Text = strArray[120];
      this.textBox122.Text = strArray[121];
      this.textBox123.Text = strArray[122];
      this.textBox124.Text = strArray[123];
      this.textBox125.Text = strArray[124];
      this.textBox126.Text = strArray[125];
      this.textBox127.Text = strArray[126];
      this.textBox128.Text = strArray[(int) sbyte.MaxValue];
      this.textBox129.Text = strArray[128];
      this.textBox130.Text = strArray[129];
      this.textBox131.Text = strArray[130];
      this.textBox132.Text = strArray[131];
      this.textBox133.Text = strArray[132];
      this.textBox134.Text = strArray[133];
      this.textBox135.Text = strArray[134];
      this.textBox136.Text = strArray[135];
      this.textBox137.Text = strArray[136];
      this.textBox138.Text = strArray[137];
      this.textBox139.Text = strArray[138];
      this.textBox140.Text = strArray[139];
      this.textBox141.Text = strArray[140];
      this.textBox142.Text = strArray[141];
      this.textBox143.Text = strArray[142];
      this.textBox144.Text = strArray[143];
      this.textBox145.Text = strArray[144];
      this.textBox146.Text = strArray[145];
      this.textBox147.Text = strArray[146];
      this.textBox148.Text = strArray[147];
      this.textBox149.Text = strArray[148];
      this.textBox150.Text = strArray[149];
      this.textBox151.Text = strArray[150];
      this.textBox152.Text = strArray[151];
      this.textBox153.Text = strArray[152];
      this.textBox154.Text = strArray[153];
      this.textBox155.Text = strArray[154];
      this.textBox156.Text = strArray[155];
      this.textBox157.Text = strArray[156];
      this.textBox158.Text = strArray[157];
      this.textBox159.Text = strArray[158];
      this.textBox160.Text = strArray[159];
      this.textBox161.Text = strArray[160];
      this.textBox162.Text = strArray[161];
      this.textBox163.Text = strArray[162];
      this.textBox164.Text = strArray[163];
      this.textBox165.Text = strArray[164];
      this.textBox166.Text = strArray[165];
      this.textBox167.Text = strArray[166];
      this.textBox168.Text = strArray[167];
      this.textBox169.Text = strArray[168];
      this.textBox170.Text = strArray[169];
      this.textBox171.Text = strArray[170];
      this.textBox172.Text = strArray[171];
      this.textBox173.Text = strArray[172];
      this.textBox174.Text = strArray[173];
      this.textBox175.Text = strArray[174];
      this.textBox176.Text = strArray[175];
      this.tbZoneFlag.Text = strArray[170];
      this.tbExtraFlag.Text = strArray[171];
      this.textBox179.Text = "-1";
      this.textBox181.Text = "1";
      this.textBox182.Text = "0";
      this.textBox183.Text = "10";
      this.textBox213.Text = "0";
      this.textBox214.Text = "0";
      this.textBox215.Text = "0";
      this.textBox216.Text = "0";
      this.textBox217.Text = "0";
      this.textBox185.Text = "-1";
      this.textBox187.Text = "-1";
      this.textBox189.Text = "-1";
      this.textBox191.Text = "-1";
      this.textBox193.Text = "-1";
      this.textBox195.Text = "-1";
      this.textBox197.Text = "-1";
      this.textBox199.Text = "-1";
      this.textBox202.Text = "-1";
      this.textBox204.Text = "-1";
      this.textBox206.Text = "-1";
      this.textBox208.Text = "-1";
      this.textBox210.Text = "-1";
      this.textBox212.Text = "-1";
      this.textBox226.Text = "0";
      this.textBox227.Text = "0";
      this.textBox230.Text = "0";
      this.textBox233.Text = "0";
      this.textBox236.Text = "0";
      this.textBox239.Text = "0";
      this.textBox242.Text = "0";
      this.textBox245.Text = "0";
      this.textBox248.Text = "0";
      this.textBox275.Text = "0";
      this.textBox272.Text = "0";
      this.textBox269.Text = "0";
      this.textBox266.Text = "0";
      this.textBox263.Text = "0";
      this.textBox260.Text = "0";
      this.textBox257.Text = "0";
      this.textBox225.Text = "0";
      this.textBox223.Text = "1";
      this.textBox222.Text = "10000";
      this.textBox228.Text = "1";
      this.textBox229.Text = "10000";
      this.textBox231.Text = "1";
      this.textBox232.Text = "10000";
      this.textBox234.Text = "1";
      this.textBox235.Text = "10000";
      this.textBox237.Text = "1";
      this.textBox238.Text = "10000";
      this.textBox240.Text = "1";
      this.textBox241.Text = "10000";
      this.textBox243.Text = "1";
      this.textBox244.Text = "10000";
      this.textBox246.Text = "1";
      this.textBox247.Text = "10000";
      this.textBox249.Text = "1";
      this.textBox250.Text = "10000";
      this.textBox276.Text = "1";
      this.textBox277.Text = "10000";
      this.textBox273.Text = "1";
      this.textBox274.Text = "10000";
      this.textBox270.Text = "1";
      this.textBox271.Text = "10000";
      this.textBox267.Text = "1";
      this.textBox268.Text = "10000";
      this.textBox264.Text = "1";
      this.textBox265.Text = "10000";
      this.textBox261.Text = "1";
      this.textBox262.Text = "10000";
      this.textBox258.Text = "1";
      this.textBox259.Text = "10000";
      this.textBox251.Text = "1";
      this.textBox252.Text = "10000";
      this.SelectBoxes();
      this.LoadDG();
      this.LoadDG2();
      this.FillGrid();
      this.FillGrid2();
    }

        public void LoadDG()
        {
            dataGridView1.Rows.Clear();

            string query = "SELECT * FROM t_npc WHERE a_index = @npcIndex;";
            using (var connection = new MySqlConnection(
                "datasource=" + Host +
                ";Port=3306;" +
                "User ID=" + User +
                ";Password=" + Password +
                ";Database=" + Database +
                ";Charset=utf8mb4;" +
				"SslMode=Preferred;" +
                "TlsVersion=Tls12"))
			{
                using (var command = new MySqlCommand(query, connection))
                {
                    command.Parameters.AddWithValue("@npcIndex", textBox1.Text.Trim());
                    connection.Open();

                    using (var reader = command.ExecuteReader())
                    {
                        if (!reader.Read())
                            return; // NPC not found

                        for (int i = 0; i < 20; i++)
                        {
                            string itemColumn = $"a_item_{i}";
                            string percentColumn = $"a_item_percent_{i}";

                            object itemObj = reader[itemColumn];
                            object percentObj = reader[percentColumn];

                            if (itemObj == DBNull.Value)
                                continue;

                            int itemIndex = SafeInt(itemObj);
                            if (itemIndex <= 0)
                                continue;

                            double percent = SafeDouble(percentObj);

                            // Look up item info
                            Bitmap icon = databaseHandle.IconFast(itemIndex);
                            string name = databaseHandle.ItemNameFast(itemIndex);

                            dataGridView1.Rows.Add(icon, itemIndex, name, percent);
                        }
                    }
                }
            }
        }

        private int SafeInt(object value)
        {
            if (value == null || value == DBNull.Value) return 0;
            return int.TryParse(value.ToString(), out int result) ? result : 0;
        }

        private double SafeDouble(object value)
        {
            if (value == null || value == DBNull.Value) return 0.0;
            return double.TryParse(value.ToString(), out double result) ? result : 0.0;
        }


        public void LoadDG2()
        {
            dataGridView2.Rows.Clear();

            string query = "SELECT * FROM t_npc WHERE a_index = @npcIndex;";
            using (var connection = new MySqlConnection(
                "datasource=" + Host +
                ";Port=3306;" +
                "User ID=" + User +
                ";Password=" + Password +
                ";Database=" + Database +
                ";Charset=utf8mb4;" +
				"SslMode=Preferred;" +
                "TlsVersion=Tls12"))
			{
                using (var command = new MySqlCommand(query, connection))
                {
                    command.Parameters.AddWithValue("@npcIndex", textBox1.Text.Trim());
                    connection.Open();

                    using (var reader = command.ExecuteReader())
                    {
                        if (!reader.Read())
                            return; // NPC not found

                        for (int i = 0; i < 20; i++)
                        {
                            string jewelCol = $"a_jewel_{i}";
                            string percentCol = $"a_jewel_percent_{i}";

                            object jewelObj = reader[jewelCol];
                            object percentObj = reader[percentCol];

                            if (jewelObj == DBNull.Value)
                                continue;

                            int jewelIndex = SafeInt(jewelObj);
                            if (jewelIndex <= 0)
                                continue;

                            double percent = SafeDouble(percentObj);

                            Bitmap icon = databaseHandle.IconFast(jewelIndex);
                            string name = databaseHandle.ItemNameFast(jewelIndex);

                            dataGridView2.Rows.Add(icon, jewelIndex, name, percent);
                        }
                    }
                }
            }
        }


        private void SelectBoxes()
    {
      int num1 = this.comboBox1.FindString(this.textBox31.Text);
      int num2 = this.comboBox2.FindString(this.textBox110.Text);
      this.comboBox1.SelectedIndex = num1;
      this.comboBox2.SelectedIndex = num2;
    }

    private void button2_Click(object sender, EventArgs e)
    {
      if (this.language == "THA")
      {
        this.namee = this.StringFromLanguage();
        this.descrr = this.DescrFromLanguage();
        this.textBox3.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        string str1 = this.textBox3.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        this.textBox4.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        string str2 = this.textBox4.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_npc SET a_index = '" + this.textBox1.Text + "', a_enable = '" + this.textBox2.Text + "', " + this.namee + "='" + str1 + "', " + this.descrr + "='" + str2 + "', a_level = '" + this.textBox5.Text + "', a_family = '" + this.textBox6.Text + "', a_skillmaster = '" + this.textBox7.Text + "', a_flag = '" + this.textBox8.Text + "', a_flag1 = '" + this.textBox9.Text + "', a_state_flag = '" + this.textBox10.Text + "', a_exp = '" + this.textBox11.Text + "', a_prize = '" + this.textBox12.Text + "', a_sight = '" + this.textBox13.Text + "', a_size = '" + this.textBox14.Text + "', a_move_area = '" + this.textBox15.Text + "', a_attack_area = '" + this.textBox16.Text + "', a_skill_point = '" + this.textBox17.Text + "', a_sskill_master = '" + this.textBox18.Text + "', a_str = '" + this.textBox19.Text + "', a_dex = '" + this.textBox20.Text + "', a_int = '" + this.textBox21.Text + "', a_con = '" + this.textBox22.Text + "', a_attack = '" + this.textBox23.Text + "', a_magic = '" + this.textBox24.Text + "', a_defense = '" + this.textBox25.Text + "', a_resist = '" + this.textBox26.Text + "', a_attacklevel = '" + this.textBox27.Text + "', a_defenselevel = '" + this.textBox28.Text + "', a_hp = '" + this.textBox29.Text + "', a_mp = '" + this.textBox30.Text + "', a_attackType = '" + this.textBox31.Text + "', a_attackSpeed = '" + this.textBox32.Text + "', a_recover_hp = '" + this.textBox33.Text + "', a_recover_mp = '" + this.textBox34.Text + "', a_walk_speed = '" + this.textBox35.Text + "', a_run_speed = '" + this.textBox36.Text + "', a_skill0 = '" + this.textBox37.Text + "', a_skill1 = '" + this.textBox38.Text + "', a_skill2 = '" + this.textBox39.Text + "', a_skill3 = '" + this.textBox40.Text + "', a_item_0 = '" + this.textBox41.Text + "', a_item_1 = '" + this.textBox42.Text + "', a_item_2 = '" + this.textBox43.Text + "', a_item_3 = '" + this.textBox44.Text + "', a_item_4 = '" + this.textBox45.Text + "', a_item_5 = '" + this.textBox46.Text + "', a_item_6 = '" + this.textBox47.Text + "', a_item_7 = '" + this.textBox48.Text + "', a_item_8 = '" + this.textBox49.Text + "', a_item_9 = '" + this.textBox50.Text + "', a_item_10 = '" + this.textBox51.Text + "', a_item_11 = '" + this.textBox52.Text + "', a_item_12 = '" + this.textBox53.Text + "', a_item_13 = '" + this.textBox54.Text + "', a_item_14 = '" + this.textBox55.Text + "', a_item_15 = '" + this.textBox56.Text + "', a_item_16 = '" + this.textBox57.Text + "', a_item_17 = '" + this.textBox58.Text + "', a_item_18 = '" + this.textBox59.Text + "', a_item_19 = '" + this.textBox60.Text + "', a_item_percent_0 = '" + this.textBox61.Text + "', a_item_percent_1 = '" + this.textBox62.Text + "', a_item_percent_2 = '" + this.textBox63.Text + "', a_item_percent_3 = '" + this.textBox64.Text + "', a_item_percent_4 = '" + this.textBox65.Text + "', a_item_percent_5 = '" + this.textBox66.Text + "', a_item_percent_6 = '" + this.textBox67.Text + "', a_item_percent_7 = '" + this.textBox68.Text + "', a_item_percent_8 = '" + this.textBox69.Text + "', a_item_percent_9 = '" + this.textBox70.Text + "', a_item_percent_10 = '" + this.textBox71.Text + "', a_item_percent_11 = '" + this.textBox72.Text + "', a_item_percent_12 = '" + this.textBox73.Text + "', a_item_percent_13 = '" + this.textBox74.Text + "', a_item_percent_14 = '" + this.textBox75.Text + "', a_item_percent_15 = '" + this.textBox76.Text + "', a_item_percent_16 = '" + this.textBox77.Text + "', a_item_percent_17 = '" + this.textBox78.Text + "', a_item_percent_18 = '" + this.textBox79.Text + "', a_item_percent_19 = '" + this.textBox80.Text + "', a_minplus = '" + this.textBox81.Text + "', a_maxplus = '" + this.textBox82.Text + "', a_probplus = '" + this.textBox83.Text + "', a_product0 = '" + this.textBox84.Text + "', a_product1 = '" + this.textBox85.Text + "', a_product2 = '" + this.textBox86.Text + "', a_product3 = '" + this.textBox87.Text + "', a_product4 = '" + this.textBox88.Text + "', a_file_smc = '" + this.textBox89.Text.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'") + "', a_motion_walk = '" + this.textBox90.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_idle = '" + this.textBox91.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_dam = '" + this.textBox92.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_attack = '" + this.textBox93.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_die = '" + this.textBox94.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_run = '" + this.textBox95.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_idle2 = '" + this.textBox96.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_attack2 = '" + this.textBox97.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_scale = '" + this.textBox98.Text + "', a_attribute = '" + this.textBox99.Text + "', a_fireDelayCount = '" + this.textBox100.Text + "', a_fireDelay0 = '" + this.textBox101.Text + "', a_fireDelay1 = '" + this.textBox102.Text + "', a_fireDelay2 = '" + this.textBox103.Text + "', a_fireDelay3 = '" + this.textBox104.Text + "', a_fireEffect0 = '" + this.textBox105.Text + "', a_fireEffect1 = '" + this.textBox106.Text + "', a_fireEffect2 = '" + this.textBox107.Text + "', a_fireObject = '" + this.textBox108.Text + "', a_fireSpeed = '" + this.textBox109.Text + "', a_aitype = '" + this.textBox110.Text + "', a_aiflag = '" + this.textBox111.Text + "', a_aileader_flag = '" + this.textBox112.Text + "', a_ai_summonHp = '" + this.textBox113.Text + "', a_aileader_idx = '" + this.textBox114.Text + "', a_aileader_count = '" + this.textBox115.Text + "', a_crafting_category = '" + this.textBox116.Text + "', a_productIndex = '" + this.textBox117.Text + "', a_hit = '" + this.textBox118.Text + "', a_dodge = '" + this.textBox119.Text + "', a_magicavoid = '" + this.textBox120.Text + "', a_job_attribute = '" + this.textBox121.Text + "', a_npc_choice_trigger_count = '" + this.textBox122.Text + "', a_npc_choice_trigger_ids = '" + this.textBox123.Text + "', a_npc_kill_trigger_count = '" + this.textBox124.Text + "', a_npc_kill_trigger_ids = '" + this.textBox125.Text + "', a_createprob = '" + this.textBox126.Text + "', a_socketprob_0 = '" + this.textBox127.Text + "', a_socketprob_1 = '" + this.textBox128.Text + "', a_socketprob_2 = '" + this.textBox129.Text + "', a_socketprob_3 = '" + this.textBox130.Text + "', a_jewel_0 = '" + this.textBox131.Text + "', a_jewel_1 = '" + this.textBox132.Text + "', a_jewel_2 = '" + this.textBox133.Text + "', a_jewel_3 = '" + this.textBox134.Text + "', a_jewel_4 = '" + this.textBox135.Text + "', a_jewel_5 = '" + this.textBox136.Text + "', a_jewel_6 = '" + this.textBox137.Text + "', a_jewel_7 = '" + this.textBox138.Text + "', a_jewel_8 = '" + this.textBox139.Text + "', a_jewel_9 = '" + this.textBox140.Text + "', a_jewel_10 = '" + this.textBox141.Text + "', a_jewel_11 = '" + this.textBox142.Text + "', a_jewel_12 = '" + this.textBox143.Text + "', a_jewel_13 = '" + this.textBox144.Text + "', a_jewel_14 = '" + this.textBox145.Text + "', a_jewel_15 = '" + this.textBox146.Text + "', a_jewel_16 = '" + this.textBox147.Text + "', a_jewel_17 = '" + this.textBox148.Text + "', a_jewel_18 = '" + this.textBox149.Text + "', a_jewel_19 = '" + this.textBox150.Text + "', a_jewel_percent_0 = '" + this.textBox151.Text + "', a_jewel_percent_1 = '" + this.textBox152.Text + "', a_jewel_percent_2 = '" + this.textBox153.Text + "', a_jewel_percent_3 = '" + this.textBox154.Text + "', a_jewel_percent_4 = '" + this.textBox155.Text + "', a_jewel_percent_5 = '" + this.textBox156.Text + "', a_jewel_percent_6 = '" + this.textBox157.Text + "', a_jewel_percent_7 = '" + this.textBox158.Text + "', a_jewel_percent_8 = '" + this.textBox159.Text + "', a_jewel_percent_9 = '" + this.textBox160.Text + "', a_jewel_percent_10 = '" + this.textBox161.Text + "', a_jewel_percent_11 = '" + this.textBox162.Text + "', a_jewel_percent_12 = '" + this.textBox163.Text + "', a_jewel_percent_13 = '" + this.textBox164.Text + "', a_jewel_percent_14 = '" + this.textBox165.Text + "', a_jewel_percent_15 = '" + this.textBox166.Text + "', a_jewel_percent_16 = '" + this.textBox167.Text + "', a_jewel_percent_17 = '" + this.textBox168.Text + "', a_jewel_percent_18 = '" + this.textBox169.Text + "', a_jewel_percent_19 = '" + this.textBox170.Text + "' WHERE a_index = '" + this.textBox1.Text + "'");
      }
      else if (this.language == "USA")
      {
        this.namee = this.StringFromLanguage();
        this.descrr = this.DescrFromLanguage();
        this.textBox3.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        string str3 = this.textBox3.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        this.textBox4.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        string str4 = this.textBox4.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_npc SET a_index = '" + this.textBox1.Text + "', a_enable = '" + this.textBox2.Text + "', a_name ='" + str3 + "',a_descr = '" + str4 + "', a_name_ger ='" + str3 + "',a_descr_ger = '" + str4 + "', a_name_spn ='" + str3 + "',a_descr_spn = '" + str4 + "', " + this.namee + "='" + str3 + "', " + this.descrr + "='" + str4 + "', a_level = '" + this.textBox5.Text + "', a_family = '" + this.textBox6.Text + "', a_skillmaster = '" + this.textBox7.Text + "', a_flag = '" + this.textBox8.Text + "', a_flag1 = '" + this.textBox9.Text + "', a_state_flag = '" + this.textBox10.Text + "', a_exp = '" + this.textBox11.Text + "', a_prize = '" + this.textBox12.Text + "', a_sight = '" + this.textBox13.Text + "', a_size = '" + this.textBox14.Text + "', a_move_area = '" + this.textBox15.Text + "', a_attack_area = '" + this.textBox16.Text + "', a_skill_point = '" + this.textBox17.Text + "', a_sskill_master = '" + this.textBox18.Text + "', a_str = '" + this.textBox19.Text + "', a_dex = '" + this.textBox20.Text + "', a_int = '" + this.textBox21.Text + "', a_con = '" + this.textBox22.Text + "', a_attack = '" + this.textBox23.Text + "', a_magic = '" + this.textBox24.Text + "', a_defense = '" + this.textBox25.Text + "', a_resist = '" + this.textBox26.Text + "', a_attacklevel = '" + this.textBox27.Text + "', a_defenselevel = '" + this.textBox28.Text + "', a_hp = '" + this.textBox29.Text + "', a_mp = '" + this.textBox30.Text + "', a_attackType = '" + this.textBox31.Text + "', a_attackSpeed = '" + this.textBox32.Text + "', a_recover_hp = '" + this.textBox33.Text + "', a_recover_mp = '" + this.textBox34.Text + "', a_walk_speed = '" + this.textBox35.Text + "', a_run_speed = '" + this.textBox36.Text + "', a_skill0 = '" + this.textBox37.Text + "', a_skill1 = '" + this.textBox38.Text + "', a_skill2 = '" + this.textBox39.Text + "', a_skill3 = '" + this.textBox40.Text + "', a_item_0 = '" + this.textBox41.Text + "', a_item_1 = '" + this.textBox42.Text + "', a_item_2 = '" + this.textBox43.Text + "', a_item_3 = '" + this.textBox44.Text + "', a_item_4 = '" + this.textBox45.Text + "', a_item_5 = '" + this.textBox46.Text + "', a_item_6 = '" + this.textBox47.Text + "', a_item_7 = '" + this.textBox48.Text + "', a_item_8 = '" + this.textBox49.Text + "', a_item_9 = '" + this.textBox50.Text + "', a_item_10 = '" + this.textBox51.Text + "', a_item_11 = '" + this.textBox52.Text + "', a_item_12 = '" + this.textBox53.Text + "', a_item_13 = '" + this.textBox54.Text + "', a_item_14 = '" + this.textBox55.Text + "', a_item_15 = '" + this.textBox56.Text + "', a_item_16 = '" + this.textBox57.Text + "', a_item_17 = '" + this.textBox58.Text + "', a_item_18 = '" + this.textBox59.Text + "', a_item_19 = '" + this.textBox60.Text + "', a_item_percent_0 = '" + this.textBox61.Text + "', a_item_percent_1 = '" + this.textBox62.Text + "', a_item_percent_2 = '" + this.textBox63.Text + "', a_item_percent_3 = '" + this.textBox64.Text + "', a_item_percent_4 = '" + this.textBox65.Text + "', a_item_percent_5 = '" + this.textBox66.Text + "', a_item_percent_6 = '" + this.textBox67.Text + "', a_item_percent_7 = '" + this.textBox68.Text + "', a_item_percent_8 = '" + this.textBox69.Text + "', a_item_percent_9 = '" + this.textBox70.Text + "', a_item_percent_10 = '" + this.textBox71.Text + "', a_item_percent_11 = '" + this.textBox72.Text + "', a_item_percent_12 = '" + this.textBox73.Text + "', a_item_percent_13 = '" + this.textBox74.Text + "', a_item_percent_14 = '" + this.textBox75.Text + "', a_item_percent_15 = '" + this.textBox76.Text + "', a_item_percent_16 = '" + this.textBox77.Text + "', a_item_percent_17 = '" + this.textBox78.Text + "', a_item_percent_18 = '" + this.textBox79.Text + "', a_item_percent_19 = '" + this.textBox80.Text + "', a_minplus = '" + this.textBox81.Text + "', a_maxplus = '" + this.textBox82.Text + "', a_probplus = '" + this.textBox83.Text + "', a_product0 = '" + this.textBox84.Text + "', a_product1 = '" + this.textBox85.Text + "', a_product2 = '" + this.textBox86.Text + "', a_product3 = '" + this.textBox87.Text + "', a_product4 = '" + this.textBox88.Text + "', a_file_smc = '" + this.textBox89.Text.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'") + "', a_motion_walk = '" + this.textBox90.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_idle = '" + this.textBox91.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_dam = '" + this.textBox92.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_attack = '" + this.textBox93.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_die = '" + this.textBox94.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_run = '" + this.textBox95.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_idle2 = '" + this.textBox96.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_attack2 = '" + this.textBox97.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_scale = '" + this.textBox98.Text + "', a_attribute = '" + this.textBox99.Text + "', a_fireDelayCount = '" + this.textBox100.Text + "', a_fireDelay0 = '" + this.textBox101.Text + "', a_fireDelay1 = '" + this.textBox102.Text + "', a_fireDelay2 = '" + this.textBox103.Text + "', a_fireDelay3 = '" + this.textBox104.Text + "', a_fireEffect0 = '" + this.textBox105.Text + "', a_fireEffect1 = '" + this.textBox106.Text + "', a_fireEffect2 = '" + this.textBox107.Text + "', a_fireObject = '" + this.textBox108.Text + "', a_fireSpeed = '" + this.textBox109.Text + "', a_aitype = '" + this.textBox110.Text + "', a_aiflag = '" + this.textBox111.Text + "', a_aileader_flag = '" + this.textBox112.Text + "', a_ai_summonHp = '" + this.textBox113.Text + "', a_aileader_idx = '" + this.textBox114.Text + "', a_aileader_count = '" + this.textBox115.Text + "', a_crafting_category = '" + this.textBox116.Text + "', a_productIndex = '" + this.textBox117.Text + "', a_hit = '" + this.textBox118.Text + "', a_dodge = '" + this.textBox119.Text + "', a_magicavoid = '" + this.textBox120.Text + "', a_job_attribute = '" + this.textBox121.Text + "', a_npc_choice_trigger_count = '" + this.textBox122.Text + "', a_npc_choice_trigger_ids = '" + this.textBox123.Text + "', a_npc_kill_trigger_count = '" + this.textBox124.Text + "', a_npc_kill_trigger_ids = '" + this.textBox125.Text + "', a_createprob = '" + this.textBox126.Text + "', a_socketprob_0 = '" + this.textBox127.Text + "', a_socketprob_1 = '" + this.textBox128.Text + "', a_socketprob_2 = '" + this.textBox129.Text + "', a_socketprob_3 = '" + this.textBox130.Text + "', a_jewel_0 = '" + this.textBox131.Text + "', a_jewel_1 = '" + this.textBox132.Text + "', a_jewel_2 = '" + this.textBox133.Text + "', a_jewel_3 = '" + this.textBox134.Text + "', a_jewel_4 = '" + this.textBox135.Text + "', a_jewel_5 = '" + this.textBox136.Text + "', a_jewel_6 = '" + this.textBox137.Text + "', a_jewel_7 = '" + this.textBox138.Text + "', a_jewel_8 = '" + this.textBox139.Text + "', a_jewel_9 = '" + this.textBox140.Text + "', a_jewel_10 = '" + this.textBox141.Text + "', a_jewel_11 = '" + this.textBox142.Text + "', a_jewel_12 = '" + this.textBox143.Text + "', a_jewel_13 = '" + this.textBox144.Text + "', a_jewel_14 = '" + this.textBox145.Text + "', a_jewel_15 = '" + this.textBox146.Text + "', a_jewel_16 = '" + this.textBox147.Text + "', a_jewel_17 = '" + this.textBox148.Text + "', a_jewel_18 = '" + this.textBox149.Text + "', a_jewel_19 = '" + this.textBox150.Text + "', a_jewel_percent_0 = '" + this.textBox151.Text + "', a_jewel_percent_1 = '" + this.textBox152.Text + "', a_jewel_percent_2 = '" + this.textBox153.Text + "', a_jewel_percent_3 = '" + this.textBox154.Text + "', a_jewel_percent_4 = '" + this.textBox155.Text + "', a_jewel_percent_5 = '" + this.textBox156.Text + "', a_jewel_percent_6 = '" + this.textBox157.Text + "', a_jewel_percent_7 = '" + this.textBox158.Text + "', a_jewel_percent_8 = '" + this.textBox159.Text + "', a_jewel_percent_9 = '" + this.textBox160.Text + "', a_jewel_percent_10 = '" + this.textBox161.Text + "', a_jewel_percent_11 = '" + this.textBox162.Text + "', a_jewel_percent_12 = '" + this.textBox163.Text + "', a_jewel_percent_13 = '" + this.textBox164.Text + "', a_jewel_percent_14 = '" + this.textBox165.Text + "', a_jewel_percent_15 = '" + this.textBox166.Text + "', a_jewel_percent_16 = '" + this.textBox167.Text + "', a_jewel_percent_17 = '" + this.textBox168.Text + "', a_jewel_percent_18 = '" + this.textBox169.Text + "', a_jewel_percent_19 = '" + this.textBox170.Text + "' WHERE a_index = '" + this.textBox1.Text + "'");
      }
      else
      {
        this.namee = this.StringFromLanguage();
        this.descrr = this.DescrFromLanguage();
        string str5 = this.textBox3.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        this.textBox3.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        string str6 = this.textBox4.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        this.textBox4.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_npc SET a_index = '" + this.textBox1.Text + "', a_enable = '" + this.textBox2.Text + "', " + this.namee + "='" + str5 + "', " + this.descrr + "='" + str6 + "', a_level = '" + this.textBox5.Text + "', a_family = '" + this.textBox6.Text + "', a_skillmaster = '" + this.textBox7.Text + "', a_flag = '" + this.textBox8.Text + "', a_flag1 = '" + this.textBox9.Text + "', a_state_flag = '" + this.textBox10.Text + "', a_exp = '" + this.textBox11.Text + "', a_prize = '" + this.textBox12.Text + "', a_sight = '" + this.textBox13.Text + "', a_size = '" + this.textBox14.Text + "', a_move_area = '" + this.textBox15.Text + "', a_attack_area = '" + this.textBox16.Text + "', a_skill_point = '" + this.textBox17.Text + "', a_sskill_master = '" + this.textBox18.Text + "', a_str = '" + this.textBox19.Text + "', a_dex = '" + this.textBox20.Text + "', a_int = '" + this.textBox21.Text + "', a_con = '" + this.textBox22.Text + "', a_attack = '" + this.textBox23.Text + "', a_magic = '" + this.textBox24.Text + "', a_defense = '" + this.textBox25.Text + "', a_resist = '" + this.textBox26.Text + "', a_attacklevel = '" + this.textBox27.Text + "', a_defenselevel = '" + this.textBox28.Text + "', a_hp = '" + this.textBox29.Text + "', a_mp = '" + this.textBox30.Text + "', a_attackType = '" + this.textBox31.Text + "', a_attackSpeed = '" + this.textBox32.Text + "', a_recover_hp = '" + this.textBox33.Text + "', a_recover_mp = '" + this.textBox34.Text + "', a_walk_speed = '" + this.textBox35.Text + "', a_run_speed = '" + this.textBox36.Text + "', a_skill0 = '" + this.textBox37.Text + "', a_skill1 = '" + this.textBox38.Text + "', a_skill2 = '" + this.textBox39.Text + "', a_skill3 = '" + this.textBox40.Text + "', a_item_0 = '" + this.textBox41.Text + "', a_item_1 = '" + this.textBox42.Text + "', a_item_2 = '" + this.textBox43.Text + "', a_item_3 = '" + this.textBox44.Text + "', a_item_4 = '" + this.textBox45.Text + "', a_item_5 = '" + this.textBox46.Text + "', a_item_6 = '" + this.textBox47.Text + "', a_item_7 = '" + this.textBox48.Text + "', a_item_8 = '" + this.textBox49.Text + "', a_item_9 = '" + this.textBox50.Text + "', a_item_10 = '" + this.textBox51.Text + "', a_item_11 = '" + this.textBox52.Text + "', a_item_12 = '" + this.textBox53.Text + "', a_item_13 = '" + this.textBox54.Text + "', a_item_14 = '" + this.textBox55.Text + "', a_item_15 = '" + this.textBox56.Text + "', a_item_16 = '" + this.textBox57.Text + "', a_item_17 = '" + this.textBox58.Text + "', a_item_18 = '" + this.textBox59.Text + "', a_item_19 = '" + this.textBox60.Text + "', a_item_percent_0 = '" + this.textBox61.Text + "', a_item_percent_1 = '" + this.textBox62.Text + "', a_item_percent_2 = '" + this.textBox63.Text + "', a_item_percent_3 = '" + this.textBox64.Text + "', a_item_percent_4 = '" + this.textBox65.Text + "', a_item_percent_5 = '" + this.textBox66.Text + "', a_item_percent_6 = '" + this.textBox67.Text + "', a_item_percent_7 = '" + this.textBox68.Text + "', a_item_percent_8 = '" + this.textBox69.Text + "', a_item_percent_9 = '" + this.textBox70.Text + "', a_item_percent_10 = '" + this.textBox71.Text + "', a_item_percent_11 = '" + this.textBox72.Text + "', a_item_percent_12 = '" + this.textBox73.Text + "', a_item_percent_13 = '" + this.textBox74.Text + "', a_item_percent_14 = '" + this.textBox75.Text + "', a_item_percent_15 = '" + this.textBox76.Text + "', a_item_percent_16 = '" + this.textBox77.Text + "', a_item_percent_17 = '" + this.textBox78.Text + "', a_item_percent_18 = '" + this.textBox79.Text + "', a_item_percent_19 = '" + this.textBox80.Text + "', a_minplus = '" + this.textBox81.Text + "', a_maxplus = '" + this.textBox82.Text + "', a_probplus = '" + this.textBox83.Text + "', a_product0 = '" + this.textBox84.Text + "', a_product1 = '" + this.textBox85.Text + "', a_product2 = '" + this.textBox86.Text + "', a_product3 = '" + this.textBox87.Text + "', a_product4 = '" + this.textBox88.Text + "', a_file_smc = '" + this.textBox89.Text.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'") + "', a_motion_walk = '" + this.textBox90.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_idle = '" + this.textBox91.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_dam = '" + this.textBox92.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_attack = '" + this.textBox93.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_die = '" + this.textBox94.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_run = '" + this.textBox95.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_idle2 = '" + this.textBox96.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_attack2 = '" + this.textBox97.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_scale = '" + this.textBox98.Text + "', a_attribute = '" + this.textBox99.Text + "', a_fireDelayCount = '" + this.textBox100.Text + "', a_fireDelay0 = '" + this.textBox101.Text + "', a_fireDelay1 = '" + this.textBox102.Text + "', a_fireDelay2 = '" + this.textBox103.Text + "', a_fireDelay3 = '" + this.textBox104.Text + "', a_fireEffect0 = '" + this.textBox105.Text + "', a_fireEffect1 = '" + this.textBox106.Text + "', a_fireEffect2 = '" + this.textBox107.Text + "', a_fireObject = '" + this.textBox108.Text + "', a_fireSpeed = '" + this.textBox109.Text + "', a_aitype = '" + this.textBox110.Text + "', a_aiflag = '" + this.textBox111.Text + "', a_aileader_flag = '" + this.textBox112.Text + "', a_ai_summonHp = '" + this.textBox113.Text + "', a_aileader_idx = '" + this.textBox114.Text + "', a_aileader_count = '" + this.textBox115.Text + "', a_crafting_category = '" + this.textBox116.Text + "', a_productIndex = '" + this.textBox117.Text + "', a_hit = '" + this.textBox118.Text + "', a_dodge = '" + this.textBox119.Text + "', a_magicavoid = '" + this.textBox120.Text + "', a_job_attribute = '" + this.textBox121.Text + "', a_npc_choice_trigger_count = '" + this.textBox122.Text + "', a_npc_choice_trigger_ids = '" + this.textBox123.Text + "', a_npc_kill_trigger_count = '" + this.textBox124.Text + "', a_npc_kill_trigger_ids = '" + this.textBox125.Text + "', a_createprob = '" + this.textBox126.Text + "', a_socketprob_0 = '" + this.textBox127.Text + "', a_socketprob_1 = '" + this.textBox128.Text + "', a_socketprob_2 = '" + this.textBox129.Text + "', a_socketprob_3 = '" + this.textBox130.Text + "', a_jewel_0 = '" + this.textBox131.Text + "', a_jewel_1 = '" + this.textBox132.Text + "', a_jewel_2 = '" + this.textBox133.Text + "', a_jewel_3 = '" + this.textBox134.Text + "', a_jewel_4 = '" + this.textBox135.Text + "', a_jewel_5 = '" + this.textBox136.Text + "', a_jewel_6 = '" + this.textBox137.Text + "', a_jewel_7 = '" + this.textBox138.Text + "', a_jewel_8 = '" + this.textBox139.Text + "', a_jewel_9 = '" + this.textBox140.Text + "', a_jewel_10 = '" + this.textBox141.Text + "', a_jewel_11 = '" + this.textBox142.Text + "', a_jewel_12 = '" + this.textBox143.Text + "', a_jewel_13 = '" + this.textBox144.Text + "', a_jewel_14 = '" + this.textBox145.Text + "', a_jewel_15 = '" + this.textBox146.Text + "', a_jewel_16 = '" + this.textBox147.Text + "', a_jewel_17 = '" + this.textBox148.Text + "', a_jewel_18 = '" + this.textBox149.Text + "', a_jewel_19 = '" + this.textBox150.Text + "', a_jewel_percent_0 = '" + this.textBox151.Text + "', a_jewel_percent_1 = '" + this.textBox152.Text + "', a_jewel_percent_2 = '" + this.textBox153.Text + "', a_jewel_percent_3 = '" + this.textBox154.Text + "', a_jewel_percent_4 = '" + this.textBox155.Text + "', a_jewel_percent_5 = '" + this.textBox156.Text + "', a_jewel_percent_6 = '" + this.textBox157.Text + "', a_jewel_percent_7 = '" + this.textBox158.Text + "', a_jewel_percent_8 = '" + this.textBox159.Text + "', a_jewel_percent_9 = '" + this.textBox160.Text + "', a_jewel_percent_10 = '" + this.textBox161.Text + "', a_jewel_percent_11 = '" + this.textBox162.Text + "', a_jewel_percent_12 = '" + this.textBox163.Text + "', a_jewel_percent_13 = '" + this.textBox164.Text + "', a_jewel_percent_14 = '" + this.textBox165.Text + "', a_jewel_percent_15 = '" + this.textBox166.Text + "', a_jewel_percent_16 = '" + this.textBox167.Text + "', a_jewel_percent_17 = '" + this.textBox168.Text + "', a_jewel_percent_18 = '" + this.textBox169.Text + "', a_jewel_percent_19 = '" + this.textBox170.Text + "' WHERE a_index = '" + this.textBox1.Text + "'");
      }
      int selectedIndex = this.listBox1.SelectedIndex;
      int num = (int) new CustomMessage("Done :)").ShowDialog();
      if (this.textBox200.Text != "")
        this.SearchList(this.textBox200.Text);
      else
        this.LoadListBox();
      this.listBox1.SelectedIndex = selectedIndex;
    }

    private void button1_Click(object sender, EventArgs e)
    {
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_npc DEFAULT VALUES");
      this.LoadListBox();
      this.listBox1.SelectedIndex = this.listBox1.Items.Count - 1;
      this.textBox2.Text = "1";
    }

    private void button3_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want to Delete NPC ID " + this.textBox1.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      int selectedIndex = this.listBox1.SelectedIndex;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_npc WHERE a_index = '" + this.textBox1.Text + "'");
      this.LoadListBox();
      this.listBox1.SelectedIndex = selectedIndex - 1;
      int num = (int) new CustomMessage("Deleted :O").ShowDialog();
    }

    public bool SearchString(string s) => s.ToUpper().Contains(this.textBox200.Text.ToUpper());

    private void textBox150_TextChanged(object sender, EventArgs e)
    {
      if (this.language == "GER")
        this.listBox1.DataSource = (object) this.databaseHandle.SearchList(this.textBox200.Text, this.menuArrayGER, "t_npc");
      else if (this.language == "POL")
        this.listBox1.DataSource = (object) this.databaseHandle.SearchList(this.textBox200.Text, this.menuArrayPOL, "t_npc");
      else if (this.language == "BRA")
        this.listBox1.DataSource = (object) this.databaseHandle.SearchList(this.textBox200.Text, this.menuArrayBRA, "t_npc");
      else if (this.language == "RUS")
        this.listBox1.DataSource = (object) this.databaseHandle.SearchList(this.textBox200.Text, this.menuArrayRUS, "t_npc");
      else if (this.language == "FRA")
        this.listBox1.DataSource = (object) this.databaseHandle.SearchList(this.textBox200.Text, this.menuArrayFRA, "t_npc");
      else if (this.language == "ESP")
        this.listBox1.DataSource = (object) this.databaseHandle.SearchList(this.textBox200.Text, this.menuArrayESP, "t_npc");
      else if (this.language == "MEX")
        this.listBox1.DataSource = (object) this.databaseHandle.SearchList(this.textBox200.Text, this.menuArrayMEX, "t_npc");
      else if (this.language == "THA")
        this.listBox1.DataSource = (object) this.databaseHandle.SearchList(this.textBox200.Text, this.menuArrayTHA, "t_npc");
      else if (this.language == "ITA")
        this.listBox1.DataSource = (object) this.databaseHandle.SearchList(this.textBox200.Text, this.menuArrayITA, "t_npc");
      else if (this.language == "USA")
        this.listBox1.DataSource = (object) this.databaseHandle.SearchList(this.textBox200.Text, this.menuArrayUSA, "t_npc");
      else
        this.listBox1.DataSource = (object) this.databaseHandle.SearchList(this.textBox200.Text, this.menuArray, "t_npc");
    }

    private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox31.Text = this.GetIndexByComboBox(this.comboBox1.Text).ToString();
    }

    private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox110.Text = this.GetIndexByComboBox(this.comboBox2.Text).ToString();
    }

    private void listBox2_SelectedIndexChanged(object sender, EventArgs e)
    {
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

    private void MobEditor_Load(object sender, EventArgs e)
    {
      this.InitializeDevice();
      this.LoadDG();
      this.LoadDG2();
      this.LoadListBox();
      this.SelectBoxes();
      this.LoadLangAtStartup();
    }

    private void TransferDataGridToTextBox()
    {
      this.textBox41.Text = Convert.ToString(this.dataGridView1.Rows[0].Cells["Column2"].Value);
      this.dataGridView1.Rows[0].Cells["Column1"].Value = (object) this.databaseHandle.IconFast(Convert.ToInt32(this.textBox41.Text));
      this.dataGridView1.Rows[0].Cells["Column3"].Value = (object) this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox41.Text));
      this.textBox42.Text = Convert.ToString(this.dataGridView1.Rows[1].Cells["Column2"].Value);
      this.dataGridView1.Rows[1].Cells["Column1"].Value = (object) this.databaseHandle.IconFast(Convert.ToInt32(this.textBox42.Text));
      this.dataGridView1.Rows[1].Cells["Column3"].Value = (object) this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox42.Text));
      this.textBox43.Text = Convert.ToString(this.dataGridView1.Rows[2].Cells["Column2"].Value);
      this.dataGridView1.Rows[2].Cells["Column1"].Value = (object) this.databaseHandle.IconFast(Convert.ToInt32(this.textBox43.Text));
      this.dataGridView1.Rows[2].Cells["Column3"].Value = (object) this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox43.Text));
      this.textBox44.Text = Convert.ToString(this.dataGridView1.Rows[3].Cells["Column2"].Value);
      this.dataGridView1.Rows[3].Cells["Column1"].Value = (object) this.databaseHandle.IconFast(Convert.ToInt32(this.textBox44.Text));
      this.dataGridView1.Rows[3].Cells["Column3"].Value = (object) this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox44.Text));
      this.textBox45.Text = Convert.ToString(this.dataGridView1.Rows[4].Cells["Column2"].Value);
      this.dataGridView1.Rows[4].Cells["Column1"].Value = (object) this.databaseHandle.IconFast(Convert.ToInt32(this.textBox45.Text));
      this.dataGridView1.Rows[4].Cells["Column3"].Value = (object) this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox45.Text));
      this.textBox46.Text = Convert.ToString(this.dataGridView1.Rows[5].Cells["Column2"].Value);
      this.dataGridView1.Rows[5].Cells["Column1"].Value = (object) this.databaseHandle.IconFast(Convert.ToInt32(this.textBox46.Text));
      this.dataGridView1.Rows[5].Cells["Column3"].Value = (object) this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox46.Text));
      this.textBox47.Text = Convert.ToString(this.dataGridView1.Rows[6].Cells["Column2"].Value);
      this.dataGridView1.Rows[6].Cells["Column1"].Value = (object) this.databaseHandle.IconFast(Convert.ToInt32(this.textBox47.Text));
      this.dataGridView1.Rows[6].Cells["Column3"].Value = (object) this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox47.Text));
      this.textBox48.Text = Convert.ToString(this.dataGridView1.Rows[7].Cells["Column2"].Value);
      this.dataGridView1.Rows[7].Cells["Column1"].Value = (object) this.databaseHandle.IconFast(Convert.ToInt32(this.textBox48.Text));
      this.dataGridView1.Rows[7].Cells["Column3"].Value = (object) this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox48.Text));
      this.textBox49.Text = Convert.ToString(this.dataGridView1.Rows[8].Cells["Column2"].Value);
      this.dataGridView1.Rows[8].Cells["Column1"].Value = (object) this.databaseHandle.IconFast(Convert.ToInt32(this.textBox49.Text));
      this.dataGridView1.Rows[8].Cells["Column3"].Value = (object) this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox49.Text));
      this.textBox50.Text = Convert.ToString(this.dataGridView1.Rows[9].Cells["Column2"].Value);
      this.dataGridView1.Rows[9].Cells["Column1"].Value = (object) this.databaseHandle.IconFast(Convert.ToInt32(this.textBox50.Text));
      this.dataGridView1.Rows[9].Cells["Column3"].Value = (object) this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox50.Text));
      this.textBox51.Text = Convert.ToString(this.dataGridView1.Rows[10].Cells["Column2"].Value);
      this.dataGridView1.Rows[10].Cells["Column1"].Value = (object) this.databaseHandle.IconFast(Convert.ToInt32(this.textBox51.Text));
      this.dataGridView1.Rows[10].Cells["Column3"].Value = (object) this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox51.Text));
      this.textBox52.Text = Convert.ToString(this.dataGridView1.Rows[11].Cells["Column2"].Value);
      this.dataGridView1.Rows[11].Cells["Column1"].Value = (object) this.databaseHandle.IconFast(Convert.ToInt32(this.textBox52.Text));
      this.dataGridView1.Rows[11].Cells["Column3"].Value = (object) this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox52.Text));
      this.textBox53.Text = Convert.ToString(this.dataGridView1.Rows[12].Cells["Column2"].Value);
      this.dataGridView1.Rows[12].Cells["Column1"].Value = (object) this.databaseHandle.IconFast(Convert.ToInt32(this.textBox53.Text));
      this.dataGridView1.Rows[12].Cells["Column3"].Value = (object) this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox53.Text));
      this.textBox54.Text = Convert.ToString(this.dataGridView1.Rows[13].Cells["Column2"].Value);
      this.dataGridView1.Rows[13].Cells["Column1"].Value = (object) this.databaseHandle.IconFast(Convert.ToInt32(this.textBox54.Text));
      this.dataGridView1.Rows[13].Cells["Column3"].Value = (object) this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox54.Text));
      this.textBox55.Text = Convert.ToString(this.dataGridView1.Rows[14].Cells["Column2"].Value);
      this.dataGridView1.Rows[14].Cells["Column1"].Value = (object) this.databaseHandle.IconFast(Convert.ToInt32(this.textBox55.Text));
      this.dataGridView1.Rows[14].Cells["Column3"].Value = (object) this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox55.Text));
      this.textBox56.Text = Convert.ToString(this.dataGridView1.Rows[15].Cells["Column2"].Value);
      this.dataGridView1.Rows[15].Cells["Column1"].Value = (object) this.databaseHandle.IconFast(Convert.ToInt32(this.textBox56.Text));
      this.dataGridView1.Rows[15].Cells["Column3"].Value = (object) this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox56.Text));
      this.textBox57.Text = Convert.ToString(this.dataGridView1.Rows[16].Cells["Column2"].Value);
      this.dataGridView1.Rows[16].Cells["Column1"].Value = (object) this.databaseHandle.IconFast(Convert.ToInt32(this.textBox57.Text));
      this.dataGridView1.Rows[16].Cells["Column3"].Value = (object) this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox57.Text));
      this.textBox58.Text = Convert.ToString(this.dataGridView1.Rows[17].Cells["Column2"].Value);
      this.dataGridView1.Rows[17].Cells["Column1"].Value = (object) this.databaseHandle.IconFast(Convert.ToInt32(this.textBox58.Text));
      this.dataGridView1.Rows[17].Cells["Column3"].Value = (object) this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox58.Text));
      this.textBox59.Text = Convert.ToString(this.dataGridView1.Rows[18].Cells["Column2"].Value);
      this.dataGridView1.Rows[18].Cells["Column1"].Value = (object) this.databaseHandle.IconFast(Convert.ToInt32(this.textBox59.Text));
      this.dataGridView1.Rows[18].Cells["Column3"].Value = (object) this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox59.Text));
      this.textBox60.Text = Convert.ToString(this.dataGridView1.Rows[19].Cells["Column2"].Value);
      this.dataGridView1.Rows[19].Cells["Column1"].Value = (object) this.databaseHandle.IconFast(Convert.ToInt32(this.textBox60.Text));
      this.dataGridView1.Rows[19].Cells["Column3"].Value = (object) this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox60.Text));
      this.textBox61.Text = Convert.ToString(this.dataGridView1.Rows[0].Cells["Column4"].Value);
      this.textBox62.Text = Convert.ToString(this.dataGridView1.Rows[1].Cells["Column4"].Value);
      this.textBox63.Text = Convert.ToString(this.dataGridView1.Rows[2].Cells["Column4"].Value);
      this.textBox64.Text = Convert.ToString(this.dataGridView1.Rows[3].Cells["Column4"].Value);
      this.textBox65.Text = Convert.ToString(this.dataGridView1.Rows[4].Cells["Column4"].Value);
      this.textBox66.Text = Convert.ToString(this.dataGridView1.Rows[5].Cells["Column4"].Value);
      this.textBox67.Text = Convert.ToString(this.dataGridView1.Rows[6].Cells["Column4"].Value);
      this.textBox68.Text = Convert.ToString(this.dataGridView1.Rows[7].Cells["Column4"].Value);
      this.textBox69.Text = Convert.ToString(this.dataGridView1.Rows[8].Cells["Column4"].Value);
      this.textBox70.Text = Convert.ToString(this.dataGridView1.Rows[9].Cells["Column4"].Value);
      this.textBox71.Text = Convert.ToString(this.dataGridView1.Rows[10].Cells["Column4"].Value);
      this.textBox72.Text = Convert.ToString(this.dataGridView1.Rows[11].Cells["Column4"].Value);
      this.textBox73.Text = Convert.ToString(this.dataGridView1.Rows[12].Cells["Column4"].Value);
      this.textBox74.Text = Convert.ToString(this.dataGridView1.Rows[13].Cells["Column4"].Value);
      this.textBox75.Text = Convert.ToString(this.dataGridView1.Rows[14].Cells["Column4"].Value);
      this.textBox76.Text = Convert.ToString(this.dataGridView1.Rows[15].Cells["Column4"].Value);
      this.textBox77.Text = Convert.ToString(this.dataGridView1.Rows[16].Cells["Column4"].Value);
      this.textBox78.Text = Convert.ToString(this.dataGridView1.Rows[17].Cells["Column4"].Value);
      this.textBox79.Text = Convert.ToString(this.dataGridView1.Rows[18].Cells["Column4"].Value);
      this.textBox80.Text = Convert.ToString(this.dataGridView1.Rows[19].Cells["Column4"].Value);
    }

    private void dataGridView1_RowLeave(object sender, DataGridViewCellEventArgs e)
    {
    }

    private void dataGridView1_CellEndEdit(object sender, DataGridViewCellEventArgs e)
    {
      this.TransferDataGridToTextBox();
    }

    private void TransferDataGrid2ToTextBox()
    {
      this.textBox131.Text = Convert.ToString(this.dataGridView2.Rows[0].Cells["Column6"].Value);
      this.dataGridView2.Rows[0].Cells["Column5"].Value = (object) this.databaseHandle.IconFast(Convert.ToInt32(this.textBox131.Text));
      this.dataGridView2.Rows[0].Cells["Column7"].Value = (object) this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox131.Text));
      this.textBox132.Text = Convert.ToString(this.dataGridView2.Rows[1].Cells["Column6"].Value);
      this.dataGridView2.Rows[1].Cells["Column5"].Value = (object) this.databaseHandle.IconFast(Convert.ToInt32(this.textBox132.Text));
      this.dataGridView2.Rows[1].Cells["Column7"].Value = (object) this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox132.Text));
      this.textBox151.Text = Convert.ToString(this.dataGridView2.Rows[0].Cells["Column8"].Value);
      this.textBox152.Text = Convert.ToString(this.dataGridView2.Rows[1].Cells["Column8"].Value);
    }

    private void dataGridView2_CellEndEdit_1(object sender, DataGridViewCellEventArgs e)
    {
      this.TransferDataGrid2ToTextBox();
    }

    private void pictureBox23_Click(object sender, EventArgs e)
    {
      FlagBuilder flagBuilder = new FlagBuilder();
      flagBuilder.flagSmall = Convert.ToInt32(this.textBox8.Text);
      flagBuilder.flagBuilderType = "npcs";
      if (flagBuilder.ShowDialog() != DialogResult.OK)
        return;
      this.textBox8.Text = flagBuilder.flagSmall.ToString();
    }

    private void pictureBox1_Click(object sender, EventArgs e)
    {
      FlagBuilder flagBuilder = new FlagBuilder();
      flagBuilder.flagSmall = Convert.ToInt32(this.textBox9.Text);
      flagBuilder.flagBuilderType = "npcs1";
      if (flagBuilder.ShowDialog() != DialogResult.OK)
        return;
      this.textBox9.Text = flagBuilder.flagSmall.ToString();
    }

    private void InitializeDevice()
    {
      this._Direct3D = new Direct3D();
      Direct3D direct3D = this._Direct3D;
      int adapter = 0;
      int num1 = 1;
      IntPtr handle1 = this.Handle;
      int num2 = 32;
      PresentParameters[] presentParametersArray = new PresentParameters[1];
      int index = 0;
      PresentParameters presentParameters = new PresentParameters();
      presentParameters.SwapEffect = SwapEffect.Discard;
      IntPtr handle2 = this.panel3DView.Handle;
      presentParameters.DeviceWindowHandle = handle2;
      int num3 = 1;
      presentParameters.Windowed = num3 != 0;
      int width = this.panel3DView.Width;
      presentParameters.BackBufferWidth = width;
      int height = this.panel3DView.Height;
      presentParameters.BackBufferHeight = height;
      int num4 = 21;
      presentParameters.BackBufferFormat = (SlimDX.Direct3D9.Format) num4;
      presentParametersArray[index] = presentParameters;
      this._Device = new Device(direct3D, adapter, (DeviceType) num1, handle1, (CreateFlags) num2, presentParametersArray);
      this._Device.SetRenderState<Cull>(RenderState.CullMode, Cull.None);
      this._Device.SetRenderState<FillMode>(RenderState.FillMode, FillMode.Solid);
      this._Device.SetRenderState(RenderState.Lighting, false);
      this.CameraPositioning();
    }

    private void CameraPositioning()
    {
      this._Device.SetTransform(TransformState.Projection, Matrix.PerspectiveFovLH(100f, 1f, 1f, 450f));
      this._Device.SetTransform(TransformState.View, Matrix.LookAtLH(new Vector3(0.0f, 0.0f, -5f), new Vector3(0.0f, 0.0f, 0.0f), new Vector3(0.0f, 1f, 0.0f)));
      this._Device.SetTransform(TransformState.World, Matrix.RotationYawPitchRoll(0.0f, 0.0f, 0.0f));
    }

    private void Render()
    {
      this._Device.Viewport = new Viewport(0, 0, this.panel3DView.Width, this.panel3DView.Height);
      this._Device.Clear(ClearFlags.ZBuffer | ClearFlags.Target, new Color4(Color.FromKnownColor(KnownColor.Control)), 1f, 0);
      this._Device.BeginScene();
      this._Device.SetTransform(TransformState.View, Matrix.LookAtLH(new Vector3(0.0f, 0.0f, this._Zoom), new Vector3(this._LeftRight, this._UpDown, 0.0f), new Vector3(0.0f, 1f, 0.0f)));
      this._Device.SetTransform(TransformState.World, Matrix.RotationYawPitchRoll(this._Rotation, 3.1f, 0.0f));
      if (this._Models != null && this._Models.Count<tMesh>() != 0)
      {
        for (int index = 0; index < this._Models.Count<tMesh>(); ++index)
        {
          if (this._Models[index].TexData != null)
            this._Device.SetTexture(0, (BaseTexture) this._Models[index].TexData);
          for (int subset = 0; subset < 1000; ++subset)
            this._Models[index].MeshData.DrawSubset(subset);
        }
      }
      this._Device.EndScene();
      this._Device.Present();
      this._Rotation -= 0.03f;
    }

    private SlimDX.Direct3D9.Format ConvFormat(texFormat tFormat)
    {
      SlimDX.Direct3D9.Format format = SlimDX.Direct3D9.Format.Unknown;
      switch (tFormat)
      {
        case texFormat.RGB:
          return SlimDX.Direct3D9.Format.R8G8B8;
        case texFormat.ARGB:
          return SlimDX.Direct3D9.Format.A8R8G8B8;
        case texFormat.DXT1:
          return SlimDX.Direct3D9.Format.Dxt1;
        case texFormat.DXT3:
          return SlimDX.Direct3D9.Format.Dxt3;
        default:
          return format;
      }
    }

    private Texture BuildTexture(byte[] imageData, SlimDX.Direct3D9.Format imageFormat, int width, int height)
    {
      switch (imageFormat)
      {
        case SlimDX.Direct3D9.Format.R8G8B8:
          MemoryStream memoryStream1;
          using (memoryStream1 = new MemoryStream())
          {
            Tex.makeRGB8(imageData, width, height).Save((Stream) memoryStream1, ImageFormat.Bmp);
            memoryStream1.Write(imageData, 0, imageData.Length);
            memoryStream1.Position = 0L;
            return Texture.FromStream(this._Device, (Stream) memoryStream1, width, height, 0, Usage.SoftwareProcessing, SlimDX.Direct3D9.Format.A8B8G8R8, Pool.Default, SlimDX.Direct3D9.Filter.None, SlimDX.Direct3D9.Filter.None, 0);
          }
        case SlimDX.Direct3D9.Format.A8R8G8B8:
          MemoryStream memoryStream2;
          using (memoryStream2 = new MemoryStream())
          {
            Tex.makeRGB(imageData, width, height).Save((Stream) memoryStream2, ImageFormat.Bmp);
            memoryStream2.Write(imageData, 0, imageData.Length);
            memoryStream2.Position = 0L;
            return Texture.FromStream(this._Device, (Stream) memoryStream2, width, height, 0, Usage.SoftwareProcessing, SlimDX.Direct3D9.Format.A8B8G8R8, Pool.Default, SlimDX.Direct3D9.Filter.None, SlimDX.Direct3D9.Filter.None, 0);
          }
        default:
          Texture texture = new Texture(this._Device, width, height, 0, Usage.None, imageFormat, Pool.Managed);
          using (Stream data = (Stream) texture.LockRectangle(0, LockFlags.None).Data)
          {
            data.Write(imageData, 0, ((IEnumerable<byte>) imageData).Count<byte>());
            texture.UnlockRectangle(0);
          }
          return texture;
      }
    }

    private Texture GetTextureFromFile(string FileName)
    {
      Texture textureFromFile = (Texture) null;
      if (File.Exists(FileName))
      {
        Tex.ReadFile(FileName);
        SlimDX.Direct3D9.Format imageFormat = this.ConvFormat(Tex.GetFormat());
        textureFromFile = this.BuildTexture(Tex.lcTex.imageData[0], imageFormat, (int) Tex.lcTex.Header.Width, (int) Tex.lcTex.Header.Height);
      }
      return textureFromFile;
    }

        private void MakeLCModels(string smcFile)
        {
            try
            {
                // Prefer the manager wrapper we added
                MobEditor3DManager.LoadSmcForForm(this, smcFile);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error initializing 3D preview: " + ex.Message, "3D Error", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
        }


        private void timer1_Tick(object sender, EventArgs e) => this.Render();

    private void slideZoom_Scroll(object sender, EventArgs e)
    {
      this._Zoom = (float) this.slideZoom.Value / 100f;
    }

    private void slideUpDown_Scroll(object sender, EventArgs e)
    {
      this._UpDown = (float) this.slideUpDown.Value / 1000f;
    }

    private void slideLeftRight_Scroll(object sender, EventArgs e)
    {
      this._LeftRight = (float) this.slideLeftRight.Value / 1000f;
    }

    private void button4_Click(object sender, EventArgs e)
    {
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DROP TABLE IF EXISTS tempTable;CREATE TEMPORARY TABLE tempTable ENGINE=MyISAM SELECT * FROM t_npc WHERE a_index=" + this.textBox1.Text + ";SELECT a_index FROM tempTable;UPDATE tempTable SET a_index=(SELECT a_index from t_npc ORDER BY a_index DESC LIMIT 1)+1; SELECT a_index FROM tempTable;INSERT INTO t_npc SELECT * FROM tempTable;");
      this.LoadListBox();
      this.listBox1.SelectedIndex = this.listBox1.Items.Count - 1;
    }

    private void dataGridView2_CellContentClick(object sender, DataGridViewCellEventArgs e)
    {
    }

    private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
    {
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void DoSetBits(CheckedListBox clb, out ulong ZoneFlags)
    {
      BitArray bitArray = new BitArray(64);
      for (int index = 0; index < clb.Items.Count; ++index)
        bitArray.Set(index, clb.GetItemChecked(index));
      byte[] numArray = new byte[8];
      bitArray.CopyTo((Array) numArray, 0);
      ZoneFlags = BitConverter.ToUInt64(numArray, 0);
    }

    private void DoSetBits(CheckedListBox clb, ItemCheckEventArgs item, out ulong ZoneFlags)
    {
      BitArray bitArray = new BitArray(64);
      for (int index = 0; index < clb.Items.Count; ++index)
        bitArray.Set(index, clb.GetItemChecked(index));
      bitArray.Set(item.Index, item.NewValue == CheckState.Checked);
      byte[] numArray = new byte[8];
      bitArray.CopyTo((Array) numArray, 0);
      ZoneFlags = BitConverter.ToUInt64(numArray, 0);
    }

    private void ZoneFlagItemCheck(object sender, ItemCheckEventArgs e)
    {
      ulong ZoneFlags = 0;
      this.DoSetBits(this.clbZone, e, out ZoneFlags);
      this.tbZoneFlag.Text = ZoneFlags.ToString();
    }

    private void ZoneFlagExtraItemCheck(object sender, ItemCheckEventArgs e)
    {
      ulong ZoneFlags = 0;
      this.DoSetBits(this.clbExtra, e, out ZoneFlags);
      this.tbExtraFlag.Text = ZoneFlags.ToString();
    }

    private void InitializeComponent()
    {
      this.components = (IContainer) new System.ComponentModel.Container();
      this.menuStrip1 = new MenuStrip();
      this.exportMobAlllodToolStripMenuItem = new ToolStripMenuItem();
      this.exportMobAlllodToolStripMenuItem1 = new ToolStripMenuItem();
      this.strNpcNamelodToolStripMenuItem = new ToolStripMenuItem();
      this.exportZoneFlaglodToolStripMenuItem = new ToolStripMenuItem();
      this.mYSQLToolStripMenuItem = new ToolStripMenuItem();
      this.massEditToolStripMenuItem = new ToolStripMenuItem();
      this.groupBox3 = new GroupBox();
      this.button4 = new Button();
      this.button3 = new Button();
      this.button1 = new Button();
      this.listBox1 = new ListBox();
      this.groupBox5 = new GroupBox();
      this.textBox200 = new TextBox();
      this.label7 = new Label();
      this.tabControl1 = new TabControl();
      this.tabPage1 = new TabPage();
      this.groupBox20 = new GroupBox();
      this.chk3D = new CheckBox();
      this.slideLeftRight = new TrackBar();
      this.slideUpDown = new TrackBar();
      this.slideZoom = new TrackBar();
      this.panel3DView = new Panel();
      this.groupBox15 = new GroupBox();
      this.label70 = new Label();
      this.label69 = new Label();
      this.textBox107 = new TextBox();
      this.textBox106 = new TextBox();
      this.textBox105 = new TextBox();
      this.label68 = new Label();
      this.groupBox14 = new GroupBox();
      this.label72 = new Label();
      this.textBox109 = new TextBox();
      this.label71 = new Label();
      this.textBox108 = new TextBox();
      this.textBox104 = new TextBox();
      this.textBox103 = new TextBox();
      this.textBox102 = new TextBox();
      this.textBox101 = new TextBox();
      this.textBox100 = new TextBox();
      this.label67 = new Label();
      this.label63 = new Label();
      this.label66 = new Label();
      this.label64 = new Label();
      this.label65 = new Label();
      this.groupBox17 = new GroupBox();
      this.textBox174 = new TextBox();
      this.textBox173 = new TextBox();
      this.label137 = new Label();
      this.label136 = new Label();
      this.groupBox13 = new GroupBox();
      this.BtnAniAttack2 = new Button();
      this.btnAniIdle2 = new Button();
      this.btnAniRun = new Button();
      this.btnAniDie = new Button();
      this.BtnAniAttack1 = new Button();
      this.BtnAniDam = new Button();
      this.BtnAniWalk = new Button();
      this.BtnAniIdle = new Button();
      this.label60 = new Label();
      this.label59 = new Label();
      this.label58 = new Label();
      this.label57 = new Label();
      this.label56 = new Label();
      this.label55 = new Label();
      this.label54 = new Label();
      this.label53 = new Label();
      this.textBox97 = new TextBox();
      this.textBox96 = new TextBox();
      this.textBox95 = new TextBox();
      this.textBox94 = new TextBox();
      this.textBox93 = new TextBox();
      this.textBox92 = new TextBox();
      this.textBox91 = new TextBox();
      this.textBox90 = new TextBox();
      this.label11 = new Label();
      this.label6 = new Label();
      this.textBox6 = new TextBox();
      this.groupBox1 = new GroupBox();
      this.cbEnabled = new CheckBox();
      this.BtnReadSmc = new Button();
      this.pictureBox1 = new PictureBox();
      this.pictureBox23 = new PictureBox();
      this.label4 = new Label();
      this.textBox4 = new TextBox();
      this.textBox98 = new TextBox();
      this.label61 = new Label();
      this.label52 = new Label();
      this.textBox89 = new TextBox();
      this.textBox30 = new TextBox();
      this.label30 = new Label();
      this.textBox9 = new TextBox();
      this.textBox29 = new TextBox();
      this.textBox1 = new TextBox();
      this.label10 = new Label();
      this.label31 = new Label();
      this.label1 = new Label();
      this.label37 = new Label();
      this.textBox8 = new TextBox();
      this.label32 = new Label();
      this.label9 = new Label();
      this.textBox36 = new TextBox();
      this.label33 = new Label();
      this.label36 = new Label();
      this.textBox32 = new TextBox();
      this.textBox35 = new TextBox();
      this.textBox31 = new TextBox();
      this.comboBox1 = new ComboBox();
      this.label17 = new Label();
      this.label15 = new Label();
      this.textBox16 = new TextBox();
      this.textBox14 = new TextBox();
      this.label8 = new Label();
      this.textBox7 = new TextBox();
      this.textBox5 = new TextBox();
      this.textBox3 = new TextBox();
      this.label3 = new Label();
      this.label5 = new Label();
      this.textBox10 = new TextBox();
      this.tabPage2 = new TabPage();
      this.groupBox6 = new GroupBox();
      this.label16 = new Label();
      this.textBox15 = new TextBox();
      this.label14 = new Label();
      this.textBox13 = new TextBox();
      this.groupBox16 = new GroupBox();
      this.textBox115 = new TextBox();
      this.label78 = new Label();
      this.label77 = new Label();
      this.textBox114 = new TextBox();
      this.label76 = new Label();
      this.textBox113 = new TextBox();
      this.label75 = new Label();
      this.textBox112 = new TextBox();
      this.label74 = new Label();
      this.textBox111 = new TextBox();
      this.label73 = new Label();
      this.textBox110 = new TextBox();
      this.comboBox2 = new ComboBox();
      this.groupBox12 = new GroupBox();
      this.label51 = new Label();
      this.label50 = new Label();
      this.label49 = new Label();
      this.label48 = new Label();
      this.label47 = new Label();
      this.textBox88 = new TextBox();
      this.textBox84 = new TextBox();
      this.textBox87 = new TextBox();
      this.textBox85 = new TextBox();
      this.textBox86 = new TextBox();
      this.groupBox2 = new GroupBox();
      this.label41 = new Label();
      this.label40 = new Label();
      this.label39 = new Label();
      this.label38 = new Label();
      this.textBox40 = new TextBox();
      this.textBox37 = new TextBox();
      this.textBox39 = new TextBox();
      this.textBox38 = new TextBox();
      this.groupBox10 = new GroupBox();
      this.textBox34 = new TextBox();
      this.label35 = new Label();
      this.textBox33 = new TextBox();
      this.label34 = new Label();
      this.groupBox9 = new GroupBox();
      this.label84 = new Label();
      this.textBox121 = new TextBox();
      this.label83 = new Label();
      this.textBox120 = new TextBox();
      this.label82 = new Label();
      this.textBox119 = new TextBox();
      this.label29 = new Label();
      this.textBox28 = new TextBox();
      this.label27 = new Label();
      this.label26 = new Label();
      this.textBox25 = new TextBox();
      this.textBox26 = new TextBox();
      this.groupBox8 = new GroupBox();
      this.label81 = new Label();
      this.textBox118 = new TextBox();
      this.label28 = new Label();
      this.textBox27 = new TextBox();
      this.textBox24 = new TextBox();
      this.label25 = new Label();
      this.textBox23 = new TextBox();
      this.label24 = new Label();
      this.groupBox7 = new GroupBox();
      this.textBox22 = new TextBox();
      this.label23 = new Label();
      this.textBox19 = new TextBox();
      this.label22 = new Label();
      this.textBox20 = new TextBox();
      this.label21 = new Label();
      this.textBox21 = new TextBox();
      this.label20 = new Label();
      this.tabPage4 = new TabPage();
      this.textBox60 = new TextBox();
      this.textBox53 = new TextBox();
      this.textBox80 = new TextBox();
      this.textBox52 = new TextBox();
      this.textBox79 = new TextBox();
      this.textBox51 = new TextBox();
      this.textBox50 = new TextBox();
      this.textBox54 = new TextBox();
      this.textBox78 = new TextBox();
      this.textBox55 = new TextBox();
      this.textBox61 = new TextBox();
      this.textBox56 = new TextBox();
      this.textBox41 = new TextBox();
      this.textBox57 = new TextBox();
      this.textBox77 = new TextBox();
      this.textBox59 = new TextBox();
      this.groupBox18 = new GroupBox();
      this.dataGridView1 = new DataGridView();
      this.Column1 = new DataGridViewImageColumn();
      this.Column2 = new DataGridViewTextBoxColumn();
      this.Column3 = new DataGridViewTextBoxColumn();
      this.Column4 = new DataGridViewTextBoxColumn();
      this.textBox58 = new TextBox();
      this.textBox42 = new TextBox();
      this.textBox76 = new TextBox();
      this.textBox43 = new TextBox();
      this.groupBox4 = new GroupBox();
      this.label18 = new Label();
      this.label13 = new Label();
      this.textBox11 = new TextBox();
      this.textBox17 = new TextBox();
      this.label12 = new Label();
      this.textBox12 = new TextBox();
      this.textBox75 = new TextBox();
      this.textBox44 = new TextBox();
      this.groupBox11 = new GroupBox();
      this.label46 = new Label();
      this.label45 = new Label();
      this.label44 = new Label();
      this.textBox83 = new TextBox();
      this.textBox82 = new TextBox();
      this.textBox81 = new TextBox();
      this.textBox45 = new TextBox();
      this.textBox74 = new TextBox();
      this.textBox70 = new TextBox();
      this.textBox46 = new TextBox();
      this.textBox73 = new TextBox();
      this.textBox47 = new TextBox();
      this.textBox69 = new TextBox();
      this.textBox71 = new TextBox();
      this.textBox48 = new TextBox();
      this.textBox66 = new TextBox();
      this.textBox49 = new TextBox();
      this.textBox72 = new TextBox();
      this.textBox63 = new TextBox();
      this.textBox64 = new TextBox();
      this.textBox67 = new TextBox();
      this.textBox68 = new TextBox();
      this.textBox62 = new TextBox();
      this.textBox65 = new TextBox();
      this.tabPage7 = new TabPage();
      this.groupBox19 = new GroupBox();
      this.dataGridView2 = new DataGridView();
      this.Column5 = new DataGridViewImageColumn();
      this.Column6 = new DataGridViewTextBoxColumn();
      this.Column7 = new DataGridViewTextBoxColumn();
      this.Column8 = new DataGridViewTextBoxColumn();
      this.textBox170 = new TextBox();
      this.textBox169 = new TextBox();
      this.textBox168 = new TextBox();
      this.textBox167 = new TextBox();
      this.textBox166 = new TextBox();
      this.textBox165 = new TextBox();
      this.textBox164 = new TextBox();
      this.textBox163 = new TextBox();
      this.textBox162 = new TextBox();
      this.textBox161 = new TextBox();
      this.textBox160 = new TextBox();
      this.textBox159 = new TextBox();
      this.textBox158 = new TextBox();
      this.textBox157 = new TextBox();
      this.textBox156 = new TextBox();
      this.textBox155 = new TextBox();
      this.textBox154 = new TextBox();
      this.textBox153 = new TextBox();
      this.textBox152 = new TextBox();
      this.textBox151 = new TextBox();
      this.textBox150 = new TextBox();
      this.textBox149 = new TextBox();
      this.textBox148 = new TextBox();
      this.textBox147 = new TextBox();
      this.textBox146 = new TextBox();
      this.textBox145 = new TextBox();
      this.textBox144 = new TextBox();
      this.textBox143 = new TextBox();
      this.textBox142 = new TextBox();
      this.textBox141 = new TextBox();
      this.textBox140 = new TextBox();
      this.textBox139 = new TextBox();
      this.textBox138 = new TextBox();
      this.textBox137 = new TextBox();
      this.textBox136 = new TextBox();
      this.textBox135 = new TextBox();
      this.textBox134 = new TextBox();
      this.textBox133 = new TextBox();
      this.textBox132 = new TextBox();
      this.textBox131 = new TextBox();
      this.tabPage6 = new TabPage();
      this.label62 = new Label();
      this.textBox99 = new TextBox();
      this.label19 = new Label();
      this.textBox18 = new TextBox();
      this.textBox176 = new TextBox();
      this.label139 = new Label();
      this.textBox175 = new TextBox();
      this.label138 = new Label();
      this.textBox172 = new TextBox();
      this.label135 = new Label();
      this.textBox171 = new TextBox();
      this.label134 = new Label();
      this.label93 = new Label();
      this.textBox130 = new TextBox();
      this.label92 = new Label();
      this.textBox129 = new TextBox();
      this.label91 = new Label();
      this.textBox128 = new TextBox();
      this.label90 = new Label();
      this.textBox127 = new TextBox();
      this.label89 = new Label();
      this.textBox126 = new TextBox();
      this.label88 = new Label();
      this.textBox125 = new TextBox();
      this.textBox124 = new TextBox();
      this.label87 = new Label();
      this.label86 = new Label();
      this.label85 = new Label();
      this.textBox123 = new TextBox();
      this.textBox122 = new TextBox();
      this.label80 = new Label();
      this.label79 = new Label();
      this.textBox117 = new TextBox();
      this.textBox116 = new TextBox();
      this.tabPage3 = new TabPage();
      this.button24 = new Button();
      this.textBox221 = new TextBox();
      this.textBox220 = new TextBox();
      this.textBox219 = new TextBox();
      this.textBox218 = new TextBox();
      this.button18 = new Button();
      this.button19 = new Button();
      this.button6 = new Button();
      this.button17 = new Button();
      this.groupBox22 = new GroupBox();
      this.textBox217 = new TextBox();
      this.label140 = new Label();
      this.textBox216 = new TextBox();
      this.label133 = new Label();
      this.textBox215 = new TextBox();
      this.label132 = new Label();
      this.textBox214 = new TextBox();
      this.label131 = new Label();
      this.textBox213 = new TextBox();
      this.label130 = new Label();
      this.button23 = new Button();
      this.pictureBox16 = new PictureBox();
      this.textBox211 = new TextBox();
      this.label128 = new Label();
      this.textBox212 = new TextBox();
      this.label129 = new Label();
      this.button22 = new Button();
      this.pictureBox15 = new PictureBox();
      this.textBox209 = new TextBox();
      this.label126 = new Label();
      this.textBox210 = new TextBox();
      this.label127 = new Label();
      this.button21 = new Button();
      this.pictureBox14 = new PictureBox();
      this.textBox207 = new TextBox();
      this.label124 = new Label();
      this.textBox208 = new TextBox();
      this.label125 = new Label();
      this.button20 = new Button();
      this.pictureBox13 = new PictureBox();
      this.textBox205 = new TextBox();
      this.label122 = new Label();
      this.textBox206 = new TextBox();
      this.label123 = new Label();
      this.button16 = new Button();
      this.pictureBox12 = new PictureBox();
      this.textBox203 = new TextBox();
      this.label120 = new Label();
      this.textBox204 = new TextBox();
      this.label121 = new Label();
      this.button15 = new Button();
      this.pictureBox11 = new PictureBox();
      this.textBox201 = new TextBox();
      this.label118 = new Label();
      this.textBox202 = new TextBox();
      this.label119 = new Label();
      this.button14 = new Button();
      this.pictureBox10 = new PictureBox();
      this.textBox198 = new TextBox();
      this.label116 = new Label();
      this.textBox199 = new TextBox();
      this.label117 = new Label();
      this.button13 = new Button();
      this.pictureBox9 = new PictureBox();
      this.textBox196 = new TextBox();
      this.label114 = new Label();
      this.textBox197 = new TextBox();
      this.label115 = new Label();
      this.button12 = new Button();
      this.pictureBox8 = new PictureBox();
      this.textBox194 = new TextBox();
      this.label112 = new Label();
      this.textBox195 = new TextBox();
      this.label113 = new Label();
      this.button11 = new Button();
      this.pictureBox6 = new PictureBox();
      this.textBox192 = new TextBox();
      this.label110 = new Label();
      this.textBox193 = new TextBox();
      this.label111 = new Label();
      this.button10 = new Button();
      this.pictureBox5 = new PictureBox();
      this.textBox190 = new TextBox();
      this.label108 = new Label();
      this.textBox191 = new TextBox();
      this.label109 = new Label();
      this.button9 = new Button();
      this.pictureBox4 = new PictureBox();
      this.textBox188 = new TextBox();
      this.label106 = new Label();
      this.textBox189 = new TextBox();
      this.label107 = new Label();
      this.button8 = new Button();
      this.pictureBox3 = new PictureBox();
      this.textBox186 = new TextBox();
      this.label104 = new Label();
      this.textBox187 = new TextBox();
      this.label105 = new Label();
      this.button7 = new Button();
      this.pictureBox2 = new PictureBox();
      this.textBox184 = new TextBox();
      this.label102 = new Label();
      this.textBox185 = new TextBox();
      this.label103 = new Label();
      this.groupBox21 = new GroupBox();
      this.label193 = new Label();
      this.button5 = new Button();
      this.pictureBox7 = new PictureBox();
      this.textBox183 = new TextBox();
      this.label101 = new Label();
      this.textBox182 = new TextBox();
      this.label100 = new Label();
      this.textBox181 = new TextBox();
      this.label99 = new Label();
      this.textBox180 = new TextBox();
      this.textBox178 = new TextBox();
      this.label98 = new Label();
      this.label96 = new Label();
      this.textBox177 = new TextBox();
      this.textBox179 = new TextBox();
      this.label95 = new Label();
      this.label97 = new Label();
      this.dgRaidItems = new DataGridView();
      this.Icon = new DataGridViewImageColumn();
      this.a_index = new DataGridViewTextBoxColumn();
      this.a_npc_index = new DataGridViewTextBoxColumn();
      this.a_item_index = new DataGridViewTextBoxColumn();
      this.ItemName = new DataGridViewTextBoxColumn();
      this.a_count = new DataGridViewTextBoxColumn();
      this.a_prob = new DataGridViewTextBoxColumn();
      this.a_flag = new DataGridViewTextBoxColumn();
      this.a_spec_item_index1 = new DataGridViewTextBoxColumn();
      this.a_spec_item_index2 = new DataGridViewTextBoxColumn();
      this.a_spec_item_index3 = new DataGridViewTextBoxColumn();
      this.a_spec_item_index4 = new DataGridViewTextBoxColumn();
      this.a_spec_item_index5 = new DataGridViewTextBoxColumn();
      this.a_spec_item_index6 = new DataGridViewTextBoxColumn();
      this.a_spec_item_index7 = new DataGridViewTextBoxColumn();
      this.a_spec_item_index8 = new DataGridViewTextBoxColumn();
      this.a_spec_item_index9 = new DataGridViewTextBoxColumn();
      this.a_spec_item_index10 = new DataGridViewTextBoxColumn();
      this.a_spec_item_index11 = new DataGridViewTextBoxColumn();
      this.a_spec_item_index12 = new DataGridViewTextBoxColumn();
      this.a_spec_item_index13 = new DataGridViewTextBoxColumn();
      this.a_spec_item_index14 = new DataGridViewTextBoxColumn();
      this.a_spec_min = new DataGridViewTextBoxColumn();
      this.a_spec_max = new DataGridViewTextBoxColumn();
      this.a_spec_count = new DataGridViewTextBoxColumn();
      this.a_spec_prob = new DataGridViewTextBoxColumn();
      this.a_spec_flag = new DataGridViewTextBoxColumn();
      this.tabPage5 = new TabPage();
      this.groupBox23 = new GroupBox();
      this.label192 = new Label();
      this.groupBox33 = new GroupBox();
      this.textBox225 = new TextBox();
      this.label187 = new Label();
      this.label188 = new Label();
      this.textBox251 = new TextBox();
      this.label189 = new Label();
      this.label190 = new Label();
      this.label191 = new Label();
      this.button36 = new Button();
      this.textBox252 = new TextBox();
      this.pictureBox27 = new PictureBox();
      this.button28 = new Button();
      this.button27 = new Button();
      this.textBox224 = new TextBox();
      this.label143 = new Label();
      this.groupBox35 = new GroupBox();
      this.textBox257 = new TextBox();
      this.label197 = new Label();
      this.label198 = new Label();
      this.textBox258 = new TextBox();
      this.label199 = new Label();
      this.label200 = new Label();
      this.label201 = new Label();
      this.button38 = new Button();
      this.textBox259 = new TextBox();
      this.pictureBox29 = new PictureBox();
      this.groupBox36 = new GroupBox();
      this.textBox260 = new TextBox();
      this.label202 = new Label();
      this.label203 = new Label();
      this.textBox261 = new TextBox();
      this.label204 = new Label();
      this.label205 = new Label();
      this.label206 = new Label();
      this.button39 = new Button();
      this.textBox262 = new TextBox();
      this.pictureBox30 = new PictureBox();
      this.groupBox37 = new GroupBox();
      this.textBox263 = new TextBox();
      this.label207 = new Label();
      this.label208 = new Label();
      this.textBox264 = new TextBox();
      this.label209 = new Label();
      this.label210 = new Label();
      this.label211 = new Label();
      this.button40 = new Button();
      this.textBox265 = new TextBox();
      this.pictureBox31 = new PictureBox();
      this.dgDropAllItems = new DataGridView();
      this.IconRaid = new DataGridViewImageColumn();
      this.a_npc_idx = new DataGridViewTextBoxColumn();
      this.a_item_idx = new DataGridViewTextBoxColumn();
      this.name_raid = new DataGridViewTextBoxColumn();
      this.a_prob_raid = new DataGridViewTextBoxColumn();
      this.Count = new DataGridViewTextBoxColumn();
      this.groupBox38 = new GroupBox();
      this.textBox266 = new TextBox();
      this.label212 = new Label();
      this.label213 = new Label();
      this.textBox267 = new TextBox();
      this.label214 = new Label();
      this.label215 = new Label();
      this.label216 = new Label();
      this.button41 = new Button();
      this.textBox268 = new TextBox();
      this.pictureBox32 = new PictureBox();
      this.groupBox39 = new GroupBox();
      this.textBox269 = new TextBox();
      this.label217 = new Label();
      this.label218 = new Label();
      this.textBox270 = new TextBox();
      this.label219 = new Label();
      this.label220 = new Label();
      this.label221 = new Label();
      this.button42 = new Button();
      this.textBox271 = new TextBox();
      this.pictureBox33 = new PictureBox();
      this.groupBox40 = new GroupBox();
      this.textBox272 = new TextBox();
      this.label222 = new Label();
      this.label223 = new Label();
      this.textBox273 = new TextBox();
      this.label224 = new Label();
      this.label225 = new Label();
      this.label226 = new Label();
      this.button43 = new Button();
      this.textBox274 = new TextBox();
      this.pictureBox34 = new PictureBox();
      this.groupBox41 = new GroupBox();
      this.textBox275 = new TextBox();
      this.label227 = new Label();
      this.label228 = new Label();
      this.textBox276 = new TextBox();
      this.label229 = new Label();
      this.label230 = new Label();
      this.label231 = new Label();
      this.button44 = new Button();
      this.textBox277 = new TextBox();
      this.pictureBox35 = new PictureBox();
      this.groupBox32 = new GroupBox();
      this.textBox248 = new TextBox();
      this.label182 = new Label();
      this.label183 = new Label();
      this.textBox249 = new TextBox();
      this.label184 = new Label();
      this.label185 = new Label();
      this.label186 = new Label();
      this.button35 = new Button();
      this.textBox250 = new TextBox();
      this.pictureBox26 = new PictureBox();
      this.groupBox30 = new GroupBox();
      this.textBox242 = new TextBox();
      this.label172 = new Label();
      this.label173 = new Label();
      this.textBox243 = new TextBox();
      this.label174 = new Label();
      this.label175 = new Label();
      this.label176 = new Label();
      this.button33 = new Button();
      this.textBox244 = new TextBox();
      this.pictureBox24 = new PictureBox();
      this.groupBox29 = new GroupBox();
      this.textBox239 = new TextBox();
      this.label167 = new Label();
      this.label168 = new Label();
      this.textBox240 = new TextBox();
      this.label169 = new Label();
      this.label170 = new Label();
      this.label171 = new Label();
      this.button32 = new Button();
      this.textBox241 = new TextBox();
      this.pictureBox22 = new PictureBox();
      this.groupBox31 = new GroupBox();
      this.textBox245 = new TextBox();
      this.label177 = new Label();
      this.label178 = new Label();
      this.textBox246 = new TextBox();
      this.label179 = new Label();
      this.label180 = new Label();
      this.label181 = new Label();
      this.button34 = new Button();
      this.textBox247 = new TextBox();
      this.pictureBox25 = new PictureBox();
      this.groupBox28 = new GroupBox();
      this.textBox236 = new TextBox();
      this.label162 = new Label();
      this.label163 = new Label();
      this.textBox237 = new TextBox();
      this.label164 = new Label();
      this.label165 = new Label();
      this.label166 = new Label();
      this.button31 = new Button();
      this.textBox238 = new TextBox();
      this.pictureBox21 = new PictureBox();
      this.groupBox27 = new GroupBox();
      this.textBox233 = new TextBox();
      this.label157 = new Label();
      this.label158 = new Label();
      this.textBox234 = new TextBox();
      this.label159 = new Label();
      this.label160 = new Label();
      this.label161 = new Label();
      this.button30 = new Button();
      this.textBox235 = new TextBox();
      this.pictureBox20 = new PictureBox();
      this.groupBox26 = new GroupBox();
      this.textBox230 = new TextBox();
      this.label152 = new Label();
      this.label153 = new Label();
      this.textBox231 = new TextBox();
      this.label154 = new Label();
      this.label155 = new Label();
      this.label156 = new Label();
      this.button29 = new Button();
      this.textBox232 = new TextBox();
      this.pictureBox19 = new PictureBox();
      this.groupBox25 = new GroupBox();
      this.textBox227 = new TextBox();
      this.label147 = new Label();
      this.label148 = new Label();
      this.textBox228 = new TextBox();
      this.label149 = new Label();
      this.label150 = new Label();
      this.label151 = new Label();
      this.button26 = new Button();
      this.textBox229 = new TextBox();
      this.pictureBox18 = new PictureBox();
      this.groupBox24 = new GroupBox();
      this.textBox226 = new TextBox();
      this.label146 = new Label();
      this.label145 = new Label();
      this.textBox223 = new TextBox();
      this.label144 = new Label();
      this.label142 = new Label();
      this.label141 = new Label();
      this.button25 = new Button();
      this.textBox222 = new TextBox();
      this.pictureBox17 = new PictureBox();
      this.tabPage8 = new TabPage();
      this.tabPage9 = new TabPage();
      this.clbExtra = new CheckedListBox();
      this.tbExtraFlag = new TextBox();
      this.tbZoneFlag = new TextBox();
      this.label43 = new Label();
      this.label94 = new Label();
      this.clbZone = new CheckedListBox();
      this.button2 = new Button();
      this.label2 = new Label();
      this.textBox2 = new TextBox();
      this.backgroundWorker1 = new BackgroundWorker();
      this.timer1 = new Timer(this.components);
      this.label42 = new Label();
      this.lblLang = new Label();
      this.btnSaveAndNext = new Button();
      this.BtnClearDrop = new Button();
      this.exportDropNpclodToolStripMenuItem = new ToolStripMenuItem();
      this.menuStrip1.SuspendLayout();
      this.groupBox3.SuspendLayout();
      this.groupBox5.SuspendLayout();
      this.tabControl1.SuspendLayout();
      this.tabPage1.SuspendLayout();
      this.groupBox20.SuspendLayout();
      this.slideLeftRight.BeginInit();
      this.slideUpDown.BeginInit();
      this.slideZoom.BeginInit();
      this.groupBox15.SuspendLayout();
      this.groupBox14.SuspendLayout();
      this.groupBox17.SuspendLayout();
      this.groupBox13.SuspendLayout();
      this.groupBox1.SuspendLayout();
      ((ISupportInitialize) this.pictureBox1).BeginInit();
      ((ISupportInitialize) this.pictureBox23).BeginInit();
      this.tabPage2.SuspendLayout();
      this.groupBox6.SuspendLayout();
      this.groupBox16.SuspendLayout();
      this.groupBox12.SuspendLayout();
      this.groupBox2.SuspendLayout();
      this.groupBox10.SuspendLayout();
      this.groupBox9.SuspendLayout();
      this.groupBox8.SuspendLayout();
      this.groupBox7.SuspendLayout();
      this.tabPage4.SuspendLayout();
      this.groupBox18.SuspendLayout();
      ((ISupportInitialize) this.dataGridView1).BeginInit();
      this.groupBox4.SuspendLayout();
      this.groupBox11.SuspendLayout();
      this.tabPage7.SuspendLayout();
      this.groupBox19.SuspendLayout();
      ((ISupportInitialize) this.dataGridView2).BeginInit();
      this.tabPage6.SuspendLayout();
      this.tabPage3.SuspendLayout();
      this.groupBox22.SuspendLayout();
      ((ISupportInitialize) this.pictureBox16).BeginInit();
      ((ISupportInitialize) this.pictureBox15).BeginInit();
      ((ISupportInitialize) this.pictureBox14).BeginInit();
      ((ISupportInitialize) this.pictureBox13).BeginInit();
      ((ISupportInitialize) this.pictureBox12).BeginInit();
      ((ISupportInitialize) this.pictureBox11).BeginInit();
      ((ISupportInitialize) this.pictureBox10).BeginInit();
      ((ISupportInitialize) this.pictureBox9).BeginInit();
      ((ISupportInitialize) this.pictureBox8).BeginInit();
      ((ISupportInitialize) this.pictureBox6).BeginInit();
      ((ISupportInitialize) this.pictureBox5).BeginInit();
      ((ISupportInitialize) this.pictureBox4).BeginInit();
      ((ISupportInitialize) this.pictureBox3).BeginInit();
      ((ISupportInitialize) this.pictureBox2).BeginInit();
      this.groupBox21.SuspendLayout();
      ((ISupportInitialize) this.pictureBox7).BeginInit();
      ((ISupportInitialize) this.dgRaidItems).BeginInit();
      this.tabPage5.SuspendLayout();
      this.groupBox23.SuspendLayout();
      this.groupBox33.SuspendLayout();
      ((ISupportInitialize) this.pictureBox27).BeginInit();
      this.groupBox35.SuspendLayout();
      ((ISupportInitialize) this.pictureBox29).BeginInit();
      this.groupBox36.SuspendLayout();
      ((ISupportInitialize) this.pictureBox30).BeginInit();
      this.groupBox37.SuspendLayout();
      ((ISupportInitialize) this.pictureBox31).BeginInit();
      ((ISupportInitialize) this.dgDropAllItems).BeginInit();
      this.groupBox38.SuspendLayout();
      ((ISupportInitialize) this.pictureBox32).BeginInit();
      this.groupBox39.SuspendLayout();
      ((ISupportInitialize) this.pictureBox33).BeginInit();
      this.groupBox40.SuspendLayout();
      ((ISupportInitialize) this.pictureBox34).BeginInit();
      this.groupBox41.SuspendLayout();
      ((ISupportInitialize) this.pictureBox35).BeginInit();
      this.groupBox32.SuspendLayout();
      ((ISupportInitialize) this.pictureBox26).BeginInit();
      this.groupBox30.SuspendLayout();
      ((ISupportInitialize) this.pictureBox24).BeginInit();
      this.groupBox29.SuspendLayout();
      ((ISupportInitialize) this.pictureBox22).BeginInit();
      this.groupBox31.SuspendLayout();
      ((ISupportInitialize) this.pictureBox25).BeginInit();
      this.groupBox28.SuspendLayout();
      ((ISupportInitialize) this.pictureBox21).BeginInit();
      this.groupBox27.SuspendLayout();
      ((ISupportInitialize) this.pictureBox20).BeginInit();
      this.groupBox26.SuspendLayout();
      ((ISupportInitialize) this.pictureBox19).BeginInit();
      this.groupBox25.SuspendLayout();
      ((ISupportInitialize) this.pictureBox18).BeginInit();
      this.groupBox24.SuspendLayout();
      ((ISupportInitialize) this.pictureBox17).BeginInit();
      this.tabPage9.SuspendLayout();
      this.SuspendLayout();
      this.menuStrip1.AllowMerge = false;
      this.menuStrip1.BackColor = SystemColors.ControlLightLight;
      this.menuStrip1.GripStyle = ToolStripGripStyle.Visible;
      this.menuStrip1.ImageScalingSize = new Size(20, 20);
      this.menuStrip1.Items.AddRange(new ToolStripItem[2]
      {
        (ToolStripItem) this.exportMobAlllodToolStripMenuItem,
        (ToolStripItem) this.mYSQLToolStripMenuItem
      });
      this.menuStrip1.Location = new Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new Size(1076, 28);
      this.menuStrip1.TabIndex = 0;
      this.menuStrip1.Text = "menuStrip1";
      this.exportMobAlllodToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[4]
      {
        (ToolStripItem) this.exportMobAlllodToolStripMenuItem1,
        (ToolStripItem) this.strNpcNamelodToolStripMenuItem,
        (ToolStripItem) this.exportZoneFlaglodToolStripMenuItem,
        (ToolStripItem) this.exportDropNpclodToolStripMenuItem
      });
      this.exportMobAlllodToolStripMenuItem.Name = "exportMobAlllodToolStripMenuItem";
      this.exportMobAlllodToolStripMenuItem.Size = new Size(93, 24);
      this.exportMobAlllodToolStripMenuItem.Text = "File Export";
      this.exportMobAlllodToolStripMenuItem1.Name = "exportMobAlllodToolStripMenuItem1";
      this.exportMobAlllodToolStripMenuItem1.Size = new Size(226, 26);
      this.exportMobAlllodToolStripMenuItem1.Text = "Export mobAll.lod";
      this.exportMobAlllodToolStripMenuItem1.Click += new EventHandler(this.exportMobAlllodToolStripMenuItem1_Click);
      this.strNpcNamelodToolStripMenuItem.Name = "strNpcNamelodToolStripMenuItem";
      this.strNpcNamelodToolStripMenuItem.Size = new Size(226, 26);
      this.strNpcNamelodToolStripMenuItem.Text = "StrNpcName.lod";
      this.strNpcNamelodToolStripMenuItem.Click += new EventHandler(this.strNpcNamelodToolStripMenuItem_Click);
      this.exportZoneFlaglodToolStripMenuItem.Enabled = false;
      this.exportZoneFlaglodToolStripMenuItem.Name = "exportZoneFlaglodToolStripMenuItem";
      this.exportZoneFlaglodToolStripMenuItem.Size = new Size(226, 26);
      this.exportZoneFlaglodToolStripMenuItem.Text = "Export ZoneFlag.lod";
      this.exportZoneFlaglodToolStripMenuItem.Click += new EventHandler(this.exportZoneFlaglodToolStripMenuItem_Click);
      this.mYSQLToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.massEditToolStripMenuItem
      });
      this.mYSQLToolStripMenuItem.Name = "mYSQLToolStripMenuItem";
      this.mYSQLToolStripMenuItem.Size = new Size(70, 24);
      this.mYSQLToolStripMenuItem.Text = "MYSQL";
      this.massEditToolStripMenuItem.Name = "massEditToolStripMenuItem";
      this.massEditToolStripMenuItem.Size = new Size(155, 26);
      this.massEditToolStripMenuItem.Text = "Mass Edit";
      this.massEditToolStripMenuItem.Click += new EventHandler(this.massEditToolStripMenuItem_Click);
      this.groupBox3.Controls.Add((Control) this.button4);
      this.groupBox3.Controls.Add((Control) this.button3);
      this.groupBox3.Controls.Add((Control) this.button1);
      this.groupBox3.Controls.Add((Control) this.listBox1);
      this.groupBox3.Location = new Point(12, 82);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Size = new Size(265, 610);
      this.groupBox3.TabIndex = 31;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "Monster";
      this.button4.FlatStyle = FlatStyle.Flat;
      this.button4.Location = new Point(97, 568);
      this.button4.Name = "button4";
      this.button4.Size = new Size(66, 23);
      this.button4.TabIndex = 5;
      this.button4.Text = "Copy";
      this.button4.UseVisualStyleBackColor = true;
      this.button4.Click += new EventHandler(this.button4_Click);
      this.button3.FlatStyle = FlatStyle.Flat;
      this.button3.Location = new Point(169, 568);
      this.button3.Name = "button3";
      this.button3.Size = new Size(90, 23);
      this.button3.TabIndex = 4;
      this.button3.Text = "Delete";
      this.button3.UseVisualStyleBackColor = true;
      this.button3.Click += new EventHandler(this.button3_Click);
      this.button1.FlatStyle = FlatStyle.Flat;
      this.button1.Location = new Point(6, 568);
      this.button1.Name = "button1";
      this.button1.Size = new Size(85, 23);
      this.button1.TabIndex = 2;
      this.button1.Text = "Add";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.listBox1.FormattingEnabled = true;
      this.listBox1.ItemHeight = 16;
      this.listBox1.Location = new Point(6, 19);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new Size(253, 532);
      this.listBox1.TabIndex = 1;
      this.listBox1.SelectedIndexChanged += new EventHandler(this.listBox1_SelectedIndexChanged);
      this.groupBox5.Controls.Add((Control) this.textBox200);
      this.groupBox5.Controls.Add((Control) this.label7);
      this.groupBox5.Location = new Point(12, 27);
      this.groupBox5.Name = "groupBox5";
      this.groupBox5.Size = new Size(265, 49);
      this.groupBox5.TabIndex = 32;
      this.groupBox5.TabStop = false;
      this.groupBox5.Text = "Search";
      this.textBox200.BorderStyle = BorderStyle.FixedSingle;
      this.textBox200.Location = new Point(43, 19);
      this.textBox200.Name = "textBox200";
      this.textBox200.Size = new Size(216, 22);
      this.textBox200.TabIndex = 14;
      this.textBox200.TextChanged += new EventHandler(this.textBox150_TextChanged);
      this.label7.AutoSize = true;
      this.label7.Location = new Point(6, 21);
      this.label7.Name = "label7";
      this.label7.Size = new Size(36, 16);
      this.label7.TabIndex = 21;
      this.label7.Text = "Text:";
      this.tabControl1.Controls.Add((Control) this.tabPage1);
      this.tabControl1.Controls.Add((Control) this.tabPage2);
      this.tabControl1.Controls.Add((Control) this.tabPage4);
      this.tabControl1.Controls.Add((Control) this.tabPage7);
      this.tabControl1.Controls.Add((Control) this.tabPage6);
      this.tabControl1.Controls.Add((Control) this.tabPage3);
      this.tabControl1.Controls.Add((Control) this.tabPage5);
      this.tabControl1.Controls.Add((Control) this.tabPage8);
      this.tabControl1.Controls.Add((Control) this.tabPage9);
      this.tabControl1.Location = new Point(283, 27);
      this.tabControl1.Name = "tabControl1";
      this.tabControl1.SelectedIndex = 0;
      this.tabControl1.Size = new Size(782, 636);
      this.tabControl1.TabIndex = 33;
      this.tabPage1.BorderStyle = BorderStyle.FixedSingle;
      this.tabPage1.Controls.Add((Control) this.groupBox20);
      this.tabPage1.Controls.Add((Control) this.groupBox15);
      this.tabPage1.Controls.Add((Control) this.groupBox14);
      this.tabPage1.Controls.Add((Control) this.groupBox17);
      this.tabPage1.Controls.Add((Control) this.groupBox13);
      this.tabPage1.Controls.Add((Control) this.label11);
      this.tabPage1.Controls.Add((Control) this.label6);
      this.tabPage1.Controls.Add((Control) this.textBox6);
      this.tabPage1.Controls.Add((Control) this.groupBox1);
      this.tabPage1.Controls.Add((Control) this.textBox10);
      this.tabPage1.Location = new Point(4, 25);
      this.tabPage1.Name = "tabPage1";
      this.tabPage1.Padding = new Padding(3);
      this.tabPage1.Size = new Size(774, 607);
      this.tabPage1.TabIndex = 0;
      this.tabPage1.Text = "Basic";
      this.groupBox20.Controls.Add((Control) this.chk3D);
      this.groupBox20.Controls.Add((Control) this.slideLeftRight);
      this.groupBox20.Controls.Add((Control) this.slideUpDown);
      this.groupBox20.Controls.Add((Control) this.slideZoom);
      this.groupBox20.Controls.Add((Control) this.panel3DView);
      this.groupBox20.Location = new Point(479, 275);
      this.groupBox20.Name = "groupBox20";
      this.groupBox20.Size = new Size(279, 313);
      this.groupBox20.TabIndex = 52;
      this.groupBox20.TabStop = false;
      this.groupBox20.Text = "3D View";
      this.chk3D.AutoSize = true;
      this.chk3D.Checked = true;
      this.chk3D.CheckState = CheckState.Checked;
      this.chk3D.FlatStyle = FlatStyle.Flat;
      this.chk3D.Location = new Point(180, 0);
      this.chk3D.Name = "chk3D";
      this.chk3D.Size = new Size(120, 20);
      this.chk3D.TabIndex = 38;
      this.chk3D.Text = "Enable 3D View";
      this.chk3D.UseVisualStyleBackColor = true;
      this.slideLeftRight.AutoSize = false;
      this.slideLeftRight.Location = new Point(188, 284);
      this.slideLeftRight.Maximum = 10000;
      this.slideLeftRight.Minimum = -10000;
      this.slideLeftRight.Name = "slideLeftRight";
      this.slideLeftRight.Size = new Size(85, 25);
      this.slideLeftRight.TabIndex = 3;
      this.slideLeftRight.TickStyle = TickStyle.None;
      this.slideLeftRight.Scroll += new EventHandler(this.slideLeftRight_Scroll);
      this.slideUpDown.AutoSize = false;
      this.slideUpDown.Location = new Point(95, 284);
      this.slideUpDown.Maximum = 10000;
      this.slideUpDown.Minimum = -10000;
      this.slideUpDown.Name = "slideUpDown";
      this.slideUpDown.Size = new Size(85, 25);
      this.slideUpDown.TabIndex = 2;
      this.slideUpDown.TickStyle = TickStyle.None;
      this.slideUpDown.Scroll += new EventHandler(this.slideUpDown_Scroll);
      this.slideZoom.AutoSize = false;
      this.slideZoom.Location = new Point(7, 284);
      this.slideZoom.Maximum = 10000;
      this.slideZoom.Minimum = -10000;
      this.slideZoom.Name = "slideZoom";
      this.slideZoom.Size = new Size(85, 25);
      this.slideZoom.TabIndex = 1;
      this.slideZoom.TickStyle = TickStyle.None;
      this.slideZoom.Scroll += new EventHandler(this.slideZoom_Scroll);
      this.panel3DView.Location = new Point(7, 20);
      this.panel3DView.Name = "panel3DView";
      this.panel3DView.Size = new Size(266, 258);
      this.panel3DView.TabIndex = 0;
      this.groupBox15.Controls.Add((Control) this.label70);
      this.groupBox15.Controls.Add((Control) this.label69);
      this.groupBox15.Controls.Add((Control) this.textBox107);
      this.groupBox15.Controls.Add((Control) this.textBox106);
      this.groupBox15.Controls.Add((Control) this.textBox105);
      this.groupBox15.Controls.Add((Control) this.label68);
      this.groupBox15.Location = new Point(253, 433);
      this.groupBox15.Name = "groupBox15";
      this.groupBox15.Size = new Size(220, 155);
      this.groupBox15.TabIndex = 51;
      this.groupBox15.TabStop = false;
      this.groupBox15.Text = "Effect";
      this.label70.AutoSize = true;
      this.label70.Location = new Point(10, 70);
      this.label70.Name = "label70";
      this.label70.Size = new Size(53, 16);
      this.label70.TabIndex = 58;
      this.label70.Text = "Effect 1:";
      this.label69.AutoSize = true;
      this.label69.Location = new Point(10, 98);
      this.label69.Name = "label69";
      this.label69.Size = new Size(53, 16);
      this.label69.TabIndex = 57;
      this.label69.Text = "Effect 2:";
      this.textBox107.BorderStyle = BorderStyle.FixedSingle;
      this.textBox107.Location = new Point(84, 96);
      this.textBox107.Name = "textBox107";
      this.textBox107.Size = new Size(121, 22);
      this.textBox107.TabIndex = 56;
      this.textBox106.BorderStyle = BorderStyle.FixedSingle;
      this.textBox106.Location = new Point(84, 63);
      this.textBox106.Name = "textBox106";
      this.textBox106.Size = new Size(121, 22);
      this.textBox106.TabIndex = 55;
      this.textBox105.BorderStyle = BorderStyle.FixedSingle;
      this.textBox105.Location = new Point(84, 28);
      this.textBox105.Name = "textBox105";
      this.textBox105.Size = new Size(121, 22);
      this.textBox105.TabIndex = 54;
      this.label68.AutoSize = true;
      this.label68.Location = new Point(10, 30);
      this.label68.Name = "label68";
      this.label68.Size = new Size(53, 16);
      this.label68.TabIndex = 49;
      this.label68.Text = "Effect 0:";
      this.groupBox14.Controls.Add((Control) this.label72);
      this.groupBox14.Controls.Add((Control) this.textBox109);
      this.groupBox14.Controls.Add((Control) this.label71);
      this.groupBox14.Controls.Add((Control) this.textBox108);
      this.groupBox14.Controls.Add((Control) this.textBox104);
      this.groupBox14.Controls.Add((Control) this.textBox103);
      this.groupBox14.Controls.Add((Control) this.textBox102);
      this.groupBox14.Controls.Add((Control) this.textBox101);
      this.groupBox14.Controls.Add((Control) this.textBox100);
      this.groupBox14.Controls.Add((Control) this.label67);
      this.groupBox14.Controls.Add((Control) this.label63);
      this.groupBox14.Controls.Add((Control) this.label66);
      this.groupBox14.Controls.Add((Control) this.label64);
      this.groupBox14.Controls.Add((Control) this.label65);
      this.groupBox14.Location = new Point(253, 194);
      this.groupBox14.Name = "groupBox14";
      this.groupBox14.Size = new Size(220, 233);
      this.groupBox14.TabIndex = 50;
      this.groupBox14.TabStop = false;
      this.groupBox14.Text = "Fire";
      this.label72.AutoSize = true;
      this.label72.Location = new Point(10, 201);
      this.label72.Name = "label72";
      this.label72.Size = new Size(51, 16);
      this.label72.TabIndex = 57;
      this.label72.Text = "Speed:";
      this.textBox109.BorderStyle = BorderStyle.FixedSingle;
      this.textBox109.Location = new Point(84, 198);
      this.textBox109.Name = "textBox109";
      this.textBox109.Size = new Size(121, 22);
      this.textBox109.TabIndex = 56;
      this.label71.AutoSize = true;
      this.label71.Location = new Point(10, 173);
      this.label71.Name = "label71";
      this.label71.Size = new Size(49, 16);
      this.label71.TabIndex = 55;
      this.label71.Text = "Object:";
      this.textBox108.BorderStyle = BorderStyle.FixedSingle;
      this.textBox108.Location = new Point(84, 169);
      this.textBox108.Name = "textBox108";
      this.textBox108.Size = new Size(121, 22);
      this.textBox108.TabIndex = 54;
      this.textBox104.BorderStyle = BorderStyle.FixedSingle;
      this.textBox104.Location = new Point(84, 140);
      this.textBox104.Name = "textBox104";
      this.textBox104.Size = new Size(121, 22);
      this.textBox104.TabIndex = 53;
      this.textBox103.BorderStyle = BorderStyle.FixedSingle;
      this.textBox103.Location = new Point(84, 111);
      this.textBox103.Name = "textBox103";
      this.textBox103.Size = new Size(121, 22);
      this.textBox103.TabIndex = 52;
      this.textBox102.BorderStyle = BorderStyle.FixedSingle;
      this.textBox102.Location = new Point(84, 82);
      this.textBox102.Name = "textBox102";
      this.textBox102.Size = new Size(121, 22);
      this.textBox102.TabIndex = 51;
      this.textBox101.BorderStyle = BorderStyle.FixedSingle;
      this.textBox101.Location = new Point(84, 52);
      this.textBox101.Name = "textBox101";
      this.textBox101.Size = new Size(121, 22);
      this.textBox101.TabIndex = 50;
      this.textBox100.BorderStyle = BorderStyle.FixedSingle;
      this.textBox100.Location = new Point(84, 22);
      this.textBox100.Name = "textBox100";
      this.textBox100.Size = new Size(121, 22);
      this.textBox100.TabIndex = 43;
      this.label67.AutoSize = true;
      this.label67.Location = new Point(10, 144);
      this.label67.Name = "label67";
      this.label67.Size = new Size(56, 16);
      this.label67.TabIndex = 48;
      this.label67.Text = "Delay 3:";
      this.label63.AutoSize = true;
      this.label63.Location = new Point(10, 26);
      this.label63.Name = "label63";
      this.label63.Size = new Size(83, 16);
      this.label63.TabIndex = 44;
      this.label63.Text = "Delay Count:";
      this.label66.AutoSize = true;
      this.label66.Location = new Point(10, 115);
      this.label66.Name = "label66";
      this.label66.Size = new Size(56, 16);
      this.label66.TabIndex = 47;
      this.label66.Text = "Delay 2:";
      this.label64.AutoSize = true;
      this.label64.Location = new Point(10, 56);
      this.label64.Name = "label64";
      this.label64.Size = new Size(56, 16);
      this.label64.TabIndex = 45;
      this.label64.Text = "Delay 0:";
      this.label65.AutoSize = true;
      this.label65.Location = new Point(10, 86);
      this.label65.Name = "label65";
      this.label65.Size = new Size(56, 16);
      this.label65.TabIndex = 46;
      this.label65.Text = "Delay 1:";
      this.groupBox17.Controls.Add((Control) this.textBox174);
      this.groupBox17.Controls.Add((Control) this.textBox173);
      this.groupBox17.Controls.Add((Control) this.label137);
      this.groupBox17.Controls.Add((Control) this.label136);
      this.groupBox17.Location = new Point(7, 452);
      this.groupBox17.Name = "groupBox17";
      this.groupBox17.Size = new Size(240, 95);
      this.groupBox17.TabIndex = 24;
      this.groupBox17.TabStop = false;
      this.groupBox17.Text = "RvR";
      this.textBox174.BorderStyle = BorderStyle.FixedSingle;
      this.textBox174.Location = new Point(72, 53);
      this.textBox174.Name = "textBox174";
      this.textBox174.Size = new Size(159, 22);
      this.textBox174.TabIndex = 27;
      this.textBox173.BorderStyle = BorderStyle.FixedSingle;
      this.textBox173.Location = new Point(72, 28);
      this.textBox173.Name = "textBox173";
      this.textBox173.Size = new Size(159, 22);
      this.textBox173.TabIndex = 26;
      this.label137.AutoSize = true;
      this.label137.Location = new Point(12, 55);
      this.label137.Name = "label137";
      this.label137.Size = new Size(78, 16);
      this.label137.TabIndex = 1;
      this.label137.Text = "RvR Grade:";
      this.label136.AutoSize = true;
      this.label136.Location = new Point(12, 30);
      this.label136.Name = "label136";
      this.label136.Size = new Size(75, 16);
      this.label136.TabIndex = 0;
      this.label136.Text = "RvR Value:";
      this.groupBox13.Controls.Add((Control) this.BtnAniAttack2);
      this.groupBox13.Controls.Add((Control) this.btnAniIdle2);
      this.groupBox13.Controls.Add((Control) this.btnAniRun);
      this.groupBox13.Controls.Add((Control) this.btnAniDie);
      this.groupBox13.Controls.Add((Control) this.BtnAniAttack1);
      this.groupBox13.Controls.Add((Control) this.BtnAniDam);
      this.groupBox13.Controls.Add((Control) this.BtnAniWalk);
      this.groupBox13.Controls.Add((Control) this.BtnAniIdle);
      this.groupBox13.Controls.Add((Control) this.label60);
      this.groupBox13.Controls.Add((Control) this.label59);
      this.groupBox13.Controls.Add((Control) this.label58);
      this.groupBox13.Controls.Add((Control) this.label57);
      this.groupBox13.Controls.Add((Control) this.label56);
      this.groupBox13.Controls.Add((Control) this.label55);
      this.groupBox13.Controls.Add((Control) this.label54);
      this.groupBox13.Controls.Add((Control) this.label53);
      this.groupBox13.Controls.Add((Control) this.textBox97);
      this.groupBox13.Controls.Add((Control) this.textBox96);
      this.groupBox13.Controls.Add((Control) this.textBox95);
      this.groupBox13.Controls.Add((Control) this.textBox94);
      this.groupBox13.Controls.Add((Control) this.textBox93);
      this.groupBox13.Controls.Add((Control) this.textBox92);
      this.groupBox13.Controls.Add((Control) this.textBox91);
      this.groupBox13.Controls.Add((Control) this.textBox90);
      this.groupBox13.Location = new Point(7, 194);
      this.groupBox13.Name = "groupBox13";
      this.groupBox13.Size = new Size(240, 252);
      this.groupBox13.TabIndex = 23;
      this.groupBox13.TabStop = false;
      this.groupBox13.Text = "Animations";
      this.BtnAniAttack2.BackColor = SystemColors.Control;
      this.BtnAniAttack2.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.search;
      this.BtnAniAttack2.BackgroundImageLayout = ImageLayout.Stretch;
      this.BtnAniAttack2.FlatAppearance.BorderSize = 0;
      this.BtnAniAttack2.FlatStyle = FlatStyle.Flat;
      this.BtnAniAttack2.Location = new Point(209, 206);
      this.BtnAniAttack2.Name = "BtnAniAttack2";
      this.BtnAniAttack2.Size = new Size(20, 20);
      this.BtnAniAttack2.TabIndex = 70;
      this.BtnAniAttack2.UseVisualStyleBackColor = true;
      this.BtnAniAttack2.Click += new EventHandler(this.AniFind);
      this.btnAniIdle2.BackColor = SystemColors.Control;
      this.btnAniIdle2.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.search;
      this.btnAniIdle2.BackgroundImageLayout = ImageLayout.Stretch;
      this.btnAniIdle2.FlatAppearance.BorderSize = 0;
      this.btnAniIdle2.FlatStyle = FlatStyle.Flat;
      this.btnAniIdle2.Location = new Point(209, 181);
      this.btnAniIdle2.Name = "btnAniIdle2";
      this.btnAniIdle2.Size = new Size(20, 20);
      this.btnAniIdle2.TabIndex = 69;
      this.btnAniIdle2.UseVisualStyleBackColor = true;
      this.btnAniIdle2.Click += new EventHandler(this.AniFind);
      this.btnAniRun.BackColor = SystemColors.Control;
      this.btnAniRun.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.search;
      this.btnAniRun.BackgroundImageLayout = ImageLayout.Stretch;
      this.btnAniRun.FlatAppearance.BorderSize = 0;
      this.btnAniRun.FlatStyle = FlatStyle.Flat;
      this.btnAniRun.Location = new Point(210, 158);
      this.btnAniRun.Name = "btnAniRun";
      this.btnAniRun.Size = new Size(20, 20);
      this.btnAniRun.TabIndex = 68;
      this.btnAniRun.UseVisualStyleBackColor = true;
      this.btnAniRun.Click += new EventHandler(this.AniFind);
      this.btnAniDie.BackColor = SystemColors.Control;
      this.btnAniDie.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.search;
      this.btnAniDie.BackgroundImageLayout = ImageLayout.Stretch;
      this.btnAniDie.FlatAppearance.BorderSize = 0;
      this.btnAniDie.FlatStyle = FlatStyle.Flat;
      this.btnAniDie.Location = new Point(210, 129);
      this.btnAniDie.Name = "btnAniDie";
      this.btnAniDie.Size = new Size(20, 20);
      this.btnAniDie.TabIndex = 67;
      this.btnAniDie.UseVisualStyleBackColor = true;
      this.btnAniDie.Click += new EventHandler(this.AniFind);
      this.BtnAniAttack1.BackColor = SystemColors.Control;
      this.BtnAniAttack1.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.search;
      this.BtnAniAttack1.BackgroundImageLayout = ImageLayout.Stretch;
      this.BtnAniAttack1.FlatAppearance.BorderSize = 0;
      this.BtnAniAttack1.FlatStyle = FlatStyle.Flat;
      this.BtnAniAttack1.Location = new Point(210, 103);
      this.BtnAniAttack1.Name = "BtnAniAttack1";
      this.BtnAniAttack1.Size = new Size(20, 20);
      this.BtnAniAttack1.TabIndex = 66;
      this.BtnAniAttack1.UseVisualStyleBackColor = true;
      this.BtnAniAttack1.Click += new EventHandler(this.AniFind);
      this.BtnAniDam.BackColor = SystemColors.Control;
      this.BtnAniDam.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.search;
      this.BtnAniDam.BackgroundImageLayout = ImageLayout.Stretch;
      this.BtnAniDam.FlatAppearance.BorderSize = 0;
      this.BtnAniDam.FlatStyle = FlatStyle.Flat;
      this.BtnAniDam.Location = new Point(210, 79);
      this.BtnAniDam.Name = "BtnAniDam";
      this.BtnAniDam.Size = new Size(20, 20);
      this.BtnAniDam.TabIndex = 65;
      this.BtnAniDam.UseVisualStyleBackColor = true;
      this.BtnAniDam.Click += new EventHandler(this.AniFind);
      this.BtnAniWalk.BackColor = SystemColors.Control;
      this.BtnAniWalk.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.search;
      this.BtnAniWalk.BackgroundImageLayout = ImageLayout.Stretch;
      this.BtnAniWalk.FlatAppearance.BorderSize = 0;
      this.BtnAniWalk.FlatStyle = FlatStyle.Flat;
      this.BtnAniWalk.Location = new Point(210, 52);
      this.BtnAniWalk.Name = "BtnAniWalk";
      this.BtnAniWalk.Size = new Size(20, 20);
      this.BtnAniWalk.TabIndex = 64;
      this.BtnAniWalk.UseVisualStyleBackColor = true;
      this.BtnAniWalk.Click += new EventHandler(this.AniFind);
      this.BtnAniIdle.BackColor = SystemColors.Control;
      this.BtnAniIdle.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.search;
      this.BtnAniIdle.BackgroundImageLayout = ImageLayout.Stretch;
      this.BtnAniIdle.FlatAppearance.BorderSize = 0;
      this.BtnAniIdle.FlatStyle = FlatStyle.Flat;
      this.BtnAniIdle.Location = new Point(210, 24);
      this.BtnAniIdle.Name = "BtnAniIdle";
      this.BtnAniIdle.Size = new Size(20, 20);
      this.BtnAniIdle.TabIndex = 63;
      this.BtnAniIdle.UseVisualStyleBackColor = true;
      this.BtnAniIdle.Click += new EventHandler(this.AniFind);
      this.label60.AutoSize = true;
      this.label60.Location = new Point(8, 210);
      this.label60.Name = "label60";
      this.label60.Size = new Size(57, 16);
      this.label60.TabIndex = 62;
      this.label60.Text = "Attack 2:";
      this.label59.AutoSize = true;
      this.label59.Location = new Point(8, 184);
      this.label59.Name = "label59";
      this.label59.Size = new Size(42, 16);
      this.label59.TabIndex = 61;
      this.label59.Text = "Idle 2:";
      this.label58.AutoSize = true;
      this.label58.Location = new Point(8, 158);
      this.label58.Name = "label58";
      this.label58.Size = new Size(34, 16);
      this.label58.TabIndex = 60;
      this.label58.Text = "Run:";
      this.label57.AutoSize = true;
      this.label57.Location = new Point(8, 132);
      this.label57.Name = "label57";
      this.label57.Size = new Size(31, 16);
      this.label57.TabIndex = 59;
      this.label57.Text = "Die:";
      this.label56.AutoSize = true;
      this.label56.Location = new Point(8, 106);
      this.label56.Name = "label56";
      this.label56.Size = new Size(47, 16);
      this.label56.TabIndex = 58;
      this.label56.Text = "Attack:";
      this.label55.AutoSize = true;
      this.label55.Location = new Point(8, 81);
      this.label55.Name = "label55";
      this.label55.Size = new Size(63, 16);
      this.label55.TabIndex = 57;
      this.label55.Text = "Damage:";
      this.label54.AutoSize = true;
      this.label54.Location = new Point(8, 55);
      this.label54.Name = "label54";
      this.label54.Size = new Size(41, 16);
      this.label54.TabIndex = 56;
      this.label54.Text = "Walk:";
      this.label53.AutoSize = true;
      this.label53.Location = new Point(8, 28);
      this.label53.Name = "label53";
      this.label53.Size = new Size(32, 16);
      this.label53.TabIndex = 40;
      this.label53.Text = "Idle:";
      this.textBox97.BorderStyle = BorderStyle.FixedSingle;
      this.textBox97.Location = new Point(60, 207);
      this.textBox97.Name = "textBox97";
      this.textBox97.Size = new Size(144, 22);
      this.textBox97.TabIndex = 55;
      this.textBox96.BorderStyle = BorderStyle.FixedSingle;
      this.textBox96.Location = new Point(60, 181);
      this.textBox96.Name = "textBox96";
      this.textBox96.Size = new Size(144, 22);
      this.textBox96.TabIndex = 54;
      this.textBox95.BorderStyle = BorderStyle.FixedSingle;
      this.textBox95.Location = new Point(60, 155);
      this.textBox95.Name = "textBox95";
      this.textBox95.Size = new Size(144, 22);
      this.textBox95.TabIndex = 53;
      this.textBox94.BorderStyle = BorderStyle.FixedSingle;
      this.textBox94.Location = new Point(60, 129);
      this.textBox94.Name = "textBox94";
      this.textBox94.Size = new Size(144, 22);
      this.textBox94.TabIndex = 52;
      this.textBox93.BorderStyle = BorderStyle.FixedSingle;
      this.textBox93.Location = new Point(60, 103);
      this.textBox93.Name = "textBox93";
      this.textBox93.Size = new Size(144, 22);
      this.textBox93.TabIndex = 51;
      this.textBox92.BorderStyle = BorderStyle.FixedSingle;
      this.textBox92.Location = new Point(60, 77);
      this.textBox92.Name = "textBox92";
      this.textBox92.Size = new Size(144, 22);
      this.textBox92.TabIndex = 50;
      this.textBox91.BorderStyle = BorderStyle.FixedSingle;
      this.textBox91.Location = new Point(60, 25);
      this.textBox91.Name = "textBox91";
      this.textBox91.Size = new Size(144, 22);
      this.textBox91.TabIndex = 49;
      this.textBox90.BorderStyle = BorderStyle.FixedSingle;
      this.textBox90.Location = new Point(60, 51);
      this.textBox90.Name = "textBox90";
      this.textBox90.Size = new Size(144, 22);
      this.textBox90.TabIndex = 48;
      this.label11.AutoSize = true;
      this.label11.Location = new Point(16, 553);
      this.label11.Name = "label11";
      this.label11.Size = new Size(71, 16);
      this.label11.TabIndex = 17;
      this.label11.Text = "State Flag:";
      this.label6.AutoSize = true;
      this.label6.Location = new Point(14, 582);
      this.label6.Name = "label6";
      this.label6.Size = new Size(50, 16);
      this.label6.TabIndex = 10;
      this.label6.Text = "Family:";
      this.textBox6.BorderStyle = BorderStyle.FixedSingle;
      this.textBox6.Location = new Point(81, 576);
      this.textBox6.Name = "textBox6";
      this.textBox6.Size = new Size(64, 22);
      this.textBox6.TabIndex = 9;
      this.groupBox1.Controls.Add((Control) this.cbEnabled);
      this.groupBox1.Controls.Add((Control) this.BtnReadSmc);
      this.groupBox1.Controls.Add((Control) this.pictureBox1);
      this.groupBox1.Controls.Add((Control) this.pictureBox23);
      this.groupBox1.Controls.Add((Control) this.label4);
      this.groupBox1.Controls.Add((Control) this.textBox4);
      this.groupBox1.Controls.Add((Control) this.textBox98);
      this.groupBox1.Controls.Add((Control) this.label61);
      this.groupBox1.Controls.Add((Control) this.label52);
      this.groupBox1.Controls.Add((Control) this.textBox89);
      this.groupBox1.Controls.Add((Control) this.textBox30);
      this.groupBox1.Controls.Add((Control) this.label30);
      this.groupBox1.Controls.Add((Control) this.textBox9);
      this.groupBox1.Controls.Add((Control) this.textBox29);
      this.groupBox1.Controls.Add((Control) this.textBox1);
      this.groupBox1.Controls.Add((Control) this.label10);
      this.groupBox1.Controls.Add((Control) this.label31);
      this.groupBox1.Controls.Add((Control) this.label1);
      this.groupBox1.Controls.Add((Control) this.label37);
      this.groupBox1.Controls.Add((Control) this.textBox8);
      this.groupBox1.Controls.Add((Control) this.label32);
      this.groupBox1.Controls.Add((Control) this.label9);
      this.groupBox1.Controls.Add((Control) this.textBox36);
      this.groupBox1.Controls.Add((Control) this.label33);
      this.groupBox1.Controls.Add((Control) this.label36);
      this.groupBox1.Controls.Add((Control) this.textBox32);
      this.groupBox1.Controls.Add((Control) this.textBox35);
      this.groupBox1.Controls.Add((Control) this.textBox31);
      this.groupBox1.Controls.Add((Control) this.comboBox1);
      this.groupBox1.Controls.Add((Control) this.label17);
      this.groupBox1.Controls.Add((Control) this.label15);
      this.groupBox1.Controls.Add((Control) this.textBox16);
      this.groupBox1.Controls.Add((Control) this.textBox14);
      this.groupBox1.Controls.Add((Control) this.label8);
      this.groupBox1.Controls.Add((Control) this.textBox7);
      this.groupBox1.Controls.Add((Control) this.textBox5);
      this.groupBox1.Controls.Add((Control) this.textBox3);
      this.groupBox1.Controls.Add((Control) this.label3);
      this.groupBox1.Controls.Add((Control) this.label5);
      this.groupBox1.Location = new Point(7, 6);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(751, 182);
      this.groupBox1.TabIndex = 8;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Basic";
      this.cbEnabled.AutoSize = true;
      this.cbEnabled.BackColor = Color.Chartreuse;
      this.cbEnabled.Location = new Point(295, 22);
      this.cbEnabled.Name = "cbEnabled";
      this.cbEnabled.Size = new Size(80, 20);
      this.cbEnabled.TabIndex = 72;
      this.cbEnabled.Text = "Enabled";
      this.cbEnabled.UseVisualStyleBackColor = false;
      this.cbEnabled.CheckedChanged += new EventHandler(this.cbEnabled_CheckedChanged);
      this.BtnReadSmc.BackColor = SystemColors.Control;
      this.BtnReadSmc.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.search;
      this.BtnReadSmc.BackgroundImageLayout = ImageLayout.Stretch;
      this.BtnReadSmc.FlatAppearance.BorderSize = 0;
      this.BtnReadSmc.FlatStyle = FlatStyle.Flat;
      this.BtnReadSmc.Location = new Point(728, 137);
      this.BtnReadSmc.Name = "BtnReadSmc";
      this.BtnReadSmc.Size = new Size(20, 20);
      this.BtnReadSmc.TabIndex = 71;
      this.BtnReadSmc.UseVisualStyleBackColor = true;
      this.BtnReadSmc.Click += new EventHandler(this.BtnReadSmc_Click);
      this.pictureBox1.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.Flag;
      this.pictureBox1.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox1.Location = new Point(561, 76);
      this.pictureBox1.Name = "pictureBox1";
      this.pictureBox1.Size = new Size(19, 24);
      this.pictureBox1.TabIndex = 43;
      this.pictureBox1.TabStop = false;
      this.pictureBox1.Tag = (object) "a";
      this.pictureBox1.Click += new EventHandler(this.pictureBox1_Click);
      this.pictureBox23.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.Flag;
      this.pictureBox23.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox23.Location = new Point(561, 46);
      this.pictureBox23.Name = "pictureBox23";
      this.pictureBox23.Size = new Size(19, 24);
      this.pictureBox23.TabIndex = 42;
      this.pictureBox23.TabStop = false;
      this.pictureBox23.Tag = (object) "a";
      this.pictureBox23.Click += new EventHandler(this.pictureBox23_Click);
      this.label4.AutoSize = true;
      this.label4.Location = new Point(7, 50);
      this.label4.Name = "label4";
      this.label4.Size = new Size(46, 16);
      this.label4.TabIndex = 35;
      this.label4.Text = "Descr:";
      this.textBox4.BorderStyle = BorderStyle.FixedSingle;
      this.textBox4.Location = new Point(82, 45);
      this.textBox4.Multiline = true;
      this.textBox4.Name = "textBox4";
      this.textBox4.Size = new Size(207, 19);
      this.textBox4.TabIndex = 18;
      this.textBox98.BorderStyle = BorderStyle.FixedSingle;
      this.textBox98.Location = new Point(491, 105);
      this.textBox98.Name = "textBox98";
      this.textBox98.Size = new Size(64, 22);
      this.textBox98.TabIndex = 41;
      this.label61.AutoSize = true;
      this.label61.Location = new Point(426, 109);
      this.label61.Name = "label61";
      this.label61.Size = new Size(45, 16);
      this.label61.TabIndex = 40;
      this.label61.Text = "Scale:";
      this.label52.AutoSize = true;
      this.label52.Location = new Point(425, 141);
      this.label52.Name = "label52";
      this.label52.Size = new Size(39, 16);
      this.label52.TabIndex = 39;
      this.label52.Text = "SMC:";
      this.textBox89.BorderStyle = BorderStyle.FixedSingle;
      this.textBox89.Location = new Point(464, 137);
      this.textBox89.Name = "textBox89";
      this.textBox89.Size = new Size(263, 22);
      this.textBox89.TabIndex = 38;
      this.textBox30.BorderStyle = BorderStyle.FixedSingle;
      this.textBox30.Location = new Point(612, 18);
      this.textBox30.Name = "textBox30";
      this.textBox30.Size = new Size(64, 22);
      this.textBox30.TabIndex = 25;
      this.label30.AutoSize = true;
      this.label30.Location = new Point(424, 22);
      this.label30.Name = "label30";
      this.label30.Size = new Size(29, 16);
      this.label30.TabIndex = 24;
      this.label30.Text = "HP:";
      this.textBox9.BorderStyle = BorderStyle.FixedSingle;
      this.textBox9.Location = new Point(491, 77);
      this.textBox9.Name = "textBox9";
      this.textBox9.Size = new Size(64, 22);
      this.textBox9.TabIndex = 12;
      this.textBox29.BorderStyle = BorderStyle.FixedSingle;
      this.textBox29.Location = new Point(491, 18);
      this.textBox29.Name = "textBox29";
      this.textBox29.Size = new Size(64, 22);
      this.textBox29.TabIndex = 23;
      this.textBox1.BorderStyle = BorderStyle.FixedSingle;
      this.textBox1.Location = new Point(82, 72);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(49, 22);
      this.textBox1.TabIndex = 36;
      this.label10.AutoSize = true;
      this.label10.Location = new Point(424, 80);
      this.label10.Name = "label10";
      this.label10.Size = new Size(47, 16);
      this.label10.TabIndex = 14;
      this.label10.Text = "Flag 2:";
      this.label31.AutoSize = true;
      this.label31.Location = new Point(580, 22);
      this.label31.Name = "label31";
      this.label31.Size = new Size(30, 16);
      this.label31.TabIndex = 26;
      this.label31.Text = "MP:";
      this.label1.AutoSize = true;
      this.label1.Location = new Point(7, 76);
      this.label1.Name = "label1";
      this.label1.Size = new Size(23, 16);
      this.label1.TabIndex = 37;
      this.label1.Text = "ID:";
      this.label37.AutoSize = true;
      this.label37.Location = new Point(161, 131);
      this.label37.Name = "label37";
      this.label37.Size = new Size(81, 16);
      this.label37.TabIndex = 26;
      this.label37.Text = "Run  Speed:";
      this.textBox8.BorderStyle = BorderStyle.FixedSingle;
      this.textBox8.Location = new Point(491, 48);
      this.textBox8.Name = "textBox8";
      this.textBox8.Size = new Size(64, 22);
      this.textBox8.TabIndex = 11;
      this.textBox8.TextChanged += new EventHandler(this.TextBox8_TextChanged);
      this.label32.AutoSize = true;
      this.label32.Location = new Point(7, 102);
      this.label32.Name = "label32";
      this.label32.Size = new Size(91, 16);
      this.label32.TabIndex = 24;
      this.label32.Text = "Attack Speed:";
      this.label9.AutoSize = true;
      this.label9.Location = new Point(424, 51);
      this.label9.Name = "label9";
      this.label9.Size = new Size(47, 16);
      this.label9.TabIndex = 13;
      this.label9.Text = "Flag 1:";
      this.textBox36.BorderStyle = BorderStyle.FixedSingle;
      this.textBox36.Location = new Point(234, (int) sbyte.MaxValue);
      this.textBox36.Name = "textBox36";
      this.textBox36.Size = new Size(55, 22);
      this.textBox36.TabIndex = 25;
      this.label33.AutoSize = true;
      this.label33.Location = new Point(7, 159);
      this.label33.Name = "label33";
      this.label33.Size = new Size(82, 16);
      this.label33.TabIndex = 27;
      this.label33.Text = "Attack Type:";
      this.label36.AutoSize = true;
      this.label36.Location = new Point(7, 131);
      this.label36.Name = "label36";
      this.label36.Size = new Size(85, 16);
      this.label36.TabIndex = 24;
      this.label36.Text = "Walk Speed:";
      this.textBox32.BorderStyle = BorderStyle.FixedSingle;
      this.textBox32.Location = new Point(82, 99);
      this.textBox32.Name = "textBox32";
      this.textBox32.Size = new Size(49, 22);
      this.textBox32.TabIndex = 23;
      this.textBox35.BorderStyle = BorderStyle.FixedSingle;
      this.textBox35.Location = new Point(82, (int) sbyte.MaxValue);
      this.textBox35.Name = "textBox35";
      this.textBox35.Size = new Size(49, 22);
      this.textBox35.TabIndex = 23;
      this.textBox31.Location = new Point(312, 154);
      this.textBox31.Name = "textBox31";
      this.textBox31.Size = new Size(21, 22);
      this.textBox31.TabIndex = 23;
      this.textBox31.Visible = false;
      this.comboBox1.FlatStyle = FlatStyle.Popup;
      this.comboBox1.FormattingEnabled = true;
      this.comboBox1.Items.AddRange(new object[4]
      {
        (object) "0 - Melee",
        (object) "1 - Ranged",
        (object) "2 - Magic",
        (object) "3 - None"
      });
      this.comboBox1.Location = new Point(82, 155);
      this.comboBox1.Name = "comboBox1";
      this.comboBox1.Size = new Size(73, 24);
      this.comboBox1.TabIndex = 24;
      this.comboBox1.SelectedIndexChanged += new EventHandler(this.comboBox1_SelectedIndexChanged);
      this.label17.AutoSize = true;
      this.label17.Location = new Point(161, 102);
      this.label17.Name = "label17";
      this.label17.Size = new Size(79, 16);
      this.label17.TabIndex = 24;
      this.label17.Text = "Attack Area:";
      this.label15.AutoSize = true;
      this.label15.Location = new Point(578, 109);
      this.label15.Name = "label15";
      this.label15.Size = new Size(36, 16);
      this.label15.TabIndex = 23;
      this.label15.Text = "Size:";
      this.textBox16.BorderStyle = BorderStyle.FixedSingle;
      this.textBox16.Location = new Point(234, 99);
      this.textBox16.Name = "textBox16";
      this.textBox16.Size = new Size(55, 22);
      this.textBox16.TabIndex = 23;
      this.textBox14.BorderStyle = BorderStyle.FixedSingle;
      this.textBox14.Location = new Point(612, 105);
      this.textBox14.Name = "textBox14";
      this.textBox14.Size = new Size(64, 22);
      this.textBox14.TabIndex = 22;
      this.label8.AutoSize = true;
      this.label8.Location = new Point(161, 144);
      this.label8.Name = "label8";
      this.label8.Size = new Size(79, 16);
      this.label8.TabIndex = 19;
      this.label8.Text = "Skill Master:";
      this.textBox7.BorderStyle = BorderStyle.FixedSingle;
      this.textBox7.Location = new Point(234, 154);
      this.textBox7.Name = "textBox7";
      this.textBox7.Size = new Size(55, 22);
      this.textBox7.TabIndex = 18;
      this.textBox5.BorderStyle = BorderStyle.FixedSingle;
      this.textBox5.Location = new Point(234, 70);
      this.textBox5.Name = "textBox5";
      this.textBox5.Size = new Size(55, 22);
      this.textBox5.TabIndex = 16;
      this.textBox3.BorderStyle = BorderStyle.FixedSingle;
      this.textBox3.Location = new Point(82, 20);
      this.textBox3.Name = "textBox3";
      this.textBox3.Size = new Size(207, 22);
      this.textBox3.TabIndex = 15;
      this.label3.AutoSize = true;
      this.label3.Location = new Point(7, 26);
      this.label3.Name = "label3";
      this.label3.Size = new Size(47, 16);
      this.label3.TabIndex = 11;
      this.label3.Text = "Name:";
      this.label5.AutoSize = true;
      this.label5.Location = new Point(161, 73);
      this.label5.Name = "label5";
      this.label5.Size = new Size(43, 16);
      this.label5.TabIndex = 12;
      this.label5.Text = "Level:";
      this.textBox10.BorderStyle = BorderStyle.FixedSingle;
      this.textBox10.Location = new Point(80, 550);
      this.textBox10.Name = "textBox10";
      this.textBox10.Size = new Size(64, 22);
      this.textBox10.TabIndex = 16;
      this.tabPage2.BorderStyle = BorderStyle.FixedSingle;
      this.tabPage2.Controls.Add((Control) this.groupBox6);
      this.tabPage2.Controls.Add((Control) this.groupBox16);
      this.tabPage2.Controls.Add((Control) this.groupBox12);
      this.tabPage2.Controls.Add((Control) this.groupBox2);
      this.tabPage2.Controls.Add((Control) this.groupBox10);
      this.tabPage2.Controls.Add((Control) this.groupBox9);
      this.tabPage2.Controls.Add((Control) this.groupBox8);
      this.tabPage2.Controls.Add((Control) this.groupBox7);
      this.tabPage2.Location = new Point(4, 25);
      this.tabPage2.Name = "tabPage2";
      this.tabPage2.Padding = new Padding(3);
      this.tabPage2.Size = new Size(774, 607);
      this.tabPage2.TabIndex = 1;
      this.tabPage2.Text = "Strength";
      this.groupBox6.Controls.Add((Control) this.label16);
      this.groupBox6.Controls.Add((Control) this.textBox15);
      this.groupBox6.Controls.Add((Control) this.label14);
      this.groupBox6.Controls.Add((Control) this.textBox13);
      this.groupBox6.Location = new Point(6, 360);
      this.groupBox6.Name = "groupBox6";
      this.groupBox6.Size = new Size(200, 89);
      this.groupBox6.TabIndex = 61;
      this.groupBox6.TabStop = false;
      this.label16.AutoSize = true;
      this.label16.Location = new Point(6, 27);
      this.label16.Name = "label16";
      this.label16.Size = new Size(76, 16);
      this.label16.TabIndex = 24;
      this.label16.Text = "Move Area:";
      this.textBox15.BorderStyle = BorderStyle.FixedSingle;
      this.textBox15.Location = new Point(80, 22);
      this.textBox15.Name = "textBox15";
      this.textBox15.Size = new Size(91, 22);
      this.textBox15.TabIndex = 23;
      this.label14.AutoSize = true;
      this.label14.Location = new Point(6, 55);
      this.label14.Name = "label14";
      this.label14.Size = new Size(40, 16);
      this.label14.TabIndex = 22;
      this.label14.Text = "Sight:";
      this.textBox13.BorderStyle = BorderStyle.FixedSingle;
      this.textBox13.Location = new Point(80, 53);
      this.textBox13.Name = "textBox13";
      this.textBox13.Size = new Size(91, 22);
      this.textBox13.TabIndex = 21;
      this.groupBox16.Controls.Add((Control) this.textBox115);
      this.groupBox16.Controls.Add((Control) this.label78);
      this.groupBox16.Controls.Add((Control) this.label77);
      this.groupBox16.Controls.Add((Control) this.textBox114);
      this.groupBox16.Controls.Add((Control) this.label76);
      this.groupBox16.Controls.Add((Control) this.textBox113);
      this.groupBox16.Controls.Add((Control) this.label75);
      this.groupBox16.Controls.Add((Control) this.textBox112);
      this.groupBox16.Controls.Add((Control) this.label74);
      this.groupBox16.Controls.Add((Control) this.textBox111);
      this.groupBox16.Controls.Add((Control) this.label73);
      this.groupBox16.Controls.Add((Control) this.textBox110);
      this.groupBox16.Controls.Add((Control) this.comboBox2);
      this.groupBox16.Location = new Point(212, 252);
      this.groupBox16.Name = "groupBox16";
      this.groupBox16.Size = new Size(242, 200);
      this.groupBox16.TabIndex = 60;
      this.groupBox16.TabStop = false;
      this.groupBox16.Text = "Al";
      this.textBox115.BorderStyle = BorderStyle.FixedSingle;
      this.textBox115.Location = new Point(82, 160);
      this.textBox115.Name = "textBox115";
      this.textBox115.Size = new Size(136, 22);
      this.textBox115.TabIndex = 68;
      this.label78.AutoSize = true;
      this.label78.Location = new Point(5, 164);
      this.label78.Name = "label78";
      this.label78.Size = new Size(90, 16);
      this.label78.TabIndex = 67;
      this.label78.Text = "Leader Count:";
      this.label77.AutoSize = true;
      this.label77.Location = new Point(5, 138);
      this.label77.Name = "label77";
      this.label77.Size = new Size(77, 16);
      this.label77.TabIndex = 66;
      this.label77.Text = "Leader IDX:";
      this.textBox114.BorderStyle = BorderStyle.FixedSingle;
      this.textBox114.Location = new Point(82, 134);
      this.textBox114.Name = "textBox114";
      this.textBox114.Size = new Size(136, 22);
      this.textBox114.TabIndex = 65;
      this.label76.AutoSize = true;
      this.label76.Location = new Point(5, 112);
      this.label76.Name = "label76";
      this.label76.Size = new Size(82, 16);
      this.label76.TabIndex = 64;
      this.label76.Text = "Summon HP";
      this.textBox113.BorderStyle = BorderStyle.FixedSingle;
      this.textBox113.Location = new Point(82, 108);
      this.textBox113.Name = "textBox113";
      this.textBox113.Size = new Size(136, 22);
      this.textBox113.TabIndex = 63;
      this.label75.AutoSize = true;
      this.label75.Location = new Point(5, 86);
      this.label75.Name = "label75";
      this.label75.Size = new Size(83, 16);
      this.label75.TabIndex = 62;
      this.label75.Text = "Leader Flag:";
      this.textBox112.BorderStyle = BorderStyle.FixedSingle;
      this.textBox112.Location = new Point(82, 82);
      this.textBox112.Name = "textBox112";
      this.textBox112.Size = new Size(136, 22);
      this.textBox112.TabIndex = 61;
      this.label74.AutoSize = true;
      this.label74.Location = new Point(5, 63);
      this.label74.Name = "label74";
      this.label74.Size = new Size(37, 16);
      this.label74.TabIndex = 60;
      this.label74.Text = "Flag:";
      this.textBox111.BorderStyle = BorderStyle.FixedSingle;
      this.textBox111.Location = new Point(82, 56);
      this.textBox111.Name = "textBox111";
      this.textBox111.Size = new Size(136, 22);
      this.textBox111.TabIndex = 41;
      this.label73.AutoSize = true;
      this.label73.Location = new Point(5, 33);
      this.label73.Name = "label73";
      this.label73.Size = new Size(54, 16);
      this.label73.TabIndex = 1;
      this.label73.Text = "Al Type";
      this.textBox110.BorderStyle = BorderStyle.FixedSingle;
      this.textBox110.Location = new Point(222, 28);
      this.textBox110.Name = "textBox110";
      this.textBox110.Size = new Size(14, 22);
      this.textBox110.TabIndex = 59;
      this.textBox110.Visible = false;
      this.comboBox2.FormattingEnabled = true;
      this.comboBox2.Items.AddRange(new object[4]
      {
        (object) "0 - NPC Normal",
        (object) "1 - NPC Tanker",
        (object) "2 - NPC Damage Dealer",
        (object) "3 - NPC Healer"
      });
      this.comboBox2.Location = new Point(59, 29);
      this.comboBox2.Name = "comboBox2";
      this.comboBox2.Size = new Size(159, 24);
      this.comboBox2.TabIndex = 0;
      this.comboBox2.SelectedIndexChanged += new EventHandler(this.comboBox2_SelectedIndexChanged);
      this.groupBox12.Controls.Add((Control) this.label51);
      this.groupBox12.Controls.Add((Control) this.label50);
      this.groupBox12.Controls.Add((Control) this.label49);
      this.groupBox12.Controls.Add((Control) this.label48);
      this.groupBox12.Controls.Add((Control) this.label47);
      this.groupBox12.Controls.Add((Control) this.textBox88);
      this.groupBox12.Controls.Add((Control) this.textBox84);
      this.groupBox12.Controls.Add((Control) this.textBox87);
      this.groupBox12.Controls.Add((Control) this.textBox85);
      this.groupBox12.Controls.Add((Control) this.textBox86);
      this.groupBox12.Location = new Point(6, 158);
      this.groupBox12.Name = "groupBox12";
      this.groupBox12.Size = new Size(200, 193);
      this.groupBox12.TabIndex = 45;
      this.groupBox12.TabStop = false;
      this.groupBox12.Text = "Product";
      this.label51.AutoSize = true;
      this.label51.Location = new Point(5, 166);
      this.label51.Name = "label51";
      this.label51.Size = new Size(66, 16);
      this.label51.TabIndex = 32;
      this.label51.Text = "Product 5:";
      this.label50.AutoSize = true;
      this.label50.Location = new Point(5, 132);
      this.label50.Name = "label50";
      this.label50.Size = new Size(66, 16);
      this.label50.TabIndex = 31;
      this.label50.Text = "Product 4:";
      this.label49.AutoSize = true;
      this.label49.Location = new Point(5, 98);
      this.label49.Name = "label49";
      this.label49.Size = new Size(66, 16);
      this.label49.TabIndex = 30;
      this.label49.Text = "Product 3:";
      this.label48.AutoSize = true;
      this.label48.Location = new Point(5, 64);
      this.label48.Name = "label48";
      this.label48.Size = new Size(66, 16);
      this.label48.TabIndex = 29;
      this.label48.Text = "Product 1:";
      this.label47.AutoSize = true;
      this.label47.Location = new Point(5, 30);
      this.label47.Name = "label47";
      this.label47.Size = new Size(66, 16);
      this.label47.TabIndex = 28;
      this.label47.Text = "Product 0:";
      this.textBox88.BorderStyle = BorderStyle.FixedSingle;
      this.textBox88.Location = new Point(76, 162);
      this.textBox88.Name = "textBox88";
      this.textBox88.Size = new Size(64, 22);
      this.textBox88.TabIndex = 27;
      this.textBox84.BorderStyle = BorderStyle.FixedSingle;
      this.textBox84.Location = new Point(76, 26);
      this.textBox84.Name = "textBox84";
      this.textBox84.Size = new Size(64, 22);
      this.textBox84.TabIndex = 23;
      this.textBox87.BorderStyle = BorderStyle.FixedSingle;
      this.textBox87.Location = new Point(76, 128);
      this.textBox87.Name = "textBox87";
      this.textBox87.Size = new Size(64, 22);
      this.textBox87.TabIndex = 26;
      this.textBox85.BorderStyle = BorderStyle.FixedSingle;
      this.textBox85.Location = new Point(76, 60);
      this.textBox85.Name = "textBox85";
      this.textBox85.Size = new Size(64, 22);
      this.textBox85.TabIndex = 24;
      this.textBox86.BorderStyle = BorderStyle.FixedSingle;
      this.textBox86.Location = new Point(76, 94);
      this.textBox86.Name = "textBox86";
      this.textBox86.Size = new Size(64, 22);
      this.textBox86.TabIndex = 25;
      this.groupBox2.BackColor = SystemColors.Control;
      this.groupBox2.Controls.Add((Control) this.label41);
      this.groupBox2.Controls.Add((Control) this.label40);
      this.groupBox2.Controls.Add((Control) this.label39);
      this.groupBox2.Controls.Add((Control) this.label38);
      this.groupBox2.Controls.Add((Control) this.textBox40);
      this.groupBox2.Controls.Add((Control) this.textBox37);
      this.groupBox2.Controls.Add((Control) this.textBox39);
      this.groupBox2.Controls.Add((Control) this.textBox38);
      this.groupBox2.Location = new Point(2, 462);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new Size(200, 144);
      this.groupBox2.TabIndex = 44;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "Skills";
      this.label41.AutoSize = true;
      this.label41.Location = new Point(10, 107);
      this.label41.Name = "label41";
      this.label41.Size = new Size(33, 16);
      this.label41.TabIndex = 47;
      this.label41.Text = "ID 3:";
      this.label40.AutoSize = true;
      this.label40.Location = new Point(10, 81);
      this.label40.Name = "label40";
      this.label40.Size = new Size(33, 16);
      this.label40.TabIndex = 46;
      this.label40.Text = "ID 2:";
      this.label39.AutoSize = true;
      this.label39.Location = new Point(10, 57);
      this.label39.Name = "label39";
      this.label39.Size = new Size(33, 16);
      this.label39.TabIndex = 45;
      this.label39.Text = "ID 1:";
      this.label38.AutoSize = true;
      this.label38.Location = new Point(10, 30);
      this.label38.Name = "label38";
      this.label38.Size = new Size(33, 16);
      this.label38.TabIndex = 44;
      this.label38.Text = "ID 0:";
      this.textBox40.Location = new Point(56, 104);
      this.textBox40.Name = "textBox40";
      this.textBox40.Size = new Size(138, 22);
      this.textBox40.TabIndex = 43;
      this.textBox37.Location = new Point(56, 27);
      this.textBox37.Name = "textBox37";
      this.textBox37.Size = new Size(138, 22);
      this.textBox37.TabIndex = 40;
      this.textBox39.Location = new Point(56, 78);
      this.textBox39.Name = "textBox39";
      this.textBox39.Size = new Size(138, 22);
      this.textBox39.TabIndex = 42;
      this.textBox38.Location = new Point(56, 52);
      this.textBox38.Name = "textBox38";
      this.textBox38.Size = new Size(138, 22);
      this.textBox38.TabIndex = 41;
      this.groupBox10.Controls.Add((Control) this.textBox34);
      this.groupBox10.Controls.Add((Control) this.label35);
      this.groupBox10.Controls.Add((Control) this.textBox33);
      this.groupBox10.Controls.Add((Control) this.label34);
      this.groupBox10.Location = new Point(458, 256);
      this.groupBox10.Name = "groupBox10";
      this.groupBox10.Size = new Size(157, 100);
      this.groupBox10.TabIndex = 39;
      this.groupBox10.TabStop = false;
      this.groupBox10.Text = "Recover HP,MP per second";
      this.textBox34.BorderStyle = BorderStyle.FixedSingle;
      this.textBox34.Location = new Point(39, 59);
      this.textBox34.Name = "textBox34";
      this.textBox34.Size = new Size(100, 22);
      this.textBox34.TabIndex = 37;
      this.label35.AutoSize = true;
      this.label35.Location = new Point(9, 65);
      this.label35.Name = "label35";
      this.label35.Size = new Size(30, 16);
      this.label35.TabIndex = 38;
      this.label35.Text = "MP:";
      this.textBox33.BorderStyle = BorderStyle.FixedSingle;
      this.textBox33.Location = new Point(39, 33);
      this.textBox33.Name = "textBox33";
      this.textBox33.Size = new Size(100, 22);
      this.textBox33.TabIndex = 35;
      this.label34.AutoSize = true;
      this.label34.Location = new Point(9, 38);
      this.label34.Name = "label34";
      this.label34.Size = new Size(29, 16);
      this.label34.TabIndex = 36;
      this.label34.Text = "HP:";
      this.groupBox9.Controls.Add((Control) this.label84);
      this.groupBox9.Controls.Add((Control) this.textBox121);
      this.groupBox9.Controls.Add((Control) this.label83);
      this.groupBox9.Controls.Add((Control) this.textBox120);
      this.groupBox9.Controls.Add((Control) this.label82);
      this.groupBox9.Controls.Add((Control) this.textBox119);
      this.groupBox9.Controls.Add((Control) this.label29);
      this.groupBox9.Controls.Add((Control) this.textBox28);
      this.groupBox9.Controls.Add((Control) this.label27);
      this.groupBox9.Controls.Add((Control) this.label26);
      this.groupBox9.Controls.Add((Control) this.textBox25);
      this.groupBox9.Controls.Add((Control) this.textBox26);
      this.groupBox9.Location = new Point(212, 6);
      this.groupBox9.Name = "groupBox9";
      this.groupBox9.Size = new Size(200, 243);
      this.groupBox9.TabIndex = 34;
      this.groupBox9.TabStop = false;
      this.groupBox9.Text = "Defense";
      this.label84.AutoSize = true;
      this.label84.Location = new Point(8, 179);
      this.label84.Name = "label84";
      this.label84.Size = new Size(84, 16);
      this.label84.TabIndex = 68;
      this.label84.Text = "Job Attribute:";
      this.textBox121.BorderStyle = BorderStyle.FixedSingle;
      this.textBox121.Location = new Point(80, 175);
      this.textBox121.Name = "textBox121";
      this.textBox121.Size = new Size(100, 22);
      this.textBox121.TabIndex = 67;
      this.label83.AutoSize = true;
      this.label83.Location = new Point(8, 148);
      this.label83.Name = "label83";
      this.label83.Size = new Size(82, 16);
      this.label83.TabIndex = 66;
      this.label83.Text = "Magic Avoid";
      this.textBox120.BorderStyle = BorderStyle.FixedSingle;
      this.textBox120.Location = new Point(80, 144);
      this.textBox120.Name = "textBox120";
      this.textBox120.Size = new Size(100, 22);
      this.textBox120.TabIndex = 65;
      this.label82.AutoSize = true;
      this.label82.Location = new Point(11, 117);
      this.label82.Name = "label82";
      this.label82.Size = new Size(52, 16);
      this.label82.TabIndex = 64;
      this.label82.Text = "Ddoge:";
      this.textBox119.BorderStyle = BorderStyle.FixedSingle;
      this.textBox119.Location = new Point(80, 113);
      this.textBox119.Name = "textBox119";
      this.textBox119.Size = new Size(100, 22);
      this.textBox119.TabIndex = 63;
      this.label29.AutoSize = true;
      this.label29.Location = new Point(11, 26);
      this.label29.Name = "label29";
      this.label29.Size = new Size(43, 16);
      this.label29.TabIndex = 40;
      this.label29.Text = "Level:";
      this.textBox28.BorderStyle = BorderStyle.FixedSingle;
      this.textBox28.Location = new Point(80, 22);
      this.textBox28.Name = "textBox28";
      this.textBox28.Size = new Size(75, 22);
      this.textBox28.TabIndex = 37;
      this.label27.AutoSize = true;
      this.label27.Location = new Point(11, 86);
      this.label27.Name = "label27";
      this.label27.Size = new Size(78, 16);
      this.label27.TabIndex = 38;
      this.label27.Text = "Resistence:";
      this.label26.AutoSize = true;
      this.label26.Location = new Point(11, 55);
      this.label26.Name = "label26";
      this.label26.Size = new Size(61, 16);
      this.label26.TabIndex = 37;
      this.label26.Text = "Defense:";
      this.textBox25.BorderStyle = BorderStyle.FixedSingle;
      this.textBox25.Location = new Point(80, 51);
      this.textBox25.Name = "textBox25";
      this.textBox25.Size = new Size(100, 22);
      this.textBox25.TabIndex = 35;
      this.textBox26.BorderStyle = BorderStyle.FixedSingle;
      this.textBox26.Location = new Point(80, 82);
      this.textBox26.Name = "textBox26";
      this.textBox26.Size = new Size(100, 22);
      this.textBox26.TabIndex = 36;
      this.groupBox8.Controls.Add((Control) this.label81);
      this.groupBox8.Controls.Add((Control) this.textBox118);
      this.groupBox8.Controls.Add((Control) this.label28);
      this.groupBox8.Controls.Add((Control) this.textBox27);
      this.groupBox8.Controls.Add((Control) this.textBox24);
      this.groupBox8.Controls.Add((Control) this.label25);
      this.groupBox8.Controls.Add((Control) this.textBox23);
      this.groupBox8.Controls.Add((Control) this.label24);
      this.groupBox8.Location = new Point(6, 6);
      this.groupBox8.Name = "groupBox8";
      this.groupBox8.Size = new Size(200, 149);
      this.groupBox8.TabIndex = 33;
      this.groupBox8.TabStop = false;
      this.groupBox8.Text = "Attack";
      this.label81.AutoSize = true;
      this.label81.Location = new Point(13, 117);
      this.label81.Name = "label81";
      this.label81.Size = new Size(26, 16);
      this.label81.TabIndex = 62;
      this.label81.Text = "Hit:";
      this.textBox118.BorderStyle = BorderStyle.FixedSingle;
      this.textBox118.Location = new Point(55, 113);
      this.textBox118.Name = "textBox118";
      this.textBox118.Size = new Size(100, 22);
      this.textBox118.TabIndex = 61;
      this.label28.AutoSize = true;
      this.label28.Location = new Point(13, 26);
      this.label28.Name = "label28";
      this.label28.Size = new Size(43, 16);
      this.label28.TabIndex = 39;
      this.label28.Text = "Level:";
      this.textBox27.BorderStyle = BorderStyle.FixedSingle;
      this.textBox27.Location = new Point(55, 22);
      this.textBox27.Name = "textBox27";
      this.textBox27.Size = new Size(75, 22);
      this.textBox27.TabIndex = 35;
      this.textBox24.BorderStyle = BorderStyle.FixedSingle;
      this.textBox24.Location = new Point(55, 82);
      this.textBox24.Name = "textBox24";
      this.textBox24.Size = new Size(100, 22);
      this.textBox24.TabIndex = 24;
      this.label25.AutoSize = true;
      this.label25.Location = new Point(8, 86);
      this.label25.Name = "label25";
      this.label25.Size = new Size(47, 16);
      this.label25.TabIndex = 28;
      this.label25.Text = "Magic:";
      this.textBox23.BorderStyle = BorderStyle.FixedSingle;
      this.textBox23.Location = new Point(55, 51);
      this.textBox23.Name = "textBox23";
      this.textBox23.Size = new Size(100, 22);
      this.textBox23.TabIndex = 23;
      this.label24.AutoSize = true;
      this.label24.Location = new Point(8, 55);
      this.label24.Name = "label24";
      this.label24.Size = new Size(47, 16);
      this.label24.TabIndex = 25;
      this.label24.Text = "Attack:";
      this.groupBox7.Controls.Add((Control) this.textBox22);
      this.groupBox7.Controls.Add((Control) this.label23);
      this.groupBox7.Controls.Add((Control) this.textBox19);
      this.groupBox7.Controls.Add((Control) this.label22);
      this.groupBox7.Controls.Add((Control) this.textBox20);
      this.groupBox7.Controls.Add((Control) this.label21);
      this.groupBox7.Controls.Add((Control) this.textBox21);
      this.groupBox7.Controls.Add((Control) this.label20);
      this.groupBox7.Location = new Point(415, 6);
      this.groupBox7.Name = "groupBox7";
      this.groupBox7.Size = new Size(169, 243);
      this.groupBox7.TabIndex = 32;
      this.groupBox7.TabStop = false;
      this.groupBox7.Text = "StatPoints";
      this.textBox22.BorderStyle = BorderStyle.FixedSingle;
      this.textBox22.Location = new Point(88, 112);
      this.textBox22.Name = "textBox22";
      this.textBox22.Size = new Size(61, 22);
      this.textBox22.TabIndex = 26;
      this.label23.AutoSize = true;
      this.label23.Location = new Point(19, 116);
      this.label23.Name = "label23";
      this.label23.Size = new Size(78, 16);
      this.label23.TabIndex = 30;
      this.label23.Text = "Constitution:";
      this.textBox19.BorderStyle = BorderStyle.FixedSingle;
      this.textBox19.Location = new Point(88, 22);
      this.textBox19.Name = "textBox19";
      this.textBox19.Size = new Size(61, 22);
      this.textBox19.TabIndex = 23;
      this.label22.AutoSize = true;
      this.label22.Location = new Point(18, 86);
      this.label22.Name = "label22";
      this.label22.Size = new Size(78, 16);
      this.label22.TabIndex = 29;
      this.label22.Text = "Intelligence:";
      this.textBox20.BorderStyle = BorderStyle.FixedSingle;
      this.textBox20.Location = new Point(88, 52);
      this.textBox20.Name = "textBox20";
      this.textBox20.Size = new Size(61, 22);
      this.textBox20.TabIndex = 24;
      this.label21.AutoSize = true;
      this.label21.Location = new Point(19, 56);
      this.label21.Name = "label21";
      this.label21.Size = new Size(62, 16);
      this.label21.TabIndex = 28;
      this.label21.Text = "Dexterity:";
      this.textBox21.BorderStyle = BorderStyle.FixedSingle;
      this.textBox21.Location = new Point(88, 82);
      this.textBox21.Name = "textBox21";
      this.textBox21.Size = new Size(61, 22);
      this.textBox21.TabIndex = 25;
      this.label20.AutoSize = true;
      this.label20.Location = new Point(19, 26);
      this.label20.Name = "label20";
      this.label20.Size = new Size(59, 16);
      this.label20.TabIndex = 27;
      this.label20.Text = "Strenght:";
      this.tabPage4.BackColor = SystemColors.Control;
      this.tabPage4.Controls.Add((Control) this.textBox60);
      this.tabPage4.Controls.Add((Control) this.textBox53);
      this.tabPage4.Controls.Add((Control) this.textBox80);
      this.tabPage4.Controls.Add((Control) this.textBox52);
      this.tabPage4.Controls.Add((Control) this.textBox79);
      this.tabPage4.Controls.Add((Control) this.textBox51);
      this.tabPage4.Controls.Add((Control) this.textBox50);
      this.tabPage4.Controls.Add((Control) this.textBox54);
      this.tabPage4.Controls.Add((Control) this.textBox78);
      this.tabPage4.Controls.Add((Control) this.textBox55);
      this.tabPage4.Controls.Add((Control) this.textBox61);
      this.tabPage4.Controls.Add((Control) this.textBox56);
      this.tabPage4.Controls.Add((Control) this.textBox41);
      this.tabPage4.Controls.Add((Control) this.textBox57);
      this.tabPage4.Controls.Add((Control) this.textBox77);
      this.tabPage4.Controls.Add((Control) this.textBox59);
      this.tabPage4.Controls.Add((Control) this.groupBox18);
      this.tabPage4.Controls.Add((Control) this.textBox58);
      this.tabPage4.Controls.Add((Control) this.textBox42);
      this.tabPage4.Controls.Add((Control) this.textBox76);
      this.tabPage4.Controls.Add((Control) this.textBox43);
      this.tabPage4.Controls.Add((Control) this.groupBox4);
      this.tabPage4.Controls.Add((Control) this.textBox75);
      this.tabPage4.Controls.Add((Control) this.textBox44);
      this.tabPage4.Controls.Add((Control) this.groupBox11);
      this.tabPage4.Controls.Add((Control) this.textBox45);
      this.tabPage4.Controls.Add((Control) this.textBox74);
      this.tabPage4.Controls.Add((Control) this.textBox70);
      this.tabPage4.Controls.Add((Control) this.textBox46);
      this.tabPage4.Controls.Add((Control) this.textBox73);
      this.tabPage4.Controls.Add((Control) this.textBox47);
      this.tabPage4.Controls.Add((Control) this.textBox69);
      this.tabPage4.Controls.Add((Control) this.textBox71);
      this.tabPage4.Controls.Add((Control) this.textBox48);
      this.tabPage4.Controls.Add((Control) this.textBox66);
      this.tabPage4.Controls.Add((Control) this.textBox49);
      this.tabPage4.Controls.Add((Control) this.textBox72);
      this.tabPage4.Controls.Add((Control) this.textBox63);
      this.tabPage4.Controls.Add((Control) this.textBox64);
      this.tabPage4.Controls.Add((Control) this.textBox67);
      this.tabPage4.Controls.Add((Control) this.textBox68);
      this.tabPage4.Controls.Add((Control) this.textBox62);
      this.tabPage4.Controls.Add((Control) this.textBox65);
      this.tabPage4.Location = new Point(4, 25);
      this.tabPage4.Name = "tabPage4";
      this.tabPage4.Padding = new Padding(3);
      this.tabPage4.Size = new Size(774, 607);
      this.tabPage4.TabIndex = 3;
      this.tabPage4.Text = "Drop List";
      this.textBox60.BorderStyle = BorderStyle.FixedSingle;
      this.textBox60.Location = new Point(586, 569);
      this.textBox60.Name = "textBox60";
      this.textBox60.Size = new Size(29, 22);
      this.textBox60.TabIndex = 73;
      this.textBox60.Visible = false;
      this.textBox53.BorderStyle = BorderStyle.FixedSingle;
      this.textBox53.Location = new Point(586, 368);
      this.textBox53.Name = "textBox53";
      this.textBox53.Size = new Size(29, 22);
      this.textBox53.TabIndex = 66;
      this.textBox53.Visible = false;
      this.textBox80.BorderStyle = BorderStyle.FixedSingle;
      this.textBox80.Location = new Point(485, 570);
      this.textBox80.Name = "textBox80";
      this.textBox80.Size = new Size(39, 22);
      this.textBox80.TabIndex = 95;
      this.textBox80.Visible = false;
      this.textBox52.BorderStyle = BorderStyle.FixedSingle;
      this.textBox52.Location = new Point(587, 340);
      this.textBox52.Name = "textBox52";
      this.textBox52.Size = new Size(28, 22);
      this.textBox52.TabIndex = 65;
      this.textBox52.Visible = false;
      this.textBox79.BorderStyle = BorderStyle.FixedSingle;
      this.textBox79.Location = new Point(485, 540);
      this.textBox79.Name = "textBox79";
      this.textBox79.Size = new Size(39, 22);
      this.textBox79.TabIndex = 94;
      this.textBox79.Visible = false;
      this.textBox51.BorderStyle = BorderStyle.FixedSingle;
      this.textBox51.Location = new Point(587, 313);
      this.textBox51.Name = "textBox51";
      this.textBox51.Size = new Size(28, 22);
      this.textBox51.TabIndex = 64;
      this.textBox51.Visible = false;
      this.textBox50.BorderStyle = BorderStyle.FixedSingle;
      this.textBox50.Location = new Point(545, 569);
      this.textBox50.Name = "textBox50";
      this.textBox50.Size = new Size(35, 22);
      this.textBox50.TabIndex = 63;
      this.textBox50.Visible = false;
      this.textBox54.BorderStyle = BorderStyle.FixedSingle;
      this.textBox54.Location = new Point(586, 397);
      this.textBox54.Name = "textBox54";
      this.textBox54.Size = new Size(29, 22);
      this.textBox54.TabIndex = 67;
      this.textBox54.Visible = false;
      this.textBox78.BorderStyle = BorderStyle.FixedSingle;
      this.textBox78.Location = new Point(485, 512);
      this.textBox78.Name = "textBox78";
      this.textBox78.Size = new Size(39, 22);
      this.textBox78.TabIndex = 93;
      this.textBox78.Visible = false;
      this.textBox55.BorderStyle = BorderStyle.FixedSingle;
      this.textBox55.Location = new Point(586, 426);
      this.textBox55.Name = "textBox55";
      this.textBox55.Size = new Size(29, 22);
      this.textBox55.TabIndex = 68;
      this.textBox55.Visible = false;
      this.textBox61.BorderStyle = BorderStyle.FixedSingle;
      this.textBox61.Location = new Point(431, 311);
      this.textBox61.Name = "textBox61";
      this.textBox61.Size = new Size(45, 22);
      this.textBox61.TabIndex = 75;
      this.textBox61.Visible = false;
      this.textBox56.BorderStyle = BorderStyle.FixedSingle;
      this.textBox56.Location = new Point(586, 454);
      this.textBox56.Name = "textBox56";
      this.textBox56.Size = new Size(29, 22);
      this.textBox56.TabIndex = 69;
      this.textBox56.Visible = false;
      this.textBox41.BorderStyle = BorderStyle.FixedSingle;
      this.textBox41.Location = new Point(545, 313);
      this.textBox41.Name = "textBox41";
      this.textBox41.Size = new Size(35, 22);
      this.textBox41.TabIndex = 54;
      this.textBox41.Visible = false;
      this.textBox57.BorderStyle = BorderStyle.FixedSingle;
      this.textBox57.Location = new Point(586, 483);
      this.textBox57.Name = "textBox57";
      this.textBox57.Size = new Size(29, 22);
      this.textBox57.TabIndex = 70;
      this.textBox57.Visible = false;
      this.textBox77.BorderStyle = BorderStyle.FixedSingle;
      this.textBox77.Location = new Point(485, 483);
      this.textBox77.Name = "textBox77";
      this.textBox77.Size = new Size(39, 22);
      this.textBox77.TabIndex = 92;
      this.textBox77.Visible = false;
      this.textBox59.BorderStyle = BorderStyle.FixedSingle;
      this.textBox59.Location = new Point(586, 541);
      this.textBox59.Name = "textBox59";
      this.textBox59.Size = new Size(29, 22);
      this.textBox59.TabIndex = 72;
      this.textBox59.Visible = false;
      this.groupBox18.Controls.Add((Control) this.dataGridView1);
      this.groupBox18.Location = new Point(6, 6);
      this.groupBox18.Name = "groupBox18";
      this.groupBox18.Size = new Size(410, 598);
      this.groupBox18.TabIndex = 100;
      this.groupBox18.TabStop = false;
      this.groupBox18.Text = "Drop Items";
      this.dataGridView1.AllowUserToAddRows = false;
      this.dataGridView1.AllowUserToDeleteRows = false;
      this.dataGridView1.BackgroundColor = SystemColors.Control;
      this.dataGridView1.BorderStyle = BorderStyle.None;
      this.dataGridView1.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dataGridView1.Columns.AddRange((DataGridViewColumn) this.Column1, (DataGridViewColumn) this.Column2, (DataGridViewColumn) this.Column3, (DataGridViewColumn) this.Column4);
      this.dataGridView1.Dock = DockStyle.Fill;
      this.dataGridView1.EditMode = DataGridViewEditMode.EditOnEnter;
      this.dataGridView1.EnableHeadersVisualStyles = false;
      this.dataGridView1.Location = new Point(3, 18);
      this.dataGridView1.Name = "dataGridView1";
      this.dataGridView1.RowHeadersVisible = false;
      this.dataGridView1.RowHeadersWidth = 51;
      this.dataGridView1.RowTemplate.Height = 32;
      this.dataGridView1.ScrollBars = ScrollBars.Vertical;
      this.dataGridView1.Size = new Size(404, 577);
      this.dataGridView1.TabIndex = 0;
      this.dataGridView1.CellContentClick += new DataGridViewCellEventHandler(this.dataGridView1_CellContentClick);
      this.dataGridView1.CellEndEdit += new DataGridViewCellEventHandler(this.dataGridView1_CellEndEdit);
      this.dataGridView1.RowLeave += new DataGridViewCellEventHandler(this.dataGridView1_RowLeave);
      this.Column1.HeaderText = "";
      this.Column1.MinimumWidth = 6;
      this.Column1.Name = "Column1";
      this.Column1.Width = 32;
      this.Column2.HeaderText = "ID";
      this.Column2.MinimumWidth = 6;
      this.Column2.Name = "Column2";
      this.Column2.Width = 50;
      this.Column3.HeaderText = "Name";
      this.Column3.MinimumWidth = 6;
      this.Column3.Name = "Column3";
      this.Column3.ReadOnly = true;
      this.Column3.Width = 200;
      this.Column4.HeaderText = "Droprate";
      this.Column4.MinimumWidth = 6;
      this.Column4.Name = "Column4";
      this.Column4.Width = 110;
      this.textBox58.BorderStyle = BorderStyle.FixedSingle;
      this.textBox58.Location = new Point(586, 513);
      this.textBox58.Name = "textBox58";
      this.textBox58.Size = new Size(29, 22);
      this.textBox58.TabIndex = 71;
      this.textBox58.Visible = false;
      this.textBox42.BorderStyle = BorderStyle.FixedSingle;
      this.textBox42.Location = new Point(545, 339);
      this.textBox42.Name = "textBox42";
      this.textBox42.Size = new Size(35, 22);
      this.textBox42.TabIndex = 55;
      this.textBox42.Visible = false;
      this.textBox76.BorderStyle = BorderStyle.FixedSingle;
      this.textBox76.Location = new Point(485, 454);
      this.textBox76.Name = "textBox76";
      this.textBox76.Size = new Size(39, 22);
      this.textBox76.TabIndex = 91;
      this.textBox76.Visible = false;
      this.textBox43.BorderStyle = BorderStyle.FixedSingle;
      this.textBox43.Location = new Point(545, 368);
      this.textBox43.Name = "textBox43";
      this.textBox43.Size = new Size(35, 22);
      this.textBox43.TabIndex = 56;
      this.textBox43.Visible = false;
      this.groupBox4.Controls.Add((Control) this.label18);
      this.groupBox4.Controls.Add((Control) this.label13);
      this.groupBox4.Controls.Add((Control) this.textBox11);
      this.groupBox4.Controls.Add((Control) this.textBox17);
      this.groupBox4.Controls.Add((Control) this.label12);
      this.groupBox4.Controls.Add((Control) this.textBox12);
      this.groupBox4.Location = new Point(422, 29);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Size = new Size(195, 138);
      this.groupBox4.TabIndex = 99;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "Prize";
      this.label18.AutoSize = true;
      this.label18.Location = new Point(8, 60);
      this.label18.Name = "label18";
      this.label18.Size = new Size(68, 16);
      this.label18.TabIndex = 25;
      this.label18.Text = "Skill Point:";
      this.label13.AutoSize = true;
      this.label13.Location = new Point(8, 87);
      this.label13.Name = "label13";
      this.label13.Size = new Size(69, 16);
      this.label13.TabIndex = 20;
      this.label13.Text = "Gold Coin:";
      this.textBox11.BorderStyle = BorderStyle.FixedSingle;
      this.textBox11.Location = new Point(83, 28);
      this.textBox11.Name = "textBox11";
      this.textBox11.Size = new Size(100, 22);
      this.textBox11.TabIndex = 16;
      this.textBox17.BorderStyle = BorderStyle.FixedSingle;
      this.textBox17.Location = new Point(83, 55);
      this.textBox17.Name = "textBox17";
      this.textBox17.Size = new Size(100, 22);
      this.textBox17.TabIndex = 23;
      this.label12.AutoSize = true;
      this.label12.Location = new Point(8, 32);
      this.label12.Name = "label12";
      this.label12.Size = new Size(78, 16);
      this.label12.TabIndex = 18;
      this.label12.Text = "Experience:";
      this.textBox12.BorderStyle = BorderStyle.FixedSingle;
      this.textBox12.Location = new Point(83, 82);
      this.textBox12.Name = "textBox12";
      this.textBox12.Size = new Size(100, 22);
      this.textBox12.TabIndex = 17;
      this.textBox75.BorderStyle = BorderStyle.FixedSingle;
      this.textBox75.Location = new Point(485, 425);
      this.textBox75.Name = "textBox75";
      this.textBox75.Size = new Size(39, 22);
      this.textBox75.TabIndex = 90;
      this.textBox75.Visible = false;
      this.textBox44.BorderStyle = BorderStyle.FixedSingle;
      this.textBox44.Location = new Point(545, 397);
      this.textBox44.Name = "textBox44";
      this.textBox44.Size = new Size(35, 22);
      this.textBox44.TabIndex = 57;
      this.textBox44.Visible = false;
      this.groupBox11.Controls.Add((Control) this.label46);
      this.groupBox11.Controls.Add((Control) this.label45);
      this.groupBox11.Controls.Add((Control) this.label44);
      this.groupBox11.Controls.Add((Control) this.textBox83);
      this.groupBox11.Controls.Add((Control) this.textBox82);
      this.groupBox11.Controls.Add((Control) this.textBox81);
      this.groupBox11.Location = new Point(422, 176);
      this.groupBox11.Name = "groupBox11";
      this.groupBox11.Size = new Size(195, 117);
      this.groupBox11.TabIndex = 98;
      this.groupBox11.TabStop = false;
      this.groupBox11.Text = "Drops";
      this.label46.AutoSize = true;
      this.label46.Location = new Point(13, 81);
      this.label46.Name = "label46";
      this.label46.Size = new Size(68, 16);
      this.label46.TabIndex = 101;
      this.label46.Text = "Prob Plus:";
      this.label45.AutoSize = true;
      this.label45.Location = new Point(13, 54);
      this.label45.Name = "label45";
      this.label45.Size = new Size(64, 16);
      this.label45.TabIndex = 100;
      this.label45.Text = "Max Plus:";
      this.label44.AutoSize = true;
      this.label44.Location = new Point(13, 28);
      this.label44.Name = "label44";
      this.label44.Size = new Size(60, 16);
      this.label44.TabIndex = 99;
      this.label44.Text = "Min Plus:";
      this.textBox83.BorderStyle = BorderStyle.FixedSingle;
      this.textBox83.Location = new Point(70, 77);
      this.textBox83.Name = "textBox83";
      this.textBox83.Size = new Size(100, 22);
      this.textBox83.TabIndex = 98;
      this.textBox82.BorderStyle = BorderStyle.FixedSingle;
      this.textBox82.Location = new Point(70, 51);
      this.textBox82.Name = "textBox82";
      this.textBox82.Size = new Size(100, 22);
      this.textBox82.TabIndex = 97;
      this.textBox81.BorderStyle = BorderStyle.FixedSingle;
      this.textBox81.Location = new Point(70, 25);
      this.textBox81.Name = "textBox81";
      this.textBox81.Size = new Size(100, 22);
      this.textBox81.TabIndex = 96;
      this.textBox45.BorderStyle = BorderStyle.FixedSingle;
      this.textBox45.Location = new Point(545, 426);
      this.textBox45.Name = "textBox45";
      this.textBox45.Size = new Size(35, 22);
      this.textBox45.TabIndex = 58;
      this.textBox45.Visible = false;
      this.textBox74.BorderStyle = BorderStyle.FixedSingle;
      this.textBox74.Location = new Point(485, 397);
      this.textBox74.Name = "textBox74";
      this.textBox74.Size = new Size(39, 22);
      this.textBox74.TabIndex = 89;
      this.textBox74.Visible = false;
      this.textBox70.BorderStyle = BorderStyle.FixedSingle;
      this.textBox70.Location = new Point(431, 571);
      this.textBox70.Name = "textBox70";
      this.textBox70.Size = new Size(45, 22);
      this.textBox70.TabIndex = 84;
      this.textBox70.Visible = false;
      this.textBox46.BorderStyle = BorderStyle.FixedSingle;
      this.textBox46.Location = new Point(545, 455);
      this.textBox46.Name = "textBox46";
      this.textBox46.Size = new Size(35, 22);
      this.textBox46.TabIndex = 59;
      this.textBox46.Visible = false;
      this.textBox73.BorderStyle = BorderStyle.FixedSingle;
      this.textBox73.Location = new Point(485, 368);
      this.textBox73.Name = "textBox73";
      this.textBox73.Size = new Size(39, 22);
      this.textBox73.TabIndex = 87;
      this.textBox73.Visible = false;
      this.textBox47.BorderStyle = BorderStyle.FixedSingle;
      this.textBox47.Location = new Point(545, 484);
      this.textBox47.Name = "textBox47";
      this.textBox47.Size = new Size(35, 22);
      this.textBox47.TabIndex = 60;
      this.textBox47.Visible = false;
      this.textBox69.BorderStyle = BorderStyle.FixedSingle;
      this.textBox69.Location = new Point(431, 542);
      this.textBox69.Name = "textBox69";
      this.textBox69.Size = new Size(45, 22);
      this.textBox69.TabIndex = 83;
      this.textBox69.Visible = false;
      this.textBox71.BorderStyle = BorderStyle.FixedSingle;
      this.textBox71.Location = new Point(485, 310);
      this.textBox71.Name = "textBox71";
      this.textBox71.Size = new Size(39, 22);
      this.textBox71.TabIndex = 85;
      this.textBox71.Visible = false;
      this.textBox48.BorderStyle = BorderStyle.FixedSingle;
      this.textBox48.Location = new Point(545, 513);
      this.textBox48.Name = "textBox48";
      this.textBox48.Size = new Size(35, 22);
      this.textBox48.TabIndex = 61;
      this.textBox48.Visible = false;
      this.textBox66.BorderStyle = BorderStyle.FixedSingle;
      this.textBox66.Location = new Point(431, 455);
      this.textBox66.Name = "textBox66";
      this.textBox66.Size = new Size(45, 22);
      this.textBox66.TabIndex = 80;
      this.textBox66.Visible = false;
      this.textBox49.BorderStyle = BorderStyle.FixedSingle;
      this.textBox49.Location = new Point(545, 542);
      this.textBox49.Name = "textBox49";
      this.textBox49.Size = new Size(35, 22);
      this.textBox49.TabIndex = 62;
      this.textBox49.Visible = false;
      this.textBox72.BorderStyle = BorderStyle.FixedSingle;
      this.textBox72.Location = new Point(485, 340);
      this.textBox72.Name = "textBox72";
      this.textBox72.Size = new Size(39, 22);
      this.textBox72.TabIndex = 86;
      this.textBox72.Visible = false;
      this.textBox63.BorderStyle = BorderStyle.FixedSingle;
      this.textBox63.Location = new Point(431, 368);
      this.textBox63.Name = "textBox63";
      this.textBox63.Size = new Size(45, 22);
      this.textBox63.TabIndex = 77;
      this.textBox63.Visible = false;
      this.textBox64.BorderStyle = BorderStyle.FixedSingle;
      this.textBox64.Location = new Point(431, 397);
      this.textBox64.Name = "textBox64";
      this.textBox64.Size = new Size(45, 22);
      this.textBox64.TabIndex = 78;
      this.textBox64.Visible = false;
      this.textBox67.BorderStyle = BorderStyle.FixedSingle;
      this.textBox67.Location = new Point(431, 484);
      this.textBox67.Name = "textBox67";
      this.textBox67.Size = new Size(45, 22);
      this.textBox67.TabIndex = 81;
      this.textBox67.Visible = false;
      this.textBox68.BorderStyle = BorderStyle.FixedSingle;
      this.textBox68.Location = new Point(431, 513);
      this.textBox68.Name = "textBox68";
      this.textBox68.Size = new Size(45, 22);
      this.textBox68.TabIndex = 82;
      this.textBox68.Visible = false;
      this.textBox62.BorderStyle = BorderStyle.FixedSingle;
      this.textBox62.Location = new Point(431, 340);
      this.textBox62.Name = "textBox62";
      this.textBox62.Size = new Size(45, 22);
      this.textBox62.TabIndex = 76;
      this.textBox62.Visible = false;
      this.textBox65.BorderStyle = BorderStyle.FixedSingle;
      this.textBox65.Location = new Point(431, 426);
      this.textBox65.Name = "textBox65";
      this.textBox65.Size = new Size(45, 22);
      this.textBox65.TabIndex = 79;
      this.textBox65.Visible = false;
      this.tabPage7.BackColor = SystemColors.Control;
      this.tabPage7.Controls.Add((Control) this.groupBox19);
      this.tabPage7.Controls.Add((Control) this.textBox170);
      this.tabPage7.Controls.Add((Control) this.textBox169);
      this.tabPage7.Controls.Add((Control) this.textBox168);
      this.tabPage7.Controls.Add((Control) this.textBox167);
      this.tabPage7.Controls.Add((Control) this.textBox166);
      this.tabPage7.Controls.Add((Control) this.textBox165);
      this.tabPage7.Controls.Add((Control) this.textBox164);
      this.tabPage7.Controls.Add((Control) this.textBox163);
      this.tabPage7.Controls.Add((Control) this.textBox162);
      this.tabPage7.Controls.Add((Control) this.textBox161);
      this.tabPage7.Controls.Add((Control) this.textBox160);
      this.tabPage7.Controls.Add((Control) this.textBox159);
      this.tabPage7.Controls.Add((Control) this.textBox158);
      this.tabPage7.Controls.Add((Control) this.textBox157);
      this.tabPage7.Controls.Add((Control) this.textBox156);
      this.tabPage7.Controls.Add((Control) this.textBox155);
      this.tabPage7.Controls.Add((Control) this.textBox154);
      this.tabPage7.Controls.Add((Control) this.textBox153);
      this.tabPage7.Controls.Add((Control) this.textBox152);
      this.tabPage7.Controls.Add((Control) this.textBox151);
      this.tabPage7.Controls.Add((Control) this.textBox150);
      this.tabPage7.Controls.Add((Control) this.textBox149);
      this.tabPage7.Controls.Add((Control) this.textBox148);
      this.tabPage7.Controls.Add((Control) this.textBox147);
      this.tabPage7.Controls.Add((Control) this.textBox146);
      this.tabPage7.Controls.Add((Control) this.textBox145);
      this.tabPage7.Controls.Add((Control) this.textBox144);
      this.tabPage7.Controls.Add((Control) this.textBox143);
      this.tabPage7.Controls.Add((Control) this.textBox142);
      this.tabPage7.Controls.Add((Control) this.textBox141);
      this.tabPage7.Controls.Add((Control) this.textBox140);
      this.tabPage7.Controls.Add((Control) this.textBox139);
      this.tabPage7.Controls.Add((Control) this.textBox138);
      this.tabPage7.Controls.Add((Control) this.textBox137);
      this.tabPage7.Controls.Add((Control) this.textBox136);
      this.tabPage7.Controls.Add((Control) this.textBox135);
      this.tabPage7.Controls.Add((Control) this.textBox134);
      this.tabPage7.Controls.Add((Control) this.textBox133);
      this.tabPage7.Controls.Add((Control) this.textBox132);
      this.tabPage7.Controls.Add((Control) this.textBox131);
      this.tabPage7.Location = new Point(4, 25);
      this.tabPage7.Name = "tabPage7";
      this.tabPage7.Size = new Size(774, 607);
      this.tabPage7.TabIndex = 6;
      this.tabPage7.Text = "Jewels Drop";
      this.groupBox19.Controls.Add((Control) this.dataGridView2);
      this.groupBox19.Location = new Point(6, 6);
      this.groupBox19.Name = "groupBox19";
      this.groupBox19.Size = new Size(410, 598);
      this.groupBox19.TabIndex = 80;
      this.groupBox19.TabStop = false;
      this.groupBox19.Text = "Jewels Drop";
      this.dataGridView2.AllowUserToAddRows = false;
      this.dataGridView2.AllowUserToDeleteRows = false;
      this.dataGridView2.BackgroundColor = SystemColors.Control;
      this.dataGridView2.BorderStyle = BorderStyle.None;
      this.dataGridView2.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dataGridView2.Columns.AddRange((DataGridViewColumn) this.Column5, (DataGridViewColumn) this.Column6, (DataGridViewColumn) this.Column7, (DataGridViewColumn) this.Column8);
      this.dataGridView2.Dock = DockStyle.Fill;
      this.dataGridView2.EditMode = DataGridViewEditMode.EditOnEnter;
      this.dataGridView2.EnableHeadersVisualStyles = false;
      this.dataGridView2.Location = new Point(3, 18);
      this.dataGridView2.Name = "dataGridView2";
      this.dataGridView2.RowHeadersVisible = false;
      this.dataGridView2.RowHeadersWidth = 51;
      this.dataGridView2.RowTemplate.Height = 32;
      this.dataGridView2.ScrollBars = ScrollBars.Vertical;
      this.dataGridView2.Size = new Size(404, 577);
      this.dataGridView2.TabIndex = 1;
      this.dataGridView2.CellContentClick += new DataGridViewCellEventHandler(this.dataGridView2_CellContentClick);
      this.dataGridView2.CellEndEdit += new DataGridViewCellEventHandler(this.dataGridView2_CellEndEdit_1);
      this.Column5.HeaderText = "";
      this.Column5.MinimumWidth = 6;
      this.Column5.Name = "Column5";
      this.Column5.Width = 32;
      this.Column6.HeaderText = "ID";
      this.Column6.MinimumWidth = 6;
      this.Column6.Name = "Column6";
      this.Column6.Width = 50;
      this.Column7.HeaderText = "Name";
      this.Column7.MinimumWidth = 6;
      this.Column7.Name = "Column7";
      this.Column7.ReadOnly = true;
      this.Column7.Width = 200;
      this.Column8.HeaderText = "Droprate";
      this.Column8.MinimumWidth = 6;
      this.Column8.Name = "Column8";
      this.Column8.Width = 110;
      this.textBox170.BorderStyle = BorderStyle.FixedSingle;
      this.textBox170.Location = new Point(581, 569);
      this.textBox170.Name = "textBox170";
      this.textBox170.Size = new Size(29, 22);
      this.textBox170.TabIndex = 79;
      this.textBox170.Visible = false;
      this.textBox169.BorderStyle = BorderStyle.FixedSingle;
      this.textBox169.Location = new Point(581, 543);
      this.textBox169.Name = "textBox169";
      this.textBox169.Size = new Size(29, 22);
      this.textBox169.TabIndex = 78;
      this.textBox169.Visible = false;
      this.textBox168.BorderStyle = BorderStyle.FixedSingle;
      this.textBox168.Location = new Point(581, 517);
      this.textBox168.Name = "textBox168";
      this.textBox168.Size = new Size(29, 22);
      this.textBox168.TabIndex = 77;
      this.textBox168.Visible = false;
      this.textBox167.BorderStyle = BorderStyle.FixedSingle;
      this.textBox167.Location = new Point(581, 491);
      this.textBox167.Name = "textBox167";
      this.textBox167.Size = new Size(29, 22);
      this.textBox167.TabIndex = 76;
      this.textBox167.Visible = false;
      this.textBox166.BorderStyle = BorderStyle.FixedSingle;
      this.textBox166.Location = new Point(581, 465);
      this.textBox166.Name = "textBox166";
      this.textBox166.Size = new Size(29, 22);
      this.textBox166.TabIndex = 75;
      this.textBox166.Visible = false;
      this.textBox165.BorderStyle = BorderStyle.FixedSingle;
      this.textBox165.Location = new Point(581, 439);
      this.textBox165.Name = "textBox165";
      this.textBox165.Size = new Size(29, 22);
      this.textBox165.TabIndex = 74;
      this.textBox165.Visible = false;
      this.textBox164.BorderStyle = BorderStyle.FixedSingle;
      this.textBox164.Location = new Point(581, 413);
      this.textBox164.Name = "textBox164";
      this.textBox164.Size = new Size(29, 22);
      this.textBox164.TabIndex = 73;
      this.textBox164.Visible = false;
      this.textBox163.BorderStyle = BorderStyle.FixedSingle;
      this.textBox163.Location = new Point(581, 385);
      this.textBox163.Name = "textBox163";
      this.textBox163.Size = new Size(29, 22);
      this.textBox163.TabIndex = 72;
      this.textBox163.Visible = false;
      this.textBox162.BorderStyle = BorderStyle.FixedSingle;
      this.textBox162.Location = new Point(581, 359);
      this.textBox162.Name = "textBox162";
      this.textBox162.Size = new Size(29, 22);
      this.textBox162.TabIndex = 71;
      this.textBox162.Visible = false;
      this.textBox161.BorderStyle = BorderStyle.FixedSingle;
      this.textBox161.Location = new Point(581, 333);
      this.textBox161.Name = "textBox161";
      this.textBox161.Size = new Size(29, 22);
      this.textBox161.TabIndex = 70;
      this.textBox161.Visible = false;
      this.textBox160.BorderStyle = BorderStyle.FixedSingle;
      this.textBox160.Location = new Point(546, 569);
      this.textBox160.Name = "textBox160";
      this.textBox160.Size = new Size(29, 22);
      this.textBox160.TabIndex = 69;
      this.textBox160.Visible = false;
      this.textBox159.BorderStyle = BorderStyle.FixedSingle;
      this.textBox159.Location = new Point(546, 542);
      this.textBox159.Name = "textBox159";
      this.textBox159.Size = new Size(29, 22);
      this.textBox159.TabIndex = 68;
      this.textBox159.Visible = false;
      this.textBox158.BorderStyle = BorderStyle.FixedSingle;
      this.textBox158.Location = new Point(546, 516);
      this.textBox158.Name = "textBox158";
      this.textBox158.Size = new Size(29, 22);
      this.textBox158.TabIndex = 67;
      this.textBox158.Visible = false;
      this.textBox157.BorderStyle = BorderStyle.FixedSingle;
      this.textBox157.Location = new Point(546, 486);
      this.textBox157.Name = "textBox157";
      this.textBox157.Size = new Size(29, 22);
      this.textBox157.TabIndex = 66;
      this.textBox157.Visible = false;
      this.textBox156.BorderStyle = BorderStyle.FixedSingle;
      this.textBox156.Location = new Point(546, 460);
      this.textBox156.Name = "textBox156";
      this.textBox156.Size = new Size(29, 22);
      this.textBox156.TabIndex = 65;
      this.textBox156.Visible = false;
      this.textBox155.BorderStyle = BorderStyle.FixedSingle;
      this.textBox155.Location = new Point(546, 434);
      this.textBox155.Name = "textBox155";
      this.textBox155.Size = new Size(29, 22);
      this.textBox155.TabIndex = 64;
      this.textBox155.Visible = false;
      this.textBox154.BorderStyle = BorderStyle.FixedSingle;
      this.textBox154.Location = new Point(546, 407);
      this.textBox154.Name = "textBox154";
      this.textBox154.Size = new Size(29, 22);
      this.textBox154.TabIndex = 63;
      this.textBox154.Visible = false;
      this.textBox153.BorderStyle = BorderStyle.FixedSingle;
      this.textBox153.Location = new Point(546, 381);
      this.textBox153.Name = "textBox153";
      this.textBox153.Size = new Size(29, 22);
      this.textBox153.TabIndex = 62;
      this.textBox153.Visible = false;
      this.textBox152.BorderStyle = BorderStyle.FixedSingle;
      this.textBox152.Location = new Point(546, 354);
      this.textBox152.Name = "textBox152";
      this.textBox152.Size = new Size(29, 22);
      this.textBox152.TabIndex = 61;
      this.textBox152.Visible = false;
      this.textBox151.BorderStyle = BorderStyle.FixedSingle;
      this.textBox151.Location = new Point(546, 329);
      this.textBox151.Name = "textBox151";
      this.textBox151.Size = new Size(29, 22);
      this.textBox151.TabIndex = 60;
      this.textBox151.Visible = false;
      this.textBox150.BorderStyle = BorderStyle.FixedSingle;
      this.textBox150.Location = new Point(581, 239);
      this.textBox150.Name = "textBox150";
      this.textBox150.Size = new Size(24, 22);
      this.textBox150.TabIndex = 39;
      this.textBox150.Visible = false;
      this.textBox149.BorderStyle = BorderStyle.FixedSingle;
      this.textBox149.Location = new Point(581, 213);
      this.textBox149.Name = "textBox149";
      this.textBox149.Size = new Size(24, 22);
      this.textBox149.TabIndex = 38;
      this.textBox149.Visible = false;
      this.textBox148.BorderStyle = BorderStyle.FixedSingle;
      this.textBox148.Location = new Point(581, 187);
      this.textBox148.Name = "textBox148";
      this.textBox148.Size = new Size(24, 22);
      this.textBox148.TabIndex = 37;
      this.textBox148.Visible = false;
      this.textBox147.BorderStyle = BorderStyle.FixedSingle;
      this.textBox147.Location = new Point(581, 161);
      this.textBox147.Name = "textBox147";
      this.textBox147.Size = new Size(24, 22);
      this.textBox147.TabIndex = 36;
      this.textBox147.Visible = false;
      this.textBox146.BorderStyle = BorderStyle.FixedSingle;
      this.textBox146.Location = new Point(581, 135);
      this.textBox146.Name = "textBox146";
      this.textBox146.Size = new Size(24, 22);
      this.textBox146.TabIndex = 35;
      this.textBox146.Visible = false;
      this.textBox145.BorderStyle = BorderStyle.FixedSingle;
      this.textBox145.Location = new Point(581, 109);
      this.textBox145.Name = "textBox145";
      this.textBox145.Size = new Size(24, 22);
      this.textBox145.TabIndex = 34;
      this.textBox145.Visible = false;
      this.textBox144.BorderStyle = BorderStyle.FixedSingle;
      this.textBox144.Location = new Point(581, 83);
      this.textBox144.Name = "textBox144";
      this.textBox144.Size = new Size(24, 22);
      this.textBox144.TabIndex = 33;
      this.textBox144.Visible = false;
      this.textBox143.BorderStyle = BorderStyle.FixedSingle;
      this.textBox143.Location = new Point(581, 57);
      this.textBox143.Name = "textBox143";
      this.textBox143.Size = new Size(24, 22);
      this.textBox143.TabIndex = 32;
      this.textBox143.Visible = false;
      this.textBox142.BorderStyle = BorderStyle.FixedSingle;
      this.textBox142.Location = new Point(581, 31);
      this.textBox142.Name = "textBox142";
      this.textBox142.Size = new Size(24, 22);
      this.textBox142.TabIndex = 31;
      this.textBox142.Visible = false;
      this.textBox141.BorderStyle = BorderStyle.FixedSingle;
      this.textBox141.Location = new Point(581, 5);
      this.textBox141.Name = "textBox141";
      this.textBox141.Size = new Size(24, 22);
      this.textBox141.TabIndex = 21;
      this.textBox141.Visible = false;
      this.textBox140.BorderStyle = BorderStyle.FixedSingle;
      this.textBox140.Location = new Point(551, 239);
      this.textBox140.Name = "textBox140";
      this.textBox140.Size = new Size(24, 22);
      this.textBox140.TabIndex = 20;
      this.textBox140.Visible = false;
      this.textBox139.BorderStyle = BorderStyle.FixedSingle;
      this.textBox139.Location = new Point(551, 213);
      this.textBox139.Name = "textBox139";
      this.textBox139.Size = new Size(24, 22);
      this.textBox139.TabIndex = 19;
      this.textBox139.Visible = false;
      this.textBox138.BorderStyle = BorderStyle.FixedSingle;
      this.textBox138.Location = new Point(551, 187);
      this.textBox138.Name = "textBox138";
      this.textBox138.Size = new Size(24, 22);
      this.textBox138.TabIndex = 18;
      this.textBox138.Visible = false;
      this.textBox137.BorderStyle = BorderStyle.FixedSingle;
      this.textBox137.Location = new Point(551, 161);
      this.textBox137.Name = "textBox137";
      this.textBox137.Size = new Size(24, 22);
      this.textBox137.TabIndex = 17;
      this.textBox137.Visible = false;
      this.textBox136.BorderStyle = BorderStyle.FixedSingle;
      this.textBox136.Location = new Point(551, 135);
      this.textBox136.Name = "textBox136";
      this.textBox136.Size = new Size(24, 22);
      this.textBox136.TabIndex = 16;
      this.textBox136.Visible = false;
      this.textBox135.BorderStyle = BorderStyle.FixedSingle;
      this.textBox135.Location = new Point(551, 109);
      this.textBox135.Name = "textBox135";
      this.textBox135.Size = new Size(24, 22);
      this.textBox135.TabIndex = 15;
      this.textBox135.Visible = false;
      this.textBox134.BorderStyle = BorderStyle.FixedSingle;
      this.textBox134.Location = new Point(551, 83);
      this.textBox134.Name = "textBox134";
      this.textBox134.Size = new Size(24, 22);
      this.textBox134.TabIndex = 14;
      this.textBox134.Visible = false;
      this.textBox133.BorderStyle = BorderStyle.FixedSingle;
      this.textBox133.Location = new Point(551, 57);
      this.textBox133.Name = "textBox133";
      this.textBox133.Size = new Size(24, 22);
      this.textBox133.TabIndex = 13;
      this.textBox133.Visible = false;
      this.textBox132.BorderStyle = BorderStyle.FixedSingle;
      this.textBox132.Location = new Point(551, 31);
      this.textBox132.Name = "textBox132";
      this.textBox132.Size = new Size(24, 22);
      this.textBox132.TabIndex = 12;
      this.textBox132.Visible = false;
      this.textBox131.BorderStyle = BorderStyle.FixedSingle;
      this.textBox131.Location = new Point(551, 4);
      this.textBox131.Name = "textBox131";
      this.textBox131.Size = new Size(24, 22);
      this.textBox131.TabIndex = 11;
      this.textBox131.Visible = false;
      this.tabPage6.BackColor = SystemColors.Control;
      this.tabPage6.Controls.Add((Control) this.label62);
      this.tabPage6.Controls.Add((Control) this.textBox99);
      this.tabPage6.Controls.Add((Control) this.label19);
      this.tabPage6.Controls.Add((Control) this.textBox18);
      this.tabPage6.Controls.Add((Control) this.textBox176);
      this.tabPage6.Controls.Add((Control) this.label139);
      this.tabPage6.Controls.Add((Control) this.textBox175);
      this.tabPage6.Controls.Add((Control) this.label138);
      this.tabPage6.Controls.Add((Control) this.textBox172);
      this.tabPage6.Controls.Add((Control) this.label135);
      this.tabPage6.Controls.Add((Control) this.textBox171);
      this.tabPage6.Controls.Add((Control) this.label134);
      this.tabPage6.Controls.Add((Control) this.label93);
      this.tabPage6.Controls.Add((Control) this.textBox130);
      this.tabPage6.Controls.Add((Control) this.label92);
      this.tabPage6.Controls.Add((Control) this.textBox129);
      this.tabPage6.Controls.Add((Control) this.label91);
      this.tabPage6.Controls.Add((Control) this.textBox128);
      this.tabPage6.Controls.Add((Control) this.label90);
      this.tabPage6.Controls.Add((Control) this.textBox127);
      this.tabPage6.Controls.Add((Control) this.label89);
      this.tabPage6.Controls.Add((Control) this.textBox126);
      this.tabPage6.Controls.Add((Control) this.label88);
      this.tabPage6.Controls.Add((Control) this.textBox125);
      this.tabPage6.Controls.Add((Control) this.textBox124);
      this.tabPage6.Controls.Add((Control) this.label87);
      this.tabPage6.Controls.Add((Control) this.label86);
      this.tabPage6.Controls.Add((Control) this.label85);
      this.tabPage6.Controls.Add((Control) this.textBox123);
      this.tabPage6.Controls.Add((Control) this.textBox122);
      this.tabPage6.Controls.Add((Control) this.label80);
      this.tabPage6.Controls.Add((Control) this.label79);
      this.tabPage6.Controls.Add((Control) this.textBox117);
      this.tabPage6.Controls.Add((Control) this.textBox116);
      this.tabPage6.Location = new Point(4, 25);
      this.tabPage6.Name = "tabPage6";
      this.tabPage6.Size = new Size(774, 607);
      this.tabPage6.TabIndex = 5;
      this.tabPage6.Text = "No Idea";
      this.label62.AutoSize = true;
      this.label62.Location = new Point(391, 528);
      this.label62.Name = "label62";
      this.label62.Size = new Size(72, 16);
      this.label62.TabIndex = 100;
      this.label62.Text = "a_attribute:";
      this.textBox99.BackColor = Color.Red;
      this.textBox99.BorderStyle = BorderStyle.FixedSingle;
      this.textBox99.Location = new Point(472, 526);
      this.textBox99.Name = "textBox99";
      this.textBox99.Size = new Size(100, 22);
      this.textBox99.TabIndex = 99;
      this.label19.AutoSize = true;
      this.label19.Location = new Point(391, 568);
      this.label19.Name = "label19";
      this.label19.Size = new Size(96, 16);
      this.label19.TabIndex = 98;
      this.label19.Text = "a_sskillmaster:";
      this.textBox18.BackColor = Color.Red;
      this.textBox18.BorderStyle = BorderStyle.FixedSingle;
      this.textBox18.Location = new Point(472, 561);
      this.textBox18.Name = "textBox18";
      this.textBox18.Size = new Size(100, 22);
      this.textBox18.TabIndex = 97;
      this.textBox176.BorderStyle = BorderStyle.FixedSingle;
      this.textBox176.Location = new Point(82, 437);
      this.textBox176.Name = "textBox176";
      this.textBox176.Size = new Size(80, 22);
      this.textBox176.TabIndex = 96;
      this.label139.AutoSize = true;
      this.label139.Location = new Point(16, 439);
      this.label139.Name = "label139";
      this.label139.Size = new Size(71, 16);
      this.label139.TabIndex = 95;
      this.label139.Text = "a_life_time";
      this.textBox175.BorderStyle = BorderStyle.FixedSingle;
      this.textBox175.Location = new Point(82, 395);
      this.textBox175.Name = "textBox175";
      this.textBox175.Size = new Size(80, 22);
      this.textBox175.TabIndex = 94;
      this.label138.AutoSize = true;
      this.label138.Location = new Point(27, 397);
      this.label138.Name = "label138";
      this.label138.Size = new Size(60, 16);
      this.label138.TabIndex = 93;
      this.label138.Text = "a_bound";
      this.textBox172.BorderStyle = BorderStyle.FixedSingle;
      this.textBox172.Location = new Point(123, 320);
      this.textBox172.Name = "textBox172";
      this.textBox172.Size = new Size(80, 22);
      this.textBox172.TabIndex = 92;
      this.label135.AutoSize = true;
      this.label135.Location = new Point(16, 327);
      this.label135.Name = "label135";
      this.label135.Size = new Size(80, 16);
      this.label135.TabIndex = 91;
      this.label135.Text = "a_extra_flag";
      this.textBox171.BorderStyle = BorderStyle.FixedSingle;
      this.textBox171.Location = new Point(123, 281);
      this.textBox171.Name = "textBox171";
      this.textBox171.Size = new Size(80, 22);
      this.textBox171.TabIndex = 90;
      this.label134.AutoSize = true;
      this.label134.Location = new Point(16, 288);
      this.label134.Name = "label134";
      this.label134.Size = new Size(80, 16);
      this.label134.TabIndex = 89;
      this.label134.Text = "a_zone_flag";
      this.label93.AutoSize = true;
      this.label93.Location = new Point(16, 195);
      this.label93.Name = "label93";
      this.label93.Size = new Size(104, 16);
      this.label93.TabIndex = 88;
      this.label93.Text = "a_socketprob_3";
      this.textBox130.BorderStyle = BorderStyle.FixedSingle;
      this.textBox130.Location = new Point(123, 188);
      this.textBox130.Name = "textBox130";
      this.textBox130.Size = new Size(80, 22);
      this.textBox130.TabIndex = 87;
      this.label92.AutoSize = true;
      this.label92.Location = new Point(16, 163);
      this.label92.Name = "label92";
      this.label92.Size = new Size(104, 16);
      this.label92.TabIndex = 86;
      this.label92.Text = "a_socketprob_2";
      this.textBox129.BorderStyle = BorderStyle.FixedSingle;
      this.textBox129.Location = new Point(123, 156);
      this.textBox129.Name = "textBox129";
      this.textBox129.Size = new Size(80, 22);
      this.textBox129.TabIndex = 85;
      this.label91.AutoSize = true;
      this.label91.Location = new Point(16, 132);
      this.label91.Name = "label91";
      this.label91.Size = new Size(104, 16);
      this.label91.TabIndex = 84;
      this.label91.Text = "a_socketprob_1";
      this.textBox128.BorderStyle = BorderStyle.FixedSingle;
      this.textBox128.Location = new Point(123, 125);
      this.textBox128.Name = "textBox128";
      this.textBox128.Size = new Size(80, 22);
      this.textBox128.TabIndex = 83;
      this.label90.AutoSize = true;
      this.label90.Location = new Point(16, 103);
      this.label90.Name = "label90";
      this.label90.Size = new Size(104, 16);
      this.label90.TabIndex = 82;
      this.label90.Text = "a_socketprob_0";
      this.textBox127.BorderStyle = BorderStyle.FixedSingle;
      this.textBox127.Location = new Point(123, 96);
      this.textBox127.Name = "textBox127";
      this.textBox127.Size = new Size(80, 22);
      this.textBox127.TabIndex = 81;
      this.label89.AutoSize = true;
      this.label89.Location = new Point(16, 72);
      this.label89.Name = "label89";
      this.label89.Size = new Size(91, 16);
      this.label89.TabIndex = 80;
      this.label89.Text = "a_createprob:";
      this.textBox126.BorderStyle = BorderStyle.FixedSingle;
      this.textBox126.Location = new Point(123, 70);
      this.textBox126.Name = "textBox126";
      this.textBox126.Size = new Size(80, 22);
      this.textBox126.TabIndex = 79;
      this.label88.AutoSize = true;
      this.label88.Location = new Point(365, 93);
      this.label88.Name = "label88";
      this.label88.Size = new Size(137, 16);
      this.label88.TabIndex = 78;
      this.label88.Text = "a_npc_kill_trigger_ids";
      this.textBox125.BorderStyle = BorderStyle.FixedSingle;
      this.textBox125.Location = new Point(511, 90);
      this.textBox125.Name = "textBox125";
      this.textBox125.Size = new Size(100, 22);
      this.textBox125.TabIndex = 77;
      this.textBox124.BorderStyle = BorderStyle.FixedSingle;
      this.textBox124.Location = new Point(511, 62);
      this.textBox124.Name = "textBox124";
      this.textBox124.Size = new Size(100, 22);
      this.textBox124.TabIndex = 76;
      this.label87.AutoSize = true;
      this.label87.Location = new Point(365, 65);
      this.label87.Name = "label87";
      this.label87.Size = new Size(151, 16);
      this.label87.TabIndex = 75;
      this.label87.Text = "a_npc_kill_trigger_count";
      this.label86.AutoSize = true;
      this.label86.Location = new Point(365, 41);
      this.label86.Name = "label86";
      this.label86.Size = new Size(161, 16);
      this.label86.TabIndex = 74;
      this.label86.Text = "a_npc_choice_trigger_ids";
      this.label85.AutoSize = true;
      this.label85.Location = new Point(365, 17);
      this.label85.Name = "label85";
      this.label85.Size = new Size(175, 16);
      this.label85.TabIndex = 73;
      this.label85.Text = "a_npc_choice_trigger_count";
      this.textBox123.BorderStyle = BorderStyle.FixedSingle;
      this.textBox123.Location = new Point(511, 36);
      this.textBox123.Name = "textBox123";
      this.textBox123.Size = new Size(100, 22);
      this.textBox123.TabIndex = 72;
      this.textBox122.BorderStyle = BorderStyle.FixedSingle;
      this.textBox122.Location = new Point(511, 10);
      this.textBox122.Name = "textBox122";
      this.textBox122.Size = new Size(100, 22);
      this.textBox122.TabIndex = 71;
      this.label80.AutoSize = true;
      this.label80.Location = new Point(16, 45);
      this.label80.Name = "label80";
      this.label80.Size = new Size(102, 16);
      this.label80.TabIndex = 46;
      this.label80.Text = "a_productIndex:";
      this.label79.AutoSize = true;
      this.label79.Location = new Point(16, 19);
      this.label79.Name = "label79";
      this.label79.Size = new Size(128, 16);
      this.label79.TabIndex = 45;
      this.label79.Text = "a_crafting_category:";
      this.textBox117.BorderStyle = BorderStyle.FixedSingle;
      this.textBox117.Location = new Point(123, 41);
      this.textBox117.Name = "textBox117";
      this.textBox117.Size = new Size(80, 22);
      this.textBox117.TabIndex = 41;
      this.textBox116.BorderStyle = BorderStyle.FixedSingle;
      this.textBox116.Location = new Point(123, 15);
      this.textBox116.Name = "textBox116";
      this.textBox116.Size = new Size(80, 22);
      this.textBox116.TabIndex = 40;
      this.tabPage3.Controls.Add((Control) this.button24);
      this.tabPage3.Controls.Add((Control) this.textBox221);
      this.tabPage3.Controls.Add((Control) this.textBox220);
      this.tabPage3.Controls.Add((Control) this.textBox219);
      this.tabPage3.Controls.Add((Control) this.textBox218);
      this.tabPage3.Controls.Add((Control) this.button18);
      this.tabPage3.Controls.Add((Control) this.button19);
      this.tabPage3.Controls.Add((Control) this.button6);
      this.tabPage3.Controls.Add((Control) this.button17);
      this.tabPage3.Controls.Add((Control) this.groupBox22);
      this.tabPage3.Controls.Add((Control) this.groupBox21);
      this.tabPage3.Controls.Add((Control) this.dgRaidItems);
      this.tabPage3.Location = new Point(4, 25);
      this.tabPage3.Name = "tabPage3";
      this.tabPage3.Padding = new Padding(3);
      this.tabPage3.Size = new Size(774, 607);
      this.tabPage3.TabIndex = 7;
      this.tabPage3.Text = "Drop Raid";
      this.tabPage3.UseVisualStyleBackColor = true;
      this.button24.BackColor = Color.GreenYellow;
      this.button24.FlatStyle = FlatStyle.Flat;
      this.button24.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources._08;
      this.button24.ImageAlign = ContentAlignment.MiddleLeft;
      this.button24.Location = new Point(15, 562);
      this.button24.Name = "button24";
      this.button24.Size = new Size(72, 27);
      this.button24.TabIndex = 112;
      this.button24.Text = "      Reset";
      this.button24.UseVisualStyleBackColor = false;
      this.button24.Click += new EventHandler(this.button24_Click);
      this.textBox221.Location = new Point(104, 538);
      this.textBox221.Name = "textBox221";
      this.textBox221.Size = new Size(27, 22);
      this.textBox221.TabIndex = 111;
      this.textBox221.Visible = false;
      this.textBox220.Location = new Point(70, 538);
      this.textBox220.Name = "textBox220";
      this.textBox220.Size = new Size(28, 22);
      this.textBox220.TabIndex = 110;
      this.textBox220.Visible = false;
      this.textBox219.Location = new Point(36, 538);
      this.textBox219.Name = "textBox219";
      this.textBox219.Size = new Size(28, 22);
      this.textBox219.TabIndex = 109;
      this.textBox219.Visible = false;
      this.textBox218.Location = new Point(6, 538);
      this.textBox218.Name = "textBox218";
      this.textBox218.Size = new Size(24, 22);
      this.textBox218.TabIndex = 108;
      this.textBox218.Visible = false;
      this.button18.BackColor = Color.LightCyan;
      this.button18.FlatStyle = FlatStyle.Flat;
      this.button18.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources._08;
      this.button18.ImageAlign = ContentAlignment.MiddleLeft;
      this.button18.Location = new Point(211, 562);
      this.button18.Name = "button18";
      this.button18.Size = new Size(72, 27);
      this.button18.TabIndex = 106;
      this.button18.Text = "      Update";
      this.button18.UseVisualStyleBackColor = false;
      this.button18.Click += new EventHandler(this.button18_Click);
      this.button19.BackColor = Color.Plum;
      this.button19.FlatStyle = FlatStyle.Flat;
      this.button19.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.control_add_blue;
      this.button19.ImageAlign = ContentAlignment.MiddleLeft;
      this.button19.Location = new Point(134, 562);
      this.button19.Name = "button19";
      this.button19.Size = new Size(71, 27);
      this.button19.TabIndex = 105;
      this.button19.Text = "     Add";
      this.button19.UseVisualStyleBackColor = false;
      this.button19.Click += new EventHandler(this.button19_Click);
      this.button6.BackgroundImageLayout = ImageLayout.None;
      this.button6.Location = new Point(814, 53);
      this.button6.Name = "button6";
      this.button6.Size = new Size(27, 25);
      this.button6.TabIndex = 104;
      this.button6.UseVisualStyleBackColor = true;
      this.button17.BackColor = Color.LightCoral;
      this.button17.FlatStyle = FlatStyle.Flat;
      this.button17.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.delete;
      this.button17.ImageAlign = ContentAlignment.MiddleLeft;
      this.button17.Location = new Point(289, 562);
      this.button17.Name = "button17";
      this.button17.Size = new Size(65, 27);
      this.button17.TabIndex = 107;
      this.button17.Text = "    Delete";
      this.button17.UseVisualStyleBackColor = false;
      this.button17.Click += new EventHandler(this.button17_Click);
      this.groupBox22.Controls.Add((Control) this.textBox217);
      this.groupBox22.Controls.Add((Control) this.label140);
      this.groupBox22.Controls.Add((Control) this.textBox216);
      this.groupBox22.Controls.Add((Control) this.label133);
      this.groupBox22.Controls.Add((Control) this.textBox215);
      this.groupBox22.Controls.Add((Control) this.label132);
      this.groupBox22.Controls.Add((Control) this.textBox214);
      this.groupBox22.Controls.Add((Control) this.label131);
      this.groupBox22.Controls.Add((Control) this.textBox213);
      this.groupBox22.Controls.Add((Control) this.label130);
      this.groupBox22.Controls.Add((Control) this.button23);
      this.groupBox22.Controls.Add((Control) this.pictureBox16);
      this.groupBox22.Controls.Add((Control) this.textBox211);
      this.groupBox22.Controls.Add((Control) this.label128);
      this.groupBox22.Controls.Add((Control) this.textBox212);
      this.groupBox22.Controls.Add((Control) this.label129);
      this.groupBox22.Controls.Add((Control) this.button22);
      this.groupBox22.Controls.Add((Control) this.pictureBox15);
      this.groupBox22.Controls.Add((Control) this.textBox209);
      this.groupBox22.Controls.Add((Control) this.label126);
      this.groupBox22.Controls.Add((Control) this.textBox210);
      this.groupBox22.Controls.Add((Control) this.label127);
      this.groupBox22.Controls.Add((Control) this.button21);
      this.groupBox22.Controls.Add((Control) this.pictureBox14);
      this.groupBox22.Controls.Add((Control) this.textBox207);
      this.groupBox22.Controls.Add((Control) this.label124);
      this.groupBox22.Controls.Add((Control) this.textBox208);
      this.groupBox22.Controls.Add((Control) this.label125);
      this.groupBox22.Controls.Add((Control) this.button20);
      this.groupBox22.Controls.Add((Control) this.pictureBox13);
      this.groupBox22.Controls.Add((Control) this.textBox205);
      this.groupBox22.Controls.Add((Control) this.label122);
      this.groupBox22.Controls.Add((Control) this.textBox206);
      this.groupBox22.Controls.Add((Control) this.label123);
      this.groupBox22.Controls.Add((Control) this.button16);
      this.groupBox22.Controls.Add((Control) this.pictureBox12);
      this.groupBox22.Controls.Add((Control) this.textBox203);
      this.groupBox22.Controls.Add((Control) this.label120);
      this.groupBox22.Controls.Add((Control) this.textBox204);
      this.groupBox22.Controls.Add((Control) this.label121);
      this.groupBox22.Controls.Add((Control) this.button15);
      this.groupBox22.Controls.Add((Control) this.pictureBox11);
      this.groupBox22.Controls.Add((Control) this.textBox201);
      this.groupBox22.Controls.Add((Control) this.label118);
      this.groupBox22.Controls.Add((Control) this.textBox202);
      this.groupBox22.Controls.Add((Control) this.label119);
      this.groupBox22.Controls.Add((Control) this.button14);
      this.groupBox22.Controls.Add((Control) this.pictureBox10);
      this.groupBox22.Controls.Add((Control) this.textBox198);
      this.groupBox22.Controls.Add((Control) this.label116);
      this.groupBox22.Controls.Add((Control) this.textBox199);
      this.groupBox22.Controls.Add((Control) this.label117);
      this.groupBox22.Controls.Add((Control) this.button13);
      this.groupBox22.Controls.Add((Control) this.pictureBox9);
      this.groupBox22.Controls.Add((Control) this.textBox196);
      this.groupBox22.Controls.Add((Control) this.label114);
      this.groupBox22.Controls.Add((Control) this.textBox197);
      this.groupBox22.Controls.Add((Control) this.label115);
      this.groupBox22.Controls.Add((Control) this.button12);
      this.groupBox22.Controls.Add((Control) this.pictureBox8);
      this.groupBox22.Controls.Add((Control) this.textBox194);
      this.groupBox22.Controls.Add((Control) this.label112);
      this.groupBox22.Controls.Add((Control) this.textBox195);
      this.groupBox22.Controls.Add((Control) this.label113);
      this.groupBox22.Controls.Add((Control) this.button11);
      this.groupBox22.Controls.Add((Control) this.pictureBox6);
      this.groupBox22.Controls.Add((Control) this.textBox192);
      this.groupBox22.Controls.Add((Control) this.label110);
      this.groupBox22.Controls.Add((Control) this.textBox193);
      this.groupBox22.Controls.Add((Control) this.label111);
      this.groupBox22.Controls.Add((Control) this.button10);
      this.groupBox22.Controls.Add((Control) this.pictureBox5);
      this.groupBox22.Controls.Add((Control) this.textBox190);
      this.groupBox22.Controls.Add((Control) this.label108);
      this.groupBox22.Controls.Add((Control) this.textBox191);
      this.groupBox22.Controls.Add((Control) this.label109);
      this.groupBox22.Controls.Add((Control) this.button9);
      this.groupBox22.Controls.Add((Control) this.pictureBox4);
      this.groupBox22.Controls.Add((Control) this.textBox188);
      this.groupBox22.Controls.Add((Control) this.label106);
      this.groupBox22.Controls.Add((Control) this.textBox189);
      this.groupBox22.Controls.Add((Control) this.label107);
      this.groupBox22.Controls.Add((Control) this.button8);
      this.groupBox22.Controls.Add((Control) this.pictureBox3);
      this.groupBox22.Controls.Add((Control) this.textBox186);
      this.groupBox22.Controls.Add((Control) this.label104);
      this.groupBox22.Controls.Add((Control) this.textBox187);
      this.groupBox22.Controls.Add((Control) this.label105);
      this.groupBox22.Controls.Add((Control) this.button7);
      this.groupBox22.Controls.Add((Control) this.pictureBox2);
      this.groupBox22.Controls.Add((Control) this.textBox184);
      this.groupBox22.Controls.Add((Control) this.label102);
      this.groupBox22.Controls.Add((Control) this.textBox185);
      this.groupBox22.Controls.Add((Control) this.label103);
      this.groupBox22.Location = new Point(379, 16);
      this.groupBox22.Name = "groupBox22";
      this.groupBox22.Size = new Size(389, 588);
      this.groupBox22.TabIndex = 3;
      this.groupBox22.TabStop = false;
      this.groupBox22.Text = "Special Drop";
      this.textBox217.Location = new Point(346, 557);
      this.textBox217.Name = "textBox217";
      this.textBox217.Size = new Size(40, 22);
      this.textBox217.TabIndex = 145;
      this.label140.AutoSize = true;
      this.label140.Location = new Point(313, 560);
      this.label140.Name = "label140";
      this.label140.Size = new Size(37, 16);
      this.label140.TabIndex = 144;
      this.label140.Text = "Flag:";
      this.textBox216.Location = new Point(270, 557);
      this.textBox216.Name = "textBox216";
      this.textBox216.Size = new Size(40, 22);
      this.textBox216.TabIndex = 143;
      this.label133.AutoSize = true;
      this.label133.Location = new Point(235, 560);
      this.label133.Name = "label133";
      this.label133.Size = new Size(39, 16);
      this.label133.TabIndex = 142;
      this.label133.Text = "Prop:";
      this.textBox215.Location = new Point(191, 557);
      this.textBox215.Name = "textBox215";
      this.textBox215.Size = new Size(40, 22);
      this.textBox215.TabIndex = 141;
      this.label132.AutoSize = true;
      this.label132.Location = new Point(150, 560);
      this.label132.Name = "label132";
      this.label132.Size = new Size(44, 16);
      this.label132.TabIndex = 140;
      this.label132.Text = "Count:";
      this.textBox214.Location = new Point(106, 557);
      this.textBox214.Name = "textBox214";
      this.textBox214.Size = new Size(40, 22);
      this.textBox214.TabIndex = 139;
      this.label131.AutoSize = true;
      this.label131.Location = new Point(76, 560);
      this.label131.Name = "label131";
      this.label131.Size = new Size(35, 16);
      this.label131.TabIndex = 138;
      this.label131.Text = "Max:";
      this.textBox213.Location = new Point(33, 557);
      this.textBox213.Name = "textBox213";
      this.textBox213.Size = new Size(40, 22);
      this.textBox213.TabIndex = 137;
      this.label130.AutoSize = true;
      this.label130.Location = new Point(3, 560);
      this.label130.Name = "label130";
      this.label130.Size = new Size(31, 16);
      this.label130.TabIndex = 136;
      this.label130.Text = "Min:";
      this.button23.BackgroundImageLayout = ImageLayout.None;
      this.button23.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.search__5_;
      this.button23.Location = new Point(349, 519);
      this.button23.Name = "button23";
      this.button23.Size = new Size(27, 25);
      this.button23.TabIndex = 135;
      this.button23.UseVisualStyleBackColor = true;
      this.button23.Click += new EventHandler(this.button23_Click);
      this.pictureBox16.Location = new Point(130, 510);
      this.pictureBox16.Name = "pictureBox16";
      this.pictureBox16.Size = new Size(32, 32);
      this.pictureBox16.TabIndex = 134;
      this.pictureBox16.TabStop = false;
      this.textBox211.Location = new Point(214, 522);
      this.textBox211.Name = "textBox211";
      this.textBox211.Size = new Size(128, 22);
      this.textBox211.TabIndex = 133;
      this.label128.AutoSize = true;
      this.label128.Location = new Point(170, 525);
      this.label128.Name = "label128";
      this.label128.Size = new Size(47, 16);
      this.label128.TabIndex = 132;
      this.label128.Text = "Name:";
      this.textBox212.Location = new Point(63, 522);
      this.textBox212.Name = "textBox212";
      this.textBox212.Size = new Size(61, 22);
      this.textBox212.TabIndex = 131;
      this.textBox212.TextChanged += new EventHandler(this.textBox212_TextChanged);
      this.label129.AutoSize = true;
      this.label129.Location = new Point(12, 525);
      this.label129.Name = "label129";
      this.label129.Size = new Size(52, 16);
      this.label129.TabIndex = 130;
      this.label129.Text = "Item 14:";
      this.button22.BackgroundImageLayout = ImageLayout.None;
      this.button22.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.search__5_;
      this.button22.Location = new Point(349, 481);
      this.button22.Name = "button22";
      this.button22.Size = new Size(27, 25);
      this.button22.TabIndex = 129;
      this.button22.UseVisualStyleBackColor = true;
      this.button22.Click += new EventHandler(this.button22_Click);
      this.pictureBox15.Location = new Point(130, 472);
      this.pictureBox15.Name = "pictureBox15";
      this.pictureBox15.Size = new Size(32, 32);
      this.pictureBox15.TabIndex = 128;
      this.pictureBox15.TabStop = false;
      this.textBox209.Location = new Point(214, 484);
      this.textBox209.Name = "textBox209";
      this.textBox209.Size = new Size(128, 22);
      this.textBox209.TabIndex = (int) sbyte.MaxValue;
      this.label126.AutoSize = true;
      this.label126.Location = new Point(170, 487);
      this.label126.Name = "label126";
      this.label126.Size = new Size(47, 16);
      this.label126.TabIndex = 126;
      this.label126.Text = "Name:";
      this.textBox210.Location = new Point(63, 484);
      this.textBox210.Name = "textBox210";
      this.textBox210.Size = new Size(61, 22);
      this.textBox210.TabIndex = 125;
      this.textBox210.TextChanged += new EventHandler(this.textBox210_TextChanged);
      this.label127.AutoSize = true;
      this.label127.Location = new Point(13, 487);
      this.label127.Name = "label127";
      this.label127.Size = new Size(52, 16);
      this.label127.TabIndex = 124;
      this.label127.Text = "Item 13:";
      this.button21.BackgroundImageLayout = ImageLayout.None;
      this.button21.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.search__5_;
      this.button21.Location = new Point(349, 444);
      this.button21.Name = "button21";
      this.button21.Size = new Size(27, 25);
      this.button21.TabIndex = 123;
      this.button21.UseVisualStyleBackColor = true;
      this.button21.Click += new EventHandler(this.button21_Click);
      this.pictureBox14.Location = new Point(130, 435);
      this.pictureBox14.Name = "pictureBox14";
      this.pictureBox14.Size = new Size(32, 32);
      this.pictureBox14.TabIndex = 122;
      this.pictureBox14.TabStop = false;
      this.textBox207.Location = new Point(214, 447);
      this.textBox207.Name = "textBox207";
      this.textBox207.Size = new Size(128, 22);
      this.textBox207.TabIndex = 121;
      this.label124.AutoSize = true;
      this.label124.Location = new Point(170, 450);
      this.label124.Name = "label124";
      this.label124.Size = new Size(47, 16);
      this.label124.TabIndex = 120;
      this.label124.Text = "Name:";
      this.textBox208.Location = new Point(63, 447);
      this.textBox208.Name = "textBox208";
      this.textBox208.Size = new Size(61, 22);
      this.textBox208.TabIndex = 119;
      this.textBox208.TextChanged += new EventHandler(this.textBox208_TextChanged);
      this.label125.AutoSize = true;
      this.label125.Location = new Point(13, 450);
      this.label125.Name = "label125";
      this.label125.Size = new Size(52, 16);
      this.label125.TabIndex = 118;
      this.label125.Text = "Item 12:";
      this.button20.BackgroundImageLayout = ImageLayout.None;
      this.button20.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.search__5_;
      this.button20.Location = new Point(349, 406);
      this.button20.Name = "button20";
      this.button20.Size = new Size(27, 25);
      this.button20.TabIndex = 117;
      this.button20.UseVisualStyleBackColor = true;
      this.button20.Click += new EventHandler(this.button20_Click);
      this.pictureBox13.Location = new Point(130, 397);
      this.pictureBox13.Name = "pictureBox13";
      this.pictureBox13.Size = new Size(32, 32);
      this.pictureBox13.TabIndex = 116;
      this.pictureBox13.TabStop = false;
      this.textBox205.Location = new Point(214, 409);
      this.textBox205.Name = "textBox205";
      this.textBox205.Size = new Size(128, 22);
      this.textBox205.TabIndex = 115;
      this.label122.AutoSize = true;
      this.label122.Location = new Point(170, 412);
      this.label122.Name = "label122";
      this.label122.Size = new Size(47, 16);
      this.label122.TabIndex = 114;
      this.label122.Text = "Name:";
      this.textBox206.Location = new Point(63, 409);
      this.textBox206.Name = "textBox206";
      this.textBox206.Size = new Size(61, 22);
      this.textBox206.TabIndex = 113;
      this.textBox206.TextChanged += new EventHandler(this.textBox206_TextChanged);
      this.label123.AutoSize = true;
      this.label123.Location = new Point(13, 412);
      this.label123.Name = "label123";
      this.label123.Size = new Size(52, 16);
      this.label123.TabIndex = 112;
      this.label123.Text = "Item 11:";
      this.button16.BackgroundImageLayout = ImageLayout.None;
      this.button16.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.search__5_;
      this.button16.Location = new Point(349, 369);
      this.button16.Name = "button16";
      this.button16.Size = new Size(27, 25);
      this.button16.TabIndex = 111;
      this.button16.UseVisualStyleBackColor = true;
      this.button16.Click += new EventHandler(this.button16_Click);
      this.pictureBox12.Location = new Point(130, 360);
      this.pictureBox12.Name = "pictureBox12";
      this.pictureBox12.Size = new Size(32, 32);
      this.pictureBox12.TabIndex = 110;
      this.pictureBox12.TabStop = false;
      this.textBox203.Location = new Point(214, 372);
      this.textBox203.Name = "textBox203";
      this.textBox203.Size = new Size(128, 22);
      this.textBox203.TabIndex = 109;
      this.label120.AutoSize = true;
      this.label120.Location = new Point(170, 375);
      this.label120.Name = "label120";
      this.label120.Size = new Size(47, 16);
      this.label120.TabIndex = 108;
      this.label120.Text = "Name:";
      this.textBox204.Location = new Point(63, 372);
      this.textBox204.Name = "textBox204";
      this.textBox204.Size = new Size(61, 22);
      this.textBox204.TabIndex = 107;
      this.textBox204.TextChanged += new EventHandler(this.textBox204_TextChanged);
      this.label121.AutoSize = true;
      this.label121.Location = new Point(13, 375);
      this.label121.Name = "label121";
      this.label121.Size = new Size(52, 16);
      this.label121.TabIndex = 106;
      this.label121.Text = "Item 10:";
      this.button15.BackgroundImageLayout = ImageLayout.None;
      this.button15.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.search__5_;
      this.button15.Location = new Point(349, 332);
      this.button15.Name = "button15";
      this.button15.Size = new Size(27, 25);
      this.button15.TabIndex = 105;
      this.button15.UseVisualStyleBackColor = true;
      this.button15.Click += new EventHandler(this.button15_Click);
      this.pictureBox11.Location = new Point(130, 323);
      this.pictureBox11.Name = "pictureBox11";
      this.pictureBox11.Size = new Size(32, 32);
      this.pictureBox11.TabIndex = 104;
      this.pictureBox11.TabStop = false;
      this.textBox201.Location = new Point(214, 335);
      this.textBox201.Name = "textBox201";
      this.textBox201.Size = new Size(128, 22);
      this.textBox201.TabIndex = 103;
      this.label118.AutoSize = true;
      this.label118.Location = new Point(170, 338);
      this.label118.Name = "label118";
      this.label118.Size = new Size(47, 16);
      this.label118.TabIndex = 102;
      this.label118.Text = "Name:";
      this.textBox202.Location = new Point(63, 335);
      this.textBox202.Name = "textBox202";
      this.textBox202.Size = new Size(61, 22);
      this.textBox202.TabIndex = 101;
      this.textBox202.TextChanged += new EventHandler(this.textBox202_TextChanged);
      this.label119.AutoSize = true;
      this.label119.Location = new Point(19, 338);
      this.label119.Name = "label119";
      this.label119.Size = new Size(45, 16);
      this.label119.TabIndex = 100;
      this.label119.Text = "Item 9:";
      this.button14.BackgroundImageLayout = ImageLayout.None;
      this.button14.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.search__5_;
      this.button14.Location = new Point(349, 295);
      this.button14.Name = "button14";
      this.button14.Size = new Size(27, 25);
      this.button14.TabIndex = 99;
      this.button14.UseVisualStyleBackColor = true;
      this.button14.Click += new EventHandler(this.button14_Click);
      this.pictureBox10.Location = new Point(130, 286);
      this.pictureBox10.Name = "pictureBox10";
      this.pictureBox10.Size = new Size(32, 32);
      this.pictureBox10.TabIndex = 98;
      this.pictureBox10.TabStop = false;
      this.textBox198.Location = new Point(214, 298);
      this.textBox198.Name = "textBox198";
      this.textBox198.Size = new Size(128, 22);
      this.textBox198.TabIndex = 97;
      this.label116.AutoSize = true;
      this.label116.Location = new Point(170, 301);
      this.label116.Name = "label116";
      this.label116.Size = new Size(47, 16);
      this.label116.TabIndex = 96;
      this.label116.Text = "Name:";
      this.textBox199.Location = new Point(63, 298);
      this.textBox199.Name = "textBox199";
      this.textBox199.Size = new Size(61, 22);
      this.textBox199.TabIndex = 95;
      this.textBox199.TextChanged += new EventHandler(this.textBox199_TextChanged);
      this.label117.AutoSize = true;
      this.label117.Location = new Point(19, 301);
      this.label117.Name = "label117";
      this.label117.Size = new Size(45, 16);
      this.label117.TabIndex = 94;
      this.label117.Text = "Item 8:";
      this.button13.BackgroundImageLayout = ImageLayout.None;
      this.button13.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.search__5_;
      this.button13.Location = new Point(349, 257);
      this.button13.Name = "button13";
      this.button13.Size = new Size(27, 25);
      this.button13.TabIndex = 93;
      this.button13.UseVisualStyleBackColor = true;
      this.button13.Click += new EventHandler(this.button13_Click);
      this.pictureBox9.Location = new Point(130, 248);
      this.pictureBox9.Name = "pictureBox9";
      this.pictureBox9.Size = new Size(32, 32);
      this.pictureBox9.TabIndex = 92;
      this.pictureBox9.TabStop = false;
      this.textBox196.Location = new Point(214, 260);
      this.textBox196.Name = "textBox196";
      this.textBox196.Size = new Size(128, 22);
      this.textBox196.TabIndex = 91;
      this.label114.AutoSize = true;
      this.label114.Location = new Point(170, 263);
      this.label114.Name = "label114";
      this.label114.Size = new Size(47, 16);
      this.label114.TabIndex = 90;
      this.label114.Text = "Name:";
      this.textBox197.Location = new Point(63, 260);
      this.textBox197.Name = "textBox197";
      this.textBox197.Size = new Size(61, 22);
      this.textBox197.TabIndex = 89;
      this.textBox197.TextChanged += new EventHandler(this.textBox197_TextChanged);
      this.label115.AutoSize = true;
      this.label115.Location = new Point(19, 263);
      this.label115.Name = "label115";
      this.label115.Size = new Size(45, 16);
      this.label115.TabIndex = 88;
      this.label115.Text = "Item 7:";
      this.button12.BackgroundImageLayout = ImageLayout.None;
      this.button12.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.search__5_;
      this.button12.Location = new Point(349, 219);
      this.button12.Name = "button12";
      this.button12.Size = new Size(27, 25);
      this.button12.TabIndex = 87;
      this.button12.UseVisualStyleBackColor = true;
      this.button12.Click += new EventHandler(this.button12_Click);
      this.pictureBox8.Location = new Point(130, 210);
      this.pictureBox8.Name = "pictureBox8";
      this.pictureBox8.Size = new Size(32, 32);
      this.pictureBox8.TabIndex = 86;
      this.pictureBox8.TabStop = false;
      this.textBox194.Location = new Point(214, 222);
      this.textBox194.Name = "textBox194";
      this.textBox194.Size = new Size(128, 22);
      this.textBox194.TabIndex = 85;
      this.label112.AutoSize = true;
      this.label112.Location = new Point(170, 225);
      this.label112.Name = "label112";
      this.label112.Size = new Size(47, 16);
      this.label112.TabIndex = 84;
      this.label112.Text = "Name:";
      this.textBox195.Location = new Point(63, 222);
      this.textBox195.Name = "textBox195";
      this.textBox195.Size = new Size(61, 22);
      this.textBox195.TabIndex = 83;
      this.textBox195.TextChanged += new EventHandler(this.textBox195_TextChanged);
      this.label113.AutoSize = true;
      this.label113.Location = new Point(19, 225);
      this.label113.Name = "label113";
      this.label113.Size = new Size(45, 16);
      this.label113.TabIndex = 82;
      this.label113.Text = "Item 6:";
      this.button11.BackgroundImageLayout = ImageLayout.None;
      this.button11.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.search__5_;
      this.button11.Location = new Point(349, 181);
      this.button11.Name = "button11";
      this.button11.Size = new Size(27, 25);
      this.button11.TabIndex = 81;
      this.button11.UseVisualStyleBackColor = true;
      this.button11.Click += new EventHandler(this.button11_Click);
      this.pictureBox6.Location = new Point(130, 172);
      this.pictureBox6.Name = "pictureBox6";
      this.pictureBox6.Size = new Size(32, 32);
      this.pictureBox6.TabIndex = 80;
      this.pictureBox6.TabStop = false;
      this.textBox192.Location = new Point(214, 184);
      this.textBox192.Name = "textBox192";
      this.textBox192.Size = new Size(128, 22);
      this.textBox192.TabIndex = 79;
      this.label110.AutoSize = true;
      this.label110.Location = new Point(170, 187);
      this.label110.Name = "label110";
      this.label110.Size = new Size(47, 16);
      this.label110.TabIndex = 78;
      this.label110.Text = "Name:";
      this.textBox193.Location = new Point(63, 184);
      this.textBox193.Name = "textBox193";
      this.textBox193.Size = new Size(61, 22);
      this.textBox193.TabIndex = 77;
      this.textBox193.TextChanged += new EventHandler(this.textBox193_TextChanged);
      this.label111.AutoSize = true;
      this.label111.Location = new Point(19, 187);
      this.label111.Name = "label111";
      this.label111.Size = new Size(45, 16);
      this.label111.TabIndex = 76;
      this.label111.Text = "Item 5:";
      this.button10.BackgroundImageLayout = ImageLayout.None;
      this.button10.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.search__5_;
      this.button10.Location = new Point(349, 143);
      this.button10.Name = "button10";
      this.button10.Size = new Size(27, 25);
      this.button10.TabIndex = 75;
      this.button10.UseVisualStyleBackColor = true;
      this.button10.Click += new EventHandler(this.button10_Click);
      this.pictureBox5.Location = new Point(130, 134);
      this.pictureBox5.Name = "pictureBox5";
      this.pictureBox5.Size = new Size(32, 32);
      this.pictureBox5.TabIndex = 74;
      this.pictureBox5.TabStop = false;
      this.textBox190.Location = new Point(214, 146);
      this.textBox190.Name = "textBox190";
      this.textBox190.Size = new Size(128, 22);
      this.textBox190.TabIndex = 73;
      this.label108.AutoSize = true;
      this.label108.Location = new Point(170, 149);
      this.label108.Name = "label108";
      this.label108.Size = new Size(47, 16);
      this.label108.TabIndex = 72;
      this.label108.Text = "Name:";
      this.textBox191.Location = new Point(63, 146);
      this.textBox191.Name = "textBox191";
      this.textBox191.Size = new Size(61, 22);
      this.textBox191.TabIndex = 71;
      this.textBox191.TextChanged += new EventHandler(this.textBox191_TextChanged);
      this.label109.AutoSize = true;
      this.label109.Location = new Point(19, 149);
      this.label109.Name = "label109";
      this.label109.Size = new Size(45, 16);
      this.label109.TabIndex = 70;
      this.label109.Text = "Item 4:";
      this.button9.BackgroundImageLayout = ImageLayout.None;
      this.button9.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.search__5_;
      this.button9.Location = new Point(349, 105);
      this.button9.Name = "button9";
      this.button9.Size = new Size(27, 25);
      this.button9.TabIndex = 69;
      this.button9.UseVisualStyleBackColor = true;
      this.button9.Click += new EventHandler(this.button9_Click);
      this.pictureBox4.Location = new Point(130, 96);
      this.pictureBox4.Name = "pictureBox4";
      this.pictureBox4.Size = new Size(32, 32);
      this.pictureBox4.TabIndex = 68;
      this.pictureBox4.TabStop = false;
      this.textBox188.Location = new Point(214, 108);
      this.textBox188.Name = "textBox188";
      this.textBox188.Size = new Size(128, 22);
      this.textBox188.TabIndex = 67;
      this.label106.AutoSize = true;
      this.label106.Location = new Point(170, 111);
      this.label106.Name = "label106";
      this.label106.Size = new Size(47, 16);
      this.label106.TabIndex = 66;
      this.label106.Text = "Name:";
      this.textBox189.Location = new Point(63, 108);
      this.textBox189.Name = "textBox189";
      this.textBox189.Size = new Size(61, 22);
      this.textBox189.TabIndex = 65;
      this.textBox189.TextChanged += new EventHandler(this.textBox189_TextChanged);
      this.label107.AutoSize = true;
      this.label107.Location = new Point(19, 111);
      this.label107.Name = "label107";
      this.label107.Size = new Size(45, 16);
      this.label107.TabIndex = 64;
      this.label107.Text = "Item 3:";
      this.button8.BackgroundImageLayout = ImageLayout.None;
      this.button8.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.search__5_;
      this.button8.Location = new Point(349, 68);
      this.button8.Name = "button8";
      this.button8.Size = new Size(27, 25);
      this.button8.TabIndex = 63;
      this.button8.UseVisualStyleBackColor = true;
      this.button8.Click += new EventHandler(this.button8_Click);
      this.pictureBox3.Location = new Point(130, 59);
      this.pictureBox3.Name = "pictureBox3";
      this.pictureBox3.Size = new Size(32, 32);
      this.pictureBox3.TabIndex = 62;
      this.pictureBox3.TabStop = false;
      this.textBox186.Location = new Point(214, 71);
      this.textBox186.Name = "textBox186";
      this.textBox186.Size = new Size(128, 22);
      this.textBox186.TabIndex = 61;
      this.label104.AutoSize = true;
      this.label104.Location = new Point(168, 74);
      this.label104.Name = "label104";
      this.label104.Size = new Size(47, 16);
      this.label104.TabIndex = 60;
      this.label104.Text = "Name:";
      this.textBox187.Location = new Point(63, 71);
      this.textBox187.Name = "textBox187";
      this.textBox187.Size = new Size(61, 22);
      this.textBox187.TabIndex = 59;
      this.textBox187.TextChanged += new EventHandler(this.textBox187_TextChanged);
      this.label105.AutoSize = true;
      this.label105.Location = new Point(19, 74);
      this.label105.Name = "label105";
      this.label105.Size = new Size(45, 16);
      this.label105.TabIndex = 58;
      this.label105.Text = "Item 2:";
      this.button7.BackgroundImageLayout = ImageLayout.None;
      this.button7.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.search__5_;
      this.button7.Location = new Point(349, 31);
      this.button7.Name = "button7";
      this.button7.Size = new Size(27, 25);
      this.button7.TabIndex = 57;
      this.button7.UseVisualStyleBackColor = true;
      this.button7.Click += new EventHandler(this.button7_Click);
      this.pictureBox2.Location = new Point(130, 22);
      this.pictureBox2.Name = "pictureBox2";
      this.pictureBox2.Size = new Size(32, 32);
      this.pictureBox2.TabIndex = 56;
      this.pictureBox2.TabStop = false;
      this.textBox184.Location = new Point(214, 34);
      this.textBox184.Name = "textBox184";
      this.textBox184.Size = new Size(128, 22);
      this.textBox184.TabIndex = 55;
      this.label102.AutoSize = true;
      this.label102.Location = new Point(170, 37);
      this.label102.Name = "label102";
      this.label102.Size = new Size(47, 16);
      this.label102.TabIndex = 54;
      this.label102.Text = "Name:";
      this.textBox185.Location = new Point(63, 34);
      this.textBox185.Name = "textBox185";
      this.textBox185.Size = new Size(61, 22);
      this.textBox185.TabIndex = 53;
      this.textBox185.TextChanged += new EventHandler(this.textBox185_TextChanged);
      this.label103.AutoSize = true;
      this.label103.Location = new Point(19, 37);
      this.label103.Name = "label103";
      this.label103.Size = new Size(45, 16);
      this.label103.TabIndex = 52;
      this.label103.Text = "Item 1:";
      this.groupBox21.Controls.Add((Control) this.label193);
      this.groupBox21.Controls.Add((Control) this.button5);
      this.groupBox21.Controls.Add((Control) this.pictureBox7);
      this.groupBox21.Controls.Add((Control) this.textBox183);
      this.groupBox21.Controls.Add((Control) this.label101);
      this.groupBox21.Controls.Add((Control) this.textBox182);
      this.groupBox21.Controls.Add((Control) this.label100);
      this.groupBox21.Controls.Add((Control) this.textBox181);
      this.groupBox21.Controls.Add((Control) this.label99);
      this.groupBox21.Controls.Add((Control) this.textBox180);
      this.groupBox21.Controls.Add((Control) this.textBox178);
      this.groupBox21.Controls.Add((Control) this.label98);
      this.groupBox21.Controls.Add((Control) this.label96);
      this.groupBox21.Controls.Add((Control) this.textBox177);
      this.groupBox21.Controls.Add((Control) this.textBox179);
      this.groupBox21.Controls.Add((Control) this.label95);
      this.groupBox21.Controls.Add((Control) this.label97);
      this.groupBox21.Location = new Point(6, 388);
      this.groupBox21.Name = "groupBox21";
      this.groupBox21.Size = new Size(369, 147);
      this.groupBox21.TabIndex = 2;
      this.groupBox21.TabStop = false;
      this.groupBox21.Text = "Item Drop";
      this.label193.AutoSize = true;
      this.label193.ForeColor = Color.Red;
      this.label193.Location = new Point(167, 131);
      this.label193.Name = "label193";
      this.label193.Size = new Size(125, 16);
      this.label193.TabIndex = 113;
      this.label193.Text = "Prop* 100% = 10000";
      this.button5.BackgroundImageLayout = ImageLayout.None;
      this.button5.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.search__5_;
      this.button5.Location = new Point(338, 30);
      this.button5.Name = "button5";
      this.button5.Size = new Size(27, 25);
      this.button5.TabIndex = 51;
      this.button5.UseVisualStyleBackColor = true;
      this.button5.Click += new EventHandler(this.button5_Click);
      this.pictureBox7.Location = new Point(121, 21);
      this.pictureBox7.Name = "pictureBox7";
      this.pictureBox7.Size = new Size(32, 32);
      this.pictureBox7.TabIndex = 50;
      this.pictureBox7.TabStop = false;
      this.textBox183.Location = new Point(205, 104);
      this.textBox183.Name = "textBox183";
      this.textBox183.Size = new Size(104, 22);
      this.textBox183.TabIndex = 15;
      this.label101.AutoSize = true;
      this.label101.Location = new Point(167, 107);
      this.label101.Name = "label101";
      this.label101.Size = new Size(39, 16);
      this.label101.TabIndex = 14;
      this.label101.Text = "Prop:";
      this.textBox182.Location = new Point(205, 69);
      this.textBox182.Name = "textBox182";
      this.textBox182.Size = new Size(61, 22);
      this.textBox182.TabIndex = 13;
      this.label100.AutoSize = true;
      this.label100.Location = new Point(169, 72);
      this.label100.Name = "label100";
      this.label100.Size = new Size(37, 16);
      this.label100.TabIndex = 12;
      this.label100.Text = "Flag:";
      this.textBox181.Location = new Point(54, 69);
      this.textBox181.Name = "textBox181";
      this.textBox181.Size = new Size(61, 22);
      this.textBox181.TabIndex = 11;
      this.label99.AutoSize = true;
      this.label99.Location = new Point(6, 72);
      this.label99.Name = "label99";
      this.label99.Size = new Size(44, 16);
      this.label99.TabIndex = 10;
      this.label99.Text = "Count:";
      this.textBox180.Location = new Point(205, 33);
      this.textBox180.Name = "textBox180";
      this.textBox180.Size = new Size(128, 22);
      this.textBox180.TabIndex = 9;
      this.textBox178.Location = new Point(48, 118);
      this.textBox178.Name = "textBox178";
      this.textBox178.Size = new Size(68, 22);
      this.textBox178.TabIndex = 7;
      this.textBox178.Visible = false;
      this.label98.AutoSize = true;
      this.label98.Location = new Point(161, 36);
      this.label98.Name = "label98";
      this.label98.Size = new Size(47, 16);
      this.label98.TabIndex = 8;
      this.label98.Text = "Name:";
      this.label96.AutoSize = true;
      this.label96.Location = new Point(12, 121);
      this.label96.Name = "label96";
      this.label96.Size = new Size(35, 16);
      this.label96.TabIndex = 6;
      this.label96.Text = "Npc:";
      this.label96.Visible = false;
      this.textBox177.Location = new Point(51, 97);
      this.textBox177.Name = "textBox177";
      this.textBox177.Size = new Size(43, 22);
      this.textBox177.TabIndex = 5;
      this.textBox177.Visible = false;
      this.textBox179.Location = new Point(54, 33);
      this.textBox179.Name = "textBox179";
      this.textBox179.Size = new Size(61, 22);
      this.textBox179.TabIndex = 7;
      this.textBox179.TextChanged += new EventHandler(this.textBox179_TextChanged);
      this.label95.AutoSize = true;
      this.label95.Location = new Point(12, 100);
      this.label95.Name = "label95";
      this.label95.Size = new Size(42, 16);
      this.label95.TabIndex = 4;
      this.label95.Text = "Index:";
      this.label95.Visible = false;
      this.label97.AutoSize = true;
      this.label97.Location = new Point(6, 36);
      this.label97.Name = "label97";
      this.label97.Size = new Size(49, 16);
      this.label97.TabIndex = 6;
      this.label97.Text = "Item Id:";
      this.dgRaidItems.AllowUserToAddRows = false;
      this.dgRaidItems.AllowUserToDeleteRows = false;
      this.dgRaidItems.BackgroundColor = SystemColors.Control;
      this.dgRaidItems.BorderStyle = BorderStyle.None;
      this.dgRaidItems.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dgRaidItems.Columns.AddRange((DataGridViewColumn) this.Icon, (DataGridViewColumn) this.a_index, (DataGridViewColumn) this.a_npc_index, (DataGridViewColumn) this.a_item_index, (DataGridViewColumn) this.ItemName, (DataGridViewColumn) this.a_count, (DataGridViewColumn) this.a_prob, (DataGridViewColumn) this.a_flag, (DataGridViewColumn) this.a_spec_item_index1, (DataGridViewColumn) this.a_spec_item_index2, (DataGridViewColumn) this.a_spec_item_index3, (DataGridViewColumn) this.a_spec_item_index4, (DataGridViewColumn) this.a_spec_item_index5, (DataGridViewColumn) this.a_spec_item_index6, (DataGridViewColumn) this.a_spec_item_index7, (DataGridViewColumn) this.a_spec_item_index8, (DataGridViewColumn) this.a_spec_item_index9, (DataGridViewColumn) this.a_spec_item_index10, (DataGridViewColumn) this.a_spec_item_index11, (DataGridViewColumn) this.a_spec_item_index12, (DataGridViewColumn) this.a_spec_item_index13, (DataGridViewColumn) this.a_spec_item_index14, (DataGridViewColumn) this.a_spec_min, (DataGridViewColumn) this.a_spec_max, (DataGridViewColumn) this.a_spec_count, (DataGridViewColumn) this.a_spec_prob, (DataGridViewColumn) this.a_spec_flag);
      this.dgRaidItems.EnableHeadersVisualStyles = false;
      this.dgRaidItems.Location = new Point(3, 16);
      this.dgRaidItems.Name = "dgRaidItems";
      this.dgRaidItems.RowHeadersVisible = false;
      this.dgRaidItems.RowHeadersWidth = 51;
      this.dgRaidItems.RowTemplate.Height = 32;
      this.dgRaidItems.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
      this.dgRaidItems.Size = new Size(370, 366);
      this.dgRaidItems.TabIndex = 1;
      this.dgRaidItems.CellClick += new DataGridViewCellEventHandler(this.dgRaidItems_CellClick);
      this.Icon.HeaderText = "";
      this.Icon.MinimumWidth = 6;
      this.Icon.Name = "Icon";
      this.Icon.Width = 32;
      this.a_index.HeaderText = "Index";
      this.a_index.MinimumWidth = 6;
      this.a_index.Name = "a_index";
      this.a_index.Visible = false;
      this.a_index.Width = 60;
      this.a_npc_index.HeaderText = "Boss";
      this.a_npc_index.MinimumWidth = 6;
      this.a_npc_index.Name = "a_npc_index";
      this.a_npc_index.Visible = false;
      this.a_npc_index.Width = 50;
      this.a_item_index.HeaderText = "Item_Id";
      this.a_item_index.MinimumWidth = 6;
      this.a_item_index.Name = "a_item_index";
      this.a_item_index.Width = 70;
      this.ItemName.HeaderText = "Name";
      this.ItemName.MinimumWidth = 6;
      this.ItemName.Name = "ItemName";
      this.ItemName.ReadOnly = true;
      this.ItemName.Width = 120;
      this.a_count.HeaderText = "Count";
      this.a_count.MinimumWidth = 6;
      this.a_count.Name = "a_count";
      this.a_count.Width = 55;
      this.a_prob.HeaderText = "Prob";
      this.a_prob.MinimumWidth = 6;
      this.a_prob.Name = "a_prob";
      this.a_prob.Width = 50;
      this.a_flag.HeaderText = "Flag";
      this.a_flag.MinimumWidth = 6;
      this.a_flag.Name = "a_flag";
      this.a_flag.Width = 40;
      this.a_spec_item_index1.HeaderText = "spec_item1";
      this.a_spec_item_index1.MinimumWidth = 6;
      this.a_spec_item_index1.Name = "a_spec_item_index1";
      this.a_spec_item_index1.Width = 70;
      this.a_spec_item_index2.HeaderText = "spec_item2";
      this.a_spec_item_index2.MinimumWidth = 6;
      this.a_spec_item_index2.Name = "a_spec_item_index2";
      this.a_spec_item_index2.Width = 70;
      this.a_spec_item_index3.HeaderText = "spec_item3";
      this.a_spec_item_index3.MinimumWidth = 6;
      this.a_spec_item_index3.Name = "a_spec_item_index3";
      this.a_spec_item_index3.Width = 70;
      this.a_spec_item_index4.HeaderText = "spec_item4";
      this.a_spec_item_index4.MinimumWidth = 6;
      this.a_spec_item_index4.Name = "a_spec_item_index4";
      this.a_spec_item_index4.Width = 70;
      this.a_spec_item_index5.HeaderText = "spec_item5";
      this.a_spec_item_index5.MinimumWidth = 6;
      this.a_spec_item_index5.Name = "a_spec_item_index5";
      this.a_spec_item_index5.Width = 70;
      this.a_spec_item_index6.HeaderText = "spec_item6";
      this.a_spec_item_index6.MinimumWidth = 6;
      this.a_spec_item_index6.Name = "a_spec_item_index6";
      this.a_spec_item_index6.Width = 70;
      this.a_spec_item_index7.HeaderText = "spec_item7";
      this.a_spec_item_index7.MinimumWidth = 6;
      this.a_spec_item_index7.Name = "a_spec_item_index7";
      this.a_spec_item_index7.Width = 70;
      this.a_spec_item_index8.HeaderText = "spec_item8";
      this.a_spec_item_index8.MinimumWidth = 6;
      this.a_spec_item_index8.Name = "a_spec_item_index8";
      this.a_spec_item_index8.Width = 70;
      this.a_spec_item_index9.HeaderText = "spec_item9";
      this.a_spec_item_index9.MinimumWidth = 6;
      this.a_spec_item_index9.Name = "a_spec_item_index9";
      this.a_spec_item_index9.Width = 70;
      this.a_spec_item_index10.HeaderText = "spec_item10";
      this.a_spec_item_index10.MinimumWidth = 6;
      this.a_spec_item_index10.Name = "a_spec_item_index10";
      this.a_spec_item_index10.Width = 70;
      this.a_spec_item_index11.HeaderText = "spec_item11";
      this.a_spec_item_index11.MinimumWidth = 6;
      this.a_spec_item_index11.Name = "a_spec_item_index11";
      this.a_spec_item_index11.Width = 70;
      this.a_spec_item_index12.HeaderText = "spec_item12";
      this.a_spec_item_index12.MinimumWidth = 6;
      this.a_spec_item_index12.Name = "a_spec_item_index12";
      this.a_spec_item_index12.Width = 70;
      this.a_spec_item_index13.HeaderText = "spec_item13";
      this.a_spec_item_index13.MinimumWidth = 6;
      this.a_spec_item_index13.Name = "a_spec_item_index13";
      this.a_spec_item_index13.Width = 70;
      this.a_spec_item_index14.HeaderText = "spec_item14";
      this.a_spec_item_index14.MinimumWidth = 6;
      this.a_spec_item_index14.Name = "a_spec_item_index14";
      this.a_spec_item_index14.Width = 70;
      this.a_spec_min.HeaderText = "spec_min";
      this.a_spec_min.MinimumWidth = 6;
      this.a_spec_min.Name = "a_spec_min";
      this.a_spec_min.Width = 70;
      this.a_spec_max.HeaderText = "spec_max";
      this.a_spec_max.MinimumWidth = 6;
      this.a_spec_max.Name = "a_spec_max";
      this.a_spec_max.Width = 70;
      this.a_spec_count.HeaderText = "spec_count";
      this.a_spec_count.MinimumWidth = 6;
      this.a_spec_count.Name = "a_spec_count";
      this.a_spec_count.Width = 70;
      this.a_spec_prob.HeaderText = "spec_prob";
      this.a_spec_prob.MinimumWidth = 6;
      this.a_spec_prob.Name = "a_spec_prob";
      this.a_spec_prob.Width = 70;
      this.a_spec_flag.HeaderText = "spec_flag";
      this.a_spec_flag.MinimumWidth = 6;
      this.a_spec_flag.Name = "a_spec_flag";
      this.a_spec_flag.Width = 70;
      this.tabPage5.Controls.Add((Control) this.groupBox23);
      this.tabPage5.Location = new Point(4, 25);
      this.tabPage5.Name = "tabPage5";
      this.tabPage5.Padding = new Padding(3);
      this.tabPage5.Size = new Size(774, 607);
      this.tabPage5.TabIndex = 8;
      this.tabPage5.Text = "Drop All";
      this.tabPage5.UseVisualStyleBackColor = true;
      this.groupBox23.Controls.Add((Control) this.label192);
      this.groupBox23.Controls.Add((Control) this.groupBox33);
      this.groupBox23.Controls.Add((Control) this.button28);
      this.groupBox23.Controls.Add((Control) this.button27);
      this.groupBox23.Controls.Add((Control) this.textBox224);
      this.groupBox23.Controls.Add((Control) this.label143);
      this.groupBox23.Controls.Add((Control) this.groupBox35);
      this.groupBox23.Controls.Add((Control) this.groupBox36);
      this.groupBox23.Controls.Add((Control) this.groupBox37);
      this.groupBox23.Controls.Add((Control) this.dgDropAllItems);
      this.groupBox23.Controls.Add((Control) this.groupBox38);
      this.groupBox23.Controls.Add((Control) this.groupBox39);
      this.groupBox23.Controls.Add((Control) this.groupBox40);
      this.groupBox23.Controls.Add((Control) this.groupBox41);
      this.groupBox23.Controls.Add((Control) this.groupBox32);
      this.groupBox23.Controls.Add((Control) this.groupBox30);
      this.groupBox23.Controls.Add((Control) this.groupBox29);
      this.groupBox23.Controls.Add((Control) this.groupBox31);
      this.groupBox23.Controls.Add((Control) this.groupBox28);
      this.groupBox23.Controls.Add((Control) this.groupBox27);
      this.groupBox23.Controls.Add((Control) this.groupBox26);
      this.groupBox23.Controls.Add((Control) this.groupBox25);
      this.groupBox23.Controls.Add((Control) this.groupBox24);
      this.groupBox23.Location = new Point(4, 6);
      this.groupBox23.Name = "groupBox23";
      this.groupBox23.Size = new Size(768, 608);
      this.groupBox23.TabIndex = 3;
      this.groupBox23.TabStop = false;
      this.groupBox23.Text = "Item Drop";
      this.label192.AutoSize = true;
      this.label192.ForeColor = Color.Red;
      this.label192.Location = new Point(260, 563);
      this.label192.Name = "label192";
      this.label192.Size = new Size(125, 16);
      this.label192.TabIndex = 112;
      this.label192.Text = "Prop* 100% = 10000";
      this.groupBox33.Controls.Add((Control) this.textBox225);
      this.groupBox33.Controls.Add((Control) this.label187);
      this.groupBox33.Controls.Add((Control) this.label188);
      this.groupBox33.Controls.Add((Control) this.textBox251);
      this.groupBox33.Controls.Add((Control) this.label189);
      this.groupBox33.Controls.Add((Control) this.label190);
      this.groupBox33.Controls.Add((Control) this.label191);
      this.groupBox33.Controls.Add((Control) this.button36);
      this.groupBox33.Controls.Add((Control) this.textBox252);
      this.groupBox33.Controls.Add((Control) this.pictureBox27);
      this.groupBox33.Location = new Point(384, 541);
      this.groupBox33.Name = "groupBox33";
      this.groupBox33.Size = new Size(381, 58);
      this.groupBox33.TabIndex = 111;
      this.groupBox33.TabStop = false;
      this.groupBox33.Text = "Item 17.";
      this.textBox225.Location = new Point(51, 19);
      this.textBox225.Name = "textBox225";
      this.textBox225.Size = new Size(58, 22);
      this.textBox225.TabIndex = 7;
      this.textBox225.TextChanged += new EventHandler(this.textBox225_TextChanged);
      this.label187.AutoSize = true;
      this.label187.ForeColor = Color.MediumVioletRed;
      this.label187.Location = new Point(51, 42);
      this.label187.Name = "label187";
      this.label187.Size = new Size(58, 16);
      this.label187.TabIndex = 54;
      this.label187.Text = "label187";
      this.label188.AutoSize = true;
      this.label188.Location = new Point(3, 22);
      this.label188.Name = "label188";
      this.label188.Size = new Size(49, 16);
      this.label188.TabIndex = 6;
      this.label188.Text = "Item Id:";
      this.textBox251.Location = new Point(202, 13);
      this.textBox251.Name = "textBox251";
      this.textBox251.Size = new Size(49, 22);
      this.textBox251.TabIndex = 53;
      this.label189.AutoSize = true;
      this.label189.Location = new Point(7, 42);
      this.label189.Name = "label189";
      this.label189.Size = new Size(47, 16);
      this.label189.TabIndex = 8;
      this.label189.Text = "Name:";
      this.label190.AutoSize = true;
      this.label190.Location = new Point(158, 16);
      this.label190.Name = "label190";
      this.label190.Size = new Size(44, 16);
      this.label190.TabIndex = 52;
      this.label190.Text = "Count:";
      this.label191.AutoSize = true;
      this.label191.Location = new Point(257, 16);
      this.label191.Name = "label191";
      this.label191.Size = new Size(39, 16);
      this.label191.TabIndex = 14;
      this.label191.Text = "Prop:";
      this.button36.BackgroundImageLayout = ImageLayout.None;
      this.button36.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.search__5_;
      this.button36.Location = new Point(348, 10);
      this.button36.Name = "button36";
      this.button36.Size = new Size(27, 25);
      this.button36.TabIndex = 51;
      this.button36.UseVisualStyleBackColor = true;
      this.button36.Click += new EventHandler(this.button36_Click);
      this.textBox252.Location = new Point(295, 13);
      this.textBox252.Name = "textBox252";
      this.textBox252.Size = new Size(49, 22);
      this.textBox252.TabIndex = 15;
      this.pictureBox27.Location = new Point(115, 10);
      this.pictureBox27.Name = "pictureBox27";
      this.pictureBox27.Size = new Size(32, 32);
      this.pictureBox27.TabIndex = 50;
      this.pictureBox27.TabStop = false;
      this.button28.BackColor = Color.LightCoral;
      this.button28.FlatStyle = FlatStyle.Flat;
      this.button28.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.delete;
      this.button28.ImageAlign = ContentAlignment.MiddleLeft;
      this.button28.Location = new Point(152, 557);
      this.button28.Name = "button28";
      this.button28.Size = new Size(65, 27);
      this.button28.TabIndex = 110;
      this.button28.Text = "    Delete";
      this.button28.UseVisualStyleBackColor = false;
      this.button28.Click += new EventHandler(this.button28_Click);
      this.button27.BackColor = Color.Plum;
      this.button27.FlatStyle = FlatStyle.Flat;
      this.button27.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.control_add_blue;
      this.button27.ImageAlign = ContentAlignment.MiddleLeft;
      this.button27.Location = new Point(54, 557);
      this.button27.Name = "button27";
      this.button27.Size = new Size(71, 27);
      this.button27.TabIndex = 108;
      this.button27.Text = "     Save";
      this.button27.UseVisualStyleBackColor = false;
      this.button27.Click += new EventHandler(this.button27_Click);
      this.textBox224.Location = new Point(586, 0);
      this.textBox224.Name = "textBox224";
      this.textBox224.Size = new Size(61, 22);
      this.textBox224.TabIndex = 11;
      this.textBox224.Visible = false;
      this.label143.AutoSize = true;
      this.label143.Location = new Point(550, 3);
      this.label143.Name = "label143";
      this.label143.Size = new Size(35, 16);
      this.label143.TabIndex = 10;
      this.label143.Text = "Npc:";
      this.label143.Visible = false;
      this.groupBox35.Controls.Add((Control) this.textBox257);
      this.groupBox35.Controls.Add((Control) this.label197);
      this.groupBox35.Controls.Add((Control) this.label198);
      this.groupBox35.Controls.Add((Control) this.textBox258);
      this.groupBox35.Controls.Add((Control) this.label199);
      this.groupBox35.Controls.Add((Control) this.label200);
      this.groupBox35.Controls.Add((Control) this.label201);
      this.groupBox35.Controls.Add((Control) this.button38);
      this.groupBox35.Controls.Add((Control) this.textBox259);
      this.groupBox35.Controls.Add((Control) this.pictureBox29);
      this.groupBox35.Location = new Point(384, 483);
      this.groupBox35.Name = "groupBox35";
      this.groupBox35.Size = new Size(381, 58);
      this.groupBox35.TabIndex = 70;
      this.groupBox35.TabStop = false;
      this.groupBox35.Text = "Item 16.";
      this.textBox257.Location = new Point(51, 19);
      this.textBox257.Name = "textBox257";
      this.textBox257.Size = new Size(58, 22);
      this.textBox257.TabIndex = 7;
      this.textBox257.TextChanged += new EventHandler(this.textBox257_TextChanged);
      this.label197.AutoSize = true;
      this.label197.ForeColor = Color.MediumVioletRed;
      this.label197.Location = new Point(51, 42);
      this.label197.Name = "label197";
      this.label197.Size = new Size(58, 16);
      this.label197.TabIndex = 54;
      this.label197.Text = "label197";
      this.label198.AutoSize = true;
      this.label198.Location = new Point(3, 22);
      this.label198.Name = "label198";
      this.label198.Size = new Size(49, 16);
      this.label198.TabIndex = 6;
      this.label198.Text = "Item Id:";
      this.textBox258.Location = new Point(202, 13);
      this.textBox258.Name = "textBox258";
      this.textBox258.Size = new Size(49, 22);
      this.textBox258.TabIndex = 53;
      this.label199.AutoSize = true;
      this.label199.Location = new Point(7, 42);
      this.label199.Name = "label199";
      this.label199.Size = new Size(47, 16);
      this.label199.TabIndex = 8;
      this.label199.Text = "Name:";
      this.label200.AutoSize = true;
      this.label200.Location = new Point(158, 16);
      this.label200.Name = "label200";
      this.label200.Size = new Size(44, 16);
      this.label200.TabIndex = 52;
      this.label200.Text = "Count:";
      this.label201.AutoSize = true;
      this.label201.Location = new Point(257, 16);
      this.label201.Name = "label201";
      this.label201.Size = new Size(39, 16);
      this.label201.TabIndex = 14;
      this.label201.Text = "Prop:";
      this.button38.BackgroundImageLayout = ImageLayout.None;
      this.button38.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.search__5_;
      this.button38.Location = new Point(348, 10);
      this.button38.Name = "button38";
      this.button38.Size = new Size(27, 25);
      this.button38.TabIndex = 51;
      this.button38.UseVisualStyleBackColor = true;
      this.button38.Click += new EventHandler(this.button38_Click);
      this.textBox259.Location = new Point(295, 13);
      this.textBox259.Name = "textBox259";
      this.textBox259.Size = new Size(49, 22);
      this.textBox259.TabIndex = 15;
      this.pictureBox29.Location = new Point(115, 10);
      this.pictureBox29.Name = "pictureBox29";
      this.pictureBox29.Size = new Size(32, 32);
      this.pictureBox29.TabIndex = 50;
      this.pictureBox29.TabStop = false;
      this.groupBox36.Controls.Add((Control) this.textBox260);
      this.groupBox36.Controls.Add((Control) this.label202);
      this.groupBox36.Controls.Add((Control) this.label203);
      this.groupBox36.Controls.Add((Control) this.textBox261);
      this.groupBox36.Controls.Add((Control) this.label204);
      this.groupBox36.Controls.Add((Control) this.label205);
      this.groupBox36.Controls.Add((Control) this.label206);
      this.groupBox36.Controls.Add((Control) this.button39);
      this.groupBox36.Controls.Add((Control) this.textBox262);
      this.groupBox36.Controls.Add((Control) this.pictureBox30);
      this.groupBox36.Location = new Point(384, 425);
      this.groupBox36.Name = "groupBox36";
      this.groupBox36.Size = new Size(379, 58);
      this.groupBox36.TabIndex = 69;
      this.groupBox36.TabStop = false;
      this.groupBox36.Text = "Item 15.";
      this.textBox260.Location = new Point(51, 19);
      this.textBox260.Name = "textBox260";
      this.textBox260.Size = new Size(58, 22);
      this.textBox260.TabIndex = 7;
      this.textBox260.TextChanged += new EventHandler(this.textBox260_TextChanged);
      this.label202.AutoSize = true;
      this.label202.ForeColor = Color.MediumVioletRed;
      this.label202.Location = new Point(51, 42);
      this.label202.Name = "label202";
      this.label202.Size = new Size(58, 16);
      this.label202.TabIndex = 54;
      this.label202.Text = "label202";
      this.label203.AutoSize = true;
      this.label203.Location = new Point(3, 22);
      this.label203.Name = "label203";
      this.label203.Size = new Size(49, 16);
      this.label203.TabIndex = 6;
      this.label203.Text = "Item Id:";
      this.textBox261.Location = new Point(202, 13);
      this.textBox261.Name = "textBox261";
      this.textBox261.Size = new Size(49, 22);
      this.textBox261.TabIndex = 53;
      this.label204.AutoSize = true;
      this.label204.Location = new Point(7, 42);
      this.label204.Name = "label204";
      this.label204.Size = new Size(47, 16);
      this.label204.TabIndex = 8;
      this.label204.Text = "Name:";
      this.label205.AutoSize = true;
      this.label205.Location = new Point(158, 16);
      this.label205.Name = "label205";
      this.label205.Size = new Size(44, 16);
      this.label205.TabIndex = 52;
      this.label205.Text = "Count:";
      this.label206.AutoSize = true;
      this.label206.Location = new Point(257, 16);
      this.label206.Name = "label206";
      this.label206.Size = new Size(39, 16);
      this.label206.TabIndex = 14;
      this.label206.Text = "Prop:";
      this.button39.BackgroundImageLayout = ImageLayout.None;
      this.button39.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.search__5_;
      this.button39.Location = new Point(348, 10);
      this.button39.Name = "button39";
      this.button39.Size = new Size(27, 25);
      this.button39.TabIndex = 51;
      this.button39.UseVisualStyleBackColor = true;
      this.button39.Click += new EventHandler(this.button39_Click);
      this.textBox262.Location = new Point(295, 13);
      this.textBox262.Name = "textBox262";
      this.textBox262.Size = new Size(49, 22);
      this.textBox262.TabIndex = 15;
      this.pictureBox30.Location = new Point(115, 10);
      this.pictureBox30.Name = "pictureBox30";
      this.pictureBox30.Size = new Size(32, 32);
      this.pictureBox30.TabIndex = 50;
      this.pictureBox30.TabStop = false;
      this.groupBox37.Controls.Add((Control) this.textBox263);
      this.groupBox37.Controls.Add((Control) this.label207);
      this.groupBox37.Controls.Add((Control) this.label208);
      this.groupBox37.Controls.Add((Control) this.textBox264);
      this.groupBox37.Controls.Add((Control) this.label209);
      this.groupBox37.Controls.Add((Control) this.label210);
      this.groupBox37.Controls.Add((Control) this.label211);
      this.groupBox37.Controls.Add((Control) this.button40);
      this.groupBox37.Controls.Add((Control) this.textBox265);
      this.groupBox37.Controls.Add((Control) this.pictureBox31);
      this.groupBox37.Location = new Point(384, 367);
      this.groupBox37.Name = "groupBox37";
      this.groupBox37.Size = new Size(379, 58);
      this.groupBox37.TabIndex = 68;
      this.groupBox37.TabStop = false;
      this.groupBox37.Text = "Item 14.";
      this.textBox263.Location = new Point(51, 19);
      this.textBox263.Name = "textBox263";
      this.textBox263.Size = new Size(58, 22);
      this.textBox263.TabIndex = 7;
      this.textBox263.TextChanged += new EventHandler(this.textBox263_TextChanged);
      this.label207.AutoSize = true;
      this.label207.ForeColor = Color.MediumVioletRed;
      this.label207.Location = new Point(51, 42);
      this.label207.Name = "label207";
      this.label207.Size = new Size(58, 16);
      this.label207.TabIndex = 54;
      this.label207.Text = "label207";
      this.label208.AutoSize = true;
      this.label208.Location = new Point(2, 22);
      this.label208.Name = "label208";
      this.label208.Size = new Size(49, 16);
      this.label208.TabIndex = 6;
      this.label208.Text = "Item Id:";
      this.textBox264.Location = new Point(202, 13);
      this.textBox264.Name = "textBox264";
      this.textBox264.Size = new Size(49, 22);
      this.textBox264.TabIndex = 53;
      this.label209.AutoSize = true;
      this.label209.Location = new Point(7, 42);
      this.label209.Name = "label209";
      this.label209.Size = new Size(47, 16);
      this.label209.TabIndex = 8;
      this.label209.Text = "Name:";
      this.label210.AutoSize = true;
      this.label210.Location = new Point(158, 16);
      this.label210.Name = "label210";
      this.label210.Size = new Size(44, 16);
      this.label210.TabIndex = 52;
      this.label210.Text = "Count:";
      this.label211.AutoSize = true;
      this.label211.Location = new Point(257, 16);
      this.label211.Name = "label211";
      this.label211.Size = new Size(39, 16);
      this.label211.TabIndex = 14;
      this.label211.Text = "Prop:";
      this.button40.BackgroundImageLayout = ImageLayout.None;
      this.button40.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.search__5_;
      this.button40.Location = new Point(348, 10);
      this.button40.Name = "button40";
      this.button40.Size = new Size(27, 25);
      this.button40.TabIndex = 51;
      this.button40.UseVisualStyleBackColor = true;
      this.button40.Click += new EventHandler(this.button40_Click);
      this.textBox265.Location = new Point(295, 13);
      this.textBox265.Name = "textBox265";
      this.textBox265.Size = new Size(49, 22);
      this.textBox265.TabIndex = 15;
      this.pictureBox31.Location = new Point(115, 10);
      this.pictureBox31.Name = "pictureBox31";
      this.pictureBox31.Size = new Size(32, 32);
      this.pictureBox31.TabIndex = 50;
      this.pictureBox31.TabStop = false;
      this.dgDropAllItems.AllowUserToAddRows = false;
      this.dgDropAllItems.AllowUserToDeleteRows = false;
      this.dgDropAllItems.BackgroundColor = SystemColors.Control;
      this.dgDropAllItems.BorderStyle = BorderStyle.None;
      this.dgDropAllItems.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dgDropAllItems.Columns.AddRange((DataGridViewColumn) this.IconRaid, (DataGridViewColumn) this.a_npc_idx, (DataGridViewColumn) this.a_item_idx, (DataGridViewColumn) this.name_raid, (DataGridViewColumn) this.a_prob_raid, (DataGridViewColumn) this.Count);
      this.dgDropAllItems.EnableHeadersVisualStyles = false;
      this.dgDropAllItems.Location = new Point(3, 15);
      this.dgDropAllItems.Name = "dgDropAllItems";
      this.dgDropAllItems.RowHeadersVisible = false;
      this.dgDropAllItems.RowHeadersWidth = 51;
      this.dgDropAllItems.RowTemplate.Height = 32;
      this.dgDropAllItems.ScrollBars = ScrollBars.Vertical;
      this.dgDropAllItems.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
      this.dgDropAllItems.Size = new Size(378, 117);
      this.dgDropAllItems.TabIndex = 2;
      this.dgDropAllItems.CellClick += new DataGridViewCellEventHandler(this.dgDropAllItems_CellClick);
      this.IconRaid.HeaderText = "";
      this.IconRaid.MinimumWidth = 6;
      this.IconRaid.Name = "IconRaid";
      this.IconRaid.Width = 32;
      this.a_npc_idx.HeaderText = "Boss";
      this.a_npc_idx.MinimumWidth = 6;
      this.a_npc_idx.Name = "a_npc_idx";
      this.a_npc_idx.Visible = false;
      this.a_npc_idx.Width = 50;
      this.a_item_idx.HeaderText = "Item_Id";
      this.a_item_idx.MinimumWidth = 6;
      this.a_item_idx.Name = "a_item_idx";
      this.a_item_idx.Width = 70;
      this.name_raid.HeaderText = "Name";
      this.name_raid.MinimumWidth = 6;
      this.name_raid.Name = "name_raid";
      this.name_raid.ReadOnly = true;
      this.name_raid.Width = 150;
      this.a_prob_raid.HeaderText = "Prob";
      this.a_prob_raid.MinimumWidth = 6;
      this.a_prob_raid.Name = "a_prob_raid";
      this.a_prob_raid.Width = 70;
      this.Count.HeaderText = "Count";
      this.Count.MinimumWidth = 6;
      this.Count.Name = "Count";
      this.Count.Width = 60;
      this.groupBox38.Controls.Add((Control) this.textBox266);
      this.groupBox38.Controls.Add((Control) this.label212);
      this.groupBox38.Controls.Add((Control) this.label213);
      this.groupBox38.Controls.Add((Control) this.textBox267);
      this.groupBox38.Controls.Add((Control) this.label214);
      this.groupBox38.Controls.Add((Control) this.label215);
      this.groupBox38.Controls.Add((Control) this.label216);
      this.groupBox38.Controls.Add((Control) this.button41);
      this.groupBox38.Controls.Add((Control) this.textBox268);
      this.groupBox38.Controls.Add((Control) this.pictureBox32);
      this.groupBox38.Location = new Point(384, 309);
      this.groupBox38.Name = "groupBox38";
      this.groupBox38.Size = new Size(379, 58);
      this.groupBox38.TabIndex = 67;
      this.groupBox38.TabStop = false;
      this.groupBox38.Text = "Item 13.";
      this.textBox266.Location = new Point(51, 19);
      this.textBox266.Name = "textBox266";
      this.textBox266.Size = new Size(58, 22);
      this.textBox266.TabIndex = 7;
      this.textBox266.TextChanged += new EventHandler(this.textBox266_TextChanged);
      this.label212.AutoSize = true;
      this.label212.ForeColor = Color.MediumVioletRed;
      this.label212.Location = new Point(51, 42);
      this.label212.Name = "label212";
      this.label212.Size = new Size(58, 16);
      this.label212.TabIndex = 54;
      this.label212.Text = "label212";
      this.label213.AutoSize = true;
      this.label213.Location = new Point(3, 22);
      this.label213.Name = "label213";
      this.label213.Size = new Size(49, 16);
      this.label213.TabIndex = 6;
      this.label213.Text = "Item Id:";
      this.textBox267.Location = new Point(202, 13);
      this.textBox267.Name = "textBox267";
      this.textBox267.Size = new Size(49, 22);
      this.textBox267.TabIndex = 53;
      this.label214.AutoSize = true;
      this.label214.Location = new Point(7, 42);
      this.label214.Name = "label214";
      this.label214.Size = new Size(47, 16);
      this.label214.TabIndex = 8;
      this.label214.Text = "Name:";
      this.label215.AutoSize = true;
      this.label215.Location = new Point(158, 16);
      this.label215.Name = "label215";
      this.label215.Size = new Size(44, 16);
      this.label215.TabIndex = 52;
      this.label215.Text = "Count:";
      this.label216.AutoSize = true;
      this.label216.Location = new Point(257, 16);
      this.label216.Name = "label216";
      this.label216.Size = new Size(39, 16);
      this.label216.TabIndex = 14;
      this.label216.Text = "Prop:";
      this.button41.BackgroundImageLayout = ImageLayout.None;
      this.button41.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.search__5_;
      this.button41.Location = new Point(348, 10);
      this.button41.Name = "button41";
      this.button41.Size = new Size(27, 25);
      this.button41.TabIndex = 51;
      this.button41.UseVisualStyleBackColor = true;
      this.button41.Click += new EventHandler(this.button41_Click);
      this.textBox268.Location = new Point(295, 13);
      this.textBox268.Name = "textBox268";
      this.textBox268.Size = new Size(49, 22);
      this.textBox268.TabIndex = 15;
      this.pictureBox32.Location = new Point(115, 10);
      this.pictureBox32.Name = "pictureBox32";
      this.pictureBox32.Size = new Size(32, 32);
      this.pictureBox32.TabIndex = 50;
      this.pictureBox32.TabStop = false;
      this.groupBox39.Controls.Add((Control) this.textBox269);
      this.groupBox39.Controls.Add((Control) this.label217);
      this.groupBox39.Controls.Add((Control) this.label218);
      this.groupBox39.Controls.Add((Control) this.textBox270);
      this.groupBox39.Controls.Add((Control) this.label219);
      this.groupBox39.Controls.Add((Control) this.label220);
      this.groupBox39.Controls.Add((Control) this.label221);
      this.groupBox39.Controls.Add((Control) this.button42);
      this.groupBox39.Controls.Add((Control) this.textBox271);
      this.groupBox39.Controls.Add((Control) this.pictureBox33);
      this.groupBox39.Location = new Point(384, 251);
      this.groupBox39.Name = "groupBox39";
      this.groupBox39.Size = new Size(379, 58);
      this.groupBox39.TabIndex = 66;
      this.groupBox39.TabStop = false;
      this.groupBox39.Text = "Item 12.";
      this.textBox269.Location = new Point(51, 19);
      this.textBox269.Name = "textBox269";
      this.textBox269.Size = new Size(58, 22);
      this.textBox269.TabIndex = 7;
      this.textBox269.TextChanged += new EventHandler(this.textBox269_TextChanged);
      this.label217.AutoSize = true;
      this.label217.ForeColor = Color.MediumVioletRed;
      this.label217.Location = new Point(51, 42);
      this.label217.Name = "label217";
      this.label217.Size = new Size(58, 16);
      this.label217.TabIndex = 54;
      this.label217.Text = "label217";
      this.label218.AutoSize = true;
      this.label218.Location = new Point(3, 22);
      this.label218.Name = "label218";
      this.label218.Size = new Size(49, 16);
      this.label218.TabIndex = 6;
      this.label218.Text = "Item Id:";
      this.textBox270.Location = new Point(202, 13);
      this.textBox270.Name = "textBox270";
      this.textBox270.Size = new Size(49, 22);
      this.textBox270.TabIndex = 53;
      this.label219.AutoSize = true;
      this.label219.Location = new Point(7, 42);
      this.label219.Name = "label219";
      this.label219.Size = new Size(47, 16);
      this.label219.TabIndex = 8;
      this.label219.Text = "Name:";
      this.label220.AutoSize = true;
      this.label220.Location = new Point(158, 16);
      this.label220.Name = "label220";
      this.label220.Size = new Size(44, 16);
      this.label220.TabIndex = 52;
      this.label220.Text = "Count:";
      this.label221.AutoSize = true;
      this.label221.Location = new Point(257, 16);
      this.label221.Name = "label221";
      this.label221.Size = new Size(39, 16);
      this.label221.TabIndex = 14;
      this.label221.Text = "Prop:";
      this.button42.BackgroundImageLayout = ImageLayout.None;
      this.button42.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.search__5_;
      this.button42.Location = new Point(348, 10);
      this.button42.Name = "button42";
      this.button42.Size = new Size(27, 25);
      this.button42.TabIndex = 51;
      this.button42.UseVisualStyleBackColor = true;
      this.button42.Click += new EventHandler(this.button42_Click);
      this.textBox271.Location = new Point(295, 13);
      this.textBox271.Name = "textBox271";
      this.textBox271.Size = new Size(49, 22);
      this.textBox271.TabIndex = 15;
      this.pictureBox33.Location = new Point(115, 10);
      this.pictureBox33.Name = "pictureBox33";
      this.pictureBox33.Size = new Size(32, 32);
      this.pictureBox33.TabIndex = 50;
      this.pictureBox33.TabStop = false;
      this.groupBox40.Controls.Add((Control) this.textBox272);
      this.groupBox40.Controls.Add((Control) this.label222);
      this.groupBox40.Controls.Add((Control) this.label223);
      this.groupBox40.Controls.Add((Control) this.textBox273);
      this.groupBox40.Controls.Add((Control) this.label224);
      this.groupBox40.Controls.Add((Control) this.label225);
      this.groupBox40.Controls.Add((Control) this.label226);
      this.groupBox40.Controls.Add((Control) this.button43);
      this.groupBox40.Controls.Add((Control) this.textBox274);
      this.groupBox40.Controls.Add((Control) this.pictureBox34);
      this.groupBox40.Location = new Point(384, 193);
      this.groupBox40.Name = "groupBox40";
      this.groupBox40.Size = new Size(379, 58);
      this.groupBox40.TabIndex = 65;
      this.groupBox40.TabStop = false;
      this.groupBox40.Text = "Item 11.";
      this.textBox272.Location = new Point(51, 19);
      this.textBox272.Name = "textBox272";
      this.textBox272.Size = new Size(58, 22);
      this.textBox272.TabIndex = 7;
      this.textBox272.TextChanged += new EventHandler(this.textBox272_TextChanged);
      this.label222.AutoSize = true;
      this.label222.ForeColor = Color.MediumVioletRed;
      this.label222.Location = new Point(51, 42);
      this.label222.Name = "label222";
      this.label222.Size = new Size(58, 16);
      this.label222.TabIndex = 54;
      this.label222.Text = "label222";
      this.label223.AutoSize = true;
      this.label223.Location = new Point(3, 22);
      this.label223.Name = "label223";
      this.label223.Size = new Size(49, 16);
      this.label223.TabIndex = 6;
      this.label223.Text = "Item Id:";
      this.textBox273.Location = new Point(202, 13);
      this.textBox273.Name = "textBox273";
      this.textBox273.Size = new Size(49, 22);
      this.textBox273.TabIndex = 53;
      this.label224.AutoSize = true;
      this.label224.Location = new Point(7, 42);
      this.label224.Name = "label224";
      this.label224.Size = new Size(47, 16);
      this.label224.TabIndex = 8;
      this.label224.Text = "Name:";
      this.label225.AutoSize = true;
      this.label225.Location = new Point(158, 16);
      this.label225.Name = "label225";
      this.label225.Size = new Size(44, 16);
      this.label225.TabIndex = 52;
      this.label225.Text = "Count:";
      this.label226.AutoSize = true;
      this.label226.Location = new Point(257, 16);
      this.label226.Name = "label226";
      this.label226.Size = new Size(39, 16);
      this.label226.TabIndex = 14;
      this.label226.Text = "Prop:";
      this.button43.BackgroundImageLayout = ImageLayout.None;
      this.button43.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.search__5_;
      this.button43.Location = new Point(348, 10);
      this.button43.Name = "button43";
      this.button43.Size = new Size(27, 25);
      this.button43.TabIndex = 51;
      this.button43.UseVisualStyleBackColor = true;
      this.button43.Click += new EventHandler(this.button43_Click);
      this.textBox274.Location = new Point(295, 13);
      this.textBox274.Name = "textBox274";
      this.textBox274.Size = new Size(49, 22);
      this.textBox274.TabIndex = 15;
      this.pictureBox34.Location = new Point(115, 10);
      this.pictureBox34.Name = "pictureBox34";
      this.pictureBox34.Size = new Size(32, 32);
      this.pictureBox34.TabIndex = 50;
      this.pictureBox34.TabStop = false;
      this.groupBox41.Controls.Add((Control) this.textBox275);
      this.groupBox41.Controls.Add((Control) this.label227);
      this.groupBox41.Controls.Add((Control) this.label228);
      this.groupBox41.Controls.Add((Control) this.textBox276);
      this.groupBox41.Controls.Add((Control) this.label229);
      this.groupBox41.Controls.Add((Control) this.label230);
      this.groupBox41.Controls.Add((Control) this.label231);
      this.groupBox41.Controls.Add((Control) this.button44);
      this.groupBox41.Controls.Add((Control) this.textBox277);
      this.groupBox41.Controls.Add((Control) this.pictureBox35);
      this.groupBox41.Location = new Point(384, 135);
      this.groupBox41.Name = "groupBox41";
      this.groupBox41.Size = new Size(379, 58);
      this.groupBox41.TabIndex = 64;
      this.groupBox41.TabStop = false;
      this.groupBox41.Text = "Item 10.";
      this.textBox275.Location = new Point(51, 19);
      this.textBox275.Name = "textBox275";
      this.textBox275.Size = new Size(58, 22);
      this.textBox275.TabIndex = 7;
      this.textBox275.TextChanged += new EventHandler(this.textBox275_TextChanged);
      this.label227.AutoSize = true;
      this.label227.ForeColor = Color.MediumVioletRed;
      this.label227.Location = new Point(51, 42);
      this.label227.Name = "label227";
      this.label227.Size = new Size(58, 16);
      this.label227.TabIndex = 54;
      this.label227.Text = "label227";
      this.label228.AutoSize = true;
      this.label228.Location = new Point(3, 22);
      this.label228.Name = "label228";
      this.label228.Size = new Size(49, 16);
      this.label228.TabIndex = 6;
      this.label228.Text = "Item Id:";
      this.textBox276.Location = new Point(202, 13);
      this.textBox276.Name = "textBox276";
      this.textBox276.Size = new Size(49, 22);
      this.textBox276.TabIndex = 53;
      this.label229.AutoSize = true;
      this.label229.Location = new Point(7, 42);
      this.label229.Name = "label229";
      this.label229.Size = new Size(47, 16);
      this.label229.TabIndex = 8;
      this.label229.Text = "Name:";
      this.label230.AutoSize = true;
      this.label230.Location = new Point(158, 16);
      this.label230.Name = "label230";
      this.label230.Size = new Size(44, 16);
      this.label230.TabIndex = 52;
      this.label230.Text = "Count:";
      this.label231.AutoSize = true;
      this.label231.Location = new Point(257, 16);
      this.label231.Name = "label231";
      this.label231.Size = new Size(39, 16);
      this.label231.TabIndex = 14;
      this.label231.Text = "Prop:";
      this.button44.BackgroundImageLayout = ImageLayout.None;
      this.button44.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.search__5_;
      this.button44.Location = new Point(348, 10);
      this.button44.Name = "button44";
      this.button44.Size = new Size(27, 25);
      this.button44.TabIndex = 51;
      this.button44.UseVisualStyleBackColor = true;
      this.button44.Click += new EventHandler(this.button44_Click);
      this.textBox277.Location = new Point(295, 13);
      this.textBox277.Name = "textBox277";
      this.textBox277.Size = new Size(49, 22);
      this.textBox277.TabIndex = 15;
      this.pictureBox35.Location = new Point(115, 10);
      this.pictureBox35.Name = "pictureBox35";
      this.pictureBox35.Size = new Size(32, 32);
      this.pictureBox35.TabIndex = 50;
      this.pictureBox35.TabStop = false;
      this.groupBox32.Controls.Add((Control) this.textBox248);
      this.groupBox32.Controls.Add((Control) this.label182);
      this.groupBox32.Controls.Add((Control) this.label183);
      this.groupBox32.Controls.Add((Control) this.textBox249);
      this.groupBox32.Controls.Add((Control) this.label184);
      this.groupBox32.Controls.Add((Control) this.label185);
      this.groupBox32.Controls.Add((Control) this.label186);
      this.groupBox32.Controls.Add((Control) this.button35);
      this.groupBox32.Controls.Add((Control) this.textBox250);
      this.groupBox32.Controls.Add((Control) this.pictureBox26);
      this.groupBox32.Location = new Point(384, 77);
      this.groupBox32.Name = "groupBox32";
      this.groupBox32.Size = new Size(379, 58);
      this.groupBox32.TabIndex = 63;
      this.groupBox32.TabStop = false;
      this.groupBox32.Text = "Item 9.";
      this.textBox248.Location = new Point(51, 19);
      this.textBox248.Name = "textBox248";
      this.textBox248.Size = new Size(58, 22);
      this.textBox248.TabIndex = 7;
      this.textBox248.TextChanged += new EventHandler(this.textBox248_TextChanged);
      this.label182.AutoSize = true;
      this.label182.ForeColor = Color.MediumVioletRed;
      this.label182.Location = new Point(51, 42);
      this.label182.Name = "label182";
      this.label182.Size = new Size(58, 16);
      this.label182.TabIndex = 54;
      this.label182.Text = "label182";
      this.label183.AutoSize = true;
      this.label183.Location = new Point(3, 22);
      this.label183.Name = "label183";
      this.label183.Size = new Size(49, 16);
      this.label183.TabIndex = 6;
      this.label183.Text = "Item Id:";
      this.textBox249.Location = new Point(202, 13);
      this.textBox249.Name = "textBox249";
      this.textBox249.Size = new Size(49, 22);
      this.textBox249.TabIndex = 53;
      this.label184.AutoSize = true;
      this.label184.Location = new Point(7, 42);
      this.label184.Name = "label184";
      this.label184.Size = new Size(47, 16);
      this.label184.TabIndex = 8;
      this.label184.Text = "Name:";
      this.label185.AutoSize = true;
      this.label185.Location = new Point(158, 16);
      this.label185.Name = "label185";
      this.label185.Size = new Size(44, 16);
      this.label185.TabIndex = 52;
      this.label185.Text = "Count:";
      this.label186.AutoSize = true;
      this.label186.Location = new Point(257, 16);
      this.label186.Name = "label186";
      this.label186.Size = new Size(39, 16);
      this.label186.TabIndex = 14;
      this.label186.Text = "Prop:";
      this.button35.BackgroundImageLayout = ImageLayout.None;
      this.button35.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.search__5_;
      this.button35.Location = new Point(350, 10);
      this.button35.Name = "button35";
      this.button35.Size = new Size(27, 25);
      this.button35.TabIndex = 51;
      this.button35.UseVisualStyleBackColor = true;
      this.button35.Click += new EventHandler(this.button35_Click);
      this.textBox250.Location = new Point(295, 13);
      this.textBox250.Name = "textBox250";
      this.textBox250.Size = new Size(49, 22);
      this.textBox250.TabIndex = 15;
      this.pictureBox26.Location = new Point(115, 10);
      this.pictureBox26.Name = "pictureBox26";
      this.pictureBox26.Size = new Size(32, 32);
      this.pictureBox26.TabIndex = 50;
      this.pictureBox26.TabStop = false;
      this.groupBox30.Controls.Add((Control) this.textBox242);
      this.groupBox30.Controls.Add((Control) this.label172);
      this.groupBox30.Controls.Add((Control) this.label173);
      this.groupBox30.Controls.Add((Control) this.textBox243);
      this.groupBox30.Controls.Add((Control) this.label174);
      this.groupBox30.Controls.Add((Control) this.label175);
      this.groupBox30.Controls.Add((Control) this.label176);
      this.groupBox30.Controls.Add((Control) this.button33);
      this.groupBox30.Controls.Add((Control) this.textBox244);
      this.groupBox30.Controls.Add((Control) this.pictureBox24);
      this.groupBox30.Location = new Point(3, 483);
      this.groupBox30.Name = "groupBox30";
      this.groupBox30.Size = new Size(379, 58);
      this.groupBox30.TabIndex = 61;
      this.groupBox30.TabStop = false;
      this.groupBox30.Text = "Item 7.";
      this.textBox242.Location = new Point(51, 19);
      this.textBox242.Name = "textBox242";
      this.textBox242.Size = new Size(58, 22);
      this.textBox242.TabIndex = 7;
      this.textBox242.TextChanged += new EventHandler(this.textBox242_TextChanged);
      this.label172.AutoSize = true;
      this.label172.ForeColor = Color.MediumVioletRed;
      this.label172.Location = new Point(51, 42);
      this.label172.Name = "label172";
      this.label172.Size = new Size(58, 16);
      this.label172.TabIndex = 54;
      this.label172.Text = "label172";
      this.label173.AutoSize = true;
      this.label173.Location = new Point(3, 22);
      this.label173.Name = "label173";
      this.label173.Size = new Size(49, 16);
      this.label173.TabIndex = 6;
      this.label173.Text = "Item Id:";
      this.textBox243.Location = new Point(202, 13);
      this.textBox243.Name = "textBox243";
      this.textBox243.Size = new Size(49, 22);
      this.textBox243.TabIndex = 53;
      this.label174.AutoSize = true;
      this.label174.Location = new Point(7, 42);
      this.label174.Name = "label174";
      this.label174.Size = new Size(47, 16);
      this.label174.TabIndex = 8;
      this.label174.Text = "Name:";
      this.label175.AutoSize = true;
      this.label175.Location = new Point(158, 16);
      this.label175.Name = "label175";
      this.label175.Size = new Size(44, 16);
      this.label175.TabIndex = 52;
      this.label175.Text = "Count:";
      this.label176.AutoSize = true;
      this.label176.Location = new Point(257, 16);
      this.label176.Name = "label176";
      this.label176.Size = new Size(39, 16);
      this.label176.TabIndex = 14;
      this.label176.Text = "Prop:";
      this.button33.BackgroundImageLayout = ImageLayout.None;
      this.button33.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.search__5_;
      this.button33.Location = new Point(348, 10);
      this.button33.Name = "button33";
      this.button33.Size = new Size(27, 25);
      this.button33.TabIndex = 51;
      this.button33.UseVisualStyleBackColor = true;
      this.button33.Click += new EventHandler(this.button33_Click);
      this.textBox244.Location = new Point(295, 13);
      this.textBox244.Name = "textBox244";
      this.textBox244.Size = new Size(49, 22);
      this.textBox244.TabIndex = 15;
      this.pictureBox24.Location = new Point(115, 10);
      this.pictureBox24.Name = "pictureBox24";
      this.pictureBox24.Size = new Size(32, 32);
      this.pictureBox24.TabIndex = 50;
      this.pictureBox24.TabStop = false;
      this.groupBox29.Controls.Add((Control) this.textBox239);
      this.groupBox29.Controls.Add((Control) this.label167);
      this.groupBox29.Controls.Add((Control) this.label168);
      this.groupBox29.Controls.Add((Control) this.textBox240);
      this.groupBox29.Controls.Add((Control) this.label169);
      this.groupBox29.Controls.Add((Control) this.label170);
      this.groupBox29.Controls.Add((Control) this.label171);
      this.groupBox29.Controls.Add((Control) this.button32);
      this.groupBox29.Controls.Add((Control) this.textBox241);
      this.groupBox29.Controls.Add((Control) this.pictureBox22);
      this.groupBox29.Location = new Point(3, 425);
      this.groupBox29.Name = "groupBox29";
      this.groupBox29.Size = new Size(379, 58);
      this.groupBox29.TabIndex = 60;
      this.groupBox29.TabStop = false;
      this.groupBox29.Text = "Item 6.";
      this.textBox239.Location = new Point(51, 19);
      this.textBox239.Name = "textBox239";
      this.textBox239.Size = new Size(58, 22);
      this.textBox239.TabIndex = 7;
      this.textBox239.TextChanged += new EventHandler(this.textBox239_TextChanged);
      this.label167.AutoSize = true;
      this.label167.ForeColor = Color.MediumVioletRed;
      this.label167.Location = new Point(51, 42);
      this.label167.Name = "label167";
      this.label167.Size = new Size(58, 16);
      this.label167.TabIndex = 54;
      this.label167.Text = "label167";
      this.label168.AutoSize = true;
      this.label168.Location = new Point(3, 22);
      this.label168.Name = "label168";
      this.label168.Size = new Size(49, 16);
      this.label168.TabIndex = 6;
      this.label168.Text = "Item Id:";
      this.textBox240.Location = new Point(202, 13);
      this.textBox240.Name = "textBox240";
      this.textBox240.Size = new Size(49, 22);
      this.textBox240.TabIndex = 53;
      this.label169.AutoSize = true;
      this.label169.Location = new Point(7, 42);
      this.label169.Name = "label169";
      this.label169.Size = new Size(47, 16);
      this.label169.TabIndex = 8;
      this.label169.Text = "Name:";
      this.label170.AutoSize = true;
      this.label170.Location = new Point(158, 16);
      this.label170.Name = "label170";
      this.label170.Size = new Size(44, 16);
      this.label170.TabIndex = 52;
      this.label170.Text = "Count:";
      this.label171.AutoSize = true;
      this.label171.Location = new Point(257, 16);
      this.label171.Name = "label171";
      this.label171.Size = new Size(39, 16);
      this.label171.TabIndex = 14;
      this.label171.Text = "Prop:";
      this.button32.BackgroundImageLayout = ImageLayout.None;
      this.button32.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.search__5_;
      this.button32.Location = new Point(348, 10);
      this.button32.Name = "button32";
      this.button32.Size = new Size(27, 25);
      this.button32.TabIndex = 51;
      this.button32.UseVisualStyleBackColor = true;
      this.button32.Click += new EventHandler(this.button32_Click);
      this.textBox241.Location = new Point(295, 13);
      this.textBox241.Name = "textBox241";
      this.textBox241.Size = new Size(49, 22);
      this.textBox241.TabIndex = 15;
      this.pictureBox22.Location = new Point(115, 10);
      this.pictureBox22.Name = "pictureBox22";
      this.pictureBox22.Size = new Size(32, 32);
      this.pictureBox22.TabIndex = 50;
      this.pictureBox22.TabStop = false;
      this.groupBox31.Controls.Add((Control) this.textBox245);
      this.groupBox31.Controls.Add((Control) this.label177);
      this.groupBox31.Controls.Add((Control) this.label178);
      this.groupBox31.Controls.Add((Control) this.textBox246);
      this.groupBox31.Controls.Add((Control) this.label179);
      this.groupBox31.Controls.Add((Control) this.label180);
      this.groupBox31.Controls.Add((Control) this.label181);
      this.groupBox31.Controls.Add((Control) this.button34);
      this.groupBox31.Controls.Add((Control) this.textBox247);
      this.groupBox31.Controls.Add((Control) this.pictureBox25);
      this.groupBox31.Location = new Point(384, 19);
      this.groupBox31.Name = "groupBox31";
      this.groupBox31.Size = new Size(379, 58);
      this.groupBox31.TabIndex = 62;
      this.groupBox31.TabStop = false;
      this.groupBox31.Text = "Item 8.";
      this.textBox245.Location = new Point(51, 19);
      this.textBox245.Name = "textBox245";
      this.textBox245.Size = new Size(58, 22);
      this.textBox245.TabIndex = 7;
      this.textBox245.TextChanged += new EventHandler(this.textBox245_TextChanged);
      this.label177.AutoSize = true;
      this.label177.ForeColor = Color.MediumVioletRed;
      this.label177.Location = new Point(51, 42);
      this.label177.Name = "label177";
      this.label177.Size = new Size(58, 16);
      this.label177.TabIndex = 54;
      this.label177.Text = "label177";
      this.label178.AutoSize = true;
      this.label178.Location = new Point(3, 22);
      this.label178.Name = "label178";
      this.label178.Size = new Size(49, 16);
      this.label178.TabIndex = 6;
      this.label178.Text = "Item Id:";
      this.textBox246.Location = new Point(202, 13);
      this.textBox246.Name = "textBox246";
      this.textBox246.Size = new Size(49, 22);
      this.textBox246.TabIndex = 53;
      this.label179.AutoSize = true;
      this.label179.Location = new Point(7, 42);
      this.label179.Name = "label179";
      this.label179.Size = new Size(47, 16);
      this.label179.TabIndex = 8;
      this.label179.Text = "Name:";
      this.label180.AutoSize = true;
      this.label180.Location = new Point(158, 16);
      this.label180.Name = "label180";
      this.label180.Size = new Size(44, 16);
      this.label180.TabIndex = 52;
      this.label180.Text = "Count:";
      this.label181.AutoSize = true;
      this.label181.Location = new Point(257, 16);
      this.label181.Name = "label181";
      this.label181.Size = new Size(39, 16);
      this.label181.TabIndex = 14;
      this.label181.Text = "Prop:";
      this.button34.BackgroundImageLayout = ImageLayout.None;
      this.button34.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.search__5_;
      this.button34.Location = new Point(350, 10);
      this.button34.Name = "button34";
      this.button34.Size = new Size(27, 25);
      this.button34.TabIndex = 51;
      this.button34.UseVisualStyleBackColor = true;
      this.button34.Click += new EventHandler(this.button34_Click);
      this.textBox247.Location = new Point(295, 13);
      this.textBox247.Name = "textBox247";
      this.textBox247.Size = new Size(49, 22);
      this.textBox247.TabIndex = 15;
      this.pictureBox25.Location = new Point(115, 10);
      this.pictureBox25.Name = "pictureBox25";
      this.pictureBox25.Size = new Size(32, 32);
      this.pictureBox25.TabIndex = 50;
      this.pictureBox25.TabStop = false;
      this.groupBox28.Controls.Add((Control) this.textBox236);
      this.groupBox28.Controls.Add((Control) this.label162);
      this.groupBox28.Controls.Add((Control) this.label163);
      this.groupBox28.Controls.Add((Control) this.textBox237);
      this.groupBox28.Controls.Add((Control) this.label164);
      this.groupBox28.Controls.Add((Control) this.label165);
      this.groupBox28.Controls.Add((Control) this.label166);
      this.groupBox28.Controls.Add((Control) this.button31);
      this.groupBox28.Controls.Add((Control) this.textBox238);
      this.groupBox28.Controls.Add((Control) this.pictureBox21);
      this.groupBox28.Location = new Point(3, 367);
      this.groupBox28.Name = "groupBox28";
      this.groupBox28.Size = new Size(379, 58);
      this.groupBox28.TabIndex = 59;
      this.groupBox28.TabStop = false;
      this.groupBox28.Text = "Item 5.";
      this.textBox236.Location = new Point(51, 19);
      this.textBox236.Name = "textBox236";
      this.textBox236.Size = new Size(58, 22);
      this.textBox236.TabIndex = 7;
      this.textBox236.TextChanged += new EventHandler(this.textBox236_TextChanged);
      this.label162.AutoSize = true;
      this.label162.ForeColor = Color.MediumVioletRed;
      this.label162.Location = new Point(51, 42);
      this.label162.Name = "label162";
      this.label162.Size = new Size(58, 16);
      this.label162.TabIndex = 54;
      this.label162.Text = "label162";
      this.label163.AutoSize = true;
      this.label163.Location = new Point(3, 22);
      this.label163.Name = "label163";
      this.label163.Size = new Size(49, 16);
      this.label163.TabIndex = 6;
      this.label163.Text = "Item Id:";
      this.textBox237.Location = new Point(202, 13);
      this.textBox237.Name = "textBox237";
      this.textBox237.Size = new Size(49, 22);
      this.textBox237.TabIndex = 53;
      this.label164.AutoSize = true;
      this.label164.Location = new Point(7, 42);
      this.label164.Name = "label164";
      this.label164.Size = new Size(47, 16);
      this.label164.TabIndex = 8;
      this.label164.Text = "Name:";
      this.label165.AutoSize = true;
      this.label165.Location = new Point(158, 16);
      this.label165.Name = "label165";
      this.label165.Size = new Size(44, 16);
      this.label165.TabIndex = 52;
      this.label165.Text = "Count:";
      this.label166.AutoSize = true;
      this.label166.Location = new Point(257, 16);
      this.label166.Name = "label166";
      this.label166.Size = new Size(39, 16);
      this.label166.TabIndex = 14;
      this.label166.Text = "Prop:";
      this.button31.BackgroundImageLayout = ImageLayout.None;
      this.button31.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.search__5_;
      this.button31.Location = new Point(348, 10);
      this.button31.Name = "button31";
      this.button31.Size = new Size(27, 25);
      this.button31.TabIndex = 51;
      this.button31.UseVisualStyleBackColor = true;
      this.button31.Click += new EventHandler(this.button31_Click);
      this.textBox238.Location = new Point(295, 13);
      this.textBox238.Name = "textBox238";
      this.textBox238.Size = new Size(49, 22);
      this.textBox238.TabIndex = 15;
      this.pictureBox21.Location = new Point(115, 10);
      this.pictureBox21.Name = "pictureBox21";
      this.pictureBox21.Size = new Size(32, 32);
      this.pictureBox21.TabIndex = 50;
      this.pictureBox21.TabStop = false;
      this.groupBox27.Controls.Add((Control) this.textBox233);
      this.groupBox27.Controls.Add((Control) this.label157);
      this.groupBox27.Controls.Add((Control) this.label158);
      this.groupBox27.Controls.Add((Control) this.textBox234);
      this.groupBox27.Controls.Add((Control) this.label159);
      this.groupBox27.Controls.Add((Control) this.label160);
      this.groupBox27.Controls.Add((Control) this.label161);
      this.groupBox27.Controls.Add((Control) this.button30);
      this.groupBox27.Controls.Add((Control) this.textBox235);
      this.groupBox27.Controls.Add((Control) this.pictureBox20);
      this.groupBox27.Location = new Point(3, 309);
      this.groupBox27.Name = "groupBox27";
      this.groupBox27.Size = new Size(379, 58);
      this.groupBox27.TabIndex = 58;
      this.groupBox27.TabStop = false;
      this.groupBox27.Text = "Item 4.";
      this.textBox233.Location = new Point(51, 19);
      this.textBox233.Name = "textBox233";
      this.textBox233.Size = new Size(58, 22);
      this.textBox233.TabIndex = 7;
      this.textBox233.TextChanged += new EventHandler(this.textBox233_TextChanged);
      this.label157.AutoSize = true;
      this.label157.ForeColor = Color.MediumVioletRed;
      this.label157.Location = new Point(51, 42);
      this.label157.Name = "label157";
      this.label157.Size = new Size(58, 16);
      this.label157.TabIndex = 54;
      this.label157.Text = "label157";
      this.label158.AutoSize = true;
      this.label158.Location = new Point(3, 22);
      this.label158.Name = "label158";
      this.label158.Size = new Size(49, 16);
      this.label158.TabIndex = 6;
      this.label158.Text = "Item Id:";
      this.textBox234.Location = new Point(202, 13);
      this.textBox234.Name = "textBox234";
      this.textBox234.Size = new Size(49, 22);
      this.textBox234.TabIndex = 53;
      this.label159.AutoSize = true;
      this.label159.Location = new Point(7, 42);
      this.label159.Name = "label159";
      this.label159.Size = new Size(47, 16);
      this.label159.TabIndex = 8;
      this.label159.Text = "Name:";
      this.label160.AutoSize = true;
      this.label160.Location = new Point(158, 16);
      this.label160.Name = "label160";
      this.label160.Size = new Size(44, 16);
      this.label160.TabIndex = 52;
      this.label160.Text = "Count:";
      this.label161.AutoSize = true;
      this.label161.Location = new Point(257, 16);
      this.label161.Name = "label161";
      this.label161.Size = new Size(39, 16);
      this.label161.TabIndex = 14;
      this.label161.Text = "Prop:";
      this.button30.BackgroundImageLayout = ImageLayout.None;
      this.button30.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.search__5_;
      this.button30.Location = new Point(348, 10);
      this.button30.Name = "button30";
      this.button30.Size = new Size(27, 25);
      this.button30.TabIndex = 51;
      this.button30.UseVisualStyleBackColor = true;
      this.button30.Click += new EventHandler(this.button30_Click);
      this.textBox235.Location = new Point(295, 13);
      this.textBox235.Name = "textBox235";
      this.textBox235.Size = new Size(49, 22);
      this.textBox235.TabIndex = 15;
      this.pictureBox20.Location = new Point(115, 10);
      this.pictureBox20.Name = "pictureBox20";
      this.pictureBox20.Size = new Size(32, 32);
      this.pictureBox20.TabIndex = 50;
      this.pictureBox20.TabStop = false;
      this.groupBox26.Controls.Add((Control) this.textBox230);
      this.groupBox26.Controls.Add((Control) this.label152);
      this.groupBox26.Controls.Add((Control) this.label153);
      this.groupBox26.Controls.Add((Control) this.textBox231);
      this.groupBox26.Controls.Add((Control) this.label154);
      this.groupBox26.Controls.Add((Control) this.label155);
      this.groupBox26.Controls.Add((Control) this.label156);
      this.groupBox26.Controls.Add((Control) this.button29);
      this.groupBox26.Controls.Add((Control) this.textBox232);
      this.groupBox26.Controls.Add((Control) this.pictureBox19);
      this.groupBox26.Location = new Point(3, 251);
      this.groupBox26.Name = "groupBox26";
      this.groupBox26.Size = new Size(379, 58);
      this.groupBox26.TabIndex = 57;
      this.groupBox26.TabStop = false;
      this.groupBox26.Text = "Item 3.";
      this.textBox230.Location = new Point(51, 19);
      this.textBox230.Name = "textBox230";
      this.textBox230.Size = new Size(58, 22);
      this.textBox230.TabIndex = 7;
      this.textBox230.TextChanged += new EventHandler(this.textBox230_TextChanged);
      this.label152.AutoSize = true;
      this.label152.ForeColor = Color.MediumVioletRed;
      this.label152.Location = new Point(51, 42);
      this.label152.Name = "label152";
      this.label152.Size = new Size(58, 16);
      this.label152.TabIndex = 54;
      this.label152.Text = "label152";
      this.label153.AutoSize = true;
      this.label153.Location = new Point(3, 22);
      this.label153.Name = "label153";
      this.label153.Size = new Size(49, 16);
      this.label153.TabIndex = 6;
      this.label153.Text = "Item Id:";
      this.textBox231.Location = new Point(202, 13);
      this.textBox231.Name = "textBox231";
      this.textBox231.Size = new Size(49, 22);
      this.textBox231.TabIndex = 53;
      this.label154.AutoSize = true;
      this.label154.Location = new Point(7, 42);
      this.label154.Name = "label154";
      this.label154.Size = new Size(47, 16);
      this.label154.TabIndex = 8;
      this.label154.Text = "Name:";
      this.label155.AutoSize = true;
      this.label155.Location = new Point(158, 16);
      this.label155.Name = "label155";
      this.label155.Size = new Size(44, 16);
      this.label155.TabIndex = 52;
      this.label155.Text = "Count:";
      this.label156.AutoSize = true;
      this.label156.Location = new Point(257, 16);
      this.label156.Name = "label156";
      this.label156.Size = new Size(39, 16);
      this.label156.TabIndex = 14;
      this.label156.Text = "Prop:";
      this.button29.BackgroundImageLayout = ImageLayout.None;
      this.button29.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.search__5_;
      this.button29.Location = new Point(348, 10);
      this.button29.Name = "button29";
      this.button29.Size = new Size(27, 25);
      this.button29.TabIndex = 51;
      this.button29.UseVisualStyleBackColor = true;
      this.button29.Click += new EventHandler(this.button29_Click);
      this.textBox232.Location = new Point(295, 13);
      this.textBox232.Name = "textBox232";
      this.textBox232.Size = new Size(49, 22);
      this.textBox232.TabIndex = 15;
      this.pictureBox19.Location = new Point(115, 10);
      this.pictureBox19.Name = "pictureBox19";
      this.pictureBox19.Size = new Size(32, 32);
      this.pictureBox19.TabIndex = 50;
      this.pictureBox19.TabStop = false;
      this.groupBox25.Controls.Add((Control) this.textBox227);
      this.groupBox25.Controls.Add((Control) this.label147);
      this.groupBox25.Controls.Add((Control) this.label148);
      this.groupBox25.Controls.Add((Control) this.textBox228);
      this.groupBox25.Controls.Add((Control) this.label149);
      this.groupBox25.Controls.Add((Control) this.label150);
      this.groupBox25.Controls.Add((Control) this.label151);
      this.groupBox25.Controls.Add((Control) this.button26);
      this.groupBox25.Controls.Add((Control) this.textBox229);
      this.groupBox25.Controls.Add((Control) this.pictureBox18);
      this.groupBox25.Location = new Point(3, 193);
      this.groupBox25.Name = "groupBox25";
      this.groupBox25.Size = new Size(379, 58);
      this.groupBox25.TabIndex = 56;
      this.groupBox25.TabStop = false;
      this.groupBox25.Text = "Item 2.";
      this.textBox227.Location = new Point(51, 19);
      this.textBox227.Name = "textBox227";
      this.textBox227.Size = new Size(58, 22);
      this.textBox227.TabIndex = 7;
      this.textBox227.TextChanged += new EventHandler(this.textBox227_TextChanged);
      this.label147.AutoSize = true;
      this.label147.ForeColor = Color.MediumVioletRed;
      this.label147.Location = new Point(51, 42);
      this.label147.Name = "label147";
      this.label147.Size = new Size(58, 16);
      this.label147.TabIndex = 54;
      this.label147.Text = "label147";
      this.label148.AutoSize = true;
      this.label148.Location = new Point(3, 22);
      this.label148.Name = "label148";
      this.label148.Size = new Size(49, 16);
      this.label148.TabIndex = 6;
      this.label148.Text = "Item Id:";
      this.textBox228.Location = new Point(202, 13);
      this.textBox228.Name = "textBox228";
      this.textBox228.Size = new Size(49, 22);
      this.textBox228.TabIndex = 53;
      this.label149.AutoSize = true;
      this.label149.Location = new Point(7, 42);
      this.label149.Name = "label149";
      this.label149.Size = new Size(47, 16);
      this.label149.TabIndex = 8;
      this.label149.Text = "Name:";
      this.label150.AutoSize = true;
      this.label150.Location = new Point(158, 16);
      this.label150.Name = "label150";
      this.label150.Size = new Size(44, 16);
      this.label150.TabIndex = 52;
      this.label150.Text = "Count:";
      this.label151.AutoSize = true;
      this.label151.Location = new Point(257, 16);
      this.label151.Name = "label151";
      this.label151.Size = new Size(39, 16);
      this.label151.TabIndex = 14;
      this.label151.Text = "Prop:";
      this.button26.BackgroundImageLayout = ImageLayout.None;
      this.button26.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.search__5_;
      this.button26.Location = new Point(348, 10);
      this.button26.Name = "button26";
      this.button26.Size = new Size(27, 25);
      this.button26.TabIndex = 51;
      this.button26.UseVisualStyleBackColor = true;
      this.button26.Click += new EventHandler(this.button26_Click);
      this.textBox229.Location = new Point(295, 13);
      this.textBox229.Name = "textBox229";
      this.textBox229.Size = new Size(49, 22);
      this.textBox229.TabIndex = 15;
      this.pictureBox18.Location = new Point(115, 10);
      this.pictureBox18.Name = "pictureBox18";
      this.pictureBox18.Size = new Size(32, 32);
      this.pictureBox18.TabIndex = 50;
      this.pictureBox18.TabStop = false;
      this.groupBox24.Controls.Add((Control) this.textBox226);
      this.groupBox24.Controls.Add((Control) this.label146);
      this.groupBox24.Controls.Add((Control) this.label145);
      this.groupBox24.Controls.Add((Control) this.textBox223);
      this.groupBox24.Controls.Add((Control) this.label144);
      this.groupBox24.Controls.Add((Control) this.label142);
      this.groupBox24.Controls.Add((Control) this.label141);
      this.groupBox24.Controls.Add((Control) this.button25);
      this.groupBox24.Controls.Add((Control) this.textBox222);
      this.groupBox24.Controls.Add((Control) this.pictureBox17);
      this.groupBox24.Location = new Point(3, 135);
      this.groupBox24.Name = "groupBox24";
      this.groupBox24.Size = new Size(379, 58);
      this.groupBox24.TabIndex = 55;
      this.groupBox24.TabStop = false;
      this.groupBox24.Text = "Item 1.";
      this.textBox226.Location = new Point(51, 19);
      this.textBox226.Name = "textBox226";
      this.textBox226.Size = new Size(58, 22);
      this.textBox226.TabIndex = 7;
      this.textBox226.TextChanged += new EventHandler(this.textBox226_TextChanged);
      this.label146.AutoSize = true;
      this.label146.ForeColor = Color.MediumVioletRed;
      this.label146.Location = new Point(51, 42);
      this.label146.Name = "label146";
      this.label146.Size = new Size(58, 16);
      this.label146.TabIndex = 54;
      this.label146.Text = "label146";
      this.label145.AutoSize = true;
      this.label145.Location = new Point(3, 22);
      this.label145.Name = "label145";
      this.label145.Size = new Size(49, 16);
      this.label145.TabIndex = 6;
      this.label145.Text = "Item Id:";
      this.textBox223.Location = new Point(202, 13);
      this.textBox223.Name = "textBox223";
      this.textBox223.Size = new Size(49, 22);
      this.textBox223.TabIndex = 53;
      this.label144.AutoSize = true;
      this.label144.Location = new Point(7, 42);
      this.label144.Name = "label144";
      this.label144.Size = new Size(47, 16);
      this.label144.TabIndex = 8;
      this.label144.Text = "Name:";
      this.label142.AutoSize = true;
      this.label142.Location = new Point(158, 16);
      this.label142.Name = "label142";
      this.label142.Size = new Size(44, 16);
      this.label142.TabIndex = 52;
      this.label142.Text = "Count:";
      this.label141.AutoSize = true;
      this.label141.Location = new Point(257, 16);
      this.label141.Name = "label141";
      this.label141.Size = new Size(39, 16);
      this.label141.TabIndex = 14;
      this.label141.Text = "Prop:";
      this.button25.BackgroundImageLayout = ImageLayout.None;
      this.button25.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.search__5_;
      this.button25.Location = new Point(348, 10);
      this.button25.Name = "button25";
      this.button25.Size = new Size(27, 25);
      this.button25.TabIndex = 51;
      this.button25.UseVisualStyleBackColor = true;
      this.button25.Click += new EventHandler(this.button25_Click);
      this.textBox222.Location = new Point(295, 13);
      this.textBox222.Name = "textBox222";
      this.textBox222.Size = new Size(49, 22);
      this.textBox222.TabIndex = 15;
      this.pictureBox17.Location = new Point(115, 10);
      this.pictureBox17.Name = "pictureBox17";
      this.pictureBox17.Size = new Size(32, 32);
      this.pictureBox17.TabIndex = 50;
      this.pictureBox17.TabStop = false;
      this.tabPage8.Location = new Point(4, 25);
      this.tabPage8.Name = "tabPage8";
      this.tabPage8.Padding = new Padding(3);
      this.tabPage8.Size = new Size(774, 607);
      this.tabPage8.TabIndex = 9;
      this.tabPage8.Text = "Drop Job";
      this.tabPage8.UseVisualStyleBackColor = true;
      this.tabPage9.Controls.Add((Control) this.clbExtra);
      this.tabPage9.Controls.Add((Control) this.tbExtraFlag);
      this.tabPage9.Controls.Add((Control) this.tbZoneFlag);
      this.tabPage9.Controls.Add((Control) this.label43);
      this.tabPage9.Controls.Add((Control) this.label94);
      this.tabPage9.Controls.Add((Control) this.clbZone);
      this.tabPage9.Location = new Point(4, 25);
      this.tabPage9.Name = "tabPage9";
      this.tabPage9.Padding = new Padding(3);
      this.tabPage9.Size = new Size(774, 607);
      this.tabPage9.TabIndex = 10;
      this.tabPage9.Text = "ZoneFlag";
      this.tabPage9.UseVisualStyleBackColor = true;
      this.clbExtra.BackColor = Color.White;
      this.clbExtra.CheckOnClick = true;
      this.clbExtra.ColumnWidth = 64;
      this.clbExtra.FormattingEnabled = true;
      this.clbExtra.Items.AddRange(new object[64]
      {
        (object) "Extra 0",
        (object) "Extra 1",
        (object) "Extra 2",
        (object) "Extra 3",
        (object) "Extra 4",
        (object) "Extra 5",
        (object) "Extra 6",
        (object) "Extra 7",
        (object) "Extra 8",
        (object) "Extra 9",
        (object) "Extra 10",
        (object) "Extra 11",
        (object) "Extra 12",
        (object) "Extra 13",
        (object) "Extra 14",
        (object) "Extra 15",
        (object) "Extra 16",
        (object) "Extra 17",
        (object) "Extra 18",
        (object) "Extra 19",
        (object) "Extra 20",
        (object) "Extra 21",
        (object) "Extra 22",
        (object) "Extra 23",
        (object) "Extra 24",
        (object) "Extra 25",
        (object) "Extra 26",
        (object) "Extra 27",
        (object) "Extra 28",
        (object) "Extra 29",
        (object) "Extra 30",
        (object) "Extra 31",
        (object) "Extra 32",
        (object) "Extra 33",
        (object) "Extra 34",
        (object) "Extra 35",
        (object) "Extra 36",
        (object) "Extra 37",
        (object) "Extra 38",
        (object) "Extra 39",
        (object) "Extra 40",
        (object) "Extra 41",
        (object) "Extra 42",
        (object) "Extra 43",
        (object) "Extra 44",
        (object) "Extra 45",
        (object) "Extra 46",
        (object) "Extra 47",
        (object) "Extra 48",
        (object) "Extra 49",
        (object) "Extra 50",
        (object) "Extra 51",
        (object) "Extra 52",
        (object) "Extra 53",
        (object) "Extra 54",
        (object) "Extra 55",
        (object) "Extra 56",
        (object) "Extra 57",
        (object) "Extra 58",
        (object) "Extra 59",
        (object) "Extra 60",
        (object) "Extra 61",
        (object) "Extra 62",
        (object) "Extra 63"
      });
      this.clbExtra.Location = new Point(281, 63);
      this.clbExtra.MultiColumn = true;
      this.clbExtra.Name = "clbExtra";
      this.clbExtra.Size = new Size(220, 480);
      this.clbExtra.TabIndex = 13;
      this.clbExtra.ThreeDCheckBoxes = true;
      this.clbExtra.Visible = false;
      this.clbExtra.ItemCheck += new ItemCheckEventHandler(this.ZoneFlagExtraItemCheck);
      this.tbExtraFlag.BackColor = Color.White;
      this.tbExtraFlag.BorderStyle = BorderStyle.FixedSingle;
      this.tbExtraFlag.ForeColor = Color.Black;
      this.tbExtraFlag.Location = new Point(604, 108);
      this.tbExtraFlag.Name = "tbExtraFlag";
      this.tbExtraFlag.Size = new Size(115, 22);
      this.tbExtraFlag.TabIndex = 12;
      this.tbExtraFlag.TextChanged += new EventHandler(this.tbExtraFlag_TextChanged);
      this.tbZoneFlag.BackColor = Color.White;
      this.tbZoneFlag.BorderStyle = BorderStyle.FixedSingle;
      this.tbZoneFlag.ForeColor = Color.Black;
      this.tbZoneFlag.Location = new Point(604, 82);
      this.tbZoneFlag.Name = "tbZoneFlag";
      this.tbZoneFlag.Size = new Size(115, 22);
      this.tbZoneFlag.TabIndex = 11;
      this.tbZoneFlag.TextChanged += new EventHandler(this.tbZoneFlag_TextChanged);
      this.label43.AutoSize = true;
      this.label43.BackColor = Color.White;
      this.label43.ForeColor = Color.Black;
      this.label43.Location = new Point(543, 111);
      this.label43.Name = "label43";
      this.label43.Size = new Size(67, 16);
      this.label43.TabIndex = 10;
      this.label43.Text = "Extra Flag";
      this.label94.AutoSize = true;
      this.label94.BackColor = Color.White;
      this.label94.ForeColor = Color.Black;
      this.label94.Location = new Point(543, 85);
      this.label94.Name = "label94";
      this.label94.Size = new Size(68, 16);
      this.label94.TabIndex = 9;
      this.label94.Text = "Zone Flag";
      this.clbZone.BackColor = Color.White;
      this.clbZone.ColumnWidth = 64;
      this.clbZone.FormattingEnabled = true;
      this.clbZone.Items.AddRange(new object[64]
      {
        (object) "Zone 0",
        (object) "Zone 1",
        (object) "Zone 2",
        (object) "Zone 3",
        (object) "Zone 4",
        (object) "Zone 5",
        (object) "Zone 6",
        (object) "Zone 7",
        (object) "Zone 8",
        (object) "Zone 9",
        (object) "Zone 10",
        (object) "Zone 11",
        (object) "Zone 12",
        (object) "Zone 13",
        (object) "Zone 14",
        (object) "Zone 15",
        (object) "Zone 16",
        (object) "Zone 17",
        (object) "Zone 18",
        (object) "Zone 19",
        (object) "Zone 20",
        (object) "Zone 21",
        (object) "Zone 22",
        (object) "Zone 23",
        (object) "Zone 24",
        (object) "Zone 25",
        (object) "Zone 26",
        (object) "Zone 27",
        (object) "Zone 28",
        (object) "Zone 29",
        (object) "Zone 30",
        (object) "Zone 31",
        (object) "Zone 32",
        (object) "Zone 33",
        (object) "Zone 34",
        (object) "Zone 35",
        (object) "Zone 36",
        (object) "Zone 37",
        (object) "Zone 38",
        (object) "Zone 39",
        (object) "Zone 40",
        (object) "Zone 41",
        (object) "Zone 42",
        (object) "Zone 43",
        (object) "Zone 44",
        (object) "Zone 45",
        (object) "Zone 46",
        (object) "Zone 47",
        (object) "Zone 48",
        (object) "Zone 49",
        (object) "Zone 50",
        (object) "Zone 51",
        (object) "Zone 52",
        (object) "Zone 53",
        (object) "Zone 54",
        (object) "Zone 55",
        (object) "Zone 56",
        (object) "Zone 57",
        (object) "Zone 58",
        (object) "Zone 59",
        (object) "Zone 60",
        (object) "Zone 61",
        (object) "Zone 62",
        (object) "Zone 63"
      });
      this.clbZone.Location = new Point(55, 63);
      this.clbZone.MultiColumn = true;
      this.clbZone.Name = "clbZone";
      this.clbZone.RightToLeft = RightToLeft.No;
      this.clbZone.Size = new Size(220, 480);
      this.clbZone.TabIndex = 8;
      this.clbZone.ThreeDCheckBoxes = true;
      this.clbZone.Visible = false;
      this.clbZone.ItemCheck += new ItemCheckEventHandler(this.ZoneFlagItemCheck);
      this.button2.Location = new Point(853, 669);
      this.button2.Name = "button2";
      this.button2.Size = new Size(100, 23);
      this.button2.TabIndex = 34;
      this.button2.Text = "Save";
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.label2.AutoSize = true;
      this.label2.Location = new Point(642, 4);
      this.label2.Name = "label2";
      this.label2.Size = new Size(53, 16);
      this.label2.TabIndex = 9;
      this.label2.Text = "Enable:";
      this.label2.Visible = false;
      this.textBox2.BorderStyle = BorderStyle.FixedSingle;
      this.textBox2.Location = new Point(691, 2);
      this.textBox2.Name = "textBox2";
      this.textBox2.Size = new Size(44, 22);
      this.textBox2.TabIndex = 18;
      this.textBox2.Visible = false;
      this.backgroundWorker1.DoWork += new DoWorkEventHandler(this.backgroundWorker1_DoWork);
      this.timer1.Enabled = true;
      this.timer1.Interval = 1;
      this.timer1.Tick += new EventHandler(this.timer1_Tick);
      this.label42.AutoSize = true;
      this.label42.BackColor = SystemColors.ControlLightLight;
      this.label42.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75f, FontStyle.Bold, GraphicsUnit.Point, (byte) 0);
      this.label42.Location = new Point(836, 3);
      this.label42.Name = "label42";
      this.label42.Size = new Size(192, 20);
      this.label42.TabIndex = 38;
      this.label42.Text = "Current Language is :";
      this.lblLang.AutoSize = true;
      this.lblLang.BackColor = SystemColors.ControlLightLight;
      this.lblLang.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75f, FontStyle.Bold, GraphicsUnit.Point, (byte) 0);
      this.lblLang.ForeColor = Color.Chartreuse;
      this.lblLang.Location = new Point(992, 5);
      this.lblLang.Name = "lblLang";
      this.lblLang.Size = new Size(0, 20);
      this.lblLang.TabIndex = 39;
      this.btnSaveAndNext.Location = new Point(960, 669);
      this.btnSaveAndNext.Name = "btnSaveAndNext";
      this.btnSaveAndNext.Size = new Size(100, 23);
      this.btnSaveAndNext.TabIndex = 40;
      this.btnSaveAndNext.Text = "Save and Next";
      this.btnSaveAndNext.UseVisualStyleBackColor = true;
      this.btnSaveAndNext.Click += new EventHandler(this.btnSaveAndNext_Click);
      this.BtnClearDrop.Location = new Point(745, 669);
      this.BtnClearDrop.Name = "BtnClearDrop";
      this.BtnClearDrop.Size = new Size(100, 23);
      this.BtnClearDrop.TabIndex = 41;
      this.BtnClearDrop.Text = "Clear Drop";
      this.BtnClearDrop.UseVisualStyleBackColor = true;
      this.BtnClearDrop.Click += new EventHandler(this.BtnClearDrop_Click);
      this.exportDropNpclodToolStripMenuItem.Name = "exportDropNpclodToolStripMenuItem";
      this.exportDropNpclodToolStripMenuItem.Size = new Size(226, 26);
      this.exportDropNpclodToolStripMenuItem.Text = "Export DropNpc.lod";
      this.exportDropNpclodToolStripMenuItem.Click += new EventHandler(this.exportDropNpclodToolStripMenuItem_Click);
      this.ClientSize = new Size(1076, 704);
      this.Controls.Add((Control) this.BtnClearDrop);
      this.Controls.Add((Control) this.btnSaveAndNext);
      this.Controls.Add((Control) this.lblLang);
      this.Controls.Add((Control) this.label42);
      this.Controls.Add((Control) this.textBox2);
      this.Controls.Add((Control) this.button2);
      this.Controls.Add((Control) this.label2);
      this.Controls.Add((Control) this.tabControl1);
      this.Controls.Add((Control) this.groupBox5);
      this.Controls.Add((Control) this.groupBox3);
      this.Controls.Add((Control) this.menuStrip1);
      this.MainMenuStrip = this.menuStrip1;
      this.MaximizeBox = false;
      this.Name = nameof (MobEditor);
      this.StartPosition = FormStartPosition.CenterScreen;
      this.Text = "MobAll EP4";
      this.Load += new EventHandler(this.MobEditor_Load);
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.groupBox3.ResumeLayout(false);
      this.groupBox5.ResumeLayout(false);
      this.groupBox5.PerformLayout();
      this.tabControl1.ResumeLayout(false);
      this.tabPage1.ResumeLayout(false);
      this.tabPage1.PerformLayout();
      this.groupBox20.ResumeLayout(false);
      this.groupBox20.PerformLayout();
      this.slideLeftRight.EndInit();
      this.slideUpDown.EndInit();
      this.slideZoom.EndInit();
      this.groupBox15.ResumeLayout(false);
      this.groupBox15.PerformLayout();
      this.groupBox14.ResumeLayout(false);
      this.groupBox14.PerformLayout();
      this.groupBox17.ResumeLayout(false);
      this.groupBox17.PerformLayout();
      this.groupBox13.ResumeLayout(false);
      this.groupBox13.PerformLayout();
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      ((ISupportInitialize) this.pictureBox1).EndInit();
      ((ISupportInitialize) this.pictureBox23).EndInit();
      this.tabPage2.ResumeLayout(false);
      this.groupBox6.ResumeLayout(false);
      this.groupBox6.PerformLayout();
      this.groupBox16.ResumeLayout(false);
      this.groupBox16.PerformLayout();
      this.groupBox12.ResumeLayout(false);
      this.groupBox12.PerformLayout();
      this.groupBox2.ResumeLayout(false);
      this.groupBox2.PerformLayout();
      this.groupBox10.ResumeLayout(false);
      this.groupBox10.PerformLayout();
      this.groupBox9.ResumeLayout(false);
      this.groupBox9.PerformLayout();
      this.groupBox8.ResumeLayout(false);
      this.groupBox8.PerformLayout();
      this.groupBox7.ResumeLayout(false);
      this.groupBox7.PerformLayout();
      this.tabPage4.ResumeLayout(false);
      this.tabPage4.PerformLayout();
      this.groupBox18.ResumeLayout(false);
      ((ISupportInitialize) this.dataGridView1).EndInit();
      this.groupBox4.ResumeLayout(false);
      this.groupBox4.PerformLayout();
      this.groupBox11.ResumeLayout(false);
      this.groupBox11.PerformLayout();
      this.tabPage7.ResumeLayout(false);
      this.tabPage7.PerformLayout();
      this.groupBox19.ResumeLayout(false);
      ((ISupportInitialize) this.dataGridView2).EndInit();
      this.tabPage6.ResumeLayout(false);
      this.tabPage6.PerformLayout();
      this.tabPage3.ResumeLayout(false);
      this.tabPage3.PerformLayout();
      this.groupBox22.ResumeLayout(false);
      this.groupBox22.PerformLayout();
      ((ISupportInitialize) this.pictureBox16).EndInit();
      ((ISupportInitialize) this.pictureBox15).EndInit();
      ((ISupportInitialize) this.pictureBox14).EndInit();
      ((ISupportInitialize) this.pictureBox13).EndInit();
      ((ISupportInitialize) this.pictureBox12).EndInit();
      ((ISupportInitialize) this.pictureBox11).EndInit();
      ((ISupportInitialize) this.pictureBox10).EndInit();
      ((ISupportInitialize) this.pictureBox9).EndInit();
      ((ISupportInitialize) this.pictureBox8).EndInit();
      ((ISupportInitialize) this.pictureBox6).EndInit();
      ((ISupportInitialize) this.pictureBox5).EndInit();
      ((ISupportInitialize) this.pictureBox4).EndInit();
      ((ISupportInitialize) this.pictureBox3).EndInit();
      ((ISupportInitialize) this.pictureBox2).EndInit();
      this.groupBox21.ResumeLayout(false);
      this.groupBox21.PerformLayout();
      ((ISupportInitialize) this.pictureBox7).EndInit();
      ((ISupportInitialize) this.dgRaidItems).EndInit();
      this.tabPage5.ResumeLayout(false);
      this.groupBox23.ResumeLayout(false);
      this.groupBox23.PerformLayout();
      this.groupBox33.ResumeLayout(false);
      this.groupBox33.PerformLayout();
      ((ISupportInitialize) this.pictureBox27).EndInit();
      this.groupBox35.ResumeLayout(false);
      this.groupBox35.PerformLayout();
      ((ISupportInitialize) this.pictureBox29).EndInit();
      this.groupBox36.ResumeLayout(false);
      this.groupBox36.PerformLayout();
      ((ISupportInitialize) this.pictureBox30).EndInit();
      this.groupBox37.ResumeLayout(false);
      this.groupBox37.PerformLayout();
      ((ISupportInitialize) this.pictureBox31).EndInit();
      ((ISupportInitialize) this.dgDropAllItems).EndInit();
      this.groupBox38.ResumeLayout(false);
      this.groupBox38.PerformLayout();
      ((ISupportInitialize) this.pictureBox32).EndInit();
      this.groupBox39.ResumeLayout(false);
      this.groupBox39.PerformLayout();
      ((ISupportInitialize) this.pictureBox33).EndInit();
      this.groupBox40.ResumeLayout(false);
      this.groupBox40.PerformLayout();
      ((ISupportInitialize) this.pictureBox34).EndInit();
      this.groupBox41.ResumeLayout(false);
      this.groupBox41.PerformLayout();
      ((ISupportInitialize) this.pictureBox35).EndInit();
      this.groupBox32.ResumeLayout(false);
      this.groupBox32.PerformLayout();
      ((ISupportInitialize) this.pictureBox26).EndInit();
      this.groupBox30.ResumeLayout(false);
      this.groupBox30.PerformLayout();
      ((ISupportInitialize) this.pictureBox24).EndInit();
      this.groupBox29.ResumeLayout(false);
      this.groupBox29.PerformLayout();
      ((ISupportInitialize) this.pictureBox22).EndInit();
      this.groupBox31.ResumeLayout(false);
      this.groupBox31.PerformLayout();
      ((ISupportInitialize) this.pictureBox25).EndInit();
      this.groupBox28.ResumeLayout(false);
      this.groupBox28.PerformLayout();
      ((ISupportInitialize) this.pictureBox21).EndInit();
      this.groupBox27.ResumeLayout(false);
      this.groupBox27.PerformLayout();
      ((ISupportInitialize) this.pictureBox20).EndInit();
      this.groupBox26.ResumeLayout(false);
      this.groupBox26.PerformLayout();
      ((ISupportInitialize) this.pictureBox19).EndInit();
      this.groupBox25.ResumeLayout(false);
      this.groupBox25.PerformLayout();
      ((ISupportInitialize) this.pictureBox18).EndInit();
      this.groupBox24.ResumeLayout(false);
      this.groupBox24.PerformLayout();
      ((ISupportInitialize) this.pictureBox17).EndInit();
      this.tabPage9.ResumeLayout(false);
      this.tabPage9.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();
    }

    private void BtnReadSmc_Click(object sender, EventArgs e)
    {
      string str = Path.GetDirectoryName(this._ClientPath).Replace("Data", "").Replace("data", "") + "\\" + this.textBox89.Text;
      if (File.Exists(str))
        new TextEditor(str).Show();
      else
        new CustomMessage("File not found").Show();
    }

    private void massEditToolStripMenuItem_Click(object sender, EventArgs e)
    {
      int num = (int) new MobMassEdit().ShowDialog();
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

    private void btnSaveAndNext_Click(object sender, EventArgs e)
    {
      if (this.language == "THA")
      {
        this.namee = this.StringFromLanguage();
        this.descrr = this.DescrFromLanguage();
        this.textBox3.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        string str1 = this.textBox3.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        this.textBox4.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        string str2 = this.textBox4.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_npc SET a_index = '" + this.textBox1.Text + "', a_enable = '" + this.textBox2.Text + "', " + this.namee + "='" + str1 + "', " + this.descrr + "='" + str2 + "', a_level = '" + this.textBox5.Text + "', a_family = '" + this.textBox6.Text + "', a_skillmaster = '" + this.textBox7.Text + "', a_flag = '" + this.textBox8.Text + "', a_flag1 = '" + this.textBox9.Text + "', a_state_flag = '" + this.textBox10.Text + "', a_exp = '" + this.textBox11.Text + "', a_prize = '" + this.textBox12.Text + "', a_sight = '" + this.textBox13.Text + "', a_size = '" + this.textBox14.Text + "', a_move_area = '" + this.textBox15.Text + "', a_attack_area = '" + this.textBox16.Text + "', a_skill_point = '" + this.textBox17.Text + "', a_sskill_master = '" + this.textBox18.Text + "', a_str = '" + this.textBox19.Text + "', a_dex = '" + this.textBox20.Text + "', a_int = '" + this.textBox21.Text + "', a_con = '" + this.textBox22.Text + "', a_attack = '" + this.textBox23.Text + "', a_magic = '" + this.textBox24.Text + "', a_defense = '" + this.textBox25.Text + "', a_resist = '" + this.textBox26.Text + "', a_attacklevel = '" + this.textBox27.Text + "', a_defenselevel = '" + this.textBox28.Text + "', a_hp = '" + this.textBox29.Text + "', a_mp = '" + this.textBox30.Text + "', a_attackType = '" + this.textBox31.Text + "', a_attackSpeed = '" + this.textBox32.Text + "', a_recover_hp = '" + this.textBox33.Text + "', a_recover_mp = '" + this.textBox34.Text + "', a_walk_speed = '" + this.textBox35.Text + "', a_run_speed = '" + this.textBox36.Text + "', a_skill0 = '" + this.textBox37.Text + "', a_skill1 = '" + this.textBox38.Text + "', a_skill2 = '" + this.textBox39.Text + "', a_skill3 = '" + this.textBox40.Text + "', a_item_0 = '" + this.textBox41.Text + "', a_item_1 = '" + this.textBox42.Text + "', a_item_2 = '" + this.textBox43.Text + "', a_item_3 = '" + this.textBox44.Text + "', a_item_4 = '" + this.textBox45.Text + "', a_item_5 = '" + this.textBox46.Text + "', a_item_6 = '" + this.textBox47.Text + "', a_item_7 = '" + this.textBox48.Text + "', a_item_8 = '" + this.textBox49.Text + "', a_item_9 = '" + this.textBox50.Text + "', a_item_10 = '" + this.textBox51.Text + "', a_item_11 = '" + this.textBox52.Text + "', a_item_12 = '" + this.textBox53.Text + "', a_item_13 = '" + this.textBox54.Text + "', a_item_14 = '" + this.textBox55.Text + "', a_item_15 = '" + this.textBox56.Text + "', a_item_16 = '" + this.textBox57.Text + "', a_item_17 = '" + this.textBox58.Text + "', a_item_18 = '" + this.textBox59.Text + "', a_item_19 = '" + this.textBox60.Text + "', a_item_percent_0 = '" + this.textBox61.Text + "', a_item_percent_1 = '" + this.textBox62.Text + "', a_item_percent_2 = '" + this.textBox63.Text + "', a_item_percent_3 = '" + this.textBox64.Text + "', a_item_percent_4 = '" + this.textBox65.Text + "', a_item_percent_5 = '" + this.textBox66.Text + "', a_item_percent_6 = '" + this.textBox67.Text + "', a_item_percent_7 = '" + this.textBox68.Text + "', a_item_percent_8 = '" + this.textBox69.Text + "', a_item_percent_9 = '" + this.textBox70.Text + "', a_item_percent_10 = '" + this.textBox71.Text + "', a_item_percent_11 = '" + this.textBox72.Text + "', a_item_percent_12 = '" + this.textBox73.Text + "', a_item_percent_13 = '" + this.textBox74.Text + "', a_item_percent_14 = '" + this.textBox75.Text + "', a_item_percent_15 = '" + this.textBox76.Text + "', a_item_percent_16 = '" + this.textBox77.Text + "', a_item_percent_17 = '" + this.textBox78.Text + "', a_item_percent_18 = '" + this.textBox79.Text + "', a_item_percent_19 = '" + this.textBox80.Text + "', a_minplus = '" + this.textBox81.Text + "', a_maxplus = '" + this.textBox82.Text + "', a_probplus = '" + this.textBox83.Text + "', a_product0 = '" + this.textBox84.Text + "', a_product1 = '" + this.textBox85.Text + "', a_product2 = '" + this.textBox86.Text + "', a_product3 = '" + this.textBox87.Text + "', a_product4 = '" + this.textBox88.Text + "', a_file_smc = '" + this.textBox89.Text.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'") + "', a_motion_walk = '" + this.textBox90.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_idle = '" + this.textBox91.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_dam = '" + this.textBox92.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_attack = '" + this.textBox93.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_die = '" + this.textBox94.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_run = '" + this.textBox95.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_idle2 = '" + this.textBox96.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_attack2 = '" + this.textBox97.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_scale = '" + this.textBox98.Text + "', a_attribute = '" + this.textBox99.Text + "', a_fireDelayCount = '" + this.textBox100.Text + "', a_fireDelay0 = '" + this.textBox101.Text + "', a_fireDelay1 = '" + this.textBox102.Text + "', a_fireDelay2 = '" + this.textBox103.Text + "', a_fireDelay3 = '" + this.textBox104.Text + "', a_fireEffect0 = '" + this.textBox105.Text + "', a_fireEffect1 = '" + this.textBox106.Text + "', a_fireEffect2 = '" + this.textBox107.Text + "', a_fireObject = '" + this.textBox108.Text + "', a_fireSpeed = '" + this.textBox109.Text + "', a_aitype = '" + this.textBox110.Text + "', a_aiflag = '" + this.textBox111.Text + "', a_aileader_flag = '" + this.textBox112.Text + "', a_ai_summonHp = '" + this.textBox113.Text + "', a_aileader_idx = '" + this.textBox114.Text + "', a_aileader_count = '" + this.textBox115.Text + "', a_crafting_category = '" + this.textBox116.Text + "', a_productIndex = '" + this.textBox117.Text + "', a_hit = '" + this.textBox118.Text + "', a_dodge = '" + this.textBox119.Text + "', a_magicavoid = '" + this.textBox120.Text + "', a_job_attribute = '" + this.textBox121.Text + "', a_npc_choice_trigger_count = '" + this.textBox122.Text + "', a_npc_choice_trigger_ids = '" + this.textBox123.Text + "', a_npc_kill_trigger_count = '" + this.textBox124.Text + "', a_npc_kill_trigger_ids = '" + this.textBox125.Text + "', a_createprob = '" + this.textBox126.Text + "', a_socketprob_0 = '" + this.textBox127.Text + "', a_socketprob_1 = '" + this.textBox128.Text + "', a_socketprob_2 = '" + this.textBox129.Text + "', a_socketprob_3 = '" + this.textBox130.Text + "', a_jewel_0 = '" + this.textBox131.Text + "', a_jewel_1 = '" + this.textBox132.Text + "', a_jewel_2 = '" + this.textBox133.Text + "', a_jewel_3 = '" + this.textBox134.Text + "', a_jewel_4 = '" + this.textBox135.Text + "', a_jewel_5 = '" + this.textBox136.Text + "', a_jewel_6 = '" + this.textBox137.Text + "', a_jewel_7 = '" + this.textBox138.Text + "', a_jewel_8 = '" + this.textBox139.Text + "', a_jewel_9 = '" + this.textBox140.Text + "', a_jewel_10 = '" + this.textBox141.Text + "', a_jewel_11 = '" + this.textBox142.Text + "', a_jewel_12 = '" + this.textBox143.Text + "', a_jewel_13 = '" + this.textBox144.Text + "', a_jewel_14 = '" + this.textBox145.Text + "', a_jewel_15 = '" + this.textBox146.Text + "', a_jewel_16 = '" + this.textBox147.Text + "', a_jewel_17 = '" + this.textBox148.Text + "', a_jewel_18 = '" + this.textBox149.Text + "', a_jewel_19 = '" + this.textBox150.Text + "', a_jewel_percent_0 = '" + this.textBox151.Text + "', a_jewel_percent_1 = '" + this.textBox152.Text + "', a_jewel_percent_2 = '" + this.textBox153.Text + "', a_jewel_percent_3 = '" + this.textBox154.Text + "', a_jewel_percent_4 = '" + this.textBox155.Text + "', a_jewel_percent_5 = '" + this.textBox156.Text + "', a_jewel_percent_6 = '" + this.textBox157.Text + "', a_jewel_percent_7 = '" + this.textBox158.Text + "', a_jewel_percent_8 = '" + this.textBox159.Text + "', a_jewel_percent_9 = '" + this.textBox160.Text + "', a_jewel_percent_10 = '" + this.textBox161.Text + "', a_jewel_percent_11 = '" + this.textBox162.Text + "', a_jewel_percent_12 = '" + this.textBox163.Text + "', a_jewel_percent_13 = '" + this.textBox164.Text + "', a_jewel_percent_14 = '" + this.textBox165.Text + "', a_jewel_percent_15 = '" + this.textBox166.Text + "', a_jewel_percent_16 = '" + this.textBox167.Text + "', a_jewel_percent_17 = '" + this.textBox168.Text + "', a_jewel_percent_18 = '" + this.textBox169.Text + "', a_jewel_percent_19 = '" + this.textBox170.Text + "' WHERE a_index = '" + this.textBox1.Text + "'");
      }
      else if (this.language == "USA")
      {
        this.textBox3.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        string str3 = this.textBox3.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        this.textBox4.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        string str4 = this.textBox4.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_npc SET a_index = '" + this.textBox1.Text + "', a_enable = '" + this.textBox2.Text + "', a_name ='" + str3 + "',a_descr = '" + str4 + "', a_name_ger ='" + str3 + "',a_descr_ger = '" + str4 + "', a_name_spn ='" + str3 + "',a_descr_spn = '" + str4 + "', " + this.namee + "='" + str3 + "', " + this.descrr + "='" + str4 + "', a_level = '" + this.textBox5.Text + "', a_family = '" + this.textBox6.Text + "', a_skillmaster = '" + this.textBox7.Text + "', a_flag = '" + this.textBox8.Text + "', a_flag1 = '" + this.textBox9.Text + "', a_state_flag = '" + this.textBox10.Text + "', a_exp = '" + this.textBox11.Text + "', a_prize = '" + this.textBox12.Text + "', a_sight = '" + this.textBox13.Text + "', a_size = '" + this.textBox14.Text + "', a_move_area = '" + this.textBox15.Text + "', a_attack_area = '" + this.textBox16.Text + "', a_skill_point = '" + this.textBox17.Text + "', a_sskill_master = '" + this.textBox18.Text + "', a_str = '" + this.textBox19.Text + "', a_dex = '" + this.textBox20.Text + "', a_int = '" + this.textBox21.Text + "', a_con = '" + this.textBox22.Text + "', a_attack = '" + this.textBox23.Text + "', a_magic = '" + this.textBox24.Text + "', a_defense = '" + this.textBox25.Text + "', a_resist = '" + this.textBox26.Text + "', a_attacklevel = '" + this.textBox27.Text + "', a_defenselevel = '" + this.textBox28.Text + "', a_hp = '" + this.textBox29.Text + "', a_mp = '" + this.textBox30.Text + "', a_attackType = '" + this.textBox31.Text + "', a_attackSpeed = '" + this.textBox32.Text + "', a_recover_hp = '" + this.textBox33.Text + "', a_recover_mp = '" + this.textBox34.Text + "', a_walk_speed = '" + this.textBox35.Text + "', a_run_speed = '" + this.textBox36.Text + "', a_skill0 = '" + this.textBox37.Text + "', a_skill1 = '" + this.textBox38.Text + "', a_skill2 = '" + this.textBox39.Text + "', a_skill3 = '" + this.textBox40.Text + "', a_item_0 = '" + this.textBox41.Text + "', a_item_1 = '" + this.textBox42.Text + "', a_item_2 = '" + this.textBox43.Text + "', a_item_3 = '" + this.textBox44.Text + "', a_item_4 = '" + this.textBox45.Text + "', a_item_5 = '" + this.textBox46.Text + "', a_item_6 = '" + this.textBox47.Text + "', a_item_7 = '" + this.textBox48.Text + "', a_item_8 = '" + this.textBox49.Text + "', a_item_9 = '" + this.textBox50.Text + "', a_item_10 = '" + this.textBox51.Text + "', a_item_11 = '" + this.textBox52.Text + "', a_item_12 = '" + this.textBox53.Text + "', a_item_13 = '" + this.textBox54.Text + "', a_item_14 = '" + this.textBox55.Text + "', a_item_15 = '" + this.textBox56.Text + "', a_item_16 = '" + this.textBox57.Text + "', a_item_17 = '" + this.textBox58.Text + "', a_item_18 = '" + this.textBox59.Text + "', a_item_19 = '" + this.textBox60.Text + "', a_item_percent_0 = '" + this.textBox61.Text + "', a_item_percent_1 = '" + this.textBox62.Text + "', a_item_percent_2 = '" + this.textBox63.Text + "', a_item_percent_3 = '" + this.textBox64.Text + "', a_item_percent_4 = '" + this.textBox65.Text + "', a_item_percent_5 = '" + this.textBox66.Text + "', a_item_percent_6 = '" + this.textBox67.Text + "', a_item_percent_7 = '" + this.textBox68.Text + "', a_item_percent_8 = '" + this.textBox69.Text + "', a_item_percent_9 = '" + this.textBox70.Text + "', a_item_percent_10 = '" + this.textBox71.Text + "', a_item_percent_11 = '" + this.textBox72.Text + "', a_item_percent_12 = '" + this.textBox73.Text + "', a_item_percent_13 = '" + this.textBox74.Text + "', a_item_percent_14 = '" + this.textBox75.Text + "', a_item_percent_15 = '" + this.textBox76.Text + "', a_item_percent_16 = '" + this.textBox77.Text + "', a_item_percent_17 = '" + this.textBox78.Text + "', a_item_percent_18 = '" + this.textBox79.Text + "', a_item_percent_19 = '" + this.textBox80.Text + "', a_minplus = '" + this.textBox81.Text + "', a_maxplus = '" + this.textBox82.Text + "', a_probplus = '" + this.textBox83.Text + "', a_product0 = '" + this.textBox84.Text + "', a_product1 = '" + this.textBox85.Text + "', a_product2 = '" + this.textBox86.Text + "', a_product3 = '" + this.textBox87.Text + "', a_product4 = '" + this.textBox88.Text + "', a_file_smc = '" + this.textBox89.Text.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'") + "', a_motion_walk = '" + this.textBox90.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_idle = '" + this.textBox91.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_dam = '" + this.textBox92.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_attack = '" + this.textBox93.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_die = '" + this.textBox94.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_run = '" + this.textBox95.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_idle2 = '" + this.textBox96.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_attack2 = '" + this.textBox97.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_scale = '" + this.textBox98.Text + "', a_attribute = '" + this.textBox99.Text + "', a_fireDelayCount = '" + this.textBox100.Text + "', a_fireDelay0 = '" + this.textBox101.Text + "', a_fireDelay1 = '" + this.textBox102.Text + "', a_fireDelay2 = '" + this.textBox103.Text + "', a_fireDelay3 = '" + this.textBox104.Text + "', a_fireEffect0 = '" + this.textBox105.Text + "', a_fireEffect1 = '" + this.textBox106.Text + "', a_fireEffect2 = '" + this.textBox107.Text + "', a_fireObject = '" + this.textBox108.Text + "', a_fireSpeed = '" + this.textBox109.Text + "', a_aitype = '" + this.textBox110.Text + "', a_aiflag = '" + this.textBox111.Text + "', a_aileader_flag = '" + this.textBox112.Text + "', a_ai_summonHp = '" + this.textBox113.Text + "', a_aileader_idx = '" + this.textBox114.Text + "', a_aileader_count = '" + this.textBox115.Text + "', a_crafting_category = '" + this.textBox116.Text + "', a_productIndex = '" + this.textBox117.Text + "', a_hit = '" + this.textBox118.Text + "', a_dodge = '" + this.textBox119.Text + "', a_magicavoid = '" + this.textBox120.Text + "', a_job_attribute = '" + this.textBox121.Text + "', a_npc_choice_trigger_count = '" + this.textBox122.Text + "', a_npc_choice_trigger_ids = '" + this.textBox123.Text + "', a_npc_kill_trigger_count = '" + this.textBox124.Text + "', a_npc_kill_trigger_ids = '" + this.textBox125.Text + "', a_createprob = '" + this.textBox126.Text + "', a_socketprob_0 = '" + this.textBox127.Text + "', a_socketprob_1 = '" + this.textBox128.Text + "', a_socketprob_2 = '" + this.textBox129.Text + "', a_socketprob_3 = '" + this.textBox130.Text + "', a_jewel_0 = '" + this.textBox131.Text + "', a_jewel_1 = '" + this.textBox132.Text + "', a_jewel_2 = '" + this.textBox133.Text + "', a_jewel_3 = '" + this.textBox134.Text + "', a_jewel_4 = '" + this.textBox135.Text + "', a_jewel_5 = '" + this.textBox136.Text + "', a_jewel_6 = '" + this.textBox137.Text + "', a_jewel_7 = '" + this.textBox138.Text + "', a_jewel_8 = '" + this.textBox139.Text + "', a_jewel_9 = '" + this.textBox140.Text + "', a_jewel_10 = '" + this.textBox141.Text + "', a_jewel_11 = '" + this.textBox142.Text + "', a_jewel_12 = '" + this.textBox143.Text + "', a_jewel_13 = '" + this.textBox144.Text + "', a_jewel_14 = '" + this.textBox145.Text + "', a_jewel_15 = '" + this.textBox146.Text + "', a_jewel_16 = '" + this.textBox147.Text + "', a_jewel_17 = '" + this.textBox148.Text + "', a_jewel_18 = '" + this.textBox149.Text + "', a_jewel_19 = '" + this.textBox150.Text + "', a_jewel_percent_0 = '" + this.textBox151.Text + "', a_jewel_percent_1 = '" + this.textBox152.Text + "', a_jewel_percent_2 = '" + this.textBox153.Text + "', a_jewel_percent_3 = '" + this.textBox154.Text + "', a_jewel_percent_4 = '" + this.textBox155.Text + "', a_jewel_percent_5 = '" + this.textBox156.Text + "', a_jewel_percent_6 = '" + this.textBox157.Text + "', a_jewel_percent_7 = '" + this.textBox158.Text + "', a_jewel_percent_8 = '" + this.textBox159.Text + "', a_jewel_percent_9 = '" + this.textBox160.Text + "', a_jewel_percent_10 = '" + this.textBox161.Text + "', a_jewel_percent_11 = '" + this.textBox162.Text + "', a_jewel_percent_12 = '" + this.textBox163.Text + "', a_jewel_percent_13 = '" + this.textBox164.Text + "', a_jewel_percent_14 = '" + this.textBox165.Text + "', a_jewel_percent_15 = '" + this.textBox166.Text + "', a_jewel_percent_16 = '" + this.textBox167.Text + "', a_jewel_percent_17 = '" + this.textBox168.Text + "', a_jewel_percent_18 = '" + this.textBox169.Text + "', a_jewel_percent_19 = '" + this.textBox170.Text + "' WHERE a_index = '" + this.textBox1.Text + "'");
      }
      else
      {
        string str5 = this.textBox3.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        this.textBox3.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        string str6 = this.textBox4.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        this.textBox4.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_npc SET a_index = '" + this.textBox1.Text + "', a_enable = '" + this.textBox2.Text + "', " + this.namee + "='" + str5 + "', " + this.descrr + "='" + str6 + "', a_level = '" + this.textBox5.Text + "', a_family = '" + this.textBox6.Text + "', a_skillmaster = '" + this.textBox7.Text + "', a_flag = '" + this.textBox8.Text + "', a_flag1 = '" + this.textBox9.Text + "', a_state_flag = '" + this.textBox10.Text + "', a_exp = '" + this.textBox11.Text + "', a_prize = '" + this.textBox12.Text + "', a_sight = '" + this.textBox13.Text + "', a_size = '" + this.textBox14.Text + "', a_move_area = '" + this.textBox15.Text + "', a_attack_area = '" + this.textBox16.Text + "', a_skill_point = '" + this.textBox17.Text + "', a_sskill_master = '" + this.textBox18.Text + "', a_str = '" + this.textBox19.Text + "', a_dex = '" + this.textBox20.Text + "', a_int = '" + this.textBox21.Text + "', a_con = '" + this.textBox22.Text + "', a_attack = '" + this.textBox23.Text + "', a_magic = '" + this.textBox24.Text + "', a_defense = '" + this.textBox25.Text + "', a_resist = '" + this.textBox26.Text + "', a_attacklevel = '" + this.textBox27.Text + "', a_defenselevel = '" + this.textBox28.Text + "', a_hp = '" + this.textBox29.Text + "', a_mp = '" + this.textBox30.Text + "', a_attackType = '" + this.textBox31.Text + "', a_attackSpeed = '" + this.textBox32.Text + "', a_recover_hp = '" + this.textBox33.Text + "', a_recover_mp = '" + this.textBox34.Text + "', a_walk_speed = '" + this.textBox35.Text + "', a_run_speed = '" + this.textBox36.Text + "', a_skill0 = '" + this.textBox37.Text + "', a_skill1 = '" + this.textBox38.Text + "', a_skill2 = '" + this.textBox39.Text + "', a_skill3 = '" + this.textBox40.Text + "', a_item_0 = '" + this.textBox41.Text + "', a_item_1 = '" + this.textBox42.Text + "', a_item_2 = '" + this.textBox43.Text + "', a_item_3 = '" + this.textBox44.Text + "', a_item_4 = '" + this.textBox45.Text + "', a_item_5 = '" + this.textBox46.Text + "', a_item_6 = '" + this.textBox47.Text + "', a_item_7 = '" + this.textBox48.Text + "', a_item_8 = '" + this.textBox49.Text + "', a_item_9 = '" + this.textBox50.Text + "', a_item_10 = '" + this.textBox51.Text + "', a_item_11 = '" + this.textBox52.Text + "', a_item_12 = '" + this.textBox53.Text + "', a_item_13 = '" + this.textBox54.Text + "', a_item_14 = '" + this.textBox55.Text + "', a_item_15 = '" + this.textBox56.Text + "', a_item_16 = '" + this.textBox57.Text + "', a_item_17 = '" + this.textBox58.Text + "', a_item_18 = '" + this.textBox59.Text + "', a_item_19 = '" + this.textBox60.Text + "', a_item_percent_0 = '" + this.textBox61.Text + "', a_item_percent_1 = '" + this.textBox62.Text + "', a_item_percent_2 = '" + this.textBox63.Text + "', a_item_percent_3 = '" + this.textBox64.Text + "', a_item_percent_4 = '" + this.textBox65.Text + "', a_item_percent_5 = '" + this.textBox66.Text + "', a_item_percent_6 = '" + this.textBox67.Text + "', a_item_percent_7 = '" + this.textBox68.Text + "', a_item_percent_8 = '" + this.textBox69.Text + "', a_item_percent_9 = '" + this.textBox70.Text + "', a_item_percent_10 = '" + this.textBox71.Text + "', a_item_percent_11 = '" + this.textBox72.Text + "', a_item_percent_12 = '" + this.textBox73.Text + "', a_item_percent_13 = '" + this.textBox74.Text + "', a_item_percent_14 = '" + this.textBox75.Text + "', a_item_percent_15 = '" + this.textBox76.Text + "', a_item_percent_16 = '" + this.textBox77.Text + "', a_item_percent_17 = '" + this.textBox78.Text + "', a_item_percent_18 = '" + this.textBox79.Text + "', a_item_percent_19 = '" + this.textBox80.Text + "', a_minplus = '" + this.textBox81.Text + "', a_maxplus = '" + this.textBox82.Text + "', a_probplus = '" + this.textBox83.Text + "', a_product0 = '" + this.textBox84.Text + "', a_product1 = '" + this.textBox85.Text + "', a_product2 = '" + this.textBox86.Text + "', a_product3 = '" + this.textBox87.Text + "', a_product4 = '" + this.textBox88.Text + "', a_file_smc = '" + this.textBox89.Text.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'") + "', a_motion_walk = '" + this.textBox90.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_idle = '" + this.textBox91.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_dam = '" + this.textBox92.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_attack = '" + this.textBox93.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_die = '" + this.textBox94.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_run = '" + this.textBox95.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_idle2 = '" + this.textBox96.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_motion_attack2 = '" + this.textBox97.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_scale = '" + this.textBox98.Text + "', a_attribute = '" + this.textBox99.Text + "', a_fireDelayCount = '" + this.textBox100.Text + "', a_fireDelay0 = '" + this.textBox101.Text + "', a_fireDelay1 = '" + this.textBox102.Text + "', a_fireDelay2 = '" + this.textBox103.Text + "', a_fireDelay3 = '" + this.textBox104.Text + "', a_fireEffect0 = '" + this.textBox105.Text + "', a_fireEffect1 = '" + this.textBox106.Text + "', a_fireEffect2 = '" + this.textBox107.Text + "', a_fireObject = '" + this.textBox108.Text + "', a_fireSpeed = '" + this.textBox109.Text + "', a_aitype = '" + this.textBox110.Text + "', a_aiflag = '" + this.textBox111.Text + "', a_aileader_flag = '" + this.textBox112.Text + "', a_ai_summonHp = '" + this.textBox113.Text + "', a_aileader_idx = '" + this.textBox114.Text + "', a_aileader_count = '" + this.textBox115.Text + "', a_crafting_category = '" + this.textBox116.Text + "', a_productIndex = '" + this.textBox117.Text + "', a_hit = '" + this.textBox118.Text + "', a_dodge = '" + this.textBox119.Text + "', a_magicavoid = '" + this.textBox120.Text + "', a_job_attribute = '" + this.textBox121.Text + "', a_npc_choice_trigger_count = '" + this.textBox122.Text + "', a_npc_choice_trigger_ids = '" + this.textBox123.Text + "', a_npc_kill_trigger_count = '" + this.textBox124.Text + "', a_npc_kill_trigger_ids = '" + this.textBox125.Text + "', a_createprob = '" + this.textBox126.Text + "', a_socketprob_0 = '" + this.textBox127.Text + "', a_socketprob_1 = '" + this.textBox128.Text + "', a_socketprob_2 = '" + this.textBox129.Text + "', a_socketprob_3 = '" + this.textBox130.Text + "', a_jewel_0 = '" + this.textBox131.Text + "', a_jewel_1 = '" + this.textBox132.Text + "', a_jewel_2 = '" + this.textBox133.Text + "', a_jewel_3 = '" + this.textBox134.Text + "', a_jewel_4 = '" + this.textBox135.Text + "', a_jewel_5 = '" + this.textBox136.Text + "', a_jewel_6 = '" + this.textBox137.Text + "', a_jewel_7 = '" + this.textBox138.Text + "', a_jewel_8 = '" + this.textBox139.Text + "', a_jewel_9 = '" + this.textBox140.Text + "', a_jewel_10 = '" + this.textBox141.Text + "', a_jewel_11 = '" + this.textBox142.Text + "', a_jewel_12 = '" + this.textBox143.Text + "', a_jewel_13 = '" + this.textBox144.Text + "', a_jewel_14 = '" + this.textBox145.Text + "', a_jewel_15 = '" + this.textBox146.Text + "', a_jewel_16 = '" + this.textBox147.Text + "', a_jewel_17 = '" + this.textBox148.Text + "', a_jewel_18 = '" + this.textBox149.Text + "', a_jewel_19 = '" + this.textBox150.Text + "', a_jewel_percent_0 = '" + this.textBox151.Text + "', a_jewel_percent_1 = '" + this.textBox152.Text + "', a_jewel_percent_2 = '" + this.textBox153.Text + "', a_jewel_percent_3 = '" + this.textBox154.Text + "', a_jewel_percent_4 = '" + this.textBox155.Text + "', a_jewel_percent_5 = '" + this.textBox156.Text + "', a_jewel_percent_6 = '" + this.textBox157.Text + "', a_jewel_percent_7 = '" + this.textBox158.Text + "', a_jewel_percent_8 = '" + this.textBox159.Text + "', a_jewel_percent_9 = '" + this.textBox160.Text + "', a_jewel_percent_10 = '" + this.textBox161.Text + "', a_jewel_percent_11 = '" + this.textBox162.Text + "', a_jewel_percent_12 = '" + this.textBox163.Text + "', a_jewel_percent_13 = '" + this.textBox164.Text + "', a_jewel_percent_14 = '" + this.textBox165.Text + "', a_jewel_percent_15 = '" + this.textBox166.Text + "', a_jewel_percent_16 = '" + this.textBox167.Text + "', a_jewel_percent_17 = '" + this.textBox168.Text + "', a_jewel_percent_18 = '" + this.textBox169.Text + "', a_jewel_percent_19 = '" + this.textBox170.Text + "' WHERE a_index = '" + this.textBox1.Text + "'");
      }
      int selectedIndex = this.listBox1.SelectedIndex;
      int num1 = this.listBox1.SelectedIndex + 1;
      int num2 = (int) new CustomMessage("Done :)").ShowDialog();
      if (this.textBox200.Text != "")
        this.SearchList(this.textBox200.Text);
      else
        this.LoadListBox();
      if (selectedIndex + 1 >= this.listBox1.Items.Count)
        this.listBox1.SelectedIndex = selectedIndex;
      else
        this.listBox1.SelectedIndex = num1;
    }

    private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
    {
    }

    private void BtnClearDrop_Click(object sender, EventArgs e)
    {
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_npc SET a_item_0 = -1, a_item_1 = -1, a_item_2 = -1, a_item_3 = -1, a_item_4 = -1, a_item_5 = -1, a_item_6 = -1, a_item_7 = -1, a_item_8 = -1, a_item_9 = -1, a_item_10 = -1, a_item_11 = -1, a_item_12 = -1, a_item_13 = -1, a_item_14 = -1, a_item_15 = -1, a_item_16 = -1, a_item_17 = -1, a_item_18 = -1, a_item_19 = -1, a_item_percent_0 = 0, a_item_percent_1 = 0, a_item_percent_2 = 0, a_item_percent_3 = 0, a_item_percent_4 = 0, a_item_percent_5 = 0, a_item_percent_6 = 0, a_item_percent_7 = 0, a_item_percent_8 = 0, a_item_percent_9 = 0, a_item_percent_10 = 0, a_item_percent_11 = 0, a_item_percent_12 = 0, a_item_percent_13 = 0, a_item_percent_14 = 0, a_item_percent_15 = 0, a_item_percent_16 = 0, a_item_percent_17 = 0, a_item_percent_18 = 0, a_item_percent_19 = 0 WHERE a_index = '" + this.textBox1.Text + "';");
      int selectedIndex = this.listBox1.SelectedIndex;
      int num = (int) new CustomMessage("Done :)").ShowDialog();
      if (this.textBox200.Text != "")
        this.SearchList(this.textBox200.Text);
      else
        this.LoadListBox();
      this.listBox1.SelectedIndex = selectedIndex;
    }

    private void TextBox8_TextChanged(object sender, EventArgs e)
    {
    }

    private void exportZoneFlaglodToolStripMenuItem_Click(object sender, EventArgs e)
    {
      this.exportLodHandle.ExportZoneFlag_V4();
    }

    private void FillGrid()
    {
      this.dgRaidItems.Rows.Clear();
      string str1 = "SELECT * FROM t_npc_dropraid WHERE a_npc_index = '" + this.textBox1.Text + "'";
      string[] strArray = new string[25]
      {
        "a_index",
        "a_npc_index",
        "a_item_index",
        "a_count",
        "a_prob",
        "a_flag",
        "a_spec_item_index1",
        "a_spec_item_index2",
        "a_spec_item_index3",
        "a_spec_item_index4",
        "a_spec_item_index5",
        "a_spec_item_index6",
        "a_spec_item_index7",
        "a_spec_item_index8",
        "a_spec_item_index9",
        "a_spec_item_index10",
        "a_spec_item_index11",
        "a_spec_item_index12",
        "a_spec_item_index13",
        "a_spec_item_index14",
        "a_spec_min",
        "a_spec_max",
        "a_spec_count",
        "a_spec_prob",
        "a_spec_flag"
      };
      MySqlConnection mySqlConnection = new MySqlConnection("datasource=" + this.Host + ";Port=3306;User ID="  + this.User + ";Password=" + this.Password + ";Database=" + this.Database + ";Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;");
      MySqlCommand command = mySqlConnection.CreateCommand();
      command.CommandText = str1;
      mySqlConnection.Open();
      MySqlDataReader mySqlDataReader = command.ExecuteReader();
      while (mySqlDataReader.Read())
      {
        int ordinal1 = mySqlDataReader.GetOrdinal("a_index");
        int ordinal2 = mySqlDataReader.GetOrdinal("a_npc_index");
        int ordinal3 = mySqlDataReader.GetOrdinal("a_item_index");
        int ordinal4 = mySqlDataReader.GetOrdinal("a_count");
        int ordinal5 = mySqlDataReader.GetOrdinal("a_prob");
        int ordinal6 = mySqlDataReader.GetOrdinal("a_flag");
        int ordinal7 = mySqlDataReader.GetOrdinal("a_spec_item_index1");
        int ordinal8 = mySqlDataReader.GetOrdinal("a_spec_item_index2");
        int ordinal9 = mySqlDataReader.GetOrdinal("a_spec_item_index3");
        int ordinal10 = mySqlDataReader.GetOrdinal("a_spec_item_index4");
        int ordinal11 = mySqlDataReader.GetOrdinal("a_spec_item_index5");
        int ordinal12 = mySqlDataReader.GetOrdinal("a_spec_item_index6");
        int ordinal13 = mySqlDataReader.GetOrdinal("a_spec_item_index7");
        int ordinal14 = mySqlDataReader.GetOrdinal("a_spec_item_index8");
        int ordinal15 = mySqlDataReader.GetOrdinal("a_spec_item_index9");
        int ordinal16 = mySqlDataReader.GetOrdinal("a_spec_item_index10");
        int ordinal17 = mySqlDataReader.GetOrdinal("a_spec_item_index11");
        int ordinal18 = mySqlDataReader.GetOrdinal("a_spec_item_index12");
        int ordinal19 = mySqlDataReader.GetOrdinal("a_spec_item_index13");
        int ordinal20 = mySqlDataReader.GetOrdinal("a_spec_item_index14");
        int ordinal21 = mySqlDataReader.GetOrdinal("a_spec_min");
        int ordinal22 = mySqlDataReader.GetOrdinal("a_spec_max");
        int ordinal23 = mySqlDataReader.GetOrdinal("a_spec_count");
        int ordinal24 = mySqlDataReader.GetOrdinal("a_spec_prob");
        int ordinal25 = mySqlDataReader.GetOrdinal("a_spec_flag");
        string str2 = mySqlDataReader.GetValue(ordinal1).ToString();
        string str3 = mySqlDataReader.GetValue(ordinal2).ToString();
        string str4 = mySqlDataReader.GetValue(ordinal3).ToString();
        string str5 = mySqlDataReader.GetValue(ordinal4).ToString();
        string str6 = mySqlDataReader.GetValue(ordinal5).ToString();
        string str7 = mySqlDataReader.GetValue(ordinal6).ToString();
        string str8 = mySqlDataReader.GetValue(ordinal7).ToString();
        string str9 = mySqlDataReader.GetValue(ordinal8).ToString();
        string str10 = mySqlDataReader.GetValue(ordinal9).ToString();
        string str11 = mySqlDataReader.GetValue(ordinal10).ToString();
        string str12 = mySqlDataReader.GetValue(ordinal11).ToString();
        string str13 = mySqlDataReader.GetValue(ordinal12).ToString();
        string str14 = mySqlDataReader.GetValue(ordinal13).ToString();
        string str15 = mySqlDataReader.GetValue(ordinal14).ToString();
        string str16 = mySqlDataReader.GetValue(ordinal15).ToString();
        string str17 = mySqlDataReader.GetValue(ordinal16).ToString();
        string str18 = mySqlDataReader.GetValue(ordinal17).ToString();
        string str19 = mySqlDataReader.GetValue(ordinal18).ToString();
        string str20 = mySqlDataReader.GetValue(ordinal19).ToString();
        string str21 = mySqlDataReader.GetValue(ordinal20).ToString();
        string str22 = mySqlDataReader.GetValue(ordinal21).ToString();
        string str23 = mySqlDataReader.GetValue(ordinal22).ToString();
        string str24 = mySqlDataReader.GetValue(ordinal23).ToString();
        string str25 = mySqlDataReader.GetValue(ordinal24).ToString();
        string str26 = mySqlDataReader.GetValue(ordinal25).ToString();
        string str27 = this.databaseHandle.ItemNameFast(Convert.ToInt32(str4));
        this.dgRaidItems.Rows.Add((object) this.databaseHandle.IconFast(Convert.ToInt32(str4)), (object) str2, (object) str3, (object) str4, (object) str27, (object) str5, (object) str6, (object) str7, (object) str8, (object) str9, (object) str10, (object) str11, (object) str12, (object) str13, (object) str14, (object) str15, (object) str16, (object) str17, (object) str18, (object) str19, (object) str20, (object) str21, (object) str22, (object) str23, (object) str24, (object) str25, (object) str26);
      }
      mySqlConnection.Close();
    }

    private void dgRaidItems_CellClick(object sender, DataGridViewCellEventArgs e)
    {
      if (e.RowIndex < 0)
        return;
      DataGridViewRow row = this.dgRaidItems.Rows[e.RowIndex];
      this.textBox177.Text = row.Cells["a_index"].Value.ToString();
      this.textBox178.Text = row.Cells["a_npc_index"].Value.ToString();
      this.textBox179.Text = row.Cells["a_item_index"].Value.ToString();
      this.textBox181.Text = row.Cells["a_count"].Value.ToString();
      this.textBox183.Text = row.Cells["a_prob"].Value.ToString();
      this.textBox182.Text = row.Cells["a_flag"].Value.ToString();
      this.textBox185.Text = row.Cells["a_spec_item_index1"].Value.ToString();
      this.textBox187.Text = row.Cells["a_spec_item_index2"].Value.ToString();
      this.textBox189.Text = row.Cells["a_spec_item_index3"].Value.ToString();
      this.textBox191.Text = row.Cells["a_spec_item_index4"].Value.ToString();
      this.textBox193.Text = row.Cells["a_spec_item_index5"].Value.ToString();
      this.textBox195.Text = row.Cells["a_spec_item_index6"].Value.ToString();
      this.textBox197.Text = row.Cells["a_spec_item_index7"].Value.ToString();
      this.textBox199.Text = row.Cells["a_spec_item_index8"].Value.ToString();
      this.textBox202.Text = row.Cells["a_spec_item_index9"].Value.ToString();
      this.textBox204.Text = row.Cells["a_spec_item_index10"].Value.ToString();
      this.textBox206.Text = row.Cells["a_spec_item_index11"].Value.ToString();
      this.textBox208.Text = row.Cells["a_spec_item_index12"].Value.ToString();
      this.textBox210.Text = row.Cells["a_spec_item_index13"].Value.ToString();
      this.textBox212.Text = row.Cells["a_spec_item_index14"].Value.ToString();
      this.textBox213.Text = row.Cells["a_spec_min"].Value.ToString();
      this.textBox214.Text = row.Cells["a_spec_max"].Value.ToString();
      this.textBox215.Text = row.Cells["a_spec_count"].Value.ToString();
      this.textBox216.Text = row.Cells["a_spec_prob"].Value.ToString();
      this.textBox217.Text = row.Cells["a_spec_flag"].Value.ToString();
    }

    private void textBox179_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox7.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox179.Text.Trim()));
      this.textBox180.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox179.Text.Trim()));
    }

    private void textBox185_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox2.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox185.Text.Trim()));
      this.textBox184.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox185.Text.Trim()));
    }

    private void textBox187_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox3.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox187.Text.Trim()));
      this.textBox186.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox187.Text.Trim()));
    }

    private void textBox189_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox4.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox189.Text.Trim()));
      this.textBox188.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox189.Text.Trim()));
    }

    private void textBox191_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox5.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox191.Text.Trim()));
      this.textBox190.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox191.Text.Trim()));
    }

    private void textBox193_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox6.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox193.Text.Trim()));
      this.textBox192.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox193.Text.Trim()));
    }

    private void textBox195_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox8.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox195.Text.Trim()));
      this.textBox194.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox195.Text.Trim()));
    }

    private void textBox197_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox9.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox197.Text.Trim()));
      this.textBox196.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox197.Text.Trim()));
    }

    private void textBox199_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox10.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox199.Text.Trim()));
      this.textBox198.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox199.Text.Trim()));
    }

    private void textBox202_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox11.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox202.Text.Trim()));
      this.textBox201.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox202.Text.Trim()));
    }

    private void textBox204_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox12.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox204.Text.Trim()));
      this.textBox203.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox204.Text.Trim()));
    }

    private void textBox206_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox13.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox206.Text.Trim()));
      this.textBox205.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox206.Text.Trim()));
    }

    private void textBox208_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox14.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox208.Text.Trim()));
      this.textBox207.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox208.Text.Trim()));
    }

    private void textBox210_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox15.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox210.Text.Trim()));
      this.textBox209.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox210.Text.Trim()));
    }

    private void textBox212_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox16.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox212.Text.Trim()));
      this.textBox211.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox212.Text.Trim()));
    }

    private void button5_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox179.Text = itemPicker.ItemIndex.ToString();
    }

    private void button7_Click(object sender, EventArgs e)
    {
      ItemPickerSpecial itemPickerSpecial = new ItemPickerSpecial();
      if (itemPickerSpecial.ShowDialog() != DialogResult.OK)
        return;
      this.textBox185.Text = itemPickerSpecial.ItemIndex.ToString();
    }

    private void button8_Click(object sender, EventArgs e)
    {
      ItemPickerSpecial itemPickerSpecial = new ItemPickerSpecial();
      if (itemPickerSpecial.ShowDialog() != DialogResult.OK)
        return;
      this.textBox187.Text = itemPickerSpecial.ItemIndex.ToString();
    }

    private void button9_Click(object sender, EventArgs e)
    {
      ItemPickerSpecial itemPickerSpecial = new ItemPickerSpecial();
      if (itemPickerSpecial.ShowDialog() != DialogResult.OK)
        return;
      this.textBox189.Text = itemPickerSpecial.ItemIndex.ToString();
    }

    private void button10_Click(object sender, EventArgs e)
    {
      ItemPickerSpecial itemPickerSpecial = new ItemPickerSpecial();
      if (itemPickerSpecial.ShowDialog() != DialogResult.OK)
        return;
      this.textBox191.Text = itemPickerSpecial.ItemIndex.ToString();
    }

    private void button11_Click(object sender, EventArgs e)
    {
      ItemPickerSpecial itemPickerSpecial = new ItemPickerSpecial();
      if (itemPickerSpecial.ShowDialog() != DialogResult.OK)
        return;
      this.textBox193.Text = itemPickerSpecial.ItemIndex.ToString();
    }

    private void button12_Click(object sender, EventArgs e)
    {
      ItemPickerSpecial itemPickerSpecial = new ItemPickerSpecial();
      if (itemPickerSpecial.ShowDialog() != DialogResult.OK)
        return;
      this.textBox195.Text = itemPickerSpecial.ItemIndex.ToString();
    }

    private void button13_Click(object sender, EventArgs e)
    {
      ItemPickerSpecial itemPickerSpecial = new ItemPickerSpecial();
      if (itemPickerSpecial.ShowDialog() != DialogResult.OK)
        return;
      this.textBox197.Text = itemPickerSpecial.ItemIndex.ToString();
    }

    private void button14_Click(object sender, EventArgs e)
    {
      ItemPickerSpecial itemPickerSpecial = new ItemPickerSpecial();
      if (itemPickerSpecial.ShowDialog() != DialogResult.OK)
        return;
      this.textBox199.Text = itemPickerSpecial.ItemIndex.ToString();
    }

    private void button15_Click(object sender, EventArgs e)
    {
      ItemPickerSpecial itemPickerSpecial = new ItemPickerSpecial();
      if (itemPickerSpecial.ShowDialog() != DialogResult.OK)
        return;
      this.textBox202.Text = itemPickerSpecial.ItemIndex.ToString();
    }

    private void button16_Click(object sender, EventArgs e)
    {
      ItemPickerSpecial itemPickerSpecial = new ItemPickerSpecial();
      if (itemPickerSpecial.ShowDialog() != DialogResult.OK)
        return;
      this.textBox204.Text = itemPickerSpecial.ItemIndex.ToString();
    }

    private void button20_Click(object sender, EventArgs e)
    {
      ItemPickerSpecial itemPickerSpecial = new ItemPickerSpecial();
      if (itemPickerSpecial.ShowDialog() != DialogResult.OK)
        return;
      this.textBox206.Text = itemPickerSpecial.ItemIndex.ToString();
    }

    private void button21_Click(object sender, EventArgs e)
    {
      ItemPickerSpecial itemPickerSpecial = new ItemPickerSpecial();
      if (itemPickerSpecial.ShowDialog() != DialogResult.OK)
        return;
      this.textBox208.Text = itemPickerSpecial.ItemIndex.ToString();
    }

    private void button22_Click(object sender, EventArgs e)
    {
      ItemPickerSpecial itemPickerSpecial = new ItemPickerSpecial();
      if (itemPickerSpecial.ShowDialog() != DialogResult.OK)
        return;
      this.textBox210.Text = itemPickerSpecial.ItemIndex.ToString();
    }

    private void button23_Click(object sender, EventArgs e)
    {
      ItemPickerSpecial itemPickerSpecial = new ItemPickerSpecial();
      if (itemPickerSpecial.ShowDialog() != DialogResult.OK)
        return;
      this.textBox212.Text = itemPickerSpecial.ItemIndex.ToString();
    }

    private void button17_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want to Delete Selected Raid Item ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      int selectedIndex = this.listBox1.SelectedIndex;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_npc_dropraid WHERE a_index = '" + this.textBox177.Text + "'");
      this.FillGrid();
      this.listBox1.SelectedIndex = selectedIndex;
    }

    private void button18_Click(object sender, EventArgs e)
    {
      this.IniRead();
      int selectedIndex = this.listBox1.SelectedIndex;
      if (MessageBox.Show("Do you want to Change Raid Item ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      MySqlConnection connection = new MySqlConnection("datasource=" + this.textBox218.Text + ";port=3306;username=" + this.textBox219.Text + ";password=" + this.textBox220.Text);
      MySqlCommand mySqlCommand = new MySqlCommand("UPDATE " + this.textBox221.Text + ".t_npc_dropraid SET a_item_index='" + this.textBox179.Text + "', a_count='" + this.textBox181.Text + "', a_prob='" + this.textBox183.Text + "', a_flag='" + this.textBox182.Text + "', a_spec_item_index1='" + this.textBox185.Text + "', a_spec_item_index2='" + this.textBox187.Text + "', a_spec_item_index3='" + this.textBox189.Text + "', a_spec_item_index4='" + this.textBox191.Text + "', a_spec_item_index5='" + this.textBox193.Text + "', a_spec_item_index6='" + this.textBox195.Text + "', a_spec_item_index7='" + this.textBox197.Text + "', a_spec_item_index8='" + this.textBox199.Text + "', a_spec_item_index9='" + this.textBox202.Text + "', a_spec_item_index10='" + this.textBox204.Text + "', a_spec_item_index11='" + this.textBox206.Text + "', a_spec_item_index12='" + this.textBox208.Text + "', a_spec_item_index13='" + this.textBox210.Text + "', a_spec_item_index14='" + this.textBox212.Text + "', a_spec_min='" + this.textBox213.Text + "', a_spec_max='" + this.textBox214.Text + "', a_spec_count='" + this.textBox215.Text + "', a_spec_prob='" + this.textBox216.Text + "', a_spec_flag='" + this.textBox217.Text + "' WHERE a_index='" + this.textBox177.Text + "'", connection);
      try
      {
        connection.Open();
        MySqlDataReader mySqlDataReader = mySqlCommand.ExecuteReader();
        int num = (int) MessageBox.Show("Your Reward is Saved!");
        while (mySqlDataReader.Read())
          ;
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message);
      }
      this.FillGrid();
      this.listBox1.SelectedIndex = selectedIndex;
    }

    private void button19_Click(object sender, EventArgs e)
    {
      int selectedIndex = this.listBox1.SelectedIndex;
      if (MessageBox.Show("Do you want add New Raid Item ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      if (Convert.ToInt32(this.textBox179.Text) <= 0)
      {
        int num1 = (int) MessageBox.Show("No data to select", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_npc_dropraid (a_npc_index, a_item_index, a_count, a_prob, a_flag, a_spec_item_index1, a_spec_item_index2, a_spec_item_index3, a_spec_item_index4, a_spec_item_index5, a_spec_item_index6, a_spec_item_index7, a_spec_item_index8, a_spec_item_index9, a_spec_item_index10, a_spec_item_index11, a_spec_item_index12, a_spec_item_index13,a_spec_item_index14, a_spec_min, a_spec_max, a_spec_count, a_spec_prob, a_spec_flag) VALUES (" + this.textBox1.Text + ", " + this.textBox179.Text + ", " + this.textBox181.Text + ", " + this.textBox183.Text + ", " + this.textBox182.Text + ", " + this.textBox185.Text + ", " + this.textBox187.Text + ", " + this.textBox189.Text + ", " + this.textBox191.Text + ", " + this.textBox193.Text + ", " + this.textBox195.Text + ", " + this.textBox197.Text + ", " + this.textBox199.Text + ", " + this.textBox202.Text + ", " + this.textBox204.Text + ", " + this.textBox206.Text + ", " + this.textBox208.Text + ", " + this.textBox210.Text + ", " + this.textBox212.Text + ", " + this.textBox213.Text + ", " + this.textBox214.Text + ", " + this.textBox215.Text + ", " + this.textBox216.Text + ", " + this.textBox217.Text + ")");
        int num2 = (int) MessageBox.Show("Successful add new", "Completed", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
        this.FillGrid();
        this.listBox1.SelectedIndex = selectedIndex;
      }
    }

    private void button24_Click(object sender, EventArgs e)
    {
      this.textBox179.Text = "-1";
      this.textBox181.Text = "1";
      this.textBox182.Text = "0";
      this.textBox183.Text = "10";
      this.textBox213.Text = "0";
      this.textBox214.Text = "0";
      this.textBox215.Text = "0";
      this.textBox216.Text = "0";
      this.textBox217.Text = "0";
      this.textBox185.Text = "-1";
      this.textBox187.Text = "-1";
      this.textBox189.Text = "-1";
      this.textBox191.Text = "-1";
      this.textBox193.Text = "-1";
      this.textBox195.Text = "-1";
      this.textBox197.Text = "-1";
      this.textBox199.Text = "-1";
      this.textBox202.Text = "-1";
      this.textBox204.Text = "-1";
      this.textBox206.Text = "-1";
      this.textBox208.Text = "-1";
      this.textBox210.Text = "-1";
      this.textBox212.Text = "-1";
    }

    private void FillGrid2()
    {
      this.dgDropAllItems.Rows.Clear();
      string str1 = "SELECT * FROM t_npc_drop_all WHERE a_npc_idx = '" + this.textBox1.Text + "'";
      string[] strArray = new string[3]
      {
        "a_npc_idx",
        "a_item_idx",
        "a_prob"
      };
      MySqlConnection mySqlConnection = new MySqlConnection("datasource=" + this.Host + ";Port=3306;User ID="  + this.User + ";Password=" + this.Password + ";Database=" + this.Database + ";Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;");
      MySqlCommand command = mySqlConnection.CreateCommand();
      command.CommandText = str1;
      mySqlConnection.Open();
      MySqlDataReader mySqlDataReader = command.ExecuteReader();
      while (mySqlDataReader.Read())
      {
        int ordinal1 = mySqlDataReader.GetOrdinal("a_npc_idx");
        int ordinal2 = mySqlDataReader.GetOrdinal("a_item_idx");
        int ordinal3 = mySqlDataReader.GetOrdinal("a_prob");
        int ordinal4 = mySqlDataReader.GetOrdinal("a_count");
        string str2 = mySqlDataReader.GetString(ordinal1);
        string str3 = mySqlDataReader.GetString(ordinal2);
        string str4 = mySqlDataReader.GetString(ordinal3);
        string str5 = mySqlDataReader.GetString(ordinal4);
        string str6 = this.databaseHandle.ItemNameFast(Convert.ToInt32(str3));
        this.dgDropAllItems.Rows.Add((object) this.databaseHandle.IconFast(Convert.ToInt32(str3)), (object) str2, (object) str3, (object) str6, (object) str4, (object) str5);
      }
      mySqlConnection.Close();
    }

    private void dgDropAllItems_CellClick(object sender, DataGridViewCellEventArgs e)
    {
      if (e.RowIndex < 0)
        return;
      DataGridViewRow row = this.dgDropAllItems.Rows[e.RowIndex];
      if (this.dgDropAllItems.Rows.Count > 0)
        this.textBox226.Text = Convert.ToString(this.dgDropAllItems.Rows[0].Cells["a_item_idx"].Value);
      if (this.dgDropAllItems.Rows.Count > 0)
        this.textBox223.Text = Convert.ToString(this.dgDropAllItems.Rows[0].Cells["Count"].Value);
      if (this.dgDropAllItems.Rows.Count > 0)
        this.textBox222.Text = Convert.ToString(this.dgDropAllItems.Rows[0].Cells["a_prob_raid"].Value);
      if (this.dgDropAllItems.Rows.Count > 1)
        this.textBox227.Text = Convert.ToString(this.dgDropAllItems.Rows[1].Cells["a_item_idx"].Value);
      if (this.dgDropAllItems.Rows.Count > 1)
        this.textBox228.Text = Convert.ToString(this.dgDropAllItems.Rows[1].Cells["Count"].Value);
      if (this.dgDropAllItems.Rows.Count > 1)
        this.textBox229.Text = Convert.ToString(this.dgDropAllItems.Rows[1].Cells["a_prob_raid"].Value);
      if (this.dgDropAllItems.Rows.Count > 2)
        this.textBox230.Text = Convert.ToString(this.dgDropAllItems.Rows[2].Cells["a_item_idx"].Value);
      if (this.dgDropAllItems.Rows.Count > 2)
        this.textBox231.Text = Convert.ToString(this.dgDropAllItems.Rows[2].Cells["Count"].Value);
      if (this.dgDropAllItems.Rows.Count > 2)
        this.textBox232.Text = Convert.ToString(this.dgDropAllItems.Rows[2].Cells["a_prob_raid"].Value);
      if (this.dgDropAllItems.Rows.Count > 3)
        this.textBox233.Text = Convert.ToString(this.dgDropAllItems.Rows[3].Cells["a_item_idx"].Value);
      if (this.dgDropAllItems.Rows.Count > 3)
        this.textBox234.Text = Convert.ToString(this.dgDropAllItems.Rows[3].Cells["Count"].Value);
      if (this.dgDropAllItems.Rows.Count > 3)
        this.textBox235.Text = Convert.ToString(this.dgDropAllItems.Rows[3].Cells["a_prob_raid"].Value);
      if (this.dgDropAllItems.Rows.Count > 4)
        this.textBox236.Text = Convert.ToString(this.dgDropAllItems.Rows[4].Cells["a_item_idx"].Value);
      if (this.dgDropAllItems.Rows.Count > 4)
        this.textBox237.Text = Convert.ToString(this.dgDropAllItems.Rows[4].Cells["Count"].Value);
      if (this.dgDropAllItems.Rows.Count > 4)
        this.textBox238.Text = Convert.ToString(this.dgDropAllItems.Rows[4].Cells["a_prob_raid"].Value);
      if (this.dgDropAllItems.Rows.Count > 5)
        this.textBox239.Text = Convert.ToString(this.dgDropAllItems.Rows[5].Cells["a_item_idx"].Value);
      if (this.dgDropAllItems.Rows.Count > 5)
        this.textBox240.Text = Convert.ToString(this.dgDropAllItems.Rows[5].Cells["Count"].Value);
      if (this.dgDropAllItems.Rows.Count > 5)
        this.textBox241.Text = Convert.ToString(this.dgDropAllItems.Rows[5].Cells["a_prob_raid"].Value);
      if (this.dgDropAllItems.Rows.Count > 6)
        this.textBox242.Text = Convert.ToString(this.dgDropAllItems.Rows[6].Cells["a_item_idx"].Value);
      if (this.dgDropAllItems.Rows.Count > 6)
        this.textBox243.Text = Convert.ToString(this.dgDropAllItems.Rows[6].Cells["Count"].Value);
      if (this.dgDropAllItems.Rows.Count > 6)
        this.textBox244.Text = Convert.ToString(this.dgDropAllItems.Rows[6].Cells["a_prob_raid"].Value);
      if (this.dgDropAllItems.Rows.Count > 7)
        this.textBox245.Text = Convert.ToString(this.dgDropAllItems.Rows[7].Cells["a_item_idx"].Value);
      if (this.dgDropAllItems.Rows.Count > 7)
        this.textBox246.Text = Convert.ToString(this.dgDropAllItems.Rows[7].Cells["Count"].Value);
      if (this.dgDropAllItems.Rows.Count > 7)
        this.textBox247.Text = Convert.ToString(this.dgDropAllItems.Rows[7].Cells["a_prob_raid"].Value);
      if (this.dgDropAllItems.Rows.Count > 8)
        this.textBox248.Text = Convert.ToString(this.dgDropAllItems.Rows[8].Cells["a_item_idx"].Value);
      if (this.dgDropAllItems.Rows.Count > 8)
        this.textBox249.Text = Convert.ToString(this.dgDropAllItems.Rows[8].Cells["Count"].Value);
      if (this.dgDropAllItems.Rows.Count > 8)
        this.textBox250.Text = Convert.ToString(this.dgDropAllItems.Rows[8].Cells["a_prob_raid"].Value);
      if (this.dgDropAllItems.Rows.Count > 9)
        this.textBox275.Text = Convert.ToString(this.dgDropAllItems.Rows[9].Cells["a_item_idx"].Value);
      if (this.dgDropAllItems.Rows.Count > 9)
        this.textBox276.Text = Convert.ToString(this.dgDropAllItems.Rows[9].Cells["Count"].Value);
      if (this.dgDropAllItems.Rows.Count > 9)
        this.textBox277.Text = Convert.ToString(this.dgDropAllItems.Rows[9].Cells["a_prob_raid"].Value);
      if (this.dgDropAllItems.Rows.Count > 10)
        this.textBox272.Text = Convert.ToString(this.dgDropAllItems.Rows[10].Cells["a_item_idx"].Value);
      if (this.dgDropAllItems.Rows.Count > 10)
        this.textBox273.Text = Convert.ToString(this.dgDropAllItems.Rows[10].Cells["Count"].Value);
      if (this.dgDropAllItems.Rows.Count > 10)
        this.textBox274.Text = Convert.ToString(this.dgDropAllItems.Rows[10].Cells["a_prob_raid"].Value);
      if (this.dgDropAllItems.Rows.Count > 11)
        this.textBox269.Text = Convert.ToString(this.dgDropAllItems.Rows[11].Cells["a_item_idx"].Value);
      if (this.dgDropAllItems.Rows.Count > 11)
        this.textBox270.Text = Convert.ToString(this.dgDropAllItems.Rows[11].Cells["Count"].Value);
      if (this.dgDropAllItems.Rows.Count > 11)
        this.textBox271.Text = Convert.ToString(this.dgDropAllItems.Rows[11].Cells["a_prob_raid"].Value);
      if (this.dgDropAllItems.Rows.Count > 12)
        this.textBox266.Text = Convert.ToString(this.dgDropAllItems.Rows[12].Cells["a_item_idx"].Value);
      if (this.dgDropAllItems.Rows.Count > 12)
        this.textBox267.Text = Convert.ToString(this.dgDropAllItems.Rows[12].Cells["Count"].Value);
      if (this.dgDropAllItems.Rows.Count > 12)
        this.textBox268.Text = Convert.ToString(this.dgDropAllItems.Rows[12].Cells["a_prob_raid"].Value);
      if (this.dgDropAllItems.Rows.Count > 13)
        this.textBox263.Text = Convert.ToString(this.dgDropAllItems.Rows[13].Cells["a_item_idx"].Value);
      if (this.dgDropAllItems.Rows.Count > 13)
        this.textBox264.Text = Convert.ToString(this.dgDropAllItems.Rows[13].Cells["Count"].Value);
      if (this.dgDropAllItems.Rows.Count > 13)
        this.textBox265.Text = Convert.ToString(this.dgDropAllItems.Rows[13].Cells["a_prob_raid"].Value);
      if (this.dgDropAllItems.Rows.Count > 14)
        this.textBox260.Text = Convert.ToString(this.dgDropAllItems.Rows[14].Cells["a_item_idx"].Value);
      if (this.dgDropAllItems.Rows.Count > 14)
        this.textBox261.Text = Convert.ToString(this.dgDropAllItems.Rows[14].Cells["Count"].Value);
      if (this.dgDropAllItems.Rows.Count > 14)
        this.textBox262.Text = Convert.ToString(this.dgDropAllItems.Rows[14].Cells["a_prob_raid"].Value);
      if (this.dgDropAllItems.Rows.Count > 15)
        this.textBox257.Text = Convert.ToString(this.dgDropAllItems.Rows[15].Cells["a_item_idx"].Value);
      if (this.dgDropAllItems.Rows.Count > 15)
        this.textBox258.Text = Convert.ToString(this.dgDropAllItems.Rows[15].Cells["Count"].Value);
      if (this.dgDropAllItems.Rows.Count > 15)
        this.textBox259.Text = Convert.ToString(this.dgDropAllItems.Rows[15].Cells["a_prob_raid"].Value);
      if (this.dgDropAllItems.Rows.Count > 16)
        this.textBox225.Text = Convert.ToString(this.dgDropAllItems.Rows[16].Cells["a_item_idx"].Value);
      if (this.dgDropAllItems.Rows.Count > 16)
        this.textBox251.Text = Convert.ToString(this.dgDropAllItems.Rows[16].Cells["Count"].Value);
      if (this.dgDropAllItems.Rows.Count <= 16)
        return;
      this.textBox252.Text = Convert.ToString(this.dgDropAllItems.Rows[16].Cells["a_prob_raid"].Value);
    }

    private void textBox226_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox17.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox226.Text.Trim()));
      this.label146.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox226.Text.Trim()));
    }

    private void button25_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox226.Text = itemPicker.ItemIndex.ToString();
    }

    private void textBox227_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox18.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox227.Text.Trim()));
      this.label147.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox227.Text.Trim()));
    }

    private void button26_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox227.Text = itemPicker.ItemIndex.ToString();
    }

    private void textBox230_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox19.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox230.Text.Trim()));
      this.label152.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox230.Text.Trim()));
    }

    private void button29_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox230.Text = itemPicker.ItemIndex.ToString();
    }

    private void textBox233_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox20.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox233.Text.Trim()));
      this.label157.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox233.Text.Trim()));
    }

    private void button30_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox233.Text = itemPicker.ItemIndex.ToString();
    }

    private void textBox236_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox21.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox236.Text.Trim()));
      this.label162.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox236.Text.Trim()));
    }

    private void button31_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox236.Text = itemPicker.ItemIndex.ToString();
    }

    private void textBox239_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox22.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox239.Text.Trim()));
      this.label167.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox239.Text.Trim()));
    }

    private void button32_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox239.Text = itemPicker.ItemIndex.ToString();
    }

    private void textBox242_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox24.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox242.Text.Trim()));
      this.label172.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox242.Text.Trim()));
    }

    private void button33_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox242.Text = itemPicker.ItemIndex.ToString();
    }

    private void textBox245_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox25.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox245.Text.Trim()));
      this.label177.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox245.Text.Trim()));
    }

    private void button34_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox245.Text = itemPicker.ItemIndex.ToString();
    }

    private void textBox248_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox26.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox248.Text.Trim()));
      this.label182.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox248.Text.Trim()));
    }

    private void button35_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox248.Text = itemPicker.ItemIndex.ToString();
    }

    private void textBox275_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox35.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox275.Text.Trim()));
      this.label227.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox275.Text.Trim()));
    }

    private void button44_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox275.Text = itemPicker.ItemIndex.ToString();
    }

    private void textBox272_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox34.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox272.Text.Trim()));
      this.label222.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox272.Text.Trim()));
    }

    private void button43_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox272.Text = itemPicker.ItemIndex.ToString();
    }

    private void textBox269_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox33.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox269.Text.Trim()));
      this.label217.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox269.Text.Trim()));
    }

    private void button42_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox269.Text = itemPicker.ItemIndex.ToString();
    }

    private void textBox266_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox32.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox266.Text.Trim()));
      this.label212.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox266.Text.Trim()));
    }

    private void button41_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox266.Text = itemPicker.ItemIndex.ToString();
    }

    private void textBox263_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox31.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox263.Text.Trim()));
      this.label207.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox263.Text.Trim()));
    }

    private void button40_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox263.Text = itemPicker.ItemIndex.ToString();
    }

    private void textBox260_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox30.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox260.Text.Trim()));
      this.label202.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox260.Text.Trim()));
    }

    private void button39_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox260.Text = itemPicker.ItemIndex.ToString();
    }

    private void textBox257_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox29.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox257.Text.Trim()));
      this.label197.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox257.Text.Trim()));
    }

    private void button38_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox257.Text = itemPicker.ItemIndex.ToString();
    }

    private void textBox225_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox27.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox225.Text.Trim()));
      this.label187.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox225.Text.Trim()));
    }

    private void button36_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox225.Text = itemPicker.ItemIndex.ToString();
    }

    private void button28_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want to Delete All Item  ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      int selectedIndex = this.listBox1.SelectedIndex;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_npc_drop_all WHERE a_npc_idx = '" + this.textBox1.Text + "'");
      this.FillGrid2();
      this.listBox1.SelectedIndex = selectedIndex;
      this.ResetDropAll();
    }

    private void button27_Click(object sender, EventArgs e)
    {
      int selectedIndex = this.listBox1.SelectedIndex;
      this.DeleteItemAll();
      this.SaveItem1();
      this.SaveItem2();
      this.SaveItem3();
      this.SaveItem4();
      this.SaveItem5();
      this.SaveItem6();
      this.SaveItem7();
      this.SaveItem8();
      this.SaveItem9();
      this.SaveItem10();
      this.SaveItem11();
      this.SaveItem12();
      this.SaveItem13();
      this.SaveItem14();
      this.SaveItem15();
      this.SaveItem16();
      this.SaveItem17();
      this.FillGrid2();
      this.listBox1.SelectedIndex = selectedIndex;
    }

    private void DeleteItemAll()
    {
      if (MessageBox.Show("Do you want to Change  ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_npc_drop_all WHERE a_npc_idx = '" + this.textBox1.Text + "'");
    }

    private void SaveItem1()
    {
      if (Convert.ToInt32(this.textBox226.Text) <= 0)
        return;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_npc_drop_all (a_npc_idx, a_item_idx, a_prob, a_count) VALUES (" + this.textBox1.Text + ", " + this.textBox226.Text + ", " + this.textBox222.Text + ", " + this.textBox223.Text + ")");
      int num = (int) MessageBox.Show("Successful add new", "Completed", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
    }

    private void SaveItem2()
    {
      if (Convert.ToInt32(this.textBox227.Text) <= 0)
        return;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_npc_drop_all (a_npc_idx, a_item_idx, a_prob, a_count) VALUES (" + this.textBox1.Text + ", " + this.textBox227.Text + ", " + this.textBox229.Text + ", " + this.textBox228.Text + ")");
    }

    private void SaveItem3()
    {
      if (Convert.ToInt32(this.textBox230.Text) <= 0)
        return;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_npc_drop_all (a_npc_idx, a_item_idx, a_prob, a_count) VALUES (" + this.textBox1.Text + ", " + this.textBox230.Text + ", " + this.textBox232.Text + ", " + this.textBox231.Text + ")");
    }

    private void SaveItem4()
    {
      if (Convert.ToInt32(this.textBox233.Text) <= 0)
        return;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_npc_drop_all (a_npc_idx, a_item_idx, a_prob, a_count) VALUES (" + this.textBox1.Text + ", " + this.textBox233.Text + ", " + this.textBox235.Text + ", " + this.textBox234.Text + ")");
    }

    private void SaveItem5()
    {
      if (Convert.ToInt32(this.textBox236.Text) <= 0)
        return;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_npc_drop_all (a_npc_idx, a_item_idx, a_prob, a_count) VALUES (" + this.textBox1.Text + ", " + this.textBox236.Text + ", " + this.textBox238.Text + ", " + this.textBox237.Text + ")");
    }

    private void SaveItem6()
    {
      if (Convert.ToInt32(this.textBox239.Text) <= 0)
        return;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_npc_drop_all (a_npc_idx, a_item_idx, a_prob, a_count) VALUES (" + this.textBox1.Text + ", " + this.textBox239.Text + ", " + this.textBox241.Text + ", " + this.textBox240.Text + ")");
    }

    private void SaveItem7()
    {
      if (Convert.ToInt32(this.textBox242.Text) <= 0)
        return;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_npc_drop_all (a_npc_idx, a_item_idx, a_prob, a_count) VALUES (" + this.textBox1.Text + ", " + this.textBox242.Text + ", " + this.textBox244.Text + ", " + this.textBox243.Text + ")");
    }

    private void SaveItem8()
    {
      if (Convert.ToInt32(this.textBox245.Text) <= 0)
        return;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_npc_drop_all (a_npc_idx, a_item_idx, a_prob, a_count) VALUES (" + this.textBox1.Text + ", " + this.textBox245.Text + ", " + this.textBox247.Text + ", " + this.textBox246.Text + ")");
    }

    private void SaveItem9()
    {
      if (Convert.ToInt32(this.textBox248.Text) <= 0)
        return;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_npc_drop_all (a_npc_idx, a_item_idx, a_prob, a_count) VALUES (" + this.textBox1.Text + ", " + this.textBox248.Text + ", " + this.textBox250.Text + ", " + this.textBox249.Text + ")");
    }

    private void SaveItem10()
    {
      if (Convert.ToInt32(this.textBox275.Text) <= 0)
        return;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_npc_drop_all (a_npc_idx, a_item_idx, a_prob, a_count) VALUES (" + this.textBox1.Text + ", " + this.textBox275.Text + ", " + this.textBox277.Text + ", " + this.textBox276.Text + ")");
    }

    private void SaveItem11()
    {
      if (Convert.ToInt32(this.textBox272.Text) <= 0)
        return;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_npc_drop_all (a_npc_idx, a_item_idx, a_prob, a_count) VALUES (" + this.textBox1.Text + ", " + this.textBox272.Text + ", " + this.textBox274.Text + ", " + this.textBox273.Text + ")");
    }

    private void SaveItem12()
    {
      if (Convert.ToInt32(this.textBox269.Text) <= 0)
        return;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_npc_drop_all (a_npc_idx, a_item_idx, a_prob, a_count) VALUES (" + this.textBox1.Text + ", " + this.textBox269.Text + ", " + this.textBox271.Text + ", " + this.textBox270.Text + ")");
    }

    private void SaveItem13()
    {
      if (Convert.ToInt32(this.textBox266.Text) <= 0)
        return;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_npc_drop_all (a_npc_idx, a_item_idx, a_prob, a_count) VALUES (" + this.textBox1.Text + ", " + this.textBox266.Text + ", " + this.textBox268.Text + ", " + this.textBox267.Text + ")");
    }

    private void SaveItem14()
    {
      if (Convert.ToInt32(this.textBox263.Text) <= 0)
        return;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_npc_drop_all (a_npc_idx, a_item_idx, a_prob, a_count) VALUES (" + this.textBox1.Text + ", " + this.textBox263.Text + ", " + this.textBox265.Text + ", " + this.textBox264.Text + ")");
    }

    private void SaveItem15()
    {
      if (Convert.ToInt32(this.textBox260.Text) <= 0)
        return;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_npc_drop_all (a_npc_idx, a_item_idx, a_prob, a_count) VALUES (" + this.textBox1.Text + ", " + this.textBox260.Text + ", " + this.textBox262.Text + ", " + this.textBox261.Text + ")");
    }

    private void SaveItem16()
    {
      if (Convert.ToInt32(this.textBox257.Text) <= 0)
        return;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_npc_drop_all (a_npc_idx, a_item_idx, a_prob, a_count) VALUES (" + this.textBox1.Text + ", " + this.textBox257.Text + ", " + this.textBox259.Text + ", " + this.textBox258.Text + ")");
    }

    private void SaveItem17()
    {
      if (Convert.ToInt32(this.textBox225.Text) <= 0)
        return;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_npc_drop_all (a_npc_idx, a_item_idx, a_prob, a_count) VALUES (" + this.textBox1.Text + ", " + this.textBox225.Text + ", " + this.textBox252.Text + ", " + this.textBox251.Text + ")");
    }

    private void ResetDropAll()
    {
      this.textBox226.Text = "0";
      this.textBox227.Text = "0";
      this.textBox230.Text = "0";
      this.textBox233.Text = "0";
      this.textBox236.Text = "0";
      this.textBox239.Text = "0";
      this.textBox242.Text = "0";
      this.textBox245.Text = "0";
      this.textBox248.Text = "0";
      this.textBox275.Text = "0";
      this.textBox272.Text = "0";
      this.textBox269.Text = "0";
      this.textBox266.Text = "0";
      this.textBox263.Text = "0";
      this.textBox260.Text = "0";
      this.textBox257.Text = "0";
      this.textBox225.Text = "0";
      this.textBox223.Text = "1";
      this.textBox222.Text = "10000";
      this.textBox228.Text = "1";
      this.textBox229.Text = "10000";
      this.textBox231.Text = "1";
      this.textBox232.Text = "10000";
      this.textBox234.Text = "1";
      this.textBox235.Text = "10000";
      this.textBox237.Text = "1";
      this.textBox238.Text = "10000";
      this.textBox240.Text = "1";
      this.textBox241.Text = "10000";
      this.textBox243.Text = "1";
      this.textBox244.Text = "10000";
      this.textBox246.Text = "1";
      this.textBox247.Text = "10000";
      this.textBox249.Text = "1";
      this.textBox250.Text = "10000";
      this.textBox276.Text = "1";
      this.textBox277.Text = "10000";
      this.textBox273.Text = "1";
      this.textBox274.Text = "10000";
      this.textBox270.Text = "1";
      this.textBox271.Text = "10000";
      this.textBox267.Text = "1";
      this.textBox268.Text = "10000";
      this.textBox264.Text = "1";
      this.textBox265.Text = "10000";
      this.textBox261.Text = "1";
      this.textBox262.Text = "10000";
      this.textBox258.Text = "1";
      this.textBox259.Text = "10000";
      this.textBox251.Text = "1";
      this.textBox252.Text = "10000";
    }

    private void ShowzoneFlag(int flag)
    {
      for (int index = 0; index < this.clbZone.Items.Count; ++index)
        this.clbZone.SetItemChecked(index, (flag & 1 << index) > 0);
    }

    private void tbZoneFlag_TextChanged(object sender, EventArgs e)
    {
    }

    private void tbExtraFlag_TextChanged(object sender, EventArgs e)
    {
    }

    private void strNpcNamelodToolStripMenuItem_Click(object sender, EventArgs e)
    {
      new FormExport().Show();
    }

    private void exportMobAlllodToolStripMenuItem1_Click(object sender, EventArgs e)
    {
      new LodExporter.LodExporter().Show();
    }

    private void exportDropNpclodToolStripMenuItem_Click(object sender, EventArgs e)
    {
      this.exportLodHandle.ExportDropMobNpc_V4();
    }
  }
}
