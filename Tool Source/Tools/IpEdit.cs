// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.IpEdit
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Text;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools
{
  public class IpEdit : Form
  {
    private StringCollection folderCol;
    public static int Version;
    public static byte[] Header_lccnct;
    public static byte[] Header_sl;
    public static string urliptxt;
    private MemoryStream userInput = new MemoryStream();
    private IContainer components = (IContainer) null;
    private TextBox textBoxIP;
    private TextBox textBoxURL;
    private TextBox textBoxversion;
    private Label label1;
    private Label label2;
    private Label label3;
    private MenuStrip menuStrip1;
    private ToolStripMenuItem toolStripMenuItem1;
    private ToolStripMenuItem saveAllToolStripMenuItem;
    private RichTextBox richTextBox1;
    private Button button1;
    private TextBox textBox1;
    private SaveFileDialog saveFileDialog2;
    private TextBox textBox2;
    private Button button2;
    private FolderBrowserDialog folderBrowserDialog1;
    private Button button3;
    private ListView listView1;
    private Label label4;

    public IpEdit() => this.InitializeComponent();

    private void CreateHeadersAndFillListView()
    {
      this.listView1.Columns.Add(new ColumnHeader()
      {
        Text = "Filename"
      });
      this.listView1.Columns.Add(new ColumnHeader()
      {
        Text = "Size"
      });
      this.listView1.Columns.Add(new ColumnHeader()
      {
        Text = "Last accessed"
      });
    }

    private void PaintListView(string root)
    {
      try
      {
        if (root.CompareTo("") == 0)
          return;
        DirectoryInfo directoryInfo1 = new DirectoryInfo(root);
        DirectoryInfo[] directories = directoryInfo1.GetDirectories();
        FileInfo[] files = directoryInfo1.GetFiles();
        this.listView1.Items.Clear();
        this.label4.Text = root;
        this.listView1.BeginUpdate();
        DateTime lastAccessTime;
        foreach (DirectoryInfo directoryInfo2 in directories)
        {
          ListViewItem listViewItem = new ListViewItem();
          listViewItem.Text = directoryInfo2.Name;
          listViewItem.Tag = (object) directoryInfo2.FullName;
          listViewItem.SubItems.Add(new ListViewItem.ListViewSubItem()
          {
            Text = ""
          });
          ListViewItem.ListViewSubItem listViewSubItem1 = new ListViewItem.ListViewSubItem();
          ListViewItem.ListViewSubItem listViewSubItem2 = listViewSubItem1;
          lastAccessTime = directoryInfo2.LastAccessTime;
          string str = lastAccessTime.ToString();
          listViewSubItem2.Text = str;
          listViewItem.SubItems.Add(listViewSubItem1);
          this.listView1.Items.Add(listViewItem);
        }
        foreach (FileInfo fileInfo in files)
        {
          ListViewItem listViewItem = new ListViewItem();
          listViewItem.Text = fileInfo.Name;
          listViewItem.Tag = (object) fileInfo.FullName;
          listViewItem.SubItems.Add(new ListViewItem.ListViewSubItem()
          {
            Text = fileInfo.Length.ToString()
          });
          ListViewItem.ListViewSubItem listViewSubItem3 = new ListViewItem.ListViewSubItem();
          ListViewItem.ListViewSubItem listViewSubItem4 = listViewSubItem3;
          lastAccessTime = fileInfo.LastAccessTime;
          string str = lastAccessTime.ToString();
          listViewSubItem4.Text = str;
          listViewItem.SubItems.Add(listViewSubItem3);
          this.listView1.Items.Add(listViewItem);
        }
        this.listView1.EndUpdate();
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show("Error: " + ex.Message);
      }
    }

    public string readdtafile(string FileName)
    {
      ASCIIEncoding asciiEncoding = new ASCIIEncoding();
      BinaryReader binaryReader = new BinaryReader((Stream) File.Open(FileName, FileMode.Open));
      int count1 = 19;
      int count2 = (int) binaryReader.BaseStream.Length - count1;
      byte[] numArray = binaryReader.ReadBytes(count1);
      if (Path.GetFileName(FileName) == "lccnct.dta")
        IpEdit.Header_lccnct = numArray;
      if (Path.GetFileName(FileName) == "sl.dta")
        IpEdit.Header_sl = numArray;
      byte[] bytes = binaryReader.ReadBytes(count2);
      binaryReader.Close();
      byte num = numArray[10];
      for (int index = 0; index < count2; ++index)
      {
        bytes[index] -= num;
        num += bytes[index];
      }
      return asciiEncoding.GetString(bytes);
    }

    public void saveDTAFile(string NewInput, string FileName)
    {
      ASCIIEncoding asciiEncoding = new ASCIIEncoding();
      byte[] buffer = new byte[0];
      if (Path.GetFileName(FileName) == "lccnct.dta")
        buffer = IpEdit.Header_lccnct;
      if (Path.GetFileName(FileName) == "sl.dta")
        buffer = IpEdit.Header_sl;
      byte[] bytes = asciiEncoding.GetBytes(NewInput);
      byte num = buffer[10];
      for (int index = 0; index < bytes.Length; ++index)
      {
        bytes[index] += num;
        num = bytes[index];
      }
      BinaryWriter binaryWriter = new BinaryWriter((Stream) File.Create(FileName));
      binaryWriter.Write(buffer);
      binaryWriter.Write(bytes);
      binaryWriter.Close();
    }

    public void OpenVTM()
    {
      OpenFileDialog openFileDialog = new OpenFileDialog();
      openFileDialog.Title = "LC Versions file to open";
      openFileDialog.InitialDirectory = "";
      openFileDialog.Filter = "brn|vtm.brn";
      if (openFileDialog.ShowDialog() == DialogResult.Cancel)
        return;
      try
      {
        BinaryReader binaryReader = new BinaryReader((Stream) File.Open(openFileDialog.FileName, FileMode.Open));
        IpEdit.Version = binaryReader.ReadInt32();
        binaryReader.Close();
        IpEdit.Version = (IpEdit.Version - 27) / 3;
        this.textBoxversion.Text = IpEdit.Version.ToString();
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show((IWin32Window) this, ex.Message, "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
    }

    public void OppenIP()
    {
      OpenFileDialog openFileDialog = new OpenFileDialog();
      openFileDialog.Title = "LC IP file to open";
      openFileDialog.InitialDirectory = "";
      openFileDialog.Filter = "dta|sl.dta";
      if (openFileDialog.ShowDialog() == DialogResult.Cancel)
        return;
      this.textBoxIP.Text = this.readdtafile(openFileDialog.FileName);
    }

    public void OpenURL()
    {
      OpenFileDialog openFileDialog = new OpenFileDialog();
      openFileDialog.Title = "LC URL file to open";
      openFileDialog.InitialDirectory = "";
      openFileDialog.Filter = "dta|lccnct.dta";
      if (openFileDialog.ShowDialog() == DialogResult.Cancel)
        return;
      this.textBoxURL.Text = this.readdtafile(openFileDialog.FileName);
    }

    public void SaveVER()
    {
      SaveFileDialog saveFileDialog = new SaveFileDialog();
      saveFileDialog.Filter = "brn|vtm.brn";
      saveFileDialog.Title = "LC Versions file to save";
      saveFileDialog.FileName = "vtm.brn";
      if (saveFileDialog.ShowDialog() == DialogResult.Cancel || !(saveFileDialog.FileName != ""))
        return;
      int num = (Convert.ToInt32(this.textBoxversion.Text) + 9) * 3;
      BinaryWriter binaryWriter = new BinaryWriter((Stream) File.Create(saveFileDialog.FileName));
      binaryWriter.Write(num);
      binaryWriter.Close();
    }

    public void SaveIP()
    {
      SaveFileDialog saveFileDialog = new SaveFileDialog();
      saveFileDialog.Filter = "dta|sl.dta";
      saveFileDialog.Title = "LC IP file to save";
      saveFileDialog.FileName = "sl.dta";
      if (saveFileDialog.ShowDialog() == DialogResult.Cancel || !(saveFileDialog.FileName != ""))
        return;
      this.saveDTAFile(this.textBoxIP.Text, saveFileDialog.FileName);
    }

    public void SaveURL()
    {
      SaveFileDialog saveFileDialog = new SaveFileDialog();
      saveFileDialog.Filter = "dta|lccnct.dta";
      saveFileDialog.Title = "LC URL file to save";
      saveFileDialog.FileName = "lccnct.dta";
      if (saveFileDialog.ShowDialog() == DialogResult.Cancel || !(saveFileDialog.FileName != ""))
        return;
      this.saveDTAFile(this.textBoxURL.Text, saveFileDialog.FileName);
    }

    private void toolStripMenuItem1_Click(object sender, EventArgs e)
    {
      this.OpenVTM();
      this.OppenIP();
      this.OpenURL();
    }

    private void button1_Click(object sender, EventArgs e)
    {
      TextWriter textWriter = (TextWriter) new StreamWriter(this.textBox2.Text + "/LCNotes.txt");
      textWriter.Write(this.richTextBox1.Text);
      textWriter.Close();
    }

    private void saveFileDialog2_FileOk(object sender, CancelEventArgs e)
    {
    }

    private void saveAllToolStripMenuItem_Click(object sender, EventArgs e)
    {
      this.SaveVER();
      this.SaveIP();
      this.SaveURL();
    }

    private void button2_Click(object sender, EventArgs e)
    {
      if (this.folderBrowserDialog1.ShowDialog() != DialogResult.OK)
        return;
      int num = (int) MessageBox.Show("Files found: " + Directory.GetFiles(this.folderBrowserDialog1.SelectedPath).Length.ToString(), "Message");
      this.textBox2.Text = this.folderBrowserDialog1.SelectedPath;
    }

    private void textBox2_TextChanged(object sender, EventArgs e)
    {
      this.textBox2.Text = this.folderBrowserDialog1.SelectedPath;
      this.folderCol = new StringCollection();
      this.CreateHeadersAndFillListView();
      this.PaintListView(this.textBox2.Text ?? "");
      this.folderCol.Add(this.textBox2.Text ?? "");
    }

    private void button3_Click(object sender, EventArgs e)
    {
      this.textBoxIP.Clear();
      this.textBoxURL.Clear();
      this.textBoxversion.Clear();
    }

    private void listView1_ItemActivate(object sender, EventArgs e)
    {
      ListView listView = (ListView) sender;
      string str = listView.SelectedItems[0].Tag.ToString();
      if (listView.SelectedItems[0].ImageIndex != 0)
      {
        try
        {
          Process.Start(str);
        }
        catch
        {
        }
      }
      else
      {
        this.PaintListView(str);
        this.folderCol.Add(str);
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
      this.textBoxIP = new TextBox();
      this.textBoxURL = new TextBox();
      this.textBoxversion = new TextBox();
      this.label1 = new Label();
      this.label2 = new Label();
      this.label3 = new Label();
      this.menuStrip1 = new MenuStrip();
      this.toolStripMenuItem1 = new ToolStripMenuItem();
      this.saveAllToolStripMenuItem = new ToolStripMenuItem();
      this.richTextBox1 = new RichTextBox();
      this.button1 = new Button();
      this.textBox1 = new TextBox();
      this.saveFileDialog2 = new SaveFileDialog();
      this.textBox2 = new TextBox();
      this.button2 = new Button();
      this.folderBrowserDialog1 = new FolderBrowserDialog();
      this.button3 = new Button();
      this.listView1 = new ListView();
      this.label4 = new Label();
      this.menuStrip1.SuspendLayout();
      this.SuspendLayout();
      this.textBoxIP.Location = new Point(60, 21);
      this.textBoxIP.Name = "textBoxIP";
      this.textBoxIP.Size = new Size(192, 20);
      this.textBoxIP.TabIndex = 0;
      this.textBoxURL.Location = new Point(60, 73);
      this.textBoxURL.Name = "textBoxURL";
      this.textBoxURL.Size = new Size(192, 20);
      this.textBoxURL.TabIndex = 1;
      this.textBoxversion.Location = new Point(60, 47);
      this.textBoxversion.Name = "textBoxversion";
      this.textBoxversion.Size = new Size(100, 20);
      this.textBoxversion.TabIndex = 2;
      this.label1.AutoSize = true;
      this.label1.Location = new Point(12, 24);
      this.label1.Name = "label1";
      this.label1.Size = new Size(17, 13);
      this.label1.TabIndex = 3;
      this.label1.Text = "IP";
      this.label2.AutoSize = true;
      this.label2.Location = new Point(12, 50);
      this.label2.Name = "label2";
      this.label2.Size = new Size(42, 13);
      this.label2.TabIndex = 4;
      this.label2.Text = "Version";
      this.label3.AutoSize = true;
      this.label3.Location = new Point(9, 76);
      this.label3.Name = "label3";
      this.label3.Size = new Size(20, 13);
      this.label3.TabIndex = 5;
      this.label3.Text = "Url";
      this.menuStrip1.Items.AddRange(new ToolStripItem[2]
      {
        (ToolStripItem) this.toolStripMenuItem1,
        (ToolStripItem) this.saveAllToolStripMenuItem
      });
      this.menuStrip1.Location = new Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new Size(856, 24);
      this.menuStrip1.TabIndex = 6;
      this.menuStrip1.Text = "menuStrip1";
      this.toolStripMenuItem1.Name = "toolStripMenuItem1";
      this.toolStripMenuItem1.Size = new Size(48, 20);
      this.toolStripMenuItem1.Text = "Open";
      this.toolStripMenuItem1.Click += new EventHandler(this.toolStripMenuItem1_Click);
      this.saveAllToolStripMenuItem.Name = "saveAllToolStripMenuItem";
      this.saveAllToolStripMenuItem.Size = new Size(60, 20);
      this.saveAllToolStripMenuItem.Text = "Save All";
      this.saveAllToolStripMenuItem.Click += new EventHandler(this.saveAllToolStripMenuItem_Click);
      this.richTextBox1.Location = new Point(339, 73);
      this.richTextBox1.Name = "richTextBox1";
      this.richTextBox1.Size = new Size(505, 286);
      this.richTextBox1.TabIndex = 7;
      this.richTextBox1.Text = "";
      this.button1.Location = new Point(258, 44);
      this.button1.Name = "button1";
      this.button1.Size = new Size(75, 23);
      this.button1.TabIndex = 8;
      this.button1.Text = "Save Text";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.textBox1.Location = new Point(339, 46);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(119, 20);
      this.textBox1.TabIndex = 9;
      this.textBox1.Text = "Note";
      this.saveFileDialog2.FileOk += new CancelEventHandler(this.saveFileDialog2_FileOk);
      this.textBox2.Location = new Point(566, 47);
      this.textBox2.Name = "textBox2";
      this.textBox2.Size = new Size(278, 20);
      this.textBox2.TabIndex = 10;
      this.textBox2.Text = "C:/Users/djcyb/Desktop/Prouff/MyTextNotes.txt";
      this.textBox2.TextChanged += new EventHandler(this.textBox2_TextChanged);
      this.button2.Location = new Point(485, 45);
      this.button2.Name = "button2";
      this.button2.Size = new Size(75, 23);
      this.button2.TabIndex = 11;
      this.button2.Text = "Select";
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.button3.Location = new Point(258, 71);
      this.button3.Name = "button3";
      this.button3.Size = new Size(75, 23);
      this.button3.TabIndex = 12;
      this.button3.Text = "Clear";
      this.button3.UseVisualStyleBackColor = true;
      this.button3.Click += new EventHandler(this.button3_Click);
      this.listView1.Location = new Point(0, 128);
      this.listView1.Name = "listView1";
      this.listView1.Size = new Size(333, 231);
      this.listView1.TabIndex = 13;
      this.listView1.UseCompatibleStateImageBehavior = false;
      this.listView1.ItemActivate += new EventHandler(this.listView1_ItemActivate);
      this.label4.AutoSize = true;
      this.label4.Location = new Point(0, 109);
      this.label4.Name = "label4";
      this.label4.Size = new Size(10, 13);
      this.label4.TabIndex = 14;
      this.label4.Text = ".";
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(856, 364);
      this.Controls.Add((Control) this.label4);
      this.Controls.Add((Control) this.listView1);
      this.Controls.Add((Control) this.button3);
      this.Controls.Add((Control) this.button2);
      this.Controls.Add((Control) this.textBox2);
      this.Controls.Add((Control) this.textBox1);
      this.Controls.Add((Control) this.button1);
      this.Controls.Add((Control) this.richTextBox1);
      this.Controls.Add((Control) this.label3);
      this.Controls.Add((Control) this.label2);
      this.Controls.Add((Control) this.label1);
      this.Controls.Add((Control) this.textBoxversion);
      this.Controls.Add((Control) this.textBoxURL);
      this.Controls.Add((Control) this.textBoxIP);
      this.Controls.Add((Control) this.menuStrip1);
      this.MainMenuStrip = this.menuStrip1;
      this.Name = nameof (IpEdit);
      this.Text = nameof (IpEdit);
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
