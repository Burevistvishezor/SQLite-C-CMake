cmake_minimum_required(VERSION 3.16)
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
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
    add_compile_options(-fPIC)
endif()

# Find SQLite3
find_package(SQLite3 REQUIRED)

# Source files from root directory
add_executable(bank_sqlite
    main.cpp
    BankAccount.cpp
)

# Include directories
target_include_directories(bank_sqlite
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link SQLite3
target_link_libraries(bank_sqlite
    PRIVATE
    SQLite::SQLite3
)

# Print configuration info
message(STATUS "===== BankSQLite Configuration =====")
message(STATUS "Project Version: ${PROJECT_VERSION}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "SQLite3 Version: ${SQLite3_VERSION}")
message(STATUS "=====================================")
cmake_minimum_required(VERSION 3.14)

project(SQLiteExample LANGUAGES CXX)

# Включение поддержки C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пути
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

# Создание исполняемого файла
add_executable(SQLiteApp
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/database.cpp
)

# Включение заголовков
target_include_directories(SQLiteApp PRIVATE ${INCLUDE_DIR})

# Подключение SQLite
include(FetchContent)

FetchContent_Declare(
  sqlite3
  GIT_REPOSITORY https://github.com/sqlite/sqlite.git
  GIT_TAG v3.42.0
)

FetchContent_MakeAvailable(sqlite3)

# Добавление исходников sqlite3
target_sources(SQLiteApp PRIVATE ${sqlite3_SOURCE_DIR}/sqlite3.c)
target_include_directories(SQLiteApp PRIVATE ${sqlite3_SOURCE_DIR})

# Опционально: тесты
enable_testing()

# Можно добавить тесты позже

