#include <iostream>
#include "headers/socket.h"

// Constructor and helper functions.
//------------------------------------------------------------------------------
Socket::Socket(u_short p) : port(p), socketHandle(INVALID_SOCKET) 
{
    if(initialize_winsock())
    { 
        isInitialized = createSocket(); 
    }
}

bool Socket::initialize_winsock() 
{
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if(result != 0) 
    {
        std::cerr<<"WSAStartup failed: "<<result<<std::endl;
        return false;
    }
    return true;
}

bool Socket::createSocket() 
{
    socketHandle = socket(AF_INET, SOCK_STREAM, 0);
    if(socketHandle == INVALID_SOCKET) 
    {
        std::cerr<<"Socket creation failed: "<<WSAGetLastError()<<std::endl;
        WSACleanup();
        return false;
    }
    return true;
}
//------------------------------------------------------------------------------

// Destructor and helpers.
//------------------------------------------------------------------------------
Socket::~Socket() 
{
    closeSocket();
}

void Socket::closeSocket() 
{
    if(socketHandle != INVALID_SOCKET) 
    {
        closesocket(socketHandle);
        socketHandle = INVALID_SOCKET;
    }
    WSACleanup();
}
//------------------------------------------------------------------------------

// Core Socket Functionality
//------------------------------------------------------------------------------
bool Socket::bindSocket()
{
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if(bind(socketHandle, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        std::cerr<<"Bind failed: "<<WSAGetLastError()<<std::endl;
        closesocket(socketHandle);
        return false;
    }
    return true;
}

bool Socket::listenSocket()
{
    if(listen(socketHandle, SOMAXCONN) == SOCKET_ERROR) 
    {
        std::cerr<<"Listen failed: "<<WSAGetLastError()<<std::endl;
        closesocket(socketHandle);
        WSACleanup();
        return false;
    }
    return true;
}

bool Socket::sendData(const char* data, int length)
{
    return true;
}

int Socket::receiveData(char* buffer, int bufferSize)
{
    int bytesReceived;
    return bytesReceived;
}
//------------------------------------------------------------------------------
