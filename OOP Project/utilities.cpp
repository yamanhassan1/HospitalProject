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
    
    cout << "Enter Gender: ";
    getline(cin, gender);

    cout << "Enter Department: ";
    getline(cin, department);

    cout << "Enter Join Date (DD/MM/YYYY): ";
    getline(cin, joinDate);
    
    cout << "Enter Salary: $";
    cin >> salary;
    cin.ignore();

    cout << "Enter Specialization: ";
    getline(cin, specialization);

    cout << "Enter Licience Number: ";
    cin >> license;
    cin.ignore();

    cout << "Enter Address: ";
    getline(cin, address);
    
    cout << "Enter Contact Number: ";
    getline(cin, contact);

    
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
    
    cout << "Enter Full Name: ";
    getline(cin, name);
    
    cout << "Enter Gender: ";
    getline(cin, gender);

    cout << "Enter Department: ";
    getline(cin, department);

    cout << "Enter Join Date (DD/MM/YYYY): ";
    getline(cin, joinDate);
    
    cout << "Enter Salary: $";
    cin >> salary;
    cin.ignore();

    cout << "Enter Shift Time: ";
    getline(cin, shift);

    cout << "Enter Qualification: ";
    getline(cin, qualification);

    cout << "Enter Address: ";
    getline(cin, address);
    
    cout << "Enter Contact Number: ";
    getline(cin, contact);
    
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

    cout << "Enter Price: ";
    cin >> price;
    cin.ignore();

    cout << "Enter Quantity: ";
    cin >> quantity;
    cin.ignore();

    cout << "Enter Expiry (DD/MM/YYYY): ";
    getline(cin, expiry);
    
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
                
                Room* room;
                hospital.findAvailableRoom(type, room);
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
                    Room* room;
                    hospital.findRoom(patient->getRoomId(), room);
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
// Handles all doctor-related operations
void doctorOperations(Doctor* doctor) {
    displayHeader("DOCTOR OPERATIONS");
    
    int choice;
    do {
        // Display menu options
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

// Handles all nurse-related operations
void nurseOperations(Nurse* nurse) {
    displayHeader("NURSE OPERATIONS");
    
    int choice;
    do {
        // Display menu options
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

// Handles inventory management operations
void inventoryOperations(HospitalSystem& hospital) {
    displayHeader("INVENTORY MANAGEMENT");
    
    int choice;
    do {
        // Display menu options
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
            case 1: {
                Medicine* med;
                createMedicine(med);
                hospital.addMedicine(med);
                break;
            }
            case 2:
                hospital.displayAllMedicines();
                break;
            case 3: {
                int id, quantity;
                cout << "\nEnter Medicine ID: ";
                cin >> id;
                cout << "Enter Required Quantity: ";
                cin >> quantity;
                
                Medicine* med;
                hospital.findMedicine(id, med);
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
                
                Medicine* med;
                hospital.findMedicine(id, med);
                if (med) {
                    med->updateStock(quantity);
                } else {
                    cout << "\nMedicine not found!\n";
                }
                break;
            }
            case 5: {
                Room* room;
                createRoom(room);
                hospital.addRoom(room);
                break;
            }
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

// Handles billing operations
void billingOperations(HospitalSystem& hospital) {
    displayHeader("BILLING MANAGEMENT");
    
    int choice;
    do {
        // Display menu options
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
                Billing* bill;
                hospital.createBill(patientId, bill);
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
                
                Billing* bill;
                hospital.findPatientBill(patientId, bill);
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
                
                Billing* bill;
                hospital.findPatientBill(patientId, bill);
                Medicine* med;
                hospital.findMedicine(medId, med);
                
                if (bill && med) {
                    med->checkAvailability(quantity);
                    bill->addMedicine(medId, quantity, med->getPrice());
                    med->updateStock(-quantity);
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
                
                Billing* bill;
                hospital.findPatientBill(patientId, bill);
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