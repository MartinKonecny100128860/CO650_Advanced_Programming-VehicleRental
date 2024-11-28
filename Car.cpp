#include "Car.h"

Car::Car(int id, const std::string& make, const std::string& model, int year, const std::string& color, double costPerDay)
    : Vehicle(id, make, model, year, color, costPerDay), available(true) {}

bool Car::getAvailability() const {
    return available;
}

void Car::setAvailability(bool availability) {
    available = availability;
}

void Car::displayCarInfo() const {
    std::cout << "ID: " << id << " - " << getCarInfo() << std::endl;
}

void Car::displayCarInfo(bool includeCostAndAvailability) const {
    std::cout << "ID: " << id << " - " << getCarInfo()
        << ", Cost per day: GBP " << costPerDay
        << ", Available: " << (available ? "Yes" : "No") << std::endl;
}
// Implementing displayInfo for the Car class
void Car::displayInfo() const {
    std::cout << "Car ID: " << id << ", Make: " << make << ", Model: " << model
        << ", Year: " << year << ", Color: " << color
        << ", Cost Per Day: £" << costPerDay << std::endl;
}

// Implementing calculateRentalCost for the Car class
double Car::calculateRentalCost(int rentalDuration) {
    return costPerDay * rentalDuration;  // Calculate cost based on the rental duration
}