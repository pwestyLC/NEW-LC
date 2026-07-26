// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.MobEditor
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
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker
{
  public class MobEditor : Form
  {
    private IContainer components = (IContainer) null;
    private MenuStrip menuStrip1;
    private ToolStripMenuItem fileToolStripMenuItem;
    private ToolStripMenuItem importFromDatabaseToolStripMenuItem;
    private ToolStripMenuItem saveToolStripMenuItem;
    private ToolStripMenuItem exportToolStripMenuItem;
    private ToolStripMenuItem moballlodToolStripMenuItem;
    private ToolStripMenuItem strToolStripMenuItem;
    private ToolStripMenuItem extraToolStripMenuItem;
    private GroupBox groupBox1;
    private GroupBox groupBox2;
    private ListBox listBox1;
    private StatusStrip statusStrip1;
    private Button btnDelete;
    private Button btnCopy;
    private TextBox textBox1;
    private TabControl tabControl1;
    private TabPage tabPage1;
    private TabPage tabPage2;
    private Button btnSave;
    private GroupBox groupBox3;
    private Label label1;
    private TextBox txtIndex;
    private CheckBox checkBoxEnable;
    private TextBox txtName;
    private Label label2;
    private GroupBox groupBox4;
    private TextBox txtFamily;
    private TextBox txtskillmaster;
    private TextBox txtFlag;
    private TextBox txtFlag1;
    private Label label3;
    private Label label4;
    private Label label6;
    private Label label5;
    private GroupBox groupBox5;
    private TextBox txtStateFlag;
    private Label label7;
    private Label label9;
    private TextBox txtExp;
    private Label label8;
    private TextBox txtLevel;
    private Label label10;
    private TextBox txtGold;
    private Label label13;
    private TextBox txtSize;
    private Label label11;
    private TextBox txtSight;
    private Label label12;
    private TextBox txtSkillPoint;
    private Label label14;
    private Label label15;
    private TextBox txtAttackArea;
    private TextBox txtMoveArea;
    private Label label16;
    private Label label17;
    private TextBox txtRunSpeed;
    private TextBox txtWalkSpeed;
    private GroupBox groupBox6;
    private TabPage tabPage3;
    private TabPage tabPage4;
    private TabPage tabPage5;
    private Label label18;
    private Label label21;
    private Label label20;
    private Label label19;
    private Label label22;
    private TextBox txtAttack;
    private Label label23;
    private TextBox txtMagic;
    private Label label25;
    private TextBox txtResist;
    private Label label24;
    private TextBox txtDefense;
    private GroupBox groupBox7;
    private GroupBox groupBox8;
    private GroupBox groupBox9;
    private TextBox txtDefenseLevel;
    private TextBox txtAttackLevel;
    private Label label26;
    private Label label27;
    private TextBox txtMP;
    private Label label28;
    private Label label29;
    private TextBox txtHP;
    private GroupBox groupBox10;
    private Label label30;
    private Label label31;
    private TextBox txtRecoverHP;
    private TextBox txtRecoverMP;
    private GroupBox groupBox11;
    private Label label33;
    private TextBox txtSkill1;
    private Label label32;
    private TextBox txtSkill0;
    private Label label34;
    private TextBox txtSkill3;
    private Label label35;
    private TextBox txtSkill2;
    private TabPage tabPage6;
    private GroupBox groupBox12;
    private TextBox txtMagicAvoid;
    private TextBox txtHit;
    private Label label36;
    private Label label37;
    private TextBox txtJobAttribute;
    private Label label38;
    private Label label39;
    private TextBox txtDodge;
    private TabPage tabPage7;
    private GroupBox groupBox13;
    private TextBox txtAttackType;
    private Label label40;
    private TextBox txtAttackSpeed;
    private Label label41;
    private Label label42;
    private TextBox txtsskillmaster;
    private NumericUpDown txtStr;
    private NumericUpDown txtDex;
    private NumericUpDown txtInt;
    private NumericUpDown txtCon;
    private ToolStripProgressBar toolStripProgressBar1;
    private ToolStripStatusLabel toolStripStatusLabel1;
    private PictureBox pictureBox23;
    private PictureBox pictureBox1;

    public MobEditor() => this.InitializeComponent();

    private void importFromDatabaseToolStripMenuItem_Click(object sender, EventArgs e)
    {
      new LoadFromDatabase().tnpc_Import();
      this.MakeList();
      this.checkListEmpty();
    }

    public void MakeList()
    {
      List<string> stringList = new List<string>();
      List<tnpc> all = AllLists.tnpc_MenuData.FindAll((Predicate<tnpc>) (p => p.name.ToLower().Contains(this.textBox1.Text.ToLower())));
      for (int index = 0; index < all.Count<tnpc>(); ++index)
        stringList.Add(all[index].index.ToString() + " - " + all[index].name.ToString());
      this.listBox1.Items.Clear();
      this.listBox1.Items.AddRange((object[]) stringList.ToArray());
    }

    private void Form1_Load(object sender, EventArgs e)
    {
      mySQL.SetConnection();
      this.checkListEmpty();
    }

    private void checkListEmpty()
    {
      if (AllLists.tnpc_MenuData.Count<tnpc>() == 0)
      {
        this.saveToolStripMenuItem.Enabled = false;
        this.tabControl1.Enabled = false;
      }
      else
      {
        this.saveToolStripMenuItem.Enabled = true;
        this.tabControl1.Enabled = true;
      }
    }

    private int GetID()
    {
      int result = -1;
      int.TryParse(this.listBox1.Text.Split(' ')[0], out result);
      return result;
    }

    private void btnSave_Click(object sender, EventArgs e)
    {
      int NpcID = this.GetID();
      if (NpcID == -1)
        return;
      tnpc tnpc = AllLists.tnpc_MenuData.Find((Predicate<tnpc>) (p => p.index.Equals(NpcID)));
      tnpc.name = Convert.ToString(this.txtName.Text);
      tnpc.family = Convert.ToInt32(this.txtFamily.Text);
      tnpc.skillmaster = Convert.ToInt32(this.txtskillmaster.Text);
      tnpc.flag = Convert.ToInt32(this.txtFlag.Text);
      tnpc.flag1 = Convert.ToInt32(this.txtFlag1.Text);
      tnpc.stateflag = Convert.ToInt32(this.txtStateFlag.Text);
      tnpc.level = Convert.ToInt32(this.txtLevel.Text);
      tnpc.exp = Convert.ToInt32(this.txtExp.Text);
      tnpc.prize = Convert.ToInt32(this.txtGold.Text);
      tnpc.sight = Convert.ToInt32(this.txtSight.Text);
      tnpc.size = Convert.ToSingle(this.txtSize.Text);
      tnpc.movearea = Convert.ToInt32(this.txtMoveArea.Text);
      tnpc.attackarea = Convert.ToSingle(this.txtAttackArea.Text);
      tnpc.skillpoint = Convert.ToInt32(this.txtSkillPoint.Text);
      tnpc.sskillmaster = Convert.ToInt32(this.txtsskillmaster.Text);
      tnpc.str = Convert.ToInt32(this.txtStr.Value);
      tnpc.dex = Convert.ToInt32(this.txtDex.Value);
      tnpc.INT = Convert.ToInt32(this.txtInt.Value);
      tnpc.con = Convert.ToInt32(this.txtCon.Value);
      tnpc.attack = Convert.ToInt32(this.txtAttack.Text);
      tnpc.magic = Convert.ToInt32(this.txtMagic.Text);
      tnpc.defense = Convert.ToInt32(this.txtDefense.Text);
      tnpc.resist = Convert.ToInt32(this.txtResist.Text);
      tnpc.attacklevel = Convert.ToInt32(this.txtAttackLevel.Text);
      tnpc.defenselevel = Convert.ToInt32(this.txtDefenseLevel.Text);
      tnpc.hp = Convert.ToInt32(this.txtHP.Text);
      tnpc.mp = Convert.ToInt32(this.txtMP.Text);
      tnpc.attacktype = Convert.ToInt32(this.txtAttackType.Text);
      tnpc.attackspeed = Convert.ToInt32(this.txtAttackSpeed.Text);
      tnpc.recoverhp = Convert.ToInt32(this.txtRecoverHP.Text);
      tnpc.recovermp = Convert.ToInt32(this.txtRecoverMP.Text);
      tnpc.walkspeed = (float) Convert.ToInt32(this.txtWalkSpeed.Text);
      tnpc.runspeed = (float) Convert.ToInt32(this.txtRunSpeed.Text);
      tnpc.skill0 = Convert.ToString(this.txtSkill0.Text);
      tnpc.skill1 = Convert.ToString(this.txtSkill1.Text);
      tnpc.skill2 = Convert.ToString(this.txtSkill2.Text);
      tnpc.skill3 = Convert.ToString(this.txtSkill3.Text);
      tnpc.dodge = Convert.ToInt32(this.txtDodge.Text);
      tnpc.magicavoid = Convert.ToInt32(this.txtMagicAvoid.Text);
      tnpc.hit = Convert.ToInt32(this.txtHit.Text);
      tnpc.jobattribute = Convert.ToInt32(this.txtJobAttribute.Text);
    }

    private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      int NpcID = this.GetID();
      if (NpcID == -1)
        return;
      tnpc tnpc = AllLists.tnpc_MenuData.Find((Predicate<tnpc>) (p => p.index.Equals(NpcID)));
      if (tnpc == null)
        return;
      this.CheckParameter(tnpc.enable);
      this.txtIndex.Text = tnpc.index.ToString();
      this.txtName.Text = tnpc.name.ToString();
      this.checkBoxEnable.Checked = tnpc.enable == 1;
      this.txtFamily.Text = tnpc.family.ToString();
      this.txtskillmaster.Text = tnpc.skillmaster.ToString();
      this.txtFlag.Text = tnpc.flag.ToString();
      this.txtFlag1.Text = tnpc.flag1.ToString();
      this.txtStateFlag.Text = tnpc.stateflag.ToString();
      this.txtLevel.Text = tnpc.level.ToString();
      this.txtExp.Text = tnpc.exp.ToString();
      this.txtGold.Text = tnpc.prize.ToString();
      this.txtSight.Text = tnpc.sight.ToString();
      this.txtSize.Text = tnpc.size.ToString();
      this.txtMoveArea.Text = tnpc.movearea.ToString();
      this.txtAttackArea.Text = tnpc.attackarea.ToString();
      this.txtSkillPoint.Text = tnpc.skillpoint.ToString();
      this.txtsskillmaster.Text = tnpc.sskillmaster.ToString();
      this.txtStr.Text = tnpc.str.ToString();
      this.txtDex.Text = tnpc.dex.ToString();
      this.txtInt.Text = tnpc.INT.ToString();
      this.txtCon.Text = tnpc.con.ToString();
      this.txtAttack.Text = tnpc.attack.ToString();
      this.txtMagic.Text = tnpc.magic.ToString();
      this.txtDefense.Text = tnpc.defense.ToString();
      this.txtResist.Text = tnpc.resist.ToString();
      this.txtAttackLevel.Text = tnpc.attacklevel.ToString();
      this.txtDefenseLevel.Text = tnpc.defenselevel.ToString();
      this.txtHP.Text = tnpc.hp.ToString();
      this.txtMP.Text = tnpc.mp.ToString();
      this.txtAttackType.Text = tnpc.attacktype.ToString();
      this.txtAttackSpeed.Text = tnpc.attackspeed.ToString();
      this.txtRecoverHP.Text = tnpc.recoverhp.ToString();
      this.txtRecoverMP.Text = tnpc.recovermp.ToString();
      this.txtWalkSpeed.Text = tnpc.walkspeed.ToString();
      this.txtRunSpeed.Text = tnpc.runspeed.ToString();
      this.txtSkill0.Text = tnpc.skill0.ToString();
      this.txtSkill1.Text = tnpc.skill1.ToString();
      this.txtSkill2.Text = tnpc.skill2.ToString();
      this.txtSkill3.Text = tnpc.skill3.ToString();
      this.txtDodge.Text = tnpc.dodge.ToString();
      this.txtMagicAvoid.Text = tnpc.magicavoid.ToString();
      this.txtHit.Text = tnpc.hit.ToString();
      this.txtJobAttribute.Text = tnpc.jobattribute.ToString();
    }

    private void CheckParameter(int checkbox)
    {
      if (checkbox == 1)
        this.checkBoxEnable.BackColor = Color.Lime;
      else
        this.checkBoxEnable.BackColor = Color.Red;
    }

    private void saveToolStripMenuItem_Click(object sender, EventArgs e)
    {
      mySQL.UpdateQuery("DELETE FROM t_npc");
      int num = AllLists.tnpc_MenuData.Count<tnpc>();
      this.toolStripProgressBar1.Visible = true;
      for (int index = 0; index < AllLists.tnpc_MenuData.Count<tnpc>(); ++index)
      {
        DatabaseUpdate.tnpc_Update(AllLists.tnpc_MenuData[index]);
        this.toolStripProgressBar1.Value = 100 * (index + 1) / num;
      }
      this.toolStripProgressBar1.Value = 0;
      this.toolStripProgressBar1.Visible = false;
    }

    private void moballlodToolStripMenuItem_Click(object sender, EventArgs e)
    {
      new ExportLodHandle().ExportMobAll_V4();
    }

    private void strToolStripMenuItem_Click(object sender, EventArgs e)
    {
    }

    private void btnCopy_Click(object sender, EventArgs e)
    {
      int NpcID = this.GetID();
      if (NpcID == -1)
        return;
      tnpc tnpc = AllLists.tnpc_MenuData.Find((Predicate<tnpc>) (p => p.index == NpcID)).Clone();
      tnpc.index = AllLists.tnpc_MenuData.Max<tnpc>((Func<tnpc, int>) (p => p.index)) + 1;
      tnpc.name += " (copy)";
      AllLists.tnpc_MenuData.Add(tnpc);
      string str = tnpc.index.ToString() + " - " + tnpc.name.ToString();
      AllLists.tnpc_Menu.Add(str);
      this.listBox1.Items.Add((object) str);
      this.listBox1.SelectedIndex = this.listBox1.Items.Count - 1;
    }

    private void textBox1_TextChanged(object sender, EventArgs e) => this.MakeList();

    private void btnDelete_Click(object sender, EventArgs e)
    {
      int NpcID = this.GetID();
      if (NpcID == -1)
        return;
      string text = this.listBox1.Text;
      this.listBox1.Items.RemoveAt(this.listBox1.SelectedIndex);
      AllLists.tnpc_Menu.Remove(text);
      AllLists.tnpc_MenuData.RemoveAll((Predicate<tnpc>) (p => p.index == NpcID));
    }

    private void pictureBox23_Click(object sender, EventArgs e)
    {
      FlagBuilder flagBuilder = new FlagBuilder();
      flagBuilder.flagSmall = Convert.ToInt32(this.txtFlag.Text);
      flagBuilder.flagBuilderType = "npcs";
      if (flagBuilder.ShowDialog() != DialogResult.OK)
        return;
      this.txtFlag.Text = flagBuilder.flagSmall.ToString();
    }

    private void pictureBox1_Click(object sender, EventArgs e)
    {
      FlagBuilder flagBuilder = new FlagBuilder();
      flagBuilder.flagSmall = Convert.ToInt32(this.txtFlag1.Text);
      flagBuilder.flagBuilderType = "npcs";
      if (flagBuilder.ShowDialog() != DialogResult.OK)
        return;
      this.txtFlag1.Text = flagBuilder.flagSmall.ToString();
    }

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
      this.importFromDatabaseToolStripMenuItem = new ToolStripMenuItem();
      this.saveToolStripMenuItem = new ToolStripMenuItem();
      this.exportToolStripMenuItem = new ToolStripMenuItem();
      this.moballlodToolStripMenuItem = new ToolStripMenuItem();
      this.strToolStripMenuItem = new ToolStripMenuItem();
      this.extraToolStripMenuItem = new ToolStripMenuItem();
      this.groupBox1 = new GroupBox();
      this.textBox1 = new TextBox();
      this.groupBox2 = new GroupBox();
      this.btnDelete = new Button();
      this.btnCopy = new Button();
      this.listBox1 = new ListBox();
      this.statusStrip1 = new StatusStrip();
      this.toolStripStatusLabel1 = new ToolStripStatusLabel();
      this.toolStripProgressBar1 = new ToolStripProgressBar();
      this.tabControl1 = new TabControl();
      this.tabPage1 = new TabPage();
      this.groupBox6 = new GroupBox();
      this.groupBox13 = new GroupBox();
      this.txtAttackType = new TextBox();
      this.label40 = new Label();
      this.txtAttackSpeed = new TextBox();
      this.label41 = new Label();
      this.groupBox12 = new GroupBox();
      this.txtMagicAvoid = new TextBox();
      this.txtHit = new TextBox();
      this.label36 = new Label();
      this.label37 = new Label();
      this.txtJobAttribute = new TextBox();
      this.label38 = new Label();
      this.label39 = new Label();
      this.txtDodge = new TextBox();
      this.groupBox11 = new GroupBox();
      this.label34 = new Label();
      this.label33 = new Label();
      this.txtSkill3 = new TextBox();
      this.label35 = new Label();
      this.txtSkill1 = new TextBox();
      this.txtSkill2 = new TextBox();
      this.label32 = new Label();
      this.txtSkill0 = new TextBox();
      this.groupBox10 = new GroupBox();
      this.label30 = new Label();
      this.label31 = new Label();
      this.txtRecoverHP = new TextBox();
      this.txtRecoverMP = new TextBox();
      this.label26 = new Label();
      this.label29 = new Label();
      this.txtHP = new TextBox();
      this.txtMP = new TextBox();
      this.groupBox9 = new GroupBox();
      this.txtDefenseLevel = new TextBox();
      this.txtAttackLevel = new TextBox();
      this.label27 = new Label();
      this.label28 = new Label();
      this.groupBox8 = new GroupBox();
      this.txtMagic = new TextBox();
      this.txtAttack = new TextBox();
      this.label25 = new Label();
      this.label22 = new Label();
      this.txtResist = new TextBox();
      this.label23 = new Label();
      this.label24 = new Label();
      this.txtDefense = new TextBox();
      this.groupBox7 = new GroupBox();
      this.txtCon = new NumericUpDown();
      this.txtInt = new NumericUpDown();
      this.txtDex = new NumericUpDown();
      this.txtStr = new NumericUpDown();
      this.label18 = new Label();
      this.label19 = new Label();
      this.label20 = new Label();
      this.label21 = new Label();
      this.groupBox5 = new GroupBox();
      this.label16 = new Label();
      this.label17 = new Label();
      this.txtRunSpeed = new TextBox();
      this.txtWalkSpeed = new TextBox();
      this.label14 = new Label();
      this.label15 = new Label();
      this.txtAttackArea = new TextBox();
      this.txtMoveArea = new TextBox();
      this.groupBox4 = new GroupBox();
      this.pictureBox1 = new PictureBox();
      this.pictureBox23 = new PictureBox();
      this.label7 = new Label();
      this.txtStateFlag = new TextBox();
      this.label6 = new Label();
      this.label5 = new Label();
      this.label4 = new Label();
      this.label3 = new Label();
      this.txtFlag1 = new TextBox();
      this.txtFlag = new TextBox();
      this.txtskillmaster = new TextBox();
      this.txtFamily = new TextBox();
      this.groupBox3 = new GroupBox();
      this.label42 = new Label();
      this.txtsskillmaster = new TextBox();
      this.label13 = new Label();
      this.txtSize = new TextBox();
      this.label11 = new Label();
      this.txtSight = new TextBox();
      this.label12 = new Label();
      this.txtSkillPoint = new TextBox();
      this.label10 = new Label();
      this.txtGold = new TextBox();
      this.label9 = new Label();
      this.txtExp = new TextBox();
      this.label8 = new Label();
      this.txtLevel = new TextBox();
      this.txtName = new TextBox();
      this.label2 = new Label();
      this.checkBoxEnable = new CheckBox();
      this.txtIndex = new TextBox();
      this.label1 = new Label();
      this.tabPage2 = new TabPage();
      this.tabPage3 = new TabPage();
      this.tabPage4 = new TabPage();
      this.tabPage5 = new TabPage();
      this.tabPage6 = new TabPage();
      this.tabPage7 = new TabPage();
      this.btnSave = new Button();
      this.menuStrip1.SuspendLayout();
      this.groupBox1.SuspendLayout();
      this.groupBox2.SuspendLayout();
      this.statusStrip1.SuspendLayout();
      this.tabControl1.SuspendLayout();
      this.tabPage1.SuspendLayout();
      this.groupBox6.SuspendLayout();
      this.groupBox13.SuspendLayout();
      this.groupBox12.SuspendLayout();
      this.groupBox11.SuspendLayout();
      this.groupBox10.SuspendLayout();
      this.groupBox9.SuspendLayout();
      this.groupBox8.SuspendLayout();
      this.groupBox7.SuspendLayout();
      this.txtCon.BeginInit();
      this.txtInt.BeginInit();
      this.txtDex.BeginInit();
      this.txtStr.BeginInit();
      this.groupBox5.SuspendLayout();
      this.groupBox4.SuspendLayout();
      ((ISupportInitialize) this.pictureBox1).BeginInit();
      ((ISupportInitialize) this.pictureBox23).BeginInit();
      this.groupBox3.SuspendLayout();
      this.SuspendLayout();
      this.menuStrip1.BackColor = SystemColors.ControlLightLight;
      this.menuStrip1.BackgroundImageLayout = ImageLayout.None;
      this.menuStrip1.Font = new Font("Segoe UI", 9f);
      this.menuStrip1.GripStyle = ToolStripGripStyle.Visible;
      this.menuStrip1.Items.AddRange(new ToolStripItem[2]
      {
        (ToolStripItem) this.fileToolStripMenuItem,
        (ToolStripItem) this.extraToolStripMenuItem
      });
      this.menuStrip1.Location = new Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new Size(970, 24);
      this.menuStrip1.TabIndex = 0;
      this.menuStrip1.Text = "menuStrip1";
      this.fileToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[3]
      {
        (ToolStripItem) this.importFromDatabaseToolStripMenuItem,
        (ToolStripItem) this.saveToolStripMenuItem,
        (ToolStripItem) this.exportToolStripMenuItem
      });
      this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
      this.fileToolStripMenuItem.Size = new Size(37, 20);
      this.fileToolStripMenuItem.Text = "File";
      this.importFromDatabaseToolStripMenuItem.Name = "importFromDatabaseToolStripMenuItem";
      this.importFromDatabaseToolStripMenuItem.Size = new Size(180, 22);
      this.importFromDatabaseToolStripMenuItem.Text = "Load from Database";
      this.importFromDatabaseToolStripMenuItem.Click += new EventHandler(this.importFromDatabaseToolStripMenuItem_Click);
      this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
      this.saveToolStripMenuItem.Size = new Size(180, 22);
      this.saveToolStripMenuItem.Text = "Save";
      this.saveToolStripMenuItem.Click += new EventHandler(this.saveToolStripMenuItem_Click);
      this.exportToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[2]
      {
        (ToolStripItem) this.moballlodToolStripMenuItem,
        (ToolStripItem) this.strToolStripMenuItem
      });
      this.exportToolStripMenuItem.Name = "exportToolStripMenuItem";
      this.exportToolStripMenuItem.Size = new Size(180, 22);
      this.exportToolStripMenuItem.Text = "Export";
      this.moballlodToolStripMenuItem.Name = "moballlodToolStripMenuItem";
      this.moballlodToolStripMenuItem.Size = new Size(178, 22);
      this.moballlodToolStripMenuItem.Text = "mobAll.lod";
      this.moballlodToolStripMenuItem.Click += new EventHandler(this.moballlodToolStripMenuItem_Click);
      this.strToolStripMenuItem.Enabled = false;
      this.strToolStripMenuItem.Name = "strToolStripMenuItem";
      this.strToolStripMenuItem.Size = new Size(178, 22);
      this.strToolStripMenuItem.Text = "strNpcName_us.lod";
      this.strToolStripMenuItem.Click += new EventHandler(this.strToolStripMenuItem_Click);
      this.extraToolStripMenuItem.Enabled = false;
      this.extraToolStripMenuItem.Name = "extraToolStripMenuItem";
      this.extraToolStripMenuItem.Size = new Size(44, 20);
      this.extraToolStripMenuItem.Text = "Extra";
      this.groupBox1.Controls.Add((Control) this.textBox1);
      this.groupBox1.Location = new Point(12, 27);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(256, 51);
      this.groupBox1.TabIndex = 1;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Search";
      this.textBox1.BorderStyle = BorderStyle.FixedSingle;
      this.textBox1.Location = new Point(6, 19);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(244, 20);
      this.textBox1.TabIndex = 4;
      this.textBox1.TextChanged += new EventHandler(this.textBox1_TextChanged);
      this.groupBox2.Controls.Add((Control) this.btnDelete);
      this.groupBox2.Controls.Add((Control) this.btnCopy);
      this.groupBox2.Controls.Add((Control) this.listBox1);
      this.groupBox2.Location = new Point(12, 84);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new Size(256, 493);
      this.groupBox2.TabIndex = 2;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "Mob list";
      this.btnDelete.FlatStyle = FlatStyle.Flat;
      this.btnDelete.Location = new Point(142, 464);
      this.btnDelete.Name = "btnDelete";
      this.btnDelete.Size = new Size(108, 23);
      this.btnDelete.TabIndex = 4;
      this.btnDelete.Text = "Delete";
      this.btnDelete.UseVisualStyleBackColor = true;
      this.btnDelete.Click += new EventHandler(this.btnDelete_Click);
      this.btnCopy.FlatStyle = FlatStyle.Flat;
      this.btnCopy.Location = new Point(6, 464);
      this.btnCopy.Name = "btnCopy";
      this.btnCopy.Size = new Size(130, 23);
      this.btnCopy.TabIndex = 2;
      this.btnCopy.Text = "New Copy";
      this.btnCopy.UseVisualStyleBackColor = true;
      this.btnCopy.Click += new EventHandler(this.btnCopy_Click);
      this.listBox1.DrawMode = DrawMode.OwnerDrawVariable;
      this.listBox1.FormattingEnabled = true;
      this.listBox1.Location = new Point(6, 19);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new Size(244, 433);
      this.listBox1.TabIndex = 0;
      this.listBox1.SelectedIndexChanged += new EventHandler(this.listBox1_SelectedIndexChanged);
      this.statusStrip1.Items.AddRange(new ToolStripItem[2]
      {
        (ToolStripItem) this.toolStripStatusLabel1,
        (ToolStripItem) this.toolStripProgressBar1
      });
      this.statusStrip1.Location = new Point(0, 580);
      this.statusStrip1.Name = "statusStrip1";
      this.statusStrip1.Size = new Size(970, 22);
      this.statusStrip1.TabIndex = 3;
      this.statusStrip1.Text = "statusStrip1";
      this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
      this.toolStripStatusLabel1.Size = new Size(39, 17);
      this.toolStripStatusLabel1.Text = "Status";
      this.toolStripProgressBar1.Margin = new Padding(5);
      this.toolStripProgressBar1.Name = "toolStripProgressBar1";
      this.toolStripProgressBar1.Size = new Size(100, 15);
      this.toolStripProgressBar1.Step = 1;
      this.toolStripProgressBar1.Visible = false;
      this.tabControl1.Controls.Add((Control) this.tabPage1);
      this.tabControl1.Controls.Add((Control) this.tabPage2);
      this.tabControl1.Controls.Add((Control) this.tabPage3);
      this.tabControl1.Controls.Add((Control) this.tabPage4);
      this.tabControl1.Controls.Add((Control) this.tabPage5);
      this.tabControl1.Controls.Add((Control) this.tabPage6);
      this.tabControl1.Controls.Add((Control) this.tabPage7);
      this.tabControl1.Enabled = false;
      this.tabControl1.Location = new Point(274, 27);
      this.tabControl1.Name = "tabControl1";
      this.tabControl1.Padding = new Point(25, 3);
      this.tabControl1.SelectedIndex = 0;
      this.tabControl1.Size = new Size(674, 509);
      this.tabControl1.TabIndex = 4;
      this.tabPage1.BorderStyle = BorderStyle.FixedSingle;
      this.tabPage1.Controls.Add((Control) this.groupBox6);
      this.tabPage1.Controls.Add((Control) this.groupBox5);
      this.tabPage1.Controls.Add((Control) this.groupBox4);
      this.tabPage1.Controls.Add((Control) this.groupBox3);
      this.tabPage1.Location = new Point(4, 22);
      this.tabPage1.Name = "tabPage1";
      this.tabPage1.Padding = new Padding(3);
      this.tabPage1.Size = new Size(666, 483);
      this.tabPage1.TabIndex = 0;
      this.tabPage1.Text = "Main";
      this.tabPage1.UseVisualStyleBackColor = true;
      this.groupBox6.Controls.Add((Control) this.groupBox13);
      this.groupBox6.Controls.Add((Control) this.groupBox12);
      this.groupBox6.Controls.Add((Control) this.groupBox11);
      this.groupBox6.Controls.Add((Control) this.groupBox10);
      this.groupBox6.Controls.Add((Control) this.groupBox9);
      this.groupBox6.Controls.Add((Control) this.groupBox8);
      this.groupBox6.Controls.Add((Control) this.groupBox7);
      this.groupBox6.Location = new Point(6, 190);
      this.groupBox6.Name = "groupBox6";
      this.groupBox6.Size = new Size(652, 285);
      this.groupBox6.TabIndex = 3;
      this.groupBox6.TabStop = false;
      this.groupBox6.Text = "Strength / Skills";
      this.groupBox13.Controls.Add((Control) this.txtAttackType);
      this.groupBox13.Controls.Add((Control) this.label40);
      this.groupBox13.Controls.Add((Control) this.txtAttackSpeed);
      this.groupBox13.Controls.Add((Control) this.label41);
      this.groupBox13.Location = new Point(190, 152);
      this.groupBox13.Name = "groupBox13";
      this.groupBox13.Size = new Size(131, 74);
      this.groupBox13.TabIndex = 42;
      this.groupBox13.TabStop = false;
      this.groupBox13.Text = "Attack";
      this.txtAttackType.BorderStyle = BorderStyle.FixedSingle;
      this.txtAttackType.Location = new Point(76, 16);
      this.txtAttackType.Name = "txtAttackType";
      this.txtAttackType.Size = new Size(44, 20);
      this.txtAttackType.TabIndex = 21;
      this.label40.AutoSize = true;
      this.label40.Location = new Point(6, 20);
      this.label40.Name = "label40";
      this.label40.Size = new Size(65, 13);
      this.label40.TabIndex = 20;
      this.label40.Text = "AttackType:";
      this.txtAttackSpeed.BorderStyle = BorderStyle.FixedSingle;
      this.txtAttackSpeed.Location = new Point(76, 42);
      this.txtAttackSpeed.Name = "txtAttackSpeed";
      this.txtAttackSpeed.Size = new Size(44, 20);
      this.txtAttackSpeed.TabIndex = 23;
      this.label41.AutoSize = true;
      this.label41.Location = new Point(6, 46);
      this.label41.Name = "label41";
      this.label41.Size = new Size(72, 13);
      this.label41.TabIndex = 22;
      this.label41.Text = "AttackSpeed:";
      this.groupBox12.Controls.Add((Control) this.txtMagicAvoid);
      this.groupBox12.Controls.Add((Control) this.txtHit);
      this.groupBox12.Controls.Add((Control) this.label36);
      this.groupBox12.Controls.Add((Control) this.label37);
      this.groupBox12.Controls.Add((Control) this.txtJobAttribute);
      this.groupBox12.Controls.Add((Control) this.label38);
      this.groupBox12.Controls.Add((Control) this.label39);
      this.groupBox12.Controls.Add((Control) this.txtDodge);
      this.groupBox12.Location = new Point(324, 101);
      this.groupBox12.Name = "groupBox12";
      this.groupBox12.Size = new Size(322, 73);
      this.groupBox12.TabIndex = 41;
      this.groupBox12.TabStop = false;
      this.groupBox12.Text = "Attribute";
      this.txtMagicAvoid.BorderStyle = BorderStyle.FixedSingle;
      this.txtMagicAvoid.Location = new Point(246, 16);
      this.txtMagicAvoid.Name = "txtMagicAvoid";
      this.txtMagicAvoid.Size = new Size(70, 20);
      this.txtMagicAvoid.TabIndex = 31;
      this.txtHit.BorderStyle = BorderStyle.FixedSingle;
      this.txtHit.Location = new Point(84, 16);
      this.txtHit.Name = "txtHit";
      this.txtHit.Size = new Size(70, 20);
      this.txtHit.TabIndex = 29;
      this.label36.AutoSize = true;
      this.label36.Location = new Point(176, 45);
      this.label36.Name = "label36";
      this.label36.Size = new Size(66, 13);
      this.label36.TabIndex = 34;
      this.label36.Text = "JobAttribute:";
      this.label37.AutoSize = true;
      this.label37.Location = new Point(14, 20);
      this.label37.Name = "label37";
      this.label37.Size = new Size(23, 13);
      this.label37.TabIndex = 28;
      this.label37.Text = "Hit:";
      this.txtJobAttribute.BorderStyle = BorderStyle.FixedSingle;
      this.txtJobAttribute.Location = new Point(246, 41);
      this.txtJobAttribute.Name = "txtJobAttribute";
      this.txtJobAttribute.Size = new Size(70, 20);
      this.txtJobAttribute.TabIndex = 35;
      this.label38.AutoSize = true;
      this.label38.Location = new Point(176, 20);
      this.label38.Name = "label38";
      this.label38.Size = new Size(66, 13);
      this.label38.TabIndex = 30;
      this.label38.Text = "MagicAvoid:";
      this.label39.AutoSize = true;
      this.label39.Location = new Point(14, 43);
      this.label39.Name = "label39";
      this.label39.Size = new Size(42, 13);
      this.label39.TabIndex = 32;
      this.label39.Text = "Dodge:";
      this.txtDodge.BorderStyle = BorderStyle.FixedSingle;
      this.txtDodge.Location = new Point(84, 39);
      this.txtDodge.Name = "txtDodge";
      this.txtDodge.Size = new Size(70, 20);
      this.txtDodge.TabIndex = 33;
      this.groupBox11.Controls.Add((Control) this.label34);
      this.groupBox11.Controls.Add((Control) this.label33);
      this.groupBox11.Controls.Add((Control) this.txtSkill3);
      this.groupBox11.Controls.Add((Control) this.label35);
      this.groupBox11.Controls.Add((Control) this.txtSkill1);
      this.groupBox11.Controls.Add((Control) this.txtSkill2);
      this.groupBox11.Controls.Add((Control) this.label32);
      this.groupBox11.Controls.Add((Control) this.txtSkill0);
      this.groupBox11.Location = new Point(324, 180);
      this.groupBox11.Name = "groupBox11";
      this.groupBox11.Size = new Size(322, 76);
      this.groupBox11.TabIndex = 40;
      this.groupBox11.TabStop = false;
      this.groupBox11.Text = "Skills";
      this.label34.AutoSize = true;
      this.label34.Location = new Point(163, 52);
      this.label34.Name = "label34";
      this.label34.Size = new Size(32, 13);
      this.label34.TabIndex = 44;
      this.label34.Text = "Skill3";
      this.label33.AutoSize = true;
      this.label33.Location = new Point(10, 52);
      this.label33.Name = "label33";
      this.label33.Size = new Size(32, 13);
      this.label33.TabIndex = 40;
      this.label33.Text = "Skill1";
      this.txtSkill3.BorderStyle = BorderStyle.FixedSingle;
      this.txtSkill3.Location = new Point(216, 50);
      this.txtSkill3.Name = "txtSkill3";
      this.txtSkill3.Size = new Size(88, 20);
      this.txtSkill3.TabIndex = 45;
      this.label35.AutoSize = true;
      this.label35.Location = new Point(164, 28);
      this.label35.Name = "label35";
      this.label35.Size = new Size(35, 13);
      this.label35.TabIndex = 42;
      this.label35.Text = "Skill2:";
      this.txtSkill1.BorderStyle = BorderStyle.FixedSingle;
      this.txtSkill1.Location = new Point(53, 50);
      this.txtSkill1.Name = "txtSkill1";
      this.txtSkill1.Size = new Size(88, 20);
      this.txtSkill1.TabIndex = 41;
      this.txtSkill2.BorderStyle = BorderStyle.FixedSingle;
      this.txtSkill2.Location = new Point(215, 24);
      this.txtSkill2.Name = "txtSkill2";
      this.txtSkill2.Size = new Size(88, 20);
      this.txtSkill2.TabIndex = 43;
      this.label32.AutoSize = true;
      this.label32.Location = new Point(7, 28);
      this.label32.Name = "label32";
      this.label32.Size = new Size(35, 13);
      this.label32.TabIndex = 38;
      this.label32.Text = "Skill0:";
      this.txtSkill0.BorderStyle = BorderStyle.FixedSingle;
      this.txtSkill0.Location = new Point(53, 26);
      this.txtSkill0.Name = "txtSkill0";
      this.txtSkill0.Size = new Size(88, 20);
      this.txtSkill0.TabIndex = 39;
      this.groupBox10.Controls.Add((Control) this.label30);
      this.groupBox10.Controls.Add((Control) this.label31);
      this.groupBox10.Controls.Add((Control) this.txtRecoverHP);
      this.groupBox10.Controls.Add((Control) this.txtRecoverMP);
      this.groupBox10.Controls.Add((Control) this.label26);
      this.groupBox10.Controls.Add((Control) this.label29);
      this.groupBox10.Controls.Add((Control) this.txtHP);
      this.groupBox10.Controls.Add((Control) this.txtMP);
      this.groupBox10.Location = new Point(6, 101);
      this.groupBox10.Name = "groupBox10";
      this.groupBox10.Size = new Size(174, (int) sbyte.MaxValue);
      this.groupBox10.TabIndex = 39;
      this.groupBox10.TabStop = false;
      this.groupBox10.Text = "Health / Mana";
      this.label30.AutoSize = true;
      this.label30.Location = new Point(13, 105);
      this.label30.Name = "label30";
      this.label30.Size = new Size(54, 13);
      this.label30.TabIndex = 38;
      this.label30.Text = "ManaReg";
      this.label31.AutoSize = true;
      this.label31.Location = new Point(13, 79);
      this.label31.Name = "label31";
      this.label31.Size = new Size(61, 13);
      this.label31.TabIndex = 36;
      this.label31.Text = "HealthReg:";
      this.txtRecoverHP.BorderStyle = BorderStyle.FixedSingle;
      this.txtRecoverHP.Location = new Point(80, 75);
      this.txtRecoverHP.Name = "txtRecoverHP";
      this.txtRecoverHP.Size = new Size(88, 20);
      this.txtRecoverHP.TabIndex = 37;
      this.txtRecoverMP.BorderStyle = BorderStyle.FixedSingle;
      this.txtRecoverMP.Location = new Point(80, 101);
      this.txtRecoverMP.Name = "txtRecoverMP";
      this.txtRecoverMP.Size = new Size(88, 20);
      this.txtRecoverMP.TabIndex = 39;
      this.label26.AutoSize = true;
      this.label26.Location = new Point(13, 51);
      this.label26.Name = "label26";
      this.label26.Size = new Size(37, 13);
      this.label26.TabIndex = 34;
      this.label26.Text = "Mana:";
      this.label29.AutoSize = true;
      this.label29.Location = new Point(13, 25);
      this.label29.Name = "label29";
      this.label29.Size = new Size(41, 13);
      this.label29.TabIndex = 32;
      this.label29.Text = "Health:";
      this.txtHP.BorderStyle = BorderStyle.FixedSingle;
      this.txtHP.Location = new Point(61, 21);
      this.txtHP.Name = "txtHP";
      this.txtHP.Size = new Size(107, 20);
      this.txtHP.TabIndex = 33;
      this.txtMP.BorderStyle = BorderStyle.FixedSingle;
      this.txtMP.Location = new Point(61, 47);
      this.txtMP.Name = "txtMP";
      this.txtMP.Size = new Size(107, 20);
      this.txtMP.TabIndex = 35;
      this.groupBox9.Controls.Add((Control) this.txtDefenseLevel);
      this.groupBox9.Controls.Add((Control) this.txtAttackLevel);
      this.groupBox9.Controls.Add((Control) this.label27);
      this.groupBox9.Controls.Add((Control) this.label28);
      this.groupBox9.Location = new Point(6, 19);
      this.groupBox9.Name = "groupBox9";
      this.groupBox9.Size = new Size(175, 76);
      this.groupBox9.TabIndex = 38;
      this.groupBox9.TabStop = false;
      this.groupBox9.Text = "Level";
      this.txtDefenseLevel.BorderStyle = BorderStyle.FixedSingle;
      this.txtDefenseLevel.Location = new Point(117, 44);
      this.txtDefenseLevel.Name = "txtDefenseLevel";
      this.txtDefenseLevel.Size = new Size(52, 20);
      this.txtDefenseLevel.TabIndex = 31;
      this.txtAttackLevel.BorderStyle = BorderStyle.FixedSingle;
      this.txtAttackLevel.Location = new Point(117, 18);
      this.txtAttackLevel.Name = "txtAttackLevel";
      this.txtAttackLevel.Size = new Size(52, 20);
      this.txtAttackLevel.TabIndex = 29;
      this.label27.AutoSize = true;
      this.label27.Location = new Point(14, 20);
      this.label27.Name = "label27";
      this.label27.Size = new Size(67, 13);
      this.label27.TabIndex = 28;
      this.label27.Text = "AttackLevel:";
      this.label28.AutoSize = true;
      this.label28.Location = new Point(14, 48);
      this.label28.Name = "label28";
      this.label28.Size = new Size(76, 13);
      this.label28.TabIndex = 30;
      this.label28.Text = "DefenseLevel:";
      this.groupBox8.Controls.Add((Control) this.txtMagic);
      this.groupBox8.Controls.Add((Control) this.txtAttack);
      this.groupBox8.Controls.Add((Control) this.label25);
      this.groupBox8.Controls.Add((Control) this.label22);
      this.groupBox8.Controls.Add((Control) this.txtResist);
      this.groupBox8.Controls.Add((Control) this.label23);
      this.groupBox8.Controls.Add((Control) this.label24);
      this.groupBox8.Controls.Add((Control) this.txtDefense);
      this.groupBox8.Location = new Point(324, 19);
      this.groupBox8.Name = "groupBox8";
      this.groupBox8.Size = new Size(322, 73);
      this.groupBox8.TabIndex = 37;
      this.groupBox8.TabStop = false;
      this.groupBox8.Text = "Stats";
      this.txtMagic.BorderStyle = BorderStyle.FixedSingle;
      this.txtMagic.Location = new Point(246, 16);
      this.txtMagic.Name = "txtMagic";
      this.txtMagic.Size = new Size(70, 20);
      this.txtMagic.TabIndex = 31;
      this.txtAttack.BorderStyle = BorderStyle.FixedSingle;
      this.txtAttack.Location = new Point(84, 16);
      this.txtAttack.Name = "txtAttack";
      this.txtAttack.Size = new Size(70, 20);
      this.txtAttack.TabIndex = 29;
      this.label25.AutoSize = true;
      this.label25.Location = new Point(176, 45);
      this.label25.Name = "label25";
      this.label25.Size = new Size(39, 13);
      this.label25.TabIndex = 34;
      this.label25.Text = "Resist:";
      this.label22.AutoSize = true;
      this.label22.Location = new Point(14, 20);
      this.label22.Name = "label22";
      this.label22.Size = new Size(41, 13);
      this.label22.TabIndex = 28;
      this.label22.Text = "Attack:";
      this.txtResist.BorderStyle = BorderStyle.FixedSingle;
      this.txtResist.Location = new Point(246, 41);
      this.txtResist.Name = "txtResist";
      this.txtResist.Size = new Size(70, 20);
      this.txtResist.TabIndex = 35;
      this.label23.AutoSize = true;
      this.label23.Location = new Point(176, 20);
      this.label23.Name = "label23";
      this.label23.Size = new Size(39, 13);
      this.label23.TabIndex = 30;
      this.label23.Text = "Magic:";
      this.label24.AutoSize = true;
      this.label24.Location = new Point(14, 43);
      this.label24.Name = "label24";
      this.label24.Size = new Size(50, 13);
      this.label24.TabIndex = 32;
      this.label24.Text = "Defense:";
      this.txtDefense.BorderStyle = BorderStyle.FixedSingle;
      this.txtDefense.Location = new Point(84, 39);
      this.txtDefense.Name = "txtDefense";
      this.txtDefense.Size = new Size(70, 20);
      this.txtDefense.TabIndex = 33;
      this.groupBox7.Controls.Add((Control) this.txtCon);
      this.groupBox7.Controls.Add((Control) this.txtInt);
      this.groupBox7.Controls.Add((Control) this.txtDex);
      this.groupBox7.Controls.Add((Control) this.txtStr);
      this.groupBox7.Controls.Add((Control) this.label18);
      this.groupBox7.Controls.Add((Control) this.label19);
      this.groupBox7.Controls.Add((Control) this.label20);
      this.groupBox7.Controls.Add((Control) this.label21);
      this.groupBox7.Location = new Point(187, 19);
      this.groupBox7.Name = "groupBox7";
      this.groupBox7.Size = new Size(131, (int) sbyte.MaxValue);
      this.groupBox7.TabIndex = 36;
      this.groupBox7.TabStop = false;
      this.groupBox7.Text = "Basic Stats";
      this.txtCon.Increment = new Decimal(new int[4]
      {
        10,
        0,
        0,
        0
      });
      this.txtCon.Location = new Point(72, 95);
      this.txtCon.Maximum = new Decimal(new int[4]
      {
        100000,
        0,
        0,
        0
      });
      this.txtCon.Name = "txtCon";
      this.txtCon.Size = new Size(53, 20);
      this.txtCon.TabIndex = 46;
      this.txtInt.Increment = new Decimal(new int[4]
      {
        10,
        0,
        0,
        0
      });
      this.txtInt.Location = new Point(72, 70);
      this.txtInt.Maximum = new Decimal(new int[4]
      {
        100000,
        0,
        0,
        0
      });
      this.txtInt.Name = "txtInt";
      this.txtInt.Size = new Size(53, 20);
      this.txtInt.TabIndex = 45;
      this.txtDex.Increment = new Decimal(new int[4]
      {
        10,
        0,
        0,
        0
      });
      this.txtDex.Location = new Point(72, 44);
      this.txtDex.Maximum = new Decimal(new int[4]
      {
        100000,
        0,
        0,
        0
      });
      this.txtDex.Name = "txtDex";
      this.txtDex.Size = new Size(53, 20);
      this.txtDex.TabIndex = 44;
      this.txtStr.Increment = new Decimal(new int[4]
      {
        10,
        0,
        0,
        0
      });
      this.txtStr.Location = new Point(72, 16);
      this.txtStr.Maximum = new Decimal(new int[4]
      {
        100000,
        0,
        0,
        0
      });
      this.txtStr.Name = "txtStr";
      this.txtStr.Size = new Size(51, 20);
      this.txtStr.TabIndex = 43;
      this.label18.AutoSize = true;
      this.label18.Location = new Point(6, 20);
      this.label18.Name = "label18";
      this.label18.Size = new Size(50, 13);
      this.label18.TabIndex = 20;
      this.label18.Text = "Strength:";
      this.label19.AutoSize = true;
      this.label19.Location = new Point(6, 46);
      this.label19.Name = "label19";
      this.label19.Size = new Size(48, 13);
      this.label19.TabIndex = 22;
      this.label19.Text = "Dexterity";
      this.label20.AutoSize = true;
      this.label20.Location = new Point(6, 72);
      this.label20.Name = "label20";
      this.label20.Size = new Size(64, 13);
      this.label20.TabIndex = 24;
      this.label20.Text = "Intelligence:";
      this.label21.AutoSize = true;
      this.label21.Location = new Point(6, 98);
      this.label21.Name = "label21";
      this.label21.Size = new Size(65, 13);
      this.label21.TabIndex = 26;
      this.label21.Text = "Constitution:";
      this.groupBox5.Controls.Add((Control) this.label16);
      this.groupBox5.Controls.Add((Control) this.label17);
      this.groupBox5.Controls.Add((Control) this.txtRunSpeed);
      this.groupBox5.Controls.Add((Control) this.txtWalkSpeed);
      this.groupBox5.Controls.Add((Control) this.label14);
      this.groupBox5.Controls.Add((Control) this.label15);
      this.groupBox5.Controls.Add((Control) this.txtAttackArea);
      this.groupBox5.Controls.Add((Control) this.txtMoveArea);
      this.groupBox5.Location = new Point(333, 107);
      this.groupBox5.Name = "groupBox5";
      this.groupBox5.Size = new Size(325, 77);
      this.groupBox5.TabIndex = 2;
      this.groupBox5.TabStop = false;
      this.groupBox5.Text = "Move";
      this.label16.AutoSize = true;
      this.label16.Location = new Point(154, 49);
      this.label16.Name = "label16";
      this.label16.Size = new Size(61, 13);
      this.label16.TabIndex = 23;
      this.label16.Text = "RunSpeed:";
      this.label17.AutoSize = true;
      this.label17.Location = new Point(6, 49);
      this.label17.Name = "label17";
      this.label17.Size = new Size(66, 13);
      this.label17.TabIndex = 22;
      this.label17.Text = "WalkSpeed:";
      this.txtRunSpeed.BorderStyle = BorderStyle.FixedSingle;
      this.txtRunSpeed.Location = new Point(223, 47);
      this.txtRunSpeed.Name = "txtRunSpeed";
      this.txtRunSpeed.Size = new Size(69, 20);
      this.txtRunSpeed.TabIndex = 21;
      this.txtWalkSpeed.BorderStyle = BorderStyle.FixedSingle;
      this.txtWalkSpeed.Location = new Point(75, 47);
      this.txtWalkSpeed.Name = "txtWalkSpeed";
      this.txtWalkSpeed.Size = new Size(54, 20);
      this.txtWalkSpeed.TabIndex = 20;
      this.label14.AutoSize = true;
      this.label14.Location = new Point(154, 23);
      this.label14.Name = "label14";
      this.label14.Size = new Size(63, 13);
      this.label14.TabIndex = 19;
      this.label14.Text = "AttackArea:";
      this.label15.AutoSize = true;
      this.label15.Location = new Point(6, 23);
      this.label15.Name = "label15";
      this.label15.Size = new Size(59, 13);
      this.label15.TabIndex = 18;
      this.label15.Text = "MoveArea:";
      this.txtAttackArea.BorderStyle = BorderStyle.FixedSingle;
      this.txtAttackArea.Location = new Point(223, 21);
      this.txtAttackArea.Name = "txtAttackArea";
      this.txtAttackArea.Size = new Size(69, 20);
      this.txtAttackArea.TabIndex = 17;
      this.txtMoveArea.BorderStyle = BorderStyle.FixedSingle;
      this.txtMoveArea.Location = new Point(75, 21);
      this.txtMoveArea.Name = "txtMoveArea";
      this.txtMoveArea.Size = new Size(54, 20);
      this.txtMoveArea.TabIndex = 16;
      this.groupBox4.Controls.Add((Control) this.pictureBox1);
      this.groupBox4.Controls.Add((Control) this.pictureBox23);
      this.groupBox4.Controls.Add((Control) this.label7);
      this.groupBox4.Controls.Add((Control) this.txtStateFlag);
      this.groupBox4.Controls.Add((Control) this.label6);
      this.groupBox4.Controls.Add((Control) this.label5);
      this.groupBox4.Controls.Add((Control) this.label4);
      this.groupBox4.Controls.Add((Control) this.label3);
      this.groupBox4.Controls.Add((Control) this.txtFlag1);
      this.groupBox4.Controls.Add((Control) this.txtFlag);
      this.groupBox4.Controls.Add((Control) this.txtskillmaster);
      this.groupBox4.Controls.Add((Control) this.txtFamily);
      this.groupBox4.Location = new Point(333, 6);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Size = new Size(325, 95);
      this.groupBox4.TabIndex = 1;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "State";
      this.pictureBox1.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox1.Cursor = Cursors.Hand;
      this.pictureBox1.Location = new Point(298, 40);
      this.pictureBox1.Name = "pictureBox1";
      this.pictureBox1.Size = new Size(17, 20);
      this.pictureBox1.TabIndex = 44;
      this.pictureBox1.TabStop = false;
      this.pictureBox1.Tag = (object) "a";
      this.pictureBox1.Click += new EventHandler(this.pictureBox1_Click);
      this.pictureBox23.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox23.Cursor = Cursors.Hand;
      this.pictureBox23.Location = new Point(298, 66);
      this.pictureBox23.Name = "pictureBox23";
      this.pictureBox23.Size = new Size(17, 20);
      this.pictureBox23.TabIndex = 43;
      this.pictureBox23.TabStop = false;
      this.pictureBox23.Tag = (object) "a";
      this.pictureBox23.Click += new EventHandler(this.pictureBox23_Click);
      this.label7.AutoSize = true;
      this.label7.Location = new Point(154, 16);
      this.label7.Name = "label7";
      this.label7.Size = new Size(55, 13);
      this.label7.TabIndex = 17;
      this.label7.Text = "StateFlag:";
      this.txtStateFlag.BorderStyle = BorderStyle.FixedSingle;
      this.txtStateFlag.Location = new Point(223, 14);
      this.txtStateFlag.Name = "txtStateFlag";
      this.txtStateFlag.Size = new Size(69, 20);
      this.txtStateFlag.TabIndex = 16;
      this.label6.AutoSize = true;
      this.label6.Location = new Point(154, 42);
      this.label6.Name = "label6";
      this.label6.Size = new Size(36, 13);
      this.label6.TabIndex = 15;
      this.label6.Text = "Flag1:";
      this.label5.AutoSize = true;
      this.label5.Location = new Point(6, 68);
      this.label5.Name = "label5";
      this.label5.Size = new Size(30, 13);
      this.label5.TabIndex = 14;
      this.label5.Text = "Flag:";
      this.label4.AutoSize = true;
      this.label4.Location = new Point(6, 42);
      this.label4.Name = "label4";
      this.label4.Size = new Size(60, 13);
      this.label4.TabIndex = 13;
      this.label4.Text = "Skillmaster:";
      this.label3.AutoSize = true;
      this.label3.Location = new Point(6, 16);
      this.label3.Name = "label3";
      this.label3.Size = new Size(39, 13);
      this.label3.TabIndex = 9;
      this.label3.Text = "Family:";
      this.txtFlag1.BorderStyle = BorderStyle.FixedSingle;
      this.txtFlag1.Location = new Point(223, 40);
      this.txtFlag1.Name = "txtFlag1";
      this.txtFlag1.Size = new Size(69, 20);
      this.txtFlag1.TabIndex = 12;
      this.txtFlag.BorderStyle = BorderStyle.FixedSingle;
      this.txtFlag.Location = new Point(75, 66);
      this.txtFlag.Name = "txtFlag";
      this.txtFlag.Size = new Size(217, 20);
      this.txtFlag.TabIndex = 11;
      this.txtskillmaster.BorderStyle = BorderStyle.FixedSingle;
      this.txtskillmaster.Location = new Point(75, 40);
      this.txtskillmaster.Name = "txtskillmaster";
      this.txtskillmaster.Size = new Size(54, 20);
      this.txtskillmaster.TabIndex = 10;
      this.txtFamily.BorderStyle = BorderStyle.FixedSingle;
      this.txtFamily.Location = new Point(75, 14);
      this.txtFamily.Name = "txtFamily";
      this.txtFamily.Size = new Size(54, 20);
      this.txtFamily.TabIndex = 9;
      this.groupBox3.Controls.Add((Control) this.label42);
      this.groupBox3.Controls.Add((Control) this.txtsskillmaster);
      this.groupBox3.Controls.Add((Control) this.label13);
      this.groupBox3.Controls.Add((Control) this.txtSize);
      this.groupBox3.Controls.Add((Control) this.label11);
      this.groupBox3.Controls.Add((Control) this.txtSight);
      this.groupBox3.Controls.Add((Control) this.label12);
      this.groupBox3.Controls.Add((Control) this.txtSkillPoint);
      this.groupBox3.Controls.Add((Control) this.label10);
      this.groupBox3.Controls.Add((Control) this.txtGold);
      this.groupBox3.Controls.Add((Control) this.label9);
      this.groupBox3.Controls.Add((Control) this.txtExp);
      this.groupBox3.Controls.Add((Control) this.label8);
      this.groupBox3.Controls.Add((Control) this.txtLevel);
      this.groupBox3.Controls.Add((Control) this.txtName);
      this.groupBox3.Controls.Add((Control) this.label2);
      this.groupBox3.Controls.Add((Control) this.checkBoxEnable);
      this.groupBox3.Controls.Add((Control) this.txtIndex);
      this.groupBox3.Controls.Add((Control) this.label1);
      this.groupBox3.Location = new Point(6, 6);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Size = new Size(321, 178);
      this.groupBox3.TabIndex = 0;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "Basic";
      this.label42.AutoSize = true;
      this.label42.Location = new Point(7, 148);
      this.label42.Name = "label42";
      this.label42.Size = new Size(68, 13);
      this.label42.TabIndex = 22;
      this.label42.Text = "SSkillMaster:";
      this.txtsskillmaster.BorderStyle = BorderStyle.FixedSingle;
      this.txtsskillmaster.Location = new Point(81, 144);
      this.txtsskillmaster.Name = "txtsskillmaster";
      this.txtsskillmaster.Size = new Size(87, 20);
      this.txtsskillmaster.TabIndex = 23;
      this.label13.AutoSize = true;
      this.label13.Location = new Point(180, 122);
      this.label13.Name = "label13";
      this.label13.Size = new Size(30, 13);
      this.label13.TabIndex = 20;
      this.label13.Text = "Size:";
      this.txtSize.BorderStyle = BorderStyle.FixedSingle;
      this.txtSize.Location = new Point(218, 118);
      this.txtSize.Name = "txtSize";
      this.txtSize.Size = new Size(97, 20);
      this.txtSize.TabIndex = 21;
      this.label11.AutoSize = true;
      this.label11.Location = new Point(7, 122);
      this.label11.Name = "label11";
      this.label11.Size = new Size(34, 13);
      this.label11.TabIndex = 18;
      this.label11.Text = "Sight:";
      this.txtSight.BorderStyle = BorderStyle.FixedSingle;
      this.txtSight.Location = new Point(81, 118);
      this.txtSight.Name = "txtSight";
      this.txtSight.Size = new Size(87, 20);
      this.txtSight.TabIndex = 19;
      this.label12.AutoSize = true;
      this.label12.Location = new Point(7, 94);
      this.label12.Name = "label12";
      this.label12.Size = new Size(53, 13);
      this.label12.TabIndex = 16;
      this.label12.Text = "SkillPoint:";
      this.txtSkillPoint.BorderStyle = BorderStyle.FixedSingle;
      this.txtSkillPoint.Location = new Point(81, 92);
      this.txtSkillPoint.Name = "txtSkillPoint";
      this.txtSkillPoint.Size = new Size(87, 20);
      this.txtSkillPoint.TabIndex = 17;
      this.label10.AutoSize = true;
      this.label10.Location = new Point(180, 70);
      this.label10.Name = "label10";
      this.label10.Size = new Size(32, 13);
      this.label10.TabIndex = 14;
      this.label10.Text = "Gold:";
      this.txtGold.BorderStyle = BorderStyle.FixedSingle;
      this.txtGold.Location = new Point(218, 66);
      this.txtGold.Name = "txtGold";
      this.txtGold.Size = new Size(97, 20);
      this.txtGold.TabIndex = 15;
      this.label9.AutoSize = true;
      this.label9.Location = new Point(7, 68);
      this.label9.Name = "label9";
      this.label9.Size = new Size(31, 13);
      this.label9.TabIndex = 12;
      this.label9.Text = "EXP:";
      this.txtExp.BorderStyle = BorderStyle.FixedSingle;
      this.txtExp.Location = new Point(81, 66);
      this.txtExp.Name = "txtExp";
      this.txtExp.Size = new Size(87, 20);
      this.txtExp.TabIndex = 13;
      this.label8.AutoSize = true;
      this.label8.Location = new Point(140, 16);
      this.label8.Name = "label8";
      this.label8.Size = new Size(36, 13);
      this.label8.TabIndex = 10;
      this.label8.Text = "Level:";
      this.txtLevel.BorderStyle = BorderStyle.FixedSingle;
      this.txtLevel.Location = new Point(182, 14);
      this.txtLevel.Name = "txtLevel";
      this.txtLevel.Size = new Size(45, 20);
      this.txtLevel.TabIndex = 11;
      this.txtName.BorderStyle = BorderStyle.FixedSingle;
      this.txtName.Location = new Point(81, 40);
      this.txtName.Name = "txtName";
      this.txtName.Size = new Size(234, 20);
      this.txtName.TabIndex = 8;
      this.label2.AutoSize = true;
      this.label2.Location = new Point(7, 42);
      this.label2.Name = "label2";
      this.label2.Size = new Size(38, 13);
      this.label2.TabIndex = 7;
      this.label2.Text = "Name:";
      this.checkBoxEnable.AutoSize = true;
      this.checkBoxEnable.FlatStyle = FlatStyle.Flat;
      this.checkBoxEnable.Location = new Point(259, 14);
      this.checkBoxEnable.Name = "checkBoxEnable";
      this.checkBoxEnable.Size = new Size(56, 17);
      this.checkBoxEnable.TabIndex = 6;
      this.checkBoxEnable.Text = "Enable";
      this.checkBoxEnable.UseVisualStyleBackColor = true;
      this.txtIndex.BorderStyle = BorderStyle.FixedSingle;
      this.txtIndex.Location = new Point(81, 14);
      this.txtIndex.Name = "txtIndex";
      this.txtIndex.Size = new Size(44, 20);
      this.txtIndex.TabIndex = 5;
      this.label1.AutoSize = true;
      this.label1.Location = new Point(6, 16);
      this.label1.Name = "label1";
      this.label1.Size = new Size(36, 13);
      this.label1.TabIndex = 0;
      this.label1.Text = "Index:";
      this.tabPage2.BorderStyle = BorderStyle.FixedSingle;
      this.tabPage2.Cursor = Cursors.Default;
      this.tabPage2.Location = new Point(4, 22);
      this.tabPage2.Name = "tabPage2";
      this.tabPage2.Padding = new Padding(3);
      this.tabPage2.Size = new Size(666, 483);
      this.tabPage2.TabIndex = 1;
      this.tabPage2.Text = "Drop";
      this.tabPage2.UseVisualStyleBackColor = true;
      this.tabPage3.BorderStyle = BorderStyle.FixedSingle;
      this.tabPage3.Location = new Point(4, 22);
      this.tabPage3.Name = "tabPage3";
      this.tabPage3.Size = new Size(666, 483);
      this.tabPage3.TabIndex = 2;
      this.tabPage3.Text = "JewelDrop";
      this.tabPage3.UseVisualStyleBackColor = true;
      this.tabPage4.BorderStyle = BorderStyle.FixedSingle;
      this.tabPage4.Location = new Point(4, 22);
      this.tabPage4.Name = "tabPage4";
      this.tabPage4.Size = new Size(666, 483);
      this.tabPage4.TabIndex = 3;
      this.tabPage4.Text = "Motion";
      this.tabPage4.UseVisualStyleBackColor = true;
      this.tabPage5.BorderStyle = BorderStyle.FixedSingle;
      this.tabPage5.Location = new Point(4, 22);
      this.tabPage5.Name = "tabPage5";
      this.tabPage5.Size = new Size(666, 483);
      this.tabPage5.TabIndex = 4;
      this.tabPage5.Text = "Effect";
      this.tabPage5.UseVisualStyleBackColor = true;
      this.tabPage6.BorderStyle = BorderStyle.FixedSingle;
      this.tabPage6.Location = new Point(4, 22);
      this.tabPage6.Name = "tabPage6";
      this.tabPage6.Size = new Size(666, 483);
      this.tabPage6.TabIndex = 5;
      this.tabPage6.Text = "P2 Control";
      this.tabPage6.UseVisualStyleBackColor = true;
      this.tabPage7.BorderStyle = BorderStyle.FixedSingle;
      this.tabPage7.Location = new Point(4, 22);
      this.tabPage7.Name = "tabPage7";
      this.tabPage7.Size = new Size(666, 483);
      this.tabPage7.TabIndex = 6;
      this.tabPage7.Text = "Misc";
      this.tabPage7.UseVisualStyleBackColor = true;
      this.btnSave.FlatStyle = FlatStyle.Flat;
      this.btnSave.Location = new Point(862, 548);
      this.btnSave.Name = "btnSave";
      this.btnSave.Size = new Size(82, 23);
      this.btnSave.TabIndex = 5;
      this.btnSave.Text = "Save";
      this.btnSave.UseVisualStyleBackColor = true;
      this.btnSave.Click += new EventHandler(this.btnSave_Click);
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(970, 602);
      this.Controls.Add((Control) this.btnSave);
      this.Controls.Add((Control) this.tabControl1);
      this.Controls.Add((Control) this.statusStrip1);
      this.Controls.Add((Control) this.groupBox2);
      this.Controls.Add((Control) this.groupBox1);
      this.Controls.Add((Control) this.menuStrip1);
      this.MainMenuStrip = this.menuStrip1;
      this.Name = nameof (MobEditor);
      this.Text = "[Beta]Ultimate MobEditor for Episode 4 by DamonA";
      this.Load += new EventHandler(this.Form1_Load);
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.groupBox2.ResumeLayout(false);
      this.statusStrip1.ResumeLayout(false);
      this.statusStrip1.PerformLayout();
      this.tabControl1.ResumeLayout(false);
      this.tabPage1.ResumeLayout(false);
      this.groupBox6.ResumeLayout(false);
      this.groupBox13.ResumeLayout(false);
      this.groupBox13.PerformLayout();
      this.groupBox12.ResumeLayout(false);
      this.groupBox12.PerformLayout();
      this.groupBox11.ResumeLayout(false);
      this.groupBox11.PerformLayout();
      this.groupBox10.ResumeLayout(false);
      this.groupBox10.PerformLayout();
      this.groupBox9.ResumeLayout(false);
      this.groupBox9.PerformLayout();
      this.groupBox8.ResumeLayout(false);
      this.groupBox8.PerformLayout();
      this.groupBox7.ResumeLayout(false);
      this.groupBox7.PerformLayout();
      this.txtCon.EndInit();
      this.txtInt.EndInit();
      this.txtDex.EndInit();
      this.txtStr.EndInit();
      this.groupBox5.ResumeLayout(false);
      this.groupBox5.PerformLayout();
      this.groupBox4.ResumeLayout(false);
      this.groupBox4.PerformLayout();
      ((ISupportInitialize) this.pictureBox1).EndInit();
      ((ISupportInitialize) this.pictureBox23).EndInit();
      this.groupBox3.ResumeLayout(false);
      this.groupBox3.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
