#ifndef BROADCASTSOCKET_H
#define BROADCASTSOCKET_H

#ifndef _WIN32
#include <arpa/inet.h>
typedef int SOCKET;
#define NULL nullptr
#else
#include <winsock2.h>
#endif

class BroadcastSocket {
    SOCKET reciever, sender;
    sockaddr_in addr, res_addr;

public:
    BroadcastSocket();

    void bind(char* addr, int port);


    void send(char* buffer, int len);
    void recieve(char* buffer, int max_len);
};

#endif // BROADCASTSOCKET_H
