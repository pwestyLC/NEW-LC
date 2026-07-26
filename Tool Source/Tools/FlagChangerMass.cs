// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.FlagChangerMass
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using LcDevPack_TeamDamonA.Properties;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools
{
  public class FlagChangerMass : Form
  {
    private string Host = ItemEditor2.connection.Settings.SqlHost;
    private string User = ItemEditor2.connection.Settings.SqlUser;
    private string Password = ItemEditor2.connection.Settings.SqlPassword;
    private string Database = ItemEditor2.connection.Settings.SqlDatabase;
    private string Episode = ItemEditor2.connection.Settings.Episode;
    public string flagBuilderType = "items";
    public long flagBig;
    public int flagSmall;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    private IContainer components = (IContainer) null;
    public CheckedListBox ClbItemFlag;
    private TextBox tbRange1;
    private TextBox tbRange2;
    private Label label1;
    private Label label2;
    private PictureBox PbSelectID1;
    private PictureBox PbSelectID2;
    private Button btnUpdateSelectedRange;
    private TextBox tbItemFlag;
    private Label label3;

    public FlagChangerMass() => this.InitializeComponent();

    private void PbSelectID1_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.tbRange1.Text = Convert.ToString(itemPicker.ItemIndex);
    }

    private void PbSelectID2_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.tbRange2.Text = Convert.ToString(itemPicker.ItemIndex);
    }

    private void btnUpdateSelectedRange_Click(object sender, EventArgs e)
    {
      if (this.tbItemFlag.Text != "" && this.tbRange1.Text != "" && this.tbRange2.Text != "")
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_item SET a_flag ='" + this.tbItemFlag.Text + "'WHERE a_index BETWEEN '" + this.tbRange1.Text + "' AND'" + this.tbRange2.Text + "';");
        new FlagChangerMass().Close();
        int num = (int) new CustomMessage("DONE!").ShowDialog();
      }
      else if (this.tbItemFlag.Text != "" && this.tbRange1.Text != "" && this.tbRange2.Text.Equals(""))
      {
        int num1 = (int) new CustomMessage("Please Enter Range 2 Value").ShowDialog();
      }
      else if (this.tbItemFlag.Text != "" && this.tbRange1.Text.Equals("") && this.tbRange2.Text != "")
      {
        int num2 = (int) new CustomMessage("Please Enter Range 1 Value").ShowDialog();
      }
      else
      {
        if (!this.tbItemFlag.Text.Equals((object) 0) || !(this.tbRange1.Text != "") || !(this.tbRange2.Text != ""))
          return;
        int num3 = (int) new CustomMessage("Please Select a Flag").ShowDialog();
      }
    }

    private void FlagChangerMass_Load(object sender, EventArgs e)
    {
      this.ClbItemFlag.Items.AddRange(new object[64]
      {
        (object) "Count",
        (object) "Drop",
        (object) "Upgrade",
        (object) "Exchange",
        (object) "Trade",
        (object) "Not Delete",
        (object) "Made",
        (object) "Mix",
        (object) "Cash",
        (object) "Lord",
        (object) "No Stash",
        (object) "Change",
        (object) "Composite",
        (object) "Duplication",
        (object) "lent",
        (object) "Rare",
        (object) "ABS",
        (object) "Not Reform",
        (object) "ZoneMove Del",
        (object) "Origin",
        (object) "Trigger",
        (object) "Raid Special",
        (object) "Quest",
        (object) "Box",
        (object) "Not TradeAgent",
        (object) "Durability",
        (object) "Costume2",
        (object) "Socket",
        (object) "Seller",
        (object) "Castillan",
        (object) "LetsParty",
        (object) "Non-RVR",
        (object) "Quest Give",
        (object) "Toggle",
        (object) "Compose",
        (object) "NotSingle",
        (object) "Invisible Custom",
        (object) "37 ",
        (object) "38 ",
        (object) "39 ",
        (object) "40 ",
        (object) "41 ",
        (object) "42 ",
        (object) "43 ",
        (object) "44 ",
        (object) "45 ",
        (object) "46 ",
        (object) "47 ",
        (object) "48 ",
        (object) "49 ",
        (object) "50 ",
        (object) "51 ",
        (object) "52 ",
        (object) "53 ",
        (object) "54 ",
        (object) "55 ",
        (object) "56 ",
        (object) "57 ",
        (object) "58 ",
        (object) "59 ",
        (object) "60 ",
        (object) "61 ",
        (object) "62 ",
        (object) "63 "
      });
    }

    private void ClbItemFlag_SelectedIndexChanged_1(object sender, EventArgs e)
    {
      long num = 0;
      for (int index = 0; index < this.ClbItemFlag.Items.Count; ++index)
      {
        if (this.ClbItemFlag.GetItemChecked(index))
          num += 1L << index;
      }
      this.tbItemFlag.Text = num.ToString();
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

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (FlagChangerMass));
      this.ClbItemFlag = new CheckedListBox();
      this.btnUpdateSelectedRange = new Button();
      this.tbRange1 = new TextBox();
      this.tbRange2 = new TextBox();
      this.label1 = new Label();
      this.label2 = new Label();
      this.PbSelectID1 = new PictureBox();
      this.PbSelectID2 = new PictureBox();
      this.tbItemFlag = new TextBox();
      this.label3 = new Label();
      ((ISupportInitialize) this.PbSelectID1).BeginInit();
      ((ISupportInitialize) this.PbSelectID2).BeginInit();
      this.SuspendLayout();
      this.ClbItemFlag.BackColor = SystemColors.Control;
      this.ClbItemFlag.BorderStyle = BorderStyle.None;
      this.ClbItemFlag.CheckOnClick = true;
      this.ClbItemFlag.Font = new Font("Microsoft Sans Serif", 8.25f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.ClbItemFlag.FormattingEnabled = true;
      this.ClbItemFlag.IntegralHeight = false;
      this.ClbItemFlag.Location = new Point(4, 4);
      this.ClbItemFlag.MultiColumn = true;
      this.ClbItemFlag.Name = "ClbItemFlag";
      this.ClbItemFlag.Size = new Size(300, 539);
      this.ClbItemFlag.TabIndex = 1;
      this.ClbItemFlag.SelectedIndexChanged += new EventHandler(this.ClbItemFlag_SelectedIndexChanged_1);
      this.btnUpdateSelectedRange.Location = new Point(12, 612);
      this.btnUpdateSelectedRange.Name = "btnUpdateSelectedRange";
      this.btnUpdateSelectedRange.Size = new Size(292, 23);
      this.btnUpdateSelectedRange.TabIndex = 2;
      this.btnUpdateSelectedRange.Text = "Update For Selected Items";
      this.btnUpdateSelectedRange.UseVisualStyleBackColor = true;
      this.btnUpdateSelectedRange.Click += new EventHandler(this.btnUpdateSelectedRange_Click);
      this.tbRange1.Location = new Point(14, 562);
      this.tbRange1.Name = "tbRange1";
      this.tbRange1.Size = new Size(100, 20);
      this.tbRange1.TabIndex = 3;
      this.tbRange2.Location = new Point(175, 563);
      this.tbRange2.Name = "tbRange2";
      this.tbRange2.Size = new Size(100, 20);
      this.tbRange2.TabIndex = 4;
      this.label1.AutoSize = true;
      this.label1.Location = new Point(16, 543);
      this.label1.Name = "label1";
      this.label1.Size = new Size(65, 13);
      this.label1.TabIndex = 5;
      this.label1.Text = "ItemRange1";
      this.label2.AutoSize = true;
      this.label2.Location = new Point(192, 545);
      this.label2.Name = "label2";
      this.label2.Size = new Size(65, 13);
      this.label2.TabIndex = 6;
      this.label2.Text = "ItemRange2";
      this.PbSelectID1.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbSelectID1.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbSelectID1.Location = new Point(118, 561);
      this.PbSelectID1.Name = "PbSelectID1";
      this.PbSelectID1.Size = new Size(22, 22);
      this.PbSelectID1.TabIndex = 105;
      this.PbSelectID1.TabStop = false;
      this.PbSelectID1.Click += new EventHandler(this.PbSelectID1_Click);
      this.PbSelectID2.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbSelectID2.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbSelectID2.Location = new Point(279, 561);
      this.PbSelectID2.Name = "PbSelectID2";
      this.PbSelectID2.Size = new Size(22, 22);
      this.PbSelectID2.TabIndex = 106;
      this.PbSelectID2.TabStop = false;
      this.PbSelectID2.Click += new EventHandler(this.PbSelectID2_Click);
      this.tbItemFlag.Location = new Point(93, 589);
      this.tbItemFlag.Name = "tbItemFlag";
      this.tbItemFlag.Size = new Size(211, 20);
      this.tbItemFlag.TabIndex = 107;
      this.label3.AutoSize = true;
      this.label3.Location = new Point(11, 592);
      this.label3.Name = "label3";
      this.label3.Size = new Size(80, 13);
      this.label3.TabIndex = 108;
      this.label3.Text = "Item Flag Value";
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(315, 641);
      this.Controls.Add((Control) this.label3);
      this.Controls.Add((Control) this.tbItemFlag);
      this.Controls.Add((Control) this.PbSelectID2);
      this.Controls.Add((Control) this.PbSelectID1);
      this.Controls.Add((Control) this.label2);
      this.Controls.Add((Control) this.label1);
      this.Controls.Add((Control) this.tbRange2);
      this.Controls.Add((Control) this.tbRange1);
      this.Controls.Add((Control) this.btnUpdateSelectedRange);
      this.Controls.Add((Control) this.ClbItemFlag);
      this.Icon = (Icon) componentResourceManager.GetObject("$this.Icon");
      this.Name = nameof (FlagChangerMass);
      this.StartPosition = FormStartPosition.CenterParent;
      this.Text = nameof (FlagChangerMass);
      this.Load += new EventHandler(this.FlagChangerMass_Load);
      ((ISupportInitialize) this.PbSelectID1).EndInit();
      ((ISupportInitialize) this.PbSelectID2).EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
