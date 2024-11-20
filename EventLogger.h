#ifndef EVENTLOGGER_H
#define EVENTLOGGER_H

#include <string>
#include <fstream>
#include "Car.h"

class EventLogger {
private:
    std::string logFileName;  // Name of the log file

public:
    // Constructor to initialize the logger with a file name
    EventLogger(const std::string& fileName);

    // Method to log car rental events
    void logCarRental(const Car& car, const std::string& customerName);

    // Method to log car addition events
    void logCarAddition(const Car& car);
    void saveCarToFile(const Car& car);  // New function to save car to file
};

#endif