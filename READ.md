# Bank Management System

A simple C++ console-based Bank Management System featuring the following functionality:

1. **Banks** – Create and manage Bank objects, each with a unique ID and set of customers.  
2. **Customers** – Add and manage Customer objects (name, ID, age).  
3. **Accounts** – Create Checking or Saving accounts for each customer.  
4. **Transactions** – Perform deposits, withdrawals, and transfers.  
5. **Interest** – Apply interest (for Saving accounts).  
6. **File Output** – Write all bank/customer/account/transaction data to a file.

---

## Project Structure

- **include/** holds the header files for each class (`Bank`, `Customer`, `BankAccount`, etc.).
- **src/** holds the `.cpp` files implementing these classes and the main entry point (`main.cpp`).
- **Makefile** compiles and links everything into an executable.
- **bank_info.txt** (generated at runtime) contains a summary of all banks, customers, accounts, and transactions.

---

## Features

- **Add Bank** – Creates a new Bank with a user-provided name, assigned a random ID.  
- **Add Customer** – Associates a new Customer with an existing Bank.  
- **Add Account** – Creates a Checking or Saving account for a chosen Customer.  
- **Add Transaction** – Performs a `Deposit`, `Withdraw`, or `Transfer` on a chosen Account.  
- **View All ...** – View all banks, customers in a bank, accounts of a customer, or transactions of an account.  
- **Search** – Look up banks, customers, accounts, or transactions by ID.  
- **Apply Interest** – Applies a global interest rate to all `SavingAccount's`.  
- **Write To File** – Outputs all data to `bank_info.txt` in a hierarchical format.

---

## Building

1. **Ensure you have a C++20 compiler** (e.g., g++ 11 or later).  
2. Navigate to the project root directory.  
3. Run `make all` to compile:

    ```bash
    make all
    ```
    
    This should create the executable (e.g. `main.exe` on Windows or `./main` on Mac/Linux).

4. Optionally, run `make clean` to remove object files and the executable.

---

## Running the Application

1. **Build** the project as described above.  
2. **Run** the resulting executable:

    ```bash
    # On Linux / macOS:
    ./main

    # On Windows:
    main.exe
    ```

3. You will see a **menu** of numbered options. Enter the number of the action you want to perform (e.g., “1” for Add Bank, “2” for Add Customer, etc.).  

4. **Regularly “Write To File”** (option 14) so you can easily look up the assigned IDs. You must enter those IDs to add or view items in future steps.

5. **Exit** the application by selecting option 15.

---

## Usage Example

1. **Add Bank**  
   - Provide a bank name, e.g. “MyBank.” The system will display the new bank’s ID (or you can later see it in `bank_info.txt`).

2. **Add Customer**  
   - Enter the **bank ID** you just created. Supply the customer’s first/last name and age. The system will generate a **customer ID**.

3. **Write To File**  
   - After adding the customer, select “Write To File” to record the new IDs in `bank_info.txt`. This file shows you the bank’s ID, the customer’s ID, etc.

4. **Add Account**  
   - Enter the **same bank ID** again, and then the **customer ID** from step 3.  
   - Choose Checking or Saving, and specify the initial balance. An **account ID** is automatically assigned.

5. **Write To File** again if you like, so you can see the new account’s ID and reference it later.

6. **Add Transaction**  
   - Enter the bank ID, the customer ID, and the account ID.  
   - Choose a transaction type (DEPOSIT, WITHDRAW, TRANSFER) and enter the amount.  
   - If successful, the system will show you the updated balance or apply fees (CheckingAccount only).

7. **View All Accounts** or **View All Transactions** to verify changes. Or **Write To File** once more to record everything.

8. **Exit**  
   - Once done, use the “Exit” option (menu item 15).

---

## License

This project is provided as-is, without warranty or guarantee. You are free to modify or extend it for your needs.

**Enjoy using the Bank Management System!**

