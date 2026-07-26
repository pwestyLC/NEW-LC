// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MoonstoneEditor
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using MySqlConnector;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools
{
  public class MoonstoneEditor : Form
  {
    public static Connection connection = new Connection();
    private string Host = MoonstoneEditor.connection.Settings.SqlHost;
    private string User = MoonstoneEditor.connection.Settings.SqlUser;
    private string Password = MoonstoneEditor.connection.Settings.SqlPassword;
    private string Database = MoonstoneEditor.connection.Settings.SqlDatabase;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    public string rowName = "a_index";
    public string[] menuArray = new string[2]
    {
      "a_index",
      "a_name"
    };
    public string MoonstoneID = "";
    private ExportLodHandle exportLodHandle = new ExportLodHandle();
    private IContainer components = (IContainer) null;
    public string name;
    public int index;
    public string test2;
    public List<string> lArrayLevel;
    public List<string> lArrayProb;
    private ToolStripStatusLabel toolStripStatusLabel1;
    private Button button5;
    private Button button4;
    private Button button3;
    private Button button2;
    private GroupBox groupBox1;
    private Button button1;
    private ToolStripButton toolStripButton1;
    private ToolStripSeparator toolStripSeparator6;
    private ToolStripButton btnAddItems;
    private ToolStripSeparator toolStripSeparator1;
    private ToolStripButton btnDeleteSelected;
    private StatusStrip statusStrip1;
    private DataGridView dgItems;
    private DataGridViewImageColumn Column7;
    private DataGridViewTextBoxColumn GiftIndex;
    private DataGridViewTextBoxColumn ItemName;
    private DataGridViewTextBoxColumn Type;
    private DataGridViewTextBoxColumn GiftCount;
    private DataGridViewTextBoxColumn GiftProb;
    private DataGridViewTextBoxColumn GiftFlag;
    private DataGridViewTextBoxColumn ID;
    private GroupBox groupBox4;
    private ToolStrip toolStrip2;
    private ToolStripMenuItem exportlodToolStripMenuItem;
    private ToolStripMenuItem fileExportToolStripMenuItem;
    private MenuStrip menuStrip1;

    public MoonstoneEditor() => this.InitializeComponent();

    private void MoonstoneEditor_Load(object sender, EventArgs e)
    {
      this.button1.BackgroundImage = (Image) this.databaseHandle.IconFast(723);
      this.button2.BackgroundImage = (Image) this.databaseHandle.IconFast(2545);
      this.button3.BackgroundImage = (Image) this.databaseHandle.IconFast(2546);
      this.button4.BackgroundImage = (Image) this.databaseHandle.IconFast(2547);
      this.button5.BackgroundImage = (Image) this.databaseHandle.IconFast(2548);
      this.toolStripStatusLabel1.Text = "Choose your category!";
      this.toolStripStatusLabel1.ForeColor = Color.Maroon;
    }

    public void LoadDG(string MoonstoneIDX)
    {
      Stopwatch stopwatch = new Stopwatch();
      stopwatch.Start();
      if (this.MoonstoneID != "")
      {
        this.toolStripStatusLabel1.Text = "Ready";
        this.toolStripStatusLabel1.ForeColor = Color.Black;
      }
      this.toolStripStatusLabel1.Text = "Load Items ...";
      this.dgItems.Rows.Clear();
      string str1 = "SELECT * FROM t_moonstone_reward WHERE a_type ='+" + MoonstoneIDX + "' ORDER BY a_index";
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

    private void btnDeleteSelected_Click(object sender, EventArgs e)
    {
      int index = this.dgItems.CurrentRow.Index;
      DataGridViewRow row = this.dgItems.Rows[index];
      string str1 = Convert.ToString(row.Cells["GiftIndex"].Value);
      string str2 = Convert.ToString(row.Cells["Type"].Value);
      string str3 = Convert.ToString(row.Cells["GiftCount"].Value);
      string str4 = Convert.ToString(row.Cells["GiftProb"].Value);
      string str5 = Convert.ToString(row.Cells["GiftFlag"].Value);
      string str6 = Convert.ToString(row.Cells["ID"].Value);
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_moonstone_reward SET a_type = '" + str2 + "', a_giftindex = '" + str1 + "', a_giftcount = '" + str3 + "', a_giftprob = '" + str4 + "', a_giftflag = '" + str5 + "' WHERE a_index = '" + str6 + "' ");
      this.dgItems.Rows.Clear();
      this.LoadDG(this.MoonstoneID);
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
      this.MoonstoneID = "723";
      this.LoadDG(this.MoonstoneID);
    }

    private void btnAddItems_Click(object sender, EventArgs e)
    {
      try
      {
        ItemPicker itemPicker = new ItemPicker();
        if (itemPicker.ShowDialog() != DialogResult.OK)
          return;
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_moonstone_reward (a_type, a_giftindex) VALUES ('" + this.MoonstoneID + "','" + itemPicker.ItemIndex.ToString() + "')");
      }
      catch
      {
        int num = (int) MessageBox.Show("Duplicated ItemID isn't allowed.", "Error");
      }
      this.dgItems.Rows.Clear();
      this.LoadDG(this.MoonstoneID);
      int index = this.dgItems.Rows.Count - 1;
      this.dgItems.Rows[index].Selected = true;
      this.dgItems.FirstDisplayedScrollingRowIndex = index;
    }

    private void toolStripButton1_Click(object sender, EventArgs e)
    {
      int index1 = this.dgItems.CurrentRow.Index;
      int index2 = index1 - 1;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_moonstone_reward WHERE a_index ='" + Convert.ToString(this.dgItems.Rows[index1].Cells["ID"].Value) + "'");
      this.dgItems.Rows.Clear();
      this.LoadDG(this.MoonstoneID);
      try
      {
        this.dgItems.Rows[index2].Selected = true;
        this.dgItems.FirstDisplayedScrollingRowIndex = index2;
      }
      catch
      {
        int num = (int) MessageBox.Show("You must select a Item", "Error");
      }
    }

    private void button2_Click(object sender, EventArgs e)
    {
      this.MoonstoneID = "2545";
      this.LoadDG(this.MoonstoneID);
    }

    private void button3_Click(object sender, EventArgs e)
    {
      this.MoonstoneID = "2546";
      this.LoadDG(this.MoonstoneID);
    }

    private void button4_Click(object sender, EventArgs e)
    {
      this.MoonstoneID = "2547";
      this.LoadDG(this.MoonstoneID);
    }

    private void button5_Click(object sender, EventArgs e)
    {
      this.MoonstoneID = "2548";
      this.LoadDG(this.MoonstoneID);
    }

    private void exportlodToolStripMenuItem_Click(object sender, EventArgs e)
    {
      new LodExporter.LodExporter().Show();
    }

    public void SaveFile(string fileName)
    {
      BinaryWriter binaryWriter = new BinaryWriter((Stream) File.Create(fileName));
      string str = "SELECT a_giftindex FROM t_moonstone_reward ORDER BY a_type";
      MySqlConnection mySqlConnection = new MySqlConnection("datasource=" + this.Host + ";Port=3306;User ID="  + this.User + ";Password=" + this.Password + ";Database=" + this.Database + ";Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;");
      MySqlCommand command = mySqlConnection.CreateCommand();
      command.CommandText = str;
      mySqlConnection.Open();
      MySqlDataReader mySqlDataReader = command.ExecuteReader();
      while (mySqlDataReader.Read())
      {
        string s = mySqlDataReader.GetValue(0).ToString();
        binaryWriter.Write(int.Parse(s));
      }
      mySqlConnection.Close();
      binaryWriter.Close();
    }

    private void toolStripStatusLabel1_Click(object sender, EventArgs e)
    {
    }

    private void exportlodToolStripMenuItem_Click_1(object sender, EventArgs e)
    {
      this.exportLodHandle.ExportMoonstoneLOD_V2();
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (MoonstoneEditor));
      this.toolStripStatusLabel1 = new ToolStripStatusLabel();
      this.button5 = new Button();
      this.button4 = new Button();
      this.button3 = new Button();
      this.button2 = new Button();
      this.groupBox1 = new GroupBox();
      this.button1 = new Button();
      this.toolStripButton1 = new ToolStripButton();
      this.toolStripSeparator6 = new ToolStripSeparator();
      this.btnAddItems = new ToolStripButton();
      this.toolStripSeparator1 = new ToolStripSeparator();
      this.btnDeleteSelected = new ToolStripButton();
      this.statusStrip1 = new StatusStrip();
      this.dgItems = new DataGridView();
      this.Column7 = new DataGridViewImageColumn();
      this.GiftIndex = new DataGridViewTextBoxColumn();
      this.ItemName = new DataGridViewTextBoxColumn();
      this.Type = new DataGridViewTextBoxColumn();
      this.GiftCount = new DataGridViewTextBoxColumn();
      this.GiftProb = new DataGridViewTextBoxColumn();
      this.GiftFlag = new DataGridViewTextBoxColumn();
      this.ID = new DataGridViewTextBoxColumn();
      this.groupBox4 = new GroupBox();
      this.toolStrip2 = new ToolStrip();
      this.exportlodToolStripMenuItem = new ToolStripMenuItem();
      this.fileExportToolStripMenuItem = new ToolStripMenuItem();
      this.menuStrip1 = new MenuStrip();
      this.groupBox1.SuspendLayout();
      this.statusStrip1.SuspendLayout();
      ((ISupportInitialize) this.dgItems).BeginInit();
      this.groupBox4.SuspendLayout();
      this.toolStrip2.SuspendLayout();
      this.menuStrip1.SuspendLayout();
      this.SuspendLayout();
      this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
      this.toolStripStatusLabel1.Size = new Size(39, 17);
      this.toolStripStatusLabel1.Text = "Ready";
      this.button5.FlatStyle = FlatStyle.Flat;
      this.button5.Location = new Point(158, 17);
      this.button5.Name = "button5";
      this.button5.Size = new Size(32, 32);
      this.button5.TabIndex = 49;
      this.button5.UseVisualStyleBackColor = true;
      this.button5.Click += new EventHandler(this.button5_Click);
      this.button4.FlatStyle = FlatStyle.Flat;
      this.button4.Location = new Point(120, 17);
      this.button4.Name = "button4";
      this.button4.Size = new Size(32, 32);
      this.button4.TabIndex = 48;
      this.button4.UseVisualStyleBackColor = true;
      this.button4.Click += new EventHandler(this.button4_Click);
      this.button3.FlatStyle = FlatStyle.Flat;
      this.button3.Location = new Point(44, 17);
      this.button3.Name = "button3";
      this.button3.Size = new Size(32, 32);
      this.button3.TabIndex = 47;
      this.button3.UseVisualStyleBackColor = true;
      this.button3.Click += new EventHandler(this.button3_Click);
      this.button2.FlatStyle = FlatStyle.Flat;
      this.button2.Location = new Point(6, 17);
      this.button2.Name = "button2";
      this.button2.Size = new Size(32, 32);
      this.button2.TabIndex = 46;
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.groupBox1.Controls.Add((Control) this.button5);
      this.groupBox1.Controls.Add((Control) this.button4);
      this.groupBox1.Controls.Add((Control) this.button3);
      this.groupBox1.Controls.Add((Control) this.button1);
      this.groupBox1.Controls.Add((Control) this.button2);
      this.groupBox1.Location = new Point(14, 27);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(200, 55);
      this.groupBox1.TabIndex = 51;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Category";
      this.button1.FlatStyle = FlatStyle.Flat;
      this.button1.Location = new Point(82, 17);
      this.button1.Name = "button1";
      this.button1.Size = new Size(32, 32);
      this.button1.TabIndex = 45;
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.toolStripButton1.DisplayStyle = ToolStripItemDisplayStyle.Text;
      this.toolStripButton1.ImageTransparentColor = Color.Magenta;
      this.toolStripButton1.Name = "toolStripButton1";
      this.toolStripButton1.Size = new Size(91, 22);
      this.toolStripButton1.Text = "Delete Selected";
      this.toolStripButton1.Click += new EventHandler(this.toolStripButton1_Click);
      this.toolStripSeparator6.Name = "toolStripSeparator6";
      this.toolStripSeparator6.Size = new Size(6, 25);
      this.btnAddItems.DisplayStyle = ToolStripItemDisplayStyle.Text;
      this.btnAddItems.ImageTransparentColor = Color.Magenta;
      this.btnAddItems.Name = "btnAddItems";
      this.btnAddItems.Size = new Size(60, 22);
      this.btnAddItems.Text = "Add Item";
      this.btnAddItems.Click += new EventHandler(this.btnAddItems_Click);
      this.toolStripSeparator1.Name = "toolStripSeparator1";
      this.toolStripSeparator1.Size = new Size(6, 25);
      this.btnDeleteSelected.DisplayStyle = ToolStripItemDisplayStyle.Text;
      this.btnDeleteSelected.ImageTransparentColor = Color.Magenta;
      this.btnDeleteSelected.Name = "btnDeleteSelected";
      this.btnDeleteSelected.Size = new Size(62, 22);
      this.btnDeleteSelected.Text = "Save Item";
      this.btnDeleteSelected.Click += new EventHandler(this.btnDeleteSelected_Click);
      this.statusStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.toolStripStatusLabel1
      });
      this.statusStrip1.Location = new Point(0, 562);
      this.statusStrip1.Name = "statusStrip1";
      this.statusStrip1.Size = new Size(707, 22);
      this.statusStrip1.TabIndex = 52;
      this.statusStrip1.Text = "statusStrip1";
      this.dgItems.AllowUserToAddRows = false;
      this.dgItems.AllowUserToDeleteRows = false;
      this.dgItems.BackgroundColor = SystemColors.Control;
      this.dgItems.BorderStyle = BorderStyle.None;
      this.dgItems.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dgItems.Columns.AddRange((DataGridViewColumn) this.Column7, (DataGridViewColumn) this.GiftIndex, (DataGridViewColumn) this.ItemName, (DataGridViewColumn) this.Type, (DataGridViewColumn) this.GiftCount, (DataGridViewColumn) this.GiftProb, (DataGridViewColumn) this.GiftFlag, (DataGridViewColumn) this.ID);
      this.dgItems.Dock = DockStyle.Fill;
      this.dgItems.EnableHeadersVisualStyles = false;
      this.dgItems.Location = new Point(3, 16);
      this.dgItems.Name = "dgItems";
      this.dgItems.RowHeadersVisible = false;
      this.dgItems.RowTemplate.Height = 32;
      this.dgItems.Size = new Size(678, 427);
      this.dgItems.TabIndex = 0;
      this.Column7.HeaderText = "";
      this.Column7.Name = "Column7";
      this.Column7.Width = 32;
      this.GiftIndex.HeaderText = "ID";
      this.GiftIndex.Name = "GiftIndex";
      this.GiftIndex.Width = 50;
      this.ItemName.HeaderText = "ItemName";
      this.ItemName.Name = "ItemName";
      this.ItemName.ReadOnly = true;
      this.ItemName.Width = 275;
      this.Type.HeaderText = "Type";
      this.Type.Name = "Type";
      this.Type.Visible = false;
      this.Type.Width = 75;
      this.GiftCount.HeaderText = "GiftCount";
      this.GiftCount.Name = "GiftCount";
      this.GiftProb.HeaderText = "GiftProb";
      this.GiftProb.Name = "GiftProb";
      this.GiftFlag.HeaderText = "GiftFlag";
      this.GiftFlag.Name = "GiftFlag";
      this.ID.HeaderText = "Index";
      this.ID.Name = "ID";
      this.ID.Visible = false;
      this.ID.Width = 60;
      this.groupBox4.Controls.Add((Control) this.dgItems);
      this.groupBox4.Controls.Add((Control) this.toolStrip2);
      this.groupBox4.Location = new Point(11, 88);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Size = new Size(684, 471);
      this.groupBox4.TabIndex = 50;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "Items";
      this.toolStrip2.Dock = DockStyle.Bottom;
      this.toolStrip2.GripStyle = ToolStripGripStyle.Hidden;
      this.toolStrip2.Items.AddRange(new ToolStripItem[5]
      {
        (ToolStripItem) this.btnDeleteSelected,
        (ToolStripItem) this.toolStripSeparator1,
        (ToolStripItem) this.btnAddItems,
        (ToolStripItem) this.toolStripSeparator6,
        (ToolStripItem) this.toolStripButton1
      });
      this.toolStrip2.Location = new Point(3, 443);
      this.toolStrip2.Name = "toolStrip2";
      this.toolStrip2.Size = new Size(678, 25);
      this.toolStrip2.TabIndex = 1;
      this.toolStrip2.Text = "toolStrip2";
      this.exportlodToolStripMenuItem.Name = "exportlodToolStripMenuItem";
      this.exportlodToolStripMenuItem.Size = new Size(131, 22);
      this.exportlodToolStripMenuItem.Text = "Export .lod";
      this.exportlodToolStripMenuItem.Click += new EventHandler(this.exportlodToolStripMenuItem_Click_1);
      this.fileExportToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.exportlodToolStripMenuItem
      });
      this.fileExportToolStripMenuItem.Name = "fileExportToolStripMenuItem";
      this.fileExportToolStripMenuItem.Size = new Size(74, 20);
      this.fileExportToolStripMenuItem.Text = "File Export";
      this.menuStrip1.AllowMerge = false;
      this.menuStrip1.BackColor = SystemColors.ButtonHighlight;
      this.menuStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.fileExportToolStripMenuItem
      });
      this.menuStrip1.Location = new Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new Size(707, 24);
      this.menuStrip1.TabIndex = 49;
      this.menuStrip1.Text = "menuStrip1";
      this.ClientSize = new Size(707, 584);
      this.Controls.Add((Control) this.groupBox1);
      this.Controls.Add((Control) this.statusStrip1);
      this.Controls.Add((Control) this.groupBox4);
      this.Controls.Add((Control) this.menuStrip1);
      this.Icon = (Icon) componentResourceManager.GetObject("$this.Icon");
      this.Name = nameof (MoonstoneEditor);
      this.Text = nameof (MoonstoneEditor);
      this.Load += new EventHandler(this.MoonstoneEditor_Load);
      this.groupBox1.ResumeLayout(false);
      this.statusStrip1.ResumeLayout(false);
      this.statusStrip1.PerformLayout();
      ((ISupportInitialize) this.dgItems).EndInit();
      this.groupBox4.ResumeLayout(false);
      this.groupBox4.PerformLayout();
      this.toolStrip2.ResumeLayout(false);
      this.toolStrip2.PerformLayout();
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
