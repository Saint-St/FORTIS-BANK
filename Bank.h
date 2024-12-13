#ifndef BANK_H
#define BANK_H

#include <iostream>
#include <string>

class Bank {
private:
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
    void fetch_account_info(long long search_account_number);
};

#endif
