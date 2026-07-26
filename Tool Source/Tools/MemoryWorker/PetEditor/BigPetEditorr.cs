// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.MemoryWorker.PetEditor.BigPetEditorr
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using MySqlConnector;
using SlimDX;
using SlimDX.Direct3D9;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools.MemoryWorker.PetEditor
{
  public class BigPetEditorr : Form
  {
    private IContainer components = (IContainer) null;
    public static Connection connection = new Connection();
    private string Host = BigPetEditorr.connection.Settings.SqlHost;
    private string User = BigPetEditorr.connection.Settings.SqlUser;
    private string Password = BigPetEditorr.connection.Settings.SqlPassword;
    private string Database = BigPetEditorr.connection.Settings.SqlDatabase;
    public string _ClientPath = LcDevPack_TeamDamonA.Tools.MobEditor.connection.Settings.ClientPath;
    public float _UpDown = -1f;
    public DatabaseHandle databaseHandle = new DatabaseHandle();
    private ASCIIEncoding _Enc = new ASCIIEncoding();
    private Encoding encoding = Encoding.GetEncoding("ISO-8859-1");
    public int DEF_APET_NAME_LENGTH = 20;
    public int DEF_SMCFILE_LENGTH = 64;
    public int DEF_APET_ANI_LENGTH = 32;
    private MenuStrip menuStrip1;
    private ToolStripMenuItem fileToolStripMenuItem;
    private ToolStripMenuItem loadFromDatabaseToolStripMenuItem;
    private ToolStripSeparator toolStripSeparator1;
    private ToolStripMenuItem ExportToolStripMenuItem;
    private ToolStripSeparator toolStripSeparator2;
    private ToolStripMenuItem exitToolStripMenuItem;
    private GroupBox groupBox1;
    private Label label1;
    private TextBox txtSearch;
    private GroupBox groupBox2;
    private Button btnDelete;
    private Button btnAdd;
    private ListBox listBox1;
    private TabControl tabControl1;
    private TabPage tabPage1;
    private TabPage tabPage2;
    private GroupBox groupBox3;
    private Button button3;
    private Label label3;
    private Label label2;
    private CheckBox checkBox1;
    private TextBox txtID;
    private GroupBox groupBox7;
    private Label label51;
    private TextBox tbAniDamage1_2;
    private TextBox tbSmc1_2;
    private Label label65;
    private TextBox tbAniIdle1_2;
    private Label label49;
    private TextBox tbAniIdle2_2;
    private Label label54;
    private TextBox tbAniRun1_2;
    private Label label56;
    private TextBox tbSkillSummon1_2;
    private TextBox tbAniWalk1_2;
    private TextBox tbAniAttack1_2;
    private Label label58;
    private Label label60;
    private Label label50;
    private TextBox tbLevelUp1_2;
    private Label label62;
    private TextBox tbSpeed1_2;
    private TextBox tbAniAttack2_2;
    private Label label61;
    private Label label59;
    private TextBox tbAniDie1_2;
    private Label label57;
    private Label label63;
    private TextBox tbMount1_2;
    private GroupBox groupBox6;
    private TextBox tbSmc1_1;
    private Label label17;
    private TextBox tbAniAttack2_1;
    private Label label44;
    private TextBox tbSpeed1_1;
    private Label label48;
    private TextBox tbAniDamage1_1;
    private Label label45;
    private TextBox tbSkillSummon1_1;
    private Label label64;
    private TextBox tbAniAttack1_1;
    private Label label52;
    private TextBox tbAniIdle2_1;
    private Label label40;
    private TextBox tbMount1_1;
    private Label label55;
    private TextBox tbAniIdle1_1;
    private Label label31;
    private TextBox tbAniDie1_1;
    private TextBox tbAniWalk1_1;
    private Label label43;
    private Label label32;
    private Label label46;
    private TextBox tbAniRun1_1;
    private TextBox tbLevelUp1_1;
    private Label label53;
    private GroupBox groupBox5;
    private Label label47;
    private TextBox tbTransType;
    private TextBox tbTransStart;
    private Label label41;
    private TextBox tbTransEnd;
    private Label label42;
    private Label label33;
    private TextBox tbFlag;
    private Label label37;
    private Label label39;
    private TextBox tbStrong;
    private GroupBox groupBox4;
    private TextBox tbAttackSpeed;
    private Label label28;
    private TextBox tbDeadly;
    private Label label29;
    private TextBox tbMagicAvoid;
    private Label label25;
    private TextBox TbHitpoint;
    private Label label26;
    private TextBox tbAvoid;
    private Label label27;
    private TextBox tbmDefense;
    private Label label24;
    private TextBox tbAttack;
    private Label label20;
    private TextBox tbDefense;
    private Label label21;
    private TextBox tbmAttack;
    private Label label22;
    private TextBox tbAfterDead;
    private Label label23;
    private TextBox tbAiSlot;
    private Label label19;
    private TextBox tbDelay;
    private Label label18;
    private TextBox tbRecoveryMP;
    private TextBox tbRecoveryHP;
    private Label label16;
    private Label label15;
    private TextBox tbmaxStm;
    private Label label12;
    private TextBox tbmaxMP;
    private TextBox tbmaxHP;
    private TextBox tbmaxFaith;
    private Label label14;
    private Label label13;
    private Label label11;
    private TextBox tbConstitution;
    private TextBox tbIntelligence;
    private TextBox TbDexteriety;
    private Label label9;
    private Label label8;
    private Label label7;
    private TextBox tbStrength;
    private Label label6;
    private TextBox tbAwful;
    private Label label30;
    private Label label36;
    private TextBox tbNoraml;
    private Label label34;
    private TextBox tbWeak;
    private Label label38;
    private TextBox tbBasicSkill2;
    private TextBox tbBasicSkill1;
    private TextBox tbCritical;
    private Label label35;
    private GroupBox groupBox20;
    private CheckBox chk3D;
    private TrackBar slideLeftRight;
    private TrackBar slideUpDown;
    private TrackBar slideZoom;
    private Panel panel3DView;
    private PictureBox PbSelectID1;
    private PictureBox pictureBox1;
    private TextBox tbItemIndex;
    private Label label10;
    private TextBox tbType;
    private Label label5;
    private ComboBox comboBox1;
    private TextBox tbEnable;
    private Button btnCopy;
    private Button BtnReadSmc2;
    private Button BtnReadSmc;
    private TextBox txtName;
    private Button BtnAniWalk;
    private Button BtnAniIdle;
    private Button BtnAniDam;
    private Button BtnAniAttack1;
    private Button btnAniDie;
    private Button btnAniRun;
    private Button btnAniIdle2;
    private Button BtnAniAttack2_1;
    private Button btnAniIdle2_1;
    private Button btnAniRun_1;
    private Button btnAniDie_1;
    private Button BtnAniAttack1_1;
    private Button BtnAniDam_1;
    private Button BtnAniIdle1;
    private Button BtnAniWalk_1;
    private Button BtnAniAttack2;
    private Button btnLevelup2;
    private Button btnLevelup1;
    public Direct3D _Direct3D;
    public Device _Device;
    public float _Zoom;
    public float _LeftRight;
    public float _Rotation;
    public List<tMesh> _Models;
    private Timer timer1;
    private TextBox tbFileCol;
    private TextBox tbFileRow;
    private TextBox tbFileID;
    private Label Status;
    private Button button2;
    private Button button1;
    private GroupBox groupBox8;
    private Label label4;
    private TextBox t_tex1;
    private TextBox t_row1;
    private Label label66;
    private TextBox t_col1;
    private Label label67;
    private PictureBox pictureBox5;
    private PictureBox pictureBox4;
    private Label label68;
    private TextBox t_tex2;
    private TextBox t_row2;
    private Label label69;
    private TextBox t_col2;
    private Label label70;
    private CheckBox cbMount2;
    private CheckBox cbMount1;
    private TextBox tbItemExist;
    private bool doespetexist;
    private Label label71;
    private TabPage tabPage3;
    private GroupBox groupBox9;
    private TextBox tb_to_ev_id;
    private Label label72;
    private TextBox tb_ev_ID;
    private Label label74;
    private TextBox tb_ev_Level;
    private Label label73;
    private TextBox tb_ev_Faith;
    private Label label76;
    private TextBox tb_ev_Stemina;
    private Label label75;
    private TextBox tb_ev_order;
    private Label label79;
    private TextBox tb_ev_stat2;
    private Label label78;
    private TextBox tb_ev_stat1;
    private Label label77;
    private ComboBox flag;
    private Label label80;
    private TabPage tabPage4;
    private GroupBox groupBox10;
    private TextBox tb_exp_a_cooltime_rate;
    private Label label81;
    private TextBox tb_exp_a_cooltime;
    private Label label82;
    private TextBox tb_exp_a_acc_rate_param2;
    private Label label83;
    private TextBox tb_exp_a_acc_rate_param1;
    private Label label84;
    private TextBox tb_exp_a_max_acc_param2;
    private Label label85;
    private TextBox tb_exp_a_max_acc_param1;
    private Label label86;
    private TextBox tb_exp_a_pet_index;
    private Label label88;
    private TabPage tabPage5;
    private DataGridView dgItems;
    private DataGridViewTextBoxColumn a_pet_index;
    private DataGridViewTextBoxColumn a_max_acc_param1;
    private DataGridViewTextBoxColumn a_max_acc_param2;
    private DataGridViewTextBoxColumn a_acc_rate_param1;
    private DataGridViewTextBoxColumn a_acc_rate_param2;
    private DataGridViewTextBoxColumn a_cooltime;
    private DataGridViewTextBoxColumn a_cooltime_rate;
    private Button button12;
    private Button button9;
    private Button button6;
    private TextBox textBox8;
    private TextBox textBox9;
    private TextBox textBox10;
    private TextBox textBox11;
    private TabPage tabPage6;
    private DataGridView dataGridView1;
    private Button button4;
    private Button button5;
    private Button button7;
    private GroupBox groupBox11;
    private TextBox textBox6;
    private Label label93;
    private Label label94;
    private TextBox textBox7;
    private TextBox textBox4;
    private Label label91;
    private Label label92;
    private TextBox textBox5;
    private TextBox textBox1;
    private TextBox textBox3;
    private Label label87;
    private Label label90;
    private Label label89;
    private TextBox textBox2;
    private GroupBox groupBox12;
    private TextBox textBox12;
    private Label label95;
    private Label label96;
    private TextBox textBox13;
    private TextBox textBox14;
    private Label label97;
    private Label label98;
    private TextBox textBox15;
    private TextBox textBox16;
    private TextBox textBox17;
    private Label label99;
    private Label label100;
    private Label label101;
    private TextBox textBox18;
    private TextBox textBox19;
    private Label label102;
    private DataGridViewTextBoxColumn a_pet_index_evo;
    private DataGridViewTextBoxColumn a_ev_pet_index;
    private DataGridViewTextBoxColumn a_level;
    private DataGridViewTextBoxColumn a_stemina;
    private DataGridViewTextBoxColumn a_faith;
    private DataGridViewTextBoxColumn a_stat1;
    private DataGridViewTextBoxColumn a_stat2;
    private DataGridViewTextBoxColumn a_order;
    private ToolStripMenuItem bigpetlodToolStripMenuItem;
    public Encoding _enc;

    public BigPetEditorr() => this.InitializeComponent();

    private void IniRead()
    {
      IniFile iniFile = new IniFile(Application.StartupPath + "\\Config\\Settings.cfg");
      this.textBox8.Text = iniFile.IniReadValue("## MYSQL", "SQL_HOST");
      this.textBox9.Text = iniFile.IniReadValue("## MYSQL", "SQL_USER");
      this.textBox10.Text = iniFile.IniReadValue("## MYSQL", "SQL_PASSWORD");
      this.textBox11.Text = iniFile.IniReadValue("## MYSQL", "SQL_DATABASE");
    }

    private void BitPetEditor_Load(object sender, EventArgs e)
    {
      mySQL.SetConnection();
      this.InitializeDevice();
      this.listBox1.Items.Clear();
      new LoadFromDatabase().tPets_Import();
      new LoadFromDatabase().tPets_Evolution_Import();
      new LoadFromDatabase().tPets_Exp_Import();
      this.RefreshAll();
      this.label71.Text = "Pet Count: " + AllLists.tpet_MenuData.Count<t_attkpet>().ToString();
      this.listBox1.SelectedIndex = 0;
      this.FillGrid();
      this.FillGrid2();
    }

    private void LoadStartupString()
    {
      this.comboBox1.Items.AddRange(new object[3]
      {
        (object) "1 - Human",
        (object) "2 - Beast",
        (object) "3 - Demon"
      });
    }

    private void MakeLCModels(string SMCFile)
    {
      List<float> source1 = new List<float>();
      List<float> source2 = new List<float>();
      List<float> source3 = new List<float>();
      List<float> floatList1 = new List<float>();
      List<float> floatList2 = new List<float>();
      List<float> floatList3 = new List<float>();
      this._Models = new List<tMesh>();
      try
      {
        List<smcMesh> source4 = SMCReader.ReadFile(SMCFile);
        for (int index1 = 0; index1 < source4.Count<smcMesh>(); ++index1)
        {
          if (LCMeshReader.ReadFile(source4[index1].FileName))
          {
            tMeshContainer pMesh = LCMeshReader.pMesh;
            source1.Add(((IEnumerable<tVertex3f>) pMesh.Vertices).Max<tVertex3f>((System.Func<tVertex3f, float>) (p => p.X)));
            source2.Add(((IEnumerable<tVertex3f>) pMesh.Vertices).Max<tVertex3f>((System.Func<tVertex3f, float>) (p => p.Y)));
            source3.Add(((IEnumerable<tVertex3f>) pMesh.Vertices).Max<tVertex3f>((System.Func<tVertex3f, float>) (p => p.Z)));
            floatList1.Add(((IEnumerable<tVertex3f>) pMesh.Vertices).Min<tVertex3f>((System.Func<tVertex3f, float>) (p => p.X)));
            floatList2.Add(((IEnumerable<tVertex3f>) pMesh.Vertices).Min<tVertex3f>((System.Func<tVertex3f, float>) (p => p.Y)));
            floatList3.Add(((IEnumerable<tVertex3f>) pMesh.Vertices).Min<tVertex3f>((System.Func<tVertex3f, float>) (p => p.Z)));
            for (int index2 = 0; index2 < ((IEnumerable<tMeshObject>) pMesh.Objects).Count<tMeshObject>(); ++index2)
            {
              int toVert = (int) pMesh.Objects[index2].ToVert;
              int faceCount = (int) pMesh.Objects[index2].FaceCount;
              short[] faces = pMesh.Objects[index2].GetFaces();
              CustomVertex.PositionNormalTextured[] positionNormalTexturedArray = new CustomVertex.PositionNormalTextured[toVert];
              int fromVert = (int) pMesh.Objects[index2].FromVert;
              for (int index3 = 0; (long) index3 < (long) pMesh.Objects[index2].ToVert; ++index3)
              {
                positionNormalTexturedArray[index3].Position = new Vector3(pMesh.Vertices[fromVert].X, pMesh.Vertices[fromVert].Y, pMesh.Vertices[fromVert].Z);
                positionNormalTexturedArray[index3].Normal = new Vector3(pMesh.Normals[fromVert].X, pMesh.Normals[fromVert].Y, pMesh.Normals[fromVert].Z);
                try
                {
                  positionNormalTexturedArray[index3].Texture = new Vector2(pMesh.UVMaps[0].Coords[fromVert].U, pMesh.UVMaps[0].Coords[fromVert].V);
                }
                catch
                {
                  positionNormalTexturedArray[index3].Texture = new Vector2(0.0f, 0.0f);
                }
                ++fromVert;
              }
              VertexBuffer vertexBuffer = new VertexBuffer(this._Device, ((IEnumerable<CustomVertex.PositionNormalTextured>) positionNormalTexturedArray).Count<CustomVertex.PositionNormalTextured>() * 32, Usage.None, VertexFormat.PositionNormal | VertexFormat.Texture1, Pool.Default);
              Mesh mesh = new Mesh(this._Device, ((IEnumerable<short>) faces).Count<short>() / 3, ((IEnumerable<CustomVertex.PositionNormalTextured>) positionNormalTexturedArray).Count<CustomVertex.PositionNormalTextured>(), MeshFlags.Managed, VertexFormat.PositionNormal | VertexFormat.Texture1);
              DataStream dataStream1;
              using (dataStream1 = mesh.VertexBuffer.Lock(0, ((IEnumerable<CustomVertex.PositionNormalTextured>) positionNormalTexturedArray).Count<CustomVertex.PositionNormalTextured>() * 32, LockFlags.None))
              {
                dataStream1.WriteRange<CustomVertex.PositionNormalTextured>(positionNormalTexturedArray);
                mesh.VertexBuffer.Unlock();
              }
              DataStream dataStream2;
              using (dataStream2 = mesh.IndexBuffer.Lock(0, ((IEnumerable<short>) faces).Count<short>() * 2, LockFlags.None))
              {
                dataStream2.WriteRange<short>(faces);
                mesh.IndexBuffer.Unlock();
              }
              if (((IEnumerable<tMeshJointWeights>) pMesh.Weights).Count<tMeshJointWeights>() != 0)
              {
                string[] strArray = new string[((IEnumerable<tMeshJointWeights>) pMesh.Weights).Count<tMeshJointWeights>()];
                List<int>[] source5 = new List<int>[((IEnumerable<tMeshJointWeights>) pMesh.Weights).Count<tMeshJointWeights>()];
                List<float>[] floatListArray = new List<float>[((IEnumerable<tMeshJointWeights>) pMesh.Weights).Count<tMeshJointWeights>()];
                for (int index4 = 0; index4 < ((IEnumerable<tMeshJointWeights>) pMesh.Weights).Count<tMeshJointWeights>(); ++index4)
                {
                  strArray[index4] = this._Enc.GetString(pMesh.Weights[index4].JointName);
                  source5[index4] = new List<int>();
                  floatListArray[index4] = new List<float>();
                  for (int index5 = 0; index5 < ((IEnumerable<tMeshWeightsMap>) pMesh.Weights[index4].WeightsMap).Count<tMeshWeightsMap>(); ++index5)
                  {
                    source5[index4].Add(pMesh.Weights[index4].WeightsMap[index5].Index);
                    floatListArray[index4].Add(pMesh.Weights[index4].WeightsMap[index5].Weight);
                  }
                }
                mesh.SkinInfo = new SkinInfo(((IEnumerable<CustomVertex.PositionNormalTextured>) positionNormalTexturedArray).Count<CustomVertex.PositionNormalTextured>(), VertexFormat.PositionNormal | VertexFormat.Texture1, (int) pMesh.HeaderInfo.JointCount);
                for (int bone = 0; bone < ((IEnumerable<List<int>>) source5).Count<List<int>>(); ++bone)
                {
                  mesh.SkinInfo.SetBoneName(bone, strArray[bone]);
                  mesh.SkinInfo.SetBoneInfluence(bone, source5[bone].ToArray(), floatListArray[bone].ToArray());
                }
              }
              mesh.GenerateAdjacency(0.5f);
              mesh.ComputeNormals();
              Texture texture = (Texture) null;
              string objName = this._Enc.GetString(pMesh.Objects[index2].Textures[0].InternalName);
              int index6 = source4[index1].Object.FindIndex((Predicate<smcObject>) (x => x.Name.Equals(objName)));
              if (index6 != -1)
                texture = this.GetTextureFromFile(source4[index1].Object[index6].Texture);
              this._Models.Add(new tMesh(mesh, texture));
            }
          }
        }
      }
      catch
      {
      }
      try
      {
        this._Zoom = ((IEnumerable<float>) new float[3]
        {
          source1.Max(),
          source2.Max(),
          source3.Max()
        }).Max() * 3f;
      }
      catch
      {
      }
      this.slideZoom.Value = (int) this._Zoom * 100;
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

    private SlimDX.Direct3D9.Format ConvFormat(texFormat tFormat)
    {
      SlimDX.Direct3D9.Format format = SlimDX.Direct3D9.Format.Unknown;
      switch (tFormat)
      {
        case texFormat.RGB:
          return SlimDX.Direct3D9.Format.R8G8B8;
        case texFormat.ARGB:
          return SlimDX.Direct3D9.Format.A8R8G8B8;
        case texFormat.DXT1:
          return SlimDX.Direct3D9.Format.Dxt1;
        case texFormat.DXT3:
          return SlimDX.Direct3D9.Format.Dxt3;
        default:
          return format;
      }
    }

    private Texture BuildTexture(byte[] imageData, SlimDX.Direct3D9.Format imageFormat, int width, int height)
    {
      switch (imageFormat)
      {
        case SlimDX.Direct3D9.Format.R8G8B8:
          MemoryStream memoryStream1;
          using (memoryStream1 = new MemoryStream())
          {
            Tex.makeRGB8(imageData, width, height).Save((Stream) memoryStream1, ImageFormat.Bmp);
            memoryStream1.Write(imageData, 0, imageData.Length);
            memoryStream1.Position = 0L;
            return Texture.FromStream(this._Device, (Stream) memoryStream1, width, height, 0, Usage.SoftwareProcessing, SlimDX.Direct3D9.Format.A8B8G8R8, Pool.Default, SlimDX.Direct3D9.Filter.None, SlimDX.Direct3D9.Filter.None, 0);
          }
        case SlimDX.Direct3D9.Format.A8R8G8B8:
          MemoryStream memoryStream2;
          using (memoryStream2 = new MemoryStream())
          {
            Tex.makeRGB(imageData, width, height).Save((Stream) memoryStream2, ImageFormat.Bmp);
            memoryStream2.Write(imageData, 0, imageData.Length);
            memoryStream2.Position = 0L;
            return Texture.FromStream(this._Device, (Stream) memoryStream2, width, height, 0, Usage.SoftwareProcessing, SlimDX.Direct3D9.Format.A8B8G8R8, Pool.Default, SlimDX.Direct3D9.Filter.None, SlimDX.Direct3D9.Filter.None, 0);
          }
        default:
          Texture texture = new Texture(this._Device, width, height, 0, Usage.None, imageFormat, Pool.Managed);
          using (Stream data = (Stream) texture.LockRectangle(0, LockFlags.None).Data)
          {
            data.Write(imageData, 0, ((IEnumerable<byte>) imageData).Count<byte>());
            texture.UnlockRectangle(0);
          }
          return texture;
      }
    }

    private Texture GetTextureFromFile(string FileName)
    {
      Texture textureFromFile = (Texture) null;
      if (File.Exists(FileName))
      {
        Tex.ReadFile(FileName);
        SlimDX.Direct3D9.Format imageFormat = this.ConvFormat(Tex.GetFormat());
        textureFromFile = this.BuildTexture(Tex.lcTex.imageData[0], imageFormat, (int) Tex.lcTex.Header.Width, (int) Tex.lcTex.Header.Height);
      }
      return textureFromFile;
    }

    private void slideZoom_Scroll(object sender, EventArgs e)
    {
      this._Zoom = (float) this.slideZoom.Value / 100f;
    }

    private void slideUpDown_Scroll(object sender, EventArgs e)
    {
      this._UpDown = (float) this.slideUpDown.Value / 1000f;
    }

    private void slideLeftRight_Scroll(object sender, EventArgs e)
    {
      this._LeftRight = (float) this.slideLeftRight.Value / 1000f;
    }

    private int GetID()
    {
      int result = -1;
      int.TryParse(this.listBox1.Text.Split(' ')[0], out result);
      return result;
    }

    public void Clean()
    {
      AllLists.tpet_MenuData.Clear();
      AllLists.tpet_Menu.Clear();
      this.listBox1.Items.Clear();
    }

    public void MakeList()
    {
      List<string> stringList = new List<string>();
      List<t_attkpet> all = AllLists.tpet_MenuData.FindAll((Predicate<t_attkpet>) (p => p.name.ToLower().Contains(this.txtName.Text.ToLower())));
      for (int index = 0; index < all.Count<t_attkpet>(); ++index)
        stringList.Add(all[index].index.ToString() + " - " + all[index].name.ToString());
      this.listBox1.Items.AddRange((object[]) stringList.ToArray());
    }

    private void AniFind(object sender, EventArgs e)
    {
      string str1 = Path.GetDirectoryName(this._ClientPath).Replace("Data", "").Replace("data", "");
      if (File.Exists(str1 + "\\" + this.tbSmc1_1.Text))
      {
        foreach (string readAllLine in File.ReadAllLines(str1 + "\\" + this.tbSmc1_1.Text))
        {
          if (readAllLine.Contains("ANIMSET"))
          {
            string str2 = str1 + "\\" + readAllLine.Split('"')[1];
            if (File.Exists(str2))
            {
              Animation_Picker animationPicker = (Animation_Picker) null;
              switch ((sender as Button).Name)
              {
                case "BtnAniAttack1":
                  animationPicker = new Animation_Picker(str2, "Attack");
                  break;
                case "BtnAniAttack2":
                  animationPicker = new Animation_Picker(str2, "Attack2");
                  break;
                case "BtnAniDam":
                  animationPicker = new Animation_Picker(str2, "Damage");
                  break;
                case "BtnAniIdle":
                  animationPicker = new Animation_Picker(str2, "Idle");
                  break;
                case "BtnAniWalk":
                  animationPicker = new Animation_Picker(str2, "Walk");
                  break;
                case "btnAniDie":
                  animationPicker = new Animation_Picker(str2, "Die");
                  break;
                case "btnAniIdle2":
                  animationPicker = new Animation_Picker(str2, "Idle2");
                  break;
                case "btnAniRun":
                  animationPicker = new Animation_Picker(str2, "Run");
                  break;
                case "btnLevelup1":
                  animationPicker = new Animation_Picker(str2, "levelup");
                  break;
                default:
                  int num = (int) MessageBox.Show("Not found : " + (sender as Button).Name);
                  break;
              }
              if (animationPicker.ShowDialog() == DialogResult.OK)
              {
                switch ((sender as Button).Name)
                {
                  case "BtnAniAttack1":
                    this.tbAniAttack1_1.Text = animationPicker.Animation;
                    this.tbAniAttack1_1.BackColor = Color.PaleTurquoise;
                    continue;
                  case "BtnAniAttack2":
                    this.tbAniAttack2_1.Text = animationPicker.Animation;
                    this.tbAniAttack2_1.BackColor = Color.PaleTurquoise;
                    continue;
                  case "BtnAniDam":
                    this.tbAniDamage1_1.Text = animationPicker.Animation;
                    this.tbAniDamage1_1.BackColor = Color.PaleTurquoise;
                    continue;
                  case "BtnAniIdle":
                    this.tbAniIdle1_1.Text = animationPicker.Animation;
                    this.tbAniIdle1_1.BackColor = Color.PaleTurquoise;
                    continue;
                  case "BtnAniWalk":
                    this.tbAniWalk1_1.Text = animationPicker.Animation;
                    this.tbAniWalk1_1.BackColor = Color.PaleTurquoise;
                    continue;
                  case "btnAniDie":
                    this.tbAniDie1_1.Text = animationPicker.Animation;
                    this.tbAniDie1_1.BackColor = Color.PaleTurquoise;
                    continue;
                  case "btnAniIdle2":
                    this.tbAniIdle2_1.Text = animationPicker.Animation;
                    this.tbAniIdle2_1.BackColor = Color.PaleTurquoise;
                    continue;
                  case "btnAniRun":
                    this.tbAniRun1_1.Text = animationPicker.Animation;
                    this.tbAniRun1_1.BackColor = Color.PaleTurquoise;
                    continue;
                  case "btnLevelup1":
                    this.tbLevelUp1_1.Text = animationPicker.Animation;
                    this.tbLevelUp1_1.BackColor = Color.PaleTurquoise;
                    continue;
                  default:
                    continue;
                }
              }
            }
            else
            {
              int num1 = (int) new CustomMessage("Not Found :" + str2).ShowDialog();
            }
          }
        }
      }
      else
        new CustomMessage("SMC File not found").Show();
    }

    private void AniFind2(object sender, EventArgs e)
    {
      string str1 = Path.GetDirectoryName(this._ClientPath).Replace("Data", "").Replace("data", "");
      if (File.Exists(str1 + "\\" + this.tbSmc1_2.Text))
      {
        foreach (string readAllLine in File.ReadAllLines(str1 + "\\" + this.tbSmc1_2.Text))
        {
          if (readAllLine.Contains("ANIMSET"))
          {
            string str2 = str1 + "\\" + readAllLine.Split('"')[1];
            if (File.Exists(str2))
            {
              Animation_Picker animationPicker = (Animation_Picker) null;
              switch ((sender as Button).Name)
              {
                case "BtnAniAttack1_1":
                  animationPicker = new Animation_Picker(str2, "Attack");
                  break;
                case "BtnAniAttack2_1":
                  animationPicker = new Animation_Picker(str2, "Attack2");
                  break;
                case "BtnAniDam_1":
                  animationPicker = new Animation_Picker(str2, "Damage");
                  break;
                case "BtnAniIdle1":
                  animationPicker = new Animation_Picker(str2, "Idle");
                  break;
                case "BtnAniWalk_1":
                  animationPicker = new Animation_Picker(str2, "Walk");
                  break;
                case "btnAniDie_1":
                  animationPicker = new Animation_Picker(str2, "Die");
                  break;
                case "btnAniIdle2_1":
                  animationPicker = new Animation_Picker(str2, "Idle2");
                  break;
                case "btnAniRun_1":
                  animationPicker = new Animation_Picker(str2, "Run");
                  break;
                case "btnLevelup2":
                  animationPicker = new Animation_Picker(str2, "levelup");
                  break;
                default:
                  int num = (int) MessageBox.Show("Not found : " + (sender as Button).Name);
                  break;
              }
              if (animationPicker.ShowDialog() == DialogResult.OK)
              {
                switch ((sender as Button).Name)
                {
                  case "BtnAniAttack1_":
                    this.tbAniAttack1_2.Text = animationPicker.Animation;
                    this.tbAniAttack1_2.BackColor = Color.PaleTurquoise;
                    continue;
                  case "BtnAniAttack2_1":
                    this.tbAniAttack2_2.Text = animationPicker.Animation;
                    this.tbAniAttack2_2.BackColor = Color.PaleTurquoise;
                    continue;
                  case "BtnAniDam_1":
                    this.tbAniDamage1_2.Text = animationPicker.Animation;
                    this.tbAniDamage1_2.BackColor = Color.PaleTurquoise;
                    continue;
                  case "BtnAniIdle1":
                    this.tbAniIdle1_2.Text = animationPicker.Animation;
                    this.tbAniDie1_2.BackColor = Color.PaleTurquoise;
                    continue;
                  case "BtnAniWalk_1":
                    this.tbAniWalk1_2.Text = animationPicker.Animation;
                    this.tbAniWalk1_2.BackColor = Color.PaleTurquoise;
                    continue;
                  case "btnAniDie_1":
                    this.tbAniDie1_2.Text = animationPicker.Animation;
                    this.tbAniDie1_2.BackColor = Color.PaleTurquoise;
                    continue;
                  case "btnAniIdle2_1":
                    this.tbAniIdle2_2.Text = animationPicker.Animation;
                    this.tbAniIdle2_2.BackColor = Color.PaleTurquoise;
                    continue;
                  case "btnAniRun_1":
                    this.tbAniRun1_2.Text = animationPicker.Animation;
                    this.tbAniRun1_2.BackColor = Color.PaleTurquoise;
                    continue;
                  case "btnLevelup2":
                    this.tbLevelUp1_2.Text = animationPicker.Animation;
                    this.tbLevelUp1_2.BackColor = Color.PaleTurquoise;
                    continue;
                  default:
                    continue;
                }
              }
            }
            else
            {
              int num1 = (int) new CustomMessage("Not Found :" + str2).ShowDialog();
            }
          }
        }
      }
      else
        new CustomMessage("SMC File not found").Show();
    }

    private void RefreshAll()
    {
      this.listBox1.Items.Clear();
      List<int> SortedIDs = new List<int>();
      for (int index = 0; index < AllLists.tpet_MenuData.Count<t_attkpet>(); ++index)
        SortedIDs.Add(AllLists.tpet_MenuData[index].index);
      SortedIDs.Sort();
      for (int a = 0; a < SortedIDs.Count<int>(); a++)
      {
        int index = AllLists.tpet_MenuData.FindIndex((Predicate<t_attkpet>) (p => p.index.Equals(SortedIDs[a])));
        if (index != -1)
          this.listBox1.Items.Add((object) (AllLists.tpet_MenuData[index].index.ToString() + " - " + AllLists.tpet_MenuData[index].name));
      }
    }

    private void IconPet()
    {
      foreach (DataRow row in (InternalDataCollectionBase) mySQL.GetFromQuery("select a_index, a_texture_id, a_texture_row, a_texture_col FROM t_item WHERE a_index ='" + this.tbItemIndex.Text + "';").Rows)
      {
        this.tbFileID.Text = Convert.ToString(row["a_texture_id"]);
        this.tbFileRow.Text = Convert.ToString(row["a_texture_row"]);
        this.tbFileCol.Text = Convert.ToString(row["a_texture_col"]);
      }
    }

    private void loadFromDatabaseToolStripMenuItem_Click(object sender, EventArgs e)
    {
      this.listBox1.Items.Clear();
      new LoadFromDatabase().tPets_Import();
      this.RefreshAll();
    }

    private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      int PetID = this.GetID();
      if (PetID == -1)
        return;
      t_attkpet tAttkpet = AllLists.tpet_MenuData.Find((Predicate<t_attkpet>) (p => p.index.Equals(PetID)));
      if (tAttkpet == null)
        return;
      this.textBox1.Text = tAttkpet.index.ToString();
      this.textBox16.Text = tAttkpet.index.ToString();
      this.ResetTbBackGround();
      this.Status.Text = "";
      this.tbItemExist.Text = "";
      this.txtID.Text = tAttkpet.index.ToString();
      this.tbEnable.Text = tAttkpet.enable.ToString();
      this.txtName.Text = tAttkpet.name.ToString();
      this.tbType.Text = tAttkpet.type.ToString();
      this.IsPetInDB();
      this.comboBox1.SelectedIndex = tAttkpet.type - 1;
      if (Convert.ToInt16(this.tbType.Text) < (short) 1)
        this.comboBox1.SelectedIndex = 0;
      this.flag.SelectedIndex = tAttkpet.flag - 1;
      this.tbStrength.Text = tAttkpet.str.ToString();
      this.tbConstitution.Text = tAttkpet.con.ToString();
      this.TbDexteriety.Text = tAttkpet.dex.ToString();
      this.tbIntelligence.Text = tAttkpet.intel.ToString();
      this.tbItemIndex.Text = tAttkpet.itemidx.ToString();
      this.tbmaxFaith.Text = tAttkpet.maxFaith.ToString();
      this.tbmaxStm.Text = tAttkpet.maxStm.ToString();
      this.tbmaxHP.Text = tAttkpet.maxHP.ToString();
      this.tbmaxMP.Text = tAttkpet.maxMP.ToString();
      this.tbRecoveryHP.Text = tAttkpet.recoverHP.ToString();
      this.tbRecoveryMP.Text = tAttkpet.recoverMP.ToString();
      this.tbDelay.Text = tAttkpet.delay.ToString();
      this.tbAiSlot.Text = tAttkpet.AISlot.ToString();
      this.tbAfterDead.Text = tAttkpet.afterDead.ToString();
      this.tbAttack.Text = tAttkpet.attack.ToString();
      this.tbDefense.Text = tAttkpet.defense.ToString();
      this.tbmAttack.Text = tAttkpet.mAttack.ToString();
      this.tbmDefense.Text = tAttkpet.mDefense.ToString();
      this.TbHitpoint.Text = tAttkpet.avoidPoint.ToString();
      this.tbAvoid.Text = tAttkpet.avoidPoint.ToString();
      this.tbMagicAvoid.Text = tAttkpet.mavoidPoint.ToString();
      this.tbAttackSpeed.Text = tAttkpet.attackSpeed.ToString();
      this.tbDeadly.Text = tAttkpet.Deadly.ToString();
      this.tbCritical.Text = tAttkpet.Critical.ToString();
      this.tbAwful.Text = tAttkpet.awful.ToString();
      this.tbStrong.Text = tAttkpet.strong.ToString();
      this.tbNoraml.Text = tAttkpet.normal.ToString();
      this.tbWeak.Text = tAttkpet.weak.ToString();
      this.tbBasicSkill1.Text = tAttkpet.bagicSkill1.ToString();
      this.tbBasicSkill2.Text = tAttkpet.bagicSkill2.ToString();
      this.tbFlag.Text = tAttkpet.flag.ToString();
      this.tbTransType.Text = tAttkpet.transType.ToString();
      this.tbTransStart.Text = tAttkpet.transStart.ToString();
      this.tbTransEnd.Text = tAttkpet.transEnd.ToString();
      this.tbSmc1_1.Text = tAttkpet.smcFileName1;
      this.tbAniIdle1_1.Text = tAttkpet.aniIdle1;
      this.tbAniIdle2_1.Text = tAttkpet.aniIdle1_2;
      this.tbAniAttack1_1.Text = tAttkpet.aniAttack1;
      this.tbAniAttack2_1.Text = tAttkpet.aniAttack1_2;
      this.tbAniDamage1_1.Text = tAttkpet.aniDamage1;
      this.tbAniDie1_1.Text = tAttkpet.aniDie1;
      this.tbAniWalk1_1.Text = tAttkpet.aniWalk1;
      this.tbAniRun1_1.Text = tAttkpet.aniRun1;
      this.tbLevelUp1_1.Text = tAttkpet.aniLevelup1;
      this.tbMount1_1.Text = tAttkpet.mount1.ToString();
      if (this.tbMount1_1.Text == "1")
      {
        this.cbMount1.Text = "Mount";
        this.cbMount1.Checked = true;
        this.cbMount1.BackColor = Color.LimeGreen;
      }
      else
      {
        this.cbMount1.Text = "NotMount";
        this.cbMount1.Checked = false;
        this.cbMount1.BackColor = Color.Red;
      }
      this.tbSkillSummon1_1.Text = tAttkpet.summonSkill1.ToString();
      this.tbSpeed1_1.Text = tAttkpet.speed1.ToString();
      this.tbSmc1_2.Text = tAttkpet.smcFileName2.ToString();
      this.tbAniDie1_2.Text = tAttkpet.aniIdle2.ToString();
      this.tbAniIdle1_2.Text = tAttkpet.aniIdle2.ToString();
      this.tbAniIdle2_2.Text = tAttkpet.aniIdle2_2.ToString();
      this.tbAniAttack1_2.Text = tAttkpet.aniAttack2.ToString();
      this.tbAniAttack2_2.Text = tAttkpet.aniAttack2_2.ToString();
      this.tbAniDamage1_2.Text = tAttkpet.aniDamage1_2.ToString();
      this.tbAniDie1_2.Text = tAttkpet.aniDie1_2.ToString();
      this.tbAniWalk1_2.Text = tAttkpet.aniWalk1_2.ToString();
      this.tbAniRun1_2.Text = tAttkpet.aniRun1_2.ToString();
      this.tbLevelUp1_2.Text = tAttkpet.aniLevelup1_2.ToString();
      this.tbMount1_2.Text = tAttkpet.mount1_2.ToString();
      if (this.tbMount1_2.Text == "1")
      {
        this.cbMount2.Text = "Mount";
        this.cbMount2.Checked = true;
        this.cbMount2.BackColor = Color.LimeGreen;
      }
      else
      {
        this.cbMount2.Text = "NotMount";
        this.cbMount2.Checked = false;
        this.cbMount2.BackColor = Color.Red;
      }
      this.tbSkillSummon1_2.Text = tAttkpet.summonSkill1_2.ToString();
      this.tbSpeed1_2.Text = tAttkpet.speed1_2.ToString();
      if (this.chk3D.Checked && File.Exists(this._ClientPath + this.tbSmc1_1.Text))
      {
        Console.WriteLine("Create Model > " + this._ClientPath + this.tbSmc1_1.Text);
        this.MakeLCModels(this._ClientPath + this.tbSmc1_1.Text);
      }
      try
      {
        this.pictureBox1.Image = (Image) this.databaseHandle.IconItem(int.Parse(this.tbFileID.Text), int.Parse(this.tbFileRow.Text), int.Parse(this.tbFileCol.Text));
      }
      catch
      {
      }
      try
      {
      }
      catch
      {
      }
      try
      {
      }
      catch
      {
      }
      if (tAttkpet.enable == 1)
      {
        this.checkBox1.Checked = true;
        this.checkBox1.BackColor = Color.LimeGreen;
      }
      else
      {
        this.checkBox1.Checked = false;
        this.checkBox1.BackColor = Color.Red;
      }
      this.groupBox9.Enabled = false;
      int PetID_ev = Convert.ToInt32(this.txtID.Text);
      int index1 = AllLists.tpet_ev_MenuData.FindIndex((Predicate<BigpetEv>) (p => p.APetIdx.Equals(PetID_ev)));
      if (index1 != -1)
      {
        this.groupBox9.Enabled = true;
        this.tb_ev_ID.Text = Convert.ToString(AllLists.tpet_ev_MenuData[index1].APetIdx);
        this.tb_ev_Level.Text = Convert.ToString(AllLists.tpet_ev_MenuData[index1].Level);
        this.tb_ev_Stemina.Text = Convert.ToString(AllLists.tpet_ev_MenuData[index1].Stemina);
        this.tb_ev_Faith.Text = Convert.ToString(AllLists.tpet_ev_MenuData[index1].Faith);
        this.tb_ev_stat1.Text = Convert.ToString(AllLists.tpet_ev_MenuData[index1].a_stat1);
        this.tb_ev_stat2.Text = Convert.ToString(AllLists.tpet_ev_MenuData[index1].a_stat2);
        this.tb_to_ev_id.Text = Convert.ToString(AllLists.tpet_ev_MenuData[index1].a_ev_pet_index);
        this.tb_ev_order.Text = Convert.ToString(AllLists.tpet_ev_MenuData[index1].a_order);
      }
      this.groupBox10.Enabled = false;
      int PetID_Exp = Convert.ToInt32(this.txtID.Text);
      int index2 = AllLists.tpet_exp_MenuData.FindIndex((Predicate<BigpetExp>) (p => p.a_pet_index.Equals(PetID_Exp)));
      if (index2 == -1)
        return;
      this.groupBox10.Enabled = true;
      this.tb_exp_a_pet_index.Text = Convert.ToString(AllLists.tpet_exp_MenuData[index2].a_pet_index);
      this.tb_exp_a_max_acc_param1.Text = Convert.ToString(AllLists.tpet_exp_MenuData[index2].a_max_acc_param1);
      this.tb_exp_a_max_acc_param2.Text = Convert.ToString(AllLists.tpet_exp_MenuData[index2].a_max_acc_param2);
      this.tb_exp_a_acc_rate_param1.Text = Convert.ToString(AllLists.tpet_exp_MenuData[index2].a_acc_rate_param1);
      this.tb_exp_a_acc_rate_param2.Text = Convert.ToString(AllLists.tpet_exp_MenuData[index2].a_acc_rate_param2);
      this.tb_exp_a_cooltime.Text = Convert.ToString(AllLists.tpet_exp_MenuData[index2].a_cooltime);
      this.tb_exp_a_cooltime_rate.Text = Convert.ToString(AllLists.tpet_exp_MenuData[index2].a_cooltime_rate);
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
      this.menuStrip1 = new MenuStrip();
      this.fileToolStripMenuItem = new ToolStripMenuItem();
      this.loadFromDatabaseToolStripMenuItem = new ToolStripMenuItem();
      this.toolStripSeparator1 = new ToolStripSeparator();
      this.ExportToolStripMenuItem = new ToolStripMenuItem();
      this.toolStripSeparator2 = new ToolStripSeparator();
      this.exitToolStripMenuItem = new ToolStripMenuItem();
      this.groupBox1 = new GroupBox();
      this.label1 = new Label();
      this.txtSearch = new TextBox();
      this.groupBox2 = new GroupBox();
      this.btnCopy = new Button();
      this.btnDelete = new Button();
      this.btnAdd = new Button();
      this.listBox1 = new ListBox();
      this.tabControl1 = new TabControl();
      this.tabPage1 = new TabPage();
      this.tbItemExist = new TextBox();
      this.tbFileCol = new TextBox();
      this.tbFileRow = new TextBox();
      this.tbFileID = new TextBox();
      this.tbEnable = new TextBox();
      this.tbType = new TextBox();
      this.PbSelectID1 = new PictureBox();
      this.pictureBox1 = new PictureBox();
      this.tbItemIndex = new TextBox();
      this.label10 = new Label();
      this.groupBox20 = new GroupBox();
      this.chk3D = new CheckBox();
      this.slideLeftRight = new TrackBar();
      this.slideUpDown = new TrackBar();
      this.slideZoom = new TrackBar();
      this.panel3DView = new Panel();
      this.label33 = new Label();
      this.tbFlag = new TextBox();
      this.label37 = new Label();
      this.label39 = new Label();
      this.tbStrong = new TextBox();
      this.groupBox4 = new GroupBox();
      this.tbAttackSpeed = new TextBox();
      this.label28 = new Label();
      this.tbDeadly = new TextBox();
      this.label29 = new Label();
      this.tbMagicAvoid = new TextBox();
      this.label25 = new Label();
      this.TbHitpoint = new TextBox();
      this.label26 = new Label();
      this.tbAvoid = new TextBox();
      this.label27 = new Label();
      this.tbmDefense = new TextBox();
      this.label24 = new Label();
      this.tbAttack = new TextBox();
      this.label20 = new Label();
      this.tbDefense = new TextBox();
      this.label21 = new Label();
      this.tbmAttack = new TextBox();
      this.label22 = new Label();
      this.tbAfterDead = new TextBox();
      this.label23 = new Label();
      this.tbAiSlot = new TextBox();
      this.label19 = new Label();
      this.tbDelay = new TextBox();
      this.label18 = new Label();
      this.tbRecoveryMP = new TextBox();
      this.tbRecoveryHP = new TextBox();
      this.label16 = new Label();
      this.label15 = new Label();
      this.tbmaxStm = new TextBox();
      this.label12 = new Label();
      this.tbmaxMP = new TextBox();
      this.tbmaxHP = new TextBox();
      this.tbmaxFaith = new TextBox();
      this.label14 = new Label();
      this.label13 = new Label();
      this.label11 = new Label();
      this.tbConstitution = new TextBox();
      this.tbIntelligence = new TextBox();
      this.TbDexteriety = new TextBox();
      this.label9 = new Label();
      this.label8 = new Label();
      this.label7 = new Label();
      this.tbStrength = new TextBox();
      this.label6 = new Label();
      this.tbAwful = new TextBox();
      this.label30 = new Label();
      this.label36 = new Label();
      this.tbNoraml = new TextBox();
      this.label34 = new Label();
      this.tbWeak = new TextBox();
      this.label38 = new Label();
      this.tbBasicSkill2 = new TextBox();
      this.tbBasicSkill1 = new TextBox();
      this.tbCritical = new TextBox();
      this.label35 = new Label();
      this.groupBox3 = new GroupBox();
      this.flag = new ComboBox();
      this.label80 = new Label();
      this.label5 = new Label();
      this.comboBox1 = new ComboBox();
      this.checkBox1 = new CheckBox();
      this.txtID = new TextBox();
      this.txtName = new TextBox();
      this.label3 = new Label();
      this.label2 = new Label();
      this.tabPage2 = new TabPage();
      this.groupBox8 = new GroupBox();
      this.label68 = new Label();
      this.t_tex2 = new TextBox();
      this.t_row2 = new TextBox();
      this.label69 = new Label();
      this.t_col2 = new TextBox();
      this.label70 = new Label();
      this.label4 = new Label();
      this.t_tex1 = new TextBox();
      this.t_row1 = new TextBox();
      this.label66 = new Label();
      this.t_col1 = new TextBox();
      this.label67 = new Label();
      this.groupBox7 = new GroupBox();
      this.cbMount2 = new CheckBox();
      this.pictureBox5 = new PictureBox();
      this.button2 = new Button();
      this.btnLevelup2 = new Button();
      this.BtnAniAttack2_1 = new Button();
      this.btnAniIdle2_1 = new Button();
      this.btnAniRun_1 = new Button();
      this.btnAniDie_1 = new Button();
      this.BtnAniAttack1_1 = new Button();
      this.BtnAniDam_1 = new Button();
      this.BtnAniIdle1 = new Button();
      this.BtnAniWalk_1 = new Button();
      this.BtnReadSmc2 = new Button();
      this.label51 = new Label();
      this.tbAniDamage1_2 = new TextBox();
      this.tbSmc1_2 = new TextBox();
      this.label65 = new Label();
      this.tbAniIdle1_2 = new TextBox();
      this.label49 = new Label();
      this.tbAniIdle2_2 = new TextBox();
      this.label54 = new Label();
      this.tbAniRun1_2 = new TextBox();
      this.label56 = new Label();
      this.tbSkillSummon1_2 = new TextBox();
      this.tbAniWalk1_2 = new TextBox();
      this.tbAniAttack1_2 = new TextBox();
      this.label58 = new Label();
      this.label60 = new Label();
      this.label50 = new Label();
      this.tbLevelUp1_2 = new TextBox();
      this.label62 = new Label();
      this.tbSpeed1_2 = new TextBox();
      this.tbAniAttack2_2 = new TextBox();
      this.label61 = new Label();
      this.label59 = new Label();
      this.tbAniDie1_2 = new TextBox();
      this.label57 = new Label();
      this.label63 = new Label();
      this.tbMount1_2 = new TextBox();
      this.groupBox6 = new GroupBox();
      this.cbMount1 = new CheckBox();
      this.pictureBox4 = new PictureBox();
      this.button1 = new Button();
      this.btnLevelup1 = new Button();
      this.BtnAniAttack2 = new Button();
      this.btnAniIdle2 = new Button();
      this.btnAniRun = new Button();
      this.btnAniDie = new Button();
      this.BtnAniAttack1 = new Button();
      this.BtnAniDam = new Button();
      this.BtnAniIdle = new Button();
      this.BtnAniWalk = new Button();
      this.BtnReadSmc = new Button();
      this.tbSmc1_1 = new TextBox();
      this.label17 = new Label();
      this.tbAniAttack2_1 = new TextBox();
      this.label44 = new Label();
      this.tbSpeed1_1 = new TextBox();
      this.label48 = new Label();
      this.tbAniDamage1_1 = new TextBox();
      this.label45 = new Label();
      this.tbSkillSummon1_1 = new TextBox();
      this.label64 = new Label();
      this.tbAniAttack1_1 = new TextBox();
      this.label52 = new Label();
      this.tbAniIdle2_1 = new TextBox();
      this.label40 = new Label();
      this.tbMount1_1 = new TextBox();
      this.label55 = new Label();
      this.tbAniIdle1_1 = new TextBox();
      this.label31 = new Label();
      this.tbAniDie1_1 = new TextBox();
      this.tbAniWalk1_1 = new TextBox();
      this.label43 = new Label();
      this.label32 = new Label();
      this.label46 = new Label();
      this.tbAniRun1_1 = new TextBox();
      this.tbLevelUp1_1 = new TextBox();
      this.label53 = new Label();
      this.groupBox5 = new GroupBox();
      this.label47 = new Label();
      this.tbTransType = new TextBox();
      this.tbTransStart = new TextBox();
      this.label41 = new Label();
      this.tbTransEnd = new TextBox();
      this.label42 = new Label();
      this.tabPage3 = new TabPage();
      this.groupBox9 = new GroupBox();
      this.tb_ev_order = new TextBox();
      this.label79 = new Label();
      this.tb_ev_stat2 = new TextBox();
      this.label78 = new Label();
      this.tb_ev_stat1 = new TextBox();
      this.label77 = new Label();
      this.tb_ev_Faith = new TextBox();
      this.label76 = new Label();
      this.tb_ev_Stemina = new TextBox();
      this.label75 = new Label();
      this.tb_ev_Level = new TextBox();
      this.label73 = new Label();
      this.tb_to_ev_id = new TextBox();
      this.label72 = new Label();
      this.tb_ev_ID = new TextBox();
      this.label74 = new Label();
      this.tabPage4 = new TabPage();
      this.groupBox10 = new GroupBox();
      this.tb_exp_a_cooltime_rate = new TextBox();
      this.label81 = new Label();
      this.tb_exp_a_cooltime = new TextBox();
      this.label82 = new Label();
      this.tb_exp_a_acc_rate_param2 = new TextBox();
      this.label83 = new Label();
      this.tb_exp_a_acc_rate_param1 = new TextBox();
      this.label84 = new Label();
      this.tb_exp_a_max_acc_param2 = new TextBox();
      this.label85 = new Label();
      this.tb_exp_a_max_acc_param1 = new TextBox();
      this.label86 = new Label();
      this.tb_exp_a_pet_index = new TextBox();
      this.label88 = new Label();
      this.tabPage5 = new TabPage();
      this.button12 = new Button();
      this.button9 = new Button();
      this.button6 = new Button();
      this.groupBox11 = new GroupBox();
      this.textBox6 = new TextBox();
      this.label93 = new Label();
      this.label94 = new Label();
      this.textBox7 = new TextBox();
      this.textBox4 = new TextBox();
      this.label91 = new Label();
      this.label92 = new Label();
      this.textBox5 = new TextBox();
      this.textBox1 = new TextBox();
      this.textBox3 = new TextBox();
      this.label87 = new Label();
      this.label90 = new Label();
      this.label89 = new Label();
      this.textBox2 = new TextBox();
      this.dgItems = new DataGridView();
      this.a_pet_index = new DataGridViewTextBoxColumn();
      this.a_max_acc_param1 = new DataGridViewTextBoxColumn();
      this.a_max_acc_param2 = new DataGridViewTextBoxColumn();
      this.a_acc_rate_param1 = new DataGridViewTextBoxColumn();
      this.a_acc_rate_param2 = new DataGridViewTextBoxColumn();
      this.a_cooltime = new DataGridViewTextBoxColumn();
      this.a_cooltime_rate = new DataGridViewTextBoxColumn();
      this.tabPage6 = new TabPage();
      this.groupBox12 = new GroupBox();
      this.textBox19 = new TextBox();
      this.label102 = new Label();
      this.textBox12 = new TextBox();
      this.label95 = new Label();
      this.label96 = new Label();
      this.textBox13 = new TextBox();
      this.textBox14 = new TextBox();
      this.label97 = new Label();
      this.label98 = new Label();
      this.textBox15 = new TextBox();
      this.textBox16 = new TextBox();
      this.textBox17 = new TextBox();
      this.label99 = new Label();
      this.label100 = new Label();
      this.label101 = new Label();
      this.textBox18 = new TextBox();
      this.button4 = new Button();
      this.button5 = new Button();
      this.button7 = new Button();
      this.dataGridView1 = new DataGridView();
      this.a_pet_index_evo = new DataGridViewTextBoxColumn();
      this.a_ev_pet_index = new DataGridViewTextBoxColumn();
      this.a_level = new DataGridViewTextBoxColumn();
      this.a_stemina = new DataGridViewTextBoxColumn();
      this.a_faith = new DataGridViewTextBoxColumn();
      this.a_stat1 = new DataGridViewTextBoxColumn();
      this.a_stat2 = new DataGridViewTextBoxColumn();
      this.a_order = new DataGridViewTextBoxColumn();
      this.button3 = new Button();
      this.timer1 = new Timer(this.components);
      this.Status = new Label();
      this.label71 = new Label();
      this.textBox8 = new TextBox();
      this.textBox9 = new TextBox();
      this.textBox10 = new TextBox();
      this.textBox11 = new TextBox();
      this.bigpetlodToolStripMenuItem = new ToolStripMenuItem();
      this.menuStrip1.SuspendLayout();
      this.groupBox1.SuspendLayout();
      this.groupBox2.SuspendLayout();
      this.tabControl1.SuspendLayout();
      this.tabPage1.SuspendLayout();
      ((ISupportInitialize) this.PbSelectID1).BeginInit();
      ((ISupportInitialize) this.pictureBox1).BeginInit();
      this.groupBox20.SuspendLayout();
      this.slideLeftRight.BeginInit();
      this.slideUpDown.BeginInit();
      this.slideZoom.BeginInit();
      this.groupBox4.SuspendLayout();
      this.groupBox3.SuspendLayout();
      this.tabPage2.SuspendLayout();
      this.groupBox8.SuspendLayout();
      this.groupBox7.SuspendLayout();
      ((ISupportInitialize) this.pictureBox5).BeginInit();
      this.groupBox6.SuspendLayout();
      ((ISupportInitialize) this.pictureBox4).BeginInit();
      this.groupBox5.SuspendLayout();
      this.tabPage3.SuspendLayout();
      this.groupBox9.SuspendLayout();
      this.tabPage4.SuspendLayout();
      this.groupBox10.SuspendLayout();
      this.tabPage5.SuspendLayout();
      this.groupBox11.SuspendLayout();
      ((ISupportInitialize) this.dgItems).BeginInit();
      this.tabPage6.SuspendLayout();
      this.groupBox12.SuspendLayout();
      ((ISupportInitialize) this.dataGridView1).BeginInit();
      this.SuspendLayout();
      this.menuStrip1.BackColor = SystemColors.Window;
      this.menuStrip1.Items.AddRange(new ToolStripItem[1]
      {
        (ToolStripItem) this.fileToolStripMenuItem
      });
      this.menuStrip1.Location = new Point(0, 0);
      this.menuStrip1.Name = "menuStrip1";
      this.menuStrip1.Size = new Size(855, 24);
      this.menuStrip1.TabIndex = 0;
      this.menuStrip1.Text = "menuStrip1";
      this.fileToolStripMenuItem.DropDownItems.AddRange(new ToolStripItem[6]
      {
        (ToolStripItem) this.loadFromDatabaseToolStripMenuItem,
        (ToolStripItem) this.toolStripSeparator1,
        (ToolStripItem) this.ExportToolStripMenuItem,
        (ToolStripItem) this.bigpetlodToolStripMenuItem,
        (ToolStripItem) this.toolStripSeparator2,
        (ToolStripItem) this.exitToolStripMenuItem
      });
      this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
      this.fileToolStripMenuItem.Size = new Size(37, 20);
      this.fileToolStripMenuItem.Text = "File";
      this.loadFromDatabaseToolStripMenuItem.Name = "loadFromDatabaseToolStripMenuItem";
      this.loadFromDatabaseToolStripMenuItem.Size = new Size(182, 22);
      this.loadFromDatabaseToolStripMenuItem.Text = "Load From Database";
      this.loadFromDatabaseToolStripMenuItem.Click += new EventHandler(this.loadFromDatabaseToolStripMenuItem_Click);
      this.toolStripSeparator1.Name = "toolStripSeparator1";
      this.toolStripSeparator1.Size = new Size(179, 6);
      this.ExportToolStripMenuItem.Name = "ExportToolStripMenuItem";
      this.ExportToolStripMenuItem.Size = new Size(182, 22);
      this.ExportToolStripMenuItem.Text = "Export .lod";
      this.ExportToolStripMenuItem.Visible = false;
      this.ExportToolStripMenuItem.Click += new EventHandler(this.saveToolStripMenuItem_Click);
      this.toolStripSeparator2.Name = "toolStripSeparator2";
      this.toolStripSeparator2.Size = new Size(179, 6);
      this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
      this.exitToolStripMenuItem.Size = new Size(182, 22);
      this.exitToolStripMenuItem.Text = "Exit";
      this.groupBox1.Controls.Add((Control) this.label1);
      this.groupBox1.Controls.Add((Control) this.txtSearch);
      this.groupBox1.Location = new Point(12, 27);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new Size(215, 63);
      this.groupBox1.TabIndex = 1;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Search";
      this.label1.AutoSize = true;
      this.label1.Location = new Point(6, 28);
      this.label1.Name = "label1";
      this.label1.Size = new Size(31, 13);
      this.label1.TabIndex = 1;
      this.label1.Text = "Text:";
      this.txtSearch.BorderStyle = BorderStyle.FixedSingle;
      this.txtSearch.Location = new Point(43, 25);
      this.txtSearch.Name = "txtSearch";
      this.txtSearch.Size = new Size(166, 20);
      this.txtSearch.TabIndex = 0;
      this.groupBox2.Controls.Add((Control) this.btnCopy);
      this.groupBox2.Controls.Add((Control) this.btnDelete);
      this.groupBox2.Controls.Add((Control) this.btnAdd);
      this.groupBox2.Controls.Add((Control) this.listBox1);
      this.groupBox2.Location = new Point(12, 96);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new Size(215, 421);
      this.groupBox2.TabIndex = 2;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "Pets";
      this.btnCopy.BackColor = Color.Plum;
      this.btnCopy.FlatStyle = FlatStyle.Flat;
      this.btnCopy.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.control_add_blue;
      this.btnCopy.ImageAlign = ContentAlignment.MiddleLeft;
      this.btnCopy.Location = new Point(69, 390);
      this.btnCopy.Name = "btnCopy";
      this.btnCopy.Size = new Size(58, 27);
      this.btnCopy.TabIndex = 66;
      this.btnCopy.Text = "     Copy";
      this.btnCopy.UseVisualStyleBackColor = false;
      this.btnCopy.Click += new EventHandler(this.btnCopy_Click);
      this.btnDelete.BackColor = Color.LightCoral;
      this.btnDelete.FlatStyle = FlatStyle.Flat;
      this.btnDelete.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.delete;
      this.btnDelete.ImageAlign = ContentAlignment.MiddleLeft;
      this.btnDelete.Location = new Point(133, 390);
      this.btnDelete.Name = "btnDelete";
      this.btnDelete.Size = new Size(76, 27);
      this.btnDelete.TabIndex = 68;
      this.btnDelete.Text = "    Delete";
      this.btnDelete.UseVisualStyleBackColor = false;
      this.btnDelete.Click += new EventHandler(this.btnDelete_Click);
      this.btnAdd.BackColor = Color.Plum;
      this.btnAdd.FlatStyle = FlatStyle.Flat;
      this.btnAdd.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.control_add_blue;
      this.btnAdd.ImageAlign = ContentAlignment.MiddleLeft;
      this.btnAdd.Location = new Point(9, 390);
      this.btnAdd.Name = "btnAdd";
      this.btnAdd.Size = new Size(54, 27);
      this.btnAdd.TabIndex = 66;
      this.btnAdd.Text = "     Add";
      this.btnAdd.UseVisualStyleBackColor = false;
      this.btnAdd.Click += new EventHandler(this.btnAdd_Click);
      this.listBox1.FormattingEnabled = true;
      this.listBox1.Location = new Point(9, 19);
      this.listBox1.Name = "listBox1";
      this.listBox1.Size = new Size(200, 368);
      this.listBox1.TabIndex = 0;
      this.listBox1.SelectedIndexChanged += new EventHandler(this.listBox1_SelectedIndexChanged);
      this.tabControl1.Controls.Add((Control) this.tabPage1);
      this.tabControl1.Controls.Add((Control) this.tabPage2);
      this.tabControl1.Controls.Add((Control) this.tabPage3);
      this.tabControl1.Controls.Add((Control) this.tabPage4);
      this.tabControl1.Controls.Add((Control) this.tabPage5);
      this.tabControl1.Controls.Add((Control) this.tabPage6);
      this.tabControl1.Location = new Point(227, 27);
      this.tabControl1.Name = "tabControl1";
      this.tabControl1.SelectedIndex = 0;
      this.tabControl1.Size = new Size(628, 490);
      this.tabControl1.TabIndex = 3;
      this.tabPage1.BackColor = SystemColors.Control;
      this.tabPage1.Controls.Add((Control) this.tbItemExist);
      this.tabPage1.Controls.Add((Control) this.tbFileCol);
      this.tabPage1.Controls.Add((Control) this.tbFileRow);
      this.tabPage1.Controls.Add((Control) this.tbFileID);
      this.tabPage1.Controls.Add((Control) this.tbEnable);
      this.tabPage1.Controls.Add((Control) this.tbType);
      this.tabPage1.Controls.Add((Control) this.PbSelectID1);
      this.tabPage1.Controls.Add((Control) this.pictureBox1);
      this.tabPage1.Controls.Add((Control) this.tbItemIndex);
      this.tabPage1.Controls.Add((Control) this.label10);
      this.tabPage1.Controls.Add((Control) this.groupBox20);
      this.tabPage1.Controls.Add((Control) this.label33);
      this.tabPage1.Controls.Add((Control) this.tbFlag);
      this.tabPage1.Controls.Add((Control) this.label37);
      this.tabPage1.Controls.Add((Control) this.label39);
      this.tabPage1.Controls.Add((Control) this.tbStrong);
      this.tabPage1.Controls.Add((Control) this.groupBox4);
      this.tabPage1.Controls.Add((Control) this.tbAwful);
      this.tabPage1.Controls.Add((Control) this.label30);
      this.tabPage1.Controls.Add((Control) this.label36);
      this.tabPage1.Controls.Add((Control) this.tbNoraml);
      this.tabPage1.Controls.Add((Control) this.label34);
      this.tabPage1.Controls.Add((Control) this.tbWeak);
      this.tabPage1.Controls.Add((Control) this.label38);
      this.tabPage1.Controls.Add((Control) this.tbBasicSkill2);
      this.tabPage1.Controls.Add((Control) this.tbBasicSkill1);
      this.tabPage1.Controls.Add((Control) this.tbCritical);
      this.tabPage1.Controls.Add((Control) this.label35);
      this.tabPage1.Controls.Add((Control) this.groupBox3);
      this.tabPage1.Location = new Point(4, 22);
      this.tabPage1.Name = "tabPage1";
      this.tabPage1.Padding = new Padding(3);
      this.tabPage1.Size = new Size(620, 464);
      this.tabPage1.TabIndex = 0;
      this.tabPage1.Text = "Basic";
      this.tbItemExist.Location = new Point(147, 2);
      this.tbItemExist.Name = "tbItemExist";
      this.tbItemExist.Size = new Size(26, 20);
      this.tbItemExist.TabIndex = 116;
      this.tbItemExist.Visible = false;
      this.tbFileCol.Location = new Point(343, 1);
      this.tbFileCol.Name = "tbFileCol";
      this.tbFileCol.Size = new Size(26, 20);
      this.tbFileCol.TabIndex = 115;
      this.tbFileCol.Visible = false;
      this.tbFileRow.Location = new Point(311, 2);
      this.tbFileRow.Name = "tbFileRow";
      this.tbFileRow.Size = new Size(26, 20);
      this.tbFileRow.TabIndex = 114;
      this.tbFileRow.Visible = false;
      this.tbFileID.Location = new Point(279, 2);
      this.tbFileID.Name = "tbFileID";
      this.tbFileID.Size = new Size(26, 20);
      this.tbFileID.TabIndex = 113;
      this.tbFileID.Visible = false;
      this.tbEnable.Location = new Point(225, 2);
      this.tbEnable.Name = "tbEnable";
      this.tbEnable.Size = new Size(27, 20);
      this.tbEnable.TabIndex = 112;
      this.tbEnable.Visible = false;
      this.tbType.Location = new Point(181, 3);
      this.tbType.Name = "tbType";
      this.tbType.Size = new Size(27, 20);
      this.tbType.TabIndex = 11;
      this.tbType.Visible = false;
      this.tbType.TextChanged += new EventHandler(this.tbType_TextChanged);
      this.PbSelectID1.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.oie_transparent;
      this.PbSelectID1.BackgroundImageLayout = ImageLayout.Stretch;
      this.PbSelectID1.Location = new Point(537, 14);
      this.PbSelectID1.Name = "PbSelectID1";
      this.PbSelectID1.Size = new Size(22, 22);
      this.PbSelectID1.TabIndex = 111;
      this.PbSelectID1.TabStop = false;
      this.PbSelectID1.Click += new EventHandler(this.PbSelectID1_Click);
      this.pictureBox1.BackColor = Color.White;
      this.pictureBox1.BorderStyle = BorderStyle.FixedSingle;
      this.pictureBox1.Location = new Point(565, 4);
      this.pictureBox1.Name = "pictureBox1";
      this.pictureBox1.Size = new Size(32, 32);
      this.pictureBox1.TabIndex = 110;
      this.pictureBox1.TabStop = false;
      this.tbItemIndex.BorderStyle = BorderStyle.FixedSingle;
      this.tbItemIndex.Location = new Point(469, 14);
      this.tbItemIndex.Name = "tbItemIndex";
      this.tbItemIndex.Size = new Size(63, 20);
      this.tbItemIndex.TabIndex = 109;
      this.tbItemIndex.TextChanged += new EventHandler(this.tbItemIndex_TextChanged);
      this.tbItemIndex.KeyPress += new KeyPressEventHandler(this.tbItemIndex_KeyPress);
      this.label10.AutoSize = true;
      this.label10.Location = new Point(407, 17);
      this.label10.Name = "label10";
      this.label10.Size = new Size(56, 13);
      this.label10.TabIndex = 108;
      this.label10.Text = "ItemIndex:";
      this.groupBox20.Controls.Add((Control) this.chk3D);
      this.groupBox20.Controls.Add((Control) this.slideLeftRight);
      this.groupBox20.Controls.Add((Control) this.slideUpDown);
      this.groupBox20.Controls.Add((Control) this.slideZoom);
      this.groupBox20.Controls.Add((Control) this.panel3DView);
      this.groupBox20.Location = new Point(326, 42);
      this.groupBox20.Name = "groupBox20";
      this.groupBox20.Size = new Size(279, 313);
      this.groupBox20.TabIndex = 107;
      this.groupBox20.TabStop = false;
      this.groupBox20.Text = "3D View";
      this.chk3D.AutoSize = true;
      this.chk3D.Checked = true;
      this.chk3D.CheckState = CheckState.Checked;
      this.chk3D.FlatStyle = FlatStyle.Flat;
      this.chk3D.Location = new Point(180, 0);
      this.chk3D.Name = "chk3D";
      this.chk3D.Size = new Size(99, 17);
      this.chk3D.TabIndex = 38;
      this.chk3D.Text = "Enable 3D View";
      this.chk3D.UseVisualStyleBackColor = true;
      this.slideLeftRight.AutoSize = false;
      this.slideLeftRight.Location = new Point(188, 284);
      this.slideLeftRight.Maximum = 10000;
      this.slideLeftRight.Minimum = -10000;
      this.slideLeftRight.Name = "slideLeftRight";
      this.slideLeftRight.Size = new Size(85, 25);
      this.slideLeftRight.TabIndex = 3;
      this.slideLeftRight.TickStyle = TickStyle.None;
      this.slideLeftRight.Scroll += new EventHandler(this.slideLeftRight_Scroll);
      this.slideUpDown.AutoSize = false;
      this.slideUpDown.Location = new Point(95, 284);
      this.slideUpDown.Maximum = 10000;
      this.slideUpDown.Minimum = -10000;
      this.slideUpDown.Name = "slideUpDown";
      this.slideUpDown.Size = new Size(85, 25);
      this.slideUpDown.TabIndex = 2;
      this.slideUpDown.TickStyle = TickStyle.None;
      this.slideUpDown.Scroll += new EventHandler(this.slideUpDown_Scroll);
      this.slideZoom.AutoSize = false;
      this.slideZoom.Location = new Point(7, 284);
      this.slideZoom.Maximum = 10000;
      this.slideZoom.Minimum = -10000;
      this.slideZoom.Name = "slideZoom";
      this.slideZoom.Size = new Size(85, 25);
      this.slideZoom.TabIndex = 1;
      this.slideZoom.TickStyle = TickStyle.None;
      this.slideZoom.Scroll += new EventHandler(this.slideZoom_Scroll);
      this.panel3DView.Location = new Point(7, 20);
      this.panel3DView.Name = "panel3DView";
      this.panel3DView.Size = new Size(266, 258);
      this.panel3DView.TabIndex = 0;
      this.label33.AutoSize = true;
      this.label33.Location = new Point(332, 440);
      this.label33.Name = "label33";
      this.label33.Size = new Size(41, 13);
      this.label33.TabIndex = 103;
      this.label33.Text = "Strong:";
      this.tbFlag.BorderStyle = BorderStyle.FixedSingle;
      this.tbFlag.Location = new Point(379, 387);
      this.tbFlag.Name = "tbFlag";
      this.tbFlag.Size = new Size(68, 20);
      this.tbFlag.TabIndex = 106;
      this.tbFlag.Visible = false;
      this.tbFlag.KeyPress += new KeyPressEventHandler(this.tbFlag_KeyPress);
      this.label37.AutoSize = true;
      this.label37.Location = new Point(482, 440);
      this.label37.Name = "label37";
      this.label37.Size = new Size(43, 13);
      this.label37.TabIndex = 95;
      this.label37.Text = "Normal:";
      this.label39.AutoSize = true;
      this.label39.Location = new Point(332, 414);
      this.label39.Name = "label39";
      this.label39.Size = new Size(41, 13);
      this.label39.TabIndex = 91;
      this.label39.Text = "Critical:";
      this.tbStrong.BorderStyle = BorderStyle.FixedSingle;
      this.tbStrong.Location = new Point(379, 439);
      this.tbStrong.Name = "tbStrong";
      this.tbStrong.Size = new Size(68, 20);
      this.tbStrong.TabIndex = 104;
      this.tbStrong.KeyPress += new KeyPressEventHandler(this.tbStrong_KeyPress);
      this.groupBox4.Controls.Add((Control) this.tbAttackSpeed);
      this.groupBox4.Controls.Add((Control) this.label28);
      this.groupBox4.Controls.Add((Control) this.tbDeadly);
      this.groupBox4.Controls.Add((Control) this.label29);
      this.groupBox4.Controls.Add((Control) this.tbMagicAvoid);
      this.groupBox4.Controls.Add((Control) this.label25);
      this.groupBox4.Controls.Add((Control) this.TbHitpoint);
      this.groupBox4.Controls.Add((Control) this.label26);
      this.groupBox4.Controls.Add((Control) this.tbAvoid);
      this.groupBox4.Controls.Add((Control) this.label27);
      this.groupBox4.Controls.Add((Control) this.tbmDefense);
      this.groupBox4.Controls.Add((Control) this.label24);
      this.groupBox4.Controls.Add((Control) this.tbAttack);
      this.groupBox4.Controls.Add((Control) this.label20);
      this.groupBox4.Controls.Add((Control) this.tbDefense);
      this.groupBox4.Controls.Add((Control) this.label21);
      this.groupBox4.Controls.Add((Control) this.tbmAttack);
      this.groupBox4.Controls.Add((Control) this.label22);
      this.groupBox4.Controls.Add((Control) this.tbAfterDead);
      this.groupBox4.Controls.Add((Control) this.label23);
      this.groupBox4.Controls.Add((Control) this.tbAiSlot);
      this.groupBox4.Controls.Add((Control) this.label19);
      this.groupBox4.Controls.Add((Control) this.tbDelay);
      this.groupBox4.Controls.Add((Control) this.label18);
      this.groupBox4.Controls.Add((Control) this.tbRecoveryMP);
      this.groupBox4.Controls.Add((Control) this.tbRecoveryHP);
      this.groupBox4.Controls.Add((Control) this.label16);
      this.groupBox4.Controls.Add((Control) this.label15);
      this.groupBox4.Controls.Add((Control) this.tbmaxStm);
      this.groupBox4.Controls.Add((Control) this.label12);
      this.groupBox4.Controls.Add((Control) this.tbmaxMP);
      this.groupBox4.Controls.Add((Control) this.tbmaxHP);
      this.groupBox4.Controls.Add((Control) this.tbmaxFaith);
      this.groupBox4.Controls.Add((Control) this.label14);
      this.groupBox4.Controls.Add((Control) this.label13);
      this.groupBox4.Controls.Add((Control) this.label11);
      this.groupBox4.Controls.Add((Control) this.tbConstitution);
      this.groupBox4.Controls.Add((Control) this.tbIntelligence);
      this.groupBox4.Controls.Add((Control) this.TbDexteriety);
      this.groupBox4.Controls.Add((Control) this.label9);
      this.groupBox4.Controls.Add((Control) this.label8);
      this.groupBox4.Controls.Add((Control) this.label7);
      this.groupBox4.Controls.Add((Control) this.tbStrength);
      this.groupBox4.Controls.Add((Control) this.label6);
      this.groupBox4.Location = new Point(8, 126);
      this.groupBox4.Name = "groupBox4";
      this.groupBox4.Size = new Size(319, 336);
      this.groupBox4.TabIndex = 90;
      this.groupBox4.TabStop = false;
      this.groupBox4.Text = "Pet Stats";
      this.tbAttackSpeed.BorderStyle = BorderStyle.FixedSingle;
      this.tbAttackSpeed.Location = new Point(81, 313);
      this.tbAttackSpeed.Name = "tbAttackSpeed";
      this.tbAttackSpeed.Size = new Size(68, 20);
      this.tbAttackSpeed.TabIndex = 41;
      this.tbAttackSpeed.KeyPress += new KeyPressEventHandler(this.tbAttackSpeed_KeyPress);
      this.label28.AutoSize = true;
      this.label28.Location = new Point(0, 316);
      this.label28.Name = "label28";
      this.label28.Size = new Size(75, 13);
      this.label28.TabIndex = 40;
      this.label28.Text = "Attack Speed:";
      this.tbDeadly.BorderStyle = BorderStyle.FixedSingle;
      this.tbDeadly.Location = new Point(233, 313);
      this.tbDeadly.Name = "tbDeadly";
      this.tbDeadly.Size = new Size(68, 20);
      this.tbDeadly.TabIndex = 39;
      this.tbDeadly.KeyPress += new KeyPressEventHandler(this.tbDeadly_KeyPress);
      this.label29.AutoSize = true;
      this.label29.Location = new Point(185, 315);
      this.label29.Name = "label29";
      this.label29.Size = new Size(43, 13);
      this.label29.TabIndex = 38;
      this.label29.Text = "Deadly:";
      this.tbMagicAvoid.BorderStyle = BorderStyle.FixedSingle;
      this.tbMagicAvoid.Location = new Point(81, 287);
      this.tbMagicAvoid.Name = "tbMagicAvoid";
      this.tbMagicAvoid.Size = new Size(68, 20);
      this.tbMagicAvoid.TabIndex = 37;
      this.tbMagicAvoid.KeyPress += new KeyPressEventHandler(this.tbMagicAvoid_KeyPress);
      this.label25.AutoSize = true;
      this.label25.Location = new Point(6, 290);
      this.label25.Name = "label25";
      this.label25.Size = new Size(69, 13);
      this.label25.TabIndex = 36;
      this.label25.Text = "Magic Avoid:";
      this.TbHitpoint.BorderStyle = BorderStyle.FixedSingle;
      this.TbHitpoint.Location = new Point(81, 235);
      this.TbHitpoint.Name = "TbHitpoint";
      this.TbHitpoint.Size = new Size(68, 20);
      this.TbHitpoint.TabIndex = 35;
      this.TbHitpoint.KeyPress += new KeyPressEventHandler(this.TbHitpoint_KeyPress);
      this.label26.AutoSize = true;
      this.label26.Location = new Point(25, 238);
      this.label26.Name = "label26";
      this.label26.Size = new Size(50, 13);
      this.label26.TabIndex = 34;
      this.label26.Text = "Hit Point:";
      this.tbAvoid.BorderStyle = BorderStyle.FixedSingle;
      this.tbAvoid.Location = new Point(81, 261);
      this.tbAvoid.Name = "tbAvoid";
      this.tbAvoid.Size = new Size(68, 20);
      this.tbAvoid.TabIndex = 33;
      this.tbAvoid.KeyPress += new KeyPressEventHandler(this.tbAvoid_KeyPress);
      this.label27.AutoSize = true;
      this.label27.Location = new Point(41, 264);
      this.label27.Name = "label27";
      this.label27.Size = new Size(34, 13);
      this.label27.TabIndex = 32;
      this.label27.Text = "Avoid";
      this.tbmDefense.BorderStyle = BorderStyle.FixedSingle;
      this.tbmDefense.Location = new Point(233, 287);
      this.tbmDefense.Name = "tbmDefense";
      this.tbmDefense.Size = new Size(68, 20);
      this.tbmDefense.TabIndex = 31;
      this.tbmDefense.KeyPress += new KeyPressEventHandler(this.tbmDefense_KeyPress);
      this.label24.AutoSize = true;
      this.label24.Location = new Point(145, 289);
      this.label24.Name = "label24";
      this.label24.Size = new Size(83, 13);
      this.label24.TabIndex = 30;
      this.label24.Text = "Magic Defence:";
      this.tbAttack.BorderStyle = BorderStyle.FixedSingle;
      this.tbAttack.Location = new Point(233, 209);
      this.tbAttack.Name = "tbAttack";
      this.tbAttack.Size = new Size(68, 20);
      this.tbAttack.TabIndex = 29;
      this.tbAttack.KeyPress += new KeyPressEventHandler(this.tbAttack_KeyPress);
      this.label20.AutoSize = true;
      this.label20.Location = new Point(187, 212);
      this.label20.Name = "label20";
      this.label20.Size = new Size(41, 13);
      this.label20.TabIndex = 28;
      this.label20.Text = "Attack:";
      this.tbDefense.BorderStyle = BorderStyle.FixedSingle;
      this.tbDefense.Location = new Point(233, 235);
      this.tbDefense.Name = "tbDefense";
      this.tbDefense.Size = new Size(68, 20);
      this.tbDefense.TabIndex = 27;
      this.tbDefense.KeyPress += new KeyPressEventHandler(this.tbDefense_KeyPress);
      this.label21.AutoSize = true;
      this.label21.Location = new Point(179, 237);
      this.label21.Name = "label21";
      this.label21.Size = new Size(49, 13);
      this.label21.TabIndex = 26;
      this.label21.Text = "defence:";
      this.tbmAttack.BorderStyle = BorderStyle.FixedSingle;
      this.tbmAttack.Location = new Point(233, 261);
      this.tbmAttack.Name = "tbmAttack";
      this.tbmAttack.Size = new Size(68, 20);
      this.tbmAttack.TabIndex = 25;
      this.tbmAttack.KeyPress += new KeyPressEventHandler(this.tbmAttack_KeyPress);
      this.label22.AutoSize = true;
      this.label22.Location = new Point(155, 263);
      this.label22.Name = "label22";
      this.label22.Size = new Size(73, 13);
      this.label22.TabIndex = 24;
      this.label22.Text = "Magic Attack:";
      this.tbAfterDead.BorderStyle = BorderStyle.FixedSingle;
      this.tbAfterDead.Location = new Point(81, 209);
      this.tbAfterDead.Name = "tbAfterDead";
      this.tbAfterDead.Size = new Size(68, 20);
      this.tbAfterDead.TabIndex = 23;
      this.tbAfterDead.KeyPress += new KeyPressEventHandler(this.tbAfterDead_KeyPress);
      this.label23.AutoSize = true;
      this.label23.Location = new Point(14, 211);
      this.label23.Name = "label23";
      this.label23.Size = new Size(61, 13);
      this.label23.TabIndex = 22;
      this.label23.Text = "After Dead:";
      this.tbAiSlot.BorderStyle = BorderStyle.FixedSingle;
      this.tbAiSlot.Location = new Point(233, 131);
      this.tbAiSlot.Name = "tbAiSlot";
      this.tbAiSlot.Size = new Size(68, 20);
      this.tbAiSlot.TabIndex = 21;
      this.tbAiSlot.KeyPress += new KeyPressEventHandler(this.tbAiSlot_KeyPress);
      this.label19.AutoSize = true;
      this.label19.Location = new Point(187, 134);
      this.label19.Name = "label19";
      this.label19.Size = new Size(41, 13);
      this.label19.TabIndex = 20;
      this.label19.Text = "AI Slot:";
      this.tbDelay.BorderStyle = BorderStyle.FixedSingle;
      this.tbDelay.Location = new Point(233, 157);
      this.tbDelay.Name = "tbDelay";
      this.tbDelay.Size = new Size(68, 20);
      this.tbDelay.TabIndex = 19;
      this.tbDelay.KeyPress += new KeyPressEventHandler(this.tbDelay_KeyPress);
      this.label18.AutoSize = true;
      this.label18.Location = new Point(191, 159);
      this.label18.Name = "label18";
      this.label18.Size = new Size(37, 13);
      this.label18.TabIndex = 18;
      this.label18.Text = "Delay:";
      this.tbRecoveryMP.BorderStyle = BorderStyle.FixedSingle;
      this.tbRecoveryMP.Location = new Point(233, 105);
      this.tbRecoveryMP.Name = "tbRecoveryMP";
      this.tbRecoveryMP.Size = new Size(68, 20);
      this.tbRecoveryMP.TabIndex = 15;
      this.tbRecoveryMP.KeyPress += new KeyPressEventHandler(this.tbRecoveryMP_KeyPress);
      this.tbRecoveryHP.BorderStyle = BorderStyle.FixedSingle;
      this.tbRecoveryHP.Location = new Point(233, 79);
      this.tbRecoveryHP.Name = "tbRecoveryHP";
      this.tbRecoveryHP.Size = new Size(68, 20);
      this.tbRecoveryHP.TabIndex = 14;
      this.tbRecoveryHP.KeyPress += new KeyPressEventHandler(this.tbRecoveryHP_KeyPress);
      this.label16.AutoSize = true;
      this.label16.Location = new Point(179, 109);
      this.label16.Name = "label16";
      this.label16.Size = new Size(49, 13);
      this.label16.TabIndex = 13;
      this.label16.Text = "Rcv MP:";
      this.label15.AutoSize = true;
      this.label15.Location = new Point(180, 82);
      this.label15.Name = "label15";
      this.label15.Size = new Size(48, 13);
      this.label15.TabIndex = 12;
      this.label15.Text = "Rcv HP:";
      this.tbmaxStm.BorderStyle = BorderStyle.FixedSingle;
      this.tbmaxStm.Location = new Point(81, 157);
      this.tbmaxStm.Name = "tbmaxStm";
      this.tbmaxStm.Size = new Size(68, 20);
      this.tbmaxStm.TabIndex = 11;
      this.tbmaxStm.KeyPress += new KeyPressEventHandler(this.tbmaxStm_KeyPress);
      this.label12.AutoSize = true;
      this.label12.Location = new Point(27, 159);
      this.label12.Name = "label12";
      this.label12.Size = new Size(48, 13);
      this.label12.TabIndex = 10;
      this.label12.Text = "MaxStm:";
      this.tbmaxMP.BorderStyle = BorderStyle.FixedSingle;
      this.tbmaxMP.Location = new Point(81, 105);
      this.tbmaxMP.Name = "tbmaxMP";
      this.tbmaxMP.Size = new Size(68, 20);
      this.tbmaxMP.TabIndex = 11;
      this.tbmaxMP.KeyPress += new KeyPressEventHandler(this.tbmaxMP_KeyPress);
      this.tbmaxHP.BorderStyle = BorderStyle.FixedSingle;
      this.tbmaxHP.Location = new Point(81, 79);
      this.tbmaxHP.Name = "tbmaxHP";
      this.tbmaxHP.Size = new Size(68, 20);
      this.tbmaxHP.TabIndex = 10;
      this.tbmaxHP.KeyPress += new KeyPressEventHandler(this.tbmaxHP_KeyPress);
      this.tbmaxFaith.BorderStyle = BorderStyle.FixedSingle;
      this.tbmaxFaith.Location = new Point(81, 131);
      this.tbmaxFaith.Name = "tbmaxFaith";
      this.tbmaxFaith.Size = new Size(68, 20);
      this.tbmaxFaith.TabIndex = 9;
      this.tbmaxFaith.KeyPress += new KeyPressEventHandler(this.tbmaxFaith_KeyPress);
      this.label14.AutoSize = true;
      this.label14.Location = new Point(29, 109);
      this.label14.Name = "label14";
      this.label14.Size = new Size(46, 13);
      this.label14.TabIndex = 9;
      this.label14.Text = "MaxMP:";
      this.label13.AutoSize = true;
      this.label13.Location = new Point(30, 82);
      this.label13.Name = "label13";
      this.label13.Size = new Size(45, 13);
      this.label13.TabIndex = 8;
      this.label13.Text = "MaxHP:";
      this.label11.AutoSize = true;
      this.label11.Location = new Point(22, 134);
      this.label11.Name = "label11";
      this.label11.Size = new Size(53, 13);
      this.label11.TabIndex = 8;
      this.label11.Text = "MaxFaith:";
      this.tbConstitution.BorderStyle = BorderStyle.FixedSingle;
      this.tbConstitution.Location = new Point(252, 53);
      this.tbConstitution.Name = "tbConstitution";
      this.tbConstitution.Size = new Size(49, 20);
      this.tbConstitution.TabIndex = 7;
      this.tbConstitution.KeyPress += new KeyPressEventHandler(this.tbConstitution_KeyPress);
      this.tbIntelligence.BorderStyle = BorderStyle.FixedSingle;
      this.tbIntelligence.Location = new Point(190, 53);
      this.tbIntelligence.Name = "tbIntelligence";
      this.tbIntelligence.Size = new Size(49, 20);
      this.tbIntelligence.TabIndex = 6;
      this.tbIntelligence.KeyPress += new KeyPressEventHandler(this.tbIntelligence_KeyPress);
      this.TbDexteriety.BorderStyle = BorderStyle.FixedSingle;
      this.TbDexteriety.Location = new Point(139, 53);
      this.TbDexteriety.Name = "TbDexteriety";
      this.TbDexteriety.Size = new Size(49, 20);
      this.TbDexteriety.TabIndex = 5;
      this.TbDexteriety.KeyPress += new KeyPressEventHandler(this.TbDexteriety_KeyPress);
      this.label9.AutoSize = true;
      this.label9.Location = new Point(254, 37);
      this.label9.Name = "label9";
      this.label9.Size = new Size(29, 13);
      this.label9.TabIndex = 4;
      this.label9.Text = "Con:";
      this.label8.AutoSize = true;
      this.label8.Location = new Point(204, 37);
      this.label8.Name = "label8";
      this.label8.Size = new Size(22, 13);
      this.label8.TabIndex = 3;
      this.label8.Text = "Int:";
      this.label7.AutoSize = true;
      this.label7.Location = new Point(145, 37);
      this.label7.Name = "label7";
      this.label7.Size = new Size(29, 13);
      this.label7.TabIndex = 2;
      this.label7.Text = "Dex:";
      this.tbStrength.BorderStyle = BorderStyle.FixedSingle;
      this.tbStrength.Location = new Point(81, 53);
      this.tbStrength.Name = "tbStrength";
      this.tbStrength.Size = new Size(49, 20);
      this.tbStrength.TabIndex = 1;
      this.tbStrength.KeyPress += new KeyPressEventHandler(this.tbStrength_KeyPress);
      this.label6.AutoSize = true;
      this.label6.Location = new Point(93, 37);
      this.label6.Name = "label6";
      this.label6.Size = new Size(23, 13);
      this.label6.TabIndex = 0;
      this.label6.Text = "Str:";
      this.tbAwful.BorderStyle = BorderStyle.FixedSingle;
      this.tbAwful.Location = new Point(531, 412);
      this.tbAwful.Name = "tbAwful";
      this.tbAwful.Size = new Size(68, 20);
      this.tbAwful.TabIndex = 98;
      this.tbAwful.KeyPress += new KeyPressEventHandler(this.tbAwful_KeyPress);
      this.label30.AutoSize = true;
      this.label30.Location = new Point(343, 387);
      this.label30.Name = "label30";
      this.label30.Size = new Size(30, 13);
      this.label30.TabIndex = 105;
      this.label30.Text = "Flag:";
      this.label30.Visible = false;
      this.label36.AutoSize = true;
      this.label36.Location = new Point(489, 414);
      this.label36.Name = "label36";
      this.label36.Size = new Size(36, 13);
      this.label36.TabIndex = 97;
      this.label36.Text = "Awful:";
      this.tbNoraml.BorderStyle = BorderStyle.FixedSingle;
      this.tbNoraml.Location = new Point(531, 438);
      this.tbNoraml.Name = "tbNoraml";
      this.tbNoraml.Size = new Size(68, 20);
      this.tbNoraml.TabIndex = 96;
      this.tbNoraml.KeyPress += new KeyPressEventHandler(this.tbNoraml_KeyPress);
      this.label34.AutoSize = true;
      this.label34.Location = new Point(337, 363);
      this.label34.Name = "label34";
      this.label34.Size = new Size(36, 13);
      this.label34.TabIndex = 101;
      this.label34.Text = "Week";
      this.tbWeak.BorderStyle = BorderStyle.FixedSingle;
      this.tbWeak.Location = new Point(379, 361);
      this.tbWeak.Name = "tbWeak";
      this.tbWeak.Size = new Size(68, 20);
      this.tbWeak.TabIndex = 102;
      this.tbWeak.KeyPress += new KeyPressEventHandler(this.tbWeak_KeyPress);
      this.label38.AutoSize = true;
      this.label38.Location = new Point(461, 363);
      this.label38.Name = "label38";
      this.label38.Size = new Size(64, 13);
      this.label38.TabIndex = 93;
      this.label38.Text = "Basic Skill 1";
      this.tbBasicSkill2.BorderStyle = BorderStyle.FixedSingle;
      this.tbBasicSkill2.Location = new Point(531, 386);
      this.tbBasicSkill2.Name = "tbBasicSkill2";
      this.tbBasicSkill2.Size = new Size(68, 20);
      this.tbBasicSkill2.TabIndex = 100;
      this.tbBasicSkill2.KeyPress += new KeyPressEventHandler(this.tbBasicSkill2_KeyPress);
      this.tbBasicSkill1.BorderStyle = BorderStyle.FixedSingle;
      this.tbBasicSkill1.Location = new Point(531, 360);
      this.tbBasicSkill1.Name = "tbBasicSkill1";
      this.tbBasicSkill1.Size = new Size(68, 20);
      this.tbBasicSkill1.TabIndex = 94;
      this.tbBasicSkill1.KeyPress += new KeyPressEventHandler(this.tbBasicSkill1_KeyPress);
      this.tbCritical.BorderStyle = BorderStyle.FixedSingle;
      this.tbCritical.Location = new Point(379, 413);
      this.tbCritical.Name = "tbCritical";
      this.tbCritical.Size = new Size(68, 20);
      this.tbCritical.TabIndex = 92;
      this.tbCritical.KeyPress += new KeyPressEventHandler(this.tbCritical_KeyPress);
      this.label35.AutoSize = true;
      this.label35.Location = new Point(461, 387);
      this.label35.Name = "label35";
      this.label35.Size = new Size(64, 13);
      this.label35.TabIndex = 99;
      this.label35.Text = "Basic Skill 2";
      this.groupBox3.Controls.Add((Control) this.flag);
      this.groupBox3.Controls.Add((Control) this.label80);
      this.groupBox3.Controls.Add((Control) this.label5);
      this.groupBox3.Controls.Add((Control) this.comboBox1);
      this.groupBox3.Controls.Add((Control) this.checkBox1);
      this.groupBox3.Controls.Add((Control) this.txtID);
      this.groupBox3.Controls.Add((Control) this.txtName);
      this.groupBox3.Controls.Add((Control) this.label3);
      this.groupBox3.Controls.Add((Control) this.label2);
      this.groupBox3.Location = new Point(8, 17);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Size = new Size(312, 103);
      this.groupBox3.TabIndex = 0;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "Basic";
      this.flag.FlatStyle = FlatStyle.Popup;
      this.flag.FormattingEnabled = true;
      this.flag.Items.AddRange(new object[2]
      {
        (object) "1 - Does not shares experience",
        (object) "2 - shares his experience"
      });
      this.flag.Location = new Point(50, 74);
      this.flag.Name = "flag";
      this.flag.Size = new Size(231, 21);
      this.flag.TabIndex = 13;
      this.flag.SelectionChangeCommitted += new EventHandler(this.flag_SelectionChangeCommitted);
      this.flag.KeyPress += new KeyPressEventHandler(this.flag_KeyPress);
      this.label80.AutoSize = true;
      this.label80.Location = new Point(11, 77);
      this.label80.Name = "label80";
      this.label80.Size = new Size(30, 13);
      this.label80.TabIndex = 12;
      this.label80.Text = "Flag:";
      this.label5.AutoSize = true;
      this.label5.Location = new Point(166, 24);
      this.label5.Name = "label5";
      this.label5.Size = new Size(34, 13);
      this.label5.TabIndex = 10;
      this.label5.Text = "Type:";
      this.comboBox1.FlatStyle = FlatStyle.Flat;
      this.comboBox1.FormattingEnabled = true;
      this.comboBox1.Items.AddRange(new object[4]
      {
        (object) "1 - Human",
        (object) "2 - Beast",
        (object) "3 - Demon",
        (object) "4 - Dark Lord"
      });
      this.comboBox1.Location = new Point(206, 21);
      this.comboBox1.Name = "comboBox1";
      this.comboBox1.Size = new Size(75, 21);
      this.comboBox1.TabIndex = 9;
      this.comboBox1.SelectedIndexChanged += new EventHandler(this.comboBox1_SelectedIndexChanged);
      this.comboBox1.SelectionChangeCommitted += new EventHandler(this.comboBox1_SelectionChangeCommitted);
      this.comboBox1.KeyPress += new KeyPressEventHandler(this.comboBox1_KeyPress);
      this.checkBox1.AutoSize = true;
      this.checkBox1.FlatStyle = FlatStyle.Flat;
      this.checkBox1.Location = new Point(97, 21);
      this.checkBox1.Name = "checkBox1";
      this.checkBox1.Size = new Size(56, 17);
      this.checkBox1.TabIndex = 4;
      this.checkBox1.Text = "Enable";
      this.checkBox1.UseVisualStyleBackColor = true;
      this.checkBox1.CheckedChanged += new EventHandler(this.checkBox1_CheckedChanged);
      this.txtID.Location = new Point(50, 19);
      this.txtID.Name = "txtID";
      this.txtID.Size = new Size(39, 20);
      this.txtID.TabIndex = 3;
      this.txtID.KeyPress += new KeyPressEventHandler(this.txtID_KeyPress);
      this.txtName.Location = new Point(50, 48);
      this.txtName.Name = "txtName";
      this.txtName.Size = new Size(233, 20);
      this.txtName.TabIndex = 2;
      this.txtName.KeyPress += new KeyPressEventHandler(this.txtName_KeyPress);
      this.label3.AutoSize = true;
      this.label3.Location = new Point(6, 51);
      this.label3.Name = "label3";
      this.label3.Size = new Size(38, 13);
      this.label3.TabIndex = 1;
      this.label3.Text = "Name:";
      this.label2.AutoSize = true;
      this.label2.Location = new Point(6, 22);
      this.label2.Name = "label2";
      this.label2.Size = new Size(21, 13);
      this.label2.TabIndex = 0;
      this.label2.Text = "ID:";
      this.tabPage2.BackColor = SystemColors.Control;
      this.tabPage2.Controls.Add((Control) this.groupBox8);
      this.tabPage2.Controls.Add((Control) this.groupBox7);
      this.tabPage2.Controls.Add((Control) this.groupBox6);
      this.tabPage2.Controls.Add((Control) this.groupBox5);
      this.tabPage2.Location = new Point(4, 22);
      this.tabPage2.Name = "tabPage2";
      this.tabPage2.Padding = new Padding(3);
      this.tabPage2.Size = new Size(620, 464);
      this.tabPage2.TabIndex = 1;
      this.tabPage2.Text = "Animation Edit";
      this.groupBox8.Controls.Add((Control) this.label68);
      this.groupBox8.Controls.Add((Control) this.t_tex2);
      this.groupBox8.Controls.Add((Control) this.t_row2);
      this.groupBox8.Controls.Add((Control) this.label69);
      this.groupBox8.Controls.Add((Control) this.t_col2);
      this.groupBox8.Controls.Add((Control) this.label70);
      this.groupBox8.Controls.Add((Control) this.label4);
      this.groupBox8.Controls.Add((Control) this.t_tex1);
      this.groupBox8.Controls.Add((Control) this.t_row1);
      this.groupBox8.Controls.Add((Control) this.label66);
      this.groupBox8.Controls.Add((Control) this.t_col1);
      this.groupBox8.Controls.Add((Control) this.label67);
      this.groupBox8.Location = new Point(443, 133);
      this.groupBox8.Name = "groupBox8";
      this.groupBox8.Size = new Size(144, 84);
      this.groupBox8.TabIndex = 68;
      this.groupBox8.TabStop = false;
      this.groupBox8.Text = "Only Admin";
      this.groupBox8.Visible = false;
      this.label68.AutoSize = true;
      this.label68.Location = new Point(74, 15);
      this.label68.Name = "label68";
      this.label68.Size = new Size(30, 13);
      this.label68.TabIndex = 62;
      this.label68.Text = "tex 2";
      this.t_tex2.BorderStyle = BorderStyle.FixedSingle;
      this.t_tex2.Location = new Point(105, 13);
      this.t_tex2.Name = "t_tex2";
      this.t_tex2.Size = new Size(33, 20);
      this.t_tex2.TabIndex = 63;
      this.t_tex2.Visible = false;
      this.t_row2.BorderStyle = BorderStyle.FixedSingle;
      this.t_row2.Location = new Point(105, 39);
      this.t_row2.Name = "t_row2";
      this.t_row2.Size = new Size(33, 20);
      this.t_row2.TabIndex = 67;
      this.t_row2.Visible = false;
      this.label69.AutoSize = true;
      this.label69.Location = new Point(74, 41);
      this.label69.Name = "label69";
      this.label69.Size = new Size(33, 13);
      this.label69.TabIndex = 66;
      this.label69.Text = "row 2";
      this.t_col2.BorderStyle = BorderStyle.FixedSingle;
      this.t_col2.Location = new Point(105, 60);
      this.t_col2.Name = "t_col2";
      this.t_col2.Size = new Size(33, 20);
      this.t_col2.TabIndex = 65;
      this.t_col2.Visible = false;
      this.label70.AutoSize = true;
      this.label70.Location = new Point(74, 67);
      this.label70.Name = "label70";
      this.label70.Size = new Size(30, 13);
      this.label70.TabIndex = 64;
      this.label70.Text = "col 2";
      this.label4.AutoSize = true;
      this.label4.Location = new Point(8, 15);
      this.label4.Name = "label4";
      this.label4.Size = new Size(30, 13);
      this.label4.TabIndex = 56;
      this.label4.Text = "tex 1";
      this.t_tex1.BorderStyle = BorderStyle.FixedSingle;
      this.t_tex1.Location = new Point(39, 13);
      this.t_tex1.Name = "t_tex1";
      this.t_tex1.Size = new Size(33, 20);
      this.t_tex1.TabIndex = 57;
      this.t_tex1.Visible = false;
      this.t_row1.BorderStyle = BorderStyle.FixedSingle;
      this.t_row1.Location = new Point(39, 39);
      this.t_row1.Name = "t_row1";
      this.t_row1.Size = new Size(33, 20);
      this.t_row1.TabIndex = 61;
      this.t_row1.Visible = false;
      this.label66.AutoSize = true;
      this.label66.Location = new Point(8, 41);
      this.label66.Name = "label66";
      this.label66.Size = new Size(33, 13);
      this.label66.TabIndex = 60;
      this.label66.Text = "row 1";
      this.t_col1.BorderStyle = BorderStyle.FixedSingle;
      this.t_col1.Location = new Point(39, 60);
      this.t_col1.Name = "t_col1";
      this.t_col1.Size = new Size(33, 20);
      this.t_col1.TabIndex = 59;
      this.t_col1.Visible = false;
      this.label67.AutoSize = true;
      this.label67.Location = new Point(8, 67);
      this.label67.Name = "label67";
      this.label67.Size = new Size(30, 13);
      this.label67.TabIndex = 58;
      this.label67.Text = "col 1";
      this.groupBox7.Controls.Add((Control) this.cbMount2);
      this.groupBox7.Controls.Add((Control) this.pictureBox5);
      this.groupBox7.Controls.Add((Control) this.button2);
      this.groupBox7.Controls.Add((Control) this.btnLevelup2);
      this.groupBox7.Controls.Add((Control) this.BtnAniAttack2_1);
      this.groupBox7.Controls.Add((Control) this.btnAniIdle2_1);
      this.groupBox7.Controls.Add((Control) this.btnAniRun_1);
      this.groupBox7.Controls.Add((Control) this.btnAniDie_1);
      this.groupBox7.Controls.Add((Control) this.BtnAniAttack1_1);
      this.groupBox7.Controls.Add((Control) this.BtnAniDam_1);
      this.groupBox7.Controls.Add((Control) this.BtnAniIdle1);
      this.groupBox7.Controls.Add((Control) this.BtnAniWalk_1);
      this.groupBox7.Controls.Add((Control) this.BtnReadSmc2);
      this.groupBox7.Controls.Add((Control) this.label51);
      this.groupBox7.Controls.Add((Control) this.tbAniDamage1_2);
      this.groupBox7.Controls.Add((Control) this.tbSmc1_2);
      this.groupBox7.Controls.Add((Control) this.label65);
      this.groupBox7.Controls.Add((Control) this.tbAniIdle1_2);
      this.groupBox7.Controls.Add((Control) this.label49);
      this.groupBox7.Controls.Add((Control) this.tbAniIdle2_2);
      this.groupBox7.Controls.Add((Control) this.label54);
      this.groupBox7.Controls.Add((Control) this.tbAniRun1_2);
      this.groupBox7.Controls.Add((Control) this.label56);
      this.groupBox7.Controls.Add((Control) this.tbSkillSummon1_2);
      this.groupBox7.Controls.Add((Control) this.tbAniWalk1_2);
      this.groupBox7.Controls.Add((Control) this.tbAniAttack1_2);
      this.groupBox7.Controls.Add((Control) this.label58);
      this.groupBox7.Controls.Add((Control) this.label60);
      this.groupBox7.Controls.Add((Control) this.label50);
      this.groupBox7.Controls.Add((Control) this.tbLevelUp1_2);
      this.groupBox7.Controls.Add((Control) this.label62);
      this.groupBox7.Controls.Add((Control) this.tbSpeed1_2);
      this.groupBox7.Controls.Add((Control) this.tbAniAttack2_2);
      this.groupBox7.Controls.Add((Control) this.label61);
      this.groupBox7.Controls.Add((Control) this.label59);
      this.groupBox7.Controls.Add((Control) this.tbAniDie1_2);
      this.groupBox7.Controls.Add((Control) this.label57);
      this.groupBox7.Controls.Add((Control) this.label63);
      this.groupBox7.Controls.Add((Control) this.tbMount1_2);
      this.groupBox7.Location = new Point(6, 226);
      this.groupBox7.Name = "groupBox7";
      this.groupBox7.Size = new Size(431, 208);
      this.groupBox7.TabIndex = 67;
      this.groupBox7.TabStop = false;
      this.groupBox7.Text = "Animation 2";
      this.cbMount2.AutoSize = true;
      this.cbMount2.FlatStyle = FlatStyle.Flat;
      this.cbMount2.Location = new Point(64, 151);
      this.cbMount2.Name = "cbMount2";
      this.cbMount2.Size = new Size(70, 17);
      this.cbMount2.TabIndex = 115;
      this.cbMount2.Text = "NotMount";
      this.cbMount2.UseVisualStyleBackColor = true;
      this.cbMount2.CheckedChanged += new EventHandler(this.cbMount2_CheckedChanged);
      this.pictureBox5.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.oie_transparent;
      this.pictureBox5.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox5.Location = new Point(381, 173);
      this.pictureBox5.Name = "pictureBox5";
      this.pictureBox5.Size = new Size(22, 22);
      this.pictureBox5.TabIndex = 115;
      this.pictureBox5.TabStop = false;
      this.pictureBox5.Click += new EventHandler(this.pictureBox5_Click);
      this.button2.BackColor = SystemColors.Control;
      this.button2.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.search;
      this.button2.BackgroundImageLayout = ImageLayout.Stretch;
      this.button2.FlatAppearance.BorderSize = 0;
      this.button2.FlatStyle = FlatStyle.Flat;
      this.button2.Location = new Point(404, 126);
      this.button2.Name = "button2";
      this.button2.Size = new Size(20, 20);
      this.button2.TabIndex = 114;
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.btnLevelup2.BackColor = SystemColors.Control;
      this.btnLevelup2.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.search;
      this.btnLevelup2.BackgroundImageLayout = ImageLayout.Stretch;
      this.btnLevelup2.FlatAppearance.BorderSize = 0;
      this.btnLevelup2.FlatStyle = FlatStyle.Flat;
      this.btnLevelup2.Location = new Point(404, 98);
      this.btnLevelup2.Name = "btnLevelup2";
      this.btnLevelup2.Size = new Size(20, 20);
      this.btnLevelup2.TabIndex = 106;
      this.btnLevelup2.UseVisualStyleBackColor = true;
      this.btnLevelup2.Click += new EventHandler(this.AniFind2);
      this.BtnAniAttack2_1.BackColor = SystemColors.Control;
      this.BtnAniAttack2_1.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.search;
      this.BtnAniAttack2_1.BackgroundImageLayout = ImageLayout.Stretch;
      this.BtnAniAttack2_1.FlatAppearance.BorderSize = 0;
      this.BtnAniAttack2_1.FlatStyle = FlatStyle.Flat;
      this.BtnAniAttack2_1.Location = new Point(183, 99);
      this.BtnAniAttack2_1.Name = "BtnAniAttack2_1";
      this.BtnAniAttack2_1.Size = new Size(20, 20);
      this.BtnAniAttack2_1.TabIndex = 112;
      this.BtnAniAttack2_1.UseVisualStyleBackColor = true;
      this.BtnAniAttack2_1.Click += new EventHandler(this.AniFind2);
      this.btnAniIdle2_1.BackColor = SystemColors.Control;
      this.btnAniIdle2_1.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.search;
      this.btnAniIdle2_1.BackgroundImageLayout = ImageLayout.Stretch;
      this.btnAniIdle2_1.FlatAppearance.BorderSize = 0;
      this.btnAniIdle2_1.FlatStyle = FlatStyle.Flat;
      this.btnAniIdle2_1.Location = new Point(183, 46);
      this.btnAniIdle2_1.Name = "btnAniIdle2_1";
      this.btnAniIdle2_1.Size = new Size(20, 20);
      this.btnAniIdle2_1.TabIndex = 111;
      this.btnAniIdle2_1.UseVisualStyleBackColor = true;
      this.btnAniIdle2_1.Click += new EventHandler(this.AniFind2);
      this.btnAniRun_1.BackColor = SystemColors.Control;
      this.btnAniRun_1.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.search;
      this.btnAniRun_1.BackgroundImageLayout = ImageLayout.Stretch;
      this.btnAniRun_1.FlatAppearance.BorderSize = 0;
      this.btnAniRun_1.FlatStyle = FlatStyle.Flat;
      this.btnAniRun_1.Location = new Point(404, 45);
      this.btnAniRun_1.Name = "btnAniRun_1";
      this.btnAniRun_1.Size = new Size(20, 20);
      this.btnAniRun_1.TabIndex = 110;
      this.btnAniRun_1.UseVisualStyleBackColor = true;
      this.btnAniRun_1.Click += new EventHandler(this.AniFind2);
      this.btnAniDie_1.BackColor = SystemColors.Control;
      this.btnAniDie_1.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.search;
      this.btnAniDie_1.BackgroundImageLayout = ImageLayout.Stretch;
      this.btnAniDie_1.FlatAppearance.BorderSize = 0;
      this.btnAniDie_1.FlatStyle = FlatStyle.Flat;
      this.btnAniDie_1.Location = new Point(183, 123);
      this.btnAniDie_1.Name = "btnAniDie_1";
      this.btnAniDie_1.Size = new Size(20, 20);
      this.btnAniDie_1.TabIndex = 109;
      this.btnAniDie_1.UseVisualStyleBackColor = true;
      this.btnAniDie_1.Click += new EventHandler(this.AniFind2);
      this.BtnAniAttack1_1.BackColor = SystemColors.Control;
      this.BtnAniAttack1_1.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.search;
      this.BtnAniAttack1_1.BackgroundImageLayout = ImageLayout.Stretch;
      this.BtnAniAttack1_1.FlatAppearance.BorderSize = 0;
      this.BtnAniAttack1_1.FlatStyle = FlatStyle.Flat;
      this.BtnAniAttack1_1.Location = new Point(183, 71);
      this.BtnAniAttack1_1.Name = "BtnAniAttack1_1";
      this.BtnAniAttack1_1.Size = new Size(20, 20);
      this.BtnAniAttack1_1.TabIndex = 108;
      this.BtnAniAttack1_1.UseVisualStyleBackColor = true;
      this.BtnAniAttack1_1.Click += new EventHandler(this.AniFind2);
      this.BtnAniDam_1.BackColor = SystemColors.Control;
      this.BtnAniDam_1.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.search;
      this.BtnAniDam_1.BackgroundImageLayout = ImageLayout.Stretch;
      this.BtnAniDam_1.FlatAppearance.BorderSize = 0;
      this.BtnAniDam_1.FlatStyle = FlatStyle.Flat;
      this.BtnAniDam_1.Location = new Point(404, 71);
      this.BtnAniDam_1.Name = "BtnAniDam_1";
      this.BtnAniDam_1.Size = new Size(20, 20);
      this.BtnAniDam_1.TabIndex = 107;
      this.BtnAniDam_1.UseVisualStyleBackColor = true;
      this.BtnAniDam_1.Click += new EventHandler(this.AniFind2);
      this.BtnAniIdle1.BackColor = SystemColors.Control;
      this.BtnAniIdle1.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.search;
      this.BtnAniIdle1.BackgroundImageLayout = ImageLayout.Stretch;
      this.BtnAniIdle1.FlatAppearance.BorderSize = 0;
      this.BtnAniIdle1.FlatStyle = FlatStyle.Flat;
      this.BtnAniIdle1.Location = new Point(183, 19);
      this.BtnAniIdle1.Name = "BtnAniIdle1";
      this.BtnAniIdle1.Size = new Size(20, 20);
      this.BtnAniIdle1.TabIndex = 106;
      this.BtnAniIdle1.UseVisualStyleBackColor = true;
      this.BtnAniIdle1.Click += new EventHandler(this.AniFind2);
      this.BtnAniWalk_1.BackColor = SystemColors.Control;
      this.BtnAniWalk_1.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.search;
      this.BtnAniWalk_1.BackgroundImageLayout = ImageLayout.Stretch;
      this.BtnAniWalk_1.FlatAppearance.BorderSize = 0;
      this.BtnAniWalk_1.FlatStyle = FlatStyle.Flat;
      this.BtnAniWalk_1.Location = new Point(404, 17);
      this.BtnAniWalk_1.Name = "BtnAniWalk_1";
      this.BtnAniWalk_1.Size = new Size(20, 20);
      this.BtnAniWalk_1.TabIndex = 105;
      this.BtnAniWalk_1.UseVisualStyleBackColor = true;
      this.BtnAniWalk_1.Click += new EventHandler(this.AniFind2);
      this.BtnReadSmc2.BackColor = SystemColors.Control;
      this.BtnReadSmc2.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.search;
      this.BtnReadSmc2.BackgroundImageLayout = ImageLayout.Stretch;
      this.BtnReadSmc2.FlatAppearance.BorderSize = 0;
      this.BtnReadSmc2.FlatStyle = FlatStyle.Flat;
      this.BtnReadSmc2.Location = new Point(352, 175);
      this.BtnReadSmc2.Name = "BtnReadSmc2";
      this.BtnReadSmc2.Size = new Size(20, 20);
      this.BtnReadSmc2.TabIndex = 97;
      this.BtnReadSmc2.UseVisualStyleBackColor = true;
      this.BtnReadSmc2.Click += new EventHandler(this.BtnReadSmc2_Click);
      this.label51.AutoSize = true;
      this.label51.Location = new Point(11, 177);
      this.label51.Name = "label51";
      this.label51.Size = new Size(30, 13);
      this.label51.TabIndex = 64;
      this.label51.Text = "SMC";
      this.tbAniDamage1_2.BorderStyle = BorderStyle.FixedSingle;
      this.tbAniDamage1_2.Location = new Point(262, 71);
      this.tbAniDamage1_2.Name = "tbAniDamage1_2";
      this.tbAniDamage1_2.Size = new Size(140, 20);
      this.tbAniDamage1_2.TabIndex = 97;
      this.tbAniDamage1_2.KeyPress += new KeyPressEventHandler(this.tbAniDamage1_2_KeyPress);
      this.tbSmc1_2.BorderStyle = BorderStyle.FixedSingle;
      this.tbSmc1_2.Location = new Point(64, 175);
      this.tbSmc1_2.Name = "tbSmc1_2";
      this.tbSmc1_2.Size = new Size(282, 20);
      this.tbSmc1_2.TabIndex = 65;
      this.tbSmc1_2.KeyPress += new KeyPressEventHandler(this.tbSmc1_2_KeyPress);
      this.label65.AutoSize = true;
      this.label65.Location = new Point(213, 75);
      this.label65.Name = "label65";
      this.label65.Size = new Size(47, 13);
      this.label65.TabIndex = 96;
      this.label65.Text = "Damage";
      this.tbAniIdle1_2.BorderStyle = BorderStyle.FixedSingle;
      this.tbAniIdle1_2.Location = new Point(50, 19);
      this.tbAniIdle1_2.Name = "tbAniIdle1_2";
      this.tbAniIdle1_2.Size = new Size((int) sbyte.MaxValue, 20);
      this.tbAniIdle1_2.TabIndex = 63;
      this.tbAniIdle1_2.KeyPress += new KeyPressEventHandler(this.tbAniIdle1_2_KeyPress);
      this.label49.AutoSize = true;
      this.label49.Location = new Point(11, 21);
      this.label49.Name = "label49";
      this.label49.Size = new Size(33, 13);
      this.label49.TabIndex = 62;
      this.label49.Text = "Idle 1";
      this.tbAniIdle2_2.BorderStyle = BorderStyle.FixedSingle;
      this.tbAniIdle2_2.Location = new Point(50, 45);
      this.tbAniIdle2_2.Name = "tbAniIdle2_2";
      this.tbAniIdle2_2.Size = new Size((int) sbyte.MaxValue, 20);
      this.tbAniIdle2_2.TabIndex = 67;
      this.tbAniIdle2_2.KeyPress += new KeyPressEventHandler(this.tbAniIdle2_2_KeyPress);
      this.label54.AutoSize = true;
      this.label54.Location = new Point(11, 47);
      this.label54.Name = "label54";
      this.label54.Size = new Size(33, 13);
      this.label54.TabIndex = 66;
      this.label54.Text = "Idle 2";
      this.tbAniRun1_2.BorderStyle = BorderStyle.FixedSingle;
      this.tbAniRun1_2.Location = new Point(248, 45);
      this.tbAniRun1_2.Name = "tbAniRun1_2";
      this.tbAniRun1_2.Size = new Size(155, 20);
      this.tbAniRun1_2.TabIndex = 85;
      this.tbAniRun1_2.KeyPress += new KeyPressEventHandler(this.tbAniRun1_2_KeyPress);
      this.label56.AutoSize = true;
      this.label56.Location = new Point(213, 47);
      this.label56.Name = "label56";
      this.label56.Size = new Size(27, 13);
      this.label56.TabIndex = 84;
      this.label56.Text = "Run";
      this.tbSkillSummon1_2.BorderStyle = BorderStyle.FixedSingle;
      this.tbSkillSummon1_2.Location = new Point(283, 123);
      this.tbSkillSummon1_2.Name = "tbSkillSummon1_2";
      this.tbSkillSummon1_2.Size = new Size(117, 20);
      this.tbSkillSummon1_2.TabIndex = 93;
      this.tbSkillSummon1_2.TextChanged += new EventHandler(this.tbSkillSummon1_2_TextChanged);
      this.tbSkillSummon1_2.KeyPress += new KeyPressEventHandler(this.tbSkillSummon1_2_KeyPress);
      this.tbAniWalk1_2.BorderStyle = BorderStyle.FixedSingle;
      this.tbAniWalk1_2.Location = new Point(248, 19);
      this.tbAniWalk1_2.Name = "tbAniWalk1_2";
      this.tbAniWalk1_2.Size = new Size(155, 20);
      this.tbAniWalk1_2.TabIndex = 81;
      this.tbAniWalk1_2.KeyPress += new KeyPressEventHandler(this.tbAniWalk1_2_KeyPress);
      this.tbAniAttack1_2.BorderStyle = BorderStyle.FixedSingle;
      this.tbAniAttack1_2.Location = new Point(64, 71);
      this.tbAniAttack1_2.Name = "tbAniAttack1_2";
      this.tbAniAttack1_2.Size = new Size(113, 20);
      this.tbAniAttack1_2.TabIndex = 75;
      this.tbAniAttack1_2.KeyPress += new KeyPressEventHandler(this.tbAniAttack1_2_KeyPress);
      this.label58.AutoSize = true;
      this.label58.Location = new Point(213, 21);
      this.label58.Name = "label58";
      this.label58.Size = new Size(32, 13);
      this.label58.TabIndex = 80;
      this.label58.Text = "Walk";
      this.label60.AutoSize = true;
      this.label60.Location = new Point(213, 130);
      this.label60.Name = "label60";
      this.label60.Size = new Size(70, 13);
      this.label60.TabIndex = 92;
      this.label60.Text = "Skill Summon";
      this.label50.AutoSize = true;
      this.label50.Location = new Point(11, 73);
      this.label50.Name = "label50";
      this.label50.Size = new Size(47, 13);
      this.label50.TabIndex = 74;
      this.label50.Text = "Attack 1";
      this.tbLevelUp1_2.BorderStyle = BorderStyle.FixedSingle;
      this.tbLevelUp1_2.Location = new Point(265, 97);
      this.tbLevelUp1_2.Name = "tbLevelUp1_2";
      this.tbLevelUp1_2.Size = new Size(136, 20);
      this.tbLevelUp1_2.TabIndex = 89;
      this.tbLevelUp1_2.KeyPress += new KeyPressEventHandler(this.tbLevelUp1_2_KeyPress);
      this.label62.AutoSize = true;
      this.label62.Location = new Point(213, 104);
      this.label62.Name = "label62";
      this.label62.Size = new Size(51, 13);
      this.label62.TabIndex = 88;
      this.label62.Text = "Level UP";
      this.tbSpeed1_2.BorderStyle = BorderStyle.FixedSingle;
      this.tbSpeed1_2.Location = new Point(266, 149);
      this.tbSpeed1_2.Name = "tbSpeed1_2";
      this.tbSpeed1_2.Size = new Size(134, 20);
      this.tbSpeed1_2.TabIndex = 91;
      this.tbSpeed1_2.KeyPress += new KeyPressEventHandler(this.tbSpeed1_2_KeyPress);
      this.tbAniAttack2_2.BorderStyle = BorderStyle.FixedSingle;
      this.tbAniAttack2_2.Location = new Point(64, 97);
      this.tbAniAttack2_2.Name = "tbAniAttack2_2";
      this.tbAniAttack2_2.Size = new Size(113, 20);
      this.tbAniAttack2_2.TabIndex = 79;
      this.tbAniAttack2_2.KeyPress += new KeyPressEventHandler(this.tbAniAttack2_2_KeyPress);
      this.label61.AutoSize = true;
      this.label61.Location = new Point(213, 151);
      this.label61.Name = "label61";
      this.label61.Size = new Size(38, 13);
      this.label61.TabIndex = 90;
      this.label61.Text = "Speed";
      this.label59.AutoSize = true;
      this.label59.Location = new Point(11, 99);
      this.label59.Name = "label59";
      this.label59.Size = new Size(47, 13);
      this.label59.TabIndex = 78;
      this.label59.Text = "Attack 2";
      this.tbAniDie1_2.BorderStyle = BorderStyle.FixedSingle;
      this.tbAniDie1_2.Location = new Point(64, 123);
      this.tbAniDie1_2.Name = "tbAniDie1_2";
      this.tbAniDie1_2.Size = new Size(113, 20);
      this.tbAniDie1_2.TabIndex = 83;
      this.tbAniDie1_2.KeyPress += new KeyPressEventHandler(this.tbAniDie1_2_KeyPress);
      this.label57.AutoSize = true;
      this.label57.Location = new Point(11, 125);
      this.label57.Name = "label57";
      this.label57.Size = new Size(23, 13);
      this.label57.TabIndex = 82;
      this.label57.Text = "Die";
      this.label63.AutoSize = true;
      this.label63.Location = new Point(11, 151);
      this.label63.Name = "label63";
      this.label63.Size = new Size(37, 13);
      this.label63.TabIndex = 86;
      this.label63.Text = "Mount";
      this.tbMount1_2.BorderStyle = BorderStyle.FixedSingle;
      this.tbMount1_2.Location = new Point(138, 149);
      this.tbMount1_2.Name = "tbMount1_2";
      this.tbMount1_2.Size = new Size(32, 20);
      this.tbMount1_2.TabIndex = 87;
      this.tbMount1_2.KeyPress += new KeyPressEventHandler(this.tbMount1_2_KeyPress);
      this.groupBox6.Controls.Add((Control) this.cbMount1);
      this.groupBox6.Controls.Add((Control) this.pictureBox4);
      this.groupBox6.Controls.Add((Control) this.button1);
      this.groupBox6.Controls.Add((Control) this.btnLevelup1);
      this.groupBox6.Controls.Add((Control) this.BtnAniAttack2);
      this.groupBox6.Controls.Add((Control) this.btnAniIdle2);
      this.groupBox6.Controls.Add((Control) this.btnAniRun);
      this.groupBox6.Controls.Add((Control) this.btnAniDie);
      this.groupBox6.Controls.Add((Control) this.BtnAniAttack1);
      this.groupBox6.Controls.Add((Control) this.BtnAniDam);
      this.groupBox6.Controls.Add((Control) this.BtnAniIdle);
      this.groupBox6.Controls.Add((Control) this.BtnAniWalk);
      this.groupBox6.Controls.Add((Control) this.BtnReadSmc);
      this.groupBox6.Controls.Add((Control) this.tbSmc1_1);
      this.groupBox6.Controls.Add((Control) this.label17);
      this.groupBox6.Controls.Add((Control) this.tbAniAttack2_1);
      this.groupBox6.Controls.Add((Control) this.label44);
      this.groupBox6.Controls.Add((Control) this.tbSpeed1_1);
      this.groupBox6.Controls.Add((Control) this.label48);
      this.groupBox6.Controls.Add((Control) this.tbAniDamage1_1);
      this.groupBox6.Controls.Add((Control) this.label45);
      this.groupBox6.Controls.Add((Control) this.tbSkillSummon1_1);
      this.groupBox6.Controls.Add((Control) this.label64);
      this.groupBox6.Controls.Add((Control) this.tbAniAttack1_1);
      this.groupBox6.Controls.Add((Control) this.label52);
      this.groupBox6.Controls.Add((Control) this.tbAniIdle2_1);
      this.groupBox6.Controls.Add((Control) this.label40);
      this.groupBox6.Controls.Add((Control) this.tbMount1_1);
      this.groupBox6.Controls.Add((Control) this.label55);
      this.groupBox6.Controls.Add((Control) this.tbAniIdle1_1);
      this.groupBox6.Controls.Add((Control) this.label31);
      this.groupBox6.Controls.Add((Control) this.tbAniDie1_1);
      this.groupBox6.Controls.Add((Control) this.tbAniWalk1_1);
      this.groupBox6.Controls.Add((Control) this.label43);
      this.groupBox6.Controls.Add((Control) this.label32);
      this.groupBox6.Controls.Add((Control) this.label46);
      this.groupBox6.Controls.Add((Control) this.tbAniRun1_1);
      this.groupBox6.Controls.Add((Control) this.tbLevelUp1_1);
      this.groupBox6.Controls.Add((Control) this.label53);
      this.groupBox6.Location = new Point(6, 10);
      this.groupBox6.Name = "groupBox6";
      this.groupBox6.Size = new Size(431, 207);
      this.groupBox6.TabIndex = 66;
      this.groupBox6.TabStop = false;
      this.groupBox6.Text = "Animations 1";
      this.cbMount1.AutoSize = true;
      this.cbMount1.FlatStyle = FlatStyle.Flat;
      this.cbMount1.Location = new Point(59, 151);
      this.cbMount1.Name = "cbMount1";
      this.cbMount1.Size = new Size(70, 17);
      this.cbMount1.TabIndex = 114;
      this.cbMount1.Text = "NotMount";
      this.cbMount1.UseVisualStyleBackColor = true;
      this.cbMount1.CheckedChanged += new EventHandler(this.cbMount1_CheckedChanged);
      this.pictureBox4.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.oie_transparent;
      this.pictureBox4.BackgroundImageLayout = ImageLayout.Stretch;
      this.pictureBox4.Location = new Point(381, 173);
      this.pictureBox4.Name = "pictureBox4";
      this.pictureBox4.Size = new Size(22, 22);
      this.pictureBox4.TabIndex = 113;
      this.pictureBox4.TabStop = false;
      this.pictureBox4.Click += new EventHandler(this.pictureBox4_Click);
      this.button1.BackColor = SystemColors.Control;
      this.button1.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.search;
      this.button1.BackgroundImageLayout = ImageLayout.Stretch;
      this.button1.FlatAppearance.BorderSize = 0;
      this.button1.FlatStyle = FlatStyle.Flat;
      this.button1.Location = new Point(404, 123);
      this.button1.Name = "button1";
      this.button1.Size = new Size(20, 20);
      this.button1.TabIndex = 112;
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.btnLevelup1.BackColor = SystemColors.Control;
      this.btnLevelup1.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.search;
      this.btnLevelup1.BackgroundImageLayout = ImageLayout.Stretch;
      this.btnLevelup1.FlatAppearance.BorderSize = 0;
      this.btnLevelup1.FlatStyle = FlatStyle.Flat;
      this.btnLevelup1.Location = new Point(404, 99);
      this.btnLevelup1.Name = "btnLevelup1";
      this.btnLevelup1.Size = new Size(20, 20);
      this.btnLevelup1.TabIndex = 105;
      this.btnLevelup1.UseVisualStyleBackColor = true;
      this.btnLevelup1.Click += new EventHandler(this.AniFind);
      this.BtnAniAttack2.BackColor = SystemColors.Control;
      this.BtnAniAttack2.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.search;
      this.BtnAniAttack2.BackgroundImageLayout = ImageLayout.Stretch;
      this.BtnAniAttack2.FlatAppearance.BorderSize = 0;
      this.BtnAniAttack2.FlatStyle = FlatStyle.Flat;
      this.BtnAniAttack2.Location = new Point(181, 99);
      this.BtnAniAttack2.Name = "BtnAniAttack2";
      this.BtnAniAttack2.Size = new Size(20, 20);
      this.BtnAniAttack2.TabIndex = 104;
      this.BtnAniAttack2.UseVisualStyleBackColor = true;
      this.BtnAniAttack2.Click += new EventHandler(this.AniFind);
      this.btnAniIdle2.BackColor = SystemColors.Control;
      this.btnAniIdle2.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.search;
      this.btnAniIdle2.BackgroundImageLayout = ImageLayout.Stretch;
      this.btnAniIdle2.FlatAppearance.BorderSize = 0;
      this.btnAniIdle2.FlatStyle = FlatStyle.Flat;
      this.btnAniIdle2.Location = new Point(181, 46);
      this.btnAniIdle2.Name = "btnAniIdle2";
      this.btnAniIdle2.Size = new Size(20, 20);
      this.btnAniIdle2.TabIndex = 103;
      this.btnAniIdle2.UseVisualStyleBackColor = true;
      this.btnAniIdle2.Click += new EventHandler(this.AniFind);
      this.btnAniRun.BackColor = SystemColors.Control;
      this.btnAniRun.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.search;
      this.btnAniRun.BackgroundImageLayout = ImageLayout.Stretch;
      this.btnAniRun.FlatAppearance.BorderSize = 0;
      this.btnAniRun.FlatStyle = FlatStyle.Flat;
      this.btnAniRun.Location = new Point(404, 45);
      this.btnAniRun.Name = "btnAniRun";
      this.btnAniRun.Size = new Size(20, 20);
      this.btnAniRun.TabIndex = 102;
      this.btnAniRun.UseVisualStyleBackColor = true;
      this.btnAniRun.Click += new EventHandler(this.AniFind);
      this.btnAniDie.BackColor = SystemColors.Control;
      this.btnAniDie.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.search;
      this.btnAniDie.BackgroundImageLayout = ImageLayout.Stretch;
      this.btnAniDie.FlatAppearance.BorderSize = 0;
      this.btnAniDie.FlatStyle = FlatStyle.Flat;
      this.btnAniDie.Location = new Point(181, 123);
      this.btnAniDie.Name = "btnAniDie";
      this.btnAniDie.Size = new Size(20, 20);
      this.btnAniDie.TabIndex = 101;
      this.btnAniDie.UseVisualStyleBackColor = true;
      this.btnAniDie.Click += new EventHandler(this.AniFind);
      this.BtnAniAttack1.BackColor = SystemColors.Control;
      this.BtnAniAttack1.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.search;
      this.BtnAniAttack1.BackgroundImageLayout = ImageLayout.Stretch;
      this.BtnAniAttack1.FlatAppearance.BorderSize = 0;
      this.BtnAniAttack1.FlatStyle = FlatStyle.Flat;
      this.BtnAniAttack1.Location = new Point(181, 71);
      this.BtnAniAttack1.Name = "BtnAniAttack1";
      this.BtnAniAttack1.Size = new Size(20, 20);
      this.BtnAniAttack1.TabIndex = 100;
      this.BtnAniAttack1.UseVisualStyleBackColor = true;
      this.BtnAniAttack1.Click += new EventHandler(this.AniFind);
      this.BtnAniDam.BackColor = SystemColors.Control;
      this.BtnAniDam.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.search;
      this.BtnAniDam.BackgroundImageLayout = ImageLayout.Stretch;
      this.BtnAniDam.FlatAppearance.BorderSize = 0;
      this.BtnAniDam.FlatStyle = FlatStyle.Flat;
      this.BtnAniDam.Location = new Point(404, 71);
      this.BtnAniDam.Name = "BtnAniDam";
      this.BtnAniDam.Size = new Size(20, 20);
      this.BtnAniDam.TabIndex = 99;
      this.BtnAniDam.UseVisualStyleBackColor = true;
      this.BtnAniDam.Click += new EventHandler(this.AniFind);
      this.BtnAniIdle.BackColor = SystemColors.Control;
      this.BtnAniIdle.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.search;
      this.BtnAniIdle.BackgroundImageLayout = ImageLayout.Stretch;
      this.BtnAniIdle.FlatAppearance.BorderSize = 0;
      this.BtnAniIdle.FlatStyle = FlatStyle.Flat;
      this.BtnAniIdle.Location = new Point(181, 19);
      this.BtnAniIdle.Name = "BtnAniIdle";
      this.BtnAniIdle.Size = new Size(20, 20);
      this.BtnAniIdle.TabIndex = 98;
      this.BtnAniIdle.UseVisualStyleBackColor = true;
      this.BtnAniIdle.Click += new EventHandler(this.AniFind);
      this.BtnAniWalk.BackColor = SystemColors.Control;
      this.BtnAniWalk.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.search;
      this.BtnAniWalk.BackgroundImageLayout = ImageLayout.Stretch;
      this.BtnAniWalk.FlatAppearance.BorderSize = 0;
      this.BtnAniWalk.FlatStyle = FlatStyle.Flat;
      this.BtnAniWalk.Location = new Point(404, 17);
      this.BtnAniWalk.Name = "BtnAniWalk";
      this.BtnAniWalk.Size = new Size(20, 20);
      this.BtnAniWalk.TabIndex = 97;
      this.BtnAniWalk.UseVisualStyleBackColor = true;
      this.BtnAniWalk.Click += new EventHandler(this.AniFind);
      this.BtnReadSmc.BackColor = SystemColors.Control;
      this.BtnReadSmc.BackgroundImage = (Image) LcDevPack_TeamDamonA.Properties.Resources.search;
      this.BtnReadSmc.BackgroundImageLayout = ImageLayout.Stretch;
      this.BtnReadSmc.FlatAppearance.BorderSize = 0;
      this.BtnReadSmc.FlatStyle = FlatStyle.Flat;
      this.BtnReadSmc.Location = new Point(355, 175);
      this.BtnReadSmc.Name = "BtnReadSmc";
      this.BtnReadSmc.Size = new Size(20, 20);
      this.BtnReadSmc.TabIndex = 96;
      this.BtnReadSmc.UseVisualStyleBackColor = true;
      this.BtnReadSmc.Click += new EventHandler(this.BtnReadSmc_Click);
      this.tbSmc1_1.BorderStyle = BorderStyle.FixedSingle;
      this.tbSmc1_1.Location = new Point(59, 175);
      this.tbSmc1_1.Name = "tbSmc1_1";
      this.tbSmc1_1.Size = new Size(290, 20);
      this.tbSmc1_1.TabIndex = 66;
      this.tbSmc1_1.KeyPress += new KeyPressEventHandler(this.tbSmc1_1_KeyPress);
      this.label17.AutoSize = true;
      this.label17.Location = new Point(6, 177);
      this.label17.Name = "label17";
      this.label17.Size = new Size(33, 13);
      this.label17.TabIndex = 65;
      this.label17.Text = "SMC:";
      this.tbAniAttack2_1.BorderStyle = BorderStyle.FixedSingle;
      this.tbAniAttack2_1.Location = new Point(59, 97);
      this.tbAniAttack2_1.Name = "tbAniAttack2_1";
      this.tbAniAttack2_1.Size = new Size(116, 20);
      this.tbAniAttack2_1.TabIndex = 47;
      this.tbAniAttack2_1.KeyPress += new KeyPressEventHandler(this.tbAniAttack2_1_KeyPress);
      this.label44.AutoSize = true;
      this.label44.Location = new Point(6, 74);
      this.label44.Name = "label44";
      this.label44.Size = new Size(47, 13);
      this.label44.TabIndex = 48;
      this.label44.Text = "Attack 1";
      this.tbSpeed1_1.BorderStyle = BorderStyle.FixedSingle;
      this.tbSpeed1_1.Location = new Point(260, 148);
      this.tbSpeed1_1.Name = "tbSpeed1_1";
      this.tbSpeed1_1.Size = new Size(140, 20);
      this.tbSpeed1_1.TabIndex = 77;
      this.tbSpeed1_1.KeyPress += new KeyPressEventHandler(this.tbSpeed1_1_KeyPress);
      this.label48.AutoSize = true;
      this.label48.Location = new Point(207, 151);
      this.label48.Name = "label48";
      this.label48.Size = new Size(38, 13);
      this.label48.TabIndex = 76;
      this.label48.Text = "Speed";
      this.tbAniDamage1_1.BorderStyle = BorderStyle.FixedSingle;
      this.tbAniDamage1_1.Location = new Point(260, 71);
      this.tbAniDamage1_1.Name = "tbAniDamage1_1";
      this.tbAniDamage1_1.Size = new Size(140, 20);
      this.tbAniDamage1_1.TabIndex = 95;
      this.tbAniDamage1_1.KeyPress += new KeyPressEventHandler(this.tbAniDamage1_1_KeyPress);
      this.label45.AutoSize = true;
      this.label45.Location = new Point(6, 100);
      this.label45.Name = "label45";
      this.label45.Size = new Size(47, 13);
      this.label45.TabIndex = 46;
      this.label45.Text = "Attack 2";
      this.tbSkillSummon1_1.BorderStyle = BorderStyle.FixedSingle;
      this.tbSkillSummon1_1.Location = new Point(283, 123);
      this.tbSkillSummon1_1.Name = "tbSkillSummon1_1";
      this.tbSkillSummon1_1.Size = new Size(117, 20);
      this.tbSkillSummon1_1.TabIndex = 73;
      this.tbSkillSummon1_1.TextChanged += new EventHandler(this.tbSkillSummon1_1_TextChanged);
      this.tbSkillSummon1_1.KeyPress += new KeyPressEventHandler(this.tbSkillSummon1_1_KeyPress);
      this.label64.AutoSize = true;
      this.label64.Location = new Point(207, 73);
      this.label64.Name = "label64";
      this.label64.Size = new Size(47, 13);
      this.label64.TabIndex = 94;
      this.label64.Text = "Damage";
      this.tbAniAttack1_1.BorderStyle = BorderStyle.FixedSingle;
      this.tbAniAttack1_1.Location = new Point(59, 71);
      this.tbAniAttack1_1.Name = "tbAniAttack1_1";
      this.tbAniAttack1_1.Size = new Size(116, 20);
      this.tbAniAttack1_1.TabIndex = 49;
      this.tbAniAttack1_1.KeyPress += new KeyPressEventHandler(this.tbAniAttack1_1_KeyPress);
      this.label52.AutoSize = true;
      this.label52.Location = new Point(207, 125);
      this.label52.Name = "label52";
      this.label52.Size = new Size(70, 13);
      this.label52.TabIndex = 72;
      this.label52.Text = "Skill Summon";
      this.tbAniIdle2_1.BorderStyle = BorderStyle.FixedSingle;
      this.tbAniIdle2_1.Location = new Point(45, 45);
      this.tbAniIdle2_1.Name = "tbAniIdle2_1";
      this.tbAniIdle2_1.Size = new Size(130, 20);
      this.tbAniIdle2_1.TabIndex = 61;
      this.tbAniIdle2_1.KeyPress += new KeyPressEventHandler(this.tbAniIdle2_1_KeyPress);
      this.label40.AutoSize = true;
      this.label40.Location = new Point(6, 19);
      this.label40.Name = "label40";
      this.label40.Size = new Size(33, 13);
      this.label40.TabIndex = 56;
      this.label40.Text = "Idle 1";
      this.tbMount1_1.BorderStyle = BorderStyle.FixedSingle;
      this.tbMount1_1.Location = new Point(138, 149);
      this.tbMount1_1.Name = "tbMount1_1";
      this.tbMount1_1.Size = new Size(27, 20);
      this.tbMount1_1.TabIndex = 69;
      this.tbMount1_1.KeyPress += new KeyPressEventHandler(this.tbMount1_1_KeyPress);
      this.label55.AutoSize = true;
      this.label55.Location = new Point(6, 155);
      this.label55.Name = "label55";
      this.label55.Size = new Size(37, 13);
      this.label55.TabIndex = 68;
      this.label55.Text = "Mount";
      this.tbAniIdle1_1.BorderStyle = BorderStyle.FixedSingle;
      this.tbAniIdle1_1.Location = new Point(45, 19);
      this.tbAniIdle1_1.Name = "tbAniIdle1_1";
      this.tbAniIdle1_1.Size = new Size(130, 20);
      this.tbAniIdle1_1.TabIndex = 57;
      this.tbAniIdle1_1.KeyPress += new KeyPressEventHandler(this.tbAniIdle1_1_KeyPress);
      this.label31.AutoSize = true;
      this.label31.Location = new Point(6, 45);
      this.label31.Name = "label31";
      this.label31.Size = new Size(33, 13);
      this.label31.TabIndex = 60;
      this.label31.Text = "Idle 2";
      this.tbAniDie1_1.BorderStyle = BorderStyle.FixedSingle;
      this.tbAniDie1_1.Location = new Point(59, 123);
      this.tbAniDie1_1.Name = "tbAniDie1_1";
      this.tbAniDie1_1.Size = new Size(116, 20);
      this.tbAniDie1_1.TabIndex = 45;
      this.tbAniDie1_1.KeyPress += new KeyPressEventHandler(this.tbAniDie1_1_KeyPress);
      this.tbAniWalk1_1.BorderStyle = BorderStyle.FixedSingle;
      this.tbAniWalk1_1.Location = new Point(245, 19);
      this.tbAniWalk1_1.Name = "tbAniWalk1_1";
      this.tbAniWalk1_1.Size = new Size(155, 20);
      this.tbAniWalk1_1.TabIndex = 51;
      this.tbAniWalk1_1.KeyPress += new KeyPressEventHandler(this.tbAniWalk1_1_KeyPress);
      this.label43.AutoSize = true;
      this.label43.Location = new Point(207, 21);
      this.label43.Name = "label43";
      this.label43.Size = new Size(32, 13);
      this.label43.TabIndex = 50;
      this.label43.Text = "Walk";
      this.label32.AutoSize = true;
      this.label32.Location = new Point(207, 47);
      this.label32.Name = "label32";
      this.label32.Size = new Size(27, 13);
      this.label32.TabIndex = 58;
      this.label32.Text = "Run";
      this.label46.AutoSize = true;
      this.label46.Location = new Point(6, (int) sbyte.MaxValue);
      this.label46.Name = "label46";
      this.label46.Size = new Size(23, 13);
      this.label46.TabIndex = 44;
      this.label46.Text = "Die";
      this.tbAniRun1_1.BorderStyle = BorderStyle.FixedSingle;
      this.tbAniRun1_1.Location = new Point(245, 45);
      this.tbAniRun1_1.Name = "tbAniRun1_1";
      this.tbAniRun1_1.Size = new Size(155, 20);
      this.tbAniRun1_1.TabIndex = 59;
      this.tbAniRun1_1.KeyPress += new KeyPressEventHandler(this.tbAniRun1_1_KeyPress);
      this.tbLevelUp1_1.BorderStyle = BorderStyle.FixedSingle;
      this.tbLevelUp1_1.Location = new Point(264, 98);
      this.tbLevelUp1_1.Name = "tbLevelUp1_1";
      this.tbLevelUp1_1.Size = new Size(136, 20);
      this.tbLevelUp1_1.TabIndex = 71;
      this.tbLevelUp1_1.KeyPress += new KeyPressEventHandler(this.tbLevelUp1_1_KeyPress);
      this.label53.AutoSize = true;
      this.label53.Location = new Point(207, 99);
      this.label53.Name = "label53";
      this.label53.Size = new Size(51, 13);
      this.label53.TabIndex = 70;
      this.label53.Text = "Level UP";
      this.groupBox5.Controls.Add((Control) this.label47);
      this.groupBox5.Controls.Add((Control) this.tbTransType);
      this.groupBox5.Controls.Add((Control) this.tbTransStart);
      this.groupBox5.Controls.Add((Control) this.label41);
      this.groupBox5.Controls.Add((Control) this.tbTransEnd);
      this.groupBox5.Controls.Add((Control) this.label42);
      this.groupBox5.Location = new Point(443, 10);
      this.groupBox5.Name = "groupBox5";
      this.groupBox5.Size = new Size(144, 119);
      this.groupBox5.TabIndex = 65;
      this.groupBox5.TabStop = false;
      this.groupBox5.Text = "Trans";
      this.label47.AutoSize = true;
      this.label47.Location = new Point(10, 36);
      this.label47.Name = "label47";
      this.label47.Size = new Size(64, 13);
      this.label47.TabIndex = 42;
      this.label47.Text = "Trans Type:";
      this.tbTransType.BorderStyle = BorderStyle.FixedSingle;
      this.tbTransType.Location = new Point(105, 35);
      this.tbTransType.Name = "tbTransType";
      this.tbTransType.Size = new Size(33, 20);
      this.tbTransType.TabIndex = 43;
      this.tbTransType.KeyPress += new KeyPressEventHandler(this.tbTransType_KeyPress);
      this.tbTransStart.BorderStyle = BorderStyle.FixedSingle;
      this.tbTransStart.Location = new Point(105, 61);
      this.tbTransStart.Name = "tbTransStart";
      this.tbTransStart.Size = new Size(33, 20);
      this.tbTransStart.TabIndex = 55;
      this.tbTransStart.KeyPress += new KeyPressEventHandler(this.tbTransStart_KeyPress);
      this.label41.AutoSize = true;
      this.label41.Location = new Point(10, 62);
      this.label41.Name = "label41";
      this.label41.Size = new Size(62, 13);
      this.label41.TabIndex = 54;
      this.label41.Text = "Trans Start:";
      this.tbTransEnd.BorderStyle = BorderStyle.FixedSingle;
      this.tbTransEnd.Location = new Point(105, 87);
      this.tbTransEnd.Name = "tbTransEnd";
      this.tbTransEnd.Size = new Size(33, 20);
      this.tbTransEnd.TabIndex = 53;
      this.tbTransEnd.KeyPress += new KeyPressEventHandler(this.tbTransEnd_KeyPress);
      this.label42.AutoSize = true;
      this.label42.Location = new Point(10, 88);
      this.label42.Name = "label42";
      this.label42.Size = new Size(56, 13);
      this.label42.TabIndex = 52;
      this.label42.Text = "Trans End";
      this.tabPage3.BackColor = SystemColors.Control;
      this.tabPage3.Controls.Add((Control) this.groupBox9);
      this.tabPage3.Location = new Point(4, 22);
      this.tabPage3.Name = "tabPage3";
      this.tabPage3.Padding = new Padding(3);
      this.tabPage3.Size = new Size(620, 464);
      this.tabPage3.TabIndex = 2;
      this.tabPage3.Text = "Pet Evolution";
      this.groupBox9.Controls.Add((Control) this.tb_ev_order);
      this.groupBox9.Controls.Add((Control) this.label79);
      this.groupBox9.Controls.Add((Control) this.tb_ev_stat2);
      this.groupBox9.Controls.Add((Control) this.label78);
      this.groupBox9.Controls.Add((Control) this.tb_ev_stat1);
      this.groupBox9.Controls.Add((Control) this.label77);
      this.groupBox9.Controls.Add((Control) this.tb_ev_Faith);
      this.groupBox9.Controls.Add((Control) this.label76);
      this.groupBox9.Controls.Add((Control) this.tb_ev_Stemina);
      this.groupBox9.Controls.Add((Control) this.label75);
      this.groupBox9.Controls.Add((Control) this.tb_ev_Level);
      this.groupBox9.Controls.Add((Control) this.label73);
      this.groupBox9.Controls.Add((Control) this.tb_to_ev_id);
      this.groupBox9.Controls.Add((Control) this.label72);
      this.groupBox9.Controls.Add((Control) this.tb_ev_ID);
      this.groupBox9.Controls.Add((Control) this.label74);
      this.groupBox9.Enabled = false;
      this.groupBox9.Location = new Point(6, 6);
      this.groupBox9.Name = "groupBox9";
      this.groupBox9.Size = new Size(239, 205);
      this.groupBox9.TabIndex = 1;
      this.groupBox9.TabStop = false;
      this.groupBox9.Text = "Basic";
      this.tb_ev_order.Location = new Point((int) sbyte.MaxValue, 174);
      this.tb_ev_order.Name = "tb_ev_order";
      this.tb_ev_order.Size = new Size(39, 20);
      this.tb_ev_order.TabIndex = 17;
      this.tb_ev_order.KeyPress += new KeyPressEventHandler(this.tb_ev_order_KeyPress);
      this.label79.AutoSize = true;
      this.label79.Location = new Point(6, 177);
      this.label79.Name = "label79";
      this.label79.Size = new Size(39, 13);
      this.label79.TabIndex = 16;
      this.label79.Text = "Order :";
      this.tb_ev_stat2.Location = new Point((int) sbyte.MaxValue, 148);
      this.tb_ev_stat2.Name = "tb_ev_stat2";
      this.tb_ev_stat2.Size = new Size(39, 20);
      this.tb_ev_stat2.TabIndex = 15;
      this.tb_ev_stat2.KeyPress += new KeyPressEventHandler(this.tb_ev_stat2_KeyPress);
      this.label78.AutoSize = true;
      this.label78.Location = new Point(6, 151);
      this.label78.Name = "label78";
      this.label78.Size = new Size(41, 13);
      this.label78.TabIndex = 14;
      this.label78.Text = "Stat 2 :";
      this.tb_ev_stat1.Location = new Point((int) sbyte.MaxValue, 122);
      this.tb_ev_stat1.Name = "tb_ev_stat1";
      this.tb_ev_stat1.Size = new Size(39, 20);
      this.tb_ev_stat1.TabIndex = 13;
      this.tb_ev_stat1.KeyPress += new KeyPressEventHandler(this.tb_ev_stat1_KeyPress);
      this.label77.AutoSize = true;
      this.label77.Location = new Point(6, 125);
      this.label77.Name = "label77";
      this.label77.Size = new Size(41, 13);
      this.label77.TabIndex = 12;
      this.label77.Text = "Stat 1 :";
      this.tb_ev_Faith.Location = new Point((int) sbyte.MaxValue, 96);
      this.tb_ev_Faith.Name = "tb_ev_Faith";
      this.tb_ev_Faith.Size = new Size(39, 20);
      this.tb_ev_Faith.TabIndex = 11;
      this.tb_ev_Faith.KeyPress += new KeyPressEventHandler(this.tb_ev_Faith_KeyPress);
      this.label76.AutoSize = true;
      this.label76.Location = new Point(6, 99);
      this.label76.Name = "label76";
      this.label76.Size = new Size(36, 13);
      this.label76.TabIndex = 10;
      this.label76.Text = "Faith :";
      this.tb_ev_Stemina.Location = new Point((int) sbyte.MaxValue, 70);
      this.tb_ev_Stemina.Name = "tb_ev_Stemina";
      this.tb_ev_Stemina.Size = new Size(39, 20);
      this.tb_ev_Stemina.TabIndex = 9;
      this.tb_ev_Stemina.KeyPress += new KeyPressEventHandler(this.tb_ev_Stemina_KeyPress);
      this.label75.AutoSize = true;
      this.label75.Location = new Point(6, 73);
      this.label75.Name = "label75";
      this.label75.Size = new Size(51, 13);
      this.label75.TabIndex = 8;
      this.label75.Text = "Stemina :";
      this.tb_ev_Level.Location = new Point((int) sbyte.MaxValue, 45);
      this.tb_ev_Level.Name = "tb_ev_Level";
      this.tb_ev_Level.Size = new Size(39, 20);
      this.tb_ev_Level.TabIndex = 7;
      this.tb_ev_Level.KeyPress += new KeyPressEventHandler(this.tb_ev_Level_KeyPress);
      this.label73.AutoSize = true;
      this.label73.Location = new Point(6, 48);
      this.label73.Name = "label73";
      this.label73.Size = new Size(115, 13);
      this.label73.TabIndex = 6;
      this.label73.Text = "Evolution Need Level :";
      this.tb_to_ev_id.Location = new Point(189, 19);
      this.tb_to_ev_id.Name = "tb_to_ev_id";
      this.tb_to_ev_id.Size = new Size(39, 20);
      this.tb_to_ev_id.TabIndex = 5;
      this.tb_to_ev_id.KeyPress += new KeyPressEventHandler(this.tb_to_ev_id_KeyPress);
      this.label72.AutoSize = true;
      this.label72.Location = new Point(103, 22);
      this.label72.Name = "label72";
      this.label72.Size = new Size(80, 13);
      this.label72.TabIndex = 4;
      this.label72.Text = "Evolution to ID:";
      this.tb_ev_ID.Location = new Point(58, 19);
      this.tb_ev_ID.Name = "tb_ev_ID";
      this.tb_ev_ID.Size = new Size(39, 20);
      this.tb_ev_ID.TabIndex = 3;
      this.tb_ev_ID.KeyPress += new KeyPressEventHandler(this.tb_ev_ID_KeyPress);
      this.label74.AutoSize = true;
      this.label74.Location = new Point(6, 22);
      this.label74.Name = "label74";
      this.label74.Size = new Size(46, 13);
      this.label74.TabIndex = 0;
      this.label74.Text = "Start ID:";
      this.tabPage4.BackColor = SystemColors.Control;
      this.tabPage4.Controls.Add((Control) this.groupBox10);
      this.tabPage4.Location = new Point(4, 22);
      this.tabPage4.Name = "tabPage4";
      this.tabPage4.Padding = new Padding(3);
      this.tabPage4.Size = new Size(620, 464);
      this.tabPage4.TabIndex = 3;
      this.tabPage4.Text = "Pet Experience";
      this.groupBox10.Controls.Add((Control) this.tb_exp_a_cooltime_rate);
      this.groupBox10.Controls.Add((Control) this.label81);
      this.groupBox10.Controls.Add((Control) this.tb_exp_a_cooltime);
      this.groupBox10.Controls.Add((Control) this.label82);
      this.groupBox10.Controls.Add((Control) this.tb_exp_a_acc_rate_param2);
      this.groupBox10.Controls.Add((Control) this.label83);
      this.groupBox10.Controls.Add((Control) this.tb_exp_a_acc_rate_param1);
      this.groupBox10.Controls.Add((Control) this.label84);
      this.groupBox10.Controls.Add((Control) this.tb_exp_a_max_acc_param2);
      this.groupBox10.Controls.Add((Control) this.label85);
      this.groupBox10.Controls.Add((Control) this.tb_exp_a_max_acc_param1);
      this.groupBox10.Controls.Add((Control) this.label86);
      this.groupBox10.Controls.Add((Control) this.tb_exp_a_pet_index);
      this.groupBox10.Controls.Add((Control) this.label88);
      this.groupBox10.Enabled = false;
      this.groupBox10.Location = new Point(6, 6);
      this.groupBox10.Name = "groupBox10";
      this.groupBox10.Size = new Size(200, 205);
      this.groupBox10.TabIndex = 2;
      this.groupBox10.TabStop = false;
      this.groupBox10.Text = "Basic";
      this.tb_exp_a_cooltime_rate.Location = new Point(152, 174);
      this.tb_exp_a_cooltime_rate.Name = "tb_exp_a_cooltime_rate";
      this.tb_exp_a_cooltime_rate.Size = new Size(39, 20);
      this.tb_exp_a_cooltime_rate.TabIndex = 17;
      this.tb_exp_a_cooltime_rate.KeyPress += new KeyPressEventHandler(this.tb_exp_a_cooltime_rate_KeyPress);
      this.label81.AutoSize = true;
      this.label81.Location = new Point(6, 177);
      this.label81.Name = "label81";
      this.label81.Size = new Size(77, 13);
      this.label81.TabIndex = 16;
      this.label81.Text = "CoolTime Rate";
      this.tb_exp_a_cooltime.Location = new Point(152, 148);
      this.tb_exp_a_cooltime.Name = "tb_exp_a_cooltime";
      this.tb_exp_a_cooltime.Size = new Size(39, 20);
      this.tb_exp_a_cooltime.TabIndex = 15;
      this.tb_exp_a_cooltime.KeyPress += new KeyPressEventHandler(this.tb_exp_a_cooltime_KeyPress);
      this.label82.AutoSize = true;
      this.label82.Location = new Point(6, 151);
      this.label82.Name = "label82";
      this.label82.Size = new Size(51, 13);
      this.label82.TabIndex = 14;
      this.label82.Text = "CoolTime";
      this.tb_exp_a_acc_rate_param2.Location = new Point(152, 122);
      this.tb_exp_a_acc_rate_param2.Name = "tb_exp_a_acc_rate_param2";
      this.tb_exp_a_acc_rate_param2.Size = new Size(39, 20);
      this.tb_exp_a_acc_rate_param2.TabIndex = 13;
      this.tb_exp_a_acc_rate_param2.KeyPress += new KeyPressEventHandler(this.tb_exp_a_acc_rate_param2_KeyPress);
      this.label83.AutoSize = true;
      this.label83.Location = new Point(6, 125);
      this.label83.Name = "label83";
      this.label83.Size = new Size(141, 13);
      this.label83.TabIndex = 12;
      this.label83.Text = "Max Player Experience Rate";
      this.tb_exp_a_acc_rate_param1.Location = new Point(152, 96);
      this.tb_exp_a_acc_rate_param1.Name = "tb_exp_a_acc_rate_param1";
      this.tb_exp_a_acc_rate_param1.Size = new Size(39, 20);
      this.tb_exp_a_acc_rate_param1.TabIndex = 11;
      this.tb_exp_a_acc_rate_param1.KeyPress += new KeyPressEventHandler(this.tb_exp_a_acc_rate_param1_KeyPress);
      this.label84.AutoSize = true;
      this.label84.Location = new Point(6, 99);
      this.label84.Name = "label84";
      this.label84.Size = new Size(128, 13);
      this.label84.TabIndex = 10;
      this.label84.Text = "Max Pet Experience Rate";
      this.tb_exp_a_max_acc_param2.Location = new Point(152, 70);
      this.tb_exp_a_max_acc_param2.Name = "tb_exp_a_max_acc_param2";
      this.tb_exp_a_max_acc_param2.Size = new Size(39, 20);
      this.tb_exp_a_max_acc_param2.TabIndex = 9;
      this.tb_exp_a_max_acc_param2.KeyPress += new KeyPressEventHandler(this.tb_exp_a_max_acc_param2_KeyPress);
      this.label85.AutoSize = true;
      this.label85.Location = new Point(6, 73);
      this.label85.Name = "label85";
      this.label85.Size = new Size(115, 13);
      this.label85.TabIndex = 8;
      this.label85.Text = "Max Player Experience";
      this.tb_exp_a_max_acc_param1.Location = new Point(152, 45);
      this.tb_exp_a_max_acc_param1.Name = "tb_exp_a_max_acc_param1";
      this.tb_exp_a_max_acc_param1.Size = new Size(39, 20);
      this.tb_exp_a_max_acc_param1.TabIndex = 7;
      this.tb_exp_a_max_acc_param1.KeyPress += new KeyPressEventHandler(this.tb_exp_a_max_acc_param1_KeyPress);
      this.label86.AutoSize = true;
      this.label86.Location = new Point(6, 48);
      this.label86.Name = "label86";
      this.label86.Size = new Size(102, 13);
      this.label86.TabIndex = 6;
      this.label86.Text = "Max Pet Experience";
      this.tb_exp_a_pet_index.Location = new Point(152, 19);
      this.tb_exp_a_pet_index.Name = "tb_exp_a_pet_index";
      this.tb_exp_a_pet_index.Size = new Size(39, 20);
      this.tb_exp_a_pet_index.TabIndex = 3;
      this.tb_exp_a_pet_index.KeyPress += new KeyPressEventHandler(this.tb_exp_a_pet_index_KeyPress);
      this.label88.AutoSize = true;
      this.label88.Location = new Point(6, 22);
      this.label88.Name = "label88";
      this.label88.Size = new Size(40, 13);
      this.label88.TabIndex = 0;
      this.label88.Text = "Pet ID:";
      this.tabPage5.Controls.Add((Control) this.button12);
      this.tabPage5.Controls.Add((Control) this.button9);
      this.tabPage5.Controls.Add((Control) this.button6);
      this.tabPage5.Controls.Add((Control) this.groupBox11);
      this.tabPage5.Controls.Add((Control) this.dgItems);
      this.tabPage5.Location = new Point(4, 22);
      this.tabPage5.Name = "tabPage5";
      this.tabPage5.Padding = new Padding(3);
      this.tabPage5.Size = new Size(620, 464);
      this.tabPage5.TabIndex = 4;
      this.tabPage5.Text = "PetExp Editor";
      this.tabPage5.UseVisualStyleBackColor = true;
      this.button12.BackColor = Color.LightCoral;
      this.button12.FlatStyle = FlatStyle.Flat;
      this.button12.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.delete;
      this.button12.ImageAlign = ContentAlignment.MiddleLeft;
      this.button12.Location = new Point(452, 407);
      this.button12.Name = "button12";
      this.button12.Size = new Size(77, 27);
      this.button12.TabIndex = 68;
      this.button12.Text = "    Delete";
      this.button12.UseVisualStyleBackColor = false;
      this.button12.Click += new EventHandler(this.button12_Click);
      this.button9.BackColor = Color.LightCyan;
      this.button9.FlatStyle = FlatStyle.Flat;
      this.button9.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources._08;
      this.button9.ImageAlign = ContentAlignment.MiddleLeft;
      this.button9.Location = new Point(362, 407);
      this.button9.Name = "button9";
      this.button9.Size = new Size(83, 27);
      this.button9.TabIndex = 67;
      this.button9.Text = "      Update";
      this.button9.UseVisualStyleBackColor = false;
      this.button9.Click += new EventHandler(this.button9_Click);
      this.button6.BackColor = Color.Plum;
      this.button6.FlatStyle = FlatStyle.Flat;
      this.button6.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.control_add_blue;
      this.button6.ImageAlign = ContentAlignment.MiddleLeft;
      this.button6.Location = new Point(279, 407);
      this.button6.Name = "button6";
      this.button6.Size = new Size(77, 27);
      this.button6.TabIndex = 66;
      this.button6.Text = "     Add";
      this.button6.UseVisualStyleBackColor = false;
      this.button6.Click += new EventHandler(this.button6_Click);
      this.groupBox11.Controls.Add((Control) this.textBox6);
      this.groupBox11.Controls.Add((Control) this.label93);
      this.groupBox11.Controls.Add((Control) this.label94);
      this.groupBox11.Controls.Add((Control) this.textBox7);
      this.groupBox11.Controls.Add((Control) this.textBox4);
      this.groupBox11.Controls.Add((Control) this.label91);
      this.groupBox11.Controls.Add((Control) this.label92);
      this.groupBox11.Controls.Add((Control) this.textBox5);
      this.groupBox11.Controls.Add((Control) this.textBox1);
      this.groupBox11.Controls.Add((Control) this.textBox3);
      this.groupBox11.Controls.Add((Control) this.label87);
      this.groupBox11.Controls.Add((Control) this.label90);
      this.groupBox11.Controls.Add((Control) this.label89);
      this.groupBox11.Controls.Add((Control) this.textBox2);
      this.groupBox11.Location = new Point(22, 276);
      this.groupBox11.Name = "groupBox11";
      this.groupBox11.Size = new Size(574, 121);
      this.groupBox11.TabIndex = 8;
      this.groupBox11.TabStop = false;
      this.groupBox11.Text = "Pet Exp Data";
      this.textBox6.Location = new Point(447, 83);
      this.textBox6.Name = "textBox6";
      this.textBox6.Size = new Size(64, 20);
      this.textBox6.TabIndex = 15;
      this.label93.AutoSize = true;
      this.label93.Location = new Point(361, 86);
      this.label93.Name = "label93";
      this.label93.Size = new Size(80, 13);
      this.label93.TabIndex = 14;
      this.label93.Text = "CoolTime Rate:";
      this.label94.AutoSize = true;
      this.label94.Location = new Point(197, 86);
      this.label94.Name = "label94";
      this.label94.Size = new Size(54, 13);
      this.label94.TabIndex = 12;
      this.label94.Text = "CoolTime:";
      this.textBox7.Location = new Point(257, 83);
      this.textBox7.Name = "textBox7";
      this.textBox7.Size = new Size(64, 20);
      this.textBox7.TabIndex = 13;
      this.textBox4.Location = new Point(447, 56);
      this.textBox4.Name = "textBox4";
      this.textBox4.Size = new Size(64, 20);
      this.textBox4.TabIndex = 11;
      this.label91.AutoSize = true;
      this.label91.Location = new Point(332, 59);
      this.label91.Name = "label91";
      this.label91.Size = new Size(109, 13);
      this.label91.TabIndex = 10;
      this.label91.Text = "Max Player Exp Rate:";
      this.label92.AutoSize = true;
      this.label92.Location = new Point(168, 59);
      this.label92.Name = "label92";
      this.label92.Size = new Size(83, 13);
      this.label92.TabIndex = 8;
      this.label92.Text = "Max Player Exp:";
      this.textBox5.Location = new Point(257, 56);
      this.textBox5.Name = "textBox5";
      this.textBox5.Size = new Size(64, 20);
      this.textBox5.TabIndex = 9;
      this.textBox1.Location = new Point(97, 30);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(64, 20);
      this.textBox1.TabIndex = 3;
      this.textBox3.Location = new Point(447, 30);
      this.textBox3.Name = "textBox3";
      this.textBox3.Size = new Size(64, 20);
      this.textBox3.TabIndex = 7;
      this.label87.AutoSize = true;
      this.label87.Location = new Point(51, 33);
      this.label87.Name = "label87";
      this.label87.Size = new Size(40, 13);
      this.label87.TabIndex = 2;
      this.label87.Text = "Pet ID:";
      this.label90.AutoSize = true;
      this.label90.Location = new Point(345, 33);
      this.label90.Name = "label90";
      this.label90.Size = new Size(96, 13);
      this.label90.TabIndex = 6;
      this.label90.Text = "Max Pet Exp Rate:";
      this.label89.AutoSize = true;
      this.label89.Location = new Point(181, 33);
      this.label89.Name = "label89";
      this.label89.Size = new Size(70, 13);
      this.label89.TabIndex = 4;
      this.label89.Text = "Max Pet Exp:";
      this.textBox2.Location = new Point(257, 30);
      this.textBox2.Name = "textBox2";
      this.textBox2.Size = new Size(64, 20);
      this.textBox2.TabIndex = 5;
      this.dgItems.AllowUserToAddRows = false;
      this.dgItems.AllowUserToDeleteRows = false;
      this.dgItems.BackgroundColor = SystemColors.Control;
      this.dgItems.BorderStyle = BorderStyle.None;
      this.dgItems.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dgItems.Columns.AddRange((DataGridViewColumn) this.a_pet_index, (DataGridViewColumn) this.a_max_acc_param1, (DataGridViewColumn) this.a_max_acc_param2, (DataGridViewColumn) this.a_acc_rate_param1, (DataGridViewColumn) this.a_acc_rate_param2, (DataGridViewColumn) this.a_cooltime, (DataGridViewColumn) this.a_cooltime_rate);
      this.dgItems.EnableHeadersVisualStyles = false;
      this.dgItems.Location = new Point(22, 16);
      this.dgItems.Name = "dgItems";
      this.dgItems.RowHeadersVisible = false;
      this.dgItems.RowTemplate.Height = 32;
      this.dgItems.ScrollBars = ScrollBars.Vertical;
      this.dgItems.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
      this.dgItems.Size = new Size(574, 254);
      this.dgItems.TabIndex = 1;
      this.dgItems.CellClick += new DataGridViewCellEventHandler(this.dgItems_CellClick);
      this.a_pet_index.HeaderText = "PetID";
      this.a_pet_index.Name = "a_pet_index";
      this.a_pet_index.Width = 60;
      this.a_max_acc_param1.HeaderText = "MaxPetExp";
      this.a_max_acc_param1.Name = "a_max_acc_param1";
      this.a_max_acc_param1.Width = 70;
      this.a_max_acc_param2.HeaderText = "MaxPlayerExp";
      this.a_max_acc_param2.Name = "a_max_acc_param2";
      this.a_acc_rate_param1.HeaderText = "PetExpRate";
      this.a_acc_rate_param1.Name = "a_acc_rate_param1";
      this.a_acc_rate_param1.Width = 70;
      this.a_acc_rate_param2.HeaderText = "PlayerExpRate";
      this.a_acc_rate_param2.Name = "a_acc_rate_param2";
      this.a_cooltime.HeaderText = "Cooltime";
      this.a_cooltime.Name = "a_cooltime";
      this.a_cooltime.Width = 70;
      this.a_cooltime_rate.HeaderText = "Cooltime_Rate";
      this.a_cooltime_rate.Name = "a_cooltime_rate";
      this.tabPage6.Controls.Add((Control) this.groupBox12);
      this.tabPage6.Controls.Add((Control) this.button4);
      this.tabPage6.Controls.Add((Control) this.button5);
      this.tabPage6.Controls.Add((Control) this.button7);
      this.tabPage6.Controls.Add((Control) this.dataGridView1);
      this.tabPage6.Location = new Point(4, 22);
      this.tabPage6.Name = "tabPage6";
      this.tabPage6.Padding = new Padding(3);
      this.tabPage6.Size = new Size(620, 464);
      this.tabPage6.TabIndex = 5;
      this.tabPage6.Text = "Pet Evo Editor";
      this.tabPage6.UseVisualStyleBackColor = true;
      this.groupBox12.Controls.Add((Control) this.textBox19);
      this.groupBox12.Controls.Add((Control) this.label102);
      this.groupBox12.Controls.Add((Control) this.textBox12);
      this.groupBox12.Controls.Add((Control) this.label95);
      this.groupBox12.Controls.Add((Control) this.label96);
      this.groupBox12.Controls.Add((Control) this.textBox13);
      this.groupBox12.Controls.Add((Control) this.textBox14);
      this.groupBox12.Controls.Add((Control) this.label97);
      this.groupBox12.Controls.Add((Control) this.label98);
      this.groupBox12.Controls.Add((Control) this.textBox15);
      this.groupBox12.Controls.Add((Control) this.textBox16);
      this.groupBox12.Controls.Add((Control) this.textBox17);
      this.groupBox12.Controls.Add((Control) this.label99);
      this.groupBox12.Controls.Add((Control) this.label100);
      this.groupBox12.Controls.Add((Control) this.label101);
      this.groupBox12.Controls.Add((Control) this.textBox18);
      this.groupBox12.Location = new Point(22, 276);
      this.groupBox12.Name = "groupBox12";
      this.groupBox12.Size = new Size(574, 121);
      this.groupBox12.TabIndex = 72;
      this.groupBox12.TabStop = false;
      this.groupBox12.Text = "Pet Exp Data";
      this.textBox19.Location = new Point(97, 60);
      this.textBox19.Name = "textBox19";
      this.textBox19.Size = new Size(64, 20);
      this.textBox19.TabIndex = 17;
      this.label102.AutoSize = true;
      this.label102.Location = new Point(32, 63);
      this.label102.Name = "label102";
      this.label102.Size = new Size(62, 13);
      this.label102.TabIndex = 16;
      this.label102.Text = "Pet Evo ID:";
      this.textBox12.Location = new Point(447, 83);
      this.textBox12.Name = "textBox12";
      this.textBox12.Size = new Size(64, 20);
      this.textBox12.TabIndex = 15;
      this.label95.AutoSize = true;
      this.label95.Location = new Point(405, 86);
      this.label95.Name = "label95";
      this.label95.Size = new Size(36, 13);
      this.label95.TabIndex = 14;
      this.label95.Text = "Order:";
      this.label96.AutoSize = true;
      this.label96.Location = new Point(215, 86);
      this.label96.Name = "label96";
      this.label96.Size = new Size(33, 13);
      this.label96.TabIndex = 12;
      this.label96.Text = "Faith:";
      this.textBox13.Location = new Point(257, 83);
      this.textBox13.Name = "textBox13";
      this.textBox13.Size = new Size(64, 20);
      this.textBox13.TabIndex = 13;
      this.textBox14.Location = new Point(447, 56);
      this.textBox14.Name = "textBox14";
      this.textBox14.Size = new Size(64, 20);
      this.textBox14.TabIndex = 11;
      this.label97.AutoSize = true;
      this.label97.Location = new Point(406, 59);
      this.label97.Name = "label97";
      this.label97.Size = new Size(35, 13);
      this.label97.TabIndex = 10;
      this.label97.Text = "Stat2:";
      this.label98.AutoSize = true;
      this.label98.Location = new Point(215, 59);
      this.label98.Name = "label98";
      this.label98.Size = new Size(35, 13);
      this.label98.TabIndex = 8;
      this.label98.Text = "Stat1:";
      this.textBox15.Location = new Point(257, 56);
      this.textBox15.Name = "textBox15";
      this.textBox15.Size = new Size(64, 20);
      this.textBox15.TabIndex = 9;
      this.textBox16.Location = new Point(97, 30);
      this.textBox16.Name = "textBox16";
      this.textBox16.Size = new Size(64, 20);
      this.textBox16.TabIndex = 3;
      this.textBox17.Location = new Point(447, 30);
      this.textBox17.Name = "textBox17";
      this.textBox17.Size = new Size(64, 20);
      this.textBox17.TabIndex = 7;
      this.label99.AutoSize = true;
      this.label99.Location = new Point(29, 33);
      this.label99.Name = "label99";
      this.label99.Size = new Size(65, 13);
      this.label99.TabIndex = 2;
      this.label99.Text = "Start Pet ID:";
      this.label100.AutoSize = true;
      this.label100.Location = new Point(393, 30);
      this.label100.Name = "label100";
      this.label100.Size = new Size(48, 13);
      this.label100.TabIndex = 6;
      this.label100.Text = "Stemina:";
      this.label101.AutoSize = true;
      this.label101.Location = new Point(195, 33);
      this.label101.Name = "label101";
      this.label101.Size = new Size(55, 13);
      this.label101.TabIndex = 4;
      this.label101.Text = "Pet Level:";
      this.textBox18.Location = new Point(257, 30);
      this.textBox18.Name = "textBox18";
      this.textBox18.Size = new Size(64, 20);
      this.textBox18.TabIndex = 5;
      this.button4.BackColor = Color.LightCoral;
      this.button4.FlatStyle = FlatStyle.Flat;
      this.button4.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.delete;
      this.button4.ImageAlign = ContentAlignment.MiddleLeft;
      this.button4.Location = new Point(452, 407);
      this.button4.Name = "button4";
      this.button4.Size = new Size(77, 27);
      this.button4.TabIndex = 71;
      this.button4.Text = "    Delete";
      this.button4.UseVisualStyleBackColor = false;
      this.button4.Click += new EventHandler(this.button4_Click);
      this.button5.BackColor = Color.LightCyan;
      this.button5.FlatStyle = FlatStyle.Flat;
      this.button5.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources._08;
      this.button5.ImageAlign = ContentAlignment.MiddleLeft;
      this.button5.Location = new Point(362, 407);
      this.button5.Name = "button5";
      this.button5.Size = new Size(83, 27);
      this.button5.TabIndex = 70;
      this.button5.Text = "      Update";
      this.button5.UseVisualStyleBackColor = false;
      this.button5.Click += new EventHandler(this.button5_Click);
      this.button7.BackColor = Color.Plum;
      this.button7.FlatStyle = FlatStyle.Flat;
      this.button7.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources.control_add_blue;
      this.button7.ImageAlign = ContentAlignment.MiddleLeft;
      this.button7.Location = new Point(279, 407);
      this.button7.Name = "button7";
      this.button7.Size = new Size(77, 27);
      this.button7.TabIndex = 69;
      this.button7.Text = "     Add";
      this.button7.UseVisualStyleBackColor = false;
      this.button7.Click += new EventHandler(this.button7_Click);
      this.dataGridView1.AllowUserToAddRows = false;
      this.dataGridView1.AllowUserToDeleteRows = false;
      this.dataGridView1.BackgroundColor = SystemColors.Control;
      this.dataGridView1.BorderStyle = BorderStyle.None;
      this.dataGridView1.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
      this.dataGridView1.Columns.AddRange((DataGridViewColumn) this.a_pet_index_evo, (DataGridViewColumn) this.a_ev_pet_index, (DataGridViewColumn) this.a_level, (DataGridViewColumn) this.a_stemina, (DataGridViewColumn) this.a_faith, (DataGridViewColumn) this.a_stat1, (DataGridViewColumn) this.a_stat2, (DataGridViewColumn) this.a_order);
      this.dataGridView1.EnableHeadersVisualStyles = false;
      this.dataGridView1.Location = new Point(22, 16);
      this.dataGridView1.Name = "dataGridView1";
      this.dataGridView1.RowHeadersVisible = false;
      this.dataGridView1.RowTemplate.Height = 32;
      this.dataGridView1.ScrollBars = ScrollBars.Vertical;
      this.dataGridView1.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
      this.dataGridView1.Size = new Size(574, 254);
      this.dataGridView1.TabIndex = 2;
      this.dataGridView1.CellClick += new DataGridViewCellEventHandler(this.dataGridView1_CellClick);
      this.a_pet_index_evo.HeaderText = "PetID";
      this.a_pet_index_evo.Name = "a_pet_index_evo";
      this.a_pet_index_evo.Width = 60;
      this.a_ev_pet_index.HeaderText = "PetEvoID";
      this.a_ev_pet_index.Name = "a_ev_pet_index";
      this.a_ev_pet_index.Width = 70;
      this.a_level.HeaderText = "Level";
      this.a_level.Name = "a_level";
      this.a_level.Width = 60;
      this.a_stemina.HeaderText = "Stemina";
      this.a_stemina.Name = "a_stemina";
      this.a_stemina.Width = 70;
      this.a_faith.HeaderText = "Faith";
      this.a_faith.Name = "a_faith";
      this.a_faith.Width = 70;
      this.a_stat1.HeaderText = "Stat1";
      this.a_stat1.Name = "a_stat1";
      this.a_stat1.Width = 70;
      this.a_stat2.HeaderText = "Stat2";
      this.a_stat2.Name = "a_stat2";
      this.a_stat2.Width = 70;
      this.a_order.HeaderText = "Order";
      this.a_order.Name = "a_order";
      this.a_order.Width = 70;
      this.button3.BackColor = Color.LightCyan;
      this.button3.FlatStyle = FlatStyle.Flat;
      this.button3.Image = (Image) LcDevPack_TeamDamonA.Properties.Resources._08;
      this.button3.ImageAlign = ContentAlignment.MiddleLeft;
      this.button3.Location = new Point(762, 519);
      this.button3.Name = "button3";
      this.button3.Size = new Size(83, 27);
      this.button3.TabIndex = 67;
      this.button3.Text = "      Update";
      this.button3.UseVisualStyleBackColor = false;
      this.button3.Click += new EventHandler(this.button3_Click);
      this.timer1.Enabled = true;
      this.timer1.Interval = 1;
      this.timer1.Tick += new EventHandler(this.timer1_Tick);
      this.Status.AutoSize = true;
      this.Status.Location = new Point(398, 524);
      this.Status.Name = "Status";
      this.Status.Size = new Size(0, 13);
      this.Status.TabIndex = 5;
      this.label71.AutoSize = true;
      this.label71.Location = new Point(12, 524);
      this.label71.Name = "label71";
      this.label71.Size = new Size(63, 13);
      this.label71.TabIndex = 41;
      this.label71.Text = "Pet Count : ";
      this.textBox8.Location = new Point(437, 1);
      this.textBox8.Name = "textBox8";
      this.textBox8.Size = new Size(31, 20);
      this.textBox8.TabIndex = 42;
      this.textBox8.Visible = false;
      this.textBox9.Location = new Point(474, 1);
      this.textBox9.Name = "textBox9";
      this.textBox9.Size = new Size(29, 20);
      this.textBox9.TabIndex = 43;
      this.textBox9.Visible = false;
      this.textBox10.Location = new Point(509, 1);
      this.textBox10.Name = "textBox10";
      this.textBox10.Size = new Size(29, 20);
      this.textBox10.TabIndex = 44;
      this.textBox10.Visible = false;
      this.textBox11.Location = new Point(544, 1);
      this.textBox11.Name = "textBox11";
      this.textBox11.Size = new Size(29, 20);
      this.textBox11.TabIndex = 45;
      this.textBox11.Visible = false;
      this.bigpetlodToolStripMenuItem.Name = "bigpetlodToolStripMenuItem";
      this.bigpetlodToolStripMenuItem.Size = new Size(182, 22);
      this.bigpetlodToolStripMenuItem.Text = "Save";
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(855, 550);
      this.Controls.Add((Control) this.textBox11);
      this.Controls.Add((Control) this.textBox10);
      this.Controls.Add((Control) this.textBox9);
      this.Controls.Add((Control) this.textBox8);
      this.Controls.Add((Control) this.label71);
      this.Controls.Add((Control) this.Status);
      this.Controls.Add((Control) this.tabControl1);
      this.Controls.Add((Control) this.groupBox2);
      this.Controls.Add((Control) this.groupBox1);
      this.Controls.Add((Control) this.menuStrip1);
      this.Controls.Add((Control) this.button3);
      this.MainMenuStrip = this.menuStrip1;
      this.Name = nameof (BigPetEditorr);
      this.Text = "Big Pet Editor";
      this.Load += new EventHandler(this.BitPetEditor_Load);
      this.menuStrip1.ResumeLayout(false);
      this.menuStrip1.PerformLayout();
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.groupBox2.ResumeLayout(false);
      this.tabControl1.ResumeLayout(false);
      this.tabPage1.ResumeLayout(false);
      this.tabPage1.PerformLayout();
      ((ISupportInitialize) this.PbSelectID1).EndInit();
      ((ISupportInitialize) this.pictureBox1).EndInit();
      this.groupBox20.ResumeLayout(false);
      this.groupBox20.PerformLayout();
      this.slideLeftRight.EndInit();
      this.slideUpDown.EndInit();
      this.slideZoom.EndInit();
      this.groupBox4.ResumeLayout(false);
      this.groupBox4.PerformLayout();
      this.groupBox3.ResumeLayout(false);
      this.groupBox3.PerformLayout();
      this.tabPage2.ResumeLayout(false);
      this.groupBox8.ResumeLayout(false);
      this.groupBox8.PerformLayout();
      this.groupBox7.ResumeLayout(false);
      this.groupBox7.PerformLayout();
      ((ISupportInitialize) this.pictureBox5).EndInit();
      this.groupBox6.ResumeLayout(false);
      this.groupBox6.PerformLayout();
      ((ISupportInitialize) this.pictureBox4).EndInit();
      this.groupBox5.ResumeLayout(false);
      this.groupBox5.PerformLayout();
      this.tabPage3.ResumeLayout(false);
      this.groupBox9.ResumeLayout(false);
      this.groupBox9.PerformLayout();
      this.tabPage4.ResumeLayout(false);
      this.groupBox10.ResumeLayout(false);
      this.groupBox10.PerformLayout();
      this.tabPage5.ResumeLayout(false);
      this.groupBox11.ResumeLayout(false);
      this.groupBox11.PerformLayout();
      ((ISupportInitialize) this.dgItems).EndInit();
      this.tabPage6.ResumeLayout(false);
      this.groupBox12.ResumeLayout(false);
      this.groupBox12.PerformLayout();
      ((ISupportInitialize) this.dataGridView1).EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();
    }

    private void BtnReadSmc_Click(object sender, EventArgs e)
    {
      string str = Path.GetDirectoryName(this._ClientPath).Replace("Data", "").Replace("data", "") + "\\" + this.tbSmc1_1.Text;
      if (File.Exists(str))
        new TextEditor(str).Show();
      else
        new CustomMessage("File not found").Show();
    }

    private void BtnReadSmc2_Click(object sender, EventArgs e)
    {
      string str = Path.GetDirectoryName(this._ClientPath).Replace("Data", "").Replace("data", "") + "\\" + this.tbSmc1_2.Text;
      if (File.Exists(str))
        new TextEditor(str).Show();
      else
        new CustomMessage("File not found").Show();
    }

    private void timer1_Tick(object sender, EventArgs e) => this.Render();

    private void PbSelectID1_Click(object sender, EventArgs e)
    {
      ItemPicker itemPicker = new ItemPicker();
      if (itemPicker.ShowDialog() != DialogResult.OK)
        return;
      this.tbItemIndex.Text = Convert.ToString(itemPicker.ItemIndex);
    }

    private void saveToolStripMenuItem_Click(object sender, EventArgs e)
    {
      new LodExporter.LodExporter().Show();
    }

    private void tbItemIndex_TextChanged(object sender, EventArgs e) => this.IconPet();

    private void btnAdd_Click(object sender, EventArgs e)
    {
      int num = AllLists.tpet_MenuData.Max<t_attkpet>((System.Func<t_attkpet, int>) (p => p.index)) + 1;
      t_attkpet tAttkpet = new t_attkpet();
      tAttkpet.index = num;
      tAttkpet.name = "New Pet";
      tAttkpet.smcFileName1 = "";
      tAttkpet.aniIdle1 = "";
      tAttkpet.aniIdle1_2 = "";
      tAttkpet.aniAttack1 = "";
      tAttkpet.aniAttack1_2 = "";
      tAttkpet.aniDamage1 = "";
      tAttkpet.aniDie1 = "";
      tAttkpet.aniWalk1 = "";
      tAttkpet.aniRun1 = "";
      tAttkpet.aniLevelup1 = "";
      tAttkpet.smcFileName2 = "";
      tAttkpet.aniIdle2 = "";
      tAttkpet.aniIdle2_2 = "";
      tAttkpet.aniAttack2 = "";
      tAttkpet.aniAttack2_2 = "";
      tAttkpet.aniDamage1_2 = "";
      tAttkpet.aniDie1_2 = "";
      tAttkpet.aniWalk1_2 = "";
      tAttkpet.aniRun1_2 = "";
      tAttkpet.aniLevelup1_2 = "";
      tAttkpet.enable = 1;
      this.tbItemExist.Text = "";
      AllLists.tpet_MenuData.Add(tAttkpet);
      AllLists.tpet_Menu.Add(tAttkpet.index.ToString() + " - " + tAttkpet.name);
      this.RefreshAll();
      this.listBox1.SelectedIndex = this.listBox1.Items.Count - 1;
    }

    private void btnDelete_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Are u sure u want to delete this entire pet?\r\nThe action cannot be undone", "Delete Pets", MessageBoxButtons.YesNo) != DialogResult.Yes)
        return;
      int PetID = this.GetID();
      AllLists.tpet_MenuData.RemoveAll((Predicate<t_attkpet>) (p => p.index.Equals(PetID)));
      mySQL.UpdateQuery("DELETE FROM t_attack_pet WHERE a_index ='" + PetID.ToString() + "';");
      int num = (int) new CustomMessage("Deleted :o").ShowDialog();
      this.RefreshAll();
    }

    private void btnCopy_Click(object sender, EventArgs e)
    {
      int PetID = this.GetID();
      int num = AllLists.tpet_MenuData.Max<t_attkpet>((System.Func<t_attkpet, int>) (p => p.index)) + 1;
      t_attkpet tAttkpet = AllLists.tpet_MenuData.Find((Predicate<t_attkpet>) (p => p.index.Equals(PetID))).Clone();
      tAttkpet.index = num;
      tAttkpet.name += " (copy)";
      tAttkpet.Menu = tAttkpet.index.ToString() + " - " + tAttkpet.name;
      this.tbItemExist.Text = "";
      AllLists.tpet_MenuData.Add(tAttkpet);
      this.RefreshAll();
      this.listBox1.SelectedIndex = this.listBox1.Items.Count - 1;
    }

    private void button3_Click(object sender, EventArgs e)
    {
      int ID = this.GetID();
      int index = AllLists.tpet_MenuData.FindIndex((Predicate<t_attkpet>) (p => p.index.Equals(ID)));
      if (index == -1)
        return;
      string menu = AllLists.tpet_MenuData[index].Menu;
      AllLists.tpet_MenuData[index].index = Convert.ToInt32(this.txtID.Text);
      AllLists.tpet_MenuData[index].enable = (int) Convert.ToInt16(this.tbEnable.Text);
      AllLists.tpet_MenuData[index].name = Convert.ToString(this.txtName.Text);
      AllLists.tpet_MenuData[index].type = Convert.ToInt32(this.tbType.Text);
      this.comboBox1.SelectedIndex = AllLists.tpet_MenuData[index].type;
      AllLists.tpet_MenuData[index].str = Convert.ToInt32(this.tbStrength.Text);
      AllLists.tpet_MenuData[index].con = Convert.ToInt32(this.tbConstitution.Text);
      AllLists.tpet_MenuData[index].dex = Convert.ToInt32(this.TbDexteriety.Text);
      AllLists.tpet_MenuData[index].intel = Convert.ToInt32(this.tbIntelligence.Text);
      AllLists.tpet_MenuData[index].itemidx = Convert.ToInt32(this.tbItemIndex.Text);
      AllLists.tpet_MenuData[index].maxFaith = Convert.ToInt32(this.tbmaxFaith.Text);
      AllLists.tpet_MenuData[index].maxStm = Convert.ToInt32(this.tbmaxStm.Text);
      AllLists.tpet_MenuData[index].maxHP = Convert.ToInt32(this.tbmaxHP.Text);
      AllLists.tpet_MenuData[index].maxMP = Convert.ToInt32(this.tbmaxMP.Text);
      AllLists.tpet_MenuData[index].recoverHP = Convert.ToInt32(this.tbRecoveryHP.Text);
      AllLists.tpet_MenuData[index].recoverMP = Convert.ToInt32(this.tbRecoveryMP.Text);
      AllLists.tpet_MenuData[index].delay = Convert.ToInt32(this.tbDelay.Text);
      AllLists.tpet_MenuData[index].AISlot = Convert.ToInt32(this.tbAiSlot.Text);
      AllLists.tpet_MenuData[index].afterDead = Convert.ToInt32(this.tbAfterDead.Text);
      AllLists.tpet_MenuData[index].attack = Convert.ToInt32(this.tbAttack.Text);
      AllLists.tpet_MenuData[index].defense = Convert.ToInt32(this.tbDefense.Text);
      AllLists.tpet_MenuData[index].mAttack = Convert.ToInt32(this.tbmAttack.Text);
      AllLists.tpet_MenuData[index].mDefense = Convert.ToInt32(this.tbmDefense.Text);
      AllLists.tpet_MenuData[index].hitPoint = Convert.ToInt32(this.TbHitpoint.Text);
      AllLists.tpet_MenuData[index].avoidPoint = Convert.ToInt32(this.tbAvoid.Text);
      AllLists.tpet_MenuData[index].mavoidPoint = Convert.ToInt32(this.tbMagicAvoid.Text);
      AllLists.tpet_MenuData[index].attackSpeed = Convert.ToInt32(this.tbAttackSpeed.Text);
      AllLists.tpet_MenuData[index].Deadly = Convert.ToInt32(this.tbDeadly.Text);
      AllLists.tpet_MenuData[index].Critical = Convert.ToInt32(this.tbCritical.Text);
      AllLists.tpet_MenuData[index].awful = Convert.ToInt32(this.tbAwful.Text);
      AllLists.tpet_MenuData[index].strong = Convert.ToInt32(this.tbStrong.Text);
      AllLists.tpet_MenuData[index].normal = Convert.ToInt32(this.tbNoraml.Text);
      AllLists.tpet_MenuData[index].weak = Convert.ToInt32(this.tbWeak.Text);
      AllLists.tpet_MenuData[index].bagicSkill1 = Convert.ToInt32(this.tbBasicSkill1.Text);
      AllLists.tpet_MenuData[index].bagicSkill2 = Convert.ToInt32(this.tbBasicSkill2.Text);
      AllLists.tpet_MenuData[index].flag = this.flag.SelectedIndex + 1;
      AllLists.tpet_MenuData[index].transType = Convert.ToInt32(this.tbTransType.Text);
      AllLists.tpet_MenuData[index].transStart = Convert.ToInt32(this.tbTransStart.Text);
      AllLists.tpet_MenuData[index].transEnd = Convert.ToInt32(this.tbTransEnd.Text);
      AllLists.tpet_MenuData[index].smcFileName1 = Convert.ToString(this.tbSmc1_1.Text);
      AllLists.tpet_MenuData[index].aniIdle1 = Convert.ToString(this.tbAniIdle1_1.Text);
      AllLists.tpet_MenuData[index].aniIdle1_2 = Convert.ToString(this.tbAniIdle2_1.Text);
      AllLists.tpet_MenuData[index].aniAttack1 = Convert.ToString(this.tbAniAttack1_1.Text);
      AllLists.tpet_MenuData[index].aniAttack1_2 = Convert.ToString(this.tbAniAttack2_1.Text);
      AllLists.tpet_MenuData[index].aniDamage1 = Convert.ToString(this.tbAniDamage1_1.Text);
      AllLists.tpet_MenuData[index].aniDie1 = Convert.ToString(this.tbAniDie1_1.Text);
      AllLists.tpet_MenuData[index].aniWalk1 = Convert.ToString(this.tbAniWalk1_1.Text);
      AllLists.tpet_MenuData[index].aniRun1 = Convert.ToString(this.tbAniRun1_1.Text);
      AllLists.tpet_MenuData[index].aniLevelup1 = Convert.ToString(this.tbLevelUp1_1.Text);
      AllLists.tpet_MenuData[index].mount1 = Convert.ToInt32(this.tbMount1_1.Text);
      AllLists.tpet_MenuData[index].summonSkill1 = Convert.ToInt32(this.tbSkillSummon1_1.Text);
      AllLists.tpet_MenuData[index].speed1 = Convert.ToInt32(this.tbSpeed1_1.Text);
      AllLists.tpet_MenuData[index].smcFileName2 = Convert.ToString(this.tbSmc1_2.Text);
      AllLists.tpet_MenuData[index].aniIdle2 = Convert.ToString(this.tbAniIdle1_2.Text);
      AllLists.tpet_MenuData[index].aniIdle2_2 = Convert.ToString(this.tbAniIdle2_2.Text);
      AllLists.tpet_MenuData[index].aniAttack2 = Convert.ToString(this.tbAniAttack1_2.Text);
      AllLists.tpet_MenuData[index].aniAttack2_2 = Convert.ToString(this.tbAniAttack2_2.Text);
      AllLists.tpet_MenuData[index].aniDamage1_2 = Convert.ToString(this.tbAniDamage1_2.Text);
      AllLists.tpet_MenuData[index].aniDie1_2 = Convert.ToString(this.tbAniDie1_2.Text);
      AllLists.tpet_MenuData[index].aniWalk1_2 = Convert.ToString(this.tbAniWalk1_2.Text);
      AllLists.tpet_MenuData[index].aniRun1_2 = Convert.ToString(this.tbAniRun1_2.Text);
      AllLists.tpet_MenuData[index].aniLevelup1_2 = Convert.ToString(this.tbLevelUp1_2.Text);
      AllLists.tpet_MenuData[index].mount1_2 = Convert.ToInt32(this.tbMount1_2.Text);
      AllLists.tpet_MenuData[index].summonSkill1_2 = Convert.ToInt32(this.tbSkillSummon1_2.Text);
      AllLists.tpet_MenuData[index].speed1_2 = Convert.ToInt32(this.tbSpeed1_2.Text);
      AllLists.tpet_MenuData[index].Menu = AllLists.tpet_MenuData[index].index.ToString() + " - " + AllLists.tpet_MenuData[index].name;
      this.listBox1.Items[this.listBox1.SelectedIndex] = (object) AllLists.tpet_MenuData[index].Menu;
      this.listBox1.SelectedItem = (object) AllLists.tpet_MenuData[index].Menu;
      this.doespetexist = false;
      this.IsPetInDB();
      if (this.doespetexist)
      {
        mySQL.UpdateQuery("UPDATE t_attack_pet SET a_index = '" + AllLists.tpet_MenuData[index].index.ToString() + "',a_enable ='" + AllLists.tpet_MenuData[index].enable.ToString() + "',a_type ='" + AllLists.tpet_MenuData[index].type.ToString() + "',a_name ='" + AllLists.tpet_MenuData[index].name + "',a_str = '" + AllLists.tpet_MenuData[index].str.ToString() + "',a_con ='" + AllLists.tpet_MenuData[index].con.ToString() + "',a_dex = '" + AllLists.tpet_MenuData[index].dex.ToString() + "',a_int = '" + AllLists.tpet_MenuData[index].intel.ToString() + "', a_item_idx = '" + AllLists.tpet_MenuData[index].itemidx.ToString() + "',a_maxFaith = '" + AllLists.tpet_MenuData[index].maxFaith.ToString() + "',a_maxStm = '" + AllLists.tpet_MenuData[index].maxStm.ToString() + "',a_maxHP = '" + AllLists.tpet_MenuData[index].maxHP.ToString() + "',a_maxMP = '" + AllLists.tpet_MenuData[index].maxMP.ToString() + "',a_recoverHP = '" + AllLists.tpet_MenuData[index].recoverHP.ToString() + "',a_recoverMP = '" + AllLists.tpet_MenuData[index].recoverMP.ToString() + "',a_delay = '" + AllLists.tpet_MenuData[index].delay.ToString() + "',a_AISlot = '" + AllLists.tpet_MenuData[index].AISlot.ToString() + "',a_after_dead = '" + AllLists.tpet_MenuData[index].afterDead.ToString() + "',a_attack = '" + AllLists.tpet_MenuData[index].attack.ToString() + "',a_defence = '" + AllLists.tpet_MenuData[index].defense.ToString() + "',a_Mattack = '" + AllLists.tpet_MenuData[index].mAttack.ToString() + "',a_Mdefence = '" + AllLists.tpet_MenuData[index].mDefense.ToString() + "',a_hitpoint = '" + AllLists.tpet_MenuData[index].hitPoint.ToString() + "',a_avoidpoint = '" + AllLists.tpet_MenuData[index].avoidPoint.ToString() + "',a_Mavoidpoint = '" + AllLists.tpet_MenuData[index].mavoidPoint.ToString() + "',a_attackSpeed = '" + AllLists.tpet_MenuData[index].attackSpeed.ToString() + "',a_deadly = '" + AllLists.tpet_MenuData[index].Deadly.ToString() + "',a_critical = '" + AllLists.tpet_MenuData[index].Critical.ToString() + "',a_awful = '" + AllLists.tpet_MenuData[index].awful.ToString() + "',a_strong = '" + AllLists.tpet_MenuData[index].strong.ToString() + "',a_normal = '" + AllLists.tpet_MenuData[index].normal.ToString() + "',a_week = '" + AllLists.tpet_MenuData[index].weak.ToString() + "',a_bagic_skill1 = '" + AllLists.tpet_MenuData[index].bagicSkill1.ToString() + "',a_bagic_skill2 = '" + AllLists.tpet_MenuData[index].bagicSkill2.ToString() + "',a_flag = '" + AllLists.tpet_MenuData[index].flag.ToString() + "',a_trans_type = '" + AllLists.tpet_MenuData[index].transType.ToString() + "',a_trans_start = '" + AllLists.tpet_MenuData[index].transStart.ToString() + "',a_trans_end = '" + AllLists.tpet_MenuData[index].transEnd.ToString() + "',a_smcFileName_1 = '" + AllLists.tpet_MenuData[index].smcFileName1.Replace("\\", "\\\\").Replace("'", "\\'") + "',a_ani_idle1_1 = '" + AllLists.tpet_MenuData[index].aniIdle1 + "',a_ani_idle2_1 = '" + AllLists.tpet_MenuData[index].aniIdle1_2 + "',a_ani_attack1_1 = '" + AllLists.tpet_MenuData[index].aniAttack1 + "',a_ani_attack2_1 = '" + AllLists.tpet_MenuData[index].aniAttack1_2 + "',a_ani_damage_1 = '" + AllLists.tpet_MenuData[index].aniDamage1 + "',a_ani_die_1 = '" + AllLists.tpet_MenuData[index].aniDie1 + "',a_ani_walk_1 = '" + AllLists.tpet_MenuData[index].aniWalk1 + "',a_ani_run_1 = '" + AllLists.tpet_MenuData[index].aniRun1 + "',a_ani_levelup_1 = '" + AllLists.tpet_MenuData[index].aniLevelup1 + "',a_mount_1 = '" + AllLists.tpet_MenuData[index].mount1.ToString() + "',a_summon_skill_1 = '" + AllLists.tpet_MenuData[index].summonSkill1.ToString() + "',a_speed_1 = '" + AllLists.tpet_MenuData[index].speed1.ToString() + "',a_smcFileName_2 = '" + AllLists.tpet_MenuData[index].smcFileName2.Replace("\\", "\\\\").Replace("'", "\\'") + "',a_ani_idle1_2 = '" + AllLists.tpet_MenuData[index].aniIdle2 + "',a_ani_idle2_2 = '" + AllLists.tpet_MenuData[index].aniIdle2_2 + "',a_ani_attack1_2 = '" + AllLists.tpet_MenuData[index].aniAttack2 + "',a_ani_attack2_2 = '" + AllLists.tpet_MenuData[index].aniAttack2_2 + "',a_ani_damage_2 = '" + AllLists.tpet_MenuData[index].aniDamage1_2 + "',a_ani_die_2 = '" + AllLists.tpet_MenuData[index].aniDie1_2 + "',a_ani_walk_2 = '" + AllLists.tpet_MenuData[index].aniWalk1_2 + "',a_ani_run_2 = '" + AllLists.tpet_MenuData[index].aniRun1_2 + "',a_ani_levelup_2 = '" + AllLists.tpet_MenuData[index].aniLevelup1_2 + "',a_mount_2 = '" + AllLists.tpet_MenuData[index].mount1_2.ToString() + "',a_summon_skill_2 = '" + AllLists.tpet_MenuData[index].summonSkill1_2.ToString() + "',a_speed_2 = '" + AllLists.tpet_MenuData[index].speed1_2.ToString() + "'WHERE a_index ='" + AllLists.tpet_MenuData[index].index.ToString() + "';");
        this.Status.Text = "Saved Pet : " + AllLists.tpet_MenuData[index].Menu;
        int num = (int) new CustomMessage("Updated Pet").ShowDialog();
      }
      else
      {
        if (this.doespetexist)
          return;
        mySQL.UpdateQuery("INSERT INTO t_attack_pet ( a_index, a_enable, a_type, a_name, a_str, a_con, a_dex, a_int, a_item_idx, a_maxFaith, a_maxStm, a_maxHP, a_maxMP, a_recoverHP, a_recoverMP, a_delay, a_AISlot, a_after_dead, a_attack, a_defence, a_Mattack, a_Mdefence, a_hitpoint, a_avoidpoint, a_Mavoidpoint, a_attackSpeed, a_deadly , a_critical, a_awful , a_strong, a_normal , a_week, a_bagic_skill1 , a_bagic_skill2, a_flag, a_trans_type, a_trans_start, a_trans_end, a_smcFileName_1, a_ani_idle1_1 , a_ani_idle2_1, a_ani_attack1_1, a_ani_attack2_1, a_ani_damage_1, a_ani_die_1, a_ani_walk_1, a_ani_run_1, a_ani_levelup_1, a_mount_1, a_summon_skill_1, a_speed_1, a_smcFileName_2, a_ani_idle1_2, a_ani_idle2_2, a_ani_attack1_2, a_ani_attack2_2, a_ani_damage_2, a_ani_die_2, a_ani_walk_2, a_ani_run_2, a_ani_levelup_2, a_mount_2, a_summon_skill_2, a_speed_2) VALUES (" + AllLists.tpet_MenuData[index].index.ToString() + "," + AllLists.tpet_MenuData[index].enable.ToString() + "," + AllLists.tpet_MenuData[index].type.ToString() + ",'" + AllLists.tpet_MenuData[index].name + "'," + AllLists.tpet_MenuData[index].str.ToString() + "," + AllLists.tpet_MenuData[index].con.ToString() + "," + AllLists.tpet_MenuData[index].dex.ToString() + "," + AllLists.tpet_MenuData[index].intel.ToString() + "," + AllLists.tpet_MenuData[index].itemidx.ToString() + "," + AllLists.tpet_MenuData[index].maxFaith.ToString() + "," + AllLists.tpet_MenuData[index].maxStm.ToString() + "," + AllLists.tpet_MenuData[index].maxHP.ToString() + "," + AllLists.tpet_MenuData[index].maxMP.ToString() + "," + AllLists.tpet_MenuData[index].recoverHP.ToString() + "," + AllLists.tpet_MenuData[index].recoverMP.ToString() + "," + AllLists.tpet_MenuData[index].delay.ToString() + "," + AllLists.tpet_MenuData[index].AISlot.ToString() + "," + AllLists.tpet_MenuData[index].afterDead.ToString() + "," + AllLists.tpet_MenuData[index].attack.ToString() + "," + AllLists.tpet_MenuData[index].defense.ToString() + "," + AllLists.tpet_MenuData[index].mAttack.ToString() + "," + AllLists.tpet_MenuData[index].mDefense.ToString() + "," + AllLists.tpet_MenuData[index].hitPoint.ToString() + "," + AllLists.tpet_MenuData[index].avoidPoint.ToString() + "," + AllLists.tpet_MenuData[index].mavoidPoint.ToString() + "," + AllLists.tpet_MenuData[index].attackSpeed.ToString() + "," + AllLists.tpet_MenuData[index].Deadly.ToString() + "," + AllLists.tpet_MenuData[index].Critical.ToString() + "," + AllLists.tpet_MenuData[index].awful.ToString() + "," + AllLists.tpet_MenuData[index].strong.ToString() + "," + AllLists.tpet_MenuData[index].normal.ToString() + "," + AllLists.tpet_MenuData[index].weak.ToString() + "," + AllLists.tpet_MenuData[index].bagicSkill1.ToString() + "," + AllLists.tpet_MenuData[index].bagicSkill2.ToString() + "," + AllLists.tpet_MenuData[index].flag.ToString() + "," + AllLists.tpet_MenuData[index].transType.ToString() + "," + AllLists.tpet_MenuData[index].transStart.ToString() + "," + AllLists.tpet_MenuData[index].transEnd.ToString() + ",'" + AllLists.tpet_MenuData[index].smcFileName1.Replace("\\", "\\\\").Replace("'", "\\'") + "','" + AllLists.tpet_MenuData[index].aniIdle1 + "','" + AllLists.tpet_MenuData[index].aniIdle1_2 + "','" + AllLists.tpet_MenuData[index].aniAttack1 + "','" + AllLists.tpet_MenuData[index].aniAttack1_2 + "','" + AllLists.tpet_MenuData[index].aniDamage1 + "','" + AllLists.tpet_MenuData[index].aniDie1 + "','" + AllLists.tpet_MenuData[index].aniWalk1 + "','" + AllLists.tpet_MenuData[index].aniRun1 + "','" + AllLists.tpet_MenuData[index].aniLevelup1 + "'," + AllLists.tpet_MenuData[index].mount1.ToString() + "," + AllLists.tpet_MenuData[index].summonSkill1.ToString() + "," + AllLists.tpet_MenuData[index].speed1.ToString() + ",'" + AllLists.tpet_MenuData[index].smcFileName2.Replace("\\", "\\\\").Replace("'", "\\'") + "','" + AllLists.tpet_MenuData[index].aniIdle2 + "','" + AllLists.tpet_MenuData[index].aniIdle2_2 + "','" + AllLists.tpet_MenuData[index].aniAttack2 + "','" + AllLists.tpet_MenuData[index].aniAttack2_2 + "','" + AllLists.tpet_MenuData[index].aniDamage1_2 + "','" + AllLists.tpet_MenuData[index].aniDie1_2 + "','" + AllLists.tpet_MenuData[index].aniWalk1_2 + "','" + AllLists.tpet_MenuData[index].aniRun1_2 + "','" + AllLists.tpet_MenuData[index].aniLevelup1_2 + "'," + AllLists.tpet_MenuData[index].mount1_2.ToString() + "," + AllLists.tpet_MenuData[index].summonSkill1_2.ToString() + "," + AllLists.tpet_MenuData[index].speed1_2.ToString() + " );");
        this.Status.Text = "Inserted Pet : " + AllLists.tpet_MenuData[index].Menu;
        int num = (int) new CustomMessage("Inserted Pet").ShowDialog();
      }
    }

    private void tbType_TextChanged(object sender, EventArgs e) => this.comboBox1.Select();

    private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
    }

    private void button1_Click(object sender, EventArgs e)
    {
      SkillPicker skillPicker = new SkillPicker();
      if (skillPicker.ShowDialog() != DialogResult.OK)
        return;
      this.tbSkillSummon1_1.Text = skillPicker.SkillIndex.ToString();
    }

    private void button2_Click(object sender, EventArgs e)
    {
      SkillPicker skillPicker = new SkillPicker();
      if (skillPicker.ShowDialog() != DialogResult.OK)
        return;
      this.tbSkillSummon1_2.Text = skillPicker.SkillIndex.ToString();
    }

    private void IsPetInDB()
    {
      foreach (DataRow row in (InternalDataCollectionBase) mySQL.GetFromQuery("select a_index FROM t_attack_pet WHERE a_index ='" + this.txtID.Text + "';").Rows)
      {
        this.tbItemExist.Text = Convert.ToString(row["a_index"]);
        if (this.tbItemExist.Text != null || this.tbItemExist.Text != "")
        {
          this.doespetexist = true;
        }
        else
        {
          this.tbItemExist.Text = "";
          this.doespetexist = false;
        }
      }
    }

    private void ResetTbBackGround()
    {
      this.txtID.BackColor = Color.White;
      this.txtName.BackColor = Color.White;
      this.comboBox1.BackColor = Color.White;
      this.flag.BackColor = Color.White;
      this.tbItemIndex.BackColor = Color.White;
      this.tbStrength.BackColor = Color.White;
      this.TbDexteriety.BackColor = Color.White;
      this.tbIntelligence.BackColor = Color.White;
      this.tbConstitution.BackColor = Color.White;
      this.tbmaxHP.BackColor = Color.White;
      this.tbmaxMP.BackColor = Color.White;
      this.tbmaxFaith.BackColor = Color.White;
      this.tbmaxStm.BackColor = Color.White;
      this.tbRecoveryHP.BackColor = Color.White;
      this.tbRecoveryMP.BackColor = Color.White;
      this.tbAiSlot.BackColor = Color.White;
      this.tbDelay.BackColor = Color.White;
      this.tbAfterDead.BackColor = Color.White;
      this.TbHitpoint.BackColor = Color.White;
      this.tbAvoid.BackColor = Color.White;
      this.tbMagicAvoid.BackColor = Color.White;
      this.tbAttackSpeed.BackColor = Color.White;
      this.tbAttack.BackColor = Color.White;
      this.tbDefense.BackColor = Color.White;
      this.tbmAttack.BackColor = Color.White;
      this.tbmDefense.BackColor = Color.White;
      this.tbDeadly.BackColor = Color.White;
      this.tbWeak.BackColor = Color.White;
      this.tbFlag.BackColor = Color.White;
      this.tbCritical.BackColor = Color.White;
      this.tbStrong.BackColor = Color.White;
      this.tbBasicSkill1.BackColor = Color.White;
      this.tbBasicSkill2.BackColor = Color.White;
      this.tbAwful.BackColor = Color.White;
      this.tbNoraml.BackColor = Color.White;
      this.tbAniIdle1_1.BackColor = Color.White;
      this.tbAniIdle2_1.BackColor = Color.White;
      this.tbAniAttack1_1.BackColor = Color.White;
      this.tbAniAttack2_1.BackColor = Color.White;
      this.tbAniDie1_1.BackColor = Color.White;
      this.tbAniWalk1_1.BackColor = Color.White;
      this.tbAniRun1_1.BackColor = Color.White;
      this.tbAniDamage1_1.BackColor = Color.White;
      this.tbLevelUp1_1.BackColor = Color.White;
      this.tbSkillSummon1_1.BackColor = Color.White;
      this.tbSpeed1_1.BackColor = Color.White;
      this.tbMount1_1.BackColor = Color.White;
      this.tbSmc1_1.BackColor = Color.White;
      this.tbAniIdle1_2.BackColor = Color.White;
      this.tbAniIdle2_2.BackColor = Color.White;
      this.tbAniAttack1_2.BackColor = Color.White;
      this.tbAniAttack2_2.BackColor = Color.White;
      this.tbAniDie1_2.BackColor = Color.White;
      this.tbAniWalk1_2.BackColor = Color.White;
      this.tbAniRun1_2.BackColor = Color.White;
      this.tbAniDamage1_2.BackColor = Color.White;
      this.tbLevelUp1_2.BackColor = Color.White;
      this.tbSkillSummon1_2.BackColor = Color.White;
      this.tbSpeed1_2.BackColor = Color.White;
      this.tbMount1_2.BackColor = Color.White;
      this.tbSmc1_2.BackColor = Color.White;
      this.tbTransType.BackColor = Color.White;
      this.tbTransStart.BackColor = Color.White;
      this.tbTransEnd.BackColor = Color.White;
      this.tb_ev_ID.BackColor = Color.White;
      this.tb_to_ev_id.BackColor = Color.White;
      this.tb_ev_Level.BackColor = Color.White;
      this.tb_ev_ID.BackColor = Color.White;
      this.tb_ev_Stemina.BackColor = Color.White;
      this.tb_ev_Faith.BackColor = Color.White;
      this.tb_ev_stat1.BackColor = Color.White;
      this.tb_ev_stat2.BackColor = Color.White;
      this.tb_ev_order.BackColor = Color.White;
      this.tb_exp_a_pet_index.BackColor = Color.White;
      this.tb_exp_a_max_acc_param1.BackColor = Color.White;
      this.tb_exp_a_max_acc_param2.BackColor = Color.White;
      this.tb_exp_a_acc_rate_param1.BackColor = Color.White;
      this.tb_exp_a_acc_rate_param2.BackColor = Color.White;
    }

    private void IconSkill()
    {
      foreach (DataRow row in (InternalDataCollectionBase) mySQL.GetFromQuery("select a_index, a_client_icon_texid, a_client_icon_row, a_client_icon_col FROM t_skill WHERE a_index ='" + this.tbSkillSummon1_1.Text + "';").Rows)
      {
        this.t_tex1.Text = Convert.ToString(row["a_client_icon_texid"]);
        this.t_row1.Text = Convert.ToString(row["a_client_icon_row"]);
        this.t_col1.Text = Convert.ToString(row["a_client_icon_col"]);
      }
    }

    private void IconSkill2()
    {
      foreach (DataRow row in (InternalDataCollectionBase) mySQL.GetFromQuery("select a_index, a_client_icon_texid, a_client_icon_row, a_client_icon_col FROM t_skill WHERE a_index ='" + this.tbSkillSummon1_2.Text + "';").Rows)
      {
        this.t_tex2.Text = Convert.ToString(row["a_client_icon_texid"]);
        this.t_row2.Text = Convert.ToString(row["a_client_icon_row"]);
        this.t_col2.Text = Convert.ToString(row["a_client_icon_col"]);
      }
    }

    private void tbSkillSummon1_1_TextChanged(object sender, EventArgs e)
    {
    }

    private void pictureBox4_Click(object sender, EventArgs e)
    {
      OpenFileDialog openFileDialog = new OpenFileDialog();
      openFileDialog.Title = "Select : *.smc";
      openFileDialog.InitialDirectory = this._ClientPath;
      openFileDialog.Filter = "SMC File|*.smc|All|*.*";
      if (openFileDialog.ShowDialog() == DialogResult.Cancel)
        return;
      openFileDialog.FileName = openFileDialog.FileName.Substring(openFileDialog.FileName.IndexOf("Data"));
      this.tbSmc1_1.Text = openFileDialog.FileName;
      this.tbSmc1_1.BackColor = Color.PaleTurquoise;
    }

    private void pictureBox5_Click(object sender, EventArgs e)
    {
      OpenFileDialog openFileDialog = new OpenFileDialog();
      openFileDialog.Title = "Select : *.smc";
      openFileDialog.InitialDirectory = this._ClientPath;
      openFileDialog.Filter = "SMC File|*.smc|All|*.*";
      if (openFileDialog.ShowDialog() == DialogResult.Cancel)
        return;
      openFileDialog.FileName = openFileDialog.FileName.Substring(openFileDialog.FileName.IndexOf("Data"));
      this.tbSmc1_2.Text = openFileDialog.FileName;
      this.tbSmc1_2.BackColor = Color.PaleTurquoise;
    }

    private void tbSkillSummon1_2_TextChanged(object sender, EventArgs e)
    {
    }

    private void checkBox1_CheckedChanged(object sender, EventArgs e)
    {
      if (this.checkBox1.Checked)
      {
        this.checkBox1.BackColor = Color.LimeGreen;
        this.checkBox1.Text = "Enable";
        this.tbEnable.Text = "1";
      }
      else
      {
        if (this.cbMount1.Checked)
          return;
        this.checkBox1.BackColor = Color.Red;
        this.tbEnable.Text = "0";
        this.checkBox1.Text = "disable";
      }
    }

    private void cbMount1_CheckedChanged(object sender, EventArgs e)
    {
      if (this.cbMount1.Checked)
      {
        this.cbMount1.BackColor = Color.LimeGreen;
        this.cbMount1.Text = "Mount";
        this.tbMount1_1.Text = "1";
      }
      else
      {
        if (this.cbMount1.Checked)
          return;
        this.cbMount1.BackColor = Color.Red;
        this.tbMount1_1.Text = "0";
        this.cbMount1.Text = "NotMount";
      }
    }

    private void cbMount2_CheckedChanged(object sender, EventArgs e)
    {
      if (this.cbMount2.Checked)
      {
        this.cbMount2.BackColor = Color.LimeGreen;
        this.cbMount2.Text = "Mount";
        this.tbMount1_2.Text = "1";
      }
      else
      {
        if (this.cbMount2.Checked)
          return;
        this.cbMount2.BackColor = Color.Red;
        this.tbMount1_2.Text = "0";
        this.cbMount2.Text = "NotMount";
      }
    }

    private void bigpetlodToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if (this.listBox1.Items.Count == 0)
        return;
      SaveFileDialog saveFileDialog = new SaveFileDialog();
      saveFileDialog.Filter = "bigpet.lod|bigpet*.lod|data|*.data|All|*.*";
      saveFileDialog.Title = "Save bigpet.lod";
      int num1 = (int) saveFileDialog.ShowDialog();
      if (!(saveFileDialog.FileName != ""))
        return;
      try
      {
        BinaryWriter binaryWriter = new BinaryWriter((Stream) new FileStream(saveFileDialog.FileName, FileMode.Create));
        binaryWriter.Write(AllLists.tpet_MenuData.Count);
        for (int index1 = 0; index1 <= AllLists.tpet_MenuData.Count<t_attkpet>() - 1; ++index1)
        {
          binaryWriter.Write(AllLists.tpet_MenuData[index1].index);
          string name = AllLists.tpet_MenuData[index1].name;
          byte[] buffer1 = new byte[20];
          int length1 = name.Length > 20 ? 20 : name.Length;
          Encoding.UTF8.GetBytes(name.Substring(0, length1)).CopyTo((Array) buffer1, 0);
          binaryWriter.Write(buffer1);
          binaryWriter.Write(AllLists.tpet_MenuData[index1].type);
          binaryWriter.Write(AllLists.tpet_MenuData[index1].itemidx);
          binaryWriter.Write(AllLists.tpet_MenuData[index1].AISlot);
          binaryWriter.Write(AllLists.tpet_MenuData[index1].mount1);
          binaryWriter.Write(AllLists.tpet_MenuData[index1].mount1_2);
          binaryWriter.Write(AllLists.tpet_MenuData[index1].summonSkill1);
          binaryWriter.Write(AllLists.tpet_MenuData[index1].summonSkill1_2);
          binaryWriter.Write(AllLists.tpet_MenuData[index1].flag);
          string smcFileName1 = AllLists.tpet_MenuData[index1].smcFileName1;
          byte[] buffer2 = new byte[64];
          int length2 = smcFileName1.Length > 64 ? 64 : smcFileName1.Length;
          Encoding.UTF8.GetBytes(smcFileName1.Substring(0, length2)).CopyTo((Array) buffer2, 0);
          binaryWriter.Write(buffer2);
          string smcFileName2 = AllLists.tpet_MenuData[index1].smcFileName2;
          byte[] buffer3 = new byte[64];
          int length3 = smcFileName2.Length > 64 ? 64 : smcFileName2.Length;
          Encoding.UTF8.GetBytes(smcFileName2.Substring(0, length3)).CopyTo((Array) buffer3, 0);
          binaryWriter.Write(buffer3);
          string aniIdle1 = AllLists.tpet_MenuData[index1].aniIdle1;
          byte[] buffer4 = new byte[32];
          int length4 = aniIdle1.Length > 32 ? 32 : aniIdle1.Length;
          Encoding.UTF8.GetBytes(aniIdle1.Substring(0, length4)).CopyTo((Array) buffer4, 0);
          binaryWriter.Write(buffer4);
          string aniIdle2 = AllLists.tpet_MenuData[index1].aniIdle2;
          byte[] buffer5 = new byte[32];
          int length5 = aniIdle2.Length > 32 ? 32 : aniIdle2.Length;
          Encoding.UTF8.GetBytes(aniIdle2.Substring(0, length5)).CopyTo((Array) buffer5, 0);
          binaryWriter.Write(buffer5);
          string aniIdle12 = AllLists.tpet_MenuData[index1].aniIdle1_2;
          byte[] buffer6 = new byte[32];
          int length6 = aniIdle12.Length > 32 ? 32 : aniIdle12.Length;
          Encoding.UTF8.GetBytes(aniIdle12.Substring(0, length6)).CopyTo((Array) buffer6, 0);
          binaryWriter.Write(buffer6);
          string aniIdle22 = AllLists.tpet_MenuData[index1].aniIdle2_2;
          byte[] buffer7 = new byte[32];
          int length7 = aniIdle22.Length > 32 ? 32 : aniIdle22.Length;
          Encoding.UTF8.GetBytes(aniIdle22.Substring(0, length7)).CopyTo((Array) buffer7, 0);
          binaryWriter.Write(buffer7);
          string aniAttack1 = AllLists.tpet_MenuData[index1].aniAttack1;
          byte[] buffer8 = new byte[32];
          int length8 = aniAttack1.Length > 32 ? 32 : aniAttack1.Length;
          Encoding.UTF8.GetBytes(aniAttack1.Substring(0, length8)).CopyTo((Array) buffer8, 0);
          binaryWriter.Write(buffer8);
          string aniAttack2 = AllLists.tpet_MenuData[index1].aniAttack2;
          byte[] buffer9 = new byte[32];
          int length9 = aniAttack2.Length > 32 ? 32 : aniAttack2.Length;
          Encoding.UTF8.GetBytes(aniAttack2.Substring(0, length9)).CopyTo((Array) buffer9, 0);
          binaryWriter.Write(buffer9);
          string aniAttack12 = AllLists.tpet_MenuData[index1].aniAttack1_2;
          byte[] buffer10 = new byte[32];
          int length10 = aniAttack12.Length > 32 ? 32 : aniAttack12.Length;
          Encoding.UTF8.GetBytes(aniAttack12.Substring(0, length10)).CopyTo((Array) buffer10, 0);
          binaryWriter.Write(buffer10);
          string aniAttack22 = AllLists.tpet_MenuData[index1].aniAttack2_2;
          byte[] buffer11 = new byte[32];
          int length11 = aniAttack22.Length > 32 ? 32 : aniAttack22.Length;
          Encoding.UTF8.GetBytes(aniAttack22.Substring(0, length11)).CopyTo((Array) buffer11, 0);
          binaryWriter.Write(buffer11);
          string aniDamage1 = AllLists.tpet_MenuData[index1].aniDamage1;
          byte[] buffer12 = new byte[32];
          int length12 = aniDamage1.Length > 32 ? 32 : aniDamage1.Length;
          Encoding.UTF8.GetBytes(aniDamage1.Substring(0, length12)).CopyTo((Array) buffer12, 0);
          binaryWriter.Write(buffer12);
          string aniDamage12 = AllLists.tpet_MenuData[index1].aniDamage1_2;
          byte[] buffer13 = new byte[32];
          int length13 = aniDamage12.Length > 32 ? 32 : aniDamage12.Length;
          Encoding.UTF8.GetBytes(aniDamage12.Substring(0, length13)).CopyTo((Array) buffer13, 0);
          binaryWriter.Write(buffer13);
          string aniDie1 = AllLists.tpet_MenuData[index1].aniDie1;
          byte[] buffer14 = new byte[32];
          int length14 = aniDie1.Length > 32 ? 32 : aniDie1.Length;
          Encoding.UTF8.GetBytes(aniDie1.Substring(0, length14)).CopyTo((Array) buffer14, 0);
          binaryWriter.Write(buffer14);
          string aniDie12 = AllLists.tpet_MenuData[index1].aniDie1_2;
          byte[] buffer15 = new byte[32];
          int length15 = aniDie12.Length > 32 ? 32 : aniDie12.Length;
          Encoding.UTF8.GetBytes(aniDie12.Substring(0, length15)).CopyTo((Array) buffer15, 0);
          binaryWriter.Write(buffer15);
          string aniWalk1 = AllLists.tpet_MenuData[index1].aniWalk1;
          byte[] buffer16 = new byte[32];
          int length16 = aniWalk1.Length > 32 ? 32 : aniWalk1.Length;
          Encoding.UTF8.GetBytes(aniWalk1.Substring(0, length16)).CopyTo((Array) buffer16, 0);
          binaryWriter.Write(buffer16);
          string aniWalk12 = AllLists.tpet_MenuData[index1].aniWalk1_2;
          byte[] buffer17 = new byte[32];
          int length17 = aniWalk12.Length > 32 ? 32 : aniWalk12.Length;
          Encoding.UTF8.GetBytes(aniWalk12.Substring(0, length17)).CopyTo((Array) buffer17, 0);
          binaryWriter.Write(buffer17);
          string aniRun1 = AllLists.tpet_MenuData[index1].aniRun1;
          byte[] buffer18 = new byte[32];
          int length18 = aniRun1.Length > 32 ? 32 : aniRun1.Length;
          Encoding.UTF8.GetBytes(aniRun1.Substring(0, length18)).CopyTo((Array) buffer18, 0);
          binaryWriter.Write(buffer18);
          string aniRun12 = AllLists.tpet_MenuData[index1].aniRun1_2;
          byte[] buffer19 = new byte[32];
          int length19 = aniRun12.Length > 32 ? 32 : aniRun12.Length;
          Encoding.UTF8.GetBytes(aniRun12.Substring(0, length19)).CopyTo((Array) buffer19, 0);
          binaryWriter.Write(buffer19);
          string aniLevelup1 = AllLists.tpet_MenuData[index1].aniLevelup1;
          byte[] buffer20 = new byte[32];
          int length20 = aniLevelup1.Length > 32 ? 32 : aniLevelup1.Length;
          Encoding.UTF8.GetBytes(aniLevelup1.Substring(0, length20)).CopyTo((Array) buffer20, 0);
          binaryWriter.Write(buffer20);
          string aniLevelup12 = AllLists.tpet_MenuData[index1].aniLevelup1_2;
          byte[] buffer21 = new byte[32];
          int length21 = aniLevelup12.Length > 32 ? 32 : aniLevelup12.Length;
          Encoding.UTF8.GetBytes(aniLevelup12.Substring(0, length21)).CopyTo((Array) buffer21, 0);
          binaryWriter.Write(buffer21);
          for (int index2 = 0; index2 <= AllLists.tpet_ev_MenuData.Count<BigpetEv>() - 1; ++index2)
          {
            if (AllLists.tpet_MenuData[index1].index == AllLists.tpet_ev_MenuData[index2].APetIdx)
            {
              binaryWriter.Write(AllLists.tpet_ev_MenuData[index2].Level);
              binaryWriter.Write(AllLists.tpet_ev_MenuData[index2].Stemina);
              binaryWriter.Write(AllLists.tpet_ev_MenuData[index2].Faith);
              binaryWriter.Write(AllLists.tpet_ev_MenuData[index2].a_ev_pet_index);
            }
          }
          for (int index3 = 0; index3 <= AllLists.tpet_exp_MenuData.Count<BigpetExp>() - 1; ++index3)
          {
            if (AllLists.tpet_MenuData[index1].index == AllLists.tpet_exp_MenuData[index3].a_pet_index)
            {
              binaryWriter.Write(AllLists.tpet_exp_MenuData[index3].a_max_acc_param1);
              binaryWriter.Write(AllLists.tpet_exp_MenuData[index3].a_max_acc_param2);
              binaryWriter.Write(AllLists.tpet_exp_MenuData[index3].a_acc_rate_param1);
              binaryWriter.Write(AllLists.tpet_exp_MenuData[index3].a_acc_rate_param2);
            }
          }
        }
        binaryWriter.Close();
      }
      catch (Exception ex)
      {
        int num2 = (int) MessageBox.Show(ex.Message, "ERROR", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
    }

    private void tbStrength_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbStrength.BackColor = Color.PaleTurquoise;
    }

    private void TbDexteriety_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.TbDexteriety.BackColor = Color.PaleTurquoise;
    }

    private void tbIntelligence_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbIntelligence.BackColor = Color.PaleTurquoise;
    }

    private void tbConstitution_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbConstitution.BackColor = Color.PaleTurquoise;
    }

    private void tbmaxHP_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbmaxHP.BackColor = Color.PaleTurquoise;
    }

    private void tbmaxMP_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbmaxMP.BackColor = Color.PaleTurquoise;
    }

    private void tbmaxFaith_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbmaxFaith.BackColor = Color.PaleTurquoise;
    }

    private void tbmaxStm_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbmaxStm.BackColor = Color.PaleTurquoise;
    }

    private void tbRecoveryHP_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbRecoveryHP.BackColor = Color.PaleTurquoise;
    }

    private void tbRecoveryMP_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbRecoveryMP.BackColor = Color.PaleTurquoise;
    }

    private void tbAiSlot_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbAiSlot.BackColor = Color.PaleTurquoise;
    }

    private void tbDelay_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbDelay.BackColor = Color.PaleTurquoise;
    }

    private void tbAfterDead_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbAfterDead.BackColor = Color.PaleTurquoise;
    }

    private void TbHitpoint_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.TbHitpoint.BackColor = Color.PaleTurquoise;
    }

    private void tbAvoid_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbAvoid.BackColor = Color.PaleTurquoise;
    }

    private void tbMagicAvoid_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbMagicAvoid.BackColor = Color.PaleTurquoise;
    }

    private void tbAttackSpeed_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbAttackSpeed.BackColor = Color.PaleTurquoise;
    }

    private void tbAttack_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbAttack.BackColor = Color.PaleTurquoise;
    }

    private void tbDefense_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbDefense.BackColor = Color.PaleTurquoise;
    }

    private void tbmAttack_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbmAttack.BackColor = Color.PaleTurquoise;
    }

    private void tbmDefense_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbmDefense.BackColor = Color.PaleTurquoise;
    }

    private void tbDeadly_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbDeadly.BackColor = Color.PaleTurquoise;
    }

    private void tbWeak_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbWeak.BackColor = Color.PaleTurquoise;
    }

    private void tbFlag_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbFlag.BackColor = Color.PaleTurquoise;
    }

    private void tbCritical_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbCritical.BackColor = Color.PaleTurquoise;
    }

    private void tbStrong_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbStrong.BackColor = Color.PaleTurquoise;
    }

    private void tbBasicSkill1_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbBasicSkill1.BackColor = Color.PaleTurquoise;
    }

    private void tbBasicSkill2_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbBasicSkill2.BackColor = Color.PaleTurquoise;
    }

    private void tbAwful_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbAwful.BackColor = Color.PaleTurquoise;
    }

    private void tbNoraml_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbNoraml.BackColor = Color.PaleTurquoise;
    }

    private void tbItemIndex_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbItemIndex.BackColor = Color.PaleTurquoise;
    }

    private void txtID_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.txtID.BackColor = Color.PaleTurquoise;
    }

    private void txtName_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.txtName.BackColor = Color.PaleTurquoise;
    }

    private void tbAniIdle1_1_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbAniIdle1_1.BackColor = Color.PaleTurquoise;
    }

    private void tbAniIdle2_1_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbAniIdle2_1.BackColor = Color.PaleTurquoise;
    }

    private void tbAniAttack1_1_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbAniAttack1_1.BackColor = Color.PaleTurquoise;
    }

    private void tbAniAttack2_1_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbAniAttack2_1.BackColor = Color.PaleTurquoise;
    }

    private void tbAniDie1_1_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbAniDie1_1.BackColor = Color.PaleTurquoise;
    }

    private void tbAniWalk1_1_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbAniWalk1_1.BackColor = Color.PaleTurquoise;
    }

    private void tbAniRun1_1_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbAniRun1_1.BackColor = Color.PaleTurquoise;
    }

    private void tbAniDamage1_1_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbAniDamage1_1.BackColor = Color.PaleTurquoise;
    }

    private void tbLevelUp1_1_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbLevelUp1_1.BackColor = Color.PaleTurquoise;
    }

    private void tbSkillSummon1_1_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbSkillSummon1_1.BackColor = Color.PaleTurquoise;
    }

    private void tbSpeed1_1_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbSpeed1_1.BackColor = Color.PaleTurquoise;
    }

    private void tbSmc1_1_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbSmc1_1.BackColor = Color.PaleTurquoise;
    }

    private void tbMount1_1_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbMount1_1.BackColor = Color.PaleTurquoise;
    }

    private void tbAniIdle1_2_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbAniIdle1_2.BackColor = Color.PaleTurquoise;
    }

    private void tbAniIdle2_2_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbAniIdle2_2.BackColor = Color.PaleTurquoise;
    }

    private void tbAniAttack1_2_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbAniAttack1_2.BackColor = Color.PaleTurquoise;
    }

    private void tbAniAttack2_2_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbAniAttack2_2.BackColor = Color.PaleTurquoise;
    }

    private void tbAniDie1_2_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbAniDie1_2.BackColor = Color.PaleTurquoise;
    }

    private void tbAniWalk1_2_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbAniWalk1_2.BackColor = Color.PaleTurquoise;
    }

    private void tbAniRun1_2_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbAniRun1_2.BackColor = Color.PaleTurquoise;
    }

    private void tbAniDamage1_2_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbAniDamage1_2.BackColor = Color.PaleTurquoise;
    }

    private void tbLevelUp1_2_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbLevelUp1_2.BackColor = Color.PaleTurquoise;
    }

    private void tbSkillSummon1_2_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbSkillSummon1_2.BackColor = Color.PaleTurquoise;
    }

    private void tbSpeed1_2_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbSpeed1_2.BackColor = Color.PaleTurquoise;
    }

    private void tbSmc1_2_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbSmc1_2.BackColor = Color.PaleTurquoise;
    }

    private void tbTransType_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbTransType.BackColor = Color.PaleTurquoise;
    }

    private void tbTransStart_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbTransStart.BackColor = Color.PaleTurquoise;
    }

    private void tbTransEnd_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbTransEnd.BackColor = Color.PaleTurquoise;
    }

    private void tb_ev_ID_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tb_ev_ID.BackColor = Color.PaleTurquoise;
    }

    private void tb_to_ev_id_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tb_to_ev_id.BackColor = Color.PaleTurquoise;
    }

    private void tb_ev_Level_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tb_ev_Level.BackColor = Color.PaleTurquoise;
    }

    private void tb_ev_Stemina_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tb_ev_Stemina.BackColor = Color.PaleTurquoise;
    }

    private void tb_ev_Faith_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tb_ev_Faith.BackColor = Color.PaleTurquoise;
    }

    private void tb_ev_stat1_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tb_ev_stat1.BackColor = Color.PaleTurquoise;
    }

    private void tb_ev_stat2_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tb_ev_stat2.BackColor = Color.PaleTurquoise;
    }

    private void tb_ev_order_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tb_ev_order.BackColor = Color.PaleTurquoise;
    }

    private void tb_exp_a_pet_index_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tb_exp_a_pet_index.BackColor = Color.PaleTurquoise;
    }

    private void tb_exp_a_max_acc_param1_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tb_exp_a_max_acc_param1.BackColor = Color.PaleTurquoise;
    }

    private void tb_exp_a_max_acc_param2_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tb_exp_a_max_acc_param2.BackColor = Color.PaleTurquoise;
    }

    private void tb_exp_a_acc_rate_param1_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tb_exp_a_acc_rate_param1.BackColor = Color.PaleTurquoise;
    }

    private void tb_exp_a_acc_rate_param2_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tb_exp_a_acc_rate_param2.BackColor = Color.PaleTurquoise;
    }

    private void tb_exp_a_cooltime_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tb_exp_a_cooltime.BackColor = Color.PaleTurquoise;
    }

    private void tb_exp_a_cooltime_rate_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tb_exp_a_cooltime_rate.BackColor = Color.PaleTurquoise;
    }

    private void comboBox1_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.comboBox1.BackColor = Color.PaleTurquoise;
    }

    private void flag_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.flag.BackColor = Color.PaleTurquoise;
    }

    private void flag_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.flag.BackColor = Color.PaleTurquoise;
    }

    private void comboBox1_SelectionChangeCommitted(object sender, EventArgs e)
    {
      this.comboBox1.BackColor = Color.PaleTurquoise;
    }

    private void tbMount1_2_KeyPress(object sender, KeyPressEventArgs e)
    {
      this.tbMount1_2.BackColor = Color.PaleTurquoise;
    }

        private void FillGrid()
        {
            this.dgItems.Rows.Clear();

            string query = "SELECT * FROM t_attack_pet_exp ORDER BY a_pet_index";

            using (var connection = new MySqlConnection(
                "datasource=" + this.Host +
                ";Port=3306;User ID=" + this.User +
                ";Password=" + this.Password +
                ";Database=" + this.Database +
                ";Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;"))
            {
                connection.Open();

                using (var command = new MySqlCommand(query, connection))
                using (var reader = command.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        // Safely convert all columns to strings
                        string petIndex = reader["a_pet_index"].ToString();
                        string maxAccParam1 = reader["a_max_acc_param1"].ToString();
                        string maxAccParam2 = reader["a_max_acc_param2"].ToString();
                        string accRateParam1 = reader["a_acc_rate_param1"].ToString();
                        string accRateParam2 = reader["a_acc_rate_param2"].ToString();
                        string cooltime = reader["a_cooltime"].ToString();
                        string cooltimeRate = reader["a_cooltime_rate"].ToString();

                        // Add each row to the grid
                        this.dgItems.Rows.Add(
                            petIndex,
                            maxAccParam1,
                            maxAccParam2,
                            accRateParam1,
                            accRateParam2,
                            cooltime,
                            cooltimeRate
                        );
                    }
                }
            }
        }


        private void dgItems_CellClick(object sender, DataGridViewCellEventArgs e)
    {
      if (e.RowIndex < 0)
        return;
      DataGridViewRow row = this.dgItems.Rows[e.RowIndex];
      this.textBox1.Text = row.Cells["a_pet_index"].Value.ToString();
      this.textBox2.Text = row.Cells["a_max_acc_param1"].Value.ToString();
      this.textBox5.Text = row.Cells["a_max_acc_param2"].Value.ToString();
      this.textBox3.Text = row.Cells["a_acc_rate_param1"].Value.ToString();
      this.textBox4.Text = row.Cells["a_acc_rate_param2"].Value.ToString();
      this.textBox7.Text = row.Cells["a_cooltime"].Value.ToString();
      this.textBox6.Text = row.Cells["a_cooltime_rate"].Value.ToString();
    }

    private void button12_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want to Delete Pet Exp Data ID " + this.textBox1.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_attack_pet_exp WHERE a_pet_index = '" + this.textBox1.Text + "'");
      this.FillGrid();
    }

    private void button9_Click(object sender, EventArgs e)
    {
      this.IniRead();
      if (MessageBox.Show("Do you want to Change Pet Exp Data ID " + this.textBox1.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      MySqlConnection connection = new MySqlConnection("datasource=" + this.textBox8.Text + ";port=3306;username=" + this.textBox9.Text + ";password=" + this.textBox10.Text);
      MySqlCommand mySqlCommand = new MySqlCommand("UPDATE " + this.textBox11.Text + ".t_attack_pet_exp SET a_max_acc_param1='" + this.textBox2.Text + "', a_max_acc_param2='" + this.textBox5.Text + "', a_acc_rate_param1='" + this.textBox3.Text + "', a_acc_rate_param2='" + this.textBox4.Text + "', a_cooltime='" + this.textBox7.Text + "', a_cooltime_rate='" + this.textBox6.Text + "' WHERE a_pet_index='" + this.textBox1.Text + "'", connection);
      try
      {
        connection.Open();
        MySqlDataReader mySqlDataReader = mySqlCommand.ExecuteReader();
        int num = (int) MessageBox.Show("Your Reward is Saved!");
        while (mySqlDataReader.Read())
          ;
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message);
      }
      this.FillGrid();
    }

    private void button6_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want add Pet Exp Data ID " + this.textBox1.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      if (this.textBox1.Text.Trim().Length <= 0)
      {
        int num1 = (int) MessageBox.Show("No data to select", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_attack_pet_exp (a_pet_index, a_max_acc_param1, a_max_acc_param2, a_acc_rate_param1, a_acc_rate_param2, a_cooltime, a_cooltime_rate) VALUES (" + this.textBox1.Text + ", " + this.textBox2.Text + ", " + this.textBox5.Text + ", " + this.textBox3.Text + ", " + this.textBox4.Text + ", " + this.textBox7.Text + ", " + this.textBox6.Text + ")");
        int num2 = (int) MessageBox.Show("Successful add new", "Completed", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
        this.FillGrid();
      }
    }

        private void FillGrid2()
        {
            this.dataGridView1.Rows.Clear();

            string query = "SELECT * FROM t_attack_pet_ev ORDER BY a_pet_index";

            using (var connection = new MySqlConnection(
                "datasource=" + this.Host +
                ";Port=3306;User ID=" + this.User +
                ";Password=" + this.Password +
                ";Database=" + this.Database +
                ";Charset=utf8mb4;SslMode=Preferred;TlsVersion=Tls12;"))
            {
                connection.Open();

                using (var command = new MySqlCommand(query, connection))
                using (var reader = command.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        // Safely convert all values to string form for display
                        string petIndex = reader["a_pet_index"].ToString();
                        string level = reader["a_level"].ToString();
                        string stamina = reader["a_stemina"].ToString();
                        string faith = reader["a_faith"].ToString();
                        string stat1 = reader["a_stat1"].ToString();
                        string stat2 = reader["a_stat2"].ToString();
                        string evPetIndex = reader["a_ev_pet_index"].ToString();
                        string order = reader["a_order"].ToString();

                        // Add row in the same order your grid expects
                        this.dataGridView1.Rows.Add(
                            petIndex,   // a_pet_index
                            evPetIndex, // a_ev_pet_index
                            level,      // a_level
                            stamina,    // a_stemina
                            faith,      // a_faith
                            stat1,      // a_stat1
                            stat2,      // a_stat2
                            order       // a_order
                        );
                    }
                }
            }
        }


        private void dataGridView1_CellClick(object sender, DataGridViewCellEventArgs e)
    {
      if (e.RowIndex < 0)
        return;
      DataGridViewRow row = this.dataGridView1.Rows[e.RowIndex];
      this.textBox16.Text = row.Cells["a_pet_index_evo"].Value.ToString();
      this.textBox18.Text = row.Cells["a_level"].Value.ToString();
      this.textBox17.Text = row.Cells["a_stemina"].Value.ToString();
      this.textBox13.Text = row.Cells["a_faith"].Value.ToString();
      this.textBox15.Text = row.Cells["a_stat1"].Value.ToString();
      this.textBox14.Text = row.Cells["a_stat2"].Value.ToString();
      this.textBox19.Text = row.Cells["a_ev_pet_index"].Value.ToString();
      this.textBox12.Text = row.Cells["a_order"].Value.ToString();
    }

    private void button4_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want to Delete Pet Evo Data ID " + this.textBox16.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "DELETE FROM t_attack_pet_ev WHERE a_pet_index='" + this.textBox16.Text + "' AND a_ev_pet_index='" + this.textBox19.Text + "'AND a_order='" + this.textBox12.Text + "' ");
      this.FillGrid2();
    }

    private void button5_Click(object sender, EventArgs e)
    {
      this.IniRead();
      if (MessageBox.Show("Do you want to Change Pet Evo Data ID " + this.textBox16.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      MySqlConnection connection = new MySqlConnection("datasource=" + this.textBox8.Text + ";port=3306;username=" + this.textBox9.Text + ";password=" + this.textBox10.Text);
      MySqlCommand mySqlCommand = new MySqlCommand("UPDATE " + this.textBox11.Text + ".t_attack_pet_ev SET a_level='" + this.textBox18.Text + "', a_stemina='" + this.textBox17.Text + "', a_faith='" + this.textBox13.Text + "', a_stat1='" + this.textBox15.Text + "', a_stat2='" + this.textBox14.Text + "', a_ev_pet_index='" + this.textBox19.Text + "' WHERE a_pet_index='" + this.textBox16.Text + "' AND a_order='" + this.textBox12.Text + "' ", connection);
      try
      {
        connection.Open();
        MySqlDataReader mySqlDataReader = mySqlCommand.ExecuteReader();
        int num = (int) MessageBox.Show("Your Reward is Saved!");
        while (mySqlDataReader.Read())
          ;
      }
      catch (Exception ex)
      {
        int num = (int) MessageBox.Show(ex.Message);
      }
      this.FillGrid2();
    }

    private void button7_Click(object sender, EventArgs e)
    {
      if (MessageBox.Show("Do you want add Pet Evo Data ID " + this.textBox16.Text.Trim() + " ?", "Please confirm.", MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)
        return;
      if (this.textBox16.Text.Trim().Length <= 0)
      {
        int num1 = (int) MessageBox.Show("No data to select", "Error", MessageBoxButtons.OK, MessageBoxIcon.Hand);
      }
      else
      {
        this.databaseHandle.SendQueryMySql(this.Host, this.User, this.Password, this.Database, "INSERT INTO t_attack_pet_ev (a_pet_index, a_level, a_stemina, a_faith, a_stat1, a_stat2, a_ev_pet_index, a_order) VALUES (" + this.textBox16.Text + ", " + this.textBox18.Text + ", " + this.textBox17.Text + ", " + this.textBox13.Text + ", " + this.textBox15.Text + ", " + this.textBox14.Text + ", " + this.textBox19.Text + ", " + this.textBox12.Text + ")");
        int num2 = (int) MessageBox.Show("Successful add new", "Completed", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
        this.FillGrid2();
      }
    }
  }
}
