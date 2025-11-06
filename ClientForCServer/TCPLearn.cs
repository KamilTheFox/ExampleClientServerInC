using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;
using System.Text;

namespace ClientForCServer
{
    public class TCPLearn : IClientSimple
    {
        public string IPserver { get; set; }
        public int Port { get; set; }

        public void Start()
        {
            Console.WriteLine($"Подключаемся к серверу {IPserver}:{Port}");
            Console.WriteLine("Вводи сообщения (для выхода введите 'exit'):");

            try
            {
                using TcpClient client = new TcpClient();
                client.Connect(IPserver, Port);

                NetworkStream stream = client.GetStream();
                byte[] buffer = new byte[1024];

                // Запускаем поток для приема сообщений от сервера
                Thread receiveThread = new Thread(() =>
                {
                    while (client.Connected)
                    {
                        try
                        {
                            int bytesRead = stream.Read(buffer, 0, buffer.Length);
                            if (bytesRead > 0)
                            {
                                string response = Encoding.UTF8.GetString(buffer, 0, bytesRead);
                                Console.WriteLine($"\n[Сервер]: {response}");
                                Console.Write("Введите сообщение: ");
                            }
                        }
                        catch
                        {
                            break;
                        }
                    }
                });
                receiveThread.Start();

                // Главный цикл для отправки сообщений
                while (client.Connected)
                {
                    Console.Write("Введите сообщение: ");
                    string message = Console.ReadLine();

                    if (message?.ToLower() == "exit")
                        break;

                    if (!string.IsNullOrEmpty(message))
                    {
                        byte[] data = Encoding.UTF8.GetBytes(message);
                        stream.Write(data, 0, data.Length);
                        Console.WriteLine($"Отправлено: {message}");

                    }
                }

                client.Close();
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Ошибка: {ex.Message}");
            }

            Console.WriteLine("Нажмите любую клавишу для выхода...");
            Console.ReadKey();
        }

      
    }
}
