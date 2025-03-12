#pragma once

#include "types.hpp"
#include "transaction_type.hpp"
#include <string>
#include <memory>
#include <iomanip>

namespace Bank
{
    class BankAccount;

    class Transaction
    {
    private:
        i32 m_transaction_id;
        BankAccount &m_associated_account;
        f64 m_transaction_amount;
        std::string m_destination_account_id;
        TransactionType m_transaction_type;
        f64 m_balance_before_transaction;
        f64 m_balance_after_transaction;
        bool m_was_invalid = false;

        void ExecuteTransaction();
        void GenerateTransactionID();

    public:
        Transaction() = default;
        Transaction(BankAccount &account, f64 amount, TransactionType transaction_type, const std::string &destination_account_id);
        ~Transaction();

        const inline i32 GetTransactionID() const { return m_transaction_id; }
        void DisplayTransaction() const;
        const inline f64 GetTransactionAmount() const { return m_transaction_amount; }
        const inline f64 GetBalanceBeforeTransaction() const { return m_balance_before_transaction; }
        const inline f64 GetBalanceAfterTransaction() const { return m_balance_after_transaction; }
        const std::string GetTransactionType() const;
        const inline bool WasInvalid() const { return m_was_invalid; }
    };
}
