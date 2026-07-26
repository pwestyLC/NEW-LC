// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneData.Zonedata
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using LcDevPack_TeamDamonA.Properties;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Text;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.ZoneData
{
  public class Zonedata : Form
  {
    private static Dictionary<int, string> m_stringTable = new Dictionary<int, string>();
    private static List<Zonedata.stInfo> zoneList;
    private static List<Zonedata.stExtraInfo> extraList;
    private IContainer components;
    private StatusStrip statusStrip1;
    private ListBox lb_zoneList;
    private Button addZoneBtn;
    private Button delZoneBtn;
    private MenuStrip menuStrip1;
    private ToolStripMenuItem fileToolStripMenuItem;
    private ToolStripMenuItem openZoneData;
    private ToolStripMenuItem saveZoneData;
    private ToolStripSeparator toolStripSeparator1;
    private ToolStripMenuItem exitEditor;
    private ToolStripMenuItem aboutToolStripMenuItem;
    private TextBox tb_zoneFile;
    private TextBox tb_texName1;
    private Label label1;
    private Label label2;
    private Button findZoneBtn;
    private Label label3;
    private TextBox tb_texName2;
    private ListBox lb_zoneExtra;
    private Button delSubZoneBtn;
    private Label label4;
    private TextBox tb_zoneType;
    private Button addSubZoneBtn;
    private Button selectExtraNameBtn;
    private Button selectZoneNameBtn;
    private Label label5;
    private TextBox tb_loadMul;
    private Label label6;
    private TextBox tb_loadSteps;
    private Button updateBtn;
    private Button findTex1Btn;
    private Button findTex2Btn;

    public Zonedata() => this.InitializeComponent();

    private string GetString(int strID)
    {
      if (strID == 0)
        return "";
      if (Zonedata.m_stringTable.Count == 0)
      {
        OpenFileDialog openFileDialog = new OpenFileDialog();
        openFileDialog.Title = "Select String Table (strClient_us.lod)";
        openFileDialog.Filter = "Client String Files (*.lod)|*.lod";
        if (openFileDialog.ShowDialog() != DialogResult.OK)
          return "";
        BinaryReader binaryReader = new BinaryReader((Stream) File.Open(openFileDialog.FileName, FileMode.Open));
        binaryReader.ReadInt32();
        binaryReader.ReadInt32();
        while (binaryReader.BaseStream.Position != binaryReader.BaseStream.Length)
        {
          int key = binaryReader.ReadInt32();
          int count = binaryReader.ReadInt32();
          if (count > 0)
          {
            string str = Encoding.GetEncoding("windows-874").GetString(binaryReader.ReadBytes(count));
            Zonedata.m_stringTable.Add(key, str);
          }
        }
        binaryReader.Close();
        binaryReader.Dispose();
      }
      string str1;
      return !Zonedata.m_stringTable.TryGetValue(strID, out str1) ? "NAME NOT FOUND" : str1;
    }

    private void RebuildLists()
    {
      this.lb_zoneList.Items.Clear();
      this.lb_zoneExtra.Items.Clear();
      for (int index = 0; index < Zonedata.zoneList.Count; ++index)
        this.lb_zoneList.Items.Add((object) this.GetString(Zonedata.zoneList[index].nString));
    }

    private void LoadZoneData(string zonefile)
    {
      if (!File.Exists(zonefile))
        return;
      BinaryReader binaryReader = new BinaryReader((Stream) File.Open(zonefile, FileMode.Open));
      int num1 = binaryReader.ReadInt32();
      Zonedata.zoneList = new List<Zonedata.stInfo>();
      for (int index = 0; index < num1; ++index)
      {
        Zonedata.zoneList.Add(new Zonedata.stInfo());
        Zonedata.zoneList[index].nZoneType = binaryReader.ReadInt32();
        Zonedata.zoneList[index].nExtraCnt = binaryReader.ReadInt32();
        Zonedata.zoneList[index].nString = binaryReader.ReadInt32();
        Zonedata.zoneList[index].wldFileName = Encoding.GetEncoding("windows-874").GetString(binaryReader.ReadBytes(128));
        Zonedata.zoneList[index].texName1 = Encoding.GetEncoding("windows-874").GetString(binaryReader.ReadBytes(64));
        Zonedata.zoneList[index].texName2 = Encoding.GetEncoding("windows-874").GetString(binaryReader.ReadBytes(64));
        Zonedata.zoneList[index].fLoadingStep = binaryReader.ReadSingle();
        Zonedata.zoneList[index].fTer_Lodmul = binaryReader.ReadSingle();
      }
      int num2 = binaryReader.ReadInt32();
      Zonedata.extraList = new List<Zonedata.stExtraInfo>();
      for (int index1 = 0; index1 < num2; ++index1)
      {
        Zonedata.extraList.Add(new Zonedata.stExtraInfo());
        for (int index2 = 0; index2 < 30; ++index2)
          Zonedata.extraList[index1].nString[index2] = binaryReader.ReadInt32();
      }
      binaryReader.Close();
      binaryReader.Dispose();
      this.RebuildLists();
    }

    private void openZoneData_Click(object sender, EventArgs e)
    {
      OpenFileDialog openFileDialog = new OpenFileDialog();
      openFileDialog.Filter = "ZoneData Binary (*.bin)|*.bin";
      openFileDialog.Title = "Open ZoneData File";
      if (openFileDialog.ShowDialog() != DialogResult.OK)
        return;
      this.LoadZoneData(openFileDialog.FileName);
    }

    private void lb_zoneList_SelectedIndexChanged(object sender, EventArgs e)
    {
      ListBox listBox = (ListBox) sender;
      if (listBox.SelectedIndex == -1)
        return;
      int selectedIndex = listBox.SelectedIndex;
      this.tb_zoneType.Text = Zonedata.zoneList[selectedIndex].nZoneType.ToString();
      this.tb_zoneFile.Text = Zonedata.zoneList[selectedIndex].wldFileName;
      this.tb_texName1.Text = Zonedata.zoneList[selectedIndex].texName1;
      this.tb_texName2.Text = Zonedata.zoneList[selectedIndex].texName2;
      this.tb_loadSteps.Text = Zonedata.zoneList[selectedIndex].fLoadingStep.ToString();
      this.tb_loadMul.Text = Zonedata.zoneList[selectedIndex].fTer_Lodmul.ToString();
      this.lb_zoneExtra.Items.Clear();
      for (int index = 0; index < Zonedata.zoneList[selectedIndex].nExtraCnt; ++index)
        this.lb_zoneExtra.Items.Add(Zonedata.extraList[selectedIndex].nString[index] != 0 ? (object) this.GetString(Zonedata.extraList[selectedIndex].nString[index]) : (object) "NONE");
    }

    private void delSubZoneBtn_Click(object sender, EventArgs e)
    {
      int selectedIndex1 = this.lb_zoneList.SelectedIndex;
      if (selectedIndex1 == -1)
        return;
      int selectedIndex2 = this.lb_zoneExtra.SelectedIndex;
      if (selectedIndex2 == -1)
        return;
      Zonedata.extraList[selectedIndex1].nString[selectedIndex2] = 0;
      this.lb_zoneExtra.Items[selectedIndex2] = (object) "NONE";
    }

    private void selectExtraNameBtn_Click(object sender, EventArgs e)
    {
      int selectedIndex1 = this.lb_zoneList.SelectedIndex;
      if (selectedIndex1 == -1)
        return;
      int selectedIndex2 = this.lb_zoneExtra.SelectedIndex;
      if (selectedIndex2 == -1)
        return;
      StringSelect stringSelect = new StringSelect(Zonedata.m_stringTable);
      int num = (int) stringSelect.ShowDialog();
      string s = stringSelect.Selected();
      if (s == "NONE")
        return;
      Zonedata.extraList[selectedIndex1].nString[selectedIndex2] = int.Parse(s);
      this.lb_zoneExtra.Items[selectedIndex2] = (object) this.GetString(int.Parse(s));
    }

    private void addSubZoneBtn_Click(object sender, EventArgs e)
    {
      int selectedIndex = this.lb_zoneList.SelectedIndex;
      if (selectedIndex == -1)
        return;
      if (Zonedata.zoneList[selectedIndex].nExtraCnt == 30)
      {
        int num = (int) MessageBox.Show("No Zone Extra Slots Availiable Limit 30.");
      }
      else
      {
        ++Zonedata.zoneList[selectedIndex].nExtraCnt;
        Zonedata.extraList[selectedIndex].nString[Zonedata.zoneList[selectedIndex].nExtraCnt - 1] = 0;
        this.lb_zoneList_SelectedIndexChanged((object) this.lb_zoneList, (EventArgs) null);
      }
    }

    private void addZoneBtn_Click(object sender, EventArgs e)
    {
      Zonedata.zoneList.Add(new Zonedata.stInfo()
      {
        nZoneType = 0,
        nString = 0,
        nExtraCnt = 0,
        fTer_Lodmul = 1f,
        fLoadingStep = 13f,
        wldFileName = "",
        texName1 = "",
        texName2 = ""
      });
      Zonedata.stExtraInfo stExtraInfo = new Zonedata.stExtraInfo();
      for (int index = 0; index < 30; ++index)
        stExtraInfo.nString[index] = 0;
      Zonedata.extraList.Add(stExtraInfo);
      this.RebuildLists();
      this.lb_zoneList.SelectedIndex = this.lb_zoneList.Items.Count - 1;
    }

    private void selectZoneNameBtn_Click(object sender, EventArgs e)
    {
      int selectedIndex = this.lb_zoneList.SelectedIndex;
      if (selectedIndex == -1)
        return;
      StringSelect stringSelect = new StringSelect(Zonedata.m_stringTable);
      int num = (int) stringSelect.ShowDialog();
      string s = stringSelect.Selected();
      if (s == "NONE")
        return;
      Zonedata.zoneList[selectedIndex].nString = int.Parse(s);
      this.lb_zoneList.Items[selectedIndex] = (object) this.GetString(int.Parse(s));
    }

    private void delZoneBtn_Click(object sender, EventArgs e)
    {
      int selectedIndex = this.lb_zoneList.SelectedIndex;
      if (selectedIndex == -1)
        return;
      Zonedata.zoneList.RemoveAt(selectedIndex);
      Zonedata.extraList.RemoveAt(selectedIndex);
      this.RebuildLists();
      if (this.lb_zoneList.Items.Count == 0)
        return;
      this.lb_zoneList.SelectedIndex = 0;
    }

    private void saveZoneData_Click(object sender, EventArgs e)
    {
      SaveFileDialog saveFileDialog = new SaveFileDialog();
      saveFileDialog.Title = "Save zone_data.bin";
      saveFileDialog.Filter = "Zone Binary File (*.bin)|*.bin";
      if (saveFileDialog.ShowDialog() != DialogResult.OK)
        return;
      BinaryWriter binaryWriter = new BinaryWriter(saveFileDialog.OpenFile());
      binaryWriter.Write(Zonedata.zoneList.Count);
      byte[] buffer1 = new byte[128];
      byte[] buffer2 = new byte[64];
      for (int index = 0; index < Zonedata.zoneList.Count; ++index)
      {
        binaryWriter.Write(Zonedata.zoneList[index].nZoneType);
        binaryWriter.Write(Zonedata.zoneList[index].nExtraCnt);
        binaryWriter.Write(Zonedata.zoneList[index].nString);
        byte[] bytes1 = Encoding.GetEncoding("windows-874").GetBytes(Zonedata.zoneList[index].wldFileName);
        Array.Clear((Array) buffer1, 0, 128);
        byte[] destinationArray1 = buffer1;
        int length1 = Zonedata.zoneList[index].wldFileName.Length;
        Array.Copy((Array) bytes1, (Array) destinationArray1, length1);
        binaryWriter.Write(buffer1);
        byte[] bytes2 = Encoding.GetEncoding("windows-874").GetBytes(Zonedata.zoneList[index].texName1);
        Array.Clear((Array) buffer2, 0, 64);
        byte[] destinationArray2 = buffer2;
        int length2 = Zonedata.zoneList[index].texName1.Length;
        Array.Copy((Array) bytes2, (Array) destinationArray2, length2);
        binaryWriter.Write(buffer2);
        byte[] bytes3 = Encoding.GetEncoding("windows-874").GetBytes(Zonedata.zoneList[index].texName2);
        Array.Clear((Array) buffer2, 0, 64);
        byte[] destinationArray3 = buffer2;
        int length3 = Zonedata.zoneList[index].texName2.Length;
        Array.Copy((Array) bytes3, (Array) destinationArray3, length3);
        binaryWriter.Write(buffer2);
        binaryWriter.Write(Zonedata.zoneList[index].fLoadingStep);
        binaryWriter.Write(Zonedata.zoneList[index].fTer_Lodmul);
      }
      binaryWriter.Write(Zonedata.extraList.Count);
      for (int index1 = 0; index1 < Zonedata.extraList.Count; ++index1)
      {
        for (int index2 = 0; index2 < 30; ++index2)
          binaryWriter.Write(Zonedata.extraList[index1].nString[index2]);
      }
      binaryWriter.Close();
      binaryWriter.Dispose();
    }

    private void exitEditor_Click(object sender, EventArgs e) => this.Close();

    private void updateBtn_Click(object sender, EventArgs e)
    {
      int selectedIndex = this.lb_zoneList.SelectedIndex;
      if (selectedIndex == -1)
        return;
      Zonedata.zoneList[selectedIndex].nZoneType = int.Parse(this.tb_zoneType.Text);
      Zonedata.zoneList[selectedIndex].wldFileName = this.tb_zoneFile.Text;
      Zonedata.zoneList[selectedIndex].texName1 = this.tb_texName1.Text;
      Zonedata.zoneList[selectedIndex].texName2 = this.tb_texName2.Text;
      Zonedata.zoneList[selectedIndex].fLoadingStep = float.Parse(this.tb_loadSteps.Text);
      Zonedata.zoneList[selectedIndex].fTer_Lodmul = float.Parse(this.tb_loadMul.Text);
    }

    private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
    {
      int num = (int) MessageBox.Show(string.Format("Zone Data Editor Version: {0} \n\nBy Illusionist.", (object) Application.ProductVersion), "About Zone Data Editor", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
    }

    private void findZoneBtn_Click(object sender, EventArgs e)
    {
      OpenFileDialog openFileDialog = new OpenFileDialog();
      openFileDialog.Title = "Select .wld file";
      openFileDialog.Filter = "Last Chaos World File (*.wld)|*.wld";
      if (openFileDialog.ShowDialog() != DialogResult.OK)
        return;
      int num = openFileDialog.FileName.LastIndexOf("Data\\World");
      int length = "Data\\World".Length;
      this.tb_zoneFile.Text = openFileDialog.FileName.Substring(num + length + 1, openFileDialog.FileName.Length - num - length - 1);
    }

    private void findTex1Btn_Click(object sender, EventArgs e)
    {
      OpenFileDialog openFileDialog = new OpenFileDialog();
      openFileDialog.Title = "Select .tex file";
      openFileDialog.Filter = "Last Chaos Texture (*.tex)|*.tex";
      if (openFileDialog.ShowDialog() != DialogResult.OK)
        return;
      this.tb_texName1.Text = Path.GetFileName(openFileDialog.FileName);
    }

    private void findTex2Btn_Click(object sender, EventArgs e)
    {
      OpenFileDialog openFileDialog = new OpenFileDialog();
      openFileDialog.Title = "Select .tex file";
      openFileDialog.Filter = "Last Chaos Texture (*.tex)|*.tex";
      if (openFileDialog.ShowDialog() != DialogResult.OK)
        return;
      this.tb_texName2.Text = Path.GetFileName(openFileDialog.FileName);
    }

    private void lb_zoneList_KeyDown(object sender, KeyEventArgs e)
    {
      if (e.KeyCode != Keys.Return)
        return;
      e.SuppressKeyPress = true;
      this.selectZoneNameBtn_Click((object) null, (EventArgs) null);
    }

    private void lb_zoneExtra_KeyDown(object sender, KeyEventArgs e)
    {
      if (e.KeyCode != Keys.Return)
        return;
      e.SuppressKeyPress = true;
      this.selectExtraNameBtn_Click((object) null, (EventArgs) null);
    }

    private void lb_zoneList_MouseDoubleClick(object sender, MouseEventArgs e)
    {
      if (this.lb_zoneList.IndexFromPoint(e.Location) == -1)
        return;
      this.selectZoneNameBtn_Click((object) null, (EventArgs) null);
    }

    private void lb_zoneExtra_MouseDoubleClick(object sender, MouseEventArgs e)
    {
      if (this.lb_zoneExtra.IndexFromPoint(e.Location) == -1)
        return;
      this.selectExtraNameBtn_Click((object) null, (EventArgs) null);
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      this.statusStrip1 = new StatusStrip();
      this.lb_zoneList = new ListBox();
      this.addZoneBtn = new Button();
      this.delZoneBtn = new Button();
      this.menuStrip1 = new MenuStrip();
      this.fileToolStripMenuItem = new ToolStripMenuItem();
      this.openZoneData = new ToolStripMenuItem();
      this.saveZoneData = new ToolStripMenuItem();
      this.toolStripSeparator1 = new ToolStripSeparator();
      this.exitEditor = new ToolStripMenuItem();
      this.aboutToolStripMenuItem = new ToolStripMenuItem();
      this.tb_zoneFile = new TextBox();
      this.tb_texName1 = new TextBox();
      this.label1 = new Label();
      this.label2 = new Label();
      this.findZoneBtn = new Button();
      this.label3 = new Label();
      this.tb_texName2 = new TextBox();
      this.lb_zoneExtra = new ListBox();
      this.delSubZoneBtn = new Button();
      this.label4 = new Label();
      this.tb_zoneType = new TextBox();
      this.addSubZoneBtn = new Button();
      this.selectExtraNameBtn = new Button();
      this.selectZoneNameBtn = new Button();
      this.label5 = new Label();
      this.tb_loadMul = new TextBox();
      this.label6 = new Label();
      this.tb_loadSteps = new TextBox();
      this.updateBtn = new Button();
      this.findTex1Btn = new Button();
      this.findTex2Btn = new Button();
      this.menuStrip1.SuspendLayout();
      this.SuspendLayout();
      this.statusStrip1.Location = new Point(0, 422);
      this.statusStrip1.Name = "statusStrip1";
      this.statusStrip1.Size = new Size(684, 22);
      this.statusStrip1.TabIndex = 0;
      this.statusStrip1.Text = "statusStrip1";
      this.lb_zoneList.FormattingEnabled = true;
      this.lb_zoneList.Location = new Point(187, 30);
      this.lb_zoneList.Name = "lb_zoneList";
      this.lb_zoneList.Size = new Size(235, 355);
      this.lb_zoneList.TabIndex = 1;
      this.lb_zoneList.SelectedIndexChanged += new EventHandler(this.lb_zoneList_SelectedIndexChanged);
      this.lb_zoneList.KeyDown += new KeyEventHandler(this.lb_zoneList_KeyDown);
      this.lb_zoneList.MouseDoubleClick += new MouseEventHandler(this.lb_zoneList_MouseDoubleClick);
      this.addZoneBtn.Location = new Point(187, 391);
      this.addZoneBtn.Name = "addZoneBtn";
      this.addZoneBtn.Size = new Size(75, 23);
      this.addZoneBtn.TabIndex = 2;
      this.addZoneBtn.Text = "Add";
      this.addZoneBtn.UseVisualStyleBackColor = true;
      this.addZoneBtn.Click += new EventHandler(this.addZoneBtn_Click);
      this.delZoneBtn.Location = new Point(347, 391);
      this.delZoneBtn.Name = "delZoneBtn";
      this.delZoneBtn.Size = new Size(75, 23);
      this.delZoneBtn.TabIndex = 3;
      this.delZoneBtn.Text = "Delete";
      this.delZoneBtn.UseVisualStyleBackColor = true;
      this.delZoneBtn.Click += new EventHandler(this.delZoneBtn_Click);
      this.menuStrip1.Items.AddRange(new ToolStripItem[2]
      {
        (ToolStripItem) this.fileToolStripMenuItem,
        (ToolStripItem) this.aboutToolStripMenuItem
      });
      this.menuStrip1.Location = new Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new Size(684, 24);
      this.menuStrip1.TabIndex = 4;
      this.menuStrip1.Text = "menuStrip1";
      this.fileToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[4]
      {
        (ToolStripItem) this.openZoneData,
        (ToolStripItem) this.saveZoneData,
        (ToolStripItem) this.toolStripSeparator1,
        (ToolStripItem) this.exitEditor
      });
      this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
      this.fileToolStripMenuItem.Size = new Size(37, 20);
      this.fileToolStripMenuItem.Text = "File";
      this.openZoneData.Name = "openZoneData";
      this.openZoneData.Size = new Size(103, 22);
      this.openZoneData.Text = "Open";
      this.openZoneData.Click += new EventHandler(this.openZoneData_Click);
      this.saveZoneData.Name = "saveZoneData";
      this.saveZoneData.Size = new Size(103, 22);
      this.saveZoneData.Text = "Save";
      this.saveZoneData.Click += new EventHandler(this.saveZoneData_Click);
      this.toolStripSeparator1.Name = "toolStripSeparator1";
      this.toolStripSeparator1.Size = new Size(100, 6);
      this.exitEditor.Name = "exitEditor";
      this.exitEditor.Size = new Size(103, 22);
      this.exitEditor.Text = "Exit";
      this.exitEditor.Click += new EventHandler(this.exitEditor_Click);
      this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
      this.aboutToolStripMenuItem.Size = new Size(52, 20);
      this.aboutToolStripMenuItem.Text = "About";
      this.aboutToolStripMenuItem.Click += new EventHandler(this.aboutToolStripMenuItem_Click);
      this.tb_zoneFile.Location = new Point(12, 85);
      this.tb_zoneFile.Name = "tb_zoneFile";
      this.tb_zoneFile.Size = new Size(138, 20);
      this.tb_zoneFile.TabIndex = 5;
      this.tb_texName1.Location = new Point(12, 125);
      this.tb_texName1.Name = "tb_texName1";
      this.tb_texName1.Size = new Size(138, 20);
      this.tb_texName1.TabIndex = 6;
      this.label1.AutoSize = true;
      this.label1.Location = new Point(12, 69);
      this.label1.Name = "label1";
      this.label1.Size = new Size(57, 13);
      this.label1.TabIndex = 7;
      this.label1.Text = "Zone File :";
      this.label2.AutoSize = true;
      this.label2.Location = new Point(12, 109);
      this.label2.Name = "label2";
      this.label2.Size = new Size(55, 13);
      this.label2.TabIndex = 8;
      this.label2.Text = "Texture 1:";
      this.findZoneBtn.BackColor = Color.White;
      this.findZoneBtn.BackgroundImage = (Image) Resources.search__5_;
      this.findZoneBtn.BackgroundImageLayout = ImageLayout.Center;
      this.findZoneBtn.FlatStyle = FlatStyle.Flat;
      this.findZoneBtn.ImageAlign = ContentAlignment.BottomCenter;
      this.findZoneBtn.Location = new Point(157, 82);
      this.findZoneBtn.Name = "findZoneBtn";
      this.findZoneBtn.Size = new Size(26, 26);
      this.findZoneBtn.TabIndex = 9;
      this.findZoneBtn.UseVisualStyleBackColor = false;
      this.findZoneBtn.Click += new EventHandler(this.findZoneBtn_Click);
      this.label3.AutoSize = true;
      this.label3.Location = new Point(12, 150);
      this.label3.Name = "label3";
      this.label3.Size = new Size(55, 13);
      this.label3.TabIndex = 12;
      this.label3.Text = "Texture 2:";
      this.tb_texName2.Location = new Point(12, 166);
      this.tb_texName2.Name = "tb_texName2";
      this.tb_texName2.Size = new Size(138, 20);
      this.tb_texName2.TabIndex = 11;
      this.lb_zoneExtra.FormattingEnabled = true;
      this.lb_zoneExtra.Location = new Point(437, 30);
      this.lb_zoneExtra.Name = "lb_zoneExtra";
      this.lb_zoneExtra.Size = new Size(235, 355);
      this.lb_zoneExtra.TabIndex = 14;
      this.lb_zoneExtra.KeyDown += new KeyEventHandler(this.lb_zoneExtra_KeyDown);
      this.lb_zoneExtra.MouseDoubleClick += new MouseEventHandler(this.lb_zoneExtra_MouseDoubleClick);
      this.delSubZoneBtn.Location = new Point(597, 391);
      this.delSubZoneBtn.Name = "delSubZoneBtn";
      this.delSubZoneBtn.Size = new Size(75, 23);
      this.delSubZoneBtn.TabIndex = 16;
      this.delSubZoneBtn.Text = "Delete";
      this.delSubZoneBtn.UseVisualStyleBackColor = true;
      this.delSubZoneBtn.Click += new EventHandler(this.delSubZoneBtn_Click);
      this.label4.AutoSize = true;
      this.label4.Location = new Point(12, 30);
      this.label4.Name = "label4";
      this.label4.Size = new Size(62, 13);
      this.label4.TabIndex = 18;
      this.label4.Text = "Zone Type:";
      this.tb_zoneType.Location = new Point(12, 46);
      this.tb_zoneType.Name = "tb_zoneType";
      this.tb_zoneType.Size = new Size(138, 20);
      this.tb_zoneType.TabIndex = 17;
      this.addSubZoneBtn.Location = new Point(437, 391);
      this.addSubZoneBtn.Name = "addSubZoneBtn";
      this.addSubZoneBtn.Size = new Size(75, 23);
      this.addSubZoneBtn.TabIndex = 15;
      this.addSubZoneBtn.Text = "Add";
      this.addSubZoneBtn.UseVisualStyleBackColor = true;
      this.addSubZoneBtn.Click += new EventHandler(this.addSubZoneBtn_Click);
      this.selectExtraNameBtn.Location = new Point(517, 391);
      this.selectExtraNameBtn.Name = "selectExtraNameBtn";
      this.selectExtraNameBtn.Size = new Size(75, 23);
      this.selectExtraNameBtn.TabIndex = 19;
      this.selectExtraNameBtn.Text = "Set Name";
      this.selectExtraNameBtn.UseVisualStyleBackColor = true;
      this.selectExtraNameBtn.Click += new EventHandler(this.selectExtraNameBtn_Click);
      this.selectZoneNameBtn.Location = new Point(267, 391);
      this.selectZoneNameBtn.Name = "selectZoneNameBtn";
      this.selectZoneNameBtn.Size = new Size(75, 23);
      this.selectZoneNameBtn.TabIndex = 20;
      this.selectZoneNameBtn.Text = "Set Name";
      this.selectZoneNameBtn.UseVisualStyleBackColor = true;
      this.selectZoneNameBtn.Click += new EventHandler(this.selectZoneNameBtn_Click);
      this.label5.AutoSize = true;
      this.label5.Location = new Point(12, 233);
      this.label5.Name = "label5";
      this.label5.Size = new Size(57, 13);
      this.label5.TabIndex = 24;
      this.label5.Text = "Load Mul :";
      this.tb_loadMul.Location = new Point(12, 249);
      this.tb_loadMul.Name = "tb_loadMul";
      this.tb_loadMul.Size = new Size(138, 20);
      this.tb_loadMul.TabIndex = 23;
      this.label6.AutoSize = true;
      this.label6.Location = new Point(12, 192);
      this.label6.Name = "label6";
      this.label6.Size = new Size(81, 13);
      this.label6.TabIndex = 22;
      this.label6.Text = "Loading Steps :";
      this.tb_loadSteps.Location = new Point(12, 208);
      this.tb_loadSteps.Name = "tb_loadSteps";
      this.tb_loadSteps.Size = new Size(138, 20);
      this.tb_loadSteps.TabIndex = 21;
      this.updateBtn.Location = new Point(12, 276);
      this.updateBtn.Name = "updateBtn";
      this.updateBtn.Size = new Size(138, 22);
      this.updateBtn.TabIndex = 25;
      this.updateBtn.Text = "Update";
      this.updateBtn.UseVisualStyleBackColor = true;
      this.updateBtn.Click += new EventHandler(this.updateBtn_Click);
      this.findTex1Btn.BackColor = Color.White;
      this.findTex1Btn.BackgroundImage = (Image) Resources.search__5_;
      this.findTex1Btn.BackgroundImageLayout = ImageLayout.Center;
      this.findTex1Btn.FlatStyle = FlatStyle.Flat;
      this.findTex1Btn.Location = new Point(157, 122);
      this.findTex1Btn.Name = "findTex1Btn";
      this.findTex1Btn.Size = new Size(26, 26);
      this.findTex1Btn.TabIndex = 26;
      this.findTex1Btn.UseVisualStyleBackColor = false;
      this.findTex1Btn.Click += new EventHandler(this.findTex1Btn_Click);
      this.findTex2Btn.BackColor = Color.White;
      this.findTex2Btn.BackgroundImage = (Image) Resources.search__5_;
      this.findTex2Btn.BackgroundImageLayout = ImageLayout.Center;
      this.findTex2Btn.FlatStyle = FlatStyle.Flat;
      this.findTex2Btn.Location = new Point(157, 162);
      this.findTex2Btn.Name = "findTex2Btn";
      this.findTex2Btn.Size = new Size(26, 26);
      this.findTex2Btn.TabIndex = 27;
      this.findTex2Btn.UseVisualStyleBackColor = false;
      this.findTex2Btn.Click += new EventHandler(this.findTex2Btn_Click);
      this.ClientSize = new Size(684, 444);
      this.Controls.Add((Control) this.findTex2Btn);
      this.Controls.Add((Control) this.findTex1Btn);
      this.Controls.Add((Control) this.updateBtn);
      this.Controls.Add((Control) this.label5);
      this.Controls.Add((Control) this.tb_loadMul);
      this.Controls.Add((Control) this.label6);
      this.Controls.Add((Control) this.tb_loadSteps);
      this.Controls.Add((Control) this.selectZoneNameBtn);
      this.Controls.Add((Control) this.selectExtraNameBtn);
      this.Controls.Add((Control) this.label4);
      this.Controls.Add((Control) this.tb_zoneType);
      this.Controls.Add((Control) this.delSubZoneBtn);
      this.Controls.Add((Control) this.addSubZoneBtn);
      this.Controls.Add((Control) this.lb_zoneExtra);
      this.Controls.Add((Control) this.label3);
      this.Controls.Add((Control) this.tb_texName2);
      this.Controls.Add((Control) this.findZoneBtn);
      this.Controls.Add((Control) this.label2);
      this.Controls.Add((Control) this.label1);
      this.Controls.Add((Control) this.tb_texName1);
      this.Controls.Add((Control) this.tb_zoneFile);
      this.Controls.Add((Control) this.delZoneBtn);
      this.Controls.Add((Control) this.addZoneBtn);
      this.Controls.Add((Control) this.lb_zoneList);
      this.Controls.Add((Control) this.statusStrip1);
      this.Controls.Add((Control) this.menuStrip1);
      this.FormBorderStyle = FormBorderStyle.FixedSingle;
      this.MainMenuStrip = this.menuStrip1;
      this.MaximizeBox = false;
      this.Name = nameof (Zonedata);
      this.Text = "Zone Data Editor";
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();
    }

    private class stInfo
    {
      public int nZoneType;
      public int nExtraCnt;
      public int nString;
      public string wldFileName;
      public string texName1;
      public string texName2;
      public float fLoadingStep;
      public float fTer_Lodmul;
    }

    private class stExtraInfo
    {
      public int[] nString = new int[30];
    }
  }
}
