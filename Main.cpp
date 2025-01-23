#include <iostream>
#include <locale>
#include <vector>
#include <string>
#include "Car.h"
#include "Customer.h"
#include "InvalidCarDataException.h"
#include "EventLogger.h"
#include "ServerLogger.h"
#include <stdexcept>
#include <algorithm>
#include <fstream>
#include <limits>
#include <iomanip>
#include <cstdlib> 

EventLogger logger("event_log.txt");

std::vector<Customer*> users;    // Pointer to Customer objects
std::vector<Vehicle*> vehicles;  // Pointer to Vehicle objects
std::vector<Car*> car;           // Pointer to Car objects

void saveCarsToFile() {
    std::ofstream carFile("cars.txt", std::ios::trunc);  // Open file in overwrite mode
    if (carFile.is_open()) {
        for (const auto& vehicle : vehicles) {
            Car* car = dynamic_cast<Car*>(vehicle);
            if (car) {
                carFile << car->getCarID() << ","
                    << car->getMake() << ","
                    << car->getModel() << ","
                    << car->getYear() << ","
                    << car->getColor() << ","
                    << car->getCostPerDay() << "\n";
            }
        }
        carFile.close();
    }
    else {
        std::cerr << "Error saving cars to file.\n";
    }
}

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
    int attempts = 0;
    const int maxAttempts = 3;

    while (attempts < maxAttempts) {
        std::cout << "Enter username: ";
        std::cin >> username;
        std::cout << "Enter password: ";
        std::cin >> password;

        if (username == correctUsername && password == correctPassword) {
            return true;
        }
        else {
            attempts++;
            if (attempts < maxAttempts) {
                std::cout << "Invalid username or password. Please try again.\n";
            }
        }
    }

    std::cout << "Maximum login attempts reached. Program will now exit.\n";
    std::exit(EXIT_FAILURE);  // Terminates the program
}

void addDefaultCars() {
    vehicles.push_back(new Car(1, "Nissan", "Skyline R34 GT-R V-Spec II", 2001, "Blue", 1200.00));
    vehicles.push_back(new Car(2, "Toyota", "Supra MK4 TT6 Single Turbo", 1997, "White", 700.00));
    vehicles.push_back(new Car(3, "Honda", "NSX NA1", 1991, "Red", 800.00));
    vehicles.push_back(new Car(4, "Mazda", "RX7 Fortune Body Kit", 2000, "Silver", 1000.00));
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

// Function to handle the rental process for a car
void rentCar() {
    // Prompt user to input the car ID they want to rent
    std::cout << "Enter the car ID to rent: ";
    int carID;
    std::cin >> carID;

    // Iterate over the list of vehicles to find the specified car
    for (auto& vehicle : vehicles) {
        // Try to cast the vehicle pointer to a Car pointer
        Car* car = dynamic_cast<Car*>(vehicle);

        // Check if the car is the correct one and is available for rent
        if (car && car->getCarID() == carID && car->getAvailability()) {
            // Collect customer information
            std::string firstName, lastName, contactDetails;
            int rentalDuration;

            std::cout << "Enter customer's first name: ";
            std::cin >> firstName;
            std::cout << "Enter customer's last name: ";
            std::cin >> lastName;
            std::cout << "Enter customer's contact details: ";
            std::cin.ignore(); // Clear the input buffer
            std::getline(std::cin, contactDetails);
            std::cout << "Enter rental duration in days: ";
            std::cin >> rentalDuration;

            // Create a new customer object and add to the list of users
            Customer* customer = new Customer(firstName, lastName, contactDetails, rentalDuration,
                car->getCarID(), car->getMake(), car->getModel());
            users.push_back(customer);

            // Calculate and display the total rental cost
            double totalCost = car->calculateRentalCost(rentalDuration);
            std::cout << "Total rental cost for " << rentalDuration << " days: $" << totalCost << "\n";

            // Mark the car as unavailable
            car->setAvailability(false);

            // Log the rental event
            EventLogger::log("Rented car: " + car->getMake() + " " + car->getModel() + " to " + firstName + " " + lastName);
            saveUsersToFile(); // Save user data to file
            std::cout << "Car rented successfully!\n";

            // Log the rental details to the server if connection is successful
            ServerLogger logger;
            if (logger.connectToServer("127.0.0.1", 5000)) { // Connect to the server using IP and port
                std::string message = "Car ID " + std::to_string(carID) + " rented to " + firstName + " " + lastName;
                logger.log(message); // Send the message to the server
            }

            return; // Exit the function once the car is rented
        }
    }
    // If no available car is found, inform the user
    std::cout << "Car with ID " << carID << " not available for rent.\n";
}


void addCar() {
    std::string make, model, color;
    int year;
    double costPerDay;

    try {
        std::cout << "Enter car make: ";
        std::cin >> make;
        if (make.empty()) {
            throw InvalidCarMakeException();
        }

        std::cout << "Enter car model: ";
        std::cin >> model;
        if (model.empty()) {
            throw InvalidCarModelException();
        }

        std::cout << "Enter car year: ";
        std::cin >> year;
        if (std::cin.fail() || year < 1886 || year > 2100) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            throw InvalidCarYearException();
        }

        std::cout << "Enter car color: ";
        std::cin.ignore();  // Clear the leftover newline
        std::getline(std::cin, color);
        if (color.empty()) {
            throw InvalidCarColorException();
        }

        std::cout << "Enter cost per day (£): ";
        std::cin >> costPerDay;
        if (std::cin.fail() || costPerDay <= 0) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            throw InvalidCarCostException();
        }

        // Generate a new ID based on the current size of the vehicle vector
        int newID = vehicles.size() + 1;

        // Create the new car object and add it to the vehicles list
        Car* newCar = new Car(newID, make, model, year, color, costPerDay);
        vehicles.push_back(newCar);

        EventLogger::log("Added car: " + newCar->getMake() + " " + newCar->getModel());

        // Save all cars to the file, overwriting the existing data
        std::ofstream carFile("cars.txt", std::ofstream::trunc);  // Open file in truncate mode to overwrite
        if (carFile.is_open()) {
            for (auto& vehicle : vehicles) {
                Car* car = dynamic_cast<Car*>(vehicle);
                if (car) {
                    carFile << car->getCarID() << ","
                        << car->getMake() << ","
                        << car->getModel() << ","
                        << car->getYear() << ","
                        << car->getColor() << ","
                        << car->getCostPerDay() << "\n";
                }
            }
            carFile.close();
            std::cout << "Car added and file updated successfully!\n";
        }
        else {
            std::cerr << "Error opening cars.txt for writing.\n";
        }
    }
    catch (const CarException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }
}


void deleteCar() {
    std::cout << "Enter the car ID to delete: ";
    int carID;
    std::cin >> carID;

    bool carDeleted = false;  // To track if a car was deleted
    std::vector<Car*> carsToDelete;  // Vector to hold cars to delete

    // Iterate over vehicles and find the car to delete
    for (auto it = vehicles.begin(); it != vehicles.end();) {
        Car* car = dynamic_cast<Car*>(*it);
        if (car && car->getCarID() == carID) {
            EventLogger::log("Deleted car: " + car->getMake() + " " + car->getModel());
            carsToDelete.push_back(car); // Mark car for deletion
            it = vehicles.erase(it); // Remove car from vector
            carDeleted = true;
        }
        else {
            ++it;  // Move iterator forward only if no deletion occurred
        }
    }

    // If car was deleted, clean up memory and update file
    if (carDeleted) {
        // Delete cars from memory
        for (Car* car : carsToDelete) {
            delete car;
        }
        // Save the remaining cars to the file
        std::vector<Car> updatedCars;
        for (auto& vehicle : vehicles) {
            Car* car = dynamic_cast<Car*>(vehicle);
            if (car) {
                updatedCars.push_back(*car);  // Add to updated list
            }
        }
        Car::saveCarsToFile(updatedCars, "cars.txt");
        std::cout << "Car deleted successfully.\n";
    }
    else {
        std::cout << "Car with ID " << carID << " not found.\n";
    }
}


// Function declaration to return a rented car and mark it as available again
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
    // error message if wrong ID is typed in
    else {
        std::cout << "No rental found for car ID " << carID << ".\n";
    }
}


// Initialise the ServerLogger instance
ServerLogger serverLogger;



using MenuAction = void(*)(); // Defining a functional pointer type named 'MenuAction'

void displayMenu() {
    int choice;

    // Array of function pointers of type MenuAction, pointing to different menu functions
    MenuAction menuActions[] = {
        viewVehicles, // Function pointer to viewVehicles
        rentCar,      // Function pointer to rentCar
        addCar,       // Function pointer to addCar
        deleteCar,    // Function pointer to deleteCar
        viewUsers,    // Function pointer to viewUsers
        returnCar     // Function pointer to returnCar
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

        // If the user selects a valid menu option, call the corresponding function using the function pointer array
        if (choice >= 1 && choice <= 6) {
            menuActions[choice - 1](); // Calling the function through the function pointer array
        }
        else if (choice == 7) {
            std::cout << "Exiting the program.\n";
            break;
        }
        else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (true); // Keep displaying the menu until a valid exit option is selected
}


int main() {
    std::cout << "Welcome to the Vehicle Rental System!\n";
    std::cout << "-------------------------------------\n";

    if (login()) {
        std::cout << "Login successful!\n";
        // Continue with the rest of your program...
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
