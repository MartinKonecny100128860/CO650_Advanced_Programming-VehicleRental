#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <sstream>

class Car : public Vehicle {

private:
    bool available; // Availability of the car
    int id;         // Unique car ID

public:
    // Constructor
    Car(int id, const std::string& make, const std::string& model, int year, const std::string& color, double costPerDay);

    // Setters and Getters
    void setAvailability(bool availability);
    bool getAvailability() const;
    std::string getMake() const;
    std::string getModel() const;
    int getYear() const { return year; }
    std::string getColor() const { return color; }
    int getCarID() const { return id; }  // Add this function

    // Method to calculate rental cost
    double calculateRentalCost(int days) const;

    // File operations
    static void saveCarsToFile(const std::vector<Car>& cars, const std::string& filename);
    static void loadCarsFromFile(std::vector<Car>& cars, const std::string& filename);

    // Overriding displayInfo from Vehicle
    void displayInfo() const override;

};

#endif

