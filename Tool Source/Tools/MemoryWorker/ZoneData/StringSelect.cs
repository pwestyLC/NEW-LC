// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneData.StringSelect
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
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneData
{
  public class StringSelect : Form
  {
    private Dictionary<int, string> m_strings;
    private bool hasSelection;
    private IContainer components;
    private ListBox lb_stringView;
    private Button selectBtn;
    private Label label1;
    private TextBox textBox1;

    public StringSelect(Dictionary<int, string> strings)
    {
      this.InitializeComponent();
      this.m_strings = strings;
      foreach (KeyValuePair<int, string> keyValuePair in this.m_strings)
        this.lb_stringView.Items.Add((object) string.Format("{0} - {1}", (object) keyValuePair.Key.ToString(), (object) keyValuePair.Value));
    }

    public string Selected()
    {
      if (!this.hasSelection)
        this.lb_stringView.SelectedIndex = -1;
      if (this.lb_stringView.Items.Count == 0 || this.lb_stringView.SelectedIndex == -1)
        return "NONE";
      return this.lb_stringView.Items[this.lb_stringView.SelectedIndex].ToString().Split('-')[0].TrimEnd(' ');
    }

    private void selectBtn_Click(object sender, EventArgs e)
    {
      this.hasSelection = true;
      this.Close();
    }

    private void textBox1_TextChanged(object sender, EventArgs e)
    {
      int num;
      try
      {
        num = this.lb_stringView.FindString(this.m_strings.First<KeyValuePair<int, string>>((Func<KeyValuePair<int, string>, bool>) (p => p.Value.ToLower().Contains(this.textBox1.Text.ToLower()))).Key.ToString());
      }
      catch (Exception ex)
      {
        return;
      }
      if (num == -1)
        return;
      this.lb_stringView.SelectedIndex = num;
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (StringSelect));
      this.lb_stringView = new ListBox();
      this.selectBtn = new Button();
      this.label1 = new Label();
      this.textBox1 = new TextBox();
      this.SuspendLayout();
      this.lb_stringView.FormattingEnabled = true;
      this.lb_stringView.Location = new Point(12, 38);
      this.lb_stringView.Name = "lb_stringView";
      this.lb_stringView.Size = new Size(243, 290);
      this.lb_stringView.TabIndex = 0;
      this.selectBtn.Location = new Point(12, 334);
      this.selectBtn.Name = "selectBtn";
      this.selectBtn.Size = new Size(243, 23);
      this.selectBtn.TabIndex = 1;
      this.selectBtn.Text = "Select";
      this.selectBtn.UseVisualStyleBackColor = true;
      this.selectBtn.Click += new EventHandler(this.selectBtn_Click);
      this.label1.AutoSize = true;
      this.label1.Location = new Point(9, 9);
      this.label1.Name = "label1";
      this.label1.Size = new Size(47, 13);
      this.label1.TabIndex = 2;
      this.label1.Text = "Search :";
      this.textBox1.Location = new Point(62, 9);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(193, 20);
      this.textBox1.TabIndex = 3;
      this.textBox1.TextChanged += new EventHandler(this.textBox1_TextChanged);
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(267, 363);
      this.Controls.Add((Control) this.textBox1);
      this.Controls.Add((Control) this.label1);
      this.Controls.Add((Control) this.selectBtn);
      this.Controls.Add((Control) this.lb_stringView);
      this.FormBorderStyle = FormBorderStyle.FixedDialog;
      this.Icon = (Icon) componentResourceManager.GetObject("$this.Icon");
      this.MaximizeBox = false;
      this.MinimizeBox = false;
      this.Name = nameof (StringSelect);
      this.Text = "Select A String";
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
