#include "serverlogger.h"
#include <iostream>
#include <ws2tcpip.h>
#include <string>

#define BUFFER_SIZE 1024

// Constructor: Initializes Winsock and sets up initial state for the server logger
ServerLogger::ServerLogger() : clientSocket(INVALID_SOCKET), isConnected(false) {
    initializeWinsock();
}

// Destructor: Ensures the connection is closed and resources are released
ServerLogger::~ServerLogger() {
    closeConnection();
}

// Initializes Winsock for network communication
void ServerLogger::initializeWinsock() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Winsock initialization failed!" << std::endl;
        exit(1);
    }
}

// Converts a standard string to a wide string (needed for certain Windows network functions)
std::wstring ServerLogger::stringToWString(const std::string& str) {
    return std::wstring(str.begin(), str.end());
}

// Connects to the server at the specified IP address and port
bool ServerLogger::connectToServer(const std::string& ipAddress, int port) {
    if (isConnected) {
        return true;  // Already connected
    }

    // Create a socket for the client
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed! Error: " << WSAGetLastError() << std::endl;
        return false;
    }

    // Setup server address structure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    // Convert IP address from string to wide string and validate it
    std::wstring wideIpAddress = stringToWString(ipAddress);
    if (InetPtonW(AF_INET, wideIpAddress.c_str(), &serverAddr.sin_addr) != 1) {
        std::cerr << "Invalid address or Address not supported!" << std::endl;
        closesocket(clientSocket);
        return false;
    }

    // Attempt to connect to the server
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Connection to server failed! Error: " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        return false;
    }

    isConnected = true;
    std::cout << "Connected to server at " << ipAddress << ":" << port << std::endl;
    return true;
}

// Sends a log message to the connected server
void ServerLogger::log(const std::string& message) {
    if (isConnected) {
        // Send the message to the server
        int bytesSent = send(clientSocket, message.c_str(), static_cast<int>(message.length()), 0);
        if (bytesSent == SOCKET_ERROR) {
            std::cerr << "Send failed: " << WSAGetLastError() << std::endl;
        }
        else {
            std::cout << "Bytes sent: " << bytesSent << " | Message sent to server: " << message << std::endl;
        }
    }
    else {
        // Display an error if not connected to the server
        std::cerr << "Not connected to server!" << std::endl;
    }
}

// Closes the connection to the server and cleans up Winsock resources
void ServerLogger::closeConnection() {
    if (isConnected) {
        closesocket(clientSocket);  // Close the socket
        WSACleanup();              // Cleanup Winsock resources
        isConnected = false;
        std::cout << "Connection closed." << std::endl;
    }
}
