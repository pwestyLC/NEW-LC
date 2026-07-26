// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.NewMagicEditor.NewMagicEditor
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
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.NewMagicEditor
{
  public class NewMagicEditor : Form
  {
    public static Connection connection = new Connection();
    private string Host = LcDevPack_TeamDamonA.Tools.MemoryWorker.NewMagicEditor.NewMagicEditor.connection.Settings.SqlHost;
    private string User = LcDevPack_TeamDamonA.Tools.MemoryWorker.NewMagicEditor.NewMagicEditor.connection.Settings.SqlUser;
    private string Password = LcDevPack_TeamDamonA.Tools.MemoryWorker.NewMagicEditor.NewMagicEditor.connection.Settings.SqlPassword;
    private string Database = LcDevPack_TeamDamonA.Tools.MemoryWorker.NewMagicEditor.NewMagicEditor.connection.Settings.SqlDatabase;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    public string[] menuArray = new string[2]
    {
      "a_index",
      "a_name"
    };
    private IContainer components = (IContainer) null;
    private GroupBox groupBox1;
    private Button button2;
    private Button button1;
    private ListBox listBox1;
    private GroupBox groupBox2;
    private Label label4;
    private Label label1;
    private TextBox textBox2;
    private TextBox textBox1;
    private GroupBox groupBox3;
    private TextBox textBox3;
    private Label label2;
    private Label label6;
    private Label label5;
    private TextBox textBox6;
    private Label label3;
    private TextBox textBox5;
    private TextBox textBox4;
    private GroupBox groupBox4;
    private Label label12;
    private TextBox textBox12;
    private Label label11;
    private TextBox textBox11;
    private Label label10;
    private Label label9;
    private TextBox textBox10;
    private TextBox textBox9;
    private Label label8;
    private TextBox textBox8;
    private Label label7;
    private TextBox textBox7;
    private GroupBox groupBox5;
    private DataGridView dgItems;
    private ToolStrip toolStrip2;
    private ToolStripButton btnSaveSelected;
    private ToolStripSeparator toolStripSeparator1;
    private ToolStripButton btnAddItems;
    private ToolStripSeparator toolStripSeparator6;
    private ToolStripButton toolStripButton1;
    private DataGridViewTextBoxColumn index;
    private DataGridViewTextBoxColumn Level;
    private DataGridViewTextBoxColumn Power;
    private DataGridViewTextBoxColumn HitRate;
    private Button button3;
    private ComboBox comboBox3;
    private ComboBox comboBox2;
    private ComboBox comboBox1;
    private TextBox textBox13;
    private Label label14;
    private ComboBox comboBox4;
    private GroupBox groupBox6;
    private Label label13;
    private ComboBox cbSubType1;
    private ComboBox cbSubType2;
    private ComboBox cbSubType10;
    private ComboBox cbSubType8;
    private ComboBox cbSubType9;
    private ComboBox cbSubType7;
    private ComboBox cbSubType5;
    private ComboBox cbSubType6;
    private ComboBox cbSubType4;
    private ComboBox cbSubType3;
    private TextBox tbSubtype;
    private Button button17;
    private Button button18;
    private Button button19;
    private TextBox textBox15;
    private Label label15;
    private Label label17;
    private TextBox textBox16;
    private TextBox textBox17;
    private Label label16;
    private TextBox textBox14;

    public NewMagicEditor() => this.InitializeComponent();

    private void LoadListBox()
    {
      this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, "select a_index, a_name, a_maxlevel, a_type, a_subtype, a_damagetype, a_hittype, a_attribute, a_psp, a_ptp, a_hsp, a_htp, a_togle from t_magic ORDER BY a_index;");
    }

    private void NewMagicEditor_Load(object sender, EventArgs e)
    {
      this.LoadStartUp();
      this.LoadListBox();
      this.SelectBoxes();
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
      string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, " SELECT a_index, a_name, a_maxlevel, a_type, a_subtype, a_damagetype, a_hittype, a_attribute, a_psp, a_ptp, a_hsp, a_htp, a_togle  from t_magic WHERE a_index ='" + this.textBox1.Text + "';", new string[13]
      {
        "a_index",
        "a_name",
        "a_maxlevel",
        "a_type",
        "a_subtype",
        "a_damagetype",
        "a_hittype",
        "a_attribute",
        "a_psp",
        "a_ptp",
        "a_hsp",
        "a_htp",
        "a_togle"
      });
      this.textBox1.Text = strArray[0];
      this.textBox2.Text = strArray[1];
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
      this.tbSubtype.Text = strArray[4];
      this.SelectBoxes();
      this.dgItems.Rows.Clear();
      this.LoadDG(this.textBox1.Text);
    }

    private void SelectBoxes()
    {
      int num1 = this.comboBox1.FindString(this.textBox4.Text);
      int num2 = this.comboBox2.FindString(this.textBox5.Text);
      int num3 = this.comboBox3.FindString(this.textBox6.Text);
      int num4 = this.comboBox4.FindString(this.textBox7.Text);
      int num5 = this.cbSubType1.FindString(this.textBox5.Text);
      int num6 = this.cbSubType2.FindString(this.textBox5.Text);
      int num7 = this.cbSubType3.FindString(this.textBox5.Text);
      int num8 = this.cbSubType4.FindString(this.textBox5.Text);
      int num9 = this.cbSubType5.FindString(this.textBox5.Text);
      int num10 = this.cbSubType6.FindString(this.textBox5.Text);
      int num11 = this.cbSubType7.FindString(this.textBox5.Text);
      int num12 = this.cbSubType8.FindString(this.textBox5.Text);
      int num13 = this.cbSubType9.FindString(this.textBox5.Text);
      int num14 = this.cbSubType10.FindString(this.textBox5.Text);
      this.comboBox1.SelectedIndex = num1;
      this.comboBox2.SelectedIndex = num2;
      this.comboBox3.SelectedIndex = num3;
      this.comboBox4.SelectedIndex = num4;
      this.cbSubType1.SelectedIndex = num5;
      this.cbSubType2.SelectedIndex = num6;
      this.cbSubType3.SelectedIndex = num7;
      this.cbSubType4.SelectedIndex = num8;
      this.cbSubType5.SelectedIndex = num9;
      this.cbSubType6.SelectedIndex = num10;
      this.cbSubType7.SelectedIndex = num11;
      this.cbSubType8.SelectedIndex = num12;
      this.cbSubType9.SelectedIndex = num13;
      this.cbSubType10.SelectedIndex = num14;
    }

    public void LoadDG(string strIndex)
    {
      this.dgItems.Rows.Clear();
      string str = "SELECT * FROM t_magiclevel WHERE  a_index ='+" + strIndex + "' ORDER BY a_level";
      MySqlConnection mySqlConnection = new MySqlConnection("datasource=" + this.Host + ";Port=3306;User ID="  + this.User + ";Password=" + this.Password + ";Database=" + this.Database + ";Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;");
      MySqlCommand command = mySqlConnection.CreateCommand();
      command.CommandText = str;
      mySqlConnection.Open();
      MySqlDataReader mySqlDataReader = command.ExecuteReader();
      while (mySqlDataReader.Read())
        this.dgItems.Rows.Add((object) mySqlDataReader.GetValue(0).ToString(), (object) mySqlDataReader.GetValue(1).ToString(), (object) mySqlDataReader.GetValue(2).ToString(), (object) mySqlDataReader.GetValue(3).ToString());
      mySqlConnection.Close();
    }

    private void button3_Click(object sender, EventArgs e)
    {
      string Query = "UPDATE t_magic SET a_index = '" + this.textBox1.Text + "', a_type = '" + this.textBox4.Text + "', a_subtype = '" + this.textBox5.Text + "', " + "a_name = '" + this.textBox2.Text.Replace("'", "\\'").Replace("\"", "\\\"") + "', a_maxlevel = '" + this.textBox3.Text + "',a_damagetype = '" + this.textBox6.Text + "',a_hittype = '" + this.textBox7.Text + "',a_attribute = '" + this.textBox8.Text + "',a_psp = '" + this.textBox9.Text + "',a_ptp = '" + this.textBox10.Text + "',a_hsp = '" + this.textBox11.Text + "',a_htp = '" + this.textBox12.Text + "',a_togle = '" + this.textBox13.Text + "' WHERE a_index = '" + this.textBox1.Text + "'";
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, Query);
      Console.WriteLine(Query);
      int selectedIndex = this.listBox1.SelectedIndex;
      int num = (int) new CustomMessage("Done :)").ShowDialog();
      if (this.textBox14.Text != "")
        this.SearchList(this.textBox14.Text);
      else
        this.LoadListBox();
      this.listBox1.SelectedIndex = selectedIndex;
    }

    private void button1_Click(object sender, EventArgs e)
    {
      string str1 = "";
      string str2 = "select * from t_magic order by a_index DESC Limit 0,1";
      MySqlConnection mySqlConnection = new MySqlConnection("datasource=" + this.Host + ";Port=3306;User ID="  + this.User + ";Password=" + this.Password + ";Database=" + this.Database + ";Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;");
      MySqlCommand command = mySqlConnection.CreateCommand();
      command.CommandText = str2;
      mySqlConnection.Open();
      MySqlDataReader mySqlDataReader = command.ExecuteReader();
      while (mySqlDataReader.Read())
        str1 = mySqlDataReader.GetValue(0).ToString();
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_magic (a_index, a_name) VALUES ('" + (Convert.ToInt32(str1) + 1).ToString() + "', 'New Magic Skill')");
      this.LoadListBox();
      this.listBox1.SelectedIndex = this.listBox1.Items.Count - 1;
    }

    private void button2_Click(object sender, EventArgs e)
    {
      int selectedIndex = this.listBox1.SelectedIndex;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_magic WHERE a_index = '" + this.textBox1.Text + "'");
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_magiclevel WHERE a_index = '" + this.textBox1.Text + "'");
      this.LoadListBox();
      this.listBox1.SelectedIndex = selectedIndex - 1;
      int num = (int) new CustomMessage("Deleted :O").ShowDialog();
    }

    private void groupBox1_Enter(object sender, EventArgs e)
    {
    }

    private void btnSaveSelected_Click(object sender, EventArgs e)
    {
      DataGridViewRow row = this.dgItems.Rows[this.dgItems.CurrentRow.Index];
      string str1 = Convert.ToString(row.Cells["index"].Value);
      string str2 = Convert.ToString(row.Cells["Level"].Value);
      string str3 = Convert.ToString(row.Cells["Power"].Value);
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_magiclevel SET a_power = '" + Convert.ToString(row.Cells["Power"].Value) + "', a_hitrate = '" + Convert.ToString(row.Cells["HitRate"].Value) + "' WHERE a_index = '" + str1 + "' AND a_level = '" + str2 + "'");
      row.SetValues((object) str1, (object) str2, (object) str3);
      this.dgItems.Rows.Clear();
      this.LoadDG(this.textBox1.Text);
    }

    private void btnAddItems_Click(object sender, EventArgs e)
    {
      int num1 = this.databaseHandle.CountByRow(this.Host, this.User, this.Password, this.Database, "SELECT COUNT(*) FROM t_magiclevel WHERE a_index = '" + this.textBox1.Text + "' ") + 1;
      try
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_magiclevel (a_index, a_level, a_power, a_hitrate) VALUES (" + this.textBox1.Text + ", '" + num1.ToString() + "', 0, 0)");
      }
      catch
      {
        int num2 = (int) MessageBox.Show("Duplicated ItemID isn't allowed.", "Error");
      }
      this.dgItems.Rows.Clear();
      this.LoadDG(this.textBox1.Text);
    }

    private void toolStripButton1_Click(object sender, EventArgs e)
    {
      int num = this.databaseHandle.CountByRow(this.Host, this.User, this.Password, this.Database, "SELECT COUNT(*) FROM t_magiclevel WHERE a_index = '" + this.textBox1.Text + "' ");
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_magiclevel WHERE a_index ='" + Convert.ToString(this.dgItems.Rows[this.dgItems.CurrentRow.Index].Cells["index"].Value) + "' AND a_level = '" + num.ToString() + "'");
      this.dgItems.Rows.Clear();
      this.LoadDG(this.textBox1.Text);
    }

    public void SearchList(string searchString)
    {
      searchString = searchString.Replace("\\", "\\\\").Replace("'", "\\'");
      this.listBox1.DataSource = (object) this.databaseHandle.SelectMySqlReturnList(this.menuArray, this.Host, this.User, this.Password, this.Database, "select a_index, a_name from t_magic WHERE a_name LIKE '%" + searchString + "%' OR a_index LIKE '" + searchString + "' ORDER BY a_index;");
    }

    private void LoadStartUp()
    {
      this.comboBox1.Items.AddRange(new object[11]
      {
        (object) "0 - Stat",
        (object) "1 - Attribute",
        (object) "2 - Assist",
        (object) "3 - Attack",
        (object) "4 - Recover",
        (object) "5 - Cure",
        (object) "6 - Other",
        (object) "7 - Reduce",
        (object) "8 - Immune",
        (object) "9 - Castle War",
        (object) "10 - Money"
      });
      this.comboBox3.Items.AddRange(new object[3]
      {
        (object) "0 - Only Power",
        (object) "1 - Addition",
        (object) "2 - Rate"
      });
      this.comboBox4.Items.AddRange(new object[2]
      {
        (object) "0 - Constant",
        (object) "1 - Varible"
      });
      this.comboBox2.Items.AddRange(new object[39]
      {
        (object) "0 - Attack",
        (object) "1 - Defense",
        (object) "2 - Magic",
        (object) "3 - Resist",
        (object) "4 - Hitrate",
        (object) "5 - Avoid",
        (object) "6 - Critical",
        (object) "7 - Attack Speed",
        (object) "8 - MagicS peed",
        (object) "9 - Move Speed",
        (object) "10 - Recover HP",
        (object) "11 - Recover MP",
        (object) "12 - Max HP",
        (object) "13 - Max MP",
        (object) "14 - Deadldy",
        (object) "15 - Magic Hitrate",
        (object) "16 - Magic Avoid",
        (object) "17 - AttackDist",
        (object) "18 - Attack Melee",
        (object) "19 - Attack Range",
        (object) "20 - Hitrate Skill",
        (object) "21 - Attack 80",
        (object) "22 - Max Hp 450",
        (object) "23 - Skill Speed",
        (object) "24 - Valor",
        (object) "25 - Statpall",
        (object) "26 - Attack Per",
        (object) "27 - Defense Per",
        (object) "28 - Statpall Per",
        (object) "29 - STR",
        (object) "30 - DEX",
        (object) "31 - INT",
        (object) "32 - CON",
        (object) "33 - Hard",
        (object) "34 - Strong",
        (object) "35 - NPC Attack",
        (object) "36 - NPC Magic",
        (object) "37 - Skill Cool Time",
        (object) "38 - Decrase Mana Spend"
      });
      this.cbSubType1.Items.AddRange(new object[8]
      {
        (object) "0 - None",
        (object) "1 - Fire",
        (object) "2 - Water",
        (object) "3 - Earth",
        (object) "4 - Wind",
        (object) "5 - Dark",
        (object) "6 - Light",
        (object) "7 - Random"
      });
      this.cbSubType2.Items.AddRange(new object[56]
      {
        (object) "0 - Posion",
        (object) "1 - Hold",
        (object) "2 - Confusion",
        (object) "3 - Stone",
        (object) "4 - Silent",
        (object) "5 - Blood",
        (object) "6 - Blind",
        (object) "7 - Sturn",
        (object) "8 - Sleep",
        (object) "9 - HP",
        (object) "10 - MP",
        (object) "11 - Move Speed",
        (object) "12 - HP Cancel",
        (object) "13 - MP Cancel",
        (object) "14 - Dizzy",
        (object) "15 - Invisible",
        (object) "16 - Sloth",
        (object) "17 - Fear",
        (object) "18 - Fake Death",
        (object) "19 - Perfect Body",
        (object) "20 - Frenzy",
        (object) "21 - Damagelink",
        (object) "22 - Berserk",
        (object) "23 - Despair",
        (object) "24 - Manascreen",
        (object) "25 - Bless",
        (object) "26 - Safeguard",
        (object) "27 - Mantle",
        (object) "28 - Guard",
        (object) "29 - Charge Attack",
        (object) "30 - Charge Magic",
        (object) "31 - Disease",
        (object) "32 - Curse",
        (object) "33 - Confused",
        (object) "34 - Taming",
        (object) "35 - Freeze",
        (object) "36 - Inverse Damage",
        (object) "37 - HP Dot",
        (object) "38 - Rebirth",
        (object) "39 - Darkness Mode",
        (object) "40 - Aura Darkness",
        (object) "41 - Aura Weakness",
        (object) "42 - Aura Illusion",
        (object) "43 - Mercenary",
        (object) "44 - Soul Totem Buff",
        (object) "45 - Soul Totem Attack",
        (object) "46 - Trap",
        (object) "47 - Parasite",
        (object) "48 - Suicide",
        (object) "49 - Invincibilty",
        (object) "50 - GPS",
        (object) "51 - Attack Tower",
        (object) "52 - Artifact GPS",
        (object) "53 - Totem Item Buff",
        (object) "54 - Totem Item Attack",
        (object) "55 - Heal % Reduction"
      });
      this.cbSubType3.Items.AddRange(new object[6]
      {
        (object) "0 - Normal",
        (object) "1 - Critical",
        (object) "2 - Drain",
        (object) "3 - One Shot Kill",
        (object) "4 - Deadly",
        (object) "5 - Hard"
      });
      this.cbSubType4.Items.AddRange(new object[6]
      {
        (object) "0 - HP",
        (object) "1 - MP",
        (object) "2 - STM",
        (object) "3 - Faith",
        (object) "4 - EXP",
        (object) "5 - SP"
      });
      this.cbSubType5.Items.AddRange(new object[16]
      {
        (object) "0 - Posion",
        (object) "1 - Hold",
        (object) "2 - Confusion",
        (object) "3 - Stone",
        (object) "4 - Silent",
        (object) "5 - Blood",
        (object) "6 - Rebirth",
        (object) "7 - Invisible",
        (object) "8 - Sturn",
        (object) "9 - Sloth",
        (object) "10 - Not Help",
        (object) "11 - Blind",
        (object) "12 - Disease",
        (object) "13 - Curse",
        (object) "14 - All",
        (object) "15 - Instant Death"
      });
      this.cbSubType6.Items.AddRange(new object[31]
      {
        (object) "0 - Instant Death",
        (object) "1 - Skill Cancel",
        (object) "2 - Tackle",
        (object) "3 - Tackle2",
        (object) "4 - Reflex",
        (object) "5 - Death EXP Plus",
        (object) "6 - Death SP Plus",
        (object) "7 - Telekinesis",
        (object) "8 - Tount",
        (object) "9 - Summon",
        (object) "10 -  Evocation",
        (object) "11 - Targetfree",
        (object) "12 - Curse",
        (object) "13 - Peace",
        (object) "14 - Soul Drain",
        (object) "15 - Knockback",
        (object) "16 - Warp",
        (object) "17 - Fly",
        (object) "18 - EXP",
        (object) "19 - SP",
        (object) "20 - Itemdrop",
        (object) "21 - Skill",
        (object) "22 - PK Disposition",
        (object) "23 - Affinity",
        (object) "24 - Affinity Quest",
        (object) "25 - Affinity Monster",
        (object) "26 - Affinity Item",
        (object) "27 - Quest Exp",
        (object) "28 - Guild Party Exp",
        (object) "29 - Guild Party Sp",
        (object) "30 - Summon NPC"
      });
      this.cbSubType7.Items.AddRange(new object[4]
      {
        (object) "0 - Melee",
        (object) "1 - Range",
        (object) "2 - Magic",
        (object) "3 - Skill"
      });
      this.cbSubType8.Items.AddRange(new object[1]
      {
        (object) "0 - Blind"
      });
      this.cbSubType9.Items.AddRange(new object[7]
      {
        (object) "0 - Melee",
        (object) "1 - Range",
        (object) "2 - Magic",
        (object) "3 - Max HP",
        (object) "4 - Defense",
        (object) "5 - Resist",
        (object) "6 - Tower Attack"
      });
      this.cbSubType10.Items.AddRange(new object[3]
      {
        (object) "0 - Buy",
        (object) "1 - Sell",
        (object) "2 - Nas"
      });
    }

    public static string[] SubTypes(int Type)
    {
      List<string> stringList = new List<string>();
      switch (Type)
      {
        case 0:
          stringList.Add("0 - Attack");
          stringList.Add("1 - Defense");
          stringList.Add("2 - Magic");
          stringList.Add("3 - Resist");
          stringList.Add("4 - Hitrate");
          stringList.Add("5 - Avoid");
          stringList.Add("6 - Critical");
          stringList.Add("7 - Attack Speed");
          stringList.Add("8 - MagicS peed");
          stringList.Add("9 - Move Speed");
          stringList.Add("10 - Recover HP");
          stringList.Add("11 - Recover MP");
          stringList.Add("12 - Max HP");
          stringList.Add("13 - Max MP");
          stringList.Add("14 - Deadldy");
          stringList.Add("15 - MagicH itrate");
          stringList.Add("16 - Magic Avoid");
          stringList.Add("17 - AttackDist");
          stringList.Add("18 - Attack Melee");
          stringList.Add("19 - Attack Range");
          stringList.Add("20 - Hitrate Skill");
          stringList.Add("21 - Attack 80");
          stringList.Add("22 - Max Hp 450");
          stringList.Add("23 - Skill Speed");
          stringList.Add("24 - Valor");
          stringList.Add("25 - Statpall");
          stringList.Add("26 - Attack Per");
          stringList.Add("27 - Defense Per");
          stringList.Add("28 - Statpall Per");
          stringList.Add("29 - STR");
          stringList.Add("30 - DEX");
          stringList.Add("31 - INT");
          stringList.Add("32 - CON");
          stringList.Add("33 - Hard");
          stringList.Add("34 - Strong");
          stringList.Add("35 - NPC Attack");
          stringList.Add("36 - NPC Magic");
          stringList.Add("37 - Skill Cool Time");
          stringList.Add("38 - Decrase Mana Spend");
          break;
        case 1:
          stringList.Add("0 - None");
          stringList.Add("1 - Fire");
          stringList.Add("2 - Water");
          stringList.Add("3 - Earth");
          stringList.Add("4 - Wind");
          stringList.Add("5 - Dark");
          stringList.Add("6 - Light");
          stringList.Add("7 - Random");
          break;
        case 2:
          stringList.Add("0 - Posion");
          stringList.Add("1 - Hold");
          stringList.Add("2 - Confusion");
          stringList.Add("3 - Stone");
          stringList.Add("4 - Silent");
          stringList.Add("5 - Blood");
          stringList.Add("6 - Blind");
          stringList.Add("7 - Sturn");
          stringList.Add("8 - Sleep");
          stringList.Add("9 - HP");
          stringList.Add("10 - MP");
          stringList.Add("11 - Move Speed");
          stringList.Add("12 - HP Cancel");
          stringList.Add("13 - MP Cancel");
          stringList.Add("14 - Dizzy");
          stringList.Add("15 - Invisible");
          stringList.Add("16 - Sloth");
          stringList.Add("17 - Fear");
          stringList.Add("18 - Fake Death");
          stringList.Add("19 - Perfect Body");
          stringList.Add("20 - Frenzy");
          stringList.Add("21 - Damagelink");
          stringList.Add("22 - Berserk");
          stringList.Add("23 - Despair");
          stringList.Add("24 - Manascreen");
          stringList.Add("25 - Bless");
          stringList.Add("26 - Safeguard");
          stringList.Add("27 - Mantle");
          stringList.Add("28 - Guard");
          stringList.Add("29 - Charge Attack");
          stringList.Add("30 - Charge Magic");
          stringList.Add("31 - Disease");
          stringList.Add("32 - Curse");
          stringList.Add("33 - Confused");
          stringList.Add("34 - Taming");
          stringList.Add("35 - Freeze");
          stringList.Add("36 - Inverse Damage");
          stringList.Add("37 - HP Dot");
          stringList.Add("38 - Rebirth");
          stringList.Add("39 - Darkness Mode");
          stringList.Add("40 - Aura Darkness");
          stringList.Add("41 - Aura Weakness");
          stringList.Add("42 - Aura Illusion");
          stringList.Add("43 - Mercenary");
          stringList.Add("44 - Soul Totem Buff");
          stringList.Add("45 - Soul Totem Attack");
          stringList.Add("46 - Trap");
          stringList.Add("47 - Parasite");
          stringList.Add("48 - Suicide");
          stringList.Add("49 - Invincibilty");
          stringList.Add("50 - GPS");
          stringList.Add("51 - Attack Tower");
          stringList.Add("52 - Artifact GPS");
          stringList.Add("53 - Totem Item Buff");
          stringList.Add("54 - Totem Item Attack");
          stringList.Add("55 - Heal % Reduction");
          break;
        case 3:
          stringList.Add("0 - Normal");
          stringList.Add("1 - Critical");
          stringList.Add("2 - Drain");
          stringList.Add("3 - One Shot Kill");
          stringList.Add("4 - Deadly");
          stringList.Add("5 - Hard");
          break;
        case 4:
          stringList.Add("0 - HP");
          stringList.Add("1 - MP");
          stringList.Add("2 - STM");
          stringList.Add("3 - Faith");
          stringList.Add("4 - EXP");
          stringList.Add("5 - SP");
          break;
        case 5:
          stringList.Add("0 - Posion");
          stringList.Add("1 - Hold");
          stringList.Add("2 - Confusion");
          stringList.Add("3 - Stone");
          stringList.Add("4 - Silent");
          stringList.Add("5 - Blood");
          stringList.Add("6 - Rebirth");
          stringList.Add("7 - Invisible");
          stringList.Add("8 - Sturn");
          stringList.Add("9 - Sloth");
          stringList.Add("10 - Not Help");
          stringList.Add("11 - Blind");
          stringList.Add("12 - Disease");
          stringList.Add("13 - Curse");
          stringList.Add("14 - All");
          stringList.Add("15 - Instant Death");
          break;
        case 6:
          stringList.Add("0 - Instant Death");
          stringList.Add("1 - Skill Cancel");
          stringList.Add("2 - Tackle");
          stringList.Add("3 - Tackle2");
          stringList.Add("4 - Reflex");
          stringList.Add("5 - Death EXP Plus");
          stringList.Add("6 - Death SP Plus");
          stringList.Add("7 - Telekinesis");
          stringList.Add("8 - Tount");
          stringList.Add("9 - Summon");
          stringList.Add("10  Evocation");
          stringList.Add("11 - Targetfree");
          stringList.Add("12 - Curse");
          stringList.Add("13 - Peace");
          stringList.Add("14 - Soul Drain");
          stringList.Add("15 - Knockback");
          stringList.Add("16 - Warp");
          stringList.Add("17 - Fly");
          stringList.Add("18 - EXP");
          stringList.Add("19 - SP");
          stringList.Add("20 - Itemdrop");
          stringList.Add("21 - Skill");
          stringList.Add("22 - PK Disposition");
          stringList.Add("23 - Affinity");
          stringList.Add("24 - Affinity Quest");
          stringList.Add("25 - Affinity Monster");
          stringList.Add("26 - Affinity Item");
          stringList.Add("27 - Quest Exp");
          stringList.Add("28 - Guild Party Exp");
          stringList.Add("29 - Guild Party Sp");
          stringList.Add("30 - Summon NPC");
          break;
        case 7:
          stringList.Add("0 - Melee");
          stringList.Add("1 - Range");
          stringList.Add("2 - Magic");
          stringList.Add("3 - Skill");
          break;
        case 8:
          stringList.Add("0 - Blind");
          break;
        case 9:
          stringList.Add("0 - Melee");
          stringList.Add("1 - Range");
          stringList.Add("2 - Magic");
          stringList.Add("3 - Max HP");
          stringList.Add("4 - Defense");
          stringList.Add("5 - Resist");
          stringList.Add("6 - Tower Attack");
          break;
        case 10:
          stringList.Add("0 - Buy");
          stringList.Add("1 - Sell");
          stringList.Add("2 - Nas");
          break;
        default:
          stringList.Add("-1 - Unknown");
          break;
      }
      return stringList.ToArray();
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

    private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox4.Text = this.comboBox1.SelectedIndex.ToString();
      if (this.textBox4.Text == "0")
      {
        this.comboBox2.Visible = true;
        this.cbSubType1.Visible = false;
        this.cbSubType2.Visible = false;
        this.cbSubType3.Visible = false;
        this.cbSubType4.Visible = false;
        this.cbSubType5.Visible = false;
        this.cbSubType6.Visible = false;
        this.cbSubType7.Visible = false;
        this.cbSubType8.Visible = false;
        this.cbSubType9.Visible = false;
        this.cbSubType10.Visible = false;
      }
      else if (this.textBox4.Text == "1")
      {
        this.comboBox2.Visible = false;
        this.cbSubType1.Visible = true;
        this.cbSubType2.Visible = false;
        this.cbSubType3.Visible = false;
        this.cbSubType4.Visible = false;
        this.cbSubType5.Visible = false;
        this.cbSubType6.Visible = false;
        this.cbSubType7.Visible = false;
        this.cbSubType8.Visible = false;
        this.cbSubType9.Visible = false;
        this.cbSubType10.Visible = false;
      }
      else if (this.textBox4.Text == "2")
      {
        this.comboBox2.Visible = false;
        this.cbSubType1.Visible = false;
        this.cbSubType2.Visible = true;
        this.cbSubType3.Visible = false;
        this.cbSubType4.Visible = false;
        this.cbSubType5.Visible = false;
        this.cbSubType6.Visible = false;
        this.cbSubType7.Visible = false;
        this.cbSubType8.Visible = false;
        this.cbSubType9.Visible = false;
        this.cbSubType10.Visible = false;
      }
      else if (this.textBox4.Text == "3")
      {
        this.comboBox2.Visible = false;
        this.cbSubType1.Visible = false;
        this.cbSubType2.Visible = false;
        this.cbSubType3.Visible = true;
        this.cbSubType4.Visible = false;
        this.cbSubType5.Visible = false;
        this.cbSubType6.Visible = false;
        this.cbSubType7.Visible = false;
        this.cbSubType8.Visible = false;
        this.cbSubType9.Visible = false;
        this.cbSubType10.Visible = false;
      }
      else if (this.textBox4.Text == "4")
      {
        this.comboBox2.Visible = false;
        this.cbSubType1.Visible = false;
        this.cbSubType2.Visible = false;
        this.cbSubType3.Visible = false;
        this.cbSubType4.Visible = true;
        this.cbSubType5.Visible = false;
        this.cbSubType6.Visible = false;
        this.cbSubType7.Visible = false;
        this.cbSubType8.Visible = false;
        this.cbSubType9.Visible = false;
        this.cbSubType10.Visible = false;
      }
      else if (this.textBox4.Text == "5")
      {
        this.comboBox2.Visible = false;
        this.cbSubType1.Visible = false;
        this.cbSubType2.Visible = false;
        this.cbSubType3.Visible = false;
        this.cbSubType4.Visible = false;
        this.cbSubType5.Visible = true;
        this.cbSubType6.Visible = false;
        this.cbSubType7.Visible = false;
        this.cbSubType8.Visible = false;
        this.cbSubType9.Visible = false;
        this.cbSubType10.Visible = false;
      }
      else if (this.textBox4.Text == "6")
      {
        this.comboBox2.Visible = false;
        this.cbSubType1.Visible = false;
        this.cbSubType2.Visible = false;
        this.cbSubType3.Visible = false;
        this.cbSubType4.Visible = false;
        this.cbSubType5.Visible = false;
        this.cbSubType6.Visible = true;
        this.cbSubType7.Visible = false;
        this.cbSubType8.Visible = false;
        this.cbSubType9.Visible = false;
        this.cbSubType10.Visible = false;
      }
      else if (this.textBox4.Text == "7")
      {
        this.comboBox2.Visible = false;
        this.cbSubType1.Visible = false;
        this.cbSubType2.Visible = false;
        this.cbSubType3.Visible = false;
        this.cbSubType4.Visible = false;
        this.cbSubType5.Visible = false;
        this.cbSubType6.Visible = false;
        this.cbSubType7.Visible = true;
        this.cbSubType8.Visible = false;
        this.cbSubType9.Visible = false;
        this.cbSubType10.Visible = false;
      }
      else if (this.textBox4.Text == "8")
      {
        this.comboBox2.Visible = false;
        this.cbSubType1.Visible = false;
        this.cbSubType2.Visible = false;
        this.cbSubType3.Visible = false;
        this.cbSubType4.Visible = false;
        this.cbSubType5.Visible = false;
        this.cbSubType6.Visible = false;
        this.cbSubType7.Visible = false;
        this.cbSubType8.Visible = true;
        this.cbSubType9.Visible = false;
        this.cbSubType10.Visible = false;
      }
      else if (this.textBox4.Text == "9")
      {
        this.comboBox2.Visible = false;
        this.cbSubType1.Visible = false;
        this.cbSubType2.Visible = false;
        this.cbSubType3.Visible = false;
        this.cbSubType4.Visible = false;
        this.cbSubType5.Visible = false;
        this.cbSubType6.Visible = false;
        this.cbSubType7.Visible = false;
        this.cbSubType8.Visible = false;
        this.cbSubType9.Visible = true;
        this.cbSubType10.Visible = false;
      }
      else
      {
        if (!(this.textBox4.Text == "10"))
          return;
        this.comboBox2.Visible = false;
        this.cbSubType1.Visible = false;
        this.cbSubType2.Visible = false;
        this.cbSubType3.Visible = false;
        this.cbSubType4.Visible = false;
        this.cbSubType5.Visible = false;
        this.cbSubType6.Visible = false;
        this.cbSubType7.Visible = false;
        this.cbSubType8.Visible = false;
        this.cbSubType9.Visible = false;
        this.cbSubType10.Visible = true;
      }
    }

    private void textBox6_TextChanged(object sender, EventArgs e)
    {
    }

    private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (!(this.textBox4.Text == "0"))
        return;
      this.textBox5.Text = this.GetIndexByComboBox(this.comboBox2.Text).ToString();
    }

    private void comboBox3_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox6.Text = this.GetIndexByComboBox(this.comboBox3.Text).ToString();
    }

    private void comboBox4_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.textBox7.Text = this.GetIndexByComboBox(this.comboBox4.Text).ToString();
    }

    private void textBox14_TextChanged(object sender, EventArgs e)
    {
      this.SearchList(this.textBox14.Text);
    }

    private void comboBox5_SelectedIndexChanged(object sender, EventArgs e)
    {
    }

    private void groupBox6_Enter(object sender, EventArgs e)
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
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (LcDevPack_TeamDamonA.Tools.MemoryWorker.NewMagicEditor.NewMagicEditor));
      this.groupBox1 = new GroupBox();
      this.button2 = new Button();
      this.button1 = new Button();
      this.button3 = new Button();
      this.listBox1 = new ListBox();
      this.groupBox2 = new GroupBox();
      this.label4 = new Label();
      this.label1 = new Label();
      this.textBox2 = new TextBox();
      this.textBox1 = new TextBox();
      this.textBox3 = new TextBox();
      this.label2 = new Label();
      this.groupBox3 = new GroupBox();
      this.cbSubType10 = new ComboBox();
      this.cbSubType8 = new ComboBox();
      this.cbSubType9 = new ComboBox();
      this.cbSubType7 = new ComboBox();
      this.cbSubType5 = new ComboBox();
      this.cbSubType6 = new ComboBox();
      this.cbSubType2 = new ComboBox();
      this.cbSubType4 = new ComboBox();
      this.comboBox4 = new ComboBox();
      this.cbSubType3 = new ComboBox();
      this.cbSubType1 = new ComboBox();
      this.comboBox3 = new ComboBox();
      this.comboBox2 = new ComboBox();
      this.comboBox1 = new ComboBox();
      this.label6 = new Label();
      this.label5 = new Label();
      this.label3 = new Label();
      this.label7 = new Label();
      this.textBox4 = new TextBox();
      this.textBox5 = new TextBox();
      this.textBox6 = new TextBox();
      this.groupBox4 = new GroupBox();
      this.label14 = new Label();
      this.textBox13 = new TextBox();
      this.label12 = new Label();
      this.textBox12 = new TextBox();
      this.label11 = new Label();
      this.textBox11 = new TextBox();
      this.label10 = new Label();
      this.label9 = new Label();
      this.textBox10 = new TextBox();
      this.textBox9 = new TextBox();
      this.label8 = new Label();
      this.textBox8 = new TextBox();
      this.textBox7 = new TextBox();
      this.groupBox5 = new GroupBox();
      this.dgItems = new DataGridView();
      this.index = new DataGridViewTextBoxColumn();
      this.Level = new DataGridViewTextBoxColumn();
      this.Power = new DataGridViewTextBoxColumn();
      this.HitRate = new DataGridViewTextBoxColumn();
      this.toolStrip2 = new ToolStrip();
      this.btnSaveSelected = new ToolStripButton();
      this.toolStripSeparator1 = new ToolStripSeparator();
      this.btnAddItems = new ToolStripButton();
      this.toolStripSeparator6 = new ToolStripSeparator();
      this.toolStripButton1 = new ToolStripButton();
      this.groupBox6 = new GroupBox();
      this.label13 = new Label();
      this.textBox14 = new TextBox();
      this.tbSubtype = new TextBox();
      this.button17 = new Button();
      this.button18 = new Button();
      this.button19 = new Button();
      this.textBox15 = new TextBox();
      this.label15 = new Label();
      this.label17 = new Label();
      this.textBox16 = new TextBox();
      this.textBox17 = new TextBox();
      this.label16 = new Label();
      this.groupBox1.SuspendLayout();
      this.groupBox2.SuspendLayout();
      this.groupBox3.SuspendLayout();
      this.groupBox4.SuspendLayout();
      this.groupBox5.SuspendLayout();
      ((ISupportInitialize) this.dgItems).BeginInit();
      this.toolStrip2.SuspendLayout();
      this.groupBox6.SuspendLayout();
      this.SuspendLayout();
      this.groupBox1.Controls.Add((Control) this.button2);
      this.groupBox1.Controls.Add((Control) this.button1);
      this.groupBox1.Controls.Add((Control) this.button3);
      this.groupBox1.Controls.Add((Control) this.listBox1);
      this.groupBox1.Location = new Point(12, 71);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(223, 598);
      this.groupBox1.TabIndex = 2;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Magics";
      this.groupBox1.Enter += new EventHandler(this.groupBox1_Enter);
      this.button2.BackColor = SystemColors.Control;
      this.button2.FlatStyle = FlatStyle.Flat;
      this.button2.Location = new Point(117, 502);
      this.button2.Name = "button2";
      this.button2.Size = new Size(100, 23);
      this.button2.TabIndex = 2;
      this.button2.Text = "Delete";
      this.button2.UseVisualStyleBackColor = false;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.button1.BackColor = SystemColors.Control;
      this.button1.FlatStyle = FlatStyle.Flat;
      this.button1.Location = new Point(6, 502);
      this.button1.Name = "button1";
      this.button1.Size = new Size(100, 23);
      this.button1.TabIndex = 1;
      this.button1.Text = "Add";
      this.button1.UseVisualStyleBackColor = false;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.button3.BackColor = SystemColors.Control;
      this.button3.FlatStyle = FlatStyle.Flat;
      this.button3.Location = new Point(60, 548);
      this.button3.Name = "button3";
      this.button3.Size = new Size(100, 23);
      this.button3.TabIndex = 46;
      this.button3.Text = "Save";
      this.button3.UseVisualStyleBackColor = false;
      this.button3.Click += new EventHandler(this.button3_Click);
      this.listBox1.FormattingEnabled = true;
      this.listBox1.Location = new Point(6, 19);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new Size(211, 459);
      this.listBox1.TabIndex = 0;
      this.listBox1.SelectedIndexChanged += new EventHandler(this.listBox1_SelectedIndexChanged);
      this.groupBox2.Controls.Add((Control) this.label4);
      this.groupBox2.Controls.Add((Control) this.label1);
      this.groupBox2.Controls.Add((Control) this.textBox2);
      this.groupBox2.Controls.Add((Control) this.textBox1);
      this.groupBox2.Controls.Add((Control) this.textBox3);
      this.groupBox2.Controls.Add((Control) this.label2);
      this.groupBox2.Location = new Point(241, 12);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new Size(244, 133);
      this.groupBox2.TabIndex = 4;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "Main";
      this.label4.AutoSize = true;
      this.label4.Location = new Point(13, 47);
      this.label4.Name = "label4";
      this.label4.Size = new Size(38, 13);
      this.label4.TabIndex = 7;
      this.label4.Text = "Name:";
      this.label1.AutoSize = true;
      this.label1.Location = new Point(13, 21);
      this.label1.Name = "label1";
      this.label1.Size = new Size(36, 13);
      this.label1.TabIndex = 3;
      this.label1.Text = "Index:";
      this.textBox2.BorderStyle = BorderStyle.FixedSingle;
      this.textBox2.Location = new Point(54, 45);
      this.textBox2.Name = "textBox2";
      this.textBox2.Size = new Size(179, 20);
      this.textBox2.TabIndex = 1;
      this.textBox1.BorderStyle = BorderStyle.FixedSingle;
      this.textBox1.Location = new Point(54, 19);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(48, 20);
      this.textBox1.TabIndex = 0;
      this.textBox3.BorderStyle = BorderStyle.FixedSingle;
      this.textBox3.Location = new Point(185, 19);
      this.textBox3.Name = "textBox3";
      this.textBox3.Size = new Size(48, 20);
      this.textBox3.TabIndex = 6;
      this.label2.AutoSize = true;
      this.label2.Location = new Point(123, 21);
      this.label2.Name = "label2";
      this.label2.Size = new Size(56, 13);
      this.label2.TabIndex = 7;
      this.label2.Text = "MaxLevel:";
      this.groupBox3.Controls.Add((Control) this.cbSubType10);
      this.groupBox3.Controls.Add((Control) this.cbSubType8);
      this.groupBox3.Controls.Add((Control) this.cbSubType9);
      this.groupBox3.Controls.Add((Control) this.cbSubType7);
      this.groupBox3.Controls.Add((Control) this.cbSubType5);
      this.groupBox3.Controls.Add((Control) this.cbSubType6);
      this.groupBox3.Controls.Add((Control) this.cbSubType2);
      this.groupBox3.Controls.Add((Control) this.cbSubType4);
      this.groupBox3.Controls.Add((Control) this.comboBox4);
      this.groupBox3.Controls.Add((Control) this.cbSubType3);
      this.groupBox3.Controls.Add((Control) this.cbSubType1);
      this.groupBox3.Controls.Add((Control) this.comboBox3);
      this.groupBox3.Controls.Add((Control) this.comboBox2);
      this.groupBox3.Controls.Add((Control) this.comboBox1);
      this.groupBox3.Controls.Add((Control) this.label6);
      this.groupBox3.Controls.Add((Control) this.label5);
      this.groupBox3.Controls.Add((Control) this.label3);
      this.groupBox3.Controls.Add((Control) this.label7);
      this.groupBox3.Location = new Point(491, 12);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Size = new Size(289, 133);
      this.groupBox3.TabIndex = 5;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "Type";
      this.cbSubType10.FlatStyle = FlatStyle.Flat;
      this.cbSubType10.FormattingEnabled = true;
      this.cbSubType10.Location = new Point(90, 44);
      this.cbSubType10.Name = "cbSubType10";
      this.cbSubType10.Size = new Size(193, 21);
      this.cbSubType10.TabIndex = 49;
      this.cbSubType10.SelectedIndexChanged += new EventHandler(this.cbSubType10_SelectedIndexChanged);
      this.cbSubType8.FlatStyle = FlatStyle.Flat;
      this.cbSubType8.FormattingEnabled = true;
      this.cbSubType8.Location = new Point(90, 44);
      this.cbSubType8.Name = "cbSubType8";
      this.cbSubType8.Size = new Size(193, 21);
      this.cbSubType8.TabIndex = 47;
      this.cbSubType8.SelectedIndexChanged += new EventHandler(this.cbSubType8_SelectedIndexChanged);
      this.cbSubType9.FlatStyle = FlatStyle.Flat;
      this.cbSubType9.FormattingEnabled = true;
      this.cbSubType9.Location = new Point(90, 44);
      this.cbSubType9.Name = "cbSubType9";
      this.cbSubType9.Size = new Size(193, 21);
      this.cbSubType9.TabIndex = 48;
      this.cbSubType9.SelectedIndexChanged += new EventHandler(this.cbSubType9_SelectedIndexChanged);
      this.cbSubType7.FlatStyle = FlatStyle.Flat;
      this.cbSubType7.FormattingEnabled = true;
      this.cbSubType7.Location = new Point(90, 44);
      this.cbSubType7.Name = "cbSubType7";
      this.cbSubType7.Size = new Size(193, 21);
      this.cbSubType7.TabIndex = 46;
      this.cbSubType7.SelectedIndexChanged += new EventHandler(this.cbSubType7_SelectedIndexChanged);
      this.cbSubType5.FlatStyle = FlatStyle.Flat;
      this.cbSubType5.FormattingEnabled = true;
      this.cbSubType5.Location = new Point(90, 44);
      this.cbSubType5.Name = "cbSubType5";
      this.cbSubType5.Size = new Size(193, 21);
      this.cbSubType5.TabIndex = 44;
      this.cbSubType5.SelectedIndexChanged += new EventHandler(this.cbSubType5_SelectedIndexChanged);
      this.cbSubType6.FlatStyle = FlatStyle.Flat;
      this.cbSubType6.FormattingEnabled = true;
      this.cbSubType6.Location = new Point(90, 44);
      this.cbSubType6.Name = "cbSubType6";
      this.cbSubType6.Size = new Size(193, 21);
      this.cbSubType6.TabIndex = 45;
      this.cbSubType6.SelectedIndexChanged += new EventHandler(this.cbSubType6_SelectedIndexChanged);
      this.cbSubType2.FlatStyle = FlatStyle.Flat;
      this.cbSubType2.FormattingEnabled = true;
      this.cbSubType2.Location = new Point(90, 44);
      this.cbSubType2.Name = "cbSubType2";
      this.cbSubType2.Size = new Size(193, 21);
      this.cbSubType2.TabIndex = 41;
      this.cbSubType2.SelectedIndexChanged += new EventHandler(this.cbSubType2_SelectedIndexChanged);
      this.cbSubType4.FlatStyle = FlatStyle.Flat;
      this.cbSubType4.FormattingEnabled = true;
      this.cbSubType4.Location = new Point(90, 44);
      this.cbSubType4.Name = "cbSubType4";
      this.cbSubType4.Size = new Size(193, 21);
      this.cbSubType4.TabIndex = 43;
      this.cbSubType4.SelectedIndexChanged += new EventHandler(this.cbSubType4_SelectedIndexChanged);
      this.comboBox4.FlatStyle = FlatStyle.Flat;
      this.comboBox4.FormattingEnabled = true;
      this.comboBox4.Location = new Point(90, 96);
      this.comboBox4.Name = "comboBox4";
      this.comboBox4.Size = new Size(193, 21);
      this.comboBox4.TabIndex = 39;
      this.comboBox4.SelectedIndexChanged += new EventHandler(this.comboBox4_SelectedIndexChanged);
      this.cbSubType3.FlatStyle = FlatStyle.Flat;
      this.cbSubType3.FormattingEnabled = true;
      this.cbSubType3.Location = new Point(90, 44);
      this.cbSubType3.Name = "cbSubType3";
      this.cbSubType3.Size = new Size(193, 21);
      this.cbSubType3.TabIndex = 42;
      this.cbSubType3.SelectedIndexChanged += new EventHandler(this.cbSubType3_SelectedIndexChanged);
      this.cbSubType1.FlatStyle = FlatStyle.Flat;
      this.cbSubType1.FormattingEnabled = true;
      this.cbSubType1.Location = new Point(90, 44);
      this.cbSubType1.Name = "cbSubType1";
      this.cbSubType1.Size = new Size(193, 21);
      this.cbSubType1.TabIndex = 40;
      this.cbSubType1.SelectedIndexChanged += new EventHandler(this.cbSubType1_SelectedIndexChanged);
      this.comboBox3.FlatStyle = FlatStyle.Flat;
      this.comboBox3.FormattingEnabled = true;
      this.comboBox3.Location = new Point(90, 70);
      this.comboBox3.Name = "comboBox3";
      this.comboBox3.Size = new Size(193, 21);
      this.comboBox3.TabIndex = 38;
      this.comboBox3.SelectedIndexChanged += new EventHandler(this.comboBox3_SelectedIndexChanged);
      this.comboBox2.FlatStyle = FlatStyle.Flat;
      this.comboBox2.FormattingEnabled = true;
      this.comboBox2.Location = new Point(90, 44);
      this.comboBox2.Name = "comboBox2";
      this.comboBox2.Size = new Size(193, 21);
      this.comboBox2.TabIndex = 37;
      this.comboBox2.SelectedIndexChanged += new EventHandler(this.comboBox2_SelectedIndexChanged);
      this.comboBox1.FlatStyle = FlatStyle.Flat;
      this.comboBox1.FormattingEnabled = true;
      this.comboBox1.Location = new Point(90, 18);
      this.comboBox1.Name = "comboBox1";
      this.comboBox1.Size = new Size(193, 21);
      this.comboBox1.TabIndex = 36;
      this.comboBox1.SelectedIndexChanged += new EventHandler(this.comboBox1_SelectedIndexChanged);
      this.label6.AutoSize = true;
      this.label6.Location = new Point(16, 99);
      this.label6.Name = "label6";
      this.label6.Size = new Size(47, 13);
      this.label6.TabIndex = 7;
      this.label6.Text = "HitType:";
      this.label5.AutoSize = true;
      this.label5.Location = new Point(16, 47);
      this.label5.Name = "label5";
      this.label5.Size = new Size(53, 13);
      this.label5.TabIndex = 7;
      this.label5.Text = "SubType:";
      this.label3.AutoSize = true;
      this.label3.Location = new Point(16, 21);
      this.label3.Name = "label3";
      this.label3.Size = new Size(34, 13);
      this.label3.TabIndex = 9;
      this.label3.Text = "Type:";
      this.label7.AutoSize = true;
      this.label7.Location = new Point(16, 73);
      this.label7.Name = "label7";
      this.label7.Size = new Size(68, 13);
      this.label7.TabIndex = 9;
      this.label7.Text = "DamageTyp:";
      this.textBox4.BorderStyle = BorderStyle.FixedSingle;
      this.textBox4.Location = new Point(786, 33);
      this.textBox4.Name = "textBox4";
      this.textBox4.Size = new Size(48, 20);
      this.textBox4.TabIndex = 8;
      this.textBox4.Visible = false;
      this.textBox5.BorderStyle = BorderStyle.FixedSingle;
      this.textBox5.Location = new Point(786, 59);
      this.textBox5.Name = "textBox5";
      this.textBox5.Size = new Size(48, 20);
      this.textBox5.TabIndex = 6;
      this.textBox5.Visible = false;
      this.textBox6.BorderStyle = BorderStyle.FixedSingle;
      this.textBox6.Location = new Point(786, 85);
      this.textBox6.Name = "textBox6";
      this.textBox6.Size = new Size(48, 20);
      this.textBox6.TabIndex = 6;
      this.textBox6.Visible = false;
      this.textBox6.TextChanged += new EventHandler(this.textBox6_TextChanged);
      this.groupBox4.Controls.Add((Control) this.label14);
      this.groupBox4.Controls.Add((Control) this.textBox13);
      this.groupBox4.Controls.Add((Control) this.label12);
      this.groupBox4.Controls.Add((Control) this.textBox12);
      this.groupBox4.Controls.Add((Control) this.label11);
      this.groupBox4.Controls.Add((Control) this.textBox11);
      this.groupBox4.Controls.Add((Control) this.label10);
      this.groupBox4.Controls.Add((Control) this.label9);
      this.groupBox4.Controls.Add((Control) this.textBox10);
      this.groupBox4.Controls.Add((Control) this.textBox9);
      this.groupBox4.Controls.Add((Control) this.label8);
      this.groupBox4.Controls.Add((Control) this.textBox8);
      this.groupBox4.Location = new Point(241, 151);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Size = new Size(539, 100);
      this.groupBox4.TabIndex = 6;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "Misc";
      this.label14.AutoSize = true;
      this.label14.Location = new Point(17, 23);
      this.label14.Name = "label14";
      this.label14.Size = new Size(49, 13);
      this.label14.TabIndex = 20;
      this.label14.Text = "Attribute:";
      this.textBox13.BorderStyle = BorderStyle.FixedSingle;
      this.textBox13.Location = new Point(329, 71);
      this.textBox13.Name = "textBox13";
      this.textBox13.Size = new Size(48, 20);
      this.textBox13.TabIndex = 18;
      this.label12.AutoSize = true;
      this.label12.Location = new Point(266, 75);
      this.label12.Name = "label12";
      this.label12.Size = new Size(37, 13);
      this.label12.TabIndex = 17;
      this.label12.Text = "Togle:";
      this.textBox12.BorderStyle = BorderStyle.FixedSingle;
      this.textBox12.Location = new Point(329, 47);
      this.textBox12.Name = "textBox12";
      this.textBox12.Size = new Size(48, 20);
      this.textBox12.TabIndex = 16;
      this.label11.AutoSize = true;
      this.label11.Location = new Point(266, 49);
      this.label11.Name = "label11";
      this.label11.Size = new Size(32, 13);
      this.label11.TabIndex = 15;
      this.label11.Text = "HTP:";
      this.textBox11.BorderStyle = BorderStyle.FixedSingle;
      this.textBox11.Location = new Point(329, 21);
      this.textBox11.Name = "textBox11";
      this.textBox11.Size = new Size(48, 20);
      this.textBox11.TabIndex = 14;
      this.label10.AutoSize = true;
      this.label10.Location = new Point(266, 23);
      this.label10.Name = "label10";
      this.label10.Size = new Size(32, 13);
      this.label10.TabIndex = 9;
      this.label10.Text = "HSP:";
      this.label9.AutoSize = true;
      this.label9.Location = new Point(17, 73);
      this.label9.Name = "label9";
      this.label9.Size = new Size(31, 13);
      this.label9.TabIndex = 13;
      this.label9.Text = "PTP:";
      this.textBox10.BorderStyle = BorderStyle.FixedSingle;
      this.textBox10.Location = new Point(80, 71);
      this.textBox10.Name = "textBox10";
      this.textBox10.Size = new Size(48, 20);
      this.textBox10.TabIndex = 8;
      this.textBox9.BorderStyle = BorderStyle.FixedSingle;
      this.textBox9.Location = new Point(80, 47);
      this.textBox9.Name = "textBox9";
      this.textBox9.Size = new Size(48, 20);
      this.textBox9.TabIndex = 12;
      this.label8.AutoSize = true;
      this.label8.Location = new Point(17, 47);
      this.label8.Name = "label8";
      this.label8.Size = new Size(31, 13);
      this.label8.TabIndex = 11;
      this.label8.Text = "PSP:";
      this.textBox8.BorderStyle = BorderStyle.FixedSingle;
      this.textBox8.Location = new Point(80, 21);
      this.textBox8.Name = "textBox8";
      this.textBox8.Size = new Size(48, 20);
      this.textBox8.TabIndex = 10;
      this.textBox7.BorderStyle = BorderStyle.FixedSingle;
      this.textBox7.Location = new Point(786, 111);
      this.textBox7.Name = "textBox7";
      this.textBox7.Size = new Size(48, 20);
      this.textBox7.TabIndex = 8;
      this.textBox7.Visible = false;
      this.groupBox5.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left;
      this.groupBox5.Controls.Add((Control) this.dgItems);
      this.groupBox5.Controls.Add((Control) this.toolStrip2);
      this.groupBox5.Location = new Point(241, 257);
      this.groupBox5.Name = "groupBox5";
      this.groupBox5.Size = new Size(539, 357);
      this.groupBox5.TabIndex = 45;
      this.groupBox5.TabStop = false;
      this.groupBox5.Text = "Skill Level";
      this.dgItems.AllowUserToAddRows = false;
      this.dgItems.AllowUserToDeleteRows = false;
      this.dgItems.BackgroundColor = SystemColors.Control;
      this.dgItems.BorderStyle = BorderStyle.None;
      this.dgItems.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dgItems.Columns.AddRange((DataGridViewColumn) this.index, (DataGridViewColumn) this.Level, (DataGridViewColumn) this.Power, (DataGridViewColumn) this.HitRate);
      this.dgItems.Dock = DockStyle.Fill;
      this.dgItems.EnableHeadersVisualStyles = false;
      this.dgItems.Location = new Point(3, 16);
      this.dgItems.Name = "dgItems";
      this.dgItems.RowHeadersVisible = false;
      this.dgItems.RowTemplate.DefaultCellStyle.Format = "C2";
      this.dgItems.RowTemplate.DefaultCellStyle.NullValue = (object) null;
      this.dgItems.RowTemplate.Height = 25;
      this.dgItems.RowTemplate.Resizable = DataGridViewTriState.True;
      this.dgItems.Size = new Size(533, 313);
      this.dgItems.TabIndex = 0;
      this.dgItems.CellClick += new DataGridViewCellEventHandler(this.dgItems_CellClick);
      this.index.HeaderText = "Index";
      this.index.Name = "index";
      this.index.Visible = false;
      this.index.Width = 50;
      this.Level.HeaderText = "Level";
      this.Level.Name = "Level";
      this.Level.Width = 70;
      this.Power.HeaderText = "Power";
      this.Power.Name = "Power";
      this.Power.Width = 150;
      this.HitRate.HeaderText = "HitRate";
      this.HitRate.Name = "HitRate";
      this.HitRate.Width = 275;
      this.toolStrip2.Dock = DockStyle.Bottom;
      this.toolStrip2.GripStyle = ToolStripGripStyle.Hidden;
      this.toolStrip2.Items.AddRange(new ToolStripItem[5]
      {
        (ToolStripItem) this.btnSaveSelected,
        (ToolStripItem) this.toolStripSeparator1,
        (ToolStripItem) this.btnAddItems,
        (ToolStripItem) this.toolStripSeparator6,
        (ToolStripItem) this.toolStripButton1
      });
      this.toolStrip2.Location = new Point(3, 329);
      this.toolStrip2.Name = "toolStrip2";
      this.toolStrip2.Size = new Size(533, 25);
      this.toolStrip2.TabIndex = 1;
      this.toolStrip2.Text = "toolStrip2";
      this.btnSaveSelected.DisplayStyle = ToolStripItemDisplayStyle.Text;
      this.btnSaveSelected.ImageTransparentColor = Color.Magenta;
      this.btnSaveSelected.Name = "btnSaveSelected";
      this.btnSaveSelected.Size = new Size(62, 22);
      this.btnSaveSelected.Text = "Save Item";
      this.btnSaveSelected.Click += new EventHandler(this.btnSaveSelected_Click);
      this.toolStripSeparator1.Name = "toolStripSeparator1";
      this.toolStripSeparator1.Size = new Size(6, 25);
      this.btnAddItems.DisplayStyle = ToolStripItemDisplayStyle.Text;
      this.btnAddItems.ImageTransparentColor = Color.Magenta;
      this.btnAddItems.Name = "btnAddItems";
      this.btnAddItems.Size = new Size(60, 22);
      this.btnAddItems.Text = "Add Item";
      this.btnAddItems.Click += new EventHandler(this.btnAddItems_Click);
      this.toolStripSeparator6.Name = "toolStripSeparator6";
      this.toolStripSeparator6.Size = new Size(6, 25);
      this.toolStripButton1.DisplayStyle = ToolStripItemDisplayStyle.Text;
      this.toolStripButton1.ImageTransparentColor = Color.Magenta;
      this.toolStripButton1.Name = "toolStripButton1";
      this.toolStripButton1.Size = new Size(44, 22);
      this.toolStripButton1.Text = "Delete";
      this.toolStripButton1.Click += new EventHandler(this.toolStripButton1_Click);
      this.groupBox6.Controls.Add((Control) this.label13);
      this.groupBox6.Controls.Add((Control) this.textBox14);
      this.groupBox6.Location = new Point(12, 12);
      this.groupBox6.Name = "groupBox6";
      this.groupBox6.Size = new Size(223, 53);
      this.groupBox6.TabIndex = 33;
      this.groupBox6.TabStop = false;
      this.groupBox6.Text = "Search";
      this.groupBox6.Enter += new EventHandler(this.groupBox6_Enter);
      this.label13.AutoSize = true;
      this.label13.Location = new Point(6, 21);
      this.label13.Name = "label13";
      this.label13.Size = new Size(31, 13);
      this.label13.TabIndex = 21;
      this.label13.Text = "Text:";
      this.textBox14.BorderStyle = BorderStyle.FixedSingle;
      this.textBox14.Location = new Point(53, 19);
      this.textBox14.Name = "textBox14";
      this.textBox14.Size = new Size(164, 20);
      this.textBox14.TabIndex = 20;
      this.textBox14.TextChanged += new EventHandler(this.textBox14_TextChanged);
      this.tbSubtype.BorderStyle = BorderStyle.FixedSingle;
      this.tbSubtype.Location = new Point(786, 151);
      this.tbSubtype.Name = "tbSubtype";
      this.tbSubtype.Size = new Size(48, 20);
      this.tbSubtype.TabIndex = 47;
      this.tbSubtype.Visible = false;
      this.button17.BackColor = Color.LightCoral;
      this.button17.FlatStyle = FlatStyle.Flat;
      this.button17.Image = (Image) Resources.delete;
      this.button17.ImageAlign = ContentAlignment.MiddleLeft;
      this.button17.Location = new Point(761, 622);
      this.button17.Name = "button17";
      this.button17.Size = new Size(65, 27);
      this.button17.TabIndex = 106;
      this.button17.Text = "    Delete";
      this.button17.UseVisualStyleBackColor = false;
      this.button17.Click += new EventHandler(this.button17_Click);
      this.button18.BackColor = Color.LightCyan;
      this.button18.FlatStyle = FlatStyle.Flat;
      this.button18.Image = (Image) Resources._08;
      this.button18.ImageAlign = ContentAlignment.MiddleLeft;
      this.button18.Location = new Point(675, 622);
      this.button18.Name = "button18";
      this.button18.Size = new Size(72, 27);
      this.button18.TabIndex = 105;
      this.button18.Text = "      Update";
      this.button18.UseVisualStyleBackColor = false;
      this.button18.Click += new EventHandler(this.button18_Click);
      this.button19.BackColor = Color.Plum;
      this.button19.FlatStyle = FlatStyle.Flat;
      this.button19.Image = (Image) Resources.control_add_blue;
      this.button19.ImageAlign = ContentAlignment.MiddleLeft;
      this.button19.Location = new Point(590, 622);
      this.button19.Name = "button19";
      this.button19.Size = new Size(71, 27);
      this.button19.TabIndex = 104;
      this.button19.Text = "     Add";
      this.button19.UseVisualStyleBackColor = false;
      this.button19.Click += new EventHandler(this.button19_Click);
      this.textBox15.BorderStyle = BorderStyle.FixedSingle;
      this.textBox15.Location = new Point(295, 626);
      this.textBox15.Name = "textBox15";
      this.textBox15.Size = new Size(100, 20);
      this.textBox15.TabIndex = 107;
      this.label15.AutoSize = true;
      this.label15.Location = new Point(249, 629);
      this.label15.Name = "label15";
      this.label15.Size = new Size(40, 13);
      this.label15.TabIndex = 108;
      this.label15.Text = "Power:";
      this.label17.AutoSize = true;
      this.label17.Location = new Point(424, 629);
      this.label17.Name = "label17";
      this.label17.Size = new Size(41, 13);
      this.label17.TabIndex = 110;
      this.label17.Text = "Hitrate:";
      this.textBox16.BorderStyle = BorderStyle.FixedSingle;
      this.textBox16.Location = new Point(471, 626);
      this.textBox16.Name = "textBox16";
      this.textBox16.Size = new Size(100, 20);
      this.textBox16.TabIndex = 111;
      this.textBox17.BorderStyle = BorderStyle.FixedSingle;
      this.textBox17.Location = new Point(295, 652);
      this.textBox17.Name = "textBox17";
      this.textBox17.Size = new Size(63, 20);
      this.textBox17.TabIndex = 112;
      this.textBox17.Visible = false;
      this.label16.AutoSize = true;
      this.label16.Location = new Point(0, 0);
      this.label16.Name = "label16";
      this.label16.Size = new Size(41, 13);
      this.label16.TabIndex = 109;
      this.label16.Text = "label16";
      this.label16.Visible = false;
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(836, 678);
      this.Controls.Add((Control) this.textBox17);
      this.Controls.Add((Control) this.textBox16);
      this.Controls.Add((Control) this.label17);
      this.Controls.Add((Control) this.label16);
      this.Controls.Add((Control) this.label15);
      this.Controls.Add((Control) this.textBox15);
      this.Controls.Add((Control) this.button17);
      this.Controls.Add((Control) this.button18);
      this.Controls.Add((Control) this.button19);
      this.Controls.Add((Control) this.tbSubtype);
      this.Controls.Add((Control) this.groupBox6);
      this.Controls.Add((Control) this.groupBox5);
      this.Controls.Add((Control) this.textBox6);
      this.Controls.Add((Control) this.groupBox4);
      this.Controls.Add((Control) this.textBox5);
      this.Controls.Add((Control) this.groupBox3);
      this.Controls.Add((Control) this.textBox7);
      this.Controls.Add((Control) this.textBox4);
      this.Controls.Add((Control) this.groupBox2);
      this.Controls.Add((Control) this.groupBox1);
      this.Icon = (Icon) componentResourceManager.GetObject("$this.Icon");
      this.Name = nameof (NewMagicEditor);
      this.Text = "Magic Editor";
      this.Load += new EventHandler(this.NewMagicEditor_Load);
      this.groupBox1.ResumeLayout(false);
      this.groupBox2.ResumeLayout(false);
      this.groupBox2.PerformLayout();
      this.groupBox3.ResumeLayout(false);
      this.groupBox3.PerformLayout();
      this.groupBox4.ResumeLayout(false);
      this.groupBox4.PerformLayout();
      this.groupBox5.ResumeLayout(false);
      this.groupBox5.PerformLayout();
      ((ISupportInitialize) this.dgItems).EndInit();
      this.toolStrip2.ResumeLayout(false);
      this.toolStrip2.PerformLayout();
      this.groupBox6.ResumeLayout(false);
      this.groupBox6.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();
    }

    private void cbSubType1_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (!(this.textBox4.Text == "1"))
        return;
      this.textBox5.Text = this.GetIndexByComboBox(this.cbSubType1.Text).ToString();
    }

    private void cbSubType2_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (!(this.textBox4.Text == "2"))
        return;
      this.textBox5.Text = this.GetIndexByComboBox(this.cbSubType2.Text).ToString();
    }

    private void cbSubType3_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (!(this.textBox4.Text == "3"))
        return;
      this.textBox5.Text = this.GetIndexByComboBox(this.cbSubType3.Text).ToString();
    }

    private void cbSubType4_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (!(this.textBox4.Text == "4"))
        return;
      this.textBox5.Text = this.GetIndexByComboBox(this.cbSubType4.Text).ToString();
    }

    private void cbSubType5_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (!(this.textBox4.Text == "5"))
        return;
      this.textBox5.Text = this.GetIndexByComboBox(this.cbSubType5.Text).ToString();
    }

    private void cbSubType6_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (!(this.textBox4.Text == "6"))
        return;
      this.textBox5.Text = this.GetIndexByComboBox(this.cbSubType6.Text).ToString();
    }

    private void cbSubType7_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (!(this.textBox4.Text == "7"))
        return;
      this.textBox5.Text = this.GetIndexByComboBox(this.cbSubType7.Text).ToString();
    }

    private void cbSubType8_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (!(this.textBox4.Text == "8"))
        return;
      this.textBox5.Text = this.GetIndexByComboBox(this.cbSubType8.Text).ToString();
    }

    private void cbSubType9_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (!(this.textBox4.Text == "9"))
        return;
      this.textBox5.Text = this.GetIndexByComboBox(this.cbSubType9.Text).ToString();
    }

    private void cbSubType10_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (!(this.textBox4.Text == "10"))
        return;
      this.textBox5.Text = this.GetIndexByComboBox(this.cbSubType10.Text).ToString();
    }

    private void button19_Click(object sender, EventArgs e)
    {
      int num1 = this.databaseHandle.CountByRow(this.Host, this.User, this.Password, this.Database, "SELECT COUNT(*) FROM t_magiclevel WHERE a_index = '" + this.textBox1.Text + "' ") + 1;
      try
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_magiclevel (a_index, a_level, a_power, a_hitrate) VALUES (" + this.textBox1.Text + ", '" + num1.ToString() + "', '" + this.textBox15.Text + "', '" + this.textBox16.Text + "')");
      }
      catch
      {
        int num2 = (int) MessageBox.Show("Duplicated ItemID isn't allowed.", "Error");
      }
      this.dgItems.Rows.Clear();
      this.LoadDG(this.textBox1.Text);
    }

    private void button17_Click(object sender, EventArgs e)
    {
      int num = this.databaseHandle.CountByRow(this.Host, this.User, this.Password, this.Database, "SELECT COUNT(*) FROM t_magiclevel WHERE a_index = '" + this.textBox1.Text + "' ");
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_magiclevel WHERE a_index ='" + Convert.ToString(this.dgItems.Rows[this.dgItems.CurrentRow.Index].Cells["index"].Value) + "' AND a_level = '" + num.ToString() + "'");
      this.dgItems.Rows.Clear();
      this.LoadDG(this.textBox1.Text);
    }

    private void dgItems_CellClick(object sender, DataGridViewCellEventArgs e)
    {
      if (e.RowIndex < 0)
        return;
      DataGridViewRow row = this.dgItems.Rows[e.RowIndex];
      this.textBox1.Text = row.Cells["index"].Value.ToString();
      this.textBox17.Text = row.Cells["Level"].Value.ToString();
      this.textBox15.Text = row.Cells["Power"].Value.ToString();
      this.textBox16.Text = row.Cells["HitRate"].Value.ToString();
    }

    private void button18_Click(object sender, EventArgs e)
    {
      if (Convert.ToInt32(this.textBox15.Text) <= 0 || Convert.ToInt32(this.textBox16.Text) <= 0)
      {
        int num1 = (int) MessageBox.Show("You need add value", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_magiclevel SET a_power = '" + this.textBox15.Text + "', a_hitrate = '" + this.textBox16.Text + "' WHERE a_index = '" + this.textBox1.Text + "' AND a_level = '" + this.textBox17.Text + "'");
        int num2 = (int) MessageBox.Show("Your Magic Level is Saved!");
        this.dgItems.Rows.Clear();
        this.LoadDG(this.textBox1.Text);
      }
    }
  }
}
