#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;

class Bank {
    char name[100], address[100], account_type, pin[5];
    int balance, amount;
    long long account_number;

public:
    void open_account();
    void deposit_money();
    void withdraw_money();
    long long generate_account_number();
    void store_account_data();
    bool account_exists(long long search_account_number);
    int get_account_balance(long long search_account_number);
    void update_account_balance(long long account_number, int new_balance);
    void read_account_data();
    void fetch_account_info(long long search_account_number);
};

long long Bank::generate_account_number() {
    srand(time(0)); // Seed the random number generator
    long long account_num = 0;
    for (int i = 0; i < 16; ++i) {
        account_num = account_num * 10 + rand() % 10;
    }
    return account_num;
}

void Bank::open_account() {
    system("cls");  // If you're on Windows
    cout << "Welcome to Fortis Bank!\n";
    cout << "Enter your full name: ";
    cin.ignore();  // Ignore any leftover newline character
    cin.getline(name, 100);
    cout << "Enter your address: ";
    cin.getline(address, 100);
    cout << "What type of account you want to open (saving (s) or current (c)): ";
    cin >> account_type;
    cout << "Enter amount to deposit: ";
    cin >> balance;
    cout << "Enter your desired 4-digit PIN: ";
    cin >> pin;
    account_number = generate_account_number();
    cout << "Your account is created. Your account number is: " << account_number << endl;
    store_account_data();
}

void Bank::store_account_data() {
    ofstream file("accounts.txt", ios::app);  // Open in append mode
    file << "Account Number: " << account_number << "\n";
    file << "Name: " << name << "\n";
    file << "Address: " << address << "\n";
    file << "Account Type: " << (account_type == 's' ? "Saving" : "Current") << "\n";
    file << "Balance: " << balance << "\n";
    file << "PIN: " << pin << "\n";
    file << "------------------------------------\n";
    file.close();
}

bool Bank::account_exists(long long search_account_number) {
    ifstream file("accounts.txt");
    string line;
    while (getline(file, line)) {
        if (line.find("Account Number: " + to_string(search_account_number)) != string::npos) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

int Bank::get_account_balance(long long search_account_number) {
    ifstream file("accounts.txt");
    string line;
    while (getline(file, line)) {
        if (line.find("Account Number: " + to_string(search_account_number)) != string::npos) {
            getline(file, line); // Skip Name line
            getline(file, line); // Skip Address line
            getline(file, line); // Skip Account Type line
            getline(file, line); // Balance line
            size_t pos = line.find("Balance: ");
            if (pos != string::npos) {
                return stoi(line.substr(pos + 9));  // Extract balance after "Balance: "
            }
        }
    }
    file.close();
    return -1;  // Account not found
}

void Bank::update_account_balance(long long search_account_number, int new_balance) {
    ifstream file("accounts.txt");
    ofstream temp_file("temp.txt");
    string line;

    while (getline(file, line)) {
        temp_file << line << endl;
        if (line.find("Account Number: " + to_string(search_account_number)) != string::npos) {
            // Update the balance for this account
            temp_file << "Balance: " << new_balance << "\n";  // Update balance
            getline(file, line); // Skip remaining lines
            temp_file << line << "\n";  // Copy other details unchanged
        }
    }

    file.close();
    temp_file.close();
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");
}

void Bank::deposit_money() {
    long long search_account_number;
    cout << "Enter your account number: ";
    cin >> search_account_number;

    if (!account_exists(search_account_number)) {
        cout << "Account not found.\n";
        return;
    }

    cout << "Enter how much money you want to deposit: ";
    cin >> amount;

    int current_balance = get_account_balance(search_account_number);

    if (current_balance == -1) {
        cout << "Account not found.\n";
        return;
    }

    balance = current_balance + amount;
    cout << "Your total deposit amount is: " << balance << endl;

    // Update balance in the file
    update_account_balance(search_account_number, balance);
}

void Bank::withdraw_money() {
    long long search_account_number;
    cout << "Enter your account number: ";
    cin >> search_account_number;

    if (!account_exists(search_account_number)) {
        cout << "Account not found.\n";
        return;
    }

    int current_balance = get_account_balance(search_account_number);

    if (current_balance == -1) {
        cout << "Account not found.\n";
        return;
    }

    cout << "Enter the amount you want to withdraw: ";
    cin >> amount;

    if (amount > current_balance) {
        cout << "Insufficient funds.\n";
    } else {
        balance = current_balance - amount;
        cout << "Now your total balance left is: " << balance << endl;

        // Update balance in the file
        update_account_balance(search_account_number, balance);
    }
}

void Bank::fetch_account_info(long long search_account_number) {
    ifstream file("accounts.txt");
    string line;
    bool account_found = false;

    while (getline(file, line)) {
        if (line.find("Account Number: " + to_string(search_account_number)) != string::npos) {
            account_found = true;
            cout << "\nAccount Information:\n";
            cout << line << endl;  // Print account number
            getline(file, line);  // Name
            cout << line << endl;
            getline(file, line);  // Address
            cout << line << endl;
            getline(file, line);  // Account Type
            cout << line << endl;
            getline(file, line);  // Balance
            cout << line << endl;
            getline(file, line);  // PIN
            cout << line << endl;
            break;
        }
    }

    if (!account_found) {
        cout << "Account not found.\n";
    }
    file.close();
}

int main() {
    int choice;
    char proceed;
    Bank obj;
    do {
        system("cls");  // If you're on Windows
        cout << "Welcome to Fortis Bank!\n";
        cout << "01) Open account\n";
        cout << "02) Deposit money\n";
        cout << "03) Withdraw money\n";
        cout << "04) Fetch account info\n";
        cout << "05) Exit\n";
        cout << "Please select an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                obj.open_account();
                break;
            case 2:
                obj.deposit_money();
                break;
            case 3:
                obj.withdraw_money();
                break;
            case 4: {
                long long search_account_number;
                cout << "Enter your account number to fetch details: ";
                cin >> search_account_number;
                obj.fetch_account_info(search_account_number);
                break;
            }
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid option, please try again.\n";
                break;
        }

        cout << "\nDo you want to select the next option? Press 'y' for yes, 'n' for no: ";
        cin >> proceed;

    } while (proceed == 'y' || proceed == 'Y');

    return 0;
}
