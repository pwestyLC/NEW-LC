// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.Reward
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using MySqlConnector;
using System;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools
{
  public class Reward : Form
  {
    public static Connection connection = new Connection();
    private string Host = Reward.connection.Settings.SqlHost;
    private string User = Reward.connection.Settings.SqlUser;
    private string Password = Reward.connection.Settings.SqlPassword;
    private string Database = Reward.connection.Settings.SqlDatabase;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    public string _ClientPath = Reward.connection.Settings.ClientPath;
    public string rowName = "a_primarykey";
    private MySqlCommand command;
    private MySqlDataAdapter adapter;
    private DataTable table = new DataTable();
    private DataTable table2 = new DataTable();
    private BindingManagerBase managerBase;
    private BindingManagerBase managerBase2;
    private MySqlCommandBuilder builder;
    private IContainer components = (IContainer) null;
    private MenuStrip menuStrip1;
    private ToolStripMenuItem saveToolStripMenuItem;
    private GroupBox groupBox1;
    private DataGridView dataGridView1;
    private TextBox textBox1;
    private TextBox textBox2;
    private TextBox textBox3;
    private TextBox textBox4;
    private TextBox textBox5;
    private TextBox textBox6;
    private TextBox textBox7;
    private TextBox textBox8;
    private TextBox textBox9;
    private TextBox textBox10;
    private TextBox textBox11;
    private Label label1;
    private Label label2;
    private Label label3;
    private Label label4;
    private Label label5;
    private Label label6;
    private Label label7;
    private Label label8;
    private Label label9;
    private Label label10;
    private Label label11;
    private Label label12;
    private Label label13;
    private TextBox textBox12;
    private TextBox textBox13;
    private Label label14;
    private RichTextBox richTextBox1;
    private Button button1;
    private Button button2;
    private Button button3;
    private Button button4;
    private Button button5;
    private Button button6;
    private DataGridView dataGridView2;
    private Button button7;
    private Button button8;
    private Button button9;
    private Button button10;
    private Button button11;
    private Button button12;
    private ToolTip toolTip1;
    private Label label15;
    private Label label16;

    public Reward() => this.InitializeComponent();

    private void Reward_Load(object sender, EventArgs e)
    {
      using (MySqlConnection connection = new MySqlConnection("datasource = " + this.Host + "; port = 3306; username = " + this.User + "; password = " + this.Password + "; database = " + this.Database))
      {
        this.command = new MySqlCommand("SELECT * FROM t_reward_data", connection);
        this.adapter = new MySqlDataAdapter(this.command);
        this.adapter.Fill(this.table);
        this.dataGridView1.DataSource = (object) this.table;
        this.textBox1.DataBindings.Add("text", (object) this.table, "a_primarykey");
        this.textBox2.DataBindings.Add("text", (object) this.table, "a_reward_idx");
        this.textBox3.DataBindings.Add("text", (object) this.table, "a_type");
        this.textBox4.DataBindings.Add("text", (object) this.table, "a_idx");
        this.textBox5.DataBindings.Add("text", (object) this.table, "a_value_1");
        this.textBox6.DataBindings.Add("text", (object) this.table, "a_value_2");
        this.textBox7.DataBindings.Add("text", (object) this.table, "a_value_3");
        this.textBox8.DataBindings.Add("text", (object) this.table, "a_job_flag");
        this.textBox9.DataBindings.Add("text", (object) this.table, "a_level_mini");
        this.textBox10.DataBindings.Add("text", (object) this.table, "a_level_maxi");
        this.textBox11.DataBindings.Add("text", (object) this.table, "a_prob");
        this.command = new MySqlCommand("SELECT * FROM t_reward_head", connection);
        this.adapter = new MySqlDataAdapter(this.command);
        this.adapter.Fill(this.table2);
        this.dataGridView2.DataSource = (object) this.table2;
        this.textBox13.DataBindings.Add("text", (object) this.table2, "a_reward_idx");
        this.richTextBox1.DataBindings.Add("text", (object) this.table2, "a_desc");
        this.textBox12.DataBindings.Add("text", (object) this.table2, "a_rand_type");
      }
      this.managerBase = this.BindingContext[(object) this.table];
      this.managerBase2 = this.BindingContext[(object) this.table2];
    }

    private void button1_Click(object sender, EventArgs e) => this.managerBase.Position = 0;

    private void button2_Click(object sender, EventArgs e)
    {
      this.managerBase.Position = this.managerBase.Count;
    }

    private void button3_Click(object sender, EventArgs e) => this.managerBase.AddNew();

    private void button4_Click(object sender, EventArgs e)
    {
      this.managerBase.EndCurrentEdit();
      this.builder = new MySqlCommandBuilder(this.adapter);
      this.adapter.Update(this.table);
      int num = (int) MessageBox.Show("New Collum Added", "New Reward", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
    }

    private void button5_Click(object sender, EventArgs e)
    {
      this.managerBase.EndCurrentEdit();
      this.builder = new MySqlCommandBuilder(this.adapter);
      this.adapter.Update(this.table);
      int num = (int) MessageBox.Show("Reward Data Updated", "Edit Reward", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
    }

    private void button6_Click(object sender, EventArgs e)
    {
      this.managerBase.RemoveAt(this.managerBase.Position);
      this.builder = new MySqlCommandBuilder(this.adapter);
      this.adapter.Update(this.table);
      int num = (int) MessageBox.Show("Reward Deleted", "Removed Reward", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
    }

    private void button7_Click(object sender, EventArgs e) => this.managerBase2.Position = 0;

    private void button8_Click(object sender, EventArgs e)
    {
      this.managerBase2.Position = this.managerBase2.Count;
    }

    private void button9_Click(object sender, EventArgs e) => this.managerBase2.AddNew();

    private void button10_Click(object sender, EventArgs e)
    {
      this.managerBase2.EndCurrentEdit();
      this.builder = new MySqlCommandBuilder(this.adapter);
      this.adapter.Update(this.table2);
      int num = (int) MessageBox.Show("New Collum Added", "New Head", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
    }

    private void button11_Click(object sender, EventArgs e)
    {
      this.managerBase2.EndCurrentEdit();
      this.builder = new MySqlCommandBuilder(this.adapter);
      this.adapter.Update(this.table2);
      int num = (int) MessageBox.Show("Reward Head Updated", "Edit Head", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
    }

    private void button12_Click(object sender, EventArgs e)
    {
      this.managerBase2.RemoveAt(this.managerBase2.Position);
      this.builder = new MySqlCommandBuilder(this.adapter);
      this.adapter.Update(this.table2);
      int num = (int) MessageBox.Show("Reward Head Deleted", "Removed Head", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
    }

    private void textBox5_MouseHover(object sender, EventArgs e)
    {
      if (this.textBox3.Text == "0")
        this.toolTip1.SetToolTip((Control) this.textBox5, "Item Plus");
      else if (this.textBox3.Text == "4")
      {
        this.toolTip1.SetToolTip((Control) this.textBox5, "Statpoint amount");
      }
      else
      {
        if (!(this.textBox3.Text == "5"))
          return;
        this.toolTip1.SetToolTip((Control) this.textBox5, "Skill Level");
      }
    }

    private void textBox6_MouseHover(object sender, EventArgs e)
    {
      if (!(this.textBox3.Text == "0"))
        return;
      this.toolTip1.SetToolTip((Control) this.textBox6, "Item Flag (used for minerals mostly)");
    }

    private void textBox3_MouseHover(object sender, EventArgs e)
    {
      if (this.textBox3.Text == "0")
        this.toolTip1.SetToolTip((Control) this.textBox3, "Item Rewards");
      else if (this.textBox3.Text == "1")
        this.toolTip1.SetToolTip((Control) this.textBox3, "Gold Reward");
      else if (this.textBox3.Text == "2")
        this.toolTip1.SetToolTip((Control) this.textBox3, "Exp Reward");
      else if (this.textBox3.Text == "3")
        this.toolTip1.SetToolTip((Control) this.textBox3, "SP Reward");
      else if (this.textBox3.Text == "4")
      {
        this.toolTip1.SetToolTip((Control) this.textBox3, "Statpoint Reward");
      }
      else
      {
        if (!(this.textBox3.Text == "5"))
          return;
        this.toolTip1.SetToolTip((Control) this.textBox3, "Skill Reward");
      }
    }

    private void textBox8_MouseHover(object sender, EventArgs e)
    {
      this.toolTip1.SetToolTip((Control) this.textBox8, "Character flag");
    }

    private void textBox11_MouseHover(object sender, EventArgs e)
    {
      if (this.textBox12.Text == "1")
        this.toolTip1.SetToolTip((Control) this.textBox12, "Probability Must Total 10,000");
      else if (this.textBox12.Text == "0")
      {
        this.toolTip1.SetToolTip((Control) this.textBox12, "Probability Must be 10,000");
      }
      else
      {
        if (!(this.textBox12.Text == "2"))
          return;
        this.toolTip1.SetToolTip((Control) this.textBox12, "Probability Must be 10,000");
      }
    }

    private void textBox7_MouseHover(object sender, EventArgs e)
    {
      if (this.textBox3.Text == "0")
        this.toolTip1.SetToolTip((Control) this.textBox7, "Item Count");
      else if (this.textBox3.Text == "1")
        this.toolTip1.SetToolTip((Control) this.textBox7, "Gold Amount");
      else if (this.textBox3.Text == "2")
      {
        this.toolTip1.SetToolTip((Control) this.textBox7, "Exp Amount");
      }
      else
      {
        if (!(this.textBox3.Text == "3"))
          return;
        this.toolTip1.SetToolTip((Control) this.textBox7, "SP Amount");
      }
    }

    private void textBox12_MouseHover(object sender, EventArgs e)
    {
      if (this.textBox12.Text == "0")
        this.toolTip1.SetToolTip((Control) this.textBox12, "Give all Items by Job");
      else if (this.textBox12.Text == "1")
      {
        this.toolTip1.SetToolTip((Control) this.textBox12, "Give one item by probability");
      }
      else
      {
        if (!(this.textBox12.Text == "2"))
          return;
        this.toolTip1.SetToolTip((Control) this.textBox12, "Give one item by random");
      }
    }

    private void textBox4_MouseHover(object sender, EventArgs e)
    {
      if (!(this.textBox3.Text == "5"))
        return;
      this.toolTip1.SetToolTip((Control) this.textBox4, "Skill ID");
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      this.components = (IContainer) new System.ComponentModel.Container();
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (Reward));
      this.menuStrip1 = new MenuStrip();
      this.saveToolStripMenuItem = new ToolStripMenuItem();
      this.groupBox1 = new GroupBox();
      this.dataGridView1 = new DataGridView();
      this.textBox1 = new TextBox();
      this.textBox2 = new TextBox();
      this.textBox3 = new TextBox();
      this.textBox4 = new TextBox();
      this.textBox5 = new TextBox();
      this.textBox6 = new TextBox();
      this.textBox7 = new TextBox();
      this.textBox8 = new TextBox();
      this.textBox9 = new TextBox();
      this.textBox10 = new TextBox();
      this.textBox11 = new TextBox();
      this.label1 = new Label();
      this.label2 = new Label();
      this.label3 = new Label();
      this.label4 = new Label();
      this.label5 = new Label();
      this.label6 = new Label();
      this.label7 = new Label();
      this.label8 = new Label();
      this.label9 = new Label();
      this.label10 = new Label();
      this.label11 = new Label();
      this.label12 = new Label();
      this.label13 = new Label();
      this.textBox12 = new TextBox();
      this.textBox13 = new TextBox();
      this.label14 = new Label();
      this.richTextBox1 = new RichTextBox();
      this.button1 = new Button();
      this.button2 = new Button();
      this.button3 = new Button();
      this.button4 = new Button();
      this.button5 = new Button();
      this.button6 = new Button();
      this.dataGridView2 = new DataGridView();
      this.button7 = new Button();
      this.button8 = new Button();
      this.button9 = new Button();
      this.button10 = new Button();
      this.button11 = new Button();
      this.button12 = new Button();
      this.toolTip1 = new ToolTip(this.components);
      this.label15 = new Label();
      this.label16 = new Label();
      this.menuStrip1.SuspendLayout();
      this.groupBox1.SuspendLayout();
      ((ISupportInitialize) this.dataGridView1).BeginInit();
      ((ISupportInitialize) this.dataGridView2).BeginInit();
      this.SuspendLayout();
      this.menuStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.saveToolStripMenuItem
      });
      this.menuStrip1.Location = new Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new Size(1064, 24);
      this.menuStrip1.TabIndex = 1;
      this.menuStrip1.Text = "menuStrip1";
      this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
      this.saveToolStripMenuItem.Size = new Size(43, 20);
      this.saveToolStripMenuItem.Text = "Save";
      this.groupBox1.Controls.Add((Control) this.dataGridView1);
      this.groupBox1.Location = new Point(12, 27);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(848, 296);
      this.groupBox1.TabIndex = 25;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Reward Data";
      this.dataGridView1.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dataGridView1.Location = new Point(6, 13);
      this.dataGridView1.Name = "dataGridView1";
      this.dataGridView1.Size = new Size(830, 271);
      this.dataGridView1.TabIndex = 0;
      this.textBox1.Location = new Point(950, 35);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(100, 20);
      this.textBox1.TabIndex = 26;
      this.textBox2.Location = new Point(950, 61);
      this.textBox2.Name = "textBox2";
      this.textBox2.Size = new Size(100, 20);
      this.textBox2.TabIndex = 27;
      this.textBox3.Location = new Point(950, 87);
      this.textBox3.Name = "textBox3";
      this.textBox3.Size = new Size(100, 20);
      this.textBox3.TabIndex = 28;
      this.textBox3.MouseHover += new EventHandler(this.textBox3_MouseHover);
      this.textBox4.Location = new Point(950, 113);
      this.textBox4.Name = "textBox4";
      this.textBox4.Size = new Size(100, 20);
      this.textBox4.TabIndex = 29;
      this.textBox4.MouseHover += new EventHandler(this.textBox4_MouseHover);
      this.textBox5.Location = new Point(950, 139);
      this.textBox5.Name = "textBox5";
      this.textBox5.Size = new Size(100, 20);
      this.textBox5.TabIndex = 30;
      this.textBox5.MouseHover += new EventHandler(this.textBox5_MouseHover);
      this.textBox6.Location = new Point(950, 165);
      this.textBox6.Name = "textBox6";
      this.textBox6.Size = new Size(100, 20);
      this.textBox6.TabIndex = 31;
      this.textBox6.MouseHover += new EventHandler(this.textBox6_MouseHover);
      this.textBox7.Location = new Point(950, 191);
      this.textBox7.Name = "textBox7";
      this.textBox7.Size = new Size(100, 20);
      this.textBox7.TabIndex = 32;
      this.textBox7.MouseHover += new EventHandler(this.textBox7_MouseHover);
      this.textBox8.Location = new Point(950, 217);
      this.textBox8.Name = "textBox8";
      this.textBox8.Size = new Size(100, 20);
      this.textBox8.TabIndex = 33;
      this.textBox8.MouseHover += new EventHandler(this.textBox8_MouseHover);
      this.textBox9.Location = new Point(950, 243);
      this.textBox9.Name = "textBox9";
      this.textBox9.Size = new Size(100, 20);
      this.textBox9.TabIndex = 34;
      this.textBox10.Location = new Point(950, 269);
      this.textBox10.Name = "textBox10";
      this.textBox10.Size = new Size(100, 20);
      this.textBox10.TabIndex = 35;
      this.textBox11.Location = new Point(950, 295);
      this.textBox11.Name = "textBox11";
      this.textBox11.Size = new Size(100, 20);
      this.textBox11.TabIndex = 36;
      this.textBox11.MouseHover += new EventHandler(this.textBox11_MouseHover);
      this.label1.AutoSize = true;
      this.label1.Location = new Point(866, 38);
      this.label1.Name = "label1";
      this.label1.Size = new Size(62, 13);
      this.label1.TabIndex = 37;
      this.label1.Text = "Primary Key";
      this.label2.AutoSize = true;
      this.label2.Location = new Point(866, 64);
      this.label2.Name = "label2";
      this.label2.Size = new Size(65, 13);
      this.label2.TabIndex = 38;
      this.label2.Text = "Reward IDX";
      this.label3.AutoSize = true;
      this.label3.Location = new Point(866, 90);
      this.label3.Name = "label3";
      this.label3.Size = new Size(31, 13);
      this.label3.TabIndex = 39;
      this.label3.Text = "Type";
      this.label4.AutoSize = true;
      this.label4.Location = new Point(866, 116);
      this.label4.Name = "label4";
      this.label4.Size = new Size(25, 13);
      this.label4.TabIndex = 40;
      this.label4.Text = "IDX";
      this.label5.AutoSize = true;
      this.label5.Location = new Point(866, 142);
      this.label5.Name = "label5";
      this.label5.Size = new Size(43, 13);
      this.label5.TabIndex = 41;
      this.label5.Text = "Value 1";
      this.label6.AutoSize = true;
      this.label6.Location = new Point(866, 168);
      this.label6.Name = "label6";
      this.label6.Size = new Size(40, 13);
      this.label6.TabIndex = 42;
      this.label6.Text = "Value2";
      this.label7.AutoSize = true;
      this.label7.Location = new Point(866, 194);
      this.label7.Name = "label7";
      this.label7.Size = new Size(40, 13);
      this.label7.TabIndex = 43;
      this.label7.Text = "Value3";
      this.label8.AutoSize = true;
      this.label8.Location = new Point(866, 220);
      this.label8.Name = "label8";
      this.label8.Size = new Size(47, 13);
      this.label8.TabIndex = 44;
      this.label8.Text = "Job Flag";
      this.label9.AutoSize = true;
      this.label9.Location = new Point(866, 246);
      this.label9.Name = "label9";
      this.label9.Size = new Size(53, 13);
      this.label9.TabIndex = 45;
      this.label9.Text = "Level Min";
      this.label10.AutoSize = true;
      this.label10.Location = new Point(866, 272);
      this.label10.Name = "label10";
      this.label10.Size = new Size(56, 13);
      this.label10.TabIndex = 46;
      this.label10.Text = "Level Max";
      this.label11.AutoSize = true;
      this.label11.Location = new Point(866, 298);
      this.label11.Name = "label11";
      this.label11.Size = new Size(61, 13);
      this.label11.TabIndex = 47;
      this.label11.Text = "Proba Rate";
      this.label12.AutoSize = true;
      this.label12.Location = new Point(421, 397);
      this.label12.Name = "label12";
      this.label12.Size = new Size(60, 13);
      this.label12.TabIndex = 51;
      this.label12.Text = "Rand Type";
      this.label13.AutoSize = true;
      this.label13.Location = new Point(421, 371);
      this.label13.Name = "label13";
      this.label13.Size = new Size(65, 13);
      this.label13.TabIndex = 50;
      this.label13.Text = "Reward IDX";
      this.textBox12.Location = new Point(505, 394);
      this.textBox12.Name = "textBox12";
      this.textBox12.Size = new Size(100, 20);
      this.textBox12.TabIndex = 49;
      this.textBox12.MouseHover += new EventHandler(this.textBox12_MouseHover);
      this.textBox13.Location = new Point(505, 368);
      this.textBox13.Name = "textBox13";
      this.textBox13.Size = new Size(100, 20);
      this.textBox13.TabIndex = 48;
      this.label14.AutoSize = true;
      this.label14.Location = new Point(612, 369);
      this.label14.Name = "label14";
      this.label14.Size = new Size(60, 13);
      this.label14.TabIndex = 52;
      this.label14.Text = "Description";
      this.richTextBox1.Location = new Point(678, 371);
      this.richTextBox1.Name = "richTextBox1";
      this.richTextBox1.Size = new Size(371, 121);
      this.richTextBox1.TabIndex = 53;
      this.richTextBox1.Text = "";
      this.button1.Location = new Point(19, 330);
      this.button1.Name = "button1";
      this.button1.Size = new Size(75, 23);
      this.button1.TabIndex = 54;
      this.button1.Text = "Top";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.button2.Location = new Point(100, 330);
      this.button2.Name = "button2";
      this.button2.Size = new Size(75, 23);
      this.button2.TabIndex = 55;
      this.button2.Text = "Bottom";
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.button3.Location = new Point(181, 330);
      this.button3.Name = "button3";
      this.button3.Size = new Size(75, 23);
      this.button3.TabIndex = 56;
      this.button3.Text = "Add";
      this.button3.UseVisualStyleBackColor = true;
      this.button3.Click += new EventHandler(this.button3_Click);
      this.button4.Location = new Point(262, 330);
      this.button4.Name = "button4";
      this.button4.Size = new Size(75, 23);
      this.button4.TabIndex = 57;
      this.button4.Text = "Insert";
      this.button4.UseVisualStyleBackColor = true;
      this.button4.Click += new EventHandler(this.button4_Click);
      this.button5.Location = new Point(343, 330);
      this.button5.Name = "button5";
      this.button5.Size = new Size(75, 23);
      this.button5.TabIndex = 58;
      this.button5.Text = "Update";
      this.button5.UseVisualStyleBackColor = true;
      this.button5.Click += new EventHandler(this.button5_Click);
      this.button6.Location = new Point(424, 330);
      this.button6.Name = "button6";
      this.button6.Size = new Size(75, 23);
      this.button6.TabIndex = 59;
      this.button6.Text = "Delete";
      this.button6.UseVisualStyleBackColor = true;
      this.button6.Click += new EventHandler(this.button6_Click);
      this.dataGridView2.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dataGridView2.Location = new Point(18, 369);
      this.dataGridView2.Name = "dataGridView2";
      this.dataGridView2.Size = new Size(397, 183);
      this.dataGridView2.TabIndex = 60;
      this.button7.Location = new Point(421, 425);
      this.button7.Name = "button7";
      this.button7.Size = new Size(75, 23);
      this.button7.TabIndex = 61;
      this.button7.Text = "Top";
      this.button7.UseVisualStyleBackColor = true;
      this.button7.Click += new EventHandler(this.button7_Click);
      this.button8.Location = new Point(421, 454);
      this.button8.Name = "button8";
      this.button8.Size = new Size(75, 23);
      this.button8.TabIndex = 62;
      this.button8.Text = "Bottom";
      this.button8.UseVisualStyleBackColor = true;
      this.button8.Click += new EventHandler(this.button8_Click);
      this.button9.Location = new Point(421, 483);
      this.button9.Name = "button9";
      this.button9.Size = new Size(75, 23);
      this.button9.TabIndex = 63;
      this.button9.Text = "Add";
      this.button9.UseVisualStyleBackColor = true;
      this.button9.Click += new EventHandler(this.button9_Click);
      this.button10.Location = new Point(421, 512);
      this.button10.Name = "button10";
      this.button10.Size = new Size(75, 23);
      this.button10.TabIndex = 64;
      this.button10.Text = "Insert";
      this.button10.UseVisualStyleBackColor = true;
      this.button10.Click += new EventHandler(this.button10_Click);
      this.button11.Location = new Point(502, 454);
      this.button11.Name = "button11";
      this.button11.Size = new Size(75, 23);
      this.button11.TabIndex = 65;
      this.button11.Text = "Update";
      this.button11.UseVisualStyleBackColor = true;
      this.button11.Click += new EventHandler(this.button11_Click);
      this.button12.Location = new Point(502, 483);
      this.button12.Name = "button12";
      this.button12.Size = new Size(75, 23);
      this.button12.TabIndex = 66;
      this.button12.Text = "Delete";
      this.button12.UseVisualStyleBackColor = true;
      this.button12.Click += new EventHandler(this.button12_Click);
      this.label15.AutoSize = true;
      this.label15.ForeColor = Color.Red;
      this.label15.Location = new Point(20, 353);
      this.label15.Name = "label15";
      this.label15.Size = new Size(274, 13);
      this.label15.TabIndex = 67;
      this.label15.Text = "a_rand_type: 0  = all items 1= random by prob 2= random";
      this.label16.AutoSize = true;
      this.label16.ForeColor = Color.Red;
      this.label16.Location = new Point(569, 326);
      this.label16.Name = "label16";
      this.label16.Size = new Size(486, 13);
      this.label16.TabIndex = 68;
      this.label16.Text = "JobFlags: Titan = 1 Knight = 2 Healer = 4 Mage =264 Rogue =144 Sorcerer = 16 NS = 32: 511 = ALL ";
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(1064, 553);
      this.Controls.Add((Control) this.label16);
      this.Controls.Add((Control) this.label15);
      this.Controls.Add((Control) this.button12);
      this.Controls.Add((Control) this.button11);
      this.Controls.Add((Control) this.button10);
      this.Controls.Add((Control) this.button9);
      this.Controls.Add((Control) this.button8);
      this.Controls.Add((Control) this.button7);
      this.Controls.Add((Control) this.dataGridView2);
      this.Controls.Add((Control) this.button6);
      this.Controls.Add((Control) this.button5);
      this.Controls.Add((Control) this.button4);
      this.Controls.Add((Control) this.button3);
      this.Controls.Add((Control) this.button2);
      this.Controls.Add((Control) this.button1);
      this.Controls.Add((Control) this.richTextBox1);
      this.Controls.Add((Control) this.label14);
      this.Controls.Add((Control) this.label12);
      this.Controls.Add((Control) this.label13);
      this.Controls.Add((Control) this.textBox12);
      this.Controls.Add((Control) this.textBox13);
      this.Controls.Add((Control) this.label11);
      this.Controls.Add((Control) this.label10);
      this.Controls.Add((Control) this.label9);
      this.Controls.Add((Control) this.label8);
      this.Controls.Add((Control) this.label7);
      this.Controls.Add((Control) this.label6);
      this.Controls.Add((Control) this.label5);
      this.Controls.Add((Control) this.label4);
      this.Controls.Add((Control) this.label3);
      this.Controls.Add((Control) this.label2);
      this.Controls.Add((Control) this.label1);
      this.Controls.Add((Control) this.textBox11);
      this.Controls.Add((Control) this.textBox10);
      this.Controls.Add((Control) this.textBox9);
      this.Controls.Add((Control) this.textBox8);
      this.Controls.Add((Control) this.textBox7);
      this.Controls.Add((Control) this.textBox6);
      this.Controls.Add((Control) this.textBox5);
      this.Controls.Add((Control) this.textBox4);
      this.Controls.Add((Control) this.textBox3);
      this.Controls.Add((Control) this.textBox2);
      this.Controls.Add((Control) this.textBox1);
      this.Controls.Add((Control) this.groupBox1);
      this.Controls.Add((Control) this.menuStrip1);
      this.Icon = (Icon) componentResourceManager.GetObject("$this.Icon");
      this.MainMenuStrip = this.menuStrip1;
      this.Name = nameof (Reward);
      this.Text = "Reward Editor";
      this.Load += new EventHandler(this.Reward_Load);
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.groupBox1.ResumeLayout(false);
      ((ISupportInitialize) this.dataGridView1).EndInit();
      ((ISupportInitialize) this.dataGridView2).EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
