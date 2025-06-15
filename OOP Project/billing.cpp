#include "hospital.h"  // Includes the hospital header file which likely contains Billing class declaration

// Billing implementation

// Static member initialization - tracks next available bill ID
int Billing::nextId = 1;

// Constructor implementation
Billing::Billing(int pId) 
    : billId(nextId++),       // Assigns auto-incremented bill ID
      patientId(pId),         // Sets patient ID from parameter
      totalAmount(0),         // Initializes amount to 0
      paymentStatus("Unpaid") {} // Default status is "Unpaid"

// Adds a medical service to the bill
void Billing::addService(const string& service, double cost) {
    servicesAvailed.push_back(service);  // Adds service to vector
    totalAmount += cost;                // Updates total cost
    cout << "\nAdded service: " << service << " ($" << cost << ")\n";  // Confirmation message
}

// Adds medication to the bill
void Billing::addMedicine(int medId, int quantity, double price) {
    medicines.emplace_back(medId, quantity);  // Adds medicine as pair (ID, quantity)
    totalAmount += (price * quantity);       // Updates total with calculated cost
    cout << "\nAdded medicine ID " << medId << " (x" << quantity << ") - $" 
         << (price * quantity) << "\n";     // Confirmation message
}

// Processes payment for the bill
void Billing::processPayment(double amount) {
    if (amount >= totalAmount) {                    // If payment covers full amount
        paymentStatus = "Paid";                    // Update status
        cout << "\nPayment processed. Change: $" << (amount - totalAmount) << "\n";  // Show change
    } else {                                       // If payment is insufficient
        cout << "\nInsufficient payment! Remaining balance: $" 
             << (totalAmount - amount) << "\n";    // Show remaining balance
    }
}

// Displays detailed bill information
void Billing::displayBill() const {
    // Bill header
    cout << "\n=== BILL #" << billId << " ===\n";
    cout << "Patient ID: " << patientId << "\n";
    cout << "Payment Status: " << paymentStatus << "\n\n";
    
    // List services
    cout << "Services Availed:\n";
    for (const auto& service : servicesAvailed) {
        cout << "- " << service << "\n";
    }
    
    // List medicines (if any)
    if (!medicines.empty()) {
        cout << "\nMedicines:\n";
        for (const auto& med : medicines) {
            cout << "- Medicine ID " << med.first << " (x" << med.second << ")\n";
        }
    }
    
    // Display total
    cout << "\nTotal Amount: $" << totalAmount << "\n";
}

// Getter for bill ID
int Billing::getId() const { return billId; }

// Getter for patient ID
int Billing::getPatientId() const { return patientId; }

// Getter for total amount
double Billing::getTotalAmount() const { return totalAmount; }

// Getter for payment status
string Billing::getPaymentStatus() const { return paymentStatus; }