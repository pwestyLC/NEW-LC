// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.LuckyDrawBoxTool
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using MySqlConnector;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools
{
  public class LuckyDrawBoxTool : Form
  {
    public static Connection connection = new Connection();
    private string Host = LuckyDrawBoxTool.connection.Settings.SqlHost;
    private string User = LuckyDrawBoxTool.connection.Settings.SqlUser;
    private string Password = LuckyDrawBoxTool.connection.Settings.SqlPassword;
    private string Database = LuckyDrawBoxTool.connection.Settings.SqlDatabase;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    public string rowName = "a_index";
    public string[] menuArray = new string[2]
    {
      "a_index",
      "a_name"
    };
    private IContainer components = (IContainer) null;
    public string name;
    public int index;
    public string test2;
    private ListBox listBox1;
    private GroupBox groupBox1;
    private Button button2;
    private Button button1;
    private Button button3;
    private GroupBox groupBox2;
    private Label label4;
    private Label label3;
    private TextBox textBox4;
    private Label label2;
    private Label label1;
    private TextBox textBox3;
    private TextBox textBox2;
    private TextBox textBox1;
    private GroupBox groupBox4;
    private DataGridView dgItems;
    private ToolStrip toolStrip2;
    private ToolStripButton btnDeleteSelected;
    private ToolStripSeparator toolStripSeparator1;
    private ToolStripButton btnAddItems;
    private ToolStripSeparator toolStripSeparator6;
    private ToolStripButton toolStripButton1;
    private GroupBox groupBox3;
    private DataGridView dgItems2;
    private ToolStrip toolStrip1;
    private ToolStripButton toolStripButton2;
    private ToolStripSeparator toolStripSeparator2;
    private ToolStripButton toolStripButton3;
    private ToolStripSeparator toolStripSeparator3;
    private ToolStripButton toolStripButton4;
    private DataGridViewImageColumn Column7;
    private DataGridViewTextBoxColumn Column1;
    private DataGridViewTextBoxColumn Column2;
    private DataGridViewTextBoxColumn Column3;
    private DataGridViewTextBoxColumn Column4;
    private DataGridViewTextBoxColumn Column5;
    private TabControl tabControl1;
    private TabPage tabPage1;
    private TabPage tabPage2;
    private DataGridViewImageColumn dataGridViewImageColumn1;
    private DataGridViewTextBoxColumn Column11;
    private DataGridViewTextBoxColumn Column12;
    private DataGridViewTextBoxColumn Column13;
    private DataGridViewTextBoxColumn Column14;
    private DataGridViewTextBoxColumn Column15;
    private DataGridViewTextBoxColumn Column16;
    private DataGridViewTextBoxColumn Column17;
    private DataGridViewTextBoxColumn Column10;
    private CheckBox checkBox1;
    private StatusStrip statusStrip1;
    private ToolStripStatusLabel toolStripStatusLabel1;
    private TextBox textBox5;
    private CheckedListBox checkedListBox1;

    public LuckyDrawBoxTool()
    {
      this.InitializeComponent();
      this.LoadStartUp();
    }

        private void LoadListBox()
        {
            listBox1.Items.Clear();

            string query = "SELECT a_index, a_name FROM t_luckydrawbox ORDER BY a_index;";

            using (var connection = new MySqlConnection(
                "datasource=" + Host +
                ";port=3306;" +
                "username=" + User +
                ";password=" + Password +
                ";database=" + Database +
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
                            int index = SafeInt(reader["a_index"]);
                            string name = reader["a_name"]?.ToString() ?? "(Unnamed Box)";
                            listBox1.Items.Add($"{index} - {name}");
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


        private void LoadStartUp()
        {
            string query = "SELECT MAX(a_index) AS max_index FROM t_luckydrawbox;";

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

                    object result = command.ExecuteScalar(); // no need for a reader here

                    if (result != null && int.TryParse(result.ToString(), out int maxIndex))
                    {
                        // You can choose to just show it...
                        textBox5.Text = maxIndex.ToString();

                        // ...or automatically increment for the next available index:
                        // textBox5.Text = (maxIndex + 1).ToString();
                    }
                    else
                    {
                        textBox5.Text = "1"; // Default if table is empty
                    }
                }
            }
        }


        private void LoadBasic()
    {
      if (this.textBox3.Text == "1")
        this.checkBox1.Checked = true;
      else
        this.checkBox1.Checked = false;
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

    private void LuckyDrawBoxTool_Load(object sender, EventArgs e) => this.LoadListBox();

    private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (this.listBox1.SelectedIndex != -1)
      {
        this.name = this.listBox1.SelectedItem.ToString();
        this.textBox1.Text = this.name;
      }
      string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, " select * from t_luckydrawbox WHERE a_index ='" + this.textBox1.Text + "';", new string[4]
      {
        "a_index",
        "a_name",
        "a_enable",
        "a_random"
      });
      this.textBox1.Text = strArray[0];
      this.textBox2.Text = strArray[1];
      this.textBox3.Text = strArray[2];
      this.textBox4.Text = strArray[3];
      this.dgItems.Rows.Clear();
      this.dgItems2.Rows.Clear();
      this.LoadDG();
      this.LoadDG2();
      this.LoadBasic();
      this.LoadMisc();
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

    public void LoadDG()
    {
      this.toolStripStatusLabel1.Text = "Load Items ...";
      string str1 = "SELECT * FROM t_luckydrawneed WHERE a_luckydraw_idx ='" + this.textBox1.Text + "'";
      string[] strArray = new string[4]
      {
        "a_index",
        "a_luckydraw_idx",
        "a_item_idx",
        "a_count"
      };
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
        Bitmap bitmap = this.databaseHandle.IconFast(Convert.ToInt32(str4));
        string str6 = this.databaseHandle.ItemNameFast(Convert.ToInt32(str4));
        this.dgItems.Rows.Add((object) bitmap, (object) str3, (object) str4, (object) str6, (object) str5, (object) str2);
      }
      mySqlConnection.Close();
      this.toolStripStatusLabel1.Text = "Ready";
    }

    public void LoadDG2()
    {
      this.toolStripStatusLabel1.Text = "Load Items ...";
      string str1 = "SELECT * FROM t_luckydrawresult WHERE a_luckydraw_idx ='" + this.textBox1.Text + "' ORDER BY a_prob DESC";
      string[] strArray1 = new string[7]
      {
        "a_index",
        "a_luckydraw_idx",
        "a_item_idx",
        "a_count",
        "a_upgrade",
        "a_prob",
        "a_flag"
      };
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
        string str8 = mySqlDataReader.GetValue(6).ToString();
        string[] strArray2 = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, "SELECT a_name, a_texture_id, a_texture_row, a_texture_col from t_item WHERE a_index ='" + str4 + "';", new string[4]
        {
          "a_name",
          "a_texture_id",
          "a_texture_row",
          "a_texture_col"
        });
        string str9 = this.databaseHandle.ItemNameFast(Convert.ToInt32(str4));
        this.dgItems2.Rows.Add((object) this.databaseHandle.IconItem(Convert.ToInt32(strArray2[1]), Convert.ToInt32(strArray2[2]), Convert.ToInt32(strArray2[3])), (object) str3, (object) str4, (object) str9, (object) str5, (object) str6, (object) str7, (object) str8, (object) str2);
      }
      mySqlConnection.Close();
      this.toolStripStatusLabel1.Text = "Ready";
    }

    private void dgItems_CellContentClick(object sender, DataGridViewCellEventArgs e)
    {
    }

    private void toolStripButton1_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want to Delete Item  ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_luckydrawneed WHERE a_index ='" + Convert.ToString(this.dgItems.Rows[this.dgItems.CurrentRow.Index].Cells["Column5"].Value) + "'");
      this.dgItems.Rows.Clear();
      this.LoadDG();
    }

    private void btnAddItems_Click(object sender, EventArgs e)
    {
      int index = this.dgItems.CurrentRow.Index;
      DataGridViewRow row = this.dgItems.Rows[this.dgItems.CurrentRow.Index];
      try
      {
        ItemPicker itemPicker = new ItemPicker();
        if (itemPicker.ShowDialog() != DialogResult.OK)
          return;
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_luckydrawneed (a_luckydraw_idx, a_item_idx, a_count) VALUES (" + this.textBox1.Text + "," + itemPicker.ItemIndex.ToString() + ",1)");
      }
      catch
      {
        int num = (int) MessageBox.Show("Duplicated ItemID isn't allowed.", "Error");
      }
      this.dgItems.Rows.Clear();
      this.LoadDG();
      this.dgItems.Rows[index].Selected = true;
      this.dgItems.FirstDisplayedScrollingRowIndex = index;
    }

    private void btnDeleteSelected_Click(object sender, EventArgs e)
    {
      int index = this.dgItems.CurrentRow.Index;
      DataGridViewRow row = this.dgItems.Rows[this.dgItems.CurrentRow.Index];
      string str = Convert.ToString(row.Cells["Column5"].Value);
      Convert.ToString(row.Cells["Column1"].Value);
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_luckydrawneed SET a_item_idx = '" + Convert.ToString(row.Cells["Column2"].Value) + "', a_count = '" + Convert.ToString(row.Cells["Column4"].Value) + "' WHERE a_index = '" + str + "' ");
      this.dgItems.Rows.Clear();
      this.LoadDG();
      this.dgItems.Rows[index].Selected = true;
      this.dgItems.FirstDisplayedScrollingRowIndex = index;
    }

    private void toolStripButton4_Click(object sender, EventArgs e)
    {
      int index = this.dgItems2.CurrentRow.Index - 1;
      DataGridViewRow row = this.dgItems2.Rows[this.dgItems2.CurrentRow.Index];
      if (this.dgItems2.CurrentRow.Index < 0)
      {
        int num = (int) MessageBox.Show("You need select Item", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        if (MessageBox.Show("Do you want to Delete Item  ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
          return;
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_luckydrawresult WHERE a_index ='" + Convert.ToString(this.dgItems2.Rows[this.dgItems2.CurrentRow.Index].Cells["Column10"].Value) + "'");
        this.dgItems2.Rows.Clear();
        this.LoadDG();
        this.LoadDG2();
        if (index == -1)
          return;
        this.dgItems2.Rows[index].Selected = true;
        this.dgItems2.FirstDisplayedScrollingRowIndex = index;
      }
    }

    private void toolStripButton3_Click(object sender, EventArgs e)
    {
      int index = this.dgItems2.CurrentRow.Index;
      DataGridViewRow row = this.dgItems2.Rows[this.dgItems2.CurrentRow.Index];
      try
      {
        ItemPicker itemPicker = new ItemPicker();
        if (itemPicker.ShowDialog() != DialogResult.OK)
          return;
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_luckydrawresult (a_luckydraw_idx, a_item_idx, a_count, a_upgrade, a_prob, a_flag) VALUES (" + this.textBox1.Text + "," + itemPicker.ItemIndex.ToString() + ", 1, 0, 0, 0)");
      }
      catch
      {
        int num = (int) MessageBox.Show("Duplicated ItemID isn't allowed.", "Error");
      }
      this.dgItems2.Rows.Clear();
      this.LoadDG2();
      this.dgItems2.Rows[index].Selected = true;
      this.dgItems2.FirstDisplayedScrollingRowIndex = index;
    }

    private void toolStripButton2_Click(object sender, EventArgs e)
    {
      int index = this.dgItems2.CurrentRow.Index;
      DataGridViewRow row = this.dgItems2.Rows[this.dgItems2.CurrentRow.Index];
      string str = Convert.ToString(row.Cells["Column10"].Value);
      Convert.ToString(row.Cells["Column11"].Value);
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_luckydrawresult SET a_item_idx = '" + Convert.ToString(row.Cells["Column12"].Value) + "', a_count = '" + Convert.ToString(row.Cells["Column14"].Value) + "', a_upgrade = '" + Convert.ToString(row.Cells["Column15"].Value) + "', a_prob = '" + Convert.ToString(row.Cells["Column16"].Value) + "', a_flag = '" + Convert.ToString(row.Cells["Column17"].Value) + "' WHERE a_index = '" + str + "' ");
      this.dgItems2.Rows.Clear();
      this.LoadDG2();
      this.dgItems2.Rows[index].Selected = true;
      this.dgItems2.FirstDisplayedScrollingRowIndex = index;
    }

    private void button1_Click(object sender, EventArgs e)
    {
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DROP TABLE IF EXISTS tempTable;CREATE TEMPORARY TABLE tempTable ENGINE=MEMORY SELECT * FROM t_luckydrawbox WHERE a_index=" + this.textBox1.Text + ";SELECT a_index FROM tempTable;UPDATE tempTable SET a_index=(SELECT a_index from t_luckydrawbox ORDER BY a_index DESC LIMIT 1)+1; SELECT a_index FROM tempTable;INSERT INTO t_luckydrawbox SELECT * FROM tempTable;");
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_luckydrawresult (a_luckydraw_idx, a_item_idx, a_count, a_upgrade, a_prob, a_flag) VALUES (" + this.textBox5.Text + " + 1,85,1,0,0,0)");
      this.LoadListBox();
      this.listBox1.SelectedIndex = this.listBox1.Items.Count - 1;
    }

    private void button2_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want to Delete Box " + this.textBox1.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      int selectedIndex = this.listBox1.SelectedIndex;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_luckydrawbox WHERE a_index = '" + this.textBox1.Text + "'");
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_luckydrawneed WHERE a_luckydraw_idx = '" + this.textBox1.Text + "'");
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_luckydrawresult WHERE a_luckydraw_idx = '" + this.textBox1.Text + "'");
      this.LoadListBox();
      this.listBox1.SelectedIndex = selectedIndex - 1;
      int num = (int) new CustomMessage("Deleted :O").ShowDialog();
    }

    private void button3_Click(object sender, EventArgs e)
    {
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_luckydrawbox SET a_name = '" + this.textBox2.Text + "', a_enable = '" + this.textBox3.Text + "', a_random = '" + this.textBox4.Text + "' WHERE a_index = '" + this.textBox1.Text + "'");
      int selectedIndex = this.listBox1.SelectedIndex;
      this.LoadListBox();
      this.listBox1.SelectedIndex = selectedIndex;
      int num = (int) new CustomMessage("Done :)").ShowDialog();
    }

    private void checkBox1_CheckedChanged(object sender, EventArgs e)
    {
      if (this.checkBox1.Checked)
        this.textBox3.Text = "1";
      else
        this.textBox3.Text = "0";
    }

    private void checkBox2_CheckedChanged(object sender, EventArgs e)
    {
    }

    private void dgItems2_CellContentClick(object sender, DataGridViewCellEventArgs e)
    {
    }

    private void checkedListBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      string comboBox = "";
      foreach (object checkedItem in this.checkedListBox1.CheckedItems)
        comboBox = checkedItem.ToString();
      this.textBox4.Text = this.GetIndexByComboBox(comboBox).ToString();
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
      string text = this.textBox4.Text;
      for (int index = 0; index < this.checkedListBox1.Items.Count; ++index)
      {
        int num = this.checkedListBox1.FindString(text);
        if (index == num)
          this.checkedListBox1.SetItemChecked(index, true);
      }
    }

    private void textBox4_TextChanged(object sender, EventArgs e)
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
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (LuckyDrawBoxTool));
      this.listBox1 = new ListBox();
      this.groupBox1 = new GroupBox();
      this.button2 = new Button();
      this.button1 = new Button();
      this.button3 = new Button();
      this.groupBox2 = new GroupBox();
      this.checkedListBox1 = new CheckedListBox();
      this.checkBox1 = new CheckBox();
      this.label4 = new Label();
      this.label1 = new Label();
      this.textBox2 = new TextBox();
      this.textBox1 = new TextBox();
      this.label3 = new Label();
      this.textBox4 = new TextBox();
      this.label2 = new Label();
      this.textBox3 = new TextBox();
      this.groupBox4 = new GroupBox();
      this.dgItems = new DataGridView();
      this.Column7 = new DataGridViewImageColumn();
      this.Column1 = new DataGridViewTextBoxColumn();
      this.Column2 = new DataGridViewTextBoxColumn();
      this.Column3 = new DataGridViewTextBoxColumn();
      this.Column4 = new DataGridViewTextBoxColumn();
      this.Column5 = new DataGridViewTextBoxColumn();
      this.toolStrip2 = new ToolStrip();
      this.btnDeleteSelected = new ToolStripButton();
      this.toolStripSeparator1 = new ToolStripSeparator();
      this.btnAddItems = new ToolStripButton();
      this.toolStripSeparator6 = new ToolStripSeparator();
      this.toolStripButton1 = new ToolStripButton();
      this.groupBox3 = new GroupBox();
      this.dgItems2 = new DataGridView();
      this.dataGridViewImageColumn1 = new DataGridViewImageColumn();
      this.Column11 = new DataGridViewTextBoxColumn();
      this.Column12 = new DataGridViewTextBoxColumn();
      this.Column13 = new DataGridViewTextBoxColumn();
      this.Column14 = new DataGridViewTextBoxColumn();
      this.Column15 = new DataGridViewTextBoxColumn();
      this.Column16 = new DataGridViewTextBoxColumn();
      this.Column17 = new DataGridViewTextBoxColumn();
      this.Column10 = new DataGridViewTextBoxColumn();
      this.toolStrip1 = new ToolStrip();
      this.toolStripButton2 = new ToolStripButton();
      this.toolStripSeparator2 = new ToolStripSeparator();
      this.toolStripButton3 = new ToolStripButton();
      this.toolStripSeparator3 = new ToolStripSeparator();
      this.toolStripButton4 = new ToolStripButton();
      this.tabControl1 = new TabControl();
      this.tabPage1 = new TabPage();
      this.tabPage2 = new TabPage();
      this.statusStrip1 = new StatusStrip();
      this.toolStripStatusLabel1 = new ToolStripStatusLabel();
      this.textBox5 = new TextBox();
      this.groupBox1.SuspendLayout();
      this.groupBox2.SuspendLayout();
      this.groupBox4.SuspendLayout();
      ((ISupportInitialize) this.dgItems).BeginInit();
      this.toolStrip2.SuspendLayout();
      this.groupBox3.SuspendLayout();
      ((ISupportInitialize) this.dgItems2).BeginInit();
      this.toolStrip1.SuspendLayout();
      this.tabControl1.SuspendLayout();
      this.tabPage1.SuspendLayout();
      this.tabPage2.SuspendLayout();
      this.statusStrip1.SuspendLayout();
      this.SuspendLayout();
      this.listBox1.FormattingEnabled = true;
      this.listBox1.ItemHeight = 16;
      this.listBox1.Location = new Point(6, 19);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new Size(211, 500);
      this.listBox1.TabIndex = 0;
      this.listBox1.SelectedIndexChanged += new EventHandler(this.listBox1_SelectedIndexChanged);
      this.groupBox1.Controls.Add((Control) this.button2);
      this.groupBox1.Controls.Add((Control) this.button1);
      this.groupBox1.Controls.Add((Control) this.listBox1);
      this.groupBox1.Location = new Point(12, 12);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(223, 577);
      this.groupBox1.TabIndex = 1;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Boxes";
      this.button2.FlatStyle = FlatStyle.Flat;
      this.button2.Location = new Point(117, 548);
      this.button2.Name = "button2";
      this.button2.Size = new Size(100, 23);
      this.button2.TabIndex = 2;
      this.button2.Text = "Delete";
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.button1.FlatStyle = FlatStyle.Flat;
      this.button1.Location = new Point(6, 548);
      this.button1.Name = "button1";
      this.button1.Size = new Size(100, 23);
      this.button1.TabIndex = 1;
      this.button1.Text = "Add";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.button3.FlatStyle = FlatStyle.Flat;
      this.button3.Location = new Point(802, 560);
      this.button3.Name = "button3";
      this.button3.Size = new Size(75, 23);
      this.button3.TabIndex = 2;
      this.button3.Text = "Save";
      this.button3.UseVisualStyleBackColor = true;
      this.button3.Click += new EventHandler(this.button3_Click);
      this.groupBox2.Controls.Add((Control) this.checkedListBox1);
      this.groupBox2.Controls.Add((Control) this.checkBox1);
      this.groupBox2.Controls.Add((Control) this.label4);
      this.groupBox2.Controls.Add((Control) this.label1);
      this.groupBox2.Controls.Add((Control) this.textBox2);
      this.groupBox2.Controls.Add((Control) this.textBox1);
      this.groupBox2.Location = new Point(241, 12);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new Size(537, 77);
      this.groupBox2.TabIndex = 3;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "Main";
      this.checkedListBox1.BackColor = SystemColors.Menu;
      this.checkedListBox1.BorderStyle = BorderStyle.None;
      this.checkedListBox1.CheckOnClick = true;
      this.checkedListBox1.FormattingEnabled = true;
      this.checkedListBox1.Items.AddRange(new object[3]
      {
        (object) "0 - Prob",
        (object) "1 - Random",
        (object) "2 - All"
      });
      this.checkedListBox1.Location = new Point(347, 16);
      this.checkedListBox1.Name = "checkedListBox1";
      this.checkedListBox1.Size = new Size(184, 34);
      this.checkedListBox1.TabIndex = 51;
      this.checkedListBox1.ItemCheck += new ItemCheckEventHandler(this.checkedListBox1_ItemCheck);
      this.checkedListBox1.SelectedIndexChanged += new EventHandler(this.checkedListBox1_SelectedIndexChanged);
      this.checkBox1.AutoSize = true;
      this.checkBox1.FlatStyle = FlatStyle.Flat;
      this.checkBox1.Location = new Point(157, 20);
      this.checkBox1.Name = "checkBox1";
      this.checkBox1.Size = new Size(68, 20);
      this.checkBox1.TabIndex = 8;
      this.checkBox1.Text = "Enable";
      this.checkBox1.UseVisualStyleBackColor = true;
      this.checkBox1.CheckedChanged += new EventHandler(this.checkBox1_CheckedChanged);
      this.label4.AutoSize = true;
      this.label4.Location = new Point(13, 47);
      this.label4.Name = "label4";
      this.label4.Size = new Size(47, 16);
      this.label4.TabIndex = 7;
      this.label4.Text = "Name:";
      this.label1.AutoSize = true;
      this.label1.Location = new Point(13, 21);
      this.label1.Name = "label1";
      this.label1.Size = new Size(42, 16);
      this.label1.TabIndex = 3;
      this.label1.Text = "Index:";
      this.textBox2.BorderStyle = BorderStyle.FixedSingle;
      this.textBox2.Location = new Point(54, 45);
      this.textBox2.Name = "textBox2";
      this.textBox2.Size = new Size(287, 22);
      this.textBox2.TabIndex = 1;
      this.textBox1.BorderStyle = BorderStyle.FixedSingle;
      this.textBox1.Location = new Point(54, 19);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(48, 22);
      this.textBox1.TabIndex = 0;
      this.label3.AutoSize = true;
      this.label3.Location = new Point(799, 38);
      this.label3.Name = "label3";
      this.label3.Size = new Size(53, 16);
      this.label3.TabIndex = 6;
      this.label3.Text = "Enable:";
      this.label3.Visible = false;
      this.textBox4.BorderStyle = BorderStyle.FixedSingle;
      this.textBox4.Location = new Point(852, 62);
      this.textBox4.Name = "textBox4";
      this.textBox4.Size = new Size(51, 22);
      this.textBox4.TabIndex = 5;
      this.textBox4.Visible = false;
      this.textBox4.TextChanged += new EventHandler(this.textBox4_TextChanged);
      this.label2.AutoSize = true;
      this.label2.Location = new Point(796, 69);
      this.label2.Name = "label2";
      this.label2.Size = new Size(62, 16);
      this.label2.TabIndex = 4;
      this.label2.Text = "Random:";
      this.label2.Visible = false;
      this.textBox3.BorderStyle = BorderStyle.FixedSingle;
      this.textBox3.Location = new Point(855, 36);
      this.textBox3.Name = "textBox3";
      this.textBox3.Size = new Size(48, 22);
      this.textBox3.TabIndex = 2;
      this.textBox3.Visible = false;
      this.groupBox4.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left;
      this.groupBox4.Controls.Add((Control) this.dgItems);
      this.groupBox4.Controls.Add((Control) this.toolStrip2);
      this.groupBox4.Location = new Point(6, 6);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Size = new Size(441, 352);
      this.groupBox4.TabIndex = 44;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "Need Items";
      this.dgItems.AllowUserToAddRows = false;
      this.dgItems.AllowUserToDeleteRows = false;
      this.dgItems.BackgroundColor = SystemColors.Control;
      this.dgItems.BorderStyle = BorderStyle.None;
      this.dgItems.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dgItems.Columns.AddRange((DataGridViewColumn) this.Column7, (DataGridViewColumn) this.Column1, (DataGridViewColumn) this.Column2, (DataGridViewColumn) this.Column3, (DataGridViewColumn) this.Column4, (DataGridViewColumn) this.Column5);
      this.dgItems.Dock = DockStyle.Fill;
      this.dgItems.EnableHeadersVisualStyles = false;
      this.dgItems.Location = new Point(3, 18);
      this.dgItems.Name = "dgItems";
      this.dgItems.RowHeadersVisible = false;
      this.dgItems.RowHeadersWidth = 51;
      this.dgItems.RowTemplate.Height = 32;
      this.dgItems.Size = new Size(435, 304);
      this.dgItems.TabIndex = 0;
      this.dgItems.CellContentClick += new DataGridViewCellEventHandler(this.dgItems_CellContentClick);
      this.Column7.HeaderText = "";
      this.Column7.MinimumWidth = 6;
      this.Column7.Name = "Column7";
      this.Column7.Width = 32;
      this.Column1.HeaderText = "BoxID";
      this.Column1.MinimumWidth = 6;
      this.Column1.Name = "Column1";
      this.Column1.Visible = false;
      this.Column1.Width = 60;
      this.Column2.HeaderText = "ItemID";
      this.Column2.MinimumWidth = 6;
      this.Column2.Name = "Column2";
      this.Column2.Width = 60;
      this.Column3.HeaderText = "Name";
      this.Column3.MinimumWidth = 6;
      this.Column3.Name = "Column3";
      this.Column3.ReadOnly = true;
      this.Column3.Width = 275;
      this.Column4.HeaderText = "Count";
      this.Column4.MinimumWidth = 6;
      this.Column4.Name = "Column4";
      this.Column4.Width = 60;
      this.Column5.HeaderText = "Index";
      this.Column5.MinimumWidth = 6;
      this.Column5.Name = "Column5";
      this.Column5.Visible = false;
      this.Column5.Width = 125;
      this.toolStrip2.Dock = DockStyle.Bottom;
      this.toolStrip2.GripStyle = ToolStripGripStyle.Hidden;
      this.toolStrip2.ImageScalingSize = new Size(20, 20);
      this.toolStrip2.Items.AddRange(new ToolStripItem[5]
      {
        (ToolStripItem) this.btnDeleteSelected,
        (ToolStripItem) this.toolStripSeparator1,
        (ToolStripItem) this.btnAddItems,
        (ToolStripItem) this.toolStripSeparator6,
        (ToolStripItem) this.toolStripButton1
      });
      this.toolStrip2.Location = new Point(3, 322);
      this.toolStrip2.Name = "toolStrip2";
      this.toolStrip2.Size = new Size(435, 27);
      this.toolStrip2.TabIndex = 1;
      this.toolStrip2.Text = "toolStrip2";
      this.btnDeleteSelected.DisplayStyle = ToolStripItemDisplayStyle.Text;
      this.btnDeleteSelected.ImageTransparentColor = Color.Magenta;
      this.btnDeleteSelected.Name = "btnDeleteSelected";
      this.btnDeleteSelected.Size = new Size(78, 24);
      this.btnDeleteSelected.Text = "Save Item";
      this.btnDeleteSelected.Click += new EventHandler(this.btnDeleteSelected_Click);
      this.toolStripSeparator1.Name = "toolStripSeparator1";
      this.toolStripSeparator1.Size = new Size(6, 27);
      this.btnAddItems.DisplayStyle = ToolStripItemDisplayStyle.Text;
      this.btnAddItems.ImageTransparentColor = Color.Magenta;
      this.btnAddItems.Name = "btnAddItems";
      this.btnAddItems.Size = new Size(75, 24);
      this.btnAddItems.Text = "Add Item";
      this.btnAddItems.Click += new EventHandler(this.btnAddItems_Click);
      this.toolStripSeparator6.Name = "toolStripSeparator6";
      this.toolStripSeparator6.Size = new Size(6, 27);
      this.toolStripButton1.DisplayStyle = ToolStripItemDisplayStyle.Text;
      this.toolStripButton1.ImageTransparentColor = Color.Magenta;
      this.toolStripButton1.Name = "toolStripButton1";
      this.toolStripButton1.Size = new Size(118, 24);
      this.toolStripButton1.Text = "Delete Selected";
      this.toolStripButton1.Click += new EventHandler(this.toolStripButton1_Click);
      this.groupBox3.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left;
      this.groupBox3.Controls.Add((Control) this.dgItems2);
      this.groupBox3.Controls.Add((Control) this.toolStrip1);
      this.groupBox3.Location = new Point(6, 6);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Size = new Size(614, 404);
      this.groupBox3.TabIndex = 45;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "Result Items";
      this.dgItems2.AllowUserToAddRows = false;
      this.dgItems2.AllowUserToDeleteRows = false;
      this.dgItems2.BackgroundColor = SystemColors.Control;
      this.dgItems2.BorderStyle = BorderStyle.None;
      this.dgItems2.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dgItems2.Columns.AddRange((DataGridViewColumn) this.dataGridViewImageColumn1, (DataGridViewColumn) this.Column11, (DataGridViewColumn) this.Column12, (DataGridViewColumn) this.Column13, (DataGridViewColumn) this.Column14, (DataGridViewColumn) this.Column15, (DataGridViewColumn) this.Column16, (DataGridViewColumn) this.Column17, (DataGridViewColumn) this.Column10);
      this.dgItems2.Dock = DockStyle.Fill;
      this.dgItems2.EditMode = DataGridViewEditMode.EditOnEnter;
      this.dgItems2.EnableHeadersVisualStyles = false;
      this.dgItems2.Location = new Point(3, 18);
      this.dgItems2.Name = "dgItems2";
      this.dgItems2.RowHeadersVisible = false;
      this.dgItems2.RowHeadersWidth = 51;
      this.dgItems2.RowTemplate.Height = 32;
      this.dgItems2.Size = new Size(608, 356);
      this.dgItems2.TabIndex = 0;
      this.dgItems2.CellContentClick += new DataGridViewCellEventHandler(this.dgItems2_CellContentClick);
      this.dataGridViewImageColumn1.HeaderText = "";
      this.dataGridViewImageColumn1.MinimumWidth = 6;
      this.dataGridViewImageColumn1.Name = "dataGridViewImageColumn1";
      this.dataGridViewImageColumn1.Width = 32;
      this.Column11.HeaderText = "BoxID";
      this.Column11.MinimumWidth = 6;
      this.Column11.Name = "Column11";
      this.Column11.Visible = false;
      this.Column11.Width = 60;
      this.Column12.HeaderText = "ItemID";
      this.Column12.MinimumWidth = 6;
      this.Column12.Name = "Column12";
      this.Column12.Width = 60;
      this.Column13.HeaderText = "Name";
      this.Column13.MinimumWidth = 6;
      this.Column13.Name = "Column13";
      this.Column13.ReadOnly = true;
      this.Column13.Width = 290;
      this.Column14.HeaderText = "Count";
      this.Column14.MinimumWidth = 6;
      this.Column14.Name = "Column14";
      this.Column14.Width = 60;
      this.Column15.HeaderText = "Upgrade";
      this.Column15.MinimumWidth = 6;
      this.Column15.Name = "Column15";
      this.Column15.Width = 60;
      this.Column16.HeaderText = "Prob";
      this.Column16.MinimumWidth = 6;
      this.Column16.Name = "Column16";
      this.Column16.Width = 50;
      this.Column17.HeaderText = "Flag";
      this.Column17.MinimumWidth = 6;
      this.Column17.Name = "Column17";
      this.Column17.Width = 35;
      this.Column10.HeaderText = "Index";
      this.Column10.MinimumWidth = 6;
      this.Column10.Name = "Column10";
      this.Column10.Visible = false;
      this.Column10.Width = 125;
      this.toolStrip1.Dock = DockStyle.Bottom;
      this.toolStrip1.GripStyle = ToolStripGripStyle.Hidden;
      this.toolStrip1.ImageScalingSize = new Size(20, 20);
      this.toolStrip1.Items.AddRange(new ToolStripItem[5]
      {
        (ToolStripItem) this.toolStripButton2,
        (ToolStripItem) this.toolStripSeparator2,
        (ToolStripItem) this.toolStripButton3,
        (ToolStripItem) this.toolStripSeparator3,
        (ToolStripItem) this.toolStripButton4
      });
      this.toolStrip1.Location = new Point(3, 374);
      this.toolStrip1.Name = "toolStrip1";
      this.toolStrip1.Size = new Size(608, 27);
      this.toolStrip1.TabIndex = 1;
      this.toolStrip1.Text = "toolStrip1";
      this.toolStripButton2.DisplayStyle = ToolStripItemDisplayStyle.Text;
      this.toolStripButton2.ImageTransparentColor = Color.Magenta;
      this.toolStripButton2.Name = "toolStripButton2";
      this.toolStripButton2.Size = new Size(78, 24);
      this.toolStripButton2.Text = "Save Item";
      this.toolStripButton2.Click += new EventHandler(this.toolStripButton2_Click);
      this.toolStripSeparator2.Name = "toolStripSeparator2";
      this.toolStripSeparator2.Size = new Size(6, 27);
      this.toolStripButton3.DisplayStyle = ToolStripItemDisplayStyle.Text;
      this.toolStripButton3.ImageTransparentColor = Color.Magenta;
      this.toolStripButton3.Name = "toolStripButton3";
      this.toolStripButton3.Size = new Size(75, 24);
      this.toolStripButton3.Text = "Add Item";
      this.toolStripButton3.Click += new EventHandler(this.toolStripButton3_Click);
      this.toolStripSeparator3.Name = "toolStripSeparator3";
      this.toolStripSeparator3.Size = new Size(6, 27);
      this.toolStripButton4.DisplayStyle = ToolStripItemDisplayStyle.Text;
      this.toolStripButton4.ImageTransparentColor = Color.Magenta;
      this.toolStripButton4.Name = "toolStripButton4";
      this.toolStripButton4.Size = new Size(118, 24);
      this.toolStripButton4.Text = "Delete Selected";
      this.toolStripButton4.Click += new EventHandler(this.toolStripButton4_Click);
      this.tabControl1.Controls.Add((Control) this.tabPage1);
      this.tabControl1.Controls.Add((Control) this.tabPage2);
      this.tabControl1.Location = new Point(241, 95);
      this.tabControl1.Name = "tabControl1";
      this.tabControl1.SelectedIndex = 0;
      this.tabControl1.Size = new Size(636, 447);
      this.tabControl1.TabIndex = 46;
      this.tabPage1.BorderStyle = BorderStyle.FixedSingle;
      this.tabPage1.Controls.Add((Control) this.groupBox3);
      this.tabPage1.Location = new Point(4, 25);
      this.tabPage1.Name = "tabPage1";
      this.tabPage1.Padding = new Padding(3);
      this.tabPage1.Size = new Size(628, 418);
      this.tabPage1.TabIndex = 0;
      this.tabPage1.Text = "Result Items";
      this.tabPage2.BorderStyle = BorderStyle.FixedSingle;
      this.tabPage2.Controls.Add((Control) this.groupBox4);
      this.tabPage2.Location = new Point(4, 25);
      this.tabPage2.Name = "tabPage2";
      this.tabPage2.Padding = new Padding(3);
      this.tabPage2.Size = new Size(628, 418);
      this.tabPage2.TabIndex = 1;
      this.tabPage2.Text = "Need Items";
      this.statusStrip1.ImageScalingSize = new Size(20, 20);
      this.statusStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.toolStripStatusLabel1
      });
      this.statusStrip1.Location = new Point(0, 599);
      this.statusStrip1.Name = "statusStrip1";
      this.statusStrip1.Size = new Size(907, 26);
      this.statusStrip1.TabIndex = 50;
      this.statusStrip1.Text = "statusStrip1";
      this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
      this.toolStripStatusLabel1.Size = new Size(50, 20);
      this.toolStripStatusLabel1.Text = "Ready";
      this.textBox5.BorderStyle = BorderStyle.FixedSingle;
      this.textBox5.Location = new Point(292, 561);
      this.textBox5.Name = "textBox5";
      this.textBox5.Size = new Size(51, 22);
      this.textBox5.TabIndex = 51;
      this.textBox5.Visible = false;
      this.ClientSize = new Size(907, 625);
      this.Controls.Add((Control) this.textBox5);
      this.Controls.Add((Control) this.statusStrip1);
      this.Controls.Add((Control) this.tabControl1);
      this.Controls.Add((Control) this.label3);
      this.Controls.Add((Control) this.groupBox2);
      this.Controls.Add((Control) this.textBox4);
      this.Controls.Add((Control) this.label2);
      this.Controls.Add((Control) this.button3);
      this.Controls.Add((Control) this.groupBox1);
      this.Controls.Add((Control) this.textBox3);
      this.Icon = (Icon) componentResourceManager.GetObject("$this.Icon");
      this.MaximizeBox = false;
      this.Name = nameof (LuckyDrawBoxTool);
      this.Text = "LuckyDrawBox Editor";
      this.Load += new EventHandler(this.LuckyDrawBoxTool_Load);
      this.groupBox1.ResumeLayout(false);
      this.groupBox2.ResumeLayout(false);
      this.groupBox2.PerformLayout();
      this.groupBox4.ResumeLayout(false);
      this.groupBox4.PerformLayout();
      ((ISupportInitialize) this.dgItems).EndInit();
      this.toolStrip2.ResumeLayout(false);
      this.toolStrip2.PerformLayout();
      this.groupBox3.ResumeLayout(false);
      this.groupBox3.PerformLayout();
      ((ISupportInitialize) this.dgItems2).EndInit();
      this.toolStrip1.ResumeLayout(false);
      this.toolStrip1.PerformLayout();
      this.tabControl1.ResumeLayout(false);
      this.tabPage1.ResumeLayout(false);
      this.tabPage2.ResumeLayout(false);
      this.statusStrip1.ResumeLayout(false);
      this.statusStrip1.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
