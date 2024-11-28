#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

// Forward declare EventLogger
class EventLogger;

class Vehicle {
protected:
    int id;
    std::string make;
    std::string model;
    int year;
    std::string color;
    double costPerDay;  // Cost per day of renting the car

    // Declare EventLogger as a FRIEND class
    friend class EventLogger;

public:
    // Constructor
    Vehicle(int id, const std::string& make, const std::string& model, int year, const std::string& color, double costPerDay);

    // Getters and Setters
    int getID() const;
    std::string getCarInfo() const;
    double getCostPerDay() const; // Getter for costPerDay

    // Abstract method for availability (to be overridden in Car class)
    virtual bool getAvailability() const = 0;
    virtual void setAvailability(bool availability) = 0;
    virtual void displayInfo() const = 0;
    virtual double calculateRentalCost(int rentalDuration) = 0;
    virtual void displayCarInfo() const = 0;
    virtual void displayCarInfo(bool includeCostAndAvailability) const = 0;
};

#endif
