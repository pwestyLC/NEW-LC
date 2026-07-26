// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.LacaBall.LacaBall
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
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.LacaBall
{
  public class LacaBall : Form
  {
    public int LacaballItemIndex = -1;
    public static Connection connection = new Connection();
    private string Host = LcDevPack_TeamDamonA.Tools.MemoryWorker.LacaBall.LacaBall.connection.Settings.SqlHost;
    private string User = LcDevPack_TeamDamonA.Tools.MemoryWorker.LacaBall.LacaBall.connection.Settings.SqlUser;
    private string Password = LcDevPack_TeamDamonA.Tools.MemoryWorker.LacaBall.LacaBall.connection.Settings.SqlPassword;
    private string Database = LcDevPack_TeamDamonA.Tools.MemoryWorker.LacaBall.LacaBall.connection.Settings.SqlDatabase;
    private string DB_Database = LcDevPack_TeamDamonA.Tools.MemoryWorker.LacaBall.LacaBall.connection.Settings.SqlDbDatabase;
    public bool ISDataGridLoaded = false;
    public bool ISFinished = false;
    public bool completed = false;
    public int ItemIndx = -1;
    public static List<t_lcball> LcBallList = new List<t_lcball>();
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    private IContainer components = (IContainer) null;
    private GroupBox groupBox1;
    private PictureBox pbLacaItemAll;
    private PictureBox pbLacaItem5;
    private PictureBox pbLacaItem4;
    private PictureBox pbLacaItem3;
    private PictureBox pbLacaItem2;
    private PictureBox pbLacaItem1;
    private DataGridView dataGridView1;
    private Button btnAdd;
    private Button btnDelete;
    private Button btnEdit;
    private Button btnCopy;
    private PictureBox pbMoveUp;
    private PictureBox pbMoveDown;
    private GroupBox gbItem;
    private Label lblItemRemain;
    private Label lblItemMax;
    private TextBox tbItemMax;
    private TextBox tbItemRemain;
    private PictureBox pbLacaItem8;
    private PictureBox pbLacaItem7;
    private PictureBox pbLacaItem6;
    private StatusStrip statusStrip1;
    private ToolStripStatusLabel toolStripStatusLabel1;
    private DataGridViewImageColumn ItemImg;
    private DataGridViewTextBoxColumn ItemOrder;
    private DataGridViewTextBoxColumn CourseCode;
    private DataGridViewTextBoxColumn Order;
    private DataGridViewTextBoxColumn ItemIndex;
    private DataGridViewTextBoxColumn ItemName;
    private DataGridViewTextBoxColumn ItemCount;
    private DataGridViewTextBoxColumn TokenIndex;

    public LacaBall() => this.InitializeComponent();

    public void LoadDG(int LacaballItemidx)
    {
      Stopwatch stopwatch = new Stopwatch();
      stopwatch.Start();
      this.dataGridView1.Rows.Clear();
      string str = "select a_item_order, a_tocken_index, a_course_code, a_order, a_item_index, a_item_count, a_item_max, a_item_remain from t_lcball WHERE a_tocken_index = " + LacaballItemidx.ToString() + " order by a_course_code ;";
            MySqlConnection mySqlConnection = new MySqlConnection(
          "datasource=" + this.Host +
          ";port=3306;" +
          "username=" + this.User +
          ";password=" + this.Password +
          ";database=" + this.DB_Database +
          ";Charset=utf8mb4;" +   // use a charset supported by .NET
          "SslMode=Preferred;" +
          "TlsVersion=Tls12;"
      );
            MySqlCommand command = mySqlConnection.CreateCommand();
      command.CommandText = str;
      mySqlConnection.Open();
      MySqlDataReader mySqlDataReader = command.ExecuteReader();
      while (mySqlDataReader.Read())
      {
        t_lcball tLcball = new t_lcball();
        tLcball.a_item_order = Convert.ToInt32(mySqlDataReader.GetValue(0).ToString());
        tLcball.a_tocken_index = Convert.ToInt32(mySqlDataReader.GetValue(1).ToString());
        tLcball.a_course_code = Convert.ToInt32(mySqlDataReader.GetValue(2).ToString());
        tLcball.a_order = Convert.ToInt32(mySqlDataReader.GetValue(3).ToString());
        tLcball.a_item_index = Convert.ToInt32(mySqlDataReader.GetValue(4).ToString());
        tLcball.a_item_count = Convert.ToInt32(mySqlDataReader.GetValue(5).ToString());
        tLcball.a_item_max = Convert.ToInt32(mySqlDataReader.GetValue(6).ToString());
        tLcball.a_item_remain = Convert.ToInt32(mySqlDataReader.GetValue(7).ToString());
        LcDevPack_TeamDamonA.Tools.MemoryWorker.LacaBall.LacaBall.LcBallList.Add(tLcball);
        string s = mySqlDataReader.GetValue(4).ToString();
        int aItemIndex = tLcball.a_item_index;
        this.dataGridView1.Rows.Add((object) new Bitmap((Image) this.databaseHandle.IconFast(int.Parse(s)), 20, 20), (object) tLcball.a_item_order, (object) tLcball.a_course_code, (object) tLcball.a_order, (object) tLcball.a_item_index, (object) this.databaseHandle.ItemNameFast(int.Parse(s)), (object) tLcball.a_item_count);
        this.tbItemMax.Text = tLcball.a_item_max.ToString();
        this.tbItemRemain.Text = tLcball.a_item_remain.ToString();
      }
      mySqlConnection.Close();
      this.ISDataGridLoaded = true;
      stopwatch.Stop();
      TimeSpan elapsed = stopwatch.Elapsed;
      string.Format("{0:00}:{1:00}:{2:00}.{3:00}", (object) elapsed.Hours, (object) elapsed.Minutes, (object) elapsed.Seconds, (object) (elapsed.Milliseconds / 10));
      this.toolStripStatusLabel1.Text = "Ready";
      this.toolStripStatusLabel1.ForeColor = Color.LimeGreen;
    }

    public void UpdatePictureBox()
    {
    }

    private void pbMoveUp_Click(object sender, EventArgs e)
    {
    }

    private void pbMoveDown_Click(object sender, EventArgs e)
    {
    }

    private void btnAdd_Click(object sender, EventArgs e)
    {
    }

    private void btnEdit_Click(object sender, EventArgs e)
    {
    }

    private void btnCopy_Click(object sender, EventArgs e)
    {
    }

    private void btnDelete_Click(object sender, EventArgs e)
    {
    }

    private void LacaBall_Load(object sender, EventArgs e)
    {
      this.MaximumSize = this.Size;
      this.MinimumSize = this.Size;
      this.pbLacaItem1.BackgroundImage = (Image) this.databaseHandle.IconFast(5123);
      this.pbLacaItem2.BackgroundImage = (Image) this.databaseHandle.IconFast(5124);
      this.pbLacaItem3.BackgroundImage = (Image) this.databaseHandle.IconFast(6653);
      this.pbLacaItem4.BackgroundImage = (Image) this.databaseHandle.IconFast(2545);
      this.pbLacaItem5.BackgroundImage = (Image) this.databaseHandle.IconFast(2546);
      this.pbLacaItem6.BackgroundImage = (Image) this.databaseHandle.IconFast(2547);
      this.pbLacaItem7.BackgroundImage = (Image) this.databaseHandle.IconFast(2548);
      this.pbLacaItem8.BackgroundImage = (Image) this.databaseHandle.IconFast(6092);
      this.toolStripStatusLabel1.Text = "Choose your Item!";
      this.toolStripStatusLabel1.ForeColor = Color.Red;
    }

    private void pbLacaItem1_Click(object sender, EventArgs e)
    {
      this.LacaballItemIndex = 5123;
      this.LoadDG(5123);
    }

    private void pbLacaItem2_Click(object sender, EventArgs e)
    {
      this.LacaballItemIndex = 5124;
      this.LoadDG(5124);
    }

    private void pbLacaItem3_Click(object sender, EventArgs e)
    {
      this.LacaballItemIndex = 6653;
      this.LoadDG(6653);
    }

    private void pbLacaItem4_Click(object sender, EventArgs e)
    {
      this.LacaballItemIndex = 2545;
      this.LoadDG(2545);
    }

    private void pbLacaItem5_Click(object sender, EventArgs e)
    {
      this.LacaballItemIndex = 2546;
      this.LoadDG(2546);
    }

    private void pbLacaItemAll_Click(object sender, EventArgs e)
    {
      this.LacaballItemIndex = 2547;
      this.LoadDG(2547);
    }

    private void pbLacaItem6_Click(object sender, EventArgs e)
    {
      this.LacaballItemIndex = 2548;
      this.LoadDG(2548);
    }

    private void pbLacaItem7_Click(object sender, EventArgs e)
    {
      this.LacaballItemIndex = 6092;
      this.LoadDG(6092);
    }

    private void pbLacaItem8_Click(object sender, EventArgs e)
    {
      this.LacaballItemIndex = 6092;
      this.LoadDG(6092);
    }

    private void dataGridView1_CellClick(object sender, DataGridViewCellEventArgs e)
    {
    }

    private void dataGridView1_CellValueChanged(object sender, DataGridViewCellEventArgs e)
    {
      t_lcball tLcball = new t_lcball();
      if (!this.ISDataGridLoaded || this.ItemIndx == int.Parse(this.dataGridView1.Rows[e.RowIndex].Cells["ItemIndex"].Value.ToString()) || !(this.dataGridView1.Rows[e.RowIndex].Cells["ItemIndex"].Value.ToString() != "-1") && !(this.dataGridView1.Rows[e.RowIndex].Cells["ItemIndex"].Value.ToString() != "0"))
        return;
      this.ItemIndx = int.Parse(this.dataGridView1.Rows[e.RowIndex].Cells["ItemIndex"].Value.ToString());
      if (!this.ISFinished)
      {
        this.ISFinished = true;
        this.dataGridView1.Rows[e.RowIndex].SetValues((object) new Bitmap((Image) this.databaseHandle.IconFast(this.ItemIndx), 20, 20));
      }
      else if (this.ISDataGridLoaded && this.ISFinished)
        this.dataGridView1.Rows[e.RowIndex].SetValues((object) new Bitmap((Image) this.databaseHandle.IconFast(this.ItemIndx), 20, 20));
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
      this.pbLacaItem8 = new PictureBox();
      this.pbLacaItem7 = new PictureBox();
      this.pbLacaItem6 = new PictureBox();
      this.pbLacaItemAll = new PictureBox();
      this.pbLacaItem5 = new PictureBox();
      this.pbLacaItem4 = new PictureBox();
      this.pbLacaItem3 = new PictureBox();
      this.pbLacaItem2 = new PictureBox();
      this.pbLacaItem1 = new PictureBox();
      this.dataGridView1 = new DataGridView();
      this.ItemImg = new DataGridViewImageColumn();
      this.ItemOrder = new DataGridViewTextBoxColumn();
      this.CourseCode = new DataGridViewTextBoxColumn();
      this.Order = new DataGridViewTextBoxColumn();
      this.ItemIndex = new DataGridViewTextBoxColumn();
      this.ItemName = new DataGridViewTextBoxColumn();
      this.ItemCount = new DataGridViewTextBoxColumn();
      this.TokenIndex = new DataGridViewTextBoxColumn();
      this.btnAdd = new Button();
      this.btnDelete = new Button();
      this.btnEdit = new Button();
      this.btnCopy = new Button();
      this.pbMoveDown = new PictureBox();
      this.pbMoveUp = new PictureBox();
      this.gbItem = new GroupBox();
      this.lblItemRemain = new Label();
      this.lblItemMax = new Label();
      this.tbItemMax = new TextBox();
      this.tbItemRemain = new TextBox();
      this.statusStrip1 = new StatusStrip();
      this.toolStripStatusLabel1 = new ToolStripStatusLabel();
      this.groupBox1.SuspendLayout();
      ((ISupportInitialize) this.pbLacaItem8).BeginInit();
      ((ISupportInitialize) this.pbLacaItem7).BeginInit();
      ((ISupportInitialize) this.pbLacaItem6).BeginInit();
      ((ISupportInitialize) this.pbLacaItemAll).BeginInit();
      ((ISupportInitialize) this.pbLacaItem5).BeginInit();
      ((ISupportInitialize) this.pbLacaItem4).BeginInit();
      ((ISupportInitialize) this.pbLacaItem3).BeginInit();
      ((ISupportInitialize) this.pbLacaItem2).BeginInit();
      ((ISupportInitialize) this.pbLacaItem1).BeginInit();
      ((ISupportInitialize) this.dataGridView1).BeginInit();
      ((ISupportInitialize) this.pbMoveDown).BeginInit();
      ((ISupportInitialize) this.pbMoveUp).BeginInit();
      this.gbItem.SuspendLayout();
      this.statusStrip1.SuspendLayout();
      this.SuspendLayout();
      this.groupBox1.Controls.Add((Control) this.pbLacaItem8);
      this.groupBox1.Controls.Add((Control) this.pbLacaItem7);
      this.groupBox1.Controls.Add((Control) this.pbLacaItem6);
      this.groupBox1.Controls.Add((Control) this.pbLacaItemAll);
      this.groupBox1.Controls.Add((Control) this.pbLacaItem5);
      this.groupBox1.Controls.Add((Control) this.pbLacaItem4);
      this.groupBox1.Controls.Add((Control) this.pbLacaItem3);
      this.groupBox1.Controls.Add((Control) this.pbLacaItem2);
      this.groupBox1.Controls.Add((Control) this.pbLacaItem1);
      this.groupBox1.Location = new Point(12, 25);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(337, 69);
      this.groupBox1.TabIndex = 0;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "LacaBall Items Sort";
      this.pbLacaItem8.BackgroundImageLayout = ImageLayout.Stretch;
      this.pbLacaItem8.Location = new Point(227, 19);
      this.pbLacaItem8.Name = "pbLacaItem8";
      this.pbLacaItem8.Size = new Size(32, 32);
      this.pbLacaItem8.TabIndex = 8;
      this.pbLacaItem8.TabStop = false;
      this.pbLacaItem8.Click += new EventHandler(this.pbLacaItem8_Click);
      this.pbLacaItem7.BackgroundImageLayout = ImageLayout.Stretch;
      this.pbLacaItem7.Location = new Point(197, 19);
      this.pbLacaItem7.Name = "pbLacaItem7";
      this.pbLacaItem7.Size = new Size(32, 32);
      this.pbLacaItem7.TabIndex = 7;
      this.pbLacaItem7.TabStop = false;
      this.pbLacaItem7.Click += new EventHandler(this.pbLacaItem7_Click);
      this.pbLacaItem6.BackgroundImageLayout = ImageLayout.Stretch;
      this.pbLacaItem6.Location = new Point(167, 19);
      this.pbLacaItem6.Name = "pbLacaItem6";
      this.pbLacaItem6.Size = new Size(32, 32);
      this.pbLacaItem6.TabIndex = 6;
      this.pbLacaItem6.TabStop = false;
      this.pbLacaItem6.Click += new EventHandler(this.pbLacaItem6_Click);
      this.pbLacaItemAll.BackgroundImageLayout = ImageLayout.Stretch;
      this.pbLacaItemAll.Location = new Point(286, 19);
      this.pbLacaItemAll.Name = "pbLacaItemAll";
      this.pbLacaItemAll.Size = new Size(32, 32);
      this.pbLacaItemAll.TabIndex = 5;
      this.pbLacaItemAll.TabStop = false;
      this.pbLacaItemAll.Click += new EventHandler(this.pbLacaItemAll_Click);
      this.pbLacaItem5.BackgroundImageLayout = ImageLayout.Stretch;
      this.pbLacaItem5.Location = new Point(137, 19);
      this.pbLacaItem5.Name = "pbLacaItem5";
      this.pbLacaItem5.Size = new Size(32, 32);
      this.pbLacaItem5.TabIndex = 4;
      this.pbLacaItem5.TabStop = false;
      this.pbLacaItem5.Click += new EventHandler(this.pbLacaItem5_Click);
      this.pbLacaItem4.BackgroundImageLayout = ImageLayout.Stretch;
      this.pbLacaItem4.Location = new Point(107, 19);
      this.pbLacaItem4.Name = "pbLacaItem4";
      this.pbLacaItem4.Size = new Size(32, 32);
      this.pbLacaItem4.TabIndex = 3;
      this.pbLacaItem4.TabStop = false;
      this.pbLacaItem4.Tag = (object) "Castle Siege Token";
      this.pbLacaItem4.Click += new EventHandler(this.pbLacaItem4_Click);
      this.pbLacaItem3.BackgroundImageLayout = ImageLayout.Stretch;
      this.pbLacaItem3.Location = new Point(77, 19);
      this.pbLacaItem3.Name = "pbLacaItem3";
      this.pbLacaItem3.Size = new Size(32, 32);
      this.pbLacaItem3.TabIndex = 2;
      this.pbLacaItem3.TabStop = false;
      this.pbLacaItem3.Tag = (object) "Gold Token";
      this.pbLacaItem3.Click += new EventHandler(this.pbLacaItem3_Click);
      this.pbLacaItem2.BackgroundImageLayout = ImageLayout.Stretch;
      this.pbLacaItem2.Location = new Point(47, 19);
      this.pbLacaItem2.Name = "pbLacaItem2";
      this.pbLacaItem2.Size = new Size(32, 32);
      this.pbLacaItem2.TabIndex = 1;
      this.pbLacaItem2.TabStop = false;
      this.pbLacaItem2.Tag = (object) "Token";
      this.pbLacaItem2.Click += new EventHandler(this.pbLacaItem2_Click);
      this.pbLacaItem1.BackgroundImageLayout = ImageLayout.Stretch;
      this.pbLacaItem1.Location = new Point(17, 19);
      this.pbLacaItem1.Name = "pbLacaItem1";
      this.pbLacaItem1.Size = new Size(32, 32);
      this.pbLacaItem1.TabIndex = 0;
      this.pbLacaItem1.TabStop = false;
      this.pbLacaItem1.Tag = (object) "All";
      this.pbLacaItem1.Click += new EventHandler(this.pbLacaItem1_Click);
      this.dataGridView1.AllowUserToAddRows = false;
      this.dataGridView1.AllowUserToDeleteRows = false;
      this.dataGridView1.BorderStyle = BorderStyle.None;
      this.dataGridView1.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dataGridView1.Columns.AddRange((DataGridViewColumn) this.ItemImg, (DataGridViewColumn) this.ItemOrder, (DataGridViewColumn) this.CourseCode, (DataGridViewColumn) this.Order, (DataGridViewColumn) this.ItemIndex, (DataGridViewColumn) this.ItemName, (DataGridViewColumn) this.ItemCount, (DataGridViewColumn) this.TokenIndex);
      this.dataGridView1.EnableHeadersVisualStyles = false;
      this.dataGridView1.Location = new Point(13, 100);
      this.dataGridView1.Name = "dataGridView1";
      this.dataGridView1.RowHeadersVisible = false;
      this.dataGridView1.Size = new Size(480, 354);
      this.dataGridView1.TabIndex = 1;
      this.dataGridView1.CellClick += new DataGridViewCellEventHandler(this.dataGridView1_CellClick);
      this.dataGridView1.CellValueChanged += new DataGridViewCellEventHandler(this.dataGridView1_CellValueChanged);
      this.ItemImg.HeaderText = "";
      this.ItemImg.Name = "ItemImg";
      this.ItemImg.Width = 20;
      this.ItemOrder.HeaderText = "ItemOrder";
      this.ItemOrder.Name = "ItemOrder";
      this.ItemOrder.Resizable = DataGridViewTriState.False;
      this.ItemOrder.Width = 70;
      this.CourseCode.HeaderText = "CourseCode";
      this.CourseCode.Name = "CourseCode";
      this.CourseCode.Resizable = DataGridViewTriState.False;
      this.CourseCode.Width = 75;
      this.Order.HeaderText = "Order";
      this.Order.Name = "Order";
      this.Order.Resizable = DataGridViewTriState.False;
      this.Order.Width = 40;
      this.ItemIndex.HeaderText = "ItemIndex";
      this.ItemIndex.Name = "ItemIndex";
      this.ItemIndex.Resizable = DataGridViewTriState.False;
      this.ItemIndex.Width = 70;
      this.ItemName.HeaderText = "ItemName";
      this.ItemName.Name = "ItemName";
      this.ItemName.ReadOnly = true;
      this.ItemName.Width = 130;
      this.ItemCount.HeaderText = "ItemCount";
      this.ItemCount.Name = "ItemCount";
      this.ItemCount.Resizable = DataGridViewTriState.False;
      this.ItemCount.Width = 70;
      this.TokenIndex.HeaderText = "TokenIndex";
      this.TokenIndex.Name = "TokenIndex";
      this.TokenIndex.Resizable = DataGridViewTriState.False;
      this.TokenIndex.Visible = false;
      this.btnAdd.BackColor = Color.Lime;
      this.btnAdd.FlatStyle = FlatStyle.Flat;
      this.btnAdd.Location = new Point(14, 460);
      this.btnAdd.Name = "btnAdd";
      this.btnAdd.Size = new Size(90, 23);
      this.btnAdd.TabIndex = 2;
      this.btnAdd.Text = "Add";
      this.btnAdd.UseVisualStyleBackColor = false;
      this.btnAdd.Click += new EventHandler(this.btnAdd_Click);
      this.btnDelete.BackColor = Color.Red;
      this.btnDelete.FlatStyle = FlatStyle.Flat;
      this.btnDelete.Location = new Point(361, 460);
      this.btnDelete.Name = "btnDelete";
      this.btnDelete.Size = new Size(103, 23);
      this.btnDelete.TabIndex = 3;
      this.btnDelete.Text = "Delete";
      this.btnDelete.UseVisualStyleBackColor = false;
      this.btnDelete.Click += new EventHandler(this.btnDelete_Click);
      this.btnEdit.BackColor = Color.SpringGreen;
      this.btnEdit.FlatStyle = FlatStyle.Flat;
      this.btnEdit.Font = new Font("Microsoft Sans Serif", 8.25f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.btnEdit.Location = new Point(124, 460);
      this.btnEdit.Name = "btnEdit";
      this.btnEdit.Size = new Size(99, 23);
      this.btnEdit.TabIndex = 4;
      this.btnEdit.Text = "Edit";
      this.btnEdit.UseVisualStyleBackColor = false;
      this.btnEdit.Click += new EventHandler(this.btnEdit_Click);
      this.btnCopy.BackColor = SystemColors.MenuHighlight;
      this.btnCopy.FlatStyle = FlatStyle.Flat;
      this.btnCopy.Font = new Font("Microsoft Sans Serif", 8.25f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.btnCopy.Location = new Point(250, 460);
      this.btnCopy.Name = "btnCopy";
      this.btnCopy.Size = new Size(88, 23);
      this.btnCopy.TabIndex = 5;
      this.btnCopy.Text = "Copy";
      this.btnCopy.UseVisualStyleBackColor = false;
      this.btnCopy.Click += new EventHandler(this.btnCopy_Click);
      this.pbMoveDown.BackgroundImage = (Image) Resources.Arrow_Red_Down_Transparent_PNG_Clip_Art_Image;
      this.pbMoveDown.BackgroundImageLayout = ImageLayout.Stretch;
      this.pbMoveDown.Location = new Point(499, 277);
      this.pbMoveDown.Name = "pbMoveDown";
      this.pbMoveDown.Size = new Size(39, 111);
      this.pbMoveDown.TabIndex = 7;
      this.pbMoveDown.TabStop = false;
      this.pbMoveDown.Click += new EventHandler(this.pbMoveDown_Click);
      this.pbMoveUp.BackgroundImage = (Image) Resources.Arrow_Green_Down_Transparent_PNG_Clip_Art_Image;
      this.pbMoveUp.BackgroundImageLayout = ImageLayout.Stretch;
      this.pbMoveUp.Location = new Point(500, 100);
      this.pbMoveUp.Name = "pbMoveUp";
      this.pbMoveUp.Size = new Size(38, 112);
      this.pbMoveUp.TabIndex = 6;
      this.pbMoveUp.TabStop = false;
      this.pbMoveUp.Click += new EventHandler(this.pbMoveUp_Click);
      this.gbItem.Controls.Add((Control) this.lblItemRemain);
      this.gbItem.Controls.Add((Control) this.lblItemMax);
      this.gbItem.Controls.Add((Control) this.tbItemMax);
      this.gbItem.Controls.Add((Control) this.tbItemRemain);
      this.gbItem.Location = new Point(355, 24);
      this.gbItem.Name = "gbItem";
      this.gbItem.Size = new Size(115, 70);
      this.gbItem.TabIndex = 8;
      this.gbItem.TabStop = false;
      this.gbItem.Text = "ItemInfo";
      this.lblItemRemain.AutoSize = true;
      this.lblItemRemain.Location = new Point(6, 51);
      this.lblItemRemain.Name = "lblItemRemain";
      this.lblItemRemain.Size = new Size(43, 13);
      this.lblItemRemain.TabIndex = 15;
      this.lblItemRemain.Text = "Remain";
      this.lblItemMax.AutoSize = true;
      this.lblItemMax.Location = new Point(14, 20);
      this.lblItemMax.Name = "lblItemMax";
      this.lblItemMax.Size = new Size(27, 13);
      this.lblItemMax.TabIndex = 14;
      this.lblItemMax.Text = "Max";
      this.tbItemMax.Location = new Point(53, 15);
      this.tbItemMax.Name = "tbItemMax";
      this.tbItemMax.Size = new Size(54, 20);
      this.tbItemMax.TabIndex = 13;
      this.tbItemRemain.Location = new Point(53, 47);
      this.tbItemRemain.Name = "tbItemRemain";
      this.tbItemRemain.Size = new Size(54, 20);
      this.tbItemRemain.TabIndex = 12;
      this.statusStrip1.Dock = DockStyle.Top;
      this.statusStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.toolStripStatusLabel1
      });
      this.statusStrip1.Location = new Point(0, 0);
      this.statusStrip1.Name = "statusStrip1";
      this.statusStrip1.Size = new Size(545, 22);
      this.statusStrip1.TabIndex = 9;
      this.statusStrip1.Text = "statusStrip1";
      this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
      this.toolStripStatusLabel1.Size = new Size(42, 17);
      this.toolStripStatusLabel1.Text = "Ready:";
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(545, 495);
      this.Controls.Add((Control) this.statusStrip1);
      this.Controls.Add((Control) this.gbItem);
      this.Controls.Add((Control) this.pbMoveDown);
      this.Controls.Add((Control) this.pbMoveUp);
      this.Controls.Add((Control) this.btnCopy);
      this.Controls.Add((Control) this.btnEdit);
      this.Controls.Add((Control) this.btnDelete);
      this.Controls.Add((Control) this.btnAdd);
      this.Controls.Add((Control) this.dataGridView1);
      this.Controls.Add((Control) this.groupBox1);
      this.Name = nameof (LacaBall);
      this.Text = "LacaBall Editor By Dethunter12";
      this.Load += new EventHandler(this.LacaBall_Load);
      this.groupBox1.ResumeLayout(false);
      ((ISupportInitialize) this.pbLacaItem8).EndInit();
      ((ISupportInitialize) this.pbLacaItem7).EndInit();
      ((ISupportInitialize) this.pbLacaItem6).EndInit();
      ((ISupportInitialize) this.pbLacaItemAll).EndInit();
      ((ISupportInitialize) this.pbLacaItem5).EndInit();
      ((ISupportInitialize) this.pbLacaItem4).EndInit();
      ((ISupportInitialize) this.pbLacaItem3).EndInit();
      ((ISupportInitialize) this.pbLacaItem2).EndInit();
      ((ISupportInitialize) this.pbLacaItem1).EndInit();
      ((ISupportInitialize) this.dataGridView1).EndInit();
      ((ISupportInitialize) this.pbMoveDown).EndInit();
      ((ISupportInitialize) this.pbMoveUp).EndInit();
      this.gbItem.ResumeLayout(false);
      this.gbItem.PerformLayout();
      this.statusStrip1.ResumeLayout(false);
      this.statusStrip1.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
