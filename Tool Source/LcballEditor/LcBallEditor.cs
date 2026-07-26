// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.LcBallEditor.LcBallEditor
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using LcDevPack_TeamDamonA.Properties;
using LcDevPack_TeamDamonA.Tools;
using MySqlConnector;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.LcBallEditor
{
  public class LcBallEditor : Form
  {
    public static Connection connection = new Connection();
    private string Host = LcDevPack_TeamDamonA.LcBallEditor.LcBallEditor.connection.Settings.SqlHost;
    private string User = LcDevPack_TeamDamonA.LcBallEditor.LcBallEditor.connection.Settings.SqlUser;
    private string Password = LcDevPack_TeamDamonA.LcBallEditor.LcBallEditor.connection.Settings.SqlPassword;
    private string Database = LcDevPack_TeamDamonA.LcBallEditor.LcBallEditor.connection.Settings.SqlDatabase;
    private string DB_Database = LcDevPack_TeamDamonA.LcBallEditor.LcBallEditor.connection.Settings.SqlDbDatabase;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    public string _ClientPath = LcDevPack_TeamDamonA.LcBallEditor.LcBallEditor.connection.Settings.ClientPath;
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
    private TextBox textBox6;
    private TextBox textBox5;
    private Label label2;
    private Label label1;
    private Button button4;
    private string country;
    public static string namee;
    private string language = LcDevPack_TeamDamonA.LcBallEditor.LcBallEditor.connection.Settings.Language;
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
    private Button button2;
    private GroupBox groupBox2;
    private DataGridView dgItems;
    private GroupBox groupBox3;
    private DataGridView dgItems1;
    private GroupBox groupBox4;
    private TextBox textBox2;
    private Label label4;
    private TextBox textBox1;
    private Label label3;
    private TextBox tb_item_qty;
    private Label label9;
    private Button button5;
    private TextBox tb_item_name;
    private TextBox tb_item_id;
    private PictureBox pictureBox2;
    private Label label10;
    private Label label11;
    private DataGridViewTextBoxColumn Oder;
    private DataGridViewImageColumn Icon;
    private DataGridViewTextBoxColumn Item;
    private DataGridViewTextBoxColumn ItemName;
    private DataGridViewTextBoxColumn course_code;
    private TextBox textBox16;
    private ComboBox comboBox1;
    private Label label6;
    private Button button18;
    private Button button1;
    private PictureBox pictureBox1;
    private TextBox textBox3;
    private Label label5;
    private Button button3;
    private TextBox textBox4;
    private TextBox textBox7;
    private DataGridViewTextBoxColumn Order1;
    private DataGridViewImageColumn dataGridViewImageColumn1;
    private DataGridViewTextBoxColumn Item1;
    private DataGridViewTextBoxColumn ItemName1;
    private DataGridViewTextBoxColumn Count1;
    private DataGridViewTextBoxColumn Max1;
    private DataGridViewTextBoxColumn Remain1;
    private DataGridViewTextBoxColumn Index1;
    private TextBox textBox8;
    public string[] menuArrayUSA = new string[2]
    {
      "a_index",
      "a_string_usa"
    };

    public LcBallEditor()
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
        LcDevPack_TeamDamonA.LcBallEditor.LcBallEditor.namee = "a_string_ger";
        return LcDevPack_TeamDamonA.LcBallEditor.LcBallEditor.namee;
      }
      if (this.language == "POL")
      {
        LcDevPack_TeamDamonA.LcBallEditor.LcBallEditor.namee = "a_string_pld";
        return LcDevPack_TeamDamonA.LcBallEditor.LcBallEditor.namee;
      }
      if (this.language == "BRA")
      {
        LcDevPack_TeamDamonA.LcBallEditor.LcBallEditor.namee = "a_string_brz";
        return LcDevPack_TeamDamonA.LcBallEditor.LcBallEditor.namee;
      }
      if (this.language == "RUS")
      {
        LcDevPack_TeamDamonA.LcBallEditor.LcBallEditor.namee = "a_string_rus";
        return LcDevPack_TeamDamonA.LcBallEditor.LcBallEditor.namee;
      }
      if (this.language == "FRA")
      {
        LcDevPack_TeamDamonA.LcBallEditor.LcBallEditor.namee = "a_string_frc";
        return LcDevPack_TeamDamonA.LcBallEditor.LcBallEditor.namee;
      }
      if (this.language == "ESP")
      {
        LcDevPack_TeamDamonA.LcBallEditor.LcBallEditor.namee = "a_string_spn";
        return LcDevPack_TeamDamonA.LcBallEditor.LcBallEditor.namee;
      }
      if (this.language == "MEX")
      {
        LcDevPack_TeamDamonA.LcBallEditor.LcBallEditor.namee = "a_string_mex";
        return LcDevPack_TeamDamonA.LcBallEditor.LcBallEditor.namee;
      }
      if (this.language == "THA")
      {
        LcDevPack_TeamDamonA.LcBallEditor.LcBallEditor.namee = "a_string_thai";
        return LcDevPack_TeamDamonA.LcBallEditor.LcBallEditor.namee;
      }
      if (this.language == "ITA")
      {
        LcDevPack_TeamDamonA.LcBallEditor.LcBallEditor.namee = "a_string_ita";
        return LcDevPack_TeamDamonA.LcBallEditor.LcBallEditor.namee;
      }
      if (!(this.language == "USA"))
        return (string) null;
      LcDevPack_TeamDamonA.LcBallEditor.LcBallEditor.namee = "a_string_usa";
      return LcDevPack_TeamDamonA.LcBallEditor.LcBallEditor.namee;
    }

		private void LoadStartUp()
		{
			string query = "SELECT MAX(a_item_order) AS max_order FROM t_lcball;";

			using (var connection = new MySqlConnection(
				"datasource=" + this.Host +
				";port=3306;" +
				"username=" + this.User +
				";password=" + this.Password +
				";database=" + this.DB_Database +
				";Charset=utf8mb4;" +
				"SslMode=None;"))
			{
				using (var command = new MySqlCommand(query, connection))
				{
					connection.Open();
					object result = command.ExecuteScalar(); // simpler since it's a single value

					if (result != null && int.TryParse(result.ToString(), out int maxOrder))
					{
						textBox8.Text = maxOrder.ToString();
					}
					else
					{
						textBox8.Text = "0"; // default if empty table
					}
				}
			}
		}


		public void LoadDG()
		{
			dgItems.Rows.Clear();

			string query = @"
        SELECT a_index, a_item_order, a_tocken_index, a_course_code, 
               a_order, a_item_index, a_item_count, a_item_max, a_item_remain
        FROM t_lcball
        ORDER BY a_item_order;";

			using (var connection = new MySqlConnection(
				"datasource=" + Host +
				";port=3306;" +
				"username=" + User +
				";password=" + Password +
				";database=" + DB_Database +
				";Charset=utf8mb4;" +
				"SslMode=None;"))
			{
				using (var command = new MySqlCommand(query, connection))
				{
					connection.Open();
					using (var reader = command.ExecuteReader())
					{
						while (reader.Read())
						{
							int index = SafeInt(reader["a_index"]);
							int itemOrder = SafeInt(reader["a_item_order"]);
							int tokenIndex = SafeInt(reader["a_tocken_index"]);
							string courseCode = reader["a_course_code"]?.ToString() ?? "";
							string itemName = databaseHandle.ItemNameFast(tokenIndex);
							var icon = databaseHandle.IconFast(tokenIndex);

							dgItems.Rows.Add(itemOrder, icon, tokenIndex, itemName, courseCode);
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
      this.textBox6.Text = row.Cells["Oder"].Value.ToString();
      this.textBox5.Text = row.Cells["Item"].Value.ToString();
      this.textBox3.Text = row.Cells["course_code"].Value.ToString();
      this.comboBox1.SelectedIndex = 0;
      this.textBox3.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox5.Text.Trim()));
      this.LoadDG1();
    }

		public void LoadDG1()
		{
			dgItems1.Rows.Clear();

			string query = @"
        SELECT a_index, a_item_order, a_tocken_index, a_course_code,
               a_order, a_item_index, a_item_count, a_item_max, a_item_remain
        FROM t_lcball
        WHERE a_item_order = @order
          AND a_course_code = @course
        ORDER BY a_order;";

			using (var connection = new MySqlConnection(
				"datasource=" + Host +
				";port=3306;" +
				"username=" + User +
				";password=" + Password +
				";database=" + DB_Database +
				";Charset=utf8mb4;" +
				"SslMode=None;"))
			{
				using (var command = new MySqlCommand(query, connection))
				{
					// Parameter binding = no injection, automatic quoting
					command.Parameters.AddWithValue("@order", textBox6.Text);
					command.Parameters.AddWithValue("@course", textBox16.Text);

					connection.Open();
					using (var reader = command.ExecuteReader())
					{
						while (reader.Read())
						{
							int index = SafeInt(reader["a_index"]);
							int itemOrder = SafeInt(reader["a_item_order"]);
							int tokenIndex = SafeInt(reader["a_tocken_index"]);
							string courseCode = reader["a_course_code"]?.ToString() ?? "";
							int order = SafeInt(reader["a_order"]);
							int itemIndex = SafeInt(reader["a_item_index"]);
							int itemCount = SafeInt(reader["a_item_count"]);
							int itemMax = SafeInt(reader["a_item_max"]);
							int itemRemain = SafeInt(reader["a_item_remain"]);

							string itemName = databaseHandle.ItemNameFast(itemIndex);
							var icon = databaseHandle.IconFast(itemIndex);

							dgItems1.Rows.Add(
								order,              // a_order
								icon,               // icon for a_item_index
								itemIndex,          // a_item_index
								itemName,           // item name
								itemCount,          // a_item_count
								itemMax,            // a_item_max
								itemRemain,         // a_item_remain
								index               // a_index
							);
						}
					}
				}
			}
		}



		private void dgItems1_CellClick(object sender, DataGridViewCellEventArgs e)
    {
      if (e.RowIndex < 0)
        return;
      DataGridViewRow row = this.dgItems1.Rows[e.RowIndex];
      this.textBox7.Text = row.Cells["Index1"].Value.ToString();
      this.textBox4.Text = row.Cells["Order1"].Value.ToString();
      this.tb_item_id.Text = row.Cells["Item1"].Value.ToString();
      this.tb_item_qty.Text = row.Cells["Count1"].Value.ToString();
      this.textBox1.Text = row.Cells["Max1"].Value.ToString();
      this.textBox2.Text = row.Cells["Remain1"].Value.ToString();
      this.tb_item_name.Text = this.databaseHandle.ItemNameFast(int.Parse(this.tb_item_id.Text.Trim()));
    }

    private int GetID()
    {
      int result = -1;
      int.TryParse(this.textBox6.Text.Split(' ')[0], out result);
      return result;
    }

    private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox16.Text = this.comboBox1.SelectedIndex.ToString();
      this.LoadDG1();
    }

    private void ClearBox()
    {
    }

    private void textBox6_TextChanged(object sender, EventArgs e)
    {
    }

    private void textBox5_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox1.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox5.Text.Trim()));
      this.textBox3.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox5.Text.Trim()));
    }

    private void exitToolStripMenuItem_Click(object sender, EventArgs e) => this.Close();

    private void button1_Click(object sender, EventArgs e)
    {
      if (this.textBox7.Text.Trim().Length <= 0)
      {
        int num1 = (int) MessageBox.Show("please Select Data", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else if (this.tb_item_id.Text.Trim().Length <= 0)
      {
        int num2 = (int) MessageBox.Show("please add Item id", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.DB_Database, "UPDATE t_lcball SET a_item_index  = '" + this.tb_item_id.Text + "', a_item_count ='" + this.tb_item_qty.Text + "',a_item_max ='" + this.textBox1.Text + "',a_item_remain ='" + this.textBox2.Text + "' WHERE a_index = '" + this.textBox7.Text + "'");
        int num3 = (int) MessageBox.Show("Update", "Completed", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
        this.LoadDG1();
        this.textBox7.Text = "";
      }
    }

    private void button2_Click(object sender, EventArgs e)
    {
      string str = Convert.ToString(Convert.ToInt32(this.textBox8.Text) + 1);
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.DB_Database, "INSERT INTO t_lcball (a_item_order, a_tocken_index, a_course_code, a_order, a_item_index, a_item_count, a_item_max, a_item_remain) VALUES ('" + str + "','" + this.textBox5.Text + "', '0', '0', '19', '100', '100', '100')");
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.DB_Database, "INSERT INTO t_lcball (a_item_order, a_tocken_index, a_course_code, a_order, a_item_index, a_item_count, a_item_max, a_item_remain) VALUES ('" + str + "','" + this.textBox5.Text + "', '0', '1', '19', '100', '100', '100')");
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.DB_Database, "INSERT INTO t_lcball (a_item_order, a_tocken_index, a_course_code, a_order, a_item_index, a_item_count, a_item_max, a_item_remain) VALUES ('" + str + "','" + this.textBox5.Text + "', '0', '2', '19', '100', '100', '100')");
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.DB_Database, "INSERT INTO t_lcball (a_item_order, a_tocken_index, a_course_code, a_order, a_item_index, a_item_count, a_item_max, a_item_remain) VALUES ('" + str + "','" + this.textBox5.Text + "', '0', '3', '19', '100', '100', '100')");
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.DB_Database, "INSERT INTO t_lcball (a_item_order, a_tocken_index, a_course_code, a_order, a_item_index, a_item_count, a_item_max, a_item_remain) VALUES ('" + str + "','" + this.textBox5.Text + "', '0', '4', '19', '100', '100', '100')");
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.DB_Database, "INSERT INTO t_lcball (a_item_order, a_tocken_index, a_course_code, a_order, a_item_index, a_item_count, a_item_max, a_item_remain) VALUES ('" + str + "','" + this.textBox5.Text + "', '1', '0', '19', '100', '100', '100')");
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.DB_Database, "INSERT INTO t_lcball (a_item_order, a_tocken_index, a_course_code, a_order, a_item_index, a_item_count, a_item_max, a_item_remain) VALUES ('" + str + "','" + this.textBox5.Text + "', '1', '1', '19', '100', '100', '100')");
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.DB_Database, "INSERT INTO t_lcball (a_item_order, a_tocken_index, a_course_code, a_order, a_item_index, a_item_count, a_item_max, a_item_remain) VALUES ('" + str + "','" + this.textBox5.Text + "', '1', '2', '19', '100', '100', '100')");
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.DB_Database, "INSERT INTO t_lcball (a_item_order, a_tocken_index, a_course_code, a_order, a_item_index, a_item_count, a_item_max, a_item_remain) VALUES ('" + str + "','" + this.textBox5.Text + "', '1', '3', '19', '100', '100', '100')");
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.DB_Database, "INSERT INTO t_lcball (a_item_order, a_tocken_index, a_course_code, a_order, a_item_index, a_item_count, a_item_max, a_item_remain) VALUES ('" + str + "','" + this.textBox5.Text + "', '1', '4', '19', '100', '100', '100')");
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.DB_Database, "INSERT INTO t_lcball (a_item_order, a_tocken_index, a_course_code, a_order, a_item_index, a_item_count, a_item_max, a_item_remain) VALUES ('" + str + "','" + this.textBox5.Text + "', '2', '0', '19', '100', '100', '100')");
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.DB_Database, "INSERT INTO t_lcball (a_item_order, a_tocken_index, a_course_code, a_order, a_item_index, a_item_count, a_item_max, a_item_remain) VALUES ('" + str + "','" + this.textBox5.Text + "', '2', '1', '19', '100', '100', '100')");
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.DB_Database, "INSERT INTO t_lcball (a_item_order, a_tocken_index, a_course_code, a_order, a_item_index, a_item_count, a_item_max, a_item_remain) VALUES ('" + str + "','" + this.textBox5.Text + "', '2', '2', '19', '100', '100', '100')");
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.DB_Database, "INSERT INTO t_lcball (a_item_order, a_tocken_index, a_course_code, a_order, a_item_index, a_item_count, a_item_max, a_item_remain) VALUES ('" + str + "','" + this.textBox5.Text + "', '2', '3', '19', '100', '100', '100')");
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.DB_Database, "INSERT INTO t_lcball (a_item_order, a_tocken_index, a_course_code, a_order, a_item_index, a_item_count, a_item_max, a_item_remain) VALUES ('" + str + "','" + this.textBox5.Text + "', '2', '4', '19', '100', '100', '100')");
      int num = (int) MessageBox.Show("Successful Add New Order", "Completed", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
      this.textBox7.Text = "";
      this.LoadDG();
      this.LoadStartUp();
    }

    private void button4_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want to Delete Order " + this.textBox3.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.DB_Database, "DELETE FROM t_lcball WHERE a_item_order = '" + this.textBox6.Text + "'");
      this.LoadDG();
      this.LoadStartUp();
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
      this.pictureBox1 = new PictureBox();
      this.textBox3 = new TextBox();
      this.label5 = new Label();
      this.button3 = new Button();
      this.button18 = new Button();
      this.button2 = new Button();
      this.button4 = new Button();
      this.textBox6 = new TextBox();
      this.textBox5 = new TextBox();
      this.label2 = new Label();
      this.label1 = new Label();
      this.groupBox2 = new GroupBox();
      this.dgItems = new DataGridView();
      this.Oder = new DataGridViewTextBoxColumn();
      this.Icon = new DataGridViewImageColumn();
      this.Item = new DataGridViewTextBoxColumn();
      this.ItemName = new DataGridViewTextBoxColumn();
      this.course_code = new DataGridViewTextBoxColumn();
      this.groupBox3 = new GroupBox();
      this.dgItems1 = new DataGridView();
      this.Order1 = new DataGridViewTextBoxColumn();
      this.dataGridViewImageColumn1 = new DataGridViewImageColumn();
      this.Item1 = new DataGridViewTextBoxColumn();
      this.ItemName1 = new DataGridViewTextBoxColumn();
      this.Count1 = new DataGridViewTextBoxColumn();
      this.Max1 = new DataGridViewTextBoxColumn();
      this.Remain1 = new DataGridViewTextBoxColumn();
      this.Index1 = new DataGridViewTextBoxColumn();
      this.groupBox4 = new GroupBox();
      this.button1 = new Button();
      this.textBox2 = new TextBox();
      this.label4 = new Label();
      this.textBox1 = new TextBox();
      this.label3 = new Label();
      this.tb_item_qty = new TextBox();
      this.label9 = new Label();
      this.button5 = new Button();
      this.tb_item_name = new TextBox();
      this.tb_item_id = new TextBox();
      this.pictureBox2 = new PictureBox();
      this.label10 = new Label();
      this.label11 = new Label();
      this.textBox4 = new TextBox();
      this.textBox16 = new TextBox();
      this.comboBox1 = new ComboBox();
      this.label6 = new Label();
      this.textBox7 = new TextBox();
      this.textBox8 = new TextBox();
      this.groupBox1.SuspendLayout();
      ((ISupportInitialize) this.pictureBox1).BeginInit();
      this.groupBox2.SuspendLayout();
      ((ISupportInitialize) this.dgItems).BeginInit();
      this.groupBox3.SuspendLayout();
      ((ISupportInitialize) this.dgItems1).BeginInit();
      this.groupBox4.SuspendLayout();
      ((ISupportInitialize) this.pictureBox2).BeginInit();
      this.SuspendLayout();
      this.groupBox1.Controls.Add((Control) this.pictureBox1);
      this.groupBox1.Controls.Add((Control) this.textBox3);
      this.groupBox1.Controls.Add((Control) this.label5);
      this.groupBox1.Controls.Add((Control) this.button3);
      this.groupBox1.Controls.Add((Control) this.button18);
      this.groupBox1.Controls.Add((Control) this.button2);
      this.groupBox1.Controls.Add((Control) this.button4);
      this.groupBox1.Controls.Add((Control) this.textBox6);
      this.groupBox1.Controls.Add((Control) this.textBox5);
      this.groupBox1.Controls.Add((Control) this.label2);
      this.groupBox1.Controls.Add((Control) this.label1);
      this.groupBox1.Location = new Point(12, 259);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(325, 152);
      this.groupBox1.TabIndex = 2;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Token";
      this.pictureBox1.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox1.Location = new Point(78, 19);
      this.pictureBox1.Name = "pictureBox1";
      this.pictureBox1.Size = new Size(42, 40);
      this.pictureBox1.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pictureBox1.TabIndex = 107;
      this.pictureBox1.TabStop = false;
      this.textBox3.Enabled = false;
      this.textBox3.Location = new Point(78, 69);
      this.textBox3.Name = "textBox3";
      this.textBox3.Size = new Size(212, 20);
      this.textBox3.TabIndex = 105;
      this.label5.AutoSize = true;
      this.label5.Location = new Point(22, 72);
      this.label5.Name = "label5";
      this.label5.Size = new Size(41, 13);
      this.label5.TabIndex = 106;
      this.label5.Text = "Name :";
      this.button3.Image = (Image) Resources.search__5_;
      this.button3.Location = new Point(248, 28);
      this.button3.Name = "button3";
      this.button3.Size = new Size(30, 27);
      this.button3.TabIndex = 104;
      this.button3.UseVisualStyleBackColor = true;
      this.button3.Click += new EventHandler(this.button3_Click_1);
      this.button18.BackColor = Color.LightCyan;
      this.button18.FlatStyle = FlatStyle.Flat;
      this.button18.Image = (Image) Resources._08;
      this.button18.ImageAlign = ContentAlignment.MiddleLeft;
      this.button18.Location = new Point(99, 108);
      this.button18.Name = "button18";
      this.button18.Size = new Size(72, 27);
      this.button18.TabIndex = 103;
      this.button18.Text = "      Update";
      this.button18.UseVisualStyleBackColor = false;
      this.button18.Click += new EventHandler(this.button18_Click);
      this.button2.BackColor = Color.Gold;
      this.button2.FlatStyle = FlatStyle.Flat;
      this.button2.Image = (Image) Resources.control_add_blue;
      this.button2.ImageAlign = ContentAlignment.MiddleLeft;
      this.button2.Location = new Point(6, 108);
      this.button2.Name = "button2";
      this.button2.Size = new Size(77, 27);
      this.button2.TabIndex = 67;
      this.button2.Text = "    Add";
      this.button2.UseVisualStyleBackColor = false;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.button4.BackColor = Color.LightCoral;
      this.button4.FlatStyle = FlatStyle.Flat;
      this.button4.Image = (Image) Resources.delete;
      this.button4.ImageAlign = ContentAlignment.MiddleLeft;
      this.button4.Location = new Point(242, 108);
      this.button4.Name = "button4";
      this.button4.Size = new Size(77, 27);
      this.button4.TabIndex = 66;
      this.button4.Text = "    Delete";
      this.button4.UseVisualStyleBackColor = false;
      this.button4.Click += new EventHandler(this.button4_Click);
      this.textBox6.Enabled = false;
      this.textBox6.Location = new Point(14, 32);
      this.textBox6.Name = "textBox6";
      this.textBox6.Size = new Size(49, 20);
      this.textBox6.TabIndex = 4;
      this.textBox6.TextChanged += new EventHandler(this.textBox6_TextChanged);
      this.textBox5.Enabled = false;
      this.textBox5.Location = new Point(136, 32);
      this.textBox5.Name = "textBox5";
      this.textBox5.Size = new Size(93, 20);
      this.textBox5.TabIndex = 3;
      this.textBox5.TextChanged += new EventHandler(this.textBox5_TextChanged);
      this.label2.AutoSize = true;
      this.label2.Location = new Point(133, 16);
      this.label2.Name = "label2";
      this.label2.Size = new Size(30, 13);
      this.label2.TabIndex = 1;
      this.label2.Text = "Item:";
      this.label1.AutoSize = true;
      this.label1.Location = new Point(11, 16);
      this.label1.Name = "label1";
      this.label1.Size = new Size(36, 13);
      this.label1.TabIndex = 0;
      this.label1.Text = "Order:";
      this.groupBox2.Controls.Add((Control) this.dgItems);
      this.groupBox2.Location = new Point(12, 12);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new Size(325, 241);
      this.groupBox2.TabIndex = 34;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "TOKEN ORDER";
      this.dgItems.AllowUserToAddRows = false;
      this.dgItems.AllowUserToDeleteRows = false;
      this.dgItems.BackgroundColor = SystemColors.Control;
      this.dgItems.BorderStyle = BorderStyle.None;
      this.dgItems.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dgItems.Columns.AddRange((DataGridViewColumn) this.Oder, (DataGridViewColumn) this.Icon, (DataGridViewColumn) this.Item, (DataGridViewColumn) this.ItemName, (DataGridViewColumn) this.course_code);
      this.dgItems.EnableHeadersVisualStyles = false;
      this.dgItems.Location = new Point(6, 19);
      this.dgItems.Name = "dgItems";
      this.dgItems.RowHeadersVisible = false;
      this.dgItems.RowTemplate.Height = 32;
      this.dgItems.ScrollBars = ScrollBars.Vertical;
      this.dgItems.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
      this.dgItems.Size = new Size(315, 216);
      this.dgItems.TabIndex = 1;
      this.dgItems.CellClick += new DataGridViewCellEventHandler(this.dgItems_CellClick);
      this.Oder.HeaderText = "Oder";
      this.Oder.Name = "Oder";
      this.Oder.Width = 50;
      this.Icon.HeaderText = "";
      this.Icon.Name = "Icon";
      this.Icon.Width = 32;
      this.Item.HeaderText = "Item";
      this.Item.Name = "Item";
      this.Item.Width = 70;
      this.ItemName.HeaderText = "Item Name";
      this.ItemName.Name = "ItemName";
      this.ItemName.Width = 160;
      this.course_code.HeaderText = "course_code";
      this.course_code.Name = "course_code";
      this.groupBox3.Controls.Add((Control) this.dgItems1);
      this.groupBox3.Location = new Point(363, 78);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Size = new Size(528, 210);
      this.groupBox3.TabIndex = 35;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "ITEM ORDER";
      this.dgItems1.AllowUserToAddRows = false;
      this.dgItems1.AllowUserToDeleteRows = false;
      this.dgItems1.BackgroundColor = SystemColors.Control;
      this.dgItems1.BorderStyle = BorderStyle.None;
      this.dgItems1.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dgItems1.Columns.AddRange((DataGridViewColumn) this.Order1, (DataGridViewColumn) this.dataGridViewImageColumn1, (DataGridViewColumn) this.Item1, (DataGridViewColumn) this.ItemName1, (DataGridViewColumn) this.Count1, (DataGridViewColumn) this.Max1, (DataGridViewColumn) this.Remain1, (DataGridViewColumn) this.Index1);
      this.dgItems1.EnableHeadersVisualStyles = false;
      this.dgItems1.Location = new Point(6, 19);
      this.dgItems1.Name = "dgItems1";
      this.dgItems1.RowHeadersVisible = false;
      this.dgItems1.RowTemplate.Height = 32;
      this.dgItems1.ScrollBars = ScrollBars.Vertical;
      this.dgItems1.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
      this.dgItems1.Size = new Size(516, 178);
      this.dgItems1.TabIndex = 1;
      this.dgItems1.CellClick += new DataGridViewCellEventHandler(this.dgItems1_CellClick);
      this.Order1.HeaderText = "Oder";
      this.Order1.Name = "Order1";
      this.Order1.Width = 50;
      this.dataGridViewImageColumn1.HeaderText = "";
      this.dataGridViewImageColumn1.Name = "dataGridViewImageColumn1";
      this.dataGridViewImageColumn1.Width = 32;
      this.Item1.HeaderText = "Item";
      this.Item1.Name = "Item1";
      this.Item1.Width = 70;
      this.ItemName1.HeaderText = "Item Name";
      this.ItemName1.Name = "ItemName1";
      this.ItemName1.Width = 160;
      this.Count1.HeaderText = "Count";
      this.Count1.Name = "Count1";
      this.Count1.Width = 70;
      this.Max1.HeaderText = "Max";
      this.Max1.Name = "Max1";
      this.Max1.Width = 70;
      this.Remain1.HeaderText = "Remain";
      this.Remain1.Name = "Remain1";
      this.Remain1.Width = 70;
      this.Index1.HeaderText = "Index1";
      this.Index1.Name = "Index1";
      this.groupBox4.BackColor = Color.Linen;
      this.groupBox4.Controls.Add((Control) this.button1);
      this.groupBox4.Controls.Add((Control) this.textBox2);
      this.groupBox4.Controls.Add((Control) this.label4);
      this.groupBox4.Controls.Add((Control) this.textBox1);
      this.groupBox4.Controls.Add((Control) this.label3);
      this.groupBox4.Controls.Add((Control) this.tb_item_qty);
      this.groupBox4.Controls.Add((Control) this.label9);
      this.groupBox4.Controls.Add((Control) this.button5);
      this.groupBox4.Controls.Add((Control) this.tb_item_name);
      this.groupBox4.Controls.Add((Control) this.tb_item_id);
      this.groupBox4.Controls.Add((Control) this.pictureBox2);
      this.groupBox4.Controls.Add((Control) this.label10);
      this.groupBox4.Controls.Add((Control) this.label11);
      this.groupBox4.Location = new Point(363, 294);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Size = new Size(528, 97);
      this.groupBox4.TabIndex = 36;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "Item Editor";
      this.button1.BackColor = Color.LightCyan;
      this.button1.FlatStyle = FlatStyle.Flat;
      this.button1.Image = (Image) Resources._08;
      this.button1.ImageAlign = ContentAlignment.MiddleLeft;
      this.button1.Location = new Point(450, 19);
      this.button1.Name = "button1";
      this.button1.Size = new Size(72, 67);
      this.button1.TabIndex = 104;
      this.button1.Text = "      Update";
      this.button1.UseVisualStyleBackColor = false;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.textBox2.Location = new Point(366, 70);
      this.textBox2.Name = "textBox2";
      this.textBox2.Size = new Size(78, 20);
      this.textBox2.TabIndex = 23;
      this.label4.AutoSize = true;
      this.label4.Location = new Point(314, 73);
      this.label4.Name = "label4";
      this.label4.Size = new Size(52, 13);
      this.label4.TabIndex = 22;
      this.label4.Text = "Remain : ";
      this.textBox1.Location = new Point(366, 30);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(78, 20);
      this.textBox1.TabIndex = 21;
      this.label3.AutoSize = true;
      this.label3.Location = new Point(324, 35);
      this.label3.Name = "label3";
      this.label3.Size = new Size(36, 13);
      this.label3.TabIndex = 20;
      this.label3.Text = "Max : ";
      this.tb_item_qty.Location = new Point(244, 32);
      this.tb_item_qty.Name = "tb_item_qty";
      this.tb_item_qty.Size = new Size(78, 20);
      this.tb_item_qty.TabIndex = 19;
      this.label9.AutoSize = true;
      this.label9.Location = new Point(204, 35);
      this.label9.Name = "label9";
      this.label9.Size = new Size(34, 13);
      this.label9.TabIndex = 18;
      this.label9.Text = "Q'ty : ";
      this.button5.Image = (Image) Resources.search__5_;
      this.button5.Location = new Point(168, 28);
      this.button5.Name = "button5";
      this.button5.Size = new Size(30, 27);
      this.button5.TabIndex = 13;
      this.button5.UseVisualStyleBackColor = true;
      this.button5.Click += new EventHandler(this.button5_Click);
      this.tb_item_name.Enabled = false;
      this.tb_item_name.Location = new Point(96, 58);
      this.tb_item_name.Name = "tb_item_name";
      this.tb_item_name.Size = new Size(212, 20);
      this.tb_item_name.TabIndex = 15;
      this.tb_item_id.Enabled = false;
      this.tb_item_id.Location = new Point(84, 34);
      this.tb_item_id.Name = "tb_item_id";
      this.tb_item_id.Size = new Size(78, 20);
      this.tb_item_id.TabIndex = 14;
      this.tb_item_id.TextChanged += new EventHandler(this.tb_item_id_TextChanged);
      this.pictureBox2.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox2.Location = new Point(11, 34);
      this.pictureBox2.Name = "pictureBox2";
      this.pictureBox2.Size = new Size(42, 40);
      this.pictureBox2.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pictureBox2.TabIndex = 10;
      this.pictureBox2.TabStop = false;
      this.label10.AutoSize = true;
      this.label10.Location = new Point(55, 62);
      this.label10.Name = "label10";
      this.label10.Size = new Size(41, 13);
      this.label10.TabIndex = 17;
      this.label10.Text = "Name :";
      this.label11.AutoSize = true;
      this.label11.Location = new Point(60, 37);
      this.label11.Name = "label11";
      this.label11.Size = new Size(27, 13);
      this.label11.TabIndex = 16;
      this.label11.Text = "ID : ";
      this.textBox4.Location = new Point(369, 397);
      this.textBox4.Name = "textBox4";
      this.textBox4.Size = new Size(25, 20);
      this.textBox4.TabIndex = 105;
      this.textBox4.Visible = false;
      this.textBox16.Enabled = false;
      this.textBox16.Location = new Point(607, 29);
      this.textBox16.Name = "textBox16";
      this.textBox16.Size = new Size(64, 20);
      this.textBox16.TabIndex = 51;
      this.textBox16.Visible = false;
      this.comboBox1.BackColor = Color.GreenYellow;
      this.comboBox1.FlatStyle = FlatStyle.Flat;
      this.comboBox1.FormattingEnabled = true;
      this.comboBox1.Items.AddRange(new object[3]
      {
        (object) "0 - LEFT",
        (object) "1 - CENTER",
        (object) "2 - RIGHT"
      });
      this.comboBox1.Location = new Point(478, 28);
      this.comboBox1.Name = "comboBox1";
      this.comboBox1.Size = new Size(112, 21);
      this.comboBox1.TabIndex = 50;
      this.comboBox1.SelectedIndexChanged += new EventHandler(this.comboBox1_SelectedIndexChanged);
      this.label6.AutoSize = true;
      this.label6.Location = new Point(379, 31);
      this.label6.Name = "label6";
      this.label6.Size = new Size(94, 13);
      this.label6.TabIndex = 49;
      this.label6.Text = "COURSE ORDER";
      this.textBox7.Enabled = false;
      this.textBox7.Location = new Point(409, 397);
      this.textBox7.Name = "textBox7";
      this.textBox7.Size = new Size(64, 20);
      this.textBox7.TabIndex = 106;
      this.textBox7.Visible = false;
      this.textBox8.Enabled = false;
      this.textBox8.Location = new Point(18, 417);
      this.textBox8.Name = "textBox8";
      this.textBox8.Size = new Size(49, 20);
      this.textBox8.TabIndex = 107;
      this.textBox8.Visible = false;
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(903, 455);
      this.Controls.Add((Control) this.textBox8);
      this.Controls.Add((Control) this.textBox7);
      this.Controls.Add((Control) this.textBox4);
      this.Controls.Add((Control) this.textBox16);
      this.Controls.Add((Control) this.comboBox1);
      this.Controls.Add((Control) this.label6);
      this.Controls.Add((Control) this.groupBox4);
      this.Controls.Add((Control) this.groupBox3);
      this.Controls.Add((Control) this.groupBox2);
      this.Controls.Add((Control) this.groupBox1);
      this.FormBorderStyle = FormBorderStyle.Fixed3D;
      this.MaximizeBox = false;
      this.Name = nameof (LcBallEditor);
      this.Text = "LastChaos LcBall Editor";
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      ((ISupportInitialize) this.pictureBox1).EndInit();
      this.groupBox2.ResumeLayout(false);
      ((ISupportInitialize) this.dgItems).EndInit();
      this.groupBox3.ResumeLayout(false);
      ((ISupportInitialize) this.dgItems1).EndInit();
      this.groupBox4.ResumeLayout(false);
      this.groupBox4.PerformLayout();
      ((ISupportInitialize) this.pictureBox2).EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();
    }

    private void button5_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.tb_item_id.Text = itemPicker.ItemIndex.ToString();
    }

    private void tb_item_id_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox2.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.tb_item_id.Text.Trim()));
      this.tb_item_name.Text = this.databaseHandle.ItemNameFast(int.Parse(this.tb_item_id.Text.Trim()));
    }

    private void button3_Click_1(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox5.Text = itemPicker.ItemIndex.ToString();
    }

    private void button18_Click(object sender, EventArgs e)
    {
      if (this.textBox5.Text.Trim().Length <= 0)
      {
        int num1 = (int) MessageBox.Show("please add Token id", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.DB_Database, "UPDATE t_lcball SET a_tocken_index  = '" + this.textBox5.Text + "' WHERE a_item_order = '" + this.textBox6.Text + "'");
        int num2 = (int) MessageBox.Show("Update", "Completed", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
        this.LoadDG1();
        this.textBox7.Text = "";
        this.LoadDG();
        this.LoadStartUp();
      }
    }
  }
}
