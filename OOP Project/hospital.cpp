#include "hospital.h"  // Includes the main hospital system header file containing class declarations

// HospitalSystem implementation

// Adds a patient to the system
void HospitalSystem::addPatient(Patient* patient) {
    persons.push_back(patient);  // Stores patient pointer in the persons vector
}

// Adds a doctor to the system
void HospitalSystem::addDoctor(Doctor* doctor) {
    persons.push_back(doctor);  // Stores doctor pointer in the persons vector
}

// Adds a nurse to the system
void HospitalSystem::addNurse(Nurse* nurse) {
    persons.push_back(nurse);  // Stores nurse pointer in the persons vector
}

// Displays all registered persons (patients, doctors, nurses)
void HospitalSystem::displayAllPersons() const {
    displayHeader("ALL REGISTERED PERSONS");  // Shows formatted header
    if (persons.empty()) {
        cout << "No persons registered.\n";  // Handles empty case
        return;
    }
    for (const auto& person : persons) {
        person->displayDetails();  // Polymorphic call to appropriate display method
        cout << "------------------------\n";  // Separator between entries
    }
}

// Finds a patient by ID using dynamic casting
void HospitalSystem::findPatient(int id, Patient*& patient) {
    for (auto& person : persons) {
        if (person->getId() == id) {  // Checks ID match
            patient = dynamic_cast<Patient*>(person);  // Safe downcasting
            return;
        }
    }
    patient = nullptr;  // Returns null if not found
}

// Finds a doctor by ID using dynamic casting
void HospitalSystem::findDoctor(int id, Doctor*& doctor) {
    for (auto& person : persons) {
        if (person->getId() == id) {  // Checks ID match
            doctor = dynamic_cast<Doctor*>(person);  // Safe downcasting
            return;
        }
    }
    doctor = nullptr;  // Returns null if not found
}

// Finds a nurse by ID using dynamic casting
void HospitalSystem::findNurse(int id, Nurse*& nurse) {
    for (auto& person : persons) {
        if (person->getId() == id) {  // Checks ID match
            nurse = dynamic_cast<Nurse*>(person);  // Safe downcasting
            return;
        }
    }
    nurse = nullptr;  // Returns null if not found
}

// Adds medicine to inventory
void HospitalSystem::addMedicine(Medicine* medicine) {
    medicines.push_back(medicine);  // Stores medicine in inventory
    cout << "\nMedicine added successfully!\n";  // Confirmation message
}

// Displays all medicines in inventory
void HospitalSystem::displayAllMedicines() const {
    displayHeader("MEDICINE INVENTORY");  // Formatted header
    if (medicines.empty()) {
        cout << "No medicines in inventory.\n";  // Empty case handling
        return;
    }
    for (const auto& med : medicines) {
        med->displayDetails();  // Shows medicine details
        cout << "------------------------\n";  // Separator
    }
}

// Finds medicine by ID
void HospitalSystem::findMedicine(int id, Medicine*& med) {
    for (auto& m : medicines) {
        if (m->getId() == id) {  // Checks ID match
            med = m;  // Returns found medicine
            return;
        }
    }
    med = nullptr;  // Returns null if not found
}

// Adds a room to the system
void HospitalSystem::addRoom(Room* room) {
    rooms.push_back(room);  // Stores room in system
    cout << "\nRoom added successfully!\n";  // Confirmation message
}

// Displays all rooms and their status
void HospitalSystem::displayAllRooms() const {
    displayHeader("ROOM STATUS");  // Formatted header
    if (rooms.empty()) {
        cout << "No rooms available.\n";  // Empty case handling
        return;
    }
    for (const auto& room : rooms) {
        room->displayDetails();  // Shows room details
        cout << "------------------------\n";  // Separator
    }
}

// Finds room by ID
void HospitalSystem::findRoom(int id, Room*& room) {
    for (auto& r : rooms) {
        if (r->getId() == id) {  // Checks ID match
            room = r;  // Returns found room
            return;
        }
    }
    room = nullptr;  // Returns null if not found
}

// Finds first available room of specified type
void HospitalSystem::findAvailableRoom(const string& type, Room*& room) {
    for (auto& r : rooms) {
        if (r->getType() == type && r->getStatus() == "Vacant") {  // Checks type and status
            room = r;  // Returns available room
            return;
        }
    }
    room = nullptr;  // Returns null if none available
}

// Creates a new bill for a patient
void HospitalSystem::createBill(int patientId, Billing*& bill) {
    bill = new Billing(patientId);  // Creates new bill instance
    bills.push_back(bill);  // Adds to billing records
    cout << "\nNew bill created for patient " << patientId << "\n";  // Confirmation
}

// Displays all billing records
void HospitalSystem::displayAllBills() const {
    displayHeader("BILLING RECORDS");  // Formatted header
    if (bills.empty()) {
        cout << "No billing records.\n";  // Empty case handling
        return;
    }
    for (const auto& bill : bills) {
        bill->displayBill();  // Shows detailed bill
        cout << "------------------------\n";  // Separator
    }
}

// Finds unpaid bill for a patient
void HospitalSystem::findPatientBill(int patientId, Billing*& bill) {
    for (auto& b : bills) {
        if (b->getPatientId() == patientId && b->getPaymentStatus() == "Unpaid") {  // Checks patient ID and status
            bill = b;  // Returns unpaid bill
            return;
        }
    }
    bill = nullptr;  // Returns null if not found
}