#ifndef __DBS_HPP
#define __DBS_HPP

#include <sqlite3.h>
#include <iostream>
#include "exceptions.hpp"
#include "config.hpp"

class Database{

    public:
        int dbs;
        int rc;
        sqlite3* db;
        char * errMsg = 0;
        std::string dbsPath  = PATH;

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
            }
            else{
                throw DBSOpeningExc();
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

        void createTable(){
            connect();
            const char* sqlCreateTable = "CREATE TABLE IF NOT EXISTS items(id INTEGER PRIMARY KEY, name TEXT);";
            rc = sqlite3_exec(db, sqlCreateTable, 0, 0, &errMsg);
        }

};


#endif