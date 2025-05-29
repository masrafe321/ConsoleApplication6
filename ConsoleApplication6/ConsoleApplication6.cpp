#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <conio.h>  
 
using namespace std;
string getPassword() {
    string password;
    char ch;
    cout << "Enter password: ";
    while ((ch = _getch()) != '\r') { 
        if (ch == '\b') { 
            if (!password.empty()) {
                cout << "\b \b";
                password.pop_back();
            }
        } else {
            password += ch;
            cout << '*';
        }
    }
    cout << endl;
    return password;
}
 
// Simple email validation
bool isValidEmail(const string& email) {
    const regex pattern("^[\\w.-]+@[\\w.-]+\\.[a-zA-Z]{2,6}$");
    return regex_match(email, pattern);
}
 
// Password strength validation
bool isValidPassword(const string& password) {
    return password.length() >= 6; 
}
void registerCustomer() {
    string name, email, password;
 
    cout << "=== Cyber Cafe Registration ===\n";
    cout << "Enter your name: ";
    getline(cin, name);
 
    do {
        cout << "Enter your email: ";
        getline(cin, email);
        if (!isValidEmail(email)) {
            cout << "Invalid email format. Please try again.\n";
        }
    } while (!isValidEmail(email));
 
    do {
        password = getPassword();
        if (!isValidPassword(password)) {
            cout << "Password must be at least 6 characters long. Try again.\n";
        }
    } while (!isValidPassword(password));
 
    // Save to file
    ofstream file("customers.txt", ios::app);
    if (file.is_open()) {
        file << name << "," << email << "," << password << endl;
        file.close();
        cout << "Registration successful!\n";
    } else {
        cerr << "Error saving registration. Try again later.\n";
    }
}
 
int main() {
    registerCustomer();
    return 0;
}
 
