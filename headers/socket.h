#ifndef SOCKET_H
#define SOCKET_H

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")  // Link the Winsock library
class Socket
{
    public:
        Socket(u_short p);
        ~Socket();

        bool bindSocket();
        bool listenSocket();

        bool sendData(const char* data, int length);
        int receiveData(char* buffer, int bufferSize);
        
        void closeSocket();

    private:
        WSADATA wsaData;
        SOCKET socketHandle;
        u_short port{8080};

        bool isInitialized;  // Track Socket State

        bool initialize_winsock();
        bool createSocket();
};

#endif