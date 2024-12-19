#include "serverlogger.h"
#include <iostream>
#include <ws2tcpip.h>
#include <string>

#define BUFFER_SIZE 1024

ServerLogger::ServerLogger() : clientSocket(INVALID_SOCKET), isConnected(false) {
    initializeWinsock();
}

ServerLogger::~ServerLogger() {
    closeConnection();
}

void ServerLogger::initializeWinsock() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Winsock initialization failed!" << std::endl;
        exit(1);
    }
}

std::wstring ServerLogger::stringToWString(const std::string& str) {
    return std::wstring(str.begin(), str.end());
}

bool ServerLogger::connectToServer(const std::string& ipAddress, int port) {
    if (isConnected) {
        return true;  // Already connected
    }

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed! Error: " << WSAGetLastError() << std::endl;
        return false;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    std::wstring wideIpAddress = stringToWString(ipAddress);
    if (InetPtonW(AF_INET, wideIpAddress.c_str(), &serverAddr.sin_addr) != 1) {
        std::cerr << "Invalid address or Address not supported!" << std::endl;
        closesocket(clientSocket);
        return false;
    }

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Connection to server failed! Error: " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        return false;
    }

    isConnected = true;
    std::cout << "Connected to server at " << ipAddress << ":" << port << std::endl;
    return true;
}

void ServerLogger::log(const std::string& message) {
    if (isConnected) {
        int bytesSent = send(clientSocket, message.c_str(), static_cast<int>(message.length()), 0);
        if (bytesSent == SOCKET_ERROR) {
            std::cerr << "Send failed: " << WSAGetLastError() << std::endl;
        }
        else {
            std::cout << "Bytes sent: " << bytesSent << " | Message sent to server: " << message << std::endl;
        }
    }
    else {
        std::cerr << "Not connected to server!" << std::endl;
    }
}

void ServerLogger::closeConnection() {
    if (isConnected) {
        closesocket(clientSocket);
        WSACleanup();
        isConnected = false;
        std::cout << "Connection closed." << std::endl;
    }
}
