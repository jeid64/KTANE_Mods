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
        public static SerialPort port = new SerialPort("COM5", 9600);

        static void Main(string[] args)
        {
            var pipein = new NamedPipeServerStream("KTANEin");
            var morsepipeout = new NamedPipeClientStream("KTANEMorseOut");
            var pipeout = new NamedPipeClientStream("KTANEout");
            pipein.WaitForConnection();
            Thread.Sleep(1000);
            pipeout.Connect();
            morsepipeout.Connect();
            Console.WriteLine("pipes open");
            StreamReader reader = new StreamReader(pipeout);
            StreamReader MorseReader = new StreamReader(morsepipeout);
            StreamWriter writer = new StreamWriter(pipein);
            writer.AutoFlush = true;
            
            port.Open();

            Thread morseThread = new Thread(new ParameterizedThreadStart(MorseHandler));
            morseThread.Start(MorseReader);
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

                string isDetonated = reader.ReadLine().ToLower();
                isDetonated = reader.ReadLine().ToLower();//what the fuck is happening
                if (isDetonated.Equals("detonated:true"))
                {
                    Console.WriteLine("Explosion");
                    port.Write(new byte[] { 1 }, 0, 1);
                }
                else
                {
                    port.Write(new byte[] { 0 }, 0, 1);
                }
            }
        }

        public static void MorseHandler(object MorseReader_arg)
        {
            StreamReader MorseReader = (StreamReader)MorseReader_arg;
            while (true)
            {
                string inputraw = MorseReader.ReadLine().ToLower();
                switch (inputraw)
                {
                    case "true":
                        inputraw = "255";
                        break;
                    case "false":
                        inputraw = "254";
                        break;
                }
                byte result = Convert.ToByte(Int32.Parse(inputraw));
                port.Write(new byte[] { result }, 0, 1);
            }
        }
    }
}
