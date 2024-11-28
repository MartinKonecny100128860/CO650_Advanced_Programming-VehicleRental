#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <iostream>

class Vehicle {
public:
    virtual ~Vehicle() {}  // Virtual destructor

    // Polymorphic method (overloaded)
    virtual void displayVehicleInfo() const = 0;  // Pure virtual function (overridden in derived classes)

    // Overloaded method
    virtual void displayVehicleInfo(const std::string& additionalInfo) const {
        std::cout << "Additional Info: " << additionalInfo << std::endl;
    }
};

#endif
