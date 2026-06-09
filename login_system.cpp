#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <conio.h>       // _getch() ke liye - Windows only

using namespace std;

#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define YELLOW  "\033[1;33m"
#define CYAN    "\033[1;36m"
#define RESET   "\033[0m"

const string FILE_NAME = "users.txt";

void showBanner() {
    cout << CYAN;
    cout << "\n";
    cout << "  ╔══════════════════════════════════════╗\n";
    cout << "  ║      LOGIN & REGISTRATION SYSTEM     ║\n";
    cout << "  ║           C++ College Project        ║\n";
    cout << "  ╚══════════════════════════════════════╝\n";
    cout << RESET << "\n";
}

string getPassword() {
    string password = "";
    char ch;
    while (true) {
        ch = _getch();
        if (ch == '\r' || ch == '\n') break;
        if (ch == '\b' && !password.empty()) {
            cout << "\b \b";
            password.pop_back();
        } else if (ch != '\b') {
            password += ch;
            cout << '*';
        }
    }
    cout << "\n";
    return password;
}

bool userExists(const string& username) {
    ifstream file(FILE_NAME);
    string line, storedUser;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, storedUser, ',');
        if (storedUser == username) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void registerUser() {
    string username, password, confirmPass;

    cout << YELLOW << "\n  ── REGISTER ──\n" << RESET;
    cout << "  Enter Username : ";
    cin >> username;

    if (userExists(username)) {
        cout << RED << "  [!] Username already taken. Try another.\n" << RESET;
        return;
    }

    cout << "  Enter Password : ";
    password = getPassword();

    cout << "  Confirm Password : ";
    confirmPass = getPassword();

    if (password != confirmPass) {
        cout << RED << "  [!] Passwords do not match!\n" << RESET;
        return;
    }

    if (password.length() < 4) {
        cout << RED << "  [!] Password too short! Use at least 4 characters.\n" << RESET;
        return;
    }

    ofstream file(FILE_NAME, ios::app);
    file << username << "," << password << "\n";
    file.close();

    cout << GREEN << "\n  [✓] Registration Successful! You can now login.\n" << RESET;
}

void loginUser() {
    string username, password;
    string storedUser, storedPass, line;

    cout << YELLOW << "\n  ── LOGIN ──\n" << RESET;
    cout << "  Enter Username : ";
    cin >> username;
    cout << "  Enter Password : ";
    password = getPassword();

    ifstream file(FILE_NAME);
    bool found = false;

    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, storedUser, ',');
        getline(ss, storedPass, ',');

        if (storedUser == username && storedPass == password) {
            found = true;
            break;
        }
    }
    file.close();

    if (found) {
        cout << GREEN;
        cout << "\n  ╔══════════════════════════════╗\n";
        cout << "  ║  Welcome back, " << username << "!";
        int spaces = 13 - (int)username.length();
        for (int i = 0; i < spaces; i++) cout << " ";
        cout << "║\n";
        cout << "  ║  Login Successful  ✓         ║\n";
        cout << "  ╚══════════════════════════════╝\n";
        cout << RESET;
    } else {
        cout << RED << "\n  [!] Invalid Username or Password.\n" << RESET;
    }
}

int main() {
    int choice;

    showBanner();

    while (true) {
        cout << "  ┌─────────────────────┐\n";
        cout << "  │  1. Register        │\n";
        cout << "  │  2. Login           │\n";
        cout << "  │  3. Exit            │\n";
        cout << "  └─────────────────────┘\n";
        cout << "  Choose option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                cout << CYAN << "\n  Bye bye! Good luck with the project!\n\n" << RESET;
                return 0;
            default:
                cout << RED << "  [!] Invalid option. Try again.\n" << RESET;
        }

        cout << "\n";
    }

    return 0;
}