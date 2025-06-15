#include "hospital.h"

// Medicine implementation
int Medicine::nextId = 1;

Medicine::Medicine(const string& name, double price, int quantity, const string& expiry)
    : medicineId(nextId++), name(name), price(price), 
      quantityInStock(quantity), expiryDate(expiry) {}

void Medicine::displayDetails() const {
    cout << "\n=== MEDICINE DETAILS ===\n";
    cout << "Medicine ID: " << medicineId << "\n";
    cout << "Name: " << name << "\n";
    cout << "Price: $" << price << "\n";
    cout << "Quantity: " << quantityInStock << "\n";
    cout << "Expiry Date: " << expiryDate << "\n";
}

void Medicine::checkAvailability(int required) const {
    if (quantityInStock >= required) {
        cout << "\n" << required << " units of " << name << " are available.\n";
    } else {
        cout << "\nOnly " << quantityInStock << " units of " << name << " available.\n";
    }
}

void Medicine::updateStock(int quantity) {
    quantityInStock += quantity;
    if (quantity > 0) {
        cout << "\nAdded " << quantity << " units to stock.\n";
    } else {
        cout << "\nDeducted " << -quantity << " units from stock.\n";
    }
    cout << "Current stock: " << quantityInStock << "\n";
}

int Medicine::getId() const { return medicineId; }
string Medicine::getName() const { return name; }
double Medicine::getPrice() const { return price; }
int Medicine::getQuantity() const { return quantityInStock; }

// Room implementation
int Room::nextId = 1;

Room::Room(const string& type) 
    : roomId(nextId++), type(type), status("Vacant"), patientId(-1) {}

void Room::displayDetails() const {
    cout << "\n=== ROOM DETAILS ===\n";
    cout << "Room ID: " << roomId << "\n";
    cout << "Type: " << type << "\n";
    cout << "Status: " << status << "\n";
    if (status == "Occupied") {
        cout << "Patient ID: " << patientId << "\n";
    }
}

void Room::checkAvailability() const {
    if (status == "Vacant") {
        cout << "\nRoom #" << roomId << " (" << type << ") is available.\n";
    } else {
        cout << "\nRoom #" << roomId << " is occupied by patient " << patientId << ".\n";
    }
}

void Room::assignPatient(int pId) {
    if (status == "Vacant") {
        patientId = pId;
        status = "Occupied";
        cout << "\nPatient " << pId << " assigned to Room #" << roomId << "\n";
    } else {
        cout << "\nRoom is already occupied!\n";
    }
}

void Room::vacateRoom() {
    if (status == "Occupied") {
        cout << "\nPatient " << patientId << " discharged from Room #" << roomId << "\n";
        patientId = -1;
        status = "Vacant";
    } else {
        cout << "\nRoom is already vacant!\n";
    }
}

int Room::getId() const { return roomId; }
string Room::getType() const { return type; }
string Room::getStatus() const { return status; }
int Room::getPatientId() const { return patientId; }