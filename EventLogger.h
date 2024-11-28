#ifndef EVENTLOGGER_H
#define EVENTLOGGER_H

#include <string>
#include <fstream>
#include "Car.h"

class EventLogger {
private:
    std::string logFileName;

public:
    EventLogger(const std::string& fileName);

    void logCarRental(const Car& car, const std::string& customerName);
    void logCarAddition(const Car& car);
    void saveCarToFile(const Car& car);
};

#endif
