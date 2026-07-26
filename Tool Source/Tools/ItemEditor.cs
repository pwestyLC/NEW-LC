// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.ItemEditor
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using MySqlConnector;
using SlimDX;
using SlimDX.Direct3D9;
using System;
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
  public class ItemEditor : Form
  {
    public static Connection connection = new Connection();
    private int w = 0;
    private int a = 0;
    private string Host = ItemEditor.connection.Settings.SqlHost;
    private string User = ItemEditor.connection.Settings.SqlUser;
    private string Password = ItemEditor.connection.Settings.SqlPassword;
    private string Database = ItemEditor.connection.Settings.SqlDatabase;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    public string rowName = "a_index";
    public string[] menuArray = new string[2]
    {
      "a_index",
      "a_name"
    };
    public string[] menuArray2 = new string[2]
    {
      "a_type",
      "a_name"
    };
    public string[] menuArray3 = new string[1]{ "a_level" };
    public string[] SearchMenu = new string[2]
    {
      "a_index",
      "a_name"
    };
    public string mSortJob = "-1";
    public string mSortJob2 = "-1";
    public string _SortAboveLevel = "-1";
    private string Episode = ItemEditor.connection.Settings.Episode;
    public System.Collections.Generic.List<string> MenuList = new System.Collections.Generic.List<string>();
    public System.Collections.Generic.List<string> MenuListSearch = new System.Collections.Generic.List<string>();
    public float _UpDown = -1f;
    private ASCIIEncoding _Enc = new ASCIIEncoding();
    public string _ClientPath = ItemEditor.connection.Settings.ClientPath;
    public bool _ComboBoxPurpleLocked = false;
    private ExportLodHandle exportLodHandle = new ExportLodHandle();
    private IContainer components = (IContainer) null;
    public System.Collections.Generic.List<string> List;
    public System.Collections.Generic.List<string> List2;
    public System.Collections.Generic.List<string> List3;
    public System.Collections.Generic.List<string> List4;
    public System.Collections.Generic.List<string> List5;
    public System.Collections.Generic.List<string> List6;
    public System.Collections.Generic.List<string> List7;
    public System.Collections.Generic.List<string> List8;
    public System.Collections.Generic.List<string> List9;
    public System.Collections.Generic.List<string> List10;
    public string name;
    public int index;
    public string test2;
    public Direct3D _Direct3D;
    public Device _Device;
    public float _Zoom;
    public float _LeftRight;
    public float _Rotation;
    public System.Collections.Generic.List<tMesh> _Models;
    public System.Collections.Generic.List<string> lArrayLevel;
    public string varf5;
    private MenuStrip menuStrip1;
    private ToolStripMenuItem fileExportToolStripMenuItem;
    private ToolStripMenuItem exportlodToolStripMenuItem;
    private GroupBox groupBox3;
    private Button button3;
    private Button button1;
    private ListBox listBox1;
    private TabControl tabControl1;
    private TabPage tabPage1;
    private TabPage tabPage2;
    private TabPage tabPage3;
    private Button button2;
    private GroupBox groupBox1;
    private GroupBox groupBox2;
    private TextBox textBox2;
    private Label label3;
    private TextBox textBox3;
    private Label label2;
    private TextBox textBox4;
    private Label label4;
    private Label label6;
    private TextBox textBox1;
    private Label label5;
    private Label label1;
    private TextBox textBox5;
    private TextBox textBox6;
    private GroupBox groupBox4;
    private TextBox textBox15;
    private Label label15;
    private TextBox textBox10;
    private Label label11;
    private Label label14;
    private TextBox textBox11;
    private TextBox textBox14;
    private Label label12;
    private Label label13;
    private TextBox textBox13;
    private Label label9;
    private Label label10;
    private TextBox textBox9;
    private TextBox textBox7;
    private GroupBox groupBox6;
    private TextBox textBox19;
    private Label label19;
    private TextBox textBox16;
    private Label label16;
    private Label label18;
    private TextBox textBox17;
    private TextBox textBox18;
    private Label label17;
    private Label label20;
    private TextBox textBox20;
    private TextBox textBox21;
    private Label label21;
    private TextBox textBox28;
    private Label label28;
    private TextBox textBox27;
    private Label label27;
    private TextBox textBox26;
    private Label label26;
    private TextBox textBox25;
    private Label label25;
    private TextBox textBox24;
    private Label label24;
    private TextBox textBox23;
    private Label label23;
    private Label label22;
    private TextBox textBox31;
    private Label label31;
    private TextBox textBox30;
    private Label label30;
    private TextBox textBox29;
    private Label label29;
    private TextBox textBox41;
    private Label label41;
    private TextBox textBox40;
    private Label label40;
    private TextBox textBox39;
    private Label label39;
    private TextBox textBox38;
    private Label label38;
    private TextBox textBox37;
    private Label label37;
    private TextBox textBox36;
    private Label label36;
    private TextBox textBox35;
    private Label label35;
    private TextBox textBox34;
    private Label label34;
    private TextBox textBox33;
    private Label label33;
    private TextBox textBox32;
    private Label label32;
    private GroupBox groupBox8;
    private TextBox textBox43;
    private Label label43;
    private TextBox textBox42;
    private Label label42;
    private TextBox textBox45;
    private Label label45;
    private TextBox textBox44;
    private Label label44;
    private TextBox textBox46;
    private Label label46;
    private Label label47;
    private TextBox textBox47;
    private GroupBox groupBox9;
    private Label label50;
    private TextBox textBox50;
    private Label label49;
    private TextBox textBox49;
    private Label label48;
    private TextBox textBox48;
    private PictureBox pictureBox1;
    private GroupBox groupBox10;
    private TextBox textBox55;
    private Label label55;
    private TextBox textBox54;
    private Label label54;
    private TextBox textBox53;
    private Label label53;
    private TextBox textBox52;
    private Label label52;
    private GroupBox groupBox11;
    private TextBox textBox57;
    private Label label56;
    private Label label57;
    private TextBox textBox56;
    private TextBox textBox58;
    private Label label58;
    private GroupBox groupBox13;
    private TextBox textBox68;
    private Label label68;
    private TextBox textBox67;
    private Label label67;
    private TextBox textBox66;
    private Label label66;
    private TextBox textBox65;
    private Label label65;
    private TextBox textBox64;
    private Label label64;
    private TextBox textBox63;
    private Label label63;
    private TextBox textBox62;
    private Label label62;
    private TextBox textBox61;
    private Label label61;
    private TextBox textBox60;
    private Label label60;
    private TextBox textBox69;
    private Label label69;
    private TextBox textBox79;
    private Label label79;
    private TextBox textBox78;
    private Label label78;
    private TextBox textBox77;
    private Label label77;
    private TextBox textBox76;
    private Label label76;
    private TextBox textBox75;
    private Label label75;
    private TextBox textBox74;
    private Label label74;
    private TextBox textBox73;
    private Label label73;
    private TextBox textBox72;
    private Label label72;
    private TextBox textBox71;
    private Label label71;
    private TextBox textBox70;
    private Label label70;
    private GroupBox groupBox14;
    private Label label80;
    private TextBox textBox80;
    private Label label82;
    private TextBox textBox82;
    private Label label81;
    private TextBox textBox81;
    private GroupBox groupBox16;
    private Label label92;
    private TextBox textBox92;
    private Label label91;
    private TextBox textBox91;
    private ComboBox comboBox1;
    private ComboBox comboBox4;
    private ComboBox comboBox2;
    private TextBox textBox90;
    private Label label90;
    private TextBox textBox89;
    private Label label89;
    private TextBox textBox88;
    private Label label88;
    private TextBox textBox87;
    private Label label87;
    private TextBox textBox86;
    private Label label86;
    private TextBox textBox85;
    private Label label85;
    private Button button4;
    private ToolStripMenuItem exportStrItemlodToolStripMenuItem;
    private CheckedListBox checkedListBox1;
    private TextBox textBox22;
    private Label label8;
    private CheckBox checkBox1;
    private TextBox textBox8;
    private GroupBox groupBox7;
    private GroupBox groupBox17;
    private ComboBox comboBox3;
    private Label label95;
    private Label label96;
    private Label label97;
    private Label label98;
    private Label label99;
    private ComboBox comboBox5;
    private ComboBox comboBox6;
    private ComboBox comboBox7;
    private ComboBox comboBox8;
    private ComboBox comboBox9;
    private ComboBox comboBox14;
    private Label label104;
    private ComboBox comboBox13;
    private Label label103;
    private Label label102;
    private Label label101;
    private Label label100;
    private ComboBox comboBox12;
    private ComboBox comboBox11;
    private ComboBox comboBox10;
    private ComboBox comboBox15;
    private ComboBox comboBox16;
    private ComboBox comboBox17;
    private ComboBox comboBox18;
    private ComboBox comboBox19;
    private ComboBox comboBox20;
    private LinkLabel linkLabel1;
    private PictureBox pictureBox3;
    private ToolTip toolTip1;
    private ComboBox comboBox21;
    private ComboBox comboBox22;
    private ComboBox comboBox23;
    private PictureBox pictureBox4;
    private PictureBox pictureBox5;
    private PictureBox pictureBox6;
    private PictureBox pictureBox7;
    private PictureBox pictureBox8;
    private PictureBox pictureBox9;
    private PictureBox pictureBox10;
    private PictureBox pictureBox11;
    private PictureBox pictureBox12;
    public PictureBox pictureBox13;
    public PictureBox pictureBox14;
    public PictureBox pictureBox15;
    public PictureBox pictureBox16;
    public PictureBox pictureBox17;
    public PictureBox pictureBox18;
    public PictureBox pictureBox19;
    public PictureBox pictureBox20;
    public PictureBox pictureBox21;
    public PictureBox pictureBox22;
    private PictureBox pictureBox23;
    public CheckedListBox clbFlagTest;
    private GroupBox groupBox18;
    private GroupBox groupBox19;
    private TextBox textBox12;
    private Label label7;
    private GroupBox groupBox5;
    private CheckedListBox checkedListBox2;
    private GroupBox groupBox20;
    private CheckBox chk3D;
    private TrackBar slideLeftRight;
    private TrackBar slideUpDown;
    private TrackBar slideZoom;
    private Panel panel3DView;
    private Timer timer1;
    private GroupBox groupBox12;
    private TextBox textBox93;
    private TextBox textBox94;
    private Label label93;
    private Label label94;
    private TextBox textBox84;
    private Label label84;
    private TextBox textBox83;
    private Label label83;
    private TextBox textBox51;
    private TextBox textBox59;
    private Label label51;
    private Label label59;
    private Label label105;
    private TextBox textBox95;

    public ItemEditor() => this.InitializeComponent();

    public ItemEditor(string text) => this.Text = text;

    private void LoadListBox()
    {
      this.listBox1.SelectedIndex = -1;
      this.MenuList.Clear();
      string Query = "SELECT a_index, a_name FROM t_item WHERE a_job_flag ='" + this.mSortJob + "' ORDER BY a_index;";
      if (this.mSortJob == "-1")
        Query = "SELECT a_index, a_name FROM t_item ORDER BY a_index;";
      if (this._SortAboveLevel != "-1")
        Query = "SELECT a_index, a_name FROM t_item WHERE a_level >= " + this._SortAboveLevel + ";";
      this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, Query);
      for (int index = 0; index < this.listBox1.Items.Count; ++index)
        this.MenuList.Add(this.listBox1.Items[index].ToString());
      this.listBox1.DataSource = (object) this.MenuList;
      this.listBox1.SelectedIndex = -1;
    }

    public void SearchList(string searchString)
    {
      searchString = searchString.Replace("\\", "\\\\").Replace("'", "\\'");
      string lower = searchString.ToLower();
      string upper = searchString.ToUpper();
      string str = "";
      if (searchString.Length > 1)
        str = char.ToUpper(searchString[0]).ToString() + searchString.Substring(1);
      this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, "select a_index, a_name from t_item WHERE a_name LIKE '%" + searchString + "%' OR a_index LIKE '%" + searchString + "%' OR a_name LIKE '%" + lower + "%' OR a_index  LIKE '%" + lower + "%' OR a_name LIKE '%" + upper + "%' OR a_index LIKE '%" + upper + "%' OR a_name LIKE '%" + str + "%' OR a_index LIKE '%" + str + "%' ORDER BY a_index;");
    }

    private void Exporter_Item_Load(object sender, EventArgs e)
    {
      this.InitializeDevice();
      this.LoadStartUp();
      this.SelectBoxes();
      this.LoadListBox();
      this.LoadMisc();
    }

    public void LoadMisc()
    {
      this.checkBox1.Checked = this.textBox4.Text == "1";
      int num1 = this.comboBox1.FindString(this.textBox2.Text);
      int num2 = this.comboBox2.FindString(this.textBox3.Text);
      int num3 = this.comboBox4.FindString(this.textBox9.Text);
      try
      {
        this.comboBox1.SelectedIndex = num1;
        this.comboBox2.SelectedIndex = num2;
        this.comboBox4.SelectedIndex = num3;
      }
      catch
      {
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
      this._ComboBoxPurpleLocked = true;
      if (this.listBox1.SelectedIndex != -1)
        this.textBox1.Text = this.GetIndex().ToString();
      this.ClearComboBoxPurple();
      this.ClearComboBoxPurple2();
      string Query = " select a_index , a_type_idx , a_subtype_idx , a_enable , a_name , a_descr, a_name_usa , a_descr_usa , a_job_flag , a_flag , a_wearing , a_num_0 , a_num_1 , a_num_2, a_num_3 , a_num_4 , a_level , a_level2 , a_weight , a_price , a_max_use , a_drop_prob_10 , a_need_item0 , a_need_item1 , a_need_item2 , a_need_item3 , a_need_item4 , a_need_item5 , a_need_item6 , a_need_item7 , a_need_item8 , a_need_item9 , a_need_item_count0 , a_need_item_count1 , a_need_item_count2 , a_need_item_count3 , a_need_item_count4 , a_need_item_count5 , a_need_item_count6 , a_need_item_count7 , a_need_item_count8 , a_need_item_count9 , a_need_sskill , a_need_sskill_level , a_need_sskill2 , a_need_sskill_level2 , a_zone_flag , a_file_smc , a_texture_id , a_texture_row , a_texture_col , b_todo_delete , a_set_0 , a_set_1 , a_set_2 , a_set_3 , a_set_4 , a_set , a_grade , a_fame , a_rare_index_0 , a_rare_index_1 , a_rare_index_2 , a_rare_index_3 , a_rare_index_4 , a_rare_index_5 , a_rare_index_6 , a_rare_index_7 , a_rare_index_8 , a_rare_index_9 , a_rare_prob_0 , a_rare_prob_1 , a_rare_prob_2 , a_rare_prob_3 , a_rare_prob_4 , a_rare_prob_5 , a_rare_prob_6 , a_rare_prob_7 , a_rare_prob_8 , a_rare_prob_9 , a_effect_name, a_attack_effect_name, a_damage_effect_name, a_quest_trigger_count , a_quest_trigger_ids , a_origin_variation1 , a_origin_variation2 , a_origin_variation3 , a_origin_variation4 , a_origin_variation5 , a_origin_variation6 , a_rvr_value , a_rvr_grade , a_durability , a_castle_war from t_item WHERE a_index ='" + this.textBox1.Text + "';";
      string[] rows = new string[93]
      {
        "a_index",
        "a_type_idx",
        "a_subtype_idx",
        "a_enable",
        "a_name_usa",
        "a_descr_usa",
        "a_job_flag",
        "a_flag",
        "a_wearing",
        "a_num_0",
        "a_num_1",
        "a_num_2",
        "a_num_3",
        "a_num_4",
        "a_level",
        "a_level2",
        "a_weight",
        "a_price",
        "a_max_use",
        "a_drop_prob_10",
        "a_need_item0",
        "a_need_item1",
        "a_need_item2",
        "a_need_item3",
        "a_need_item4",
        "a_need_item5",
        "a_need_item6",
        "a_need_item7",
        "a_need_item8",
        "a_need_item9",
        "a_need_item_count0",
        "a_need_item_count1",
        "a_need_item_count2",
        "a_need_item_count3",
        "a_need_item_count4",
        "a_need_item_count5",
        "a_need_item_count6",
        "a_need_item_count7",
        "a_need_item_count8",
        "a_need_item_count9",
        "a_need_sskill",
        "a_need_sskill_level",
        "a_need_sskill2",
        "a_need_sskill_level2",
        "a_zone_flag",
        "a_file_smc",
        "a_texture_id",
        "a_texture_row",
        "a_texture_col",
        "b_todo_delete",
        "a_set_0",
        "a_set_1",
        "a_set_2",
        "a_set_3",
        "a_set_4",
        "a_set",
        "a_grade",
        "a_fame",
        "a_rare_index_0",
        "a_rare_index_1",
        "a_rare_index_2",
        "a_rare_index_3",
        "a_rare_index_4",
        "a_rare_index_5",
        "a_rare_index_6",
        "a_rare_index_7",
        "a_rare_index_8",
        "a_rare_index_9",
        "a_rare_prob_0",
        "a_rare_prob_1",
        "a_rare_prob_2",
        "a_rare_prob_3",
        "a_rare_prob_4",
        "a_rare_prob_5",
        "a_rare_prob_6",
        "a_rare_prob_7",
        "a_rare_prob_8",
        "a_rare_prob_9",
        "a_effect_name",
        "a_attack_effect_name",
        "a_damage_effect_name",
        "a_quest_trigger_count",
        "a_quest_trigger_ids",
        "a_origin_variation1",
        "a_origin_variation2",
        "a_origin_variation3",
        "a_origin_variation4",
        "a_origin_variation5",
        "a_origin_variation6",
        "a_rvr_value",
        "a_rvr_grade",
        "a_durability",
        "a_castle_war"
      };
      Query.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'");
      string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query, rows);
      if (this.chk3D.Checked && File.Exists(this._ClientPath + strArray[45]))
      {
        Console.WriteLine("Create Model > " + this._ClientPath + strArray[45]);
        this.MakeLCModels(this._ClientPath + strArray[45]);
      }
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
      this.textBox13.Text = strArray[11];
      this.textBox14.Text = strArray[12];
      this.textBox15.Text = strArray[13];
      this.textBox16.Text = strArray[14];
      this.textBox17.Text = strArray[15];
      this.textBox18.Text = strArray[16];
      this.textBox19.Text = strArray[17];
      this.textBox20.Text = strArray[18];
      this.textBox21.Text = strArray[19];
      this.textBox22.Text = strArray[20];
      this.textBox23.Text = strArray[21];
      this.textBox24.Text = strArray[22];
      this.textBox25.Text = strArray[23];
      this.textBox26.Text = strArray[24];
      this.textBox27.Text = strArray[25];
      this.textBox28.Text = strArray[26];
      this.textBox29.Text = strArray[27];
      this.textBox30.Text = strArray[28];
      this.textBox31.Text = strArray[29];
      this.textBox32.Text = strArray[30];
      this.textBox33.Text = strArray[31];
      this.textBox34.Text = strArray[32];
      this.textBox35.Text = strArray[33];
      this.textBox36.Text = strArray[34];
      this.textBox37.Text = strArray[35];
      this.textBox38.Text = strArray[36];
      this.textBox39.Text = strArray[37];
      this.textBox40.Text = strArray[38];
      this.textBox41.Text = strArray[39];
      this.textBox42.Text = strArray[40];
      this.textBox43.Text = strArray[41];
      this.textBox44.Text = strArray[42];
      this.textBox45.Text = strArray[43];
      this.textBox46.Text = strArray[44];
      this.textBox47.Text = strArray[45];
      this.textBox48.Text = strArray[46];
      this.textBox49.Text = strArray[47];
      this.textBox50.Text = strArray[48];
      this.textBox51.Text = strArray[49];
      this.textBox52.Text = strArray[50];
      this.textBox53.Text = strArray[51];
      this.textBox54.Text = strArray[52];
      this.textBox55.Text = strArray[53];
      this.textBox56.Text = strArray[54];
      this.textBox57.Text = strArray[55];
      this.textBox58.Text = strArray[56];
      this.textBox59.Text = strArray[57];
      this.textBox60.Text = strArray[58];
      this.textBox61.Text = strArray[59];
      this.textBox62.Text = strArray[60];
      this.textBox63.Text = strArray[61];
      this.textBox64.Text = strArray[62];
      this.textBox65.Text = strArray[63];
      this.textBox66.Text = strArray[64];
      this.textBox67.Text = strArray[65];
      this.textBox68.Text = strArray[66];
      this.textBox69.Text = strArray[67];
      this.textBox70.Text = strArray[68];
      this.textBox71.Text = strArray[69];
      this.textBox72.Text = strArray[70];
      this.textBox73.Text = strArray[71];
      this.textBox74.Text = strArray[72];
      this.textBox75.Text = strArray[73];
      this.textBox76.Text = strArray[74];
      this.textBox77.Text = strArray[75];
      this.textBox78.Text = strArray[76];
      this.textBox79.Text = strArray[77];
      this.textBox80.Text = strArray[78];
      this.textBox81.Text = strArray[79];
      this.textBox82.Text = strArray[80];
      this.textBox83.Text = strArray[81];
      this.textBox84.Text = strArray[82];
      this.textBox85.Text = strArray[83];
      this.textBox86.Text = strArray[84];
      this.textBox87.Text = strArray[85];
      this.textBox88.Text = strArray[86];
      this.textBox89.Text = strArray[87];
      this.textBox90.Text = strArray[88];
      this.textBox91.Text = strArray[89];
      this.textBox92.Text = strArray[90];
      this.textBox93.Text = strArray[91];
      this.textBox94.Text = strArray[92];
      this.SelectBoxes();
      int int32 = Convert.ToInt32(strArray[6]);
      if (this.Episode == "EP4")
        this.ShowFlagLong(Convert.ToInt64(strArray[7]));
      else
        this.ShowFlag(Convert.ToInt32(strArray[7]));
      this.ShowJobFlag(int32);
      this.LoadMisc();
      try
      {
        this.pictureBox1.Image = (Image) this.databaseHandle.IconItem(int.Parse(this.textBox48.Text), int.Parse(this.textBox49.Text), int.Parse(this.textBox50.Text));
      }
      catch
      {
      }
      long int64 = Convert.ToInt64(strArray[7]);
      if (this.FlagCheck(int64, 19) && !this.FlagCheck(int64, 26))
      {
        this.comboBox5.SelectedIndex = int.Parse(this.textBox61.Text);
        this.comboBox6.SelectedIndex = int.Parse(this.textBox62.Text);
        this.comboBox7.SelectedIndex = int.Parse(this.textBox63.Text);
        this.comboBox8.SelectedIndex = int.Parse(this.textBox64.Text);
        this.comboBox9.SelectedIndex = int.Parse(this.textBox65.Text);
        this.comboBox10.SelectedIndex = int.Parse(this.textBox66.Text);
        this.SetSelectedComboBoxPurple2();
      }
      this._ComboBoxPurpleLocked = false;
    }

    public bool FlagCheck(long Flag, int CheckFlag) => (Flag & (long) (1 << CheckFlag)) > 0L;

    private void SelectBoxes()
    {
      this.comboBox2.SelectedIndex = this.comboBox2.FindString(this.textBox3.Text);
    }

    private void button2_Click(object sender, EventArgs e)
    {
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_item SET a_type_idx = '" + this.textBox2.Text + "', a_subtype_idx = '" + this.textBox3.Text + "', a_enable = '" + this.textBox4.Text + "', " + "a_name_usa = '" + this.textBox5.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_descr_usa = '" + this.textBox6.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_job_flag = '" + this.textBox7.Text + "', a_flag = '" + this.textBox8.Text + "', a_wearing = '" + this.textBox9.Text + "', a_num_0 = '" + this.textBox10.Text + "', a_num_1 = '" + this.textBox11.Text + "', a_num_2 = '" + this.textBox13.Text + "', a_num_3 = '" + this.textBox14.Text + "', a_num_4 = '" + this.textBox15.Text + "', a_level = '" + this.textBox16.Text + "', a_level2 = '" + this.textBox17.Text + "', a_weight = '" + this.textBox18.Text + "', a_price = '" + this.textBox19.Text + "', a_max_use = '" + this.textBox20.Text + "', a_drop_prob_10 = '" + this.textBox21.Text + "', a_need_item0 = '" + this.textBox22.Text + "', a_need_item1 = '" + this.textBox23.Text + "', a_need_item2 = '" + this.textBox24.Text + "', a_need_item3 = '" + this.textBox25.Text + "', a_need_item4 = '" + this.textBox26.Text + "', a_need_item5 = '" + this.textBox27.Text + "', a_need_item6 = '" + this.textBox28.Text + "', a_need_item7 = '" + this.textBox29.Text + "', a_need_item8 = '" + this.textBox30.Text + "', a_need_item9 = '" + this.textBox31.Text + "', a_need_item_count0 = '" + this.textBox32.Text + "', a_need_item_count1 = '" + this.textBox33.Text + "', a_need_item_count2 = '" + this.textBox34.Text + "', a_need_item_count3 = '" + this.textBox35.Text + "', a_need_item_count4 = '" + this.textBox36.Text + "', a_need_item_count5 = '" + this.textBox37.Text + "', a_need_item_count6 = '" + this.textBox38.Text + "', a_need_item_count7 = '" + this.textBox39.Text + "', a_need_item_count8 = '" + this.textBox40.Text + "', a_need_item_count9 = '" + this.textBox41.Text + "', a_need_sskill = '" + this.textBox42.Text + "', a_need_sskill_level = '" + this.textBox43.Text + "', a_need_sskill2 = '" + this.textBox44.Text + "', a_need_sskill_level2 = '" + this.textBox45.Text + "', a_zone_flag = '" + this.textBox46.Text + "', a_file_smc = '" + this.textBox47.Text.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'") + "', a_texture_id = '" + this.textBox48.Text + "', a_texture_row = '" + this.textBox49.Text + "', a_texture_col = '" + this.textBox50.Text + "', b_todo_delete = '" + this.textBox51.Text + "', a_set_0 = '" + this.textBox52.Text + "', a_set_1 = '" + this.textBox53.Text + "', a_set_2 = '" + this.textBox54.Text + "', a_set_3 = '" + this.textBox55.Text + "', a_set_4 = '" + this.textBox56.Text + "', a_set = '" + this.textBox57.Text + "', a_grade = '" + this.textBox58.Text + "', a_fame = '" + this.textBox59.Text + "', a_rare_index_0 = '" + this.textBox60.Text + "', a_rare_index_1 = '" + this.textBox61.Text + "', a_rare_index_2 = '" + this.textBox62.Text + "', a_rare_index_3 = '" + this.textBox63.Text + "', a_rare_index_4 = '" + this.textBox64.Text + "', a_rare_index_5 = '" + this.textBox65.Text + "', a_rare_index_6 = '" + this.textBox66.Text + "', a_rare_index_7 = '" + this.textBox67.Text + "', a_rare_index_8 = '" + this.textBox68.Text + "', a_rare_index_9 = '" + this.textBox69.Text + "', a_rare_prob_0 = '" + this.textBox70.Text + "', a_rare_prob_1 = '" + this.textBox71.Text + "', a_rare_prob_2 = '" + this.textBox72.Text + "', a_rare_prob_3 = '" + this.textBox73.Text + "', a_rare_prob_4 = '" + this.textBox74.Text + "', a_rare_prob_5 = '" + this.textBox75.Text + "', a_rare_prob_6 = '" + this.textBox76.Text + "', a_rare_prob_7 = '" + this.textBox77.Text + "', a_rare_prob_8 = '" + this.textBox78.Text + "', a_rare_prob_9 = '" + this.textBox79.Text + "', a_effect_name = '" + this.textBox80.Text + "', a_attack_effect_name = '" + this.textBox81.Text + "', a_damage_effect_name = '" + this.textBox82.Text + "', a_quest_trigger_count = '" + this.textBox83.Text + "', a_quest_trigger_ids = '" + this.textBox84.Text + "', a_origin_variation1 = '" + this.textBox85.Text + "', a_origin_variation2 = '" + this.textBox86.Text + "', a_origin_variation3 = '" + this.textBox87.Text + "', a_origin_variation4 = '" + this.textBox88.Text + "', a_origin_variation5 = '" + this.textBox89.Text + "', a_origin_variation6 = '" + this.textBox90.Text + "', a_rvr_value = '" + this.textBox91.Text + "', a_rvr_grade = '" + this.textBox92.Text + "', a_durability = '" + this.textBox93.Text + "', a_castle_war = '" + this.textBox94.Text + "' WHERE a_index = '" + this.textBox1.Text + "'");
      int selectedIndex = this.listBox1.SelectedIndex;
      if (this.textBox12.Text != "")
        this.SearchList(this.textBox12.Text);
      else
        this.LoadListBox();
      this.listBox1.SelectedIndex = selectedIndex;
    }

    private void button1_Click(object sender, EventArgs e)
    {
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_item DEFAULT VALUES");
      this.LoadListBox();
      this.listBox1.SelectedIndex = this.listBox1.Items.Count - 1;
      this.textBox4.Text = "1";
      this.textBox46.Text = "1023";
      this.checkBox1.Checked = true;
      this.checkBox1.BackColor = Color.Lime;
    }

    private void button3_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want to Delete Item " + this.textBox1.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      int selectedIndex = this.listBox1.SelectedIndex;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_item WHERE a_index = '" + this.textBox1.Text + "'");
      this.LoadListBox();
      this.listBox1.SelectedIndex = selectedIndex - 1;
    }

    private void exportlodToolStripMenuItem_Click(object sender, EventArgs e)
    {
      this.exportLodHandle.ExportItemAll_V4();
    }

    private void checkBox1_CheckedChanged(object sender, EventArgs e)
    {
      if (this.checkBox1.Checked)
      {
        this.textBox4.Text = "1";
        this.checkBox1.BackColor = Color.Lime;
      }
      else
      {
        this.textBox4.Text = "0";
        this.checkBox1.BackColor = Color.Red;
      }
    }

    private void LoadStartUp()
    {
      string str1 = "SELECT * FROM t_option ORDER BY a_index";
      MySqlConnection mySqlConnection = new MySqlConnection("datasource=" + this.Host + ";Port=3306;User ID="  + this.User + ";Password=" + this.Password + ";Database=" + this.Database + ";Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;");
      MySqlCommand command = mySqlConnection.CreateCommand();
      command.CommandText = str1;
      mySqlConnection.Open();
      MySqlDataReader mySqlDataReader = command.ExecuteReader();
      while (mySqlDataReader.Read())
      {
        int ordinal1 = mySqlDataReader.GetOrdinal("a_index");
        mySqlDataReader.GetString(ordinal1);
        int ordinal2 = mySqlDataReader.GetOrdinal("a_type");
        string str2 = mySqlDataReader.GetString(ordinal2);
        int ordinal3 = mySqlDataReader.GetOrdinal("a_name");
        string str3 = mySqlDataReader.GetString(ordinal3);
        string str4 = str2 + " - " + str3;
        this.comboBox3.Items.Add((object) str4);
        this.comboBox5.Items.Add((object) str4);
        this.comboBox6.Items.Add((object) str4);
        this.comboBox7.Items.Add((object) str4);
        this.comboBox8.Items.Add((object) str4);
        this.comboBox9.Items.Add((object) str4);
        this.comboBox10.Items.Add((object) str4);
        this.comboBox11.Items.Add((object) str4);
        this.comboBox12.Items.Add((object) str4);
        this.comboBox13.Items.Add((object) str4);
      }
      mySqlConnection.Close();
      this.checkedListBox1.Items.AddRange(new object[11]
      {
        (object) "Titan",
        (object) "Knight",
        (object) "Healer",
        (object) "Mage",
        (object) "Rogue",
        (object) "Sorcerer",
        (object) "NS",
        (object) "Ex-Rogue",
        (object) "Ex-Mage",
        (object) "P1 Pet",
        (object) "P2 Pet"
      });
      this.checkedListBox2.Items.AddRange(new object[9]
      {
        (object) "Titan",
        (object) "Knight",
        (object) "Healer",
        (object) "Mage",
        (object) "Rogue",
        (object) "Sorcerer",
        (object) "NS",
        (object) "Ex-Rogue",
        (object) "Ex-Mage"
      });
      if (this.Episode == "EP4")
        this.clbFlagTest.Items.AddRange(new object[64]
        {
          (object) "Count",
          (object) "Drop",
          (object) "Upgrade",
          (object) "Exchange",
          (object) "Trade",
          (object) "Not Delete",
          (object) "Made",
          (object) "Mix",
          (object) "Cash",
          (object) "Lord",
          (object) "No Stash",
          (object) "Change",
          (object) "Composite",
          (object) "Duplication",
          (object) "lent",
          (object) "Rare",
          (object) "ABS",
          (object) "Not Reform",
          (object) "ZoneMove Del",
          (object) "Origin",
          (object) "Trigger",
          (object) "Raid Special",
          (object) "Quest",
          (object) "Box",
          (object) "Not TradeAgent",
          (object) "Durability",
          (object) "Costume2",
          (object) "Socket",
          (object) "Seller",
          (object) "Castillan",
          (object) "LetsParty",
          (object) "Non-RVR",
          (object) "Quest Give",
          (object) "Toggle",
          (object) "Compose",
          (object) "NotSingle",
          (object) "Invisible Custom",
          (object) "37 ",
          (object) "38 ",
          (object) "39 ",
          (object) "40 ",
          (object) "41 ",
          (object) "42 ",
          (object) "43 ",
          (object) "44 ",
          (object) "45 ",
          (object) "46 ",
          (object) "47 ",
          (object) "48 ",
          (object) "49 ",
          (object) "50 ",
          (object) "51 ",
          (object) "52 ",
          (object) "53 ",
          (object) "54 ",
          (object) "55 ",
          (object) "56 ",
          (object) "57 ",
          (object) "58 ",
          (object) "59 ",
          (object) "60 ",
          (object) "61 ",
          (object) "62 ",
          (object) "63 "
        });
      else
        this.clbFlagTest.Items.AddRange(new object[37]
        {
          (object) "Count",
          (object) "Drop",
          (object) "Upgrade",
          (object) "Exchange",
          (object) "Trade",
          (object) "Not Delete",
          (object) "Made",
          (object) "Mix",
          (object) "Cash",
          (object) "Lord",
          (object) "No Stash",
          (object) "Change",
          (object) "Composite",
          (object) "Duplication",
          (object) "lent",
          (object) "Rare",
          (object) "ABS",
          (object) "Not Reform",
          (object) "ZoneMove Del",
          (object) "Origin",
          (object) "Trigger",
          (object) "Raid Special",
          (object) "Quest",
          (object) "Box",
          (object) "Not TradeAgent",
          (object) "Durability",
          (object) "Costume2",
          (object) "Socket",
          (object) "Seller",
          (object) "Castillan",
          (object) "LetsParty",
          (object) "Non-RVR",
          (object) "Quest Give",
          (object) "Toggle",
          (object) "Compose",
          (object) "NotSingle",
          (object) "Invisible Custom"
        });
      this.comboBox1.Items.AddRange(new object[8]
      {
        (object) "0 - Weapons",
        (object) "1 - Armor",
        (object) "2 - Books, Scrolls",
        (object) "3 - Shot",
        (object) "4 - Quest, Event, Upgrade",
        (object) "5 - Accesoires, Pets",
        (object) "6 - Potions",
        (object) "Unknown"
      });
      this.comboBox4.Items.AddRange(new object[14]
      {
        (object) "-1 - None",
        (object) "0 - Hood Slot",
        (object) "1 - Shirt Slot",
        (object) "2 - Weapon Slot",
        (object) "3 - Pants Slot",
        (object) "4 - Shield Slot",
        (object) "5 - Gloves Slot",
        (object) "6 - Boots Slot",
        (object) "7 - Accesoire Slot",
        (object) "8 - Accesoire Slot",
        (object) "9 - Accesoire Slot",
        (object) "10 - Pet Slot",
        (object) "11 - Wing Slot",
        (object) "12 - Not Know"
      });
    }

    public static string[] SubTypes(int Type)
    {
      System.Collections.Generic.List<string> stringList = new System.Collections.Generic.List<string>();
      switch (Type)
      {
        case 0:
          stringList.Add("0 - Single Sword");
          stringList.Add("1 - X-Bow");
          stringList.Add("2 - Staff");
          stringList.Add("3 - Big Sword");
          stringList.Add("4 - Axe");
          stringList.Add("5 - Wand");
          stringList.Add("6 - Bow");
          stringList.Add("7 - Dagger");
          stringList.Add("8 - Hammer");
          stringList.Add("9 - Knife");
          stringList.Add("10 - Energy Collector");
          stringList.Add("11 - Dual Swords");
          stringList.Add("12 - Scepter");
          stringList.Add("13 - Scythe");
          stringList.Add("14 - Fallarm");
          stringList.Add("15 - NS Weapon");
          break;
        case 1:
          stringList.Add("0 - Helm");
          stringList.Add("1 - Shirt");
          stringList.Add("2 - Pants");
          stringList.Add("3 - Gloves");
          stringList.Add("4 - Boots");
          stringList.Add("5 - Shield");
          stringList.Add("6 - Wing");
          stringList.Add("7 - Complete Costume");
          break;
        case 2:
          stringList.Add("0 - Teleporting");
          stringList.Add("1 - Production Manual");
          stringList.Add("2 - Crafting Manual");
          stringList.Add("3 - Box");
          stringList.Add("4 - Potion Manual");
          stringList.Add("5 - Transformation Scrolls");
          stringList.Add("6 - Quest Scrolls");
          stringList.Add("7 - Changing Stuff");
          stringList.Add("8 - Mob Summoning");
          stringList.Add("9 - Boxes and Monstercombo");
          stringList.Add("10 - Attack Scrolls");
          stringList.Add("11 - Titles");
          stringList.Add("12 - Reward Package");
          stringList.Add("13 - Jumping Potion");
          stringList.Add("14 - Extend Character Slot");
          stringList.Add("15 - Server Trans");
          stringList.Add("16 - Remote Express");
          stringList.Add("17 - Jewel Pocket");
          stringList.Add("18 - Chaos Jewel Pocket");
          stringList.Add("19 - Cash Inventory");
          stringList.Add("20 - Pet Stash");
          stringList.Add("21 - GPS");
          stringList.Add("22 - Holy Water");
          stringList.Add("23 - Protect PVP");
          stringList.Add("24 - Cash Ticket");
          stringList.Add("25 - statpt_remain_200");
          break;
        case 3:
          stringList.Add("0 - Item Bullet Attack");
          stringList.Add("1 - Item Bullet Mana");
          stringList.Add("2 - Item Bullet Arrow");
          break;
        case 4:
          stringList.Add("0 - Quest Items");
          stringList.Add("1 - Event");
          stringList.Add("2 - SkillUp");
          stringList.Add("3 - Upgrade Stuff");
          stringList.Add("4 - Materials & Skillbooks");
          stringList.Add("5 - Gold");
          stringList.Add("6 - Materials 1");
          stringList.Add("7 - Materials 2");
          stringList.Add("8 - Bloodseal Items");
          stringList.Add("9 - Powder");
          stringList.Add("10 - Event Items 1");
          stringList.Add("11 - Castle Siege Concentration");
          stringList.Add("12 - Castle Siege Powder");
          stringList.Add("13 - Castle Siege Stone");
          stringList.Add("14 - [P2] Target");
          stringList.Add("15 - Quest Trigger");
          stringList.Add("16 - Socket Jewel");
          stringList.Add("17 - Socket Upgrading");
          stringList.Add("18 - Socket Creation");
          stringList.Add("19 - Monster Mercenary");
          stringList.Add("20 - Guild Mark");
          stringList.Add("21 - Reformer");
          stringList.Add("22 - Chaos jewel");
          stringList.Add("23 - Function");
          stringList.Add("24 - RvR Jewel");
          break;
        case 5:
          stringList.Add("0 - Accesoires Charm");
          stringList.Add("1 - Accesoires Magic Stone");
          stringList.Add("2 - Accesoires Light Stone");
          stringList.Add("3 - Accesoires Earing");
          stringList.Add("4 - Accesoires Ring");
          stringList.Add("5 - Accesoires Necklace");
          stringList.Add("6 - P1 Pet");
          stringList.Add("7 - P2 Pet");
          stringList.Add("8 - Artifact");
          break;
        case 6:
          stringList.Add("0 - Antidotes / Cures");
          stringList.Add("1 - HP Heal Potions");
          stringList.Add("2 - MP Heal Potions");
          stringList.Add("3 - HP+MP Heal Potions");
          stringList.Add("4 - HP, MP, Attack Boost");
          stringList.Add("5 - Steroids");
          stringList.Add("6 - Minerals");
          stringList.Add("7 - Tears");
          stringList.Add("8 - Exp Crystals");
          stringList.Add("9 - NPC Scroll");
          stringList.Add("10 - HP Recovery Speed Potions");
          stringList.Add("11 - MP Recovery Speed Potions");
          stringList.Add("12 - [P2] Heal Items");
          stringList.Add("13 - [P2] SpeedUp");
          break;
        default:
          stringList.Add("-1 - Unknown");
          break;
      }
      return stringList.ToArray();
    }

    private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.comboBox2.Items.Clear();
      this.comboBox2.Items.AddRange((object[]) ItemEditor.SubTypes(this.comboBox1.SelectedIndex));
      this.textBox2.Text = this.comboBox1.SelectedIndex.ToString();
      this.LoadMisc();
    }

    private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox3.Text = this.GetIndexByComboBox(this.comboBox2.Text).ToString();
    }

    private void comboBox4_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox9.Text = this.GetIndexByComboBox(this.comboBox4.Text).ToString();
    }

    public bool SearchString(string s) => s.ToUpper().Contains(this.textBox12.Text.ToUpper());

    private void textBox12_TextChanged(object sender, EventArgs e)
    {
      this.MenuListSearch = this.MenuList.FindAll(new Predicate<string>(this.SearchString));
      this.listBox1.DataSource = (object) this.MenuListSearch;
    }

    private void SetFlag(long flag, CheckedListBox clbFlagTest)
    {
      for (int index = 0; index < 64; ++index)
        clbFlagTest.SetItemChecked(index, (flag & 1L << index) > 0L);
    }

    private long GetFlag(CheckedListBox clbFlagTest)
    {
      long flag = 0;
      for (int index = 0; index < clbFlagTest.Items.Count; ++index)
      {
        if (clbFlagTest.GetItemChecked(index))
          flag += 1L << index;
      }
      return flag;
    }

    private void tabPage1_Click(object sender, EventArgs e)
    {
    }

    private void ShowJobFlag(int flag)
    {
      for (int index = 0; index < this.checkedListBox1.Items.Count; ++index)
        this.checkedListBox1.SetItemChecked(index, (flag & 1 << index) > 0);
    }

    private void ShowFlagLong(long flag)
    {
      for (int index = 0; index < 64; ++index)
        this.clbFlagTest.SetItemChecked(index, (flag & 1L << index) > 0L);
    }

    private void ShowFlag(int flag)
    {
      for (int index = 0; index < this.clbFlagTest.Items.Count; ++index)
        this.clbFlagTest.SetItemChecked(index, (flag & 1 << index) > 0);
    }

    private void button4_Click(object sender, EventArgs e)
    {
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DROP TABLE IF EXISTS tempTable;CREATE TEMPORARY TABLE tempTable ENGINE=MEMORY SELECT * FROM t_item WHERE a_index=" + this.textBox1.Text + ";SELECT a_index FROM tempTable;UPDATE tempTable SET a_index=(SELECT a_index from t_item ORDER BY a_index DESC LIMIT 1)+1; SELECT a_index FROM tempTable;INSERT INTO t_item SELECT * FROM tempTable;");
      this.LoadListBox();
      this.listBox1.SelectedIndex = this.listBox1.Items.Count - 1;
    }

    private void exportStrItemlodToolStripMenuItem_Click(object sender, EventArgs e)
    {
      this.exportLodHandle.ExportString_V4("strItem");
    }

    private void checkedListBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      int num = 0;
      for (int index = 0; index < this.checkedListBox1.Items.Count; ++index)
      {
        if (this.checkedListBox1.GetItemChecked(index))
          num += 1 << index;
      }
      this.textBox7.Text = num.ToString();
    }

    private void clbFlagTest_SelectedIndexChanged_1(object sender, EventArgs e)
    {
      long num = 0;
      for (int index = 0; index < this.clbFlagTest.Items.Count; ++index)
      {
        if (this.clbFlagTest.GetItemChecked(index))
          num += 1L << index;
      }
      this.textBox8.Text = num.ToString();
    }

    private void comboBox3_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox60.Text = this.comboBox3.SelectedIndex.ToString();
      this.List = this.databaseHandle.SelectMySqlExplodedReturnList(this.menuArray3, this.Host, this.User, this.Password, this.Database, "select * from t_option WHERE a_type = '" + this.textBox60.Text + "' ORDER BY a_index;");
      this.comboBox14.DataSource = (object) null;
      this.comboBox14.Items.Clear();
      this.comboBox14.DataSource = (object) this.List;
    }

    private void comboBox5_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox61.Text = this.comboBox5.SelectedIndex.ToString();
      this.List2 = this.databaseHandle.SelectMySqlExplodedReturnList(this.menuArray3, this.Host, this.User, this.Password, this.Database, "select * from t_option WHERE a_type = '" + this.textBox61.Text + "' ORDER BY a_index;");
      this.comboBox15.DataSource = (object) null;
      this.comboBox15.Items.Clear();
      this.comboBox15.DataSource = (object) this.List2;
      if (!(this.textBox61.Text != "-1"))
        return;
      this.comboBox15.SelectedIndex = Convert.ToInt32(this.textBox71.Text) - 1;
    }

    private void SetSelectedComboBoxPurple2()
    {
      if (this.textBox61.Text != "-1")
        this.comboBox15.SelectedIndex = Convert.ToInt32(this.textBox71.Text) - 1;
      if (this.textBox62.Text != "-1")
        this.comboBox16.SelectedIndex = Convert.ToInt32(this.textBox72.Text) - 1;
      if (this.textBox63.Text != "-1")
        this.comboBox17.SelectedIndex = Convert.ToInt32(this.textBox73.Text) - 1;
      if (this.textBox64.Text != "-1")
        this.comboBox18.SelectedIndex = Convert.ToInt32(this.textBox74.Text) - 1;
      if (this.textBox65.Text != "-1")
        this.comboBox19.SelectedIndex = Convert.ToInt32(this.textBox75.Text) - 1;
      if (!(this.textBox66.Text != "-1"))
        return;
      this.comboBox20.SelectedIndex = Convert.ToInt32(this.textBox76.Text) - 1;
    }

    private void ClearComboBoxPurple2()
    {
      this.comboBox15.SelectedIndex = -1;
      this.comboBox16.SelectedIndex = -1;
      this.comboBox17.SelectedIndex = -1;
      this.comboBox18.SelectedIndex = -1;
      this.comboBox19.SelectedIndex = -1;
      this.comboBox20.SelectedIndex = -1;
    }

    private void ClearComboBoxPurple()
    {
      this.comboBox5.SelectedIndex = -1;
      this.comboBox6.SelectedIndex = -1;
      this.comboBox7.SelectedIndex = -1;
      this.comboBox8.SelectedIndex = -1;
      this.comboBox9.SelectedIndex = -1;
      this.comboBox10.SelectedIndex = -1;
    }

    private void comboBox14_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox70.Text = this.comboBox14.SelectedIndex.ToString();
    }

    private void comboBox15_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (this._ComboBoxPurpleLocked)
        return;
      this.textBox71.Text = (this.comboBox15.SelectedIndex + 1).ToString();
    }

    private void comboBox6_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox62.Text = this.comboBox6.SelectedIndex.ToString();
      this.List3 = this.databaseHandle.SelectMySqlExplodedReturnList(this.menuArray3, this.Host, this.User, this.Password, this.Database, "select * from t_option WHERE a_type = '" + this.textBox62.Text + "' ORDER BY a_index;");
      this.comboBox16.DataSource = (object) null;
      this.comboBox16.Items.Clear();
      this.comboBox16.DataSource = (object) this.List3;
      if (!(this.textBox62.Text != "-1"))
        return;
      this.comboBox16.SelectedIndex = Convert.ToInt32(this.textBox72.Text);
    }

    private void comboBox16_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (this._ComboBoxPurpleLocked)
        return;
      this.textBox72.Text = (this.comboBox16.SelectedIndex + 1).ToString();
    }

    private void comboBox7_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox63.Text = this.comboBox7.SelectedIndex.ToString();
      this.List4 = this.databaseHandle.SelectMySqlExplodedReturnList(this.menuArray3, this.Host, this.User, this.Password, this.Database, "select * from t_option WHERE a_type = '" + this.textBox63.Text + "' ORDER BY a_index;");
      this.comboBox17.DataSource = (object) null;
      this.comboBox17.Items.Clear();
      this.comboBox17.DataSource = (object) this.List4;
      if (!(this.textBox63.Text != "-1"))
        return;
      this.comboBox17.SelectedIndex = Convert.ToInt32(this.textBox73.Text);
    }

    private void comboBox17_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (this._ComboBoxPurpleLocked)
        return;
      this.textBox73.Text = (this.comboBox17.SelectedIndex + 1).ToString();
    }

    private void comboBox8_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox64.Text = this.comboBox8.SelectedIndex.ToString();
      this.List5 = this.databaseHandle.SelectMySqlExplodedReturnList(this.menuArray3, this.Host, this.User, this.Password, this.Database, "select * from t_option WHERE a_type = '" + this.textBox64.Text + "' ORDER BY a_index;");
      this.comboBox18.DataSource = (object) null;
      this.comboBox18.Items.Clear();
      this.comboBox18.DataSource = (object) this.List5;
      if (!(this.textBox64.Text != "-1"))
        return;
      this.comboBox18.SelectedIndex = Convert.ToInt32(this.textBox74.Text);
    }

    private void comboBox18_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (this._ComboBoxPurpleLocked)
        return;
      this.textBox74.Text = (this.comboBox18.SelectedIndex + 1).ToString();
    }

    private void comboBox9_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox65.Text = this.comboBox9.SelectedIndex.ToString();
      this.List6 = this.databaseHandle.SelectMySqlExplodedReturnList(this.menuArray3, this.Host, this.User, this.Password, this.Database, "select * from t_option WHERE a_type = '" + this.textBox65.Text + "' ORDER BY a_index;");
      this.comboBox19.DataSource = (object) null;
      this.comboBox19.Items.Clear();
      this.comboBox19.DataSource = (object) this.List6;
      if (!(this.textBox65.Text != "-1"))
        return;
      this.comboBox19.SelectedIndex = Convert.ToInt32(this.textBox75.Text);
    }

    private void comboBox19_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (this._ComboBoxPurpleLocked)
        return;
      this.textBox75.Text = (this.comboBox19.SelectedIndex + 1).ToString();
    }

    private void comboBox10_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox66.Text = this.comboBox10.SelectedIndex.ToString();
      this.List7 = this.databaseHandle.SelectMySqlExplodedReturnList(this.menuArray3, this.Host, this.User, this.Password, this.Database, "select * from t_option WHERE a_type = '" + this.textBox66.Text + "' ORDER BY a_index;");
      this.comboBox20.DataSource = (object) null;
      this.comboBox20.Items.Clear();
      this.comboBox20.DataSource = (object) this.List7;
      if (!(this.textBox66.Text != "-1"))
        return;
      this.comboBox20.SelectedIndex = Convert.ToInt32(this.textBox76.Text);
    }

    private void comboBox20_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (this._ComboBoxPurpleLocked)
        return;
      this.textBox76.Text = (this.comboBox20.SelectedIndex + 1).ToString();
    }

    private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
    {
      IconPickerItem iconPickerItem = new IconPickerItem();
      iconPickerItem.OldItemBtnSelect = Convert.ToInt32(this.textBox48.Text);
      if (iconPickerItem.ShowDialog() != DialogResult.OK)
        return;
      this.textBox48.Text = iconPickerItem.TexID.ToString();
      this.textBox49.Text = iconPickerItem.TexColumn.ToString();
      this.textBox50.Text = iconPickerItem.TexRow.ToString();
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_item SET a_texture_id = '" + this.textBox48.Text + "', a_texture_row = '" + this.textBox50.Text + "', a_texture_col = '" + this.textBox49.Text + "' WHERE a_index = '" + this.textBox1.Text + "'");
      int selectedIndex = this.listBox1.SelectedIndex;
      if (this.textBox12.Text != "")
        this.SearchList(this.textBox12.Text);
      else
        this.LoadListBox();
      this.listBox1.SelectedIndex = selectedIndex;
    }

    private void comboBox11_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox67.Text = this.comboBox11.SelectedIndex.ToString();
      this.List8 = this.databaseHandle.SelectMySqlExplodedReturnList(this.menuArray3, this.Host, this.User, this.Password, this.Database, "select * from t_option WHERE a_type = '" + this.textBox67.Text + "' ORDER BY a_index;");
      this.comboBox21.DataSource = (object) null;
      this.comboBox21.Items.Clear();
      this.comboBox21.DataSource = (object) this.List8;
    }

    private void comboBox21_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox77.Text = this.comboBox21.SelectedIndex.ToString();
    }

    private void comboBox12_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox68.Text = this.comboBox12.SelectedIndex.ToString();
      this.List9 = this.databaseHandle.SelectMySqlExplodedReturnList(this.menuArray3, this.Host, this.User, this.Password, this.Database, "select * from t_option WHERE a_type = '" + this.textBox68.Text + "' ORDER BY a_index;");
      this.comboBox22.DataSource = (object) null;
      this.comboBox22.Items.Clear();
      this.comboBox22.DataSource = (object) this.List9;
    }

    private void comboBox22_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox78.Text = this.comboBox22.SelectedIndex.ToString();
    }

    private void comboBox13_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox69.Text = this.comboBox13.SelectedIndex.ToString();
      this.List10 = this.databaseHandle.SelectMySqlExplodedReturnList(this.menuArray3, this.Host, this.User, this.Password, this.Database, "select * from t_option WHERE a_type = '" + this.textBox69.Text + "' ORDER BY a_index;");
      this.comboBox23.DataSource = (object) null;
      this.comboBox23.Items.Clear();
      this.comboBox23.DataSource = (object) this.List10;
    }

    private void comboBox23_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox79.Text = this.comboBox23.SelectedIndex.ToString();
    }

    private void pictureBox3_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox22.Text = itemPicker.ItemIndex.ToString();
    }

    private void pictureBox3_MouseMove_1(object sender, MouseEventArgs e)
    {
      this.pictureBox3.Size = new Size(26, 26);
    }

    private void pictureBox3_MouseLeave(object sender, EventArgs e)
    {
      this.pictureBox3.Size = new Size(22, 22);
    }

    private void pictureBox4_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox23.Text = itemPicker.ItemIndex.ToString();
    }

    private void pictureBox4_MouseMove(object sender, MouseEventArgs e)
    {
      this.pictureBox4.Size = new Size(26, 26);
    }

    private void pictureBox4_MouseLeave(object sender, EventArgs e)
    {
      this.pictureBox4.Size = new Size(22, 22);
    }

    private void pictureBox5_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox24.Text = itemPicker.ItemIndex.ToString();
    }

    private void pictureBox5_MouseMove(object sender, MouseEventArgs e)
    {
      this.pictureBox5.Size = new Size(26, 26);
    }

    private void pictureBox5_MouseLeave(object sender, EventArgs e)
    {
      this.pictureBox5.Size = new Size(22, 22);
    }

    private void pictureBox6_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox25.Text = itemPicker.ItemIndex.ToString();
    }

    private void pictureBox6_MouseMove(object sender, MouseEventArgs e)
    {
      this.pictureBox6.Size = new Size(26, 26);
    }

    private void pictureBox6_MouseLeave(object sender, EventArgs e)
    {
      this.pictureBox6.Size = new Size(22, 22);
    }

    private void pictureBox7_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox26.Text = itemPicker.ItemIndex.ToString();
    }

    private void pictureBox7_MouseMove(object sender, MouseEventArgs e)
    {
      this.pictureBox7.Size = new Size(26, 26);
    }

    private void pictureBox7_MouseLeave(object sender, EventArgs e)
    {
      this.pictureBox7.Size = new Size(22, 22);
    }

    private void pictureBox8_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox27.Text = itemPicker.ItemIndex.ToString();
    }

    private void pictureBox8_MouseMove(object sender, MouseEventArgs e)
    {
      this.pictureBox8.Size = new Size(26, 26);
    }

    private void pictureBox8_MouseLeave(object sender, EventArgs e)
    {
      this.pictureBox8.Size = new Size(22, 22);
    }

    private void pictureBox9_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox28.Text = itemPicker.ItemIndex.ToString();
    }

    private void pictureBox9_MouseMove(object sender, MouseEventArgs e)
    {
      this.pictureBox9.Size = new Size(26, 26);
    }

    private void pictureBox9_MouseLeave(object sender, EventArgs e)
    {
      this.pictureBox9.Size = new Size(22, 22);
    }

    private void pictureBox10_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox29.Text = itemPicker.ItemIndex.ToString();
    }

    private void pictureBox10_MouseMove(object sender, MouseEventArgs e)
    {
      this.pictureBox10.Size = new Size(26, 26);
    }

    private void pictureBox10_MouseLeave(object sender, EventArgs e)
    {
      this.pictureBox10.Size = new Size(22, 22);
    }

    private void pictureBox11_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox30.Text = itemPicker.ItemIndex.ToString();
    }

    private void pictureBox11_MouseMove(object sender, MouseEventArgs e)
    {
      this.pictureBox11.Size = new Size(26, 26);
    }

    private void pictureBox11_MouseLeave(object sender, EventArgs e)
    {
      this.pictureBox11.Size = new Size(22, 22);
    }

    private void pictureBox12_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox31.Text = itemPicker.ItemIndex.ToString();
    }

    private void pictureBox12_MouseMove(object sender, MouseEventArgs e)
    {
      this.pictureBox12.Size = new Size(26, 26);
    }

    private void pictureBox12_MouseLeave(object sender, EventArgs e)
    {
      this.pictureBox12.Size = new Size(22, 22);
    }

    private void pictureBox13_Click(object sender, EventArgs e)
    {
      RareOptSearch rareOptSearch = new RareOptSearch();
      if (rareOptSearch.ShowDialog() != DialogResult.OK)
        return;
      this.textBox60.Text = rareOptSearch.varf3;
    }

    private void pictureBox13_MouseMove(object sender, MouseEventArgs e)
    {
      this.pictureBox13.Size = new Size(26, 26);
    }

    private void pictureBox13_MouseLeave(object sender, EventArgs e)
    {
      this.pictureBox13.Size = new Size(22, 22);
    }

    private void pictureBox14_Click(object sender, EventArgs e)
    {
      RareOptSearch rareOptSearch = new RareOptSearch();
      if (rareOptSearch.ShowDialog() != DialogResult.OK)
        return;
      this.textBox61.Text = rareOptSearch.varf3;
    }

    private void pictureBox14_MouseMove(object sender, MouseEventArgs e)
    {
      this.pictureBox14.Size = new Size(26, 26);
    }

    private void pictureBox14_MouseLeave(object sender, EventArgs e)
    {
      this.pictureBox14.Size = new Size(22, 22);
    }

    private void pictureBox15_Click(object sender, EventArgs e)
    {
      RareOptSearch rareOptSearch = new RareOptSearch();
      if (rareOptSearch.ShowDialog() != DialogResult.OK)
        return;
      this.textBox62.Text = rareOptSearch.varf3;
    }

    private void pictureBox15_MouseMove(object sender, MouseEventArgs e)
    {
      this.pictureBox15.Size = new Size(26, 26);
    }

    private void pictureBox15_MouseLeave(object sender, EventArgs e)
    {
      this.pictureBox15.Size = new Size(22, 22);
    }

    private void pictureBox16_Click(object sender, EventArgs e)
    {
      RareOptSearch rareOptSearch = new RareOptSearch();
      if (rareOptSearch.ShowDialog() != DialogResult.OK)
        return;
      this.textBox63.Text = rareOptSearch.varf3;
    }

    private void pictureBox16_MouseMove(object sender, MouseEventArgs e)
    {
      this.pictureBox16.Size = new Size(26, 26);
    }

    private void pictureBox16_MouseLeave(object sender, EventArgs e)
    {
      this.pictureBox16.Size = new Size(22, 22);
    }

    private void pictureBox17_Click(object sender, EventArgs e)
    {
      RareOptSearch rareOptSearch = new RareOptSearch();
      if (rareOptSearch.ShowDialog() != DialogResult.OK)
        return;
      this.textBox64.Text = rareOptSearch.varf3;
    }

    private void pictureBox17_MouseMove(object sender, MouseEventArgs e)
    {
      this.pictureBox17.Size = new Size(26, 26);
    }

    private void pictureBox17_MouseLeave(object sender, EventArgs e)
    {
      this.pictureBox17.Size = new Size(22, 22);
    }

    private void pictureBox18_Click(object sender, EventArgs e)
    {
      RareOptSearch rareOptSearch = new RareOptSearch();
      if (rareOptSearch.ShowDialog() != DialogResult.OK)
        return;
      this.textBox65.Text = rareOptSearch.varf3;
    }

    private void pictureBox18_MouseMove(object sender, MouseEventArgs e)
    {
      this.pictureBox18.Size = new Size(26, 26);
    }

    private void pictureBox18_MouseLeave(object sender, EventArgs e)
    {
      this.pictureBox18.Size = new Size(22, 22);
    }

    private void pictureBox19_Click(object sender, EventArgs e)
    {
      RareOptSearch rareOptSearch = new RareOptSearch();
      if (rareOptSearch.ShowDialog() != DialogResult.OK)
        return;
      this.textBox66.Text = rareOptSearch.varf3;
    }

    private void pictureBox19_MouseMove(object sender, MouseEventArgs e)
    {
      this.pictureBox19.Size = new Size(26, 26);
    }

    private void pictureBox19_MouseLeave(object sender, EventArgs e)
    {
      this.pictureBox19.Size = new Size(22, 22);
    }

    private void pictureBox20_Click(object sender, EventArgs e)
    {
      RareOptSearch rareOptSearch = new RareOptSearch();
      if (rareOptSearch.ShowDialog() != DialogResult.OK)
        return;
      this.textBox67.Text = rareOptSearch.varf3;
    }

    private void pictureBox20_MouseMove(object sender, MouseEventArgs e)
    {
      this.pictureBox20.Size = new Size(26, 26);
    }

    private void pictureBox20_MouseLeave(object sender, EventArgs e)
    {
      this.pictureBox20.Size = new Size(22, 22);
    }

    private void pictureBox21_Click(object sender, EventArgs e)
    {
      RareOptSearch rareOptSearch = new RareOptSearch();
      if (rareOptSearch.ShowDialog() != DialogResult.OK)
        return;
      this.textBox68.Text = rareOptSearch.varf3;
    }

    private void pictureBox21_MouseMove(object sender, MouseEventArgs e)
    {
      this.pictureBox21.Size = new Size(26, 26);
    }

    private void pictureBox21_MouseLeave(object sender, EventArgs e)
    {
      this.pictureBox21.Size = new Size(22, 22);
    }

    private void pictureBox22_Click(object sender, EventArgs e)
    {
      RareOptSearch rareOptSearch = new RareOptSearch();
      if (rareOptSearch.ShowDialog() != DialogResult.OK)
        return;
      this.textBox69.Text = rareOptSearch.varf3;
    }

    private void pictureBox22_MouseMove(object sender, MouseEventArgs e)
    {
      this.pictureBox22.Size = new Size(26, 26);
    }

    private void pictureBox22_MouseLeave(object sender, EventArgs e)
    {
      this.pictureBox22.Size = new Size(22, 22);
    }

    private void pictureBox23_Click(object sender, EventArgs e)
    {
      FlagBuilder flagBuilder = new FlagBuilder();
      if (this.Episode == "EP4")
      {
        flagBuilder.flagBig = Convert.ToInt64(this.textBox8.Text);
        if (flagBuilder.ShowDialog() != DialogResult.OK)
          return;
        this.textBox8.Text = flagBuilder.flagBig.ToString();
      }
      else
      {
        flagBuilder.flagSmall = Convert.ToInt32(this.textBox8.Text);
        if (flagBuilder.ShowDialog() != DialogResult.OK)
          return;
        this.textBox8.Text = flagBuilder.flagSmall.ToString();
      }
    }

    private void pictureBox23_MouseMove_1(object sender, MouseEventArgs e)
    {
      this.pictureBox23.Size = new Size(26, 26);
    }

    private void pictureBox23_MouseLeave(object sender, EventArgs e)
    {
      this.pictureBox23.Size = new Size(19, 24);
    }

    private void comboBox24_SelectedIndexChanged(object sender, EventArgs e)
    {
    }

    private void comboBox25_SelectedIndexChanged(object sender, EventArgs e)
    {
    }

    private void textBox7_TextChanged(object sender, EventArgs e)
    {
    }

    private void checkedListBox2_SelectedIndexChanged(object sender, EventArgs e)
    {
      int num1 = 0;
      int num2 = 0;
      for (int index = 0; index < this.checkedListBox2.Items.Count; ++index)
      {
        if (this.checkedListBox2.GetItemChecked(index))
        {
          num1 += 1 << index;
          ++num2;
        }
      }
      this.mSortJob = num1.ToString();
      if (num2 == 0)
        this.mSortJob = "-1";
      this.LoadListBox();
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

    private void MakeLCModels(string SMCFile)
    {
      System.Collections.Generic.List<float> source1 = new System.Collections.Generic.List<float>();
      System.Collections.Generic.List<float> source2 = new System.Collections.Generic.List<float>();
      System.Collections.Generic.List<float> source3 = new System.Collections.Generic.List<float>();
      System.Collections.Generic.List<float> floatList1 = new System.Collections.Generic.List<float>();
      System.Collections.Generic.List<float> floatList2 = new System.Collections.Generic.List<float>();
      System.Collections.Generic.List<float> floatList3 = new System.Collections.Generic.List<float>();
      this._Models = new System.Collections.Generic.List<tMesh>();
      try
      {
        System.Collections.Generic.List<smcMesh> source4 = SMCReader.ReadFile(SMCFile);
        for (int index1 = 0; index1 < source4.Count<smcMesh>(); ++index1)
        {
          if (LCMeshReader.ReadFile(source4[index1].FileName))
          {
            tMeshContainer pMesh = LCMeshReader.pMesh;
            source1.Add(((IEnumerable<tVertex3f>) pMesh.Vertices).Max<tVertex3f>((Func<tVertex3f, float>) (p => p.X)));
            source2.Add(((IEnumerable<tVertex3f>) pMesh.Vertices).Max<tVertex3f>((Func<tVertex3f, float>) (p => p.Y)));
            source3.Add(((IEnumerable<tVertex3f>) pMesh.Vertices).Max<tVertex3f>((Func<tVertex3f, float>) (p => p.Z)));
            floatList1.Add(((IEnumerable<tVertex3f>) pMesh.Vertices).Min<tVertex3f>((Func<tVertex3f, float>) (p => p.X)));
            floatList2.Add(((IEnumerable<tVertex3f>) pMesh.Vertices).Min<tVertex3f>((Func<tVertex3f, float>) (p => p.Y)));
            floatList3.Add(((IEnumerable<tVertex3f>) pMesh.Vertices).Min<tVertex3f>((Func<tVertex3f, float>) (p => p.Z)));
            for (int index2 = 0; index2 < ((IEnumerable<tMeshObject>) pMesh.Objects).Count<tMeshObject>(); ++index2)
            {
              int toVert = (int) pMesh.Objects[index2].ToVert;
              int faceCount = (int) pMesh.Objects[index2].FaceCount;
              short[] faces = pMesh.Objects[index2].GetFaces();
              CustomVertex.PositionNormalTextured[] positionNormalTexturedArray = new CustomVertex.PositionNormalTextured[toVert];
              int fromVert = (int) pMesh.Objects[index2].FromVert;
              for (int index3 = 0; (long) index3 < (long) pMesh.Objects[index2].ToVert; ++index3)
              {
                positionNormalTexturedArray[index3].Position = new Vector3(pMesh.Vertices[fromVert].X, pMesh.Vertices[fromVert].Y, pMesh.Vertices[fromVert].Z);
                positionNormalTexturedArray[index3].Normal = new Vector3(pMesh.Normals[fromVert].X, pMesh.Normals[fromVert].Y, pMesh.Normals[fromVert].Z);
                try
                {
                  positionNormalTexturedArray[index3].Texture = new Vector2(pMesh.UVMaps[0].Coords[fromVert].U, pMesh.UVMaps[0].Coords[fromVert].V);
                }
                catch
                {
                  positionNormalTexturedArray[index3].Texture = new Vector2(0.0f, 0.0f);
                }
                ++fromVert;
              }
              VertexBuffer vertexBuffer = new VertexBuffer(this._Device, ((IEnumerable<CustomVertex.PositionNormalTextured>) positionNormalTexturedArray).Count<CustomVertex.PositionNormalTextured>() * 32, Usage.None, VertexFormat.PositionNormal | VertexFormat.Texture1, Pool.Default);
              Mesh mesh = new Mesh(this._Device, ((IEnumerable<short>) faces).Count<short>() / 3, ((IEnumerable<CustomVertex.PositionNormalTextured>) positionNormalTexturedArray).Count<CustomVertex.PositionNormalTextured>(), MeshFlags.Managed, VertexFormat.PositionNormal | VertexFormat.Texture1);
              DataStream dataStream1;
              using (dataStream1 = mesh.VertexBuffer.Lock(0, ((IEnumerable<CustomVertex.PositionNormalTextured>) positionNormalTexturedArray).Count<CustomVertex.PositionNormalTextured>() * 32, LockFlags.None))
              {
                dataStream1.WriteRange<CustomVertex.PositionNormalTextured>(positionNormalTexturedArray);
                mesh.VertexBuffer.Unlock();
              }
              DataStream dataStream2;
              using (dataStream2 = mesh.IndexBuffer.Lock(0, ((IEnumerable<short>) faces).Count<short>() * 2, LockFlags.None))
              {
                dataStream2.WriteRange<short>(faces);
                mesh.IndexBuffer.Unlock();
              }
              if (((IEnumerable<tMeshJointWeights>) pMesh.Weights).Count<tMeshJointWeights>() != 0)
              {
                string[] strArray = new string[((IEnumerable<tMeshJointWeights>) pMesh.Weights).Count<tMeshJointWeights>()];
                System.Collections.Generic.List<int>[] source5 = new System.Collections.Generic.List<int>[((IEnumerable<tMeshJointWeights>) pMesh.Weights).Count<tMeshJointWeights>()];
                System.Collections.Generic.List<float>[] floatListArray = new System.Collections.Generic.List<float>[((IEnumerable<tMeshJointWeights>) pMesh.Weights).Count<tMeshJointWeights>()];
                for (int index4 = 0; index4 < ((IEnumerable<tMeshJointWeights>) pMesh.Weights).Count<tMeshJointWeights>(); ++index4)
                {
                  strArray[index4] = this._Enc.GetString(pMesh.Weights[index4].JointName);
                  source5[index4] = new System.Collections.Generic.List<int>();
                  floatListArray[index4] = new System.Collections.Generic.List<float>();
                  for (int index5 = 0; index5 < ((IEnumerable<tMeshWeightsMap>) pMesh.Weights[index4].WeightsMap).Count<tMeshWeightsMap>(); ++index5)
                  {
                    source5[index4].Add(pMesh.Weights[index4].WeightsMap[index5].Index);
                    floatListArray[index4].Add(pMesh.Weights[index4].WeightsMap[index5].Weight);
                  }
                }
                mesh.SkinInfo = new SkinInfo(((IEnumerable<CustomVertex.PositionNormalTextured>) positionNormalTexturedArray).Count<CustomVertex.PositionNormalTextured>(), VertexFormat.PositionNormal | VertexFormat.Texture1, (int) pMesh.HeaderInfo.JointCount);
                for (int bone = 0; bone < ((IEnumerable<System.Collections.Generic.List<int>>) source5).Count<System.Collections.Generic.List<int>>(); ++bone)
                {
                  mesh.SkinInfo.SetBoneName(bone, strArray[bone]);
                  mesh.SkinInfo.SetBoneInfluence(bone, source5[bone].ToArray(), floatListArray[bone].ToArray());
                }
              }
              mesh.GenerateAdjacency(0.5f);
              mesh.ComputeNormals();
              Texture texture = (Texture) null;
              string objName = this._Enc.GetString(pMesh.Objects[index2].Textures[0].InternalName);
              int index6 = source4[index1].Object.FindIndex((Predicate<smcObject>) (x => x.Name.Equals(objName)));
              if (index6 != -1)
                texture = this.GetTextureFromFile(source4[index1].Object[index6].Texture);
              this._Models.Add(new tMesh(mesh, texture));
            }
          }
        }
      }
      catch
      {
      }
      try
      {
        this._Zoom = ((IEnumerable<float>) new float[3]
        {
          source1.Max(),
          source2.Max(),
          source3.Max()
        }).Max() * 3f;
      }
      catch
      {
      }
      this.slideZoom.Value = (int) this._Zoom * 100;
    }

    private void timer1_Tick(object sender, EventArgs e) => this.Render();

    private void textBox95_TextChanged(object sender, EventArgs e)
    {
      this._SortAboveLevel = this.textBox95.Text;
      this.LoadListBox();
    }

    private void button27_Click(object sender, EventArgs e)
    {
    }

    private void textBox70_TextChanged(object sender, EventArgs e)
    {
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
      this.menuStrip1 = new MenuStrip();
      this.fileExportToolStripMenuItem = new ToolStripMenuItem();
      this.exportlodToolStripMenuItem = new ToolStripMenuItem();
      this.exportStrItemlodToolStripMenuItem = new ToolStripMenuItem();
      this.groupBox3 = new GroupBox();
      this.button4 = new Button();
      this.button3 = new Button();
      this.button1 = new Button();
      this.listBox1 = new ListBox();
      this.tabControl1 = new TabControl();
      this.tabPage1 = new TabPage();
      this.groupBox12 = new GroupBox();
      this.textBox93 = new TextBox();
      this.textBox94 = new TextBox();
      this.label93 = new Label();
      this.label94 = new Label();
      this.textBox84 = new TextBox();
      this.label84 = new Label();
      this.textBox83 = new TextBox();
      this.label83 = new Label();
      this.textBox51 = new TextBox();
      this.textBox59 = new TextBox();
      this.label51 = new Label();
      this.label59 = new Label();
      this.groupBox20 = new GroupBox();
      this.chk3D = new CheckBox();
      this.slideLeftRight = new TrackBar();
      this.slideUpDown = new TrackBar();
      this.slideZoom = new TrackBar();
      this.panel3DView = new Panel();
      this.groupBox19 = new GroupBox();
      this.textBox90 = new TextBox();
      this.label90 = new Label();
      this.textBox85 = new TextBox();
      this.label85 = new Label();
      this.textBox89 = new TextBox();
      this.label89 = new Label();
      this.textBox86 = new TextBox();
      this.label86 = new Label();
      this.textBox88 = new TextBox();
      this.label88 = new Label();
      this.textBox87 = new TextBox();
      this.label87 = new Label();
      this.groupBox16 = new GroupBox();
      this.label92 = new Label();
      this.textBox92 = new TextBox();
      this.label91 = new Label();
      this.textBox91 = new TextBox();
      this.groupBox14 = new GroupBox();
      this.label82 = new Label();
      this.textBox82 = new TextBox();
      this.label81 = new Label();
      this.textBox81 = new TextBox();
      this.label80 = new Label();
      this.textBox80 = new TextBox();
      this.groupBox11 = new GroupBox();
      this.textBox58 = new TextBox();
      this.label58 = new Label();
      this.textBox57 = new TextBox();
      this.label57 = new Label();
      this.groupBox10 = new GroupBox();
      this.textBox55 = new TextBox();
      this.label56 = new Label();
      this.label55 = new Label();
      this.textBox54 = new TextBox();
      this.textBox56 = new TextBox();
      this.label54 = new Label();
      this.textBox53 = new TextBox();
      this.label53 = new Label();
      this.textBox52 = new TextBox();
      this.label52 = new Label();
      this.groupBox9 = new GroupBox();
      this.linkLabel1 = new LinkLabel();
      this.pictureBox1 = new PictureBox();
      this.textBox50 = new TextBox();
      this.label50 = new Label();
      this.textBox48 = new TextBox();
      this.label48 = new Label();
      this.label49 = new Label();
      this.textBox49 = new TextBox();
      this.groupBox6 = new GroupBox();
      this.textBox21 = new TextBox();
      this.textBox19 = new TextBox();
      this.label21 = new Label();
      this.label19 = new Label();
      this.textBox16 = new TextBox();
      this.label16 = new Label();
      this.label18 = new Label();
      this.textBox17 = new TextBox();
      this.textBox18 = new TextBox();
      this.label17 = new Label();
      this.groupBox4 = new GroupBox();
      this.textBox15 = new TextBox();
      this.label15 = new Label();
      this.textBox10 = new TextBox();
      this.label11 = new Label();
      this.label14 = new Label();
      this.textBox11 = new TextBox();
      this.textBox14 = new TextBox();
      this.label12 = new Label();
      this.label13 = new Label();
      this.textBox13 = new TextBox();
      this.groupBox2 = new GroupBox();
      this.pictureBox23 = new PictureBox();
      this.textBox7 = new TextBox();
      this.label8 = new Label();
      this.comboBox4 = new ComboBox();
      this.checkedListBox1 = new CheckedListBox();
      this.comboBox2 = new ComboBox();
      this.comboBox1 = new ComboBox();
      this.label20 = new Label();
      this.label9 = new Label();
      this.textBox20 = new TextBox();
      this.label10 = new Label();
      this.textBox8 = new TextBox();
      this.textBox2 = new TextBox();
      this.textBox9 = new TextBox();
      this.label3 = new Label();
      this.textBox3 = new TextBox();
      this.label2 = new Label();
      this.groupBox1 = new GroupBox();
      this.checkBox1 = new CheckBox();
      this.label47 = new Label();
      this.textBox46 = new TextBox();
      this.textBox47 = new TextBox();
      this.label46 = new Label();
      this.label6 = new Label();
      this.textBox1 = new TextBox();
      this.label5 = new Label();
      this.label1 = new Label();
      this.textBox5 = new TextBox();
      this.textBox6 = new TextBox();
      this.tabPage2 = new TabPage();
      this.groupBox7 = new GroupBox();
      this.pictureBox12 = new PictureBox();
      this.pictureBox11 = new PictureBox();
      this.pictureBox10 = new PictureBox();
      this.pictureBox9 = new PictureBox();
      this.pictureBox8 = new PictureBox();
      this.pictureBox7 = new PictureBox();
      this.pictureBox6 = new PictureBox();
      this.pictureBox5 = new PictureBox();
      this.pictureBox4 = new PictureBox();
      this.pictureBox3 = new PictureBox();
      this.textBox36 = new TextBox();
      this.textBox27 = new TextBox();
      this.textBox39 = new TextBox();
      this.label40 = new Label();
      this.textBox31 = new TextBox();
      this.label28 = new Label();
      this.textBox26 = new TextBox();
      this.label27 = new Label();
      this.label39 = new Label();
      this.label34 = new Label();
      this.textBox40 = new TextBox();
      this.label22 = new Label();
      this.textBox28 = new TextBox();
      this.textBox33 = new TextBox();
      this.textBox38 = new TextBox();
      this.label41 = new Label();
      this.textBox34 = new TextBox();
      this.label29 = new Label();
      this.textBox22 = new TextBox();
      this.label26 = new Label();
      this.label33 = new Label();
      this.label38 = new Label();
      this.textBox41 = new TextBox();
      this.label35 = new Label();
      this.textBox29 = new TextBox();
      this.label23 = new Label();
      this.textBox25 = new TextBox();
      this.textBox32 = new TextBox();
      this.textBox37 = new TextBox();
      this.textBox35 = new TextBox();
      this.label30 = new Label();
      this.textBox23 = new TextBox();
      this.label25 = new Label();
      this.label32 = new Label();
      this.label37 = new Label();
      this.label36 = new Label();
      this.textBox30 = new TextBox();
      this.label24 = new Label();
      this.textBox24 = new TextBox();
      this.label31 = new Label();
      this.groupBox8 = new GroupBox();
      this.textBox45 = new TextBox();
      this.label45 = new Label();
      this.textBox44 = new TextBox();
      this.label44 = new Label();
      this.textBox43 = new TextBox();
      this.label43 = new Label();
      this.textBox42 = new TextBox();
      this.label42 = new Label();
      this.tabPage3 = new TabPage();
      this.groupBox17 = new GroupBox();
      this.comboBox23 = new ComboBox();
      this.comboBox22 = new ComboBox();
      this.comboBox21 = new ComboBox();
      this.comboBox20 = new ComboBox();
      this.comboBox19 = new ComboBox();
      this.comboBox18 = new ComboBox();
      this.comboBox17 = new ComboBox();
      this.comboBox16 = new ComboBox();
      this.comboBox15 = new ComboBox();
      this.comboBox14 = new ComboBox();
      this.label104 = new Label();
      this.comboBox13 = new ComboBox();
      this.label103 = new Label();
      this.label102 = new Label();
      this.label101 = new Label();
      this.label100 = new Label();
      this.comboBox12 = new ComboBox();
      this.comboBox11 = new ComboBox();
      this.comboBox10 = new ComboBox();
      this.comboBox9 = new ComboBox();
      this.comboBox8 = new ComboBox();
      this.label99 = new Label();
      this.comboBox7 = new ComboBox();
      this.label98 = new Label();
      this.comboBox6 = new ComboBox();
      this.label97 = new Label();
      this.comboBox5 = new ComboBox();
      this.label96 = new Label();
      this.comboBox3 = new ComboBox();
      this.label95 = new Label();
      this.groupBox13 = new GroupBox();
      this.pictureBox22 = new PictureBox();
      this.pictureBox21 = new PictureBox();
      this.pictureBox20 = new PictureBox();
      this.pictureBox19 = new PictureBox();
      this.pictureBox18 = new PictureBox();
      this.pictureBox17 = new PictureBox();
      this.pictureBox16 = new PictureBox();
      this.pictureBox15 = new PictureBox();
      this.pictureBox14 = new PictureBox();
      this.pictureBox13 = new PictureBox();
      this.textBox79 = new TextBox();
      this.label79 = new Label();
      this.textBox78 = new TextBox();
      this.label78 = new Label();
      this.textBox77 = new TextBox();
      this.label77 = new Label();
      this.textBox76 = new TextBox();
      this.label76 = new Label();
      this.textBox75 = new TextBox();
      this.label75 = new Label();
      this.textBox74 = new TextBox();
      this.label74 = new Label();
      this.textBox73 = new TextBox();
      this.label73 = new Label();
      this.textBox72 = new TextBox();
      this.label72 = new Label();
      this.textBox71 = new TextBox();
      this.label71 = new Label();
      this.textBox70 = new TextBox();
      this.label70 = new Label();
      this.textBox69 = new TextBox();
      this.label69 = new Label();
      this.textBox68 = new TextBox();
      this.label68 = new Label();
      this.textBox67 = new TextBox();
      this.label67 = new Label();
      this.textBox66 = new TextBox();
      this.label66 = new Label();
      this.textBox65 = new TextBox();
      this.label65 = new Label();
      this.textBox64 = new TextBox();
      this.label64 = new Label();
      this.textBox63 = new TextBox();
      this.label63 = new Label();
      this.textBox62 = new TextBox();
      this.label62 = new Label();
      this.textBox61 = new TextBox();
      this.label61 = new Label();
      this.textBox60 = new TextBox();
      this.label60 = new Label();
      this.clbFlagTest = new CheckedListBox();
      this.textBox4 = new TextBox();
      this.label4 = new Label();
      this.button2 = new Button();
      this.toolTip1 = new ToolTip(this.components);
      this.groupBox18 = new GroupBox();
      this.textBox12 = new TextBox();
      this.label7 = new Label();
      this.groupBox5 = new GroupBox();
      this.label105 = new Label();
      this.textBox95 = new TextBox();
      this.checkedListBox2 = new CheckedListBox();
      this.timer1 = new Timer(this.components);
      this.menuStrip1.SuspendLayout();
      this.groupBox3.SuspendLayout();
      this.tabControl1.SuspendLayout();
      this.tabPage1.SuspendLayout();
      this.groupBox12.SuspendLayout();
      this.groupBox20.SuspendLayout();
      this.slideLeftRight.BeginInit();
      this.slideUpDown.BeginInit();
      this.slideZoom.BeginInit();
      this.groupBox19.SuspendLayout();
      this.groupBox16.SuspendLayout();
      this.groupBox14.SuspendLayout();
      this.groupBox11.SuspendLayout();
      this.groupBox10.SuspendLayout();
      this.groupBox9.SuspendLayout();
      ((ISupportInitialize) this.pictureBox1).BeginInit();
      this.groupBox6.SuspendLayout();
      this.groupBox4.SuspendLayout();
      this.groupBox2.SuspendLayout();
      ((ISupportInitialize) this.pictureBox23).BeginInit();
      this.groupBox1.SuspendLayout();
      this.tabPage2.SuspendLayout();
      this.groupBox7.SuspendLayout();
      ((ISupportInitialize) this.pictureBox12).BeginInit();
      ((ISupportInitialize) this.pictureBox11).BeginInit();
      ((ISupportInitialize) this.pictureBox10).BeginInit();
      ((ISupportInitialize) this.pictureBox9).BeginInit();
      ((ISupportInitialize) this.pictureBox8).BeginInit();
      ((ISupportInitialize) this.pictureBox7).BeginInit();
      ((ISupportInitialize) this.pictureBox6).BeginInit();
      ((ISupportInitialize) this.pictureBox5).BeginInit();
      ((ISupportInitialize) this.pictureBox4).BeginInit();
      ((ISupportInitialize) this.pictureBox3).BeginInit();
      this.groupBox8.SuspendLayout();
      this.tabPage3.SuspendLayout();
      this.groupBox17.SuspendLayout();
      this.groupBox13.SuspendLayout();
      ((ISupportInitialize) this.pictureBox22).BeginInit();
      ((ISupportInitialize) this.pictureBox21).BeginInit();
      ((ISupportInitialize) this.pictureBox20).BeginInit();
      ((ISupportInitialize) this.pictureBox19).BeginInit();
      ((ISupportInitialize) this.pictureBox18).BeginInit();
      ((ISupportInitialize) this.pictureBox17).BeginInit();
      ((ISupportInitialize) this.pictureBox16).BeginInit();
      ((ISupportInitialize) this.pictureBox15).BeginInit();
      ((ISupportInitialize) this.pictureBox14).BeginInit();
      ((ISupportInitialize) this.pictureBox13).BeginInit();
      this.groupBox18.SuspendLayout();
      this.groupBox5.SuspendLayout();
      this.SuspendLayout();
      this.menuStrip1.AllowMerge = false;
      this.menuStrip1.BackColor = SystemColors.ControlLightLight;
      this.menuStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.fileExportToolStripMenuItem
      });
      this.menuStrip1.Location = new Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new Size(1239, 24);
      this.menuStrip1.TabIndex = 0;
      this.menuStrip1.Text = "menuStrip1";
      this.fileExportToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[2]
      {
        (ToolStripItem) this.exportlodToolStripMenuItem,
        (ToolStripItem) this.exportStrItemlodToolStripMenuItem
      });
      this.fileExportToolStripMenuItem.Name = "fileExportToolStripMenuItem";
      this.fileExportToolStripMenuItem.Size = new Size(73, 20);
      this.fileExportToolStripMenuItem.Text = "File Export";
      this.exportlodToolStripMenuItem.Name = "exportlodToolStripMenuItem";
      this.exportlodToolStripMenuItem.Size = new Size(168, 22);
      this.exportlodToolStripMenuItem.Text = "Export itemAll.lod";
      this.exportlodToolStripMenuItem.Click += new EventHandler(this.exportlodToolStripMenuItem_Click);
      this.exportStrItemlodToolStripMenuItem.Name = "exportStrItemlodToolStripMenuItem";
      this.exportStrItemlodToolStripMenuItem.Size = new Size(168, 22);
      this.exportStrItemlodToolStripMenuItem.Text = "Export strItem.lod";
      this.exportStrItemlodToolStripMenuItem.Click += new EventHandler(this.exportStrItemlodToolStripMenuItem_Click);
      this.groupBox3.Controls.Add((Control) this.button4);
      this.groupBox3.Controls.Add((Control) this.button3);
      this.groupBox3.Controls.Add((Control) this.button1);
      this.groupBox3.Controls.Add((Control) this.listBox1);
      this.groupBox3.Location = new Point(12, 168);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Size = new Size(265, 535);
      this.groupBox3.TabIndex = 31;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "Items";
      this.button4.FlatStyle = FlatStyle.Flat;
      this.button4.Location = new Point(91, 501);
      this.button4.Name = "button4";
      this.button4.Size = new Size(91, 23);
      this.button4.TabIndex = 5;
      this.button4.Text = "Copy to new";
      this.button4.UseVisualStyleBackColor = true;
      this.button4.Click += new EventHandler(this.button4_Click);
      this.button3.FlatStyle = FlatStyle.Flat;
      this.button3.Location = new Point(188, 501);
      this.button3.Name = "button3";
      this.button3.Size = new Size(75, 23);
      this.button3.TabIndex = 4;
      this.button3.Text = "Delete Item";
      this.button3.UseVisualStyleBackColor = true;
      this.button3.Click += new EventHandler(this.button3_Click);
      this.button1.FlatStyle = FlatStyle.Flat;
      this.button1.Location = new Point(10, 501);
      this.button1.Name = "button1";
      this.button1.Size = new Size(75, 23);
      this.button1.TabIndex = 2;
      this.button1.Text = "Add Item";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.listBox1.FormattingEnabled = true;
      this.listBox1.Location = new Point(6, 19);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new Size(253, 459);
      this.listBox1.TabIndex = 1;
      this.listBox1.SelectedIndexChanged += new EventHandler(this.listBox1_SelectedIndexChanged);
      this.tabControl1.Controls.Add((Control) this.tabPage1);
      this.tabControl1.Controls.Add((Control) this.tabPage2);
      this.tabControl1.Controls.Add((Control) this.tabPage3);
      this.tabControl1.Location = new Point(283, 27);
      this.tabControl1.Name = "tabControl1";
      this.tabControl1.SelectedIndex = 0;
      this.tabControl1.Size = new Size(947, 636);
      this.tabControl1.TabIndex = 33;
      this.tabPage1.BorderStyle = BorderStyle.FixedSingle;
      this.tabPage1.Controls.Add((Control) this.groupBox12);
      this.tabPage1.Controls.Add((Control) this.groupBox20);
      this.tabPage1.Controls.Add((Control) this.groupBox19);
      this.tabPage1.Controls.Add((Control) this.groupBox16);
      this.tabPage1.Controls.Add((Control) this.groupBox14);
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
      this.tabPage1.Size = new Size(939, 610);
      this.tabPage1.TabIndex = 0;
      this.tabPage1.Text = "Basic";
      this.tabPage1.Click += new EventHandler(this.tabPage1_Click);
      this.groupBox12.Controls.Add((Control) this.textBox93);
      this.groupBox12.Controls.Add((Control) this.textBox94);
      this.groupBox12.Controls.Add((Control) this.label93);
      this.groupBox12.Controls.Add((Control) this.label94);
      this.groupBox12.Controls.Add((Control) this.textBox84);
      this.groupBox12.Controls.Add((Control) this.label84);
      this.groupBox12.Controls.Add((Control) this.textBox83);
      this.groupBox12.Controls.Add((Control) this.label83);
      this.groupBox12.Controls.Add((Control) this.textBox51);
      this.groupBox12.Controls.Add((Control) this.textBox59);
      this.groupBox12.Controls.Add((Control) this.label51);
      this.groupBox12.Controls.Add((Control) this.label59);
      this.groupBox12.Location = new Point(743, 9);
      this.groupBox12.Name = "groupBox12";
      this.groupBox12.Size = new Size(195, 226);
      this.groupBox12.TabIndex = 56;
      this.groupBox12.TabStop = false;
      this.groupBox12.Text = "Misc";
      this.textBox93.BorderStyle = BorderStyle.FixedSingle;
      this.textBox93.Location = new Point(111, 107);
      this.textBox93.Name = "textBox93";
      this.textBox93.Size = new Size(69, 20);
      this.textBox93.TabIndex = 59;
      this.textBox94.BorderStyle = BorderStyle.FixedSingle;
      this.textBox94.Location = new Point(111, 78);
      this.textBox94.Name = "textBox94";
      this.textBox94.Size = new Size(69, 20);
      this.textBox94.TabIndex = 55;
      this.label93.AutoSize = true;
      this.label93.Location = new Point(7, 112);
      this.label93.Name = "label93";
      this.label93.Size = new Size(53, 13);
      this.label93.TabIndex = 60;
      this.label93.Text = "Durability:";
      this.label94.AutoSize = true;
      this.label94.Location = new Point(7, 82);
      this.label94.Name = "label94";
      this.label94.Size = new Size(59, 13);
      this.label94.TabIndex = 56;
      this.label94.Text = "CastleWar:";
      this.textBox84.BorderStyle = BorderStyle.FixedSingle;
      this.textBox84.Location = new Point(111, 165);
      this.textBox84.Name = "textBox84";
      this.textBox84.Size = new Size(69, 20);
      this.textBox84.TabIndex = 53;
      this.label84.AutoSize = true;
      this.label84.Location = new Point(7, 170);
      this.label84.Name = "label84";
      this.label84.Size = new Size(87, 13);
      this.label84.TabIndex = 54;
      this.label84.Text = "QuestTriggerIDs:";
      this.textBox83.BorderStyle = BorderStyle.FixedSingle;
      this.textBox83.Location = new Point(111, 136);
      this.textBox83.Name = "textBox83";
      this.textBox83.Size = new Size(69, 20);
      this.textBox83.TabIndex = 51;
      this.label83.AutoSize = true;
      this.label83.Location = new Point(6, 140);
      this.label83.Name = "label83";
      this.label83.Size = new Size(99, 13);
      this.label83.TabIndex = 52;
      this.label83.Text = "QuestTriggerCount:";
      this.textBox51.BorderStyle = BorderStyle.FixedSingle;
      this.textBox51.Location = new Point(111, 49);
      this.textBox51.Name = "textBox51";
      this.textBox51.Size = new Size(69, 20);
      this.textBox51.TabIndex = 42;
      this.textBox59.BorderStyle = BorderStyle.FixedSingle;
      this.textBox59.Location = new Point(111, 20);
      this.textBox59.Name = "textBox59";
      this.textBox59.Size = new Size(69, 20);
      this.textBox59.TabIndex = 49;
      this.label51.AutoSize = true;
      this.label51.Location = new Point(6, 51);
      this.label51.Name = "label51";
      this.label51.Size = new Size(66, 13);
      this.label51.TabIndex = 43;
      this.label51.Text = "TodoDelete:";
      this.label59.AutoSize = true;
      this.label59.Location = new Point(7, 22);
      this.label59.Name = "label59";
      this.label59.Size = new Size(36, 13);
      this.label59.TabIndex = 50;
      this.label59.Text = "Fame:";
      this.groupBox20.Controls.Add((Control) this.chk3D);
      this.groupBox20.Controls.Add((Control) this.slideLeftRight);
      this.groupBox20.Controls.Add((Control) this.slideUpDown);
      this.groupBox20.Controls.Add((Control) this.slideZoom);
      this.groupBox20.Controls.Add((Control) this.panel3DView);
      this.groupBox20.Location = new Point(648, 289);
      this.groupBox20.Name = "groupBox20";
      this.groupBox20.Size = new Size(279, 313);
      this.groupBox20.TabIndex = 55;
      this.groupBox20.TabStop = false;
      this.groupBox20.Text = "3D View";
      this.chk3D.AutoSize = true;
      this.chk3D.Checked = true;
      this.chk3D.CheckState = CheckState.Checked;
      this.chk3D.FlatStyle = FlatStyle.Flat;
      this.chk3D.Location = new Point(180, 0);
      this.chk3D.Name = "chk3D";
      this.chk3D.Size = new Size(99, 17);
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
      this.slideUpDown.AutoSize = false;
      this.slideUpDown.Location = new Point(95, 284);
      this.slideUpDown.Maximum = 10000;
      this.slideUpDown.Minimum = -10000;
      this.slideUpDown.Name = "slideUpDown";
      this.slideUpDown.Size = new Size(85, 25);
      this.slideUpDown.TabIndex = 2;
      this.slideUpDown.TickStyle = TickStyle.None;
      this.slideZoom.AutoSize = false;
      this.slideZoom.Location = new Point(7, 284);
      this.slideZoom.Maximum = 10000;
      this.slideZoom.Minimum = -10000;
      this.slideZoom.Name = "slideZoom";
      this.slideZoom.Size = new Size(85, 25);
      this.slideZoom.TabIndex = 1;
      this.slideZoom.TickStyle = TickStyle.None;
      this.panel3DView.Location = new Point(7, 20);
      this.panel3DView.Name = "panel3DView";
      this.panel3DView.Size = new Size(266, 258);
      this.panel3DView.TabIndex = 0;
      this.panel3DView.Paint += new PaintEventHandler(this.panel3DView_Paint);
      this.groupBox19.Controls.Add((Control) this.textBox90);
      this.groupBox19.Controls.Add((Control) this.label90);
      this.groupBox19.Controls.Add((Control) this.textBox85);
      this.groupBox19.Controls.Add((Control) this.label85);
      this.groupBox19.Controls.Add((Control) this.textBox89);
      this.groupBox19.Controls.Add((Control) this.label89);
      this.groupBox19.Controls.Add((Control) this.textBox86);
      this.groupBox19.Controls.Add((Control) this.label86);
      this.groupBox19.Controls.Add((Control) this.textBox88);
      this.groupBox19.Controls.Add((Control) this.label88);
      this.groupBox19.Controls.Add((Control) this.textBox87);
      this.groupBox19.Controls.Add((Control) this.label87);
      this.groupBox19.Location = new Point(495, 241);
      this.groupBox19.Name = "groupBox19";
      this.groupBox19.Size = new Size(147, 180);
      this.groupBox19.TabIndex = 54;
      this.groupBox19.TabStop = false;
      this.groupBox19.Text = "Origin";
      this.textBox90.BorderStyle = BorderStyle.FixedSingle;
      this.textBox90.Location = new Point(73, 150);
      this.textBox90.Name = "textBox90";
      this.textBox90.Size = new Size(61, 20);
      this.textBox90.TabIndex = 52;
      this.label90.AutoSize = true;
      this.label90.Location = new Point(5, 153);
      this.label90.Name = "label90";
      this.label90.Size = new Size(57, 13);
      this.label90.TabIndex = 53;
      this.label90.Text = "Variation6:";
      this.textBox85.BorderStyle = BorderStyle.FixedSingle;
      this.textBox85.Location = new Point(73, 19);
      this.textBox85.Name = "textBox85";
      this.textBox85.Size = new Size(61, 20);
      this.textBox85.TabIndex = 42;
      this.label85.AutoSize = true;
      this.label85.Location = new Point(5, 22);
      this.label85.Name = "label85";
      this.label85.Size = new Size(57, 13);
      this.label85.TabIndex = 43;
      this.label85.Text = "Variation1:";
      this.textBox89.BorderStyle = BorderStyle.FixedSingle;
      this.textBox89.Location = new Point(73, 124);
      this.textBox89.Name = "textBox89";
      this.textBox89.Size = new Size(61, 20);
      this.textBox89.TabIndex = 50;
      this.label89.AutoSize = true;
      this.label89.Location = new Point(5, (int) sbyte.MaxValue);
      this.label89.Name = "label89";
      this.label89.Size = new Size(57, 13);
      this.label89.TabIndex = 51;
      this.label89.Text = "Variation5:";
      this.textBox86.BorderStyle = BorderStyle.FixedSingle;
      this.textBox86.Location = new Point(73, 46);
      this.textBox86.Name = "textBox86";
      this.textBox86.Size = new Size(61, 20);
      this.textBox86.TabIndex = 44;
      this.label86.AutoSize = true;
      this.label86.Location = new Point(5, 48);
      this.label86.Name = "label86";
      this.label86.Size = new Size(57, 13);
      this.label86.TabIndex = 45;
      this.label86.Text = "Variation2:";
      this.textBox88.BorderStyle = BorderStyle.FixedSingle;
      this.textBox88.Location = new Point(73, 98);
      this.textBox88.Name = "textBox88";
      this.textBox88.Size = new Size(61, 20);
      this.textBox88.TabIndex = 48;
      this.label88.AutoSize = true;
      this.label88.Location = new Point(5, 102);
      this.label88.Name = "label88";
      this.label88.Size = new Size(57, 13);
      this.label88.TabIndex = 49;
      this.label88.Text = "Variation4:";
      this.textBox87.BorderStyle = BorderStyle.FixedSingle;
      this.textBox87.Location = new Point(73, 72);
      this.textBox87.Name = "textBox87";
      this.textBox87.Size = new Size(61, 20);
      this.textBox87.TabIndex = 46;
      this.label87.AutoSize = true;
      this.label87.Location = new Point(5, 75);
      this.label87.Name = "label87";
      this.label87.Size = new Size(57, 13);
      this.label87.TabIndex = 47;
      this.label87.Text = "Variation3:";
      this.groupBox16.Controls.Add((Control) this.label92);
      this.groupBox16.Controls.Add((Control) this.textBox92);
      this.groupBox16.Controls.Add((Control) this.label91);
      this.groupBox16.Controls.Add((Control) this.textBox91);
      this.groupBox16.Location = new Point(12, 535);
      this.groupBox16.Name = "groupBox16";
      this.groupBox16.Size = new Size(135, 67);
      this.groupBox16.TabIndex = 53;
      this.groupBox16.TabStop = false;
      this.groupBox16.Text = "RvR";
      this.label92.AutoSize = true;
      this.label92.Location = new Point(13, 42);
      this.label92.Name = "label92";
      this.label92.Size = new Size(39, 13);
      this.label92.TabIndex = 58;
      this.label92.Text = "Grade:";
      this.textBox92.BorderStyle = BorderStyle.FixedSingle;
      this.textBox92.Location = new Point(56, 40);
      this.textBox92.Name = "textBox92";
      this.textBox92.Size = new Size(64, 20);
      this.textBox92.TabIndex = 57;
      this.label91.AutoSize = true;
      this.label91.Location = new Point(13, 16);
      this.label91.Name = "label91";
      this.label91.Size = new Size(37, 13);
      this.label91.TabIndex = 56;
      this.label91.Text = "Value:";
      this.textBox91.BorderStyle = BorderStyle.FixedSingle;
      this.textBox91.Location = new Point(56, 14);
      this.textBox91.Name = "textBox91";
      this.textBox91.Size = new Size(64, 20);
      this.textBox91.TabIndex = 55;
      this.groupBox14.Controls.Add((Control) this.label82);
      this.groupBox14.Controls.Add((Control) this.textBox82);
      this.groupBox14.Controls.Add((Control) this.label81);
      this.groupBox14.Controls.Add((Control) this.textBox81);
      this.groupBox14.Controls.Add((Control) this.label80);
      this.groupBox14.Controls.Add((Control) this.textBox80);
      this.groupBox14.Location = new Point(200, 241);
      this.groupBox14.Name = "groupBox14";
      this.groupBox14.Size = new Size(282, 100);
      this.groupBox14.TabIndex = 52;
      this.groupBox14.TabStop = false;
      this.groupBox14.Text = "Item Special Effects";
      this.label82.AutoSize = true;
      this.label82.Location = new Point(6, 77);
      this.label82.Name = "label82";
      this.label82.Size = new Size(50, 13);
      this.label82.TabIndex = 58;
      this.label82.Text = "Damage:";
      this.textBox82.BorderStyle = BorderStyle.FixedSingle;
      this.textBox82.Location = new Point(63, 74);
      this.textBox82.Name = "textBox82";
      this.textBox82.Size = new Size(204, 20);
      this.textBox82.TabIndex = 57;
      this.label81.AutoSize = true;
      this.label81.Location = new Point(6, 49);
      this.label81.Name = "label81";
      this.label81.Size = new Size(41, 13);
      this.label81.TabIndex = 56;
      this.label81.Text = "Attack:";
      this.textBox81.BorderStyle = BorderStyle.FixedSingle;
      this.textBox81.Location = new Point(63, 46);
      this.textBox81.Name = "textBox81";
      this.textBox81.Size = new Size(204, 20);
      this.textBox81.TabIndex = 55;
      this.label80.AutoSize = true;
      this.label80.Location = new Point(6, 22);
      this.label80.Name = "label80";
      this.label80.Size = new Size(43, 13);
      this.label80.TabIndex = 54;
      this.label80.Text = "Normal:";
      this.textBox80.BorderStyle = BorderStyle.FixedSingle;
      this.textBox80.Location = new Point(63, 19);
      this.textBox80.Name = "textBox80";
      this.textBox80.Size = new Size(204, 20);
      this.textBox80.TabIndex = 53;
      this.groupBox11.Controls.Add((Control) this.textBox58);
      this.groupBox11.Controls.Add((Control) this.label58);
      this.groupBox11.Controls.Add((Control) this.textBox57);
      this.groupBox11.Controls.Add((Control) this.label57);
      this.groupBox11.Location = new Point(6, 462);
      this.groupBox11.Name = "groupBox11";
      this.groupBox11.Size = new Size(215, 66);
      this.groupBox11.TabIndex = 48;
      this.groupBox11.TabStop = false;
      this.groupBox11.Text = "Common RareOption";
      this.textBox58.BorderStyle = BorderStyle.FixedSingle;
      this.textBox58.Location = new Point(153, 30);
      this.textBox58.Name = "textBox58";
      this.textBox58.Size = new Size(53, 20);
      this.textBox58.TabIndex = 49;
      this.label58.AutoSize = true;
      this.label58.Location = new Point(105, 32);
      this.label58.Name = "label58";
      this.label58.Size = new Size(33, 13);
      this.label58.TabIndex = 50;
      this.label58.Text = "Rate:";
      this.textBox57.BorderStyle = BorderStyle.FixedSingle;
      this.textBox57.Location = new Point(43, 30);
      this.textBox57.Name = "textBox57";
      this.textBox57.Size = new Size(53, 20);
      this.textBox57.TabIndex = 46;
      this.label57.AutoSize = true;
      this.label57.Location = new Point(6, 32);
      this.label57.Name = "label57";
      this.label57.Size = new Size(21, 13);
      this.label57.TabIndex = 47;
      this.label57.Text = "ID:";
      this.groupBox10.Controls.Add((Control) this.textBox55);
      this.groupBox10.Controls.Add((Control) this.label56);
      this.groupBox10.Controls.Add((Control) this.label55);
      this.groupBox10.Controls.Add((Control) this.textBox54);
      this.groupBox10.Controls.Add((Control) this.textBox56);
      this.groupBox10.Controls.Add((Control) this.label54);
      this.groupBox10.Controls.Add((Control) this.textBox53);
      this.groupBox10.Controls.Add((Control) this.label53);
      this.groupBox10.Controls.Add((Control) this.textBox52);
      this.groupBox10.Controls.Add((Control) this.label52);
      this.groupBox10.Location = new Point(361, 348);
      this.groupBox10.Name = "groupBox10";
      this.groupBox10.Size = new Size(128, 180);
      this.groupBox10.TabIndex = 41;
      this.groupBox10.TabStop = false;
      this.groupBox10.Text = "Random Settings";
      this.textBox55.BorderStyle = BorderStyle.FixedSingle;
      this.textBox55.Location = new Point(69, 98);
      this.textBox55.Name = "textBox55";
      this.textBox55.Size = new Size(53, 20);
      this.textBox55.TabIndex = 50;
      this.label56.AutoSize = true;
      this.label56.Location = new Point(13, 126);
      this.label56.Name = "label56";
      this.label56.Size = new Size(32, 13);
      this.label56.TabIndex = 45;
      this.label56.Text = "Set4:";
      this.label55.AutoSize = true;
      this.label55.Location = new Point(13, 100);
      this.label55.Name = "label55";
      this.label55.Size = new Size(32, 13);
      this.label55.TabIndex = 51;
      this.label55.Text = "Set3:";
      this.textBox54.BorderStyle = BorderStyle.FixedSingle;
      this.textBox54.Location = new Point(69, 72);
      this.textBox54.Name = "textBox54";
      this.textBox54.Size = new Size(53, 20);
      this.textBox54.TabIndex = 48;
      this.textBox56.BorderStyle = BorderStyle.FixedSingle;
      this.textBox56.Location = new Point(69, 124);
      this.textBox56.Name = "textBox56";
      this.textBox56.Size = new Size(53, 20);
      this.textBox56.TabIndex = 44;
      this.label54.AutoSize = true;
      this.label54.Location = new Point(13, 74);
      this.label54.Name = "label54";
      this.label54.Size = new Size(32, 13);
      this.label54.TabIndex = 49;
      this.label54.Text = "Set2:";
      this.textBox53.BorderStyle = BorderStyle.FixedSingle;
      this.textBox53.Location = new Point(69, 46);
      this.textBox53.Name = "textBox53";
      this.textBox53.Size = new Size(53, 20);
      this.textBox53.TabIndex = 46;
      this.label53.AutoSize = true;
      this.label53.Location = new Point(13, 48);
      this.label53.Name = "label53";
      this.label53.Size = new Size(32, 13);
      this.label53.TabIndex = 47;
      this.label53.Text = "Set1:";
      this.textBox52.BorderStyle = BorderStyle.FixedSingle;
      this.textBox52.Location = new Point(69, 20);
      this.textBox52.Name = "textBox52";
      this.textBox52.Size = new Size(53, 20);
      this.textBox52.TabIndex = 44;
      this.label52.AutoSize = true;
      this.label52.Location = new Point(13, 22);
      this.label52.Name = "label52";
      this.label52.Size = new Size(32, 13);
      this.label52.TabIndex = 45;
      this.label52.Text = "Set0:";
      this.groupBox9.Controls.Add((Control) this.linkLabel1);
      this.groupBox9.Controls.Add((Control) this.pictureBox1);
      this.groupBox9.Controls.Add((Control) this.textBox50);
      this.groupBox9.Controls.Add((Control) this.label50);
      this.groupBox9.Controls.Add((Control) this.textBox48);
      this.groupBox9.Controls.Add((Control) this.label48);
      this.groupBox9.Controls.Add((Control) this.label49);
      this.groupBox9.Controls.Add((Control) this.textBox49);
      this.groupBox9.Location = new Point(6, 241);
      this.groupBox9.Name = "groupBox9";
      this.groupBox9.Size = new Size(187, 100);
      this.groupBox9.TabIndex = 40;
      this.groupBox9.TabStop = false;
      this.groupBox9.Text = "Icon";
      this.linkLabel1.AutoSize = true;
      this.linkLabel1.LinkColor = Color.Blue;
      this.linkLabel1.Location = new Point(117, 75);
      this.linkLabel1.Name = "linkLabel1";
      this.linkLabel1.Size = new Size(61, 13);
      this.linkLabel1.TabIndex = 96;
      this.linkLabel1.TabStop = true;
      this.linkLabel1.Text = "Icon Picker";
      this.linkLabel1.LinkClicked += new LinkLabelLinkClickedEventHandler(this.linkLabel1_LinkClicked);
      this.pictureBox1.BackColor = SystemColors.ButtonHighlight;
      this.pictureBox1.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox1.Cursor = Cursors.Default;
      this.pictureBox1.Location = new Point((int) sbyte.MaxValue, 20);
      this.pictureBox1.Name = "pictureBox1";
      this.pictureBox1.Size = new Size(40, 40);
      this.pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
      this.pictureBox1.TabIndex = 95;
      this.pictureBox1.TabStop = false;
      this.textBox50.BorderStyle = BorderStyle.FixedSingle;
      this.textBox50.Location = new Point(59, 74);
      this.textBox50.Name = "textBox50";
      this.textBox50.Size = new Size(37, 20);
      this.textBox50.TabIndex = 38;
      this.label50.AutoSize = true;
      this.label50.Location = new Point(11, 76);
      this.label50.Name = "label50";
      this.label50.Size = new Size(25, 13);
      this.label50.TabIndex = 39;
      this.label50.Text = "Col:";
      this.textBox48.BorderStyle = BorderStyle.FixedSingle;
      this.textBox48.Location = new Point(59, 20);
      this.textBox48.Name = "textBox48";
      this.textBox48.Size = new Size(37, 20);
      this.textBox48.TabIndex = 34;
      this.label48.AutoSize = true;
      this.label48.Location = new Point(11, 22);
      this.label48.Name = "label48";
      this.label48.Size = new Size(21, 13);
      this.label48.TabIndex = 35;
      this.label48.Text = "ID:";
      this.label49.AutoSize = true;
      this.label49.Location = new Point(11, 48);
      this.label49.Name = "label49";
      this.label49.Size = new Size(32, 13);
      this.label49.TabIndex = 37;
      this.label49.Text = "Row:";
      this.textBox49.BorderStyle = BorderStyle.FixedSingle;
      this.textBox49.Location = new Point(59, 46);
      this.textBox49.Name = "textBox49";
      this.textBox49.Size = new Size(37, 20);
      this.textBox49.TabIndex = 36;
      this.groupBox6.Controls.Add((Control) this.textBox21);
      this.groupBox6.Controls.Add((Control) this.textBox19);
      this.groupBox6.Controls.Add((Control) this.label21);
      this.groupBox6.Controls.Add((Control) this.label19);
      this.groupBox6.Controls.Add((Control) this.textBox16);
      this.groupBox6.Controls.Add((Control) this.label16);
      this.groupBox6.Controls.Add((Control) this.label18);
      this.groupBox6.Controls.Add((Control) this.textBox17);
      this.groupBox6.Controls.Add((Control) this.textBox18);
      this.groupBox6.Controls.Add((Control) this.label17);
      this.groupBox6.Location = new Point(6, 348);
      this.groupBox6.Name = "groupBox6";
      this.groupBox6.Size = new Size(215, 108);
      this.groupBox6.TabIndex = 33;
      this.groupBox6.TabStop = false;
      this.groupBox6.Text = "Stats";
      this.textBox21.BorderStyle = BorderStyle.FixedSingle;
      this.textBox21.Location = new Point(169, 51);
      this.textBox21.Name = "textBox21";
      this.textBox21.Size = new Size(37, 20);
      this.textBox21.TabIndex = 34;
      this.textBox19.BorderStyle = BorderStyle.FixedSingle;
      this.textBox19.Location = new Point(60, 78);
      this.textBox19.Name = "textBox19";
      this.textBox19.Size = new Size(146, 20);
      this.textBox19.TabIndex = 31;
      this.label21.AutoSize = true;
      this.label21.Location = new Point(106, 54);
      this.label21.Name = "label21";
      this.label21.Size = new Size(57, 13);
      this.label21.TabIndex = 35;
      this.label21.Text = "Drop prob:";
      this.label19.AutoSize = true;
      this.label19.Location = new Point(4, 80);
      this.label19.Name = "label19";
      this.label19.Size = new Size(34, 13);
      this.label19.TabIndex = 32;
      this.label19.Text = "Price:";
      this.textBox16.BorderStyle = BorderStyle.FixedSingle;
      this.textBox16.Location = new Point(61, 22);
      this.textBox16.Name = "textBox16";
      this.textBox16.Size = new Size(37, 20);
      this.textBox16.TabIndex = 25;
      this.label16.AutoSize = true;
      this.label16.Location = new Point(3, 25);
      this.label16.Name = "label16";
      this.label16.Size = new Size(56, 13);
      this.label16.TabIndex = 26;
      this.label16.Text = "Min Level:";
      this.label18.AutoSize = true;
      this.label18.Location = new Point(3, 54);
      this.label18.Name = "label18";
      this.label18.Size = new Size(38, 13);
      this.label18.TabIndex = 30;
      this.label18.Text = "Stack:";
      this.textBox17.BorderStyle = BorderStyle.FixedSingle;
      this.textBox17.Location = new Point(169, 22);
      this.textBox17.Name = "textBox17";
      this.textBox17.Size = new Size(37, 20);
      this.textBox17.TabIndex = 27;
      this.textBox18.BorderStyle = BorderStyle.FixedSingle;
      this.textBox18.Location = new Point(60, 52);
      this.textBox18.Name = "textBox18";
      this.textBox18.Size = new Size(37, 20);
      this.textBox18.TabIndex = 29;
      this.label17.AutoSize = true;
      this.label17.Location = new Point(106, 25);
      this.label17.Name = "label17";
      this.label17.Size = new Size(59, 13);
      this.label17.TabIndex = 28;
      this.label17.Text = "Max Level:";
      this.groupBox4.Controls.Add((Control) this.textBox15);
      this.groupBox4.Controls.Add((Control) this.label15);
      this.groupBox4.Controls.Add((Control) this.textBox10);
      this.groupBox4.Controls.Add((Control) this.label11);
      this.groupBox4.Controls.Add((Control) this.label14);
      this.groupBox4.Controls.Add((Control) this.textBox11);
      this.groupBox4.Controls.Add((Control) this.textBox14);
      this.groupBox4.Controls.Add((Control) this.label12);
      this.groupBox4.Controls.Add((Control) this.label13);
      this.groupBox4.Controls.Add((Control) this.textBox13);
      this.groupBox4.Location = new Point(227, 348);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Size = new Size(128, 180);
      this.groupBox4.TabIndex = 24;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "Options";
      this.textBox15.BorderStyle = BorderStyle.FixedSingle;
      this.textBox15.Location = new Point(65, 124);
      this.textBox15.Name = "textBox15";
      this.textBox15.Size = new Size(53, 20);
      this.textBox15.TabIndex = 22;
      this.label15.AutoSize = true;
      this.label15.Location = new Point(9, 126);
      this.label15.Name = "label15";
      this.label15.Size = new Size(38, 13);
      this.label15.TabIndex = 23;
      this.label15.Text = "Num4:";
      this.textBox10.BorderStyle = BorderStyle.FixedSingle;
      this.textBox10.Location = new Point(65, 20);
      this.textBox10.Name = "textBox10";
      this.textBox10.Size = new Size(53, 20);
      this.textBox10.TabIndex = 14;
      this.label11.AutoSize = true;
      this.label11.Location = new Point(9, 22);
      this.label11.Name = "label11";
      this.label11.Size = new Size(38, 13);
      this.label11.TabIndex = 15;
      this.label11.Text = "Num0:";
      this.label14.AutoSize = true;
      this.label14.Location = new Point(9, 100);
      this.label14.Name = "label14";
      this.label14.Size = new Size(38, 13);
      this.label14.TabIndex = 21;
      this.label14.Text = "Num3:";
      this.textBox11.BorderStyle = BorderStyle.FixedSingle;
      this.textBox11.Location = new Point(65, 46);
      this.textBox11.Name = "textBox11";
      this.textBox11.Size = new Size(53, 20);
      this.textBox11.TabIndex = 16;
      this.textBox14.BorderStyle = BorderStyle.FixedSingle;
      this.textBox14.Location = new Point(65, 98);
      this.textBox14.Name = "textBox14";
      this.textBox14.Size = new Size(53, 20);
      this.textBox14.TabIndex = 20;
      this.label12.AutoSize = true;
      this.label12.Location = new Point(9, 48);
      this.label12.Name = "label12";
      this.label12.Size = new Size(38, 13);
      this.label12.TabIndex = 17;
      this.label12.Text = "Num1:";
      this.label13.AutoSize = true;
      this.label13.Location = new Point(9, 74);
      this.label13.Name = "label13";
      this.label13.Size = new Size(38, 13);
      this.label13.TabIndex = 19;
      this.label13.Text = "Num2:";
      this.textBox13.BorderStyle = BorderStyle.FixedSingle;
      this.textBox13.Location = new Point(65, 72);
      this.textBox13.Name = "textBox13";
      this.textBox13.Size = new Size(53, 20);
      this.textBox13.TabIndex = 18;
      this.groupBox2.Controls.Add((Control) this.pictureBox23);
      this.groupBox2.Controls.Add((Control) this.textBox7);
      this.groupBox2.Controls.Add((Control) this.label8);
      this.groupBox2.Controls.Add((Control) this.comboBox4);
      this.groupBox2.Controls.Add((Control) this.checkedListBox1);
      this.groupBox2.Controls.Add((Control) this.comboBox2);
      this.groupBox2.Controls.Add((Control) this.comboBox1);
      this.groupBox2.Controls.Add((Control) this.label20);
      this.groupBox2.Controls.Add((Control) this.label9);
      this.groupBox2.Controls.Add((Control) this.textBox20);
      this.groupBox2.Controls.Add((Control) this.label10);
      this.groupBox2.Controls.Add((Control) this.textBox8);
      this.groupBox2.Controls.Add((Control) this.textBox2);
      this.groupBox2.Controls.Add((Control) this.textBox9);
      this.groupBox2.Controls.Add((Control) this.label3);
      this.groupBox2.Controls.Add((Control) this.textBox3);
      this.groupBox2.Controls.Add((Control) this.label2);
      this.groupBox2.Location = new Point(338, 6);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new Size(402, 229);
      this.groupBox2.TabIndex = 11;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "Character";
      this.pictureBox23.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.Flag;
      this.pictureBox23.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox23.Location = new Point(173, 192);
      this.pictureBox23.Name = "pictureBox23";
      this.pictureBox23.Size = new Size(19, 24);
      this.pictureBox23.TabIndex = 41;
      this.pictureBox23.TabStop = false;
      this.pictureBox23.Tag = (object) "a";
      this.toolTip1.SetToolTip((Control) this.pictureBox23, "Flag Builder");
      this.pictureBox23.Click += new EventHandler(this.pictureBox23_Click);
      this.pictureBox23.MouseLeave += new EventHandler(this.pictureBox23_MouseLeave);
      this.pictureBox23.MouseMove += new MouseEventHandler(this.pictureBox23_MouseMove_1);
      this.textBox7.BorderStyle = BorderStyle.FixedSingle;
      this.textBox7.Location = new Point(361, 129);
      this.textBox7.Name = "textBox7";
      this.textBox7.Size = new Size(30, 20);
      this.textBox7.TabIndex = 12;
      this.textBox7.TextChanged += new EventHandler(this.textBox7_TextChanged);
      this.label8.AutoSize = true;
      this.label8.Location = new Point(16, 78);
      this.label8.Name = "label8";
      this.label8.Size = new Size(35, 13);
      this.label8.TabIndex = 40;
      this.label8.Text = "Class:";
      this.comboBox4.FlatStyle = FlatStyle.Flat;
      this.comboBox4.FormattingEnabled = true;
      this.comboBox4.Location = new Point(72, 155);
      this.comboBox4.Name = "comboBox4";
      this.comboBox4.Size = new Size(268, 21);
      this.comboBox4.TabIndex = 38;
      this.comboBox4.SelectedIndexChanged += new EventHandler(this.comboBox4_SelectedIndexChanged);
      this.checkedListBox1.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
      this.checkedListBox1.BackColor = SystemColors.Control;
      this.checkedListBox1.BorderStyle = BorderStyle.None;
      this.checkedListBox1.CheckOnClick = true;
      this.checkedListBox1.ColumnWidth = 105;
      this.checkedListBox1.FormattingEnabled = true;
      this.checkedListBox1.IntegralHeight = false;
      this.checkedListBox1.Location = new Point(72, 78);
      this.checkedListBox1.MultiColumn = true;
      this.checkedListBox1.Name = "checkedListBox1";
      this.checkedListBox1.Size = new Size(319, 71);
      this.checkedListBox1.TabIndex = 39;
      this.checkedListBox1.SelectedIndexChanged += new EventHandler(this.checkedListBox1_SelectedIndexChanged);
      this.comboBox2.FlatStyle = FlatStyle.Flat;
      this.comboBox2.FormattingEnabled = true;
      this.comboBox2.Location = new Point(75, 47);
      this.comboBox2.Name = "comboBox2";
      this.comboBox2.Size = new Size(268, 21);
      this.comboBox2.TabIndex = 36;
      this.comboBox2.SelectedIndexChanged += new EventHandler(this.comboBox2_SelectedIndexChanged);
      this.comboBox1.FlatStyle = FlatStyle.Flat;
      this.comboBox1.FormattingEnabled = true;
      this.comboBox1.Location = new Point(75, 21);
      this.comboBox1.Name = "comboBox1";
      this.comboBox1.Size = new Size(268, 21);
      this.comboBox1.TabIndex = 35;
      this.comboBox1.SelectedIndexChanged += new EventHandler(this.comboBox1_SelectedIndexChanged);
      this.label20.AutoSize = true;
      this.label20.Location = new Point(205, 196);
      this.label20.Name = "label20";
      this.label20.Size = new Size(49, 13);
      this.label20.TabIndex = 34;
      this.label20.Text = "MaxUse:";
      this.label9.AutoSize = true;
      this.label9.Location = new Point(16, 196);
      this.label9.Name = "label9";
      this.label9.Size = new Size(30, 13);
      this.label9.TabIndex = 15;
      this.label9.Text = "Flag:";
      this.textBox20.BorderStyle = BorderStyle.FixedSingle;
      this.textBox20.Location = new Point(260, 194);
      this.textBox20.Name = "textBox20";
      this.textBox20.Size = new Size(100, 20);
      this.textBox20.TabIndex = 33;
      this.label10.AutoSize = true;
      this.label10.Location = new Point(16, 158);
      this.label10.Name = "label10";
      this.label10.Size = new Size(50, 13);
      this.label10.TabIndex = 17;
      this.label10.Text = "Wearing:";
      this.textBox8.BorderStyle = BorderStyle.FixedSingle;
      this.textBox8.Location = new Point(72, 194);
      this.textBox8.Name = "textBox8";
      this.textBox8.Size = new Size(100, 20);
      this.textBox8.TabIndex = 14;
      this.textBox2.BorderStyle = BorderStyle.FixedSingle;
      this.textBox2.Location = new Point(361, 21);
      this.textBox2.Name = "textBox2";
      this.textBox2.Size = new Size(30, 20);
      this.textBox2.TabIndex = 2;
      this.textBox9.BorderStyle = BorderStyle.FixedSingle;
      this.textBox9.Location = new Point(361, 155);
      this.textBox9.Name = "textBox9";
      this.textBox9.Size = new Size(30, 20);
      this.textBox9.TabIndex = 16;
      this.label3.AutoSize = true;
      this.label3.Location = new Point(16, 49);
      this.label3.Name = "label3";
      this.label3.Size = new Size(53, 13);
      this.label3.TabIndex = 9;
      this.label3.Text = "SubType:";
      this.textBox3.BorderStyle = BorderStyle.FixedSingle;
      this.textBox3.Location = new Point(361, 47);
      this.textBox3.Name = "textBox3";
      this.textBox3.Size = new Size(30, 20);
      this.textBox3.TabIndex = 3;
      this.label2.AutoSize = true;
      this.label2.Location = new Point(16, 23);
      this.label2.Name = "label2";
      this.label2.Size = new Size(34, 13);
      this.label2.TabIndex = 8;
      this.label2.Text = "Type:";
      this.groupBox1.Controls.Add((Control) this.checkBox1);
      this.groupBox1.Controls.Add((Control) this.label47);
      this.groupBox1.Controls.Add((Control) this.textBox46);
      this.groupBox1.Controls.Add((Control) this.textBox47);
      this.groupBox1.Controls.Add((Control) this.label46);
      this.groupBox1.Controls.Add((Control) this.label6);
      this.groupBox1.Controls.Add((Control) this.textBox1);
      this.groupBox1.Controls.Add((Control) this.label5);
      this.groupBox1.Controls.Add((Control) this.label1);
      this.groupBox1.Controls.Add((Control) this.textBox5);
      this.groupBox1.Controls.Add((Control) this.textBox6);
      this.groupBox1.Location = new Point(6, 6);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(326, 229);
      this.groupBox1.TabIndex = 0;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Basic";
      this.checkBox1.BackgroundImageLayout = ImageLayout.None;
      this.checkBox1.FlatStyle = FlatStyle.Flat;
      this.checkBox1.Location = new Point(14, 18);
      this.checkBox1.Name = "checkBox1";
      this.checkBox1.Size = new Size(306, 17);
      this.checkBox1.TabIndex = 35;
      this.checkBox1.Text = "Enable";
      this.checkBox1.UseVisualStyleBackColor = true;
      this.checkBox1.CheckedChanged += new EventHandler(this.checkBox1_CheckedChanged);
      this.label47.AutoSize = true;
      this.label47.Location = new Point(11, 200);
      this.label47.Name = "label47";
      this.label47.Size = new Size(33, 13);
      this.label47.TabIndex = 35;
      this.label47.Text = "SMC:";
      this.textBox46.BorderStyle = BorderStyle.FixedSingle;
      this.textBox46.Location = new Point(269, 39);
      this.textBox46.Name = "textBox46";
      this.textBox46.Size = new Size(51, 20);
      this.textBox46.TabIndex = 34;
      this.textBox47.BorderStyle = BorderStyle.FixedSingle;
      this.textBox47.Location = new Point(67, 198);
      this.textBox47.Name = "textBox47";
      this.textBox47.Size = new Size(253, 20);
      this.textBox47.TabIndex = 34;
      this.label46.AutoSize = true;
      this.label46.Location = new Point(213, 41);
      this.label46.Name = "label46";
      this.label46.Size = new Size(55, 13);
      this.label46.TabIndex = 35;
      this.label46.Text = "ZoneFlag:";
      this.label6.AutoSize = true;
      this.label6.Location = new Point(11, 93);
      this.label6.Name = "label6";
      this.label6.Size = new Size(35, 13);
      this.label6.TabIndex = 12;
      this.label6.Text = "Desc:";
      this.textBox1.BorderStyle = BorderStyle.FixedSingle;
      this.textBox1.Location = new Point(67, 39);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(51, 20);
      this.textBox1.TabIndex = 1;
      this.label5.AutoSize = true;
      this.label5.Location = new Point(11, 67);
      this.label5.Name = "label5";
      this.label5.Size = new Size(38, 13);
      this.label5.TabIndex = 11;
      this.label5.Text = "Name:";
      this.label1.AutoSize = true;
      this.label1.Location = new Point(11, 41);
      this.label1.Name = "label1";
      this.label1.Size = new Size(36, 13);
      this.label1.TabIndex = 7;
      this.label1.Text = "Index:";
      this.textBox5.BorderStyle = BorderStyle.FixedSingle;
      this.textBox5.Location = new Point(67, 65);
      this.textBox5.Name = "textBox5";
      this.textBox5.Size = new Size(253, 20);
      this.textBox5.TabIndex = 5;
      this.textBox5.TextChanged += new EventHandler(this.textBox5_TextChanged);
      this.textBox6.BorderStyle = BorderStyle.FixedSingle;
      this.textBox6.Location = new Point(67, 91);
      this.textBox6.Multiline = true;
      this.textBox6.Name = "textBox6";
      this.textBox6.Size = new Size(253, 101);
      this.textBox6.TabIndex = 6;
      this.tabPage2.BorderStyle = BorderStyle.FixedSingle;
      this.tabPage2.Controls.Add((Control) this.groupBox7);
      this.tabPage2.Controls.Add((Control) this.groupBox8);
      this.tabPage2.Location = new Point(4, 22);
      this.tabPage2.Name = "tabPage2";
      this.tabPage2.Padding = new Padding(3);
      this.tabPage2.Size = new Size(939, 610);
      this.tabPage2.TabIndex = 1;
      this.tabPage2.Text = "Crafting";
      this.groupBox7.Controls.Add((Control) this.pictureBox12);
      this.groupBox7.Controls.Add((Control) this.pictureBox11);
      this.groupBox7.Controls.Add((Control) this.pictureBox10);
      this.groupBox7.Controls.Add((Control) this.pictureBox9);
      this.groupBox7.Controls.Add((Control) this.pictureBox8);
      this.groupBox7.Controls.Add((Control) this.pictureBox7);
      this.groupBox7.Controls.Add((Control) this.pictureBox6);
      this.groupBox7.Controls.Add((Control) this.pictureBox5);
      this.groupBox7.Controls.Add((Control) this.pictureBox4);
      this.groupBox7.Controls.Add((Control) this.pictureBox3);
      this.groupBox7.Controls.Add((Control) this.textBox36);
      this.groupBox7.Controls.Add((Control) this.textBox27);
      this.groupBox7.Controls.Add((Control) this.textBox39);
      this.groupBox7.Controls.Add((Control) this.label40);
      this.groupBox7.Controls.Add((Control) this.textBox31);
      this.groupBox7.Controls.Add((Control) this.label28);
      this.groupBox7.Controls.Add((Control) this.textBox26);
      this.groupBox7.Controls.Add((Control) this.label27);
      this.groupBox7.Controls.Add((Control) this.label39);
      this.groupBox7.Controls.Add((Control) this.label34);
      this.groupBox7.Controls.Add((Control) this.textBox40);
      this.groupBox7.Controls.Add((Control) this.label22);
      this.groupBox7.Controls.Add((Control) this.textBox28);
      this.groupBox7.Controls.Add((Control) this.textBox33);
      this.groupBox7.Controls.Add((Control) this.textBox38);
      this.groupBox7.Controls.Add((Control) this.label41);
      this.groupBox7.Controls.Add((Control) this.textBox34);
      this.groupBox7.Controls.Add((Control) this.label29);
      this.groupBox7.Controls.Add((Control) this.textBox22);
      this.groupBox7.Controls.Add((Control) this.label26);
      this.groupBox7.Controls.Add((Control) this.label33);
      this.groupBox7.Controls.Add((Control) this.label38);
      this.groupBox7.Controls.Add((Control) this.textBox41);
      this.groupBox7.Controls.Add((Control) this.label35);
      this.groupBox7.Controls.Add((Control) this.textBox29);
      this.groupBox7.Controls.Add((Control) this.label23);
      this.groupBox7.Controls.Add((Control) this.textBox25);
      this.groupBox7.Controls.Add((Control) this.textBox32);
      this.groupBox7.Controls.Add((Control) this.textBox37);
      this.groupBox7.Controls.Add((Control) this.textBox35);
      this.groupBox7.Controls.Add((Control) this.label30);
      this.groupBox7.Controls.Add((Control) this.textBox23);
      this.groupBox7.Controls.Add((Control) this.label25);
      this.groupBox7.Controls.Add((Control) this.label32);
      this.groupBox7.Controls.Add((Control) this.label37);
      this.groupBox7.Controls.Add((Control) this.label36);
      this.groupBox7.Controls.Add((Control) this.textBox30);
      this.groupBox7.Controls.Add((Control) this.label24);
      this.groupBox7.Controls.Add((Control) this.textBox24);
      this.groupBox7.Controls.Add((Control) this.label31);
      this.groupBox7.Location = new Point(6, 90);
      this.groupBox7.Name = "groupBox7";
      this.groupBox7.Size = new Size(733, 176);
      this.groupBox7.TabIndex = 41;
      this.groupBox7.TabStop = false;
      this.groupBox7.Text = "Item Crafting";
      this.pictureBox12.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox12.Location = new Point(447, 129);
      this.pictureBox12.Name = "pictureBox12";
      this.pictureBox12.Size = new Size(22, 22);
      this.pictureBox12.TabIndex = 94;
      this.pictureBox12.TabStop = false;
      this.toolTip1.SetToolTip((Control) this.pictureBox12, "Search Item");
      this.pictureBox12.Click += new EventHandler(this.pictureBox12_Click);
      this.pictureBox12.MouseLeave += new EventHandler(this.pictureBox12_MouseLeave);
      this.pictureBox12.MouseMove += new MouseEventHandler(this.pictureBox12_MouseMove);
      this.pictureBox11.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox11.Location = new Point(447, 103);
      this.pictureBox11.Name = "pictureBox11";
      this.pictureBox11.Size = new Size(22, 22);
      this.pictureBox11.TabIndex = 93;
      this.pictureBox11.TabStop = false;
      this.toolTip1.SetToolTip((Control) this.pictureBox11, "Search Item");
      this.pictureBox11.Click += new EventHandler(this.pictureBox11_Click);
      this.pictureBox11.MouseLeave += new EventHandler(this.pictureBox11_MouseLeave);
      this.pictureBox11.MouseMove += new MouseEventHandler(this.pictureBox11_MouseMove);
      this.pictureBox10.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox10.Location = new Point(447, 77);
      this.pictureBox10.Name = "pictureBox10";
      this.pictureBox10.Size = new Size(22, 22);
      this.pictureBox10.TabIndex = 92;
      this.pictureBox10.TabStop = false;
      this.toolTip1.SetToolTip((Control) this.pictureBox10, "Search Item");
      this.pictureBox10.Click += new EventHandler(this.pictureBox10_Click);
      this.pictureBox10.MouseLeave += new EventHandler(this.pictureBox10_MouseLeave);
      this.pictureBox10.MouseMove += new MouseEventHandler(this.pictureBox10_MouseMove);
      this.pictureBox9.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox9.Location = new Point(447, 51);
      this.pictureBox9.Name = "pictureBox9";
      this.pictureBox9.Size = new Size(22, 22);
      this.pictureBox9.TabIndex = 91;
      this.pictureBox9.TabStop = false;
      this.toolTip1.SetToolTip((Control) this.pictureBox9, "Search Item");
      this.pictureBox9.Click += new EventHandler(this.pictureBox9_Click);
      this.pictureBox9.MouseLeave += new EventHandler(this.pictureBox9_MouseLeave);
      this.pictureBox9.MouseMove += new MouseEventHandler(this.pictureBox9_MouseMove);
      this.pictureBox8.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox8.Location = new Point(447, 25);
      this.pictureBox8.Name = "pictureBox8";
      this.pictureBox8.Size = new Size(22, 22);
      this.pictureBox8.TabIndex = 90;
      this.pictureBox8.TabStop = false;
      this.toolTip1.SetToolTip((Control) this.pictureBox8, "Search Item");
      this.pictureBox8.Click += new EventHandler(this.pictureBox8_Click);
      this.pictureBox8.MouseLeave += new EventHandler(this.pictureBox8_MouseLeave);
      this.pictureBox8.MouseMove += new MouseEventHandler(this.pictureBox8_MouseMove);
      this.pictureBox7.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox7.Location = new Point(143, 129);
      this.pictureBox7.Name = "pictureBox7";
      this.pictureBox7.Size = new Size(22, 22);
      this.pictureBox7.TabIndex = 89;
      this.pictureBox7.TabStop = false;
      this.toolTip1.SetToolTip((Control) this.pictureBox7, "Search Item");
      this.pictureBox7.Click += new EventHandler(this.pictureBox7_Click);
      this.pictureBox7.MouseLeave += new EventHandler(this.pictureBox7_MouseLeave);
      this.pictureBox7.MouseMove += new MouseEventHandler(this.pictureBox7_MouseMove);
      this.pictureBox6.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox6.Location = new Point(143, 103);
      this.pictureBox6.Name = "pictureBox6";
      this.pictureBox6.Size = new Size(22, 22);
      this.pictureBox6.TabIndex = 88;
      this.pictureBox6.TabStop = false;
      this.toolTip1.SetToolTip((Control) this.pictureBox6, "Search Item");
      this.pictureBox6.Click += new EventHandler(this.pictureBox6_Click);
      this.pictureBox6.MouseLeave += new EventHandler(this.pictureBox6_MouseLeave);
      this.pictureBox6.MouseMove += new MouseEventHandler(this.pictureBox6_MouseMove);
      this.pictureBox5.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox5.Location = new Point(143, 77);
      this.pictureBox5.Name = "pictureBox5";
      this.pictureBox5.Size = new Size(22, 22);
      this.pictureBox5.TabIndex = 87;
      this.pictureBox5.TabStop = false;
      this.toolTip1.SetToolTip((Control) this.pictureBox5, "Search Item");
      this.pictureBox5.Click += new EventHandler(this.pictureBox5_Click);
      this.pictureBox5.MouseLeave += new EventHandler(this.pictureBox5_MouseLeave);
      this.pictureBox5.MouseMove += new MouseEventHandler(this.pictureBox5_MouseMove);
      this.pictureBox4.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox4.Location = new Point(143, 51);
      this.pictureBox4.Name = "pictureBox4";
      this.pictureBox4.Size = new Size(22, 22);
      this.pictureBox4.TabIndex = 86;
      this.pictureBox4.TabStop = false;
      this.toolTip1.SetToolTip((Control) this.pictureBox4, "Search Item");
      this.pictureBox4.Click += new EventHandler(this.pictureBox4_Click);
      this.pictureBox4.MouseLeave += new EventHandler(this.pictureBox4_MouseLeave);
      this.pictureBox4.MouseMove += new MouseEventHandler(this.pictureBox4_MouseMove);
      this.pictureBox3.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox3.Location = new Point(143, 25);
      this.pictureBox3.Name = "pictureBox3";
      this.pictureBox3.Size = new Size(22, 22);
      this.pictureBox3.TabIndex = 42;
      this.pictureBox3.TabStop = false;
      this.toolTip1.SetToolTip((Control) this.pictureBox3, "Search Item");
      this.pictureBox3.Click += new EventHandler(this.pictureBox3_Click);
      this.pictureBox3.MouseLeave += new EventHandler(this.pictureBox3_MouseLeave);
      this.pictureBox3.MouseMove += new MouseEventHandler(this.pictureBox3_MouseMove_1);
      this.textBox36.BorderStyle = BorderStyle.FixedSingle;
      this.textBox36.Location = new Point(249, 130);
      this.textBox36.Name = "textBox36";
      this.textBox36.Size = new Size(40, 20);
      this.textBox36.TabIndex = 66;
      this.textBox27.BorderStyle = BorderStyle.FixedSingle;
      this.textBox27.Location = new Point(380, 26);
      this.textBox27.Name = "textBox27";
      this.textBox27.Size = new Size(61, 20);
      this.textBox27.TabIndex = 48;
      this.textBox39.BorderStyle = BorderStyle.FixedSingle;
      this.textBox39.Location = new Point(544, 78);
      this.textBox39.Name = "textBox39";
      this.textBox39.Size = new Size(40, 20);
      this.textBox39.TabIndex = 72;
      this.label40.AutoSize = true;
      this.label40.Location = new Point(480, 106);
      this.label40.Name = "label40";
      this.label40.Size = new Size(46, 13);
      this.label40.TabIndex = 75;
      this.label40.Text = "Amount:";
      this.textBox31.BorderStyle = BorderStyle.FixedSingle;
      this.textBox31.Location = new Point(380, 130);
      this.textBox31.Name = "textBox31";
      this.textBox31.Size = new Size(61, 20);
      this.textBox31.TabIndex = 56;
      this.label28.AutoSize = true;
      this.label28.Location = new Point(320, 54);
      this.label28.Name = "label28";
      this.label28.Size = new Size(44, 13);
      this.label28.TabIndex = 51;
      this.label28.Text = "Item ID:";
      this.textBox26.BorderStyle = BorderStyle.FixedSingle;
      this.textBox26.Location = new Point(76, 130);
      this.textBox26.Name = "textBox26";
      this.textBox26.Size = new Size(61, 20);
      this.textBox26.TabIndex = 46;
      this.label27.AutoSize = true;
      this.label27.Location = new Point(320, 28);
      this.label27.Name = "label27";
      this.label27.Size = new Size(44, 13);
      this.label27.TabIndex = 49;
      this.label27.Text = "Item ID:";
      this.label39.AutoSize = true;
      this.label39.Location = new Point(480, 80);
      this.label39.Name = "label39";
      this.label39.Size = new Size(46, 13);
      this.label39.TabIndex = 73;
      this.label39.Text = "Amount:";
      this.label34.AutoSize = true;
      this.label34.Location = new Point(187, 80);
      this.label34.Name = "label34";
      this.label34.Size = new Size(46, 13);
      this.label34.TabIndex = 63;
      this.label34.Text = "Amount:";
      this.textBox40.BorderStyle = BorderStyle.FixedSingle;
      this.textBox40.Location = new Point(544, 104);
      this.textBox40.Name = "textBox40";
      this.textBox40.Size = new Size(40, 20);
      this.textBox40.TabIndex = 74;
      this.label22.AutoSize = true;
      this.label22.Location = new Point(18, 28);
      this.label22.Name = "label22";
      this.label22.Size = new Size(44, 13);
      this.label22.TabIndex = 39;
      this.label22.Text = "Item ID:";
      this.textBox28.BorderStyle = BorderStyle.FixedSingle;
      this.textBox28.Location = new Point(380, 52);
      this.textBox28.Name = "textBox28";
      this.textBox28.Size = new Size(61, 20);
      this.textBox28.TabIndex = 50;
      this.textBox33.BorderStyle = BorderStyle.FixedSingle;
      this.textBox33.Location = new Point(249, 52);
      this.textBox33.Name = "textBox33";
      this.textBox33.Size = new Size(40, 20);
      this.textBox33.TabIndex = 60;
      this.textBox38.BorderStyle = BorderStyle.FixedSingle;
      this.textBox38.Location = new Point(544, 52);
      this.textBox38.Name = "textBox38";
      this.textBox38.Size = new Size(40, 20);
      this.textBox38.TabIndex = 70;
      this.label41.AutoSize = true;
      this.label41.Location = new Point(480, 132);
      this.label41.Name = "label41";
      this.label41.Size = new Size(46, 13);
      this.label41.TabIndex = 77;
      this.label41.Text = "Amount:";
      this.textBox34.BorderStyle = BorderStyle.FixedSingle;
      this.textBox34.Location = new Point(249, 78);
      this.textBox34.Name = "textBox34";
      this.textBox34.Size = new Size(40, 20);
      this.textBox34.TabIndex = 62;
      this.label29.AutoSize = true;
      this.label29.Location = new Point(320, 80);
      this.label29.Name = "label29";
      this.label29.Size = new Size(44, 13);
      this.label29.TabIndex = 53;
      this.label29.Text = "Item ID:";
      this.textBox22.BorderStyle = BorderStyle.FixedSingle;
      this.textBox22.Location = new Point(76, 26);
      this.textBox22.Name = "textBox22";
      this.textBox22.Size = new Size(61, 20);
      this.textBox22.TabIndex = 38;
      this.label26.AutoSize = true;
      this.label26.Location = new Point(18, 132);
      this.label26.Name = "label26";
      this.label26.Size = new Size(44, 13);
      this.label26.TabIndex = 47;
      this.label26.Text = "Item ID:";
      this.label33.AutoSize = true;
      this.label33.Location = new Point(187, 54);
      this.label33.Name = "label33";
      this.label33.Size = new Size(46, 13);
      this.label33.TabIndex = 61;
      this.label33.Text = "Amount:";
      this.label38.AutoSize = true;
      this.label38.Location = new Point(480, 54);
      this.label38.Name = "label38";
      this.label38.Size = new Size(46, 13);
      this.label38.TabIndex = 71;
      this.label38.Text = "Amount:";
      this.textBox41.BorderStyle = BorderStyle.FixedSingle;
      this.textBox41.Location = new Point(544, 130);
      this.textBox41.Name = "textBox41";
      this.textBox41.Size = new Size(40, 20);
      this.textBox41.TabIndex = 76;
      this.label35.AutoSize = true;
      this.label35.Location = new Point(187, 106);
      this.label35.Name = "label35";
      this.label35.Size = new Size(46, 13);
      this.label35.TabIndex = 65;
      this.label35.Text = "Amount:";
      this.textBox29.BorderStyle = BorderStyle.FixedSingle;
      this.textBox29.Location = new Point(380, 78);
      this.textBox29.Name = "textBox29";
      this.textBox29.Size = new Size(61, 20);
      this.textBox29.TabIndex = 52;
      this.label23.AutoSize = true;
      this.label23.Location = new Point(18, 54);
      this.label23.Name = "label23";
      this.label23.Size = new Size(44, 13);
      this.label23.TabIndex = 41;
      this.label23.Text = "Item ID:";
      this.textBox25.BorderStyle = BorderStyle.FixedSingle;
      this.textBox25.Location = new Point(76, 104);
      this.textBox25.Name = "textBox25";
      this.textBox25.Size = new Size(61, 20);
      this.textBox25.TabIndex = 44;
      this.textBox32.BorderStyle = BorderStyle.FixedSingle;
      this.textBox32.Location = new Point(249, 26);
      this.textBox32.Name = "textBox32";
      this.textBox32.Size = new Size(40, 20);
      this.textBox32.TabIndex = 58;
      this.textBox37.BorderStyle = BorderStyle.FixedSingle;
      this.textBox37.Location = new Point(544, 26);
      this.textBox37.Name = "textBox37";
      this.textBox37.Size = new Size(40, 20);
      this.textBox37.TabIndex = 68;
      this.textBox35.BorderStyle = BorderStyle.FixedSingle;
      this.textBox35.Location = new Point(249, 104);
      this.textBox35.Name = "textBox35";
      this.textBox35.Size = new Size(40, 20);
      this.textBox35.TabIndex = 64;
      this.label30.AutoSize = true;
      this.label30.Location = new Point(320, 106);
      this.label30.Name = "label30";
      this.label30.Size = new Size(44, 13);
      this.label30.TabIndex = 55;
      this.label30.Text = "Item ID:";
      this.textBox23.BorderStyle = BorderStyle.FixedSingle;
      this.textBox23.Location = new Point(76, 52);
      this.textBox23.Name = "textBox23";
      this.textBox23.Size = new Size(61, 20);
      this.textBox23.TabIndex = 40;
      this.label25.AutoSize = true;
      this.label25.Location = new Point(18, 106);
      this.label25.Name = "label25";
      this.label25.Size = new Size(44, 13);
      this.label25.TabIndex = 45;
      this.label25.Text = "Item ID:";
      this.label32.AutoSize = true;
      this.label32.Location = new Point(187, 28);
      this.label32.Name = "label32";
      this.label32.Size = new Size(46, 13);
      this.label32.TabIndex = 59;
      this.label32.Text = "Amount:";
      this.label37.AutoSize = true;
      this.label37.Location = new Point(480, 28);
      this.label37.Name = "label37";
      this.label37.Size = new Size(46, 13);
      this.label37.TabIndex = 69;
      this.label37.Text = "Amount:";
      this.label36.AutoSize = true;
      this.label36.Location = new Point(187, 132);
      this.label36.Name = "label36";
      this.label36.Size = new Size(46, 13);
      this.label36.TabIndex = 67;
      this.label36.Text = "Amount:";
      this.textBox30.BorderStyle = BorderStyle.FixedSingle;
      this.textBox30.Location = new Point(380, 104);
      this.textBox30.Name = "textBox30";
      this.textBox30.Size = new Size(61, 20);
      this.textBox30.TabIndex = 54;
      this.label24.AutoSize = true;
      this.label24.Location = new Point(18, 80);
      this.label24.Name = "label24";
      this.label24.Size = new Size(44, 13);
      this.label24.TabIndex = 43;
      this.label24.Text = "Item ID:";
      this.textBox24.BorderStyle = BorderStyle.FixedSingle;
      this.textBox24.Location = new Point(76, 78);
      this.textBox24.Name = "textBox24";
      this.textBox24.Size = new Size(61, 20);
      this.textBox24.TabIndex = 42;
      this.label31.AutoSize = true;
      this.label31.Location = new Point(320, 132);
      this.label31.Name = "label31";
      this.label31.Size = new Size(44, 13);
      this.label31.TabIndex = 57;
      this.label31.Text = "Item ID:";
      this.groupBox8.Controls.Add((Control) this.textBox45);
      this.groupBox8.Controls.Add((Control) this.label45);
      this.groupBox8.Controls.Add((Control) this.textBox44);
      this.groupBox8.Controls.Add((Control) this.label44);
      this.groupBox8.Controls.Add((Control) this.textBox43);
      this.groupBox8.Controls.Add((Control) this.label43);
      this.groupBox8.Controls.Add((Control) this.textBox42);
      this.groupBox8.Controls.Add((Control) this.label42);
      this.groupBox8.Location = new Point(6, 6);
      this.groupBox8.Name = "groupBox8";
      this.groupBox8.Size = new Size(232, 78);
      this.groupBox8.TabIndex = 39;
      this.groupBox8.TabStop = false;
      this.groupBox8.Text = "Crafting Skill Requirement";
      this.textBox45.BorderStyle = BorderStyle.FixedSingle;
      this.textBox45.Location = new Point(178, 50);
      this.textBox45.Name = "textBox45";
      this.textBox45.Size = new Size(40, 20);
      this.textBox45.TabIndex = 84;
      this.label45.AutoSize = true;
      this.label45.Location = new Point(114, 52);
      this.label45.Name = "label45";
      this.label45.Size = new Size(58, 13);
      this.label45.TabIndex = 85;
      this.label45.Text = "Skill Level:";
      this.textBox44.BorderStyle = BorderStyle.FixedSingle;
      this.textBox44.Location = new Point(52, 50);
      this.textBox44.Name = "textBox44";
      this.textBox44.Size = new Size(40, 20);
      this.textBox44.TabIndex = 82;
      this.label44.AutoSize = true;
      this.label44.Location = new Point(6, 52);
      this.label44.Name = "label44";
      this.label44.Size = new Size(43, 13);
      this.label44.TabIndex = 83;
      this.label44.Text = "Skill ID:";
      this.textBox43.BorderStyle = BorderStyle.FixedSingle;
      this.textBox43.Location = new Point(178, 24);
      this.textBox43.Name = "textBox43";
      this.textBox43.Size = new Size(40, 20);
      this.textBox43.TabIndex = 80;
      this.label43.AutoSize = true;
      this.label43.Location = new Point(114, 26);
      this.label43.Name = "label43";
      this.label43.Size = new Size(58, 13);
      this.label43.TabIndex = 81;
      this.label43.Text = "Skill Level:";
      this.textBox42.BorderStyle = BorderStyle.FixedSingle;
      this.textBox42.Location = new Point(52, 24);
      this.textBox42.Name = "textBox42";
      this.textBox42.Size = new Size(40, 20);
      this.textBox42.TabIndex = 78;
      this.label42.AutoSize = true;
      this.label42.Location = new Point(6, 26);
      this.label42.Name = "label42";
      this.label42.Size = new Size(43, 13);
      this.label42.TabIndex = 79;
      this.label42.Text = "Skill ID:";
      this.tabPage3.BorderStyle = BorderStyle.FixedSingle;
      this.tabPage3.Controls.Add((Control) this.groupBox17);
      this.tabPage3.Controls.Add((Control) this.groupBox13);
      this.tabPage3.Location = new Point(4, 22);
      this.tabPage3.Name = "tabPage3";
      this.tabPage3.Size = new Size(939, 610);
      this.tabPage3.TabIndex = 2;
      this.tabPage3.Text = "Rare & Purple ";
      this.groupBox17.Controls.Add((Control) this.comboBox23);
      this.groupBox17.Controls.Add((Control) this.comboBox22);
      this.groupBox17.Controls.Add((Control) this.comboBox21);
      this.groupBox17.Controls.Add((Control) this.comboBox20);
      this.groupBox17.Controls.Add((Control) this.comboBox19);
      this.groupBox17.Controls.Add((Control) this.comboBox18);
      this.groupBox17.Controls.Add((Control) this.comboBox17);
      this.groupBox17.Controls.Add((Control) this.comboBox16);
      this.groupBox17.Controls.Add((Control) this.comboBox15);
      this.groupBox17.Controls.Add((Control) this.comboBox14);
      this.groupBox17.Controls.Add((Control) this.label104);
      this.groupBox17.Controls.Add((Control) this.comboBox13);
      this.groupBox17.Controls.Add((Control) this.label103);
      this.groupBox17.Controls.Add((Control) this.label102);
      this.groupBox17.Controls.Add((Control) this.label101);
      this.groupBox17.Controls.Add((Control) this.label100);
      this.groupBox17.Controls.Add((Control) this.comboBox12);
      this.groupBox17.Controls.Add((Control) this.comboBox11);
      this.groupBox17.Controls.Add((Control) this.comboBox10);
      this.groupBox17.Controls.Add((Control) this.comboBox9);
      this.groupBox17.Controls.Add((Control) this.comboBox8);
      this.groupBox17.Controls.Add((Control) this.label99);
      this.groupBox17.Controls.Add((Control) this.comboBox7);
      this.groupBox17.Controls.Add((Control) this.label98);
      this.groupBox17.Controls.Add((Control) this.comboBox6);
      this.groupBox17.Controls.Add((Control) this.label97);
      this.groupBox17.Controls.Add((Control) this.comboBox5);
      this.groupBox17.Controls.Add((Control) this.label96);
      this.groupBox17.Controls.Add((Control) this.comboBox3);
      this.groupBox17.Controls.Add((Control) this.label95);
      this.groupBox17.Location = new Point(318, 3);
      this.groupBox17.Name = "groupBox17";
      this.groupBox17.Size = new Size(427, 295);
      this.groupBox17.TabIndex = 1;
      this.groupBox17.TabStop = false;
      this.groupBox17.Text = "Purple Items";
      this.comboBox23.FlatStyle = FlatStyle.Flat;
      this.comboBox23.FormattingEnabled = true;
      this.comboBox23.Location = new Point(299, 261);
      this.comboBox23.Name = "comboBox23";
      this.comboBox23.Size = new Size(109, 21);
      this.comboBox23.TabIndex = 37;
      this.comboBox23.SelectedIndexChanged += new EventHandler(this.comboBox23_SelectedIndexChanged);
      this.comboBox22.FlatStyle = FlatStyle.Flat;
      this.comboBox22.FormattingEnabled = true;
      this.comboBox22.Location = new Point(299, 234);
      this.comboBox22.Name = "comboBox22";
      this.comboBox22.Size = new Size(109, 21);
      this.comboBox22.TabIndex = 36;
      this.comboBox22.SelectedIndexChanged += new EventHandler(this.comboBox22_SelectedIndexChanged);
      this.comboBox21.FlatStyle = FlatStyle.Flat;
      this.comboBox21.FormattingEnabled = true;
      this.comboBox21.Location = new Point(299, 207);
      this.comboBox21.Name = "comboBox21";
      this.comboBox21.Size = new Size(109, 21);
      this.comboBox21.TabIndex = 35;
      this.comboBox21.SelectedIndexChanged += new EventHandler(this.comboBox21_SelectedIndexChanged);
      this.comboBox20.FlatStyle = FlatStyle.Flat;
      this.comboBox20.FormattingEnabled = true;
      this.comboBox20.Location = new Point(299, 180);
      this.comboBox20.Name = "comboBox20";
      this.comboBox20.Size = new Size(109, 21);
      this.comboBox20.TabIndex = 34;
      this.comboBox20.SelectedIndexChanged += new EventHandler(this.comboBox20_SelectedIndexChanged);
      this.comboBox19.FlatStyle = FlatStyle.Flat;
      this.comboBox19.FormattingEnabled = true;
      this.comboBox19.Location = new Point(299, 153);
      this.comboBox19.Name = "comboBox19";
      this.comboBox19.Size = new Size(109, 21);
      this.comboBox19.TabIndex = 33;
      this.comboBox19.SelectedIndexChanged += new EventHandler(this.comboBox19_SelectedIndexChanged);
      this.comboBox18.FlatStyle = FlatStyle.Flat;
      this.comboBox18.FormattingEnabled = true;
      this.comboBox18.Location = new Point(299, 126);
      this.comboBox18.Name = "comboBox18";
      this.comboBox18.Size = new Size(109, 21);
      this.comboBox18.TabIndex = 32;
      this.comboBox18.SelectedIndexChanged += new EventHandler(this.comboBox18_SelectedIndexChanged);
      this.comboBox17.FlatStyle = FlatStyle.Flat;
      this.comboBox17.FormattingEnabled = true;
      this.comboBox17.Location = new Point(299, 99);
      this.comboBox17.Name = "comboBox17";
      this.comboBox17.Size = new Size(109, 21);
      this.comboBox17.TabIndex = 31;
      this.comboBox17.SelectedIndexChanged += new EventHandler(this.comboBox17_SelectedIndexChanged);
      this.comboBox16.FlatStyle = FlatStyle.Flat;
      this.comboBox16.FormattingEnabled = true;
      this.comboBox16.Location = new Point(299, 72);
      this.comboBox16.Name = "comboBox16";
      this.comboBox16.Size = new Size(109, 21);
      this.comboBox16.TabIndex = 30;
      this.comboBox16.SelectedIndexChanged += new EventHandler(this.comboBox16_SelectedIndexChanged);
      this.comboBox15.FlatStyle = FlatStyle.Flat;
      this.comboBox15.FormattingEnabled = true;
      this.comboBox15.Location = new Point(299, 45);
      this.comboBox15.Name = "comboBox15";
      this.comboBox15.Size = new Size(109, 21);
      this.comboBox15.TabIndex = 29;
      this.comboBox15.SelectedIndexChanged += new EventHandler(this.comboBox15_SelectedIndexChanged);
      this.comboBox14.FlatStyle = FlatStyle.Flat;
      this.comboBox14.FormattingEnabled = true;
      this.comboBox14.Location = new Point(299, 18);
      this.comboBox14.Name = "comboBox14";
      this.comboBox14.Size = new Size(109, 21);
      this.comboBox14.TabIndex = 28;
      this.comboBox14.SelectedIndexChanged += new EventHandler(this.comboBox14_SelectedIndexChanged);
      this.label104.AutoSize = true;
      this.label104.Location = new Point(16, 264);
      this.label104.Name = "label104";
      this.label104.Size = new Size(40, 13);
      this.label104.TabIndex = 27;
      this.label104.Text = "Seal 9:";
      this.comboBox13.FlatStyle = FlatStyle.Flat;
      this.comboBox13.FormattingEnabled = true;
      this.comboBox13.Location = new Point(62, 261);
      this.comboBox13.Name = "comboBox13";
      this.comboBox13.Size = new Size(217, 21);
      this.comboBox13.TabIndex = 26;
      this.comboBox13.SelectedIndexChanged += new EventHandler(this.comboBox13_SelectedIndexChanged);
      this.label103.AutoSize = true;
      this.label103.Location = new Point(16, 237);
      this.label103.Name = "label103";
      this.label103.Size = new Size(40, 13);
      this.label103.TabIndex = 25;
      this.label103.Text = "Seal 8:";
      this.label102.AutoSize = true;
      this.label102.Location = new Point(16, 211);
      this.label102.Name = "label102";
      this.label102.Size = new Size(40, 13);
      this.label102.TabIndex = 24;
      this.label102.Text = "Seal 7:";
      this.label101.AutoSize = true;
      this.label101.Location = new Point(16, 184);
      this.label101.Name = "label101";
      this.label101.Size = new Size(40, 13);
      this.label101.TabIndex = 23;
      this.label101.Text = "Seal 6:";
      this.label100.AutoSize = true;
      this.label100.Location = new Point(16, 156);
      this.label100.Name = "label100";
      this.label100.Size = new Size(40, 13);
      this.label100.TabIndex = 22;
      this.label100.Text = "Seal 5:";
      this.comboBox12.FlatStyle = FlatStyle.Flat;
      this.comboBox12.FormattingEnabled = true;
      this.comboBox12.Location = new Point(62, 234);
      this.comboBox12.Name = "comboBox12";
      this.comboBox12.Size = new Size(217, 21);
      this.comboBox12.TabIndex = 21;
      this.comboBox12.SelectedIndexChanged += new EventHandler(this.comboBox12_SelectedIndexChanged);
      this.comboBox11.FlatStyle = FlatStyle.Flat;
      this.comboBox11.FormattingEnabled = true;
      this.comboBox11.Location = new Point(62, 207);
      this.comboBox11.Name = "comboBox11";
      this.comboBox11.Size = new Size(217, 21);
      this.comboBox11.TabIndex = 20;
      this.comboBox11.SelectedIndexChanged += new EventHandler(this.comboBox11_SelectedIndexChanged);
      this.comboBox10.FlatStyle = FlatStyle.Flat;
      this.comboBox10.FormattingEnabled = true;
      this.comboBox10.Location = new Point(62, 180);
      this.comboBox10.Name = "comboBox10";
      this.comboBox10.Size = new Size(217, 21);
      this.comboBox10.TabIndex = 19;
      this.comboBox10.SelectedIndexChanged += new EventHandler(this.comboBox10_SelectedIndexChanged);
      this.comboBox9.FlatStyle = FlatStyle.Flat;
      this.comboBox9.FormattingEnabled = true;
      this.comboBox9.Location = new Point(62, 153);
      this.comboBox9.Name = "comboBox9";
      this.comboBox9.Size = new Size(217, 21);
      this.comboBox9.TabIndex = 18;
      this.comboBox9.SelectedIndexChanged += new EventHandler(this.comboBox9_SelectedIndexChanged);
      this.comboBox8.FlatStyle = FlatStyle.Flat;
      this.comboBox8.FormattingEnabled = true;
      this.comboBox8.Location = new Point(62, 126);
      this.comboBox8.Name = "comboBox8";
      this.comboBox8.Size = new Size(217, 21);
      this.comboBox8.TabIndex = 17;
      this.comboBox8.SelectedIndexChanged += new EventHandler(this.comboBox8_SelectedIndexChanged);
      this.label99.AutoSize = true;
      this.label99.Location = new Point(16, 128);
      this.label99.Name = "label99";
      this.label99.Size = new Size(40, 13);
      this.label99.TabIndex = 16;
      this.label99.Text = "Seal 4:";
      this.comboBox7.FlatStyle = FlatStyle.Flat;
      this.comboBox7.FormattingEnabled = true;
      this.comboBox7.Location = new Point(62, 99);
      this.comboBox7.Name = "comboBox7";
      this.comboBox7.Size = new Size(217, 21);
      this.comboBox7.TabIndex = 13;
      this.comboBox7.SelectedIndexChanged += new EventHandler(this.comboBox7_SelectedIndexChanged);
      this.label98.AutoSize = true;
      this.label98.Location = new Point(16, 101);
      this.label98.Name = "label98";
      this.label98.Size = new Size(40, 13);
      this.label98.TabIndex = 12;
      this.label98.Text = "Seal 3:";
      this.comboBox6.FlatStyle = FlatStyle.Flat;
      this.comboBox6.FormattingEnabled = true;
      this.comboBox6.Location = new Point(62, 72);
      this.comboBox6.Name = "comboBox6";
      this.comboBox6.Size = new Size(217, 21);
      this.comboBox6.TabIndex = 9;
      this.comboBox6.SelectedIndexChanged += new EventHandler(this.comboBox6_SelectedIndexChanged);
      this.label97.AutoSize = true;
      this.label97.Location = new Point(16, 76);
      this.label97.Name = "label97";
      this.label97.Size = new Size(40, 13);
      this.label97.TabIndex = 8;
      this.label97.Text = "Seal 2:";
      this.comboBox5.FlatStyle = FlatStyle.Flat;
      this.comboBox5.FormattingEnabled = true;
      this.comboBox5.Location = new Point(62, 45);
      this.comboBox5.Name = "comboBox5";
      this.comboBox5.Size = new Size(217, 21);
      this.comboBox5.TabIndex = 5;
      this.comboBox5.SelectedIndexChanged += new EventHandler(this.comboBox5_SelectedIndexChanged);
      this.label96.AutoSize = true;
      this.label96.Location = new Point(16, 49);
      this.label96.Name = "label96";
      this.label96.Size = new Size(40, 13);
      this.label96.TabIndex = 4;
      this.label96.Text = "Seal 1:";
      this.comboBox3.FlatStyle = FlatStyle.Flat;
      this.comboBox3.FormattingEnabled = true;
      this.comboBox3.Location = new Point(62, 18);
      this.comboBox3.Name = "comboBox3";
      this.comboBox3.Size = new Size(217, 21);
      this.comboBox3.TabIndex = 1;
      this.comboBox3.SelectedIndexChanged += new EventHandler(this.comboBox3_SelectedIndexChanged);
      this.label95.AutoSize = true;
      this.label95.Location = new Point(16, 21);
      this.label95.Name = "label95";
      this.label95.Size = new Size(40, 13);
      this.label95.TabIndex = 0;
      this.label95.Text = "Seal 0:";
      this.groupBox13.Controls.Add((Control) this.pictureBox22);
      this.groupBox13.Controls.Add((Control) this.pictureBox21);
      this.groupBox13.Controls.Add((Control) this.pictureBox20);
      this.groupBox13.Controls.Add((Control) this.pictureBox19);
      this.groupBox13.Controls.Add((Control) this.pictureBox18);
      this.groupBox13.Controls.Add((Control) this.pictureBox17);
      this.groupBox13.Controls.Add((Control) this.pictureBox16);
      this.groupBox13.Controls.Add((Control) this.pictureBox15);
      this.groupBox13.Controls.Add((Control) this.pictureBox14);
      this.groupBox13.Controls.Add((Control) this.pictureBox13);
      this.groupBox13.Controls.Add((Control) this.textBox79);
      this.groupBox13.Controls.Add((Control) this.label79);
      this.groupBox13.Controls.Add((Control) this.textBox78);
      this.groupBox13.Controls.Add((Control) this.label78);
      this.groupBox13.Controls.Add((Control) this.textBox77);
      this.groupBox13.Controls.Add((Control) this.label77);
      this.groupBox13.Controls.Add((Control) this.textBox76);
      this.groupBox13.Controls.Add((Control) this.label76);
      this.groupBox13.Controls.Add((Control) this.textBox75);
      this.groupBox13.Controls.Add((Control) this.label75);
      this.groupBox13.Controls.Add((Control) this.textBox74);
      this.groupBox13.Controls.Add((Control) this.label74);
      this.groupBox13.Controls.Add((Control) this.textBox73);
      this.groupBox13.Controls.Add((Control) this.label73);
      this.groupBox13.Controls.Add((Control) this.textBox72);
      this.groupBox13.Controls.Add((Control) this.label72);
      this.groupBox13.Controls.Add((Control) this.textBox71);
      this.groupBox13.Controls.Add((Control) this.label71);
      this.groupBox13.Controls.Add((Control) this.textBox70);
      this.groupBox13.Controls.Add((Control) this.label70);
      this.groupBox13.Controls.Add((Control) this.textBox69);
      this.groupBox13.Controls.Add((Control) this.label69);
      this.groupBox13.Controls.Add((Control) this.textBox68);
      this.groupBox13.Controls.Add((Control) this.label68);
      this.groupBox13.Controls.Add((Control) this.textBox67);
      this.groupBox13.Controls.Add((Control) this.label67);
      this.groupBox13.Controls.Add((Control) this.textBox66);
      this.groupBox13.Controls.Add((Control) this.label66);
      this.groupBox13.Controls.Add((Control) this.textBox65);
      this.groupBox13.Controls.Add((Control) this.label65);
      this.groupBox13.Controls.Add((Control) this.textBox64);
      this.groupBox13.Controls.Add((Control) this.label64);
      this.groupBox13.Controls.Add((Control) this.textBox63);
      this.groupBox13.Controls.Add((Control) this.label63);
      this.groupBox13.Controls.Add((Control) this.textBox62);
      this.groupBox13.Controls.Add((Control) this.label62);
      this.groupBox13.Controls.Add((Control) this.textBox61);
      this.groupBox13.Controls.Add((Control) this.label61);
      this.groupBox13.Controls.Add((Control) this.textBox60);
      this.groupBox13.Controls.Add((Control) this.label60);
      this.groupBox13.Location = new Point(3, 3);
      this.groupBox13.Name = "groupBox13";
      this.groupBox13.Size = new Size(309, 295);
      this.groupBox13.TabIndex = 0;
      this.groupBox13.TabStop = false;
      this.groupBox13.Text = "Rare Options";
      this.pictureBox22.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox22.Location = new Point(135, 254);
      this.pictureBox22.Name = "pictureBox22";
      this.pictureBox22.Size = new Size(22, 22);
      this.pictureBox22.TabIndex = 99;
      this.pictureBox22.TabStop = false;
      this.toolTip1.SetToolTip((Control) this.pictureBox22, "Search Option");
      this.pictureBox22.Click += new EventHandler(this.pictureBox22_Click);
      this.pictureBox22.MouseLeave += new EventHandler(this.pictureBox22_MouseLeave);
      this.pictureBox22.MouseMove += new MouseEventHandler(this.pictureBox22_MouseMove);
      this.pictureBox21.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox21.Location = new Point(135, 228);
      this.pictureBox21.Name = "pictureBox21";
      this.pictureBox21.Size = new Size(22, 22);
      this.pictureBox21.TabIndex = 98;
      this.pictureBox21.TabStop = false;
      this.toolTip1.SetToolTip((Control) this.pictureBox21, "Search Option");
      this.pictureBox21.Click += new EventHandler(this.pictureBox21_Click);
      this.pictureBox21.MouseLeave += new EventHandler(this.pictureBox21_MouseLeave);
      this.pictureBox21.MouseMove += new MouseEventHandler(this.pictureBox21_MouseMove);
      this.pictureBox20.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox20.Location = new Point(135, 202);
      this.pictureBox20.Name = "pictureBox20";
      this.pictureBox20.Size = new Size(22, 22);
      this.pictureBox20.TabIndex = 97;
      this.pictureBox20.TabStop = false;
      this.toolTip1.SetToolTip((Control) this.pictureBox20, "Search Option");
      this.pictureBox20.Click += new EventHandler(this.pictureBox20_Click);
      this.pictureBox20.MouseLeave += new EventHandler(this.pictureBox20_MouseLeave);
      this.pictureBox20.MouseMove += new MouseEventHandler(this.pictureBox20_MouseMove);
      this.pictureBox19.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox19.Location = new Point(135, 175);
      this.pictureBox19.Name = "pictureBox19";
      this.pictureBox19.Size = new Size(22, 22);
      this.pictureBox19.TabIndex = 96;
      this.pictureBox19.TabStop = false;
      this.toolTip1.SetToolTip((Control) this.pictureBox19, "Search Option");
      this.pictureBox19.Click += new EventHandler(this.pictureBox19_Click);
      this.pictureBox19.MouseLeave += new EventHandler(this.pictureBox19_MouseLeave);
      this.pictureBox19.MouseMove += new MouseEventHandler(this.pictureBox19_MouseMove);
      this.pictureBox18.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox18.Location = new Point(135, 149);
      this.pictureBox18.Name = "pictureBox18";
      this.pictureBox18.Size = new Size(22, 22);
      this.pictureBox18.TabIndex = 95;
      this.pictureBox18.TabStop = false;
      this.toolTip1.SetToolTip((Control) this.pictureBox18, "Search Option");
      this.pictureBox18.Click += new EventHandler(this.pictureBox18_Click);
      this.pictureBox18.MouseLeave += new EventHandler(this.pictureBox18_MouseLeave);
      this.pictureBox18.MouseMove += new MouseEventHandler(this.pictureBox18_MouseMove);
      this.pictureBox17.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox17.Location = new Point(135, 123);
      this.pictureBox17.Name = "pictureBox17";
      this.pictureBox17.Size = new Size(22, 22);
      this.pictureBox17.TabIndex = 94;
      this.pictureBox17.TabStop = false;
      this.toolTip1.SetToolTip((Control) this.pictureBox17, "Search Option");
      this.pictureBox17.Click += new EventHandler(this.pictureBox17_Click);
      this.pictureBox17.MouseLeave += new EventHandler(this.pictureBox17_MouseLeave);
      this.pictureBox17.MouseMove += new MouseEventHandler(this.pictureBox17_MouseMove);
      this.pictureBox16.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox16.Location = new Point(135, 97);
      this.pictureBox16.Name = "pictureBox16";
      this.pictureBox16.Size = new Size(22, 22);
      this.pictureBox16.TabIndex = 93;
      this.pictureBox16.TabStop = false;
      this.toolTip1.SetToolTip((Control) this.pictureBox16, "Search Option");
      this.pictureBox16.Click += new EventHandler(this.pictureBox16_Click);
      this.pictureBox16.MouseLeave += new EventHandler(this.pictureBox16_MouseLeave);
      this.pictureBox16.MouseMove += new MouseEventHandler(this.pictureBox16_MouseMove);
      this.pictureBox15.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox15.Location = new Point(135, 71);
      this.pictureBox15.Name = "pictureBox15";
      this.pictureBox15.Size = new Size(22, 22);
      this.pictureBox15.TabIndex = 92;
      this.pictureBox15.TabStop = false;
      this.toolTip1.SetToolTip((Control) this.pictureBox15, "Search Option");
      this.pictureBox15.Click += new EventHandler(this.pictureBox15_Click);
      this.pictureBox15.MouseLeave += new EventHandler(this.pictureBox15_MouseLeave);
      this.pictureBox15.MouseMove += new MouseEventHandler(this.pictureBox15_MouseMove);
      this.pictureBox14.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox14.Location = new Point(135, 45);
      this.pictureBox14.Name = "pictureBox14";
      this.pictureBox14.Size = new Size(22, 22);
      this.pictureBox14.TabIndex = 91;
      this.pictureBox14.TabStop = false;
      this.toolTip1.SetToolTip((Control) this.pictureBox14, "Search Option");
      this.pictureBox14.Click += new EventHandler(this.pictureBox14_Click);
      this.pictureBox14.MouseLeave += new EventHandler(this.pictureBox14_MouseLeave);
      this.pictureBox14.MouseMove += new MouseEventHandler(this.pictureBox14_MouseMove);
      this.pictureBox13.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox13.Location = new Point(135, 19);
      this.pictureBox13.Name = "pictureBox13";
      this.pictureBox13.Size = new Size(22, 22);
      this.pictureBox13.TabIndex = 90;
      this.pictureBox13.TabStop = false;
      this.toolTip1.SetToolTip((Control) this.pictureBox13, "Search Option");
      this.pictureBox13.Click += new EventHandler(this.pictureBox13_Click);
      this.pictureBox13.MouseLeave += new EventHandler(this.pictureBox13_MouseLeave);
      this.pictureBox13.MouseMove += new MouseEventHandler(this.pictureBox13_MouseMove);
      this.textBox79.BorderStyle = BorderStyle.FixedSingle;
      this.textBox79.Location = new Point(234, 257);
      this.textBox79.Name = "textBox79";
      this.textBox79.Size = new Size(61, 20);
      this.textBox79.TabIndex = 78;
      this.label79.AutoSize = true;
      this.label79.Location = new Point(181, 259);
      this.label79.Name = "label79";
      this.label79.Size = new Size(47, 13);
      this.label79.TabIndex = 79;
      this.label79.Text = "Chance:";
      this.textBox78.BorderStyle = BorderStyle.FixedSingle;
      this.textBox78.Location = new Point(234, 231);
      this.textBox78.Name = "textBox78";
      this.textBox78.Size = new Size(61, 20);
      this.textBox78.TabIndex = 76;
      this.label78.AutoSize = true;
      this.label78.Location = new Point(181, 233);
      this.label78.Name = "label78";
      this.label78.Size = new Size(47, 13);
      this.label78.TabIndex = 77;
      this.label78.Text = "Chance:";
      this.textBox77.BorderStyle = BorderStyle.FixedSingle;
      this.textBox77.Location = new Point(234, 205);
      this.textBox77.Name = "textBox77";
      this.textBox77.Size = new Size(61, 20);
      this.textBox77.TabIndex = 74;
      this.label77.AutoSize = true;
      this.label77.Location = new Point(181, 207);
      this.label77.Name = "label77";
      this.label77.Size = new Size(47, 13);
      this.label77.TabIndex = 75;
      this.label77.Text = "Chance:";
      this.textBox76.BorderStyle = BorderStyle.FixedSingle;
      this.textBox76.Location = new Point(234, 179);
      this.textBox76.Name = "textBox76";
      this.textBox76.Size = new Size(61, 20);
      this.textBox76.TabIndex = 72;
      this.label76.AutoSize = true;
      this.label76.Location = new Point(181, 181);
      this.label76.Name = "label76";
      this.label76.Size = new Size(47, 13);
      this.label76.TabIndex = 73;
      this.label76.Text = "Chance:";
      this.textBox75.BorderStyle = BorderStyle.FixedSingle;
      this.textBox75.Location = new Point(234, 153);
      this.textBox75.Name = "textBox75";
      this.textBox75.Size = new Size(61, 20);
      this.textBox75.TabIndex = 70;
      this.label75.AutoSize = true;
      this.label75.Location = new Point(181, 155);
      this.label75.Name = "label75";
      this.label75.Size = new Size(47, 13);
      this.label75.TabIndex = 71;
      this.label75.Text = "Chance:";
      this.textBox74.BorderStyle = BorderStyle.FixedSingle;
      this.textBox74.Location = new Point(234, 126);
      this.textBox74.Name = "textBox74";
      this.textBox74.Size = new Size(61, 20);
      this.textBox74.TabIndex = 68;
      this.label74.AutoSize = true;
      this.label74.Location = new Point(181, 128);
      this.label74.Name = "label74";
      this.label74.Size = new Size(47, 13);
      this.label74.TabIndex = 69;
      this.label74.Text = "Chance:";
      this.textBox73.BorderStyle = BorderStyle.FixedSingle;
      this.textBox73.Location = new Point(234, 98);
      this.textBox73.Name = "textBox73";
      this.textBox73.Size = new Size(61, 20);
      this.textBox73.TabIndex = 66;
      this.label73.AutoSize = true;
      this.label73.Location = new Point(181, 100);
      this.label73.Name = "label73";
      this.label73.Size = new Size(47, 13);
      this.label73.TabIndex = 67;
      this.label73.Text = "Chance:";
      this.textBox72.BorderStyle = BorderStyle.FixedSingle;
      this.textBox72.Location = new Point(234, 72);
      this.textBox72.Name = "textBox72";
      this.textBox72.Size = new Size(61, 20);
      this.textBox72.TabIndex = 64;
      this.label72.AutoSize = true;
      this.label72.Location = new Point(181, 74);
      this.label72.Name = "label72";
      this.label72.Size = new Size(47, 13);
      this.label72.TabIndex = 65;
      this.label72.Text = "Chance:";
      this.textBox71.BorderStyle = BorderStyle.FixedSingle;
      this.textBox71.Location = new Point(234, 46);
      this.textBox71.Name = "textBox71";
      this.textBox71.Size = new Size(61, 20);
      this.textBox71.TabIndex = 62;
      this.label71.AutoSize = true;
      this.label71.Location = new Point(181, 48);
      this.label71.Name = "label71";
      this.label71.Size = new Size(47, 13);
      this.label71.TabIndex = 63;
      this.label71.Text = "Chance:";
      this.textBox70.BorderStyle = BorderStyle.FixedSingle;
      this.textBox70.Location = new Point(234, 20);
      this.textBox70.Name = "textBox70";
      this.textBox70.Size = new Size(61, 20);
      this.textBox70.TabIndex = 60;
      this.textBox70.TextChanged += new EventHandler(this.textBox70_TextChanged);
      this.label70.AutoSize = true;
      this.label70.Location = new Point(181, 22);
      this.label70.Name = "label70";
      this.label70.Size = new Size(47, 13);
      this.label70.TabIndex = 61;
      this.label70.Text = "Chance:";
      this.textBox69.BorderStyle = BorderStyle.FixedSingle;
      this.textBox69.Location = new Point(68, (int) byte.MaxValue);
      this.textBox69.Name = "textBox69";
      this.textBox69.Size = new Size(61, 20);
      this.textBox69.TabIndex = 58;
      this.label69.AutoSize = true;
      this.label69.Location = new Point(15, 257);
      this.label69.Name = "label69";
      this.label69.Size = new Size(47, 13);
      this.label69.TabIndex = 59;
      this.label69.Text = "Option9:";
      this.textBox68.BorderStyle = BorderStyle.FixedSingle;
      this.textBox68.Location = new Point(68, 229);
      this.textBox68.Name = "textBox68";
      this.textBox68.Size = new Size(61, 20);
      this.textBox68.TabIndex = 56;
      this.label68.AutoSize = true;
      this.label68.Location = new Point(15, 231);
      this.label68.Name = "label68";
      this.label68.Size = new Size(47, 13);
      this.label68.TabIndex = 57;
      this.label68.Text = "Option8:";
      this.textBox67.BorderStyle = BorderStyle.FixedSingle;
      this.textBox67.Location = new Point(68, 203);
      this.textBox67.Name = "textBox67";
      this.textBox67.Size = new Size(61, 20);
      this.textBox67.TabIndex = 54;
      this.label67.AutoSize = true;
      this.label67.Location = new Point(15, 205);
      this.label67.Name = "label67";
      this.label67.Size = new Size(47, 13);
      this.label67.TabIndex = 55;
      this.label67.Text = "Option7:";
      this.textBox66.BorderStyle = BorderStyle.FixedSingle;
      this.textBox66.Location = new Point(68, 177);
      this.textBox66.Name = "textBox66";
      this.textBox66.Size = new Size(61, 20);
      this.textBox66.TabIndex = 52;
      this.label66.AutoSize = true;
      this.label66.Location = new Point(15, 179);
      this.label66.Name = "label66";
      this.label66.Size = new Size(47, 13);
      this.label66.TabIndex = 53;
      this.label66.Text = "Option6:";
      this.textBox65.BorderStyle = BorderStyle.FixedSingle;
      this.textBox65.Location = new Point(68, 151);
      this.textBox65.Name = "textBox65";
      this.textBox65.Size = new Size(61, 20);
      this.textBox65.TabIndex = 50;
      this.label65.AutoSize = true;
      this.label65.Location = new Point(15, 153);
      this.label65.Name = "label65";
      this.label65.Size = new Size(47, 13);
      this.label65.TabIndex = 51;
      this.label65.Text = "Option5:";
      this.textBox64.BorderStyle = BorderStyle.FixedSingle;
      this.textBox64.Location = new Point(68, 124);
      this.textBox64.Name = "textBox64";
      this.textBox64.Size = new Size(61, 20);
      this.textBox64.TabIndex = 48;
      this.label64.AutoSize = true;
      this.label64.Location = new Point(15, 126);
      this.label64.Name = "label64";
      this.label64.Size = new Size(47, 13);
      this.label64.TabIndex = 49;
      this.label64.Text = "Option4:";
      this.textBox63.BorderStyle = BorderStyle.FixedSingle;
      this.textBox63.Location = new Point(68, 98);
      this.textBox63.Name = "textBox63";
      this.textBox63.Size = new Size(61, 20);
      this.textBox63.TabIndex = 46;
      this.label63.AutoSize = true;
      this.label63.Location = new Point(15, 100);
      this.label63.Name = "label63";
      this.label63.Size = new Size(47, 13);
      this.label63.TabIndex = 47;
      this.label63.Text = "Option3:";
      this.textBox62.BorderStyle = BorderStyle.FixedSingle;
      this.textBox62.Location = new Point(68, 72);
      this.textBox62.Name = "textBox62";
      this.textBox62.Size = new Size(61, 20);
      this.textBox62.TabIndex = 44;
      this.label62.AutoSize = true;
      this.label62.Location = new Point(15, 74);
      this.label62.Name = "label62";
      this.label62.Size = new Size(47, 13);
      this.label62.TabIndex = 45;
      this.label62.Text = "Option2:";
      this.textBox61.BorderStyle = BorderStyle.FixedSingle;
      this.textBox61.Location = new Point(68, 46);
      this.textBox61.Name = "textBox61";
      this.textBox61.Size = new Size(61, 20);
      this.textBox61.TabIndex = 42;
      this.label61.AutoSize = true;
      this.label61.Location = new Point(15, 48);
      this.label61.Name = "label61";
      this.label61.Size = new Size(47, 13);
      this.label61.TabIndex = 43;
      this.label61.Text = "Option1:";
      this.textBox60.BorderStyle = BorderStyle.FixedSingle;
      this.textBox60.Location = new Point(68, 20);
      this.textBox60.Name = "textBox60";
      this.textBox60.Size = new Size(61, 20);
      this.textBox60.TabIndex = 40;
      this.label60.AutoSize = true;
      this.label60.Location = new Point(15, 22);
      this.label60.Name = "label60";
      this.label60.Size = new Size(47, 13);
      this.label60.TabIndex = 41;
      this.label60.Text = "Option0:";
      this.clbFlagTest.BackColor = SystemColors.Control;
      this.clbFlagTest.CheckOnClick = true;
      this.clbFlagTest.Location = new Point(6, 17);
      this.clbFlagTest.MultiColumn = true;
      this.clbFlagTest.Name = "clbFlagTest";
      this.clbFlagTest.Size = new Size(246, 574);
      this.clbFlagTest.TabIndex = 15;
      this.clbFlagTest.SelectedIndexChanged += new EventHandler(this.clbFlagTest_SelectedIndexChanged_1);
      this.textBox4.BorderStyle = BorderStyle.FixedSingle;
      this.textBox4.Location = new Point(589, 2);
      this.textBox4.Name = "textBox4";
      this.textBox4.Size = new Size(31, 20);
      this.textBox4.TabIndex = 4;
      this.textBox4.Visible = false;
      this.label4.AutoSize = true;
      this.label4.Location = new Point(540, 6);
      this.label4.Name = "label4";
      this.label4.Size = new Size(43, 13);
      this.label4.TabIndex = 10;
      this.label4.Text = "Enable:";
      this.label4.Visible = false;
      this.button2.FlatStyle = FlatStyle.Flat;
      this.button2.Location = new Point(1126, 669);
      this.button2.Name = "button2";
      this.button2.Size = new Size(100, 23);
      this.button2.TabIndex = 34;
      this.button2.Text = "Save";
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.toolTip1.Tag = (object) "";
      this.toolTip1.ToolTipTitle = "Information";
      this.groupBox18.Controls.Add((Control) this.clbFlagTest);
      this.groupBox18.Location = new Point(1249, 42);
      this.groupBox18.Name = "groupBox18";
      this.groupBox18.Size = new Size(260, 617);
      this.groupBox18.TabIndex = 35;
      this.groupBox18.TabStop = false;
      this.groupBox18.Text = "Flag Builder";
      this.groupBox18.Visible = false;
      this.textBox12.BorderStyle = BorderStyle.FixedSingle;
      this.textBox12.Location = new Point(43, 19);
      this.textBox12.Name = "textBox12";
      this.textBox12.Size = new Size(216, 20);
      this.textBox12.TabIndex = 20;
      this.textBox12.TextChanged += new EventHandler(this.textBox12_TextChanged);
      this.label7.AutoSize = true;
      this.label7.Location = new Point(6, 21);
      this.label7.Name = "label7";
      this.label7.Size = new Size(31, 13);
      this.label7.TabIndex = 21;
      this.label7.Text = "Text:";
      this.groupBox5.Controls.Add((Control) this.label105);
      this.groupBox5.Controls.Add((Control) this.textBox95);
      this.groupBox5.Controls.Add((Control) this.checkedListBox2);
      this.groupBox5.Controls.Add((Control) this.label7);
      this.groupBox5.Controls.Add((Control) this.textBox12);
      this.groupBox5.Location = new Point(12, 27);
      this.groupBox5.Name = "groupBox5";
      this.groupBox5.Size = new Size(265, 135);
      this.groupBox5.TabIndex = 32;
      this.groupBox5.TabStop = false;
      this.groupBox5.Text = "Search";
      this.label105.AutoSize = true;
      this.label105.Location = new Point(6, 108);
      this.label105.Name = "label105";
      this.label105.Size = new Size(102, 13);
      this.label105.TabIndex = 44;
      this.label105.Text = "Search above level:";
      this.textBox95.BorderStyle = BorderStyle.FixedSingle;
      this.textBox95.Location = new Point(114, 105);
      this.textBox95.Name = "textBox95";
      this.textBox95.Size = new Size(42, 20);
      this.textBox95.TabIndex = 43;
      this.textBox95.TextChanged += new EventHandler(this.textBox95_TextChanged);
      this.checkedListBox2.Anchor = AnchorStyles.None;
      this.checkedListBox2.BackColor = SystemColors.Control;
      this.checkedListBox2.BorderStyle = BorderStyle.None;
      this.checkedListBox2.CheckOnClick = true;
      this.checkedListBox2.ColumnWidth = 70;
      this.checkedListBox2.FormattingEnabled = true;
      this.checkedListBox2.IntegralHeight = false;
      this.checkedListBox2.Location = new Point(9, 48);
      this.checkedListBox2.MultiColumn = true;
      this.checkedListBox2.Name = "checkedListBox2";
      this.checkedListBox2.Size = new Size(250, 52);
      this.checkedListBox2.TabIndex = 42;
      this.checkedListBox2.SelectedIndexChanged += new EventHandler(this.checkedListBox2_SelectedIndexChanged);
      this.timer1.Enabled = true;
      this.timer1.Interval = 1;
      this.timer1.Tick += new EventHandler(this.timer1_Tick);
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(1239, 708);
      this.Controls.Add((Control) this.groupBox18);
      this.Controls.Add((Control) this.button2);
      this.Controls.Add((Control) this.tabControl1);
      this.Controls.Add((Control) this.groupBox5);
      this.Controls.Add((Control) this.groupBox3);
      this.Controls.Add((Control) this.textBox4);
      this.Controls.Add((Control) this.label4);
      this.Controls.Add((Control) this.menuStrip1);
      this.FormBorderStyle = FormBorderStyle.FixedSingle;
      this.MainMenuStrip = this.menuStrip1;
      this.MaximizeBox = false;
      this.Name = nameof (ItemEditor);
      this.StartPosition = FormStartPosition.CenterScreen;
      this.Text = "Item Editor EP4";
      this.Load += new EventHandler(this.Exporter_Item_Load);
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.groupBox3.ResumeLayout(false);
      this.tabControl1.ResumeLayout(false);
      this.tabPage1.ResumeLayout(false);
      this.groupBox12.ResumeLayout(false);
      this.groupBox12.PerformLayout();
      this.groupBox20.ResumeLayout(false);
      this.groupBox20.PerformLayout();
      this.slideLeftRight.EndInit();
      this.slideUpDown.EndInit();
      this.slideZoom.EndInit();
      this.groupBox19.ResumeLayout(false);
      this.groupBox19.PerformLayout();
      this.groupBox16.ResumeLayout(false);
      this.groupBox16.PerformLayout();
      this.groupBox14.ResumeLayout(false);
      this.groupBox14.PerformLayout();
      this.groupBox11.ResumeLayout(false);
      this.groupBox11.PerformLayout();
      this.groupBox10.ResumeLayout(false);
      this.groupBox10.PerformLayout();
      this.groupBox9.ResumeLayout(false);
      this.groupBox9.PerformLayout();
      ((ISupportInitialize) this.pictureBox1).EndInit();
      this.groupBox6.ResumeLayout(false);
      this.groupBox6.PerformLayout();
      this.groupBox4.ResumeLayout(false);
      this.groupBox4.PerformLayout();
      this.groupBox2.ResumeLayout(false);
      this.groupBox2.PerformLayout();
      ((ISupportInitialize) this.pictureBox23).EndInit();
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.tabPage2.ResumeLayout(false);
      this.groupBox7.ResumeLayout(false);
      this.groupBox7.PerformLayout();
      ((ISupportInitialize) this.pictureBox12).EndInit();
      ((ISupportInitialize) this.pictureBox11).EndInit();
      ((ISupportInitialize) this.pictureBox10).EndInit();
      ((ISupportInitialize) this.pictureBox9).EndInit();
      ((ISupportInitialize) this.pictureBox8).EndInit();
      ((ISupportInitialize) this.pictureBox7).EndInit();
      ((ISupportInitialize) this.pictureBox6).EndInit();
      ((ISupportInitialize) this.pictureBox5).EndInit();
      ((ISupportInitialize) this.pictureBox4).EndInit();
      ((ISupportInitialize) this.pictureBox3).EndInit();
      this.groupBox8.ResumeLayout(false);
      this.groupBox8.PerformLayout();
      this.tabPage3.ResumeLayout(false);
      this.groupBox17.ResumeLayout(false);
      this.groupBox17.PerformLayout();
      this.groupBox13.ResumeLayout(false);
      this.groupBox13.PerformLayout();
      ((ISupportInitialize) this.pictureBox22).EndInit();
      ((ISupportInitialize) this.pictureBox21).EndInit();
      ((ISupportInitialize) this.pictureBox20).EndInit();
      ((ISupportInitialize) this.pictureBox19).EndInit();
      ((ISupportInitialize) this.pictureBox18).EndInit();
      ((ISupportInitialize) this.pictureBox17).EndInit();
      ((ISupportInitialize) this.pictureBox16).EndInit();
      ((ISupportInitialize) this.pictureBox15).EndInit();
      ((ISupportInitialize) this.pictureBox14).EndInit();
      ((ISupportInitialize) this.pictureBox13).EndInit();
      this.groupBox18.ResumeLayout(false);
      this.groupBox5.ResumeLayout(false);
      this.groupBox5.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();
    }

    private void textBox5_TextChanged(object sender, EventArgs e)
    {
    }

    private void panel3DView_Paint(object sender, PaintEventArgs e)
    {
    }
  }
}
