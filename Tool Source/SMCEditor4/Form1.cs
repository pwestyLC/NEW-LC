// Decompiled with JetBrains decompiler
// Type: SMCEditor3.Form1
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using FieryLib.Models;
using LcDevPack_TeamDamonA;
using Microsoft.Win32;
using MySqlConnector;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;

#nullable disable
namespace SMCEditor3
{
  public class Form1 : Form
  {
    private Encoding encoding = Encoding.GetEncoding("windows-874");
    private IContainer components = (IContainer) null;
    private Button btnAdd;
    private Button btnDelete;
    private Button btnModAdd;
    private Button btnModDelete;
    private Button btnSaveRecord;
    private Button btnTexAdd;
    private Button btnTexDelete;
    private DataGridViewTextBoxColumn colModFile;
    private DataGridViewTextBoxColumn colModID;
    private DataGridViewTextBoxColumn colTexFile;
    private DataGridViewTextBoxColumn colTexID;
    private DataGridViewTextBoxColumn colTexName;
    private DataGridView dgModel;
    private DataGridView dgTexture;
    private ToolStripMenuItem fileToolStripMenuItem;
    private GroupBox groupBox1;
    private GroupBox groupBox2;
    private Label label1;
    private Label label2;
    private Label label3;
    private ListBox lbList;
    private MenuStrip menuStrip1;
    private OpenFileDialog ofd;
    private static string openedFile;
    private ToolStripMenuItem openToolStripMenuItem;
    private ToolStripMenuItem quitToolStripMenuItem;
    private ToolStripMenuItem saveAsToolStripMenuItem;
    private ToolStripMenuItem saveToolStripMenuItem;
    private SaveFileDialog sfd;
    private SplitContainer splitContainer1;
    private SplitContainer splitContainer2;
    private SplitContainer splitContainer3;
    private ToolStripStatusLabel status;
    private StatusStrip statusStrip1;
    private TextBox tbItemID;
    private TextBox tbModelName;
    private TextBox tbSearch;
    private ToolStripMenuItem loadFromDatabaseToolStripMenuItem;
    private ToolStripSeparator toolStripSeparator1;
    private ToolStripSeparator toolStripSeparator2;
    private ToolStripSeparator toolStripSeparator3;

    public Form1() => this.InitializeComponent();

    private void btnAdd_Click(object sender, EventArgs e)
    {
      SmcImportFromItemAll importFromItemAll = new SmcImportFromItemAll();
      if (importFromItemAll.ShowDialog() == DialogResult.OK)
      {
        foreach (tSmcRecords tSmcRecords in importFromItemAll.SMCDATA)
        {
          tSmcRecords sr = tSmcRecords;
          int index = Smc.SMCFile.FindIndex((Predicate<tSmcRecords>) (p => p.ID.Equals(sr.ID)));
          if (index != -1)
            Smc.SMCFile[index] = sr;
          else
            Smc.SMCFile.Add(sr);
        }
        this.RefreshAll();
      }
      this.UpdateList();
    }

    private void btnDelete_Click(object sender, EventArgs e)
    {
      int ItemID = this.GetId();
      int index = Smc.SMCFile.FindIndex((Predicate<tSmcRecords>) (p => p.ID.Equals(ItemID)));
      if (index == -1)
        return;
      Smc.SMCFile.RemoveAt(index);
      this.RefreshAll();
    }

    private void btnModAdd_Click(object sender, EventArgs e)
    {
      int ItemID = this.GetId();
      int index = Smc.SMCFile.FindIndex((Predicate<tSmcRecords>) (p => p.ID.Equals(ItemID)));
      if (index == -1)
        return;
      tModels tModels = new tModels()
      {
        Textures = new List<tTextures>(),
        ModelID = Smc.SMCFile[index].Models.Max<tModels>((Func<tModels, int>) (p => p.ModelID)) + 1,
        ModelFile = "(new model)"
      };
      Smc.SMCFile[index].Models.Add(tModels);
      this.dgModel.Rows.Add((object) tModels.ModelID, (object) tModels.ModelFile);
    }

    private void btnModDelete_Click(object sender, EventArgs e)
    {
      if (this.dgModel.SelectedCells.Count <= 0)
        return;
      int rowIndex = this.dgModel.SelectedCells[0].RowIndex;
      int ModelID = Convert.ToInt32(this.dgModel.Rows[rowIndex].Cells["colModID"].Value);
      int ItemID = this.GetId();
      int index = Smc.SMCFile.FindIndex((Predicate<tSmcRecords>) (p => p.ID.Equals(ItemID)));
      if (index == -1)
        return;
      this.dgModel.Rows.RemoveAt(rowIndex);
      Smc.SMCFile[index].Models.RemoveAll((Predicate<tModels>) (p => p.ModelID.Equals(ModelID)));
    }

    private void btnReRead_Click(object sender, EventArgs e)
    {
      int ItemID = this.GetId();
      int index = Smc.SMCFile.FindIndex((Predicate<tSmcRecords>) (p => p.ID.Equals(ItemID)));
      if (index == -1)
        return;
      tSmcRecords tSmcRecords = Smc.SMCFile[index];
    }

    private void btnSaveRecord_Click(object sender, EventArgs e)
    {
      int ItemID = this.GetId();
      int index = Smc.SMCFile.FindIndex((Predicate<tSmcRecords>) (p => p.ID.Equals(ItemID)));
      if (index == -1)
        return;
      Smc.SMCFile[index].ID = Convert.ToInt32(this.tbItemID.Text);
      Smc.SMCFile[index].Name = this.tbModelName.Text;
    }

    private void btnTexAdd_Click(object sender, EventArgs e)
    {
      if (this.dgModel.SelectedCells.Count <= 0)
        return;
      int ModelID = Convert.ToInt32(this.dgModel.Rows[this.dgModel.SelectedCells[0].RowIndex].Cells["colModID"].Value);
      int ItemID = this.GetId();
      int index1 = Smc.SMCFile.FindIndex((Predicate<tSmcRecords>) (p => p.ID.Equals(ItemID)));
      if (index1 == -1)
        return;
      int index2 = Smc.SMCFile[index1].Models.FindIndex((Predicate<tModels>) (p => p.ModelID.Equals(ModelID)));
      if (index2 == -1)
        return;
      tTextures tTextures = new tTextures()
      {
        TexID = Smc.SMCFile[index1].Models[index2].Textures.Max<tTextures>((Func<tTextures, int>) (p => p.TexID)) + 1,
        TextureName = "(New Name)",
        TextureFile = "New File)"
      };
      Smc.SMCFile[index1].Models[index2].Textures.Add(tTextures);
      this.dgTexture.Rows.Add((object) tTextures.TexID, (object) tTextures.TextureName, (object) tTextures.TextureFile);
    }

    private void btnTexDelete_Click(object sender, EventArgs e)
    {
      if (this.dgModel.SelectedCells.Count <= 0)
        return;
      int ModelID = Convert.ToInt32(this.dgModel.Rows[this.dgModel.SelectedCells[0].RowIndex].Cells["colModID"].Value);
      int ItemID = this.GetId();
      if (this.dgTexture.SelectedCells.Count <= 0)
        return;
      int rowIndex = this.dgTexture.SelectedCells[0].RowIndex;
      int TexID = Convert.ToInt32(this.dgTexture.Rows[rowIndex].Cells["colTexID"].Value);
      int index1 = Smc.SMCFile.FindIndex((Predicate<tSmcRecords>) (p => p.ID.Equals(ItemID)));
      if (index1 == -1)
        return;
      int index2 = Smc.SMCFile[index1].Models.FindIndex((Predicate<tModels>) (p => p.ModelID.Equals(ModelID)));
      if (index2 == -1)
        return;
      this.dgTexture.Rows.RemoveAt(rowIndex);
      Smc.SMCFile[index1].Models[index2].Textures.RemoveAll((Predicate<tTextures>) (p => p.TexID.Equals(TexID)));
    }

    private void copyRecordsFromOtherFileToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (this.ofd.ShowDialog() != DialogResult.OK)
        return;
      RecordSelector recordSelector = new RecordSelector(this.ofd.FileName);
      if (recordSelector.ShowDialog() != DialogResult.OK)
        return;
      tSmcRecords[] tmp = recordSelector.Records;
      for (int i = 0; i < ((IEnumerable<tSmcRecords>) tmp).Count<tSmcRecords>(); i++)
      {
        Predicate<tSmcRecords> match = (Predicate<tSmcRecords>) (p => p.ID.Equals(tmp[i].ID));
        if (Smc.SMCFile.FindIndex(match) == -1)
          Smc.SMCFile.Add((tSmcRecords) tmp[i].Clone());
      }
      this.RefreshAll();
    }

    private void dgModel_CellEndEdit(object sender, DataGridViewCellEventArgs e)
    {
      if (this.dgModel.SelectedCells.Count <= 0)
        return;
      int rowIndex = this.dgModel.SelectedCells[0].RowIndex;
      int ModelID = Convert.ToInt32(this.dgModel.Rows[rowIndex].Cells["colModID"].Value);
      int ItemID = this.GetId();
      int index1 = Smc.SMCFile.FindIndex((Predicate<tSmcRecords>) (p => p.ID.Equals(ItemID)));
      if (index1 == -1)
        return;
      int index2 = Smc.SMCFile[index1].Models.FindIndex((Predicate<tModels>) (p => p.ModelID.Equals(ModelID)));
      if (index2 != -1)
        Smc.SMCFile[index1].Models[index2].ModelFile = this.dgModel.Rows[rowIndex].Cells["colModFile"].Value.ToString();
    }

    private void dgModel_SelectionChanged(object sender, EventArgs e)
    {
      if (this.dgModel.SelectedCells.Count <= 0)
        return;
      this.GetTexGrid(this.GetId(), Convert.ToInt32(this.dgModel.Rows[this.dgModel.SelectedCells[0].RowIndex].Cells["colModID"].Value));
    }

    private void dgTexture_CellEndEdit(object sender, DataGridViewCellEventArgs e)
    {
      if (this.dgModel.SelectedCells.Count <= 0)
        return;
      int ModelID = Convert.ToInt32(this.dgModel.Rows[this.dgModel.SelectedCells[0].RowIndex].Cells["colModID"].Value);
      int ItemID = this.GetId();
      if (this.dgTexture.SelectedCells.Count <= 0)
        return;
      int rowIndex = this.dgTexture.SelectedCells[0].RowIndex;
      int TexID = Convert.ToInt32(this.dgTexture.Rows[rowIndex].Cells["colTexID"].Value);
      int index1 = Smc.SMCFile.FindIndex((Predicate<tSmcRecords>) (p => p.ID.Equals(ItemID)));
      if (index1 == -1)
        return;
      int index2 = Smc.SMCFile[index1].Models.FindIndex((Predicate<tModels>) (p => p.ModelID.Equals(ModelID)));
      if (index2 == -1)
        return;
      int index3 = Smc.SMCFile[index1].Models[index2].Textures.FindIndex((Predicate<tTextures>) (p => p.TexID.Equals(TexID)));
      if (index3 != -1)
      {
        Smc.SMCFile[index1].Models[index2].Textures[index3].TextureFile = this.dgTexture.Rows[rowIndex].Cells["colTexFile"].Value.ToString();
        Smc.SMCFile[index1].Models[index2].Textures[index3].TextureName = this.dgTexture.Rows[rowIndex].Cells["colTexName"].Value.ToString();
      }
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private int GetId()
    {
      int result = -1;
      int.TryParse(this.lbList.Text.Split(' ')[0], out result);
      return result;
    }

    private void GetTexGrid(int ItemID, int ModelID)
    {
      int index1 = Smc.SMCFile.FindIndex((Predicate<tSmcRecords>) (p => p.ID.Equals(ItemID)));
      if (index1 == -1)
        return;
      tSmcRecords tSmcRecords = Smc.SMCFile[index1];
      int index2 = tSmcRecords.Models.FindIndex((Predicate<tModels>) (p => p.ModelID.Equals(ModelID)));
      if (index2 == -1)
        return;
      tModels model = tSmcRecords.Models[index2];
      this.dgTexture.Rows.Clear();
      for (int index3 = 0; index3 < model.Textures.Count<tTextures>(); ++index3)
      {
        tTextures texture = model.Textures[index3];
        this.dgTexture.Rows.Add((object) texture.TexID, (object) texture.TextureName, (object) texture.TextureFile);
      }
    }

    private void InitializeComponent()
    {
      this.menuStrip1 = new MenuStrip();
      this.fileToolStripMenuItem = new ToolStripMenuItem();
      this.openToolStripMenuItem = new ToolStripMenuItem();
      this.toolStripSeparator1 = new ToolStripSeparator();
      this.saveToolStripMenuItem = new ToolStripMenuItem();
      this.saveAsToolStripMenuItem = new ToolStripMenuItem();
      this.toolStripSeparator2 = new ToolStripSeparator();
      this.quitToolStripMenuItem = new ToolStripMenuItem();
      this.loadFromDatabaseToolStripMenuItem = new ToolStripMenuItem();
      this.toolStripSeparator3 = new ToolStripSeparator();
      this.statusStrip1 = new StatusStrip();
      this.status = new ToolStripStatusLabel();
      this.splitContainer1 = new SplitContainer();
      this.splitContainer2 = new SplitContainer();
      this.tbSearch = new TextBox();
      this.label1 = new Label();
      this.splitContainer3 = new SplitContainer();
      this.lbList = new ListBox();
      this.btnDelete = new Button();
      this.btnAdd = new Button();
      this.btnSaveRecord = new Button();
      this.groupBox2 = new GroupBox();
      this.dgTexture = new DataGridView();
      this.colTexID = new DataGridViewTextBoxColumn();
      this.colTexName = new DataGridViewTextBoxColumn();
      this.colTexFile = new DataGridViewTextBoxColumn();
      this.groupBox1 = new GroupBox();
      this.dgModel = new DataGridView();
      this.colModID = new DataGridViewTextBoxColumn();
      this.colModFile = new DataGridViewTextBoxColumn();
      this.btnTexDelete = new Button();
      this.btnTexAdd = new Button();
      this.btnModDelete = new Button();
      this.btnModAdd = new Button();
      this.tbModelName = new TextBox();
      this.label3 = new Label();
      this.tbItemID = new TextBox();
      this.label2 = new Label();
      this.ofd = new OpenFileDialog();
      this.sfd = new SaveFileDialog();
      this.menuStrip1.SuspendLayout();
      this.statusStrip1.SuspendLayout();
      this.splitContainer1.BeginInit();
      this.splitContainer1.Panel1.SuspendLayout();
      this.splitContainer1.Panel2.SuspendLayout();
      this.splitContainer1.SuspendLayout();
      this.splitContainer2.BeginInit();
      this.splitContainer2.Panel1.SuspendLayout();
      this.splitContainer2.Panel2.SuspendLayout();
      this.splitContainer2.SuspendLayout();
      this.splitContainer3.BeginInit();
      this.splitContainer3.Panel1.SuspendLayout();
      this.splitContainer3.Panel2.SuspendLayout();
      this.splitContainer3.SuspendLayout();
      this.groupBox2.SuspendLayout();
      ((ISupportInitialize) this.dgTexture).BeginInit();
      this.groupBox1.SuspendLayout();
      ((ISupportInitialize) this.dgModel).BeginInit();
      this.SuspendLayout();
      this.menuStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.fileToolStripMenuItem
      });
      this.menuStrip1.Location = new Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new Size(819, 24);
      this.menuStrip1.TabIndex = 0;
      this.menuStrip1.Text = "menuStrip1";
      this.fileToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[8]
      {
        (ToolStripItem) this.openToolStripMenuItem,
        (ToolStripItem) this.loadFromDatabaseToolStripMenuItem,
        (ToolStripItem) this.toolStripSeparator1,
        (ToolStripItem) this.saveToolStripMenuItem,
        (ToolStripItem) this.saveAsToolStripMenuItem,
        (ToolStripItem) this.toolStripSeparator2,
        (ToolStripItem) this.quitToolStripMenuItem,
        (ToolStripItem) this.toolStripSeparator3
      });
      this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
      this.fileToolStripMenuItem.Size = new Size(37, 20);
      this.fileToolStripMenuItem.Text = "File";
      this.openToolStripMenuItem.Name = "openToolStripMenuItem";
      this.openToolStripMenuItem.Size = new Size(112, 22);
      this.openToolStripMenuItem.Text = "Open";
      this.openToolStripMenuItem.Click += new EventHandler(this.openToolStripMenuItem_Click);
      this.loadFromDatabaseToolStripMenuItem.Name = "loadFromDatabaseToolStripMenuItem";
      this.loadFromDatabaseToolStripMenuItem.Size = new Size(112, 22);
      this.loadFromDatabaseToolStripMenuItem.Text = "Load from Database";
      this.loadFromDatabaseToolStripMenuItem.Click += new EventHandler(this.loadFromDatabaseToolStripMenuItem_Click);
      this.toolStripSeparator3.Name = "toolStripSeparator3";
      this.toolStripSeparator3.Size = new Size(109, 6);
      this.toolStripSeparator1.Name = "toolStripSeparator1";
      this.toolStripSeparator1.Size = new Size(109, 6);
      this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
      this.saveToolStripMenuItem.Size = new Size(112, 22);
      this.saveToolStripMenuItem.Text = "Save";
      this.saveToolStripMenuItem.Click += new EventHandler(this.saveToolStripMenuItem_Click);
      this.saveAsToolStripMenuItem.Name = "saveAsToolStripMenuItem";
      this.saveAsToolStripMenuItem.Size = new Size(112, 22);
      this.saveAsToolStripMenuItem.Text = "Save as";
      this.saveAsToolStripMenuItem.Click += new EventHandler(this.saveAsToolStripMenuItem_Click);
      this.toolStripSeparator2.Name = "toolStripSeparator2";
      this.toolStripSeparator2.Size = new Size(109, 6);
      this.quitToolStripMenuItem.Name = "quitToolStripMenuItem";
      this.quitToolStripMenuItem.Size = new Size(112, 22);
      this.quitToolStripMenuItem.Text = "Exit";
      this.statusStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.status
      });
      this.statusStrip1.Location = new Point(0, 497);
      this.statusStrip1.Name = "statusStrip1";
      this.statusStrip1.Size = new Size(819, 22);
      this.statusStrip1.TabIndex = 1;
      this.statusStrip1.Text = "statusStrip1";
      this.status.Name = "status";
      this.status.Size = new Size(0, 17);
      this.splitContainer1.Dock = DockStyle.Fill;
      this.splitContainer1.FixedPanel = FixedPanel.Panel1;
      this.splitContainer1.IsSplitterFixed = true;
      this.splitContainer1.Location = new Point(0, 24);
      this.splitContainer1.Name = "splitContainer1";
      this.splitContainer1.Panel1.Controls.Add((Control) this.splitContainer2);
      this.splitContainer1.Panel2.Controls.Add((Control) this.btnSaveRecord);
      this.splitContainer1.Panel2.Controls.Add((Control) this.groupBox2);
      this.splitContainer1.Panel2.Controls.Add((Control) this.groupBox1);
      this.splitContainer1.Panel2.Controls.Add((Control) this.btnTexDelete);
      this.splitContainer1.Panel2.Controls.Add((Control) this.btnTexAdd);
      this.splitContainer1.Panel2.Controls.Add((Control) this.btnModDelete);
      this.splitContainer1.Panel2.Controls.Add((Control) this.btnModAdd);
      this.splitContainer1.Panel2.Controls.Add((Control) this.tbModelName);
      this.splitContainer1.Panel2.Controls.Add((Control) this.label3);
      this.splitContainer1.Panel2.Controls.Add((Control) this.tbItemID);
      this.splitContainer1.Panel2.Controls.Add((Control) this.label2);
      this.splitContainer1.Size = new Size(819, 473);
      this.splitContainer1.SplitterDistance = 261;
      this.splitContainer1.TabIndex = 2;
      this.splitContainer2.Dock = DockStyle.Fill;
      this.splitContainer2.FixedPanel = FixedPanel.Panel1;
      this.splitContainer2.IsSplitterFixed = true;
      this.splitContainer2.Location = new Point(0, 0);
      this.splitContainer2.Name = "splitContainer2";
      this.splitContainer2.Orientation = Orientation.Horizontal;
      this.splitContainer2.Panel1.Controls.Add((Control) this.tbSearch);
      this.splitContainer2.Panel1.Controls.Add((Control) this.label1);
      this.splitContainer2.Panel2.Controls.Add((Control) this.splitContainer3);
      this.splitContainer2.Size = new Size(261, 473);
      this.splitContainer2.SplitterDistance = 29;
      this.splitContainer2.TabIndex = 0;
      this.tbSearch.BorderStyle = BorderStyle.FixedSingle;
      this.tbSearch.Location = new Point(54, 5);
      this.tbSearch.Name = "tbSearch";
      this.tbSearch.Size = new Size(207, 20);
      this.tbSearch.TabIndex = 1;
      this.tbSearch.TextChanged += new EventHandler(this.tbSearch_TextChanged);
      this.label1.AutoSize = true;
      this.label1.Location = new Point(7, 7);
      this.label1.Name = "label1";
      this.label1.Size = new Size(27, 13);
      this.label1.TabIndex = 0;
      this.label1.Text = "Find";
      this.splitContainer3.Dock = DockStyle.Fill;
      this.splitContainer3.FixedPanel = FixedPanel.Panel2;
      this.splitContainer3.IsSplitterFixed = true;
      this.splitContainer3.Location = new Point(0, 0);
      this.splitContainer3.Name = "splitContainer3";
      this.splitContainer3.Orientation = Orientation.Horizontal;
      this.splitContainer3.Panel1.Controls.Add((Control) this.lbList);
      this.splitContainer3.Panel1.Padding = new Padding(10, 0, 0, 0);
      this.splitContainer3.Panel2.Controls.Add((Control) this.btnDelete);
      this.splitContainer3.Panel2.Controls.Add((Control) this.btnAdd);
      this.splitContainer3.Size = new Size(261, 440);
      this.splitContainer3.SplitterDistance = 401;
      this.splitContainer3.TabIndex = 0;
      this.lbList.Dock = DockStyle.Fill;
      this.lbList.FormattingEnabled = true;
      this.lbList.Location = new Point(10, 0);
      this.lbList.Name = "lbList";
      this.lbList.Size = new Size(251, 401);
      this.lbList.TabIndex = 0;
      this.lbList.SelectedIndexChanged += new EventHandler(this.lbList_SelectedIndexChanged);
      this.btnDelete.Location = new Point(141, 3);
      this.btnDelete.Name = "btnDelete";
      this.btnDelete.Size = new Size(120, 23);
      this.btnDelete.TabIndex = 1;
      this.btnDelete.Text = "Delete Item";
      this.btnDelete.UseVisualStyleBackColor = true;
      this.btnDelete.Click += new EventHandler(this.btnDelete_Click);
      this.btnAdd.Location = new Point(10, 3);
      this.btnAdd.Name = "btnAdd";
      this.btnAdd.Size = new Size(120, 23);
      this.btnAdd.TabIndex = 0;
      this.btnAdd.Text = "Add Item";
      this.btnAdd.UseVisualStyleBackColor = true;
      this.btnAdd.Click += new EventHandler(this.btnAdd_Click);
      this.btnSaveRecord.Location = new Point(466, 436);
      this.btnSaveRecord.Name = "btnSaveRecord";
      this.btnSaveRecord.Size = new Size(75, 23);
      this.btnSaveRecord.TabIndex = 14;
      this.btnSaveRecord.Text = "Save";
      this.btnSaveRecord.UseVisualStyleBackColor = true;
      this.btnSaveRecord.Click += new EventHandler(this.btnSaveRecord_Click);
      this.groupBox2.Controls.Add((Control) this.dgTexture);
      this.groupBox2.Location = new Point(19, 264);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new Size(523, 168);
      this.groupBox2.TabIndex = 13;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "Texture";
      this.dgTexture.AllowUserToAddRows = false;
      this.dgTexture.AllowUserToDeleteRows = false;
      this.dgTexture.BackgroundColor = SystemColors.Control;
      this.dgTexture.BorderStyle = BorderStyle.None;
      this.dgTexture.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dgTexture.Columns.AddRange((DataGridViewColumn) this.colTexID, (DataGridViewColumn) this.colTexName, (DataGridViewColumn) this.colTexFile);
      this.dgTexture.Dock = DockStyle.Fill;
      this.dgTexture.EnableHeadersVisualStyles = false;
      this.dgTexture.Location = new Point(3, 16);
      this.dgTexture.Name = "dgTexture";
      this.dgTexture.RowHeadersVisible = false;
      this.dgTexture.Size = new Size(517, 149);
      this.dgTexture.TabIndex = 7;
      this.dgTexture.CellEndEdit += new DataGridViewCellEventHandler(this.dgTexture_CellEndEdit);
      this.colTexID.HeaderText = "ID";
      this.colTexID.Name = "colTexID";
      this.colTexID.Width = 50;
      this.colTexName.HeaderText = "Name";
      this.colTexName.Name = "colTexName";
      this.colTexName.Width = 150;
      this.colTexFile.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
      this.colTexFile.HeaderText = "Pacth Of File";
      this.colTexFile.Name = "colTexFile";
      this.groupBox1.Controls.Add((Control) this.dgModel);
      this.groupBox1.Location = new Point(19, 38);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(523, 160);
      this.groupBox1.TabIndex = 12;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Models";
      this.dgModel.AllowUserToAddRows = false;
      this.dgModel.AllowUserToDeleteRows = false;
      this.dgModel.BackgroundColor = SystemColors.Control;
      this.dgModel.BorderStyle = BorderStyle.None;
      this.dgModel.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dgModel.Columns.AddRange((DataGridViewColumn) this.colModID, (DataGridViewColumn) this.colModFile);
      this.dgModel.Dock = DockStyle.Fill;
      this.dgModel.EnableHeadersVisualStyles = false;
      this.dgModel.Location = new Point(3, 16);
      this.dgModel.Name = "dgModel";
      this.dgModel.RowHeadersVisible = false;
      this.dgModel.Size = new Size(517, 141);
      this.dgModel.TabIndex = 6;
      this.dgModel.CellEndEdit += new DataGridViewCellEventHandler(this.dgModel_CellEndEdit);
      this.dgModel.SelectionChanged += new EventHandler(this.dgModel_SelectionChanged);
      this.colModID.HeaderText = "ID";
      this.colModID.Name = "colModID";
      this.colModID.Width = 50;
      this.colModFile.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
      this.colModFile.HeaderText = "Pacth Of File";
      this.colModFile.Name = "colModFile";
      this.btnTexDelete.Location = new Point(101, 438);
      this.btnTexDelete.Name = "btnTexDelete";
      this.btnTexDelete.Size = new Size(75, 23);
      this.btnTexDelete.TabIndex = 11;
      this.btnTexDelete.Text = "Delete";
      this.btnTexDelete.UseVisualStyleBackColor = true;
      this.btnTexDelete.Click += new EventHandler(this.btnTexDelete_Click);
      this.btnTexAdd.Location = new Point(20, 438);
      this.btnTexAdd.Name = "btnTexAdd";
      this.btnTexAdd.Size = new Size(75, 23);
      this.btnTexAdd.TabIndex = 10;
      this.btnTexAdd.Text = "Add";
      this.btnTexAdd.UseVisualStyleBackColor = true;
      this.btnTexAdd.Click += new EventHandler(this.btnTexAdd_Click);
      this.btnModDelete.Location = new Point(101, 204);
      this.btnModDelete.Name = "btnModDelete";
      this.btnModDelete.Size = new Size(75, 23);
      this.btnModDelete.TabIndex = 9;
      this.btnModDelete.Text = "Delete";
      this.btnModDelete.UseVisualStyleBackColor = true;
      this.btnModDelete.Click += new EventHandler(this.btnModDelete_Click);
      this.btnModAdd.Location = new Point(19, 204);
      this.btnModAdd.Name = "btnModAdd";
      this.btnModAdd.Size = new Size(75, 23);
      this.btnModAdd.TabIndex = 8;
      this.btnModAdd.Text = "Add";
      this.btnModAdd.UseVisualStyleBackColor = true;
      this.btnModAdd.Click += new EventHandler(this.btnModAdd_Click);
      this.tbModelName.BorderStyle = BorderStyle.FixedSingle;
      this.tbModelName.Location = new Point(233, 5);
      this.tbModelName.Name = "tbModelName";
      this.tbModelName.Size = new Size(309, 20);
      this.tbModelName.TabIndex = 5;
      this.label3.AutoSize = true;
      this.label3.Location = new Point(160, 7);
      this.label3.Name = "label3";
      this.label3.Size = new Size(36, 13);
      this.label3.TabIndex = 4;
      this.label3.Text = "Model";
      this.tbItemID.BorderStyle = BorderStyle.FixedSingle;
      this.tbItemID.Location = new Point(60, 5);
      this.tbItemID.Name = "tbItemID";
      this.tbItemID.Size = new Size(69, 20);
      this.tbItemID.TabIndex = 3;
      this.label2.AutoSize = true;
      this.label2.Location = new Point(16, 7);
      this.label2.Name = "label2";
      this.label2.Size = new Size(38, 13);
      this.label2.TabIndex = 2;
      this.label2.Text = "ItemID";
      this.ofd.Filter = "|SMC.lod|smc.lod|.lod|All Files|*.*";
      this.sfd.DefaultExt = "lod";
      this.ClientSize = new Size(819, 519);
      this.Controls.Add((Control) this.splitContainer1);
      this.Controls.Add((Control) this.statusStrip1);
      this.Controls.Add((Control) this.menuStrip1);
      this.FormBorderStyle = FormBorderStyle.FixedToolWindow;
      this.MainMenuStrip = this.menuStrip1;
      this.Name = nameof (Form1);
      this.Text = "LastChaos SMC Editor By FieryGame";
      this.Load += new EventHandler(this.Form1_Load);
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.statusStrip1.ResumeLayout(false);
      this.statusStrip1.PerformLayout();
      this.splitContainer1.Panel1.ResumeLayout(false);
      this.splitContainer1.Panel2.ResumeLayout(false);
      this.splitContainer1.Panel2.PerformLayout();
      this.splitContainer1.EndInit();
      this.splitContainer1.ResumeLayout(false);
      this.splitContainer2.Panel1.ResumeLayout(false);
      this.splitContainer2.Panel1.PerformLayout();
      this.splitContainer2.Panel2.ResumeLayout(false);
      this.splitContainer2.EndInit();
      this.splitContainer2.ResumeLayout(false);
      this.splitContainer3.Panel1.ResumeLayout(false);
      this.splitContainer3.Panel2.ResumeLayout(false);
      this.splitContainer3.EndInit();
      this.splitContainer3.ResumeLayout(false);
      this.groupBox2.ResumeLayout(false);
      ((ISupportInitialize) this.dgTexture).EndInit();
      this.groupBox1.ResumeLayout(false);
      ((ISupportInitialize) this.dgModel).EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();
    }

    private void lbList_SelectedIndexChanged(object sender, EventArgs e) => this.ViewRecord();

    public void MakeList()
    {
    }

    private void openToolStripMenuItem_Click(object sender, EventArgs e)
    {
      string FileName = "";
      string str = "";
      OpenFileDialog openFileDialog1 = new OpenFileDialog();
      openFileDialog1.Title = "[R]Opening File itemAll";
      openFileDialog1.FileName = "itemAll.lod";
      openFileDialog1.Filter = "FileOption (itemAll.lod)|itemAll.lod";
      this.ofd = openFileDialog1;
      if (this.ofd.ShowDialog() == DialogResult.OK)
        FileName = this.ofd.FileName;
      OpenFileDialog openFileDialog2 = new OpenFileDialog();
      openFileDialog2.Title = "[R]Opening File smc";
      openFileDialog2.FileName = "smc.lod";
      openFileDialog2.Filter = "FileOption (smc.lod)|smc.lod";
      this.ofd = openFileDialog2;
      if (this.ofd.ShowDialog() == DialogResult.OK)
      {
        Form1.openedFile = this.ofd.FileName;
        str = this.ofd.FileName;
      }
      OpenFileDialog openFileDialog3 = new OpenFileDialog();
      openFileDialog3.Title = "[R]Opening File item Name";
      openFileDialog3.FileName = "strItem_us.lod";
      openFileDialog3.Filter = "strItem*|strItem*.*|lod|*.lod|data|*.data|All|*.*";
      this.ofd = openFileDialog3;
      if (this.ofd.ShowDialog() != DialogResult.OK)
        return;
      string fileName = this.ofd.FileName;
      Smc.ReadFile(str);
      Items.LoadFromFile(FileName, fileName, str);
    }

    private void RefreshAll()
    {
      Smc.Menu.Clear();
      Smc.MakeList();
      this.MakeList();
    }

    private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (this.sfd.ShowDialog() != DialogResult.OK)
        return;
      if (Smc.WriteFile(this.sfd.FileName))
      {
        int num1 = (int) MessageBox.Show("Save Success!");
      }
      else
      {
        int num2 = (int) MessageBox.Show("Error saving file");
      }
    }

    private void saveToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (Smc.WriteFile(Form1.openedFile))
      {
        int num1 = (int) MessageBox.Show("Save Success!");
      }
      else
      {
        int num2 = (int) MessageBox.Show("Error saving file");
      }
    }

    public bool SearchString(string s) => s.ToUpper().Contains(this.tbSearch.Text.ToUpper());

    private void tbSearch_TextChanged(object sender, EventArgs e) => this.MakeList();

    private void ViewRecord()
    {
      int ItemID = this.GetId();
      int index1 = Smc.SMCFile.FindIndex((Predicate<tSmcRecords>) (p => p.ID.Equals(ItemID)));
      if (index1 == -1)
        return;
      tSmcRecords tSmcRecords = Smc.SMCFile[index1];
      this.tbItemID.Text = tSmcRecords.ID.ToString();
      this.tbModelName.Text = tSmcRecords.Name;
      this.dgModel.Rows.Clear();
      for (int index2 = 0; index2 < tSmcRecords.Models.Count<tModels>(); ++index2)
        this.dgModel.Rows.Add((object) tSmcRecords.Models[index2].ModelID, (object) tSmcRecords.Models[index2].ModelFile);
    }

    private void Form1_Load(object sender, EventArgs e)
    {
      try
      {
        RegistryKey registryKey = Registry.CurrentUser.OpenSubKey("[R]Developer").OpenSubKey("SMCLC");
        if ((string) registryKey.GetValue("Path") != "" && (string) registryKey.GetValue("PathName") != "" && (string) registryKey.GetValue("PathSMC") != "")
        {
          Smc.openedFile = (string) registryKey.GetValue("PathSMC");
          Smc.ReadFile(Smc.openedFile);
          Items.LoadFromFile((string) registryKey.GetValue("Path"), (string) registryKey.GetValue("PathName"), (string) registryKey.GetValue("PathSMC"));
          Form1.openedFile = (string) registryKey.GetValue("PathSMC");
          this.UpdateList();
          this.status.Text = "Automatic file Link";
        }
        else
          this.status.Text = "The paths to automatically open files are not listed";
      }
      catch (Exception ex)
      {
        this.status.Text = "The registry has not yet been generated. (Open the files manually for genius, after restart the program)";
      }
    }

    private void UpdateList()
    {
      this.lbList.Items.Clear();
      foreach (tSmcRecords tSmcRecords in Smc.SMCFile)
      {
        foreach (StrModel strModel in Items.NameItem)
        {
          if (tSmcRecords.ID == strModel.m_index)
            this.lbList.Items.Add((object) (tSmcRecords.ID.ToString() + " - " + strModel.m_name));
        }
      }
    }

    private void loadFromDatabaseToolStripMenuItem_Click(object sender, EventArgs e)
    {
      try
      {
        FolderBrowserDialog fbd = new FolderBrowserDialog();
        fbd.Description = "Select the client folder (the folder that contains the Data directory)";
        if (fbd.ShowDialog() != DialogResult.OK)
          return;
        string basePath = fbd.SelectedPath;

        Connection conn = DatabaseHandle.connection;
        string host = conn.Settings.SqlHost;
        string user = conn.Settings.SqlUser;
        string pass = conn.Settings.SqlPassword;
        string database = conn.Settings.SqlDatabase;
        string lang = conn.Settings.Language;

        string langCol = lang switch
        {
          "GER" => "a_name_ger",
          "POL" => "a_name_pld",
          "BRA" => "a_name_brz",
          "RUS" => "a_name_rus",
          "FRA" => "a_name_frc",
          "ESP" => "a_name_spn",
          "MEX" => "a_name_mex",
          "THA" => "a_name_thai",
          "ITA" => "a_name_ita",
          "USA" => "a_name_usa",
          _ => "a_name_usa"
        };

        string connStr = $"server={host};port=3306;user={user};password={pass};database={database};charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;";
        string query = $"SELECT a_index, {langCol}, a_file_smc FROM t_item WHERE a_file_smc IS NOT NULL AND a_file_smc != '' ORDER BY a_index";

        Smc.SMCFile = new List<tSmcRecords>();
        Smc.Menu = new List<string>();
        Items.NameItem = new List<StrModel>();

        int loaded = 0;
        int skipped = 0;

        using (MySqlConnection connection = new MySqlConnection(connStr))
        {
          connection.Open();
          using (MySqlCommand cmd = new MySqlCommand(query, connection))
          using (MySqlDataReader reader = cmd.ExecuteReader())
          {
            while (reader.Read())
            {
              int id = reader.GetInt32(0);
              string name = reader.IsDBNull(1) ? "" : reader.GetString(1);
              string smcPath = reader.IsDBNull(2) ? "" : reader.GetString(2);

              string fullPath = Path.Combine(basePath, smcPath.Replace("\0", string.Empty));
              tSmcRecords record;

              if (File.Exists(fullPath))
              {
                try
                {
                  List<smcMesh> meshData = SMCReader.ReadFile(fullPath);
                  record = new tSmcRecords() { haveData = true, ID = id };
                  try { record.Name = meshData[0].meshname; } catch { record.Name = ""; }
                  record.Models = new List<tModels>();
                  for (int i = 0; i < meshData.Count(); ++i)
                  {
                    tModels model = new tModels()
                    {
                      ModelID = i + 1,
                      ModelFile = meshData[i].FileName,
                      Textures = new List<tTextures>()
                    };
                    for (int j = 0; j < meshData[i].Object.Count(); ++j)
                    {
                      tTextures tex = new tTextures()
                      {
                        TexID = j + 1,
                        TextureName = meshData[i].Object[j].Name,
                        TextureFile = meshData[i].Object[j].Texture
                      };
                      model.Textures.Add(tex);
                    }
                    record.Models.Add(model);
                  }
                  loaded++;
                }
                catch
                {
                  record = new tSmcRecords()
                  {
                    ID = id,
                    Name = smcPath,
                    Models = new List<tModels>(),
                    haveData = true
                  };
                  skipped++;
                }
              }
              else
              {
                record = new tSmcRecords()
                {
                  ID = id,
                  Name = smcPath,
                  Models = new List<tModels>(),
                  haveData = true
                };
                skipped++;
              }

              Smc.SMCFile.Add(record);

              Items.NameItem.Add(new StrModel()
              {
                m_index = id,
                m_name = name
              });
            }
          }
        }

        this.UpdateList();
        this.status.Text = "Loaded " + loaded.ToString() + " SMC records from database (" + skipped.ToString() + " skipped, no .smc file found)";
      }
      catch (Exception ex)
      {
        MessageBox.Show(ex.Message, "Database Error");
      }
    }
  }
}
