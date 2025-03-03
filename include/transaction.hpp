#pragma once

#include "types.hpp"
#include "transaction_type.hpp"
#include <string>
#include <memory>

namespace Bank
{
    class BankAccount;

    class Transaction
    {
    private:
        i32 m_transaction_id;
        BankAccount &m_associated_account;
        f64 m_transaction_amount;
        i32 m_transfer_account_index;
        TransactionType m_transaction_type;
        f64 m_balance_before_transaction;
        f64 m_balance_after_transaction;
        void ExecuteTransaction();
        void GenerateTransactionID();

    public:
        Transaction() = default;
        Transaction(BankAccount &account, f64 amount, TransactionType transaction_type, i32 transfer_account_index);
        ~Transaction();

        inline i32 GetTransactionID() const { return m_transaction_id; }
        void DisplayTransaction() const;
    };
}
