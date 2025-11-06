using ClientForCServer;

string serverIP = "192.168.41.130";
int port = 8080;

IClientSimple[] clientSimples =
{
    new TCPLearn(),
    new UDPLearn()
};

IClientSimple current = clientSimples[1];
current.IPserver = serverIP;
current.Port = port;

current.Start();
