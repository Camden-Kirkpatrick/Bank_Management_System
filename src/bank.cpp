/**
 * @file bank.cpp
 * @brief This file implements the Bank class, which manages customers and applies interest to their accounts.
 */

#include "../include/bank.hpp"
#include "../include/bank_account.hpp"
#include "../include/global.hpp"
#include <random>
#include <exception>
#include <algorithm>
#include <iostream>

namespace Bank
{
    /**
     * @class Bank
     * @brief Represents a bank containing multiple customers.
     */

    /**
     * @brief Constructs a Bank with a given name and generates a random ID.
     * @param bank_name The name of the Bank.
     */
    Bank::Bank(const std::string &bank_name) : m_bank_name(bank_name)
    {
        GenerateID();
        std::cout << "Bank created: " << m_bank_name << " (Bank ID: " << m_bank_id << ")" << std::endl;
    }

    /**
     * @brief Destructor for the Bank class.
     */
    Bank::~Bank()
    {
        // Let the user know when a Bank object is being destroyed
        std::cout << "\nDeleting bank" << std::endl;
    }

    /**
     * @brief Generates a random Bank ID in the range [MIN_BANK_ID, MAX_BANK_ID].
     */
    void Bank::GenerateID()
    {
        std::random_device rd; // Used to generate a truly random seed
        m_bank_id = rd() % (MAX_BANK_ID - MIN_BANK_ID + 1) + MIN_BANK_ID;
    }

    /**
     * @brief Creates and adds a new Customer to this Bank in sorted order by ID.
     * @param fname Customer's first name.
     * @param lname Customer's last name.
     * @param age Customer's age.
     */
    void Bank::AddCustomer(const std::string &fname, const std::string &lname, i32 age)
    {
        // Ensure we have space in the customers vector
        if (m_customers.capacity() == 0)
        {
            m_customers.reserve(50);
        }

        // Create a new Customer object on the heap
        std::unique_ptr<Customer> new_customer = std::make_unique<Customer>(fname, lname, age);

        // Insert the new Customer in sorted order by their ID
        auto it = std::lower_bound(
            m_customers.begin(), m_customers.end(), new_customer,
            [](const std::unique_ptr<Customer> &a, const std::unique_ptr<Customer> &b)
            {
                return a->GetID() < b->GetID();
            });

        m_customers.insert(it, std::move(new_customer));
    }

    /**
     * @brief Outputs all customers' information for this bank.
     */
    void Bank::ViewAllCustomers() const
    {
        // Print each customer's info, preceded by a header line
        for (size_t i = 0; i < m_customers.size(); i++)
        {
            std::cout << "---------------------------------" << std::endl;
            std::cout << "Customer #" << i + 1 << std::endl;
            m_customers[i]->DisplayCustomerInfo();
        }
        std::cout << "---------------------------------" << std::endl;
    }

    /**
     * @brief Applies interest to all SavingAccount objects in this Bank.
     */
    void Bank::ApplyInterestToAllAccounts()
    {
        // For each customer, for each account, if it's a SavingAccount, apply interest
        for (const auto &customer : m_customers)
        {
            for (const auto &account : customer->GetAccounts())
            {
                if (auto *saving_acc = dynamic_cast<SavingAccount *>(account.get()))
                {
                    saving_acc->ApplyInterest();
                }
            }
        }
    }
}
