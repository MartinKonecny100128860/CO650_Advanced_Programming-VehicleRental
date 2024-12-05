#include "Vehicle.h"
#include <locale>

Vehicle::Vehicle(const std::string& make, const std::string& model, int year, double costPerDay)
    : make(make), model(model), year(year), costPerDay(costPerDay), id(-1) {  // Default value for id
    // Validate cost per day
    if (costPerDay <= 0) {
        throw std::invalid_argument("Cost per day must be a positive value.");
    }
    // Validate year
    if (year < 1886 || year > 2100) {
        throw std::invalid_argument("Year is out of valid range.");
    }
}


// Accessor methods
int Vehicle::getID() const {
    return id;
}

std::string Vehicle::getCarInfo() const {
    return make + " " + model + " (" + std::to_string(year) + ") Color: " + color;
}

double Vehicle::getCostPerDay() const {
    return costPerDay;
}
