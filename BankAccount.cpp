#include "BankAccount.h"
#include <iostream>

BankAccount::BankAccount(const std::string& ownerName, double initialBalance)
    : owner(ownerName), balance(initialBalance) {}

void BankAccount::deposit(double amount) {
    if (amount > 0) balance += amount;
}

void BankAccount::withdraw(double amount) {
    if (amount > 0 && amount <= balance) balance -= amount;
    else std::cout << "Insufficient funds\n";
}

void BankAccount::applyInterest() {
    balance += balance * interestRate;
}

double BankAccount::getBalance() const {
    return balance;
}

std::string BankAccount::getOwner() const {
    return owner;
}

