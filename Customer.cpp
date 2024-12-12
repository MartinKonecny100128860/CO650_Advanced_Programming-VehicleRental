#include "Customer.h"
#include <iostream>

Customer::Customer(const std::string& firstName, const std::string& lastName, const std::string& contactDetails,
    int rentalDuration, int carID, const std::string& carMake, const std::string& carModel)
    : firstName(firstName), lastName(lastName), contactDetails(contactDetails),
    rentalDuration(rentalDuration), rentedCarID(carID), rentedCarMake(carMake), rentedCarModel(carModel) {}


// Getter methods for rented car details
int Customer::getRentedCarID() const {
    return rentedCarID;
}

std::string Customer::getRentedCarMake() const {
    return rentedCarMake;
}

std::string Customer::getRentedCarModel() const {
    return rentedCarModel;
}

// Method to display customer details, including booked car details
void Customer::displayCustomerInfo() const {
    std::cout << "Car ID: " << rentedCarID << "\n"
        << "Car Details: " << rentedCarMake << " " << rentedCarModel << "\n"
        << "Customer Name: " << firstName << " " << lastName << "\n"
        << "Contact Details: " << contactDetails << "\n"
        << "Rental Duration: " << rentalDuration << " days\n";
}
