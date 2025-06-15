#include "hospital.h"

// Appointment implementation
int Appointment::nextId = 1;

Appointment::Appointment(int pId, int dId, const string& dt) 
    : appointmentId(nextId++), patientId(pId), doctorId(dId), 
      dateTime(dt), status("Pending"), diagnosisNotes("") {}

void Appointment::completeAppointment(const string& notes) {
    status = "Completed";
    diagnosisNotes = notes;
    cout << "\nAppointment #" << appointmentId << " marked as completed.\n";
}

void Appointment::cancelAppointment() {
    status = "Cancelled";
    cout << "\nAppointment #" << appointmentId << " has been cancelled.\n";
}

void Appointment::displayDetails() const {
    cout << "\n=== APPOINTMENT DETAILS ===\n";
    cout << "Appointment ID: " << appointmentId << "\n";
    cout << "Patient ID: " << patientId << "\n";
    cout << "Doctor ID: " << doctorId << "\n";
    cout << "Date/Time: " << dateTime << "\n";
    cout << "Status: " << status << "\n";
    if (!diagnosisNotes.empty()) {
        cout << "Diagnosis Notes: " << diagnosisNotes << "\n";
    }
}

int Appointment::getId() const { return appointmentId; }
int Appointment::getPatientId() const { return patientId; }
int Appointment::getDoctorId() const { return doctorId; }
string Appointment::getStatus() const { return status; }

// Prescription implementation
int Prescription::nextId = 1;

Prescription::Prescription(int pId, int dId, const string& date) 
    : prescriptionId(nextId++), patientId(pId), doctorId(dId) {
    dateIssued = date.empty() ? "Current Date" : date;
}

void Prescription::addMedication(const string& med, const string& dosage) {
    medications.push_back(med);
    dosages.push_back(dosage);
    cout << "\nAdded " << med << " (" << dosage << ") to prescription #" 
         << prescriptionId << "\n";
}

void Prescription::display() const {
    cout << "\n=== PRESCRIPTION #" << prescriptionId << " ===\n";
    cout << "Patient ID: " << patientId << "\n";
    cout << "Doctor ID: " << doctorId << "\n";
    cout << "Date Issued: " << dateIssued;
    cout << "Medications:\n";
    for (size_t i = 0; i < medications.size(); i++) {
        cout << "- " << medications[i] << " (" << dosages[i] << ")\n";
    }
}

int Prescription::getId() const { return prescriptionId; }

// MedicalRecord implementation
int MedicalRecord::nextId = 1;

MedicalRecord::MedicalRecord(int pId, int dId, const string& diag, const string& plan)
    : recordId(nextId++), patientId(pId), doctorId(dId), 
      diagnosis(diag), treatmentPlan(plan) {}

void MedicalRecord::addTestResult(const string& result) {
    testReports.push_back(result);
    cout << "\nAdded test result to record #" << recordId << "\n";
}

void MedicalRecord::updateTreatmentPlan(const string& newPlan) {
    treatmentPlan = newPlan;
    cout << "\nUpdated treatment plan for record #" << recordId << "\n";
}

void MedicalRecord::display() const {
    cout << "\n=== MEDICAL RECORD #" << recordId << " ===\n";
    cout << "Patient ID: " << patientId << "\n";
    cout << "Doctor ID: " << doctorId << "\n";
    cout << "Diagnosis: " << diagnosis << "\n";
    cout << "Treatment Plan: " << treatmentPlan << "\n";
    if (!testReports.empty()) {
        cout << "Test Results:\n";
        for (const auto& test : testReports) {
            cout << "- " << test << "\n";
        }
    }
}

int MedicalRecord::getId() const { return recordId; }