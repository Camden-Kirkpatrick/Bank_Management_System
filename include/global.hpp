#pragma once
#include "types.hpp"

constexpr i32 MIN_BANK_ID = 1'000;
constexpr i32 MAX_BANK_ID = 9'999;

constexpr i32 MIN_CUSTOMER_ID = 10'000;
constexpr i32 MAX_CUSTOMER_ID = 99'999;

constexpr i32 MIN_ACCOUNT_ID = 100'000;
constexpr i32 MAX_ACCOUNT_ID = 999'999;

constexpr i32 MIN_TRANSACTION_ID = 1'000'000;
constexpr i32 MAX_TRANSACTION_ID = 9'999'999;

constexpr f64 MIN_STARTING_BALANCE = 50.00;
constexpr f64 MIN_BALANCE = 0.00;
constexpr f64 MAX_BALANCE = 1'000'000.00;

constexpr i32 MIN_AGE = 16;
constexpr i32 MAX_AGE = 120;

constexpr i32 MIN_MENU_CHOICE = 1;
constexpr i32 MAX_MENU_CHOICE = 15;

constexpr i32 MIN_ACCOUNT_TYPE = 0;
constexpr i32 MAX_ACCOUNT_TYPE = 1;

constexpr i32 MIN_TRANSACTION_TYPE = 0;
constexpr i32 MAX_TRANSACTION_TYPE = 2;

constexpr f64 MIN_TRANSACTION_AMOUNT = 1.00;
constexpr f64 MAX_TRANSACTION_AMOUNT = 10'000.00;

constexpr f64 INTEREST_RATE = 0.05;

constexpr f64 OVERDRAFT_FEE = 35.00;
constexpr f64 OVERDRAFT_LIMIT = 100.00;
