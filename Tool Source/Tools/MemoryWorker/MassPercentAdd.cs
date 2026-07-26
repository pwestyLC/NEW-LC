// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.MassPercentAdd
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using LcDevPack_TeamDamonA.Properties;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker
{
  public class MassPercentAdd : Form
  {
    private string Host = ItemEditor2.connection.Settings.SqlHost;
    private string User = ItemEditor2.connection.Settings.SqlUser;
    private string Password = ItemEditor2.connection.Settings.SqlPassword;
    private string Database = ItemEditor2.connection.Settings.SqlDatabase;
    private double result1;
    private double result2;
    private double result3;
    private double output1;
    private double output2;
    private double output3;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    private IContainer components = (IContainer) null;
    private PictureBox PbSelectID2;
    private PictureBox PbSelectID1;
    private Label lblRange2;
    private TextBox tbRange2;
    private TextBox tbRange1;
    private Label lblRange1;
    private TextBox TbNum1;
    private TextBox TbNum2;
    private TextBox TbNum0;
    private Label label1;
    private Label label2;
    private Label label3;
    private Label label4;
    private Label label5;
    private Label label6;
    private Button button1;
    private ToolTip toolTip1;
    private Button btnSubtract;

    private void TbNum0_KeyPress(object sender, KeyPressEventArgs e)
    {
      if (char.IsControl(e.KeyChar) || char.IsDigit(e.KeyChar))
        return;
      e.Handled = true;
    }

    private void TbNum1_KeyPress(object sender, KeyPressEventArgs e)
    {
      if (char.IsControl(e.KeyChar) || char.IsDigit(e.KeyChar))
        return;
      e.Handled = true;
    }

    private void TbNum2_KeyPress(object sender, KeyPressEventArgs e)
    {
      if (char.IsControl(e.KeyChar) || char.IsDigit(e.KeyChar))
        return;
      e.Handled = true;
    }

    private void TbRange1_KeyPress(object sender, KeyPressEventArgs e)
    {
      if (char.IsControl(e.KeyChar) || char.IsDigit(e.KeyChar))
        return;
      e.Handled = true;
    }

    private void TbRange2_KeyPress(object sender, KeyPressEventArgs e)
    {
      if (char.IsControl(e.KeyChar) || char.IsDigit(e.KeyChar))
        return;
      e.Handled = true;
    }

    private void btnSubtract_Click(object sender, EventArgs e)
    {
      if (this.TbNum0.Text != "" && this.TbNum1.Text != "" && this.TbNum2.Text != "")
      {
        this.result1 = Convert.ToDouble(this.TbNum0.Text);
        this.result2 = Convert.ToDouble(this.TbNum1.Text);
        this.result3 = Convert.ToDouble(this.TbNum2.Text);
        this.output1 = this.result1 / 100.0;
        this.output2 = this.result2 / 100.0;
        this.output3 = this.result3 / 100.0;
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_item SET a_num_0 = (a_num_0 * 1) - a_num_0 * '" + this.output1.ToString() + "', a_num_1 = (a_num_1 * 1) - a_num_1 * '" + this.output2.ToString() + "', a_num_2 = (a_num_2 *1) - a_num_2 * '" + this.output3.ToString() + "' " + " WHERE a_index BETWEEN '" + this.tbRange1.Text + "' AND'" + this.tbRange2.Text + "';");
        this.Close();
      }
      else
      {
        if (this.TbNum0.Text == "" || this.TbNum1.Text == "" || this.TbNum2.Text == "" || !this.tbRange2.Text.Equals("") && !this.tbRange1.Text.Equals(""))
          return;
        int num = (int) new CustomMessage("Please Enter 2 Ranges of Numbers").ShowDialog();
      }
    }

    public MassPercentAdd() => this.InitializeComponent();

    private void Button1_Click(object sender, EventArgs e)
    {
      if (this.TbNum0.Text != "" && this.TbNum1.Text != "" && this.TbNum2.Text != "")
      {
        this.result1 = Convert.ToDouble(this.TbNum0.Text);
        this.result2 = Convert.ToDouble(this.TbNum1.Text);
        this.result3 = Convert.ToDouble(this.TbNum2.Text);
        this.output1 = this.result1 / 100.0;
        this.output2 = this.result2 / 100.0;
        this.output3 = this.result3 / 100.0;
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "UPDATE t_item SET a_num_0 = (a_num_0 * 1) + a_num_0 * '" + this.output1.ToString() + "', a_num_1 = (a_num_1 * 1) + a_num_1 * '" + this.output2.ToString() + "', a_num_2 = (a_num_2 *1) + a_num_2 * '" + this.output3.ToString() + "' " + " WHERE a_index BETWEEN '" + this.tbRange1.Text + "' AND'" + this.tbRange2.Text + "';");
        this.Close();
      }
      else
      {
        if (this.TbNum0.Text == "" || this.TbNum1.Text == "" || this.TbNum2.Text == "" || !this.tbRange2.Text.Equals("") && !this.tbRange1.Text.Equals(""))
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
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (MassPercentAdd));
      this.PbSelectID2 = new PictureBox();
      this.PbSelectID1 = new PictureBox();
      this.lblRange2 = new Label();
      this.tbRange2 = new TextBox();
      this.tbRange1 = new TextBox();
      this.lblRange1 = new Label();
      this.TbNum1 = new TextBox();
      this.TbNum2 = new TextBox();
      this.TbNum0 = new TextBox();
      this.label1 = new Label();
      this.label2 = new Label();
      this.label3 = new Label();
      this.label4 = new Label();
      this.label5 = new Label();
      this.label6 = new Label();
      this.button1 = new Button();
      this.toolTip1 = new ToolTip(this.components);
      this.btnSubtract = new Button();
      ((ISupportInitialize) this.PbSelectID2).BeginInit();
      ((ISupportInitialize) this.PbSelectID1).BeginInit();
      this.SuspendLayout();
      this.PbSelectID2.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbSelectID2.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbSelectID2.Location = new Point(188, 63);
      this.PbSelectID2.Name = "PbSelectID2";
      this.PbSelectID2.Size = new Size(22, 22);
      this.PbSelectID2.TabIndex = 111;
      this.PbSelectID2.TabStop = false;
      this.PbSelectID2.Click += new EventHandler(this.PbSelectID2_Click);
      this.PbSelectID1.BackgroundImage = (Image) Resources.oie_transparent;
      this.PbSelectID1.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbSelectID1.Location = new Point(186, 23);
      this.PbSelectID1.Name = "PbSelectID1";
      this.PbSelectID1.Size = new Size(22, 22);
      this.PbSelectID1.TabIndex = 110;
      this.PbSelectID1.TabStop = false;
      this.PbSelectID1.Click += new EventHandler(this.PbSelectID1_Click);
      this.lblRange2.AutoSize = true;
      this.lblRange2.Location = new Point(126, 48);
      this.lblRange2.Name = "lblRange2";
      this.lblRange2.Size = new Size(45, 13);
      this.lblRange2.TabIndex = 109;
      this.lblRange2.Text = "Range2";
      this.tbRange2.Location = new Point(111, 64);
      this.tbRange2.Name = "tbRange2";
      this.tbRange2.Size = new Size(72, 20);
      this.tbRange2.TabIndex = 108;
      this.toolTip1.SetToolTip((Control) this.tbRange2, "End Index");
      this.tbRange2.KeyPress += new KeyPressEventHandler(this.TbRange2_KeyPress);
      this.tbRange1.Location = new Point(108, 25);
      this.tbRange1.Name = "tbRange1";
      this.tbRange1.Size = new Size(72, 20);
      this.tbRange1.TabIndex = 107;
      this.toolTip1.SetToolTip((Control) this.tbRange1, "Start Index");
      this.tbRange1.KeyPress += new KeyPressEventHandler(this.TbRange1_KeyPress);
      this.lblRange1.AutoSize = true;
      this.lblRange1.Location = new Point(126, 9);
      this.lblRange1.Name = "lblRange1";
      this.lblRange1.Size = new Size(45, 13);
      this.lblRange1.TabIndex = 106;
      this.lblRange1.Text = "Range1";
      this.TbNum1.Location = new Point(38, 45);
      this.TbNum1.Name = "TbNum1";
      this.TbNum1.Size = new Size(46, 20);
      this.TbNum1.TabIndex = 112;
      this.TbNum1.Text = "0";
      this.toolTip1.SetToolTip((Control) this.TbNum1, "Magical Defence/Magical Attack");
      this.TbNum1.KeyPress += new KeyPressEventHandler(this.TbNum1_KeyPress);
      this.TbNum2.Location = new Point(38, 68);
      this.TbNum2.Name = "TbNum2";
      this.TbNum2.Size = new Size(46, 20);
      this.TbNum2.TabIndex = 113;
      this.TbNum2.Text = "0";
      this.toolTip1.SetToolTip((Control) this.TbNum2, "Flight Speed/Attack Speed");
      this.TbNum2.KeyPress += new KeyPressEventHandler(this.TbNum2_KeyPress);
      this.TbNum0.Location = new Point(38, 19);
      this.TbNum0.Name = "TbNum0";
      this.TbNum0.Size = new Size(46, 20);
      this.TbNum0.TabIndex = 114;
      this.TbNum0.Text = "0";
      this.toolTip1.SetToolTip((Control) this.TbNum0, "Physical Defence/Physical Attack");
      this.TbNum0.KeyPress += new KeyPressEventHandler(this.TbNum0_KeyPress);
      this.label1.AutoSize = true;
      this.label1.Location = new Point(3, 22);
      this.label1.Name = "label1";
      this.label1.Size = new Size(35, 13);
      this.label1.TabIndex = 115;
      this.label1.Text = "Num0";
      this.label2.AutoSize = true;
      this.label2.Location = new Point(3, 48);
      this.label2.Name = "label2";
      this.label2.Size = new Size(35, 13);
      this.label2.TabIndex = 116;
      this.label2.Text = "Num1";
      this.label3.AutoSize = true;
      this.label3.Location = new Point(3, 71);
      this.label3.Name = "label3";
      this.label3.Size = new Size(35, 13);
      this.label3.TabIndex = 117;
      this.label3.Text = "Num3";
      this.label4.AutoSize = true;
      this.label4.Location = new Point(87, 23);
      this.label4.Name = "label4";
      this.label4.Size = new Size(15, 13);
      this.label4.TabIndex = 106;
      this.label4.Text = "%";
      this.label5.AutoSize = true;
      this.label5.Location = new Point(87, 75);
      this.label5.Name = "label5";
      this.label5.Size = new Size(15, 13);
      this.label5.TabIndex = 118;
      this.label5.Text = "%";
      this.label6.AutoSize = true;
      this.label6.Location = new Point(87, 52);
      this.label6.Name = "label6";
      this.label6.Size = new Size(15, 13);
      this.label6.TabIndex = 119;
      this.label6.Text = "%";
      this.button1.Location = new Point(11, 95);
      this.button1.Name = "button1";
      this.button1.Size = new Size(197, 23);
      this.button1.TabIndex = 120;
      this.button1.Text = "Add Percent";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.Button1_Click);
      this.btnSubtract.Location = new Point(11, 124);
      this.btnSubtract.Name = "btnSubtract";
      this.btnSubtract.Size = new Size(197, 23);
      this.btnSubtract.TabIndex = 121;
      this.btnSubtract.Text = "Subtract Percent";
      this.btnSubtract.UseVisualStyleBackColor = true;
      this.btnSubtract.Click += new EventHandler(this.btnSubtract_Click);
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(219, 151);
      this.Controls.Add((Control) this.btnSubtract);
      this.Controls.Add((Control) this.button1);
      this.Controls.Add((Control) this.label6);
      this.Controls.Add((Control) this.label5);
      this.Controls.Add((Control) this.label4);
      this.Controls.Add((Control) this.label3);
      this.Controls.Add((Control) this.label2);
      this.Controls.Add((Control) this.label1);
      this.Controls.Add((Control) this.TbNum0);
      this.Controls.Add((Control) this.TbNum2);
      this.Controls.Add((Control) this.TbNum1);
      this.Controls.Add((Control) this.PbSelectID2);
      this.Controls.Add((Control) this.PbSelectID1);
      this.Controls.Add((Control) this.lblRange2);
      this.Controls.Add((Control) this.tbRange2);
      this.Controls.Add((Control) this.tbRange1);
      this.Controls.Add((Control) this.lblRange1);
      this.FormBorderStyle = FormBorderStyle.Fixed3D;
      this.Icon = (Icon) componentResourceManager.GetObject("$this.Icon");
      this.MaximizeBox = false;
      this.MinimizeBox = false;
      this.Name = nameof (MassPercentAdd);
      this.StartPosition = FormStartPosition.CenterParent;
      this.Text = nameof (MassPercentAdd);
      ((ISupportInitialize) this.PbSelectID2).EndInit();
      ((ISupportInitialize) this.PbSelectID1).EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
