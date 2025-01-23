#ifndef INVALIDCARDATAEXCEPTION_H
#define INVALIDCARDATAEXCEPTION_H

#include <exception>
#include <string>

// Base exception class for car-related exceptions
// This class provides a generic structure for handling car-related errors.
// It inherits from std::exception and stores an error message.
class CarException : public std::exception {
protected:
    std::string message;  // Stores the error message

public:
    // Constructor to initialize the error message
    explicit CarException(const std::string& msg) : message(msg) {}

    // Override the what() function to return the error message
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

// Specific exception classes for various types of car-related errors
// Each exception class inherits from CarException and defines a specific error message.

class InvalidCarMakeException : public CarException {
public:
    // Thrown when the car make is empty
    InvalidCarMakeException() : CarException("Car make cannot be empty!") {}
};

class InvalidCarModelException : public CarException {
public:
    // Thrown when the car model is empty
    InvalidCarModelException() : CarException("Car model cannot be empty!") {}
};

class InvalidCarYearException : public CarException {
public:
    // Thrown when the car year is invalid (e.g., outside the valid range)
    InvalidCarYearException() : CarException("Invalid year entered. Please enter a valid year (e.g., 1998).") {}
};

class InvalidCarColorException : public CarException {
public:
    // Thrown when the car color is empty
    InvalidCarColorException() : CarException("Car color cannot be empty!") {}
};

class InvalidCarCostException : public CarException {
public:
    // Thrown when the cost per day is invalid (e.g., non-positive value)
    InvalidCarCostException() : CarException("Invalid cost per day. Please enter a positive number.") {}
};

#endif
