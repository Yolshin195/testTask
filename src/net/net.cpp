#include "net.hpp"

net::sock &net::sock::operator << (std::string data) 
{
    buf << data;
    return *this;
}

net::sock &net::sock::operator << (double data)
{
    buf << data;
    return *this;
}

net::sock &net::sock::operator << (int data)
{
    buf << data;
    return *this;
}

net::sock &net::sock::operator << (net::sock &(*send)(net::sock &n))
{
    return send(*this);
}

net::sock &net::sock::operator >> (std::string &data)
{
    buf >> data;
    return *this;
}

void net::sock::init()
{
    WSADATA wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		std::cout << "Error get winSock2.dll!" << std::endl;
		exit(1);
	};

	SOCKADDR_IN addr;
	int size_addr = sizeof(addr);
	addr.sin_addr.S_un.S_addr 	= inet_addr("127.0.0.1");
	addr.sin_port 				= htons(port);
	addr.sin_family				= AF_INET;

	connection = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(connection, (SOCKADDR*) &addr, sizeof(addr)) != 0)
	{
		std::cout << "Error: failed connect to server." << std::endl;
		exit(1);
	}
	
	std::cout << "Connected to server" << std::endl;
}

void net::sock::_send()
{
    std::cout << buf.str().length() << " " << buf.str() << std::endl;
    std::string data = buf.str();
    int size = data.length();

    //buf.clear();

    send(connection, (char*)&size, sizeof(int), 0);
    send(connection, data.c_str(), size, 0);

    data.clear();
}

net::sock &net::sendl(net::sock &n)
{
    n._send();
    return n;
}