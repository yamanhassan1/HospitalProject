#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class UserCredentials {
private:
    string username;
    string password;
    string role;

public:
    UserCredentials(const string& uname, const string& pwd, const string& r);
    bool authenticate(const string& uname, const string& pwd) const;
    void resetPassword(const string& newPwd);
    string getRole() const;
    string getUsername() const;
};

class AuthenticationSystem {
private:
    vector<pair<string, UserCredentials*>> users;

public:
    void addUser(const string& username, const string& password, const string& role);
    void login(string& role);
    void logout();
    void resetPassword(const string& username);
};