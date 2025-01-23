#include "Customer.h"
#include <iostream>

// Constructor for the Customer class. It initializes the customer details
//and the details of the car they rented using the provided parameters.

Customer::Customer(const std::string& firstName, const std::string& lastName, const std::string& contactDetails,
    int rentalDuration, int carID, const std::string& carMake, const std::string& carModel)
    : firstName(firstName), lastName(lastName), contactDetails(contactDetails),
    rentalDuration(rentalDuration), rentedCarID(carID), rentedCarMake(carMake), rentedCarModel(carModel) {}

// Getter methods
int Customer::getRentedCarID() const {
    return rentedCarID;
}

std::string Customer::getRentedCarMake() const {
    return rentedCarMake;
}

std::string Customer::getRentedCarModel() const {
    return rentedCarModel;
}

// Display customer details
void Customer::displayCustomerInfo() const {
    std::cout << "Car ID: " << rentedCarID << "\n"
        << "Car Details: " << rentedCarMake << " " << rentedCarModel << "\n"
        << "Customer Name: " << firstName << " " << lastName << "\n"
        << "Contact Details: " << contactDetails << "\n"
        << "Rental Duration: " << rentalDuration << " days\n";
}

// Friend function implementation
void displayCustomerAndCarDetails(const Customer& customer) {
    std::cout << "[Friend Function Access] Customer Name: " << customer.firstName << " " << customer.lastName << "\n";
    std::cout << "Rented Car: " << customer.rentedCarMake << " " << customer.rentedCarModel << " (ID: " << customer.rentedCarID << ")\n";
    std::cout << "Rental Duration: " << customer.rentalDuration << " days\n";
}
