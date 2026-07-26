// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Main
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using LcDevPack_TeamDamonA.ClientString;
using LcDevPack_TeamDamonA.Tools;
using LcDevPack_TeamDamonA.Tools.MemoryWorker;
using LcDevPack_TeamDamonA.Tools.MemoryWorker.Action;
using LcDevPack_TeamDamonA.Tools.MemoryWorker.Catalog_Editor;
using LcDevPack_TeamDamonA.Tools.MemoryWorker.EventDrop;
using LcDevPack_TeamDamonA.Tools.MemoryWorker.Item;
using LcDevPack_TeamDamonA.Tools.MemoryWorker.Jawel;
using LcDevPack_TeamDamonA.Tools.MemoryWorker.NewDaily;
using LcDevPack_TeamDamonA.Tools.MemoryWorker.NewExchange;
using LcDevPack_TeamDamonA.Tools.MemoryWorker.Passive;
using LcDevPack_TeamDamonA.Tools.MemoryWorker.PetEditor;
using LcDevPack_TeamDamonA.Tools.MemoryWorker.rareoption;
using LcDevPack_TeamDamonA.Tools.MemoryWorker.SetItem;
using LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneData;
using MySqlConnector;
using StringExporter;
using System;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Threading.Tasks;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA
{
  public class Main : Form
  {
    public static Connection connection = new Connection();
    private string Host = Main.connection.Settings.SqlHost;
    private string User = Main.connection.Settings.SqlUser;
    private string Password = Main.connection.Settings.SqlPassword;
    private string Database = Main.connection.Settings.SqlDatabase;
    private string Episode = Main.connection.Settings.Episode;
    private IContainer components = (IContainer) null;
    private MenuStrip menuStrip1;
    private ToolStripMenuItem aboutToolStripMenuItem;
    private ToolStripMenuItem reloadMemoryItemsToolStripMenuItem;
    private GroupBox groupBox1;
    private CheckedListBox checkedListBox1;
    private StatusStrip statusStrip1;
    private ToolStripStatusLabel statusLabel;
    private StatusStrip statusStrip2;
    private ToolStripMenuItem languageToolStripMenuItem;
    private ToolStripMenuItem changeLanguageToolStripMenuItem;
    private ToolStripMenuItem configToolStripMenuItem;
    private ToolStripMenuItem editConfigToolStripMenuItem;
    private ToolStripStatusLabel toolStripStatusLabel2;
    private ToolStripStatusLabel toolStripStatusLabel3;
    private ToolStripStatusLabel toolStripStatusLabel4;
    private Timer timer1;
    private PerformanceCounter performanceCounter1;
    private ProgressBar progressBar1;
    private ToolStripMenuItem updateLOGToolStripMenuItem;
    private ToolStripMenuItem clientToolsToolStripMenuItem;
    private ToolStripMenuItem oldDBEditorToolStripMenuItem;
    private ToolStripMenuItem otherToolsToolStripMenuItem;
    private ToolStripMenuItem xxxtexEditorToolStripMenuItem;
    private ToolStripMenuItem eventlodEditorToolStripMenuItem;
    private ToolStripMenuItem psdatEditorToolStripMenuItem;
    private ToolStripMenuItem actionEditorToolStripMenuItem;
    private ToolStripMenuItem itemComposeEditorToolStripMenuItem;
    private ToolStripMenuItem eventEditorToolStripMenuItem;
    private ToolStripMenuItem dropEventEditorToolStripMenuItem;
    private ToolStripMenuItem luckyDrawBoxEditorToolStripMenuItem;
    private ToolStripMenuItem itemCollectionEditorToolStripMenuItem;
    private ToolStripMenuItem nPCEditorToolStripMenuItem;
    private ToolStripMenuItem rewardPackageEditorToolStripMenuItem;
    private ToolStripMenuItem rareOptionEditorToolStripMenuItem;
    private ToolStripMenuItem skillsMagicEditorToolStripMenuItem;
    private ToolStripMenuItem titleEditorToolStripMenuItem;
    private ToolStripMenuItem zoneEditorToolStripMenuItem;
    private ToolStripMenuItem affinityEditorToolStripMenuItem;
    private ToolStripMenuItem makeItemEditorToolStripMenuItem;
    private ToolStripMenuItem monsterComboEditorToolStripMenuItem;
    private ToolStripMenuItem encryptToolToolStripMenuItem;
    private ToolStripMenuItem mD5GeneratorToolStripMenuItem;
    private ToolStripMenuItem oldDbEditorConfigToolStripMenuItem;
    private ToolStripMenuItem mapToolToolStripMenuItem;
    private ToolStripMenuItem zonedataToolStripMenuItem;
    private Label label113;
    private Label lblLang;
    private Label CurrentDB;
    private Label label1;
    private ToolStripStatusLabel toolStripStatusLabel1;
    private ToolStripMenuItem lodExporterToolStripMenuItem;
    private ToolStripMenuItem stringExporterToolStripMenuItem;
    private ToolStripMenuItem catalogFileOpenToolStripMenuItem;
    private ToolStripMenuItem zoneDataToolStripMenuItem1;
    private string language = ItemEditor2.connection.Settings.Language;

    public Main() => this.InitializeComponent();

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    [DllImport("kernel32.dll", SetLastError = true)]
    [return: MarshalAs(UnmanagedType.Bool)]
    private static extern bool AllocConsole();

    private void LoadLangAtStartup()
    {
      if (this.language == "GER")
        this.lblLang.Text = "German";
      else if (this.language == "POL")
        this.lblLang.Text = "Polish";
      else if (this.language == "BRA")
        this.lblLang.Text = "Brasilian";
      else if (this.language == "RUS")
        this.lblLang.Text = "Russian";
      else if (this.language == "FRA")
        this.lblLang.Text = "French";
      else if (this.language == "ESP")
        this.lblLang.Text = "Spanish";
      else if (this.language == "MEX")
        this.lblLang.Text = "Mex";
      else if (this.language == "THA")
        this.lblLang.Text = "Thai";
      else if (this.language == "ITA")
        this.lblLang.Text = "Italian";
      else if (this.language == "USA")
        this.lblLang.Text = "English";
      else
        this.lblLang.Text = "";
    }

    private async void Form1_Load(object sender, EventArgs e)
    {
      this.label1.Text = this.Database;
      this.LoadLangAtStartup();
      this.statusLabel.Text = "Version: " + Globals.Version;
      this.checkedListBox1.Items.AddRange(new object[38]
      {
        (object) "Catalog2",
        (object) "LuckyDraw",
        (object) "Magic",
        (object) "Moonstone",
        (object) "Option",
        (object) "Shop",
        (object) "Title",
        (object) "Skill",
        (object) "ItemEditor",
        (object) "MobEditor",
        (object) "QuestEditor",
        (object) "RewardEditor",
        (object) "AffinityEditor",
        (object) "ItemCollection",
        (object) "BigPetEditor",
        (object) "ExChange",
        (object) "LevelUpGuide",
        (object) "Jewel Prob",
        (object) "RareOption",
        (object) "DailyLogin",
        (object) "ZoneFlag",
        (object) "ZoneData",
        (object) "OX Quiz",
        (object) "StringEditor",
        (object) "Action",
        (object) "LoginReward",
        (object) "Drop Event",
        (object) "MapDtaEditor",
        (object) "String Client",
        (object) "LcBall Editor",
        (object) "SMC Editor",
        (object) "SetItem",
        (object) "MakeItem",
        (object) "O.X Reward",
        (object) "BattlePass",
        (object) "Party Dungeon",
        (object) "Passive Editor",
        (object) "Prestige"
      });

      // Title is set immediately from configured settings; we no longer perform a
      // separate "test" connection here because each *.Import() below already opens
      // its own MySQL connection. Doing it twice doubled startup latency on remote
      // servers (full TCP+TLS+auth handshake on the UI thread).
      this.Text = Globals.Name + $" [Server: {this.Host}]";

      // SetConnection() only builds connection strings; safe to call on UI thread.
      IconList.SetConnection();
      NpcList.SetConnection();
      IconSkill.SetConnection();
      QuestListPick.SetConnection();
      NpcShopList.SetConnection();
      AffinityList.SetConnection();
      OptionList.SetConnection();

      // Run the 7 Import() calls in parallel on the thread pool. Each Import opens
      // its own MySQL connection, so doing them sequentially on the UI thread cost
      // ~7 * RTT (very noticeable on non-local servers). Each list class writes to
      // its own static List, so they don't share mutable state with one another.
      this.checkedListBox1.Enabled = false;
      var importTasks = new (string Name, Task Task)[]
      {
        ("IconSkill",    Task.Run(() => IconSkill.Import())),
        ("IconList",     Task.Run(() => IconList.Import())),
        ("NpcList",      Task.Run(() => NpcList.Import())),
        ("QuestListPick",Task.Run(() => QuestListPick.Import())),
        ("NpcShopList",  Task.Run(() => NpcShopList.Import())),
        ("AffinityList", Task.Run(() => AffinityList.Import())),
        ("OptionList",   Task.Run(() => OptionList.Import())),
      };
      try
      {
        await Task.WhenAll(importTasks.Select(t => t.Task)).ConfigureAwait(true);
      }
      catch
      {
        // Report every failed Import individually so we can tell which one(s) blew up.
        var failures = importTasks
          .Where(t => t.Task.IsFaulted)
          .Select(t => $"[{t.Name}] {(t.Task.Exception?.InnerException ?? (Exception)t.Task.Exception)}")
          .ToArray();
        var combined = string.Join("\r\n\r\n", failures);
        if (failures.Any(f => f.Contains("MySqlException")))
          MessageBox.Show(combined);
        else
          MessageBox.Show(combined, "Unknown Exception", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }

      this.checkedListBox1.Enabled = true;
      if (!Globals.Console)
        return;
      Main.AllocConsole();
      Console.Title = "Debug Console";
      Console.WriteLine("Console Initialized.");
    }

    private void checkedListBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      foreach (string checkedItem in this.checkedListBox1.CheckedItems)
      {
        if (checkedItem == "Moonstone")
          new MoonstoneEditor().Show();
        if (checkedItem == "Skill")
          new SkillEditor().Show();
        if (checkedItem == "SkillV1")
          new SkillEditorV1().Show();
        if (checkedItem == "Catalog2")
          new CatalogEditor().Show();
        if (checkedItem == "Item")
          new ItemEditor().Show();
        if (checkedItem == "Option")
          new OptionEditor().Show();
        if (checkedItem == "Shop")
          new ShopEditor().Show();
        if (checkedItem == "Title")
          new TitleEditor().Show();
        if (checkedItem == "LuckyDraw")
          new LuckyDrawBoxTool().Show();
        if (checkedItem == "Magic")
          new LcDevPack_TeamDamonA.Tools.MemoryWorker.NewMagicEditor.NewMagicEditor().Show();
        if (checkedItem == "ItemEditor")
          new ItemEditor2().Show();
        if (checkedItem == "MobEditor")
          new LcDevPack_TeamDamonA.Tools.MobEditor().Show();
        if (checkedItem == "MobEditor2")
          new LcDevPack_TeamDamonA.Tools.MemoryWorker.MobEditor().Show();
        if (checkedItem == "QuestEditor")
          new QuestEditor().Show();
        if (checkedItem == "RewardEditor")
          new RewardEditor().Show();
        if (checkedItem == "AffinityEditor")
          new AffinityEditor().Show();
        if (checkedItem == "ItemCollection")
          new ItemCollection().Show();
        if (checkedItem == "SetItem")
          new SetitemEditor().Show();
        if (checkedItem == "MakeItemEditor")
          new LcDevPack_TeamDamonA.Tools.MakeItemEditor().Show();
        if (checkedItem == "BigPetEditor")
          new BigPetEditorr().Show();
        if (checkedItem == "ExChange")
          new ExchangeEditor().Show();
        if (checkedItem == "LevelUpGuide")
          new LcDevPack_TeamDamonA.Tools.MemoryWorker.LevelUpGuide.LevelUpGuide().Show();
        if (checkedItem == "Jewel Prob")
          new JawelData().Show();
        if (checkedItem == "ItemEP4")
          new ItemAll().Show();
        if (checkedItem == "RareOption")
          new RareOptionEditor().Show();
        if (checkedItem == "ZoneFlag")
          new LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag().Show();
        if (checkedItem == "ZoneData")
          new Zonedata().Show();
        if (checkedItem == "OX Quiz")
          new LcDevPack_TeamDamonA.Tools.MemoryWorker.OX.OX().Show();
        if (checkedItem == "SMC")
          new SMCEditor3.Form1().Show();
        if (checkedItem == "StringEditor")
          new String_Editor.Form1().Show();
        if (checkedItem == "Action")
          new ActionEditor().Show();
        if (checkedItem == "LoginReward")
          new LcDevPack_TeamDamonA.Tools.MemoryWorker.LoginReward.LoginReward().Show();
        if (checkedItem == "Drop Event")
          new EventDropTool().Show();
        if (checkedItem == "MapDtaEditor")
          new MapDtaRead.Form1().Show();
        if (checkedItem == "String Client")
          new ClientStringTool().Show();
        if (checkedItem == "LcBall Editor")
          new LcDevPack_TeamDamonA.LcBallEditor.LcBallEditor().Show();
        if (checkedItem == "SMC Editor")
          new SMCEditor4.Form1().Show();
        if (checkedItem == "MakeItem")
          new LcDevPack_TeamDamonA.Tools.MemoryWorker.MakeItem.MakeItemEditor().Show();
        if (checkedItem == "O.X Reward")
          new LcDevPack_TeamDamonA.Tools.MemoryWorker.OXRewards.OXReward().Show();
        if (checkedItem == "BattlePass")
          new LcDevPack_TeamDamonA.Tools.MemoryWorker.BattlePass.BattlePass().Show();
        if (checkedItem == "Party Dungeon")
          new LcDevPack_TeamDamonA.Tools.MemoryWorker.PartyDungeon.PartyDungeon().Show();
        if (checkedItem == "Passive Editor")
          new PassiveEditor().Show();
        if (checkedItem == "Prestige")
          new LcDevPack_TeamDamonA.Tools.MemoryWorker.Prestige.Prestige().Show();
      }
      for (int index = 0; index < this.checkedListBox1.Items.Count; ++index)
        this.checkedListBox1.SetItemChecked(index, false);
    }

    private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
    {
      int num = (int) MessageBox.Show("This website is not operated by gamigo AG. Last Chaos, ©Barunson Games Inc., published by gamigo AG 2008, LastChaos is a protected trademark, All rights reserved.", "Information");
    }

    private void reloadMemoryItemsToolStripMenuItem_Click(object sender, EventArgs e)
    {
      IconList.List.Clear();
      NpcList.List.Clear();
      IconSkill.List.Clear();
      QuestListPick.List.Clear();
      NpcShopList.List.Clear();
      AffinityList.List.Clear();
      OptionList.List.Clear();
      IconList.Import();
      NpcList.Import();
      IconSkill.Import();
      QuestListPick.Import();
      NpcShopList.Import();
      AffinityList.Import();
      OptionList.Import();
    }

    private void InitializeComponent()
    {
      this.components = (IContainer) new System.ComponentModel.Container();
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (Main));
      this.menuStrip1 = new MenuStrip();
      this.reloadMemoryItemsToolStripMenuItem = new ToolStripMenuItem();
      this.clientToolsToolStripMenuItem = new ToolStripMenuItem();
      this.lodExporterToolStripMenuItem = new ToolStripMenuItem();
      this.stringExporterToolStripMenuItem = new ToolStripMenuItem();
      this.xxxtexEditorToolStripMenuItem = new ToolStripMenuItem();
      this.eventlodEditorToolStripMenuItem = new ToolStripMenuItem();
      this.psdatEditorToolStripMenuItem = new ToolStripMenuItem();
      this.actionEditorToolStripMenuItem = new ToolStripMenuItem();
      this.itemComposeEditorToolStripMenuItem = new ToolStripMenuItem();
      this.catalogFileOpenToolStripMenuItem = new ToolStripMenuItem();
      this.zoneDataToolStripMenuItem1 = new ToolStripMenuItem();
      this.oldDBEditorToolStripMenuItem = new ToolStripMenuItem();
      this.eventEditorToolStripMenuItem = new ToolStripMenuItem();
      this.dropEventEditorToolStripMenuItem = new ToolStripMenuItem();
      this.luckyDrawBoxEditorToolStripMenuItem = new ToolStripMenuItem();
      this.itemCollectionEditorToolStripMenuItem = new ToolStripMenuItem();
      this.nPCEditorToolStripMenuItem = new ToolStripMenuItem();
      this.rewardPackageEditorToolStripMenuItem = new ToolStripMenuItem();
      this.rareOptionEditorToolStripMenuItem = new ToolStripMenuItem();
      this.skillsMagicEditorToolStripMenuItem = new ToolStripMenuItem();
      this.titleEditorToolStripMenuItem = new ToolStripMenuItem();
      this.zoneEditorToolStripMenuItem = new ToolStripMenuItem();
      this.affinityEditorToolStripMenuItem = new ToolStripMenuItem();
      this.makeItemEditorToolStripMenuItem = new ToolStripMenuItem();
      this.monsterComboEditorToolStripMenuItem = new ToolStripMenuItem();
      this.mapToolToolStripMenuItem = new ToolStripMenuItem();
      this.zonedataToolStripMenuItem = new ToolStripMenuItem();
      this.otherToolsToolStripMenuItem = new ToolStripMenuItem();
      this.encryptToolToolStripMenuItem = new ToolStripMenuItem();
      this.mD5GeneratorToolStripMenuItem = new ToolStripMenuItem();
      this.languageToolStripMenuItem = new ToolStripMenuItem();
      this.changeLanguageToolStripMenuItem = new ToolStripMenuItem();
      this.configToolStripMenuItem = new ToolStripMenuItem();
      this.editConfigToolStripMenuItem = new ToolStripMenuItem();
      this.oldDbEditorConfigToolStripMenuItem = new ToolStripMenuItem();
      this.aboutToolStripMenuItem = new ToolStripMenuItem();
      this.updateLOGToolStripMenuItem = new ToolStripMenuItem();
      this.groupBox1 = new GroupBox();
      this.checkedListBox1 = new CheckedListBox();
      this.statusStrip1 = new StatusStrip();
      this.statusLabel = new ToolStripStatusLabel();
      this.statusStrip2 = new StatusStrip();
      this.toolStripStatusLabel1 = new ToolStripStatusLabel();
      this.toolStripStatusLabel2 = new ToolStripStatusLabel();
      this.toolStripStatusLabel3 = new ToolStripStatusLabel();
      this.toolStripStatusLabel4 = new ToolStripStatusLabel();
      this.timer1 = new Timer(this.components);
      this.performanceCounter1 = new PerformanceCounter();
      this.progressBar1 = new ProgressBar();
      this.label113 = new Label();
      this.lblLang = new Label();
      this.CurrentDB = new Label();
      this.label1 = new Label();
      this.menuStrip1.SuspendLayout();
      this.groupBox1.SuspendLayout();
      this.statusStrip1.SuspendLayout();
      this.statusStrip2.SuspendLayout();
      this.performanceCounter1.BeginInit();
      this.SuspendLayout();
      this.menuStrip1.BackColor = SystemColors.ButtonHighlight;
      this.menuStrip1.GripStyle = ToolStripGripStyle.Visible;
      this.menuStrip1.ImageScalingSize = new Size(20, 20);
      this.menuStrip1.Items.AddRange(new ToolStripItem[7]
      {
        (ToolStripItem) this.reloadMemoryItemsToolStripMenuItem,
        (ToolStripItem) this.clientToolsToolStripMenuItem,
        (ToolStripItem) this.oldDBEditorToolStripMenuItem,
        (ToolStripItem) this.otherToolsToolStripMenuItem,
        (ToolStripItem) this.languageToolStripMenuItem,
        (ToolStripItem) this.configToolStripMenuItem,
        (ToolStripItem) this.aboutToolStripMenuItem
      });
      this.menuStrip1.Location = new Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Padding = new Padding(2, 2, 0, 2);
      this.menuStrip1.Size = new Size(906, 27);
      this.menuStrip1.TabIndex = 6;
      this.menuStrip1.Text = "menuStrip1";
      this.reloadMemoryItemsToolStripMenuItem.Name = "reloadMemoryItemsToolStripMenuItem";
      this.reloadMemoryItemsToolStripMenuItem.Size = new Size(102, 23);
      this.reloadMemoryItemsToolStripMenuItem.Text = "Reload Items";
      this.reloadMemoryItemsToolStripMenuItem.Click += new EventHandler(this.reloadMemoryItemsToolStripMenuItem_Click);
      this.clientToolsToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[9]
      {
        (ToolStripItem) this.lodExporterToolStripMenuItem,
        (ToolStripItem) this.stringExporterToolStripMenuItem,
        (ToolStripItem) this.xxxtexEditorToolStripMenuItem,
        (ToolStripItem) this.eventlodEditorToolStripMenuItem,
        (ToolStripItem) this.psdatEditorToolStripMenuItem,
        (ToolStripItem) this.actionEditorToolStripMenuItem,
        (ToolStripItem) this.itemComposeEditorToolStripMenuItem,
        (ToolStripItem) this.catalogFileOpenToolStripMenuItem,
        (ToolStripItem) this.zoneDataToolStripMenuItem1
      });
      this.clientToolsToolStripMenuItem.Name = "clientToolsToolStripMenuItem";
      this.clientToolsToolStripMenuItem.Size = new Size(93, 23);
      this.clientToolsToolStripMenuItem.Text = "Client Tools";
      this.lodExporterToolStripMenuItem.Name = "lodExporterToolStripMenuItem";
      this.lodExporterToolStripMenuItem.Size = new Size(212, 24);
      this.lodExporterToolStripMenuItem.Text = "LodExporter";
      this.lodExporterToolStripMenuItem.Click += new EventHandler(this.lodExporterToolStripMenuItem_Click_1);
      this.stringExporterToolStripMenuItem.Name = "stringExporterToolStripMenuItem";
      this.stringExporterToolStripMenuItem.Size = new Size(212, 24);
      this.stringExporterToolStripMenuItem.Text = "StringExporter";
      this.stringExporterToolStripMenuItem.Click += new EventHandler(this.stringExporterToolStripMenuItem_Click);
      this.xxxtexEditorToolStripMenuItem.Name = "xxxtexEditorToolStripMenuItem";
      this.xxxtexEditorToolStripMenuItem.Size = new Size(212, 24);
      this.xxxtexEditorToolStripMenuItem.Text = "xxx.tex Editor";
      this.xxxtexEditorToolStripMenuItem.Click += new EventHandler(this.xxxtexEditorToolStripMenuItem_Click);
      this.eventlodEditorToolStripMenuItem.Name = "eventlodEditorToolStripMenuItem";
      this.eventlodEditorToolStripMenuItem.Size = new Size(212, 24);
      this.eventlodEditorToolStripMenuItem.Text = "Event.lod Editor";
      this.eventlodEditorToolStripMenuItem.Click += new EventHandler(this.eventlodEditorToolStripMenuItem_Click);
      this.psdatEditorToolStripMenuItem.Name = "psdatEditorToolStripMenuItem";
      this.psdatEditorToolStripMenuItem.Size = new Size(212, 24);
      this.psdatEditorToolStripMenuItem.Text = "Ps.dat Editor";
      this.psdatEditorToolStripMenuItem.Click += new EventHandler(this.psdatEditorToolStripMenuItem_Click);
      this.actionEditorToolStripMenuItem.Name = "actionEditorToolStripMenuItem";
      this.actionEditorToolStripMenuItem.Size = new Size(212, 24);
      this.actionEditorToolStripMenuItem.Text = "Action Editor";
      this.actionEditorToolStripMenuItem.Click += new EventHandler(this.actionEditorToolStripMenuItem_Click);
      this.itemComposeEditorToolStripMenuItem.Name = "itemComposeEditorToolStripMenuItem";
      this.itemComposeEditorToolStripMenuItem.Size = new Size(212, 24);
      this.itemComposeEditorToolStripMenuItem.Text = "ItemCompose Editor";
      this.itemComposeEditorToolStripMenuItem.Click += new EventHandler(this.itemComposeEditorToolStripMenuItem_Click);
      this.catalogFileOpenToolStripMenuItem.Name = "catalogFileOpenToolStripMenuItem";
      this.catalogFileOpenToolStripMenuItem.Size = new Size(212, 24);
      this.catalogFileOpenToolStripMenuItem.Text = "Catalog File Open";
      this.catalogFileOpenToolStripMenuItem.Click += new EventHandler(this.catalogFileOpenToolStripMenuItem_Click);
      this.zoneDataToolStripMenuItem1.Name = "zoneDataToolStripMenuItem1";
      this.zoneDataToolStripMenuItem1.Size = new Size(212, 24);
      this.zoneDataToolStripMenuItem1.Text = "ZoneData";
      this.zoneDataToolStripMenuItem1.Click += new EventHandler(this.zoneDataEditorAzazelToolStripMenuItem_Click);
      this.oldDBEditorToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[15]
      {
        (ToolStripItem) this.eventEditorToolStripMenuItem,
        (ToolStripItem) this.dropEventEditorToolStripMenuItem,
        (ToolStripItem) this.luckyDrawBoxEditorToolStripMenuItem,
        (ToolStripItem) this.itemCollectionEditorToolStripMenuItem,
        (ToolStripItem) this.nPCEditorToolStripMenuItem,
        (ToolStripItem) this.rewardPackageEditorToolStripMenuItem,
        (ToolStripItem) this.rareOptionEditorToolStripMenuItem,
        (ToolStripItem) this.skillsMagicEditorToolStripMenuItem,
        (ToolStripItem) this.titleEditorToolStripMenuItem,
        (ToolStripItem) this.zoneEditorToolStripMenuItem,
        (ToolStripItem) this.affinityEditorToolStripMenuItem,
        (ToolStripItem) this.makeItemEditorToolStripMenuItem,
        (ToolStripItem) this.monsterComboEditorToolStripMenuItem,
        (ToolStripItem) this.mapToolToolStripMenuItem,
        (ToolStripItem) this.zonedataToolStripMenuItem
      });
      this.oldDBEditorToolStripMenuItem.Name = "oldDBEditorToolStripMenuItem";
      this.oldDBEditorToolStripMenuItem.Size = new Size(157, 23);
      this.oldDBEditorToolStripMenuItem.Text = "Oficial Tools DB Editor";
      this.eventEditorToolStripMenuItem.Name = "eventEditorToolStripMenuItem";
      this.eventEditorToolStripMenuItem.Size = new Size(227, 24);
      this.eventEditorToolStripMenuItem.Text = "Event Editor";
      this.eventEditorToolStripMenuItem.Click += new EventHandler(this.eventEditorToolStripMenuItem_Click);
      this.dropEventEditorToolStripMenuItem.Name = "dropEventEditorToolStripMenuItem";
      this.dropEventEditorToolStripMenuItem.Size = new Size(227, 24);
      this.dropEventEditorToolStripMenuItem.Text = "Drop Event Editor";
      this.dropEventEditorToolStripMenuItem.Click += new EventHandler(this.dropEventEditorToolStripMenuItem_Click);
      this.luckyDrawBoxEditorToolStripMenuItem.Name = "luckyDrawBoxEditorToolStripMenuItem";
      this.luckyDrawBoxEditorToolStripMenuItem.Size = new Size(227, 24);
      this.luckyDrawBoxEditorToolStripMenuItem.Text = "LuckyDrawBox Editor";
      this.luckyDrawBoxEditorToolStripMenuItem.Click += new EventHandler(this.luckyDrawBoxEditorToolStripMenuItem_Click);
      this.itemCollectionEditorToolStripMenuItem.Name = "itemCollectionEditorToolStripMenuItem";
      this.itemCollectionEditorToolStripMenuItem.Size = new Size(227, 24);
      this.itemCollectionEditorToolStripMenuItem.Text = "ItemCollection Editor";
      this.itemCollectionEditorToolStripMenuItem.Click += new EventHandler(this.itemCollectionEditorToolStripMenuItem_Click);
      this.nPCEditorToolStripMenuItem.Name = "nPCEditorToolStripMenuItem";
      this.nPCEditorToolStripMenuItem.Size = new Size(227, 24);
      this.nPCEditorToolStripMenuItem.Text = "NPC Editor";
      this.nPCEditorToolStripMenuItem.Click += new EventHandler(this.nPCEditorToolStripMenuItem_Click);
      this.rewardPackageEditorToolStripMenuItem.Name = "rewardPackageEditorToolStripMenuItem";
      this.rewardPackageEditorToolStripMenuItem.Size = new Size(227, 24);
      this.rewardPackageEditorToolStripMenuItem.Text = "Reward Package Editor";
      this.rewardPackageEditorToolStripMenuItem.Click += new EventHandler(this.rewardPackageEditorToolStripMenuItem_Click);
      this.rareOptionEditorToolStripMenuItem.Name = "rareOptionEditorToolStripMenuItem";
      this.rareOptionEditorToolStripMenuItem.Size = new Size(227, 24);
      this.rareOptionEditorToolStripMenuItem.Text = "Rare Option Editor";
      this.rareOptionEditorToolStripMenuItem.Click += new EventHandler(this.rareOptionEditorToolStripMenuItem_Click);
      this.skillsMagicEditorToolStripMenuItem.Name = "skillsMagicEditorToolStripMenuItem";
      this.skillsMagicEditorToolStripMenuItem.Size = new Size(227, 24);
      this.skillsMagicEditorToolStripMenuItem.Text = "Skills And Magic Editor";
      this.skillsMagicEditorToolStripMenuItem.Click += new EventHandler(this.skillsMagicEditorToolStripMenuItem_Click);
      this.titleEditorToolStripMenuItem.Name = "titleEditorToolStripMenuItem";
      this.titleEditorToolStripMenuItem.Size = new Size(227, 24);
      this.titleEditorToolStripMenuItem.Text = "Title Editor";
      this.titleEditorToolStripMenuItem.Click += new EventHandler(this.titleEditorToolStripMenuItem_Click);
      this.zoneEditorToolStripMenuItem.Name = "zoneEditorToolStripMenuItem";
      this.zoneEditorToolStripMenuItem.Size = new Size(227, 24);
      this.zoneEditorToolStripMenuItem.Text = "Zone Editor";
      this.zoneEditorToolStripMenuItem.Click += new EventHandler(this.zoneEditorToolStripMenuItem_Click);
      this.affinityEditorToolStripMenuItem.Name = "affinityEditorToolStripMenuItem";
      this.affinityEditorToolStripMenuItem.Size = new Size(227, 24);
      this.affinityEditorToolStripMenuItem.Text = "Affinity Editor";
      this.affinityEditorToolStripMenuItem.Click += new EventHandler(this.affinityEditorToolStripMenuItem_Click);
      this.makeItemEditorToolStripMenuItem.Name = "makeItemEditorToolStripMenuItem";
      this.makeItemEditorToolStripMenuItem.Size = new Size(227, 24);
      this.makeItemEditorToolStripMenuItem.Text = "MakeItem Editor";
      this.makeItemEditorToolStripMenuItem.Click += new EventHandler(this.makeItemEditorToolStripMenuItem_Click);
      this.monsterComboEditorToolStripMenuItem.Name = "monsterComboEditorToolStripMenuItem";
      this.monsterComboEditorToolStripMenuItem.Size = new Size(227, 24);
      this.monsterComboEditorToolStripMenuItem.Text = "Monster Combo Editor";
      this.monsterComboEditorToolStripMenuItem.Click += new EventHandler(this.monsterComboEditorToolStripMenuItem_Click);
      this.mapToolToolStripMenuItem.Name = "mapToolToolStripMenuItem";
      this.mapToolToolStripMenuItem.Size = new Size(227, 24);
      this.mapToolToolStripMenuItem.Text = "MapTool";
      this.mapToolToolStripMenuItem.Click += new EventHandler(this.mapToolToolStripMenuItem_Click);
      this.zonedataToolStripMenuItem.Name = "zonedataToolStripMenuItem";
      this.zonedataToolStripMenuItem.Size = new Size(227, 24);
      this.zonedataToolStripMenuItem.Text = "Zonedata";
      this.zonedataToolStripMenuItem.Click += new EventHandler(this.zonedataToolStripMenuItem_Click);
      this.otherToolsToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[2]
      {
        (ToolStripItem) this.encryptToolToolStripMenuItem,
        (ToolStripItem) this.mD5GeneratorToolStripMenuItem
      });
      this.otherToolsToolStripMenuItem.Name = "otherToolsToolStripMenuItem";
      this.otherToolsToolStripMenuItem.Size = new Size(94, 23);
      this.otherToolsToolStripMenuItem.Text = "Other Tools";
      this.encryptToolToolStripMenuItem.Name = "encryptToolToolStripMenuItem";
      this.encryptToolToolStripMenuItem.Size = new Size(179, 24);
      this.encryptToolToolStripMenuItem.Text = "Encrypt Tool";
      this.encryptToolToolStripMenuItem.Click += new EventHandler(this.encryptToolToolStripMenuItem_Click);
      this.mD5GeneratorToolStripMenuItem.Name = "mD5GeneratorToolStripMenuItem";
      this.mD5GeneratorToolStripMenuItem.Size = new Size(179, 24);
      this.mD5GeneratorToolStripMenuItem.Text = "MD5Generator";
      this.mD5GeneratorToolStripMenuItem.Click += new EventHandler(this.mD5GeneratorToolStripMenuItem_Click);
      this.languageToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.changeLanguageToolStripMenuItem
      });
      this.languageToolStripMenuItem.Name = "languageToolStripMenuItem";
      this.languageToolStripMenuItem.Size = new Size(83, 23);
      this.languageToolStripMenuItem.Text = "Language";
      this.languageToolStripMenuItem.Click += new EventHandler(this.languageToolStripMenuItem_Click);
      this.changeLanguageToolStripMenuItem.Name = "changeLanguageToolStripMenuItem";
      this.changeLanguageToolStripMenuItem.Size = new Size(197, 24);
      this.changeLanguageToolStripMenuItem.Text = "Change Language";
      this.changeLanguageToolStripMenuItem.Click += new EventHandler(this.changeLanguageToolStripMenuItem_Click);
      this.configToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[2]
      {
        (ToolStripItem) this.editConfigToolStripMenuItem,
        (ToolStripItem) this.oldDbEditorConfigToolStripMenuItem
      });
      this.configToolStripMenuItem.Name = "configToolStripMenuItem";
      this.configToolStripMenuItem.Size = new Size(63, 23);
      this.configToolStripMenuItem.Text = "Config";
      this.editConfigToolStripMenuItem.Name = "editConfigToolStripMenuItem";
      this.editConfigToolStripMenuItem.Size = new Size(206, 24);
      this.editConfigToolStripMenuItem.Text = "Edit Config";
      this.editConfigToolStripMenuItem.Click += new EventHandler(this.editConfigToolStripMenuItem_Click);
      this.oldDbEditorConfigToolStripMenuItem.Name = "oldDbEditorConfigToolStripMenuItem";
      this.oldDbEditorConfigToolStripMenuItem.Size = new Size(206, 24);
      this.oldDbEditorConfigToolStripMenuItem.Text = "Official Tools Config";
      this.oldDbEditorConfigToolStripMenuItem.Click += new EventHandler(this.oldDbEditorConfigToolStripMenuItem_Click);
      this.aboutToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.updateLOGToolStripMenuItem
      });
      this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
      this.aboutToolStripMenuItem.Size = new Size(61, 23);
      this.aboutToolStripMenuItem.Text = "About";
      this.aboutToolStripMenuItem.Click += new EventHandler(this.aboutToolStripMenuItem_Click);
      this.updateLOGToolStripMenuItem.Name = "updateLOGToolStripMenuItem";
      this.updateLOGToolStripMenuItem.Size = new Size(159, 24);
      this.updateLOGToolStripMenuItem.Text = "UpdateLOG";
      this.groupBox1.Controls.Add((Control) this.checkedListBox1);
      this.groupBox1.Font = new Font("Arial", 14f, FontStyle.Regular, GraphicsUnit.Pixel, (byte) 0);
      this.groupBox1.Location = new Point(9, 29);
      this.groupBox1.Margin = new Padding(5, 5, 5, 5);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Padding = new Padding(5, 5, 5, 5);
      this.groupBox1.Size = new Size(883, 287);
      this.groupBox1.TabIndex = 7;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Episode 4";
      this.checkedListBox1.BackColor = SystemColors.Control;
      this.checkedListBox1.BorderStyle = BorderStyle.None;
      this.checkedListBox1.CheckOnClick = true;
      this.checkedListBox1.Dock = DockStyle.Fill;
      this.checkedListBox1.Enabled = false;
      this.checkedListBox1.FormattingEnabled = true;
      this.checkedListBox1.Location = new Point(5, 22);
      this.checkedListBox1.Margin = new Padding(5, 5, 5, 5);
      this.checkedListBox1.MultiColumn = true;
      this.checkedListBox1.Name = "checkedListBox1";
      this.checkedListBox1.Size = new Size(873, 260);
      this.checkedListBox1.Sorted = true;
      this.checkedListBox1.TabIndex = 0;
      this.checkedListBox1.SelectedIndexChanged += new EventHandler(this.checkedListBox1_SelectedIndexChanged);
      this.statusStrip1.ImageScalingSize = new Size(20, 20);
      this.statusStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.statusLabel
      });
      this.statusStrip1.Location = new Point(0, 345);
      this.statusStrip1.Name = "statusStrip1";
      this.statusStrip1.Size = new Size(906, 24);
      this.statusStrip1.TabIndex = 8;
      this.statusStrip1.Text = "statusStrip1";
      this.statusLabel.Name = "statusLabel";
      this.statusLabel.Size = new Size(47, 19);
      this.statusLabel.Text = "Status";
      this.statusStrip2.ImageScalingSize = new Size(20, 20);
      this.statusStrip2.Items.AddRange(new ToolStripItem[4]
      {
        (ToolStripItem) this.toolStripStatusLabel1,
        (ToolStripItem) this.toolStripStatusLabel2,
        (ToolStripItem) this.toolStripStatusLabel3,
        (ToolStripItem) this.toolStripStatusLabel4
      });
      this.statusStrip2.Location = new Point(0, 321);
      this.statusStrip2.Name = "statusStrip2";
      this.statusStrip2.Size = new Size(906, 24);
      this.statusStrip2.TabIndex = 9;
      this.statusStrip2.Text = "statusStrip2";
      this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
      this.toolStripStatusLabel1.Size = new Size(47, 19);
      this.toolStripStatusLabel1.Text = "Status";
      this.toolStripStatusLabel2.Name = "toolStripStatusLabel2";
      this.toolStripStatusLabel2.Size = new Size(0, 19);
      this.toolStripStatusLabel3.Name = "toolStripStatusLabel3";
      this.toolStripStatusLabel3.Size = new Size(12, 19);
      this.toolStripStatusLabel3.Text = ":";
      this.toolStripStatusLabel4.Name = "toolStripStatusLabel4";
      this.toolStripStatusLabel4.Size = new Size(139, 19);
      this.toolStripStatusLabel4.Text = "toolStripStatusLabel4";
      this.toolStripStatusLabel4.Click += new EventHandler(this.toolStripStatusLabel4_Click);
      this.timer1.Enabled = true;
      this.timer1.Interval = 1000;
      this.timer1.Tick += new EventHandler(this.timer1_Tick);
      this.performanceCounter1.CategoryName = "Processor";
      this.performanceCounter1.CounterName = "% Processor Time";
      this.performanceCounter1.InstanceName = "_Total";
      this.progressBar1.Location = new Point(709, 4);
      this.progressBar1.Name = "progressBar1";
      this.progressBar1.Size = new Size(100, 16);
      this.progressBar1.TabIndex = 10;
      this.label113.AutoSize = true;
      this.label113.BackColor = SystemColors.ControlLightLight;
      this.label113.Font = new Font("Microsoft Sans Serif", 9.75f, FontStyle.Bold, GraphicsUnit.Point, (byte) 0);
      this.label113.Location = new Point(645, 351);
      this.label113.Name = "label113";
      this.label113.Size = new Size(169, 18);
      this.label113.TabIndex = 53;
      this.label113.Text = "Current Language is :";
      this.lblLang.AutoSize = true;
      this.lblLang.ForeColor = Color.DarkMagenta;
      this.lblLang.Location = new Point(806, 351);
      this.lblLang.Name = "lblLang";
      this.lblLang.Size = new Size(41, 13);
      this.lblLang.TabIndex = 54;
      this.lblLang.Text = "lblLang";
      this.CurrentDB.AutoSize = true;
      this.CurrentDB.BackColor = SystemColors.ControlLightLight;
      this.CurrentDB.Font = new Font("Microsoft Sans Serif", 9.75f, FontStyle.Bold, GraphicsUnit.Point, (byte) 0);
      this.CurrentDB.Location = new Point(363, 351);
      this.CurrentDB.Name = "CurrentDB";
      this.CurrentDB.Size = new Size(102, 18);
      this.CurrentDB.TabIndex = 55;
      this.CurrentDB.Text = "Current DB :";
      this.label1.AutoSize = true;
      this.label1.ForeColor = Color.DarkMagenta;
      this.label1.Location = new Point(459, 351);
      this.label1.Name = "label1";
      this.label1.Size = new Size(35, 13);
      this.label1.TabIndex = 56;
      this.label1.Text = "label1";
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(906, 369);
      this.Controls.Add((Control) this.label1);
      this.Controls.Add((Control) this.CurrentDB);
      this.Controls.Add((Control) this.lblLang);
      this.Controls.Add((Control) this.label113);
      this.Controls.Add((Control) this.progressBar1);
      this.Controls.Add((Control) this.statusStrip2);
      this.Controls.Add((Control) this.statusStrip1);
      this.Controls.Add((Control) this.groupBox1);
      this.Controls.Add((Control) this.menuStrip1);
      this.FormBorderStyle = FormBorderStyle.Fixed3D;
      this.Icon = (Icon) componentResourceManager.GetObject("$this.Icon");
      this.Name = nameof (Main);
      this.Text = "LastChaos mutli Tool ";
      this.Load += new EventHandler(this.Form1_Load);
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.groupBox1.ResumeLayout(false);
      this.statusStrip1.ResumeLayout(false);
      this.statusStrip1.PerformLayout();
      this.statusStrip2.ResumeLayout(false);
      this.statusStrip2.PerformLayout();
      this.performanceCounter1.EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();
    }

    private void languageToolStripMenuItem_Click(object sender, EventArgs e)
    {
    }

    private void changeLanguageToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (new LangSelect().ShowDialog() == DialogResult.OK)
        ;
    }

        private void editConfigToolStripMenuItem_Click(object sender, EventArgs e)
        {
            using (var form = new LcDevPack_TeamDamonA.Tools.Settings())
            {
                if (form.ShowDialog() == DialogResult.OK)
                {
                    // Optional: reload settings after closing
                }
            }
        }



        private void toolStripStatusLabel4_Click(object sender, EventArgs e)
    {
    }

    private void timer1_Tick(object sender, EventArgs e)
    {
      this.progressBar1.Value = (int) this.performanceCounter1.NextValue();
      this.toolStripStatusLabel4.Text = "Processor Time: " + this.progressBar1.Value.ToString() + "%";
    }

    private void lodExporterToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Process.Start("LodExporter\\LodExporter.exe");
    }

    private void strxxlodExporterToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Process.Start("StrExporter\\StringExporter.exe");
    }

    private void stringEditorToolStripMenuItem_Click(object sender, EventArgs e)
    {
      new String_Editor.Form1().Show();
    }

    private void sMCEditorToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Process.Start("ect\\SMC\\SMCEditor4.exe");
    }

    private void catalogEditorTHToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Process.Start("ect\\Catalog\\Catalog Editor.exe");
    }

    private void zoneDataEditorAzazelToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Process.Start("ect\\AzazelTools\\ZoneData Editor.exe");
    }

    private void zoneFlagEditorAzazelToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Process.Start("ect\\AzazelTools\\ZoneFlag Editor.exe");
    }

    private void xxxtexEditorToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Process.Start("ect\\Textool\\textool.exe");
    }

    private void eventlodEditorToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Process.Start("ect\\Event_Editor\\event.lod-Editor.exe");
    }

    private void psdatEditorToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Process.Start("ect\\PersistentSymbolTool\\PersistentSymbolTool.exe");
    }

    private void skillTreeEditorToolStripMenuItem_Click(object sender, EventArgs e)
    {
    }

    private void optionEditorToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Process.Start("ect\\AzazelTools\\OptionEditor.exe");
    }

    private void actionEditorToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Process.Start("ect\\ActionEditor\\EP4_ActionEditor.exe");
    }

    private void itemComposeEditorToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Process.Start("ect\\CompositionEditor2015\\CompositionEditorEP4.exe");
    }

    private void zoneEditorEditorEp4ToolStripMenuItem_Click(object sender, EventArgs e)
    {
      new Zonedata().Show();
    }

    private void eventEditorToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Process.Start("OfficialToolsEP4\\EventTool2012.exe");
    }

    private void dropEventEditorToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Process.Start("OfficialToolsEP4\\DropItemTools.exe");
    }

    private void luckyDrawBoxEditorToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Process.Start("OfficialToolsEP4\\LuckyDrawBox.exe");
    }

    private void itemCollectionEditorToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Process.Start("OfficialToolsEP4\\ItemCollectionTool.exe");
    }

    private void nPCEditorToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Process.Start("OfficialToolsEP4\\NPCTool.exe");
    }

    private void rewardPackageEditorToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Process.Start("OfficialToolsEP4\\RewardTool.exe");
    }

    private void rareOptionEditorToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Process.Start("OfficialToolsEP4\\RareOptionTool.exe");
    }

    private void skillsMagicEditorToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Process.Start("OfficialToolsEP4\\SkillTool.exe");
    }

    private void titleEditorToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Process.Start("OfficialToolsEP4\\TitleTool.exe");
    }

    private void zoneEditorToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Process.Start("OfficialToolsEP4\\ZoneDataTool.exe");
    }

    private void affinityEditorToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Process.Start("OfficialToolsEP4\\AffinityTool.exe");
    }

    private void makeItemEditorToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Process.Start("OfficialToolsEP4\\MakeList.exe");
    }

    private void monsterComboEditorToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Process.Start("OfficialToolsEP4\\MonsterCombo.exe");
    }

    private void encryptToolToolStripMenuItem_Click(object sender, EventArgs e)
    {
      new EncryptTool.Form1().Show();
    }

    private void mD5GeneratorToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Process.Start("ect\\Md5 password Hasher\\MD5Generator.exe");
    }

    private void oldDbEditorConfigToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Process.Start("DB_Config.ini");
    }

    private void lodExporterToolStripMenuItem1_Click(object sender, EventArgs e)
    {
      Process.Start("config.txt");
    }

    private void strExporterDBConfigToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Process.Start("StrExporter\\StrConfig_db.ini");
    }

    private void lodSaveLocationConfigToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Process.Start("config.ini");
    }

    private void strxxlodSaveLocationConfigToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Process.Start("StrConfig.ini");
    }

    private void catalogToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Process.Start("ect\\Catalog\\Catalog Editor 4.exe");
    }

    private void zoneFlagEditorToolStripMenuItem_Click(object sender, EventArgs e)
    {
      new LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneFlag.ZoneFlag().Show();
    }

    private void mapToolToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Process.Start("OfficialToolsEP4\\MapTool.exe");
    }

    private void zonedataToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Process.Start("OfficialToolsEP4\\ZoneDataTool.exe");
    }

    private void zoneToolsLCTMToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Process.Start("LCMT\\LCMT.exe");
    }

    private void zoneLCMTToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Process.Start("LCMT.ini");
    }

    private void lodExporterToolStripMenuItem_Click_1(object sender, EventArgs e)
    {
      new LodExporter.LodExporter().Show();
    }

    private void stringExporterToolStripMenuItem_Click(object sender, EventArgs e)
    {
      new FormExport().Show();
    }

    private void catalogFileOpenToolStripMenuItem_Click(object sender, EventArgs e)
    {
      new Form2().Show();
    }
  }
}
