#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"

class Car : public Vehicle {
private:
    bool available;

public:
    // Constructor for the Car class
    Car(int id, const std::string& make, const std::string& model, int year, const std::string& color, double costPerDay);

    // Getter and Setter for availability
    bool getAvailability() const;
    void setAvailability(bool availability);

    // Overridden method for displaying information about the car
    void displayCarInfo(bool includeCostAndAvailability) const override;

    // Overridden method for displaying more detailed info about the car
    void displayInfo() const override;  // Polymorphic behavior

    // Custom method to calculate rental cost
    double calculateRentalCost(int rentalDuration);
};

#endif
