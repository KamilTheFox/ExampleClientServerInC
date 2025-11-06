using ClientForCServer;
using System.Net;
using System.Net.Sockets;
using System.Text;



namespace ClientForCServer
{
    public class UDPLearn : IClientSimple
    {
        public string IPserver { get; set; }
        public int Port { get; set; }

        public void Start()
        {

            // Создаем UDP клиент
            using UdpClient client = new UdpClient();
            IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse(IPserver), Port);

            Console.WriteLine($"UDP клиент готов. Сервер: {IPserver}:{Port}");
            Console.WriteLine("Вводи сообщения (exit для выхода):");

            try
            {
                while (true)
                {
                    Console.Write("Введите сообщение: ");
                    string message = Console.ReadLine();

                    if (message?.ToLower() == "exit")
                        break;

                    if (!string.IsNullOrEmpty(message))
                    {
                        // Отправляем сообщение
                        byte[] data = Encoding.UTF8.GetBytes(message);
                        client.Send(data, data.Length, serverEndPoint);
                        Console.WriteLine($"Отправлено {data.Length} байт");

                        // Ждем ответ с таймаутом 5 секунд
                        client.Client.ReceiveTimeout = 5000;

                        try
                        {
                            byte[] responseData = client.Receive(ref serverEndPoint);
                            string response = Encoding.UTF8.GetString(responseData);
                            Console.WriteLine($"Ответ сервера: {response}");
                        }
                        catch (SocketException ex) when (ex.SocketErrorCode == SocketError.TimedOut)
                        {
                            Console.WriteLine("Таймаут ожидания ответа");
                        }
                    }

                    Console.WriteLine();
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Ошибка: {ex.Message}");
            }

            Console.WriteLine("Нажмите любую клавишу...");
            Console.ReadKey();
        }
    }
}
