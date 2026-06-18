cmake_minimum_required(VERSION 3.20)
project(BankSQLite
    VERSION 1.0.0
    DESCRIPTION "Modern C++ banking application with SQLite3 backend"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Compiler warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
    add_compile_options(-fPIC)
endif()

option(USE_SYSTEM_SQLITE "Use system-installed SQLite3 (find_package)" ON)

if(USE_SYSTEM_SQLITE)
    find_package(SQLite3 REQUIRED)
else()
    include(FetchContent)
    FetchContent_Declare(
      sqlite3
      GIT_REPOSITORY https://github.com/sqlite/sqlite.git
      GIT_TAG v3.42.0
    )
    FetchContent_MakeAvailable(sqlite3)
endif()

# Sources
set(SRC
    main.cpp
    BankAccount.cpp
    src_fixed/database.cpp
)

add_executable(bank_sqlite ${SRC})

target_include_directories(bank_sqlite
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link SQLite (system or vendored)
if(USE_SYSTEM_SQLITE)
    # Prefer modern imported target if available
    if(TARGET SQLite::SQLite3)
        target_link_libraries(bank_sqlite PRIVATE SQLite::SQLite3)
    else()
        target_link_libraries(bank_sqlite PRIVATE sqlite3)
    endif()
else()
    target_sources(bank_sqlite PRIVATE ${sqlite3_SOURCE_DIR}/sqlite3.c)
    target_include_directories(bank_sqlite PRIVATE ${sqlite3_SOURCE_DIR})
endif()

# Installation
include(GNUInstallDirs)
install(TARGETS bank_sqlite
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/BankAccount.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/database.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Tests
enable_testing()
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.13.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(test_database
    tests/test_database.cpp
    src_fixed/database.cpp
    BankAccount.cpp
)
target_include_directories(test_database PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
if(TARGET SQLite::SQLite3)
    target_link_libraries(test_database PRIVATE SQLite::SQLite3 gtest_main)
else()
    target_link_libraries(test_database PRIVATE sqlite3 gtest_main)
endif()
add_test(NAME DatabaseTest COMMAND test_database)
