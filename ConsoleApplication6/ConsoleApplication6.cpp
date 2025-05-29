#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <unordered_map>
using namespace std;
struct User {
    string name;
    string email;
    string password;
    bool isAdmin;
    bool isActive;
};

vector<User> users;
unordered_map<string, double> pricing = { {"print", 0.10}, {"scan", 0.05} };

bool validate Password(const string& password) {
  
    return regex_match(password, regex("^(?=.*[A-Z])(?=.*\\d).{8,}$"));
}

void registerUser() {
    User user;
    cout << "Enter name: ";
    cin >> user.name;
    cout << "Enter email: ";
    cin >> user.email;
    do {
        cout << "Enter strong password (min 8 chars, 1 uppercase, 1 digit): ";
        cin >> user.password;
    } while (!validatePassword(user.password));

    user.isAdmin = false;
    user.isActive = true;
    users.push_back(user);
    cout << "Registration successful!\n";
}

int login(string& email) {
    string password;
    cout << "Enter email: ";
    cin >> email;
    cout << "Enter password: ";
    cin >> password;

    for (int i = 0; i < users.size(); ++i) {
        if (users[i].email == email && users[i].password == password && users[i].isActive) {
            return i;
        }
    }
    return -1;
}

void scanDocuments() {
    int pages;
    cout << "Enter number of pages to scan: ";
    cin >> pages;
    double cost = pages * pricing["scan"];
    cout << "Scanned " << pages << " pages. Total cost: $" << cost << endl;
}

void adminPanel(int userIndex) {
    int choice;
    do {
        cout << "\n--- Admin Panel ---\n";
        cout << "1. Set printing/scanning price\n";
        cout << "2. Delete/inactivate user\n";
        cout << "3. Logout\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            string service;
            double price;
            cout << "Enter service name (print/scan): ";
            cin >> service;
            cout << "Enter new price per page: ";
            cin >> price;
            pricing[service] = price;
            cout << service << " price updated to $" << price << endl;
        }
        else if (choice == 2) {
            string targetEmail;
            cout << "Enter user email to delete/inactivate: ";
            cin >> targetEmail;
            for (auto& u : users) {
                if (u.email == targetEmail) {
                    u.isActive = false;
                    cout << "User " << targetEmail << " inactivated.\n";
                }
            }
        }
    } while (choice != 3);
}

int main() {
 
    users.push_back({"Admin", "admin@sys.com", "Admin123", true, true});

    int choice;
    string currentEmail;
    do {
        cout << "\n1. Register\n2. Login\n3. Exit\nChoice: ";
        cin >> choice;
        if (choice == 1) {
            registerUser();
        }
        else if (choice == 2) {
            int userIndex = login(currentEmail);
            if (userIndex != -1) {
                if (users[userIndex].isAdmin) {
                    adminPanel(userIndex);
                } else {
                    scanDocuments();
                }
            } else {
                cout << "Invalid login or user inactive.\n";
            }
        }
    } while (choice != 3);

    return 0;
}
