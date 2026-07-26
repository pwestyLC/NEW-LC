// Decompiled with JetBrains decompiler
// Type: SMCEditor4.RecordSelector
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;

#nullable disable
namespace SMCEditor4
{
  public class RecordSelector : Form
  {
    private List<tSmcRecords> data = new List<tSmcRecords>();
    private Button btnAdd;
    private Button btnCancel;
    private CheckedListBox clbList;
    private IContainer components;
    private Label label1;
    public tSmcRecords[] Records;
    private SplitContainer splitContainer1;
    private SplitContainer splitContainer2;

    public RecordSelector(string FileName)
    {
      this.InitializeComponent();
      this.data = Smc.ReadFile2(FileName);
      this.MakeList();
    }

    private void btnAdd_Click(object sender, EventArgs e)
    {
      List<tSmcRecords> tSmcRecordsList = new List<tSmcRecords>();
      for (int index1 = 0; index1 < this.clbList.CheckedIndices.Count; ++index1)
      {
        int ItemID = this.GetID(this.clbList.Items[this.clbList.CheckedIndices[index1]].ToString());
        int index2 = this.data.FindIndex((Predicate<tSmcRecords>) (p => p.ID.Equals(ItemID)));
        if (index2 != -1)
          tSmcRecordsList.Add((tSmcRecords) this.data[index2].Clone());
      }
      this.Records = tSmcRecordsList.ToArray();
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private int GetID(string text)
    {
      int result = -1;
      int.TryParse(text.Split(' ')[0], out result);
      return result;
    }

    private void InitializeComponent()
    {
      this.splitContainer1 = new SplitContainer();
      this.label1 = new Label();
      this.splitContainer2 = new SplitContainer();
      this.clbList = new CheckedListBox();
      this.btnCancel = new Button();
      this.btnAdd = new Button();
      this.splitContainer1.BeginInit();
      this.splitContainer1.Panel1.SuspendLayout();
      this.splitContainer1.Panel2.SuspendLayout();
      this.splitContainer1.SuspendLayout();
      this.splitContainer2.BeginInit();
      this.splitContainer2.Panel1.SuspendLayout();
      this.splitContainer2.Panel2.SuspendLayout();
      this.splitContainer2.SuspendLayout();
      this.SuspendLayout();
      this.splitContainer1.Dock = DockStyle.Fill;
      this.splitContainer1.FixedPanel = FixedPanel.Panel1;
      this.splitContainer1.Location = new Point(0, 0);
      this.splitContainer1.Name = "splitContainer1";
      this.splitContainer1.Orientation = Orientation.Horizontal;
      this.splitContainer1.Panel1.Controls.Add((Control) this.label1);
      this.splitContainer1.Panel2.Controls.Add((Control) this.splitContainer2);
      this.splitContainer1.Size = new Size(294, 556);
      this.splitContainer1.SplitterDistance = 40;
      this.splitContainer1.TabIndex = 0;
      this.label1.AutoSize = true;
      this.label1.Location = new Point(7, 13);
      this.label1.Name = "label1";
      this.label1.Size = new Size(264, 13);
      this.label1.TabIndex = 0;
      this.label1.Text = "Select the records that u want to add to the original file";
      this.splitContainer2.Dock = DockStyle.Fill;
      this.splitContainer2.FixedPanel = FixedPanel.Panel2;
      this.splitContainer2.Location = new Point(0, 0);
      this.splitContainer2.Name = "splitContainer2";
      this.splitContainer2.Orientation = Orientation.Horizontal;
      this.splitContainer2.Panel1.Controls.Add((Control) this.clbList);
      this.splitContainer2.Panel1.Padding = new Padding(10, 0, 10, 0);
      this.splitContainer2.Panel2.Controls.Add((Control) this.btnCancel);
      this.splitContainer2.Panel2.Controls.Add((Control) this.btnAdd);
      this.splitContainer2.Size = new Size(294, 512);
      this.splitContainer2.SplitterDistance = 462;
      this.splitContainer2.TabIndex = 0;
      this.clbList.Dock = DockStyle.Fill;
      this.clbList.FormattingEnabled = true;
      this.clbList.Location = new Point(10, 0);
      this.clbList.Name = "clbList";
      this.clbList.Size = new Size(274, 462);
      this.clbList.TabIndex = 0;
      this.btnCancel.Location = new Point(128, 11);
      this.btnCancel.Name = "btnCancel";
      this.btnCancel.Size = new Size(75, 23);
      this.btnCancel.TabIndex = 1;
      this.btnCancel.Text = "Cancel";
      this.btnCancel.UseVisualStyleBackColor = true;
      this.btnAdd.Location = new Point(209, 11);
      this.btnAdd.Name = "btnAdd";
      this.btnAdd.Size = new Size(75, 23);
      this.btnAdd.TabIndex = 0;
      this.btnAdd.Text = "Add";
      this.btnAdd.UseVisualStyleBackColor = true;
      this.btnAdd.Click += new EventHandler(this.btnAdd_Click);
      this.ClientSize = new Size(294, 556);
      this.Controls.Add((Control) this.splitContainer1);
      this.Name = nameof (RecordSelector);
      this.Text = nameof (RecordSelector);
      this.Load += new EventHandler(this.RecordSelector_Load);
      this.splitContainer1.Panel1.ResumeLayout(false);
      this.splitContainer1.Panel1.PerformLayout();
      this.splitContainer1.Panel2.ResumeLayout(false);
      this.splitContainer1.EndInit();
      this.splitContainer1.ResumeLayout(false);
      this.splitContainer2.Panel1.ResumeLayout(false);
      this.splitContainer2.Panel2.ResumeLayout(false);
      this.splitContainer2.EndInit();
      this.splitContainer2.ResumeLayout(false);
      this.ResumeLayout(false);
    }

    private void MakeList()
    {
      List<string> stringList = new List<string>();
      for (int index = 0; index < this.data.Count<tSmcRecords>(); ++index)
        stringList.Add(this.data[index].ID.ToString() + " - " + Items.GetNameFromID(this.data[index].ID));
      this.clbList.Items.Clear();
      this.clbList.Items.AddRange((object[]) stringList.ToArray());
    }

    private void RecordSelector_Load(object sender, EventArgs e)
    {
    }
  }
}
