cmake_minimum_required(VERSION 3.20)
project(BankSQLite 
    VERSION 1.0.0
    DESCRIPTION "Modern C++ banking application with SQLite3 backend"
    LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Compiler flags
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
    add_compile_options(-fPIC)
endif()

# Find dependencies
find_package(SQLite3 REQUIRED)

# Main executable
add_executable(bank_sqlite
    src_fixed/main.cpp
    src_fixed/BankAccount.cpp
)

target_include_directories(bank_sqlite
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(bank_sqlite
    PRIVATE
    SQLite::SQLite3
)

# Enable testing
enable_testing()

# Optional: Add test executable if tests exist
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests")
    add_subdirectory(tests)
endif()

# Print configuration info
message(STATUS "BankSQLite ${PROJECT_VERSION}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
