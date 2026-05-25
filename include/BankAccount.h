#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <string>
#include <stdexcept>
#include <iomanip>
#include <sstream>

/**
 * @class BankAccount
 * @brief Represents a single bank account with deposit, withdrawal, and interest calculations
 * 
 * Provides functionality for deposits, withdrawals, balance queries, and interest operations.
 * Implements exception-based error handling for invalid operations.
 */
class BankAccount {
private:
    std::string owner;
    double balance;
    static constexpr double DEFAULT_INTEREST_RATE = 0.02; // 2% annual interest

public:
    /**
     * @brief Constructs a BankAccount with owner name and initial balance
     * @param ownerName The account owner's name (must not be empty)
     * @param initialBalance The initial account balance (must be non-negative)
     * @throws std::invalid_argument if ownerName is empty or initialBalance is negative
     */
    explicit BankAccount(const std::string& ownerName, double initialBalance);

    /**
     * @brief Deposits money into the account
     * @param amount The amount to deposit (must be positive)
     * @throws std::invalid_argument if amount is non-positive or NaN
     */
    void deposit(double amount);

    /**
     * @brief Withdraws money from the account
     * @param amount The amount to withdraw (must be positive and not exceed balance)
     * @throws std::invalid_argument if amount is non-positive, NaN, or exceeds balance
     * @throws std::runtime_error if withdrawal would result in insufficient funds
     */
    void withdraw(double amount);

    /**
     * @brief Applies compound interest to the account balance
     * Uses a fixed 2% annual interest rate
     */
    void applyInterest() noexcept;

    /**
     * @brief Gets the current account balance
     * @return The current account balance as a double
     */
    [[nodiscard]] double getBalance() const noexcept;

    /**
     * @brief Gets the account owner's name
     * @return The account owner's name
     */
    [[nodiscard]] std::string getOwner() const noexcept;

    /**
     * @brief Gets the interest rate as a formatted string
     * @return The interest rate formatted as a percentage string
     */
    [[nodiscard]] std::string getInterestRateStr() const noexcept;
};

#endif // BANK_ACCOUNT_H
