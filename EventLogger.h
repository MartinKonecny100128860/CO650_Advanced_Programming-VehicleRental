#ifndef EVENTLOGGER_H
#define EVENTLOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include "car.h"
#include "customer.h"


class EventLogger {
private:
    static std::ofstream logFile;

public:
    EventLogger(const std::string& filename);
    void saveCustomerDetails(const Customer& customer);  // Declare the function

    // Static function for initializing the log file
    static void initialize(const std::string& filename);

    // Static function to log messages
    static void log(const std::string& message);

    // Static function to close the log file
    static void close();

    void logCarAddition(const Car& car); // Logs when a car is added
    void saveCarToFile(const Car& car); // Saves car details to a file
    void logCarRental(const Car& car, const Customer& customer); // Logs car rentals
};

#endif // EVENTLOGGER_H
