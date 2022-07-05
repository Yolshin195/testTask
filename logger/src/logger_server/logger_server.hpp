#include <WinSock2.h>
#include "server.hpp"

class logger_server
{
    int in_port {8006};

    server logger {in_port};


public:
    void run();
};