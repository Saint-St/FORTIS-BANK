#ifndef ACCOUNT_UTILS_H
#define ACCOUNT_UTILS_H

#include <string>

void append_account_data(long long account_number, const char* name, const char* address, char account_type, int balance, const char* pin);
bool check_account_existence(long long account_number);
int retrieve_account_balance(long long account_number);
void modify_account_balance(long long account_number, int new_balance);
void display_account_info(long long account_number);

#endif
