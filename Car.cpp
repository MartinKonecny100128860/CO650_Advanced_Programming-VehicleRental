#include "Car.h"
#include <iostream>
#include <locale>
#include <iomanip>

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

void Car::displayInfo() const {
    // Print table header only once
    static bool headerPrinted = false;
    if (!headerPrinted) {
        std::cout << std::setw(8) << std::left << "Car ID"
            << std::setw(15) << std::left << "Make"
            << std::setw(30) << std::left << "Model"
            << std::setw(8) << std::left << "Year"
            << std::setw(30) << std::left << "Color"
            << std::setw(20) << std::right << "Cost per day"   // Right-aligned header for Cost per day
            << std::setw(15) << std::right << "Available"       // Right-aligned header for Available
            << std::endl;

        // Print table separator line: updated length to match the full column widths
        std::cout << std::string(8 + 15 + 30 + 8 + 30 + 20 + 15, '-') << std::endl;

        headerPrinted = true; // Mark header as printed
    }

    // Print car details with appropriate formatting
    std::cout << std::setw(8) << std::left << id
        << std::setw(15) << std::left << make
        << std::setw(30) << std::left << model
        << std::setw(8) << std::left << year
        << std::setw(30) << std::left << color
        << std::setw(10) << std::right << "$" << std::fixed << std::setprecision(2) << costPerDay
        << std::setw(15) << std::right << (available ? "Yes" : "No") << std::endl;

    // Print footer separator line: same length as the header separator
    std::cout << std::string(8 + 15 + 30 + 8 + 30 + 20 + 15, '-') << std::endl;
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


