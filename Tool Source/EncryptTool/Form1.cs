// Decompiled with JetBrains decompiler
// Type: EncryptTool.Form1
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Windows.Forms;

#nullable disable
namespace EncryptTool
{
  public class Form1 : Form
  {
    private int indexOfExtension;
    private IContainer components = (IContainer) null;
    private OpenFileDialog openFileDialog1;
    private ComboBox comboBox1;
    private Button button1;
    private Label label2;
    private Label label1;
    private SaveFileDialog saveFileDialog1;
    private Button button2;

    public Form1()
    {
      this.InitializeComponent();
      this.comboBox1.SelectedIndex = 0;
    }

    private void button1_Click(object sender, EventArgs e)
    {
      switch (this.indexOfExtension)
      {
        case 0:
          this.openFileDialog1.Filter = "Tex (*.tex)|*.tex";
          this.saveFileDialog1.Filter = "Tex (*.tex)|*.tex";
          this.saveFileDialog1.FilterIndex = 1;
          this.openFileDialog1.FilterIndex = 1;
          break;
        case 1:
          this.openFileDialog1.Filter = "Model (*.bm)|*.bm";
          this.saveFileDialog1.Filter = "Model (*.bm)|*.bm";
          this.saveFileDialog1.FilterIndex = 1;
          this.openFileDialog1.FilterIndex = 1;
          break;
        case 2:
          this.openFileDialog1.Filter = "Bones (*.bs)|*.bs";
          this.saveFileDialog1.Filter = "Bones (*.bs)|*.bs";
          this.saveFileDialog1.FilterIndex = 1;
          this.openFileDialog1.FilterIndex = 1;
          break;
        case 3:
          this.openFileDialog1.Filter = "Animation (*.ba)|*.ba";
          this.saveFileDialog1.Filter = "Animation (*.ba)|*.ba";
          this.saveFileDialog1.FilterIndex = 1;
          this.openFileDialog1.FilterIndex = 1;
          break;
        case 4:
          this.openFileDialog1.Filter = "Animation Effects (*.bae)|*.bae";
          this.saveFileDialog1.Filter = "Animation Effects (*.bae)|*.bae";
          this.saveFileDialog1.FilterIndex = 1;
          this.openFileDialog1.FilterIndex = 1;
          break;
        case 5:
          this.openFileDialog1.Filter = "Collider (*.bmc)|*.bmc";
          this.saveFileDialog1.Filter = "Collider (*.bmc)|*.bmc";
          this.openFileDialog1.FilterIndex = 1;
          this.saveFileDialog1.FilterIndex = 1;
          break;
      }
      DialogResult dialogResult = this.openFileDialog1.ShowDialog();
      int num1 = (int) this.saveFileDialog1.ShowDialog();
      if (dialogResult != DialogResult.OK)
        return;
      string fileName1 = this.openFileDialog1.FileName;
      string fileName2 = this.saveFileDialog1.FileName;
      try
      {
        switch (this.indexOfExtension)
        {
          case 0:
            if (File.Exists(fileName1))
            {
              byte[] numArray;
              long num2;
              using (BinaryReader binaryReader = new BinaryReader((Stream) File.Open(fileName1, FileMode.Open)))
              {
                binaryReader.BaseStream.Seek(0L, SeekOrigin.Begin);
                numArray = binaryReader.ReadBytes((int) binaryReader.BaseStream.Length);
                binaryReader.BaseStream.Seek(12L, SeekOrigin.Begin);
                num2 = (long) binaryReader.ReadUInt32() + (long) numArray.Length;
              }
              using (BinaryWriter binaryWriter = new BinaryWriter((Stream) File.Open(fileName2, FileMode.Create)))
              {
                numArray[4] = (byte) 18;
                for (int index = 0; index < 8; ++index)
                  binaryWriter.Write(numArray[index]);
                binaryWriter.Write(num2);
                numArray[0] = (byte) 65;
                numArray[1] = (byte) 122;
                numArray[2] = (byte) 97;
                numArray[3] = (byte) 122;
                numArray[4] = (byte) 101;
                numArray[5] = (byte) 108;
                numArray[6] = (byte) 76;
                numArray[7] = (byte) 67;
                binaryWriter.BaseStream.Seek(12L, SeekOrigin.Begin);
                for (int index = 0; index < 8; ++index)
                  binaryWriter.Write(numArray[index]);
                numArray[4] = (byte) 46;
                numArray[5] = (byte) 114;
                numArray[6] = (byte) 117;
                numArray[7] = (byte) 0;
                for (int index = 4; index < 8; ++index)
                  binaryWriter.Write(numArray[index]);
                for (int index = 8; index < 12; ++index)
                  binaryWriter.Write(numArray[index]);
                for (int index = 16; index < numArray.Length; ++index)
                  binaryWriter.Write(numArray[index]);
                break;
              }
            }
            else
              break;
          case 1:
            if (File.Exists(fileName1))
            {
              byte[] numArray;
              long num3;
              using (BinaryReader binaryReader = new BinaryReader((Stream) File.Open(fileName1, FileMode.Open)))
              {
                binaryReader.BaseStream.Seek(0L, SeekOrigin.Begin);
                numArray = binaryReader.ReadBytes((int) binaryReader.BaseStream.Length);
                binaryReader.BaseStream.Seek(8L, SeekOrigin.Begin);
                num3 = (long) (binaryReader.ReadUInt32() / 2U) + (long) numArray.Length;
              }
              using (BinaryWriter binaryWriter = new BinaryWriter((Stream) File.Open(fileName2, FileMode.Create)))
              {
                numArray[4] = (byte) 0;
                numArray[5] = (byte) 0;
                numArray[6] = (byte) 19;
                numArray[7] = (byte) 0;
                for (int index = 0; index < 8; ++index)
                  binaryWriter.Write(numArray[index]);
                binaryWriter.Write(num3);
                numArray[0] = (byte) 65;
                numArray[1] = (byte) 122;
                numArray[2] = (byte) 97;
                numArray[3] = (byte) 122;
                numArray[4] = (byte) 101;
                numArray[5] = (byte) 108;
                numArray[6] = (byte) 76;
                numArray[7] = (byte) 67;
                binaryWriter.BaseStream.Seek(12L, SeekOrigin.Begin);
                for (int index = 0; index < 8; ++index)
                  binaryWriter.Write(numArray[index]);
                numArray[4] = (byte) 46;
                numArray[5] = (byte) 114;
                numArray[6] = (byte) 117;
                numArray[7] = (byte) 0;
                for (int index = 4; index < 8; ++index)
                  binaryWriter.Write(numArray[index]);
                for (int index = 12; index < numArray.Length; ++index)
                  binaryWriter.Write(numArray[index]);
                break;
              }
            }
            else
              break;
          case 3:
            byte[] numArray1;
            long num4;
            using (BinaryReader binaryReader = new BinaryReader((Stream) File.Open(fileName1, FileMode.Open)))
            {
              binaryReader.BaseStream.Seek(0L, SeekOrigin.Begin);
              numArray1 = binaryReader.ReadBytes((int) binaryReader.BaseStream.Length);
              binaryReader.BaseStream.Seek(8L, SeekOrigin.Begin);
              num4 = (long) binaryReader.ReadUInt32() + (long) numArray1.Length - 353L;
            }
            using (BinaryWriter binaryWriter = new BinaryWriter((Stream) File.Open(fileName2, FileMode.Create)))
            {
              numArray1[4] = (byte) 21;
              int num5 = 0;
              for (int index = 0; index < 8; ++index)
                binaryWriter.Write(numArray1[index]);
              binaryWriter.Write(num4);
              binaryWriter.Write(num5);
              numArray1[0] = (byte) 91;
              numArray1[1] = (byte) 65;
              numArray1[2] = (byte) 68;
              numArray1[3] = (byte) 77;
              numArray1[4] = (byte) 93;
              numArray1[5] = (byte) 68;
              numArray1[6] = (byte) 97;
              numArray1[7] = (byte) 114;
              binaryWriter.BaseStream.Seek(12L, SeekOrigin.Begin);
              for (int index = 0; index < 8; ++index)
                binaryWriter.Write(numArray1[index]);
              numArray1[4] = (byte) 107;
              numArray1[5] = (byte) 0;
              numArray1[6] = (byte) 0;
              numArray1[7] = (byte) 0;
              for (int index = 4; index < 8; ++index)
                binaryWriter.Write(numArray1[index]);
              for (int index = 8; index < 12; ++index)
                binaryWriter.Write(numArray1[index]);
              for (int index = 16; index < numArray1.Length; ++index)
                binaryWriter.Write(numArray1[index]);
              break;
            }
        }
      }
      catch (IOException ex)
      {
      }
    }

    private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.indexOfExtension = this.comboBox1.SelectedIndex;
    }

    private void button2_Click(object sender, EventArgs e)
    {
      switch (this.indexOfExtension)
      {
        case 0:
          this.openFileDialog1.Filter = "Tex (*.tex)|*.tex";
          this.saveFileDialog1.Filter = "Tex (*.tex)|*.tex";
          this.saveFileDialog1.FilterIndex = 1;
          this.openFileDialog1.FilterIndex = 1;
          break;
        case 1:
          this.openFileDialog1.Filter = "Model (*.bm)|*.bm";
          this.saveFileDialog1.Filter = "Model (*.bm)|*.bm";
          this.saveFileDialog1.FilterIndex = 1;
          this.openFileDialog1.FilterIndex = 1;
          break;
        case 2:
          this.openFileDialog1.Filter = "Bones (*.bs)|*.bs";
          this.saveFileDialog1.Filter = "Bones (*.bs)|*.bs";
          this.saveFileDialog1.FilterIndex = 1;
          this.openFileDialog1.FilterIndex = 1;
          break;
        case 3:
          this.openFileDialog1.Filter = "Animation (*.ba)|*.ba";
          this.saveFileDialog1.Filter = "Animation (*.ba)|*.ba";
          this.saveFileDialog1.FilterIndex = 1;
          this.openFileDialog1.FilterIndex = 1;
          break;
        case 4:
          this.openFileDialog1.Filter = "Animation Effects (*.bae)|*.bae";
          this.saveFileDialog1.Filter = "Animation Effects (*.bae)|*.bae";
          this.saveFileDialog1.FilterIndex = 1;
          this.openFileDialog1.FilterIndex = 1;
          break;
        case 5:
          this.openFileDialog1.Filter = "Collider (*.bmc)|*.bmc";
          this.saveFileDialog1.Filter = "Collider (*.bmc)|*.bmc";
          this.openFileDialog1.FilterIndex = 1;
          this.saveFileDialog1.FilterIndex = 1;
          break;
      }
      DialogResult dialogResult = this.openFileDialog1.ShowDialog();
      int num1 = (int) this.saveFileDialog1.ShowDialog();
      if (dialogResult != DialogResult.OK)
        return;
      string fileName1 = this.openFileDialog1.FileName;
      string fileName2 = this.saveFileDialog1.FileName;
      try
      {
        int num2 = 0;
        switch (this.indexOfExtension)
        {
          case 0:
            if (File.Exists(fileName1))
            {
              byte[] numArray;
              using (BinaryReader binaryReader = new BinaryReader((Stream) File.Open(fileName1, FileMode.Open)))
              {
                binaryReader.BaseStream.Seek(0L, SeekOrigin.Begin);
                numArray = binaryReader.ReadBytes((int) binaryReader.BaseStream.Length);
                switch (numArray[4])
                {
                  case 17:
                    break;
                  case 18:
                    binaryReader.BaseStream.Seek(8L, SeekOrigin.Begin);
                    num2 = binaryReader.ReadInt32() - numArray.Length + 12;
                    break;
                  default:
                    int num3 = (int) MessageBox.Show("Unknown Encryption");
                    return;
                }
              }
              using (BinaryWriter binaryWriter = new BinaryWriter((Stream) File.Open(fileName2, FileMode.Create)))
              {
                switch (numArray[4])
                {
                  case 17:
                    numArray[4] = (byte) 4;
                    for (int index = 0; index < 8; ++index)
                      binaryWriter.Write(numArray[index]);
                    for (int index = 12; index < numArray.Length; ++index)
                      binaryWriter.Write(numArray[index]);
                    break;
                  case 18:
                    numArray[4] = (byte) 4;
                    for (int index = 0; index < 8; ++index)
                      binaryWriter.Write(numArray[index]);
                    for (int index = 24; index < 28; ++index)
                      binaryWriter.Write(numArray[index]);
                    binaryWriter.Write(num2);
                    for (int index = 28; index < numArray.Length; ++index)
                      binaryWriter.Write(numArray[index]);
                    break;
                }
              }
              break;
            }
            break;
          case 1:
            if (File.Exists(fileName1))
            {
              byte[] numArray;
              using (BinaryReader binaryReader = new BinaryReader((Stream) File.Open(fileName1, FileMode.Open)))
              {
                binaryReader.BaseStream.Seek(0L, SeekOrigin.Begin);
                numArray = binaryReader.ReadBytes((int) binaryReader.BaseStream.Length);
                switch (numArray[6])
                {
                  case 18:
                    break;
                  case 19:
                    binaryReader.BaseStream.Seek(8L, SeekOrigin.Begin);
                    num2 = (binaryReader.ReadInt32() - numArray.Length) * 2 + 25;
                    break;
                  default:
                    int num4 = (int) MessageBox.Show("Unknown Encryption");
                    return;
                }
              }
              using (BinaryWriter binaryWriter = new BinaryWriter((Stream) File.Open(fileName2, FileMode.Create)))
              {
                switch (numArray[6])
                {
                  case 18:
                    numArray[4] = (byte) 17;
                    numArray[5] = (byte) 0;
                    numArray[6] = (byte) 0;
                    numArray[7] = (byte) 0;
                    for (int index = 0; index < 8; ++index)
                      binaryWriter.Write(numArray[index]);
                    for (int index = 12; index < numArray.Length; ++index)
                      binaryWriter.Write(numArray[index]);
                    break;
                  case 19:
                    numArray[4] = (byte) 17;
                    numArray[5] = (byte) 0;
                    numArray[6] = (byte) 0;
                    numArray[7] = (byte) 0;
                    for (int index = 0; index < 8; ++index)
                      binaryWriter.Write(numArray[index]);
                    binaryWriter.Write(num2);
                    for (int index = 24; index < numArray.Length; ++index)
                      binaryWriter.Write(numArray[index]);
                    break;
                }
              }
              break;
            }
            break;
          case 3:
            byte[] numArray1;
            using (BinaryReader binaryReader = new BinaryReader((Stream) File.Open(fileName1, FileMode.Open)))
            {
              binaryReader.BaseStream.Seek(0L, SeekOrigin.Begin);
              numArray1 = binaryReader.ReadBytes((int) binaryReader.BaseStream.Length);
              if (numArray1[4] == (byte) 21)
              {
                binaryReader.BaseStream.Seek(8L, SeekOrigin.Begin);
                num2 = binaryReader.ReadInt32() - numArray1.Length + 365;
                int num5 = (int) MessageBox.Show(num2.ToString() ?? "");
              }
              else
              {
                int num6 = (int) MessageBox.Show("Unknown Encryption");
                break;
              }
            }
            using (BinaryWriter binaryWriter = new BinaryWriter((Stream) File.Open(fileName2, FileMode.Create)))
            {
              if (numArray1[4] == (byte) 21)
              {
                numArray1[4] = (byte) 20;
                for (int index = 0; index < 8; ++index)
                  binaryWriter.Write(numArray1[index]);
                binaryWriter.Write(num2);
                for (int index = 28; index < numArray1.Length; ++index)
                  binaryWriter.Write(numArray1[index]);
                break;
              }
              break;
            }
        }
      }
      catch (IOException ex)
      {
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
      this.openFileDialog1 = new OpenFileDialog();
      this.button1 = new Button();
      this.comboBox1 = new ComboBox();
      this.label1 = new Label();
      this.label2 = new Label();
      this.saveFileDialog1 = new SaveFileDialog();
      this.button2 = new Button();
      this.SuspendLayout();
      this.openFileDialog1.FileName = "openFileDialog1";
      this.button1.Location = new Point(89, 95);
      this.button1.Name = "button1";
      this.button1.Size = new Size(60, 23);
      this.button1.TabIndex = 1;
      this.button1.Text = "Encrypt";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.comboBox1.FormattingEnabled = true;
      this.comboBox1.Items.AddRange(new object[6]
      {
        (object) "Texture (.tex)",
        (object) "Model (*.bm)",
        (object) "Bones (*.bs)",
        (object) "Animation (*.ba)",
        (object) "Animation Effects (*.bae)",
        (object) "Collider (*.bmc)"
      });
      this.comboBox1.Location = new Point(89, 58);
      this.comboBox1.Name = "comboBox1";
      this.comboBox1.Size = new Size(121, 21);
      this.comboBox1.TabIndex = 3;
      this.comboBox1.SelectedIndexChanged += new EventHandler(this.comboBox1_SelectedIndexChanged);
      this.label1.AutoSize = true;
      this.label1.Font = new Font("Comic Sans MS", 9.75f, FontStyle.Regular, GraphicsUnit.Point, (byte) 204);
      this.label1.ForeColor = Color.Navy;
      this.label1.Location = new Point(101, 9);
      this.label1.Name = "label1";
      this.label1.Size = new Size(109, 18);
      this.label1.TabIndex = 4;
      this.label1.Text = " LC Encrypt Tool\r\n";
      this.label1.TextAlign = ContentAlignment.MiddleCenter;
      this.label2.AutoSize = true;
      this.label2.Location = new Point(124, 37);
      this.label2.Name = "label2";
      this.label2.Size = new Size(50, 13);
      this.label2.TabIndex = 5;
      this.label2.Text = "File Type";
      this.button2.Location = new Point(150, 95);
      this.button2.Name = "button2";
      this.button2.Size = new Size(60, 23);
      this.button2.TabIndex = 7;
      this.button2.Text = "Decrypt";
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.AutoSizeMode = AutoSizeMode.GrowAndShrink;
      this.ClientSize = new Size(299, 138);
      this.Controls.Add((Control) this.button2);
      this.Controls.Add((Control) this.label2);
      this.Controls.Add((Control) this.label1);
      this.Controls.Add((Control) this.comboBox1);
      this.Controls.Add((Control) this.button1);
      this.Name = nameof (Form1);
      this.Text = "Encrypt Tool";
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
