#include "Customer.h"
#include <iostream>

// Updated constructor to include car details
Customer::Customer(const std::string& firstName, const std::string& lastName, const std::string& contactDetails,
    int rentalDuration, int carID, const std::string& carMake, const std::string& carModel)
    : firstName(firstName), lastName(lastName), contactDetails(contactDetails), rentalDuration(rentalDuration),
    carID(carID), carMake(carMake), carModel(carModel) {}

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
    std::cout << "Car ID: " << carID << "\n"
        << "Car Details: " << carMake << " " << carModel << "\n"
        << "Customer Name: " << firstName << " " << lastName << "\n"
        << "Contact Details: " << contactDetails << "\n"
        << "Rental Duration: " << rentalDuration << " days\n";
}