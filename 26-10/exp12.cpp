
#include <iostream>
#include <string>
using namespace std;

class Account {
protected:
    int accountNumber;
    string name;
    double balance;

public:
    Account(int accNo, string n, double b) {
        accountNumber = accNo;
        name = n;
        balance = b;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Amount deposited successfully.\n";
        } else {
            cout << "Invalid amount!\n";
        }
    }

    virtual void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful.\n";
        } else {
            cout << "Insufficient balance or invalid amount!\n";
        }
    }

    virtual void statement() {
        cout << "\nAccount Number: " << accountNumber;
        cout << "\nAccount Holder: " << name;
        cout << "\nBalance: Rs. " << balance << endl;
    }

    virtual ~Account() {}
};

class SavingsAccount : public Account {
public:
    SavingsAccount(int accNo, string n, double b)
        : Account(accNo, n, b) {}

    void statement() override {
        cout << "\n--- Savings Account Statement ---\n";
        Account::statement();
    }
};

class CheckingAccount : public Account {
public:
    CheckingAccount(int accNo, string n, double b)
        : Account(accNo, n, b) {}

    void statement() override {
        cout << "\n--- Checking Account Statement ---\n";
        Account::statement();
    }
};

int main() {
    int choice, type, accNo;
    string name;
    double balance, amount;

    cout << "Select Account Type:\n";
    cout << "1. Savings Account\n";
    cout << "2. Checking Account\n";
    cout << "Enter choice: ";
    cin >> type;

    cout << "Enter Account Number: ";
    cin >> accNo;

    cout << "Enter Account Holder Name: ";
    cin >> ws;
    getline(cin, name);

    cout << "Enter Initial Balance: ";
    cin >> balance;

    if (balance < 0) {
        cout << "Invalid initial balance!\n";
        return 0;
    }

    SavingsAccount savings(accNo, name, balance);
    CheckingAccount checking(accNo, name, balance);

    Account* account;

    if (type == 1)
        account = &savings;
    else if (type == 2)
        account = &checking;
    else {
        cout << "Invalid account type!\n";
        return 0;
    }

    do {
        cout << "\n--- Banking Menu ---\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Account Statement\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter deposit amount: ";
            cin >> amount;
            account->deposit(amount);
            break;

        case 2:
            cout << "Enter withdrawal amount: ";
            cin >> amount;
            account->withdraw(amount);
            break;

        case 3:
            account->statement();
            break;

        case 4:
            cout << "Thank you for using the banking system!\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}
