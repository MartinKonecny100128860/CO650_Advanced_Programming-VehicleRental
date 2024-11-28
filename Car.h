#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"
#include <iostream>

class Car : public Vehicle {
private:
    bool available;

public:
    // Constructor
    Car(int id, const std::string& make, const std::string& model, int year, const std::string& color, double costPerDay);

    // Overriding methods from Vehicle
    bool getAvailability() const override;
    void setAvailability(bool availability) override;
    void displayInfo() const override;
    double calculateRentalCost(int rentalDuration) override;
    // Overloaded displayCarInfo methods
  void displayCarInfo() const override;  // Basic info
  void displayCarInfo(bool includeCostAndAvailability) const override;  // Detailed info with cost and availability
};

#endif
