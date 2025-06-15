#include "hospital.h"  // Main hospital system header

// ========== UTILITY FUNCTIONS ========== //

// Clears console screen (cross-platform)
void clearScreen() {
    #ifdef _WIN32
        system("cls");  // Windows command
    #else
        system("clear");  // Unix/Linux/Mac command
    #endif
}

// Displays formatted header with title
void displayHeader(const string& title) {
    clearScreen();  // Clear screen first
    cout << "=========================================================\n";
    cout << "  " << title << "   \n";  // Centered title
    cout << "=========================================================\n\n";
}

// Pauses execution until Enter is pressed
void pressEnterToContinue() {
    cout << "\nPress Enter to continue...";
    cin.ignore();  // Clear input buffer
    cin.get();     // Wait for Enter key
}

// ========== CREATION FUNCTIONS ========== //

// Creates new patient with user input
void createPatient(Patient*& patient) {
    displayHeader("REGISTER NEW PATIENT");
    
    // Declare all needed variables
    int id, age, doctorId;
    string name, gender, address, contact, bloodGroup;
    
    // Get input for each field
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
    
    // Create new Patient object
    patient = new Patient(id, name, age, gender, address, contact, bloodGroup, doctorId);
}

// Creates new doctor with user input
void createDoctor(Doctor*& doctor) {
    displayHeader("REGISTER NEW DOCTOR");
    
    int id, age;
    double salary;
    string name, gender, address, contact, department, joinDate, specialization, license;
    
    // Get input for each field
    cout << "Enter Doctor ID: ";
    cin >> id;
    cin.ignore();
    
    cout << "Enter Full Name: ";
    getline(cin, name);
    
    cout << "Enter Age: ";
    cin >> age;
    cin.ignore();
    
    // ... (additional input collection)
    
    doctor = new Doctor(id, name, age, gender, address, contact, salary, department, 
                       joinDate, specialization, license);
}

// Creates new nurse with user input
void createNurse(Nurse*& nurse) {
    displayHeader("REGISTER NEW NURSE");
    
    int id, age;
    double salary;
    string name, gender, address, contact, department, joinDate, shift, qualification;
    
    // Get input for each field
    cout << "Enter Nurse ID: ";
    cin >> id;
    cin.ignore();
    
    // ... (additional input collection)
    
    nurse = new Nurse(id, name, age, gender, address, contact, salary, department, 
                     joinDate, shift, qualification);
}

// Creates new medicine with user input
void createMedicine(Medicine*& medicine) {
    displayHeader("ADD NEW MEDICINE");
    
    string name, expiry;
    double price;
    int quantity;
    
    // Get input for each field
    cout << "Enter Medicine Name: ";
    getline(cin, name);
    
    // ... (additional input collection)
    
    medicine = new Medicine(name, price, quantity, expiry);
}

// Creates new room with user input
void createRoom(Room*& room) {
    displayHeader("ADD NEW ROOM");
    
    string type;
    cout << "Enter Room Type (General/ICU/Private): ";
    getline(cin, type);
    
    room = new Room(type);
}

// ========== OPERATION FUNCTIONS ========== //

// Handles all patient-related operations
void patientOperations(HospitalSystem& hospital, Patient* patient) {
    displayHeader("PATIENT OPERATIONS");
    
    int choice;
    do {
        // Display menu options
        cout << "\n1. Book Appointment\n";
        cout << "2. View Appointments\n";
        // ... (other options)
        
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch(choice) {
            case 1: {  // Book appointment
                int doctorId;
                string dateTime;
                cout << "\nEnter Doctor ID: ";
                cin >> doctorId;
                cout << "Enter Date/Time: ";
                getline(cin, dateTime);
                patient->scheduleAppointment(doctorId, dateTime);
                break;
            }
            // ... (other cases)
            case 0:  // Exit
                return;
            default:
                cout << "\nInvalid choice!\n";
        }
        pressEnterToContinue();
    } while (choice != 0);
}

// Handles all doctor-related operations
void doctorOperations(Doctor* doctor) {
    displayHeader("DOCTOR OPERATIONS");
    
    int choice;
    do {
        // Display menu options
        cout << "\n1. Add Available Slot\n";
        // ... (other options)
        
        switch(choice) {
            case 1: {  // Add time slot
                string slot;
                cout << "\nEnter Available Time Slot: ";
                getline(cin, slot);
                doctor->addAvailableSlot(slot);
                break;
            }
            // ... (other cases)
        }
        pressEnterToContinue();
    } while (choice != 0);
}

// Handles all nurse-related operations
void nurseOperations(Nurse* nurse) {
    displayHeader("NURSE OPERATIONS");
    
    int choice;
    do {
        // Display menu options
        cout << "\n1. Assist Doctor\n";
        // ... (other options)
        
        switch(choice) {
            case 1: {  // Assist doctor
                int doctorId;
                cout << "\nEnter Doctor ID: ";
                cin >> doctorId;
                nurse->assistDoctor(doctorId);
                break;
            }
            // ... (other cases)
        }
        pressEnterToContinue();
    } while (choice != 0);
}

// Handles inventory management operations
void inventoryOperations(HospitalSystem& hospital) {
    displayHeader("INVENTORY MANAGEMENT");
    
    int choice;
    do {
        // Display menu options
        cout << "\n1. Add New Medicine\n";
        // ... (other options)
        
        switch(choice) {
            case 1: {  // Add medicine
                Medicine* med;
                createMedicine(med);
                hospital.addMedicine(med);
                break;
            }
            // ... (other cases)
        }
        pressEnterToContinue();
    } while (choice != 0);
}

// Handles billing operations
void billingOperations(HospitalSystem& hospital) {
    displayHeader("BILLING MANAGEMENT");
    
    int choice;
    do {
        // Display menu options
        cout << "\n1. Create New Bill\n";
        // ... (other options)
        
        switch(choice) {
            case 1: {  // Create bill
                int patientId;
                cout << "\nEnter Patient ID: ";
                cin >> patientId;
                Billing* bill;
                hospital.createBill(patientId, bill);
                break;
            }
            // ... (other cases)
        }
        pressEnterToContinue();
    } while (choice != 0);
}