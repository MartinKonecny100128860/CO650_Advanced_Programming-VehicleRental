#include <iostream>
#include <locale> 
#include <vector>
#include <string>
#include "Car.h"
#include "Customer.h"
#include "EventLogger.h"
#include <stdexcept>
#include <algorithm> 

// Friendship is demonstarted here in the main class.
// Event logger takes information from car class.
// Then logs it in a text file. 
EventLogger logger("event_log.txt");


// Declare the list of cars and users (using pointers)
std::vector<Car*> cars;
std::vector<Customer*> users;

// Function to add default cars to the system
void addDefaultCars() {
    cars.push_back(new Car(1, "Nissan", "Skyline R34 GT-R V-Spec II", 2001, "Blue", 1200.00));
    cars.push_back(new Car(2, "Toyota", "Supra MK4 TT6 Single Turbo", 1997, "White", 700.00));
    cars.push_back(new Car(3, "Honda", "NSX NA1", 1991, "Red", 800.00));
    cars.push_back(new Car(4, "Mazda", "RX7", 2000, "Silver with Fortune Body Kit", 1000.00));
    cars.push_back(new Car(5, "Mitsubishi", "Lancer Evo", 2001, "White", 600.00));
    cars.push_back(new Car(6, "Mazda", "RX7", 2000, "Orange", 1000.00));
}

// Function to display all cars (using overloaded displayCarInfo)
void viewAllCars() {
    std::cout << "\n--- Available Cars ---\n";

    // Sort cars by ID in ascending order before displaying
    // POINTERS TO CAR OBJECTS ARE USED TO ACCESS THE DATA
    std::sort(cars.begin(), cars.end(), [](const Car* a, const Car* b) {
        return a->getID() < b->getID(); // Sorting by ID in ascending order
        });

    std::cout << "Number of cars in system: " << cars.size() << std::endl;
    for (const auto& car : cars) {
        // Use overloaded function to display detailed car info
        car->displayCarInfo(true);  // Pass 'true' to display cost and availability
    }
}


void rentCar() {
    std::cout << "Enter the car ID to rent: ";
    int carID;
    std::cin >> carID;

    bool carFound = false;
    for (auto& car : cars) {
        if (car->getID() == carID && car->getAvailability()) {
            carFound = true;
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

            Customer* customer = new Customer(firstName, lastName, contactDetails, rentalDuration);
            customer->displayCustomerInfo();
            double totalCost = car->calculateRentalCost(rentalDuration);
            std::cout << "Total rental cost for " << rentalDuration << " days: £" << totalCost << "\n";

            car->setAvailability(false);
            users.push_back(customer);

            // Log the rental event
            logger.logCarRental(*car, firstName + " " + lastName);

            std::cout << "\nCar rented successfully!\n";
            break;
        }
    }

    if (!carFound) {
        std::cout << "Car ID not found or car is not available.\n";
    }
}

void addCar() {
    std::string make, model, color;
    int year;
    double costPerDay;

    // Prompt for car details
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
    if (std::cin.fail() || year < 1886 || year > 2100) {  // Validate the year
        std::cin.clear(); // Clear the error state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        std::cerr << "Invalid year entered. Please enter a valid year (e.g., 1998).\n";
        return;
    }

    std::cout << "Enter car color: ";
    std::cin.ignore();  // Ignore leftover newline character
    std::getline(std::cin, color);
    if (color.empty()) {
        std::cerr << "Car color cannot be empty!\n";
        return;
    }

    std::cout << "Enter cost per day (£): ";
    std::cin >> costPerDay;
    if (std::cin.fail() || costPerDay <= 0) {  // Validate cost per day
        std::cin.clear(); // Clear the error state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        std::cerr << "Invalid cost per day. Please enter a positive number.\n";
        return;
    }

    // Generate a new ID based on the current number of cars
    int newID = cars.size() + 1;

    try {
        // Exception Handling: Catch any invalid arguments during car creation
        Car* newCar = new Car(newID, make, model, year, color, costPerDay);
        cars.push_back(newCar);

        // Log the car addition and save to file
        logger.logCarAddition(*newCar);
        logger.saveCarToFile(*newCar);

        std::cout << "Car added successfully!\n";
    }
    // Catch exceptions and display an error message
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

// Function to view all users
void viewUsers() {
    std::cout << "\n--- Registered Users ---\n";
    for (const auto& user : users) {
        user->displayCustomerInfo();
    }
}

// Function to handle login
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

#include <iostream>

// Define function pointers for the menu
void (*menuFunctions[])() = { viewAllCars, rentCar, addCar, viewUsers };

// Update the displayMenu function to use function pointers
void displayMenu() {
    int choice;
    do {
        std::cout << "\n--- Main Menu ---\n";
        std::cout << "1. View All Cars\n";
        std::cout << "2. Rent a Car\n";
        std::cout << "3. Add a Car\n";
        std::cout << "4. View Users\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice >= 1 && choice <= 4) {
            menuFunctions[choice - 1]();  // Call the corresponding function using the pointer
        }
        else if (choice == 5) {
            std::cout << "Exiting program.\n";
        }
        else {
            std::cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 5);
}


void loadCarsFromFile() {
    std::ifstream carFile("cars.txt");
    if (carFile.is_open()) {
        std::cout << "Opening cars.txt...\n";
        int id, year;
        std::string make, model, color;
        double costPerDay;

        while (carFile >> id) {
            carFile.ignore();  // Skip the comma before the make
            std::getline(carFile, make, ',');  // Read the car make
            std::getline(carFile, model, ',');  // Read the car model
            carFile >> year;
            carFile.ignore();  // Ignore the comma before color
            std::getline(carFile, color, ',');  // Read the car color
            carFile >> costPerDay;

            // Exception Handling: Throw if costPerDay or year is invalid
            try {
                if (costPerDay <= 0) {
                    throw std::invalid_argument("Invalid cost per day in file.");
                }
                if (year < 1886 || year > 2100) {
                    throw std::invalid_argument("Invalid year in file.");
                }

                Car* loadedCar = new Car(id, make, model, year, color, costPerDay);
                cars.push_back(loadedCar);
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Error loading car: " << e.what() << std::endl;
            }
        }

        carFile.close();
    }
    else {
        std::cerr << "Error opening file!\n";
    }
}

// Cleanup function to delete allocated memory
void cleanup() {
    // DELETING DYNAMICALLY ALLOCATED MEMORY FOR CAR POINTERS
    for (auto& car : cars) {
        delete car;  // FREEING MEMORY FOR EACH CAR OBJECT
    }
    // DELETING DYNAMICALLY ALLOCATED MEMORY FOR CUSTOMER POINTERS
    for (auto& user : users) {
        delete user;  // FREEING MEMORY FOR EACH CUSTOMER OBJECT
    }
}

int main() {
    // Load the existing cars from file
    loadCarsFromFile();

    // Add default cars
    addDefaultCars();

    // Handle user login
    if (login()) {
        // Main menu loop
        displayMenu();
    }

    // Cleanup allocated memory before program exits
    cleanup();

    return 0;
}