// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.AffinityEditor
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using LcDevPack_TeamDamonA.Properties;
using LcDevPack_TeamDamonA.Tools.MemoryWorker.Affinity_EP4_By_Assasin;
using MySqlConnector;
using StringExporter;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools
{
  public class AffinityEditor : Form
  {
    public static Connection connection = new Connection();
    private string Host = AffinityEditor.connection.Settings.SqlHost;
    private string User = AffinityEditor.connection.Settings.SqlUser;
    private string Password = AffinityEditor.connection.Settings.SqlPassword;
    private string Database = AffinityEditor.connection.Settings.SqlDatabase;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    private ExportLodHandle exportLodHandle = new ExportLodHandle();
    public static string ISO = "ISO-8859-1";
    public string rowName = "a_index";
    public string[] menuArray = new string[2]
    {
      "a_index",
      "a_name"
    };
    public string[] menuArrayTHA = new string[2]
    {
      "a_index",
      "a_name_thai"
    };
    private string language = AffinityEditor.connection.Settings.Language;
    private string Episode = AffinityEditor.connection.Settings.Episode;
    public List<string> MenuList = new List<string>();
    public List<string> MenuListSearch = new List<string>();
    private IContainer components = (IContainer) null;
    public string name;
    public int index;
    private MenuStrip menuStrip1;
    private ToolStripMenuItem gToolStripMenuItem;
    private ToolStripMenuItem exportAffinitylodToolStripMenuItem;
    private ToolStripMenuItem exportStrAffinitylodToolStripMenuItem;
    private GroupBox groupBox1;
    private GroupBox groupBox2;
    private ListBox listBox1;
    private TextBox textBox1;
    private GroupBox groupBox3;
    private Label label1;
    private TextBox textBox2;
    private CheckBox checkBox1;
    private Label label2;
    private GroupBox groupBox4;
    private Label label3;
    private TextBox textBox4;
    private PictureBox pictureBox1;
    private Label label4;
    private Label label5;
    private Label label6;
    private Label label7;
    private Label label8;
    private Label label9;
    private Label label10;
    private PictureBox pictureBox2;
    private Label label11;
    private PictureBox pictureBox3;
    private TextBox textBox3;
    private TextBox textBox7;
    private TextBox textBox6;
    private TextBox textBox5;
    private TextBox textBox8;
    private TextBox textBox9;
    private TextBox textBox10;
    private TextBox textBox11;
    private TextBox textBox13;
    private TextBox textBox12;
    private TextBox textBox17;
    private TextBox textBox16;
    private TextBox textBox15;
    private TextBox textBox14;
    private TextBox textBox21;
    private TextBox textBox20;
    private TextBox textBox19;
    private TextBox textBox18;
    private Label label12;
    private PictureBox pictureBox4;
    private PictureBox pictureBox5;
    private GroupBox groupBox5;
    private DataGridView dataGridView1;
    private GroupBox groupBox6;
    private DataGridView dataGridView2;
    private GroupBox groupBox7;
    private DataGridView dataGridView3;
    private GroupBox groupBox8;
    private DataGridView dataGridView4;
    private Button button2;
    private Button button1;
    private GroupBox groupBox9;
    private TextBox textBox22;
    private Label label13;
    private Button button3;
    private DataGridView dataGridView5;
    private ToolStrip toolStrip1;
    private ToolStripButton toolStripButton1;
    private ToolStripSeparator toolStripSeparator1;
    private ToolStripButton toolStripButton2;
    private ToolStrip toolStrip2;
    private ToolStripButton toolStripButton3;
    private ToolStripSeparator toolStripSeparator2;
    private ToolStripButton toolStripButton4;
    private ToolStrip toolStrip3;
    private ToolStripButton toolStripButton5;
    private ToolStripSeparator toolStripSeparator3;
    private ToolStripButton toolStripButton6;
    private DataGridViewImageColumn dataGridViewImageColumn1;
    private DataGridViewTextBoxColumn Work_Type;
    private DataGridViewTextBoxColumn ItemID;
    private DataGridViewTextBoxColumn ItemName;
    private DataGridViewTextBoxColumn AffinityIdx;
    private DataGridViewTextBoxColumn AffinityPoints;
    private DataGridViewTextBoxColumn Enable;
    private TextBox textBox23;
    private Label label14;
    private PictureBox pictureBox7;
    private Label label15;
    private TextBox textBox24;
    private Button button4;
    private TextBox textBox25;
    private TextBox textBox26;
    private Label label16;
    private Label label17;
    private Label label18;
    private TextBox textBox27;
    private Label label19;
    private TextBox textBox28;
    private Label label20;
    private TextBox textBox29;
    private Button button6;
    private Button button9;
    private Button button12;
    private Button button5;
    private Button button7;
    private Button button8;
    private Label label21;
    private TextBox textBox30;
    private Label label22;
    private TextBox textBox31;
    private Label label23;
    private TextBox textBox32;
    private Label label24;
    private TextBox textBox33;
    private Button button10;
    private TextBox textBox34;
    private TextBox textBox35;
    private Label label25;
    private Label label26;
    private Label label27;
    private Label label28;
    private DataGridViewTextBoxColumn a_work_type;
    private DataGridViewTextBoxColumn QuestID;
    private DataGridViewTextBoxColumn QuestName;
    private DataGridViewTextBoxColumn a_affinity_idx;
    private DataGridViewTextBoxColumn AffinityPoints2;
    private DataGridViewTextBoxColumn a_enable;
    private Label label29;
    private Label label30;
    private TextBox textBox36;
    private Label label31;
    private TextBox textBox37;
    private Label label32;
    private TextBox textBox38;
    private Button button11;
    private TextBox textBox39;
    private Label label33;
    private Label label34;
    private TextBox textBox40;
    private TextBox textBox41;
    private Label label35;
    private Button button13;
    private Button button14;
    private Button button15;
    private PictureBox pictureBox8;
    private PictureBox pictureBox9;
    private TextBox textBox42;
    private TextBox textBox43;
    private TextBox textBox44;
    private TextBox textBox45;
    private DataGridViewTextBoxColumn Column2;
    private DataGridViewTextBoxColumn Column1;
    private DataGridViewTextBoxColumn Column3;
    private DataGridViewTextBoxColumn Column4;
    private DataGridViewTextBoxColumn Column5;
    private DataGridViewTextBoxColumn Column6;
    private DataGridViewTextBoxColumn a_id;
    private DataGridViewTextBoxColumn a_row;
    private DataGridViewTextBoxColumn a_col;
    private Label label37;
    private Label label38;
    private TextBox textBox46;
    private Label label39;
    private TextBox textBox47;
    private Label label40;
    private TextBox textBox48;
    private Button button16;
    private TextBox textBox49;
    private Label label41;
    private Label label42;
    private TextBox textBox50;
    private TextBox textBox51;
    private Label label43;
    private Button button17;
    private Button button18;
    private Button button19;
    private Label label44;
    private TextBox textBox52;
    private Label label45;
    private Label label46;
    private Label label47;
    private TextBox textBox53;
    private Label label48;
    private TextBox textBox54;
    private Label label49;
    private TextBox textBox55;
    private Label label50;
    private TextBox textBox56;
    private Label label51;
    private Label label52;
    private TextBox textBox57;
    private Button button20;
    private Label label53;
    private TextBox textBox58;
    private Label label54;
    private TextBox textBox59;
    private Label label55;
    private Label label56;
    private TextBox textBox60;
    private TextBox textBox61;
    private Label label57;
    private TextBox textBox62;
    private Label label58;
    private Button button22;
    private Button button23;
    private Button button24;
    private Label label59;
    private TextBox textBox63;
    private Button button21;
    private Label label60;
    private TextBox textBox64;
    private DataGridViewImageColumn dataGridViewImageGift;
    private DataGridViewTextBoxColumn Column16;
    private DataGridViewTextBoxColumn GiftItemName;
    private DataGridViewTextBoxColumn Column18;
    private DataGridViewTextBoxColumn Column15;
    private DataGridViewTextBoxColumn Column14;
    private DataGridViewTextBoxColumn Column17;
    private DataGridViewTextBoxColumn Column19;
    private DataGridViewTextBoxColumn Column20;
    private DataGridViewTextBoxColumn Column21;
    private DataGridViewTextBoxColumn Column22;
    private DataGridViewTextBoxColumn Column23;
    private PictureBox pictureBox10;
    private PictureBox pictureBox11;
    private TextBox textBox65;
    private TextBox textBox66;
    private TextBox textBox67;
    private TextBox textBox68;
    private TextBox textBox69;
    private TextBox textBox70;
    private Button button25;
    private DataGridViewTextBoxColumn Column7;
    private DataGridViewTextBoxColumn Column8;
    private DataGridViewTextBoxColumn Column13;
    private DataGridViewTextBoxColumn Column9;
    private DataGridViewTextBoxColumn Column10;
    private DataGridViewTextBoxColumn Column11;
    private DataGridViewTextBoxColumn Column12;
    private Label label36;

    public AffinityEditor() => this.InitializeComponent();

    public void LoadMisc()
    {
      if (this.textBox4.Text == "1")
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

    private void IniRead()
    {
      IniFile iniFile = new IniFile(Application.StartupPath + "\\Config\\Settings.cfg");
      this.textBox65.Text = iniFile.IniReadValue("## MYSQL", "SQL_HOST");
      this.textBox66.Text = iniFile.IniReadValue("## MYSQL", "SQL_USER");
      this.textBox67.Text = iniFile.IniReadValue("## MYSQL", "SQL_PASSWORD");
      this.textBox68.Text = iniFile.IniReadValue("## MYSQL", "SQL_DATABASE");
    }

    private void LoadListBox()
    {
      this.MenuList.Clear();
      if (this.language == "THA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayTHA, this.Host, this.User, this.Password, this.Database, "select a_index, a_name_thai from t_affinity ORDER BY a_index;");
      else
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, "select a_index, a_name from t_affinity WHERE a_enable = 1 ORDER BY a_index;");
    }

    public void SearchList(string searchString)
    {
      searchString = searchString.Replace("\\", "\\\\").Replace("'", "\\'");
      string lower = searchString.ToLower();
      string upper = searchString.ToUpper();
      string str = "";
      if (searchString.Length > 1)
        str = char.ToUpper(searchString[0]).ToString() + searchString.Substring(1);
      this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, "select a_index, a_name from t_affinity WHERE a_name LIKE '%" + searchString + "%' OR a_index LIKE '%" + searchString + "%' OR a_name LIKE '%" + lower + "%' OR a_index  LIKE '%" + lower + "%' OR a_name LIKE '%" + upper + "%' OR a_index LIKE '%" + upper + "%' OR a_name LIKE '%" + str + "%' OR a_index LIKE '%" + str + "%' ORDER BY a_index;");
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

    private void AffinityEditor_Load(object sender, EventArgs e)
    {
      this.LoadDG();
      this.LoadDG2();
      this.LoadDG3();
      this.LoadDG4();
      this.LoadDG5(this.textBox1.Text);
      this.LoadDG6();
      this.LoadDG7();
      this.LoadListBox();
      this.LoadMisc();
    }

    private void AffinityIcon()
    {
      string Query = "select a_index, a_name_usa, a_texture_id, a_texture_row, a_texture_col from t_affinity WHERE a_index ='" + this.textBox12.Text + "';";
      string[] rows = new string[5]
      {
        "a_index",
        "a_name_usa",
        "a_texture_id",
        "a_texture_row",
        "a_texture_col"
      };
      Query.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'");
      string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query, rows);
      this.textBox14.Text = strArray[0];
      this.label11.Text = strArray[1];
      this.textBox15.Text = strArray[2];
      this.textBox16.Text = strArray[3];
      this.textBox17.Text = strArray[4];
      if (!(this.textBox14.Text == ""))
        return;
      this.pictureBox2.Image = (Image) null;
      this.label11.Visible = true;
    }

    private void ItemIcon()
    {
      string Query = "select a_index, a_name_usa, a_texture_id, a_texture_row, a_texture_col from t_item WHERE a_index = '" + this.textBox10.Text + "';";
      string[] rows = new string[5]
      {
        "a_index",
        "a_name_usa",
        "a_texture_id",
        "a_texture_row",
        "a_texture_col"
      };
      Query.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'");
      string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query, rows);
      this.textBox18.Text = strArray[0];
      this.label12.Text = strArray[1];
      this.textBox19.Text = strArray[2];
      this.textBox20.Text = strArray[3];
      this.textBox21.Text = strArray[4];
      if (!(this.textBox18.Text == ""))
        return;
      this.pictureBox4.Image = (Image) null;
      this.label12.Visible = true;
    }

    private int GetID()
    {
      int result = -1;
      int.TryParse(this.listBox1.Text.Split(' ')[0], out result);
      return result;
    }

    private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (this.listBox1.SelectedIndex != -1)
        this.textBox1.Text = this.GetIndex().ToString();
      string Query = "select a_index, a_name, a_name_thai, a_maxvalue, a_enable, a_texture_id, a_texture_row, a_texture_col, a_nas, a_needlevel, a_needitemidx, a_needitemcount, a_affinity_idx, a_affinity_value from t_affinity WHERE a_index ='" + this.textBox1.Text + "';";
      string[] rows = new string[14]
      {
        "a_index",
        "a_name",
        "a_maxvalue",
        "a_enable",
        "a_texture_id",
        "a_texture_row",
        "a_texture_col",
        "a_nas",
        "a_needlevel",
        "a_needitemidx",
        "a_needitemcount",
        "a_affinity_idx",
        "a_affinity_value",
        "a_name_thai"
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
      if (this.language == "THA")
      {
        int ItemID = this.GetID();
        if (ItemID == -1)
          return;
        tAffinity2 tAffinity2 = AffinityList.List.Find((Predicate<tAffinity2>) (p => p.ItemID.Equals(ItemID)));
        if (tAffinity2 == null)
          return;
        this.textBox2.Text = tAffinity2.Name;
      }
      this.AffinityIcon();
      this.textBox23.Clear();
      this.textBox45.Clear();
      this.textBox25.Clear();
      this.textBox26.Text = "0";
      this.textBox27.Text = "1";
      this.textBox28.Text = "0";
      this.textBox29.Clear();
      this.textBox30.Clear();
      this.textBox31.Text = "2";
      this.textBox32.Text = "1";
      this.textBox34.Clear();
      this.textBox35.Text = "0";
      this.textBox36.Clear();
      this.textBox37.Text = "1";
      this.textBox38.Text = "1";
      this.textBox39.Text = "0";
      this.textBox41.Clear();
      this.textBox46.Clear();
      this.textBox47.Clear();
      this.textBox48.Text = "1";
      this.textBox49.Text = "0";
      this.textBox51.Text = "0";
      this.textBox52.Clear();
      this.textBox53.Text = "0";
      this.textBox54.Text = "0";
      this.textBox55.Text = "0";
      this.textBox56.Text = "0";
      this.textBox57.Text = "0";
      this.textBox59.Text = "0";
      this.textBox61.Text = "1";
      this.textBox62.Text = "0";
      this.textBox63.Clear();
      this.textBox64.Clear();
      this.pictureBox9.Image = (Image) null;
      this.pictureBox7.Image = (Image) null;
      this.pictureBox10.Image = (Image) null;
      this.pictureBox11.Image = (Image) null;
      this.LoadDG6();
      this.LoadDG7();
      this.LoadDG5(this.textBox1.Text);
      this.LoadDG4();
      this.LoadDG3();
      this.LoadDG2();
      this.LoadDG();
      this.ItemIcon();
      this.LoadMisc();
      try
      {
        this.pictureBox1.Image = (Image) this.databaseHandle.IconSkill1(int.Parse(this.textBox5.Text), int.Parse(this.textBox6.Text), int.Parse(this.textBox7.Text));
        this.pictureBox2.Image = (Image) this.databaseHandle.IconSkill1(int.Parse(this.textBox15.Text), int.Parse(this.textBox16.Text), int.Parse(this.textBox17.Text));
      }
      catch
      {
      }
      try
      {
        this.pictureBox4.Image = (Image) this.databaseHandle.IconItem(int.Parse(this.textBox19.Text), int.Parse(this.textBox20.Text), int.Parse(this.textBox21.Text));
      }
      catch
      {
      }
    }

        public void LoadDG()
        {
            this.dataGridView1.Rows.Clear();

            string query = "SELECT * FROM t_affinity_work WHERE a_work_type = 1 AND a_affinity_idx = '" + this.textBox1.Text + "'";

            using (var connection = new MySqlConnection(
                "datasource=" + this.Host +
                ";Port=3306;User ID=" + this.User +
                ";Password=" + this.Password +
                ";Database=" + this.Database +
                ";Charset=utf8mb4;SslMode=None;"))
            {
                connection.Open();

                using (var command = new MySqlCommand(query, connection))
                using (var reader = command.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        // Safe conversions for all column types
                        string workType = reader["a_work_type"].ToString();
                        string typeIdx = reader["a_type_idx"].ToString();
                        string affinityIdx = reader["a_affinity_idx"].ToString();
                        string value = reader["a_value"].ToString();
                        string enable = reader["a_enable"].ToString();
                        string id = reader["a_id"].ToString();
                        string row = reader["a_row"].ToString();
                        string col = reader["a_col"].ToString();

                        // Get mob name via helper
                        string mobName = this.databaseHandle.MobNameFast(Convert.ToInt32(typeIdx));

                        // Add a row to the DataGridView
                        this.dataGridView1.Rows.Add(
                            workType,     // a_work_type
                            typeIdx,      // a_type_idx
                            mobName,      // resolved mob name
                            affinityIdx,  // a_affinity_idx
                            value,        // a_value
                            enable,       // a_enable
                            id,           // a_id
                            row,          // a_row
                            col           // a_col
                        );
                    }
                }
            }
        }


        private void dataGridView1_CellClick(object sender, DataGridViewCellEventArgs e)
    {
      if (e.RowIndex < 0)
        return;
      DataGridViewRow row = this.dataGridView1.Rows[e.RowIndex];
      this.textBox36.Text = row.Cells["Column4"].Value.ToString();
      this.textBox37.Text = row.Cells["Column2"].Value.ToString();
      this.textBox39.Text = row.Cells["Column1"].Value.ToString();
      this.textBox41.Text = row.Cells["Column5"].Value.ToString();
      this.textBox38.Text = row.Cells["Column6"].Value.ToString();
      this.textBox44.Text = row.Cells["a_id"].Value.ToString();
      this.textBox43.Text = row.Cells["a_row"].Value.ToString();
      this.textBox42.Text = row.Cells["a_col"].Value.ToString();
      this.pictureBox9.Image = (Image) this.databaseHandle.IconCombo(int.Parse(this.textBox44.Text), int.Parse(this.textBox43.Text), int.Parse(this.textBox42.Text));
    }

    private void textBox39_TextChanged(object sender, EventArgs e)
    {
      this.textBox40.Text = this.databaseHandle.MobNameFast(int.Parse(this.textBox39.Text.Trim()));
    }

        public void LoadDG2()
        {
            this.dataGridView2.Rows.Clear();

            string query = "SELECT * FROM t_affinity_work WHERE a_work_type = 0 AND a_affinity_idx = '" + this.textBox1.Text + "'";

            using (var connection = new MySqlConnection(
                "datasource=" + this.Host +
                ";Port=3306;User ID=" + this.User +
                ";Password=" + this.Password +
                ";Database=" + this.Database +
                ";Charset=utf8mb4;SslMode=None;"))
            {
                connection.Open();

                using (var command = new MySqlCommand(query, connection))
                using (var reader = command.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        // Safe conversions for all fields
                        string workType = reader["a_work_type"].ToString();
                        string typeIdx = reader["a_type_idx"].ToString();
                        string affinityIdx = reader["a_affinity_idx"].ToString();
                        string value = reader["a_value"].ToString();
                        string enable = reader["a_enable"].ToString();
                        string id = reader["a_id"].ToString();
                        string row = reader["a_row"].ToString();
                        string col = reader["a_col"].ToString();

                        // Get item info
                        int itemId = Convert.ToInt32(typeIdx);
                        string itemName = this.databaseHandle.ItemNameFast(itemId);
                        var icon = this.databaseHandle.IconFast(itemId);

                        // Add to DataGridView
                        this.dataGridView2.Rows.Add(
                            icon,         // item icon
                            workType,     // a_work_type
                            typeIdx,      // a_type_idx
                            itemName,     // resolved name
                            affinityIdx,  // a_affinity_idx
                            value,        // a_value
                            enable        // a_enable
                        );
                    }
                }
            }
        }


        private void dataGridView2_CellClick(object sender, DataGridViewCellEventArgs e)
    {
      if (e.RowIndex < 0)
        return;
      DataGridViewRow row = this.dataGridView2.Rows[e.RowIndex];
      this.textBox29.Text = row.Cells["AffinityIdx"].Value.ToString();
      this.textBox28.Text = row.Cells["Work_Type"].Value.ToString();
      this.textBox26.Text = row.Cells["ItemID"].Value.ToString();
      this.textBox25.Text = row.Cells["AffinityPoints"].Value.ToString();
      this.textBox27.Text = row.Cells["Enable"].Value.ToString();
    }

    private void textBox26_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox7.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox26.Text.Trim()));
      this.textBox24.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox26.Text.Trim()));
    }

        public void LoadDG3()
        {
            this.dataGridView3.Rows.Clear();

            string query = "SELECT * FROM t_affinity_work WHERE a_work_type = 2 AND a_affinity_idx = '" + this.textBox1.Text + "'";

            using (var connection = new MySqlConnection(
                "datasource=" + this.Host +
                ";Port=3306;User ID=" + this.User +
                ";Password=" + this.Password +
                ";Database=" + this.Database +
                ";Charset=utf8mb4;SslMode=None;"))
            {
                connection.Open();

                using (var command = new MySqlCommand(query, connection))
                using (var reader = command.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        // Safely convert all types to string form
                        string workType = reader["a_work_type"].ToString();
                        string typeIdx = reader["a_type_idx"].ToString();
                        string affinityIdx = reader["a_affinity_idx"].ToString();
                        string value = reader["a_value"].ToString();
                        string enable = reader["a_enable"].ToString();
                        string id = reader["a_id"].ToString();
                        string row = reader["a_row"].ToString();
                        string col = reader["a_col"].ToString();

                        // Get quest name via helper
                        string questName = this.databaseHandle.QuestNameFast(Convert.ToInt32(typeIdx));

                        // Add a new row to the DataGridView
                        this.dataGridView3.Rows.Add(
                            workType,
                            typeIdx,
                            questName,
                            affinityIdx,
                            value,
                            enable
                        );
                    }
                }
            }
        }


        private void dataGridView3_CellClick(object sender, DataGridViewCellEventArgs e)
    {
      if (e.RowIndex < 0)
        return;
      DataGridViewRow row = this.dataGridView3.Rows[e.RowIndex];
      this.textBox30.Text = row.Cells["a_affinity_idx"].Value.ToString();
      this.textBox31.Text = row.Cells["a_work_type"].Value.ToString();
      this.textBox35.Text = row.Cells["QuestID"].Value.ToString();
      this.textBox34.Text = row.Cells["AffinityPoints2"].Value.ToString();
      this.textBox32.Text = row.Cells["a_enable"].Value.ToString();
    }

    private void textBox35_TextChanged(object sender, EventArgs e)
    {
      this.textBox33.Text = this.databaseHandle.QuestNameFast(int.Parse(this.textBox35.Text.Trim()));
    }

        public void LoadDG4()
        {
            this.dataGridView4.Rows.Clear();

            string query = "SELECT * FROM t_affinity_npc WHERE a_affinity_idx = '" + this.textBox1.Text + "'";

            using (var connection = new MySqlConnection(
                "datasource=" + this.Host +
                ";Port=3306;User ID=" + this.User +
                ";Password=" + this.Password +
                ";Database=" + this.Database +
                ";Charset=utf8mb4;SslMode=None;"))
            {
                connection.Open();

                using (var command = new MySqlCommand(query, connection))
                using (var reader = command.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        // Convert all DB values safely to string
                        string affinityIdx = reader["a_affinity_idx"].ToString();
                        string npcIdx = reader["a_npcidx"].ToString();
                        string usePoint = reader["a_use_point"].ToString();
                        string enable = reader["a_enable"].ToString();
                        string flag = reader["a_flag"].ToString();
                        string stringIdx = reader["a_string_idx"].ToString();

                        // Get mob name using your existing helper
                        string mobName = this.databaseHandle.MobNameFast(Convert.ToInt32(npcIdx));

                        // Add to DataGridView
                        this.dataGridView4.Rows.Add(
                            affinityIdx,
                            npcIdx,
                            mobName,
                            usePoint,
                            enable,
                            flag,
                            stringIdx
                        );
                    }
                }
            }
        }


        public void LoadDG6()
        {
            string query = "SELECT * FROM t_affinity_npc WHERE a_flag = '11' AND a_affinity_idx = '" + this.textBox1.Text + "'";
            using (var connection = new MySqlConnection("datasource=" + this.Host + ";Port=3306;User ID=" + this.User + ";Password=" + this.Password + ";Database=" + this.Database + ";Charset=utf8mb4;SslMode=None;"))
            {
                connection.Open();
                using (var command = new MySqlCommand(query, connection))
                using (var reader = command.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        // Convert to strings safely using .ToString() so ints don't cause InvalidCastException
                        string affinityIdx = reader["a_affinity_idx"].ToString();
                        string npcIdx = reader["a_npcidx"].ToString();
                        string usePoint = reader["a_use_point"].ToString();
                        string enable = reader["a_enable"].ToString();
                        string flag = reader["a_flag"].ToString();
                        string stringIdx = reader["a_string_idx"].ToString();

                        // These are now always valid strings
                        this.databaseHandle.FunctionMonsterName(Convert.ToInt32(npcIdx));
                        this.textBox23.Text = npcIdx;
                        this.textBox45.Text = flag;
                    }
                }
            }
        }


        public void LoadDG7()
        {
            string query = "SELECT * FROM t_affinity_npc WHERE a_flag = '4' AND a_affinity_idx = '" + this.textBox1.Text + "'";

            using (var connection = new MySqlConnection(
                "datasource=" + this.Host +
                ";Port=3306;User ID=" + this.User +
                ";Password=" + this.Password +
                ";Database=" + this.Database +
                ";Charset=utf8mb4;SslMode=None;"))
            {
                connection.Open();

                using (var command = new MySqlCommand(query, connection))
                using (var reader = command.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        // Safe conversion for all column types (int, bool, string)
                        string affinityIdx = reader["a_affinity_idx"].ToString();
                        string npcIdx = reader["a_npcidx"].ToString();
                        string usePoint = reader["a_use_point"].ToString();
                        string enable = reader["a_enable"].ToString();
                        string flag = reader["a_flag"].ToString();
                        string stringIdx = reader["a_string_idx"].ToString();

                        // Reuse FunctionMonsterName for display
                        this.databaseHandle.FunctionMonsterName(Convert.ToInt32(npcIdx));
                        this.textBox70.Text = npcIdx;
                        this.textBox69.Text = flag;
                    }
                }
            }
        }


        private void dataGridView4_CellClick(object sender, DataGridViewCellEventArgs e)
    {
      DataGridViewRow row = this.dataGridView4.Rows[e.RowIndex];
      this.textBox45.Text = row.Cells["Column11"].Value.ToString();
      this.textBox23.Text = row.Cells["Column8"].Value.ToString();
      this.textBox47.Text = row.Cells["Column11"].Value.ToString();
      this.textBox49.Text = row.Cells["Column8"].Value.ToString();
      this.textBox46.Text = row.Cells["Column7"].Value.ToString();
      this.textBox51.Text = row.Cells["Column9"].Value.ToString();
      this.textBox52.Text = row.Cells["Column12"].Value.ToString();
      this.textBox48.Text = row.Cells["Column10"].Value.ToString();
      this.dataGridView5.Rows.Clear();
      this.textBox53.Clear();
      this.textBox54.Clear();
      this.textBox55.Text = "0";
      this.textBox56.Clear();
      this.textBox57.Clear();
      this.textBox59.Text = "0";
      this.textBox61.Clear();
      this.textBox62.Clear();
      this.textBox63.Clear();
      this.textBox64.Clear();
      this.pictureBox10.Image = (Image) null;
      this.pictureBox11.Image = (Image) null;
      this.LoadDG5(this.textBox1.Text);
    }

    private void textBox49_TextChanged(object sender, EventArgs e)
    {
      this.textBox50.Text = this.databaseHandle.MobNameFast(int.Parse(this.textBox49.Text.Trim()));
    }

        public void LoadDG5(string npcidx)
        {
            this.dataGridView5.Rows.Clear();

            string query = "SELECT * FROM t_affinity_reward_item WHERE a_npcidx = '" + this.textBox23.Text + "'";

            using (var connection = new MySqlConnection(
                "datasource=" + this.Host +
                ";Port=3306;User ID=" + this.User +
                ";Password=" + this.Password +
                ";Database=" + this.Database +
                ";Charset=utf8mb4;SslMode=None;"))
            {
                connection.Open();
                using (var command = new MySqlCommand(query, connection))
                using (var reader = command.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        // Safe string conversions for all field types
                        string npcIdx = reader["a_npcidx"].ToString();
                        string allowPoint = reader["a_allow_point"].ToString();
                        string itemIdx = reader["a_itemidx"].ToString();
                        string flag = reader["a_flag"].ToString();
                        string count = reader["a_count"].ToString();
                        string exp = reader["a_exp"].ToString();
                        string sp = reader["a_sp"].ToString();
                        string needPcLevel = reader["a_needpclevel"].ToString();
                        string needItemIdx = reader["a_needitemidx"].ToString();
                        string needItemCount = reader["a_needitemcount"].ToString();

                        // Fetch item name and icon safely
                        string itemName = this.databaseHandle.ItemNameFast(Convert.ToInt32(itemIdx));

                        // Add the row to the grid
                        this.dataGridView5.Rows.Add(
                            this.databaseHandle.IconFast(Convert.ToInt32(itemIdx)),
                            itemIdx,
                            itemName,
                            count,
                            allowPoint,
                            npcIdx,
                            flag,
                            exp,
                            sp,
                            needPcLevel,
                            needItemIdx,
                            needItemCount
                        );

                        this.textBox64.Text = this.textBox23.Text;
                    }
                }
            }
        }


        private void dataGridView5_CellClick(object sender, DataGridViewCellEventArgs e)
    {
      if (e.RowIndex < 0)
        return;
      DataGridViewRow row = this.dataGridView5.Rows[e.RowIndex];
      this.textBox64.Text = row.Cells["Column14"].Value.ToString();
      this.textBox63.Text = row.Cells["Column15"].Value.ToString();
      this.textBox59.Text = row.Cells["Column16"].Value.ToString();
      this.textBox62.Text = row.Cells["Column17"].Value.ToString();
      this.textBox61.Text = row.Cells["Column18"].Value.ToString();
      this.textBox54.Text = row.Cells["Column19"].Value.ToString();
      this.textBox56.Text = row.Cells["Column20"].Value.ToString();
      this.textBox53.Text = row.Cells["Column21"].Value.ToString();
      this.textBox55.Text = row.Cells["Column22"].Value.ToString();
      this.textBox57.Text = row.Cells["Column23"].Value.ToString();
    }

    private void textBox59_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox10.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox59.Text.Trim()));
      this.textBox60.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox59.Text.Trim()));
    }

    private void textBox55_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox11.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox55.Text.Trim()));
      this.textBox58.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox55.Text.Trim()));
    }

    private void pictureBox3_Click(object sender, EventArgs e)
    {
      IconPickerSkill iconPickerSkill = new IconPickerSkill();
      iconPickerSkill.OldItemBtnSelect = Convert.ToInt32(this.textBox5.Text);
      if (iconPickerSkill.ShowDialog() != DialogResult.OK)
        return;
      this.textBox5.Text = iconPickerSkill.TexID.ToString();
      this.textBox6.Text = iconPickerSkill.TexRow.ToString();
      this.textBox7.Text = iconPickerSkill.TexColumn.ToString();
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_affinity SET a_texture_id = '" + this.textBox5.Text + "', a_texture_row = '" + this.textBox6.Text + "', a_texture_col = '" + this.textBox7.Text + "' WHERE a_index = '" + this.textBox1.Text + "'");
      int selectedIndex = this.listBox1.SelectedIndex;
      this.LoadListBox();
      this.listBox1.SelectedIndex = selectedIndex;
    }

    private void pictureBox5_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox10.Text = itemPicker.ItemIndex.ToString();
    }

    private void dataGridView1_CellValidating(object sender, DataGridViewCellValidatingEventArgs e)
    {
    }

    private void button1_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want add New Affinity  ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      if (this.textBox1.Text.Trim().Length <= 0)
      {
        int num1 = (int) MessageBox.Show("No data to select", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DROP TABLE IF EXISTS tempTable;CREATE TEMPORARY TABLE tempTable ENGINE=MEMORY SELECT * FROM t_affinity WHERE a_index=" + this.textBox1.Text + ";SELECT a_index FROM tempTable;UPDATE tempTable SET a_index=(SELECT a_index from t_affinity ORDER BY a_index DESC LIMIT 1)+1; SELECT a_index FROM tempTable;INSERT INTO t_affinity SELECT * FROM tempTable;");
        int num2 = (int) MessageBox.Show("Successful Add new", "Completed", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
        this.LoadListBox();
        this.listBox1.SelectedIndex = this.listBox1.Items.Count - 1;
      }
    }

    private void button2_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want to Delete Affinity id " + this.textBox1.Text.Trim() + "-" + this.textBox2.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      int selectedIndex = this.listBox1.SelectedIndex;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_affinity WHERE a_index = '" + this.textBox1.Text + "'");
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_affinity_reward_item WHERE a_npcidx = '" + this.textBox23.Text + "'");
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_affinity_work WHERE a_affinity_idx = '" + this.textBox1.Text + "'");
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_affinity_npc WHERE a_affinity_idx = '" + this.textBox1.Text + "'");
      this.LoadListBox();
      this.listBox1.SelectedIndex = selectedIndex - 1;
    }

    private void checkBox1_CheckedChanged(object sender, EventArgs e)
    {
    }

    private void toolStripButton1_Click(object sender, EventArgs e)
    {
      try
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_affinity_work (a_work_type, a_type_idx) VALUES (" + this.textBox1.Text + ")");
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message, "Error");
      }
      this.dataGridView1.Rows.Clear();
      this.LoadDG();
    }

    private void toolStripButton2_Click(object sender, EventArgs e)
    {
      DataGridViewRow row = this.dataGridView1.Rows[this.dataGridView1.CurrentRow.Index];
      string str1 = Convert.ToString(row.Cells["Column1"].Value);
      string str2 = Convert.ToString(row.Cells["Column2"].Value);
      string str3 = Convert.ToString(row.Cells["Column4"].Value);
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_affinity_work WHERE a_work_type ='" + str1 + "' a_affinity_idx = '" + str3 + "AND a_type_idx = '" + str2 + "'");
      this.dataGridView1.Rows.Clear();
      this.LoadDG();
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (AffinityEditor));
      this.menuStrip1 = new MenuStrip();
      this.gToolStripMenuItem = new ToolStripMenuItem();
      this.exportAffinitylodToolStripMenuItem = new ToolStripMenuItem();
      this.exportStrAffinitylodToolStripMenuItem = new ToolStripMenuItem();
      this.groupBox1 = new GroupBox();
      this.textBox22 = new TextBox();
      this.label13 = new Label();
      this.groupBox2 = new GroupBox();
      this.button2 = new Button();
      this.button1 = new Button();
      this.listBox1 = new ListBox();
      this.button3 = new Button();
      this.textBox1 = new TextBox();
      this.groupBox3 = new GroupBox();
      this.textBox7 = new TextBox();
      this.textBox6 = new TextBox();
      this.textBox5 = new TextBox();
      this.pictureBox3 = new PictureBox();
      this.pictureBox1 = new PictureBox();
      this.label2 = new Label();
      this.checkBox1 = new CheckBox();
      this.label1 = new Label();
      this.textBox2 = new TextBox();
      this.groupBox4 = new GroupBox();
      this.pictureBox5 = new PictureBox();
      this.textBox21 = new TextBox();
      this.textBox20 = new TextBox();
      this.textBox19 = new TextBox();
      this.textBox18 = new TextBox();
      this.label12 = new Label();
      this.pictureBox4 = new PictureBox();
      this.textBox3 = new TextBox();
      this.textBox8 = new TextBox();
      this.label3 = new Label();
      this.textBox17 = new TextBox();
      this.label5 = new Label();
      this.textBox16 = new TextBox();
      this.textBox15 = new TextBox();
      this.textBox14 = new TextBox();
      this.textBox13 = new TextBox();
      this.textBox12 = new TextBox();
      this.textBox11 = new TextBox();
      this.textBox10 = new TextBox();
      this.textBox9 = new TextBox();
      this.label11 = new Label();
      this.pictureBox2 = new PictureBox();
      this.label10 = new Label();
      this.label9 = new Label();
      this.label8 = new Label();
      this.label7 = new Label();
      this.label6 = new Label();
      this.label14 = new Label();
      this.textBox23 = new TextBox();
      this.textBox4 = new TextBox();
      this.label4 = new Label();
      this.groupBox5 = new GroupBox();
      this.toolStrip1 = new ToolStrip();
      this.toolStripButton1 = new ToolStripButton();
      this.toolStripSeparator1 = new ToolStripSeparator();
      this.toolStripButton2 = new ToolStripButton();
      this.dataGridView1 = new DataGridView();
      this.Column2 = new DataGridViewTextBoxColumn();
      this.Column1 = new DataGridViewTextBoxColumn();
      this.Column3 = new DataGridViewTextBoxColumn();
      this.Column4 = new DataGridViewTextBoxColumn();
      this.Column5 = new DataGridViewTextBoxColumn();
      this.Column6 = new DataGridViewTextBoxColumn();
      this.a_id = new DataGridViewTextBoxColumn();
      this.a_row = new DataGridViewTextBoxColumn();
      this.a_col = new DataGridViewTextBoxColumn();
      this.groupBox6 = new GroupBox();
      this.toolStrip2 = new ToolStrip();
      this.toolStripButton3 = new ToolStripButton();
      this.toolStripSeparator2 = new ToolStripSeparator();
      this.toolStripButton4 = new ToolStripButton();
      this.dataGridView2 = new DataGridView();
      this.dataGridViewImageColumn1 = new DataGridViewImageColumn();
      this.Work_Type = new DataGridViewTextBoxColumn();
      this.ItemID = new DataGridViewTextBoxColumn();
      this.ItemName = new DataGridViewTextBoxColumn();
      this.AffinityIdx = new DataGridViewTextBoxColumn();
      this.AffinityPoints = new DataGridViewTextBoxColumn();
      this.Enable = new DataGridViewTextBoxColumn();
      this.groupBox7 = new GroupBox();
      this.toolStrip3 = new ToolStrip();
      this.toolStripButton5 = new ToolStripButton();
      this.toolStripSeparator3 = new ToolStripSeparator();
      this.toolStripButton6 = new ToolStripButton();
      this.dataGridView3 = new DataGridView();
      this.a_work_type = new DataGridViewTextBoxColumn();
      this.QuestID = new DataGridViewTextBoxColumn();
      this.QuestName = new DataGridViewTextBoxColumn();
      this.a_affinity_idx = new DataGridViewTextBoxColumn();
      this.AffinityPoints2 = new DataGridViewTextBoxColumn();
      this.a_enable = new DataGridViewTextBoxColumn();
      this.groupBox8 = new GroupBox();
      this.dataGridView4 = new DataGridView();
      this.Column7 = new DataGridViewTextBoxColumn();
      this.Column8 = new DataGridViewTextBoxColumn();
      this.Column13 = new DataGridViewTextBoxColumn();
      this.Column9 = new DataGridViewTextBoxColumn();
      this.Column10 = new DataGridViewTextBoxColumn();
      this.Column11 = new DataGridViewTextBoxColumn();
      this.Column12 = new DataGridViewTextBoxColumn();
      this.label46 = new Label();
      this.textBox45 = new TextBox();
      this.label36 = new Label();
      this.groupBox9 = new GroupBox();
      this.dataGridView5 = new DataGridView();
      this.dataGridViewImageGift = new DataGridViewImageColumn();
      this.Column16 = new DataGridViewTextBoxColumn();
      this.GiftItemName = new DataGridViewTextBoxColumn();
      this.Column18 = new DataGridViewTextBoxColumn();
      this.Column15 = new DataGridViewTextBoxColumn();
      this.Column14 = new DataGridViewTextBoxColumn();
      this.Column17 = new DataGridViewTextBoxColumn();
      this.Column19 = new DataGridViewTextBoxColumn();
      this.Column20 = new DataGridViewTextBoxColumn();
      this.Column21 = new DataGridViewTextBoxColumn();
      this.Column22 = new DataGridViewTextBoxColumn();
      this.Column23 = new DataGridViewTextBoxColumn();
      this.pictureBox7 = new PictureBox();
      this.label15 = new Label();
      this.textBox24 = new TextBox();
      this.button4 = new Button();
      this.textBox25 = new TextBox();
      this.textBox26 = new TextBox();
      this.label16 = new Label();
      this.label17 = new Label();
      this.label18 = new Label();
      this.textBox27 = new TextBox();
      this.label19 = new Label();
      this.textBox28 = new TextBox();
      this.label20 = new Label();
      this.textBox29 = new TextBox();
      this.button6 = new Button();
      this.button9 = new Button();
      this.button12 = new Button();
      this.button5 = new Button();
      this.button7 = new Button();
      this.button8 = new Button();
      this.label21 = new Label();
      this.textBox30 = new TextBox();
      this.label22 = new Label();
      this.textBox31 = new TextBox();
      this.label23 = new Label();
      this.textBox32 = new TextBox();
      this.label24 = new Label();
      this.textBox33 = new TextBox();
      this.button10 = new Button();
      this.textBox34 = new TextBox();
      this.textBox35 = new TextBox();
      this.label25 = new Label();
      this.label26 = new Label();
      this.label27 = new Label();
      this.label28 = new Label();
      this.label29 = new Label();
      this.label30 = new Label();
      this.textBox36 = new TextBox();
      this.label31 = new Label();
      this.textBox37 = new TextBox();
      this.label32 = new Label();
      this.textBox38 = new TextBox();
      this.button11 = new Button();
      this.textBox39 = new TextBox();
      this.label33 = new Label();
      this.label34 = new Label();
      this.textBox40 = new TextBox();
      this.textBox41 = new TextBox();
      this.label35 = new Label();
      this.button13 = new Button();
      this.button14 = new Button();
      this.button15 = new Button();
      this.pictureBox8 = new PictureBox();
      this.pictureBox9 = new PictureBox();
      this.textBox42 = new TextBox();
      this.textBox43 = new TextBox();
      this.textBox44 = new TextBox();
      this.label37 = new Label();
      this.label38 = new Label();
      this.textBox46 = new TextBox();
      this.label39 = new Label();
      this.textBox47 = new TextBox();
      this.label40 = new Label();
      this.textBox48 = new TextBox();
      this.button16 = new Button();
      this.textBox49 = new TextBox();
      this.label41 = new Label();
      this.label42 = new Label();
      this.textBox50 = new TextBox();
      this.textBox51 = new TextBox();
      this.label43 = new Label();
      this.button17 = new Button();
      this.button18 = new Button();
      this.button19 = new Button();
      this.label44 = new Label();
      this.textBox52 = new TextBox();
      this.label45 = new Label();
      this.label47 = new Label();
      this.textBox53 = new TextBox();
      this.label48 = new Label();
      this.textBox54 = new TextBox();
      this.label49 = new Label();
      this.textBox55 = new TextBox();
      this.label50 = new Label();
      this.textBox56 = new TextBox();
      this.label51 = new Label();
      this.label52 = new Label();
      this.textBox57 = new TextBox();
      this.button20 = new Button();
      this.label53 = new Label();
      this.textBox58 = new TextBox();
      this.label54 = new Label();
      this.textBox59 = new TextBox();
      this.label55 = new Label();
      this.label56 = new Label();
      this.textBox60 = new TextBox();
      this.textBox61 = new TextBox();
      this.label57 = new Label();
      this.textBox62 = new TextBox();
      this.label58 = new Label();
      this.button22 = new Button();
      this.button23 = new Button();
      this.button24 = new Button();
      this.label59 = new Label();
      this.textBox63 = new TextBox();
      this.button21 = new Button();
      this.label60 = new Label();
      this.textBox64 = new TextBox();
      this.pictureBox10 = new PictureBox();
      this.pictureBox11 = new PictureBox();
      this.textBox65 = new TextBox();
      this.textBox66 = new TextBox();
      this.textBox67 = new TextBox();
      this.textBox68 = new TextBox();
      this.textBox69 = new TextBox();
      this.textBox70 = new TextBox();
      this.button25 = new Button();
      this.menuStrip1.SuspendLayout();
      this.groupBox1.SuspendLayout();
      this.groupBox2.SuspendLayout();
      this.groupBox3.SuspendLayout();
      ((ISupportInitialize) this.pictureBox3).BeginInit();
      ((ISupportInitialize) this.pictureBox1).BeginInit();
      this.groupBox4.SuspendLayout();
      ((ISupportInitialize) this.pictureBox5).BeginInit();
      ((ISupportInitialize) this.pictureBox4).BeginInit();
      ((ISupportInitialize) this.pictureBox2).BeginInit();
      this.groupBox5.SuspendLayout();
      this.toolStrip1.SuspendLayout();
      ((ISupportInitialize) this.dataGridView1).BeginInit();
      this.groupBox6.SuspendLayout();
      this.toolStrip2.SuspendLayout();
      ((ISupportInitialize) this.dataGridView2).BeginInit();
      this.groupBox7.SuspendLayout();
      this.toolStrip3.SuspendLayout();
      ((ISupportInitialize) this.dataGridView3).BeginInit();
      this.groupBox8.SuspendLayout();
      ((ISupportInitialize) this.dataGridView4).BeginInit();
      this.groupBox9.SuspendLayout();
      ((ISupportInitialize) this.dataGridView5).BeginInit();
      ((ISupportInitialize) this.pictureBox7).BeginInit();
      ((ISupportInitialize) this.pictureBox8).BeginInit();
      ((ISupportInitialize) this.pictureBox9).BeginInit();
      ((ISupportInitialize) this.pictureBox10).BeginInit();
      ((ISupportInitialize) this.pictureBox11).BeginInit();
      this.SuspendLayout();
      this.menuStrip1.BackColor = SystemColors.ControlLightLight;
      this.menuStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.gToolStripMenuItem
      });
      this.menuStrip1.Location = new Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new Size(1370, 24);
      this.menuStrip1.TabIndex = 0;
      this.menuStrip1.Text = "menuStrip1";
      this.gToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[2]
      {
        (ToolStripItem) this.exportAffinitylodToolStripMenuItem,
        (ToolStripItem) this.exportStrAffinitylodToolStripMenuItem
      });
      this.gToolStripMenuItem.Name = "gToolStripMenuItem";
      this.gToolStripMenuItem.Size = new Size(74, 20);
      this.gToolStripMenuItem.Text = "File Export";
      this.exportAffinitylodToolStripMenuItem.Name = "exportAffinitylodToolStripMenuItem";
      this.exportAffinitylodToolStripMenuItem.Size = new Size(183, 22);
      this.exportAffinitylodToolStripMenuItem.Text = "Export affinity.lod";
      this.exportAffinitylodToolStripMenuItem.Click += new EventHandler(this.exportAffinitylodToolStripMenuItem_Click);
      this.exportStrAffinitylodToolStripMenuItem.Name = "exportStrAffinitylodToolStripMenuItem";
      this.exportStrAffinitylodToolStripMenuItem.Size = new Size(183, 22);
      this.exportStrAffinitylodToolStripMenuItem.Text = "Export strAffinity.lod";
      this.exportStrAffinitylodToolStripMenuItem.Click += new EventHandler(this.exportStrAffinitylodToolStripMenuItem_Click);
      this.groupBox1.Controls.Add((Control) this.textBox22);
      this.groupBox1.Controls.Add((Control) this.label13);
      this.groupBox1.Location = new Point(12, 27);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(219, 53);
      this.groupBox1.TabIndex = 1;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Search";
      this.textBox22.BorderStyle = BorderStyle.FixedSingle;
      this.textBox22.Location = new Point(43, 22);
      this.textBox22.Name = "textBox22";
      this.textBox22.Size = new Size(167, 20);
      this.textBox22.TabIndex = 1;
      this.label13.AutoSize = true;
      this.label13.Location = new Point(6, 24);
      this.label13.Name = "label13";
      this.label13.Size = new Size(31, 13);
      this.label13.TabIndex = 0;
      this.label13.Text = "Text:";
      this.groupBox2.Controls.Add((Control) this.button2);
      this.groupBox2.Controls.Add((Control) this.button1);
      this.groupBox2.Controls.Add((Control) this.listBox1);
      this.groupBox2.Location = new Point(12, 86);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new Size(219, 493);
      this.groupBox2.TabIndex = 2;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "Affinities";
      this.button2.BackColor = Color.LightCoral;
      this.button2.FlatStyle = FlatStyle.Flat;
      this.button2.Image = (Image) Resources.delete;
      this.button2.ImageAlign = ContentAlignment.MiddleLeft;
      this.button2.Location = new Point(145, 458);
      this.button2.Name = "button2";
      this.button2.Size = new Size(65, 27);
      this.button2.TabIndex = 100;
      this.button2.Text = "    Delete";
      this.button2.UseVisualStyleBackColor = false;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.button1.BackColor = Color.Plum;
      this.button1.FlatStyle = FlatStyle.Flat;
      this.button1.Image = (Image) Resources.control_add_blue;
      this.button1.ImageAlign = ContentAlignment.MiddleLeft;
      this.button1.Location = new Point(9, 458);
      this.button1.Name = "button1";
      this.button1.Size = new Size(71, 27);
      this.button1.TabIndex = 98;
      this.button1.Text = "     Add";
      this.button1.UseVisualStyleBackColor = false;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.listBox1.FormattingEnabled = true;
      this.listBox1.Location = new Point(8, 19);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new Size(202, 433);
      this.listBox1.TabIndex = 0;
      this.listBox1.SelectedIndexChanged += new EventHandler(this.listBox1_SelectedIndexChanged);
      this.button3.BackColor = Color.LightCyan;
      this.button3.FlatStyle = FlatStyle.Flat;
      this.button3.Image = (Image) Resources._08;
      this.button3.ImageAlign = ContentAlignment.MiddleLeft;
      this.button3.Location = new Point(302, 166);
      this.button3.Name = "button3";
      this.button3.Size = new Size(72, 27);
      this.button3.TabIndex = 99;
      this.button3.Text = "      Change";
      this.button3.UseVisualStyleBackColor = false;
      this.button3.Click += new EventHandler(this.button3_Click);
      this.textBox1.BorderStyle = BorderStyle.FixedSingle;
      this.textBox1.Location = new Point(60, 16);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(43, 20);
      this.textBox1.TabIndex = 3;
      this.groupBox3.Controls.Add((Control) this.textBox7);
      this.groupBox3.Controls.Add((Control) this.textBox6);
      this.groupBox3.Controls.Add((Control) this.textBox5);
      this.groupBox3.Controls.Add((Control) this.pictureBox3);
      this.groupBox3.Controls.Add((Control) this.pictureBox1);
      this.groupBox3.Controls.Add((Control) this.label2);
      this.groupBox3.Controls.Add((Control) this.checkBox1);
      this.groupBox3.Controls.Add((Control) this.textBox1);
      this.groupBox3.Controls.Add((Control) this.label1);
      this.groupBox3.Controls.Add((Control) this.textBox2);
      this.groupBox3.Location = new Point(237, 27);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Size = new Size(430, 72);
      this.groupBox3.TabIndex = 4;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "Basic";
      this.textBox7.Location = new Point(399, 13);
      this.textBox7.Name = "textBox7";
      this.textBox7.Size = new Size(20, 20);
      this.textBox7.TabIndex = 11;
      this.textBox7.Visible = false;
      this.textBox6.Location = new Point(373, 13);
      this.textBox6.Name = "textBox6";
      this.textBox6.Size = new Size(20, 20);
      this.textBox6.TabIndex = 10;
      this.textBox6.Visible = false;
      this.textBox5.Location = new Point(347, 13);
      this.textBox5.Name = "textBox5";
      this.textBox5.Size = new Size(20, 20);
      this.textBox5.TabIndex = 9;
      this.textBox5.Visible = false;
      this.pictureBox3.BackgroundImage = (Image) Resources.oie_transparent;
      this.pictureBox3.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox3.Location = new Point(396, 41);
      this.pictureBox3.Name = "pictureBox3";
      this.pictureBox3.Size = new Size(22, 22);
      this.pictureBox3.TabIndex = 8;
      this.pictureBox3.TabStop = false;
      this.pictureBox3.Click += new EventHandler(this.pictureBox3_Click);
      this.pictureBox1.Location = new Point(358, 36);
      this.pictureBox1.Name = "pictureBox1";
      this.pictureBox1.Size = new Size(32, 32);
      this.pictureBox1.TabIndex = 0;
      this.pictureBox1.TabStop = false;
      this.label2.AutoSize = true;
      this.label2.Location = new Point(16, 20);
      this.label2.Name = "label2";
      this.label2.Size = new Size(36, 13);
      this.label2.TabIndex = 7;
      this.label2.Text = "Index:";
      this.checkBox1.AutoSize = true;
      this.checkBox1.FlatStyle = FlatStyle.Flat;
      this.checkBox1.Location = new Point(188, 18);
      this.checkBox1.Name = "checkBox1";
      this.checkBox1.Size = new Size(56, 17);
      this.checkBox1.TabIndex = 6;
      this.checkBox1.Text = "Enable";
      this.checkBox1.UseVisualStyleBackColor = true;
      this.checkBox1.CheckedChanged += new EventHandler(this.checkBox1_CheckedChanged);
      this.label1.AutoSize = true;
      this.label1.Location = new Point(16, 45);
      this.label1.Name = "label1";
      this.label1.Size = new Size(38, 13);
      this.label1.TabIndex = 5;
      this.label1.Text = "Name:";
      this.textBox2.BorderStyle = BorderStyle.FixedSingle;
      this.textBox2.Location = new Point(60, 42);
      this.textBox2.Name = "textBox2";
      this.textBox2.Size = new Size(292, 20);
      this.textBox2.TabIndex = 0;
      this.groupBox4.Controls.Add((Control) this.button3);
      this.groupBox4.Controls.Add((Control) this.pictureBox5);
      this.groupBox4.Controls.Add((Control) this.textBox21);
      this.groupBox4.Controls.Add((Control) this.textBox20);
      this.groupBox4.Controls.Add((Control) this.textBox19);
      this.groupBox4.Controls.Add((Control) this.textBox18);
      this.groupBox4.Controls.Add((Control) this.label12);
      this.groupBox4.Controls.Add((Control) this.pictureBox4);
      this.groupBox4.Controls.Add((Control) this.textBox3);
      this.groupBox4.Controls.Add((Control) this.textBox8);
      this.groupBox4.Controls.Add((Control) this.label3);
      this.groupBox4.Controls.Add((Control) this.textBox17);
      this.groupBox4.Controls.Add((Control) this.label5);
      this.groupBox4.Controls.Add((Control) this.textBox16);
      this.groupBox4.Controls.Add((Control) this.textBox15);
      this.groupBox4.Controls.Add((Control) this.textBox14);
      this.groupBox4.Controls.Add((Control) this.textBox13);
      this.groupBox4.Controls.Add((Control) this.textBox12);
      this.groupBox4.Controls.Add((Control) this.textBox11);
      this.groupBox4.Controls.Add((Control) this.textBox10);
      this.groupBox4.Controls.Add((Control) this.textBox9);
      this.groupBox4.Controls.Add((Control) this.label11);
      this.groupBox4.Controls.Add((Control) this.pictureBox2);
      this.groupBox4.Controls.Add((Control) this.label10);
      this.groupBox4.Controls.Add((Control) this.label9);
      this.groupBox4.Controls.Add((Control) this.label8);
      this.groupBox4.Controls.Add((Control) this.label7);
      this.groupBox4.Controls.Add((Control) this.label6);
      this.groupBox4.Location = new Point(237, 101);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Size = new Size(430, 197);
      this.groupBox4.TabIndex = 5;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "Need for Affinity";
      this.pictureBox5.BackgroundImage = (Image) Resources.oie_transparent;
      this.pictureBox5.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox5.Location = new Point(188, 29);
      this.pictureBox5.Name = "pictureBox5";
      this.pictureBox5.Size = new Size(23, 20);
      this.pictureBox5.TabIndex = 29;
      this.pictureBox5.TabStop = false;
      this.pictureBox5.Click += new EventHandler(this.pictureBox5_Click);
      this.textBox21.Location = new Point(196, 6);
      this.textBox21.Name = "textBox21";
      this.textBox21.Size = new Size(20, 20);
      this.textBox21.TabIndex = 28;
      this.textBox21.Visible = false;
      this.textBox20.Location = new Point(174, 6);
      this.textBox20.Name = "textBox20";
      this.textBox20.Size = new Size(20, 20);
      this.textBox20.TabIndex = 27;
      this.textBox20.Visible = false;
      this.textBox19.Location = new Point(149, 6);
      this.textBox19.Name = "textBox19";
      this.textBox19.Size = new Size(20, 20);
      this.textBox19.TabIndex = 26;
      this.textBox19.Visible = false;
      this.textBox18.Location = new Point(126, 6);
      this.textBox18.Name = "textBox18";
      this.textBox18.Size = new Size(20, 20);
      this.textBox18.TabIndex = 25;
      this.textBox18.Visible = false;
      this.label12.AutoSize = true;
      this.label12.Location = new Point(260, 32);
      this.label12.Name = "label12";
      this.label12.Size = new Size(41, 13);
      this.label12.TabIndex = 24;
      this.label12.Text = "label12";
      this.label12.Visible = false;
      this.pictureBox4.Location = new Point(221, 23);
      this.pictureBox4.Name = "pictureBox4";
      this.pictureBox4.Size = new Size(32, 32);
      this.pictureBox4.TabIndex = 23;
      this.pictureBox4.TabStop = false;
      this.textBox3.BorderStyle = BorderStyle.FixedSingle;
      this.textBox3.Location = new Point(126, 171);
      this.textBox3.Name = "textBox3";
      this.textBox3.Size = new Size(100, 20);
      this.textBox3.TabIndex = 12;
      this.textBox8.BorderStyle = BorderStyle.FixedSingle;
      this.textBox8.Location = new Point(301, 133);
      this.textBox8.Name = "textBox8";
      this.textBox8.Size = new Size(117, 20);
      this.textBox8.TabIndex = 13;
      this.label3.AutoSize = true;
      this.label3.Location = new Point(57, 173);
      this.label3.Name = "label3";
      this.label3.Size = new Size(60, 13);
      this.label3.TabIndex = 6;
      this.label3.Text = "Max Value:";
      this.textBox17.Location = new Point(365, 47);
      this.textBox17.Name = "textBox17";
      this.textBox17.Size = new Size(20, 20);
      this.textBox17.TabIndex = 22;
      this.textBox17.Visible = false;
      this.label5.AutoSize = true;
      this.label5.Location = new Point(264, 138);
      this.label5.Name = "label5";
      this.label5.Size = new Size(29, 13);
      this.label5.TabIndex = 0;
      this.label5.Text = "Nas:";
      this.textBox16.Location = new Point(343, 47);
      this.textBox16.Name = "textBox16";
      this.textBox16.Size = new Size(20, 20);
      this.textBox16.TabIndex = 21;
      this.textBox16.Visible = false;
      this.textBox15.Location = new Point(322, 47);
      this.textBox15.Name = "textBox15";
      this.textBox15.Size = new Size(20, 20);
      this.textBox15.TabIndex = 20;
      this.textBox15.Visible = false;
      this.textBox14.Location = new Point(301, 47);
      this.textBox14.Name = "textBox14";
      this.textBox14.Size = new Size(20, 20);
      this.textBox14.TabIndex = 19;
      this.textBox14.Visible = false;
      this.textBox13.BorderStyle = BorderStyle.FixedSingle;
      this.textBox13.Location = new Point(126, 136);
      this.textBox13.Name = "textBox13";
      this.textBox13.Size = new Size(100, 20);
      this.textBox13.TabIndex = 18;
      this.textBox12.BorderStyle = BorderStyle.FixedSingle;
      this.textBox12.Location = new Point(126, 101);
      this.textBox12.Name = "textBox12";
      this.textBox12.Size = new Size(100, 20);
      this.textBox12.TabIndex = 17;
      this.textBox11.BorderStyle = BorderStyle.FixedSingle;
      this.textBox11.Location = new Point(126, 68);
      this.textBox11.Name = "textBox11";
      this.textBox11.Size = new Size(100, 20);
      this.textBox11.TabIndex = 16;
      this.textBox10.BorderStyle = BorderStyle.FixedSingle;
      this.textBox10.Location = new Point(126, 29);
      this.textBox10.Name = "textBox10";
      this.textBox10.Size = new Size(56, 20);
      this.textBox10.TabIndex = 15;
      this.textBox9.BorderStyle = BorderStyle.FixedSingle;
      this.textBox9.Location = new Point(301, 68);
      this.textBox9.Name = "textBox9";
      this.textBox9.Size = new Size(70, 20);
      this.textBox9.TabIndex = 14;
      this.label11.AutoSize = true;
      this.label11.Location = new Point(299, 105);
      this.label11.Name = "label11";
      this.label11.Size = new Size(41, 13);
      this.label11.TabIndex = 11;
      this.label11.Text = "label11";
      this.pictureBox2.Location = new Point(263, 94);
      this.pictureBox2.Name = "pictureBox2";
      this.pictureBox2.Size = new Size(32, 32);
      this.pictureBox2.TabIndex = 10;
      this.pictureBox2.TabStop = false;
      this.label10.AutoSize = true;
      this.label10.Location = new Point(16, 140);
      this.label10.Name = "label10";
      this.label10.Size = new Size(102, 13);
      this.label10.TabIndex = 8;
      this.label10.Text = "Need Affinity Points:";
      this.label9.AutoSize = true;
      this.label9.Location = new Point(16, 105);
      this.label9.Name = "label9";
      this.label9.Size = new Size(70, 13);
      this.label9.TabIndex = 7;
      this.label9.Text = "Need Affinity:";
      this.label8.AutoSize = true;
      this.label8.Location = new Point(16, 72);
      this.label8.Name = "label8";
      this.label8.Size = new Size(90, 13);
      this.label8.TabIndex = 4;
      this.label8.Text = "Need Item Count:";
      this.label7.AutoSize = true;
      this.label7.Location = new Point(16, 32);
      this.label7.Name = "label7";
      this.label7.Size = new Size(59, 13);
      this.label7.TabIndex = 3;
      this.label7.Text = "Need Item:";
      this.label6.AutoSize = true;
      this.label6.Location = new Point(236, 70);
      this.label6.Name = "label6";
      this.label6.Size = new Size(65, 13);
      this.label6.TabIndex = 2;
      this.label6.Text = "Need Level:";
      this.label14.AutoSize = true;
      this.label14.Location = new Point(361, 387);
      this.label14.Name = "label14";
      this.label14.Size = new Size(46, 13);
      this.label14.TabIndex = 32;
      this.label14.Text = "NPC ID:";
      this.label14.Visible = false;
      this.textBox23.Enabled = false;
      this.textBox23.Location = new Point(412, 383);
      this.textBox23.Name = "textBox23";
      this.textBox23.Size = new Size(28, 20);
      this.textBox23.TabIndex = 31;
      this.textBox23.Visible = false;
      this.textBox4.Location = new Point(562, 1);
      this.textBox4.Name = "textBox4";
      this.textBox4.Size = new Size(42, 20);
      this.textBox4.TabIndex = 7;
      this.textBox4.Visible = false;
      this.label4.AutoSize = true;
      this.label4.Location = new Point(516, 4);
      this.label4.Name = "label4";
      this.label4.Size = new Size(40, 13);
      this.label4.TabIndex = 11;
      this.label4.Text = "Enable";
      this.label4.Visible = false;
      this.groupBox5.Controls.Add((Control) this.toolStrip1);
      this.groupBox5.Controls.Add((Control) this.dataGridView1);
      this.groupBox5.Location = new Point(673, 29);
      this.groupBox5.Name = "groupBox5";
      this.groupBox5.Size = new Size(689, 175);
      this.groupBox5.TabIndex = 12;
      this.groupBox5.TabStop = false;
      this.groupBox5.Text = "Monster Set";
      this.toolStrip1.Dock = DockStyle.Bottom;
      this.toolStrip1.Items.AddRange(new ToolStripItem[3]
      {
        (ToolStripItem) this.toolStripButton1,
        (ToolStripItem) this.toolStripSeparator1,
        (ToolStripItem) this.toolStripButton2
      });
      this.toolStrip1.Location = new Point(3, 147);
      this.toolStrip1.Name = "toolStrip1";
      this.toolStrip1.Size = new Size(683, 25);
      this.toolStrip1.TabIndex = 1;
      this.toolStrip1.Text = "toolStrip1";
      this.toolStripButton1.DisplayStyle = ToolStripItemDisplayStyle.Text;
      this.toolStripButton1.Enabled = false;
      this.toolStripButton1.ImageTransparentColor = Color.Magenta;
      this.toolStripButton1.Name = "toolStripButton1";
      this.toolStripButton1.Size = new Size(80, 22);
      this.toolStripButton1.Text = "Add Monster";
      this.toolStripButton1.Click += new EventHandler(this.toolStripButton1_Click);
      this.toolStripSeparator1.Name = "toolStripSeparator1";
      this.toolStripSeparator1.Size = new Size(6, 25);
      this.toolStripButton2.DisplayStyle = ToolStripItemDisplayStyle.Text;
      this.toolStripButton2.Enabled = false;
      this.toolStripButton2.ImageTransparentColor = Color.Magenta;
      this.toolStripButton2.Name = "toolStripButton2";
      this.toolStripButton2.Size = new Size(90, 22);
      this.toolStripButton2.Text = "Delete selected";
      this.toolStripButton2.Click += new EventHandler(this.toolStripButton2_Click);
      this.dataGridView1.AllowUserToAddRows = false;
      this.dataGridView1.AllowUserToDeleteRows = false;
      this.dataGridView1.AllowUserToResizeColumns = false;
      this.dataGridView1.AllowUserToResizeRows = false;
      this.dataGridView1.BackgroundColor = SystemColors.Control;
      this.dataGridView1.BorderStyle = BorderStyle.None;
      this.dataGridView1.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dataGridView1.Columns.AddRange((DataGridViewColumn) this.Column2, (DataGridViewColumn) this.Column1, (DataGridViewColumn) this.Column3, (DataGridViewColumn) this.Column4, (DataGridViewColumn) this.Column5, (DataGridViewColumn) this.Column6, (DataGridViewColumn) this.a_id, (DataGridViewColumn) this.a_row, (DataGridViewColumn) this.a_col);
      this.dataGridView1.EnableHeadersVisualStyles = false;
      this.dataGridView1.Location = new Point(3, 16);
      this.dataGridView1.Name = "dataGridView1";
      this.dataGridView1.RowHeadersVisible = false;
      this.dataGridView1.ScrollBars = ScrollBars.Vertical;
      this.dataGridView1.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
      this.dataGridView1.Size = new Size(683, 134);
      this.dataGridView1.TabIndex = 0;
      this.dataGridView1.CellClick += new DataGridViewCellEventHandler(this.dataGridView1_CellClick);
      this.dataGridView1.CellValidating += new DataGridViewCellValidatingEventHandler(this.dataGridView1_CellValidating);
      this.Column2.HeaderText = "a_work_type";
      this.Column2.Name = "Column2";
      this.Column2.Width = 70;
      this.Column1.HeaderText = "Monster";
      this.Column1.Name = "Column1";
      this.Column1.Width = 80;
      this.Column3.HeaderText = "Monster Name";
      this.Column3.Name = "Column3";
      this.Column3.ReadOnly = true;
      this.Column3.Width = 230;
      this.Column4.HeaderText = "a_affinity_idx";
      this.Column4.Name = "Column4";
      this.Column4.Width = 70;
      this.Column5.HeaderText = "Affinity Points";
      this.Column5.Name = "Column5";
      this.Column5.Width = 150;
      this.Column6.HeaderText = "a_enable";
      this.Column6.Name = "Column6";
      this.Column6.Width = 70;
      this.a_id.HeaderText = "a_id";
      this.a_id.Name = "a_id";
      this.a_id.Width = 50;
      this.a_row.HeaderText = "a_row";
      this.a_row.Name = "a_row";
      this.a_row.Width = 50;
      this.a_col.HeaderText = "a_col";
      this.a_col.Name = "a_col";
      this.a_col.Width = 50;
      this.groupBox6.Controls.Add((Control) this.toolStrip2);
      this.groupBox6.Controls.Add((Control) this.dataGridView2);
      this.groupBox6.Location = new Point(673, 283);
      this.groupBox6.Name = "groupBox6";
      this.groupBox6.Size = new Size(462, 192);
      this.groupBox6.TabIndex = 13;
      this.groupBox6.TabStop = false;
      this.groupBox6.Text = "Donate Items Set";
      this.toolStrip2.Dock = DockStyle.Bottom;
      this.toolStrip2.Items.AddRange(new ToolStripItem[3]
      {
        (ToolStripItem) this.toolStripButton3,
        (ToolStripItem) this.toolStripSeparator2,
        (ToolStripItem) this.toolStripButton4
      });
      this.toolStrip2.Location = new Point(3, 164);
      this.toolStrip2.Name = "toolStrip2";
      this.toolStrip2.Size = new Size(456, 25);
      this.toolStrip2.TabIndex = 1;
      this.toolStrip2.Text = "toolStrip2";
      this.toolStripButton3.DisplayStyle = ToolStripItemDisplayStyle.Text;
      this.toolStripButton3.Enabled = false;
      this.toolStripButton3.ImageTransparentColor = Color.Magenta;
      this.toolStripButton3.Name = "toolStripButton3";
      this.toolStripButton3.Size = new Size(60, 22);
      this.toolStripButton3.Text = "Add Item";
      this.toolStripButton3.ToolTipText = "Add Item";
      this.toolStripButton3.Click += new EventHandler(this.toolStripButton3_Click);
      this.toolStripSeparator2.Name = "toolStripSeparator2";
      this.toolStripSeparator2.Size = new Size(6, 25);
      this.toolStripButton4.DisplayStyle = ToolStripItemDisplayStyle.Text;
      this.toolStripButton4.Enabled = false;
      this.toolStripButton4.ImageTransparentColor = Color.Magenta;
      this.toolStripButton4.Name = "toolStripButton4";
      this.toolStripButton4.Size = new Size(44, 22);
      this.toolStripButton4.Text = "Delete";
      this.toolStripButton4.Click += new EventHandler(this.toolStripButton4_Click);
      this.dataGridView2.AllowUserToAddRows = false;
      this.dataGridView2.AllowUserToDeleteRows = false;
      this.dataGridView2.AutoSizeRowsMode = DataGridViewAutoSizeRowsMode.DisplayedCells;
      this.dataGridView2.BackgroundColor = SystemColors.Control;
      this.dataGridView2.BorderStyle = BorderStyle.None;
      this.dataGridView2.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dataGridView2.Columns.AddRange((DataGridViewColumn) this.dataGridViewImageColumn1, (DataGridViewColumn) this.Work_Type, (DataGridViewColumn) this.ItemID, (DataGridViewColumn) this.ItemName, (DataGridViewColumn) this.AffinityIdx, (DataGridViewColumn) this.AffinityPoints, (DataGridViewColumn) this.Enable);
      this.dataGridView2.Dock = DockStyle.Fill;
      this.dataGridView2.EnableHeadersVisualStyles = false;
      this.dataGridView2.Location = new Point(3, 16);
      this.dataGridView2.Name = "dataGridView2";
      this.dataGridView2.RowHeadersVisible = false;
      this.dataGridView2.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
      this.dataGridView2.Size = new Size(456, 173);
      this.dataGridView2.TabIndex = 0;
      this.dataGridView2.CellClick += new DataGridViewCellEventHandler(this.dataGridView2_CellClick);
      this.dataGridView2.CellContentClick += new DataGridViewCellEventHandler(this.dataGridView2_CellContentClick);
      this.dataGridViewImageColumn1.HeaderText = "";
      this.dataGridViewImageColumn1.Name = "dataGridViewImageColumn1";
      this.dataGridViewImageColumn1.Width = 32;
      this.Work_Type.HeaderText = "a_work_type";
      this.Work_Type.Name = "Work_Type";
      this.Work_Type.Visible = false;
      this.ItemID.HeaderText = "ItemID";
      this.ItemID.Name = "ItemID";
      this.ItemName.HeaderText = "Item Name";
      this.ItemName.Name = "ItemName";
      this.ItemName.Width = 205;
      this.AffinityIdx.HeaderText = "a_affinity_idx";
      this.AffinityIdx.Name = "AffinityIdx";
      this.AffinityIdx.Visible = false;
      this.AffinityPoints.HeaderText = "Affinity Points";
      this.AffinityPoints.Name = "AffinityPoints";
      this.Enable.HeaderText = "a_enable";
      this.Enable.Name = "Enable";
      this.Enable.Visible = false;
      this.groupBox7.Controls.Add((Control) this.toolStrip3);
      this.groupBox7.Controls.Add((Control) this.dataGridView3);
      this.groupBox7.Location = new Point(670, 484);
      this.groupBox7.Name = "groupBox7";
      this.groupBox7.Size = new Size(462, 196);
      this.groupBox7.TabIndex = 14;
      this.groupBox7.TabStop = false;
      this.groupBox7.Text = "Quest Set";
      this.toolStrip3.Dock = DockStyle.Bottom;
      this.toolStrip3.Items.AddRange(new ToolStripItem[3]
      {
        (ToolStripItem) this.toolStripButton5,
        (ToolStripItem) this.toolStripSeparator3,
        (ToolStripItem) this.toolStripButton6
      });
      this.toolStrip3.Location = new Point(3, 168);
      this.toolStrip3.Name = "toolStrip3";
      this.toolStrip3.Size = new Size(456, 25);
      this.toolStrip3.TabIndex = 2;
      this.toolStrip3.Text = "toolStrip3";
      this.toolStripButton5.DisplayStyle = ToolStripItemDisplayStyle.Text;
      this.toolStripButton5.Enabled = false;
      this.toolStripButton5.ImageTransparentColor = Color.Magenta;
      this.toolStripButton5.Name = "toolStripButton5";
      this.toolStripButton5.Size = new Size(67, 22);
      this.toolStripButton5.Text = "Add Quest";
      this.toolStripButton5.Click += new EventHandler(this.toolStripButton5_Click);
      this.toolStripSeparator3.Name = "toolStripSeparator3";
      this.toolStripSeparator3.Size = new Size(6, 25);
      this.toolStripButton6.DisplayStyle = ToolStripItemDisplayStyle.Text;
      this.toolStripButton6.Enabled = false;
      this.toolStripButton6.ImageTransparentColor = Color.Magenta;
      this.toolStripButton6.Name = "toolStripButton6";
      this.toolStripButton6.Size = new Size(44, 22);
      this.toolStripButton6.Text = "Delete";
      this.toolStripButton6.Click += new EventHandler(this.toolStripButton6_Click);
      this.dataGridView3.AllowUserToAddRows = false;
      this.dataGridView3.AllowUserToDeleteRows = false;
      this.dataGridView3.AllowUserToResizeColumns = false;
      this.dataGridView3.AllowUserToResizeRows = false;
      this.dataGridView3.BackgroundColor = SystemColors.Control;
      this.dataGridView3.BorderStyle = BorderStyle.None;
      this.dataGridView3.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dataGridView3.Columns.AddRange((DataGridViewColumn) this.a_work_type, (DataGridViewColumn) this.QuestID, (DataGridViewColumn) this.QuestName, (DataGridViewColumn) this.a_affinity_idx, (DataGridViewColumn) this.AffinityPoints2, (DataGridViewColumn) this.a_enable);
      this.dataGridView3.Dock = DockStyle.Fill;
      this.dataGridView3.EnableHeadersVisualStyles = false;
      this.dataGridView3.Location = new Point(3, 16);
      this.dataGridView3.Name = "dataGridView3";
      this.dataGridView3.RowHeadersVisible = false;
      this.dataGridView3.ScrollBars = ScrollBars.Vertical;
      this.dataGridView3.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
      this.dataGridView3.Size = new Size(456, 177);
      this.dataGridView3.TabIndex = 1;
      this.dataGridView3.CellClick += new DataGridViewCellEventHandler(this.dataGridView3_CellClick);
      this.a_work_type.HeaderText = "a_work_type";
      this.a_work_type.Name = "a_work_type";
      this.a_work_type.Visible = false;
      this.QuestID.HeaderText = "QuestID";
      this.QuestID.Name = "QuestID";
      this.QuestName.HeaderText = "Quest Name";
      this.QuestName.Name = "QuestName";
      this.QuestName.Width = 230;
      this.a_affinity_idx.HeaderText = "a_affinity_idx";
      this.a_affinity_idx.Name = "a_affinity_idx";
      this.a_affinity_idx.Visible = false;
      this.AffinityPoints2.HeaderText = "Affinity Points";
      this.AffinityPoints2.Name = "AffinityPoints2";
      this.a_enable.HeaderText = "a_enable";
      this.a_enable.Name = "a_enable";
      this.a_enable.Visible = false;
      this.groupBox8.Controls.Add((Control) this.dataGridView4);
      this.groupBox8.Location = new Point(237, 300);
      this.groupBox8.Name = "groupBox8";
      this.groupBox8.Size = new Size(430, 84);
      this.groupBox8.TabIndex = 15;
      this.groupBox8.TabStop = false;
      this.groupBox8.Text = "Manager NPC Settings";
      this.dataGridView4.AllowUserToAddRows = false;
      this.dataGridView4.AllowUserToDeleteRows = false;
      this.dataGridView4.AllowUserToResizeColumns = false;
      this.dataGridView4.AllowUserToResizeRows = false;
      this.dataGridView4.BackgroundColor = SystemColors.Control;
      this.dataGridView4.BorderStyle = BorderStyle.None;
      this.dataGridView4.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dataGridView4.Columns.AddRange((DataGridViewColumn) this.Column7, (DataGridViewColumn) this.Column8, (DataGridViewColumn) this.Column13, (DataGridViewColumn) this.Column9, (DataGridViewColumn) this.Column10, (DataGridViewColumn) this.Column11, (DataGridViewColumn) this.Column12);
      this.dataGridView4.EnableHeadersVisualStyles = false;
      this.dataGridView4.Location = new Point(3, 16);
      this.dataGridView4.Name = "dataGridView4";
      this.dataGridView4.RowHeadersVisible = false;
      this.dataGridView4.ScrollBars = ScrollBars.Vertical;
      this.dataGridView4.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
      this.dataGridView4.Size = new Size(424, 65);
      this.dataGridView4.TabIndex = 0;
      this.dataGridView4.CellClick += new DataGridViewCellEventHandler(this.dataGridView4_CellClick);
      this.Column7.HeaderText = "a_affinity_idx";
      this.Column7.Name = "Column7";
      this.Column7.Visible = false;
      this.Column8.HeaderText = "NpcID";
      this.Column8.Name = "Column8";
      this.Column8.Width = 65;
      this.Column13.HeaderText = "Npc Name";
      this.Column13.Name = "Column13";
      this.Column13.Width = 140;
      this.Column9.HeaderText = "Use Points";
      this.Column9.Name = "Column9";
      this.Column10.HeaderText = "a_enable";
      this.Column10.Name = "Column10";
      this.Column10.Visible = false;
      this.Column11.HeaderText = "Flag";
      this.Column11.Name = "Column11";
      this.Column11.Width = 60;
      this.Column12.HeaderText = "String ID";
      this.Column12.Name = "Column12";
      this.label46.AutoSize = true;
      this.label46.ForeColor = Color.Red;
      this.label46.Location = new Point(518, 387);
      this.label46.Name = "label46";
      this.label46.Size = new Size(144, 13);
      this.label46.TabIndex = 35;
      this.label46.Text = "* Reg Flag =11 Shop Flag =4";
      this.textBox45.Enabled = false;
      this.textBox45.Location = new Point(472, 383);
      this.textBox45.Name = "textBox45";
      this.textBox45.Size = new Size(36, 20);
      this.textBox45.TabIndex = 33;
      this.textBox45.Visible = false;
      this.label36.AutoSize = true;
      this.label36.Location = new Point(445, 387);
      this.label36.Name = "label36";
      this.label36.Size = new Size(30, 13);
      this.label36.TabIndex = 34;
      this.label36.Text = "Flag:";
      this.label36.Visible = false;
      this.groupBox9.Controls.Add((Control) this.dataGridView5);
      this.groupBox9.Location = new Point(240, 483);
      this.groupBox9.Name = "groupBox9";
      this.groupBox9.Size = new Size(424, 128);
      this.groupBox9.TabIndex = 16;
      this.groupBox9.TabStop = false;
      this.groupBox9.Text = "Affinity Reward";
      this.dataGridView5.AllowUserToAddRows = false;
      this.dataGridView5.AllowUserToDeleteRows = false;
      this.dataGridView5.AllowUserToResizeColumns = false;
      this.dataGridView5.AllowUserToResizeRows = false;
      this.dataGridView5.BackgroundColor = SystemColors.Control;
      this.dataGridView5.BorderStyle = BorderStyle.None;
      this.dataGridView5.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dataGridView5.Columns.AddRange((DataGridViewColumn) this.dataGridViewImageGift, (DataGridViewColumn) this.Column16, (DataGridViewColumn) this.GiftItemName, (DataGridViewColumn) this.Column18, (DataGridViewColumn) this.Column15, (DataGridViewColumn) this.Column14, (DataGridViewColumn) this.Column17, (DataGridViewColumn) this.Column19, (DataGridViewColumn) this.Column20, (DataGridViewColumn) this.Column21, (DataGridViewColumn) this.Column22, (DataGridViewColumn) this.Column23);
      this.dataGridView5.Dock = DockStyle.Fill;
      this.dataGridView5.EnableHeadersVisualStyles = false;
      this.dataGridView5.Location = new Point(3, 16);
      this.dataGridView5.Name = "dataGridView5";
      this.dataGridView5.RowHeadersVisible = false;
      this.dataGridView5.ScrollBars = ScrollBars.Vertical;
      this.dataGridView5.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
      this.dataGridView5.Size = new Size(418, 109);
      this.dataGridView5.TabIndex = 0;
      this.dataGridView5.CellClick += new DataGridViewCellEventHandler(this.dataGridView5_CellClick);
      this.dataGridViewImageGift.HeaderText = "";
      this.dataGridViewImageGift.Name = "dataGridViewImageGift";
      this.dataGridViewImageGift.Width = 32;
      this.Column16.HeaderText = "a_itemidx";
      this.Column16.Name = "Column16";
      this.Column16.Width = 60;
      this.GiftItemName.HeaderText = "Item Name";
      this.GiftItemName.Name = "GiftItemName";
      this.Column18.HeaderText = "a_count";
      this.Column18.Name = "Column18";
      this.Column18.Width = 50;
      this.Column15.HeaderText = "a_allow_point";
      this.Column15.Name = "Column15";
      this.Column14.HeaderText = "a_npcidx";
      this.Column14.Name = "Column14";
      this.Column14.Width = 60;
      this.Column17.HeaderText = "a_flag";
      this.Column17.Name = "Column17";
      this.Column19.HeaderText = "a_exp";
      this.Column19.Name = "Column19";
      this.Column20.HeaderText = "a_sp";
      this.Column20.Name = "Column20";
      this.Column21.HeaderText = "a_needpclevle";
      this.Column21.Name = "Column21";
      this.Column22.HeaderText = "a_needitemidx";
      this.Column22.Name = "Column22";
      this.Column23.HeaderText = "a_needitemcount";
      this.Column23.Name = "Column23";
      this.pictureBox7.Location = new Point(1145, 342);
      this.pictureBox7.Name = "pictureBox7";
      this.pictureBox7.Size = new Size(32, 32);
      this.pictureBox7.TabIndex = 33;
      this.pictureBox7.TabStop = false;
      this.label15.AutoSize = true;
      this.label15.Location = new Point(1150, 415);
      this.label15.Name = "label15";
      this.label15.Size = new Size(38, 13);
      this.label15.TabIndex = 32;
      this.label15.Text = "Name:";
      this.textBox24.Enabled = false;
      this.textBox24.Location = new Point(1194, 412);
      this.textBox24.Multiline = true;
      this.textBox24.Name = "textBox24";
      this.textBox24.Size = new Size(170, 21);
      this.textBox24.TabIndex = 31;
      this.button4.BackgroundImageLayout = ImageLayout.None;
      this.button4.Image = (Image) Resources.search__5_;
      this.button4.Location = new Point(1333, 349);
      this.button4.Name = "button4";
      this.button4.Size = new Size(27, 25);
      this.button4.TabIndex = 30;
      this.button4.UseVisualStyleBackColor = true;
      this.button4.Click += new EventHandler(this.button4_Click);
      this.textBox25.Location = new Point(1235, 382);
      this.textBox25.Multiline = true;
      this.textBox25.Name = "textBox25";
      this.textBox25.Size = new Size(129, 21);
      this.textBox25.TabIndex = 29;
      this.textBox26.Enabled = false;
      this.textBox26.Location = new Point(1235, 351);
      this.textBox26.Multiline = true;
      this.textBox26.Name = "textBox26";
      this.textBox26.Size = new Size(92, 21);
      this.textBox26.TabIndex = 28;
      this.textBox26.TextChanged += new EventHandler(this.textBox26_TextChanged);
      this.label16.AutoSize = true;
      this.label16.Location = new Point(1195, 385);
      this.label16.Name = "label16";
      this.label16.Size = new Size(34, 13);
      this.label16.TabIndex = 27;
      this.label16.Text = "Point:";
      this.label17.AutoSize = true;
      this.label17.Location = new Point(1185, 354);
      this.label17.Name = "label17";
      this.label17.Size = new Size(44, 13);
      this.label17.TabIndex = 26;
      this.label17.Text = "Item ID:";
      this.label18.AutoSize = true;
      this.label18.Location = new Point(1271, 286);
      this.label18.Name = "label18";
      this.label18.Size = new Size(43, 13);
      this.label18.TabIndex = 35;
      this.label18.Text = "Enable:";
      this.textBox27.Enabled = false;
      this.textBox27.Location = new Point(1319, 283);
      this.textBox27.Name = "textBox27";
      this.textBox27.Size = new Size(31, 20);
      this.textBox27.TabIndex = 34;
      this.label19.AutoSize = true;
      this.label19.Location = new Point(1279, 315);
      this.label19.Name = "label19";
      this.label19.Size = new Size(34, 13);
      this.label19.TabIndex = 37;
      this.label19.Text = "Type:";
      this.textBox28.Enabled = false;
      this.textBox28.Location = new Point(1319, 312);
      this.textBox28.Name = "textBox28";
      this.textBox28.Size = new Size(31, 20);
      this.textBox28.TabIndex = 36;
      this.label20.AutoSize = true;
      this.label20.Location = new Point(1188, 315);
      this.label20.Name = "label20";
      this.label20.Size = new Size(41, 13);
      this.label20.TabIndex = 39;
      this.label20.Text = "Affinity:";
      this.textBox29.Enabled = false;
      this.textBox29.Location = new Point(1235, 312);
      this.textBox29.Name = "textBox29";
      this.textBox29.Size = new Size(30, 20);
      this.textBox29.TabIndex = 38;
      this.button6.BackColor = Color.Plum;
      this.button6.FlatStyle = FlatStyle.Flat;
      this.button6.Image = (Image) Resources.control_add_blue;
      this.button6.ImageAlign = ContentAlignment.MiddleLeft;
      this.button6.Location = new Point(1144, 439);
      this.button6.Name = "button6";
      this.button6.Size = new Size(71, 27);
      this.button6.TabIndex = 40;
      this.button6.Text = "     Add";
      this.button6.UseVisualStyleBackColor = false;
      this.button6.Click += new EventHandler(this.button6_Click);
      this.button9.BackColor = Color.LightCyan;
      this.button9.FlatStyle = FlatStyle.Flat;
      this.button9.Image = (Image) Resources._08;
      this.button9.ImageAlign = ContentAlignment.MiddleLeft;
      this.button9.Location = new Point(1221, 439);
      this.button9.Name = "button9";
      this.button9.Size = new Size(72, 27);
      this.button9.TabIndex = 41;
      this.button9.Text = "      Change";
      this.button9.UseVisualStyleBackColor = false;
      this.button9.Click += new EventHandler(this.button9_Click);
      this.button12.BackColor = Color.LightCoral;
      this.button12.FlatStyle = FlatStyle.Flat;
      this.button12.Image = (Image) Resources.delete;
      this.button12.ImageAlign = ContentAlignment.MiddleLeft;
      this.button12.Location = new Point(1299, 439);
      this.button12.Name = "button12";
      this.button12.Size = new Size(65, 27);
      this.button12.TabIndex = 42;
      this.button12.Text = "    Delete";
      this.button12.UseVisualStyleBackColor = false;
      this.button12.Click += new EventHandler(this.button12_Click);
      this.button5.BackColor = Color.LightCoral;
      this.button5.FlatStyle = FlatStyle.Flat;
      this.button5.Image = (Image) Resources.delete;
      this.button5.ImageAlign = ContentAlignment.MiddleLeft;
      this.button5.Location = new Point(1295, 644);
      this.button5.Name = "button5";
      this.button5.Size = new Size(65, 27);
      this.button5.TabIndex = 59;
      this.button5.Text = "    Delete";
      this.button5.UseVisualStyleBackColor = false;
      this.button5.Click += new EventHandler(this.button5_Click);
      this.button7.BackColor = Color.LightCyan;
      this.button7.FlatStyle = FlatStyle.Flat;
      this.button7.Image = (Image) Resources._08;
      this.button7.ImageAlign = ContentAlignment.MiddleLeft;
      this.button7.Location = new Point(1217, 644);
      this.button7.Name = "button7";
      this.button7.Size = new Size(72, 27);
      this.button7.TabIndex = 58;
      this.button7.Text = "      Change";
      this.button7.UseVisualStyleBackColor = false;
      this.button7.Click += new EventHandler(this.button7_Click);
      this.button8.BackColor = Color.Plum;
      this.button8.FlatStyle = FlatStyle.Flat;
      this.button8.Image = (Image) Resources.control_add_blue;
      this.button8.ImageAlign = ContentAlignment.MiddleLeft;
      this.button8.Location = new Point(1140, 644);
      this.button8.Name = "button8";
      this.button8.Size = new Size(71, 27);
      this.button8.TabIndex = 57;
      this.button8.Text = "     Add";
      this.button8.UseVisualStyleBackColor = false;
      this.button8.Click += new EventHandler(this.button8_Click);
      this.label21.AutoSize = true;
      this.label21.Location = new Point(1184, 520);
      this.label21.Name = "label21";
      this.label21.Size = new Size(41, 13);
      this.label21.TabIndex = 56;
      this.label21.Text = "Affinity:";
      this.textBox30.Enabled = false;
      this.textBox30.Location = new Point(1231, 517);
      this.textBox30.Name = "textBox30";
      this.textBox30.Size = new Size(30, 20);
      this.textBox30.TabIndex = 55;
      this.label22.AutoSize = true;
      this.label22.Location = new Point(1275, 520);
      this.label22.Name = "label22";
      this.label22.Size = new Size(34, 13);
      this.label22.TabIndex = 54;
      this.label22.Text = "Type:";
      this.textBox31.Enabled = false;
      this.textBox31.Location = new Point(1315, 517);
      this.textBox31.Name = "textBox31";
      this.textBox31.Size = new Size(31, 20);
      this.textBox31.TabIndex = 53;
      this.label23.AutoSize = true;
      this.label23.Location = new Point(1267, 494);
      this.label23.Name = "label23";
      this.label23.Size = new Size(43, 13);
      this.label23.TabIndex = 52;
      this.label23.Text = "Enable:";
      this.textBox32.Enabled = false;
      this.textBox32.Location = new Point(1315, 491);
      this.textBox32.Name = "textBox32";
      this.textBox32.Size = new Size(31, 20);
      this.textBox32.TabIndex = 51;
      this.label24.AutoSize = true;
      this.label24.Location = new Point(1146, 620);
      this.label24.Name = "label24";
      this.label24.Size = new Size(38, 13);
      this.label24.TabIndex = 49;
      this.label24.Text = "Name:";
      this.textBox33.Enabled = false;
      this.textBox33.Location = new Point(1190, 617);
      this.textBox33.Multiline = true;
      this.textBox33.Name = "textBox33";
      this.textBox33.Size = new Size(170, 21);
      this.textBox33.TabIndex = 48;
      this.button10.BackgroundImageLayout = ImageLayout.None;
      this.button10.Image = (Image) Resources.search__5_;
      this.button10.Location = new Point(1329, 554);
      this.button10.Name = "button10";
      this.button10.Size = new Size(27, 25);
      this.button10.TabIndex = 47;
      this.button10.UseVisualStyleBackColor = true;
      this.button10.Click += new EventHandler(this.button10_Click);
      this.textBox34.Location = new Point(1231, 587);
      this.textBox34.Multiline = true;
      this.textBox34.Name = "textBox34";
      this.textBox34.Size = new Size(129, 21);
      this.textBox34.TabIndex = 46;
      this.textBox35.Enabled = false;
      this.textBox35.Location = new Point(1231, 556);
      this.textBox35.Multiline = true;
      this.textBox35.Name = "textBox35";
      this.textBox35.Size = new Size(92, 21);
      this.textBox35.TabIndex = 45;
      this.textBox35.TextChanged += new EventHandler(this.textBox35_TextChanged);
      this.label25.AutoSize = true;
      this.label25.Location = new Point(1191, 590);
      this.label25.Name = "label25";
      this.label25.Size = new Size(34, 13);
      this.label25.TabIndex = 44;
      this.label25.Text = "Point:";
      this.label26.AutoSize = true;
      this.label26.Location = new Point(1181, 559);
      this.label26.Name = "label26";
      this.label26.Size = new Size(52, 13);
      this.label26.TabIndex = 43;
      this.label26.Text = "Quest ID:";
      this.label27.AutoSize = true;
      this.label27.Location = new Point(1153, 285);
      this.label27.Name = "label27";
      this.label27.Size = new Size(67, 13);
      this.label27.TabIndex = 60;
      this.label27.Text = "Item Set Edit";
      this.label28.AutoSize = true;
      this.label28.Location = new Point(1153, 494);
      this.label28.Name = "label28";
      this.label28.Size = new Size(75, 13);
      this.label28.TabIndex = 61;
      this.label28.Text = "Quest Set Edit";
      this.label29.AutoSize = true;
      this.label29.Location = new Point(685, 207);
      this.label29.Name = "label29";
      this.label29.Size = new Size(85, 13);
      this.label29.TabIndex = 68;
      this.label29.Text = "Monster Set Edit";
      this.label30.AutoSize = true;
      this.label30.Location = new Point(776, 210);
      this.label30.Name = "label30";
      this.label30.Size = new Size(41, 13);
      this.label30.TabIndex = 67;
      this.label30.Text = "Affinity:";
      this.textBox36.Enabled = false;
      this.textBox36.Location = new Point(823, 206);
      this.textBox36.Name = "textBox36";
      this.textBox36.Size = new Size(30, 20);
      this.textBox36.TabIndex = 66;
      this.label31.AutoSize = true;
      this.label31.Location = new Point(944, 209);
      this.label31.Name = "label31";
      this.label31.Size = new Size(34, 13);
      this.label31.TabIndex = 65;
      this.label31.Text = "Type:";
      this.textBox37.Enabled = false;
      this.textBox37.Location = new Point(984, 206);
      this.textBox37.Name = "textBox37";
      this.textBox37.Size = new Size(31, 20);
      this.textBox37.TabIndex = 64;
      this.label32.AutoSize = true;
      this.label32.Location = new Point(859, 210);
      this.label32.Name = "label32";
      this.label32.Size = new Size(43, 13);
      this.label32.TabIndex = 63;
      this.label32.Text = "Enable:";
      this.textBox38.Enabled = false;
      this.textBox38.Location = new Point(907, 206);
      this.textBox38.Name = "textBox38";
      this.textBox38.Size = new Size(31, 20);
      this.textBox38.TabIndex = 62;
      this.button11.BackgroundImageLayout = ImageLayout.None;
      this.button11.Image = (Image) Resources.search__5_;
      this.button11.Location = new Point(1164, 204);
      this.button11.Name = "button11";
      this.button11.Size = new Size(27, 25);
      this.button11.TabIndex = 71;
      this.button11.UseVisualStyleBackColor = true;
      this.button11.Click += new EventHandler(this.button11_Click);
      this.textBox39.Enabled = false;
      this.textBox39.Location = new Point(1066, 206);
      this.textBox39.Multiline = true;
      this.textBox39.Name = "textBox39";
      this.textBox39.Size = new Size(92, 21);
      this.textBox39.TabIndex = 70;
      this.textBox39.TextChanged += new EventHandler(this.textBox39_TextChanged);
      this.label33.AutoSize = true;
      this.label33.Location = new Point(1016, 210);
      this.label33.Name = "label33";
      this.label33.Size = new Size(44, 13);
      this.label33.TabIndex = 69;
      this.label33.Text = "Npc ID:";
      this.label34.AutoSize = true;
      this.label34.Location = new Point(1195, 210);
      this.label34.Name = "label34";
      this.label34.Size = new Size(38, 13);
      this.label34.TabIndex = 73;
      this.label34.Text = "Name:";
      this.textBox40.Enabled = false;
      this.textBox40.Location = new Point(1239, 207);
      this.textBox40.Multiline = true;
      this.textBox40.Name = "textBox40";
      this.textBox40.Size = new Size(125, 21);
      this.textBox40.TabIndex = 72;
      this.textBox41.Location = new Point(984, 238);
      this.textBox41.Multiline = true;
      this.textBox41.Name = "textBox41";
      this.textBox41.Size = new Size((int) sbyte.MaxValue, 21);
      this.textBox41.TabIndex = 75;
      this.label35.AutoSize = true;
      this.label35.Location = new Point(944, 241);
      this.label35.Name = "label35";
      this.label35.Size = new Size(34, 13);
      this.label35.TabIndex = 74;
      this.label35.Text = "Point:";
      this.button13.BackColor = Color.LightCoral;
      this.button13.FlatStyle = FlatStyle.Flat;
      this.button13.Image = (Image) Resources.delete;
      this.button13.ImageAlign = ContentAlignment.MiddleLeft;
      this.button13.Location = new Point(1299, 234);
      this.button13.Name = "button13";
      this.button13.Size = new Size(65, 27);
      this.button13.TabIndex = 78;
      this.button13.Text = "    Delete";
      this.button13.UseVisualStyleBackColor = false;
      this.button13.Click += new EventHandler(this.button13_Click);
      this.button14.BackColor = Color.LightCyan;
      this.button14.FlatStyle = FlatStyle.Flat;
      this.button14.Image = (Image) Resources._08;
      this.button14.ImageAlign = ContentAlignment.MiddleLeft;
      this.button14.Location = new Point(1221, 234);
      this.button14.Name = "button14";
      this.button14.Size = new Size(72, 27);
      this.button14.TabIndex = 77;
      this.button14.Text = "      Change";
      this.button14.UseVisualStyleBackColor = false;
      this.button14.Click += new EventHandler(this.button14_Click);
      this.button15.BackColor = Color.Plum;
      this.button15.FlatStyle = FlatStyle.Flat;
      this.button15.Image = (Image) Resources.control_add_blue;
      this.button15.ImageAlign = ContentAlignment.MiddleLeft;
      this.button15.Location = new Point(1144, 234);
      this.button15.Name = "button15";
      this.button15.Size = new Size(71, 27);
      this.button15.TabIndex = 76;
      this.button15.Text = "     Add";
      this.button15.UseVisualStyleBackColor = false;
      this.button15.Click += new EventHandler(this.button15_Click);
      this.pictureBox8.BackgroundImage = (Image) Resources.oie_transparent;
      this.pictureBox8.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox8.Location = new Point(907, 243);
      this.pictureBox8.Name = "pictureBox8";
      this.pictureBox8.Size = new Size(22, 22);
      this.pictureBox8.TabIndex = 80;
      this.pictureBox8.TabStop = false;
      this.pictureBox8.Click += new EventHandler(this.pictureBox8_Click);
      this.pictureBox9.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox9.Location = new Point(851, 229);
      this.pictureBox9.Name = "pictureBox9";
      this.pictureBox9.Size = new Size(50, 50);
      this.pictureBox9.TabIndex = 79;
      this.pictureBox9.TabStop = false;
      this.textBox42.Location = new Point(740, 241);
      this.textBox42.Name = "textBox42";
      this.textBox42.Size = new Size(20, 20);
      this.textBox42.TabIndex = 83;
      this.textBox42.Visible = false;
      this.textBox43.Location = new Point(714, 241);
      this.textBox43.Name = "textBox43";
      this.textBox43.Size = new Size(20, 20);
      this.textBox43.TabIndex = 82;
      this.textBox43.Visible = false;
      this.textBox44.Location = new Point(688, 241);
      this.textBox44.Name = "textBox44";
      this.textBox44.Size = new Size(20, 20);
      this.textBox44.TabIndex = 81;
      this.textBox44.Visible = false;
      this.label37.AutoSize = true;
      this.label37.Location = new Point(817, 248);
      this.label37.Name = "label37";
      this.label37.Size = new Size(28, 13);
      this.label37.TabIndex = 84;
      this.label37.Text = "Icon";
      this.label38.AutoSize = true;
      this.label38.Location = new Point(302, 407);
      this.label38.Name = "label38";
      this.label38.Size = new Size(41, 13);
      this.label38.TabIndex = 90;
      this.label38.Text = "Affinity:";
      this.textBox46.Enabled = false;
      this.textBox46.Location = new Point(346, 403);
      this.textBox46.Name = "textBox46";
      this.textBox46.Size = new Size(30, 20);
      this.textBox46.TabIndex = 89;
      this.label39.AutoSize = true;
      this.label39.Location = new Point(470, 406);
      this.label39.Name = "label39";
      this.label39.Size = new Size(30, 13);
      this.label39.TabIndex = 88;
      this.label39.Text = "Flag:";
      this.textBox47.Location = new Point(501, 403);
      this.textBox47.Name = "textBox47";
      this.textBox47.Size = new Size(41, 20);
      this.textBox47.TabIndex = 87;
      this.label40.AutoSize = true;
      this.label40.Location = new Point(385, 407);
      this.label40.Name = "label40";
      this.label40.Size = new Size(43, 13);
      this.label40.TabIndex = 86;
      this.label40.Text = "Enable:";
      this.textBox48.Enabled = false;
      this.textBox48.Location = new Point(431, 403);
      this.textBox48.Name = "textBox48";
      this.textBox48.Size = new Size(31, 20);
      this.textBox48.TabIndex = 85;
      this.button16.BackgroundImageLayout = ImageLayout.None;
      this.button16.Image = (Image) Resources.search__5_;
      this.button16.Location = new Point(385, 423);
      this.button16.Name = "button16";
      this.button16.Size = new Size(27, 25);
      this.button16.TabIndex = 93;
      this.button16.UseVisualStyleBackColor = true;
      this.button16.Click += new EventHandler(this.button16_Click);
      this.textBox49.Enabled = false;
      this.textBox49.Location = new Point(287, 425);
      this.textBox49.Multiline = true;
      this.textBox49.Name = "textBox49";
      this.textBox49.Size = new Size(92, 21);
      this.textBox49.TabIndex = 92;
      this.textBox49.TextChanged += new EventHandler(this.textBox49_TextChanged);
      this.label41.AutoSize = true;
      this.label41.Location = new Point(237, 429);
      this.label41.Name = "label41";
      this.label41.Size = new Size(44, 13);
      this.label41.TabIndex = 91;
      this.label41.Text = "Npc ID:";
      this.label42.AutoSize = true;
      this.label42.Location = new Point(243, 451);
      this.label42.Name = "label42";
      this.label42.Size = new Size(38, 13);
      this.label42.TabIndex = 95;
      this.label42.Text = "Name:";
      this.textBox50.Enabled = false;
      this.textBox50.Location = new Point(287, 448);
      this.textBox50.Multiline = true;
      this.textBox50.Name = "textBox50";
      this.textBox50.Size = new Size(125, 21);
      this.textBox50.TabIndex = 94;
      this.textBox51.Location = new Point(469, 426);
      this.textBox51.Multiline = true;
      this.textBox51.Name = "textBox51";
      this.textBox51.Size = new Size((int) sbyte.MaxValue, 21);
      this.textBox51.TabIndex = 97;
      this.label43.AutoSize = true;
      this.label43.Location = new Point(418, 429);
      this.label43.Name = "label43";
      this.label43.Size = new Size(53, 13);
      this.label43.TabIndex = 96;
      this.label43.Text = "UsePoint:";
      this.button17.BackColor = Color.LightCoral;
      this.button17.FlatStyle = FlatStyle.Flat;
      this.button17.Image = (Image) Resources.delete;
      this.button17.ImageAlign = ContentAlignment.MiddleLeft;
      this.button17.Location = new Point(580, 454);
      this.button17.Name = "button17";
      this.button17.Size = new Size(65, 27);
      this.button17.TabIndex = 100;
      this.button17.Text = "    Delete";
      this.button17.UseVisualStyleBackColor = false;
      this.button17.Click += new EventHandler(this.button17_Click);
      this.button18.BackColor = Color.LightCyan;
      this.button18.FlatStyle = FlatStyle.Flat;
      this.button18.Image = (Image) Resources._08;
      this.button18.ImageAlign = ContentAlignment.MiddleLeft;
      this.button18.Location = new Point(502, 454);
      this.button18.Name = "button18";
      this.button18.Size = new Size(72, 27);
      this.button18.TabIndex = 99;
      this.button18.Text = "      Change";
      this.button18.UseVisualStyleBackColor = false;
      this.button18.Click += new EventHandler(this.button18_Click);
      this.button19.BackColor = Color.Plum;
      this.button19.FlatStyle = FlatStyle.Flat;
      this.button19.Image = (Image) Resources.control_add_blue;
      this.button19.ImageAlign = ContentAlignment.MiddleLeft;
      this.button19.Location = new Point(425, 454);
      this.button19.Name = "button19";
      this.button19.Size = new Size(71, 27);
      this.button19.TabIndex = 98;
      this.button19.Text = "     Add";
      this.button19.UseVisualStyleBackColor = false;
      this.button19.Click += new EventHandler(this.button19_Click);
      this.label44.AutoSize = true;
      this.label44.Location = new Point(547, 407);
      this.label44.Name = "label44";
      this.label44.Size = new Size(37, 13);
      this.label44.TabIndex = 102;
      this.label44.Text = "String:";
      this.textBox52.Location = new Point(587, 404);
      this.textBox52.Name = "textBox52";
      this.textBox52.Size = new Size(71, 20);
      this.textBox52.TabIndex = 101;
      this.label45.AutoSize = true;
      this.label45.Location = new Point(240, 391);
      this.label45.Name = "label45";
      this.label45.Size = new Size(48, 13);
      this.label45.TabIndex = 103;
      this.label45.Text = "Npc Edit";
      this.label47.AutoSize = true;
      this.label47.Location = new Point(148, 605);
      this.label47.Name = "label47";
      this.label47.Size = new Size(36, 13);
      this.label47.TabIndex = 111;
      this.label47.Text = "Level:";
      this.textBox53.Location = new Point(187, 602);
      this.textBox53.Name = "textBox53";
      this.textBox53.Size = new Size(35, 20);
      this.textBox53.TabIndex = 110;
      this.label48.AutoSize = true;
      this.label48.Location = new Point(17, 609);
      this.label48.Name = "label48";
      this.label48.Size = new Size(28, 13);
      this.label48.TabIndex = 109;
      this.label48.Text = "Exp:";
      this.textBox54.Location = new Point(47, 604);
      this.textBox54.Name = "textBox54";
      this.textBox54.Size = new Size(99, 20);
      this.textBox54.TabIndex = 108;
      this.label49.AutoSize = true;
      this.label49.Location = new Point(15, 653);
      this.label49.Name = "label49";
      this.label49.Size = new Size(30, 13);
      this.label49.TabIndex = 107;
      this.label49.Text = "Item:";
      this.textBox55.Enabled = false;
      this.textBox55.Location = new Point(47, 650);
      this.textBox55.Name = "textBox55";
      this.textBox55.Size = new Size(65, 20);
      this.textBox55.TabIndex = 106;
      this.textBox55.TextChanged += new EventHandler(this.textBox55_TextChanged);
      this.label50.AutoSize = true;
      this.label50.Location = new Point(22, 630);
      this.label50.Name = "label50";
      this.label50.Size = new Size(23, 13);
      this.label50.TabIndex = 105;
      this.label50.Text = "Sp:";
      this.textBox56.Location = new Point(47, 627);
      this.textBox56.Name = "textBox56";
      this.textBox56.Size = new Size(99, 20);
      this.textBox56.TabIndex = 104;
      this.label51.AutoSize = true;
      this.label51.ForeColor = Color.Blue;
      this.label51.Location = new Point(12, 584);
      this.label51.Name = "label51";
      this.label51.Size = new Size(91, 13);
      this.label51.TabIndex = 112;
      this.label51.Text = "Need For Reward";
      this.label52.AutoSize = true;
      this.label52.Location = new Point(147, 653);
      this.label52.Name = "label52";
      this.label52.Size = new Size(38, 13);
      this.label52.TabIndex = 114;
      this.label52.Text = "Count:";
      this.textBox57.Location = new Point(186, 650);
      this.textBox57.Name = "textBox57";
      this.textBox57.Size = new Size(36, 20);
      this.textBox57.TabIndex = 113;
      this.button20.BackgroundImageLayout = ImageLayout.None;
      this.button20.Image = (Image) Resources.search__5_;
      this.button20.Location = new Point(117, 648);
      this.button20.Name = "button20";
      this.button20.Size = new Size(27, 25);
      this.button20.TabIndex = 115;
      this.button20.UseVisualStyleBackColor = true;
      this.button20.Click += new EventHandler(this.button20_Click);
      this.label53.AutoSize = true;
      this.label53.Location = new Point(7, 679);
      this.label53.Name = "label53";
      this.label53.Size = new Size(38, 13);
      this.label53.TabIndex = 117;
      this.label53.Text = "Name:";
      this.textBox58.Enabled = false;
      this.textBox58.Location = new Point(47, 676);
      this.textBox58.Multiline = true;
      this.textBox58.Name = "textBox58";
      this.textBox58.Size = new Size(97, 21);
      this.textBox58.TabIndex = 116;
      this.label54.AutoSize = true;
      this.label54.Location = new Point(240, 614);
      this.label54.Name = "label54";
      this.label54.Size = new Size(65, 13);
      this.label54.TabIndex = 118;
      this.label54.Text = "Reward Edit";
      this.textBox59.Enabled = false;
      this.textBox59.Location = new Point(287, 630);
      this.textBox59.Multiline = true;
      this.textBox59.Name = "textBox59";
      this.textBox59.Size = new Size(92, 21);
      this.textBox59.TabIndex = 120;
      this.textBox59.TextChanged += new EventHandler(this.textBox59_TextChanged);
      this.label55.AutoSize = true;
      this.label55.Location = new Point(237, 634);
      this.label55.Name = "label55";
      this.label55.Size = new Size(44, 13);
      this.label55.TabIndex = 119;
      this.label55.Text = "Item ID:";
      this.label56.AutoSize = true;
      this.label56.Location = new Point(243, 658);
      this.label56.Name = "label56";
      this.label56.Size = new Size(38, 13);
      this.label56.TabIndex = 123;
      this.label56.Text = "Name:";
      this.textBox60.Enabled = false;
      this.textBox60.Location = new Point(287, 655);
      this.textBox60.Multiline = true;
      this.textBox60.Name = "textBox60";
      this.textBox60.Size = new Size(125, 21);
      this.textBox60.TabIndex = 122;
      this.textBox61.Location = new Point(506, 630);
      this.textBox61.Multiline = true;
      this.textBox61.Name = "textBox61";
      this.textBox61.Size = new Size(51, 21);
      this.textBox61.TabIndex = 125;
      this.label57.AutoSize = true;
      this.label57.Location = new Point(466, 634);
      this.label57.Name = "label57";
      this.label57.Size = new Size(38, 13);
      this.label57.TabIndex = 124;
      this.label57.Text = "Count:";
      this.textBox62.Location = new Point(603, 629);
      this.textBox62.Multiline = true;
      this.textBox62.Name = "textBox62";
      this.textBox62.Size = new Size(53, 21);
      this.textBox62.TabIndex = (int) sbyte.MaxValue;
      this.label58.AutoSize = true;
      this.label58.Location = new Point(563, 633);
      this.label58.Name = "label58";
      this.label58.Size = new Size(30, 13);
      this.label58.TabIndex = 126;
      this.label58.Text = "Flag:";
      this.button22.BackColor = Color.LightCoral;
      this.button22.FlatStyle = FlatStyle.Flat;
      this.button22.Image = (Image) Resources.delete;
      this.button22.ImageAlign = ContentAlignment.MiddleLeft;
      this.button22.Location = new Point(578, 679);
      this.button22.Name = "button22";
      this.button22.Size = new Size(65, 27);
      this.button22.TabIndex = 130;
      this.button22.Text = "    Delete";
      this.button22.UseVisualStyleBackColor = false;
      this.button22.Click += new EventHandler(this.button22_Click);
      this.button23.BackColor = Color.LightCyan;
      this.button23.FlatStyle = FlatStyle.Flat;
      this.button23.Image = (Image) Resources._08;
      this.button23.ImageAlign = ContentAlignment.MiddleLeft;
      this.button23.Location = new Point(500, 679);
      this.button23.Name = "button23";
      this.button23.Size = new Size(72, 27);
      this.button23.TabIndex = 129;
      this.button23.Text = "      Change";
      this.button23.UseVisualStyleBackColor = false;
      this.button23.Click += new EventHandler(this.button23_Click);
      this.button24.BackColor = Color.Plum;
      this.button24.FlatStyle = FlatStyle.Flat;
      this.button24.Image = (Image) Resources.control_add_blue;
      this.button24.ImageAlign = ContentAlignment.MiddleLeft;
      this.button24.Location = new Point(423, 679);
      this.button24.Name = "button24";
      this.button24.Size = new Size(71, 27);
      this.button24.TabIndex = 128;
      this.button24.Text = "     Add";
      this.button24.UseVisualStyleBackColor = false;
      this.button24.Click += new EventHandler(this.button24_Click);
      this.label59.AutoSize = true;
      this.label59.Location = new Point(418, 658);
      this.label59.Name = "label59";
      this.label59.Size = new Size(62, 13);
      this.label59.TabIndex = 132;
      this.label59.Text = "Allow Point:";
      this.textBox63.Location = new Point(492, 655);
      this.textBox63.Multiline = true;
      this.textBox63.Name = "textBox63";
      this.textBox63.Size = new Size(116, 21);
      this.textBox63.TabIndex = 131;
      this.button21.BackgroundImageLayout = ImageLayout.None;
      this.button21.Image = (Image) Resources.search__5_;
      this.button21.Location = new Point(385, 628);
      this.button21.Name = "button21";
      this.button21.Size = new Size(27, 25);
      this.button21.TabIndex = 121;
      this.button21.UseVisualStyleBackColor = true;
      this.button21.Click += new EventHandler(this.button21_Click);
      this.label60.AutoSize = true;
      this.label60.Location = new Point(229, 683);
      this.label60.Name = "label60";
      this.label60.Size = new Size(52, 13);
      this.label60.TabIndex = 134;
      this.label60.Text = "Name ID:";
      this.textBox64.Enabled = false;
      this.textBox64.Location = new Point(287, 680);
      this.textBox64.Multiline = true;
      this.textBox64.Name = "textBox64";
      this.textBox64.Size = new Size(68, 21);
      this.textBox64.TabIndex = 133;
      this.pictureBox10.Location = new Point(421, 623);
      this.pictureBox10.Name = "pictureBox10";
      this.pictureBox10.Size = new Size(32, 32);
      this.pictureBox10.TabIndex = 135;
      this.pictureBox10.TabStop = false;
      this.pictureBox11.Location = new Point(153, 669);
      this.pictureBox11.Name = "pictureBox11";
      this.pictureBox11.Size = new Size(32, 32);
      this.pictureBox11.TabIndex = 136;
      this.pictureBox11.TabStop = false;
      this.textBox65.Location = new Point(685, 1);
      this.textBox65.Name = "textBox65";
      this.textBox65.Size = new Size(20, 20);
      this.textBox65.TabIndex = 139;
      this.textBox65.Visible = false;
      this.textBox66.Location = new Point(659, 1);
      this.textBox66.Name = "textBox66";
      this.textBox66.Size = new Size(20, 20);
      this.textBox66.TabIndex = 138;
      this.textBox66.Visible = false;
      this.textBox67.Location = new Point(633, 1);
      this.textBox67.Name = "textBox67";
      this.textBox67.Size = new Size(20, 20);
      this.textBox67.TabIndex = 137;
      this.textBox67.Visible = false;
      this.textBox68.Location = new Point(714, 1);
      this.textBox68.Name = "textBox68";
      this.textBox68.Size = new Size(20, 20);
      this.textBox68.TabIndex = 140;
      this.textBox68.Visible = false;
      this.textBox69.Enabled = false;
      this.textBox69.Location = new Point(321, 383);
      this.textBox69.Name = "textBox69";
      this.textBox69.Size = new Size(22, 20);
      this.textBox69.TabIndex = 142;
      this.textBox69.Visible = false;
      this.textBox70.Enabled = false;
      this.textBox70.Location = new Point(294, 383);
      this.textBox70.Name = "textBox70";
      this.textBox70.Size = new Size(21, 20);
      this.textBox70.TabIndex = 141;
      this.textBox70.Visible = false;
      this.button25.BackColor = Color.Plum;
      this.button25.FlatStyle = FlatStyle.Flat;
      this.button25.Image = (Image) Resources.control_add_blue;
      this.button25.ImageAlign = ContentAlignment.MiddleLeft;
      this.button25.Location = new Point(232, 0);
      this.button25.Name = "button25";
      this.button25.Size = new Size(100, 23);
      this.button25.TabIndex = 100;
      this.button25.Text = "    Go to Export ";
      this.button25.UseVisualStyleBackColor = false;
      this.button25.Visible = false;
      this.button25.Click += new EventHandler(this.button25_Click);
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(1370, 708);
      this.Controls.Add((Control) this.button25);
      this.Controls.Add((Control) this.textBox69);
      this.Controls.Add((Control) this.textBox70);
      this.Controls.Add((Control) this.textBox68);
      this.Controls.Add((Control) this.textBox65);
      this.Controls.Add((Control) this.pictureBox11);
      this.Controls.Add((Control) this.pictureBox10);
      this.Controls.Add((Control) this.textBox66);
      this.Controls.Add((Control) this.label60);
      this.Controls.Add((Control) this.textBox64);
      this.Controls.Add((Control) this.textBox67);
      this.Controls.Add((Control) this.label59);
      this.Controls.Add((Control) this.textBox63);
      this.Controls.Add((Control) this.label46);
      this.Controls.Add((Control) this.textBox45);
      this.Controls.Add((Control) this.button22);
      this.Controls.Add((Control) this.label36);
      this.Controls.Add((Control) this.button23);
      this.Controls.Add((Control) this.textBox23);
      this.Controls.Add((Control) this.button24);
      this.Controls.Add((Control) this.label14);
      this.Controls.Add((Control) this.textBox62);
      this.Controls.Add((Control) this.textBox61);
      this.Controls.Add((Control) this.label56);
      this.Controls.Add((Control) this.label58);
      this.Controls.Add((Control) this.label57);
      this.Controls.Add((Control) this.textBox60);
      this.Controls.Add((Control) this.button21);
      this.Controls.Add((Control) this.textBox59);
      this.Controls.Add((Control) this.label55);
      this.Controls.Add((Control) this.label54);
      this.Controls.Add((Control) this.label53);
      this.Controls.Add((Control) this.textBox58);
      this.Controls.Add((Control) this.button20);
      this.Controls.Add((Control) this.label52);
      this.Controls.Add((Control) this.textBox57);
      this.Controls.Add((Control) this.label51);
      this.Controls.Add((Control) this.label47);
      this.Controls.Add((Control) this.textBox53);
      this.Controls.Add((Control) this.label48);
      this.Controls.Add((Control) this.textBox54);
      this.Controls.Add((Control) this.label49);
      this.Controls.Add((Control) this.textBox55);
      this.Controls.Add((Control) this.label50);
      this.Controls.Add((Control) this.textBox56);
      this.Controls.Add((Control) this.label45);
      this.Controls.Add((Control) this.label44);
      this.Controls.Add((Control) this.textBox52);
      this.Controls.Add((Control) this.button17);
      this.Controls.Add((Control) this.button18);
      this.Controls.Add((Control) this.button19);
      this.Controls.Add((Control) this.textBox51);
      this.Controls.Add((Control) this.label43);
      this.Controls.Add((Control) this.label42);
      this.Controls.Add((Control) this.textBox50);
      this.Controls.Add((Control) this.button16);
      this.Controls.Add((Control) this.textBox49);
      this.Controls.Add((Control) this.label41);
      this.Controls.Add((Control) this.label38);
      this.Controls.Add((Control) this.textBox46);
      this.Controls.Add((Control) this.label39);
      this.Controls.Add((Control) this.textBox47);
      this.Controls.Add((Control) this.label40);
      this.Controls.Add((Control) this.textBox48);
      this.Controls.Add((Control) this.label37);
      this.Controls.Add((Control) this.textBox42);
      this.Controls.Add((Control) this.textBox43);
      this.Controls.Add((Control) this.textBox44);
      this.Controls.Add((Control) this.pictureBox8);
      this.Controls.Add((Control) this.pictureBox9);
      this.Controls.Add((Control) this.button13);
      this.Controls.Add((Control) this.button14);
      this.Controls.Add((Control) this.button15);
      this.Controls.Add((Control) this.textBox41);
      this.Controls.Add((Control) this.label35);
      this.Controls.Add((Control) this.label34);
      this.Controls.Add((Control) this.textBox40);
      this.Controls.Add((Control) this.button11);
      this.Controls.Add((Control) this.textBox39);
      this.Controls.Add((Control) this.label33);
      this.Controls.Add((Control) this.label29);
      this.Controls.Add((Control) this.label30);
      this.Controls.Add((Control) this.textBox36);
      this.Controls.Add((Control) this.label31);
      this.Controls.Add((Control) this.textBox37);
      this.Controls.Add((Control) this.label32);
      this.Controls.Add((Control) this.textBox38);
      this.Controls.Add((Control) this.label28);
      this.Controls.Add((Control) this.label27);
      this.Controls.Add((Control) this.button5);
      this.Controls.Add((Control) this.button7);
      this.Controls.Add((Control) this.button8);
      this.Controls.Add((Control) this.label21);
      this.Controls.Add((Control) this.textBox30);
      this.Controls.Add((Control) this.label22);
      this.Controls.Add((Control) this.textBox31);
      this.Controls.Add((Control) this.label23);
      this.Controls.Add((Control) this.textBox32);
      this.Controls.Add((Control) this.label24);
      this.Controls.Add((Control) this.textBox33);
      this.Controls.Add((Control) this.button10);
      this.Controls.Add((Control) this.textBox34);
      this.Controls.Add((Control) this.textBox35);
      this.Controls.Add((Control) this.label25);
      this.Controls.Add((Control) this.label26);
      this.Controls.Add((Control) this.button12);
      this.Controls.Add((Control) this.button9);
      this.Controls.Add((Control) this.button6);
      this.Controls.Add((Control) this.label20);
      this.Controls.Add((Control) this.textBox29);
      this.Controls.Add((Control) this.label19);
      this.Controls.Add((Control) this.textBox28);
      this.Controls.Add((Control) this.label18);
      this.Controls.Add((Control) this.textBox27);
      this.Controls.Add((Control) this.pictureBox7);
      this.Controls.Add((Control) this.label15);
      this.Controls.Add((Control) this.textBox24);
      this.Controls.Add((Control) this.button4);
      this.Controls.Add((Control) this.textBox25);
      this.Controls.Add((Control) this.textBox26);
      this.Controls.Add((Control) this.label16);
      this.Controls.Add((Control) this.label17);
      this.Controls.Add((Control) this.groupBox9);
      this.Controls.Add((Control) this.groupBox8);
      this.Controls.Add((Control) this.groupBox7);
      this.Controls.Add((Control) this.groupBox6);
      this.Controls.Add((Control) this.groupBox5);
      this.Controls.Add((Control) this.label4);
      this.Controls.Add((Control) this.groupBox4);
      this.Controls.Add((Control) this.textBox4);
      this.Controls.Add((Control) this.groupBox3);
      this.Controls.Add((Control) this.groupBox2);
      this.Controls.Add((Control) this.groupBox1);
      this.Controls.Add((Control) this.menuStrip1);
      this.Icon = (Icon) componentResourceManager.GetObject("$this.Icon");
      this.MainMenuStrip = this.menuStrip1;
      this.Name = nameof (AffinityEditor);
      this.Text = "Affinity Editor";
      this.Load += new EventHandler(this.AffinityEditor_Load);
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.groupBox2.ResumeLayout(false);
      this.groupBox3.ResumeLayout(false);
      this.groupBox3.PerformLayout();
      ((ISupportInitialize) this.pictureBox3).EndInit();
      ((ISupportInitialize) this.pictureBox1).EndInit();
      this.groupBox4.ResumeLayout(false);
      this.groupBox4.PerformLayout();
      ((ISupportInitialize) this.pictureBox5).EndInit();
      ((ISupportInitialize) this.pictureBox4).EndInit();
      ((ISupportInitialize) this.pictureBox2).EndInit();
      this.groupBox5.ResumeLayout(false);
      this.groupBox5.PerformLayout();
      this.toolStrip1.ResumeLayout(false);
      this.toolStrip1.PerformLayout();
      ((ISupportInitialize) this.dataGridView1).EndInit();
      this.groupBox6.ResumeLayout(false);
      this.groupBox6.PerformLayout();
      this.toolStrip2.ResumeLayout(false);
      this.toolStrip2.PerformLayout();
      ((ISupportInitialize) this.dataGridView2).EndInit();
      this.groupBox7.ResumeLayout(false);
      this.groupBox7.PerformLayout();
      this.toolStrip3.ResumeLayout(false);
      this.toolStrip3.PerformLayout();
      ((ISupportInitialize) this.dataGridView3).EndInit();
      this.groupBox8.ResumeLayout(false);
      ((ISupportInitialize) this.dataGridView4).EndInit();
      this.groupBox9.ResumeLayout(false);
      ((ISupportInitialize) this.dataGridView5).EndInit();
      ((ISupportInitialize) this.pictureBox7).EndInit();
      ((ISupportInitialize) this.pictureBox8).EndInit();
      ((ISupportInitialize) this.pictureBox9).EndInit();
      ((ISupportInitialize) this.pictureBox10).EndInit();
      ((ISupportInitialize) this.pictureBox11).EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();
    }

    private void exportAffinitylodToolStripMenuItem_Click(object sender, EventArgs e)
    {
      new LodExporter.LodExporter().Show();
    }

    private void toolStripButton7_Click(object sender, EventArgs e)
    {
    }

    private void toolStripButton5_Click(object sender, EventArgs e)
    {
    }

    private void toolStripButton3_Click(object sender, EventArgs e)
    {
    }

    private void toolStripButton6_Click(object sender, EventArgs e)
    {
      DataGridViewRow row = this.dataGridView3.Rows[this.dataGridView3.CurrentRow.Index];
      Convert.ToString(row.Cells["Column1"].Value);
      Convert.ToString(row.Cells["Column2"].Value);
      Convert.ToString(row.Cells["Column4"].Value);
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_magicLevel WHERE a_index ='" + Convert.ToString(row.Cells["index"].Value) + "' AND a_level = '" + Convert.ToString(row.Cells["Level"].Value) + "'");
      this.dataGridView3.Rows.Clear();
      this.LoadDG3();
    }

    private void toolStripButton4_Click(object sender, EventArgs e)
    {
    }

    private void toolStripButton8_Click(object sender, EventArgs e)
    {
    }

    private void step2ExportAffinitylodAgainForFixToolStripMenuItem_Click(
      object sender,
      EventArgs e)
    {
      new Affinity_EP4().Show();
    }

    private void dataGridView2_CellContentClick(object sender, DataGridViewCellEventArgs e)
    {
    }

    private void button4_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox26.Text = itemPicker.ItemIndex.ToString();
    }

    private void button9_Click(object sender, EventArgs e)
    {
      this.IniRead();
      if (MessageBox.Show("Do you want to Change Item Affinity Point " + this.textBox24.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      MySqlConnection connection = new MySqlConnection("datasource=" + this.textBox65.Text + ";port=3306;username=" + this.textBox66.Text + ";password=" + this.textBox67.Text);
      MySqlCommand mySqlCommand = new MySqlCommand("UPDATE " + this.textBox68.Text + ".t_affinity_work SET a_value='" + this.textBox25.Text + "' WHERE a_type_idx='" + this.textBox26.Text + "' AND a_affinity_idx='" + this.textBox29.Text + "' AND a_work_type='0'", connection);
      try
      {
        connection.Open();
        MySqlDataReader mySqlDataReader = mySqlCommand.ExecuteReader();
        int num = (int) MessageBox.Show("Your Affinity Point is Saved!");
        while (mySqlDataReader.Read())
          ;
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message);
      }
      this.LoadListBox();
    }

    private void button12_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want to delete " + this.textBox24.Text.Trim() + " ?", "Please confirm delete.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      if (this.textBox26.Text.Trim().Length <= 0)
      {
        int num = (int) MessageBox.Show("No data to delete in select item to delete first", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "delete from t_affinity_work where a_work_type ='0' AND a_type_idx = " + this.textBox26.Text.Trim());
        this.LoadListBox();
      }
    }

    private void button6_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want add New " + this.textBox24.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      if (this.textBox26.Text.Trim().Length <= 0)
      {
        int num1 = (int) MessageBox.Show("No data to select", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else if (this.textBox25.Text.Trim().Length <= 0)
      {
        int num2 = (int) MessageBox.Show("You need add point value", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_affinity_work (a_work_type, a_type_idx, a_affinity_idx, a_value, a_enable, a_id, a_row,a_col) VALUES (" + this.textBox28.Text + ", " + this.textBox26.Text + ", " + this.textBox1.Text + ", " + this.textBox25.Text + ", " + this.textBox27.Text + ", 0, 0, 0)");
        int num3 = (int) MessageBox.Show("Successful add new", "Completed", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
        this.LoadListBox();
      }
    }

    private void button10_Click(object sender, EventArgs e)
    {
      QuestPicker questPicker = new QuestPicker();
      if (questPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox35.Text = questPicker.QuestIndex.ToString();
    }

    private void button7_Click(object sender, EventArgs e)
    {
      this.IniRead();
      if (MessageBox.Show("Do you want to Change Affinity Point Quest" + this.textBox35.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      MySqlConnection connection = new MySqlConnection("datasource=" + this.textBox65.Text + ";port=3306;username=" + this.textBox66.Text + ";password=" + this.textBox67.Text);
      MySqlCommand mySqlCommand = new MySqlCommand("UPDATE " + this.textBox68.Text + ".t_affinity_work SET a_value='" + this.textBox34.Text + "' WHERE a_type_idx='" + this.textBox35.Text + "' AND a_affinity_idx='" + this.textBox30.Text + "' AND a_work_type='2'", connection);
      try
      {
        connection.Open();
        MySqlDataReader mySqlDataReader = mySqlCommand.ExecuteReader();
        int num = (int) MessageBox.Show("Your Affinity Point is Saved!");
        while (mySqlDataReader.Read())
          ;
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message);
      }
      this.LoadListBox();
    }

    private void button5_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want to delete QUEST" + this.textBox35.Text.Trim() + " ?", "Please confirm delete.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      if (this.textBox35.Text.Trim().Length <= 0)
      {
        int num = (int) MessageBox.Show("No data to delete in select item to delete first", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "delete from t_affinity_work where a_work_type ='2' AND a_type_idx = " + this.textBox35.Text.Trim());
        this.LoadListBox();
      }
    }

    private void button8_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want add New Quest " + this.textBox35.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      if (this.textBox35.Text.Trim().Length <= 0)
      {
        int num1 = (int) MessageBox.Show("No data to select", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else if (this.textBox34.Text.Trim().Length <= 0)
      {
        int num2 = (int) MessageBox.Show("You Need add point value", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_affinity_work (a_work_type, a_type_idx, a_affinity_idx, a_value, a_enable, a_id, a_row,a_col) VALUES (" + this.textBox31.Text + ", " + this.textBox35.Text + ", " + this.textBox1.Text + ", " + this.textBox34.Text + ", " + this.textBox32.Text + ", 0, 0, 0)");
        int num3 = (int) MessageBox.Show("Successful add new", "Completed", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
        this.LoadListBox();
      }
    }

    private void pictureBox8_Click(object sender, EventArgs e)
    {
      this.textBox44.Text = "0";
      this.textBox43.Text = "0";
      this.textBox42.Text = "0";
      IconPickerCombo iconPickerCombo = new IconPickerCombo();
      if (iconPickerCombo.ShowDialog() != DialogResult.OK)
        return;
      TextBox textBox44 = this.textBox44;
      int num = iconPickerCombo.TexID;
      string str1 = num.ToString();
      textBox44.Text = str1;
      TextBox textBox43 = this.textBox43;
      num = iconPickerCombo.TexRow;
      string str2 = num.ToString();
      textBox43.Text = str2;
      TextBox textBox42 = this.textBox42;
      num = iconPickerCombo.TexColumn;
      string str3 = num.ToString();
      textBox42.Text = str3;
      this.pictureBox9.Image = (Image) this.databaseHandle.IconCombo(int.Parse(this.textBox44.Text), int.Parse(this.textBox43.Text), int.Parse(this.textBox42.Text));
    }

    private void button11_Click(object sender, EventArgs e)
    {
      this.textBox39.Text = "0";
      MobPicker mobPicker = new MobPicker();
      if (mobPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox39.Text = mobPicker.MobIndex.ToString();
    }

    private void button14_Click(object sender, EventArgs e)
    {
      this.IniRead();
      if (MessageBox.Show("Do you want to Change Monster Data " + this.textBox40.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      MySqlConnection connection = new MySqlConnection("datasource=" + this.textBox65.Text + ";port=3306;username=" + this.textBox66.Text + ";password=" + this.textBox67.Text);
      MySqlCommand mySqlCommand = new MySqlCommand("UPDATE " + this.textBox68.Text + ".t_affinity_work SET a_value='" + this.textBox41.Text + "', a_id='" + this.textBox44.Text + "', a_row='" + this.textBox43.Text + "', a_col='" + this.textBox42.Text + "' WHERE a_type_idx='" + this.textBox39.Text + "' AND a_affinity_idx='" + this.textBox36.Text + "' AND a_work_type='1'", connection);
      try
      {
        connection.Open();
        MySqlDataReader mySqlDataReader = mySqlCommand.ExecuteReader();
        int num = (int) MessageBox.Show("Your Affinity Point is Saved!");
        while (mySqlDataReader.Read())
          ;
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message);
      }
      this.LoadListBox();
    }

    private void button13_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want to delete Monster" + this.textBox39.Text.Trim() + " ?", "Please confirm delete.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      if (this.textBox39.Text.Trim().Length <= 0)
      {
        int num = (int) MessageBox.Show("No data to delete in select item to delete first", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "delete from t_affinity_work where a_work_type ='1' AND a_type_idx = " + this.textBox39.Text.Trim());
        this.LoadListBox();
      }
    }

    private void button15_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want add New Monster " + this.textBox39.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      if (this.textBox39.Text.Trim().Length <= 0)
      {
        int num1 = (int) MessageBox.Show("No data to select", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else if (this.textBox41.Text.Trim().Length <= 0)
      {
        int num2 = (int) MessageBox.Show("You need add Point Value", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_affinity_work (a_work_type, a_type_idx, a_affinity_idx, a_value, a_enable, a_id, a_row,a_col) VALUES (" + this.textBox37.Text + ", " + this.textBox39.Text + ", " + this.textBox1.Text + ", " + this.textBox41.Text + ", " + this.textBox38.Text + ", " + this.textBox44.Text + ", " + this.textBox43.Text + ", " + this.textBox42.Text + ")");
        int num3 = (int) MessageBox.Show("Successful add new", "Completed", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
        this.LoadListBox();
      }
    }

    private void button18_Click(object sender, EventArgs e)
    {
      this.IniRead();
      if (MessageBox.Show("Do you want to Change Manager Npc Data " + this.textBox49.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      MySqlConnection connection = new MySqlConnection("datasource=" + this.textBox65.Text + ";port=3306;username=" + this.textBox66.Text + ";password=" + this.textBox67.Text);
      MySqlCommand mySqlCommand = new MySqlCommand("UPDATE " + this.textBox68.Text + ".t_affinity_npc SET a_use_point='" + this.textBox51.Text + "', a_string_idx='" + this.textBox52.Text + "', a_flag='" + this.textBox47.Text + "' WHERE a_npcidx='" + this.textBox49.Text + "' AND a_affinity_idx='" + this.textBox46.Text + "'", connection);
      try
      {
        connection.Open();
        MySqlDataReader mySqlDataReader = mySqlCommand.ExecuteReader();
        int num = (int) MessageBox.Show("Your Affinity is Saved!");
        while (mySqlDataReader.Read())
          ;
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message);
      }
      this.LoadListBox();
    }

    private void button17_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want to delete Manager NPC" + this.textBox49.Text.Trim() + " ?", "Please confirm delete.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      if (this.textBox49.Text.Trim().Length <= 0)
      {
        int num = (int) MessageBox.Show("No data to delete in select item to delete first", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "delete from t_affinity_npc where a_npcidx='" + this.textBox49.Text + "' AND a_affinity_idx = " + this.textBox46.Text.Trim());
        this.LoadListBox();
      }
    }

    private void button19_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want add New NPC " + this.textBox49.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      if (this.textBox49.Text.Trim().Length <= 0)
      {
        int num1 = (int) MessageBox.Show("No data to select", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else if (this.textBox47.Text.Trim().Length <= 0)
      {
        int num2 = (int) MessageBox.Show("You need add Flag Value", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_affinity_npc (a_affinity_idx, a_npcidx, a_use_point, a_enable, a_flag, a_string_idx) VALUES (" + this.textBox1.Text + ", " + this.textBox49.Text + ", " + this.textBox51.Text + ", " + this.textBox48.Text + ", " + this.textBox47.Text + ", " + this.textBox52.Text + ")");
        int num3 = (int) MessageBox.Show("Successful add new", "Completed", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
        this.LoadListBox();
      }
    }

    private void button16_Click(object sender, EventArgs e)
    {
      this.textBox49.Text = "0";
      MobPicker mobPicker = new MobPicker();
      if (mobPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox49.Text = mobPicker.MobIndex.ToString();
    }

    private void button20_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox55.Text = itemPicker.ItemIndex.ToString();
    }

    private void button21_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox59.Text = itemPicker.ItemIndex.ToString();
    }

    private void button23_Click(object sender, EventArgs e)
    {
      this.IniRead();
      if (MessageBox.Show("Do you want to Change Reward Data " + this.textBox59.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      MySqlConnection connection = new MySqlConnection("datasource=" + this.textBox65.Text + ";port=3306;username=" + this.textBox66.Text + ";password=" + this.textBox67.Text);
      MySqlCommand mySqlCommand = new MySqlCommand("UPDATE " + this.textBox68.Text + ".t_affinity_reward_item SET a_allow_point='" + this.textBox63.Text + "', a_flag='" + this.textBox62.Text + "', a_count='" + this.textBox61.Text + "', a_exp='" + this.textBox54.Text + "', a_sp='" + this.textBox56.Text + "', a_needpclevel='" + this.textBox53.Text + "', a_needitemidx='" + this.textBox55.Text + "', a_needitemcount='" + this.textBox57.Text + "' WHERE a_npcidx='" + this.textBox23.Text + "' AND a_itemidx='" + this.textBox59.Text + "'", connection);
      try
      {
        connection.Open();
        MySqlDataReader mySqlDataReader = mySqlCommand.ExecuteReader();
        int num = (int) MessageBox.Show("Your Affinity is Saved!");
        while (mySqlDataReader.Read())
          ;
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message);
      }
      this.LoadListBox();
    }

    private void button22_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want to delete Manager NPC" + this.textBox59.Text.Trim() + " ?", "Please confirm delete.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      if (this.textBox59.Text.Trim().Length <= 0)
      {
        int num = (int) MessageBox.Show("No data to delete in select item to delete first", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "delete from t_affinity_reward_item where a_npcidx='" + this.textBox23.Text + "' AND a_itemidx = " + this.textBox59.Text.Trim());
        this.LoadListBox();
      }
    }

    private void button24_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want add New Reward " + this.textBox59.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      if (this.textBox23.Text.Trim().Length <= 0)
      {
        int num1 = (int) MessageBox.Show("No Manager NPC Plsase add NPC", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else if (this.textBox59.Text.Trim().Length <= 0)
      {
        int num2 = (int) MessageBox.Show("No data to select", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else if (this.textBox63.Text.Trim().Length <= 0)
      {
        int num3 = (int) MessageBox.Show("You need add allow point ", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_affinity_reward_item (a_npcidx, a_allow_point, a_itemidx, a_flag, a_count, a_exp, a_sp, a_needpclevel, a_needitemidx, a_needitemcount) VALUES (" + this.textBox23.Text + ", " + this.textBox63.Text + ", " + this.textBox59.Text + ", " + this.textBox62.Text + ", " + this.textBox61.Text + ", " + this.textBox54.Text + ", " + this.textBox56.Text + ", " + this.textBox53.Text + ", " + this.textBox55.Text + ", " + this.textBox57.Text + ")");
        int num4 = (int) MessageBox.Show("Successful add new", "Completed", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
        this.LoadListBox();
      }
    }

    private void button3_Click(object sender, EventArgs e)
    {
      this.IniRead();
      if (MessageBox.Show("Do you want to Change data Affinity id " + this.textBox1.Text.Trim() + "-" + this.textBox2.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      if (this.language == "THA")
      {
        this.textBox2.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        string str = this.textBox2.Text.Replace("'", "\\'").Replace("\"", "\\\"");
        MySqlConnection connection = new MySqlConnection("datasource=" + this.textBox65.Text + ";port=3306;username=" + this.textBox66.Text + ";password=" + this.textBox67.Text);
        MySqlCommand mySqlCommand = new MySqlCommand("UPDATE " + this.textBox68.Text + ".t_affinity SET a_name_thai='" + str + "', a_maxvalue='" + this.textBox3.Text + "', a_texture_id='" + this.textBox5.Text + "', a_texture_row='" + this.textBox6.Text + "', a_texture_col='" + this.textBox7.Text + "', a_nas='" + this.textBox8.Text + "', a_needlevel='" + this.textBox9.Text + "', a_needitemidx='" + this.textBox10.Text + "', a_needitemcount='" + this.textBox11.Text + "', a_affinity_idx='" + this.textBox12.Text + "', a_affinity_value='" + this.textBox13.Text + "' WHERE a_index='" + this.textBox1.Text + "'", connection);
        try
        {
          connection.Open();
          MySqlDataReader mySqlDataReader = mySqlCommand.ExecuteReader();
          int num = (int) MessageBox.Show("Affinity " + this.textBox2.Text.Trim() + " บันทึกแล้ว!");
          while (mySqlDataReader.Read())
            ;
        }
        catch (Exception ex)
        {
          int num = (int) MessageBox.Show(ex.Message);
        }
      }
      else
      {
        MySqlConnection connection = new MySqlConnection("datasource=" + this.textBox65.Text + ";port=3306;username=" + this.textBox66.Text + ";password=" + this.textBox67.Text);
        MySqlCommand mySqlCommand = new MySqlCommand("UPDATE " + this.textBox68.Text + ".t_affinity SET a_name='" + this.textBox2.Text + "', a_maxvalue='" + this.textBox3.Text + "', a_texture_id='" + this.textBox5.Text + "', a_texture_row='" + this.textBox6.Text + "', a_texture_col='" + this.textBox7.Text + "', a_nas='" + this.textBox8.Text + "', a_needlevel='" + this.textBox9.Text + "', a_needitemidx='" + this.textBox10.Text + "', a_needitemcount='" + this.textBox11.Text + "', a_affinity_idx='" + this.textBox12.Text + "', a_affinity_value='" + this.textBox13.Text + "' WHERE a_index='" + this.textBox1.Text + "'", connection);
        try
        {
          connection.Open();
          MySqlDataReader mySqlDataReader = mySqlCommand.ExecuteReader();
          int num = (int) MessageBox.Show("Your Affinity " + this.textBox2.Text.Trim() + " is Saved!");
          while (mySqlDataReader.Read())
            ;
        }
        catch (Exception ex)
        {
          int num = (int) MessageBox.Show(ex.Message);
        }
      }
      this.LoadListBox();
    }

    private void button25_Click(object sender, EventArgs e) => new Affinity_EP4().Show();

    private void exportStrAffinitylodToolStripMenuItem_Click(object sender, EventArgs e)
    {
      new FormExport().Show();
    }
  }
}
