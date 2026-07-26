// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.QuestSearch
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using LcDevPack_TeamDamonA.Tools.MemoryWorker.AssasinPL_Read_Need_Lod;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker
{
  public class QuestSearch : Form
  {
    public int ReturnQuestID;
    public static List<string> Menu = new List<string>();
    private List<string> MenuList = new List<string>();
    public static string ISO = "ISO-8859-1";
    private IContainer components = (IContainer) null;
    private TextBox QuestSearchBox;
    private Label label1;
    private ListBox questnameList;
    private Button button1;
    private Button CloseButton;
    private Button PickButton;
    private RichTextBox richTextBox1;
    private RichTextBox richTextBox2;
    private RichTextBox richTextBox3;

    public QuestSearch()
    {
      this.InitializeComponent();
      Encoding.GetEncoding(QuestSearch.ISO);
      for (int index = 0; index < Quest_Lod.QuestList.Count<Quest>(); ++index)
      {
        int questIndex = Quest_Lod.QuestList[index].QuestIndex;
        QuestSearch.Menu.Add(questIndex.ToString() + " " + Quest_Lod.QuestList[index].QuestName);
        this.questnameList.Items.Add((object) (questIndex.ToString() + " " + Quest_Lod.QuestList[index].QuestName));
      }
    }

    public void MakeList()
    {
      this.MenuList = QuestSearch.Menu.FindAll(new Predicate<string>(this.SearchString));
      this.questnameList.Items.Clear();
      this.questnameList.Items.AddRange((object[]) this.MenuList.ToArray());
    }

    public bool SearchString(string s) => s.ToUpper().Contains(this.QuestSearchBox.Text.ToUpper());

    public int GetIDFromList() => Convert.ToInt32(this.questnameList.Text.Split(' ')[0]);

    private void button1_Click(object sender, EventArgs e) => this.ReturnQuestID = -1;

    private void CloseButton_Click(object sender, EventArgs e) => this.ReturnQuestID = -1;

    private void PickButton_Click(object sender, EventArgs e)
    {
      this.ReturnQuestID = this.GetIDFromList();
    }

    private void QuestSearchBox_TextChanged(object sender, EventArgs e) => this.MakeList();

    private void questnameList_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (this.questnameList.SelectedIndex == -1)
        return;
      int id = this.GetIDFromList();
      int index = Quest_Lod.QuestList.FindIndex((Predicate<Quest>) (p => p.QuestIndex.Equals(id)));
      if (index == -1)
        return;
      this.richTextBox1.Text = Quest_Lod.QuestList[index].QuestInfo;
      this.richTextBox2.Text = Quest_Lod.QuestList[index].QuestNPCStory;
      this.richTextBox3.Text = Quest_Lod.QuestList[index].QuestCompleteResponse;
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      this.QuestSearchBox = new TextBox();
      this.label1 = new Label();
      this.questnameList = new ListBox();
      this.button1 = new Button();
      this.CloseButton = new Button();
      this.PickButton = new Button();
      this.richTextBox1 = new RichTextBox();
      this.richTextBox2 = new RichTextBox();
      this.richTextBox3 = new RichTextBox();
      this.SuspendLayout();
      this.QuestSearchBox.BorderStyle = BorderStyle.FixedSingle;
      this.QuestSearchBox.Location = new Point(52, 12);
      this.QuestSearchBox.Name = "QuestSearchBox";
      this.QuestSearchBox.Size = new Size(213, 20);
      this.QuestSearchBox.TabIndex = 4;
      this.QuestSearchBox.TextChanged += new EventHandler(this.QuestSearchBox_TextChanged);
      this.label1.AutoSize = true;
      this.label1.Location = new Point(5, 15);
      this.label1.Name = "label1";
      this.label1.Size = new Size(41, 13);
      this.label1.TabIndex = 3;
      this.label1.Text = "Search";
      this.questnameList.FormattingEnabled = true;
      this.questnameList.Location = new Point(8, 38);
      this.questnameList.Name = "questnameList";
      this.questnameList.Size = new Size(257, 212);
      this.questnameList.TabIndex = 5;
      this.questnameList.SelectedIndexChanged += new EventHandler(this.questnameList_SelectedIndexChanged);
      this.button1.DialogResult = DialogResult.OK;
      this.button1.Location = new Point(8, 256);
      this.button1.Name = "button1";
      this.button1.Size = new Size(96, 23);
      this.button1.TabIndex = 8;
      this.button1.Text = "Select No Item";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.CloseButton.DialogResult = DialogResult.Cancel;
      this.CloseButton.Location = new Point(167, 256);
      this.CloseButton.Name = "CloseButton";
      this.CloseButton.Size = new Size(46, 23);
      this.CloseButton.TabIndex = 7;
      this.CloseButton.Text = "Close";
      this.CloseButton.UseVisualStyleBackColor = true;
      this.CloseButton.Click += new EventHandler(this.CloseButton_Click);
      this.PickButton.DialogResult = DialogResult.OK;
      this.PickButton.Location = new Point(219, 256);
      this.PickButton.Name = "PickButton";
      this.PickButton.Size = new Size(46, 23);
      this.PickButton.TabIndex = 6;
      this.PickButton.Text = "Pick";
      this.PickButton.UseVisualStyleBackColor = true;
      this.PickButton.Click += new EventHandler(this.PickButton_Click);
      this.richTextBox1.Location = new Point(8, 285);
      this.richTextBox1.Name = "richTextBox1";
      this.richTextBox1.Size = new Size(257, 49);
      this.richTextBox1.TabIndex = 9;
      this.richTextBox1.Text = "";
      this.richTextBox2.Location = new Point(8, 340);
      this.richTextBox2.Name = "richTextBox2";
      this.richTextBox2.Size = new Size(257, 49);
      this.richTextBox2.TabIndex = 10;
      this.richTextBox2.Text = "";
      this.richTextBox3.Location = new Point(8, 395);
      this.richTextBox3.Name = "richTextBox3";
      this.richTextBox3.Size = new Size(257, 49);
      this.richTextBox3.TabIndex = 11;
      this.richTextBox3.Text = "";
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(272, 449);
      this.Controls.Add((Control) this.richTextBox3);
      this.Controls.Add((Control) this.richTextBox2);
      this.Controls.Add((Control) this.richTextBox1);
      this.Controls.Add((Control) this.button1);
      this.Controls.Add((Control) this.CloseButton);
      this.Controls.Add((Control) this.PickButton);
      this.Controls.Add((Control) this.questnameList);
      this.Controls.Add((Control) this.QuestSearchBox);
      this.Controls.Add((Control) this.label1);
      this.Name = nameof (QuestSearch);
      this.Text = nameof (QuestSearch);
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
