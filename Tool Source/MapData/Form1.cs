// Decompiled with JetBrains decompiler
// Type: MapDtaRead.Form1
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

#nullable disable
namespace MapDtaRead
{
  public class Form1 : Form
  {
    private IContainer components;
    private MenuStrip menuStrip1;
    private ToolStripMenuItem fileToolStripMenuItem;
    private ToolStripMenuItem openToolStripMenuItem;
    private ToolStripMenuItem saveToolStripMenuItem;
    private ToolStripMenuItem fuckYourSelfToolStripMenuItem;
    private OpenFileDialog openDta;
    private SaveFileDialog saveDta;
    private Panel panel1;
    private ListBox zones;
    private Button DelZone;
    private Button AddZone;
    private Label label1;
    private Button button1;
    private Label label22;
    private TextBox SubzoneType;
    private Label label12;
    private TextBox SubzoneHeight;
    private Label label11;
    private TextBox SubzoneWidth;
    private Label label13;
    private TextBox subzoneid;
    private Button DelSub;
    private Button AddSub;
    private ListBox subzones;
    private Label label25;
    private Label label24;
    private Label label21;
    private TextBox DFloatRatio;
    private TextBox DFloatY;
    private Label label20;
    private TextBox DFloatX;
    private Label label19;
    private Label label18;
    private Label label17;
    private Label label16;
    private TextBox Dbottom;
    private TextBox Dright;
    private TextBox Dtop;
    private Label label15;
    private TextBox Dleft;
    private TextBox Sbot;
    private TextBox Sright;
    private TextBox Stop;
    private Label label23;
    private Button button4;
    private Button button5;
    private TextBox Sleft;
    private Button button6;
    private ListBox listBox1;
    private Button ApplySubZoneBtn;
    private Label label10;
    private TextBox zoneid;
    private Label label8;
    private TextBox fRatio;
    private TextBox nLeft;
    private Label label7;
    private TextBox nRight;
    private Label label6;
    private TextBox nTop;
    private Label label5;
    private TextBox nBottom;
    private Label label4;
    private GroupBox groupBox1;
    private GroupBox groupBox2;
    private GroupBox groupBox3;
    private Label label9;
    private TextBox NpcIdx;
    private Button AddNpcBtn;
    private Button DelNpcBtn;
    private Label label3;
    private TextBox NpcCoordX;
    private Button EditNpcBtn;
    private ListBox npclist;
    private Label label2;
    private TextBox NpcCoordY;
    private Label label14;
    private TextBox NUnKnown;
    private Label label26;
    private TextBox ZUnknown;

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
      this.saveToolStripMenuItem = new ToolStripMenuItem();
      this.fuckYourSelfToolStripMenuItem = new ToolStripMenuItem();
      this.openDta = new OpenFileDialog();
      this.saveDta = new SaveFileDialog();
      this.panel1 = new Panel();
      this.zones = new ListBox();
      this.DelZone = new Button();
      this.AddZone = new Button();
      this.label1 = new Label();
      this.button1 = new Button();
      this.label22 = new Label();
      this.SubzoneType = new TextBox();
      this.label12 = new Label();
      this.SubzoneHeight = new TextBox();
      this.label11 = new Label();
      this.SubzoneWidth = new TextBox();
      this.label13 = new Label();
      this.subzoneid = new TextBox();
      this.DelSub = new Button();
      this.AddSub = new Button();
      this.subzones = new ListBox();
      this.label25 = new Label();
      this.label24 = new Label();
      this.label21 = new Label();
      this.DFloatRatio = new TextBox();
      this.DFloatY = new TextBox();
      this.label20 = new Label();
      this.DFloatX = new TextBox();
      this.label19 = new Label();
      this.label18 = new Label();
      this.label17 = new Label();
      this.label16 = new Label();
      this.Dbottom = new TextBox();
      this.Dright = new TextBox();
      this.Dtop = new TextBox();
      this.label15 = new Label();
      this.Dleft = new TextBox();
      this.Sbot = new TextBox();
      this.Sright = new TextBox();
      this.Stop = new TextBox();
      this.label23 = new Label();
      this.button4 = new Button();
      this.button5 = new Button();
      this.Sleft = new TextBox();
      this.button6 = new Button();
      this.listBox1 = new ListBox();
      this.ApplySubZoneBtn = new Button();
      this.label10 = new Label();
      this.zoneid = new TextBox();
      this.label8 = new Label();
      this.fRatio = new TextBox();
      this.nLeft = new TextBox();
      this.label7 = new Label();
      this.nRight = new TextBox();
      this.label6 = new Label();
      this.nTop = new TextBox();
      this.label5 = new Label();
      this.nBottom = new TextBox();
      this.label4 = new Label();
      this.groupBox1 = new GroupBox();
      this.groupBox2 = new GroupBox();
      this.groupBox3 = new GroupBox();
      this.label14 = new Label();
      this.NUnKnown = new TextBox();
      this.label2 = new Label();
      this.NpcCoordY = new TextBox();
      this.label9 = new Label();
      this.NpcIdx = new TextBox();
      this.AddNpcBtn = new Button();
      this.DelNpcBtn = new Button();
      this.label3 = new Label();
      this.NpcCoordX = new TextBox();
      this.EditNpcBtn = new Button();
      this.npclist = new ListBox();
      this.label26 = new Label();
      this.ZUnknown = new TextBox();
      this.menuStrip1.SuspendLayout();
      this.panel1.SuspendLayout();
      this.groupBox1.SuspendLayout();
      this.groupBox2.SuspendLayout();
      this.groupBox3.SuspendLayout();
      this.SuspendLayout();
      this.menuStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.fileToolStripMenuItem
      });
      this.menuStrip1.Location = new Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new Size(829, 24);
      this.menuStrip1.TabIndex = 3;
      this.menuStrip1.Text = "menuStrip1";
      this.fileToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[3]
      {
        (ToolStripItem) this.openToolStripMenuItem,
        (ToolStripItem) this.saveToolStripMenuItem,
        (ToolStripItem) this.fuckYourSelfToolStripMenuItem
      });
      this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
      this.fileToolStripMenuItem.Size = new Size(37, 20);
      this.fileToolStripMenuItem.Text = "File";
      this.openToolStripMenuItem.Name = "openToolStripMenuItem";
      this.openToolStripMenuItem.Size = new Size(103, 22);
      this.openToolStripMenuItem.Text = "Open";
      this.openToolStripMenuItem.Click += new EventHandler(this.openToolStripMenuItem_Click);
      this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
      this.saveToolStripMenuItem.Size = new Size(103, 22);
      this.saveToolStripMenuItem.Text = "Save";
      this.saveToolStripMenuItem.Click += new EventHandler(this.saveToolStripMenuItem_Click);
      this.fuckYourSelfToolStripMenuItem.Name = "fuckYourSelfToolStripMenuItem";
      this.fuckYourSelfToolStripMenuItem.Size = new Size(103, 22);
      this.fuckYourSelfToolStripMenuItem.Text = "Close";
      this.fuckYourSelfToolStripMenuItem.Click += new EventHandler(this.fuckYourSelfToolStripMenuItem_Click);
      this.openDta.FileOk += new CancelEventHandler(this.openDta_FileOk);
      this.saveDta.CheckPathExists = false;
      this.saveDta.DefaultExt = "*.dta";
      this.saveDta.FileName = "Map.dta";
      this.saveDta.FileOk += new CancelEventHandler(this.saveDta_FileOk);
      this.panel1.Controls.Add((Control) this.zones);
      this.panel1.Controls.Add((Control) this.DelZone);
      this.panel1.Controls.Add((Control) this.AddZone);
      this.panel1.Controls.Add((Control) this.label1);
      this.panel1.Dock = DockStyle.Left;
      this.panel1.Location = new Point(0, 24);
      this.panel1.Name = "panel1";
      this.panel1.Size = new Size(172, 409);
      this.panel1.TabIndex = 39;
      this.zones.FormattingEnabled = true;
      this.zones.Location = new Point(12, 22);
      this.zones.Name = "zones";
      this.zones.Size = new Size(150, 329);
      this.zones.TabIndex = 31;
      this.zones.SelectedIndexChanged += new EventHandler(this.zones_SelectedIndexChanged);
      this.DelZone.Location = new Point(12, 376);
      this.DelZone.Name = "DelZone";
      this.DelZone.Size = new Size(70, 23);
      this.DelZone.TabIndex = 30;
      this.DelZone.Text = "Delete";
      this.DelZone.UseVisualStyleBackColor = true;
      this.DelZone.Click += new EventHandler(this.DelZone_Click);
      this.AddZone.Location = new Point(92, 376);
      this.AddZone.Name = "AddZone";
      this.AddZone.Size = new Size(70, 23);
      this.AddZone.TabIndex = 29;
      this.AddZone.Text = "Add";
      this.AddZone.UseVisualStyleBackColor = true;
      this.AddZone.Click += new EventHandler(this.AddZone_Click);
      this.label1.AutoSize = true;
      this.label1.Location = new Point(9, 3);
      this.label1.Name = "label1";
      this.label1.Size = new Size(32, 13);
      this.label1.TabIndex = 28;
      this.label1.Text = "Zone";
      this.button1.Location = new Point(121, 132);
      this.button1.Name = "button1";
      this.button1.Size = new Size(154, 23);
      this.button1.TabIndex = 193;
      this.button1.Text = "Apply";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.label22.AutoSize = true;
      this.label22.Location = new Point(118, 109);
      this.label22.Name = "label22";
      this.label22.Size = new Size(31, 13);
      this.label22.TabIndex = 182;
      this.label22.Text = "Type";
      this.SubzoneType.Location = new Point(178, 106);
      this.SubzoneType.Name = "SubzoneType";
      this.SubzoneType.Size = new Size(97, 20);
      this.SubzoneType.TabIndex = 181;
      this.label12.AutoSize = true;
      this.label12.Location = new Point(118, 83);
      this.label12.Name = "label12";
      this.label12.Size = new Size(14, 13);
      this.label12.TabIndex = 180;
      this.label12.Text = "Y";
      this.SubzoneHeight.Location = new Point(178, 80);
      this.SubzoneHeight.Name = "SubzoneHeight";
      this.SubzoneHeight.Size = new Size(97, 20);
      this.SubzoneHeight.TabIndex = 179;
      this.label11.AutoSize = true;
      this.label11.Location = new Point(118, 57);
      this.label11.Name = "label11";
      this.label11.Size = new Size(14, 13);
      this.label11.TabIndex = 178;
      this.label11.Text = "X";
      this.SubzoneWidth.Location = new Point(178, 54);
      this.SubzoneWidth.Name = "SubzoneWidth";
      this.SubzoneWidth.Size = new Size(97, 20);
      this.SubzoneWidth.TabIndex = 177;
      this.label13.AutoSize = true;
      this.label13.Location = new Point(118, 31);
      this.label13.Name = "label13";
      this.label13.Size = new Size(46, 13);
      this.label13.TabIndex = 176;
      this.label13.Text = "Marker?";
      this.subzoneid.Location = new Point(178, 28);
      this.subzoneid.Name = "subzoneid";
      this.subzoneid.Size = new Size(97, 20);
      this.subzoneid.TabIndex = 175;
      this.DelSub.Location = new Point(121, 159);
      this.DelSub.Name = "DelSub";
      this.DelSub.Size = new Size(72, 23);
      this.DelSub.TabIndex = 174;
      this.DelSub.Text = "Delete";
      this.DelSub.UseVisualStyleBackColor = true;
      this.DelSub.Click += new EventHandler(this.DelSub_Click);
      this.AddSub.Location = new Point(203, 159);
      this.AddSub.Name = "AddSub";
      this.AddSub.Size = new Size(72, 23);
      this.AddSub.TabIndex = 173;
      this.AddSub.Text = "Add";
      this.AddSub.UseVisualStyleBackColor = true;
      this.AddSub.Click += new EventHandler(this.AddSub_Click);
      this.subzones.FormattingEnabled = true;
      this.subzones.Location = new Point(11, 22);
      this.subzones.Name = "subzones";
      this.subzones.Size = new Size(97, 160);
      this.subzones.TabIndex = 172;
      this.subzones.SelectedIndexChanged += new EventHandler(this.subzones_SelectedIndexChanged);
      this.label25.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
      this.label25.AutoSize = true;
      this.label25.Location = new Point(330, 107);
      this.label25.Name = "label25";
      this.label25.Size = new Size(55, 13);
      this.label25.TabIndex = 170;
      this.label25.Text = "FloatRatio";
      this.label24.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
      this.label24.AutoSize = true;
      this.label24.Location = new Point(274, 107);
      this.label24.Name = "label24";
      this.label24.Size = new Size(37, 13);
      this.label24.TabIndex = 169;
      this.label24.Text = "FloatY";
      this.label21.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
      this.label21.AutoSize = true;
      this.label21.Location = new Point(218, 107);
      this.label21.Name = "label21";
      this.label21.Size = new Size(37, 13);
      this.label21.TabIndex = 168;
      this.label21.Text = "FloatX";
      this.DFloatRatio.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
      this.DFloatRatio.Location = new Point(333, 123);
      this.DFloatRatio.Name = "DFloatRatio";
      this.DFloatRatio.Size = new Size(50, 20);
      this.DFloatRatio.TabIndex = 167;
      this.DFloatY.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
      this.DFloatY.Location = new Point(277, 123);
      this.DFloatY.Name = "DFloatY";
      this.DFloatY.Size = new Size(50, 20);
      this.DFloatY.TabIndex = 166;
      this.label20.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
      this.label20.AutoSize = true;
      this.label20.Location = new Point(137, 126);
      this.label20.Name = "label20";
      this.label20.Size = new Size(78, 13);
      this.label20.TabIndex = 165;
      this.label20.Text = "MapZoomFloat";
      this.DFloatX.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
      this.DFloatX.Location = new Point(221, 123);
      this.DFloatX.Name = "DFloatX";
      this.DFloatX.Size = new Size(50, 20);
      this.DFloatX.TabIndex = 164;
      this.label19.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
      this.label19.AutoSize = true;
      this.label19.Location = new Point(330, 36);
      this.label19.Name = "label19";
      this.label19.Size = new Size(40, 13);
      this.label19.TabIndex = 163;
      this.label19.Text = "Bottom";
      this.label18.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
      this.label18.AutoSize = true;
      this.label18.Location = new Point(274, 36);
      this.label18.Name = "label18";
      this.label18.Size = new Size(32, 13);
      this.label18.TabIndex = 162;
      this.label18.Text = "Right";
      this.label17.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
      this.label17.AutoSize = true;
      this.label17.Location = new Point(218, 36);
      this.label17.Name = "label17";
      this.label17.Size = new Size(26, 13);
      this.label17.TabIndex = 161;
      this.label17.Text = "Top";
      this.label16.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
      this.label16.AutoSize = true;
      this.label16.Location = new Point(162, 36);
      this.label16.Name = "label16";
      this.label16.Size = new Size(25, 13);
      this.label16.TabIndex = 160;
      this.label16.Text = "Left";
      this.Dbottom.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
      this.Dbottom.Location = new Point(333, 78);
      this.Dbottom.Name = "Dbottom";
      this.Dbottom.Size = new Size(50, 20);
      this.Dbottom.TabIndex = 159;
      this.Dright.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
      this.Dright.Location = new Point(277, 78);
      this.Dright.Name = "Dright";
      this.Dright.Size = new Size(50, 20);
      this.Dright.TabIndex = 158;
      this.Dtop.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
      this.Dtop.Location = new Point(221, 78);
      this.Dtop.Name = "Dtop";
      this.Dtop.Size = new Size(50, 20);
      this.Dtop.TabIndex = 157;
      this.label15.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
      this.label15.AutoSize = true;
      this.label15.Location = new Point(108, 81);
      this.label15.Name = "label15";
      this.label15.Size = new Size(57, 13);
      this.label15.TabIndex = 156;
      this.label15.Text = "ZoomRect";
      this.Dleft.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
      this.Dleft.Location = new Point(165, 78);
      this.Dleft.Name = "Dleft";
      this.Dleft.Size = new Size(50, 20);
      this.Dleft.TabIndex = 155;
      this.Sbot.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
      this.Sbot.Location = new Point(333, 52);
      this.Sbot.Name = "Sbot";
      this.Sbot.Size = new Size(50, 20);
      this.Sbot.TabIndex = 154;
      this.Sright.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
      this.Sright.Location = new Point(277, 52);
      this.Sright.Name = "Sright";
      this.Sright.Size = new Size(50, 20);
      this.Sright.TabIndex = 153;
      this.Stop.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
      this.Stop.Location = new Point(221, 52);
      this.Stop.Name = "Stop";
      this.Stop.Size = new Size(50, 20);
      this.Stop.TabIndex = 152;
      this.label23.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
      this.label23.AutoSize = true;
      this.label23.Location = new Point(108, 55);
      this.label23.Name = "label23";
      this.label23.Size = new Size(45, 13);
      this.label23.TabIndex = 151;
      this.label23.Text = "SelRect";
      this.button4.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
      this.button4.Location = new Point(244, 149);
      this.button4.Name = "button4";
      this.button4.Size = new Size(67, 23);
      this.button4.TabIndex = 150;
      this.button4.Text = "Add";
      this.button4.UseVisualStyleBackColor = true;
      this.button4.Click += new EventHandler(this.button4_Click);
      this.button5.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
      this.button5.Location = new Point(148, 149);
      this.button5.Name = "button5";
      this.button5.Size = new Size(67, 23);
      this.button5.TabIndex = 149;
      this.button5.Text = "Delete";
      this.button5.UseVisualStyleBackColor = true;
      this.button5.Click += new EventHandler(this.button5_Click);
      this.Sleft.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
      this.Sleft.Location = new Point(165, 52);
      this.Sleft.Name = "Sleft";
      this.Sleft.Size = new Size(50, 20);
      this.Sleft.TabIndex = 148;
      this.button6.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
      this.button6.Location = new Point(316, 149);
      this.button6.Name = "button6";
      this.button6.Size = new Size(67, 23);
      this.button6.TabIndex = 147;
      this.button6.Text = "Apply";
      this.button6.UseVisualStyleBackColor = true;
      this.button6.Click += new EventHandler(this.button6_Click);
      this.listBox1.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
      this.listBox1.FormattingEnabled = true;
      this.listBox1.Location = new Point(6, 13);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new Size(97, 160);
      this.listBox1.TabIndex = 146;
      this.listBox1.SelectedIndexChanged += new EventHandler(this.listBox1_SelectedIndexChanged);
      this.ApplySubZoneBtn.Location = new Point(256, 212);
      this.ApplySubZoneBtn.Name = "ApplySubZoneBtn";
      this.ApplySubZoneBtn.Size = new Size(97, 23);
      this.ApplySubZoneBtn.TabIndex = 145;
      this.ApplySubZoneBtn.Text = "ApplyZone";
      this.ApplySubZoneBtn.UseVisualStyleBackColor = true;
      this.ApplySubZoneBtn.Click += new EventHandler(this.ApplySubZoneBtn_Click);
      this.label10.AutoSize = true;
      this.label10.Location = new Point(178, 30);
      this.label10.Name = "label10";
      this.label10.Size = new Size(32, 13);
      this.label10.TabIndex = 144;
      this.label10.Text = "Zone";
      this.zoneid.Location = new Point(256, 27);
      this.zoneid.Name = "zoneid";
      this.zoneid.Size = new Size(97, 20);
      this.zoneid.TabIndex = 143;
      this.label8.AutoSize = true;
      this.label8.Location = new Point(178, 160);
      this.label8.Name = "label8";
      this.label8.Size = new Size(32, 13);
      this.label8.TabIndex = 142;
      this.label8.Text = "Ratio";
      this.fRatio.Location = new Point(256, 157);
      this.fRatio.Name = "fRatio";
      this.fRatio.Size = new Size(97, 20);
      this.fRatio.TabIndex = 141;
      this.nLeft.Location = new Point(256, 53);
      this.nLeft.Name = "nLeft";
      this.nLeft.Size = new Size(97, 20);
      this.nLeft.TabIndex = 133;
      this.label7.AutoSize = true;
      this.label7.Location = new Point(178, 134);
      this.label7.Name = "label7";
      this.label7.Size = new Size(40, 13);
      this.label7.TabIndex = 140;
      this.label7.Text = "Bottom";
      this.nRight.Location = new Point(256, 105);
      this.nRight.Name = "nRight";
      this.nRight.Size = new Size(97, 20);
      this.nRight.TabIndex = 134;
      this.label6.AutoSize = true;
      this.label6.Location = new Point(178, 108);
      this.label6.Name = "label6";
      this.label6.Size = new Size(32, 13);
      this.label6.TabIndex = 139;
      this.label6.Text = "Right";
      this.nTop.Location = new Point(256, 79);
      this.nTop.Name = "nTop";
      this.nTop.Size = new Size(97, 20);
      this.nTop.TabIndex = 135;
      this.label5.AutoSize = true;
      this.label5.Location = new Point(178, 82);
      this.label5.Name = "label5";
      this.label5.Size = new Size(26, 13);
      this.label5.TabIndex = 138;
      this.label5.Text = "Top";
      this.nBottom.Location = new Point(256, 131);
      this.nBottom.Name = "nBottom";
      this.nBottom.Size = new Size(97, 20);
      this.nBottom.TabIndex = 136;
      this.label4.AutoSize = true;
      this.label4.Location = new Point(178, 56);
      this.label4.Name = "label4";
      this.label4.Size = new Size(25, 13);
      this.label4.TabIndex = 137;
      this.label4.Text = "Left";
      this.groupBox1.Controls.Add((Control) this.listBox1);
      this.groupBox1.Controls.Add((Control) this.button6);
      this.groupBox1.Controls.Add((Control) this.Sleft);
      this.groupBox1.Controls.Add((Control) this.button5);
      this.groupBox1.Controls.Add((Control) this.button4);
      this.groupBox1.Controls.Add((Control) this.label23);
      this.groupBox1.Controls.Add((Control) this.Stop);
      this.groupBox1.Controls.Add((Control) this.Sright);
      this.groupBox1.Controls.Add((Control) this.Sbot);
      this.groupBox1.Controls.Add((Control) this.Dleft);
      this.groupBox1.Controls.Add((Control) this.label15);
      this.groupBox1.Controls.Add((Control) this.Dtop);
      this.groupBox1.Controls.Add((Control) this.Dright);
      this.groupBox1.Controls.Add((Control) this.Dbottom);
      this.groupBox1.Controls.Add((Control) this.label16);
      this.groupBox1.Controls.Add((Control) this.label17);
      this.groupBox1.Controls.Add((Control) this.label18);
      this.groupBox1.Controls.Add((Control) this.label19);
      this.groupBox1.Controls.Add((Control) this.DFloatX);
      this.groupBox1.Controls.Add((Control) this.label20);
      this.groupBox1.Controls.Add((Control) this.DFloatY);
      this.groupBox1.Controls.Add((Control) this.DFloatRatio);
      this.groupBox1.Controls.Add((Control) this.label21);
      this.groupBox1.Controls.Add((Control) this.label24);
      this.groupBox1.Controls.Add((Control) this.label25);
      this.groupBox1.Location = new Point(434, 30);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(395, 183);
      this.groupBox1.TabIndex = 194;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "MapZoomRects";
      this.groupBox2.Controls.Add((Control) this.subzones);
      this.groupBox2.Controls.Add((Control) this.button1);
      this.groupBox2.Controls.Add((Control) this.AddSub);
      this.groupBox2.Controls.Add((Control) this.DelSub);
      this.groupBox2.Controls.Add((Control) this.subzoneid);
      this.groupBox2.Controls.Add((Control) this.label13);
      this.groupBox2.Controls.Add((Control) this.SubzoneWidth);
      this.groupBox2.Controls.Add((Control) this.label11);
      this.groupBox2.Controls.Add((Control) this.SubzoneHeight);
      this.groupBox2.Controls.Add((Control) this.label12);
      this.groupBox2.Controls.Add((Control) this.SubzoneType);
      this.groupBox2.Controls.Add((Control) this.label22);
      this.groupBox2.Location = new Point(181, 241);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new Size(302, 193);
      this.groupBox2.TabIndex = 195;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "Unknown? Markers?";
      this.groupBox3.Controls.Add((Control) this.label14);
      this.groupBox3.Controls.Add((Control) this.NUnKnown);
      this.groupBox3.Controls.Add((Control) this.label2);
      this.groupBox3.Controls.Add((Control) this.NpcCoordY);
      this.groupBox3.Controls.Add((Control) this.label9);
      this.groupBox3.Controls.Add((Control) this.NpcIdx);
      this.groupBox3.Controls.Add((Control) this.AddNpcBtn);
      this.groupBox3.Controls.Add((Control) this.DelNpcBtn);
      this.groupBox3.Controls.Add((Control) this.label3);
      this.groupBox3.Controls.Add((Control) this.NpcCoordX);
      this.groupBox3.Controls.Add((Control) this.EditNpcBtn);
      this.groupBox3.Controls.Add((Control) this.npclist);
      this.groupBox3.Location = new Point(527, 241);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Size = new Size(302, 193);
      this.groupBox3.TabIndex = 196;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "Npc's On Map";
      this.label14.AutoSize = true;
      this.label14.Location = new Point(113, 102);
      this.label14.Name = "label14";
      this.label14.Size = new Size(69, 13);
      this.label14.TabIndex = 203;
      this.label14.Text = "UnKnownVal";
      this.NUnKnown.Location = new Point(188, 99);
      this.NUnKnown.Name = "NUnKnown";
      this.NUnKnown.Size = new Size(96, 20);
      this.NUnKnown.TabIndex = 194;
      this.label2.AutoSize = true;
      this.label2.Location = new Point(113, 76);
      this.label2.Name = "label2";
      this.label2.Size = new Size(14, 13);
      this.label2.TabIndex = 202;
      this.label2.Text = "Y";
      this.NpcCoordY.Location = new Point(188, 73);
      this.NpcCoordY.Name = "NpcCoordY";
      this.NpcCoordY.Size = new Size(96, 20);
      this.NpcCoordY.TabIndex = 201;
      this.label9.AutoSize = true;
      this.label9.Location = new Point(113, 22);
      this.label9.Name = "label9";
      this.label9.Size = new Size(56, 13);
      this.label9.TabIndex = 200;
      this.label9.Text = "Npc Index";
      this.NpcIdx.Location = new Point(188, 19);
      this.NpcIdx.Name = "NpcIdx";
      this.NpcIdx.Size = new Size(96, 20);
      this.NpcIdx.TabIndex = 199;
      this.AddNpcBtn.Location = new Point(212, 159);
      this.AddNpcBtn.Name = "AddNpcBtn";
      this.AddNpcBtn.Size = new Size(72, 23);
      this.AddNpcBtn.TabIndex = 198;
      this.AddNpcBtn.Text = "Add";
      this.AddNpcBtn.UseVisualStyleBackColor = true;
      this.AddNpcBtn.Click += new EventHandler(this.AddNpcBtn_Click);
      this.DelNpcBtn.Location = new Point(130, 159);
      this.DelNpcBtn.Name = "DelNpcBtn";
      this.DelNpcBtn.Size = new Size(72, 23);
      this.DelNpcBtn.TabIndex = 197;
      this.DelNpcBtn.Text = "Delete";
      this.DelNpcBtn.UseVisualStyleBackColor = true;
      this.DelNpcBtn.Click += new EventHandler(this.DelNpcBtn_Click);
      this.label3.AutoSize = true;
      this.label3.Location = new Point(113, 50);
      this.label3.Name = "label3";
      this.label3.Size = new Size(14, 13);
      this.label3.TabIndex = 196;
      this.label3.Text = "X";
      this.NpcCoordX.Location = new Point(188, 47);
      this.NpcCoordX.Name = "NpcCoordX";
      this.NpcCoordX.Size = new Size(96, 20);
      this.NpcCoordX.TabIndex = 195;
      this.EditNpcBtn.Location = new Point(130, 132);
      this.EditNpcBtn.Name = "EditNpcBtn";
      this.EditNpcBtn.Size = new Size(154, 23);
      this.EditNpcBtn.TabIndex = 194;
      this.EditNpcBtn.Text = "Apply";
      this.EditNpcBtn.UseVisualStyleBackColor = true;
      this.EditNpcBtn.Click += new EventHandler(this.EditNpcBtn_Click);
      this.npclist.FormattingEnabled = true;
      this.npclist.Location = new Point(10, 22);
      this.npclist.Name = "npclist";
      this.npclist.Size = new Size(97, 160);
      this.npclist.TabIndex = 193;
      this.npclist.SelectedIndexChanged += new EventHandler(this.npclist_SelectedIndexChanged);
      this.label26.AutoSize = true;
      this.label26.Location = new Point(178, 189);
      this.label26.Name = "label26";
      this.label26.Size = new Size(53, 13);
      this.label26.TabIndex = 198;
      this.label26.Text = "Unknown";
      this.ZUnknown.Location = new Point(256, 186);
      this.ZUnknown.Name = "ZUnknown";
      this.ZUnknown.Size = new Size(97, 20);
      this.ZUnknown.TabIndex = 197;
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(829, 433);
      this.Controls.Add((Control) this.label26);
      this.Controls.Add((Control) this.ZUnknown);
      this.Controls.Add((Control) this.groupBox3);
      this.Controls.Add((Control) this.groupBox2);
      this.Controls.Add((Control) this.groupBox1);
      this.Controls.Add((Control) this.ApplySubZoneBtn);
      this.Controls.Add((Control) this.label10);
      this.Controls.Add((Control) this.zoneid);
      this.Controls.Add((Control) this.label8);
      this.Controls.Add((Control) this.fRatio);
      this.Controls.Add((Control) this.nLeft);
      this.Controls.Add((Control) this.label7);
      this.Controls.Add((Control) this.nRight);
      this.Controls.Add((Control) this.label6);
      this.Controls.Add((Control) this.nTop);
      this.Controls.Add((Control) this.label5);
      this.Controls.Add((Control) this.nBottom);
      this.Controls.Add((Control) this.label4);
      this.Controls.Add((Control) this.panel1);
      this.Controls.Add((Control) this.menuStrip1);
      this.FormBorderStyle = FormBorderStyle.FixedSingle;
      this.MainMenuStrip = this.menuStrip1;
      this.Name = nameof (Form1);
      this.Text = "MapDtaEditor";
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.panel1.ResumeLayout(false);
      this.panel1.PerformLayout();
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.groupBox2.ResumeLayout(false);
      this.groupBox2.PerformLayout();
      this.groupBox3.ResumeLayout(false);
      this.groupBox3.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();
    }

    public Form1() => this.InitializeComponent();

    private void fuckYourSelfToolStripMenuItem_Click(object sender, EventArgs e) => this.Close();

    private void openToolStripMenuItem_Click(object sender, EventArgs e)
    {
      this.openDta.Filter = "D(a)ta|*.dta|All|*.*";
      this.openDta.Title = "Save The MapData File";
      int num = (int) this.openDta.ShowDialog();
    }

    private void openDta_FileOk(object sender, CancelEventArgs e)
    {
      LoadFile.LoadFromFile(this.openDta.FileName);
      this.SetZoneList();
    }

    private void saveToolStripMenuItem_Click(object sender, EventArgs e)
    {
      this.saveDta.Filter = "D(a)ta|*.dta|All|*.*";
      this.saveDta.Title = "Save The MapData File";
      int num = (int) this.saveDta.ShowDialog();
    }

    private void saveDta_FileOk(object sender, CancelEventArgs e)
    {
      if (!(this.saveDta.FileName != ""))
        return;
      SaveFile.SaveToFile(this.saveDta.FileName);
    }

    private void SetZoneList()
    {
      this.zones.Items.Clear();
      for (int index = 0; index < LoadFile.MapShit.Count; ++index)
      {
        this.zones.Items.Add((object) (index.ToString() + " - " + LoadFile.MapShit[index].nIndex.ToString()));
        this.zones.Update();
      }
    }

    private void zones_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (this.zones.SelectedIndex == -1)
        return;
      this.npclist.Items.Clear();
      this.subzones.Items.Clear();
      this.listBox1.Items.Clear();
      TextBox zoneid = this.zoneid;
      int num = LoadFile.MapShit[this.zones.SelectedIndex].nIndex;
      string str1 = num.ToString();
      zoneid.Text = str1;
      TextBox nLeft = this.nLeft;
      num = LoadFile.MapShit[this.zones.SelectedIndex].nLeft;
      string str2 = num.ToString();
      nLeft.Text = str2;
      TextBox nTop = this.nTop;
      num = LoadFile.MapShit[this.zones.SelectedIndex].nTop;
      string str3 = num.ToString();
      nTop.Text = str3;
      TextBox nRight = this.nRight;
      num = LoadFile.MapShit[this.zones.SelectedIndex].nRight;
      string str4 = num.ToString();
      nRight.Text = str4;
      TextBox nBottom = this.nBottom;
      num = LoadFile.MapShit[this.zones.SelectedIndex].nBottom;
      string str5 = num.ToString();
      nBottom.Text = str5;
      this.fRatio.Text = LoadFile.MapShit[this.zones.SelectedIndex].fRatio.ToString();
      this.ZUnknown.Text = LoadFile.MapShit[this.zones.SelectedIndex].unknown.ToString();
      if (LoadFile.MapShit[this.zones.SelectedIndex].sbDetailCount > (sbyte) 0)
      {
        for (int index = 0; index < LoadFile.MapShit[this.zones.SelectedIndex].DetailZones.Count; ++index)
        {
          this.listBox1.Items.Add((object) index);
          this.listBox1.Update();
        }
      }
      if (LoadFile.MapShit[this.zones.SelectedIndex].sbSubZoneCount > (sbyte) 0)
      {
        for (int index = 0; index < LoadFile.MapShit[this.zones.SelectedIndex].SubData.Count; ++index)
        {
          ListBox.ObjectCollection items = this.subzones.Items;
          string str6 = index.ToString();
          num = LoadFile.MapShit[this.zones.SelectedIndex].SubData[index].nIndex;
          string str7 = num.ToString();
          string str8 = str6 + " - " + str7;
          items.Add((object) str8);
          this.subzones.Update();
        }
      }
      if (LoadFile.MapShit[this.zones.SelectedIndex].NpcCount <= 0)
        return;
      for (int index = 0; index < LoadFile.MapShit[this.zones.SelectedIndex].NpcData.Count; ++index)
      {
        ListBox.ObjectCollection items = this.npclist.Items;
        string str9 = index.ToString();
        num = LoadFile.MapShit[this.zones.SelectedIndex].NpcData[index].nIndex;
        string str10 = num.ToString();
        string str11 = str9 + " - " + str10;
        items.Add((object) str11);
        this.npclist.Update();
      }
    }

    private void ApplySubZoneBtn_Click(object sender, EventArgs e)
    {
      try
      {
        LoadFile.MapShit[this.zones.SelectedIndex].nIndex = Convert.ToInt32(this.zoneid.Text);
        LoadFile.MapShit[this.zones.SelectedIndex].nLeft = Convert.ToInt32(this.nLeft.Text);
        LoadFile.MapShit[this.zones.SelectedIndex].nTop = Convert.ToInt32(this.nTop.Text);
        LoadFile.MapShit[this.zones.SelectedIndex].nRight = Convert.ToInt32(this.nRight.Text);
        LoadFile.MapShit[this.zones.SelectedIndex].nBottom = Convert.ToInt32(this.nBottom.Text);
        LoadFile.MapShit[this.zones.SelectedIndex].fRatio = Convert.ToSingle(this.fRatio.Text);
        LoadFile.MapShit[this.zones.SelectedIndex].unknown = Convert.ToInt64(this.ZUnknown.Text);
        ListBox.ObjectCollection items = this.zones.Items;
        int selectedIndex = this.zones.SelectedIndex;
        int num = this.zones.SelectedIndex;
        string str1 = num.ToString();
        num = LoadFile.MapShit[this.zones.SelectedIndex].nIndex;
        string str2 = num.ToString();
        string str3 = str1 + " - " + str2;
        items[selectedIndex] = (object) str3;
        this.zones.Update();
      }
      catch (Exception ex)
      {
        int num = (int) new Error(ex.Message + "\n \n" + ex.StackTrace).ShowDialog();
      }
    }

    private void DelZone_Click(object sender, EventArgs e)
    {
      if (this.zones.SelectedIndex == -1)
        return;
      LoadFile.MapShit.RemoveAt(this.zones.SelectedIndex);
      this.zones.Items.RemoveAt(this.zones.SelectedIndex);
      this.zones.Update();
    }

    private void AddZone_Click(object sender, EventArgs e)
    {
      LoadFile.MapShit.Add(new MapDataS()
      {
        DetailZones = new List<MapDetail>(),
        SubData = new List<SubZones>(),
        NpcData = new List<NpcData>(),
        nIndex = 0,
        sbLayer = (sbyte) 0,
        nLeft = 0,
        nTop = 0,
        nRight = 0,
        nBottom = 0,
        fRatio = 0.0f,
        unknown = 0L,
        sbDetailCount = (sbyte) 0,
        sbSubZoneCount = (sbyte) 0,
        NpcCount = 0
      });
      if (this.zones.Items.Count > 0)
      {
        int num = this.zones.Items.Count - 1;
        this.zones.Items.Add((object) ((num + 1).ToString() + " - " + LoadFile.MapShit[num + 1].nIndex.ToString()));
        this.zones.Update();
      }
      else
      {
        int index = 0;
        this.zones.Items.Add((object) (index.ToString() + " - " + LoadFile.MapShit[index].nIndex.ToString()));
        this.zones.Update();
      }
    }

    private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (this.listBox1.SelectedIndex == -1)
        return;
      this.Sleft.Text = LoadFile.MapShit[this.zones.SelectedIndex].DetailZones[this.listBox1.SelectedIndex].nSelLeft.ToString();
      this.Stop.Text = LoadFile.MapShit[this.zones.SelectedIndex].DetailZones[this.listBox1.SelectedIndex].nSelTop.ToString();
      this.Sright.Text = LoadFile.MapShit[this.zones.SelectedIndex].DetailZones[this.listBox1.SelectedIndex].nSelRight.ToString();
      this.Sbot.Text = LoadFile.MapShit[this.zones.SelectedIndex].DetailZones[this.listBox1.SelectedIndex].nSelBottom.ToString();
      this.Dleft.Text = LoadFile.MapShit[this.zones.SelectedIndex].DetailZones[this.listBox1.SelectedIndex].nLeft.ToString();
      this.Dtop.Text = LoadFile.MapShit[this.zones.SelectedIndex].DetailZones[this.listBox1.SelectedIndex].nTop.ToString();
      this.Dright.Text = LoadFile.MapShit[this.zones.SelectedIndex].DetailZones[this.listBox1.SelectedIndex].nRight.ToString();
      this.Dbottom.Text = LoadFile.MapShit[this.zones.SelectedIndex].DetailZones[this.listBox1.SelectedIndex].nBottom.ToString();
      this.DFloatX.Text = LoadFile.MapShit[this.zones.SelectedIndex].DetailZones[this.listBox1.SelectedIndex].fX.ToString();
      this.DFloatY.Text = LoadFile.MapShit[this.zones.SelectedIndex].DetailZones[this.listBox1.SelectedIndex].fZ.ToString();
      this.DFloatRatio.Text = LoadFile.MapShit[this.zones.SelectedIndex].DetailZones[this.listBox1.SelectedIndex].fRatio.ToString();
    }

    private void button6_Click(object sender, EventArgs e)
    {
      try
      {
        if (this.listBox1.SelectedIndex == -1)
          return;
        int selectedIndex1 = this.listBox1.SelectedIndex;
        int selectedIndex2 = this.zones.SelectedIndex;
        LoadFile.MapShit[selectedIndex2].DetailZones[selectedIndex1].nSelLeft = Convert.ToInt32(this.nLeft.Text);
        LoadFile.MapShit[selectedIndex2].DetailZones[selectedIndex1].nSelLeft = Convert.ToInt32(this.Sleft.Text);
        LoadFile.MapShit[selectedIndex2].DetailZones[selectedIndex1].nSelTop = Convert.ToInt32(this.Stop.Text);
        LoadFile.MapShit[selectedIndex2].DetailZones[selectedIndex1].nSelRight = Convert.ToInt32(this.Sright.Text);
        LoadFile.MapShit[selectedIndex2].DetailZones[selectedIndex1].nSelBottom = Convert.ToInt32(this.Sbot.Text);
        LoadFile.MapShit[selectedIndex2].DetailZones[selectedIndex1].nLeft = Convert.ToInt32(this.Dleft.Text);
        LoadFile.MapShit[selectedIndex2].DetailZones[selectedIndex1].nTop = Convert.ToInt32(this.Dtop.Text);
        LoadFile.MapShit[selectedIndex2].DetailZones[selectedIndex1].nRight = Convert.ToInt32(this.Dright.Text);
        LoadFile.MapShit[selectedIndex2].DetailZones[selectedIndex1].nBottom = Convert.ToInt32(this.Dbottom.Text);
        LoadFile.MapShit[selectedIndex2].DetailZones[selectedIndex1].fRatio = Convert.ToSingle(this.DFloatRatio.Text);
        LoadFile.MapShit[selectedIndex2].DetailZones[selectedIndex1].fX = Convert.ToSingle(this.DFloatX.Text);
        LoadFile.MapShit[selectedIndex2].DetailZones[selectedIndex1].fZ = Convert.ToSingle(this.DFloatY.Text);
      }
      catch (Exception ex)
      {
        int num = (int) new Error(ex.Message + "\n \n" + ex.StackTrace).ShowDialog();
      }
    }

    private void button5_Click(object sender, EventArgs e)
    {
      if (this.listBox1.SelectedIndex == -1)
        return;
      int selectedIndex = this.zones.SelectedIndex;
      LoadFile.MapShit[selectedIndex].DetailZones.RemoveAt(this.listBox1.SelectedIndex);
      LoadFile.MapShit[selectedIndex].sbDetailCount = Convert.ToSByte(LoadFile.MapShit[selectedIndex].DetailZones.Count);
      this.listBox1.Items.RemoveAt(this.listBox1.SelectedIndex);
      this.listBox1.Update();
    }

    private void button4_Click(object sender, EventArgs e)
    {
      MapDetail mapDetail = new MapDetail();
      int selectedIndex = this.zones.SelectedIndex;
      mapDetail.nSelLeft = 0;
      mapDetail.nSelTop = 0;
      mapDetail.nSelRight = 0;
      mapDetail.nSelBottom = 0;
      mapDetail.nLeft = 0;
      mapDetail.nTop = 0;
      mapDetail.nRight = 0;
      mapDetail.nBottom = 0;
      mapDetail.fRatio = 0.0f;
      mapDetail.fX = 0.0f;
      mapDetail.fZ = 0.0f;
      LoadFile.MapShit[selectedIndex].DetailZones.Add(mapDetail);
      LoadFile.MapShit[selectedIndex].sbDetailCount = Convert.ToSByte(LoadFile.MapShit[selectedIndex].DetailZones.Count);
      if (this.listBox1.Items.Count > 0)
      {
        this.listBox1.Items.Add((object) (this.listBox1.Items.Count - 1 + 1));
        this.listBox1.Update();
      }
      else
      {
        this.listBox1.Items.Add((object) 0);
        this.listBox1.Update();
      }
    }

    private void subzones_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (this.subzones.SelectedIndex == -1)
        return;
      this.SubzoneWidth.Text = LoadFile.MapShit[this.zones.SelectedIndex].SubData[this.subzones.SelectedIndex].fX.ToString();
      this.SubzoneHeight.Text = LoadFile.MapShit[this.zones.SelectedIndex].SubData[this.subzones.SelectedIndex].fZ.ToString();
      this.subzoneid.Text = LoadFile.MapShit[this.zones.SelectedIndex].SubData[this.subzones.SelectedIndex].nIndex.ToString();
      this.SubzoneType.Text = LoadFile.MapShit[this.zones.SelectedIndex].SubData[this.subzones.SelectedIndex].sbtype.ToString();
    }

    private void button1_Click(object sender, EventArgs e)
    {
      try
      {
        if (this.subzones.SelectedIndex == -1)
          return;
        int selectedIndex1 = this.subzones.SelectedIndex;
        int selectedIndex2 = this.zones.SelectedIndex;
        LoadFile.MapShit[selectedIndex2].SubData[selectedIndex1].nIndex = Convert.ToInt32(this.subzoneid.Text);
        LoadFile.MapShit[selectedIndex2].SubData[selectedIndex1].fX = Convert.ToSingle(this.SubzoneWidth.Text);
        LoadFile.MapShit[selectedIndex2].SubData[selectedIndex1].fZ = Convert.ToSingle(this.SubzoneHeight.Text);
        LoadFile.MapShit[selectedIndex2].SubData[selectedIndex1].sbtype = Convert.ToSByte(this.SubzoneType.Text);
        this.subzones.Items[selectedIndex1] = (object) (selectedIndex1.ToString() + " - " + LoadFile.MapShit[selectedIndex2].SubData[selectedIndex1].nIndex.ToString());
        this.subzones.Update();
      }
      catch (Exception ex)
      {
        int num = (int) new Error(ex.Message + "\n \n" + ex.StackTrace).ShowDialog();
      }
    }

    private void DelSub_Click(object sender, EventArgs e)
    {
      if (this.subzones.SelectedIndex == -1)
        return;
      int selectedIndex = this.zones.SelectedIndex;
      LoadFile.MapShit[this.zones.SelectedIndex].SubData.RemoveAt(this.subzones.SelectedIndex);
      LoadFile.MapShit[selectedIndex].sbSubZoneCount = Convert.ToSByte(LoadFile.MapShit[selectedIndex].SubData.Count);
      this.subzones.Items.RemoveAt(this.subzones.SelectedIndex);
      this.subzones.Update();
    }

    private void AddSub_Click(object sender, EventArgs e)
    {
      SubZones subZones = new SubZones();
      int selectedIndex = this.zones.SelectedIndex;
      subZones.nIndex = 0;
      subZones.fX = 0.0f;
      subZones.fZ = 0.0f;
      subZones.sbtype = (sbyte) 0;
      LoadFile.MapShit[selectedIndex].SubData.Add(subZones);
      LoadFile.MapShit[selectedIndex].sbSubZoneCount = Convert.ToSByte(LoadFile.MapShit[selectedIndex].SubData.Count);
      if (this.subzones.Items.Count > 0)
      {
        int num = this.subzones.Items.Count - 1;
        this.subzones.Items.Add((object) ((num + 1).ToString() + " - " + LoadFile.MapShit[selectedIndex].SubData[num + 1].nIndex.ToString()));
        this.subzones.Update();
      }
      else
      {
        int index = 0;
        this.subzones.Items.Add((object) (index.ToString() + " - " + LoadFile.MapShit[selectedIndex].SubData[index].nIndex.ToString()));
        this.subzones.Update();
      }
    }

    private void npclist_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (this.npclist.SelectedIndex == -1)
        return;
      this.NpcCoordX.Text = LoadFile.MapShit[this.zones.SelectedIndex].NpcData[this.npclist.SelectedIndex].fX.ToString();
      this.NpcCoordY.Text = LoadFile.MapShit[this.zones.SelectedIndex].NpcData[this.npclist.SelectedIndex].fZ.ToString();
      this.NpcIdx.Text = LoadFile.MapShit[this.zones.SelectedIndex].NpcData[this.npclist.SelectedIndex].nIndex.ToString();
      this.NUnKnown.Text = LoadFile.MapShit[this.zones.SelectedIndex].NpcData[this.npclist.SelectedIndex].Unknown.ToString();
    }

    private void EditNpcBtn_Click(object sender, EventArgs e)
    {
      try
      {
        if (this.npclist.SelectedIndex == -1)
          return;
        int selectedIndex1 = this.npclist.SelectedIndex;
        int selectedIndex2 = this.zones.SelectedIndex;
        LoadFile.MapShit[selectedIndex2].NpcData[selectedIndex1].nIndex = Convert.ToInt32(this.NpcIdx.Text);
        LoadFile.MapShit[selectedIndex2].NpcData[selectedIndex1].fX = Convert.ToSingle(this.NpcCoordX.Text);
        LoadFile.MapShit[selectedIndex2].NpcData[selectedIndex1].fZ = Convert.ToSingle(this.NpcCoordY.Text);
        LoadFile.MapShit[selectedIndex2].NpcData[selectedIndex1].Unknown = Convert.ToInt32(this.NUnKnown.Text);
        this.npclist.Items[selectedIndex1] = (object) (selectedIndex1.ToString() + " - " + LoadFile.MapShit[selectedIndex2].NpcData[selectedIndex1].nIndex.ToString());
        this.npclist.Update();
      }
      catch (Exception ex)
      {
        int num = (int) new Error(ex.Message + "\n \n" + ex.StackTrace).ShowDialog();
      }
    }

    private void DelNpcBtn_Click(object sender, EventArgs e)
    {
      if (this.npclist.SelectedIndex == -1)
        return;
      int selectedIndex = this.zones.SelectedIndex;
      LoadFile.MapShit[selectedIndex].NpcData.RemoveAt(this.npclist.SelectedIndex);
      LoadFile.MapShit[selectedIndex].NpcCount = Convert.ToInt32(LoadFile.MapShit[selectedIndex].NpcData.Count);
      this.npclist.Items.RemoveAt(this.npclist.SelectedIndex);
      this.npclist.Update();
    }

    private void AddNpcBtn_Click(object sender, EventArgs e)
    {
      NpcData npcData = new NpcData();
      int selectedIndex = this.zones.SelectedIndex;
      npcData.nIndex = 0;
      npcData.fX = 0.0f;
      npcData.fZ = 0.0f;
      npcData.Unknown = 0;
      LoadFile.MapShit[selectedIndex].NpcData.Add(npcData);
      LoadFile.MapShit[selectedIndex].NpcCount = Convert.ToInt32(LoadFile.MapShit[selectedIndex].NpcData.Count);
      if (this.npclist.Items.Count > 0)
      {
        int num = this.npclist.Items.Count - 1;
        this.npclist.Items.Add((object) ((num + 1).ToString() + " - " + LoadFile.MapShit[selectedIndex].NpcData[num + 1].nIndex.ToString()));
        this.npclist.Update();
      }
      else
      {
        int index = 0;
        this.npclist.Items.Add((object) (index.ToString() + " - " + LoadFile.MapShit[selectedIndex].NpcData[index].nIndex.ToString()));
        this.npclist.Update();
      }
    }
  }
}
