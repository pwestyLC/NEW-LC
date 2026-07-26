// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.QuestPicker
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using SlimDX.Direct3D9;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools
{
  public class QuestPicker : Form
  {
    public static Connection connection = new Connection();
    public List<string> MenuList = new List<string>();
    public List<string> MenuListSearch = new List<string>();
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    private string Host = SkillEditor.connection.Settings.SqlHost;
    private string User = SkillEditor.connection.Settings.SqlUser;
    private string Password = SkillEditor.connection.Settings.SqlPassword;
    private string Database = SkillEditor.connection.Settings.SqlDatabase;
    public string _ClientPath = SkillEditor.connection.Settings.ClientPath;
    public string[] menuArray = new string[2]
    {
      "a_index",
      "a_name_usa"
    };
    public float _UpDown = -1f;
    public int QuestIndex = -1;
    private ASCIIEncoding _Enc = new ASCIIEncoding();
    private IContainer components = (IContainer) null;
    public Direct3D _Direct3D;
    public Device _Device;
    public float _Zoom;
    public float _LeftRight;
    public float _Rotation;
    public List<tMesh> _Models;
    private ListBox listBox1;
    private GroupBox groupBox1;
    private TextBox textBox1;
    private GroupBox groupBox2;
    private Button button3;
    private Button button2;
    private Button button1;
    private GroupBox groupBox3;
    private TextBox textBox2;
    private Label label1;
    private GroupBox groupBox4;
    private GroupBox groupBox5;
    private GroupBox groupBox6;
    private TextBox textBox3;
    private TextBox textBox4;
    private TextBox textBox5;
    private Timer timer1;

    public QuestPicker() => this.InitializeComponent();

    private void QuestPicker_Load(object sender, EventArgs e)
    {
      this.MenuList.Clear();
      for (int index = 0; index < QuestListPick.List.Count<tQuest>(); ++index)
        this.MenuList.Add(QuestListPick.List[index].ItemID.ToString() + " - " + QuestListPick.List[index].Name.ToString());
      this.listBox1.DataSource = (object) this.MenuList;
    }

    public bool SearchString(string s) => s.ToUpper().Contains(this.textBox1.Text.ToUpper());

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

    private int GetID()
    {
      int result = -1;
      int.TryParse(this.listBox1.Text.Split(' ')[0], out result);
      return result;
    }

    private void textBox1_TextChanged(object sender, EventArgs e)
    {
      this.MenuListSearch = this.MenuList.FindAll(new Predicate<string>(this.SearchString));
      this.listBox1.DataSource = (object) this.MenuListSearch;
    }

    private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      int QuestIndex = this.GetID();
      if (QuestIndex == -1)
        return;
      tQuest tQuest = QuestListPick.List.Find((Predicate<tQuest>) (p => p.ItemID.Equals(QuestIndex)));
      if (tQuest == null)
        return;
      QuestIndex = tQuest.ItemID;
      this.textBox2.Text = tQuest.Name;
      this.textBox3.Text = tQuest.Desc;
      this.textBox4.Text = tQuest.Desc2;
      this.textBox5.Text = tQuest.Desc3;
    }

    private void button1_Click(object sender, EventArgs e)
    {
      this.DialogResult = DialogResult.OK;
      this.QuestIndex = this.GetID();
    }

    private void button2_Click(object sender, EventArgs e)
    {
      this.QuestIndex = -1;
      this.DialogResult = DialogResult.OK;
    }

    private void button3_Click(object sender, EventArgs e) => this.Close();

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      this.components = (IContainer) new System.ComponentModel.Container();
      this.listBox1 = new ListBox();
      this.groupBox1 = new GroupBox();
      this.textBox1 = new TextBox();
      this.groupBox2 = new GroupBox();
      this.button3 = new Button();
      this.button2 = new Button();
      this.button1 = new Button();
      this.groupBox3 = new GroupBox();
      this.label1 = new Label();
      this.textBox2 = new TextBox();
      this.timer1 = new Timer(this.components);
      this.groupBox4 = new GroupBox();
      this.groupBox5 = new GroupBox();
      this.groupBox6 = new GroupBox();
      this.textBox3 = new TextBox();
      this.textBox4 = new TextBox();
      this.textBox5 = new TextBox();
      this.groupBox1.SuspendLayout();
      this.groupBox2.SuspendLayout();
      this.groupBox3.SuspendLayout();
      this.groupBox4.SuspendLayout();
      this.groupBox5.SuspendLayout();
      this.groupBox6.SuspendLayout();
      this.SuspendLayout();
      this.listBox1.FormattingEnabled = true;
      this.listBox1.Location = new Point(6, 19);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new Size(205, 355);
      this.listBox1.TabIndex = 0;
      this.listBox1.SelectedIndexChanged += new EventHandler(this.listBox1_SelectedIndexChanged);
      this.groupBox1.Controls.Add((Control) this.textBox1);
      this.groupBox1.Location = new Point(11, 34);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(505, 52);
      this.groupBox1.TabIndex = 6;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Search";
      this.textBox1.BorderStyle = BorderStyle.FixedSingle;
      this.textBox1.Location = new Point(6, 19);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(482, 20);
      this.textBox1.TabIndex = 0;
      this.textBox1.TextChanged += new EventHandler(this.textBox1_TextChanged);
      this.groupBox2.Controls.Add((Control) this.button3);
      this.groupBox2.Controls.Add((Control) this.button2);
      this.groupBox2.Controls.Add((Control) this.button1);
      this.groupBox2.Controls.Add((Control) this.listBox1);
      this.groupBox2.Location = new Point(11, 92);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new Size(226, 407);
      this.groupBox2.TabIndex = 7;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "Quest";
      this.button3.FlatStyle = FlatStyle.Flat;
      this.button3.Location = new Point(165, 378);
      this.button3.Name = "button3";
      this.button3.Size = new Size(46, 23);
      this.button3.TabIndex = 3;
      this.button3.Text = "Close";
      this.button3.UseVisualStyleBackColor = true;
      this.button3.Click += new EventHandler(this.button3_Click);
      this.button2.FlatStyle = FlatStyle.Flat;
      this.button2.Location = new Point(104, 378);
      this.button2.Name = "button2";
      this.button2.Size = new Size(55, 23);
      this.button2.TabIndex = 2;
      this.button2.Text = "None";
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.button1.FlatStyle = FlatStyle.Flat;
      this.button1.Location = new Point(6, 378);
      this.button1.Name = "button1";
      this.button1.Size = new Size(92, 23);
      this.button1.TabIndex = 1;
      this.button1.Text = "Pick";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.groupBox3.Controls.Add((Control) this.label1);
      this.groupBox3.Controls.Add((Control) this.textBox2);
      this.groupBox3.Location = new Point(243, 92);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Size = new Size(273, 57);
      this.groupBox3.TabIndex = 8;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "Preview";
      this.label1.AutoSize = true;
      this.label1.Location = new Point(4, 24);
      this.label1.Name = "label1";
      this.label1.Size = new Size(69, 13);
      this.label1.TabIndex = 5;
      this.label1.Text = "Quest Name:";
      this.textBox2.BorderStyle = BorderStyle.FixedSingle;
      this.textBox2.Location = new Point(75, 19);
      this.textBox2.Name = "textBox2";
      this.textBox2.ReadOnly = true;
      this.textBox2.Size = new Size(192, 20);
      this.textBox2.TabIndex = 4;
      this.timer1.Enabled = true;
      this.timer1.Interval = 1;
      this.groupBox4.Controls.Add((Control) this.textBox3);
      this.groupBox4.Location = new Point(243, 155);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Size = new Size(273, 114);
      this.groupBox4.TabIndex = 55;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "Desc";
      this.groupBox5.Controls.Add((Control) this.textBox4);
      this.groupBox5.Location = new Point(243, 275);
      this.groupBox5.Name = "groupBox5";
      this.groupBox5.Size = new Size(273, 114);
      this.groupBox5.TabIndex = 56;
      this.groupBox5.TabStop = false;
      this.groupBox5.Text = "Desc2";
      this.groupBox6.Controls.Add((Control) this.textBox5);
      this.groupBox6.Location = new Point(243, 395);
      this.groupBox6.Name = "groupBox6";
      this.groupBox6.Size = new Size(273, 114);
      this.groupBox6.TabIndex = 57;
      this.groupBox6.TabStop = false;
      this.groupBox6.Text = "Desc3";
      this.textBox3.BorderStyle = BorderStyle.FixedSingle;
      this.textBox3.Location = new Point(6, 19);
      this.textBox3.Multiline = true;
      this.textBox3.Name = "textBox3";
      this.textBox3.ReadOnly = true;
      this.textBox3.Size = new Size(261, 89);
      this.textBox3.TabIndex = 5;
      this.textBox4.BorderStyle = BorderStyle.FixedSingle;
      this.textBox4.Location = new Point(7, 19);
      this.textBox4.Multiline = true;
      this.textBox4.Name = "textBox4";
      this.textBox4.ReadOnly = true;
      this.textBox4.Size = new Size(261, 89);
      this.textBox4.TabIndex = 6;
      this.textBox5.BorderStyle = BorderStyle.FixedSingle;
      this.textBox5.Location = new Point(6, 19);
      this.textBox5.Multiline = true;
      this.textBox5.Name = "textBox5";
      this.textBox5.ReadOnly = true;
      this.textBox5.Size = new Size(261, 89);
      this.textBox5.TabIndex = 6;
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(527, 511);
      this.Controls.Add((Control) this.groupBox6);
      this.Controls.Add((Control) this.groupBox5);
      this.Controls.Add((Control) this.groupBox4);
      this.Controls.Add((Control) this.groupBox1);
      this.Controls.Add((Control) this.groupBox2);
      this.Controls.Add((Control) this.groupBox3);
      this.Name = nameof (QuestPicker);
      this.Text = nameof (QuestPicker);
      this.Load += new EventHandler(this.QuestPicker_Load);
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.groupBox2.ResumeLayout(false);
      this.groupBox3.ResumeLayout(false);
      this.groupBox3.PerformLayout();
      this.groupBox4.ResumeLayout(false);
      this.groupBox4.PerformLayout();
      this.groupBox5.ResumeLayout(false);
      this.groupBox5.PerformLayout();
      this.groupBox6.ResumeLayout(false);
      this.groupBox6.PerformLayout();
      this.ResumeLayout(false);
    }
  }
}
