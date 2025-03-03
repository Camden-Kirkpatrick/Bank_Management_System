#include "../include/bank.hpp"
#include "../include/constants.hpp"
#include <random>
#include <exception>
#include <algorithm>
#include <iostream>

namespace Bank
{
    Bank::Bank(const std::string &bank_name) : m_bank_name(bank_name)
    {
        GenerateID();
        std::cout << "Bank created: " << m_bank_name << " (Bank ID: " << m_bank_id << ")" << std::endl;
    }

    Bank::~Bank()
    {
        std::cout << "\nDeleting " << this->GetName() << " bank" << std::endl;
    }

    void Bank::GenerateID()
    {
        std::random_device rd;
        // Generate a random bank ID between 100,000,000 and 999,999,999, including both bounds
        m_bank_id = rd() % (MAX_BANK_ID - MIN_BANK_ID + 1) + MIN_BANK_ID;
    }

    void Bank::AddCustomer(const std::string &fname, const std::string &lname, i32 age)
    {
        if (m_customers.capacity() == 0)
        {
            m_customers.reserve(50);
        }

        auto new_customer = std::make_unique<Customer>(fname, lname, age);

        // Find the correct insertion point
        auto it = std::lower_bound(
            m_customers.begin(), m_customers.end(), new_customer,
            [](const std::unique_ptr<Customer> &a, const std::unique_ptr<Customer> &b)
            {
                return a->GetID() < b->GetID();
            });

        // Insert customer at the correct position
        m_customers.insert(it, std::move(new_customer));
    }

    void Bank::ViewAllCustomers() const
    {
        for (size_t i = 0; i < m_customers.size(); i++)
        {
            std::cout << "---------------------------------" << std::endl;
            std::cout << "Customer #" << i + 1 << std::endl;
            m_customers[i]->DisplayCustomerInfo();
        }
        std::cout << "---------------------------------" << std::endl;
    }
}
