// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using LcDevPack_TeamDamonA.Properties;
using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag
{
  public class ZoneFlag : Form
  {
    public static Connection connection = new Connection();
    private string Host = LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag.connection.Settings.SqlHost;
    private string User = LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag.connection.Settings.SqlUser;
    private string Password = LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag.connection.Settings.SqlPassword;
    private string Database = LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag.connection.Settings.SqlDatabase;
    private string language = LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag.connection.Settings.Language;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    private ExportLodHandle exportLodHandle = new ExportLodHandle();
    public static List<FileMenager> ItemList = new List<FileMenager>();
    private Encoding encoding = Encoding.GetEncoding("ISO-8859-1");
    public int lastidSkill;
    private IContainer components;
    private MenuStrip menuStrip1;
    private ToolStripMenuItem fileToolStripMenuItem;
    private ToolStripMenuItem openToolStripMenuItem;
    private ToolStripMenuItem saveToolStripMenuItem;
    private ToolStripMenuItem closeToolStripMenuItem;
    private ListBox L_Box;
    private TextBox textBox1;
    private TextBox textBox2;
    private TextBox textBox3;
    private Label label1;
    private Label label2;
    private Label label3;
    private Button button1;
    private Button button2;
    private Button button3;
    private CheckedListBox clbZone;
    private CheckedListBox clbExtra;
    private TextBox textBox4;
    private Label label5;
    private Button button18;
    private Label label6;
    private Label label7;
    private Label label8;
    private Label label9;
    private Button button15;
    private Label label10;
    private Label label11;
    private Label label4;

    public ZoneFlag()
    {
      this.InitializeComponent();
      this.clbZone.CheckOnClick = true;
      this.clbExtra.CheckOnClick = true;
    }

    private void openToolStripMenuItem_Click(object sender, EventArgs e)
    {
      LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag.ItemList.Clear();
      OpenFileDialog openFileDialog = new OpenFileDialog();
      openFileDialog.Title = "Edit : ZoneFlag*.lod";
      openFileDialog.InitialDirectory = "";
      openFileDialog.Filter = "ZoneFlag*.lod|ZoneFlag*.lod|data|*.data|All|*.*";
      if (openFileDialog.ShowDialog() == DialogResult.Cancel)
        return;
      this.Text = "Editor by AssasinPL & Kimpobin For LastChaos - Editor(" + openFileDialog.SafeFileName + ")";
      using (BinaryReader binaryReader = new BinaryReader((Stream) File.Open(openFileDialog.FileName, FileMode.Open)))
      {
        binaryReader.ReadInt32();
        while (binaryReader.BaseStream.Position < binaryReader.BaseStream.Length)
          LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag.ItemList.Add(new FileMenager()
          {
            NpcId = binaryReader.ReadInt32(),
            Flag = binaryReader.ReadInt64(),
            ExtraFlag = binaryReader.ReadInt64()
          });
        binaryReader.Close();
        this.L_Box.Items.Clear();
        int num = LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag.ItemList.Count<FileMenager>();
        for (int index = 0; index < num; ++index)
          this.L_Box.Items.Add((object) LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag.ItemList[index].NpcId);
      }
    }

    private void L_Box_SelectedIndexChanged(object sender, EventArgs e)
    {
      for (int index = 0; index < this.clbZone.Items.Count; ++index)
        this.clbZone.SetItemChecked(index, false);
      for (int index = 0; index < this.clbExtra.Items.Count; ++index)
        this.clbExtra.SetItemChecked(index, false);
      if (this.L_Box.SelectedIndex == -1)
        return;
      int Item = Convert.ToInt32(this.L_Box.SelectedItem.ToString().Split('-')[0]);
      int index1 = LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag.ItemList.FindIndex((Predicate<FileMenager>) (p => p.NpcId.Equals(Item)));
      this.textBox1.Text = Convert.ToString(Item);
      this.textBox2.Text = Convert.ToString(LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag.ItemList[index1].Flag);
      this.textBox3.Text = Convert.ToString(LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag.ItemList[index1].ExtraFlag);
      this.label11.Text = string.Format("{0}", (object) Convert.ToString(Item));
      this.label4.Text = this.databaseHandle.MobNameFast(Convert.ToInt32(this.textBox1.Text));
      this.label4.Visible = true;
      this.label11.Visible = true;
      for (int index2 = 0; index2 < this.clbZone.Items.Count; ++index2)
      {
        if ((LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag.ItemList[index1].Flag & 1L << index2) != 0L)
        {
          for (int index3 = 0; index3 < this.clbExtra.Items.Count; ++index3)
          {
            if ((LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag.ItemList[index1].ExtraFlag & 1L << index3) != 0L)
            {
              this.textBox4.Text = index3.ToString();
              this.clbZone.SetItemChecked(index2, true);
              this.clbExtra.SetItemChecked(index3, true);
            }
          }
        }
      }
    }

    private void button1_Click(object sender, EventArgs e)
    {
      if (this.L_Box.Items.Count == 0)
        return;
      int num1 = LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag.ItemList[LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag.ItemList.Count - 1].NpcId + 1;
      LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag.ItemList.Add(new FileMenager()
      {
        NpcId = num1,
        Flag = Convert.ToInt64("1"),
        ExtraFlag = Convert.ToInt64("1")
      });
      this.L_Box.Items.Clear();
      int num2 = LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag.ItemList.Count<FileMenager>();
      for (int index = 0; index < num2; ++index)
        this.L_Box.Items.Add((object) LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag.ItemList[index].NpcId);
      this.L_Box.SelectedIndex = this.L_Box.Items.Count - 1;
    }

    private void button2_Click(object sender, EventArgs e)
    {
      if (this.L_Box.SelectedIndex == -1)
        return;
      int selectedIndex = this.L_Box.SelectedIndex;
      int Item = Convert.ToInt32(this.L_Box.SelectedItem.ToString().Split('-')[0]);
      int index1 = LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag.ItemList.FindIndex((Predicate<FileMenager>) (p => p.NpcId.Equals(Item)));
      LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag.ItemList[index1].NpcId = Convert.ToInt32(this.textBox1.Text);
      LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag.ItemList[index1].Flag = Convert.ToInt64(this.textBox2.Text);
      LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag.ItemList[index1].ExtraFlag = Convert.ToInt64(this.textBox3.Text);
      this.L_Box.Items.Clear();
      int num = LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag.ItemList.Count<FileMenager>();
      for (int index2 = 0; index2 < num; ++index2)
        this.L_Box.Items.Add((object) LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag.ItemList[index2].NpcId);
      this.L_Box.SelectedIndex = selectedIndex;
    }

    private void button3_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want to Delete NPC " + this.textBox1.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes || this.L_Box.SelectedIndex == -1)
        return;
      int selectedIndex = this.L_Box.SelectedIndex;
      this.L_Box.Items.Remove((object) selectedIndex);
      int Item = Convert.ToInt32(this.L_Box.SelectedItem.ToString().Split('-')[0]);
      int index1 = LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag.ItemList.FindIndex((Predicate<FileMenager>) (p => p.NpcId.Equals(Item)));
      LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag.ItemList.RemoveAt(index1);
      this.L_Box.Items.Clear();
      int num = LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag.ItemList.Count<FileMenager>();
      for (int index2 = 0; index2 < num; ++index2)
        this.L_Box.Items.Add((object) LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag.ItemList[index2].NpcId);
      this.L_Box.SelectedIndex = selectedIndex - 1;
    }

    private void saveToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (this.L_Box.Items.Count == 0)
        return;
      SaveFileDialog saveFileDialog = new SaveFileDialog();
      saveFileDialog.Filter = "ZoneFlag.lod|ZoneFlag*.lod|data|*.data|All|*.*";
      saveFileDialog.Title = "Save ZoneFlag.lod";
      int num1 = (int) saveFileDialog.ShowDialog();
      if (!(saveFileDialog.FileName != ""))
        return;
      try
      {
        BinaryWriter binaryWriter = new BinaryWriter((Stream) new FileStream(saveFileDialog.FileName, FileMode.Create));
        binaryWriter.Write(LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag.ItemList[LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag.ItemList.Count - 1].NpcId);
        for (int index = 0; index <= LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag.ItemList.Count<FileMenager>() - 1; ++index)
        {
          binaryWriter.Write(LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag.ItemList[index].NpcId);
          binaryWriter.Write(Convert.ToInt64(LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag.ItemList[index].Flag));
          binaryWriter.Write(Convert.ToInt64(LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag.ItemList[index].ExtraFlag));
        }
        binaryWriter.Close();
        int num2 = (int) MessageBox.Show("Sucess!");
      }
      catch (Exception ex)
      {
        int num3 = (int) MessageBox.Show(ex.Message, "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
    }

    private void closeToolStripMenuItem_Click(object sender, EventArgs e) => this.Close();

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void DoSetBits(CheckedListBox clb, ItemCheckEventArgs item, out ulong ZoneFlags)
    {
      BitArray bitArray = new BitArray(64);
      for (int index = 0; index < clb.Items.Count; ++index)
        bitArray.Set(index, clb.GetItemChecked(index));
      bitArray.Set(item.Index, item.NewValue == CheckState.Checked);
      byte[] numArray = new byte[8];
      bitArray.CopyTo((Array) numArray, 0);
      ZoneFlags = BitConverter.ToUInt64(numArray, 0);
    }

    private void ZoneFlagItemCheck(object sender, ItemCheckEventArgs e)
    {
      ulong ZoneFlags = 0;
      this.DoSetBits(this.clbZone, e, out ZoneFlags);
      this.textBox2.Text = ZoneFlags.ToString();
    }

    private void DoSetBits2(
      CheckedListBox Exclb,
      ItemCheckEventArgs item2,
      out ulong ExtraZoneFlags)
    {
      BitArray bitArray = new BitArray(64);
      for (int index = 0; index < Exclb.Items.Count; ++index)
        bitArray.Set(index, Exclb.GetItemChecked(index));
      bitArray.Set(item2.Index, item2.NewValue == CheckState.Checked);
      byte[] numArray = new byte[8];
      bitArray.CopyTo((Array) numArray, 0);
      ExtraZoneFlags = BitConverter.ToUInt64(numArray, 0);
    }

    private void ZoneFlagExtraItemCheck(object sender, ItemCheckEventArgs e)
    {
      if (e.NewValue == CheckState.Checked && this.clbExtra.CheckedItems.Count >= 1)
        e.NewValue = CheckState.Unchecked;
      ulong ZoneFlags = 0;
      this.DoSetBits(this.clbExtra, e, out ZoneFlags);
      this.textBox3.Text = ZoneFlags.ToString();
      int selectedIndex = this.clbExtra.SelectedIndex;
      if (selectedIndex == -1)
        return;
      this.textBox4.Text = selectedIndex.ToString();
    }

    private void InitializeComponent()
    {
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag));
      this.menuStrip1 = new MenuStrip();
      this.fileToolStripMenuItem = new ToolStripMenuItem();
      this.openToolStripMenuItem = new ToolStripMenuItem();
      this.saveToolStripMenuItem = new ToolStripMenuItem();
      this.closeToolStripMenuItem = new ToolStripMenuItem();
      this.L_Box = new ListBox();
      this.textBox1 = new TextBox();
      this.textBox2 = new TextBox();
      this.textBox3 = new TextBox();
      this.label1 = new Label();
      this.label2 = new Label();
      this.label3 = new Label();
      this.button1 = new Button();
      this.button2 = new Button();
      this.button3 = new Button();
      this.label4 = new Label();
      this.clbZone = new CheckedListBox();
      this.clbExtra = new CheckedListBox();
      this.textBox4 = new TextBox();
      this.label5 = new Label();
      this.button18 = new Button();
      this.label6 = new Label();
      this.label7 = new Label();
      this.label8 = new Label();
      this.label9 = new Label();
      this.button15 = new Button();
      this.label10 = new Label();
      this.label11 = new Label();
      this.menuStrip1.SuspendLayout();
      this.SuspendLayout();
      this.menuStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.fileToolStripMenuItem
      });
      this.menuStrip1.Location = new Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new Size(865, 24);
      this.menuStrip1.TabIndex = 0;
      this.menuStrip1.Text = "menuStrip1";
      this.fileToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[3]
      {
        (ToolStripItem) this.openToolStripMenuItem,
        (ToolStripItem) this.saveToolStripMenuItem,
        (ToolStripItem) this.closeToolStripMenuItem
      });
      this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
      this.fileToolStripMenuItem.Size = new Size(37, 20);
      this.fileToolStripMenuItem.Text = "File";
      this.openToolStripMenuItem.Name = "openToolStripMenuItem";
      this.openToolStripMenuItem.Size = new Size(103, 22);
      this.openToolStripMenuItem.Text = "Open";
      this.openToolStripMenuItem.Click += new EventHandler(this.openToolStripMenuItem_Click);
      this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
      this.saveToolStripMenuItem.Size = new Size(103, 22);
      this.saveToolStripMenuItem.Text = "Save";
      this.saveToolStripMenuItem.Click += new EventHandler(this.saveToolStripMenuItem_Click);
      this.closeToolStripMenuItem.Name = "closeToolStripMenuItem";
      this.closeToolStripMenuItem.Size = new Size(103, 22);
      this.closeToolStripMenuItem.Text = "Close";
      this.closeToolStripMenuItem.Click += new EventHandler(this.closeToolStripMenuItem_Click);
      this.L_Box.FormattingEnabled = true;
      this.L_Box.Location = new Point(12, 27);
      this.L_Box.Name = "L_Box";
      this.L_Box.Size = new Size(163, 342);
      this.L_Box.TabIndex = 1;
      this.L_Box.SelectedIndexChanged += new EventHandler(this.L_Box_SelectedIndexChanged);
      this.textBox1.Location = new Point(244, 43);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(100, 20);
      this.textBox1.TabIndex = 2;
      this.textBox2.Enabled = false;
      this.textBox2.Location = new Point(244, 69);
      this.textBox2.Name = "textBox2";
      this.textBox2.Size = new Size(153, 20);
      this.textBox2.TabIndex = 3;
      this.textBox3.Enabled = false;
      this.textBox3.Location = new Point(244, 95);
      this.textBox3.Name = "textBox3";
      this.textBox3.Size = new Size(153, 20);
      this.textBox3.TabIndex = 4;
      this.textBox3.TextChanged += new EventHandler(this.textBox3_TextChanged);
      this.label1.AutoSize = true;
      this.label1.Location = new Point(181, 46);
      this.label1.Name = "label1";
      this.label1.Size = new Size(24, 13);
      this.label1.TabIndex = 5;
      this.label1.Text = "ID :";
      this.label2.AutoSize = true;
      this.label2.Location = new Point(181, 72);
      this.label2.Name = "label2";
      this.label2.Size = new Size(58, 13);
      this.label2.TabIndex = 6;
      this.label2.Text = "ZoneFlag :";
      this.label3.AutoSize = true;
      this.label3.Location = new Point(181, 98);
      this.label3.Name = "label3";
      this.label3.Size = new Size(57, 13);
      this.label3.TabIndex = 7;
      this.label3.Text = "ExtraFlag :";
      this.button1.Location = new Point(12, 382);
      this.button1.Name = "button1";
      this.button1.Size = new Size(57, 23);
      this.button1.TabIndex = 8;
      this.button1.Text = "Add";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.button2.Location = new Point(75, 382);
      this.button2.Name = "button2";
      this.button2.Size = new Size(57, 23);
      this.button2.TabIndex = 9;
      this.button2.Text = "Save";
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.button3.Location = new Point(138, 382);
      this.button3.Name = "button3";
      this.button3.Size = new Size(57, 23);
      this.button3.TabIndex = 10;
      this.button3.Text = "Delete";
      this.button3.UseVisualStyleBackColor = true;
      this.button3.Click += new EventHandler(this.button3_Click);
      this.label4.AutoSize = true;
      this.label4.Font = new Font("Segoe Print", 9.75f, FontStyle.Bold, GraphicsUnit.Point, (byte) 238);
      this.label4.ForeColor = Color.DodgerBlue;
      this.label4.Location = new Point(180, 195);
      this.label4.Name = "label4";
      this.label4.Size = new Size(50, 23);
      this.label4.TabIndex = 12;
      this.label4.Text = "label4";
      this.label4.Visible = false;
      this.clbZone.BackColor = Color.White;
      this.clbZone.ColumnWidth = 64;
      this.clbZone.FormattingEnabled = true;
      this.clbZone.Items.AddRange(new object[64]
      {
        (object) "Zone 0",
        (object) "Zone 1",
        (object) "Zone 2",
        (object) "Zone 3",
        (object) "Zone 4",
        (object) "Zone 5",
        (object) "Zone 6",
        (object) "Zone 7",
        (object) "Zone 8",
        (object) "Zone 9",
        (object) "Zone 10",
        (object) "Zone 11",
        (object) "Zone 12",
        (object) "Zone 13",
        (object) "Zone 14",
        (object) "Zone 15",
        (object) "Zone 16",
        (object) "Zone 17",
        (object) "Zone 18",
        (object) "Zone 19",
        (object) "Zone 20",
        (object) "Zone 21",
        (object) "Zone 22",
        (object) "Zone 23",
        (object) "Zone 24",
        (object) "Zone 25",
        (object) "Zone 26",
        (object) "Zone 27",
        (object) "Zone 28",
        (object) "Zone 29",
        (object) "Zone 30",
        (object) "Zone 31",
        (object) "Zone 32",
        (object) "Zone 33",
        (object) "Zone 34",
        (object) "Zone 35",
        (object) "Zone 36",
        (object) "Zone 37",
        (object) "Zone 38",
        (object) "Zone 39",
        (object) "Zone 40",
        (object) "Zone 41",
        (object) "Zone 42",
        (object) "Zone 43",
        (object) "Zone 44",
        (object) "Zone 45",
        (object) "Zone 46",
        (object) "Zone 47",
        (object) "Zone 48",
        (object) "Zone 49",
        (object) "Zone 50",
        (object) "Zone 51",
        (object) "Zone 52",
        (object) "Zone 53",
        (object) "Zone 54",
        (object) "Zone 55",
        (object) "Zone 56",
        (object) "Zone 57",
        (object) "Zone 58",
        (object) "Zone 59",
        (object) "Zone 60",
        (object) "Zone 61",
        (object) "Zone 62",
        (object) "Zone 63"
      });
      this.clbZone.Location = new Point(403, 27);
      this.clbZone.MultiColumn = true;
      this.clbZone.Name = "clbZone";
      this.clbZone.RightToLeft = RightToLeft.No;
      this.clbZone.Size = new Size(220, 379);
      this.clbZone.TabIndex = 13;
      this.clbZone.ThreeDCheckBoxes = true;
      this.clbZone.ItemCheck += new ItemCheckEventHandler(this.ZoneFlagItemCheck);
      this.clbZone.SelectedIndexChanged += new EventHandler(this.clbZone_SelectedIndexChanged);
      this.clbExtra.BackColor = Color.White;
      this.clbExtra.CheckOnClick = true;
      this.clbExtra.ColumnWidth = 64;
      this.clbExtra.FormattingEnabled = true;
      this.clbExtra.Items.AddRange(new object[64]
      {
        (object) "Extra 0",
        (object) "Extra 1",
        (object) "Extra 2",
        (object) "Extra 3",
        (object) "Extra 4",
        (object) "Extra 5",
        (object) "Extra 6",
        (object) "Extra 7",
        (object) "Extra 8",
        (object) "Extra 9",
        (object) "Extra 10",
        (object) "Extra 11",
        (object) "Extra 12",
        (object) "Extra 13",
        (object) "Extra 14",
        (object) "Extra 15",
        (object) "Extra 16",
        (object) "Extra 17",
        (object) "Extra 18",
        (object) "Extra 19",
        (object) "Extra 20",
        (object) "Extra 21",
        (object) "Extra 22",
        (object) "Extra 23",
        (object) "Extra 24",
        (object) "Extra 25",
        (object) "Extra 26",
        (object) "Extra 27",
        (object) "Extra 28",
        (object) "Extra 29",
        (object) "Extra 30",
        (object) "Extra 31",
        (object) "Extra 32",
        (object) "Extra 33",
        (object) "Extra 34",
        (object) "Extra 35",
        (object) "Extra 36",
        (object) "Extra 37",
        (object) "Extra 38",
        (object) "Extra 39",
        (object) "Extra 40",
        (object) "Extra 41",
        (object) "Extra 42",
        (object) "Extra 43",
        (object) "Extra 44",
        (object) "Extra 45",
        (object) "Extra 46",
        (object) "Extra 47",
        (object) "Extra 48",
        (object) "Extra 49",
        (object) "Extra 50",
        (object) "Extra 51",
        (object) "Extra 52",
        (object) "Extra 53",
        (object) "Extra 54",
        (object) "Extra 55",
        (object) "Extra 56",
        (object) "Extra 57",
        (object) "Extra 58",
        (object) "Extra 59",
        (object) "Extra 60",
        (object) "Extra 61",
        (object) "Extra 62",
        (object) "Extra 63"
      });
      this.clbExtra.Location = new Point(638, 27);
      this.clbExtra.MultiColumn = true;
      this.clbExtra.Name = "clbExtra";
      this.clbExtra.Size = new Size(220, 379);
      this.clbExtra.TabIndex = 14;
      this.clbExtra.ThreeDCheckBoxes = true;
      this.clbExtra.ItemCheck += new ItemCheckEventHandler(this.ZoneFlagExtraItemCheck);
      this.clbExtra.SelectedIndexChanged += new EventHandler(this.clbExtra_SelectedIndexChanged);
      this.textBox4.Enabled = false;
      this.textBox4.Location = new Point(244, 121);
      this.textBox4.Name = "textBox4";
      this.textBox4.Size = new Size(153, 20);
      this.textBox4.TabIndex = 15;
      this.textBox4.TextChanged += new EventHandler(this.textBox4_TextChanged);
      this.label5.AutoSize = true;
      this.label5.Location = new Point(181, 124);
      this.label5.Name = "label5";
      this.label5.Size = new Size(62, 13);
      this.label5.TabIndex = 16;
      this.label5.Text = "ExtraZone :";
      this.button18.BackColor = Color.LightCyan;
      this.button18.FlatStyle = FlatStyle.Flat;
      this.button18.Image = (Image) Resources._08;
      this.button18.ImageAlign = ContentAlignment.MiddleLeft;
      this.button18.Location = new Point(240, 283);
      this.button18.Name = "button18";
      this.button18.Size = new Size(104, 25);
      this.button18.TabIndex = 103;
      this.button18.Text = "      Update To DB";
      this.button18.UseVisualStyleBackColor = false;
      this.button18.Click += new EventHandler(this.button18_Click);
      this.label6.AutoSize = true;
      this.label6.ForeColor = Color.OrangeRed;
      this.label6.Location = new Point(228, 334);
      this.label6.Name = "label6";
      this.label6.Size = new Size(153, 13);
      this.label6.TabIndex = 104;
      this.label6.Text = "* Need add New Teleport NPC";
      this.label7.AutoSize = true;
      this.label7.ForeColor = Color.OrangeRed;
      this.label7.Location = new Point(228, 356);
      this.label7.Name = "label7";
      this.label7.Size = new Size(119, 13);
      this.label7.TabIndex = 105;
      this.label7.Text = "* NPC Flag = 33554736";
      this.label8.AutoSize = true;
      this.label8.ForeColor = Color.OrangeRed;
      this.label8.Location = new Point(228, 382);
      this.label8.Name = "label8";
      this.label8.Size = new Size(126, 13);
      this.label8.TabIndex = 106;
      this.label8.Text = "Or NPC Flag = 33554480";
      this.label9.AutoSize = true;
      this.label9.ForeColor = Color.OrangeRed;
      this.label9.Location = new Point(228, 311);
      this.label9.Name = "label9";
      this.label9.Size = new Size((int) sbyte.MaxValue, 13);
      this.label9.TabIndex = 107;
      this.label9.Text = "* If NPC null Can't update";
      this.button15.BackgroundImage = (Image) Resources.search__5_;
      this.button15.BackgroundImageLayout = ImageLayout.None;
      this.button15.Location = new Point(354, 40);
      this.button15.Name = "button15";
      this.button15.Size = new Size(27, 25);
      this.button15.TabIndex = 108;
      this.button15.UseVisualStyleBackColor = true;
      this.button15.Click += new EventHandler(this.button15_Click);
      this.label10.AutoSize = true;
      this.label10.Location = new Point(181, 173);
      this.label10.Name = "label10";
      this.label10.Size = new Size(66, 13);
      this.label10.TabIndex = 109;
      this.label10.Text = "NPC Name :";
      this.label11.AutoSize = true;
      this.label11.Font = new Font("Segoe Print", 9.75f, FontStyle.Bold, GraphicsUnit.Point, (byte) 238);
      this.label11.Location = new Point(253, 167);
      this.label11.Name = "label11";
      this.label11.Size = new Size(59, 23);
      this.label11.TabIndex = 110;
      this.label11.Text = "label11";
      this.label11.Visible = false;
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.BackColor = SystemColors.Control;
      this.ClientSize = new Size(865, 417);
      this.Controls.Add((Control) this.label11);
      this.Controls.Add((Control) this.label10);
      this.Controls.Add((Control) this.button15);
      this.Controls.Add((Control) this.label9);
      this.Controls.Add((Control) this.label8);
      this.Controls.Add((Control) this.label7);
      this.Controls.Add((Control) this.label6);
      this.Controls.Add((Control) this.button18);
      this.Controls.Add((Control) this.label5);
      this.Controls.Add((Control) this.textBox4);
      this.Controls.Add((Control) this.clbExtra);
      this.Controls.Add((Control) this.clbZone);
      this.Controls.Add((Control) this.label4);
      this.Controls.Add((Control) this.button3);
      this.Controls.Add((Control) this.button2);
      this.Controls.Add((Control) this.button1);
      this.Controls.Add((Control) this.label3);
      this.Controls.Add((Control) this.label2);
      this.Controls.Add((Control) this.label1);
      this.Controls.Add((Control) this.textBox3);
      this.Controls.Add((Control) this.textBox2);
      this.Controls.Add((Control) this.textBox1);
      this.Controls.Add((Control) this.L_Box);
      this.Controls.Add((Control) this.menuStrip1);
      this.Icon = (Icon) componentResourceManager.GetObject("$this.Icon");
      this.MainMenuStrip = this.menuStrip1;
      this.Name = nameof (ZoneFlag);
      this.StartPosition = FormStartPosition.CenterScreen;
      this.Text = "ZoneFlag Editor";
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();
    }

    private void textBox3_TextChanged(object sender, EventArgs e)
    {
    }

    private void textBox4_TextChanged(object sender, EventArgs e)
    {
    }

    private void clbExtra_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.clbExtra.ClearSelected();
    }

    private void button18_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("You sure added Teleport NPC ID :" + this.textBox1.Text.Trim() + " if Npc null data not update to DB. Need Add New Teleport NPC Before Update", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      if (this.textBox1.Text.Trim().Length <= 0)
      {
        int num1 = (int) MessageBox.Show("No data to select", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_npc SET a_zone_flag = '" + this.textBox2.Text + "', a_extra_flag = '" + this.textBox4.Text + "' WHERE a_index ='" + this.textBox1.Text + "'");
      int selectedIndex = this.L_Box.SelectedIndex;
      this.button2_Click(sender, e);
      int num2 = (int) new CustomMessage("Done :)").ShowDialog();
    }

    private void button15_Click(object sender, EventArgs e)
    {
      MobPicker mobPicker = new MobPicker();
      if (mobPicker.ShowDialog() != DialogResult.OK)
        return;
      this.textBox1.Text = mobPicker.MobIndex.ToString();
      this.label4.Text = this.databaseHandle.MobNameFast(Convert.ToInt32(this.textBox1.Text));
    }

    private void clbZone_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.clbZone.ClearSelected();
    }
  }
}
