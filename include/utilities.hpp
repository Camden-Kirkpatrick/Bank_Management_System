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