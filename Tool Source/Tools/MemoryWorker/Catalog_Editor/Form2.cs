// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.Catalog_Editor.Form2
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using LcDevPack_TeamDamonA.Properties;
using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.Catalog_Editor
{
  public class Form2 : Form
  {
    public static Connection connection = new Connection();
    private string Host = Form2.connection.Settings.SqlHost;
    private string User = Form2.connection.Settings.SqlUser;
    private string Password = Form2.connection.Settings.SqlPassword;
    private string Database = Form2.connection.Settings.SqlDatabase;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    private ExportLodHandle exportLodHandle = new ExportLodHandle();
    private string Episode = AffinityEditor.connection.Settings.Episode;
    public static List<string> Menu_Item = new List<string>();
    private static byte[] key = new byte[0];
    public static Encoding encoding = Encoding.GetEncoding(1252);
    public static List<ItemMallContainer> MallProducts = new List<ItemMallContainer>();
    private Encoding ascii = Encoding.GetEncoding(1252);
    private IContainer components = (IContainer) null;
    private int LangNum;
    public static string openedfile;
    private Button bt_AddRecord;
    private Button bt_DeleteRecord;
    private Button buttonItemDelete;
    private Button bt_SaveRecord;
    private CheckBox checkBoxEn;
    private ToolStripMenuItem fileToolStripMenuItem;
    private GroupBox groupBox1;
    private Label label1;
    private Label label10;
    private Label label11;
    private Label label12;
    private Label label13;
    private Label label14;
    private Label label2;
    private Label label3;
    private Label label4;
    private Label label5;
    private Label label9;
    private ListBox listBoxItems;
    private ListBox listBoxPackets;
    private MenuStrip menuStrip1;
    private ToolStripMenuItem openToolStripMenuItem;
    private ToolStripMenuItem saveAslodToolStripMenuItem;
    private TextBox textBoxCash;
    private TextBox textBoxCat;
    private TextBox textBoxicon;
    private TextBox textBoxLevel;
    private TextBox textBoxName;
    private TextBox textBoxOption;
    private TextBox textBoxProducktID;
    private TextBox textBoxSearch;
    private StatusStrip statusStrip1;
    private GroupBox groupBox3;
    private CheckBox checkBox_active;
    private GroupBox groupBox4;
    private RadioButton radioButton1;
    private RadioButton radioButton2;
    private RadioButton radioButton3;
    private Label label6;
    private RadioButton radioButton4;
    private GroupBox groupBox6;
    private TextBox textBox3;
    private Button Category_6;
    private Button Category_5;
    private Button Category_1;
    private Button Category_4;
    private Button Category_2;
    private Button Category_3;
    private GroupBox groupBox7;
    private OpenFileDialog openFileDialog1;
    private TextBox textBox4;
    private NumericUpDown textBoxItemID;
    private NumericUpDown textBoxPlus;
    private PictureBox pictureBox_req0;
    private TextBox textBox2;
    private Button button1;
    private Button button13;
    private Button button12;
    private Button button11;
    private Button button10;
    private Button button9;
    private Button button8;
    private Button BtnAddItem;
    private ToolStripMenuItem mySQLToolStripMenuItem;
    private ToolStripMenuItem saveAsSQLToolStripMenuItem;
    private NumericUpDown textBoxAmout;
    private RadioButton radioButton10;
    private RadioButton radioButton9;
    private RadioButton radioButton8;
    private RadioButton radioButton7;
    private RadioButton radioButton6;
    private RadioButton radioButton5;
    private ToolStripStatusLabel toolSS;
    private TextBox richTextBoxDesc;
    private string Path_strItem;
    private ToolStripMenuItem AdditionalFilesToolStripMenuItem;
    private PictureBox pictureBox1;
    private NumericUpDown textBox1;
    private ComboBox cbox_Language;
    private ToolStripMenuItem DeleteNonActiveToolStripMenuItem;
    private ToolStripMenuItem CreateSqlNamesToolStripMenuItem;
    private ToolStripMenuItem AddFromOtherFileToolStripMenuItem;
    private Label label7;
    private PictureBox pictureBox2;
    private Button BtnUseItemNameAndDerc;
    private string Path_itemAll;

    public Form2() => this.InitializeComponent();

    private void buttonAddItem_Click(object sender, EventArgs e)
    {
    }

    private void addcatalog_Click(object sender, EventArgs e)
    {
    }

    private void buttonCoplvlroduct_Click(object sender, EventArgs e)
    {
      if (this.listBoxPackets.SelectedIndex == -1)
        return;
      int num = Form2.MallProducts.Max<ItemMallContainer>((Func<ItemMallContainer, int>) (p => p.PackID)) + 1;
      ItemMallContainer itemMallContainer = new ItemMallContainer();
      itemMallContainer.PackID = num;
      itemMallContainer.Cat = 0;
      itemMallContainer.Price = 0;
      itemMallContainer.data4 = 0;
      itemMallContainer.data5 = 0;
      itemMallContainer.Enabled = (byte) 0;
      itemMallContainer.Name = Form2.encoding.GetBytes(Language.get("New record", this.LangNum));
      itemMallContainer.descr = Form2.encoding.GetBytes("");
      itemMallContainer.PkgAmount = 0;
      itemMallContainer.Items = new List<tMallItem>();
      tMallItem tMallItem = new tMallItem();
      itemMallContainer.ItemIcon = 0;
      this.listBoxPackets.Items.Add((object) (itemMallContainer.PackID.ToString() + " - " + Form2.encoding.GetString(itemMallContainer.Name)));
      Form2.MallProducts.Add(itemMallContainer);
      this.listBoxPackets.SelectedIndex = this.listBoxPackets.Items.Count - 1;
    }

    private void buttonDelProduct_Click(object sender, EventArgs e)
    {
      int id = this.GetIDFromList();
      int index = Form2.MallProducts.FindIndex((Predicate<ItemMallContainer>) (p => p.PackID.Equals(id)));
      if (this.listBoxPackets.SelectedIndex == -1 || index == -1 || MessageBox.Show(Language.get("Are you sure you want to delete this entry?", this.LangNum), "", MessageBoxButtons.YesNo) != DialogResult.Yes)
        return;
      Form2.MallProducts.RemoveAt(index);
      this.listBoxPackets.Items.Remove(this.listBoxPackets.SelectedItem);
    }

    private void buttonItemDelete_Click(object sender, EventArgs e)
    {
      int id = this.GetIDFromList();
      int index = Form2.MallProducts.FindIndex((Predicate<ItemMallContainer>) (p => p.PackID.Equals(id)));
      int int32 = Convert.ToInt32(this.listBoxItems.SelectedIndex);
      if (this.listBoxPackets.SelectedIndex == -1 || index == -1 || int32 == -1 || MessageBox.Show(Language.get("Are you sure you want to delete this entry?", this.LangNum), "", MessageBoxButtons.YesNo) != DialogResult.Yes)
        return;
      --Form2.MallProducts[index].PkgAmount;
      Form2.MallProducts[index].Items.RemoveAt(int32);
      this.listBoxPackets.Items[this.listBoxPackets.SelectedIndex] = (object) (this.textBoxProducktID.Text + " - " + this.textBoxName.Text);
    }

    private void buttonSaveChanges_Click(object sender, EventArgs e)
    {
      if (this.listBoxPackets.SelectedIndex == -1)
        return;
      Predicate<ItemMallContainer> match = (Predicate<ItemMallContainer>) (i => i.PackID.Equals(Convert.ToInt32(this.textBoxProducktID.Text)));
      int index1 = Form2.MallProducts.FindIndex(match);
      int Item = Convert.ToInt32(this.listBoxPackets.SelectedItem.ToString().Split('-')[0]);
      int index2 = Form2.MallProducts.FindIndex((Predicate<ItemMallContainer>) (a => a.PackID.Equals(Item)));
      if (index1 != -1 && Convert.ToInt32(this.textBoxProducktID.Text) != Form2.MallProducts[index2].PackID)
        return;
      Form2.MallProducts[index2].PackID = Convert.ToInt32(this.textBoxProducktID.Text);
      Form2.MallProducts[index2].Cat = Convert.ToInt32(this.textBoxCat.Text);
      Form2.MallProducts[index2].Price = Convert.ToInt32(this.textBoxCash.Text);
      Form2.MallProducts[index2].data4 = Convert.ToInt32(this.textBox1.Text);
      Form2.MallProducts[index2].data5 = Convert.ToInt32(this.textBox2.Text);
      Form2.MallProducts[index2].Enabled = !this.checkBoxEn.Checked ? (byte) 0 : (byte) 1;
      Form2.MallProducts[index2].Name = Form2.encoding.GetBytes(this.textBoxName.Text);
      Form2.MallProducts[index2].descr = Form2.encoding.GetBytes(this.richTextBoxDesc.Text);
      Form2.MallProducts[index2].PkgAmount = this.listBoxItems.Items.Count;
      if (this.listBoxItems.SelectedIndex != -1)
      {
        int selectedIndex = this.listBoxItems.SelectedIndex;
        Form2.MallProducts[index2].Items[selectedIndex].ItemID = Convert.ToInt32(this.textBoxItemID.Text);
        Form2.MallProducts[index2].Items[selectedIndex].Level = Convert.ToInt32(this.textBoxLevel.Text);
        Form2.MallProducts[index2].Items[selectedIndex].Plus = Convert.ToInt32(this.textBoxPlus.Text);
        Form2.MallProducts[index2].Items[selectedIndex].Option = Convert.ToInt32(this.textBoxOption.Text);
        Form2.MallProducts[index2].Items[selectedIndex].Amount = Convert.ToInt32(this.textBoxAmout.Text);
      }
      Form2.MallProducts[index2].ItemIcon = Convert.ToInt32(this.textBoxicon.Text);
      int selectedIndex1 = this.listBoxItems.SelectedIndex;
      this.listBoxPackets.Items[this.listBoxPackets.SelectedIndex] = (object) (this.textBoxProducktID.Text + " - " + this.textBoxName.Text);
      this.listBoxItems.SelectedIndex = selectedIndex1;
      this.toolSS.Text = Language.get("Record saved.", this.LangNum) + " ID - " + Form2.MallProducts[index2].PackID.ToString();
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
      this.openToolStripMenuItem = new ToolStripMenuItem();
      this.saveAslodToolStripMenuItem = new ToolStripMenuItem();
      this.mySQLToolStripMenuItem = new ToolStripMenuItem();
      this.saveAsSQLToolStripMenuItem = new ToolStripMenuItem();
      this.CreateSqlNamesToolStripMenuItem = new ToolStripMenuItem();
      this.AdditionalFilesToolStripMenuItem = new ToolStripMenuItem();
      this.DeleteNonActiveToolStripMenuItem = new ToolStripMenuItem();
      this.AddFromOtherFileToolStripMenuItem = new ToolStripMenuItem();
      this.listBoxPackets = new ListBox();
      this.groupBox1 = new GroupBox();
      this.pictureBox2 = new PictureBox();
      this.textBox1 = new NumericUpDown();
      this.pictureBox1 = new PictureBox();
      this.label6 = new Label();
      this.textBoxicon = new TextBox();
      this.label9 = new Label();
      this.richTextBoxDesc = new TextBox();
      this.label4 = new Label();
      this.textBoxCash = new TextBox();
      this.checkBoxEn = new CheckBox();
      this.textBoxName = new TextBox();
      this.textBoxProducktID = new TextBox();
      this.label2 = new Label();
      this.label1 = new Label();
      this.label3 = new Label();
      this.listBoxItems = new ListBox();
      this.textBoxSearch = new TextBox();
      this.label5 = new Label();
      this.textBoxCat = new TextBox();
      this.bt_SaveRecord = new Button();
      this.label10 = new Label();
      this.textBoxLevel = new TextBox();
      this.textBoxOption = new TextBox();
      this.label11 = new Label();
      this.label12 = new Label();
      this.label13 = new Label();
      this.label14 = new Label();
      this.buttonItemDelete = new Button();
      this.bt_AddRecord = new Button();
      this.bt_DeleteRecord = new Button();
      this.statusStrip1 = new StatusStrip();
      this.toolSS = new ToolStripStatusLabel();
      this.groupBox3 = new GroupBox();
      this.BtnUseItemNameAndDerc = new Button();
      this.textBoxAmout = new NumericUpDown();
      this.BtnAddItem = new Button();
      this.pictureBox_req0 = new PictureBox();
      this.textBoxPlus = new NumericUpDown();
      this.textBox4 = new TextBox();
      this.textBoxItemID = new NumericUpDown();
      this.checkBox_active = new CheckBox();
      this.groupBox4 = new GroupBox();
      this.button13 = new Button();
      this.button12 = new Button();
      this.button11 = new Button();
      this.button10 = new Button();
      this.button9 = new Button();
      this.button8 = new Button();
      this.button1 = new Button();
      this.radioButton1 = new RadioButton();
      this.radioButton2 = new RadioButton();
      this.radioButton3 = new RadioButton();
      this.radioButton4 = new RadioButton();
      this.groupBox6 = new GroupBox();
      this.textBox3 = new TextBox();
      this.Category_6 = new Button();
      this.Category_5 = new Button();
      this.Category_1 = new Button();
      this.Category_4 = new Button();
      this.Category_2 = new Button();
      this.Category_3 = new Button();
      this.groupBox7 = new GroupBox();
      this.textBox2 = new TextBox();
      this.radioButton10 = new RadioButton();
      this.radioButton9 = new RadioButton();
      this.radioButton8 = new RadioButton();
      this.radioButton7 = new RadioButton();
      this.radioButton6 = new RadioButton();
      this.radioButton5 = new RadioButton();
      this.openFileDialog1 = new OpenFileDialog();
      this.cbox_Language = new ComboBox();
      this.label7 = new Label();
      this.menuStrip1.SuspendLayout();
      this.groupBox1.SuspendLayout();
      ((ISupportInitialize) this.pictureBox2).BeginInit();
      this.textBox1.BeginInit();
      ((ISupportInitialize) this.pictureBox1).BeginInit();
      this.statusStrip1.SuspendLayout();
      this.groupBox3.SuspendLayout();
      this.textBoxAmout.BeginInit();
      ((ISupportInitialize) this.pictureBox_req0).BeginInit();
      this.textBoxPlus.BeginInit();
      this.textBoxItemID.BeginInit();
      this.groupBox4.SuspendLayout();
      this.groupBox6.SuspendLayout();
      this.groupBox7.SuspendLayout();
      this.SuspendLayout();
      this.menuStrip1.BackColor = SystemColors.ControlLight;
      this.menuStrip1.Enabled = false;
      this.menuStrip1.Items.AddRange(new ToolStripItem[5]
      {
        (ToolStripItem) this.fileToolStripMenuItem,
        (ToolStripItem) this.mySQLToolStripMenuItem,
        (ToolStripItem) this.AdditionalFilesToolStripMenuItem,
        (ToolStripItem) this.DeleteNonActiveToolStripMenuItem,
        (ToolStripItem) this.AddFromOtherFileToolStripMenuItem
      });
      this.menuStrip1.Location = new Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new Size(955, 24);
      this.menuStrip1.TabIndex = 0;
      this.menuStrip1.Text = "menuStrip1";
      this.menuStrip1.ItemClicked += new ToolStripItemClickedEventHandler(this.menuStrip1_ItemClicked);
      this.fileToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[2]
      {
        (ToolStripItem) this.openToolStripMenuItem,
        (ToolStripItem) this.saveAslodToolStripMenuItem
      });
      this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
      this.fileToolStripMenuItem.Size = new Size(37, 20);
      this.fileToolStripMenuItem.Text = "File";
      this.fileToolStripMenuItem.Click += new EventHandler(this.fileToolStripMenuItem_Click);
      this.openToolStripMenuItem.Name = "openToolStripMenuItem";
      this.openToolStripMenuItem.Size = new Size(103, 22);
      this.openToolStripMenuItem.Text = "Open";
      this.openToolStripMenuItem.Click += new EventHandler(this.openToolStripMenuItem_Click);
      this.saveAslodToolStripMenuItem.Name = "saveAslodToolStripMenuItem";
      this.saveAslodToolStripMenuItem.Size = new Size(103, 22);
      this.saveAslodToolStripMenuItem.Text = "Save";
      this.saveAslodToolStripMenuItem.Click += new EventHandler(this.saveAslodToolStripMenuItem_Click);
      this.mySQLToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[2]
      {
        (ToolStripItem) this.saveAsSQLToolStripMenuItem,
        (ToolStripItem) this.CreateSqlNamesToolStripMenuItem
      });
      this.mySQLToolStripMenuItem.Name = "mySQLToolStripMenuItem";
      this.mySQLToolStripMenuItem.Size = new Size(57, 20);
      this.mySQLToolStripMenuItem.Text = "mySQL";
      this.saveAsSQLToolStripMenuItem.Name = "saveAsSQLToolStripMenuItem";
      this.saveAsSQLToolStripMenuItem.Size = new Size(164, 22);
      this.saveAsSQLToolStripMenuItem.Text = "Create SQL File";
      this.saveAsSQLToolStripMenuItem.Click += new EventHandler(this.saveAsSQLToolStripMenuItem_Click);
      this.CreateSqlNamesToolStripMenuItem.Name = "CreateSqlNamesToolStripMenuItem";
      this.CreateSqlNamesToolStripMenuItem.Size = new Size(164, 22);
      this.CreateSqlNamesToolStripMenuItem.Text = "Create sql names";
      this.CreateSqlNamesToolStripMenuItem.Click += new EventHandler(this.CreateSqlNamesToolStripMenuItem_Click);
      this.AdditionalFilesToolStripMenuItem.Name = "AdditionalFilesToolStripMenuItem";
      this.AdditionalFilesToolStripMenuItem.Size = new Size(70, 20);
      this.AdditionalFilesToolStripMenuItem.Text = "Add. Files";
      this.AdditionalFilesToolStripMenuItem.Click += new EventHandler(this.AdditionalFilesToolStripMenuItem_Click);
      this.DeleteNonActiveToolStripMenuItem.Name = "DeleteNonActiveToolStripMenuItem";
      this.DeleteNonActiveToolStripMenuItem.Size = new Size(107, 20);
      this.DeleteNonActiveToolStripMenuItem.Text = "Delete not active";
      this.DeleteNonActiveToolStripMenuItem.Click += new EventHandler(this.DeleteNonActiveToolStripMenuItem_Click);
      this.AddFromOtherFileToolStripMenuItem.Name = "AddFromOtherFileToolStripMenuItem";
      this.AddFromOtherFileToolStripMenuItem.Size = new Size(133, 20);
      this.AddFromOtherFileToolStripMenuItem.Text = "Add from another file";
      this.AddFromOtherFileToolStripMenuItem.Click += new EventHandler(this.AddFromOtherFileToolStripMenuItem_Click);
      this.listBoxPackets.Enabled = false;
      this.listBoxPackets.ForeColor = System.Drawing.Color.Black;
      this.listBoxPackets.FormattingEnabled = true;
      this.listBoxPackets.Location = new Point(12, 135);
      this.listBoxPackets.Name = "listBoxPackets";
      this.listBoxPackets.Size = new Size(231, 329);
      this.listBoxPackets.TabIndex = 1;
      this.listBoxPackets.DrawItem += new DrawItemEventHandler(this.lbList_DrawItem);
      this.listBoxPackets.SelectedIndexChanged += new EventHandler(this.listBoxPackets_SelectedIndexChanged);
      this.groupBox1.Controls.Add((Control) this.pictureBox2);
      this.groupBox1.Controls.Add((Control) this.textBox1);
      this.groupBox1.Controls.Add((Control) this.pictureBox1);
      this.groupBox1.Controls.Add((Control) this.label6);
      this.groupBox1.Controls.Add((Control) this.textBoxicon);
      this.groupBox1.Controls.Add((Control) this.label9);
      this.groupBox1.Controls.Add((Control) this.richTextBoxDesc);
      this.groupBox1.Controls.Add((Control) this.label4);
      this.groupBox1.Controls.Add((Control) this.textBoxCash);
      this.groupBox1.Controls.Add((Control) this.checkBoxEn);
      this.groupBox1.Controls.Add((Control) this.textBoxName);
      this.groupBox1.Controls.Add((Control) this.textBoxProducktID);
      this.groupBox1.Controls.Add((Control) this.label2);
      this.groupBox1.Controls.Add((Control) this.label1);
      this.groupBox1.Controls.Add((Control) this.label3);
      this.groupBox1.Enabled = false;
      this.groupBox1.Location = new Point(249, 30);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(510, 219);
      this.groupBox1.TabIndex = 3;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Main";
      this.pictureBox2.Location = new Point(43, 156);
      this.pictureBox2.Name = "pictureBox2";
      this.pictureBox2.Size = new Size(24, 23);
      this.pictureBox2.TabIndex = 53;
      this.pictureBox2.TabStop = false;
      this.textBox1.Location = new Point(210, 157);
      this.textBox1.Maximum = new Decimal(new int[4]
      {
        100000000,
        0,
        0,
        0
      });
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(107, 20);
      this.textBox1.TabIndex = 52;
      this.pictureBox1.Location = new Point(463, 157);
      this.pictureBox1.Name = "pictureBox1";
      this.pictureBox1.Size = new Size(32, 32);
      this.pictureBox1.TabIndex = 52;
      this.pictureBox1.TabStop = false;
      this.label6.AutoSize = true;
      this.label6.Location = new Point(164, 160);
      this.label6.Name = "label6";
      this.label6.Size = new Size(28, 13);
      this.label6.TabIndex = 27;
      this.label6.Text = "Limit";
      this.label6.Click += new EventHandler(this.label6_Click);
      this.textBoxicon.Location = new Point(388, 157);
      this.textBoxicon.Name = "textBoxicon";
      this.textBoxicon.Size = new Size(69, 20);
      this.textBoxicon.TabIndex = 19;
      this.textBoxicon.TextChanged += new EventHandler(this.textBoxicon_TextChanged);
      this.label9.AutoSize = true;
      this.label9.Location = new Point(323, 160);
      this.label9.Name = "label9";
      this.label9.Size = new Size(47, 13);
      this.label9.TabIndex = 20;
      this.label9.Text = "ID Icons";
      this.richTextBoxDesc.Location = new Point(73, 71);
      this.richTextBoxDesc.Multiline = true;
      this.richTextBoxDesc.Name = "richTextBoxDesc";
      this.richTextBoxDesc.Size = new Size(423, 80);
      this.richTextBoxDesc.TabIndex = 26;
      this.label4.AutoSize = true;
      this.label4.Location = new Point(6, 74);
      this.label4.Name = "label4";
      this.label4.Size = new Size(60, 13);
      this.label4.TabIndex = 7;
      this.label4.Text = "Description";
      this.textBoxCash.Location = new Point(73, 157);
      this.textBoxCash.Name = "textBoxCash";
      this.textBoxCash.Size = new Size(85, 20);
      this.textBoxCash.TabIndex = 6;
      this.checkBoxEn.AccessibleRole = AccessibleRole.TitleBar;
      this.checkBoxEn.BackColor = System.Drawing.Color.Red;
      this.checkBoxEn.BackgroundImageLayout = ImageLayout.Center;
      this.checkBoxEn.CheckAlign = ContentAlignment.TopLeft;
      this.checkBoxEn.FlatStyle = FlatStyle.Flat;
      this.checkBoxEn.Location = new Point(73, 184);
      this.checkBoxEn.Margin = new Padding(30);
      this.checkBoxEn.Name = "checkBoxEn";
      this.checkBoxEn.Padding = new Padding(5, 2, 0, 0);
      this.checkBoxEn.Size = new Size(85, 20);
      this.checkBoxEn.TabIndex = 18;
      this.checkBoxEn.Text = "Available";
      this.checkBoxEn.TextAlign = ContentAlignment.TopLeft;
      this.checkBoxEn.UseVisualStyleBackColor = false;
      this.checkBoxEn.CheckedChanged += new EventHandler(this.checkBoxEn_CheckedChanged);
      this.textBoxName.Location = new Point(73, 45);
      this.textBoxName.Name = "textBoxName";
      this.textBoxName.Size = new Size(423, 20);
      this.textBoxName.TabIndex = 4;
      this.textBoxProducktID.Location = new Point(73, 19);
      this.textBoxProducktID.Name = "textBoxProducktID";
      this.textBoxProducktID.Size = new Size(69, 20);
      this.textBoxProducktID.TabIndex = 3;
      this.label2.AutoSize = true;
      this.label2.Location = new Point(6, 48);
      this.label2.Name = "label2";
      this.label2.Size = new Size(27, 13);
      this.label2.TabIndex = 1;
      this.label2.Text = "Title";
      this.label1.AutoSize = true;
      this.label1.Location = new Point(6, 22);
      this.label1.Name = "label1";
      this.label1.Size = new Size(37, 13);
      this.label1.TabIndex = 0;
      this.label1.Text = "ID Set";
      this.label3.AutoSize = true;
      this.label3.Location = new Point(6, 160);
      this.label3.Name = "label3";
      this.label3.Size = new Size(31, 13);
      this.label3.TabIndex = 2;
      this.label3.Text = "Price";
      this.listBoxItems.FormattingEnabled = true;
      this.listBoxItems.Location = new Point(6, 22);
      this.listBoxItems.Name = "listBoxItems";
      this.listBoxItems.Size = new Size(115, 173);
      this.listBoxItems.TabIndex = 4;
      this.listBoxItems.SelectedIndexChanged += new EventHandler(this.listBoxItems_SelectedIndexChanged);
      this.textBoxSearch.Enabled = false;
      this.textBoxSearch.Location = new Point(51, 42);
      this.textBoxSearch.Name = "textBoxSearch";
      this.textBoxSearch.Size = new Size(169, 20);
      this.textBoxSearch.TabIndex = 8;
      this.textBoxSearch.TextChanged += new EventHandler(this.textBoxSearch_TextChanged);
      this.label5.AutoSize = true;
      this.label5.Location = new Point(6, 45);
      this.label5.Name = "label5";
      this.label5.Size = new Size(41, 13);
      this.label5.TabIndex = 9;
      this.label5.Text = "Search";
      this.textBoxCat.Location = new Point(615, 475);
      this.textBoxCat.Name = "textBoxCat";
      this.textBoxCat.Size = new Size(110, 20);
      this.textBoxCat.TabIndex = 15;
      this.textBoxCat.Visible = false;
      this.textBoxCat.TextChanged += new EventHandler(this.textBoxCat_TextChanged);
      this.bt_SaveRecord.BackColor = System.Drawing.Color.LightCyan;
      this.bt_SaveRecord.Enabled = false;
      this.bt_SaveRecord.FlatStyle = FlatStyle.Flat;
      this.bt_SaveRecord.Image = (Image) Resources._08;
      this.bt_SaveRecord.ImageAlign = ContentAlignment.MiddleLeft;
      this.bt_SaveRecord.Location = new Point(835, 468);
      this.bt_SaveRecord.Name = "bt_SaveRecord";
      this.bt_SaveRecord.Size = new Size(83, 27);
      this.bt_SaveRecord.TabIndex = 67;
      this.bt_SaveRecord.Text = "      Save";
      this.bt_SaveRecord.UseVisualStyleBackColor = false;
      this.bt_SaveRecord.Click += new EventHandler(this.buttonSaveChanges_Click);
      this.label10.AutoSize = true;
      this.label10.Location = new Point((int) sbyte.MaxValue, 25);
      this.label10.Name = "label10";
      this.label10.Size = new Size(41, 13);
      this.label10.TabIndex = 8;
      this.label10.Text = "ID Item";
      this.textBoxLevel.Location = new Point(205, 126);
      this.textBoxLevel.Name = "textBoxLevel";
      this.textBoxLevel.Size = new Size(79, 20);
      this.textBoxLevel.TabIndex = 14;
      this.textBoxOption.Location = new Point(205, 74);
      this.textBoxOption.Name = "textBoxOption";
      this.textBoxOption.Size = new Size(79, 20);
      this.textBoxOption.TabIndex = 16;
      this.label11.AutoSize = true;
      this.label11.Location = new Point(129, 129);
      this.label11.Name = "label11";
      this.label11.Size = new Size(50, 13);
      this.label11.TabIndex = 17;
      this.label11.Text = "Item Flag";
      this.label12.AutoSize = true;
      this.label12.Location = new Point((int) sbyte.MaxValue, 50);
      this.label12.Name = "label12";
      this.label12.Size = new Size(48, 13);
      this.label12.TabIndex = 18;
      this.label12.Text = "Upgrade";
      this.label13.AutoSize = true;
      this.label13.Location = new Point((int) sbyte.MaxValue, 77);
      this.label13.Name = "label13";
      this.label13.Size = new Size(53, 13);
      this.label13.TabIndex = 19;
      this.label13.Text = "Unknown";
      this.label14.AutoSize = true;
      this.label14.Location = new Point((int) sbyte.MaxValue, 102);
      this.label14.Name = "label14";
      this.label14.Size = new Size(43, 13);
      this.label14.TabIndex = 21;
      this.label14.Text = "Amount";
      this.buttonItemDelete.BackColor = System.Drawing.Color.LightCoral;
      this.buttonItemDelete.FlatStyle = FlatStyle.Flat;
      this.buttonItemDelete.Image = (Image) Resources.delete;
      this.buttonItemDelete.ImageAlign = ContentAlignment.MiddleLeft;
      this.buttonItemDelete.Location = new Point(410, 171);
      this.buttonItemDelete.Name = "buttonItemDelete";
      this.buttonItemDelete.Size = new Size(77, 27);
      this.buttonItemDelete.TabIndex = 68;
      this.buttonItemDelete.Text = "    Delete";
      this.buttonItemDelete.UseVisualStyleBackColor = false;
      this.buttonItemDelete.Click += new EventHandler(this.buttonItemDelete_Click);
      this.bt_AddRecord.BackColor = System.Drawing.Color.Plum;
      this.bt_AddRecord.Enabled = false;
      this.bt_AddRecord.FlatStyle = FlatStyle.Flat;
      this.bt_AddRecord.Image = (Image) Resources.control_add_blue;
      this.bt_AddRecord.ImageAlign = ContentAlignment.MiddleLeft;
      this.bt_AddRecord.Location = new Point(12, 468);
      this.bt_AddRecord.Name = "bt_AddRecord";
      this.bt_AddRecord.Size = new Size(77, 27);
      this.bt_AddRecord.TabIndex = 66;
      this.bt_AddRecord.Text = "     Add";
      this.bt_AddRecord.UseVisualStyleBackColor = false;
      this.bt_AddRecord.Click += new EventHandler(this.buttonCoplvlroduct_Click);
      this.bt_DeleteRecord.BackColor = System.Drawing.Color.LightCoral;
      this.bt_DeleteRecord.Enabled = false;
      this.bt_DeleteRecord.FlatStyle = FlatStyle.Flat;
      this.bt_DeleteRecord.Image = (Image) Resources.delete;
      this.bt_DeleteRecord.ImageAlign = ContentAlignment.MiddleLeft;
      this.bt_DeleteRecord.Location = new Point(166, 468);
      this.bt_DeleteRecord.Name = "bt_DeleteRecord";
      this.bt_DeleteRecord.Size = new Size(77, 27);
      this.bt_DeleteRecord.TabIndex = 68;
      this.bt_DeleteRecord.Text = "    Delete";
      this.bt_DeleteRecord.UseVisualStyleBackColor = false;
      this.bt_DeleteRecord.Click += new EventHandler(this.buttonDelProduct_Click);
      this.statusStrip1.Enabled = false;
      this.statusStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.toolSS
      });
      this.statusStrip1.Location = new Point(0, 501);
      this.statusStrip1.Name = "statusStrip1";
      this.statusStrip1.Size = new Size(955, 22);
      this.statusStrip1.TabIndex = 26;
      this.statusStrip1.Text = "statusStrip1";
      this.toolSS.Name = "toolSS";
      this.toolSS.Size = new Size(0, 17);
      this.groupBox3.Controls.Add((Control) this.BtnUseItemNameAndDerc);
      this.groupBox3.Controls.Add((Control) this.textBoxAmout);
      this.groupBox3.Controls.Add((Control) this.BtnAddItem);
      this.groupBox3.Controls.Add((Control) this.pictureBox_req0);
      this.groupBox3.Controls.Add((Control) this.textBoxPlus);
      this.groupBox3.Controls.Add((Control) this.textBox4);
      this.groupBox3.Controls.Add((Control) this.textBoxItemID);
      this.groupBox3.Controls.Add((Control) this.listBoxItems);
      this.groupBox3.Controls.Add((Control) this.label10);
      this.groupBox3.Controls.Add((Control) this.textBoxLevel);
      this.groupBox3.Controls.Add((Control) this.buttonItemDelete);
      this.groupBox3.Controls.Add((Control) this.textBoxOption);
      this.groupBox3.Controls.Add((Control) this.label14);
      this.groupBox3.Controls.Add((Control) this.label11);
      this.groupBox3.Controls.Add((Control) this.label12);
      this.groupBox3.Controls.Add((Control) this.label13);
      this.groupBox3.Enabled = false;
      this.groupBox3.Location = new Point(249, (int) byte.MaxValue);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Size = new Size(510, 209);
      this.groupBox3.TabIndex = 27;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "Items";
      this.BtnUseItemNameAndDerc.BackColor = System.Drawing.Color.LightCyan;
      this.BtnUseItemNameAndDerc.Enabled = false;
      this.BtnUseItemNameAndDerc.FlatStyle = FlatStyle.Flat;
      this.BtnUseItemNameAndDerc.ImageAlign = ContentAlignment.MiddleLeft;
      this.BtnUseItemNameAndDerc.Location = new Point(225, 171);
      this.BtnUseItemNameAndDerc.Name = "BtnUseItemNameAndDerc";
      this.BtnUseItemNameAndDerc.Size = new Size(179, 27);
      this.BtnUseItemNameAndDerc.TabIndex = 67;
      this.BtnUseItemNameAndDerc.Text = "Use Item Name and Description";
      this.BtnUseItemNameAndDerc.UseVisualStyleBackColor = false;
      this.BtnUseItemNameAndDerc.Click += new EventHandler(this.BtnUseItemNameAndDerc_Click);
      this.textBoxAmout.Location = new Point(205, 100);
      this.textBoxAmout.Maximum = new Decimal(new int[4]
      {
        100000000,
        0,
        0,
        0
      });
      this.textBoxAmout.Name = "textBoxAmout";
      this.textBoxAmout.Size = new Size(79, 20);
      this.textBoxAmout.TabIndex = 51;
      this.BtnAddItem.BackColor = System.Drawing.Color.Plum;
      this.BtnAddItem.FlatStyle = FlatStyle.Flat;
      this.BtnAddItem.Image = (Image) Resources.control_add_blue;
      this.BtnAddItem.ImageAlign = ContentAlignment.MiddleLeft;
      this.BtnAddItem.Location = new Point(142, 171);
      this.BtnAddItem.Name = "BtnAddItem";
      this.BtnAddItem.Size = new Size(77, 27);
      this.BtnAddItem.TabIndex = 66;
      this.BtnAddItem.Text = "     Add";
      this.BtnAddItem.UseVisualStyleBackColor = false;
      this.BtnAddItem.Click += new EventHandler(this.button14_Click);
      this.pictureBox_req0.Location = new Point(290, 47);
      this.pictureBox_req0.Name = "pictureBox_req0";
      this.pictureBox_req0.Size = new Size(32, 32);
      this.pictureBox_req0.TabIndex = 49;
      this.pictureBox_req0.TabStop = false;
      this.textBoxPlus.Location = new Point(205, 48);
      this.textBoxPlus.Maximum = new Decimal(new int[4]
      {
        100000000,
        0,
        0,
        0
      });
      this.textBoxPlus.Name = "textBoxPlus";
      this.textBoxPlus.Size = new Size(79, 20);
      this.textBoxPlus.TabIndex = 48;
      this.textBox4.Enabled = false;
      this.textBox4.Location = new Point(290, 21);
      this.textBox4.Name = "textBox4";
      this.textBox4.Size = new Size(206, 20);
      this.textBox4.TabIndex = 25;
      this.textBoxItemID.Location = new Point(205, 22);
      this.textBoxItemID.Maximum = new Decimal(new int[4]
      {
        100000000,
        0,
        0,
        0
      });
      this.textBoxItemID.Name = "textBoxItemID";
      this.textBoxItemID.Size = new Size(79, 20);
      this.textBoxItemID.TabIndex = 47;
      this.textBoxItemID.ValueChanged += new EventHandler(this.textBoxItemID_ValueChanged);
      this.checkBox_active.BackColor = SystemColors.ControlLight;
      this.checkBox_active.Location = new Point(9, 19);
      this.checkBox_active.Name = "checkBox_active";
      this.checkBox_active.Padding = new Padding(5, 2, 0, 0);
      this.checkBox_active.Size = new Size(211, 19);
      this.checkBox_active.TabIndex = 35;
      this.checkBox_active.Text = "Only show active";
      this.checkBox_active.UseVisualStyleBackColor = false;
      this.checkBox_active.CheckedChanged += new EventHandler(this.checkBox_active_CheckedChanged);
      this.groupBox4.Controls.Add((Control) this.button13);
      this.groupBox4.Controls.Add((Control) this.button12);
      this.groupBox4.Controls.Add((Control) this.button11);
      this.groupBox4.Controls.Add((Control) this.button10);
      this.groupBox4.Controls.Add((Control) this.button9);
      this.groupBox4.Controls.Add((Control) this.button8);
      this.groupBox4.Controls.Add((Control) this.button1);
      this.groupBox4.Controls.Add((Control) this.checkBox_active);
      this.groupBox4.Controls.Add((Control) this.textBoxSearch);
      this.groupBox4.Controls.Add((Control) this.label5);
      this.groupBox4.Location = new Point(12, 30);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Size = new Size(231, 99);
      this.groupBox4.TabIndex = 36;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "Fast access";
      this.button13.BackgroundImageLayout = ImageLayout.Center;
      this.button13.Location = new Point(195, 68);
      this.button13.Name = "button13";
      this.button13.Size = new Size(30, 25);
      this.button13.TabIndex = 63;
      this.button13.Text = "All";
      this.button13.UseVisualStyleBackColor = false;
      this.button13.Click += new EventHandler(this.button13_Click);
      this.button12.BackgroundImage = (Image) Resources._7;
      this.button12.BackgroundImageLayout = ImageLayout.Zoom;
      this.button12.FlatStyle = FlatStyle.Flat;
      this.button12.Location = new Point(164, 68);
      this.button12.Name = "button12";
      this.button12.Size = new Size(25, 25);
      this.button12.TabIndex = 62;
      this.button12.UseVisualStyleBackColor = false;
      this.button12.Click += new EventHandler(this.button12_Click);
      this.button11.BackgroundImage = (Image) Resources._6;
      this.button11.BackgroundImageLayout = ImageLayout.Zoom;
      this.button11.FlatStyle = FlatStyle.Flat;
      this.button11.Location = new Point(133, 68);
      this.button11.Name = "button11";
      this.button11.Size = new Size(25, 25);
      this.button11.TabIndex = 62;
      this.button11.UseVisualStyleBackColor = false;
      this.button11.Click += new EventHandler(this.button11_Click);
      this.button10.BackgroundImage = (Image) Resources._5;
      this.button10.BackgroundImageLayout = ImageLayout.Zoom;
      this.button10.FlatStyle = FlatStyle.Flat;
      this.button10.Location = new Point(102, 68);
      this.button10.Name = "button10";
      this.button10.Size = new Size(25, 25);
      this.button10.TabIndex = 62;
      this.button10.UseVisualStyleBackColor = false;
      this.button10.Click += new EventHandler(this.button10_Click);
      this.button9.BackgroundImage = (Image) Resources._4;
      this.button9.BackgroundImageLayout = ImageLayout.Zoom;
      this.button9.FlatStyle = FlatStyle.Flat;
      this.button9.Location = new Point(71, 68);
      this.button9.Name = "button9";
      this.button9.Size = new Size(25, 25);
      this.button9.TabIndex = 62;
      this.button9.UseVisualStyleBackColor = false;
      this.button9.Click += new EventHandler(this.button9_Click);
      this.button8.BackgroundImage = (Image) Resources._3;
      this.button8.BackgroundImageLayout = ImageLayout.Zoom;
      this.button8.FlatStyle = FlatStyle.Flat;
      this.button8.Location = new Point(40, 68);
      this.button8.Name = "button8";
      this.button8.Size = new Size(25, 25);
      this.button8.TabIndex = 62;
      this.button8.UseVisualStyleBackColor = false;
      this.button8.Click += new EventHandler(this.button8_Click);
      this.button1.BackgroundImage = (Image) Resources._2;
      this.button1.BackgroundImageLayout = ImageLayout.Zoom;
      this.button1.FlatStyle = FlatStyle.Flat;
      this.button1.Location = new Point(9, 68);
      this.button1.Name = "button1";
      this.button1.Size = new Size(25, 25);
      this.button1.TabIndex = 62;
      this.button1.UseVisualStyleBackColor = false;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.radioButton1.AutoSize = true;
      this.radioButton1.Location = new Point(15, 41);
      this.radioButton1.Name = "radioButton1";
      this.radioButton1.Size = new Size(47, 17);
      this.radioButton1.TabIndex = 38;
      this.radioButton1.TabStop = true;
      this.radioButton1.Text = "New";
      this.radioButton1.UseVisualStyleBackColor = true;
      this.radioButton1.CheckedChanged += new EventHandler(this.Type_ValueChanged);
      this.radioButton2.AutoSize = true;
      this.radioButton2.Location = new Point(15, 64);
      this.radioButton2.Name = "radioButton2";
      this.radioButton2.Size = new Size(61, 17);
      this.radioButton2.TabIndex = 39;
      this.radioButton2.TabStop = true;
      this.radioButton2.Text = "Popular";
      this.radioButton2.UseVisualStyleBackColor = true;
      this.radioButton2.CheckedChanged += new EventHandler(this.Type_ValueChanged);
      this.radioButton3.AutoSize = true;
      this.radioButton3.Location = new Point(15, 87);
      this.radioButton3.Name = "radioButton3";
      this.radioButton3.Size = new Size(67, 17);
      this.radioButton3.TabIndex = 40;
      this.radioButton3.TabStop = true;
      this.radioButton3.Text = "Discount";
      this.radioButton3.UseVisualStyleBackColor = true;
      this.radioButton3.CheckedChanged += new EventHandler(this.Type_ValueChanged);
      this.radioButton4.AutoSize = true;
      this.radioButton4.Location = new Point(15, 18);
      this.radioButton4.Name = "radioButton4";
      this.radioButton4.Size = new Size(87, 17);
      this.radioButton4.TabIndex = 41;
      this.radioButton4.TabStop = true;
      this.radioButton4.Text = "Not assigned";
      this.radioButton4.UseVisualStyleBackColor = true;
      this.radioButton4.CheckedChanged += new EventHandler(this.Type_ValueChanged);
      this.groupBox6.Controls.Add((Control) this.textBox3);
      this.groupBox6.Controls.Add((Control) this.Category_6);
      this.groupBox6.Controls.Add((Control) this.Category_5);
      this.groupBox6.Controls.Add((Control) this.Category_1);
      this.groupBox6.Controls.Add((Control) this.Category_4);
      this.groupBox6.Controls.Add((Control) this.Category_2);
      this.groupBox6.Controls.Add((Control) this.Category_3);
      this.groupBox6.Location = new Point(765, 316);
      this.groupBox6.Name = "groupBox6";
      this.groupBox6.Size = new Size(177, 148);
      this.groupBox6.TabIndex = 42;
      this.groupBox6.TabStop = false;
      this.groupBox6.Text = "Category";
      this.textBox3.Enabled = false;
      this.textBox3.Location = new Point(14, 110);
      this.textBox3.Name = "textBox3";
      this.textBox3.Size = new Size(149, 20);
      this.textBox3.TabIndex = 61;
      this.textBox3.TextAlign = HorizontalAlignment.Center;
      this.textBox3.TextChanged += new EventHandler(this.textBox3_TextChanged);
      this.Category_6.BackgroundImage = (Image) Resources._7;
      this.Category_6.BackgroundImageLayout = ImageLayout.Zoom;
      this.Category_6.FlatStyle = FlatStyle.Flat;
      this.Category_6.Location = new Point(111, 63);
      this.Category_6.Name = "Category_6";
      this.Category_6.Size = new Size(35, 35);
      this.Category_6.TabIndex = 49;
      this.Category_6.UseVisualStyleBackColor = false;
      this.Category_6.Click += new EventHandler(this.Category_6_Click);
      this.Category_5.BackgroundImage = (Image) Resources._6;
      this.Category_5.BackgroundImageLayout = ImageLayout.Zoom;
      this.Category_5.FlatStyle = FlatStyle.Flat;
      this.Category_5.Location = new Point(70, 63);
      this.Category_5.Name = "Category_5";
      this.Category_5.Size = new Size(35, 35);
      this.Category_5.TabIndex = 48;
      this.Category_5.UseVisualStyleBackColor = false;
      this.Category_5.Click += new EventHandler(this.Category_5_Click);
      this.Category_1.BackgroundImage = (Image) Resources._2;
      this.Category_1.BackgroundImageLayout = ImageLayout.Zoom;
      this.Category_1.FlatStyle = FlatStyle.Flat;
      this.Category_1.Location = new Point(29, 22);
      this.Category_1.Name = "Category_1";
      this.Category_1.Size = new Size(35, 35);
      this.Category_1.TabIndex = 44;
      this.Category_1.UseVisualStyleBackColor = false;
      this.Category_1.Click += new EventHandler(this.Category_1_Click);
      this.Category_4.BackgroundImage = (Image) Resources._5;
      this.Category_4.BackgroundImageLayout = ImageLayout.Zoom;
      this.Category_4.FlatStyle = FlatStyle.Flat;
      this.Category_4.Location = new Point(29, 63);
      this.Category_4.Name = "Category_4";
      this.Category_4.Size = new Size(35, 35);
      this.Category_4.TabIndex = 47;
      this.Category_4.UseVisualStyleBackColor = false;
      this.Category_4.Click += new EventHandler(this.Category_4_Click);
      this.Category_2.BackgroundImage = (Image) Resources._3;
      this.Category_2.BackgroundImageLayout = ImageLayout.Zoom;
      this.Category_2.FlatStyle = FlatStyle.Flat;
      this.Category_2.Location = new Point(70, 22);
      this.Category_2.Name = "Category_2";
      this.Category_2.Size = new Size(35, 35);
      this.Category_2.TabIndex = 45;
      this.Category_2.UseVisualStyleBackColor = false;
      this.Category_2.Click += new EventHandler(this.Category_2_Click);
      this.Category_3.BackgroundImage = (Image) Resources._4;
      this.Category_3.BackgroundImageLayout = ImageLayout.Zoom;
      this.Category_3.FlatStyle = FlatStyle.Flat;
      this.Category_3.Location = new Point(111, 22);
      this.Category_3.Name = "Category_3";
      this.Category_3.Size = new Size(35, 35);
      this.Category_3.TabIndex = 46;
      this.Category_3.UseVisualStyleBackColor = false;
      this.Category_3.Click += new EventHandler(this.Category_3_Click);
      this.groupBox7.Controls.Add((Control) this.textBox2);
      this.groupBox7.Controls.Add((Control) this.radioButton10);
      this.groupBox7.Controls.Add((Control) this.radioButton9);
      this.groupBox7.Controls.Add((Control) this.radioButton8);
      this.groupBox7.Controls.Add((Control) this.radioButton7);
      this.groupBox7.Controls.Add((Control) this.radioButton6);
      this.groupBox7.Controls.Add((Control) this.radioButton5);
      this.groupBox7.Controls.Add((Control) this.radioButton4);
      this.groupBox7.Controls.Add((Control) this.radioButton1);
      this.groupBox7.Controls.Add((Control) this.radioButton3);
      this.groupBox7.Controls.Add((Control) this.radioButton2);
      this.groupBox7.Location = new Point(765, 30);
      this.groupBox7.Name = "groupBox7";
      this.groupBox7.Size = new Size(177, 280);
      this.groupBox7.TabIndex = 43;
      this.groupBox7.TabStop = false;
      this.groupBox7.Text = "Type";
      this.textBox2.Location = new Point(15, 250);
      this.textBox2.Name = "textBox2";
      this.textBox2.Size = new Size(149, 20);
      this.textBox2.TabIndex = 47;
      this.textBox2.TextChanged += new EventHandler(this.textBox2_TextChanged_1);
      this.radioButton10.AutoSize = true;
      this.radioButton10.Enabled = false;
      this.radioButton10.Location = new Point(15, 225);
      this.radioButton10.Name = "radioButton10";
      this.radioButton10.Size = new Size(71, 17);
      this.radioButton10.TabIndex = 47;
      this.radioButton10.TabStop = true;
      this.radioButton10.Text = "Unknown";
      this.radioButton10.UseVisualStyleBackColor = true;
      this.radioButton9.AutoSize = true;
      this.radioButton9.Location = new Point(15, 202);
      this.radioButton9.Name = "radioButton9";
      this.radioButton9.Size = new Size(61, 17);
      this.radioButton9.TabIndex = 46;
      this.radioButton9.TabStop = true;
      this.radioButton9.Text = "Best - 5";
      this.radioButton9.UseVisualStyleBackColor = true;
      this.radioButton9.CheckedChanged += new EventHandler(this.Type_ValueChanged);
      this.radioButton8.AutoSize = true;
      this.radioButton8.Location = new Point(15, 179);
      this.radioButton8.Name = "radioButton8";
      this.radioButton8.Size = new Size(61, 17);
      this.radioButton8.TabIndex = 45;
      this.radioButton8.TabStop = true;
      this.radioButton8.Text = "Best - 4";
      this.radioButton8.UseVisualStyleBackColor = true;
      this.radioButton8.CheckedChanged += new EventHandler(this.Type_ValueChanged);
      this.radioButton7.AutoSize = true;
      this.radioButton7.Location = new Point(15, 156);
      this.radioButton7.Name = "radioButton7";
      this.radioButton7.Size = new Size(61, 17);
      this.radioButton7.TabIndex = 44;
      this.radioButton7.TabStop = true;
      this.radioButton7.Text = "Best - 3";
      this.radioButton7.UseVisualStyleBackColor = true;
      this.radioButton7.CheckedChanged += new EventHandler(this.Type_ValueChanged);
      this.radioButton6.AutoSize = true;
      this.radioButton6.Location = new Point(15, 133);
      this.radioButton6.Name = "radioButton6";
      this.radioButton6.Size = new Size(61, 17);
      this.radioButton6.TabIndex = 43;
      this.radioButton6.TabStop = true;
      this.radioButton6.Text = "Best - 2";
      this.radioButton6.UseVisualStyleBackColor = true;
      this.radioButton6.CheckedChanged += new EventHandler(this.Type_ValueChanged);
      this.radioButton5.AutoSize = true;
      this.radioButton5.Location = new Point(15, 110);
      this.radioButton5.Name = "radioButton5";
      this.radioButton5.Size = new Size(61, 17);
      this.radioButton5.TabIndex = 42;
      this.radioButton5.TabStop = true;
      this.radioButton5.Text = "Best - 1";
      this.radioButton5.UseVisualStyleBackColor = true;
      this.radioButton5.CheckedChanged += new EventHandler(this.Type_ValueChanged);
      this.openFileDialog1.FileName = "openFileDialog1";
      this.cbox_Language.FormattingEnabled = true;
      this.cbox_Language.Items.AddRange(new object[10]
      {
        (object) "Russian",
        (object) "English",
        (object) "Thai",
        (object) "German",
        (object) "France",
        (object) "Italian",
        (object) "Polish",
        (object) "Espanol",
        (object) "BRA",
        (object) "Mex"
      });
      this.cbox_Language.Location = new Point(833, 1);
      this.cbox_Language.Name = "cbox_Language";
      this.cbox_Language.Size = new Size(121, 21);
      this.cbox_Language.TabIndex = 111;
      this.cbox_Language.SelectedIndexChanged += new EventHandler(this.cbox_Language_SelectedIndexChanged);
      this.label7.AutoSize = true;
      this.label7.BackColor = System.Drawing.Color.Red;
      this.label7.ForeColor = SystemColors.ControlLightLight;
      this.label7.Location = new Point(733, 4);
      this.label7.Name = "label7";
      this.label7.Size = new Size(94, 13);
      this.label7.TabIndex = 112;
      this.label7.Text = "SELECT FIRST ->";
      this.AutoSizeMode = AutoSizeMode.GrowAndShrink;
      this.ClientSize = new Size(955, 523);
      this.Controls.Add((Control) this.label7);
      this.Controls.Add((Control) this.cbox_Language);
      this.Controls.Add((Control) this.textBoxCat);
      this.Controls.Add((Control) this.groupBox7);
      this.Controls.Add((Control) this.groupBox6);
      this.Controls.Add((Control) this.groupBox4);
      this.Controls.Add((Control) this.groupBox3);
      this.Controls.Add((Control) this.statusStrip1);
      this.Controls.Add((Control) this.bt_DeleteRecord);
      this.Controls.Add((Control) this.bt_AddRecord);
      this.Controls.Add((Control) this.bt_SaveRecord);
      this.Controls.Add((Control) this.groupBox1);
      this.Controls.Add((Control) this.listBoxPackets);
      this.Controls.Add((Control) this.menuStrip1);
      this.FormBorderStyle = FormBorderStyle.FixedSingle;
      this.MainMenuStrip = this.menuStrip1;
      this.MaximizeBox = false;
      this.Name = nameof (Form2);
      this.StartPosition = FormStartPosition.CenterScreen;
      this.Text = "Catalog Editor EP4";
      this.FormClosed += new FormClosedEventHandler(this.Form2_FormClosed);
      this.Load += new EventHandler(this.Form1_Load);
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      ((ISupportInitialize) this.pictureBox2).EndInit();
      this.textBox1.EndInit();
      ((ISupportInitialize) this.pictureBox1).EndInit();
      this.statusStrip1.ResumeLayout(false);
      this.statusStrip1.PerformLayout();
      this.groupBox3.ResumeLayout(false);
      this.groupBox3.PerformLayout();
      this.textBoxAmout.EndInit();
      ((ISupportInitialize) this.pictureBox_req0).EndInit();
      this.textBoxPlus.EndInit();
      this.textBoxItemID.EndInit();
      this.groupBox4.ResumeLayout(false);
      this.groupBox4.PerformLayout();
      this.groupBox6.ResumeLayout(false);
      this.groupBox6.PerformLayout();
      this.groupBox7.ResumeLayout(false);
      this.groupBox7.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();
    }

    private void listBoxItems_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (this.listBoxPackets.SelectedIndex == -1)
        return;
      int Item = Convert.ToInt32(this.listBoxPackets.SelectedItem.ToString().Split('-')[0]);
      int index1 = Form2.MallProducts.FindIndex((Predicate<ItemMallContainer>) (a => a.PackID.Equals(Item)));
      if (this.listBoxItems.SelectedIndex == -1)
        return;
      int Item2 = Convert.ToInt32(this.listBoxItems.SelectedItem.ToString().Split('-')[1]);
      int index2 = Form2.MallProducts[index1].Items.FindIndex((Predicate<tMallItem>) (a => a.ItemID.Equals(Item2)));
      this.textBoxItemID.Text = Form2.MallProducts[index1].Items[index2].ItemID.ToString();
      this.textBoxPlus.Text = Form2.MallProducts[index1].Items[index2].Plus.ToString();
      this.textBoxOption.Text = Form2.MallProducts[index1].Items[index2].Option.ToString();
      this.textBoxLevel.Text = Form2.MallProducts[index1].Items[index2].Level.ToString();
      this.textBoxAmout.Text = Form2.MallProducts[index1].Items[index2].Amount.ToString();
    }

    private void listBoxPackets_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (this.listBoxPackets.SelectedIndex == -1)
        return;
      this.textBoxItemID.Text = "0";
      this.textBoxPlus.Text = "0";
      this.textBoxOption.Text = "0";
      this.textBoxAmout.Text = "0";
      this.textBoxLevel.Text = "0";
      this.listBoxItems.Items.Clear();
      int Item = Convert.ToInt32(this.listBoxPackets.SelectedItem.ToString().Split('-')[0]);
      int index1 = Form2.MallProducts.FindIndex((Predicate<ItemMallContainer>) (a => a.PackID.Equals(Item)));
      this.textBoxProducktID.Text = Form2.MallProducts[index1].PackID.ToString();
      TextBox textBoxCat = this.textBoxCat;
      int num = Form2.MallProducts[index1].Cat;
      string str1 = num.ToString();
      textBoxCat.Text = str1;
      TextBox textBoxCash = this.textBoxCash;
      num = Form2.MallProducts[index1].Price;
      string str2 = num.ToString();
      textBoxCash.Text = str2;
      NumericUpDown textBox1 = this.textBox1;
      num = Form2.MallProducts[index1].data4;
      string str3 = num.ToString();
      textBox1.Text = str3;
      TextBox textBox2 = this.textBox2;
      num = Form2.MallProducts[index1].data5;
      string str4 = num.ToString();
      textBox2.Text = str4;
      if (Form2.MallProducts[index1].Enabled == (byte) 1)
      {
        this.checkBoxEn.Checked = true;
        this.checkBoxEn.BackColor = System.Drawing.Color.LimeGreen;
      }
      else
      {
        this.checkBoxEn.Checked = false;
        this.checkBoxEn.BackColor = System.Drawing.Color.Red;
      }
      this.textBoxName.Text = Form2.encoding.GetString(Form2.MallProducts[index1].Name);
      this.richTextBoxDesc.Text = Form2.encoding.GetString(Form2.MallProducts[index1].descr);
      for (int index2 = 0; index2 <= Form2.MallProducts[index1].PkgAmount - 1; ++index2)
        this.listBoxItems.Items.Add((object) ((index2 + 1).ToString() + " - " + Form2.MallProducts[index1].Items[index2].ItemID.ToString()));
      TextBox textBoxicon = this.textBoxicon;
      num = Form2.MallProducts[index1].ItemIcon;
      string str5 = num.ToString();
      textBoxicon.Text = str5;
      if (Form2.MallProducts[index1].PkgAmount == 0)
        return;
      this.listBoxItems.SelectedIndex = 0;
    }

    private void openToolStripMenuItem_Click(object sender, EventArgs e)
    {
      OpenFileDialog openFileDialog1 = new OpenFileDialog();
      openFileDialog1.Title = "Open catalog.lod";
      openFileDialog1.InitialDirectory = "";
      openFileDialog1.Filter = "catalog*.lod|catalog*.lod|All|*.*";
      if (openFileDialog1.ShowDialog() == DialogResult.Cancel)
        return;
      OpenFileDialog openFileDialog2 = new OpenFileDialog();
      openFileDialog2.Title = "Open strItem.lod";
      openFileDialog2.InitialDirectory = "";
      openFileDialog2.Filter = "strItem_*.lod|strItem_*.lod|All|*.*";
      if (openFileDialog2.ShowDialog() == DialogResult.Cancel)
        return;
      string directoryName = Path.GetDirectoryName(openFileDialog1.FileName);
      this.listBoxPackets.Items.Clear();
      Form2.MallProducts.Clear();
      this.FileOpen(openFileDialog1.FileName);
      this.ReadItem(directoryName + "\\itemAll.lod");
      strItem.LoadFromFile(openFileDialog2.FileName);
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
            itemAll.t_ItemAll tItemAll = new itemAll.t_ItemAll();
            tItemAll.ItemID = binaryReader.ReadInt32();
            tItemAll.JobFlag = binaryReader.ReadInt32();
            tItemAll.Weight = binaryReader.ReadInt32();
            tItemAll.MaxUse = binaryReader.ReadInt32();
            tItemAll.Level = binaryReader.ReadInt32();
            tItemAll.Flag = binaryReader.ReadInt64();
            tItemAll.Position = binaryReader.ReadInt32();
            tItemAll.Type = binaryReader.ReadInt32();
            tItemAll.SubType = binaryReader.ReadInt32();
            int[] numArray1 = new int[10];
            int[] numArray2 = new int[10];
            for (int index = 0; index < 10; ++index)
            {
              numArray1[index] = binaryReader.ReadInt32();
              numArray2[index] = binaryReader.ReadInt32();
            }
            tItemAll.CraftItemID = numArray1;
            tItemAll.CraftItemAmount = numArray2;
            tItemAll.Need_SSkill1_Id = binaryReader.ReadInt32();
            tItemAll.Need_SSkill1_Level = binaryReader.ReadInt32();
            tItemAll.Need_SSkill2_Id = binaryReader.ReadInt32();
            tItemAll.Need_SSkill2_Level = binaryReader.ReadInt32();
            tItemAll.TexID = binaryReader.ReadInt32();
            tItemAll.TexRow = binaryReader.ReadInt32();
            tItemAll.TexCol = binaryReader.ReadInt32();
            tItemAll.Num0 = binaryReader.ReadInt32();
            tItemAll.Num1 = binaryReader.ReadInt32();
            tItemAll.Num2 = binaryReader.ReadInt32();
            tItemAll.Num3 = binaryReader.ReadInt32();
            tItemAll.Price = binaryReader.ReadInt32();
            tItemAll.Set1 = binaryReader.ReadInt32();
            tItemAll.Set2 = binaryReader.ReadInt32();
            tItemAll.Set3 = binaryReader.ReadInt32();
            tItemAll.Set4 = binaryReader.ReadInt32();
            tItemAll.Set5 = binaryReader.ReadInt32();
            tItemAll.Smc = Encoding.GetEncoding("ISO-8859-1").GetString(binaryReader.ReadBytes(64));
            tItemAll.Effect1 = Encoding.GetEncoding("ISO-8859-1").GetString(binaryReader.ReadBytes(32));
            tItemAll.Effect2 = Encoding.GetEncoding("ISO-8859-1").GetString(binaryReader.ReadBytes(32));
            tItemAll.Effect3 = Encoding.GetEncoding("ISO-8859-1").GetString(binaryReader.ReadBytes(32));
            tItemAll.JewelOptionType = binaryReader.ReadInt32();
            tItemAll.JewelOptionLevel = binaryReader.ReadInt32();
            int[] numArray3 = new int[10];
            int[] numArray4 = new int[10];
            for (int index = 0; index < 10; ++index)
              numArray3[index] = binaryReader.ReadInt32();
            for (int index = 0; index < 10; ++index)
              numArray4[index] = binaryReader.ReadInt32();
            tItemAll.rareOptionType = numArray3;
            tItemAll.rareOptionChance = numArray4;
            tItemAll.syndicate_type = binaryReader.ReadInt32();
            tItemAll.syndicate_grade = binaryReader.ReadInt32();
            tItemAll.fortuneIndex = binaryReader.ReadInt32();
            tItemAll.castleWar = (int) binaryReader.ReadByte();
            itemAll.ItemList.Add(tItemAll);
            Form2.Menu_Item.Add(tItemAll.ItemID.ToString() + " - " + strItem.GetNameFromID(tItemAll.ItemID));
          }
          else
            binaryReader.BaseStream.Position = binaryReader.BaseStream.Length;
        }
      }
    }

    public void FileOpen(string filename)
    {
      try
      {
        using (BinaryReader binaryReader = new BinaryReader((Stream) File.Open(filename, FileMode.Open)))
        {
          binaryReader.ReadInt32();
          while (binaryReader.BaseStream.Position < binaryReader.BaseStream.Length)
          {
            ItemMallContainer itemMallContainer = new ItemMallContainer();
            int num1 = itemMallContainer.PackID = binaryReader.ReadInt32();
            itemMallContainer.Cat = binaryReader.ReadInt32();
            itemMallContainer.Price = binaryReader.ReadInt32();
            itemMallContainer.data4 = binaryReader.ReadInt32();
            itemMallContainer.data5 = binaryReader.ReadInt32();
            itemMallContainer.Enabled = binaryReader.ReadByte();
            byte[] bytes = itemMallContainer.Name = binaryReader.ReadBytes(binaryReader.ReadInt32());
            itemMallContainer.descr = binaryReader.ReadBytes(binaryReader.ReadInt32());
            int num2 = itemMallContainer.PkgAmount = binaryReader.ReadInt32();
            itemMallContainer.Items = new List<tMallItem>();
            for (int index = 0; index <= num2 - 1; ++index)
            {
              tMallItem tMallItem = new tMallItem()
              {
                ItemID = binaryReader.ReadInt32(),
                Level = binaryReader.ReadInt32(),
                Plus = binaryReader.ReadInt32(),
                Option = binaryReader.ReadInt32(),
                Amount = binaryReader.ReadInt32()
              };
              itemMallContainer.Items.Add(tMallItem);
            }
            itemMallContainer.ItemIcon = binaryReader.ReadInt32();
            Form2.MallProducts.Add(itemMallContainer);
            this.listBoxPackets.Items.Add((object) (num1.ToString() + " - " + Form2.encoding.GetString(bytes)));
            this.textBoxSearch.Enabled = true;
            this.listBoxPackets.Enabled = true;
            this.bt_AddRecord.Enabled = true;
            this.bt_DeleteRecord.Enabled = true;
            this.groupBox1.Enabled = true;
            this.groupBox3.Enabled = true;
            this.bt_SaveRecord.Enabled = true;
          }
          this.listBoxPackets.SelectedIndex = -1;
        }
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message, "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
    }

    private void saveAslodToolStripMenuItem_Click(object sender, EventArgs e)
    {
      SaveFileDialog saveFileDialog1 = new SaveFileDialog();
      saveFileDialog1.Filter = "catalog|catalog*.lod";
      SaveFileDialog saveFileDialog2 = saveFileDialog1;
      if (saveFileDialog2.ShowDialog() == DialogResult.Cancel)
        return;
      try
      {
        int num1 = Form2.MallProducts.Count<ItemMallContainer>();
        BinaryWriter binaryWriter = new BinaryWriter((Stream) new FileStream(saveFileDialog2.FileName, FileMode.Create));
        binaryWriter.Write(num1);
        for (int index1 = 0; index1 < Form2.MallProducts.Count<ItemMallContainer>(); ++index1)
        {
          binaryWriter.Write(Form2.MallProducts[index1].PackID);
          binaryWriter.Write(Form2.MallProducts[index1].Cat);
          binaryWriter.Write(Form2.MallProducts[index1].Price);
          binaryWriter.Write(Form2.MallProducts[index1].data4);
          binaryWriter.Write(Form2.MallProducts[index1].data5);
          binaryWriter.Write(Form2.MallProducts[index1].Enabled);
          binaryWriter.Write(Form2.MallProducts[index1].Name.Length);
          binaryWriter.Write(Form2.MallProducts[index1].Name);
          binaryWriter.Write(Form2.MallProducts[index1].descr.Length);
          binaryWriter.Write(Form2.MallProducts[index1].descr);
          binaryWriter.Write(Form2.MallProducts[index1].PkgAmount);
          for (int index2 = 0; index2 <= Form2.MallProducts[index1].PkgAmount - 1; ++index2)
          {
            binaryWriter.Write(Form2.MallProducts[index1].Items[index2].ItemID);
            binaryWriter.Write(Form2.MallProducts[index1].Items[index2].Level);
            binaryWriter.Write(Form2.MallProducts[index1].Items[index2].Plus);
            binaryWriter.Write(Form2.MallProducts[index1].Items[index2].Option);
            binaryWriter.Write(Form2.MallProducts[index1].Items[index2].Amount);
          }
          binaryWriter.Write(Form2.MallProducts[index1].ItemIcon);
        }
        binaryWriter.Close();
        int num2 = (int) MessageBox.Show("File Saved ");
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message, "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
    }

    private void saveAsSQLToolStripMenuItem_Click(object sender, EventArgs e)
    {
      SaveFileDialog saveFileDialog1 = new SaveFileDialog();
      saveFileDialog1.Filter = "SQL Data|*.sql";
      saveFileDialog1.Title = "Save SQL Export";
      saveFileDialog1.FileName = "t_catalog";
      SaveFileDialog saveFileDialog2 = saveFileDialog1;
      if (saveFileDialog2.ShowDialog() == DialogResult.Cancel)
        return;
      try
      {
        StreamWriter streamWriter1 = new StreamWriter((Stream) File.Create(saveFileDialog2.FileName));
        streamWriter1.WriteLine("delete from t_catalog;");
        streamWriter1.WriteLine("delete from t_catalog_1;");
        streamWriter1.WriteLine("delete from t_ct_item;");
        streamWriter1.WriteLine("delete from t_ct_item_1;");
        foreach (ItemMallContainer mallProduct in Form2.MallProducts)
        {
          int num = mallProduct.Cat;
          string str = num.ToString()[0].ToString() + "0000";
          streamWriter1.WriteLine("INSERT INTO t_catalog (a_ctid, a_category, a_Type, a_subType, a_cash, a_mileage, a_enable, a_flag) VALUES");
          StreamWriter streamWriter2 = streamWriter1;
          object[] objArray1 = new object[15];
          objArray1[0] = (object) "(";
          objArray1[1] = (object) mallProduct.PackID;
          objArray1[2] = (object) ", ";
          objArray1[3] = (object) str.ToString();
          objArray1[4] = (object) ", ";
          object[] objArray2 = objArray1;
          object[] objArray3 = objArray2;
          num = mallProduct.Cat;
          objArray3[5] = (object) num.ToString();
          objArray2[6] = (object) ", ";
          object[] objArray4 = objArray2;
          num = mallProduct.Cat;
          objArray4[7] = (object) num.ToString();
          objArray2[8] = (object) ", ";
          object[] objArray5 = objArray2;
          num = mallProduct.Price;
          objArray5[9] = (object) num.ToString();
          objArray2[10] = (object) ", 0, ";
          objArray2[11] = (object) mallProduct.Enabled.ToString();
          objArray2[12] = (object) ", ";
          object[] objArray6 = objArray2;
          num = mallProduct.data5;
          objArray6[13] = (object) num.ToString();
          objArray2[14] = (object) ");";
          streamWriter2.WriteLine(string.Concat(objArray2));
          for (int index = 0; mallProduct.PkgAmount != index; ++index)
          {
            streamWriter1.WriteLine("INSERT INTO t_ct_item (a_index, a_ctid, a_item_idx, a_item_flag, a_item_plus, a_item_option, a_item_num) VALUES");
            StreamWriter streamWriter3 = streamWriter1;
            object[] objArray7 = new object[13];
            objArray7[0] = (object) "(NULL, ";
            object[] objArray8 = objArray7;
            object[] objArray9 = objArray8;
            num = mallProduct.PackID;
            objArray9[1] = (object) num.ToString();
            objArray8[2] = (object) ", ";
            object[] objArray10 = objArray8;
            num = mallProduct.Items[index].ItemID;
            objArray10[3] = (object) num.ToString();
            objArray8[4] = (object) ", ";
            object[] objArray11 = objArray8;
            num = mallProduct.Items[index].Level;
            objArray11[5] = (object) num.ToString();
            objArray8[6] = (object) ", ";
            object[] objArray12 = objArray8;
            num = mallProduct.Items[index].Plus;
            objArray12[7] = (object) num.ToString();
            objArray8[8] = (object) ", ";
            object[] objArray13 = objArray8;
            num = mallProduct.Items[index].Option;
            objArray13[9] = (object) num.ToString();
            objArray8[10] = (object) ", ";
            object[] objArray14 = objArray8;
            num = mallProduct.Items[index].Amount;
            objArray14[11] = (object) num.ToString();
            objArray8[12] = (object) ");";
            streamWriter3.WriteLine(string.Concat(objArray8));
          }
        }
        streamWriter1.Dispose();
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message, "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
    }

    private void textBoxSearch_TextChanged(object sender, EventArgs e)
    {
      this.listBoxPackets.Items.Clear();
      int num = Form2.MallProducts.Count<ItemMallContainer>();
      for (int index = 0; index < num; ++index)
      {
        int packId = Form2.MallProducts[index].PackID;
        string str = Form2.encoding.GetString(Form2.MallProducts[index].Name);
        if ((packId.ToString() + " - " + str).IndexOf(this.textBoxSearch.Text) != -1)
          this.listBoxPackets.Items.Add((object) (packId.ToString() + " - " + str));
      }
    }

    private void Form1_Load(object sender, EventArgs e)
    {
    }

    private void Form2_FormClosed(object sender, FormClosedEventArgs e)
    {
      if (this.cbox_Language.SelectedIndex == -1)
        return;
      RegistryKey subKey = Registry.CurrentUser.CreateSubKey("LC_Path");
      subKey.SetValue("Language", (object) Convert.ToString(this.cbox_Language.SelectedIndex));
      subKey.Close();
    }

    private void richTextBoxDesc_TextChanged(object sender, EventArgs e)
    {
    }

    private void textBox2_TextChanged(object sender, EventArgs e)
    {
      if (this.textBox2.Text == "0")
        this.radioButton4.Checked = true;
      if (this.textBox2.Text == "1")
        this.radioButton1.Checked = true;
      if (this.textBox2.Text == "2")
        this.radioButton2.Checked = true;
      if (!(this.textBox2.Text == "3"))
        return;
      this.radioButton3.Checked = true;
    }

    private void textBoxCat_TextChanged(object sender, EventArgs e)
    {
      for (int index = 1; index <= 6; ++index)
        (this.Controls.Find("Category_" + index.ToString(), true)[0] as Button).BackColor = SystemColors.Control;
      if (Convert.ToInt32(this.textBoxCat.Text) >= 20000 && Convert.ToInt32(this.textBoxCat.Text) < 30000)
      {
        this.Category_1.BackColor = System.Drawing.Color.Lime;
        this.textBox3.Text = Language.get("Popular", this.LangNum);
      }
      if (Convert.ToInt32(this.textBoxCat.Text) >= 30000 && Convert.ToInt32(this.textBoxCat.Text) < 40000)
      {
        this.Category_2.BackColor = System.Drawing.Color.Lime;
        this.textBox3.Text = Language.get("Potions and scrolls", this.LangNum);
      }
      if (Convert.ToInt32(this.textBoxCat.Text) >= 40000 && Convert.ToInt32(this.textBoxCat.Text) < 50000)
      {
        this.Category_3.BackColor = System.Drawing.Color.Lime;
        this.textBox3.Text = Language.get("Equipment", this.LangNum);
      }
      if (Convert.ToInt32(this.textBoxCat.Text) >= 50000 && Convert.ToInt32(this.textBoxCat.Text) < 60000)
      {
        this.Category_4.BackColor = System.Drawing.Color.Lime;
        this.textBox3.Text = Language.get("Pets", this.LangNum);
      }
      if (Convert.ToInt32(this.textBoxCat.Text) >= 60000 && Convert.ToInt32(this.textBoxCat.Text) < 70000)
      {
        this.Category_5.BackColor = System.Drawing.Color.Lime;
        this.textBox3.Text = Language.get("Misc", this.LangNum);
      }
      if (Convert.ToInt32(this.textBoxCat.Text) < 70000 || Convert.ToInt32(this.textBoxCat.Text) >= 80000)
        return;
      this.Category_6.BackColor = System.Drawing.Color.Lime;
      this.textBox3.Text = Language.get("Sets", this.LangNum);
    }

    private void menuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
    {
    }

    private void checkBox_active_CheckedChanged(object sender, EventArgs e)
    {
      if (this.checkBox_active.CheckState == CheckState.Checked)
      {
        this.listBoxPackets.Items.Clear();
        int num = Form2.MallProducts.Count<ItemMallContainer>();
        for (int index = 0; index < num; ++index)
        {
          if (Form2.MallProducts[index].Enabled == (byte) 1)
            this.listBoxPackets.Items.Add((object) (Form2.MallProducts[index].PackID.ToString() + " - " + Form2.encoding.GetString(Form2.MallProducts[index].Name)));
        }
      }
      else
      {
        this.listBoxPackets.Items.Clear();
        int num = Form2.MallProducts.Count<ItemMallContainer>();
        for (int index = 0; index < num; ++index)
          this.listBoxPackets.Items.Add((object) (Form2.MallProducts[index].PackID.ToString() + " - " + Form2.encoding.GetString(Form2.MallProducts[index].Name)));
      }
      this.toolSS.Text = "";
    }

    private void checkBox1_CheckedChanged(object sender, EventArgs e)
    {
      if (this.checkBox_active.CheckState == CheckState.Checked)
      {
        this.listBoxPackets.Items.Clear();
        int num = Form2.MallProducts.Count<ItemMallContainer>();
        for (int index = 0; index < num; ++index)
        {
          if (Form2.MallProducts[index].data5 == 1)
            this.listBoxPackets.Items.Add((object) (Form2.MallProducts[index].PackID.ToString() + " - " + Form2.encoding.GetString(Form2.MallProducts[index].Name)));
        }
      }
      else
      {
        this.listBoxPackets.Items.Clear();
        int num = Form2.MallProducts.Count<ItemMallContainer>();
        for (int index = 0; index < num; ++index)
          this.listBoxPackets.Items.Add((object) (Form2.MallProducts[index].PackID.ToString() + " - " + Form2.encoding.GetString(Form2.MallProducts[index].Name)));
      }
    }

    private void checkBox2_CheckedChanged(object sender, EventArgs e)
    {
      if (this.checkBox_active.CheckState == CheckState.Checked)
      {
        this.listBoxPackets.Items.Clear();
        int num = Form2.MallProducts.Count<ItemMallContainer>();
        for (int index = 0; index < num; ++index)
        {
          if (Form2.MallProducts[index].data5 == 2)
            this.listBoxPackets.Items.Add((object) (Form2.MallProducts[index].PackID.ToString() + " - " + Form2.encoding.GetString(Form2.MallProducts[index].Name)));
        }
      }
      else
      {
        this.listBoxPackets.Items.Clear();
        int num = Form2.MallProducts.Count<ItemMallContainer>();
        for (int index = 0; index < num; ++index)
          this.listBoxPackets.Items.Add((object) (Form2.MallProducts[index].PackID.ToString() + " - " + Form2.encoding.GetString(Form2.MallProducts[index].Name)));
      }
    }

    private void checkBox3_CheckedChanged(object sender, EventArgs e)
    {
      if (this.checkBox_active.CheckState == CheckState.Checked)
      {
        this.listBoxPackets.Items.Clear();
        int num = Form2.MallProducts.Count<ItemMallContainer>();
        for (int index = 0; index < num; ++index)
        {
          if (Form2.MallProducts[index].data5 == 3)
            this.listBoxPackets.Items.Add((object) (Form2.MallProducts[index].PackID.ToString() + " - " + Form2.encoding.GetString(Form2.MallProducts[index].Name)));
        }
      }
      else
      {
        this.listBoxPackets.Items.Clear();
        int num = Form2.MallProducts.Count<ItemMallContainer>();
        for (int index = 0; index < num; ++index)
          this.listBoxPackets.Items.Add((object) (Form2.MallProducts[index].PackID.ToString() + " - " + Form2.encoding.GetString(Form2.MallProducts[index].Name)));
      }
    }

    private void Type_ValueChanged(object sender, EventArgs e)
    {
      if (this.radioButton4.Checked)
        this.textBox2.Text = "0";
      if (this.radioButton1.Checked)
        this.textBox2.Text = "1";
      if (this.radioButton2.Checked)
        this.textBox2.Text = "2";
      if (this.radioButton3.Checked)
        this.textBox2.Text = "3";
      if (this.radioButton5.Checked)
        this.textBox2.Text = "8";
      if (this.radioButton6.Checked)
        this.textBox2.Text = "16";
      if (this.radioButton7.Checked)
        this.textBox2.Text = "32";
      if (this.radioButton8.Checked)
        this.textBox2.Text = "64";
      if (!this.radioButton9.Checked)
        return;
      this.textBox2.Text = "128";
    }

    private void NoColor_Category(object sender, EventArgs e)
    {
      this.Category_1.BackColor = SystemColors.Control;
      this.Category_2.BackColor = SystemColors.Control;
      this.Category_3.BackColor = SystemColors.Control;
      this.Category_4.BackColor = SystemColors.Control;
      this.Category_5.BackColor = SystemColors.Control;
      this.Category_6.BackColor = SystemColors.Control;
    }

    private void Category1_Click(object sender, EventArgs e)
    {
      this.Category_1.BackColor = System.Drawing.Color.Lime;
    }

    private void Category2_Click(object sender, EventArgs e)
    {
      this.Category_2.BackColor = System.Drawing.Color.Lime;
    }

    private void Category3_Click(object sender, EventArgs e)
    {
      this.Category_3.BackColor = System.Drawing.Color.Lime;
    }

    private void Category4_Click(object sender, EventArgs e)
    {
      this.Category_4.BackColor = System.Drawing.Color.Lime;
    }

    private void Category5_Click(object sender, EventArgs e)
    {
      this.Category_5.BackColor = System.Drawing.Color.Lime;
    }

    private void Category6_Click(object sender, EventArgs e)
    {
      this.Category_6.BackColor = System.Drawing.Color.Lime;
    }

    private void textBoxicon_TextChanged(object sender, EventArgs e)
    {
      int value = Convert.ToInt32(this.textBoxicon.Text);
      if (value > 0)
      {
        int index = itemAll.ItemList.FindIndex((Predicate<itemAll.t_ItemAll>) (p => p.ItemID.Equals(value)));
        if (index == -1)
          return;
        this.pictureBox1.Image = (Image) itemAll.Icon((object) itemAll.ItemList[index].ItemID);
      }
      else
        this.pictureBox1.Image = (Image) null;
    }

    private void textBoxItemID_ValueChanged(object sender, EventArgs e)
    {
      int value = Convert.ToInt32(this.textBoxItemID.Value);
      if (value > 0)
      {
        int index = itemAll.ItemList.FindIndex((Predicate<itemAll.t_ItemAll>) (p => p.ItemID.Equals(value)));
        if (index == -1)
          return;
        this.pictureBox_req0.Image = (Image) itemAll.Icon((object) itemAll.ItemList[index].ItemID);
        this.textBox4.Text = strItem.GetNameFromID(itemAll.ItemList[index].ItemID);
      }
      else
      {
        this.pictureBox_req0.Image = (Image) null;
        this.textBox4.Text = "";
      }
    }

    private void textBox3_TextChanged(object sender, EventArgs e)
    {
    }

    private void textBox2_TextChanged_1(object sender, EventArgs e)
    {
      switch (this.textBox2.Text)
      {
        case "0":
          this.radioButton4.Checked = true;
          break;
        case "1":
          this.radioButton1.Checked = true;
          break;
        case "128":
          this.radioButton9.Checked = true;
          break;
        case "16":
          this.radioButton6.Checked = true;
          break;
        case "2":
          this.radioButton2.Checked = true;
          break;
        case "3":
          this.radioButton3.Checked = true;
          break;
        case "32":
          this.radioButton7.Checked = true;
          break;
        case "64":
          this.radioButton8.Checked = true;
          break;
        case "8":
          this.radioButton5.Checked = true;
          break;
        default:
          this.radioButton10.Checked = true;
          break;
      }
    }

    private void button1_Click(object sender, EventArgs e)
    {
      this.listBoxPackets.Items.Clear();
      int num = Form2.MallProducts.Count<ItemMallContainer>();
      int packId;
      for (int index = 0; index < num; ++index)
      {
        if (this.checkBox_active.Checked)
        {
          if (Form2.MallProducts[index].Cat >= 20000 && Form2.MallProducts[index].Cat < 30000 && Form2.MallProducts[index].Enabled == (byte) 1)
          {
            ListBox.ObjectCollection items = this.listBoxPackets.Items;
            packId = Form2.MallProducts[index].PackID;
            string str = packId.ToString() + " - " + Form2.encoding.GetString(Form2.MallProducts[index].Name);
            items.Add((object) str);
          }
        }
        else if (Form2.MallProducts[index].Cat >= 20000 && Form2.MallProducts[index].Cat < 30000)
        {
          ListBox.ObjectCollection items = this.listBoxPackets.Items;
          packId = Form2.MallProducts[index].PackID;
          string str = packId.ToString() + " - " + Form2.encoding.GetString(Form2.MallProducts[index].Name);
          items.Add((object) str);
        }
      }
      this.toolSS.Text = Language.get("Search filtering: Popular", this.LangNum);
    }

    private void button8_Click(object sender, EventArgs e)
    {
      this.listBoxPackets.Items.Clear();
      int num = Form2.MallProducts.Count<ItemMallContainer>();
      int packId;
      for (int index = 0; index < num; ++index)
      {
        if (this.checkBox_active.Checked)
        {
          if (Form2.MallProducts[index].Cat >= 30000 && Form2.MallProducts[index].Cat < 40000 && Form2.MallProducts[index].Enabled == (byte) 1)
          {
            ListBox.ObjectCollection items = this.listBoxPackets.Items;
            packId = Form2.MallProducts[index].PackID;
            string str = packId.ToString() + " - " + Form2.encoding.GetString(Form2.MallProducts[index].Name);
            items.Add((object) str);
          }
        }
        else if (Form2.MallProducts[index].Cat >= 30000 && Form2.MallProducts[index].Cat < 40000)
        {
          ListBox.ObjectCollection items = this.listBoxPackets.Items;
          packId = Form2.MallProducts[index].PackID;
          string str = packId.ToString() + " - " + Form2.encoding.GetString(Form2.MallProducts[index].Name);
          items.Add((object) str);
        }
      }
      this.toolSS.Text = Language.get("Search filtering: Potions and scrolls", this.LangNum);
    }

    private void button9_Click(object sender, EventArgs e)
    {
      this.listBoxPackets.Items.Clear();
      int num = Form2.MallProducts.Count<ItemMallContainer>();
      int packId;
      for (int index = 0; index < num; ++index)
      {
        if (this.checkBox_active.Checked)
        {
          if (Form2.MallProducts[index].Cat >= 40000 && Form2.MallProducts[index].Cat < 50000 && Form2.MallProducts[index].Enabled == (byte) 1)
          {
            ListBox.ObjectCollection items = this.listBoxPackets.Items;
            packId = Form2.MallProducts[index].PackID;
            string str = packId.ToString() + " - " + Form2.encoding.GetString(Form2.MallProducts[index].Name);
            items.Add((object) str);
          }
        }
        else if (Form2.MallProducts[index].Cat >= 40000 && Form2.MallProducts[index].Cat < 50000)
        {
          ListBox.ObjectCollection items = this.listBoxPackets.Items;
          packId = Form2.MallProducts[index].PackID;
          string str = packId.ToString() + " - " + Form2.encoding.GetString(Form2.MallProducts[index].Name);
          items.Add((object) str);
        }
      }
      this.toolSS.Text = Language.get("Search filtering: Equipment", this.LangNum);
    }

    private void button10_Click(object sender, EventArgs e)
    {
      this.listBoxPackets.Items.Clear();
      int num = Form2.MallProducts.Count<ItemMallContainer>();
      int packId;
      for (int index = 0; index < num; ++index)
      {
        if (this.checkBox_active.Checked)
        {
          if (Form2.MallProducts[index].Cat >= 50000 && Form2.MallProducts[index].Cat < 60000 && Form2.MallProducts[index].Enabled == (byte) 1)
          {
            ListBox.ObjectCollection items = this.listBoxPackets.Items;
            packId = Form2.MallProducts[index].PackID;
            string str = packId.ToString() + " - " + Form2.encoding.GetString(Form2.MallProducts[index].Name);
            items.Add((object) str);
          }
        }
        else if (Form2.MallProducts[index].Cat >= 50000 && Form2.MallProducts[index].Cat < 60000)
        {
          ListBox.ObjectCollection items = this.listBoxPackets.Items;
          packId = Form2.MallProducts[index].PackID;
          string str = packId.ToString() + " - " + Form2.encoding.GetString(Form2.MallProducts[index].Name);
          items.Add((object) str);
        }
      }
      this.toolSS.Text = Language.get("Search filtering: Pets", this.LangNum);
    }

    private void button11_Click(object sender, EventArgs e)
    {
      this.listBoxPackets.Items.Clear();
      int num = Form2.MallProducts.Count<ItemMallContainer>();
      int packId;
      for (int index = 0; index < num; ++index)
      {
        if (this.checkBox_active.Checked)
        {
          if (Form2.MallProducts[index].Cat >= 60000 && Form2.MallProducts[index].Cat < 70000 && Form2.MallProducts[index].Enabled == (byte) 1)
          {
            ListBox.ObjectCollection items = this.listBoxPackets.Items;
            packId = Form2.MallProducts[index].PackID;
            string str = packId.ToString() + " - " + Form2.encoding.GetString(Form2.MallProducts[index].Name);
            items.Add((object) str);
          }
        }
        else if (Form2.MallProducts[index].Cat >= 60000 && Form2.MallProducts[index].Cat < 70000)
        {
          ListBox.ObjectCollection items = this.listBoxPackets.Items;
          packId = Form2.MallProducts[index].PackID;
          string str = packId.ToString() + " - " + Form2.encoding.GetString(Form2.MallProducts[index].Name);
          items.Add((object) str);
        }
      }
      this.toolSS.Text = Language.get("Search filtering: Misc", this.LangNum);
    }

    private void button12_Click(object sender, EventArgs e)
    {
      this.listBoxPackets.Items.Clear();
      int num = Form2.MallProducts.Count<ItemMallContainer>();
      int packId;
      for (int index = 0; index < num; ++index)
      {
        if (this.checkBox_active.Checked)
        {
          if (Form2.MallProducts[index].Cat >= 70000 && Form2.MallProducts[index].Cat < 80000 && Form2.MallProducts[index].Enabled == (byte) 1)
          {
            ListBox.ObjectCollection items = this.listBoxPackets.Items;
            packId = Form2.MallProducts[index].PackID;
            string str = packId.ToString() + " - " + Form2.encoding.GetString(Form2.MallProducts[index].Name);
            items.Add((object) str);
          }
        }
        else if (Form2.MallProducts[index].Cat >= 70000 && Form2.MallProducts[index].Cat < 80000)
        {
          ListBox.ObjectCollection items = this.listBoxPackets.Items;
          packId = Form2.MallProducts[index].PackID;
          string str = packId.ToString() + " - " + Form2.encoding.GetString(Form2.MallProducts[index].Name);
          items.Add((object) str);
        }
      }
      this.toolSS.Text = Language.get("Search filtering: Sets", this.LangNum);
    }

    private void button13_Click(object sender, EventArgs e)
    {
      this.listBoxPackets.Items.Clear();
      int num = Form2.MallProducts.Count<ItemMallContainer>();
      int packId;
      for (int index = 0; index < num; ++index)
      {
        if (this.checkBox_active.Checked)
        {
          if (Form2.MallProducts[index].Enabled == (byte) 1)
          {
            ListBox.ObjectCollection items = this.listBoxPackets.Items;
            packId = Form2.MallProducts[index].PackID;
            string str = packId.ToString() + " - " + Form2.encoding.GetString(Form2.MallProducts[index].Name);
            items.Add((object) str);
          }
        }
        else
        {
          ListBox.ObjectCollection items = this.listBoxPackets.Items;
          packId = Form2.MallProducts[index].PackID;
          string str = packId.ToString() + " - " + Form2.encoding.GetString(Form2.MallProducts[index].Name);
          items.Add((object) str);
        }
      }
      this.toolSS.Text = "";
    }

    private void checkBoxEn_CheckedChanged(object sender, EventArgs e)
    {
      if (this.checkBoxEn.Checked)
        this.checkBoxEn.BackColor = System.Drawing.Color.LimeGreen;
      if (this.checkBoxEn.Checked)
        return;
      this.checkBoxEn.BackColor = System.Drawing.Color.Red;
    }

    public int GetIDFromList()
    {
      try
      {
        return Convert.ToInt32(this.listBoxPackets.Text.Split(' ')[0]);
      }
      catch
      {
        return 2;
      }
    }

    private void button14_Click(object sender, EventArgs e)
    {
      int idFromList = this.GetIDFromList();
      if (this.listBoxPackets.SelectedIndex == -1 || new ItemSearch(idFromList).ShowDialog() != DialogResult.OK)
        return;
      int selectedIndex = this.listBoxItems.SelectedIndex;
      this.listBoxPackets.Items[this.listBoxPackets.SelectedIndex] = (object) (this.textBoxProducktID.Text + " - " + this.textBoxName.Text);
      this.listBoxItems.SelectedIndex = selectedIndex;
    }

    private void lbList_DrawItem(object sender, DrawItemEventArgs e)
    {
      int index1 = Form2.MallProducts.Count<ItemMallContainer>();
      for (int index2 = 0; index2 < index1; ++index2)
      {
        if (Form2.MallProducts[index1].data5 == 8 || Form2.MallProducts[index1].data5 == 16 || Form2.MallProducts[index1].data5 == 32 || Form2.MallProducts[index1].data5 == 64 || Form2.MallProducts[index1].data5 == 128)
          this.listBoxPackets.Items[e.Index] = (object) System.Drawing.Color.Red;
      }
    }

    private void AdditionalFilesToolStripMenuItem_Click(object sender, EventArgs e)
    {
      int num = (int) new EditRegistrlvlath().ShowDialog();
    }

    private void Category_1_Click(object sender, EventArgs e) => this.textBoxCat.Text = "20000";

    private void Category_2_Click(object sender, EventArgs e) => this.textBoxCat.Text = "30100";

    private void Category_3_Click(object sender, EventArgs e) => this.textBoxCat.Text = "40200";

    private void Category_4_Click(object sender, EventArgs e) => this.textBoxCat.Text = "50200";

    private void Category_5_Click(object sender, EventArgs e) => this.textBoxCat.Text = "60100";

    private void Category_6_Click(object sender, EventArgs e) => this.textBoxCat.Text = "70000";

    private void label6_Click(object sender, EventArgs e)
    {
    }

    private void cbox_Language_SelectedIndexChanged(object sender, EventArgs e)
    {
      int selectedIndex = this.listBoxPackets.SelectedIndex;
      switch (this.cbox_Language.Text)
      {
        case "BRA":
          this.LangNum = 8;
          Form2.encoding = Encoding.GetEncoding("Windows-1252");
          break;
        case "English":
          this.LangNum = 1;
          Form2.encoding = Encoding.GetEncoding("Windows-1252");
          break;
        case "Espanol":
          this.LangNum = 7;
          Form2.encoding = Encoding.GetEncoding("Windows-1252");
          break;
        case "France":
          this.LangNum = 4;
          Form2.encoding = Encoding.GetEncoding("Windows-1252");
          break;
        case "German":
          this.LangNum = 3;
          Form2.encoding = Encoding.GetEncoding("Windows-1252");
          break;
        case "Italian":
          this.LangNum = 5;
          Form2.encoding = Encoding.GetEncoding("Windows-1252");
          break;
        case "Mex":
          this.LangNum = 9;
          Form2.encoding = Encoding.GetEncoding("Windows-1252");
          break;
        case "Polish":
          this.LangNum = 6;
          Form2.encoding = Encoding.GetEncoding("Windows-1250");
          break;
        case "Russian":
          this.LangNum = 0;
          Form2.encoding = Encoding.GetEncoding(1252);
          break;
        case "Thai":
          this.LangNum = 2;
          Form2.encoding = Encoding.GetEncoding("windows-874");
          break;
      }
      this.textBoxSearch.Enabled = true;
      this.listBoxPackets.Enabled = true;
      this.bt_AddRecord.Enabled = true;
      this.bt_DeleteRecord.Enabled = true;
      this.groupBox1.Enabled = true;
      this.groupBox3.Enabled = true;
      this.bt_SaveRecord.Enabled = true;
      this.fileToolStripMenuItem.Enabled = true;
      this.menuStrip1.Enabled = true;
      this.label7.Visible = false;
      this.Text = Language.get("Catalog Editor EP4", this.LangNum);
      this.fileToolStripMenuItem.Text = Language.get("File", this.LangNum);
      this.bt_AddRecord.Text = Language.get("Add", this.LangNum);
      this.BtnUseItemNameAndDerc.Text = Language.get("Use Item Name and Description", this.LangNum);
      this.bt_DeleteRecord.Text = Language.get("Delete", this.LangNum);
      this.BtnAddItem.Text = Language.get("Add", this.LangNum);
      this.buttonItemDelete.Text = Language.get("Delete", this.LangNum);
      this.bt_SaveRecord.Text = Language.get("Save", this.LangNum);
      this.openToolStripMenuItem.Text = Language.get("Open", this.LangNum);
      this.saveAslodToolStripMenuItem.Text = Language.get("Save", this.LangNum);
      this.AdditionalFilesToolStripMenuItem.Text = Language.get("Add. Files", this.LangNum);
      this.saveAsSQLToolStripMenuItem.Text = Language.get("Create SQL File", this.LangNum);
      this.CreateSqlNamesToolStripMenuItem.Text = Language.get("Create sql names", this.LangNum);
      this.groupBox1.Text = Language.get("Main", this.LangNum);
      this.groupBox7.Text = Language.get("of", this.LangNum);
      this.radioButton4.Text = Language.get("Not assigned", this.LangNum);
      this.radioButton1.Text = Language.get("New", this.LangNum);
      this.radioButton2.Text = Language.get("Popular", this.LangNum);
      this.radioButton3.Text = Language.get("Discount", this.LangNum);
      this.radioButton5.Text = Language.get("Best - 1", this.LangNum);
      this.radioButton6.Text = Language.get("Best - 2", this.LangNum);
      this.radioButton7.Text = Language.get("Best - 3", this.LangNum);
      this.radioButton8.Text = Language.get("Best - 4", this.LangNum);
      this.radioButton9.Text = Language.get("Best - 5", this.LangNum);
      this.radioButton10.Text = Language.get("Unknown", this.LangNum);
      this.groupBox4.Text = Language.get("Fast access", this.LangNum);
      this.checkBox_active.Text = Language.get("Only show active", this.LangNum);
      this.label5.Text = Language.get("Search", this.LangNum);
      this.groupBox3.Text = Language.get("Items", this.LangNum);
      this.label10.Text = Language.get("ID Item", this.LangNum);
      this.label12.Text = Language.get("Upgrade", this.LangNum);
      this.label13.Text = Language.get("Unknown", this.LangNum);
      this.label14.Text = Language.get("Amount", this.LangNum);
      this.groupBox6.Text = Language.get("Category", this.LangNum);
      this.label1.Text = Language.get("ID Set", this.LangNum);
      this.label2.Text = Language.get("Title", this.LangNum);
      this.label4.Text = Language.get("Description", this.LangNum);
      this.label3.Text = Language.get("Price", this.LangNum);
      this.label6.Text = Language.get("Limit", this.LangNum);
      this.label9.Text = Language.get("ID Icons", this.LangNum);
      this.checkBoxEn.Text = Language.get("Available", this.LangNum);
      this.AddFromOtherFileToolStripMenuItem.Text = Language.get("Add from another file", this.LangNum);
      this.DeleteNonActiveToolStripMenuItem.Text = Language.get("Delete not active", this.LangNum);
      this.listBoxPackets.SelectedIndex = selectedIndex;
    }

    private void fileToolStripMenuItem_Click(object sender, EventArgs e)
    {
    }

    private void DeleteNonActiveToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Form2.MallProducts.RemoveAll((Predicate<ItemMallContainer>) (a => a.Enabled != (byte) 1));
    }

    private void CreateSqlNamesToolStripMenuItem_Click(object sender, EventArgs e)
    {
      SaveFileDialog saveFileDialog1 = new SaveFileDialog();
      saveFileDialog1.Filter = "SQL Data|*.sql";
      saveFileDialog1.Title = "Save SQL Export";
      saveFileDialog1.FileName = "t_catalog_name";
      SaveFileDialog saveFileDialog2 = saveFileDialog1;
      if (saveFileDialog2.ShowDialog() == DialogResult.Cancel)
        return;
      try
      {
        StreamWriter streamWriter = new StreamWriter((Stream) File.Create(saveFileDialog2.FileName));
        foreach (ItemMallContainer mallProduct in Form2.MallProducts)
          streamWriter.WriteLine(string.Format("UPDATE t_catalog SET a_ctname = \"{0}\", a_ctdesc = \"{1}\" WHERE a_ctid = {2};", (object) Form2.encoding.GetString(mallProduct.Name).Replace("\"", "'"), (object) Form2.encoding.GetString(mallProduct.descr).Replace("\"", "'"), (object) mallProduct.PackID));
        streamWriter.Dispose();
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message, "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
    }

    private void AddFromOtherFileToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (new File2_F().ShowDialog() != DialogResult.OK)
        return;
      this.listBoxPackets.Items.Clear();
      int num = Form2.MallProducts.Count<ItemMallContainer>();
      for (int index = 0; index < num; ++index)
      {
        int packId = Form2.MallProducts[index].PackID;
        string str = Form2.encoding.GetString(Form2.MallProducts[index].Name);
        if ((packId.ToString() + " - " + str).IndexOf(this.textBoxSearch.Text) != -1)
          this.listBoxPackets.Items.Add((object) (packId.ToString() + " - " + str));
      }
    }

    private void BtnUseItemNameAndDerc_Click(object sender, EventArgs e)
    {
      int value = Convert.ToInt32(this.textBoxItemID.Value);
      if (value <= 0)
        return;
      int index = itemAll.ItemList.FindIndex((Predicate<itemAll.t_ItemAll>) (p => p.ItemID.Equals(value)));
      if (index == -1)
        return;
      this.textBoxName.Text = strItem.GetNameFromID(itemAll.ItemList[index].ItemID);
      this.richTextBoxDesc.Text = strItem.GetDescrFromID(itemAll.ItemList[index].ItemID);
    }
  }
}
