/*
    Includes/Headers
*/
#include "../headers/socket.h"
-----------------------------------------------------------------------------------------------------------------------------
/*
    Core Class Functionality
*/
Socket::Socket()
{
    initialize_winsock();
}

Socket::~Socket()
{

}

SOCKET Socket::createSocket()
{

}

void Socket::closeSocket(SOCKET sock)
{

}
-----------------------------------------------------------------------------------------------------------------------------
/*
    Helper Functions and Misc
*/
void Socket::initialize_winsock() 
{
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if(result != 0) 
    {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        exit(1);
    }
}
-----------------------------------------------------------------------------------------------------------------------------