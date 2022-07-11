#ifndef NET_H
#define NET_H

#include <string>
#include <sstream>
#include <iostream>
#include <WinSock2.h>

namespace net {

    enum sock_type {
        CLIENT, SERVER
    };

    class sock
    {
        int port;
        sock_type type;
        SOCKET connection;

    public:
        std::stringstream buf;
        void _send();
        void _receive();
        void init();
        sock(int port, sock_type type) : port(port), type(type) {};
        sock &operator >> (std::string &data);
        sock &operator >> (double &data);
        sock &operator >> (int &data);

        sock &operator << (sock &(*send)(sock &n));

        sock &operator << (std::string data);
        sock &operator << (double data);
        sock &operator << (int data);
        sock &operator << (sock &(*send)(sock &n));
    };

    sock &sendl(sock &n);
}

#endif