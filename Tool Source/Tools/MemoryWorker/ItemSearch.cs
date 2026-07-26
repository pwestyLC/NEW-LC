// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.ItemSearch
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using LcDevPack_TeamDamonA.Tools.MemoryWorker.AssasinPL_Read_Need_Lod;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker
{
  public class ItemSearch : Form
  {
    public int ReturnItemID;
    private IContainer components = (IContainer) null;
    private TextBox ItemSearchBox;
    private Label label1;
    private ListBox ItemList;
    private Button button1;
    private PictureBox IconBox;
    private TextBox DescriptionBox;
    private Button CloseButton;
    private Button PickButton;

    public ItemSearch()
    {
      this.InitializeComponent();
      this.MakeList();
    }

    private void button1_Click(object sender, EventArgs e) => this.ReturnItemID = -1;

    private void PickButton_Click(object sender, EventArgs e)
    {
      this.ReturnItemID = this.GetIDFromList();
    }

    public int GetIDFromList() => Convert.ToInt32(this.ItemList.Text.Split(' ')[0]);

    private void ItemSearchBox_TextChanged(object sender, EventArgs e)
    {
      this.ItemList.Items.Clear();
      for (int index = 0; index < Item_Lod.ItemList.Count<ItemContainer>(); ++index)
      {
        string str = Item_Lod.ItemList[index].ItemID.ToString() + " " + Item_Lod.ItemList[index].Name;
        if (str.ToUpper().IndexOf(this.ItemSearchBox.Text.ToUpper()) != -1)
          this.ItemList.Items.Add((object) str);
      }
    }

    public void MakeList()
    {
      this.ItemList.Items.Clear();
      for (int index = 0; index < Item_Lod.ItemList.Count<ItemContainer>(); ++index)
        this.ItemList.Items.Add((object) (Item_Lod.ItemList[index].ItemID.ToString() + " " + Item_Lod.ItemList[index].Name));
    }

    private void ItemList_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (this.ItemList.SelectedIndex == -1)
        return;
      int id = this.GetIDFromList();
      int index = Item_Lod.ItemList.FindIndex((Predicate<ItemContainer>) (p => p.ItemID.Equals(id)));
      if (index == -1)
        return;
      this.DescriptionBox.Text = Item_Lod.ItemList[index].Description;
      this.IconBox.Image = (Image) Item_Lod.Icon(Item_Lod.ItemList[index].TexID, Item_Lod.ItemList[index].TexRow, Item_Lod.ItemList[index].TexCol);
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      this.ItemSearchBox = new TextBox();
      this.label1 = new Label();
      this.ItemList = new ListBox();
      this.button1 = new Button();
      this.IconBox = new PictureBox();
      this.DescriptionBox = new TextBox();
      this.CloseButton = new Button();
      this.PickButton = new Button();
      ((ISupportInitialize) this.IconBox).BeginInit();
      this.SuspendLayout();
      this.ItemSearchBox.BorderStyle = BorderStyle.FixedSingle;
      this.ItemSearchBox.Location = new Point(54, 12);
      this.ItemSearchBox.Name = "ItemSearchBox";
      this.ItemSearchBox.Size = new Size(213, 20);
      this.ItemSearchBox.TabIndex = 9;
      this.ItemSearchBox.TextChanged += new EventHandler(this.ItemSearchBox_TextChanged);
      this.label1.AutoSize = true;
      this.label1.Location = new Point(7, 15);
      this.label1.Name = "label1";
      this.label1.Size = new Size(41, 13);
      this.label1.TabIndex = 6;
      this.label1.Text = "Search";
      this.ItemList.FormattingEnabled = true;
      this.ItemList.Location = new Point(10, 38);
      this.ItemList.Name = "ItemList";
      this.ItemList.Size = new Size(257, 212);
      this.ItemList.TabIndex = 7;
      this.ItemList.SelectedIndexChanged += new EventHandler(this.ItemList_SelectedIndexChanged);
      this.button1.DialogResult = DialogResult.OK;
      this.button1.Location = new Point(12, 256);
      this.button1.Name = "button1";
      this.button1.Size = new Size(96, 23);
      this.button1.TabIndex = 12;
      this.button1.Text = "Select No Item";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.IconBox.BorderStyle = BorderStyle.FixedSingle;
      this.IconBox.Location = new Point(13, 289);
      this.IconBox.Name = "IconBox";
      this.IconBox.Size = new Size(34, 34);
      this.IconBox.TabIndex = 11;
      this.IconBox.TabStop = false;
      this.DescriptionBox.BorderStyle = BorderStyle.FixedSingle;
      this.DescriptionBox.Location = new Point(59, 284);
      this.DescriptionBox.Multiline = true;
      this.DescriptionBox.Name = "DescriptionBox";
      this.DescriptionBox.Size = new Size(208, 44);
      this.DescriptionBox.TabIndex = 10;
      this.CloseButton.DialogResult = DialogResult.Cancel;
      this.CloseButton.Location = new Point(169, 256);
      this.CloseButton.Name = "CloseButton";
      this.CloseButton.Size = new Size(46, 23);
      this.CloseButton.TabIndex = 8;
      this.CloseButton.Text = "Close";
      this.CloseButton.UseVisualStyleBackColor = true;
      this.PickButton.DialogResult = DialogResult.OK;
      this.PickButton.Location = new Point(221, 256);
      this.PickButton.Name = "PickButton";
      this.PickButton.Size = new Size(46, 23);
      this.PickButton.TabIndex = 5;
      this.PickButton.Text = "Pick";
      this.PickButton.UseVisualStyleBackColor = true;
      this.PickButton.Click += new EventHandler(this.PickButton_Click);
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(274, 333);
      this.Controls.Add((Control) this.ItemSearchBox);
      this.Controls.Add((Control) this.label1);
      this.Controls.Add((Control) this.ItemList);
      this.Controls.Add((Control) this.button1);
      this.Controls.Add((Control) this.IconBox);
      this.Controls.Add((Control) this.DescriptionBox);
      this.Controls.Add((Control) this.CloseButton);
      this.Controls.Add((Control) this.PickButton);
      this.MaximizeBox = false;
      this.MaximumSize = new Size(290, 371);
      this.MinimizeBox = false;
      this.MinimumSize = new Size(290, 371);
      this.Name = nameof (ItemSearch);
      this.Text = nameof (ItemSearch);
      ((ISupportInitialize) this.IconBox).EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
