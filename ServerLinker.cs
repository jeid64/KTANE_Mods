using System;
using System.Collections.Generic;
using System.IO.Pipes;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;

namespace KTANECommunication
{
    class Program
    {
        static void Main(string[] args)
        {
            var server = new NamedPipeServerStream("KTANEpipe");
            server.WaitForConnection();
            StreamReader reader = new StreamReader(server);
            StreamWriter writer = new StreamWriter(server);
            writer.AutoFlush = true;

            SerialPort port = new SerialPort("COM5", 9600);
            port.Open();

            while (true)
            {
                string hardwareInput = port.ReadLine();
                writer.WriteLine("0maze");
                string result = reader.ReadLine();
                Console.WriteLine(result);
                port.Write(result);
            }
        }
    }
}
