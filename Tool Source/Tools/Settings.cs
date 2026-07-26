// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.Settings
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using LcDevPack_TeamDamonA.Properties;
using System;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools
{
  public class Settings : Form
  {
    public string FolderPath = "";
    public string buffer = "\\";
    public static Connection connection = new Connection();
    private string language = Settings.connection.Settings.Language;
    private string Host = Settings.connection.Settings.SqlHost;
    private string User = Settings.connection.Settings.SqlUser;
    private string Password = Settings.connection.Settings.SqlPassword;
    private string Database = Settings.connection.Settings.SqlDatabase;
    private string DB_Database = Settings.connection.Settings.SqlDbDatabase;
    private string DB_Auth = Settings.connection.Settings.SqlDbAuth;
    private string ClientPath = Settings.connection.Settings.ClientPath;
    private IContainer components = (IContainer) null;
    private Button btnSave;
    private TextBox TbClientPath;
    private TextBox TbSqlHost;
    private TextBox TbSqlUser;
    private TextBox TbSqlPassword;
    private TextBox TbSqlDatabase;
    private Label label1;
    private Label label2;
    private Label label3;
    private Label label4;
    private Label label5;
    private Label label6;
    private ComboBox CbLangSelect;
    private PictureBox pictureBox1;
    private CheckBox CBPass;
    private CheckBox CBUser;
    private CheckBox CBHost;
    private CheckBox CBClientPath;
    private CheckBox checkBox1;
    private CheckBox CbDb;
    private Label label7;
    private TextBox TbSqlDb;
    private CheckBox CbAth;
    private Label label8;
    private TextBox TbSqlAuth;

    public Settings() => this.InitializeComponent();

    private void textBox6_TextChanged(object sender, EventArgs e)
    {
    }

    private void textBox5_TextChanged(object sender, EventArgs e)
    {
    }

    private void textBox4_TextChanged(object sender, EventArgs e)
    {
    }

    private void textBox3_TextChanged(object sender, EventArgs e)
    {
    }

    private void textBox2_TextChanged(object sender, EventArgs e)
    {
    }

    private void textBox1_TextChanged(object sender, EventArgs e)
    {
    }

    private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
    }

    private void pictureBox1_Click(object sender, EventArgs e)
    {
      FolderBrowserDialog folderBrowserDialog = new FolderBrowserDialog();
      if (folderBrowserDialog.ShowDialog() == DialogResult.OK)
        this.FolderPath = folderBrowserDialog.SelectedPath.ToString();
      this.TbClientPath.Text = this.FolderPath + this.buffer;
    }

    private void CBClientPath_CheckedChanged(object sender, EventArgs e)
    {
      if (this.CBClientPath.Checked)
      {
        this.TbClientPath.PasswordChar = '●';
      }
      else
      {
        if (this.CBClientPath.Checked)
          return;
        this.TbClientPath.PasswordChar = char.MinValue;
      }
    }

    private void CBHost_CheckedChanged(object sender, EventArgs e)
    {
      if (this.CBHost.Checked)
      {
        this.TbSqlHost.PasswordChar = '●';
      }
      else
      {
        if (this.CBHost.Checked)
          return;
        this.TbSqlHost.PasswordChar = char.MinValue;
      }
    }

    private void CBUser_CheckedChanged(object sender, EventArgs e)
    {
      if (this.CBUser.Checked)
      {
        this.TbSqlUser.PasswordChar = '●';
      }
      else
      {
        if (this.CBUser.Checked)
          return;
        this.TbSqlUser.PasswordChar = char.MinValue;
      }
    }

    private void CBPass_CheckedChanged(object sender, EventArgs e)
    {
      if (this.CBPass.Checked)
      {
        this.TbSqlPassword.PasswordChar = '●';
      }
      else
      {
        if (this.CBPass.Checked)
          return;
        this.TbSqlPassword.PasswordChar = char.MinValue;
      }
    }

    private void checkBox1_CheckedChanged(object sender, EventArgs e)
    {
      if (this.checkBox1.Checked)
      {
        this.TbSqlDatabase.PasswordChar = '●';
      }
      else
      {
        if (this.checkBox1.Checked)
          return;
        this.TbSqlDatabase.PasswordChar = char.MinValue;
      }
    }

    private void Settings_Load(object sender, EventArgs e)
    {
      this.ComboBoxLoad();
      this.TbClientPath.Text = this.ClientPath;
      this.TbSqlDatabase.Text = this.Database;
      this.TbSqlHost.Text = this.Host;
      this.TbSqlPassword.Text = this.Password;
      this.TbSqlUser.Text = this.User;
      this.TbSqlDb.Text = this.DB_Database;
      this.TbSqlAuth.Text = this.DB_Auth;
      if (this.language == "GER")
        this.CbLangSelect.SelectedIndex = 0;
      else if (this.language == "POL")
        this.CbLangSelect.SelectedIndex = 1;
      else if (this.language == "BRA")
        this.CbLangSelect.SelectedIndex = 2;
      else if (this.language == "RUS")
        this.CbLangSelect.SelectedIndex = 3;
      else if (this.language == "FRA")
        this.CbLangSelect.SelectedIndex = 4;
      else if (this.language == "ESP")
        this.CbLangSelect.SelectedIndex = 5;
      else if (this.language == "MEX")
        this.CbLangSelect.SelectedIndex = 6;
      else if (this.language == "THA")
        this.CbLangSelect.SelectedIndex = 7;
      else if (this.language == "ITA")
      {
        this.CbLangSelect.SelectedIndex = 8;
      }
      else
      {
        if (!(this.language == "USA"))
          return;
        this.CbLangSelect.SelectedIndex = 9;
      }
    }

    private void ComboBoxLoad()
    {
      this.CbLangSelect.Items.AddRange(new object[10]
      {
        (object) "1 - GER",
        (object) "2 - POL",
        (object) "3 - BRA",
        (object) "4 - RUS",
        (object) "5 - FRA",
        (object) "6 - ESP",
        (object) "7 - MEX",
        (object) "8 - THA",
        (object) "9 - ITA",
        (object) "10 - USA"
      });
    }

    public int GetIndexByComboBox(string comboBox)
    {
      try
      {
        return Convert.ToInt32(comboBox.Split(' ')[0]);
      }
      catch
      {
        return 0;
      }
    }

    private void btnSave_Click(object sender, EventArgs e)
    {
      try
      {
        TextWriter textWriter = (TextWriter) new StreamWriter("Config//Settings.cfg");
        textWriter.WriteLine("## MYSQL");
        textWriter.WriteLine("Episode=EP4");
        textWriter.WriteLine("ClientPath=" + this.TbClientPath.Text);
        textWriter.WriteLine("[## MYSQL]");
        textWriter.WriteLine("SQL_HOST=" + this.TbSqlHost.Text);
        textWriter.WriteLine("SQL_USER=" + this.TbSqlUser.Text);
        textWriter.WriteLine("SQL_PASSWORD=" + this.TbSqlPassword.Text);
        textWriter.WriteLine("SQL_DATABASE=" + this.TbSqlDatabase.Text);
        textWriter.WriteLine("SQL_DB_DATABASE=" + this.TbSqlDb.Text);
        textWriter.WriteLine("SQL_DB_AUTH=" + this.TbSqlAuth.Text);
        textWriter.WriteLine("SQL_DB_DATALOD=" + this.TbSqlDatabase.Text);
        if (this.CbLangSelect.SelectedIndex == 0)
          textWriter.WriteLine("Language=GER");
        else if (this.CbLangSelect.SelectedIndex == 1)
          textWriter.WriteLine("Language=POL");
        else if (this.CbLangSelect.SelectedIndex == 2)
          textWriter.WriteLine("Language=BRA");
        else if (this.CbLangSelect.SelectedIndex == 3)
          textWriter.WriteLine("Language=RUS");
        else if (this.CbLangSelect.SelectedIndex == 4)
          textWriter.WriteLine("Language=FRA");
        else if (this.CbLangSelect.SelectedIndex == 5)
          textWriter.WriteLine("Language=ESP");
        else if (this.CbLangSelect.SelectedIndex == 6)
          textWriter.WriteLine("Language=MEX");
        else if (this.CbLangSelect.SelectedIndex == 7)
          textWriter.WriteLine("Language=THA");
        else if (this.CbLangSelect.SelectedIndex == 8)
          textWriter.WriteLine("Language=ITA");
        else if (this.CbLangSelect.SelectedIndex == 9)
          textWriter.WriteLine("Language=USA");
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
        textWriter.WriteLine("[path_pre]");
        textWriter.WriteLine("usa=" + this.TbClientPath.Text + "Data\\");
        textWriter.WriteLine("[path_ship]");
        textWriter.WriteLine("usa=" + this.TbClientPath.Text + "Data\\");
        textWriter.WriteLine("[Str_Path_Ship]");
        if (this.CbLangSelect.SelectedIndex == 0)
          textWriter.WriteLine("GER=" + this.TbClientPath.Text + "Local\\de\\String\\");
        else if (this.CbLangSelect.SelectedIndex == 1)
          textWriter.WriteLine("POL=" + this.TbClientPath.Text + "Local\\pl\\String\\");
        else if (this.CbLangSelect.SelectedIndex == 2)
          textWriter.WriteLine("BRA=" + this.TbClientPath.Text + "Local\\br\\String\\");
        else if (this.CbLangSelect.SelectedIndex == 3)
          textWriter.WriteLine("RUS=" + this.TbClientPath.Text + "Local\\ru\\String\\");
        else if (this.CbLangSelect.SelectedIndex == 4)
          textWriter.WriteLine("FRA=" + this.TbClientPath.Text + "Local\\fr\\String\\");
        else if (this.CbLangSelect.SelectedIndex == 5)
          textWriter.WriteLine("ESP=" + this.TbClientPath.Text + "Local\\es\\String\\");
        else if (this.CbLangSelect.SelectedIndex == 6)
          textWriter.WriteLine("MEX=" + this.TbClientPath.Text + "Local\\mx\\String\\");
        else if (this.CbLangSelect.SelectedIndex == 7)
          textWriter.WriteLine("THA=" + this.TbClientPath.Text + "Local\\th\\String\\");
        else if (this.CbLangSelect.SelectedIndex == 8)
          textWriter.WriteLine("ITA=" + this.TbClientPath.Text + "Local\\it\\String\\");
        else if (this.CbLangSelect.SelectedIndex == 9)
          textWriter.WriteLine("USA=" + this.TbClientPath.Text + "Local\\us\\String\\");
        textWriter.WriteLine("[Str_Path_Pre]");
        if (this.CbLangSelect.SelectedIndex == 0)
          textWriter.WriteLine("GER=" + this.TbClientPath.Text + "Local\\de\\String\\");
        else if (this.CbLangSelect.SelectedIndex == 1)
          textWriter.WriteLine("POL=" + this.TbClientPath.Text + "Local\\pl\\String\\");
        else if (this.CbLangSelect.SelectedIndex == 2)
          textWriter.WriteLine("BRA=" + this.TbClientPath.Text + "Local\\br\\String\\");
        else if (this.CbLangSelect.SelectedIndex == 3)
          textWriter.WriteLine("RUS=" + this.TbClientPath.Text + "Local\\ru\\String\\");
        else if (this.CbLangSelect.SelectedIndex == 4)
          textWriter.WriteLine("FRA=" + this.TbClientPath.Text + "Local\\fr\\String\\");
        else if (this.CbLangSelect.SelectedIndex == 5)
          textWriter.WriteLine("ESP=" + this.TbClientPath.Text + "Local\\es\\String\\");
        else if (this.CbLangSelect.SelectedIndex == 6)
          textWriter.WriteLine("MEX=" + this.TbClientPath.Text + "Local\\mx\\String\\");
        else if (this.CbLangSelect.SelectedIndex == 7)
          textWriter.WriteLine("THA=" + this.TbClientPath.Text + "Local\\th\\String\\");
        else if (this.CbLangSelect.SelectedIndex == 8)
          textWriter.WriteLine("ITA=" + this.TbClientPath.Text + "Local\\it\\String\\");
        else if (this.CbLangSelect.SelectedIndex == 9)
          textWriter.WriteLine("USA=" + this.TbClientPath.Text + "Local\\us\\String\\");
        textWriter.Close();
        int num = (int) new CustomMessage("Saved!").ShowDialog();
        Application.Restart();
      }
      catch
      {
        int num = (int) new CustomMessage("failed :(").ShowDialog();
      }
    }

    private void CbDb_CheckedChanged(object sender, EventArgs e)
    {
      if (this.CbDb.Checked)
      {
        this.TbSqlDb.PasswordChar = '●';
      }
      else
      {
        if (this.CbDb.Checked)
          return;
        this.TbSqlDb.PasswordChar = char.MinValue;
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
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (Settings));
      this.btnSave = new Button();
      this.TbClientPath = new TextBox();
      this.TbSqlHost = new TextBox();
      this.TbSqlUser = new TextBox();
      this.TbSqlPassword = new TextBox();
      this.TbSqlDatabase = new TextBox();
      this.label1 = new Label();
      this.label2 = new Label();
      this.label3 = new Label();
      this.label4 = new Label();
      this.label5 = new Label();
      this.label6 = new Label();
      this.CbLangSelect = new ComboBox();
      this.pictureBox1 = new PictureBox();
      this.CBPass = new CheckBox();
      this.CBUser = new CheckBox();
      this.CBHost = new CheckBox();
      this.CBClientPath = new CheckBox();
      this.checkBox1 = new CheckBox();
      this.CbDb = new CheckBox();
      this.label7 = new Label();
      this.TbSqlDb = new TextBox();
      this.CbAth = new CheckBox();
      this.label8 = new Label();
      this.TbSqlAuth = new TextBox();
      ((ISupportInitialize) this.pictureBox1).BeginInit();
      this.SuspendLayout();
      this.btnSave.BackgroundImageLayout = ImageLayout.None;
      this.btnSave.FlatStyle = FlatStyle.Popup;
      this.btnSave.Location = new Point(137, 384);
      this.btnSave.Name = "btnSave";
      this.btnSave.Size = new Size(210, 33);
      this.btnSave.TabIndex = 0;
      this.btnSave.Text = "SAVE SETTINGS";
      this.btnSave.UseVisualStyleBackColor = true;
      this.btnSave.Click += new EventHandler(this.btnSave_Click);
      this.TbClientPath.BorderStyle = BorderStyle.FixedSingle;
      this.TbClientPath.Location = new Point(137, 15);
      this.TbClientPath.Name = "TbClientPath";
      this.TbClientPath.Size = new Size(271, 20);
      this.TbClientPath.TabIndex = 1;
      this.TbClientPath.TextChanged += new EventHandler(this.textBox1_TextChanged);
      this.TbSqlHost.BorderStyle = BorderStyle.FixedSingle;
      this.TbSqlHost.Location = new Point(137, 60);
      this.TbSqlHost.Name = "TbSqlHost";
      this.TbSqlHost.Size = new Size(271, 20);
      this.TbSqlHost.TabIndex = 2;
      this.TbSqlHost.TextChanged += new EventHandler(this.textBox2_TextChanged);
      this.TbSqlUser.BorderStyle = BorderStyle.FixedSingle;
      this.TbSqlUser.Location = new Point(137, 106);
      this.TbSqlUser.Name = "TbSqlUser";
      this.TbSqlUser.Size = new Size(271, 20);
      this.TbSqlUser.TabIndex = 3;
      this.TbSqlUser.TextChanged += new EventHandler(this.textBox3_TextChanged);
      this.TbSqlPassword.BorderStyle = BorderStyle.FixedSingle;
      this.TbSqlPassword.Location = new Point(137, 159);
      this.TbSqlPassword.Name = "TbSqlPassword";
      this.TbSqlPassword.Size = new Size(271, 20);
      this.TbSqlPassword.TabIndex = 4;
      this.TbSqlPassword.TextChanged += new EventHandler(this.textBox4_TextChanged);
      this.TbSqlDatabase.BorderStyle = BorderStyle.FixedSingle;
      this.TbSqlDatabase.Location = new Point(137, 211);
      this.TbSqlDatabase.Name = "TbSqlDatabase";
      this.TbSqlDatabase.Size = new Size(271, 20);
      this.TbSqlDatabase.TabIndex = 5;
      this.TbSqlDatabase.TextChanged += new EventHandler(this.textBox5_TextChanged);
      this.label1.AutoSize = true;
      this.label1.Location = new Point(11, 18);
      this.label1.Name = "label1";
      this.label1.Size = new Size(80, 13);
      this.label1.TabIndex = 7;
      this.label1.Text = "CLIENT PATH:";
      this.label2.AutoSize = true;
      this.label2.Location = new Point(9, 63);
      this.label2.Name = "label2";
      this.label2.Size = new Size(67, 13);
      this.label2.TabIndex = 8;
      this.label2.Text = "SQL_HOST:";
      this.label3.AutoSize = true;
      this.label3.Location = new Point(6, 109);
      this.label3.Name = "label3";
      this.label3.Size = new Size(67, 13);
      this.label3.TabIndex = 9;
      this.label3.Text = "SQL_USER:";
      this.label4.AutoSize = true;
      this.label4.Location = new Point(1, 163);
      this.label4.Name = "label4";
      this.label4.Size = new Size(100, 13);
      this.label4.TabIndex = 10;
      this.label4.Text = "SQL_PASSWORD:";
      this.label5.AutoSize = true;
      this.label5.Location = new Point(1, 216);
      this.label5.Name = "label5";
      this.label5.Size = new Size(129, 13);
      this.label5.TabIndex = 11;
      this.label5.Text = "SQL_DATABASE_DATA:";
      this.label6.AutoSize = true;
      this.label6.Location = new Point(10, 362);
      this.label6.Name = "label6";
      this.label6.Size = new Size(69, 13);
      this.label6.TabIndex = 12;
      this.label6.Text = "LANGUAGE:";
      this.CbLangSelect.FlatStyle = FlatStyle.Popup;
      this.CbLangSelect.FormattingEnabled = true;
      this.CbLangSelect.Location = new Point(137, 357);
      this.CbLangSelect.Name = "CbLangSelect";
      this.CbLangSelect.Size = new Size(271, 21);
      this.CbLangSelect.TabIndex = 13;
      this.CbLangSelect.SelectedIndexChanged += new EventHandler(this.comboBox1_SelectedIndexChanged);
      this.pictureBox1.BackgroundImage = (Image) Resources.oie_transparent;
      this.pictureBox1.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox1.Location = new Point(414, 15);
      this.pictureBox1.Name = "pictureBox1";
      this.pictureBox1.Size = new Size(31, 31);
      this.pictureBox1.TabIndex = 14;
      this.pictureBox1.TabStop = false;
      this.pictureBox1.Click += new EventHandler(this.pictureBox1_Click);
      this.CBPass.AutoSize = true;
      this.CBPass.Font = new Font("Microsoft Sans Serif", 9.75f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.CBPass.Location = new Point(137, 185);
      this.CBPass.Name = "CBPass";
      this.CBPass.Size = new Size(147, 20);
      this.CBPass.TabIndex = 15;
      this.CBPass.Text = "Password is Hidden";
      this.CBPass.UseVisualStyleBackColor = true;
      this.CBPass.CheckedChanged += new EventHandler(this.CBPass_CheckedChanged);
      this.CBUser.AutoSize = true;
      this.CBUser.Font = new Font("Microsoft Sans Serif", 9.75f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.CBUser.Location = new Point(137, 132);
      this.CBUser.Name = "CBUser";
      this.CBUser.Size = new Size(116, 20);
      this.CBUser.TabIndex = 16;
      this.CBUser.Text = "User is Hidden";
      this.CBUser.UseVisualStyleBackColor = true;
      this.CBUser.CheckedChanged += new EventHandler(this.CBUser_CheckedChanged);
      this.CBHost.AutoSize = true;
      this.CBHost.Font = new Font("Microsoft Sans Serif", 9.75f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.CBHost.Location = new Point(137, 80);
      this.CBHost.Name = "CBHost";
      this.CBHost.Size = new Size(115, 20);
      this.CBHost.TabIndex = 17;
      this.CBHost.Text = "Host is Hidden";
      this.CBHost.UseVisualStyleBackColor = true;
      this.CBHost.CheckedChanged += new EventHandler(this.CBHost_CheckedChanged);
      this.CBClientPath.AutoSize = true;
      this.CBClientPath.Font = new Font("Microsoft Sans Serif", 9.75f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.CBClientPath.Location = new Point(139, 37);
      this.CBClientPath.Name = "CBClientPath";
      this.CBClientPath.Size = new Size(147, 20);
      this.CBClientPath.TabIndex = 18;
      this.CBClientPath.Text = "ClientPath is Hidden";
      this.CBClientPath.UseVisualStyleBackColor = true;
      this.CBClientPath.CheckedChanged += new EventHandler(this.CBClientPath_CheckedChanged);
      this.checkBox1.AutoSize = true;
      this.checkBox1.Font = new Font("Microsoft Sans Serif", 9.75f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.checkBox1.Location = new Point(137, 231);
      this.checkBox1.Name = "checkBox1";
      this.checkBox1.Size = new Size(147, 20);
      this.checkBox1.TabIndex = 19;
      this.checkBox1.Text = "Database is Hidden";
      this.checkBox1.UseVisualStyleBackColor = true;
      this.checkBox1.CheckedChanged += new EventHandler(this.checkBox1_CheckedChanged);
      this.CbDb.AutoSize = true;
      this.CbDb.Font = new Font("Microsoft Sans Serif", 9.75f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.CbDb.Location = new Point(137, 279);
      this.CbDb.Name = "CbDb";
      this.CbDb.Size = new Size(147, 20);
      this.CbDb.TabIndex = 22;
      this.CbDb.Text = "Database is Hidden";
      this.CbDb.UseVisualStyleBackColor = true;
      this.CbDb.CheckedChanged += new EventHandler(this.CbDb_CheckedChanged);
      this.label7.AutoSize = true;
      this.label7.Location = new Point(1, 264);
      this.label7.Name = "label7";
      this.label7.Size = new Size(115, 13);
      this.label7.TabIndex = 21;
      this.label7.Text = "SQL_DB_DATABASE:";
      this.TbSqlDb.BorderStyle = BorderStyle.FixedSingle;
      this.TbSqlDb.Location = new Point(137, 259);
      this.TbSqlDb.Name = "TbSqlDb";
      this.TbSqlDb.Size = new Size(271, 20);
      this.TbSqlDb.TabIndex = 20;
      this.CbAth.AutoSize = true;
      this.CbAth.Font = new Font("Microsoft Sans Serif", 9.75f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.CbAth.Location = new Point(137, 327);
      this.CbAth.Name = "CbAth";
      this.CbAth.Size = new Size(147, 20);
      this.CbAth.TabIndex = 25;
      this.CbAth.Text = "Database is Hidden";
      this.CbAth.UseVisualStyleBackColor = true;
      this.label8.AutoSize = true;
      this.label8.Location = new Point(1, 312);
      this.label8.Name = "label8";
      this.label8.Size = new Size(88, 13);
      this.label8.TabIndex = 24;
      this.label8.Text = "SQL_DB_AUTH:";
      this.TbSqlAuth.BorderStyle = BorderStyle.FixedSingle;
      this.TbSqlAuth.Location = new Point(137, 307);
      this.TbSqlAuth.Name = "TbSqlAuth";
      this.TbSqlAuth.Size = new Size(271, 20);
      this.TbSqlAuth.TabIndex = 23;
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(456, 424);
      this.Controls.Add((Control) this.CbAth);
      this.Controls.Add((Control) this.label8);
      this.Controls.Add((Control) this.TbSqlAuth);
      this.Controls.Add((Control) this.CbDb);
      this.Controls.Add((Control) this.label7);
      this.Controls.Add((Control) this.TbSqlDb);
      this.Controls.Add((Control) this.checkBox1);
      this.Controls.Add((Control) this.CBClientPath);
      this.Controls.Add((Control) this.CBHost);
      this.Controls.Add((Control) this.CBUser);
      this.Controls.Add((Control) this.CBPass);
      this.Controls.Add((Control) this.pictureBox1);
      this.Controls.Add((Control) this.CbLangSelect);
      this.Controls.Add((Control) this.label6);
      this.Controls.Add((Control) this.label5);
      this.Controls.Add((Control) this.label4);
      this.Controls.Add((Control) this.label3);
      this.Controls.Add((Control) this.label2);
      this.Controls.Add((Control) this.label1);
      this.Controls.Add((Control) this.TbSqlDatabase);
      this.Controls.Add((Control) this.TbSqlPassword);
      this.Controls.Add((Control) this.TbSqlUser);
      this.Controls.Add((Control) this.TbSqlHost);
      this.Controls.Add((Control) this.TbClientPath);
      this.Controls.Add((Control) this.btnSave);
      this.Icon = (Icon) componentResourceManager.GetObject("$this.Icon");
      this.Name = nameof (Settings);
      this.Text = nameof (Settings);
      this.Load += new EventHandler(this.Settings_Load);
      ((ISupportInitialize) this.pictureBox1).EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
