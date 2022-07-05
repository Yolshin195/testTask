#include <WinSock2.h>

class server
{
    int port;
    int size_addr;
    SOCKADDR_IN addr;
    SOCKET listener;
    SOCKET connection;

    void init();
    void connect();

public:
    void read(char *msg, int size);
    server(int port) : port(port) { init(); }
};