#include <iostream>
#include <iomanip>
#include "BankAccount.h"

void printAccountInfo(const BankAccount& account) {
    std::cout << "┌─ Account Information ─────────────┐\n";
    std::cout << "│ Owner:   " << std::left << std::setw(24) << account.getOwner() << "│\n";
    std::cout << "│ Balance: " << std::fixed << std::setprecision(2) << std::right 
              << std::setw(19) << account.getBalance() << " EUR              │\n";
    std::cout << "└────────────────────────────────────┘\n";
}

int main() {
    try {
        std::cout << "╔════════════════════════════════════╗\n";
        std::cout << "║  Modern Bank Account Application   ║\n";
        std::cout << "║  Built with C++17 & CMake          ║\n";
        std::cout << "╚════════════════════════════════════╝\n\n";

        BankAccount account("Vince Mueller", 1000.00);
        
        std::cout << "Initial Account:\n";
        printAccountInfo(account);
        std::cout << "\n";

        std::cout << "[DEPOSIT] Adding 500 EUR...\n";
        account.deposit(500.00);
        printAccountInfo(account);
        std::cout << "\n";

        std::cout << "[WITHDRAW] Removing 200 EUR...\n";
        account.withdraw(200.00);
        printAccountInfo(account);
        std::cout << "\n";

        std::cout << "[INTEREST] Applying 2% annual interest...\n";
        account.applyInterest();
        printAccountInfo(account);
        std::cout << "\n";

        std::cout << "✓ Application completed successfully!\n";
        return 0;

    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << "\n";
        return 1;
    }
}
mkdir -p SQLite-C-CMake/include
mkdir -p SQLite-C-CMake/src
mkdir -p SQLite-C-CMake/tests
