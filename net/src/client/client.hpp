#include <WinSock2.h>
#include "../signal/signal.hpp"

class client
{
    int port;
    int status;
    int size_addr;
    SOCKADDR_IN addr;
    SOCKET connection;
    
    void connect_socket();

public:
    client(int port) : port(port) {
        init();
    };
    void init();
    void write(char *msg, int size);
    void write(signal siganl);
};