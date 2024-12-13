#include <fstream>
#include <iostream>
#include <string>
#include "AccountUtils.h"

using namespace std;

void append_account_data(long long account_number, const char* name, const char* address, char account_type, int balance, const char* pin) {
    ofstream file("accounts.txt", ios::app);
    file << "Account Number: " << account_number << "\n";
    file << "Name: " << name << "\n";
    file << "Address: " << address << "\n";
    file << "Account Type: " << (account_type == 's' ? "Saving" : "Current") << "\n";
    file << "Balance: " << balance << "\n";
    file << "PIN: " << pin << "\n";
    file << "------------------------------------\n";
    file.close();
}

bool check_account_existence(long long account_number) {
    ifstream file("accounts.txt");
    string line;
    while (getline(file, line)) {
        if (line.find("Account Number: " + to_string(account_number)) != string::npos) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

int retrieve_account_balance(long long account_number) {
    ifstream file("accounts.txt");
    string line;
    while (getline(file, line)) {
        if (line.find("Account Number: " + to_string(account_number)) != string::npos) {
            for (int i = 0; i < 4; ++i) getline(file, line);  // Skip to Balance line
            size_t pos = line.find("Balance: ");
            if (pos != string::npos) {
                return stoi(line.substr(pos + 9));
            }
        }
    }
    file.close();
    return -1;
}

void modify_account_balance(long long account_number, int new_balance) {
    ifstream file("accounts.txt");
    ofstream temp_file("temp.txt");
    string line;

    while (getline(file, line)) {
        temp_file << line << endl;  // Write current line to the temporary file

        if (line.find("Account Number: " + to_string(account_number)) != string::npos) {
            // Copy the next 3 details as they are
            for (int i = 0; i < 3; ++i) {
                getline(file, line);
                temp_file << line << endl;
            }

            // Update the balance
            temp_file << "Balance: " << new_balance << "\n";

            // Skip the old balance line
            getline(file, line);
        }
    }

    file.close();
    temp_file.close();

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");
}


void display_account_info(long long account_number) {
    ifstream file("accounts.txt");
    string line;
    while (getline(file, line)) {
        if (line.find("Account Number: " + to_string(account_number)) != string::npos) {
            cout << line << endl;
            for (int i = 0; i < 5; ++i) {
                getline(file, line);
                cout << line << endl;
            }
            break;
        }
    }
    file.close();
}
