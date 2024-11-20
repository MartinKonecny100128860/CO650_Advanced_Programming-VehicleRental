#ifndef CAR_H
#define CAR_H

#include <string>
#include <iostream>

// Forward declare EventLogger
class EventLogger;

class Car {
private:
    int id;
    std::string make;
    std::string model;
    int year;
    std::string color;
    double costPerDay;  // Cost per day of renting the car
    bool available;

    // Declare EventLogger as a FRIEND class
    friend class EventLogger;

public:
    // Constructor
    Car(int id, const std::string& make, const std::string& model, int year, const std::string& color, double costPerDay);

    // Getters and Setters
    bool getAvailability() const;
    void setAvailability(bool availability);

    // Get car details
    int getID() const;
    std::string getCarInfo() const;
    double calculateRentalCost(int rentalDuration) const;

    // Method to display car details
    void displayCarInfo() const;
};

#endif