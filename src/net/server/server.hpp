#include <WinSock2.h>
#include <sstream>

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
    int read(std::stringstream &buf);
    server(int port) : port(port) { init(); }
};