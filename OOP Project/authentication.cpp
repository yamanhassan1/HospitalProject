#include "authentication.h"

// UserCredentials implementation

// Constructor for UserCredentials class
UserCredentials::UserCredentials(const string& uname, const string& pwd, const string& r)
    : username(uname), password(pwd), role(r) {}  // Initializes username, password, and role with provided values

// Method to authenticate user by comparing provided credentials with stored ones
bool UserCredentials::authenticate(const string& uname, const string& pwd) const {
    return (username == uname && password == pwd);  // Returns true if both username and password match
}

// Method to reset the user's password
void UserCredentials::resetPassword(const string& newPwd) {
    password = newPwd;  // Updates the password with the new one
    cout << "\nPassword reset successfully!\n";  // Prints success message
}

// Getter method for user's role
string UserCredentials::getRole() const { return role; }

// Getter method for username
string UserCredentials::getUsername() const { return username; }

// AuthenticationSystem implementation

// Method to add a new user to the system
void AuthenticationSystem::addUser(const string& username, const string& password, const string& role) {
    users.push_back(make_pair(username, new UserCredentials(username, password, role)));  // Creates new UserCredentials and adds to users vector
}

// Method to handle user login
void AuthenticationSystem::login(string& role) {
    string username, password;
    cout << "\nEnter username: ";  // Prompts for username
    cin >> username;              // Reads username input
    cout << "Enter password: ";   // Prompts for password
    cin >> password;              // Reads password input

    // Iterates through all users to find a match
    for (const auto& user : users) {
        if (user.second->authenticate(username, password)) {  // Checks credentials
            cout << "\nLogin successful as " << user.second->getRole() << "\n";  // Success message
            role = user.second->getRole();  // Sets the role parameter to the user's role
            return;                         // Exits after successful login
        }
    }
    cout << "\nInvalid username or password!\n";  // Error message if no match found
    role = "";                                    // Sets role to empty string on failure
}

// Method to handle user logout
void AuthenticationSystem::logout() {
    cout << "\nLogged out successfully!\n";  // Prints logout message
}

// Method to reset a user's password
void AuthenticationSystem::resetPassword(const string& username) {
    // Searches for user by username
    for (auto& user : users) {
        if (user.first == username) {  // If user found
            string newPassword;
            cout << "\nEnter new password: ";  // Prompts for new password
            cin >> newPassword;                // Reads new password
            user.second->resetPassword(newPassword);  // Calls resetPassword on UserCredentials object
            return;                             // Exits after reset
        }
    }
    cout << "\nUser not found!\n";  // Error message if user not found
}