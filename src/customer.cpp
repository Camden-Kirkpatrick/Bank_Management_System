/**
 * @file customer.cpp
 * @brief This file implements the Customer class, which manages the creation and viewing of
 *        multiple BankAccounts and stores identifying information about the Customer.
 */

#include "../include/bank_account.hpp"
#include "../include/account_type.hpp"
#include "../include/transaction.hpp"
#include "../include/customer.hpp"
#include "../include/types.hpp"
#include "../include/global.hpp"
#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <random>
#include <algorithm>

namespace Bank
{
    /**
     * @class Customer
     * @brief Represents a single customer with a unique ID, name, and age, who can have multiple bank accounts.
     */

    /**
     * @brief Constructs a Customer with given first name, last name, and age. Also generates a random Customer ID.
     * @param fName Customer's first name.
     * @param lName Customer's last name.
     * @param age Customer's age.
     */
    Customer::Customer(const std::string &fName, const std::string &lName, i32 age)
        : m_fName(fName), m_lName(lName), m_age(age)
    {
        // Immediately generate a unique ID for this customer
        GenerateCustomerID();
        std::cout << "Customer created: " << this->GetName()
                  << " (Customer ID: " << m_customer_id << ")" << std::endl;
    }

    /**
     * @brief Destructor for the Customer class.
     */
    Customer::~Customer()
    {
        // Notify that this customer is being deleted
        std::cout << "Deleting customer" << std::endl;
    }

    /**
     * @brief Generates a random ID for this Customer in the range [MIN_CUSTOMER_ID, MAX_CUSTOMER_ID].
     */
    void Customer::GenerateCustomerID()
    {
        std::random_device rd; // For random seeding
        m_customer_id = rd() % (MAX_CUSTOMER_ID - MIN_CUSTOMER_ID + 1) + MIN_CUSTOMER_ID;
    }

    /**
     * @brief Displays the Customer's basic information (ID, first name, last name, and age).
     */
    void Customer::DisplayCustomerInfo() const
    {
        // Print out the key details of this Customer
        std::cout << "Customer ID: " << m_customer_id << std::endl;
        std::cout << "First name: " << m_fName << std::endl;
        std::cout << "Last name: " << m_lName << std::endl;
        std::cout << "Age: " << m_age << std::endl;
    }

    /**
     * @brief Creates a new BankAccount (Checking or Saving) for this Customer and inserts it in sorted order by ID.
     * @param account_type The type of the account (CHECKING or SAVING).
     * @param account_initial_balance The initial balance of the account.
     */
    void Customer::CreateBankAccount(AccountType account_type, f64 account_initial_balance)
    {
        // If our vector wasn't preallocated, reserve space for up to 5 accounts
        if (m_accounts.capacity() == 0)
        {
            m_accounts.reserve(5);
        }

        // Use a unique_ptr to store new Checking/Saving account
        std::unique_ptr<BankAccount> new_account;

        if (account_type == AccountType::CHECKING)
            new_account = std::make_unique<CheckingAccount>(account_type, *this, account_initial_balance);
        else if (account_type == AccountType::SAVING)
            new_account = std::make_unique<SavingAccount>(account_type, *this, account_initial_balance);

        // Insert the account in the correct sorted position
        auto it = std::lower_bound(
            m_accounts.begin(), m_accounts.end(), new_account,
            [](const std::unique_ptr<BankAccount> &a, const std::unique_ptr<BankAccount> &b)
            {
                return a->GetID() < b->GetID();
            });

        m_accounts.insert(it, std::move(new_account));
    }

    /**
     * @brief Displays summary information (account ID and balance) for each BankAccount owned by this Customer.
     */
    void Customer::ViewCustomerAccounts() const
    {
        // Print basic info for each account (ID and balance)
        std::cout << this->GetName() << "'s accounts:" << std::endl;
        std::cout << "----------------------------" << std::endl;
        for (size_t i = 0; i < m_accounts.size(); i++)
        {
            std::cout << "Account #" << (i + 1) << std::endl;
            std::cout << "Account ID: " << m_accounts[i]->GetID() << std::endl;
            std::cout << "Account balance: $"
                      << std::fixed << std::setprecision(2)
                      << m_accounts[i]->GetBalance() << std::endl;
            std::cout << "----------------------------" << std::endl;
        }
    }
}
