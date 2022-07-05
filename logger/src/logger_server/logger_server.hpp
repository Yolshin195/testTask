#include <WinSock2.h>

class logger_server
{
    int port = 8006;

    SOCKET connection;

public:
    void run();
};