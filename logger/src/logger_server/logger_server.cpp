#include "logger_server.hpp"
#include <iostream>
#pragma comment(lib, "ws2_32.lib")

void logger_server::run()
{
    while (1)
    {
		char msg[256];

		logger.read(msg, sizeof(msg));

		std::cout << "message: " << msg << std::endl;
    }
	
}