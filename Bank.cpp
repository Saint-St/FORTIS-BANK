#include "Bank.h"
#include "AccountUtils.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

long long Bank::generate_account_number() {
    srand(time(0));
    long long account_num = 0;
    for (int i = 0; i < 16; ++i) {
        account_num = account_num * 10 + rand() % 10;
    }
    return account_num;
}

void Bank::open_account() {
    cout << "Welcome to Fortis Bank!\n";
    cout << "Enter your full name: ";
    cin.ignore();
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
    append_account_data(account_number, name, address, account_type, balance, pin);
}

bool Bank::account_exists(long long search_account_number) {
    return check_account_existence(search_account_number);
}

int Bank::get_account_balance(long long search_account_number) {
    return retrieve_account_balance(search_account_number);
}

void Bank::update_account_balance(long long search_account_number, int new_balance) {
    modify_account_balance(search_account_number, new_balance);
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
    balance = current_balance + amount;

    cout << "Your total deposit amount is: " << balance << endl;
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
    cout << "Enter the amount you want to withdraw: ";
    cin >> amount;

    if (amount > current_balance) {
        cout << "Insufficient funds.\n";
    } else {
        balance = current_balance - amount;
        cout << "Now your total balance left is: " << balance << endl;
        update_account_balance(search_account_number, balance);
    }
}

void Bank::fetch_account_info(long long search_account_number) {
    display_account_info(search_account_number);
}
