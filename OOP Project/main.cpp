#include "hospital.h"         // Main hospital management system header
#include "authentication.h"   // User authentication system
using namespace std;

int main() {
    // Initialize hospital system and set name
    HospitalSystem hospital;
    string hospitalName = "City General Hospital";
    string currentRole;  // Tracks logged-in user's role
    
    // ========== SAMPLE DATA INITIALIZATION ========== //
    // Create sample patient with complete details
    Patient* p1 = new Patient(101, "John Smith", 35, "Male", "123 Main St", "555-1234", "O+", 201);
    
    // Create sample doctor with specialization
    Doctor* d1 = new Doctor(201, "Dr. Sarah Johnson", 45, "Female", "456 Oak Ave", "555-5678", 
                          150000, "Cardiology", "01/01/2010", "Cardiologist", "MD12345");
    
    // Create sample nurse with shift info
    Nurse* n1 = new Nurse(301, "Emily Davis", 28, "Female", "789 Pine Rd", "555-9012", 
                        65000, "Cardiology", "15/06/2018", "Day", "RN");
    
    // Create sample medicines
    Medicine* m1 = new Medicine("Paracetamol", 5.99, 100, "01/01/2025");
    Medicine* m2 = new Medicine("Ibuprofen", 8.50, 75, "01/06/2024");
    
    // Create sample rooms of different types
    Room* r1 = new Room("General");
    Room* r2 = new Room("ICU");
    Room* r3 = new Room("Private");

    // Add all sample data to hospital system
    hospital.addPatient(p1);
    hospital.addDoctor(d1);
    hospital.addNurse(n1);
    hospital.addMedicine(m1);
    hospital.addMedicine(m2);
    hospital.addRoom(r1);
    hospital.addRoom(r2);
    hospital.addRoom(r3);

    // ========== MAIN PROGRAM LOOP ========== //
    int mainChoice;
    do {
        // Display main menu with formatted header
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
        cin.ignore();  // Clear input buffer
        cout << "||==================================||\n";

        switch(mainChoice) {
            case 1: {  // Login System
                cout << "\nSelect your role (Admin/Doctor/Nurse/Patient): ";
                getline(cin, currentRole);
                
                // Validate role input
                if (currentRole == "Admin" || currentRole == "Doctor" || 
                    currentRole == "Nurse" || currentRole == "Patient") {
                    cout << "\nLogged in as " << currentRole << "\n";
                    
                    // ========== ROLE-SPECIFIC DASHBOARD ========== //
                    int roleChoice;
                    do {
                        displayHeader(hospitalName + " - " + currentRole + " Dashboard");
                        
                        // Common options for all roles
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

                        // Process role-specific choices
                        switch(roleChoice) {
                            case 1: {  // View Profile
                                int id;
                                cout << "\nEnter your ID: ";
                                cin >> id;
                                // Doctor profile view
                                if (currentRole == "Doctor") {
                                    Doctor* doctor;
                                    hospital.findDoctor(id, doctor);
                                    if (doctor) doctor->displayDetails();
                                    else cout << "\nDoctor not found!\n";
                                } 
                                // Nurse profile view
                                else if (currentRole == "Nurse") {
                                    Nurse* nurse;
                                    hospital.findNurse(id, nurse);
                                    if (nurse) nurse->displayDetails();
                                    else cout << "\nNurse not found!\n";
                                }
                                // Patient profile view
                                else if (currentRole == "Patient") {
                                    Patient* patient;
                                    hospital.findPatient(id, patient);
                                    if (patient) patient->displayDetails();
                                    else cout << "\nPatient not found!\n";
                                }
                                break;
                            }
                            case 2: {  // Update Contact Info
                                int id;
                                string address, contact;
                                cout << "\nEnter your ID: ";
                                cin >> id;
                                cin.ignore();
                                cout << "Enter new address: ";
                                getline(cin, address);
                                cout << "Enter new contact number: ";
                                getline(cin, contact);
                                
                                // Update based on role
                                if (currentRole == "Doctor") {
                                    Doctor* doctor;
                                    hospital.findDoctor(id, doctor);
                                    if (doctor) doctor->updateContactInfo(address, contact);
                                }
                                else if (currentRole == "Nurse") {
                                    Nurse* nurse;
                                    hospital.findNurse(id, nurse);
                                    if (nurse) nurse->updateContactInfo(address, contact);
                                }
                                else if (currentRole == "Patient") {
                                    Patient* patient;
                                    hospital.findPatient(id, patient);
                                    if (patient) patient->updateContactInfo(address, contact);
                                }
                                break;
                            }
                            case 3:  // Role-specific option 3
                                if (currentRole == "Admin") {
                                    // Staff registration
                                    cout << "\n1. Register Doctor\n2. Register Nurse\nChoice: ";
                                    int regChoice;
                                    cin >> regChoice;
                                    if (regChoice == 1) {
                                        Doctor* doctor;
                                        createDoctor(doctor);
                                        hospital.addDoctor(doctor);
                                    } else {
                                        Nurse* nurse;
                                        createNurse(nurse);
                                        hospital.addNurse(nurse);
                                    }
                                }
                                else if (currentRole == "Doctor") {
                                    // View appointments
                                    int id;
                                    cout << "\nEnter your Doctor ID: ";
                                    cin >> id;
                                    Doctor* doctor;
                                    hospital.findDoctor(id, doctor);
                                    if (doctor) doctor->viewAppointments();
                                }
                                else if (currentRole == "Nurse") {
                                    // Assist doctor
                                    int id, doctorId;
                                    cout << "\nEnter Doctor ID to assist: ";
                                    cin >> doctorId;
                                    Nurse* nurse;
                                    hospital.findNurse(id, nurse);
                                    if (nurse) nurse->assistDoctor(doctorId);
                                }
                                else if (currentRole == "Patient") {
                                    // Book appointment
                                    int id, doctorId;
                                    string date;
                                    cout << "\nEnter your Patient ID: ";
                                    cin >> id;
                                    Patient* patient;
                                    hospital.findPatient(id, patient);
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
                            case 0:  // Logout
                                currentRole = "";
                                cout << "\nLogged out successfully.\n";
                                break;
                            default:
                                cout << "\nInvalid choice!\n";
                        }
                        pressEnterToContinue();
                    } while (currentRole != "");  // Continue until logout
                } else {
                    cout << "\nInvalid role!\n";
                }
                break;
            }
            case 2: {  // Password Reset
                string username;
                cout << "\nEnter username: ";
                getline(cin, username);
                cout << "\nPassword reset link sent (simulated)\n";
                break;
            }
            case 3: {  // Quick Access Menu
                int quickChoice;
                do {
                    displayHeader(hospitalName + " - QUICK ACCESS MENU");
                    // Quick access options
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

                    // Process quick access choices
                    switch(quickChoice) {
                        case 1: {  // New patient registration
                            Patient* patient;
                            createPatient(patient);
                            hospital.addPatient(patient);
                            break;
                        }
                        case 2:  // View all records
                            hospital.displayAllPersons();
                            break;
                        case 3: {  // Patient operations
                            int id;
                            cout << "\nEnter Patient ID: ";
                            cin >> id;
                            Patient* patient;
                            hospital.findPatient(id, patient);
                            if (patient) {
                                patientOperations(hospital, patient);
                            } else {
                                cout << "\nPatient not found!\n";
                            }
                            break;
                        }
                        case 4: {  // Doctor operations
                            int id;
                            cout << "\nEnter Doctor ID: ";
                            cin >> id;
                            Doctor* doctor;
                            hospital.findDoctor(id, doctor);
                            if (doctor) {
                                doctorOperations(doctor);
                            } else {
                                cout << "\nDoctor not found!\n";
                            }
                            break;
                        }
                        case 5: {  // Nurse operations
                            int id;
                            cout << "\nEnter Nurse ID: ";
                            cin >> id;
                            Nurse* nurse;
                            hospital.findNurse(id, nurse);
                            if (nurse) {
                                nurseOperations(nurse);
                            } else {
                                cout << "\nNurse not found!\n";
                            }
                            break;
                        }
                        case 6:  // Inventory management
                            inventoryOperations(hospital);
                            break;
                        case 7:  // Billing management
                            billingOperations(hospital);
                            break;
                        case 0:  // Return to main menu
                            break;
                        default:
                            cout << "\nInvalid choice!\n";
                    }
                    if (quickChoice != 0) pressEnterToContinue();
                } while (quickChoice != 0);
                break;
            }
            case 0:  // Exit system
                cout << "\nExiting system. Goodbye!\n";
                break;
            default:
                cout << "\nInvalid choice!\n";
        }
        if (mainChoice != 0) pressEnterToContinue();
    } while (mainChoice != 0);  // Continue until exit

    return 0;
}