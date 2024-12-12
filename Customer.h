#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

class Customer {
private:
    std::string firstName;
    std::string lastName;
    std::string contactDetails;
    int rentalDuration; // Number of days the car is rented for

    // New attributes to store booked car details
    int carID;
    std::string carMake;
    std::string carModel;

    int rentedCarID;
    std::string rentedCarMake;
    std::string rentedCarModel;

public:
    // Updated constructor to include car details
    Customer(const std::string& firstName, const std::string& lastName, const std::string& contactDetails,
        int rentalDuration, int carID, const std::string& carMake, const std::string& carModel);

    // Display customer details
    void displayCustomerInfo() const;

    // Add these to Customer.h
    std::string getFirstName() const { return firstName; }
    std::string getLastName() const { return lastName; }
    std::string getContactDetails() const { return contactDetails; }
    int getRentalDuration() const { return rentalDuration; }
    int getRentedCarID() const;
    std::string getRentedCarMake() const;
    std::string getRentedCarModel() const;
};

#endif
