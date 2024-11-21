#ifndef INVALIDCARDATAEXCEPTION_H
#define INVALIDCARDATAEXCEPTION_H

#include <exception>
#include <string>

// Custom exception class inheriting from std::exception
class InvalidCarDataException : public std::exception {
private:
    std::string errorMessage; // Error message

public:
    // Constructor to initialize error message
    explicit InvalidCarDataException(const std::string& message)
        : errorMessage(message) {}

    // Override the what() method to provide the error message
    const char* what() const noexcept override {
        return errorMessage.c_str();
    }
};

#endif
