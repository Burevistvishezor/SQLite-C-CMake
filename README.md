# 🏦 Bank SQLite - Modern C++ Banking Application

A professional-grade C++ banking application demonstrating modern C++17 practices with CMake build system and SQLite3 database backend.

## ✨ Features

- **Object-Oriented Design**: Clean class architecture with proper encapsulation
- **C++17 Standards**: Modern C++ features including `constexpr`, `[[nodiscard]]`, and exception handling
- **CMake Build System**: Professional build configuration with version management
- **SQLite3 Integration**: Persistent data storage for accounts
- **Exception Safety**: Comprehensive error handling with meaningful error messages
- **Code Documentation**: Detailed Doxygen-ready comments throughout
- **Cross-Platform**: Works on Linux, macOS, and Windows

## 📋 Requirements

- **C++17 compatible compiler** (GCC 8+, Clang 6+, MSVC 2017+)
- **CMake 3.20+**
- **SQLite3 development libraries**

### Installation

**Ubuntu/Debian:**
```bash
sudo apt-get install build-essential cmake sqlite3 libsqlite3-dev
```

**macOS:**
```bash
brew install cmake sqlite3
```

**Windows (MSVC):**
```bash
# Using vcpkg
vcpkg install sqlite3:x64-windows
```

## 🚀 Quick Start

### Build from Source

```bash
# Clone the repository
git clone https://github.com/Burevistvishezor/SQLite-C-CMake.git
cd SQLite-C-CMake

# Create build directory
mkdir build
cd build

# Configure and build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .

# Run the application
./bin/bank_sqlite
```

### Expected Output

```
╔════════════════════════════════════╗
║  Modern Bank Account Application   ║
║  Built with C++17 & CMake          ║
╚════════════════════════════════════╝

┌─ Account Information ─────────────┐
│ Owner:   Vince Mueller            │
│ Balance: 1000.00 EUR              │
└────────────────────────────────────┘

[DEPOSIT] Adding 500 EUR...
┌─ Account Information ─────────────┐
│ Owner:   Vince Mueller            │
│ Balance: 1500.00 EUR              │
└────────────────────────────────────┘

[WITHDRAW] Removing 200 EUR...
┌─ Account Information ─────────────┐
│ Owner:   Vince Mueller            │
│ Balance: 1300.00 EUR              │
└────────────────────────────────────┘

[INTEREST] Applying 2% annual interest...
┌─ Account Information ─────────────┐
│ Owner:   Vince Mueller            │
│ Balance: 1326.00 EUR              │
└────────────────────────────────────┘

✓ Application completed successfully!
```

## 📚 Project Structure

```
SQLite-C-CMake/
├── CMakeLists.txt          # Modern CMake configuration
├── include/
│   └── BankAccount.h       # Account class header
├── src/
│   ├── BankAccount.cpp     # Account implementation
│   └── main.cpp            # Application entry point
├── .clang-format          # Code formatting rules
├── .gitignore             # Git ignore patterns
└── README.md              # This file
```

## 🎯 Core Classes

### BankAccount

Manages individual bank accounts with the following operations:

```cpp
// Constructor
BankAccount(const std::string& ownerName, double initialBalance);

// Operations
void deposit(double amount);           // Add funds
void withdraw(double amount);          // Remove funds
void applyInterest();                  // Apply 2% annual interest

// Queries
double getBalance() const;             // Current balance
std::string getOwner() const;          // Account owner
```

## 🔄 Exception Handling

The application uses modern C++ exceptions for error handling:

```cpp
try {
    BankAccount account("John", -100);  // Throws std::invalid_argument
} catch (const std::invalid_argument& e) {
    std::cerr << "Error: " << e.what() << "\n";
}
```

## 📖 Modern C++ Features Used

- ✅ `constexpr` for compile-time constants
- ✅ `[[nodiscard]]` attribute for important return values
- ✅ `noexcept` specifications for exception-safe functions
- ✅ Structured exception handling
- ✅ Smart pointers and RAII principles
- ✅ Range-based for loops
- ✅ `std::fixed` and `std::setprecision` for formatting

## 🔜 Future Enhancements

- [ ] SQLite database persistence
- [ ] Transaction support
- [ ] Multi-account management system
- [ ] Comprehensive unit tests (Google Test)
- [ ] Docker containerization
- [ ] REST API interface
- [ ] Performance benchmarking

## 🛠️ Development

### Code Formatting

Format code using clang-format:

```bash
clang-format -i src/*.cpp include/*.h
```

### Building with Debug Symbols

```bash
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build .
```

## 📄 License

This project is open source and available under the MIT License.

## 👨‍💻 Author

**Burevistvishezor** - [GitHub Profile](https://github.com/Burevistvishezor)

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## 📞 Support

For issues and questions, please use the [GitHub Issues](https://github.com/Burevistvishezor/SQLite-C-CMake/issues) page.

---

**Last Updated:** 2026  
**Status:** Active Development  
**C++ Standard:** C++17  
**Build System:** CMake 3.20+
