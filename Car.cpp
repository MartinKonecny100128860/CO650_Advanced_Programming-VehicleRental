#include "car.h"
#include "InvalidCarDataException.h" // Ensure this header exists and is included
#include <iostream>
#include <iomanip>

// Constructor
Car::Car(int id, const std::string& make, const std::string& model, int year, const std::string& color, double costPerDay)
    : id(id), make(make), model(model), year(year), color(color), costPerDay(costPerDay), available(true) {
    if (costPerDay <= 0) {
        throw InvalidCarDataException("Cost per day must be a positive value.");
    }
    if (year < 1886 || year > 2100) {
        throw InvalidCarDataException("Year is out of valid range.");
    }
}

// Getters
int Car::getId() const { return id; }
std::string Car::getMake() const { return make; }
std::string Car::getModel() const { return model; }
int Car::getYear() const { return year; }
std::string Car::getColor() const { return color; }
double Car::getCostPerDay() const { return costPerDay; }
bool Car::isAvailable() const { return available; }

// Setters
void Car::setAvailable(bool availability) { available = availability; }

// Inside the Car class
void Car::displayCarDetails() const {
    std::cout << "Car ID: " << id
        << "  Make: " << make
        << "  Model: " << model
        << "  Year: " << year
        << "  Color: " << color
        << "  Cost Per Day: " << std::fixed << std::setprecision(2) << costPerDay
        << "  Availability: " << (available ? "Available" : "Not Available")
        << "\n";
}

