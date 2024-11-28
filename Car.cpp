#include "Car.h"
#include <iostream>

// Constructor implementation
Car::Car(int id, const std::string& make, const std::string& model, int year, const std::string& color, double costPerDay)
    : Vehicle(id, make, model, year, color, costPerDay), available(true) {}

// Getter for availability
bool Car::getAvailability() const {
    return available;
}

// Setter for availability
void Car::setAvailability(bool availability) {
    available = availability;
}

// Overridden method for displaying general info about the car
void Car::displayInfo() const {
    std::cout << "Car ID: " << getID() << ", Make: " << make << ", Model: " << model
        << ", Year: " << year << ", Color: " << color
        << ", Cost Per Day: £" << getCostPerDay() << std::endl;
}

// Method to calculate rental cost
double Car::calculateRentalCost(int rentalDuration) {
    return getCostPerDay() * rentalDuration;
}

// Overridden method for displaying detailed info about the car
void Car::displayCarInfo(bool includeCostAndAvailability) const {
    if (includeCostAndAvailability) {
        std::cout << "ID: " << getID() << " - " << getCarInfo()
            << ", Cost per day: GBP " << getCostPerDay()
            << ", Available: " << (available ? "Yes" : "No") << std::endl;
    }
    else {
        std::cout << "ID: " << getID() << " - " << getCarInfo() << std::endl;
    }
}
