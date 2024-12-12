#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

class Customer {
private:
    std::string firstName;
    std::string lastName;
    std::string contactDetails;
    int rentalDuration;

    // New attributes to store booked car details
    int carID;
    std::string carMake;
    std::string carModel;

public:
    // Updated constructor to include car details
    Customer(const std::string& firstName, const std::string& lastName, const std::string& contactDetails,
        int rentalDuration, int carID, const std::string& carMake, const std::string& carModel);

    // Display customer details
    void displayCustomerInfo() const;

    // Add these to Customer.h
    std::string getFirstName() const { return firstName; }
    std::string getLastName() const { return lastName; }
};

#endif

