#pragma once

#include "types.hpp"
#include "account_type.hpp"
#include "transaction.hpp"
#include <string>
#include <vector>
#include <memory>

namespace Bank
{
    class Customer
    {
    private:
        i32 m_customer_id;
        std::string m_fName;
        std::string m_lName;
        i32 m_age;
        std::vector<std::unique_ptr<BankAccount>> m_accounts;
        void GenerateCustomerID();

    public:
        Customer() = default;
        Customer(const std::string &fName, const std::string &lName, i32 age);
        ~Customer();

        void DisplayCustomerInfo() const;
        void CreateBankAccount(AccountType account_type, f64 account_initial_balance);
        void ViewCustomerAccounts() const;
        inline i32 GetID() const { return m_customer_id; }
        inline std::string GetName() const { return m_fName + " " + m_lName; }
        inline i32 GetAge() const { return m_age; }
        inline i32 GetNumberOfAccounts() const { return m_accounts.size(); }
        const inline std::vector<std::unique_ptr<BankAccount>> &GetAccounts() const { return m_accounts; }
    };
}
