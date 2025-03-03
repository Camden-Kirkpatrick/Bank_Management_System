#include "../include/bank_account.hpp"
#include "../include/account_type.hpp"
#include "../include/transaction.hpp"
#include "../include/customer.hpp"
#include "../include/types.hpp"
#include "../include/constants.hpp"
#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <random>
#include <algorithm>

namespace Bank
{
    Customer::Customer(const std::string &fName, const std::string &lName, i32 age)
        : m_fName(fName), m_lName(lName), m_age(age)
    {
        GenerateCustomerID();
        std::cout << "Customer created: " << this->GetName() << " (Customer ID: " << m_customer_id << ")" << std::endl;
    }

    Customer::~Customer()
    {
        std::cout << "Deleting " << this->GetName() << " customer" << std::endl;
    }

    void Customer::GenerateCustomerID()
    {
        std::random_device rd;
        m_customer_id = rd() % (MAX_CUSTOMER_ID - MIN_CUSTOMER_ID + 1) + MIN_CUSTOMER_ID;
    }

    void Customer::DisplayCustomerInfo() const
    {
        std::cout << "Customer ID: " << m_customer_id << std::endl;
        std::cout << "First name: " << m_fName << std::endl;
        std::cout << "Last name: " << m_lName << std::endl;
        std::cout << "Age: " << m_age << std::endl;
    }

    void Customer::CreateBankAccount(AccountType account_type, f64 account_initial_balance)
    {
        if (m_accounts.capacity() == 0)
        {
            m_accounts.reserve(5);
        }

        std::unique_ptr<BankAccount> new_account;

        if (account_type == AccountType::CHECKING)
            new_account = std::make_unique<CheckingAccount>(account_type, *this, account_initial_balance);
        else if (account_type == AccountType::SAVING)
            new_account = std::make_unique<SavingAccount>(account_type, *this, account_initial_balance);

        // Insert account in sorted order instead of sorting after insertion
        auto it = std::lower_bound(
            m_accounts.begin(), m_accounts.end(), new_account,
            [](const std::unique_ptr<BankAccount> &a, const std::unique_ptr<BankAccount> &b)
            {
                return a->GetID() < b->GetID();
            });

        m_accounts.insert(it, std::move(new_account)); // Move ownership into the sorted position
    }

    void Customer::ViewCustomerAccounts() const
    {
        std::cout << this->GetName() << "'s accounts:" << std::endl;
        std::cout << "----------------------------" << std::endl;
        for (size_t i = 0; i < m_accounts.size(); i++)
        {
            std::cout << "Account #" << (i + 1) << std::endl;
            std::cout << "Account ID: " << m_accounts[i]->GetID() << std::endl;
            std::cout << "Account balance: $" << m_accounts[i]->GetBalance() << std::endl;

            std::cout << "----------------------------" << std::endl;
        }
    }
}
