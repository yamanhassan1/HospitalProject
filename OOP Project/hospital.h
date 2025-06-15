#pragma once  // Header guard to prevent multiple inclusions

// Standard library includes
#include <iostream>   // For input/output operations
#include <vector>     // For dynamic array containers
#include <ctime>      // For date/time handling
#include <string>     // For string operations
using namespace std;  // Standard namespace (note: generally avoided in headers)

// Forward declarations of all classes to resolve circular dependencies
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

// Utility function declarations
void clearScreen();                     // Clears console screen
void displayHeader(const string& title);// Displays formatted section headers
void pressEnterToContinue();            // Pauses execution until Enter key

// Base Person class (abstract)
class Person {
protected:
    int id;                // Unique identifier
    string name;           // Full name
    int age;               // Age in years
    string gender;         // Gender identity
    string address;        // Physical address
    string contactNumber;  // Phone number

public:
    // Constructor initializes all basic person attributes
    Person(int id, string name, int age, string gender, string address, string contactNumber);
    
    // Pure virtual function makes this an abstract class
    virtual void displayDetails() const = 0;
    
    // Updates contact information
    void updateContactInfo(string newAddress, string newContact);
    
    // Accessor methods
    int getId() const;
    string getName() const;
};

// Staff base class (inherits from Person)
class Staff : public Person {
protected:
    int staffId;         // Staff-specific ID
    double salary;       // Monthly compensation
    string department;   // Department assignment
    string joinDate;     // Employment start date

public:
    // Constructor adds staff-specific attributes
    Staff(int id, string name, int age, string gender, string address, string contactNumber,
          double salary, string department, string joinDate);
    
    // Displays staff details (override from Person)
    void displayDetails() const override;
};

// Appointment management class
class Appointment {
private:
    static int nextId;       // Tracks next available ID
    int appointmentId;       // Unique appointment ID
    int patientId;           // Associated patient
    int doctorId;            // Assigned doctor
    string dateTime;         // Scheduled date/time
    string status;           // Current status (Pending/Completed/Cancelled)
    string diagnosisNotes;   // Doctor's notes

public:
    // Constructor creates new appointment
    Appointment(int pId, int dId, const string& dt);
    
    // Marks appointment as complete with notes
    void completeAppointment(const string& notes);
    
    // Cancels the appointment
    void cancelAppointment();
    
    // Shows appointment details
    void displayDetails() const;
    
    // Accessor methods
    int getId() const;
    int getPatientId() const;
    int getDoctorId() const;
    string getStatus() const;
};

// Prescription management class
class Prescription {
private:
    static int nextId;           // Tracks next available ID
    int prescriptionId;          // Unique prescription ID
    int patientId;               // Associated patient
    int doctorId;                // Prescribing doctor
    vector<string> medications;  // List of prescribed drugs
    vector<string> dosages;      // Corresponding dosages
    string dateIssued;           // Creation date

public:
    // Constructor creates new prescription
    Prescription(int pId, int dId, const string& date = "");
    
    // Adds medication to prescription
    void addMedication(const string& med, const string& dosage);
    
    // Displays prescription details
    void display() const;
    
    // Accessor method
    int getId() const;
};

// Medical record management class
class MedicalRecord {
private:
    static int nextId;           // Tracks next available ID
    int recordId;                // Unique record ID
    int patientId;               // Associated patient
    int doctorId;                // Attending doctor
    string diagnosis;            // Medical diagnosis
    string treatmentPlan;        // Recommended treatment
    vector<string> testReports;  // Lab/test results

public:
    // Constructor creates new medical record
    MedicalRecord(int pId, int dId, const string& diag, const string& plan);
    
    // Adds test result to record
    void addTestResult(const string& result);
    
    // Updates treatment plan
    void updateTreatmentPlan(const string& newPlan);
    
    // Displays record details
    void display() const;
    
    // Accessor method
    int getId() const;
};

// Patient class (inherits from Person)
class Patient : public Person {
private:
    int patientId;                         // Patient-specific ID
    string bloodGroup;                     // Blood type
    vector<string> diseases;               // Known conditions
    int assignedDoctorId;                   // Primary physician
    vector<Appointment> appointments;      // Scheduled appointments
    vector<Prescription> prescriptions;    // Medication history
    vector<MedicalRecord> medicalRecords;  // Health records
    int roomId;                            // Assigned room (-1 if none)

public:
    // Constructor adds patient-specific attributes
    Patient(int id, string name, int age, string gender, string address, string contactNumber,
            string bloodGroup, int assignedDoctorId);
    
    // Displays patient details (override from Person)
    void displayDetails() const override;
    
    // Adds diagnosed condition
    void addDisease(const string& disease);
    
    // Display methods for patient data
    void displayAppointments() const;
    void displayPrescriptions() const;
    void displayMedicalRecords() const;
    
    // Management methods
    void scheduleAppointment(int doctorId, const string& dateTime);
    void addPrescription(int doctorId);
    void addMedicalRecord(int doctorId, const string& diagnosis, const string& plan);
    void assignRoom(int rId);
    void dischargeFromRoom();
    
    // Search methods
    void getAppointment(int id, Appointment*& appt);
    void getPrescription(int id, Prescription*& presc);
    void getMedicalRecord(int id, MedicalRecord*& record);
    
    // Accessor method
    int getRoomId() const;
};

// Doctor class (inherits from Staff)
class Doctor : public Staff {
private:
    int doctorId;                   // Doctor-specific ID
    string specialization;          // Medical specialty
    string licenseNumber;           // Professional license
    vector<string> availableSlots;   // Open appointment times
    vector<Appointment> appointments; // Scheduled appointments

public:
    // Constructor adds doctor-specific attributes
    Doctor(int id, string name, int age, string gender, string address, string contactNumber,
           double salary, string department, string joinDate, string specialization, string licenseNumber);
    
    // Displays doctor details (override from Staff)
    void displayDetails() const override;
    
    // Prescribes medication to patient
    void prescribeMedication(int patientId, const string &medication, const string& dosage);
    
    // Manages availability
    void addAvailableSlot(const string& slot);
    
    // Appointment management
    void viewAppointments() const;
    void completeAppointment(int apptId, const string& notes);
    void addAppointment(int patientId, const string& dateTime);
    
    // Search method
    void getAppointment(int id, Appointment*& appt);
};

// Nurse class (inherits from Staff)
class Nurse : public Staff {
private:
    int nurseId;            // Nurse-specific ID
    string shiftTime;       // Work schedule
    string qualification;   // Professional credentials

public:
    // Constructor adds nurse-specific attributes
    Nurse(int id, string name, int age, string gender, string address, string contactNumber,
          double salary, string department, string joinDate, string shiftTime, string qualification);
    
    // Displays nurse details (override from Staff)
    void displayDetails() const override;
    
    // Work methods
    void assistDoctor(int doctorId);
    void monitorPatient(int patientId);
};

// Medicine inventory class
class Medicine {
private:
    static int nextId;          // Tracks next available ID
    int medicineId;             // Unique medicine ID
    string name;                // Drug name
    double price;               // Unit price
    int quantityInStock;        // Current inventory
    string expiryDate;          // Shelf life

public:
    // Constructor creates medicine entry
    Medicine(const string& name, double price, int quantity, const string& expiry);
    
    // Displays medicine details
    void displayDetails() const;
    
    // Inventory management
    void checkAvailability(int required) const;
    void updateStock(int quantity);
    
    // Accessor methods
    int getId() const;
    string getName() const;
    double getPrice() const;
    int getQuantity() const;
};

// Room management class
class Room {
private:
    static int nextId;    // Tracks next available ID
    int roomId;           // Unique room number
    string type;          // Room category (General/ICU/OR)
    string status;        // Vacant/Occupied
    int patientId;        // Current occupant (-1 if vacant)

public:
    // Constructor creates room
    Room(const string& type);
    
    // Displays room details
    void displayDetails() const;
    
    // Status methods
    void checkAvailability() const;
    void assignPatient(int pId);
    void vacateRoom();
    
    // Accessor methods
    int getId() const;
    string getType() const;
    string getStatus() const;
    int getPatientId() const;
};

// Billing system class
class Billing {
private:
    static int nextId;            // Tracks next available ID
    int billId;                   // Unique bill number
    int patientId;                // Associated patient
    double totalAmount;           // Charges total
    string paymentStatus;         // Paid/Unpaid
    vector<string> servicesAvailed; // Medical services
    vector<pair<int, int>> medicines; // (Medicine ID, Quantity) pairs

public:
    // Constructor creates new bill
    Billing(int pId);
    
    // Adds service charge
    void addService(const string& service, double cost);
    
    // Adds medication charge
    void addMedicine(int medId, int quantity, double price);
    
    // Processes payment
    void processPayment(double amount);
    
    // Displays detailed bill
    void displayBill() const;
    
    // Accessor methods
    int getId() const;
    int getPatientId() const;
    double getTotalAmount() const;
    string getPaymentStatus() const;
};

// Main hospital management system
class HospitalSystem {
private:
    vector<Person*> persons;      // All people (patients/staff)
    vector<Medicine*> medicines;  // Medicine inventory
    vector<Room*> rooms;          // Room inventory
    vector<Billing*> bills;       // Financial records

public:
    // Person management
    void addPatient(Patient* patient);
    void addDoctor(Doctor* doctor);
    void addNurse(Nurse* nurse);
    void displayAllPersons() const;
    void findPatient(int id, Patient*& patient);
    void findDoctor(int id, Doctor*& doctor);
    void findNurse(int id, Nurse*& nurse);

    // Medicine management
    void addMedicine(Medicine* medicine);
    void displayAllMedicines() const;
    void findMedicine(int id, Medicine*& med);

    // Room management
    void addRoom(Room* room);
    void displayAllRooms() const;
    void findRoom(int id, Room*& room);
    void findAvailableRoom(const string& type, Room*& room);

    // Billing management
    void createBill(int patientId, Billing*& bill);
    void displayAllBills() const;
    void findPatientBill(int patientId, Billing*& bill);
};

// Factory functions for object creation
void createPatient(Patient*& patient);
void createDoctor(Doctor*& doctor);
void createNurse(Nurse*& nurse);
void createMedicine(Medicine*& medicine);
void createRoom(Room*& room);

// Operational menus
void patientOperations(HospitalSystem& hospital, Patient* patient);
void doctorOperations(Doctor* doctor);
void nurseOperations(Nurse* nurse);
void inventoryOperations(HospitalSystem& hospital);
void billingOperations(HospitalSystem& hospital);