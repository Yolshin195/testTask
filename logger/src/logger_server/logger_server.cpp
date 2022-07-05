#include "logger_server.hpp"
#include <iostream>
#pragma comment(lib, "ws2_32.lib")

void logger_server::run()
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
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(this->port);
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, 0);
	bind(sListen, (SOCKADDR *)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

    char msg[256];

	std::cout << "Started logger to port " << this->port << std::endl;

    while (1)
    {
        this->connection = accept(sListen, (SOCKADDR *)&addr, &size_addr);
        int status = -1;
        while (status != 0)
        {
            status = recv(this->connection, msg, sizeof(msg), 0);
			std::cout << msg << std::endl;
        }
    }
	
}