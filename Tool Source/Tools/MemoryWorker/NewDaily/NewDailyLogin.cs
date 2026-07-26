// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.NewDaily.NewDailyLogin
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
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.NewDaily
{
  public class NewDailyLogin : Form
  {
    public static Connection connection = new Connection();
    private string Host = NewDailyLogin.connection.Settings.SqlHost;
    private string User = NewDailyLogin.connection.Settings.SqlUser;
    private string Password = NewDailyLogin.connection.Settings.SqlPassword;
    private string Database = NewDailyLogin.connection.Settings.SqlDatabase;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    private ExportLodHandle exportLodHandle = new ExportLodHandle();
    public string _ClientPath = NewDailyLogin.connection.Settings.ClientPath;
    public string rowName = "a_drop_idx";
    private DataTable table = new DataTable();
    private DataTable table2 = new DataTable();
    private MySqlCommand command;
    private MySqlDataAdapter adapter;
    private BindingManagerBase managerBase;
    private BindingManagerBase managerBase2;
    private MySqlCommandBuilder builder;
    private IContainer components = (IContainer) null;
    private GroupBox groupBox1;
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
    private Button button12;
    private Button button9;
    private Button button6;
    private PictureBox pictureBox7;
    private DataGridViewTextBoxColumn Day;
    private DataGridViewImageColumn Icon;
    private DataGridViewTextBoxColumn Item;
    private DataGridViewTextBoxColumn ItemName;
    private DataGridViewTextBoxColumn Count;
    private DataGridViewTextBoxColumn Month;
    private Button button11;
    private ComboBox comboBox1;

    private void IniRead()
    {
      IniFile iniFile = new IniFile(Application.StartupPath + "\\Config\\Settings.cfg");
      this.textBox2.Text = iniFile.IniReadValue("## MYSQL", "SQL_HOST");
      this.textBox3.Text = iniFile.IniReadValue("## MYSQL", "SQL_USER");
      this.textBox4.Text = iniFile.IniReadValue("## MYSQL", "SQL_PASSWORD");
      this.textBox5.Text = iniFile.IniReadValue("## MYSQL", "SQL_DATABASE");
    }

    public NewDailyLogin()
    {
      this.InitializeComponent();
      this.FillGrid();
      this.comboBox1.Items.AddRange(new object[12]
      {
        (object) "1.มกราคม-Jan",
        (object) "2.กุมภาพันธ์-Feb",
        (object) "3.มีนาคม-Mar",
        (object) "4.เมษายน-Apr",
        (object) "5.พฤษภาคม-May",
        (object) "6.มิถุนายน-Jun",
        (object) "7.กรกฎาคม-Jul",
        (object) "8.สิงหาคม-Aug",
        (object) "9.กันยายน-Sep",
        (object) "10.ตุลาคม-Oct",
        (object) "11.พฤศจิกายน-Nov",
        (object) "12.ธันวาคม-Dec"
      });
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
            this.dgItems.Rows.Clear();

            string query = "SELECT * FROM t_loginrewardnew ORDER BY a_day";

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
                        string day = reader["a_day"].ToString();
                        string itemIdx = reader["a_itemidx"].ToString();
                        string plus = reader["a_plus"].ToString();
                        string flag = reader["a_flag"].ToString();
                        string count = reader["a_count"].ToString();

                        // Lookup item name and icon safely
                        string itemName = this.databaseHandle.ItemNameFast(Convert.ToInt32(itemIdx));
                        Image icon = this.databaseHandle.IconFast(Convert.ToInt32(itemIdx));

                        // Add row to grid (matching your column order)
                        this.dgItems.Rows.Add(
                            day,       // Day
                            icon,      // Icon
                            itemIdx,   // Item ID
                            itemName,  // Item Name
                            plus,      // Plus
                            flag,      // Flag
                            count      // Count
                        );
                    }
                }
            }
        }
        private void FillGridByMonth(int month)
        {
            this.dgItems.Rows.Clear();

            string query = "SELECT * FROM t_loginrewardnew ORDER BY a_day";

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
                        string day = reader["a_day"].ToString();
                        string itemIdx = reader["a_itemidx"].ToString();
                        string plus = reader["a_plus"].ToString();
                        string flag = reader["a_flag"].ToString();
                        string count = reader["a_count"].ToString();

                        string itemName = this.databaseHandle.ItemNameFast(Convert.ToInt32(itemIdx));
                        Image icon = this.databaseHandle.IconFast(Convert.ToInt32(itemIdx));

                        this.dgItems.Rows.Add(day, icon, itemIdx, itemName, plus, flag, count);
                    }
                }
            }
        }


        private void dgItems_CellClick(object sender, DataGridViewCellEventArgs e)
    {
      if (e.RowIndex < 0)
        return;
      DataGridViewRow row = this.dgItems.Rows[e.RowIndex];
      this.textBox25.Text = row.Cells["Month"].Value.ToString();
      this.textBox10.Text = row.Cells["Day"].Value.ToString();
      this.textBox26.Text = row.Cells["Item"].Value.ToString();
      this.textBox11.Text = row.Cells["Count"].Value.ToString();
    }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            // Just re-read your config
            this.IniRead();

            // Determine selected month (1–12)
            int month = this.comboBox1.SelectedIndex + 1;

            // Call the unified method
            this.FillGridByMonth(month);
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
      this.comboBox1 = new ComboBox();
      this.groupBox4 = new GroupBox();
      this.dgItems = new DataGridView();
      this.Day = new DataGridViewTextBoxColumn();
      this.Icon = new DataGridViewImageColumn();
      this.Item = new DataGridViewTextBoxColumn();
      this.ItemName = new DataGridViewTextBoxColumn();
      this.Count = new DataGridViewTextBoxColumn();
      this.Month = new DataGridViewTextBoxColumn();
      this.textBox2 = new TextBox();
      this.textBox3 = new TextBox();
      this.textBox4 = new TextBox();
      this.textBox5 = new TextBox();
      this.textBox8 = new TextBox();
      this.groupBox5 = new GroupBox();
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
      this.button12 = new Button();
      this.button9 = new Button();
      this.button6 = new Button();
      this.button11 = new Button();
      this.groupBox1.SuspendLayout();
      this.groupBox4.SuspendLayout();
      ((ISupportInitialize) this.dgItems).BeginInit();
      this.groupBox5.SuspendLayout();
      ((ISupportInitialize) this.pictureBox7).BeginInit();
      this.SuspendLayout();
      this.groupBox1.Controls.Add((Control) this.comboBox1);
      this.groupBox1.Location = new Point(12, 13);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(256, 51);
      this.groupBox1.TabIndex = 3;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Select Month";
      this.comboBox1.BackColor = Color.GreenYellow;
      this.comboBox1.FlatStyle = FlatStyle.Flat;
      this.comboBox1.FormattingEnabled = true;
      this.comboBox1.Location = new Point(40, 19);
      this.comboBox1.Name = "comboBox1";
      this.comboBox1.Size = new Size(173, 21);
      this.comboBox1.TabIndex = 66;
      this.comboBox1.Text = "Select Month";
      this.comboBox1.SelectedIndexChanged += new EventHandler(this.comboBox1_SelectedIndexChanged);
      this.groupBox4.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left;
      this.groupBox4.Controls.Add((Control) this.dgItems);
      this.groupBox4.Location = new Point(12, 70);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Size = new Size(437, 622);
      this.groupBox4.TabIndex = 26;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "Item Data";
      this.dgItems.AllowUserToAddRows = false;
      this.dgItems.AllowUserToDeleteRows = false;
      this.dgItems.BackgroundColor = SystemColors.Control;
      this.dgItems.BorderStyle = BorderStyle.None;
      this.dgItems.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dgItems.Columns.AddRange((DataGridViewColumn) this.Day, (DataGridViewColumn) this.Icon, (DataGridViewColumn) this.Item, (DataGridViewColumn) this.ItemName, (DataGridViewColumn) this.Count, (DataGridViewColumn) this.Month);
      this.dgItems.Dock = DockStyle.Fill;
      this.dgItems.EnableHeadersVisualStyles = false;
      this.dgItems.Location = new Point(3, 16);
      this.dgItems.Name = "dgItems";
      this.dgItems.RowHeadersVisible = false;
      this.dgItems.RowTemplate.Height = 32;
      this.dgItems.ScrollBars = ScrollBars.Vertical;
      this.dgItems.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
      this.dgItems.Size = new Size(431, 603);
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
      this.Item.Width = 80;
      this.ItemName.HeaderText = "Item Name";
      this.ItemName.Name = "ItemName";
      this.ItemName.Width = 160;
      this.Count.HeaderText = "Count";
      this.Count.Name = "Count";
      this.Count.Width = 50;
      this.Month.HeaderText = "Month";
      this.Month.Name = "Month";
      this.Month.Width = 50;
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
      this.groupBox5.Location = new Point(466, 86);
      this.groupBox5.Name = "groupBox5";
      this.groupBox5.Size = new Size(372, 131);
      this.groupBox5.TabIndex = 60;
      this.groupBox5.TabStop = false;
      this.groupBox5.Text = "Item Setting";
      this.label15.AutoSize = true;
      this.label15.Location = new Point(51, 100);
      this.label15.Name = "label15";
      this.label15.Size = new Size(38, 13);
      this.label15.TabIndex = 41;
      this.label15.Text = "Name:";
      this.textBox24.Enabled = false;
      this.textBox24.Location = new Point(91, 97);
      this.textBox24.Multiline = true;
      this.textBox24.Name = "textBox24";
      this.textBox24.Size = new Size(251, 21);
      this.textBox24.TabIndex = 40;
      this.pictureBox7.Location = new Point(8, 68);
      this.pictureBox7.Name = "pictureBox7";
      this.pictureBox7.Size = new Size(32, 32);
      this.pictureBox7.TabIndex = 49;
      this.pictureBox7.TabStop = false;
      this.textBox25.Enabled = false;
      this.textBox25.Location = new Point(54, 19);
      this.textBox25.Multiline = true;
      this.textBox25.Name = "textBox25";
      this.textBox25.Size = new Size(55, 21);
      this.textBox25.TabIndex = 43;
      this.textBox11.Location = new Point(282, 68);
      this.textBox11.Multiline = true;
      this.textBox11.Name = "textBox11";
      this.textBox11.Size = new Size(60, 21);
      this.textBox11.TabIndex = 47;
      this.button4.BackgroundImageLayout = ImageLayout.None;
      this.button4.Image = (Image) Resources.search__5_;
      this.button4.Location = new Point(189, 70);
      this.button4.Name = "button4";
      this.button4.Size = new Size(27, 25);
      this.button4.TabIndex = 39;
      this.button4.UseVisualStyleBackColor = true;
      this.button4.Click += new EventHandler(this.button4_Click);
      this.label16.AutoSize = true;
      this.label16.Location = new Point(8, 22);
      this.label16.Name = "label16";
      this.label16.Size = new Size(40, 13);
      this.label16.TabIndex = 42;
      this.label16.Text = "Month:";
      this.label6.AutoSize = true;
      this.label6.Location = new Point(237, 76);
      this.label6.Name = "label6";
      this.label6.Size = new Size(38, 13);
      this.label6.TabIndex = 46;
      this.label6.Text = "Count:";
      this.textBox26.Enabled = false;
      this.textBox26.Location = new Point(91, 72);
      this.textBox26.Multiline = true;
      this.textBox26.Name = "textBox26";
      this.textBox26.Size = new Size(92, 21);
      this.textBox26.TabIndex = 38;
      this.textBox26.TextChanged += new EventHandler(this.textBox26_TextChanged);
      this.label4.AutoSize = true;
      this.label4.Location = new Point(46, 75);
      this.label4.Name = "label4";
      this.label4.Size = new Size(44, 13);
      this.label4.TabIndex = 37;
      this.label4.Text = "Item ID:";
      this.textBox10.Enabled = false;
      this.textBox10.Location = new Point(157, 19);
      this.textBox10.Multiline = true;
      this.textBox10.Name = "textBox10";
      this.textBox10.Size = new Size(55, 21);
      this.textBox10.TabIndex = 45;
      this.label5.AutoSize = true;
      this.label5.Location = new Point(122, 22);
      this.label5.Name = "label5";
      this.label5.Size = new Size(29, 13);
      this.label5.TabIndex = 44;
      this.label5.Text = "Day:";
      this.button12.BackColor = Color.LightCoral;
      this.button12.FlatStyle = FlatStyle.Flat;
      this.button12.Image = (Image) Resources.delete;
      this.button12.ImageAlign = ContentAlignment.MiddleLeft;
      this.button12.Location = new Point(470, 265);
      this.button12.Name = "button12";
      this.button12.Size = new Size(65, 27);
      this.button12.TabIndex = 65;
      this.button12.Text = "    Delete";
      this.button12.UseVisualStyleBackColor = false;
      this.button9.BackColor = Color.LightCyan;
      this.button9.FlatStyle = FlatStyle.Flat;
      this.button9.Image = (Image) Resources._08;
      this.button9.ImageAlign = ContentAlignment.MiddleLeft;
      this.button9.Location = new Point(557, 234);
      this.button9.Name = "button9";
      this.button9.Size = new Size(281, 60);
      this.button9.TabIndex = 64;
      this.button9.Text = "      Update";
      this.button9.UseVisualStyleBackColor = false;
      this.button6.BackColor = Color.Plum;
      this.button6.FlatStyle = FlatStyle.Flat;
      this.button6.Image = (Image) Resources.control_add_blue;
      this.button6.ImageAlign = ContentAlignment.MiddleLeft;
      this.button6.Location = new Point(470, 232);
      this.button6.Name = "button6";
      this.button6.Size = new Size(65, 27);
      this.button6.TabIndex = 63;
      this.button6.Text = "     Add";
      this.button6.UseVisualStyleBackColor = false;
      this.button11.BackColor = Color.White;
      this.button11.FlatStyle = FlatStyle.Flat;
      this.button11.Image = (Image) Resources.FOLDER05;
      this.button11.ImageAlign = ContentAlignment.MiddleLeft;
      this.button11.Location = new Point(470, 314);
      this.button11.Name = "button11";
      this.button11.Size = new Size(65, 27);
      this.button11.TabIndex = 66;
      this.button11.Text = "  Export";
      this.button11.UseVisualStyleBackColor = false;
      this.button11.Click += new EventHandler(this.button11_Click);
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(845, 718);
      this.Controls.Add((Control) this.button11);
      this.Controls.Add((Control) this.button12);
      this.Controls.Add((Control) this.button9);
      this.Controls.Add((Control) this.button6);
      this.Controls.Add((Control) this.groupBox5);
      this.Controls.Add((Control) this.textBox8);
      this.Controls.Add((Control) this.textBox5);
      this.Controls.Add((Control) this.textBox4);
      this.Controls.Add((Control) this.textBox3);
      this.Controls.Add((Control) this.textBox2);
      this.Controls.Add((Control) this.groupBox4);
      this.Controls.Add((Control) this.groupBox1);
      this.MaximizeBox = false;
      this.Name = nameof (NewDailyLogin);
      this.Text = nameof (NewDailyLogin);
      this.Load += new EventHandler(this.NewDailyLogin_Load);
      this.groupBox1.ResumeLayout(false);
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

    private void button11_Click(object sender, EventArgs e)
    {
      this.exportLodHandle.ExportDailyLogin_V4();
    }
  }
}
