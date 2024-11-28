#include "EventLogger.h"
#include <iostream>

EventLogger::EventLogger(const std::string& fileName) : logFileName(fileName) {}

void EventLogger::logCarRental(const Car& car, const std::string& customerName) {
    std::ofstream logFile(logFileName, std::ios::app);
    if (logFile.is_open()) {
        logFile << "Car Rented: " << car.getCarInfo()
            << " by " << customerName
            << ". Cost Per Day: £" << car.getCostPerDay() << "\n";
        logFile.close();
    }
    else {
        std::cerr << "Failed to open log file.\n";
    }
}

void EventLogger::logCarAddition(const Car& car) {
    std::ofstream logFile(logFileName, std::ios::app);
    if (logFile.is_open()) {
        logFile << "Car Added: " << car.getCarInfo()
            << ". Cost Per Day: £" << car.getCostPerDay() << "\n";
        logFile.close();
    }
    else {
        std::cerr << "Failed to open log file.\n";
    }
}

void EventLogger::saveCarToFile(const Car& car) {
    std::ofstream carFile("cars.txt", std::ios::app);
    if (carFile.is_open()) {
        carFile << car.getID() << ","
            << car.getMake() << ","  // Use getter for make
            << car.getModel() << "," // Use getter for model
            << car.getYear() << ","  // Assuming there's a getter for year
            << car.getColor() << "," // Use getter for color
            << car.getCostPerDay() << "\n";  // Use getter for cost per day
        carFile.close();
    }
    else {
        std::cerr << "Failed to open cars.txt for writing.\n";
    }
}
