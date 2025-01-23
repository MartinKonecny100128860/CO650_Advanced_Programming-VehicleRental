#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

// Forward declaration of the friend function
class Customer;

// Declare the friend function
void displayCustomerAndCarDetails(const Customer& customer);

class Customer {
    // ENCAPSULATION. Encapsulated attributes ensuring that sensitive 
    //data is not directly accessible, maintaining encapsulation.
private:
    std::string firstName;
    std::string lastName;
    std::string contactDetails;
    int rentalDuration; // Number of days the car is rented for

    // Attributes to store booked car details
    int rentedCarID;
    std::string rentedCarMake;
    std::string rentedCarModel;

public:
    // Constructor
    Customer(const std::string& firstName, const std::string& lastName, const std::string& contactDetails,
        int rentalDuration, int carID = -1, const std::string& carMake = "", const std::string& carModel = "");

    // Getter methods for rented car details
    int getRentedCarID() const;
    std::string getRentedCarMake() const;
    std::string getRentedCarModel() const;

    // Display customer details
    void displayCustomerInfo() const;

    // Add getter methods for customer attributes
    std::string getFirstName() const { return firstName; }
    std::string getLastName() const { return lastName; }
    std::string getContactDetails() const { return contactDetails; }
    int getRentalDuration() const { return rentalDuration; }

    // Declare friend function
    friend void displayCustomerAndCarDetails(const Customer& customer);
};

#endif
