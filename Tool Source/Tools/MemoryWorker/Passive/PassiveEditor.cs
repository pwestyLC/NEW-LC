// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.Passive.PassiveEditor
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using LcDevPack_TeamDamonA.Properties;
using MySqlConnector;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.Passive
{
  public class PassiveEditor : Form
  {
    public static Connection connection = new Connection();
    private static System.Collections.Generic.List<t_passive_system> RareOptionList = new System.Collections.Generic.List<t_passive_system>();
    private string Host = PassiveEditor.connection.Settings.SqlHost;
    private string User = PassiveEditor.connection.Settings.SqlUser;
    private string Password = PassiveEditor.connection.Settings.SqlPassword;
    private string Database = PassiveEditor.connection.Settings.SqlDatabase;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    private ExportLodHandle exportLodHandle = new ExportLodHandle();
    public string _ClientPath = LcDevPack_TeamDamonA.Tools.MobEditor.connection.Settings.ClientPath;
    private IContainer components = (IContainer) null;
    public System.Collections.Generic.List<string> MenuList = new System.Collections.Generic.List<string>();
    public string[] menuArray = new string[2]
    {
      "a_index",
      "a_name"
    };
    private string language = ItemEditor2.connection.Settings.Language;
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
      "a_name_frc"
    };
    public string[] menuArrayESP = new string[2]
    {
      "a_index",
      "a_name_spn"
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
    public string[] menuArrayUSA = new string[2]
    {
      "a_index",
      "a_name_usa"
    };
    private TextBox idtxt;
    private Label label1;
    private GroupBox groupBox3;
    private TextBox Passive_Desc;
    private Label label2;
    private TextBox Passive_name;
    private Label label4;
    private string namee;
    private TextBox icon_col;
    private Label label3;
    private TextBox icon_row;
    private string clientDesc;
    public string[] menuArray3 = new string[1]{ "a_level" };
    private ToolStrip toolStrip1;
    private ToolStripDropDownButton toolStripDropDownButton1;
    private ToolStripMenuItem exportToolStripMenuItem;
    private ToolStripMenuItem PassivelodToolStripMenuItem;
    private ToolStripMenuItem strPassiveusToolStripMenuItem;
    public bool _ComboBoxLocked = false;
    private GroupBox groupBox1;
    private GroupBox groupBox2;
    private Button UpdateButton;
    private Button remove;
    private ListBox listBox1;
    private Button button1;
    private GroupBox groupBox13;
    private TextBox a_option_level;
    private Label label70;
    private TextBox a_option_id;
    private Label label60;
    private GroupBox groupBox17;
    private ComboBox comboBox14;
    private ComboBox comboBox3;
    private Label label95;
    public System.Collections.Generic.List<string> List;
    public System.Collections.Generic.List<string> List2;
    public System.Collections.Generic.List<string> List3;
    public System.Collections.Generic.List<string> List4;
    public System.Collections.Generic.List<string> List5;
    public System.Collections.Generic.List<string> List6;
    public System.Collections.Generic.List<string> List7;
    public System.Collections.Generic.List<string> List8;
    public System.Collections.Generic.List<string> List9;
    public System.Collections.Generic.List<string> List11;
    public System.Collections.Generic.List<string> List12;
    public System.Collections.Generic.List<string> List13;
    public System.Collections.Generic.List<string> List14;
    public System.Collections.Generic.List<string> List15;
    public System.Collections.Generic.List<string> List16;
    public System.Collections.Generic.List<string> List17;
    public System.Collections.Generic.List<string> List18;
    public System.Collections.Generic.List<string> List19;
    public System.Collections.Generic.List<string> List20;
    public System.Collections.Generic.List<string> List10;
    public string name;

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

    public string DescFromLanguage()
    {
      if (this.language == "GER")
      {
        this.clientDesc = "a_client_description_ger";
        return this.clientDesc;
      }
      if (this.language == "POL")
      {
        this.clientDesc = "a_client_description_pld";
        return this.clientDesc;
      }
      if (this.language == "BRA")
      {
        this.clientDesc = "a_client_description_brz";
        return this.clientDesc;
      }
      if (this.language == "RUS")
      {
        this.clientDesc = "a_client_description_rus";
        return this.clientDesc;
      }
      if (this.language == "FRA")
      {
        this.clientDesc = "a_client_description_frc";
        return this.clientDesc;
      }
      if (this.language == "ESP")
      {
        this.clientDesc = "a_client_description_spn";
        return this.clientDesc;
      }
      if (this.language == "MEX")
      {
        this.clientDesc = "a_client_description_mex";
        return this.clientDesc;
      }
      if (this.language == "THA")
      {
        this.clientDesc = "a_client_description_thai";
        return this.clientDesc;
      }
      if (this.language == "ITA")
      {
        this.clientDesc = "a_client_description_ita";
        return this.clientDesc;
      }
      if (!(this.language == "USA"))
        return (string) null;
      this.clientDesc = "a_client_description_usa";
      return this.clientDesc;
    }

    public PassiveEditor()
    {
      this.InitializeComponent();
      this.LoadStartUp();
      this.Fill_listbox();
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

        private void LoadStartUp()
        {
            try
            {
                // Determine which language column to use (e.g. a_name_eng, a_name_ger, etc.)
                this.namee = this.StringFromLanguage();
                if (string.IsNullOrEmpty(this.namee))
                    this.namee = "a_name"; // fallback if language string is missing

                string query = "SELECT a_index, a_type, " + this.namee + " FROM t_option ORDER BY a_index;";

                using (MySqlConnection conn = new MySqlConnection(
                    "datasource=" + this.Host +
                    ";Port=3306;" +
                    "User ID=" + this.User +
                    ";Password=" + this.Password +
                    ";Database=" + this.Database +
                    ";Charset=utf8mb4;" +
                    "SslMode=Preferred;" +
                    "TlsVersion=Tls12"))
                using (MySqlCommand cmd = conn.CreateCommand())
                {
                    cmd.CommandText = query;
                    conn.Open();

                    using (MySqlDataReader reader = cmd.ExecuteReader())
                    {
                        comboBox3.Items.Clear();

                        while (reader.Read())
                        {
                            string type = reader["a_type"].ToString();
                            string name = reader[this.namee].ToString();

                            comboBox3.Items.Add($"{type} - {name}");
                        }
                    }
                }

                // Auto-select first item if any results
                if (comboBox3.Items.Count > 0)
                    comboBox3.SelectedIndex = 0;
            }
            catch (Exception ex)
            {
                MessageBox.Show("Failed to load t_option data:\n" + ex.Message,
                    "Database Error",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error);
            }
        }


        private void comboBox3_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.a_option_id.Text = this.comboBox3.SelectedIndex.ToString();
      this.List = this.databaseHandle.SelectMySqlExplodedReturnList(this.menuArray3, this.Host, this.User, this.Password, this.Database, "select * from t_option WHERE a_type = '" + this.a_option_id.Text + "' ORDER BY a_index;");
      this.comboBox14.DataSource = (object) null;
      this.comboBox14.Items.Clear();
      this.comboBox14.DataSource = (object) this.List;
      if (!(this.a_option_id.Text != "-1"))
        return;
      this.comboBox14.SelectedIndex = Convert.ToInt32(this.a_option_level.Text) - 1;
    }

    private void comboBox3_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.comboBox3.BackColor = Color.Pink;
    }

    private void comboBox14_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.comboBox14.BackColor = Color.Pink;
    }

    private void comboBox14_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (this._ComboBoxLocked)
        return;
      this.a_option_level.Text = this.comboBox14.SelectedIndex.ToString();
    }

    private void ClearComboBoxPurple2() => this.comboBox14.SelectedIndex = -1;

    private void ClearComboBoxPurple() => this.comboBox3.SelectedIndex = -1;

    private void ResetComboBoxPurpleBg() => this.comboBox3.BackColor = Color.White;

        private void Fill_listbox()
        {
            try
            {
                // Determine which column to use for the name (language column)
                this.namee = this.StringFromLanguage();
                if (string.IsNullOrEmpty(this.namee))
                    this.namee = "a_name"; // fallback if language name not resolved

                string query = "SELECT a_index, " + this.namee + " FROM t_passive_system ORDER BY a_index ASC;";

                using (var conn = new MySqlConnection(
                    "datasource=" + this.Host +
                    ";Port=3306;" +
                    "User ID=" + this.User +
                    ";Password=" + this.Password +
                    ";Database=" + this.Database +
                    ";Charset=utf8mb4;" +
                    "SslMode=Preferred;" +
                    "TlsVersion=Tls12"))
                using (var cmd = new MySqlCommand(query, conn))
                {
                    conn.Open();
                    using (var reader = cmd.ExecuteReader())
                    {
                        listBox1.Items.Clear();

                        while (reader.Read())
                        {
                            string index = reader["a_index"].ToString();
                            string name = "";

                            try
                            {
                                name = reader[this.namee].ToString();
                            }
                            catch
                            {
                                name = "(missing column)";
                            }

                            listBox1.Items.Add($"{index} - {name}");
                        }
                    }
                }

                // Optional: auto-select first entry
                if (listBox1.Items.Count > 0)
                    listBox1.SelectedIndex = 0;
            }
            catch (Exception ex)
            {
                MessageBox.Show(
                    "Error while loading passive system list:\n" + ex.Message,
                    "Database Error",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error
                );
            }
        }


        private void Fill_listbox2()
        {
            try
            {
                // Ensure no item is selected while refreshing
                listBox1.SelectedIndex = -1;

                // Clear old menu data
                MenuList.Clear();

                // Build query
                string query = "SELECT * FROM t_passive_system ORDER BY a_index ASC;";

                // Pick correct language array
                List<string> rawList;
                if (language == "USA")
                    rawList = databaseHandle.SelectMySqlReturnList(menuArrayUSA, Host, User, Password, Database, query);
                else if (language == "THA")
                    rawList = databaseHandle.SelectMySqlReturnList(menuArrayTHA, Host, User, Password, Database, query);
                else
                    rawList = databaseHandle.SelectMySqlReturnList(menuArray, Host, User, Password, Database, query);

                // Verify the result and store into MenuList
                if (rawList != null && rawList.Count > 0)
                {
                    foreach (string item in rawList)
                        MenuList.Add(item);
                }

                // Rebind data safely
                listBox1.DataSource = null;
                listBox1.DataSource = MenuList;

                // Start with no selection
                listBox1.SelectedIndex = -1;
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Error while loading passive system list:\n{ex.Message}",
                    "Database Error",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error);
            }
        }


        private void RestTextBoxField()
    {
    }

    private void ListBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.namee = this.StringFromLanguage();
      this.clientDesc = this.DescFromLanguage();
            string connectionString =
                      $"Server={Host};Port=3306;User ID={User};Password={Password};Database={Database};" +
                      "SslMode=Preferred;TlsVersion=Tls12;";
            string cmdText = "select * FROM t_passive_system WHERE a_index ='" + this.listBox1.Text + "';";
      MySqlConnection connection = new MySqlConnection(connectionString);
      MySqlCommand mySqlCommand = new MySqlCommand(cmdText, connection);
      try
      {
        connection.Open();
        MySqlDataReader mySqlDataReader = mySqlCommand.ExecuteReader();
        while (mySqlDataReader.Read())
        {
          int int32 = mySqlDataReader.GetInt32("a_index");
          string str1 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("a_option_id");
          string str2 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("a_option_level");
          string str3 = int32.ToString();
          int ordinal1 = mySqlDataReader.GetOrdinal(this.namee ?? "");
          string str4 = mySqlDataReader.GetString(ordinal1);
          int ordinal2 = mySqlDataReader.GetOrdinal(this.clientDesc ?? "");
          string str5 = mySqlDataReader.GetString(ordinal2);
          int32 = mySqlDataReader.GetInt32("a_row");
          string str6 = int32.ToString();
          int32 = mySqlDataReader.GetInt32("a_col");
          string str7 = int32.ToString();
          this.idtxt.Text = str1;
          this.Passive_name.Text = str4;
          this.Passive_Desc.Text = str5;
          this.a_option_id.Text = str2;
          this.icon_row.Text = str6;
          this.icon_col.Text = str7;
          this.comboBox3.SelectedIndex = Convert.ToInt32(str2);
          this.a_option_level.Text = str3;
          this.comboBox14.SelectedIndex = Convert.ToInt32(str3);
        }
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message);
      }
      connection.Close();
    }

    private void UpdateButton_Click(object sender, EventArgs e)
    {
      this.namee = this.StringFromLanguage();
      this.clientDesc = this.DescFromLanguage();
      int selectedIndex = this.listBox1.SelectedIndex;
      if (MessageBox.Show("Do you want to Change Passive Option " + this.idtxt.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_passive_system SET a_option_id = '" + this.a_option_id.Text + "', a_option_level = '" + this.a_option_level.Text + "', a_row = '" + this.icon_row.Text + "', a_col = '" + this.icon_col.Text + "', " + this.namee + " = '" + this.Passive_name.Text + "', " + this.clientDesc + " = '" + this.Passive_Desc.Text + "' WHERE a_index = '" + this.idtxt.Text + "'");
      this.Fill_listbox2();
      this.listBox1.SelectedIndex = selectedIndex;
      this.ResetComboBoxPurpleBg();
      int num = (int) new CustomMessage("Update Done :)").ShowDialog();
    }

    private void Remove_Click(object sender, EventArgs e)
    {
      int selectedIndex = this.listBox1.SelectedIndex;
      if (MessageBox.Show("Do you want to Delete Option " + this.idtxt.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_passive_system WHERE a_index = '" + this.idtxt.Text + "'");
      this.Fill_listbox2();
      this.listBox1.SelectedIndex = this.listBox1.Items.Count - 1;
      this.ResetComboBoxPurpleBg();
      int num = (int) new CustomMessage("Deleted :O").ShowDialog();
    }

    private void Button1_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want to Copy?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DROP TABLE IF EXISTS tempTable;CREATE TEMPORARY TABLE tempTable ENGINE=MyISAM SELECT * FROM t_passive_system WHERE a_index =" + this.idtxt.Text + ";SELECT a_index FROM tempTable;UPDATE tempTable SET a_index=(SELECT a_index from t_passive_system ORDER BY a_index DESC LIMIT 1)+1; SELECT a_index FROM tempTable;INSERT INTO t_passive_system SELECT * FROM tempTable;");
      this.Fill_listbox2();
      this.listBox1.SelectedIndex = this.listBox1.Items.Count - 1;
      int num = (int) new CustomMessage("Copying Complete").ShowDialog();
      this.ResetComboBoxPurpleBg();
    }

    private void PassiveEditor_Load(object sender, EventArgs e)
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
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (PassiveEditor));
      this.toolStrip1 = new ToolStrip();
      this.toolStripDropDownButton1 = new ToolStripDropDownButton();
      this.exportToolStripMenuItem = new ToolStripMenuItem();
      this.PassivelodToolStripMenuItem = new ToolStripMenuItem();
      this.strPassiveusToolStripMenuItem = new ToolStripMenuItem();
      this.groupBox1 = new GroupBox();
      this.groupBox3 = new GroupBox();
      this.icon_col = new TextBox();
      this.label3 = new Label();
      this.icon_row = new TextBox();
      this.idtxt = new TextBox();
      this.Passive_Desc = new TextBox();
      this.label2 = new Label();
      this.Passive_name = new TextBox();
      this.label1 = new Label();
      this.label4 = new Label();
      this.groupBox17 = new GroupBox();
      this.comboBox14 = new ComboBox();
      this.comboBox3 = new ComboBox();
      this.label95 = new Label();
      this.groupBox13 = new GroupBox();
      this.a_option_level = new TextBox();
      this.label70 = new Label();
      this.a_option_id = new TextBox();
      this.label60 = new Label();
      this.groupBox2 = new GroupBox();
      this.button1 = new Button();
      this.UpdateButton = new Button();
      this.remove = new Button();
      this.listBox1 = new ListBox();
      this.toolStrip1.SuspendLayout();
      this.groupBox1.SuspendLayout();
      this.groupBox3.SuspendLayout();
      this.groupBox17.SuspendLayout();
      this.groupBox13.SuspendLayout();
      this.groupBox2.SuspendLayout();
      this.SuspendLayout();
      this.toolStrip1.ImageScalingSize = new Size(20, 20);
      this.toolStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.toolStripDropDownButton1
      });
      this.toolStrip1.Location = new Point(0, 0);
      this.toolStrip1.Name = "toolStrip1";
      this.toolStrip1.Size = new Size(782, 27);
      this.toolStrip1.TabIndex = 0;
      this.toolStrip1.Text = "toolStrip1";
      this.toolStripDropDownButton1.DisplayStyle = ToolStripItemDisplayStyle.Image;
      this.toolStripDropDownButton1.DropDownItems.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.exportToolStripMenuItem
      });
      this.toolStripDropDownButton1.Image = (Image) Resources._08;
      this.toolStripDropDownButton1.ImageTransparentColor = Color.Magenta;
      this.toolStripDropDownButton1.Name = "toolStripDropDownButton1";
      this.toolStripDropDownButton1.Size = new Size(34, 24);
      this.toolStripDropDownButton1.Text = "toolStripDropDownButton1";
      this.exportToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[2]
      {
        (ToolStripItem) this.PassivelodToolStripMenuItem,
        (ToolStripItem) this.strPassiveusToolStripMenuItem
      });
      this.exportToolStripMenuItem.Name = "exportToolStripMenuItem";
      this.exportToolStripMenuItem.Size = new Size(135, 26);
      this.exportToolStripMenuItem.Text = "Export";
      this.PassivelodToolStripMenuItem.Name = "PassivelodToolStripMenuItem";
      this.PassivelodToolStripMenuItem.Size = new Size(212, 26);
      this.PassivelodToolStripMenuItem.Text = "passiveSystem.lod";
      this.PassivelodToolStripMenuItem.Click += new EventHandler(this.rareOptionlodToolStripMenuItem_Click);
      this.strPassiveusToolStripMenuItem.Name = "strPassiveusToolStripMenuItem";
      this.strPassiveusToolStripMenuItem.Size = new Size(212, 26);
      this.strPassiveusToolStripMenuItem.Text = "strPassiveSystem";
      this.strPassiveusToolStripMenuItem.Click += new EventHandler(this.strRareOptionusToolStripMenuItem_Click);
      this.groupBox1.Controls.Add((Control) this.groupBox3);
      this.groupBox1.Controls.Add((Control) this.groupBox17);
      this.groupBox1.Controls.Add((Control) this.groupBox13);
      this.groupBox1.Controls.Add((Control) this.groupBox2);
      this.groupBox1.Controls.Add((Control) this.listBox1);
      this.groupBox1.Location = new Point(16, 34);
      this.groupBox1.Margin = new Padding(4);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Padding = new Padding(4);
      this.groupBox1.Size = new Size(759, 438);
      this.groupBox1.TabIndex = 1;
      this.groupBox1.TabStop = false;
      this.groupBox3.Controls.Add((Control) this.icon_col);
      this.groupBox3.Controls.Add((Control) this.label3);
      this.groupBox3.Controls.Add((Control) this.icon_row);
      this.groupBox3.Controls.Add((Control) this.idtxt);
      this.groupBox3.Controls.Add((Control) this.Passive_Desc);
      this.groupBox3.Controls.Add((Control) this.label2);
      this.groupBox3.Controls.Add((Control) this.Passive_name);
      this.groupBox3.Controls.Add((Control) this.label1);
      this.groupBox3.Controls.Add((Control) this.label4);
      this.groupBox3.Location = new Point(242, 23);
      this.groupBox3.Margin = new Padding(4);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Padding = new Padding(4);
      this.groupBox3.Size = new Size(489, 98);
      this.groupBox3.TabIndex = 44;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "Passive Options Value";
      this.icon_col.BorderStyle = BorderStyle.FixedSingle;
      this.icon_col.Location = new Point(114, 68);
      this.icon_col.Margin = new Padding(4);
      this.icon_col.Name = "icon_col";
      this.icon_col.Size = new Size(46, 22);
      this.icon_col.TabIndex = 67;
      this.label3.AutoSize = true;
      this.label3.Location = new Point(3, 70);
      this.label3.Margin = new Padding(4, 0, 4, 0);
      this.label3.Name = "label3";
      this.label3.Size = new Size(35, 16);
      this.label3.TabIndex = 65;
      this.label3.Text = "Icon:";
      this.icon_row.BorderStyle = BorderStyle.FixedSingle;
      this.icon_row.Location = new Point(46, 68);
      this.icon_row.Margin = new Padding(4);
      this.icon_row.Name = "icon_row";
      this.icon_row.Size = new Size(46, 22);
      this.icon_row.TabIndex = 64;
      this.idtxt.Enabled = false;
      this.idtxt.Location = new Point(75, 31);
      this.idtxt.Margin = new Padding(4);
      this.idtxt.Name = "idtxt";
      this.idtxt.Size = new Size(63, 22);
      this.idtxt.TabIndex = 63;
      this.Passive_Desc.BorderStyle = BorderStyle.FixedSingle;
      this.Passive_Desc.Location = new Point(245, 59);
      this.Passive_Desc.Margin = new Padding(4);
      this.Passive_Desc.Name = "Passive_Desc";
      this.Passive_Desc.Size = new Size(233, 22);
      this.Passive_Desc.TabIndex = 60;
      this.label2.AutoSize = true;
      this.label2.Location = new Point(195, 61);
      this.label2.Margin = new Padding(4, 0, 4, 0);
      this.label2.Name = "label2";
      this.label2.Size = new Size(42, 16);
      this.label2.TabIndex = 61;
      this.label2.Text = "Desc:";
      this.Passive_name.BorderStyle = BorderStyle.FixedSingle;
      this.Passive_name.Location = new Point(245, 31);
      this.Passive_name.Margin = new Padding(4);
      this.Passive_name.Name = "Passive_name";
      this.Passive_name.Size = new Size(233, 22);
      this.Passive_name.TabIndex = 40;
      this.label1.AutoSize = true;
      this.label1.Location = new Point(19, 33);
      this.label1.Margin = new Padding(4, 0, 4, 0);
      this.label1.Name = "label1";
      this.label1.Size = new Size(26, 16);
      this.label1.TabIndex = 62;
      this.label1.Text = "ID :";
      this.label4.AutoSize = true;
      this.label4.Location = new Point(195, 33);
      this.label4.Margin = new Padding(4, 0, 4, 0);
      this.label4.Name = "label4";
      this.label4.Size = new Size(47, 16);
      this.label4.TabIndex = 41;
      this.label4.Text = "Name:";
      this.groupBox17.Controls.Add((Control) this.comboBox14);
      this.groupBox17.Controls.Add((Control) this.comboBox3);
      this.groupBox17.Controls.Add((Control) this.label95);
      this.groupBox17.Location = new Point(245, 227);
      this.groupBox17.Margin = new Padding(4);
      this.groupBox17.Name = "groupBox17";
      this.groupBox17.Padding = new Padding(4);
      this.groupBox17.Size = new Size(489, 80);
      this.groupBox17.TabIndex = 43;
      this.groupBox17.TabStop = false;
      this.groupBox17.Text = "Option Selecter";
      this.comboBox14.FlatStyle = FlatStyle.Flat;
      this.comboBox14.FormattingEnabled = true;
      this.comboBox14.Location = new Point(368, 22);
      this.comboBox14.Margin = new Padding(4);
      this.comboBox14.Name = "comboBox14";
      this.comboBox14.Size = new Size(107, 24);
      this.comboBox14.TabIndex = 28;
      this.comboBox14.SelectedIndexChanged += new EventHandler(this.comboBox14_SelectedIndexChanged);
      this.comboBox14.SelectionChangeCommitted += new EventHandler(this.comboBox14_SelectionChangeCommitted);
      this.comboBox3.FlatStyle = FlatStyle.Flat;
      this.comboBox3.FormattingEnabled = true;
      this.comboBox3.Location = new Point(68, 22);
      this.comboBox3.Margin = new Padding(4);
      this.comboBox3.Name = "comboBox3";
      this.comboBox3.Size = new Size(288, 24);
      this.comboBox3.TabIndex = 1;
      this.comboBox3.SelectedIndexChanged += new EventHandler(this.comboBox3_SelectedIndexChanged);
      this.comboBox3.SelectionChangeCommitted += new EventHandler(this.comboBox3_SelectionChangeCommitted);
      this.label95.AutoSize = true;
      this.label95.Location = new Point(7, 26);
      this.label95.Margin = new Padding(4, 0, 4, 0);
      this.label95.Name = "label95";
      this.label95.Size = new Size(41, 16);
      this.label95.TabIndex = 0;
      this.label95.Text = "Seal :";
      this.groupBox13.Controls.Add((Control) this.a_option_level);
      this.groupBox13.Controls.Add((Control) this.label70);
      this.groupBox13.Controls.Add((Control) this.a_option_id);
      this.groupBox13.Controls.Add((Control) this.label60);
      this.groupBox13.Location = new Point(242, 129);
      this.groupBox13.Margin = new Padding(4);
      this.groupBox13.Name = "groupBox13";
      this.groupBox13.Padding = new Padding(4);
      this.groupBox13.Size = new Size(489, 80);
      this.groupBox13.TabIndex = 42;
      this.groupBox13.TabStop = false;
      this.groupBox13.Text = "Passive Options Value";
      this.a_option_level.BorderStyle = BorderStyle.FixedSingle;
      this.a_option_level.Location = new Point(366, 31);
      this.a_option_level.Margin = new Padding(4);
      this.a_option_level.Name = "a_option_level";
      this.a_option_level.Size = new Size(81, 22);
      this.a_option_level.TabIndex = 60;
      this.label70.AutoSize = true;
      this.label70.Location = new Point(295, 33);
      this.label70.Margin = new Padding(4, 0, 4, 0);
      this.label70.Name = "label70";
      this.label70.Size = new Size(43, 16);
      this.label70.TabIndex = 61;
      this.label70.Text = "Level:";
      this.a_option_id.BorderStyle = BorderStyle.FixedSingle;
      this.a_option_id.Location = new Point(161, 31);
      this.a_option_id.Margin = new Padding(4);
      this.a_option_id.Name = "a_option_id";
      this.a_option_id.Size = new Size(81, 22);
      this.a_option_id.TabIndex = 40;
      this.label60.AutoSize = true;
      this.label60.Location = new Point(90, 33);
      this.label60.Margin = new Padding(4, 0, 4, 0);
      this.label60.Name = "label60";
      this.label60.Size = new Size(49, 16);
      this.label60.TabIndex = 41;
      this.label60.Text = "Option:";
      this.groupBox2.Controls.Add((Control) this.button1);
      this.groupBox2.Controls.Add((Control) this.UpdateButton);
      this.groupBox2.Controls.Add((Control) this.remove);
      this.groupBox2.Location = new Point(245, 348);
      this.groupBox2.Margin = new Padding(4);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Padding = new Padding(4);
      this.groupBox2.Size = new Size(489, 74);
      this.groupBox2.TabIndex = 1;
      this.groupBox2.TabStop = false;
      this.button1.BackColor = Color.Plum;
      this.button1.FlatStyle = FlatStyle.Flat;
      this.button1.Image = (Image) Resources.control_add_blue;
      this.button1.ImageAlign = ContentAlignment.MiddleLeft;
      this.button1.Location = new Point(90, 23);
      this.button1.Margin = new Padding(4);
      this.button1.Name = "button1";
      this.button1.Size = new Size(103, 33);
      this.button1.TabIndex = 63;
      this.button1.Text = "     Add";
      this.button1.UseVisualStyleBackColor = false;
      this.button1.Click += new EventHandler(this.Button1_Click);
      this.UpdateButton.BackColor = Color.LightCyan;
      this.UpdateButton.FlatStyle = FlatStyle.Flat;
      this.UpdateButton.Image = (Image) Resources._08;
      this.UpdateButton.ImageAlign = ContentAlignment.MiddleLeft;
      this.UpdateButton.Location = new Point(209, 23);
      this.UpdateButton.Margin = new Padding(4);
      this.UpdateButton.Name = "UpdateButton";
      this.UpdateButton.Size = new Size(96, 33);
      this.UpdateButton.TabIndex = 102;
      this.UpdateButton.Text = "      Update";
      this.UpdateButton.UseVisualStyleBackColor = false;
      this.UpdateButton.Click += new EventHandler(this.UpdateButton_Click);
      this.remove.BackColor = Color.LightCoral;
      this.remove.FlatStyle = FlatStyle.Flat;
      this.remove.Image = (Image) Resources.delete;
      this.remove.ImageAlign = ContentAlignment.MiddleLeft;
      this.remove.Location = new Point(321, 23);
      this.remove.Margin = new Padding(4);
      this.remove.Name = "remove";
      this.remove.Size = new Size(87, 33);
      this.remove.TabIndex = 103;
      this.remove.Text = "    Delete";
      this.remove.UseVisualStyleBackColor = false;
      this.remove.Click += new EventHandler(this.Remove_Click);
      this.listBox1.FormattingEnabled = true;
      this.listBox1.ItemHeight = 16;
      this.listBox1.Location = new Point(9, 18);
      this.listBox1.Margin = new Padding(4);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new Size(228, 404);
      this.listBox1.TabIndex = 0;
      this.listBox1.SelectedIndexChanged += new EventHandler(this.ListBox1_SelectedIndexChanged);
      this.AutoScaleDimensions = new SizeF(8f, 16f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(782, 482);
      this.Controls.Add((Control) this.groupBox1);
      this.Controls.Add((Control) this.toolStrip1);
      this.Icon = (Icon) componentResourceManager.GetObject("$this.Icon");
      this.Margin = new Padding(4);
      this.Name = nameof (PassiveEditor);
      this.Text = "PassiveEditor By kimpobin";
      this.Load += new EventHandler(this.PassiveEditor_Load);
      this.toolStrip1.ResumeLayout(false);
      this.toolStrip1.PerformLayout();
      this.groupBox1.ResumeLayout(false);
      this.groupBox3.ResumeLayout(false);
      this.groupBox3.PerformLayout();
      this.groupBox17.ResumeLayout(false);
      this.groupBox17.PerformLayout();
      this.groupBox13.ResumeLayout(false);
      this.groupBox13.PerformLayout();
      this.groupBox2.ResumeLayout(false);
      this.ResumeLayout(false);
      this.PerformLayout();
    }

    private void rareOptionlodToolStripMenuItem_Click(object sender, EventArgs e)
    {
      this.exportLodHandle.ExportPassiveSystem_V4();
    }

    private void strRareOptionusToolStripMenuItem_Click(object sender, EventArgs e)
    {
      this.exportLodHandle.ExportStringPassive_V4("strPassiveSystem");
    }
  }
}
