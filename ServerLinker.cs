using System;
using System.Collections.Generic;
using System.IO.Pipes;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.IO.Ports;

namespace KTANECommunication
{
    class Program
    {
        static void Main(string[] args)
        {
            var pipein = new NamedPipeServerStream("KTANEin");
            var pipeout = new NamedPipeClientStream("KTANEout");
            pipein.WaitForConnection();
            Thread.Sleep(1000);
            pipeout.Connect();
            Console.WriteLine("pipes open");
            StreamReader reader = new StreamReader(pipeout);
            StreamWriter writer = new StreamWriter(pipein);
            writer.AutoFlush = true;
            
            SerialPort port = new SerialPort("COM5", 9600);
            port.Open();

            while (true)
            {
                string hardwareInput = port.ReadLine();
                Console.WriteLine("Hardware "+hardwareInput);
                writer.WriteLine(hardwareInput);

                string inputraw = reader.ReadLine().ToLower();
                switch (inputraw)
                {
                    case "true":
                        inputraw = "1";
                        break;
                    case "false":
                        inputraw = "0";
                        break;
                }

                byte result = Convert.ToByte(Int32.Parse(inputraw));
                Console.WriteLine("Response " + result);

                port.Write(new byte[]{result},0,1);
            }
        }
    }
}
