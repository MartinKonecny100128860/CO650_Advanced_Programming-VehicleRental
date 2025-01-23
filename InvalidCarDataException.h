#ifndef INVALIDCARDATAEXCEPTION_H
#define INVALIDCARDATAEXCEPTION_H

#include <exception>
#include <string>

#include <exception>
#include <string>

// Base exception class for car-related exceptions
class CarException : public std::exception {
protected:
    std::string message;

public:
    explicit CarException(const std::string& msg) : message(msg) {}

    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

// Exception Handling using Exception Classes (Inheriting from Exception
class InvalidCarMakeException : public CarException {
public:
    InvalidCarMakeException() : CarException("Car make cannot be empty!") {}
};

class InvalidCarModelException : public CarException {
public:
    InvalidCarModelException() : CarException("Car model cannot be empty!") {}
};

class InvalidCarYearException : public CarException {
public:
    InvalidCarYearException() : CarException("Invalid year entered. Please enter a valid year (e.g., 1998).") {}
};

class InvalidCarColorException : public CarException {
public:
    InvalidCarColorException() : CarException("Car color cannot be empty!") {}
};

class InvalidCarCostException : public CarException {
public:
    InvalidCarCostException() : CarException("Invalid cost per day. Please enter a positive number.") {}
};


#endif



