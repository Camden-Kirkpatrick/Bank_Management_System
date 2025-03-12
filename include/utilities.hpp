#pragma once

#include "bank_account.hpp"
#include "account_type.hpp"
#include "transaction.hpp"
#include "customer.hpp"
#include "bank.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <regex>

class Utility
{
public:
    /**
     * @brief Retrieves and validates user input of a numeric type T, ensuring it falls within [min, max].
     *
     * This function uses regular expressions to enforce integer-only input or up to two decimal places,
     * based on the enforce_two_decimals parameter. It continually prompts the user until a valid input
     * is provided.
     *
     * @tparam T A numeric data type (e.g., int, long long, double, etc.).
     * @param prompt The message displayed to the user before input.
     * @param min The minimum valid value for the input.
     * @param max The maximum valid value for the input.
     * @param enforce_two_decimals If true, allows up to two decimal places; otherwise, enforces integer input.
     * @return A valid numeric value within the specified range [min, max].
     */
    template <typename T>
    static T GetValidInput(const std::string &prompt, const T min, const T max, const bool enforce_two_decimals = false)
    {
        std::string input;
        T value;

        // Regex for integer-only input (e.g., IDs, ages)
        std::regex integer_regex(R"(^\d+$)");

        // Regex for input with up to two decimal places (e.g., currency, prices)
        std::regex decimal_regex(R"(^\d+(\.\d{1,2})?$)");

        while (true)
        {
            std::cout << prompt;
            std::getline(std::cin, input);

            bool valid = false;

            // Determine which regex to apply based on whether decimals are allowed
            if (enforce_two_decimals)
            {
                // Match against decimal pattern
                if (std::regex_match(input, decimal_regex))
                {
                    value = std::stod(input);
                    valid = (value >= min && value <= max);
                }
            }
            else
            {
                // Match against integer pattern
                if (std::regex_match(input, integer_regex))
                {
                    value = std::stoll(input);
                    valid = (value >= min && value <= max);
                }
            }

            // If the input is valid, return it
            if (valid)
                return value;

            // Otherwise, print an error and prompt again
            std::cerr << "Invalid input. Please enter a value between "
                      << std::fixed << std::setprecision(2) << min
                      << " and " << max;

            if (enforce_two_decimals)
                std::cerr << " (up to two decimal places)";

            std::cerr << ".\n";
        }
    }

    static std::string GetValidString(const std::string &prompt);
};

Bank::Bank *FindBank(const std::vector<std::unique_ptr<Bank::Bank>> &banks, i32 bank_id);
Bank::Customer *FindCustomer(const Bank::Bank *const bank, i32 customer_id);
Bank::BankAccount *FindAccount(const Bank::Customer *const customer, const std::string &account_id);

Bank::Bank *SelectBank(const std::vector<std::unique_ptr<Bank::Bank>> &banks);
Bank::Customer *SelectCustomer(const Bank::Bank *bank);
Bank::BankAccount *SelectAccount(const Bank::Customer *customer);

void WaitForUser();
void ClearScreen();

void DisplayMenu(i32 choice, bool is_running, std::vector<std::unique_ptr<Bank::Bank>> &banks);
void HandleUserChoice(i32 choice, bool is_running, std::vector<std::unique_ptr<Bank::Bank>> &banks);

void CreateBank(std::vector<std::unique_ptr<Bank::Bank>> &banks);
void CreateCustomer(std::vector<std::unique_ptr<Bank::Bank>> &banks);
void ViewAllBanks(const std::vector<std::unique_ptr<Bank::Bank>> &banks);
void ViewAllCustomer(const std::vector<std::unique_ptr<Bank::Bank>> &banks);
void SearchForBank(const std::vector<std::unique_ptr<Bank::Bank>> &banks);
void SearchForCustomer(std::vector<std::unique_ptr<Bank::Bank>> &banks);

void AddAccount(std::vector<std::unique_ptr<Bank::Bank>> &banks);
void AddTransaction(std::vector<std::unique_ptr<Bank::Bank>> &banks);
void ViewAllAccounts(std::vector<std::unique_ptr<Bank::Bank>> &banks);
void ViewAllTransactions(std::vector<std::unique_ptr<Bank::Bank>> &banks);
void SearchForAccount(std::vector<std::unique_ptr<Bank::Bank>> &banks);
void SearchForTransaction(std::vector<std::unique_ptr<Bank::Bank>> &banks);

void ApplyInterest(const std::vector<std::unique_ptr<Bank::Bank>> &banks);

void WriteToFile(const std::vector<std::unique_ptr<Bank::Bank>> &banks);