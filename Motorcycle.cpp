#include "Motorcycle.h"

Motorcycle::Motorcycle(int id, const std::string& make, const std::string& model, int year, double engineCapacity)
    : id(id), make(make), model(model), year(year), engineCapacity(engineCapacity) {}

void Motorcycle::displayVehicleInfo() const {
    std::cout << "Motorcycle ID: " << id << " - " << make << " " << model << " " << year
        << ", Engine Capacity: " << engineCapacity << "cc" << std::endl;
}

void Motorcycle::displayVehicleInfo(const std::string& additionalInfo) const {
    displayVehicleInfo();  // Call the base display method
    std::cout << "Additional Info: " << additionalInfo << std::endl;
}

void Motorcycle::displayVehicleInfo(int engineSize) const {
    std::cout << "Motorcycle ID: " << id << " - " << make << " " << model << " " << year
        << ", Engine Size: " << engineSize << "cc" << std::endl;
}
