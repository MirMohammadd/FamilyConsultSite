#ifndef __DATABASE_HPP
#define __DATABASE_HPP


#include <iostream>
#include "xdevapi.h"
#include "config.hpp"

class database{
    public:
        std::string username;
        std::string password;
        std::string host;
        std::string database;
    private:

        void getDbsInfo(){
            std::cout << "Username: ";
            std::cin >> username;

            std::cout << "Password: ";
            std::cin >> password;

            std::cout << "Host: ";
            std::cin >> host;

            std::cout << "Database: ";
            std::cin >> database;
        }

    public:
        void connect(){
            mysqlx::Session sess(host, 33060, username, password);
            mysqlx::Schema db = sess.getSchema(database);

        }

        

};

#endif