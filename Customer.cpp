#include "Customer.h"
#include <iostream>

// Constructor
Customer::Customer(const std::string& firstName, const std::string& lastName, const std::string& contactDetails, int rentalDuration)
    : firstName(firstName), lastName(lastName), contactDetails(contactDetails), rentalDuration(rentalDuration) {}

// Method to display customer details
void Customer::displayCustomerInfo() const {
    std::cout << "Customer Name: " << firstName << " " << lastName << "\n"
        << "Contact Details: " << contactDetails << "\n"
        << "Rental Duration: " << rentalDuration << " days\n";
}
