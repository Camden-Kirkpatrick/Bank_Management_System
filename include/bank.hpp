#pragma once

#include "customer.hpp"
#include "types.hpp"
#include <iostream>
#include <string>
#include <memory>
#include <vector>

namespace Bank
{
    class Customer;
    class Bank
    {
    private:
        i32 m_bank_id;
        std::string m_bank_name;
        std::vector<std::unique_ptr<Customer>> m_customers;
        void GenerateID();

    public:
        Bank() = default;
        Bank(const std::string &bank_name);
        ~Bank();

        void AddCustomer(const std::string &fname, const std::string &lname, i32 age);
        void ViewAllCustomers() const;
        inline std::string GetName() const { return m_bank_name; }
        inline i32 GetID() const { return m_bank_id; }
        inline i32 GetNumberOfCustomers() const { return m_customers.size(); }
        inline const std::unique_ptr<Customer> &GetCustomer(i32 index) const { return m_customers[index]; }
        inline const std::vector<std::unique_ptr<Customer>> &GetCustomers() const { return m_customers; }
    };
}
