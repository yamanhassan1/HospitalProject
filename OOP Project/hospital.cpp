#include "hospital.h"

// HospitalSystem implementation
void HospitalSystem::addPatient(Patient* patient) {
    persons.push_back(patient);
}

void HospitalSystem::addDoctor(Doctor* doctor) {
    persons.push_back(doctor);
}

void HospitalSystem::addNurse(Nurse* nurse) {
    persons.push_back(nurse);
}

void HospitalSystem::displayAllPersons() const {
    displayHeader("ALL REGISTERED PERSONS");
    if (persons.empty()) {
        cout << "No persons registered.\n";
        return;
    }
    for (const auto& person : persons) {
        person->displayDetails();
        cout << "------------------------\n";
    }
}

void HospitalSystem::findPatient(int id, Patient*& patient) {
    for (auto& person : persons) {
        if (person->getId() == id) {
            patient = dynamic_cast<Patient*>(person);
            return;
        }
    }
    patient = nullptr;
}

void HospitalSystem::findDoctor(int id, Doctor*& doctor) {
    for (auto& person : persons) {
        if (person->getId() == id) {
            doctor = dynamic_cast<Doctor*>(person);
            return;
        }
    }
    doctor = nullptr;
}

void HospitalSystem::findNurse(int id, Nurse*& nurse) {
    for (auto& person : persons) {
        if (person->getId() == id) {
            nurse = dynamic_cast<Nurse*>(person);
            return;
        }
    }
    nurse = nullptr;
}

void HospitalSystem::addMedicine(Medicine* medicine) {
    medicines.push_back(medicine);
    cout << "\nMedicine added successfully!\n";
}

void HospitalSystem::displayAllMedicines() const {
    displayHeader("MEDICINE INVENTORY");
    if (medicines.empty()) {
        cout << "No medicines in inventory.\n";
        return;
    }
    for (const auto& med : medicines) {
        med->displayDetails();
        cout << "------------------------\n";
    }
}

void HospitalSystem::findMedicine(int id, Medicine*& med) {
    for (auto& m : medicines) {
        if (m->getId() == id) {
            med = m;
            return;
        }
    }
    med = nullptr;
}

void HospitalSystem::addRoom(Room* room) {
    rooms.push_back(room);
    cout << "\nRoom added successfully!\n";
}

void HospitalSystem::displayAllRooms() const {
    displayHeader("ROOM STATUS");
    if (rooms.empty()) {
        cout << "No rooms available.\n";
        return;
    }
    for (const auto& room : rooms) {
        room->displayDetails();
        cout << "------------------------\n";
    }
}

void HospitalSystem::findRoom(int id, Room*& room) {
    for (auto& r : rooms) {
        if (r->getId() == id) {
            room = r;
            return;
        }
    }
    room = nullptr;
}

void HospitalSystem::findAvailableRoom(const string& type, Room*& room) {
    for (auto& r : rooms) {
        if (r->getType() == type && r->getStatus() == "Vacant") {
            room = r;
            return;
        }
    }
    room = nullptr;
}

void HospitalSystem::createBill(int patientId, Billing*& bill) {
    bill = new Billing(patientId);
    bills.push_back(bill);
    cout << "\nNew bill created for patient " << patientId << "\n";
}

void HospitalSystem::displayAllBills() const {
    displayHeader("BILLING RECORDS");
    if (bills.empty()) {
        cout << "No billing records.\n";
        return;
    }
    for (const auto& bill : bills) {
        bill->displayBill();
        cout << "------------------------\n";
    }
}

void HospitalSystem::findPatientBill(int patientId, Billing*& bill) {
    for (auto& b : bills) {
        if (b->getPatientId() == patientId && b->getPaymentStatus() == "Unpaid") {
            bill = b;
            return;
        }
    }
    bill = nullptr;
}