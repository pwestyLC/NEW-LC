// Decompiled with JetBrains decompiler
// Type: String_Editor.ConfiMysql
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using MySqlConnector;
using System;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Windows.Forms;

#nullable disable
namespace String_Editor
{
  public class ConfiMysql : Form
  {
    private IContainer components = (IContainer) null;
    private TextBox textUser;
    private TextBox textPass;
    private TextBox textDb;
    private TextBox textIP;
    private Label label4;
    private Label label3;
    private Label label2;
    private Label label1;
    private Button btnTest;
    private Button btnExit;

    public ConfiMysql() => this.InitializeComponent();

    private void ConfiMysql_Load(object sender, EventArgs e)
    {
      StreamReader streamReader = new StreamReader("configStrTool.txt");
      this.textIP.Text = streamReader.ReadLine();
      this.textUser.Text = streamReader.ReadLine();
      this.textPass.Text = streamReader.ReadLine();
      this.textDb.Text = streamReader.ReadLine();
      streamReader.Close();
      streamReader.Dispose();
    }

    private void btnTest_Click(object sender, EventArgs e)
    {
            Form1.strProvider = "server=" + this.textIP.Text +
                          ";user=" + this.textUser.Text +
                          ";password=" + this.textPass.Text +
                          ";database=" + this.textDb.Text +
                          ";Charset=utf8mb4;SslMode=None;";

            MySqlConnection mySqlConnection = new MySqlConnection(Form1.strProvider);
      try
      {
        mySqlConnection.Open();
        mySqlConnection.Close();
        int num = (int) MessageBox.Show("Success Connection", "Success", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show("Fail connection", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
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
      this.textUser = new TextBox();
      this.textPass = new TextBox();
      this.textDb = new TextBox();
      this.textIP = new TextBox();
      this.label4 = new Label();
      this.label3 = new Label();
      this.label2 = new Label();
      this.label1 = new Label();
      this.btnTest = new Button();
      this.btnExit = new Button();
      this.SuspendLayout();
      this.textUser.Location = new Point(66, 38);
      this.textUser.Name = "textUser";
      this.textUser.Size = new Size(169, 20);
      this.textUser.TabIndex = 13;
      this.textPass.Location = new Point(66, 63);
      this.textPass.Name = "textPass";
      this.textPass.Size = new Size(169, 20);
      this.textPass.TabIndex = 14;
      this.textDb.Location = new Point(66, 89);
      this.textDb.Name = "textDb";
      this.textDb.Size = new Size(169, 20);
      this.textDb.TabIndex = 15;
      this.textIP.Location = new Point(66, 12);
      this.textIP.Name = "textIP";
      this.textIP.Size = new Size(169, 20);
      this.textIP.TabIndex = 8;
      this.label4.AutoSize = true;
      this.label4.Location = new Point(7, 92);
      this.label4.Name = "label4";
      this.label4.Size = new Size(53, 13);
      this.label4.TabIndex = 9;
      this.label4.Text = "Database";
      this.label3.AutoSize = true;
      this.label3.Location = new Point(30, 66);
      this.label3.Name = "label3";
      this.label3.Size = new Size(30, 13);
      this.label3.TabIndex = 10;
      this.label3.Text = "Pass";
      this.label2.AutoSize = true;
      this.label2.Location = new Point(31, 41);
      this.label2.Name = "label2";
      this.label2.Size = new Size(29, 13);
      this.label2.TabIndex = 11;
      this.label2.Text = "User";
      this.label1.AutoSize = true;
      this.label1.Location = new Point(43, 15);
      this.label1.Name = "label1";
      this.label1.Size = new Size(17, 13);
      this.label1.TabIndex = 12;
      this.label1.Text = "IP";
      this.btnTest.DialogResult = DialogResult.OK;
      this.btnTest.Location = new Point(34, 124);
      this.btnTest.Name = "btnTest";
      this.btnTest.Size = new Size(93, 23);
      this.btnTest.TabIndex = 16;
      this.btnTest.Text = "Test";
      this.btnTest.UseVisualStyleBackColor = true;
      this.btnTest.Click += new EventHandler(this.btnTest_Click);
      this.btnExit.DialogResult = DialogResult.Cancel;
      this.btnExit.Location = new Point(133, 124);
      this.btnExit.Name = "btnExit";
      this.btnExit.Size = new Size(102, 23);
      this.btnExit.TabIndex = 17;
      this.btnExit.Text = "Exit";
      this.btnExit.UseVisualStyleBackColor = true;
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(250, 156);
      this.Controls.Add((Control) this.textUser);
      this.Controls.Add((Control) this.textPass);
      this.Controls.Add((Control) this.textDb);
      this.Controls.Add((Control) this.textIP);
      this.Controls.Add((Control) this.label4);
      this.Controls.Add((Control) this.label3);
      this.Controls.Add((Control) this.label2);
      this.Controls.Add((Control) this.label1);
      this.Controls.Add((Control) this.btnTest);
      this.Controls.Add((Control) this.btnExit);
      this.FormBorderStyle = FormBorderStyle.FixedSingle;
      this.MaximizeBox = false;
      this.MinimizeBox = false;
      this.Name = nameof (ConfiMysql);
      this.StartPosition = FormStartPosition.CenterScreen;
      this.Text = nameof (ConfiMysql);
      this.Load += new EventHandler(this.ConfiMysql_Load);
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
