//this repo initially had bugs and i came to find out the reason was the light mode i was using,
//use darkmode mate itll help you
//alter nothing, nimetransnight siku mzima debuggindg the bugs that i wrote

//code crafted to nothing short of perfection



#include "Bank.h"
#include <iostream>

using namespace std;

int main() {
    int choice;
    char proceed;
    Bank obj;
    do {
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
                long long account_number;
                cout << "Enter your account number: ";
                cin >> account_number;
                obj.fetch_account_info(account_number);
                break;
            }
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid option.\n";
        }

        cout << "\nDo you want to select another option? (y/n): ";
        cin >> proceed;

    } while (proceed == 'y' || proceed == 'Y');

    return 0;
}
