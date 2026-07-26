// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.LangSelect
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using LcDevPack_TeamDamonA.Tools;
using System;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA
{
  public class LangSelect : Form
  {
    public static Connection connection = new Connection();
        private string language => LangSelect.connection.Settings.Language;
        public string Language = ""; // You can keep this if you still need a form-level copy
        private string Host => LangSelect.connection.Settings.SqlHost;
        private string User => LangSelect.connection.Settings.SqlUser;
        private string Password => LangSelect.connection.Settings.SqlPassword;
        private string Database => LangSelect.connection.Settings.SqlDatabase;
        private string DB_Database => LangSelect.connection.Settings.SqlDbDatabase;
        private string DB_Auth => LangSelect.connection.Settings.SqlDbAuth;
        private string ClientPath => LangSelect.connection.Settings.ClientPath;

        private string buffer = "Rb";
    private IContainer components = (IContainer) null;
    private GroupBox GbLangSelect;
    private Button BtnSave;
    private RadioButton RbMEX;
    private RadioButton RbBRA;
    private RadioButton RbESP;
    private RadioButton RbPOL;
    private RadioButton RbTHA;
    private RadioButton RbRUS;
    private RadioButton RbITA;
    private RadioButton RbFRA;
    private RadioButton RbGER;
    private RadioButton RbUSA;

    public LangSelect() => this.InitializeComponent();

    private void LoadColorFromConfig()
    {
      if (this.RbBRA.Text == this.language)
      {
        this.RbBRA.Checked = true;
        this.RbESP.Checked = false;
        this.RbFRA.Checked = false;
        this.RbGER.Checked = false;
        this.RbITA.Checked = false;
        this.RbMEX.Checked = false;
        this.RbPOL.Checked = false;
        this.RbRUS.Checked = false;
        this.RbTHA.Checked = false;
        this.RbUSA.Checked = false;
      }
      else if (this.RbESP.Text == this.language)
      {
        this.RbBRA.Checked = false;
        this.RbESP.Checked = true;
        this.RbFRA.Checked = false;
        this.RbGER.Checked = false;
        this.RbITA.Checked = false;
        this.RbMEX.Checked = false;
        this.RbPOL.Checked = false;
        this.RbRUS.Checked = false;
        this.RbTHA.Checked = false;
        this.RbUSA.Checked = false;
      }
      else if (this.RbFRA.Text == this.language)
      {
        this.RbBRA.Checked = false;
        this.RbESP.Checked = false;
        this.RbFRA.Checked = true;
        this.RbGER.Checked = false;
        this.RbITA.Checked = false;
        this.RbMEX.Checked = false;
        this.RbPOL.Checked = false;
        this.RbRUS.Checked = false;
        this.RbTHA.Checked = false;
        this.RbUSA.Checked = false;
      }
      else if (this.RbGER.Text == this.language)
      {
        this.RbBRA.Checked = false;
        this.RbESP.Checked = false;
        this.RbFRA.Checked = false;
        this.RbGER.Checked = true;
        this.RbITA.Checked = false;
        this.RbMEX.Checked = false;
        this.RbPOL.Checked = false;
        this.RbRUS.Checked = false;
        this.RbTHA.Checked = false;
        this.RbUSA.Checked = false;
      }
      else if (this.RbITA.Text == this.language)
      {
        this.RbBRA.Checked = false;
        this.RbESP.Checked = false;
        this.RbFRA.Checked = false;
        this.RbGER.Checked = false;
        this.RbITA.Checked = true;
        this.RbMEX.Checked = false;
        this.RbPOL.Checked = false;
        this.RbRUS.Checked = false;
        this.RbTHA.Checked = false;
        this.RbUSA.Checked = false;
      }
      else if (this.RbMEX.Text == this.language)
      {
        this.RbBRA.Checked = false;
        this.RbESP.Checked = false;
        this.RbFRA.Checked = false;
        this.RbGER.Checked = false;
        this.RbITA.Checked = false;
        this.RbMEX.Checked = true;
        this.RbPOL.Checked = false;
        this.RbRUS.Checked = false;
        this.RbTHA.Checked = false;
        this.RbUSA.Checked = false;
      }
      else if (this.RbPOL.Text == this.language)
      {
        this.RbBRA.Checked = false;
        this.RbESP.Checked = false;
        this.RbFRA.Checked = false;
        this.RbGER.Checked = false;
        this.RbITA.Checked = false;
        this.RbMEX.Checked = false;
        this.RbPOL.Checked = true;
        this.RbRUS.Checked = false;
        this.RbTHA.Checked = false;
        this.RbUSA.Checked = false;
      }
      else if (this.RbRUS.Text == this.language)
      {
        this.RbBRA.Checked = false;
        this.RbESP.Checked = false;
        this.RbFRA.Checked = false;
        this.RbGER.Checked = false;
        this.RbITA.Checked = false;
        this.RbMEX.Checked = false;
        this.RbPOL.Checked = false;
        this.RbRUS.Checked = true;
        this.RbTHA.Checked = false;
        this.RbUSA.Checked = false;
      }
      else if (this.RbTHA.Text == this.language)
      {
        this.RbBRA.Checked = false;
        this.RbESP.Checked = false;
        this.RbFRA.Checked = false;
        this.RbGER.Checked = false;
        this.RbITA.Checked = false;
        this.RbMEX.Checked = false;
        this.RbPOL.Checked = false;
        this.RbRUS.Checked = false;
        this.RbTHA.Checked = true;
        this.RbUSA.Checked = false;
      }
      else if (this.RbUSA.Text == this.language)
      {
        this.RbBRA.Checked = false;
        this.RbESP.Checked = false;
        this.RbFRA.Checked = false;
        this.RbGER.Checked = false;
        this.RbITA.Checked = false;
        this.RbMEX.Checked = false;
        this.RbPOL.Checked = false;
        this.RbRUS.Checked = false;
        this.RbTHA.Checked = false;
        this.RbUSA.Checked = true;
      }
      else
      {
        if (!(this.language != this.RbBRA.Text) || !(this.language != this.RbESP.Text) || !(this.language != this.RbFRA.Text) || !(this.language != this.RbGER.Text) || !(this.language != this.RbITA.Text) || !(this.language != this.RbMEX.Text) || !(this.language != this.RbPOL.Text) || !(this.language != this.RbRUS.Text) || !(this.language != this.RbTHA.Text) || !(this.language != this.RbUSA.Text))
          return;
        this.RbUSA.Checked = true;
        int num = (int) MessageBox.Show("please check your config for proper language format");
      }
    }

    private void BtnSave_Click(object sender, EventArgs e)
    {
      if (this.RbBRA.Checked)
        this.Language = this.RbBRA.Text;
      else if (this.RbESP.Checked)
        this.Language = this.RbESP.Text;
      else if (this.RbFRA.Checked)
        this.Language = this.RbFRA.Text;
      else if (this.RbGER.Checked)
        this.Language = this.RbGER.Text;
      else if (this.RbITA.Checked)
        this.Language = this.RbITA.Text;
      else if (this.RbMEX.Checked)
        this.Language = this.RbMEX.Text;
      else if (this.RbPOL.Checked)
        this.Language = this.RbPOL.Text;
      else if (this.RbRUS.Checked)
        this.Language = this.RbRUS.Text;
      else if (this.RbTHA.Checked)
        this.Language = this.RbTHA.Text;
      else if (this.RbUSA.Checked)
        this.Language = this.RbUSA.Text;
      try
      {
        TextWriter textWriter = (TextWriter) new StreamWriter("Config//Settings.cfg");
        textWriter.WriteLine("## MYSQL");
        textWriter.WriteLine("Episode=EP4");
        textWriter.WriteLine("ClientPath=" + this.ClientPath);
        textWriter.WriteLine("[## MYSQL]");
        textWriter.WriteLine("SQL_HOST=" + this.Host);
        textWriter.WriteLine("SQL_USER=" + this.User);
        textWriter.WriteLine("SQL_PASSWORD=" + this.Password);
        textWriter.WriteLine("SQL_DATABASE=" + this.Database);
        textWriter.WriteLine("SQL_DB_DATABASE=" + this.DB_Database);
        textWriter.WriteLine("SQL_DB_AUTH=" + this.DB_Auth);
        textWriter.WriteLine("Language=" + this.Language);
        textWriter.WriteLine("##language list");
        textWriter.WriteLine("GER");
        textWriter.WriteLine("POL");
        textWriter.WriteLine("BRA");
        textWriter.WriteLine("RUS");
        textWriter.WriteLine("FRA");
        textWriter.WriteLine("ESP");
        textWriter.WriteLine("MEX");
        textWriter.WriteLine("THA");
        textWriter.WriteLine("ITA");
        textWriter.WriteLine("USA");
        textWriter.Close();
        int num = (int) new CustomMessage("Saved!").ShowDialog();
        Application.Restart();
      }
      catch
      {
        int num = (int) new CustomMessage("failed :(").ShowDialog();
      }
    }

    private void LangSelect_Load(object sender, EventArgs e) => this.LoadColorFromConfig();

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (LangSelect));
      this.GbLangSelect = new GroupBox();
      this.BtnSave = new Button();
      this.RbMEX = new RadioButton();
      this.RbBRA = new RadioButton();
      this.RbESP = new RadioButton();
      this.RbPOL = new RadioButton();
      this.RbTHA = new RadioButton();
      this.RbRUS = new RadioButton();
      this.RbITA = new RadioButton();
      this.RbFRA = new RadioButton();
      this.RbGER = new RadioButton();
      this.RbUSA = new RadioButton();
      this.GbLangSelect.SuspendLayout();
      this.SuspendLayout();
      this.GbLangSelect.Controls.Add((Control) this.BtnSave);
      this.GbLangSelect.Controls.Add((Control) this.RbMEX);
      this.GbLangSelect.Controls.Add((Control) this.RbBRA);
      this.GbLangSelect.Controls.Add((Control) this.RbESP);
      this.GbLangSelect.Controls.Add((Control) this.RbPOL);
      this.GbLangSelect.Controls.Add((Control) this.RbTHA);
      this.GbLangSelect.Controls.Add((Control) this.RbRUS);
      this.GbLangSelect.Controls.Add((Control) this.RbITA);
      this.GbLangSelect.Controls.Add((Control) this.RbFRA);
      this.GbLangSelect.Controls.Add((Control) this.RbGER);
      this.GbLangSelect.Controls.Add((Control) this.RbUSA);
      this.GbLangSelect.Location = new Point(7, 12);
      this.GbLangSelect.Name = "GbLangSelect";
      this.GbLangSelect.Size = new Size(369, 77);
      this.GbLangSelect.TabIndex = 0;
      this.GbLangSelect.TabStop = false;
      this.GbLangSelect.Text = "Language";
      this.BtnSave.Location = new Point(318, 19);
      this.BtnSave.Name = "BtnSave";
      this.BtnSave.Size = new Size(45, 52);
      this.BtnSave.TabIndex = 10;
      this.BtnSave.Text = "Save";
      this.BtnSave.UseVisualStyleBackColor = true;
      this.BtnSave.Click += new EventHandler(this.BtnSave_Click);
      this.RbMEX.AutoSize = true;
      this.RbMEX.Location = new Point(264, 54);
      this.RbMEX.Name = "RbMEX";
      this.RbMEX.Size = new Size(48, 17);
      this.RbMEX.TabIndex = 9;
      this.RbMEX.Text = "MEX";
      this.RbMEX.UseVisualStyleBackColor = true;
      this.RbBRA.AutoSize = true;
      this.RbBRA.Location = new Point(264, 20);
      this.RbBRA.Name = "RbBRA";
      this.RbBRA.Size = new Size(47, 17);
      this.RbBRA.TabIndex = 8;
      this.RbBRA.Text = "BRA";
      this.RbBRA.UseVisualStyleBackColor = true;
      this.RbESP.AutoSize = true;
      this.RbESP.Location = new Point(204, 54);
      this.RbESP.Name = "RbESP";
      this.RbESP.Size = new Size(46, 17);
      this.RbESP.TabIndex = 7;
      this.RbESP.Text = "ESP";
      this.RbESP.UseVisualStyleBackColor = true;
      this.RbPOL.AutoSize = true;
      this.RbPOL.Location = new Point(204, 20);
      this.RbPOL.Name = "RbPOL";
      this.RbPOL.Size = new Size(46, 17);
      this.RbPOL.TabIndex = 6;
      this.RbPOL.Text = "POL";
      this.RbPOL.UseVisualStyleBackColor = true;
      this.RbTHA.AutoSize = true;
      this.RbTHA.Location = new Point(149, 54);
      this.RbTHA.Name = "RbTHA";
      this.RbTHA.Size = new Size(47, 17);
      this.RbTHA.TabIndex = 5;
      this.RbTHA.Text = "THA";
      this.RbTHA.UseVisualStyleBackColor = true;
      this.RbRUS.AutoSize = true;
      this.RbRUS.Location = new Point(149, 20);
      this.RbRUS.Name = "RbRUS";
      this.RbRUS.Size = new Size(48, 17);
      this.RbRUS.TabIndex = 4;
      this.RbRUS.Text = "RUS";
      this.RbRUS.UseVisualStyleBackColor = true;
      this.RbITA.AutoSize = true;
      this.RbITA.Location = new Point(84, 54);
      this.RbITA.Name = "RbITA";
      this.RbITA.Size = new Size(42, 17);
      this.RbITA.TabIndex = 3;
      this.RbITA.Text = "ITA";
      this.RbITA.UseVisualStyleBackColor = true;
      this.RbFRA.AutoSize = true;
      this.RbFRA.Location = new Point(84, 20);
      this.RbFRA.Name = "RbFRA";
      this.RbFRA.Size = new Size(46, 17);
      this.RbFRA.TabIndex = 2;
      this.RbFRA.Text = "FRA";
      this.RbFRA.UseVisualStyleBackColor = true;
      this.RbGER.AutoSize = true;
      this.RbGER.Location = new Point(20, 54);
      this.RbGER.Name = "RbGER";
      this.RbGER.Size = new Size(48, 17);
      this.RbGER.TabIndex = 1;
      this.RbGER.Text = "GER";
      this.RbGER.UseVisualStyleBackColor = true;
      this.RbUSA.AutoSize = true;
      this.RbUSA.Location = new Point(20, 20);
      this.RbUSA.Name = "RbUSA";
      this.RbUSA.Size = new Size(47, 17);
      this.RbUSA.TabIndex = 0;
      this.RbUSA.Text = "USA";
      this.RbUSA.UseVisualStyleBackColor = true;
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(377, 101);
      this.Controls.Add((Control) this.GbLangSelect);
      this.Icon = (Icon) componentResourceManager.GetObject("$this.Icon");
      this.Name = nameof (LangSelect);
      this.Text = nameof (LangSelect);
      this.Load += new EventHandler(this.LangSelect_Load);
      this.GbLangSelect.ResumeLayout(false);
      this.GbLangSelect.PerformLayout();
      this.ResumeLayout(false);
    }
  }
}
