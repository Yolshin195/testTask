#include "socket.hpp"
#include <stdio.h>
#include <iostream>

inline bool InitializeSockets()
{
#if PLATFORM == PLATFORM_WINDOWS
    WSADATA WsaData;
    return WSAStartup(MAKEWORD(2, 2), &WsaData) == NO_ERROR;
#else
    return true;
#endif
}

inline void ShutdownSockets()
{
#if PLATFORM == PLATFORM_WINDOWS
    WSACleanup();
#endif
}

Socket::Socket()
{
}

Socket::~Socket()
{
}

bool Socket::Open(unsigned short port)
{
    InitializeSockets();

    int handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (handle <= 0)
    {
        printf("failed to create socket\n");
        return false;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons((unsigned short)port);

    if (bind(handle, (const sockaddr *)&address, sizeof(sockaddr_in)) < 0)
    {
        printf("failed to bind socket\n");
        return false;
    }

#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX

    int nonBlocking = 1;
    if (fcntl(handle, F_SETFL, O_NONBLOCK, nonBlocking) == -1)
    {
        printf("failed to set non-blocking socket\n");
        return false;
    }

#elif PLATFORM == PLATFORM_WINDOWS

    DWORD nonBlocking = 1;
    if (ioctlsocket(handle, FIONBIO, &nonBlocking) != 0)
    {
        printf("failed to set non-blocking socket\n");
        return false;
    }

#endif

    return true;
}

void Socket::Close()
{
#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
    close(handle);
#elif PLATFORM == PLATFORM_WINDOWS
    closesocket(handle);
#endif

    ShutdownSockets();
}

bool Socket::IsOpen() const
{
    return false;
}

bool Socket::Send(const Address &destination, const void *packet_data, int packet_size)
{

    char data[256] = "test";

    std::cout << packet_data << std::endl;

    unsigned int a = 127;
    unsigned int b = 0;
    unsigned int c = 0;
    unsigned int d = 1;
    unsigned short port = 9001;

    unsigned int destination_address = ( a << 24 ) | ( b << 16 ) | ( c << 8 ) | d;
    unsigned short destination_port = port;

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl( destination.GetAddress() );
    address.sin_port = htons( destination.GetPort() );

    int sent_bytes = sendto(handle, (const char *)data, packet_size,
                            0, (sockaddr *)&address, sizeof(sockaddr_in));

    if (sent_bytes != packet_size)
    {
        printf("failed to send packet: return value = %d\n", sent_bytes);
        return false;
    }

    return true;
}

int Socket::Receive(Address &sender, void *packet_data, int packet_size)
{
    sockaddr_in from;
    socklen_t fromLength = sizeof(from);

    int received_bytes = recvfrom(handle, (char *)packet_data, packet_size,
                                  0, (sockaddr *)&from, &fromLength);

    unsigned int from_address = ntohl(from.sin_addr.s_addr);
    unsigned int from_port = ntohs(from.sin_port);

    return received_bytes;
}

Address::Address() {}

Address::Address(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned short port)
{
    this->address = ( a << 24 ) | ( b << 16 ) | ( c << 8 ) | d;
    this->port = port;
}

Address::Address(unsigned int address, unsigned short port)
{
    this->address = address;
    this->port = port;
}

unsigned int Address::GetAddress() const
{
    return address;
}

unsigned char Address::GetA() const
{
    return 1;
}

unsigned char Address::GetB() const
{
    return 1;
}

unsigned char Address::GetC() const
{
    return 1;
}

unsigned char Address::GetD() const
{
    return 1;
}

unsigned short Address::GetPort() const
{
    return port;
}

bool Address::operator==(const Address &other) const
{
    return (address == other.GetAddress()) && (port == other.GetPort()); 
}

bool Address::operator!=(const Address &other) const
{
    return (address != other.GetAddress()) || (port != other.GetPort());
}

