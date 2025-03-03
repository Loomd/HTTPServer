#ifndef SOCKET_H
#define SOCKET_H

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")  
// Links with the Winsock library ("g++ -o http_server.exe main.cpp -lws2_32").
// This directive tells the linker to include `ws2_32.lib`, ensuring that Winsock2 functions are available at runtime.

#define PORT 8080        // Default port for network communication.
#define BUFFER_SIZE 1024 // Buffer size for incoming data.

/**
 * @class Socket
 * @brief Handles socket operations for server-side communication using the Winsock2 API.
 * 
 * This class provides an abstraction over the raw Winsock2 API, encapsulating key networking 
 * functionality such as:
 * - Initializing Winsock (required before using sockets on Windows).
 * - Creating a socket for TCP communication.
 * - Closing a socket and properly releasing system resources.
 * 
 * The `Socket` class adheres to the **RAII (Resource Acquisition Is Initialization) principle**, 
 * ensuring Winsock is initialized at object creation and cleaned up at destruction.
 */
class Socket 
{
    public:
        /**
         * @brief Constructs a Socket object and initializes Winsock.
         * 
         * This constructor ensures that any instance of `Socket` is immediately 
         * ready for use by calling `initialize_winsock()`. It eliminates the need 
         * for manual Winsock initialization in higher-level code.
         * 
         * @pre None.
         * @post Winsock2 API is initialized for network communication.
         */
        Socket();

        /**
         * @brief Destroys the Socket object and cleans up Winsock.
         * 
         * Automatically calls `WSACleanup()`, ensuring that system resources 
         * allocated by Winsock are released when the `Socket` object goes out of scope.
         * 
         * This follows RAII principles and prevents resource leaks.
         * 
         * @pre Winsock must have been initialized.
         * @post Winsock2 API is cleaned up, releasing resources.
         */
        ~Socket();

        /**
         * @brief Creates a new socket for communication.
         * 
         * This function abstracts the `socket()` system call, ensuring that a TCP 
         * socket is properly created using:
         * - `AF_INET`: IPv4 addressing.
         * - `SOCK_STREAM`: TCP protocol (reliable, connection-oriented communication).
         * - `0`: Uses the default TCP/IP protocol.
         * 
         * If socket creation fails, an error is logged, and `INVALID_SOCKET` is returned.
         * 
         * @pre Winsock must be initialized.
         * @post Returns a valid socket descriptor if successful; otherwise, returns INVALID_SOCKET.
         * @return SOCKET A valid socket descriptor on success; INVALID_SOCKET on failure.
         */
        SOCKET createSocket();

        /**
         * @brief Closes the specified socket.
         * 
         * This function encapsulates the `closesocket()` system call, ensuring 
         * that a socket is properly closed before it goes out of scope.
         * 
         * It includes a safety check to ensure that only valid sockets are closed,
         * preventing undefined behavior or accidental double-closing.
         * 
         * @param sock The socket to be closed.
         * @pre The socket must be a valid, open socket.
         * @post The socket is closed and can no longer be used.
         */
        void closeSocket(SOCKET sock);
    
    private:
        WSADATA wsaData;  ///< Stores Winsock startup information.

        /**
         * @brief Initializes the Winsock2 API.
         * 
         * Calls `WSAStartup()`, which is required before performing any socket operations.
         * This function ensures that version 2.2 of Winsock is loaded successfully.
         * 
         * If initialization fails, an error is logged, and the program exits immediately,
         * preventing any attempts to use uninitialized sockets.
         * 
         * @pre None.
         * @post Winsock2 API is successfully initialized, or the program exits if initialization fails.
         */
        void initialize_winsock();
};

#endif // SOCKET_H
