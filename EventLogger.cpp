#include "eventlogger.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>

// Constructor
EventLogger::EventLogger(const std::string& filePath) : logFilePath(filePath) {}

// Destructor
EventLogger::~EventLogger() {
    // Optional cleanup, if necessary
}

// Log an event
void EventLogger::logEvent(const std::string& eventMessage) {
    // Lock mutex to ensure thread-safe access
    std::lock_guard<std::mutex> lock(logMutex);

    // Open file in append mode
    std::ofstream logFile(logFilePath, std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file: " << logFilePath << "\n";
        return;
    }

    // Get current time
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Use localtime_s for thread-safe conversion
    std::tm localTime;
    if (localtime_s(&localTime, &currentTime) != 0) {
        std::cerr << "Failed to get local time.\n";
        return;
    }

    // Write timestamp and event message
    logFile << "[" << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S") << "] "
        << eventMessage << "\n";

    logFile.close();
}

// Clear log file
void EventLogger::clearLogFile() {
    // Lock mutex to ensure thread-safe access
    std::lock_guard<std::mutex> lock(logMutex);

    // Open file in truncation mode to clear content
    std::ofstream logFile(logFilePath, std::ios::trunc);
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file: " << logFilePath << "\n";
        return;
    }

    logFile.close();
}
