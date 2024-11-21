#ifndef EVENTLOGGER_H
#define EVENTLOGGER_H

#include <string>
#include <fstream>
#include <mutex>

class EventLogger {
private:
    std::string logFilePath; // Path to the log file
    std::mutex logMutex;     // Mutex for thread-safe logging

public:
    // Constructor
    explicit EventLogger(const std::string& filePath);

    // Destructor
    ~EventLogger();

    // Log an event
    void logEvent(const std::string& eventMessage);

    // Clear log file
    void clearLogFile();
};

#endif // EVENTLOGGER_H
