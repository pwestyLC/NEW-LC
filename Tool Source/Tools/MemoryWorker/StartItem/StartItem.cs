// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.StartItem.StartItem
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using LcDevPack_TeamDamonA.Properties;
using MySqlConnector;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.StartItem
{
  public class StartItem : Form
  {
    public static Connection connection = new Connection();
    private string Host = LcDevPack_TeamDamonA.Tools.MemoryWorker.StartItem.StartItem.connection.Settings.SqlHost;
    private string User = LcDevPack_TeamDamonA.Tools.MemoryWorker.StartItem.StartItem.connection.Settings.SqlUser;
    private string Password = LcDevPack_TeamDamonA.Tools.MemoryWorker.StartItem.StartItem.connection.Settings.SqlPassword;
    private string Database = LcDevPack_TeamDamonA.Tools.MemoryWorker.StartItem.StartItem.connection.Settings.SqlDatabase;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    public string rowName = nameof (a_index);
    public string[] menuArray = new string[2]
    {
      nameof (a_index),
      "a_name"
    };
    public string JobID = "";
    private ExportLodHandle exportLodHandle = new ExportLodHandle();
    private IContainer components = (IContainer) null;
    public string name;
    public int index;
    public string test2;
    public List<string> lArrayLevel;
    public List<string> lArrayProb;
    private ToolStripStatusLabel toolStripStatusLabel1;
    private Button Rouge;
    private Button Mage;
    private Button Knight;
    private Button Titan;
    private GroupBox groupBox1;
    private Button Healer;
    private ToolStripButton btnDeleteSelected;
    private ToolStripSeparator toolStripSeparator6;
    private ToolStripButton btnAddItems;
    private ToolStripSeparator toolStripSeparator1;
    private ToolStripButton btnSaveSelected;
    private StatusStrip statusStrip1;
    private DataGridView dgItems;
    private GroupBox groupBox4;
    private ToolStrip toolStrip2;
    private Button ArchMage;
    private Button ExRouge;
    private Button NightShadow;
    private Button Sorcerer;
    private GroupBox groupBox5;
    private TextBox ItemWearing;
    private Label label15;
    private TextBox NameItem;
    private PictureBox pictureBox7;
    private TextBox StartIndex;
    private TextBox ItemCount;
    private Button button4;
    private Label label16;
    private Label label6;
    private TextBox ItemID;
    private Label label4;
    private TextBox ItemPlus;
    private Label label5;
    private TextBox CharJob;
    private Label label2;
    private ComboBox comboBox1;
    private Button button6;
    private Button button12;
    private Button button9;
    private DataGridViewImageColumn Column7;
    private DataGridViewTextBoxColumn a_itemidx;
    private DataGridViewTextBoxColumn ItemName;
    private DataGridViewTextBoxColumn a_Job;
    private DataGridViewTextBoxColumn a_itemcount;
    private DataGridViewTextBoxColumn a_wearpos;
    private DataGridViewTextBoxColumn a_plus;
    private DataGridViewTextBoxColumn a_index;
    private Button button1;
    private Label label10;

    public StartItem() => this.InitializeComponent();

    private void StartItem_Load(object sender, EventArgs e)
    {
      this.toolStripStatusLabel1.Text = "Choose your Job!";
      this.toolStripStatusLabel1.ForeColor = Color.Maroon;
    }

    public void LoadDG(string JobIDX)
    {
      Stopwatch stopwatch = new Stopwatch();
      stopwatch.Start();
      if (this.JobID != "")
      {
        this.toolStripStatusLabel1.Text = "Ready";
        this.toolStripStatusLabel1.ForeColor = Color.Black;
      }
      this.toolStripStatusLabel1.Text = "Load Items ...";
      this.dgItems.Rows.Clear();
      string str1 = "SELECT * FROM t_startitems WHERE a_job ='+" + JobIDX + "' ORDER BY a_index";
      MySqlConnection mySqlConnection = new MySqlConnection("datasource=" + this.Host + ";Port=3306;User ID="  + this.User + ";Password=" + this.Password + ";Database=" + this.Database + ";Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;");
      MySqlCommand command = mySqlConnection.CreateCommand();
      command.CommandText = str1;
      mySqlConnection.Open();
      MySqlDataReader mySqlDataReader = command.ExecuteReader();
      while (mySqlDataReader.Read())
      {
        string str2 = mySqlDataReader.GetValue(0).ToString();
        string str3 = mySqlDataReader.GetValue(1).ToString();
        string str4 = mySqlDataReader.GetValue(2).ToString();
        string str5 = mySqlDataReader.GetValue(3).ToString();
        string str6 = mySqlDataReader.GetValue(4).ToString();
        string str7 = mySqlDataReader.GetValue(5).ToString();
        int int32 = Convert.ToInt32(str4);
        this.dgItems.Rows.Add((object) this.databaseHandle.IconFast(int32), (object) str4, (object) this.databaseHandle.ItemNameFast(int32), (object) str3, (object) str5, (object) str6, (object) str7, (object) str2);
      }
      mySqlConnection.Close();
      stopwatch.Stop();
      TimeSpan elapsed = stopwatch.Elapsed;
      string.Format("{0:00}:{1:00}:{2:00}.{3:00}", (object) elapsed.Hours, (object) elapsed.Minutes, (object) elapsed.Seconds, (object) (elapsed.Milliseconds / 10));
      this.toolStripStatusLabel1.Text = "Ready";
    }

    private void dgItems_CellClick(object sender, DataGridViewCellEventArgs e)
    {
      if (e.RowIndex < 0)
        return;
      DataGridViewRow row = this.dgItems.Rows[e.RowIndex];
      this.StartIndex.Text = row.Cells["a_index"].Value.ToString();
      this.CharJob.Text = row.Cells["a_job"].Value.ToString();
      this.ItemID.Text = row.Cells["a_itemidx"].Value.ToString();
      this.ItemCount.Text = row.Cells["a_itemcount"].Value.ToString();
      this.ItemWearing.Text = row.Cells["a_wearpos"].Value.ToString();
      this.ItemPlus.Text = row.Cells["a_plus"].Value.ToString();
      this.comboBox1.SelectedIndex = int.Parse(this.ItemWearing.Text) + 1;
      Convert.ToInt32(this.CharJob.Text);
    }

    private void btnSaveSelected_Click(object sender, EventArgs e)
    {
      int index = this.dgItems.CurrentRow.Index;
      DataGridViewRow row = this.dgItems.Rows[index];
      string str1 = Convert.ToString(row.Cells["a_itemidx"].Value);
      string str2 = Convert.ToString(row.Cells["a_job"].Value);
      string str3 = Convert.ToString(row.Cells["a_itemcount"].Value);
      string str4 = Convert.ToString(row.Cells["a_wearpos"].Value);
      string str5 = Convert.ToString(row.Cells["a_plus"].Value);
      string str6 = Convert.ToString(row.Cells["a_itemidx"].Value);
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_startitems SET a_job = '" + str2 + "', a_itemidx = '" + str1 + "', a_itemcount = '" + str3 + "', a_wearpos = '" + str4 + "', a_plus = '" + str5 + "' WHERE a_index = '" + str6 + "' ");
      this.dgItems.Rows.Clear();
      this.LoadDG(this.JobID);
      try
      {
        this.dgItems.Rows[index].Selected = true;
        this.dgItems.FirstDisplayedScrollingRowIndex = index;
      }
      catch
      {
        int num = (int) MessageBox.Show("You must select a Item", "Error");
      }
    }

    private void Titan_Click(object sender, EventArgs e)
    {
      this.JobID = "0";
      this.LoadDG(this.JobID);
      this.CharJob.Text = this.JobID;
    }

    private void btnAddItems_Click(object sender, EventArgs e)
    {
      if (this.CharJob.Text.Trim().Length <= 0)
      {
        int num1 = (int) MessageBox.Show("You need select Job", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        try
        {
          ItemPicker itemPicker = new ItemPicker();
          if (itemPicker.ShowDialog() != DialogResult.OK)
            return;
          this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_startitems (a_job, a_itemidx) VALUES ('" + this.JobID + "','" + itemPicker.ItemIndex.ToString() + "')");
        }
        catch
        {
          int num2 = (int) MessageBox.Show("Duplicated ItemID isn't allowed.", "Error");
        }
        this.dgItems.Rows.Clear();
        this.LoadDG(this.JobID);
        int index = this.dgItems.Rows.Count - 1;
        this.dgItems.Rows[index].Selected = true;
        this.dgItems.FirstDisplayedScrollingRowIndex = index;
      }
    }

    private void btnDeleteSelected_Click(object sender, EventArgs e)
    {
      if (this.ItemID.Text.Trim().Length <= 0)
      {
        int num1 = (int) MessageBox.Show("You need select Item", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        int index1 = this.dgItems.CurrentRow.Index;
        int index2 = index1 - 1;
        if (MessageBox.Show("Do you want to Delete Item: " + this.ItemID.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
          return;
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_startitems WHERE a_index ='" + Convert.ToString(this.dgItems.Rows[index1].Cells["a_index"].Value) + "'");
        this.dgItems.Rows.Clear();
        this.LoadDG(this.JobID);
        try
        {
          this.dgItems.Rows[index2].Selected = true;
          this.dgItems.FirstDisplayedScrollingRowIndex = index2;
        }
        catch
        {
          int num2 = (int) MessageBox.Show("You must select a Item", "Error");
        }
      }
    }

    private void Knight_Click(object sender, EventArgs e)
    {
      this.JobID = "1";
      this.LoadDG(this.JobID);
      this.CharJob.Text = this.JobID;
    }

    private void Healer_Click(object sender, EventArgs e)
    {
      this.JobID = "2";
      this.LoadDG(this.JobID);
      this.CharJob.Text = this.JobID;
    }

    private void Mage_Click(object sender, EventArgs e)
    {
      this.JobID = "3";
      this.LoadDG(this.JobID);
      this.CharJob.Text = this.JobID;
    }

    private void Rouge_Click(object sender, EventArgs e)
    {
      this.JobID = "4";
      this.LoadDG(this.JobID);
      this.CharJob.Text = this.JobID;
    }

    private void Sorcerer_Click(object sender, EventArgs e)
    {
      this.JobID = "5";
      this.LoadDG(this.JobID);
      this.CharJob.Text = this.JobID;
    }

    private void NightShadow_Click(object sender, EventArgs e)
    {
      this.JobID = "6";
      this.LoadDG(this.JobID);
      this.CharJob.Text = this.JobID;
    }

    private void ExRouge_Click(object sender, EventArgs e)
    {
      this.JobID = "7";
      this.LoadDG(this.JobID);
      this.CharJob.Text = this.JobID;
    }

    private void ArchMage_Click(object sender, EventArgs e)
    {
      this.JobID = "8";
      this.LoadDG(this.JobID);
      this.CharJob.Text = this.JobID;
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

    private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.ItemWearing.Text = this.GetIndexByComboBox(this.comboBox1.Text).ToString();
    }

    private void comboBox1_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.comboBox1.BackColor = Color.Pink;
      this.ItemWearing.BackColor = Color.Pink;
    }

    private void ItemID_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox7.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.ItemID.Text.Trim()));
      this.NameItem.Text = this.databaseHandle.ItemNameFast(int.Parse(this.ItemID.Text.Trim()));
    }

    private void exportlodToolStripMenuItem_Click(object sender, EventArgs e)
    {
    }

    private void toolStripStatusLabel1_Click(object sender, EventArgs e)
    {
    }

    private void exportlodToolStripMenuItem_Click_1(object sender, EventArgs e)
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
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (LcDevPack_TeamDamonA.Tools.MemoryWorker.StartItem.StartItem));
      this.toolStripStatusLabel1 = new ToolStripStatusLabel();
      this.groupBox1 = new GroupBox();
      this.ArchMage = new Button();
      this.ExRouge = new Button();
      this.NightShadow = new Button();
      this.Sorcerer = new Button();
      this.Rouge = new Button();
      this.Mage = new Button();
      this.Knight = new Button();
      this.Healer = new Button();
      this.Titan = new Button();
      this.btnDeleteSelected = new ToolStripButton();
      this.toolStripSeparator6 = new ToolStripSeparator();
      this.btnAddItems = new ToolStripButton();
      this.toolStripSeparator1 = new ToolStripSeparator();
      this.btnSaveSelected = new ToolStripButton();
      this.statusStrip1 = new StatusStrip();
      this.dgItems = new DataGridView();
      this.Column7 = new DataGridViewImageColumn();
      this.a_itemidx = new DataGridViewTextBoxColumn();
      this.ItemName = new DataGridViewTextBoxColumn();
      this.a_Job = new DataGridViewTextBoxColumn();
      this.a_itemcount = new DataGridViewTextBoxColumn();
      this.a_wearpos = new DataGridViewTextBoxColumn();
      this.a_plus = new DataGridViewTextBoxColumn();
      this.a_index = new DataGridViewTextBoxColumn();
      this.groupBox4 = new GroupBox();
      this.toolStrip2 = new ToolStrip();
      this.groupBox5 = new GroupBox();
      this.comboBox1 = new ComboBox();
      this.label10 = new Label();
      this.CharJob = new TextBox();
      this.label2 = new Label();
      this.ItemWearing = new TextBox();
      this.label15 = new Label();
      this.NameItem = new TextBox();
      this.pictureBox7 = new PictureBox();
      this.StartIndex = new TextBox();
      this.ItemCount = new TextBox();
      this.button4 = new Button();
      this.label16 = new Label();
      this.label6 = new Label();
      this.ItemID = new TextBox();
      this.label4 = new Label();
      this.ItemPlus = new TextBox();
      this.label5 = new Label();
      this.button6 = new Button();
      this.button12 = new Button();
      this.button9 = new Button();
      this.button1 = new Button();
      this.groupBox1.SuspendLayout();
      this.statusStrip1.SuspendLayout();
      ((ISupportInitialize) this.dgItems).BeginInit();
      this.groupBox4.SuspendLayout();
      this.toolStrip2.SuspendLayout();
      this.groupBox5.SuspendLayout();
      ((ISupportInitialize) this.pictureBox7).BeginInit();
      this.SuspendLayout();
      this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
      this.toolStripStatusLabel1.Size = new Size(50, 20);
      this.toolStripStatusLabel1.Text = "Ready";
      this.groupBox1.Controls.Add((Control) this.ArchMage);
      this.groupBox1.Controls.Add((Control) this.ExRouge);
      this.groupBox1.Controls.Add((Control) this.NightShadow);
      this.groupBox1.Controls.Add((Control) this.Sorcerer);
      this.groupBox1.Controls.Add((Control) this.Rouge);
      this.groupBox1.Controls.Add((Control) this.Mage);
      this.groupBox1.Controls.Add((Control) this.Knight);
      this.groupBox1.Controls.Add((Control) this.Healer);
      this.groupBox1.Controls.Add((Control) this.Titan);
      this.groupBox1.Location = new Point(14, 7);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(348, 55);
      this.groupBox1.TabIndex = 51;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Job Selecter";
      this.ArchMage.BackgroundImage = (Image) Resources._8ArchMage;
      this.ArchMage.BackgroundImageLayout = ImageLayout.Stretch;
      this.ArchMage.FlatStyle = FlatStyle.Flat;
      this.ArchMage.Location = new Point(310, 17);
      this.ArchMage.Name = "ArchMage";
      this.ArchMage.Size = new Size(32, 32);
      this.ArchMage.TabIndex = 53;
      this.ArchMage.UseVisualStyleBackColor = true;
      this.ArchMage.Click += new EventHandler(this.ArchMage_Click);
      this.ExRouge.BackgroundImage = (Image) Resources._7ExRouge;
      this.ExRouge.BackgroundImageLayout = ImageLayout.Stretch;
      this.ExRouge.FlatStyle = FlatStyle.Flat;
      this.ExRouge.Location = new Point(272, 17);
      this.ExRouge.Name = "ExRouge";
      this.ExRouge.Size = new Size(32, 32);
      this.ExRouge.TabIndex = 52;
      this.ExRouge.UseVisualStyleBackColor = true;
      this.ExRouge.Click += new EventHandler(this.ExRouge_Click);
      this.NightShadow.BackgroundImage = (Image) Resources._6NightShadow;
      this.NightShadow.BackgroundImageLayout = ImageLayout.Stretch;
      this.NightShadow.FlatStyle = FlatStyle.Flat;
      this.NightShadow.Location = new Point(234, 17);
      this.NightShadow.Name = "NightShadow";
      this.NightShadow.Size = new Size(32, 32);
      this.NightShadow.TabIndex = 51;
      this.NightShadow.UseVisualStyleBackColor = true;
      this.NightShadow.Click += new EventHandler(this.NightShadow_Click);
      this.Sorcerer.BackgroundImage = (Image) Resources._5Sorcerer;
      this.Sorcerer.BackgroundImageLayout = ImageLayout.Stretch;
      this.Sorcerer.FlatStyle = FlatStyle.Flat;
      this.Sorcerer.Location = new Point(196, 17);
      this.Sorcerer.Name = "Sorcerer";
      this.Sorcerer.Size = new Size(32, 32);
      this.Sorcerer.TabIndex = 50;
      this.Sorcerer.UseVisualStyleBackColor = true;
      this.Sorcerer.Click += new EventHandler(this.Sorcerer_Click);
      this.Rouge.BackgroundImage = (Image) Resources._4Rouge;
      this.Rouge.BackgroundImageLayout = ImageLayout.Stretch;
      this.Rouge.FlatStyle = FlatStyle.Flat;
      this.Rouge.Location = new Point(158, 17);
      this.Rouge.Name = "Rouge";
      this.Rouge.Size = new Size(32, 32);
      this.Rouge.TabIndex = 49;
      this.Rouge.UseVisualStyleBackColor = true;
      this.Rouge.Click += new EventHandler(this.Rouge_Click);
      this.Mage.BackgroundImage = (Image) Resources._3Mage;
      this.Mage.BackgroundImageLayout = ImageLayout.Stretch;
      this.Mage.FlatStyle = FlatStyle.Flat;
      this.Mage.Location = new Point(120, 17);
      this.Mage.Name = "Mage";
      this.Mage.Size = new Size(32, 32);
      this.Mage.TabIndex = 48;
      this.Mage.UseVisualStyleBackColor = true;
      this.Mage.Click += new EventHandler(this.Mage_Click);
      this.Knight.BackgroundImage = (Image) Resources._1Knight;
      this.Knight.BackgroundImageLayout = ImageLayout.Stretch;
      this.Knight.FlatStyle = FlatStyle.Flat;
      this.Knight.Location = new Point(44, 17);
      this.Knight.Name = "Knight";
      this.Knight.Size = new Size(32, 32);
      this.Knight.TabIndex = 47;
      this.Knight.UseVisualStyleBackColor = true;
      this.Knight.Click += new EventHandler(this.Knight_Click);
      this.Healer.BackgroundImage = (Image) Resources._2Healer;
      this.Healer.BackgroundImageLayout = ImageLayout.Stretch;
      this.Healer.FlatStyle = FlatStyle.Flat;
      this.Healer.Location = new Point(82, 17);
      this.Healer.Name = "Healer";
      this.Healer.Size = new Size(32, 32);
      this.Healer.TabIndex = 45;
      this.Healer.UseVisualStyleBackColor = true;
      this.Healer.Click += new EventHandler(this.Healer_Click);
      this.Titan.BackgroundImage = (Image) Resources._0Titan;
      this.Titan.BackgroundImageLayout = ImageLayout.Stretch;
      this.Titan.FlatStyle = FlatStyle.Flat;
      this.Titan.Location = new Point(6, 17);
      this.Titan.Name = "Titan";
      this.Titan.Size = new Size(32, 32);
      this.Titan.TabIndex = 46;
      this.Titan.UseVisualStyleBackColor = true;
      this.Titan.Click += new EventHandler(this.Titan_Click);
      this.btnDeleteSelected.DisplayStyle = ToolStripItemDisplayStyle.Text;
      this.btnDeleteSelected.ImageTransparentColor = Color.Magenta;
      this.btnDeleteSelected.Name = "btnDeleteSelected";
      this.btnDeleteSelected.Size = new Size(118, 24);
      this.btnDeleteSelected.Text = "Delete Selected";
      this.btnDeleteSelected.Click += new EventHandler(this.btnDeleteSelected_Click);
      this.toolStripSeparator6.Name = "toolStripSeparator6";
      this.toolStripSeparator6.Size = new Size(6, 27);
      this.btnAddItems.DisplayStyle = ToolStripItemDisplayStyle.Text;
      this.btnAddItems.ImageTransparentColor = Color.Magenta;
      this.btnAddItems.Name = "btnAddItems";
      this.btnAddItems.Size = new Size(75, 24);
      this.btnAddItems.Text = "Add Item";
      this.btnAddItems.Click += new EventHandler(this.btnAddItems_Click);
      this.toolStripSeparator1.Name = "toolStripSeparator1";
      this.toolStripSeparator1.Size = new Size(6, 27);
      this.btnSaveSelected.DisplayStyle = ToolStripItemDisplayStyle.Text;
      this.btnSaveSelected.ImageTransparentColor = Color.Magenta;
      this.btnSaveSelected.Name = "btnSaveSelected";
      this.btnSaveSelected.Size = new Size(78, 24);
      this.btnSaveSelected.Text = "Save Item";
      this.btnSaveSelected.Click += new EventHandler(this.btnSaveSelected_Click);
      this.statusStrip1.ImageScalingSize = new Size(20, 20);
      this.statusStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.toolStripStatusLabel1
      });
      this.statusStrip1.Location = new Point(0, 609);
      this.statusStrip1.Name = "statusStrip1";
      this.statusStrip1.Size = new Size(707, 26);
      this.statusStrip1.TabIndex = 52;
      this.statusStrip1.Text = "statusStrip1";
      this.dgItems.AllowUserToAddRows = false;
      this.dgItems.AllowUserToDeleteRows = false;
      this.dgItems.BackgroundColor = SystemColors.Control;
      this.dgItems.BorderStyle = BorderStyle.None;
      this.dgItems.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dgItems.Columns.AddRange((DataGridViewColumn) this.Column7, (DataGridViewColumn) this.a_itemidx, (DataGridViewColumn) this.ItemName, (DataGridViewColumn) this.a_Job, (DataGridViewColumn) this.a_itemcount, (DataGridViewColumn) this.a_wearpos, (DataGridViewColumn) this.a_plus, (DataGridViewColumn) this.a_index);
      this.dgItems.Dock = DockStyle.Fill;
      this.dgItems.EnableHeadersVisualStyles = false;
      this.dgItems.Location = new Point(3, 18);
      this.dgItems.Name = "dgItems";
      this.dgItems.RowHeadersVisible = false;
      this.dgItems.RowHeadersWidth = 51;
      this.dgItems.RowTemplate.Height = 32;
      this.dgItems.Size = new Size(678, 340);
      this.dgItems.TabIndex = 0;
      this.dgItems.CellClick += new DataGridViewCellEventHandler(this.dgItems_CellClick);
      this.Column7.HeaderText = "";
      this.Column7.MinimumWidth = 6;
      this.Column7.Name = "Column7";
      this.Column7.Width = 32;
      this.a_itemidx.HeaderText = "ItemID";
      this.a_itemidx.MinimumWidth = 6;
      this.a_itemidx.Name = "a_itemidx";
      this.a_itemidx.Width = 50;
      this.ItemName.HeaderText = "ItemName";
      this.ItemName.MinimumWidth = 6;
      this.ItemName.Name = "ItemName";
      this.ItemName.ReadOnly = true;
      this.ItemName.Width = 275;
      this.a_Job.HeaderText = "Job";
      this.a_Job.MinimumWidth = 6;
      this.a_Job.Name = "a_Job";
      this.a_Job.Visible = false;
      this.a_Job.Width = 75;
      this.a_itemcount.HeaderText = "ItemCount";
      this.a_itemcount.MinimumWidth = 6;
      this.a_itemcount.Name = "a_itemcount";
      this.a_itemcount.Width = 125;
      this.a_wearpos.HeaderText = "Wearpos";
      this.a_wearpos.MinimumWidth = 6;
      this.a_wearpos.Name = "a_wearpos";
      this.a_wearpos.Width = 125;
      this.a_plus.HeaderText = "Plus";
      this.a_plus.MinimumWidth = 6;
      this.a_plus.Name = "a_plus";
      this.a_plus.Width = 125;
      this.a_index.HeaderText = "Index";
      this.a_index.MinimumWidth = 6;
      this.a_index.Name = "a_index";
      this.a_index.Visible = false;
      this.a_index.Width = 60;
      this.groupBox4.Controls.Add((Control) this.dgItems);
      this.groupBox4.Controls.Add((Control) this.toolStrip2);
      this.groupBox4.Location = new Point(11, 67);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Size = new Size(684, 388);
      this.groupBox4.TabIndex = 50;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "Items";
      this.toolStrip2.Dock = DockStyle.Bottom;
      this.toolStrip2.GripStyle = ToolStripGripStyle.Hidden;
      this.toolStrip2.ImageScalingSize = new Size(20, 20);
      this.toolStrip2.Items.AddRange(new ToolStripItem[5]
      {
        (ToolStripItem) this.btnSaveSelected,
        (ToolStripItem) this.toolStripSeparator1,
        (ToolStripItem) this.btnAddItems,
        (ToolStripItem) this.toolStripSeparator6,
        (ToolStripItem) this.btnDeleteSelected
      });
      this.toolStrip2.Location = new Point(3, 358);
      this.toolStrip2.Name = "toolStrip2";
      this.toolStrip2.Size = new Size(678, 27);
      this.toolStrip2.TabIndex = 1;
      this.toolStrip2.Text = "toolStrip2";
      this.groupBox5.BackColor = Color.FromArgb(224, 224, 224);
      this.groupBox5.Controls.Add((Control) this.comboBox1);
      this.groupBox5.Controls.Add((Control) this.label10);
      this.groupBox5.Controls.Add((Control) this.CharJob);
      this.groupBox5.Controls.Add((Control) this.label2);
      this.groupBox5.Controls.Add((Control) this.ItemWearing);
      this.groupBox5.Controls.Add((Control) this.label15);
      this.groupBox5.Controls.Add((Control) this.NameItem);
      this.groupBox5.Controls.Add((Control) this.pictureBox7);
      this.groupBox5.Controls.Add((Control) this.StartIndex);
      this.groupBox5.Controls.Add((Control) this.ItemCount);
      this.groupBox5.Controls.Add((Control) this.button4);
      this.groupBox5.Controls.Add((Control) this.label16);
      this.groupBox5.Controls.Add((Control) this.label6);
      this.groupBox5.Controls.Add((Control) this.ItemID);
      this.groupBox5.Controls.Add((Control) this.label4);
      this.groupBox5.Controls.Add((Control) this.ItemPlus);
      this.groupBox5.Controls.Add((Control) this.label5);
      this.groupBox5.Location = new Point(11, 463);
      this.groupBox5.Name = "groupBox5";
      this.groupBox5.Size = new Size(684, 109);
      this.groupBox5.TabIndex = 61;
      this.groupBox5.TabStop = false;
      this.groupBox5.Text = "Item Setting";
      this.comboBox1.FlatStyle = FlatStyle.Flat;
      this.comboBox1.FormattingEnabled = true;
      this.comboBox1.Items.AddRange(new object[13]
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
        (object) "11 - Wing Slot"
      });
      this.comboBox1.Location = new Point(473, 42);
      this.comboBox1.Name = "comboBox1";
      this.comboBox1.Size = new Size(144, 24);
      this.comboBox1.TabIndex = 55;
      this.comboBox1.SelectedIndexChanged += new EventHandler(this.comboBox1_SelectedIndexChanged);
      this.comboBox1.SelectionChangeCommitted += new EventHandler(this.comboBox1_SelectionChangeCommitted);
      this.label10.AutoSize = true;
      this.label10.Location = new Point(417, 45);
      this.label10.Name = "label10";
      this.label10.Size = new Size(65, 17);
      this.label10.TabIndex = 54;
      this.label10.Text = "Wearing:";
      this.CharJob.Enabled = false;
      this.CharJob.Location = new Point(152, 16);
      this.CharJob.Multiline = true;
      this.CharJob.Name = "CharJob";
      this.CharJob.Size = new Size(55, 21);
      this.CharJob.TabIndex = 53;
      this.label2.AutoSize = true;
      this.label2.Location = new Point(117, 19);
      this.label2.Name = "label2";
      this.label2.Size = new Size(35, 17);
      this.label2.TabIndex = 52;
      this.label2.Text = "Job:";
      this.ItemWearing.Location = new Point(623, 41);
      this.ItemWearing.Multiline = true;
      this.ItemWearing.Name = "ItemWearing";
      this.ItemWearing.Size = new Size(55, 21);
      this.ItemWearing.TabIndex = 51;
      this.label15.AutoSize = true;
      this.label15.Location = new Point(52, 81);
      this.label15.Name = "label15";
      this.label15.Size = new Size(49, 17);
      this.label15.TabIndex = 41;
      this.label15.Text = "Name:";
      this.NameItem.Enabled = false;
      this.NameItem.Location = new Point(92, 78);
      this.NameItem.Multiline = true;
      this.NameItem.Name = "NameItem";
      this.NameItem.Size = new Size(218, 21);
      this.NameItem.TabIndex = 40;
      this.pictureBox7.Location = new Point(8, 41);
      this.pictureBox7.Name = "pictureBox7";
      this.pictureBox7.Size = new Size(32, 32);
      this.pictureBox7.TabIndex = 49;
      this.pictureBox7.TabStop = false;
      this.StartIndex.Enabled = false;
      this.StartIndex.Location = new Point(50, 16);
      this.StartIndex.Multiline = true;
      this.StartIndex.Name = "StartIndex";
      this.StartIndex.Size = new Size(55, 21);
      this.StartIndex.TabIndex = 43;
      this.ItemCount.Location = new Point(262, 41);
      this.ItemCount.Multiline = true;
      this.ItemCount.Name = "ItemCount";
      this.ItemCount.Size = new Size(48, 21);
      this.ItemCount.TabIndex = 47;
      this.button4.BackgroundImageLayout = ImageLayout.None;
      this.button4.Image = (Image) Resources.search__5_;
      this.button4.Location = new Point(189, 43);
      this.button4.Name = "button4";
      this.button4.Size = new Size(27, 25);
      this.button4.TabIndex = 39;
      this.button4.UseVisualStyleBackColor = true;
      this.button4.Click += new EventHandler(this.button4_Click);
      this.label16.AutoSize = true;
      this.label16.Location = new Point(15, 19);
      this.label16.Name = "label16";
      this.label16.Size = new Size(45, 17);
      this.label16.TabIndex = 42;
      this.label16.Text = "Index:";
      this.label6.AutoSize = true;
      this.label6.Location = new Point(220, 49);
      this.label6.Name = "label6";
      this.label6.Size = new Size(49, 17);
      this.label6.TabIndex = 46;
      this.label6.Text = "Count:";
      this.ItemID.Enabled = false;
      this.ItemID.Location = new Point(91, 45);
      this.ItemID.Multiline = true;
      this.ItemID.Name = "ItemID";
      this.ItemID.Size = new Size(92, 21);
      this.ItemID.TabIndex = 38;
      this.ItemID.TextChanged += new EventHandler(this.ItemID_TextChanged);
      this.label4.AutoSize = true;
      this.label4.Location = new Point(46, 48);
      this.label4.Name = "label4";
      this.label4.Size = new Size(55, 17);
      this.label4.TabIndex = 37;
      this.label4.Text = "Item ID:";
      this.ItemPlus.Location = new Point(356, 42);
      this.ItemPlus.Multiline = true;
      this.ItemPlus.Name = "ItemPlus";
      this.ItemPlus.Size = new Size(55, 21);
      this.ItemPlus.TabIndex = 45;
      this.label5.AutoSize = true;
      this.label5.Location = new Point(321, 45);
      this.label5.Name = "label5";
      this.label5.Size = new Size(39, 17);
      this.label5.TabIndex = 44;
      this.label5.Text = "Plus:";
      this.button6.BackColor = Color.Plum;
      this.button6.FlatStyle = FlatStyle.Flat;
      this.button6.Image = (Image) Resources.control_add_blue;
      this.button6.ImageAlign = ContentAlignment.MiddleLeft;
      this.button6.Location = new Point(17, 579);
      this.button6.Name = "button6";
      this.button6.Size = new Size(90, 27);
      this.button6.TabIndex = 63;
      this.button6.Text = "     Add ";
      this.button6.UseVisualStyleBackColor = false;
      this.button6.Click += new EventHandler(this.button6_Click);
      this.button12.BackColor = Color.LightCoral;
      this.button12.FlatStyle = FlatStyle.Flat;
      this.button12.Image = (Image) Resources.delete;
      this.button12.ImageAlign = ContentAlignment.MiddleLeft;
      this.button12.Location = new Point(258, 578);
      this.button12.Name = "button12";
      this.button12.Size = new Size(81, 27);
      this.button12.TabIndex = 62;
      this.button12.Text = "    Delete";
      this.button12.UseVisualStyleBackColor = false;
      this.button12.Click += new EventHandler(this.button12_Click);
      this.button9.BackColor = Color.LightCyan;
      this.button9.FlatStyle = FlatStyle.Flat;
      this.button9.Image = (Image) Resources._08;
      this.button9.ImageAlign = ContentAlignment.MiddleLeft;
      this.button9.Location = new Point(608, 578);
      this.button9.Name = "button9";
      this.button9.Size = new Size(81, 27);
      this.button9.TabIndex = 64;
      this.button9.Text = "   Save";
      this.button9.UseVisualStyleBackColor = false;
      this.button9.Click += new EventHandler(this.button9_Click);
      this.button1.BackColor = Color.Plum;
      this.button1.FlatStyle = FlatStyle.Flat;
      this.button1.Image = (Image) Resources.control_add_blue;
      this.button1.ImageAlign = ContentAlignment.MiddleLeft;
      this.button1.Location = new Point(137, 579);
      this.button1.Name = "button1";
      this.button1.Size = new Size(90, 27);
      this.button1.TabIndex = 65;
      this.button1.Text = "     Add  Copy";
      this.button1.UseVisualStyleBackColor = false;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.ClientSize = new Size(707, 635);
      this.Controls.Add((Control) this.button1);
      this.Controls.Add((Control) this.button9);
      this.Controls.Add((Control) this.button6);
      this.Controls.Add((Control) this.button12);
      this.Controls.Add((Control) this.groupBox5);
      this.Controls.Add((Control) this.groupBox1);
      this.Controls.Add((Control) this.statusStrip1);
      this.Controls.Add((Control) this.groupBox4);
      this.Icon = (Icon) componentResourceManager.GetObject("$this.Icon");
      this.Name = nameof (StartItem);
      this.Text = nameof (StartItem);
      this.Load += new EventHandler(this.StartItem_Load);
      this.groupBox1.ResumeLayout(false);
      this.statusStrip1.ResumeLayout(false);
      this.statusStrip1.PerformLayout();
      ((ISupportInitialize) this.dgItems).EndInit();
      this.groupBox4.ResumeLayout(false);
      this.groupBox4.PerformLayout();
      this.toolStrip2.ResumeLayout(false);
      this.toolStrip2.PerformLayout();
      this.groupBox5.ResumeLayout(false);
      this.groupBox5.PerformLayout();
      ((ISupportInitialize) this.pictureBox7).EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();
    }

    private void button6_Click(object sender, EventArgs e)
    {
      if (this.CharJob.Text.Trim().Length <= 0)
      {
        int num1 = (int) MessageBox.Show("You need select Job", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        try
        {
          ItemPicker itemPicker = new ItemPicker();
          if (itemPicker.ShowDialog() != DialogResult.OK)
            return;
          this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_startitems (a_job, a_itemidx) VALUES ('" + this.JobID + "','" + itemPicker.ItemIndex.ToString() + "')");
        }
        catch
        {
          int num2 = (int) MessageBox.Show("Duplicated ItemID isn't allowed.", "Error");
        }
        this.dgItems.Rows.Clear();
        this.LoadDG(this.JobID);
        int index = this.dgItems.Rows.Count - 1;
        this.dgItems.Rows[index].Selected = true;
        this.dgItems.FirstDisplayedScrollingRowIndex = index;
      }
    }

    private void button12_Click(object sender, EventArgs e)
    {
      if (this.ItemID.Text.Trim().Length <= 0)
      {
        int num1 = (int) MessageBox.Show("You need select Item", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        int index1 = this.dgItems.CurrentRow.Index;
        int index2 = index1 - 1;
        if (MessageBox.Show("Do you want to Delete Item: " + this.ItemID.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
          return;
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_startitems WHERE a_index ='" + Convert.ToString(this.dgItems.Rows[index1].Cells["a_index"].Value) + "'");
        this.dgItems.Rows.Clear();
        this.LoadDG(this.JobID);
        try
        {
          this.dgItems.Rows[index2].Selected = true;
          this.dgItems.FirstDisplayedScrollingRowIndex = index2;
        }
        catch
        {
          int num2 = (int) MessageBox.Show("You must select a Item", "Error");
        }
      }
    }

    private void button9_Click(object sender, EventArgs e)
    {
      int index = this.dgItems.CurrentRow.Index;
      DataGridViewRow row = this.dgItems.Rows[index];
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_startitems SET a_job = '" + this.CharJob.Text + "', a_itemidx = '" + this.ItemID.Text + "', a_itemcount = '" + this.ItemCount.Text + "', a_wearpos = '" + this.ItemWearing.Text + "', a_plus = '" + this.ItemPlus.Text + "' WHERE a_index = '" + this.StartIndex.Text + "' ");
      this.dgItems.Rows.Clear();
      this.LoadDG(this.JobID);
      try
      {
        this.dgItems.Rows[index].Selected = true;
        this.dgItems.FirstDisplayedScrollingRowIndex = index;
      }
      catch
      {
        int num = (int) MessageBox.Show("You must select a Item", "Error");
      }
    }

    private void button1_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want copy to New From Index " + this.ItemID.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      if (this.ItemID.Text.Trim().Length <= 0)
      {
        int num1 = (int) MessageBox.Show("No data to select", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DROP TABLE IF EXISTS tempTable;CREATE TEMPORARY TABLE tempTable ENGINE=MEMORY SELECT * FROM t_startitems WHERE a_index=" + this.StartIndex.Text + ";SELECT a_index FROM tempTable;UPDATE tempTable SET a_index=(SELECT a_index from t_startitems ORDER BY a_index DESC LIMIT 1)+1; SELECT a_index FROM tempTable;INSERT INTO t_startitems SELECT * FROM tempTable;");
        int num2 = (int) MessageBox.Show("Successful copy", "Completed", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
        this.dgItems.Rows.Clear();
        this.LoadDG(this.JobID);
        int index = this.dgItems.Rows.Count - 1;
        this.dgItems.Rows[index].Selected = true;
        this.dgItems.FirstDisplayedScrollingRowIndex = index;
      }
    }

    private void button4_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.ItemID.Text = itemPicker.ItemIndex.ToString();
    }
  }
}
