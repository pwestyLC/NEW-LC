// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.RareOptSearch
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA
{
  public class RareOptSearch : Form
  {
    public static Connection connection = new Connection();
    private string Host = RareOptSearch.connection.Settings.SqlHost;
    private string User = RareOptSearch.connection.Settings.SqlUser;
    private string Password = RareOptSearch.connection.Settings.SqlPassword;
    private string Database = RareOptSearch.connection.Settings.SqlDatabase;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    public string rowName = "a_index";
    public string[] menuArray = new string[2]
    {
      "a_index",
      "a_prefix_usa"
    };
    public string[] SearchMenu = new string[2]
    {
      "a_index",
      "a_prefix_usa"
    };
    public List<string> MenuList = new List<string>();
    public List<string> MenuListSearch = new List<string>();
    private IContainer components = (IContainer) null;
    public string name;
    public int index;
    public string varf3;
    private ListBox listBox1;
    private Button button3;
    private Button button2;
    private Button button1;
    private TextBox textBox1;
    private TextBox textBox2;
    private GroupBox groupBox1;
    private Label label1;
    private TextBox textBox3;

    public RareOptSearch() => this.InitializeComponent();

    private void LoadListBox()
    {
      this.MenuList.Clear();
      this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, "select a_index, a_prefix_usa from t_rareoption ORDER BY a_index;");
      for (int index = 0; index < this.listBox1.Items.Count; ++index)
        this.MenuList.Add(this.listBox1.Items[index].ToString());
      this.listBox1.DataSource = (object) this.MenuList;
    }

    public void SearchList(string searchString)
    {
      searchString = searchString.Replace("\\", "\\\\").Replace("'", "\\'");
      string lower = searchString.ToLower();
      string upper = searchString.ToUpper();
      string str = "";
      if (searchString.Length > 1)
        str = char.ToUpper(searchString[0]).ToString() + searchString.Substring(1);
      this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, "select a_index, a_prefix_usa from t_rareoption WHERE a_prefix_usa LIKE '%" + searchString + "%' OR a_index LIKE '%" + searchString + "%' OR a_prefix_usa LIKE '%" + lower + "%' OR a_index  LIKE '%" + lower + "%' OR a_prefix_usa LIKE '%" + upper + "%' OR a_index LIKE '%" + upper + "%' OR a_prefix_usa LIKE '%" + str + "%' OR a_index LIKE '%" + str + "%' ORDER BY a_index;");
    }

    public int GetIndex()
    {
      try
      {
        return Convert.ToInt32(this.listBox1.Text.Split(' ')[0]);
      }
      catch
      {
        return 0;
      }
    }

    private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (this.listBox1.SelectedIndex != -1)
        this.textBox1.Text = this.GetIndex().ToString();
      string Query = " select a_index , a_prefix_usa from t_rareoption WHERE a_index ='" + this.textBox1.Text + "';";
      string[] rows = new string[2]
      {
        "a_index",
        "a_prefix_usa"
      };
      Query.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'");
      this.textBox1.Text = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query, rows)[0];
    }

    private void Form4_Load(object sender, EventArgs e) => this.LoadListBox();

    private void button1_Click(object sender, EventArgs e) => this.varf3 = this.textBox1.Text;

    private void button2_Click(object sender, EventArgs e) => this.varf3 = this.textBox2.Text;

    private void button3_Click(object sender, EventArgs e) => this.Close();

    public bool SearchString(string s) => s.ToUpper().Contains(this.textBox3.Text.ToUpper());

    private void textBox3_TextChanged(object sender, EventArgs e)
    {
      this.MenuListSearch = this.MenuList.FindAll(new Predicate<string>(this.SearchString));
      this.listBox1.DataSource = (object) this.MenuListSearch;
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      this.listBox1 = new ListBox();
      this.button3 = new Button();
      this.button2 = new Button();
      this.button1 = new Button();
      this.textBox1 = new TextBox();
      this.textBox2 = new TextBox();
      this.groupBox1 = new GroupBox();
      this.textBox3 = new TextBox();
      this.label1 = new Label();
      this.groupBox1.SuspendLayout();
      this.SuspendLayout();
      this.listBox1.FormattingEnabled = true;
      this.listBox1.Location = new Point(8, 70);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new Size(199, 407);
      this.listBox1.TabIndex = 0;
      this.listBox1.SelectedIndexChanged += new EventHandler(this.listBox1_SelectedIndexChanged);
      this.button3.Location = new Point(157, 488);
      this.button3.Name = "button3";
      this.button3.Size = new Size(52, 23);
      this.button3.TabIndex = 7;
      this.button3.Text = "Close";
      this.button3.UseVisualStyleBackColor = true;
      this.button3.Click += new EventHandler(this.button3_Click);
      this.button2.DialogResult = DialogResult.OK;
      this.button2.Location = new Point(85, 488);
      this.button2.Name = "button2";
      this.button2.Size = new Size(52, 23);
      this.button2.TabIndex = 6;
      this.button2.Text = "No Opt";
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.button1.DialogResult = DialogResult.OK;
      this.button1.Location = new Point(15, 488);
      this.button1.Name = "button1";
      this.button1.Size = new Size(52, 23);
      this.button1.TabIndex = 5;
      this.button1.Text = "Pick";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.textBox1.Location = new Point(217, 100);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(100, 20);
      this.textBox1.TabIndex = 8;
      this.textBox2.Location = new Point(217, 126);
      this.textBox2.Name = "textBox2";
      this.textBox2.Size = new Size(100, 20);
      this.textBox2.TabIndex = 9;
      this.textBox2.Text = "-1";
      this.groupBox1.Controls.Add((Control) this.label1);
      this.groupBox1.Controls.Add((Control) this.textBox3);
      this.groupBox1.Location = new Point(8, 12);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(195, 50);
      this.groupBox1.TabIndex = 10;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Search";
      this.textBox3.BorderStyle = BorderStyle.FixedSingle;
      this.textBox3.Location = new Point(43, 19);
      this.textBox3.Name = "textBox3";
      this.textBox3.Size = new Size(146, 20);
      this.textBox3.TabIndex = 0;
      this.textBox3.TextChanged += new EventHandler(this.textBox3_TextChanged);
      this.label1.AutoSize = true;
      this.label1.Location = new Point(6, 24);
      this.label1.Name = "label1";
      this.label1.Size = new Size(31, 13);
      this.label1.TabIndex = 1;
      this.label1.Text = "Text:";
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(215, 522);
      this.Controls.Add((Control) this.groupBox1);
      this.Controls.Add((Control) this.textBox2);
      this.Controls.Add((Control) this.textBox1);
      this.Controls.Add((Control) this.button3);
      this.Controls.Add((Control) this.button2);
      this.Controls.Add((Control) this.button1);
      this.Controls.Add((Control) this.listBox1);
      this.FormBorderStyle = FormBorderStyle.FixedToolWindow;
      this.MaximizeBox = false;
      this.MinimizeBox = false;
      this.Name = nameof (RareOptSearch);
      this.Text = "Rare Option";
      this.Load += new EventHandler(this.Form4_Load);
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
