#include "Car.h"
#include <iostream>
#include <locale>

// Constructor definition
Car::Car(int id, const std::string& make, const std::string& model, int year, const std::string& color, double costPerDay)
    : Vehicle(make, model, year, costPerDay), id(id), available(true) {
    this->color = color;  // Set the color after calling the base class constructor
}

// Getter and Setter methods
void Car::setAvailability(bool availability) {
    available = availability;
}

bool Car::getAvailability() const {
    return available;
}

std::string Car::getMake() const {
    return make;
}

std::string Car::getModel() const {
    return model;
}

double Car::calculateRentalCost(int days) const {
    return days * costPerDay;
}

// Display car details
void Car::displayInfo() const {
    std::cout << "Car ID: " << id << ", Make: " << make << ", Model: " << model
        << ", Year: " << year << ", Color: " << color << ", Cost per day: $" << costPerDay << ".00"
        << ", Available: " << (available ? "Yes" : "No") << "\n";
}

// Static file operations
void Car::saveCarsToFile(const std::vector<Car>& cars, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const Car& car : cars) {
            file << car.getCarID() << "," << car.getMake() << "," << car.getModel() << ","
                << car.getYear() << "," << car.getColor() << "," << car.calculateRentalCost(1) << "\n";
        }
        file.close();
    }
    else {
        std::cerr << "Error opening file for saving cars!\n";
    }
}

void Car::loadCarsFromFile(std::vector<Car>& cars, const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        int id, year;
        std::string make, model, color;
        double costPerDay;

        while (file >> id) {
            file.ignore();
            std::getline(file, make, ',');
            std::getline(file, model, ',');
            file >> year;
            file.ignore();
            std::getline(file, color, ',');
            file >> costPerDay;
            cars.push_back(Car(id, make, model, year, color, costPerDay));
        }
        file.close();
    }
    else {
        std::cerr << "Error opening file for loading cars!\n";
    }
}


