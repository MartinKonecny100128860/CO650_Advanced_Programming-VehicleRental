#include <iostream>
#include <locale>
#include <vector>
#include <string>
#include "Car.h"
#include "Customer.h"
#include "EventLogger.h"
#include "ServerLogger.h"
#include <stdexcept>
#include <algorithm>
#include <fstream>
#include <limits>
#include <iomanip>

EventLogger logger("event_log.txt");

std::vector<Customer*> users;
std::vector<Vehicle*> vehicles;
std::vector<Car*> car;

void loadCarsFromFile() {
    std::ifstream carFile("cars.txt");
    if (carFile.is_open()) {
        int id, year;
        std::string make, model, color;
        double costPerDay;

        while (carFile >> id) {
            carFile.ignore();  
            std::getline(carFile, make, ','); 
            std::getline(carFile, model, ',');
            carFile >> year;
            carFile.ignore();
            std::getline(carFile, color, ',');
            carFile >> costPerDay;

            try {
                if (costPerDay <= 0) {
                    throw std::invalid_argument("Invalid cost per day in file.");
                }
                if (year < 1886 || year > 2100) {
                    throw std::invalid_argument("Invalid year in file.");
                }

                Car* loadedCar = new Car(id, make, model, year, color, costPerDay);
                vehicles.push_back(loadedCar);
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Error loading car from file: " << e.what() << "\n";
            }
        }
        carFile.close();
    }
    else {
        std::cerr << "Error opening cars.txt.\n";
    }
}

void saveUsersToFile() {
    std::ofstream userFile("users.txt");
    if (userFile.is_open()) {
        for (const auto& user : users) {
            userFile << user->getFirstName() << ","
                << user->getLastName() << ","
                << user->getContactDetails() << ","
                << user->getRentalDuration() << ","
                << user->getRentedCarID() << ","
                << user->getRentedCarMake() << ","
                << user->getRentedCarModel() << "\n";
        }
        userFile.close();
    }
    else {
        std::cerr << "Error saving users to file.\n";
    }
}

void loadUsersFromFile() {
    std::ifstream userFile("users.txt");
    if (userFile.is_open()) {
        std::string firstName, lastName, contactDetails, make, model;
        int rentalDuration, carID;

        while (std::getline(userFile, firstName, ',')) {
            std::getline(userFile, lastName, ',');
            std::getline(userFile, contactDetails, ',');
            userFile >> rentalDuration;
            userFile.ignore();
            userFile >> carID;
            userFile.ignore();
            std::getline(userFile, make, ',');
            std::getline(userFile, model);

            Customer* loadedUser = new Customer(firstName, lastName, contactDetails, rentalDuration, carID, make, model);
            users.push_back(loadedUser);

            for (auto& vehicle : vehicles) {
                Car* car = dynamic_cast<Car*>(vehicle);
                if (car && car->getCarID() == carID) {
                    car->setAvailability(false);
                    break;
                }
            }
        }
        userFile.close();
    }
    else {
        std::cerr << "Error loading users from file.\n";
    }
}

bool login() {
    std::string username, password;
    const std::string correctUsername = "admin";
    const std::string correctPassword = "password";

    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    if (username == correctUsername && password == correctPassword) {
        return true;
    }
    else {
        std::cout << "Invalid username or password. Please try again.\n";
        return false;
    }
}

void addDefaultCars() {
    vehicles.push_back(new Car(1, "Nissan", "Skyline R34 GT-R V-Spec II", 2001, "Blue", 1200.00));
    vehicles.push_back(new Car(2, "Toyota", "Supra MK4 TT6 Single Turbo", 1997, "White", 700.00));
    vehicles.push_back(new Car(3, "Honda", "NSX NA1", 1991, "Red", 800.00));
    vehicles.push_back(new Car(4, "Mazda", "RX7", 2000, "Silver with Fortune Body Kit", 1000.00));
    vehicles.push_back(new Car(5, "Mitsubishi", "Lancer Evo", 2001, "White", 600.00));
    vehicles.push_back(new Car(6, "Nissan", "200SX", 1996, "Orange", 1000.00));
}

void viewVehicles() {
    for (auto vehicle : vehicles) {
        vehicle->displayInfo();
    }
}

void viewUsers() {
    std::cout << "\n--- Registered Users ---\n";
    for (const auto& user : users) {
        user->displayCustomerInfo();
    }
}

void rentCar() {
    std::cout << "Enter the car ID to rent: ";
    int carID;
    std::cin >> carID;

    for (auto& vehicle : vehicles) {
        Car* car = dynamic_cast<Car*>(vehicle);
        if (car && car->getCarID() == carID && car->getAvailability()) {
            std::string firstName, lastName, contactDetails;
            int rentalDuration;

            std::cout << "Enter customer's first name: ";
            std::cin >> firstName;
            std::cout << "Enter customer's last name: ";
            std::cin >> lastName;
            std::cout << "Enter customer's contact details: ";
            std::cin.ignore();
            std::getline(std::cin, contactDetails);
            std::cout << "Enter rental duration in days: ";
            std::cin >> rentalDuration;

            Customer* customer = new Customer(firstName, lastName, contactDetails, rentalDuration,
                car->getCarID(), car->getMake(), car->getModel());
            users.push_back(customer);

            double totalCost = car->calculateRentalCost(rentalDuration);
            std::cout << "Total rental cost for " << rentalDuration << " days: $" << totalCost << "\n";

            car->setAvailability(false);
            EventLogger::log("Rented car: " + car->getMake() + " " + car->getModel() + " to " + firstName + " " + lastName);
            saveUsersToFile();
            std::cout << "Car rented successfully!\n";

            // Send message to the server
            ServerLogger logger;
            if (logger.connectToServer("127.0.0.1", 5000)) {  // Connect to the server (use your server's IP and port)
                std::string message = "Car ID " + std::to_string(carID) + " rented to " + firstName + " " + lastName;
                logger.log(message);  // Log the rental message to the server
            }

            return;
        }
    }
    std::cout << "Car with ID " << carID << " not available for rent.\n";
}

#include <iostream>
#include <limits> // Ensure this header is included for std::numeric_limits

void addCar() {
    std::string make, model, color;
    int year;
    double costPerDay;

    std::cout << "Enter car make: ";
    std::cin >> make;
    if (make.empty()) {
        std::cerr << "Car make cannot be empty!\n";
        return;
    }

    std::cout << "Enter car model: ";
    std::cin >> model;
    if (model.empty()) {
        std::cerr << "Car model cannot be empty!\n";
        return;
    }

    std::cout << "Enter car year: ";
    std::cin >> year;
    if (std::cin.fail() || year < 1886 || year > 2100) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');  // Ignore up to 10,000 characters
        std::cerr << "Invalid year entered. Please enter a valid year (e.g., 1998).\n";
        return;
    }

    std::cout << "Enter car color: ";
    std::cin.ignore();  // Clear the leftover newline
    std::getline(std::cin, color);
    if (color.empty()) {
        std::cerr << "Car color cannot be empty!\n";
        return;
    }

    std::cout << "Enter cost per day (£): ";
    std::cin >> costPerDay;
    if (std::cin.fail() || costPerDay <= 0) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');  // Ignore up to 10,000 characters
        std::cerr << "Invalid cost per day. Please enter a positive number.\n";
        return;
    }

    int newID = vehicles.size() + 1;

    try {
        Car* newCar = new Car(newID, make, model, year, color, costPerDay);
        vehicles.push_back(newCar);

        EventLogger::log("Added car: " + newCar->getMake() + " " + newCar->getModel());

        std::vector<Car> cars;
        for (auto& vehicle : vehicles) {
            Car* car = dynamic_cast<Car*>(vehicle);
            if (car) {
                cars.push_back(*car);
            }
        }

        Car::saveCarsToFile(cars, "cars.txt");

        std::cout << "Car added successfully!\n";
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}


void deleteCar() {
    std::cout << "Enter the car ID to delete: ";
    int carID;
    std::cin >> carID;

    for (auto it = vehicles.begin(); it != vehicles.end(); ++it) {
        Car* car = dynamic_cast<Car*>(*it);
        if (car && car->getCarID() == carID) {
            EventLogger::log("Deleted car: " + car->getMake() + " " + car->getModel());
            delete car;
            vehicles.erase(it);

            std::vector<Car> cars;
            for (auto& vehicle : vehicles) {
                Car* car = dynamic_cast<Car*>(vehicle);
                if (car) {
                    cars.push_back(*car);
                }
            }

            Car::saveCarsToFile(cars, "cars.txt");
            std::cout << "Car deleted successfully.\n";
            return;
        }
    }
    std::cout << "Car with ID " << carID << " not found.\n";
}

void returnCar() {
    std::cout << "Enter the car ID to return: ";
    int carID;
    std::cin >> carID;

    // Find the customer who rented the car
    auto customerIt = std::find_if(users.begin(), users.end(), [carID](Customer* user) {
        return user->getRentedCarID() == carID;
        });

    if (customerIt != users.end()) {
        // Retrieve the customer's first name and last name
        std::string firstName = (*customerIt)->getFirstName();
        std::string lastName = (*customerIt)->getLastName();

        // Concatenate first name and last name to get the full customer name
        std::string customerName = firstName + " " + lastName;

        // Find and return the car
        for (auto& vehicle : vehicles) {
            Car* car = dynamic_cast<Car*>(vehicle);
            if (car && car->getCarID() == carID) {
                car->setAvailability(true);  // Mark car as available
                std::cout << "Car with ID " << carID << " has been returned and is available to be rented again.\n";
                break;
            }
        }

        // Remove the customer and rental information
        users.erase(customerIt);
        std::cout << "Customer " << customerName << " and rental information removed from records.\n";

        // Save updated records
        saveUsersToFile();

        // Log the return event with customer name
        EventLogger::log("Returned car with ID: " + std::to_string(carID) + " by customer: " + customerName);

        // Send message to the server with customer name and car ID
        ServerLogger logger;
        if (logger.connectToServer("127.0.0.1", 5000)) {  // Connect to the server (use your server's IP and port)
            logger.log("Car ID " + std::to_string(carID) + " returned by " + customerName);
        }
    }
    else {
        std::cout << "No rental found for car ID " << carID << ".\n";
    }
}


// Initialize the ServerLogger instance
ServerLogger serverLogger;



using MenuAction = void(*)();

void displayMenu() {
    int choice;

    MenuAction menuActions[] = {
        viewVehicles, 
        rentCar,     
        addCar,      
        deleteCar,   
        viewUsers,  
        returnCar 
    };

    do {
        std::cout << "\n=====================================\n";
        std::cout << "          --- Main Menu ---          \n";
        std::cout << "=====================================\n";
        std::cout << "  1. View All Cars                 \n";
        std::cout << "  2. Rent a Car                    \n";
        std::cout << "  3. Add a Car                     \n";
        std::cout << "  4. Delete a Car                  \n";  
        std::cout << "  5. View Users                    \n";
        std::cout << "  6. Return a Car                  \n"; 
        std::cout << "  7. Exit                          \n";
        std::cout << "=====================================\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice >= 1 && choice <= 6) {
            menuActions[choice - 1]();
        }
        else if (choice == 7) {
            std::cout << "Exiting the program.\n";
            break;
        }
        else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (true);
}

int main() {
    std::cout << "Welcome to the Vehicle Rental System!\n";
    std::cout << "-------------------------------------\n";

    if (!login()) {
        std::cerr << "Login failed! Exiting...\n";
        return 1;
    }

    // Connect to the server before renting or returning cars
    ServerLogger serverLogger;
    if (!serverLogger.connectToServer("127.0.0.1", 5000)) {
        std::cerr << "Failed to connect to server." << std::endl;
        return 1;
    }

    // Load cars and users
    loadCarsFromFile();
    loadUsersFromFile();

    if (vehicles.empty()) {
        addDefaultCars();  // Add default cars if no cars exist
    }

    displayMenu();  // Display menu for further interactions

    // Cleanup dynamic memory allocations
    for (auto user : users) delete user;
    for (auto vehicle : vehicles) delete vehicle;

    return 0;
}
