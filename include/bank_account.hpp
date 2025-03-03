#pragma once

#include "customer.hpp"
#include "types.hpp"
#include "account_type.hpp"
#include "transaction.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <memory>

namespace Bank
{
    class BankAccount
    {
    public:
        BankAccount() = default;
        BankAccount(AccountType account_type, Customer &customer, f64 balance);
        virtual ~BankAccount();

        void Withdraw(f64 amount);
        void Deposit(f64 amount);
        void Transfer(i32 account_index, f64 amount);
        virtual void ApplyOverdraftFee(f64 fee) {}
        void CreateTransaction(TransactionType transaction_type, f64 amount, i32 transfer_account_index = -1);
        void ViewAccountTransactions() const;
        inline std::string GetID() const { return m_account_id; }
        inline f64 GetBalance() const { return m_balance; }
        inline Customer &GetAccountOwner() const { return m_associated_customer; }
        inline AccountType GetAccountType() const { return m_account_type; }
        inline i32 GetNumberOfTransactions() const { return m_transactions.size(); }
        inline const std::vector<std::unique_ptr<Transaction>> &GetTransactions() const { return m_transactions; }

    private:
        AccountType m_account_type;
        std::vector<std::unique_ptr<Transaction>> m_transactions;
        void GenerateAccountID();

    protected:
        std::string m_account_id;
        f64 m_balance;
        Customer &m_associated_customer;
    };

    class CheckingAccount : public BankAccount
    {
    public:
        CheckingAccount() = default;
        CheckingAccount(AccountType account_type, Customer &customer, f64 balance);
        ~CheckingAccount() override = default;

        // void ApplyOverdraftFee(f64 fee);
        void ApplyOverdraftFee(f64 fee) override
        {
            m_balance -= fee;
            std::cout << "Overdraft fee of $" << fee << " applied to Checking Account (ID: " << m_account_id << ")\n";
        }
    };

    class SavingAccount : public BankAccount
    {
    public:
        SavingAccount() = default;
        SavingAccount(AccountType account_type, Customer &customer, f64 balance);
        ~SavingAccount() override = default;

        void ApplyInterest(f64 rate);
    };
}
