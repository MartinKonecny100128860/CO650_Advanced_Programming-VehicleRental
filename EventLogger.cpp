#include "EventLogger.h"
#include <iostream>

// Constructor: Opens a log file for writing
EventLogger::EventLogger(const std::string& fileName) : logFileName(fileName) {}

// Logs car rental events Demonstrates FRIENDSHIP: Accesses Car's private members directly
void EventLogger::logCarRental(const Car& car, const std::string& customerName) {
    std::ofstream logFile(logFileName, std::ios::app);
    if (logFile.is_open()) {
        logFile << "Car Rented: " << car.getCarInfo()
            << " by " << customerName
            << ". Cost Per Day: £" << car.costPerDay << "\n";
        logFile.close();
    }
    else {
        std::cerr << "Failed to open log file.\n";
    }
}

// Logs car addition events
void EventLogger::logCarAddition(const Car& car) {
    std::ofstream logFile(logFileName, std::ios::app);
    if (logFile.is_open()) {
        logFile << "Car Added: " << car.getCarInfo()
            << ". Cost Per Day: £" << car.costPerDay << "\n";
        logFile.close();
    }
    else {
        std::cerr << "Failed to open log file.\n";
    }
}

void EventLogger::saveCarToFile(const Car& car) {
    std::ofstream carFile("cars.txt", std::ios::app);
    if (carFile.is_open()) {
        carFile << car.getID() << "," << car.make << "," << car.model << "," << car.year
            << "," << car.color << "," << car.costPerDay << "\n";
        carFile.close();
    }
    else {
        std::cerr << "Failed to open cars.txt for writing.\n";
    }
}


