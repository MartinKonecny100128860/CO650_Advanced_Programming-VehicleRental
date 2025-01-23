#include "Vehicle.h"
#include <locale>

// Constructor: Initializes a vehicle with its make, model, year, and cost per day
// Default ID is set to -1, indicating it has not been assigned yet.
Vehicle::Vehicle(const std::string& make, const std::string& model, int year, double costPerDay)
    : make(make), model(model), year(year), costPerDay(costPerDay), id(-1) {
}

// Accessor method to get the vehicle's unique ID
int Vehicle::getID() const {
    return id;
}

// Returns a string containing detailed information about the vehicle
// Includes make, model, year, and color.
std::string Vehicle::getCarInfo() const {
    return make + " " + model + " (" + std::to_string(year) + ") Color: " + color;
}

// Accessor method to get the cost per day for renting the vehicle
double Vehicle::getCostPerDay() const {
    return costPerDay;
}
