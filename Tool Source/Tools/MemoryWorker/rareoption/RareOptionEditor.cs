// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.rareoption.RareOptionEditor
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using LcDevPack_TeamDamonA.Properties;
using MySqlConnector;
using StringExporter;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.rareoption
{
    public class RareOptionEditor : Form
    {


        public RareOptionEditor()
        {
            this.InitializeComponent();
            this.LoadStartUp();
        }
        public static Connection connection = new Connection();
        private static System.Collections.Generic.List<t_rareoption> RareOptionList = new System.Collections.Generic.List<t_rareoption>();
        private string Host = RareOptionEditor.connection.Settings.SqlHost;
        private string User = RareOptionEditor.connection.Settings.SqlUser;
        private string Password = RareOptionEditor.connection.Settings.SqlPassword;
        private string Database = RareOptionEditor.connection.Settings.SqlDatabase;
        private DatabaseHandle databaseHandle = new DatabaseHandle();
        private ExportLodHandle exportLodHandle = new ExportLodHandle();
        public string _ClientPath = LcDevPack_TeamDamonA.Tools.MobEditor.connection.Settings.ClientPath;
        private IContainer components = (IContainer)null;
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
        private string namee;
        public string[] menuArray3 = new string[1] { "a_level" };
        private ToolStrip toolStrip1;
        private ToolStripDropDownButton toolStripDropDownButton1;
        private ToolStripMenuItem exportToolStripMenuItem;
        private ToolStripMenuItem rareOptionlodToolStripMenuItem;
        private ToolStripMenuItem strRareOptionusToolStripMenuItem;
        public bool _ComboBoxLocked = false;
        private GroupBox groupBox1;
        private GroupBox groupBox3;
        private TextBox rstxt;
        private Label label9;
        private ComboBox tdrop;
        private Label label8;
        private ComboBox gdrop;
        private Label label7;
        private TextBox mtktxt;
        private Label label5;
        private TextBox deftxt;
        private Label label4;
        private TextBox atktxt;
        private Label label3;
        private TextBox nametxt;
        private Label label2;
        private TextBox idtxt;
        private Label label1;
        private GroupBox groupBox2;
        private Button UpdateButton;
        private Button remove;
        private ListBox listBox1;
        private Label label6;
        private Label label20;
        private Button button1;
        private PictureBox PbAcc;
        private PictureBox PbArmor;
        private PictureBox PbWeapon;
        private Label LblNote;
        private TextBox TbType;
        private TextBox TbGrade;
        private TextBox TbPercent4;
        private TextBox TbPercent3;
        private TextBox TbPercent2;
        private TextBox TbPercent1;
        private Button btnPercentAddResist;
        private Button btnPercentAddMattk;
        private Button btnPercentAddDef;
        private Button btnPercentAddAttk;
        private Label LblPercent3;
        private Label LblPercent4;
        private Label LblPercent2;
        private Label LblPercent1;
        private TextBox TbSeal7;
        private TextBox TbSeal6;
        private TextBox TbSeal9;
        private TextBox TbSeal8;
        private TextBox TbSeal5;
        private TextBox TbSeal4;
        private TextBox TbSeal3;
        private TextBox TbSeal2;
        private TextBox TbSeal1;
        private GroupBox groupBox13;
        private TextBox textBox79;
        private Label label79;
        private TextBox textBox78;
        private Label label78;
        private TextBox textBox77;
        private Label label77;
        private TextBox textBox76;
        private Label label76;
        private TextBox textBox75;
        private Label label75;
        private TextBox textBox74;
        private Label label74;
        private TextBox textBox73;
        private Label label73;
        private TextBox textBox72;
        private Label label72;
        private TextBox textBox71;
        private Label label71;
        private TextBox textBox70;
        private Label label70;
        private TextBox textBox69;
        private Label label69;
        private TextBox textBox68;
        private Label label68;
        private TextBox textBox67;
        private Label label67;
        private TextBox textBox66;
        private Label label66;
        private TextBox textBox65;
        private Label label65;
        private TextBox textBox64;
        private Label label64;
        private TextBox textBox63;
        private Label label63;
        private TextBox textBox62;
        private Label label62;
        private TextBox textBox61;
        private Label label61;
        private TextBox textBox60;
        private Label label60;
        private GroupBox groupBox17;
        private ComboBox comboBox23;
        private ComboBox comboBox22;
        private ComboBox comboBox21;
        private ComboBox comboBox20;
        private ComboBox comboBox19;
        private ComboBox comboBox18;
        private ComboBox comboBox17;
        private ComboBox comboBox16;
        private ComboBox comboBox15;
        private ComboBox comboBox14;
        private Label label104;
        private ComboBox comboBox13;
        private Label label103;
        private Label label102;
        private Label label101;
        private Label label100;
        private ComboBox comboBox12;
        private ComboBox comboBox11;
        private ComboBox comboBox10;
        private ComboBox comboBox9;
        private ComboBox comboBox8;
        private Label label99;
        private ComboBox comboBox7;
        private Label label98;
        private ComboBox comboBox6;
        private Label label97;
        private ComboBox comboBox5;
        private Label label96;
        private ComboBox comboBox3;
        private Label label95;
        private TextBox TbSeal0;
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
        private TextBox od9;
        private Label label10;
        private TextBox od8;
        private Label label11;
        private TextBox od7;
        private Label label12;
        private TextBox od6;
        private Label label13;
        private TextBox od5;
        private Label label14;
        private TextBox od4;
        private Label label15;
        private TextBox od3;
        private Label label16;
        private TextBox od2;
        private Label label17;
        private TextBox od1;
        private Label label18;
        private TextBox od0;
        private Label label19;
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
                return (string)null;
            this.namee = "a_name_usa";
            return this.namee;
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
                this.namee = this.StringFromLanguage();
                if (string.IsNullOrEmpty(this.namee))
                    this.namee = "a_name"; // fallback if language column not found

                string query = "SELECT a_index, a_type, " + this.namee + " FROM t_option ORDER BY a_index;";

                using (var conn = new MySqlConnection(
                    $"datasource={Host};Port=3306;User ID={User};Password={Password};Database={Database};Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;"))
                using (var cmd = new MySqlCommand(query, conn))
                {
                    conn.Open();
                    using (var reader = cmd.ExecuteReader())
                    {
                        var comboBoxes = new[]
                        {
                    comboBox3, comboBox5, comboBox6, comboBox7, comboBox8,
                    comboBox9, comboBox10, comboBox11, comboBox12, comboBox13
                };

                        foreach (var combo in comboBoxes)
                            combo.Items.Clear();

                        while (reader.Read())
                        {
                            int index = reader.GetInt32("a_index"); // INT field
                            string type = reader["a_type"].ToString(); // works for string or numeric
                            string name = reader[this.namee].ToString();

                            string display = $"{index}: {type} - {name}";
                            foreach (var combo in comboBoxes)
                                combo.Items.Add(display);
                        }

                        foreach (var combo in comboBoxes)
                        {
                            if (combo.Items.Count > 0)
                                combo.SelectedIndex = 0;
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Error while loading options: {ex.Message}",
                    "Database Error",
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error);
            }
        }



        private void comboBox3_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.textBox60.Text = this.comboBox3.SelectedIndex.ToString();
            this.List = this.databaseHandle.SelectMySqlExplodedReturnList(this.menuArray3, this.Host, this.User, this.Password, this.Database, "select * from t_option WHERE a_type = '" + this.textBox60.Text + "' ORDER BY a_index;");
            this.comboBox14.DataSource = (object)null;
            this.comboBox14.Items.Clear();
            this.comboBox14.DataSource = (object)this.List;
            if (!(this.textBox60.Text != "-1"))
                return;
            this.comboBox14.SelectedIndex = Convert.ToInt32(this.textBox70.Text) - 1;
        }

        private void comboBox3_SelectionChangeCommitted(object sender, EventArgs e)
        {
            this.comboBox3.BackColor = Color.Pink;
        }

        private void comboBox5_SelectionChangeCommitted(object sender, EventArgs e)
        {
            this.comboBox5.BackColor = Color.Pink;
        }

        private void comboBox6_SelectionChangeCommitted(object sender, EventArgs e)
        {
            this.comboBox6.BackColor = Color.Pink;
        }

        private void comboBox7_SelectionChangeCommitted(object sender, EventArgs e)
        {
            this.comboBox7.BackColor = Color.Pink;
        }

        private void comboBox8_SelectionChangeCommitted(object sender, EventArgs e)
        {
            this.comboBox8.BackColor = Color.Pink;
        }

        private void comboBox9_SelectionChangeCommitted(object sender, EventArgs e)
        {
            this.comboBox9.BackColor = Color.Pink;
        }

        private void comboBox10_SelectionChangeCommitted(object sender, EventArgs e)
        {
            this.comboBox10.BackColor = Color.Pink;
        }

        private void comboBox11_SelectionChangeCommitted(object sender, EventArgs e)
        {
            this.comboBox11.BackColor = Color.Pink;
        }

        private void comboBox12_SelectionChangeCommitted(object sender, EventArgs e)
        {
            this.comboBox12.BackColor = Color.Pink;
        }

        private void comboBox13_SelectionChangeCommitted(object sender, EventArgs e)
        {
            this.comboBox13.BackColor = Color.Pink;
        }

        private void comboBox14_SelectionChangeCommitted(object sender, EventArgs e)
        {
            this.comboBox14.BackColor = Color.Pink;
        }

        private void comboBox15_SelectionChangeCommitted(object sender, EventArgs e)
        {
            this.comboBox15.BackColor = Color.Pink;
        }

        private void comboBox16_SelectionChangeCommitted(object sender, EventArgs e)
        {
            this.comboBox16.BackColor = Color.Pink;
        }

        private void comboBox17_SelectionChangeCommitted(object sender, EventArgs e)
        {
            this.comboBox17.BackColor = Color.Pink;
        }

        private void comboBox18_SelectionChangeCommitted(object sender, EventArgs e)
        {
            this.comboBox18.BackColor = Color.Pink;
        }

        private void comboBox19_SelectionChangeCommitted(object sender, EventArgs e)
        {
            this.comboBox19.BackColor = Color.Pink;
        }

        private void comboBox20_SelectionChangeCommitted(object sender, EventArgs e)
        {
            this.comboBox20.BackColor = Color.Pink;
        }

        private void comboBox21_SelectionChangeCommitted(object sender, EventArgs e)
        {
            this.comboBox21.BackColor = Color.Pink;
        }

        private void comboBox22_SelectionChangeCommitted(object sender, EventArgs e)
        {
            this.comboBox22.BackColor = Color.Pink;
        }

        private void comboBox23_SelectionChangeCommitted(object sender, EventArgs e)
        {
            this.comboBox23.BackColor = Color.Pink;
        }

        private void comboBox5_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.textBox61.Text = this.comboBox5.SelectedIndex.ToString();
            this.List2 = this.databaseHandle.SelectMySqlExplodedReturnList(this.menuArray3, this.Host, this.User, this.Password, this.Database, "select * from t_option WHERE a_type = '" + this.textBox61.Text + "' ORDER BY a_index;");
            this.comboBox15.DataSource = (object)null;
            this.comboBox15.Items.Clear();
            this.comboBox15.DataSource = (object)this.List2;
            if (!(this.textBox61.Text != "-1"))
                return;
            this.comboBox15.SelectedIndex = Convert.ToInt32(this.textBox71.Text) - 1;
        }

        private void comboBox6_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.textBox62.Text = this.comboBox6.SelectedIndex.ToString();
            this.List3 = this.databaseHandle.SelectMySqlExplodedReturnList(this.menuArray3, this.Host, this.User, this.Password, this.Database, "select * from t_option WHERE a_type = '" + this.textBox62.Text + "' ORDER BY a_index;");
            this.comboBox16.DataSource = (object)null;
            this.comboBox16.Items.Clear();
            this.comboBox16.DataSource = (object)this.List3;
            if (!(this.textBox62.Text != "-1"))
                return;
            this.comboBox16.SelectedIndex = Convert.ToInt32(this.textBox72.Text) - 1;
        }

        private void comboBox7_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.textBox63.Text = this.comboBox7.SelectedIndex.ToString();
            this.List4 = this.databaseHandle.SelectMySqlExplodedReturnList(this.menuArray3, this.Host, this.User, this.Password, this.Database, "select * from t_option WHERE a_type = '" + this.textBox63.Text + "' ORDER BY a_index;");
            this.comboBox17.DataSource = (object)null;
            this.comboBox17.Items.Clear();
            this.comboBox17.DataSource = (object)this.List4;
            if (!(this.textBox63.Text != "-1"))
                return;
            this.comboBox17.SelectedIndex = Convert.ToInt32(this.textBox73.Text) - 1;
        }

        private void comboBox8_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.textBox64.Text = this.comboBox8.SelectedIndex.ToString();
            this.List5 = this.databaseHandle.SelectMySqlExplodedReturnList(this.menuArray3, this.Host, this.User, this.Password, this.Database, "select * from t_option WHERE a_type = '" + this.textBox64.Text + "' ORDER BY a_index;");
            this.comboBox18.DataSource = (object)null;
            this.comboBox18.Items.Clear();
            this.comboBox18.DataSource = (object)this.List5;
            if (!(this.textBox64.Text != "-1"))
                return;
            this.comboBox18.SelectedIndex = Convert.ToInt32(this.textBox74.Text) - 1;
        }

        private void comboBox9_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.textBox65.Text = this.comboBox9.SelectedIndex.ToString();
            this.List6 = this.databaseHandle.SelectMySqlExplodedReturnList(this.menuArray3, this.Host, this.User, this.Password, this.Database, "select * from t_option WHERE a_type = '" + this.textBox65.Text + "' ORDER BY a_index;");
            this.comboBox19.DataSource = (object)null;
            this.comboBox19.Items.Clear();
            this.comboBox19.DataSource = (object)this.List6;
            if (!(this.textBox65.Text != "-1"))
                return;
            this.comboBox19.SelectedIndex = Convert.ToInt32(this.textBox75.Text) - 1;
        }

        private void comboBox10_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.textBox66.Text = this.comboBox10.SelectedIndex.ToString();
            this.List7 = this.databaseHandle.SelectMySqlExplodedReturnList(this.menuArray3, this.Host, this.User, this.Password, this.Database, "select * from t_option WHERE a_type = '" + this.textBox66.Text + "' ORDER BY a_index;");
            this.comboBox20.DataSource = (object)null;
            this.comboBox20.Items.Clear();
            this.comboBox20.DataSource = (object)this.List7;
            if (!(this.textBox66.Text != "-1"))
                return;
            this.comboBox20.SelectedIndex = Convert.ToInt32(this.textBox76.Text) - 1;
        }

        private void comboBox11_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.textBox67.Text = this.comboBox11.SelectedIndex.ToString();
            this.List8 = this.databaseHandle.SelectMySqlExplodedReturnList(this.menuArray3, this.Host, this.User, this.Password, this.Database, "select * from t_option WHERE a_type = '" + this.textBox67.Text + "' ORDER BY a_index;");
            this.comboBox21.DataSource = (object)null;
            this.comboBox21.Items.Clear();
            this.comboBox21.DataSource = (object)this.List8;
            if (!(this.textBox67.Text != "-1"))
                return;
            this.comboBox21.SelectedIndex = Convert.ToInt32(this.textBox76.Text) - 1;
        }

        private void comboBox12_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.textBox68.Text = this.comboBox12.SelectedIndex.ToString();
            this.List9 = this.databaseHandle.SelectMySqlExplodedReturnList(this.menuArray3, this.Host, this.User, this.Password, this.Database, "select * from t_option WHERE a_type = '" + this.textBox68.Text + "' ORDER BY a_index;");
            this.comboBox22.DataSource = (object)null;
            this.comboBox22.Items.Clear();
            this.comboBox22.DataSource = (object)this.List9;
            if (!(this.textBox68.Text != "-1"))
                return;
            this.comboBox22.SelectedIndex = Convert.ToInt32(this.textBox78.Text) - 1;
        }

        private void comboBox13_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.textBox69.Text = this.comboBox13.SelectedIndex.ToString();
            this.List10 = this.databaseHandle.SelectMySqlExplodedReturnList(this.menuArray3, this.Host, this.User, this.Password, this.Database, "select * from t_option WHERE a_type = '" + this.textBox69.Text + "' ORDER BY a_index;");
            this.comboBox23.DataSource = (object)null;
            this.comboBox23.Items.Clear();
            this.comboBox23.DataSource = (object)this.List10;
            if (!(this.textBox69.Text != "-1"))
                return;
            this.comboBox23.SelectedIndex = Convert.ToInt32(this.textBox79.Text) - 1;
        }

        private void comboBox14_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (this._ComboBoxLocked)
                return;
            this.textBox70.Text = (this.comboBox14.SelectedIndex + 1).ToString();
        }

        private void comboBox15_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (this._ComboBoxLocked)
                return;
            this.textBox71.Text = (this.comboBox15.SelectedIndex + 1).ToString();
        }

        private void comboBox16_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (this._ComboBoxLocked)
                return;
            this.textBox72.Text = (this.comboBox16.SelectedIndex + 1).ToString();
        }

        private void comboBox17_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (this._ComboBoxLocked)
                return;
            this.textBox73.Text = (this.comboBox17.SelectedIndex + 1).ToString();
        }

        private void comboBox18_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (this._ComboBoxLocked)
                return;
            this.textBox74.Text = (this.comboBox18.SelectedIndex + 1).ToString();
        }

        private void comboBox19_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (this._ComboBoxLocked)
                return;
            this.textBox75.Text = (this.comboBox19.SelectedIndex + 1).ToString();
        }

        private void comboBox20_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (this._ComboBoxLocked)
                return;
            this.textBox76.Text = (this.comboBox20.SelectedIndex + 1).ToString();
        }

        private void comboBox21_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (this._ComboBoxLocked)
                return;
            this.textBox77.Text = (this.comboBox21.SelectedIndex + 1).ToString();
        }

        private void comboBox22_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (this._ComboBoxLocked)
                return;
            this.textBox78.Text = (this.comboBox22.SelectedIndex + 1).ToString();
        }

        private void comboBox23_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (this._ComboBoxLocked)
                return;
            this.textBox79.Text = (this.comboBox23.SelectedIndex + 1).ToString();
        }

        private void textBox70_KeyPress(object sender, KeyPressEventArgs e)
        {
            this.textBox70.BackColor = Color.Pink;
        }

        private void textBox71_KeyPress(object sender, KeyPressEventArgs e)
        {
            this.textBox71.BackColor = Color.Pink;
        }

        private void textBox72_KeyPress(object sender, KeyPressEventArgs e)
        {
            this.textBox72.BackColor = Color.Pink;
        }

        private void textBox73_KeyPress(object sender, KeyPressEventArgs e)
        {
            this.textBox73.BackColor = Color.Pink;
        }

        private void textBox74_KeyPress(object sender, KeyPressEventArgs e)
        {
            this.textBox74.BackColor = Color.Pink;
        }

        private void textBox75_KeyPress(object sender, KeyPressEventArgs e)
        {
            this.textBox75.BackColor = Color.Pink;
        }

        private void textBox76_KeyPress(object sender, KeyPressEventArgs e)
        {
            this.textBox76.BackColor = Color.Pink;
        }

        private void textBox77_KeyPress(object sender, KeyPressEventArgs e)
        {
            this.textBox77.BackColor = Color.Pink;
        }

        private void textBox78_KeyPress(object sender, KeyPressEventArgs e)
        {
            this.textBox78.BackColor = Color.Pink;
        }

        private void textBox79_KeyPress(object sender, KeyPressEventArgs e)
        {
            this.textBox79.BackColor = Color.Pink;
        }

        private void ClearComboBoxPurple2()
        {
            this.comboBox14.SelectedIndex = -1;
            this.comboBox15.SelectedIndex = -1;
            this.comboBox16.SelectedIndex = -1;
            this.comboBox17.SelectedIndex = -1;
            this.comboBox18.SelectedIndex = -1;
            this.comboBox19.SelectedIndex = -1;
            this.comboBox20.SelectedIndex = -1;
            this.comboBox21.SelectedIndex = -1;
            this.comboBox22.SelectedIndex = -1;
            this.comboBox23.SelectedIndex = -1;
        }

        private void ClearComboBoxPurple()
        {
            this.comboBox3.SelectedIndex = -1;
            this.comboBox5.SelectedIndex = -1;
            this.comboBox6.SelectedIndex = -1;
            this.comboBox7.SelectedIndex = -1;
            this.comboBox8.SelectedIndex = -1;
            this.comboBox9.SelectedIndex = -1;
            this.comboBox10.SelectedIndex = -1;
            this.comboBox11.SelectedIndex = -1;
            this.comboBox12.SelectedIndex = -1;
            this.comboBox13.SelectedIndex = -1;
        }

        private void ResetComboBoxPurpleBg()
        {
            this.comboBox3.BackColor = Color.White;
            this.comboBox5.BackColor = Color.White;
            this.comboBox6.BackColor = Color.White;
            this.comboBox7.BackColor = Color.White;
            this.comboBox8.BackColor = Color.White;
            this.comboBox9.BackColor = Color.White;
            this.comboBox10.BackColor = Color.White;
            this.comboBox11.BackColor = Color.White;
            this.comboBox12.BackColor = Color.White;
            this.comboBox13.BackColor = Color.White;
            this.comboBox14.BackColor = Color.White;
            this.comboBox15.BackColor = Color.White;
            this.comboBox16.BackColor = Color.White;
            this.comboBox17.BackColor = Color.White;
            this.comboBox18.BackColor = Color.White;
            this.comboBox19.BackColor = Color.White;
            this.comboBox20.BackColor = Color.White;
            this.comboBox21.BackColor = Color.White;
            this.comboBox22.BackColor = Color.White;
            this.comboBox23.BackColor = Color.White;
        }

        private void Fill_listbox()
        {
            try
            {
                // Determine language column name
                this.namee = this.StringFromLanguage();
                if (string.IsNullOrEmpty(this.namee))
                    this.namee = "a_name"; // Fallback if language not found

                // Prepare SQL connection
                string connectionString = $"datasource={this.Host};port=3306;username={this.User};password={this.Password};database={this.Database};Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;";
                string cmdText = "SELECT a_index, " + this.namee + " FROM t_rareoption ORDER BY a_index ASC;";

                using (var connection = new MySqlConnection(connectionString))
                using (var command = new MySqlCommand(cmdText, connection))
                {
                    connection.Open();
                    using (var reader = command.ExecuteReader())
                    {
                        listBox1.Items.Clear();

                        while (reader.Read())
                        {
                            // Safely read index (numeric field)
                            int index = reader.GetInt32("a_index");

                            // Safely read localized name
                            string name = reader[this.namee].ToString();

                            listBox1.Items.Add($"{index} - {name}");
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Error loading rare options:\n{ex.Message}", "Database Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }


        private void Fill_listbox2()
        {
            try
            {
                // Clear previous items and data
                listBox1.DataSource = null;
                listBox1.Items.Clear();
                listBox1.SelectedIndex = -1;
                MenuList.Clear();

                string query = "SELECT a_index, " + this.StringFromLanguage() + " FROM t_rareoption ORDER BY a_index ASC;";
                string connStr = $"datasource={Host};port=3306;username={User};password={Password};database={Database};Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;";

                using (var conn = new MySqlConnection(connStr))
                using (var cmd = new MySqlCommand(query, conn))
                {
                    conn.Open();
                    using (var reader = cmd.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            int index = reader.GetInt32("a_index");
                            string name = reader[this.StringFromLanguage()].ToString();

                            // Combine index + name
                            MenuList.Add($"{index} - {name}");
                        }
                    }
                }

                // Apply the same list to ListBox
                listBox1.DataSource = new List<string>(MenuList);

                // No selection by default
                listBox1.SelectedIndex = -1;
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Error loading rare options:\n{ex.Message}", "Database Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }


        private void RestTextBoxField()
        {
            this.TbPercent1.Text = "";
            this.TbPercent2.Text = "";
            this.TbPercent3.Text = "";
            this.TbPercent4.Text = "";
            this.idtxt.BackColor = Color.White;
            this.nametxt.BackColor = Color.White;
            this.gdrop.BackColor = Color.White;
            this.tdrop.BackColor = Color.White;
            this.atktxt.BackColor = Color.White;
            this.mtktxt.BackColor = Color.White;
            this.rstxt.BackColor = Color.White;
            this.deftxt.BackColor = Color.White;
            this.TbPercent1.BackColor = Color.White;
            this.TbPercent2.BackColor = Color.White;
            this.TbPercent3.BackColor = Color.White;
            this.TbPercent4.BackColor = Color.White;
        }

        private void ListBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.namee = this.StringFromLanguage();
            string connectionString =
                $"Server={Host};Port=3306;User ID={User};Password={Password};Database={Database};" +
                "SslMode=Preferred;TlsVersion=Tls12;";
            string cmdText = "select * FROM t_rareoption WHERE a_index ='" + this.listBox1.Text + "';";
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
                    string str2 = mySqlDataReader.GetString(this.namee ?? "");
                    int32 = mySqlDataReader.GetInt32("a_attack");
                    string str3 = int32.ToString();
                    int32 = mySqlDataReader.GetInt32("a_defense");
                    string str4 = int32.ToString();
                    int32 = mySqlDataReader.GetInt32("a_magic");
                    string str5 = int32.ToString();
                    int32 = mySqlDataReader.GetInt32("a_resist");
                    string str6 = int32.ToString();
                    int32 = mySqlDataReader.GetInt32("a_grade");
                    string str7 = int32.ToString();
                    this.gdrop.SelectedIndex = Convert.ToInt32(str7);
                    int32 = mySqlDataReader.GetInt32("a_type");
                    string str8 = int32.ToString();
                    this.tdrop.SelectedIndex = Convert.ToInt32(str8);
                    int32 = mySqlDataReader.GetInt32("a_option_index0");
                    string str9 = int32.ToString();
                    int32 = mySqlDataReader.GetInt32("a_option_index1");
                    string str10 = int32.ToString();
                    int32 = mySqlDataReader.GetInt32("a_option_index2");
                    string str11 = int32.ToString();
                    int32 = mySqlDataReader.GetInt32("a_option_index3");
                    string str12 = int32.ToString();
                    int32 = mySqlDataReader.GetInt32("a_option_index4");
                    string str13 = int32.ToString();
                    int32 = mySqlDataReader.GetInt32("a_option_index5");
                    string str14 = int32.ToString();
                    int32 = mySqlDataReader.GetInt32("a_option_index6");
                    string str15 = int32.ToString();
                    int32 = mySqlDataReader.GetInt32("a_option_index7");
                    string str16 = int32.ToString();
                    int32 = mySqlDataReader.GetInt32("a_option_index8");
                    string str17 = int32.ToString();
                    int32 = mySqlDataReader.GetInt32("a_option_index9");
                    string str18 = int32.ToString();
                    int32 = mySqlDataReader.GetInt32("a_option_level0");
                    string str19 = int32.ToString();
                    int32 = mySqlDataReader.GetInt32("a_option_level1");
                    string str20 = int32.ToString();
                    int32 = mySqlDataReader.GetInt32("a_option_level2");
                    string str21 = int32.ToString();
                    int32 = mySqlDataReader.GetInt32("a_option_level3");
                    string str22 = int32.ToString();
                    int32 = mySqlDataReader.GetInt32("a_option_level4");
                    string str23 = int32.ToString();
                    int32 = mySqlDataReader.GetInt32("a_option_level5");
                    string str24 = int32.ToString();
                    int32 = mySqlDataReader.GetInt32("a_option_level6");
                    string str25 = int32.ToString();
                    int32 = mySqlDataReader.GetInt32("a_option_level7");
                    string str26 = int32.ToString();
                    int32 = mySqlDataReader.GetInt32("a_option_level8");
                    string str27 = int32.ToString();
                    int32 = mySqlDataReader.GetInt32("a_option_level9");
                    string str28 = int32.ToString();
                    int32 = mySqlDataReader.GetInt32("a_option_prob0");
                    string str29 = int32.ToString();
                    int32 = mySqlDataReader.GetInt32("a_option_prob1");
                    string str30 = int32.ToString();
                    int32 = mySqlDataReader.GetInt32("a_option_prob2");
                    string str31 = int32.ToString();
                    int32 = mySqlDataReader.GetInt32("a_option_prob3");
                    string str32 = int32.ToString();
                    int32 = mySqlDataReader.GetInt32("a_option_prob4");
                    string str33 = int32.ToString();
                    int32 = mySqlDataReader.GetInt32("a_option_prob5");
                    string str34 = int32.ToString();
                    int32 = mySqlDataReader.GetInt32("a_option_prob6");
                    string str35 = int32.ToString();
                    int32 = mySqlDataReader.GetInt32("a_option_prob7");
                    string str36 = int32.ToString();
                    int32 = mySqlDataReader.GetInt32("a_option_prob8");
                    string str37 = int32.ToString();
                    int32 = mySqlDataReader.GetInt32("a_option_prob9");
                    string str38 = int32.ToString();
                    this.RestTextBoxField();
                    this.idtxt.Text = str1;
                    this.nametxt.Text = str2;
                    this.atktxt.Text = str3;
                    this.deftxt.Text = str4;
                    this.mtktxt.Text = str5;
                    this.rstxt.Text = str6;
                    this.TbGrade.Text = str7;
                    this.TbType.Text = str8;
                    this.od0.Text = str29;
                    this.od1.Text = str30;
                    this.od2.Text = str31;
                    this.od3.Text = str32;
                    this.od4.Text = str33;
                    this.od5.Text = str34;
                    this.od6.Text = str35;
                    this.od7.Text = str36;
                    this.od8.Text = str37;
                    this.od9.Text = str38;
                    if (this.TbType.Text == "0")
                    {
                        this.PbWeapon.BackColor = Color.LimeGreen;
                        this.PbArmor.BackColor = Control.DefaultBackColor;
                        this.PbAcc.BackColor = Control.DefaultBackColor;
                    }
                    else if (this.TbType.Text == "1")
                    {
                        this.PbArmor.BackColor = Color.LimeGreen;
                        this.PbWeapon.BackColor = Control.DefaultBackColor;
                        this.PbAcc.BackColor = Control.DefaultBackColor;
                    }
                    else if (this.TbType.Text == "2")
                    {
                        this.PbAcc.BackColor = Color.LimeGreen;
                        this.PbArmor.BackColor = Control.DefaultBackColor;
                        this.PbWeapon.BackColor = Control.DefaultBackColor;
                    }
                    this.textBox60.Text = str9;
                    this.comboBox3.SelectedIndex = Convert.ToInt32(str9);
                    this.textBox61.Text = str10;
                    this.comboBox5.SelectedIndex = Convert.ToInt32(str10);
                    this.textBox62.Text = str11;
                    this.comboBox6.SelectedIndex = Convert.ToInt32(str11);
                    this.textBox63.Text = str12;
                    this.comboBox7.SelectedIndex = Convert.ToInt32(str12);
                    this.textBox64.Text = str13;
                    this.comboBox8.SelectedIndex = Convert.ToInt32(str13);
                    this.textBox65.Text = str14;
                    this.comboBox9.SelectedIndex = Convert.ToInt32(str14);
                    this.textBox66.Text = str15;
                    this.comboBox10.SelectedIndex = Convert.ToInt32(str15);
                    this.textBox67.Text = str16;
                    this.comboBox11.SelectedIndex = Convert.ToInt32(str16);
                    this.textBox68.Text = str17;
                    this.comboBox12.SelectedIndex = Convert.ToInt32(str17);
                    this.textBox69.Text = str18;
                    this.comboBox13.SelectedIndex = Convert.ToInt32(str18);
                    this.textBox70.Text = str19;
                    this.comboBox14.SelectedIndex = Convert.ToInt32(str19) - 1;
                    this.textBox71.Text = str20;
                    this.comboBox15.SelectedIndex = Convert.ToInt32(str20) - 1;
                    this.textBox72.Text = str21;
                    this.comboBox16.SelectedIndex = Convert.ToInt32(str21) - 1;
                    this.textBox73.Text = str22;
                    this.comboBox17.SelectedIndex = Convert.ToInt32(str22) - 1;
                    this.textBox74.Text = str23;
                    this.comboBox18.SelectedIndex = Convert.ToInt32(str23) - 1;
                    this.textBox75.Text = str24;
                    this.comboBox19.SelectedIndex = Convert.ToInt32(str24) - 1;
                    this.textBox76.Text = str25;
                    this.comboBox20.SelectedIndex = Convert.ToInt32(str25) - 1;
                    this.textBox77.Text = str26;
                    this.comboBox21.SelectedIndex = Convert.ToInt32(str26) - 1;
                    this.textBox78.Text = str27;
                    this.comboBox22.SelectedIndex = Convert.ToInt32(str27) - 1;
                    this.textBox79.Text = str28;
                    this.comboBox23.SelectedIndex = Convert.ToInt32(str28) - 1;
                }
            }
            catch (Exception ex)
            {
                int num = (int)MessageBox.Show(ex.Message);
            }
            connection.Close();
        }

        private void UpdateButton_Click(object sender, EventArgs e)
        {
            int selectedIndex = this.listBox1.SelectedIndex;
            if (MessageBox.Show("Do you want to Change Rare Option " + this.idtxt.Text.Trim() + " - " + this.nametxt.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
                return;
            this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_rareoption SET a_index = '" + this.idtxt.Text + "', " + this.namee + " = '" + this.nametxt.Text + "', a_grade = '" + this.TbGrade.Text + "', a_type = '" + this.TbType.Text + "', a_attack = '" + this.atktxt.Text + "', a_defense = '" + this.deftxt.Text + "', a_magic = '" + this.mtktxt.Text + "', a_resist = '" + this.rstxt.Text + "', a_option_index0 = '" + this.textBox60.Text + "', a_option_index1 = '" + this.textBox61.Text + "', a_option_index2 = '" + this.textBox62.Text + "', a_option_index3 = '" + this.textBox63.Text + "', a_option_index4 = '" + this.textBox64.Text + "', a_option_index5 = '" + this.textBox65.Text + "', a_option_index6 = '" + this.textBox66.Text + "', a_option_index7 = '" + this.textBox67.Text + "', a_option_index8 = '" + this.textBox68.Text + "', a_option_index9 = '" + this.textBox69.Text + "', a_option_level0 = '" + this.textBox70.Text + "', a_option_level1 = '" + this.textBox71.Text + "', a_option_level2 = '" + this.textBox72.Text + "', a_option_level3 = '" + this.textBox73.Text + "', a_option_level4 = '" + this.textBox74.Text + "', a_option_level5 = '" + this.textBox75.Text + "', a_option_level6 = '" + this.textBox76.Text + "', a_option_level7 = '" + this.textBox77.Text + "', a_option_level8 = '" + this.textBox78.Text + "', a_option_level9 = '" + this.textBox79.Text + "', a_option_prob0 = '" + this.od0.Text + "', a_option_prob1 = '" + this.od1.Text + "', a_option_prob2 = '" + this.od2.Text + "', a_option_prob3 = '" + this.od3.Text + "', a_option_prob4 = '" + this.od4.Text + "', a_option_prob5 = '" + this.od5.Text + "', a_option_prob6 = '" + this.od6.Text + "', a_option_prob7 = '" + this.od7.Text + "', a_option_prob8 = '" + this.od8.Text + "', a_option_prob9 = '" + this.od9.Text + "' WHERE a_index = '" + this.idtxt.Text + "'");
            this.Fill_listbox2();
            this.listBox1.SelectedIndex = selectedIndex;
            this.ResetComboBoxPurpleBg();
            int num = (int)new CustomMessage("Update Done :)").ShowDialog();
        }

        private void Remove_Click(object sender, EventArgs e)
        {
            int selectedIndex = this.listBox1.SelectedIndex;
            if (MessageBox.Show("Do you want to Delete Rare Option " + this.idtxt.Text.Trim() + " - " + this.nametxt.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
                return;
            this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_rareoption WHERE a_index = '" + this.idtxt.Text + "'");
            this.Fill_listbox2();
            this.listBox1.SelectedIndex = this.listBox1.Items.Count - 1;
            this.ResetComboBoxPurpleBg();
            int num = (int)new CustomMessage("Deleted :O").ShowDialog();
        }

        private void Button1_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show("Do you want to Add New Rare Option From " + this.idtxt.Text.Trim() + " - " + this.nametxt.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
                return;
            this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DROP TABLE IF EXISTS tempTable;CREATE TEMPORARY TABLE tempTable ENGINE=MEMORY SELECT * FROM t_rareoption WHERE a_index=" + this.idtxt.Text + ";SELECT a_index FROM tempTable;UPDATE tempTable SET a_index=(SELECT a_index from t_rareoption ORDER BY a_index DESC LIMIT 1)+1; SELECT a_index FROM tempTable;INSERT INTO t_rareoption SELECT * FROM tempTable;");
            this.Fill_listbox2();
            this.listBox1.SelectedIndex = this.listBox1.Items.Count - 1;
            int num = (int)new CustomMessage("Copying Complete").ShowDialog();
            this.idtxt.BackColor = Color.Lime;
            this.nametxt.BackColor = Color.Lime;
            this.ResetComboBoxPurpleBg();
        }

        private void RareOptionEditor_Load(object sender, EventArgs e)
        {
            this.Fill_listbox();
            this.gdrop.Items.AddRange(new object[5]
            {
        (object) "0 - Blue",
        (object) "1 - Green",
        (object) "2 - Yellow",
        (object) "3 - White bonus",
        (object) "4 - White"
            });
            this.tdrop.Items.AddRange(new object[3]
            {
        (object) "0 - Weapon",
        (object) "1 - Armor",
        (object) "2 - Accessory"
            });
            this.listBox1.SelectedIndex = -1;
        }

        private void Gdrop_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.TbGrade.Text = this.GetIndexByComboBox(this.gdrop.Text).ToString();
        }

        private void Tdrop_SelectedIndexChanged(object sender, EventArgs e)
        {
            this.TbType.Text = this.GetIndexByComboBox(this.tdrop.Text).ToString();
        }

        private void PbWeapon_Click(object sender, EventArgs e)
        {
            this.TbType.Text = Convert.ToString(0);
            this.tdrop.SelectedIndex = 0;
            if (this.PbAcc.BackColor == Color.LimeGreen || this.PbArmor.BackColor == Color.LimeGreen)
            {
                this.PbAcc.BackColor = Control.DefaultBackColor;
                this.PbArmor.BackColor = Control.DefaultBackColor;
            }
            this.PbWeapon.BackColor = Color.LimeGreen;
        }

        private void PbArmor_Click(object sender, EventArgs e)
        {
            this.TbType.Text = Convert.ToString(1);
            this.tdrop.SelectedIndex = 1;
            if (this.PbWeapon.BackColor == Color.LimeGreen || this.PbAcc.BackColor == Color.LimeGreen)
            {
                this.PbWeapon.BackColor = Control.DefaultBackColor;
                this.PbAcc.BackColor = Control.DefaultBackColor;
            }
            this.PbArmor.BackColor = Color.LimeGreen;
        }

        private void PbAcc_Click(object sender, EventArgs e)
        {
            this.TbType.Text = Convert.ToString(2);
            this.tdrop.SelectedIndex = 2;
            if (this.PbWeapon.BackColor == Color.LimeGreen || this.PbArmor.BackColor == Color.LimeGreen)
            {
                this.PbWeapon.BackColor = Control.DefaultBackColor;
                this.PbArmor.BackColor = Control.DefaultBackColor;
            }
            this.PbAcc.BackColor = Color.LimeGreen;
        }

        private void BtnPercentAddAttk_Click(object sender, EventArgs e)
        {
            if (this.atktxt.Text != "0")
            {
                try
                {
                    int result1 = 0;
                    float result2 = 0.0f;
                    if (!int.TryParse(this.atktxt.Text, out result1) || !float.TryParse(this.TbPercent1.Text.Replace('.', ','), out result2))
                        return;
                    this.atktxt.Text = ((int)((double)result1 / 100.0 * (double)result2) + result1).ToString();
                }
                catch (Exception ex)
                {
                }
            }
            else
            {
                if (!(this.atktxt.Text == "0"))
                    return;
                int num = (int)MessageBox.Show("Please edit the attack value first");
            }
        }

        private void BtnPercentAddDef_Click(object sender, EventArgs e)
        {
            if (this.deftxt.Text != "0")
            {
                try
                {
                    int result1 = 0;
                    float result2 = 0.0f;
                    if (!int.TryParse(this.deftxt.Text, out result1) || !float.TryParse(this.TbPercent2.Text.Replace('.', ','), out result2))
                        return;
                    this.deftxt.Text = ((int)((double)result1 / 100.0 * (double)result2) + result1).ToString();
                }
                catch (Exception ex)
                {
                }
            }
            else
            {
                if (!(this.deftxt.Text == "0"))
                    return;
                int num = (int)MessageBox.Show("Please edit the defence value first");
            }
        }

        private void BtnPercentAddMattk_Click(object sender, EventArgs e)
        {
            if (this.mtktxt.Text != "0")
            {
                try
                {
                    int result1 = 0;
                    float result2 = 0.0f;
                    if (!int.TryParse(this.mtktxt.Text, out result1) || !float.TryParse(this.TbPercent3.Text.Replace('.', ','), out result2))
                        return;
                    this.mtktxt.Text = ((int)((double)result1 / 100.0 * (double)result2) + result1).ToString();
                }
                catch (Exception ex)
                {
                }
            }
            else
            {
                if (!(this.mtktxt.Text == "0"))
                    return;
                int num = (int)MessageBox.Show("Please edit the magic attack value first");
            }
        }

        private void BtnPercentAddResist_Click(object sender, EventArgs e)
        {
            if (this.rstxt.Text != "0")
            {
                try
                {
                    int result1 = 0;
                    float result2 = 0.0f;
                    if (!int.TryParse(this.rstxt.Text, out result1) || !float.TryParse(this.TbPercent4.Text.Replace('.', ','), out result2))
                        return;
                    this.rstxt.Text = ((int)((double)result1 / 100.0 * (double)result2) + result1).ToString();
                }
                catch (Exception ex)
                {
                }
            }
            else
            {
                if (!(this.rstxt.Text == "0"))
                    return;
                int num = (int)MessageBox.Show("Please edit the magic defence value first");
            }
        }

        private void Atktxt_KeyPress(object sender, KeyPressEventArgs e)
        {
            this.atktxt.BackColor = Color.Pink;
        }

        private void Deftxt_KeyPress(object sender, KeyPressEventArgs e)
        {
            this.deftxt.BackColor = Color.Pink;
        }

        private void Mtktxt_KeyPress(object sender, KeyPressEventArgs e)
        {
            this.mtktxt.BackColor = Color.Pink;
        }

        private void Rstxt_KeyPress(object sender, KeyPressEventArgs e)
        {
            this.rstxt.BackColor = Color.Pink;
        }

        private void Nametxt_KeyPress(object sender, KeyPressEventArgs e)
        {
            this.nametxt.BackColor = Color.Pink;
        }

        private void Idtxt_KeyPress(object sender, KeyPressEventArgs e)
        {
            this.idtxt.BackColor = Color.Pink;
        }

        private void Gdrop_KeyPress(object sender, KeyPressEventArgs e)
        {
            this.gdrop.BackColor = Color.Pink;
        }

        private void Tdrop_KeyPress(object sender, KeyPressEventArgs e)
        {
            this.tdrop.BackColor = Color.Pink;
        }

        private void TbPercent1_KeyPress(object sender, KeyPressEventArgs e)
        {
            this.TbPercent1.BackColor = Color.Pink;
        }

        private void TbPercent2_KeyPress(object sender, KeyPressEventArgs e)
        {
            this.TbPercent2.BackColor = Color.Pink;
        }

        private void TbPercent3_KeyPress(object sender, KeyPressEventArgs e)
        {
            this.TbPercent3.BackColor = Color.Pink;
        }

        private void TbPercent4_KeyPress(object sender, KeyPressEventArgs e)
        {
            this.TbPercent4.BackColor = Color.Pink;
        }

        private void TbType_TextChanged(object sender, EventArgs e)
        {
            int int16 = (int)Convert.ToInt16(this.TbType.Text);
            if (int16 < 0 || int16 > 2)
            {
                int num = (int)MessageBox.Show("Error Type Value Not Within Range ");
            }
            else
            {
                if (int16 != 0 && int16 != 1 && int16 != 2)
                    return;
                switch (int16)
                {
                    case 0:
                        this.PbWeapon.BackColor = Color.LimeGreen;
                        this.PbArmor.BackColor = Control.DefaultBackColor;
                        this.PbAcc.BackColor = Control.DefaultBackColor;
                        break;
                    case 1:
                        this.PbArmor.BackColor = Color.LimeGreen;
                        this.PbWeapon.BackColor = Control.DefaultBackColor;
                        this.PbAcc.BackColor = Control.DefaultBackColor;
                        break;
                    case 2:
                        this.PbAcc.BackColor = Color.LimeGreen;
                        this.PbWeapon.BackColor = Control.DefaultBackColor;
                        this.PbArmor.BackColor = Control.DefaultBackColor;
                        break;
                }
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
            ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof(RareOptionEditor));
            this.toolStrip1 = new ToolStrip();
            this.toolStripDropDownButton1 = new ToolStripDropDownButton();
            this.exportToolStripMenuItem = new ToolStripMenuItem();
            this.rareOptionlodToolStripMenuItem = new ToolStripMenuItem();
            this.strRareOptionusToolStripMenuItem = new ToolStripMenuItem();
            this.groupBox1 = new GroupBox();
            this.groupBox17 = new GroupBox();
            this.comboBox23 = new ComboBox();
            this.comboBox22 = new ComboBox();
            this.comboBox21 = new ComboBox();
            this.comboBox20 = new ComboBox();
            this.comboBox19 = new ComboBox();
            this.comboBox18 = new ComboBox();
            this.comboBox17 = new ComboBox();
            this.comboBox16 = new ComboBox();
            this.comboBox15 = new ComboBox();
            this.comboBox14 = new ComboBox();
            this.label104 = new Label();
            this.comboBox13 = new ComboBox();
            this.label103 = new Label();
            this.label102 = new Label();
            this.label101 = new Label();
            this.label100 = new Label();
            this.comboBox12 = new ComboBox();
            this.comboBox11 = new ComboBox();
            this.comboBox10 = new ComboBox();
            this.comboBox9 = new ComboBox();
            this.comboBox8 = new ComboBox();
            this.label99 = new Label();
            this.comboBox7 = new ComboBox();
            this.label98 = new Label();
            this.comboBox6 = new ComboBox();
            this.label97 = new Label();
            this.comboBox5 = new ComboBox();
            this.label96 = new Label();
            this.comboBox3 = new ComboBox();
            this.label95 = new Label();
            this.groupBox13 = new GroupBox();
            this.od9 = new TextBox();
            this.label10 = new Label();
            this.od8 = new TextBox();
            this.label11 = new Label();
            this.od7 = new TextBox();
            this.label12 = new Label();
            this.od6 = new TextBox();
            this.label13 = new Label();
            this.od5 = new TextBox();
            this.label14 = new Label();
            this.od4 = new TextBox();
            this.label15 = new Label();
            this.od3 = new TextBox();
            this.label16 = new Label();
            this.od2 = new TextBox();
            this.label17 = new Label();
            this.od1 = new TextBox();
            this.label18 = new Label();
            this.od0 = new TextBox();
            this.label19 = new Label();
            this.textBox79 = new TextBox();
            this.label79 = new Label();
            this.textBox78 = new TextBox();
            this.label78 = new Label();
            this.textBox77 = new TextBox();
            this.label77 = new Label();
            this.textBox76 = new TextBox();
            this.label76 = new Label();
            this.textBox75 = new TextBox();
            this.label75 = new Label();
            this.textBox74 = new TextBox();
            this.label74 = new Label();
            this.textBox73 = new TextBox();
            this.label73 = new Label();
            this.textBox72 = new TextBox();
            this.label72 = new Label();
            this.textBox71 = new TextBox();
            this.label71 = new Label();
            this.textBox70 = new TextBox();
            this.label70 = new Label();
            this.textBox69 = new TextBox();
            this.label69 = new Label();
            this.textBox68 = new TextBox();
            this.label68 = new Label();
            this.textBox67 = new TextBox();
            this.label67 = new Label();
            this.textBox66 = new TextBox();
            this.label66 = new Label();
            this.textBox65 = new TextBox();
            this.label65 = new Label();
            this.textBox64 = new TextBox();
            this.label64 = new Label();
            this.textBox63 = new TextBox();
            this.label63 = new Label();
            this.textBox62 = new TextBox();
            this.label62 = new Label();
            this.textBox61 = new TextBox();
            this.label61 = new Label();
            this.textBox60 = new TextBox();
            this.label60 = new Label();
            this.LblPercent3 = new Label();
            this.LblNote = new Label();
            this.label20 = new Label();
            this.label6 = new Label();
            this.groupBox3 = new GroupBox();
            this.TbSeal7 = new TextBox();
            this.TbSeal6 = new TextBox();
            this.TbSeal9 = new TextBox();
            this.TbSeal8 = new TextBox();
            this.TbSeal5 = new TextBox();
            this.TbSeal4 = new TextBox();
            this.TbSeal3 = new TextBox();
            this.TbSeal2 = new TextBox();
            this.TbSeal1 = new TextBox();
            this.TbSeal0 = new TextBox();
            this.LblPercent4 = new Label();
            this.LblPercent2 = new Label();
            this.LblPercent1 = new Label();
            this.TbPercent4 = new TextBox();
            this.TbPercent3 = new TextBox();
            this.TbPercent2 = new TextBox();
            this.TbPercent1 = new TextBox();
            this.btnPercentAddResist = new Button();
            this.btnPercentAddMattk = new Button();
            this.btnPercentAddDef = new Button();
            this.btnPercentAddAttk = new Button();
            this.TbType = new TextBox();
            this.TbGrade = new TextBox();
            this.PbAcc = new PictureBox();
            this.PbArmor = new PictureBox();
            this.PbWeapon = new PictureBox();
            this.rstxt = new TextBox();
            this.label9 = new Label();
            this.tdrop = new ComboBox();
            this.label8 = new Label();
            this.gdrop = new ComboBox();
            this.label7 = new Label();
            this.mtktxt = new TextBox();
            this.label5 = new Label();
            this.deftxt = new TextBox();
            this.label4 = new Label();
            this.atktxt = new TextBox();
            this.label3 = new Label();
            this.nametxt = new TextBox();
            this.label2 = new Label();
            this.idtxt = new TextBox();
            this.label1 = new Label();
            this.groupBox2 = new GroupBox();
            this.button1 = new Button();
            this.UpdateButton = new Button();
            this.remove = new Button();
            this.listBox1 = new ListBox();
            this.toolStrip1.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox17.SuspendLayout();
            this.groupBox13.SuspendLayout();
            this.groupBox3.SuspendLayout();
            ((ISupportInitialize)this.PbAcc).BeginInit();
            ((ISupportInitialize)this.PbArmor).BeginInit();
            ((ISupportInitialize)this.PbWeapon).BeginInit();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            this.toolStrip1.Items.AddRange(new ToolStripItem[1]
            {
        (ToolStripItem) this.toolStripDropDownButton1
            });
            this.toolStrip1.Location = new Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new Size(1216, 25);
            this.toolStrip1.TabIndex = 0;
            this.toolStrip1.Text = "toolStrip1";
            this.toolStripDropDownButton1.DisplayStyle = ToolStripItemDisplayStyle.Image;
            this.toolStripDropDownButton1.DropDownItems.AddRange(new ToolStripItem[1]
            {
        (ToolStripItem) this.exportToolStripMenuItem
            });
            this.toolStripDropDownButton1.Image = (Image)Resources._08;
            this.toolStripDropDownButton1.ImageTransparentColor = Color.Magenta;
            this.toolStripDropDownButton1.Name = "toolStripDropDownButton1";
            this.toolStripDropDownButton1.Size = new Size(29, 22);
            this.toolStripDropDownButton1.Text = "toolStripDropDownButton1";
            this.exportToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[2]
            {
        (ToolStripItem) this.rareOptionlodToolStripMenuItem,
        (ToolStripItem) this.strRareOptionusToolStripMenuItem
            });
            this.exportToolStripMenuItem.Name = "exportToolStripMenuItem";
            this.exportToolStripMenuItem.Size = new Size(152, 22);
            this.exportToolStripMenuItem.Text = "Export";
            this.rareOptionlodToolStripMenuItem.Name = "rareOptionlodToolStripMenuItem";
            this.rareOptionlodToolStripMenuItem.Size = new Size(154, 22);
            this.rareOptionlodToolStripMenuItem.Text = "RareOption.lod";
            this.rareOptionlodToolStripMenuItem.Click += new EventHandler(this.rareOptionlodToolStripMenuItem_Click);
            this.strRareOptionusToolStripMenuItem.Name = "strRareOptionusToolStripMenuItem";
            this.strRareOptionusToolStripMenuItem.Size = new Size(154, 22);
            this.strRareOptionusToolStripMenuItem.Text = "strRareOption";
            this.strRareOptionusToolStripMenuItem.Click += new EventHandler(this.strRareOptionusToolStripMenuItem_Click);
            this.groupBox1.Controls.Add((Control)this.groupBox17);
            this.groupBox1.Controls.Add((Control)this.groupBox13);
            this.groupBox1.Controls.Add((Control)this.LblPercent3);
            this.groupBox1.Controls.Add((Control)this.LblNote);
            this.groupBox1.Controls.Add((Control)this.label20);
            this.groupBox1.Controls.Add((Control)this.label6);
            this.groupBox1.Controls.Add((Control)this.groupBox3);
            this.groupBox1.Controls.Add((Control)this.groupBox2);
            this.groupBox1.Controls.Add((Control)this.listBox1);
            this.groupBox1.Location = new Point(12, 28);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new Size(1192, 414);
            this.groupBox1.TabIndex = 1;
            this.groupBox1.TabStop = false;
            this.groupBox17.Controls.Add((Control)this.comboBox23);
            this.groupBox17.Controls.Add((Control)this.comboBox22);
            this.groupBox17.Controls.Add((Control)this.comboBox21);
            this.groupBox17.Controls.Add((Control)this.comboBox20);
            this.groupBox17.Controls.Add((Control)this.comboBox19);
            this.groupBox17.Controls.Add((Control)this.comboBox18);
            this.groupBox17.Controls.Add((Control)this.comboBox17);
            this.groupBox17.Controls.Add((Control)this.comboBox16);
            this.groupBox17.Controls.Add((Control)this.comboBox15);
            this.groupBox17.Controls.Add((Control)this.comboBox14);
            this.groupBox17.Controls.Add((Control)this.label104);
            this.groupBox17.Controls.Add((Control)this.comboBox13);
            this.groupBox17.Controls.Add((Control)this.label103);
            this.groupBox17.Controls.Add((Control)this.label102);
            this.groupBox17.Controls.Add((Control)this.label101);
            this.groupBox17.Controls.Add((Control)this.label100);
            this.groupBox17.Controls.Add((Control)this.comboBox12);
            this.groupBox17.Controls.Add((Control)this.comboBox11);
            this.groupBox17.Controls.Add((Control)this.comboBox10);
            this.groupBox17.Controls.Add((Control)this.comboBox9);
            this.groupBox17.Controls.Add((Control)this.comboBox8);
            this.groupBox17.Controls.Add((Control)this.label99);
            this.groupBox17.Controls.Add((Control)this.comboBox7);
            this.groupBox17.Controls.Add((Control)this.label98);
            this.groupBox17.Controls.Add((Control)this.comboBox6);
            this.groupBox17.Controls.Add((Control)this.label97);
            this.groupBox17.Controls.Add((Control)this.comboBox5);
            this.groupBox17.Controls.Add((Control)this.label96);
            this.groupBox17.Controls.Add((Control)this.comboBox3);
            this.groupBox17.Controls.Add((Control)this.label95);
            this.groupBox17.Location = new Point(819, 18);
            this.groupBox17.Name = "groupBox17";
            this.groupBox17.Size = new Size(367, 296);
            this.groupBox17.TabIndex = 43;
            this.groupBox17.TabStop = false;
            this.groupBox17.Text = "Option Selecter";
            this.comboBox23.FlatStyle = FlatStyle.Flat;
            this.comboBox23.FormattingEnabled = true;
            this.comboBox23.Location = new Point(275, 261);
            this.comboBox23.Name = "comboBox23";
            this.comboBox23.Size = new Size(81, 21);
            this.comboBox23.TabIndex = 37;
            this.comboBox23.SelectedIndexChanged += new EventHandler(this.comboBox23_SelectedIndexChanged);
            this.comboBox23.SelectionChangeCommitted += new EventHandler(this.comboBox23_SelectionChangeCommitted);
            this.comboBox22.FlatStyle = FlatStyle.Flat;
            this.comboBox22.FormattingEnabled = true;
            this.comboBox22.Location = new Point(275, 234);
            this.comboBox22.Name = "comboBox22";
            this.comboBox22.Size = new Size(81, 21);
            this.comboBox22.TabIndex = 36;
            this.comboBox22.SelectedIndexChanged += new EventHandler(this.comboBox22_SelectedIndexChanged);
            this.comboBox22.SelectionChangeCommitted += new EventHandler(this.comboBox22_SelectionChangeCommitted);
            this.comboBox21.FlatStyle = FlatStyle.Flat;
            this.comboBox21.FormattingEnabled = true;
            this.comboBox21.Location = new Point(275, 207);
            this.comboBox21.Name = "comboBox21";
            this.comboBox21.Size = new Size(81, 21);
            this.comboBox21.TabIndex = 35;
            this.comboBox21.SelectedIndexChanged += new EventHandler(this.comboBox21_SelectedIndexChanged);
            this.comboBox21.SelectionChangeCommitted += new EventHandler(this.comboBox21_SelectionChangeCommitted);
            this.comboBox20.FlatStyle = FlatStyle.Flat;
            this.comboBox20.FormattingEnabled = true;
            this.comboBox20.Location = new Point(275, 180);
            this.comboBox20.Name = "comboBox20";
            this.comboBox20.Size = new Size(81, 21);
            this.comboBox20.TabIndex = 34;
            this.comboBox20.SelectedIndexChanged += new EventHandler(this.comboBox20_SelectedIndexChanged);
            this.comboBox20.SelectionChangeCommitted += new EventHandler(this.comboBox20_SelectionChangeCommitted);
            this.comboBox19.FlatStyle = FlatStyle.Flat;
            this.comboBox19.FormattingEnabled = true;
            this.comboBox19.Location = new Point(275, 153);
            this.comboBox19.Name = "comboBox19";
            this.comboBox19.Size = new Size(81, 21);
            this.comboBox19.TabIndex = 33;
            this.comboBox19.SelectedIndexChanged += new EventHandler(this.comboBox19_SelectedIndexChanged);
            this.comboBox19.SelectionChangeCommitted += new EventHandler(this.comboBox19_SelectionChangeCommitted);
            this.comboBox18.FlatStyle = FlatStyle.Flat;
            this.comboBox18.FormattingEnabled = true;
            this.comboBox18.Location = new Point(275, 126);
            this.comboBox18.Name = "comboBox18";
            this.comboBox18.Size = new Size(81, 21);
            this.comboBox18.TabIndex = 32;
            this.comboBox18.SelectedIndexChanged += new EventHandler(this.comboBox18_SelectedIndexChanged);
            this.comboBox18.SelectionChangeCommitted += new EventHandler(this.comboBox18_SelectionChangeCommitted);
            this.comboBox17.FlatStyle = FlatStyle.Flat;
            this.comboBox17.FormattingEnabled = true;
            this.comboBox17.Location = new Point(275, 99);
            this.comboBox17.Name = "comboBox17";
            this.comboBox17.Size = new Size(81, 21);
            this.comboBox17.TabIndex = 31;
            this.comboBox17.SelectedIndexChanged += new EventHandler(this.comboBox17_SelectedIndexChanged);
            this.comboBox17.SelectionChangeCommitted += new EventHandler(this.comboBox17_SelectionChangeCommitted);
            this.comboBox16.FlatStyle = FlatStyle.Flat;
            this.comboBox16.FormattingEnabled = true;
            this.comboBox16.Location = new Point(275, 72);
            this.comboBox16.Name = "comboBox16";
            this.comboBox16.Size = new Size(81, 21);
            this.comboBox16.TabIndex = 30;
            this.comboBox16.SelectedIndexChanged += new EventHandler(this.comboBox16_SelectedIndexChanged);
            this.comboBox16.SelectionChangeCommitted += new EventHandler(this.comboBox16_SelectionChangeCommitted);
            this.comboBox15.FlatStyle = FlatStyle.Flat;
            this.comboBox15.FormattingEnabled = true;
            this.comboBox15.Location = new Point(275, 45);
            this.comboBox15.Name = "comboBox15";
            this.comboBox15.Size = new Size(81, 21);
            this.comboBox15.TabIndex = 29;
            this.comboBox15.SelectedIndexChanged += new EventHandler(this.comboBox15_SelectedIndexChanged);
            this.comboBox15.SelectionChangeCommitted += new EventHandler(this.comboBox15_SelectionChangeCommitted);
            this.comboBox14.FlatStyle = FlatStyle.Flat;
            this.comboBox14.FormattingEnabled = true;
            this.comboBox14.Location = new Point(275, 18);
            this.comboBox14.Name = "comboBox14";
            this.comboBox14.Size = new Size(81, 21);
            this.comboBox14.TabIndex = 28;
            this.comboBox14.SelectedIndexChanged += new EventHandler(this.comboBox14_SelectedIndexChanged);
            this.comboBox14.SelectionChangeCommitted += new EventHandler(this.comboBox14_SelectionChangeCommitted);
            this.label104.AutoSize = true;
            this.label104.Location = new Point(5, 264);
            this.label104.Name = "label104";
            this.label104.Size = new Size(40, 13);
            this.label104.TabIndex = 27;
            this.label104.Text = "Seal 9:";
            this.comboBox13.FlatStyle = FlatStyle.Flat;
            this.comboBox13.FormattingEnabled = true;
            this.comboBox13.Location = new Point(51, 261);
            this.comboBox13.Name = "comboBox13";
            this.comboBox13.Size = new Size(217, 21);
            this.comboBox13.TabIndex = 26;
            this.comboBox13.SelectedIndexChanged += new EventHandler(this.comboBox12_SelectedIndexChanged);
            this.comboBox13.SelectionChangeCommitted += new EventHandler(this.comboBox13_SelectionChangeCommitted);
            this.label103.AutoSize = true;
            this.label103.Location = new Point(5, 237);
            this.label103.Name = "label103";
            this.label103.Size = new Size(40, 13);
            this.label103.TabIndex = 25;
            this.label103.Text = "Seal 8:";
            this.label102.AutoSize = true;
            this.label102.Location = new Point(5, 211);
            this.label102.Name = "label102";
            this.label102.Size = new Size(40, 13);
            this.label102.TabIndex = 24;
            this.label102.Text = "Seal 7:";
            this.label101.AutoSize = true;
            this.label101.Location = new Point(5, 184);
            this.label101.Name = "label101";
            this.label101.Size = new Size(40, 13);
            this.label101.TabIndex = 23;
            this.label101.Text = "Seal 6:";
            this.label100.AutoSize = true;
            this.label100.Location = new Point(5, 156);
            this.label100.Name = "label100";
            this.label100.Size = new Size(40, 13);
            this.label100.TabIndex = 22;
            this.label100.Text = "Seal 5:";
            this.comboBox12.FlatStyle = FlatStyle.Flat;
            this.comboBox12.FormattingEnabled = true;
            this.comboBox12.Location = new Point(51, 234);
            this.comboBox12.Name = "comboBox12";
            this.comboBox12.Size = new Size(217, 21);
            this.comboBox12.TabIndex = 21;
            this.comboBox12.SelectedIndexChanged += new EventHandler(this.comboBox12_SelectedIndexChanged);
            this.comboBox12.SelectionChangeCommitted += new EventHandler(this.comboBox12_SelectionChangeCommitted);
            this.comboBox11.FlatStyle = FlatStyle.Flat;
            this.comboBox11.FormattingEnabled = true;
            this.comboBox11.Location = new Point(51, 207);
            this.comboBox11.Name = "comboBox11";
            this.comboBox11.Size = new Size(217, 21);
            this.comboBox11.TabIndex = 20;
            this.comboBox11.SelectedIndexChanged += new EventHandler(this.comboBox11_SelectedIndexChanged);
            this.comboBox11.SelectionChangeCommitted += new EventHandler(this.comboBox11_SelectionChangeCommitted);
            this.comboBox10.FlatStyle = FlatStyle.Flat;
            this.comboBox10.FormattingEnabled = true;
            this.comboBox10.Location = new Point(51, 180);
            this.comboBox10.Name = "comboBox10";
            this.comboBox10.Size = new Size(217, 21);
            this.comboBox10.TabIndex = 19;
            this.comboBox10.SelectedIndexChanged += new EventHandler(this.comboBox10_SelectedIndexChanged);
            this.comboBox10.SelectionChangeCommitted += new EventHandler(this.comboBox10_SelectionChangeCommitted);
            this.comboBox9.FlatStyle = FlatStyle.Flat;
            this.comboBox9.FormattingEnabled = true;
            this.comboBox9.Location = new Point(51, 153);
            this.comboBox9.Name = "comboBox9";
            this.comboBox9.Size = new Size(217, 21);
            this.comboBox9.TabIndex = 18;
            this.comboBox9.SelectedIndexChanged += new EventHandler(this.comboBox9_SelectedIndexChanged);
            this.comboBox9.SelectionChangeCommitted += new EventHandler(this.comboBox9_SelectionChangeCommitted);
            this.comboBox8.FlatStyle = FlatStyle.Flat;
            this.comboBox8.FormattingEnabled = true;
            this.comboBox8.Location = new Point(51, 126);
            this.comboBox8.Name = "comboBox8";
            this.comboBox8.Size = new Size(217, 21);
            this.comboBox8.TabIndex = 17;
            this.comboBox8.SelectedIndexChanged += new EventHandler(this.comboBox8_SelectedIndexChanged);
            this.comboBox8.SelectionChangeCommitted += new EventHandler(this.comboBox8_SelectionChangeCommitted);
            this.label99.AutoSize = true;
            this.label99.Location = new Point(5, 128);
            this.label99.Name = "label99";
            this.label99.Size = new Size(40, 13);
            this.label99.TabIndex = 16;
            this.label99.Text = "Seal 4:";
            this.comboBox7.FlatStyle = FlatStyle.Flat;
            this.comboBox7.FormattingEnabled = true;
            this.comboBox7.Location = new Point(51, 99);
            this.comboBox7.Name = "comboBox7";
            this.comboBox7.Size = new Size(217, 21);
            this.comboBox7.TabIndex = 13;
            this.comboBox7.SelectedIndexChanged += new EventHandler(this.comboBox7_SelectedIndexChanged);
            this.comboBox7.SelectionChangeCommitted += new EventHandler(this.comboBox7_SelectionChangeCommitted);
            this.label98.AutoSize = true;
            this.label98.Location = new Point(5, 101);
            this.label98.Name = "label98";
            this.label98.Size = new Size(40, 13);
            this.label98.TabIndex = 12;
            this.label98.Text = "Seal 3:";
            this.comboBox6.FlatStyle = FlatStyle.Flat;
            this.comboBox6.FormattingEnabled = true;
            this.comboBox6.Location = new Point(51, 72);
            this.comboBox6.Name = "comboBox6";
            this.comboBox6.Size = new Size(217, 21);
            this.comboBox6.TabIndex = 9;
            this.comboBox6.SelectedIndexChanged += new EventHandler(this.comboBox6_SelectedIndexChanged);
            this.comboBox6.SelectionChangeCommitted += new EventHandler(this.comboBox6_SelectionChangeCommitted);
            this.label97.AutoSize = true;
            this.label97.Location = new Point(5, 76);
            this.label97.Name = "label97";
            this.label97.Size = new Size(40, 13);
            this.label97.TabIndex = 8;
            this.label97.Text = "Seal 2:";
            this.comboBox5.FlatStyle = FlatStyle.Flat;
            this.comboBox5.FormattingEnabled = true;
            this.comboBox5.Location = new Point(51, 45);
            this.comboBox5.Name = "comboBox5";
            this.comboBox5.Size = new Size(217, 21);
            this.comboBox5.TabIndex = 5;
            this.comboBox5.SelectedIndexChanged += new EventHandler(this.comboBox5_SelectedIndexChanged);
            this.comboBox5.SelectionChangeCommitted += new EventHandler(this.comboBox5_SelectionChangeCommitted);
            this.label96.AutoSize = true;
            this.label96.Location = new Point(5, 49);
            this.label96.Name = "label96";
            this.label96.Size = new Size(40, 13);
            this.label96.TabIndex = 4;
            this.label96.Text = "Seal 1:";
            this.comboBox3.FlatStyle = FlatStyle.Flat;
            this.comboBox3.FormattingEnabled = true;
            this.comboBox3.Location = new Point(51, 18);
            this.comboBox3.Name = "comboBox3";
            this.comboBox3.Size = new Size(217, 21);
            this.comboBox3.TabIndex = 1;
            this.comboBox3.SelectedIndexChanged += new EventHandler(this.comboBox3_SelectedIndexChanged);
            this.comboBox3.SelectionChangeCommitted += new EventHandler(this.comboBox3_SelectionChangeCommitted);
            this.label95.AutoSize = true;
            this.label95.Location = new Point(5, 21);
            this.label95.Name = "label95";
            this.label95.Size = new Size(40, 13);
            this.label95.TabIndex = 0;
            this.label95.Text = "Seal 0:";
            this.groupBox13.Controls.Add((Control)this.od9);
            this.groupBox13.Controls.Add((Control)this.label10);
            this.groupBox13.Controls.Add((Control)this.od8);
            this.groupBox13.Controls.Add((Control)this.label11);
            this.groupBox13.Controls.Add((Control)this.od7);
            this.groupBox13.Controls.Add((Control)this.label12);
            this.groupBox13.Controls.Add((Control)this.od6);
            this.groupBox13.Controls.Add((Control)this.label13);
            this.groupBox13.Controls.Add((Control)this.od5);
            this.groupBox13.Controls.Add((Control)this.label14);
            this.groupBox13.Controls.Add((Control)this.od4);
            this.groupBox13.Controls.Add((Control)this.label15);
            this.groupBox13.Controls.Add((Control)this.od3);
            this.groupBox13.Controls.Add((Control)this.label16);
            this.groupBox13.Controls.Add((Control)this.od2);
            this.groupBox13.Controls.Add((Control)this.label17);
            this.groupBox13.Controls.Add((Control)this.od1);
            this.groupBox13.Controls.Add((Control)this.label18);
            this.groupBox13.Controls.Add((Control)this.od0);
            this.groupBox13.Controls.Add((Control)this.label19);
            this.groupBox13.Controls.Add((Control)this.textBox79);
            this.groupBox13.Controls.Add((Control)this.label79);
            this.groupBox13.Controls.Add((Control)this.textBox78);
            this.groupBox13.Controls.Add((Control)this.label78);
            this.groupBox13.Controls.Add((Control)this.textBox77);
            this.groupBox13.Controls.Add((Control)this.label77);
            this.groupBox13.Controls.Add((Control)this.textBox76);
            this.groupBox13.Controls.Add((Control)this.label76);
            this.groupBox13.Controls.Add((Control)this.textBox75);
            this.groupBox13.Controls.Add((Control)this.label75);
            this.groupBox13.Controls.Add((Control)this.textBox74);
            this.groupBox13.Controls.Add((Control)this.label74);
            this.groupBox13.Controls.Add((Control)this.textBox73);
            this.groupBox13.Controls.Add((Control)this.label73);
            this.groupBox13.Controls.Add((Control)this.textBox72);
            this.groupBox13.Controls.Add((Control)this.label72);
            this.groupBox13.Controls.Add((Control)this.textBox71);
            this.groupBox13.Controls.Add((Control)this.label71);
            this.groupBox13.Controls.Add((Control)this.textBox70);
            this.groupBox13.Controls.Add((Control)this.label70);
            this.groupBox13.Controls.Add((Control)this.textBox69);
            this.groupBox13.Controls.Add((Control)this.label69);
            this.groupBox13.Controls.Add((Control)this.textBox68);
            this.groupBox13.Controls.Add((Control)this.label68);
            this.groupBox13.Controls.Add((Control)this.textBox67);
            this.groupBox13.Controls.Add((Control)this.label67);
            this.groupBox13.Controls.Add((Control)this.textBox66);
            this.groupBox13.Controls.Add((Control)this.label66);
            this.groupBox13.Controls.Add((Control)this.textBox65);
            this.groupBox13.Controls.Add((Control)this.label65);
            this.groupBox13.Controls.Add((Control)this.textBox64);
            this.groupBox13.Controls.Add((Control)this.label64);
            this.groupBox13.Controls.Add((Control)this.textBox63);
            this.groupBox13.Controls.Add((Control)this.label63);
            this.groupBox13.Controls.Add((Control)this.textBox62);
            this.groupBox13.Controls.Add((Control)this.label62);
            this.groupBox13.Controls.Add((Control)this.textBox61);
            this.groupBox13.Controls.Add((Control)this.label61);
            this.groupBox13.Controls.Add((Control)this.textBox60);
            this.groupBox13.Controls.Add((Control)this.label60);
            this.groupBox13.Location = new Point(432, 19);
            this.groupBox13.Name = "groupBox13";
            this.groupBox13.Size = new Size(381, 295);
            this.groupBox13.TabIndex = 42;
            this.groupBox13.TabStop = false;
            this.groupBox13.Text = "Rare Options Value";
            this.od9.BorderStyle = BorderStyle.FixedSingle;
            this.od9.Location = new Point(314, 257);
            this.od9.Name = "od9";
            this.od9.Size = new Size(61, 20);
            this.od9.TabIndex = 98;
            this.label10.AutoSize = true;
            this.label10.Location = new Point(261, 259);
            this.label10.Name = "label10";
            this.label10.Size = new Size(32, 13);
            this.label10.TabIndex = 99;
            this.label10.Text = "Prop:";
            this.od8.BorderStyle = BorderStyle.FixedSingle;
            this.od8.Location = new Point(314, 231);
            this.od8.Name = "od8";
            this.od8.Size = new Size(61, 20);
            this.od8.TabIndex = 96;
            this.label11.AutoSize = true;
            this.label11.Location = new Point(261, 233);
            this.label11.Name = "label11";
            this.label11.Size = new Size(32, 13);
            this.label11.TabIndex = 97;
            this.label11.Text = "Prop:";
            this.od7.BorderStyle = BorderStyle.FixedSingle;
            this.od7.Location = new Point(314, 205);
            this.od7.Name = "od7";
            this.od7.Size = new Size(61, 20);
            this.od7.TabIndex = 94;
            this.label12.AutoSize = true;
            this.label12.Location = new Point(261, 207);
            this.label12.Name = "label12";
            this.label12.Size = new Size(32, 13);
            this.label12.TabIndex = 95;
            this.label12.Text = "Prop:";
            this.od6.BorderStyle = BorderStyle.FixedSingle;
            this.od6.Location = new Point(314, 179);
            this.od6.Name = "od6";
            this.od6.Size = new Size(61, 20);
            this.od6.TabIndex = 92;
            this.label13.AutoSize = true;
            this.label13.Location = new Point(261, 181);
            this.label13.Name = "label13";
            this.label13.Size = new Size(32, 13);
            this.label13.TabIndex = 93;
            this.label13.Text = "Prop:";
            this.od5.BorderStyle = BorderStyle.FixedSingle;
            this.od5.Location = new Point(314, 153);
            this.od5.Name = "od5";
            this.od5.Size = new Size(61, 20);
            this.od5.TabIndex = 90;
            this.label14.AutoSize = true;
            this.label14.Location = new Point(261, 155);
            this.label14.Name = "label14";
            this.label14.Size = new Size(32, 13);
            this.label14.TabIndex = 91;
            this.label14.Text = "Prop:";
            this.od4.BorderStyle = BorderStyle.FixedSingle;
            this.od4.Location = new Point(314, 126);
            this.od4.Name = "od4";
            this.od4.Size = new Size(61, 20);
            this.od4.TabIndex = 88;
            this.label15.AutoSize = true;
            this.label15.Location = new Point(261, 128);
            this.label15.Name = "label15";
            this.label15.Size = new Size(32, 13);
            this.label15.TabIndex = 89;
            this.label15.Text = "Prop:";
            this.od3.BorderStyle = BorderStyle.FixedSingle;
            this.od3.Location = new Point(314, 98);
            this.od3.Name = "od3";
            this.od3.Size = new Size(61, 20);
            this.od3.TabIndex = 86;
            this.label16.AutoSize = true;
            this.label16.Location = new Point(261, 100);
            this.label16.Name = "label16";
            this.label16.Size = new Size(32, 13);
            this.label16.TabIndex = 87;
            this.label16.Text = "Prop:";
            this.od2.BorderStyle = BorderStyle.FixedSingle;
            this.od2.Location = new Point(314, 72);
            this.od2.Name = "od2";
            this.od2.Size = new Size(61, 20);
            this.od2.TabIndex = 84;
            this.label17.AutoSize = true;
            this.label17.Location = new Point(261, 74);
            this.label17.Name = "label17";
            this.label17.Size = new Size(32, 13);
            this.label17.TabIndex = 85;
            this.label17.Text = "Prop:";
            this.od1.BorderStyle = BorderStyle.FixedSingle;
            this.od1.Location = new Point(314, 46);
            this.od1.Name = "od1";
            this.od1.Size = new Size(61, 20);
            this.od1.TabIndex = 82;
            this.label18.AutoSize = true;
            this.label18.Location = new Point(261, 48);
            this.label18.Name = "label18";
            this.label18.Size = new Size(32, 13);
            this.label18.TabIndex = 83;
            this.label18.Text = "Prop:";
            this.od0.BorderStyle = BorderStyle.FixedSingle;
            this.od0.Location = new Point(314, 20);
            this.od0.Name = "od0";
            this.od0.Size = new Size(61, 20);
            this.od0.TabIndex = 80;
            this.label19.AutoSize = true;
            this.label19.Location = new Point(261, 22);
            this.label19.Name = "label19";
            this.label19.Size = new Size(32, 13);
            this.label19.TabIndex = 81;
            this.label19.Text = "Prop:";
            this.textBox79.BorderStyle = BorderStyle.FixedSingle;
            this.textBox79.Location = new Point(188, 257);
            this.textBox79.Name = "textBox79";
            this.textBox79.Size = new Size(61, 20);
            this.textBox79.TabIndex = 78;
            this.label79.AutoSize = true;
            this.label79.Location = new Point(135, 259);
            this.label79.Name = "label79";
            this.label79.Size = new Size(36, 13);
            this.label79.TabIndex = 79;
            this.label79.Text = "Level:";
            this.textBox78.BorderStyle = BorderStyle.FixedSingle;
            this.textBox78.Location = new Point(188, 231);
            this.textBox78.Name = "textBox78";
            this.textBox78.Size = new Size(61, 20);
            this.textBox78.TabIndex = 76;
            this.label78.AutoSize = true;
            this.label78.Location = new Point(135, 233);
            this.label78.Name = "label78";
            this.label78.Size = new Size(36, 13);
            this.label78.TabIndex = 77;
            this.label78.Text = "Level:";
            this.textBox77.BorderStyle = BorderStyle.FixedSingle;
            this.textBox77.Location = new Point(188, 205);
            this.textBox77.Name = "textBox77";
            this.textBox77.Size = new Size(61, 20);
            this.textBox77.TabIndex = 74;
            this.label77.AutoSize = true;
            this.label77.Location = new Point(135, 207);
            this.label77.Name = "label77";
            this.label77.Size = new Size(36, 13);
            this.label77.TabIndex = 75;
            this.label77.Text = "Level:";
            this.textBox76.BorderStyle = BorderStyle.FixedSingle;
            this.textBox76.Location = new Point(188, 179);
            this.textBox76.Name = "textBox76";
            this.textBox76.Size = new Size(61, 20);
            this.textBox76.TabIndex = 72;
            this.label76.AutoSize = true;
            this.label76.Location = new Point(135, 181);
            this.label76.Name = "label76";
            this.label76.Size = new Size(36, 13);
            this.label76.TabIndex = 73;
            this.label76.Text = "Level:";
            this.textBox75.BorderStyle = BorderStyle.FixedSingle;
            this.textBox75.Location = new Point(188, 153);
            this.textBox75.Name = "textBox75";
            this.textBox75.Size = new Size(61, 20);
            this.textBox75.TabIndex = 70;
            this.label75.AutoSize = true;
            this.label75.Location = new Point(135, 155);
            this.label75.Name = "label75";
            this.label75.Size = new Size(36, 13);
            this.label75.TabIndex = 71;
            this.label75.Text = "Level:";
            this.textBox74.BorderStyle = BorderStyle.FixedSingle;
            this.textBox74.Location = new Point(188, 126);
            this.textBox74.Name = "textBox74";
            this.textBox74.Size = new Size(61, 20);
            this.textBox74.TabIndex = 68;
            this.label74.AutoSize = true;
            this.label74.Location = new Point(135, 128);
            this.label74.Name = "label74";
            this.label74.Size = new Size(36, 13);
            this.label74.TabIndex = 69;
            this.label74.Text = "Level:";
            this.textBox73.BorderStyle = BorderStyle.FixedSingle;
            this.textBox73.Location = new Point(188, 98);
            this.textBox73.Name = "textBox73";
            this.textBox73.Size = new Size(61, 20);
            this.textBox73.TabIndex = 66;
            this.label73.AutoSize = true;
            this.label73.Location = new Point(135, 100);
            this.label73.Name = "label73";
            this.label73.Size = new Size(36, 13);
            this.label73.TabIndex = 67;
            this.label73.Text = "Level:";
            this.textBox72.BorderStyle = BorderStyle.FixedSingle;
            this.textBox72.Location = new Point(188, 72);
            this.textBox72.Name = "textBox72";
            this.textBox72.Size = new Size(61, 20);
            this.textBox72.TabIndex = 64;
            this.label72.AutoSize = true;
            this.label72.Location = new Point(135, 74);
            this.label72.Name = "label72";
            this.label72.Size = new Size(36, 13);
            this.label72.TabIndex = 65;
            this.label72.Text = "Level:";
            this.textBox71.BorderStyle = BorderStyle.FixedSingle;
            this.textBox71.Location = new Point(188, 46);
            this.textBox71.Name = "textBox71";
            this.textBox71.Size = new Size(61, 20);
            this.textBox71.TabIndex = 62;
            this.label71.AutoSize = true;
            this.label71.Location = new Point(135, 48);
            this.label71.Name = "label71";
            this.label71.Size = new Size(36, 13);
            this.label71.TabIndex = 63;
            this.label71.Text = "Level:";
            this.textBox70.BorderStyle = BorderStyle.FixedSingle;
            this.textBox70.Location = new Point(188, 20);
            this.textBox70.Name = "textBox70";
            this.textBox70.Size = new Size(61, 20);
            this.textBox70.TabIndex = 60;
            this.label70.AutoSize = true;
            this.label70.Location = new Point(135, 22);
            this.label70.Name = "label70";
            this.label70.Size = new Size(36, 13);
            this.label70.TabIndex = 61;
            this.label70.Text = "Level:";
            this.textBox69.BorderStyle = BorderStyle.FixedSingle;
            this.textBox69.Location = new Point(68, (int)byte.MaxValue);
            this.textBox69.Name = "textBox69";
            this.textBox69.Size = new Size(61, 20);
            this.textBox69.TabIndex = 58;
            this.label69.AutoSize = true;
            this.label69.Location = new Point(15, 257);
            this.label69.Name = "label69";
            this.label69.Size = new Size(47, 13);
            this.label69.TabIndex = 59;
            this.label69.Text = "Option9:";
            this.textBox68.BorderStyle = BorderStyle.FixedSingle;
            this.textBox68.Location = new Point(68, 229);
            this.textBox68.Name = "textBox68";
            this.textBox68.Size = new Size(61, 20);
            this.textBox68.TabIndex = 56;
            this.label68.AutoSize = true;
            this.label68.Location = new Point(15, 231);
            this.label68.Name = "label68";
            this.label68.Size = new Size(47, 13);
            this.label68.TabIndex = 57;
            this.label68.Text = "Option8:";
            this.textBox67.BorderStyle = BorderStyle.FixedSingle;
            this.textBox67.Location = new Point(68, 203);
            this.textBox67.Name = "textBox67";
            this.textBox67.Size = new Size(61, 20);
            this.textBox67.TabIndex = 54;
            this.label67.AutoSize = true;
            this.label67.Location = new Point(15, 205);
            this.label67.Name = "label67";
            this.label67.Size = new Size(47, 13);
            this.label67.TabIndex = 55;
            this.label67.Text = "Option7:";
            this.textBox66.BorderStyle = BorderStyle.FixedSingle;
            this.textBox66.Location = new Point(68, 177);
            this.textBox66.Name = "textBox66";
            this.textBox66.Size = new Size(61, 20);
            this.textBox66.TabIndex = 52;
            this.label66.AutoSize = true;
            this.label66.Location = new Point(15, 179);
            this.label66.Name = "label66";
            this.label66.Size = new Size(47, 13);
            this.label66.TabIndex = 53;
            this.label66.Text = "Option6:";
            this.textBox65.BorderStyle = BorderStyle.FixedSingle;
            this.textBox65.Location = new Point(68, 151);
            this.textBox65.Name = "textBox65";
            this.textBox65.Size = new Size(61, 20);
            this.textBox65.TabIndex = 50;
            this.label65.AutoSize = true;
            this.label65.Location = new Point(15, 153);
            this.label65.Name = "label65";
            this.label65.Size = new Size(47, 13);
            this.label65.TabIndex = 51;
            this.label65.Text = "Option5:";
            this.textBox64.BorderStyle = BorderStyle.FixedSingle;
            this.textBox64.Location = new Point(68, 124);
            this.textBox64.Name = "textBox64";
            this.textBox64.Size = new Size(61, 20);
            this.textBox64.TabIndex = 48;
            this.label64.AutoSize = true;
            this.label64.Location = new Point(15, 126);
            this.label64.Name = "label64";
            this.label64.Size = new Size(47, 13);
            this.label64.TabIndex = 49;
            this.label64.Text = "Option4:";
            this.textBox63.BorderStyle = BorderStyle.FixedSingle;
            this.textBox63.Location = new Point(68, 98);
            this.textBox63.Name = "textBox63";
            this.textBox63.Size = new Size(61, 20);
            this.textBox63.TabIndex = 46;
            this.label63.AutoSize = true;
            this.label63.Location = new Point(15, 100);
            this.label63.Name = "label63";
            this.label63.Size = new Size(47, 13);
            this.label63.TabIndex = 47;
            this.label63.Text = "Option3:";
            this.textBox62.BorderStyle = BorderStyle.FixedSingle;
            this.textBox62.Location = new Point(68, 72);
            this.textBox62.Name = "textBox62";
            this.textBox62.Size = new Size(61, 20);
            this.textBox62.TabIndex = 44;
            this.label62.AutoSize = true;
            this.label62.Location = new Point(15, 74);
            this.label62.Name = "label62";
            this.label62.Size = new Size(47, 13);
            this.label62.TabIndex = 45;
            this.label62.Text = "Option2:";
            this.textBox61.BorderStyle = BorderStyle.FixedSingle;
            this.textBox61.Location = new Point(68, 46);
            this.textBox61.Name = "textBox61";
            this.textBox61.Size = new Size(61, 20);
            this.textBox61.TabIndex = 42;
            this.label61.AutoSize = true;
            this.label61.Location = new Point(15, 48);
            this.label61.Name = "label61";
            this.label61.Size = new Size(47, 13);
            this.label61.TabIndex = 43;
            this.label61.Text = "Option1:";
            this.textBox60.BorderStyle = BorderStyle.FixedSingle;
            this.textBox60.Location = new Point(68, 20);
            this.textBox60.Name = "textBox60";
            this.textBox60.Size = new Size(61, 20);
            this.textBox60.TabIndex = 40;
            this.label60.AutoSize = true;
            this.label60.Location = new Point(15, 22);
            this.label60.Name = "label60";
            this.label60.Size = new Size(47, 13);
            this.label60.TabIndex = 41;
            this.label60.Text = "Option0:";
            this.LblPercent3.AutoSize = true;
            this.LblPercent3.Font = new Font("Consolas", 9.75f, FontStyle.Regular, GraphicsUnit.Point, (byte)0);
            this.LblPercent3.Location = new Point(409, 144);
            this.LblPercent3.Name = "LblPercent3";
            this.LblPercent3.Size = new Size(14, 15);
            this.LblPercent3.TabIndex = 41;
            this.LblPercent3.Text = "%";
            this.LblNote.AutoSize = true;
            this.LblNote.ForeColor = Color.Red;
            this.LblNote.Location = new Point(560, 383);
            this.LblNote.Name = "LblNote";
            this.LblNote.Size = new Size(275, 13);
            this.LblNote.TabIndex = 7;
            this.LblNote.Text = "Note: Probability 10,000 = 100% chance to achieve seal ";
            this.label20.AutoSize = true;
            this.label20.ForeColor = Color.Red;
            this.label20.Location = new Point(560, 366);
            this.label20.Name = "label20";
            this.label20.Size = new Size(225, 13);
            this.label20.TabIndex = 6;
            this.label20.Text = "Type Info - 0 = Weapon , 1 = Armor , 2 = Accs";
            this.label6.AutoSize = true;
            this.label6.ForeColor = Color.Red;
            this.label6.Location = new Point(560, 345);
            this.label6.Name = "label6";
            this.label6.Size = new Size(343, 13);
            this.label6.TabIndex = 5;
            this.label6.Text = "Grade Info - 0 = Blue ,1= Green , 2= Yellow,3 = White bonus, 4 = White";
            this.groupBox3.Controls.Add((Control)this.TbSeal7);
            this.groupBox3.Controls.Add((Control)this.TbSeal6);
            this.groupBox3.Controls.Add((Control)this.TbSeal9);
            this.groupBox3.Controls.Add((Control)this.TbSeal8);
            this.groupBox3.Controls.Add((Control)this.TbSeal5);
            this.groupBox3.Controls.Add((Control)this.TbSeal4);
            this.groupBox3.Controls.Add((Control)this.TbSeal3);
            this.groupBox3.Controls.Add((Control)this.TbSeal2);
            this.groupBox3.Controls.Add((Control)this.TbSeal1);
            this.groupBox3.Controls.Add((Control)this.TbSeal0);
            this.groupBox3.Controls.Add((Control)this.LblPercent4);
            this.groupBox3.Controls.Add((Control)this.LblPercent2);
            this.groupBox3.Controls.Add((Control)this.LblPercent1);
            this.groupBox3.Controls.Add((Control)this.TbPercent4);
            this.groupBox3.Controls.Add((Control)this.TbPercent3);
            this.groupBox3.Controls.Add((Control)this.TbPercent2);
            this.groupBox3.Controls.Add((Control)this.TbPercent1);
            this.groupBox3.Controls.Add((Control)this.btnPercentAddResist);
            this.groupBox3.Controls.Add((Control)this.btnPercentAddMattk);
            this.groupBox3.Controls.Add((Control)this.btnPercentAddDef);
            this.groupBox3.Controls.Add((Control)this.btnPercentAddAttk);
            this.groupBox3.Controls.Add((Control)this.TbType);
            this.groupBox3.Controls.Add((Control)this.TbGrade);
            this.groupBox3.Controls.Add((Control)this.PbAcc);
            this.groupBox3.Controls.Add((Control)this.PbArmor);
            this.groupBox3.Controls.Add((Control)this.PbWeapon);
            this.groupBox3.Controls.Add((Control)this.rstxt);
            this.groupBox3.Controls.Add((Control)this.label9);
            this.groupBox3.Controls.Add((Control)this.tdrop);
            this.groupBox3.Controls.Add((Control)this.label8);
            this.groupBox3.Controls.Add((Control)this.gdrop);
            this.groupBox3.Controls.Add((Control)this.label7);
            this.groupBox3.Controls.Add((Control)this.mtktxt);
            this.groupBox3.Controls.Add((Control)this.label5);
            this.groupBox3.Controls.Add((Control)this.deftxt);
            this.groupBox3.Controls.Add((Control)this.label4);
            this.groupBox3.Controls.Add((Control)this.atktxt);
            this.groupBox3.Controls.Add((Control)this.label3);
            this.groupBox3.Controls.Add((Control)this.nametxt);
            this.groupBox3.Controls.Add((Control)this.label2);
            this.groupBox3.Controls.Add((Control)this.idtxt);
            this.groupBox3.Controls.Add((Control)this.label1);
            this.groupBox3.Location = new Point(192, 15);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new Size(234, 314);
            this.groupBox3.TabIndex = 2;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Info";
            this.TbSeal7.Location = new Point(209, 258);
            this.TbSeal7.Name = "TbSeal7";
            this.TbSeal7.Size = new Size(23, 20);
            this.TbSeal7.TabIndex = 52;
            this.TbSeal7.Visible = false;
            this.TbSeal6.Location = new Point(180, 258);
            this.TbSeal6.Name = "TbSeal6";
            this.TbSeal6.Size = new Size(23, 20);
            this.TbSeal6.TabIndex = 51;
            this.TbSeal6.Visible = false;
            this.TbSeal9.Location = new Point(209, 287);
            this.TbSeal9.Name = "TbSeal9";
            this.TbSeal9.Size = new Size(23, 20);
            this.TbSeal9.TabIndex = 50;
            this.TbSeal9.Visible = false;
            this.TbSeal8.Location = new Point(180, 287);
            this.TbSeal8.Name = "TbSeal8";
            this.TbSeal8.Size = new Size(23, 20);
            this.TbSeal8.TabIndex = 49;
            this.TbSeal8.Visible = false;
            this.TbSeal5.Location = new Point(152, 286);
            this.TbSeal5.Name = "TbSeal5";
            this.TbSeal5.Size = new Size(23, 20);
            this.TbSeal5.TabIndex = 48;
            this.TbSeal5.Visible = false;
            this.TbSeal4.Location = new Point(123, 286);
            this.TbSeal4.Name = "TbSeal4";
            this.TbSeal4.Size = new Size(23, 20);
            this.TbSeal4.TabIndex = 47;
            this.TbSeal4.Visible = false;
            this.TbSeal3.Location = new Point(94, 286);
            this.TbSeal3.Name = "TbSeal3";
            this.TbSeal3.Size = new Size(23, 20);
            this.TbSeal3.TabIndex = 46;
            this.TbSeal3.Visible = false;
            this.TbSeal2.Location = new Point(65, 286);
            this.TbSeal2.Name = "TbSeal2";
            this.TbSeal2.Size = new Size(23, 20);
            this.TbSeal2.TabIndex = 45;
            this.TbSeal2.Visible = false;
            this.TbSeal1.Location = new Point(36, 286);
            this.TbSeal1.Name = "TbSeal1";
            this.TbSeal1.Size = new Size(23, 20);
            this.TbSeal1.TabIndex = 44;
            this.TbSeal1.Visible = false;
            this.TbSeal0.Location = new Point(7, 286);
            this.TbSeal0.Name = "TbSeal0";
            this.TbSeal0.Size = new Size(23, 20);
            this.TbSeal0.TabIndex = 43;
            this.TbSeal0.Visible = false;
            this.LblPercent4.AutoSize = true;
            this.LblPercent4.Font = new Font("Consolas", 9.75f, FontStyle.Regular, GraphicsUnit.Point, (byte)0);
            this.LblPercent4.Location = new Point(217, 155);
            this.LblPercent4.Name = "LblPercent4";
            this.LblPercent4.Size = new Size(14, 15);
            this.LblPercent4.TabIndex = 42;
            this.LblPercent4.Text = "%";
            this.LblPercent2.AutoSize = true;
            this.LblPercent2.Font = new Font("Consolas", 9.75f, FontStyle.Regular, GraphicsUnit.Point, (byte)0);
            this.LblPercent2.Location = new Point(217, 104);
            this.LblPercent2.Name = "LblPercent2";
            this.LblPercent2.Size = new Size(14, 15);
            this.LblPercent2.TabIndex = 40;
            this.LblPercent2.Text = "%";
            this.LblPercent1.AutoSize = true;
            this.LblPercent1.Font = new Font("Consolas", 9.75f, FontStyle.Regular, GraphicsUnit.Point, (byte)0);
            this.LblPercent1.Location = new Point(217, 76);
            this.LblPercent1.Name = "LblPercent1";
            this.LblPercent1.Size = new Size(14, 15);
            this.LblPercent1.TabIndex = 39;
            this.LblPercent1.Text = "%";
            this.TbPercent4.Location = new Point(180, 152);
            this.TbPercent4.Name = "TbPercent4";
            this.TbPercent4.Size = new Size(33, 20);
            this.TbPercent4.TabIndex = 38;
            this.TbPercent4.KeyPress += new KeyPressEventHandler(this.TbPercent4_KeyPress);
            this.TbPercent3.Location = new Point(180, 125);
            this.TbPercent3.Name = "TbPercent3";
            this.TbPercent3.Size = new Size(33, 20);
            this.TbPercent3.TabIndex = 37;
            this.TbPercent3.KeyPress += new KeyPressEventHandler(this.TbPercent3_KeyPress);
            this.TbPercent2.Location = new Point(180, 100);
            this.TbPercent2.Name = "TbPercent2";
            this.TbPercent2.Size = new Size(33, 20);
            this.TbPercent2.TabIndex = 36;
            this.TbPercent2.KeyPress += new KeyPressEventHandler(this.TbPercent2_KeyPress);
            this.TbPercent1.Location = new Point(180, 72);
            this.TbPercent1.Name = "TbPercent1";
            this.TbPercent1.Size = new Size(33, 20);
            this.TbPercent1.TabIndex = 35;
            this.TbPercent1.KeyPress += new KeyPressEventHandler(this.TbPercent1_KeyPress);
            this.btnPercentAddResist.Location = new Point(154, 152);
            this.btnPercentAddResist.Name = "btnPercentAddResist";
            this.btnPercentAddResist.Size = new Size(19, 20);
            this.btnPercentAddResist.TabIndex = 34;
            this.btnPercentAddResist.Text = "+";
            this.btnPercentAddResist.UseVisualStyleBackColor = true;
            this.btnPercentAddResist.Click += new EventHandler(this.BtnPercentAddResist_Click);
            this.btnPercentAddMattk.Location = new Point(154, 126);
            this.btnPercentAddMattk.Name = "btnPercentAddMattk";
            this.btnPercentAddMattk.Size = new Size(19, 20);
            this.btnPercentAddMattk.TabIndex = 33;
            this.btnPercentAddMattk.Text = "+";
            this.btnPercentAddMattk.UseVisualStyleBackColor = true;
            this.btnPercentAddMattk.Click += new EventHandler(this.BtnPercentAddMattk_Click);
            this.btnPercentAddDef.Location = new Point(154, 99);
            this.btnPercentAddDef.Name = "btnPercentAddDef";
            this.btnPercentAddDef.Size = new Size(19, 20);
            this.btnPercentAddDef.TabIndex = 32;
            this.btnPercentAddDef.Text = "+";
            this.btnPercentAddDef.UseVisualStyleBackColor = true;
            this.btnPercentAddDef.Click += new EventHandler(this.BtnPercentAddDef_Click);
            this.btnPercentAddAttk.Location = new Point(154, 73);
            this.btnPercentAddAttk.Name = "btnPercentAddAttk";
            this.btnPercentAddAttk.Size = new Size(19, 20);
            this.btnPercentAddAttk.TabIndex = 31;
            this.btnPercentAddAttk.Text = "+";
            this.btnPercentAddAttk.UseVisualStyleBackColor = true;
            this.btnPercentAddAttk.Click += new EventHandler(this.BtnPercentAddAttk_Click);
            this.TbType.Location = new Point(154, 213);
            this.TbType.Name = "TbType";
            this.TbType.Size = new Size(29, 20);
            this.TbType.TabIndex = 25;
            this.TbType.Visible = false;
            this.TbType.TextChanged += new EventHandler(this.TbType_TextChanged);
            this.TbGrade.Location = new Point(154, 182);
            this.TbGrade.Name = "TbGrade";
            this.TbGrade.Size = new Size(29, 20);
            this.TbGrade.TabIndex = 24;
            this.TbGrade.Visible = false;
            this.PbAcc.BackgroundImage = (Image)Resources.accessory;
            this.PbAcc.BackgroundImageLayout = ImageLayout.Center;
            this.PbAcc.Location = new Point(124, 241);
            this.PbAcc.Name = "PbAcc";
            this.PbAcc.Size = new Size(39, 38);
            this.PbAcc.TabIndex = 23;
            this.PbAcc.TabStop = false;
            this.PbAcc.Click += new EventHandler(this.PbAcc_Click);
            this.PbArmor.BackColor = SystemColors.Control;
            this.PbArmor.BackgroundImage = (Image)Resources.button10_BackgroundImage;
            this.PbArmor.BackgroundImageLayout = ImageLayout.Center;
            this.PbArmor.Location = new Point(71, 240);
            this.PbArmor.Name = "PbArmor";
            this.PbArmor.Size = new Size(39, 38);
            this.PbArmor.TabIndex = 22;
            this.PbArmor.TabStop = false;
            this.PbArmor.Click += new EventHandler(this.PbArmor_Click);
            this.PbWeapon.BackColor = SystemColors.Control;
            this.PbWeapon.BackgroundImage = (Image)Resources.weapon;
            this.PbWeapon.BackgroundImageLayout = ImageLayout.Center;
            this.PbWeapon.Location = new Point(20, 241);
            this.PbWeapon.Name = "PbWeapon";
            this.PbWeapon.Size = new Size(39, 38);
            this.PbWeapon.TabIndex = 21;
            this.PbWeapon.TabStop = false;
            this.PbWeapon.Click += new EventHandler(this.PbWeapon_Click);
            this.rstxt.Location = new Point(49, 150);
            this.rstxt.Name = "rstxt";
            this.rstxt.Size = new Size(100, 20);
            this.rstxt.TabIndex = 17;
            this.rstxt.KeyPress += new KeyPressEventHandler(this.Rstxt_KeyPress);
            this.label9.AutoSize = true;
            this.label9.Location = new Point(7, 155);
            this.label9.Name = "label9";
            this.label9.Size = new Size(36, 13);
            this.label9.TabIndex = 16;
            this.label9.Text = "Resist";
            this.tdrop.FormattingEnabled = true;
            this.tdrop.Location = new Point(48, 209);
            this.tdrop.Name = "tdrop";
            this.tdrop.Size = new Size(100, 21);
            this.tdrop.TabIndex = 15;
            this.tdrop.SelectedIndexChanged += new EventHandler(this.Tdrop_SelectedIndexChanged);
            this.tdrop.KeyPress += new KeyPressEventHandler(this.Tdrop_KeyPress);
            this.label8.AutoSize = true;
            this.label8.Location = new Point(7, 213);
            this.label8.Name = "label8";
            this.label8.Size = new Size(31, 13);
            this.label8.TabIndex = 14;
            this.label8.Text = "Type";
            this.gdrop.FormattingEnabled = true;
            this.gdrop.Location = new Point(48, 182);
            this.gdrop.Name = "gdrop";
            this.gdrop.Size = new Size(100, 21);
            this.gdrop.TabIndex = 13;
            this.gdrop.SelectedIndexChanged += new EventHandler(this.Gdrop_SelectedIndexChanged);
            this.gdrop.KeyPress += new KeyPressEventHandler(this.Gdrop_KeyPress);
            this.label7.AutoSize = true;
            this.label7.Location = new Point(7, 186);
            this.label7.Name = "label7";
            this.label7.Size = new Size(36, 13);
            this.label7.TabIndex = 12;
            this.label7.Text = "Grade";
            this.mtktxt.Location = new Point(48, 124);
            this.mtktxt.Name = "mtktxt";
            this.mtktxt.Size = new Size(100, 20);
            this.mtktxt.TabIndex = 9;
            this.mtktxt.KeyPress += new KeyPressEventHandler(this.Mtktxt_KeyPress);
            this.label5.AutoSize = true;
            this.label5.Location = new Point(6, 129);
            this.label5.Name = "label5";
            this.label5.Size = new Size(32, 13);
            this.label5.TabIndex = 8;
            this.label5.Text = "MAtk";
            this.deftxt.Location = new Point(48, 98);
            this.deftxt.Name = "deftxt";
            this.deftxt.Size = new Size(100, 20);
            this.deftxt.TabIndex = 7;
            this.deftxt.KeyPress += new KeyPressEventHandler(this.Deftxt_KeyPress);
            this.label4.AutoSize = true;
            this.label4.Location = new Point(6, 103);
            this.label4.Name = "label4";
            this.label4.Size = new Size(24, 13);
            this.label4.TabIndex = 6;
            this.label4.Text = "Def";
            this.atktxt.Location = new Point(48, 72);
            this.atktxt.Name = "atktxt";
            this.atktxt.Size = new Size(100, 20);
            this.atktxt.TabIndex = 5;
            this.atktxt.KeyPress += new KeyPressEventHandler(this.Atktxt_KeyPress);
            this.label3.AutoSize = true;
            this.label3.Location = new Point(6, 77);
            this.label3.Name = "label3";
            this.label3.Size = new Size(23, 13);
            this.label3.TabIndex = 4;
            this.label3.Text = "Atk";
            this.nametxt.Location = new Point(48, 46);
            this.nametxt.Name = "nametxt";
            this.nametxt.Size = new Size(180, 20);
            this.nametxt.TabIndex = 3;
            this.nametxt.KeyPress += new KeyPressEventHandler(this.Nametxt_KeyPress);
            this.label2.AutoSize = true;
            this.label2.Location = new Point(6, 51);
            this.label2.Name = "label2";
            this.label2.Size = new Size(35, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Name";
            this.idtxt.Location = new Point(48, 20);
            this.idtxt.Name = "idtxt";
            this.idtxt.Size = new Size(48, 20);
            this.idtxt.TabIndex = 1;
            this.idtxt.KeyPress += new KeyPressEventHandler(this.Idtxt_KeyPress);
            this.label1.AutoSize = true;
            this.label1.Location = new Point(6, 25);
            this.label1.Name = "label1";
            this.label1.Size = new Size(18, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "ID";
            this.groupBox2.Controls.Add((Control)this.button1);
            this.groupBox2.Controls.Add((Control)this.UpdateButton);
            this.groupBox2.Controls.Add((Control)this.remove);
            this.groupBox2.Location = new Point(192, 336);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new Size(273, 60);
            this.groupBox2.TabIndex = 1;
            this.groupBox2.TabStop = false;
            this.button1.BackColor = Color.Plum;
            this.button1.FlatStyle = FlatStyle.Flat;
            this.button1.Image = (Image)Resources.control_add_blue;
            this.button1.ImageAlign = ContentAlignment.MiddleLeft;
            this.button1.Location = new Point(180, 20);
            this.button1.Name = "button1";
            this.button1.Size = new Size(77, 27);
            this.button1.TabIndex = 63;
            this.button1.Text = "     Add";
            this.button1.UseVisualStyleBackColor = false;
            this.button1.Click += new EventHandler(this.Button1_Click);
            this.UpdateButton.BackColor = Color.LightCyan;
            this.UpdateButton.FlatStyle = FlatStyle.Flat;
            this.UpdateButton.Image = (Image)Resources._08;
            this.UpdateButton.ImageAlign = ContentAlignment.MiddleLeft;
            this.UpdateButton.Location = new Point(95, 20);
            this.UpdateButton.Name = "UpdateButton";
            this.UpdateButton.Size = new Size(72, 27);
            this.UpdateButton.TabIndex = 102;
            this.UpdateButton.Text = "      Update";
            this.UpdateButton.UseVisualStyleBackColor = false;
            this.UpdateButton.Click += new EventHandler(this.UpdateButton_Click);
            this.remove.BackColor = Color.LightCoral;
            this.remove.FlatStyle = FlatStyle.Flat;
            this.remove.Image = (Image)Resources.delete;
            this.remove.ImageAlign = ContentAlignment.MiddleLeft;
            this.remove.Location = new Point(17, 20);
            this.remove.Name = "remove";
            this.remove.Size = new Size(65, 27);
            this.remove.TabIndex = 103;
            this.remove.Text = "    Delete";
            this.remove.UseVisualStyleBackColor = false;
            this.remove.Click += new EventHandler(this.Remove_Click);
            this.listBox1.FormattingEnabled = true;
            this.listBox1.Location = new Point(7, 15);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new Size(172, 381);
            this.listBox1.TabIndex = 0;
            this.listBox1.SelectedIndexChanged += new EventHandler(this.ListBox1_SelectedIndexChanged);
            this.AutoScaleDimensions = new SizeF(6f, 13f);
            this.AutoScaleMode = AutoScaleMode.Font;
            this.ClientSize = new Size(1216, 457);
            this.Controls.Add((Control)this.groupBox1);
            this.Controls.Add((Control)this.toolStrip1);
            this.Icon = (Icon)componentResourceManager.GetObject("$this.Icon");
            this.Name = nameof(RareOptionEditor);
            this.Text = "RareOptionEditor Fixed By kimpobin";
            this.Load += new EventHandler(this.RareOptionEditor_Load);
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox17.ResumeLayout(false);
            this.groupBox17.PerformLayout();
            this.groupBox13.ResumeLayout(false);
            this.groupBox13.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            ((ISupportInitialize)this.PbAcc).EndInit();
            ((ISupportInitialize)this.PbArmor).EndInit();
            ((ISupportInitialize)this.PbWeapon).EndInit();
            this.groupBox2.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();
        }

        private void rareOptionlodToolStripMenuItem_Click(object sender, EventArgs e)
        {
            new LodExporter.LodExporter().Show();
        }

        private void strRareOptionusToolStripMenuItem_Click(object sender, EventArgs e)
        {
            new FormExport().Show();
        }
    }
}
