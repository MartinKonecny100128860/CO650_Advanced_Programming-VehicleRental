#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <iostream>
#include <stdexcept>

class Vehicle {
protected:
    int id;
    std::string make;
    std::string model;
    int year;
    std::string color;
    double costPerDay;

public:
    Vehicle(int id, const std::string& make, const std::string& model, int year, const std::string& color, double costPerDay);
    std::string getMake() const { return make; }
    std::string getModel() const { return model; }
    std::string getColor() const { return color; }
    int getYear() const { return year; }
    virtual ~Vehicle() = default; // Virtual destructor for proper cleanup in derived classes

    int getID() const;
    std::string getCarInfo() const;
    double getCostPerDay() const;
    virtual bool getAvailability() const = 0;  // Pure virtual method, forcing Car to implement
    virtual void setAvailability(bool availability) = 0;  // Pure virtual method
    virtual double calculateRentalCost(int rentalDuration) = 0;  // Pure virtual method
    // Virtual method for polymorphism
    virtual void displayInfo() const = 0;  // Pure virtual function (abstract method)
    virtual void displayCarInfo(bool includeCostAndAvailability) const {
        std::cout << "Vehicle ID: " << id << " - " << getCarInfo() << std::endl;

    }
};

#endif
