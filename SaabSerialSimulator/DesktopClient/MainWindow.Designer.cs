namespace SaabSerialSimulator.DesktopClient
{
	partial class MainWindow
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
			this.rtbIncoming = new System.Windows.Forms.RichTextBox();
			this.cboPorts = new System.Windows.Forms.ComboBox();
			this.cboBaudRate = new System.Windows.Forms.ComboBox();
			this.btnTest = new System.Windows.Forms.Button();
			this.rtbOutgoing = new System.Windows.Forms.RichTextBox();
			this.button1 = new System.Windows.Forms.Button();
			this.btnPortState = new System.Windows.Forms.Button();
			this.button2 = new System.Windows.Forms.Button();
			this.button3 = new System.Windows.Forms.Button();
			this.button4 = new System.Windows.Forms.Button();
			this.button5 = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// rtbIncoming
			// 
			this.rtbIncoming.Location = new System.Drawing.Point(12, 300);
			this.rtbIncoming.Name = "rtbIncoming";
			this.rtbIncoming.Size = new System.Drawing.Size(508, 96);
			this.rtbIncoming.TabIndex = 1;
			this.rtbIncoming.Text = "";
			// 
			// cboPorts
			// 
			this.cboPorts.FormattingEnabled = true;
			this.cboPorts.Location = new System.Drawing.Point(102, 29);
			this.cboPorts.Name = "cboPorts";
			this.cboPorts.Size = new System.Drawing.Size(121, 21);
			this.cboPorts.TabIndex = 2;
			// 
			// cboBaudRate
			// 
			this.cboBaudRate.FormattingEnabled = true;
			this.cboBaudRate.Location = new System.Drawing.Point(102, 56);
			this.cboBaudRate.Name = "cboBaudRate";
			this.cboBaudRate.Size = new System.Drawing.Size(121, 21);
			this.cboBaudRate.TabIndex = 3;
			// 
			// btnTest
			// 
			this.btnTest.Location = new System.Drawing.Point(422, 27);
			this.btnTest.Name = "btnTest";
			this.btnTest.Size = new System.Drawing.Size(75, 23);
			this.btnTest.TabIndex = 12;
			this.btnTest.Text = "Test";
			this.btnTest.UseVisualStyleBackColor = true;
			this.btnTest.Visible = false;
			this.btnTest.Click += new System.EventHandler(this.btnTest_Click);
			// 
			// rtbOutgoing
			// 
			this.rtbOutgoing.Location = new System.Drawing.Point(12, 203);
			this.rtbOutgoing.Name = "rtbOutgoing";
			this.rtbOutgoing.Size = new System.Drawing.Size(333, 31);
			this.rtbOutgoing.TabIndex = 15;
			this.rtbOutgoing.Text = "";
			// 
			// button1
			// 
			this.button1.Location = new System.Drawing.Point(377, 203);
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size(75, 23);
			this.button1.TabIndex = 16;
			this.button1.Text = "Send";
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new System.EventHandler(this.Btn_SendClick);
			// 
			// btnPortState
			// 
			this.btnPortState.Location = new System.Drawing.Point(12, 29);
			this.btnPortState.Name = "btnPortState";
			this.btnPortState.Size = new System.Drawing.Size(75, 23);
			this.btnPortState.TabIndex = 13;
			this.btnPortState.Text = "Open";
			this.btnPortState.UseVisualStyleBackColor = true;
			this.btnPortState.Click += new System.EventHandler(this.btnPortState_Click);
			// 
			// button2
			// 
			this.button2.Location = new System.Drawing.Point(422, 76);
			this.button2.Name = "button2";
			this.button2.Size = new System.Drawing.Size(75, 23);
			this.button2.TabIndex = 17;
			this.button2.Text = "nextSong";
			this.button2.UseVisualStyleBackColor = true;
			this.button2.Visible = true;
			this.button2.Click += new System.EventHandler(this.Btn_Change_song);
			// 
			// button3
			// 
			this.button3.Location = new System.Drawing.Point(422, 123);
			this.button3.Name = "button3";
			this.button3.Size = new System.Drawing.Size(75, 23);
			this.button3.TabIndex = 18;
			this.button3.Text = "nextDir";
			this.button3.UseVisualStyleBackColor = true;
			this.button3.Visible = true;
			this.button3.Click += new System.EventHandler(this.Btn_Change_song);
			// 
			// button4
			// 
			this.button4.Location = new System.Drawing.Point(503, 76);
			this.button4.Name = "button4";
			this.button4.Size = new System.Drawing.Size(75, 23);
			this.button4.TabIndex = 19;
			this.button4.Text = "prevSong";
			this.button4.UseVisualStyleBackColor = true;
			this.button4.Visible = true;
			this.button4.Click += new System.EventHandler(this.Btn_Change_song);
			// 
			// button5
			// 
			this.button5.Location = new System.Drawing.Point(503, 123);
			this.button5.Name = "button5";
			this.button5.Size = new System.Drawing.Size(75, 23);
			this.button5.TabIndex = 20;
			this.button5.Text = "prevDir";
			this.button5.UseVisualStyleBackColor = true;
			this.button5.Visible = true;
			this.button5.Click += new System.EventHandler(this.Btn_Change_song);
			// 
			// MainWindow
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(567, 408);
			this.Controls.Add(this.button5);
			this.Controls.Add(this.button4);
			this.Controls.Add(this.button3);
			this.Controls.Add(this.button2);
			this.Controls.Add(this.button1);
			this.Controls.Add(this.rtbOutgoing);
			this.Controls.Add(this.btnPortState);
			this.Controls.Add(this.btnTest);
			this.Controls.Add(this.cboBaudRate);
			this.Controls.Add(this.cboPorts);
			this.Controls.Add(this.rtbIncoming);
			this.Name = "MainWindow";
			this.Text = "Serial ";
			this.ResumeLayout(false);

		}

		#endregion
		private System.Windows.Forms.RichTextBox rtbIncoming;
		private System.Windows.Forms.ComboBox cboPorts;
		private System.Windows.Forms.ComboBox cboBaudRate;
		private System.Windows.Forms.Button btnTest;
		private System.Windows.Forms.RichTextBox rtbOutgoing;
		private System.Windows.Forms.Button button1;
		private System.Windows.Forms.Button btnPortState;
		private System.Windows.Forms.Button button2;
		private System.Windows.Forms.Button button3;
		private System.Windows.Forms.Button button4;
		private System.Windows.Forms.Button button5;
	}
}

