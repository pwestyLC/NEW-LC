// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.LogReader
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools
{
  public class LogReader : Form
  {
    private IContainer components = (IContainer) null;
    private TabControl tabControl1;
    private TabPage tabPage1;
    private TabPage tabPage2;
    private TabPage tabPage3;
    private TabPage tabPage4;
    private TabPage tabPage5;
    private TabPage tabPage6;
    private TabPage tabPage7;
    private TabPage tabPage8;
    private MenuStrip menuStrip1;
    private ToolStripMenuItem openLogToolStripMenuItem;
    private TabPage tabPage9;
    private TabPage tabPage10;
    private TabPage tabPage11;
    private TabPage tabPage12;
    private TabPage tabPage14;
    private OpenFileDialog openFileDialog1;
    private ListBox listBox1;
    private ListBox listBox2;
    private ListBox listBox3;
    private ListBox listBox4;
    private ListBox listBox5;
    private ListBox listBox6;
    private ListBox listBox7;
    private ListBox listBox8;
    private ListBox listBox15;
    private ListBox listBox9;
    private ListBox listBox10;
    private ListBox listBox11;
    private ListBox listBox12;
    private TabPage tabPage13;
    private ListBox listBox13;
    private ListBox listBox14;

    public LogReader() => this.InitializeComponent();

    private void tabPage1_Click(object sender, EventArgs e)
    {
    }

    private void openLogToolStripMenuItem_Click(object sender, EventArgs e)
    {
      OpenFileDialog openFileDialog = new OpenFileDialog();
      openFileDialog.Filter = "Log Files|*.log";
      openFileDialog.Title = "Select a Log File";
      if (openFileDialog.ShowDialog() != DialogResult.OK)
        return;
      string[] strArray = File.ReadAllLines(openFileDialog.FileName);
      for (int index = 0; index < strArray.Length; ++index)
      {
        if (strArray[index].Contains("HACK_QUICK") || strArray[index].Contains("HACK QUICK") || strArray[index].Contains("HACK_PULSE") || strArray[index].Contains("HACK PULSE") || strArray[index].Contains("HACK_WEAPON") || strArray[index].Contains("HACK WEAPON") || strArray[index].Contains("HACK USER") || strArray[index].Contains("HACK_USER") || strArray[index].Contains("HACK_PULSE_NOT_RESPONSE") || strArray[index].Contains("HACK PULSE NOT RESPONSE") || strArray[index].Contains("HACK_CHECK") || strArray[index].Contains("HACK CHECK") || strArray[index].Contains("TELEPORT_HACK") || strArray[index].Contains("TELEPORT HACK") || strArray[index].Contains("HACK ATTACK") || strArray[index].Contains("HACK_ATTACK") || strArray[index].Contains("MOVE_HACK") || strArray[index].Contains("MOVE_HACK") || strArray[index].Contains("HACK_MOVE") || strArray[index].Contains("HACK MOVE"))
          this.listBox2.Items.Add((object) strArray[index]);
        if (strArray[index].Contains("ITEM_DROP") || strArray[index].Contains("ITEM_LOAD") || strArray[index].Contains("GM COMMAND"))
          this.listBox1.Items.Add((object) strArray[index]);
        if (strArray[index].Contains("ITEM_JUNK") || strArray[index].Contains("ITEM_PICK") || strArray[index].Contains("ITEM_SELL") || strArray[index].Contains("ITEM_BUY") || strArray[index].Contains("ITEM_BREAK") || strArray[index].Contains("ITEM_EXCHANGE") || strArray[index].Contains("ITEM_ADJUST") || strArray[index].Contains("ITEM_UPGRADE") || strArray[index].Contains("ITEM_MIX") || strArray[index].Contains("ITEM_MAKE") || strArray[index].Contains("ITEM_PROCESS") || strArray[index].Contains("ITEM_PROCESS_SAMPLE") || strArray[index].Contains("ITEM_OPTION_DEL") || strArray[index].Contains("ITEM_REFINE") || strArray[index].Contains("ITEM_OPTION_ADD") || strArray[index].Contains("ITEM_ARCANE") || strArray[index].Contains("ITEM_PICK_QUESTPRIZE") || strArray[index].Contains("ITEM_PICK_LEVELUP") || strArray[index].Contains("WEAR ITEM"))
          this.listBox3.Items.Add((object) strArray[index]);
        if (strArray[index].Contains("CHAR_UPATE") || strArray[index].Contains("CHAR_DELETE") || strArray[index].Contains("CHAR_CREATE") || strArray[index].Contains("CHAR_LOAD") || strArray[index].Contains("REBIRTH PC") || strArray[index].Contains("LEVEL_UP") || strArray[index].Contains("HAVE_MONEY") || strArray[index].Contains("PERSONAL SHOP BUY") || strArray[index].Contains("PERSONAL SHOP START") || strArray[index].Contains("CHAR_DEAUTH"))
          this.listBox4.Items.Add((object) strArray[index]);
        if (strArray[index].Contains("GUILD_NEW") || strArray[index].Contains("GUILD_CREATE") || strArray[index].Contains("GUILD_DEL") || strArray[index].Contains("GUILD_KICK") || strArray[index].Contains("GUILD_LEAVE") || strArray[index].Contains("GUIL_SET_GRADE") || strArray[index].Contains("GUILD_JOIN"))
          this.listBox5.Items.Add((object) strArray[index]);
        if (strArray[index].Contains("BAD_CONNECTION") || strArray[index].Contains("SYS_ERROR") || strArray[index].Contains("SYS_ERR") || strArray[index].Contains("CONN_ERR") || strArray[index].Contains("INVALID_VERSION"))
          this.listBox6.Items.Add((object) strArray[index]);
        if (strArray[index].Contains("STASH_IN") || strArray[index].Contains("STASH_OUT"))
          this.listBox7.Items.Add((object) strArray[index]);
        if (strArray[index].Contains("JOIN") || strArray[index].Contains("DISCONNECT"))
          this.listBox8.Items.Add((object) strArray[index]);
        if (strArray[index].Contains("QUEST REQUEST") || strArray[index].Contains("QUEST START") || strArray[index].Contains("QUEST COMPLETE") || strArray[index].Contains("QUEST GIVEUP") || strArray[index].Contains("QUEST FAIL") || strArray[index].Contains("QUEST PRIZE") || strArray[index].Contains("QUEST ERROR"))
          this.listBox9.Items.Add((object) strArray[index]);
        if (strArray[index].Contains("TITLE ITEM USE") || strArray[index].Contains("TITLE SELECT"))
          this.listBox10.Items.Add((object) strArray[index]);
        if (strArray[index].Contains("MOB DEAD") || strArray[index].Contains("MOB DROP MONEY") || strArray[index].Contains("MOD DROP ITEM") || strArray[index].Contains("MOB REGEN"))
          this.listBox11.Items.Add((object) strArray[index]);
        if (strArray[index].Contains("CASH_ASSIST_DEL") || strArray[index].Contains("CASH_ABS_ASSIST") || strArray[index].Contains("CASH_MEMPOS_STASH_TIME"))
          this.listBox12.Items.Add((object) strArray[index]);
        if (strArray[index].Contains("EP SKILL END") || strArray[index].Contains("EP SKILL START") || strArray[index].Contains("SKILL LEARN"))
          this.listBox14.Items.Add((object) strArray[index]);
      }
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      this.tabControl1 = new TabControl();
      this.tabPage1 = new TabPage();
      this.tabPage2 = new TabPage();
      this.tabPage3 = new TabPage();
      this.tabPage4 = new TabPage();
      this.tabPage5 = new TabPage();
      this.tabPage6 = new TabPage();
      this.tabPage7 = new TabPage();
      this.tabPage8 = new TabPage();
      this.menuStrip1 = new MenuStrip();
      this.openLogToolStripMenuItem = new ToolStripMenuItem();
      this.tabPage9 = new TabPage();
      this.tabPage10 = new TabPage();
      this.tabPage11 = new TabPage();
      this.tabPage12 = new TabPage();
      this.tabPage14 = new TabPage();
      this.openFileDialog1 = new OpenFileDialog();
      this.listBox1 = new ListBox();
      this.listBox2 = new ListBox();
      this.listBox3 = new ListBox();
      this.listBox4 = new ListBox();
      this.listBox5 = new ListBox();
      this.listBox6 = new ListBox();
      this.listBox7 = new ListBox();
      this.listBox8 = new ListBox();
      this.listBox9 = new ListBox();
      this.listBox10 = new ListBox();
      this.listBox11 = new ListBox();
      this.listBox12 = new ListBox();
      this.tabPage13 = new TabPage();
      this.listBox13 = new ListBox();
      this.listBox14 = new ListBox();
      this.listBox15 = new ListBox();
      this.tabControl1.SuspendLayout();
      this.tabPage1.SuspendLayout();
      this.tabPage2.SuspendLayout();
      this.tabPage3.SuspendLayout();
      this.tabPage4.SuspendLayout();
      this.tabPage5.SuspendLayout();
      this.tabPage6.SuspendLayout();
      this.tabPage7.SuspendLayout();
      this.tabPage8.SuspendLayout();
      this.menuStrip1.SuspendLayout();
      this.tabPage9.SuspendLayout();
      this.tabPage10.SuspendLayout();
      this.tabPage11.SuspendLayout();
      this.tabPage12.SuspendLayout();
      this.tabPage14.SuspendLayout();
      this.tabPage13.SuspendLayout();
      this.SuspendLayout();
      this.tabControl1.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
      this.tabControl1.Controls.Add((Control) this.tabPage1);
      this.tabControl1.Controls.Add((Control) this.tabPage2);
      this.tabControl1.Controls.Add((Control) this.tabPage3);
      this.tabControl1.Controls.Add((Control) this.tabPage4);
      this.tabControl1.Controls.Add((Control) this.tabPage5);
      this.tabControl1.Controls.Add((Control) this.tabPage6);
      this.tabControl1.Controls.Add((Control) this.tabPage7);
      this.tabControl1.Controls.Add((Control) this.tabPage8);
      this.tabControl1.Controls.Add((Control) this.tabPage9);
      this.tabControl1.Controls.Add((Control) this.tabPage10);
      this.tabControl1.Controls.Add((Control) this.tabPage11);
      this.tabControl1.Controls.Add((Control) this.tabPage12);
      this.tabControl1.Controls.Add((Control) this.tabPage13);
      this.tabControl1.Controls.Add((Control) this.tabPage14);
      this.tabControl1.Location = new Point(3, 30);
      this.tabControl1.Name = "tabControl1";
      this.tabControl1.SelectedIndex = 0;
      this.tabControl1.Size = new Size(1135, 511);
      this.tabControl1.TabIndex = 0;
      this.tabPage1.BackColor = Color.Black;
      this.tabPage1.Controls.Add((Control) this.listBox1);
      this.tabPage1.ForeColor = SystemColors.ControlLightLight;
      this.tabPage1.Location = new Point(4, 22);
      this.tabPage1.Name = "tabPage1";
      this.tabPage1.Padding = new Padding(3);
      this.tabPage1.Size = new Size(1127, 485);
      this.tabPage1.TabIndex = 0;
      this.tabPage1.Text = "GM Logs";
      this.tabPage1.Click += new EventHandler(this.tabPage1_Click);
      this.tabPage2.BackColor = Color.Black;
      this.tabPage2.Controls.Add((Control) this.listBox2);
      this.tabPage2.ForeColor = Color.Yellow;
      this.tabPage2.Location = new Point(4, 22);
      this.tabPage2.Name = "tabPage2";
      this.tabPage2.Padding = new Padding(3);
      this.tabPage2.Size = new Size(1127, 485);
      this.tabPage2.TabIndex = 1;
      this.tabPage2.Text = "Hack Logs";
      this.tabPage3.BackColor = Color.Black;
      this.tabPage3.Controls.Add((Control) this.listBox3);
      this.tabPage3.ForeColor = Color.Red;
      this.tabPage3.Location = new Point(4, 22);
      this.tabPage3.Name = "tabPage3";
      this.tabPage3.Padding = new Padding(3);
      this.tabPage3.Size = new Size(1127, 485);
      this.tabPage3.TabIndex = 2;
      this.tabPage3.Text = "Items Logs";
      this.tabPage4.BackColor = Color.Black;
      this.tabPage4.Controls.Add((Control) this.listBox4);
      this.tabPage4.ForeColor = Color.Coral;
      this.tabPage4.Location = new Point(4, 22);
      this.tabPage4.Name = "tabPage4";
      this.tabPage4.Padding = new Padding(3);
      this.tabPage4.Size = new Size(1127, 485);
      this.tabPage4.TabIndex = 3;
      this.tabPage4.Text = "Char Logs";
      this.tabPage5.BackColor = Color.Black;
      this.tabPage5.Controls.Add((Control) this.listBox5);
      this.tabPage5.ForeColor = Color.Lime;
      this.tabPage5.Location = new Point(4, 22);
      this.tabPage5.Name = "tabPage5";
      this.tabPage5.Padding = new Padding(3);
      this.tabPage5.Size = new Size(1127, 485);
      this.tabPage5.TabIndex = 4;
      this.tabPage5.Text = "Guild Logs";
      this.tabPage6.BackColor = Color.Black;
      this.tabPage6.Controls.Add((Control) this.listBox6);
      this.tabPage6.ForeColor = Color.Aqua;
      this.tabPage6.Location = new Point(4, 22);
      this.tabPage6.Name = "tabPage6";
      this.tabPage6.Padding = new Padding(3);
      this.tabPage6.Size = new Size(1127, 485);
      this.tabPage6.TabIndex = 5;
      this.tabPage6.Text = "Err Logs";
      this.tabPage7.BackColor = Color.Black;
      this.tabPage7.Controls.Add((Control) this.listBox7);
      this.tabPage7.ForeColor = Color.Fuchsia;
      this.tabPage7.Location = new Point(4, 22);
      this.tabPage7.Name = "tabPage7";
      this.tabPage7.Padding = new Padding(3);
      this.tabPage7.Size = new Size(1127, 485);
      this.tabPage7.TabIndex = 6;
      this.tabPage7.Text = "Stash Logs";
      this.tabPage8.BackColor = Color.Black;
      this.tabPage8.Controls.Add((Control) this.listBox8);
      this.tabPage8.ForeColor = Color.FromArgb(128, (int) byte.MaxValue, (int) byte.MaxValue);
      this.tabPage8.Location = new Point(4, 22);
      this.tabPage8.Name = "tabPage8";
      this.tabPage8.Padding = new Padding(3);
      this.tabPage8.Size = new Size(1127, 485);
      this.tabPage8.TabIndex = 7;
      this.tabPage8.Text = "Join DC Logs";
      this.menuStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.openLogToolStripMenuItem
      });
      this.menuStrip1.Location = new Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new Size(1139, 24);
      this.menuStrip1.TabIndex = 1;
      this.menuStrip1.Text = "menuStrip1";
      this.openLogToolStripMenuItem.Name = "openLogToolStripMenuItem";
      this.openLogToolStripMenuItem.Size = new Size(71, 20);
      this.openLogToolStripMenuItem.Text = "Open Log";
      this.openLogToolStripMenuItem.Click += new EventHandler(this.openLogToolStripMenuItem_Click);
      this.tabPage9.BackColor = Color.Black;
      this.tabPage9.Controls.Add((Control) this.listBox15);
      this.tabPage9.Controls.Add((Control) this.listBox9);
      this.tabPage9.ForeColor = Color.CornflowerBlue;
      this.tabPage9.Location = new Point(4, 22);
      this.tabPage9.Name = "tabPage9";
      this.tabPage9.Size = new Size(1127, 485);
      this.tabPage9.TabIndex = 8;
      this.tabPage9.Text = "Quest Logs";
      this.tabPage10.BackColor = Color.Black;
      this.tabPage10.Controls.Add((Control) this.listBox10);
      this.tabPage10.ForeColor = SystemColors.MenuHighlight;
      this.tabPage10.Location = new Point(4, 22);
      this.tabPage10.Name = "tabPage10";
      this.tabPage10.Size = new Size(1127, 485);
      this.tabPage10.TabIndex = 9;
      this.tabPage10.Text = "Title Logs";
      this.tabPage11.BackColor = Color.Black;
      this.tabPage11.Controls.Add((Control) this.listBox11);
      this.tabPage11.ForeColor = Color.Pink;
      this.tabPage11.Location = new Point(4, 22);
      this.tabPage11.Name = "tabPage11";
      this.tabPage11.Size = new Size(1127, 485);
      this.tabPage11.TabIndex = 10;
      this.tabPage11.Text = "Mobs Logs";
      this.tabPage12.BackColor = Color.Black;
      this.tabPage12.Controls.Add((Control) this.listBox12);
      this.tabPage12.ForeColor = Color.Orchid;
      this.tabPage12.Location = new Point(4, 22);
      this.tabPage12.Name = "tabPage12";
      this.tabPage12.Size = new Size(1127, 485);
      this.tabPage12.TabIndex = 11;
      this.tabPage12.Text = "Cash Logs";
      this.tabPage14.BackColor = Color.Black;
      this.tabPage14.Controls.Add((Control) this.listBox14);
      this.tabPage14.ForeColor = Color.GreenYellow;
      this.tabPage14.Location = new Point(4, 22);
      this.tabPage14.Name = "tabPage14";
      this.tabPage14.Size = new Size(1127, 485);
      this.tabPage14.TabIndex = 13;
      this.tabPage14.Text = "Skills Logs";
      this.openFileDialog1.FileName = "openFileDialog1";
      this.listBox1.BackColor = Color.Black;
      this.listBox1.Dock = DockStyle.Fill;
      this.listBox1.ForeColor = Color.Aqua;
      this.listBox1.FormattingEnabled = true;
      this.listBox1.Location = new Point(3, 3);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new Size(1121, 479);
      this.listBox1.TabIndex = 0;
      this.listBox2.BackColor = Color.Black;
      this.listBox2.Dock = DockStyle.Fill;
      this.listBox2.ForeColor = Color.YellowGreen;
      this.listBox2.FormattingEnabled = true;
      this.listBox2.Location = new Point(3, 3);
      this.listBox2.Name = "listBox2";
      this.listBox2.Size = new Size(1121, 479);
      this.listBox2.TabIndex = 1;
      this.listBox3.BackColor = Color.Black;
      this.listBox3.Dock = DockStyle.Fill;
      this.listBox3.ForeColor = Color.Lime;
      this.listBox3.FormattingEnabled = true;
      this.listBox3.Location = new Point(3, 3);
      this.listBox3.Name = "listBox3";
      this.listBox3.Size = new Size(1121, 479);
      this.listBox3.TabIndex = 1;
      this.listBox4.BackColor = Color.Black;
      this.listBox4.Dock = DockStyle.Fill;
      this.listBox4.ForeColor = Color.Aqua;
      this.listBox4.FormattingEnabled = true;
      this.listBox4.Location = new Point(3, 3);
      this.listBox4.Name = "listBox4";
      this.listBox4.Size = new Size(1121, 479);
      this.listBox4.TabIndex = 1;
      this.listBox5.BackColor = Color.Black;
      this.listBox5.Dock = DockStyle.Fill;
      this.listBox5.ForeColor = Color.Fuchsia;
      this.listBox5.FormattingEnabled = true;
      this.listBox5.Location = new Point(3, 3);
      this.listBox5.Name = "listBox5";
      this.listBox5.Size = new Size(1121, 479);
      this.listBox5.TabIndex = 1;
      this.listBox6.BackColor = Color.Black;
      this.listBox6.Dock = DockStyle.Fill;
      this.listBox6.ForeColor = Color.Red;
      this.listBox6.FormattingEnabled = true;
      this.listBox6.Location = new Point(3, 3);
      this.listBox6.Name = "listBox6";
      this.listBox6.Size = new Size(1121, 479);
      this.listBox6.TabIndex = 1;
      this.listBox7.BackColor = Color.Black;
      this.listBox7.Dock = DockStyle.Fill;
      this.listBox7.ForeColor = Color.FromArgb((int) byte.MaxValue, 192, 128);
      this.listBox7.FormattingEnabled = true;
      this.listBox7.Location = new Point(3, 3);
      this.listBox7.Name = "listBox7";
      this.listBox7.Size = new Size(1121, 479);
      this.listBox7.TabIndex = 1;
      this.listBox8.BackColor = Color.Black;
      this.listBox8.Dock = DockStyle.Fill;
      this.listBox8.ForeColor = Color.White;
      this.listBox8.FormattingEnabled = true;
      this.listBox8.Location = new Point(3, 3);
      this.listBox8.Name = "listBox8";
      this.listBox8.Size = new Size(1121, 479);
      this.listBox8.TabIndex = 1;
      this.listBox9.BackColor = Color.Black;
      this.listBox9.Dock = DockStyle.Fill;
      this.listBox9.FormattingEnabled = true;
      this.listBox9.Location = new Point(0, 0);
      this.listBox9.Name = "listBox9";
      this.listBox9.Size = new Size(1127, 485);
      this.listBox9.TabIndex = 1;
      this.listBox10.BackColor = Color.Black;
      this.listBox10.Dock = DockStyle.Fill;
      this.listBox10.ForeColor = Color.Khaki;
      this.listBox10.FormattingEnabled = true;
      this.listBox10.Location = new Point(0, 0);
      this.listBox10.Name = "listBox10";
      this.listBox10.Size = new Size(1127, 485);
      this.listBox10.TabIndex = 1;
      this.listBox11.BackColor = Color.Black;
      this.listBox11.Dock = DockStyle.Fill;
      this.listBox11.ForeColor = Color.LawnGreen;
      this.listBox11.FormattingEnabled = true;
      this.listBox11.Location = new Point(0, 0);
      this.listBox11.Name = "listBox11";
      this.listBox11.Size = new Size(1127, 485);
      this.listBox11.TabIndex = 1;
      this.listBox12.BackColor = Color.Black;
      this.listBox12.Dock = DockStyle.Fill;
      this.listBox12.ForeColor = Color.MediumAquamarine;
      this.listBox12.FormattingEnabled = true;
      this.listBox12.Location = new Point(0, 0);
      this.listBox12.Name = "listBox12";
      this.listBox12.Size = new Size(1127, 485);
      this.listBox12.TabIndex = 1;
      this.tabPage13.BackColor = Color.Black;
      this.tabPage13.Controls.Add((Control) this.listBox13);
      this.tabPage13.ForeColor = Color.SpringGreen;
      this.tabPage13.Location = new Point(4, 22);
      this.tabPage13.Name = "tabPage13";
      this.tabPage13.Size = new Size(1127, 485);
      this.tabPage13.TabIndex = 12;
      this.tabPage13.Text = "LuckDraw Logs";
      this.listBox13.BackColor = Color.Black;
      this.listBox13.Dock = DockStyle.Fill;
      this.listBox13.ForeColor = Color.Silver;
      this.listBox13.FormattingEnabled = true;
      this.listBox13.Location = new Point(0, 0);
      this.listBox13.Name = "listBox13";
      this.listBox13.Size = new Size(1127, 485);
      this.listBox13.TabIndex = 1;
      this.listBox14.BackColor = Color.Black;
      this.listBox14.Dock = DockStyle.Fill;
      this.listBox14.ForeColor = Color.Yellow;
      this.listBox14.FormattingEnabled = true;
      this.listBox14.Location = new Point(0, 0);
      this.listBox14.Name = "listBox14";
      this.listBox14.Size = new Size(1127, 485);
      this.listBox14.TabIndex = 1;
      this.listBox15.BackColor = Color.Black;
      this.listBox15.Dock = DockStyle.Fill;
      this.listBox15.ForeColor = Color.DarkOrange;
      this.listBox15.FormattingEnabled = true;
      this.listBox15.Location = new Point(0, 0);
      this.listBox15.Name = "listBox15";
      this.listBox15.Size = new Size(1127, 485);
      this.listBox15.TabIndex = 2;
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(1139, 537);
      this.Controls.Add((Control) this.tabControl1);
      this.Controls.Add((Control) this.menuStrip1);
      this.MainMenuStrip = this.menuStrip1;
      this.Name = nameof (LogReader);
      this.Text = nameof (LogReader);
      this.tabControl1.ResumeLayout(false);
      this.tabPage1.ResumeLayout(false);
      this.tabPage2.ResumeLayout(false);
      this.tabPage3.ResumeLayout(false);
      this.tabPage4.ResumeLayout(false);
      this.tabPage5.ResumeLayout(false);
      this.tabPage6.ResumeLayout(false);
      this.tabPage7.ResumeLayout(false);
      this.tabPage8.ResumeLayout(false);
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.tabPage9.ResumeLayout(false);
      this.tabPage10.ResumeLayout(false);
      this.tabPage11.ResumeLayout(false);
      this.tabPage12.ResumeLayout(false);
      this.tabPage14.ResumeLayout(false);
      this.tabPage13.ResumeLayout(false);
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
