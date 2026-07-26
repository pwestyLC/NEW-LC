// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.Catalog_Editor.File2_F
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.Catalog_Editor
{
  public class File2_F : Form
  {
    private static byte[] key = new byte[0];
    public static System.Collections.Generic.List<ItemMallContainer> List = new System.Collections.Generic.List<ItemMallContainer>();
    private static Encoding iso = Encoding.GetEncoding("ISO-8859-1");
    private Encoding ascii = Encoding.GetEncoding(1252);
    private IContainer components = (IContainer) null;
    public Encoding encoding = Encoding.GetEncoding(1252);
    private int LangNum;
    public static string openedfile;
    private System.Collections.Generic.List<string> Menu;
    private ToolStripMenuItem fileToolStripMenuItem;
    private MenuStrip menuStrip1;
    private ToolStripMenuItem openToolStripMenuItem;
    private ToolStripMenuItem saveAslodToolStripMenuItem;
    private OpenFileDialog openFileDialog1;
    private string Path_strItem;
    private ComboBox cbox_Language;
    private CheckedListBox List_CLB;
    private Button Add_B;
    private string Path_itemAll;

    public File2_F() => this.InitializeComponent();

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
      this.saveAslodToolStripMenuItem = new ToolStripMenuItem();
      this.openFileDialog1 = new OpenFileDialog();
      this.cbox_Language = new ComboBox();
      this.List_CLB = new CheckedListBox();
      this.Add_B = new Button();
      this.menuStrip1.SuspendLayout();
      this.SuspendLayout();
      this.menuStrip1.BackColor = SystemColors.ControlLight;
      this.menuStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.fileToolStripMenuItem
      });
      this.menuStrip1.Location = new Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new Size(301, 24);
      this.menuStrip1.TabIndex = 0;
      this.menuStrip1.Text = "menuStrip1";
      this.fileToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[2]
      {
        (ToolStripItem) this.openToolStripMenuItem,
        (ToolStripItem) this.saveAslodToolStripMenuItem
      });
      this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
      this.fileToolStripMenuItem.Size = new Size(37, 20);
      this.fileToolStripMenuItem.Text = "File";
      this.openToolStripMenuItem.Name = "openToolStripMenuItem";
      this.openToolStripMenuItem.Size = new Size(103, 22);
      this.openToolStripMenuItem.Text = "Open";
      this.openToolStripMenuItem.Click += new EventHandler(this.openToolStripMenuItem_Click);
      this.saveAslodToolStripMenuItem.Name = "saveAslodToolStripMenuItem";
      this.saveAslodToolStripMenuItem.Size = new Size(103, 22);
      this.saveAslodToolStripMenuItem.Text = "Save";
      this.openFileDialog1.FileName = "openFileDialog1";
      this.cbox_Language.FormattingEnabled = true;
      this.cbox_Language.Items.AddRange(new object[2]
      {
        (object) "Russian",
        (object) "English"
      });
      this.cbox_Language.Location = new Point(833, 1);
      this.cbox_Language.Name = "cbox_Language";
      this.cbox_Language.Size = new Size(121, 21);
      this.cbox_Language.TabIndex = 111;
      this.List_CLB.FormattingEnabled = true;
      this.List_CLB.Location = new Point(12, 38);
      this.List_CLB.Name = "List_CLB";
      this.List_CLB.Size = new Size(274, 409);
      this.List_CLB.TabIndex = 112;
      this.Add_B.DialogResult = DialogResult.OK;
      this.Add_B.Location = new Point(12, 453);
      this.Add_B.Name = "Add_B";
      this.Add_B.Size = new Size(274, 23);
      this.Add_B.TabIndex = 113;
      this.Add_B.Text = "Add";
      this.Add_B.UseVisualStyleBackColor = true;
      this.Add_B.Click += new EventHandler(this.Add_B_Click);
      this.AutoSizeMode = AutoSizeMode.GrowAndShrink;
      this.ClientSize = new Size(301, 490);
      this.Controls.Add((Control) this.Add_B);
      this.Controls.Add((Control) this.List_CLB);
      this.Controls.Add((Control) this.cbox_Language);
      this.Controls.Add((Control) this.menuStrip1);
      this.FormBorderStyle = FormBorderStyle.FixedSingle;
      this.MainMenuStrip = this.menuStrip1;
      this.MaximizeBox = false;
      this.Name = nameof (File2_F);
      this.Text = "Catalog Editor EP4 - Adding from another file";
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();
    }

    private void openToolStripMenuItem_Click(object sender, EventArgs e)
    {
      OpenFileDialog openFileDialog1 = new OpenFileDialog();
      openFileDialog1.Filter = "catalog|catalog*.lod";
      OpenFileDialog openFileDialog2 = openFileDialog1;
      if (openFileDialog2.ShowDialog() == DialogResult.Cancel)
        return;
      this.List_CLB.Items.Clear();
      File2_F.List.Clear();
      this.FileOpen(openFileDialog2.FileName);
      File2_F.openedfile = openFileDialog2.FileName;
    }

    public void FileOpen(string filename)
    {
      try
      {
        using (BinaryReader binaryReader = new BinaryReader((Stream) File.Open(filename, FileMode.Open)))
        {
          binaryReader.ReadInt32();
          while (binaryReader.BaseStream.Position < binaryReader.BaseStream.Length)
          {
            ItemMallContainer itemMallContainer = new ItemMallContainer();
            int num1 = itemMallContainer.PackID = binaryReader.ReadInt32();
            itemMallContainer.Cat = binaryReader.ReadInt32();
            itemMallContainer.Price = binaryReader.ReadInt32();
            itemMallContainer.data4 = binaryReader.ReadInt32();
            itemMallContainer.data5 = binaryReader.ReadInt32();
            itemMallContainer.Enabled = binaryReader.ReadByte();
            byte[] bytes = itemMallContainer.Name = binaryReader.ReadBytes(binaryReader.ReadInt32());
            itemMallContainer.descr = binaryReader.ReadBytes(binaryReader.ReadInt32());
            int num2 = itemMallContainer.PkgAmount = binaryReader.ReadInt32();
            itemMallContainer.Items = new System.Collections.Generic.List<tMallItem>();
            for (int index = 0; index <= num2 - 1; ++index)
            {
              tMallItem tMallItem = new tMallItem()
              {
                ItemID = binaryReader.ReadInt32(),
                Level = binaryReader.ReadInt32(),
                Plus = binaryReader.ReadInt32(),
                Option = binaryReader.ReadInt32(),
                Amount = binaryReader.ReadInt32()
              };
              itemMallContainer.Items.Add(tMallItem);
            }
            itemMallContainer.ItemIcon = binaryReader.ReadInt32();
            File2_F.List.Add(itemMallContainer);
            this.List_CLB.Items.Add((object) (num1.ToString() + " - " + this.encoding.GetString(bytes)));
          }
          this.List_CLB.SelectedIndex = 0;
        }
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message, "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
    }

    public int GetIDFromList()
    {
      try
      {
        return Convert.ToInt32(this.List_CLB.Text.Split(' ')[0]);
      }
      catch
      {
        return 2;
      }
    }

    private int GetID(string text)
    {
      int result = -1;
      int.TryParse(text.Split(' ')[0], out result);
      return result;
    }

    private void Add_B_Click(object sender, EventArgs e)
    {
      int count = this.List_CLB.CheckedItems.Count;
      for (int index1 = 0; index1 < count; ++index1)
      {
        int PackID = this.GetID(this.List_CLB.Items[this.List_CLB.CheckedIndices[index1]].ToString());
        int index2 = File2_F.List.FindIndex((Predicate<ItemMallContainer>) (p => p.PackID.Equals(PackID)));
        int index3;
        if ((index3 = Form2.MallProducts.FindIndex((Predicate<ItemMallContainer>) (a => a.PackID.Equals(PackID)))) != -1)
          ;
        if (index3 != -1)
          PackID = Form2.MallProducts.Max<ItemMallContainer>((Func<ItemMallContainer, int>) (a => a.PackID)) + 1;
        ItemMallContainer itemMallContainer = new ItemMallContainer();
        itemMallContainer.PackID = PackID;
        itemMallContainer.Cat = File2_F.List[index2].Cat;
        itemMallContainer.Price = File2_F.List[index2].Price;
        itemMallContainer.data4 = File2_F.List[index2].data4;
        itemMallContainer.data5 = File2_F.List[index2].data5;
        itemMallContainer.Enabled = File2_F.List[index2].Enabled;
        itemMallContainer.Name = File2_F.List[index2].Name;
        itemMallContainer.descr = File2_F.List[index2].descr;
        itemMallContainer.PkgAmount = File2_F.List[index2].PkgAmount;
        itemMallContainer.Items = new System.Collections.Generic.List<tMallItem>();
        for (int index4 = 0; index4 <= itemMallContainer.PkgAmount - 1; ++index4)
        {
          tMallItem tMallItem = new tMallItem()
          {
            ItemID = File2_F.List[index2].Items[index4].ItemID,
            Level = File2_F.List[index2].Items[index4].Level,
            Plus = File2_F.List[index2].Items[index4].Plus,
            Option = File2_F.List[index2].Items[index4].Option,
            Amount = File2_F.List[index2].Items[index4].Amount
          };
          itemMallContainer.Items.Add(tMallItem);
        }
        itemMallContainer.ItemIcon = File2_F.List[index2].ItemIcon;
        Form2.MallProducts.Add(itemMallContainer);
      }
    }
  }
}
