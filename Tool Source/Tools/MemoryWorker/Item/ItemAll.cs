// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.Item.ItemAll
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using SlimDX;
using SlimDX.Direct3D9;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.Item
{
  public class ItemAll : Form
  {
    private Direct3D mD3d;
    public static List<ItemContainer> ItemList = new List<ItemContainer>();
    public static Connection connection = new Connection();
    private string Host = ItemAll.connection.Settings.SqlHost;
    private string User = ItemAll.connection.Settings.SqlUser;
    private string Password = ItemAll.connection.Settings.SqlPassword;
    private string Database = ItemAll.connection.Settings.SqlDatabase;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    private ExportLodHandle exportLodHandle = new ExportLodHandle();
    public string _ClientPath = LcDevPack_TeamDamonA.Tools.MobEditor.connection.Settings.ClientPath;
    private bool CaptureChanges;
    private Device device;
    private ASCIIEncoding Enc = new ASCIIEncoding();
    private float zoom;
    private List<tMesh> models;
    private float rotation;
    private float leftright;
    private float updown = -0.9f;
    public static string OpenedFile;
    private IContainer components = (IContainer) null;
    private MenuStrip menuStrip1;
    private ToolStripMenuItem fileToolStripMenuItem;
    private ToolStripMenuItem openToolStripMenuItem;
    private ToolStripSeparator toolStripSeparator1;
    private ToolStripMenuItem saveToolStripMenuItem;
    private ToolStripMenuItem saveasToolStripMenuItem;
    private ToolStripSeparator toolStripSeparator2;
    private ToolStripMenuItem exitToolStripMenuItem1;
    private ToolStripMenuItem exportToolStripMenuItem;
    private ToolStripMenuItem toolStripMenuItem1;
    private ToolStripMenuItem sQLToolStripMenuItem;
    private ToolStripMenuItem xMLToolStripMenuItem;
    private ToolStripMenuItem itemnameToolStripMenuItem;
    private ToolStripMenuItem hTMLToolStripMenuItem;
    private ToolStripMenuItem thisToolStripMenuItem;
    private ToolStripMenuItem insertQueryToolStripMenuItem;
    private ToolStripMenuItem updateQueryToolStripMenuItem;
    private ToolStripMenuItem toolsToolStripMenuItem;
    private ToolStripMenuItem iconViewerToolStripMenuItem;
    private ToolStripMenuItem itemFlagBuilderToolStripMenuItem;
    private ToolStripMenuItem mySQLConnectionToolStripMenuItem;
    private ToolStripMenuItem uPDATEThisRecordToolStripMenuItem;
    private ToolStripMenuItem iNSERTThisRecordToolStripMenuItem;
    private ToolStripMenuItem configConnectionToolStripMenuItem;
    private ToolStripMenuItem massActionToolStripMenuItem;
    private ToolStripMenuItem iNSERTALLNotExistingToolStripMenuItem;
    private ToolStripMenuItem uPDATEINSERTThisRecordToolStripMenuItem;
    private ToolStripMenuItem gETALLFromDatabaseToolStripMenuItem;
    private ToolStripMenuItem updateAllNamesToDBToolStripMenuItem;
    private ToolStripMenuItem updateAllFlagsToDBToolStripMenuItem;
    private ToolStripMenuItem updateAllPicsToDBToolStripMenuItem;
    private ToolStripMenuItem extraToolStripMenuItem;
    private ToolStripMenuItem updateAllNamesInDatabaseToolStripMenuItem;
    private ToolStripMenuItem toolStripMenuItem2;
    private ToolStripMenuItem getRecordsFromOtherFileToolStripMenuItem;
    private ToolStripMenuItem updateAllPricesInDatabaseToolStripMenuItem;
    private ToolStripMenuItem getPhpItemlistToolStripMenuItem;
    private ToolStripMenuItem removeAllIconsAbove9ToolStripMenuItem;
    private ToolStripMenuItem removeAllIconsAbove14ToolStripMenuItem;
    private ToolStripMenuItem getAllFlagsFromOtherFileToolStripMenuItem;
    private ToolStripMenuItem getIconsFromOtherFileToolStripMenuItem;
    private TabControl tabControl2;
    private TabPage tabPage3;
    private GroupBox groupBox1;
    private CheckBox chk3D;
    private TrackBar slideLeftRight;
    private TrackBar slideUpDown;
    private TrackBar slideZoom;
    private Panel panel3DView;
    private GroupBox groupBox2;
    private Button button2;
    private TextBox t_SMC;
    private Label label55;
    private TextBox t_Description;
    private Label label4;
    private TextBox t_ItemName;
    private Label label3;
    private TextBox t_ItemID;
    private Label label2;
    private GroupBox groupBox3;
    private PictureBox t_Icon;
    private LinkLabel t_iconpick;
    private TextBox t_IconColumn;
    private Label label7;
    private TextBox t_IconRow;
    private Label label6;
    private TextBox t_IconID;
    private Label label5;
    private GroupBox groupBox4;
    private TextBox t_EffectDamage;
    private Label label8;
    private TextBox t_EffectAttack;
    private Label label9;
    private TextBox t_EffectNormal;
    private Label label10;
    private GroupBox groupBox10;
    private TextBox t_Set5;
    private Label label34;
    private TextBox t_Set4;
    private Label label30;
    private TextBox t_Set3;
    private Label label31;
    private TextBox t_Set2;
    private Label label32;
    private TextBox t_Set1;
    private Label label33;
    private GroupBox groupBox5;
    private TextBox t_Price;
    private TextBox t_Weight;
    private TextBox t_Level;
    private Label label11;
    private GroupBox groupBox8;
    private TextBox t_RareOptionRate;
    private Label label24;
    private TextBox t_RareOptionID;
    private Label label25;
    private GroupBox groupBox7;
    private TextBox t_maxuse;
    private Label label76;
    private Button button1;
    private TextBox t_Flag;
    private Label label22;
    private ComboBox t_WearingPosCombo;
    private TextBox t_WearingPos;
    private Label label21;
    private TextBox t_Class;
    private Label label20;
    private ComboBox t_SubTypeCombo;
    private TextBox t_SubType;
    private Label label19;
    private ComboBox t_TypeCombo;
    private TextBox t_Type;
    private Label label18;
    private TabPage tabPage4;
    private GroupBox groupBox11;
    private TabControl tabControl1;
    private TabPage tabPage1;
    private DataGridView CraftGrid;
    private DataGridViewImageColumn ItemIcon;
    private DataGridViewTextBoxColumn ItemID;
    private DataGridViewTextBoxColumn ItemName;
    private DataGridViewTextBoxColumn Amount;
    private TabPage tabPage2;
    private Button t_CraftItemSearch10;
    private TextBox t_CraftItemAmount10;
    private TextBox t_CraftItemID10;
    private Label label45;
    private Label label46;
    private TextBox t_CraftItemAmount9;
    private TextBox t_CraftItemID9;
    private Label label47;
    private Label label48;
    private TextBox t_CraftItemAmount8;
    private TextBox t_CraftItemID8;
    private Label label49;
    private Label label50;
    private TextBox t_CraftItemAmount7;
    private TextBox t_CraftItemID7;
    private Label label51;
    private Label label52;
    private TextBox t_CraftItemAmount6;
    private TextBox t_CraftItemID6;
    private Label label53;
    private Label label54;
    private TextBox t_CraftItemAmount5;
    private TextBox t_CraftItemID5;
    private Label label43;
    private Label label44;
    private TextBox t_CraftItemAmount4;
    private TextBox t_CraftItemID4;
    private Label label41;
    private Label label42;
    private TextBox t_CraftItemAmount3;
    private TextBox t_CraftItemID3;
    private Label label39;
    private Label label40;
    private TextBox t_CraftItemAmount2;
    private TextBox t_CraftItemID2;
    private Label label37;
    private Label label38;
    private TextBox t_CraftItemAmount1;
    private TextBox t_CraftItemID1;
    private Label label35;
    private Label label36;
    private Button t_CraftItemSearch9;
    private Button t_CraftItemSearch8;
    private Button t_CraftItemSearch7;
    private Button t_CraftItemSearch6;
    private Button t_CraftItemSearch5;
    private Button t_CraftItemSearch4;
    private Button t_CraftItemSearch3;
    private Button t_CraftItemSearch2;
    private Button t_CraftItemSearch1;
    private GroupBox groupBox9;
    private TextBox t_CraftSkill2Level;
    private Label label27;
    private TextBox t_CraftSkill1Level;
    private Label label28;
    private TextBox t_CraftSkill2ID;
    private Label label23;
    private TextBox t_CraftSkill1ID;
    private Label label26;
    private TabPage tabPage5;
    private GroupBox groupBox12;
    private Button btnRareSearch9;
    private TextBox tbRareOpt9;
    private TextBox tbRareChance9;
    private Label label66;
    private Label label67;
    private Button btnRareSearch8;
    private TextBox tbRareOpt8;
    private TextBox tbRareChance8;
    private Label label68;
    private Label label69;
    private Button btnRareSearch7;
    private TextBox tbRareOpt7;
    private TextBox tbRareChance7;
    private Label label70;
    private Label label71;
    private Button btnRareSearch6;
    private TextBox tbRareOpt6;
    private TextBox tbRareChance6;
    private Label label72;
    private Label label73;
    private Button btnRareSearch5;
    private TextBox tbRareOpt5;
    private TextBox tbRareChance5;
    private Label label74;
    private Label label75;
    private Button btnRareSearch4;
    private TextBox tbRareOpt4;
    private TextBox tbRareChance4;
    private Label label64;
    private Label label65;
    private Button btnRareSearch3;
    private TextBox tbRareOpt3;
    private TextBox tbRareChance3;
    private Label label62;
    private Label label63;
    private Button btnRareSearch2;
    private TextBox tbRareOpt2;
    private TextBox tbRareChance2;
    private Label label60;
    private Label label61;
    private Button btnRareSearch1;
    private TextBox tbRareOpt1;
    private TextBox tbRareChance1;
    private Label label58;
    private Label label59;
    private Button btnRareSearch0;
    private TextBox tbRareOpt0;
    private TextBox tbRareChance0;
    private Label label57;
    private Label label56;
    private Panel panel3;
    private Button btnRareDbPut;
    private Button btnRareDbGet;
    private TabPage tabPage6;
    private TextBox textBox6;
    private TextBox textBox5;
    private TextBox textBox4;
    private TextBox textBox3;
    private TextBox textBox2;
    private TextBox textBox1;
    private Button btnSearchSkill3;
    private Button btnSearchSkill2;
    private Button btnSearchSkill1;
    private TextBox tbCB1;
    private TextBox tbCB2;
    private Label label89;
    private Label label86;
    private Label label87;
    private Label label88;
    private Label label85;
    private Label label84;
    private Label label83;
    private Label lblCurDataPurple;
    private Button btnPurplePut;
    private Button btnPurpleGet;
    private Label label81;
    private Label label82;
    private TextBox tbSkillLevel3;
    private TextBox tbSkillID3;
    private Label label79;
    private Label label80;
    private TextBox tbSkillLevel2;
    private TextBox tbSkillID2;
    private Label label78;
    private Label label77;
    private TextBox tbSkillLevel1;
    private TextBox tbSkillID1;
    private TextBox tbSealID6;
    private ComboBox cbSealLevel6;
    private TextBox tbSealLevel6;
    private ComboBox cbSealID6;
    private TextBox tbSealID5;
    private ComboBox cbSealLevel5;
    private TextBox tbSealLevel5;
    private ComboBox cbSealID5;
    private TextBox tbSealID4;
    private ComboBox cbSealLevel4;
    private TextBox tbSealLevel4;
    private ComboBox cbSealID4;
    private TextBox tbSealID3;
    private ComboBox cbSealLevel3;
    private TextBox tbSealLevel3;
    private ComboBox cbSealID3;
    private TextBox tbSealID2;
    private ComboBox cbSealLevel2;
    private TextBox tbSealLevel2;
    private ComboBox cbSealID2;
    private TextBox tbSealID1;
    private ComboBox cbSealLevel1;
    private TextBox tbSealLevel1;
    private ComboBox cbSealID1;
    private PictureBox pbSkill3Icon;
    private PictureBox pbSkill2Icon;
    private PictureBox pbSkill1Icon;
    private Panel ModPanel;
    private CheckBox chkDbUpdate;
    private PictureBox pictureBox1;
    private Label label29;
    private Button t_DiscardChanges;
    private Button t_SaveRecord;
    private Label label1;
    private TextBox SearchText;
    private StatusStrip statusStrip1;
    private ToolStripStatusLabel status;
    private Button button4;
    private Button button3;
    private GroupBox groupBox16;
    private ComboBox comboBox26;
    private ComboBox comboBox25;
    private ComboBox comboBox24;
    private Label label92;
    private TextBox t_rvr_Grade;
    private Label label91;
    private TextBox t_rvr_Value;
    private GroupBox groupBox23;
    private Label label12;
    private TextBox t_quest_tigger;
    private Label label13;
    private TextBox t_quest_tigger_count;
    private GroupBox groupBox13;
    private Button btnPercent2Add;
    private Button btnPercent1Add;
    private Button btnPercentAdd;
    private TextBox TbPercent2;
    private TextBox TbPercent1;
    private TextBox TbPercent;
    private Label label108;
    private Label label107;
    private Label label106;
    private TextBox t_Num4;
    private Label label90;
    private TextBox t_Num0;
    private Label label93;
    private Label label94;
    private TextBox t_Num1;
    private TextBox t_Num3;
    private Label label95;
    private Label label96;
    private TextBox t_Num2;
    private TextBox t_Level2;
    private Label label14;
    private Label label15;
    private TextBox textBox7;
    private GroupBox groupBox6;
    private GroupBox groupBox14;
    private ListBox ItemListBox;
    private Button t_DeleteItem;
    private Button t_CopyToNew;
    private Button t_NewItem;
    private Timer timer1;
    private Panel panel2;
    private CheckBox checkBox_class8;
    private CheckBox checkBox_class7;
    private CheckBox checkBox_class6;
    private CheckBox checkBox_class5;
    private CheckBox checkBox_class4;
    private CheckBox checkBox_class3;
    private CheckBox checkBox_class2;
    private CheckBox checkBox_class1;
    private CheckBox checkBox_class0;
    private TextBox tb_castleWar;
    private Label label16;

    public ItemAll() => this.InitializeComponent();

    private void InitializeDevice()
    {
      this.mD3d = new Direct3D();
      this.device = new Device(this.mD3d, 0, DeviceType.Hardware, this.Handle, CreateFlags.SoftwareVertexProcessing, new PresentParameters[1]
      {
        new PresentParameters()
        {
          SwapEffect = SwapEffect.Discard,
          DeviceWindowHandle = this.panel3DView.Handle,
          Windowed = true,
          BackBufferWidth = this.panel3DView.Width,
          BackBufferHeight = this.panel3DView.Height,
          BackBufferFormat = SlimDX.Direct3D9.Format.A8R8G8B8
        }
      });
      this.device.SetRenderState<Cull>(RenderState.CullMode, Cull.None);
      this.device.SetRenderState<FillMode>(RenderState.FillMode, FillMode.Solid);
      this.device.SetRenderState(RenderState.Lighting, false);
      this.CameraPositioning();
    }

    private void openToolStripMenuItem_Click(object sender, EventArgs e)
    {
      OpenFileDialog openFileDialog1 = new OpenFileDialog();
      openFileDialog1.Title = "Abrir itemAll.lod";
      openFileDialog1.InitialDirectory = this._ClientPath;
      openFileDialog1.Filter = "itemAll.lod|itemAll.lod|All|*.*";
      if (openFileDialog1.ShowDialog() == DialogResult.Cancel)
        return;
      OpenFileDialog openFileDialog2 = new OpenFileDialog();
      openFileDialog2.Title = "Abrir strItem_br.lod";
      openFileDialog2.InitialDirectory = "";
      openFileDialog2.Filter = "strItem_*.lod|strItem_*.lod|All|*.*";
      if (openFileDialog2.ShowDialog() != DialogResult.Cancel)
      {
        ItemAll.ItemList.Clear();
        this.ItemListBox.Items.Clear();
        this.ReadItem(openFileDialog1.FileName);
        ItemAll.OpenedFile = openFileDialog1.FileName;
        this.ReadItemName(openFileDialog2.FileName);
        this.makelist();
        this.tabControl2.Enabled = true;
      }
    }

    private void ReadItem(string itemsource)
    {
      using (BinaryReader binaryReader = new BinaryReader((Stream) File.Open(itemsource, FileMode.Open)))
      {
        binaryReader.ReadInt32();
        while (binaryReader.BaseStream.Position < binaryReader.BaseStream.Length)
        {
          if (binaryReader.BaseStream.Length - 25L > binaryReader.BaseStream.Position)
          {
            ItemContainer itemContainer = new ItemContainer();
            itemContainer.ItemID = binaryReader.ReadInt32();
            itemContainer.JobFlag = binaryReader.ReadInt32();
            itemContainer.Weight = binaryReader.ReadInt32();
            itemContainer.MaxUse = binaryReader.ReadInt32();
            itemContainer.Level = binaryReader.ReadInt32();
            itemContainer.Flag = binaryReader.ReadInt64();
            itemContainer.Position = binaryReader.ReadInt32();
            itemContainer.Type = binaryReader.ReadInt32();
            itemContainer.SubType = binaryReader.ReadInt32();
            int[] numArray1 = new int[10];
            int[] numArray2 = new int[10];
            for (int index = 0; index < 10; ++index)
            {
              numArray1[index] = binaryReader.ReadInt32();
              numArray2[index] = binaryReader.ReadInt32();
            }
            itemContainer.CraftItemID = numArray1;
            itemContainer.CraftItemAmount = numArray2;
            itemContainer.Need_SSkill1_Id = binaryReader.ReadInt32();
            itemContainer.Need_SSkill1_Level = binaryReader.ReadInt32();
            itemContainer.Need_SSkill2_Id = binaryReader.ReadInt32();
            itemContainer.Need_SSkill2_Level = binaryReader.ReadInt32();
            itemContainer.TexID = binaryReader.ReadInt32();
            itemContainer.TexRow = binaryReader.ReadInt32();
            itemContainer.TexCol = binaryReader.ReadInt32();
            itemContainer.Num0 = binaryReader.ReadInt32();
            itemContainer.Num1 = binaryReader.ReadInt32();
            itemContainer.Num2 = binaryReader.ReadInt32();
            itemContainer.Num3 = binaryReader.ReadInt32();
            itemContainer.Price = binaryReader.ReadInt32();
            itemContainer.Set1 = binaryReader.ReadInt32();
            itemContainer.Set2 = binaryReader.ReadInt32();
            itemContainer.Set3 = binaryReader.ReadInt32();
            itemContainer.Set4 = binaryReader.ReadInt32();
            itemContainer.Set5 = binaryReader.ReadInt32();
            itemContainer.Smc = Encoding.GetEncoding("ISO-8859-1").GetString(binaryReader.ReadBytes(64));
            itemContainer.Effect1 = Encoding.GetEncoding("ISO-8859-1").GetString(binaryReader.ReadBytes(32));
            itemContainer.Effect2 = Encoding.GetEncoding("ISO-8859-1").GetString(binaryReader.ReadBytes(32));
            itemContainer.Effect3 = Encoding.GetEncoding("ISO-8859-1").GetString(binaryReader.ReadBytes(32));
            itemContainer.JewelOptionType = binaryReader.ReadInt32();
            itemContainer.JewelOptionLevel = binaryReader.ReadInt32();
            int[] numArray3 = new int[10];
            int[] numArray4 = new int[10];
            for (int index = 0; index < 10; ++index)
              numArray3[index] = binaryReader.ReadInt32();
            for (int index = 0; index < 10; ++index)
              numArray4[index] = binaryReader.ReadInt32();
            itemContainer.rareOptionType = numArray3;
            itemContainer.rareOptionChance = numArray4;
            itemContainer.syndicate_type = binaryReader.ReadInt32();
            itemContainer.syndicate_grade = binaryReader.ReadInt32();
            itemContainer.fortuneIndex = binaryReader.ReadInt32();
            itemContainer.castleWar = (int) binaryReader.ReadByte();
            ItemAll.ItemList.Add(itemContainer);
          }
          else
            binaryReader.BaseStream.Position = binaryReader.BaseStream.Length;
        }
      }
    }

    private void ReadItemName(string itemnamesource)
    {
      using (BinaryReader binaryReader = new BinaryReader((Stream) File.Open(itemnamesource, FileMode.Open)))
      {
        binaryReader.ReadInt32();
        binaryReader.ReadInt32();
        while (binaryReader.BaseStream.Position < binaryReader.BaseStream.Length)
        {
          int ID = binaryReader.ReadInt32();
          int index = ItemAll.ItemList.FindIndex((Predicate<ItemContainer>) (p => p.ItemID.Equals(ID)));
          string str1 = Encoding.GetEncoding("ISO-8859-1").GetString(binaryReader.ReadBytes(binaryReader.ReadInt32()));
          string str2 = Encoding.GetEncoding("ISO-8859-1").GetString(binaryReader.ReadBytes(binaryReader.ReadInt32()));
          if (index != -1)
          {
            ItemAll.ItemList[index].Name = str1;
            ItemAll.ItemList[index].Description = str2;
          }
        }
        binaryReader.Close();
        binaryReader.Dispose();
      }
    }

    private void makelist()
    {
      ItemAll.ItemList.OrderBy<ItemContainer, int>((Func<ItemContainer, int>) (x => x.ItemID));
      List<ItemContainer> list = ItemAll.ItemList.OrderBy<ItemContainer, int>((Func<ItemContainer, int>) (o => o.ItemID)).ToList<ItemContainer>();
      int num = list.Count<ItemContainer>();
      for (int index = 0; index < num; ++index)
      {
        int itemId = list[index].ItemID;
        string name = list[index].Name;
        string str = list[index].Level.ToString();
        this.ItemListBox.Items.Add((object) (itemId.ToString() + " - " + name + " (Lv " + str + ")"));
      }
      this.status.Text = "Found " + ItemAll.ItemList.Count.ToString() + " items";
    }

    private void ItemListBox_SelectedIndexChanged(object sender, EventArgs e) => this.ViewItem();

    private void textBox7_TextChanged(object sender, EventArgs e) => this.makelist();

    public int GetIDFromList()
    {
      int idFromList;
      try
      {
        idFromList = Convert.ToInt32(this.ItemListBox.Text.Split(' ')[0]);
      }
      catch
      {
        idFromList = 2;
      }
      return idFromList;
    }

    public void ViewItem()
    {
      this.CaptureChanges = false;
      int ID = this.GetIDFromList();
      int index = ItemAll.ItemList.FindIndex((Predicate<ItemContainer>) (p => p.ItemID.Equals(ID)));
      if (index == -1)
      {
        new CustomMessage("Cannot find ItemID " + ID.ToString()).Show();
      }
      else
      {
        this.t_ItemID.Text = ItemAll.ItemList[index].ItemID.ToString();
        this.t_ItemName.Text = ItemAll.ItemList[index].Name;
        this.t_Description.Text = ItemAll.ItemList[index].Description;
        this.t_SMC.Text = ItemAll.ItemList[index].Smc;
        this.t_IconID.Text = ItemAll.ItemList[index].TexID.ToString();
        this.t_IconRow.Text = ItemAll.ItemList[index].TexRow.ToString();
        this.t_IconColumn.Text = ItemAll.ItemList[index].TexCol.ToString();
        this.t_EffectNormal.Text = ItemAll.ItemList[index].Effect1;
        this.t_EffectAttack.Text = ItemAll.ItemList[index].Effect2;
        this.t_EffectDamage.Text = ItemAll.ItemList[index].Effect3;
        this.t_Num0.Text = ItemAll.ItemList[index].Num0.ToString();
        this.t_Num1.Text = ItemAll.ItemList[index].Num1.ToString();
        this.t_Num2.Text = ItemAll.ItemList[index].Num2.ToString();
        this.t_Num3.Text = ItemAll.ItemList[index].Num3.ToString();
        this.t_Level.Text = ItemAll.ItemList[index].Level.ToString();
        this.t_Weight.Text = ItemAll.ItemList[index].Weight.ToString();
        this.t_Price.Text = ItemAll.ItemList[index].Price.ToString();
        this.t_Set1.Text = ItemAll.ItemList[index].Set1.ToString();
        this.t_Set2.Text = ItemAll.ItemList[index].Set2.ToString();
        this.t_Set3.Text = ItemAll.ItemList[index].Set3.ToString();
        this.t_Set4.Text = ItemAll.ItemList[index].Set4.ToString();
        this.t_Set5.Text = ItemAll.ItemList[index].Set5.ToString();
        this.t_Type.Text = ItemAll.ItemList[index].Type.ToString();
        this.t_SubType.Text = ItemAll.ItemList[index].SubType.ToString();
        this.t_Class.Text = ItemAll.ItemList[index].JobFlag.ToString();
        this.t_WearingPos.Text = ItemAll.ItemList[index].Position.ToString();
        this.t_Flag.Text = ItemAll.ItemList[index].Flag.ToString();
        this.t_maxuse.Text = ItemAll.ItemList[index].MaxUse.ToString();
        this.t_RareOptionID.Text = ItemAll.ItemList[index].RareOption.ToString();
        this.t_RareOptionRate.Text = ItemAll.ItemList[index].RareChance.ToString();
        this.t_CraftSkill1ID.Text = ItemAll.ItemList[index].Need_SSkill1_Id.ToString();
        this.t_CraftSkill1Level.Text = ItemAll.ItemList[index].Need_SSkill1_Level.ToString();
        this.t_CraftSkill2ID.Text = ItemAll.ItemList[index].Need_SSkill2_Id.ToString();
        this.t_CraftSkill2Level.Text = ItemAll.ItemList[index].Need_SSkill2_Level.ToString();
        this.t_CraftItemID1.Text = ItemAll.ItemList[index].CraftItemID[0].ToString();
        this.t_CraftItemAmount1.Text = ItemAll.ItemList[index].CraftItemAmount[0].ToString();
        this.t_CraftItemID2.Text = ItemAll.ItemList[index].CraftItemID[1].ToString();
        this.t_CraftItemAmount2.Text = ItemAll.ItemList[index].CraftItemAmount[1].ToString();
        this.t_CraftItemID3.Text = ItemAll.ItemList[index].CraftItemID[2].ToString();
        this.t_CraftItemAmount3.Text = ItemAll.ItemList[index].CraftItemAmount[2].ToString();
        this.t_CraftItemID4.Text = ItemAll.ItemList[index].CraftItemID[3].ToString();
        this.t_CraftItemAmount4.Text = ItemAll.ItemList[index].CraftItemAmount[3].ToString();
        this.t_CraftItemID5.Text = ItemAll.ItemList[index].CraftItemID[4].ToString();
        this.t_CraftItemAmount5.Text = ItemAll.ItemList[index].CraftItemAmount[4].ToString();
        this.t_CraftItemID6.Text = ItemAll.ItemList[index].CraftItemID[5].ToString();
        this.t_CraftItemAmount6.Text = ItemAll.ItemList[index].CraftItemAmount[5].ToString();
        this.t_CraftItemID7.Text = ItemAll.ItemList[index].CraftItemID[6].ToString();
        this.t_CraftItemAmount7.Text = ItemAll.ItemList[index].CraftItemAmount[6].ToString();
        this.t_CraftItemID8.Text = ItemAll.ItemList[index].CraftItemID[7].ToString();
        this.t_CraftItemAmount8.Text = ItemAll.ItemList[index].CraftItemAmount[7].ToString();
        this.t_CraftItemID9.Text = ItemAll.ItemList[index].CraftItemID[8].ToString();
        this.t_CraftItemAmount9.Text = ItemAll.ItemList[index].CraftItemAmount[8].ToString();
        this.t_CraftItemID10.Text = ItemAll.ItemList[index].CraftItemID[9].ToString();
        this.t_CraftItemAmount10.Text = ItemAll.ItemList[index].CraftItemAmount[9].ToString();
        this.BuildCraftGrid();
        this.CaptureChanges = true;
        string str = Path.GetDirectoryName(ItemAll.OpenedFile).Replace("Data", "").Replace("data", "");
        if (!this.chk3D.Checked || !File.Exists(str + this.t_SMC.Text))
          return;
        this.models = new List<tMesh>();
        switch (ItemAll.ItemList[index].JobFlag)
        {
          case 1:
            this.MakeLCModels(str + "Data\\Character\\Titan\\ti.smc");
            break;
          case 2:
            this.MakeLCModels(str + "Data\\Character\\Knight\\ni.smc");
            break;
          case 4:
            this.MakeLCModels(str + "Data\\Character\\Healer\\hw.smc");
            break;
          case 8:
            this.MakeLCModels(str + "Data\\Character\\Mage\\ma.smc");
            break;
          case 16:
            this.MakeLCModels(str + "Data\\Character\\Rogue\\ro.smc");
            break;
          case 32:
            this.MakeLCModels(str + "Data\\Character\\Sorcerer\\so.smc");
            break;
          case 64:
            this.MakeLCModels(str + "Data\\Character\\NightShadow\\ns.smc");
            break;
          case 128:
            this.MakeLCModels(str + "Data\\Character\\Rogue\\ro.smc");
            break;
          case 144:
            this.MakeLCModels(str + "Data\\Character\\Rogue\\ro.smc");
            break;
          case 256:
            this.MakeLCModels(str + "Data\\Character\\Mage\\ma.smc");
            break;
          case 264:
            this.MakeLCModels(str + "Data\\Character\\Mage\\ma.smc");
            break;
        }
        this.MakeLCModels(str + this.t_SMC.Text);
      }
    }

    private void MakeLCModels(string SMCFile)
    {
      int num = -1;
      int ID = this.GetIDFromList();
      int index1 = ItemAll.ItemList.FindIndex((Predicate<ItemContainer>) (p => p.ItemID.Equals(ID)));
      if (index1 != -1)
      {
        int jobFlag = ItemAll.ItemList[index1].JobFlag;
        num = ItemAll.ItemList[index1].Position;
      }
      try
      {
        List<smcMesh> source1 = SMCReader.ReadFile(SMCFile);
        for (int index2 = 0; index2 < source1.Count<smcMesh>(); ++index2)
        {
          if ((num != 0 || !source1[index2].FileName.Contains("_hair_000")) && (num != 1 || !source1[index2].FileName.Contains("_bu_000")) && (num != 3 || !source1[index2].FileName.Contains("_bd_000")) && (num != 5 || !source1[index2].FileName.Contains("_hn_000")) && (num != 6 || !source1[index2].FileName.Contains("_ft_000")) && LCMeshReader.ReadFile(source1[index2].FileName))
          {
            tMeshContainer pMesh = LCMeshReader.pMesh;
            for (int index3 = 0; index3 < ((IEnumerable<tMeshObject>) pMesh.Objects).Count<tMeshObject>(); ++index3)
            {
              int toVert = (int) pMesh.Objects[index3].ToVert;
              uint faceCount = pMesh.Objects[index3].FaceCount;
              short[] faces = pMesh.Objects[index3].GetFaces();
              CustomVertex.PositionNormalTextured[] positionNormalTexturedArray = new CustomVertex.PositionNormalTextured[toVert];
              int fromVert = (int) pMesh.Objects[index3].FromVert;
              for (int index4 = 0; (long) index4 < (long) pMesh.Objects[index3].ToVert; ++index4)
              {
                positionNormalTexturedArray[index4].Position = new Vector3(pMesh.Vertices[fromVert].X, pMesh.Vertices[fromVert].Y, pMesh.Vertices[fromVert].Z);
                positionNormalTexturedArray[index4].Normal = new Vector3(pMesh.Normals[fromVert].X, pMesh.Normals[fromVert].Y, pMesh.Normals[fromVert].Z);
                try
                {
                  positionNormalTexturedArray[index4].Texture = new Vector2(pMesh.UVMaps[0].Coords[fromVert].U, pMesh.UVMaps[0].Coords[fromVert].V);
                }
                catch
                {
                  positionNormalTexturedArray[index4].Texture = new Vector2(0.0f, 0.0f);
                }
                ++fromVert;
              }
              VertexBuffer vertexBuffer = new VertexBuffer(this.device, ((IEnumerable<CustomVertex.PositionNormalTextured>) positionNormalTexturedArray).Count<CustomVertex.PositionNormalTextured>() * 32, Usage.None, VertexFormat.PositionNormal | VertexFormat.Texture1, Pool.Default);
              Mesh mesh = new Mesh(this.device, ((IEnumerable<short>) faces).Count<short>() / 3, ((IEnumerable<CustomVertex.PositionNormalTextured>) positionNormalTexturedArray).Count<CustomVertex.PositionNormalTextured>(), MeshFlags.Managed, VertexFormat.PositionNormal | VertexFormat.Texture1);
              DataStream dataStream1;
              DataStream dataStream2 = dataStream1 = mesh.VertexBuffer.Lock(0, ((IEnumerable<CustomVertex.PositionNormalTextured>) positionNormalTexturedArray).Count<CustomVertex.PositionNormalTextured>() * 32, LockFlags.None);
              try
              {
                dataStream2.WriteRange<CustomVertex.PositionNormalTextured>(positionNormalTexturedArray);
                mesh.VertexBuffer.Unlock();
              }
              finally
              {
                dataStream1?.Dispose();
              }
              DataStream dataStream3;
              DataStream dataStream4 = dataStream3 = mesh.IndexBuffer.Lock(0, ((IEnumerable<short>) faces).Count<short>() * 2, LockFlags.None);
              try
              {
                dataStream4.WriteRange<short>(faces);
                mesh.IndexBuffer.Unlock();
              }
              finally
              {
                dataStream3?.Dispose();
              }
              if (((IEnumerable<tMeshJointWeights>) pMesh.Weights).Count<tMeshJointWeights>() != 0)
              {
                string[] strArray = new string[((IEnumerable<tMeshJointWeights>) pMesh.Weights).Count<tMeshJointWeights>()];
                List<int>[] source2 = new List<int>[((IEnumerable<tMeshJointWeights>) pMesh.Weights).Count<tMeshJointWeights>()];
                List<float>[] floatListArray = new List<float>[((IEnumerable<tMeshJointWeights>) pMesh.Weights).Count<tMeshJointWeights>()];
                for (int index5 = 0; index5 < ((IEnumerable<tMeshJointWeights>) pMesh.Weights).Count<tMeshJointWeights>(); ++index5)
                {
                  strArray[index5] = this.Enc.GetString(pMesh.Weights[index5].JointName);
                  source2[index5] = new List<int>();
                  floatListArray[index5] = new List<float>();
                  for (int index6 = 0; index6 < ((IEnumerable<tMeshWeightsMap>) pMesh.Weights[index5].WeightsMap).Count<tMeshWeightsMap>(); ++index6)
                  {
                    source2[index5].Add(pMesh.Weights[index5].WeightsMap[index6].Index);
                    floatListArray[index5].Add(pMesh.Weights[index5].WeightsMap[index6].Weight);
                  }
                }
                mesh.SkinInfo = new SkinInfo(((IEnumerable<CustomVertex.PositionNormalTextured>) positionNormalTexturedArray).Count<CustomVertex.PositionNormalTextured>(), VertexFormat.PositionNormal | VertexFormat.Texture1, (int) pMesh.HeaderInfo.JointCount);
                for (int bone = 0; bone < ((IEnumerable<List<int>>) source2).Count<List<int>>(); ++bone)
                {
                  mesh.SkinInfo.SetBoneName(bone, strArray[bone]);
                  mesh.SkinInfo.SetBoneInfluence(bone, source2[bone].ToArray(), floatListArray[bone].ToArray());
                }
              }
              mesh.GenerateAdjacency(0.5f);
              mesh.ComputeNormals();
              Texture texture = (Texture) null;
              string objName = this.Enc.GetString(pMesh.Objects[index3].Textures[0].InternalName);
              int index7 = source1[index2].Object.FindIndex((Predicate<smcObject>) (x => x.Name.Equals(objName)));
              if (index7 != -1)
                texture = this.GetTextureFromFile(source1[index2].Object[index7].Texture);
              this.models.Add(new tMesh(mesh, texture));
            }
          }
        }
      }
      catch
      {
      }
      this.zoom = 4f;
    }

    private Texture GetTextureFromFile(string FileName)
    {
      Texture textureFromFile = (Texture) null;
      if (File.Exists(FileName))
      {
        Tex.ReadFile(FileName);
        SlimDX.Direct3D9.Format imageFormat = this.ConvFormat(Tex.GetFormat());
        textureFromFile = this.BuildTexture(Tex.lcTex.imageData[0], imageFormat, (int) Tex.lcTex.Header.Width, (int) Tex.lcTex.Header.Height);
      }
      return textureFromFile;
    }

    private Texture BuildTexture(byte[] imageData, SlimDX.Direct3D9.Format imageFormat, int width, int height)
    {
      switch (imageFormat)
      {
        case SlimDX.Direct3D9.Format.R8G8B8:
          MemoryStream memoryStream1;
          MemoryStream memoryStream2 = memoryStream1 = new MemoryStream();
          try
          {
            Tex.makeRGB8(imageData, width, height).Save((Stream) memoryStream2, ImageFormat.Bmp);
            memoryStream2.Write(imageData, 0, imageData.Length);
            memoryStream2.Position = 0L;
            return Texture.FromStream(this.device, (Stream) memoryStream2, width, height, 0, Usage.SoftwareProcessing, SlimDX.Direct3D9.Format.A8B8G8R8, Pool.Default, SlimDX.Direct3D9.Filter.None, SlimDX.Direct3D9.Filter.None, 0);
          }
          finally
          {
            memoryStream1?.Dispose();
          }
        case SlimDX.Direct3D9.Format.A8R8G8B8:
          MemoryStream memoryStream3;
          MemoryStream memoryStream4 = memoryStream3 = new MemoryStream();
          try
          {
            Tex.makeRGB(imageData, width, height).Save((Stream) memoryStream4, ImageFormat.Bmp);
            memoryStream4.Write(imageData, 0, imageData.Length);
            memoryStream4.Position = 0L;
            return Texture.FromStream(this.device, (Stream) memoryStream4, width, height, 0, Usage.SoftwareProcessing, SlimDX.Direct3D9.Format.A8B8G8R8, Pool.Default, SlimDX.Direct3D9.Filter.None, SlimDX.Direct3D9.Filter.None, 0);
          }
          finally
          {
            memoryStream3?.Dispose();
          }
        default:
          Texture texture = new Texture(this.device, width, height, 0, Usage.None, imageFormat, Pool.Managed);
          using (Stream data = (Stream) texture.LockRectangle(0, LockFlags.None).Data)
          {
            data.Write(imageData, 0, ((IEnumerable<byte>) imageData).Count<byte>());
            texture.UnlockRectangle(0);
          }
          return texture;
      }
    }

    private SlimDX.Direct3D9.Format ConvFormat(texFormat tFormat)
    {
      SlimDX.Direct3D9.Format format = SlimDX.Direct3D9.Format.Unknown;
      switch (tFormat)
      {
        case texFormat.RGB:
          return SlimDX.Direct3D9.Format.R8G8B8;
        case texFormat.ARGB:
          return SlimDX.Direct3D9.Format.A8R8G8B8;
        case texFormat.DXT1:
          return SlimDX.Direct3D9.Format.Dxt1;
        case texFormat.DXT3:
          return SlimDX.Direct3D9.Format.Dxt3;
        default:
          return format;
      }
    }

    public void BuildCraftGrid()
    {
      this.CraftGrid.Rows.Clear();
      if (Convert.ToInt32(this.t_CraftItemID1.Text) != -1)
        this.CraftGrid.Rows.Add((object) Items.Icon((object) this.t_CraftItemID1.Text), (object) this.t_CraftItemID1.Text, (object) Items.GetNameFromID((object) this.t_CraftItemID1.Text), (object) this.t_CraftItemAmount1.Text);
      if (Convert.ToInt32(this.t_CraftItemID2.Text) != -1)
        this.CraftGrid.Rows.Add((object) Items.Icon((object) this.t_CraftItemID2.Text), (object) this.t_CraftItemID2.Text, (object) Items.GetNameFromID((object) this.t_CraftItemID2.Text), (object) this.t_CraftItemAmount2.Text);
      if (Convert.ToInt32(this.t_CraftItemID3.Text) != -1)
        this.CraftGrid.Rows.Add((object) Items.Icon((object) this.t_CraftItemID3.Text), (object) this.t_CraftItemID3.Text, (object) Items.GetNameFromID((object) this.t_CraftItemID3.Text), (object) this.t_CraftItemAmount3.Text);
      if (Convert.ToInt32(this.t_CraftItemID4.Text) != -1)
        this.CraftGrid.Rows.Add((object) Items.Icon((object) this.t_CraftItemID4.Text), (object) this.t_CraftItemID4.Text, (object) Items.GetNameFromID((object) this.t_CraftItemID4.Text), (object) this.t_CraftItemAmount4.Text);
      if (Convert.ToInt32(this.t_CraftItemID5.Text) != -1)
        this.CraftGrid.Rows.Add((object) Items.Icon((object) this.t_CraftItemID5.Text), (object) this.t_CraftItemID5.Text, (object) Items.GetNameFromID((object) this.t_CraftItemID5.Text), (object) this.t_CraftItemAmount5.Text);
      if (Convert.ToInt32(this.t_CraftItemID6.Text) != -1)
        this.CraftGrid.Rows.Add((object) Items.Icon((object) this.t_CraftItemID6.Text), (object) this.t_CraftItemID6.Text, (object) Items.GetNameFromID((object) this.t_CraftItemID6.Text), (object) this.t_CraftItemAmount6.Text);
      if (Convert.ToInt32(this.t_CraftItemID7.Text) != -1)
        this.CraftGrid.Rows.Add((object) Items.Icon((object) this.t_CraftItemID7.Text), (object) this.t_CraftItemID7.Text, (object) Items.GetNameFromID((object) this.t_CraftItemID7.Text), (object) this.t_CraftItemAmount7.Text);
      if (Convert.ToInt32(this.t_CraftItemID8.Text) != -1)
        this.CraftGrid.Rows.Add((object) Items.Icon((object) this.t_CraftItemID8.Text), (object) this.t_CraftItemID8.Text, (object) Items.GetNameFromID((object) this.t_CraftItemID8.Text), (object) this.t_CraftItemAmount8.Text);
      if (Convert.ToInt32(this.t_CraftItemID9.Text) != -1)
        this.CraftGrid.Rows.Add((object) Items.Icon((object) this.t_CraftItemID9.Text), (object) this.t_CraftItemID9.Text, (object) Items.GetNameFromID((object) this.t_CraftItemID9.Text), (object) this.t_CraftItemAmount9.Text);
      if (Convert.ToInt32(this.t_CraftItemID10.Text) == -1)
        return;
      this.CraftGrid.Rows.Add((object) Items.Icon((object) this.t_CraftItemID10.Text), (object) this.t_CraftItemID10.Text, (object) Items.GetNameFromID((object) this.t_CraftItemID10.Text), (object) this.t_CraftItemAmount10.Text);
    }

    private void chk3D_CheckedChanged(object sender, EventArgs e)
    {
      if (this.chk3D.Checked)
        this.panel3DView.Visible = true;
      else
        this.panel3DView.Visible = false;
    }

    private void CameraPositioning()
    {
      this.device.SetTransform(TransformState.Projection, Matrix.PerspectiveFovLH(100f, 1f, 1f, 450f));
      this.device.SetTransform(TransformState.View, Matrix.LookAtLH(new Vector3(0.0f, 0.0f, -5f), new Vector3(0.0f, 0.0f, 0.0f), new Vector3(0.0f, 1f, 0.0f)));
      this.device.SetTransform(TransformState.World, Matrix.RotationYawPitchRoll(0.0f, 0.0f, 0.0f));
    }

    private void ItemAll_Load(object sender, EventArgs e) => this.InitializeDevice();

    private void Render()
    {
      this.device.Viewport = new Viewport(0, 0, this.panel3DView.Width, this.panel3DView.Height);
      this.device.Clear(ClearFlags.ZBuffer | ClearFlags.Target, new Color4(Color.FromKnownColor(KnownColor.Control)), 1f, 0);
      this.device.BeginScene();
      this.device.SetTransform(TransformState.View, Matrix.LookAtLH(new Vector3(0.0f, 0.0f, this.zoom), new Vector3(this.leftright, this.updown, 0.0f), new Vector3(0.0f, 1f, 0.0f)));
      this.device.SetTransform(TransformState.World, Matrix.RotationYawPitchRoll(this.rotation, 3.1f, 0.0f));
      if (this.models != null && this.models.Count<tMesh>() != 0)
      {
        for (int index = 0; index < this.models.Count<tMesh>(); ++index)
        {
          if (this.models[index].TexData != null)
            this.device.SetTexture(0, (BaseTexture) this.models[index].TexData);
          for (int subset = 0; subset < 1000; ++subset)
            this.models[index].MeshData.DrawSubset(subset);
        }
      }
      this.device.EndScene();
      this.device.Present();
      this.rotation -= 0.03f;
    }

    private void timer1_Tick(object sender, EventArgs e)
    {
      this.Render();
      Application.DoEvents();
    }

    private void ValueChanged(object sender, EventArgs e)
    {
      if (!this.CaptureChanges)
        return;
      if (sender is TextBox)
        (sender as TextBox).BackColor = Color.FromArgb(224, (int) byte.MaxValue, 168);
      if (sender is ComboBox)
        (sender as ComboBox).BackColor = Color.FromArgb(224, (int) byte.MaxValue, 168);
      if (sender is DataGrid)
        (sender as DataGrid).BackColor = Color.FromArgb(224, (int) byte.MaxValue, 168);
      this.ModPanel.Visible = true;
      this.menuStrip1.Enabled = false;
    }

    private void slideZoom_Scroll(object sender, EventArgs e)
    {
      this.zoom = (float) this.slideZoom.Value / 100f;
    }

    private void slideUpDown_Scroll(object sender, EventArgs e)
    {
      this.updown = (float) this.slideUpDown.Value / 1000f;
    }

    private void slideLeftRight_Scroll(object sender, EventArgs e)
    {
      this.leftright = (float) this.slideLeftRight.Value / 1000f;
    }

    private void button2_Click(object sender, EventArgs e)
    {
      string str = Path.GetDirectoryName(ItemAll.OpenedFile).Replace("Data", "").Replace("data", "") + this.t_SMC.Text;
      if (File.Exists(str))
        new TextEditor(str).Show();
      else
        new CustomMessage("File not found").Show();
    }

    public void ShowItemIcon()
    {
      try
      {
        this.t_Icon.Image = (Image) Items.Icon(Convert.ToInt32(this.t_IconID.Text), Convert.ToInt32(this.t_IconRow.Text), Convert.ToInt32(this.t_IconColumn.Text));
      }
      catch
      {
      }
    }

    private void t_IconID_TextChanged(object sender, EventArgs e)
    {
      this.ShowItemIcon();
      this.ValueChanged(sender, e);
    }

    private void t_IconRow_TextChanged(object sender, EventArgs e)
    {
      this.ShowItemIcon();
      this.ValueChanged(sender, e);
    }

    private void t_IconColumn_TextChanged(object sender, EventArgs e)
    {
      this.ShowItemIcon();
      this.ValueChanged(sender, e);
    }

    private void t_Type_TextChanged(object sender, EventArgs e)
    {
      this.SetTypeCombo();
      this.SetSubTypeCombo();
      this.ValueChanged(sender, e);
    }

    public void SetTypeCombo()
    {
      int result = -1;
      int.TryParse(this.t_Type.Text, out result);
      if (result > -1 && result < 7)
        this.t_TypeCombo.SelectedIndex = result;
      else
        this.t_TypeCombo.Text = "Unknown Type";
    }

    public void SetSubTypeCombo()
    {
      int result1 = -1;
      int.TryParse(this.t_Type.Text, out result1);
      int result2 = -1;
      int.TryParse(this.t_SubType.Text, out result2);
      if (result1 > -1 && result1 < 7)
      {
        if (result2 == -1)
        {
          this.t_SubTypeCombo.Text = "Unknown Subtype";
        }
        else
        {
          try
          {
            this.t_SubTypeCombo.SelectedIndex = result2;
          }
          catch
          {
            this.t_SubTypeCombo.Text = "Unknown Subtype";
          }
        }
      }
      else
        this.t_SubTypeCombo.Text = "Unknown Subtype";
    }

    private void t_SubType_TextChanged(object sender, EventArgs e)
    {
      this.SetSubTypeCombo();
      this.ValueChanged(sender, e);
    }

    private void t_Class_TextChanged(object sender, EventArgs e)
    {
      int result = (int) sbyte.MaxValue;
      int.TryParse(this.t_Class.Text, out result);
      for (int index = 0; index < 9; ++index)
        (this.Controls.Find("checkBox_class" + index.ToString(), true)[0] as CheckBox).Checked = Convert.ToBoolean(result & 1 << index);
      this.ValueChanged(sender, e);
    }

    private void t_TypeCombo_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.t_SubTypeCombo.Items.Clear();
      this.t_SubTypeCombo.Items.AddRange((object[]) Items.SubTypes(this.t_TypeCombo.SelectedIndex));
      if (Convert.ToInt32(this.t_Type.Text) != this.t_TypeCombo.SelectedIndex)
        this.t_Type.Text = this.t_TypeCombo.SelectedIndex.ToString();
      this.ValueChanged(sender, e);
    }

    private void t_SubTypeCombo_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (Convert.ToInt32(this.t_SubType.Text) != this.t_SubTypeCombo.SelectedIndex)
        this.t_SubType.Text = this.t_SubTypeCombo.SelectedIndex.ToString();
      this.ValueChanged(sender, e);
    }

    private void checkBox_class_CheckedChanged(object sender, EventArgs e)
    {
      int num = 0;
      for (int index = 0; index < 9; ++index)
      {
        if ((this.Controls.Find("checkBox_class" + index.ToString(), true)[0] as CheckBox).Checked)
          num += 1 << index;
      }
      this.t_Class.Text = num.ToString();
    }

    private void t_WearingPos_TextChanged(object sender, EventArgs e)
    {
      int result = -1;
      int.TryParse(this.t_WearingPos.Text, out result);
      this.t_WearingPosCombo.SelectedIndex = result + 1;
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      this.components = (IContainer) new System.ComponentModel.Container();
      this.menuStrip1 = new MenuStrip();
      this.fileToolStripMenuItem = new ToolStripMenuItem();
      this.openToolStripMenuItem = new ToolStripMenuItem();
      this.toolStripSeparator1 = new ToolStripSeparator();
      this.saveToolStripMenuItem = new ToolStripMenuItem();
      this.saveasToolStripMenuItem = new ToolStripMenuItem();
      this.toolStripSeparator2 = new ToolStripSeparator();
      this.exitToolStripMenuItem1 = new ToolStripMenuItem();
      this.exportToolStripMenuItem = new ToolStripMenuItem();
      this.toolStripMenuItem1 = new ToolStripMenuItem();
      this.sQLToolStripMenuItem = new ToolStripMenuItem();
      this.xMLToolStripMenuItem = new ToolStripMenuItem();
      this.itemnameToolStripMenuItem = new ToolStripMenuItem();
      this.hTMLToolStripMenuItem = new ToolStripMenuItem();
      this.thisToolStripMenuItem = new ToolStripMenuItem();
      this.insertQueryToolStripMenuItem = new ToolStripMenuItem();
      this.updateQueryToolStripMenuItem = new ToolStripMenuItem();
      this.toolsToolStripMenuItem = new ToolStripMenuItem();
      this.iconViewerToolStripMenuItem = new ToolStripMenuItem();
      this.itemFlagBuilderToolStripMenuItem = new ToolStripMenuItem();
      this.mySQLConnectionToolStripMenuItem = new ToolStripMenuItem();
      this.uPDATEThisRecordToolStripMenuItem = new ToolStripMenuItem();
      this.iNSERTThisRecordToolStripMenuItem = new ToolStripMenuItem();
      this.configConnectionToolStripMenuItem = new ToolStripMenuItem();
      this.massActionToolStripMenuItem = new ToolStripMenuItem();
      this.iNSERTALLNotExistingToolStripMenuItem = new ToolStripMenuItem();
      this.uPDATEINSERTThisRecordToolStripMenuItem = new ToolStripMenuItem();
      this.gETALLFromDatabaseToolStripMenuItem = new ToolStripMenuItem();
      this.updateAllNamesToDBToolStripMenuItem = new ToolStripMenuItem();
      this.updateAllFlagsToDBToolStripMenuItem = new ToolStripMenuItem();
      this.updateAllPicsToDBToolStripMenuItem = new ToolStripMenuItem();
      this.extraToolStripMenuItem = new ToolStripMenuItem();
      this.updateAllNamesInDatabaseToolStripMenuItem = new ToolStripMenuItem();
      this.toolStripMenuItem2 = new ToolStripMenuItem();
      this.getRecordsFromOtherFileToolStripMenuItem = new ToolStripMenuItem();
      this.updateAllPricesInDatabaseToolStripMenuItem = new ToolStripMenuItem();
      this.getPhpItemlistToolStripMenuItem = new ToolStripMenuItem();
      this.removeAllIconsAbove9ToolStripMenuItem = new ToolStripMenuItem();
      this.removeAllIconsAbove14ToolStripMenuItem = new ToolStripMenuItem();
      this.getAllFlagsFromOtherFileToolStripMenuItem = new ToolStripMenuItem();
      this.getIconsFromOtherFileToolStripMenuItem = new ToolStripMenuItem();
      this.tabControl2 = new TabControl();
      this.tabPage3 = new TabPage();
      this.groupBox13 = new GroupBox();
      this.btnPercent2Add = new Button();
      this.btnPercent1Add = new Button();
      this.btnPercentAdd = new Button();
      this.TbPercent2 = new TextBox();
      this.TbPercent1 = new TextBox();
      this.TbPercent = new TextBox();
      this.label108 = new Label();
      this.label107 = new Label();
      this.label106 = new Label();
      this.t_Num4 = new TextBox();
      this.label90 = new Label();
      this.t_Num0 = new TextBox();
      this.label93 = new Label();
      this.label94 = new Label();
      this.t_Num1 = new TextBox();
      this.t_Num3 = new TextBox();
      this.label95 = new Label();
      this.label96 = new Label();
      this.t_Num2 = new TextBox();
      this.groupBox23 = new GroupBox();
      this.label12 = new Label();
      this.t_quest_tigger = new TextBox();
      this.label13 = new Label();
      this.t_quest_tigger_count = new TextBox();
      this.groupBox16 = new GroupBox();
      this.comboBox26 = new ComboBox();
      this.comboBox25 = new ComboBox();
      this.comboBox24 = new ComboBox();
      this.label92 = new Label();
      this.t_rvr_Grade = new TextBox();
      this.label91 = new Label();
      this.t_rvr_Value = new TextBox();
      this.groupBox2 = new GroupBox();
      this.button2 = new Button();
      this.t_SMC = new TextBox();
      this.label55 = new Label();
      this.t_Description = new TextBox();
      this.label4 = new Label();
      this.t_ItemName = new TextBox();
      this.label3 = new Label();
      this.t_ItemID = new TextBox();
      this.label2 = new Label();
      this.groupBox3 = new GroupBox();
      this.t_Icon = new PictureBox();
      this.t_iconpick = new LinkLabel();
      this.t_IconColumn = new TextBox();
      this.label7 = new Label();
      this.t_IconRow = new TextBox();
      this.label6 = new Label();
      this.t_IconID = new TextBox();
      this.label5 = new Label();
      this.groupBox4 = new GroupBox();
      this.t_EffectDamage = new TextBox();
      this.label8 = new Label();
      this.t_EffectAttack = new TextBox();
      this.label9 = new Label();
      this.t_EffectNormal = new TextBox();
      this.label10 = new Label();
      this.groupBox10 = new GroupBox();
      this.t_Set5 = new TextBox();
      this.label34 = new Label();
      this.t_Set4 = new TextBox();
      this.label30 = new Label();
      this.t_Set3 = new TextBox();
      this.label31 = new Label();
      this.t_Set2 = new TextBox();
      this.label32 = new Label();
      this.t_Set1 = new TextBox();
      this.label33 = new Label();
      this.groupBox5 = new GroupBox();
      this.t_Level2 = new TextBox();
      this.label14 = new Label();
      this.button4 = new Button();
      this.button3 = new Button();
      this.t_Price = new TextBox();
      this.t_Weight = new TextBox();
      this.t_Level = new TextBox();
      this.label11 = new Label();
      this.groupBox8 = new GroupBox();
      this.t_RareOptionRate = new TextBox();
      this.label24 = new Label();
      this.t_RareOptionID = new TextBox();
      this.label25 = new Label();
      this.groupBox7 = new GroupBox();
      this.panel2 = new Panel();
      this.checkBox_class8 = new CheckBox();
      this.checkBox_class7 = new CheckBox();
      this.checkBox_class6 = new CheckBox();
      this.checkBox_class5 = new CheckBox();
      this.checkBox_class4 = new CheckBox();
      this.checkBox_class3 = new CheckBox();
      this.checkBox_class2 = new CheckBox();
      this.checkBox_class1 = new CheckBox();
      this.checkBox_class0 = new CheckBox();
      this.t_maxuse = new TextBox();
      this.label76 = new Label();
      this.button1 = new Button();
      this.t_Flag = new TextBox();
      this.label22 = new Label();
      this.t_WearingPosCombo = new ComboBox();
      this.t_WearingPos = new TextBox();
      this.label21 = new Label();
      this.t_Class = new TextBox();
      this.label20 = new Label();
      this.t_SubTypeCombo = new ComboBox();
      this.t_SubType = new TextBox();
      this.label19 = new Label();
      this.t_TypeCombo = new ComboBox();
      this.t_Type = new TextBox();
      this.label18 = new Label();
      this.tabPage4 = new TabPage();
      this.groupBox11 = new GroupBox();
      this.tabControl1 = new TabControl();
      this.tabPage1 = new TabPage();
      this.CraftGrid = new DataGridView();
      this.ItemIcon = new DataGridViewImageColumn();
      this.ItemID = new DataGridViewTextBoxColumn();
      this.ItemName = new DataGridViewTextBoxColumn();
      this.Amount = new DataGridViewTextBoxColumn();
      this.tabPage2 = new TabPage();
      this.t_CraftItemSearch10 = new Button();
      this.t_CraftItemAmount10 = new TextBox();
      this.t_CraftItemID10 = new TextBox();
      this.label45 = new Label();
      this.label46 = new Label();
      this.t_CraftItemAmount9 = new TextBox();
      this.t_CraftItemID9 = new TextBox();
      this.label47 = new Label();
      this.label48 = new Label();
      this.t_CraftItemAmount8 = new TextBox();
      this.t_CraftItemID8 = new TextBox();
      this.label49 = new Label();
      this.label50 = new Label();
      this.t_CraftItemAmount7 = new TextBox();
      this.t_CraftItemID7 = new TextBox();
      this.label51 = new Label();
      this.label52 = new Label();
      this.t_CraftItemAmount6 = new TextBox();
      this.t_CraftItemID6 = new TextBox();
      this.label53 = new Label();
      this.label54 = new Label();
      this.t_CraftItemAmount5 = new TextBox();
      this.t_CraftItemID5 = new TextBox();
      this.label43 = new Label();
      this.label44 = new Label();
      this.t_CraftItemAmount4 = new TextBox();
      this.t_CraftItemID4 = new TextBox();
      this.label41 = new Label();
      this.label42 = new Label();
      this.t_CraftItemAmount3 = new TextBox();
      this.t_CraftItemID3 = new TextBox();
      this.label39 = new Label();
      this.label40 = new Label();
      this.t_CraftItemAmount2 = new TextBox();
      this.t_CraftItemID2 = new TextBox();
      this.label37 = new Label();
      this.label38 = new Label();
      this.t_CraftItemAmount1 = new TextBox();
      this.t_CraftItemID1 = new TextBox();
      this.label35 = new Label();
      this.label36 = new Label();
      this.t_CraftItemSearch9 = new Button();
      this.t_CraftItemSearch8 = new Button();
      this.t_CraftItemSearch7 = new Button();
      this.t_CraftItemSearch6 = new Button();
      this.t_CraftItemSearch5 = new Button();
      this.t_CraftItemSearch4 = new Button();
      this.t_CraftItemSearch3 = new Button();
      this.t_CraftItemSearch2 = new Button();
      this.t_CraftItemSearch1 = new Button();
      this.groupBox9 = new GroupBox();
      this.t_CraftSkill2Level = new TextBox();
      this.label27 = new Label();
      this.t_CraftSkill1Level = new TextBox();
      this.label28 = new Label();
      this.t_CraftSkill2ID = new TextBox();
      this.label23 = new Label();
      this.t_CraftSkill1ID = new TextBox();
      this.label26 = new Label();
      this.tabPage5 = new TabPage();
      this.groupBox12 = new GroupBox();
      this.btnRareSearch9 = new Button();
      this.tbRareOpt9 = new TextBox();
      this.tbRareChance9 = new TextBox();
      this.label66 = new Label();
      this.label67 = new Label();
      this.btnRareSearch8 = new Button();
      this.tbRareOpt8 = new TextBox();
      this.tbRareChance8 = new TextBox();
      this.label68 = new Label();
      this.label69 = new Label();
      this.btnRareSearch7 = new Button();
      this.tbRareOpt7 = new TextBox();
      this.tbRareChance7 = new TextBox();
      this.label70 = new Label();
      this.label71 = new Label();
      this.btnRareSearch6 = new Button();
      this.tbRareOpt6 = new TextBox();
      this.tbRareChance6 = new TextBox();
      this.label72 = new Label();
      this.label73 = new Label();
      this.btnRareSearch5 = new Button();
      this.tbRareOpt5 = new TextBox();
      this.tbRareChance5 = new TextBox();
      this.label74 = new Label();
      this.label75 = new Label();
      this.btnRareSearch4 = new Button();
      this.tbRareOpt4 = new TextBox();
      this.tbRareChance4 = new TextBox();
      this.label64 = new Label();
      this.label65 = new Label();
      this.btnRareSearch3 = new Button();
      this.tbRareOpt3 = new TextBox();
      this.tbRareChance3 = new TextBox();
      this.label62 = new Label();
      this.label63 = new Label();
      this.btnRareSearch2 = new Button();
      this.tbRareOpt2 = new TextBox();
      this.tbRareChance2 = new TextBox();
      this.label60 = new Label();
      this.label61 = new Label();
      this.btnRareSearch1 = new Button();
      this.tbRareOpt1 = new TextBox();
      this.tbRareChance1 = new TextBox();
      this.label58 = new Label();
      this.label59 = new Label();
      this.btnRareSearch0 = new Button();
      this.tbRareOpt0 = new TextBox();
      this.tbRareChance0 = new TextBox();
      this.label57 = new Label();
      this.label56 = new Label();
      this.panel3 = new Panel();
      this.btnRareDbPut = new Button();
      this.btnRareDbGet = new Button();
      this.tabPage6 = new TabPage();
      this.textBox6 = new TextBox();
      this.textBox5 = new TextBox();
      this.textBox4 = new TextBox();
      this.textBox3 = new TextBox();
      this.textBox2 = new TextBox();
      this.textBox1 = new TextBox();
      this.btnSearchSkill3 = new Button();
      this.btnSearchSkill2 = new Button();
      this.btnSearchSkill1 = new Button();
      this.tbCB1 = new TextBox();
      this.tbCB2 = new TextBox();
      this.label89 = new Label();
      this.label86 = new Label();
      this.label87 = new Label();
      this.label88 = new Label();
      this.label85 = new Label();
      this.label84 = new Label();
      this.label83 = new Label();
      this.label81 = new Label();
      this.label82 = new Label();
      this.tbSkillLevel3 = new TextBox();
      this.tbSkillID3 = new TextBox();
      this.label79 = new Label();
      this.label80 = new Label();
      this.tbSkillLevel2 = new TextBox();
      this.tbSkillID2 = new TextBox();
      this.label78 = new Label();
      this.label77 = new Label();
      this.tbSkillLevel1 = new TextBox();
      this.tbSkillID1 = new TextBox();
      this.tbSealID6 = new TextBox();
      this.cbSealLevel6 = new ComboBox();
      this.tbSealLevel6 = new TextBox();
      this.cbSealID6 = new ComboBox();
      this.tbSealID5 = new TextBox();
      this.cbSealLevel5 = new ComboBox();
      this.tbSealLevel5 = new TextBox();
      this.cbSealID5 = new ComboBox();
      this.tbSealID4 = new TextBox();
      this.cbSealLevel4 = new ComboBox();
      this.tbSealLevel4 = new TextBox();
      this.cbSealID4 = new ComboBox();
      this.tbSealID3 = new TextBox();
      this.cbSealLevel3 = new ComboBox();
      this.tbSealLevel3 = new TextBox();
      this.cbSealID3 = new ComboBox();
      this.tbSealID2 = new TextBox();
      this.cbSealLevel2 = new ComboBox();
      this.tbSealLevel2 = new TextBox();
      this.cbSealID2 = new ComboBox();
      this.tbSealID1 = new TextBox();
      this.cbSealLevel1 = new ComboBox();
      this.tbSealLevel1 = new TextBox();
      this.cbSealID1 = new ComboBox();
      this.pbSkill3Icon = new PictureBox();
      this.pbSkill2Icon = new PictureBox();
      this.pbSkill1Icon = new PictureBox();
      this.lblCurDataPurple = new Label();
      this.btnPurplePut = new Button();
      this.btnPurpleGet = new Button();
      this.groupBox1 = new GroupBox();
      this.chk3D = new CheckBox();
      this.slideLeftRight = new TrackBar();
      this.slideUpDown = new TrackBar();
      this.slideZoom = new TrackBar();
      this.panel3DView = new Panel();
      this.ModPanel = new Panel();
      this.chkDbUpdate = new CheckBox();
      this.pictureBox1 = new PictureBox();
      this.label29 = new Label();
      this.t_DiscardChanges = new Button();
      this.t_SaveRecord = new Button();
      this.label1 = new Label();
      this.SearchText = new TextBox();
      this.statusStrip1 = new StatusStrip();
      this.status = new ToolStripStatusLabel();
      this.label15 = new Label();
      this.textBox7 = new TextBox();
      this.groupBox6 = new GroupBox();
      this.groupBox14 = new GroupBox();
      this.ItemListBox = new ListBox();
      this.t_DeleteItem = new Button();
      this.t_CopyToNew = new Button();
      this.t_NewItem = new Button();
      this.timer1 = new Timer(this.components);
      this.tb_castleWar = new TextBox();
      this.label16 = new Label();
      this.menuStrip1.SuspendLayout();
      this.tabControl2.SuspendLayout();
      this.tabPage3.SuspendLayout();
      this.groupBox13.SuspendLayout();
      this.groupBox23.SuspendLayout();
      this.groupBox16.SuspendLayout();
      this.groupBox2.SuspendLayout();
      this.groupBox3.SuspendLayout();
      ((ISupportInitialize) this.t_Icon).BeginInit();
      this.groupBox4.SuspendLayout();
      this.groupBox10.SuspendLayout();
      this.groupBox5.SuspendLayout();
      this.groupBox8.SuspendLayout();
      this.groupBox7.SuspendLayout();
      this.panel2.SuspendLayout();
      this.tabPage4.SuspendLayout();
      this.groupBox11.SuspendLayout();
      this.tabControl1.SuspendLayout();
      this.tabPage1.SuspendLayout();
      ((ISupportInitialize) this.CraftGrid).BeginInit();
      this.tabPage2.SuspendLayout();
      this.groupBox9.SuspendLayout();
      this.tabPage5.SuspendLayout();
      this.groupBox12.SuspendLayout();
      this.panel3.SuspendLayout();
      this.tabPage6.SuspendLayout();
      ((ISupportInitialize) this.pbSkill3Icon).BeginInit();
      ((ISupportInitialize) this.pbSkill2Icon).BeginInit();
      ((ISupportInitialize) this.pbSkill1Icon).BeginInit();
      this.groupBox1.SuspendLayout();
      this.slideLeftRight.BeginInit();
      this.slideUpDown.BeginInit();
      this.slideZoom.BeginInit();
      this.ModPanel.SuspendLayout();
      ((ISupportInitialize) this.pictureBox1).BeginInit();
      this.statusStrip1.SuspendLayout();
      this.groupBox6.SuspendLayout();
      this.groupBox14.SuspendLayout();
      this.SuspendLayout();
      this.menuStrip1.Items.AddRange(new ToolStripItem[5]
      {
        (ToolStripItem) this.fileToolStripMenuItem,
        (ToolStripItem) this.exportToolStripMenuItem,
        (ToolStripItem) this.toolsToolStripMenuItem,
        (ToolStripItem) this.mySQLConnectionToolStripMenuItem,
        (ToolStripItem) this.extraToolStripMenuItem
      });
      this.menuStrip1.Location = new Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new Size(1453, 24);
      this.menuStrip1.TabIndex = 3;
      this.menuStrip1.Text = "menuStrip1";
      this.fileToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[6]
      {
        (ToolStripItem) this.openToolStripMenuItem,
        (ToolStripItem) this.toolStripSeparator1,
        (ToolStripItem) this.saveToolStripMenuItem,
        (ToolStripItem) this.saveasToolStripMenuItem,
        (ToolStripItem) this.toolStripSeparator2,
        (ToolStripItem) this.exitToolStripMenuItem1
      });
      this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
      this.fileToolStripMenuItem.Size = new Size(37, 20);
      this.fileToolStripMenuItem.Text = "File";
      this.openToolStripMenuItem.Name = "openToolStripMenuItem";
      this.openToolStripMenuItem.Size = new Size(180, 22);
      this.openToolStripMenuItem.Text = "Open";
      this.openToolStripMenuItem.Click += new EventHandler(this.openToolStripMenuItem_Click);
      this.toolStripSeparator1.Name = "toolStripSeparator1";
      this.toolStripSeparator1.Size = new Size(177, 6);
      this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
      this.saveToolStripMenuItem.Size = new Size(180, 22);
      this.saveToolStripMenuItem.Text = "Save";
      this.saveasToolStripMenuItem.Name = "saveasToolStripMenuItem";
      this.saveasToolStripMenuItem.Size = new Size(180, 22);
      this.saveasToolStripMenuItem.Text = "Save As";
      this.toolStripSeparator2.Name = "toolStripSeparator2";
      this.toolStripSeparator2.Size = new Size(177, 6);
      this.exitToolStripMenuItem1.Name = "exitToolStripMenuItem1";
      this.exitToolStripMenuItem1.Size = new Size(180, 22);
      this.exitToolStripMenuItem1.Text = "Exit";
      this.exportToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[2]
      {
        (ToolStripItem) this.toolStripMenuItem1,
        (ToolStripItem) this.thisToolStripMenuItem
      });
      this.exportToolStripMenuItem.Name = "exportToolStripMenuItem";
      this.exportToolStripMenuItem.Size = new Size(52, 20);
      this.exportToolStripMenuItem.Text = "Export";
      this.toolStripMenuItem1.DropDownItems.AddRange(new ToolStripItem[4]
      {
        (ToolStripItem) this.sQLToolStripMenuItem,
        (ToolStripItem) this.xMLToolStripMenuItem,
        (ToolStripItem) this.itemnameToolStripMenuItem,
        (ToolStripItem) this.hTMLToolStripMenuItem
      });
      this.toolStripMenuItem1.Name = "toolStripMenuItem1";
      this.toolStripMenuItem1.Size = new Size(133, 22);
      this.toolStripMenuItem1.Text = "File";
      this.sQLToolStripMenuItem.Name = "sQLToolStripMenuItem";
      this.sQLToolStripMenuItem.Size = new Size(148, 22);
      this.sQLToolStripMenuItem.Text = "SQL";
      this.xMLToolStripMenuItem.Name = "xMLToolStripMenuItem";
      this.xMLToolStripMenuItem.Size = new Size(148, 22);
      this.xMLToolStripMenuItem.Text = "XML";
      this.itemnameToolStripMenuItem.Name = "itemnameToolStripMenuItem";
      this.itemnameToolStripMenuItem.Size = new Size(148, 22);
      this.itemnameToolStripMenuItem.Text = "Itemname.lod";
      this.hTMLToolStripMenuItem.Name = "hTMLToolStripMenuItem";
      this.hTMLToolStripMenuItem.Size = new Size(148, 22);
      this.hTMLToolStripMenuItem.Text = "HTML";
      this.thisToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[2]
      {
        (ToolStripItem) this.insertQueryToolStripMenuItem,
        (ToolStripItem) this.updateQueryToolStripMenuItem
      });
      this.thisToolStripMenuItem.Name = "thisToolStripMenuItem";
      this.thisToolStripMenuItem.Size = new Size(133, 22);
      this.thisToolStripMenuItem.Text = "This record";
      this.insertQueryToolStripMenuItem.Name = "insertQueryToolStripMenuItem";
      this.insertQueryToolStripMenuItem.Size = new Size(147, 22);
      this.insertQueryToolStripMenuItem.Text = "Insert Query";
      this.updateQueryToolStripMenuItem.Name = "updateQueryToolStripMenuItem";
      this.updateQueryToolStripMenuItem.Size = new Size(147, 22);
      this.updateQueryToolStripMenuItem.Text = "Update Query";
      this.toolsToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[2]
      {
        (ToolStripItem) this.iconViewerToolStripMenuItem,
        (ToolStripItem) this.itemFlagBuilderToolStripMenuItem
      });
      this.toolsToolStripMenuItem.Name = "toolsToolStripMenuItem";
      this.toolsToolStripMenuItem.Size = new Size(47, 20);
      this.toolsToolStripMenuItem.Text = "Tools";
      this.iconViewerToolStripMenuItem.Name = "iconViewerToolStripMenuItem";
      this.iconViewerToolStripMenuItem.Size = new Size(163, 22);
      this.iconViewerToolStripMenuItem.Text = "Icon Viewer";
      this.itemFlagBuilderToolStripMenuItem.Name = "itemFlagBuilderToolStripMenuItem";
      this.itemFlagBuilderToolStripMenuItem.Size = new Size(163, 22);
      this.itemFlagBuilderToolStripMenuItem.Text = "Item Flag Builder";
      this.mySQLConnectionToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[10]
      {
        (ToolStripItem) this.uPDATEThisRecordToolStripMenuItem,
        (ToolStripItem) this.iNSERTThisRecordToolStripMenuItem,
        (ToolStripItem) this.configConnectionToolStripMenuItem,
        (ToolStripItem) this.massActionToolStripMenuItem,
        (ToolStripItem) this.iNSERTALLNotExistingToolStripMenuItem,
        (ToolStripItem) this.uPDATEINSERTThisRecordToolStripMenuItem,
        (ToolStripItem) this.gETALLFromDatabaseToolStripMenuItem,
        (ToolStripItem) this.updateAllNamesToDBToolStripMenuItem,
        (ToolStripItem) this.updateAllFlagsToDBToolStripMenuItem,
        (ToolStripItem) this.updateAllPicsToDBToolStripMenuItem
      });
      this.mySQLConnectionToolStripMenuItem.Name = "mySQLConnectionToolStripMenuItem";
      this.mySQLConnectionToolStripMenuItem.Size = new Size(122, 20);
      this.mySQLConnectionToolStripMenuItem.Text = "mySQL Connection";
      this.uPDATEThisRecordToolStripMenuItem.Name = "uPDATEThisRecordToolStripMenuItem";
      this.uPDATEThisRecordToolStripMenuItem.Size = new Size(221, 22);
      this.uPDATEThisRecordToolStripMenuItem.Text = "UPDATE this record";
      this.iNSERTThisRecordToolStripMenuItem.Name = "iNSERTThisRecordToolStripMenuItem";
      this.iNSERTThisRecordToolStripMenuItem.Size = new Size(221, 22);
      this.iNSERTThisRecordToolStripMenuItem.Text = "INSERT this record";
      this.configConnectionToolStripMenuItem.Name = "configConnectionToolStripMenuItem";
      this.configConnectionToolStripMenuItem.Size = new Size(221, 22);
      this.configConnectionToolStripMenuItem.Text = "Config Connection";
      this.massActionToolStripMenuItem.Name = "massActionToolStripMenuItem";
      this.massActionToolStripMenuItem.Size = new Size(221, 22);
      this.massActionToolStripMenuItem.Text = "Mass Action";
      this.iNSERTALLNotExistingToolStripMenuItem.Name = "iNSERTALLNotExistingToolStripMenuItem";
      this.iNSERTALLNotExistingToolStripMenuItem.Size = new Size(221, 22);
      this.iNSERTALLNotExistingToolStripMenuItem.Text = "INSERT ALL Not Existing";
      this.uPDATEINSERTThisRecordToolStripMenuItem.Name = "uPDATEINSERTThisRecordToolStripMenuItem";
      this.uPDATEINSERTThisRecordToolStripMenuItem.Size = new Size(221, 22);
      this.uPDATEINSERTThisRecordToolStripMenuItem.Text = "UPDATE/INSERT This record";
      this.gETALLFromDatabaseToolStripMenuItem.Name = "gETALLFromDatabaseToolStripMenuItem";
      this.gETALLFromDatabaseToolStripMenuItem.Size = new Size(221, 22);
      this.gETALLFromDatabaseToolStripMenuItem.Text = "GET ALL From Database";
      this.updateAllNamesToDBToolStripMenuItem.Name = "updateAllNamesToDBToolStripMenuItem";
      this.updateAllNamesToDBToolStripMenuItem.Size = new Size(221, 22);
      this.updateAllNamesToDBToolStripMenuItem.Text = "Update All Names To DB";
      this.updateAllFlagsToDBToolStripMenuItem.Name = "updateAllFlagsToDBToolStripMenuItem";
      this.updateAllFlagsToDBToolStripMenuItem.Size = new Size(221, 22);
      this.updateAllFlagsToDBToolStripMenuItem.Text = "Update All Flags To DB";
      this.updateAllPicsToDBToolStripMenuItem.Name = "updateAllPicsToDBToolStripMenuItem";
      this.updateAllPicsToDBToolStripMenuItem.Size = new Size(221, 22);
      this.updateAllPicsToDBToolStripMenuItem.Text = "Update All Pics To DB";
      this.extraToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[9]
      {
        (ToolStripItem) this.updateAllNamesInDatabaseToolStripMenuItem,
        (ToolStripItem) this.toolStripMenuItem2,
        (ToolStripItem) this.getRecordsFromOtherFileToolStripMenuItem,
        (ToolStripItem) this.updateAllPricesInDatabaseToolStripMenuItem,
        (ToolStripItem) this.getPhpItemlistToolStripMenuItem,
        (ToolStripItem) this.removeAllIconsAbove9ToolStripMenuItem,
        (ToolStripItem) this.removeAllIconsAbove14ToolStripMenuItem,
        (ToolStripItem) this.getAllFlagsFromOtherFileToolStripMenuItem,
        (ToolStripItem) this.getIconsFromOtherFileToolStripMenuItem
      });
      this.extraToolStripMenuItem.Name = "extraToolStripMenuItem";
      this.extraToolStripMenuItem.Size = new Size(44, 20);
      this.extraToolStripMenuItem.Text = "Extra";
      this.updateAllNamesInDatabaseToolStripMenuItem.Name = "updateAllNamesInDatabaseToolStripMenuItem";
      this.updateAllNamesInDatabaseToolStripMenuItem.Size = new Size(243, 22);
      this.updateAllNamesInDatabaseToolStripMenuItem.Text = "Update all names in database";
      this.toolStripMenuItem2.Name = "toolStripMenuItem2";
      this.toolStripMenuItem2.Size = new Size(243, 22);
      this.toolStripMenuItem2.Text = "Update language from other file";
      this.getRecordsFromOtherFileToolStripMenuItem.Name = "getRecordsFromOtherFileToolStripMenuItem";
      this.getRecordsFromOtherFileToolStripMenuItem.Size = new Size(243, 22);
      this.getRecordsFromOtherFileToolStripMenuItem.Text = "Get records from other file";
      this.updateAllPricesInDatabaseToolStripMenuItem.Name = "updateAllPricesInDatabaseToolStripMenuItem";
      this.updateAllPricesInDatabaseToolStripMenuItem.Size = new Size(243, 22);
      this.updateAllPricesInDatabaseToolStripMenuItem.Text = "Update all prices in database";
      this.getPhpItemlistToolStripMenuItem.Name = "getPhpItemlistToolStripMenuItem";
      this.getPhpItemlistToolStripMenuItem.Size = new Size(243, 22);
      this.getPhpItemlistToolStripMenuItem.Text = "Get php itemlist";
      this.removeAllIconsAbove9ToolStripMenuItem.Name = "removeAllIconsAbove9ToolStripMenuItem";
      this.removeAllIconsAbove9ToolStripMenuItem.Size = new Size(243, 22);
      this.removeAllIconsAbove9ToolStripMenuItem.Text = "Remove all icons above 9";
      this.removeAllIconsAbove14ToolStripMenuItem.Name = "removeAllIconsAbove14ToolStripMenuItem";
      this.removeAllIconsAbove14ToolStripMenuItem.Size = new Size(243, 22);
      this.removeAllIconsAbove14ToolStripMenuItem.Text = "Remove all icons above 14";
      this.getAllFlagsFromOtherFileToolStripMenuItem.Enabled = false;
      this.getAllFlagsFromOtherFileToolStripMenuItem.Name = "getAllFlagsFromOtherFileToolStripMenuItem";
      this.getAllFlagsFromOtherFileToolStripMenuItem.Size = new Size(243, 22);
      this.getAllFlagsFromOtherFileToolStripMenuItem.Text = "Get All Flags From Other File";
      this.getIconsFromOtherFileToolStripMenuItem.Name = "getIconsFromOtherFileToolStripMenuItem";
      this.getIconsFromOtherFileToolStripMenuItem.Size = new Size(243, 22);
      this.getIconsFromOtherFileToolStripMenuItem.Text = "Get Icons From Other File";
      this.tabControl2.Controls.Add((Control) this.tabPage3);
      this.tabControl2.Controls.Add((Control) this.tabPage4);
      this.tabControl2.Controls.Add((Control) this.tabPage5);
      this.tabControl2.Controls.Add((Control) this.tabPage6);
      this.tabControl2.Enabled = false;
      this.tabControl2.Location = new Point(287, 27);
      this.tabControl2.Name = "tabControl2";
      this.tabControl2.SelectedIndex = 0;
      this.tabControl2.Size = new Size(770, 518);
      this.tabControl2.TabIndex = 19;
      this.tabPage3.BackColor = SystemColors.Control;
      this.tabPage3.BorderStyle = BorderStyle.FixedSingle;
      this.tabPage3.Controls.Add((Control) this.tb_castleWar);
      this.tabPage3.Controls.Add((Control) this.label16);
      this.tabPage3.Controls.Add((Control) this.groupBox13);
      this.tabPage3.Controls.Add((Control) this.groupBox23);
      this.tabPage3.Controls.Add((Control) this.groupBox16);
      this.tabPage3.Controls.Add((Control) this.groupBox2);
      this.tabPage3.Controls.Add((Control) this.groupBox3);
      this.tabPage3.Controls.Add((Control) this.groupBox4);
      this.tabPage3.Controls.Add((Control) this.groupBox10);
      this.tabPage3.Controls.Add((Control) this.groupBox5);
      this.tabPage3.Controls.Add((Control) this.groupBox8);
      this.tabPage3.Controls.Add((Control) this.groupBox7);
      this.tabPage3.Location = new Point(4, 22);
      this.tabPage3.Name = "tabPage3";
      this.tabPage3.Padding = new Padding(3);
      this.tabPage3.Size = new Size(762, 492);
      this.tabPage3.TabIndex = 0;
      this.tabPage3.Text = "Basic Propperties";
      this.groupBox13.Controls.Add((Control) this.btnPercent2Add);
      this.groupBox13.Controls.Add((Control) this.btnPercent1Add);
      this.groupBox13.Controls.Add((Control) this.btnPercentAdd);
      this.groupBox13.Controls.Add((Control) this.TbPercent2);
      this.groupBox13.Controls.Add((Control) this.TbPercent1);
      this.groupBox13.Controls.Add((Control) this.TbPercent);
      this.groupBox13.Controls.Add((Control) this.label108);
      this.groupBox13.Controls.Add((Control) this.label107);
      this.groupBox13.Controls.Add((Control) this.label106);
      this.groupBox13.Controls.Add((Control) this.t_Num4);
      this.groupBox13.Controls.Add((Control) this.label90);
      this.groupBox13.Controls.Add((Control) this.t_Num0);
      this.groupBox13.Controls.Add((Control) this.label93);
      this.groupBox13.Controls.Add((Control) this.label94);
      this.groupBox13.Controls.Add((Control) this.t_Num1);
      this.groupBox13.Controls.Add((Control) this.t_Num3);
      this.groupBox13.Controls.Add((Control) this.label95);
      this.groupBox13.Controls.Add((Control) this.label96);
      this.groupBox13.Controls.Add((Control) this.t_Num2);
      this.groupBox13.Location = new Point(201, 305);
      this.groupBox13.Name = "groupBox13";
      this.groupBox13.Size = new Size((int) byte.MaxValue, 146);
      this.groupBox13.TabIndex = 62;
      this.groupBox13.TabStop = false;
      this.groupBox13.Text = "Options";
      this.btnPercent2Add.Location = new Point(131, 73);
      this.btnPercent2Add.Name = "btnPercent2Add";
      this.btnPercent2Add.Size = new Size(19, 20);
      this.btnPercent2Add.TabIndex = 32;
      this.btnPercent2Add.Text = "+";
      this.btnPercent2Add.UseVisualStyleBackColor = true;
      this.btnPercent1Add.Location = new Point(131, 47);
      this.btnPercent1Add.Name = "btnPercent1Add";
      this.btnPercent1Add.Size = new Size(19, 20);
      this.btnPercent1Add.TabIndex = 31;
      this.btnPercent1Add.Text = "+";
      this.btnPercent1Add.UseVisualStyleBackColor = true;
      this.btnPercentAdd.Location = new Point(131, 19);
      this.btnPercentAdd.Name = "btnPercentAdd";
      this.btnPercentAdd.Size = new Size(19, 20);
      this.btnPercentAdd.TabIndex = 30;
      this.btnPercentAdd.Text = "+";
      this.btnPercentAdd.UseVisualStyleBackColor = true;
      this.TbPercent2.BorderStyle = BorderStyle.FixedSingle;
      this.TbPercent2.Location = new Point(157, 72);
      this.TbPercent2.Name = "TbPercent2";
      this.TbPercent2.Size = new Size(53, 20);
      this.TbPercent2.TabIndex = 29;
      this.TbPercent2.TextChanged += new EventHandler(this.ValueChanged);
      this.TbPercent1.BorderStyle = BorderStyle.FixedSingle;
      this.TbPercent1.Location = new Point(157, 46);
      this.TbPercent1.Name = "TbPercent1";
      this.TbPercent1.Size = new Size(53, 20);
      this.TbPercent1.TabIndex = 28;
      this.TbPercent1.TextChanged += new EventHandler(this.ValueChanged);
      this.TbPercent.BorderStyle = BorderStyle.FixedSingle;
      this.TbPercent.Location = new Point(157, 20);
      this.TbPercent.Name = "TbPercent";
      this.TbPercent.Size = new Size(53, 20);
      this.TbPercent.TabIndex = 27;
      this.TbPercent.TextChanged += new EventHandler(this.ValueChanged);
      this.label108.AutoSize = true;
      this.label108.Font = new System.Drawing.Font("Consolas", 9.75f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.label108.Location = new Point(218, 75);
      this.label108.Name = "label108";
      this.label108.Size = new Size(14, 15);
      this.label108.TabIndex = 26;
      this.label108.Text = "%";
      this.label107.AutoSize = true;
      this.label107.Font = new System.Drawing.Font("Consolas", 9.75f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.label107.Location = new Point(217, 49);
      this.label107.Name = "label107";
      this.label107.Size = new Size(14, 15);
      this.label107.TabIndex = 25;
      this.label107.Text = "%";
      this.label106.AutoSize = true;
      this.label106.Font = new System.Drawing.Font("Consolas", 9.75f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.label106.Location = new Point(216, 22);
      this.label106.Name = "label106";
      this.label106.Size = new Size(14, 15);
      this.label106.TabIndex = 24;
      this.label106.Text = "%";
      this.t_Num4.BorderStyle = BorderStyle.FixedSingle;
      this.t_Num4.Location = new Point(65, 124);
      this.t_Num4.Name = "t_Num4";
      this.t_Num4.Size = new Size(53, 20);
      this.t_Num4.TabIndex = 22;
      this.label90.AutoSize = true;
      this.label90.Location = new Point(9, 126);
      this.label90.Name = "label90";
      this.label90.Size = new Size(38, 13);
      this.label90.TabIndex = 23;
      this.label90.Text = "Num4:";
      this.t_Num0.BorderStyle = BorderStyle.FixedSingle;
      this.t_Num0.Location = new Point(65, 20);
      this.t_Num0.Name = "t_Num0";
      this.t_Num0.Size = new Size(53, 20);
      this.t_Num0.TabIndex = 14;
      this.t_Num0.TextChanged += new EventHandler(this.ValueChanged);
      this.label93.AutoSize = true;
      this.label93.Location = new Point(9, 22);
      this.label93.Name = "label93";
      this.label93.Size = new Size(38, 13);
      this.label93.TabIndex = 15;
      this.label93.Text = "Num0:";
      this.label94.AutoSize = true;
      this.label94.Location = new Point(9, 100);
      this.label94.Name = "label94";
      this.label94.Size = new Size(38, 13);
      this.label94.TabIndex = 21;
      this.label94.Text = "Num3:";
      this.t_Num1.BorderStyle = BorderStyle.FixedSingle;
      this.t_Num1.Location = new Point(65, 46);
      this.t_Num1.Name = "t_Num1";
      this.t_Num1.Size = new Size(53, 20);
      this.t_Num1.TabIndex = 16;
      this.t_Num1.TextChanged += new EventHandler(this.ValueChanged);
      this.t_Num3.BorderStyle = BorderStyle.FixedSingle;
      this.t_Num3.Location = new Point(65, 98);
      this.t_Num3.Name = "t_Num3";
      this.t_Num3.Size = new Size(53, 20);
      this.t_Num3.TabIndex = 20;
      this.t_Num3.TextChanged += new EventHandler(this.ValueChanged);
      this.label95.AutoSize = true;
      this.label95.Location = new Point(9, 48);
      this.label95.Name = "label95";
      this.label95.Size = new Size(38, 13);
      this.label95.TabIndex = 17;
      this.label95.Text = "Num1:";
      this.label96.AutoSize = true;
      this.label96.Location = new Point(9, 74);
      this.label96.Name = "label96";
      this.label96.Size = new Size(38, 13);
      this.label96.TabIndex = 19;
      this.label96.Text = "Num2:";
      this.t_Num2.BorderStyle = BorderStyle.FixedSingle;
      this.t_Num2.Location = new Point(65, 72);
      this.t_Num2.Name = "t_Num2";
      this.t_Num2.Size = new Size(53, 20);
      this.t_Num2.TabIndex = 18;
      this.t_Num2.TextChanged += new EventHandler(this.ValueChanged);
      this.groupBox23.Controls.Add((Control) this.label12);
      this.groupBox23.Controls.Add((Control) this.t_quest_tigger);
      this.groupBox23.Controls.Add((Control) this.label13);
      this.groupBox23.Controls.Add((Control) this.t_quest_tigger_count);
      this.groupBox23.Location = new Point(201, 258);
      this.groupBox23.Name = "groupBox23";
      this.groupBox23.Size = new Size(289, 41);
      this.groupBox23.TabIndex = 61;
      this.groupBox23.TabStop = false;
      this.groupBox23.Text = "Quest Trigger Info";
      this.label12.AutoSize = true;
      this.label12.Location = new Point(28, 21);
      this.label12.Name = "label12";
      this.label12.Size = new Size(26, 13);
      this.label12.TabIndex = 54;
      this.label12.Text = "IDs:";
      this.t_quest_tigger.BorderStyle = BorderStyle.FixedSingle;
      this.t_quest_tigger.Location = new Point(60, 17);
      this.t_quest_tigger.Name = "t_quest_tigger";
      this.t_quest_tigger.Size = new Size(68, 20);
      this.t_quest_tigger.TabIndex = 53;
      this.t_quest_tigger.TextChanged += new EventHandler(this.ValueChanged);
      this.label13.AutoSize = true;
      this.label13.Location = new Point(134, 19);
      this.label13.Name = "label13";
      this.label13.Size = new Size(38, 13);
      this.label13.TabIndex = 52;
      this.label13.Text = "Count:";
      this.t_quest_tigger_count.BorderStyle = BorderStyle.FixedSingle;
      this.t_quest_tigger_count.Location = new Point(178, 16);
      this.t_quest_tigger_count.Name = "t_quest_tigger_count";
      this.t_quest_tigger_count.Size = new Size(68, 20);
      this.t_quest_tigger_count.TabIndex = 51;
      this.t_quest_tigger_count.TextChanged += new EventHandler(this.ValueChanged);
      this.groupBox16.Controls.Add((Control) this.comboBox26);
      this.groupBox16.Controls.Add((Control) this.comboBox25);
      this.groupBox16.Controls.Add((Control) this.comboBox24);
      this.groupBox16.Controls.Add((Control) this.label92);
      this.groupBox16.Controls.Add((Control) this.t_rvr_Grade);
      this.groupBox16.Controls.Add((Control) this.label91);
      this.groupBox16.Controls.Add((Control) this.t_rvr_Value);
      this.groupBox16.Location = new Point(473, 174);
      this.groupBox16.Name = "groupBox16";
      this.groupBox16.Size = new Size(209, 74);
      this.groupBox16.TabIndex = 54;
      this.groupBox16.TabStop = false;
      this.groupBox16.Text = "RvR";
      this.comboBox26.FormattingEnabled = true;
      this.comboBox26.Location = new Point(55, 45);
      this.comboBox26.Name = "comboBox26";
      this.comboBox26.Size = new Size(102, 21);
      this.comboBox26.TabIndex = 61;
      this.comboBox25.FormattingEnabled = true;
      this.comboBox25.Location = new Point(55, 45);
      this.comboBox25.Name = "comboBox25";
      this.comboBox25.Size = new Size(102, 21);
      this.comboBox25.TabIndex = 60;
      this.comboBox24.FormattingEnabled = true;
      this.comboBox24.Location = new Point(55, 17);
      this.comboBox24.Name = "comboBox24";
      this.comboBox24.Size = new Size(102, 21);
      this.comboBox24.TabIndex = 59;
      this.label92.AutoSize = true;
      this.label92.Location = new Point(13, 48);
      this.label92.Name = "label92";
      this.label92.Size = new Size(39, 13);
      this.label92.TabIndex = 58;
      this.label92.Text = "Grade:";
      this.t_rvr_Grade.BorderStyle = BorderStyle.FixedSingle;
      this.t_rvr_Grade.Location = new Point(172, 45);
      this.t_rvr_Grade.Name = "t_rvr_Grade";
      this.t_rvr_Grade.Size = new Size(31, 20);
      this.t_rvr_Grade.TabIndex = 57;
      this.t_rvr_Grade.TextChanged += new EventHandler(this.ValueChanged);
      this.label91.AutoSize = true;
      this.label91.Location = new Point(13, 19);
      this.label91.Name = "label91";
      this.label91.Size = new Size(37, 13);
      this.label91.TabIndex = 56;
      this.label91.Text = "Value:";
      this.t_rvr_Value.BorderStyle = BorderStyle.FixedSingle;
      this.t_rvr_Value.Location = new Point(172, 17);
      this.t_rvr_Value.Name = "t_rvr_Value";
      this.t_rvr_Value.Size = new Size(31, 20);
      this.t_rvr_Value.TabIndex = 55;
      this.t_rvr_Value.TextChanged += new EventHandler(this.ValueChanged);
      this.groupBox2.BackColor = SystemColors.Control;
      this.groupBox2.Controls.Add((Control) this.button2);
      this.groupBox2.Controls.Add((Control) this.t_SMC);
      this.groupBox2.Controls.Add((Control) this.label55);
      this.groupBox2.Controls.Add((Control) this.t_Description);
      this.groupBox2.Controls.Add((Control) this.label4);
      this.groupBox2.Controls.Add((Control) this.t_ItemName);
      this.groupBox2.Controls.Add((Control) this.label3);
      this.groupBox2.Controls.Add((Control) this.t_ItemID);
      this.groupBox2.Controls.Add((Control) this.label2);
      this.groupBox2.Location = new Point(6, 6);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new Size(332, 166);
      this.groupBox2.TabIndex = 0;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "Basic";
      this.button2.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.oie_transparent;
      this.button2.BackgroundImageLayout = ImageLayout.Stretch;
      this.button2.FlatAppearance.BorderSize = 0;
      this.button2.FlatStyle = FlatStyle.Flat;
      this.button2.Location = new Point(298, 138);
      this.button2.Name = "button2";
      this.button2.Size = new Size(17, 17);
      this.button2.TabIndex = 17;
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.t_SMC.BorderStyle = BorderStyle.FixedSingle;
      this.t_SMC.Location = new Point(72, 136);
      this.t_SMC.Name = "t_SMC";
      this.t_SMC.Size = new Size(221, 20);
      this.t_SMC.TabIndex = 7;
      this.t_SMC.TextChanged += new EventHandler(this.ValueChanged);
      this.label55.AutoSize = true;
      this.label55.Location = new Point(6, 138);
      this.label55.Name = "label55";
      this.label55.Size = new Size(30, 13);
      this.label55.TabIndex = 6;
      this.label55.Text = "SMC";
      this.t_Description.BorderStyle = BorderStyle.FixedSingle;
      this.t_Description.Location = new Point(72, 72);
      this.t_Description.Multiline = true;
      this.t_Description.Name = "t_Description";
      this.t_Description.Size = new Size(244, 58);
      this.t_Description.TabIndex = 5;
      this.t_Description.TextChanged += new EventHandler(this.ValueChanged);
      this.label4.AutoSize = true;
      this.label4.Location = new Point(6, 74);
      this.label4.Name = "label4";
      this.label4.Size = new Size(60, 13);
      this.label4.TabIndex = 4;
      this.label4.Text = "Description";
      this.t_ItemName.BorderStyle = BorderStyle.FixedSingle;
      this.t_ItemName.Location = new Point(72, 46);
      this.t_ItemName.Name = "t_ItemName";
      this.t_ItemName.Size = new Size(244, 20);
      this.t_ItemName.TabIndex = 3;
      this.t_ItemName.TextChanged += new EventHandler(this.ValueChanged);
      this.label3.AutoSize = true;
      this.label3.Location = new Point(6, 48);
      this.label3.Name = "label3";
      this.label3.Size = new Size(35, 13);
      this.label3.TabIndex = 2;
      this.label3.Text = "Name";
      this.t_ItemID.BorderStyle = BorderStyle.FixedSingle;
      this.t_ItemID.Location = new Point(72, 20);
      this.t_ItemID.Name = "t_ItemID";
      this.t_ItemID.Size = new Size(69, 20);
      this.t_ItemID.TabIndex = 1;
      this.t_ItemID.TextChanged += new EventHandler(this.ValueChanged);
      this.label2.AutoSize = true;
      this.label2.Location = new Point(6, 22);
      this.label2.Name = "label2";
      this.label2.Size = new Size(18, 13);
      this.label2.TabIndex = 0;
      this.label2.Text = "ID";
      this.groupBox3.Controls.Add((Control) this.t_Icon);
      this.groupBox3.Controls.Add((Control) this.t_iconpick);
      this.groupBox3.Controls.Add((Control) this.t_IconColumn);
      this.groupBox3.Controls.Add((Control) this.label7);
      this.groupBox3.Controls.Add((Control) this.t_IconRow);
      this.groupBox3.Controls.Add((Control) this.label6);
      this.groupBox3.Controls.Add((Control) this.t_IconID);
      this.groupBox3.Controls.Add((Control) this.label5);
      this.groupBox3.Location = new Point(6, 170);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Size = new Size(189, 105);
      this.groupBox3.TabIndex = 1;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "Inventory Icon";
      this.t_Icon.BorderStyle = BorderStyle.FixedSingle;
      this.t_Icon.Location = new Point(136, 30);
      this.t_Icon.Name = "t_Icon";
      this.t_Icon.Size = new Size(30, 30);
      this.t_Icon.SizeMode = PictureBoxSizeMode.StretchImage;
      this.t_Icon.TabIndex = 8;
      this.t_Icon.TabStop = false;
      this.t_iconpick.AutoSize = true;
      this.t_iconpick.Location = new Point(119, 72);
      this.t_iconpick.Name = "t_iconpick";
      this.t_iconpick.Size = new Size(61, 13);
      this.t_iconpick.TabIndex = 9;
      this.t_iconpick.TabStop = true;
      this.t_iconpick.Text = "Icon Picker";
      this.t_IconColumn.BorderStyle = BorderStyle.FixedSingle;
      this.t_IconColumn.Location = new Point(62, 71);
      this.t_IconColumn.Name = "t_IconColumn";
      this.t_IconColumn.Size = new Size(50, 20);
      this.t_IconColumn.TabIndex = 7;
      this.t_IconColumn.TextChanged += new EventHandler(this.t_IconColumn_TextChanged);
      this.label7.AutoSize = true;
      this.label7.Location = new Point(14, 73);
      this.label7.Name = "label7";
      this.label7.Size = new Size(42, 13);
      this.label7.TabIndex = 6;
      this.label7.Text = "Column";
      this.t_IconRow.BorderStyle = BorderStyle.FixedSingle;
      this.t_IconRow.Location = new Point(62, 45);
      this.t_IconRow.Name = "t_IconRow";
      this.t_IconRow.Size = new Size(50, 20);
      this.t_IconRow.TabIndex = 5;
      this.t_IconRow.TextChanged += new EventHandler(this.t_IconRow_TextChanged);
      this.label6.AutoSize = true;
      this.label6.Location = new Point(14, 47);
      this.label6.Name = "label6";
      this.label6.Size = new Size(29, 13);
      this.label6.TabIndex = 4;
      this.label6.Text = "Row";
      this.t_IconID.BorderStyle = BorderStyle.FixedSingle;
      this.t_IconID.Location = new Point(62, 19);
      this.t_IconID.Name = "t_IconID";
      this.t_IconID.Size = new Size(50, 20);
      this.t_IconID.TabIndex = 3;
      this.t_IconID.TextChanged += new EventHandler(this.t_IconID_TextChanged);
      this.label5.AutoSize = true;
      this.label5.Location = new Point(14, 21);
      this.label5.Name = "label5";
      this.label5.Size = new Size(37, 13);
      this.label5.TabIndex = 2;
      this.label5.Text = "File ID";
      this.groupBox4.Controls.Add((Control) this.t_EffectDamage);
      this.groupBox4.Controls.Add((Control) this.label8);
      this.groupBox4.Controls.Add((Control) this.t_EffectAttack);
      this.groupBox4.Controls.Add((Control) this.label9);
      this.groupBox4.Controls.Add((Control) this.t_EffectNormal);
      this.groupBox4.Controls.Add((Control) this.label10);
      this.groupBox4.Location = new Point(201, 171);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Size = new Size(265, 84);
      this.groupBox4.TabIndex = 2;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "Item Special Effects";
      this.t_EffectDamage.BorderStyle = BorderStyle.FixedSingle;
      this.t_EffectDamage.Location = new Point(67, 57);
      this.t_EffectDamage.Name = "t_EffectDamage";
      this.t_EffectDamage.Size = new Size(192, 20);
      this.t_EffectDamage.TabIndex = 7;
      this.t_EffectDamage.TextChanged += new EventHandler(this.ValueChanged);
      this.label8.AutoSize = true;
      this.label8.Location = new Point(14, 59);
      this.label8.Name = "label8";
      this.label8.Size = new Size(47, 13);
      this.label8.TabIndex = 6;
      this.label8.Text = "Damage";
      this.t_EffectAttack.BorderStyle = BorderStyle.FixedSingle;
      this.t_EffectAttack.Location = new Point(67, 35);
      this.t_EffectAttack.Name = "t_EffectAttack";
      this.t_EffectAttack.Size = new Size(192, 20);
      this.t_EffectAttack.TabIndex = 5;
      this.t_EffectAttack.TextChanged += new EventHandler(this.ValueChanged);
      this.label9.AutoSize = true;
      this.label9.Location = new Point(14, 37);
      this.label9.Name = "label9";
      this.label9.Size = new Size(38, 13);
      this.label9.TabIndex = 4;
      this.label9.Text = "Attack";
      this.t_EffectNormal.BorderStyle = BorderStyle.FixedSingle;
      this.t_EffectNormal.Location = new Point(67, 14);
      this.t_EffectNormal.Name = "t_EffectNormal";
      this.t_EffectNormal.Size = new Size(192, 20);
      this.t_EffectNormal.TabIndex = 3;
      this.t_EffectNormal.TextChanged += new EventHandler(this.ValueChanged);
      this.label10.AutoSize = true;
      this.label10.Location = new Point(14, 16);
      this.label10.Name = "label10";
      this.label10.Size = new Size(40, 13);
      this.label10.TabIndex = 2;
      this.label10.Text = "Normal";
      this.groupBox10.Controls.Add((Control) this.t_Set5);
      this.groupBox10.Controls.Add((Control) this.label34);
      this.groupBox10.Controls.Add((Control) this.t_Set4);
      this.groupBox10.Controls.Add((Control) this.label30);
      this.groupBox10.Controls.Add((Control) this.t_Set3);
      this.groupBox10.Controls.Add((Control) this.label31);
      this.groupBox10.Controls.Add((Control) this.t_Set2);
      this.groupBox10.Controls.Add((Control) this.label32);
      this.groupBox10.Controls.Add((Control) this.t_Set1);
      this.groupBox10.Controls.Add((Control) this.label33);
      this.groupBox10.Location = new Point(124, 279);
      this.groupBox10.Name = "groupBox10";
      this.groupBox10.Size = new Size(71, 135);
      this.groupBox10.TabIndex = 12;
      this.groupBox10.TabStop = false;
      this.groupBox10.Text = "Rand, S,";
      this.t_Set5.BorderStyle = BorderStyle.FixedSingle;
      this.t_Set5.Location = new Point(18, 107);
      this.t_Set5.Name = "t_Set5";
      this.t_Set5.Size = new Size(44, 20);
      this.t_Set5.TabIndex = 13;
      this.t_Set5.TextChanged += new EventHandler(this.ValueChanged);
      this.label34.AutoSize = true;
      this.label34.Location = new Point(2, 109);
      this.label34.Name = "label34";
      this.label34.Size = new Size(13, 13);
      this.label34.TabIndex = 12;
      this.label34.Text = "5";
      this.t_Set4.BorderStyle = BorderStyle.FixedSingle;
      this.t_Set4.Location = new Point(18, 84);
      this.t_Set4.Name = "t_Set4";
      this.t_Set4.Size = new Size(44, 20);
      this.t_Set4.TabIndex = 11;
      this.t_Set4.TextChanged += new EventHandler(this.ValueChanged);
      this.label30.AutoSize = true;
      this.label30.Location = new Point(2, 86);
      this.label30.Name = "label30";
      this.label30.Size = new Size(13, 13);
      this.label30.TabIndex = 10;
      this.label30.Text = "4";
      this.t_Set3.BorderStyle = BorderStyle.FixedSingle;
      this.t_Set3.Location = new Point(18, 61);
      this.t_Set3.Name = "t_Set3";
      this.t_Set3.Size = new Size(44, 20);
      this.t_Set3.TabIndex = 9;
      this.t_Set3.TextChanged += new EventHandler(this.ValueChanged);
      this.label31.AutoSize = true;
      this.label31.Location = new Point(2, 63);
      this.label31.Name = "label31";
      this.label31.Size = new Size(13, 13);
      this.label31.TabIndex = 8;
      this.label31.Text = "3";
      this.t_Set2.BorderStyle = BorderStyle.FixedSingle;
      this.t_Set2.Location = new Point(18, 38);
      this.t_Set2.Name = "t_Set2";
      this.t_Set2.Size = new Size(44, 20);
      this.t_Set2.TabIndex = 7;
      this.t_Set2.TextChanged += new EventHandler(this.ValueChanged);
      this.label32.AutoSize = true;
      this.label32.Location = new Point(2, 40);
      this.label32.Name = "label32";
      this.label32.Size = new Size(13, 13);
      this.label32.TabIndex = 6;
      this.label32.Text = "2";
      this.t_Set1.BorderStyle = BorderStyle.FixedSingle;
      this.t_Set1.Location = new Point(18, 15);
      this.t_Set1.Name = "t_Set1";
      this.t_Set1.Size = new Size(44, 20);
      this.t_Set1.TabIndex = 5;
      this.t_Set1.TextChanged += new EventHandler(this.ValueChanged);
      this.label33.AutoSize = true;
      this.label33.Location = new Point(2, 17);
      this.label33.Name = "label33";
      this.label33.Size = new Size(13, 13);
      this.label33.TabIndex = 4;
      this.label33.Text = "1";
      this.groupBox5.Controls.Add((Control) this.t_Level2);
      this.groupBox5.Controls.Add((Control) this.label14);
      this.groupBox5.Controls.Add((Control) this.button4);
      this.groupBox5.Controls.Add((Control) this.button3);
      this.groupBox5.Controls.Add((Control) this.t_Price);
      this.groupBox5.Controls.Add((Control) this.t_Weight);
      this.groupBox5.Controls.Add((Control) this.t_Level);
      this.groupBox5.Controls.Add((Control) this.label11);
      this.groupBox5.Location = new Point(6, 273);
      this.groupBox5.Name = "groupBox5";
      this.groupBox5.Size = new Size(112, 125);
      this.groupBox5.TabIndex = 3;
      this.groupBox5.TabStop = false;
      this.groupBox5.Text = "Stats";
      this.t_Level2.BorderStyle = BorderStyle.FixedSingle;
      this.t_Level2.Location = new Point(47, 41);
      this.t_Level2.Name = "t_Level2";
      this.t_Level2.Size = new Size(49, 20);
      this.t_Level2.TabIndex = 20;
      this.label14.AutoSize = true;
      this.label14.Location = new Point(1, 43);
      this.label14.Name = "label14";
      this.label14.Size = new Size(42, 13);
      this.label14.TabIndex = 19;
      this.label14.Text = "Level 2";
      this.button4.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.gold1;
      this.button4.BackgroundImageLayout = ImageLayout.Stretch;
      this.button4.FlatAppearance.BorderSize = 0;
      this.button4.FlatStyle = FlatStyle.Flat;
      this.button4.Location = new Point(23, 92);
      this.button4.Name = "button4";
      this.button4.Size = new Size(20, 20);
      this.button4.TabIndex = 18;
      this.button4.UseVisualStyleBackColor = true;
      this.button3.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.depositphotos_17405057_stock_illustration_scales_of_justice;
      this.button3.BackgroundImageLayout = ImageLayout.Stretch;
      this.button3.FlatAppearance.BorderSize = 0;
      this.button3.FlatStyle = FlatStyle.Flat;
      this.button3.Location = new Point(21, 65);
      this.button3.Name = "button3";
      this.button3.Size = new Size(20, 20);
      this.button3.TabIndex = 17;
      this.button3.UseVisualStyleBackColor = true;
      this.t_Price.BorderStyle = BorderStyle.FixedSingle;
      this.t_Price.Location = new Point(47, 92);
      this.t_Price.Name = "t_Price";
      this.t_Price.Size = new Size(49, 20);
      this.t_Price.TabIndex = 9;
      this.t_Price.TextChanged += new EventHandler(this.ValueChanged);
      this.t_Weight.BorderStyle = BorderStyle.FixedSingle;
      this.t_Weight.Location = new Point(47, 67);
      this.t_Weight.Name = "t_Weight";
      this.t_Weight.Size = new Size(49, 20);
      this.t_Weight.TabIndex = 7;
      this.t_Weight.TextChanged += new EventHandler(this.ValueChanged);
      this.t_Level.BorderStyle = BorderStyle.FixedSingle;
      this.t_Level.Location = new Point(47, 14);
      this.t_Level.Name = "t_Level";
      this.t_Level.Size = new Size(49, 20);
      this.t_Level.TabIndex = 5;
      this.t_Level.TextChanged += new EventHandler(this.ValueChanged);
      this.label11.AutoSize = true;
      this.label11.Location = new Point(1, 16);
      this.label11.Name = "label11";
      this.label11.Size = new Size(33, 13);
      this.label11.TabIndex = 4;
      this.label11.Text = "Level";
      this.groupBox8.Controls.Add((Control) this.t_RareOptionRate);
      this.groupBox8.Controls.Add((Control) this.label24);
      this.groupBox8.Controls.Add((Control) this.t_RareOptionID);
      this.groupBox8.Controls.Add((Control) this.label25);
      this.groupBox8.Location = new Point(6, 399);
      this.groupBox8.Name = "groupBox8";
      this.groupBox8.Size = new Size(71, 71);
      this.groupBox8.TabIndex = 10;
      this.groupBox8.TabStop = false;
      this.groupBox8.Text = "RareOpt";
      this.t_RareOptionRate.BorderStyle = BorderStyle.FixedSingle;
      this.t_RareOptionRate.Location = new Point(29, 45);
      this.t_RareOptionRate.Name = "t_RareOptionRate";
      this.t_RareOptionRate.Size = new Size(33, 20);
      this.t_RareOptionRate.TabIndex = 7;
      this.label24.AutoSize = true;
      this.label24.Location = new Point(1, 47);
      this.label24.Name = "label24";
      this.label24.Size = new Size(30, 13);
      this.label24.TabIndex = 6;
      this.label24.Text = "Rate";
      this.t_RareOptionID.BorderStyle = BorderStyle.FixedSingle;
      this.t_RareOptionID.Location = new Point(29, 19);
      this.t_RareOptionID.Name = "t_RareOptionID";
      this.t_RareOptionID.Size = new Size(33, 20);
      this.t_RareOptionID.TabIndex = 5;
      this.label25.AutoSize = true;
      this.label25.Location = new Point(1, 21);
      this.label25.Name = "label25";
      this.label25.Size = new Size(18, 13);
      this.label25.TabIndex = 4;
      this.label25.Text = "ID";
      this.groupBox7.Controls.Add((Control) this.panel2);
      this.groupBox7.Controls.Add((Control) this.t_maxuse);
      this.groupBox7.Controls.Add((Control) this.label76);
      this.groupBox7.Controls.Add((Control) this.button1);
      this.groupBox7.Controls.Add((Control) this.t_Flag);
      this.groupBox7.Controls.Add((Control) this.label22);
      this.groupBox7.Controls.Add((Control) this.t_WearingPosCombo);
      this.groupBox7.Controls.Add((Control) this.t_WearingPos);
      this.groupBox7.Controls.Add((Control) this.label21);
      this.groupBox7.Controls.Add((Control) this.t_Class);
      this.groupBox7.Controls.Add((Control) this.label20);
      this.groupBox7.Controls.Add((Control) this.t_SubTypeCombo);
      this.groupBox7.Controls.Add((Control) this.t_SubType);
      this.groupBox7.Controls.Add((Control) this.label19);
      this.groupBox7.Controls.Add((Control) this.t_TypeCombo);
      this.groupBox7.Controls.Add((Control) this.t_Type);
      this.groupBox7.Controls.Add((Control) this.label18);
      this.groupBox7.Location = new Point(344, 8);
      this.groupBox7.Name = "groupBox7";
      this.groupBox7.Size = new Size(406, 164);
      this.groupBox7.TabIndex = 11;
      this.groupBox7.TabStop = false;
      this.groupBox7.Text = "Catagorize";
      this.panel2.Controls.Add((Control) this.checkBox_class8);
      this.panel2.Controls.Add((Control) this.checkBox_class7);
      this.panel2.Controls.Add((Control) this.checkBox_class6);
      this.panel2.Controls.Add((Control) this.checkBox_class5);
      this.panel2.Controls.Add((Control) this.checkBox_class4);
      this.panel2.Controls.Add((Control) this.checkBox_class3);
      this.panel2.Controls.Add((Control) this.checkBox_class2);
      this.panel2.Controls.Add((Control) this.checkBox_class1);
      this.panel2.Controls.Add((Control) this.checkBox_class0);
      this.panel2.Location = new Point(68, 65);
      this.panel2.Name = "panel2";
      this.panel2.Size = new Size(290, 41);
      this.panel2.TabIndex = 46;
      this.checkBox_class8.AutoSize = true;
      this.checkBox_class8.Location = new Point(176, 21);
      this.checkBox_class8.Name = "checkBox_class8";
      this.checkBox_class8.Size = new Size(70, 17);
      this.checkBox_class8.TabIndex = 8;
      this.checkBox_class8.Text = "EX-Mage";
      this.checkBox_class8.UseVisualStyleBackColor = true;
      this.checkBox_class7.AutoSize = true;
      this.checkBox_class7.Location = new Point(101, 21);
      this.checkBox_class7.Name = "checkBox_class7";
      this.checkBox_class7.Size = new Size(75, 17);
      this.checkBox_class7.TabIndex = 7;
      this.checkBox_class7.Text = "EX-Rogue";
      this.checkBox_class7.UseVisualStyleBackColor = true;
      this.checkBox_class6.AutoSize = true;
      this.checkBox_class6.Location = new Point(48, 21);
      this.checkBox_class6.Name = "checkBox_class6";
      this.checkBox_class6.Size = new Size(41, 17);
      this.checkBox_class6.TabIndex = 6;
      this.checkBox_class6.Text = "NS";
      this.checkBox_class6.UseVisualStyleBackColor = true;
      this.checkBox_class5.AutoSize = true;
      this.checkBox_class5.Location = new Point(1, 21);
      this.checkBox_class5.Name = "checkBox_class5";
      this.checkBox_class5.Size = new Size(48, 17);
      this.checkBox_class5.TabIndex = 5;
      this.checkBox_class5.Text = "Sorc";
      this.checkBox_class5.UseVisualStyleBackColor = true;
      this.checkBox_class4.AutoSize = true;
      this.checkBox_class4.Location = new Point(207, 3);
      this.checkBox_class4.Name = "checkBox_class4";
      this.checkBox_class4.Size = new Size(58, 17);
      this.checkBox_class4.TabIndex = 4;
      this.checkBox_class4.Text = "Rogue";
      this.checkBox_class4.UseVisualStyleBackColor = true;
      this.checkBox_class3.AutoSize = true;
      this.checkBox_class3.Location = new Point(155, 3);
      this.checkBox_class3.Name = "checkBox_class3";
      this.checkBox_class3.Size = new Size(53, 17);
      this.checkBox_class3.TabIndex = 3;
      this.checkBox_class3.Text = "Mage";
      this.checkBox_class3.UseVisualStyleBackColor = true;
      this.checkBox_class2.AutoSize = true;
      this.checkBox_class2.Location = new Point(101, 3);
      this.checkBox_class2.Name = "checkBox_class2";
      this.checkBox_class2.Size = new Size(57, 17);
      this.checkBox_class2.TabIndex = 2;
      this.checkBox_class2.Text = "Healer";
      this.checkBox_class2.UseVisualStyleBackColor = true;
      this.checkBox_class1.AutoSize = true;
      this.checkBox_class1.Location = new Point(48, 3);
      this.checkBox_class1.Name = "checkBox_class1";
      this.checkBox_class1.Size = new Size(56, 17);
      this.checkBox_class1.TabIndex = 1;
      this.checkBox_class1.Text = "Knight";
      this.checkBox_class1.UseVisualStyleBackColor = true;
      this.checkBox_class0.AutoSize = true;
      this.checkBox_class0.Location = new Point(1, 3);
      this.checkBox_class0.Name = "checkBox_class0";
      this.checkBox_class0.Size = new Size(50, 17);
      this.checkBox_class0.TabIndex = 0;
      this.checkBox_class0.Text = "Titan";
      this.checkBox_class0.UseVisualStyleBackColor = true;
      this.t_maxuse.BorderStyle = BorderStyle.FixedSingle;
      this.t_maxuse.Location = new Point(275, 137);
      this.t_maxuse.Name = "t_maxuse";
      this.t_maxuse.Size = new Size(60, 20);
      this.t_maxuse.TabIndex = 18;
      this.t_maxuse.TextChanged += new EventHandler(this.ValueChanged);
      this.label76.AutoSize = true;
      this.label76.Location = new Point(220, 140);
      this.label76.Name = "label76";
      this.label76.Size = new Size(49, 13);
      this.label76.TabIndex = 17;
      this.label76.Text = "Max Use";
      this.button1.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.search;
      this.button1.BackgroundImageLayout = ImageLayout.Stretch;
      this.button1.FlatAppearance.BorderSize = 0;
      this.button1.FlatStyle = FlatStyle.Flat;
      this.button1.Location = new Point(183, 138);
      this.button1.Name = "button1";
      this.button1.Size = new Size(17, 17);
      this.button1.TabIndex = 16;
      this.button1.UseVisualStyleBackColor = true;
      this.t_Flag.BorderStyle = BorderStyle.FixedSingle;
      this.t_Flag.Location = new Point(91, 137);
      this.t_Flag.Name = "t_Flag";
      this.t_Flag.Size = new Size(89, 20);
      this.t_Flag.TabIndex = 15;
      this.t_Flag.TextChanged += new EventHandler(this.ValueChanged);
      this.label22.AutoSize = true;
      this.label22.Location = new Point(7, 139);
      this.label22.Name = "label22";
      this.label22.Size = new Size(27, 13);
      this.label22.TabIndex = 14;
      this.label22.Text = "Flag";
      this.t_WearingPosCombo.FormattingEnabled = true;
      this.t_WearingPosCombo.Items.AddRange(new object[13]
      {
        (object) "None",
        (object) "Hood Slot",
        (object) "Shirt Slot",
        (object) "Weapon Slot",
        (object) "Pants Slot",
        (object) "Shield Slot",
        (object) "Gloves Slot",
        (object) "Boots Slot",
        (object) "Accesoire Slot",
        (object) "Accesoire Slot",
        (object) "Accesoire Slot",
        (object) "Pet Slot",
        (object) "Wing Slot"
      });
      this.t_WearingPosCombo.Location = new Point(91, 112);
      this.t_WearingPosCombo.Name = "t_WearingPosCombo";
      this.t_WearingPosCombo.Size = new Size(207, 21);
      this.t_WearingPosCombo.TabIndex = 13;
      this.t_WearingPos.BorderStyle = BorderStyle.FixedSingle;
      this.t_WearingPos.Location = new Point(304, 113);
      this.t_WearingPos.Name = "t_WearingPos";
      this.t_WearingPos.Size = new Size(31, 20);
      this.t_WearingPos.TabIndex = 12;
      this.t_WearingPos.TextChanged += new EventHandler(this.t_WearingPos_TextChanged);
      this.label21.AutoSize = true;
      this.label21.Location = new Point(7, 115);
      this.label21.Name = "label21";
      this.label21.Size = new Size(68, 13);
      this.label21.TabIndex = 11;
      this.label21.Text = "Wearing Pos";
      this.t_Class.BorderStyle = BorderStyle.FixedSingle;
      this.t_Class.Location = new Point(367, 67);
      this.t_Class.Name = "t_Class";
      this.t_Class.Size = new Size(31, 20);
      this.t_Class.TabIndex = 9;
      this.t_Class.TextChanged += new EventHandler(this.t_Class_TextChanged);
      this.label20.AutoSize = true;
      this.label20.Location = new Point(7, 69);
      this.label20.Name = "label20";
      this.label20.Size = new Size(32, 13);
      this.label20.TabIndex = 8;
      this.label20.Text = "Class";
      this.t_SubTypeCombo.FormattingEnabled = true;
      this.t_SubTypeCombo.Items.AddRange(new object[3]
      {
        (object) "Item Name",
        (object) "Item Description",
        (object) "Flag"
      });
      this.t_SubTypeCombo.Location = new Point(142, 38);
      this.t_SubTypeCombo.Name = "t_SubTypeCombo";
      this.t_SubTypeCombo.Size = new Size(216, 21);
      this.t_SubTypeCombo.TabIndex = 7;
      this.t_SubTypeCombo.SelectedIndexChanged += new EventHandler(this.t_SubTypeCombo_SelectedIndexChanged);
      this.t_SubType.BorderStyle = BorderStyle.FixedSingle;
      this.t_SubType.Location = new Point(367, 41);
      this.t_SubType.Name = "t_SubType";
      this.t_SubType.Size = new Size(31, 20);
      this.t_SubType.TabIndex = 6;
      this.t_SubType.TextChanged += new EventHandler(this.t_SubType_TextChanged);
      this.label19.AutoSize = true;
      this.label19.Location = new Point(7, 44);
      this.label19.Name = "label19";
      this.label19.Size = new Size(53, 13);
      this.label19.TabIndex = 5;
      this.label19.Text = "Sub Type";
      this.t_TypeCombo.FormattingEnabled = true;
      this.t_TypeCombo.Items.AddRange(new object[7]
      {
        (object) "ITYPE_WEAPON",
        (object) "ITYPE_WEAR",
        (object) "ITYPE_ONCE",
        (object) "ITYPE_SHOT",
        (object) "ITYPE_ETC",
        (object) "ITYPE_ACCESSORY",
        (object) "ITYPE_POTION"
      });
      this.t_TypeCombo.Location = new Point(142, 14);
      this.t_TypeCombo.Name = "t_TypeCombo";
      this.t_TypeCombo.Size = new Size(216, 21);
      this.t_TypeCombo.TabIndex = 4;
      this.t_TypeCombo.SelectedIndexChanged += new EventHandler(this.t_TypeCombo_SelectedIndexChanged);
      this.t_Type.BorderStyle = BorderStyle.FixedSingle;
      this.t_Type.Location = new Point(367, 14);
      this.t_Type.Name = "t_Type";
      this.t_Type.Size = new Size(31, 20);
      this.t_Type.TabIndex = 3;
      this.t_Type.TextChanged += new EventHandler(this.t_Type_TextChanged);
      this.label18.AutoSize = true;
      this.label18.Location = new Point(7, 17);
      this.label18.Name = "label18";
      this.label18.Size = new Size(31, 13);
      this.label18.TabIndex = 2;
      this.label18.Text = "Type";
      this.tabPage4.BackColor = SystemColors.Control;
      this.tabPage4.BorderStyle = BorderStyle.FixedSingle;
      this.tabPage4.Controls.Add((Control) this.groupBox11);
      this.tabPage4.Controls.Add((Control) this.groupBox9);
      this.tabPage4.Location = new Point(4, 22);
      this.tabPage4.Name = "tabPage4";
      this.tabPage4.Padding = new Padding(3);
      this.tabPage4.Size = new Size(762, 492);
      this.tabPage4.TabIndex = 1;
      this.tabPage4.Text = "Crafting Data";
      this.groupBox11.Controls.Add((Control) this.tabControl1);
      this.groupBox11.Location = new Point(6, 92);
      this.groupBox11.Name = "groupBox11";
      this.groupBox11.Size = new Size(477, 263);
      this.groupBox11.TabIndex = 13;
      this.groupBox11.TabStop = false;
      this.groupBox11.Text = "Item Crafting Data";
      this.tabControl1.Appearance = TabAppearance.FlatButtons;
      this.tabControl1.Controls.Add((Control) this.tabPage1);
      this.tabControl1.Controls.Add((Control) this.tabPage2);
      this.tabControl1.Dock = DockStyle.Fill;
      this.tabControl1.Location = new Point(3, 16);
      this.tabControl1.Name = "tabControl1";
      this.tabControl1.SelectedIndex = 0;
      this.tabControl1.Size = new Size(471, 244);
      this.tabControl1.TabIndex = 0;
      this.tabPage1.Controls.Add((Control) this.CraftGrid);
      this.tabPage1.Location = new Point(4, 25);
      this.tabPage1.Name = "tabPage1";
      this.tabPage1.Padding = new Padding(3);
      this.tabPage1.Size = new Size(463, 215);
      this.tabPage1.TabIndex = 0;
      this.tabPage1.Text = "View";
      this.tabPage1.UseVisualStyleBackColor = true;
      this.CraftGrid.AllowUserToAddRows = false;
      this.CraftGrid.AllowUserToDeleteRows = false;
      this.CraftGrid.BackgroundColor = SystemColors.Control;
      this.CraftGrid.BorderStyle = BorderStyle.None;
      this.CraftGrid.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.CraftGrid.Columns.AddRange((DataGridViewColumn) this.ItemIcon, (DataGridViewColumn) this.ItemID, (DataGridViewColumn) this.ItemName, (DataGridViewColumn) this.Amount);
      this.CraftGrid.Dock = DockStyle.Fill;
      this.CraftGrid.EnableHeadersVisualStyles = false;
      this.CraftGrid.Location = new Point(3, 3);
      this.CraftGrid.MultiSelect = false;
      this.CraftGrid.Name = "CraftGrid";
      this.CraftGrid.ReadOnly = true;
      this.CraftGrid.RowHeadersVisible = false;
      this.CraftGrid.RowTemplate.Height = 34;
      this.CraftGrid.Size = new Size(457, 209);
      this.CraftGrid.TabIndex = 0;
      this.ItemIcon.HeaderText = "";
      this.ItemIcon.Name = "ItemIcon";
      this.ItemIcon.ReadOnly = true;
      this.ItemIcon.Width = 32;
      this.ItemID.HeaderText = "ID";
      this.ItemID.Name = "ItemID";
      this.ItemID.ReadOnly = true;
      this.ItemID.Width = 65;
      this.ItemName.HeaderText = "ItemName";
      this.ItemName.Name = "ItemName";
      this.ItemName.ReadOnly = true;
      this.ItemName.Resizable = DataGridViewTriState.True;
      this.ItemName.SortMode = DataGridViewColumnSortMode.NotSortable;
      this.ItemName.Width = 250;
      this.Amount.HeaderText = "Amount";
      this.Amount.Name = "Amount";
      this.Amount.ReadOnly = true;
      this.Amount.Width = 75;
      this.tabPage2.Controls.Add((Control) this.t_CraftItemSearch10);
      this.tabPage2.Controls.Add((Control) this.t_CraftItemAmount10);
      this.tabPage2.Controls.Add((Control) this.t_CraftItemID10);
      this.tabPage2.Controls.Add((Control) this.label45);
      this.tabPage2.Controls.Add((Control) this.label46);
      this.tabPage2.Controls.Add((Control) this.t_CraftItemAmount9);
      this.tabPage2.Controls.Add((Control) this.t_CraftItemID9);
      this.tabPage2.Controls.Add((Control) this.label47);
      this.tabPage2.Controls.Add((Control) this.label48);
      this.tabPage2.Controls.Add((Control) this.t_CraftItemAmount8);
      this.tabPage2.Controls.Add((Control) this.t_CraftItemID8);
      this.tabPage2.Controls.Add((Control) this.label49);
      this.tabPage2.Controls.Add((Control) this.label50);
      this.tabPage2.Controls.Add((Control) this.t_CraftItemAmount7);
      this.tabPage2.Controls.Add((Control) this.t_CraftItemID7);
      this.tabPage2.Controls.Add((Control) this.label51);
      this.tabPage2.Controls.Add((Control) this.label52);
      this.tabPage2.Controls.Add((Control) this.t_CraftItemAmount6);
      this.tabPage2.Controls.Add((Control) this.t_CraftItemID6);
      this.tabPage2.Controls.Add((Control) this.label53);
      this.tabPage2.Controls.Add((Control) this.label54);
      this.tabPage2.Controls.Add((Control) this.t_CraftItemAmount5);
      this.tabPage2.Controls.Add((Control) this.t_CraftItemID5);
      this.tabPage2.Controls.Add((Control) this.label43);
      this.tabPage2.Controls.Add((Control) this.label44);
      this.tabPage2.Controls.Add((Control) this.t_CraftItemAmount4);
      this.tabPage2.Controls.Add((Control) this.t_CraftItemID4);
      this.tabPage2.Controls.Add((Control) this.label41);
      this.tabPage2.Controls.Add((Control) this.label42);
      this.tabPage2.Controls.Add((Control) this.t_CraftItemAmount3);
      this.tabPage2.Controls.Add((Control) this.t_CraftItemID3);
      this.tabPage2.Controls.Add((Control) this.label39);
      this.tabPage2.Controls.Add((Control) this.label40);
      this.tabPage2.Controls.Add((Control) this.t_CraftItemAmount2);
      this.tabPage2.Controls.Add((Control) this.t_CraftItemID2);
      this.tabPage2.Controls.Add((Control) this.label37);
      this.tabPage2.Controls.Add((Control) this.label38);
      this.tabPage2.Controls.Add((Control) this.t_CraftItemAmount1);
      this.tabPage2.Controls.Add((Control) this.t_CraftItemID1);
      this.tabPage2.Controls.Add((Control) this.label35);
      this.tabPage2.Controls.Add((Control) this.label36);
      this.tabPage2.Controls.Add((Control) this.t_CraftItemSearch9);
      this.tabPage2.Controls.Add((Control) this.t_CraftItemSearch8);
      this.tabPage2.Controls.Add((Control) this.t_CraftItemSearch7);
      this.tabPage2.Controls.Add((Control) this.t_CraftItemSearch6);
      this.tabPage2.Controls.Add((Control) this.t_CraftItemSearch5);
      this.tabPage2.Controls.Add((Control) this.t_CraftItemSearch4);
      this.tabPage2.Controls.Add((Control) this.t_CraftItemSearch3);
      this.tabPage2.Controls.Add((Control) this.t_CraftItemSearch2);
      this.tabPage2.Controls.Add((Control) this.t_CraftItemSearch1);
      this.tabPage2.Location = new Point(4, 25);
      this.tabPage2.Name = "tabPage2";
      this.tabPage2.Padding = new Padding(3);
      this.tabPage2.Size = new Size(463, 215);
      this.tabPage2.TabIndex = 1;
      this.tabPage2.Text = "Edit";
      this.tabPage2.UseVisualStyleBackColor = true;
      this.t_CraftItemSearch10.BackgroundImageLayout = ImageLayout.None;
      this.t_CraftItemSearch10.FlatAppearance.BorderSize = 0;
      this.t_CraftItemSearch10.FlatStyle = FlatStyle.Flat;
      this.t_CraftItemSearch10.Location = new Point(341, 125);
      this.t_CraftItemSearch10.Name = "t_CraftItemSearch10";
      this.t_CraftItemSearch10.Size = new Size(19, 20);
      this.t_CraftItemSearch10.TabIndex = 61;
      this.t_CraftItemSearch10.UseVisualStyleBackColor = true;
      this.t_CraftItemAmount10.BorderStyle = BorderStyle.FixedSingle;
      this.t_CraftItemAmount10.Location = new Point(412, 124);
      this.t_CraftItemAmount10.Name = "t_CraftItemAmount10";
      this.t_CraftItemAmount10.Size = new Size(36, 20);
      this.t_CraftItemAmount10.TabIndex = 60;
      this.t_CraftItemID10.BackColor = SystemColors.Window;
      this.t_CraftItemID10.BorderStyle = BorderStyle.FixedSingle;
      this.t_CraftItemID10.Location = new Point(290, 124);
      this.t_CraftItemID10.Name = "t_CraftItemID10";
      this.t_CraftItemID10.ReadOnly = true;
      this.t_CraftItemID10.Size = new Size(42, 20);
      this.t_CraftItemID10.TabIndex = 58;
      this.label45.AutoSize = true;
      this.label45.Location = new Point(366, 126);
      this.label45.Name = "label45";
      this.label45.Size = new Size(43, 13);
      this.label45.TabIndex = 59;
      this.label45.Text = "Amount";
      this.label46.AutoSize = true;
      this.label46.Location = new Point(244, 126);
      this.label46.Name = "label46";
      this.label46.Size = new Size(41, 13);
      this.label46.TabIndex = 57;
      this.label46.Text = "Item ID";
      this.t_CraftItemAmount9.BorderStyle = BorderStyle.FixedSingle;
      this.t_CraftItemAmount9.Location = new Point(412, 98);
      this.t_CraftItemAmount9.Name = "t_CraftItemAmount9";
      this.t_CraftItemAmount9.Size = new Size(36, 20);
      this.t_CraftItemAmount9.TabIndex = 55;
      this.t_CraftItemID9.BackColor = SystemColors.Window;
      this.t_CraftItemID9.BorderStyle = BorderStyle.FixedSingle;
      this.t_CraftItemID9.Location = new Point(290, 98);
      this.t_CraftItemID9.Name = "t_CraftItemID9";
      this.t_CraftItemID9.ReadOnly = true;
      this.t_CraftItemID9.Size = new Size(42, 20);
      this.t_CraftItemID9.TabIndex = 53;
      this.label47.AutoSize = true;
      this.label47.Location = new Point(366, 100);
      this.label47.Name = "label47";
      this.label47.Size = new Size(43, 13);
      this.label47.TabIndex = 54;
      this.label47.Text = "Amount";
      this.label48.AutoSize = true;
      this.label48.Location = new Point(244, 100);
      this.label48.Name = "label48";
      this.label48.Size = new Size(41, 13);
      this.label48.TabIndex = 52;
      this.label48.Text = "Item ID";
      this.t_CraftItemAmount8.BorderStyle = BorderStyle.FixedSingle;
      this.t_CraftItemAmount8.Location = new Point(412, 72);
      this.t_CraftItemAmount8.Name = "t_CraftItemAmount8";
      this.t_CraftItemAmount8.Size = new Size(36, 20);
      this.t_CraftItemAmount8.TabIndex = 50;
      this.t_CraftItemID8.BackColor = SystemColors.Window;
      this.t_CraftItemID8.BorderStyle = BorderStyle.FixedSingle;
      this.t_CraftItemID8.Location = new Point(290, 72);
      this.t_CraftItemID8.Name = "t_CraftItemID8";
      this.t_CraftItemID8.ReadOnly = true;
      this.t_CraftItemID8.Size = new Size(42, 20);
      this.t_CraftItemID8.TabIndex = 48;
      this.label49.AutoSize = true;
      this.label49.Location = new Point(366, 74);
      this.label49.Name = "label49";
      this.label49.Size = new Size(43, 13);
      this.label49.TabIndex = 49;
      this.label49.Text = "Amount";
      this.label50.AutoSize = true;
      this.label50.Location = new Point(244, 74);
      this.label50.Name = "label50";
      this.label50.Size = new Size(41, 13);
      this.label50.TabIndex = 47;
      this.label50.Text = "Item ID";
      this.t_CraftItemAmount7.BorderStyle = BorderStyle.FixedSingle;
      this.t_CraftItemAmount7.Location = new Point(412, 46);
      this.t_CraftItemAmount7.Name = "t_CraftItemAmount7";
      this.t_CraftItemAmount7.Size = new Size(36, 20);
      this.t_CraftItemAmount7.TabIndex = 45;
      this.t_CraftItemID7.BackColor = SystemColors.Window;
      this.t_CraftItemID7.BorderStyle = BorderStyle.FixedSingle;
      this.t_CraftItemID7.Location = new Point(290, 46);
      this.t_CraftItemID7.Name = "t_CraftItemID7";
      this.t_CraftItemID7.ReadOnly = true;
      this.t_CraftItemID7.Size = new Size(42, 20);
      this.t_CraftItemID7.TabIndex = 43;
      this.label51.AutoSize = true;
      this.label51.Location = new Point(366, 48);
      this.label51.Name = "label51";
      this.label51.Size = new Size(43, 13);
      this.label51.TabIndex = 44;
      this.label51.Text = "Amount";
      this.label52.AutoSize = true;
      this.label52.Location = new Point(244, 48);
      this.label52.Name = "label52";
      this.label52.Size = new Size(41, 13);
      this.label52.TabIndex = 42;
      this.label52.Text = "Item ID";
      this.t_CraftItemAmount6.BorderStyle = BorderStyle.FixedSingle;
      this.t_CraftItemAmount6.Location = new Point(412, 20);
      this.t_CraftItemAmount6.Name = "t_CraftItemAmount6";
      this.t_CraftItemAmount6.Size = new Size(36, 20);
      this.t_CraftItemAmount6.TabIndex = 40;
      this.t_CraftItemID6.BackColor = SystemColors.Window;
      this.t_CraftItemID6.BorderStyle = BorderStyle.FixedSingle;
      this.t_CraftItemID6.Location = new Point(290, 20);
      this.t_CraftItemID6.Name = "t_CraftItemID6";
      this.t_CraftItemID6.ReadOnly = true;
      this.t_CraftItemID6.Size = new Size(42, 20);
      this.t_CraftItemID6.TabIndex = 38;
      this.label53.AutoSize = true;
      this.label53.Location = new Point(366, 22);
      this.label53.Name = "label53";
      this.label53.Size = new Size(43, 13);
      this.label53.TabIndex = 39;
      this.label53.Text = "Amount";
      this.label54.AutoSize = true;
      this.label54.Location = new Point(244, 22);
      this.label54.Name = "label54";
      this.label54.Size = new Size(41, 13);
      this.label54.TabIndex = 37;
      this.label54.Text = "Item ID";
      this.t_CraftItemAmount5.BorderStyle = BorderStyle.FixedSingle;
      this.t_CraftItemAmount5.Location = new Point(174, 121);
      this.t_CraftItemAmount5.Name = "t_CraftItemAmount5";
      this.t_CraftItemAmount5.Size = new Size(36, 20);
      this.t_CraftItemAmount5.TabIndex = 35;
      this.t_CraftItemID5.BackColor = SystemColors.Window;
      this.t_CraftItemID5.BorderStyle = BorderStyle.FixedSingle;
      this.t_CraftItemID5.Location = new Point(52, 121);
      this.t_CraftItemID5.Name = "t_CraftItemID5";
      this.t_CraftItemID5.ReadOnly = true;
      this.t_CraftItemID5.Size = new Size(42, 20);
      this.t_CraftItemID5.TabIndex = 33;
      this.label43.AutoSize = true;
      this.label43.Location = new Point(128, 123);
      this.label43.Name = "label43";
      this.label43.Size = new Size(43, 13);
      this.label43.TabIndex = 34;
      this.label43.Text = "Amount";
      this.label44.AutoSize = true;
      this.label44.Location = new Point(6, 123);
      this.label44.Name = "label44";
      this.label44.Size = new Size(41, 13);
      this.label44.TabIndex = 32;
      this.label44.Text = "Item ID";
      this.t_CraftItemAmount4.BorderStyle = BorderStyle.FixedSingle;
      this.t_CraftItemAmount4.Location = new Point(174, 95);
      this.t_CraftItemAmount4.Name = "t_CraftItemAmount4";
      this.t_CraftItemAmount4.Size = new Size(36, 20);
      this.t_CraftItemAmount4.TabIndex = 30;
      this.t_CraftItemID4.BackColor = SystemColors.Window;
      this.t_CraftItemID4.BorderStyle = BorderStyle.FixedSingle;
      this.t_CraftItemID4.Location = new Point(52, 95);
      this.t_CraftItemID4.Name = "t_CraftItemID4";
      this.t_CraftItemID4.ReadOnly = true;
      this.t_CraftItemID4.Size = new Size(42, 20);
      this.t_CraftItemID4.TabIndex = 28;
      this.label41.AutoSize = true;
      this.label41.Location = new Point(128, 97);
      this.label41.Name = "label41";
      this.label41.Size = new Size(43, 13);
      this.label41.TabIndex = 29;
      this.label41.Text = "Amount";
      this.label42.AutoSize = true;
      this.label42.Location = new Point(6, 97);
      this.label42.Name = "label42";
      this.label42.Size = new Size(41, 13);
      this.label42.TabIndex = 27;
      this.label42.Text = "Item ID";
      this.t_CraftItemAmount3.BorderStyle = BorderStyle.FixedSingle;
      this.t_CraftItemAmount3.Location = new Point(174, 69);
      this.t_CraftItemAmount3.Name = "t_CraftItemAmount3";
      this.t_CraftItemAmount3.Size = new Size(36, 20);
      this.t_CraftItemAmount3.TabIndex = 25;
      this.t_CraftItemID3.BackColor = SystemColors.Window;
      this.t_CraftItemID3.BorderStyle = BorderStyle.FixedSingle;
      this.t_CraftItemID3.Location = new Point(52, 69);
      this.t_CraftItemID3.Name = "t_CraftItemID3";
      this.t_CraftItemID3.ReadOnly = true;
      this.t_CraftItemID3.Size = new Size(42, 20);
      this.t_CraftItemID3.TabIndex = 23;
      this.label39.AutoSize = true;
      this.label39.Location = new Point(128, 71);
      this.label39.Name = "label39";
      this.label39.Size = new Size(43, 13);
      this.label39.TabIndex = 24;
      this.label39.Text = "Amount";
      this.label40.AutoSize = true;
      this.label40.Location = new Point(6, 71);
      this.label40.Name = "label40";
      this.label40.Size = new Size(41, 13);
      this.label40.TabIndex = 22;
      this.label40.Text = "Item ID";
      this.t_CraftItemAmount2.BorderStyle = BorderStyle.FixedSingle;
      this.t_CraftItemAmount2.Location = new Point(174, 43);
      this.t_CraftItemAmount2.Name = "t_CraftItemAmount2";
      this.t_CraftItemAmount2.Size = new Size(36, 20);
      this.t_CraftItemAmount2.TabIndex = 20;
      this.t_CraftItemID2.BackColor = SystemColors.Window;
      this.t_CraftItemID2.BorderStyle = BorderStyle.FixedSingle;
      this.t_CraftItemID2.Location = new Point(52, 43);
      this.t_CraftItemID2.Name = "t_CraftItemID2";
      this.t_CraftItemID2.ReadOnly = true;
      this.t_CraftItemID2.Size = new Size(42, 20);
      this.t_CraftItemID2.TabIndex = 18;
      this.label37.AutoSize = true;
      this.label37.Location = new Point(128, 45);
      this.label37.Name = "label37";
      this.label37.Size = new Size(43, 13);
      this.label37.TabIndex = 19;
      this.label37.Text = "Amount";
      this.label38.AutoSize = true;
      this.label38.Location = new Point(6, 45);
      this.label38.Name = "label38";
      this.label38.Size = new Size(41, 13);
      this.label38.TabIndex = 17;
      this.label38.Text = "Item ID";
      this.t_CraftItemAmount1.BorderStyle = BorderStyle.FixedSingle;
      this.t_CraftItemAmount1.Location = new Point(174, 17);
      this.t_CraftItemAmount1.Name = "t_CraftItemAmount1";
      this.t_CraftItemAmount1.Size = new Size(36, 20);
      this.t_CraftItemAmount1.TabIndex = 15;
      this.t_CraftItemID1.BackColor = SystemColors.Window;
      this.t_CraftItemID1.BorderStyle = BorderStyle.FixedSingle;
      this.t_CraftItemID1.Location = new Point(52, 17);
      this.t_CraftItemID1.Name = "t_CraftItemID1";
      this.t_CraftItemID1.ReadOnly = true;
      this.t_CraftItemID1.Size = new Size(42, 20);
      this.t_CraftItemID1.TabIndex = 13;
      this.label35.AutoSize = true;
      this.label35.Location = new Point(128, 19);
      this.label35.Name = "label35";
      this.label35.Size = new Size(43, 13);
      this.label35.TabIndex = 14;
      this.label35.Text = "Amount";
      this.label36.AutoSize = true;
      this.label36.Location = new Point(6, 19);
      this.label36.Name = "label36";
      this.label36.Size = new Size(41, 13);
      this.label36.TabIndex = 12;
      this.label36.Text = "Item ID";
      this.t_CraftItemSearch9.BackgroundImageLayout = ImageLayout.None;
      this.t_CraftItemSearch9.FlatAppearance.BorderSize = 0;
      this.t_CraftItemSearch9.FlatStyle = FlatStyle.Flat;
      this.t_CraftItemSearch9.Location = new Point(341, 99);
      this.t_CraftItemSearch9.Name = "t_CraftItemSearch9";
      this.t_CraftItemSearch9.Size = new Size(19, 20);
      this.t_CraftItemSearch9.TabIndex = 56;
      this.t_CraftItemSearch9.UseVisualStyleBackColor = true;
      this.t_CraftItemSearch8.BackgroundImageLayout = ImageLayout.None;
      this.t_CraftItemSearch8.FlatAppearance.BorderSize = 0;
      this.t_CraftItemSearch8.FlatStyle = FlatStyle.Flat;
      this.t_CraftItemSearch8.Location = new Point(341, 73);
      this.t_CraftItemSearch8.Name = "t_CraftItemSearch8";
      this.t_CraftItemSearch8.Size = new Size(19, 20);
      this.t_CraftItemSearch8.TabIndex = 51;
      this.t_CraftItemSearch8.UseVisualStyleBackColor = true;
      this.t_CraftItemSearch7.BackgroundImageLayout = ImageLayout.None;
      this.t_CraftItemSearch7.FlatAppearance.BorderSize = 0;
      this.t_CraftItemSearch7.FlatStyle = FlatStyle.Flat;
      this.t_CraftItemSearch7.Location = new Point(341, 47);
      this.t_CraftItemSearch7.Name = "t_CraftItemSearch7";
      this.t_CraftItemSearch7.Size = new Size(19, 20);
      this.t_CraftItemSearch7.TabIndex = 46;
      this.t_CraftItemSearch7.UseVisualStyleBackColor = true;
      this.t_CraftItemSearch6.BackgroundImageLayout = ImageLayout.None;
      this.t_CraftItemSearch6.FlatAppearance.BorderSize = 0;
      this.t_CraftItemSearch6.FlatStyle = FlatStyle.Flat;
      this.t_CraftItemSearch6.Location = new Point(341, 21);
      this.t_CraftItemSearch6.Name = "t_CraftItemSearch6";
      this.t_CraftItemSearch6.Size = new Size(19, 20);
      this.t_CraftItemSearch6.TabIndex = 41;
      this.t_CraftItemSearch6.UseVisualStyleBackColor = true;
      this.t_CraftItemSearch5.BackgroundImageLayout = ImageLayout.None;
      this.t_CraftItemSearch5.FlatAppearance.BorderSize = 0;
      this.t_CraftItemSearch5.FlatStyle = FlatStyle.Flat;
      this.t_CraftItemSearch5.Location = new Point(103, 122);
      this.t_CraftItemSearch5.Name = "t_CraftItemSearch5";
      this.t_CraftItemSearch5.Size = new Size(19, 20);
      this.t_CraftItemSearch5.TabIndex = 36;
      this.t_CraftItemSearch5.UseVisualStyleBackColor = true;
      this.t_CraftItemSearch4.BackgroundImageLayout = ImageLayout.None;
      this.t_CraftItemSearch4.FlatAppearance.BorderSize = 0;
      this.t_CraftItemSearch4.FlatStyle = FlatStyle.Flat;
      this.t_CraftItemSearch4.Location = new Point(103, 96);
      this.t_CraftItemSearch4.Name = "t_CraftItemSearch4";
      this.t_CraftItemSearch4.Size = new Size(19, 20);
      this.t_CraftItemSearch4.TabIndex = 31;
      this.t_CraftItemSearch4.UseVisualStyleBackColor = true;
      this.t_CraftItemSearch3.BackgroundImageLayout = ImageLayout.None;
      this.t_CraftItemSearch3.FlatAppearance.BorderSize = 0;
      this.t_CraftItemSearch3.FlatStyle = FlatStyle.Flat;
      this.t_CraftItemSearch3.Location = new Point(103, 70);
      this.t_CraftItemSearch3.Name = "t_CraftItemSearch3";
      this.t_CraftItemSearch3.Size = new Size(19, 20);
      this.t_CraftItemSearch3.TabIndex = 26;
      this.t_CraftItemSearch3.UseVisualStyleBackColor = true;
      this.t_CraftItemSearch2.BackgroundImageLayout = ImageLayout.None;
      this.t_CraftItemSearch2.FlatAppearance.BorderSize = 0;
      this.t_CraftItemSearch2.FlatStyle = FlatStyle.Flat;
      this.t_CraftItemSearch2.Location = new Point(103, 44);
      this.t_CraftItemSearch2.Name = "t_CraftItemSearch2";
      this.t_CraftItemSearch2.Size = new Size(19, 20);
      this.t_CraftItemSearch2.TabIndex = 21;
      this.t_CraftItemSearch2.UseVisualStyleBackColor = true;
      this.t_CraftItemSearch1.BackgroundImageLayout = ImageLayout.None;
      this.t_CraftItemSearch1.FlatAppearance.BorderSize = 0;
      this.t_CraftItemSearch1.FlatStyle = FlatStyle.Flat;
      this.t_CraftItemSearch1.Location = new Point(103, 18);
      this.t_CraftItemSearch1.Name = "t_CraftItemSearch1";
      this.t_CraftItemSearch1.Size = new Size(19, 20);
      this.t_CraftItemSearch1.TabIndex = 16;
      this.t_CraftItemSearch1.UseVisualStyleBackColor = true;
      this.groupBox9.Controls.Add((Control) this.t_CraftSkill2Level);
      this.groupBox9.Controls.Add((Control) this.label27);
      this.groupBox9.Controls.Add((Control) this.t_CraftSkill1Level);
      this.groupBox9.Controls.Add((Control) this.label28);
      this.groupBox9.Controls.Add((Control) this.t_CraftSkill2ID);
      this.groupBox9.Controls.Add((Control) this.label23);
      this.groupBox9.Controls.Add((Control) this.t_CraftSkill1ID);
      this.groupBox9.Controls.Add((Control) this.label26);
      this.groupBox9.Location = new Point(6, 6);
      this.groupBox9.Name = "groupBox9";
      this.groupBox9.Size = new Size(260, 80);
      this.groupBox9.TabIndex = 11;
      this.groupBox9.TabStop = false;
      this.groupBox9.Text = "Craft Skill Requirements";
      this.t_CraftSkill2Level.BorderStyle = BorderStyle.FixedSingle;
      this.t_CraftSkill2Level.Location = new Point(173, 45);
      this.t_CraftSkill2Level.Name = "t_CraftSkill2Level";
      this.t_CraftSkill2Level.Size = new Size(60, 20);
      this.t_CraftSkill2Level.TabIndex = 11;
      this.label27.AutoSize = true;
      this.label27.Location = new Point((int) sbyte.MaxValue, 47);
      this.label27.Name = "label27";
      this.label27.Size = new Size(33, 13);
      this.label27.TabIndex = 10;
      this.label27.Text = "Level";
      this.t_CraftSkill1Level.BorderStyle = BorderStyle.FixedSingle;
      this.t_CraftSkill1Level.Location = new Point(173, 19);
      this.t_CraftSkill1Level.Name = "t_CraftSkill1Level";
      this.t_CraftSkill1Level.Size = new Size(60, 20);
      this.t_CraftSkill1Level.TabIndex = 9;
      this.label28.AutoSize = true;
      this.label28.Location = new Point((int) sbyte.MaxValue, 21);
      this.label28.Name = "label28";
      this.label28.Size = new Size(33, 13);
      this.label28.TabIndex = 8;
      this.label28.Text = "Level";
      this.t_CraftSkill2ID.BorderStyle = BorderStyle.FixedSingle;
      this.t_CraftSkill2ID.Location = new Point(59, 45);
      this.t_CraftSkill2ID.Name = "t_CraftSkill2ID";
      this.t_CraftSkill2ID.Size = new Size(60, 20);
      this.t_CraftSkill2ID.TabIndex = 7;
      this.label23.AutoSize = true;
      this.label23.Location = new Point(13, 47);
      this.label23.Name = "label23";
      this.label23.Size = new Size(40, 13);
      this.label23.TabIndex = 6;
      this.label23.Text = "Skill ID";
      this.t_CraftSkill1ID.BorderStyle = BorderStyle.FixedSingle;
      this.t_CraftSkill1ID.Location = new Point(59, 19);
      this.t_CraftSkill1ID.Name = "t_CraftSkill1ID";
      this.t_CraftSkill1ID.Size = new Size(60, 20);
      this.t_CraftSkill1ID.TabIndex = 5;
      this.label26.AutoSize = true;
      this.label26.Location = new Point(13, 21);
      this.label26.Name = "label26";
      this.label26.Size = new Size(40, 13);
      this.label26.TabIndex = 4;
      this.label26.Text = "Skill ID";
      this.tabPage5.BackColor = SystemColors.Control;
      this.tabPage5.BorderStyle = BorderStyle.FixedSingle;
      this.tabPage5.Controls.Add((Control) this.groupBox12);
      this.tabPage5.Controls.Add((Control) this.panel3);
      this.tabPage5.Location = new Point(4, 22);
      this.tabPage5.Name = "tabPage5";
      this.tabPage5.Size = new Size(762, 492);
      this.tabPage5.TabIndex = 2;
      this.tabPage5.Text = "Rare Option";
      this.groupBox12.Controls.Add((Control) this.btnRareSearch9);
      this.groupBox12.Controls.Add((Control) this.tbRareOpt9);
      this.groupBox12.Controls.Add((Control) this.tbRareChance9);
      this.groupBox12.Controls.Add((Control) this.label66);
      this.groupBox12.Controls.Add((Control) this.label67);
      this.groupBox12.Controls.Add((Control) this.btnRareSearch8);
      this.groupBox12.Controls.Add((Control) this.tbRareOpt8);
      this.groupBox12.Controls.Add((Control) this.tbRareChance8);
      this.groupBox12.Controls.Add((Control) this.label68);
      this.groupBox12.Controls.Add((Control) this.label69);
      this.groupBox12.Controls.Add((Control) this.btnRareSearch7);
      this.groupBox12.Controls.Add((Control) this.tbRareOpt7);
      this.groupBox12.Controls.Add((Control) this.tbRareChance7);
      this.groupBox12.Controls.Add((Control) this.label70);
      this.groupBox12.Controls.Add((Control) this.label71);
      this.groupBox12.Controls.Add((Control) this.btnRareSearch6);
      this.groupBox12.Controls.Add((Control) this.tbRareOpt6);
      this.groupBox12.Controls.Add((Control) this.tbRareChance6);
      this.groupBox12.Controls.Add((Control) this.label72);
      this.groupBox12.Controls.Add((Control) this.label73);
      this.groupBox12.Controls.Add((Control) this.btnRareSearch5);
      this.groupBox12.Controls.Add((Control) this.tbRareOpt5);
      this.groupBox12.Controls.Add((Control) this.tbRareChance5);
      this.groupBox12.Controls.Add((Control) this.label74);
      this.groupBox12.Controls.Add((Control) this.label75);
      this.groupBox12.Controls.Add((Control) this.btnRareSearch4);
      this.groupBox12.Controls.Add((Control) this.tbRareOpt4);
      this.groupBox12.Controls.Add((Control) this.tbRareChance4);
      this.groupBox12.Controls.Add((Control) this.label64);
      this.groupBox12.Controls.Add((Control) this.label65);
      this.groupBox12.Controls.Add((Control) this.btnRareSearch3);
      this.groupBox12.Controls.Add((Control) this.tbRareOpt3);
      this.groupBox12.Controls.Add((Control) this.tbRareChance3);
      this.groupBox12.Controls.Add((Control) this.label62);
      this.groupBox12.Controls.Add((Control) this.label63);
      this.groupBox12.Controls.Add((Control) this.btnRareSearch2);
      this.groupBox12.Controls.Add((Control) this.tbRareOpt2);
      this.groupBox12.Controls.Add((Control) this.tbRareChance2);
      this.groupBox12.Controls.Add((Control) this.label60);
      this.groupBox12.Controls.Add((Control) this.label61);
      this.groupBox12.Controls.Add((Control) this.btnRareSearch1);
      this.groupBox12.Controls.Add((Control) this.tbRareOpt1);
      this.groupBox12.Controls.Add((Control) this.tbRareChance1);
      this.groupBox12.Controls.Add((Control) this.label58);
      this.groupBox12.Controls.Add((Control) this.label59);
      this.groupBox12.Controls.Add((Control) this.btnRareSearch0);
      this.groupBox12.Controls.Add((Control) this.tbRareOpt0);
      this.groupBox12.Controls.Add((Control) this.tbRareChance0);
      this.groupBox12.Controls.Add((Control) this.label57);
      this.groupBox12.Controls.Add((Control) this.label56);
      this.groupBox12.Location = new Point(6, 38);
      this.groupBox12.Name = "groupBox12";
      this.groupBox12.Size = new Size(317, 328);
      this.groupBox12.TabIndex = 12;
      this.groupBox12.TabStop = false;
      this.groupBox12.Text = "Rare Options";
      this.btnRareSearch9.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.oie_transparent;
      this.btnRareSearch9.BackgroundImageLayout = ImageLayout.Stretch;
      this.btnRareSearch9.FlatAppearance.BorderSize = 0;
      this.btnRareSearch9.FlatStyle = FlatStyle.Flat;
      this.btnRareSearch9.Location = new Point(134, 273);
      this.btnRareSearch9.Name = "btnRareSearch9";
      this.btnRareSearch9.Size = new Size(19, 20);
      this.btnRareSearch9.TabIndex = 62;
      this.btnRareSearch9.UseVisualStyleBackColor = true;
      this.tbRareOpt9.BorderStyle = BorderStyle.FixedSingle;
      this.tbRareOpt9.Location = new Point(73, 273);
      this.tbRareOpt9.Name = "tbRareOpt9";
      this.tbRareOpt9.Size = new Size(55, 20);
      this.tbRareOpt9.TabIndex = 61;
      this.tbRareChance9.BorderStyle = BorderStyle.FixedSingle;
      this.tbRareChance9.Location = new Point(220, 273);
      this.tbRareChance9.Name = "tbRareChance9";
      this.tbRareChance9.Size = new Size(74, 20);
      this.tbRareChance9.TabIndex = 60;
      this.label66.AutoSize = true;
      this.label66.Location = new Point(170, 275);
      this.label66.Name = "label66";
      this.label66.Size = new Size(44, 13);
      this.label66.TabIndex = 59;
      this.label66.Text = "Chance";
      this.label67.AutoSize = true;
      this.label67.Location = new Point(18, 275);
      this.label67.Name = "label67";
      this.label67.Size = new Size(47, 13);
      this.label67.TabIndex = 58;
      this.label67.Text = "Option 9";
      this.btnRareSearch8.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.oie_transparent;
      this.btnRareSearch8.BackgroundImageLayout = ImageLayout.Stretch;
      this.btnRareSearch8.FlatAppearance.BorderSize = 0;
      this.btnRareSearch8.FlatStyle = FlatStyle.Flat;
      this.btnRareSearch8.Location = new Point(134, 247);
      this.btnRareSearch8.Name = "btnRareSearch8";
      this.btnRareSearch8.Size = new Size(19, 20);
      this.btnRareSearch8.TabIndex = 57;
      this.btnRareSearch8.UseVisualStyleBackColor = true;
      this.tbRareOpt8.BorderStyle = BorderStyle.FixedSingle;
      this.tbRareOpt8.Location = new Point(73, 247);
      this.tbRareOpt8.Name = "tbRareOpt8";
      this.tbRareOpt8.Size = new Size(55, 20);
      this.tbRareOpt8.TabIndex = 56;
      this.tbRareChance8.BorderStyle = BorderStyle.FixedSingle;
      this.tbRareChance8.Location = new Point(220, 247);
      this.tbRareChance8.Name = "tbRareChance8";
      this.tbRareChance8.Size = new Size(74, 20);
      this.tbRareChance8.TabIndex = 55;
      this.label68.AutoSize = true;
      this.label68.Location = new Point(170, 249);
      this.label68.Name = "label68";
      this.label68.Size = new Size(44, 13);
      this.label68.TabIndex = 54;
      this.label68.Text = "Chance";
      this.label69.AutoSize = true;
      this.label69.Location = new Point(18, 249);
      this.label69.Name = "label69";
      this.label69.Size = new Size(47, 13);
      this.label69.TabIndex = 53;
      this.label69.Text = "Option 8";
      this.btnRareSearch7.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.oie_transparent;
      this.btnRareSearch7.BackgroundImageLayout = ImageLayout.Stretch;
      this.btnRareSearch7.FlatAppearance.BorderSize = 0;
      this.btnRareSearch7.FlatStyle = FlatStyle.Flat;
      this.btnRareSearch7.Location = new Point(134, 221);
      this.btnRareSearch7.Name = "btnRareSearch7";
      this.btnRareSearch7.Size = new Size(19, 20);
      this.btnRareSearch7.TabIndex = 52;
      this.btnRareSearch7.UseVisualStyleBackColor = true;
      this.tbRareOpt7.BorderStyle = BorderStyle.FixedSingle;
      this.tbRareOpt7.Location = new Point(73, 221);
      this.tbRareOpt7.Name = "tbRareOpt7";
      this.tbRareOpt7.Size = new Size(55, 20);
      this.tbRareOpt7.TabIndex = 51;
      this.tbRareChance7.BorderStyle = BorderStyle.FixedSingle;
      this.tbRareChance7.Location = new Point(220, 221);
      this.tbRareChance7.Name = "tbRareChance7";
      this.tbRareChance7.Size = new Size(74, 20);
      this.tbRareChance7.TabIndex = 50;
      this.label70.AutoSize = true;
      this.label70.Location = new Point(170, 223);
      this.label70.Name = "label70";
      this.label70.Size = new Size(44, 13);
      this.label70.TabIndex = 49;
      this.label70.Text = "Chance";
      this.label71.AutoSize = true;
      this.label71.Location = new Point(18, 223);
      this.label71.Name = "label71";
      this.label71.Size = new Size(47, 13);
      this.label71.TabIndex = 48;
      this.label71.Text = "Option 7";
      this.btnRareSearch6.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.oie_transparent;
      this.btnRareSearch6.BackgroundImageLayout = ImageLayout.Stretch;
      this.btnRareSearch6.FlatAppearance.BorderSize = 0;
      this.btnRareSearch6.FlatStyle = FlatStyle.Flat;
      this.btnRareSearch6.Location = new Point(134, 195);
      this.btnRareSearch6.Name = "btnRareSearch6";
      this.btnRareSearch6.Size = new Size(19, 20);
      this.btnRareSearch6.TabIndex = 47;
      this.btnRareSearch6.UseVisualStyleBackColor = true;
      this.tbRareOpt6.BorderStyle = BorderStyle.FixedSingle;
      this.tbRareOpt6.Location = new Point(73, 195);
      this.tbRareOpt6.Name = "tbRareOpt6";
      this.tbRareOpt6.Size = new Size(55, 20);
      this.tbRareOpt6.TabIndex = 46;
      this.tbRareChance6.BorderStyle = BorderStyle.FixedSingle;
      this.tbRareChance6.Location = new Point(220, 195);
      this.tbRareChance6.Name = "tbRareChance6";
      this.tbRareChance6.Size = new Size(74, 20);
      this.tbRareChance6.TabIndex = 45;
      this.label72.AutoSize = true;
      this.label72.Location = new Point(170, 197);
      this.label72.Name = "label72";
      this.label72.Size = new Size(44, 13);
      this.label72.TabIndex = 44;
      this.label72.Text = "Chance";
      this.label73.AutoSize = true;
      this.label73.Location = new Point(18, 197);
      this.label73.Name = "label73";
      this.label73.Size = new Size(47, 13);
      this.label73.TabIndex = 43;
      this.label73.Text = "Option 6";
      this.btnRareSearch5.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.oie_transparent;
      this.btnRareSearch5.BackgroundImageLayout = ImageLayout.Stretch;
      this.btnRareSearch5.FlatAppearance.BorderSize = 0;
      this.btnRareSearch5.FlatStyle = FlatStyle.Flat;
      this.btnRareSearch5.Location = new Point(134, 169);
      this.btnRareSearch5.Name = "btnRareSearch5";
      this.btnRareSearch5.Size = new Size(19, 20);
      this.btnRareSearch5.TabIndex = 42;
      this.btnRareSearch5.UseVisualStyleBackColor = true;
      this.tbRareOpt5.BorderStyle = BorderStyle.FixedSingle;
      this.tbRareOpt5.Location = new Point(73, 169);
      this.tbRareOpt5.Name = "tbRareOpt5";
      this.tbRareOpt5.Size = new Size(55, 20);
      this.tbRareOpt5.TabIndex = 41;
      this.tbRareChance5.BorderStyle = BorderStyle.FixedSingle;
      this.tbRareChance5.Location = new Point(220, 169);
      this.tbRareChance5.Name = "tbRareChance5";
      this.tbRareChance5.Size = new Size(74, 20);
      this.tbRareChance5.TabIndex = 40;
      this.label74.AutoSize = true;
      this.label74.Location = new Point(170, 171);
      this.label74.Name = "label74";
      this.label74.Size = new Size(44, 13);
      this.label74.TabIndex = 39;
      this.label74.Text = "Chance";
      this.label75.AutoSize = true;
      this.label75.Location = new Point(18, 171);
      this.label75.Name = "label75";
      this.label75.Size = new Size(47, 13);
      this.label75.TabIndex = 38;
      this.label75.Text = "Option 5";
      this.btnRareSearch4.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.oie_transparent;
      this.btnRareSearch4.BackgroundImageLayout = ImageLayout.Stretch;
      this.btnRareSearch4.FlatAppearance.BorderSize = 0;
      this.btnRareSearch4.FlatStyle = FlatStyle.Flat;
      this.btnRareSearch4.Location = new Point(134, 143);
      this.btnRareSearch4.Name = "btnRareSearch4";
      this.btnRareSearch4.Size = new Size(19, 20);
      this.btnRareSearch4.TabIndex = 37;
      this.btnRareSearch4.UseVisualStyleBackColor = true;
      this.tbRareOpt4.BorderStyle = BorderStyle.FixedSingle;
      this.tbRareOpt4.Location = new Point(73, 143);
      this.tbRareOpt4.Name = "tbRareOpt4";
      this.tbRareOpt4.Size = new Size(55, 20);
      this.tbRareOpt4.TabIndex = 36;
      this.tbRareChance4.BorderStyle = BorderStyle.FixedSingle;
      this.tbRareChance4.Location = new Point(220, 143);
      this.tbRareChance4.Name = "tbRareChance4";
      this.tbRareChance4.Size = new Size(74, 20);
      this.tbRareChance4.TabIndex = 35;
      this.label64.AutoSize = true;
      this.label64.Location = new Point(170, 145);
      this.label64.Name = "label64";
      this.label64.Size = new Size(44, 13);
      this.label64.TabIndex = 34;
      this.label64.Text = "Chance";
      this.label65.AutoSize = true;
      this.label65.Location = new Point(18, 145);
      this.label65.Name = "label65";
      this.label65.Size = new Size(47, 13);
      this.label65.TabIndex = 33;
      this.label65.Text = "Option 4";
      this.btnRareSearch3.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.oie_transparent;
      this.btnRareSearch3.BackgroundImageLayout = ImageLayout.Stretch;
      this.btnRareSearch3.FlatAppearance.BorderSize = 0;
      this.btnRareSearch3.FlatStyle = FlatStyle.Flat;
      this.btnRareSearch3.Location = new Point(134, 117);
      this.btnRareSearch3.Name = "btnRareSearch3";
      this.btnRareSearch3.Size = new Size(19, 20);
      this.btnRareSearch3.TabIndex = 32;
      this.btnRareSearch3.UseVisualStyleBackColor = true;
      this.tbRareOpt3.BorderStyle = BorderStyle.FixedSingle;
      this.tbRareOpt3.Location = new Point(73, 117);
      this.tbRareOpt3.Name = "tbRareOpt3";
      this.tbRareOpt3.Size = new Size(55, 20);
      this.tbRareOpt3.TabIndex = 31;
      this.tbRareChance3.BorderStyle = BorderStyle.FixedSingle;
      this.tbRareChance3.Location = new Point(220, 117);
      this.tbRareChance3.Name = "tbRareChance3";
      this.tbRareChance3.Size = new Size(74, 20);
      this.tbRareChance3.TabIndex = 30;
      this.label62.AutoSize = true;
      this.label62.Location = new Point(170, 119);
      this.label62.Name = "label62";
      this.label62.Size = new Size(44, 13);
      this.label62.TabIndex = 29;
      this.label62.Text = "Chance";
      this.label63.AutoSize = true;
      this.label63.Location = new Point(18, 119);
      this.label63.Name = "label63";
      this.label63.Size = new Size(47, 13);
      this.label63.TabIndex = 28;
      this.label63.Text = "Option 3";
      this.btnRareSearch2.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.oie_transparent;
      this.btnRareSearch2.BackgroundImageLayout = ImageLayout.Stretch;
      this.btnRareSearch2.FlatAppearance.BorderSize = 0;
      this.btnRareSearch2.FlatStyle = FlatStyle.Flat;
      this.btnRareSearch2.Location = new Point(134, 91);
      this.btnRareSearch2.Name = "btnRareSearch2";
      this.btnRareSearch2.Size = new Size(19, 20);
      this.btnRareSearch2.TabIndex = 27;
      this.btnRareSearch2.UseVisualStyleBackColor = true;
      this.tbRareOpt2.BorderStyle = BorderStyle.FixedSingle;
      this.tbRareOpt2.Location = new Point(73, 91);
      this.tbRareOpt2.Name = "tbRareOpt2";
      this.tbRareOpt2.Size = new Size(55, 20);
      this.tbRareOpt2.TabIndex = 26;
      this.tbRareChance2.BorderStyle = BorderStyle.FixedSingle;
      this.tbRareChance2.Location = new Point(220, 91);
      this.tbRareChance2.Name = "tbRareChance2";
      this.tbRareChance2.Size = new Size(74, 20);
      this.tbRareChance2.TabIndex = 25;
      this.label60.AutoSize = true;
      this.label60.Location = new Point(170, 93);
      this.label60.Name = "label60";
      this.label60.Size = new Size(44, 13);
      this.label60.TabIndex = 24;
      this.label60.Text = "Chance";
      this.label61.AutoSize = true;
      this.label61.Location = new Point(18, 93);
      this.label61.Name = "label61";
      this.label61.Size = new Size(47, 13);
      this.label61.TabIndex = 23;
      this.label61.Text = "Option 2";
      this.btnRareSearch1.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.oie_transparent;
      this.btnRareSearch1.BackgroundImageLayout = ImageLayout.Stretch;
      this.btnRareSearch1.FlatAppearance.BorderSize = 0;
      this.btnRareSearch1.FlatStyle = FlatStyle.Flat;
      this.btnRareSearch1.Location = new Point(134, 65);
      this.btnRareSearch1.Name = "btnRareSearch1";
      this.btnRareSearch1.Size = new Size(19, 20);
      this.btnRareSearch1.TabIndex = 22;
      this.btnRareSearch1.UseVisualStyleBackColor = true;
      this.tbRareOpt1.BorderStyle = BorderStyle.FixedSingle;
      this.tbRareOpt1.Location = new Point(73, 65);
      this.tbRareOpt1.Name = "tbRareOpt1";
      this.tbRareOpt1.Size = new Size(55, 20);
      this.tbRareOpt1.TabIndex = 21;
      this.tbRareChance1.BorderStyle = BorderStyle.FixedSingle;
      this.tbRareChance1.Location = new Point(220, 65);
      this.tbRareChance1.Name = "tbRareChance1";
      this.tbRareChance1.Size = new Size(74, 20);
      this.tbRareChance1.TabIndex = 20;
      this.label58.AutoSize = true;
      this.label58.Location = new Point(170, 67);
      this.label58.Name = "label58";
      this.label58.Size = new Size(44, 13);
      this.label58.TabIndex = 19;
      this.label58.Text = "Chance";
      this.label59.AutoSize = true;
      this.label59.Location = new Point(18, 67);
      this.label59.Name = "label59";
      this.label59.Size = new Size(47, 13);
      this.label59.TabIndex = 18;
      this.label59.Text = "Option 1";
      this.btnRareSearch0.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.oie_transparent;
      this.btnRareSearch0.BackgroundImageLayout = ImageLayout.Stretch;
      this.btnRareSearch0.FlatAppearance.BorderSize = 0;
      this.btnRareSearch0.FlatStyle = FlatStyle.Flat;
      this.btnRareSearch0.Location = new Point(134, 39);
      this.btnRareSearch0.Name = "btnRareSearch0";
      this.btnRareSearch0.Size = new Size(19, 20);
      this.btnRareSearch0.TabIndex = 17;
      this.btnRareSearch0.UseVisualStyleBackColor = true;
      this.tbRareOpt0.BorderStyle = BorderStyle.FixedSingle;
      this.tbRareOpt0.Location = new Point(73, 39);
      this.tbRareOpt0.Name = "tbRareOpt0";
      this.tbRareOpt0.Size = new Size(55, 20);
      this.tbRareOpt0.TabIndex = 4;
      this.tbRareChance0.BorderStyle = BorderStyle.FixedSingle;
      this.tbRareChance0.Location = new Point(220, 39);
      this.tbRareChance0.Name = "tbRareChance0";
      this.tbRareChance0.Size = new Size(74, 20);
      this.tbRareChance0.TabIndex = 3;
      this.label57.AutoSize = true;
      this.label57.Location = new Point(170, 41);
      this.label57.Name = "label57";
      this.label57.Size = new Size(44, 13);
      this.label57.TabIndex = 2;
      this.label57.Text = "Chance";
      this.label56.AutoSize = true;
      this.label56.Location = new Point(18, 41);
      this.label56.Name = "label56";
      this.label56.Size = new Size(47, 13);
      this.label56.TabIndex = 1;
      this.label56.Text = "Option 0";
      this.panel3.BackColor = Color.White;
      this.panel3.BorderStyle = BorderStyle.FixedSingle;
      this.panel3.Controls.Add((Control) this.btnRareDbPut);
      this.panel3.Controls.Add((Control) this.btnRareDbGet);
      this.panel3.Location = new Point(6, 3);
      this.panel3.Name = "panel3";
      this.panel3.Size = new Size(687, 29);
      this.panel3.TabIndex = 11;
      this.btnRareDbPut.Location = new Point(152, 2);
      this.btnRareDbPut.Name = "btnRareDbPut";
      this.btnRareDbPut.Size = new Size(152, 23);
      this.btnRareDbPut.TabIndex = 1;
      this.btnRareDbPut.Text = "Update to database";
      this.btnRareDbPut.TextImageRelation = TextImageRelation.ImageBeforeText;
      this.btnRareDbPut.UseVisualStyleBackColor = true;
      this.btnRareDbGet.BackgroundImageLayout = ImageLayout.None;
      this.btnRareDbGet.Location = new Point(5, 2);
      this.btnRareDbGet.Name = "btnRareDbGet";
      this.btnRareDbGet.Size = new Size(141, 23);
      this.btnRareDbGet.TabIndex = 0;
      this.btnRareDbGet.Text = "Get from database";
      this.btnRareDbGet.TextImageRelation = TextImageRelation.ImageBeforeText;
      this.btnRareDbGet.UseVisualStyleBackColor = true;
      this.tabPage6.BackColor = SystemColors.Control;
      this.tabPage6.BorderStyle = BorderStyle.FixedSingle;
      this.tabPage6.Controls.Add((Control) this.textBox6);
      this.tabPage6.Controls.Add((Control) this.textBox5);
      this.tabPage6.Controls.Add((Control) this.textBox4);
      this.tabPage6.Controls.Add((Control) this.textBox3);
      this.tabPage6.Controls.Add((Control) this.textBox2);
      this.tabPage6.Controls.Add((Control) this.textBox1);
      this.tabPage6.Controls.Add((Control) this.btnSearchSkill3);
      this.tabPage6.Controls.Add((Control) this.btnSearchSkill2);
      this.tabPage6.Controls.Add((Control) this.btnSearchSkill1);
      this.tabPage6.Controls.Add((Control) this.tbCB1);
      this.tabPage6.Controls.Add((Control) this.tbCB2);
      this.tabPage6.Controls.Add((Control) this.label89);
      this.tabPage6.Controls.Add((Control) this.label86);
      this.tabPage6.Controls.Add((Control) this.label87);
      this.tabPage6.Controls.Add((Control) this.label88);
      this.tabPage6.Controls.Add((Control) this.label85);
      this.tabPage6.Controls.Add((Control) this.label84);
      this.tabPage6.Controls.Add((Control) this.label83);
      this.tabPage6.Controls.Add((Control) this.label81);
      this.tabPage6.Controls.Add((Control) this.label82);
      this.tabPage6.Controls.Add((Control) this.tbSkillLevel3);
      this.tabPage6.Controls.Add((Control) this.tbSkillID3);
      this.tabPage6.Controls.Add((Control) this.label79);
      this.tabPage6.Controls.Add((Control) this.label80);
      this.tabPage6.Controls.Add((Control) this.tbSkillLevel2);
      this.tabPage6.Controls.Add((Control) this.tbSkillID2);
      this.tabPage6.Controls.Add((Control) this.label78);
      this.tabPage6.Controls.Add((Control) this.label77);
      this.tabPage6.Controls.Add((Control) this.tbSkillLevel1);
      this.tabPage6.Controls.Add((Control) this.tbSkillID1);
      this.tabPage6.Controls.Add((Control) this.tbSealID6);
      this.tabPage6.Controls.Add((Control) this.cbSealLevel6);
      this.tabPage6.Controls.Add((Control) this.tbSealLevel6);
      this.tabPage6.Controls.Add((Control) this.cbSealID6);
      this.tabPage6.Controls.Add((Control) this.tbSealID5);
      this.tabPage6.Controls.Add((Control) this.cbSealLevel5);
      this.tabPage6.Controls.Add((Control) this.tbSealLevel5);
      this.tabPage6.Controls.Add((Control) this.cbSealID5);
      this.tabPage6.Controls.Add((Control) this.tbSealID4);
      this.tabPage6.Controls.Add((Control) this.cbSealLevel4);
      this.tabPage6.Controls.Add((Control) this.tbSealLevel4);
      this.tabPage6.Controls.Add((Control) this.cbSealID4);
      this.tabPage6.Controls.Add((Control) this.tbSealID3);
      this.tabPage6.Controls.Add((Control) this.cbSealLevel3);
      this.tabPage6.Controls.Add((Control) this.tbSealLevel3);
      this.tabPage6.Controls.Add((Control) this.cbSealID3);
      this.tabPage6.Controls.Add((Control) this.tbSealID2);
      this.tabPage6.Controls.Add((Control) this.cbSealLevel2);
      this.tabPage6.Controls.Add((Control) this.tbSealLevel2);
      this.tabPage6.Controls.Add((Control) this.cbSealID2);
      this.tabPage6.Controls.Add((Control) this.tbSealID1);
      this.tabPage6.Controls.Add((Control) this.cbSealLevel1);
      this.tabPage6.Controls.Add((Control) this.tbSealLevel1);
      this.tabPage6.Controls.Add((Control) this.cbSealID1);
      this.tabPage6.Controls.Add((Control) this.pbSkill3Icon);
      this.tabPage6.Controls.Add((Control) this.pbSkill2Icon);
      this.tabPage6.Controls.Add((Control) this.pbSkill1Icon);
      this.tabPage6.Location = new Point(4, 22);
      this.tabPage6.Name = "tabPage6";
      this.tabPage6.Padding = new Padding(3);
      this.tabPage6.Size = new Size(762, 492);
      this.tabPage6.TabIndex = 3;
      this.tabPage6.Text = "Purple Items";
      this.textBox6.BorderStyle = BorderStyle.FixedSingle;
      this.textBox6.Location = new Point(485, 99);
      this.textBox6.Name = "textBox6";
      this.textBox6.Size = new Size(38, 20);
      this.textBox6.TabIndex = 61;
      this.textBox5.BorderStyle = BorderStyle.FixedSingle;
      this.textBox5.Location = new Point(485, 236);
      this.textBox5.Name = "textBox5";
      this.textBox5.Size = new Size(38, 20);
      this.textBox5.TabIndex = 60;
      this.textBox4.BorderStyle = BorderStyle.FixedSingle;
      this.textBox4.Location = new Point(485, 210);
      this.textBox4.Name = "textBox4";
      this.textBox4.Size = new Size(38, 20);
      this.textBox4.TabIndex = 59;
      this.textBox3.BorderStyle = BorderStyle.FixedSingle;
      this.textBox3.Location = new Point(485, 182);
      this.textBox3.Name = "textBox3";
      this.textBox3.Size = new Size(38, 20);
      this.textBox3.TabIndex = 58;
      this.textBox2.BorderStyle = BorderStyle.FixedSingle;
      this.textBox2.Location = new Point(485, 155);
      this.textBox2.Name = "textBox2";
      this.textBox2.Size = new Size(38, 20);
      this.textBox2.TabIndex = 57;
      this.textBox1.BorderStyle = BorderStyle.FixedSingle;
      this.textBox1.Location = new Point(485, 126);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(38, 20);
      this.textBox1.TabIndex = 56;
      this.btnSearchSkill3.BackgroundImageLayout = ImageLayout.None;
      this.btnSearchSkill3.FlatAppearance.BorderSize = 0;
      this.btnSearchSkill3.FlatStyle = FlatStyle.Flat;
      this.btnSearchSkill3.Location = new Point(171, 372);
      this.btnSearchSkill3.Name = "btnSearchSkill3";
      this.btnSearchSkill3.Size = new Size(19, 20);
      this.btnSearchSkill3.TabIndex = 55;
      this.btnSearchSkill3.UseVisualStyleBackColor = true;
      this.btnSearchSkill2.BackgroundImageLayout = ImageLayout.None;
      this.btnSearchSkill2.FlatAppearance.BorderSize = 0;
      this.btnSearchSkill2.FlatStyle = FlatStyle.Flat;
      this.btnSearchSkill2.Location = new Point(171, 332);
      this.btnSearchSkill2.Name = "btnSearchSkill2";
      this.btnSearchSkill2.Size = new Size(19, 20);
      this.btnSearchSkill2.TabIndex = 54;
      this.btnSearchSkill2.UseVisualStyleBackColor = true;
      this.btnSearchSkill1.BackgroundImageLayout = ImageLayout.None;
      this.btnSearchSkill1.FlatAppearance.BorderSize = 0;
      this.btnSearchSkill1.FlatStyle = FlatStyle.Flat;
      this.btnSearchSkill1.Location = new Point(171, 293);
      this.btnSearchSkill1.Name = "btnSearchSkill1";
      this.btnSearchSkill1.Size = new Size(19, 20);
      this.btnSearchSkill1.TabIndex = 53;
      this.btnSearchSkill1.UseVisualStyleBackColor = true;
      this.tbCB1.BorderStyle = BorderStyle.FixedSingle;
      this.tbCB1.Location = new Point(162, 52);
      this.tbCB1.Name = "tbCB1";
      this.tbCB1.Size = new Size(38, 20);
      this.tbCB1.TabIndex = 46;
      this.tbCB2.BorderStyle = BorderStyle.FixedSingle;
      this.tbCB2.Location = new Point(206, 52);
      this.tbCB2.Name = "tbCB2";
      this.tbCB2.Size = new Size(38, 20);
      this.tbCB2.TabIndex = 45;
      this.label89.AutoSize = true;
      this.label89.Location = new Point(70, 54);
      this.label89.Name = "label89";
      this.label89.Size = new Size(86, 13);
      this.label89.TabIndex = 44;
      this.label89.Text = "Character bound";
      this.label86.AutoSize = true;
      this.label86.Location = new Point(27, 237);
      this.label86.Name = "label86";
      this.label86.Size = new Size(37, 13);
      this.label86.TabIndex = 43;
      this.label86.Text = "Seal 6";
      this.label87.AutoSize = true;
      this.label87.Location = new Point(27, 210);
      this.label87.Name = "label87";
      this.label87.Size = new Size(37, 13);
      this.label87.TabIndex = 42;
      this.label87.Text = "Seal 5";
      this.label88.AutoSize = true;
      this.label88.Location = new Point(27, 182);
      this.label88.Name = "label88";
      this.label88.Size = new Size(37, 13);
      this.label88.TabIndex = 41;
      this.label88.Text = "Seal 4";
      this.label85.AutoSize = true;
      this.label85.Location = new Point(27, 157);
      this.label85.Name = "label85";
      this.label85.Size = new Size(37, 13);
      this.label85.TabIndex = 40;
      this.label85.Text = "Seal 3";
      this.label84.AutoSize = true;
      this.label84.Location = new Point(27, 130);
      this.label84.Name = "label84";
      this.label84.Size = new Size(37, 13);
      this.label84.TabIndex = 39;
      this.label84.Text = "Seal 2";
      this.label83.AutoSize = true;
      this.label83.Location = new Point(27, 102);
      this.label83.Name = "label83";
      this.label83.Size = new Size(37, 13);
      this.label83.TabIndex = 38;
      this.label83.Text = "Seal 1";
      this.label81.AutoSize = true;
      this.label81.Location = new Point(196, 374);
      this.label81.Name = "label81";
      this.label81.Size = new Size(33, 13);
      this.label81.TabIndex = 36;
      this.label81.Text = "Level";
      this.label82.AutoSize = true;
      this.label82.Location = new Point(67, 374);
      this.label82.Name = "label82";
      this.label82.Size = new Size(40, 13);
      this.label82.TabIndex = 35;
      this.label82.Text = "Skill ID";
      this.tbSkillLevel3.BorderStyle = BorderStyle.FixedSingle;
      this.tbSkillLevel3.Location = new Point(235, 372);
      this.tbSkillLevel3.Name = "tbSkillLevel3";
      this.tbSkillLevel3.Size = new Size(38, 20);
      this.tbSkillLevel3.TabIndex = 34;
      this.tbSkillID3.BorderStyle = BorderStyle.FixedSingle;
      this.tbSkillID3.Location = new Point(113, 372);
      this.tbSkillID3.Name = "tbSkillID3";
      this.tbSkillID3.Size = new Size(52, 20);
      this.tbSkillID3.TabIndex = 33;
      this.label79.AutoSize = true;
      this.label79.Location = new Point(196, 334);
      this.label79.Name = "label79";
      this.label79.Size = new Size(33, 13);
      this.label79.TabIndex = 32;
      this.label79.Text = "Level";
      this.label80.AutoSize = true;
      this.label80.Location = new Point(67, 334);
      this.label80.Name = "label80";
      this.label80.Size = new Size(40, 13);
      this.label80.TabIndex = 31;
      this.label80.Text = "Skill ID";
      this.tbSkillLevel2.BorderStyle = BorderStyle.FixedSingle;
      this.tbSkillLevel2.Location = new Point(235, 332);
      this.tbSkillLevel2.Name = "tbSkillLevel2";
      this.tbSkillLevel2.Size = new Size(38, 20);
      this.tbSkillLevel2.TabIndex = 30;
      this.tbSkillID2.BorderStyle = BorderStyle.FixedSingle;
      this.tbSkillID2.Location = new Point(113, 332);
      this.tbSkillID2.Name = "tbSkillID2";
      this.tbSkillID2.Size = new Size(52, 20);
      this.tbSkillID2.TabIndex = 29;
      this.label78.AutoSize = true;
      this.label78.Location = new Point(196, 295);
      this.label78.Name = "label78";
      this.label78.Size = new Size(33, 13);
      this.label78.TabIndex = 28;
      this.label78.Text = "Level";
      this.label77.AutoSize = true;
      this.label77.Location = new Point(67, 295);
      this.label77.Name = "label77";
      this.label77.Size = new Size(40, 13);
      this.label77.TabIndex = 27;
      this.label77.Text = "Skill ID";
      this.tbSkillLevel1.BorderStyle = BorderStyle.FixedSingle;
      this.tbSkillLevel1.Location = new Point(235, 293);
      this.tbSkillLevel1.Name = "tbSkillLevel1";
      this.tbSkillLevel1.Size = new Size(38, 20);
      this.tbSkillLevel1.TabIndex = 26;
      this.tbSkillID1.BorderStyle = BorderStyle.FixedSingle;
      this.tbSkillID1.Location = new Point(113, 293);
      this.tbSkillID1.Name = "tbSkillID1";
      this.tbSkillID1.Size = new Size(52, 20);
      this.tbSkillID1.TabIndex = 25;
      this.tbSealID6.BorderStyle = BorderStyle.FixedSingle;
      this.tbSealID6.Location = new Point(397, 234);
      this.tbSealID6.Name = "tbSealID6";
      this.tbSealID6.ReadOnly = true;
      this.tbSealID6.Size = new Size(38, 20);
      this.tbSealID6.TabIndex = 24;
      this.cbSealLevel6.FormattingEnabled = true;
      this.cbSealLevel6.Location = new Point(288, 234);
      this.cbSealLevel6.MaxDropDownItems = 100;
      this.cbSealLevel6.Name = "cbSealLevel6";
      this.cbSealLevel6.Size = new Size(99, 21);
      this.cbSealLevel6.TabIndex = 23;
      this.tbSealLevel6.BorderStyle = BorderStyle.FixedSingle;
      this.tbSealLevel6.Location = new Point(441, 234);
      this.tbSealLevel6.Name = "tbSealLevel6";
      this.tbSealLevel6.ReadOnly = true;
      this.tbSealLevel6.Size = new Size(38, 20);
      this.tbSealLevel6.TabIndex = 22;
      this.cbSealID6.FormattingEnabled = true;
      this.cbSealID6.Location = new Point(70, 235);
      this.cbSealID6.MaxDropDownItems = 100;
      this.cbSealID6.Name = "cbSealID6";
      this.cbSealID6.Size = new Size(212, 21);
      this.cbSealID6.TabIndex = 21;
      this.tbSealID5.BorderStyle = BorderStyle.FixedSingle;
      this.tbSealID5.Location = new Point(397, 207);
      this.tbSealID5.Name = "tbSealID5";
      this.tbSealID5.ReadOnly = true;
      this.tbSealID5.Size = new Size(38, 20);
      this.tbSealID5.TabIndex = 20;
      this.cbSealLevel5.FormattingEnabled = true;
      this.cbSealLevel5.Location = new Point(288, 207);
      this.cbSealLevel5.MaxDropDownItems = 100;
      this.cbSealLevel5.Name = "cbSealLevel5";
      this.cbSealLevel5.Size = new Size(99, 21);
      this.cbSealLevel5.TabIndex = 19;
      this.tbSealLevel5.BorderStyle = BorderStyle.FixedSingle;
      this.tbSealLevel5.Location = new Point(441, 207);
      this.tbSealLevel5.Name = "tbSealLevel5";
      this.tbSealLevel5.ReadOnly = true;
      this.tbSealLevel5.Size = new Size(38, 20);
      this.tbSealLevel5.TabIndex = 18;
      this.cbSealID5.FormattingEnabled = true;
      this.cbSealID5.Location = new Point(70, 208);
      this.cbSealID5.MaxDropDownItems = 100;
      this.cbSealID5.Name = "cbSealID5";
      this.cbSealID5.Size = new Size(212, 21);
      this.cbSealID5.TabIndex = 17;
      this.tbSealID4.BorderStyle = BorderStyle.FixedSingle;
      this.tbSealID4.Location = new Point(397, 180);
      this.tbSealID4.Name = "tbSealID4";
      this.tbSealID4.ReadOnly = true;
      this.tbSealID4.Size = new Size(38, 20);
      this.tbSealID4.TabIndex = 16;
      this.cbSealLevel4.FormattingEnabled = true;
      this.cbSealLevel4.Location = new Point(288, 180);
      this.cbSealLevel4.MaxDropDownItems = 100;
      this.cbSealLevel4.Name = "cbSealLevel4";
      this.cbSealLevel4.Size = new Size(99, 21);
      this.cbSealLevel4.TabIndex = 15;
      this.tbSealLevel4.BorderStyle = BorderStyle.FixedSingle;
      this.tbSealLevel4.Location = new Point(441, 180);
      this.tbSealLevel4.Name = "tbSealLevel4";
      this.tbSealLevel4.ReadOnly = true;
      this.tbSealLevel4.Size = new Size(38, 20);
      this.tbSealLevel4.TabIndex = 14;
      this.cbSealID4.FormattingEnabled = true;
      this.cbSealID4.Location = new Point(70, 181);
      this.cbSealID4.MaxDropDownItems = 100;
      this.cbSealID4.Name = "cbSealID4";
      this.cbSealID4.Size = new Size(212, 21);
      this.cbSealID4.TabIndex = 13;
      this.tbSealID3.BorderStyle = BorderStyle.FixedSingle;
      this.tbSealID3.Location = new Point(397, 153);
      this.tbSealID3.Name = "tbSealID3";
      this.tbSealID3.ReadOnly = true;
      this.tbSealID3.Size = new Size(38, 20);
      this.tbSealID3.TabIndex = 12;
      this.cbSealLevel3.FormattingEnabled = true;
      this.cbSealLevel3.Location = new Point(288, 153);
      this.cbSealLevel3.MaxDropDownItems = 100;
      this.cbSealLevel3.Name = "cbSealLevel3";
      this.cbSealLevel3.Size = new Size(99, 21);
      this.cbSealLevel3.TabIndex = 11;
      this.tbSealLevel3.BorderStyle = BorderStyle.FixedSingle;
      this.tbSealLevel3.Location = new Point(441, 153);
      this.tbSealLevel3.Name = "tbSealLevel3";
      this.tbSealLevel3.ReadOnly = true;
      this.tbSealLevel3.Size = new Size(38, 20);
      this.tbSealLevel3.TabIndex = 10;
      this.cbSealID3.FormattingEnabled = true;
      this.cbSealID3.Location = new Point(70, 154);
      this.cbSealID3.MaxDropDownItems = 100;
      this.cbSealID3.Name = "cbSealID3";
      this.cbSealID3.Size = new Size(212, 21);
      this.cbSealID3.TabIndex = 9;
      this.tbSealID2.BorderStyle = BorderStyle.FixedSingle;
      this.tbSealID2.Location = new Point(397, 126);
      this.tbSealID2.Name = "tbSealID2";
      this.tbSealID2.ReadOnly = true;
      this.tbSealID2.Size = new Size(38, 20);
      this.tbSealID2.TabIndex = 8;
      this.cbSealLevel2.FormattingEnabled = true;
      this.cbSealLevel2.Location = new Point(288, 126);
      this.cbSealLevel2.MaxDropDownItems = 100;
      this.cbSealLevel2.Name = "cbSealLevel2";
      this.cbSealLevel2.Size = new Size(99, 21);
      this.cbSealLevel2.TabIndex = 7;
      this.tbSealLevel2.BorderStyle = BorderStyle.FixedSingle;
      this.tbSealLevel2.Location = new Point(441, 126);
      this.tbSealLevel2.Name = "tbSealLevel2";
      this.tbSealLevel2.ReadOnly = true;
      this.tbSealLevel2.Size = new Size(38, 20);
      this.tbSealLevel2.TabIndex = 6;
      this.cbSealID2.FormattingEnabled = true;
      this.cbSealID2.Location = new Point(70, (int) sbyte.MaxValue);
      this.cbSealID2.MaxDropDownItems = 100;
      this.cbSealID2.Name = "cbSealID2";
      this.cbSealID2.Size = new Size(212, 21);
      this.cbSealID2.TabIndex = 5;
      this.tbSealID1.BorderStyle = BorderStyle.FixedSingle;
      this.tbSealID1.Location = new Point(397, 99);
      this.tbSealID1.Name = "tbSealID1";
      this.tbSealID1.ReadOnly = true;
      this.tbSealID1.Size = new Size(38, 20);
      this.tbSealID1.TabIndex = 3;
      this.cbSealLevel1.FormattingEnabled = true;
      this.cbSealLevel1.Location = new Point(288, 99);
      this.cbSealLevel1.MaxDropDownItems = 100;
      this.cbSealLevel1.Name = "cbSealLevel1";
      this.cbSealLevel1.Size = new Size(99, 21);
      this.cbSealLevel1.TabIndex = 2;
      this.tbSealLevel1.BorderStyle = BorderStyle.FixedSingle;
      this.tbSealLevel1.Location = new Point(441, 99);
      this.tbSealLevel1.Name = "tbSealLevel1";
      this.tbSealLevel1.ReadOnly = true;
      this.tbSealLevel1.Size = new Size(38, 20);
      this.tbSealLevel1.TabIndex = 1;
      this.cbSealID1.FormattingEnabled = true;
      this.cbSealID1.Location = new Point(70, 100);
      this.cbSealID1.MaxDropDownItems = 100;
      this.cbSealID1.Name = "cbSealID1";
      this.cbSealID1.Size = new Size(212, 21);
      this.cbSealID1.TabIndex = 0;
      this.pbSkill3Icon.BorderStyle = BorderStyle.FixedSingle;
      this.pbSkill3Icon.Location = new Point(297, 365);
      this.pbSkill3Icon.Name = "pbSkill3Icon";
      this.pbSkill3Icon.Size = new Size(32, 32);
      this.pbSkill3Icon.TabIndex = 51;
      this.pbSkill3Icon.TabStop = false;
      this.pbSkill2Icon.BorderStyle = BorderStyle.FixedSingle;
      this.pbSkill2Icon.Location = new Point(297, 327);
      this.pbSkill2Icon.Name = "pbSkill2Icon";
      this.pbSkill2Icon.Size = new Size(32, 32);
      this.pbSkill2Icon.TabIndex = 49;
      this.pbSkill2Icon.TabStop = false;
      this.pbSkill1Icon.BorderStyle = BorderStyle.FixedSingle;
      this.pbSkill1Icon.Location = new Point(297, 289);
      this.pbSkill1Icon.Name = "pbSkill1Icon";
      this.pbSkill1Icon.Size = new Size(32, 32);
      this.pbSkill1Icon.TabIndex = 47;
      this.pbSkill1Icon.TabStop = false;
      this.lblCurDataPurple.AutoSize = true;
      this.lblCurDataPurple.Location = new Point(310, 7);
      this.lblCurDataPurple.Name = "lblCurDataPurple";
      this.lblCurDataPurple.Size = new Size(0, 13);
      this.lblCurDataPurple.TabIndex = 2;
      this.btnPurplePut.Location = new Point(152, 2);
      this.btnPurplePut.Name = "btnPurplePut";
      this.btnPurplePut.Size = new Size(152, 23);
      this.btnPurplePut.TabIndex = 1;
      this.btnPurplePut.Text = "Update to database";
      this.btnPurplePut.TextImageRelation = TextImageRelation.ImageBeforeText;
      this.btnPurplePut.UseVisualStyleBackColor = true;
      this.btnPurpleGet.BackgroundImageLayout = ImageLayout.None;
      this.btnPurpleGet.Location = new Point(5, 2);
      this.btnPurpleGet.Name = "btnPurpleGet";
      this.btnPurpleGet.Size = new Size(141, 23);
      this.btnPurpleGet.TabIndex = 0;
      this.btnPurpleGet.Text = "Get from database";
      this.btnPurpleGet.TextImageRelation = TextImageRelation.ImageBeforeText;
      this.btnPurpleGet.UseVisualStyleBackColor = true;
      this.groupBox1.Controls.Add((Control) this.chk3D);
      this.groupBox1.Controls.Add((Control) this.slideLeftRight);
      this.groupBox1.Controls.Add((Control) this.slideUpDown);
      this.groupBox1.Controls.Add((Control) this.slideZoom);
      this.groupBox1.Controls.Add((Control) this.panel3DView);
      this.groupBox1.Location = new Point(1063, 49);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(378, 430);
      this.groupBox1.TabIndex = 38;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "3D View";
      this.chk3D.AutoSize = true;
      this.chk3D.Checked = true;
      this.chk3D.CheckState = CheckState.Checked;
      this.chk3D.FlatStyle = FlatStyle.Flat;
      this.chk3D.Location = new Point(273, -3);
      this.chk3D.Name = "chk3D";
      this.chk3D.Size = new Size(99, 17);
      this.chk3D.TabIndex = 39;
      this.chk3D.Text = "Enable 3D View";
      this.chk3D.UseVisualStyleBackColor = true;
      this.chk3D.CheckedChanged += new EventHandler(this.chk3D_CheckedChanged);
      this.slideLeftRight.AutoSize = false;
      this.slideLeftRight.Location = new Point(234, 400);
      this.slideLeftRight.Maximum = 10000;
      this.slideLeftRight.Minimum = -10000;
      this.slideLeftRight.Name = "slideLeftRight";
      this.slideLeftRight.Size = new Size(85, 25);
      this.slideLeftRight.TabIndex = 3;
      this.slideLeftRight.TickStyle = TickStyle.None;
      this.slideLeftRight.Scroll += new EventHandler(this.slideLeftRight_Scroll);
      this.slideUpDown.AutoSize = false;
      this.slideUpDown.Location = new Point(143, 400);
      this.slideUpDown.Maximum = 10000;
      this.slideUpDown.Minimum = -10000;
      this.slideUpDown.Name = "slideUpDown";
      this.slideUpDown.Size = new Size(85, 25);
      this.slideUpDown.TabIndex = 2;
      this.slideUpDown.TickStyle = TickStyle.None;
      this.slideUpDown.Scroll += new EventHandler(this.slideUpDown_Scroll);
      this.slideZoom.AutoSize = false;
      this.slideZoom.Location = new Point(57, 400);
      this.slideZoom.Maximum = 100000;
      this.slideZoom.Minimum = -10000;
      this.slideZoom.Name = "slideZoom";
      this.slideZoom.Size = new Size(85, 25);
      this.slideZoom.TabIndex = 1;
      this.slideZoom.TickStyle = TickStyle.None;
      this.slideZoom.Scroll += new EventHandler(this.slideZoom_Scroll);
      this.panel3DView.BackColor = SystemColors.Highlight;
      this.panel3DView.Location = new Point(7, 20);
      this.panel3DView.Name = "panel3DView";
      this.panel3DView.Size = new Size(371, 371);
      this.panel3DView.TabIndex = 0;
      this.ModPanel.BackColor = Color.White;
      this.ModPanel.BorderStyle = BorderStyle.FixedSingle;
      this.ModPanel.Controls.Add((Control) this.chkDbUpdate);
      this.ModPanel.Controls.Add((Control) this.pictureBox1);
      this.ModPanel.Controls.Add((Control) this.label29);
      this.ModPanel.Controls.Add((Control) this.t_DiscardChanges);
      this.ModPanel.Controls.Add((Control) this.t_SaveRecord);
      this.ModPanel.Location = new Point(287, 557);
      this.ModPanel.Name = "ModPanel";
      this.ModPanel.Size = new Size(687, 30);
      this.ModPanel.TabIndex = 20;
      this.ModPanel.Visible = false;
      this.chkDbUpdate.AutoSize = true;
      this.chkDbUpdate.Location = new Point(290, 7);
      this.chkDbUpdate.Name = "chkDbUpdate";
      this.chkDbUpdate.Size = new Size(131, 17);
      this.chkDbUpdate.TabIndex = 18;
      this.chkDbUpdate.Text = "Auto update database";
      this.chkDbUpdate.UseVisualStyleBackColor = true;
      this.pictureBox1.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.Wykrzyknik;
      this.pictureBox1.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox1.Location = new Point(7, 5);
      this.pictureBox1.Name = "pictureBox1";
      this.pictureBox1.Size = new Size(17, 17);
      this.pictureBox1.TabIndex = 17;
      this.pictureBox1.TabStop = false;
      this.label29.AutoSize = true;
      this.label29.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25f, FontStyle.Bold, GraphicsUnit.Point, (byte) 0);
      this.label29.ForeColor = Color.DarkRed;
      this.label29.Location = new Point(30, 8);
      this.label29.Name = "label29";
      this.label29.Size = new Size(233, 13);
      this.label29.TabIndex = 16;
      this.label29.Text = "Changes have been made to this record";
      this.t_DiscardChanges.Location = new Point(434, 3);
      this.t_DiscardChanges.Name = "t_DiscardChanges";
      this.t_DiscardChanges.Size = new Size(126, 23);
      this.t_DiscardChanges.TabIndex = 15;
      this.t_DiscardChanges.Text = "&Discard Changes";
      this.t_DiscardChanges.UseVisualStyleBackColor = true;
      this.t_SaveRecord.Location = new Point(566, 3);
      this.t_SaveRecord.Name = "t_SaveRecord";
      this.t_SaveRecord.Size = new Size(112, 23);
      this.t_SaveRecord.TabIndex = 14;
      this.t_SaveRecord.Text = "&Save all Changes";
      this.t_SaveRecord.UseVisualStyleBackColor = true;
      this.label1.AutoSize = true;
      this.label1.Location = new Point(8, 11);
      this.label1.Name = "label1";
      this.label1.Size = new Size(41, 13);
      this.label1.TabIndex = 2;
      this.label1.Text = "Search";
      this.SearchText.BorderStyle = BorderStyle.FixedSingle;
      this.SearchText.Location = new Point(55, 9);
      this.SearchText.Name = "SearchText";
      this.SearchText.Size = new Size(207, 20);
      this.SearchText.TabIndex = 1;
      this.statusStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.status
      });
      this.statusStrip1.Location = new Point(0, 591);
      this.statusStrip1.Name = "statusStrip1";
      this.statusStrip1.Size = new Size(1453, 22);
      this.statusStrip1.TabIndex = 22;
      this.statusStrip1.Text = "statusStrip1";
      this.status.Name = "status";
      this.status.Size = new Size(0, 17);
      this.label15.AutoSize = true;
      this.label15.Location = new Point(9, 21);
      this.label15.Name = "label15";
      this.label15.Size = new Size(41, 13);
      this.label15.TabIndex = 40;
      this.label15.Text = "Search";
      this.textBox7.BorderStyle = BorderStyle.FixedSingle;
      this.textBox7.Location = new Point(56, 19);
      this.textBox7.Name = "textBox7";
      this.textBox7.Size = new Size(207, 20);
      this.textBox7.TabIndex = 39;
      this.textBox7.TextChanged += new EventHandler(this.textBox7_TextChanged);
      this.groupBox6.Controls.Add((Control) this.textBox7);
      this.groupBox6.Controls.Add((Control) this.label15);
      this.groupBox6.Location = new Point(12, 27);
      this.groupBox6.Name = "groupBox6";
      this.groupBox6.Size = new Size(269, 47);
      this.groupBox6.TabIndex = 41;
      this.groupBox6.TabStop = false;
      this.groupBox14.Controls.Add((Control) this.ItemListBox);
      this.groupBox14.Location = new Point(12, 80);
      this.groupBox14.Name = "groupBox14";
      this.groupBox14.Size = new Size(269, 465);
      this.groupBox14.TabIndex = 42;
      this.groupBox14.TabStop = false;
      this.ItemListBox.Location = new Point(4, 16);
      this.ItemListBox.Name = "ItemListBox";
      this.ItemListBox.Size = new Size(259, 433);
      this.ItemListBox.TabIndex = 1;
      this.ItemListBox.SelectedIndexChanged += new EventHandler(this.ItemListBox_SelectedIndexChanged);
      this.t_DeleteItem.Location = new Point(196, 561);
      this.t_DeleteItem.Name = "t_DeleteItem";
      this.t_DeleteItem.Size = new Size(87, 23);
      this.t_DeleteItem.TabIndex = 45;
      this.t_DeleteItem.Text = "Delete Item";
      this.t_DeleteItem.UseVisualStyleBackColor = true;
      this.t_CopyToNew.Location = new Point(105, 561);
      this.t_CopyToNew.Name = "t_CopyToNew";
      this.t_CopyToNew.Size = new Size(85, 23);
      this.t_CopyToNew.TabIndex = 44;
      this.t_CopyToNew.Text = "Copy to New";
      this.t_CopyToNew.UseVisualStyleBackColor = true;
      this.t_NewItem.Location = new Point(24, 561);
      this.t_NewItem.Name = "t_NewItem";
      this.t_NewItem.Size = new Size(75, 23);
      this.t_NewItem.TabIndex = 43;
      this.t_NewItem.Text = "New Item";
      this.t_NewItem.UseVisualStyleBackColor = true;
      this.timer1.Enabled = true;
      this.timer1.Interval = 1;
      this.timer1.Tick += new EventHandler(this.timer1_Tick);
      this.tb_castleWar.BorderStyle = BorderStyle.FixedSingle;
      this.tb_castleWar.Location = new Point(537, 273);
      this.tb_castleWar.Name = "tb_castleWar";
      this.tb_castleWar.Size = new Size(51, 20);
      this.tb_castleWar.TabIndex = 63;
      this.label16.AutoSize = true;
      this.label16.Location = new Point(497, 275);
      this.label16.Name = "label16";
      this.label16.Size = new Size(39, 13);
      this.label16.TabIndex = 64;
      this.label16.Text = "Castle:";
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(1453, 613);
      this.Controls.Add((Control) this.t_DeleteItem);
      this.Controls.Add((Control) this.t_CopyToNew);
      this.Controls.Add((Control) this.t_NewItem);
      this.Controls.Add((Control) this.groupBox14);
      this.Controls.Add((Control) this.groupBox6);
      this.Controls.Add((Control) this.groupBox1);
      this.Controls.Add((Control) this.statusStrip1);
      this.Controls.Add((Control) this.ModPanel);
      this.Controls.Add((Control) this.tabControl2);
      this.Controls.Add((Control) this.menuStrip1);
      this.Name = nameof (ItemAll);
      this.Text = nameof (ItemAll);
      this.Load += new EventHandler(this.ItemAll_Load);
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.tabControl2.ResumeLayout(false);
      this.tabPage3.ResumeLayout(false);
      this.tabPage3.PerformLayout();
      this.groupBox13.ResumeLayout(false);
      this.groupBox13.PerformLayout();
      this.groupBox23.ResumeLayout(false);
      this.groupBox23.PerformLayout();
      this.groupBox16.ResumeLayout(false);
      this.groupBox16.PerformLayout();
      this.groupBox2.ResumeLayout(false);
      this.groupBox2.PerformLayout();
      this.groupBox3.ResumeLayout(false);
      this.groupBox3.PerformLayout();
      ((ISupportInitialize) this.t_Icon).EndInit();
      this.groupBox4.ResumeLayout(false);
      this.groupBox4.PerformLayout();
      this.groupBox10.ResumeLayout(false);
      this.groupBox10.PerformLayout();
      this.groupBox5.ResumeLayout(false);
      this.groupBox5.PerformLayout();
      this.groupBox8.ResumeLayout(false);
      this.groupBox8.PerformLayout();
      this.groupBox7.ResumeLayout(false);
      this.groupBox7.PerformLayout();
      this.panel2.ResumeLayout(false);
      this.panel2.PerformLayout();
      this.tabPage4.ResumeLayout(false);
      this.groupBox11.ResumeLayout(false);
      this.tabControl1.ResumeLayout(false);
      this.tabPage1.ResumeLayout(false);
      ((ISupportInitialize) this.CraftGrid).EndInit();
      this.tabPage2.ResumeLayout(false);
      this.tabPage2.PerformLayout();
      this.groupBox9.ResumeLayout(false);
      this.groupBox9.PerformLayout();
      this.tabPage5.ResumeLayout(false);
      this.groupBox12.ResumeLayout(false);
      this.groupBox12.PerformLayout();
      this.panel3.ResumeLayout(false);
      this.tabPage6.ResumeLayout(false);
      this.tabPage6.PerformLayout();
      ((ISupportInitialize) this.pbSkill3Icon).EndInit();
      ((ISupportInitialize) this.pbSkill2Icon).EndInit();
      ((ISupportInitialize) this.pbSkill1Icon).EndInit();
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.slideLeftRight.EndInit();
      this.slideUpDown.EndInit();
      this.slideZoom.EndInit();
      this.ModPanel.ResumeLayout(false);
      this.ModPanel.PerformLayout();
      ((ISupportInitialize) this.pictureBox1).EndInit();
      this.statusStrip1.ResumeLayout(false);
      this.statusStrip1.PerformLayout();
      this.groupBox6.ResumeLayout(false);
      this.groupBox6.PerformLayout();
      this.groupBox14.ResumeLayout(false);
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
