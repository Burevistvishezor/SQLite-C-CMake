# Create a new test fixture and two tests for the database wrapper
#include <gtest/gtest.h>
#include "database.h"
#include "BankAccount.h"
#include <filesystem>

class DatabaseFixture : public ::testing::Test {
protected:
    std::string dbfile = "test_db.sqlite";
    Database* db = nullptr;

    void SetUp() override {
        if (std::filesystem::exists(dbfile)) std::filesystem::remove(dbfile);
        db = new Database(dbfile);
        ASSERT_TRUE(db->open());
        ASSERT_TRUE(db->init());
    }

    void TearDown() override {
        delete db;
        db = nullptr;
        if (std::filesystem::exists(dbfile)) std::filesystem::remove(dbfile);
    }
};

TEST_F(DatabaseFixture, SaveAndLoadBalance) {
    BankAccount acct("UnitTester", 123.45);
    EXPECT_TRUE(db->saveAccount(acct.getOwner(), acct.getBalance()));

    auto loaded = db->loadBalance(acct.getOwner());
    ASSERT_TRUE(loaded.has_value());
    EXPECT_DOUBLE_EQ(loaded.value(), acct.getBalance());
}

TEST_F(DatabaseFixture, SaveUpdateAndLoadBalance) {
    BankAccount acct("Updater", 50.0);
    EXPECT_TRUE(db->saveAccount(acct.getOwner(), acct.getBalance()));

    acct.deposit(25.0);
    EXPECT_TRUE(db->saveAccount(acct.getOwner(), acct.getBalance()));

    acct.deposit(25.0);
    EXPECT_TRUE(db->saveAccount(acct.getOwner(), acct.getBalance()));

    auto loaded = db->loadBalance(acct.getOwner());
    ASSERT_TRUE(loaded.has_value());
    EXPECT_DOUBLE_EQ(loaded.value(), acct.getBalance());
}
