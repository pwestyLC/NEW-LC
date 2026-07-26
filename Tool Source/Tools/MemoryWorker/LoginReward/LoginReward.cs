// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.LoginReward.LoginReward
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using LcDevPack_TeamDamonA.Properties;
using MySqlConnector;
using System;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.LoginReward
{
  public class LoginReward : Form
  {
    public static Connection connection = new Connection();
    private string Host = LcDevPack_TeamDamonA.Tools.MemoryWorker.LoginReward.LoginReward.connection.Settings.SqlHost;
    private string User = LcDevPack_TeamDamonA.Tools.MemoryWorker.LoginReward.LoginReward.connection.Settings.SqlUser;
    private string Password = LcDevPack_TeamDamonA.Tools.MemoryWorker.LoginReward.LoginReward.connection.Settings.SqlPassword;
    private string Database = LcDevPack_TeamDamonA.Tools.MemoryWorker.LoginReward.LoginReward.connection.Settings.SqlDatabase;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    private ExportLodHandle exportLodHandle = new ExportLodHandle();
    public string _ClientPath = LcDevPack_TeamDamonA.Tools.MemoryWorker.LoginReward.LoginReward.connection.Settings.ClientPath;
    public string rowName = "a_drop_idx";
    private DataTable table = new DataTable();
    private DataTable table2 = new DataTable();
    private MySqlCommand command;
    private MySqlDataAdapter adapter;
    private BindingManagerBase managerBase;
    private BindingManagerBase managerBase2;
    private MySqlCommandBuilder builder;
    private IContainer components = (IContainer) null;
    private GroupBox groupBox4;
    private DataGridView dgItems;
    private TextBox textBox2;
    private TextBox textBox3;
    private TextBox textBox4;
    private TextBox textBox5;
    private TextBox textBox8;
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
    private Button button9;
    private PictureBox pictureBox7;
    private TextBox textBox1;
    private Label label1;
    private DataGridViewTextBoxColumn Day;
    private DataGridViewImageColumn Icon;
    private DataGridViewTextBoxColumn Item;
    private DataGridViewTextBoxColumn ItemName;
    private DataGridViewTextBoxColumn Plus;
    private DataGridViewTextBoxColumn Flag;
    private DataGridViewTextBoxColumn Count;

    private void IniRead()
    {
      IniFile iniFile = new IniFile(Application.StartupPath + "\\Config\\Settings.cfg");
      this.textBox2.Text = iniFile.IniReadValue("## MYSQL", "SQL_HOST");
      this.textBox3.Text = iniFile.IniReadValue("## MYSQL", "SQL_USER");
      this.textBox4.Text = iniFile.IniReadValue("## MYSQL", "SQL_PASSWORD");
      this.textBox5.Text = iniFile.IniReadValue("## MYSQL", "SQL_DATABASE");
    }

    public LoginReward()
    {
      this.InitializeComponent();
      this.FillGrid();
    }

    private void saveToolStripMenuItem_Click(object sender, EventArgs e)
    {
    }

    private void NewDailyLogin_Load(object sender, EventArgs e) => mySQL.SetConnection();

    private void textBox1_TextChanged(object sender, EventArgs e) => this.FillGrid();

    private void LoadDataGrid()
    {
    }

        private void FillGrid()
        {
            dgItems.Rows.Clear();

            string query = "SELECT a_day, a_itemidx, a_plus, a_flag, a_count FROM t_loginrewardnew ORDER BY a_day;";

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
                    connection.Open();
                    using (var reader = command.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            int day = SafeInt(reader["a_day"]);
                            int itemIdx = SafeInt(reader["a_itemidx"]);
                            int plus = SafeInt(reader["a_plus"]);
                            int flag = SafeInt(reader["a_flag"]);
                            int count = SafeInt(reader["a_count"]);

                            string itemName = databaseHandle.ItemNameFast(itemIdx);
                            var icon = databaseHandle.IconFast(itemIdx);

                            dgItems.Rows.Add(
                                day,
                                icon,
                                itemIdx,
                                itemName,
                                plus,
                                flag,
                                count
                            );
                        }
                    }
                }
            }
        }

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
      this.textBox25.Text = row.Cells["Day"].Value.ToString();
      this.textBox26.Text = row.Cells["Item"].Value.ToString();
      this.textBox11.Text = row.Cells["Count"].Value.ToString();
      this.textBox10.Text = row.Cells["Plus"].Value.ToString();
      this.textBox1.Text = row.Cells["Flag"].Value.ToString();
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      this.groupBox4 = new GroupBox();
      this.dgItems = new DataGridView();
      this.Day = new DataGridViewTextBoxColumn();
      this.Icon = new DataGridViewImageColumn();
      this.Item = new DataGridViewTextBoxColumn();
      this.ItemName = new DataGridViewTextBoxColumn();
      this.Plus = new DataGridViewTextBoxColumn();
      this.Flag = new DataGridViewTextBoxColumn();
      this.Count = new DataGridViewTextBoxColumn();
      this.textBox2 = new TextBox();
      this.textBox3 = new TextBox();
      this.textBox4 = new TextBox();
      this.textBox5 = new TextBox();
      this.textBox8 = new TextBox();
      this.groupBox5 = new GroupBox();
      this.textBox1 = new TextBox();
      this.label1 = new Label();
      this.label15 = new Label();
      this.textBox24 = new TextBox();
      this.pictureBox7 = new PictureBox();
      this.textBox25 = new TextBox();
      this.textBox11 = new TextBox();
      this.button4 = new Button();
      this.label16 = new Label();
      this.label6 = new Label();
      this.textBox26 = new TextBox();
      this.label4 = new Label();
      this.textBox10 = new TextBox();
      this.label5 = new Label();
      this.button9 = new Button();
      this.groupBox4.SuspendLayout();
      ((ISupportInitialize) this.dgItems).BeginInit();
      this.groupBox5.SuspendLayout();
      ((ISupportInitialize) this.pictureBox7).BeginInit();
      this.SuspendLayout();
      this.groupBox4.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left;
      this.groupBox4.Controls.Add((Control) this.dgItems);
      this.groupBox4.Location = new Point(12, 12);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Size = new Size(490, 527);
      this.groupBox4.TabIndex = 26;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "Item Data";
      this.dgItems.AllowUserToAddRows = false;
      this.dgItems.AllowUserToDeleteRows = false;
      this.dgItems.BackgroundColor = SystemColors.Control;
      this.dgItems.BorderStyle = BorderStyle.None;
      this.dgItems.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dgItems.Columns.AddRange((DataGridViewColumn) this.Day, (DataGridViewColumn) this.Icon, (DataGridViewColumn) this.Item, (DataGridViewColumn) this.ItemName, (DataGridViewColumn) this.Plus, (DataGridViewColumn) this.Flag, (DataGridViewColumn) this.Count);
      this.dgItems.EnableHeadersVisualStyles = false;
      this.dgItems.Location = new Point(3, 16);
      this.dgItems.Name = "dgItems";
      this.dgItems.RowHeadersVisible = false;
      this.dgItems.RowTemplate.Height = 32;
      this.dgItems.ScrollBars = ScrollBars.Vertical;
      this.dgItems.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
      this.dgItems.Size = new Size(484, 505);
      this.dgItems.TabIndex = 0;
      this.dgItems.CellClick += new DataGridViewCellEventHandler(this.dgItems_CellClick);
      this.Day.HeaderText = "Day";
      this.Day.Name = "Day";
      this.Day.Width = 50;
      this.Icon.HeaderText = "";
      this.Icon.Name = "Icon";
      this.Icon.Width = 32;
      this.Item.HeaderText = "Item";
      this.Item.Name = "Item";
      this.Item.Width = 70;
      this.ItemName.HeaderText = "Item Name";
      this.ItemName.Name = "ItemName";
      this.ItemName.Width = 160;
      this.Plus.FillWeight = 50f;
      this.Plus.HeaderText = "Plus";
      this.Plus.Name = "Plus";
      this.Plus.Width = 50;
      this.Flag.HeaderText = "Flag";
      this.Flag.Name = "Flag";
      this.Flag.Width = 70;
      this.Count.HeaderText = "Count";
      this.Count.Name = "Count";
      this.Count.Width = 50;
      this.textBox2.Enabled = false;
      this.textBox2.Location = new Point(622, 37);
      this.textBox2.Name = "textBox2";
      this.textBox2.Size = new Size(27, 20);
      this.textBox2.TabIndex = 27;
      this.textBox2.Visible = false;
      this.textBox3.Enabled = false;
      this.textBox3.Location = new Point(656, 37);
      this.textBox3.Name = "textBox3";
      this.textBox3.Size = new Size(28, 20);
      this.textBox3.TabIndex = 28;
      this.textBox3.Visible = false;
      this.textBox4.Enabled = false;
      this.textBox4.Location = new Point(690, 37);
      this.textBox4.Name = "textBox4";
      this.textBox4.Size = new Size(27, 20);
      this.textBox4.TabIndex = 29;
      this.textBox4.Visible = false;
      this.textBox5.Enabled = false;
      this.textBox5.Location = new Point(724, 37);
      this.textBox5.Name = "textBox5";
      this.textBox5.Size = new Size(26, 20);
      this.textBox5.TabIndex = 30;
      this.textBox5.Visible = false;
      this.textBox8.Enabled = false;
      this.textBox8.Location = new Point(785, 37);
      this.textBox8.Name = "textBox8";
      this.textBox8.Size = new Size(55, 20);
      this.textBox8.TabIndex = 53;
      this.textBox8.Visible = false;
      this.groupBox5.BackColor = Color.FromArgb((int) byte.MaxValue, 224, 192);
      this.groupBox5.Controls.Add((Control) this.textBox1);
      this.groupBox5.Controls.Add((Control) this.label1);
      this.groupBox5.Controls.Add((Control) this.label15);
      this.groupBox5.Controls.Add((Control) this.textBox24);
      this.groupBox5.Controls.Add((Control) this.pictureBox7);
      this.groupBox5.Controls.Add((Control) this.textBox25);
      this.groupBox5.Controls.Add((Control) this.textBox11);
      this.groupBox5.Controls.Add((Control) this.button4);
      this.groupBox5.Controls.Add((Control) this.label16);
      this.groupBox5.Controls.Add((Control) this.label6);
      this.groupBox5.Controls.Add((Control) this.textBox26);
      this.groupBox5.Controls.Add((Control) this.label4);
      this.groupBox5.Controls.Add((Control) this.textBox10);
      this.groupBox5.Controls.Add((Control) this.label5);
      this.groupBox5.Location = new Point(523, 86);
      this.groupBox5.Name = "groupBox5";
      this.groupBox5.Size = new Size(315, 131);
      this.groupBox5.TabIndex = 60;
      this.groupBox5.TabStop = false;
      this.groupBox5.Text = "Item Setting";
      this.textBox1.Location = new Point(199, 72);
      this.textBox1.Multiline = true;
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(55, 21);
      this.textBox1.TabIndex = 51;
      this.label1.AutoSize = true;
      this.label1.Location = new Point(164, 75);
      this.label1.Name = "label1";
      this.label1.Size = new Size(30, 13);
      this.label1.TabIndex = 50;
      this.label1.Text = "Flag:";
      this.label15.AutoSize = true;
      this.label15.Location = new Point(51, 102);
      this.label15.Name = "label15";
      this.label15.Size = new Size(38, 13);
      this.label15.TabIndex = 41;
      this.label15.Text = "Name:";
      this.textBox24.Enabled = false;
      this.textBox24.Location = new Point(91, 99);
      this.textBox24.Multiline = true;
      this.textBox24.Name = "textBox24";
      this.textBox24.Size = new Size(218, 21);
      this.textBox24.TabIndex = 40;
      this.pictureBox7.Location = new Point(8, 41);
      this.pictureBox7.Name = "pictureBox7";
      this.pictureBox7.Size = new Size(32, 32);
      this.pictureBox7.TabIndex = 49;
      this.pictureBox7.TabStop = false;
      this.textBox25.Enabled = false;
      this.textBox25.Location = new Point(50, 16);
      this.textBox25.Multiline = true;
      this.textBox25.Name = "textBox25";
      this.textBox25.Size = new Size(55, 21);
      this.textBox25.TabIndex = 43;
      this.textBox11.Location = new Point(262, 41);
      this.textBox11.Multiline = true;
      this.textBox11.Name = "textBox11";
      this.textBox11.Size = new Size(48, 21);
      this.textBox11.TabIndex = 47;
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
      this.label16.Size = new Size(29, 13);
      this.label16.TabIndex = 42;
      this.label16.Text = "Day:";
      this.label6.AutoSize = true;
      this.label6.Location = new Point(220, 49);
      this.label6.Name = "label6";
      this.label6.Size = new Size(38, 13);
      this.label6.TabIndex = 46;
      this.label6.Text = "Count:";
      this.textBox26.Enabled = false;
      this.textBox26.Location = new Point(91, 45);
      this.textBox26.Multiline = true;
      this.textBox26.Name = "textBox26";
      this.textBox26.Size = new Size(92, 21);
      this.textBox26.TabIndex = 38;
      this.textBox26.TextChanged += new EventHandler(this.textBox26_TextChanged);
      this.label4.AutoSize = true;
      this.label4.Location = new Point(46, 48);
      this.label4.Name = "label4";
      this.label4.Size = new Size(44, 13);
      this.label4.TabIndex = 37;
      this.label4.Text = "Item ID:";
      this.textBox10.Location = new Point(95, 72);
      this.textBox10.Multiline = true;
      this.textBox10.Name = "textBox10";
      this.textBox10.Size = new Size(55, 21);
      this.textBox10.TabIndex = 45;
      this.label5.AutoSize = true;
      this.label5.Location = new Point(60, 75);
      this.label5.Name = "label5";
      this.label5.Size = new Size(30, 13);
      this.label5.TabIndex = 44;
      this.label5.Text = "Plus:";
      this.button9.BackColor = SystemColors.ControlLight;
      this.button9.FlatStyle = FlatStyle.Flat;
      this.button9.Image = (Image) Resources._08;
      this.button9.ImageAlign = ContentAlignment.MiddleLeft;
      this.button9.Location = new Point(572, 233);
      this.button9.Name = "button9";
      this.button9.Size = new Size(216, 60);
      this.button9.TabIndex = 64;
      this.button9.Text = "      Update";
      this.button9.UseVisualStyleBackColor = false;
      this.button9.Click += new EventHandler(this.button9_Click);
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(845, 551);
      this.Controls.Add((Control) this.button9);
      this.Controls.Add((Control) this.groupBox5);
      this.Controls.Add((Control) this.textBox8);
      this.Controls.Add((Control) this.textBox5);
      this.Controls.Add((Control) this.textBox4);
      this.Controls.Add((Control) this.textBox3);
      this.Controls.Add((Control) this.textBox2);
      this.Controls.Add((Control) this.groupBox4);
      this.MaximizeBox = false;
      this.Name = nameof (LoginReward);
      this.Text = nameof (LoginReward);
      this.Load += new EventHandler(this.NewDailyLogin_Load);
      this.groupBox4.ResumeLayout(false);
      ((ISupportInitialize) this.dgItems).EndInit();
      this.groupBox5.ResumeLayout(false);
      this.groupBox5.PerformLayout();
      ((ISupportInitialize) this.pictureBox7).EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();
    }

    private void textBox26_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox7.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox26.Text.Trim()));
      this.textBox24.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox26.Text.Trim()));
    }

    private void ClearBox()
    {
      this.pictureBox7.Image = (Image) null;
      this.textBox26.Text = "0";
      this.textBox25.Text = "0";
      this.textBox10.Text = "0";
      this.textBox11.Text = "1";
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
      int index = this.dgItems.CurrentRow.Index;
      DataGridViewRow row = this.dgItems.Rows[this.dgItems.CurrentRow.Index];
      MySqlConnection connection = new MySqlConnection("datasource=" + this.textBox2.Text + ";port=3306;username=" + this.textBox3.Text + ";password=" + this.textBox4.Text);
      MySqlCommand mySqlCommand = new MySqlCommand("UPDATE " + this.textBox5.Text + ".t_loginrewardnew SET a_itemidx='" + this.textBox26.Text + "', a_plus='" + this.textBox10.Text + "', a_flag='" + this.textBox1.Text + "', a_count='" + this.textBox11.Text + "' WHERE a_day='" + this.textBox25.Text + "'", connection);
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
      this.dgItems.Rows[index].Selected = true;
      this.dgItems.FirstDisplayedScrollingRowIndex = index;
    }
  }
}
