// Decompiled with JetBrains decompiler
// Type: LodExporter.LodExporter
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using LcDevPack_TeamDamonA;
using System;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.Windows.Forms;

#nullable disable
namespace LodExporter
{
  public class LodExporter : Form
  {
    private string[] mysql;
    private IContainer components;
    private TextBox m_ip;
    private TextBox m_db;
    private TextBox m_user;
    private TextBox m_pw;
    private GroupBox groupBox2;
    private RadioButton version2;
    private RadioButton version1;
    private GroupBox groupbox3;
    private RadioButton kor;
    private RadioButton usa;
    private RadioButton ger;
    private GroupBox groupBox4;
    private CheckedListBox lodfiles;
    private Button run;
    public static Connection connection = new Connection();
        private string Host = connection.Settings.SqlHost;
        private string User = connection.Settings.SqlUser;
        private string Password = connection.Settings.SqlPassword;
        private string Databaselod = connection.Settings.SqlDatabase;

        public LodExporter()
    {
      this.InitializeComponent();
      this.m_ip.Text = this.Host;
      this.m_db.Text = this.Databaselod;
      this.m_user.Text = this.User;
      this.m_pw.Text = this.Password;
      this.version1.Checked = true;
      this.usa.Checked = true;
      this.lodfiles.Items.Add((object) "Items");
      this.lodfiles.Items.Add((object) "Itemai");
      this.lodfiles.Items.Add((object) "Itemname");
      this.lodfiles.Items.Add((object) "Skill");
      this.lodfiles.Items.Add((object) "SpecialSkill");
      this.lodfiles.Items.Add((object) "Action");
      this.lodfiles.Items.Add((object) "NPC");
      this.lodfiles.Items.Add((object) "NPCName");
      this.lodfiles.Items.Add((object) "Affinity");
      this.lodfiles.Items.Add((object) "Option");
      this.lodfiles.Items.Add((object) "Quest");
      this.lodfiles.Items.Add((object) "Title");
      this.lodfiles.Items.Add((object) "Rareoption");
      this.lodfiles.Items.Add((object) "aPet");
      this.lodfiles.Items.Add((object) "Map");
      this.lodfiles.Items.Add((object) "Help NPC");
      this.lodfiles.Items.Add((object) "Combo");
      this.lodfiles.Items.Add((object) "Lacarette");
      this.lodfiles.Items.Add((object) "Shop");
      this.lodfiles.Items.Add((object) "itemCollection");
    }

    private void run_Click(object sender, EventArgs e)
    {
      for (int index = 0; index < this.lodfiles.Items.Count; ++index)
      {
        if (this.lodfiles.GetItemChecked(index))
        {
          string s = this.lodfiles.Items[index].ToString();
          string str1;
                    // ISSUE: reference to a compiler-generated method
                    switch (s)
                    {
                        case "Help NPC":
                            str1 = "helpnpc";
                            break;
                        case "Affinity":
                            str1 = "affinity";
                            break;
                        case "Action":
                            str1 = "action";
                            break;
                        case "NPCName":
                            str1 = "npcname";
                            break;
                        case "Option":
                            str1 = "option";
                            break;
                        case "itemCollection":
                            str1 = "itemCollection";
                            break;
                        case "Title":
                            str1 = "title";
                            break;
                        case "Shop":
                            str1 = "shop";
                            break;
                        case "Itemai":
                            str1 = "itemai";
                            break;
                        case "Map":
                            str1 = "map";
                            break;
                        case "Rareoption":
                            str1 = "rareoption";
                            break;
                        case "aPet":
                            str1 = "apet";
                            break;
                        case "NPC":
                            str1 = "npc";
                            break;
                        case "Skill":
                            str1 = "skill";
                            break;
                        case "Lacarette":
                            str1 = "lacarette";
                            break;
                        case "Combo":
                            str1 = "combo";
                            break;
                        case "Quest":
                            str1 = "quest";
                            break;
                        case "SpecialSkill":
                            str1 = "sskill";
                            break;
                        case "Items":
                            str1 = "item";
                            break;
                        case "Itemname":
                            str1 = "itemname";
                            break;
                        default:
                            return;
                    }

                    string str2 = !this.version1.Checked ? "path_pre" : "path_ship";
          string str3 = this.ger.Checked ? "ger" : (this.usa.Checked ? "usa" : (!this.kor.Checked ? "usa" : "kor"));
          Process.Start(new ProcessStartInfo()
          {
            FileName = "ExportLod.exe",
            Arguments = " -h " + this.m_ip.Text + " -d " + this.m_db.Text + " -u " + this.m_user.Text + " -p " + this.m_pw.Text + " -k " + str2 + " -l " + str3 + " -t " + str1
          });
        }
      }
    }

    private void lodfiles_SelectedIndexChanged(object sender, EventArgs e)
    {
    }

    private void ger_CheckedChanged(object sender, EventArgs e)
    {
    }

    private void Form1_Load(object sender, EventArgs e)
    {
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
            ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof(LodExporter));
            this.m_ip = new TextBox();
      this.m_db = new TextBox();
      this.m_user = new TextBox();
      this.m_pw = new TextBox();
      this.groupBox2 = new GroupBox();
      this.version2 = new RadioButton();
      this.version1 = new RadioButton();
      this.groupbox3 = new GroupBox();
      this.kor = new RadioButton();
      this.usa = new RadioButton();
      this.ger = new RadioButton();
      this.groupBox4 = new GroupBox();
      this.lodfiles = new CheckedListBox();
      this.run = new Button();
      this.groupBox2.SuspendLayout();
      this.groupbox3.SuspendLayout();
      this.groupBox4.SuspendLayout();
      this.SuspendLayout();
      this.m_ip.Location = new Point(27, 261);
      this.m_ip.Name = "m_ip";
      this.m_ip.Size = new Size(38, 20);
      this.m_ip.TabIndex = 4;
      this.m_ip.Visible = false;
      this.m_db.Location = new Point(81, 261);
      this.m_db.Name = "m_db";
      this.m_db.Size = new Size(39, 20);
      this.m_db.TabIndex = 5;
      this.m_db.Visible = false;
      this.m_user.Location = new Point(126, 261);
      this.m_user.Name = "m_user";
      this.m_user.Size = new Size(40, 20);
      this.m_user.TabIndex = 6;
      this.m_user.Visible = false;
      this.m_pw.Location = new Point(181, 261);
      this.m_pw.Name = "m_pw";
      this.m_pw.Size = new Size(41, 20);
      this.m_pw.TabIndex = 7;
      this.m_pw.Visible = false;
      this.groupBox2.Controls.Add((Control) this.version2);
      this.groupBox2.Controls.Add((Control) this.version1);
      this.groupBox2.Location = new Point(12, 9);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new Size(228, 53);
      this.groupBox2.TabIndex = 9;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "VERSION";
      this.version2.AutoSize = true;
      this.version2.Location = new Point(137, 24);
      this.version2.Name = "version2";
      this.version2.Size = new Size(79, 17);
      this.version2.TabIndex = 1;
      this.version2.TabStop = true;
      this.version2.Text = "Pre Version";
      this.version2.UseVisualStyleBackColor = true;
      this.version1.AutoSize = true;
      this.version1.Location = new Point(9, 24);
      this.version1.Name = "version1";
      this.version1.Size = new Size(84, 17);
      this.version1.TabIndex = 0;
      this.version1.TabStop = true;
      this.version1.Text = "Ship Version";
      this.version1.UseVisualStyleBackColor = true;
      this.groupbox3.Controls.Add((Control) this.kor);
      this.groupbox3.Controls.Add((Control) this.usa);
      this.groupbox3.Controls.Add((Control) this.ger);
      this.groupbox3.Location = new Point(12, 72);
      this.groupbox3.Name = "groupbox3";
      this.groupbox3.Size = new Size(228, 58);
      this.groupbox3.TabIndex = 10;
      this.groupbox3.TabStop = false;
      this.groupbox3.Text = "LANGUAGE";
      this.kor.AutoSize = true;
      this.kor.Location = new Point(154, 27);
      this.kor.Name = "kor";
      this.kor.Size = new Size(62, 17);
      this.kor.TabIndex = 13;
      this.kor.TabStop = true;
      this.kor.Text = "KOREA";
      this.kor.UseVisualStyleBackColor = true;
      this.usa.AutoSize = true;
      this.usa.Location = new Point(86, 27);
      this.usa.Name = "usa";
      this.usa.Size = new Size(47, 17);
      this.usa.TabIndex = 12;
      this.usa.TabStop = true;
      this.usa.Text = "USA";
      this.usa.UseVisualStyleBackColor = true;
      this.ger.AutoSize = true;
      this.ger.Location = new Point(16, 27);
      this.ger.Name = "ger";
      this.ger.Size = new Size(48, 17);
      this.ger.TabIndex = 11;
      this.ger.TabStop = true;
      this.ger.Text = "GER";
      this.ger.UseVisualStyleBackColor = true;
      this.ger.CheckedChanged += new EventHandler(this.ger_CheckedChanged);
      this.groupBox4.Controls.Add((Control) this.lodfiles);
      this.groupBox4.Location = new Point(246, 9);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Size = new Size(298, 329);
      this.groupBox4.TabIndex = 11;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "LOD FILE";
      this.lodfiles.BackColor = SystemColors.Control;
      this.lodfiles.BorderStyle = BorderStyle.None;
      this.lodfiles.FormattingEnabled = true;
      this.lodfiles.Location = new Point(6, 20);
      this.lodfiles.Name = "lodfiles";
      this.lodfiles.Size = new Size(286, 300);
      this.lodfiles.TabIndex = 0;
      this.lodfiles.SelectedIndexChanged += new EventHandler(this.lodfiles_SelectedIndexChanged);
      this.run.Location = new Point(46, 164);
      this.run.Name = "run";
      this.run.Size = new Size(157, 38);
      this.run.TabIndex = 12;
      this.run.Text = "Export File";
      this.run.UseVisualStyleBackColor = true;
      this.run.Click += new EventHandler(this.run_Click);
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(556, 344);
      this.Controls.Add((Control) this.m_pw);
      this.Controls.Add((Control) this.m_ip);
      this.Controls.Add((Control) this.m_user);
      this.Controls.Add((Control) this.run);
      this.Controls.Add((Control) this.m_db);
      this.Controls.Add((Control) this.groupBox4);
      this.Controls.Add((Control) this.groupbox3);
      this.Controls.Add((Control) this.groupBox2);
      this.Icon = (Icon) componentResourceManager.GetObject("$this.Icon");
      this.Name = nameof (LodExporter);
      this.Text = "Lod Exporter";
      this.Load += new EventHandler(this.Form1_Load);
      this.groupBox2.ResumeLayout(false);
      this.groupBox2.PerformLayout();
      this.groupbox3.ResumeLayout(false);
      this.groupbox3.PerformLayout();
      this.groupBox4.ResumeLayout(false);
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
