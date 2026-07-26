// Decompiled with JetBrains decompiler
// Type: ExchangeExport.ExchangeExport_cHaR
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using LcDevPack_TeamDamonA;
using LcDevPack_TeamDamonA.Tools;
using LcDevPack_TeamDamonA.Tools.MemoryWorker.ExChange;
using MySqlConnector;
using SlimDX;
using SlimDX.Direct3D9;
using System;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Windows.Forms;

#nullable disable
namespace ExchangeExport
{
  public class ExchangeExport_cHaR : Form
  {
    public static Connection connection = new Connection();
    private string Host = MoonstoneEditor.connection.Settings.SqlHost;
    private string User = MoonstoneEditor.connection.Settings.SqlUser;
    private string Password = MoonstoneEditor.connection.Settings.SqlPassword;
    private string Database = MoonstoneEditor.connection.Settings.SqlDatabase;
    public static System.Collections.Generic.List<tbl_exchange> ExChangeList = new System.Collections.Generic.List<tbl_exchange>();
    private int action_state = 0;
    private DataTable dt_npc;
    private DataTable dt_item;
    private DataTable dt_item_exchange;
    private ImageList img_item;
    private ImageList img_npc;
    public Direct3D _Direct3D;
    public Device _Device;
    public float _Zoom;
    public float _LeftRight;
    public float _Rotation;
    public System.Collections.Generic.List<tMesh> _Models;
    public float _UpDown = -1f;
    private DatabaseHandle databaseHandle = new DatabaseHandle();
    private System.Collections.Generic.List<ExchangeExport_cHaR.ticon> List = new System.Collections.Generic.List<ExchangeExport_cHaR.ticon>();
    private IContainer components = (IContainer) null;
    private GroupBox groupBox4;
    private GroupBox groupBox3;
    private GroupBox gb_npc;
    private GroupBox groupBox1;
    private Button button2;
    private TextBox tb_reward_name;
    private TextBox tb_reward_id;
    private PictureBox pictureBox2;
    private Label label2;
    private Label label1;
    private Button bt_npc;
    private TextBox tx_npc_name;
    private TextBox tx_npc_id;
    private PictureBox pc_npc;
    private Label label3;
    private Label label4;
    private Label label5;
    private TextBox tb_reward_qty;
    private TextBox textBox18;
    private Label label18;
    private Label label19;
    private Label label20;
    private Button button7;
    private TextBox textBox19;
    private TextBox r_t_id5;
    private PictureBox pictureBox7;
    private TextBox textBox15;
    private Label label15;
    private Label label16;
    private Label label17;
    private Button button6;
    private TextBox textBox16;
    private TextBox r_t_id4;
    private PictureBox pictureBox6;
    private TextBox textBox12;
    private Label label12;
    private Label label13;
    private Label label14;
    private Button button5;
    private TextBox textBox13;
    private TextBox r_t_id3;
    private PictureBox pictureBox5;
    private TextBox textBox9;
    private Label label9;
    private Label label10;
    private Label label11;
    private Button button4;
    private TextBox textBox10;
    private TextBox r_t_id2;
    private PictureBox pictureBox4;
    private TextBox textBox6;
    private Label label6;
    private Label label7;
    private Label label8;
    private Button button3;
    private TextBox textBox7;
    private TextBox r_t_id1;
    private PictureBox pictureBox3;
    private Button button9;
    private Button button8;
    private GroupBox groupBox7;
    private Button button11;
    private DataGridView dgItems;
    private Panel panel3DView;
    private Button button12;
    private GroupBox groupBox2;
    private TextBox t_exchange_id;
    private Button bt_refresh;
    private CheckBox checkBox1;
    private CheckBox checkBox5;
    private CheckBox checkBox4;
    private CheckBox checkBox3;
    private CheckBox checkBox2;
    private Label label21;
    private Label label23;
    private Label label22;
    private TextBox a_desc;
    private TextBox a_name;
    private GroupBox groupBox5;
    private Button button1;
    private DataGridViewImageColumn Column7;
    private DataGridViewTextBoxColumn ID;
    private DataGridViewTextBoxColumn ItemName;
    private DataGridViewTextBoxColumn NpcName;

    public ExchangeExport_cHaR() => this.InitializeComponent();

    private void Form1_Load(object sender, EventArgs e)
    {
      this.MaximumSize = this.Size;
      this.MinimumSize = this.Size;
      this.button9.Enabled = false;
      this.button12.Enabled = false;
      this.button1.Enabled = false;
      this.InitializeDevice();
      this.LoadDG();
    }

    private void LoadDG()
    {
      Stopwatch stopwatch = new Stopwatch();
      stopwatch.Start();
      this.dgItems.Rows.Clear();
      string str1 = "select a_index, a_npc_index, result_itemIndex, result_itemCount, source_itemIndex0, source_itemCount0, source_itemIndex1, source_itemCount1, source_itemIndex2, source_itemCount2, source_itemIndex3, source_itemCount3, source_itemIndex4, source_itemCount4      from t_item_exchange order by a_index";
      MySqlConnection mySqlConnection = new MySqlConnection("datasource=" + this.Host + ";Port=3306;User ID="  + this.User + ";Password=" + this.Password + ";Database=" + this.Database + ";Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;");
      MySqlCommand command = mySqlConnection.CreateCommand();
      command.CommandText = str1;
      mySqlConnection.Open();
      MySqlDataReader mySqlDataReader = command.ExecuteReader();
      while (mySqlDataReader.Read())
      {
        ExchangeExport_cHaR.ExChangeList.Add(new tbl_exchange()
        {
          index = Convert.ToInt32(mySqlDataReader.GetValue(0).ToString()),
          npcidx = Convert.ToInt32(mySqlDataReader.GetValue(1).ToString()),
          result_itemIndex = Convert.ToInt32(mySqlDataReader.GetValue(2).ToString()),
          result_itemCount = Convert.ToInt32(mySqlDataReader.GetValue(3).ToString()),
          source_itemIndex0 = Convert.ToInt32(mySqlDataReader.GetValue(4).ToString()),
          source_itemCount0 = Convert.ToInt32(mySqlDataReader.GetValue(5).ToString()),
          source_itemIndex1 = Convert.ToInt32(mySqlDataReader.GetValue(6).ToString()),
          source_itemCount1 = Convert.ToInt32(mySqlDataReader.GetValue(7).ToString()),
          source_itemIndex2 = Convert.ToInt32(mySqlDataReader.GetValue(8).ToString()),
          source_itemCount2 = Convert.ToInt32(mySqlDataReader.GetValue(9).ToString()),
          source_itemIndex3 = Convert.ToInt32(mySqlDataReader.GetValue(10).ToString()),
          source_itemCount3 = Convert.ToInt32(mySqlDataReader.GetValue(11).ToString()),
          source_item_Index4 = Convert.ToInt32(mySqlDataReader.GetValue(12).ToString()),
          source_itemCount4 = Convert.ToInt32(mySqlDataReader.GetValue(13).ToString())
        });
        string str2 = mySqlDataReader.GetValue(0).ToString();
        string s1 = mySqlDataReader.GetValue(1).ToString();
        string s2 = mySqlDataReader.GetValue(2).ToString();
        this.dgItems.Rows.Add((object) new Bitmap((Image) this.databaseHandle.IconFast(int.Parse(s2)), 20, 20), (object) str2, (object) this.databaseHandle.ItemNameFast(int.Parse(s2)), (object) this.databaseHandle.MobNameFast(int.Parse(s1)));
      }
      mySqlConnection.Close();
      stopwatch.Stop();
      TimeSpan elapsed = stopwatch.Elapsed;
      string.Format("{0:00}:{1:00}:{2:00}.{3:00}", (object) elapsed.Hours, (object) elapsed.Minutes, (object) elapsed.Seconds, (object) (elapsed.Milliseconds / 10));
    }

    private void item_src_init(PictureBox pb, TextBox id, TextBox name_src, TextBox qty)
    {
      pb.Image = (Image) null;
      pb.SizeMode = PictureBoxSizeMode.StretchImage;
    }

    private void item_src_load(PictureBox pb, TextBox id, TextBox name_src, TextBox qty)
    {
    }

    private void language_selection_CheckedChanged(object sender, EventArgs e)
    {
      int num = ((Control) sender).Name == "rd_usa" ? 1 : 0;
      Label label1 = this.label1;
      Label label4 = this.label4;
      Label label8 = this.label8;
      Label label11 = this.label11;
      Label label14 = this.label14;
      Label label17 = this.label17;
      string str1;
      this.label20.Text = str1 = num == 1 ? "ID :" : "รหัส :";
      string str2;
      string str3 = str2 = str1;
      label17.Text = str2;
      string str4;
      string str5 = str4 = str3;
      label14.Text = str4;
      string str6;
      string str7 = str6 = str5;
      label11.Text = str6;
      string str8;
      string str9 = str8 = str7;
      label8.Text = str8;
      string str10;
      string str11 = str10 = str9;
      label4.Text = str10;
      string str12 = str11;
      label1.Text = str12;
      this.label2.Text = num == 1 ? "Name :" : "ชื่อ npc :";
      Label label3 = this.label3;
      Label label7 = this.label7;
      Label label10 = this.label10;
      Label label13 = this.label13;
      Label label16 = this.label16;
      string str13;
      this.label19.Text = str13 = num == 1 ? "Name :" : "ชื่อไอเทม :";
      string str14;
      string str15 = str14 = str13;
      label16.Text = str14;
      string str16;
      string str17 = str16 = str15;
      label13.Text = str16;
      string str18;
      string str19 = str18 = str17;
      label10.Text = str18;
      string str20;
      string str21 = str20 = str19;
      label7.Text = str20;
      string str22 = str21;
      label3.Text = str22;
    }

    private void button2_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.tb_reward_id.Text = Convert.ToString(itemPicker.ItemIndex);
    }

    private void tb_reward_id_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox2.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.tb_reward_id.Text.Trim()));
      this.tb_reward_name.Text = this.databaseHandle.ItemNameFast(Convert.ToInt32(this.tb_reward_id.Text));
    }

    private void button3_Click(object sender, EventArgs e)
    {
      this.r_t_id1.Text = "0";
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.r_t_id1.Text = Convert.ToString(itemPicker.ItemIndex);
    }

    private void textBox8_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox3.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.r_t_id1.Text.Trim()));
      this.textBox7.Text = this.databaseHandle.ItemNameFast(int.Parse(this.r_t_id1.Text.Trim()));
    }

    private void dgItems_CellClick(object sender, DataGridViewCellEventArgs e)
    {
      if (e.RowIndex < 0 || !(this.dgItems.Rows[e.RowIndex].Cells["ID"].Value.ToString().Trim() != ""))
        return;
      string str = "select * from t_item_exchange where a_index = " + this.dgItems.Rows[e.RowIndex].Cells["ID"].Value.ToString();
      MySqlConnection mySqlConnection = new MySqlConnection("datasource=" + this.Host + ";Port=3306;User ID="  + this.User + ";Password=" + this.Password + ";Database=" + this.Database + ";Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;");
      MySqlCommand command = mySqlConnection.CreateCommand();
      command.CommandText = str;
      mySqlConnection.Open();
      MySqlDataReader mySqlDataReader = command.ExecuteReader();
      while (mySqlDataReader.Read())
      {
        tbl_exchange tblExchange = new tbl_exchange();
        this.t_exchange_id.Text = mySqlDataReader.GetValue(0).ToString();
        this.tx_npc_id.Text = mySqlDataReader.GetValue(2).ToString();
        this.tb_reward_id.Text = mySqlDataReader.GetValue(3).ToString();
        this.tb_reward_qty.Text = mySqlDataReader.GetValue(4).ToString();
        this.r_t_id1.Text = mySqlDataReader.GetValue(5).ToString();
        this.textBox6.Text = mySqlDataReader.GetValue(6).ToString();
        this.r_t_id2.Text = mySqlDataReader.GetValue(7).ToString();
        this.textBox9.Text = mySqlDataReader.GetValue(8).ToString();
        this.r_t_id3.Text = mySqlDataReader.GetValue(9).ToString();
        this.textBox12.Text = mySqlDataReader.GetValue(10).ToString();
        this.r_t_id4.Text = mySqlDataReader.GetValue(11).ToString();
        this.textBox15.Text = mySqlDataReader.GetValue(12).ToString();
        this.r_t_id5.Text = mySqlDataReader.GetValue(13).ToString();
        this.textBox18.Text = mySqlDataReader.GetValue(14).ToString();
        this.a_name.Text = mySqlDataReader.GetValue(15).ToString();
        this.a_desc.Text = mySqlDataReader.GetValue(16).ToString();
        ExchangeExport_cHaR.ExChangeList.Add(tblExchange);
      }
      mySqlConnection.Close();
    }

    private void tx_npc_id_TextChanged(object sender, EventArgs e)
    {
      this.pc_npc.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.tx_npc_id.Text.Trim()));
      this.tx_npc_name.Text = this.databaseHandle.MobNameFast(int.Parse(this.tx_npc_id.Text.Trim()));
    }

    private void r_t_id4_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox6.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.r_t_id4.Text.Trim()));
      this.textBox16.Text = this.databaseHandle.ItemNameFast(int.Parse(this.r_t_id4.Text.Trim()));
    }

    private void r_t_id5_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox7.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.r_t_id5.Text.Trim()));
      this.textBox19.Text = this.databaseHandle.ItemNameFast(int.Parse(this.r_t_id5.Text.Trim()));
    }

    private void r_t_id3_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox5.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.r_t_id3.Text.Trim()));
      this.textBox13.Text = this.databaseHandle.ItemNameFast(int.Parse(this.r_t_id3.Text.Trim()));
    }

    private void r_t_id2_TextChanged(object sender, EventArgs e)
    {
      this.pictureBox4.Image = (Image) this.databaseHandle.IconFast(int.Parse(this.r_t_id2.Text.Trim()));
      this.textBox10.Text = this.databaseHandle.ItemNameFast(int.Parse(this.r_t_id2.Text.Trim()));
    }

    private void InitializeDevice()
    {
      this._Direct3D = new Direct3D();
      Direct3D direct3D = this._Direct3D;
      int adapter = 0;
      int num1 = 1;
      IntPtr handle1 = this.Handle;
      int num2 = 32;
      PresentParameters[] presentParametersArray = new PresentParameters[1];
      int index = 0;
      PresentParameters presentParameters = new PresentParameters();
      presentParameters.SwapEffect = SwapEffect.Discard;
      IntPtr handle2 = this.panel3DView.Handle;
      presentParameters.DeviceWindowHandle = handle2;
      int num3 = 1;
      presentParameters.Windowed = num3 != 0;
      int width = this.panel3DView.Width;
      presentParameters.BackBufferWidth = width;
      int height = this.panel3DView.Height;
      presentParameters.BackBufferHeight = height;
      int num4 = 21;
      presentParameters.BackBufferFormat = (SlimDX.Direct3D9.Format) num4;
      presentParametersArray[index] = presentParameters;
      this._Device = new Device(direct3D, adapter, (DeviceType) num1, handle1, (CreateFlags) num2, presentParametersArray);
      this._Device.SetRenderState<Cull>(RenderState.CullMode, Cull.None);
      this._Device.SetRenderState<FillMode>(RenderState.FillMode, FillMode.Solid);
      this._Device.SetRenderState(RenderState.Lighting, false);
      this.CameraPositioning();
    }

    private void CameraPositioning()
    {
      this._Device.SetTransform(TransformState.Projection, Matrix.PerspectiveFovLH(100f, 1f, 1f, 450f));
      this._Device.SetTransform(TransformState.View, Matrix.LookAtLH(new Vector3(0.0f, 0.0f, -5f), new Vector3(0.0f, 0.0f, 0.0f), new Vector3(0.0f, 1f, 0.0f)));
      this._Device.SetTransform(TransformState.World, Matrix.RotationYawPitchRoll(0.0f, 0.0f, 0.0f));
    }

    private void Render()
    {
      this._Device.Viewport = new Viewport(0, 0, this.panel3DView.Width, this.panel3DView.Height);
      this._Device.Clear(ClearFlags.ZBuffer | ClearFlags.Target, new Color4(Color.FromKnownColor(KnownColor.Control)), 1f, 0);
      this._Device.BeginScene();
      this._Device.SetTransform(TransformState.View, Matrix.LookAtLH(new Vector3(0.0f, 0.0f, this._Zoom), new Vector3(this._LeftRight, this._UpDown, 0.0f), new Vector3(0.0f, 1f, 0.0f)));
      this._Device.SetTransform(TransformState.World, Matrix.RotationYawPitchRoll(this._Rotation, 3.1f, 0.0f));
      if (this._Models != null && this._Models.Count<tMesh>() != 0)
      {
        for (int index = 0; index < this._Models.Count<tMesh>(); ++index)
        {
          if (this._Models[index].TexData != null)
            this._Device.SetTexture(0, (BaseTexture) this._Models[index].TexData);
          for (int subset = 0; subset < 1000; ++subset)
            this._Models[index].MeshData.DrawSubset(subset);
        }
      }
      this._Device.EndScene();
      this._Device.Present();
      this._Rotation -= 0.03f;
    }

    private void timer1_Tick(object sender, EventArgs e)
    {
    }

    private void dgItems_CellContentClick(object sender, DataGridViewCellEventArgs e)
    {
    }

    private void button4_Click(object sender, EventArgs e)
    {
      this.r_t_id2.Text = "0";
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.r_t_id2.Text = Convert.ToString(itemPicker.ItemIndex);
    }

    private void button5_Click(object sender, EventArgs e)
    {
      this.r_t_id3.Text = "0";
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.r_t_id3.Text = Convert.ToString(itemPicker.ItemIndex);
    }

    private void button6_Click(object sender, EventArgs e)
    {
      this.r_t_id4.Text = "0";
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.r_t_id4.Text = Convert.ToString(itemPicker.ItemIndex);
    }

    private void button7_Click(object sender, EventArgs e)
    {
      this.r_t_id5.Text = "0";
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.r_t_id5.Text = Convert.ToString(itemPicker.ItemIndex);
    }

    private void t_exchange_id_TextChanged(object sender, EventArgs e)
    {
      this.button9.Enabled = this.t_exchange_id.Text.Trim().Length > 0;
      this.button12.Enabled = this.t_exchange_id.Text.Trim().Length > 0;
      this.button1.Enabled = this.t_exchange_id.Text.Trim().Length > 0;
      this.button8.Enabled = this.t_exchange_id.Text.Trim().Length <= 0;
    }

    private void btn_EnabledChanged(object sender, EventArgs e)
    {
      if (((Control) sender).Enabled)
      {
        switch (((Control) sender).Name)
        {
          case "button9":
            ((Control) sender).BackColor = Color.LightCyan;
            break;
          case "button12":
            ((Control) sender).BackColor = Color.LightCoral;
            break;
          case "button1":
            ((Control) sender).BackColor = Color.Plum;
            break;
          default:
            ((Control) sender).BackColor = Color.Honeydew;
            break;
        }
      }
      else
        ((Control) sender).BackColor = Color.Silver;
    }

    private void Number_textbox_KeyPress(object sender, KeyPressEventArgs e)
    {
    }

    private void bt_refresh_Click(object sender, EventArgs e)
    {
      this.t_exchange_id.Text = "";
      this.tx_npc_id.Text = "0";
      this.tb_reward_id.Text = "0";
      this.tb_reward_qty.Text = "0";
      this.r_t_id1.Text = "0";
      this.textBox6.Text = "0";
      this.r_t_id2.Text = "0";
      this.textBox9.Text = "0";
      this.r_t_id3.Text = "0";
      this.textBox12.Text = "0";
      this.r_t_id4.Text = "0";
      this.textBox15.Text = "0";
      this.r_t_id5.Text = "0";
      this.textBox18.Text = "0";
      this.a_name.Text = "";
      this.a_desc.Text = "";
    }

    private void bt_npc_Click(object sender, EventArgs e)
    {
      this.tx_npc_id.Text = "0";
      MobPicker mobPicker = new MobPicker();
      if (mobPicker.ShowDialog() != DialogResult.OK)
        return;
      this.tx_npc_id.Text = mobPicker.MobIndex.ToString();
    }

    private void button8_Click(object sender, EventArgs e)
    {
      if (this.tx_npc_id.Text.Trim().Length <= 0)
      {
        int num = (int) MessageBox.Show("Please input NPC ID first", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "insert into t_item_exchange(a_index, a_enable, a_npc_index, result_itemIndex, result_itemCount, source_itemIndex0, source_itemCount0, source_itemIndex1, source_itemCount1, source_itemIndex2, source_itemCount2, source_itemIndex3, source_itemCount3, source_itemIndex4, source_itemCount4) select IFNULL(max(a.a_index), 0) + 1 as id, a_enable, " + this.tx_npc_id.Text.Trim() + ", " + (this.tb_reward_id.Text.Trim().Length == 0 ? "0" : this.tb_reward_id.Text.Trim()) + ", " + (this.tb_reward_qty.Text.Trim().Length == 0 ? "0" : this.tb_reward_qty.Text.Trim()) + ", " + (this.r_t_id1.Text.Trim().Length == 0 ? "0" : this.r_t_id1.Text.Trim()) + ", " + (this.textBox6.Text.Trim().Length == 0 ? "0" : this.textBox6.Text.Trim()) + ", " + (this.r_t_id2.Text.Trim().Length == 0 ? "0" : this.r_t_id2.Text.Trim()) + ", " + (this.textBox9.Text.Trim().Length == 0 ? "0" : this.textBox9.Text.Trim()) + ", " + (this.r_t_id3.Text.Trim().Length == 0 ? "0" : this.r_t_id3.Text.Trim()) + ", " + (this.textBox12.Text.Trim().Length == 0 ? "0" : this.textBox12.Text.Trim()) + ", " + (this.r_t_id4.Text.Trim().Length == 0 ? "0" : this.r_t_id4.Text.Trim()) + ", " + (this.textBox15.Text.Trim().Length == 0 ? "0" : this.textBox15.Text.Trim()) + ", " + (this.r_t_id5.Text.Trim().Length == 0 ? "0" : this.r_t_id5.Text.Trim()) + ", " + (this.textBox18.Text.Trim().Length == 0 ? "0" : this.textBox18.Text.Trim()) + ", '" + this.a_name.Text.Trim() + "', '" + this.a_desc.Text.Trim() + "' from t_item_exchange a");
        this.LoadDG();
      }
    }

    private void button12_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want to delete " + this.tb_reward_name.Text.Trim() + " ?", "Please confirm delete.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      if (this.t_exchange_id.Text.Trim().Length <= 0)
      {
        int num = (int) MessageBox.Show("No data to delete in select item to delete first", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "delete from t_item_exchange where a_index = " + this.t_exchange_id.Text.Trim());
        this.LoadDG();
      }
    }

    private void button9_Click(object sender, EventArgs e)
    {
      if (this.tx_npc_id.Text.Trim().Length <= 0)
      {
        int num = (int) MessageBox.Show("Please input NPC ID first", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        int ID = Convert.ToInt32(this.dgItems.Rows[0].Cells["ID"].Value);
        int index = ExchangeExport_cHaR.ExChangeList.FindIndex((Predicate<tbl_exchange>) (p => p.index.Equals(ID)));
        ExchangeExport_cHaR.ExChangeList[index].npcidx = Convert.ToInt32(this.tx_npc_id.Text);
        ExchangeExport_cHaR.ExChangeList[index].result_itemIndex = Convert.ToInt32(this.tb_reward_id.Text);
        ExchangeExport_cHaR.ExChangeList[index].result_itemCount = Convert.ToInt32(this.tb_reward_qty.Text);
        ExchangeExport_cHaR.ExChangeList[index].source_itemIndex0 = Convert.ToInt32(this.r_t_id1.Text);
        ExchangeExport_cHaR.ExChangeList[index].source_itemCount0 = Convert.ToInt32(this.textBox6.Text);
        ExchangeExport_cHaR.ExChangeList[index].source_itemIndex1 = Convert.ToInt32(this.r_t_id2.Text);
        ExchangeExport_cHaR.ExChangeList[index].source_itemCount1 = Convert.ToInt32(this.textBox9.Text);
        ExchangeExport_cHaR.ExChangeList[index].source_itemIndex2 = Convert.ToInt32(this.r_t_id3.Text);
        ExchangeExport_cHaR.ExChangeList[index].source_itemCount2 = Convert.ToInt32(this.textBox12.Text);
        ExchangeExport_cHaR.ExChangeList[index].source_itemIndex3 = Convert.ToInt32(this.r_t_id4.Text);
        ExchangeExport_cHaR.ExChangeList[index].source_itemCount3 = Convert.ToInt32(this.textBox15.Text);
        ExchangeExport_cHaR.ExChangeList[index].source_item_Index4 = Convert.ToInt32(this.r_t_id5.Text);
        ExchangeExport_cHaR.ExChangeList[index].source_itemCount4 = Convert.ToInt32(this.textBox18.Text);
        ExchangeExport_cHaR.ExChangeList[index].npcidx = Convert.ToInt32(this.tx_npc_id.Text);
        ExchangeExport_cHaR.ExChangeList[index].npcidx = Convert.ToInt32(this.tx_npc_id.Text);
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "update t_item_exchange set a_npc_index = " + this.tx_npc_id.Text.Trim() + ", result_itemIndex = " + (this.tb_reward_id.Text.Trim().Length == 0 ? "0" : this.tb_reward_id.Text.Trim()) + ", result_itemCount = " + (this.tb_reward_qty.Text.Trim().Length == 0 ? "0" : this.tb_reward_qty.Text.Trim()) + ", source_itemIndex0 = " + (this.r_t_id1.Text.Trim().Length == 0 ? "0" : this.r_t_id1.Text.Trim()) + ", source_itemCount0 = " + (this.textBox6.Text.Trim().Length == 0 ? "0" : this.textBox6.Text.Trim()) + ", source_itemIndex1 = " + (this.r_t_id2.Text.Trim().Length == 0 ? "0" : this.r_t_id2.Text.Trim()) + ", source_itemCount1 = " + (this.textBox9.Text.Trim().Length == 0 ? "0" : this.textBox9.Text.Trim()) + ", source_itemIndex2 = " + (this.r_t_id3.Text.Trim().Length == 0 ? "0" : this.r_t_id3.Text.Trim()) + ", source_itemCount2 = " + (this.textBox12.Text.Trim().Length == 0 ? "0" : this.textBox12.Text.Trim()) + ", source_itemIndex3 = " + (this.r_t_id4.Text.Trim().Length == 0 ? "0" : this.r_t_id4.Text.Trim()) + ", source_itemCount3 = " + (this.textBox15.Text.Trim().Length == 0 ? "0" : this.textBox15.Text.Trim()) + ", source_itemIndex4 = " + (this.r_t_id5.Text.Trim().Length == 0 ? "0" : this.r_t_id5.Text.Trim()) + ", source_itemCount4  = " + (this.textBox18.Text.Trim().Length == 0 ? "0" : this.textBox18.Text.Trim()) + ", a_name = '" + (this.r_t_id5.Text.Trim().Length == 0 ? "0" : this.r_t_id5.Text.Trim()) + "', a_desc  = '" + (this.textBox18.Text.Trim().Length == 0 ? "0" : this.textBox18.Text.Trim()) + "' where a_index = " + this.t_exchange_id.Text.Trim());
        this.LoadDG();
      }
    }

    private void button11_Click(object sender, EventArgs e)
    {
      SaveFileDialog saveFileDialog = new SaveFileDialog();
      saveFileDialog.Filter = "File item_exchange.lod|item_exchange*.lod";
      saveFileDialog.FileName = "item_exchange.lod";
      saveFileDialog.Title = "Save item_exchange.lod file";
      if (saveFileDialog.ShowDialog() != DialogResult.OK)
        return;
      BinaryWriter binaryWriter = new BinaryWriter((Stream) File.Create(saveFileDialog.FileName));
      int num1 = this.databaseHandle.CountByRow(this.Host, this.User, this.Password, this.Database, "SELECT COUNT(*) FROM t_item_exchange");
      int num2 = this.databaseHandle.CountByRow(this.Host, this.User, this.Password, this.Database, "SELECT MAX(a_index) FROM t_item_exchange");
      string str = "SELECT * FROM t_item_exchange WHERE a_enable = 1 ORDER by a_index";
      MySqlConnection mySqlConnection = new MySqlConnection("datasource=" + this.Host + ";Port=3306;User ID="  + this.User + ";Password=" + this.Password + ";Database=" + this.Database + ";Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;");
      MySqlCommand command = mySqlConnection.CreateCommand();
      command.CommandText = str;
      mySqlConnection.Open();
      command.ExecuteReader();
      binaryWriter.Write(num2);
      binaryWriter.Write(num1);
      for (int index = 0; index <= num1 - 1; ++index)
      {
        binaryWriter.Write(ExchangeExport_cHaR.ExChangeList[index].index);
        binaryWriter.Write(ExchangeExport_cHaR.ExChangeList[index].npcidx);
        binaryWriter.Write(ExchangeExport_cHaR.ExChangeList[index].result_itemIndex);
        binaryWriter.Write(ExchangeExport_cHaR.ExChangeList[index].result_itemCount);
        binaryWriter.Write(ExchangeExport_cHaR.ExChangeList[index].source_itemIndex0);
        binaryWriter.Write(ExchangeExport_cHaR.ExChangeList[index].source_itemCount0);
        binaryWriter.Write(ExchangeExport_cHaR.ExChangeList[index].source_itemIndex1);
        binaryWriter.Write(ExchangeExport_cHaR.ExChangeList[index].source_itemCount1);
        binaryWriter.Write(ExchangeExport_cHaR.ExChangeList[index].source_itemIndex2);
        binaryWriter.Write(ExchangeExport_cHaR.ExChangeList[index].source_itemCount2);
        binaryWriter.Write(ExchangeExport_cHaR.ExChangeList[index].source_itemIndex3);
        binaryWriter.Write(ExchangeExport_cHaR.ExChangeList[index].source_itemCount3);
        binaryWriter.Write(ExchangeExport_cHaR.ExChangeList[index].source_item_Index4);
        binaryWriter.Write(ExchangeExport_cHaR.ExChangeList[index].source_itemCount4);
      }
      mySqlConnection.Close();
      binaryWriter.Close();
      int num3 = (int) MessageBox.Show("It's done.", "Completed", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
    }

    private void button1_Click(object sender, EventArgs e)
    {
      if (this.tx_npc_id.Text.Trim().Length <= 0)
      {
        int num1 = (int) MessageBox.Show("Please input NPC ID first", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "insert into t_item_exchange select IFNULL(max(a.a_index), 0) + 1 as id, a_enable, a.a_npc_index, a.result_itemIndex, a.result_itemCount, a.source_itemIndex0, a.source_itemCount0, a.source_itemIndex1, a.source_itemCount1, a.source_itemIndex2, a.source_itemCount2, a.source_itemIndex3, a.source_itemCount3, a.source_itemIndex4, a.source_itemCount4, a.a_name, a.a_desc from t_item_exchange a");
        int num2 = (int) MessageBox.Show("Successful copy", "Completed", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
        this.LoadDG();
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
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (ExchangeExport_cHaR));
      this.groupBox4 = new GroupBox();
      this.tb_reward_qty = new TextBox();
      this.label5 = new Label();
      this.button2 = new Button();
      this.tb_reward_name = new TextBox();
      this.tb_reward_id = new TextBox();
      this.pictureBox2 = new PictureBox();
      this.label3 = new Label();
      this.label4 = new Label();
      this.groupBox3 = new GroupBox();
      this.groupBox5 = new GroupBox();
      this.a_name = new TextBox();
      this.label23 = new Label();
      this.a_desc = new TextBox();
      this.label22 = new Label();
      this.checkBox5 = new CheckBox();
      this.checkBox4 = new CheckBox();
      this.checkBox3 = new CheckBox();
      this.checkBox2 = new CheckBox();
      this.checkBox1 = new CheckBox();
      this.textBox18 = new TextBox();
      this.label18 = new Label();
      this.button7 = new Button();
      this.textBox19 = new TextBox();
      this.r_t_id5 = new TextBox();
      this.pictureBox7 = new PictureBox();
      this.textBox15 = new TextBox();
      this.label15 = new Label();
      this.button6 = new Button();
      this.textBox16 = new TextBox();
      this.r_t_id4 = new TextBox();
      this.pictureBox6 = new PictureBox();
      this.textBox12 = new TextBox();
      this.label12 = new Label();
      this.button5 = new Button();
      this.textBox13 = new TextBox();
      this.r_t_id3 = new TextBox();
      this.pictureBox5 = new PictureBox();
      this.textBox9 = new TextBox();
      this.label9 = new Label();
      this.button4 = new Button();
      this.textBox10 = new TextBox();
      this.r_t_id2 = new TextBox();
      this.pictureBox4 = new PictureBox();
      this.textBox6 = new TextBox();
      this.label6 = new Label();
      this.button3 = new Button();
      this.textBox7 = new TextBox();
      this.r_t_id1 = new TextBox();
      this.pictureBox3 = new PictureBox();
      this.label19 = new Label();
      this.label20 = new Label();
      this.label16 = new Label();
      this.label17 = new Label();
      this.label13 = new Label();
      this.label14 = new Label();
      this.label10 = new Label();
      this.label11 = new Label();
      this.label7 = new Label();
      this.label8 = new Label();
      this.gb_npc = new GroupBox();
      this.panel3DView = new Panel();
      this.bt_npc = new Button();
      this.tx_npc_name = new TextBox();
      this.tx_npc_id = new TextBox();
      this.pc_npc = new PictureBox();
      this.label2 = new Label();
      this.label1 = new Label();
      this.groupBox1 = new GroupBox();
      this.dgItems = new DataGridView();
      this.groupBox7 = new GroupBox();
      this.button1 = new Button();
      this.button9 = new Button();
      this.bt_refresh = new Button();
      this.button12 = new Button();
      this.button8 = new Button();
      this.button11 = new Button();
      this.groupBox2 = new GroupBox();
      this.t_exchange_id = new TextBox();
      this.label21 = new Label();
      this.Column7 = new DataGridViewImageColumn();
      this.ID = new DataGridViewTextBoxColumn();
      this.ItemName = new DataGridViewTextBoxColumn();
      this.NpcName = new DataGridViewTextBoxColumn();
      this.groupBox4.SuspendLayout();
      ((ISupportInitialize) this.pictureBox2).BeginInit();
      this.groupBox3.SuspendLayout();
      this.groupBox5.SuspendLayout();
      ((ISupportInitialize) this.pictureBox7).BeginInit();
      ((ISupportInitialize) this.pictureBox6).BeginInit();
      ((ISupportInitialize) this.pictureBox5).BeginInit();
      ((ISupportInitialize) this.pictureBox4).BeginInit();
      ((ISupportInitialize) this.pictureBox3).BeginInit();
      this.gb_npc.SuspendLayout();
      ((ISupportInitialize) this.pc_npc).BeginInit();
      this.groupBox1.SuspendLayout();
      ((ISupportInitialize) this.dgItems).BeginInit();
      this.groupBox7.SuspendLayout();
      this.groupBox2.SuspendLayout();
      this.SuspendLayout();
      this.groupBox4.BackColor = Color.Linen;
      this.groupBox4.Controls.Add((Control) this.tb_reward_qty);
      this.groupBox4.Controls.Add((Control) this.label5);
      this.groupBox4.Controls.Add((Control) this.button2);
      this.groupBox4.Controls.Add((Control) this.tb_reward_name);
      this.groupBox4.Controls.Add((Control) this.tb_reward_id);
      this.groupBox4.Controls.Add((Control) this.pictureBox2);
      this.groupBox4.Controls.Add((Control) this.label3);
      this.groupBox4.Controls.Add((Control) this.label4);
      this.groupBox4.Location = new Point(394, 58);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Size = new Size(409, 97);
      this.groupBox4.TabIndex = 8;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "Reward Item";
      this.tb_reward_qty.Location = new Point(254, 28);
      this.tb_reward_qty.Name = "tb_reward_qty";
      this.tb_reward_qty.Size = new Size(78, 21);
      this.tb_reward_qty.TabIndex = 19;
      this.tb_reward_qty.KeyPress += new KeyPressEventHandler(this.Number_textbox_KeyPress);
      this.label5.AutoSize = true;
      this.label5.Location = new Point(211, 32);
      this.label5.Name = "label5";
      this.label5.Size = new Size(37, 13);
      this.label5.TabIndex = 18;
      this.label5.Text = "Q'ty : ";
      this.button2.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.search__5_;
      this.button2.Location = new Point(360, 24);
      this.button2.Name = "button2";
      this.button2.Size = new Size(30, 27);
      this.button2.TabIndex = 13;
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.tb_reward_name.Enabled = false;
      this.tb_reward_name.Location = new Point(115, 57);
      this.tb_reward_name.Name = "tb_reward_name";
      this.tb_reward_name.Size = new Size(288, 21);
      this.tb_reward_name.TabIndex = 15;
      this.tb_reward_id.Enabled = false;
      this.tb_reward_id.Location = new Point(115, 28);
      this.tb_reward_id.Name = "tb_reward_id";
      this.tb_reward_id.Size = new Size(78, 21);
      this.tb_reward_id.TabIndex = 14;
      this.tb_reward_id.TextChanged += new EventHandler(this.tb_reward_id_TextChanged);
      this.pictureBox2.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox2.Image = (Image) componentResourceManager.GetObject("pictureBox2.Image");
      this.pictureBox2.Location = new Point(11, 34);
      this.pictureBox2.Name = "pictureBox2";
      this.pictureBox2.Size = new Size(42, 40);
      this.pictureBox2.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pictureBox2.TabIndex = 10;
      this.pictureBox2.TabStop = false;
      this.label3.AutoSize = true;
      this.label3.Location = new Point(60, 61);
      this.label3.Name = "label3";
      this.label3.Size = new Size(41, 13);
      this.label3.TabIndex = 17;
      this.label3.Text = "Name :";
      this.label4.AutoSize = true;
      this.label4.Location = new Point(60, 32);
      this.label4.Name = "label4";
      this.label4.Size = new Size(28, 13);
      this.label4.TabIndex = 16;
      this.label4.Text = "ID : ";
      this.groupBox3.BackColor = Color.Honeydew;
      this.groupBox3.Controls.Add((Control) this.groupBox5);
      this.groupBox3.Controls.Add((Control) this.checkBox5);
      this.groupBox3.Controls.Add((Control) this.checkBox4);
      this.groupBox3.Controls.Add((Control) this.checkBox3);
      this.groupBox3.Controls.Add((Control) this.checkBox2);
      this.groupBox3.Controls.Add((Control) this.checkBox1);
      this.groupBox3.Controls.Add((Control) this.textBox18);
      this.groupBox3.Controls.Add((Control) this.label18);
      this.groupBox3.Controls.Add((Control) this.button7);
      this.groupBox3.Controls.Add((Control) this.textBox19);
      this.groupBox3.Controls.Add((Control) this.r_t_id5);
      this.groupBox3.Controls.Add((Control) this.pictureBox7);
      this.groupBox3.Controls.Add((Control) this.textBox15);
      this.groupBox3.Controls.Add((Control) this.label15);
      this.groupBox3.Controls.Add((Control) this.button6);
      this.groupBox3.Controls.Add((Control) this.textBox16);
      this.groupBox3.Controls.Add((Control) this.r_t_id4);
      this.groupBox3.Controls.Add((Control) this.pictureBox6);
      this.groupBox3.Controls.Add((Control) this.textBox12);
      this.groupBox3.Controls.Add((Control) this.label12);
      this.groupBox3.Controls.Add((Control) this.button5);
      this.groupBox3.Controls.Add((Control) this.textBox13);
      this.groupBox3.Controls.Add((Control) this.r_t_id3);
      this.groupBox3.Controls.Add((Control) this.pictureBox5);
      this.groupBox3.Controls.Add((Control) this.textBox9);
      this.groupBox3.Controls.Add((Control) this.label9);
      this.groupBox3.Controls.Add((Control) this.button4);
      this.groupBox3.Controls.Add((Control) this.textBox10);
      this.groupBox3.Controls.Add((Control) this.r_t_id2);
      this.groupBox3.Controls.Add((Control) this.pictureBox4);
      this.groupBox3.Controls.Add((Control) this.textBox6);
      this.groupBox3.Controls.Add((Control) this.label6);
      this.groupBox3.Controls.Add((Control) this.button3);
      this.groupBox3.Controls.Add((Control) this.textBox7);
      this.groupBox3.Controls.Add((Control) this.r_t_id1);
      this.groupBox3.Controls.Add((Control) this.pictureBox3);
      this.groupBox3.Controls.Add((Control) this.label19);
      this.groupBox3.Controls.Add((Control) this.label20);
      this.groupBox3.Controls.Add((Control) this.label16);
      this.groupBox3.Controls.Add((Control) this.label17);
      this.groupBox3.Controls.Add((Control) this.label13);
      this.groupBox3.Controls.Add((Control) this.label14);
      this.groupBox3.Controls.Add((Control) this.label10);
      this.groupBox3.Controls.Add((Control) this.label11);
      this.groupBox3.Controls.Add((Control) this.label7);
      this.groupBox3.Controls.Add((Control) this.label8);
      this.groupBox3.Location = new Point(394, 161);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Size = new Size(733, 258);
      this.groupBox3.TabIndex = 7;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "Exchange Items";
      this.groupBox5.Controls.Add((Control) this.a_name);
      this.groupBox5.Controls.Add((Control) this.label23);
      this.groupBox5.Controls.Add((Control) this.a_desc);
      this.groupBox5.Controls.Add((Control) this.label22);
      this.groupBox5.Location = new Point(357, 168);
      this.groupBox5.Name = "groupBox5";
      this.groupBox5.Size = new Size(371, 81);
      this.groupBox5.TabIndex = 74;
      this.groupBox5.TabStop = false;
      this.groupBox5.Text = "Other Content : ";
      this.a_name.Enabled = false;
      this.a_name.Location = new Point(87, 20);
      this.a_name.Name = "a_name";
      this.a_name.Size = new Size(258, 21);
      this.a_name.TabIndex = 70;
      this.label23.AutoSize = true;
      this.label23.Location = new Point(15, 51);
      this.label23.Name = "label23";
      this.label23.Size = new Size(67, 13);
      this.label23.TabIndex = 73;
      this.label23.Text = "Description :";
      this.a_desc.Enabled = false;
      this.a_desc.Location = new Point(88, 47);
      this.a_desc.Name = "a_desc";
      this.a_desc.Size = new Size(258, 21);
      this.a_desc.TabIndex = 71;
      this.label22.AutoSize = true;
      this.label22.Location = new Point(14, 23);
      this.label22.Name = "label22";
      this.label22.Size = new Size(41, 13);
      this.label22.TabIndex = 72;
      this.label22.Text = "Name :";
      this.checkBox5.AutoSize = true;
      this.checkBox5.Location = new Point(7, 180);
      this.checkBox5.Name = "checkBox5";
      this.checkBox5.Size = new Size(117, 17);
      this.checkBox5.TabIndex = 69;
      this.checkBox5.Text = "Item Require No. 5";
      this.checkBox5.UseVisualStyleBackColor = true;
      this.checkBox4.AutoSize = true;
      this.checkBox4.Location = new Point(381, 96);
      this.checkBox4.Name = "checkBox4";
      this.checkBox4.Size = new Size(117, 17);
      this.checkBox4.TabIndex = 68;
      this.checkBox4.Text = "Item Require No. 4";
      this.checkBox4.UseVisualStyleBackColor = true;
      this.checkBox3.AutoSize = true;
      this.checkBox3.Location = new Point(6, 96);
      this.checkBox3.Name = "checkBox3";
      this.checkBox3.Size = new Size(117, 17);
      this.checkBox3.TabIndex = 67;
      this.checkBox3.Text = "Item Require No. 3";
      this.checkBox3.UseVisualStyleBackColor = true;
      this.checkBox2.AutoSize = true;
      this.checkBox2.Location = new Point(381, 18);
      this.checkBox2.Name = "checkBox2";
      this.checkBox2.Size = new Size(117, 17);
      this.checkBox2.TabIndex = 66;
      this.checkBox2.Text = "Item Require No. 2";
      this.checkBox2.UseVisualStyleBackColor = true;
      this.checkBox1.AutoSize = true;
      this.checkBox1.Location = new Point(7, 18);
      this.checkBox1.Name = "checkBox1";
      this.checkBox1.Size = new Size(117, 17);
      this.checkBox1.TabIndex = 65;
      this.checkBox1.Text = "Item Require No. 1";
      this.checkBox1.UseVisualStyleBackColor = true;
      this.textBox18.Location = new Point(225, 197);
      this.textBox18.Name = "textBox18";
      this.textBox18.Size = new Size(66, 21);
      this.textBox18.TabIndex = 59;
      this.textBox18.KeyPress += new KeyPressEventHandler(this.Number_textbox_KeyPress);
      this.label18.AutoSize = true;
      this.label18.Location = new Point(182, 201);
      this.label18.Name = "label18";
      this.label18.Size = new Size(37, 13);
      this.label18.TabIndex = 58;
      this.label18.Text = "Q'ty : ";
      this.button7.Image = (Image) componentResourceManager.GetObject("button7.Image");
      this.button7.Location = new Point(295, 194);
      this.button7.Name = "button7";
      this.button7.Size = new Size(27, 25);
      this.button7.TabIndex = 53;
      this.button7.UseVisualStyleBackColor = true;
      this.button7.Click += new EventHandler(this.button7_Click);
      this.textBox19.Enabled = false;
      this.textBox19.Location = new Point(111, 226);
      this.textBox19.Name = "textBox19";
      this.textBox19.Size = new Size(224, 21);
      this.textBox19.TabIndex = 55;
      this.r_t_id5.Enabled = false;
      this.r_t_id5.Location = new Point(111, 197);
      this.r_t_id5.Name = "r_t_id5";
      this.r_t_id5.Size = new Size(66, 21);
      this.r_t_id5.TabIndex = 54;
      this.r_t_id5.TextChanged += new EventHandler(this.r_t_id5_TextChanged);
      this.pictureBox7.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox7.Image = (Image) componentResourceManager.GetObject("pictureBox7.Image");
      this.pictureBox7.Location = new Point(7, 203);
      this.pictureBox7.Name = "pictureBox7";
      this.pictureBox7.Size = new Size(42, 40);
      this.pictureBox7.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pictureBox7.TabIndex = 52;
      this.pictureBox7.TabStop = false;
      this.textBox15.Location = new Point(599, 113);
      this.textBox15.Name = "textBox15";
      this.textBox15.Size = new Size(66, 21);
      this.textBox15.TabIndex = 51;
      this.textBox15.KeyPress += new KeyPressEventHandler(this.Number_textbox_KeyPress);
      this.label15.AutoSize = true;
      this.label15.Location = new Point(556, 117);
      this.label15.Name = "label15";
      this.label15.Size = new Size(37, 13);
      this.label15.TabIndex = 50;
      this.label15.Text = "Q'ty : ";
      this.button6.Image = (Image) componentResourceManager.GetObject("button6.Image");
      this.button6.Location = new Point(669, 106);
      this.button6.Name = "button6";
      this.button6.Size = new Size(27, 25);
      this.button6.TabIndex = 45;
      this.button6.UseVisualStyleBackColor = true;
      this.button6.Click += new EventHandler(this.button6_Click);
      this.textBox16.Enabled = false;
      this.textBox16.Location = new Point(485, 142);
      this.textBox16.Name = "textBox16";
      this.textBox16.Size = new Size(224, 21);
      this.textBox16.TabIndex = 47;
      this.r_t_id4.Enabled = false;
      this.r_t_id4.Location = new Point(485, 113);
      this.r_t_id4.Name = "r_t_id4";
      this.r_t_id4.Size = new Size(66, 21);
      this.r_t_id4.TabIndex = 46;
      this.r_t_id4.TextChanged += new EventHandler(this.r_t_id4_TextChanged);
      this.pictureBox6.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox6.Image = (Image) componentResourceManager.GetObject("pictureBox6.Image");
      this.pictureBox6.Location = new Point(381, 119);
      this.pictureBox6.Name = "pictureBox6";
      this.pictureBox6.Size = new Size(42, 40);
      this.pictureBox6.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pictureBox6.TabIndex = 44;
      this.pictureBox6.TabStop = false;
      this.textBox12.Location = new Point(225, 113);
      this.textBox12.Name = "textBox12";
      this.textBox12.Size = new Size(66, 21);
      this.textBox12.TabIndex = 43;
      this.textBox12.KeyPress += new KeyPressEventHandler(this.Number_textbox_KeyPress);
      this.label12.AutoSize = true;
      this.label12.Location = new Point(182, 117);
      this.label12.Name = "label12";
      this.label12.Size = new Size(37, 13);
      this.label12.TabIndex = 42;
      this.label12.Text = "Q'ty : ";
      this.button5.Image = (Image) componentResourceManager.GetObject("button5.Image");
      this.button5.Location = new Point(295, 110);
      this.button5.Name = "button5";
      this.button5.Size = new Size(27, 25);
      this.button5.TabIndex = 37;
      this.button5.UseVisualStyleBackColor = true;
      this.button5.Click += new EventHandler(this.button5_Click);
      this.textBox13.Enabled = false;
      this.textBox13.Location = new Point(111, 142);
      this.textBox13.Name = "textBox13";
      this.textBox13.Size = new Size(224, 21);
      this.textBox13.TabIndex = 39;
      this.r_t_id3.Enabled = false;
      this.r_t_id3.Location = new Point(111, 113);
      this.r_t_id3.Name = "r_t_id3";
      this.r_t_id3.Size = new Size(66, 21);
      this.r_t_id3.TabIndex = 38;
      this.r_t_id3.TextChanged += new EventHandler(this.r_t_id3_TextChanged);
      this.pictureBox5.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox5.Image = (Image) componentResourceManager.GetObject("pictureBox5.Image");
      this.pictureBox5.Location = new Point(7, 119);
      this.pictureBox5.Name = "pictureBox5";
      this.pictureBox5.Size = new Size(42, 40);
      this.pictureBox5.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pictureBox5.TabIndex = 36;
      this.pictureBox5.TabStop = false;
      this.textBox9.Location = new Point(599, 35);
      this.textBox9.Name = "textBox9";
      this.textBox9.Size = new Size(66, 21);
      this.textBox9.TabIndex = 35;
      this.textBox9.KeyPress += new KeyPressEventHandler(this.Number_textbox_KeyPress);
      this.label9.AutoSize = true;
      this.label9.Location = new Point(556, 39);
      this.label9.Name = "label9";
      this.label9.Size = new Size(37, 13);
      this.label9.TabIndex = 34;
      this.label9.Text = "Q'ty : ";
      this.button4.Image = (Image) componentResourceManager.GetObject("button4.Image");
      this.button4.Location = new Point(669, 33);
      this.button4.Name = "button4";
      this.button4.Size = new Size(27, 25);
      this.button4.TabIndex = 29;
      this.button4.UseVisualStyleBackColor = true;
      this.button4.Click += new EventHandler(this.button4_Click);
      this.textBox10.Enabled = false;
      this.textBox10.Location = new Point(485, 64);
      this.textBox10.Name = "textBox10";
      this.textBox10.Size = new Size(224, 21);
      this.textBox10.TabIndex = 31;
      this.r_t_id2.Enabled = false;
      this.r_t_id2.Location = new Point(485, 35);
      this.r_t_id2.Name = "r_t_id2";
      this.r_t_id2.Size = new Size(66, 21);
      this.r_t_id2.TabIndex = 30;
      this.r_t_id2.TextChanged += new EventHandler(this.r_t_id2_TextChanged);
      this.pictureBox4.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox4.Image = (Image) componentResourceManager.GetObject("pictureBox4.Image");
      this.pictureBox4.Location = new Point(381, 41);
      this.pictureBox4.Name = "pictureBox4";
      this.pictureBox4.Size = new Size(42, 40);
      this.pictureBox4.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pictureBox4.TabIndex = 28;
      this.pictureBox4.TabStop = false;
      this.textBox6.Location = new Point(225, 35);
      this.textBox6.Name = "textBox6";
      this.textBox6.Size = new Size(66, 21);
      this.textBox6.TabIndex = 27;
      this.textBox6.KeyPress += new KeyPressEventHandler(this.Number_textbox_KeyPress);
      this.label6.AutoSize = true;
      this.label6.Location = new Point(182, 39);
      this.label6.Name = "label6";
      this.label6.Size = new Size(37, 13);
      this.label6.TabIndex = 26;
      this.label6.Text = "Q'ty : ";
      this.button3.Image = (Image) componentResourceManager.GetObject("button3.Image");
      this.button3.Location = new Point(295, 33);
      this.button3.Name = "button3";
      this.button3.Size = new Size(27, 25);
      this.button3.TabIndex = 21;
      this.button3.UseVisualStyleBackColor = true;
      this.button3.Click += new EventHandler(this.button3_Click);
      this.textBox7.Enabled = false;
      this.textBox7.Location = new Point(111, 64);
      this.textBox7.Name = "textBox7";
      this.textBox7.Size = new Size(224, 21);
      this.textBox7.TabIndex = 23;
      this.r_t_id1.Enabled = false;
      this.r_t_id1.Location = new Point(111, 35);
      this.r_t_id1.Name = "r_t_id1";
      this.r_t_id1.Size = new Size(66, 21);
      this.r_t_id1.TabIndex = 22;
      this.r_t_id1.TextChanged += new EventHandler(this.textBox8_TextChanged);
      this.pictureBox3.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox3.Image = (Image) componentResourceManager.GetObject("pictureBox3.Image");
      this.pictureBox3.Location = new Point(7, 41);
      this.pictureBox3.Name = "pictureBox3";
      this.pictureBox3.Size = new Size(42, 40);
      this.pictureBox3.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pictureBox3.TabIndex = 20;
      this.pictureBox3.TabStop = false;
      this.label19.AutoSize = true;
      this.label19.Location = new Point(56, 230);
      this.label19.Name = "label19";
      this.label19.Size = new Size(41, 13);
      this.label19.TabIndex = 57;
      this.label19.Text = "Name :";
      this.label20.AutoSize = true;
      this.label20.Location = new Point(56, 201);
      this.label20.Name = "label20";
      this.label20.Size = new Size(28, 13);
      this.label20.TabIndex = 56;
      this.label20.Text = "ID : ";
      this.label16.AutoSize = true;
      this.label16.Location = new Point(430, 146);
      this.label16.Name = "label16";
      this.label16.Size = new Size(41, 13);
      this.label16.TabIndex = 49;
      this.label16.Text = "Name :";
      this.label17.AutoSize = true;
      this.label17.Location = new Point(430, 117);
      this.label17.Name = "label17";
      this.label17.Size = new Size(28, 13);
      this.label17.TabIndex = 48;
      this.label17.Text = "ID : ";
      this.label13.AutoSize = true;
      this.label13.Location = new Point(56, 146);
      this.label13.Name = "label13";
      this.label13.Size = new Size(41, 13);
      this.label13.TabIndex = 41;
      this.label13.Text = "Name :";
      this.label14.AutoSize = true;
      this.label14.Location = new Point(56, 117);
      this.label14.Name = "label14";
      this.label14.Size = new Size(28, 13);
      this.label14.TabIndex = 40;
      this.label14.Text = "ID : ";
      this.label10.AutoSize = true;
      this.label10.Location = new Point(430, 68);
      this.label10.Name = "label10";
      this.label10.Size = new Size(41, 13);
      this.label10.TabIndex = 33;
      this.label10.Text = "Name :";
      this.label11.AutoSize = true;
      this.label11.Location = new Point(430, 39);
      this.label11.Name = "label11";
      this.label11.Size = new Size(28, 13);
      this.label11.TabIndex = 32;
      this.label11.Text = "ID : ";
      this.label7.AutoSize = true;
      this.label7.Location = new Point(56, 68);
      this.label7.Name = "label7";
      this.label7.Size = new Size(41, 13);
      this.label7.TabIndex = 25;
      this.label7.Text = "Name :";
      this.label8.AutoSize = true;
      this.label8.Location = new Point(56, 39);
      this.label8.Name = "label8";
      this.label8.Size = new Size(28, 13);
      this.label8.TabIndex = 24;
      this.label8.Text = "ID : ";
      this.gb_npc.BackColor = Color.Snow;
      this.gb_npc.Controls.Add((Control) this.panel3DView);
      this.gb_npc.Controls.Add((Control) this.bt_npc);
      this.gb_npc.Controls.Add((Control) this.tx_npc_name);
      this.gb_npc.Controls.Add((Control) this.tx_npc_id);
      this.gb_npc.Controls.Add((Control) this.pc_npc);
      this.gb_npc.Controls.Add((Control) this.label2);
      this.gb_npc.Controls.Add((Control) this.label1);
      this.gb_npc.Location = new Point(813, 58);
      this.gb_npc.Name = "gb_npc";
      this.gb_npc.Size = new Size(314, 97);
      this.gb_npc.TabIndex = 6;
      this.gb_npc.TabStop = false;
      this.gb_npc.Text = "NPC Information";
      this.panel3DView.Location = new Point(6, 31);
      this.panel3DView.Name = "panel3DView";
      this.panel3DView.Size = new Size(48, 45);
      this.panel3DView.TabIndex = 15;
      this.bt_npc.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.search__5_;
      this.bt_npc.Location = new Point(259, 25);
      this.bt_npc.Name = "bt_npc";
      this.bt_npc.Size = new Size(30, 27);
      this.bt_npc.TabIndex = 0;
      this.bt_npc.UseVisualStyleBackColor = true;
      this.bt_npc.Click += new EventHandler(this.bt_npc_Click);
      this.tx_npc_name.Enabled = false;
      this.tx_npc_name.Location = new Point(105, 59);
      this.tx_npc_name.Name = "tx_npc_name";
      this.tx_npc_name.Size = new Size(197, 21);
      this.tx_npc_name.TabIndex = 12;
      this.tx_npc_id.Enabled = false;
      this.tx_npc_id.Location = new Point(105, 29);
      this.tx_npc_id.Name = "tx_npc_id";
      this.tx_npc_id.Size = new Size(92, 21);
      this.tx_npc_id.TabIndex = 11;
      this.tx_npc_id.TextChanged += new EventHandler(this.tx_npc_id_TextChanged);
      this.pc_npc.BorderStyle = BorderStyle.FixedSingle;
      this.pc_npc.Image = (Image) componentResourceManager.GetObject("pc_npc.Image");
      this.pc_npc.Location = new Point(11, 34);
      this.pc_npc.Name = "pc_npc";
      this.pc_npc.Size = new Size(42, 40);
      this.pc_npc.SizeMode = PictureBoxSizeMode.CenterImage;
      this.pc_npc.TabIndex = 9;
      this.pc_npc.TabStop = false;
      this.label2.AutoSize = true;
      this.label2.Location = new Point(60, 63);
      this.label2.Name = "label2";
      this.label2.Size = new Size(41, 13);
      this.label2.TabIndex = 14;
      this.label2.Text = "Name :";
      this.label1.AutoSize = true;
      this.label1.Location = new Point(60, 33);
      this.label1.Name = "label1";
      this.label1.Size = new Size(28, 13);
      this.label1.TabIndex = 13;
      this.label1.Text = "ID : ";
      this.groupBox1.Controls.Add((Control) this.dgItems);
      this.groupBox1.Location = new Point(6, 58);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(383, 361);
      this.groupBox1.TabIndex = 5;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Data";
      this.dgItems.AllowUserToAddRows = false;
      this.dgItems.AllowUserToDeleteRows = false;
      this.dgItems.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.ColumnHeader;
      this.dgItems.BackgroundColor = SystemColors.Control;
      this.dgItems.BorderStyle = BorderStyle.None;
      this.dgItems.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dgItems.Columns.AddRange((DataGridViewColumn) this.Column7, (DataGridViewColumn) this.ID, (DataGridViewColumn) this.ItemName, (DataGridViewColumn) this.NpcName);
      this.dgItems.Dock = DockStyle.Fill;
      this.dgItems.EnableHeadersVisualStyles = false;
      this.dgItems.Location = new Point(3, 17);
      this.dgItems.Name = "dgItems";
      this.dgItems.RowHeadersVisible = false;
      this.dgItems.RowTemplate.Height = 20;
      this.dgItems.Size = new Size(377, 341);
      this.dgItems.TabIndex = 1;
      this.dgItems.CellClick += new DataGridViewCellEventHandler(this.dgItems_CellClick);
      this.dgItems.CellContentClick += new DataGridViewCellEventHandler(this.dgItems_CellContentClick);
      this.groupBox7.Controls.Add((Control) this.button1);
      this.groupBox7.Controls.Add((Control) this.button9);
      this.groupBox7.Controls.Add((Control) this.bt_refresh);
      this.groupBox7.Controls.Add((Control) this.button12);
      this.groupBox7.Controls.Add((Control) this.button8);
      this.groupBox7.Controls.Add((Control) this.button11);
      this.groupBox7.Location = new Point(144, 1);
      this.groupBox7.Name = "groupBox7";
      this.groupBox7.Size = new Size(670, 52);
      this.groupBox7.TabIndex = 11;
      this.groupBox7.TabStop = false;
      this.groupBox7.Text = "Working";
      this.button1.BackColor = Color.Plum;
      this.button1.FlatStyle = FlatStyle.Flat;
      this.button1.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.control_add_blue;
      this.button1.ImageAlign = ContentAlignment.MiddleLeft;
      this.button1.Location = new Point(278, 18);
      this.button1.Name = "button1";
      this.button1.Size = new Size(96, 27);
      this.button1.TabIndex = 15;
      this.button1.Text = "     Add Copy ";
      this.button1.UseVisualStyleBackColor = false;
      this.button1.EnabledChanged += new EventHandler(this.btn_EnabledChanged);
      this.button1.Click += new EventHandler(this.button1_Click);
      this.button9.BackColor = Color.LightCyan;
      this.button9.FlatStyle = FlatStyle.Flat;
      this.button9.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources._08;
      this.button9.ImageAlign = ContentAlignment.MiddleLeft;
      this.button9.Location = new Point(102, 18);
      this.button9.Name = "button9";
      this.button9.Size = new Size(81, 27);
      this.button9.TabIndex = 12;
      this.button9.Text = "   Update";
      this.button9.UseVisualStyleBackColor = false;
      this.button9.EnabledChanged += new EventHandler(this.btn_EnabledChanged);
      this.button9.Click += new EventHandler(this.button9_Click);
      this.bt_refresh.BackColor = Color.MistyRose;
      this.bt_refresh.FlatStyle = FlatStyle.Flat;
      this.bt_refresh.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.refresh;
      this.bt_refresh.ImageAlign = ContentAlignment.MiddleLeft;
      this.bt_refresh.Location = new Point(446, 17);
      this.bt_refresh.Name = "bt_refresh";
      this.bt_refresh.Size = new Size(81, 27);
      this.bt_refresh.TabIndex = 11;
      this.bt_refresh.Text = "    Reset";
      this.bt_refresh.UseVisualStyleBackColor = false;
      this.bt_refresh.Click += new EventHandler(this.bt_refresh_Click);
      this.button12.BackColor = Color.LightCoral;
      this.button12.FlatStyle = FlatStyle.Flat;
      this.button12.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.delete;
      this.button12.ImageAlign = ContentAlignment.MiddleLeft;
      this.button12.Location = new Point(191, 18);
      this.button12.Name = "button12";
      this.button12.Size = new Size(81, 27);
      this.button12.TabIndex = 11;
      this.button12.Text = "    Delete";
      this.button12.UseVisualStyleBackColor = false;
      this.button12.EnabledChanged += new EventHandler(this.btn_EnabledChanged);
      this.button12.Click += new EventHandler(this.button12_Click);
      this.button8.BackColor = Color.Honeydew;
      this.button8.FlatStyle = FlatStyle.Flat;
      this.button8.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.control_add_blue;
      this.button8.ImageAlign = ContentAlignment.MiddleLeft;
      this.button8.Location = new Point(13, 18);
      this.button8.Name = "button8";
      this.button8.Size = new Size(81, 27);
      this.button8.TabIndex = 11;
      this.button8.Text = "     Add New";
      this.button8.UseVisualStyleBackColor = false;
      this.button8.EnabledChanged += new EventHandler(this.btn_EnabledChanged);
      this.button8.Click += new EventHandler(this.button8_Click);
      this.button11.BackColor = Color.White;
      this.button11.FlatStyle = FlatStyle.Flat;
      this.button11.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.FOLDER05;
      this.button11.ImageAlign = ContentAlignment.MiddleLeft;
      this.button11.Location = new Point(557, 18);
      this.button11.Name = "button11";
      this.button11.Size = new Size(89, 27);
      this.button11.TabIndex = 14;
      this.button11.Text = "  Export";
      this.button11.UseVisualStyleBackColor = false;
      this.button11.Click += new EventHandler(this.button11_Click);
      this.groupBox2.Controls.Add((Control) this.t_exchange_id);
      this.groupBox2.Controls.Add((Control) this.label21);
      this.groupBox2.Location = new Point(6, 1);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new Size(131, 52);
      this.groupBox2.TabIndex = 23;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "Exchange Information";
      this.t_exchange_id.Enabled = false;
      this.t_exchange_id.Location = new Point(56, 23);
      this.t_exchange_id.Name = "t_exchange_id";
      this.t_exchange_id.Size = new Size(69, 21);
      this.t_exchange_id.TabIndex = 19;
      this.t_exchange_id.TextAlign = HorizontalAlignment.Center;
      this.t_exchange_id.TextChanged += new EventHandler(this.t_exchange_id_TextChanged);
      this.label21.AutoSize = true;
      this.label21.Location = new Point(6, 26);
      this.label21.Name = "label21";
      this.label21.Size = new Size(52, 13);
      this.label21.TabIndex = 20;
      this.label21.Text = "Exc. ID : ";
      this.Column7.HeaderText = "";
      this.Column7.MinimumWidth = 20;
      this.Column7.Name = "Column7";
      this.Column7.Width = 20;
      this.ID.AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
      this.ID.HeaderText = "ID";
      this.ID.Name = "ID";
      this.ItemName.HeaderText = "ItemName";
      this.ItemName.Name = "ItemName";
      this.ItemName.ReadOnly = true;
      this.ItemName.Width = 81;
      this.NpcName.HeaderText = "NpcName";
      this.NpcName.Name = "NpcName";
      this.NpcName.Width = 77;
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.BackColor = Color.White;
      this.ClientSize = new Size(1132, 424);
      this.Controls.Add((Control) this.groupBox2);
      this.Controls.Add((Control) this.groupBox7);
      this.Controls.Add((Control) this.groupBox4);
      this.Controls.Add((Control) this.groupBox3);
      this.Controls.Add((Control) this.gb_npc);
      this.Controls.Add((Control) this.groupBox1);
      this.Font = new System.Drawing.Font("Tahoma", 8.25f, FontStyle.Regular, GraphicsUnit.Point, (byte) 222);
      this.Name = nameof (ExchangeExport_cHaR);
      this.Text = "Item Exchange";
      this.Load += new EventHandler(this.Form1_Load);
      this.groupBox4.ResumeLayout(false);
      this.groupBox4.PerformLayout();
      ((ISupportInitialize) this.pictureBox2).EndInit();
      this.groupBox3.ResumeLayout(false);
      this.groupBox3.PerformLayout();
      this.groupBox5.ResumeLayout(false);
      this.groupBox5.PerformLayout();
      ((ISupportInitialize) this.pictureBox7).EndInit();
      ((ISupportInitialize) this.pictureBox6).EndInit();
      ((ISupportInitialize) this.pictureBox5).EndInit();
      ((ISupportInitialize) this.pictureBox4).EndInit();
      ((ISupportInitialize) this.pictureBox3).EndInit();
      this.gb_npc.ResumeLayout(false);
      this.gb_npc.PerformLayout();
      ((ISupportInitialize) this.pc_npc).EndInit();
      this.groupBox1.ResumeLayout(false);
      ((ISupportInitialize) this.dgItems).EndInit();
      this.groupBox7.ResumeLayout(false);
      this.groupBox2.ResumeLayout(false);
      this.groupBox2.PerformLayout();
      this.ResumeLayout(false);
    }

    public class ticon
    {
      public int ItemID;
      public int FileID;
      public int Row;
      public int Col;
      public string Name;
      public string Desc;
    }
  }
}
