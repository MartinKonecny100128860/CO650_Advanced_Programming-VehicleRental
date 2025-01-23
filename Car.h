#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <sstream>

// Forward declaration of the friend function
class Car;
void displayCarDetails(const Car& car);

// Inheritance: Vehicle is the base class, and Car is a derived class
class Car : public Vehicle { // INHERITANCE: Car class inherits from the Vehicle class
private:
    int id;              // Unique ID for the car
    std::string color;   // Color of the car
    int year;            // Year of manufacture
    bool available;      // Availability status
    bool isRented;       // Rental status

public:
    // Constructor
    Car(int id, const std::string& make, const std::string& model, int year, const std::string& color, double costPerDay);

    // Getter and Setter methods
    int getCarID() const { return id; }
    std::string getColor() const { return color; }
    int getYear() const { return year; }

    void setAvailability(bool availability);
    bool getAvailability() const;
    void setIsRented(bool rented);
    bool getIsRented() const;

    std::string getMake() const;
    std::string getModel() const;

    // OVERLOADING calculateRentalCost function by providing a default rental duration:
    double calculateRentalCost(int days = 1) const;

    // Overriding displayInfo from Vehicle
    void displayInfo() const override;

    // Friend function (for external access to private members)
    friend void displayCarDetails(const Car& car);

    // Static file operations (unchanged)
    static void saveCarsToFile(const std::vector<Car>& cars, const std::string& filename);
    static void loadCarsFromFile(std::vector<Car>& cars, const std::string& filename);
    static void saveRentalData(const std::vector<Car>& cars, const std::string& filename);
    static void loadRentalData(std::vector<Car>& cars, const std::string& filename);
};

#endif
