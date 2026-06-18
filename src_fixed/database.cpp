#include "database.h"
#include <sqlite3.h>
#include <iostream>

Database::Database(const std::string& dbPath) noexcept
    : dbPath_(dbPath), db_(nullptr) {}

Database::~Database() {
    if (db_) sqlite3_close(db_);
}

bool Database::open() {
    if (sqlite3_open(dbPath_.c_str(), &db_) != SQLITE_OK) {
        std::cerr << "Failed to open SQLite db: " << (db_ ? sqlite3_errmsg(db_) : "unknown") << "\n";
        if (db_) { sqlite3_close(db_); db_ = nullptr; }
        return false;
    }
    return true;
}

void Database::close() noexcept {
    if (db_) { sqlite3_close(db_); db_ = nullptr; }
}

bool Database::init() {
    const char* sql = "CREATE TABLE IF NOT EXISTS accounts("
                      "owner TEXT PRIMARY KEY,"
                      "balance REAL NOT NULL);";
    char* errmsg = nullptr;
    if (sqlite3_exec(db_, sql, nullptr, nullptr, &errmsg) != SQLITE_OK) {
        std::cerr << "Schema init failed: " << (errmsg ? errmsg : "unknown") << "\n";
        sqlite3_free(errmsg);
        return false;
    }
    return true;
}

bool Database::saveAccount(const std::string& owner, double balance) {
    const char* sql = "INSERT INTO accounts(owner, balance) VALUES(?, ?) "
                      "ON CONFLICT(owner) DO UPDATE SET balance=excluded.balance;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare save statement: " << sqlite3_errmsg(db_) << "\n";
        return false;
    }
    sqlite3_bind_text(stmt, 1, owner.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 2, balance);
    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Failed to execute save statement: " << sqlite3_errmsg(db_) << "\n";
        sqlite3_finalize(stmt);
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
}

std::optional<double> Database::loadBalance(const std::string& owner) {
    const char* sql = "SELECT balance FROM accounts WHERE owner = ? LIMIT 1;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare load statement: " << sqlite3_errmsg(db_) << "\n";
        return std::nullopt;
    }
    sqlite3_bind_text(stmt, 1, owner.c_str(), -1, SQLITE_TRANSIENT);
    int rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        double balance = sqlite3_column_double(stmt, 0);
        sqlite3_finalize(stmt);
        return balance;
    }
    sqlite3_finalize(stmt);
    return std::nullopt;
}
