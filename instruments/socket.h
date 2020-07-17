#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H

#ifndef _WIN32
#include <arpa/inet.h>
typedef int SOCKET;
#define NULL nullptr
#else
#include <winsock2.h>
#endif

class Socket
{
    SOCKET sock;
    sockaddr_in address;

    Socket(int);
public:

    static void init();
    static void clear();

    int send(char* data, int len);
    int receive(char* buffer, int len);
    int connect(const char * ip_addr, int port);
    int bind(int port);


    int listen() const;
    Socket * accept();

    Socket();
    ~Socket();
};

#endif // SOCKETCLIENT_H
