#include <iostream>
#include "BankAccount.h"

int main() {
    BankAccount account("Vince", 1000.0);

    std::cout << "Initial balance: " << account.getBalance() << " EUR\n";

    account.deposit(500.0);
    std::cout << "After deposit of 500 EUR: " << account.getBalance() << " EUR\n";

    account.withdraw(200.0);
    std::cout << "After withdrawal of 200 EUR: " << account.getBalance() << " EUR\n";

    account.applyInterest();
    std::cout << "After applying interest: " << account.getBalance() << " EUR\n";

    return 0;
}

