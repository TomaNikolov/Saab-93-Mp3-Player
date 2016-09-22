namespace SaabSerialSimulator.DesktopClient
{
	using System;
	using System.Windows.Forms;

	public static class StartUp
	{
		[STAThread]
		static void Main()
		{
			Application.EnableVisualStyles();
			Application.SetCompatibleTextRenderingDefault(false);
			Application.Run(new MainWindow());
		}
	}
}