// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.Catalog_Editor.ItemSearch
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.Catalog_Editor
{
  public class ItemSearch : Form
  {
    private List<string> MenuList = new List<string>();
    private IContainer components;
    private TextBox DescriptionBox;
    private PictureBox IconBox;
    private TextBox ItemSearchBox;
    private Label label1;
    private Button PickButton;
    public int ReturnItemID;
    private GroupBox groupBox2;
    private string Search;
    private string Done;
    private ListBox List_Select_Item;
    private CheckedListBox checkedListBox1;
    private int ID;

    public int ItemID => this.ReturnItemID;

    public ItemSearch(int idx)
    {
      this.InitializeComponent();
      this.MakeList();
      this.ID = idx;
    }

    private void button1_Click(object sender, EventArgs e) => this.ReturnItemID = 0;

    private void CloseButton_Click(object sender, EventArgs e) => this.Close();

    private void CloseButton_Click_1(object sender, EventArgs e)
    {
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    public int GetIDFromList() => Convert.ToInt32(this.checkedListBox1.Text.Split(' ')[0]);

    private void InitializeComponent()
    {
      this.ItemSearchBox = new TextBox();
      this.label1 = new Label();
      this.IconBox = new PictureBox();
      this.DescriptionBox = new TextBox();
      this.PickButton = new Button();
      this.groupBox2 = new GroupBox();
      this.List_Select_Item = new ListBox();
      this.checkedListBox1 = new CheckedListBox();
      ((ISupportInitialize) this.IconBox).BeginInit();
      this.groupBox2.SuspendLayout();
      this.SuspendLayout();
      this.ItemSearchBox.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
      this.ItemSearchBox.Location = new Point(6, 19);
      this.ItemSearchBox.Name = "ItemSearchBox";
      this.ItemSearchBox.Size = new Size(221, 20);
      this.ItemSearchBox.TabIndex = 2;
      this.ItemSearchBox.TextChanged += new EventHandler(this.ItemSearchBox_TextChanged);
      this.label1.AutoSize = true;
      this.label1.Location = new Point(12, 16);
      this.label1.Name = "label1";
      this.label1.Size = new Size(39, 13);
      this.label1.TabIndex = 1;
      this.label1.Text = "Search";
      this.IconBox.BorderStyle = BorderStyle.FixedSingle;
      this.IconBox.Location = new Point(211, 301);
      this.IconBox.Name = "IconBox";
      this.IconBox.Size = new Size(34, 34);
      this.IconBox.TabIndex = 3;
      this.IconBox.TabStop = false;
      this.DescriptionBox.Location = new Point(12, 301);
      this.DescriptionBox.Multiline = true;
      this.DescriptionBox.Name = "DescriptionBox";
      this.DescriptionBox.Size = new Size(195, 34);
      this.DescriptionBox.TabIndex = 2;
      this.PickButton.DialogResult = DialogResult.OK;
      this.PickButton.Location = new Point(12, 341);
      this.PickButton.Name = "PickButton";
      this.PickButton.Size = new Size(233, 23);
      this.PickButton.TabIndex = 0;
      this.PickButton.Text = "Choose";
      this.PickButton.UseVisualStyleBackColor = true;
      this.PickButton.Click += new EventHandler(this.PickButton_Click);
      this.groupBox2.Controls.Add((Control) this.ItemSearchBox);
      this.groupBox2.Location = new Point(12, 12);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new Size(233, 48);
      this.groupBox2.TabIndex = 67;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "Search";
      this.List_Select_Item.FormattingEnabled = true;
      this.List_Select_Item.Location = new Point(12, 66);
      this.List_Select_Item.Name = "List_Select_Item";
      this.List_Select_Item.Size = new Size(93, 225);
      this.List_Select_Item.TabIndex = 68;
      this.List_Select_Item.SelectedIndexChanged += new EventHandler(this.List_Select_Item_SelectedIndexChanged);
      this.checkedListBox1.FormattingEnabled = true;
      this.checkedListBox1.Location = new Point(111, 66);
      this.checkedListBox1.Name = "checkedListBox1";
      this.checkedListBox1.Size = new Size(120, 229);
      this.checkedListBox1.TabIndex = 69;
      this.checkedListBox1.SelectedIndexChanged += new EventHandler(this.checkedListBox1_SelectedIndexChanged);
      this.ClientSize = new Size(257, 376);
      this.Controls.Add((Control) this.checkedListBox1);
      this.Controls.Add((Control) this.List_Select_Item);
      this.Controls.Add((Control) this.IconBox);
      this.Controls.Add((Control) this.groupBox2);
      this.Controls.Add((Control) this.PickButton);
      this.Controls.Add((Control) this.DescriptionBox);
      this.FormBorderStyle = FormBorderStyle.FixedToolWindow;
      this.Name = nameof (ItemSearch);
      this.ShowInTaskbar = false;
      this.StartPosition = FormStartPosition.CenterScreen;
      this.Load += new EventHandler(this.ItemSearch_Load);
      ((ISupportInitialize) this.IconBox).EndInit();
      this.groupBox2.ResumeLayout(false);
      this.groupBox2.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();
    }

    private void ItemList_SelectedIndexChanged(object sender, EventArgs e)
    {
      int ItemID = this.GetIDFromList();
      int index = itemAll.ItemList.FindIndex((Predicate<itemAll.t_ItemAll>) (p => p.ItemID.Equals(ItemID)));
      if (index == -1)
        return;
      this.DescriptionBox.Text = strItem.ItemList[index].Descr_1;
      this.IconBox.Image = (Image) itemAll.Icon1(itemAll.ItemList[index].TexID, itemAll.ItemList[index].TexRow, itemAll.ItemList[index].TexCol);
    }

    private void ItemSearchBox_TextChanged(object sender, EventArgs e) => this.MakeList();

    public void MakeList()
    {
      this.MenuList = strItem.Menu_STRITEM.FindAll(new Predicate<string>(this.SearchString));
      this.List_Select_Item.Items.Clear();
      this.List_Select_Item.Items.AddRange((object[]) this.MenuList.ToArray());
      this.checkedListBox1.Items.AddRange((object[]) this.MenuList.ToArray());
    }

    private int GetID(string text)
    {
      int result = -1;
      int.TryParse(text.Split(' ')[0], out result);
      return result;
    }

    private void PickButton_Click(object sender, EventArgs e)
    {
      int index = Form2.MallProducts.FindIndex((Predicate<ItemMallContainer>) (p => p.PackID.Equals(this.ID)));
      ++Form2.MallProducts[index].PkgAmount;
      Form2.MallProducts[index].Items.Add(new tMallItem()
      {
        ItemID = this.GetIDFromList(),
        Level = 0,
        Plus = 0,
        Option = 0,
        Amount = 1
      });
    }

    public bool SearchString(string s) => s.ToUpper().Contains(this.ItemSearchBox.Text.ToUpper());

    private void ItemSearch_Load(object sender, EventArgs e)
    {
    }

    private void List_Select_Item_SelectedIndexChanged(object sender, EventArgs e)
    {
      int ItemID = this.GetIDFromList();
      int index = itemAll.ItemList.FindIndex((Predicate<itemAll.t_ItemAll>) (p => p.ItemID.Equals(ItemID)));
      if (index == -1)
        return;
      this.DescriptionBox.Text = strItem.ItemList[index].Descr_1;
      this.IconBox.Image = (Image) itemAll.Icon1(itemAll.ItemList[index].TexID, itemAll.ItemList[index].TexRow, itemAll.ItemList[index].TexCol);
    }

    private void checkedListBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      int ItemID = this.GetIDFromList();
      int index = itemAll.ItemList.FindIndex((Predicate<itemAll.t_ItemAll>) (p => p.ItemID.Equals(ItemID)));
      if (index == -1)
        return;
      this.DescriptionBox.Text = strItem.ItemList[index].Descr_1;
      this.IconBox.Image = (Image) itemAll.Icon1(itemAll.ItemList[index].TexID, itemAll.ItemList[index].TexRow, itemAll.ItemList[index].TexCol);
    }
  }
}
