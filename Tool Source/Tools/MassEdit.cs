// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MassEdit
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
  public class MassEdit : Form
  {
    private string Host = ItemEditor2.connection.Settings.SqlHost;
    private string User = ItemEditor2.connection.Settings.SqlUser;
    private string Password = ItemEditor2.connection.Settings.SqlPassword;
    private string Database = ItemEditor2.connection.Settings.SqlDatabase;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    private IContainer components = (IContainer) null;
    private TextBox TbMinLevelMass;
    private TextBox tbMaxLevelMass;
    private TextBox tbFlagMass;
    private Label lblFlagMass;
    private Label lblLevelMass;
    private Label lblMaxLevelMass;
    private Label lblNum0Mass;
    private Label lblNum1Mass;
    private Label lblNum2Mass;
    private TextBox tbNum0Mass;
    private TextBox tbNum1Mass;
    private TextBox tbNum2Mass;
    private TextBox tbPriceMass;
    private TextBox tbStackMass;
    private Label lblPriceMass;
    private Label lblStackMass;
    private Label lblRange1;
    private TextBox tbRange1;
    private TextBox tbRange2;
    private Label lblUpdatee;
    private Label lblRange2;
    private Label lblInstruction;
    private Label label1;
    private Button btnUpdateMass;
    private PictureBox PbSelectID1;
    private PictureBox PbSelectID2;
    private ToolTip toolTip1;

    public MassEdit() => this.InitializeComponent();

    private void textBox6_TextChanged(object sender, EventArgs e)
    {
    }

    private void btnUpdateMass_Click(object sender, EventArgs e)
    {
      if (this.TbMinLevelMass.Text != "" && this.tbMaxLevelMass.Text != "" && this.tbFlagMass.Text != "" && this.tbNum0Mass.Text != "" && this.tbNum1Mass.Text != "" && this.tbNum2Mass.Text != "" && this.tbPriceMass.Text != "" && this.tbStackMass.Text != "" && this.tbRange1.Text != "" && this.tbRange2.Text != "")
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_item SET a_level = '" + this.TbMinLevelMass.Text + "', a_level2 = '" + this.tbMaxLevelMass.Text + "', a_flag = '" + this.tbFlagMass.Text + "', " + "a_price = '" + this.tbPriceMass.Text + "', a_num_0 = '" + this.tbNum0Mass.Text + "', a_num_1 = '" + this.tbNum1Mass.Text + "', a_num_2 = '" + this.tbNum2Mass.Text + "', a_weight = '" + this.tbStackMass.Text + "' WHERE a_index BETWEEN '" + this.tbRange1.Text + "' AND'" + this.tbRange2.Text + "';");
        this.Close();
      }
      else
      {
        if (!this.tbRange2.Text.Equals("") && !this.tbRange1.Text.Equals(""))
          return;
        int num = (int) new CustomMessage("Please Enter 2 Ranges of Numbers").ShowDialog();
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
      this.components = (IContainer) new System.ComponentModel.Container();
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (MassEdit));
      this.TbMinLevelMass = new TextBox();
      this.tbMaxLevelMass = new TextBox();
      this.tbFlagMass = new TextBox();
      this.lblFlagMass = new Label();
      this.lblLevelMass = new Label();
      this.lblMaxLevelMass = new Label();
      this.lblNum0Mass = new Label();
      this.lblNum1Mass = new Label();
      this.lblNum2Mass = new Label();
      this.tbNum0Mass = new TextBox();
      this.tbNum1Mass = new TextBox();
      this.tbNum2Mass = new TextBox();
      this.tbPriceMass = new TextBox();
      this.tbStackMass = new TextBox();
      this.lblPriceMass = new Label();
      this.lblStackMass = new Label();
      this.lblRange1 = new Label();
      this.tbRange1 = new TextBox();
      this.tbRange2 = new TextBox();
      this.lblUpdatee = new Label();
      this.lblRange2 = new Label();
      this.lblInstruction = new Label();
      this.label1 = new Label();
      this.btnUpdateMass = new Button();
      this.PbSelectID1 = new PictureBox();
      this.PbSelectID2 = new PictureBox();
      this.toolTip1 = new ToolTip(this.components);
      ((ISupportInitialize) this.PbSelectID1).BeginInit();
      ((ISupportInitialize) this.PbSelectID2).BeginInit();
      this.SuspendLayout();
      this.TbMinLevelMass.Location = new Point(64, 122);
      this.TbMinLevelMass.Name = "TbMinLevelMass";
      this.TbMinLevelMass.Size = new Size(72, 20);
      this.TbMinLevelMass.TabIndex = 0;
      this.tbMaxLevelMass.Location = new Point(64, 161);
      this.tbMaxLevelMass.Name = "tbMaxLevelMass";
      this.tbMaxLevelMass.Size = new Size(72, 20);
      this.tbMaxLevelMass.TabIndex = 1;
      this.tbFlagMass.Location = new Point(64, 203);
      this.tbFlagMass.Name = "tbFlagMass";
      this.tbFlagMass.Size = new Size(72, 20);
      this.tbFlagMass.TabIndex = 2;
      this.toolTip1.SetToolTip((Control) this.tbFlagMass, "Item Flag");
      this.lblFlagMass.AutoSize = true;
      this.lblFlagMass.Location = new Point(14, 207);
      this.lblFlagMass.Name = "lblFlagMass";
      this.lblFlagMass.Size = new Size(27, 13);
      this.lblFlagMass.TabIndex = 3;
      this.lblFlagMass.Text = "Flag";
      this.lblLevelMass.AutoSize = true;
      this.lblLevelMass.Location = new Point(12, 125);
      this.lblLevelMass.Name = "lblLevelMass";
      this.lblLevelMass.Size = new Size(46, 13);
      this.lblLevelMass.TabIndex = 4;
      this.lblLevelMass.Text = "Minlevel";
      this.lblMaxLevelMass.AutoSize = true;
      this.lblMaxLevelMass.Location = new Point(9, 166);
      this.lblMaxLevelMass.Name = "lblMaxLevelMass";
      this.lblMaxLevelMass.Size = new Size(49, 13);
      this.lblMaxLevelMass.TabIndex = 5;
      this.lblMaxLevelMass.Text = "Maxlevel";
      this.lblNum0Mass.AutoSize = true;
      this.lblNum0Mass.Location = new Point(169, 125);
      this.lblNum0Mass.Name = "lblNum0Mass";
      this.lblNum0Mass.Size = new Size(35, 13);
      this.lblNum0Mass.TabIndex = 6;
      this.lblNum0Mass.Text = "Num0";
      this.lblNum1Mass.AutoSize = true;
      this.lblNum1Mass.Location = new Point(169, 168);
      this.lblNum1Mass.Name = "lblNum1Mass";
      this.lblNum1Mass.Size = new Size(35, 13);
      this.lblNum1Mass.TabIndex = 7;
      this.lblNum1Mass.Text = "Num1";
      this.lblNum2Mass.AutoSize = true;
      this.lblNum2Mass.Location = new Point(169, 210);
      this.lblNum2Mass.Name = "lblNum2Mass";
      this.lblNum2Mass.Size = new Size(35, 13);
      this.lblNum2Mass.TabIndex = 8;
      this.lblNum2Mass.Text = "Num2";
      this.tbNum0Mass.Location = new Point(219, 122);
      this.tbNum0Mass.Name = "tbNum0Mass";
      this.tbNum0Mass.Size = new Size(72, 20);
      this.tbNum0Mass.TabIndex = 9;
      this.tbNum1Mass.Location = new Point(219, 163);
      this.tbNum1Mass.Name = "tbNum1Mass";
      this.tbNum1Mass.Size = new Size(72, 20);
      this.tbNum1Mass.TabIndex = 10;
      this.tbNum2Mass.Location = new Point(219, 207);
      this.tbNum2Mass.Name = "tbNum2Mass";
      this.tbNum2Mass.Size = new Size(72, 20);
      this.tbNum2Mass.TabIndex = 11;
      this.tbNum2Mass.TextChanged += new EventHandler(this.textBox6_TextChanged);
      this.tbPriceMass.Location = new Point(64, 244);
      this.tbPriceMass.Name = "tbPriceMass";
      this.tbPriceMass.Size = new Size(72, 20);
      this.tbPriceMass.TabIndex = 12;
      this.tbStackMass.Location = new Point(219, 244);
      this.tbStackMass.Name = "tbStackMass";
      this.tbStackMass.Size = new Size(72, 20);
      this.tbStackMass.TabIndex = 13;
      this.toolTip1.SetToolTip((Control) this.tbStackMass, "Items hold limit ");
      this.lblPriceMass.AutoSize = true;
      this.lblPriceMass.Location = new Point(12, 247);
      this.lblPriceMass.Name = "lblPriceMass";
      this.lblPriceMass.Size = new Size(31, 13);
      this.lblPriceMass.TabIndex = 14;
      this.lblPriceMass.Text = "Price";
      this.lblStackMass.AutoSize = true;
      this.lblStackMass.Location = new Point(171, 247);
      this.lblStackMass.Name = "lblStackMass";
      this.lblStackMass.Size = new Size(35, 13);
      this.lblStackMass.TabIndex = 15;
      this.lblStackMass.Text = "Stack";
      this.lblRange1.AutoSize = true;
      this.lblRange1.Location = new Point(45, 45);
      this.lblRange1.Name = "lblRange1";
      this.lblRange1.Size = new Size(45, 13);
      this.lblRange1.TabIndex = 16;
      this.lblRange1.Text = "Range1";
      this.tbRange1.Location = new Point(30, 61);
      this.tbRange1.Name = "tbRange1";
      this.tbRange1.Size = new Size(72, 20);
      this.tbRange1.TabIndex = 17;
      this.toolTip1.SetToolTip((Control) this.tbRange1, "Start Index");
      this.tbRange2.Location = new Point(179, 61);
      this.tbRange2.Name = "tbRange2";
      this.tbRange2.Size = new Size(72, 20);
      this.tbRange2.TabIndex = 18;
      this.toolTip1.SetToolTip((Control) this.tbRange2, "End Index");
      this.lblUpdatee.AutoSize = true;
      this.lblUpdatee.Font = new Font("Microsoft Sans Serif", 8.25f, FontStyle.Bold, GraphicsUnit.Point, (byte) 0);
      this.lblUpdatee.Location = new Point(0, 92);
      this.lblUpdatee.Name = "lblUpdatee";
      this.lblUpdatee.Size = new Size(301, 13);
      this.lblUpdatee.TabIndex = 19;
      this.lblUpdatee.Text = "Update the Following Options for a Range of Indexs";
      this.lblRange2.AutoSize = true;
      this.lblRange2.Location = new Point(194, 45);
      this.lblRange2.Name = "lblRange2";
      this.lblRange2.Size = new Size(45, 13);
      this.lblRange2.TabIndex = 20;
      this.lblRange2.Text = "Range2";
      this.lblInstruction.AutoSize = true;
      this.lblInstruction.Font = new Font("Microsoft Sans Serif", 8.25f, FontStyle.Bold, GraphicsUnit.Point, (byte) 0);
      this.lblInstruction.Location = new Point(27, 9);
      this.lblInstruction.Name = "lblInstruction";
      this.lblInstruction.Size = new Size(272, 13);
      this.lblInstruction.TabIndex = 21;
      this.lblInstruction.Text = "Enter the Range of Indexs you Want to Adjust ";
      this.label1.AutoSize = true;
      this.label1.Font = new Font("Microsoft Sans Serif", 8.25f, FontStyle.Bold, GraphicsUnit.Point, (byte) 0);
      this.label1.Location = new Point(30, 25);
      this.label1.Name = "label1";
      this.label1.Size = new Size(153, 13);
      this.label1.TabIndex = 22;
      this.label1.Text = "Ex: Between 500 and 600";
      this.btnUpdateMass.Font = new Font("Microsoft Sans Serif", 8.25f, FontStyle.Bold, GraphicsUnit.Point, (byte) 0);
      this.btnUpdateMass.Location = new Point(101, 270);
      this.btnUpdateMass.Name = "btnUpdateMass";
      this.btnUpdateMass.Size = new Size(122, 23);
      this.btnUpdateMass.TabIndex = 23;
      this.btnUpdateMass.Text = "Update";
      this.btnUpdateMass.UseVisualStyleBackColor = true;
      this.btnUpdateMass.Click += new EventHandler(this.btnUpdateMass_Click);
      this.PbSelectID1.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbSelectID1.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbSelectID1.Location = new Point(109, 61);
      this.PbSelectID1.Name = "PbSelectID1";
      this.PbSelectID1.Size = new Size(22, 22);
      this.PbSelectID1.TabIndex = 104;
      this.PbSelectID1.TabStop = false;
      this.PbSelectID1.Click += new EventHandler(this.PbSelectID1_Click);
      this.PbSelectID2.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbSelectID2.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbSelectID2.Location = new Point(257, 61);
      this.PbSelectID2.Name = "PbSelectID2";
      this.PbSelectID2.Size = new Size(22, 22);
      this.PbSelectID2.TabIndex = 105;
      this.PbSelectID2.TabStop = false;
      this.PbSelectID2.Click += new EventHandler(this.PbSelectID2_Click);
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(303, 303);
      this.Controls.Add((Control) this.PbSelectID2);
      this.Controls.Add((Control) this.PbSelectID1);
      this.Controls.Add((Control) this.btnUpdateMass);
      this.Controls.Add((Control) this.label1);
      this.Controls.Add((Control) this.lblInstruction);
      this.Controls.Add((Control) this.lblRange2);
      this.Controls.Add((Control) this.lblUpdatee);
      this.Controls.Add((Control) this.tbRange2);
      this.Controls.Add((Control) this.tbRange1);
      this.Controls.Add((Control) this.lblRange1);
      this.Controls.Add((Control) this.lblStackMass);
      this.Controls.Add((Control) this.lblPriceMass);
      this.Controls.Add((Control) this.tbStackMass);
      this.Controls.Add((Control) this.tbPriceMass);
      this.Controls.Add((Control) this.tbNum2Mass);
      this.Controls.Add((Control) this.tbNum1Mass);
      this.Controls.Add((Control) this.tbNum0Mass);
      this.Controls.Add((Control) this.lblNum2Mass);
      this.Controls.Add((Control) this.lblNum1Mass);
      this.Controls.Add((Control) this.lblNum0Mass);
      this.Controls.Add((Control) this.lblMaxLevelMass);
      this.Controls.Add((Control) this.lblLevelMass);
      this.Controls.Add((Control) this.lblFlagMass);
      this.Controls.Add((Control) this.tbFlagMass);
      this.Controls.Add((Control) this.tbMaxLevelMass);
      this.Controls.Add((Control) this.TbMinLevelMass);
      this.FormBorderStyle = FormBorderStyle.Fixed3D;
      this.Icon = (Icon) componentResourceManager.GetObject("$this.Icon");
      this.MaximizeBox = false;
      this.MinimizeBox = false;
      this.Name = nameof (MassEdit);
      this.Text = nameof (MassEdit);
      ((ISupportInitialize) this.PbSelectID1).EndInit();
      ((ISupportInitialize) this.PbSelectID2).EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
