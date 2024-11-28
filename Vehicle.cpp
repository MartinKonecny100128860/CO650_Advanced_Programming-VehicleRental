#include "Vehicle.h"

Vehicle::Vehicle(int id, const std::string& make, const std::string& model, int year, const std::string& color, double costPerDay)
    : id(id), make(make), model(model), year(year), color(color), costPerDay(costPerDay) {
    // Exception Handling: Ensure `costPerDay` is positive; throw an exception if invalid
    if (costPerDay <= 0) {
        throw std::invalid_argument("Cost per day must be a positive value.");
    }
    // Exception Handling: Validate the year is within a realistic range; throw an exception if invalid
    if (year < 1886 || year > 2100) {
        throw std::invalid_argument("Year is out of valid range.");
    }
}

int Vehicle::getID() const {
    return id;
}

std::string Vehicle::getCarInfo() const {
    return make + " " + model + " " + std::to_string(year) + " Color: " + color;
}

double Vehicle::getCostPerDay() const {
    return costPerDay;
}
