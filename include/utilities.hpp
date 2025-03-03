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

i32 GetValidInt(const std::string &prompt, i32 min, i32 max);
f64 GetValidFloat(const std::string &prompt, f64 min);
std::string GetValidString(const std::string &prompt);

std::unique_ptr<Bank::Bank> &SelectBank(std::vector<std::unique_ptr<Bank::Bank>> &banks);
const std::unique_ptr<Bank::Customer> &SelectCustomer(std::unique_ptr<Bank::Bank> &bank);
const std::unique_ptr<Bank::BankAccount> &SelectAccount(const std::unique_ptr<Bank::Customer> &customer);

void CreateBank(std::vector<std::unique_ptr<Bank::Bank>> &banks);
void CreateCustomer(std::vector<std::unique_ptr<Bank::Bank>> &banks);
void ViewAllBanks(std::vector<std::unique_ptr<Bank::Bank>> &banks);
void ViewAllCustomer(std::vector<std::unique_ptr<Bank::Bank>> &banks);
void SearchForBank(const std::vector<std::unique_ptr<Bank::Bank>> &banks);
void SearchForCustomer(std::vector<std::unique_ptr<Bank::Bank>> &banks);

void AddAccount(std::vector<std::unique_ptr<Bank::Bank>> &banks);
void AddTransaction(std::vector<std::unique_ptr<Bank::Bank>> &banks);
void ViewAllAccounts(std::vector<std::unique_ptr<Bank::Bank>> &banks);
void ViewAllTransactions(std::vector<std::unique_ptr<Bank::Bank>> &banks);
void SearchForAccount(std::vector<std::unique_ptr<Bank::Bank>> &banks);
void SearchForTransaction(std::vector<std::unique_ptr<Bank::Bank>> &banks);

void DisplayMenu(i32 &choice, bool &is_running, std::vector<std::unique_ptr<Bank::Bank>> &banks);

void WaitForUser();
void ClearScreen();