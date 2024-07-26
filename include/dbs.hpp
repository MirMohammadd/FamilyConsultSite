#ifndef __DBS_HPP
#define __DBS_HPP

#include <sqlite3.h>
#include <iostream>
#include <vector>
#include "exceptions.hpp"
#include "config.hpp"

class Database{

    public:
        int dbs;
        int rc;
        sqlite3* db;
        char * errMsg = 0;
        std::string dbsPath  = PATH;
        std::vector<std::string> columnsByUser;

    private:
        void getDbsInfo(){
            return;
        }
    
    public:
        void connect(){
            getDbsInfo();
            rc = sqlite3_open(dbsPath.c_str(), &db);

            if (rc){
            std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
            throw DBSOpeningExc();
            }
            else{
                std::cout<<"Could open database successfully"<<std::endl;
            }
        }

        int chooseOptions(){
        int result;
        std::cout << "Choose option: " << std::endl;
        std::cout << "1. Create table" << std::endl;
        std::cout << "2. Insert data" << std::endl;
        std::cout << "3. Select data" << std::endl;
        std::cout << "4. Update data" << std::endl;
        std::cout << "5. Delete data" << std::endl;
        std::cout << "6. Exit" << std::endl;
        
        std::cin >> result;

        switch(result){
            case 1:
                return 1;
            case 2:
                return 2;
            case 3:
                return 3;
            case 4:
                return 4;
            case 5:
                return 5;
            case 6:
                return 6;
            default:
                return -1;
        }


        }

    void createTable(const std::string& table, int colNumbers, bool autoFill) {
        connect(); // Ensure this method connects to the SQLite database and sets `db`

        if (!autoFill) {
            std::vector<std::string> columnsByUser; // Vector to store column definitions

            // Collect column names and types
            for (int i = 0; i < colNumbers; i++) {
                std::string colName;
                std::cout << "Enter column name: ";
                std::cin >> colName;

                std::string colType;
                std::cout << "Enter column type: ";
                std::cin >> colType;

                // Add column definition to the vector
                columnsByUser.push_back(colName + " " + colType);
            }

            // Build the SQL command
            std::string sqlStatement = "CREATE TABLE IF NOT EXISTS " + table + " (";
            for (size_t i = 0; i < columnsByUser.size(); ++i) {
                sqlStatement += columnsByUser[i];
                if (i < columnsByUser.size() - 1) {
                    sqlStatement += ", ";
                }
            }
            sqlStatement += ");";

            // Confirm before executing
            std::cout << "Executing: " << sqlStatement << "\nDo you confirm? Enter 1 to confirm: ";
            int confirm;
            std::cin >> confirm;
            if (confirm == 1) {
                char* errMsg = nullptr;
                int rc = sqlite3_exec(db, sqlStatement.c_str(), 0, 0, &errMsg);
                if (rc != SQLITE_OK) {
                    std::cerr << "SQL error: " << errMsg << std::endl;
                    sqlite3_free(errMsg);
                } else {
                    std::cout << "Table created successfully." << std::endl;
                }
            } else {
                std::cout << "Table creation cancelled." << std::endl;
            }
        } else {
            // AutoFill case
            std::string sqlCreateTable = "CREATE TABLE IF NOT EXISTS " + table + " (id INTEGER PRIMARY KEY, name TEXT);";
            char* errMsg = nullptr;
            int rc = sqlite3_exec(db, sqlCreateTable.c_str(), 0, 0, &errMsg);
            if (rc != SQLITE_OK) {
                std::cerr << "SQL error: " << errMsg << std::endl;
                sqlite3_free(errMsg);
            } else {
                std::cout << "Table created successfully." << std::endl;
            }
        }
    }

    private:
            static int callback(void *data, int argc, char **argv, char **azColName) {
        for (int i = 0; i < argc; i++) {
            std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << "\t";
        }
            std::cout << std::endl;
                return 0;
        }

    public:

        void setStatementManually(){
        connect(); // Ensure the database is connected

        std::string sqlStatement;

        std::cout << "Enter SQL statement: ";
        std::getline(std::cin, sqlStatement);

        char *errMsg = nullptr;
        int rc = sqlite3_exec(db, sqlStatement.c_str(), callback, 0, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        } else {
            std::cout << "Statement executed successfully." << std::endl;
        }

        // Close the database connection
        sqlite3_close(db);
        }

 
    void fetch() {
        connect();
        std::string statement = "SELECT * FROM ";
        std::string table;
        std::cout << "Enter the table name you want to retrieve: ";
        std::getline(std::cin, table);
        statement += table;
        statement += ";";

        sqlite3_stmt* stmt;
        int rc = sqlite3_prepare_v2(db, statement.c_str(), -1, &stmt, 0);

        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        } else {
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                int id = sqlite3_column_int(stmt, 0);
                const unsigned char* name = sqlite3_column_text(stmt, 1);
                std::cout << "id: " << id << " / name: " << name << std::endl;
            }
            sqlite3_finalize(stmt);
        }
    }

};

#endif