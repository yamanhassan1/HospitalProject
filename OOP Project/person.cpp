#include "hospital.h"  // Includes the main hospital system header

// ========== PERSON CLASS IMPLEMENTATION ========== //

// Constructor implementation for base Person class
Person::Person(int id, string name, int age, string gender, string address, string contactNumber)
    : id(id),            // Unique identifier
      name(name),        // Full name
      age(age),          // Age in years
      gender(gender),    // Gender identity
      address(address),  // Physical address
      contactNumber(contactNumber) {}  // Contact information

// Updates contact information for any person
void Person::updateContactInfo(string newAddress, string newContact) {
    address = newAddress;          // Updates address
    contactNumber = newContact;    // Updates phone number
    cout << "\nContact information updated successfully!\n";  // Confirmation
}

// Getter for person ID
int Person::getId() const { return id; }

// Getter for person name
string Person::getName() const { return name; }

// ========== STAFF CLASS IMPLEMENTATION ========== //

// Constructor for Staff (inherits from Person)
Staff::Staff(int id, string name, int age, string gender, string address, string contactNumber,
      double salary, string department, string joinDate)
    : Person(id, name, age, gender, address, contactNumber),  // Initializes base Person
      staffId(id),          // Staff-specific ID
      salary(salary),       // Annual salary
      department(department),  // Department assignment
      joinDate(joinDate) {} // Employment start date

// Displays complete staff information
void Staff::displayDetails() const {
    cout << "\n=== STAFF DETAILS ===\n";  // Header
    cout << "ID: " << staffId << "\n";
    cout << "Name: " << name << "\n";
    cout << "Department: " << department << "\n";
    cout << "Join Date: " << joinDate << "\n";
    cout << "Salary: $" << salary << "\n";  // Formatted currency
}

// ========== PATIENT CLASS IMPLEMENTATION ========== //

// Constructor for Patient (inherits from Person)
Patient::Patient(int id, string name, int age, string gender, string address, string contactNumber,
        string bloodGroup, int assignedDoctorId)
    : Person(id, name, age, gender, address, contactNumber),  // Initializes base Person
      patientId(id),          // Patient-specific ID
      bloodGroup(bloodGroup), // Blood type
      assignedDoctorId(assignedDoctorId),  // Primary physician
      roomId(-1) {}           // -1 indicates no room assigned

// Displays complete patient information
void Patient::displayDetails() const {
    cout << "\n=== PATIENT DETAILS ===\n";  // Header
    cout << "ID: " << patientId << "\n";
    cout << "Name: " << name << "\n";
    cout << "Age: " << age << "\n";
    cout << "Gender: " << gender << "\n";
    cout << "Blood Group: " << bloodGroup << "\n";
    cout << "Assigned Doctor ID: " << assignedDoctorId << "\n";
    if (roomId != -1) {  // Only shows room if assigned
        cout << "Room ID: " << roomId << "\n";
    }
    cout << "Address: " << address << "\n";
    cout << "Contact: " << contactNumber << "\n";
}

// Adds medical condition to patient's record
void Patient::addDisease(const string& disease) {
    diseases.push_back(disease);  // Stores condition
    cout << "\nAdded medical condition: " << disease << "\n";  // Confirmation
}

// Displays all patient appointments
void Patient::displayAppointments() const {
    if (appointments.empty()) {  // Handles empty case
        cout << "\nNo appointments scheduled.\n";
        return;
    }
    
    cout << "\n=== APPOINTMENTS ===\n";
    for (const auto& appt : appointments) {  // Shows each appointment
        appt.displayDetails();
        cout << "------------------------\n";  // Separator
    }
}

// Displays all patient prescriptions
void Patient::displayPrescriptions() const {
    if (prescriptions.empty()) {  // Handles empty case
        cout << "\nNo prescriptions available.\n";
        return;
    }
    
    cout << "\n=== PRESCRIPTIONS ===\n";
    for (const auto& presc : prescriptions) {  // Shows each prescription
        presc.display();
        cout << "------------------------\n";  // Separator
    }
}

// Displays all medical records
void Patient::displayMedicalRecords() const {
    if (medicalRecords.empty()) {  // Handles empty case
        cout << "\nNo medical records available.\n";
        return;
    }
    
    cout << "\n=== MEDICAL RECORDS ===\n";
    for (const auto& record : medicalRecords) {  // Shows each record
        record.display();
        cout << "------------------------\n";  // Separator
    }
}

// Schedules new appointment
void Patient::scheduleAppointment(int doctorId, const string& dateTime) {
    appointments.emplace_back(patientId, doctorId, dateTime);  // Creates new appointment
    cout << "\nAppointment scheduled successfully!\n";  // Confirmation
}

// Creates new prescription
void Patient::addPrescription(int doctorId) {
    prescriptions.emplace_back(patientId, doctorId);  // Creates new prescription
    cout << "\nNew prescription created!\n";  // Confirmation
}

// Creates new medical record
void Patient::addMedicalRecord(int doctorId, const string& diagnosis, const string& plan) {
    medicalRecords.emplace_back(patientId, doctorId, diagnosis, plan);  // Creates record
    cout << "\nMedical record created!\n";  // Confirmation
}

// Assigns patient to room
void Patient::assignRoom(int rId) {
    roomId = rId;  // Sets room ID
    cout << "\nAssigned to Room #" << rId << "\n";  // Confirmation
}

// Removes patient from room
void Patient::dischargeFromRoom() {
    roomId = -1;  // Resets room assignment
    cout << "\nDischarged from room\n";  // Confirmation
}

// Finds appointment by ID
void Patient::getAppointment(int id, Appointment*& appt) {
    for (auto& a : appointments) {  // Searches appointments
        if (a.getId() == id) {
            appt = &a;  // Returns found appointment
            return;
        }
    }
    appt = nullptr;  // Returns null if not found
}

// Finds prescription by ID
void Patient::getPrescription(int id, Prescription*& presc) {
    for (auto& p : prescriptions) {  // Searches prescriptions
        if (p.getId() == id) {
            presc = &p;  // Returns found prescription
            return;
        }
    }
    presc = nullptr;  // Returns null if not found
}

// Finds medical record by ID
void Patient::getMedicalRecord(int id, MedicalRecord*& record) {
    for (auto& r : medicalRecords) {  // Searches records
        if (r.getId() == id) {
            record = &r;  // Returns found record
            return;
        }
    }
    record = nullptr;  // Returns null if not found
}

// Getter for room ID
int Patient::getRoomId() const { return roomId; }

// ========== DOCTOR CLASS IMPLEMENTATION ========== //

// Constructor for Doctor (inherits from Staff)
Doctor::Doctor(int id, string name, int age, string gender, string address, string contactNumber,
       double salary, string department, string joinDate, string specialization, string licenseNumber)
    : Staff(id, name, age, gender, address, contactNumber, salary, department, joinDate),  // Base Staff
      doctorId(id),                // Doctor-specific ID
      specialization(specialization),  // Medical specialty
      licenseNumber(licenseNumber) {}  // Professional license

// Displays complete doctor information
void Doctor::displayDetails() const {
    Staff::displayDetails();  // Shows base Staff info
    cout << "Specialization: " << specialization << "\n";
    cout << "License Number: " << licenseNumber << "\n";
    
    if (!availableSlots.empty()) {  // Shows available slots if any
        cout << "\nAvailable Slots:\n";
        for (const auto& slot : availableSlots) {
            cout << "- " << slot << "\n";
        }
    }
}

// Creates medication prescription
void Doctor::prescribeMedication(int patientId, const string &medication, const string& dosage) {
    cout << "\nPrescription created:\n";
    cout << "Patient ID: " << patientId << "\n";
    cout << "Medication: " << medication << "\n";
    cout << "Dosage: " << dosage << "\n";  // Detailed prescription info
}

// Adds available appointment slot
void Doctor::addAvailableSlot(const string& slot) {
    availableSlots.push_back(slot);  // Stores time slot
    cout << "\nAdded available slot: " << slot << "\n";  // Confirmation
}

// Displays all doctor appointments
void Doctor::viewAppointments() const {
    if (appointments.empty()) {  // Handles empty case
        cout << "\nNo appointments scheduled.\n";
        return;
    }
    
    cout << "\n=== APPOINTMENTS ===\n";
    cout << "Dr. " << name << " (" << specialization << ")\n\n";  // Doctor header
    for (const auto& appt : appointments) {  // Shows each appointment
        appt.displayDetails();
        cout << "------------------------\n";  // Separator
    }
}

// Completes appointment with notes
void Doctor::completeAppointment(int apptId, const string& notes) {
    for (auto& appt : appointments) {  // Finds appointment
        if (appt.getId() == apptId && appt.getStatus() == "Pending") {
            appt.completeAppointment(notes);  // Marks complete
            return;
        }
    }
    cout << "\nAppointment not found or not pending!\n";  // Error message
}

// Adds new appointment
void Doctor::addAppointment(int patientId, const string& dateTime) {
    appointments.emplace_back(patientId, doctorId, dateTime);  // Creates appointment
}

// Finds appointment by ID
void Doctor::getAppointment(int id, Appointment*& appt) {
    for (auto& a : appointments) {  // Searches appointments
        if (a.getId() == id) {
            appt = &a;  // Returns found appointment
            return;
        }
    }
    appt = nullptr;  // Returns null if not found
}

// ========== NURSE CLASS IMPLEMENTATION ========== //

// Constructor for Nurse (inherits from Staff)
Nurse::Nurse(int id, string name, int age, string gender, string address, string contactNumber,
      double salary, string department, string joinDate, string shiftTime, string qualification)
    : Staff(id, name, age, gender, address, contactNumber, salary, department, joinDate),  // Base Staff
      nurseId(id),            // Nurse-specific ID
      shiftTime(shiftTime),   // Work schedule
      qualification(qualification) {}  // Professional credentials

// Displays complete nurse information
void Nurse::displayDetails() const {
    Staff::displayDetails();  // Shows base Staff info
    cout << "Shift Time: " << shiftTime << "\n";
    cout << "Qualification: " << qualification << "\n";
}

// Simulates assisting a doctor
void Nurse::assistDoctor(int doctorId) {
    cout << "\nNurse " << name << " is now assisting Doctor ID " << doctorId << "\n";
}

// Simulates monitoring a patient
void Nurse::monitorPatient(int patientId) {
    cout << "\nNurse " << name << " is now monitoring Patient ID " << patientId << "\n";
}