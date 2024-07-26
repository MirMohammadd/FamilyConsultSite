#ifndef __DBS_HPP
#define __DBS_HPP

#include <sqlite3.h>
#include <iostream>
#include "exceptions.hpp"

class Database{

    public:
        int dbs;
        int rc;
        sqlite3* db;
        char * errMsg = 0;
        std::string dbsPath  = "/Applications/MAMP/db/sqlite";

    private:
        void getDbsInfo(){
            std::cout << "dbsName (with .db): ";
            std::cin >> dbs;
            dbsPath += dbs;
            std::cout<< "Database path:"<<dbsPath;
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
};

#endif