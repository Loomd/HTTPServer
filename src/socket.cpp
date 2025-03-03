// Socket class implementation file
// - Encapsulates Winsock2 API initialization and cleanup within an OOP paradigm.
// - Ensures that any instance of `Socket` is always in a valid state with Winsock initialized.
// - Provides an intuitive interface for socket management, eliminating the need for 
//   manual Winsock setup and cleanup by users of this class.
// - Implements RAII (Resource Acquisition Is Initialization), ensuring cleanup happens 
//   automatically when a `Socket` object goes out of scope.

#include "headers/socket.h"

/**
 * @brief Constructs a `Socket` object and initializes Winsock.
 * @details This constructor follows the **RAII (Resource Acquisition Is Initialization)** 
 * principle, ensuring that any `Socket` object is automatically equipped with an initialized 
 * Winsock environment. This eliminates the risk of the user forgetting to initialize Winsock 
 * before using sockets.
 * 
 * @pre None.
 * @post Winsock2 API is initialized and ready for socket communication.
 */
Socket::Socket() 
{
    initialize_winsock();  // Encapsulates Winsock initialization to ensure readiness.
}

/**
 * @brief Destroys the `Socket` object and cleans up Winsock.
 * @details This destructor ensures that Winsock resources are released when the object goes out 
 * of scope, following the **RAII** principle. Since Winsock operates at the OS level, failing 
 * to call `WSACleanup()` could lead to **resource leaks** that impact other applications.
 * 
 * @pre Winsock must have been initialized.
 * @post Winsock2 API is cleaned up, and system resources are released.
 */
Socket::~Socket()
{
    WSACleanup();  // Ensures Winsock cleanup upon object destruction.
}

/**
 * @brief Initializes the Winsock2 API.
 * @details This function is responsible for setting up the Winsock library for use with 
 * network programming. The function calls `WSAStartup()`, which is a mandatory requirement 
 * before any socket operations can be performed on Windows.
 * 
 * @pre None.
 * @post Winsock2 API is successfully initialized, or the program exits if initialization fails.
 */
void Socket::initialize_winsock()
{
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    
    // `MAKEWORD(2,2)` requests Winsock version 2.2, which provides modern networking capabilities.
    if(result != 0) 
    {
        // If initialization fails, output the error and terminate the program.
        std::cerr<<"WSAStartup failed: "<<result<<std::endl;
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Creates a new TCP socket for communication.
 * @details This method abstracts the socket creation process, shielding the user from the 
 * complexities of the `socket()` system call. It ensures that a valid TCP socket is created 
 * and ready to be used.
 * 
 * @pre Winsock must be initialized.
 * @post A valid socket descriptor is returned if successful; otherwise, `INVALID_SOCKET` is returned.
 * 
 * @return SOCKET A valid socket descriptor on success; `INVALID_SOCKET` on failure.
 */
SOCKET Socket::createSocket()
{
    // Create a socket using:
    // - AF_INET: Specifies IPv4 addressing.
    // - SOCK_STREAM: Specifies TCP (connection-oriented protocol).
    // - 0: Uses the default protocol for the specified type (TCP).
    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    if(server_socket == INVALID_SOCKET) 
    {
        // Retrieve and print the error code if socket creation fails.
        std::cerr<<"Socket creation failed: "<<WSAGetLastError()<<std::endl;
        return INVALID_SOCKET;
    }

    return server_socket;  // Return the successfully created socket.
}

/**
 * @brief Closes the specified socket.
 * @details This function encapsulates the `closesocket()` system call, ensuring that sockets are 
 * properly closed before they go out of scope. It also prevents undefined behavior by checking 
 * the validity of the socket before attempting to close it.
 * 
 * @param sock The socket to be closed.
 * 
 * @pre The socket must be a valid, open socket.
 * @post The socket is closed and can no longer be used.
 */
void Socket::closeSocket(SOCKET sock)
{
    // Prevent accidental double-closing of an invalid socket.
    if(sock != INVALID_SOCKET)  
    {
        closesocket(sock);  // Close the socket and release system resources.
    }
}
