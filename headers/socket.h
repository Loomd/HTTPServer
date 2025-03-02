/*
    Includes, Constants...
*/
#ifndef SOCKET_H
#define SOCKET_H

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")  // Link with Winsock library ("g++ -o http_server.exe main.cpp -lws2_32").

#define PORT 8080
#define BUFFER_SIZE 1024
-----------------------------------------------------------------------------------------------------------------------------
/*
    Socket class specifications:
        public:
            - Constructor: Socket(); 
            - Destructor: ~Socket();
            - Generate a socket: SOCKET createSocket();
            - Terminate a socket: void closeSocket(Socket sock);
        Private:
            - Struct from winsock2.h which contains information about the windows socket implementation: WSADATA wsaData;
            - Initialize Winsock2 API: void initialize_winsock();
*/
class Socket
{
    public:
        Socket();
        ~Socket();
        SOCKET createSocket();
        void closeSocket(SOCKET sock);
    private:
        WSADATA wsaData;
        void initialize_winsock();
};
-----------------------------------------------------------------------------------------------------------------------------
#endif