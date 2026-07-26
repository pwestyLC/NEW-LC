// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.EventDrop.EventDropTool
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
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.EventDrop
{
  public class EventDropTool : Form
  {
    public static Connection connection = new Connection();
    private string Host = EventDropTool.connection.Settings.SqlHost;
    private string User = EventDropTool.connection.Settings.SqlUser;
    private string Password = EventDropTool.connection.Settings.SqlPassword;
    private string Database = EventDropTool.connection.Settings.SqlDatabase;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    public string _ClientPath = EventDropTool.connection.Settings.ClientPath;
    public string rowName = nameof (a_drop_idx);
    public List<string> MenuList = new List<string>();
    public string[] menuArray = new string[2]
    {
      nameof (a_drop_idx),
      "a_desc"
    };
    private DataTable table = new DataTable();
    private DataTable table2 = new DataTable();
    private MySqlCommand command;
    private MySqlDataAdapter adapter;
    private BindingManagerBase managerBase;
    private BindingManagerBase managerBase2;
    private MySqlCommandBuilder builder;
    private IContainer components = (IContainer) null;
    private MenuStrip menuStrip1;
    private ToolStripMenuItem fileToolStripMenuItem;
    private ToolStripMenuItem importFromDatabaseToolStripMenuItem;
    private ToolStripMenuItem saveToolStripMenuItem;
    private ToolStripMenuItem extraToolStripMenuItem;
    private GroupBox groupBox2;
    private GroupBox groupBox1;
    private TextBox textBox1;
    private GroupBox groupBox4;
    private DataGridView dgItems;
    private TextBox textBox2;
    private TextBox textBox3;
    private TextBox textBox4;
    private TextBox textBox5;
    private GroupBox groupBox3;
    private TextBox textBox7;
    private Label label2;
    private TextBox textBox6;
    private Label label1;
    private CheckedListBox checkedListBox1;
    private TextBox textBox8;
    private GroupBox groupBox21;
    private CheckedListBox checkedListBox2;
    private TextBox textBox9;
    private GroupBox groupBox5;
    private Label label4;
    private Button button4;
    private TextBox textBox26;
    private Label label15;
    private TextBox textBox24;
    private TextBox textBox11;
    private Label label6;
    private TextBox textBox10;
    private Label label5;
    private TextBox textBox25;
    private Label label16;
    private GroupBox groupBox7;
    private TextBox textBox14;
    private Button button12;
    private Button button9;
    private Button button6;
    private Button button17;
    private Button button18;
    private Button button19;
    private TextBox textBox15;
    private TextBox textBox16;
    private CheckBox checkBox1;
    private PictureBox pictureBox7;
    private Label label9;
    private Label label12;
    private Label label11;
    private Label label10;
    private TextBox textBox17;
    private GroupBox groupBox9;
    private TextBox textBox21;
    private Label label17;
    private GroupBox groupBox8;
    private TextBox textBox20;
    private Label label14;
    private TextBox textBox19;
    private Label label13;
    private TextBox textBox18;
    private GroupBox groupBox10;
    private TextBox textBox22;
    private Label label18;
    private GroupBox groupBox11;
    private TextBox textBox23;
    private Label label19;
    private TextBox textBox27;
    private Label label20;
    private Button button3;
    private Button button1;
    private Button button2;
    private GroupBox groupBox12;
    private DataGridView dataGridView1;
    private DataGridViewTextBoxColumn Level1;
    private DataGridViewTextBoxColumn Level2;
    private DataGridViewTextBoxColumn ProbL;
    private Label label22;
    private TextBox textBox29;
    private TextBox textBox28;
    private Label label21;
    private Button button8;
    private Button button7;
    private Button button5;
    private TextBox textBox30;
    private Label label23;
    private Button button15;
    private Label label3;
    private TextBox textBox12;
    private DataGridView ItemDropHead;
    private DataGridViewTextBoxColumn drop_idx;
    private DataGridViewTextBoxColumn Desc;
    private DataGridViewTextBoxColumn drop_type;
    private DataGridViewTextBoxColumn level_min;
    private DataGridViewTextBoxColumn level_max;
    private DataGridViewTextBoxColumn prob;
    private DataGridViewTextBoxColumn prob_level;
    private DataGridViewTextBoxColumn npc_type_party;
    private DataGridViewTextBoxColumn npc_type_boss;
    private DataGridViewTextBoxColumn npc;
    private DataGridViewTextBoxColumn level_section;
    private DataGridViewImageColumn Icon;
    private DataGridViewTextBoxColumn PrimaryKey;
    private DataGridViewTextBoxColumn a_drop_idx;
    private DataGridViewTextBoxColumn a_item_idx;
    private DataGridViewTextBoxColumn ItemName;
    private DataGridViewTextBoxColumn a_plus;
    private DataGridViewTextBoxColumn a_flag;
    private DataGridViewTextBoxColumn a_count;
    private DataGridViewTextBoxColumn a_prob;
    private DataGridViewTextBoxColumn JobFlag;
    private Label label8;

    private void IniRead()
    {
      IniFile iniFile = new IniFile(Application.StartupPath + "\\Config\\Settings.cfg");
      this.textBox2.Text = iniFile.IniReadValue("## MYSQL", "SQL_HOST");
      this.textBox3.Text = iniFile.IniReadValue("## MYSQL", "SQL_USER");
      this.textBox4.Text = iniFile.IniReadValue("## MYSQL", "SQL_PASSWORD");
      this.textBox5.Text = iniFile.IniReadValue("## MYSQL", "SQL_DATABASE");
    }

    public EventDropTool()
    {
      this.InitializeComponent();
      this.MakeList();
    }

        public void MakeList()
        {
            this.ItemDropHead.Rows.Clear();

            string query = "SELECT * FROM t_drop_item_head ORDER BY a_drop_idx ASC";

            using (var connection = new MySqlConnection(
                "datasource=" + this.Host +
                ";Port=3306;User ID=" + this.User +
                ";Password=" + this.Password +
                ";Database=" + this.Database +
                ";Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;"))
            {
                connection.Open();

                using (var command = new MySqlCommand(query, connection))
                using (var reader = command.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        int dropIdx = reader.GetInt32("a_drop_idx");
                        string desc = reader["a_desc"].ToString();
                        int dropType = reader.GetInt32("a_drop_type");
                        int levelMini = reader.GetInt32("a_level_mini");
                        int levelMaxi = reader.GetInt32("a_level_maxi");
                        int prob = reader.GetInt32("a_prob");
                        int probLevel = reader.GetInt32("a_prob_level");
                        int npcTypeParty = reader.GetInt32("a_npc_type_party");
                        int npcTypeBoss = reader.GetInt32("a_npc_type_boss");
                        int npcIdx = 0;
                        if (int.TryParse(reader["a_npc"].ToString(), out int parsedNpc))
                            npcIdx = parsedNpc;
                        int levelSection = 0;
                        if (int.TryParse(reader["a_level_section"]?.ToString(), out int parsedSection))
                            levelSection = parsedSection;

                        this.ItemDropHead.Rows.Add(
                            dropIdx,
                            desc,
                            dropType,
                            levelMini,
                            levelMaxi,
                            prob,
                            probLevel,
                            npcTypeParty,
                            npcTypeBoss,
                            npcIdx,
                            levelSection
                        );
                    }
                }
            }
        }


        private void ItemDropHead_CellClick(object sender, DataGridViewCellEventArgs e)
    {
      if (e.RowIndex < 0)
        return;
      DataGridViewRow row = this.ItemDropHead.Rows[e.RowIndex];
      this.textBox6.Text = row.Cells["drop_idx"].Value.ToString();
      this.textBox7.Text = row.Cells["Desc"].Value.ToString();
      this.textBox8.Text = row.Cells["drop_type"].Value.ToString();
      this.textBox18.Text = row.Cells["level_min"].Value.ToString();
      this.textBox19.Text = row.Cells["level_max"].Value.ToString();
      this.textBox22.Text = row.Cells["prob"].Value.ToString();
      this.textBox20.Text = row.Cells["prob_level"].Value.ToString();
      this.textBox23.Text = row.Cells["npc_type_party"].Value.ToString();
      this.textBox27.Text = row.Cells["npc_type_boss"].Value.ToString();
      this.textBox21.Text = row.Cells["npc"].Value.ToString();
      this.LoadMisc();
      this.FillGrid();
    }

    private void ShowRandom(int flag)
    {
      for (int index = 0; index < this.checkedListBox1.Items.Count; ++index)
      {
        if (flag != 0)
          this.checkedListBox1.SetItemChecked(index, true);
        else
          this.checkedListBox1.SetItemChecked(index, false);
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

    private void checkedListBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      string comboBox = "";
      foreach (object checkedItem in this.checkedListBox1.CheckedItems)
        comboBox = checkedItem.ToString();
      this.textBox8.Text = this.GetIndexByComboBox(comboBox).ToString();
    }

    private void checkedListBox1_ItemCheck(object sender, ItemCheckEventArgs e)
    {
      if (e.NewValue != CheckState.Checked)
        return;
      for (int index = 0; index < this.checkedListBox1.Items.Count; ++index)
      {
        if (e.Index != index)
          this.checkedListBox1.SetItemChecked(index, false);
      }
    }

    public void LoadMisc()
    {
      string text = this.textBox8.Text;
      for (int index = 0; index < this.checkedListBox1.Items.Count; ++index)
      {
        int num = this.checkedListBox1.FindString(text);
        if (index == num)
          this.checkedListBox1.SetItemChecked(index, true);
      }
    }

    private void saveToolStripMenuItem_Click(object sender, EventArgs e)
    {
    }

    private void EventDropTool_Load(object sender, EventArgs e) => mySQL.SetConnection();

    private void textBox1_TextChanged(object sender, EventArgs e) => this.MakeList();

    private void LoadDataGrid()
    {
    }

        private void FillGrid()
        {
            dgItems.Rows.Clear();

            string query = "SELECT * FROM t_drop_item_data WHERE a_drop_idx = @dropIdx";

            using (var connection = new MySqlConnection(
                "datasource=" + Host +
                ";Port=3306;User ID=" + User +
                ";Password=" + Password +
                ";Database=" + Database +
                ";Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;"))
            {
                using (var command = new MySqlCommand(query, connection))
                {
                    command.Parameters.AddWithValue("@dropIdx", textBox6.Text);
                    connection.Open();

                    using (var reader = command.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            // Safe reads with TryParse to handle varchar or null columns
                            int primaryKey = SafeInt(reader["a_primarykey"]);
                            int dropIdx = SafeInt(reader["a_drop_idx"]);
                            int itemIdx = SafeInt(reader["a_item_idx"]);
                            int plus = SafeInt(reader["a_plus"]);
                            int flag = SafeInt(reader["a_flag"]);
                            int count = SafeInt(reader["a_count"]);
                            int prob = SafeInt(reader["a_prob"]);
                            int jobFlag = SafeInt(reader["a_job_flag"]);

                            string itemName = databaseHandle.ItemNameFast(itemIdx);

                            dgItems.Rows.Add(
                                databaseHandle.IconFast(itemIdx),
                                primaryKey,
                                dropIdx,
                                itemIdx,
                                itemName,
                                plus,
                                flag,
                                count,
                                prob,
                                jobFlag
                            );
                        }
                    }
                }
            }
        }

        // A small helper so you never crash on type mismatches or nulls
        private int SafeInt(object value)
        {
            if (value == null || value == DBNull.Value)
                return 0;

            return int.TryParse(value.ToString(), out int result) ? result : 0;
        }


        private void dgItems_CellClick(object sender, DataGridViewCellEventArgs e)
    {
      if (e.RowIndex < 0)
        return;
      DataGridViewRow row = this.dgItems.Rows[e.RowIndex];
      this.textBox16.Text = row.Cells["a_drop_idx"].Value.ToString();
      this.textBox26.Text = row.Cells["a_item_idx"].Value.ToString();
      this.textBox25.Text = row.Cells["a_plus"].Value.ToString();
      this.textBox10.Text = row.Cells["a_flag"].Value.ToString();
      this.textBox11.Text = row.Cells["a_count"].Value.ToString();
      this.textBox15.Text = row.Cells["JobFlag"].Value.ToString();
      this.textBox14.Text = row.Cells["a_prob"].Value.ToString();
      this.textBox17.Text = row.Cells["PrimaryKey"].Value.ToString();
      this.ShowJobFlag(Convert.ToInt32(this.textBox15.Text));
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void ShowJobFlag(int flag)
    {
      for (int index = 0; index < this.checkedListBox2.Items.Count; ++index)
        this.checkedListBox2.SetItemChecked(index, (flag & 1 << index) > 0);
    }

    private void checkedListBox2_SelectedIndexChanged(object sender, EventArgs e)
    {
      int num = 0;
      for (int index = 0; index < this.checkedListBox2.Items.Count; ++index)
      {
        if (this.checkedListBox2.GetItemChecked(index))
          num += 1 << index;
      }
      this.textBox15.Text = num.ToString();
    }

    private void checkedListBox2_SelectedValueChanged(object sender, EventArgs e)
    {
      this.textBox15.BackColor = Color.Pink;
    }

    private void checkBox1_CheckedChanged(object sender, EventArgs e)
    {
      if (this.checkBox1.Checked)
      {
        for (int index = 0; index < this.checkedListBox2.Items.Count; ++index)
        {
          this.checkedListBox2.SetItemChecked(index, true);
          this.textBox15.Text = "511";
        }
      }
      else
      {
        for (int index = 0; index < this.checkedListBox2.Items.Count; ++index)
        {
          this.checkedListBox2.SetItemChecked(index, false);
          this.textBox15.Text = "0";
        }
      }
    }

    private void checkBox1_SelectedValueChanged(object sender, EventArgs e)
    {
      this.textBox15.BackColor = Color.Pink;
    }

    private void textBox15_TextChanged(object sender, EventArgs e)
    {
    }

    private void InitializeComponent()
    {
      this.menuStrip1 = new MenuStrip();
      this.fileToolStripMenuItem = new ToolStripMenuItem();
      this.importFromDatabaseToolStripMenuItem = new ToolStripMenuItem();
      this.saveToolStripMenuItem = new ToolStripMenuItem();
      this.extraToolStripMenuItem = new ToolStripMenuItem();
      this.groupBox2 = new GroupBox();
      this.ItemDropHead = new DataGridView();
      this.drop_idx = new DataGridViewTextBoxColumn();
      this.Desc = new DataGridViewTextBoxColumn();
      this.drop_type = new DataGridViewTextBoxColumn();
      this.level_min = new DataGridViewTextBoxColumn();
      this.level_max = new DataGridViewTextBoxColumn();
      this.prob = new DataGridViewTextBoxColumn();
      this.prob_level = new DataGridViewTextBoxColumn();
      this.npc_type_party = new DataGridViewTextBoxColumn();
      this.npc_type_boss = new DataGridViewTextBoxColumn();
      this.npc = new DataGridViewTextBoxColumn();
      this.level_section = new DataGridViewTextBoxColumn();
      this.button17 = new Button();
      this.button18 = new Button();
      this.button19 = new Button();
      this.groupBox1 = new GroupBox();
      this.textBox1 = new TextBox();
      this.groupBox4 = new GroupBox();
      this.dgItems = new DataGridView();
      this.Icon = new DataGridViewImageColumn();
      this.PrimaryKey = new DataGridViewTextBoxColumn();
      this.a_drop_idx = new DataGridViewTextBoxColumn();
      this.a_item_idx = new DataGridViewTextBoxColumn();
      this.ItemName = new DataGridViewTextBoxColumn();
      this.a_plus = new DataGridViewTextBoxColumn();
      this.a_flag = new DataGridViewTextBoxColumn();
      this.a_count = new DataGridViewTextBoxColumn();
      this.a_prob = new DataGridViewTextBoxColumn();
      this.JobFlag = new DataGridViewTextBoxColumn();
      this.textBox2 = new TextBox();
      this.textBox3 = new TextBox();
      this.textBox4 = new TextBox();
      this.textBox5 = new TextBox();
      this.groupBox3 = new GroupBox();
      this.label3 = new Label();
      this.textBox12 = new TextBox();
      this.button15 = new Button();
      this.groupBox12 = new GroupBox();
      this.button8 = new Button();
      this.button7 = new Button();
      this.button5 = new Button();
      this.textBox30 = new TextBox();
      this.label23 = new Label();
      this.label22 = new Label();
      this.textBox29 = new TextBox();
      this.textBox28 = new TextBox();
      this.label21 = new Label();
      this.dataGridView1 = new DataGridView();
      this.Level1 = new DataGridViewTextBoxColumn();
      this.Level2 = new DataGridViewTextBoxColumn();
      this.ProbL = new DataGridViewTextBoxColumn();
      this.button3 = new Button();
      this.button1 = new Button();
      this.button2 = new Button();
      this.groupBox11 = new GroupBox();
      this.textBox27 = new TextBox();
      this.label20 = new Label();
      this.textBox23 = new TextBox();
      this.label19 = new Label();
      this.groupBox10 = new GroupBox();
      this.textBox22 = new TextBox();
      this.label18 = new Label();
      this.groupBox9 = new GroupBox();
      this.checkedListBox1 = new CheckedListBox();
      this.textBox21 = new TextBox();
      this.label17 = new Label();
      this.groupBox8 = new GroupBox();
      this.textBox20 = new TextBox();
      this.label14 = new Label();
      this.textBox19 = new TextBox();
      this.label13 = new Label();
      this.textBox18 = new TextBox();
      this.textBox7 = new TextBox();
      this.label2 = new Label();
      this.textBox6 = new TextBox();
      this.label1 = new Label();
      this.textBox8 = new TextBox();
      this.groupBox21 = new GroupBox();
      this.checkBox1 = new CheckBox();
      this.textBox15 = new TextBox();
      this.label8 = new Label();
      this.checkedListBox2 = new CheckedListBox();
      this.textBox9 = new TextBox();
      this.groupBox5 = new GroupBox();
      this.label12 = new Label();
      this.label10 = new Label();
      this.label11 = new Label();
      this.label15 = new Label();
      this.textBox24 = new TextBox();
      this.pictureBox7 = new PictureBox();
      this.textBox25 = new TextBox();
      this.textBox11 = new TextBox();
      this.label16 = new Label();
      this.button4 = new Button();
      this.label6 = new Label();
      this.groupBox7 = new GroupBox();
      this.textBox14 = new TextBox();
      this.textBox26 = new TextBox();
      this.label4 = new Label();
      this.label5 = new Label();
      this.textBox10 = new TextBox();
      this.textBox17 = new TextBox();
      this.textBox16 = new TextBox();
      this.button12 = new Button();
      this.button9 = new Button();
      this.button6 = new Button();
      this.label9 = new Label();
      this.menuStrip1.SuspendLayout();
      this.groupBox2.SuspendLayout();
      ((ISupportInitialize) this.ItemDropHead).BeginInit();
      this.groupBox1.SuspendLayout();
      this.groupBox4.SuspendLayout();
      ((ISupportInitialize) this.dgItems).BeginInit();
      this.groupBox3.SuspendLayout();
      this.groupBox12.SuspendLayout();
      ((ISupportInitialize) this.dataGridView1).BeginInit();
      this.groupBox11.SuspendLayout();
      this.groupBox10.SuspendLayout();
      this.groupBox9.SuspendLayout();
      this.groupBox8.SuspendLayout();
      this.groupBox21.SuspendLayout();
      this.groupBox5.SuspendLayout();
      ((ISupportInitialize) this.pictureBox7).BeginInit();
      this.groupBox7.SuspendLayout();
      this.SuspendLayout();
      this.menuStrip1.BackColor = SystemColors.ControlLightLight;
      this.menuStrip1.BackgroundImageLayout = ImageLayout.None;
      this.menuStrip1.Font = new Font("Segoe UI", 9f);
      this.menuStrip1.GripStyle = ToolStripGripStyle.Visible;
      this.menuStrip1.Items.AddRange(new ToolStripItem[2]
      {
        (ToolStripItem) this.fileToolStripMenuItem,
        (ToolStripItem) this.extraToolStripMenuItem
      });
      this.menuStrip1.Location = new Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new Size(931, 24);
      this.menuStrip1.TabIndex = 1;
      this.menuStrip1.Text = "menuStrip1";
      this.fileToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[2]
      {
        (ToolStripItem) this.importFromDatabaseToolStripMenuItem,
        (ToolStripItem) this.saveToolStripMenuItem
      });
      this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
      this.fileToolStripMenuItem.Size = new Size(37, 20);
      this.fileToolStripMenuItem.Text = "File";
      this.importFromDatabaseToolStripMenuItem.Name = "importFromDatabaseToolStripMenuItem";
      this.importFromDatabaseToolStripMenuItem.Size = new Size(180, 22);
      this.importFromDatabaseToolStripMenuItem.Text = "Load from Database";
      this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
      this.saveToolStripMenuItem.Size = new Size(180, 22);
      this.saveToolStripMenuItem.Text = "Save";
      this.saveToolStripMenuItem.Click += new EventHandler(this.saveToolStripMenuItem_Click);
      this.extraToolStripMenuItem.Enabled = false;
      this.extraToolStripMenuItem.Name = "extraToolStripMenuItem";
      this.extraToolStripMenuItem.Size = new Size(45, 20);
      this.extraToolStripMenuItem.Text = "Extra";
      this.groupBox2.Controls.Add((Control) this.ItemDropHead);
      this.groupBox2.Controls.Add((Control) this.button17);
      this.groupBox2.Controls.Add((Control) this.button18);
      this.groupBox2.Controls.Add((Control) this.button19);
      this.groupBox2.Location = new Point(12, 84);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new Size(256, 565);
      this.groupBox2.TabIndex = 4;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "Drop Event Head list";
      this.ItemDropHead.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.ItemDropHead.Columns.AddRange((DataGridViewColumn) this.drop_idx, (DataGridViewColumn) this.Desc, (DataGridViewColumn) this.drop_type, (DataGridViewColumn) this.level_min, (DataGridViewColumn) this.level_max, (DataGridViewColumn) this.prob, (DataGridViewColumn) this.prob_level, (DataGridViewColumn) this.npc_type_party, (DataGridViewColumn) this.npc_type_boss, (DataGridViewColumn) this.npc, (DataGridViewColumn) this.level_section);
      this.ItemDropHead.Location = new Point(6, 16);
      this.ItemDropHead.Name = "ItemDropHead";
      this.ItemDropHead.RowHeadersVisible = false;
      this.ItemDropHead.ScrollBars = ScrollBars.Vertical;
      this.ItemDropHead.Size = new Size(244, 490);
      this.ItemDropHead.TabIndex = 104;
      this.ItemDropHead.CellClick += new DataGridViewCellEventHandler(this.ItemDropHead_CellClick);
      this.drop_idx.HeaderText = "drop_idx";
      this.drop_idx.Name = "drop_idx";
      this.drop_idx.Width = 50;
      this.Desc.HeaderText = "Desc";
      this.Desc.Name = "Desc";
      this.Desc.Width = 200;
      this.drop_type.HeaderText = "drop_type";
      this.drop_type.Name = "drop_type";
      this.drop_type.Visible = false;
      this.level_min.HeaderText = "level_min";
      this.level_min.Name = "level_min";
      this.level_min.Visible = false;
      this.level_max.HeaderText = "level_max";
      this.level_max.Name = "level_max";
      this.level_max.Visible = false;
      this.prob.HeaderText = "prob";
      this.prob.Name = "prob";
      this.prob.Visible = false;
      this.prob_level.HeaderText = "prob_level";
      this.prob_level.Name = "prob_level";
      this.prob_level.Visible = false;
      this.npc_type_party.HeaderText = "npc_type_party";
      this.npc_type_party.Name = "npc_type_party";
      this.npc_type_party.Visible = false;
      this.npc_type_boss.HeaderText = "npc_type_boss";
      this.npc_type_boss.Name = "npc_type_boss";
      this.npc_type_boss.Visible = false;
      this.npc.HeaderText = "npc";
      this.npc.Name = "npc";
      this.npc.Visible = false;
      this.level_section.HeaderText = "level_section";
      this.level_section.Name = "level_section";
      this.level_section.Visible = false;
      this.button17.BackColor = Color.LightCoral;
      this.button17.FlatStyle = FlatStyle.Flat;
      this.button17.Image = (Image) Resources.delete;
      this.button17.ImageAlign = ContentAlignment.MiddleLeft;
      this.button17.Location = new Point(174, 512);
      this.button17.Name = "button17";
      this.button17.Size = new Size(65, 27);
      this.button17.TabIndex = 103;
      this.button17.Text = "    Delete";
      this.button17.UseVisualStyleBackColor = false;
      this.button17.Click += new EventHandler(this.button17_Click);
      this.button18.BackColor = Color.LightCyan;
      this.button18.FlatStyle = FlatStyle.Flat;
      this.button18.Image = (Image) Resources._08;
      this.button18.ImageAlign = ContentAlignment.MiddleLeft;
      this.button18.Location = new Point(96, 512);
      this.button18.Name = "button18";
      this.button18.Size = new Size(72, 27);
      this.button18.TabIndex = 102;
      this.button18.Text = "      Update";
      this.button18.UseVisualStyleBackColor = false;
      this.button18.Click += new EventHandler(this.button18_Click);
      this.button19.BackColor = Color.Plum;
      this.button19.FlatStyle = FlatStyle.Flat;
      this.button19.Image = (Image) Resources.control_add_blue;
      this.button19.ImageAlign = ContentAlignment.MiddleLeft;
      this.button19.Location = new Point(19, 512);
      this.button19.Name = "button19";
      this.button19.Size = new Size(71, 27);
      this.button19.TabIndex = 101;
      this.button19.Text = "     Add";
      this.button19.UseVisualStyleBackColor = false;
      this.button19.Click += new EventHandler(this.button19_Click);
      this.groupBox1.Controls.Add((Control) this.textBox1);
      this.groupBox1.Location = new Point(12, 27);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(256, 51);
      this.groupBox1.TabIndex = 3;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Search";
      this.textBox1.BorderStyle = BorderStyle.FixedSingle;
      this.textBox1.Location = new Point(6, 19);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(244, 20);
      this.textBox1.TabIndex = 4;
      this.textBox1.TextChanged += new EventHandler(this.textBox1_TextChanged);
      this.groupBox4.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left;
      this.groupBox4.Controls.Add((Control) this.dgItems);
      this.groupBox4.Location = new Point(274, (int) byte.MaxValue);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Size = new Size(644, 233);
      this.groupBox4.TabIndex = 26;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "Item Data";
      this.dgItems.AllowUserToAddRows = false;
      this.dgItems.AllowUserToDeleteRows = false;
      this.dgItems.BackgroundColor = SystemColors.Control;
      this.dgItems.BorderStyle = BorderStyle.None;
      this.dgItems.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dgItems.Columns.AddRange((DataGridViewColumn) this.Icon, (DataGridViewColumn) this.PrimaryKey, (DataGridViewColumn) this.a_drop_idx, (DataGridViewColumn) this.a_item_idx, (DataGridViewColumn) this.ItemName, (DataGridViewColumn) this.a_plus, (DataGridViewColumn) this.a_flag, (DataGridViewColumn) this.a_count, (DataGridViewColumn) this.a_prob, (DataGridViewColumn) this.JobFlag);
      this.dgItems.Dock = DockStyle.Fill;
      this.dgItems.EnableHeadersVisualStyles = false;
      this.dgItems.Location = new Point(3, 16);
      this.dgItems.Name = "dgItems";
      this.dgItems.RowHeadersVisible = false;
      this.dgItems.RowTemplate.Height = 32;
      this.dgItems.ScrollBars = ScrollBars.Vertical;
      this.dgItems.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
      this.dgItems.Size = new Size(638, 214);
      this.dgItems.TabIndex = 0;
      this.dgItems.CellClick += new DataGridViewCellEventHandler(this.dgItems_CellClick);
      this.Icon.HeaderText = "";
      this.Icon.Name = "Icon";
      this.Icon.Width = 32;
      this.PrimaryKey.HeaderText = "Index";
      this.PrimaryKey.Name = "PrimaryKey";
      this.PrimaryKey.Visible = false;
      this.PrimaryKey.Width = 60;
      this.a_drop_idx.HeaderText = "a_drop_idx";
      this.a_drop_idx.Name = "a_drop_idx";
      this.a_drop_idx.Visible = false;
      this.a_drop_idx.Width = 80;
      this.a_item_idx.HeaderText = "a_item_idx";
      this.a_item_idx.Name = "a_item_idx";
      this.a_item_idx.Width = 80;
      this.ItemName.HeaderText = "Item Name";
      this.ItemName.Name = "ItemName";
      this.ItemName.Width = 180;
      this.a_plus.HeaderText = "a_plus";
      this.a_plus.Name = "a_plus";
      this.a_plus.Width = 70;
      this.a_flag.HeaderText = "a_flag";
      this.a_flag.Name = "a_flag";
      this.a_flag.Width = 70;
      this.a_count.HeaderText = "a_count";
      this.a_count.Name = "a_count";
      this.a_count.Width = 50;
      this.a_prob.HeaderText = "a_prob";
      this.a_prob.Name = "a_prob";
      this.a_prob.Width = 90;
      this.JobFlag.HeaderText = "JobFlag";
      this.JobFlag.Name = "JobFlag";
      this.JobFlag.Width = 70;
      this.textBox2.Enabled = false;
      this.textBox2.Location = new Point(646, 3);
      this.textBox2.Name = "textBox2";
      this.textBox2.Size = new Size(27, 20);
      this.textBox2.TabIndex = 27;
      this.textBox2.Visible = false;
      this.textBox3.Enabled = false;
      this.textBox3.Location = new Point(680, 3);
      this.textBox3.Name = "textBox3";
      this.textBox3.Size = new Size(28, 20);
      this.textBox3.TabIndex = 28;
      this.textBox3.Visible = false;
      this.textBox4.Enabled = false;
      this.textBox4.Location = new Point(714, 3);
      this.textBox4.Name = "textBox4";
      this.textBox4.Size = new Size(27, 20);
      this.textBox4.TabIndex = 29;
      this.textBox4.Visible = false;
      this.textBox5.Enabled = false;
      this.textBox5.Location = new Point(748, 3);
      this.textBox5.Name = "textBox5";
      this.textBox5.Size = new Size(26, 20);
      this.textBox5.TabIndex = 30;
      this.textBox5.Visible = false;
      this.groupBox3.Controls.Add((Control) this.label3);
      this.groupBox3.Controls.Add((Control) this.textBox12);
      this.groupBox3.Controls.Add((Control) this.button15);
      this.groupBox3.Controls.Add((Control) this.groupBox12);
      this.groupBox3.Controls.Add((Control) this.button3);
      this.groupBox3.Controls.Add((Control) this.button1);
      this.groupBox3.Controls.Add((Control) this.button2);
      this.groupBox3.Controls.Add((Control) this.groupBox11);
      this.groupBox3.Controls.Add((Control) this.groupBox10);
      this.groupBox3.Controls.Add((Control) this.groupBox9);
      this.groupBox3.Controls.Add((Control) this.textBox21);
      this.groupBox3.Controls.Add((Control) this.label17);
      this.groupBox3.Controls.Add((Control) this.groupBox8);
      this.groupBox3.Controls.Add((Control) this.textBox7);
      this.groupBox3.Controls.Add((Control) this.label2);
      this.groupBox3.Controls.Add((Control) this.textBox6);
      this.groupBox3.Controls.Add((Control) this.label1);
      this.groupBox3.Location = new Point(280, 27);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Size = new Size(639, 222);
      this.groupBox3.TabIndex = 31;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "Drop Setting";
      this.label3.AutoSize = true;
      this.label3.Location = new Point(160, 51);
      this.label3.Name = "label3";
      this.label3.Size = new Size(35, 13);
      this.label3.TabIndex = 107;
      this.label3.Text = "Name";
      this.textBox12.Location = new Point(195, 48);
      this.textBox12.Name = "textBox12";
      this.textBox12.Size = new Size(128, 20);
      this.textBox12.TabIndex = 106;
      this.button15.BackgroundImage = (Image) Resources.search__5_;
      this.button15.BackgroundImageLayout = ImageLayout.None;
      this.button15.Location = new Point((int) sbyte.MaxValue, 45);
      this.button15.Name = "button15";
      this.button15.Size = new Size(27, 25);
      this.button15.TabIndex = 105;
      this.button15.UseVisualStyleBackColor = true;
      this.button15.Click += new EventHandler(this.button15_Click);
      this.groupBox12.Controls.Add((Control) this.button8);
      this.groupBox12.Controls.Add((Control) this.button7);
      this.groupBox12.Controls.Add((Control) this.button5);
      this.groupBox12.Controls.Add((Control) this.textBox30);
      this.groupBox12.Controls.Add((Control) this.label23);
      this.groupBox12.Controls.Add((Control) this.label22);
      this.groupBox12.Controls.Add((Control) this.textBox29);
      this.groupBox12.Controls.Add((Control) this.textBox28);
      this.groupBox12.Controls.Add((Control) this.label21);
      this.groupBox12.Controls.Add((Control) this.dataGridView1);
      this.groupBox12.Location = new Point(366, 80);
      this.groupBox12.Name = "groupBox12";
      this.groupBox12.Size = new Size(266, 136);
      this.groupBox12.TabIndex = 104;
      this.groupBox12.TabStop = false;
      this.groupBox12.Text = "Prob Bonus Level Section";
      this.button8.BackColor = Color.LightCoral;
      this.button8.FlatStyle = FlatStyle.Flat;
      this.button8.ImageAlign = ContentAlignment.MiddleLeft;
      this.button8.Location = new Point(134, 107);
      this.button8.Name = "button8";
      this.button8.Size = new Size(52, 23);
      this.button8.TabIndex = 105;
      this.button8.Text = " Delete";
      this.button8.UseVisualStyleBackColor = false;
      this.button7.BackColor = Color.LightCyan;
      this.button7.FlatStyle = FlatStyle.Flat;
      this.button7.ImageAlign = ContentAlignment.MiddleLeft;
      this.button7.Location = new Point(75, 107);
      this.button7.Name = "button7";
      this.button7.Size = new Size(53, 23);
      this.button7.TabIndex = 104;
      this.button7.Text = "Update";
      this.button7.UseVisualStyleBackColor = false;
      this.button5.BackColor = Color.Plum;
      this.button5.FlatStyle = FlatStyle.Flat;
      this.button5.ImageAlign = ContentAlignment.MiddleLeft;
      this.button5.Location = new Point(14, 107);
      this.button5.Name = "button5";
      this.button5.Size = new Size(55, 23);
      this.button5.TabIndex = 67;
      this.button5.Text = "Add";
      this.button5.UseVisualStyleBackColor = false;
      this.textBox30.Location = new Point(217, 63);
      this.textBox30.Name = "textBox30";
      this.textBox30.Size = new Size(49, 20);
      this.textBox30.TabIndex = 61;
      this.label23.AutoSize = true;
      this.label23.Location = new Point(155, 66);
      this.label23.Name = "label23";
      this.label23.Size = new Size(62, 13);
      this.label23.TabIndex = 60;
      this.label23.Text = "Bonus Prob";
      this.label22.AutoSize = true;
      this.label22.Location = new Point(203, 44);
      this.label22.Name = "label22";
      this.label22.Size = new Size(14, 13);
      this.label22.TabIndex = 59;
      this.label22.Text = "~";
      this.textBox29.Location = new Point(224, 37);
      this.textBox29.Name = "textBox29";
      this.textBox29.Size = new Size(36, 20);
      this.textBox29.TabIndex = 58;
      this.textBox28.Location = new Point(159, 37);
      this.textBox28.Name = "textBox28";
      this.textBox28.Size = new Size(36, 20);
      this.textBox28.TabIndex = 57;
      this.label21.AutoSize = true;
      this.label21.Location = new Point(172, 21);
      this.label21.Name = "label21";
      this.label21.Size = new Size(72, 13);
      this.label21.TabIndex = 56;
      this.label21.Text = "Level Section";
      this.dataGridView1.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dataGridView1.Columns.AddRange((DataGridViewColumn) this.Level1, (DataGridViewColumn) this.Level2, (DataGridViewColumn) this.ProbL);
      this.dataGridView1.EnableHeadersVisualStyles = false;
      this.dataGridView1.Location = new Point(0, 19);
      this.dataGridView1.Name = "dataGridView1";
      this.dataGridView1.RowHeadersVisible = false;
      this.dataGridView1.ScrollBars = ScrollBars.Vertical;
      this.dataGridView1.Size = new Size(153, 82);
      this.dataGridView1.TabIndex = 0;
      this.Level1.HeaderText = "n<=Level";
      this.Level1.Name = "Level1";
      this.Level1.Width = 55;
      this.Level2.HeaderText = "Level<=n";
      this.Level2.Name = "Level2";
      this.Level2.Width = 55;
      this.ProbL.HeaderText = "Prob";
      this.ProbL.Name = "ProbL";
      this.ProbL.Width = 50;
      this.button3.BackColor = Color.LightCyan;
      this.button3.FlatStyle = FlatStyle.Flat;
      this.button3.Image = (Image) Resources._08;
      this.button3.ImageAlign = ContentAlignment.MiddleLeft;
      this.button3.Location = new Point(147, 171);
      this.button3.Name = "button3";
      this.button3.Size = new Size(72, 27);
      this.button3.TabIndex = 103;
      this.button3.Text = "      Update";
      this.button3.UseVisualStyleBackColor = false;
      this.button3.Click += new EventHandler(this.button3_Click);
      this.button1.BackColor = Color.LightCoral;
      this.button1.FlatStyle = FlatStyle.Flat;
      this.button1.Image = (Image) Resources.delete;
      this.button1.ImageAlign = ContentAlignment.MiddleLeft;
      this.button1.Location = new Point(225, 171);
      this.button1.Name = "button1";
      this.button1.Size = new Size(77, 27);
      this.button1.TabIndex = 67;
      this.button1.Text = "    Delete";
      this.button1.UseVisualStyleBackColor = false;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.button2.BackColor = Color.Plum;
      this.button2.FlatStyle = FlatStyle.Flat;
      this.button2.Image = (Image) Resources.control_add_blue;
      this.button2.ImageAlign = ContentAlignment.MiddleLeft;
      this.button2.Location = new Point(64, 171);
      this.button2.Name = "button2";
      this.button2.Size = new Size(77, 27);
      this.button2.TabIndex = 66;
      this.button2.Text = "     Add";
      this.button2.UseVisualStyleBackColor = false;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.groupBox11.Controls.Add((Control) this.textBox27);
      this.groupBox11.Controls.Add((Control) this.label20);
      this.groupBox11.Controls.Add((Control) this.textBox23);
      this.groupBox11.Controls.Add((Control) this.label19);
      this.groupBox11.Location = new Point(222, 76);
      this.groupBox11.Name = "groupBox11";
      this.groupBox11.Size = new Size(142, 72);
      this.groupBox11.TabIndex = 58;
      this.groupBox11.TabStop = false;
      this.groupBox11.Text = "Prob Bonus By Npc Type";
      this.textBox27.Location = new Point(55, 45);
      this.textBox27.Name = "textBox27";
      this.textBox27.Size = new Size(52, 20);
      this.textBox27.TabIndex = 59;
      this.label20.AutoSize = true;
      this.label20.Location = new Point(13, 47);
      this.label20.Name = "label20";
      this.label20.Size = new Size(33, 13);
      this.label20.TabIndex = 58;
      this.label20.Text = "Boss:";
      this.textBox23.Location = new Point(55, 16);
      this.textBox23.Name = "textBox23";
      this.textBox23.Size = new Size(52, 20);
      this.textBox23.TabIndex = 57;
      this.label19.AutoSize = true;
      this.label19.Location = new Point(13, 18);
      this.label19.Name = "label19";
      this.label19.Size = new Size(34, 13);
      this.label19.TabIndex = 56;
      this.label19.Text = "Party:";
      this.groupBox10.Controls.Add((Control) this.textBox22);
      this.groupBox10.Controls.Add((Control) this.label18);
      this.groupBox10.Location = new Point(118, 76);
      this.groupBox10.Name = "groupBox10";
      this.groupBox10.Size = new Size(102, 72);
      this.groupBox10.TabIndex = 57;
      this.groupBox10.TabStop = false;
      this.groupBox10.Text = "Drop Prob";
      this.textBox22.Location = new Point(23, 40);
      this.textBox22.Name = "textBox22";
      this.textBox22.Size = new Size(52, 20);
      this.textBox22.TabIndex = 57;
      this.label18.AutoSize = true;
      this.label18.Location = new Point(6, 19);
      this.label18.Name = "label18";
      this.label18.Size = new Size(95, 13);
      this.label18.TabIndex = 56;
      this.label18.Text = "Drop Default Prob:";
      this.groupBox9.Controls.Add((Control) this.checkedListBox1);
      this.groupBox9.Location = new Point(8, 76);
      this.groupBox9.Name = "groupBox9";
      this.groupBox9.Size = new Size(107, 72);
      this.groupBox9.TabIndex = 56;
      this.groupBox9.TabStop = false;
      this.groupBox9.Text = "Drop Type";
      this.checkedListBox1.BackColor = SystemColors.Menu;
      this.checkedListBox1.BorderStyle = BorderStyle.None;
      this.checkedListBox1.CheckOnClick = true;
      this.checkedListBox1.FormattingEnabled = true;
      this.checkedListBox1.Items.AddRange(new object[3]
      {
        (object) "0 - Multi",
        (object) "1 - Once-Random",
        (object) "2 - Once-Select"
      });
      this.checkedListBox1.Location = new Point(6, 15);
      this.checkedListBox1.Name = "checkedListBox1";
      this.checkedListBox1.Size = new Size(94, 45);
      this.checkedListBox1.TabIndex = 52;
      this.checkedListBox1.ItemCheck += new ItemCheckEventHandler(this.checkedListBox1_ItemCheck);
      this.checkedListBox1.SelectedIndexChanged += new EventHandler(this.checkedListBox1_SelectedIndexChanged);
      this.textBox21.Location = new Point(63, 47);
      this.textBox21.Name = "textBox21";
      this.textBox21.Size = new Size(52, 20);
      this.textBox21.TabIndex = 55;
      this.textBox21.TextChanged += new EventHandler(this.textBox21_TextChanged);
      this.label17.AutoSize = true;
      this.label17.Location = new Point(7, 50);
      this.label17.Name = "label17";
      this.label17.Size = new Size(53, 13);
      this.label17.TabIndex = 54;
      this.label17.Text = "Drop Npc";
      this.groupBox8.Controls.Add((Control) this.textBox20);
      this.groupBox8.Controls.Add((Control) this.label14);
      this.groupBox8.Controls.Add((Control) this.textBox19);
      this.groupBox8.Controls.Add((Control) this.label13);
      this.groupBox8.Controls.Add((Control) this.textBox18);
      this.groupBox8.Location = new Point(341, 17);
      this.groupBox8.Name = "groupBox8";
      this.groupBox8.Size = new Size(291, 57);
      this.groupBox8.TabIndex = 53;
      this.groupBox8.TabStop = false;
      this.groupBox8.Text = "Prob By Difference Level";
      this.textBox20.Location = new Point(188, 25);
      this.textBox20.Name = "textBox20";
      this.textBox20.Size = new Size(81, 20);
      this.textBox20.TabIndex = 6;
      this.label14.AutoSize = true;
      this.label14.Location = new Point(177, 9);
      this.label14.Name = "label14";
      this.label14.Size = new Size(108, 13);
      this.label14.TabIndex = 5;
      this.label14.Text = "Decrease Prob/1 Diff";
      this.textBox19.Location = new Point(103, 26);
      this.textBox19.Name = "textBox19";
      this.textBox19.Size = new Size(45, 20);
      this.textBox19.TabIndex = 4;
      this.label13.AutoSize = true;
      this.label13.Location = new Point(56, 29);
      this.label13.Name = "label13";
      this.label13.Size = new Size(41, 13);
      this.label13.TabIndex = 3;
      this.label13.Text = "< Diff <";
      this.textBox18.Location = new Point(7, 26);
      this.textBox18.Name = "textBox18";
      this.textBox18.Size = new Size(45, 20);
      this.textBox18.TabIndex = 2;
      this.textBox7.Location = new Point(139, 17);
      this.textBox7.Name = "textBox7";
      this.textBox7.Size = new Size(184, 20);
      this.textBox7.TabIndex = 3;
      this.label2.AutoSize = true;
      this.label2.Location = new Point(101, 20);
      this.label2.Name = "label2";
      this.label2.Size = new Size(32, 13);
      this.label2.TabIndex = 2;
      this.label2.Text = "Desc";
      this.textBox6.Location = new Point(41, 17);
      this.textBox6.Name = "textBox6";
      this.textBox6.Size = new Size(45, 20);
      this.textBox6.TabIndex = 1;
      this.label1.AutoSize = true;
      this.label1.Location = new Point(7, 20);
      this.label1.Name = "label1";
      this.label1.Size = new Size(33, 13);
      this.label1.TabIndex = 0;
      this.label1.Text = "Index";
      this.textBox8.Enabled = false;
      this.textBox8.Location = new Point(809, 3);
      this.textBox8.Name = "textBox8";
      this.textBox8.Size = new Size(55, 20);
      this.textBox8.TabIndex = 53;
      this.textBox8.Visible = false;
      this.groupBox21.Controls.Add((Control) this.checkBox1);
      this.groupBox21.Controls.Add((Control) this.textBox15);
      this.groupBox21.Controls.Add((Control) this.label8);
      this.groupBox21.Controls.Add((Control) this.checkedListBox2);
      this.groupBox21.Controls.Add((Control) this.textBox9);
      this.groupBox21.Location = new Point(278, 494);
      this.groupBox21.Name = "groupBox21";
      this.groupBox21.Size = new Size(242, 155);
      this.groupBox21.TabIndex = 59;
      this.groupBox21.TabStop = false;
      this.groupBox21.Text = "Job Flag Setting";
      this.checkBox1.AutoSize = true;
      this.checkBox1.Location = new Point(12, 121);
      this.checkBox1.Name = "checkBox1";
      this.checkBox1.Size = new Size(71, 17);
      this.checkBox1.TabIndex = 48;
      this.checkBox1.Text = "Check All";
      this.checkBox1.UseVisualStyleBackColor = true;
      this.checkBox1.CheckedChanged += new EventHandler(this.checkBox1_CheckedChanged);
      this.textBox15.Location = new Point(147, 94);
      this.textBox15.Multiline = true;
      this.textBox15.Name = "textBox15";
      this.textBox15.Size = new Size(55, 21);
      this.textBox15.TabIndex = 47;
      this.textBox15.TextChanged += new EventHandler(this.textBox15_TextChanged);
      this.label8.AutoSize = true;
      this.label8.Location = new Point(107, 97);
      this.label8.Name = "label8";
      this.label8.Size = new Size(34, 13);
      this.label8.TabIndex = 46;
      this.label8.Text = "Total:";
      this.checkedListBox2.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
      this.checkedListBox2.BackColor = SystemColors.Control;
      this.checkedListBox2.BorderStyle = BorderStyle.None;
      this.checkedListBox2.CheckOnClick = true;
      this.checkedListBox2.ColumnWidth = 105;
      this.checkedListBox2.FormattingEnabled = true;
      this.checkedListBox2.IntegralHeight = false;
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
      this.checkedListBox2.Location = new Point(12, 19);
      this.checkedListBox2.MultiColumn = true;
      this.checkedListBox2.Name = "checkedListBox2";
      this.checkedListBox2.Size = new Size(213, 96);
      this.checkedListBox2.TabIndex = 39;
      this.checkedListBox2.SelectedIndexChanged += new EventHandler(this.checkedListBox2_SelectedIndexChanged);
      this.checkedListBox2.SelectedValueChanged += new EventHandler(this.checkedListBox2_SelectedValueChanged);
      this.textBox9.BorderStyle = BorderStyle.FixedSingle;
      this.textBox9.Location = new Point(47, 184);
      this.textBox9.Name = "textBox9";
      this.textBox9.Size = new Size(55, 20);
      this.textBox9.TabIndex = 12;
      this.groupBox5.Controls.Add((Control) this.label12);
      this.groupBox5.Controls.Add((Control) this.label10);
      this.groupBox5.Controls.Add((Control) this.label11);
      this.groupBox5.Controls.Add((Control) this.label15);
      this.groupBox5.Controls.Add((Control) this.textBox24);
      this.groupBox5.Controls.Add((Control) this.pictureBox7);
      this.groupBox5.Controls.Add((Control) this.textBox25);
      this.groupBox5.Controls.Add((Control) this.textBox11);
      this.groupBox5.Controls.Add((Control) this.label16);
      this.groupBox5.Controls.Add((Control) this.button4);
      this.groupBox5.Controls.Add((Control) this.label6);
      this.groupBox5.Controls.Add((Control) this.groupBox7);
      this.groupBox5.Controls.Add((Control) this.textBox26);
      this.groupBox5.Controls.Add((Control) this.label4);
      this.groupBox5.Controls.Add((Control) this.label5);
      this.groupBox5.Controls.Add((Control) this.textBox10);
      this.groupBox5.Location = new Point(526, 494);
      this.groupBox5.Name = "groupBox5";
      this.groupBox5.Size = new Size(372, 131);
      this.groupBox5.TabIndex = 60;
      this.groupBox5.TabStop = false;
      this.groupBox5.Text = "Item Setting";
      this.label12.AutoSize = true;
      this.label12.Font = new Font("Microsoft Sans Serif", 8.25f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.label12.ForeColor = SystemColors.AppWorkspace;
      this.label12.Location = new Point(223, 85);
      this.label12.Name = "label12";
      this.label12.Size = new Size(40, 13);
      this.label12.TabIndex = 52;
      this.label12.Text = "Value3";
      this.label10.AutoSize = true;
      this.label10.Font = new Font("Microsoft Sans Serif", 8.25f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.label10.ForeColor = SystemColors.AppWorkspace;
      this.label10.Location = new Point(6, 85);
      this.label10.Name = "label10";
      this.label10.Size = new Size(40, 13);
      this.label10.TabIndex = 50;
      this.label10.Text = "Value1";
      this.label11.AutoSize = true;
      this.label11.Font = new Font("Microsoft Sans Serif", 8.25f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.label11.ForeColor = SystemColors.AppWorkspace;
      this.label11.Location = new Point(117, 85);
      this.label11.Name = "label11";
      this.label11.Size = new Size(40, 13);
      this.label11.TabIndex = 51;
      this.label11.Text = "Value2";
      this.label15.AutoSize = true;
      this.label15.Location = new Point(51, 51);
      this.label15.Name = "label15";
      this.label15.Size = new Size(38, 13);
      this.label15.TabIndex = 41;
      this.label15.Text = "Name:";
      this.textBox24.Enabled = false;
      this.textBox24.Location = new Point(91, 48);
      this.textBox24.Multiline = true;
      this.textBox24.Name = "textBox24";
      this.textBox24.Size = new Size(125, 21);
      this.textBox24.TabIndex = 40;
      this.pictureBox7.Location = new Point(8, 19);
      this.pictureBox7.Name = "pictureBox7";
      this.pictureBox7.Size = new Size(32, 32);
      this.pictureBox7.TabIndex = 49;
      this.pictureBox7.TabStop = false;
      this.textBox25.Location = new Point(56, 90);
      this.textBox25.Multiline = true;
      this.textBox25.Name = "textBox25";
      this.textBox25.Size = new Size(55, 21);
      this.textBox25.TabIndex = 43;
      this.textBox11.Location = new Point(270, 90);
      this.textBox11.Multiline = true;
      this.textBox11.Name = "textBox11";
      this.textBox11.Size = new Size(60, 21);
      this.textBox11.TabIndex = 47;
      this.label16.AutoSize = true;
      this.label16.Location = new Point(16, 98);
      this.label16.Name = "label16";
      this.label16.Size = new Size(30, 13);
      this.label16.TabIndex = 42;
      this.label16.Text = "Plus:";
      this.button4.BackgroundImageLayout = ImageLayout.None;
      this.button4.Image = (Image) Resources.search__5_;
      this.button4.Location = new Point(189, 21);
      this.button4.Name = "button4";
      this.button4.Size = new Size(27, 25);
      this.button4.TabIndex = 39;
      this.button4.UseVisualStyleBackColor = true;
      this.button4.Click += new EventHandler(this.button4_Click);
      this.label6.AutoSize = true;
      this.label6.Location = new Point(225, 98);
      this.label6.Name = "label6";
      this.label6.Size = new Size(38, 13);
      this.label6.TabIndex = 46;
      this.label6.Text = "Count:";
      this.groupBox7.Controls.Add((Control) this.textBox14);
      this.groupBox7.Location = new Point(227, 21);
      this.groupBox7.Name = "groupBox7";
      this.groupBox7.Size = new Size(135, 50);
      this.groupBox7.TabIndex = 62;
      this.groupBox7.TabStop = false;
      this.groupBox7.Text = "Prob (10000 = 100%)";
      this.textBox14.Location = new Point(19, 19);
      this.textBox14.Name = "textBox14";
      this.textBox14.Size = new Size(100, 20);
      this.textBox14.TabIndex = 3;
      this.textBox26.Enabled = false;
      this.textBox26.Location = new Point(91, 23);
      this.textBox26.Multiline = true;
      this.textBox26.Name = "textBox26";
      this.textBox26.Size = new Size(92, 21);
      this.textBox26.TabIndex = 38;
      this.textBox26.TextChanged += new EventHandler(this.textBox26_TextChanged);
      this.label4.AutoSize = true;
      this.label4.Location = new Point(46, 26);
      this.label4.Name = "label4";
      this.label4.Size = new Size(44, 13);
      this.label4.TabIndex = 37;
      this.label4.Text = "Item ID:";
      this.label5.AutoSize = true;
      this.label5.Location = new Point((int) sbyte.MaxValue, 98);
      this.label5.Name = "label5";
      this.label5.Size = new Size(30, 13);
      this.label5.TabIndex = 44;
      this.label5.Text = "Flag:";
      this.textBox10.Location = new Point(163, 90);
      this.textBox10.Multiline = true;
      this.textBox10.Name = "textBox10";
      this.textBox10.Size = new Size(55, 21);
      this.textBox10.TabIndex = 45;
      this.textBox17.Enabled = false;
      this.textBox17.Location = new Point(370, 669);
      this.textBox17.Name = "textBox17";
      this.textBox17.Size = new Size(64, 20);
      this.textBox17.TabIndex = 53;
      this.textBox17.Visible = false;
      this.textBox16.Enabled = false;
      this.textBox16.Location = new Point(441, 669);
      this.textBox16.Name = "textBox16";
      this.textBox16.Size = new Size(64, 20);
      this.textBox16.TabIndex = 48;
      this.textBox16.Visible = false;
      this.button12.BackColor = Color.LightCoral;
      this.button12.FlatStyle = FlatStyle.Flat;
      this.button12.Image = (Image) Resources.delete;
      this.button12.ImageAlign = ContentAlignment.MiddleLeft;
      this.button12.Location = new Point(526, 660);
      this.button12.Name = "button12";
      this.button12.Size = new Size(77, 27);
      this.button12.TabIndex = 65;
      this.button12.Text = "    Delete";
      this.button12.UseVisualStyleBackColor = false;
      this.button12.Click += new EventHandler(this.button12_Click);
      this.button9.BackColor = Color.LightCyan;
      this.button9.FlatStyle = FlatStyle.Flat;
      this.button9.Image = (Image) Resources._08;
      this.button9.ImageAlign = ContentAlignment.MiddleLeft;
      this.button9.Location = new Point(613, 629);
      this.button9.Name = "button9";
      this.button9.Size = new Size(293, 60);
      this.button9.TabIndex = 64;
      this.button9.Text = "      Update";
      this.button9.UseVisualStyleBackColor = false;
      this.button9.Click += new EventHandler(this.button9_Click);
      this.button6.BackColor = Color.Plum;
      this.button6.FlatStyle = FlatStyle.Flat;
      this.button6.Image = (Image) Resources.control_add_blue;
      this.button6.ImageAlign = ContentAlignment.MiddleLeft;
      this.button6.Location = new Point(526, 627);
      this.button6.Name = "button6";
      this.button6.Size = new Size(77, 27);
      this.button6.TabIndex = 63;
      this.button6.Text = "     Add";
      this.button6.UseVisualStyleBackColor = false;
      this.button6.Click += new EventHandler(this.button6_Click);
      this.label9.AutoSize = true;
      this.label9.ForeColor = Color.Red;
      this.label9.Location = new Point(273, 696);
      this.label9.Name = "label9";
      this.label9.Size = new Size(591, 13);
      this.label9.TabIndex = 69;
      this.label9.Text = "JobFlags: Titan = 1 Knight = 2 Healer = 4 Mage+ArchMage =264 Rogue+ExRouge =144 Sorcerer = 32 NS = 64: 511 = ALL ";
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(931, 718);
      this.Controls.Add((Control) this.textBox17);
      this.Controls.Add((Control) this.label9);
      this.Controls.Add((Control) this.button12);
      this.Controls.Add((Control) this.button9);
      this.Controls.Add((Control) this.button6);
      this.Controls.Add((Control) this.groupBox5);
      this.Controls.Add((Control) this.textBox16);
      this.Controls.Add((Control) this.groupBox21);
      this.Controls.Add((Control) this.textBox8);
      this.Controls.Add((Control) this.groupBox3);
      this.Controls.Add((Control) this.textBox5);
      this.Controls.Add((Control) this.textBox4);
      this.Controls.Add((Control) this.textBox3);
      this.Controls.Add((Control) this.textBox2);
      this.Controls.Add((Control) this.groupBox4);
      this.Controls.Add((Control) this.groupBox2);
      this.Controls.Add((Control) this.groupBox1);
      this.Controls.Add((Control) this.menuStrip1);
      this.MaximizeBox = false;
      this.Name = nameof (EventDropTool);
      this.Text = nameof (EventDropTool);
      this.Load += new EventHandler(this.EventDropTool_Load);
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.groupBox2.ResumeLayout(false);
      ((ISupportInitialize) this.ItemDropHead).EndInit();
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.groupBox4.ResumeLayout(false);
      ((ISupportInitialize) this.dgItems).EndInit();
      this.groupBox3.ResumeLayout(false);
      this.groupBox3.PerformLayout();
      this.groupBox12.ResumeLayout(false);
      this.groupBox12.PerformLayout();
      ((ISupportInitialize) this.dataGridView1).EndInit();
      this.groupBox11.ResumeLayout(false);
      this.groupBox11.PerformLayout();
      this.groupBox10.ResumeLayout(false);
      this.groupBox10.PerformLayout();
      this.groupBox9.ResumeLayout(false);
      this.groupBox8.ResumeLayout(false);
      this.groupBox8.PerformLayout();
      this.groupBox21.ResumeLayout(false);
      this.groupBox21.PerformLayout();
      this.groupBox5.ResumeLayout(false);
      this.groupBox5.PerformLayout();
      ((ISupportInitialize) this.pictureBox7).EndInit();
      this.groupBox7.ResumeLayout(false);
      this.groupBox7.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();
    }

    private void button4_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox26.Text = itemPicker.ItemIndex.ToString();
    }

    private void textBox26_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox7.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox26.Text.Trim()));
      this.textBox24.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox26.Text.Trim()));
    }

    private void button12_Click(object sender, EventArgs e)
    {
      int index1 = this.dgItems.CurrentRow.Index - 1;
      DataGridViewRow row = this.dgItems.Rows[this.dgItems.CurrentRow.Index];
      if (this.dgItems.CurrentRow.Index < 0)
      {
        int num = (int) MessageBox.Show("You need select Item", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        if (MessageBox.Show("Do you want to Delete Item " + this.textBox26.Text.Trim() + "-" + this.textBox24.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
          return;
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_drop_item_data WHERE a_primarykey = '" + this.textBox17.Text + "'");
        this.FillGrid();
        if (index1 != -1)
        {
          this.dgItems.Rows[index1].Selected = true;
          this.dgItems.FirstDisplayedScrollingRowIndex = index1;
        }
        this.checkBox1.Checked = false;
        for (int index2 = 0; index2 < this.checkedListBox2.Items.Count; ++index2)
          this.checkedListBox2.SetItemChecked(index2, false);
      }
    }

    private void button9_Click(object sender, EventArgs e)
    {
      this.IniRead();
      int index1 = this.dgItems.CurrentRow.Index;
      DataGridViewRow row = this.dgItems.Rows[this.dgItems.CurrentRow.Index];
      if (MessageBox.Show("Do you want to Change Item to " + this.textBox24.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      MySqlConnection connection = new MySqlConnection("datasource=" + this.textBox2.Text + ";port=3306;username=" + this.textBox3.Text + ";password=" + this.textBox4.Text);
      MySqlCommand mySqlCommand = new MySqlCommand("UPDATE " + this.textBox5.Text + ".t_drop_item_data SET a_drop_idx='" + this.textBox6.Text + "', a_item_idx='" + this.textBox26.Text + "', a_plus='" + this.textBox25.Text + "', a_flag='" + this.textBox10.Text + "', a_count='" + this.textBox11.Text + "', a_prob='" + this.textBox14.Text + "', a_job_flag='" + this.textBox15.Text + "' WHERE a_primarykey='" + this.textBox17.Text + "'", connection);
      try
      {
        connection.Open();
        MySqlDataReader mySqlDataReader = mySqlCommand.ExecuteReader();
        int num = (int) MessageBox.Show("Your Item is Saved!");
        while (mySqlDataReader.Read())
          ;
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message);
      }
      this.FillGrid();
      this.dgItems.Rows[index1].Selected = true;
      this.dgItems.FirstDisplayedScrollingRowIndex = index1;
      this.checkBox1.Checked = false;
      for (int index2 = 0; index2 < this.checkedListBox2.Items.Count; ++index2)
        this.checkedListBox2.SetItemChecked(index2, false);
    }

    private void button6_Click(object sender, EventArgs e)
    {
      int index1 = this.dgItems.CurrentRow.Index;
      DataGridViewRow row = this.dgItems.Rows[this.dgItems.CurrentRow.Index];
      if (MessageBox.Show("Do you Add Item ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_drop_item_data (a_drop_idx, a_item_idx, a_plus, a_flag, a_count, a_prob, a_job_flag) VALUES (" + this.textBox6.Text + ", " + this.textBox26.Text + ", " + this.textBox25.Text + ", " + this.textBox10.Text + ", " + this.textBox11.Text + ", " + this.textBox14.Text + ", " + this.textBox15.Text + ")");
      int num = (int) MessageBox.Show("Successful add new", "Completed", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
      this.FillGrid();
      this.dgItems.Rows[index1].Selected = true;
      this.dgItems.FirstDisplayedScrollingRowIndex = index1;
      this.checkBox1.Checked = false;
      for (int index2 = 0; index2 < this.checkedListBox2.Items.Count; ++index2)
        this.checkedListBox2.SetItemChecked(index2, false);
    }

    private void button17_Click(object sender, EventArgs e)
    {
      int index = this.ItemDropHead.CurrentRow.Index - 1;
      DataGridViewRow row = this.ItemDropHead.Rows[this.ItemDropHead.CurrentRow.Index];
      if (this.ItemDropHead.CurrentRow.Index < 0)
      {
        int num = (int) MessageBox.Show("You need select Item", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        if (MessageBox.Show("Do you want to Delete All Drop " + this.textBox6.Text.Trim() + "-" + this.textBox7.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
          return;
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_drop_item_head WHERE a_drop_idx = '" + this.textBox6.Text + "'");
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_drop_item_data WHERE a_drop_idx = '" + this.textBox6.Text + "'");
        this.MakeList();
        if (index == -1)
          return;
        this.ItemDropHead.Rows[index].Selected = true;
        this.ItemDropHead.FirstDisplayedScrollingRowIndex = index;
      }
    }

    private void button18_Click(object sender, EventArgs e)
    {
      this.IniRead();
      int index = this.ItemDropHead.CurrentRow.Index;
      DataGridViewRow row = this.ItemDropHead.Rows[this.ItemDropHead.CurrentRow.Index];
      if (MessageBox.Show("Do you want to Change Drop Head Data " + this.textBox24.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      MySqlConnection connection = new MySqlConnection("datasource=" + this.textBox2.Text + ";port=3306;username=" + this.textBox3.Text + ";password=" + this.textBox4.Text);
      MySqlCommand mySqlCommand = new MySqlCommand("UPDATE " + this.textBox5.Text + ".t_drop_item_head SET a_desc='" + this.textBox7.Text + "', a_drop_type='" + this.textBox8.Text + "', a_level_mini='" + this.textBox18.Text + "', a_level_maxi='" + this.textBox19.Text + "', a_prob='" + this.textBox22.Text + "', a_prob_level='" + this.textBox20.Text + "', a_npc_type_party='" + this.textBox23.Text + "', a_npc_type_boss='" + this.textBox27.Text + "', a_npc='" + this.textBox21.Text + "' WHERE a_drop_idx='" + this.textBox6.Text + "'", connection);
      try
      {
        connection.Open();
        MySqlDataReader mySqlDataReader = mySqlCommand.ExecuteReader();
        int num = (int) MessageBox.Show("Your Drop Event is Saved!");
        while (mySqlDataReader.Read())
          ;
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message);
      }
      this.MakeList();
      this.ItemDropHead.Rows[index].Selected = true;
      this.ItemDropHead.FirstDisplayedScrollingRowIndex = index;
    }

    private void button19_Click(object sender, EventArgs e)
    {
      int index = this.ItemDropHead.CurrentRow.Index;
      DataGridViewRow row = this.ItemDropHead.Rows[this.ItemDropHead.CurrentRow.Index];
      if (MessageBox.Show("Do you want add New Drop Head  ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      if (this.textBox6.Text.Trim().Length <= 0)
      {
        int num1 = (int) MessageBox.Show("No data to select", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DROP TABLE IF EXISTS tempTable;CREATE TEMPORARY TABLE tempTable ENGINE=MEMORY SELECT * FROM t_drop_item_head WHERE a_drop_idx=" + this.textBox6.Text + ";SELECT a_drop_idx FROM tempTable;UPDATE tempTable SET a_drop_idx=(SELECT a_drop_idx from t_drop_item_head ORDER BY a_drop_idx DESC LIMIT 1)+1; SELECT a_drop_idx FROM tempTable;INSERT INTO t_drop_item_head SELECT * FROM tempTable;");
        int num2 = (int) MessageBox.Show("Successful Add new", "Completed", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
        this.MakeList();
        this.ItemDropHead.Rows[index].Selected = true;
        this.ItemDropHead.FirstDisplayedScrollingRowIndex = index;
      }
    }

    private void ClearBox()
    {
      this.pictureBox7.Image = (Image) null;
      this.textBox26.Text = "0";
      this.textBox25.Text = "0";
      this.textBox10.Text = "0";
      this.textBox11.Text = "1";
      this.textBox14.Text = "10000";
      this.textBox15.Clear();
      for (int index = 0; index < this.checkedListBox2.Items.Count; ++index)
        this.checkedListBox2.SetItemChecked(index, false);
    }

    private void button15_Click(object sender, EventArgs e)
    {
      this.textBox21.Text = "";
      MobPicker mobPicker = new MobPicker();
      if (mobPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox21.Text = mobPicker.MobIndex.ToString();
    }

    private void textBox21_TextChanged(object sender, EventArgs e)
    {
      this.textBox12.Text = "";
      if (this.textBox21.Text.Trim().Length <= 0)
        return;
      this.textBox12.Text = this.databaseHandle.MobNameFast(int.Parse(this.textBox21.Text.Trim()));
    }

    private void button2_Click(object sender, EventArgs e)
    {
      int index = this.ItemDropHead.CurrentRow.Index;
      DataGridViewRow row = this.ItemDropHead.Rows[this.ItemDropHead.CurrentRow.Index];
      if (MessageBox.Show("Do you want add New Drop Head  ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      if (this.textBox6.Text.Trim().Length <= 0)
      {
        int num1 = (int) MessageBox.Show("No data to select", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DROP TABLE IF EXISTS tempTable;CREATE TEMPORARY TABLE tempTable ENGINE=MEMORY SELECT * FROM t_drop_item_head WHERE a_drop_idx=" + this.textBox6.Text + ";SELECT a_drop_idx FROM tempTable;UPDATE tempTable SET a_drop_idx=(SELECT a_drop_idx from t_drop_item_head ORDER BY a_drop_idx DESC LIMIT 1)+1; SELECT a_drop_idx FROM tempTable;INSERT INTO t_drop_item_head SELECT * FROM tempTable;");
        int num2 = (int) MessageBox.Show("Successful Add new", "Completed", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
        this.MakeList();
        this.ItemDropHead.Rows[index].Selected = true;
        this.ItemDropHead.FirstDisplayedScrollingRowIndex = index;
      }
    }

    private void button3_Click(object sender, EventArgs e)
    {
      this.IniRead();
      int index = this.ItemDropHead.CurrentRow.Index;
      DataGridViewRow row = this.ItemDropHead.Rows[this.ItemDropHead.CurrentRow.Index];
      if (MessageBox.Show("Do you want to Change Drop Head Data " + this.textBox24.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      MySqlConnection connection = new MySqlConnection("datasource=" + this.textBox2.Text + ";port=3306;username=" + this.textBox3.Text + ";password=" + this.textBox4.Text);
      MySqlCommand mySqlCommand = new MySqlCommand("UPDATE " + this.textBox5.Text + ".t_drop_item_head SET a_desc='" + this.textBox7.Text + "', a_drop_type='" + this.textBox8.Text + "', a_level_mini='" + this.textBox18.Text + "', a_level_maxi='" + this.textBox19.Text + "', a_prob='" + this.textBox22.Text + "', a_prob_level='" + this.textBox20.Text + "', a_npc_type_party='" + this.textBox23.Text + "', a_npc_type_boss='" + this.textBox27.Text + "', a_npc='" + this.textBox21.Text + "' WHERE a_drop_idx='" + this.textBox6.Text + "'", connection);
      try
      {
        connection.Open();
        MySqlDataReader mySqlDataReader = mySqlCommand.ExecuteReader();
        int num = (int) MessageBox.Show("Your Drop Event is Saved!");
        while (mySqlDataReader.Read())
          ;
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message);
      }
      this.MakeList();
      this.ItemDropHead.Rows[index].Selected = true;
      this.ItemDropHead.FirstDisplayedScrollingRowIndex = index;
    }

    private void button1_Click(object sender, EventArgs e)
    {
      int index = this.ItemDropHead.CurrentRow.Index - 1;
      DataGridViewRow row = this.ItemDropHead.Rows[this.ItemDropHead.CurrentRow.Index];
      if (this.ItemDropHead.CurrentRow.Index < 0)
      {
        int num = (int) MessageBox.Show("You need select Item", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        if (MessageBox.Show("Do you want to Delete All Drop " + this.textBox6.Text.Trim() + "-" + this.textBox7.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
          return;
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_drop_item_head WHERE a_drop_idx = '" + this.textBox6.Text + "'");
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_drop_item_data WHERE a_drop_idx = '" + this.textBox6.Text + "'");
        this.MakeList();
        if (index == -1)
          return;
        this.ItemDropHead.Rows[index].Selected = true;
        this.ItemDropHead.FirstDisplayedScrollingRowIndex = index;
      }
    }
  }
}
