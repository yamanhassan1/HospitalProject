#include "hospital.h"

// Person implementation
Person::Person(int id, string name, int age, string gender, string address, string contactNumber)
    : id(id), name(name), age(age), gender(gender), address(address), contactNumber(contactNumber) {}

void Person::updateContactInfo(string newAddress, string newContact) {
    address = newAddress;
    contactNumber = newContact;
    cout << "\nContact information updated successfully!\n";
}

int Person::getId() const { return id; }
string Person::getName() const { return name; }

// Staff implementation
Staff::Staff(int id, string name, int age, string gender, string address, string contactNumber,
      double salary, string department, string joinDate)
    : Person(id, name, age, gender, address, contactNumber),
      staffId(id), salary(salary), department(department), joinDate(joinDate) {}

void Staff::displayDetails() const {
    cout << "\n=== STAFF DETAILS ===\n";
    cout << "ID: " << staffId << "\n";
    cout << "Name: " << name << "\n";
    cout << "Department: " << department << "\n";
    cout << "Join Date: " << joinDate << "\n";
    cout << "Salary: $" << salary << "\n";
}

// Patient implementation
Patient::Patient(int id, string name, int age, string gender, string address, string contactNumber,
        string bloodGroup, int assignedDoctorId)
    : Person(id, name, age, gender, address, contactNumber), 
      patientId(id), bloodGroup(bloodGroup), assignedDoctorId(assignedDoctorId), roomId(-1) {}

void Patient::displayDetails() const {
    cout << "\n=== PATIENT DETAILS ===\n";
    cout << "ID: " << patientId << "\n";
    cout << "Name: " << name << "\n";
    cout << "Age: " << age << "\n";
    cout << "Gender: " << gender << "\n";
    cout << "Blood Group: " << bloodGroup << "\n";
    cout << "Assigned Doctor ID: " << assignedDoctorId << "\n";
    if (roomId != -1) {
        cout << "Room ID: " << roomId << "\n";
    }
    cout << "Address: " << address << "\n";
    cout << "Contact: " << contactNumber << "\n";
}

void Patient::addDisease(const string& disease) {
    diseases.push_back(disease);
    cout << "\nAdded medical condition: " << disease << "\n";
}

void Patient::displayAppointments() const {
    if (appointments.empty()) {
        cout << "\nNo appointments scheduled.\n";
        return;
    }
    
    cout << "\n=== APPOINTMENTS ===\n";
    for (const auto& appt : appointments) {
        appt.displayDetails();
        cout << "------------------------\n";
    }
}

void Patient::displayPrescriptions() const {
    if (prescriptions.empty()) {
        cout << "\nNo prescriptions available.\n";
        return;
    }
    
    cout << "\n=== PRESCRIPTIONS ===\n";
    for (const auto& presc : prescriptions) {
        presc.display();
        cout << "------------------------\n";
    }
}

void Patient::displayMedicalRecords() const {
    if (medicalRecords.empty()) {
        cout << "\nNo medical records available.\n";
        return;
    }
    
    cout << "\n=== MEDICAL RECORDS ===\n";
    for (const auto& record : medicalRecords) {
        record.display();
        cout << "------------------------\n";
    }
}

void Patient::scheduleAppointment(int doctorId, const string& dateTime) {
    appointments.emplace_back(patientId, doctorId, dateTime);
    cout << "\nAppointment scheduled successfully!\n";
}

void Patient::addPrescription(int doctorId) {
    prescriptions.emplace_back(patientId, doctorId);
    cout << "\nNew prescription created!\n";
}

void Patient::addMedicalRecord(int doctorId, const string& diagnosis, const string& plan) {
    medicalRecords.emplace_back(patientId, doctorId, diagnosis, plan);
    cout << "\nMedical record created!\n";
}

void Patient::assignRoom(int rId) {
    roomId = rId;
    cout << "\nAssigned to Room #" << rId << "\n";
}

void Patient::dischargeFromRoom() {
    roomId = -1;
    cout << "\nDischarged from room\n";
}

void Patient::getAppointment(int id, Appointment*& appt) {
    for (auto& a : appointments) {
        if (a.getId() == id) {
            appt = &a;
            return;
        }
    }
    appt = nullptr;
}

void Patient::getPrescription(int id, Prescription*& presc) {
    for (auto& p : prescriptions) {
        if (p.getId() == id) {
            presc = &p;
            return;
        }
    }
    presc = nullptr;
}

void Patient::getMedicalRecord(int id, MedicalRecord*& record) {
    for (auto& r : medicalRecords) {
        if (r.getId() == id) {
            record = &r;
            return;
        }
    }
    record = nullptr;
}

int Patient::getRoomId() const { return roomId; }

// Doctor implementation
Doctor::Doctor(int id, string name, int age, string gender, string address, string contactNumber,
       double salary, string department, string joinDate, string specialization, string licenseNumber)
    : Staff(id, name, age, gender, address, contactNumber, salary, department, joinDate),
      doctorId(id), specialization(specialization), licenseNumber(licenseNumber) {}

void Doctor::displayDetails() const {
    Staff::displayDetails();
    cout << "Specialization: " << specialization << "\n";
    cout << "License Number: " << licenseNumber << "\n";
    
    if (!availableSlots.empty()) {
        cout << "\nAvailable Slots:\n";
        for (const auto& slot : availableSlots) {
            cout << "- " << slot << "\n";
        }
    }
}

void Doctor::prescribeMedication(int patientId, const string &medication, const string& dosage) {
    cout << "\nPrescription created:\n";
    cout << "Patient ID: " << patientId << "\n";
    cout << "Medication: " << medication << "\n";
    cout << "Dosage: " << dosage << "\n";
}

void Doctor::addAvailableSlot(const string& slot) {
    availableSlots.push_back(slot);
    cout << "\nAdded available slot: " << slot << "\n";
}

void Doctor::viewAppointments() const {
    if (appointments.empty()) {
        cout << "\nNo appointments scheduled.\n";
        return;
    }
    
    cout << "\n=== APPOINTMENTS ===\n";
    cout << "Dr. " << name << " (" << specialization << ")\n\n";
    for (const auto& appt : appointments) {
        appt.displayDetails();
        cout << "------------------------\n";
    }
}

void Doctor::completeAppointment(int apptId, const string& notes) {
    for (auto& appt : appointments) {
        if (appt.getId() == apptId && appt.getStatus() == "Pending") {
            appt.completeAppointment(notes);
            return;
        }
    }
    cout << "\nAppointment not found or not pending!\n";
}

void Doctor::addAppointment(int patientId, const string& dateTime) {
    appointments.emplace_back(patientId, doctorId, dateTime);
}

void Doctor::getAppointment(int id, Appointment*& appt) {
    for (auto& a : appointments) {
        if (a.getId() == id) {
            appt = &a;
            return;
        }
    }
    appt = nullptr;
}

// Nurse implementation
Nurse::Nurse(int id, string name, int age, string gender, string address, string contactNumber,
      double salary, string department, string joinDate, string shiftTime, string qualification)
    : Staff(id, name, age, gender, address, contactNumber, salary, department, joinDate),
      nurseId(id), shiftTime(shiftTime), qualification(qualification) {}

void Nurse::displayDetails() const {
    Staff::displayDetails();
    cout << "Shift Time: " << shiftTime << "\n";
    cout << "Qualification: " << qualification << "\n";
}

void Nurse::assistDoctor(int doctorId) {
    cout << "\nNurse " << name << " is now assisting Doctor ID " << doctorId << "\n";
}

void Nurse::monitorPatient(int patientId) {
    cout << "\nNurse " << name << " is now monitoring Patient ID " << patientId << "\n";
}