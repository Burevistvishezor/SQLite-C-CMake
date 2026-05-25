#include "BankAccount.h"
#include <iomanip>
#include <iostream>

BankAccount::BankAccount(const std::string& ownerName, double initialBalance)
    : owner(ownerName), balance(initialBalance) {
    if (initialBalance < 0) {
        throw std::invalid_argument("Initial balance cannot be negative");
    }
}

void BankAccount::deposit(double amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Deposit amount must be positive");
    }
    balance += amount;
}

void BankAccount::withdraw(double amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Withdrawal amount must be positive");
    }
    if (amount > balance) {
        throw std::invalid_argument("Insufficient funds for withdrawal");
    }
    balance -= amount;
}

void BankAccount::applyInterest() noexcept {
    balance *= (1.0 + DEFAULT_INTEREST_RATE);
}

double BankAccount::getBalance() const noexcept {
    return balance;
}

std::string BankAccount::getOwner() const noexcept {
    return owner;
}
