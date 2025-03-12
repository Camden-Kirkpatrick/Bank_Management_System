/**
 * @file utilities.cpp
 * @brief This file provides various utility and helper functions for the Bank Management System,
 *        including input validation, object selection, menu display, and user interaction.
 */

#include "../include/utilities.hpp"
#include "../include/global.hpp"
#include <limits>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include <iomanip>

/**
 * @brief Gets a valid non-empty string from the user.
 * @param prompt The message displayed to the user before input.
 * @return A valid, non-empty std::string entered by the user.
 */
std::string Utility::GetValidString(const std::string &prompt)
{
    // Repeatedly prompt until the user enters a valid, non-empty string
    std::string value;
    while (true)
    {
        std::cout << prompt;
        std::getline(std::cin, value);
        if (!std::cin.fail() && !value.empty())
        {
            return value;
        }
        std::cerr << "Invalid input. Please enter a non-empty string.\n";
    }
}

/**
 * @brief Searches for and returns a pointer to a Bank object by its ID.
 * @param banks A vector of unique_ptr to Bank objects.
 * @param bank_id The ID of the Bank to find.
 * @return A pointer to the Bank if found, otherwise nullptr.
 */
Bank::Bank *FindBank(const std::vector<std::unique_ptr<Bank::Bank>> &banks, i32 bank_id)
{
    // Use std::find_if to locate a Bank with the matching ID
    auto it = std::find_if(banks.begin(), banks.end(),
                           [bank_id](const std::unique_ptr<Bank::Bank> &b)
                           { return b->GetID() == bank_id; });
    return (it != banks.end()) ? it->get() : nullptr;
}

/**
 * @brief Searches for and returns a pointer to a Customer object by its ID.
 * @param bank Pointer to the Bank that contains customers.
 * @param customer_id The ID of the Customer to find.
 * @return A pointer to the Customer if found, otherwise nullptr.
 */
Bank::Customer *FindCustomer(const Bank::Bank *bank, i32 customer_id)
{
    // Similar approach: find_if on the bank's customers
    auto it = std::find_if(bank->GetCustomers().begin(), bank->GetCustomers().end(),
                           [customer_id](const std::unique_ptr<Bank::Customer> &c)
                           { return c->GetID() == customer_id; });
    return (it != bank->GetCustomers().end()) ? it->get() : nullptr;
}

/**
 * @brief Searches for and returns a pointer to a BankAccount object by its ID.
 * @param customer Pointer to the Customer that contains the accounts.
 * @param account_id The ID of the BankAccount to find.
 * @return A pointer to the BankAccount if found, otherwise nullptr.
 */
Bank::BankAccount *FindAccount(const Bank::Customer *customer, const std::string &account_id)
{
    // If the account ID matches, return that BankAccount
    auto it = std::find_if(customer->GetAccounts().begin(), customer->GetAccounts().end(),
                           [account_id](const std::unique_ptr<Bank::BankAccount> &a)
                           { return a->GetID() == account_id; });
    return (it != customer->GetAccounts().end()) ? it->get() : nullptr;
}

/**
 * @brief Prompts the user to select a Bank by entering its ID.
 * @param banks A vector of unique_ptr to Bank objects.
 * @return A pointer to the selected Bank if found, otherwise nullptr.
 */
Bank::Bank *SelectBank(const std::vector<std::unique_ptr<Bank::Bank>> &banks)
{
    // Let the user pick a Bank ID, then try to find the Bank
    i32 bank_id = Utility::GetValidInput("Enter bank ID: ", MIN_BANK_ID, MAX_BANK_ID);
    Bank::Bank *bank = FindBank(banks, bank_id);

    if (!bank)
        std::cerr << "Error: Bank not found.\n";

    return bank;
}

/**
 * @brief Prompts the user to select a Customer by entering its ID.
 * @param bank Pointer to the Bank containing the Customer objects.
 * @return A pointer to the selected Customer if found, otherwise nullptr.
 */
Bank::Customer *SelectCustomer(const Bank::Bank *bank)
{
    // Ensure the bank and its customers exist
    if (!bank || bank->GetNumberOfCustomers() == 0)
    {
        std::cerr << "Error: No customers available.\n";
        return nullptr;
    }

    // Prompt user for Customer ID
    i32 customer_id = Utility::GetValidInput("Enter customer ID: ", MIN_CUSTOMER_ID, MAX_CUSTOMER_ID);
    Bank::Customer *customer = FindCustomer(bank, customer_id);

    if (!customer)
        std::cerr << "Error: Customer not found.\n";

    return customer;
}

/**
 * @brief Prompts the user to select an Account by entering its ID.
 * @param customer Pointer to the Customer containing the BankAccount objects.
 * @return A pointer to the selected BankAccount if found, otherwise nullptr.
 */
Bank::BankAccount *SelectAccount(const Bank::Customer *customer)
{
    // Ensure the customer and their accounts exist
    if (!customer || customer->GetNumberOfAccounts() == 0)
    {
        std::cerr << "Error: No accounts available.\n";
        return nullptr;
    }

    // Prompt user for the account ID
    std::string account_id = Utility::GetValidString("Enter account ID: ");
    Bank::BankAccount *account = FindAccount(customer, account_id);

    if (!account)
        std::cerr << "Error: Account not found.\n";

    return account;
}

/**
 * @brief Pauses program execution until the user presses Enter.
 */
void WaitForUser()
{
    // Simple prompt to hold the console until a key is pressed
    std::cout << "Press Enter to continue...";
    std::cin.get();
}

/**
 * @brief Clears the console screen, using the appropriate system call for Windows or Unix-like systems.
 */
void ClearScreen()
{
#ifdef _WIN32
    system("cls"); // Windows command to clear the screen
#else
    system("clear"); // Unix/Linux/Mac command to clear the screen
#endif
}

/**
 * @brief Displays a menu of options for managing banks, customers, accounts, transactions, etc.
 * @param choice An integer reference that will store the user's menu choice.
 * @param is_running A boolean reference indicating if the program should continue running.
 * @param banks A vector of unique_ptr to Bank objects.
 */
void DisplayMenu(i32 &choice, bool &is_running, std::vector<std::unique_ptr<Bank::Bank>> &banks)
{
    // Then your actual menu title and items
    std::cout << "========= BANK MANAGEMENT MENU =========\n";
    std::cout << "1.  Add Bank\n";
    std::cout << "2.  Add Customer\n";
    std::cout << "3.  Add Account\n";
    std::cout << "4.  Add Transaction\n";
    std::cout << "5.  View All Banks\n";
    std::cout << "6.  View All Customers\n";
    std::cout << "7.  View All Accounts\n";
    std::cout << "8.  View All Transactions\n";
    std::cout << "9.  Search For Bank\n";
    std::cout << "10. Search For Customer\n";
    std::cout << "11. Search For Account\n";
    std::cout << "12. Search For Transaction\n";
    std::cout << "13. Apply Interest\n";
    std::cout << "14. Write To File\n";
    std::cout << "15. Exit\n";
    std::cout << "========================================\n";

    // Obtain user choice and proceed
    choice = Utility::GetValidInput("Enter choice: ", MIN_MENU_CHOICE, MAX_MENU_CHOICE);
    HandleUserChoice(choice, is_running, banks);
}

/**
 * @brief Handles the user's menu choice and calls the appropriate function based on that choice.
 * @param choice An integer reference containing the user's menu choice.
 * @param is_running A boolean reference indicating if the program should continue running.
 * @param banks A vector of unique_ptr to Bank objects.
 */
void HandleUserChoice(i32 &choice, bool &is_running, std::vector<std::unique_ptr<Bank::Bank>> &banks)
{
    // Switch statement to handle each menu option
    switch (choice)
    {
    case 1:
        CreateBank(banks);
        break;
    case 2:
        CreateCustomer(banks);
        break;
    case 3:
        AddAccount(banks);
        break;
    case 4:
        AddTransaction(banks);
        break;
    case 5:
        ViewAllBanks(banks);
        break;
    case 6:
        ViewAllCustomer(banks);
        break;
    case 7:
        ViewAllAccounts(banks);
        break;
    case 8:
        ViewAllTransactions(banks);
        break;
    case 9:
        SearchForBank(banks);
        break;
    case 10:
        SearchForCustomer(banks);
        break;
    case 11:
        SearchForAccount(banks);
        break;
    case 12:
        SearchForTransaction(banks);
        break;
    case 13:
        ApplyInterest(banks);
        break;
    case 14:
        WriteToFile(banks);
        break;
    case 15:
        // User wants to exit the program
        is_running = false;
        return;
    default:
        std::cerr << "Invalid choice. Please try again.\n";
        return;
    }

    // Wait for user input, then clear screen for next operation
    WaitForUser();
    ClearScreen();
}

/**
 * @brief Creates a new Bank object, assigns it a random ID, and inserts it into the banks vector in sorted order.
 * @param banks A reference to a vector of unique_ptr to Bank objects.
 */
void CreateBank(std::vector<std::unique_ptr<Bank::Bank>> &banks)
{
    // If no capacity is set, reserve space for up to 10 Bank objects
    if (banks.capacity() == 0)
    {
        banks.reserve(10);
    }

    std::string bank_name = Utility::GetValidString("Enter bank name: ");
    std::unique_ptr<Bank::Bank> new_bank = std::make_unique<Bank::Bank>(bank_name);

    // Keep the vector sorted by Bank ID
    auto it = std::lower_bound(
        banks.begin(), banks.end(), new_bank,
        [](const std::unique_ptr<Bank::Bank> &a, const std::unique_ptr<Bank::Bank> &b)
        {
            return a->GetID() < b->GetID();
        });

    banks.insert(it, std::move(new_bank));
}

/**
 * @brief Creates a new Customer object and associates it with a selected Bank.
 * @param banks A reference to a vector of unique_ptr to Bank objects.
 */
void CreateCustomer(std::vector<std::unique_ptr<Bank::Bank>> &banks)
{
    if (banks.empty())
    {
        std::cerr << "Error: No banks available. Create a bank first.\n";
        return;
    }

    // Prompt user to select which bank to add a customer to
    Bank::Bank *bank = SelectBank(banks);
    if (!bank)
        return;

    // Gather necessary info for the new Customer
    std::string fname = Utility::GetValidString("Enter first name: ");
    std::string lname = Utility::GetValidString("Enter last name: ");
    i32 age = Utility::GetValidInput("Enter age: ", MIN_AGE, MAX_AGE);

    bank->AddCustomer(fname, lname, age);
}

/**
 * @brief Displays basic information (ID and Name) of all Banks in the system.
 * @param banks A const reference to a vector of unique_ptr to Bank objects.
 */
void ViewAllBanks(const std::vector<std::unique_ptr<Bank::Bank>> &banks)
{
    if (banks.empty())
    {
        std::cerr << "Error: No banks available.\n";
        return;
    }

    std::cout << "\n========= All Banks =========\n";
    for (size_t i = 0; i < banks.size(); i++)
    {
        std::cout << "Bank #" << i + 1 << "\n";
        std::cout << "Bank Name: " << banks[i]->GetName() << "\n";
        std::cout << "Bank ID: " << banks[i]->GetID() << "\n";
        std::cout << "--------------------------------\n";
    }
}

/**
 * @brief Displays all Customers of a selected Bank.
 * @param banks A const reference to a vector of unique_ptr to Bank objects.
 */
void ViewAllCustomer(const std::vector<std::unique_ptr<Bank::Bank>> &banks)
{
    if (banks.empty())
    {
        std::cerr << "Error: No banks available.\n";
        return;
    }

    // User selects which bank to view customers from
    const Bank::Bank *bank = SelectBank(banks);
    if (!bank)
        return;

    if (bank->GetNumberOfCustomers() == 0)
    {
        std::cerr << "Error: No customers available in this bank.\n";
        return;
    }

    std::cout << "\n========= All Customers =========\n";
    bank->ViewAllCustomers();
}

/**
 * @brief Searches for a Bank by ID using a binary-like search approach.
 * @param banks A const reference to a vector of unique_ptr to Bank objects.
 */
void SearchForBank(const std::vector<std::unique_ptr<Bank::Bank>> &banks)
{
    if (banks.empty())
    {
        std::cerr << "Error: No banks available.\n";
        return;
    }

    // Let the user type in a Bank ID to look for
    i32 bank_id = Utility::GetValidInput("Enter bank ID: ", MIN_BANK_ID, MAX_BANK_ID);

    auto it = std::lower_bound(banks.begin(), banks.end(), bank_id,
                               [](const std::unique_ptr<Bank::Bank> &b, i32 bank_id)
                               { return b->GetID() < bank_id; });

    if (it != banks.end() && (*it)->GetID() == bank_id)
    {
        // Found a match
        std::cout << "Bank found!\n";
        std::cout << "Bank Name: " << (*it)->GetName() << "\n";
        std::cout << "Bank ID: " << (*it)->GetID() << "\n";
    }
    else
    {
        std::cerr << "Error: Bank not found.\n";
    }
}

/**
 * @brief Searches for a Customer by ID in a selected Bank using a sorted approach.
 * @param banks A reference to a vector of unique_ptr to Bank objects.
 */
void SearchForCustomer(std::vector<std::unique_ptr<Bank::Bank>> &banks)
{
    if (banks.empty())
    {
        std::cerr << "Error: No banks available.\n";
        return;
    }

    // First pick which bank we are searching in
    const Bank::Bank *bank = SelectBank(banks);
    if (!bank)
        return;

    if (bank->GetNumberOfCustomers() == 0)
    {
        std::cerr << "Error: No customers available in this bank.\n";
        return;
    }

    i32 customer_id = Utility::GetValidInput("Enter customer ID: ", MIN_CUSTOMER_ID, MAX_CUSTOMER_ID);

    auto it = std::lower_bound(bank->GetCustomers().begin(), bank->GetCustomers().end(), customer_id,
                               [](const std::unique_ptr<Bank::Customer> &c, i32 customer_id)
                               {
                                   return c->GetID() < customer_id;
                               });

    if (it != bank->GetCustomers().end() && (*it)->GetID() == customer_id)
    {
        // Found the customer
        std::cout << "Customer found!\n";
        std::cout << "Customer ID: " << (*it)->GetID() << "\n";
        std::cout << "Name: " << (*it)->GetName() << "\n";
        std::cout << "Age: " << (*it)->GetAge() << "\n";
    }
    else
    {
        std::cerr << "Error: Customer not found.\n";
    }
}

/**
 * @brief Creates a new BankAccount for an existing Customer in a selected Bank.
 * @param banks A reference to a vector of unique_ptr to Bank objects.
 */
void AddAccount(std::vector<std::unique_ptr<Bank::Bank>> &banks)
{
    if (banks.empty())
    {
        std::cerr << "Error: No banks available. Create a bank first.\n";
        return;
    }

    // Pick the bank that will hold the new account
    Bank::Bank *bank = SelectBank(banks);
    if (!bank)
        return;

    if (bank->GetNumberOfCustomers() == 0)
    {
        std::cerr << "Error: No customers available. Add a customer first.\n";
        return;
    }

    // Next, pick which Customer in that bank will own the new account
    Bank::Customer *customer = SelectCustomer(bank);
    if (!customer)
        return;

    // Ask for the account type and initial balance
    i32 account_type = Utility::GetValidInput("Enter account type (0: CHECKING, 1: SAVING): ", MIN_ACCOUNT_TYPE, MAX_ACCOUNT_TYPE);
    f64 balance = Utility::GetValidInput("Enter initial balance: ", MIN_STARTING_BALANCE, MAX_BALANCE, true);

    // Create the bank account for that customer
    customer->CreateBankAccount(static_cast<Bank::AccountType>(account_type), balance);
}

void AddTransaction(std::vector<std::unique_ptr<Bank::Bank>> &banks)
{
    if (banks.empty())
    {
        std::cerr << "Error: No banks available. Create a bank first.\n";
        return;
    }

    // Select the bank where the transaction will occur
    Bank::Bank *bank = SelectBank(banks);
    if (!bank)
        return;

    if (bank->GetNumberOfCustomers() == 0)
    {
        std::cerr << "Error: No customers available. Add a customer first.\n";
        return;
    }

    // Select the customer
    Bank::Customer *customer = SelectCustomer(bank);
    if (!customer)
        return;

    if (customer->GetNumberOfAccounts() == 0)
    {
        std::cerr << "Error: No accounts available. Create an account first.\n";
        return;
    }

    // Choose which account to perform the transaction on
    Bank::BankAccount *source_account = SelectAccount(customer);
    if (!source_account)
        return;

    i32 transaction_type = Utility::GetValidInput(
        "Enter transaction type (0: DEPOSIT, 1: WITHDRAW, 2: TRANSFER): ",
        MIN_TRANSACTION_TYPE, MAX_TRANSACTION_TYPE);

    if (static_cast<Bank::TransactionType>(transaction_type) == Bank::TransactionType::TRANSFER)
    {
        // Transfers require at least two accounts
        if (customer->GetNumberOfAccounts() < 2)
        {
            std::cerr << "Error: You must have at least two accounts to transfer funds.\n";
            return;
        }

        f64 amount = Utility::GetValidInput(
            "Enter transaction amount: ",
            MIN_TRANSACTION_AMOUNT, MAX_TRANSACTION_AMOUNT,
            true); // allow decimals

        // Check if user is attempting to transfer more money than they have
        if (amount > source_account->GetBalance())
        {
            std::cerr << "Error: You can't transfer more money than your current balance.\n";
            return;
        }

        // Prompt user for the destination account ID
        std::string dest_id = Utility::GetValidString("Enter the ID of the destination account: ");

        // Check that the user isn't transferring to the same account
        if (dest_id == source_account->GetID())
        {
            std::cerr << "Error: Cannot transfer to the same account.\n";
            return;
        }

        // Create a new Transfer transaction
        source_account->CreateTransaction(
            static_cast<Bank::TransactionType>(transaction_type),
            amount,
            dest_id);
    }
    else
    {
        // DEPOSIT or WITHDRAW
        f64 amount = Utility::GetValidInput(
            "Enter transaction amount: ",
            MIN_TRANSACTION_AMOUNT, MAX_TRANSACTION_AMOUNT, true);

        source_account->CreateTransaction(
            static_cast<Bank::TransactionType>(transaction_type),
            amount);
    }
}

/**
 * @brief Displays all accounts belonging to a selected Customer in a selected Bank.
 * @param banks A reference to a vector of unique_ptr to Bank objects.
 */
void ViewAllAccounts(std::vector<std::unique_ptr<Bank::Bank>> &banks)
{
    if (banks.empty())
    {
        std::cerr << "Error: No banks available.\n";
        return;
    }

    // Select the bank
    const Bank::Bank *bank = SelectBank(banks);
    if (!bank)
        return;

    if (bank->GetNumberOfCustomers() == 0)
    {
        std::cerr << "Error: No customers available in this bank.\n";
        return;
    }

    // Select the customer
    const Bank::Customer *customer = SelectCustomer(bank);
    if (!customer)
        return;

    if (customer->GetNumberOfAccounts() == 0)
    {
        std::cerr << "Error: This customer has no accounts.\n";
        return;
    }

    // Print all of that customer's accounts
    std::cout << "\n========= Customer's Accounts =========\n";
    customer->ViewCustomerAccounts();
}

/**
 * @brief Displays all transactions belonging to a selected BankAccount in a selected Customer/Bank.
 * @param banks A reference to a vector of unique_ptr to Bank objects.
 */
void ViewAllTransactions(std::vector<std::unique_ptr<Bank::Bank>> &banks)
{
    if (banks.empty())
    {
        std::cerr << "Error: No banks available.\n";
        return;
    }

    // Select bank -> customer -> account
    const Bank::Bank *bank = SelectBank(banks);
    if (!bank)
        return;

    if (bank->GetNumberOfCustomers() == 0)
    {
        std::cerr << "Error: No customers available in this bank.\n";
        return;
    }

    const Bank::Customer *customer = SelectCustomer(bank);
    if (!customer)
        return;

    if (customer->GetNumberOfAccounts() == 0)
    {
        std::cerr << "Error: This customer has no accounts.\n";
        return;
    }

    const Bank::BankAccount *account = SelectAccount(customer);
    if (!account)
        return;

    if (account->GetNumberOfTransactions() == 0)
    {
        std::cerr << "Error: This account has no transactions.\n";
        return;
    }

    // Display the transaction history for the selected account
    std::cout << "\n========= Account Transactions =========\n";
    account->ViewAccountTransactions();
}

/**
 * @brief Searches for a BankAccount by ID in a selected Customer/Bank using a sorted approach.
 * @param banks A reference to a vector of unique_ptr to Bank objects.
 */
void SearchForAccount(std::vector<std::unique_ptr<Bank::Bank>> &banks)
{
    if (banks.empty())
    {
        std::cerr << "Error: No banks available.\n";
        return;
    }

    // First pick which bank
    const Bank::Bank *bank = SelectBank(banks);
    if (!bank)
        return;

    if (bank->GetNumberOfCustomers() == 0)
    {
        std::cerr << "Error: No customers available in this bank.\n";
        return;
    }

    // Then pick the customer
    const Bank::Customer *customer = SelectCustomer(bank);
    if (!customer)
        return;

    if (customer->GetNumberOfAccounts() == 0)
    {
        std::cerr << "Error: This customer has no accounts.\n";
        return;
    }

    // Finally, search for the account by ID
    std::string account_id = Utility::GetValidString("Enter account ID: ");

    auto it = std::lower_bound(customer->GetAccounts().begin(), customer->GetAccounts().end(), account_id,
                               [](const std::unique_ptr<Bank::BankAccount> &a, const std::string &account_id)
                               {
                                   return a->GetID() < account_id;
                               });

    if (it != customer->GetAccounts().end() && (*it)->GetID() == account_id)
    {
        // Found it
        std::cout << "Account found!\n";
        std::cout << "Account ID: " << (*it)->GetID() << "\n";
        std::cout << "Balance: $" << std::fixed << std::setprecision(2) << (*it)->GetBalance() << "\n";
    }
    else
    {
        std::cerr << "Error: Account not found.\n";
    }
}

/**
 * @brief Searches for a Transaction by ID in a selected BankAccount (in a selected Customer/Bank).
 * @param banks A reference to a vector of unique_ptr to Bank objects.
 */
void SearchForTransaction(std::vector<std::unique_ptr<Bank::Bank>> &banks)
{
    if (banks.empty())
    {
        std::cerr << "Error: No banks available.\n";
        return;
    }

    // Choose bank -> customer -> account
    const Bank::Bank *bank = SelectBank(banks);
    if (!bank)
        return;

    if (bank->GetNumberOfCustomers() == 0)
    {
        std::cerr << "Error: No customers available in this bank.\n";
        return;
    }

    const Bank::Customer *customer = SelectCustomer(bank);
    if (!customer)
        return;

    if (customer->GetNumberOfAccounts() == 0)
    {
        std::cerr << "Error: This customer has no accounts.\n";
        return;
    }

    const Bank::BankAccount *account = SelectAccount(customer);
    if (!account)
        return;

    if (account->GetNumberOfTransactions() == 0)
    {
        std::cerr << "Error: This account has no transactions.\n";
        return;
    }

    // Query the user for the transaction ID
    i32 transaction_id = Utility::GetValidInput("Enter transaction ID: ", MIN_TRANSACTION_ID, MAX_TRANSACTION_ID);

    const std::vector<std::unique_ptr<Bank::Transaction>> &transactions = account->GetTransactions();
    auto it = std::lower_bound(transactions.begin(), transactions.end(), transaction_id,
                               [](const std::unique_ptr<Bank::Transaction> &t, i32 id)
                               {
                                   return t->GetTransactionID() < id;
                               });

    if (it != transactions.end() && (*it)->GetTransactionID() == transaction_id)
    {
        std::cout << "Transaction found!\n";
        (*it)->DisplayTransaction();
    }
    else
    {
        std::cerr << "Error: Transaction not found.\n";
    }
}

/**
 * @brief Applies interest to all SavingAccounts in all Banks.
 * @param banks A const reference to a vector of unique_ptr to Bank objects.
 */
void ApplyInterest(const std::vector<std::unique_ptr<Bank::Bank>> &banks)
{
    if (banks.empty())
    {
        std::cerr << "Error: No banks available.\n";
        return;
    }

    bool has_savings_accounts = false;

    // Check if there's at least one SavingsAccount among all banks
    for (const auto &bank : banks)
    {
        for (const auto &customer : bank->GetCustomers())
        {
            for (const auto &account : customer->GetAccounts())
            {
                if (dynamic_cast<Bank::SavingAccount *>(account.get()))
                {
                    has_savings_accounts = true;
                    break;
                }
            }
            if (has_savings_accounts)
                break;
        }
        if (has_savings_accounts)
            break;
    }

    if (!has_savings_accounts)
    {
        std::cerr << "Error: No savings accounts available in any bank. Interest cannot be applied.\n";
        return;
    }

    // Apply interest to all savings accounts across all banks
    for (const auto &bank : banks)
    {
        bank->ApplyInterestToAllAccounts();
    }
    std::cout << "Interest applied to all savings accounts in all banks.\n";
}

/**
 * @brief Writes all bank information (banks, customers, accounts, transactions) to a text file named 'bank_info.txt'.
 * @param banks A const reference to a vector of unique_ptr to Bank objects.
 */
void WriteToFile(const std::vector<std::unique_ptr<Bank::Bank>> &banks)
{
    std::ofstream ofs("bank_info.txt");
    if (!ofs.is_open())
    {
        std::cerr << "bank_info.txt could not be opened!" << std::endl;
        return;
    }

    // Iterate through each bank and its associated customers, accounts, and transactions
    for (const auto &bank : banks)
    {
        ofs << "Bank: " << bank->GetID() << " | " << bank->GetName() << std::endl;
        for (const auto &customer : bank->GetCustomers())
        {
            ofs << "\t"
                << "Customer: " << customer->GetID() << " | "
                << customer->GetName() << " | " << customer->GetAge() << std::endl;
            for (const auto &account : customer->GetAccounts())
            {
                ofs << "\t\t"
                    << "Account: " << account->GetID() << " | $"
                    << std::fixed << std::setprecision(2) << account->GetBalance() << std::endl;
                for (const auto &transaction : account->GetTransactions())
                {
                    ofs << "\t\t\t"
                        << "Transaction: " << transaction->GetTransactionID() << " | $"
                        << std::fixed << std::setprecision(2)
                        << transaction->GetTransactionAmount() << " | "
                        << transaction->GetTransactionType();

                    // If it was invalid, add an extra marker
                    if (transaction->WasInvalid())
                    {
                        ofs << " [INVALID]";
                    }
                    ofs << '\n';
                }
            }
        }
    }
    ofs.close();
}
