/**
 * @file transaction.cpp
 * @brief This file implements the Transaction class, which represents a single transaction performed on a BankAccount.
 */

#include "../include/bank_account.hpp"
#include "../include/global.hpp"
#include <iostream>
#include <cassert>
#include <random>

namespace Bank
{
    /**
     * @class Transaction
     * @brief Represents a deposit, withdrawal, or transfer transaction performed on a BankAccount.
     */

    /**
     * @brief Constructs a Transaction and executes it immediately.
     * @param account A reference to the BankAccount on which the transaction is performed.
     * @param amount The transaction amount.
     * @param transaction_type The type of transaction (DEPOSIT, WITHDRAW, or TRANSFER).
     * @param transfer_account_index The index of the destination account for transfers (ignored otherwise).
     */
    Transaction::Transaction(BankAccount &account, f64 amount, TransactionType transaction_type, const std::string &destination_account_id)
        : m_associated_account(account), m_transaction_amount(amount),
          m_transaction_type(transaction_type), m_destination_account_id(destination_account_id)
    {
        GenerateTransactionID(); // Assign a unique random transaction ID
        std::cout << "Transaction created for " << m_associated_account.GetAccountOwner().GetName()
                  << " (Transaction ID: " << m_transaction_id << ")" << std::endl;
        ExecuteTransaction(); // Execute the transaction right upon creation
    }

    /**
     * @brief Destructor for the Transaction class.
     */
    Transaction::~Transaction()
    {
        // Log message when Transaction is destroyed
        std::cout << "Deleting transaction" << std::endl;
    }

    /**
     * @brief Executes the transaction by calling the appropriate method on the associated BankAccount.
     */
    void Transaction::ExecuteTransaction()
    {
        // Record the balance before
        m_balance_before_transaction = m_associated_account.GetBalance();

        // Decide which operation to perform based on transaction type
        if (m_transaction_type == TransactionType::DEPOSIT)
        {
            m_associated_account.Deposit(m_transaction_amount);
        }
        else if (m_transaction_type == TransactionType::WITHDRAW)
        {
            bool success = m_associated_account.Withdraw(m_transaction_amount);
            if (!success)
            {
                // Mark this transaction as invalid if withdrawal failed
                m_was_invalid = true;
            }
        }
        else
        {
            // Perform a Transfer
            m_associated_account.Transfer(m_destination_account_id, m_transaction_amount);
        }

        // Capture the balance after
        m_balance_after_transaction = m_associated_account.GetBalance();
    }

    /**
     * @brief Generates a random ID for this Transaction in the range [MIN_TRANSACTION_ID, MAX_TRANSACTION_ID].
     */
    void Transaction::GenerateTransactionID()
    {
        // Use a random_device for random seeding
        std::random_device rd;
        m_transaction_id = rd() % (MAX_TRANSACTION_ID - MIN_TRANSACTION_ID + 1) + MIN_TRANSACTION_ID;
    }

    /**
     * @brief Outputs all details about this Transaction, including ID, type, amount, and balance changes.
     */
    void Transaction::DisplayTransaction() const
    {
        std::string transaction_type = GetTransactionType();

        // Show transaction info to the console
        std::cout << "Transaction ID: " << m_transaction_id << std::endl;
        std::cout << "Transaction Type: " << transaction_type << std::endl;
        std::cout << "Transaction Amount: $" << m_transaction_amount << std::endl;
        std::cout << "Balance before transaction: $" << m_balance_before_transaction << std::endl;
        std::cout << "Balance after transaction: $" << m_balance_after_transaction << std::endl;
    }

    /**
     * @brief Returns a string representation of the TransactionType.
     * @return "Deposit", "Withdraw", or "Transfer".
     */
    const std::string Transaction::GetTransactionType() const
    {
        // Convert the enum to a user-readable string
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
        return transaction_type;
    }
}
