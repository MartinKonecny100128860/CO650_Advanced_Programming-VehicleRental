#ifndef CAR_H
#define CAR_H

#include <string>

class Car {
private:
    int id;
    std::string make;
    std::string model;
    int year;
    std::string color;
    double costPerDay;
    bool available;

public:
    // Constructor
    Car(int id, const std::string& make, const std::string& model, int year, const std::string& color, double costPerDay);

    // Getters
    int getId() const;
    std::string getMake() const;
    std::string getModel() const;
    int getYear() const;
    std::string getColor() const;
    double getCostPerDay() const;
    bool isAvailable() const;

    // Setters
    void setAvailable(bool availability);

    // Display car details
    void displayCarDetails() const;
};

#endif // CAR_H
