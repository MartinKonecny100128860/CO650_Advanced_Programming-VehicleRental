#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <iostream>
#include <stdexcept>


// Abstract base class
class Vehicle {
protected:
    int id;
    std::string make, model, color;
    int year;
    double costPerDay;

// In Vehicle.h
public:
    Vehicle(const std::string& make, const std::string& model, int year, double costPerDay);


    // Accessor methods
    int getID() const;                       // Get Vehicle ID
    std::string getCarInfo() const;          // Get car details as a string
    double getCostPerDay() const;            // Get cost per day of rental

    // Pure virtual method (abstract class)
    virtual void displayInfo() const = 0;

    // Virtual destructor
    virtual ~Vehicle() {}
};

#endif
