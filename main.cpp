#include "include/database.h"
#include "include/BankAccount.h"
#include <iostream>
#include <iomanip>

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

        const std::string dbfile = "bank.db";
        Database db(dbfile);
        if (!db.open()) {
            std::cerr << "Failed to open database: " << dbfile << "\n";
            return 1;
        }
        if (!db.init()) {
            std::cerr << "Failed to initialize database schema\n";
            return 1;
        }

        // Try to load an existing account; if not found, create default
        const std::string owner = "Vince Mueller";
        auto loaded = db.loadBalance(owner);
        BankAccount account(owner, loaded.value_or(1000.00));

        std::cout << "Initial Account:\n";
        printAccountInfo(account);
        std::cout << "\n";

        std::cout << "[DEPOSIT] Adding 500 EUR...\n";
        account.deposit(500.00);
        db.saveAccount(account.getOwner(), account.getBalance());
        printAccountInfo(account);
        std::cout << "\n";

        std::cout << "[WITHDRAW] Removing 200 EUR...\n";
        account.withdraw(200.00);
        db.saveAccount(account.getOwner(), account.getBalance());
        printAccountInfo(account);
        std::cout << "\n";

        std::cout << "[INTEREST] Applying 2% annual interest...\n";
        account.applyInterest();
        db.saveAccount(account.getOwner(), account.getBalance());
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
