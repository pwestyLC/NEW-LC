// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.FlagBuilder
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools
{
  public class FlagBuilder : Form
  {
    public static Connection connection = new Connection();
    private string Episode = FlagBuilder.connection.Settings.Episode;
    public string flagBuilderType = "items";
    private IContainer components = (IContainer) null;
    public long flagBig;
    public int flagSmall;
    private Button button1;
    public TextBox textBox2;
    public CheckedListBox clbFlagTest2;

    public FlagBuilder() => this.InitializeComponent();

    private void LoadStartUp()
    {
      string[] items = new string[1]{ "0 - none" };
      if (this.flagBuilderType == "skills")
        items = FlagList.Skills;
      else if (this.flagBuilderType == "skills1")
        items = FlagList.Skills2;
      else if (this.flagBuilderType == "skills2")
        items = FlagList.Skills3;
      else if (this.flagBuilderType == "items")
        items = !(this.Episode == "EP4") ? FlagList.ItemsEP3 : FlagList.ItemsEP4;
      else if (this.flagBuilderType == "npcs")
        items = FlagList.Npcs;
      else if (this.flagBuilderType == "npcs1")
        items = FlagList.Npcs1;
      this.clbFlagTest2.Items.AddRange((object[]) items);
    }

    private void SetFlag(long flag, CheckedListBox clbFlagTest)
    {
      for (int index = 0; index < 64; ++index)
        clbFlagTest.SetItemChecked(index, (flag & 1L << index) > 0L);
    }

    private long GetFlag(CheckedListBox clbFlagTest)
    {
      long flag = 0;
      for (int index = 0; index < clbFlagTest.Items.Count; ++index)
      {
        if (clbFlagTest.GetItemChecked(index))
          flag += 1L << index;
      }
      return flag;
    }

    private void ShowFlagLong(long flag)
    {
      for (int index = 0; index < 64; ++index)
        this.clbFlagTest2.SetItemChecked(index, (flag & 1L << index) > 0L);
    }

    private void ShowFlag(int flag)
    {
      for (int index = 0; index < this.clbFlagTest2.Items.Count; ++index)
        this.clbFlagTest2.SetItemChecked(index, (flag & 1 << index) > 0);
    }

    private void clbFlagTest2_SelectedIndexChanged(object sender, EventArgs e)
    {
      long num = 0;
      for (int index = 0; index < this.clbFlagTest2.Items.Count; ++index)
      {
        if (this.clbFlagTest2.GetItemChecked(index))
          num += 1L << index;
      }
      this.textBox2.Text = num.ToString();
      if (this.flagBuilderType == "items")
      {
        if (this.Episode == "EP4")
          this.flagBig = num;
        else
          this.flagSmall = Convert.ToInt32(num);
      }
      else
        this.flagSmall = Convert.ToInt32(num);
    }

    private void Form5_Load(object sender, EventArgs e)
    {
      this.LoadStartUp();
      if (this.flagBuilderType == "items")
      {
        if (this.Episode == "EP4")
        {
          this.ShowFlagLong(this.flagBig);
          this.textBox2.Text = this.flagBig.ToString();
        }
        else
        {
          this.ShowFlag(this.flagSmall);
          this.textBox2.Text = this.flagSmall.ToString();
        }
      }
      else
      {
        this.ShowFlag(this.flagSmall);
        this.textBox2.Text = this.flagSmall.ToString();
      }
    }

    private void button1_Click(object sender, EventArgs e) => this.DialogResult = DialogResult.OK;

    private void textBox2_TextChanged(object sender, EventArgs e)
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
      this.textBox2 = new TextBox();
      this.clbFlagTest2 = new CheckedListBox();
      this.button1 = new Button();
      this.SuspendLayout();
      this.textBox2.BorderStyle = BorderStyle.FixedSingle;
      this.textBox2.Location = new Point(12, 578);
      this.textBox2.Name = "textBox2";
      this.textBox2.Size = new Size(174, 20);
      this.textBox2.TabIndex = 3;
      this.textBox2.TextChanged += new EventHandler(this.textBox2_TextChanged);
      this.clbFlagTest2.CheckOnClick = true;
      this.clbFlagTest2.FormattingEnabled = true;
      this.clbFlagTest2.Location = new Point(12, 10);
      this.clbFlagTest2.MultiColumn = true;
      this.clbFlagTest2.Name = "clbFlagTest2";
      this.clbFlagTest2.Size = new Size(280, 559);
      this.clbFlagTest2.TabIndex = 4;
      this.clbFlagTest2.SelectedIndexChanged += new EventHandler(this.clbFlagTest2_SelectedIndexChanged);
      this.button1.FlatStyle = FlatStyle.Flat;
      this.button1.Location = new Point(192, 575);
      this.button1.Name = "button1";
      this.button1.Size = new Size(100, 23);
      this.button1.TabIndex = 7;
      this.button1.Text = "Save Flag";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.ClientSize = new Size(305, 610);
      this.Controls.Add((Control) this.button1);
      this.Controls.Add((Control) this.clbFlagTest2);
      this.Controls.Add((Control) this.textBox2);
      this.MaximizeBox = false;
      this.MinimizeBox = false;
      this.Name = nameof (FlagBuilder);
      this.StartPosition = FormStartPosition.CenterParent;
      this.Text = nameof (FlagBuilder);
      this.Load += new EventHandler(this.Form5_Load);
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
