// Decompiled with JetBrains decompiler
// Type: StringExporter.FormExport
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using LcDevPack_TeamDamonA;
using LcDevPack_TeamDamonA.Tools.MemoryWorker;
using MySqlConnector;
using System;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Text;
using System.Windows.Forms;
using UTIL;

#nullable disable
namespace StringExporter
{
  public class FormExport : Form
  {
    private int _BitString;
    private int _BitNation;
    private mysql _sql;
    private mySQL _sql2;
    private IContainer components = (IContainer) null;
    private CheckBox _chk_all;
    private GroupBox groupBox1;
    private CheckBox _chk_affinity;
    private CheckBox _chk_combo;
    private CheckBox _chk_help1;
    private CheckBox _chk_sskill;
    private CheckBox _chk_action;
    private CheckBox _chk_skill;
    private CheckBox _chk_quest;
    private CheckBox _chk_npcname;
    private CheckBox _chk_setitem;
    private CheckBox _chk_item;
    private CheckBox _chk_string;
    private GroupBox _group_nation;
    private Button _btn_select_all;
    private CheckBox _chk_nation_tha;
    private CheckBox _chk_nation_usa;
    private CheckBox _chk_nation_rus;
    private CheckBox _chk_nation_esp;
    private CheckBox _chk_nation_pol;
    private CheckBox _chk_nation_ita;
    private CheckBox _chk_nation_fra;
    private CheckBox _chk_nation_ger;
    private CheckBox _chk_nation_gamigo_all;
    private CheckBox _chk_nation_dev;
    private Button button2;
    private Label label1;
    private ListBox _lb_output;
    private CheckBox _chk_opt_rare;
    private CheckBox _chk_option;
    private RadioButton _radio_pre;
    private RadioButton _radio_ship;
    private CheckBox _chk_nation_uk;
    private CheckBox _chk_nation_mex;
    private CheckBox _chk_nation_bra;
    private CheckBox _chk_lacarette;
    private CheckBox _chk_itemcollection;
    private readonly string[] NationPostfix = new string[12]
    {
      "",
      "_ger",
      "_frc",
      "_ita",
      "_pld",
      "_spn",
      "_brz",
      "_mex",
      "_rus",
      "_usa",
      "_thai",
      "_uk"
    };
    private readonly string[] OutputNationPost = new string[12]
    {
      "",
      "_de",
      "_fr",
      "_it",
      "_pl",
      "_es",
      "_br",
      "_mx",
      "_ru",
      "_us",
      "_th",
      "_uk"
    };
    public readonly string[] strEncoding = new string[12]
    {
      string.Empty,
      "Windows-1252",
      "Windows-1252",
      "Windows-1252",
      "Windows-1250",
      "Windows-1252",
      "Windows-1252",
      "Windows-1252",
      "Windows-1251",
      string.Empty,
      "windows-874",
      string.Empty
    };
    public static Connection connection = new Connection();
    private string Host = FormExport.connection.Settings.SqlHost;
    private string User = FormExport.connection.Settings.SqlUser;
    private string Password = FormExport.connection.Settings.SqlPassword;
    private TextBox textBox1;
    private string Database = FormExport.connection.Settings.SqlDatabase;

    public FormExport()
    {
      this.InitializeComponent();
      this._sql2 = new mySQL();
      MySqlConnection mySqlConnection = new MySqlConnection("datasource=" + this.Host + ";Port=3306;User ID="  + this.User + ";Password=" + this.Password + ";Database=" + this.Database + ";Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;");
      this.OnInitNation();
    }

        private string EncodingString(string orig, int nNation)
        {
            if (string.IsNullOrEmpty(orig))
                return string.Empty;

            try
            {
                // Determine encoding from strEncoding table or fallback
                string encName = this.strEncoding != null && nNation < this.strEncoding.Length
                    ? this.strEncoding[nNation]
                    : string.Empty;

                Encoding encoding;
                if (!string.IsNullOrEmpty(encName))
                {
                    encoding = Encoding.GetEncoding(encName,
                        EncoderFallback.ReplacementFallback,
                        DecoderFallback.ReplacementFallback);
                }
                else
                {
                    encoding = Encoding.Default;
                }

                // Normalize newlines for consistency
                orig = orig.Replace("\r\n", "\n").Replace("\r", "\n");

                // Encode/decode roundtrip only to normalize invalid sequences
                byte[] bytes = encoding.GetBytes(orig);
                string normalized = encoding.GetString(bytes);

                return normalized;
            }
            catch (Exception ex)
            {
                // If encoding lookup fails, return original safely
                Console.WriteLine($"[EncodingString] Warning: {ex.Message}");
                return orig;
            }
        }



        private bool exportData(params object[] args)
        {
            int nNation = Convert.ToInt32(args[1]);
            string tableName = args[2].ToString();
            string columnName = args[3].ToString();
            int fieldCount = Convert.ToInt32(args[4]);
            if (fieldCount == 0)
                return false;

            string[] fields = new string[fieldCount];
            for (int i = 0; i < fieldCount; i++)
                fields[i] = args[5 + i].ToString() + this.NationPostfix[nNation];

            // INI config
            string configPath = Path.Combine(Directory.GetCurrentDirectory(), "Config\\Settings.cfg");
            INI ini = new INI(configPath);
            string section = this._radio_pre.Checked ? "Str_Path_Pre" : "Str_Path_Ship";

            string outDir = ini.GetIniValue(section, ((FormExport.eNATION)nNation).ToString());
            if (string.IsNullOrEmpty(outDir))
            {
                MessageBox.Show("Missing output path in INI for nation " + ((FormExport.eNATION)nNation).ToString());
                return false;
            }

            string outFile = Path.Combine(outDir, $"{tableName}{this.OutputNationPost[nNation]}.lod");

            // Choose correct encoding for nation
            Encoding encoding;
            switch ((FormExport.eNATION)nNation)
            {
                case FormExport.eNATION.RUS:
                    encoding = Encoding.GetEncoding(1251, EncoderFallback.ExceptionFallback, DecoderFallback.ExceptionFallback);
                    break;
                case FormExport.eNATION.THA:
                    encoding = Encoding.GetEncoding(874, EncoderFallback.ExceptionFallback, DecoderFallback.ExceptionFallback);
                    break;
                case FormExport.eNATION.DEV:
                case FormExport.eNATION.USA:
                    encoding = Encoding.GetEncoding(1252, EncoderFallback.ExceptionFallback, DecoderFallback.ExceptionFallback);
                    break;
                default:
                    encoding = Encoding.GetEncoding(1250, EncoderFallback.ExceptionFallback, DecoderFallback.ExceptionFallback);
                    break;
            }

            DataTable dt = this._sql2.dt;
            if (dt == null || dt.Rows.Count == 0)
            {
                MessageBox.Show("No data to export for " + tableName);
                return false;
            }

            int maxIndex = 0;
            try
            {
                maxIndex = Convert.ToInt32(dt.Select($"{columnName} = MAX({columnName})")[0][columnName]);
            }
            catch { }

            using (var fs = new FileStream(outFile, FileMode.Create, FileAccess.Write))
            using (var bw = new BinaryWriter(fs))
            {
                bw.Write(dt.Rows.Count);
                bw.Write(maxIndex);

                foreach (DataRow row in dt.Rows)
                {
                    int indexValue = Convert.ToInt32(row[columnName]);
                    bw.Write(indexValue);

                    for (int i = 0; i < fieldCount; i++)
                    {
                        string text = row[fields[i]]?.ToString() ?? string.Empty;
                        text = text.Replace("\r\n", "\n").Replace("\r", "\n");

                        byte[] bytes;
                        try
                        {
                            bytes = encoding.GetBytes(text);
                        }
                        catch (EncoderFallbackException)
                        {
                            // fallback if invalid characters for codepage
                            bytes = Encoding.GetEncoding(1252).GetBytes(text);
                        }

                        bw.Write(bytes.Length);
                        if (bytes.Length > 0)
                            bw.Write(bytes);
                    }
                }
            }

            this._lb_output.Items.Add($"Exported {tableName}{this.OutputNationPost[nNation]} using {encoding.EncodingName}");
            this._lb_output.Refresh();
            this._lb_output.Invalidate();

            return true;
        }

        private void OnExport(object sender, EventArgs e)
    {
      this._lb_output.Items.Clear();
      this._lb_output.Items.Add((object) "Exporting !");
      this._lb_output.Refresh();
      this._lb_output.Invalidate();
      CheckBox[] checkBoxArray1 = new CheckBox[15]
      {
        this._chk_string,
        this._chk_help1,
        this._chk_item,
        this._chk_setitem,
        this._chk_option,
        this._chk_opt_rare,
        this._chk_npcname,
        this._chk_quest,
        this._chk_skill,
        this._chk_sskill,
        this._chk_action,
        this._chk_combo,
        this._chk_affinity,
        this._chk_lacarette,
        this._chk_itemcollection
      };
      CheckBox[] checkBoxArray2 = new CheckBox[12]
      {
        this._chk_nation_dev,
        this._chk_nation_ger,
        this._chk_nation_fra,
        this._chk_nation_ita,
        this._chk_nation_pol,
        this._chk_nation_esp,
        this._chk_nation_bra,
        this._chk_nation_mex,
        this._chk_nation_rus,
        this._chk_nation_usa,
        this._chk_nation_tha,
        this._chk_nation_uk
      };
      this._BitString = 0;
      this._BitNation = 0;
      for (int index = 0; index < 15; ++index)
      {
        if (checkBoxArray1[index].Checked)
          this._BitString |= 1 << index;
      }
      string str = Directory.GetCurrentDirectory() + "\\Config\\";
      INI ini = new INI(str + "Settings.cfg");
      string Section = "Str_Path_Ship";
      if (this._radio_pre.Checked)
        Section = "Str_Path_Pre";
      for (int index = 0; index < 12; ++index)
      {
        if (checkBoxArray2[index].Checked)
        {
          this._BitNation |= 1 << index;
          string Key = ((FormExport.eNATION) index).ToString();
          if (ini.GetIniValue(Section, Key) == string.Empty)
          {
            using (FolderBrowserDialog folderBrowserDialog = new FolderBrowserDialog())
            {
              folderBrowserDialog.Description = Key + " Set Data Path";
              folderBrowserDialog.ShowNewFolderButton = false;
              folderBrowserDialog.SelectedPath = str;
              if (folderBrowserDialog.ShowDialog() == DialogResult.OK)
                ini.SetIniValue(Section, ((FormExport.eNATION) index).ToString(), folderBrowserDialog.SelectedPath + "\\");
            }
          }
        }
      }
      for (int StringIdx = 0; StringIdx < 15; ++StringIdx)
      {
        if ((this._BitString & 1 << StringIdx) != 0)
        {
          this.QueryProc(StringIdx);
          for (int index = 0; index < 12; ++index)
          {
            if ((this._BitNation & 1 << index) != 0)
            {
              switch (StringIdx)
              {
                case 0:
                  this.exportData((object) StringIdx, (object) index, (object) "strClient", (object) "a_index", (object) 1, (object) "a_string");
                  break;
                case 1:
                  this.exportData((object) StringIdx, (object) index, (object) "strHelp", (object) "a_index", (object) 2, (object) "a_name", (object) "a_desc");
                  break;
                case 2:
                  this.exportData((object) StringIdx, (object) index, (object) "strItem", (object) "a_index", (object) 2, (object) "a_name", (object) "a_descr");
                  break;
                case 3:
                  this.exportData((object) StringIdx, (object) index, (object) "strSetItem", (object) "a_set_idx", (object) 1, (object) "a_set_name");
                  break;
                case 4:
                  this.exportData((object) StringIdx, (object) index, (object) "strOption", (object) "a_index", (object) 1, (object) "a_name");
                  break;
                case 5:
                  this.exportData((object) StringIdx, (object) index, (object) "strRareOption", (object) "a_index", (object) 1, (object) "a_prefix");
                  break;
                case 6:
                  this.exportData((object) StringIdx, (object) index, (object) "strNpcName", (object) "a_index", (object) 2, (object) "a_name", (object) "a_descr");
                  break;
                case 7:
                  this.exportData((object) StringIdx, (object) index, (object) "strQuest", (object) "a_index", (object) 4, (object) "a_name", (object) "a_desc", (object) "a_desc2", (object) "a_desc3");
                  break;
                case 8:
                  this.exportData((object) StringIdx, (object) index, (object) "strSkill", (object) "a_index", (object) 3, (object) "a_name", (object) "a_client_description", (object) "a_client_tooltip");
                  break;
                case 9:
                  this.exportData((object) StringIdx, (object) index, (object) "strSSkill", (object) "a_index", (object) 2, (object) "a_name", (object) "a_desc");
                  break;
                case 10:
                  this.exportData((object) StringIdx, (object) index, (object) "strAction", (object) "a_index", (object) 2, (object) "a_name", (object) "a_client_description");
                  break;
                case 11:
                  this.exportData((object) StringIdx, (object) index, (object) "strCombo", (object) "a_index", (object) 1, (object) "a_name");
                  break;
                case 12:
                  this.exportData((object) StringIdx, (object) index, (object) "strAffinity", (object) "a_index", (object) 1, (object) "a_name");
                  break;
                case 13:
                  this.exportData((object) StringIdx, (object) index, (object) "strLacarette", (object) "a_index", (object) 1, (object) "a_name");
                  break;
                case 14:
                  this.exportData((object) StringIdx, (object) index, (object) "strItemCollection", (object) "a_theme", (object) 2, (object) "a_theme_string", (object) "a_desc_string");
                  break;
              }
            }
          }
        }
      }
      this._lb_output.SelectedIndex = this._lb_output.Items.Add((object) "Exported Completed!");
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void _chk_nation_tha_CheckedChanged(object sender, EventArgs e)
    {
      if (this._chk_nation_tha.Checked)
        this.textBox1.Text = "THA";
      else
        this.textBox1.Text = "0";
    }

    private void InitializeComponent()
    {
      this._chk_all = new CheckBox();
      this.groupBox1 = new GroupBox();
      this._chk_itemcollection = new CheckBox();
      this._chk_lacarette = new CheckBox();
      this._chk_opt_rare = new CheckBox();
      this._chk_option = new CheckBox();
      this._chk_affinity = new CheckBox();
      this._chk_combo = new CheckBox();
      this._chk_help1 = new CheckBox();
      this._chk_sskill = new CheckBox();
      this._chk_action = new CheckBox();
      this._chk_skill = new CheckBox();
      this._chk_quest = new CheckBox();
      this._chk_npcname = new CheckBox();
      this._chk_setitem = new CheckBox();
      this._chk_item = new CheckBox();
      this._chk_string = new CheckBox();
      this._group_nation = new GroupBox();
      this._chk_nation_usa = new CheckBox();
      this._chk_nation_uk = new CheckBox();
      this._chk_nation_rus = new CheckBox();
      this._chk_nation_tha = new CheckBox();
      this._radio_pre = new RadioButton();
      this._chk_nation_bra = new CheckBox();
      this._radio_ship = new RadioButton();
      this._chk_nation_mex = new CheckBox();
      this.button2 = new Button();
      this._chk_nation_dev = new CheckBox();
      this._chk_nation_pol = new CheckBox();
      this._chk_nation_esp = new CheckBox();
      this._chk_nation_gamigo_all = new CheckBox();
      this._chk_nation_fra = new CheckBox();
      this._chk_nation_ita = new CheckBox();
      this._chk_nation_ger = new CheckBox();
      this._btn_select_all = new Button();
      this.label1 = new Label();
      this._lb_output = new ListBox();
      this.textBox1 = new TextBox();
      this.groupBox1.SuspendLayout();
      this._group_nation.SuspendLayout();
      this.SuspendLayout();
      this._chk_all.AutoSize = true;
      this._chk_all.Location = new Point(16, 25);
      this._chk_all.Name = "_chk_all";
      this._chk_all.Size = new Size(45, 17);
      this._chk_all.TabIndex = 0;
      this._chk_all.Text = "ALL";
      this._chk_all.UseVisualStyleBackColor = true;
      this._chk_all.CheckedChanged += new EventHandler(this._chk_all_CheckedChanged);
      this.groupBox1.Controls.Add((Control) this._chk_itemcollection);
      this.groupBox1.Controls.Add((Control) this._chk_lacarette);
      this.groupBox1.Controls.Add((Control) this._chk_opt_rare);
      this.groupBox1.Controls.Add((Control) this._chk_option);
      this.groupBox1.Controls.Add((Control) this._chk_affinity);
      this.groupBox1.Controls.Add((Control) this._chk_combo);
      this.groupBox1.Controls.Add((Control) this._chk_help1);
      this.groupBox1.Controls.Add((Control) this._chk_sskill);
      this.groupBox1.Controls.Add((Control) this._chk_action);
      this.groupBox1.Controls.Add((Control) this._chk_skill);
      this.groupBox1.Controls.Add((Control) this._chk_quest);
      this.groupBox1.Controls.Add((Control) this._chk_npcname);
      this.groupBox1.Controls.Add((Control) this._chk_setitem);
      this.groupBox1.Controls.Add((Control) this._chk_item);
      this.groupBox1.Controls.Add((Control) this._chk_string);
      this.groupBox1.Controls.Add((Control) this._chk_all);
      this.groupBox1.Location = new Point(10, 8);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(189, 174);
      this.groupBox1.TabIndex = 1;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "String Type";
      this._chk_itemcollection.AutoSize = true;
      this._chk_itemcollection.Location = new Point(93, 152);
      this._chk_itemcollection.Name = "_chk_itemcollection";
      this._chk_itemcollection.Size = new Size(95, 17);
      this._chk_itemcollection.TabIndex = 20;
      this._chk_itemcollection.Text = "Item Collection";
      this._chk_itemcollection.UseVisualStyleBackColor = true;
      this._chk_lacarette.AutoSize = true;
      this._chk_lacarette.Location = new Point(16, 151);
      this._chk_lacarette.Name = "_chk_lacarette";
      this._chk_lacarette.Size = new Size(71, 17);
      this._chk_lacarette.TabIndex = 19;
      this._chk_lacarette.Text = "Lacarette";
      this._chk_lacarette.UseVisualStyleBackColor = true;
      this._chk_opt_rare.AutoSize = true;
      this._chk_opt_rare.Location = new Point(93, 61);
      this._chk_opt_rare.Name = "_chk_opt_rare";
      this._chk_opt_rare.Size = new Size(83, 17);
      this._chk_opt_rare.TabIndex = 17;
      this._chk_opt_rare.Text = "Rare Option";
      this._chk_opt_rare.UseVisualStyleBackColor = true;
      this._chk_option.AutoSize = true;
      this._chk_option.Location = new Point(16, 79);
      this._chk_option.Name = "_chk_option";
      this._chk_option.Size = new Size(57, 17);
      this._chk_option.TabIndex = 16;
      this._chk_option.Text = "Option";
      this._chk_option.UseVisualStyleBackColor = true;
      this._chk_affinity.AutoSize = true;
      this._chk_affinity.Location = new Point(93, 134);
      this._chk_affinity.Name = "_chk_affinity";
      this._chk_affinity.Size = new Size(57, 17);
      this._chk_affinity.TabIndex = 13;
      this._chk_affinity.Text = "Affinity";
      this._chk_affinity.UseVisualStyleBackColor = true;
      this._chk_combo.AutoSize = true;
      this._chk_combo.Location = new Point(16, 133);
      this._chk_combo.Name = "_chk_combo";
      this._chk_combo.Size = new Size(59, 17);
      this._chk_combo.TabIndex = 12;
      this._chk_combo.Text = "Combo";
      this._chk_combo.UseVisualStyleBackColor = true;
      this._chk_help1.AutoSize = true;
      this._chk_help1.Location = new Point(93, 25);
      this._chk_help1.Name = "_chk_help1";
      this._chk_help1.Size = new Size(54, 17);
      this._chk_help1.TabIndex = 11;
      this._chk_help1.Text = "Help1";
      this._chk_help1.UseVisualStyleBackColor = true;
      this._chk_sskill.AutoSize = true;
      this._chk_sskill.Location = new Point(93, 97);
      this._chk_sskill.Name = "_chk_sskill";
      this._chk_sskill.Size = new Size(55, 17);
      this._chk_sskill.TabIndex = 10;
      this._chk_sskill.Text = "S Skill";
      this._chk_sskill.UseVisualStyleBackColor = true;
      this._chk_action.AutoSize = true;
      this._chk_action.Location = new Point(93, 115);
      this._chk_action.Name = "_chk_action";
      this._chk_action.Size = new Size(56, 17);
      this._chk_action.TabIndex = 9;
      this._chk_action.Text = "Action";
      this._chk_action.UseVisualStyleBackColor = true;
      this._chk_skill.AutoSize = true;
      this._chk_skill.Location = new Point(16, 115);
      this._chk_skill.Name = "_chk_skill";
      this._chk_skill.Size = new Size(45, 17);
      this._chk_skill.TabIndex = 8;
      this._chk_skill.Text = "Skill";
      this._chk_skill.UseVisualStyleBackColor = true;
      this._chk_quest.AutoSize = true;
      this._chk_quest.Location = new Point(93, 79);
      this._chk_quest.Name = "_chk_quest";
      this._chk_quest.Size = new Size(54, 17);
      this._chk_quest.TabIndex = 7;
      this._chk_quest.Text = "Quest";
      this._chk_quest.UseVisualStyleBackColor = true;
      this._chk_npcname.AutoSize = true;
      this._chk_npcname.Location = new Point(16, 97);
      this._chk_npcname.Name = "_chk_npcname";
      this._chk_npcname.Size = new Size(79, 17);
      this._chk_npcname.TabIndex = 5;
      this._chk_npcname.Text = "NPC Name";
      this._chk_npcname.UseVisualStyleBackColor = true;
      this._chk_setitem.AutoSize = true;
      this._chk_setitem.Location = new Point(93, 43);
      this._chk_setitem.Name = "_chk_setitem";
      this._chk_setitem.Size = new Size(62, 17);
      this._chk_setitem.TabIndex = 3;
      this._chk_setitem.Text = "SetItem";
      this._chk_setitem.UseVisualStyleBackColor = true;
      this._chk_item.AutoSize = true;
      this._chk_item.Location = new Point(16, 61);
      this._chk_item.Name = "_chk_item";
      this._chk_item.Size = new Size(46, 17);
      this._chk_item.TabIndex = 2;
      this._chk_item.Text = "Item";
      this._chk_item.UseVisualStyleBackColor = true;
      this._chk_string.AutoSize = true;
      this._chk_string.Location = new Point(16, 43);
      this._chk_string.Name = "_chk_string";
      this._chk_string.Size = new Size(53, 17);
      this._chk_string.TabIndex = 1;
      this._chk_string.Text = "String";
      this._chk_string.UseVisualStyleBackColor = true;
      this._group_nation.Controls.Add((Control) this._chk_nation_usa);
      this._group_nation.Controls.Add((Control) this._chk_nation_uk);
      this._group_nation.Controls.Add((Control) this._chk_nation_rus);
      this._group_nation.Controls.Add((Control) this._chk_nation_tha);
      this._group_nation.Controls.Add((Control) this._radio_pre);
      this._group_nation.Controls.Add((Control) this._chk_nation_bra);
      this._group_nation.Controls.Add((Control) this._radio_ship);
      this._group_nation.Controls.Add((Control) this._chk_nation_mex);
      this._group_nation.Controls.Add((Control) this.button2);
      this._group_nation.Controls.Add((Control) this._chk_nation_dev);
      this._group_nation.Controls.Add((Control) this._chk_nation_pol);
      this._group_nation.Controls.Add((Control) this._chk_nation_esp);
      this._group_nation.Controls.Add((Control) this._chk_nation_gamigo_all);
      this._group_nation.Controls.Add((Control) this._chk_nation_fra);
      this._group_nation.Controls.Add((Control) this._chk_nation_ita);
      this._group_nation.Controls.Add((Control) this._chk_nation_ger);
      this._group_nation.Location = new Point(205, 8);
      this._group_nation.Name = "_group_nation";
      this._group_nation.Size = new Size(201, 174);
      this._group_nation.TabIndex = 2;
      this._group_nation.TabStop = false;
      this._group_nation.Text = "Nation";
      this._chk_nation_usa.AutoSize = true;
      this._chk_nation_usa.Location = new Point(18, 94);
      this._chk_nation_usa.Name = "_chk_nation_usa";
      this._chk_nation_usa.Size = new Size(41, 17);
      this._chk_nation_usa.TabIndex = 6;
      this._chk_nation_usa.Text = "US";
      this._chk_nation_usa.UseVisualStyleBackColor = true;
      this._chk_nation_uk.AutoSize = true;
      this._chk_nation_uk.Location = new Point(118, 76);
      this._chk_nation_uk.Name = "_chk_nation_uk";
      this._chk_nation_uk.Size = new Size(41, 17);
      this._chk_nation_uk.TabIndex = 7;
      this._chk_nation_uk.Text = "UK";
      this._chk_nation_uk.UseVisualStyleBackColor = true;
      this._chk_nation_rus.AutoSize = true;
      this._chk_nation_rus.Location = new Point(67, 76);
      this._chk_nation_rus.Name = "_chk_nation_rus";
      this._chk_nation_rus.Size = new Size(49, 17);
      this._chk_nation_rus.TabIndex = 5;
      this._chk_nation_rus.Text = "RUS";
      this._chk_nation_rus.UseVisualStyleBackColor = true;
      this._chk_nation_tha.AutoSize = true;
      this._chk_nation_tha.Location = new Point(118, 58);
      this._chk_nation_tha.Name = "_chk_nation_tha";
      this._chk_nation_tha.Size = new Size(48, 17);
      this._chk_nation_tha.TabIndex = 7;
      this._chk_nation_tha.Text = "THA";
      this._chk_nation_tha.UseVisualStyleBackColor = true;
      this._chk_nation_tha.CheckedChanged += new EventHandler(this._chk_nation_tha_CheckedChanged);
      this._radio_pre.AutoSize = true;
      this._radio_pre.Location = new Point(92, 117);
      this._radio_pre.Name = "_radio_pre";
      this._radio_pre.Size = new Size(63, 17);
      this._radio_pre.TabIndex = 1;
      this._radio_pre.TabStop = true;
      this._radio_pre.Text = "Pre Ver.";
      this._radio_pre.UseVisualStyleBackColor = true;
      this._chk_nation_bra.AutoSize = true;
      this._chk_nation_bra.Location = new Point(18, 76);
      this._chk_nation_bra.Name = "_chk_nation_bra";
      this._chk_nation_bra.Size = new Size(48, 17);
      this._chk_nation_bra.TabIndex = 3;
      this._chk_nation_bra.Text = "BRA";
      this._chk_nation_bra.UseVisualStyleBackColor = true;
      this._radio_ship.AutoSize = true;
      this._radio_ship.Checked = true;
      this._radio_ship.Location = new Point(18, 117);
      this._radio_ship.Name = "_radio_ship";
      this._radio_ship.Size = new Size(68, 17);
      this._radio_ship.TabIndex = 0;
      this._radio_ship.TabStop = true;
      this._radio_ship.Text = "Ship Ver.";
      this._radio_ship.UseVisualStyleBackColor = true;
      this._chk_nation_mex.AutoSize = true;
      this._chk_nation_mex.Location = new Point(67, 58);
      this._chk_nation_mex.Name = "_chk_nation_mex";
      this._chk_nation_mex.Size = new Size(49, 17);
      this._chk_nation_mex.TabIndex = 4;
      this._chk_nation_mex.Text = "MEX";
      this._chk_nation_mex.UseVisualStyleBackColor = true;
      this.button2.Location = new Point(18, 140);
      this.button2.Name = "button2";
      this.button2.Size = new Size(64, 25);
      this.button2.TabIndex = 3;
      this.button2.Text = "Export";
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Click += new EventHandler(this.OnExport);
      this._chk_nation_dev.AutoSize = true;
      this._chk_nation_dev.Location = new Point(18, 22);
      this._chk_nation_dev.Name = "_chk_nation_dev";
      this._chk_nation_dev.Size = new Size(46, 17);
      this._chk_nation_dev.TabIndex = 0;
      this._chk_nation_dev.Text = "Dev";
      this._chk_nation_dev.UseVisualStyleBackColor = true;
      this._chk_nation_pol.AutoSize = true;
      this._chk_nation_pol.Location = new Point(18, 58);
      this._chk_nation_pol.Name = "_chk_nation_pol";
      this._chk_nation_pol.Size = new Size(47, 17);
      this._chk_nation_pol.TabIndex = 4;
      this._chk_nation_pol.Text = "POL";
      this._chk_nation_pol.UseVisualStyleBackColor = true;
      this._chk_nation_esp.AutoSize = true;
      this._chk_nation_esp.Location = new Point(118, 40);
      this._chk_nation_esp.Name = "_chk_nation_esp";
      this._chk_nation_esp.Size = new Size(47, 17);
      this._chk_nation_esp.TabIndex = 5;
      this._chk_nation_esp.Text = "ESP";
      this._chk_nation_esp.UseVisualStyleBackColor = true;
      this._chk_nation_gamigo_all.AutoSize = true;
      this._chk_nation_gamigo_all.Location = new Point(67, 22);
      this._chk_nation_gamigo_all.Name = "_chk_nation_gamigo_all";
      this._chk_nation_gamigo_all.Size = new Size(45, 17);
      this._chk_nation_gamigo_all.TabIndex = 0;
      this._chk_nation_gamigo_all.Text = "ALL";
      this._chk_nation_gamigo_all.UseVisualStyleBackColor = true;
      this._chk_nation_gamigo_all.CheckedChanged += new EventHandler(this._chk_nation_gamigo_all_CheckedChanged);
      this._chk_nation_fra.AutoSize = true;
      this._chk_nation_fra.Location = new Point(118, 22);
      this._chk_nation_fra.Name = "_chk_nation_fra";
      this._chk_nation_fra.Size = new Size(47, 17);
      this._chk_nation_fra.TabIndex = 2;
      this._chk_nation_fra.Text = "FRA";
      this._chk_nation_fra.UseVisualStyleBackColor = true;
      this._chk_nation_ita.AutoSize = true;
      this._chk_nation_ita.Location = new Point(18, 40);
      this._chk_nation_ita.Name = "_chk_nation_ita";
      this._chk_nation_ita.Size = new Size(43, 17);
      this._chk_nation_ita.TabIndex = 3;
      this._chk_nation_ita.Text = "ITA";
      this._chk_nation_ita.UseVisualStyleBackColor = true;
      this._chk_nation_ger.AutoSize = true;
      this._chk_nation_ger.Location = new Point(67, 40);
      this._chk_nation_ger.Name = "_chk_nation_ger";
      this._chk_nation_ger.Size = new Size(49, 17);
      this._chk_nation_ger.TabIndex = 1;
      this._chk_nation_ger.Text = "GER";
      this._chk_nation_ger.UseVisualStyleBackColor = true;
      this._btn_select_all.Location = new Point(479, 191);
      this._btn_select_all.Name = "_btn_select_all";
      this._btn_select_all.Size = new Size(64, 25);
      this._btn_select_all.TabIndex = 8;
      this._btn_select_all.Text = "Select All";
      this._btn_select_all.UseVisualStyleBackColor = true;
      this._btn_select_all.Click += new EventHandler(this.OnChangeBtnSelect);
      this.label1.AutoSize = true;
      this.label1.Location = new Point(11, 516);
      this.label1.Name = "label1";
      this.label1.Size = new Size(25, 13);
      this.label1.TabIndex = 5;
      this.label1.Text = "Log";
      this._lb_output.BackColor = SystemColors.InfoText;
      this._lb_output.ForeColor = Color.Yellow;
      this._lb_output.FormattingEnabled = true;
      this._lb_output.Location = new Point(412, 5);
      this._lb_output.Name = "_lb_output";
      this._lb_output.Size = new Size(211, 160);
      this._lb_output.TabIndex = 6;
      this.textBox1.Location = new Point(477, 166);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(100, 20);
      this.textBox1.TabIndex = 9;
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(631, 187);
      this.Controls.Add((Control) this.textBox1);
      this.Controls.Add((Control) this._lb_output);
      this.Controls.Add((Control) this.label1);
      this.Controls.Add((Control) this._group_nation);
      this.Controls.Add((Control) this.groupBox1);
      this.Controls.Add((Control) this._btn_select_all);
      this.FormBorderStyle = FormBorderStyle.FixedDialog;
      this.MaximizeBox = false;
      this.Name = nameof (FormExport);
      this.Text = "String Export";
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this._group_nation.ResumeLayout(false);
      this._group_nation.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();
    }

    private void OnInitNation()
    {
      this._radio_ship.Checked = true;
      MySqlConnection mySqlConnection = new MySqlConnection("datasource=" + this.Host + ";Port=3306;User ID="  + this.User + ";Password=" + this.Password + ";Database=" + this.Database + ";Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;");
      this._chk_nation_dev.Hide();
      this._btn_select_all.Hide();
    }

    private bool QueryProc(int StringIdx)
    {
      this._lb_output.Items.Add((object) string.Format("{0} DB Query 시작", (object) ((FormExport.eSTRING) StringIdx).ToString()));
      this._lb_output.Refresh();
      this._lb_output.Invalidate();
      switch (StringIdx)
      {
        case 0:
          this._sql2.Query("SELECT * FROM t_string ORDER BY a_index");
          break;
        case 1:
          this._sql2.Query("SELECT * FROM t_help1 ORDER BY a_index");
          break;
        case 2:
          this._sql2.Query("SELECT * FROM t_item WHERE a_enable = 1 ORDER BY a_index");
          break;
        case 3:
          this._sql2.Query("SELECT * FROM t_set_item WHERE a_enable = 1 ORDER BY a_set_idx");
          break;
        case 4:
          this._sql2.Query("SELECT * FROM t_option ORDER BY a_index");
          break;
        case 5:
          this._sql2.Query("SELECT * FROM t_rareoption ORDER BY a_index");
          break;
        case 6:
          this._sql2.Query("SELECT DISTINCT * FROM t_npc WHERE a_enable = 1 ORDER BY a_index");
          break;
        case 7:
          this._sql2.Query("SELECT * FROM t_quest ORDER BY a_index");
          break;
        case 8:
          this._sql2.Query("SELECT * FROM t_skill WHERE a_job>=0 ORDER BY a_index");
          break;
        case 9:
          this._sql2.Query("SELECT * FROM t_special_skill WHERE a_enable=1 ORDER BY a_index");
          break;
        case 10:
          this._sql2.Query("SELECT * FROM t_action WHERE a_index = a_index ORDER BY a_index");
          break;
        case 11:
          this._sql2.Query("SELECT * FROM t_missioncase WHERE a_enable = 1 ORDER BY a_index");
          break;
        case 12:
          this._sql2.Query("SELECT * FROM t_affinity WHERE a_enable = 1 ORDER BY a_index");
          break;
        case 13:
          this._sql2.Query("SELECT * FROM t_lacarette WHERE a_enable = 1 ORDER BY a_index");
          break;
        case 14:
          this._sql2.Query("SELECT * FROM t_item_collection ORDER BY a_theme");
          break;
      }
      return true;
    }

    private void _chk_all_CheckedChanged(object sender, EventArgs e)
    {
      bool flag = this._chk_all.Checked;
      this._chk_string.Checked = flag;
      this._chk_help1.Checked = flag;
      this._chk_item.Checked = flag;
      this._chk_setitem.Checked = flag;
      this._chk_option.Checked = flag;
      this._chk_opt_rare.Checked = flag;
      this._chk_npcname.Checked = flag;
      this._chk_quest.Checked = flag;
      this._chk_skill.Checked = flag;
      this._chk_sskill.Checked = flag;
      this._chk_action.Checked = flag;
      this._chk_combo.Checked = flag;
      this._chk_affinity.Checked = flag;
      this._chk_lacarette.Checked = flag;
      this._chk_itemcollection.Checked = flag;
    }

    private void _chk_nation_gamigo_all_CheckedChanged(object sender, EventArgs e)
    {
      bool flag = this._chk_nation_gamigo_all.Checked;
      this._chk_nation_ger.Checked = flag;
      this._chk_nation_fra.Checked = flag;
      this._chk_nation_ita.Checked = flag;
      this._chk_nation_pol.Checked = flag;
      this._chk_nation_esp.Checked = flag;
      this._chk_nation_usa.Checked = flag;
      this._chk_nation_bra.Checked = flag;
      this._chk_nation_mex.Checked = flag;
      this._chk_nation_uk.Checked = flag;
      this._chk_nation_rus.Checked = flag;
    }

    private void OnChangeBtnSelect(object sender, EventArgs e)
    {
      bool flag = !this._chk_nation_dev.Checked;
      this._chk_nation_dev.Checked = flag;
      this._chk_nation_gamigo_all.Checked = flag;
      this._chk_nation_rus.Checked = flag;
      this._chk_nation_tha.Checked = flag;
      if (flag)
        this._btn_select_all.Text = "선택 해제";
      else
        this._btn_select_all.Text = "전체 선택";
    }

    private void saveLocationToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Process.Start("StrConfig.ini");
    }

    public enum eSTRING
    {
      STRING,
      HELP1,
      ITEM,
      ITEM_SET,
      OPTION,
      OPTION_RARE,
      NPC_NAME,
      QUEST,
      SKILL,
      SKILL_SPECIAL,
      ACTION,
      COMBO,
      AFFINITY,
      LACARETTE,
      ITEMCOLLECTION,
      MAX,
    }

    public enum eNATION
    {
      DEV,
      GER,
      FRA,
      ITA,
      POL,
      ESP,
      BRA,
      MEX,
      RUS,
      USA,
      THA,
      GBR,
      MAX,
    }
  }
}
