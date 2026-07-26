// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.TitleEditor
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using LcDevPack_TeamDamonA.Properties;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Globalization;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools
{
  public class TitleEditor : Form
  {
    public static Connection connection = new Connection();
    private string Host = TitleEditor.connection.Settings.SqlHost;
    private string User = TitleEditor.connection.Settings.SqlUser;
    private string Password = TitleEditor.connection.Settings.SqlPassword;
    private string Database = TitleEditor.connection.Settings.SqlDatabase;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    public string rowName = "a_index";
    public string[] menuArray = new string[2]
    {
      "a_index",
      "a_name"
    };
    public string[] menuArray2 = new string[2]
    {
      "a_type",
      "a_name_usa"
    };
    private string language = TitleEditor.connection.Settings.Language;
    public string[] menuArrayGER = new string[2]
    {
      "a_type",
      "a_name_ger"
    };
    public string[] menuArrayPOL = new string[2]
    {
      "a_type",
      "a_name_pld"
    };
    public string[] menuArrayBRA = new string[2]
    {
      "a_type",
      "a_name_brz"
    };
    public string[] menuArrayRUS = new string[2]
    {
      "a_type",
      "a_name_rus"
    };
    public string[] menuArrayFRA = new string[2]
    {
      "a_type",
      "a_name_frc"
    };
    public string[] menuArrayESP = new string[2]
    {
      "a_type",
      "a_name_spn"
    };
    public string[] menuArrayMEX = new string[2]
    {
      "a_type",
      "a_name_mex"
    };
    public string[] menuArrayTHA = new string[2]
    {
      "a_type",
      "a_name_thai"
    };
    public string[] menuArrayITA = new string[2]
    {
      "a_type",
      "a_name_ita"
    };
    public string[] menuArrayUSA = new string[2]
    {
      "a_type",
      "a_name_usa"
    };
    private string namee;
    public string[] menuArray3 = new string[1]{ "a_level" };
    private ExportLodHandle exportLodHandle = new ExportLodHandle();
    private IContainer components = (IContainer) null;
    public System.Collections.Generic.List<string> List;
    public System.Collections.Generic.List<string> List2;
    public System.Collections.Generic.List<string> List3;
    public System.Collections.Generic.List<string> List4;
    public System.Collections.Generic.List<string> List5;
    public System.Collections.Generic.List<string> List6;
    public System.Collections.Generic.List<string> List7;
    public System.Collections.Generic.List<string> List8;
    public System.Collections.Generic.List<string> List9;
    public System.Collections.Generic.List<string> List10;
    public System.Collections.Generic.List<string> List11;
    public System.Collections.Generic.List<string> List12;
    public System.Collections.Generic.List<string> List13;
    public System.Collections.Generic.List<string> List14;
    public System.Collections.Generic.List<string> List15;
    public string name;
    public int index;
    private ListBox listBox1;
    private MenuStrip menuStrip1;
    private ToolStripMenuItem fileToolStripMenuItem;
    private ToolStripMenuItem exportlodToolStripMenuItem;
    private Button button1;
    private Button button2;
    private Button button3;
    private GroupBox groupBox1;
    private Label label26;
    private Label label3;
    private Label label2;
    private TextBox textBox1;
    private Label label1;
    private GroupBox groupBox2;
    private Label label6;
    private Label label5;
    private Label label4;
    private GroupBox groupBox3;
    private GroupBox groupBox6;
    private Label label15;
    private GroupBox groupBox5;
    private TrackBar trackBar8;
    private TrackBar trackBar7;
    private TrackBar trackBar6;
    private TrackBar trackBar5;
    private Label label14;
    private Label label13;
    private Label label12;
    private Label label11;
    private GroupBox groupBox4;
    private TrackBar trackBar4;
    private TrackBar trackBar3;
    private TrackBar trackBar2;
    private TrackBar trackBar1;
    private Label label10;
    private Label label9;
    private Label label7;
    private Label label8;
    private TextBox textBox4;
    private TextBox textBox2;
    private TextBox textBox3;
    private TextBox textBox7;
    private TextBox textBox6;
    private TextBox textBox5;
    private Label label16;
    private Label label17;
    private TextBox textBox8;
    private TextBox textBox9;
    private TextBox textBox10;
    private GroupBox groupBox7;
    private TextBox textBox20;
    private TextBox textBox19;
    private TextBox textBox18;
    private TextBox textBox17;
    private TextBox textBox16;
    private TextBox textBox15;
    private TextBox textBox14;
    private TextBox textBox13;
    private TextBox textBox12;
    private TextBox textBox11;
    private TextBox textBox21;
    private Label label18;
    private TextBox textBox23;
    private TextBox textBox22;
    private Label label19;
    private TextBox textBox24;
    private TextBox textBox25;
    private TextBox textBox26;
    private TextBox textBox27;
    private TextBox textBox28;
    private TextBox textBox29;
    private TextBox textBox30;
    private TextBox textBox31;
    private ComboBox comboBox10;
    private ComboBox comboBox9;
    private ComboBox comboBox8;
    private ComboBox comboBox7;
    private ComboBox comboBox6;
    private ComboBox comboBox5;
    private ComboBox comboBox4;
    private ComboBox comboBox3;
    private ComboBox comboBox2;
    private Label label20;
    private Label label21;
    private Label label22;
    private Label label23;
    private Label label24;
    private ComboBox comboBox1;
    private TextBox textBox32;
    private TextBox textBox33;
    private TextBox textBox34;
    private TextBox textBox35;
    private TextBox textBox36;
    private GroupBox groupBox8;
    private TextBox textBox37;
    private Label label25;
    private GroupBox groupBox9;
    private Label label27;
    private PictureBox pictureBox1;
    private TextBox textBox38;
    private TextBox textBox39;
    private TextBox textBox40;
    private ToolStripMenuItem clickMeBeforeEditingTitlesToolStripMenuItem;
    private PictureBox PbSelectID1;
    private ToolStripMenuItem saveToolStripMenuItem;
    private Button button4;

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

    public TitleEditor() => this.InitializeComponent();

    public int GetIndex() => Convert.ToInt32(this.comboBox1.SelectedText.Split(' ')[0]);

    public Bitmap CropImage(Bitmap source, Rectangle section)
    {
      Bitmap bitmap = new Bitmap(section.Width, section.Height);
      Graphics.FromImage((Image) bitmap).DrawImage((Image) source, 0, 0, section, GraphicsUnit.Pixel);
      return bitmap;
    }

    public void cropIcon()
    {
      try
      {
        this.pictureBox1.Image = (Image) this.databaseHandle.IconFast(Convert.ToInt32(this.textBox21.Text));
      }
      catch
      {
      }
    }

    public void SearchList(string searchString)
    {
      searchString = searchString.Replace("\\", "\\\\").Replace("'", "\\'");
      this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, "select a_index, a_name from t_title WHERE a_name LIKE '%" + searchString + "%' ORDER BY a_index;");
    }

    private void Exporter_Title_Load(object sender, EventArgs e)
    {
      this.listBox1.Items.Clear();
      this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, "select a_index, a_name from t_title ORDER BY a_index;");
      this.ChangeColor();
      string Query = "select * from t_option ORDER BY a_index;";
      if (this.language == "THA")
      {
        this.List = this.databaseHandle.SelectMySqlReturnList(this.menuArrayTHA, this.Host, this.User, this.Password, this.Database, Query);
        this.List2 = this.databaseHandle.SelectMySqlReturnList(this.menuArrayTHA, this.Host, this.User, this.Password, this.Database, Query);
        this.List3 = this.databaseHandle.SelectMySqlReturnList(this.menuArrayTHA, this.Host, this.User, this.Password, this.Database, Query);
        this.List4 = this.databaseHandle.SelectMySqlReturnList(this.menuArrayTHA, this.Host, this.User, this.Password, this.Database, Query);
        this.List5 = this.databaseHandle.SelectMySqlReturnList(this.menuArrayTHA, this.Host, this.User, this.Password, this.Database, Query);
      }
      else
      {
        this.List = this.databaseHandle.SelectMySqlReturnList(this.menuArray2, this.Host, this.User, this.Password, this.Database, Query);
        this.List2 = this.databaseHandle.SelectMySqlReturnList(this.menuArray2, this.Host, this.User, this.Password, this.Database, Query);
        this.List3 = this.databaseHandle.SelectMySqlReturnList(this.menuArray2, this.Host, this.User, this.Password, this.Database, Query);
        this.List4 = this.databaseHandle.SelectMySqlReturnList(this.menuArray2, this.Host, this.User, this.Password, this.Database, Query);
        this.List5 = this.databaseHandle.SelectMySqlReturnList(this.menuArray2, this.Host, this.User, this.Password, this.Database, Query);
      }
      this.comboBox1.DataSource = (object) this.List;
      this.comboBox2.DataSource = (object) this.List2;
      this.comboBox3.DataSource = (object) this.List3;
      this.comboBox4.DataSource = (object) this.List4;
      this.comboBox5.DataSource = (object) this.List5;
      this.listBox1.SelectedIndex = 1;
      this.listBox1.SelectedIndex = 0;
    }

    public new void ResetBindings() => this.textBox1.DataBindings.Clear();

    public void ChangeColor()
    {
      int alpha1 = int.Parse(this.textBox27.Text);
      int red1 = int.Parse(this.textBox24.Text);
      int green1 = int.Parse(this.textBox25.Text);
      int blue1 = int.Parse(this.textBox26.Text);
      int alpha2 = int.Parse(this.textBox31.Text);
      int red2 = int.Parse(this.textBox28.Text);
      int green2 = int.Parse(this.textBox29.Text);
      int blue2 = int.Parse(this.textBox30.Text);
      string str1 = alpha1.ToString("X2");
      string str2 = red1.ToString("X2");
      string str3 = blue1.ToString("X2");
      string str4 = green1.ToString("X2");
      string str5 = alpha2.ToString("X2");
      string str6 = red2.ToString("X2");
      string str7 = blue2.ToString("X2");
      string str8 = green2.ToString("X2");
      string str9 = str2 + str4 + str3 + str1;
      this.textBox9.Text = str6 + str8 + str7 + str5;
      this.textBox10.Text = str9;
      Color color1 = Color.FromArgb(alpha1, red1, green1, blue1);
      Color color2 = Color.FromArgb(alpha2, red2, green2, blue2);
      this.label15.ForeColor = color1;
      this.label15.BackColor = color2;
    }

    private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.ResetBindings();
      if (this.listBox1.SelectedIndex != -1)
      {
        this.name = this.listBox1.SelectedItem.ToString();
        this.textBox1.Text = this.name;
      }
      string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, " select * FROM t_title WHERE a_index ='" + this.textBox1.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "';", new string[23]
      {
        "a_index",
        "a_name",
        "a_enable",
        "a_describe",
        "a_effect_name",
        "a_attack",
        "a_damage",
        "a_time",
        "a_bgcolor",
        "a_color",
        "a_option_index0",
        "a_option_level0",
        "a_option_index1",
        "a_option_level1",
        "a_option_index2",
        "a_option_level2",
        "a_option_index3",
        "a_option_level3",
        "a_option_index4",
        "a_option_level4",
        "a_item_index",
        "a_flag",
        "a_castle_num"
      });
      this.textBox1.Text = strArray[0];
      this.textBox3.Text = strArray[2];
      this.textBox4.Text = strArray[3];
      this.textBox5.Text = strArray[4];
      this.textBox6.Text = strArray[5];
      this.textBox7.Text = strArray[6];
      this.textBox8.Text = strArray[7];
      this.textBox9.Text = strArray[8];
      this.textBox10.Text = strArray[9];
      this.textBox11.Text = strArray[10];
      this.textBox12.Text = strArray[11];
      this.textBox13.Text = strArray[12];
      this.textBox14.Text = strArray[13];
      this.textBox15.Text = strArray[14];
      this.textBox16.Text = strArray[15];
      this.textBox17.Text = strArray[16];
      this.textBox18.Text = strArray[17];
      this.textBox19.Text = strArray[18];
      this.textBox20.Text = strArray[19];
      this.textBox21.Text = strArray[20];
      this.textBox22.Text = strArray[21];
      this.textBox23.Text = strArray[22];
      this.textBox2.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox21.Text));
      int num1 = int.Parse(strArray[9].Substring(0, strArray[9].Length - 6), NumberStyles.HexNumber);
      int num2 = int.Parse(strArray[9].Substring(2, strArray[9].Length - 6), NumberStyles.HexNumber);
      int num3 = int.Parse(strArray[9].Substring(4, strArray[9].Length - 6), NumberStyles.HexNumber);
      int num4 = int.Parse(strArray[9].Substring(6, strArray[9].Length - 6), NumberStyles.HexNumber);
      int num5 = int.Parse(strArray[8].Substring(0, strArray[8].Length - 6), NumberStyles.HexNumber);
      int num6 = int.Parse(strArray[8].Substring(2, strArray[8].Length - 6), NumberStyles.HexNumber);
      int num7 = int.Parse(strArray[8].Substring(4, strArray[8].Length - 6), NumberStyles.HexNumber);
      int num8 = int.Parse(strArray[8].Substring(6, strArray[8].Length - 6), NumberStyles.HexNumber);
      this.label15.Text = strArray[1];
      this.textBox24.Text = num1.ToString();
      this.textBox25.Text = num2.ToString();
      this.textBox26.Text = num3.ToString();
      this.textBox27.Text = num4.ToString();
      this.textBox28.Text = num5.ToString();
      this.textBox29.Text = num6.ToString();
      this.textBox30.Text = num7.ToString();
      this.textBox31.Text = num8.ToString();
      this.trackBar1.Value = int.Parse(this.textBox27.Text);
      this.trackBar2.Value = int.Parse(this.textBox24.Text);
      this.trackBar3.Value = int.Parse(this.textBox25.Text);
      this.trackBar4.Value = int.Parse(this.textBox26.Text);
      this.trackBar5.Value = int.Parse(this.textBox31.Text);
      this.trackBar6.Value = int.Parse(this.textBox28.Text);
      this.trackBar7.Value = int.Parse(this.textBox29.Text);
      this.trackBar8.Value = int.Parse(this.textBox30.Text);
      this.ChangeColor();
      this.comboBox1.SelectedIndex = int.Parse(this.textBox11.Text);
      this.comboBox2.SelectedIndex = int.Parse(this.textBox13.Text);
      this.comboBox3.SelectedIndex = int.Parse(this.textBox15.Text);
      this.comboBox4.SelectedIndex = int.Parse(this.textBox17.Text);
      this.comboBox5.SelectedIndex = int.Parse(this.textBox19.Text);
      string text1 = this.textBox11.Text;
      string text2 = this.textBox13.Text;
      string text3 = this.textBox15.Text;
      string text4 = this.textBox17.Text;
      string text5 = this.textBox19.Text;
      string Query1 = "select * from t_option WHERE a_type = '" + text1 + "' ORDER BY a_index;";
      string Query2 = "select * from t_option WHERE a_type = '" + text2 + "' ORDER BY a_index;";
      string Query3 = "select * from t_option WHERE a_type = '" + text3 + "' ORDER BY a_index;";
      string Query4 = "select * from t_option WHERE a_type = '" + text4 + "' ORDER BY a_index;";
      string Query5 = "select * from t_option WHERE a_type = '" + text5 + "' ORDER BY a_index;";
      this.List6 = this.databaseHandle.SelectMySqlExplodedReturnList(this.menuArray3, this.Host, this.User, this.Password, this.Database, Query1);
      this.List7 = this.databaseHandle.SelectMySqlExplodedReturnList(this.menuArray3, this.Host, this.User, this.Password, this.Database, Query2);
      this.List8 = this.databaseHandle.SelectMySqlExplodedReturnList(this.menuArray3, this.Host, this.User, this.Password, this.Database, Query3);
      this.List9 = this.databaseHandle.SelectMySqlExplodedReturnList(this.menuArray3, this.Host, this.User, this.Password, this.Database, Query4);
      this.List10 = this.databaseHandle.SelectMySqlExplodedReturnList(this.menuArray3, this.Host, this.User, this.Password, this.Database, Query5);
      this.comboBox6.DataSource = (object) this.List6;
      this.comboBox7.DataSource = (object) this.List7;
      this.comboBox8.DataSource = (object) this.List8;
      this.comboBox9.DataSource = (object) this.List9;
      this.comboBox10.DataSource = (object) this.List10;
      try
      {
        this.comboBox6.SelectedIndex = int.Parse(this.textBox12.Text) - 1;
        this.comboBox7.SelectedIndex = int.Parse(this.textBox14.Text) - 1;
        this.comboBox8.SelectedIndex = int.Parse(this.textBox16.Text) - 1;
        this.comboBox9.SelectedIndex = int.Parse(this.textBox18.Text) - 1;
        this.comboBox10.SelectedIndex = int.Parse(this.textBox20.Text) - 1;
      }
      catch
      {
      }
      this.cropIcon();
      this.label27.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox21.Text));
    }

    private void trackBar1_Scroll(object sender, EventArgs e)
    {
      this.textBox27.Text = this.trackBar1.Value.ToString();
      this.ChangeColor();
    }

    private void trackBar2_Scroll(object sender, EventArgs e)
    {
      this.textBox24.Text = this.trackBar2.Value.ToString();
      this.ChangeColor();
    }

    private void trackBar3_Scroll(object sender, EventArgs e)
    {
      this.textBox25.Text = this.trackBar3.Value.ToString();
      this.ChangeColor();
    }

    private void trackBar4_Scroll(object sender, EventArgs e)
    {
      this.textBox26.Text = this.trackBar4.Value.ToString();
      this.ChangeColor();
    }

    private void trackBar5_Scroll(object sender, EventArgs e)
    {
      this.textBox31.Text = this.trackBar5.Value.ToString();
      this.ChangeColor();
    }

    private void trackBar6_Scroll(object sender, EventArgs e)
    {
      this.textBox28.Text = this.trackBar6.Value.ToString();
      this.ChangeColor();
    }

    private void trackBar7_Scroll(object sender, EventArgs e)
    {
      this.textBox29.Text = this.trackBar7.Value.ToString();
      this.ChangeColor();
    }

    private void trackBar8_Scroll(object sender, EventArgs e)
    {
      this.textBox30.Text = this.trackBar8.Value.ToString();
      this.ChangeColor();
    }

    private void textBox2_TextChanged(object sender, EventArgs e)
    {
    }

    private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox11.Text = this.comboBox1.SelectedIndex.ToString();
      this.List11 = this.databaseHandle.SelectMySqlExplodedReturnList(this.menuArray3, this.Host, this.User, this.Password, this.Database, "select * from t_option WHERE a_type = '" + this.textBox11.Text + "' ORDER BY a_index;");
      this.comboBox6.DataSource = (object) null;
      this.comboBox6.Items.Clear();
      this.comboBox6.DataSource = (object) this.List11;
    }

    private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox13.Text = this.comboBox2.SelectedIndex.ToString();
      this.List12 = this.databaseHandle.SelectMySqlExplodedReturnList(this.menuArray3, this.Host, this.User, this.Password, this.Database, "select * from t_option WHERE a_type = '" + this.textBox13.Text + "' ORDER BY a_index;");
      this.comboBox7.DataSource = (object) null;
      this.comboBox7.Items.Clear();
      this.comboBox7.DataSource = (object) this.List12;
    }

    private void comboBox3_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox15.Text = this.comboBox3.SelectedIndex.ToString();
      this.List13 = this.databaseHandle.SelectMySqlExplodedReturnList(this.menuArray3, this.Host, this.User, this.Password, this.Database, "select * from t_option WHERE a_type = '" + this.textBox15.Text + "' ORDER BY a_index;");
      this.comboBox8.DataSource = (object) null;
      this.comboBox8.Items.Clear();
      this.comboBox8.DataSource = (object) this.List13;
    }

    private void comboBox4_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox17.Text = this.comboBox4.SelectedIndex.ToString();
      this.List14 = this.databaseHandle.SelectMySqlExplodedReturnList(this.menuArray3, this.Host, this.User, this.Password, this.Database, "select * from t_option WHERE a_type = '" + this.textBox17.Text + "' ORDER BY a_index;");
      this.comboBox9.DataSource = (object) null;
      this.comboBox9.Items.Clear();
      this.comboBox9.DataSource = (object) this.List14;
    }

    private void comboBox5_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox19.Text = this.comboBox5.SelectedIndex.ToString();
      this.List15 = this.databaseHandle.SelectMySqlExplodedReturnList(this.menuArray3, this.Host, this.User, this.Password, this.Database, "select * from t_option WHERE a_type = '" + this.textBox19.Text + "' ORDER BY a_index;");
      this.comboBox10.DataSource = (object) null;
      this.comboBox10.Items.Clear();
      this.comboBox10.DataSource = (object) this.List15;
    }

    private void comboBox6_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox36.Text = (this.comboBox6.SelectedIndex + 1).ToString();
    }

    private void comboBox7_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox35.Text = (this.comboBox7.SelectedIndex + 1).ToString();
    }

    private void comboBox8_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox34.Text = (this.comboBox8.SelectedIndex + 1).ToString();
    }

    private void comboBox9_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox33.Text = (this.comboBox9.SelectedIndex + 1).ToString();
    }

    private void comboBox10_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox32.Text = (this.comboBox10.SelectedIndex + 1).ToString();
    }

    private void textBox12_TextChanged(object sender, EventArgs e)
    {
    }

    private void textBox36_TextChanged(object sender, EventArgs e)
    {
    }

    private string EncodeMySqlString(string value) => value = value.Replace("'", "'");

    private void button3_Click(object sender, EventArgs e)
    {
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_title SET a_name = '" + this.textBox2.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_enable = '" + this.textBox3.Text + "', a_describe = '" + this.textBox4.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_effect_Name = '" + this.textBox5.Text + "', a_attack = '" + this.textBox6.Text + "', a_damage = '" + this.textBox7.Text + "', a_time = '" + this.textBox8.Text + "', a_bgcolor = '" + this.textBox9.Text + "', a_color = '" + this.textBox10.Text + "', a_option_index0 = '" + this.textBox11.Text + "', a_option_level0 = '" + this.textBox36.Text + "', a_option_index1 = '" + this.textBox13.Text + "', a_option_level1 = '" + this.textBox35.Text + "', a_option_index2 = '" + this.textBox15.Text + "', a_option_level2 = '" + this.textBox34.Text + "', a_option_index3 = '" + this.textBox17.Text + "', a_option_level3 = '" + this.textBox33.Text + "', a_option_index4 = '" + this.textBox19.Text + "', a_option_level4 = '" + this.textBox32.Text + "', a_item_index = '" + this.textBox21.Text + "', a_flag = '" + this.textBox22.Text + "', a_castle_num = '" + this.textBox23.Text + "' WHERE a_index ='" + this.textBox1.Text + "';");
      this.cropIcon();
      int selectedIndex = this.listBox1.SelectedIndex;
      if (this.textBox37.Text != "")
        this.SearchList(this.textBox12.Text);
      else
        this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, "select * from t_title ORDER BY a_index;");
      this.listBox1.SelectedIndex = selectedIndex;
      int num = (int) new CustomMessage("Done :)").ShowDialog();
    }

    private void button1_Click(object sender, EventArgs e)
    {
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_title (a_name, a_enable, a_bgcolor, a_color) VALUES ('New Title', '1', 'FFFFFFFF', '000000FF')");
      this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, "select * from t_title ORDER BY a_index;");
      this.listBox1.SelectedIndex = this.listBox1.Items.Count - 1;
    }

    private void button2_Click(object sender, EventArgs e)
    {
      int selectedIndex = this.listBox1.SelectedIndex;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_title WHERE a_index = '" + this.textBox1.Text + "'");
      this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, "select * from t_title ORDER BY a_index;");
      this.listBox1.SelectedIndex = selectedIndex - 1;
      int num = (int) new CustomMessage("Deleted :O").ShowDialog();
    }

    private void textBox37_TextChanged(object sender, EventArgs e)
    {
      this.SearchList(this.textBox37.Text);
    }

    private void exportlodToolStripMenuItem_Click(object sender, EventArgs e)
    {
      new LodExporter.LodExporter().Show();
    }

    private void menuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
    {
    }

    private void textBox10_TextChanged(object sender, EventArgs e)
    {
    }

    private void textBox9_TextChanged(object sender, EventArgs e)
    {
    }

    private void textBox24_TextChanged(object sender, EventArgs e)
    {
    }

    private void button4_Click(object sender, EventArgs e)
    {
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DROP TABLE IF EXISTS tempTable;CREATE TEMPORARY TABLE tempTable ENGINE=MEMORY SELECT * FROM t_title WHERE a_index=" + this.textBox1.Text + ";SELECT a_index FROM tempTable;UPDATE tempTable SET a_index=(SELECT a_index from t_title ORDER BY a_index DESC LIMIT 1)+1; SELECT a_index FROM tempTable;INSERT INTO t_title SELECT * FROM tempTable;");
      this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, "select * from t_title ORDER BY a_index;");
      this.listBox1.SelectedIndex = this.listBox1.Items.Count - 1;
      int num = (int) new CustomMessage("Copying Complete !!").ShowDialog();
    }

    private void textBox21_TextChanged(object sender, EventArgs e)
    {
      this.label27.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.textBox21.Text));
      if (!(this.textBox21.Text != ""))
        return;
      this.pictureBox1.Image = (Image) this.databaseHandle.IconFast(Convert.ToInt32(this.textBox21.Text));
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (TitleEditor));
      this.listBox1 = new ListBox();
      this.menuStrip1 = new MenuStrip();
      this.fileToolStripMenuItem = new ToolStripMenuItem();
      this.exportlodToolStripMenuItem = new ToolStripMenuItem();
      this.clickMeBeforeEditingTitlesToolStripMenuItem = new ToolStripMenuItem();
      this.button1 = new Button();
      this.button2 = new Button();
      this.button3 = new Button();
      this.groupBox1 = new GroupBox();
      this.label19 = new Label();
      this.label18 = new Label();
      this.textBox23 = new TextBox();
      this.textBox22 = new TextBox();
      this.textBox8 = new TextBox();
      this.label17 = new Label();
      this.textBox3 = new TextBox();
      this.label16 = new Label();
      this.textBox2 = new TextBox();
      this.textBox4 = new TextBox();
      this.label26 = new Label();
      this.label2 = new Label();
      this.textBox1 = new TextBox();
      this.label1 = new Label();
      this.textBox21 = new TextBox();
      this.label3 = new Label();
      this.groupBox2 = new GroupBox();
      this.textBox7 = new TextBox();
      this.textBox6 = new TextBox();
      this.textBox5 = new TextBox();
      this.label6 = new Label();
      this.label5 = new Label();
      this.label4 = new Label();
      this.groupBox3 = new GroupBox();
      this.groupBox6 = new GroupBox();
      this.label15 = new Label();
      this.groupBox5 = new GroupBox();
      this.textBox9 = new TextBox();
      this.trackBar8 = new TrackBar();
      this.trackBar7 = new TrackBar();
      this.trackBar6 = new TrackBar();
      this.trackBar5 = new TrackBar();
      this.label14 = new Label();
      this.label13 = new Label();
      this.label12 = new Label();
      this.label11 = new Label();
      this.groupBox4 = new GroupBox();
      this.textBox10 = new TextBox();
      this.trackBar4 = new TrackBar();
      this.trackBar3 = new TrackBar();
      this.trackBar2 = new TrackBar();
      this.trackBar1 = new TrackBar();
      this.label10 = new Label();
      this.label9 = new Label();
      this.label7 = new Label();
      this.label8 = new Label();
      this.groupBox7 = new GroupBox();
      this.textBox32 = new TextBox();
      this.comboBox10 = new ComboBox();
      this.textBox33 = new TextBox();
      this.comboBox9 = new ComboBox();
      this.comboBox8 = new ComboBox();
      this.textBox34 = new TextBox();
      this.comboBox7 = new ComboBox();
      this.comboBox6 = new ComboBox();
      this.textBox35 = new TextBox();
      this.comboBox5 = new ComboBox();
      this.comboBox4 = new ComboBox();
      this.textBox36 = new TextBox();
      this.comboBox3 = new ComboBox();
      this.comboBox2 = new ComboBox();
      this.label20 = new Label();
      this.label21 = new Label();
      this.label22 = new Label();
      this.label23 = new Label();
      this.label24 = new Label();
      this.comboBox1 = new ComboBox();
      this.textBox19 = new TextBox();
      this.textBox17 = new TextBox();
      this.textBox15 = new TextBox();
      this.textBox13 = new TextBox();
      this.textBox11 = new TextBox();
      this.textBox14 = new TextBox();
      this.textBox12 = new TextBox();
      this.textBox16 = new TextBox();
      this.textBox20 = new TextBox();
      this.textBox18 = new TextBox();
      this.textBox24 = new TextBox();
      this.textBox25 = new TextBox();
      this.textBox26 = new TextBox();
      this.textBox27 = new TextBox();
      this.textBox28 = new TextBox();
      this.textBox29 = new TextBox();
      this.textBox30 = new TextBox();
      this.textBox31 = new TextBox();
      this.groupBox8 = new GroupBox();
      this.textBox37 = new TextBox();
      this.label25 = new Label();
      this.groupBox9 = new GroupBox();
      this.PbSelectID1 = new PictureBox();
      this.label27 = new Label();
      this.pictureBox1 = new PictureBox();
      this.textBox38 = new TextBox();
      this.textBox39 = new TextBox();
      this.textBox40 = new TextBox();
      this.button4 = new Button();
      this.saveToolStripMenuItem = new ToolStripMenuItem();
      this.menuStrip1.SuspendLayout();
      this.groupBox1.SuspendLayout();
      this.groupBox2.SuspendLayout();
      this.groupBox3.SuspendLayout();
      this.groupBox6.SuspendLayout();
      this.groupBox5.SuspendLayout();
      this.trackBar8.BeginInit();
      this.trackBar7.BeginInit();
      this.trackBar6.BeginInit();
      this.trackBar5.BeginInit();
      this.groupBox4.SuspendLayout();
      this.trackBar4.BeginInit();
      this.trackBar3.BeginInit();
      this.trackBar2.BeginInit();
      this.trackBar1.BeginInit();
      this.groupBox7.SuspendLayout();
      this.groupBox8.SuspendLayout();
      this.groupBox9.SuspendLayout();
      ((ISupportInitialize) this.PbSelectID1).BeginInit();
      ((ISupportInitialize) this.pictureBox1).BeginInit();
      this.SuspendLayout();
      this.listBox1.FormattingEnabled = true;
      this.listBox1.Location = new Point(12, 94);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new Size(239, 576);
      this.listBox1.TabIndex = 0;
      this.listBox1.SelectedIndexChanged += new EventHandler(this.listBox1_SelectedIndexChanged);
      this.menuStrip1.AllowMerge = false;
      this.menuStrip1.BackColor = SystemColors.ButtonHighlight;
      this.menuStrip1.Items.AddRange(new ToolStripItem[2]
      {
        (ToolStripItem) this.fileToolStripMenuItem,
        (ToolStripItem) this.clickMeBeforeEditingTitlesToolStripMenuItem
      });
      this.menuStrip1.Location = new Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new Size(822, 24);
      this.menuStrip1.TabIndex = 1;
      this.menuStrip1.Text = "menuStrip1";
      this.menuStrip1.ItemClicked += new ToolStripItemClickedEventHandler(this.menuStrip1_ItemClicked);
      this.fileToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[2]
      {
        (ToolStripItem) this.exportlodToolStripMenuItem,
        (ToolStripItem) this.saveToolStripMenuItem
      });
      this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
      this.fileToolStripMenuItem.Size = new Size(71, 20);
      this.fileToolStripMenuItem.Text = "FileExport";
      this.exportlodToolStripMenuItem.Name = "exportlodToolStripMenuItem";
      this.exportlodToolStripMenuItem.Size = new Size(152, 22);
      this.exportlodToolStripMenuItem.Text = "Export .lod";
      this.exportlodToolStripMenuItem.Click += new EventHandler(this.exportlodToolStripMenuItem_Click);
      this.clickMeBeforeEditingTitlesToolStripMenuItem.Name = "clickMeBeforeEditingTitlesToolStripMenuItem";
      this.clickMeBeforeEditingTitlesToolStripMenuItem.Size = new Size(178, 20);
      this.clickMeBeforeEditingTitlesToolStripMenuItem.Text = "Click Me Before Editing Titles!!";
      this.clickMeBeforeEditingTitlesToolStripMenuItem.Click += new EventHandler(this.clickMeBeforeEditingTitlesToolStripMenuItem_Click);
      this.button1.FlatStyle = FlatStyle.Flat;
      this.button1.Location = new Point(12, 676);
      this.button1.Name = "button1";
      this.button1.Size = new Size(75, 23);
      this.button1.TabIndex = 2;
      this.button1.Text = "Add";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.button2.FlatStyle = FlatStyle.Flat;
      this.button2.Location = new Point(176, 676);
      this.button2.Name = "button2";
      this.button2.Size = new Size(75, 23);
      this.button2.TabIndex = 3;
      this.button2.Text = "Delete";
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.button3.FlatStyle = FlatStyle.Flat;
      this.button3.Location = new Point(742, 676);
      this.button3.Name = "button3";
      this.button3.Size = new Size(75, 23);
      this.button3.TabIndex = 4;
      this.button3.Text = "Save";
      this.button3.UseVisualStyleBackColor = true;
      this.button3.Click += new EventHandler(this.button3_Click);
      this.groupBox1.Controls.Add((Control) this.label19);
      this.groupBox1.Controls.Add((Control) this.label18);
      this.groupBox1.Controls.Add((Control) this.textBox23);
      this.groupBox1.Controls.Add((Control) this.textBox22);
      this.groupBox1.Controls.Add((Control) this.textBox8);
      this.groupBox1.Controls.Add((Control) this.label17);
      this.groupBox1.Controls.Add((Control) this.textBox3);
      this.groupBox1.Controls.Add((Control) this.label16);
      this.groupBox1.Controls.Add((Control) this.textBox2);
      this.groupBox1.Controls.Add((Control) this.textBox4);
      this.groupBox1.Controls.Add((Control) this.label26);
      this.groupBox1.Controls.Add((Control) this.label2);
      this.groupBox1.Controls.Add((Control) this.textBox1);
      this.groupBox1.Controls.Add((Control) this.label1);
      this.groupBox1.Location = new Point(269, 37);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(283, 184);
      this.groupBox1.TabIndex = 5;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "General";
      this.label19.AutoSize = true;
      this.label19.Location = new Point(167, 138);
      this.label19.Name = "label19";
      this.label19.Size = new Size(36, 13);
      this.label19.TabIndex = 17;
      this.label19.Text = "Castle";
      this.label18.AutoSize = true;
      this.label18.Location = new Point(10, 138);
      this.label18.Name = "label18";
      this.label18.Size = new Size(27, 13);
      this.label18.TabIndex = 16;
      this.label18.Text = "Flag";
      this.textBox23.BorderStyle = BorderStyle.FixedSingle;
      this.textBox23.Location = new Point(214, 136);
      this.textBox23.Name = "textBox23";
      this.textBox23.Size = new Size(52, 20);
      this.textBox23.TabIndex = 15;
      this.textBox22.BorderStyle = BorderStyle.FixedSingle;
      this.textBox22.Location = new Point(85, 136);
      this.textBox22.Name = "textBox22";
      this.textBox22.Size = new Size(52, 20);
      this.textBox22.TabIndex = 14;
      this.textBox8.BorderStyle = BorderStyle.FixedSingle;
      this.textBox8.Location = new Point(214, 107);
      this.textBox8.Name = "textBox8";
      this.textBox8.Size = new Size(52, 20);
      this.textBox8.TabIndex = 12;
      this.label17.AutoSize = true;
      this.label17.Location = new Point(167, 109);
      this.label17.Name = "label17";
      this.label17.Size = new Size(30, 13);
      this.label17.TabIndex = 11;
      this.label17.Text = "Time";
      this.textBox3.BorderStyle = BorderStyle.FixedSingle;
      this.textBox3.Location = new Point(85, 107);
      this.textBox3.Name = "textBox3";
      this.textBox3.Size = new Size(52, 20);
      this.textBox3.TabIndex = 10;
      this.label16.AutoSize = true;
      this.label16.Location = new Point(10, 109);
      this.label16.Name = "label16";
      this.label16.Size = new Size(43, 13);
      this.label16.TabIndex = 10;
      this.label16.Text = "Enable:";
      this.textBox2.BorderStyle = BorderStyle.FixedSingle;
      this.textBox2.Location = new Point(85, 55);
      this.textBox2.Name = "textBox2";
      this.textBox2.ReadOnly = true;
      this.textBox2.Size = new Size(181, 20);
      this.textBox2.TabIndex = 9;
      this.textBox2.TextChanged += new EventHandler(this.textBox2_TextChanged);
      this.textBox4.BorderStyle = BorderStyle.FixedSingle;
      this.textBox4.Location = new Point(85, 80);
      this.textBox4.Name = "textBox4";
      this.textBox4.Size = new Size(181, 20);
      this.textBox4.TabIndex = 7;
      this.label26.AutoSize = true;
      this.label26.Location = new Point(6, 82);
      this.label26.Name = "label26";
      this.label26.Size = new Size(58, 13);
      this.label26.TabIndex = 8;
      this.label26.Text = "Title Desc:";
      this.label2.AutoSize = true;
      this.label2.Location = new Point(6, 57);
      this.label2.Name = "label2";
      this.label2.Size = new Size(61, 13);
      this.label2.TabIndex = 4;
      this.label2.Text = "Title Name:";
      this.textBox1.BorderStyle = BorderStyle.FixedSingle;
      this.textBox1.Location = new Point(85, 24);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(52, 20);
      this.textBox1.TabIndex = 3;
      this.label1.AutoSize = true;
      this.label1.Location = new Point(6, 26);
      this.label1.Name = "label1";
      this.label1.Size = new Size(41, 13);
      this.label1.TabIndex = 2;
      this.label1.Text = "TitleID:";
      this.textBox21.BorderStyle = BorderStyle.FixedSingle;
      this.textBox21.Location = new Point(52, 24);
      this.textBox21.Name = "textBox21";
      this.textBox21.Size = new Size(52, 20);
      this.textBox21.TabIndex = 13;
      this.textBox21.TextChanged += new EventHandler(this.textBox21_TextChanged);
      this.label3.AutoSize = true;
      this.label3.Location = new Point(5, 26);
      this.label3.Name = "label3";
      this.label3.Size = new Size(41, 13);
      this.label3.TabIndex = 6;
      this.label3.Text = "ItemID:";
      this.groupBox2.Controls.Add((Control) this.textBox7);
      this.groupBox2.Controls.Add((Control) this.textBox6);
      this.groupBox2.Controls.Add((Control) this.textBox5);
      this.groupBox2.Controls.Add((Control) this.label6);
      this.groupBox2.Controls.Add((Control) this.label5);
      this.groupBox2.Controls.Add((Control) this.label4);
      this.groupBox2.Location = new Point(567, 111);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new Size(250, 110);
      this.groupBox2.TabIndex = 6;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "Effects";
      this.textBox7.BorderStyle = BorderStyle.FixedSingle;
      this.textBox7.Location = new Point(63, 76);
      this.textBox7.Name = "textBox7";
      this.textBox7.Size = new Size(181, 20);
      this.textBox7.TabIndex = 12;
      this.textBox6.BorderStyle = BorderStyle.FixedSingle;
      this.textBox6.Location = new Point(63, 50);
      this.textBox6.Name = "textBox6";
      this.textBox6.Size = new Size(181, 20);
      this.textBox6.TabIndex = 11;
      this.textBox5.BorderStyle = BorderStyle.FixedSingle;
      this.textBox5.Location = new Point(63, 24);
      this.textBox5.Name = "textBox5";
      this.textBox5.Size = new Size(181, 20);
      this.textBox5.TabIndex = 10;
      this.label6.AutoSize = true;
      this.label6.Location = new Point(6, 78);
      this.label6.Name = "label6";
      this.label6.Size = new Size(50, 13);
      this.label6.TabIndex = 2;
      this.label6.Text = "Damage:";
      this.label5.AutoSize = true;
      this.label5.Location = new Point(6, 52);
      this.label5.Name = "label5";
      this.label5.Size = new Size(41, 13);
      this.label5.TabIndex = 1;
      this.label5.Text = "Attack:";
      this.label4.AutoSize = true;
      this.label4.Location = new Point(6, 26);
      this.label4.Name = "label4";
      this.label4.Size = new Size(38, 13);
      this.label4.TabIndex = 0;
      this.label4.Text = "Effect:";
      this.groupBox3.Controls.Add((Control) this.groupBox6);
      this.groupBox3.Controls.Add((Control) this.groupBox5);
      this.groupBox3.Controls.Add((Control) this.groupBox4);
      this.groupBox3.Location = new Point(269, 227);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Size = new Size(548, 259);
      this.groupBox3.TabIndex = 6;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "Visual View";
      this.groupBox6.Controls.Add((Control) this.label15);
      this.groupBox6.Location = new Point(6, 176);
      this.groupBox6.Name = "groupBox6";
      this.groupBox6.Size = new Size(536, 77);
      this.groupBox6.TabIndex = 8;
      this.groupBox6.TabStop = false;
      this.groupBox6.Text = "Pre-View";
      this.label15.Location = new Point(6, 18);
      this.label15.Name = "label15";
      this.label15.Size = new Size(527, 50);
      this.label15.TabIndex = 0;
      this.label15.Text = "Preview Text";
      this.label15.TextAlign = ContentAlignment.MiddleCenter;
      this.groupBox5.Controls.Add((Control) this.textBox9);
      this.groupBox5.Controls.Add((Control) this.trackBar8);
      this.groupBox5.Controls.Add((Control) this.trackBar7);
      this.groupBox5.Controls.Add((Control) this.trackBar6);
      this.groupBox5.Controls.Add((Control) this.trackBar5);
      this.groupBox5.Controls.Add((Control) this.label14);
      this.groupBox5.Controls.Add((Control) this.label13);
      this.groupBox5.Controls.Add((Control) this.label12);
      this.groupBox5.Controls.Add((Control) this.label11);
      this.groupBox5.Location = new Point(306, 19);
      this.groupBox5.Name = "groupBox5";
      this.groupBox5.Size = new Size(239, 151);
      this.groupBox5.TabIndex = 7;
      this.groupBox5.TabStop = false;
      this.groupBox5.Text = "Background Color";
      this.textBox9.BorderStyle = BorderStyle.FixedSingle;
      this.textBox9.Location = new Point(153, 123);
      this.textBox9.Name = "textBox9";
      this.textBox9.Size = new Size(80, 20);
      this.textBox9.TabIndex = 13;
      this.textBox9.TextChanged += new EventHandler(this.textBox9_TextChanged);
      this.trackBar8.AutoSize = false;
      this.trackBar8.Location = new Point(58, 97);
      this.trackBar8.Maximum = (int) byte.MaxValue;
      this.trackBar8.Name = "trackBar8";
      this.trackBar8.Size = new Size(126, 20);
      this.trackBar8.TabIndex = 13;
      this.trackBar8.TickStyle = TickStyle.None;
      this.trackBar8.Scroll += new EventHandler(this.trackBar8_Scroll);
      this.trackBar7.AutoSize = false;
      this.trackBar7.Location = new Point(58, 72);
      this.trackBar7.Maximum = (int) byte.MaxValue;
      this.trackBar7.Name = "trackBar7";
      this.trackBar7.Size = new Size(126, 20);
      this.trackBar7.TabIndex = 12;
      this.trackBar7.TickStyle = TickStyle.None;
      this.trackBar7.Scroll += new EventHandler(this.trackBar7_Scroll);
      this.trackBar6.AutoSize = false;
      this.trackBar6.Location = new Point(58, 46);
      this.trackBar6.Maximum = (int) byte.MaxValue;
      this.trackBar6.Name = "trackBar6";
      this.trackBar6.Size = new Size(126, 20);
      this.trackBar6.TabIndex = 11;
      this.trackBar6.TickStyle = TickStyle.None;
      this.trackBar6.Scroll += new EventHandler(this.trackBar6_Scroll);
      this.trackBar5.AutoSize = false;
      this.trackBar5.Location = new Point(58, 19);
      this.trackBar5.Maximum = (int) byte.MaxValue;
      this.trackBar5.Name = "trackBar5";
      this.trackBar5.Size = new Size(126, 20);
      this.trackBar5.TabIndex = 7;
      this.trackBar5.TickStyle = TickStyle.None;
      this.trackBar5.Scroll += new EventHandler(this.trackBar5_Scroll);
      this.label14.AutoSize = true;
      this.label14.Location = new Point(6, 100);
      this.label14.Name = "label14";
      this.label14.Size = new Size(17, 13);
      this.label14.TabIndex = 3;
      this.label14.Text = "B:";
      this.label13.AutoSize = true;
      this.label13.Location = new Point(5, 74);
      this.label13.Name = "label13";
      this.label13.Size = new Size(18, 13);
      this.label13.TabIndex = 2;
      this.label13.Text = "G:";
      this.label12.AutoSize = true;
      this.label12.Location = new Point(6, 49);
      this.label12.Name = "label12";
      this.label12.Size = new Size(18, 13);
      this.label12.TabIndex = 1;
      this.label12.Text = "R:";
      this.label11.AutoSize = true;
      this.label11.Location = new Point(6, 22);
      this.label11.Name = "label11";
      this.label11.Size = new Size(46, 13);
      this.label11.TabIndex = 0;
      this.label11.Text = "Opacity:";
      this.groupBox4.Controls.Add((Control) this.textBox10);
      this.groupBox4.Controls.Add((Control) this.trackBar4);
      this.groupBox4.Controls.Add((Control) this.trackBar3);
      this.groupBox4.Controls.Add((Control) this.trackBar2);
      this.groupBox4.Controls.Add((Control) this.trackBar1);
      this.groupBox4.Controls.Add((Control) this.label10);
      this.groupBox4.Controls.Add((Control) this.label9);
      this.groupBox4.Controls.Add((Control) this.label7);
      this.groupBox4.Controls.Add((Control) this.label8);
      this.groupBox4.Location = new Point(6, 19);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Size = new Size(239, 151);
      this.groupBox4.TabIndex = 6;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "Text Color";
      this.textBox10.BorderStyle = BorderStyle.FixedSingle;
      this.textBox10.Location = new Point(156, 123);
      this.textBox10.Name = "textBox10";
      this.textBox10.Size = new Size(74, 20);
      this.textBox10.TabIndex = 14;
      this.textBox10.Text = " ";
      this.textBox10.TextChanged += new EventHandler(this.textBox10_TextChanged);
      this.trackBar4.AutoSize = false;
      this.trackBar4.Location = new Point(58, 97);
      this.trackBar4.Maximum = (int) byte.MaxValue;
      this.trackBar4.Name = "trackBar4";
      this.trackBar4.Size = new Size(125, 20);
      this.trackBar4.TabIndex = 9;
      this.trackBar4.TickStyle = TickStyle.None;
      this.trackBar4.Scroll += new EventHandler(this.trackBar4_Scroll);
      this.trackBar3.AutoSize = false;
      this.trackBar3.Location = new Point(58, 71);
      this.trackBar3.Maximum = (int) byte.MaxValue;
      this.trackBar3.Name = "trackBar3";
      this.trackBar3.Size = new Size(125, 20);
      this.trackBar3.TabIndex = 8;
      this.trackBar3.TickStyle = TickStyle.None;
      this.trackBar3.Scroll += new EventHandler(this.trackBar3_Scroll);
      this.trackBar2.AutoSize = false;
      this.trackBar2.Location = new Point(58, 47);
      this.trackBar2.Maximum = (int) byte.MaxValue;
      this.trackBar2.Name = "trackBar2";
      this.trackBar2.Size = new Size(125, 20);
      this.trackBar2.TabIndex = 7;
      this.trackBar2.TickStyle = TickStyle.None;
      this.trackBar2.Scroll += new EventHandler(this.trackBar2_Scroll);
      this.trackBar1.AutoSize = false;
      this.trackBar1.Location = new Point(58, 20);
      this.trackBar1.Maximum = (int) byte.MaxValue;
      this.trackBar1.Name = "trackBar1";
      this.trackBar1.Size = new Size(126, 20);
      this.trackBar1.TabIndex = 6;
      this.trackBar1.TickStyle = TickStyle.None;
      this.trackBar1.Scroll += new EventHandler(this.trackBar1_Scroll);
      this.label10.AutoSize = true;
      this.label10.Location = new Point(6, 22);
      this.label10.Name = "label10";
      this.label10.Size = new Size(46, 13);
      this.label10.TabIndex = 3;
      this.label10.Text = "Opacity:";
      this.label9.AutoSize = true;
      this.label9.Location = new Point(7, 100);
      this.label9.Name = "label9";
      this.label9.Size = new Size(17, 13);
      this.label9.TabIndex = 2;
      this.label9.Text = "B:";
      this.label7.AutoSize = true;
      this.label7.Location = new Point(6, 49);
      this.label7.Name = "label7";
      this.label7.Size = new Size(18, 13);
      this.label7.TabIndex = 0;
      this.label7.Text = "R:";
      this.label8.AutoSize = true;
      this.label8.Location = new Point(6, 74);
      this.label8.Name = "label8";
      this.label8.Size = new Size(18, 13);
      this.label8.TabIndex = 1;
      this.label8.Text = "G:";
      this.groupBox7.Controls.Add((Control) this.textBox32);
      this.groupBox7.Controls.Add((Control) this.comboBox10);
      this.groupBox7.Controls.Add((Control) this.textBox33);
      this.groupBox7.Controls.Add((Control) this.comboBox9);
      this.groupBox7.Controls.Add((Control) this.comboBox8);
      this.groupBox7.Controls.Add((Control) this.textBox34);
      this.groupBox7.Controls.Add((Control) this.comboBox7);
      this.groupBox7.Controls.Add((Control) this.comboBox6);
      this.groupBox7.Controls.Add((Control) this.textBox35);
      this.groupBox7.Controls.Add((Control) this.comboBox5);
      this.groupBox7.Controls.Add((Control) this.comboBox4);
      this.groupBox7.Controls.Add((Control) this.textBox36);
      this.groupBox7.Controls.Add((Control) this.comboBox3);
      this.groupBox7.Controls.Add((Control) this.comboBox2);
      this.groupBox7.Controls.Add((Control) this.label20);
      this.groupBox7.Controls.Add((Control) this.label21);
      this.groupBox7.Controls.Add((Control) this.label22);
      this.groupBox7.Controls.Add((Control) this.label23);
      this.groupBox7.Controls.Add((Control) this.label24);
      this.groupBox7.Controls.Add((Control) this.comboBox1);
      this.groupBox7.Controls.Add((Control) this.textBox19);
      this.groupBox7.Controls.Add((Control) this.textBox17);
      this.groupBox7.Controls.Add((Control) this.textBox15);
      this.groupBox7.Controls.Add((Control) this.textBox13);
      this.groupBox7.Controls.Add((Control) this.textBox11);
      this.groupBox7.Controls.Add((Control) this.textBox14);
      this.groupBox7.Controls.Add((Control) this.textBox12);
      this.groupBox7.Controls.Add((Control) this.textBox16);
      this.groupBox7.Controls.Add((Control) this.textBox20);
      this.groupBox7.Controls.Add((Control) this.textBox18);
      this.groupBox7.Location = new Point(269, 492);
      this.groupBox7.Name = "groupBox7";
      this.groupBox7.Size = new Size(548, 169);
      this.groupBox7.TabIndex = 7;
      this.groupBox7.TabStop = false;
      this.groupBox7.Text = "Seals";
      this.textBox32.BorderStyle = BorderStyle.FixedSingle;
      this.textBox32.Location = new Point(299, 272);
      this.textBox32.Name = "textBox32";
      this.textBox32.Size = new Size(52, 20);
      this.textBox32.TabIndex = 42;
      this.comboBox10.BackColor = SystemColors.Window;
      this.comboBox10.FlatStyle = FlatStyle.Flat;
      this.comboBox10.FormattingEnabled = true;
      this.comboBox10.Location = new Point(382, 132);
      this.comboBox10.Name = "comboBox10";
      this.comboBox10.Size = new Size(114, 21);
      this.comboBox10.TabIndex = 37;
      this.comboBox10.SelectedIndexChanged += new EventHandler(this.comboBox10_SelectedIndexChanged);
      this.textBox33.BorderStyle = BorderStyle.FixedSingle;
      this.textBox33.Location = new Point(241, 272);
      this.textBox33.Name = "textBox33";
      this.textBox33.Size = new Size(52, 20);
      this.textBox33.TabIndex = 41;
      this.comboBox9.BackColor = SystemColors.Window;
      this.comboBox9.FlatStyle = FlatStyle.Flat;
      this.comboBox9.FormattingEnabled = true;
      this.comboBox9.Location = new Point(382, 102);
      this.comboBox9.Name = "comboBox9";
      this.comboBox9.Size = new Size(114, 21);
      this.comboBox9.TabIndex = 36;
      this.comboBox9.SelectedIndexChanged += new EventHandler(this.comboBox9_SelectedIndexChanged);
      this.comboBox8.BackColor = SystemColors.Window;
      this.comboBox8.FlatStyle = FlatStyle.Flat;
      this.comboBox8.FormattingEnabled = true;
      this.comboBox8.Location = new Point(382, 74);
      this.comboBox8.Name = "comboBox8";
      this.comboBox8.Size = new Size(114, 21);
      this.comboBox8.TabIndex = 35;
      this.comboBox8.SelectedIndexChanged += new EventHandler(this.comboBox8_SelectedIndexChanged);
      this.textBox34.BorderStyle = BorderStyle.FixedSingle;
      this.textBox34.Location = new Point(180, 272);
      this.textBox34.Name = "textBox34";
      this.textBox34.Size = new Size(52, 20);
      this.textBox34.TabIndex = 40;
      this.comboBox7.BackColor = SystemColors.Window;
      this.comboBox7.FlatStyle = FlatStyle.Flat;
      this.comboBox7.FormattingEnabled = true;
      this.comboBox7.Location = new Point(382, 46);
      this.comboBox7.Name = "comboBox7";
      this.comboBox7.Size = new Size(114, 21);
      this.comboBox7.TabIndex = 34;
      this.comboBox7.SelectedIndexChanged += new EventHandler(this.comboBox7_SelectedIndexChanged);
      this.comboBox6.BackColor = SystemColors.Window;
      this.comboBox6.FlatStyle = FlatStyle.Flat;
      this.comboBox6.FormattingEnabled = true;
      this.comboBox6.Location = new Point(382, 17);
      this.comboBox6.Name = "comboBox6";
      this.comboBox6.Size = new Size(114, 21);
      this.comboBox6.TabIndex = 33;
      this.comboBox6.SelectedIndexChanged += new EventHandler(this.comboBox6_SelectedIndexChanged);
      this.textBox35.BorderStyle = BorderStyle.FixedSingle;
      this.textBox35.Location = new Point(122, 271);
      this.textBox35.Name = "textBox35";
      this.textBox35.Size = new Size(52, 20);
      this.textBox35.TabIndex = 39;
      this.comboBox5.BackColor = SystemColors.Window;
      this.comboBox5.FlatStyle = FlatStyle.Flat;
      this.comboBox5.FormattingEnabled = true;
      this.comboBox5.Items.AddRange(new object[1]
      {
        (object) "-1 - None"
      });
      this.comboBox5.Location = new Point(102, 132);
      this.comboBox5.Name = "comboBox5";
      this.comboBox5.Size = new Size(234, 21);
      this.comboBox5.TabIndex = 32;
      this.comboBox5.SelectedIndexChanged += new EventHandler(this.comboBox5_SelectedIndexChanged);
      this.comboBox4.BackColor = SystemColors.Window;
      this.comboBox4.FlatStyle = FlatStyle.Flat;
      this.comboBox4.FormattingEnabled = true;
      this.comboBox4.Items.AddRange(new object[1]
      {
        (object) "-1 - None"
      });
      this.comboBox4.Location = new Point(102, 102);
      this.comboBox4.Name = "comboBox4";
      this.comboBox4.Size = new Size(234, 21);
      this.comboBox4.TabIndex = 31;
      this.comboBox4.SelectedIndexChanged += new EventHandler(this.comboBox4_SelectedIndexChanged);
      this.textBox36.BorderStyle = BorderStyle.FixedSingle;
      this.textBox36.Location = new Point(64, 271);
      this.textBox36.Name = "textBox36";
      this.textBox36.Size = new Size(52, 20);
      this.textBox36.TabIndex = 38;
      this.textBox36.TextChanged += new EventHandler(this.textBox36_TextChanged);
      this.comboBox3.BackColor = SystemColors.Window;
      this.comboBox3.FlatStyle = FlatStyle.Flat;
      this.comboBox3.FormattingEnabled = true;
      this.comboBox3.Items.AddRange(new object[1]
      {
        (object) "-1 - None"
      });
      this.comboBox3.Location = new Point(102, 74);
      this.comboBox3.Name = "comboBox3";
      this.comboBox3.Size = new Size(234, 21);
      this.comboBox3.TabIndex = 30;
      this.comboBox3.SelectedIndexChanged += new EventHandler(this.comboBox3_SelectedIndexChanged);
      this.comboBox2.BackColor = SystemColors.Window;
      this.comboBox2.FlatStyle = FlatStyle.Flat;
      this.comboBox2.FormattingEnabled = true;
      this.comboBox2.Items.AddRange(new object[1]
      {
        (object) "-1 - None"
      });
      this.comboBox2.Location = new Point(102, 46);
      this.comboBox2.Name = "comboBox2";
      this.comboBox2.Size = new Size(234, 21);
      this.comboBox2.TabIndex = 29;
      this.comboBox2.SelectedIndexChanged += new EventHandler(this.comboBox2_SelectedIndexChanged);
      this.label20.AutoSize = true;
      this.label20.Location = new Point(35, 135);
      this.label20.Name = "label20";
      this.label20.Size = new Size(40, 13);
      this.label20.TabIndex = 28;
      this.label20.Text = "Seal 5:";
      this.label21.AutoSize = true;
      this.label21.Location = new Point(34, 105);
      this.label21.Name = "label21";
      this.label21.Size = new Size(40, 13);
      this.label21.TabIndex = 27;
      this.label21.Text = "Seal 4:";
      this.label22.AutoSize = true;
      this.label22.Location = new Point(34, 77);
      this.label22.Name = "label22";
      this.label22.Size = new Size(40, 13);
      this.label22.TabIndex = 26;
      this.label22.Text = "Seal 3:";
      this.label23.AutoSize = true;
      this.label23.Location = new Point(35, 49);
      this.label23.Name = "label23";
      this.label23.Size = new Size(40, 13);
      this.label23.TabIndex = 25;
      this.label23.Text = "Seal 2:";
      this.label24.AutoSize = true;
      this.label24.Location = new Point(34, 20);
      this.label24.Name = "label24";
      this.label24.Size = new Size(40, 13);
      this.label24.TabIndex = 24;
      this.label24.Text = "Seal 1:";
      this.comboBox1.BackColor = SystemColors.Window;
      this.comboBox1.FlatStyle = FlatStyle.Flat;
      this.comboBox1.FormattingEnabled = true;
      this.comboBox1.Items.AddRange(new object[1]
      {
        (object) "-1 - None"
      });
      this.comboBox1.Location = new Point(102, 17);
      this.comboBox1.Name = "comboBox1";
      this.comboBox1.Size = new Size(234, 21);
      this.comboBox1.TabIndex = 23;
      this.comboBox1.SelectedIndexChanged += new EventHandler(this.comboBox1_SelectedIndexChanged);
      this.textBox19.BorderStyle = BorderStyle.FixedSingle;
      this.textBox19.Location = new Point(299, 208);
      this.textBox19.Name = "textBox19";
      this.textBox19.Size = new Size(52, 20);
      this.textBox19.TabIndex = 21;
      this.textBox17.BorderStyle = BorderStyle.FixedSingle;
      this.textBox17.Location = new Point(241, 208);
      this.textBox17.Name = "textBox17";
      this.textBox17.Size = new Size(52, 20);
      this.textBox17.TabIndex = 19;
      this.textBox15.BorderStyle = BorderStyle.FixedSingle;
      this.textBox15.Location = new Point(183, 208);
      this.textBox15.Name = "textBox15";
      this.textBox15.Size = new Size(52, 20);
      this.textBox15.TabIndex = 17;
      this.textBox13.BorderStyle = BorderStyle.FixedSingle;
      this.textBox13.Location = new Point(122, 208);
      this.textBox13.Name = "textBox13";
      this.textBox13.Size = new Size(52, 20);
      this.textBox13.TabIndex = 15;
      this.textBox11.BorderStyle = BorderStyle.FixedSingle;
      this.textBox11.Location = new Point(64, 208);
      this.textBox11.Name = "textBox11";
      this.textBox11.Size = new Size(52, 20);
      this.textBox11.TabIndex = 13;
      this.textBox14.BorderStyle = BorderStyle.FixedSingle;
      this.textBox14.Location = new Point(122, 245);
      this.textBox14.Name = "textBox14";
      this.textBox14.Size = new Size(52, 20);
      this.textBox14.TabIndex = 16;
      this.textBox12.BorderStyle = BorderStyle.FixedSingle;
      this.textBox12.Location = new Point(64, 245);
      this.textBox12.Name = "textBox12";
      this.textBox12.Size = new Size(52, 20);
      this.textBox12.TabIndex = 14;
      this.textBox12.TextChanged += new EventHandler(this.textBox12_TextChanged);
      this.textBox16.BorderStyle = BorderStyle.FixedSingle;
      this.textBox16.Location = new Point(180, 245);
      this.textBox16.Name = "textBox16";
      this.textBox16.Size = new Size(52, 20);
      this.textBox16.TabIndex = 18;
      this.textBox20.BorderStyle = BorderStyle.FixedSingle;
      this.textBox20.Location = new Point(299, 245);
      this.textBox20.Name = "textBox20";
      this.textBox20.Size = new Size(52, 20);
      this.textBox20.TabIndex = 22;
      this.textBox18.BorderStyle = BorderStyle.FixedSingle;
      this.textBox18.Location = new Point(241, 245);
      this.textBox18.Name = "textBox18";
      this.textBox18.Size = new Size(52, 20);
      this.textBox18.TabIndex = 20;
      this.textBox24.BorderStyle = BorderStyle.FixedSingle;
      this.textBox24.Location = new Point(958, 217);
      this.textBox24.Name = "textBox24";
      this.textBox24.Size = new Size(53, 20);
      this.textBox24.TabIndex = 22;
      this.textBox24.TextChanged += new EventHandler(this.textBox24_TextChanged);
      this.textBox25.BorderStyle = BorderStyle.FixedSingle;
      this.textBox25.Location = new Point(958, 243);
      this.textBox25.Name = "textBox25";
      this.textBox25.Size = new Size(53, 20);
      this.textBox25.TabIndex = 23;
      this.textBox26.BorderStyle = BorderStyle.FixedSingle;
      this.textBox26.Location = new Point(958, 268);
      this.textBox26.Name = "textBox26";
      this.textBox26.Size = new Size(53, 20);
      this.textBox26.TabIndex = 24;
      this.textBox27.BorderStyle = BorderStyle.FixedSingle;
      this.textBox27.Location = new Point(958, 295);
      this.textBox27.Name = "textBox27";
      this.textBox27.Size = new Size(53, 20);
      this.textBox27.TabIndex = 25;
      this.textBox28.BorderStyle = BorderStyle.FixedSingle;
      this.textBox28.Location = new Point(958, 339);
      this.textBox28.Name = "textBox28";
      this.textBox28.Size = new Size(53, 20);
      this.textBox28.TabIndex = 26;
      this.textBox29.BorderStyle = BorderStyle.FixedSingle;
      this.textBox29.Location = new Point(958, 369);
      this.textBox29.Name = "textBox29";
      this.textBox29.Size = new Size(53, 20);
      this.textBox29.TabIndex = 27;
      this.textBox30.BorderStyle = BorderStyle.FixedSingle;
      this.textBox30.Location = new Point(958, 395);
      this.textBox30.Name = "textBox30";
      this.textBox30.Size = new Size(53, 20);
      this.textBox30.TabIndex = 28;
      this.textBox31.BorderStyle = BorderStyle.FixedSingle;
      this.textBox31.Location = new Point(958, 421);
      this.textBox31.Name = "textBox31";
      this.textBox31.Size = new Size(53, 20);
      this.textBox31.TabIndex = 29;
      this.groupBox8.Controls.Add((Control) this.textBox37);
      this.groupBox8.Controls.Add((Control) this.label25);
      this.groupBox8.Location = new Point(12, 36);
      this.groupBox8.Name = "groupBox8";
      this.groupBox8.Size = new Size(239, 52);
      this.groupBox8.TabIndex = 30;
      this.groupBox8.TabStop = false;
      this.groupBox8.Text = "Search";
      this.textBox37.BorderStyle = BorderStyle.FixedSingle;
      this.textBox37.Location = new Point(44, 19);
      this.textBox37.Name = "textBox37";
      this.textBox37.Size = new Size(189, 20);
      this.textBox37.TabIndex = 5;
      this.textBox37.TextChanged += new EventHandler(this.textBox37_TextChanged);
      this.label25.AutoSize = true;
      this.label25.Location = new Point(6, 21);
      this.label25.Name = "label25";
      this.label25.Size = new Size(31, 13);
      this.label25.TabIndex = 4;
      this.label25.Text = "Text:";
      this.groupBox9.Controls.Add((Control) this.PbSelectID1);
      this.groupBox9.Controls.Add((Control) this.label27);
      this.groupBox9.Controls.Add((Control) this.textBox21);
      this.groupBox9.Controls.Add((Control) this.pictureBox1);
      this.groupBox9.Controls.Add((Control) this.label3);
      this.groupBox9.Location = new Point(567, 37);
      this.groupBox9.Name = "groupBox9";
      this.groupBox9.Size = new Size(250, 68);
      this.groupBox9.TabIndex = 31;
      this.groupBox9.TabStop = false;
      this.groupBox9.Text = "Item";
      this.PbSelectID1.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbSelectID1.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbSelectID1.Location = new Point(114, 23);
      this.PbSelectID1.Name = "PbSelectID1";
      this.PbSelectID1.Size = new Size(22, 22);
      this.PbSelectID1.TabIndex = 106;
      this.PbSelectID1.TabStop = false;
      this.PbSelectID1.Click += new EventHandler(this.PbSelectID1_Click);
      this.label27.Location = new Point(9, 52);
      this.label27.Name = "label27";
      this.label27.Size = new Size(235, 13);
      this.label27.TabIndex = 99;
      this.label27.Text = "label27";
      this.pictureBox1.BackColor = SystemColors.ButtonHighlight;
      this.pictureBox1.Location = new Point(212, 18);
      this.pictureBox1.Name = "pictureBox1";
      this.pictureBox1.Size = new Size(32, 32);
      this.pictureBox1.TabIndex = 98;
      this.pictureBox1.TabStop = false;
      this.textBox38.BorderStyle = BorderStyle.FixedSingle;
      this.textBox38.Location = new Point(942, 94);
      this.textBox38.Name = "textBox38";
      this.textBox38.Size = new Size(53, 20);
      this.textBox38.TabIndex = 32;
      this.textBox39.BorderStyle = BorderStyle.FixedSingle;
      this.textBox39.Location = new Point(942, 128);
      this.textBox39.Name = "textBox39";
      this.textBox39.Size = new Size(53, 20);
      this.textBox39.TabIndex = 32;
      this.textBox40.BorderStyle = BorderStyle.FixedSingle;
      this.textBox40.Location = new Point(942, 154);
      this.textBox40.Name = "textBox40";
      this.textBox40.Size = new Size(53, 20);
      this.textBox40.TabIndex = 33;
      this.button4.FlatStyle = FlatStyle.Flat;
      this.button4.Location = new Point(95, 676);
      this.button4.Name = "button4";
      this.button4.Size = new Size(75, 23);
      this.button4.TabIndex = 34;
      this.button4.Text = "Copy";
      this.button4.UseVisualStyleBackColor = true;
      this.button4.Click += new EventHandler(this.button4_Click);
      this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
      this.saveToolStripMenuItem.Size = new Size(152, 22);
      this.saveToolStripMenuItem.Text = "Save";
      this.saveToolStripMenuItem.Click += new EventHandler(this.saveToolStripMenuItem_Click);
      this.ClientSize = new Size(822, 709);
      this.Controls.Add((Control) this.button4);
      this.Controls.Add((Control) this.textBox40);
      this.Controls.Add((Control) this.textBox39);
      this.Controls.Add((Control) this.textBox38);
      this.Controls.Add((Control) this.groupBox9);
      this.Controls.Add((Control) this.groupBox8);
      this.Controls.Add((Control) this.textBox31);
      this.Controls.Add((Control) this.textBox30);
      this.Controls.Add((Control) this.textBox29);
      this.Controls.Add((Control) this.textBox28);
      this.Controls.Add((Control) this.textBox27);
      this.Controls.Add((Control) this.textBox26);
      this.Controls.Add((Control) this.textBox25);
      this.Controls.Add((Control) this.textBox24);
      this.Controls.Add((Control) this.groupBox7);
      this.Controls.Add((Control) this.groupBox3);
      this.Controls.Add((Control) this.groupBox2);
      this.Controls.Add((Control) this.groupBox1);
      this.Controls.Add((Control) this.button3);
      this.Controls.Add((Control) this.button2);
      this.Controls.Add((Control) this.button1);
      this.Controls.Add((Control) this.listBox1);
      this.Controls.Add((Control) this.menuStrip1);
      this.Icon = (Icon) componentResourceManager.GetObject("$this.Icon");
      this.MainMenuStrip = this.menuStrip1;
      this.Name = nameof (TitleEditor);
      this.Text = "Title Editor";
      this.Load += new EventHandler(this.Exporter_Title_Load);
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.groupBox2.ResumeLayout(false);
      this.groupBox2.PerformLayout();
      this.groupBox3.ResumeLayout(false);
      this.groupBox6.ResumeLayout(false);
      this.groupBox5.ResumeLayout(false);
      this.groupBox5.PerformLayout();
      this.trackBar8.EndInit();
      this.trackBar7.EndInit();
      this.trackBar6.EndInit();
      this.trackBar5.EndInit();
      this.groupBox4.ResumeLayout(false);
      this.groupBox4.PerformLayout();
      this.trackBar4.EndInit();
      this.trackBar3.EndInit();
      this.trackBar2.EndInit();
      this.trackBar1.EndInit();
      this.groupBox7.ResumeLayout(false);
      this.groupBox7.PerformLayout();
      this.groupBox8.ResumeLayout(false);
      this.groupBox8.PerformLayout();
      this.groupBox9.ResumeLayout(false);
      this.groupBox9.PerformLayout();
      ((ISupportInitialize) this.PbSelectID1).EndInit();
      ((ISupportInitialize) this.pictureBox1).EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();
    }

    private void clickMeBeforeEditingTitlesToolStripMenuItem_Click(object sender, EventArgs e)
    {
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_option set a_level = TRIM(a_level);");
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_option set a_prob = TRIM(a_prob);");
      int num = (int) new CustomMessage("Done :)").ShowDialog();
      this.clickMeBeforeEditingTitlesToolStripMenuItem.Enabled = false;
    }

    private void PbSelectID1_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox21.Text = Convert.ToString(itemPicker.ItemIndex);
    }

    private void saveToolStripMenuItem_Click(object sender, EventArgs e)
    {
      this.exportLodHandle.ExportTitle_V4();
    }
  }
}
