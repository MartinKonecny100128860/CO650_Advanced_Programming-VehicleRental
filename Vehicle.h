#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <iostream>
#include <stdexcept>


// Abstract base class
class Vehicle {

    protected:
        int id;                         // Unique ID for the car
        std::string make, model, color; // Basic vehicle attributes
        int year;                       // Year of mthe car
        double costPerDay;              // Cost per day of a car

    public:
        // Constructor to initialize the vehicle with make, model, year, and cost per day
        Vehicle(const std::string& make, const std::string& model, int year, double costPerDay);

        // Accessor methods that helps getting vehicle details 
        int getID() const;                // Get Vehicle ID
        std::string getCarInfo() const;   // Get car details as a string
        double getCostPerDay() const;     // Get cost per day of rental

        // ABSTRACTION - Pure virtual method that must be implemented by derived classes
        // POLYMORPHIC BEHAVIOUR - Enabling runtime method resolution through the virtual mechanism.
        virtual void displayInfo() const = 0;        // Display specific vehicle information

        // Virtual destructor to allow proper cleanup in derived classes (important for polymorphic use)
        virtual ~Vehicle() {}
};

#endif
