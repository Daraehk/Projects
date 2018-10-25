namespace Generics
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.PalBtn = new System.Windows.Forms.Button();
            this.PalCBX = new System.Windows.Forms.ComboBox();
            this.PalTB = new System.Windows.Forms.TextBox();
            this.AnaBtn = new System.Windows.Forms.Button();
            this.AnaTB1 = new System.Windows.Forms.TextBox();
            this.AnaTB2 = new System.Windows.Forms.TextBox();
            this.AnaCBX = new System.Windows.Forms.ComboBox();
            this.SuspendLayout();
            // 
            // PalBtn
            // 
            this.PalBtn.Location = new System.Drawing.Point(13, 13);
            this.PalBtn.Name = "PalBtn";
            this.PalBtn.Size = new System.Drawing.Size(95, 38);
            this.PalBtn.TabIndex = 0;
            this.PalBtn.Text = "Palindrome";
            this.PalBtn.UseVisualStyleBackColor = true;
            this.PalBtn.Click += new System.EventHandler(this.PalBtn_Click);
            // 
            // PalCBX
            // 
            this.PalCBX.DisplayMember = "1";
            this.PalCBX.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.PalCBX.FormattingEnabled = true;
            this.PalCBX.Items.AddRange(new object[] {
            "Integer",
            "Float",
            "Character",
            "String"});
            this.PalCBX.Location = new System.Drawing.Point(115, 23);
            this.PalCBX.Name = "PalCBX";
            this.PalCBX.Size = new System.Drawing.Size(121, 21);
            this.PalCBX.TabIndex = 0;
            this.PalCBX.ValueMember = "0";
            // 
            // PalTB
            // 
            this.PalTB.Location = new System.Drawing.Point(243, 23);
            this.PalTB.Name = "PalTB";
            this.PalTB.Size = new System.Drawing.Size(278, 20);
            this.PalTB.TabIndex = 1;
            // 
            // AnaBtn
            // 
            this.AnaBtn.Location = new System.Drawing.Point(13, 58);
            this.AnaBtn.Name = "AnaBtn";
            this.AnaBtn.Size = new System.Drawing.Size(95, 38);
            this.AnaBtn.TabIndex = 2;
            this.AnaBtn.Text = "Anagram";
            this.AnaBtn.UseVisualStyleBackColor = true;
            this.AnaBtn.Click += new System.EventHandler(this.AnaBtn_Click);
            // 
            // AnaTB1
            // 
            this.AnaTB1.Location = new System.Drawing.Point(243, 68);
            this.AnaTB1.Name = "AnaTB1";
            this.AnaTB1.Size = new System.Drawing.Size(134, 20);
            this.AnaTB1.TabIndex = 3;
            // 
            // AnaTB2
            // 
            this.AnaTB2.Location = new System.Drawing.Point(383, 68);
            this.AnaTB2.Name = "AnaTB2";
            this.AnaTB2.Size = new System.Drawing.Size(138, 20);
            this.AnaTB2.TabIndex = 4;
            // 
            // AnaCBX
            // 
            this.AnaCBX.DisplayMember = "1";
            this.AnaCBX.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.AnaCBX.FormattingEnabled = true;
            this.AnaCBX.Items.AddRange(new object[] {
            "Integer",
            "Float",
            "Character",
            "String"});
            this.AnaCBX.Location = new System.Drawing.Point(114, 68);
            this.AnaCBX.Name = "AnaCBX";
            this.AnaCBX.Size = new System.Drawing.Size(121, 21);
            this.AnaCBX.TabIndex = 5;
            this.AnaCBX.ValueMember = "0";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(533, 460);
            this.Controls.Add(this.AnaCBX);
            this.Controls.Add(this.AnaTB2);
            this.Controls.Add(this.AnaTB1);
            this.Controls.Add(this.AnaBtn);
            this.Controls.Add(this.PalTB);
            this.Controls.Add(this.PalCBX);
            this.Controls.Add(this.PalBtn);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button PalBtn;
        private System.Windows.Forms.ComboBox PalCBX;
        private System.Windows.Forms.TextBox PalTB;
        private System.Windows.Forms.Button AnaBtn;
        private System.Windows.Forms.TextBox AnaTB1;
        private System.Windows.Forms.TextBox AnaTB2;
        private System.Windows.Forms.ComboBox AnaCBX;
    }
}

