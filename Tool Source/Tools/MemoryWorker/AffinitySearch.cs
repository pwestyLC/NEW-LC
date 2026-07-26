// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.AffinitySearch
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using LcDevPack_TeamDamonA.Tools.MemoryWorker.Affinity_EP4_By_Assasin;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker
{
  public class AffinitySearch : Form
  {
    public static List<string> Menu = new List<string>();
    private List<string> MenuList = new List<string>();
    public int ReturnAffinityID;
    private IContainer components = (IContainer) null;
    private TextBox AffinitySearchBox;
    private Label label1;
    private ListBox affinitynamelist;
    private Button button1;
    private PictureBox pictureBox_Affinity;
    private Button CloseButton;
    private Button PickButton;

    public AffinitySearch()
    {
      this.InitializeComponent();
      AffinitySearch.Menu.Clear();
      for (int index = 0; index < Affinity_EP4.AffinityList.Count<tAffinity>(); ++index)
      {
        int aIndex = Affinity_EP4.AffinityList[index].a_index;
        AffinitySearch.Menu.Add(aIndex.ToString() + " " + Affinity_EP4.AffinityList[index].a_name_usa);
        this.affinitynamelist.Items.Add((object) (aIndex.ToString() + " " + Affinity_EP4.AffinityList[index].a_name_usa));
      }
    }

    public int GetIDFromList()
    {
      try
      {
        return Convert.ToInt32(this.affinitynamelist.Text.Split(' ')[0]);
      }
      catch
      {
        return -1;
      }
    }

    private void AffinitySearch_Load(object sender, EventArgs e)
    {
    }

    private void button1_Click(object sender, EventArgs e) => this.ReturnAffinityID = -1;

    private void PickButton_Click(object sender, EventArgs e)
    {
      this.ReturnAffinityID = this.GetIDFromList();
    }

    private void affinitynamelist_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (this.affinitynamelist.SelectedIndex == -1)
        return;
      int index = Affinity_EP4.AffinityList.FindIndex((Predicate<tAffinity>) (p => p.a_index.Equals(this.GetIDFromList())));
      if (index == -1)
        return;
      this.pictureBox_Affinity.Image = (Image) Affinity_EP4.AffinityIcons(Affinity_EP4.AffinityList[index].a_texture_id, Affinity_EP4.AffinityList[index].a_texture_row, Affinity_EP4.AffinityList[index].a_texture_col);
    }

    public void MakeList()
    {
      this.MenuList = AffinitySearch.Menu.FindAll(new Predicate<string>(this.SearchString));
      this.affinitynamelist.Items.Clear();
      this.affinitynamelist.Items.AddRange((object[]) this.MenuList.ToArray());
    }

    public bool SearchString(string s)
    {
      return s.ToUpper().Contains(this.AffinitySearchBox.Text.ToUpper());
    }

    private void AffinitySearchBox_TextChanged(object sender, EventArgs e) => this.MakeList();

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      this.AffinitySearchBox = new TextBox();
      this.label1 = new Label();
      this.affinitynamelist = new ListBox();
      this.button1 = new Button();
      this.pictureBox_Affinity = new PictureBox();
      this.CloseButton = new Button();
      this.PickButton = new Button();
      ((ISupportInitialize) this.pictureBox_Affinity).BeginInit();
      this.SuspendLayout();
      this.AffinitySearchBox.BorderStyle = BorderStyle.FixedSingle;
      this.AffinitySearchBox.Location = new Point(51, 12);
      this.AffinitySearchBox.Name = "AffinitySearchBox";
      this.AffinitySearchBox.Size = new Size(213, 20);
      this.AffinitySearchBox.TabIndex = 4;
      this.AffinitySearchBox.TextChanged += new EventHandler(this.AffinitySearchBox_TextChanged);
      this.label1.AutoSize = true;
      this.label1.Location = new Point(4, 15);
      this.label1.Name = "label1";
      this.label1.Size = new Size(41, 13);
      this.label1.TabIndex = 3;
      this.label1.Text = "Search";
      this.affinitynamelist.FormattingEnabled = true;
      this.affinitynamelist.Location = new Point(7, 38);
      this.affinitynamelist.Name = "affinitynamelist";
      this.affinitynamelist.Size = new Size(257, 173);
      this.affinitynamelist.TabIndex = 5;
      this.affinitynamelist.SelectedIndexChanged += new EventHandler(this.affinitynamelist_SelectedIndexChanged);
      this.button1.DialogResult = DialogResult.OK;
      this.button1.Location = new Point(7, 217);
      this.button1.Name = "button1";
      this.button1.Size = new Size(96, 23);
      this.button1.TabIndex = 13;
      this.button1.Text = "Select No Item";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.pictureBox_Affinity.Location = new Point(128, 217);
      this.pictureBox_Affinity.Name = "pictureBox_Affinity";
      this.pictureBox_Affinity.Size = new Size(32, 32);
      this.pictureBox_Affinity.TabIndex = 12;
      this.pictureBox_Affinity.TabStop = false;
      this.CloseButton.DialogResult = DialogResult.Cancel;
      this.CloseButton.Location = new Point(166, 217);
      this.CloseButton.Name = "CloseButton";
      this.CloseButton.Size = new Size(46, 23);
      this.CloseButton.TabIndex = 11;
      this.CloseButton.Text = "Close";
      this.CloseButton.UseVisualStyleBackColor = true;
      this.PickButton.DialogResult = DialogResult.OK;
      this.PickButton.Location = new Point(218, 217);
      this.PickButton.Name = "PickButton";
      this.PickButton.Size = new Size(46, 23);
      this.PickButton.TabIndex = 10;
      this.PickButton.Text = "Pick";
      this.PickButton.UseVisualStyleBackColor = true;
      this.PickButton.Click += new EventHandler(this.PickButton_Click);
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(272, 258);
      this.Controls.Add((Control) this.button1);
      this.Controls.Add((Control) this.pictureBox_Affinity);
      this.Controls.Add((Control) this.CloseButton);
      this.Controls.Add((Control) this.PickButton);
      this.Controls.Add((Control) this.affinitynamelist);
      this.Controls.Add((Control) this.AffinitySearchBox);
      this.Controls.Add((Control) this.label1);
      this.MaximizeBox = false;
      this.MinimizeBox = false;
      this.Name = nameof (AffinitySearch);
      this.StartPosition = FormStartPosition.CenterParent;
      this.Text = nameof (AffinitySearch);
      this.Load += new EventHandler(this.AffinitySearch_Load);
      ((ISupportInitialize) this.pictureBox_Affinity).EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
