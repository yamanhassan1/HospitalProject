#include "hospital.h"

// Billing implementation
int Billing::nextId = 1;

Billing::Billing(int pId) 
    : billId(nextId++), patientId(pId), totalAmount(0), paymentStatus("Unpaid") {}

void Billing::addService(const string& service, double cost) {
    servicesAvailed.push_back(service);
    totalAmount += cost;
    cout << "\nAdded service: " << service << " ($" << cost << ")\n";
}

void Billing::addMedicine(int medId, int quantity, double price) {
    medicines.emplace_back(medId, quantity);
    totalAmount += (price * quantity);
    cout << "\nAdded medicine ID " << medId << " (x" << quantity << ") - $" 
         << (price * quantity) << "\n";
}

void Billing::processPayment(double amount) {
    if (amount >= totalAmount) {
        paymentStatus = "Paid";
        cout << "\nPayment processed. Change: $" << (amount - totalAmount) << "\n";
    } else {
        cout << "\nInsufficient payment! Remaining balance: $" 
             << (totalAmount - amount) << "\n";
    }
}

void Billing::displayBill() const {
    cout << "\n=== BILL #" << billId << " ===\n";
    cout << "Patient ID: " << patientId << "\n";
    cout << "Payment Status: " << paymentStatus << "\n\n";
    
    cout << "Services Availed:\n";
    for (const auto& service : servicesAvailed) {
        cout << "- " << service << "\n";
    }
    
    if (!medicines.empty()) {
        cout << "\nMedicines:\n";
        for (const auto& med : medicines) {
            cout << "- Medicine ID " << med.first << " (x" << med.second << ")\n";
        }
    }
    
    cout << "\nTotal Amount: $" << totalAmount << "\n";
}

int Billing::getId() const { return billId; }
int Billing::getPatientId() const { return patientId; }
double Billing::getTotalAmount() const { return totalAmount; }
string Billing::getPaymentStatus() const { return paymentStatus; }