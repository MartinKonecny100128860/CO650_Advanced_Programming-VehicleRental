#ifndef SERVERLOGGER_H
#define SERVERLOGGER_H

#include <string>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")  // Link with ws2_32.lib

class ServerLogger {
private:
    SOCKET clientSocket;
    sockaddr_in serverAddr;
    bool isConnected;

public:
    ServerLogger();  // Constructor to initialize Winsock
    ~ServerLogger();  // Destructor to clean up Winsock and close socket

    bool connectToServer(const std::string& ipAddress, int port);  // Connect to the server
    void log(const std::string& message);  // Log message function
    void closeConnection();  // Close the connection

private:
    void initializeWinsock();  // Initialize Winsock
    std::wstring stringToWString(const std::string& str);  // Convert std::string to std::wstring
};

#endif  // SERVERLOGGER_H
