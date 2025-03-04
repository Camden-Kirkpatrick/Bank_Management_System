// cd src && g++ main.cpp utilities.cpp bank.cpp customer.cpp bank_account.cpp transaction.cpp -o main

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

    return 0;
}
