// Decompiled with JetBrains decompiler
// Type: SMCEditor3.SmcImportFromItemAll
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using FieryLib.Models;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Windows.Forms;

#nullable disable
namespace SMCEditor3
{
  public class SmcImportFromItemAll : Form
  {
    private IContainer components = (IContainer) null;
    private Button btnUse;
    private List<smcMesh> data;
    private CheckedListBox lbItems;
    public List<tSmcRecords> SMCDATA;
    private TextBox tbSmcFile;
    private TreeView tvSmc;

    public SmcImportFromItemAll()
    {
      this.InitializeComponent();
      this.MakeList();
    }

    private void btnUse_Click(object sender, EventArgs e)
    {
      this.SMCDATA = new List<tSmcRecords>();
      for (int index = 0; index < this.lbItems.CheckedIndices.Count; ++index)
      {
        int id = this.GetID(this.lbItems.Items[this.lbItems.CheckedIndices[index]].ToString());
        if (id != -1)
        {
          string smcPath = this.GetSmcPath(id);
          this.tbSmcFile.Text = smcPath;
          this.SMCDATA.Add(this.ConvertToBin(SMCReader.ReadFile(smcPath), id));
        }
      }
    }

    private tSmcRecords ConvertToBin(List<smcMesh> curData, int ItemID)
    {
      tSmcRecords bin = new tSmcRecords()
      {
        haveData = true,
        ID = ItemID,
        Name = curData[0].meshname,
        Models = new List<tModels>()
      };
      for (int index1 = 0; index1 < curData.Count<smcMesh>(); ++index1)
      {
        tModels tModels = new tModels()
        {
          ModelID = index1 + 1,
          ModelFile = curData[index1].FileName,
          Textures = new List<tTextures>()
        };
        for (int index2 = 0; index2 < curData[index1].Object.Count<smcObject>(); ++index2)
        {
          tTextures tTextures = new tTextures()
          {
            TexID = index2 + 1,
            TextureName = curData[index1].Object[index2].Name,
            TextureFile = curData[index1].Object[index2].Texture
          };
          tModels.Textures.Add(tTextures);
        }
        bin.Models.Add(tModels);
      }
      return bin;
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private int GetID()
    {
      int result = -1;
      try
      {
        int.TryParse(this.lbItems.Text.Split(' ')[0], out result);
      }
      catch
      {
      }
      return result;
    }

    private int GetID(string text)
    {
      int result = -1;
      try
      {
        int.TryParse(text.Split(' ')[0], out result);
      }
      catch
      {
      }
      return result;
    }

    private string GetSmcPath(int ItemID)
    {
      string[] source = Path.GetDirectoryName(Smc.openedFile).Split('\\');
      string smcPath = "";
      bool flag = true;
      for (int index = 0; index < ((IEnumerable<string>) source).Count<string>(); ++index)
      {
        if (source[index].ToUpper() == "DATA")
          flag = false;
        if (flag)
          smcPath = smcPath + source[index] + "\\";
      }
      int index1 = Items.ItemList.FindIndex((Predicate<ItemAllLod>) (p => p.ItemID.Equals(ItemID)));
      if (index1 != -1)
        smcPath += Items.ItemList[index1].SMC;
      return smcPath;
    }

    private void InitializeComponent()
    {
      this.tvSmc = new TreeView();
      this.btnUse = new Button();
      this.tbSmcFile = new TextBox();
      this.lbItems = new CheckedListBox();
      this.SuspendLayout();
      this.tvSmc.Location = new Point(267, 38);
      this.tvSmc.Name = "tvSmc";
      this.tvSmc.Size = new Size(570, 391);
      this.tvSmc.TabIndex = 1;
      this.btnUse.DialogResult = DialogResult.OK;
      this.btnUse.Location = new Point(267, 433);
      this.btnUse.Name = "btnUse";
      this.btnUse.Size = new Size(570, 23);
      this.btnUse.TabIndex = 2;
      this.btnUse.Text = "Add to SMC";
      this.btnUse.UseVisualStyleBackColor = true;
      this.btnUse.Click += new EventHandler(this.btnUse_Click);
      this.tbSmcFile.BorderStyle = BorderStyle.FixedSingle;
      this.tbSmcFile.Location = new Point(267, 12);
      this.tbSmcFile.Name = "tbSmcFile";
      this.tbSmcFile.Size = new Size(570, 20);
      this.tbSmcFile.TabIndex = 3;
      this.lbItems.FormattingEnabled = true;
      this.lbItems.Location = new Point(12, 12);
      this.lbItems.Name = "lbItems";
      this.lbItems.Size = new Size(249, 439);
      this.lbItems.TabIndex = 4;
      this.lbItems.SelectedIndexChanged += new EventHandler(this.lbItems_SelectedIndexChanged);
      this.ClientSize = new Size(849, 468);
      this.Controls.Add((Control) this.lbItems);
      this.Controls.Add((Control) this.tbSmcFile);
      this.Controls.Add((Control) this.btnUse);
      this.Controls.Add((Control) this.tvSmc);
      this.Name = nameof (SmcImportFromItemAll);
      this.Text = "SMC from the ItemAll file";
      this.ResumeLayout(false);
      this.PerformLayout();
    }

    private void lbItems_SelectedIndexChanged(object sender, EventArgs e)
    {
      string smcPath = this.GetSmcPath(this.GetID());
      this.tbSmcFile.Text = smcPath;
      this.data = SMCReader.ReadFile(smcPath);
      this.MakeTree(this.data);
    }

    private void MakeList()
    {
      this.lbItems.Items.Clear();
      foreach (StrModel strModel in Items.NameItem)
        this.lbItems.Items.Add((object) (strModel.m_index.ToString() + " - " + strModel.m_name));
    }

    private void MakeTree(List<smcMesh> data)
    {
      this.tvSmc.Nodes.Clear();
      for (int index1 = 0; index1 < data.Count<smcMesh>(); ++index1)
      {
        this.tvSmc.Nodes.Add(data[index1].FileName);
        for (int index2 = 0; index2 < data[index1].Object.Count<smcObject>(); ++index2)
        {
          smcObject smcObject = data[index1].Object[index2];
          this.tvSmc.Nodes[index1].Nodes.Add(smcObject.Name + " : " + smcObject.Texture);
        }
      }
      this.tvSmc.ExpandAll();
    }
  }
}
