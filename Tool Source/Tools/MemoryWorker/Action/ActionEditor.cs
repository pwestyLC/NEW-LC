// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.Action.ActionEditor
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using LcDevPack_TeamDamonA.Properties;
using MySqlConnector;
using StringExporter;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.Action
{
  public class ActionEditor : Form
  {
    public static Connection connection = new Connection();
    private string Host = ActionEditor.connection.Settings.SqlHost;
    private string User = ActionEditor.connection.Settings.SqlUser;
    private string Password = ActionEditor.connection.Settings.SqlPassword;
    private string Database = ActionEditor.connection.Settings.SqlDatabase;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    public string _ClientPath = ActionEditor.connection.Settings.ClientPath;
    private ExportLodHandle exportLodHandle = new ExportLodHandle();
    private string language = ActionEditor.connection.Settings.Language;
    private IContainer components = (IContainer) null;
    private MySqlDataAdapter sda;
    private BindingSource bSource;
    private DataTable dbdataset;
    private MenuStrip menuStrip1;
    private ToolStripMenuItem menüToolStripMenuItem;
    private ToolStripMenuItem ExportToolStripMenuItem;
    private ToolStripMenuItem exitToolStripMenuItem;
    private TextBox textBox1;
    private TextBox textBox2;
    private TextBox textBox3;
    private TextBox textBox4;
    private TextBox textBox7;
    private Label label7;
    private GroupBox groupBox4;
    private TextBox tb_name_action;
    private Label label9;
    private TextBox tb_desc;
    private TextBox tb_action_id;
    private Label label10;
    private Label label11;
    private GroupBox groupBox7;
    private Button button6;
    private Button button9;
    private Button button12;
    private Button button8;
    private ListBox listBox1;
    private string namee;
    public string descrr;
    public List<string> MenuList = new List<string>();
    public string[] menuArray = new string[2]
    {
      "a_index",
      "a_name"
    };
    public string[] menuArrayGER = new string[2]
    {
      "a_index",
      "a_name_ger"
    };
    public string[] menuArrayPOL = new string[2]
    {
      "a_index",
      "a_name_pld"
    };
    public string[] menuArrayBRA = new string[2]
    {
      "a_index",
      "a_name_brz"
    };
    public string[] menuArrayRUS = new string[2]
    {
      "a_index",
      "a_name_rus"
    };
    public string[] menuArrayFRA = new string[2]
    {
      "a_index",
      "a_question"
    };
    public string[] menuArrayESP = new string[2]
    {
      "a_index",
      "a_name_frc"
    };
    public string[] menuArrayMEX = new string[2]
    {
      "a_index",
      "a_name_mex"
    };
    public string[] menuArrayTHA = new string[2]
    {
      "a_index",
      "a_name_thai"
    };
    public string[] menuArrayITA = new string[2]
    {
      "a_index",
      "a_name_ita"
    };
    private ComboBox comboBox1;
    private GroupBox groupBox9;
    private LinkLabel linkLabel1;
    private PictureBox pictureBox1;
    private TextBox textBox12;
    private Label label50;
    private TextBox textBox10;
    private Label label48;
    private Label label49;
    private TextBox textBox11;
    private GroupBox groupBox21;
    private CheckBox checkBox1;
    private TextBox textBox15;
    private Label label8;
    private CheckedListBox checkedListBox2;
    private TextBox textBox9;
    private TextBox textBox5;
    private ToolStripMenuItem exportStrActionToolStripMenuItem;
    public string[] menuArrayUSA = new string[2]
    {
      "a_index",
      "a_name_usa"
    };

    public string StringFromLanguage()
    {
      if (this.language == "GER")
      {
        this.namee = "a_name_ger";
        return this.namee;
      }
      if (this.language == "POL")
      {
        this.namee = "a_name_pld";
        return this.namee;
      }
      if (this.language == "BRA")
      {
        this.namee = "a_name_brz";
        return this.namee;
      }
      if (this.language == "RUS")
      {
        this.namee = "a_name_rus";
        return this.namee;
      }
      if (this.language == "FRA")
      {
        this.namee = "a_name_frc";
        return this.namee;
      }
      if (this.language == "ESP")
      {
        this.namee = "a_name_spn";
        return this.namee;
      }
      if (this.language == "MEX")
      {
        this.namee = "a_name_mex";
        return this.namee;
      }
      if (this.language == "THA")
      {
        this.namee = "a_name_thai";
        return this.namee;
      }
      if (this.language == "ITA")
      {
        this.namee = "a_name_ita";
        return this.namee;
      }
      if (!(this.language == "USA"))
        return (string) null;
      this.namee = "a_name_usa";
      return this.namee;
    }

    public string DescrFromLanguage()
    {
      if (this.language == "GER")
      {
        this.descrr = "a_client_description_ger";
        return this.descrr;
      }
      if (this.language == "POL")
      {
        this.descrr = "a_client_description_pld";
        return this.descrr;
      }
      if (this.language == "BRA")
      {
        this.descrr = "a_client_description_brz";
        return this.descrr;
      }
      if (this.language == "RUS")
      {
        this.descrr = "a_client_description_rus";
        return this.descrr;
      }
      if (this.language == "FRA")
      {
        this.descrr = "a_client_description_frc";
        return this.descrr;
      }
      if (this.language == "ESP")
      {
        this.descrr = "a_client_description_spn";
        return this.descrr;
      }
      if (this.language == "MEX")
      {
        this.descrr = "a_client_description_mex";
        return this.descrr;
      }
      if (this.language == "THA")
      {
        this.descrr = "a_client_description_thai";
        return this.descrr;
      }
      if (this.language == "ITA")
      {
        this.descrr = "a_client_description_ita";
        return this.descrr;
      }
      if (!(this.language == "USA"))
        return (string) null;
      this.descrr = "a_client_description_usa";
      return this.descrr;
    }

    public ActionEditor()
    {
      this.InitializeComponent();
      this.LoadListBox();
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

    private void LoadListBox()
    {
      this.listBox1.SelectedIndex = -1;
      this.MenuList.Clear();
      this.namee = this.StringFromLanguage();
      string Query = "SELECT a_index, " + this.namee + " FROM t_action ORDER BY a_index;";
      if (this.language == "GER")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayGER, this.Host, this.User, this.Password, this.Database, Query);
      else if (this.language == "POL")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayPOL, this.Host, this.User, this.Password, this.Database, Query);
      else if (this.language == "BRA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayBRA, this.Host, this.User, this.Password, this.Database, Query);
      else if (this.language == "RUS")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayRUS, this.Host, this.User, this.Password, this.Database, Query);
      else if (this.language == "FRA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayFRA, this.Host, this.User, this.Password, this.Database, Query);
      else if (this.language == "ESP")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayESP, this.Host, this.User, this.Password, this.Database, Query);
      else if (this.language == "MEX")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayMEX, this.Host, this.User, this.Password, this.Database, Query);
      else if (this.language == "THA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayTHA, this.Host, this.User, this.Password, this.Database, Query);
      else if (this.language == "ITA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayITA, this.Host, this.User, this.Password, this.Database, Query);
      else if (this.language == "USA")
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArrayUSA, this.Host, this.User, this.Password, this.Database, Query);
      else
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, Query);
      for (int index = 0; index < this.listBox1.Items.Count; ++index)
        this.MenuList.Add(this.listBox1.Items[index].ToString());
      this.listBox1.DataSource = (object) this.MenuList;
      this.listBox1.SelectedIndex = -1;
    }

        private void ListBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            string Query =
                "SELECT a_index, a_type, a_job, a_iconid, a_iconrow, a_iconcol, a_name, " +
                "a_name_frc, a_name_ita, a_name_usa, a_name_rus, a_name_thai, a_name_pld, a_name_spn, a_name_brz, a_name_ger, " +
                "a_client_description, a_client_description_frc, a_client_description_ita, a_client_description_usa, " +
                "a_client_description_rus, a_client_description_thai, a_client_description_pld, a_client_description_spn, " +
                "a_client_description_brz, a_client_description_ger, a_name_mex, a_client_description_mex " +
                "FROM t_action WHERE a_index = '" + this.listBox1.Text + "';";

            string[] rows = new string[28]
            {
        "a_index",
        "a_type",
        "a_job",
        "a_iconid",
        "a_iconrow",
        "a_iconcol",
        "a_name",
        "a_name_frc",
        "a_name_ita",
        "a_name_usa",
        "a_name_rus",
        "a_name_thai",
        "a_name_pld",
        "a_name_spn",
        "a_name_brz",
        "a_name_ger",
        "a_client_description",
        "a_client_description_frc",
        "a_client_description_ita",
        "a_client_description_usa",
        "a_client_description_rus",
        "a_client_description_thai",
        "a_client_description_pld",
        "a_client_description_spn",
        "a_client_description_brz",
        "a_client_description_ger",
        "a_name_mex",
        "a_client_description_mex"
            };

            Query.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'");
            string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query, rows);

            // Core values
            this.tb_action_id.Text = strArray[0];  // a_index
            this.textBox5.Text = strArray[1];      // a_type
            this.textBox15.Text = strArray[2];     // a_job
            this.textBox10.Text = strArray[3];     // a_iconid
            this.textBox11.Text = strArray[4];     // a_iconrow
            this.textBox12.Text = strArray[5];     // a_iconcol

            // Default name/desc (English)
            this.tb_name_action.Text = strArray[6];   // a_name
            this.tb_desc.Text = strArray[16];         // a_client_description

            // Localized overrides
            if (this.language == "FRA")
            {
                this.tb_name_action.Text = strArray[7];
                this.tb_desc.Text = strArray[17];
            }
            else if (this.language == "ITA")
            {
                this.tb_name_action.Text = strArray[8];
                this.tb_desc.Text = strArray[18];
            }
            else if (this.language == "USA")
            {
                this.tb_name_action.Text = strArray[9];
                this.tb_desc.Text = strArray[19];
            }
            else if (this.language == "RUS")
            {
                this.tb_name_action.Text = strArray[10];
                this.tb_desc.Text = strArray[20];
            }
            else if (this.language == "THA")
            {
                this.tb_name_action.Text = strArray[11];
                this.tb_desc.Text = strArray[21];
            }
            else if (this.language == "POL")
            {
                this.tb_name_action.Text = strArray[12];
                this.tb_desc.Text = strArray[22];
            }
            else if (this.language == "ESP")
            {
                this.tb_name_action.Text = strArray[13];
                this.tb_desc.Text = strArray[23];
            }
            else if (this.language == "BRA")
            {
                this.tb_name_action.Text = strArray[14];
                this.tb_desc.Text = strArray[24];
            }
            else if (this.language == "GER")
            {
                this.tb_name_action.Text = strArray[15];
                this.tb_desc.Text = strArray[25];
            }
            else if (this.language == "MEX")
            {
                this.tb_name_action.Text = strArray[26];
                this.tb_desc.Text = strArray[27];
            }

            // Type combo and job flags
            this.comboBox1.SelectedIndex = Convert.ToInt32(strArray[1]); // a_type
            this.ShowJobFlag(Convert.ToInt32(strArray[2]));              // a_job

            // Load icon
            try
            {
                this.pictureBox1.Image = (Image)this.databaseHandle.IconAction(
                    int.Parse(this.textBox10.Text),
                    int.Parse(this.textBox11.Text),
                    int.Parse(this.textBox12.Text));
            }
            catch { }
        }



        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox5.Text = this.comboBox1.SelectedIndex.ToString();
    }

    private void exitToolStripMenuItem_Click(object sender, EventArgs e) => this.Close();

    private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
    {
      int num = (int) MessageBox.Show("LastChaos Action Editor By inwshadow !", "About", MessageBoxButtons.OK, MessageBoxIcon.Asterisk, MessageBoxDefaultButton.Button2);
    }

        private void button9_Click(object sender, EventArgs e)
        {
            int selectedIndex = this.listBox1.SelectedIndex;

            this.descrr = this.DescrFromLanguage();
            this.namee = this.StringFromLanguage();

            // Escape user input safely
            string safeName = this.tb_name_action.Text.Replace("'", "\\'").Replace("\"", "\\\"");
            string safeDesc = this.tb_desc.Text.Replace("'", "\\'").Replace("\"", "\\\"");
            string safeJob = this.textBox15.Text.Replace("'", "\\'").Replace("\"", "\\\"");
            string safeIconId = this.textBox10.Text.Replace("'", "\\'").Replace("\"", "\\\"");
            string safeIconRow = this.textBox11.Text.Replace("'", "\\'").Replace("\"", "\\\"");
            string safeIconCol = this.textBox12.Text.Replace("'", "\\'").Replace("\"", "\\\"");
            string safeIndex = this.tb_action_id.Text.Replace("'", "\\'").Replace("\"", "\\\"");
            string safeType = this.textBox5.Text.Replace("'", "\\'").Replace("\"", "\\\"");

            string query = $"UPDATE t_action SET " +
                           $"a_type = '{safeType}', " +
                           $"{this.namee} = '{safeName}', " +
                           $"{this.descrr} = '{safeDesc}', " +
                           $"a_job = '{safeJob}', " +
                           $"a_iconid = '{safeIconId}', " +
                           $"a_iconrow = '{safeIconRow}', " +
                           $"a_iconcol = '{safeIconCol}' " +
                           $"WHERE a_index = '{safeIndex}'";

            this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, query);

            this.LoadListBox();
            this.listBox1.SelectedIndex = selectedIndex;
            new CustomMessage("Done :)").ShowDialog();
        }

    private void ShowJobFlag(int flag)
    {
      for (int index = 0; index < this.checkedListBox2.Items.Count; ++index)
        this.checkedListBox2.SetItemChecked(index, (flag & 1 << index) > 0);
    }

    private void checkedListBox2_SelectedIndexChanged(object sender, EventArgs e)
    {
      int num = 0;
      for (int index = 0; index < this.checkedListBox2.Items.Count; ++index)
      {
        if (this.checkedListBox2.GetItemChecked(index))
          num += 1 << index;
      }
      this.textBox15.Text = num.ToString();
    }

    private void checkedListBox2_SelectedValueChanged(object sender, EventArgs e)
    {
      this.textBox15.BackColor = Color.Pink;
    }


    private void checkBox1_CheckedChanged(object sender, EventArgs e)
    {
      if (this.checkBox1.Checked)
      {
        for (int index = 0; index < this.checkedListBox2.Items.Count; ++index)
        {
          this.checkedListBox2.SetItemChecked(index, true);
          this.textBox15.Text = "511";
        }
      }
      else
      {
        for (int index = 0; index < this.checkedListBox2.Items.Count; ++index)
        {
          this.checkedListBox2.SetItemChecked(index, false);
          this.textBox15.Text = "0";
        }
      }
    }

    private void checkBox1_SelectedValueChanged(object sender, EventArgs e)
    {
      this.textBox15.BackColor = Color.Pink;
    }

    private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
    {
      IconPickerAction iconPickerAction = new IconPickerAction();
      iconPickerAction.OldItemBtnSelect = Convert.ToInt32(this.textBox10.Text);
      if (iconPickerAction.ShowDialog() != DialogResult.OK)
        return;
      this.textBox10.Text = iconPickerAction.TexID.ToString();
      this.textBox11.Text = iconPickerAction.TexRow.ToString();
      this.textBox12.Text = iconPickerAction.TexColumn.ToString();
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_action SET a_iconid = '" + this.textBox10.Text + "', a_iconrow = '" + this.textBox11.Text + "', a_iconcol = '" + this.textBox12.Text + "' WHERE a_index = '" + this.tb_action_id.Text + "'");
      int selectedIndex = this.listBox1.SelectedIndex;
      this.LoadListBox();
      this.listBox1.SelectedIndex = selectedIndex;
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
      this.ExportToolStripMenuItem = new ToolStripMenuItem();
      this.exportStrActionToolStripMenuItem = new ToolStripMenuItem();
      this.exitToolStripMenuItem = new ToolStripMenuItem();
      this.textBox1 = new TextBox();
      this.textBox2 = new TextBox();
      this.textBox3 = new TextBox();
      this.textBox4 = new TextBox();
      this.textBox7 = new TextBox();
      this.label7 = new Label();
      this.groupBox4 = new GroupBox();
      this.textBox5 = new TextBox();
      this.groupBox21 = new GroupBox();
      this.checkBox1 = new CheckBox();
      this.textBox15 = new TextBox();
      this.label8 = new Label();
      this.checkedListBox2 = new CheckedListBox();
      this.textBox9 = new TextBox();
      this.groupBox9 = new GroupBox();
      this.linkLabel1 = new LinkLabel();
      this.pictureBox1 = new PictureBox();
      this.textBox12 = new TextBox();
      this.label50 = new Label();
      this.textBox10 = new TextBox();
      this.label48 = new Label();
      this.label49 = new Label();
      this.textBox11 = new TextBox();
      this.comboBox1 = new ComboBox();
      this.tb_name_action = new TextBox();
      this.label9 = new Label();
      this.tb_desc = new TextBox();
      this.tb_action_id = new TextBox();
      this.label10 = new Label();
      this.label11 = new Label();
      this.groupBox7 = new GroupBox();
      this.button6 = new Button();
      this.button12 = new Button();
      this.button8 = new Button();
      this.button9 = new Button();
      this.listBox1 = new ListBox();
      this.menuStrip1.SuspendLayout();
      this.groupBox4.SuspendLayout();
      this.groupBox21.SuspendLayout();
      this.groupBox9.SuspendLayout();
      ((ISupportInitialize) this.pictureBox1).BeginInit();
      this.groupBox7.SuspendLayout();
      this.SuspendLayout();
      this.menuStrip1.BackColor = Color.Transparent;
      this.menuStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.menüToolStripMenuItem
      });
      this.menuStrip1.Location = new Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new Size(704, 24);
      this.menuStrip1.TabIndex = 0;
      this.menuStrip1.Text = "menuStrip1";
      this.menüToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[3]
      {
        (ToolStripItem) this.ExportToolStripMenuItem,
        (ToolStripItem) this.exportStrActionToolStripMenuItem,
        (ToolStripItem) this.exitToolStripMenuItem
      });
      this.menüToolStripMenuItem.Name = "menüToolStripMenuItem";
      this.menüToolStripMenuItem.Size = new Size(74, 20);
      this.menüToolStripMenuItem.Text = "File Export";
      this.ExportToolStripMenuItem.Name = "ExportToolStripMenuItem";
      this.ExportToolStripMenuItem.Size = new Size(196, 22);
      this.ExportToolStripMenuItem.Text = "Export Action.lod";
      this.ExportToolStripMenuItem.Click += new EventHandler(this.ExportToolStripMenuItem_Click);
      this.exportStrActionToolStripMenuItem.Name = "exportStrActionToolStripMenuItem";
      this.exportStrActionToolStripMenuItem.Size = new Size(196, 22);
      this.exportStrActionToolStripMenuItem.Text = "Export strAction_xx.lod";
      this.exportStrActionToolStripMenuItem.Click += new EventHandler(this.exportStrActionToolStripMenuItem_Click);
      this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
      this.exitToolStripMenuItem.Size = new Size(196, 22);
      this.exitToolStripMenuItem.Text = "Exit";
      this.exitToolStripMenuItem.Click += new EventHandler(this.exitToolStripMenuItem_Click);
      this.textBox1.Location = new Point(493, 7);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(57, 20);
      this.textBox1.TabIndex = 3;
      this.textBox1.Visible = false;
      this.textBox2.Location = new Point(409, 7);
      this.textBox2.Name = "textBox2";
      this.textBox2.Size = new Size(54, 20);
      this.textBox2.TabIndex = 4;
      this.textBox2.Visible = false;
      this.textBox3.Location = new Point(633, 7);
      this.textBox3.Name = "textBox3";
      this.textBox3.Size = new Size(49, 20);
      this.textBox3.TabIndex = 5;
      this.textBox3.Visible = false;
      this.textBox4.Location = new Point(322, 7);
      this.textBox4.Name = "textBox4";
      this.textBox4.Size = new Size(57, 20);
      this.textBox4.TabIndex = 6;
      this.textBox4.Visible = false;
      this.textBox7.Location = new Point(568, 7);
      this.textBox7.Name = "textBox7";
      this.textBox7.Size = new Size(40, 20);
      this.textBox7.TabIndex = 6;
      this.textBox7.Visible = false;
      this.label7.AutoSize = true;
      this.label7.Location = new Point(211, 115);
      this.label7.Name = "label7";
      this.label7.Size = new Size(55, 13);
      this.label7.TabIndex = 14;
      this.label7.Text = "Catagory :";
      this.groupBox4.BackColor = Color.Linen;
      this.groupBox4.Controls.Add((Control) this.textBox5);
      this.groupBox4.Controls.Add((Control) this.groupBox21);
      this.groupBox4.Controls.Add((Control) this.groupBox9);
      this.groupBox4.Controls.Add((Control) this.comboBox1);
      this.groupBox4.Controls.Add((Control) this.tb_name_action);
      this.groupBox4.Controls.Add((Control) this.label9);
      this.groupBox4.Controls.Add((Control) this.tb_desc);
      this.groupBox4.Controls.Add((Control) this.tb_action_id);
      this.groupBox4.Controls.Add((Control) this.label7);
      this.groupBox4.Controls.Add((Control) this.label10);
      this.groupBox4.Controls.Add((Control) this.label11);
      this.groupBox4.Location = new Point(218, 91);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Size = new Size(478, 252);
      this.groupBox4.TabIndex = 9;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "Action Data";
      this.textBox5.Enabled = false;
      this.textBox5.Location = new Point(427, 112);
      this.textBox5.Name = "textBox5";
      this.textBox5.Size = new Size(45, 20);
      this.textBox5.TabIndex = 61;
      this.groupBox21.Controls.Add((Control) this.checkBox1);
      this.groupBox21.Controls.Add((Control) this.textBox15);
      this.groupBox21.Controls.Add((Control) this.label8);
      this.groupBox21.Controls.Add((Control) this.checkedListBox2);
      this.groupBox21.Controls.Add((Control) this.textBox9);
      this.groupBox21.Location = new Point(7, 132);
      this.groupBox21.Name = "groupBox21";
      this.groupBox21.Size = new Size(465, 114);
      this.groupBox21.TabIndex = 60;
      this.groupBox21.TabStop = false;
      this.groupBox21.Text = "Job";
      this.checkBox1.AutoSize = true;
      this.checkBox1.Location = new Point(12, 81);
      this.checkBox1.Name = "checkBox1";
      this.checkBox1.Size = new Size(71, 17);
      this.checkBox1.TabIndex = 48;
      this.checkBox1.Text = "Check All";
      this.checkBox1.UseVisualStyleBackColor = true;
      this.checkBox1.CheckedChanged += new EventHandler(this.checkBox1_CheckedChanged);
      this.textBox15.Location = new Point(145, 77);
      this.textBox15.Multiline = true;
      this.textBox15.Name = "textBox15";
      this.textBox15.Size = new Size(55, 21);
      this.textBox15.TabIndex = 47;
      this.label8.AutoSize = true;
      this.label8.Location = new Point(107, 81);
      this.label8.Name = "label8";
      this.label8.Size = new Size(34, 13);
      this.label8.TabIndex = 46;
      this.label8.Text = "Total:";
      this.checkedListBox2.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
      this.checkedListBox2.BackColor = SystemColors.Control;
      this.checkedListBox2.BorderStyle = BorderStyle.None;
      this.checkedListBox2.CheckOnClick = true;
      this.checkedListBox2.ColumnWidth = 105;
      this.checkedListBox2.FormattingEnabled = true;
      this.checkedListBox2.IntegralHeight = false;
      this.checkedListBox2.Items.AddRange(new object[9]
      {
        (object) "Titan",
        (object) "Knight",
        (object) "Healer",
        (object) "Mage",
        (object) "Rogue",
        (object) "Sorcerer",
        (object) "NS",
        (object) "Ex-Rogue",
        (object) "Ex-Mage"
      });
      this.checkedListBox2.Location = new Point(12, 19);
      this.checkedListBox2.MultiColumn = true;
      this.checkedListBox2.Name = "checkedListBox2";
      this.checkedListBox2.Size = new Size(447, 53);
      this.checkedListBox2.TabIndex = 39;
      this.checkedListBox2.SelectedIndexChanged += new EventHandler(this.checkedListBox2_SelectedIndexChanged);
      this.checkedListBox2.SelectedValueChanged += new EventHandler(this.checkedListBox2_SelectedValueChanged);
      this.textBox9.BorderStyle = BorderStyle.FixedSingle;
      this.textBox9.Location = new Point(47, 184);
      this.textBox9.Name = "textBox9";
      this.textBox9.Size = new Size(55, 20);
      this.textBox9.TabIndex = 12;
      this.groupBox9.Controls.Add((Control) this.linkLabel1);
      this.groupBox9.Controls.Add((Control) this.pictureBox1);
      this.groupBox9.Controls.Add((Control) this.textBox12);
      this.groupBox9.Controls.Add((Control) this.label50);
      this.groupBox9.Controls.Add((Control) this.textBox10);
      this.groupBox9.Controls.Add((Control) this.label48);
      this.groupBox9.Controls.Add((Control) this.label49);
      this.groupBox9.Controls.Add((Control) this.textBox11);
      this.groupBox9.Location = new Point(6, 26);
      this.groupBox9.Name = "groupBox9";
      this.groupBox9.Size = new Size(201, 100);
      this.groupBox9.TabIndex = 41;
      this.groupBox9.TabStop = false;
      this.groupBox9.Text = "Icon";
      this.linkLabel1.AutoSize = true;
      this.linkLabel1.LinkColor = Color.Blue;
      this.linkLabel1.Location = new Point(117, 75);
      this.linkLabel1.Name = "linkLabel1";
      this.linkLabel1.Size = new Size(61, 13);
      this.linkLabel1.TabIndex = 96;
      this.linkLabel1.TabStop = true;
      this.linkLabel1.Text = "Icon Picker";
      this.linkLabel1.LinkClicked += new LinkLabelLinkClickedEventHandler(this.linkLabel1_LinkClicked);
      this.pictureBox1.BackColor = SystemColors.ButtonHighlight;
      this.pictureBox1.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox1.Cursor = Cursors.Default;
      this.pictureBox1.Location = new Point((int) sbyte.MaxValue, 20);
      this.pictureBox1.Name = "pictureBox1";
      this.pictureBox1.Size = new Size(40, 40);
      this.pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
      this.pictureBox1.TabIndex = 95;
      this.pictureBox1.TabStop = false;
      this.textBox12.BorderStyle = BorderStyle.FixedSingle;
      this.textBox12.Location = new Point(59, 74);
      this.textBox12.Name = "textBox12";
      this.textBox12.Size = new Size(37, 20);
      this.textBox12.TabIndex = 38;
      this.label50.AutoSize = true;
      this.label50.Location = new Point(11, 76);
      this.label50.Name = "label50";
      this.label50.Size = new Size(25, 13);
      this.label50.TabIndex = 39;
      this.label50.Text = "Col:";
      this.textBox10.BorderStyle = BorderStyle.FixedSingle;
      this.textBox10.Location = new Point(59, 20);
      this.textBox10.Name = "textBox10";
      this.textBox10.Size = new Size(37, 20);
      this.textBox10.TabIndex = 34;
      this.label48.AutoSize = true;
      this.label48.Location = new Point(11, 22);
      this.label48.Name = "label48";
      this.label48.Size = new Size(21, 13);
      this.label48.TabIndex = 35;
      this.label48.Text = "ID:";
      this.label49.AutoSize = true;
      this.label49.Location = new Point(11, 48);
      this.label49.Name = "label49";
      this.label49.Size = new Size(32, 13);
      this.label49.TabIndex = 37;
      this.label49.Text = "Row:";
      this.textBox11.BorderStyle = BorderStyle.FixedSingle;
      this.textBox11.Location = new Point(59, 46);
      this.textBox11.Name = "textBox11";
      this.textBox11.Size = new Size(37, 20);
      this.textBox11.TabIndex = 36;
      this.comboBox1.BackColor = Color.GreenYellow;
      this.comboBox1.FlatStyle = FlatStyle.Flat;
      this.comboBox1.FormattingEnabled = true;
      this.comboBox1.Items.AddRange(new object[6]
      {
        (object) "0 - Action",
        (object) "1 - Social",
        (object) "2 - Party",
        (object) "3 - Guild",
        (object) "4 - Old pet active",
        (object) "5 - [P2] Pet active"
      });
      this.comboBox1.Location = new Point(274, 112);
      this.comboBox1.Name = "comboBox1";
      this.comboBox1.Size = new Size(144, 21);
      this.comboBox1.TabIndex = 37;
      this.comboBox1.SelectedIndexChanged += new EventHandler(this.comboBox1_SelectedIndexChanged);
      this.tb_name_action.Location = new Point(273, 55);
      this.tb_name_action.Name = "tb_name_action";
      this.tb_name_action.Size = new Size(145, 20);
      this.tb_name_action.TabIndex = 19;
      this.label9.AutoSize = true;
      this.label9.Location = new Point(225, 58);
      this.label9.Name = "label9";
      this.label9.Size = new Size(44, 13);
      this.label9.TabIndex = 18;
      this.label9.Text = "Name : ";
      this.tb_desc.Location = new Point(274, 81);
      this.tb_desc.Name = "tb_desc";
      this.tb_desc.Size = new Size(198, 20);
      this.tb_desc.TabIndex = 15;
      this.tb_action_id.Enabled = false;
      this.tb_action_id.Location = new Point(273, 26);
      this.tb_action_id.Name = "tb_action_id";
      this.tb_action_id.Size = new Size(78, 20);
      this.tb_action_id.TabIndex = 14;
      this.label10.AutoSize = true;
      this.label10.Location = new Point(221, 86);
      this.label10.Name = "label10";
      this.label10.Size = new Size(45, 13);
      this.label10.TabIndex = 17;
      this.label10.Text = "Tooltip :";
      this.label11.AutoSize = true;
      this.label11.Location = new Point(243, 29);
      this.label11.Name = "label11";
      this.label11.Size = new Size(27, 13);
      this.label11.TabIndex = 16;
      this.label11.Text = "ID : ";
      this.groupBox7.Controls.Add((Control) this.button6);
      this.groupBox7.Controls.Add((Control) this.button12);
      this.groupBox7.Controls.Add((Control) this.button8);
      this.groupBox7.Location = new Point(12, 33);
      this.groupBox7.Name = "groupBox7";
      this.groupBox7.Size = new Size(684, 52);
      this.groupBox7.TabIndex = 25;
      this.groupBox7.TabStop = false;
      this.groupBox7.Text = "Working";
      this.button6.BackColor = Color.Plum;
      this.button6.FlatStyle = FlatStyle.Flat;
      this.button6.Image = (Image) Resources.control_add_blue;
      this.button6.ImageAlign = ContentAlignment.MiddleLeft;
      this.button6.Location = new Point(112, 18);
      this.button6.Name = "button6";
      this.button6.Size = new Size(96, 27);
      this.button6.TabIndex = 15;
      this.button6.Text = "     Add Copy ";
      this.button6.UseVisualStyleBackColor = false;
      this.button6.Click += new EventHandler(this.button6_Click);
      this.button12.BackColor = Color.LightCoral;
      this.button12.FlatStyle = FlatStyle.Flat;
      this.button12.Image = (Image) Resources.delete;
      this.button12.ImageAlign = ContentAlignment.MiddleLeft;
      this.button12.Location = new Point(226, 17);
      this.button12.Name = "button12";
      this.button12.Size = new Size(81, 27);
      this.button12.TabIndex = 11;
      this.button12.Text = "    Delete";
      this.button12.UseVisualStyleBackColor = false;
      this.button12.Click += new EventHandler(this.button12_Click);
      this.button8.BackColor = Color.Honeydew;
      this.button8.FlatStyle = FlatStyle.Flat;
      this.button8.Image = (Image) Resources.control_add_blue;
      this.button8.ImageAlign = ContentAlignment.MiddleLeft;
      this.button8.Location = new Point(13, 18);
      this.button8.Name = "button8";
      this.button8.Size = new Size(81, 27);
      this.button8.TabIndex = 11;
      this.button8.Text = "     Add New";
      this.button8.UseVisualStyleBackColor = false;
      this.button8.Click += new EventHandler(this.button8_Click);
      this.button9.BackColor = Color.LightCyan;
      this.button9.FlatStyle = FlatStyle.Flat;
      this.button9.Image = (Image) Resources._08;
      this.button9.ImageAlign = ContentAlignment.MiddleLeft;
      this.button9.Location = new Point(601, 358);
      this.button9.Name = "button9";
      this.button9.Size = new Size(81, 27);
      this.button9.TabIndex = 12;
      this.button9.Text = "   Save";
      this.button9.UseVisualStyleBackColor = false;
      this.button9.Click += new EventHandler(this.button9_Click);
      this.listBox1.FormattingEnabled = true;
      this.listBox1.Location = new Point(12, 97);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new Size(200, 290);
      this.listBox1.TabIndex = 27;
      this.listBox1.SelectedIndexChanged += new EventHandler(this.ListBox1_SelectedIndexChanged);
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.BackColor = Color.White;
      this.ClientSize = new Size(704, 404);
      this.Controls.Add((Control) this.listBox1);
      this.Controls.Add((Control) this.button9);
      this.Controls.Add((Control) this.groupBox7);
      this.Controls.Add((Control) this.groupBox4);
      this.Controls.Add((Control) this.textBox7);
      this.Controls.Add((Control) this.textBox4);
      this.Controls.Add((Control) this.textBox3);
      this.Controls.Add((Control) this.textBox2);
      this.Controls.Add((Control) this.textBox1);
      this.Controls.Add((Control) this.menuStrip1);
      this.FormBorderStyle = FormBorderStyle.Fixed3D;
      this.MainMenuStrip = this.menuStrip1;
      this.MaximizeBox = false;
      this.Name = nameof (ActionEditor);
      this.Text = "LastChaos Action Editor";
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.groupBox4.ResumeLayout(false);
      this.groupBox4.PerformLayout();
      this.groupBox21.ResumeLayout(false);
      this.groupBox21.PerformLayout();
      this.groupBox9.ResumeLayout(false);
      this.groupBox9.PerformLayout();
      ((ISupportInitialize) this.pictureBox1).EndInit();
      this.groupBox7.ResumeLayout(false);
      this.groupBox7.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();
    }

    private void button12_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want to delete " + this.tb_desc.Text.Trim() + " ?", "Please confirm delete.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      if (this.tb_action_id.Text.Trim().Length <= 0)
      {
        int num = (int) MessageBox.Show("No data to delete in select item to delete first", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "delete from t_action where a_index = " + this.tb_action_id.Text.Trim());
        this.LoadListBox();
        this.listBox1.SelectedIndex = this.listBox1.Items.Count - 1;
      }
    }

    private void button6_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want copy to New From Index " + this.tb_action_id.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      if (this.tb_action_id.Text.Trim().Length <= 0)
      {
        int num1 = (int) MessageBox.Show("No data to select", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DROP TABLE IF EXISTS tempTable;CREATE TEMPORARY TABLE tempTable ENGINE=MEMORY SELECT * FROM t_action WHERE a_index=" + this.tb_action_id.Text + ";SELECT a_index FROM tempTable;UPDATE tempTable SET a_index=(SELECT a_index from t_action ORDER BY a_index DESC LIMIT 1)+1; SELECT a_index FROM tempTable;INSERT INTO t_action SELECT * FROM tempTable;");
        int num2 = (int) MessageBox.Show("Successful copy", "Completed", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
        this.LoadListBox();
        this.listBox1.SelectedIndex = this.listBox1.Items.Count - 1;
      }
    }

    private void button8_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want add New " + this.tb_action_id.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      if (this.tb_action_id.Text.Trim().Length <= 0)
      {
        int num1 = (int) MessageBox.Show("No data to select", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_action DEFAULT VALUES");
        int num2 = (int) MessageBox.Show("Successful add new", "Completed", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
        this.LoadListBox();
        this.listBox1.SelectedIndex = this.listBox1.Items.Count - 1;
      }
    }

    private void settingToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (new LcDevPack_TeamDamonA.Tools.Settings().ShowDialog() == DialogResult.OK)
        ;
    }

    private void ExportToolStripMenuItem_Click(object sender, EventArgs e)
    {
      new LodExporter.LodExporter().Show();
    }

    private void exportStrActionToolStripMenuItem_Click(object sender, EventArgs e)
    {
      new FormExport().Show();
    }
  }
}
