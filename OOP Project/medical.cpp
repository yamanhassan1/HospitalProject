#include "hospital.h"  // Includes the main hospital system header

// ========== APPOINTMENT CLASS IMPLEMENTATION ========== //

// Static member initialization - tracks next appointment ID
int Appointment::nextId = 1;

// Constructor implementation
Appointment::Appointment(int pId, int dId, const string& dt) 
    : appointmentId(nextId++),  // Auto-increments ID
      patientId(pId),          // Sets patient ID
      doctorId(dId),           // Sets doctor ID
      dateTime(dt),            // Sets appointment datetime
      status("Pending"),       // Default status
      diagnosisNotes("") {}    // Empty notes initially

// Marks appointment as complete with doctor's notes
void Appointment::completeAppointment(const string& notes) {
    status = "Completed";             // Updates status
    diagnosisNotes = notes;           // Stores diagnosis
    cout << "\nAppointment #" << appointmentId << " marked as completed.\n";  // Confirmation
}

// Cancels the appointment
void Appointment::cancelAppointment() {
    status = "Cancelled";  // Updates status
    cout << "\nAppointment #" << appointmentId << " has been cancelled.\n";  // Confirmation
}

// Displays complete appointment details
void Appointment::displayDetails() const {
    cout << "\n=== APPOINTMENT DETAILS ===\n";  // Header
    cout << "Appointment ID: " << appointmentId << "\n";
    cout << "Patient ID: " << patientId << "\n";
    cout << "Doctor ID: " << doctorId << "\n";
    cout << "Date/Time: " << dateTime << "\n";
    cout << "Status: " << status << "\n";
    if (!diagnosisNotes.empty()) {  // Only shows notes if exists
        cout << "Diagnosis Notes: " << diagnosisNotes << "\n";
    }
}

// Getter for appointment ID
int Appointment::getId() const { return appointmentId; }

// Getter for patient ID
int Appointment::getPatientId() const { return patientId; }

// Getter for doctor ID
int Appointment::getDoctorId() const { return doctorId; }

// Getter for appointment status
string Appointment::getStatus() const { return status; }

// ========== PRESCRIPTION CLASS IMPLEMENTATION ========== //

// Static member initialization - tracks next prescription ID
int Prescription::nextId = 1;

// Constructor implementation
Prescription::Prescription(int pId, int dId, const string& date) 
    : prescriptionId(nextId++),  // Auto-increments ID
      patientId(pId),           // Sets patient ID
      doctorId(dId) {           // Sets doctor ID
    dateIssued = date.empty() ? "Current Date" : date;  // Defaults to current date if empty
}

// Adds medication to prescription
void Prescription::addMedication(const string& med, const string& dosage) {
    medications.push_back(med);    // Stores medication name
    dosages.push_back(dosage);     // Stores dosage information
    cout << "\nAdded " << med << " (" << dosage << ") to prescription #" 
         << prescriptionId << "\n";  // Confirmation
}

// Displays complete prescription details
void Prescription::display() const {
    cout << "\n=== PRESCRIPTION #" << prescriptionId << " ===\n";
    cout << "Patient ID: " << patientId << "\n";
    cout << "Doctor ID: " << doctorId << "\n";
    cout << "Date Issued: " << dateIssued;
    cout << "Medications:\n";
    // Lists all medications with dosages
    for (size_t i = 0; i < medications.size(); i++) {
        cout << "- " << medications[i] << " (" << dosages[i] << ")\n";
    }
}

// Getter for prescription ID
int Prescription::getId() const { return prescriptionId; }

// ========== MEDICAL RECORD CLASS IMPLEMENTATION ========== //

// Static member initialization - tracks next record ID
int MedicalRecord::nextId = 1;

// Constructor implementation
MedicalRecord::MedicalRecord(int pId, int dId, const string& diag, const string& plan)
    : recordId(nextId++),  // Auto-increments ID
      patientId(pId),      // Sets patient ID
      doctorId(dId),       // Sets doctor ID
      diagnosis(diag),     // Stores initial diagnosis
      treatmentPlan(plan) {} // Stores treatment plan

// Adds test result to medical record
void MedicalRecord::addTestResult(const string& result) {
    testReports.push_back(result);  // Stores test result
    cout << "\nAdded test result to record #" << recordId << "\n";  // Confirmation
}

// Updates the treatment plan
void MedicalRecord::updateTreatmentPlan(const string& newPlan) {
    treatmentPlan = newPlan;  // Updates treatment plan
    cout << "\nUpdated treatment plan for record #" << recordId << "\n";  // Confirmation
}

// Displays complete medical record
void MedicalRecord::display() const {
    cout << "\n=== MEDICAL RECORD #" << recordId << " ===\n";
    cout << "Patient ID: " << patientId << "\n";
    cout << "Doctor ID: " << doctorId << "\n";
    cout << "Diagnosis: " << diagnosis << "\n";
    cout << "Treatment Plan: " << treatmentPlan << "\n";
    if (!testReports.empty()) {  // Only shows tests if exists
        cout << "Test Results:\n";
        for (const auto& test : testReports) {
            cout << "- " << test << "\n";
        }
    }
}

// Getter for record ID
int MedicalRecord::getId() const { return recordId; }