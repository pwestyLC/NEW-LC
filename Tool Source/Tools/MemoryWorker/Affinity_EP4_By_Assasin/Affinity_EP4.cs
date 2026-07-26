// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.Affinity_EP4_By_Assasin.Affinity_EP4
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using LcDevPack_TeamDamonA.Properties;
using LcDevPack_TeamDamonA.Tools.MemoryWorker.AssasinPL_Read_Need_Lod;
using MySqlConnector;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.Affinity_EP4_By_Assasin
{
  public class Affinity_EP4 : Form
  {
    public static Connection connection = new Connection();
    public static string Host = Affinity_EP4.connection.Settings.SqlHost;
    public static string User = Affinity_EP4.connection.Settings.SqlUser;
    public static string Password = Affinity_EP4.connection.Settings.SqlPassword;
    public static string Database = Affinity_EP4.connection.Settings.SqlDatabase;
    public string _ClientPath = LcDevPack_TeamDamonA.Tools.MobEditor.connection.Settings.ClientPath;
    public static string language = LcDevPack_TeamDamonA.Tools.Settings.connection.Settings.Language;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    public static List<tAffinity> AffinityList = new List<tAffinity>();
    public static string ISO = "ISO-8859-1";
    public static string OpenedFile = "";
    public static string OpenedFileString = "";
    public static bool changetIcon = false;
    private string bgwCon = "";
    public static int newTexID;
    public static int newTexcol;
    public static int newTexrow;
    public static string Read_Name_DB = IconList.namee;
    public static string Str_Lang = Affinity_EP4.ChangeLang();
    public static string ConnectionString;
    private IContainer components = (IContainer) null;
    private ToolStrip toolStrip1;
    private ToolStripButton Open;
    private ToolStripButton Save;
    private ToolStripButton Saveas;
    private ListBox lbAffinity;
    private GroupBox groupBox2;
    private Button button_itemsearch;
    private Button button7;
    private TextBox textBox_needItemName;
    private NumericUpDown numericUpDown_needaffinitypoints;
    private PictureBox pictureBox_needaffinity;
    private NumericUpDown numericUpDown_needaffinityid;
    private TextBox textBox_needaffinityName;
    private Label label7;
    private Label label6;
    private PictureBox pictureBox_needItemID;
    private NumericUpDown numericUpDown_needLevel;
    private NumericUpDown numericUpDown_needitemcount;
    private NumericUpDown numericUpDown_needitemID;
    private Label label3;
    private Label label5;
    private Label label4;
    private GroupBox groupBox1;
    private Button button_iconsearch;
    private PictureBox pictureBox_Affinity;
    private NumericUpDown numericUpDown_ID;
    private Label label2;
    private TextBox textBox_name;
    private Label label1;
    private GroupBox groupBox8;
    private TextBox textBox22;
    private Label label13;
    private Button button2;
    private Button button1;
    private Button button3;
    private GroupBox groupBox7;
    private DataGridView dataGridView_getAff_Quest;
    private DataGridViewTextBoxColumn dataGridViewTextBoxColumn7;
    private DataGridViewTextBoxColumn dataGridViewTextBoxColumn8;
    private DataGridViewTextBoxColumn dataGridViewTextBoxColumn9;
    private Button button5;
    private Button button6;
    private GroupBox groupBox6;
    private DataGridView dataGridView_GetAff_Monster;
    private DataGridViewTextBoxColumn dataGridViewTextBoxColumn4;
    private DataGridViewTextBoxColumn dataGridViewTextBoxColumn5;
    private DataGridViewTextBoxColumn dataGridViewTextBoxColumn6;
    private Button button4;
    private Button button8;
    private GroupBox groupBox5;
    private DataGridView dataGridView_GetAff_Item;
    private DataGridViewImageColumn dataGridViewImageColumn1;
    private DataGridViewTextBoxColumn dataGridViewTextBoxColumn1;
    private DataGridViewTextBoxColumn dataGridViewTextBoxColumn2;
    private DataGridViewTextBoxColumn dataGridViewTextBoxColumn3;
    private Button button9;
    private Button b_affitem;
    private GroupBox groupBox4;
    private DataGridView dataGridView_affinity_rewardItem;
    private DataGridViewImageColumn image;
    private DataGridViewTextBoxColumn Column1;
    private DataGridViewTextBoxColumn Column2;
    private DataGridViewTextBoxColumn Column3;
    private Button button_removeaffinityitemReward;
    private Button button_addaffinityitemReward;
    private GroupBox groupBox3;
    private Button button_removenpc;
    private DataGridView dataGridView_npc;
    private Button button_addnpc;
    private DataGridViewTextBoxColumn Npcid;
    private DataGridViewTextBoxColumn npcname;
    private DataGridViewTextBoxColumn Flag;
    private DataGridViewTextBoxColumn Stringid;
    private DataGridViewTextBoxColumn Column6;
    private DataGridViewTextBoxColumn Column4;
    private DataGridViewTextBoxColumn Column5;
    private ToolStripSplitButton toolStripSplitButton1;
    private ToolStripMenuItem getAllFromDBToolStripMenuItem;
    private ToolStripMenuItem saveAllToDBToolStripMenuItem;
    private Button button10;
    private Button button11;
    private Button button12;

    public Affinity_EP4() => this.InitializeComponent();

    public static bool SetConnection()
    {
      Affinity_EP4.ConnectionString = string.Format("Data Source={0};Database={1};User ID={2};Password={3};SslMode=Preferred;TlsVersion=Tls12;", (object) Affinity_EP4.Host, (object) Affinity_EP4.Database, (object) Affinity_EP4.User, (object) Affinity_EP4.Password);
      return true;
    }

    public static string ChangeLang()
    {
      switch (Affinity_EP4.language)
      {
        case "GER":
          Affinity_EP4.Str_Lang = "ger";
          return Affinity_EP4.Str_Lang;
        case "POL":
          Affinity_EP4.Str_Lang = "pld";
          return Affinity_EP4.Str_Lang;
        case "BRA":
          Affinity_EP4.Str_Lang = "brz";
          return Affinity_EP4.Str_Lang;
        case "RUS":
          Affinity_EP4.Str_Lang = "rus";
          return Affinity_EP4.Str_Lang;
        case "FRA":
          Affinity_EP4.Str_Lang = "frc";
          return Affinity_EP4.Str_Lang;
        case "ESP":
          Affinity_EP4.Str_Lang = "spn";
          return Affinity_EP4.Str_Lang;
        case "MEX":
          Affinity_EP4.Str_Lang = "mex";
          return Affinity_EP4.Str_Lang;
        case "THA":
          Affinity_EP4.Str_Lang = "th";
          return Affinity_EP4.Str_Lang;
        case "ITA":
          Affinity_EP4.Str_Lang = "ita";
          return Affinity_EP4.Str_Lang;
        case "USA":
          Affinity_EP4.Str_Lang = "us";
          return Affinity_EP4.Str_Lang;
        default:
          return (string) null;
      }
    }

    public static Bitmap AffinityIcons(int texID, int texRow, int texCol)
    {
      Image image = Image.FromFile("icons/SkillBtn" + texID.ToString() + ".png");
      Bitmap bitmap = new Bitmap(32, 32);
      Graphics graphics = Graphics.FromImage((Image) bitmap);
      int y = texRow * 32;
      Rectangle srcRect = new Rectangle(texCol * 32, y, 32, 32);
      graphics.DrawImage(image, 0, 0, srcRect, GraphicsUnit.Pixel);
      graphics.Dispose();
      return bitmap;
    }

    private void LoadListBox()
    {
      MySqlConnection connection = new MySqlConnection("datasource=" + Affinity_EP4.Host + ";port=3306;username=" + Affinity_EP4.User + ";password=" + Affinity_EP4.Password + ";database=" + Affinity_EP4.Database);
      connection.Open();
      MySqlCommand mySqlCommand = new MySqlCommand("SELECT * FROM t_affinity WHERE a_enable=1 ORDER BY a_index ASC;", connection);
      mySqlCommand.ExecuteNonQuery();
      MySqlDataReader mySqlDataReader = mySqlCommand.ExecuteReader();
      while (mySqlDataReader.Read())
      {
        tAffinity tAffinity = new tAffinity()
        {
          a_index = Convert.ToInt32(mySqlDataReader["a_index"]),
          a_texture_id = Convert.ToInt32(mySqlDataReader["a_texture_id"]),
          a_texture_row = Convert.ToInt32(mySqlDataReader["a_texture_row"]),
          a_texture_col = Convert.ToInt32(mySqlDataReader["a_texture_col"]),
          a_needitemidx = Convert.ToInt32(mySqlDataReader["a_needitemidx"]),
          a_needitemcount = Convert.ToInt32(mySqlDataReader["a_needitemcount"]),
          a_needlevel = Convert.ToInt32(mySqlDataReader["a_needlevel"]),
          a_affinity_idx = Convert.ToInt32(mySqlDataReader["a_affinity_idx"]),
          a_affinity_value = Convert.ToInt32(mySqlDataReader["a_affinity_value"]),
          a_name_usa = mySqlDataReader[Affinity_EP4.Read_Name_DB ?? ""].ToString(),
          a_maxvalue = Convert.ToInt32(mySqlDataReader["a_maxvalue"])
        };
        tAffinity.Npcs = Affinity_EP4.GetNpcs(tAffinity.a_index);
        tAffinity.NpcCount = tAffinity.Npcs.Count<tAffinityNpc>();
        tAffinity.Work = Affinity_EP4.GetWork(tAffinity.a_index);
        tAffinity.WorkItemCount = tAffinity.Work.Count<tAffinityWork>();
        tAffinity.Items = new List<tAffinityRewardItem>();
        for (int index = 0; index < tAffinity.NpcCount; ++index)
          tAffinity.Items.AddRange((IEnumerable<tAffinityRewardItem>) Affinity_EP4.GetRewardItems(tAffinity.Npcs[index].a_npcidx));
        tAffinity.ItemCount = tAffinity.Items.Count<tAffinityRewardItem>();
        Affinity_EP4.AffinityList.Add(tAffinity);
      }
      int num = (int) new CustomMessage("Done!").ShowDialog();
    }

		private static List<tAffinityNpc> GetNpcs(int affinityid)
		{
			var npcs = new List<tAffinityNpc>();

			using (var connection = new MySqlConnection(
				$"Server={Affinity_EP4.Host};Port=3306;User ID={Affinity_EP4.User};Password={Affinity_EP4.Password};Database={Affinity_EP4.Database};Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12"))
			{
				connection.Open();

				string query = "SELECT * FROM t_affinity_npc WHERE a_affinity_idx = @affinityid";

				using (var cmd = new MySqlCommand(query, connection))
				{
					cmd.Parameters.AddWithValue("@affinityid", affinityid);

					using (var reader = cmd.ExecuteReader())
					{
						while (reader.Read())
						{
							npcs.Add(new tAffinityNpc
							{
								a_npcidx = reader.GetInt32("a_npcidx"),
								a_use_point = reader.GetInt32("a_use_point"),
								a_enable = reader.GetBoolean("a_enable"),
								a_flag = reader.GetInt32("a_flag"),
								a_string_idx = reader.GetInt32("a_string_idx")
							});
						}
					}
				}
			}

			return npcs;
		}

		private static List<tAffinityWork> GetWork(int affinityid)
		{
			var work = new List<tAffinityWork>();

			using (var connection = new MySqlConnection(
				$"Server={Host};Port=3306;User ID={User};Password={Password};Database={Database};Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12"))
			{
				connection.Open();
				const string query = "SELECT * FROM t_affinity_work WHERE a_affinity_idx = @affinityid";

				using (var cmd = new MySqlCommand(query, connection))
				{
					cmd.Parameters.AddWithValue("@affinityid", affinityid);

					using (var reader = cmd.ExecuteReader())
					{
						while (reader.Read())
						{
							work.Add(new tAffinityWork
							{
								a_work_type = reader.GetInt32("a_work_type"),
								a_type_idx = reader.GetInt32("a_type_idx"),
								a_value = reader.GetInt32("a_value"),
								a_enable = reader.GetBoolean("a_enable"),
								a_id = reader.GetInt32("a_id"),
								a_row = reader.GetInt32("a_row"),
								a_col = reader.GetInt32("a_col")
							});
						}
					}
				}
			}

			return work;
		}


		private static List<tAffinityRewardItem> GetRewardItems(int npcID)
		{
			var rewardItems = new List<tAffinityRewardItem>();

			using (var connection = new MySqlConnection(
				$"Server={Host};Port=3306;User ID={User};Password={Password};Database={Database};Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12"))
			{
				connection.Open();
				const string query = "SELECT * FROM t_affinity_reward_item WHERE a_npcidx = @npcID";

				using (var cmd = new MySqlCommand(query, connection))
				{
					cmd.Parameters.AddWithValue("@npcID", npcID);

					using (var reader = cmd.ExecuteReader())
					{
						while (reader.Read())
						{
							rewardItems.Add(new tAffinityRewardItem
							{
								a_itemidx = reader.GetInt32("a_itemidx"),
								a_flag = reader.GetInt32("a_flag"),
								a_count = reader.GetInt32("a_count"),
								a_exp = reader.GetInt32("a_exp"),
								a_sp = reader.GetInt32("a_sp"),
								a_needpclevel = reader.GetInt32("a_needpclevel"),
								a_needitemidx = reader.GetInt32("a_needitemidx"),
								a_needitemcount = reader.GetInt32("a_needitemcount"),
								a_allow_point = reader.GetInt32("a_allow_point")
							});
						}
					}
				}
			}

			return rewardItems;
		}


		private void makelist()
    {
      int num = Affinity_EP4.AffinityList.Count<tAffinity>();
      for (int index = 0; index < num; ++index)
      {
        int aIndex = Affinity_EP4.AffinityList[index].a_index;
        string aNameUsa = Affinity_EP4.AffinityList[index].a_name_usa;
        this.lbAffinity.Items.Add((object) (aIndex.ToString() + " - " + aNameUsa));
      }
    }

    private void Open_Click(object sender, EventArgs e)
    {
      Skill_Lod.LoadFromFile(this._ClientPath + "Data\\skills.lod");
      Skill_Lod.LoadFromFileName(this._ClientPath + "Local\\" + Affinity_EP4.Str_Lang + "\\String\\strSkill_" + Affinity_EP4.Str_Lang + ".lod");
    }

    private void Affinity_EP4_Load(object sender, EventArgs e)
    {
      this.lbAffinity.Items.Clear();
      Affinity_EP4.AffinityList.Clear();
      Item_Lod.LoadFromFile(this._ClientPath + "Data\\itemAll.lod");
      Item_Lod.LoadFromFileName(this._ClientPath + "Local\\" + Affinity_EP4.Str_Lang + "\\String\\strItem_" + Affinity_EP4.Str_Lang + ".lod");
      Quest_Lod.LoadFromFile(this._ClientPath + "Data\\questAll.lod");
      Quest_Lod.LoadFromFileName(this._ClientPath + "Local\\" + Affinity_EP4.Str_Lang + "\\String\\strQuest_" + Affinity_EP4.Str_Lang + ".lod");
      Mob_Lod.LoadFromFile(this._ClientPath + "Data\\mobAll.lod");
      Mob_Lod.LoadFromFileName(this._ClientPath + "Local\\" + Affinity_EP4.Str_Lang + "\\String\\strNpcName_" + Affinity_EP4.Str_Lang + ".lod");
      Client_Lod.LoadFromFileName(this._ClientPath + "Local\\" + Affinity_EP4.Str_Lang + "\\String\\strClient_" + Affinity_EP4.Str_Lang + ".lod");
      this.LoadListBox();
      this.makelist();
    }

    private void button1_Click(object sender, EventArgs e)
    {
      List<int> intList = new List<int>();
      for (int index = 0; index < Affinity_EP4.AffinityList.Count<tAffinity>(); ++index)
        intList.Add(Affinity_EP4.AffinityList[index].a_index);
      intList.Sort();
      tAffinity tAffinity = new tAffinity();
      tAffinity.a_index = intList[intList.Count - 1] + 1;
      tAffinity.a_texture_id = 0;
      tAffinity.a_texture_row = 0;
      tAffinity.a_texture_col = 0;
      tAffinity.a_needitemidx = 0;
      tAffinity.a_needitemcount = 0;
      tAffinity.a_needlevel = 0;
      tAffinity.a_affinity_idx = 0;
      tAffinity.a_affinity_value = 0;
      tAffinity.a_name_usa = "New Affinity";
      tAffinity.NpcCount = 0;
      tAffinity.Npcs = new List<tAffinityNpc>();
      tAffinity.WorkItemCount = 0;
      tAffinity.Work = new List<tAffinityWork>();
      tAffinity.WorkMonsterCount = 0;
      tAffinity.WorkQuestCount = 0;
      tAffinity.ItemCount = 0;
      tAffinity.Items = new List<tAffinityRewardItem>();
      this.lbAffinity.Items.Add((object) (tAffinity.a_index.ToString() + " - " + tAffinity.a_name_usa));
      Affinity_EP4.AffinityList.Add(tAffinity);
    }

    private void button2_Click(object sender, EventArgs e)
    {
      int selectedIndex = this.lbAffinity.SelectedIndex;
      if (selectedIndex == -1)
        return;
      int ID = int.Parse(this.lbAffinity.SelectedItem.ToString().Split(' ')[0]);
      int index = Affinity_EP4.AffinityList.FindIndex((Predicate<tAffinity>) (p => p.a_index.Equals(ID)));
      if (index == -1)
        return;
      Affinity_EP4.AffinityList.RemoveAt(index);
      this.lbAffinity.Items.RemoveAt(selectedIndex);
    }

    private void button3_Click(object sender, EventArgs e)
    {
      int selectedIndex = this.lbAffinity.SelectedIndex;
      if (selectedIndex == -1)
        return;
      int ID = int.Parse(this.lbAffinity.SelectedItem.ToString().Split(' ')[0]);
      int index1 = Affinity_EP4.AffinityList.FindIndex((Predicate<tAffinity>) (p => p.a_index.Equals(ID)));
      if (index1 == -1)
        return;
      Affinity_EP4.AffinityList[index1].a_name_usa = this.textBox_name.Text;
      Affinity_EP4.AffinityList[index1].a_index = Convert.ToInt32(this.numericUpDown_ID.Value);
      if (Affinity_EP4.changetIcon)
      {
        Affinity_EP4.AffinityList[index1].a_texture_id = Affinity_EP4.newTexID;
        Affinity_EP4.AffinityList[index1].a_texture_row = Affinity_EP4.newTexrow;
        Affinity_EP4.AffinityList[index1].a_texture_col = Affinity_EP4.newTexcol;
      }
      Affinity_EP4.AffinityList[index1].a_needitemidx = Convert.ToInt32(this.numericUpDown_needitemID.Value);
      Affinity_EP4.AffinityList[index1].a_needitemcount = Convert.ToInt32(this.numericUpDown_needitemcount.Value);
      Affinity_EP4.AffinityList[index1].a_needlevel = Convert.ToInt32(this.numericUpDown_needLevel.Value);
      Affinity_EP4.AffinityList[index1].a_affinity_idx = Convert.ToInt32(this.numericUpDown_needaffinityid.Value);
      Affinity_EP4.AffinityList[index1].a_affinity_value = Convert.ToInt32(this.numericUpDown_needaffinitypoints.Value);
      int count1 = this.dataGridView_npc.Rows.Count;
      int count2 = this.dataGridView_affinity_rewardItem.Rows.Count;
      Affinity_EP4.AffinityList[index1].NpcCount = count1;
      Affinity_EP4.AffinityList[index1].Npcs.Clear();
      for (int index2 = 0; index2 < count1; ++index2)
        Affinity_EP4.AffinityList[index1].Npcs.Add(new tAffinityNpc()
        {
          a_npcidx = Convert.ToInt32(this.dataGridView_npc.Rows[index2].Cells[0].Value),
          a_flag = Convert.ToInt32(this.dataGridView_npc.Rows[index2].Cells[2].Value),
          a_string_idx = Convert.ToInt32(this.dataGridView_npc.Rows[index2].Cells[3].Value)
        });
      Affinity_EP4.AffinityList[index1].ItemCount = count2;
      Affinity_EP4.AffinityList[index1].Items.Clear();
      for (int index3 = 0; index3 < count2; ++index3)
        Affinity_EP4.AffinityList[index1].Items.Add(new tAffinityRewardItem()
        {
          a_itemidx = Convert.ToInt32(this.dataGridView_affinity_rewardItem.Rows[index3].Cells[1].Value),
          a_allow_point = Convert.ToInt32(this.dataGridView_affinity_rewardItem.Rows[index3].Cells[3].Value)
        });
      int count3 = this.dataGridView_GetAff_Monster.Rows.Count;
      int count4 = this.dataGridView_GetAff_Item.Rows.Count;
      int count5 = this.dataGridView_getAff_Quest.Rows.Count;
      Affinity_EP4.AffinityList[index1].WorkItemCount = count4;
      Affinity_EP4.AffinityList[index1].WorkMonsterCount = count3;
      Affinity_EP4.AffinityList[index1].WorkQuestCount = count5;
      Affinity_EP4.AffinityList[index1].Work.Clear();
      for (int index4 = 0; index4 < count4; ++index4)
        Affinity_EP4.AffinityList[index1].Work.Add(new tAffinityWork()
        {
          a_work_type = 0,
          a_type_idx = Convert.ToInt32(this.dataGridView_GetAff_Item.Rows[index4].Cells[1].Value),
          a_value = Convert.ToInt32(this.dataGridView_GetAff_Item.Rows[index4].Cells[3].Value)
        });
      for (int index5 = 0; index5 < count3; ++index5)
        Affinity_EP4.AffinityList[index1].Work.Add(new tAffinityWork()
        {
          a_work_type = 1,
          a_type_idx = Convert.ToInt32(this.dataGridView_GetAff_Monster.Rows[index5].Cells[0].Value),
          a_value = Convert.ToInt32(this.dataGridView_GetAff_Monster.Rows[index5].Cells[2].Value)
        });
      for (int index6 = 0; index6 < count5; ++index6)
        Affinity_EP4.AffinityList[index1].Work.Add(new tAffinityWork()
        {
          a_work_type = 2,
          a_type_idx = Convert.ToInt32(this.dataGridView_getAff_Quest.Rows[index6].Cells[0].Value),
          a_value = Convert.ToInt32(this.dataGridView_getAff_Quest.Rows[index6].Cells[2].Value)
        });
      this.lbAffinity.Items[selectedIndex] = (object) (this.numericUpDown_ID.Value.ToString() + " - " + this.textBox_name.Text);
      int num = (int) new CustomMessage("Change Saved!").ShowDialog();
    }

    private void lbAffinity_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (this.lbAffinity.SelectedIndex == -1)
        return;
      int ID = int.Parse(this.lbAffinity.SelectedItem.ToString().Split(' ')[0]);
      int index1 = Affinity_EP4.AffinityList.FindIndex((Predicate<tAffinity>) (p => p.a_index.Equals(ID)));
      if (index1 == -1)
        return;
      this.textBox_name.Text = Affinity_EP4.AffinityList[index1].a_name_usa;
      this.numericUpDown_ID.Value = (Decimal) Affinity_EP4.AffinityList[index1].a_index;
      this.pictureBox_Affinity.Image = (Image) Affinity_EP4.AffinityIcons(Affinity_EP4.AffinityList[index1].a_texture_id, Affinity_EP4.AffinityList[index1].a_texture_row, Affinity_EP4.AffinityList[index1].a_texture_col);
      this.numericUpDown_needitemID.Value = (Decimal) Affinity_EP4.AffinityList[index1].a_needitemidx;
      this.numericUpDown_needitemcount.Value = (Decimal) Affinity_EP4.AffinityList[index1].a_needitemcount;
      this.numericUpDown_needLevel.Value = (Decimal) Affinity_EP4.AffinityList[index1].a_needlevel;
      this.numericUpDown_needaffinityid.Value = (Decimal) Affinity_EP4.AffinityList[index1].a_affinity_idx;
      this.numericUpDown_needaffinitypoints.Value = (Decimal) Affinity_EP4.AffinityList[index1].a_affinity_value;
      this.dataGridView_npc.Rows.Clear();
      for (int index2 = 0; index2 < Affinity_EP4.AffinityList[index1].NpcCount; ++index2)
      {
        int NPCID = Affinity_EP4.AffinityList[index1].Npcs[index2].a_npcidx;
        int aUsePoint = Affinity_EP4.AffinityList[index1].Npcs[index2].a_use_point;
        bool aEnable = Affinity_EP4.AffinityList[index1].Npcs[index2].a_enable;
        int aFlag = Affinity_EP4.AffinityList[index1].Npcs[index2].a_flag;
        int aStringIdx = Affinity_EP4.AffinityList[index1].Npcs[index2].a_string_idx;
        string nameFromId = Client_Lod.GetNameFromID(Affinity_EP4.AffinityList[index1].Npcs[index2].a_string_idx);
        int index3 = Mob_Lod.MobList.FindIndex((Predicate<Mob>) (n => n.NpcID.Equals(NPCID)));
        if (index3 != -1)
          this.dataGridView_npc.Rows.Add((object) NPCID, (object) Mob_Lod.MobList[index3].NpcName, (object) aFlag, (object) aStringIdx, (object) nameFromId, (object) aUsePoint, (object) aEnable);
        else
          this.dataGridView_npc.Rows.Add((object) NPCID, (object) "", (object) aFlag, (object) aStringIdx, (object) "", (object) aUsePoint, (object) aEnable);
      }
      this.dataGridView_affinity_rewardItem.Rows.Clear();
      this.dataGridView_affinity_rewardItem.AutoSizeRowsMode = DataGridViewAutoSizeRowsMode.AllCells;
      for (int index4 = 0; index4 < Affinity_EP4.AffinityList[index1].ItemCount; ++index4)
        this.dataGridView_affinity_rewardItem.Rows.Add((object) Item_Lod.Icon((object) Affinity_EP4.AffinityList[index1].Items[index4].a_itemidx), (object) Affinity_EP4.AffinityList[index1].Items[index4].a_itemidx, (object) Item_Lod.GetNameFromID(Affinity_EP4.AffinityList[index1].Items[index4].a_itemidx), (object) Affinity_EP4.AffinityList[index1].Items[index4].a_allow_point);
      List<tAffinityWork> work = Affinity_EP4.AffinityList[index1].Work.FindAll((Predicate<tAffinityWork>) (p => p.a_work_type.Equals(0)));
      this.dataGridView_GetAff_Item.Rows.Clear();
      this.dataGridView_GetAff_Item.AutoSizeRowsMode = DataGridViewAutoSizeRowsMode.AllCells;
      for (int index5 = 0; index5 < work.Count<tAffinityWork>(); ++index5)
        this.dataGridView_GetAff_Item.Rows.Add((object) Item_Lod.Icon((object) work[index5].a_type_idx), (object) work[index5].a_type_idx, (object) Item_Lod.GetNameFromID(work[index5].a_type_idx), (object) work[index5].a_value);
      work = Affinity_EP4.AffinityList[index1].Work.FindAll((Predicate<tAffinityWork>) (p => p.a_work_type.Equals(1)));
      this.dataGridView_GetAff_Monster.Rows.Clear();
      this.dataGridView_GetAff_Monster.AutoSizeRowsMode = DataGridViewAutoSizeRowsMode.AllCells;
      for (int i = 0; i < work.Count<tAffinityWork>(); ++i)
      {
        int index6 = Mob_Lod.MobList.FindIndex((Predicate<Mob>) (n => n.NpcID.Equals(work[i].a_type_idx)));
        if (index6 != -1)
          this.dataGridView_GetAff_Monster.Rows.Add((object) work[i].a_type_idx, (object) Mob_Lod.MobList[index6].NpcName, (object) work[i].a_value);
        else
          this.dataGridView_GetAff_Monster.Rows.Add((object) work[i].a_type_idx, (object) "", (object) work[i].a_value);
      }
      work = Affinity_EP4.AffinityList[index1].Work.FindAll((Predicate<tAffinityWork>) (p => p.a_work_type.Equals(2)));
      this.dataGridView_getAff_Quest.Rows.Clear();
      this.dataGridView_getAff_Quest.AutoSizeRowsMode = DataGridViewAutoSizeRowsMode.AllCells;
      Encoding.GetEncoding(Affinity_EP4.ISO);
      for (int i = 0; i < work.Count<tAffinityWork>(); ++i)
      {
        int index7 = Quest_Lod.QuestList.FindIndex((Predicate<Quest>) (p => p.QuestIndex.Equals(work[i].a_type_idx)));
        if (index7 != -1)
          this.dataGridView_getAff_Quest.Rows.Add((object) work[i].a_type_idx, (object) Quest_Lod.QuestList[index7].QuestName, (object) work[i].a_value);
        else
          this.dataGridView_getAff_Quest.Rows.Add((object) work[i].a_type_idx, (object) "", (object) work[i].a_value);
      }
    }

    private void button_addnpc_Click(object sender, EventArgs e)
    {
      if (this.lbAffinity.SelectedIndex == -1)
        return;
      int ID = int.Parse(this.lbAffinity.SelectedItem.ToString().Split(' ')[0]);
      if (Affinity_EP4.AffinityList.FindIndex((Predicate<tAffinity>) (p => p.a_index.Equals(ID))) == -1)
        return;
      NpcSearch npcSearch = new NpcSearch();
      if (npcSearch.ShowDialog() != DialogResult.OK)
        return;
      int NPCID = npcSearch.ReturnNpcID;
      if (NPCID < 0)
        return;
      int num1 = 0;
      int num2 = 0;
      int num3 = 0;
      bool flag = true;
      int index = Mob_Lod.MobList.FindIndex((Predicate<Mob>) (n => n.NpcID.Equals(NPCID)));
      if (index != -1)
        this.dataGridView_npc.Rows.Add((object) NPCID, (object) Mob_Lod.MobList[index].NpcName, (object) num1, (object) num2, (object) num3, (object) flag);
      else
        this.dataGridView_npc.Rows.Add((object) NPCID, (object) "", (object) num1, (object) num2, (object) num3, (object) flag);
    }

    private void button_removenpc_Click(object sender, EventArgs e)
    {
      if (this.lbAffinity.SelectedIndex == -1)
        return;
      int ID = int.Parse(this.lbAffinity.SelectedItem.ToString().Split(' ')[0]);
      if (Affinity_EP4.AffinityList.FindIndex((Predicate<tAffinity>) (p => p.a_index.Equals(ID))) == -1)
        return;
      int count = this.dataGridView_npc.SelectedRows.Count;
      int[] numArray = new int[count];
      for (int index = 0; index < count; ++index)
        numArray[index] = this.dataGridView_npc.SelectedRows[index].Index;
      for (int index = 0; index < count; ++index)
        this.dataGridView_npc.Rows.RemoveAt(numArray[index]);
    }

    private void numericUpDown_needaffinityid_ValueChanged(object sender, EventArgs e)
    {
      int AffinityID = Convert.ToInt32(this.numericUpDown_needaffinityid.Value);
      int index = Affinity_EP4.AffinityList.FindIndex((Predicate<tAffinity>) (p => p.a_index.Equals(AffinityID)));
      if (index != -1)
      {
        this.textBox_needaffinityName.Text = Affinity_EP4.AffinityList[index].a_name_usa;
        this.pictureBox_needaffinity.Image = (Image) Affinity_EP4.AffinityIcons(Affinity_EP4.AffinityList[index].a_texture_id, Affinity_EP4.AffinityList[index].a_texture_row, Affinity_EP4.AffinityList[index].a_texture_col);
      }
      else
      {
        this.textBox_needaffinityName.Text = "";
        this.pictureBox_needaffinity.Image = (Image) null;
      }
    }

    private void button_addaffinityitemReward_Click(object sender, EventArgs e)
    {
      if (this.lbAffinity.SelectedIndex == -1)
        return;
      int ID = int.Parse(this.lbAffinity.SelectedItem.ToString().Split(' ')[0]);
      if (Affinity_EP4.AffinityList.FindIndex((Predicate<tAffinity>) (p => p.a_index.Equals(ID))) == -1)
        return;
      LcDevPack_TeamDamonA.Tools.MemoryWorker.ItemSearch itemSearch = new LcDevPack_TeamDamonA.Tools.MemoryWorker.ItemSearch();
      if (itemSearch.ShowDialog() != DialogResult.OK)
        return;
      int returnItemId = itemSearch.ReturnItemID;
      if (returnItemId < 0)
        return;
      this.dataGridView_affinity_rewardItem.Rows.Add((object) Item_Lod.Icon((object) returnItemId), (object) returnItemId, (object) Item_Lod.GetNameFromID(returnItemId), (object) 1);
    }

    private void button_removeaffinityitemReward_Click(object sender, EventArgs e)
    {
      if (this.lbAffinity.SelectedIndex == -1)
        return;
      int ID = int.Parse(this.lbAffinity.SelectedItem.ToString().Split(' ')[0]);
      if (Affinity_EP4.AffinityList.FindIndex((Predicate<tAffinity>) (p => p.a_index.Equals(ID))) == -1)
        return;
      int count = this.dataGridView_affinity_rewardItem.SelectedRows.Count;
      int[] numArray = new int[count];
      for (int index = 0; index < count; ++index)
        numArray[index] = this.dataGridView_affinity_rewardItem.SelectedRows[index].Index;
      for (int index = 0; index < count; ++index)
        this.dataGridView_affinity_rewardItem.Rows.RemoveAt(numArray[index]);
    }

    private void b_affitem_Click(object sender, EventArgs e)
    {
    }

    private void button9_Click(object sender, EventArgs e)
    {
      if (this.lbAffinity.SelectedIndex == -1)
        return;
      int ID = int.Parse(this.lbAffinity.SelectedItem.ToString().Split(' ')[0]);
      if (Affinity_EP4.AffinityList.FindIndex((Predicate<tAffinity>) (p => p.a_index.Equals(ID))) == -1)
        return;
      int count = this.dataGridView_GetAff_Item.SelectedRows.Count;
      int[] numArray = new int[count];
      for (int index = 0; index < count; ++index)
        numArray[index] = this.dataGridView_GetAff_Item.SelectedRows[index].Index;
      for (int index = 0; index < count; ++index)
        this.dataGridView_GetAff_Item.Rows.RemoveAt(numArray[index]);
    }

    private void button8_Click(object sender, EventArgs e)
    {
      if (this.lbAffinity.SelectedIndex == -1)
        return;
      int ID = int.Parse(this.lbAffinity.SelectedItem.ToString().Split(' ')[0]);
      if (Affinity_EP4.AffinityList.FindIndex((Predicate<tAffinity>) (p => p.a_index.Equals(ID))) == -1)
        return;
      NpcSearch npcSearch = new NpcSearch();
      if (npcSearch.ShowDialog() != DialogResult.OK)
        return;
      int NPCID = npcSearch.ReturnNpcID;
      if (NPCID < 0)
        return;
      int num1 = 0;
      int num2 = 0;
      int index = Mob_Lod.MobList.FindIndex((Predicate<Mob>) (n => n.NpcID.Equals(NPCID)));
      if (index != -1)
        this.dataGridView_GetAff_Monster.Rows.Add((object) NPCID, (object) NpcSearch.NPCList[index].NpcName, (object) num1, (object) num2);
      else
        this.dataGridView_GetAff_Monster.Rows.Add((object) NPCID, (object) "", (object) num1, (object) num2);
    }

    private void button4_Click(object sender, EventArgs e)
    {
      if (this.lbAffinity.SelectedIndex == -1)
        return;
      int ID = int.Parse(this.lbAffinity.SelectedItem.ToString().Split(' ')[0]);
      if (Affinity_EP4.AffinityList.FindIndex((Predicate<tAffinity>) (p => p.a_index.Equals(ID))) == -1)
        return;
      int count = this.dataGridView_GetAff_Monster.SelectedRows.Count;
      int[] numArray = new int[count];
      for (int index = 0; index < count; ++index)
        numArray[index] = this.dataGridView_GetAff_Monster.SelectedRows[index].Index;
      for (int index = 0; index < count; ++index)
        this.dataGridView_GetAff_Monster.Rows.RemoveAt(numArray[index]);
    }

    private void button6_Click(object sender, EventArgs e)
    {
      if (this.lbAffinity.SelectedIndex == -1)
        return;
      int ID = int.Parse(this.lbAffinity.SelectedItem.ToString().Split(' ')[0]);
      if (Affinity_EP4.AffinityList.FindIndex((Predicate<tAffinity>) (p => p.a_index.Equals(ID))) == -1)
        return;
      QuestSearch questSearch = new QuestSearch();
      if (questSearch.ShowDialog() != DialogResult.OK)
        return;
      int QUESTID = questSearch.ReturnQuestID;
      if (QUESTID < 0)
        return;
      Encoding.GetEncoding(Affinity_EP4.ISO);
      int index = Quest_Lod.QuestList.FindIndex((Predicate<Quest>) (p => p.QuestIndex.Equals(QUESTID)));
      if (index != -1)
        this.dataGridView_getAff_Quest.Rows.Add((object) QUESTID, (object) Quest_Lod.QuestList[index].QuestName, (object) 1);
      else
        this.dataGridView_getAff_Quest.Rows.Add((object) QUESTID, (object) "", (object) 1);
    }

    private void button5_Click(object sender, EventArgs e)
    {
      if (this.lbAffinity.SelectedIndex == -1)
        return;
      int ID = int.Parse(this.lbAffinity.SelectedItem.ToString().Split(' ')[0]);
      if (Affinity_EP4.AffinityList.FindIndex((Predicate<tAffinity>) (p => p.a_index.Equals(ID))) == -1)
        return;
      int count = this.dataGridView_getAff_Quest.SelectedRows.Count;
      int[] numArray = new int[count];
      for (int index = 0; index < count; ++index)
        numArray[index] = this.dataGridView_getAff_Quest.SelectedRows[index].Index;
      for (int index = 0; index < count; ++index)
        this.dataGridView_getAff_Quest.Rows.RemoveAt(numArray[index]);
    }

    private void numericUpDown_needitemID_ValueChanged(object sender, EventArgs e)
    {
      int ItemID = Convert.ToInt32(this.numericUpDown_needitemID.Value);
      int index = Item_Lod.ItemList.FindIndex((Predicate<ItemContainer>) (i => i.ItemID.Equals(ItemID)));
      if (index != -1)
      {
        this.textBox_needItemName.Text = Item_Lod.ItemList[index].Name;
        this.pictureBox_needItemID.Image = (Image) Item_Lod.Icon(Item_Lod.ItemList[index].TexID, Item_Lod.ItemList[index].TexRow, Item_Lod.ItemList[index].TexCol);
      }
      else
      {
        this.textBox_needItemName.Text = "";
        this.pictureBox_needItemID.Image = (Image) null;
      }
    }

    private void numericUpDown_ID_ValueChanged(object sender, EventArgs e)
    {
    }

    private void button_iconsearch_Click(object sender, EventArgs e)
    {
      if (this.lbAffinity.SelectedIndex == -1)
        return;
      int ID = int.Parse(this.lbAffinity.SelectedItem.ToString().Split(' ')[0]);
      if (Affinity_EP4.AffinityList.FindIndex((Predicate<tAffinity>) (p => p.a_index.Equals(ID))) == -1)
        return;
      IconPickerAffinity iconPickerAffinity = new IconPickerAffinity();
      if (iconPickerAffinity.ShowDialog() != DialogResult.OK)
        return;
      Affinity_EP4.newTexID = iconPickerAffinity.TexID;
      Affinity_EP4.newTexrow = iconPickerAffinity.TexRow;
      Affinity_EP4.newTexcol = iconPickerAffinity.TexColumn;
      this.pictureBox_Affinity.Image = (Image) Affinity_EP4.AffinityIcons(Affinity_EP4.newTexID, Affinity_EP4.newTexrow, Affinity_EP4.newTexcol);
      Affinity_EP4.changetIcon = true;
    }

    private void button_itemsearch_Click(object sender, EventArgs e)
    {
      if (this.lbAffinity.SelectedIndex == -1)
        return;
      int ID = int.Parse(this.lbAffinity.SelectedItem.ToString().Split(' ')[0]);
      if (Affinity_EP4.AffinityList.FindIndex((Predicate<tAffinity>) (p => p.a_index.Equals(ID))) == -1)
        return;
      LcDevPack_TeamDamonA.Tools.MemoryWorker.ItemSearch itemSearch = new LcDevPack_TeamDamonA.Tools.MemoryWorker.ItemSearch();
      if (itemSearch.ShowDialog() != DialogResult.OK)
        return;
      int returnItemId = itemSearch.ReturnItemID;
      if (returnItemId < 0)
        return;
      this.numericUpDown_needitemID.Value = (Decimal) returnItemId;
    }

    private void button7_Click(object sender, EventArgs e)
    {
      if (this.lbAffinity.SelectedIndex == -1)
        return;
      int ID = int.Parse(this.lbAffinity.SelectedItem.ToString().Split(' ')[0]);
      if (Affinity_EP4.AffinityList.FindIndex((Predicate<tAffinity>) (p => p.a_index.Equals(ID))) == -1)
        return;
      AffinitySearch affinitySearch = new AffinitySearch();
      if (affinitySearch.ShowDialog() != DialogResult.OK)
        return;
      int returnAffinityId = affinitySearch.ReturnAffinityID;
      if (returnAffinityId < 0)
        return;
      this.numericUpDown_needaffinityid.Value = (Decimal) returnAffinityId;
    }

    private void textBox22_TextChanged(object sender, EventArgs e)
    {
    }

    private void Save_Click(object sender, EventArgs e)
    {
      SaveFileDialog saveFileDialog = new SaveFileDialog();
      saveFileDialog.Filter = "affinity*|affinity*.*|lod|*.lod|data|*.data|All|*.*";
      saveFileDialog.Title = "Save Affinity.lod";
      if (saveFileDialog.ShowDialog() == DialogResult.Cancel)
        return;
      Affinity_EP4.SaveFile(saveFileDialog.FileName);
    }

    public static void SaveFile(string FileName)
    {
      try
      {
        int num1 = 0;
        Encoding.GetEncoding(Affinity_EP4.ISO);
        List<int> SortedIDs = new List<int>();
        for (int index = 0; index < Affinity_EP4.AffinityList.Count<tAffinity>(); ++index)
          SortedIDs.Add(Affinity_EP4.AffinityList[index].a_index);
        SortedIDs.Sort();
        BinaryWriter binaryWriter = new BinaryWriter((Stream) File.Create(FileName));
        binaryWriter.Write(Affinity_EP4.AffinityList.Count<tAffinity>());
        num1 = -1;
        for (int a = 0; a < SortedIDs.Count<int>(); ++a)
        {
          int index1 = Affinity_EP4.AffinityList.FindIndex((Predicate<tAffinity>) (p => p.a_index.Equals(SortedIDs[a])));
          if (index1 != -1)
          {
            binaryWriter.Write(Affinity_EP4.AffinityList[index1].a_index);
            binaryWriter.Write(Affinity_EP4.AffinityList[index1].a_texture_id);
            binaryWriter.Write(Affinity_EP4.AffinityList[index1].a_texture_row);
            binaryWriter.Write(Affinity_EP4.AffinityList[index1].a_texture_col);
            binaryWriter.Write(Affinity_EP4.AffinityList[index1].a_needitemidx);
            binaryWriter.Write(Affinity_EP4.AffinityList[index1].a_needitemcount);
            binaryWriter.Write(Affinity_EP4.AffinityList[index1].a_needlevel);
            binaryWriter.Write(Affinity_EP4.AffinityList[index1].a_affinity_idx);
            binaryWriter.Write(Affinity_EP4.AffinityList[index1].a_affinity_value);
            binaryWriter.Write(Affinity_EP4.AffinityList[index1].NpcCount);
            foreach (tAffinityNpc npc in Affinity_EP4.AffinityList[index1].Npcs)
            {
              binaryWriter.Write(npc.a_npcidx);
              binaryWriter.Write(npc.a_flag);
              binaryWriter.Write(npc.a_string_idx);
            }
            List<tAffinityWork> all1 = Affinity_EP4.AffinityList[index1].Work.FindAll((Predicate<tAffinityWork>) (p => p.a_work_type.Equals(0)));
            binaryWriter.Write(all1.Count);
            for (int index2 = 0; index2 < all1.Count; ++index2)
            {
              binaryWriter.Write(all1[index2].a_type_idx);
              binaryWriter.Write(all1[index2].a_value);
            }
            List<tAffinityWork> all2 = Affinity_EP4.AffinityList[index1].Work.FindAll((Predicate<tAffinityWork>) (p => p.a_work_type.Equals(1)));
            binaryWriter.Write(all2.Count);
            for (int index3 = 0; index3 < all2.Count; ++index3)
            {
              binaryWriter.Write(all2[index3].a_type_idx);
              binaryWriter.Write(all2[index3].a_value);
              binaryWriter.Write(all2[index3].a_id);
              binaryWriter.Write(all2[index3].a_row);
              binaryWriter.Write(all2[index3].a_col);
            }
            List<tAffinityWork> all3 = Affinity_EP4.AffinityList[index1].Work.FindAll((Predicate<tAffinityWork>) (p => p.a_work_type.Equals(2)));
            binaryWriter.Write(all3.Count);
            for (int index4 = 0; index4 < all3.Count; ++index4)
            {
              binaryWriter.Write(all3[index4].a_type_idx);
              binaryWriter.Write(all3[index4].a_value);
            }
            binaryWriter.Write(Affinity_EP4.AffinityList[index1].ItemCount);
            foreach (tAffinityRewardItem affinityRewardItem in Affinity_EP4.AffinityList[index1].Items)
            {
              binaryWriter.Write(affinityRewardItem.a_itemidx);
              binaryWriter.Write(affinityRewardItem.a_allow_point);
            }
          }
        }
        binaryWriter.Close();
        int num2 = (int) new CustomMessage("File Saved!").ShowDialog();
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message, "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
    }

    private void Saveas_Click(object sender, EventArgs e)
    {
      SaveFileDialog saveFileDialog = new SaveFileDialog();
      saveFileDialog.Filter = "affinity*|affinity*.*|lod|*.lod|data|*.data|All|*.*";
      saveFileDialog.Title = "Save Affinity.lod";
      if (saveFileDialog.ShowDialog() == DialogResult.Cancel)
        return;
      Affinity_EP4.SaveFile(saveFileDialog.FileName);
    }

    private void getAllFromDBToolStripMenuItem_Click(object sender, EventArgs e)
    {
      this.lbAffinity.Items.Clear();
      Affinity_EP4.AffinityList.Clear();
      Affinity_EP4.GetAll();
      for (int index = 0; index < Affinity_EP4.AffinityList.Count<tAffinity>(); ++index)
        this.lbAffinity.Items.Add((object) (Affinity_EP4.AffinityList[index].a_index.ToString() + " - " + Affinity_EP4.AffinityList[index].a_name_usa));
    }

    public static void GetAll()
    {
      MySqlConnection connection = new MySqlConnection("datasource=" + Affinity_EP4.Host + ";port=3306;username=" + Affinity_EP4.User + ";password=" + Affinity_EP4.Password + ";database=" + Affinity_EP4.Database);
      connection.Open();
      MySqlCommand mySqlCommand = new MySqlCommand("SELECT * FROM t_affinity WHERE a_enable = 1", connection);
      mySqlCommand.ExecuteNonQuery();
      MySqlDataReader mySqlDataReader = mySqlCommand.ExecuteReader();
      while (mySqlDataReader.Read())
      {
        tAffinity tAffinity = new tAffinity()
        {
          a_index = Convert.ToInt32(mySqlDataReader["a_index"]),
          a_texture_id = Convert.ToInt32(mySqlDataReader["a_texture_id"]),
          a_texture_row = Convert.ToInt32(mySqlDataReader["a_texture_row"]),
          a_texture_col = Convert.ToInt32(mySqlDataReader["a_texture_col"]),
          a_needitemidx = Convert.ToInt32(mySqlDataReader["a_needitemidx"]),
          a_needitemcount = Convert.ToInt32(mySqlDataReader["a_needitemcount"]),
          a_needlevel = Convert.ToInt32(mySqlDataReader["a_needlevel"]),
          a_affinity_idx = Convert.ToInt32(mySqlDataReader["a_affinity_idx"]),
          a_affinity_value = Convert.ToInt32(mySqlDataReader["a_affinity_value"]),
          a_name_usa = mySqlDataReader["a_name_usa"].ToString(),
          a_maxvalue = Convert.ToInt32(mySqlDataReader["a_maxvalue"])
        };
        tAffinity.Npcs = Affinity_EP4.GetNpcs(tAffinity.a_index);
        tAffinity.NpcCount = tAffinity.Npcs.Count<tAffinityNpc>();
        tAffinity.Work = Affinity_EP4.GetWork(tAffinity.a_index);
        tAffinity.WorkItemCount = tAffinity.Work.Count<tAffinityWork>();
        tAffinity.Items = new List<tAffinityRewardItem>();
        for (int index = 0; index < tAffinity.NpcCount; ++index)
          tAffinity.Items.AddRange((IEnumerable<tAffinityRewardItem>) Affinity_EP4.GetRewardItems(tAffinity.Npcs[index].a_npcidx));
        tAffinity.ItemCount = tAffinity.Items.Count<tAffinityRewardItem>();
        Affinity_EP4.AffinityList.Add(tAffinity);
      }
      int num = (int) new CustomMessage("Done!").ShowDialog();
    }

		public static void SaveWork(tAffinity aff)
		{
			using (var connection = new MySqlConnection(
				$"Server={Host};Port=3306;User ID={User};Password={Password};Database={Database};Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12"))
			{
				connection.Open();

				using (var delCmd = new MySqlCommand("DELETE FROM t_affinity_work WHERE a_affinity_idx = @idx", connection))
				{
					delCmd.Parameters.AddWithValue("@idx", aff.a_index);
					delCmd.ExecuteNonQuery();
				}

				const string insertQuery = @"INSERT INTO t_affinity_work
            (a_work_type, a_type_idx, a_affinity_idx, a_value, a_enable, a_id, a_row, a_col)
            VALUES (@type, @typeidx, @affidx, @value, @enable, @id, @row, @col)";

				foreach (var work in aff.Work)
				{
					using (var cmd = new MySqlCommand(insertQuery, connection))
					{
						cmd.Parameters.AddWithValue("@type", work.a_work_type);
						cmd.Parameters.AddWithValue("@typeidx", work.a_type_idx);
						cmd.Parameters.AddWithValue("@affidx", aff.a_index);
						cmd.Parameters.AddWithValue("@value", work.a_value);
						cmd.Parameters.AddWithValue("@enable", work.a_enable);
						cmd.Parameters.AddWithValue("@id", work.a_id);
						cmd.Parameters.AddWithValue("@row", work.a_row);
						cmd.Parameters.AddWithValue("@col", work.a_col);
						cmd.ExecuteNonQuery();
					}
				}
			}
		}


		public static bool SaveDatabase()
		{
			try
			{
				using (var connection = new MySqlConnection(
					$"Server={Affinity_EP4.Host};Port=3306;User ID={Affinity_EP4.User};Password={Affinity_EP4.Password};Database={Affinity_EP4.Database};Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12"))
				{
					connection.Open();

					// Wipe existing tables safely
					var truncateTables = new[]
					{
				"TRUNCATE TABLE t_affinity;",
				"TRUNCATE TABLE t_affinity_npc;",
				"TRUNCATE TABLE t_affinity_reward_item;",
				"TRUNCATE TABLE t_affinity_work;"
			};

					foreach (var sql in truncateTables)
					{
						using (var cmd = new MySqlCommand(sql, connection))
							cmd.ExecuteNonQuery();
					}

					// Re-insert affinities
					const string insertQuery = @"
                INSERT INTO t_affinity(
                    a_index, a_name, a_maxvalue, a_enable, a_texture_id, a_texture_row, a_texture_col,
                    a_nas, a_needlevel, a_needitemidx, a_needitemcount, a_affinity_idx, a_affinity_value, a_name_usa)
                VALUES(
                    @index, @name, @maxvalue, @enable, @texid, @texrow, @texcol,
                    @nas, @needlevel, @needitemidx, @needitemcount, @needaffinity, @needaffinityvalue, @nameUSA)";

					foreach (var affinity in Affinity_EP4.AffinityList)
					{
						using (var cmd = new MySqlCommand(insertQuery, connection))
						{
							cmd.Parameters.AddWithValue("@index", affinity.a_index);
							cmd.Parameters.AddWithValue("@name", affinity.a_name_usa);
							cmd.Parameters.AddWithValue("@maxvalue", affinity.a_maxvalue);
							cmd.Parameters.AddWithValue("@enable", affinity.a_enable);
							cmd.Parameters.AddWithValue("@texid", affinity.a_texture_id);
							cmd.Parameters.AddWithValue("@texrow", affinity.a_texture_row);
							cmd.Parameters.AddWithValue("@texcol", affinity.a_texture_col);
							cmd.Parameters.AddWithValue("@nas", affinity.a_nas);
							cmd.Parameters.AddWithValue("@needlevel", affinity.a_needlevel);
							cmd.Parameters.AddWithValue("@needitemidx", affinity.a_needitemidx);
							cmd.Parameters.AddWithValue("@needitemcount", affinity.a_needitemcount);
							cmd.Parameters.AddWithValue("@needaffinity", affinity.a_affinity_idx);
							cmd.Parameters.AddWithValue("@needaffinityvalue", affinity.a_affinity_value);
							cmd.Parameters.AddWithValue("@nameUSA", affinity.a_name_usa);
							cmd.ExecuteNonQuery();
						}
					}
				}

				return true;
			}
			catch (Exception ex)
			{
				MessageBox.Show($"Database save failed: {ex.Message}", "MySQL Error");
				return false;
			}
		}

		private void saveAllToDBToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (Affinity_EP4.SaveDatabase())
      {
        int num1 = (int) new CustomMessage("Done! :)").ShowDialog();
      }
      else
      {
        int num2 = (int) new CustomMessage("Failed! :(").ShowDialog();
      }
    }

    private void button11_Click(object sender, EventArgs e)
    {
      this.lbAffinity.Items.Clear();
      Affinity_EP4.AffinityList.Clear();
      Affinity_EP4.GetAll();
      for (int index = 0; index < Affinity_EP4.AffinityList.Count<tAffinity>(); ++index)
        this.lbAffinity.Items.Add((object) (Affinity_EP4.AffinityList[index].a_index.ToString() + " - " + Affinity_EP4.AffinityList[index].a_name_usa));
    }

    private void button10_Click(object sender, EventArgs e) => new AffinityEditor().Show();

    private void button12_Click(object sender, EventArgs e)
    {
      SaveFileDialog saveFileDialog = new SaveFileDialog();
      saveFileDialog.Filter = "affinity*|affinity*.*|lod|*.lod|data|*.data|All|*.*";
      saveFileDialog.Title = "Save Affinity.lod";
      if (saveFileDialog.ShowDialog() == DialogResult.Cancel)
        return;
      Affinity_EP4.SaveFile(saveFileDialog.FileName);
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (Affinity_EP4));
      this.toolStrip1 = new ToolStrip();
      this.lbAffinity = new ListBox();
      this.groupBox2 = new GroupBox();
      this.textBox_needItemName = new TextBox();
      this.numericUpDown_needaffinitypoints = new NumericUpDown();
      this.numericUpDown_needaffinityid = new NumericUpDown();
      this.textBox_needaffinityName = new TextBox();
      this.label7 = new Label();
      this.label6 = new Label();
      this.numericUpDown_needLevel = new NumericUpDown();
      this.numericUpDown_needitemcount = new NumericUpDown();
      this.numericUpDown_needitemID = new NumericUpDown();
      this.label3 = new Label();
      this.label5 = new Label();
      this.label4 = new Label();
      this.groupBox1 = new GroupBox();
      this.numericUpDown_ID = new NumericUpDown();
      this.label2 = new Label();
      this.textBox_name = new TextBox();
      this.label1 = new Label();
      this.groupBox8 = new GroupBox();
      this.textBox22 = new TextBox();
      this.label13 = new Label();
      this.button2 = new Button();
      this.button1 = new Button();
      this.button3 = new Button();
      this.groupBox7 = new GroupBox();
      this.dataGridView_getAff_Quest = new DataGridView();
      this.dataGridViewTextBoxColumn7 = new DataGridViewTextBoxColumn();
      this.dataGridViewTextBoxColumn8 = new DataGridViewTextBoxColumn();
      this.dataGridViewTextBoxColumn9 = new DataGridViewTextBoxColumn();
      this.button5 = new Button();
      this.button6 = new Button();
      this.groupBox6 = new GroupBox();
      this.dataGridView_GetAff_Monster = new DataGridView();
      this.dataGridViewTextBoxColumn4 = new DataGridViewTextBoxColumn();
      this.dataGridViewTextBoxColumn5 = new DataGridViewTextBoxColumn();
      this.dataGridViewTextBoxColumn6 = new DataGridViewTextBoxColumn();
      this.button4 = new Button();
      this.button8 = new Button();
      this.groupBox5 = new GroupBox();
      this.dataGridView_GetAff_Item = new DataGridView();
      this.dataGridViewImageColumn1 = new DataGridViewImageColumn();
      this.dataGridViewTextBoxColumn1 = new DataGridViewTextBoxColumn();
      this.dataGridViewTextBoxColumn2 = new DataGridViewTextBoxColumn();
      this.dataGridViewTextBoxColumn3 = new DataGridViewTextBoxColumn();
      this.button9 = new Button();
      this.b_affitem = new Button();
      this.groupBox4 = new GroupBox();
      this.dataGridView_affinity_rewardItem = new DataGridView();
      this.image = new DataGridViewImageColumn();
      this.Column1 = new DataGridViewTextBoxColumn();
      this.Column2 = new DataGridViewTextBoxColumn();
      this.Column3 = new DataGridViewTextBoxColumn();
      this.button_removeaffinityitemReward = new Button();
      this.button_addaffinityitemReward = new Button();
      this.groupBox3 = new GroupBox();
      this.button_removenpc = new Button();
      this.dataGridView_npc = new DataGridView();
      this.Npcid = new DataGridViewTextBoxColumn();
      this.npcname = new DataGridViewTextBoxColumn();
      this.Flag = new DataGridViewTextBoxColumn();
      this.Stringid = new DataGridViewTextBoxColumn();
      this.Column6 = new DataGridViewTextBoxColumn();
      this.Column4 = new DataGridViewTextBoxColumn();
      this.Column5 = new DataGridViewTextBoxColumn();
      this.button_addnpc = new Button();
      this.button12 = new Button();
      this.button11 = new Button();
      this.button10 = new Button();
      this.button_itemsearch = new Button();
      this.button7 = new Button();
      this.pictureBox_needaffinity = new PictureBox();
      this.pictureBox_needItemID = new PictureBox();
      this.button_iconsearch = new Button();
      this.pictureBox_Affinity = new PictureBox();
      this.Open = new ToolStripButton();
      this.Save = new ToolStripButton();
      this.Saveas = new ToolStripButton();
      this.toolStripSplitButton1 = new ToolStripSplitButton();
      this.getAllFromDBToolStripMenuItem = new ToolStripMenuItem();
      this.saveAllToDBToolStripMenuItem = new ToolStripMenuItem();
      this.toolStrip1.SuspendLayout();
      this.groupBox2.SuspendLayout();
      this.numericUpDown_needaffinitypoints.BeginInit();
      this.numericUpDown_needaffinityid.BeginInit();
      this.numericUpDown_needLevel.BeginInit();
      this.numericUpDown_needitemcount.BeginInit();
      this.numericUpDown_needitemID.BeginInit();
      this.groupBox1.SuspendLayout();
      this.numericUpDown_ID.BeginInit();
      this.groupBox8.SuspendLayout();
      this.groupBox7.SuspendLayout();
      ((ISupportInitialize) this.dataGridView_getAff_Quest).BeginInit();
      this.groupBox6.SuspendLayout();
      ((ISupportInitialize) this.dataGridView_GetAff_Monster).BeginInit();
      this.groupBox5.SuspendLayout();
      ((ISupportInitialize) this.dataGridView_GetAff_Item).BeginInit();
      this.groupBox4.SuspendLayout();
      ((ISupportInitialize) this.dataGridView_affinity_rewardItem).BeginInit();
      this.groupBox3.SuspendLayout();
      ((ISupportInitialize) this.dataGridView_npc).BeginInit();
      ((ISupportInitialize) this.pictureBox_needaffinity).BeginInit();
      ((ISupportInitialize) this.pictureBox_needItemID).BeginInit();
      ((ISupportInitialize) this.pictureBox_Affinity).BeginInit();
      this.SuspendLayout();
      this.toolStrip1.Items.AddRange(new ToolStripItem[4]
      {
        (ToolStripItem) this.Open,
        (ToolStripItem) this.Save,
        (ToolStripItem) this.Saveas,
        (ToolStripItem) this.toolStripSplitButton1
      });
      this.toolStrip1.Location = new Point(0, 0);
      this.toolStrip1.Name = "toolStrip1";
      this.toolStrip1.Size = new Size(1109, 25);
      this.toolStrip1.TabIndex = 21;
      this.toolStrip1.Text = "toolStrip1";
      this.lbAffinity.FormattingEnabled = true;
      this.lbAffinity.Location = new Point(12, 97);
      this.lbAffinity.Name = "lbAffinity";
      this.lbAffinity.Size = new Size(196, 446);
      this.lbAffinity.TabIndex = 23;
      this.lbAffinity.SelectedIndexChanged += new EventHandler(this.lbAffinity_SelectedIndexChanged);
      this.groupBox2.Controls.Add((Control) this.button_itemsearch);
      this.groupBox2.Controls.Add((Control) this.button7);
      this.groupBox2.Controls.Add((Control) this.textBox_needItemName);
      this.groupBox2.Controls.Add((Control) this.numericUpDown_needaffinitypoints);
      this.groupBox2.Controls.Add((Control) this.pictureBox_needaffinity);
      this.groupBox2.Controls.Add((Control) this.numericUpDown_needaffinityid);
      this.groupBox2.Controls.Add((Control) this.textBox_needaffinityName);
      this.groupBox2.Controls.Add((Control) this.label7);
      this.groupBox2.Controls.Add((Control) this.label6);
      this.groupBox2.Controls.Add((Control) this.pictureBox_needItemID);
      this.groupBox2.Controls.Add((Control) this.numericUpDown_needLevel);
      this.groupBox2.Controls.Add((Control) this.numericUpDown_needitemcount);
      this.groupBox2.Controls.Add((Control) this.numericUpDown_needitemID);
      this.groupBox2.Controls.Add((Control) this.label3);
      this.groupBox2.Controls.Add((Control) this.label5);
      this.groupBox2.Controls.Add((Control) this.label4);
      this.groupBox2.Location = new Point(214, 119);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new Size(443, 161);
      this.groupBox2.TabIndex = 25;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "Need For Affinity";
      this.textBox_needItemName.Enabled = false;
      this.textBox_needItemName.Location = new Point(180, 18);
      this.textBox_needItemName.Name = "textBox_needItemName";
      this.textBox_needItemName.Size = new Size(223, 20);
      this.textBox_needItemName.TabIndex = 13;
      this.numericUpDown_needaffinitypoints.Location = new Point(117, 129);
      this.numericUpDown_needaffinitypoints.Maximum = new Decimal(new int[4]
      {
        -159383552,
        46653770,
        5421,
        0
      });
      this.numericUpDown_needaffinitypoints.Name = "numericUpDown_needaffinitypoints";
      this.numericUpDown_needaffinitypoints.Size = new Size(284, 20);
      this.numericUpDown_needaffinitypoints.TabIndex = 12;
      this.numericUpDown_needaffinityid.Location = new Point(85, 103);
      this.numericUpDown_needaffinityid.Maximum = new Decimal(new int[4]
      {
        1569325056,
        23283064,
        0,
        0
      });
      this.numericUpDown_needaffinityid.Name = "numericUpDown_needaffinityid";
      this.numericUpDown_needaffinityid.Size = new Size(62, 20);
      this.numericUpDown_needaffinityid.TabIndex = 8;
      this.numericUpDown_needaffinityid.ValueChanged += new EventHandler(this.numericUpDown_needaffinityid_ValueChanged);
      this.textBox_needaffinityName.Enabled = false;
      this.textBox_needaffinityName.Location = new Point(191, 102);
      this.textBox_needaffinityName.Name = "textBox_needaffinityName";
      this.textBox_needaffinityName.Size = new Size(212, 20);
      this.textBox_needaffinityName.TabIndex = 8;
      this.label7.AutoSize = true;
      this.label7.Location = new Point(6, 131);
      this.label7.Name = "label7";
      this.label7.Size = new Size(105, 13);
      this.label7.TabIndex = 11;
      this.label7.Text = "Need Affinity Points :";
      this.label6.AutoSize = true;
      this.label6.Location = new Point(6, 106);
      this.label6.Name = "label6";
      this.label6.Size = new Size(73, 13);
      this.label6.TabIndex = 10;
      this.label6.Text = "Need Affinity :";
      this.numericUpDown_needLevel.Location = new Point(85, 77);
      this.numericUpDown_needLevel.Maximum = new Decimal(new int[4]
      {
        100000000,
        0,
        0,
        0
      });
      this.numericUpDown_needLevel.Name = "numericUpDown_needLevel";
      this.numericUpDown_needLevel.Size = new Size(62, 20);
      this.numericUpDown_needLevel.TabIndex = 9;
      this.numericUpDown_needitemcount.Location = new Point(105, 51);
      this.numericUpDown_needitemcount.Maximum = new Decimal(new int[4]
      {
        276447232,
        23283,
        0,
        0
      });
      this.numericUpDown_needitemcount.Name = "numericUpDown_needitemcount";
      this.numericUpDown_needitemcount.Size = new Size(296, 20);
      this.numericUpDown_needitemcount.TabIndex = 8;
      this.numericUpDown_needitemID.Location = new Point(74, 19);
      this.numericUpDown_needitemID.Maximum = new Decimal(new int[4]
      {
        1410065408,
        2,
        0,
        0
      });
      this.numericUpDown_needitemID.Name = "numericUpDown_needitemID";
      this.numericUpDown_needitemID.Size = new Size(62, 20);
      this.numericUpDown_needitemID.TabIndex = 7;
      this.numericUpDown_needitemID.ValueChanged += new EventHandler(this.numericUpDown_needitemID_ValueChanged);
      this.label3.AutoSize = true;
      this.label3.Location = new Point(6, 21);
      this.label3.Name = "label3";
      this.label3.Size = new Size(62, 13);
      this.label3.TabIndex = 3;
      this.label3.Text = "Need Item :";
      this.label5.AutoSize = true;
      this.label5.Location = new Point(6, 79);
      this.label5.Name = "label5";
      this.label5.Size = new Size(68, 13);
      this.label5.TabIndex = 5;
      this.label5.Text = "Need Level :";
      this.label4.AutoSize = true;
      this.label4.Location = new Point(6, 53);
      this.label4.Name = "label4";
      this.label4.Size = new Size(93, 13);
      this.label4.TabIndex = 4;
      this.label4.Text = "Need Item Count :";
      this.groupBox1.Controls.Add((Control) this.button_iconsearch);
      this.groupBox1.Controls.Add((Control) this.pictureBox_Affinity);
      this.groupBox1.Controls.Add((Control) this.numericUpDown_ID);
      this.groupBox1.Controls.Add((Control) this.label2);
      this.groupBox1.Controls.Add((Control) this.textBox_name);
      this.groupBox1.Controls.Add((Control) this.label1);
      this.groupBox1.Location = new Point(214, 52);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(443, 61);
      this.groupBox1.TabIndex = 24;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Basic";
      this.numericUpDown_ID.Location = new Point(300, 19);
      this.numericUpDown_ID.Maximum = new Decimal(new int[4]
      {
        276447232,
        23283,
        0,
        0
      });
      this.numericUpDown_ID.Name = "numericUpDown_ID";
      this.numericUpDown_ID.Size = new Size(62, 20);
      this.numericUpDown_ID.TabIndex = 6;
      this.numericUpDown_ID.ValueChanged += new EventHandler(this.numericUpDown_ID_ValueChanged);
      this.label2.AutoSize = true;
      this.label2.Location = new Point(270, 21);
      this.label2.Name = "label2";
      this.label2.Size = new Size(24, 13);
      this.label2.TabIndex = 2;
      this.label2.Text = "ID :";
      this.textBox_name.Location = new Point(52, 19);
      this.textBox_name.Name = "textBox_name";
      this.textBox_name.Size = new Size(212, 20);
      this.textBox_name.TabIndex = 1;
      this.label1.AutoSize = true;
      this.label1.Location = new Point(5, 22);
      this.label1.Name = "label1";
      this.label1.Size = new Size(41, 13);
      this.label1.TabIndex = 0;
      this.label1.Text = "Name :";
      this.groupBox8.Controls.Add((Control) this.textBox22);
      this.groupBox8.Controls.Add((Control) this.label13);
      this.groupBox8.Location = new Point(12, 38);
      this.groupBox8.Name = "groupBox8";
      this.groupBox8.Size = new Size(196, 53);
      this.groupBox8.TabIndex = 31;
      this.groupBox8.TabStop = false;
      this.groupBox8.Text = "Search";
      this.textBox22.BorderStyle = BorderStyle.FixedSingle;
      this.textBox22.Location = new Point(43, 22);
      this.textBox22.Name = "textBox22";
      this.textBox22.Size = new Size(147, 20);
      this.textBox22.TabIndex = 1;
      this.textBox22.TextChanged += new EventHandler(this.textBox22_TextChanged);
      this.label13.AutoSize = true;
      this.label13.Location = new Point(6, 24);
      this.label13.Name = "label13";
      this.label13.Size = new Size(31, 13);
      this.label13.TabIndex = 0;
      this.label13.Text = "Text:";
      this.button2.Enabled = false;
      this.button2.FlatStyle = FlatStyle.Flat;
      this.button2.Location = new Point(71, 550);
      this.button2.Name = "button2";
      this.button2.Size = new Size(50, 28);
      this.button2.TabIndex = 38;
      this.button2.Text = "Delete";
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.button1.Enabled = false;
      this.button1.FlatStyle = FlatStyle.Flat;
      this.button1.Location = new Point(12, 550);
      this.button1.Name = "button1";
      this.button1.Size = new Size(48, 28);
      this.button1.TabIndex = 37;
      this.button1.Text = "Add";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.button3.Enabled = false;
      this.button3.FlatStyle = FlatStyle.Flat;
      this.button3.Location = new Point(132, 550);
      this.button3.Name = "button3";
      this.button3.Size = new Size(55, 28);
      this.button3.TabIndex = 39;
      this.button3.Text = "Save";
      this.button3.UseVisualStyleBackColor = true;
      this.button3.Click += new EventHandler(this.button3_Click);
      this.groupBox7.Controls.Add((Control) this.dataGridView_getAff_Quest);
      this.groupBox7.Controls.Add((Control) this.button5);
      this.groupBox7.Controls.Add((Control) this.button6);
      this.groupBox7.Location = new Point(663, 428);
      this.groupBox7.Name = "groupBox7";
      this.groupBox7.Size = new Size(443, 195);
      this.groupBox7.TabIndex = 45;
      this.groupBox7.TabStop = false;
      this.groupBox7.Text = "Get Affinity From Quest";
      this.dataGridView_getAff_Quest.AllowUserToAddRows = false;
      this.dataGridView_getAff_Quest.AllowUserToDeleteRows = false;
      this.dataGridView_getAff_Quest.AllowUserToResizeColumns = false;
      this.dataGridView_getAff_Quest.AllowUserToResizeRows = false;
      this.dataGridView_getAff_Quest.BackgroundColor = SystemColors.Control;
      this.dataGridView_getAff_Quest.ColumnHeadersHeight = 21;
      this.dataGridView_getAff_Quest.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.DisableResizing;
      this.dataGridView_getAff_Quest.Columns.AddRange((DataGridViewColumn) this.dataGridViewTextBoxColumn7, (DataGridViewColumn) this.dataGridViewTextBoxColumn8, (DataGridViewColumn) this.dataGridViewTextBoxColumn9);
      this.dataGridView_getAff_Quest.Dock = DockStyle.Top;
      this.dataGridView_getAff_Quest.Location = new Point(3, 16);
      this.dataGridView_getAff_Quest.MultiSelect = false;
      this.dataGridView_getAff_Quest.Name = "dataGridView_getAff_Quest";
      this.dataGridView_getAff_Quest.RowHeadersVisible = false;
      this.dataGridView_getAff_Quest.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
      this.dataGridView_getAff_Quest.Size = new Size(437, 150);
      this.dataGridView_getAff_Quest.TabIndex = 15;
      this.dataGridViewTextBoxColumn7.HeaderText = "Quest ID";
      this.dataGridViewTextBoxColumn7.Name = "dataGridViewTextBoxColumn7";
      this.dataGridViewTextBoxColumn7.ReadOnly = true;
      this.dataGridViewTextBoxColumn7.Width = 50;
      this.dataGridViewTextBoxColumn8.HeaderText = "Monster Name";
      this.dataGridViewTextBoxColumn8.Name = "dataGridViewTextBoxColumn8";
      this.dataGridViewTextBoxColumn8.ReadOnly = true;
      this.dataGridViewTextBoxColumn8.Width = 200;
      this.dataGridViewTextBoxColumn9.HeaderText = "Affinity Points";
      this.dataGridViewTextBoxColumn9.Name = "dataGridViewTextBoxColumn9";
      this.dataGridViewTextBoxColumn9.Width = 90;
      this.button5.Enabled = false;
      this.button5.Location = new Point(87, 172);
      this.button5.Name = "button5";
      this.button5.Size = new Size(75, 23);
      this.button5.TabIndex = 12;
      this.button5.Text = "Remove";
      this.button5.UseVisualStyleBackColor = true;
      this.button5.Click += new EventHandler(this.button5_Click);
      this.button6.Enabled = false;
      this.button6.Location = new Point(6, 172);
      this.button6.Name = "button6";
      this.button6.Size = new Size(75, 23);
      this.button6.TabIndex = 11;
      this.button6.Text = "Add";
      this.button6.UseVisualStyleBackColor = true;
      this.button6.Click += new EventHandler(this.button6_Click);
      this.groupBox6.Controls.Add((Control) this.dataGridView_GetAff_Monster);
      this.groupBox6.Controls.Add((Control) this.button4);
      this.groupBox6.Controls.Add((Control) this.button8);
      this.groupBox6.Location = new Point(663, 218);
      this.groupBox6.Name = "groupBox6";
      this.groupBox6.Size = new Size(443, 204);
      this.groupBox6.TabIndex = 44;
      this.groupBox6.TabStop = false;
      this.groupBox6.Text = "Get Affinity From Monster";
      this.dataGridView_GetAff_Monster.AllowUserToAddRows = false;
      this.dataGridView_GetAff_Monster.AllowUserToDeleteRows = false;
      this.dataGridView_GetAff_Monster.AllowUserToResizeColumns = false;
      this.dataGridView_GetAff_Monster.AllowUserToResizeRows = false;
      this.dataGridView_GetAff_Monster.BackgroundColor = SystemColors.Control;
      this.dataGridView_GetAff_Monster.ColumnHeadersHeight = 21;
      this.dataGridView_GetAff_Monster.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.DisableResizing;
      this.dataGridView_GetAff_Monster.Columns.AddRange((DataGridViewColumn) this.dataGridViewTextBoxColumn4, (DataGridViewColumn) this.dataGridViewTextBoxColumn5, (DataGridViewColumn) this.dataGridViewTextBoxColumn6);
      this.dataGridView_GetAff_Monster.Dock = DockStyle.Top;
      this.dataGridView_GetAff_Monster.Location = new Point(3, 16);
      this.dataGridView_GetAff_Monster.MultiSelect = false;
      this.dataGridView_GetAff_Monster.Name = "dataGridView_GetAff_Monster";
      this.dataGridView_GetAff_Monster.RowHeadersVisible = false;
      this.dataGridView_GetAff_Monster.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
      this.dataGridView_GetAff_Monster.Size = new Size(437, 150);
      this.dataGridView_GetAff_Monster.TabIndex = 15;
      this.dataGridViewTextBoxColumn4.HeaderText = "Monster ID";
      this.dataGridViewTextBoxColumn4.Name = "dataGridViewTextBoxColumn4";
      this.dataGridViewTextBoxColumn4.ReadOnly = true;
      this.dataGridViewTextBoxColumn4.Width = 50;
      this.dataGridViewTextBoxColumn5.HeaderText = "Monster Name";
      this.dataGridViewTextBoxColumn5.Name = "dataGridViewTextBoxColumn5";
      this.dataGridViewTextBoxColumn5.ReadOnly = true;
      this.dataGridViewTextBoxColumn5.Width = 200;
      this.dataGridViewTextBoxColumn6.HeaderText = "Affinity Points";
      this.dataGridViewTextBoxColumn6.Name = "dataGridViewTextBoxColumn6";
      this.dataGridViewTextBoxColumn6.Width = 90;
      this.button4.Enabled = false;
      this.button4.Location = new Point(87, 172);
      this.button4.Name = "button4";
      this.button4.Size = new Size(75, 23);
      this.button4.TabIndex = 12;
      this.button4.Text = "Remove";
      this.button4.UseVisualStyleBackColor = true;
      this.button4.Click += new EventHandler(this.button4_Click);
      this.button8.Enabled = false;
      this.button8.Location = new Point(6, 172);
      this.button8.Name = "button8";
      this.button8.Size = new Size(75, 23);
      this.button8.TabIndex = 11;
      this.button8.Text = "Add";
      this.button8.UseVisualStyleBackColor = true;
      this.button8.Click += new EventHandler(this.button8_Click);
      this.groupBox5.Controls.Add((Control) this.dataGridView_GetAff_Item);
      this.groupBox5.Controls.Add((Control) this.button9);
      this.groupBox5.Controls.Add((Control) this.b_affitem);
      this.groupBox5.Location = new Point(663, 8);
      this.groupBox5.Name = "groupBox5";
      this.groupBox5.Size = new Size(443, 204);
      this.groupBox5.TabIndex = 43;
      this.groupBox5.TabStop = false;
      this.groupBox5.Text = "Get Affinity From Item";
      this.dataGridView_GetAff_Item.AllowUserToAddRows = false;
      this.dataGridView_GetAff_Item.AllowUserToDeleteRows = false;
      this.dataGridView_GetAff_Item.AllowUserToResizeColumns = false;
      this.dataGridView_GetAff_Item.AllowUserToResizeRows = false;
      this.dataGridView_GetAff_Item.BackgroundColor = SystemColors.Control;
      this.dataGridView_GetAff_Item.ColumnHeadersHeight = 21;
      this.dataGridView_GetAff_Item.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.DisableResizing;
      this.dataGridView_GetAff_Item.Columns.AddRange((DataGridViewColumn) this.dataGridViewImageColumn1, (DataGridViewColumn) this.dataGridViewTextBoxColumn1, (DataGridViewColumn) this.dataGridViewTextBoxColumn2, (DataGridViewColumn) this.dataGridViewTextBoxColumn3);
      this.dataGridView_GetAff_Item.Dock = DockStyle.Top;
      this.dataGridView_GetAff_Item.Location = new Point(3, 16);
      this.dataGridView_GetAff_Item.MultiSelect = false;
      this.dataGridView_GetAff_Item.Name = "dataGridView_GetAff_Item";
      this.dataGridView_GetAff_Item.RowHeadersVisible = false;
      this.dataGridView_GetAff_Item.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
      this.dataGridView_GetAff_Item.Size = new Size(437, 150);
      this.dataGridView_GetAff_Item.TabIndex = 15;
      this.dataGridViewImageColumn1.HeaderText = "";
      this.dataGridViewImageColumn1.Name = "dataGridViewImageColumn1";
      this.dataGridViewImageColumn1.ReadOnly = true;
      this.dataGridViewImageColumn1.Width = 35;
      this.dataGridViewTextBoxColumn1.HeaderText = "Item ID";
      this.dataGridViewTextBoxColumn1.Name = "dataGridViewTextBoxColumn1";
      this.dataGridViewTextBoxColumn1.ReadOnly = true;
      this.dataGridViewTextBoxColumn1.Width = 50;
      this.dataGridViewTextBoxColumn2.HeaderText = "Item Name";
      this.dataGridViewTextBoxColumn2.Name = "dataGridViewTextBoxColumn2";
      this.dataGridViewTextBoxColumn2.ReadOnly = true;
      this.dataGridViewTextBoxColumn2.Width = 200;
      this.dataGridViewTextBoxColumn3.HeaderText = "Affinity Points";
      this.dataGridViewTextBoxColumn3.Name = "dataGridViewTextBoxColumn3";
      this.dataGridViewTextBoxColumn3.Width = 90;
      this.button9.Enabled = false;
      this.button9.Location = new Point(87, 172);
      this.button9.Name = "button9";
      this.button9.Size = new Size(75, 23);
      this.button9.TabIndex = 12;
      this.button9.Text = "Remove";
      this.button9.UseVisualStyleBackColor = true;
      this.button9.Click += new EventHandler(this.button9_Click);
      this.b_affitem.Enabled = false;
      this.b_affitem.Location = new Point(6, 172);
      this.b_affitem.Name = "b_affitem";
      this.b_affitem.Size = new Size(75, 23);
      this.b_affitem.TabIndex = 11;
      this.b_affitem.Text = "Add";
      this.b_affitem.UseVisualStyleBackColor = true;
      this.b_affitem.Click += new EventHandler(this.b_affitem_Click);
      this.groupBox4.Controls.Add((Control) this.dataGridView_affinity_rewardItem);
      this.groupBox4.Controls.Add((Control) this.button_removeaffinityitemReward);
      this.groupBox4.Controls.Add((Control) this.button_addaffinityitemReward);
      this.groupBox4.Location = new Point(214, 428);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Size = new Size(443, 195);
      this.groupBox4.TabIndex = 42;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "Affinity Reward";
      this.dataGridView_affinity_rewardItem.AllowUserToAddRows = false;
      this.dataGridView_affinity_rewardItem.AllowUserToDeleteRows = false;
      this.dataGridView_affinity_rewardItem.AllowUserToResizeColumns = false;
      this.dataGridView_affinity_rewardItem.AllowUserToResizeRows = false;
      this.dataGridView_affinity_rewardItem.BackgroundColor = SystemColors.Control;
      this.dataGridView_affinity_rewardItem.ColumnHeadersHeight = 21;
      this.dataGridView_affinity_rewardItem.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.DisableResizing;
      this.dataGridView_affinity_rewardItem.Columns.AddRange((DataGridViewColumn) this.image, (DataGridViewColumn) this.Column1, (DataGridViewColumn) this.Column2, (DataGridViewColumn) this.Column3);
      this.dataGridView_affinity_rewardItem.Dock = DockStyle.Top;
      this.dataGridView_affinity_rewardItem.Location = new Point(3, 16);
      this.dataGridView_affinity_rewardItem.MultiSelect = false;
      this.dataGridView_affinity_rewardItem.Name = "dataGridView_affinity_rewardItem";
      this.dataGridView_affinity_rewardItem.RowHeadersVisible = false;
      this.dataGridView_affinity_rewardItem.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
      this.dataGridView_affinity_rewardItem.Size = new Size(437, 150);
      this.dataGridView_affinity_rewardItem.TabIndex = 15;
      this.image.HeaderText = "";
      this.image.Name = "image";
      this.image.ReadOnly = true;
      this.image.Width = 35;
      this.Column1.HeaderText = "Item ID";
      this.Column1.Name = "Column1";
      this.Column1.ReadOnly = true;
      this.Column1.Width = 50;
      this.Column2.HeaderText = "Item Name";
      this.Column2.Name = "Column2";
      this.Column2.ReadOnly = true;
      this.Column2.Width = 200;
      this.Column3.HeaderText = "Affinity Points";
      this.Column3.Name = "Column3";
      this.Column3.Width = 90;
      this.button_removeaffinityitemReward.Enabled = false;
      this.button_removeaffinityitemReward.Location = new Point(87, 172);
      this.button_removeaffinityitemReward.Name = "button_removeaffinityitemReward";
      this.button_removeaffinityitemReward.Size = new Size(75, 23);
      this.button_removeaffinityitemReward.TabIndex = 12;
      this.button_removeaffinityitemReward.Text = "Remove";
      this.button_removeaffinityitemReward.UseVisualStyleBackColor = true;
      this.button_removeaffinityitemReward.Click += new EventHandler(this.button_removeaffinityitemReward_Click);
      this.button_addaffinityitemReward.Enabled = false;
      this.button_addaffinityitemReward.Location = new Point(6, 172);
      this.button_addaffinityitemReward.Name = "button_addaffinityitemReward";
      this.button_addaffinityitemReward.Size = new Size(75, 23);
      this.button_addaffinityitemReward.TabIndex = 11;
      this.button_addaffinityitemReward.Text = "Add";
      this.button_addaffinityitemReward.UseVisualStyleBackColor = true;
      this.button_addaffinityitemReward.Click += new EventHandler(this.button_addaffinityitemReward_Click);
      this.groupBox3.Controls.Add((Control) this.button_removenpc);
      this.groupBox3.Controls.Add((Control) this.dataGridView_npc);
      this.groupBox3.Controls.Add((Control) this.button_addnpc);
      this.groupBox3.Location = new Point(214, 286);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Size = new Size(443, 136);
      this.groupBox3.TabIndex = 41;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "Affinity NPC's";
      this.button_removenpc.Enabled = false;
      this.button_removenpc.Location = new Point(87, 107);
      this.button_removenpc.Name = "button_removenpc";
      this.button_removenpc.Size = new Size(75, 23);
      this.button_removenpc.TabIndex = 10;
      this.button_removenpc.Text = "Remove";
      this.button_removenpc.UseVisualStyleBackColor = true;
      this.button_removenpc.Click += new EventHandler(this.button_removenpc_Click);
      this.dataGridView_npc.AllowUserToAddRows = false;
      this.dataGridView_npc.AllowUserToDeleteRows = false;
      this.dataGridView_npc.AllowUserToResizeColumns = false;
      this.dataGridView_npc.AllowUserToResizeRows = false;
      this.dataGridView_npc.BackgroundColor = SystemColors.Control;
      this.dataGridView_npc.ColumnHeadersHeight = 21;
      this.dataGridView_npc.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.DisableResizing;
      this.dataGridView_npc.Columns.AddRange((DataGridViewColumn) this.Npcid, (DataGridViewColumn) this.npcname, (DataGridViewColumn) this.Flag, (DataGridViewColumn) this.Stringid, (DataGridViewColumn) this.Column6, (DataGridViewColumn) this.Column4, (DataGridViewColumn) this.Column5);
      this.dataGridView_npc.Dock = DockStyle.Top;
      this.dataGridView_npc.Location = new Point(3, 16);
      this.dataGridView_npc.MultiSelect = false;
      this.dataGridView_npc.Name = "dataGridView_npc";
      this.dataGridView_npc.RowHeadersVisible = false;
      this.dataGridView_npc.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
      this.dataGridView_npc.Size = new Size(437, 85);
      this.dataGridView_npc.TabIndex = 14;
      this.Npcid.HeaderText = "NPC ID";
      this.Npcid.Name = "Npcid";
      this.Npcid.ReadOnly = true;
      this.Npcid.Width = 50;
      this.npcname.HeaderText = "Npc Name";
      this.npcname.Name = "npcname";
      this.npcname.ReadOnly = true;
      this.npcname.Width = 150;
      this.Flag.HeaderText = "Flag";
      this.Flag.Name = "Flag";
      this.Flag.Width = 50;
      this.Stringid.HeaderText = "String ID";
      this.Stringid.Name = "Stringid";
      this.Stringid.Width = 80;
      this.Column6.HeaderText = "String Name";
      this.Column6.Name = "Column6";
      this.Column4.HeaderText = "Point";
      this.Column4.Name = "Column4";
      this.Column4.Width = 50;
      this.Column5.HeaderText = "Enable";
      this.Column5.Name = "Column5";
      this.Column5.Width = 50;
      this.button_addnpc.Enabled = false;
      this.button_addnpc.Location = new Point(6, 107);
      this.button_addnpc.Name = "button_addnpc";
      this.button_addnpc.Size = new Size(75, 23);
      this.button_addnpc.TabIndex = 9;
      this.button_addnpc.Text = "Add";
      this.button_addnpc.UseVisualStyleBackColor = true;
      this.button_addnpc.Click += new EventHandler(this.button_addnpc_Click);
      this.button12.BackColor = Color.Gold;
      this.button12.FlatStyle = FlatStyle.Flat;
      this.button12.Image = (Image) Resources.control_add_blue;
      this.button12.ImageAlign = ContentAlignment.MiddleLeft;
      this.button12.Location = new Point(326, 19);
      this.button12.Name = "button12";
      this.button12.Size = new Size(88, 27);
      this.button12.TabIndex = 48;
      this.button12.Text = "     Export ";
      this.button12.UseVisualStyleBackColor = false;
      this.button12.Click += new EventHandler(this.button12_Click);
      this.button11.BackColor = Color.Plum;
      this.button11.FlatStyle = FlatStyle.Flat;
      this.button11.Image = (Image) Resources.control_add_blue;
      this.button11.ImageAlign = ContentAlignment.MiddleLeft;
      this.button11.Location = new Point(420, 19);
      this.button11.Name = "button11";
      this.button11.Size = new Size(126, 27);
      this.button11.TabIndex = 47;
      this.button11.Text = "     Get All From DB ";
      this.button11.UseVisualStyleBackColor = false;
      this.button11.Click += new EventHandler(this.button11_Click);
      this.button10.BackColor = Color.LightCyan;
      this.button10.FlatStyle = FlatStyle.Flat;
      this.button10.Image = (Image) Resources._08;
      this.button10.ImageAlign = ContentAlignment.MiddleLeft;
      this.button10.Location = new Point(553, 19);
      this.button10.Name = "button10";
      this.button10.Size = new Size(92, 27);
      this.button10.TabIndex = 46;
      this.button10.Text = "   DB Editor";
      this.button10.UseVisualStyleBackColor = false;
      this.button10.Click += new EventHandler(this.button10_Click);
      this.button_itemsearch.BackgroundImage = (Image) Resources.search;
      this.button_itemsearch.BackgroundImageLayout = ImageLayout.Zoom;
      this.button_itemsearch.Enabled = false;
      this.button_itemsearch.FlatAppearance.BorderSize = 0;
      this.button_itemsearch.FlatStyle = FlatStyle.Flat;
      this.button_itemsearch.Location = new Point(409, 16);
      this.button_itemsearch.Name = "button_itemsearch";
      this.button_itemsearch.Size = new Size(22, 23);
      this.button_itemsearch.TabIndex = 15;
      this.button_itemsearch.UseVisualStyleBackColor = true;
      this.button_itemsearch.Click += new EventHandler(this.button_itemsearch_Click);
      this.button7.BackgroundImage = (Image) Resources.search;
      this.button7.BackgroundImageLayout = ImageLayout.Zoom;
      this.button7.Enabled = false;
      this.button7.FlatAppearance.BorderSize = 0;
      this.button7.FlatStyle = FlatStyle.Flat;
      this.button7.Location = new Point(409, 101);
      this.button7.Name = "button7";
      this.button7.Size = new Size(22, 23);
      this.button7.TabIndex = 14;
      this.button7.UseVisualStyleBackColor = true;
      this.button7.Click += new EventHandler(this.button7_Click);
      this.pictureBox_needaffinity.Location = new Point(153, 94);
      this.pictureBox_needaffinity.Name = "pictureBox_needaffinity";
      this.pictureBox_needaffinity.Size = new Size(32, 32);
      this.pictureBox_needaffinity.TabIndex = 8;
      this.pictureBox_needaffinity.TabStop = false;
      this.pictureBox_needItemID.Location = new Point(142, 13);
      this.pictureBox_needItemID.Name = "pictureBox_needItemID";
      this.pictureBox_needItemID.Size = new Size(32, 32);
      this.pictureBox_needItemID.TabIndex = 8;
      this.pictureBox_needItemID.TabStop = false;
      this.button_iconsearch.BackgroundImage = (Image) Resources.search;
      this.button_iconsearch.BackgroundImageLayout = ImageLayout.Stretch;
      this.button_iconsearch.FlatAppearance.BorderSize = 0;
      this.button_iconsearch.FlatStyle = FlatStyle.Flat;
      this.button_iconsearch.Location = new Point(407, 16);
      this.button_iconsearch.Name = "button_iconsearch";
      this.button_iconsearch.Size = new Size(22, 23);
      this.button_iconsearch.TabIndex = 15;
      this.button_iconsearch.UseVisualStyleBackColor = true;
      this.button_iconsearch.Click += new EventHandler(this.button_iconsearch_Click);
      this.pictureBox_Affinity.Location = new Point(369, 13);
      this.pictureBox_Affinity.Name = "pictureBox_Affinity";
      this.pictureBox_Affinity.Size = new Size(32, 32);
      this.pictureBox_Affinity.TabIndex = 7;
      this.pictureBox_Affinity.TabStop = false;
      this.Open.BackgroundImageLayout = ImageLayout.Center;
      this.Open.DisplayStyle = ToolStripItemDisplayStyle.Image;
      this.Open.Enabled = false;
      this.Open.Image = (Image) Resources.Folder;
      this.Open.ImageTransparentColor = Color.Magenta;
      this.Open.Name = "Open";
      this.Open.Size = new Size(23, 22);
      this.Open.Text = "Open";
      this.Open.Click += new EventHandler(this.Open_Click);
      this.Save.BackgroundImageLayout = ImageLayout.Center;
      this.Save.DisplayStyle = ToolStripItemDisplayStyle.Image;
      this.Save.Image = (Image) Resources.Save;
      this.Save.ImageTransparentColor = Color.Magenta;
      this.Save.Name = "Save";
      this.Save.Size = new Size(23, 22);
      this.Save.Text = "Save";
      this.Save.Click += new EventHandler(this.Save_Click);
      this.Saveas.BackgroundImageLayout = ImageLayout.Center;
      this.Saveas.DisplayStyle = ToolStripItemDisplayStyle.Image;
      this.Saveas.Image = (Image) Resources.Save_as_icon;
      this.Saveas.ImageTransparentColor = Color.Magenta;
      this.Saveas.Name = "Saveas";
      this.Saveas.Size = new Size(23, 22);
      this.Saveas.Tag = (object) "bla";
      this.Saveas.Text = "Save As";
      this.Saveas.Click += new EventHandler(this.Saveas_Click);
      this.toolStripSplitButton1.DisplayStyle = ToolStripItemDisplayStyle.Image;
      this.toolStripSplitButton1.DropDownItems.AddRange(new ToolStripItem[2]
      {
        (ToolStripItem) this.getAllFromDBToolStripMenuItem,
        (ToolStripItem) this.saveAllToDBToolStripMenuItem
      });
      this.toolStripSplitButton1.Image = (Image) componentResourceManager.GetObject("toolStripSplitButton1.Image");
      this.toolStripSplitButton1.ImageTransparentColor = Color.Magenta;
      this.toolStripSplitButton1.Name = "toolStripSplitButton1";
      this.toolStripSplitButton1.Size = new Size(32, 22);
      this.toolStripSplitButton1.Text = "toolStripSplitButton1";
      this.getAllFromDBToolStripMenuItem.Name = "getAllFromDBToolStripMenuItem";
      this.getAllFromDBToolStripMenuItem.Size = new Size(158, 22);
      this.getAllFromDBToolStripMenuItem.Text = "Get All From DB";
      this.getAllFromDBToolStripMenuItem.Click += new EventHandler(this.getAllFromDBToolStripMenuItem_Click);
      this.saveAllToDBToolStripMenuItem.Enabled = false;
      this.saveAllToDBToolStripMenuItem.Name = "saveAllToDBToolStripMenuItem";
      this.saveAllToDBToolStripMenuItem.Size = new Size(158, 22);
      this.saveAllToDBToolStripMenuItem.Text = "Save All To DB";
      this.saveAllToDBToolStripMenuItem.Click += new EventHandler(this.saveAllToDBToolStripMenuItem_Click);
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(1109, 625);
      this.Controls.Add((Control) this.button12);
      this.Controls.Add((Control) this.button11);
      this.Controls.Add((Control) this.button10);
      this.Controls.Add((Control) this.groupBox7);
      this.Controls.Add((Control) this.groupBox6);
      this.Controls.Add((Control) this.groupBox5);
      this.Controls.Add((Control) this.groupBox4);
      this.Controls.Add((Control) this.groupBox3);
      this.Controls.Add((Control) this.button3);
      this.Controls.Add((Control) this.button2);
      this.Controls.Add((Control) this.button1);
      this.Controls.Add((Control) this.groupBox8);
      this.Controls.Add((Control) this.groupBox2);
      this.Controls.Add((Control) this.groupBox1);
      this.Controls.Add((Control) this.lbAffinity);
      this.Controls.Add((Control) this.toolStrip1);
      this.Name = nameof (Affinity_EP4);
      this.Text = nameof (Affinity_EP4);
      this.Load += new EventHandler(this.Affinity_EP4_Load);
      this.toolStrip1.ResumeLayout(false);
      this.toolStrip1.PerformLayout();
      this.groupBox2.ResumeLayout(false);
      this.groupBox2.PerformLayout();
      this.numericUpDown_needaffinitypoints.EndInit();
      this.numericUpDown_needaffinityid.EndInit();
      this.numericUpDown_needLevel.EndInit();
      this.numericUpDown_needitemcount.EndInit();
      this.numericUpDown_needitemID.EndInit();
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.numericUpDown_ID.EndInit();
      this.groupBox8.ResumeLayout(false);
      this.groupBox8.PerformLayout();
      this.groupBox7.ResumeLayout(false);
      ((ISupportInitialize) this.dataGridView_getAff_Quest).EndInit();
      this.groupBox6.ResumeLayout(false);
      ((ISupportInitialize) this.dataGridView_GetAff_Monster).EndInit();
      this.groupBox5.ResumeLayout(false);
      ((ISupportInitialize) this.dataGridView_GetAff_Item).EndInit();
      this.groupBox4.ResumeLayout(false);
      ((ISupportInitialize) this.dataGridView_affinity_rewardItem).EndInit();
      this.groupBox3.ResumeLayout(false);
      ((ISupportInitialize) this.dataGridView_npc).EndInit();
      ((ISupportInitialize) this.pictureBox_needaffinity).EndInit();
      ((ISupportInitialize) this.pictureBox_needItemID).EndInit();
      ((ISupportInitialize) this.pictureBox_Affinity).EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
