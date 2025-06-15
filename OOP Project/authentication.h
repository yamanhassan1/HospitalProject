#pragma once  // Prevents multiple inclusions of this header file

#include <iostream>   // For input/output operations (cout, cin)
#include <string>     // For string class
#include <vector>     // For vector container
using namespace std;  // Using standard namespace (simplifies code but not recommended for large projects)

// Class representing user credentials (username, password, role)
class UserCredentials {
private:
    string username;  // Stores the user's login name
    string password;  // Stores the user's password (insecure: should be hashed in real applications)
    string role;      // Stores the user's role/privilege level (e.g., "admin", "user")

public:
    // Constructor to initialize credentials
    UserCredentials(const string& uname, const string& pwd, const string& r);
    
    // Method to verify if provided credentials match stored ones
    bool authenticate(const string& uname, const string& pwd) const;
    
    // Method to change the user's password
    void resetPassword(const string& newPwd);
    
    // Getter for user's role
    string getRole() const;
    
    // Getter for username
    string getUsername() const;
};

// Class representing the authentication system that manages multiple users
class AuthenticationSystem {
private:
    // Stores users as pairs of usernames and UserCredentials pointers
    // Using pointers to avoid object slicing and allow polymorphism
    vector<pair<string, UserCredentials*>> users;

public:
    // Adds a new user to the system
    void addUser(const string& username, const string& password, const string& role);
    
    // Attempts to log in a user, returns role through reference parameter
    void login(string& role);
    
    // Logs out the current user (simple implementation)
    void logout();
    
    // Resets password for specified username
    void resetPassword(const string& username);
};