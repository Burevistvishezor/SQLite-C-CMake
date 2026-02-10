#include <iostream>
#include <sqlite3.h>

void execute(sqlite3* db, const std::string& sql)
{
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

int callback(void*, int argc, char** argv, char** colName)
{
    for (int i = 0; i < argc; i++)
        std::cout << colName[i] << ": " << (argv[i] ? argv[i] : "NULL") << " | ";
    std::cout << std::endl;
    return 0;
}

int main()
{
    sqlite3* db;
    sqlite3_open("bank.db", &db);

    execute(db,
        "CREATE TABLE IF NOT EXISTS accounts ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "owner TEXT,"
        "balance REAL);");

    execute(db,
        "INSERT INTO accounts (owner, balance) VALUES "
        "('Alice', 1200.50),"
        "('Bob', 800.00);");

    std::cout << "Accounts in database:\n";
    sqlite3_exec(db, "SELECT * FROM accounts;", callback, nullptr, nullptr);

    sqlite3_close(db);
    return 0;
}

