// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using LcDevPack_TeamDamonA.Properties;
using MySqlConnector;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange
{
  public class ExChange : Form
  {
    public static Connection connection = new Connection();
    private string Host = LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.connection.Settings.SqlHost;
    private string User = LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.connection.Settings.SqlUser;
    private string Password = LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.connection.Settings.SqlPassword;
    private string Database = LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.connection.Settings.SqlDatabase;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    private ExportLodHandle exportLodHandle = new ExportLodHandle();
    public static List<t_EXChange> ExChangeList = new List<t_EXChange>();
    public string _ClientPath = LcDevPack_TeamDamonA.Tools.MobEditor.connection.Settings.ClientPath;
    private IContainer components = (IContainer) null;
    private GroupBox groupBox3;
    private Button button3;
    private Button button1;
    private ListBox listBox1;
    private MenuStrip menuStrip1;
    private StatusStrip statusStrip1;
    private ToolStripStatusLabel toolStripStatusLabel1;
    private GroupBox groupBox4;
    private GroupBox groupBox2;
    private Label label10;
    private Label label8;
    private TextBox textBox6;
    private TextBox textBox9;
    private GroupBox groupBox1;
    private TextBox textBox11;
    private Label label4;
    private Label label3;
    private Label label2;
    private TextBox textBox2;
    private Label label1;
    private TextBox textBox1;
    private TextBox textBox3;
    private TextBox textBox4;
    private Button button2;
    private PictureBox PbSelectID1;
    private PictureBox pictureBox1;
    private TextBox tbFileID;
    private TextBox tbFileRow;
    private TextBox tbFileCol;
    private PictureBox pictureBox2;
    private PictureBox pictureBox3;
    private Label label5;
    private TextBox tb_source_itemIndex0;
    private PictureBox pictureBox10;
    private PictureBox pictureBox11;
    private Label label11;
    private TextBox tb_source_itemIndex4;
    private PictureBox pictureBox8;
    private PictureBox pictureBox9;
    private Label label9;
    private TextBox tb_source_itemIndex3;
    private PictureBox pictureBox6;
    private PictureBox pictureBox7;
    private Label label7;
    private TextBox tb_source_itemIndex2;
    private PictureBox pictureBox4;
    private PictureBox pictureBox5;
    private Label label6;
    private TextBox tb_source_itemIndex1;
    private TextBox tbFileCol0;
    private TextBox tbFileRow0;
    private TextBox tbFileID0;
    private TextBox tbFileCol4;
    private TextBox tbFileRow4;
    private TextBox tbFileID4;
    private TextBox tbFileCol3;
    private TextBox tbFileRow3;
    private TextBox tbFileID3;
    private TextBox tbFileCol2;
    private TextBox tbFileRow2;
    private TextBox tbFileID2;
    private TextBox tbFileCol1;
    private TextBox tbFileRow1;
    private TextBox tbFileID1;
    private GroupBox groupBox5;
    private Label label12;
    private TextBox tb_count_itemIndex4;
    private Label label13;
    private TextBox tb_count_itemIndex3;
    private Label label14;
    private TextBox tb_count_itemIndex2;
    private Label label15;
    private TextBox tb_count_itemIndex1;
    private Label label16;
    private TextBox tb_count_itemIndex0;
    private ToolStripMenuItem fileToolStripMenuItem;
    private ToolStripMenuItem saveToLodToolStripMenuItem;
    private CheckBox checkBox1;
    private Label label17;

    public ExChange() => this.InitializeComponent();

    private void LoadListBox()
    {
      MySqlConnection connection = new MySqlConnection("datasource=" + this.Host + ";Port=3306;User ID="  + this.User + ";Password=" + this.Password + ";Database=" + this.Database + ";Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;");
      connection.Open();
      MySqlCommand mySqlCommand = new MySqlCommand("SELECT * FROM t_item_exchange ORDER BY a_index ASC;", connection);
      mySqlCommand.ExecuteNonQuery();
      MySqlDataReader mySqlDataReader = mySqlCommand.ExecuteReader();
      while (mySqlDataReader.Read())
        LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList.Add(new t_EXChange()
        {
          IndexID = (int) mySqlDataReader["a_index"],
          Enable = (int) mySqlDataReader["a_enable"],
          NpcIndex = (int) mySqlDataReader["a_npc_index"],
          ResultItemIdx = (int) mySqlDataReader["result_itemIndex"],
          ResultItemCount = (int) mySqlDataReader["result_itemCount"],
          SourceItemIndex0 = (int) mySqlDataReader["source_itemIndex0"],
          SourceItemIndex1 = (int) mySqlDataReader["source_itemIndex1"],
          SourceItemIndex2 = (int) mySqlDataReader["source_itemIndex2"],
          SourceItemIndex3 = (int) mySqlDataReader["source_itemIndex3"],
          SourceItemIndex4 = (int) mySqlDataReader["source_itemIndex4"],
          SourceItemCount0 = (int) mySqlDataReader["source_itemCount0"],
          SourceItemCount1 = (int) mySqlDataReader["source_itemCount1"],
          SourceItemCount2 = (int) mySqlDataReader["source_itemCount2"],
          SourceItemCount3 = (int) mySqlDataReader["source_itemCount3"],
          SourceItemCount4 = (int) mySqlDataReader["source_itemCount4"]
        });
      this.listBox1.Items.Clear();
      int num = LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList.Count<t_EXChange>();
      for (int index = 0; index < num; ++index)
      {
        int indexId = LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index].IndexID;
        int npcIndex = LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index].NpcIndex;
        this.listBox1.Items.Add((object) (indexId.ToString() + " - NPC ID  - " + npcIndex.ToString()));
      }
      connection.Close();
    }

    private void ExChange_Load(object sender, EventArgs e) => this.LoadListBox();

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
      if (this.listBox1.SelectedIndex == -1)
        return;
      int Item = Convert.ToInt32(this.listBox1.SelectedItem.ToString().Split('-')[0]);
      int index = LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList.FindIndex((Predicate<t_EXChange>) (p => p.IndexID.Equals(Item)));
      this.textBox1.Text = Convert.ToString(Item);
      this.textBox2.Text = LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index].Enable.ToString();
      this.textBox3.Text = LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index].NpcIndex.ToString();
      this.textBox6.Text = LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index].ResultItemIdx.ToString();
      this.textBox9.Text = LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index].ResultItemCount.ToString();
      this.tb_source_itemIndex0.Text = LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index].SourceItemIndex0.ToString();
      this.tb_source_itemIndex1.Text = LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index].SourceItemIndex1.ToString();
      this.tb_source_itemIndex2.Text = LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index].SourceItemIndex2.ToString();
      this.tb_source_itemIndex3.Text = LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index].SourceItemIndex3.ToString();
      this.tb_source_itemIndex4.Text = LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index].SourceItemIndex4.ToString();
      this.tb_count_itemIndex0.Text = LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index].SourceItemCount0.ToString();
      this.tb_count_itemIndex1.Text = LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index].SourceItemCount1.ToString();
      this.tb_count_itemIndex2.Text = LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index].SourceItemCount2.ToString();
      this.tb_count_itemIndex3.Text = LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index].SourceItemCount3.ToString();
      this.tb_count_itemIndex4.Text = LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index].SourceItemCount4.ToString();
      try
      {
        this.pictureBox1.Image = (Image) this.databaseHandle.IconItem(int.Parse(this.tbFileID.Text), int.Parse(this.tbFileRow.Text), int.Parse(this.tbFileCol.Text));
        this.pictureBox3.Image = (Image) this.databaseHandle.IconItem(int.Parse(this.tbFileID0.Text), int.Parse(this.tbFileRow0.Text), int.Parse(this.tbFileCol0.Text));
        this.pictureBox5.Image = (Image) this.databaseHandle.IconItem(int.Parse(this.tbFileID1.Text), int.Parse(this.tbFileRow1.Text), int.Parse(this.tbFileCol1.Text));
        this.pictureBox7.Image = (Image) this.databaseHandle.IconItem(int.Parse(this.tbFileID2.Text), int.Parse(this.tbFileRow2.Text), int.Parse(this.tbFileCol2.Text));
        this.pictureBox9.Image = (Image) this.databaseHandle.IconItem(int.Parse(this.tbFileID3.Text), int.Parse(this.tbFileRow3.Text), int.Parse(this.tbFileCol3.Text));
        this.pictureBox11.Image = (Image) this.databaseHandle.IconItem(int.Parse(this.tbFileID4.Text), int.Parse(this.tbFileRow4.Text), int.Parse(this.tbFileCol4.Text));
      }
      catch
      {
      }
    }

    private void IconResult()
    {
      string Query = "select a_index, a_texture_id, a_texture_row, a_texture_col FROM t_item WHERE a_index ='" + this.textBox6.Text + "';";
      string[] rows = new string[4]
      {
        "a_index",
        "a_texture_id",
        "a_texture_row",
        "a_texture_col"
      };
      Query.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'");
      string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query, rows);
      this.tbFileID.Text = strArray[1];
      this.tbFileRow.Text = strArray[2];
      this.tbFileCol.Text = strArray[3];
    }

    private void textBox6_TextChanged(object sender, EventArgs e) => this.IconResult();

    private void Iconsource_itemIndex0()
    {
      string Query = "select a_index, a_texture_id, a_texture_row, a_texture_col FROM t_item WHERE a_index ='" + this.tb_source_itemIndex0.Text + "';";
      string[] rows = new string[4]
      {
        "a_index",
        "a_texture_id",
        "a_texture_row",
        "a_texture_col"
      };
      Query.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'");
      string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query, rows);
      this.tbFileID0.Text = strArray[1];
      this.tbFileRow0.Text = strArray[2];
      this.tbFileCol0.Text = strArray[3];
    }

    private void tb_source_itemIndex0_TextChanged(object sender, EventArgs e)
    {
      this.Iconsource_itemIndex0();
    }

    private void Iconsource_itemIndex1()
    {
      string Query = "select a_index, a_texture_id, a_texture_row, a_texture_col FROM t_item WHERE a_index ='" + this.tb_source_itemIndex1.Text + "';";
      string[] rows = new string[4]
      {
        "a_index",
        "a_texture_id",
        "a_texture_row",
        "a_texture_col"
      };
      Query.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'");
      string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query, rows);
      this.tbFileID1.Text = strArray[1];
      this.tbFileRow1.Text = strArray[2];
      this.tbFileCol1.Text = strArray[3];
    }

    private void tb_source_itemIndex1_TextChanged(object sender, EventArgs e)
    {
      this.Iconsource_itemIndex1();
    }

    private void Iconsource_itemIndex2()
    {
      string Query = "select a_index, a_texture_id, a_texture_row, a_texture_col FROM t_item WHERE a_index ='" + this.tb_source_itemIndex2.Text + "';";
      string[] rows = new string[4]
      {
        "a_index",
        "a_texture_id",
        "a_texture_row",
        "a_texture_col"
      };
      Query.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'");
      string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query, rows);
      this.tbFileID2.Text = strArray[1];
      this.tbFileRow2.Text = strArray[2];
      this.tbFileCol2.Text = strArray[3];
    }

    private void tb_source_itemIndex2_TextChanged(object sender, EventArgs e)
    {
      this.Iconsource_itemIndex2();
    }

    private void Iconsource_itemIndex3()
    {
      string Query = "select a_index, a_texture_id, a_texture_row, a_texture_col FROM t_item WHERE a_index ='" + this.tb_source_itemIndex3.Text + "';";
      string[] rows = new string[4]
      {
        "a_index",
        "a_texture_id",
        "a_texture_row",
        "a_texture_col"
      };
      Query.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'");
      string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query, rows);
      this.tbFileID3.Text = strArray[1];
      this.tbFileRow3.Text = strArray[2];
      this.tbFileCol3.Text = strArray[3];
    }

    private void tb_source_itemIndex3_TextChanged(object sender, EventArgs e)
    {
      this.Iconsource_itemIndex3();
    }

    private void Iconsource_itemIndex4()
    {
      string Query = "select a_index, a_texture_id, a_texture_row, a_texture_col FROM t_item WHERE a_index ='" + this.tb_source_itemIndex4.Text + "';";
      string[] rows = new string[4]
      {
        "a_index",
        "a_texture_id",
        "a_texture_row",
        "a_texture_col"
      };
      Query.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'");
      string[] strArray = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query, rows);
      this.tbFileID4.Text = strArray[1];
      this.tbFileRow4.Text = strArray[2];
      this.tbFileCol4.Text = strArray[3];
    }

    private void tb_source_itemIndex4_TextChanged(object sender, EventArgs e)
    {
      this.Iconsource_itemIndex4();
    }

    private void NpcNameRead()
    {
      string Query = "select a_index, a_name FROM t_npc WHERE a_index ='" + this.textBox3.Text + "';";
      string[] rows = new string[2]{ "a_index", "a_name" };
      Query.Replace("'", "\\'").Replace("\\", "\\\\").Replace("'", "\\'");
      this.textBox4.Text = this.databaseHandle.SelectMySqlReturnArray(this.Host, this.User, this.Password, this.Database, Query, rows)[1];
    }

    private void textBox3_TextChanged(object sender, EventArgs e) => this.NpcNameRead();

    private void openToolStripMenuItem_Click(object sender, EventArgs e)
    {
    }

    private void button1_Click(object sender, EventArgs e)
    {
      if (this.listBox1.Items.Count == 0)
        return;
      int num1 = LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList.Count - 1].IndexID + 1;
      LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList.Add(new t_EXChange()
      {
        IndexID = num1
      });
      this.listBox1.Items.Clear();
      int num2 = LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList.Count<t_EXChange>();
      for (int index = 0; index < num2; ++index)
      {
        int indexId = LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index].IndexID;
        int npcIndex = LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index].NpcIndex;
        this.listBox1.Items.Add((object) (indexId.ToString() + " - " + npcIndex.ToString()));
      }
      if (this.checkBox1.Checked)
      {
        MySqlConnection connection = new MySqlConnection("datasource=" + this.Host + ";Port=3306;User ID="  + this.User + ";Password=" + this.Password + ";Database=" + this.Database + ";Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;");
        connection.Open();
        new MySqlCommand("INSERT INTO t_item_exchange (a_index,a_enable)VALUES('" + (object) num1 + "','1" + "');", connection).ExecuteNonQuery();
        connection.Close();
      }
    }

    private void button3_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Are u sure u want to delete this record?", "Delete Record Confirmation", MessageBoxButtons.YesNo) != DialogResult.Yes || this.listBox1.SelectedIndex == -1)
        return;
      string[] strArray = this.listBox1.SelectedItem.ToString().Split('-');
      if (this.checkBox1.Checked)
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_item_exchange WHERE a_index = '" + this.textBox1.Text + "'");
      int id = int.Parse(strArray[0]);
      int index = LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList.FindIndex((Predicate<t_EXChange>) (p => p.IndexID.Equals(id)));
      if (index != -1)
      {
        LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList.RemoveAt(index);
        this.listBox1.Items.RemoveAt(this.listBox1.SelectedIndex);
      }
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

    private void PbSelectID1_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox6.Text = Convert.ToString(itemPicker.ItemIndex);
    }

    private void pictureBox2_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.tb_source_itemIndex0.Text = Convert.ToString(itemPicker.ItemIndex);
    }

    private void pictureBox4_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.tb_source_itemIndex1.Text = Convert.ToString(itemPicker.ItemIndex);
    }

    private void pictureBox6_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.tb_source_itemIndex2.Text = Convert.ToString(itemPicker.ItemIndex);
    }

    private void pictureBox8_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.tb_source_itemIndex3.Text = Convert.ToString(itemPicker.ItemIndex);
    }

    private void pictureBox10_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.tb_source_itemIndex4.Text = Convert.ToString(itemPicker.ItemIndex);
    }

    private void button2_Click(object sender, EventArgs e)
    {
      if (this.listBox1.SelectedIndex == -1)
        return;
      int ID = int.Parse(this.listBox1.SelectedItem.ToString().Split('-')[0]);
      int index1 = LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList.FindIndex((Predicate<t_EXChange>) (p => p.IndexID.Equals(ID)));
      if (this.checkBox1.Checked)
        this.Update_To_DB_SELECT();
      if (index1 != -1)
      {
        LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index1].IndexID = Convert.ToInt32(this.textBox1.Text);
        LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index1].Enable = Convert.ToInt32(this.textBox2.Text);
        LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index1].NpcIndex = Convert.ToInt32(this.textBox3.Text);
        LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index1].ResultItemIdx = Convert.ToInt32(this.textBox6.Text);
        LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index1].ResultItemCount = Convert.ToInt32(this.textBox9.Text);
        LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index1].SourceItemIndex0 = Convert.ToInt32(this.tb_source_itemIndex0.Text);
        LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index1].SourceItemIndex1 = Convert.ToInt32(this.tb_source_itemIndex1.Text);
        LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index1].SourceItemIndex2 = Convert.ToInt32(this.tb_source_itemIndex2.Text);
        LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index1].SourceItemIndex3 = Convert.ToInt32(this.tb_source_itemIndex3.Text);
        LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index1].SourceItemIndex4 = Convert.ToInt32(this.tb_source_itemIndex4.Text);
        LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index1].SourceItemCount0 = Convert.ToInt32(this.tb_count_itemIndex0.Text);
        LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index1].SourceItemCount1 = Convert.ToInt32(this.tb_count_itemIndex1.Text);
        LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index1].SourceItemCount2 = Convert.ToInt32(this.tb_count_itemIndex2.Text);
        LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index1].SourceItemCount3 = Convert.ToInt32(this.tb_count_itemIndex3.Text);
        LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index1].SourceItemCount4 = Convert.ToInt32(this.tb_count_itemIndex4.Text);
      }
      this.listBox1.Items.Clear();
      int num = LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList.Count<t_EXChange>();
      for (int index2 = 0; index2 < num; ++index2)
      {
        int indexId = LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index2].IndexID;
        int npcIndex = LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index2].NpcIndex;
        this.listBox1.Items.Add((object) (indexId.ToString() + " - " + npcIndex.ToString()));
      }
    }

    private void Update_To_DB_SELECT()
    {
      MySqlConnection connection = new MySqlConnection("datasource=" + this.Host + ";Port=3306;User ID="  + this.User + ";Password=" + this.Password + ";Database=" + this.Database + ";Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;");
      connection.Open();
      new MySqlCommand("UPDATE t_item_exchange SET a_index = '" + this.textBox1.Text + "',a_enable = '" + this.textBox2.Text + "',a_npc_index = '" + this.textBox3.Text + "',a_result_itemIndex = '" + this.textBox6.Text + "',a_result_itemCount = '" + this.textBox9.Text + "',source_itemIndex0 = '" + this.tb_source_itemIndex0.Text + "',source_itemIndex1 = '" + this.tb_source_itemIndex1.Text + "',source_itemIndex2 = '" + this.tb_source_itemIndex2.Text + "',source_itemIndex3 = '" + this.tb_source_itemIndex3.Text + "',source_itemIndex4 = '" + this.tb_source_itemIndex4.Text + "',source_itemCount0 = '" + this.tb_count_itemIndex0.Text + "',source_itemCount1 = '" + this.tb_count_itemIndex1.Text + "',source_itemCount2 = '" + this.tb_count_itemIndex2.Text + "',source_itemCount3 = '" + this.tb_count_itemIndex3.Text + "',source_itemCount4 = '" + this.tb_count_itemIndex4.Text + "' WHERE a_index = '" + this.textBox1.Text + "';", connection).ExecuteNonQuery();
      connection.Close();
    }

    private void saveToLodToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (this.listBox1.Items.Count == 0)
        return;
      SaveFileDialog saveFileDialog = new SaveFileDialog();
      saveFileDialog.Filter = "item_exchange*.lod|item_exchange*.lod|data|*.data|All|*.*";
      saveFileDialog.Title = "Save item_exchange*.lod";
      saveFileDialog.InitialDirectory = this._ClientPath;
      int num1 = (int) saveFileDialog.ShowDialog();
      if (saveFileDialog.FileName != "")
      {
        try
        {
          BinaryWriter binaryWriter = new BinaryWriter((Stream) new FileStream(saveFileDialog.FileName, FileMode.Create));
          binaryWriter.Write(LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList.Count);
          binaryWriter.Write(LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList.Count - 1].IndexID);
          for (int index = 0; index <= LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList.Count<t_EXChange>() - 1; ++index)
          {
            binaryWriter.Write(LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index].IndexID);
            binaryWriter.Write(LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index].NpcIndex);
            binaryWriter.Write(LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index].ResultItemIdx);
            binaryWriter.Write(LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index].ResultItemCount);
            binaryWriter.Write(LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index].SourceItemIndex0);
            binaryWriter.Write(LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index].SourceItemCount0);
            binaryWriter.Write(LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index].SourceItemIndex1);
            binaryWriter.Write(LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index].SourceItemCount1);
            binaryWriter.Write(LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index].SourceItemIndex2);
            binaryWriter.Write(LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index].SourceItemCount2);
            binaryWriter.Write(LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index].SourceItemIndex3);
            binaryWriter.Write(LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index].SourceItemCount3);
            binaryWriter.Write(LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index].SourceItemIndex3);
            binaryWriter.Write(LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange.ExChange.ExChangeList[index].SourceItemCount3);
          }
          binaryWriter.Close();
          int num2 = (int) MessageBox.Show("Sucess!");
        }
        catch (Exception ex)
        {
          int num3 = (int) MessageBox.Show(ex.Message, "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Hand);
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
      this.groupBox3 = new GroupBox();
      this.button3 = new Button();
      this.button1 = new Button();
      this.listBox1 = new ListBox();
      this.menuStrip1 = new MenuStrip();
      this.fileToolStripMenuItem = new ToolStripMenuItem();
      this.saveToLodToolStripMenuItem = new ToolStripMenuItem();
      this.statusStrip1 = new StatusStrip();
      this.toolStripStatusLabel1 = new ToolStripStatusLabel();
      this.groupBox4 = new GroupBox();
      this.tbFileCol4 = new TextBox();
      this.tbFileRow4 = new TextBox();
      this.tbFileID4 = new TextBox();
      this.tbFileCol3 = new TextBox();
      this.tbFileRow3 = new TextBox();
      this.tbFileID3 = new TextBox();
      this.tbFileCol2 = new TextBox();
      this.tbFileRow2 = new TextBox();
      this.tbFileID2 = new TextBox();
      this.tbFileCol1 = new TextBox();
      this.tbFileRow1 = new TextBox();
      this.tbFileID1 = new TextBox();
      this.tbFileCol0 = new TextBox();
      this.tbFileRow0 = new TextBox();
      this.tbFileID0 = new TextBox();
      this.pictureBox10 = new PictureBox();
      this.pictureBox11 = new PictureBox();
      this.label11 = new Label();
      this.tb_source_itemIndex4 = new TextBox();
      this.pictureBox8 = new PictureBox();
      this.pictureBox9 = new PictureBox();
      this.label9 = new Label();
      this.tb_source_itemIndex3 = new TextBox();
      this.pictureBox6 = new PictureBox();
      this.pictureBox7 = new PictureBox();
      this.label7 = new Label();
      this.tb_source_itemIndex2 = new TextBox();
      this.pictureBox4 = new PictureBox();
      this.pictureBox5 = new PictureBox();
      this.label6 = new Label();
      this.tb_source_itemIndex1 = new TextBox();
      this.pictureBox2 = new PictureBox();
      this.pictureBox3 = new PictureBox();
      this.label5 = new Label();
      this.tb_source_itemIndex0 = new TextBox();
      this.groupBox2 = new GroupBox();
      this.PbSelectID1 = new PictureBox();
      this.pictureBox1 = new PictureBox();
      this.label10 = new Label();
      this.label8 = new Label();
      this.textBox6 = new TextBox();
      this.textBox9 = new TextBox();
      this.groupBox1 = new GroupBox();
      this.textBox11 = new TextBox();
      this.label4 = new Label();
      this.label3 = new Label();
      this.label2 = new Label();
      this.textBox2 = new TextBox();
      this.label1 = new Label();
      this.textBox1 = new TextBox();
      this.textBox3 = new TextBox();
      this.textBox4 = new TextBox();
      this.button2 = new Button();
      this.tbFileID = new TextBox();
      this.tbFileRow = new TextBox();
      this.tbFileCol = new TextBox();
      this.groupBox5 = new GroupBox();
      this.label12 = new Label();
      this.tb_count_itemIndex4 = new TextBox();
      this.label13 = new Label();
      this.tb_count_itemIndex3 = new TextBox();
      this.label14 = new Label();
      this.tb_count_itemIndex2 = new TextBox();
      this.label15 = new Label();
      this.tb_count_itemIndex1 = new TextBox();
      this.label16 = new Label();
      this.tb_count_itemIndex0 = new TextBox();
      this.checkBox1 = new CheckBox();
      this.label17 = new Label();
      this.groupBox3.SuspendLayout();
      this.menuStrip1.SuspendLayout();
      this.statusStrip1.SuspendLayout();
      this.groupBox4.SuspendLayout();
      ((ISupportInitialize) this.pictureBox10).BeginInit();
      ((ISupportInitialize) this.pictureBox11).BeginInit();
      ((ISupportInitialize) this.pictureBox8).BeginInit();
      ((ISupportInitialize) this.pictureBox9).BeginInit();
      ((ISupportInitialize) this.pictureBox6).BeginInit();
      ((ISupportInitialize) this.pictureBox7).BeginInit();
      ((ISupportInitialize) this.pictureBox4).BeginInit();
      ((ISupportInitialize) this.pictureBox5).BeginInit();
      ((ISupportInitialize) this.pictureBox2).BeginInit();
      ((ISupportInitialize) this.pictureBox3).BeginInit();
      this.groupBox2.SuspendLayout();
      ((ISupportInitialize) this.PbSelectID1).BeginInit();
      ((ISupportInitialize) this.pictureBox1).BeginInit();
      this.groupBox1.SuspendLayout();
      this.groupBox5.SuspendLayout();
      this.SuspendLayout();
      this.groupBox3.Controls.Add((Control) this.button3);
      this.groupBox3.Controls.Add((Control) this.button1);
      this.groupBox3.Controls.Add((Control) this.listBox1);
      this.groupBox3.Location = new Point(12, 27);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Size = new Size(237, 475);
      this.groupBox3.TabIndex = 31;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "ExChange NPC";
      this.button3.FlatStyle = FlatStyle.Flat;
      this.button3.Location = new Point(131, 446);
      this.button3.Name = "button3";
      this.button3.Size = new Size(100, 23);
      this.button3.TabIndex = 4;
      this.button3.Text = "Delete";
      this.button3.UseVisualStyleBackColor = true;
      this.button3.Click += new EventHandler(this.button3_Click);
      this.button1.FlatStyle = FlatStyle.Flat;
      this.button1.Location = new Point(6, 446);
      this.button1.Name = "button1";
      this.button1.Size = new Size(100, 23);
      this.button1.TabIndex = 2;
      this.button1.Text = "Add";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.listBox1.FormattingEnabled = true;
      this.listBox1.Location = new Point(6, 14);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new Size(225, 420);
      this.listBox1.TabIndex = 1;
      this.listBox1.SelectedIndexChanged += new EventHandler(this.listBox1_SelectedIndexChanged);
      this.menuStrip1.AllowMerge = false;
      this.menuStrip1.BackColor = SystemColors.ButtonHighlight;
      this.menuStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.fileToolStripMenuItem
      });
      this.menuStrip1.Location = new Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new Size(811, 24);
      this.menuStrip1.TabIndex = 32;
      this.menuStrip1.Text = "menuStrip1";
      this.fileToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.saveToLodToolStripMenuItem
      });
      this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
      this.fileToolStripMenuItem.Size = new Size(37, 20);
      this.fileToolStripMenuItem.Text = "File";
      this.saveToLodToolStripMenuItem.Name = "saveToLodToolStripMenuItem";
      this.saveToLodToolStripMenuItem.Size = new Size(152, 22);
      this.saveToLodToolStripMenuItem.Text = "Save to lod";
      this.saveToLodToolStripMenuItem.Click += new EventHandler(this.saveToLodToolStripMenuItem_Click);
      this.statusStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.toolStripStatusLabel1
      });
      this.statusStrip1.Location = new Point(0, 503);
      this.statusStrip1.Name = "statusStrip1";
      this.statusStrip1.Size = new Size(811, 22);
      this.statusStrip1.TabIndex = 50;
      this.statusStrip1.Text = "statusStrip1";
      this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
      this.toolStripStatusLabel1.Size = new Size(39, 17);
      this.toolStripStatusLabel1.Text = "Ready";
      this.groupBox4.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left;
      this.groupBox4.Controls.Add((Control) this.tbFileCol4);
      this.groupBox4.Controls.Add((Control) this.tbFileRow4);
      this.groupBox4.Controls.Add((Control) this.tbFileID4);
      this.groupBox4.Controls.Add((Control) this.tbFileCol3);
      this.groupBox4.Controls.Add((Control) this.tbFileRow3);
      this.groupBox4.Controls.Add((Control) this.tbFileID3);
      this.groupBox4.Controls.Add((Control) this.tbFileCol2);
      this.groupBox4.Controls.Add((Control) this.tbFileRow2);
      this.groupBox4.Controls.Add((Control) this.tbFileID2);
      this.groupBox4.Controls.Add((Control) this.tbFileCol1);
      this.groupBox4.Controls.Add((Control) this.tbFileRow1);
      this.groupBox4.Controls.Add((Control) this.tbFileID1);
      this.groupBox4.Controls.Add((Control) this.tbFileCol0);
      this.groupBox4.Controls.Add((Control) this.tbFileRow0);
      this.groupBox4.Controls.Add((Control) this.tbFileID0);
      this.groupBox4.Controls.Add((Control) this.pictureBox10);
      this.groupBox4.Controls.Add((Control) this.pictureBox11);
      this.groupBox4.Controls.Add((Control) this.label11);
      this.groupBox4.Controls.Add((Control) this.tb_source_itemIndex4);
      this.groupBox4.Controls.Add((Control) this.pictureBox8);
      this.groupBox4.Controls.Add((Control) this.pictureBox9);
      this.groupBox4.Controls.Add((Control) this.label9);
      this.groupBox4.Controls.Add((Control) this.tb_source_itemIndex3);
      this.groupBox4.Controls.Add((Control) this.pictureBox6);
      this.groupBox4.Controls.Add((Control) this.pictureBox7);
      this.groupBox4.Controls.Add((Control) this.label7);
      this.groupBox4.Controls.Add((Control) this.tb_source_itemIndex2);
      this.groupBox4.Controls.Add((Control) this.pictureBox4);
      this.groupBox4.Controls.Add((Control) this.pictureBox5);
      this.groupBox4.Controls.Add((Control) this.label6);
      this.groupBox4.Controls.Add((Control) this.tb_source_itemIndex1);
      this.groupBox4.Controls.Add((Control) this.pictureBox2);
      this.groupBox4.Controls.Add((Control) this.pictureBox3);
      this.groupBox4.Controls.Add((Control) this.label5);
      this.groupBox4.Controls.Add((Control) this.tb_source_itemIndex0);
      this.groupBox4.Location = new Point(258, 184);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Size = new Size(187, 220);
      this.groupBox4.TabIndex = 51;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "Items Need";
      this.tbFileCol4.BorderStyle = BorderStyle.FixedSingle;
      this.tbFileCol4.Location = new Point(241, 182);
      this.tbFileCol4.Name = "tbFileCol4";
      this.tbFileCol4.Size = new Size(13, 20);
      this.tbFileCol4.TabIndex = 148;
      this.tbFileCol4.Visible = false;
      this.tbFileRow4.BorderStyle = BorderStyle.FixedSingle;
      this.tbFileRow4.Location = new Point(216, 182);
      this.tbFileRow4.Name = "tbFileRow4";
      this.tbFileRow4.Size = new Size(19, 20);
      this.tbFileRow4.TabIndex = 147;
      this.tbFileRow4.Visible = false;
      this.tbFileID4.BorderStyle = BorderStyle.FixedSingle;
      this.tbFileID4.Location = new Point(189, 182);
      this.tbFileID4.Name = "tbFileID4";
      this.tbFileID4.Size = new Size(21, 20);
      this.tbFileID4.TabIndex = 146;
      this.tbFileID4.Visible = false;
      this.tbFileCol3.BorderStyle = BorderStyle.FixedSingle;
      this.tbFileCol3.Location = new Point(241, 144);
      this.tbFileCol3.Name = "tbFileCol3";
      this.tbFileCol3.Size = new Size(13, 20);
      this.tbFileCol3.TabIndex = 145;
      this.tbFileCol3.Visible = false;
      this.tbFileRow3.BorderStyle = BorderStyle.FixedSingle;
      this.tbFileRow3.Location = new Point(216, 144);
      this.tbFileRow3.Name = "tbFileRow3";
      this.tbFileRow3.Size = new Size(19, 20);
      this.tbFileRow3.TabIndex = 144;
      this.tbFileRow3.Visible = false;
      this.tbFileID3.BorderStyle = BorderStyle.FixedSingle;
      this.tbFileID3.Location = new Point(189, 144);
      this.tbFileID3.Name = "tbFileID3";
      this.tbFileID3.Size = new Size(21, 20);
      this.tbFileID3.TabIndex = 143;
      this.tbFileID3.Visible = false;
      this.tbFileCol2.BorderStyle = BorderStyle.FixedSingle;
      this.tbFileCol2.Location = new Point(241, 106);
      this.tbFileCol2.Name = "tbFileCol2";
      this.tbFileCol2.Size = new Size(13, 20);
      this.tbFileCol2.TabIndex = 142;
      this.tbFileCol2.Visible = false;
      this.tbFileRow2.BorderStyle = BorderStyle.FixedSingle;
      this.tbFileRow2.Location = new Point(216, 106);
      this.tbFileRow2.Name = "tbFileRow2";
      this.tbFileRow2.Size = new Size(19, 20);
      this.tbFileRow2.TabIndex = 141;
      this.tbFileRow2.Visible = false;
      this.tbFileID2.BorderStyle = BorderStyle.FixedSingle;
      this.tbFileID2.Location = new Point(189, 106);
      this.tbFileID2.Name = "tbFileID2";
      this.tbFileID2.Size = new Size(21, 20);
      this.tbFileID2.TabIndex = 140;
      this.tbFileID2.Visible = false;
      this.tbFileCol1.BorderStyle = BorderStyle.FixedSingle;
      this.tbFileCol1.Location = new Point(241, 68);
      this.tbFileCol1.Name = "tbFileCol1";
      this.tbFileCol1.Size = new Size(13, 20);
      this.tbFileCol1.TabIndex = 139;
      this.tbFileCol1.Visible = false;
      this.tbFileRow1.BorderStyle = BorderStyle.FixedSingle;
      this.tbFileRow1.Location = new Point(216, 68);
      this.tbFileRow1.Name = "tbFileRow1";
      this.tbFileRow1.Size = new Size(19, 20);
      this.tbFileRow1.TabIndex = 138;
      this.tbFileRow1.Visible = false;
      this.tbFileID1.BorderStyle = BorderStyle.FixedSingle;
      this.tbFileID1.Location = new Point(189, 68);
      this.tbFileID1.Name = "tbFileID1";
      this.tbFileID1.Size = new Size(21, 20);
      this.tbFileID1.TabIndex = 137;
      this.tbFileID1.Visible = false;
      this.tbFileCol0.BorderStyle = BorderStyle.FixedSingle;
      this.tbFileCol0.Location = new Point(241, 30);
      this.tbFileCol0.Name = "tbFileCol0";
      this.tbFileCol0.Size = new Size(13, 20);
      this.tbFileCol0.TabIndex = 136;
      this.tbFileCol0.Visible = false;
      this.tbFileRow0.BorderStyle = BorderStyle.FixedSingle;
      this.tbFileRow0.Location = new Point(216, 30);
      this.tbFileRow0.Name = "tbFileRow0";
      this.tbFileRow0.Size = new Size(19, 20);
      this.tbFileRow0.TabIndex = 135;
      this.tbFileRow0.Visible = false;
      this.tbFileID0.BorderStyle = BorderStyle.FixedSingle;
      this.tbFileID0.Location = new Point(189, 30);
      this.tbFileID0.Name = "tbFileID0";
      this.tbFileID0.Size = new Size(21, 20);
      this.tbFileID0.TabIndex = 134;
      this.tbFileID0.Visible = false;
      this.pictureBox10.BackgroundImage = (Image) Resources.oie_transparent;
      this.pictureBox10.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox10.Location = new Point(123, 180);
      this.pictureBox10.Name = "pictureBox10";
      this.pictureBox10.Size = new Size(22, 22);
      this.pictureBox10.TabIndex = 133;
      this.pictureBox10.TabStop = false;
      this.pictureBox10.Click += new EventHandler(this.pictureBox10_Click);
      this.pictureBox11.BackColor = Color.White;
      this.pictureBox11.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox11.Location = new Point(151, 176);
      this.pictureBox11.Name = "pictureBox11";
      this.pictureBox11.Size = new Size(32, 32);
      this.pictureBox11.TabIndex = 132;
      this.pictureBox11.TabStop = false;
      this.label11.AutoSize = true;
      this.label11.Location = new Point(15, 182);
      this.label11.Name = "label11";
      this.label11.Size = new Size(27, 13);
      this.label11.TabIndex = 131;
      this.label11.Text = "Item";
      this.tb_source_itemIndex4.BorderStyle = BorderStyle.FixedSingle;
      this.tb_source_itemIndex4.Location = new Point(67, 180);
      this.tb_source_itemIndex4.Name = "tb_source_itemIndex4";
      this.tb_source_itemIndex4.Size = new Size(50, 20);
      this.tb_source_itemIndex4.TabIndex = 130;
      this.tb_source_itemIndex4.TextChanged += new EventHandler(this.tb_source_itemIndex4_TextChanged);
      this.pictureBox8.BackgroundImage = (Image) Resources.oie_transparent;
      this.pictureBox8.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox8.Location = new Point(123, 142);
      this.pictureBox8.Name = "pictureBox8";
      this.pictureBox8.Size = new Size(22, 22);
      this.pictureBox8.TabIndex = 129;
      this.pictureBox8.TabStop = false;
      this.pictureBox8.Click += new EventHandler(this.pictureBox8_Click);
      this.pictureBox9.BackColor = Color.White;
      this.pictureBox9.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox9.Location = new Point(151, 138);
      this.pictureBox9.Name = "pictureBox9";
      this.pictureBox9.Size = new Size(32, 32);
      this.pictureBox9.TabIndex = 128;
      this.pictureBox9.TabStop = false;
      this.label9.AutoSize = true;
      this.label9.Location = new Point(15, 144);
      this.label9.Name = "label9";
      this.label9.Size = new Size(27, 13);
      this.label9.TabIndex = (int) sbyte.MaxValue;
      this.label9.Text = "Item";
      this.tb_source_itemIndex3.BorderStyle = BorderStyle.FixedSingle;
      this.tb_source_itemIndex3.Location = new Point(67, 142);
      this.tb_source_itemIndex3.Name = "tb_source_itemIndex3";
      this.tb_source_itemIndex3.Size = new Size(50, 20);
      this.tb_source_itemIndex3.TabIndex = 126;
      this.tb_source_itemIndex3.TextChanged += new EventHandler(this.tb_source_itemIndex3_TextChanged);
      this.pictureBox6.BackgroundImage = (Image) Resources.oie_transparent;
      this.pictureBox6.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox6.Location = new Point(123, 104);
      this.pictureBox6.Name = "pictureBox6";
      this.pictureBox6.Size = new Size(22, 22);
      this.pictureBox6.TabIndex = 125;
      this.pictureBox6.TabStop = false;
      this.pictureBox6.Click += new EventHandler(this.pictureBox6_Click);
      this.pictureBox7.BackColor = Color.White;
      this.pictureBox7.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox7.Location = new Point(151, 100);
      this.pictureBox7.Name = "pictureBox7";
      this.pictureBox7.Size = new Size(32, 32);
      this.pictureBox7.TabIndex = 124;
      this.pictureBox7.TabStop = false;
      this.label7.AutoSize = true;
      this.label7.Location = new Point(15, 106);
      this.label7.Name = "label7";
      this.label7.Size = new Size(27, 13);
      this.label7.TabIndex = 123;
      this.label7.Text = "Item";
      this.tb_source_itemIndex2.BorderStyle = BorderStyle.FixedSingle;
      this.tb_source_itemIndex2.Location = new Point(67, 104);
      this.tb_source_itemIndex2.Name = "tb_source_itemIndex2";
      this.tb_source_itemIndex2.Size = new Size(50, 20);
      this.tb_source_itemIndex2.TabIndex = 122;
      this.tb_source_itemIndex2.TextChanged += new EventHandler(this.tb_source_itemIndex2_TextChanged);
      this.pictureBox4.BackgroundImage = (Image) Resources.oie_transparent;
      this.pictureBox4.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox4.Location = new Point(123, 66);
      this.pictureBox4.Name = "pictureBox4";
      this.pictureBox4.Size = new Size(22, 22);
      this.pictureBox4.TabIndex = 121;
      this.pictureBox4.TabStop = false;
      this.pictureBox4.Click += new EventHandler(this.pictureBox4_Click);
      this.pictureBox5.BackColor = Color.White;
      this.pictureBox5.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox5.Location = new Point(151, 62);
      this.pictureBox5.Name = "pictureBox5";
      this.pictureBox5.Size = new Size(32, 32);
      this.pictureBox5.TabIndex = 120;
      this.pictureBox5.TabStop = false;
      this.label6.AutoSize = true;
      this.label6.Location = new Point(15, 68);
      this.label6.Name = "label6";
      this.label6.Size = new Size(27, 13);
      this.label6.TabIndex = 119;
      this.label6.Text = "Item";
      this.tb_source_itemIndex1.BorderStyle = BorderStyle.FixedSingle;
      this.tb_source_itemIndex1.Location = new Point(67, 66);
      this.tb_source_itemIndex1.Name = "tb_source_itemIndex1";
      this.tb_source_itemIndex1.Size = new Size(50, 20);
      this.tb_source_itemIndex1.TabIndex = 118;
      this.tb_source_itemIndex1.TextChanged += new EventHandler(this.tb_source_itemIndex1_TextChanged);
      this.pictureBox2.BackgroundImage = (Image) Resources.oie_transparent;
      this.pictureBox2.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox2.Location = new Point(123, 28);
      this.pictureBox2.Name = "pictureBox2";
      this.pictureBox2.Size = new Size(22, 22);
      this.pictureBox2.TabIndex = 117;
      this.pictureBox2.TabStop = false;
      this.pictureBox2.Click += new EventHandler(this.pictureBox2_Click);
      this.pictureBox3.BackColor = Color.White;
      this.pictureBox3.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox3.Location = new Point(151, 24);
      this.pictureBox3.Name = "pictureBox3";
      this.pictureBox3.Size = new Size(32, 32);
      this.pictureBox3.TabIndex = 116;
      this.pictureBox3.TabStop = false;
      this.label5.AutoSize = true;
      this.label5.Location = new Point(15, 30);
      this.label5.Name = "label5";
      this.label5.Size = new Size(27, 13);
      this.label5.TabIndex = 115;
      this.label5.Text = "Item";
      this.tb_source_itemIndex0.BorderStyle = BorderStyle.FixedSingle;
      this.tb_source_itemIndex0.Location = new Point(67, 28);
      this.tb_source_itemIndex0.Name = "tb_source_itemIndex0";
      this.tb_source_itemIndex0.Size = new Size(50, 20);
      this.tb_source_itemIndex0.TabIndex = 114;
      this.tb_source_itemIndex0.TextChanged += new EventHandler(this.tb_source_itemIndex0_TextChanged);
      this.groupBox2.Controls.Add((Control) this.PbSelectID1);
      this.groupBox2.Controls.Add((Control) this.pictureBox1);
      this.groupBox2.Controls.Add((Control) this.label10);
      this.groupBox2.Controls.Add((Control) this.label8);
      this.groupBox2.Controls.Add((Control) this.textBox6);
      this.groupBox2.Controls.Add((Control) this.textBox9);
      this.groupBox2.Location = new Point(530, 41);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new Size(183, 137);
      this.groupBox2.TabIndex = 53;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "Result Gift";
      this.PbSelectID1.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbSelectID1.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbSelectID1.Location = new Point(115, 23);
      this.PbSelectID1.Name = "PbSelectID1";
      this.PbSelectID1.Size = new Size(22, 22);
      this.PbSelectID1.TabIndex = 113;
      this.PbSelectID1.TabStop = false;
      this.PbSelectID1.Click += new EventHandler(this.PbSelectID1_Click);
      this.pictureBox1.BackColor = Color.White;
      this.pictureBox1.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox1.Location = new Point(143, 19);
      this.pictureBox1.Name = "pictureBox1";
      this.pictureBox1.Size = new Size(32, 32);
      this.pictureBox1.TabIndex = 112;
      this.pictureBox1.TabStop = false;
      this.label10.AutoSize = true;
      this.label10.Location = new Point(7, 25);
      this.label10.Name = "label10";
      this.label10.Size = new Size(27, 13);
      this.label10.TabIndex = 44;
      this.label10.Text = "Item";
      this.label8.AutoSize = true;
      this.label8.Location = new Point(6, 80);
      this.label8.Name = "label8";
      this.label8.Size = new Size(35, 13);
      this.label8.TabIndex = 42;
      this.label8.Text = "Count";
      this.textBox6.BorderStyle = BorderStyle.FixedSingle;
      this.textBox6.Location = new Point(59, 23);
      this.textBox6.Name = "textBox6";
      this.textBox6.Size = new Size(50, 20);
      this.textBox6.TabIndex = 40;
      this.textBox6.TextChanged += new EventHandler(this.textBox6_TextChanged);
      this.textBox9.BorderStyle = BorderStyle.FixedSingle;
      this.textBox9.Location = new Point(59, 78);
      this.textBox9.Name = "textBox9";
      this.textBox9.Size = new Size(82, 20);
      this.textBox9.TabIndex = 37;
      this.groupBox1.Controls.Add((Control) this.textBox11);
      this.groupBox1.Controls.Add((Control) this.label4);
      this.groupBox1.Controls.Add((Control) this.label3);
      this.groupBox1.Controls.Add((Control) this.label2);
      this.groupBox1.Controls.Add((Control) this.textBox2);
      this.groupBox1.Controls.Add((Control) this.label1);
      this.groupBox1.Controls.Add((Control) this.textBox1);
      this.groupBox1.Controls.Add((Control) this.textBox3);
      this.groupBox1.Controls.Add((Control) this.textBox4);
      this.groupBox1.Location = new Point(258, 41);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(266, 137);
      this.groupBox1.TabIndex = 52;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Main";
      this.textBox11.BorderStyle = BorderStyle.FixedSingle;
      this.textBox11.Location = new Point(79, 0);
      this.textBox11.Name = "textBox11";
      this.textBox11.Size = new Size(50, 20);
      this.textBox11.TabIndex = 39;
      this.textBox11.Visible = false;
      this.label4.AutoSize = true;
      this.label4.Location = new Point(6, 80);
      this.label4.Name = "label4";
      this.label4.Size = new Size(61, 13);
      this.label4.TabIndex = 37;
      this.label4.Text = "Npc Name:";
      this.label3.AutoSize = true;
      this.label3.Location = new Point(6, 54);
      this.label3.Name = "label3";
      this.label3.Size = new Size(44, 13);
      this.label3.TabIndex = 36;
      this.label3.Text = "Npc ID:";
      this.label2.AutoSize = true;
      this.label2.Location = new Point(144, 25);
      this.label2.Name = "label2";
      this.label2.Size = new Size(43, 13);
      this.label2.TabIndex = 1;
      this.label2.Text = "Enable:";
      this.textBox2.BorderStyle = BorderStyle.FixedSingle;
      this.textBox2.Location = new Point(204, 23);
      this.textBox2.Name = "textBox2";
      this.textBox2.Size = new Size(50, 20);
      this.textBox2.TabIndex = 32;
      this.label1.AutoSize = true;
      this.label1.Location = new Point(6, 25);
      this.label1.Name = "label1";
      this.label1.Size = new Size(36, 13);
      this.label1.TabIndex = 0;
      this.label1.Text = "Index:";
      this.textBox1.BorderStyle = BorderStyle.FixedSingle;
      this.textBox1.Location = new Point(79, 23);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(50, 20);
      this.textBox1.TabIndex = 31;
      this.textBox3.BorderStyle = BorderStyle.FixedSingle;
      this.textBox3.Location = new Point(79, 52);
      this.textBox3.Name = "textBox3";
      this.textBox3.Size = new Size(50, 20);
      this.textBox3.TabIndex = 33;
      this.textBox3.TextChanged += new EventHandler(this.textBox3_TextChanged);
      this.textBox4.BorderStyle = BorderStyle.FixedSingle;
      this.textBox4.Location = new Point(79, 78);
      this.textBox4.Name = "textBox4";
      this.textBox4.Size = new Size(175, 20);
      this.textBox4.TabIndex = 34;
      this.button2.FlatStyle = FlatStyle.Flat;
      this.button2.Location = new Point(705, 479);
      this.button2.Name = "button2";
      this.button2.Size = new Size(100, 23);
      this.button2.TabIndex = 54;
      this.button2.Text = "Save";
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.tbFileID.BorderStyle = BorderStyle.FixedSingle;
      this.tbFileID.Location = new Point(719, 93);
      this.tbFileID.Name = "tbFileID";
      this.tbFileID.Size = new Size(50, 20);
      this.tbFileID.TabIndex = 55;
      this.tbFileID.Visible = false;
      this.tbFileRow.BorderStyle = BorderStyle.FixedSingle;
      this.tbFileRow.Location = new Point(719, 119);
      this.tbFileRow.Name = "tbFileRow";
      this.tbFileRow.Size = new Size(50, 20);
      this.tbFileRow.TabIndex = 56;
      this.tbFileRow.Visible = false;
      this.tbFileCol.BorderStyle = BorderStyle.FixedSingle;
      this.tbFileCol.Location = new Point(719, 145);
      this.tbFileCol.Name = "tbFileCol";
      this.tbFileCol.Size = new Size(50, 20);
      this.tbFileCol.TabIndex = 57;
      this.tbFileCol.Visible = false;
      this.groupBox5.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left;
      this.groupBox5.Controls.Add((Control) this.label12);
      this.groupBox5.Controls.Add((Control) this.tb_count_itemIndex4);
      this.groupBox5.Controls.Add((Control) this.label13);
      this.groupBox5.Controls.Add((Control) this.tb_count_itemIndex3);
      this.groupBox5.Controls.Add((Control) this.label14);
      this.groupBox5.Controls.Add((Control) this.tb_count_itemIndex2);
      this.groupBox5.Controls.Add((Control) this.label15);
      this.groupBox5.Controls.Add((Control) this.tb_count_itemIndex1);
      this.groupBox5.Controls.Add((Control) this.label16);
      this.groupBox5.Controls.Add((Control) this.tb_count_itemIndex0);
      this.groupBox5.Location = new Point(451, 184);
      this.groupBox5.Name = "groupBox5";
      this.groupBox5.Size = new Size(139, 220);
      this.groupBox5.TabIndex = 58;
      this.groupBox5.TabStop = false;
      this.groupBox5.Text = "Items Count Need";
      this.label12.AutoSize = true;
      this.label12.Location = new Point(15, 182);
      this.label12.Name = "label12";
      this.label12.Size = new Size(35, 13);
      this.label12.TabIndex = 131;
      this.label12.Text = "Count";
      this.tb_count_itemIndex4.BorderStyle = BorderStyle.FixedSingle;
      this.tb_count_itemIndex4.Location = new Point(67, 180);
      this.tb_count_itemIndex4.Name = "tb_count_itemIndex4";
      this.tb_count_itemIndex4.Size = new Size(50, 20);
      this.tb_count_itemIndex4.TabIndex = 130;
      this.label13.AutoSize = true;
      this.label13.Location = new Point(15, 144);
      this.label13.Name = "label13";
      this.label13.Size = new Size(35, 13);
      this.label13.TabIndex = (int) sbyte.MaxValue;
      this.label13.Text = "Count";
      this.tb_count_itemIndex3.BorderStyle = BorderStyle.FixedSingle;
      this.tb_count_itemIndex3.Location = new Point(67, 142);
      this.tb_count_itemIndex3.Name = "tb_count_itemIndex3";
      this.tb_count_itemIndex3.Size = new Size(50, 20);
      this.tb_count_itemIndex3.TabIndex = 126;
      this.label14.AutoSize = true;
      this.label14.Location = new Point(15, 106);
      this.label14.Name = "label14";
      this.label14.Size = new Size(35, 13);
      this.label14.TabIndex = 123;
      this.label14.Text = "Count";
      this.tb_count_itemIndex2.BorderStyle = BorderStyle.FixedSingle;
      this.tb_count_itemIndex2.Location = new Point(67, 104);
      this.tb_count_itemIndex2.Name = "tb_count_itemIndex2";
      this.tb_count_itemIndex2.Size = new Size(50, 20);
      this.tb_count_itemIndex2.TabIndex = 122;
      this.label15.AutoSize = true;
      this.label15.Location = new Point(15, 68);
      this.label15.Name = "label15";
      this.label15.Size = new Size(35, 13);
      this.label15.TabIndex = 119;
      this.label15.Text = "Count";
      this.tb_count_itemIndex1.BorderStyle = BorderStyle.FixedSingle;
      this.tb_count_itemIndex1.Location = new Point(67, 66);
      this.tb_count_itemIndex1.Name = "tb_count_itemIndex1";
      this.tb_count_itemIndex1.Size = new Size(50, 20);
      this.tb_count_itemIndex1.TabIndex = 118;
      this.label16.AutoSize = true;
      this.label16.Location = new Point(15, 30);
      this.label16.Name = "label16";
      this.label16.Size = new Size(35, 13);
      this.label16.TabIndex = 115;
      this.label16.Text = "Count";
      this.tb_count_itemIndex0.BorderStyle = BorderStyle.FixedSingle;
      this.tb_count_itemIndex0.Location = new Point(67, 28);
      this.tb_count_itemIndex0.Name = "tb_count_itemIndex0";
      this.tb_count_itemIndex0.Size = new Size(50, 20);
      this.tb_count_itemIndex0.TabIndex = 114;
      this.checkBox1.AutoSize = true;
      this.checkBox1.BackColor = Color.Red;
      this.checkBox1.Location = new Point(657, 483);
      this.checkBox1.Name = "checkBox1";
      this.checkBox1.Size = new Size(42, 17);
      this.checkBox1.TabIndex = 59;
      this.checkBox1.Text = "NO";
      this.checkBox1.UseVisualStyleBackColor = false;
      this.checkBox1.CheckedChanged += new EventHandler(this.checkBox1_CheckedChanged);
      this.label17.AutoSize = true;
      this.label17.Location = new Point(549, 484);
      this.label17.Name = "label17";
      this.label17.Size = new Size(102, 13);
      this.label17.TabIndex = 60;
      this.label17.Text = "Auto In Database ->";
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(811, 525);
      this.Controls.Add((Control) this.label17);
      this.Controls.Add((Control) this.checkBox1);
      this.Controls.Add((Control) this.groupBox5);
      this.Controls.Add((Control) this.tbFileCol);
      this.Controls.Add((Control) this.tbFileRow);
      this.Controls.Add((Control) this.tbFileID);
      this.Controls.Add((Control) this.button2);
      this.Controls.Add((Control) this.groupBox2);
      this.Controls.Add((Control) this.groupBox1);
      this.Controls.Add((Control) this.groupBox4);
      this.Controls.Add((Control) this.statusStrip1);
      this.Controls.Add((Control) this.menuStrip1);
      this.Controls.Add((Control) this.groupBox3);
      this.Name = nameof (ExChange);
      this.Text = nameof (ExChange);
      this.Load += new EventHandler(this.ExChange_Load);
      this.groupBox3.ResumeLayout(false);
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.statusStrip1.ResumeLayout(false);
      this.statusStrip1.PerformLayout();
      this.groupBox4.ResumeLayout(false);
      this.groupBox4.PerformLayout();
      ((ISupportInitialize) this.pictureBox10).EndInit();
      ((ISupportInitialize) this.pictureBox11).EndInit();
      ((ISupportInitialize) this.pictureBox8).EndInit();
      ((ISupportInitialize) this.pictureBox9).EndInit();
      ((ISupportInitialize) this.pictureBox6).EndInit();
      ((ISupportInitialize) this.pictureBox7).EndInit();
      ((ISupportInitialize) this.pictureBox4).EndInit();
      ((ISupportInitialize) this.pictureBox5).EndInit();
      ((ISupportInitialize) this.pictureBox2).EndInit();
      ((ISupportInitialize) this.pictureBox3).EndInit();
      this.groupBox2.ResumeLayout(false);
      this.groupBox2.PerformLayout();
      ((ISupportInitialize) this.PbSelectID1).EndInit();
      ((ISupportInitialize) this.pictureBox1).EndInit();
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.groupBox5.ResumeLayout(false);
      this.groupBox5.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
