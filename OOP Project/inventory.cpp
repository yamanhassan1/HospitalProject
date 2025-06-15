#include "hospital.h"  // Includes the main hospital system header

// Medicine implementation

// Static member initialization - tracks next available medicine ID
int Medicine::nextId = 1;

// Constructor implementation
Medicine::Medicine(const string& name, double price, int quantity, const string& expiry)
    : medicineId(nextId++),  // Auto-increments ID for each new medicine
      name(name),            // Sets medicine name
      price(price),          // Sets unit price
      quantityInStock(quantity), // Initializes stock quantity
      expiryDate(expiry) {}  // Sets expiration date

// Displays complete medicine information
void Medicine::displayDetails() const {
    cout << "\n=== MEDICINE DETAILS ===\n";  // Header
    cout << "Medicine ID: " << medicineId << "\n";  // Unique identifier
    cout << "Name: " << name << "\n";        // Medicine name
    cout << "Price: $" << price << "\n";     // Cost per unit
    cout << "Quantity: " << quantityInStock << "\n";  // Current stock
    cout << "Expiry Date: " << expiryDate << "\n";  // Shelf life
}

// Checks if required quantity is available
void Medicine::checkAvailability(int required) const {
    if (quantityInStock >= required) {
        cout << "\n" << required << " units of " << name << " are available.\n";
    } else {
        cout << "\nOnly " << quantityInStock << " units of " << name << " available.\n";
    }
}

// Updates inventory quantity (adds or removes stock)
void Medicine::updateStock(int quantity) {
    quantityInStock += quantity;  // Modifies current stock
    if (quantity > 0) {
        cout << "\nAdded " << quantity << " units to stock.\n";  // Restock message
    } else {
        cout << "\nDeducted " << -quantity << " units from stock.\n";  // Dispensing message
    }
    cout << "Current stock: " << quantityInStock << "\n";  // Updated quantity
}

// Getter for medicine ID
int Medicine::getId() const { return medicineId; }

// Getter for medicine name
string Medicine::getName() const { return name; }

// Getter for unit price
double Medicine::getPrice() const { return price; }

// Getter for current quantity
int Medicine::getQuantity() const { return quantityInStock; }

// Room implementation

// Static member initialization - tracks next available room ID
int Room::nextId = 1;

// Constructor implementation
Room::Room(const string& type) 
    : roomId(nextId++),  // Auto-increments ID for each new room
      type(type),        // Sets room type (General/ICU/OR)
      status("Vacant"),  // Default status
      patientId(-1) {}   // -1 indicates no patient assigned

// Displays complete room information
void Room::displayDetails() const {
    cout << "\n=== ROOM DETAILS ===\n";  // Header
    cout << "Room ID: " << roomId << "\n";  // Unique identifier
    cout << "Type: " << type << "\n";    // Room category
    cout << "Status: " << status << "\n"; // Vacant/Occupied
    if (status == "Occupied") {
        cout << "Patient ID: " << patientId << "\n";  // Shows occupant if occupied
    }
}

// Checks and displays room availability
void Room::checkAvailability() const {
    if (status == "Vacant") {
        cout << "\nRoom #" << roomId << " (" << type << ") is available.\n";
    } else {
        cout << "\nRoom #" << roomId << " is occupied by patient " << patientId << ".\n";
    }
}

// Assigns a patient to the room
void Room::assignPatient(int pId) {
    if (status == "Vacant") {  // Only assign if vacant
        patientId = pId;
        status = "Occupied";
        cout << "\nPatient " << pId << " assigned to Room #" << roomId << "\n";
    } else {
        cout << "\nRoom is already occupied!\n";  // Error message
    }
}

// Vacates the room
void Room::vacateRoom() {
    if (status == "Occupied") {  // Only vacate if occupied
        cout << "\nPatient " << patientId << " discharged from Room #" << roomId << "\n";
        patientId = -1;  // Reset patient ID
        status = "Vacant";  // Update status
    } else {
        cout << "\nRoom is already vacant!\n";  // Error message
    }
}

// Getter for room ID
int Room::getId() const { return roomId; }

// Getter for room type
string Room::getType() const { return type; }

// Getter for room status
string Room::getStatus() const { return status; }

// Getter for assigned patient ID
int Room::getPatientId() const { return patientId; }