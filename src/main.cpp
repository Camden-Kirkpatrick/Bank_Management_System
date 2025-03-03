// cd C:\Users\nedma\.vscode\C++\_In Progress\Bank\src && g++ main.cpp bank_account.cpp transaction.cpp customer.cpp bank.cpp utilities.cpp -o main

#include "../include/utilities.hpp"
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::unique_ptr<Bank::Bank>> banks;
    bool is_running = true;
    int choice = 0;

    do
    {
        DisplayMenu(choice, is_running, banks);
    } while (is_running);

    std::cout << "Goodbye!" << std::endl;

    // std::cout << "CreateBank()\n\n";
    // CreateBank(banks);
    // std::cout << "\n";
    // std::cout << "CreateCustomer()\n\n";
    // CreateCustomer(banks);
    // std::cout << "\n";
    // std::cout << "AddAccount() #1\n\n";
    // AddAccount(banks);
    // std::cout << "\n";
    // std::cout << "AddAccount() #2\n\n";
    // AddAccount(banks);
    // std::cout << "\n";
    // std::cout << "AddTransaction()\n\n";
    // AddTransaction(banks);
    // std::cout << "\n";
    // std::cout << "ViewAllTransactions()\n\n";
    // ViewAllTransactions(banks);

    return 0;
}