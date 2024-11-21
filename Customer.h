#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

class Customer {
private:
    std::string firstName;
    std::string lastName;
    std::string contactDetails;
    int rentalDuration;

public:
    // Constructor
    Customer(const std::string& firstName, const std::string& lastName, const std::string& contactDetails, int rentalDuration);

    // Display customer details
    void displayCustomerInfo() const;
};

#endif
