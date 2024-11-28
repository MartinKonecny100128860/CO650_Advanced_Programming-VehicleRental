#ifndef MOTORCYCLE_H
#define MOTORCYCLE_H

#include "Vehicle.h"

class Motorcycle : public Vehicle {
private:
    int id;
    std::string make;
    std::string model;
    int year;
    double engineCapacity;

public:
    Motorcycle(int id, const std::string& make, const std::string& model, int year, double engineCapacity);

    void displayVehicleInfo() const override;  // Polymorphic method

    // Overloaded methods
    void displayVehicleInfo(const std::string& additionalInfo) const override;
    void displayVehicleInfo(int engineSize) const;
};

#endif
