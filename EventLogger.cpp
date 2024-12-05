#include "eventlogger.h"
#include "car.h"
#include "customer.h"
#include <stdexcept> // For runtime_error

std::ofstream EventLogger::logFile;  // Static member definition

// Define the EventLogger constructor
EventLogger::EventLogger(const std::string& filename) {
    initialize(filename);  // Call initialize to open the log file
}

// Initialize the log file
void EventLogger::initialize(const std::string& filename) {
    logFile.open(filename, std::ios::app);
    if (!logFile) {
        throw std::runtime_error("Error opening log file.");
    }
}

void EventLogger::logCarAddition(const Car& car) {
    log("Added car: " + car.getMake() + " " + car.getModel());
}

void EventLogger::saveCarToFile(const Car& car) {
    std::ofstream outFile("cars.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << car.getID() << "," << car.getMake() << "," << car.getModel()
            << "," << car.getYear() << "," << car.getColor() << "," << car.getCostPerDay() << "\n";
        outFile.close();
    }
}

void EventLogger::logCarRental(const Car& car, const Customer& customer) {
    log("Rented car: " + car.getMake() + " " + car.getModel() +
        " to " + customer.getFirstName() + " " + customer.getLastName());
}

// Log a message
void EventLogger::log(const std::string& message) {
    if (logFile) {
        logFile << message << std::endl;
    }
}

// Close the log file
void EventLogger::close() {
    if (logFile.is_open()) {
        logFile.close();
    }
}
