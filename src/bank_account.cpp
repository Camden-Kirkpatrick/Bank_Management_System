#include "../include/bank_account.hpp"
#include "../include/transaction_type.hpp"
#include "../include/constants.hpp"
#include <iostream>
#include <cassert>
#include <random>
#include <iomanip>
#include <algorithm>

namespace Bank
{
    BankAccount::BankAccount(AccountType account_type, Customer &customer, f64 balance)
        : m_account_type(account_type), m_associated_customer(customer), m_balance(balance)
    {
        GenerateAccountID();
    }

    CheckingAccount::CheckingAccount(AccountType account_type, Customer &customer, f64 balance)
        : BankAccount(account_type, customer, balance)
    {
        std::cout << "Checking account created for " << m_associated_customer.GetName() << " (Account ID: " << m_account_id << ")" << std::endl;
    }

    SavingAccount::SavingAccount(AccountType account_type, Customer &customer, f64 balance)
        : BankAccount(account_type, customer, balance)
    {
        std::cout << "Saving account created for " << m_associated_customer.GetName() << " (Account ID: " << m_account_id << ")" << std::endl;
    }

    BankAccount::~BankAccount()
    {
        std::cout << "Deleting " << m_associated_customer.GetName() << "'s account (Account ID: " << m_account_id << ")" << std::endl;
    }

    void BankAccount::Withdraw(f64 amount)
    {
        m_balance -= amount;
        std::cout << m_associated_customer.GetName() << " withdrew $" << amount << " from their account (Account ID: " << m_account_id << ")" << std::endl;
    }

    void BankAccount::Deposit(f64 amount)
    {
        m_balance += amount;
        std::cout << m_associated_customer.GetName() << " deposited $" << amount << " into their account (Account ID: " << m_account_id << ")" << std::endl;
    }

    void BankAccount::Transfer(i32 account_index, f64 amount)
    {
        this->m_balance -= amount;
        BankAccount &destination_account = *(this->GetAccountOwner().GetAccount(account_index));
        destination_account.m_balance += amount;
    }

    void BankAccount::GenerateAccountID()
    {
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

    void BankAccount::CreateTransaction(TransactionType transaction_type, f64 amount, i32 transfer_account_index)
    {
        if (m_transactions.capacity() == 0)
        {
            m_transactions.reserve(100);
        }

        auto new_transaction = std::make_unique<Transaction>(*this, amount, transaction_type, transfer_account_index);

        // Insert transaction in sorted order instead of sorting after insertion
        auto it = std::lower_bound(
            m_transactions.begin(), m_transactions.end(), new_transaction,
            [](const std::unique_ptr<Transaction> &a, const std::unique_ptr<Transaction> &b)
            {
                return a->GetTransactionID() < b->GetTransactionID();
            });

        m_transactions.insert(it, std::move(new_transaction)); // Move ownership into the sorted position
    }

    void BankAccount::ViewAccountTransactions() const
    {
        std::cout << "Transactions for account #" << m_account_id << ":" << std::endl;
        std::cout << "--------------------------------" << std::endl;
        for (size_t i = 0; i < m_transactions.size(); i++)
        {
            std::cout << "Transaction #" << (i + 1) << std::endl;
            m_transactions[i]->DisplayTransaction();
            std::cout << "--------------------------------" << std::endl;
        }
    }

    // void CheckingAccount::ApplyOverdraftFee(f64 fee)
    // {
    //     m_balance -= fee;
    //     std::cout << "Overdraft fee applied!" << std::endl;
    // }

    void SavingAccount::ApplyInterest(f64 rate)
    {
        m_balance += m_balance * rate;
        std::cout << "Interest applied. Current balance: $" << m_balance << std::endl;
    }

    // void BankAccount::SortTransactionsByID()
    // {
    //     std::sort(m_transactions.begin(), m_transactions.end(),
    //               [](const std::unique_ptr<Transaction> &a, const std::unique_ptr<Transaction> &b)
    //               {
    //                   return a->GetTransactionID() < b->GetTransactionID();
    //               });
    // }
}
