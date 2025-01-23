#include "Vehicle.h"
#include <locale>

Vehicle::Vehicle(const std::string& make, const std::string& model, int year, double costPerDay)
    : make(make), model(model), year(year), costPerDay(costPerDay), id(-1) { 
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
