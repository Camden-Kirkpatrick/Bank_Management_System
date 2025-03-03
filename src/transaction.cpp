#include "../include/bank_account.hpp"
#include "../include/constants.hpp"
#include <iostream>
#include <cassert>
#include <random>

namespace Bank
{
    Transaction::Transaction(BankAccount &account, f64 amount, TransactionType transaction_type, i32 transfer_account_index)
        : m_associated_account(account), m_transaction_amount(amount), m_transaction_type(transaction_type), m_transfer_account_index(transfer_account_index)
    {

        GenerateTransactionID();
        std::cout << "Transaction created for " << m_associated_account.GetAccountOwner().GetName()
                  << " (Transaction ID: " << m_transaction_id << ")" << std::endl;
        ExecuteTransaction();
    }

    Transaction::~Transaction()
    {
        std::cout << "Deleting transaction " << m_transaction_id << std::endl;
    }

    void Transaction::ExecuteTransaction()
    {
        m_balance_before_transaction = m_associated_account.GetBalance();
        if (m_transaction_type == TransactionType::DEPOSIT)
        {
            m_associated_account.Deposit(m_transaction_amount);
        }
        else if (m_transaction_type == TransactionType::WITHDRAW)
        {
            // Check for overdraft
            if (m_associated_account.GetAccountType() == AccountType::CHECKING && m_transaction_amount > m_associated_account.GetBalance())
            {
                m_associated_account.Withdraw(m_associated_account.GetBalance());
                m_associated_account.ApplyOverdraftFee(50);
            }
            else
                m_associated_account.Withdraw(m_transaction_amount);
        }
        else
        {
            m_associated_account.Transfer(m_transfer_account_index, m_transaction_amount);
        }
        m_balance_after_transaction = m_associated_account.GetBalance();
    }

    void Transaction::GenerateTransactionID()
    {
        std::random_device rd;
        m_transaction_id = rd() % (MAX_TRANSACTION_ID - MIN_TRANSACTION_ID + 1) + MIN_TRANSACTION_ID;
    }

    void Transaction::DisplayTransaction() const
    {
        std::string transaction_type;
        switch (m_transaction_type)
        {
        case TransactionType::DEPOSIT:
            transaction_type = "Deposit";
            break;
        case TransactionType::WITHDRAW:
            transaction_type = "Withdraw";
            break;
        default:
            transaction_type = "Transfer";
            break;
        }

        std::cout << "Transaction ID: " << m_transaction_id << std::endl;
        std::cout << "Transaction Type: " << transaction_type << std::endl;
        std::cout << "Transaction Amount: $" << m_transaction_amount << std::endl;
        std::cout << "Balance before transaction: $" << m_balance_before_transaction << std::endl;
        std::cout << "Balance after transaction: $" << m_balance_after_transaction << std::endl;
    }

}