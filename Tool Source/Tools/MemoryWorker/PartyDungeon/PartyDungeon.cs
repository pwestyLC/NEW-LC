// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.PartyDungeon.PartyDungeon
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
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.PartyDungeon
{
  public class PartyDungeon : Form
  {
    public static Connection connection = new Connection();
    private string Host = LcDevPack_TeamDamonA.Tools.MemoryWorker.PartyDungeon.PartyDungeon.connection.Settings.SqlHost;
    private string User = LcDevPack_TeamDamonA.Tools.MemoryWorker.PartyDungeon.PartyDungeon.connection.Settings.SqlUser;
    private string Password = LcDevPack_TeamDamonA.Tools.MemoryWorker.PartyDungeon.PartyDungeon.connection.Settings.SqlPassword;
    private string Database = LcDevPack_TeamDamonA.Tools.MemoryWorker.PartyDungeon.PartyDungeon.connection.Settings.SqlDatabase;
    private string DB_Database = LcDevPack_TeamDamonA.Tools.MemoryWorker.PartyDungeon.PartyDungeon.connection.Settings.SqlDbDatabase;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    public string _ClientPath = LcDevPack_TeamDamonA.Tools.MemoryWorker.PartyDungeon.PartyDungeon.connection.Settings.ClientPath;
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
    private string country;
    public static string namee;
        private bool initialized;
        private string language = LcDevPack_TeamDamonA.Tools.MemoryWorker.PartyDungeon.PartyDungeon.connection.Settings.Language;
    public string[] menuArray = new string[2]
    {
      "a_index",
      "a_string"
    };
    public string[] menuArrayGER = new string[2]
    {
      "a_index",
      "a_string_ger"
    };
    public string[] menuArrayPOL = new string[2]
    {
      "a_index",
      "a_string_pld"
    };
    public string[] menuArrayBRA = new string[2]
    {
      "a_index",
      "a_string_brz"
    };
    public string[] menuArrayRUS = new string[2]
    {
      "a_index",
      "a_string_rus"
    };
    public string[] menuArrayFRA = new string[2]
    {
      "a_index",
      "a_string_frc"
    };
    public string[] menuArrayESP = new string[2]
    {
      "a_index",
      "a_string_spn"
    };
    public string[] menuArrayMEX = new string[2]
    {
      "a_index",
      "a_string_mex"
    };
    public string[] menuArrayTHA = new string[2]
    {
      "a_index",
      "a_string_thai"
    };
    public string[] menuArrayITA = new string[2]
    {
      "a_index",
      "a_string_ita"
    };
    private GroupBox groupBox2;
    private DataGridView dgItems;
    private TextBox textBox16;
    private ComboBox comboBox1;
    private Label label6;
    private Button button18;
    private TextBox textBox4;
    private TextBox textBox7;
    private TextBox textBox8;
    private GroupBox groupBox4;
    private TextBox a_need_item_count;
    private Label label9;
    private Button bt_needitem;
    private TextBox need_item_name;
    private TextBox a_need_item_idx;
    private PictureBox pictureBox2;
    private Label label10;
    private Label label11;
    private GroupBox groupBox3;
    private Button bt_title;
    private TextBox Title_name;
    private TextBox Title_Id;
    private PictureBox pictureBox9;
    private Label label36;
    private Label label37;
    private GroupBox groupBox5;
    private TextBox Box_Count;
    private Label label38;
    private Button bt_box;
    private TextBox Box_name;
    private TextBox Box_Id;
    private PictureBox pictureBox10;
    private Label label39;
    private Label label40;
    private GroupBox groupBox6;
    private CheckBox checkBox5;
    private CheckBox checkBox4;
    private CheckBox checkBox3;
    private CheckBox checkBox2;
    private CheckBox checkBox1;
    private TextBox r_t_id5_count;
    private Label label18;
    private Button bt_r_t_id5;
    private TextBox r_t_id5_name;
    private TextBox r_t_id5;
    private PictureBox pictureBox7;
    private TextBox r_t_id4_count;
    private Label label15;
    private Button bt_r_t_id4;
    private TextBox r_t_id4_name;
    private TextBox r_t_id4;
    private PictureBox pictureBox6;
    private TextBox r_t_id3_count;
    private Label label12;
    private Button bt_r_t_id3;
    private TextBox r_t_id3_name;
    private TextBox r_t_id3;
    private PictureBox pictureBox5;
    private TextBox r_t_id2_count;
    private Label label13;
    private Button bt_r_t_id2;
    private TextBox r_t_id2_name;
    private TextBox r_t_id2;
    private PictureBox pictureBox4;
    private TextBox r_t_id1_count;
    private Label label14;
    private Button bt_r_t_id1;
    private TextBox r_t_id1_name;
    private TextBox r_t_id1;
    private PictureBox pictureBox3;
    private Label label19;
    private Label label20;
    private Label label16;
    private Label label17;
    private Label label24;
    private Label label25;
    private Label label26;
    private Label label27;
    private Label label28;
    private Label label29;
    private GroupBox Boss1_npc;
    private Label label43;
    private Label label42;
    private Label label41;
    private PictureBox pictureBox8;
    private PictureBox pictureBox11;
    private Button bt_boss3;
    private TextBox Boss3_name;
    private TextBox Boss_id3;
    private Label label33;
    private Label label34;
    private Button bt_boss2;
    private TextBox Boss2_name;
    private TextBox Boss_id2;
    private Label label22;
    private Label label23;
    private Button bt_boss1;
    private TextBox Boss1_name;
    private TextBox Boss_id1;
    private PictureBox pc_npc;
    private Label label7;
    private Label label8;
    private TextBox index;
    private Label label21;
    private TextBox Zone_Id;
    private Label label1;
    private TextBox Difficulty;
    private Label label2;
    private TextBox CP;
    private Label label4;
    private TextBox Level;
    private Label label3;
    private TextBox Party_member;
    private Label label35;
    private TextBox Time;
    private Label label44;
    private TextBox DominationPoint;
    private Label label31;
    private TextBox Domination1;
    private Label label30;
    private TextBox Domination0;
    private Label label5;
    private TextBox Type;
    private Label label32;
    private TextBox Info;
    private Label label45;
    private DataGridViewTextBoxColumn Zone;
    private DataGridViewTextBoxColumn ZoneId;
    private TextBox textBoxLevel;
    private TextBox textBoxDifficulty;
    private TextBox textBoxTime;
    public string[] menuArrayUSA = new string[2]
    {
      "a_index",
      "a_string_usa"
    };

    public PartyDungeon()
    {
      
      this.InitializeComponent();
      this.LoadDG();
      this.LoadStartUp();
      this.comboBox1.SelectedIndex = 0;
    }

    private string StringFromLanguage()
    {
      if (this.language == "GER")
      {
        LcDevPack_TeamDamonA.Tools.MemoryWorker.PartyDungeon.PartyDungeon.namee = "a_string_ger";
        return LcDevPack_TeamDamonA.Tools.MemoryWorker.PartyDungeon.PartyDungeon.namee;
      }
      if (this.language == "POL")
      {
        LcDevPack_TeamDamonA.Tools.MemoryWorker.PartyDungeon.PartyDungeon.namee = "a_string_pld";
        return LcDevPack_TeamDamonA.Tools.MemoryWorker.PartyDungeon.PartyDungeon.namee;
      }
      if (this.language == "BRA")
      {
        LcDevPack_TeamDamonA.Tools.MemoryWorker.PartyDungeon.PartyDungeon.namee = "a_string_brz";
        return LcDevPack_TeamDamonA.Tools.MemoryWorker.PartyDungeon.PartyDungeon.namee;
      }
      if (this.language == "RUS")
      {
        LcDevPack_TeamDamonA.Tools.MemoryWorker.PartyDungeon.PartyDungeon.namee = "a_string_rus";
        return LcDevPack_TeamDamonA.Tools.MemoryWorker.PartyDungeon.PartyDungeon.namee;
      }
      if (this.language == "FRA")
      {
        LcDevPack_TeamDamonA.Tools.MemoryWorker.PartyDungeon.PartyDungeon.namee = "a_string_frc";
        return LcDevPack_TeamDamonA.Tools.MemoryWorker.PartyDungeon.PartyDungeon.namee;
      }
      if (this.language == "ESP")
      {
        LcDevPack_TeamDamonA.Tools.MemoryWorker.PartyDungeon.PartyDungeon.namee = "a_string_spn";
        return LcDevPack_TeamDamonA.Tools.MemoryWorker.PartyDungeon.PartyDungeon.namee;
      }
      if (this.language == "MEX")
      {
        LcDevPack_TeamDamonA.Tools.MemoryWorker.PartyDungeon.PartyDungeon.namee = "a_string_mex";
        return LcDevPack_TeamDamonA.Tools.MemoryWorker.PartyDungeon.PartyDungeon.namee;
      }
      if (this.language == "THA")
      {
        LcDevPack_TeamDamonA.Tools.MemoryWorker.PartyDungeon.PartyDungeon.namee = "a_string_thai";
        return LcDevPack_TeamDamonA.Tools.MemoryWorker.PartyDungeon.PartyDungeon.namee;
      }
      if (this.language == "ITA")
      {
        LcDevPack_TeamDamonA.Tools.MemoryWorker.PartyDungeon.PartyDungeon.namee = "a_string_ita";
        return LcDevPack_TeamDamonA.Tools.MemoryWorker.PartyDungeon.PartyDungeon.namee;
      }
      if (!(this.language == "USA"))
        return (string) null;
      LcDevPack_TeamDamonA.Tools.MemoryWorker.PartyDungeon.PartyDungeon.namee = "a_string_usa";
      return LcDevPack_TeamDamonA.Tools.MemoryWorker.PartyDungeon.PartyDungeon.namee;
    }

        private void LoadStartUp()
        {
            // Query simplified and fixed (removed invalid MAX() alias)
            string query = @"
        SELECT 
            a_index,
            a_zonetid,
            a_difficulty,
            a_level,
            a_cp,
            a_need_item_idx,
            a_need_item_count,
            a_member_need,
            a_time,
            a_reward_item_idx,
            a_reward_item_count,
            a_reward_item_idx1,
            a_reward_item_count1,
            a_reward_item_idx2,
            a_reward_item_count2,
            a_reward_item_idx3,
            a_reward_item_count3,
            a_reward_item_idx4,
            a_reward_item_count4,
            a_tittle_reward,
            a_box_reward,
            a_box_count,
            a_boss_idx1,
            a_boss_idx2,
            a_boss_idx3,
            a_domination0,
            a_domination1,
            a_domination_point,
            a_type,
            a_info
        FROM t_cloud_partyexpedition_config
        ORDER BY a_zonetid ASC
        LIMIT 1;
    ";

            using (var conn = new MySqlConnection(
                $"datasource={Host};Port=3306;User ID={User};Password={Password};Database={Database};Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;"))
            using (var cmd = new MySqlCommand(query, conn))
            {
                conn.Open();

                using (var reader = cmd.ExecuteReader())
                {
                    if (reader.Read())
                    {
                        int zoneId = reader.GetInt32("a_zonetid");
                        int level = reader.GetInt32("a_level");
                        int difficulty = reader.GetInt32("a_difficulty");
                        int time = reader.GetInt32("a_time");

                        // Populate your UI
                        textBox8.Text = zoneId.ToString();
                        textBoxLevel.Text = level.ToString();
                        textBoxDifficulty.Text = difficulty.ToString();
                        textBoxTime.Text = time.ToString();
                    }
                    else
                    {
                        MessageBox.Show("No expedition data found in the table!");
                    }
                }
            }
        }


        public void LoadDG()
        {
            
            dgItems.Rows.Clear();

            string query = @"
        SELECT 
            a_index, a_zonetid, a_difficulty, a_level, a_cp,
            a_need_item_idx, a_need_item_count, a_member_need, a_time,
            a_reward_item_idx, a_reward_item_count,
            a_reward_item_idx1, a_reward_item_count1,
            a_reward_item_idx2, a_reward_item_count2,
            a_reward_item_idx3, a_reward_item_count3,
            a_reward_item_idx4, a_reward_item_count4,
            a_tittle_reward, a_box_reward, a_box_count,
            a_boss_idx1, a_boss_idx2, a_boss_idx3,
            a_domination0, a_domination1, a_domination_point,
            a_type, a_info
        FROM t_cloud_partyexpedition_config
        GROUP BY a_zonetid;
    ";

            using (var conn = new MySqlConnection(
                $"datasource={Host};Port=3306;User ID={User};Password={Password};Database={Database};Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;"))
            using (var cmd = new MySqlCommand(query, conn))
            {
                conn.Open();
                using (var reader = cmd.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        int zoneId = reader.GetInt32("a_zonetid");
                        int level = reader.GetInt32("a_level");
                        int difficulty = reader.GetInt32("a_difficulty");
                        int time = reader.GetInt32("a_time");

                        int rewardItem = reader.GetInt32("a_reward_item_idx");
                        int rewardCount = reader.GetInt32("a_reward_item_count");

                        // use your DatabaseHandle to get item name and icon
                        Bitmap icon = databaseHandle.IconFast(rewardItem);
                        string itemName = databaseHandle.ItemNameFast(rewardItem);

                        dgItems.Rows.Add(
                            "Party Dungeon Zone",
                            zoneId,
                            difficulty,
                            level,
                            $"{time / 60} min",
                            icon,
                            $"{itemName} × {rewardCount}"
                        );
                    }
                }
            }
            if (dgItems.Rows.Count > 0)
            {
                dgItems.Rows[0].Selected = true;
                Zone_Id.Text = dgItems.Rows[0].Cells["ZoneId"].Value.ToString();

                // Set default difficulty if not already chosen
                if (comboBox1.SelectedIndex < 0)
                    comboBox1.SelectedIndex = 0;

                // Load rewards automatically
                LoadDifficult();
            }
        }


        public void LoadDifficult()
        {
            string query = $@"
        SELECT 
            a_index, a_zonetid, a_difficulty, a_level, a_cp, 
            a_need_item_idx, a_need_item_count, a_member_need, a_time,
            a_reward_item_idx, a_reward_item_count,
            a_reward_item_idx1, a_reward_item_count1,
            a_reward_item_idx2, a_reward_item_count2,
            a_reward_item_idx3, a_reward_item_count3,
            a_reward_item_idx4, a_reward_item_count4,
            a_tittle_reward, a_box_reward, a_box_count,
            a_boss_idx1, a_boss_idx2, a_boss_idx3,
            a_domination0, a_domination1, a_domination_point,
            a_type, a_info
        FROM t_cloud_partyexpedition_config
        WHERE a_zonetid = @ZoneId AND a_difficulty = @Difficulty;
    ";

            using (var conn = new MySqlConnection(
                $"datasource={Host};Port=3306;User ID={User};Password={Password};Database={Database};Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;"))
            using (var cmd = new MySqlCommand(query, conn))
            {
                // Parameterized query — prevents SQL injection
                cmd.Parameters.AddWithValue("@ZoneId", Zone_Id.Text);
                cmd.Parameters.AddWithValue("@Difficulty", textBox16.Text);

                conn.Open();
                using (var reader = cmd.ExecuteReader())
                {
                    if (!reader.Read())
                    {
                        ClearDifficultyFields();
                        return;
                    }

                    // Assign directly via field names
                    Difficulty.Text = reader["a_difficulty"].ToString();
                    Level.Text = reader["a_level"].ToString();
                    CP.Text = reader["a_cp"].ToString();
                    a_need_item_idx.Text = reader["a_need_item_idx"].ToString();
                    a_need_item_count.Text = reader["a_need_item_count"].ToString();
                    Party_member.Text = reader["a_member_need"].ToString();
                    Time.Text = reader["a_time"].ToString();

                    r_t_id1.Text = reader["a_reward_item_idx"].ToString();
                    r_t_id1_count.Text = reader["a_reward_item_count"].ToString();
                    r_t_id2.Text = reader["a_reward_item_idx1"].ToString();
                    r_t_id2_count.Text = reader["a_reward_item_count1"].ToString();
                    r_t_id3.Text = reader["a_reward_item_idx2"].ToString();
                    r_t_id3_count.Text = reader["a_reward_item_count2"].ToString();
                    r_t_id4.Text = reader["a_reward_item_idx3"].ToString();
                    r_t_id4_count.Text = reader["a_reward_item_count3"].ToString();
                    r_t_id5.Text = reader["a_reward_item_idx4"].ToString();
                    r_t_id5_count.Text = reader["a_reward_item_count4"].ToString();

                    Title_Id.Text = reader["a_tittle_reward"].ToString();
                    Box_Id.Text = reader["a_box_reward"].ToString();
                    Box_Count.Text = reader["a_box_count"].ToString();

                    Boss_id1.Text = reader["a_boss_idx1"].ToString();
                    Boss_id2.Text = reader["a_boss_idx2"].ToString();
                    Boss_id3.Text = reader["a_boss_idx3"].ToString();

                    Domination0.Text = reader["a_domination0"].ToString();
                    Domination1.Text = reader["a_domination1"].ToString();
                    DominationPoint.Text = reader["a_domination_point"].ToString();

                    Type.Text = reader["a_type"].ToString();
                    Info.Text = reader["a_info"].ToString();
                }
            }
        }


        private void dgItems_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex < 0)
                return;

            // Get selected zone
            this.Zone_Id.Text = this.dgItems.Rows[e.RowIndex].Cells["ZoneId"].Value.ToString();

           
            int currentDifficulty = comboBox1.SelectedIndex;
            if (currentDifficulty < 0)
                currentDifficulty = 0; 

            
            this.LoadDifficult();

            
            comboBox1.SelectedIndex = currentDifficulty;
        }

        private int GetID()
    {
      int result = -1;
      int.TryParse(this.Zone_Id.Text.Split(' ')[0], out result);
      return result;
    }

    private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox16.Text = this.comboBox1.SelectedIndex.ToString();
      this.LoadDifficult();
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
    }

    private void button2_Click(object sender, EventArgs e)
    {
    }

    private void button4_Click(object sender, EventArgs e)
    {
    }

    private void r_t_id1_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox3.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.r_t_id1.Text.Trim()));
      this.r_t_id1_name.Text = this.databaseHandle.ItemNameFast(int.Parse(this.r_t_id1.Text.Trim()));
    }

    private void r_t_id2_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox4.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.r_t_id2.Text.Trim()));
      this.r_t_id2_name.Text = this.databaseHandle.ItemNameFast(int.Parse(this.r_t_id2.Text.Trim()));
    }

    private void r_t_id3_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox5.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.r_t_id3.Text.Trim()));
      this.r_t_id3_name.Text = this.databaseHandle.ItemNameFast(int.Parse(this.r_t_id3.Text.Trim()));
    }

    private void r_t_id4_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox6.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.r_t_id4.Text.Trim()));
      this.r_t_id4_name.Text = this.databaseHandle.ItemNameFast(int.Parse(this.r_t_id4.Text.Trim()));
    }

    private void r_t_id5_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox7.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.r_t_id5.Text.Trim()));
      this.r_t_id5_name.Text = this.databaseHandle.ItemNameFast(int.Parse(this.r_t_id5.Text.Trim()));
    }

    private void a_need_item_idx_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox2.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.a_need_item_idx.Text.Trim()));
      this.need_item_name.Text = this.databaseHandle.ItemNameFast(int.Parse(this.a_need_item_idx.Text.Trim()));
    }

    private void Title_Id_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox9.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.Title_Id.Text.Trim()));
      this.Title_name.Text = this.databaseHandle.ItemNameFast(int.Parse(this.Title_Id.Text.Trim()));
    }

    private void Box_Id_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox10.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.Box_Id.Text.Trim()));
      this.Box_name.Text = this.databaseHandle.ItemNameFast(int.Parse(this.Box_Id.Text.Trim()));
    }

    private void Boss_id1_TextChanged(object sender, EventArgs e)
    {
      this.Boss1_name.Text = this.databaseHandle.MobNameFast(int.Parse(this.Boss_id1.Text.Trim()));
    }

    private void Boss_id2_TextChanged(object sender, EventArgs e)
    {
      this.Boss2_name.Text = this.databaseHandle.MobNameFast(int.Parse(this.Boss_id2.Text.Trim()));
    }

    private void Boss_id3_TextChanged(object sender, EventArgs e)
    {
      this.Boss3_name.Text = this.databaseHandle.MobNameFast(int.Parse(this.Boss_id3.Text.Trim()));
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
      this.Info = new TextBox();
      this.label45 = new Label();
      this.Type = new TextBox();
      this.label32 = new Label();
      this.DominationPoint = new TextBox();
      this.label31 = new Label();
      this.Domination1 = new TextBox();
      this.label30 = new Label();
      this.Domination0 = new TextBox();
      this.label5 = new Label();
      this.Time = new TextBox();
      this.label44 = new Label();
      this.Party_member = new TextBox();
      this.label35 = new Label();
      this.CP = new TextBox();
      this.label4 = new Label();
      this.Level = new TextBox();
      this.label3 = new Label();
      this.Difficulty = new TextBox();
      this.label2 = new Label();
      this.Zone_Id = new TextBox();
      this.label1 = new Label();
      this.index = new TextBox();
      this.label21 = new Label();
      this.groupBox2 = new GroupBox();
      this.dgItems = new DataGridView();
      this.Zone = new DataGridViewTextBoxColumn();
      this.ZoneId = new DataGridViewTextBoxColumn();
      this.textBox4 = new TextBox();
      this.textBox16 = new TextBox();
      this.comboBox1 = new ComboBox();
      this.label6 = new Label();
      this.textBox7 = new TextBox();
      this.textBox8 = new TextBox();
      this.groupBox4 = new GroupBox();
      this.a_need_item_count = new TextBox();
      this.label9 = new Label();
      this.need_item_name = new TextBox();
      this.a_need_item_idx = new TextBox();
      this.label10 = new Label();
      this.label11 = new Label();
      this.groupBox3 = new GroupBox();
      this.Title_name = new TextBox();
      this.Title_Id = new TextBox();
      this.label36 = new Label();
      this.label37 = new Label();
      this.groupBox5 = new GroupBox();
      this.Box_Count = new TextBox();
      this.label38 = new Label();
      this.Box_name = new TextBox();
      this.Box_Id = new TextBox();
      this.label39 = new Label();
      this.label40 = new Label();
      this.groupBox6 = new GroupBox();
      this.checkBox5 = new CheckBox();
      this.checkBox4 = new CheckBox();
      this.checkBox3 = new CheckBox();
      this.checkBox2 = new CheckBox();
      this.checkBox1 = new CheckBox();
      this.r_t_id5_count = new TextBox();
      this.label18 = new Label();
      this.r_t_id5_name = new TextBox();
      this.r_t_id5 = new TextBox();
      this.r_t_id4_count = new TextBox();
      this.label15 = new Label();
      this.r_t_id4_name = new TextBox();
      this.r_t_id4 = new TextBox();
      this.r_t_id3_count = new TextBox();
      this.label12 = new Label();
      this.r_t_id3_name = new TextBox();
      this.r_t_id3 = new TextBox();
      this.r_t_id2_count = new TextBox();
      this.label13 = new Label();
      this.r_t_id2_name = new TextBox();
      this.r_t_id2 = new TextBox();
      this.r_t_id1_count = new TextBox();
      this.label14 = new Label();
      this.r_t_id1_name = new TextBox();
      this.r_t_id1 = new TextBox();
      this.label19 = new Label();
      this.label20 = new Label();
      this.label16 = new Label();
      this.label17 = new Label();
      this.label24 = new Label();
      this.label25 = new Label();
      this.label26 = new Label();
      this.label27 = new Label();
      this.label28 = new Label();
      this.label29 = new Label();
      this.Boss1_npc = new GroupBox();
      this.label43 = new Label();
      this.label42 = new Label();
      this.label41 = new Label();
      this.Boss3_name = new TextBox();
      this.Boss_id3 = new TextBox();
      this.label33 = new Label();
      this.label34 = new Label();
      this.Boss2_name = new TextBox();
      this.Boss_id2 = new TextBox();
      this.label22 = new Label();
      this.label23 = new Label();
      this.Boss1_name = new TextBox();
      this.Boss_id1 = new TextBox();
      this.label7 = new Label();
      this.label8 = new Label();
      this.pictureBox8 = new PictureBox();
      this.pictureBox11 = new PictureBox();
      this.bt_boss3 = new Button();
      this.bt_boss2 = new Button();
      this.bt_boss1 = new Button();
      this.pc_npc = new PictureBox();
      this.bt_r_t_id5 = new Button();
      this.pictureBox7 = new PictureBox();
      this.bt_r_t_id4 = new Button();
      this.pictureBox6 = new PictureBox();
      this.bt_r_t_id3 = new Button();
      this.pictureBox5 = new PictureBox();
      this.bt_r_t_id2 = new Button();
      this.pictureBox4 = new PictureBox();
      this.bt_r_t_id1 = new Button();
      this.pictureBox3 = new PictureBox();
      this.bt_box = new Button();
      this.pictureBox10 = new PictureBox();
      this.bt_title = new Button();
      this.pictureBox9 = new PictureBox();
      this.bt_needitem = new Button();
      this.pictureBox2 = new PictureBox();
      this.button18 = new Button();
      this.groupBox1.SuspendLayout();
      this.groupBox2.SuspendLayout();
      ((ISupportInitialize) this.dgItems).BeginInit();
      this.groupBox4.SuspendLayout();
      this.groupBox3.SuspendLayout();
      this.groupBox5.SuspendLayout();
      this.groupBox6.SuspendLayout();
      this.Boss1_npc.SuspendLayout();
      ((ISupportInitialize) this.pictureBox8).BeginInit();
      ((ISupportInitialize) this.pictureBox11).BeginInit();
      ((ISupportInitialize) this.pc_npc).BeginInit();
      ((ISupportInitialize) this.pictureBox7).BeginInit();
      ((ISupportInitialize) this.pictureBox6).BeginInit();
      ((ISupportInitialize) this.pictureBox5).BeginInit();
      ((ISupportInitialize) this.pictureBox4).BeginInit();
      ((ISupportInitialize) this.pictureBox3).BeginInit();
      ((ISupportInitialize) this.pictureBox10).BeginInit();
      ((ISupportInitialize) this.pictureBox9).BeginInit();
      ((ISupportInitialize) this.pictureBox2).BeginInit();
      this.SuspendLayout();
      this.groupBox1.Controls.Add((Control) this.Info);
      this.groupBox1.Controls.Add((Control) this.label45);
      this.groupBox1.Controls.Add((Control) this.Type);
      this.groupBox1.Controls.Add((Control) this.label32);
      this.groupBox1.Controls.Add((Control) this.DominationPoint);
      this.groupBox1.Controls.Add((Control) this.label31);
      this.groupBox1.Controls.Add((Control) this.Domination1);
      this.groupBox1.Controls.Add((Control) this.label30);
      this.groupBox1.Controls.Add((Control) this.Domination0);
      this.groupBox1.Controls.Add((Control) this.label5);
      this.groupBox1.Controls.Add((Control) this.Time);
      this.groupBox1.Controls.Add((Control) this.label44);
      this.groupBox1.Controls.Add((Control) this.Party_member);
      this.groupBox1.Controls.Add((Control) this.label35);
      this.groupBox1.Controls.Add((Control) this.CP);
      this.groupBox1.Controls.Add((Control) this.label4);
      this.groupBox1.Controls.Add((Control) this.Level);
      this.groupBox1.Controls.Add((Control) this.label3);
      this.groupBox1.Controls.Add((Control) this.Difficulty);
      this.groupBox1.Controls.Add((Control) this.label2);
      this.groupBox1.Controls.Add((Control) this.Zone_Id);
      this.groupBox1.Controls.Add((Control) this.label1);
      this.groupBox1.Controls.Add((Control) this.index);
      this.groupBox1.Controls.Add((Control) this.label21);
      this.groupBox1.Controls.Add((Control) this.button18);
      this.groupBox1.Location = new Point(11, 334);
      this.groupBox1.Margin = new Padding(4);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Padding = new Padding(4);
      this.groupBox1.Size = new Size(433, 331);
      this.groupBox1.TabIndex = 2;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Dungeon Info";
      this.Info.Location = new Point(54, 238);
      this.Info.Margin = new Padding(4);
      this.Info.Name = "Info";
      this.Info.Size = new Size(345, 22);
      this.Info.TabIndex = (int) sbyte.MaxValue;
      this.label45.AutoSize = true;
      this.label45.Location = new Point(11, 241);
      this.label45.Margin = new Padding(4, 0, 4, 0);
      this.label45.Name = "label45";
      this.label45.Size = new Size(37, 16);
      this.label45.TabIndex = 126;
      this.label45.Text = "Info : ";
      this.Type.Enabled = false;
      this.Type.Location = new Point(334, 124);
      this.Type.Margin = new Padding(4);
      this.Type.Name = "Type";
      this.Type.Size = new Size(65, 22);
      this.Type.TabIndex = 124;
      this.Type.TextAlign = HorizontalAlignment.Center;
      this.label32.AutoSize = true;
      this.label32.Location = new Point(284, (int) sbyte.MaxValue);
      this.label32.Margin = new Padding(4, 0, 4, 0);
      this.label32.Name = "label32";
      this.label32.Size = new Size(48, 16);
      this.label32.TabIndex = 125;
      this.label32.Text = "Type : ";
      this.DominationPoint.Location = new Point(288, 204);
      this.DominationPoint.Margin = new Padding(4);
      this.DominationPoint.Name = "DominationPoint";
      this.DominationPoint.Size = new Size(65, 22);
      this.DominationPoint.TabIndex = 123;
      this.label31.AutoSize = true;
      this.label31.Location = new Point(174, 208);
      this.label31.Margin = new Padding(4, 0, 4, 0);
      this.label31.Name = "label31";
      this.label31.Size = new Size(114, 16);
      this.label31.TabIndex = 122;
      this.label31.Text = "domination point : ";
      this.Domination1.Location = new Point(289, 166);
      this.Domination1.Margin = new Padding(4);
      this.Domination1.Name = "Domination1";
      this.Domination1.Size = new Size(65, 22);
      this.Domination1.TabIndex = 121;
      this.label30.AutoSize = true;
      this.label30.Location = new Point(199, 169);
      this.label30.Margin = new Padding(4, 0, 4, 0);
      this.label30.Name = "label30";
      this.label30.Size = new Size(89, 16);
      this.label30.TabIndex = 120;
      this.label30.Text = "domination1 : ";
      this.Domination0.Location = new Point(116, 166);
      this.Domination0.Margin = new Padding(4);
      this.Domination0.Name = "Domination0";
      this.Domination0.Size = new Size(65, 22);
      this.Domination0.TabIndex = 119;
      this.label5.AutoSize = true;
      this.label5.Location = new Point(19, 169);
      this.label5.Margin = new Padding(4, 0, 4, 0);
      this.label5.Name = "label5";
      this.label5.Size = new Size(89, 16);
      this.label5.TabIndex = 118;
      this.label5.Text = "domination0 : ";
      this.Time.Location = new Point(334, 78);
      this.Time.Margin = new Padding(4);
      this.Time.Name = "Time";
      this.Time.Size = new Size(65, 22);
      this.Time.TabIndex = 117;
      this.label44.AutoSize = true;
      this.label44.Location = new Point(285, 81);
      this.label44.Margin = new Padding(4, 0, 4, 0);
      this.label44.Name = "label44";
      this.label44.Size = new Size(47, 16);
      this.label44.TabIndex = 116;
      this.label44.Text = "Time : ";
      this.Party_member.Location = new Point(116, 124);
      this.Party_member.Margin = new Padding(4);
      this.Party_member.Name = "Party_member";
      this.Party_member.Size = new Size(65, 22);
      this.Party_member.TabIndex = 115;
      this.label35.AutoSize = true;
      this.label35.Location = new Point(8, (int) sbyte.MaxValue);
      this.label35.Margin = new Padding(4, 0, 4, 0);
      this.label35.Name = "label35";
      this.label35.Size = new Size(100, 16);
      this.label35.TabIndex = 114;
      this.label35.Text = "Party Member : ";
      this.CP.Location = new Point(202, 75);
      this.CP.Margin = new Padding(4);
      this.CP.Name = "CP";
      this.CP.Size = new Size(57, 22);
      this.CP.TabIndex = 113;
      this.label4.AutoSize = true;
      this.label4.Location = new Point(161, 78);
      this.label4.Margin = new Padding(4, 0, 4, 0);
      this.label4.Name = "label4";
      this.label4.Size = new Size(34, 16);
      this.label4.TabIndex = 112;
      this.label4.Text = "CP : ";
      this.Level.Enabled = false;
      this.Level.Location = new Point(68, 78);
      this.Level.Margin = new Padding(4);
      this.Level.Name = "Level";
      this.Level.Size = new Size(57, 22);
      this.Level.TabIndex = 110;
      this.Level.TextAlign = HorizontalAlignment.Center;
      this.label3.AutoSize = true;
      this.label3.Location = new Point(11, 81);
      this.label3.Margin = new Padding(4, 0, 4, 0);
      this.label3.Name = "label3";
      this.label3.Size = new Size(49, 16);
      this.label3.TabIndex = 111;
      this.label3.Text = "Level : ";
      this.Difficulty.Enabled = false;
      this.Difficulty.Location = new Point(336, 35);
      this.Difficulty.Margin = new Padding(4);
      this.Difficulty.Name = "Difficulty";
      this.Difficulty.Size = new Size(63, 22);
      this.Difficulty.TabIndex = 108;
      this.Difficulty.TextAlign = HorizontalAlignment.Center;
      this.label2.AutoSize = true;
      this.label2.Location = new Point(267, 38);
      this.label2.Margin = new Padding(4, 0, 4, 0);
      this.label2.Name = "label2";
      this.label2.Size = new Size(65, 16);
      this.label2.TabIndex = 109;
      this.label2.Text = "Difficulty : ";
      this.Zone_Id.Enabled = false;
      this.Zone_Id.Location = new Point(202, 33);
      this.Zone_Id.Margin = new Padding(4);
      this.Zone_Id.Name = "Zone_Id";
      this.Zone_Id.Size = new Size(57, 22);
      this.Zone_Id.TabIndex = 106;
      this.Zone_Id.TextAlign = HorizontalAlignment.Center;
      this.label1.AutoSize = true;
      this.label1.Location = new Point(134, 36);
      this.label1.Margin = new Padding(4, 0, 4, 0);
      this.label1.Name = "label1";
      this.label1.Size = new Size(61, 16);
      this.label1.TabIndex = 107;
      this.label1.Text = "Zone Id : ";
      this.index.Enabled = false;
      this.index.Location = new Point(67, 33);
      this.index.Margin = new Padding(4);
      this.index.Name = "index";
      this.index.Size = new Size(57, 22);
      this.index.TabIndex = 104;
      this.index.TextAlign = HorizontalAlignment.Center;
      this.label21.AutoSize = true;
      this.label21.Location = new Point(11, 36);
      this.label21.Margin = new Padding(4, 0, 4, 0);
      this.label21.Name = "label21";
      this.label21.Size = new Size(48, 16);
      this.label21.TabIndex = 105;
      this.label21.Text = "Index : ";
      this.groupBox2.Controls.Add((Control) this.dgItems);
      this.groupBox2.Location = new Point(16, 15);
      this.groupBox2.Margin = new Padding(4);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Padding = new Padding(4);
      this.groupBox2.Size = new Size(433, 298);
      this.groupBox2.TabIndex = 34;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "TOKEN ORDER";
      this.dgItems.AllowUserToAddRows = false;
      this.dgItems.AllowUserToDeleteRows = false;
      this.dgItems.AllowUserToResizeColumns = false;
      this.dgItems.AllowUserToResizeRows = false;
      this.dgItems.BackgroundColor = SystemColors.Control;
      this.dgItems.BorderStyle = BorderStyle.None;
      this.dgItems.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dgItems.Columns.AddRange((DataGridViewColumn) this.Zone, (DataGridViewColumn) this.ZoneId);
      this.dgItems.EnableHeadersVisualStyles = false;
      this.dgItems.Location = new Point(8, 23);
      this.dgItems.Margin = new Padding(4);
      this.dgItems.Name = "dgItems";
      this.dgItems.RowHeadersVisible = false;
      this.dgItems.RowHeadersWidth = 51;
      this.dgItems.RowTemplate.Height = 32;
      this.dgItems.ScrollBars = ScrollBars.Vertical;
      this.dgItems.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
      this.dgItems.Size = new Size(420, 257);
      this.dgItems.TabIndex = 1;
      this.dgItems.CellClick += new DataGridViewCellEventHandler(this.dgItems_CellClick);
      this.Zone.HeaderText = "None";
      this.Zone.MinimumWidth = 6;
      this.Zone.Name = "Zone";
      this.Zone.ReadOnly = true;
      this.Zone.Width = 200;
      this.ZoneId.HeaderText = "Zone Id";
      this.ZoneId.MinimumWidth = 6;
      this.ZoneId.Name = "ZoneId";
      this.ZoneId.ReadOnly = true;
      this.ZoneId.Width = 150;
      this.textBox4.Location = new Point(96, 673);
      this.textBox4.Margin = new Padding(4);
      this.textBox4.Name = "textBox4";
      this.textBox4.Size = new Size(32, 22);
      this.textBox4.TabIndex = 105;
      this.textBox4.Visible = false;
      this.textBox16.Enabled = false;
      this.textBox16.Location = new Point(809, 36);
      this.textBox16.Margin = new Padding(4);
      this.textBox16.Name = "textBox16";
      this.textBox16.Size = new Size(84, 22);
      this.textBox16.TabIndex = 51;
      this.textBox16.Visible = false;
      this.comboBox1.BackColor = Color.GreenYellow;
      this.comboBox1.FlatStyle = FlatStyle.Flat;
      this.comboBox1.FormattingEnabled = true;
      this.comboBox1.Items.AddRange(new object[3]
      {
        (object) "0 - Normal",
        (object) "1 - Hard",
        (object) "2 - Hell"
      });
      this.comboBox1.Location = new Point(637, 34);
      this.comboBox1.Margin = new Padding(4);
      this.comboBox1.Name = "comboBox1";
      this.comboBox1.Size = new Size(148, 24);
      this.comboBox1.TabIndex = 50;
      this.comboBox1.SelectedIndexChanged += new EventHandler(this.comboBox1_SelectedIndexChanged);
      this.label6.AutoSize = true;
      this.label6.Location = new Point(505, 38);
      this.label6.Margin = new Padding(4, 0, 4, 0);
      this.label6.Name = "label6";
      this.label6.Size = new Size(116, 16);
      this.label6.TabIndex = 49;
      this.label6.Text = "DIFFICULTY";
      this.textBox7.Enabled = false;
      this.textBox7.Location = new Point(148, 673);
      this.textBox7.Margin = new Padding(4);
      this.textBox7.Name = "textBox7";
      this.textBox7.Size = new Size(84, 22);
      this.textBox7.TabIndex = 106;
      this.textBox7.Visible = false;
      this.textBox8.Enabled = false;
      this.textBox8.Location = new Point(24, 673);
      this.textBox8.Margin = new Padding(4);
      this.textBox8.Name = "textBox8";
      this.textBox8.Size = new Size(64, 22);
      this.textBox8.TabIndex = 107;
      this.textBox8.Visible = false;
      this.groupBox4.BackColor = Color.Linen;
      this.groupBox4.Controls.Add((Control) this.a_need_item_count);
      this.groupBox4.Controls.Add((Control) this.label9);
      this.groupBox4.Controls.Add((Control) this.bt_needitem);
      this.groupBox4.Controls.Add((Control) this.need_item_name);
      this.groupBox4.Controls.Add((Control) this.a_need_item_idx);
      this.groupBox4.Controls.Add((Control) this.pictureBox2);
      this.groupBox4.Controls.Add((Control) this.label10);
      this.groupBox4.Controls.Add((Control) this.label11);
      this.groupBox4.Location = new Point(457, 77);
      this.groupBox4.Margin = new Padding(4);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Padding = new Padding(4);
      this.groupBox4.Size = new Size(457, 119);
      this.groupBox4.TabIndex = 108;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "Need Item";
      this.a_need_item_count.Location = new Point(290, 32);
      this.a_need_item_count.Margin = new Padding(4);
      this.a_need_item_count.Name = "a_need_item_count";
      this.a_need_item_count.Size = new Size(97, 22);
      this.a_need_item_count.TabIndex = 19;
      this.label9.AutoSize = true;
      this.label9.Location = new Point(242, 38);
      this.label9.Margin = new Padding(4, 0, 4, 0);
      this.label9.Name = "label9";
      this.label9.Size = new Size(39, 16);
      this.label9.TabIndex = 18;
      this.label9.Text = "Q'ty : ";
      this.need_item_name.Enabled = false;
      this.need_item_name.Location = new Point(148, 71);
      this.need_item_name.Margin = new Padding(4);
      this.need_item_name.Name = "need_item_name";
      this.need_item_name.Size = new Size(297, 22);
      this.need_item_name.TabIndex = 15;
      this.a_need_item_idx.Enabled = false;
      this.a_need_item_idx.Location = new Point(150, 34);
      this.a_need_item_idx.Margin = new Padding(4);
      this.a_need_item_idx.Name = "a_need_item_idx";
      this.a_need_item_idx.Size = new Size(85, 22);
      this.a_need_item_idx.TabIndex = 14;
      this.a_need_item_idx.TextChanged += new EventHandler(this.a_need_item_idx_TextChanged);
      this.label10.AutoSize = true;
      this.label10.Location = new Point(80, 75);
      this.label10.Margin = new Padding(4, 0, 4, 0);
      this.label10.Name = "label10";
      this.label10.Size = new Size(50, 16);
      this.label10.TabIndex = 17;
      this.label10.Text = "Name :";
      this.label11.AutoSize = true;
      this.label11.Location = new Point(80, 39);
      this.label11.Margin = new Padding(4, 0, 4, 0);
      this.label11.Name = "label11";
      this.label11.Size = new Size(29, 16);
      this.label11.TabIndex = 16;
      this.label11.Text = "ID : ";
      this.groupBox3.BackColor = Color.LightSteelBlue;
      this.groupBox3.Controls.Add((Control) this.bt_title);
      this.groupBox3.Controls.Add((Control) this.Title_name);
      this.groupBox3.Controls.Add((Control) this.Title_Id);
      this.groupBox3.Controls.Add((Control) this.pictureBox9);
      this.groupBox3.Controls.Add((Control) this.label36);
      this.groupBox3.Controls.Add((Control) this.label37);
      this.groupBox3.Location = new Point(922, 77);
      this.groupBox3.Margin = new Padding(4);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Padding = new Padding(4);
      this.groupBox3.Size = new Size(457, 119);
      this.groupBox3.TabIndex = 109;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "Title Item";
      this.Title_name.Enabled = false;
      this.Title_name.Location = new Point(148, 71);
      this.Title_name.Margin = new Padding(4);
      this.Title_name.Name = "Title_name";
      this.Title_name.Size = new Size(297, 22);
      this.Title_name.TabIndex = 15;
      this.Title_Id.Enabled = false;
      this.Title_Id.Location = new Point(150, 34);
      this.Title_Id.Margin = new Padding(4);
      this.Title_Id.Name = "Title_Id";
      this.Title_Id.Size = new Size(85, 22);
      this.Title_Id.TabIndex = 14;
      this.Title_Id.TextChanged += new EventHandler(this.Title_Id_TextChanged);
      this.label36.AutoSize = true;
      this.label36.Location = new Point(80, 75);
      this.label36.Margin = new Padding(4, 0, 4, 0);
      this.label36.Name = "label36";
      this.label36.Size = new Size(50, 16);
      this.label36.TabIndex = 17;
      this.label36.Text = "Name :";
      this.label37.AutoSize = true;
      this.label37.Location = new Point(80, 39);
      this.label37.Margin = new Padding(4, 0, 4, 0);
      this.label37.Name = "label37";
      this.label37.Size = new Size(29, 16);
      this.label37.TabIndex = 16;
      this.label37.Text = "ID : ";
      this.groupBox5.BackColor = Color.LightYellow;
      this.groupBox5.Controls.Add((Control) this.Box_Count);
      this.groupBox5.Controls.Add((Control) this.label38);
      this.groupBox5.Controls.Add((Control) this.bt_box);
      this.groupBox5.Controls.Add((Control) this.Box_name);
      this.groupBox5.Controls.Add((Control) this.Box_Id);
      this.groupBox5.Controls.Add((Control) this.pictureBox10);
      this.groupBox5.Controls.Add((Control) this.label39);
      this.groupBox5.Controls.Add((Control) this.label40);
      this.groupBox5.Location = new Point(922, 204);
      this.groupBox5.Margin = new Padding(4);
      this.groupBox5.Name = "groupBox5";
      this.groupBox5.Padding = new Padding(4);
      this.groupBox5.Size = new Size(457, 119);
      this.groupBox5.TabIndex = 110;
      this.groupBox5.TabStop = false;
      this.groupBox5.Text = "Box Item";
      this.Box_Count.Location = new Point(290, 32);
      this.Box_Count.Margin = new Padding(4);
      this.Box_Count.Name = "Box_Count";
      this.Box_Count.Size = new Size(97, 22);
      this.Box_Count.TabIndex = 19;
      this.label38.AutoSize = true;
      this.label38.Location = new Point(242, 38);
      this.label38.Margin = new Padding(4, 0, 4, 0);
      this.label38.Name = "label38";
      this.label38.Size = new Size(39, 16);
      this.label38.TabIndex = 18;
      this.label38.Text = "Q'ty : ";
      this.Box_name.Enabled = false;
      this.Box_name.Location = new Point(148, 71);
      this.Box_name.Margin = new Padding(4);
      this.Box_name.Name = "Box_name";
      this.Box_name.Size = new Size(297, 22);
      this.Box_name.TabIndex = 15;
      this.Box_Id.Enabled = false;
      this.Box_Id.Location = new Point(150, 34);
      this.Box_Id.Margin = new Padding(4);
      this.Box_Id.Name = "Box_Id";
      this.Box_Id.Size = new Size(85, 22);
      this.Box_Id.TabIndex = 14;
      this.Box_Id.TextChanged += new EventHandler(this.Box_Id_TextChanged);
      this.label39.AutoSize = true;
      this.label39.Location = new Point(80, 75);
      this.label39.Margin = new Padding(4, 0, 4, 0);
      this.label39.Name = "label39";
      this.label39.Size = new Size(50, 16);
      this.label39.TabIndex = 17;
      this.label39.Text = "Name :";
      this.label40.AutoSize = true;
      this.label40.Location = new Point(80, 39);
      this.label40.Margin = new Padding(4, 0, 4, 0);
      this.label40.Name = "label40";
      this.label40.Size = new Size(29, 16);
      this.label40.TabIndex = 16;
      this.label40.Text = "ID : ";
      this.groupBox6.BackColor = Color.Honeydew;
      this.groupBox6.Controls.Add((Control) this.checkBox5);
      this.groupBox6.Controls.Add((Control) this.checkBox4);
      this.groupBox6.Controls.Add((Control) this.checkBox3);
      this.groupBox6.Controls.Add((Control) this.checkBox2);
      this.groupBox6.Controls.Add((Control) this.checkBox1);
      this.groupBox6.Controls.Add((Control) this.r_t_id5_count);
      this.groupBox6.Controls.Add((Control) this.label18);
      this.groupBox6.Controls.Add((Control) this.bt_r_t_id5);
      this.groupBox6.Controls.Add((Control) this.r_t_id5_name);
      this.groupBox6.Controls.Add((Control) this.r_t_id5);
      this.groupBox6.Controls.Add((Control) this.pictureBox7);
      this.groupBox6.Controls.Add((Control) this.r_t_id4_count);
      this.groupBox6.Controls.Add((Control) this.label15);
      this.groupBox6.Controls.Add((Control) this.bt_r_t_id4);
      this.groupBox6.Controls.Add((Control) this.r_t_id4_name);
      this.groupBox6.Controls.Add((Control) this.r_t_id4);
      this.groupBox6.Controls.Add((Control) this.pictureBox6);
      this.groupBox6.Controls.Add((Control) this.r_t_id3_count);
      this.groupBox6.Controls.Add((Control) this.label12);
      this.groupBox6.Controls.Add((Control) this.bt_r_t_id3);
      this.groupBox6.Controls.Add((Control) this.r_t_id3_name);
      this.groupBox6.Controls.Add((Control) this.r_t_id3);
      this.groupBox6.Controls.Add((Control) this.pictureBox5);
      this.groupBox6.Controls.Add((Control) this.r_t_id2_count);
      this.groupBox6.Controls.Add((Control) this.label13);
      this.groupBox6.Controls.Add((Control) this.bt_r_t_id2);
      this.groupBox6.Controls.Add((Control) this.r_t_id2_name);
      this.groupBox6.Controls.Add((Control) this.r_t_id2);
      this.groupBox6.Controls.Add((Control) this.pictureBox4);
      this.groupBox6.Controls.Add((Control) this.r_t_id1_count);
      this.groupBox6.Controls.Add((Control) this.label14);
      this.groupBox6.Controls.Add((Control) this.bt_r_t_id1);
      this.groupBox6.Controls.Add((Control) this.r_t_id1_name);
      this.groupBox6.Controls.Add((Control) this.r_t_id1);
      this.groupBox6.Controls.Add((Control) this.pictureBox3);
      this.groupBox6.Controls.Add((Control) this.label19);
      this.groupBox6.Controls.Add((Control) this.label20);
      this.groupBox6.Controls.Add((Control) this.label16);
      this.groupBox6.Controls.Add((Control) this.label17);
      this.groupBox6.Controls.Add((Control) this.label24);
      this.groupBox6.Controls.Add((Control) this.label25);
      this.groupBox6.Controls.Add((Control) this.label26);
      this.groupBox6.Controls.Add((Control) this.label27);
      this.groupBox6.Controls.Add((Control) this.label28);
      this.groupBox6.Controls.Add((Control) this.label29);
      this.groupBox6.Location = new Point(457, 204);
      this.groupBox6.Margin = new Padding(4);
      this.groupBox6.Name = "groupBox6";
      this.groupBox6.Padding = new Padding(4);
      this.groupBox6.Size = new Size(457, 478);
      this.groupBox6.TabIndex = 111;
      this.groupBox6.TabStop = false;
      this.groupBox6.Text = "Reward Items";
      this.checkBox5.AutoSize = true;
      this.checkBox5.Location = new Point(15, 381);
      this.checkBox5.Margin = new Padding(4);
      this.checkBox5.Name = "checkBox5";
      this.checkBox5.Size = new Size(138, 20);
      this.checkBox5.TabIndex = 69;
      this.checkBox5.Text = "Item Reward No. 5";
      this.checkBox5.UseVisualStyleBackColor = true;
      this.checkBox4.AutoSize = true;
      this.checkBox4.Location = new Point(15, 287);
      this.checkBox4.Margin = new Padding(4);
      this.checkBox4.Name = "checkBox4";
      this.checkBox4.Size = new Size(138, 20);
      this.checkBox4.TabIndex = 68;
      this.checkBox4.Text = "Item Reward No. 4";
      this.checkBox4.UseVisualStyleBackColor = true;
      this.checkBox3.AutoSize = true;
      this.checkBox3.Location = new Point(10, 194);
      this.checkBox3.Margin = new Padding(4);
      this.checkBox3.Name = "checkBox3";
      this.checkBox3.Size = new Size(138, 20);
      this.checkBox3.TabIndex = 67;
      this.checkBox3.Text = "Item Reward No. 3";
      this.checkBox3.UseVisualStyleBackColor = true;
      this.checkBox2.AutoSize = true;
      this.checkBox2.Location = new Point(9, 109);
      this.checkBox2.Margin = new Padding(4);
      this.checkBox2.Name = "checkBox2";
      this.checkBox2.Size = new Size(138, 20);
      this.checkBox2.TabIndex = 66;
      this.checkBox2.Text = "Item Reward No. 2";
      this.checkBox2.UseVisualStyleBackColor = true;
      this.checkBox1.AutoSize = true;
      this.checkBox1.Location = new Point(9, 22);
      this.checkBox1.Margin = new Padding(4);
      this.checkBox1.Name = "checkBox1";
      this.checkBox1.Size = new Size(138, 20);
      this.checkBox1.TabIndex = 65;
      this.checkBox1.Text = "Item Reward No. 1";
      this.checkBox1.UseVisualStyleBackColor = true;
      this.r_t_id5_count.Location = new Point(306, 401);
      this.r_t_id5_count.Margin = new Padding(4);
      this.r_t_id5_count.Name = "r_t_id5_count";
      this.r_t_id5_count.Size = new Size(87, 22);
      this.r_t_id5_count.TabIndex = 59;
      this.label18.AutoSize = true;
      this.label18.Location = new Point(249, 406);
      this.label18.Margin = new Padding(4, 0, 4, 0);
      this.label18.Name = "label18";
      this.label18.Size = new Size(39, 16);
      this.label18.TabIndex = 58;
      this.label18.Text = "Q'ty : ";
      this.r_t_id5_name.Enabled = false;
      this.r_t_id5_name.Location = new Point(154, 437);
      this.r_t_id5_name.Margin = new Padding(4);
      this.r_t_id5_name.Name = "r_t_id5_name";
      this.r_t_id5_name.Size = new Size(297, 22);
      this.r_t_id5_name.TabIndex = 55;
      this.r_t_id5.Enabled = false;
      this.r_t_id5.Location = new Point(154, 401);
      this.r_t_id5.Margin = new Padding(4);
      this.r_t_id5.Name = "r_t_id5";
      this.r_t_id5.Size = new Size(87, 22);
      this.r_t_id5.TabIndex = 54;
      this.r_t_id5.TextChanged += new EventHandler(this.r_t_id5_TextChanged);
      this.r_t_id4_count.Location = new Point(306, 308);
      this.r_t_id4_count.Margin = new Padding(4);
      this.r_t_id4_count.Name = "r_t_id4_count";
      this.r_t_id4_count.Size = new Size(87, 22);
      this.r_t_id4_count.TabIndex = 51;
      this.label15.AutoSize = true;
      this.label15.Location = new Point(248, 313);
      this.label15.Margin = new Padding(4, 0, 4, 0);
      this.label15.Name = "label15";
      this.label15.Size = new Size(39, 16);
      this.label15.TabIndex = 50;
      this.label15.Text = "Q'ty : ";
      this.r_t_id4_name.Enabled = false;
      this.r_t_id4_name.Location = new Point(154, 344);
      this.r_t_id4_name.Margin = new Padding(4);
      this.r_t_id4_name.Name = "r_t_id4_name";
      this.r_t_id4_name.Size = new Size(297, 22);
      this.r_t_id4_name.TabIndex = 47;
      this.r_t_id4.Enabled = false;
      this.r_t_id4.Location = new Point(154, 308);
      this.r_t_id4.Margin = new Padding(4);
      this.r_t_id4.Name = "r_t_id4";
      this.r_t_id4.Size = new Size(87, 22);
      this.r_t_id4.TabIndex = 46;
      this.r_t_id4.TextChanged += new EventHandler(this.r_t_id4_TextChanged);
      this.r_t_id3_count.Location = new Point(302, 215);
      this.r_t_id3_count.Margin = new Padding(4);
      this.r_t_id3_count.Name = "r_t_id3_count";
      this.r_t_id3_count.Size = new Size(87, 22);
      this.r_t_id3_count.TabIndex = 43;
      this.label12.AutoSize = true;
      this.label12.Location = new Point(245, 220);
      this.label12.Margin = new Padding(4, 0, 4, 0);
      this.label12.Name = "label12";
      this.label12.Size = new Size(39, 16);
      this.label12.TabIndex = 42;
      this.label12.Text = "Q'ty : ";
      this.r_t_id3_name.Enabled = false;
      this.r_t_id3_name.Location = new Point(150, 251);
      this.r_t_id3_name.Margin = new Padding(4);
      this.r_t_id3_name.Name = "r_t_id3_name";
      this.r_t_id3_name.Size = new Size(297, 22);
      this.r_t_id3_name.TabIndex = 39;
      this.r_t_id3.Enabled = false;
      this.r_t_id3.Location = new Point(150, 215);
      this.r_t_id3.Margin = new Padding(4);
      this.r_t_id3.Name = "r_t_id3";
      this.r_t_id3.Size = new Size(87, 22);
      this.r_t_id3.TabIndex = 38;
      this.r_t_id3.TextChanged += new EventHandler(this.r_t_id3_TextChanged);
      this.r_t_id2_count.Location = new Point(300, 130);
      this.r_t_id2_count.Margin = new Padding(4);
      this.r_t_id2_count.Name = "r_t_id2_count";
      this.r_t_id2_count.Size = new Size(87, 22);
      this.r_t_id2_count.TabIndex = 35;
      this.label13.AutoSize = true;
      this.label13.Location = new Point(242, 135);
      this.label13.Margin = new Padding(4, 0, 4, 0);
      this.label13.Name = "label13";
      this.label13.Size = new Size(39, 16);
      this.label13.TabIndex = 34;
      this.label13.Text = "Q'ty : ";
      this.r_t_id2_name.Enabled = false;
      this.r_t_id2_name.Location = new Point(148, 166);
      this.r_t_id2_name.Margin = new Padding(4);
      this.r_t_id2_name.Name = "r_t_id2_name";
      this.r_t_id2_name.Size = new Size(297, 22);
      this.r_t_id2_name.TabIndex = 31;
      this.r_t_id2.Enabled = false;
      this.r_t_id2.Location = new Point(148, 130);
      this.r_t_id2.Margin = new Padding(4);
      this.r_t_id2.Name = "r_t_id2";
      this.r_t_id2.Size = new Size(87, 22);
      this.r_t_id2.TabIndex = 30;
      this.r_t_id2.TextChanged += new EventHandler(this.r_t_id2_TextChanged);
      this.r_t_id1_count.Location = new Point(300, 43);
      this.r_t_id1_count.Margin = new Padding(4);
      this.r_t_id1_count.Name = "r_t_id1_count";
      this.r_t_id1_count.Size = new Size(87, 22);
      this.r_t_id1_count.TabIndex = 27;
      this.label14.AutoSize = true;
      this.label14.Location = new Point(243, 48);
      this.label14.Margin = new Padding(4, 0, 4, 0);
      this.label14.Name = "label14";
      this.label14.Size = new Size(39, 16);
      this.label14.TabIndex = 26;
      this.label14.Text = "Q'ty : ";
      this.r_t_id1_name.Enabled = false;
      this.r_t_id1_name.Location = new Point(148, 79);
      this.r_t_id1_name.Margin = new Padding(4);
      this.r_t_id1_name.Name = "r_t_id1_name";
      this.r_t_id1_name.Size = new Size(297, 22);
      this.r_t_id1_name.TabIndex = 23;
      this.r_t_id1.Enabled = false;
      this.r_t_id1.Location = new Point(148, 43);
      this.r_t_id1.Margin = new Padding(4);
      this.r_t_id1.Name = "r_t_id1";
      this.r_t_id1.Size = new Size(87, 22);
      this.r_t_id1.TabIndex = 22;
      this.r_t_id1.TextChanged += new EventHandler(this.r_t_id1_TextChanged);
      this.label19.AutoSize = true;
      this.label19.Location = new Point(81, 442);
      this.label19.Margin = new Padding(4, 0, 4, 0);
      this.label19.Name = "label19";
      this.label19.Size = new Size(50, 16);
      this.label19.TabIndex = 57;
      this.label19.Text = "Name :";
      this.label20.AutoSize = true;
      this.label20.Location = new Point(81, 406);
      this.label20.Margin = new Padding(4, 0, 4, 0);
      this.label20.Name = "label20";
      this.label20.Size = new Size(29, 16);
      this.label20.TabIndex = 56;
      this.label20.Text = "ID : ";
      this.label16.AutoSize = true;
      this.label16.Location = new Point(80, 349);
      this.label16.Margin = new Padding(4, 0, 4, 0);
      this.label16.Name = "label16";
      this.label16.Size = new Size(50, 16);
      this.label16.TabIndex = 49;
      this.label16.Text = "Name :";
      this.label17.AutoSize = true;
      this.label17.Location = new Point(80, 313);
      this.label17.Margin = new Padding(4, 0, 4, 0);
      this.label17.Name = "label17";
      this.label17.Size = new Size(29, 16);
      this.label17.TabIndex = 48;
      this.label17.Text = "ID : ";
      this.label24.AutoSize = true;
      this.label24.Location = new Point(77, 256);
      this.label24.Margin = new Padding(4, 0, 4, 0);
      this.label24.Name = "label24";
      this.label24.Size = new Size(50, 16);
      this.label24.TabIndex = 41;
      this.label24.Text = "Name :";
      this.label25.AutoSize = true;
      this.label25.Location = new Point(77, 220);
      this.label25.Margin = new Padding(4, 0, 4, 0);
      this.label25.Name = "label25";
      this.label25.Size = new Size(29, 16);
      this.label25.TabIndex = 40;
      this.label25.Text = "ID : ";
      this.label26.AutoSize = true;
      this.label26.Location = new Point(74, 171);
      this.label26.Margin = new Padding(4, 0, 4, 0);
      this.label26.Name = "label26";
      this.label26.Size = new Size(50, 16);
      this.label26.TabIndex = 33;
      this.label26.Text = "Name :";
      this.label27.AutoSize = true;
      this.label27.Location = new Point(74, 135);
      this.label27.Margin = new Padding(4, 0, 4, 0);
      this.label27.Name = "label27";
      this.label27.Size = new Size(29, 16);
      this.label27.TabIndex = 32;
      this.label27.Text = "ID : ";
      this.label28.AutoSize = true;
      this.label28.Location = new Point(75, 84);
      this.label28.Margin = new Padding(4, 0, 4, 0);
      this.label28.Name = "label28";
      this.label28.Size = new Size(50, 16);
      this.label28.TabIndex = 25;
      this.label28.Text = "Name :";
      this.label29.AutoSize = true;
      this.label29.Location = new Point(75, 48);
      this.label29.Margin = new Padding(4, 0, 4, 0);
      this.label29.Name = "label29";
      this.label29.Size = new Size(29, 16);
      this.label29.TabIndex = 24;
      this.label29.Text = "ID : ";
      this.Boss1_npc.BackColor = Color.Snow;
      this.Boss1_npc.Controls.Add((Control) this.label43);
      this.Boss1_npc.Controls.Add((Control) this.label42);
      this.Boss1_npc.Controls.Add((Control) this.label41);
      this.Boss1_npc.Controls.Add((Control) this.pictureBox8);
      this.Boss1_npc.Controls.Add((Control) this.pictureBox11);
      this.Boss1_npc.Controls.Add((Control) this.bt_boss3);
      this.Boss1_npc.Controls.Add((Control) this.Boss3_name);
      this.Boss1_npc.Controls.Add((Control) this.Boss_id3);
      this.Boss1_npc.Controls.Add((Control) this.label33);
      this.Boss1_npc.Controls.Add((Control) this.label34);
      this.Boss1_npc.Controls.Add((Control) this.bt_boss2);
      this.Boss1_npc.Controls.Add((Control) this.Boss2_name);
      this.Boss1_npc.Controls.Add((Control) this.Boss_id2);
      this.Boss1_npc.Controls.Add((Control) this.label22);
      this.Boss1_npc.Controls.Add((Control) this.label23);
      this.Boss1_npc.Controls.Add((Control) this.bt_boss1);
      this.Boss1_npc.Controls.Add((Control) this.Boss1_name);
      this.Boss1_npc.Controls.Add((Control) this.Boss_id1);
      this.Boss1_npc.Controls.Add((Control) this.pc_npc);
      this.Boss1_npc.Controls.Add((Control) this.label7);
      this.Boss1_npc.Controls.Add((Control) this.label8);
      this.Boss1_npc.Location = new Point(922, 353);
      this.Boss1_npc.Margin = new Padding(4);
      this.Boss1_npc.Name = "Boss1_npc";
      this.Boss1_npc.Padding = new Padding(4);
      this.Boss1_npc.Size = new Size(457, 328);
      this.Boss1_npc.TabIndex = 112;
      this.Boss1_npc.TabStop = false;
      this.Boss1_npc.Text = "BOSS Information";
      this.label43.AutoSize = true;
      this.label43.ForeColor = Color.Coral;
      this.label43.Location = new Point(18, 222);
      this.label43.Margin = new Padding(4, 0, 4, 0);
      this.label43.Name = "label43";
      this.label43.Size = new Size(75, 16);
      this.label43.TabIndex = 32;
      this.label43.Text = "BOSS No.3";
      this.label42.AutoSize = true;
      this.label42.ForeColor = Color.OrangeRed;
      this.label42.Location = new Point(18, 121);
      this.label42.Margin = new Padding(4, 0, 4, 0);
      this.label42.Name = "label42";
      this.label42.Size = new Size(75, 16);
      this.label42.TabIndex = 31;
      this.label42.Text = "BOSS No.2";
      this.label41.AutoSize = true;
      this.label41.ForeColor = Color.Red;
      this.label41.Location = new Point(18, 19);
      this.label41.Margin = new Padding(4, 0, 4, 0);
      this.label41.Name = "label41";
      this.label41.Size = new Size(75, 16);
      this.label41.TabIndex = 30;
      this.label41.Text = "BOSS No.1";
      this.Boss3_name.Enabled = false;
      this.Boss3_name.Location = new Point(138, 279);
      this.Boss3_name.Margin = new Padding(4);
      this.Boss3_name.Name = "Boss3_name";
      this.Boss3_name.Size = new Size(261, 22);
      this.Boss3_name.TabIndex = 24;
      this.Boss_id3.Enabled = false;
      this.Boss_id3.Location = new Point(138, 242);
      this.Boss_id3.Margin = new Padding(4);
      this.Boss_id3.Name = "Boss_id3";
      this.Boss_id3.Size = new Size(121, 22);
      this.Boss_id3.TabIndex = 23;
      this.Boss_id3.TextChanged += new EventHandler(this.Boss_id3_TextChanged);
      this.label33.AutoSize = true;
      this.label33.Location = new Point(78, 284);
      this.label33.Margin = new Padding(4, 0, 4, 0);
      this.label33.Name = "label33";
      this.label33.Size = new Size(50, 16);
      this.label33.TabIndex = 26;
      this.label33.Text = "Name :";
      this.label34.AutoSize = true;
      this.label34.Location = new Point(78, 247);
      this.label34.Margin = new Padding(4, 0, 4, 0);
      this.label34.Name = "label34";
      this.label34.Size = new Size(29, 16);
      this.label34.TabIndex = 25;
      this.label34.Text = "ID : ";
      this.Boss2_name.Enabled = false;
      this.Boss2_name.Location = new Point(140, 173);
      this.Boss2_name.Margin = new Padding(4);
      this.Boss2_name.Name = "Boss2_name";
      this.Boss2_name.Size = new Size(261, 22);
      this.Boss2_name.TabIndex = 18;
      this.Boss_id2.Enabled = false;
      this.Boss_id2.Location = new Point(140, 136);
      this.Boss_id2.Margin = new Padding(4);
      this.Boss_id2.Name = "Boss_id2";
      this.Boss_id2.Size = new Size(121, 22);
      this.Boss_id2.TabIndex = 17;
      this.Boss_id2.TextChanged += new EventHandler(this.Boss_id2_TextChanged);
      this.label22.AutoSize = true;
      this.label22.Location = new Point(80, 178);
      this.label22.Margin = new Padding(4, 0, 4, 0);
      this.label22.Name = "label22";
      this.label22.Size = new Size(50, 16);
      this.label22.TabIndex = 20;
      this.label22.Text = "Name :";
      this.label23.AutoSize = true;
      this.label23.Location = new Point(80, 141);
      this.label23.Margin = new Padding(4, 0, 4, 0);
      this.label23.Name = "label23";
      this.label23.Size = new Size(29, 16);
      this.label23.TabIndex = 19;
      this.label23.Text = "ID : ";
      this.Boss1_name.Enabled = false;
      this.Boss1_name.Location = new Point(140, 73);
      this.Boss1_name.Margin = new Padding(4);
      this.Boss1_name.Name = "Boss1_name";
      this.Boss1_name.Size = new Size(261, 22);
      this.Boss1_name.TabIndex = 12;
      this.Boss_id1.Enabled = false;
      this.Boss_id1.Location = new Point(140, 36);
      this.Boss_id1.Margin = new Padding(4);
      this.Boss_id1.Name = "Boss_id1";
      this.Boss_id1.Size = new Size(121, 22);
      this.Boss_id1.TabIndex = 11;
      this.Boss_id1.TextChanged += new EventHandler(this.Boss_id1_TextChanged);
      this.label7.AutoSize = true;
      this.label7.Location = new Point(80, 78);
      this.label7.Margin = new Padding(4, 0, 4, 0);
      this.label7.Name = "label7";
      this.label7.Size = new Size(50, 16);
      this.label7.TabIndex = 14;
      this.label7.Text = "Name :";
      this.label8.AutoSize = true;
      this.label8.Location = new Point(80, 41);
      this.label8.Margin = new Padding(4, 0, 4, 0);
      this.label8.Name = "label8";
      this.label8.Size = new Size(29, 16);
      this.label8.TabIndex = 13;
      this.label8.Text = "ID : ";
      this.pictureBox8.BackColor = Color.LightCyan;
      this.pictureBox8.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox8.Image = (Image) Resources.pc_npc_Image;
      this.pictureBox8.Location = new Point(15, 242);
      this.pictureBox8.Margin = new Padding(4);
      this.pictureBox8.Name = "pictureBox8";
      this.pictureBox8.Size = new Size(55, 49);
      this.pictureBox8.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pictureBox8.TabIndex = 29;
      this.pictureBox8.TabStop = false;
      this.pictureBox11.BackColor = Color.LightCyan;
      this.pictureBox11.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox11.Image = (Image) Resources.pc_npc_Image;
      this.pictureBox11.Location = new Point(15, 141);
      this.pictureBox11.Margin = new Padding(4);
      this.pictureBox11.Name = "pictureBox11";
      this.pictureBox11.Size = new Size(55, 49);
      this.pictureBox11.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pictureBox11.TabIndex = 28;
      this.pictureBox11.TabStop = false;
      this.bt_boss3.Image = (Image) Resources.search__5_;
      this.bt_boss3.Location = new Point(343, 237);
      this.bt_boss3.Margin = new Padding(4);
      this.bt_boss3.Name = "bt_boss3";
      this.bt_boss3.Size = new Size(40, 33);
      this.bt_boss3.TabIndex = 22;
      this.bt_boss3.UseVisualStyleBackColor = true;
      this.bt_boss3.Click += new EventHandler(this.bt_boss3_Click);
      this.bt_boss2.Image = (Image) Resources.search__5_;
      this.bt_boss2.Location = new Point(345, 131);
      this.bt_boss2.Margin = new Padding(4);
      this.bt_boss2.Name = "bt_boss2";
      this.bt_boss2.Size = new Size(40, 33);
      this.bt_boss2.TabIndex = 16;
      this.bt_boss2.UseVisualStyleBackColor = true;
      this.bt_boss2.Click += new EventHandler(this.bt_boss2_Click);
      this.bt_boss1.Image = (Image) Resources.search__5_;
      this.bt_boss1.Location = new Point(345, 31);
      this.bt_boss1.Margin = new Padding(4);
      this.bt_boss1.Name = "bt_boss1";
      this.bt_boss1.Size = new Size(40, 33);
      this.bt_boss1.TabIndex = 0;
      this.bt_boss1.UseVisualStyleBackColor = true;
      this.bt_boss1.Click += new EventHandler(this.bt_boss1_Click);
      this.pc_npc.BackColor = Color.LightCyan;
      this.pc_npc.BorderStyle = BorderStyle.FixedSingle;
      this.pc_npc.Image = (Image) Resources.pc_npc_Image;
      this.pc_npc.Location = new Point(15, 42);
      this.pc_npc.Margin = new Padding(4);
      this.pc_npc.Name = "pc_npc";
      this.pc_npc.Size = new Size(55, 49);
      this.pc_npc.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pc_npc.TabIndex = 9;
      this.pc_npc.TabStop = false;
      this.bt_r_t_id5.BackgroundImage = (Image) Resources.search__5_;
      this.bt_r_t_id5.BackgroundImageLayout = ImageLayout.None;
      this.bt_r_t_id5.Location = new Point(399, 398);
      this.bt_r_t_id5.Margin = new Padding(4);
      this.bt_r_t_id5.Name = "bt_r_t_id5";
      this.bt_r_t_id5.Size = new Size(36, 31);
      this.bt_r_t_id5.TabIndex = 53;
      this.bt_r_t_id5.UseVisualStyleBackColor = true;
      this.bt_r_t_id5.Click += new EventHandler(this.bt_r_t_id5_Click);
      this.pictureBox7.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox7.Location = new Point(15, 409);
      this.pictureBox7.Margin = new Padding(4);
      this.pictureBox7.Name = "pictureBox7";
      this.pictureBox7.Size = new Size(55, 49);
      this.pictureBox7.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pictureBox7.TabIndex = 52;
      this.pictureBox7.TabStop = false;
      this.bt_r_t_id4.BackgroundImage = (Image) Resources.search__5_;
      this.bt_r_t_id4.BackgroundImageLayout = ImageLayout.None;
      this.bt_r_t_id4.Location = new Point(399, 299);
      this.bt_r_t_id4.Margin = new Padding(4);
      this.bt_r_t_id4.Name = "bt_r_t_id4";
      this.bt_r_t_id4.Size = new Size(36, 31);
      this.bt_r_t_id4.TabIndex = 45;
      this.bt_r_t_id4.UseVisualStyleBackColor = true;
      this.bt_r_t_id4.Click += new EventHandler(this.bt_r_t_id4_Click);
      this.pictureBox6.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox6.Location = new Point(15, 315);
      this.pictureBox6.Margin = new Padding(4);
      this.pictureBox6.Name = "pictureBox6";
      this.pictureBox6.Size = new Size(55, 49);
      this.pictureBox6.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pictureBox6.TabIndex = 44;
      this.pictureBox6.TabStop = false;
      this.bt_r_t_id3.BackgroundImage = (Image) Resources.search__5_;
      this.bt_r_t_id3.BackgroundImageLayout = ImageLayout.None;
      this.bt_r_t_id3.Location = new Point(395, 211);
      this.bt_r_t_id3.Margin = new Padding(4);
      this.bt_r_t_id3.Name = "bt_r_t_id3";
      this.bt_r_t_id3.Size = new Size(36, 31);
      this.bt_r_t_id3.TabIndex = 37;
      this.bt_r_t_id3.UseVisualStyleBackColor = true;
      this.bt_r_t_id3.Click += new EventHandler(this.bt_r_t_id3_Click);
      this.pictureBox5.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox5.Location = new Point(11, 222);
      this.pictureBox5.Margin = new Padding(4);
      this.pictureBox5.Name = "pictureBox5";
      this.pictureBox5.Size = new Size(55, 49);
      this.pictureBox5.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pictureBox5.TabIndex = 36;
      this.pictureBox5.TabStop = false;
      this.bt_r_t_id2.BackgroundImage = (Image) Resources.search__5_;
      this.bt_r_t_id2.BackgroundImageLayout = ImageLayout.None;
      this.bt_r_t_id2.Location = new Point(393, 128);
      this.bt_r_t_id2.Margin = new Padding(4);
      this.bt_r_t_id2.Name = "bt_r_t_id2";
      this.bt_r_t_id2.Size = new Size(36, 31);
      this.bt_r_t_id2.TabIndex = 29;
      this.bt_r_t_id2.UseVisualStyleBackColor = true;
      this.bt_r_t_id2.Click += new EventHandler(this.bt_r_t_id2_Click);
      this.pictureBox4.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox4.Location = new Point(9, 137);
      this.pictureBox4.Margin = new Padding(4);
      this.pictureBox4.Name = "pictureBox4";
      this.pictureBox4.Size = new Size(55, 49);
      this.pictureBox4.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pictureBox4.TabIndex = 28;
      this.pictureBox4.TabStop = false;
      this.bt_r_t_id1.BackgroundImage = (Image) Resources.search__5_;
      this.bt_r_t_id1.BackgroundImageLayout = ImageLayout.None;
      this.bt_r_t_id1.Location = new Point(393, 41);
      this.bt_r_t_id1.Margin = new Padding(4);
      this.bt_r_t_id1.Name = "bt_r_t_id1";
      this.bt_r_t_id1.Size = new Size(36, 31);
      this.bt_r_t_id1.TabIndex = 21;
      this.bt_r_t_id1.UseVisualStyleBackColor = true;
      this.bt_r_t_id1.Click += new EventHandler(this.bt_r_t_id1_Click);
      this.pictureBox3.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox3.Location = new Point(9, 50);
      this.pictureBox3.Margin = new Padding(4);
      this.pictureBox3.Name = "pictureBox3";
      this.pictureBox3.Size = new Size(55, 49);
      this.pictureBox3.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pictureBox3.TabIndex = 20;
      this.pictureBox3.TabStop = false;
      this.bt_box.Image = (Image) Resources.search__5_;
      this.bt_box.Location = new Point(405, 27);
      this.bt_box.Margin = new Padding(4);
      this.bt_box.Name = "bt_box";
      this.bt_box.Size = new Size(40, 33);
      this.bt_box.TabIndex = 13;
      this.bt_box.UseVisualStyleBackColor = true;
      this.bt_box.Click += new EventHandler(this.bt_box_Click);
      this.pictureBox10.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox10.Location = new Point(15, 42);
      this.pictureBox10.Margin = new Padding(4);
      this.pictureBox10.Name = "pictureBox10";
      this.pictureBox10.Size = new Size(55, 49);
      this.pictureBox10.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pictureBox10.TabIndex = 10;
      this.pictureBox10.TabStop = false;
      this.bt_title.Image = (Image) Resources.search__5_;
      this.bt_title.Location = new Point(405, 27);
      this.bt_title.Margin = new Padding(4);
      this.bt_title.Name = "bt_title";
      this.bt_title.Size = new Size(40, 33);
      this.bt_title.TabIndex = 13;
      this.bt_title.UseVisualStyleBackColor = true;
      this.bt_title.Click += new EventHandler(this.bt_title_Click);
      this.pictureBox9.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox9.Location = new Point(15, 42);
      this.pictureBox9.Margin = new Padding(4);
      this.pictureBox9.Name = "pictureBox9";
      this.pictureBox9.Size = new Size(55, 49);
      this.pictureBox9.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pictureBox9.TabIndex = 10;
      this.pictureBox9.TabStop = false;
      this.bt_needitem.Image = (Image) Resources.search__5_;
      this.bt_needitem.Location = new Point(405, 27);
      this.bt_needitem.Margin = new Padding(4);
      this.bt_needitem.Name = "bt_needitem";
      this.bt_needitem.Size = new Size(40, 33);
      this.bt_needitem.TabIndex = 13;
      this.bt_needitem.UseVisualStyleBackColor = true;
      this.bt_needitem.Click += new EventHandler(this.bt_needitem_Click);
      this.pictureBox2.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox2.Location = new Point(15, 42);
      this.pictureBox2.Margin = new Padding(4);
      this.pictureBox2.Name = "pictureBox2";
      this.pictureBox2.Size = new Size(55, 49);
      this.pictureBox2.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pictureBox2.TabIndex = 10;
      this.pictureBox2.TabStop = false;
      this.button18.BackColor = Color.LightCyan;
      this.button18.FlatStyle = FlatStyle.Flat;
      this.button18.Image = (Image) Resources._08;
      this.button18.ImageAlign = ContentAlignment.MiddleLeft;
      this.button18.Location = new Point(8, 276);
      this.button18.Margin = new Padding(4);
      this.button18.Name = "button18";
      this.button18.Size = new Size(417, 47);
      this.button18.TabIndex = 103;
      this.button18.Text = "      Update";
      this.button18.UseVisualStyleBackColor = false;
      this.button18.Click += new EventHandler(this.button18_Click);
      this.AutoScaleDimensions = new SizeF(8f, 16f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(1390, 697);
      this.Controls.Add((Control) this.Boss1_npc);
      this.Controls.Add((Control) this.groupBox6);
      this.Controls.Add((Control) this.groupBox5);
      this.Controls.Add((Control) this.groupBox3);
      this.Controls.Add((Control) this.groupBox4);
      this.Controls.Add((Control) this.textBox8);
      this.Controls.Add((Control) this.textBox7);
      this.Controls.Add((Control) this.textBox4);
      this.Controls.Add((Control) this.textBox16);
      this.Controls.Add((Control) this.comboBox1);
      this.Controls.Add((Control) this.label6);
      this.Controls.Add((Control) this.groupBox2);
      this.Controls.Add((Control) this.groupBox1);
      this.FormBorderStyle = FormBorderStyle.Fixed3D;
      this.Margin = new Padding(4);
      this.MaximizeBox = false;
      this.Name = nameof (PartyDungeon);
      this.Text = "LastChaos Party Dungeon Editor";
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.groupBox2.ResumeLayout(false);
      ((ISupportInitialize) this.dgItems).EndInit();
      this.groupBox4.ResumeLayout(false);
      this.groupBox4.PerformLayout();
      this.groupBox3.ResumeLayout(false);
      this.groupBox3.PerformLayout();
      this.groupBox5.ResumeLayout(false);
      this.groupBox5.PerformLayout();
      this.groupBox6.ResumeLayout(false);
      this.groupBox6.PerformLayout();
      this.Boss1_npc.ResumeLayout(false);
      this.Boss1_npc.PerformLayout();
      ((ISupportInitialize) this.pictureBox8).EndInit();
      ((ISupportInitialize) this.pictureBox11).EndInit();
      ((ISupportInitialize) this.pc_npc).EndInit();
      ((ISupportInitialize) this.pictureBox7).EndInit();
      ((ISupportInitialize) this.pictureBox6).EndInit();
      ((ISupportInitialize) this.pictureBox5).EndInit();
      ((ISupportInitialize) this.pictureBox4).EndInit();
      ((ISupportInitialize) this.pictureBox3).EndInit();
      ((ISupportInitialize) this.pictureBox10).EndInit();
      ((ISupportInitialize) this.pictureBox9).EndInit();
      ((ISupportInitialize) this.pictureBox2).EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();
      textBoxLevel = new TextBox { Location = new Point(900, 35), Size = new Size(80, 22), Enabled = false };
      textBoxDifficulty = new TextBox { Location = new Point(990, 35), Size = new Size(80, 22), Enabled = false };
      textBoxTime = new TextBox { Location = new Point(1080, 35), Size = new Size(80, 22), Enabled = false };

      Controls.Add(textBoxLevel);
      Controls.Add(textBoxDifficulty);
      Controls.Add(textBoxTime);
        }

    private void bt_needitem_Click(object sender, EventArgs e)
    {
      this.a_need_item_idx.Text = "0";
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.a_need_item_idx.Text = itemPicker.ItemIndex.ToString();
    }

    private void bt_title_Click(object sender, EventArgs e)
    {
      this.Title_Id.Text = "0";
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.Title_Id.Text = itemPicker.ItemIndex.ToString();
    }

    private void bt_box_Click(object sender, EventArgs e)
    {
      this.Box_Id.Text = "0";
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.Box_Id.Text = itemPicker.ItemIndex.ToString();
    }

    private void bt_r_t_id1_Click(object sender, EventArgs e)
    {
      this.r_t_id1.Text = "0";
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.r_t_id1.Text = itemPicker.ItemIndex.ToString();
    }

    private void bt_r_t_id2_Click(object sender, EventArgs e)
    {
      this.r_t_id2.Text = "0";
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.r_t_id2.Text = itemPicker.ItemIndex.ToString();
    }

    private void bt_r_t_id3_Click(object sender, EventArgs e)
    {
      this.r_t_id3.Text = "0";
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.r_t_id3.Text = itemPicker.ItemIndex.ToString();
    }

    private void bt_r_t_id4_Click(object sender, EventArgs e)
    {
      this.r_t_id4.Text = "0";
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.r_t_id4.Text = itemPicker.ItemIndex.ToString();
    }

    private void bt_r_t_id5_Click(object sender, EventArgs e)
    {
      this.r_t_id5.Text = "0";
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.r_t_id5.Text = itemPicker.ItemIndex.ToString();
    }

    private void bt_boss1_Click(object sender, EventArgs e)
    {
      this.Boss_id1.Text = "0";
      MobPicker mobPicker = new MobPicker();
      if (mobPicker.ShowDialog() != DialogResult.OK)
        return;
      this.Boss_id1.Text = mobPicker.MobIndex.ToString();
    }

    private void bt_boss2_Click(object sender, EventArgs e)
    {
      this.Boss_id2.Text = "0";
      MobPicker mobPicker = new MobPicker();
      if (mobPicker.ShowDialog() != DialogResult.OK)
        return;
      this.Boss_id2.Text = mobPicker.MobIndex.ToString();
    }

    private void bt_boss3_Click(object sender, EventArgs e)
    {
      this.Boss_id3.Text = "0";
      MobPicker mobPicker = new MobPicker();
      if (mobPicker.ShowDialog() != DialogResult.OK)
        return;
      this.Boss_id3.Text = mobPicker.MobIndex.ToString();
    }

    private void button18_Click(object sender, EventArgs e)
    {
      if (this.Difficulty.Text.Trim().Length <= 0)
      {
        int num1 = (int) MessageBox.Show("Please Select Zone", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_cloud_partyexpedition_config SET a_level  = '" + this.Level.Text + "', a_cp  = '" + this.CP.Text + "', a_need_item_idx  = '" + this.a_need_item_idx.Text + "', a_need_item_count  = '" + this.a_need_item_count.Text + "', a_member_need  = '" + this.Party_member.Text + "', a_time  = '" + this.Time.Text + "', a_reward_item_idx  = '" + this.r_t_id1.Text + "', a_reward_item_count  = '" + this.r_t_id1_count.Text + "', a_reward_item_idx1  = '" + this.r_t_id2.Text + "', a_reward_item_count1  = '" + this.r_t_id2_count.Text + "', a_reward_item_idx2  = '" + this.r_t_id3.Text + "', a_reward_item_count2  = '" + this.r_t_id3_count.Text + "', a_reward_item_idx3  = '" + this.r_t_id4.Text + "', a_reward_item_count3  = '" + this.r_t_id4_count.Text + "', a_reward_item_idx4  = '" + this.r_t_id5.Text + "', a_reward_item_count4  = '" + this.r_t_id4_count.Text + "' WHERE a_zonetid = '" + this.Zone_Id.Text + "' AND a_difficulty = '" + this.textBox16.Text + "'");
        int num2 = (int) MessageBox.Show("Update", "Completed", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
        this.LoadDifficult();
      }
    }

        private void ClearDifficultyFields()
        {
            Difficulty.Clear();
            Level.Clear();
            CP.Clear();
            a_need_item_idx.Clear();
            a_need_item_count.Clear();
            Party_member.Clear();
            Time.Clear();

            r_t_id1.Clear(); r_t_id1_count.Clear();
            r_t_id2.Clear(); r_t_id2_count.Clear();
            r_t_id3.Clear(); r_t_id3_count.Clear();
            r_t_id4.Clear(); r_t_id4_count.Clear();
            r_t_id5.Clear(); r_t_id5_count.Clear();

            Title_Id.Clear();
            Box_Id.Clear();
            Box_Count.Clear();
            Boss_id1.Clear();
            Boss_id2.Clear();
            Boss_id3.Clear();
            Domination0.Clear();
            Domination1.Clear();
            DominationPoint.Clear();
            Type.Clear();
            Info.Clear();
        }

    }
}
