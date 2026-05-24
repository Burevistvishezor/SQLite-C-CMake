#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <string>
#include <stdexcept>

/**
 * @class BankAccount
 * @brief Represents a single bank account with basic operations
 * 
 * Provides functionality for deposits, withdrawals, balance queries,
 * and interest calculations.
 */
class BankAccount {
private:
    std::string owner;
    double balance;
    static constexpr double DEFAULT_INTEREST_RATE = 0.02; // 2% annual interest

public:
    /**
     * @brief Constructs a BankAccount with owner name and initial balance
     * @param ownerName The account owner's name
     * @param initialBalance The initial account balance
     * @throws std::invalid_argument if initialBalance is negative
     */
    explicit BankAccount(const std::string& ownerName, double initialBalance);

    /**
     * @brief Deposits money into the account
     * @param amount The amount to deposit
     * @throws std::invalid_argument if amount is non-positive
     */
    void deposit(double amount);

    /**
     * @brief Withdraws money from the account
     * @param amount The amount to withdraw
     * @throws std::invalid_argument if amount is non-positive or exceeds balance
     */
    void withdraw(double amount);

    /**
     * @brief Applies interest to the account
     */
    void applyInterest() noexcept;

    /**
     * @brief Gets the current balance
     * @return The current account balance
     */
    [[nodiscard]] double getBalance() const noexcept;

    /**
     * @brief Gets the owner's name
     * @return The account owner's name
     */
    [[nodiscard]] std::string getOwner() const noexcept;
};

#endif // BANK_ACCOUNT_H
