//this repo initially had bugs and i came to find out the reason was the light mode i was using,
//use darkmode mate it'll help you!
//alter nothing, nimetransnight siku mzima debuggindg the bugs that i wrote

//code crafted to nothing short of perfection



#include "Bank.h"
#include <iostream>
#include <limits> // For numeric limits

using namespace std;

int main() {
    int choice;
    char proceed;
    Bank obj;

    do {
        try {
            cout << "Welcome to Fortis Bank!\n";
            cout << "01) Open account\n";
            cout << "02) Deposit money\n";
            cout << "03) Withdraw money\n";
            cout << "04) Fetch account info\n";
            cout << "05) Exit\n";
            cout << "Please select an option: ";

            if (!(cin >> choice)) {
                throw invalid_argument("Invalid input! Please enter a number between 1 and 5.");
            }

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
                    if (!(cin >> account_number)) {
                        cin.clear(); // Clear the error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                        throw invalid_argument("Invalid input! Account number must be numeric.");
                    }
                    obj.fetch_account_info(account_number);
                    break;
                }
                case 5:
                    cout << "Exiting...\n";
                    break;
                default:
                    throw out_of_range("Invalid option! Please select a number between 1 and 5.");
            }

            cout << "\nDo you want to select another option? (y/n): ";
            cin >> proceed;

        } catch (const exception &e) {
            cout << "Error: " << e.what() << endl;
            proceed = 'y'; // Allow user to retry after an error
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
        }

    } while (proceed == 'y' || proceed == 'Y');

    return 0;
}
