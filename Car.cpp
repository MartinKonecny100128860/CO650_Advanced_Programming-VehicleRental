#include "Car.h"

// CONSTRUCTOR: Initializes the car's attributes when a new Car object is created.
Car::Car(int id, const std::string& make, const std::string& model, int year, const std::string& color, double costPerDay)
    : id(id), make(make), model(model), year(year), color(color), costPerDay(costPerDay), available(true) {
    // Exception Handling: Ensure `costPerDay` is positive; throw an exception if inval
    if (costPerDay <= 0) {
        throw std::invalid_argument("Cost per day must be a positive value.");
    }
    // Exception Handling: Validate the year is within a realistic range; throw an exception if invalid
    if (year < 1886 || year > 2100) {
        throw std::invalid_argument("Year is out of valid range.");
    }
}



// ENCAPSULATION: private members can't be directly accessed from outside the class.
// Access is controlled via getters and setters.
bool Car::getAvailability() const {
    return available;
}

// Set car availability
void Car::setAvailability(bool availability) {
    available = availability;
}

// Get car ID
int Car::getID() const {
    return id;
}

// getCarInfo() ABSTRACTS the details of how car info is stored and returns it as a string.
std::string Car::getCarInfo() const {
    return make + " " + model + " " + std::to_string(year) + " Color: " + color;
}

// calculateRentalCost() ABSTRACTS the calculation logic for the rental cost.
double Car::calculateRentalCost(int rentalDuration) const {
    return costPerDay * rentalDuration;
}

// Display car information
void Car::displayCarInfo() const {
    std::cout << "ID: " << id << " - " << getCarInfo()
        << ", Cost per day: GBP " << costPerDay << ", Available: " << (available ? "Yes" : "No") << std::endl;
}