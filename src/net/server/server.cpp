#include "server.hpp"
#include <iostream>

void server::init()
{
    WSADATA wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		std::cout << "Error get winSock2.dll!" << std::endl;
		exit(1);
	};

	this->size_addr = sizeof(this->addr);
	this->addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	this->addr.sin_port = htons(this->port);
	this->addr.sin_family = AF_INET;

	this->listener = socket(AF_INET, SOCK_STREAM, 0);
	bind(this->listener, (SOCKADDR *)&addr, sizeof(addr));
	listen(this->listener, SOMAXCONN);
	connect();
}

void server::connect()
{
    this->connection = accept(this->listener, (SOCKADDR *)&addr, &size_addr);
	std::cout << "new connection!" << std::endl;
}

// void server::read(char *msg, int size)
// {
//     int status = recv(this->connection, msg, size, 0);
//     if (status == -1)
//     {
// 		std::cout << "close connection!" << std::endl;
//         connect();
//         recv(this->connection, msg, size, 0);
//     }
    
// }

int server::read(std::stringstream &buf)
{	
	int size = 0;
    int status = recv(this->connection, (char*)(&size), sizeof(int), 0);
	std::cout << "read size: " << size << std::endl;

	char* data = new char[size];
	status = recv(this->connection, data, size, 0);
	buf << data;

    if (status == -1)
    {
		std::cout << "close connection!" << std::endl;
        connect();
		return -1;
    }

	return status;
}