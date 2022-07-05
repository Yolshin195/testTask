#include "control_system.hpp"
#include <windows.h>
#include <iostream>

void control_system::getLogSocket()
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
	addr.sin_port 				= htons(this->log_port);
	addr.sin_family				= AF_INET;

	this->log_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(this->log_socket, (SOCKADDR*) &addr, sizeof(addr)) != 0)
	{
		std::cout << "Error: failed connect to logger port " << this->log_port << std::endl;
		exit(1);
	}
	
	std::cout << "Connected to server logger to port" << this->log_port << std::endl;

	// CreateThread(0, 0, (LPTHREAD_START_ROUTINE) clientHandler, 0, 0, 0);

	// char msg[256];
	// while (1)
	// {
	// 	std::cin.getline(msg, sizeof(msg));
	// 	send(Connection, msg, sizeof(msg), 0);
	// 	Sleep(10);
	// }

}

void control_system::connectSocket(int port, SOCKET *new_socket)
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

	*new_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(*new_socket, (SOCKADDR*) &addr, sizeof(addr)) != 0)
	{
		std::cout << "Error: failed connect to logger port " << port << std::endl;
		exit(1);
	}
	
	std::cout << "Connected to server logger to port" << port << std::endl;
}
void control_system::getLogSocket()
{
   connectSocket(this->log_port, &this->log_socket);
}

void control_system::update()
{
    getLogSocket();

    char msg[256] = "hello world";

    while(1)
    {
        int s = send(this->log_socket, msg, sizeof(msg), 0);
		std::cout << "status logger: " << s << std::endl;
        Sleep(1000);
    }
}