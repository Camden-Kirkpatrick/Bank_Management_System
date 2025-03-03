#include "../include/utilities.hpp"
#include <limits>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <memory>

// ==============================
// HELPER FUNCTIONS FOR INPUT VALIDATION
// ==============================

i32 GetValidInt(const std::string &prompt, i32 min, i32 max)
{
    i32 value;
    while (true)
    {
        std::cout << prompt;
        std::cin >> value;

        if (!std::cin.fail() && value >= min && value <= max)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cerr << "Invalid input. Please enter a value between " << min << " and " << max << ".\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

f64 GetValidFloat(const std::string &prompt, f64 min)
{
    f64 value;
    while (true)
    {
        std::cout << prompt;
        std::cin >> value;

        if (!std::cin.fail() && value >= min)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cerr << "Invalid input. Please enter a value greater than or equal to " << min << ".\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string GetValidString(const std::string &prompt)
{
    std::string value;
    while (true)
    {
        std::cout << prompt;
        std::getline(std::cin, value);

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cerr << "Invalid input. Please enter a valid string.\n";
        }
        else if (!value.empty())
        {
            return value;
        }
        else
        {
            std::cerr << "Invalid input. Please enter a non-empty string.\n";
        }
    }
}

std::unique_ptr<Bank::Bank> &SelectBank(std::vector<std::unique_ptr<Bank::Bank>> &banks)
{
    i32 bank_index = GetValidInt("Enter bank index: ", 0, banks.size() - 1);
    return banks[bank_index];
}

const std::unique_ptr<Bank::Customer> &SelectCustomer(std::unique_ptr<Bank::Bank> &bank)
{
    i32 customer_index = GetValidInt("Enter customer index: ", 0, bank->GetNumberOfCustomers() - 1);
    return bank->GetCustomer(customer_index);
}

const std::unique_ptr<Bank::BankAccount> &SelectAccount(const std::unique_ptr<Bank::Customer> &customer)
{
    i32 account_index = GetValidInt("Enter account index: ", 0, customer->GetNumberOfAccounts() - 1);
    return customer->GetAccount(account_index);
}

// ==============================
// HELPER FUNCTIONS FOR USER INTERACTION
// ==============================

void WaitForUser()
{
    std::cout << "Press Enter to continue...";
    std::cin.get();
}

void ClearScreen()
{
#ifdef _WIN32
    system("cls"); // Windows command to clear the screen
#else
    system("clear"); // Unix/Linux/Mac command to clear the screen
#endif
}

// ==============================
// MENU FUNCTION
// ==============================

void DisplayMenu(i32 &choice, bool &is_running, std::vector<std::unique_ptr<Bank::Bank>> &banks)
{
    std::cout << "\n========= BANK MANAGEMENT MENU =========\n";
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
    std::cout << "13. Exit\n";
    std::cout << "========================================\n";
    choice = GetValidInt("Enter choice: ", 1, 13);

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
        is_running = false;
        return;
    default:
        std::cerr << "Invalid choice. Please try again.\n";
        return;
    }

    WaitForUser();
    ClearScreen();
}

// ==============================
// BANK & CUSTOMER FUNCTIONS
// ==============================

void CreateBank(std::vector<std::unique_ptr<Bank::Bank>> &banks)
{
    if (banks.capacity() == 0)
    {
        banks.reserve(10);
    }

    std::string bank_name = GetValidString("Enter bank name: ");
    auto new_bank = std::make_unique<Bank::Bank>(bank_name);

    // Find the correct sorted position
    auto it = std::lower_bound(
        banks.begin(), banks.end(), new_bank,
        [](const std::unique_ptr<Bank::Bank> &a, const std::unique_ptr<Bank::Bank> &b)
        {
            return a->GetID() < b->GetID();
        });

    // Insert the new bank at the correct position
    banks.insert(it, std::move(new_bank));
}

void CreateCustomer(std::vector<std::unique_ptr<Bank::Bank>> &banks)
{
    if (banks.empty())
    {
        std::cerr << "Error: No banks available. Create a bank first.\n";
        return;
    }

    auto &bank = SelectBank(banks);

    std::string fname = GetValidString("Enter first name: ");
    std::string lname = GetValidString("Enter last name: ");
    i32 age = GetValidInt("Enter age: ", 1, 120);

    bank->AddCustomer(fname, lname, age);
}

void ViewAllBanks(std::vector<std::unique_ptr<Bank::Bank>> &banks)
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

void ViewAllCustomer(std::vector<std::unique_ptr<Bank::Bank>> &banks)
{
    if (banks.empty())
    {
        std::cerr << "Error: No banks available.\n";
        return;
    }

    auto &bank = SelectBank(banks);

    if (bank->GetNumberOfCustomers() == 0)
    {
        std::cerr << "Error: No customers available in this bank.\n";
        return;
    }

    std::cout << "\n========= All Customers =========\n";
    bank->ViewAllCustomers();
}

void SearchForBank(const std::vector<std::unique_ptr<Bank::Bank>> &banks)
{
    if (banks.empty())
    {
        std::cerr << "Error: No banks available.\n";
        return;
    }

    i32 bank_id = GetValidInt("Enter bank ID: ", 0, std::numeric_limits<i32>::max());

    auto it = std::lower_bound(banks.begin(), banks.end(), bank_id, [](const std::unique_ptr<Bank::Bank> &b, i32 bank_id)
                               { return b->GetID() < bank_id; });

    if (it != banks.end() && (*it)->GetID() == bank_id)
    {
        std::cout << "Bank found!\n";
        std::cout << "Bank Name: " << (*it)->GetName() << "\n";
        std::cout << "Bank ID: " << (*it)->GetID() << "\n";
    }
    else
    {
        std::cerr << "Error: Bank not found.\n";
    }
}

void SearchForCustomer(std::vector<std::unique_ptr<Bank::Bank>> &banks)
{
    if (banks.empty())
    {
        std::cerr << "Error: No banks available.\n";
        return;
    }

    auto &bank = SelectBank(banks);

    if (bank->GetNumberOfCustomers() == 0)
    {
        std::cerr << "Error: No customers available in this bank.\n";
        return;
    }

    i32 customer_id = GetValidInt("Enter customer ID: ", 0, std::numeric_limits<i32>::max());

    auto it = std::lower_bound(bank->GetCustomers().begin(), bank->GetCustomers().end(), customer_id,
                               [](const std::unique_ptr<Bank::Customer> &c, i32 customer_id)
                               {
                                   return c->GetID() < customer_id;
                               });

    if (it != bank->GetCustomers().end() && (*it)->GetID() == customer_id)
    {
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

// ==============================
// ACCOUNT & TRANSACTION FUNCTIONS
// ==============================

void AddAccount(std::vector<std::unique_ptr<Bank::Bank>> &banks)
{
    if (banks.empty())
    {
        std::cerr << "Error: No banks available. Create a bank first.\n";
        return;
    }

    auto &bank = SelectBank(banks);

    if (bank->GetNumberOfCustomers() == 0)
    {
        std::cerr << "Error: No customers available. Add a customer first.\n";
        return;
    }

    auto &customer = SelectCustomer(bank);

    i32 account_type = GetValidInt("Enter account type (0: CHECKING, 1: SAVING): ", 0, 1);
    f64 balance = GetValidFloat("Enter initial balance: ", 0.0);

    customer->CreateBankAccount(static_cast<Bank::AccountType>(account_type), balance);
}

void AddTransaction(std::vector<std::unique_ptr<Bank::Bank>> &banks)
{
    if (banks.empty())
    {
        std::cerr << "Error: No banks available. Create a bank first.\n";
        return;
    }

    auto &bank = SelectBank(banks);

    if (bank->GetNumberOfCustomers() == 0)
    {
        std::cerr << "Error: No customers available. Add a customer first.\n";
        return;
    }

    auto &customer = SelectCustomer(bank);

    if (customer->GetNumberOfAccounts() == 0)
    {
        std::cerr << "Error: No accounts available. Create an account first.\n";
        return;
    }

    auto &account = SelectAccount(customer);

    i32 transaction_type = GetValidInt("Enter transaction type (0: DEPOSIT, 1: WITHDRAW, 2: TRANSFER): ", 0, 2);

    if (static_cast<Bank::TransactionType>(transaction_type) == Bank::TransactionType::TRANSFER)
    {
        i32 num_of_accounts = customer->GetAccounts().size();
        if (!(num_of_accounts >= 2))
        {
            std::cerr << "Error: You must have at least two accounts to transfer funds.\n";
            return;
        }

        f64 amount = GetValidFloat("Enter transaction amount: ", 1.0);

        if (amount > account->GetBalance())
        {
            std::cerr << "Error: You can't transfer more money than your current balance.\n";
            return;
        }

        i32 transaction_account_index = GetValidInt("Enter the index of the account you want to tranfer funds to: ", 0, num_of_accounts - 1);

        account->CreateTransaction(static_cast<Bank::TransactionType>(transaction_type), amount, transaction_account_index);
    }
    else
    {
        f64 amount = GetValidFloat("Enter transaction amount: ", 1.0);
        account->CreateTransaction(static_cast<Bank::TransactionType>(transaction_type), amount);
    }
}

void ViewAllAccounts(std::vector<std::unique_ptr<Bank::Bank>> &banks)
{
    if (banks.empty())
    {
        std::cerr << "Error: No banks available.\n";
        return;
    }

    auto &bank = SelectBank(banks);

    if (bank->GetNumberOfCustomers() == 0)
    {
        std::cerr << "Error: No customers available in this bank.\n";
        return;
    }

    auto &customer = SelectCustomer(bank);

    if (customer->GetNumberOfAccounts() == 0)
    {
        std::cerr << "Error: This customer has no accounts.\n";
        return;
    }

    std::cout << "\n========= Customer's Accounts =========\n";
    customer->ViewCustomerAccounts();
}

void ViewAllTransactions(std::vector<std::unique_ptr<Bank::Bank>> &banks)
{
    if (banks.empty())
    {
        std::cerr << "Error: No banks available.\n";
        return;
    }

    auto &bank = SelectBank(banks);

    if (bank->GetNumberOfCustomers() == 0)
    {
        std::cerr << "Error: No customers available in this bank.\n";
        return;
    }

    auto &customer = SelectCustomer(bank);

    if (customer->GetNumberOfAccounts() == 0)
    {
        std::cerr << "Error: This customer has no accounts.\n";
        return;
    }

    auto &account = SelectAccount(customer);

    if (account->GetNumberOfTransactions() == 0)
    {
        std::cerr << "Error: This account has no transactions.\n";
        return;
    }

    std::cout << "\n========= Account Transactions =========\n";
    account->ViewAccountTransactions();
}

void SearchForAccount(std::vector<std::unique_ptr<Bank::Bank>> &banks)
{
    if (banks.empty())
    {
        std::cerr << "Error: No banks available.\n";
        return;
    }

    auto &bank = SelectBank(banks);

    if (bank->GetNumberOfCustomers() == 0)
    {
        std::cerr << "Error: No customers available in this bank.\n";
        return;
    }

    auto &customer = SelectCustomer(bank);

    if (customer->GetNumberOfAccounts() == 0)
    {
        std::cerr << "Error: This customer has no accounts.\n";
        return;
    }

    std::string account_id = GetValidString("Enter account ID: ");

    auto it = std::lower_bound(customer->GetAccounts().begin(), customer->GetAccounts().end(), account_id,
                               [](const std::unique_ptr<Bank::BankAccount> &a, const std::string &account_id)
                               {
                                   return a->GetID() < account_id;
                               });

    if (it != customer->GetAccounts().end() && (*it)->GetID() == account_id)
    {
        std::cout << "Account found!\n";
        std::cout << "Account ID: " << (*it)->GetID() << "\n";
        std::cout << "Balance: $" << (*it)->GetBalance() << "\n";
    }
    else
    {
        std::cerr << "Error: Account not found.\n";
    }
}

void SearchForTransaction(std::vector<std::unique_ptr<Bank::Bank>> &banks)
{
    if (banks.empty())
    {
        std::cerr << "Error: No banks available.\n";
        return;
    }

    auto &bank = SelectBank(banks);

    if (bank->GetNumberOfCustomers() == 0)
    {
        std::cerr << "Error: No customers available in this bank.\n";
        return;
    }

    auto &customer = SelectCustomer(bank);

    if (customer->GetNumberOfAccounts() == 0)
    {
        std::cerr << "Error: This customer has no accounts.\n";
        return;
    }

    auto &account = SelectAccount(customer);

    if (account->GetNumberOfTransactions() == 0)
    {
        std::cerr << "Error: This account has no transactions.\n";
        return;
    }

    i32 transaction_id = GetValidInt("Enter transaction ID: ", 0, std::numeric_limits<i32>::max());

    auto &transactions = account->GetTransactions();
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
