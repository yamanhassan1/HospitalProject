#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

// ====================== UTILITY FUNCTIONS ======================
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void displayHeader(const string& title) {
    clearScreen();
    cout << "=========================================================\n";
    cout << "  " << title << "   \n";
    cout << "=========================================================\n\n";
}

void pressEnterToContinue() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

// ====================== AUTHENTICATION SYSTEM ======================
class UserCredentials {
private:
    string username;
    string password;
    string role; // Admin/Doctor/Nurse/Patient

public:
    UserCredentials(const string& uname, const string& pwd, const string& r)
        : username(uname), password(pwd), role(r) {}

    bool authenticate(const string& uname, const string& pwd) const {
        return (username == uname && password == pwd);
    }

    void resetPassword(const string& newPwd) {
        password = newPwd;
        cout << "\nPassword reset successfully!\n";
    }

    string getRole() const { return role; }
    string getUsername() const { return username; }
};

class AuthenticationSystem {
private:
    vector<pair<string, UserCredentials*>> users;

public:
    void addUser(const string& username, const string& password, const string& role) {
        users.push_back(make_pair(username, new UserCredentials(username, password, role)));
    }

    string login() {
        string username, password;
        cout << "\nEnter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        for (const auto& user : users) {
            if (user.second->authenticate(username, password)) {
                cout << "\nLogin successful as " << user.second->getRole() << "\n";
                return user.second->getRole();
            }
        }
        cout << "\nInvalid username or password!\n";
        return "";
    }

    void logout() {
        cout << "\nLogged out successfully!\n";
    }

    void resetPassword(const string& username) {
        for (auto& user : users) {
            if (user.first == username) {
                string newPassword;
                cout << "\nEnter new password: ";
                cin >> newPassword;
                user.second->resetPassword(newPassword);
                return;
            }
        }
        cout << "\nUser not found!\n";
    }
};

// ====================== BASE CLASSES ======================
class Person {
protected:
    int id;
    string name;
    int age;
    string gender;
    string address;
    string contactNumber;

public:
    Person(int id, string name, int age, string gender, string address, string contactNumber)
        : id(id), name(name), age(age), gender(gender), address(address), contactNumber(contactNumber) {}

    virtual void displayDetails() const = 0;

    void updateContactInfo(string newAddress, string newContact) {
        address = newAddress;
        contactNumber = newContact;
        cout << "\nContact information updated successfully!\n";
    }

    int getId() const { return id; }
    string getName() const { return name; }
};

class Staff : public Person {
protected:
    int staffId;
    double salary;
    string department;
    string joinDate;

public:
    Staff(int id, string name, int age, string gender, string address, string contactNumber,
          double salary, string department, string joinDate)
        : Person(id, name, age, gender, address, contactNumber),
          staffId(id), salary(salary), department(department), joinDate(joinDate) {}

    void displayDetails() const override {
        cout << "\n=== STAFF DETAILS ===\n";
        cout << "ID: " << staffId << "\n";
        cout << "Name: " << name << "\n";
        cout << "Department: " << department << "\n";
        cout << "Join Date: " << joinDate << "\n";
        cout << "Salary: $" << salary << "\n";
    }
};

// ====================== MEDICAL ENTITY CLASSES ======================
class Appointment {
private:
    static int nextId;
    int appointmentId;
    int patientId;
    int doctorId;
    string dateTime;
    string status; // Pending/Completed/Cancelled
    string diagnosisNotes;

public:
    Appointment(int pId, int dId, const string& dt) 
        : appointmentId(nextId++), patientId(pId), doctorId(dId), 
          dateTime(dt), status("Pending"), diagnosisNotes("") {}

    void completeAppointment(const string& notes) {
        status = "Completed";
        diagnosisNotes = notes;
        cout << "\nAppointment #" << appointmentId << " marked as completed.\n";
    }

    void cancelAppointment() {
        status = "Cancelled";
        cout << "\nAppointment #" << appointmentId << " has been cancelled.\n";
    }

    void displayDetails() const {
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

    int getId() const { return appointmentId; }
    int getPatientId() const { return patientId; }
    int getDoctorId() const { return doctorId; }
    string getStatus() const { return status; }
};
int Appointment::nextId = 1;

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
    Prescription(int pId, int dId, const string& date = "") 
    : prescriptionId(nextId++), patientId(pId), doctorId(dId) {
    dateIssued = date.empty() ? "Current Date" : date;
}

    void addMedication(const string& med, const string& dosage) {
        medications.push_back(med);
        dosages.push_back(dosage);
        cout << "\nAdded " << med << " (" << dosage << ") to prescription #" 
             << prescriptionId << "\n";
    }

    void display() const {
        cout << "\n=== PRESCRIPTION #" << prescriptionId << " ===\n";
        cout << "Patient ID: " << patientId << "\n";
        cout << "Doctor ID: " << doctorId << "\n";
        cout << "Date Issued: " << dateIssued;
        cout << "Medications:\n";
        for (size_t i = 0; i < medications.size(); i++) {
            cout << "- " << medications[i] << " (" << dosages[i] << ")\n";
        }
    }

    int getId() const { return prescriptionId; }
};
int Prescription::nextId = 1;

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
    MedicalRecord(int pId, int dId, const string& diag, const string& plan)
        : recordId(nextId++), patientId(pId), doctorId(dId), 
          diagnosis(diag), treatmentPlan(plan) {}

    void addTestResult(const string& result) {
        testReports.push_back(result);
        cout << "\nAdded test result to record #" << recordId << "\n";
    }

    void updateTreatmentPlan(const string& newPlan) {
        treatmentPlan = newPlan;
        cout << "\nUpdated treatment plan for record #" << recordId << "\n";
    }

    void display() const {
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

    int getId() const { return recordId; }
};
int MedicalRecord::nextId = 1;

// ====================== INVENTORY & BILLING CLASSES ======================
class Medicine {
private:
    static int nextId;
    int medicineId;
    string name;
    double price;
    int quantityInStock;
    string expiryDate;

public:
    Medicine(const string& name, double price, int quantity, const string& expiry)
        : medicineId(nextId++), name(name), price(price), 
          quantityInStock(quantity), expiryDate(expiry) {}

    void displayDetails() const {
        cout << "\n=== MEDICINE DETAILS ===\n";
        cout << "Medicine ID: " << medicineId << "\n";
        cout << "Name: " << name << "\n";
        cout << "Price: $" << price << "\n";
        cout << "Quantity: " << quantityInStock << "\n";
        cout << "Expiry Date: " << expiryDate << "\n";
    }

    bool checkAvailability(int required) const {
        if (quantityInStock >= required) {
            cout << "\n" << required << " units of " << name << " are available.\n";
            return true;
        } else {
            cout << "\nOnly " << quantityInStock << " units of " << name << " available.\n";
            return false;
        }
    }

    void updateStock(int quantity) {
        quantityInStock += quantity;
        if (quantity > 0) {
            cout << "\nAdded " << quantity << " units to stock.\n";
        } else {
            cout << "\nDeducted " << -quantity << " units from stock.\n";
        }
        cout << "Current stock: " << quantityInStock << "\n";
    }

    int getId() const { return medicineId; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantityInStock; }
};
int Medicine::nextId = 1;

class Room {
private:
    static int nextId;
    int roomId;
    string type; // General/ICU/Private
    string status; // Occupied/Vacant
    int patientId; // -1 if vacant

public:
    Room(const string& type) 
        : roomId(nextId++), type(type), status("Vacant"), patientId(-1) {}

    void displayDetails() const {
        cout << "\n=== ROOM DETAILS ===\n";
        cout << "Room ID: " << roomId << "\n";
        cout << "Type: " << type << "\n";
        cout << "Status: " << status << "\n";
        if (status == "Occupied") {
            cout << "Patient ID: " << patientId << "\n";
        }
    }

    bool checkAvailability() const {
        if (status == "Vacant") {
            cout << "\nRoom #" << roomId << " (" << type << ") is available.\n";
            return true;
        } else {
            cout << "\nRoom #" << roomId << " is occupied by patient " << patientId << ".\n";
            return false;
        }
    }

    void assignPatient(int pId) {
        if (status == "Vacant") {
            patientId = pId;
            status = "Occupied";
            cout << "\nPatient " << pId << " assigned to Room #" << roomId << "\n";
        } else {
            cout << "\nRoom is already occupied!\n";
        }
    }

    void vacateRoom() {
        if (status == "Occupied") {
            cout << "\nPatient " << patientId << " discharged from Room #" << roomId << "\n";
            patientId = -1;
            status = "Vacant";
        } else {
            cout << "\nRoom is already vacant!\n";
        }
    }

    int getId() const { return roomId; }
    string getType() const { return type; }
    string getStatus() const { return status; }
    int getPatientId() const { return patientId; }
};
int Room::nextId = 1;

class Billing {
private:
    static int nextId;
    int billId;
    int patientId;
    double totalAmount;
    string paymentStatus; // Paid/Unpaid
    vector<string> servicesAvailed;
    vector<pair<int, int>> medicines; // medicineId, quantity

public:
    Billing(int pId) 
        : billId(nextId++), patientId(pId), totalAmount(0), paymentStatus("Unpaid") {}

    void addService(const string& service, double cost) {
        servicesAvailed.push_back(service);
        totalAmount += cost;
        cout << "\nAdded service: " << service << " ($" << cost << ")\n";
    }

    void addMedicine(int medId, int quantity, double price) {
        medicines.emplace_back(medId, quantity);
        totalAmount += (price * quantity);
        cout << "\nAdded medicine ID " << medId << " (x" << quantity << ") - $" 
             << (price * quantity) << "\n";
    }

    void processPayment(double amount) {
        if (amount >= totalAmount) {
            paymentStatus = "Paid";
            cout << "\nPayment processed. Change: $" << (amount - totalAmount) << "\n";
        } else {
            cout << "\nInsufficient payment! Remaining balance: $" 
                 << (totalAmount - amount) << "\n";
        }
    }

    void displayBill() const {
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

    int getId() const { return billId; }
    int getPatientId() const { return patientId; }
    double getTotalAmount() const { return totalAmount; }
    string getPaymentStatus() const { return paymentStatus; }
};
int Billing::nextId = 1;

// ====================== HOSPITAL STAFF CLASSES ======================
class Patient : public Person {
private:
    int patientId;
    string bloodGroup;
    vector<string> diseases;
    int assignedDoctorId;
    vector<Appointment> appointments;
    vector<Prescription> prescriptions;
    vector<MedicalRecord> medicalRecords;
    int roomId; // -1 if not assigned

public:
    Patient(int id, string name, int age, string gender, string address, string contactNumber,
            string bloodGroup, int assignedDoctorId)
        : Person(id, name, age, gender, address, contactNumber), 
          patientId(id), bloodGroup(bloodGroup), assignedDoctorId(assignedDoctorId), roomId(-1) {}

    void displayDetails() const override {
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

    void addDisease(const string& disease) {
        diseases.push_back(disease);
        cout << "\nAdded medical condition: " << disease << "\n";
    }

    void displayAppointments() const {
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

    void displayPrescriptions() const {
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

    void displayMedicalRecords() const {
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

    void scheduleAppointment(int doctorId, const string& dateTime) {
        appointments.emplace_back(patientId, doctorId, dateTime);
        cout << "\nAppointment scheduled successfully!\n";
    }

    void addPrescription(int doctorId) {
        prescriptions.emplace_back(patientId, doctorId);
        cout << "\nNew prescription created!\n";
    }

    void addMedicalRecord(int doctorId, const string& diagnosis, const string& plan) {
        medicalRecords.emplace_back(patientId, doctorId, diagnosis, plan);
        cout << "\nMedical record created!\n";
    }

    void assignRoom(int rId) {
        roomId = rId;
        cout << "\nAssigned to Room #" << rId << "\n";
    }

    void dischargeFromRoom() {
        roomId = -1;
        cout << "\nDischarged from room\n";
    }

    Appointment* getAppointment(int id) {
        for (auto& appt : appointments) {
            if (appt.getId() == id) return &appt;
        }
        return nullptr;
    }

    Prescription* getPrescription(int id) {
        for (auto& presc : prescriptions) {
            if (presc.getId() == id) return &presc;
        }
        return nullptr;
    }

    MedicalRecord* getMedicalRecord(int id) {
        for (auto& record : medicalRecords) {
            if (record.getId() == id) return &record;
        }
        return nullptr;
    }

    int getRoomId() const { return roomId; }
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
           double salary, string department, string joinDate, string specialization, string licenseNumber)
        : Staff(id, name, age, gender, address, contactNumber, salary, department, joinDate),
          doctorId(id), specialization(specialization), licenseNumber(licenseNumber) {}

    void displayDetails() const override {
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

    void prescribeMedication(int patientId, const string &medication, const string& dosage) {
        cout << "\nPrescription created:\n";
        cout << "Patient ID: " << patientId << "\n";
        cout << "Medication: " << medication << "\n";
        cout << "Dosage: " << dosage << "\n";
    }

    void addAvailableSlot(const string& slot) {
        availableSlots.push_back(slot);
        cout << "\nAdded available slot: " << slot << "\n";
    }

    void viewAppointments() const {
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

    void completeAppointment(int apptId, const string& notes) {
        for (auto& appt : appointments) {
            if (appt.getId() == apptId && appt.getStatus() == "Pending") {
                appt.completeAppointment(notes);
                return;
            }
        }
        cout << "\nAppointment not found or not pending!\n";
    }

    void addAppointment(int patientId, const string& dateTime) {
        appointments.emplace_back(patientId, doctorId, dateTime);
    }

    Appointment* getAppointment(int id) {
        for (auto& appt : appointments) {
            if (appt.getId() == id) return &appt;
        }
        return nullptr;
    }
};

class Nurse : public Staff {
private:
    int nurseId;
    string shiftTime;
    string qualification;

public:
    Nurse(int id, string name, int age, string gender, string address, string contactNumber,
          double salary, string department, string joinDate, string shiftTime, string qualification)
        : Staff(id, name, age, gender, address, contactNumber, salary, department, joinDate),
          nurseId(id), shiftTime(shiftTime), qualification(qualification) {}

    void displayDetails() const override {
        Staff::displayDetails();
        cout << "Shift Time: " << shiftTime << "\n";
        cout << "Qualification: " << qualification << "\n";
    }

    void assistDoctor(int doctorId) {
        cout << "\nNurse " << name << " is now assisting Doctor ID " << doctorId << "\n";
    }

    void monitorPatient(int patientId) {
        cout << "\nNurse " << name << " is now monitoring Patient ID " << patientId << "\n";
    }
};

// ====================== HOSPITAL SYSTEM CLASS ======================
class HospitalSystem {
private:
    vector<Person*> persons;
    vector<Medicine*> medicines;
    vector<Room*> rooms;
    vector<Billing*> bills;

public:
    // Person Management
    void addPatient(Patient* patient) {
        persons.push_back(patient);
    }

    void addDoctor(Doctor* doctor) {
        persons.push_back(doctor);
    }

    void addNurse(Nurse* nurse) {
        persons.push_back(nurse);
    }

    void displayAllPersons() const {
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

    Patient* findPatient(int id) {
        for (auto& person : persons) {
            if (person->getId() == id) {
                if (auto patient = dynamic_cast<Patient*>(person)) {
                    return patient;
                }
            }
        }
        return nullptr;
    }

    Doctor* findDoctor(int id) {
        for (auto& person : persons) {
            if (person->getId() == id) {
                if (auto doctor = dynamic_cast<Doctor*>(person)) {
                    return doctor;
                }
            }
        }
        return nullptr;
    }

    Nurse* findNurse(int id) {
        for (auto& person : persons) {
            if (person->getId() == id) {
                if (auto nurse = dynamic_cast<Nurse*>(person)) {
                    return nurse;
                }
            }
        }
        return nullptr;
    }

    // Medicine Management
    void addMedicine(Medicine* medicine) {
        medicines.push_back(medicine);
        cout << "\nMedicine added successfully!\n";
    }

    void displayAllMedicines() const {
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

    Medicine* findMedicine(int id) {
        for (auto& med : medicines) {
            if (med->getId() == id) return med;
        }
        return nullptr;
    }

    // Room Management
    void addRoom(Room* room) {
        rooms.push_back(room);
        cout << "\nRoom added successfully!\n";
    }

    void displayAllRooms() const {
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

    Room* findRoom(int id) {
        for (auto& room : rooms) {
            if (room->getId() == id) return room;
        }
        return nullptr;
    }

    Room* findAvailableRoom(const string& type) {
        for (auto& room : rooms) {
            if (room->getType() == type && room->getStatus() == "Vacant") {
                return room;
            }
        }
        return nullptr;
    }

    // Billing Management
    Billing* createBill(int patientId) {
        bills.push_back(new Billing(patientId));
        cout << "\nNew bill created for patient " << patientId << "\n";
        return bills.back();
    }

    void displayAllBills() const {
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

    Billing* findPatientBill(int patientId) {
        for (auto& bill : bills) {
            if (bill->getPatientId() == patientId && bill->getPaymentStatus() == "Unpaid") {
                return bill;
            }
        }
        return nullptr;
    }
};

// ====================== CREATION FUNCTIONS ======================
Patient* createPatient() {
    displayHeader("REGISTER NEW PATIENT");
    
    int id, age, doctorId;
    string name, gender, address, contact, bloodGroup;
    
    cout << "Enter Patient ID: ";
    cin >> id;
    cin.ignore();
    
    cout << "Enter Full Name: ";
    getline(cin, name);
    
    cout << "Enter Age: ";
    cin >> age;
    cin.ignore();
    
    cout << "Enter Gender: ";
    getline(cin, gender);
    
    cout << "Enter Address: ";
    getline(cin, address);
    
    cout << "Enter Contact Number: ";
    getline(cin, contact);
    
    cout << "Enter Blood Group: ";
    getline(cin, bloodGroup);
    
    cout << "Enter Assigned Doctor ID: ";
    cin >> doctorId;
    
    return new Patient(id, name, age, gender, address, contact, bloodGroup, doctorId);
}

Doctor* createDoctor() {
    displayHeader("REGISTER NEW DOCTOR");
    
    int id, age;
    double salary;
    string name, gender, address, contact, department, joinDate, specialization, license;
    
    cout << "Enter Doctor ID: ";
    cin >> id;
    cin.ignore();
    
    cout << "Enter Full Name: ";
    getline(cin, name);
    
    cout << "Enter Age: ";
    cin >> age;
    cin.ignore();
    
    cout << "Enter Gender: ";
    getline(cin, gender);
    
    cout << "Enter Address: ";
    getline(cin, address);
    
    cout << "Enter Contact Number: ";
    getline(cin, contact);
    
    cout << "Enter Salary: $";
    cin >> salary;
    cin.ignore();
    
    cout << "Enter Department: ";
    getline(cin, department);
    
    cout << "Enter Join Date (DD/MM/YYYY): ";
    getline(cin, joinDate);
    
    cout << "Enter Specialization: ";
    getline(cin, specialization);
    
    cout << "Enter License Number: ";
    getline(cin, license);
    
    return new Doctor(id, name, age, gender, address, contact, salary, department, joinDate, specialization, license);
}

Nurse* createNurse() {
    displayHeader("REGISTER NEW NURSE");
    
    int id, age;
    double salary;
    string name, gender, address, contact, department, joinDate, shift, qualification;
    
    cout << "Enter Nurse ID: ";
    cin >> id;
    cin.ignore();
    
    cout << "Enter Full Name: ";
    getline(cin, name);
    
    cout << "Enter Age: ";
    cin >> age;
    cin.ignore();
    
    cout << "Enter Gender: ";
    getline(cin, gender);
    
    cout << "Enter Address: ";
    getline(cin, address);
    
    cout << "Enter Contact Number: ";
    getline(cin, contact);
    
    cout << "Enter Salary: $";
    cin >> salary;
    cin.ignore();
    
    cout << "Enter Department: ";
    getline(cin, department);
    
    cout << "Enter Join Date (DD/MM/YYYY): ";
    getline(cin, joinDate);
    
    cout << "Enter Shift Time (Morning/Evening/Night): ";
    getline(cin, shift);
    
    cout << "Enter Qualification: ";
    getline(cin, qualification);
    
    return new Nurse(id, name, age, gender, address, contact, salary, department, joinDate, shift, qualification);
}

Medicine* createMedicine() {
    displayHeader("ADD NEW MEDICINE");
    
    string name, expiry;
    double price;
    int quantity;
    
    cout << "Enter Medicine Name: ";
    getline(cin, name);
    cout << "Enter Price: $";
    cin >> price;
    cout << "Enter Quantity: ";
    cin >> quantity;
    cin.ignore();
    cout << "Enter Expiry Date (DD/MM/YYYY): ";
    getline(cin, expiry);
    
    return new Medicine(name, price, quantity, expiry);
}

Room* createRoom() {
    displayHeader("ADD NEW ROOM");
    
    string type;
    cout << "Enter Room Type (General/ICU/Private): ";
    getline(cin, type);
    
    return new Room(type);
}

// ====================== OPERATION FUNCTIONS ======================
void patientOperations(HospitalSystem& hospital, Patient* patient) {
    displayHeader("PATIENT OPERATIONS");
    
    int choice;
    do {
        cout << "\n1. Book Appointment\n";
        cout << "2. View Appointments\n";
        cout << "3. View Prescriptions\n";
        cout << "4. View Medical Records\n";
        cout << "5. Add Medical Condition\n";
        cout << "6. Update Contact Info\n";
        cout << "7. View Details\n";
        cout << "8. Assign to Room\n";
        cout << "9. Discharge from Room\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1: {
                int doctorId;
                string dateTime;
                cout << "\nEnter Doctor ID: ";
                cin >> doctorId;
                cout << "Enter Date/Time (DD/MM/YYYY HH:MM): ";
                getline(cin, dateTime);
                patient->scheduleAppointment(doctorId, dateTime);
                break;
            }
            case 2:
                patient->displayAppointments();
                break;
            case 3:
                patient->displayPrescriptions();
                break;
            case 4:
                patient->displayMedicalRecords();
                break;
            case 5: {
                string disease;
                cout << "\nEnter Medical Condition: ";
                getline(cin, disease);
                patient->addDisease(disease);
                break;
            }
            case 6: {
                string address, contact;
                cout << "\nEnter New Address: ";
                getline(cin, address);
                cout << "Enter New Contact Number: ";
                getline(cin, contact);
                patient->updateContactInfo(address, contact);
                break;
            }
            case 7:
                patient->displayDetails();
                break;
            case 8: {
                string type;
                cout << "\nEnter Room Type (General/ICU/Private): ";
                getline(cin, type);
                
                Room* room = hospital.findAvailableRoom(type);
                if (room) {
                    room->assignPatient(patient->getId());
                    patient->assignRoom(room->getId());
                } else {
                    cout << "\nNo available " << type << " rooms found!\n";
                }
                break;
            }
            case 9: {
                if (patient->getRoomId() != -1) {
                    Room* room = hospital.findRoom(patient->getRoomId());
                    if (room) {
                        room->vacateRoom();
                    }
                    patient->dischargeFromRoom();
                } else {
                    cout << "\nPatient is not assigned to any room!\n";
                }
                break;
            }
            case 0:
                return;
            default:
                cout << "\nInvalid choice! Please try again.\n";
        }
        pressEnterToContinue();
    } while (choice != 0);
}

void doctorOperations(Doctor* doctor) {
    displayHeader("DOCTOR OPERATIONS");
    
    int choice;
    do {
        cout << "\n1. Add Available Slot\n";
        cout << "2. View Appointments\n";
        cout << "3. Complete Appointment\n";
        cout << "4. Prescribe Medication\n";
        cout << "5. Create Medical Record\n";
        cout << "6. Update Contact Info\n";
        cout << "7. View Details\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1: {
                string slot;
                cout << "\nEnter Available Time Slot (e.g., Monday 9:00 AM): ";
                getline(cin, slot);
                doctor->addAvailableSlot(slot);
                break;
            }
            case 2:
                doctor->viewAppointments();
                break;
            case 3: {
                int apptId;
                string notes;
                cout << "\nEnter Appointment ID to complete: ";
                cin >> apptId;
                cin.ignore();
                cout << "Enter Diagnosis Notes: ";
                getline(cin, notes);
                doctor->completeAppointment(apptId, notes);
                break;
            }
            case 4: {
                int patientId;
                string med, dosage;
                cout << "\nEnter Patient ID: ";
                cin >> patientId;
                cin.ignore();
                cout << "Enter Medication Name: ";
                getline(cin, med);
                cout << "Enter Dosage Instructions: ";
                getline(cin, dosage);
                doctor->prescribeMedication(patientId, med, dosage);
                break;
            }
            case 5: {
                int patientId;
                string diagnosis, plan;
                cout << "\nEnter Patient ID: ";
                cin >> patientId;
                cin.ignore();
                cout << "Enter Diagnosis: ";
                getline(cin, diagnosis);
                cout << "Enter Treatment Plan: ";
                getline(cin, plan);
                doctor->addAppointment(patientId, "");
                break;
            }
            case 6: {
                string address, contact;
                cout << "\nEnter New Address: ";
                getline(cin, address);
                cout << "Enter New Contact Number: ";
                getline(cin, contact);
                doctor->updateContactInfo(address, contact);
                break;
            }
            case 7:
                doctor->displayDetails();
                break;
            case 0:
                return;
            default:
                cout <<"\nInvalid choice! Please try again.\n";
        }
        pressEnterToContinue();
    } while (choice != 0);
}

void nurseOperations(Nurse* nurse) {
    displayHeader("NURSE OPERATIONS");
    
    int choice;
    do {
        cout << "\n1. Assist Doctor\n";
        cout << "2. Monitor Patient\n";
        cout << "3. Update Contact Info\n";
        cout << "4. View Details\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1: {
                int doctorId;
                cout << "\nEnter Doctor ID to Assist: ";
                cin >> doctorId;
                nurse->assistDoctor(doctorId);
                break;
            }
            case 2: {
                int patientId;
                cout << "\nEnter Patient ID to Monitor: ";
                cin >> patientId;
                nurse->monitorPatient(patientId);
                break;
            }
            case 3: {
                string address, contact;
                cout << "\nEnter New Address: ";
                getline(cin, address);
                cout << "Enter New Contact Number: ";
                getline(cin, contact);
                nurse->updateContactInfo(address, contact);
                break;
            }
            case 4:
                nurse->displayDetails();
                break;
            case 0:
                return;
            default:
                cout << "\nInvalid choice! Please try again.\n";
        }
        pressEnterToContinue();
    } while (choice != 0);
}

void inventoryOperations(HospitalSystem& hospital) {
    displayHeader("INVENTORY MANAGEMENT");
    
    int choice;
    do {
        cout << "\n1. Add New Medicine\n";
        cout << "2. View Medicine Inventory\n";
        cout << "3. Check Medicine Availability\n";
        cout << "4. Update Medicine Stock\n";
        cout << "5. Add New Room\n";
        cout << "6. View Room Status\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1:
                hospital.addMedicine(createMedicine());
                break;
            case 2:
                hospital.displayAllMedicines();
                break;
            case 3: {
                int id, quantity;
                cout << "\nEnter Medicine ID: ";
                cin >> id;
                cout << "Enter Required Quantity: ";
                cin >> quantity;
                
                Medicine* med = hospital.findMedicine(id);
                if (med) {
                    med->checkAvailability(quantity);
                } else {
                    cout << "\nMedicine not found!\n";
                }
                break;
            }
            case 4: {
                int id, quantity;
                cout << "\nEnter Medicine ID: ";
                cin >> id;
                cout << "Enter Quantity to Add/Deduct (use - for deduction): ";
                cin >> quantity;
                
                Medicine* med = hospital.findMedicine(id);
                if (med) {
                    med->updateStock(quantity);
                } else {
                    cout << "\nMedicine not found!\n";
                }
                break;
            }
            case 5:
                hospital.addRoom(createRoom());
                break;
            case 6:
                hospital.displayAllRooms();
                break;
            case 0:
                return;
            default:
                cout << "\nInvalid choice! Please try again.\n";
        }
        pressEnterToContinue();
    } while (choice != 0);
}

void billingOperations(HospitalSystem& hospital) {
    displayHeader("BILLING MANAGEMENT");
    
    int choice;
    do {
        cout << "\n1. Create New Bill\n";
        cout << "2. Add Service to Bill\n";
        cout << "3. Add Medicine to Bill\n";
        cout << "4. Process Payment\n";
        cout << "5. View All Bills\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1: {
                int patientId;
                cout << "\nEnter Patient ID: ";
                cin >> patientId;
                hospital.createBill(patientId);
                break;
            }
            case 2: {
                int patientId;
                string service;
                double cost;
                
                cout << "\nEnter Patient ID: ";
                cin >> patientId;
                cin.ignore();
                cout << "Enter Service Description: ";
                getline(cin, service);
                cout << "Enter Service Cost: $";
                cin >> cost;
                
                Billing* bill = hospital.findPatientBill(patientId);
                if (bill) {
                    bill->addService(service, cost);
                } else {
                    cout << "\nNo unpaid bill found for this patient!\n";
                }
                break;
            }
            case 3: {
                int patientId, medId, quantity;
                cout << "\nEnter Patient ID: ";
                cin >> patientId;
                cout << "Enter Medicine ID: ";
                cin >> medId;
                cout << "Enter Quantity: ";
                cin >> quantity;
                
                Billing* bill = hospital.findPatientBill(patientId);
                Medicine* med = hospital.findMedicine(medId);
                
                if (bill && med) {
                    if (med->checkAvailability(quantity)) {
                        bill->addMedicine(medId, quantity, med->getPrice());
                        med->updateStock(-quantity);
                    }
                } else {
                    cout << "\nBill or medicine not found!\n";
                }
                break;
            }
            case 4: {
                int patientId;
                double amount;
                cout << "\nEnter Patient ID: ";
                cin >> patientId;
                cout << "Enter Payment Amount: $";
                cin >> amount;
                
                Billing* bill = hospital.findPatientBill(patientId);
                if (bill) {
                    bill->processPayment(amount);
                } else {
                    cout << "\nNo unpaid bill found for this patient!\n";
                }
                break;
            }
            case 5:
                hospital.displayAllBills();
                break;
            case 0:
                return;
            default:
                cout << "\nInvalid choice! Please try again.\n";
        }
        pressEnterToContinue();
    } while (choice != 0);
}

// ====================== MAIN FUNCTION ======================
int main() {
    HospitalSystem hospital;
    string hospitalName = "City General Hospital";
    string currentRole;
    
    // Create initial sample data
    hospital.addPatient(new Patient(101, "John Smith", 35, "Male", "123 Main St", "555-1234", "O+", 201));
    hospital.addDoctor(new Doctor(201, "Dr. Sarah Johnson", 45, "Female", "456 Oak Ave", "555-5678", 150000, "Cardiology", "01/01/2010", "Cardiologist", "MD12345"));
    hospital.addNurse(new Nurse(301, "Emily Davis", 28, "Female", "789 Pine Rd", "555-9012", 65000, "Cardiology", "15/06/2018", "Day", "RN"));
    hospital.addMedicine(new Medicine("Paracetamol", 5.99, 100, "01/01/2025"));
    hospital.addMedicine(new Medicine("Ibuprofen", 8.50, 75, "01/06/2024"));
    hospital.addRoom(new Room("General"));
    hospital.addRoom(new Room("ICU"));
    hospital.addRoom(new Room("Private"));

    // Main menu
    int mainChoice;
    do {
        displayHeader(hospitalName + " - HOSPITAL MANAGEMENT SYSTEM");
        cout << "||==================================||\n";
        cout << "||\t1. Login                    ||\n";
        cout << "||==================================||\n";
        cout << "||\t2. Reset Password           ||\n";
        cout << "||==================================||\n";
        cout << "||\t3. Quick Access (No Login)  ||\n";
        cout << "||==================================||\n";
        cout << "||\t0. Exit                     ||\n";
        cout << "||==================================||\n";
        cout << "||\tEnter your choice: ";
        cin >> mainChoice;
        cin.ignore();
        cout << "||==================================||\n";
        switch(mainChoice) {
            case 1: {
                // Simplified login - in real system would verify credentials
                cout << "\nSelect your role (Admin/Doctor/Nurse/Patient): ";
                getline(cin, currentRole);
                
                if (currentRole == "Admin" || currentRole == "Doctor" || 
                    currentRole == "Nurse" || currentRole == "Patient") {
                    cout << "\nLogged in as " << currentRole << "\n";
                    
                    // Role-specific menu
                    int roleChoice;
                    do {
                        displayHeader(hospitalName + " - " + currentRole + " Dashboard");
                        
                        // Common options
                        cout << "1. View My Profile\n";
                        cout << "2. Update Contact Information\n";
                        
                        // Admin-specific options
                        if (currentRole == "Admin") {
                            cout << "3. Register New Staff\n";
                            cout << "4. View All Records\n";
                            cout << "5. Inventory Management\n";
                            cout << "6. Billing Management\n";
                            cout << "7. Room Management\n";
                        }
                        // Doctor-specific options
                        else if (currentRole == "Doctor") {
                            cout << "3. View Appointments\n";
                            cout << "4. Complete Appointment\n";
                            cout << "5. Prescribe Medication\n";
                            cout << "6. Create Medical Record\n";
                        }
                        // Nurse-specific options
                        else if (currentRole == "Nurse") {
                            cout << "3. Assist Doctor\n";
                            cout << "4. Monitor Patient\n";
                            cout << "5. View Room Assignments\n";
                        }
                        // Patient-specific options
                        else if (currentRole == "Patient") {
                            cout << "3. Book Appointment\n";
                            cout << "4. View Medical History\n";
                            cout << "5. View Prescriptions\n";
                            cout << "6. Pay Bill\n";
                        }
                        
                        cout << "0. Logout\n";
                        cout << "Enter your choice: ";
                        cin >> roleChoice;
                        cin.ignore();

                        switch(roleChoice) {
                            case 1: {
                                // View profile based on role
                                int id;
                                cout << "\nEnter your ID: ";
                                cin >> id;
                                if (currentRole == "Doctor") {
                                    Doctor* doctor = hospital.findDoctor(id);
                                    if (doctor) doctor->displayDetails();
                                    else cout << "\nDoctor not found!\n";
                                } 
                                else if (currentRole == "Nurse") {
                                    Nurse* nurse = hospital.findNurse(id);
                                    if (nurse) nurse->displayDetails();
                                    else cout << "\nNurse not found!\n";
                                }
                                else if (currentRole == "Patient") {
                                    Patient* patient = hospital.findPatient(id);
                                    if (patient) patient->displayDetails();
                                    else cout << "\nPatient not found!\n";
                                }
                                break;
                            }
                            case 2: {
                                // Update contact info
                                int id;
                                string address, contact;
                                cout << "\nEnter your ID: ";
                                cin >> id;
                                cin.ignore();
                                cout << "Enter new address: ";
                                getline(cin, address);
                                cout << "Enter new contact number: ";
                                getline(cin, contact);
                                
                                if (currentRole == "Doctor") {
                                    Doctor* doctor = hospital.findDoctor(id);
                                    if (doctor) doctor->updateContactInfo(address, contact);
                                }
                                else if (currentRole == "Nurse") {
                                    Nurse* nurse = hospital.findNurse(id);
                                    if (nurse) nurse->updateContactInfo(address, contact);
                                }
                                else if (currentRole == "Patient") {
                                    Patient* patient = hospital.findPatient(id);
                                    if (patient) patient->updateContactInfo(address, contact);
                                }
                                break;
                            }
                            // Admin options
                            case 3: 
                                if (currentRole == "Admin") {
                                    cout << "\n1. Register Doctor\n2. Register Nurse\nChoice: ";
                                    int regChoice;
                                    cin >> regChoice;
                                    if (regChoice == 1) {
                                        hospital.addDoctor(createDoctor());
                                    } else {
                                        hospital.addNurse(createNurse());
                                    }
                                }
                                // Doctor options
                                else if (currentRole == "Doctor") {
                                    int id;
                                    cout << "\nEnter your Doctor ID: ";
                                    cin >> id;
                                    Doctor* doctor = hospital.findDoctor(id);
                                    if (doctor) doctor->viewAppointments();
                                }
                                // Nurse options
                                else if (currentRole == "Nurse") {
                                    int id, doctorId;
                                    cout << "\nEnter Doctor ID to assist: ";
                                    cin >> doctorId;
                                    Nurse* nurse = hospital.findNurse(id);
                                    if (nurse) nurse->assistDoctor(doctorId);
                                }
                                // Patient options
                                else if (currentRole == "Patient") {
                                    int id, doctorId;
                                    string date;
                                    cout << "\nEnter your Patient ID: ";
                                    cin >> id;
                                    Patient* patient = hospital.findPatient(id);
                                    if (patient) {
                                        cout << "Enter Doctor ID: ";
                                        cin >> doctorId;
                                        cin.ignore();
                                        cout << "Enter Date/Time (DD/MM/YYYY HH:MM): ";
                                        getline(cin, date);
                                        patient->scheduleAppointment(doctorId, date);
                                    }
                                }
                                break;
                            // Continue with other cases...
                            case 0:
                                currentRole = "";
                                cout << "\nLogged out successfully.\n";
                                break;
                            default:
                                cout << "\nInvalid choice!\n";
                        }
                        pressEnterToContinue();
                    } while (currentRole != "");
                } else {
                    cout << "\nInvalid role!\n";
                }
                break;
            }
            case 2: {
                // Simplified password reset - in real system would have proper auth
                string username;
                cout << "\nEnter username: ";
                getline(cin, username);
                cout << "\nPassword reset link sent (simulated)\n";
                break;
            }
            case 3: {
                // Quick access without login (for demo purposes)
                int quickChoice;
                do {
                    displayHeader(hospitalName + " - QUICK ACCESS MENU");
                    cout << "1. Register New Patient\n";
                    cout << "2. View All Records\n";
                    cout << "3. Patient Operations\n";
                    cout << "4. Doctor Operations\n";
                    cout << "5. Nurse Operations\n";
                    cout << "6. Inventory Management\n";
                    cout << "7. Billing Management\n";
                    cout << "0. Back to Main Menu\n";
                    cout << "Enter your choice: ";
                    cin >> quickChoice;
                    cin.ignore();

                    switch(quickChoice) {
                        case 1:
                            hospital.addPatient(createPatient());
                            break;
                        case 2:
                            hospital.displayAllPersons();
                            break;
                        case 3: {
                            int id;
                            cout << "\nEnter Patient ID: ";
                            cin >> id;
                            Patient* patient = hospital.findPatient(id);
                            if (patient) {
                                patientOperations(hospital, patient);
                            } else {
                                cout << "\nPatient not found!\n";
                            }
                            break;
                        }
                        case 4: {
                            int id;
                            cout << "\nEnter Doctor ID: ";
                            cin >> id;
                            Doctor* doctor = hospital.findDoctor(id);
                            if (doctor) {
                                doctorOperations(doctor);
                            } else {
                                cout << "\nDoctor not found!\n";
                            }
                            break;
                        }
                        case 5: {
                            int id;
                            cout << "\nEnter Nurse ID: ";
                            cin >> id;
                            Nurse* nurse = hospital.findNurse(id);
                            if (nurse) {
                                nurseOperations(nurse);
                            } else {
                                cout << "\nNurse not found!\n";
                            }
                            break;
                        }
                        case 6:
                            inventoryOperations(hospital);
                            break;
                        case 7:
                            billingOperations(hospital);
                            break;
                        case 0:
                            break;
                        default:
                            cout << "\nInvalid choice!\n";
                    }
                    if (quickChoice != 0) pressEnterToContinue();
                } while (quickChoice != 0);
                break;
            }
            case 0:
                cout << "\nExiting system. Goodbye!\n";
                break;
            default:
                cout << "\nInvalid choice!\n";
        }
        if (mainChoice != 0) pressEnterToContinue();
    } while (mainChoice != 0);

    return 0;
}
