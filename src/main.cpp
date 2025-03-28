#define SPDLOG_WCHAR_TO_UTF8_SUPPORT

#include "fmt/core.h"
#include "fmt/xchar.h"
#include "spdlog/spdlog.h"
#include "sqlite3/sqlite3.h"
#include <boost/locale.hpp>
#include <fcntl.h>
#include <filesystem>
#include <io.h>
#include <iostream>
#include <spdlog/sinks/basic_file_sink.h>
#include <string>

// SQLite3 callback function for query results
static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    // Print each column name and value
    for (int i = 0; i < argc; i++)
    {
        std::wcout << boost::locale::conv::to_utf<wchar_t>(azColName[i], "UTF-8") << L" = " << boost::locale::conv::to_utf<wchar_t>(argv[i] ? argv[i] : "NULL", "UTF-8") << std::endl;
    }
    std::wcout << std::endl;
    return 0;
}

int main()
{
    // Set Windows console to use UTF-16 (required for wcout)
    _setmode(_fileno(stdout), _O_U16TEXT);

    // Initialize logger
    auto logger = spdlog::basic_logger_mt("file_logger", "log.txt");
    spdlog::set_default_logger(logger);
    spdlog::info("Application started");

    // String conversion example (UTF-8 to UTF-16)
    std::string utf8_str = "你好，世界！"; // UTF-8 string
    std::wstring wide_str = boost::locale::conv::to_utf<wchar_t>(utf8_str, "UTF-8");
    std::wcout << L"Converted wstring: " << wide_str << std::endl;

    // Display current working directory
    std::wcout << L"Current path: " << std::filesystem::current_path().wstring() << std::endl;

    // Formatted output using fmt
    std::wcout << fmt::format(L"Hello, {}!", L"world") << std::endl;

    // SQLite3 database operations
    sqlite3 *db;       // Database handle
    char *zErrMsg = 0; // Error message buffer
    int rc;            // Return code

    /* Open database (creates if doesn't exist) */
    rc = sqlite3_open("test.db", &db);
    if (rc)
    {
        std::wstring error = boost::locale::conv::to_utf<wchar_t>(sqlite3_errmsg(db), "UTF-8");
        std::wcerr << L"Can't open database: " << error << std::endl;
        spdlog::error("Can't open database: {}", sqlite3_errmsg(db));
        return 1;
    }
    else
    {
        std::wcout << L"Opened database successfully" << std::endl;
        spdlog::info("Opened database successfully");
    }

    /* Create SQL statement for table creation */
    const char *sql = "CREATE TABLE IF NOT EXISTS COMPANY("
                      "ID INT PRIMARY KEY     NOT NULL,"
                      "NAME           TEXT    NOT NULL,"
                      "AGE            INT     NOT NULL,"
                      "ADDRESS        CHAR(50),"
                      "SALARY         REAL );";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        std::wstring error = boost::locale::conv::to_utf<wchar_t>(zErrMsg, "UTF-8");
        std::wcerr << L"SQL error: " << error << std::endl;
        spdlog::error("SQL error: {}", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
    {
        std::wcout << L"Table created successfully" << std::endl;
        spdlog::info("Table created successfully");
    }

    /* Create SQL statement for data insertion */
    sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "
          "VALUES (1, 'Paul', 32, 'California', 20000.00 ); "
          "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "
          "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "
          "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)"
          "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );"
          "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)"
          "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        std::wstring error = boost::locale::conv::to_utf<wchar_t>(zErrMsg, "UTF-8");
        std::wcerr << L"SQL error: " << error << std::endl;
        spdlog::error("SQL error: {}", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
    {
        std::wcout << L"Records created successfully" << std::endl;
        spdlog::info("Records created successfully");
    }

    /* Query the database */
    std::wcout << L"\nQuery results:" << std::endl;
    sql = "SELECT * from COMPANY";
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        std::wstring error = boost::locale::conv::to_utf<wchar_t>(zErrMsg, "UTF-8");
        std::wcerr << L"SQL error: " << error << std::endl;
        spdlog::error("SQL error: {}", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    /* Close database connection */
    sqlite3_close(db);
    spdlog::info("Database connection closed");
    std::wcout << L"Database connection closed" << std::endl;

    return 0;
}