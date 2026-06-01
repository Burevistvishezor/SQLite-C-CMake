mkdir -p SQLite-C-CMake/include
mkdir -p SQLite-C-CMake/src
mkdir -p SQLite-C-CMake/tests
cd /путь/к/вашему/проекту  # перейдите в папку проекта
mkdir include
mkdir src
mkdir tests   # если не нужен, пропустите
#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>

class Database {
public:
    explicit Database(const std::string& db_name);
    ~Database();

    bool open();
    void close();
    bool execute(const std::string& sql);

private:
    std::string db_name_;
    sqlite3* db_;
};

#endif // DATABASE_H
