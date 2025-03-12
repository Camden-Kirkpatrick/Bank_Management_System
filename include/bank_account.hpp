#pragma once

#include "customer.hpp"
#include "types.hpp"
#include "account_type.hpp"
#include "transaction.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <chrono>

namespace Bank
{
    class BankAccount
    {
    public:
        BankAccount() = default;
        BankAccount(AccountType account_type, Customer &customer, f64 balance);
        virtual ~BankAccount();

        virtual bool Withdraw(f64 amount) = 0;
        virtual void ApplyInterest() {}
        virtual void ApplyOverdraftFee() {}

        void Deposit(const f64 amount);
        void Transfer(const std::string &account_index, const f64 amount);
        void CreateTransaction(TransactionType transaction_type, f64 amount, const std::string &destination_account_id = "");
        void ViewAccountTransactions() const;
        inline std::string GetID() const { return m_account_id; }
        const inline f64 GetBalance() const { return m_balance; }
        inline Customer &GetAccountOwner() const { return m_associated_customer; }
        inline AccountType GetAccountType() const { return m_account_type; }
        inline i32 GetNumberOfTransactions() const { return m_transactions.size(); }
        const inline std::vector<std::unique_ptr<Transaction>> &GetTransactions() const { return m_transactions; }

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
        CheckingAccount(AccountType account_type, Customer &customer, f64 balance);
        bool Withdraw(f64 amount) override;
        void ApplyOverdraftFee() override;
    };

    class SavingAccount : public BankAccount
    {
    public:
        SavingAccount(AccountType account_type, Customer &customer, f64 balance);
        bool Withdraw(f64 amount) override;
        void ApplyInterest() override;
    };

}
