#include "client.hpp"
#include <iostream>

void client::init()
{
	WSADATA wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		std::cout << "Error get winSock2.dll!" << std::endl;
		exit(1);
	};

    size_addr = sizeof(addr);
	addr.sin_addr.S_un.S_addr 	= inet_addr("127.0.0.1");
	addr.sin_port 				= htons(port);
	addr.sin_family				= AF_INET;

	connection = socket(AF_INET, SOCK_STREAM, 0);

    connect_socket();
}

void client::connect_socket()
{
	if (connect(connection, (SOCKADDR*) &addr, size_addr) != 0)
	{
		std::cout << "Error: failed connect to port " << port << std::endl;
	}
    else
    {
        std::cout << "Connected to server to port" << port << std::endl;
    }
}

// void client::write(char *msg, int size)
// {
//     int s = send(connection, msg, size, 0);
// 	std::cout << "status logger: " << s << std::endl;
// 	if (s == -1) 
// 	{
// 		init();
// 	}
// }

int client::write(std::stringstream &buf)
{
	std::string value = buf.str(); 
	int size = value.size();
	
	int status = send(connection, (char*)&size, sizeof(int), 0);

	status = send(connection, value.c_str(), value.size(), 0);

	if (status == -1) 
	{
		init();
	}

	return status;
}