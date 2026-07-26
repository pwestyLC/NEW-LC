// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.NpcSearch
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using LcDevPack_TeamDamonA.Tools.MemoryWorker.AssasinPL_Read_Need_Lod;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker
{
  public class NpcSearch : Form
  {
    public static List<Mob> NPCList = new List<Mob>();
    public int ReturnNpcID;
    private IContainer components = (IContainer) null;
    private TextBox NpcSearchBox;
    private Label label1;
    private ListBox npcnameList;
    private Button button1;
    private Button CloseButton;
    private Button PickButton;

    public NpcSearch()
    {
      this.InitializeComponent();
      this.MakeList();
    }

    public void MakeList()
    {
      Mob_Lod.MenuList = Mob_Lod.Menu.FindAll(new Predicate<string>(this.SearchString));
      this.npcnameList.Items.Clear();
      this.npcnameList.Items.AddRange((object[]) Mob_Lod.MenuList.ToArray());
    }

    private void button1_Click(object sender, EventArgs e) => this.ReturnNpcID = -1;

    private void PickButton_Click(object sender, EventArgs e)
    {
      this.ReturnNpcID = this.GetIDFromList();
    }

    public int NpcID => this.ReturnNpcID;

    public int GetIDFromList() => Convert.ToInt32(this.npcnameList.Text.Split(' ')[0]);

    private void npcnameList_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.GetIDFromList();
    }

    public bool SearchString(string s) => s.ToUpper().Contains(this.NpcSearchBox.Text.ToUpper());

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      this.NpcSearchBox = new TextBox();
      this.label1 = new Label();
      this.npcnameList = new ListBox();
      this.button1 = new Button();
      this.CloseButton = new Button();
      this.PickButton = new Button();
      this.SuspendLayout();
      this.NpcSearchBox.BorderStyle = BorderStyle.FixedSingle;
      this.NpcSearchBox.Location = new Point(52, 12);
      this.NpcSearchBox.Name = "NpcSearchBox";
      this.NpcSearchBox.Size = new Size(213, 20);
      this.NpcSearchBox.TabIndex = 4;
      this.label1.AutoSize = true;
      this.label1.Location = new Point(5, 15);
      this.label1.Name = "label1";
      this.label1.Size = new Size(41, 13);
      this.label1.TabIndex = 3;
      this.label1.Text = "Search";
      this.npcnameList.FormattingEnabled = true;
      this.npcnameList.Location = new Point(8, 38);
      this.npcnameList.Name = "npcnameList";
      this.npcnameList.Size = new Size(257, 225);
      this.npcnameList.TabIndex = 5;
      this.npcnameList.SelectedIndexChanged += new EventHandler(this.npcnameList_SelectedIndexChanged);
      this.button1.DialogResult = DialogResult.OK;
      this.button1.Location = new Point(8, 269);
      this.button1.Name = "button1";
      this.button1.Size = new Size(96, 23);
      this.button1.TabIndex = 8;
      this.button1.Text = "Select No Item";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.CloseButton.DialogResult = DialogResult.Cancel;
      this.CloseButton.Location = new Point(167, 269);
      this.CloseButton.Name = "CloseButton";
      this.CloseButton.Size = new Size(46, 23);
      this.CloseButton.TabIndex = 7;
      this.CloseButton.Text = "Close";
      this.CloseButton.UseVisualStyleBackColor = true;
      this.PickButton.DialogResult = DialogResult.OK;
      this.PickButton.Location = new Point(219, 269);
      this.PickButton.Name = "PickButton";
      this.PickButton.Size = new Size(46, 23);
      this.PickButton.TabIndex = 6;
      this.PickButton.Text = "Pick";
      this.PickButton.UseVisualStyleBackColor = true;
      this.PickButton.Click += new EventHandler(this.PickButton_Click);
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(270, 296);
      this.Controls.Add((Control) this.button1);
      this.Controls.Add((Control) this.CloseButton);
      this.Controls.Add((Control) this.PickButton);
      this.Controls.Add((Control) this.npcnameList);
      this.Controls.Add((Control) this.NpcSearchBox);
      this.Controls.Add((Control) this.label1);
      this.FormBorderStyle = FormBorderStyle.FixedDialog;
      this.MaximizeBox = false;
      this.MaximumSize = new Size(286, 334);
      this.MinimizeBox = false;
      this.MinimumSize = new Size(286, 334);
      this.Name = nameof (NpcSearch);
      this.StartPosition = FormStartPosition.CenterScreen;
      this.Text = nameof (NpcSearch);
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
