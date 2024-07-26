#ifndef __DBS_HPP
#define __DBS_HPP

#include <sqlite3.h>
#include <iostream>

class Database{

    public:
        int dbs;
        std::string dbsPath  = "/Applications/MAMP/db/sqlite";

    private:
        void getDbsInfo(){
            std::cout << "dbsName (with .db): ";
            std::cin >> dbs;
            dbsPath += dbs;
            std::cout<< "Database path:"<<dbsPath;
        }
        
};

#endif