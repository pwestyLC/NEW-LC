// Decompiled with JetBrains decompiler
// Type: LcDevPack_TeamDamonA.Tools.Animation_Picker
// Assembly: LcDevPack_TeamDamonA, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: B13AD660-B9C7-4C88-A534-19FC9102A906
// Assembly location: C:\Users\westy\Desktop\my lc\LC_TOOLS\LCT\Debug\LcDevPack_TeamDamonA.exe

using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

#nullable disable
namespace LcDevPack_TeamDamonA.Tools
{
  public class Animation_Picker : Form
  {
    public string Animation;
    private IContainer components = (IContainer) null;
    private ListBox LbAnimationList;
    private Button BtnPickAni;

    public Animation_Picker(string FileName, string Animation)
    {
      this.InitializeComponent();
      this.Text = Animation;
      foreach (cAnimation cAnimation in AnimReader.ReadFile(FileName).Animation)
        this.LbAnimationList.Items.Add((object) cAnimation.AnimeName);
    }

    private void LbAnimationList_SelectedIndexChanged(object sender, EventArgs e)
    {
      this.Animation = this.LbAnimationList.Text;
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (Animation_Picker));
      this.LbAnimationList = new ListBox();
      this.BtnPickAni = new Button();
      this.SuspendLayout();
      this.LbAnimationList.FormattingEnabled = true;
      this.LbAnimationList.Location = new Point(12, 12);
      this.LbAnimationList.Name = "LbAnimationList";
      this.LbAnimationList.Size = new Size(206, 303);
      this.LbAnimationList.TabIndex = 0;
      this.LbAnimationList.SelectedIndexChanged += new EventHandler(this.LbAnimationList_SelectedIndexChanged);
      this.BtnPickAni.DialogResult = DialogResult.OK;
      this.BtnPickAni.FlatStyle = FlatStyle.Popup;
      this.BtnPickAni.Location = new Point(13, 321);
      this.BtnPickAni.Name = "BtnPickAni";
      this.BtnPickAni.Size = new Size(206, 23);
      this.BtnPickAni.TabIndex = 1;
      this.BtnPickAni.Text = "Pick Animation";
      this.BtnPickAni.UseVisualStyleBackColor = true;
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.ClientSize = new Size(230, 345);
      this.Controls.Add((Control) this.BtnPickAni);
      this.Controls.Add((Control) this.LbAnimationList);
      this.Icon = (Icon) componentResourceManager.GetObject("$this.Icon");
      this.Name = nameof (Animation_Picker);
      this.StartPosition = FormStartPosition.CenterParent;
      this.Text = nameof (Animation_Picker);
      this.ResumeLayout(false);
    }
  }
}
