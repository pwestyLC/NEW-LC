// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.DailyLogin.DailyLogin
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
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.DailyLogin
{
  public class DailyLogin : Form
  {
    public static Connection connection = new Connection();
    public static List<tbl_dailylogin> dailyloginList = new List<tbl_dailylogin>();
    private string Host = LcDevPack_TeamDamonA.Tools.MemoryWorker.DailyLogin.DailyLogin.connection.Settings.SqlHost;
    private string User = LcDevPack_TeamDamonA.Tools.MemoryWorker.DailyLogin.DailyLogin.connection.Settings.SqlUser;
    private string Password = LcDevPack_TeamDamonA.Tools.MemoryWorker.DailyLogin.DailyLogin.connection.Settings.SqlPassword;
    private string Database = LcDevPack_TeamDamonA.Tools.MemoryWorker.DailyLogin.DailyLogin.connection.Settings.SqlDatabase;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    private ExportLodHandle exportLodHandle = new ExportLodHandle();
    private IContainer components = (IContainer) null;
    private MySqlDataAdapter sda;
    private BindingSource bSource;
    private DataTable dbdataset;
    private MenuStrip menuStrip1;
    private ToolStripMenuItem menüToolStripMenuItem;
    private ToolStripMenuItem aboutToolStripMenuItem;
    private ToolStripMenuItem exitToolStripMenuItem;
    private DataGridView dataGridView1;
    private GroupBox groupBox1;
    private TextBox textBox1;
    private TextBox textBox2;
    private TextBox textBox3;
    private TextBox textBox4;
    private TextBox textBox5;
    private Label label2;
    private TextBox textBox8;
    private Label label3;
    private Label label4;
    private TextBox textBox9;
    private Label label5;
    private TextBox textBox10;
    private Button button3;
    private Label label6;
    private TextBox textBox11;
    private TextBox textBox7;
    private PictureBox pictureBox1;
    private Button button9;
    private Button button11;
    private Label label1;
    private ComboBox comboBox1;

    public DailyLogin()
    {
      this.InitializeComponent();
      this.LoadListBox();
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

    private void LoadListBox()
    {
      this.IniRead();
      this.SelectDB1();
    }

    private void configToolStripMenuItem_Click(object sender, EventArgs e)
    {
    }

    private void IniRead()
    {
      IniFile iniFile = new IniFile(Application.StartupPath + "\\Config\\Settings.cfg");
      this.textBox1.Text = iniFile.IniReadValue("## MYSQL", "SQL_HOST");
      this.textBox2.Text = iniFile.IniReadValue("## MYSQL", "SQL_USER");
      this.textBox3.Text = iniFile.IniReadValue("## MYSQL", "SQL_PASSWORD");
      this.textBox4.Text = iniFile.IniReadValue("## MYSQL", "SQL_DATABASE");
    }

    private void SelectDB()
    {
      MySqlCommand mySqlCommand = new MySqlCommand(" select a_month,a_day,a_item,a_count from " + this.textBox4.Text + ".t_loginrewardnew", new MySqlConnection("datasource=" + this.textBox1.Text + ";port=3306;username=" + this.textBox2.Text + ";password=" + this.textBox3.Text));
      try
      {
        MySqlDataAdapter mySqlDataAdapter = new MySqlDataAdapter();
        mySqlDataAdapter.SelectCommand = mySqlCommand;
        DataTable dataTable = new DataTable();
        mySqlDataAdapter.Fill(dataTable);
        this.dataGridView1.DataSource = (object) new BindingSource()
        {
          DataSource = (object) dataTable
        };
        mySqlDataAdapter.Update(dataTable);
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message, "Neustart");
        this.Close();
      }
    }

    private void SelectDB1()
    {
      MySqlCommand mySqlCommand = new MySqlCommand(" select a_month,a_day,a_item,a_count from " + this.textBox4.Text + ".t_loginrewardnew WHERE a_month=1;", new MySqlConnection("datasource=" + this.textBox1.Text + ";port=3306;username=" + this.textBox2.Text + ";password=" + this.textBox3.Text));
      try
      {
        MySqlDataAdapter mySqlDataAdapter = new MySqlDataAdapter();
        mySqlDataAdapter.SelectCommand = mySqlCommand;
        DataTable dataTable = new DataTable();
        mySqlDataAdapter.Fill(dataTable);
        this.dataGridView1.DataSource = (object) new BindingSource()
        {
          DataSource = (object) dataTable
        };
        mySqlDataAdapter.Update(dataTable);
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message, "Neustart");
        this.Close();
      }
    }

    private void SelectDB2()
    {
      MySqlCommand mySqlCommand = new MySqlCommand(" select a_month,a_day,a_item,a_count from " + this.textBox4.Text + ".t_loginrewardnew WHERE a_month=2;", new MySqlConnection("datasource=" + this.textBox1.Text + ";port=3306;username=" + this.textBox2.Text + ";password=" + this.textBox3.Text));
      try
      {
        MySqlDataAdapter mySqlDataAdapter = new MySqlDataAdapter();
        mySqlDataAdapter.SelectCommand = mySqlCommand;
        DataTable dataTable = new DataTable();
        mySqlDataAdapter.Fill(dataTable);
        this.dataGridView1.DataSource = (object) new BindingSource()
        {
          DataSource = (object) dataTable
        };
        mySqlDataAdapter.Update(dataTable);
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message, "Neustart");
        this.Close();
      }
    }

    private void SelectDB3()
    {
      MySqlCommand mySqlCommand = new MySqlCommand(" select a_month,a_day,a_item,a_count from " + this.textBox4.Text + ".t_loginrewardnew WHERE a_month=3;", new MySqlConnection("datasource=" + this.textBox1.Text + ";port=3306;username=" + this.textBox2.Text + ";password=" + this.textBox3.Text));
      try
      {
        MySqlDataAdapter mySqlDataAdapter = new MySqlDataAdapter();
        mySqlDataAdapter.SelectCommand = mySqlCommand;
        DataTable dataTable = new DataTable();
        mySqlDataAdapter.Fill(dataTable);
        this.dataGridView1.DataSource = (object) new BindingSource()
        {
          DataSource = (object) dataTable
        };
        mySqlDataAdapter.Update(dataTable);
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message, "Neustart");
        this.Close();
      }
    }

    private void SelectDB4()
    {
      MySqlCommand mySqlCommand = new MySqlCommand(" select a_month,a_day,a_item,a_count from " + this.textBox4.Text + ".t_loginrewardnew WHERE a_month=4;", new MySqlConnection("datasource=" + this.textBox1.Text + ";port=3306;username=" + this.textBox2.Text + ";password=" + this.textBox3.Text));
      try
      {
        MySqlDataAdapter mySqlDataAdapter = new MySqlDataAdapter();
        mySqlDataAdapter.SelectCommand = mySqlCommand;
        DataTable dataTable = new DataTable();
        mySqlDataAdapter.Fill(dataTable);
        this.dataGridView1.DataSource = (object) new BindingSource()
        {
          DataSource = (object) dataTable
        };
        mySqlDataAdapter.Update(dataTable);
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message, "Neustart");
        this.Close();
      }
    }

    private void SelectDB5()
    {
      MySqlCommand mySqlCommand = new MySqlCommand(" select a_month,a_day,a_item,a_count from " + this.textBox4.Text + ".t_loginrewardnew WHERE a_month=5;", new MySqlConnection("datasource=" + this.textBox1.Text + ";port=3306;username=" + this.textBox2.Text + ";password=" + this.textBox3.Text));
      try
      {
        MySqlDataAdapter mySqlDataAdapter = new MySqlDataAdapter();
        mySqlDataAdapter.SelectCommand = mySqlCommand;
        DataTable dataTable = new DataTable();
        mySqlDataAdapter.Fill(dataTable);
        this.dataGridView1.DataSource = (object) new BindingSource()
        {
          DataSource = (object) dataTable
        };
        mySqlDataAdapter.Update(dataTable);
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message, "Neustart");
        this.Close();
      }
    }

    private void SelectDB6()
    {
      MySqlCommand mySqlCommand = new MySqlCommand(" select a_month,a_day,a_item,a_count from " + this.textBox4.Text + ".t_loginrewardnew WHERE a_month=6;", new MySqlConnection("datasource=" + this.textBox1.Text + ";port=3306;username=" + this.textBox2.Text + ";password=" + this.textBox3.Text));
      try
      {
        MySqlDataAdapter mySqlDataAdapter = new MySqlDataAdapter();
        mySqlDataAdapter.SelectCommand = mySqlCommand;
        DataTable dataTable = new DataTable();
        mySqlDataAdapter.Fill(dataTable);
        this.dataGridView1.DataSource = (object) new BindingSource()
        {
          DataSource = (object) dataTable
        };
        mySqlDataAdapter.Update(dataTable);
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message, "Neustart");
        this.Close();
      }
    }

    private void SelectDB7()
    {
      MySqlCommand mySqlCommand = new MySqlCommand(" select a_month,a_day,a_item,a_count from " + this.textBox4.Text + ".t_loginrewardnew WHERE a_month=7;", new MySqlConnection("datasource=" + this.textBox1.Text + ";port=3306;username=" + this.textBox2.Text + ";password=" + this.textBox3.Text));
      try
      {
        MySqlDataAdapter mySqlDataAdapter = new MySqlDataAdapter();
        mySqlDataAdapter.SelectCommand = mySqlCommand;
        DataTable dataTable = new DataTable();
        mySqlDataAdapter.Fill(dataTable);
        this.dataGridView1.DataSource = (object) new BindingSource()
        {
          DataSource = (object) dataTable
        };
        mySqlDataAdapter.Update(dataTable);
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message, "Neustart");
        this.Close();
      }
    }

    private void SelectDB8()
    {
      MySqlCommand mySqlCommand = new MySqlCommand(" select a_month,a_day,a_item,a_count from " + this.textBox4.Text + ".t_loginrewardnew WHERE a_month=8;", new MySqlConnection("datasource=" + this.textBox1.Text + ";port=3306;username=" + this.textBox2.Text + ";password=" + this.textBox3.Text));
      try
      {
        MySqlDataAdapter mySqlDataAdapter = new MySqlDataAdapter();
        mySqlDataAdapter.SelectCommand = mySqlCommand;
        DataTable dataTable = new DataTable();
        mySqlDataAdapter.Fill(dataTable);
        this.dataGridView1.DataSource = (object) new BindingSource()
        {
          DataSource = (object) dataTable
        };
        mySqlDataAdapter.Update(dataTable);
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message, "Neustart");
        this.Close();
      }
    }

    private void SelectDB9()
    {
      MySqlCommand mySqlCommand = new MySqlCommand(" select a_month,a_day,a_item,a_count from " + this.textBox4.Text + ".t_loginrewardnew WHERE a_month=9;", new MySqlConnection("datasource=" + this.textBox1.Text + ";port=3306;username=" + this.textBox2.Text + ";password=" + this.textBox3.Text));
      try
      {
        MySqlDataAdapter mySqlDataAdapter = new MySqlDataAdapter();
        mySqlDataAdapter.SelectCommand = mySqlCommand;
        DataTable dataTable = new DataTable();
        mySqlDataAdapter.Fill(dataTable);
        this.dataGridView1.DataSource = (object) new BindingSource()
        {
          DataSource = (object) dataTable
        };
        mySqlDataAdapter.Update(dataTable);
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message, "Neustart");
        this.Close();
      }
    }

    private void SelectDB10()
    {
      MySqlCommand mySqlCommand = new MySqlCommand(" select a_month,a_day,a_item,a_count from " + this.textBox4.Text + ".t_loginrewardnew WHERE a_month=10;", new MySqlConnection("datasource=" + this.textBox1.Text + ";port=3306;username=" + this.textBox2.Text + ";password=" + this.textBox3.Text));
      try
      {
        MySqlDataAdapter mySqlDataAdapter = new MySqlDataAdapter();
        mySqlDataAdapter.SelectCommand = mySqlCommand;
        DataTable dataTable = new DataTable();
        mySqlDataAdapter.Fill(dataTable);
        this.dataGridView1.DataSource = (object) new BindingSource()
        {
          DataSource = (object) dataTable
        };
        mySqlDataAdapter.Update(dataTable);
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message, "Neustart");
        this.Close();
      }
    }

    private void SelectDB11()
    {
      MySqlCommand mySqlCommand = new MySqlCommand(" select a_month,a_day,a_item,a_count from " + this.textBox4.Text + ".t_loginrewardnew WHERE a_month=11;", new MySqlConnection("datasource=" + this.textBox1.Text + ";port=3306;username=" + this.textBox2.Text + ";password=" + this.textBox3.Text));
      try
      {
        MySqlDataAdapter mySqlDataAdapter = new MySqlDataAdapter();
        mySqlDataAdapter.SelectCommand = mySqlCommand;
        DataTable dataTable = new DataTable();
        mySqlDataAdapter.Fill(dataTable);
        this.dataGridView1.DataSource = (object) new BindingSource()
        {
          DataSource = (object) dataTable
        };
        mySqlDataAdapter.Update(dataTable);
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message, "Neustart");
        this.Close();
      }
    }

    private void SelectDB12()
    {
      MySqlCommand mySqlCommand = new MySqlCommand(" select a_month,a_day,a_item,a_count from " + this.textBox4.Text + ".t_loginrewardnew WHERE a_month=12;", new MySqlConnection("datasource=" + this.textBox1.Text + ";port=3306;username=" + this.textBox2.Text + ";password=" + this.textBox3.Text));
      try
      {
        MySqlDataAdapter mySqlDataAdapter = new MySqlDataAdapter();
        mySqlDataAdapter.SelectCommand = mySqlCommand;
        DataTable dataTable = new DataTable();
        mySqlDataAdapter.Fill(dataTable);
        this.dataGridView1.DataSource = (object) new BindingSource()
        {
          DataSource = (object) dataTable
        };
        mySqlDataAdapter.Update(dataTable);
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message, "Neustart");
        this.Close();
      }
    }

    private void loadFromDatabaseToolStripMenuItem_Click(object sender, EventArgs e)
    {
      this.IniRead();
      this.SelectDB();
    }

    private void textBox6_TextChanged(object sender, EventArgs e)
    {
    }

    private void textBox5_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox1.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.textBox5.Text.Trim()));
      this.textBox11.Text = this.databaseHandle.ItemNameFast(int.Parse(this.textBox5.Text.Trim()));
    }

    private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (this.comboBox1.SelectedItem.ToString() == "1.มกราคม-Jan")
      {
        this.IniRead();
        this.SelectDB1();
      }
      if (this.comboBox1.SelectedItem.ToString() == "2.กุมภาพันธ์-Feb")
      {
        this.IniRead();
        this.SelectDB2();
      }
      if (this.comboBox1.SelectedItem.ToString() == "3.มีนาคม-Mar")
      {
        this.IniRead();
        this.SelectDB3();
      }
      if (this.comboBox1.SelectedItem.ToString() == "4.เมษายน-Apr")
      {
        this.IniRead();
        this.SelectDB4();
      }
      if (this.comboBox1.SelectedItem.ToString() == "5.พฤษภาคม-May")
      {
        this.IniRead();
        this.SelectDB5();
      }
      if (this.comboBox1.SelectedItem.ToString() == "6.มิถุนายน-Jun")
      {
        this.IniRead();
        this.SelectDB6();
      }
      if (this.comboBox1.SelectedItem.ToString() == "7.กรกฎาคม-Jul")
      {
        this.IniRead();
        this.SelectDB7();
      }
      if (this.comboBox1.SelectedItem.ToString() == "8.สิงหาคม-Aug")
      {
        this.IniRead();
        this.SelectDB8();
      }
      if (this.comboBox1.SelectedItem.ToString() == "9.กันยายน-Sep")
      {
        this.IniRead();
        this.SelectDB9();
      }
      if (this.comboBox1.SelectedItem.ToString() == "10.ตุลาคม-Oct")
      {
        this.IniRead();
        this.SelectDB10();
      }
      if (this.comboBox1.SelectedItem.ToString() == "11.พฤศจิกายน-Nov")
      {
        this.IniRead();
        this.SelectDB11();
      }
      if (!(this.comboBox1.SelectedItem.ToString() == "12.ธันวาคม-Dec"))
        return;
      this.IniRead();
      this.SelectDB12();
    }

    private void exitToolStripMenuItem_Click(object sender, EventArgs e) => this.Close();

    private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
    {
      int num = (int) MessageBox.Show("LastChaos Daily Login Editor By inwshadow !", "About", MessageBoxButtons.OK, MessageBoxIcon.Asterisk, MessageBoxDefaultButton.Button2);
    }

    private void button9_Click(object sender, EventArgs e)
    {
      this.IniRead();
      MySqlConnection connection = new MySqlConnection("datasource=" + this.textBox1.Text + ";port=3306;username=" + this.textBox2.Text + ";password=" + this.textBox3.Text);
      MySqlCommand mySqlCommand = new MySqlCommand("UPDATE " + this.textBox4.Text + ".t_loginrewardnew SET  a_item='" + this.textBox5.Text + "', a_count='" + this.textBox8.Text + "' WHERE a_day='" + this.textBox9.Text + "' AND a_month='" + this.textBox10.Text + "'", connection);
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
      if (this.comboBox1.SelectedItem.ToString() == "1.มกราคม-Jan")
      {
        this.IniRead();
        this.SelectDB1();
      }
      if (this.comboBox1.SelectedItem.ToString() == "2.กุมภาพันธ์-Feb")
      {
        this.IniRead();
        this.SelectDB2();
      }
      if (this.comboBox1.SelectedItem.ToString() == "3.มีนาคม-Mar")
      {
        this.IniRead();
        this.SelectDB3();
      }
      if (this.comboBox1.SelectedItem.ToString() == "4.เมษายน-Apr")
      {
        this.IniRead();
        this.SelectDB4();
      }
      if (this.comboBox1.SelectedItem.ToString() == "5.พฤษภาคม-May")
      {
        this.IniRead();
        this.SelectDB5();
      }
      if (this.comboBox1.SelectedItem.ToString() == "6.มิถุนายน-Jun")
      {
        this.IniRead();
        this.SelectDB6();
      }
      if (this.comboBox1.SelectedItem.ToString() == "7.กรกฎาคม-Jul")
      {
        this.IniRead();
        this.SelectDB7();
      }
      if (this.comboBox1.SelectedItem.ToString() == "8.สิงหาคม-Aug")
      {
        this.IniRead();
        this.SelectDB8();
      }
      if (this.comboBox1.SelectedItem.ToString() == "9.กันยายน-Sep")
      {
        this.IniRead();
        this.SelectDB9();
      }
      if (this.comboBox1.SelectedItem.ToString() == "10.ตุลาคม-Oct")
      {
        this.IniRead();
        this.SelectDB10();
      }
      if (this.comboBox1.SelectedItem.ToString() == "11.พฤศจิกายน-Nov")
      {
        this.IniRead();
        this.SelectDB11();
      }
      if (!(this.comboBox1.SelectedItem.ToString() == "12.ธันวาคม-Dec"))
        return;
      this.IniRead();
      this.SelectDB12();
    }

    private void dataGridView1_CellClick(object sender, DataGridViewCellEventArgs e)
    {
      if (e.RowIndex < 0)
        return;
      DataGridViewRow row = this.dataGridView1.Rows[e.RowIndex];
      this.textBox5.Text = row.Cells["a_item"].Value.ToString();
      this.textBox8.Text = row.Cells["a_count"].Value.ToString();
      this.textBox9.Text = row.Cells["a_day"].Value.ToString();
      this.textBox10.Text = row.Cells["a_month"].Value.ToString();
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      this.menuStrip1 = new MenuStrip();
      this.menüToolStripMenuItem = new ToolStripMenuItem();
      this.aboutToolStripMenuItem = new ToolStripMenuItem();
      this.exitToolStripMenuItem = new ToolStripMenuItem();
      this.dataGridView1 = new DataGridView();
      this.groupBox1 = new GroupBox();
      this.label1 = new Label();
      this.comboBox1 = new ComboBox();
      this.button11 = new Button();
      this.button9 = new Button();
      this.pictureBox1 = new PictureBox();
      this.label6 = new Label();
      this.textBox11 = new TextBox();
      this.button3 = new Button();
      this.label5 = new Label();
      this.textBox10 = new TextBox();
      this.label4 = new Label();
      this.textBox9 = new TextBox();
      this.textBox8 = new TextBox();
      this.textBox5 = new TextBox();
      this.label3 = new Label();
      this.label2 = new Label();
      this.textBox1 = new TextBox();
      this.textBox2 = new TextBox();
      this.textBox3 = new TextBox();
      this.textBox4 = new TextBox();
      this.textBox7 = new TextBox();
      this.menuStrip1.SuspendLayout();
      ((ISupportInitialize) this.dataGridView1).BeginInit();
      this.groupBox1.SuspendLayout();
      ((ISupportInitialize) this.pictureBox1).BeginInit();
      this.SuspendLayout();
      this.menuStrip1.BackColor = Color.Transparent;
      this.menuStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.menüToolStripMenuItem
      });
      this.menuStrip1.Location = new Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new Size(720, 24);
      this.menuStrip1.TabIndex = 0;
      this.menuStrip1.Text = "menuStrip1";
      this.menüToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[2]
      {
        (ToolStripItem) this.aboutToolStripMenuItem,
        (ToolStripItem) this.exitToolStripMenuItem
      });
      this.menüToolStripMenuItem.Name = "menüToolStripMenuItem";
      this.menüToolStripMenuItem.Size = new Size(50, 20);
      this.menüToolStripMenuItem.Text = "Menü";
      this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
      this.aboutToolStripMenuItem.Size = new Size(107, 22);
      this.aboutToolStripMenuItem.Text = "About";
      this.aboutToolStripMenuItem.Click += new EventHandler(this.aboutToolStripMenuItem_Click);
      this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
      this.exitToolStripMenuItem.Size = new Size(107, 22);
      this.exitToolStripMenuItem.Text = "Exit";
      this.exitToolStripMenuItem.Click += new EventHandler(this.exitToolStripMenuItem_Click);
      this.dataGridView1.AllowUserToAddRows = false;
      this.dataGridView1.AllowUserToDeleteRows = false;
      this.dataGridView1.BackgroundColor = Color.White;
      this.dataGridView1.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dataGridView1.Location = new Point(12, 27);
      this.dataGridView1.Name = "dataGridView1";
      this.dataGridView1.ReadOnly = true;
      this.dataGridView1.RowHeadersVisible = false;
      this.dataGridView1.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
      this.dataGridView1.Size = new Size(417, 711);
      this.dataGridView1.TabIndex = 1;
      this.dataGridView1.CellClick += new DataGridViewCellEventHandler(this.dataGridView1_CellClick);
      this.groupBox1.BackColor = Color.Snow;
      this.groupBox1.Controls.Add((Control) this.label1);
      this.groupBox1.Controls.Add((Control) this.comboBox1);
      this.groupBox1.Controls.Add((Control) this.button11);
      this.groupBox1.Controls.Add((Control) this.button9);
      this.groupBox1.Controls.Add((Control) this.pictureBox1);
      this.groupBox1.Controls.Add((Control) this.label6);
      this.groupBox1.Controls.Add((Control) this.textBox11);
      this.groupBox1.Controls.Add((Control) this.button3);
      this.groupBox1.Controls.Add((Control) this.label5);
      this.groupBox1.Controls.Add((Control) this.textBox10);
      this.groupBox1.Controls.Add((Control) this.label4);
      this.groupBox1.Controls.Add((Control) this.textBox9);
      this.groupBox1.Controls.Add((Control) this.textBox8);
      this.groupBox1.Controls.Add((Control) this.textBox5);
      this.groupBox1.Controls.Add((Control) this.label3);
      this.groupBox1.Controls.Add((Control) this.label2);
      this.groupBox1.Location = new Point(439, 27);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(272, 267);
      this.groupBox1.TabIndex = 2;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Change item data";
      this.label1.AutoSize = true;
      this.label1.Location = new Point(11, 20);
      this.label1.Name = "label1";
      this.label1.Size = new Size(83, 13);
      this.label1.TabIndex = 37;
      this.label1.Text = "Load Database:";
      this.comboBox1.BackColor = Color.GreenYellow;
      this.comboBox1.FlatStyle = FlatStyle.Flat;
      this.comboBox1.FormattingEnabled = true;
      this.comboBox1.Location = new Point(11, 35);
      this.comboBox1.Name = "comboBox1";
      this.comboBox1.Size = new Size(173, 21);
      this.comboBox1.TabIndex = 36;
      this.comboBox1.Text = "Select Month";
      this.comboBox1.SelectedIndexChanged += new EventHandler(this.comboBox1_SelectedIndexChanged);
      this.button11.BackColor = Color.White;
      this.button11.FlatStyle = FlatStyle.Flat;
      this.button11.Image = (Image) Resources.FOLDER05;
      this.button11.ImageAlign = ContentAlignment.MiddleLeft;
      this.button11.Location = new Point(141, 224);
      this.button11.Name = "button11";
      this.button11.Size = new Size(89, 27);
      this.button11.TabIndex = 20;
      this.button11.Text = "  Export";
      this.button11.UseVisualStyleBackColor = false;
      this.button11.Click += new EventHandler(this.button11_Click);
      this.button9.BackColor = Color.LightCyan;
      this.button9.FlatStyle = FlatStyle.Flat;
      this.button9.Image = (Image) Resources._08;
      this.button9.ImageAlign = ContentAlignment.MiddleLeft;
      this.button9.Location = new Point(54, 224);
      this.button9.Name = "button9";
      this.button9.Size = new Size(81, 27);
      this.button9.TabIndex = 19;
      this.button9.Text = "   Save";
      this.button9.UseVisualStyleBackColor = false;
      this.button9.Click += new EventHandler(this.button9_Click);
      this.pictureBox1.Location = new Point(19, 119);
      this.pictureBox1.Name = "pictureBox1";
      this.pictureBox1.Size = new Size(32, 32);
      this.pictureBox1.TabIndex = 17;
      this.pictureBox1.TabStop = false;
      this.label6.AutoSize = true;
      this.label6.Location = new Point(8, 172);
      this.label6.Name = "label6";
      this.label6.Size = new Size(38, 13);
      this.label6.TabIndex = 16;
      this.label6.Text = "Name:";
      this.textBox11.Enabled = false;
      this.textBox11.Location = new Point(54, 167);
      this.textBox11.Multiline = true;
      this.textBox11.Name = "textBox11";
      this.textBox11.Size = new Size(214, 21);
      this.textBox11.TabIndex = 15;
      this.button3.BackgroundImageLayout = ImageLayout.None;
      this.button3.Image = (Image) Resources.search__5_;
      this.button3.Location = new Point(231, 122);
      this.button3.Name = "button3";
      this.button3.Size = new Size(27, 25);
      this.button3.TabIndex = 14;
      this.button3.UseVisualStyleBackColor = true;
      this.button3.Click += new EventHandler(this.button3_Click);
      this.label5.AutoSize = true;
      this.label5.Location = new Point(64, 69);
      this.label5.Name = "label5";
      this.label5.Size = new Size(40, 13);
      this.label5.TabIndex = 13;
      this.label5.Text = "Month:";
      this.textBox10.Enabled = false;
      this.textBox10.Location = new Point(67, 85);
      this.textBox10.Name = "textBox10";
      this.textBox10.Size = new Size(49, 20);
      this.textBox10.TabIndex = 12;
      this.label4.AutoSize = true;
      this.label4.Location = new Point(10, 69);
      this.label4.Name = "label4";
      this.label4.Size = new Size(29, 13);
      this.label4.TabIndex = 11;
      this.label4.Text = "Day:";
      this.textBox9.Enabled = false;
      this.textBox9.Location = new Point(13, 85);
      this.textBox9.Name = "textBox9";
      this.textBox9.Size = new Size(49, 20);
      this.textBox9.TabIndex = 10;
      this.textBox8.Location = new Point(176, 124);
      this.textBox8.Multiline = true;
      this.textBox8.Name = "textBox8";
      this.textBox8.Size = new Size(49, 21);
      this.textBox8.TabIndex = 9;
      this.textBox5.Enabled = false;
      this.textBox5.Location = new Point(71, 124);
      this.textBox5.Multiline = true;
      this.textBox5.Name = "textBox5";
      this.textBox5.Size = new Size(99, 21);
      this.textBox5.TabIndex = 3;
      this.textBox5.TextChanged += new EventHandler(this.textBox5_TextChanged);
      this.label3.AutoSize = true;
      this.label3.Location = new Point(180, 108);
      this.label3.Name = "label3";
      this.label3.Size = new Size(38, 13);
      this.label3.TabIndex = 2;
      this.label3.Text = "Count:";
      this.label2.AutoSize = true;
      this.label2.Location = new Point(68, 108);
      this.label2.Name = "label2";
      this.label2.Size = new Size(44, 13);
      this.label2.TabIndex = 1;
      this.label2.Text = "Item ID:";
      this.textBox1.Location = new Point(611, 326);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(100, 20);
      this.textBox1.TabIndex = 3;
      this.textBox1.Visible = false;
      this.textBox2.Location = new Point(504, 326);
      this.textBox2.Name = "textBox2";
      this.textBox2.Size = new Size(100, 20);
      this.textBox2.TabIndex = 4;
      this.textBox2.Visible = false;
      this.textBox3.Location = new Point(610, 300);
      this.textBox3.Name = "textBox3";
      this.textBox3.Size = new Size(100, 20);
      this.textBox3.TabIndex = 5;
      this.textBox3.Visible = false;
      this.textBox4.Location = new Point(504, 300);
      this.textBox4.Name = "textBox4";
      this.textBox4.Size = new Size(100, 20);
      this.textBox4.TabIndex = 6;
      this.textBox4.Visible = false;
      this.textBox7.Location = new Point(504, 352);
      this.textBox7.Name = "textBox7";
      this.textBox7.Size = new Size(100, 20);
      this.textBox7.TabIndex = 6;
      this.textBox7.Visible = false;
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.BackColor = Color.AliceBlue;
      this.ClientSize = new Size(720, 745);
      this.Controls.Add((Control) this.textBox7);
      this.Controls.Add((Control) this.textBox4);
      this.Controls.Add((Control) this.textBox3);
      this.Controls.Add((Control) this.textBox2);
      this.Controls.Add((Control) this.textBox1);
      this.Controls.Add((Control) this.groupBox1);
      this.Controls.Add((Control) this.dataGridView1);
      this.Controls.Add((Control) this.menuStrip1);
      this.FormBorderStyle = FormBorderStyle.Fixed3D;
      this.MainMenuStrip = this.menuStrip1;
      this.MaximizeBox = false;
      this.Name = nameof (DailyLogin);
      this.Text = "LastChaos DailyLogin Editor";
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      ((ISupportInitialize) this.dataGridView1).EndInit();
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      ((ISupportInitialize) this.pictureBox1).EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();
    }

    private void button3_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox5.Text = itemPicker.ItemIndex.ToString();
    }

    private void button11_Click(object sender, EventArgs e)
    {
      this.exportLodHandle.ExportDailyLogin_V4();
    }

    private void settingToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (new LcDevPack_TeamDamonA.Tools.Settings().ShowDialog() == DialogResult.OK)
        ;
    }
  }
}
