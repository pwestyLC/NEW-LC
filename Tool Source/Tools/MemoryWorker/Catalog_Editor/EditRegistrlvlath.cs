// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.Catalog_Editor.EditRegistrlvlath
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.Catalog_Editor
{
  public class EditRegistrlvlath : Form
  {
    private List<string> MenuList = new List<string>();
    private IContainer components;
    private TextBox tb_itemAll;
    private Button PickButton;
    private GroupBox groupBox1;
    public int ReturnItemID;
    public string Path_itemAll;
    private GroupBox groupBox3;
    private TextBox tb_Path_strItem;
    public string Path_strItem;

    public EditRegistrlvlath() => this.InitializeComponent();

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

    private void InitializeComponent()
    {
      this.tb_itemAll = new TextBox();
      this.PickButton = new Button();
      this.groupBox1 = new GroupBox();
      this.groupBox3 = new GroupBox();
      this.tb_Path_strItem = new TextBox();
      this.groupBox1.SuspendLayout();
      this.groupBox3.SuspendLayout();
      this.SuspendLayout();
      this.tb_itemAll.Location = new Point(6, 19);
      this.tb_itemAll.Name = "tb_itemAll";
      this.tb_itemAll.Size = new Size(450, 20);
      this.tb_itemAll.TabIndex = 2;
      this.PickButton.DialogResult = DialogResult.OK;
      this.PickButton.Location = new Point(12, 120);
      this.PickButton.Name = "PickButton";
      this.PickButton.Size = new Size(495, 23);
      this.PickButton.TabIndex = 0;
      this.PickButton.Text = "OK";
      this.PickButton.UseVisualStyleBackColor = true;
      this.PickButton.Click += new EventHandler(this.PickButton_Click);
      this.groupBox1.Controls.Add((Control) this.tb_itemAll);
      this.groupBox1.Location = new Point(12, 12);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(495, 48);
      this.groupBox1.TabIndex = 66;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "itemAll.lod";
      this.groupBox3.Controls.Add((Control) this.tb_Path_strItem);
      this.groupBox3.Location = new Point(12, 66);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Size = new Size(495, 48);
      this.groupBox3.TabIndex = 68;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "strItem_*.lod";
      this.tb_Path_strItem.Location = new Point(6, 19);
      this.tb_Path_strItem.Name = "tb_Path_strItem";
      this.tb_Path_strItem.Size = new Size(450, 20);
      this.tb_Path_strItem.TabIndex = 2;
      this.ClientSize = new Size(520, 158);
      this.Controls.Add((Control) this.groupBox3);
      this.Controls.Add((Control) this.groupBox1);
      this.Controls.Add((Control) this.PickButton);
      this.FormBorderStyle = FormBorderStyle.FixedToolWindow;
      this.Name = nameof (EditRegistrlvlath);
      this.ShowInTaskbar = false;
      this.Load += new EventHandler(this.ItemSearch_Load);
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.groupBox3.ResumeLayout(false);
      this.groupBox3.PerformLayout();
      this.ResumeLayout(false);
    }

    private void ItemSearch_Load(object sender, EventArgs e)
    {
      RegistryKey registryKey = Registry.CurrentUser.OpenSubKey("LC_Path");
      this.tb_itemAll.Text = (string) registryKey.GetValue("Path_itemAll");
      this.tb_Path_strItem.Text = (string) registryKey.GetValue("Path_strItem");
    }

    private void PickButton_Click(object sender, EventArgs e)
    {
      RegistryKey subKey = Registry.CurrentUser.CreateSubKey("LC_Path");
      subKey.SetValue("Path_itemAll", (object) this.tb_itemAll.Text);
      subKey.SetValue("Path_strItem", (object) this.tb_Path_strItem.Text);
      subKey.Close();
      this.Path_itemAll = this.tb_itemAll.Text;
      this.Path_strItem = this.tb_Path_strItem.Text;
    }
  }
}
