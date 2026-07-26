// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MassNameChanger
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
  public class MassNameChanger : Form
  {
    private string Host = ItemEditor2.connection.Settings.SqlHost;
    private string User = ItemEditor2.connection.Settings.SqlUser;
    private string Password = ItemEditor2.connection.Settings.SqlPassword;
    private string Database = ItemEditor2.connection.Settings.SqlDatabase;
    private string language = ItemEditor2.connection.Settings.Language;
    public string namee;
    public string aname = "";
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    private IContainer components = (IContainer) null;
    private Label label3;
    private TextBox tbItemName;
    private PictureBox PbSelectID2;
    private PictureBox PbSelectID1;
    private Label label2;
    private Label label1;
    private TextBox tbRange2;
    private TextBox tbRange1;
    private Button btnUpdateSelectedRange;
    private CheckBox cbRemoveBefore;
    private GroupBox groupBox1;
    private CheckBox cbAddBefore;

    public string StringFromLanguage()
    {
      if (this.language == "GER")
      {
        this.namee = "a_name_ger";
        return this.namee;
      }
      if (this.language == "POL")
      {
        this.namee = "a_name_pld";
        return this.namee;
      }
      if (this.language == "BRA")
      {
        this.namee = "a_name_brz";
        return this.namee;
      }
      if (this.language == "RUS")
      {
        this.namee = "a_name_rus";
        return this.namee;
      }
      if (this.language == "FRA")
      {
        this.namee = "a_name_frc";
        return this.namee;
      }
      if (this.language == "ESP")
      {
        this.namee = "a_name_spn";
        return this.namee;
      }
      if (this.language == "MEX")
      {
        this.namee = "a_name_mex";
        return this.namee;
      }
      if (this.language == "THA")
      {
        this.namee = "a_name_thai";
        return this.namee;
      }
      if (this.language == "ITA")
      {
        this.namee = "a_name_ita";
        return this.namee;
      }
      if (!(this.language == "USA"))
        return (string) null;
      this.namee = "a_name_usa";
      return this.namee;
    }

    public MassNameChanger() => this.InitializeComponent();

    private void BtnUpdateSelectedRange_Click(object sender, EventArgs e)
    {
      this.namee = this.StringFromLanguage();
      if (this.cbAddBefore.Checked || this.cbRemoveBefore.Checked)
      {
        if (this.tbItemName.Text != "" && this.tbRange1.Text != "" && this.tbRange2.Text != "" && this.cbRemoveBefore.Checked)
        {
          this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_item SET " + this.namee + "= REPLACE(" + this.namee + ",'" + this.tbItemName.Text + "','') WHERE a_index BETWEEN '" + this.tbRange1.Text + "' AND'" + this.tbRange2.Text + "';");
          int num = (int) new CustomMessage("DONE!").ShowDialog();
          this.Close();
        }
        else if (this.tbItemName.Text != "" && this.tbRange1.Text != "" && this.tbRange2.Text != "" && this.cbAddBefore.Checked)
        {
          this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_item SET " + this.namee + "= CONCAT ('" + this.tbItemName.Text + "'," + this.namee + ")WHERE a_index BETWEEN '" + this.tbRange1.Text + "' AND'" + this.tbRange2.Text + "';");
          int num = (int) new CustomMessage("DONE!").ShowDialog();
          new MassNameChanger().Close();
        }
        else if (this.tbItemName.Text != "" && this.tbRange1.Text != "" && this.tbRange2.Text.Equals(""))
        {
          int num1 = (int) new CustomMessage("Please Enter Range 2 Value").ShowDialog();
        }
        else if (this.tbItemName.Text != "" && this.tbRange1.Text.Equals("") && this.tbRange2.Text != "")
        {
          int num2 = (int) new CustomMessage("Please Enter Range 1 Value").ShowDialog();
        }
        else
        {
          if (!this.tbItemName.Text.Equals("") || !(this.tbRange1.Text != "") || !(this.tbRange2.Text != ""))
            return;
          int num3 = (int) new CustomMessage("Please Select a Name ").ShowDialog();
        }
      }
      else
      {
        int num4 = (int) new CustomMessage("Check one of the boxes").ShowDialog();
      }
    }

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

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (MassNameChanger));
      this.label3 = new Label();
      this.tbItemName = new TextBox();
      this.PbSelectID2 = new PictureBox();
      this.PbSelectID1 = new PictureBox();
      this.label2 = new Label();
      this.label1 = new Label();
      this.tbRange2 = new TextBox();
      this.tbRange1 = new TextBox();
      this.btnUpdateSelectedRange = new Button();
      this.cbRemoveBefore = new CheckBox();
      this.groupBox1 = new GroupBox();
      this.cbAddBefore = new CheckBox();
      ((ISupportInitialize) this.PbSelectID2).BeginInit();
      ((ISupportInitialize) this.PbSelectID1).BeginInit();
      this.groupBox1.SuspendLayout();
      this.SuspendLayout();
      this.label3.AutoSize = true;
      this.label3.Location = new Point(23, 8);
      this.label3.Name = "label3";
      this.label3.Size = new Size(58, 13);
      this.label3.TabIndex = 117;
      this.label3.Text = "Item Name";
      this.tbItemName.Location = new Point(96, 5);
      this.tbItemName.Name = "tbItemName";
      this.tbItemName.Size = new Size(211, 20);
      this.tbItemName.TabIndex = 116;
      this.tbItemName.Text = "Item Name";
      this.PbSelectID2.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbSelectID2.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbSelectID2.Location = new Point(286, 45);
      this.PbSelectID2.Name = "PbSelectID2";
      this.PbSelectID2.Size = new Size(22, 22);
      this.PbSelectID2.TabIndex = 115;
      this.PbSelectID2.TabStop = false;
      this.PbSelectID2.Click += new EventHandler(this.PbSelectID2_Click);
      this.PbSelectID1.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbSelectID1.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbSelectID1.Location = new Point(125, 45);
      this.PbSelectID1.Name = "PbSelectID1";
      this.PbSelectID1.Size = new Size(22, 22);
      this.PbSelectID1.TabIndex = 114;
      this.PbSelectID1.TabStop = false;
      this.PbSelectID1.Click += new EventHandler(this.PbSelectID1_Click);
      this.label2.AutoSize = true;
      this.label2.Location = new Point(199, 29);
      this.label2.Name = "label2";
      this.label2.Size = new Size(65, 13);
      this.label2.TabIndex = 113;
      this.label2.Text = "ItemRange2";
      this.label1.AutoSize = true;
      this.label1.Location = new Point(23, 27);
      this.label1.Name = "label1";
      this.label1.Size = new Size(65, 13);
      this.label1.TabIndex = 112;
      this.label1.Text = "ItemRange1";
      this.tbRange2.Location = new Point(182, 47);
      this.tbRange2.Name = "tbRange2";
      this.tbRange2.Size = new Size(100, 20);
      this.tbRange2.TabIndex = 111;
      this.tbRange2.Text = "End Index";
      this.tbRange1.Location = new Point(21, 46);
      this.tbRange1.Name = "tbRange1";
      this.tbRange1.Size = new Size(100, 20);
      this.tbRange1.TabIndex = 110;
      this.tbRange1.Text = "Start Index";
      this.btnUpdateSelectedRange.Location = new Point(15, 134);
      this.btnUpdateSelectedRange.Name = "btnUpdateSelectedRange";
      this.btnUpdateSelectedRange.Size = new Size(292, 23);
      this.btnUpdateSelectedRange.TabIndex = 109;
      this.btnUpdateSelectedRange.Text = "Update For Selected Items";
      this.btnUpdateSelectedRange.UseVisualStyleBackColor = true;
      this.btnUpdateSelectedRange.Click += new EventHandler(this.BtnUpdateSelectedRange_Click);
      this.cbRemoveBefore.AutoSize = true;
      this.cbRemoveBefore.Location = new Point(12, 16);
      this.cbRemoveBefore.Name = "cbRemoveBefore";
      this.cbRemoveBefore.Size = new Size(96, 17);
      this.cbRemoveBefore.TabIndex = 118;
      this.cbRemoveBefore.Text = "Remove String";
      this.cbRemoveBefore.UseVisualStyleBackColor = true;
      this.groupBox1.Controls.Add((Control) this.cbAddBefore);
      this.groupBox1.Controls.Add((Control) this.cbRemoveBefore);
      this.groupBox1.Location = new Point(19, 70);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(289, 58);
      this.groupBox1.TabIndex = 119;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "NameModify";
      this.cbAddBefore.AutoSize = true;
      this.cbAddBefore.Location = new Point(151, 15);
      this.cbAddBefore.Name = "cbAddBefore";
      this.cbAddBefore.Size = new Size(75, 17);
      this.cbAddBefore.TabIndex = 119;
      this.cbAddBefore.Text = "Add String";
      this.cbAddBefore.UseVisualStyleBackColor = true;
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(314, 159);
      this.Controls.Add((Control) this.groupBox1);
      this.Controls.Add((Control) this.label3);
      this.Controls.Add((Control) this.tbItemName);
      this.Controls.Add((Control) this.PbSelectID2);
      this.Controls.Add((Control) this.PbSelectID1);
      this.Controls.Add((Control) this.label2);
      this.Controls.Add((Control) this.label1);
      this.Controls.Add((Control) this.tbRange2);
      this.Controls.Add((Control) this.tbRange1);
      this.Controls.Add((Control) this.btnUpdateSelectedRange);
      this.Icon = (Icon) componentResourceManager.GetObject("$this.Icon");
      this.Name = nameof (MassNameChanger);
      this.StartPosition = FormStartPosition.CenterParent;
      this.Text = nameof (MassNameChanger);
      ((ISupportInitialize) this.PbSelectID2).EndInit();
      ((ISupportInitialize) this.PbSelectID1).EndInit();
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
