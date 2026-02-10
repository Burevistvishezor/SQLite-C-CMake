#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>

class BankAccount {
private:
    std::string owner;
    double balance;
    double interestRate = 0.02; // 2% annual interest

public:
    BankAccount(const std::string& ownerName, double initialBalance);
    void deposit(double amount);
    void withdraw(double amount);
    void applyInterest();
    double getBalance() const;
    std::string getOwner() const;
};

#endif // BANKACCOUNT_H
