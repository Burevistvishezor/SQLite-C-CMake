#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <optional>

struct sqlite3; // forward declaration

class Database {
public:
    explicit Database(const std::string& dbPath) noexcept;
    ~Database();

    // Open (or create) the database file
    bool open();

    // Create schema (accounts table)
    bool init();

    // Save account balance (INSERT OR REPLACE)
    bool saveAccount(const std::string& owner, double balance);

    // Load account balance by owner. Returns std::nullopt if not found / on error
    std::optional<double> loadBalance(const std::string& owner);

    // Close explicitly (optional)
    void close() noexcept;

private:
    std::string dbPath_;
    sqlite3* db_ = nullptr;
};

#endif // DATABASE_H
