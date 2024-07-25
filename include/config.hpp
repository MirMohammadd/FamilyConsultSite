#ifndef __CONFIG_HPP
#define __CONFIG_HPP

#include <iostream>
#include <sqlite3.h>
#include "xdevapi.h"
#include <string>

#define CONNECTED_MESSAGE "Connected successfully to the DBMS!"
#define CONNECT_TO_AND_GET(host, port, user, pass, dbs) \
    try { \
        mysqlx::Session sess(host, port, user, pass); \
        sess.sql("USE `" + dbs + "`").execute(); \
        std::cout << "Connected to the database '" << dbs << "' successfully!" << std::endl; \
        mysqlx::Schema db = sess.getSchema(dbs); \
        std::cout << "Tables in the database:" << std::endl; \
        for (const auto& tableName : db.getTableNames()) { \
            std::string tableNameStr = tableName; \
            std::string query = "DESCRIBE `" + tableNameStr + "`"; \
            mysqlx::SqlStatement stmt = sess.sql(query); \
            mysqlx::RowResult result = stmt.execute(); \
            std::cout << "Columns in " << tableNameStr << ":" << std::endl; \
            for (const auto& row : result) { \
                std::string columnName = row[0].get<std::string>(); \
                std::string columnType = row[1].get<std::string>(); \
                std::string isNull = row[2].get<std::string>(); \
                std::string key = row[3].get<std::string>(); \
                std::string defaultValue; \
                std::string extra; \
                try { \
                    defaultValue = row[4].get<std::string>(); \
                } catch (...) { \
                    defaultValue = "N/A"; \
                } \
                try { \
                    extra = row[5].get<std::string>(); \
                } catch (...) { \
                    extra = "N/A"; \
                } \
                std::cout << "Column: " << columnName \
                          << ", Type: " << columnType \
                          << ", Null: " << isNull \
                          << ", Key: " << key \
                          << ", Default: " << defaultValue \
                          << ", Extra: " << extra << std::endl; \
            } \
        } \
        sess.close(); \
    } catch (const mysqlx::Error &err) { \
        std::cerr << "MySQL Error: " << err.what() << std::endl; \
    } catch (std::exception &ex) { \
        std::cerr << "Standard Exception: " << ex.what() << std::endl; \
    } catch (...) { \
        std::cerr << "Unexpected error!" << std::endl; \
    }



#endif