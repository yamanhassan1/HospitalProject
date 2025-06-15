#include "authentication.h"

// UserCredentials implementation
UserCredentials::UserCredentials(const string& uname, const string& pwd, const string& r)
    : username(uname), password(pwd), role(r) {}

bool UserCredentials::authenticate(const string& uname, const string& pwd) const {
    return (username == uname && password == pwd);
}

void UserCredentials::resetPassword(const string& newPwd) {
    password = newPwd;
    cout << "\nPassword reset successfully!\n";
}

string UserCredentials::getRole() const { return role; }
string UserCredentials::getUsername() const { return username; }

// AuthenticationSystem implementation
void AuthenticationSystem::addUser(const string& username, const string& password, const string& role) {
    users.push_back(make_pair(username, new UserCredentials(username, password, role)));
}

void AuthenticationSystem::login(string& role) {
    string username, password;
    cout << "\nEnter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    for (const auto& user : users) {
        if (user.second->authenticate(username, password)) {
            cout << "\nLogin successful as " << user.second->getRole() << "\n";
            role = user.second->getRole();
            return;
        }
    }
    cout << "\nInvalid username or password!\n";
    role = "";
}

void AuthenticationSystem::logout() {
    cout << "\nLogged out successfully!\n";
}

void AuthenticationSystem::resetPassword(const string& username) {
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