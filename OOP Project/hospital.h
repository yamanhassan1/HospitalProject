#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <string>
using namespace std;

// Forward declarations
class Person;
class Patient;
class Staff;
class Doctor;
class Nurse;
class Medicine;
class Room;
class Billing;
class Appointment;
class Prescription;
class MedicalRecord;

// Utility functions
void clearScreen();
void displayHeader(const string& title);
void pressEnterToContinue();

// Person classes
class Person {
protected:
    int id;
    string name;
    int age;
    string gender;
    string address;
    string contactNumber;

public:
    Person(int id, string name, int age, string gender, string address, string contactNumber);
    virtual void displayDetails() const = 0;
    void updateContactInfo(string newAddress, string newContact);
    int getId() const;
    string getName() const;
};

class Staff : public Person {
protected:
    int staffId;
    double salary;
    string department;
    string joinDate;

public:
    Staff(int id, string name, int age, string gender, string address, string contactNumber,
          double salary, string department, string joinDate);
    void displayDetails() const override;
};

// Medical entity classes
class Appointment {
private:
    static int nextId;
    int appointmentId;
    int patientId;
    int doctorId;
    string dateTime;
    string status;
    string diagnosisNotes;

public:
    Appointment(int pId, int dId, const string& dt);
    void completeAppointment(const string& notes);
    void cancelAppointment();
    void displayDetails() const;
    int getId() const;
    int getPatientId() const;
    int getDoctorId() const;
    string getStatus() const;
};

class Prescription {
private:
    static int nextId;
    int prescriptionId;
    int patientId;
    int doctorId;
    vector<string> medications;
    vector<string> dosages;
    string dateIssued;

public:
    Prescription(int pId, int dId, const string& date = "");
    void addMedication(const string& med, const string& dosage);
    void display() const;
    int getId() const;
};

class MedicalRecord {
private:
    static int nextId;
    int recordId;
    int patientId;
    int doctorId;
    string diagnosis;
    string treatmentPlan;
    vector<string> testReports;

public:
    MedicalRecord(int pId, int dId, const string& diag, const string& plan);
    void addTestResult(const string& result);
    void updateTreatmentPlan(const string& newPlan);
    void display() const;
    int getId() const;
};

// Hospital staff classes
class Patient : public Person {
private:
    int patientId;
    string bloodGroup;
    vector<string> diseases;
    int assignedDoctorId;
    vector<Appointment> appointments;
    vector<Prescription> prescriptions;
    vector<MedicalRecord> medicalRecords;
    int roomId;

public:
    Patient(int id, string name, int age, string gender, string address, string contactNumber,
            string bloodGroup, int assignedDoctorId);
    void displayDetails() const override;
    void addDisease(const string& disease);
    void displayAppointments() const;
    void displayPrescriptions() const;
    void displayMedicalRecords() const;
    void scheduleAppointment(int doctorId, const string& dateTime);
    void addPrescription(int doctorId);
    void addMedicalRecord(int doctorId, const string& diagnosis, const string& plan);
    void assignRoom(int rId);
    void dischargeFromRoom();
    void getAppointment(int id, Appointment*& appt);
    void getPrescription(int id, Prescription*& presc);
    void getMedicalRecord(int id, MedicalRecord*& record);
    int getRoomId() const;
};

class Doctor : public Staff {
private:
    int doctorId;
    string specialization;
    string licenseNumber;
    vector<string> availableSlots;
    vector<Appointment> appointments;

public:
    Doctor(int id, string name, int age, string gender, string address, string contactNumber,
           double salary, string department, string joinDate, string specialization, string licenseNumber);
    void displayDetails() const override;
    void prescribeMedication(int patientId, const string &medication, const string& dosage);
    void addAvailableSlot(const string& slot);
    void viewAppointments() const;
    void completeAppointment(int apptId, const string& notes);
    void addAppointment(int patientId, const string& dateTime);
    void getAppointment(int id, Appointment*& appt);
};

class Nurse : public Staff {
private:
    int nurseId;
    string shiftTime;
    string qualification;

public:
    Nurse(int id, string name, int age, string gender, string address, string contactNumber,
          double salary, string department, string joinDate, string shiftTime, string qualification);
    void displayDetails() const override;
    void assistDoctor(int doctorId);
    void monitorPatient(int patientId);
};

// Inventory classes
class Medicine {
private:
    static int nextId;
    int medicineId;
    string name;
    double price;
    int quantityInStock;
    string expiryDate;

public:
    Medicine(const string& name, double price, int quantity, const string& expiry);
    void displayDetails() const;
    void checkAvailability(int required) const;
    void updateStock(int quantity);
    int getId() const;
    string getName() const;
    double getPrice() const;
    int getQuantity() const;
};

class Room {
private:
    static int nextId;
    int roomId;
    string type;
    string status;
    int patientId;

public:
    Room(const string& type);
    void displayDetails() const;
    void checkAvailability() const;
    void assignPatient(int pId);
    void vacateRoom();
    int getId() const;
    string getType() const;
    string getStatus() const;
    int getPatientId() const;
};

// Billing class
class Billing {
private:
    static int nextId;
    int billId;
    int patientId;
    double totalAmount;
    string paymentStatus;
    vector<string> servicesAvailed;
    vector<pair<int, int>> medicines;

public:
    Billing(int pId);
    void addService(const string& service, double cost);
    void addMedicine(int medId, int quantity, double price);
    void processPayment(double amount);
    void displayBill() const;
    int getId() const;
    int getPatientId() const;
    double getTotalAmount() const;
    string getPaymentStatus() const;
};

// Hospital system class
class HospitalSystem {
private:
    vector<Person*> persons;
    vector<Medicine*> medicines;
    vector<Room*> rooms;
    vector<Billing*> bills;

public:
    // Person Management
    void addPatient(Patient* patient);
    void addDoctor(Doctor* doctor);
    void addNurse(Nurse* nurse);
    void displayAllPersons() const;
    void findPatient(int id, Patient*& patient);
    void findDoctor(int id, Doctor*& doctor);
    void findNurse(int id, Nurse*& nurse);

    // Medicine Management
    void addMedicine(Medicine* medicine);
    void displayAllMedicines() const;
    void findMedicine(int id, Medicine*& med);

    // Room Management
    void addRoom(Room* room);
    void displayAllRooms() const;
    void findRoom(int id, Room*& room);
    void findAvailableRoom(const string& type, Room*& room);

    // Billing Management
    void createBill(int patientId, Billing*& bill);
    void displayAllBills() const;
    void findPatientBill(int patientId, Billing*& bill);
};

// Creation functions
void createPatient(Patient*& patient);
void createDoctor(Doctor*& doctor);
void createNurse(Nurse*& nurse);
void createMedicine(Medicine*& medicine);
void createRoom(Room*& room);

// Operation functions
void patientOperations(HospitalSystem& hospital, Patient* patient);
void doctorOperations(Doctor* doctor);
void nurseOperations(Nurse* nurse);
void inventoryOperations(HospitalSystem& hospital);
void billingOperations(HospitalSystem& hospital);
