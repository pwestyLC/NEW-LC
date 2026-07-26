// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.LevelUpGuide.LevelUpGuide
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.LevelUpGuide
{
  public class LevelUpGuide : Form
  {
    public static string stritem;
    public static string stritemname;
    public static List<LevelUP> ItemList = new List<LevelUP>();
    public string _ClientPath = LcDevPack_TeamDamonA.Tools.MobEditor.connection.Settings.ClientPath;
    private IContainer components = (IContainer) null;
    private MenuStrip menuStrip1;
    private ToolStripMenuItem fileToolStripMenuItem;
    private ToolStripMenuItem openToolStripMenuItem;
    private ToolStripMenuItem saveToolStripMenuItem;
    private RichTextBox richTextBox1;
    private Button button3;
    private Button button2;
    private Button button1;
    private Label label3;
    private Label label2;
    private TextBox textBox2;
    private Label label1;
    private TextBox textBox1;
    private ListBox ItemListBox;

    public LevelUpGuide() => this.InitializeComponent();

    private void openToolStripMenuItem_Click(object sender, EventArgs e)
    {
      OpenFileDialog openFileDialog1 = new OpenFileDialog();
      openFileDialog1.Title = "Abrir levelup_guide.bin";
      openFileDialog1.InitialDirectory = this._ClientPath;
      openFileDialog1.Filter = "levelup_guide.bin|levelup_guide.bin|All|*.*";
      if (openFileDialog1.ShowDialog() == DialogResult.Cancel)
        return;
      OpenFileDialog openFileDialog2 = new OpenFileDialog();
      openFileDialog2.Title = "Abrir strClient_us.lod";
      openFileDialog2.InitialDirectory = this._ClientPath;
      openFileDialog2.Filter = "strClient*.lod|strClient*.lod|All|*.*";
      if (openFileDialog2.ShowDialog() != DialogResult.Cancel)
      {
        LcDevPack_TeamDamonA.Tools.MemoryWorker.LevelUpGuide.LevelUpGuide.ItemList.Clear();
        this.ItemListBox.Items.Clear();
        this.ReadItem(openFileDialog1.FileName);
        this.ReadItemName(openFileDialog2.FileName);
        this.makelist();
      }
    }

    private void ReadItem(string itemsource)
    {
      using (BinaryReader binaryReader = new BinaryReader((Stream) File.Open(itemsource, FileMode.Open)))
      {
        binaryReader.ReadInt32();
        while (binaryReader.BaseStream.Position < binaryReader.BaseStream.Length)
          LcDevPack_TeamDamonA.Tools.MemoryWorker.LevelUpGuide.LevelUpGuide.ItemList.Add(new LevelUP()
          {
            Level = binaryReader.ReadInt32(),
            StringIndex = binaryReader.ReadInt32()
          });
      }
    }

    private void ReadItemName(string itemnamesource)
    {
      using (BinaryReader binaryReader = new BinaryReader((Stream) File.Open(itemnamesource, FileMode.Open)))
      {
        binaryReader.ReadInt32();
        binaryReader.ReadInt32();
        while (binaryReader.BaseStream.Position < binaryReader.BaseStream.Length)
        {
          int ID = binaryReader.ReadInt32();
          int index = LcDevPack_TeamDamonA.Tools.MemoryWorker.LevelUpGuide.LevelUpGuide.ItemList.FindIndex((Predicate<LevelUP>) (p => p.StringIndex.Equals(ID)));
          string str = Encoding.GetEncoding("ISO-8859-1").GetString(binaryReader.ReadBytes(binaryReader.ReadInt32()));
          if (index != -1)
            LcDevPack_TeamDamonA.Tools.MemoryWorker.LevelUpGuide.LevelUpGuide.ItemList[index].Name = str;
        }
        binaryReader.Close();
        binaryReader.Dispose();
      }
    }

    private void makelist()
    {
      List<LevelUP> list = LcDevPack_TeamDamonA.Tools.MemoryWorker.LevelUpGuide.LevelUpGuide.ItemList.OrderBy<LevelUP, int>((Func<LevelUP, int>) (o => o.Level)).ToList<LevelUP>();
      int num = list.Count<LevelUP>();
      for (int index = 0; index < num; ++index)
      {
        int level = list[index].Level;
        string name = list[index].Name;
        this.ItemListBox.Items.Add((object) (level.ToString() + " - " + name + ")"));
      }
    }

    public int GetIDFromList()
    {
      int idFromList;
      try
      {
        idFromList = Convert.ToInt32(this.ItemListBox.Text.Split(' ')[0]);
      }
      catch
      {
        idFromList = 2;
      }
      return idFromList;
    }

    public void ViewItem()
    {
      int ID = this.GetIDFromList();
      int index = LcDevPack_TeamDamonA.Tools.MemoryWorker.LevelUpGuide.LevelUpGuide.ItemList.FindIndex((Predicate<LevelUP>) (p => p.Level.Equals(ID)));
      this.textBox1.Text = LcDevPack_TeamDamonA.Tools.MemoryWorker.LevelUpGuide.LevelUpGuide.ItemList[index].Level.ToString();
      this.textBox2.Text = LcDevPack_TeamDamonA.Tools.MemoryWorker.LevelUpGuide.LevelUpGuide.ItemList[index].StringIndex.ToString();
      this.richTextBox1.Text = LcDevPack_TeamDamonA.Tools.MemoryWorker.LevelUpGuide.LevelUpGuide.ItemList[index].Name;
    }

    private void ItemListBox_SelectedIndexChanged(object sender, EventArgs e) => this.ViewItem();

    private void saveToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (this.ItemListBox.Items.Count == 0)
        return;
      SaveFileDialog saveFileDialog = new SaveFileDialog();
      saveFileDialog.Filter = "levelup_guide.bin|levelup_guide*.bin|bin|*.bin|All|*.*";
      saveFileDialog.Title = "Save levelup_guide.bin";
      int num1 = (int) saveFileDialog.ShowDialog();
      if (saveFileDialog.FileName != "")
      {
        try
        {
          BinaryWriter binaryWriter = new BinaryWriter((Stream) new FileStream(saveFileDialog.FileName, FileMode.Create));
          binaryWriter.Write(LcDevPack_TeamDamonA.Tools.MemoryWorker.LevelUpGuide.LevelUpGuide.ItemList[LcDevPack_TeamDamonA.Tools.MemoryWorker.LevelUpGuide.LevelUpGuide.ItemList.Count - 1].Level);
          for (int index = 0; index <= LcDevPack_TeamDamonA.Tools.MemoryWorker.LevelUpGuide.LevelUpGuide.ItemList.Count<LevelUP>() - 1; ++index)
          {
            binaryWriter.Write(LcDevPack_TeamDamonA.Tools.MemoryWorker.LevelUpGuide.LevelUpGuide.ItemList[index].Level);
            binaryWriter.Write(LcDevPack_TeamDamonA.Tools.MemoryWorker.LevelUpGuide.LevelUpGuide.ItemList[index].StringIndex);
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

    private void button1_Click(object sender, EventArgs e)
    {
      if (this.ItemListBox.Items.Count != 0 && MessageBox.Show("Are you sure you want to add new record?", "Adder", MessageBoxButtons.YesNo) == DialogResult.Yes)
      {
        int num = LcDevPack_TeamDamonA.Tools.MemoryWorker.LevelUpGuide.LevelUpGuide.ItemList[LcDevPack_TeamDamonA.Tools.MemoryWorker.LevelUpGuide.LevelUpGuide.ItemList.Count - 1].Level + 1;
        LcDevPack_TeamDamonA.Tools.MemoryWorker.LevelUpGuide.LevelUpGuide.ItemList.Add(new LevelUP()
        {
          Level = num,
          StringIndex = 1
        });
        this.ItemListBox.Items.Clear();
      }
      this.ItemListBox.SelectedIndex = this.ItemListBox.Items.Count - 1;
      this.makelist();
    }

    private void button3_Click(object sender, EventArgs e)
    {
      if (this.ItemListBox.SelectedIndex == -1 || MessageBox.Show("Are you sure you want to save the record?", "Save Select", MessageBoxButtons.YesNo) != DialogResult.Yes)
        return;
      this.SaveLevelGuide();
      this.makelist();
    }

    private void button2_Click(object sender, EventArgs e)
    {
      int ID = this.GetIDFromList();
      int index = LcDevPack_TeamDamonA.Tools.MemoryWorker.LevelUpGuide.LevelUpGuide.ItemList.FindIndex((Predicate<LevelUP>) (p => p.Level.Equals(ID)));
      if (index == -1 || MessageBox.Show("Are you sure you want to delete the record?", "removal", MessageBoxButtons.YesNo) != DialogResult.Yes)
        return;
      LcDevPack_TeamDamonA.Tools.MemoryWorker.LevelUpGuide.LevelUpGuide.ItemList.RemoveAt(index);
      this.makelist();
    }

    private void SaveLevelGuide()
    {
      try
      {
        int ID = this.GetIDFromList();
        int index = LcDevPack_TeamDamonA.Tools.MemoryWorker.LevelUpGuide.LevelUpGuide.ItemList.FindIndex((Predicate<LevelUP>) (p => p.Level.Equals(ID)));
        if (index == -1)
          return;
        LcDevPack_TeamDamonA.Tools.MemoryWorker.LevelUpGuide.LevelUpGuide.ItemList[index].Level = Convert.ToInt32(this.textBox1.Text);
        LcDevPack_TeamDamonA.Tools.MemoryWorker.LevelUpGuide.LevelUpGuide.ItemList[index].StringIndex = Convert.ToInt32(this.textBox2.Text);
      }
      catch (Exception ex)
      {
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
      this.openToolStripMenuItem = new ToolStripMenuItem();
      this.saveToolStripMenuItem = new ToolStripMenuItem();
      this.richTextBox1 = new RichTextBox();
      this.button3 = new Button();
      this.button2 = new Button();
      this.button1 = new Button();
      this.label3 = new Label();
      this.label2 = new Label();
      this.textBox2 = new TextBox();
      this.label1 = new Label();
      this.textBox1 = new TextBox();
      this.ItemListBox = new ListBox();
      this.menuStrip1.SuspendLayout();
      this.SuspendLayout();
      this.menuStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.fileToolStripMenuItem
      });
      this.menuStrip1.Location = new Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new Size(428, 24);
      this.menuStrip1.TabIndex = 0;
      this.menuStrip1.Text = "menuStrip1";
      this.fileToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[2]
      {
        (ToolStripItem) this.openToolStripMenuItem,
        (ToolStripItem) this.saveToolStripMenuItem
      });
      this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
      this.fileToolStripMenuItem.Size = new Size(37, 20);
      this.fileToolStripMenuItem.Text = "File";
      this.openToolStripMenuItem.Name = "openToolStripMenuItem";
      this.openToolStripMenuItem.Size = new Size(152, 22);
      this.openToolStripMenuItem.Text = "Open";
      this.openToolStripMenuItem.Click += new EventHandler(this.openToolStripMenuItem_Click);
      this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
      this.saveToolStripMenuItem.Size = new Size(152, 22);
      this.saveToolStripMenuItem.Text = "Save";
      this.saveToolStripMenuItem.Click += new EventHandler(this.saveToolStripMenuItem_Click);
      this.richTextBox1.Location = new Point(197, 93);
      this.richTextBox1.Name = "richTextBox1";
      this.richTextBox1.Size = new Size(222, 96);
      this.richTextBox1.TabIndex = 21;
      this.richTextBox1.Text = "";
      this.button3.Location = new Point(52, 227);
      this.button3.Name = "button3";
      this.button3.Size = new Size(43, 23);
      this.button3.TabIndex = 20;
      this.button3.Text = "Save";
      this.button3.UseVisualStyleBackColor = true;
      this.button3.Click += new EventHandler(this.button3_Click);
      this.button2.Location = new Point(101, 227);
      this.button2.Name = "button2";
      this.button2.Size = new Size(31, 23);
      this.button2.TabIndex = 19;
      this.button2.Text = "Del";
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.button1.Location = new Point(12, 227);
      this.button1.Name = "button1";
      this.button1.Size = new Size(34, 23);
      this.button1.TabIndex = 18;
      this.button1.Text = "Add";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.label3.AutoSize = true;
      this.label3.Location = new Point(138, 135);
      this.label3.Name = "label3";
      this.label3.Size = new Size(40, 13);
      this.label3.TabIndex = 17;
      this.label3.Text = "String :";
      this.label2.AutoSize = true;
      this.label2.Location = new Point(135, 67);
      this.label2.Name = "label2";
      this.label2.Size = new Size(53, 13);
      this.label2.TabIndex = 16;
      this.label2.Text = "str Index :";
      this.textBox2.Location = new Point(197, 64);
      this.textBox2.Name = "textBox2";
      this.textBox2.Size = new Size(100, 20);
      this.textBox2.TabIndex = 15;
      this.label1.AutoSize = true;
      this.label1.Location = new Point(135, 41);
      this.label1.Name = "label1";
      this.label1.Size = new Size(39, 13);
      this.label1.TabIndex = 14;
      this.label1.Text = "Level :";
      this.textBox1.Location = new Point(197, 38);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(100, 20);
      this.textBox1.TabIndex = 13;
      this.ItemListBox.FormattingEnabled = true;
      this.ItemListBox.Location = new Point(12, 27);
      this.ItemListBox.Name = "ItemListBox";
      this.ItemListBox.Size = new Size(120, 199);
      this.ItemListBox.TabIndex = 12;
      this.ItemListBox.SelectedIndexChanged += new EventHandler(this.ItemListBox_SelectedIndexChanged);
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(428, 266);
      this.Controls.Add((Control) this.richTextBox1);
      this.Controls.Add((Control) this.button3);
      this.Controls.Add((Control) this.button2);
      this.Controls.Add((Control) this.button1);
      this.Controls.Add((Control) this.label3);
      this.Controls.Add((Control) this.label2);
      this.Controls.Add((Control) this.textBox2);
      this.Controls.Add((Control) this.label1);
      this.Controls.Add((Control) this.textBox1);
      this.Controls.Add((Control) this.ItemListBox);
      this.Controls.Add((Control) this.menuStrip1);
      this.FormBorderStyle = FormBorderStyle.FixedToolWindow;
      this.MainMenuStrip = this.menuStrip1;
      this.MaximumSize = new Size(444, 300);
      this.MinimizeBox = false;
      this.MinimumSize = new Size(444, 300);
      this.Name = nameof (LevelUpGuide);
      this.Text = nameof (LevelUpGuide);
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
