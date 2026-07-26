// Decompiled with JetBrains decompiler
// Type: String_Editor.Form1
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using LcDevPack_TeamDamonA;
using MySqlConnector;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;

#nullable disable
namespace String_Editor
{
  public class Form1 : Form
  {
    public static List<StringContainer> StringList = new List<StringContainer>();
    private string ISO = "ISO-8859-1";
    public string ERROR_TITULO = "ERRO";
    public string ERROR_SUPORTE = "Este arquivo não é suportado";
    public string ERROR_NATION = "Por favor insira a nação no nome do arquivo, Exemplo: (strClient_XX.lod) XX = Nação";
    public string ERROR_SALVAR = "";
    public string SUCESSO_TITULO = "SUCESSO";
    public string SUCESSO_SALVAR = "Arquivo salvo com sucesso";
    public string INFORMACAO_TITULO = "INFORMAÇÃO";
    public string INFORMACAO_SALVAR = "Por favor insira a nação no nome do arquivo, Exemplo: (strClient_XX.lod) XX = Nação";
    private IContainer components = (IContainer) null;
    public int lastid3;
    public int lastid4;
    public int lastid5;
    public int lastid6;
    public string FileName;
    public string FileOpen;
    public string nation;
    public static string strProvider;
    private MenuStrip menuStrip1;
    private ToolStripMenuItem menu_arquivo;
    private ToolStripMenuItem menu_abrir;
    private ToolStripMenuItem menu_salvar;
    private ToolStripMenuItem menu_sair;
    private TextBox textBox1;
    private ListBox listBox1;
    private GroupBox gbGeral;
    private GroupBox gbEditar;
    private Label lbSucesso;
    private Button btnGravar;
    private TextBox textBox5;
    private TextBox textBox4;
    private TextBox textBox3;
    private TextBox textBox2;
    private Label lbDescr2;
    private Label lbDescr;
    private Label lbNome;
    private Label lbID;
    private ComboBox cb_idioma;
    private Button lbBuscar;
    private Button button1;
    private Button button3;
    private Button button2;
    private ProgressBar progressBar1;
    private TextBox textBox6;
    private Label label1;
    private Label label2;
    private Label label3;
    private TextBox textBox7;
    private string thaieng = "thai";
    public static Connection connection = new Connection();
        private string Host => Form1.connection.Settings.SqlHost;
        private string User => Form1.connection.Settings.SqlUser;
        private string Password => Form1.connection.Settings.SqlPassword;
        private string Database => Form1.connection.Settings.SqlDatabase;

        public Form1()
    {
      this.InitializeComponent();
            MySqlConnection mySqlConnection = new MySqlConnection(
          "Server=" + this.Host +
          ";Port=3306" +
          ";User ID=" + this.User +
          ";Password=" + this.Password +
          ";Database=" + this.Database +
          ";Charset=utf8mb4" +
          ";SslMode=Preferred" +
          ";TlsVersion=Tls12;"
      );
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            this.checkDir();
            Form1.strProvider =
    $"Server={Host};Port=3306;User ID={User};Password={Password};Database={Database};" +
    "Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;";

            MySqlConnection mySqlConnection = new MySqlConnection(Form1.strProvider);
        }

        private void clean()
    {
      Form1.StringList.Clear();
      this.listBox1.Items.Clear();
      this.textBox1.Clear();
      this.textBox2.Clear();
      this.textBox3.Clear();
      this.textBox4.Clear();
      this.textBox5.Clear();
      this.textBox6.Clear();
    }

    private void readFile(int ver)
    {
      try
      {
        string[] strArray = this.FileName.Split('_')[1].Split('.');
        this.textBox4.Enabled = false;
        this.textBox5.Enabled = false;
        this.textBox6.Enabled = false;
        this.nation = strArray[0];
        if (this.nation.Length == 2)
        {
          try
          {
            using (BinaryReader binaryReader = new BinaryReader((Stream) File.Open(this.FileOpen, FileMode.Open)))
            {
              binaryReader.ReadInt32();
              binaryReader.ReadInt32();
              while (binaryReader.BaseStream.Position < binaryReader.BaseStream.Length)
              {
                StringContainer stringContainer = new StringContainer();
                if (ver == 2015)
                {
                  int num = binaryReader.ReadInt32();
                  stringContainer.Index = num;
                  stringContainer.name = binaryReader.ReadBytes(binaryReader.ReadInt32());
                  Encoding.GetEncoding(this.ISO).GetString(stringContainer.name);
                  if (this.FileName == "strSkill_" + this.nation + ".lod" || this.FileName == "strSSkill_" + this.nation + ".lod" || this.FileName == "strNPCShop_" + this.nation + ".lod" || this.FileName == "strItemCollection_" + this.nation + ".lod" || this.FileName == "strItem_" + this.nation + ".lod" || this.FileName == "strAction_" + this.nation + ".lod" || this.FileName == "strPassiveSystem_" + this.nation + ".lod" || this.FileName == "strQuest_" + this.nation + ".lod")
                  {
                    stringContainer.descr = binaryReader.ReadBytes(binaryReader.ReadInt32());
                    Encoding.GetEncoding(this.ISO).GetString(stringContainer.descr);
                    this.textBox4.Enabled = true;
                  }
                  if (this.FileName == "strSkill_" + this.nation + ".lod" || this.FileName == "strNpcName_" + this.nation + ".lod" || this.FileName == "strNPCHelp_" + this.nation + ".lod" || this.FileName == "strHelp_" + this.nation + ".lod")
                  {
                    int count = binaryReader.ReadInt32();
                    if (count > 0)
                    {
                      stringContainer.descr2 = binaryReader.ReadBytes(count);
                      Encoding.GetEncoding(this.ISO).GetString(stringContainer.descr2);
                      this.textBox5.Enabled = true;
                    }
                    else
                      stringContainer.descr2 = Encoding.GetEncoding(this.ISO).GetBytes("");
                  }
                  if (this.FileName == "strQuest_" + this.nation + ".lod")
                  {
                    stringContainer.descr2 = binaryReader.ReadBytes(binaryReader.ReadInt32());
                    Encoding.GetEncoding(this.ISO).GetString(stringContainer.descr2);
                    this.textBox5.Enabled = true;
                    stringContainer.descr3 = binaryReader.ReadBytes(binaryReader.ReadInt32());
                    Encoding.GetEncoding(this.ISO).GetString(stringContainer.descr3);
                    this.textBox6.Enabled = true;
                  }
                }
                Form1.StringList.Add(stringContainer);
              }
              binaryReader.Close();
              binaryReader.Dispose();
            }
            this.listBox1.Items.Clear();
            this.makelist();
          }
          catch
          {
            int num = (int) MessageBox.Show(this.ERROR_SUPORTE, this.ERROR_TITULO, MessageBoxButtons.OK, MessageBoxIcon.Hand);
            this.gbGeral.Enabled = false;
          }
        }
      }
      catch
      {
        int num = (int) MessageBox.Show(this.ERROR_SUPORTE, this.ERROR_TITULO, MessageBoxButtons.OK, MessageBoxIcon.Hand);
        this.gbGeral.Enabled = false;
      }
      this.textBox7.Text = this.nation;
    }

    private void makelist()
    {
      this.listBox1.Items.Clear();
      Form1.StringList.OrderBy<StringContainer, int>((Func<StringContainer, int>) (x => x.Index));
      List<StringContainer> list = Form1.StringList.OrderBy<StringContainer, int>((Func<StringContainer, int>) (o => o.Index)).ToList<StringContainer>();
      int num = list.Count<StringContainer>();
      for (int index = 0; index < num; ++index)
        this.listBox1.Items.Add((object) (list[index].Index.ToString() + " - " + Encoding.GetEncoding(this.ISO).GetString(list[index].name)));
      this.menu_salvar.Enabled = true;
      this.gbGeral.Enabled = true;
    }

    private void checkDir()
    {
      if (!Directory.Exists("Config\\\\lang"))
      {
        Directory.CreateDirectory("Config\\\\lang");
        this.checkTranducao();
      }
      else
        this.checkTranducao();
    }

    private void checkTranducao()
    {
      if (Directory.EnumerateFileSystemEntries("Config\\\\lang").Any<string>())
      {
        string[] files = Directory.GetFiles("Config\\\\lang");
        for (int index = 0; index < files.Length; ++index)
        {
          this.cb_idioma.Items.Add((object) Path.GetFileNameWithoutExtension(files[index]));
          if (index == 0)
          {
            this.cb_idioma.Text = "pt-BR";
            this.cb_idioma.SelectedItem = (object) "pt-BR";
          }
        }
      }
      else
      {
        using (StreamWriter streamWriter = new StreamWriter("Config\\\\lang\\\\usa.txt"))
        {
          streamWriter.WriteLine("############## English - USA ##############");
          streamWriter.WriteLine("------------------- Menus -------------------");
          streamWriter.WriteLine("menu_arquivo=File");
          streamWriter.WriteLine("menu_abrir=Open");
          streamWriter.WriteLine("menu_salvar=Save");
          streamWriter.WriteLine("menu_sair=Exit");
          streamWriter.WriteLine("------------------- Label -------------------");
          streamWriter.WriteLine("label_buscar=Search");
          streamWriter.WriteLine("gb_geral=General");
          streamWriter.WriteLine("gb_editar=Edit");
          streamWriter.WriteLine("------------------- Buttons -----------------");
          streamWriter.WriteLine("btn_gravar=Save");
          streamWriter.WriteLine("------------------- ERRORs -----------------");
          streamWriter.WriteLine("erro_titulo=ERROR");
          streamWriter.WriteLine("erro_suporte=This File is not Supported");
          streamWriter.WriteLine("erro_nation=Please enter the nation in the file name, Example: (strClient_XX.lod) XX = Nation");
          streamWriter.WriteLine("erro_salvar=Could not save the file");
          streamWriter.WriteLine("------------------- SUCCESS -----------------");
          streamWriter.WriteLine("sucesso_titulo=SUCCESS");
          streamWriter.WriteLine("sucesso_gravar=Successfully saved changes");
          streamWriter.WriteLine("sucesso_salvar=Successfully saved file");
          streamWriter.WriteLine("------------------- INFORMATION ------------");
          streamWriter.WriteLine("iformacao_titulo=INFORMATION");
          streamWriter.WriteLine("informacao_salvar=Please enter the nation in the file name, Example: (strClient_XX.lod) XX = Nation");
        }
        using (StreamWriter streamWriter = new StreamWriter("Config\\\\lang\\\\thai.txt"))
        {
          streamWriter.WriteLine("############## THAI ##############");
          streamWriter.WriteLine("------------------- Menus -------------------");
          streamWriter.WriteLine("menu_arquivo=ไฟล์");
          streamWriter.WriteLine("menu_abrir=เปิด");
          streamWriter.WriteLine("menu_salvar=บันทึก");
          streamWriter.WriteLine("menu_sair=ปิด");
          streamWriter.WriteLine("------------------- Label -------------------");
          streamWriter.WriteLine("label_buscar=ค้นหา");
          streamWriter.WriteLine("gb_geral=ทั่วไป");
          streamWriter.WriteLine("gb_editar=แก้ไข");
          streamWriter.WriteLine("------------------- Buttons -----------------");
          streamWriter.WriteLine("btn_gravar=บันทึก");
          streamWriter.WriteLine("------------------- ERRORs -----------------");
          streamWriter.WriteLine("erro_titulo=ERROR");
          streamWriter.WriteLine("erro_suporte=ไฟล์นี้ไม่รองรับ");
          streamWriter.WriteLine("erro_nation=โปรดเลือกภาษาที่ต้องการบันทึก, Example: (strClient_XX.lod) XX = Nation");
          streamWriter.WriteLine("erro_salvar=ไม่สามารถบันทึกการเปลี่ยนแปลง");
          streamWriter.WriteLine("------------------- SUCCESS -----------------");
          streamWriter.WriteLine("sucesso_titulo=SUCCESS");
          streamWriter.WriteLine("sucesso_gravar=บันทึกการเปลี่ยนแปลงสำเร็จแล้ว");
          streamWriter.WriteLine("sucesso_salvar=บันทึกสำเร็จแล้ว");
          streamWriter.WriteLine("------------------- INFORMATION ------------");
          streamWriter.WriteLine("iformacao_titulo=INFORMATION");
          streamWriter.WriteLine("informacao_salvar=โปรดเลือกภาษาที่ต้องการบันทึก, Example: (strClient_XX.lod) XX = Nation");
        }
        using (StreamWriter streamWriter = new StreamWriter("Config\\\\lang\\\\pld.txt"))
        {
          streamWriter.WriteLine("############## English - USA ##############");
          streamWriter.WriteLine("------------------- Menus -------------------");
          streamWriter.WriteLine("menu_arquivo=File");
          streamWriter.WriteLine("menu_abrir=Open");
          streamWriter.WriteLine("menu_salvar=Save");
          streamWriter.WriteLine("menu_sair=Exit");
          streamWriter.WriteLine("------------------- Label -------------------");
          streamWriter.WriteLine("label_buscar=Search");
          streamWriter.WriteLine("gb_geral=General");
          streamWriter.WriteLine("gb_editar=Edit");
          streamWriter.WriteLine("------------------- Buttons -----------------");
          streamWriter.WriteLine("btn_gravar=Save");
          streamWriter.WriteLine("------------------- ERRORs -----------------");
          streamWriter.WriteLine("erro_titulo=ERROR");
          streamWriter.WriteLine("erro_suporte=This File is not Supported");
          streamWriter.WriteLine("erro_nation=Please enter the nation in the file name, Example: (strClient_XX.lod) XX = Nation");
          streamWriter.WriteLine("erro_salvar=Could not save the file");
          streamWriter.WriteLine("------------------- SUCCESS -----------------");
          streamWriter.WriteLine("sucesso_titulo=SUCCESS");
          streamWriter.WriteLine("sucesso_gravar=Successfully saved changes");
          streamWriter.WriteLine("sucesso_salvar=Successfully saved file");
          streamWriter.WriteLine("------------------- INFORMATION ------------");
          streamWriter.WriteLine("iformacao_titulo=INFORMATION");
          streamWriter.WriteLine("informacao_salvar=Please enter the nation in the file name, Example: (strClient_XX.lod) XX = Nation");
        }
        using (StreamWriter streamWriter = new StreamWriter("Config\\\\lang\\\\ger.txt"))
        {
          streamWriter.WriteLine("############## English - USA ##############");
          streamWriter.WriteLine("------------------- Menus -------------------");
          streamWriter.WriteLine("menu_arquivo=File");
          streamWriter.WriteLine("menu_abrir=Open");
          streamWriter.WriteLine("menu_salvar=Save");
          streamWriter.WriteLine("menu_sair=Exit");
          streamWriter.WriteLine("------------------- Label -------------------");
          streamWriter.WriteLine("label_buscar=Search");
          streamWriter.WriteLine("gb_geral=General");
          streamWriter.WriteLine("gb_editar=Edit");
          streamWriter.WriteLine("------------------- Buttons -----------------");
          streamWriter.WriteLine("btn_gravar=Save");
          streamWriter.WriteLine("------------------- ERRORs -----------------");
          streamWriter.WriteLine("erro_titulo=ERROR");
          streamWriter.WriteLine("erro_suporte=This File is not Supported");
          streamWriter.WriteLine("erro_nation=Please enter the nation in the file name, Example: (strClient_XX.lod) XX = Nation");
          streamWriter.WriteLine("erro_salvar=Could not save the file");
          streamWriter.WriteLine("------------------- SUCCESS -----------------");
          streamWriter.WriteLine("sucesso_titulo=SUCCESS");
          streamWriter.WriteLine("sucesso_gravar=Successfully saved changes");
          streamWriter.WriteLine("sucesso_salvar=Successfully saved file");
          streamWriter.WriteLine("------------------- INFORMATION ------------");
          streamWriter.WriteLine("iformacao_titulo=INFORMATION");
          streamWriter.WriteLine("informacao_salvar=Please enter the nation in the file name, Example: (strClient_XX.lod) XX = Nation");
        }
        using (StreamWriter streamWriter = new StreamWriter("Config\\\\lang\\\\rus.txt"))
        {
          streamWriter.WriteLine("############## Russian ##############");
          streamWriter.WriteLine("------------------- Menus -------------------");
          streamWriter.WriteLine("menu_arquivo=Файл");
          streamWriter.WriteLine("menu_abrir=Открыть");
          streamWriter.WriteLine("menu_salvar=Сохранить");
          streamWriter.WriteLine("menu_sair=Выход");
          streamWriter.WriteLine("------------------- Label -------------------");
          streamWriter.WriteLine("label_buscar=Поиск");
          streamWriter.WriteLine("gb_geral=Основное");
          streamWriter.WriteLine("gb_editar=Редактирование");
          streamWriter.WriteLine("------------------- Buttons -----------------");
          streamWriter.WriteLine("btn_gravar=Сохранить");
          streamWriter.WriteLine("------------------- ERRORs -----------------");
          streamWriter.WriteLine("erro_titulo=ОШИБКА");
          streamWriter.WriteLine("erro_suporte=Данный файл не поддерживается!");
          streamWriter.WriteLine("erro_nation=Пожалуйста укажите национальный код, Пример: (strClient_XX.lod) XX = Национальный код");
          streamWriter.WriteLine("erro_salvar=Cannot save file");
          streamWriter.WriteLine("------------------- SUCESS -----------------");
          streamWriter.WriteLine("sucesso_titulo=УСПЕШНО");
          streamWriter.WriteLine("sucesso_gravar=Изменения сохранены");
          streamWriter.WriteLine("sucesso_salvar=Файл сохранен");
          streamWriter.WriteLine("------------------- INFORMATION ------------");
          streamWriter.WriteLine("iformacao_titulo=ИНФОРМАЦИЯ");
          streamWriter.WriteLine("informacao_salvar=Пожалуйста используйте оригинальные названия файлов с национальным кодом,Пример: (strClient_XX.lod) XX = Национальный код");
        }
        using (StreamWriter streamWriter = new StreamWriter("Config\\\\lang\\\\frc.txt", true, Encoding.GetEncoding(this.ISO)))
        {
          streamWriter.WriteLine("############## Français - FRA ##############");
          streamWriter.WriteLine("------------------- Menus -------------------");
          streamWriter.WriteLine("menu_arquivo=File");
          streamWriter.WriteLine("menu_abrir=Ouvrir");
          streamWriter.WriteLine("menu_salvar=Sauvegarder");
          streamWriter.WriteLine("menu_sair=quitter");
          streamWriter.WriteLine("------------------- Label -------------------");
          streamWriter.WriteLine("label_buscar=Chercher");
          streamWriter.WriteLine("gb_geral=General");
          streamWriter.WriteLine("gb_editar=Edité");
          streamWriter.WriteLine("------------------- Bouttons -----------------");
          streamWriter.WriteLine("btn_gravar=Sauvegardé");
          streamWriter.WriteLine("------------------- ERREURs -----------------");
          streamWriter.WriteLine("erro_titulo=ERREUR");
          streamWriter.WriteLine("erro_suporte=Le fichier n'est pas supporter");
          streamWriter.WriteLine("erro_nation=S'il vous plait entré la nation du  fichier, Exemple: (strClient_XX.lod) XX = nation");
          streamWriter.WriteLine("erro_salvar=Ne peut pas sauvegardé  le fichier");
          streamWriter.WriteLine("------------------- SUCCESS -----------------");
          streamWriter.WriteLine("sucesso_titulo=Réussi");
          streamWriter.WriteLine("sucesso_gravar=Changement  réussi avec  succes");
          streamWriter.WriteLine("sucesso_salvar=Réussi fichier changé");
          streamWriter.WriteLine("------------------- INFORMATION ------------");
          streamWriter.WriteLine("iformacao_titulo=INFORMATION");
          streamWriter.WriteLine("informacao_salvar=S'il vous plait entré la nation du  fichier, Exemple: (strClient_XX.lod) XX = nation");
        }
        using (StreamWriter streamWriter = new StreamWriter("Config\\\\lang\\\\brz.txt", true, Encoding.GetEncoding(this.ISO)))
        {
          streamWriter.WriteLine("############## Português - BRASIL ##############");
          streamWriter.WriteLine("------------------- Menus -------------------");
          streamWriter.WriteLine("menu_arquivo=Arquivo");
          streamWriter.WriteLine("menu_abrir=Abrir");
          streamWriter.WriteLine("menu_salvar=Salvar");
          streamWriter.WriteLine("menu_sair=Sair");
          streamWriter.WriteLine("------------------- Label -------------------");
          streamWriter.WriteLine("label_buscar=Buscar");
          streamWriter.WriteLine("gb_geral=Geral");
          streamWriter.WriteLine("gb_editar=Editar");
          streamWriter.WriteLine("------------------- Buttons -----------------");
          streamWriter.WriteLine("btn_gravar=Gravar");
          streamWriter.WriteLine("------------------- ERRORs -----------------");
          streamWriter.WriteLine("erro_titulo=ERRO");
          streamWriter.WriteLine("erro_suporte=Este arquivo não é suportado");
          streamWriter.WriteLine("erro_nation=Por favor insira a nação no nome do arquivo, Exemplo: (strClient_XX.lod) XX = Nação");
          streamWriter.WriteLine("erro_salvar=Não foi possivel salvar o arquivo");
          streamWriter.WriteLine("------------------- SUCESS -----------------");
          streamWriter.WriteLine("sucesso_titulo=SUCESSO");
          streamWriter.WriteLine("sucesso_gravar=Alterações salvas com sucesso");
          streamWriter.WriteLine("sucesso_salvar=Arquivo salvo com sucesso");
          streamWriter.WriteLine("------------------- INFORMATION ------------");
          streamWriter.WriteLine("iformacao_titulo=INFORMAÇÃO");
          streamWriter.WriteLine("informacao_salvar=Por favor insira a nação no nome do arquivo, Exemplo: (strClient_XX.lod) XX = Nação");
        }
        using (StreamWriter streamWriter = new StreamWriter("Config\\\\lang\\\\spn.txt", true, Encoding.GetEncoding(this.ISO)))
        {
          streamWriter.WriteLine("############## Espanhol - Google ##############");
          streamWriter.WriteLine("------------------- Menus -------------------");
          streamWriter.WriteLine("menu_arquivo=Archivo");
          streamWriter.WriteLine("menu_abrir=Abrir");
          streamWriter.WriteLine("menu_salvar=Guardar");
          streamWriter.WriteLine("menu_sair=Salir");
          streamWriter.WriteLine("------------------- Label -------------------");
          streamWriter.WriteLine("label_buscar=Hallar");
          streamWriter.WriteLine("gb_geral=General");
          streamWriter.WriteLine("gb_editar=Editar");
          streamWriter.WriteLine("------------------- Buttons -----------------");
          streamWriter.WriteLine("btn_gravar=Cambiar");
          streamWriter.WriteLine("------------------- ERRORs -----------------");
          streamWriter.WriteLine("erro_titulo=ERROR");
          streamWriter.WriteLine("erro_suporte=Este archivo no es compatible");
          streamWriter.WriteLine("erro_nation=Por favor, introduzca la nación en el nombre del archivo, Ejemplo: (strClient_XX.lod / strClient_XX.lod) XX = Nación");
          streamWriter.WriteLine("erro_salvar=No se pudo guardar el archivo");
          streamWriter.WriteLine("------------------- SUCCESS -----------------");
          streamWriter.WriteLine("sucesso_titulo=ÉXITO");
          streamWriter.WriteLine("sucesso_gravar=Cambios guardados con éxito");
          streamWriter.WriteLine("sucesso_salvar=Archivo guardado con éxito");
          streamWriter.WriteLine("------------------- INFORMATION ------------");
          streamWriter.WriteLine("iformacao_titulo=INFORMACIÓN");
          streamWriter.WriteLine("informacao_salvar=Por favor, introduzca la nación en el nombre del archivo, Ejemplo: (strClient_XX.lod / strClient_XX.lod) XX = Nación");
        }
        using (StreamWriter streamWriter = new StreamWriter("Config\\\\lang\\\\tr-TR.txt"))
        {
          streamWriter.WriteLine("############## Turkish - By:darklord ##############");
          streamWriter.WriteLine("------------------- Menus -------------------");
          streamWriter.WriteLine("menu_arquivo=Dosya");
          streamWriter.WriteLine("menu_abrir=Ac");
          streamWriter.WriteLine("menu_salvar=Kaydet");
          streamWriter.WriteLine("menu_sair=Cikis");
          streamWriter.WriteLine("------------------- Label -------------------");
          streamWriter.WriteLine("label_buscar=Ara");
          streamWriter.WriteLine("gb_geral=Genel");
          streamWriter.WriteLine("gb_editar=Düzenle");
          streamWriter.WriteLine("------------------- Buttons -----------------");
          streamWriter.WriteLine("btn_gravar=Kaydet");
          streamWriter.WriteLine("------------------- ERRORs -----------------");
          streamWriter.WriteLine("erro_titulo=HATA");
          streamWriter.WriteLine("erro_suporte=Dosyayı desteklemiyor");
          streamWriter.WriteLine("erro_nation=Lutfen lisan ID'sini girin, Ornek: (strClient_de.lod) XX = Nation");
          streamWriter.WriteLine("erro_salvar=Dosya kaydedilmedi");
          streamWriter.WriteLine("------------------- SUCCESS -----------------");
          streamWriter.WriteLine("sucesso_titulo=BASARILI");
          streamWriter.WriteLine("sucesso_gravar=Basariyla degistirildi");
          streamWriter.WriteLine("sucesso_salvar=Kaydedildi");
          streamWriter.WriteLine("------------------- INFORMATION ------------");
          streamWriter.WriteLine("iformacao_titulo=BiLGi");
          streamWriter.WriteLine("informacao_salvar=Lutfen lisan ID'sini girin, Ornek: (strClient_de.lod) XX = Nation");
        }
        this.checkDir();
      }
    }

    private void menu_abrir_Click(object sender, EventArgs e)
    {
      OpenFileDialog openFileDialog = new OpenFileDialog();
      openFileDialog.Title = "Abrir str*.dta";
      openFileDialog.InitialDirectory = "";
      openFileDialog.Filter = "str.lod|str*.lod|All|*.*";
      if (openFileDialog.ShowDialog() == DialogResult.Cancel)
        return;
      this.clean();
      this.Text = "Fenix LastChaos - Editando(" + openFileDialog.SafeFileName + ")";
      this.FileName = openFileDialog.SafeFileName;
      this.FileOpen = openFileDialog.FileName;
      this.readFile(2015);
    }

    private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.lbSucesso.Visible = false;
      if (this.listBox1.SelectedIndex == -1)
        return;
      int Item = Convert.ToInt32(this.listBox1.SelectedItem.ToString().Split('-')[0]);
      int index = Form1.StringList.FindIndex((Predicate<StringContainer>) (p => p.Index.Equals(Item)));
      this.textBox2.Text = Convert.ToString(Item);
      this.textBox3.Text = Encoding.GetEncoding(this.ISO).GetString(Form1.StringList[index].name);
      if (Form1.StringList[index].descr != null)
        this.textBox4.Text = Encoding.GetEncoding(this.ISO).GetString(Form1.StringList[index].descr);
      if (Form1.StringList[index].descr2 != null)
        this.textBox5.Text = Encoding.GetEncoding(this.ISO).GetString(Form1.StringList[index].descr2);
      if (Form1.StringList[index].descr3 == null)
        return;
      this.textBox6.Text = Encoding.GetEncoding(this.ISO).GetString(Form1.StringList[index].descr3);
    }

    private void btnGravar_Click(object sender, EventArgs e)
    {
      if (this.listBox1.SelectedIndex == -1)
        return;
      int Item = Convert.ToInt32(this.listBox1.SelectedItem.ToString().Split('-')[0]);
      int index = Form1.StringList.FindIndex((Predicate<StringContainer>) (p => p.Index.Equals(Item)));
      int nindex = Convert.ToInt32(this.textBox2.Text);
      if (Item != nindex)
      {
        if (Form1.StringList.FindIndex((Predicate<StringContainer>) (p => p.Index.Equals(nindex))) > -1)
        {
          int num = (int) MessageBox.Show("ID EXIST", "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Hand);
        }
        else
        {
          Form1.StringList[index].Index = Convert.ToInt32(this.textBox2.Text);
          Form1.StringList[index].name = Encoding.GetEncoding(this.ISO).GetBytes(this.textBox3.Text);
          Form1.StringList[index].descr = Encoding.GetEncoding(this.ISO).GetBytes(this.textBox4.Text);
          int selectedIndex = this.listBox1.SelectedIndex;
          this.makelist();
          this.listBox1.SelectedIndex = selectedIndex;
          this.lbSucesso.Visible = true;
        }
      }
      else
      {
        Form1.StringList[index].Index = Convert.ToInt32(this.textBox2.Text);
        Form1.StringList[index].name = Encoding.GetEncoding(this.ISO).GetBytes(this.textBox3.Text);
        Form1.StringList[index].descr = Encoding.GetEncoding(this.ISO).GetBytes(this.textBox4.Text);
        int selectedIndex = this.listBox1.SelectedIndex;
        this.makelist();
        this.listBox1.SelectedIndex = selectedIndex;
        this.lbSucesso.Visible = true;
      }
    }

    private void menu_salvar_Click(object sender, EventArgs e)
    {
      SaveFileDialog saveFileDialog = new SaveFileDialog();
      saveFileDialog.Filter = "All|*.*";
      saveFileDialog.FileName = this.FileName;
      saveFileDialog.Title = "Salvar str.dta";
      int num1 = (int) MessageBox.Show(this.INFORMACAO_SALVAR, this.INFORMACAO_TITULO, MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
      if (saveFileDialog.ShowDialog() != DialogResult.OK)
        return;
      BinaryWriter binaryWriter = new BinaryWriter((Stream) new FileStream(saveFileDialog.FileName, FileMode.Create));
      List<StringContainer> list = Form1.StringList.OrderBy<StringContainer, int>((Func<StringContainer, int>) (o => o.Index)).ToList<StringContainer>();
      if (this.nation.Length == 2)
      {
        binaryWriter.Write(Form1.StringList[list.Count<StringContainer>() - 1].Index);
        binaryWriter.Write(Form1.StringList[list.Count<StringContainer>() - 1].Index);
        if (this.FileName == "strRareOption_" + this.nation + ".lod")
        {
          binaryWriter.Write(this.lastid3);
          binaryWriter.Write(this.lastid4);
          binaryWriter.Write(this.lastid5);
          binaryWriter.Write(this.lastid6);
        }
        for (int index = 0; index <= list.Count<StringContainer>() - 1; ++index)
        {
          binaryWriter.Write(list[index].Index);
          binaryWriter.Write(list[index].name.Length);
          binaryWriter.Write(list[index].name);
          Encoding.GetEncoding(this.ISO).GetString(list[index].name);
          if (this.FileName == "strSkill_" + this.nation + ".lod" || this.FileName == "strSSkill_" + this.nation + ".lod" || this.FileName == "strNPCShop_" + this.nation + ".lod" || this.FileName == "strItemCollection_" + this.nation + ".lod" || this.FileName == "strItem_" + this.nation + ".lod" || this.FileName == "strAction_" + this.nation + ".lod" || this.FileName == "strPassiveSystem_" + this.nation + ".lod")
          {
            binaryWriter.Write(list[index].descr.Length);
            binaryWriter.Write(list[index].descr);
          }
          if (this.FileName == "strSkill_" + this.nation + ".lod" || this.FileName == "strNpcName_" + this.nation + ".lod" || this.FileName == "strNPCHelp_" + this.nation + ".lod" || this.FileName == "strHelp_" + this.nation + ".lod")
          {
            if (Encoding.GetEncoding(this.ISO).GetString(Form1.StringList[index].descr2) != "")
            {
              binaryWriter.Write(list[index].descr2.Length);
              binaryWriter.Write(list[index].descr2);
            }
            else
              binaryWriter.Write(0);
          }
          if (this.FileName == "strQuest_" + this.nation + ".lod")
          {
            binaryWriter.Write(list[index].descr2.Length);
            binaryWriter.Write(list[index].descr2);
            binaryWriter.Write(list[index].descr3.Length);
            binaryWriter.Write(list[index].descr3);
          }
        }
        binaryWriter.Close();
      }
      else
      {
        int num2 = (int) MessageBox.Show(this.ERROR_NATION, this.ERROR_TITULO + " - 001", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      int num3 = (int) MessageBox.Show(this.SUCESSO_SALVAR, this.SUCESSO_TITULO, MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
    }

    private void cb_idioma_SelectedIndexChanged_1(object sender, EventArgs e)
    {
      StreamReader streamReader;
      if (this.cb_idioma.Text == "brz")
      {
        this.ISO = "windows-1251";
        if (this.FileOpen != null)
          this.makelist();
        streamReader = new StreamReader("Config\\\\lang\\\\" + this.cb_idioma.Text + ".txt");
      }
      else if (this.cb_idioma.Text == "tr-TR")
      {
        this.ISO = "Windows-1254";
        if (this.FileOpen != null)
          this.makelist();
        streamReader = new StreamReader("Config\\\\lang\\\\" + this.cb_idioma.Text + ".txt");
      }
      else if (this.cb_idioma.Text == "thai")
      {
        this.ISO = "windows-874";
        if (this.FileOpen != null)
          this.makelist();
        streamReader = new StreamReader("Config\\\\lang\\\\" + this.cb_idioma.Text + ".txt");
      }
      else if (this.cb_idioma.Text == "pld")
      {
        this.ISO = "Windows-1250";
        if (this.FileOpen != null)
          this.makelist();
        streamReader = new StreamReader("Config\\\\lang\\\\" + this.cb_idioma.Text + ".txt");
      }
      else if (this.cb_idioma.Text == "ger")
      {
        this.ISO = "Windows-1252";
        if (this.FileOpen != null)
          this.makelist();
        streamReader = new StreamReader("Config\\\\lang\\\\" + this.cb_idioma.Text + ".txt");
      }
      else if (this.cb_idioma.Text == "rus")
      {
        this.ISO = "Windows-1251";
        if (this.FileOpen != null)
          this.makelist();
        streamReader = new StreamReader("Config\\\\lang\\\\" + this.cb_idioma.Text + ".txt");
      }
      else
      {
        this.ISO = "ISO-8859-1";
        if (this.FileOpen != null)
          this.makelist();
        streamReader = new StreamReader("Config\\\\lang\\\\" + this.cb_idioma.Text + ".txt", Encoding.GetEncoding(this.ISO), true);
      }
      string str;
      while ((str = streamReader.ReadLine()) != null)
      {
        string[] strArray = str.Split('=');
        if (strArray[0] == "menu_arquivo")
          this.menu_arquivo.Text = strArray[1];
        if (strArray[0] == "menu_abrir")
          this.menu_abrir.Text = strArray[1];
        if (strArray[0] == "menu_salvar")
          this.menu_salvar.Text = strArray[1];
        if (strArray[0] == "menu_sair")
          this.menu_sair.Text = strArray[1];
        if (strArray[0] == "label_buscar")
          this.lbBuscar.Text = strArray[1];
        if (strArray[0] == "gb_geral")
          this.gbGeral.Text = strArray[1];
        if (strArray[0] == "gb_editar")
          this.gbEditar.Text = strArray[1];
        if (strArray[0] == "btn_gravar")
          this.btnGravar.Text = strArray[1];
        if (strArray[0] == "erro_titulo")
          this.ERROR_TITULO = strArray[1];
        if (strArray[0] == "erro_suporte")
          this.ERROR_SUPORTE = strArray[1];
        if (strArray[0] == "erro_nation")
          this.ERROR_NATION = strArray[1];
        if (strArray[0] == "erro_salvar")
          this.ERROR_SALVAR = strArray[1];
        if (strArray[0] == "sucesso_titulo")
          this.SUCESSO_TITULO = strArray[1];
        if (strArray[0] == "sucesso_gravar")
          this.lbSucesso.Text = strArray[1];
        if (strArray[0] == "sucesso_salvar")
          this.SUCESSO_SALVAR = strArray[1];
        if (strArray[0] == "iformacao_titulo")
          this.INFORMACAO_TITULO = strArray[1];
        if (strArray[0] == "informacao_salvar")
          this.INFORMACAO_SALVAR = strArray[1];
      }
    }

    private void menu_sair_Click(object sender, EventArgs e) => Application.Exit();

    private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
    {
      Process.Start("");
    }

    private void button1_Click(object sender, EventArgs e) => this.Buscar();

    private void Buscar()
    {
      this.listBox1.Items.Clear();
      int num = Form1.StringList.Count<StringContainer>();
      for (int index1 = 0; index1 < num; ++index1)
      {
        int index2 = Form1.StringList[index1].Index;
        if ((index2.ToString() + " - " + Encoding.GetEncoding(this.ISO).GetString(Form1.StringList[index1].name)).ToLower().Contains(this.textBox1.Text.ToLower()))
          this.listBox1.Items.Add((object) (index2.ToString() + " - " + Encoding.GetEncoding(this.ISO).GetString(Form1.StringList[index1].name)));
      }
    }

    private void textBox1_KeyDown(object sender, KeyEventArgs e)
    {
      if (e.KeyCode != Keys.Return)
        return;
      this.Buscar();
    }

    private void updateThaiEng()
    {
      MySqlConnection connection = new MySqlConnection(Form1.strProvider);
      this.progressBar1.Minimum = 0;
      this.progressBar1.Maximum = this.listBox1.Items.Count - 1;
      this.FileName.Split('_');
      try
      {
        for (int index = 0; index < this.listBox1.Items.Count - 1; ++index)
        {
          string cmdText;
          if (this.FileName == "strAction_" + this.nation + ".lod")
            cmdText = "UPDATE t_action SET a_name_" + this.thaieng + " = @name, a_client_description_" + this.thaieng + " = @description, WHERE a_index = @index;";
          else if (this.FileName == "strAffinity_" + this.nation + ".lod")
            cmdText = "UPDATE t_affinity SET a_name_" + this.thaieng + " = @name WHERE a_index = @index;";
          else if (this.FileName == "strClient_" + this.nation + ".lod")
            cmdText = "UPDATE t_string SET a_string_" + this.thaieng + " = @name WHERE a_index = @index;";
          else if (this.FileName == "strCombo_" + this.nation + ".lod")
            cmdText = "UPDATE t_missioncase SET a_name = @name, a_name_usa = @name, a_name_brz = @name WHERE a_index = @index;";
          else if (this.FileName == "strItem_" + this.nation + ".lod")
            cmdText = "UPDATE t_item SET a_name_" + this.thaieng + " = @name, a_descr_" + this.thaieng + " = @description WHERE a_index = @index;";
          else if (this.FileName == "strItemCollection_" + this.nation + ".lod")
            cmdText = "UPDATE t_item_collection SET a_theme_string_usa = @name, a_desc_string_" + this.thaieng + " = @description WHERE a_theme = @index;";
          else if (this.FileName == "strNpcName_" + this.nation + ".lod")
            cmdText = "UPDATE t_npc SET a_name_" + this.thaieng + " = @name, a_descr_" + this.thaieng + " = @description WHERE a_index = @index;";
          else if (this.FileName == "strNPCShop_" + this.nation + ".lod")
            cmdText = "UPDATE t_shop SET a_name_" + this.thaieng + " = @name WHERE a_keeper_idx = @index;";
          else if (this.FileName == "strSetItem_" + this.nation + ".lod")
            cmdText = "UPDATE t_set_item SET a_set_name_" + this.thaieng + " = @name WHERE a_set_idx = @index;";
          else if (this.FileName == "strOption_" + this.nation + ".lod")
            cmdText = "UPDATE t_option SET a_name_" + this.thaieng + " = @name WHERE a_index = @index;";
          else if (this.FileName == "strQuest_" + this.nation + ".lod")
            cmdText = "UPDATE t_quest SET a_name_" + this.thaieng + " = @name, a_desc_" + this.thaieng + " = @description, a_desc2_" + this.thaieng + " = @desc2, a_desc3_" + this.thaieng + " = @desc3 WHERE a_index = @index;";
          else if (this.FileName == "strRareOption_" + this.nation + ".lod")
            cmdText = "UPDATE t_rareoption SET a_name_" + this.thaieng + " = @name WHERE a_index = @index;";
          else if (this.FileName == "strPassiveSystem_" + this.nation + ".lod")
            cmdText = "UPDATE t_passive_system SET a_name_" + this.thaieng + " = @name, a_client_description_" + this.thaieng + " = @description, WHERE a_index = @index;";
          else if (this.FileName == "strSkill_" + this.nation + ".lod")
          {
            cmdText = "UPDATE t_skill SET a_name_" + this.thaieng + " = @name, a_client_description_" + this.thaieng + " = @description, a_client_tooltip_" + this.thaieng + " = @tooltip WHERE a_index = @index;";
          }
          else
          {
            if (!(this.FileName == "strSSkill_" + this.nation + ".lod"))
            {
              int num = (int) MessageBox.Show("File not Supported", "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Hand);
              return;
            }
            cmdText = "UPDATE t_special_skill SET a_name = @name, a_name_usa = @name, a_name_brz = @name, a_desc = @description, a_desc_usa = @description, a_desc_brz = @description WHERE a_index = @index;";
          }
          MySqlCommand mySqlCommand = new MySqlCommand(cmdText, connection);
					mySqlCommand.Parameters.AddWithValue("@name", Form1.StringList[index].name);
					mySqlCommand.Parameters.AddWithValue("@index", Form1.StringList[index].Index);

					if (this.FileName == "strSkill_" + this.nation + ".lod" ||
						this.FileName == "strItem_" + this.nation + ".lod" ||
						this.FileName == "strNpcName_" + this.nation + ".lod" ||
						this.FileName == "strAction_" + this.nation + ".lod" ||
						this.FileName == "strPassiveSystem_" + this.nation + ".lod" ||
						this.FileName == "strItemCollection_" + this.nation + ".lod" ||
						this.FileName == "strSSkill_" + this.nation + ".lod" ||
						this.FileName == "strQuest_" + this.nation + ".lod")
					{
						mySqlCommand.Parameters.AddWithValue("@description", Form1.StringList[index].descr);
					}

					if (this.FileName == "strSkill_" + this.nation + ".lod")
					{
						mySqlCommand.Parameters.AddWithValue("@tooltip", Form1.StringList[index].descr2);
					}

					if (this.FileName == "strQuest_" + this.nation + ".lod")
					{
						mySqlCommand.Parameters.AddWithValue("@desc2", Form1.StringList[index].descr2);
						mySqlCommand.Parameters.AddWithValue("@desc3", Form1.StringList[index].descr3);
					}

					connection.Open();
          mySqlCommand.ExecuteNonQuery();
          connection.Close();
          this.progressBar1.Value = index;
        }
        int num1 = (int) MessageBox.Show("Done");
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message);
      }
    }

    private void button1_Click_1(object sender, EventArgs e)
    {
      if (this.cb_idioma.Text == "thai")
      {
        MySqlConnection connection = new MySqlConnection(Form1.strProvider);
        this.progressBar1.Minimum = 0;
        this.progressBar1.Maximum = this.listBox1.Items.Count - 1;
        this.FileName.Split('_');
        try
        {
          for (int index = 0; index < this.listBox1.Items.Count - 1; ++index)
          {
            string cmdText;
            if (this.FileName == "strAction_" + this.nation + ".lod")
              cmdText = "UPDATE t_action SET a_name_" + this.cb_idioma.Text + " = @name, a_client_description_" + this.cb_idioma.Text + " = @description, WHERE a_index = @index;";
            else if (this.FileName == "strAffinity_" + this.nation + ".lod")
              cmdText = "UPDATE t_affinity SET a_name_" + this.cb_idioma.Text + " = @name WHERE a_index = @index;";
            else if (this.FileName == "strClient_" + this.nation + ".lod")
              cmdText = "UPDATE t_string SET a_string_" + this.cb_idioma.Text + " = @name WHERE a_index = @index;";
            else if (this.FileName == "strCombo_" + this.nation + ".lod")
              cmdText = "UPDATE t_missioncase SET a_name = @name, a_name_usa = @name, a_name_brz = @name WHERE a_index = @index;";
            else if (this.FileName == "strItem_" + this.nation + ".lod")
              cmdText = "UPDATE t_item SET a_name_" + this.cb_idioma.Text + " = @name, a_descr_" + this.cb_idioma.Text + " = @description WHERE a_index = @index;";
            else if (this.FileName == "strItemCollection_" + this.nation + ".lod")
              cmdText = "UPDATE t_item_collection SET a_theme_string_usa = @name, a_desc_string_" + this.cb_idioma.Text + " = @description WHERE a_theme = @index;";
            else if (this.FileName == "strNpcName_" + this.nation + ".lod")
              cmdText = "UPDATE t_npc SET a_name_" + this.cb_idioma.Text + " = @name, a_descr_" + this.cb_idioma.Text + " = @description WHERE a_index = @index;";
            else if (this.FileName == "strNPCShop_" + this.nation + ".lod")
              cmdText = "UPDATE t_shop SET a_name_" + this.cb_idioma.Text + " = @name WHERE a_keeper_idx = @index;";
            else if (this.FileName == "strSetItem_" + this.nation + ".lod")
              cmdText = "UPDATE t_set_item SET a_set_name_" + this.cb_idioma.Text + " = @name WHERE a_set_idx = @index;";
            else if (this.FileName == "strOption_" + this.nation + ".lod")
              cmdText = "UPDATE t_option SET a_name_" + this.cb_idioma.Text + " = @name WHERE a_index = @index;";
            else if (this.FileName == "strQuest_" + this.nation + ".lod")
              cmdText = "UPDATE t_quest SET a_name_" + this.cb_idioma.Text + " = @name, a_desc_" + this.cb_idioma.Text + " = @description, a_desc2_" + this.cb_idioma.Text + " = @desc2, a_desc3_" + this.cb_idioma.Text + " = @desc3 WHERE a_index = @index;";
            else if (this.FileName == "strRareOption_" + this.nation + ".lod")
              cmdText = "UPDATE t_rareoption SET a_name_" + this.cb_idioma.Text + " = @name WHERE a_index = @index;";
            else if (this.FileName == "strPassiveSystem_" + this.nation + ".lod")
              cmdText = "UPDATE t_passive_system SET a_name_" + this.cb_idioma.Text + " = @name, a_client_description_" + this.cb_idioma.Text + " = @description, WHERE a_index = @index;";
            else if (this.FileName == "strSkill_" + this.nation + ".lod")
            {
              cmdText = "UPDATE t_skill SET a_name_" + this.cb_idioma.Text + " = @name, a_client_description_" + this.cb_idioma.Text + " = @description, a_client_tooltip_" + this.cb_idioma.Text + " = @tooltip WHERE a_index = @index;";
            }
            else
            {
              if (!(this.FileName == "strSSkill_" + this.nation + ".lod"))
              {
                int num = (int) MessageBox.Show("File not Supported", "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Hand);
                return;
              }
              cmdText = "UPDATE t_special_skill SET a_name = @name, a_name_usa = @name, a_name_brz = @name, a_desc = @description, a_desc_usa = @description, a_desc_brz = @description WHERE a_index = @index;";
            }
            MySqlCommand mySqlCommand = new MySqlCommand(cmdText, connection);
						// Add string and index parameters
						mySqlCommand.Parameters.AddWithValue("@name", Form1.StringList[index].name);
						mySqlCommand.Parameters.AddWithValue("@index", Form1.StringList[index].Index);

						// Only add description for certain file types
						if (this.FileName == "strSkill_" + this.nation + ".lod" ||
							this.FileName == "strItem_" + this.nation + ".lod" ||
							this.FileName == "strNpcName_" + this.nation + ".lod" ||
							this.FileName == "strAction_" + this.nation + ".lod" ||
							this.FileName == "strPassiveSystem_" + this.nation + ".lod" ||
							this.FileName == "strItemCollection_" + this.nation + ".lod" ||
							this.FileName == "strSSkill_" + this.nation + ".lod" ||
							this.FileName == "strQuest_" + this.nation + ".lod")
						{
							mySqlCommand.Parameters.AddWithValue("@description", Form1.StringList[index].descr);
						}

						// Add tooltip for skills
						if (this.FileName == "strSkill_" + this.nation + ".lod")
						{
							mySqlCommand.Parameters.AddWithValue("@tooltip", Form1.StringList[index].descr2);
						}

						// Add extra descriptions for quests
						if (this.FileName == "strQuest_" + this.nation + ".lod")
						{
							mySqlCommand.Parameters.AddWithValue("@desc2", Form1.StringList[index].descr2);
							mySqlCommand.Parameters.AddWithValue("@desc3", Form1.StringList[index].descr3);
						}

						connection.Open();
            mySqlCommand.ExecuteNonQuery();
            connection.Close();
            this.progressBar1.Value = index;
          }
        }
        catch (Exception ex)
        {
        }
      }
      else
      {
        MySqlConnection connection = new MySqlConnection(Form1.strProvider);
        this.progressBar1.Minimum = 0;
        this.progressBar1.Maximum = this.listBox1.Items.Count - 1;
        this.FileName.Split('_');
        try
        {
          for (int index = 0; index < this.listBox1.Items.Count - 1; ++index)
          {
            string cmdText;
            if (this.FileName == "strAction_" + this.nation + ".lod")
              cmdText = "UPDATE t_action SET a_name_" + this.cb_idioma.Text + " = @name, a_client_description_" + this.cb_idioma.Text + " = @description, WHERE a_index = @index;";
            else if (this.FileName == "strAffinity_" + this.nation + ".lod")
              cmdText = "UPDATE t_affinity SET a_name_" + this.cb_idioma.Text + " = @name WHERE a_index = @index;";
            else if (this.FileName == "strClient_" + this.nation + ".lod")
              cmdText = "UPDATE t_string SET a_string_" + this.cb_idioma.Text + " = @name WHERE a_index = @index;";
            else if (this.FileName == "strCombo_" + this.nation + ".lod")
              cmdText = "UPDATE t_missioncase SET a_name = @name, a_name_usa = @name, a_name_brz = @name WHERE a_index = @index;";
            else if (this.FileName == "strItem_" + this.nation + ".lod")
              cmdText = "UPDATE t_item SET a_name_" + this.cb_idioma.Text + " = @name, a_descr_" + this.cb_idioma.Text + " = @description WHERE a_index = @index;";
            else if (this.FileName == "strItemCollection_" + this.nation + ".lod")
              cmdText = "UPDATE t_item_collection SET a_theme_string_usa = @name, a_desc_string_" + this.cb_idioma.Text + " = @description WHERE a_theme = @index;";
            else if (this.FileName == "strNpcName_" + this.nation + ".lod")
              cmdText = "UPDATE t_npc SET a_name_" + this.cb_idioma.Text + " = @name, a_descr_" + this.cb_idioma.Text + " = @description WHERE a_index = @index;";
            else if (this.FileName == "strNPCShop_" + this.nation + ".lod")
              cmdText = "UPDATE t_shop SET a_name_" + this.cb_idioma.Text + " = @name WHERE a_keeper_idx = @index;";
            else if (this.FileName == "strSetItem_" + this.nation + ".lod")
              cmdText = "UPDATE t_set_item SET a_set_name_" + this.cb_idioma.Text + " = @name WHERE a_set_idx = @index;";
            else if (this.FileName == "strOption_" + this.nation + ".lod")
              cmdText = "UPDATE t_option SET a_name_" + this.cb_idioma.Text + " = @name WHERE a_index = @index;";
            else if (this.FileName == "strQuest_" + this.nation + ".lod")
              cmdText = "UPDATE t_quest SET a_name_" + this.cb_idioma.Text + " = @name, a_desc_" + this.cb_idioma.Text + " = @description, a_desc2_" + this.cb_idioma.Text + " = @desc2, a_desc3_" + this.cb_idioma.Text + " = @desc3 WHERE a_index = @index;";
            else if (this.FileName == "strRareOption_" + this.nation + ".lod")
              cmdText = "UPDATE t_rareoption SET a_name_" + this.cb_idioma.Text + " = @name WHERE a_index = @index;";
            else if (this.FileName == "strPassiveSystem_" + this.nation + ".lod")
              cmdText = "UPDATE t_passive_system SET a_name_" + this.cb_idioma.Text + " = @name, a_client_description_" + this.cb_idioma.Text + " = @description, WHERE a_index = @index;";
            else if (this.FileName == "strSkill_" + this.nation + ".lod")
            {
              cmdText = "UPDATE t_skill SET a_name_" + this.cb_idioma.Text + " = @name, a_client_description_" + this.cb_idioma.Text + " = @description, a_client_tooltip_" + this.cb_idioma.Text + " = @tooltip WHERE a_index = @index;";
            }
            else
            {
              if (!(this.FileName == "strSSkill_" + this.nation + ".lod"))
              {
                int num = (int) MessageBox.Show("File not Supported", "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Hand);
                return;
              }
              cmdText = "UPDATE t_special_skill SET a_name = @name, a_name_usa = @name, a_name_brz = @name, a_desc = @description, a_desc_usa = @description, a_desc_brz = @description WHERE a_index = @index;";
            }
            MySqlCommand mySqlCommand = new MySqlCommand(cmdText, connection);
						// name and index parameters
						mySqlCommand.Parameters.AddWithValue("@name", Form1.StringList[index].name);
						mySqlCommand.Parameters.AddWithValue("@index", Form1.StringList[index].Index);

						// description for most string tables
						if (this.FileName == "strSkill_" + this.nation + ".lod" ||
							this.FileName == "strItem_" + this.nation + ".lod" ||
							this.FileName == "strNpcName_" + this.nation + ".lod" ||
							this.FileName == "strAction_" + this.nation + ".lod" ||
							this.FileName == "strPassiveSystem_" + this.nation + ".lod" ||
							this.FileName == "strItemCollection_" + this.nation + ".lod" ||
							this.FileName == "strSSkill_" + this.nation + ".lod" ||
							this.FileName == "strQuest_" + this.nation + ".lod")
						{
							mySqlCommand.Parameters.AddWithValue("@description", Form1.StringList[index].descr);
						}

						// tooltip for skills
						if (this.FileName == "strSkill_" + this.nation + ".lod")
						{
							mySqlCommand.Parameters.AddWithValue("@tooltip", Form1.StringList[index].descr2);
						}

						// extra descriptions for quests
						if (this.FileName == "strQuest_" + this.nation + ".lod")
						{
							mySqlCommand.Parameters.AddWithValue("@desc2", Form1.StringList[index].descr2);
							mySqlCommand.Parameters.AddWithValue("@desc3", Form1.StringList[index].descr3);
						}

						connection.Open();
            mySqlCommand.ExecuteNonQuery();
            connection.Close();
            this.progressBar1.Value = index;
          }
          int num1 = (int) MessageBox.Show("Done");
        }
        catch (Exception ex)
        {
          int num = (int) MessageBox.Show(ex.Message);
        }
      }
      this.updateThaiEng();
    }

    private void button2_Click(object sender, EventArgs e)
    {
      int num = Form1.StringList.Max<StringContainer>((Func<StringContainer, int>) (p => p.Index)) + 1;
      string s1 = "New String";
      string s2 = "";
      string s3 = "";
      StringContainer stringContainer = new StringContainer();
      stringContainer.Index = num;
      stringContainer.name = Encoding.GetEncoding(this.ISO).GetBytes(s1);
      stringContainer.descr = Encoding.GetEncoding(this.ISO).GetBytes(s2);
      if (this.FileName == "strSkill_" + this.nation + ".lod" || this.FileName == "strSSkill_" + this.nation + ".lod" || this.FileName == "strNPCShop_" + this.nation + ".lod" || this.FileName == "strItemCollection_" + this.nation + ".lod" || this.FileName == "strItem_" + this.nation + ".lod" || this.FileName == "strAction_" + this.nation + ".lod" || this.FileName == "strPassiveSystem_" + this.nation + ".lod")
        stringContainer.descr2 = Encoding.GetEncoding(this.ISO).GetBytes(s2);
      if (this.FileName == "strSkill_" + this.nation + ".lod" || this.FileName == "strNpcName_" + this.nation + ".lod" || this.FileName == "strNPCHelp_" + this.nation + ".lod" || this.FileName == "strHelp_" + this.nation + ".lod")
        stringContainer.descr2 = Encoding.GetEncoding(this.ISO).GetBytes(s3);
      Form1.StringList.Add(stringContainer);
      this.listBox1.Items.Add((object) (num.ToString() + " - " + s1));
      this.listBox1.SelectedIndex = this.listBox1.Items.Count - 1;
    }

    private void button3_Click(object sender, EventArgs e)
    {
      if (this.listBox1.SelectedIndex == -1)
        return;
      int Item = Convert.ToInt32(this.listBox1.SelectedItem.ToString().Split('-')[0]);
      int selectedIndex = this.listBox1.SelectedIndex;
      int index = Form1.StringList.FindIndex((Predicate<StringContainer>) (p => p.Index.Equals(Item)));
      if (index == -1)
        return;
      Form1.StringList.RemoveAt(index);
      this.listBox1.Items.RemoveAt(selectedIndex);
      if (selectedIndex > 0)
        this.listBox1.SelectedIndex = selectedIndex - 1;
      else
        this.listBox1.SelectedIndex = -1;
    }

    private void configToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (new ConfiMysql().ShowDialog() == DialogResult.OK)
        ;
    }

    private void btnConnect_Click(object sender, EventArgs e)
    {
      MySqlConnection mySqlConnection = new MySqlConnection(Form1.strProvider);
      try
      {
        mySqlConnection.Open();
        mySqlConnection.Close();
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message);
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
      this.menuStrip1 = new MenuStrip();
      this.menu_arquivo = new ToolStripMenuItem();
      this.menu_abrir = new ToolStripMenuItem();
      this.menu_salvar = new ToolStripMenuItem();
      this.menu_sair = new ToolStripMenuItem();
      this.textBox1 = new TextBox();
      this.listBox1 = new ListBox();
      this.gbGeral = new GroupBox();
      this.label3 = new Label();
      this.label2 = new Label();
      this.button3 = new Button();
      this.button2 = new Button();
      this.button1 = new Button();
      this.lbBuscar = new Button();
      this.gbEditar = new GroupBox();
      this.textBox7 = new TextBox();
      this.lbSucesso = new Label();
      this.btnGravar = new Button();
      this.textBox6 = new TextBox();
      this.textBox5 = new TextBox();
      this.textBox4 = new TextBox();
      this.textBox3 = new TextBox();
      this.label1 = new Label();
      this.textBox2 = new TextBox();
      this.lbDescr2 = new Label();
      this.lbDescr = new Label();
      this.lbNome = new Label();
      this.lbID = new Label();
      this.cb_idioma = new ComboBox();
      this.progressBar1 = new ProgressBar();
      this.menuStrip1.SuspendLayout();
      this.gbGeral.SuspendLayout();
      this.gbEditar.SuspendLayout();
      this.SuspendLayout();
      this.menuStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.menu_arquivo
      });
      this.menuStrip1.Location = new Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new Size(859, 24);
      this.menuStrip1.TabIndex = 1;
      this.menuStrip1.Text = "menuStrip1";
      this.menu_arquivo.DropDownItems.AddRange(new ToolStripItem[3]
      {
        (ToolStripItem) this.menu_abrir,
        (ToolStripItem) this.menu_salvar,
        (ToolStripItem) this.menu_sair
      });
      this.menu_arquivo.Name = "menu_arquivo";
      this.menu_arquivo.Size = new Size(37, 20);
      this.menu_arquivo.Text = "File";
      this.menu_abrir.Name = "menu_abrir";
      this.menu_abrir.Size = new Size(103, 22);
      this.menu_abrir.Text = "Open";
      this.menu_abrir.Click += new EventHandler(this.menu_abrir_Click);
      this.menu_salvar.Enabled = false;
      this.menu_salvar.Name = "menu_salvar";
      this.menu_salvar.Size = new Size(103, 22);
      this.menu_salvar.Text = "Save";
      this.menu_salvar.Click += new EventHandler(this.menu_salvar_Click);
      this.menu_sair.Name = "menu_sair";
      this.menu_sair.Size = new Size(103, 22);
      this.menu_sair.Text = "Exit";
      this.menu_sair.Click += new EventHandler(this.menu_sair_Click);
      this.textBox1.Location = new Point(9, 32);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(228, 20);
      this.textBox1.TabIndex = 5;
      this.textBox1.KeyDown += new KeyEventHandler(this.textBox1_KeyDown);
      this.listBox1.FormattingEnabled = true;
      this.listBox1.Location = new Point(9, 58);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new Size(308, 355);
      this.listBox1.TabIndex = 7;
      this.listBox1.SelectedIndexChanged += new EventHandler(this.listBox1_SelectedIndexChanged);
      this.gbGeral.Controls.Add((Control) this.label3);
      this.gbGeral.Controls.Add((Control) this.label2);
      this.gbGeral.Controls.Add((Control) this.button3);
      this.gbGeral.Controls.Add((Control) this.button2);
      this.gbGeral.Controls.Add((Control) this.button1);
      this.gbGeral.Controls.Add((Control) this.lbBuscar);
      this.gbGeral.Controls.Add((Control) this.gbEditar);
      this.gbGeral.Controls.Add((Control) this.listBox1);
      this.gbGeral.Controls.Add((Control) this.textBox1);
      this.gbGeral.Enabled = false;
      this.gbGeral.Location = new Point(12, 27);
      this.gbGeral.Name = "gbGeral";
      this.gbGeral.Size = new Size(833, 452);
      this.gbGeral.TabIndex = 7;
      this.gbGeral.TabStop = false;
      this.gbGeral.Text = "Gereral";
      this.label3.AutoSize = true;
      this.label3.Location = new Point(500, 19);
      this.label3.Name = "label3";
      this.label3.Size = new Size(0, 13);
      this.label3.TabIndex = 23;
      this.label2.AutoSize = true;
      this.label2.Location = new Point(425, 19);
      this.label2.Name = "label2";
      this.label2.Size = new Size(79, 13);
      this.label2.TabIndex = 22;
      this.label2.Text = "You Nation is : ";
      this.button3.Location = new Point(170, 419);
      this.button3.Name = "button3";
      this.button3.Size = new Size(147, 23);
      this.button3.TabIndex = 21;
      this.button3.Text = "Delete";
      this.button3.UseVisualStyleBackColor = true;
      this.button3.Click += new EventHandler(this.button3_Click);
      this.button2.Location = new Point(9, 419);
      this.button2.Name = "button2";
      this.button2.Size = new Size(155, 23);
      this.button2.TabIndex = 21;
      this.button2.Text = "Add";
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.button1.Location = new Point(709, 419);
      this.button1.Name = "button1";
      this.button1.Size = new Size(118, 23);
      this.button1.TabIndex = 14;
      this.button1.Text = "Update DB";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click_1);
      this.lbBuscar.Location = new Point(243, 30);
      this.lbBuscar.Name = "lbBuscar";
      this.lbBuscar.Size = new Size(74, 23);
      this.lbBuscar.TabIndex = 6;
      this.lbBuscar.Text = "Search";
      this.lbBuscar.UseVisualStyleBackColor = true;
      this.lbBuscar.Click += new EventHandler(this.button1_Click);
      this.gbEditar.Controls.Add((Control) this.textBox7);
      this.gbEditar.Controls.Add((Control) this.lbSucesso);
      this.gbEditar.Controls.Add((Control) this.btnGravar);
      this.gbEditar.Controls.Add((Control) this.textBox6);
      this.gbEditar.Controls.Add((Control) this.textBox5);
      this.gbEditar.Controls.Add((Control) this.textBox4);
      this.gbEditar.Controls.Add((Control) this.textBox3);
      this.gbEditar.Controls.Add((Control) this.label1);
      this.gbEditar.Controls.Add((Control) this.textBox2);
      this.gbEditar.Controls.Add((Control) this.lbDescr2);
      this.gbEditar.Controls.Add((Control) this.lbDescr);
      this.gbEditar.Controls.Add((Control) this.lbNome);
      this.gbEditar.Controls.Add((Control) this.lbID);
      this.gbEditar.Location = new Point(335, 35);
      this.gbEditar.Name = "gbEditar";
      this.gbEditar.Size = new Size(483, 365);
      this.gbEditar.TabIndex = 7;
      this.gbEditar.TabStop = false;
      this.gbEditar.Text = "Edit";
      this.textBox7.Location = new Point(178, 46);
      this.textBox7.Name = "textBox7";
      this.textBox7.Size = new Size(69, 20);
      this.textBox7.TabIndex = 14;
      this.lbSucesso.AutoSize = true;
      this.lbSucesso.ForeColor = Color.ForestGreen;
      this.lbSucesso.Location = new Point(165, 336);
      this.lbSucesso.Name = "lbSucesso";
      this.lbSucesso.Size = new Size(76, 13);
      this.lbSucesso.TabIndex = 13;
      this.lbSucesso.Text = "Save Success";
      this.lbSucesso.Visible = false;
      this.btnGravar.Location = new Point(351, 331);
      this.btnGravar.Name = "btnGravar";
      this.btnGravar.Size = new Size(118, 23);
      this.btnGravar.TabIndex = 12;
      this.btnGravar.Text = "Save";
      this.btnGravar.UseVisualStyleBackColor = true;
      this.btnGravar.Click += new EventHandler(this.btnGravar_Click);
      this.textBox6.Enabled = false;
      this.textBox6.Location = new Point(93, 242);
      this.textBox6.Multiline = true;
      this.textBox6.Name = "textBox6";
      this.textBox6.Size = new Size(370, 70);
      this.textBox6.TabIndex = 11;
      this.textBox5.Location = new Point(93, 166);
      this.textBox5.Multiline = true;
      this.textBox5.Name = "textBox5";
      this.textBox5.Size = new Size(370, 70);
      this.textBox5.TabIndex = 11;
      this.textBox4.Location = new Point(93, 98);
      this.textBox4.Multiline = true;
      this.textBox4.Name = "textBox4";
      this.textBox4.Size = new Size(370, 62);
      this.textBox4.TabIndex = 10;
      this.textBox3.Location = new Point(93, 72);
      this.textBox3.Name = "textBox3";
      this.textBox3.Size = new Size(262, 20);
      this.textBox3.TabIndex = 9;
      this.label1.AutoSize = true;
      this.label1.Location = new Point(39, 245);
      this.label1.Name = "label1";
      this.label1.Size = new Size(41, 13);
      this.label1.TabIndex = 3;
      this.label1.Text = "Descr3";
      this.textBox2.Location = new Point(93, 46);
      this.textBox2.Name = "textBox2";
      this.textBox2.Size = new Size(69, 20);
      this.textBox2.TabIndex = 8;
      this.lbDescr2.AutoSize = true;
      this.lbDescr2.Location = new Point(39, 169);
      this.lbDescr2.Name = "lbDescr2";
      this.lbDescr2.Size = new Size(41, 13);
      this.lbDescr2.TabIndex = 3;
      this.lbDescr2.Text = "Descr2";
      this.lbDescr.AutoSize = true;
      this.lbDescr.Location = new Point(46, 101);
      this.lbDescr.Name = "lbDescr";
      this.lbDescr.Size = new Size(35, 13);
      this.lbDescr.TabIndex = 2;
      this.lbDescr.Text = "Descr";
      this.lbNome.AutoSize = true;
      this.lbNome.Location = new Point(46, 75);
      this.lbNome.Name = "lbNome";
      this.lbNome.Size = new Size(34, 13);
      this.lbNome.TabIndex = 1;
      this.lbNome.Text = "String";
      this.lbID.AutoSize = true;
      this.lbID.Location = new Point(63, 49);
      this.lbID.Name = "lbID";
      this.lbID.Size = new Size(18, 13);
      this.lbID.TabIndex = 0;
      this.lbID.Text = "ID";
      this.cb_idioma.FormattingEnabled = true;
      this.cb_idioma.Location = new Point(724, 3);
      this.cb_idioma.Name = "cb_idioma";
      this.cb_idioma.Size = new Size(121, 21);
      this.cb_idioma.TabIndex = 8;
      this.cb_idioma.SelectedIndexChanged += new EventHandler(this.cb_idioma_SelectedIndexChanged_1);
      this.progressBar1.Location = new Point(12, 485);
      this.progressBar1.Name = "progressBar1";
      this.progressBar1.Size = new Size(833, 11);
      this.progressBar1.TabIndex = 10;
      this.ClientSize = new Size(859, 498);
      this.Controls.Add((Control) this.progressBar1);
      this.Controls.Add((Control) this.cb_idioma);
      this.Controls.Add((Control) this.gbGeral);
      this.Controls.Add((Control) this.menuStrip1);
      this.MainMenuStrip = this.menuStrip1;
      this.MaximizeBox = false;
      this.Name = nameof (Form1);
      this.StartPosition = FormStartPosition.CenterScreen;
      this.Text = "LastChaos - String Editor";
      this.Load += new EventHandler(this.Form1_Load);
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.gbGeral.ResumeLayout(false);
      this.gbGeral.PerformLayout();
      this.gbEditar.ResumeLayout(false);
      this.gbEditar.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
