#ifndef SOCKET_H
#define SOCKET_H

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")  // Link with Winsock library ("g++ -o http_server.exe main.cpp -lws2_32").

#define PORT 8080
#define BUFFER_SIZE 1024

class Socket
{
    public:
        Socket();                        // Constructor
        ~Socket();                       // Destructor
        SOCKET createSocket();           // Creates a socket
        void closeSocket(SOCKET sock);   // Closes a socket
    private:
        WSADATA wsaData;                // Struct from winsock2.h which contains information about the windows socket implementation.
        void initialize_winsock();      // Initialize Winsock2 API 
};

#endif