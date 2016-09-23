namespace SaabSerialSimulator.DesktopClient
{ 
	using System;
	using System.IO.Ports;
	using System.Linq;
	using System.Windows.Forms;

	public partial class MainWindow : Form
	{
		private SerialPort comPort;
		private delegate void SetTextCallback(string text);

		public MainWindow()
		{
			comPort = new SerialPort();
			InitializeComponent();
			InitializeComPorts();
			comPort.DataReceived += new SerialDataReceivedEventHandler(OnDataReceived);
		}
	 
		private void InitializeComPorts()
		{
			var comPortsNames = SerialPort.GetPortNames();
			Array.ForEach(comPortsNames, name => cboPorts.Items.Add(name));

			Array.Sort(comPortsNames);

			// get first item print in text
			this.cboPorts.Text = comPortsNames.First();

			// Baud Rate
			this.cboBaudRate.Items.Add(9600);
			this.cboBaudRate.Items.Add(14400);
			this.cboBaudRate.Items.Add(19200);
			this.cboBaudRate.Items.Add(38400);
			this.cboBaudRate.Items.Add(57600);
			this.cboBaudRate.Items.Add(115200);
			this.cboBaudRate.Items.ToString();

			// get first item print in text
			this.cboBaudRate.Text = cboBaudRate.Items[0].ToString();
		}

		private void OnDataReceived(object sender, SerialDataReceivedEventArgs e)
		{
			var inputData = comPort.ReadExisting();
			if (inputData != string.Empty)
			{
				this.BeginInvoke(new SetTextCallback(this.SetText), new object[] { inputData });
			}
		}

		private void SetText(string text)
		{
			this.rtbIncoming.Text += text;
		}

		private void btnTest_Click(object sender, EventArgs e)
		{
			this.comPort.Open();

			this.comPort.RtsEnable = true;
			this.comPort.DtrEnable = true;
			this.btnTest.Enabled = false;
		}

		private void btnPortState_Click(object sender, EventArgs e)
		{
			try
			{
				if (this.btnPortState.Text == "Open")
				{
					this.comPort.PortName = Convert.ToString(cboPorts.Text);
					this.comPort.BaudRate = Convert.ToInt32(cboBaudRate.Text);
					this.comPort.Open();
					this.btnPortState.Text = "Close";
				}
				else if (this.btnPortState.Text == "Close")
				{
					this.comPort.Close();
					this.btnPortState.Text = "open";
				}
			}
			catch (Exception ex)
			{
				MessageBox.Show(ex.Message);
			}
		}

		private void Btn_SendClick(object sender, EventArgs e)
		{
			if (comPort.IsOpen)
			{
				comPort.Write(this.rtbOutgoing.Text);
			}

			this.rtbOutgoing.Text = string.Empty;
		}

		private void Btn_Change_song(object sender, EventArgs e)
		{
			if (comPort.IsOpen)
			{
				var message = ((Button) sender).Text;
				comPort.Write(message);
			}
		}
	}
}
