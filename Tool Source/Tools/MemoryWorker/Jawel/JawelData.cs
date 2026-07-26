// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.Jawel.JawelData
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using MySqlConnector;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.Jawel
{
  public class JawelData : Form
  {
    public static Connection connection = new Connection();
    public static List<JawelStruct> JawelList = new List<JawelStruct>();
    private string Host = JawelData.connection.Settings.SqlHost;
    private string User = JawelData.connection.Settings.SqlUser;
    private string Password = JawelData.connection.Settings.SqlPassword;
    private string Database = JawelData.connection.Settings.SqlDatabase;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    private ExportLodHandle exportLodHandle = new ExportLodHandle();
    public string _ClientPath = LcDevPack_TeamDamonA.Tools.MobEditor.connection.Settings.ClientPath;
    private IContainer components = (IContainer) null;
    private MenuStrip menuStrip1;
    private ToolStripMenuItem fileToolStripMenuItem;
    private ToolStripMenuItem saveToLODToolStripMenuItem;
    private GroupBox groupBox3;
    private Button button3;
    private Button button1;
    private ListBox listBox1;
    private StatusStrip statusStrip1;
    private ToolStripStatusLabel toolStripStatusLabel1;
    private Label label17;
    private CheckBox checkBox1;
    private Button button2;
    private TabControl tabControl1;
    private TabPage tabPage1;
    private TabPage tabPage2;
    private Label label1;
    private TextBox tb_normal_compose_neednas;
    private GroupBox groupBox1;
    private TextBox tb_normal_compose_prob;
    private Label label3;
    private GroupBox groupBox2;
    private TextBox tb_chaos_compose_prob;
    private Label label2;
    private TextBox tb_chaos_compose_neednas;
    private Label label4;
    private TextBox tb_a_compose_normalToChaos_prob;
    private Label label5;
    private GroupBox groupBox4;
    private TextBox tb_a_normal_plus3_prob;
    private Label label6;
    private TextBox tb_a_normal_plus2_prob;
    private Label label7;
    private GroupBox groupBox5;
    private TextBox tb_a_chaos_plus3_prob;
    private Label label8;
    private TextBox tb_a_chaos_plus2_prob;
    private Label label9;
    private GroupBox groupBox6;
    private TextBox tb_a_normal_minus3_prob;
    private Label label12;
    private TextBox tb_a_normal_minus2_prob;
    private Label label10;
    private TextBox tb_a_normal_minus1_prob;
    private Label label11;
    private GroupBox groupBox7;
    private TextBox tb_a_chaos_minus3_prob;
    private Label label13;
    private TextBox tb_a_chaos_minus2_prob;
    private Label label14;
    private TextBox tb_a_chaos_minus1_prob;
    private Label label15;
    private TextBox textBox1;
    private Label label16;

    private void LoadListBox()
    {
      MySqlConnection connection = new MySqlConnection("datasource=" + this.Host + ";Port=3306;User ID="  + this.User + ";Password=" + this.Password + ";Database=" + this.Database + ";Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;");
      connection.Open();
      MySqlCommand mySqlCommand = new MySqlCommand("SELECT * FROM t_jewel_data ORDER BY a_index ASC;", connection);
      mySqlCommand.ExecuteNonQuery();
      MySqlDataReader mySqlDataReader = mySqlCommand.ExecuteReader();
      while (mySqlDataReader.Read())
        JawelData.JawelList.Add(new JawelStruct()
        {
          a_index = (int) mySqlDataReader["a_index"],
          a_normal_compose_neednas = (long) mySqlDataReader["a_normal_compose_neednas"],
          a_chaos_compose_neednas = (long) mySqlDataReader["a_chaos_compose_neednas"],
          a_normal_compose_prob = (int) mySqlDataReader["a_normal_compose_prob"],
          a_chaos_compose_prob = (int) mySqlDataReader["a_chaos_compose_prob"],
          a_compose_normalToChaos_prob = (int) mySqlDataReader["a_compose_normalToChaos_prob"],
          a_normal_plus2_prob = (int) mySqlDataReader["a_normal_plus2_prob"],
          a_normal_plus3_prob = (int) mySqlDataReader["a_normal_plus3_prob"],
          a_chaos_plus2_prob = (int) mySqlDataReader["a_chaos_plus2_prob"],
          a_chaos_plus3_prob = (int) mySqlDataReader["a_chaos_plus3_prob"],
          a_normal_minus1_prob = (int) mySqlDataReader["a_normal_minus1_prob"],
          a_normal_minus2_prob = (int) mySqlDataReader["a_normal_minus2_prob"],
          a_normal_minus3_prob = (int) mySqlDataReader["a_normal_minus3_prob"],
          a_chaos_minus1_prob = (int) mySqlDataReader["a_chaos_minus1_prob"],
          a_chaos_minus2_prob = (int) mySqlDataReader["a_chaos_minus2_prob"],
          a_chaos_minus3_prob = (int) mySqlDataReader["a_chaos_minus3_prob"]
        });
      this.listBox1.Items.Clear();
      int num = JawelData.JawelList.Count<JawelStruct>();
      for (int index = 0; index < num; ++index)
        this.listBox1.Items.Add((object) JawelData.JawelList[index].a_index);
      connection.Close();
    }

    public JawelData() => this.InitializeComponent();

    private void JawelData_Load(object sender, EventArgs e)
    {
      this.listBox1.Items.Clear();
      JawelData.JawelList.Clear();
      this.LoadListBox();
    }

    private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (this.listBox1.SelectedIndex == -1)
        return;
      int Item = Convert.ToInt32(this.listBox1.SelectedItem.ToString().Split('-')[0]);
      int index = JawelData.JawelList.FindIndex((Predicate<JawelStruct>) (p => p.a_index.Equals(Item)));
      this.textBox1.Text = Convert.ToString(Item);
      this.tb_normal_compose_neednas.Text = JawelData.JawelList[index].a_normal_compose_neednas.ToString();
      this.tb_normal_compose_prob.Text = JawelData.JawelList[index].a_normal_compose_prob.ToString();
      this.tb_chaos_compose_neednas.Text = JawelData.JawelList[index].a_chaos_compose_neednas.ToString();
      this.tb_chaos_compose_prob.Text = JawelData.JawelList[index].a_chaos_compose_prob.ToString();
      this.tb_a_compose_normalToChaos_prob.Text = JawelData.JawelList[index].a_compose_normalToChaos_prob.ToString();
      this.tb_a_normal_plus2_prob.Text = JawelData.JawelList[index].a_normal_plus2_prob.ToString();
      this.tb_a_normal_plus3_prob.Text = JawelData.JawelList[index].a_normal_plus3_prob.ToString();
      this.tb_a_chaos_plus2_prob.Text = JawelData.JawelList[index].a_chaos_plus2_prob.ToString();
      this.tb_a_chaos_plus3_prob.Text = JawelData.JawelList[index].a_chaos_plus3_prob.ToString();
      this.tb_a_normal_minus1_prob.Text = JawelData.JawelList[index].a_normal_minus1_prob.ToString();
      this.tb_a_normal_minus2_prob.Text = JawelData.JawelList[index].a_normal_minus2_prob.ToString();
      this.tb_a_normal_minus3_prob.Text = JawelData.JawelList[index].a_normal_minus3_prob.ToString();
      this.tb_a_chaos_minus1_prob.Text = JawelData.JawelList[index].a_chaos_minus1_prob.ToString();
      this.tb_a_chaos_minus2_prob.Text = JawelData.JawelList[index].a_chaos_minus2_prob.ToString();
      this.tb_a_chaos_minus3_prob.Text = JawelData.JawelList[index].a_chaos_minus3_prob.ToString();
    }

    private void button1_Click(object sender, EventArgs e)
    {
      if (this.listBox1.Items.Count == 0)
        return;
      int num1 = JawelData.JawelList[JawelData.JawelList.Count - 1].a_index + 1;
      JawelData.JawelList.Add(new JawelStruct()
      {
        a_index = num1
      });
      this.listBox1.Items.Clear();
      int num2 = JawelData.JawelList.Count<JawelStruct>();
      for (int index = 0; index < num2; ++index)
        this.listBox1.Items.Add((object) JawelData.JawelList[index].a_index);
      if (!this.checkBox1.Checked)
        return;
      MySqlConnection connection = new MySqlConnection("datasource=" + this.Host + ";Port=3306;User ID="  + this.User + ";Password=" + this.Password + ";Database=" + this.Database + ";Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;");
      connection.Open();
      new MySqlCommand("INSERT INTO t_jewel_data (a_index)VALUES('" + num1.ToString() + "');", connection).ExecuteNonQuery();
      connection.Close();
    }

    private void checkBox1_CheckedChanged(object sender, EventArgs e)
    {
      if (this.checkBox1.Checked)
      {
        this.checkBox1.Text = "YES";
        this.checkBox1.BackColor = Color.LimeGreen;
      }
      else
      {
        this.checkBox1.Text = "NO";
        this.checkBox1.BackColor = Color.Red;
      }
    }

    private void button3_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Are u sure u want to delete this record?", "Delete Record Confirmation", MessageBoxButtons.YesNo) != DialogResult.Yes || this.listBox1.SelectedIndex == -1)
        return;
      string[] strArray = this.listBox1.SelectedItem.ToString().Split('-');
      if (this.checkBox1.Checked)
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_jewel_data WHERE a_index = '" + this.textBox1.Text + "'");
      int id = int.Parse(strArray[0]);
      int index = JawelData.JawelList.FindIndex((Predicate<JawelStruct>) (p => p.a_index.Equals(id)));
      if (index == -1)
        return;
      JawelData.JawelList.RemoveAt(index);
      this.listBox1.Items.RemoveAt(this.listBox1.SelectedIndex);
    }

    private void button2_Click(object sender, EventArgs e)
    {
      if (this.listBox1.SelectedIndex == -1)
        return;
      int ID = int.Parse(this.listBox1.SelectedItem.ToString().Split('-')[0]);
      int index1 = JawelData.JawelList.FindIndex((Predicate<JawelStruct>) (p => p.a_index.Equals(ID)));
      if (this.checkBox1.Checked)
        this.Update_To_DB_SELECT();
      if (index1 != -1)
      {
        JawelData.JawelList[index1].a_index = Convert.ToInt32(this.textBox1.Text);
        JawelData.JawelList[index1].a_normal_compose_neednas = (long) Convert.ToInt32(this.tb_normal_compose_neednas.Text);
        JawelData.JawelList[index1].a_chaos_compose_neednas = (long) Convert.ToInt32(this.tb_chaos_compose_neednas.Text);
        JawelData.JawelList[index1].a_normal_compose_prob = Convert.ToInt32(this.tb_normal_compose_prob.Text);
        JawelData.JawelList[index1].a_chaos_compose_prob = Convert.ToInt32(this.tb_chaos_compose_prob.Text);
        JawelData.JawelList[index1].a_compose_normalToChaos_prob = Convert.ToInt32(this.tb_a_compose_normalToChaos_prob.Text);
        JawelData.JawelList[index1].a_normal_plus2_prob = Convert.ToInt32(this.tb_a_normal_plus2_prob.Text);
        JawelData.JawelList[index1].a_normal_plus3_prob = Convert.ToInt32(this.tb_a_normal_plus3_prob.Text);
        JawelData.JawelList[index1].a_chaos_plus2_prob = Convert.ToInt32(this.tb_a_chaos_plus2_prob.Text);
        JawelData.JawelList[index1].a_chaos_plus3_prob = Convert.ToInt32(this.tb_a_chaos_plus3_prob.Text);
        JawelData.JawelList[index1].a_normal_minus1_prob = Convert.ToInt32(this.tb_a_normal_minus1_prob.Text);
        JawelData.JawelList[index1].a_normal_minus2_prob = Convert.ToInt32(this.tb_a_normal_minus2_prob.Text);
        JawelData.JawelList[index1].a_normal_minus3_prob = Convert.ToInt32(this.tb_a_normal_minus3_prob.Text);
        JawelData.JawelList[index1].a_chaos_minus1_prob = Convert.ToInt32(this.tb_a_chaos_minus1_prob.Text);
        JawelData.JawelList[index1].a_chaos_minus2_prob = Convert.ToInt32(this.tb_a_chaos_minus2_prob.Text);
        JawelData.JawelList[index1].a_chaos_minus3_prob = Convert.ToInt32(this.tb_a_chaos_minus3_prob.Text);
      }
      this.listBox1.Items.Clear();
      int num = JawelData.JawelList.Count<JawelStruct>();
      for (int index2 = 0; index2 < num; ++index2)
        this.listBox1.Items.Add((object) JawelData.JawelList[index2].a_index);
    }

    private void Update_To_DB_SELECT()
    {
      MySqlConnection connection = new MySqlConnection("datasource=" + this.Host + ";Port=3306;User ID="  + this.User + ";Password=" + this.Password + ";Database=" + this.Database + ";Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;");
      connection.Open();
      new MySqlCommand("UPDATE t_jewel_data SET a_index = '" + this.textBox1.Text + "',a_normal_compose_neednas = '" + this.tb_normal_compose_neednas.Text + "',a_chaos_compose_neednas = '" + this.tb_chaos_compose_neednas.Text + "',a_normal_compose_prob = '" + this.tb_normal_compose_prob.Text + "',a_chaos_compose_prob = '" + this.tb_chaos_compose_prob.Text + "',a_compose_normalToChaos_prob = '" + this.tb_a_compose_normalToChaos_prob.Text + "',a_normal_plus2_prob = '" + this.tb_a_normal_plus2_prob.Text + "',a_normal_plus3_prob = '" + this.tb_a_normal_plus3_prob.Text + "',a_chaos_plus2_prob = '" + this.tb_a_chaos_plus2_prob.Text + "',a_chaos_plus3_prob = '" + this.tb_a_chaos_plus3_prob.Text + "',a_normal_minus1_prob = '" + this.tb_a_normal_minus1_prob.Text + "',a_normal_minus2_prob = '" + this.tb_a_normal_minus2_prob.Text + "',a_normal_minus3_prob = '" + this.tb_a_normal_minus3_prob.Text + "',a_chaos_minus1_prob = '" + this.tb_a_chaos_minus1_prob.Text + "',a_chaos_minus2_prob = '" + this.tb_a_chaos_minus2_prob.Text + "',a_chaos_minus3_prob = '" + this.tb_a_chaos_minus3_prob.Text + "' WHERE a_index = '" + this.textBox1.Text + "';", connection).ExecuteNonQuery();
      connection.Close();
    }

    private void saveToLODToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (this.listBox1.Items.Count == 0)
        return;
      SaveFileDialog saveFileDialog = new SaveFileDialog();
      saveFileDialog.Filter = "JewelCompos*.lod|JewelCompos*.lod|data|*.data|All|*.*";
      saveFileDialog.Title = "Save JewelCompos*.lod";
      saveFileDialog.InitialDirectory = this._ClientPath;
      int num1 = (int) saveFileDialog.ShowDialog();
      if (!(saveFileDialog.FileName != ""))
        return;
      try
      {
        BinaryWriter binaryWriter = new BinaryWriter((Stream) new FileStream(saveFileDialog.FileName, FileMode.Create));
        binaryWriter.Write(JawelData.JawelList.Count);
        for (int index = 0; index <= JawelData.JawelList.Count<JawelStruct>() - 1; ++index)
        {
          binaryWriter.Write(JawelData.JawelList[index].a_index);
          binaryWriter.Write(Convert.ToInt32(JawelData.JawelList[index].a_normal_compose_neednas));
          binaryWriter.Write(Convert.ToInt32(JawelData.JawelList[index].a_chaos_compose_neednas));
          binaryWriter.Write(JawelData.JawelList[index].a_normal_compose_prob);
          binaryWriter.Write(JawelData.JawelList[index].a_chaos_compose_prob);
          binaryWriter.Write(JawelData.JawelList[index].a_compose_normalToChaos_prob);
          binaryWriter.Write(JawelData.JawelList[index].a_normal_plus2_prob);
          binaryWriter.Write(JawelData.JawelList[index].a_normal_plus3_prob);
          binaryWriter.Write(JawelData.JawelList[index].a_chaos_plus2_prob);
          binaryWriter.Write(JawelData.JawelList[index].a_chaos_plus3_prob);
          binaryWriter.Write(JawelData.JawelList[index].a_normal_minus1_prob);
          binaryWriter.Write(JawelData.JawelList[index].a_normal_minus2_prob);
          binaryWriter.Write(JawelData.JawelList[index].a_normal_minus3_prob);
          binaryWriter.Write(JawelData.JawelList[index].a_chaos_minus1_prob);
          binaryWriter.Write(JawelData.JawelList[index].a_chaos_minus2_prob);
          binaryWriter.Write(JawelData.JawelList[index].a_chaos_minus3_prob);
        }
        binaryWriter.Close();
        int num2 = (int) MessageBox.Show("Sucess!");
      }
      catch (Exception ex)
      {
        int num3 = (int) MessageBox.Show(ex.Message, "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
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
      this.fileToolStripMenuItem = new ToolStripMenuItem();
      this.saveToLODToolStripMenuItem = new ToolStripMenuItem();
      this.groupBox3 = new GroupBox();
      this.button3 = new Button();
      this.button1 = new Button();
      this.listBox1 = new ListBox();
      this.statusStrip1 = new StatusStrip();
      this.toolStripStatusLabel1 = new ToolStripStatusLabel();
      this.label17 = new Label();
      this.checkBox1 = new CheckBox();
      this.button2 = new Button();
      this.tabControl1 = new TabControl();
      this.tabPage1 = new TabPage();
      this.groupBox1 = new GroupBox();
      this.tb_normal_compose_prob = new TextBox();
      this.label3 = new Label();
      this.tb_normal_compose_neednas = new TextBox();
      this.label1 = new Label();
      this.tabPage2 = new TabPage();
      this.groupBox2 = new GroupBox();
      this.tb_chaos_compose_prob = new TextBox();
      this.label2 = new Label();
      this.tb_chaos_compose_neednas = new TextBox();
      this.label4 = new Label();
      this.tb_a_compose_normalToChaos_prob = new TextBox();
      this.label5 = new Label();
      this.groupBox4 = new GroupBox();
      this.tb_a_normal_plus3_prob = new TextBox();
      this.label6 = new Label();
      this.tb_a_normal_plus2_prob = new TextBox();
      this.label7 = new Label();
      this.groupBox5 = new GroupBox();
      this.tb_a_chaos_plus3_prob = new TextBox();
      this.label8 = new Label();
      this.tb_a_chaos_plus2_prob = new TextBox();
      this.label9 = new Label();
      this.groupBox6 = new GroupBox();
      this.tb_a_normal_minus2_prob = new TextBox();
      this.label10 = new Label();
      this.tb_a_normal_minus1_prob = new TextBox();
      this.label11 = new Label();
      this.tb_a_normal_minus3_prob = new TextBox();
      this.label12 = new Label();
      this.groupBox7 = new GroupBox();
      this.tb_a_chaos_minus3_prob = new TextBox();
      this.label13 = new Label();
      this.tb_a_chaos_minus2_prob = new TextBox();
      this.label14 = new Label();
      this.tb_a_chaos_minus1_prob = new TextBox();
      this.label15 = new Label();
      this.textBox1 = new TextBox();
      this.label16 = new Label();
      this.menuStrip1.SuspendLayout();
      this.groupBox3.SuspendLayout();
      this.statusStrip1.SuspendLayout();
      this.tabControl1.SuspendLayout();
      this.tabPage1.SuspendLayout();
      this.groupBox1.SuspendLayout();
      this.tabPage2.SuspendLayout();
      this.groupBox2.SuspendLayout();
      this.groupBox4.SuspendLayout();
      this.groupBox5.SuspendLayout();
      this.groupBox6.SuspendLayout();
      this.groupBox7.SuspendLayout();
      this.SuspendLayout();
      this.menuStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.fileToolStripMenuItem
      });
      this.menuStrip1.Location = new Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new Size(392, 24);
      this.menuStrip1.TabIndex = 0;
      this.menuStrip1.Text = "menuStrip1";
      this.fileToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.saveToLODToolStripMenuItem
      });
      this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
      this.fileToolStripMenuItem.Size = new Size(37, 20);
      this.fileToolStripMenuItem.Text = "File";
      this.saveToLODToolStripMenuItem.Name = "saveToLODToolStripMenuItem";
      this.saveToLODToolStripMenuItem.Size = new Size(180, 22);
      this.saveToLODToolStripMenuItem.Text = "Save to LOD";
      this.saveToLODToolStripMenuItem.Click += new EventHandler(this.saveToLODToolStripMenuItem_Click);
      this.groupBox3.Controls.Add((Control) this.button3);
      this.groupBox3.Controls.Add((Control) this.button1);
      this.groupBox3.Controls.Add((Control) this.listBox1);
      this.groupBox3.Location = new Point(12, 27);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Size = new Size(113, 356);
      this.groupBox3.TabIndex = 32;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "ExChange NPC";
      this.button3.FlatStyle = FlatStyle.Flat;
      this.button3.Location = new Point(6, 326);
      this.button3.Name = "button3";
      this.button3.Size = new Size(100, 23);
      this.button3.TabIndex = 4;
      this.button3.Text = "Delete";
      this.button3.UseVisualStyleBackColor = true;
      this.button3.Click += new EventHandler(this.button3_Click);
      this.button1.FlatStyle = FlatStyle.Flat;
      this.button1.Location = new Point(6, 297);
      this.button1.Name = "button1";
      this.button1.Size = new Size(100, 23);
      this.button1.TabIndex = 2;
      this.button1.Text = "Add";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.listBox1.BackColor = SystemColors.Control;
      this.listBox1.FormattingEnabled = true;
      this.listBox1.Location = new Point(6, 14);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new Size(100, 277);
      this.listBox1.TabIndex = 1;
      this.listBox1.SelectedIndexChanged += new EventHandler(this.listBox1_SelectedIndexChanged);
      this.statusStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.toolStripStatusLabel1
      });
      this.statusStrip1.Location = new Point(0, 388);
      this.statusStrip1.Name = "statusStrip1";
      this.statusStrip1.Size = new Size(392, 22);
      this.statusStrip1.TabIndex = 51;
      this.statusStrip1.Text = "statusStrip1";
      this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
      this.toolStripStatusLabel1.Size = new Size(39, 17);
      this.toolStripStatusLabel1.Text = "Ready";
      this.label17.AutoSize = true;
      this.label17.Location = new Point(131, 358);
      this.label17.Name = "label17";
      this.label17.Size = new Size(102, 13);
      this.label17.TabIndex = 63;
      this.label17.Text = "Auto In Database ->";
      this.checkBox1.AutoSize = true;
      this.checkBox1.BackColor = Color.Red;
      this.checkBox1.Location = new Point(239, 357);
      this.checkBox1.Name = "checkBox1";
      this.checkBox1.Size = new Size(42, 17);
      this.checkBox1.TabIndex = 62;
      this.checkBox1.Text = "NO";
      this.checkBox1.UseVisualStyleBackColor = false;
      this.checkBox1.CheckedChanged += new EventHandler(this.checkBox1_CheckedChanged);
      this.button2.FlatStyle = FlatStyle.Flat;
      this.button2.Location = new Point(287, 353);
      this.button2.Name = "button2";
      this.button2.Size = new Size(100, 23);
      this.button2.TabIndex = 61;
      this.button2.Text = "Save";
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.tabControl1.Controls.Add((Control) this.tabPage1);
      this.tabControl1.Controls.Add((Control) this.tabPage2);
      this.tabControl1.Location = new Point(131, 27);
      this.tabControl1.Name = "tabControl1";
      this.tabControl1.SelectedIndex = 0;
      this.tabControl1.Size = new Size(256, 294);
      this.tabControl1.TabIndex = 64;
      this.tabPage1.BackColor = SystemColors.Control;
      this.tabPage1.Controls.Add((Control) this.groupBox6);
      this.tabPage1.Controls.Add((Control) this.groupBox4);
      this.tabPage1.Controls.Add((Control) this.groupBox1);
      this.tabPage1.Location = new Point(4, 22);
      this.tabPage1.Name = "tabPage1";
      this.tabPage1.Padding = new Padding(3);
      this.tabPage1.Size = new Size(248, 268);
      this.tabPage1.TabIndex = 0;
      this.tabPage1.Text = "Jawel Normal";
      this.groupBox1.Controls.Add((Control) this.tb_normal_compose_prob);
      this.groupBox1.Controls.Add((Control) this.label3);
      this.groupBox1.Controls.Add((Control) this.tb_normal_compose_neednas);
      this.groupBox1.Controls.Add((Control) this.label1);
      this.groupBox1.Location = new Point(6, 6);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(227, 75);
      this.groupBox1.TabIndex = 2;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Compose Info";
      this.tb_normal_compose_prob.BackColor = SystemColors.Control;
      this.tb_normal_compose_prob.Location = new Point(79, 45);
      this.tb_normal_compose_prob.Name = "tb_normal_compose_prob";
      this.tb_normal_compose_prob.Size = new Size(130, 20);
      this.tb_normal_compose_prob.TabIndex = 3;
      this.label3.AutoSize = true;
      this.label3.Location = new Point(18, 48);
      this.label3.Name = "label3";
      this.label3.Size = new Size(29, 13);
      this.label3.TabIndex = 2;
      this.label3.Text = "Prob";
      this.tb_normal_compose_neednas.BackColor = SystemColors.Control;
      this.tb_normal_compose_neednas.Location = new Point(79, 19);
      this.tb_normal_compose_neednas.Name = "tb_normal_compose_neednas";
      this.tb_normal_compose_neednas.Size = new Size(130, 20);
      this.tb_normal_compose_neednas.TabIndex = 1;
      this.label1.AutoSize = true;
      this.label1.Location = new Point(18, 22);
      this.label1.Name = "label1";
      this.label1.Size = new Size(55, 13);
      this.label1.TabIndex = 0;
      this.label1.Text = "Need Nas";
      this.tabPage2.BackColor = SystemColors.Control;
      this.tabPage2.Controls.Add((Control) this.groupBox7);
      this.tabPage2.Controls.Add((Control) this.groupBox5);
      this.tabPage2.Controls.Add((Control) this.groupBox2);
      this.tabPage2.Location = new Point(4, 22);
      this.tabPage2.Name = "tabPage2";
      this.tabPage2.Padding = new Padding(3);
      this.tabPage2.Size = new Size(248, 268);
      this.tabPage2.TabIndex = 1;
      this.tabPage2.Text = "Jawel Chaos";
      this.groupBox2.Controls.Add((Control) this.tb_chaos_compose_prob);
      this.groupBox2.Controls.Add((Control) this.label2);
      this.groupBox2.Controls.Add((Control) this.tb_chaos_compose_neednas);
      this.groupBox2.Controls.Add((Control) this.label4);
      this.groupBox2.Location = new Point(6, 6);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new Size(227, 75);
      this.groupBox2.TabIndex = 3;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "Compose Info";
      this.tb_chaos_compose_prob.BackColor = SystemColors.Control;
      this.tb_chaos_compose_prob.Location = new Point(79, 45);
      this.tb_chaos_compose_prob.Name = "tb_chaos_compose_prob";
      this.tb_chaos_compose_prob.Size = new Size(130, 20);
      this.tb_chaos_compose_prob.TabIndex = 3;
      this.label2.AutoSize = true;
      this.label2.Location = new Point(18, 48);
      this.label2.Name = "label2";
      this.label2.Size = new Size(29, 13);
      this.label2.TabIndex = 2;
      this.label2.Text = "Prob";
      this.tb_chaos_compose_neednas.BackColor = SystemColors.Control;
      this.tb_chaos_compose_neednas.Location = new Point(79, 19);
      this.tb_chaos_compose_neednas.Name = "tb_chaos_compose_neednas";
      this.tb_chaos_compose_neednas.Size = new Size(130, 20);
      this.tb_chaos_compose_neednas.TabIndex = 1;
      this.label4.AutoSize = true;
      this.label4.Location = new Point(18, 22);
      this.label4.Name = "label4";
      this.label4.Size = new Size(55, 13);
      this.label4.TabIndex = 0;
      this.label4.Text = "Need Nas";
      this.tb_a_compose_normalToChaos_prob.BackColor = SystemColors.Control;
      this.tb_a_compose_normalToChaos_prob.Location = new Point(310, 327);
      this.tb_a_compose_normalToChaos_prob.Name = "tb_a_compose_normalToChaos_prob";
      this.tb_a_compose_normalToChaos_prob.Size = new Size(77, 20);
      this.tb_a_compose_normalToChaos_prob.TabIndex = 66;
      this.label5.AutoSize = true;
      this.label5.Location = new Point(133, 330);
      this.label5.Name = "label5";
      this.label5.Size = new Size(171, 13);
      this.label5.TabIndex = 65;
      this.label5.Text = "Commpose Normal to Chaos Proub";
      this.groupBox4.Controls.Add((Control) this.tb_a_normal_plus3_prob);
      this.groupBox4.Controls.Add((Control) this.label6);
      this.groupBox4.Controls.Add((Control) this.tb_a_normal_plus2_prob);
      this.groupBox4.Controls.Add((Control) this.label7);
      this.groupBox4.Location = new Point(6, 87);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Size = new Size(227, 75);
      this.groupBox4.TabIndex = 3;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "Jawel Upgrade Proub Succes";
      this.tb_a_normal_plus3_prob.BackColor = SystemColors.Control;
      this.tb_a_normal_plus3_prob.Location = new Point(98, 45);
      this.tb_a_normal_plus3_prob.Name = "tb_a_normal_plus3_prob";
      this.tb_a_normal_plus3_prob.Size = new Size(111, 20);
      this.tb_a_normal_plus3_prob.TabIndex = 3;
      this.label6.AutoSize = true;
      this.label6.Location = new Point(18, 48);
      this.label6.Name = "label6";
      this.label6.Size = new Size(83, 13);
      this.label6.TabIndex = 2;
      this.label6.Text = "Jawel + 3 Proub";
      this.tb_a_normal_plus2_prob.BackColor = SystemColors.Control;
      this.tb_a_normal_plus2_prob.Location = new Point(98, 19);
      this.tb_a_normal_plus2_prob.Name = "tb_a_normal_plus2_prob";
      this.tb_a_normal_plus2_prob.Size = new Size(111, 20);
      this.tb_a_normal_plus2_prob.TabIndex = 1;
      this.label7.AutoSize = true;
      this.label7.Location = new Point(18, 22);
      this.label7.Name = "label7";
      this.label7.Size = new Size(83, 13);
      this.label7.TabIndex = 0;
      this.label7.Text = "Jawel + 2 Proub";
      this.groupBox5.Controls.Add((Control) this.tb_a_chaos_plus3_prob);
      this.groupBox5.Controls.Add((Control) this.label8);
      this.groupBox5.Controls.Add((Control) this.tb_a_chaos_plus2_prob);
      this.groupBox5.Controls.Add((Control) this.label9);
      this.groupBox5.Location = new Point(6, 87);
      this.groupBox5.Name = "groupBox5";
      this.groupBox5.Size = new Size(227, 75);
      this.groupBox5.TabIndex = 4;
      this.groupBox5.TabStop = false;
      this.groupBox5.Text = "Jawel Upgrade Proub Succes";
      this.tb_a_chaos_plus3_prob.BackColor = SystemColors.Control;
      this.tb_a_chaos_plus3_prob.Location = new Point(98, 45);
      this.tb_a_chaos_plus3_prob.Name = "tb_a_chaos_plus3_prob";
      this.tb_a_chaos_plus3_prob.Size = new Size(111, 20);
      this.tb_a_chaos_plus3_prob.TabIndex = 3;
      this.label8.AutoSize = true;
      this.label8.Location = new Point(18, 48);
      this.label8.Name = "label8";
      this.label8.Size = new Size(83, 13);
      this.label8.TabIndex = 2;
      this.label8.Text = "Jawel + 3 Proub";
      this.tb_a_chaos_plus2_prob.BackColor = SystemColors.Control;
      this.tb_a_chaos_plus2_prob.Location = new Point(98, 19);
      this.tb_a_chaos_plus2_prob.Name = "tb_a_chaos_plus2_prob";
      this.tb_a_chaos_plus2_prob.Size = new Size(111, 20);
      this.tb_a_chaos_plus2_prob.TabIndex = 1;
      this.label9.AutoSize = true;
      this.label9.Location = new Point(18, 22);
      this.label9.Name = "label9";
      this.label9.Size = new Size(83, 13);
      this.label9.TabIndex = 0;
      this.label9.Text = "Jawel + 2 Proub";
      this.groupBox6.Controls.Add((Control) this.tb_a_normal_minus3_prob);
      this.groupBox6.Controls.Add((Control) this.label12);
      this.groupBox6.Controls.Add((Control) this.tb_a_normal_minus2_prob);
      this.groupBox6.Controls.Add((Control) this.label10);
      this.groupBox6.Controls.Add((Control) this.tb_a_normal_minus1_prob);
      this.groupBox6.Controls.Add((Control) this.label11);
      this.groupBox6.Location = new Point(6, 168);
      this.groupBox6.Name = "groupBox6";
      this.groupBox6.Size = new Size(227, 94);
      this.groupBox6.TabIndex = 4;
      this.groupBox6.TabStop = false;
      this.groupBox6.Text = "Jawel Upgrade Proub Minus";
      this.tb_a_normal_minus2_prob.BackColor = SystemColors.Control;
      this.tb_a_normal_minus2_prob.Location = new Point(98, 45);
      this.tb_a_normal_minus2_prob.Name = "tb_a_normal_minus2_prob";
      this.tb_a_normal_minus2_prob.Size = new Size(111, 20);
      this.tb_a_normal_minus2_prob.TabIndex = 3;
      this.label10.AutoSize = true;
      this.label10.Location = new Point(18, 48);
      this.label10.Name = "label10";
      this.label10.Size = new Size(80, 13);
      this.label10.TabIndex = 2;
      this.label10.Text = "Jawel - 2 Proub";
      this.tb_a_normal_minus1_prob.BackColor = SystemColors.Control;
      this.tb_a_normal_minus1_prob.Location = new Point(98, 19);
      this.tb_a_normal_minus1_prob.Name = "tb_a_normal_minus1_prob";
      this.tb_a_normal_minus1_prob.Size = new Size(111, 20);
      this.tb_a_normal_minus1_prob.TabIndex = 1;
      this.label11.AutoSize = true;
      this.label11.Location = new Point(18, 22);
      this.label11.Name = "label11";
      this.label11.Size = new Size(80, 13);
      this.label11.TabIndex = 0;
      this.label11.Text = "Jawel - 1 Proub";
      this.tb_a_normal_minus3_prob.BackColor = SystemColors.Control;
      this.tb_a_normal_minus3_prob.Location = new Point(98, 71);
      this.tb_a_normal_minus3_prob.Name = "tb_a_normal_minus3_prob";
      this.tb_a_normal_minus3_prob.Size = new Size(111, 20);
      this.tb_a_normal_minus3_prob.TabIndex = 5;
      this.label12.AutoSize = true;
      this.label12.Location = new Point(18, 74);
      this.label12.Name = "label12";
      this.label12.Size = new Size(80, 13);
      this.label12.TabIndex = 4;
      this.label12.Text = "Jawel - 3 Proub";
      this.groupBox7.Controls.Add((Control) this.tb_a_chaos_minus3_prob);
      this.groupBox7.Controls.Add((Control) this.label13);
      this.groupBox7.Controls.Add((Control) this.tb_a_chaos_minus2_prob);
      this.groupBox7.Controls.Add((Control) this.label14);
      this.groupBox7.Controls.Add((Control) this.tb_a_chaos_minus1_prob);
      this.groupBox7.Controls.Add((Control) this.label15);
      this.groupBox7.Location = new Point(6, 168);
      this.groupBox7.Name = "groupBox7";
      this.groupBox7.Size = new Size(227, 94);
      this.groupBox7.TabIndex = 5;
      this.groupBox7.TabStop = false;
      this.groupBox7.Text = "Jawel Upgrade Proub Minus";
      this.tb_a_chaos_minus3_prob.BackColor = SystemColors.Control;
      this.tb_a_chaos_minus3_prob.Location = new Point(98, 71);
      this.tb_a_chaos_minus3_prob.Name = "tb_a_chaos_minus3_prob";
      this.tb_a_chaos_minus3_prob.Size = new Size(111, 20);
      this.tb_a_chaos_minus3_prob.TabIndex = 5;
      this.label13.AutoSize = true;
      this.label13.Location = new Point(18, 74);
      this.label13.Name = "label13";
      this.label13.Size = new Size(80, 13);
      this.label13.TabIndex = 4;
      this.label13.Text = "Jawel - 3 Proub";
      this.tb_a_chaos_minus2_prob.BackColor = SystemColors.Control;
      this.tb_a_chaos_minus2_prob.Location = new Point(98, 45);
      this.tb_a_chaos_minus2_prob.Name = "tb_a_chaos_minus2_prob";
      this.tb_a_chaos_minus2_prob.Size = new Size(111, 20);
      this.tb_a_chaos_minus2_prob.TabIndex = 3;
      this.label14.AutoSize = true;
      this.label14.Location = new Point(18, 48);
      this.label14.Name = "label14";
      this.label14.Size = new Size(80, 13);
      this.label14.TabIndex = 2;
      this.label14.Text = "Jawel - 2 Proub";
      this.tb_a_chaos_minus1_prob.BackColor = SystemColors.Control;
      this.tb_a_chaos_minus1_prob.Location = new Point(98, 19);
      this.tb_a_chaos_minus1_prob.Name = "tb_a_chaos_minus1_prob";
      this.tb_a_chaos_minus1_prob.Size = new Size(111, 20);
      this.tb_a_chaos_minus1_prob.TabIndex = 1;
      this.label15.AutoSize = true;
      this.label15.Location = new Point(18, 22);
      this.label15.Name = "label15";
      this.label15.Size = new Size(80, 13);
      this.label15.TabIndex = 0;
      this.label15.Text = "Jawel - 1 Proub";
      this.textBox1.BackColor = SystemColors.Control;
      this.textBox1.Location = new Point(330, 0);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(57, 20);
      this.textBox1.TabIndex = 68;
      this.label16.AutoSize = true;
      this.label16.Location = new Point(273, 3);
      this.label16.Name = "label16";
      this.label16.Size = new Size(51, 13);
      this.label16.TabIndex = 67;
      this.label16.Text = "Select ID";
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(392, 410);
      this.Controls.Add((Control) this.textBox1);
      this.Controls.Add((Control) this.label16);
      this.Controls.Add((Control) this.tb_a_compose_normalToChaos_prob);
      this.Controls.Add((Control) this.label5);
      this.Controls.Add((Control) this.tabControl1);
      this.Controls.Add((Control) this.label17);
      this.Controls.Add((Control) this.checkBox1);
      this.Controls.Add((Control) this.button2);
      this.Controls.Add((Control) this.statusStrip1);
      this.Controls.Add((Control) this.groupBox3);
      this.Controls.Add((Control) this.menuStrip1);
      this.FormBorderStyle = FormBorderStyle.FixedToolWindow;
      this.MainMenuStrip = this.menuStrip1;
      this.MaximumSize = new Size(408, 449);
      this.MinimumSize = new Size(408, 449);
      this.Name = nameof (JawelData);
      this.Text = nameof (JawelData);
      this.Load += new EventHandler(this.JawelData_Load);
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.groupBox3.ResumeLayout(false);
      this.statusStrip1.ResumeLayout(false);
      this.statusStrip1.PerformLayout();
      this.tabControl1.ResumeLayout(false);
      this.tabPage1.ResumeLayout(false);
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.tabPage2.ResumeLayout(false);
      this.groupBox2.ResumeLayout(false);
      this.groupBox2.PerformLayout();
      this.groupBox4.ResumeLayout(false);
      this.groupBox4.PerformLayout();
      this.groupBox5.ResumeLayout(false);
      this.groupBox5.PerformLayout();
      this.groupBox6.ResumeLayout(false);
      this.groupBox6.PerformLayout();
      this.groupBox7.ResumeLayout(false);
      this.groupBox7.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
