/**
 * @file bank_account.cpp
 * @brief Implements the BankAccount class hierarchy (CheckingAccount, SavingAccount),
 *        including core functionality and transaction management.
 */

#include "../include/bank_account.hpp"
#include "../include/transaction_type.hpp"
#include "../include/utilities.hpp"
#include "../include/transaction.hpp"
#include "../include/global.hpp"
#include <iostream>
#include <cassert>
#include <random>
#include <iomanip>
#include <memory>
#include <algorithm>

namespace Bank
{
    /**
     * @class BankAccount
     * @brief Abstract base class for different types of bank accounts.
     */

    /**
     * @brief Constructs a BankAccount object.
     * @param account_type The type of this bank account (CHECKING or SAVING).
     * @param customer A reference to the Customer who owns this account.
     * @param balance The initial balance of this account.
     */
    BankAccount::BankAccount(AccountType account_type, Customer &customer, f64 balance)
        : m_account_type(account_type), m_associated_customer(customer), m_balance(balance)
    {
        GenerateAccountID(); // Automatically assign a unique ID upon construction
    }

    /**
     * @brief Virtual destructor for BankAccount.
     */
    BankAccount::~BankAccount()
    {
        // Log a message when deleting a BankAccount
        std::cout << "Deleting bank account" << std::endl;
    }

    /**
     * @class CheckingAccount
     * @brief Derived class representing a checking account with overdraft protection.
     */

    /**
     * @brief Constructs a CheckingAccount object.
     * @param account_type The type of this account (should be CHECKING).
     * @param customer A reference to the Customer who owns this account.
     * @param balance The initial balance of this checking account.
     */
    CheckingAccount::CheckingAccount(AccountType account_type, Customer &customer, f64 balance)
        : BankAccount(account_type, customer, balance)
    {
        std::cout << "Checking account created for " << m_associated_customer.GetName()
                  << " (Account ID: " << m_account_id << ")" << std::endl;
    }

    /**
     * @class SavingAccount
     * @brief Derived class representing a savings account with interest accrual.
     */

    /**
     * @brief Constructs a SavingAccount object.
     * @param account_type The type of this account (should be SAVING).
     * @param customer A reference to the Customer who owns this account.
     * @param balance The initial balance of this savings account.
     */
    SavingAccount::SavingAccount(AccountType account_type, Customer &customer, f64 balance)
        : BankAccount(account_type, customer, balance)
    {
        std::cout << "Saving account created for " << m_associated_customer.GetName()
                  << " (Account ID: " << m_account_id << ")" << std::endl;
    }

    /**
     * @brief Deposits the specified amount into this account.
     * @param amount The amount to deposit.
     */
    void BankAccount::Deposit(f64 amount)
    {
        // Simply add to the current balance
        m_balance += amount;
        std::cout << m_associated_customer.GetName() << " deposited $" << amount
                  << " into their account (Account ID: " << m_account_id << ")" << std::endl;
    }

    /**
     * @brief Transfers a specified amount from this BankAccount to another of the same Customer, by destination account ID.
     * @param destination_account_id The ID of the account to which the amount should be transferred.
     * @param amount The amount to transfer.
     */
    void BankAccount::Transfer(const std::string &destination_account_id, f64 amount)
    {
        // Deduct from the source account
        m_balance -= amount;

        // Locate the destination account via the same Customer
        BankAccount *const destAccount = FindAccount(&this->GetAccountOwner(), destination_account_id);
        if (!destAccount)
        {
            std::cerr << "Error: Destination account not found. Transfer aborted.\n";
            return;
        }

        // Credit the destination account
        destAccount->m_balance += amount;
    }

    /**
     * @brief Generates a unique account ID for this BankAccount,
     *        based on the account type (Checking or Saving) and a random ID.
     */
    void BankAccount::GenerateAccountID()
    {
        // Generate a random integer, then attach 'C' or 'S' depending on account type
        i32 temp_id;
        std::random_device rd;
        temp_id = rd() % (MAX_ACCOUNT_ID - MIN_ACCOUNT_ID + 1) + MIN_ACCOUNT_ID;

        if (m_account_type == AccountType::CHECKING)
        {
            m_account_id = std::to_string(temp_id) + 'C';
        }
        else if (m_account_type == AccountType::SAVING)
        {
            m_account_id = std::to_string(temp_id) + 'S';
        }
    }

    /**
     * @brief Creates a new Transaction object associated with this account and inserts it in sorted order by transaction ID.
     * @param transaction_type The type of transaction (DEPOSIT, WITHDRAW, or TRANSFER).
     * @param amount The transaction amount.
     * @param destination_account_id The ID of the destination account if this is a TRANSFER; otherwise, an empty string.
     */
    void BankAccount::CreateTransaction(TransactionType transaction_type, f64 amount, const std::string &destination_account_id)
    {
        // Ensure there's enough capacity for new transactions
        if (m_transactions.capacity() == 0)
        {
            m_transactions.reserve(100);
        }

        // Create the new Transaction
        std::unique_ptr<Transaction> new_transaction =
            std::make_unique<Transaction>(*this, amount, transaction_type, destination_account_id);

        // Insert transaction in sorted order by transaction ID
        auto it = std::lower_bound(
            m_transactions.begin(), m_transactions.end(), new_transaction,
            [](const std::unique_ptr<Transaction> &a, const std::unique_ptr<Transaction> &b)
            {
                return a->GetTransactionID() < b->GetTransactionID();
            });

        m_transactions.insert(it, std::move(new_transaction));
    }

    /**
     * @brief Displays all transactions associated with this bank account.
     */
    void BankAccount::ViewAccountTransactions() const
    {
        // Loop through each transaction and display its details
        std::cout << "Transactions for account #" << m_account_id << ":\n";
        std::cout << "--------------------------------\n";
        for (size_t i = 0; i < m_transactions.size(); i++)
        {
            std::cout << "Transaction #" << (i + 1) << std::endl;
            m_transactions[i]->DisplayTransaction();
            std::cout << "--------------------------------\n";
        }
    }

    /**
     * @brief Withdraws a specified amount from this checking account, respecting the overdraft limit.
     * @param amount The amount to withdraw.
     * @return True if the withdrawal succeeds, false if it fails due to overdraft limit.
     */
    bool CheckingAccount::Withdraw(f64 amount)
    {
        // Check if this withdrawal would exceed the overdraft limit
        if ((m_balance - amount) < -OVERDRAFT_LIMIT)
        {
            std::cerr << "Error: Overdraft limit exceeded. Transaction denied.\n";
            return false;
        }

        m_balance -= amount;

        // If the new balance is below zero, apply an overdraft fee
        if (m_balance < 0)
        {
            ApplyOverdraftFee();
        }

        std::cout << m_associated_customer.GetName()
                  << " withdrew $" << amount
                  << " from their Checking Account (ID: " << m_account_id
                  << ")." << std::endl;

        return true;
    }

    /**
     * @brief Applies an overdraft fee to this checking account if the balance is negative.
     */
    void CheckingAccount::ApplyOverdraftFee()
    {
        // Deduct a fixed overdraft fee
        m_balance -= OVERDRAFT_FEE;
        std::cout << "Overdraft fee of $" << OVERDRAFT_FEE
                  << " applied to " << m_associated_customer.GetName()
                  << "'s Checking Account (ID: " << m_account_id
                  << ")." << std::endl;
    }

    /**
     * @brief Withdraws a specified amount from this savings account if sufficient funds are available.
     * @param amount The amount to withdraw.
     * @return True if the withdrawal succeeds, false if insufficient funds.
     */
    bool SavingAccount::Withdraw(f64 amount)
    {
        // Cannot go negative for a savings account
        if (m_balance < amount)
        {
            std::cerr << "Error: Insufficient funds to withdraw $"
                      << amount << " from " << m_associated_customer.GetName()
                      << "'s account (Account ID: " << m_account_id << ")\n";
            return false;
        }

        m_balance -= amount;
        std::cout << m_associated_customer.GetName()
                  << " withdrew $" << amount
                  << " from their Saving Account (ID: " << m_account_id << ")\n";
        return true;
    }

    /**
     * @brief Applies interest to this savings account based on the global INTEREST_RATE.
     */
    void SavingAccount::ApplyInterest()
    {
        // Ensure that the global interest rate is valid
        if (INTEREST_RATE < 0)
        {
            std::cerr << "Error: Interest rate cannot be negative.\n";
            return;
        }

        // Calculate interest and update the balance
        f64 interest = m_balance * INTEREST_RATE;
        m_balance += interest;
    }
}
