#ifndef __DATABASE_HPP
#define __DATABASE_HPP


#include <iostream>
#include "xdevapi.h"

class database{
    public:
        std::string username;
        std::string password;
        std::string host;
    
    private:

        void getDbsInfo(){
            std::cout << "Username: ";
            std::cin >> username;

            std::cout << "Password: ";
            std::cin >> password;

            std::cout << "Host: ";
            std::cin >> host;
        }

    public:
        void connect(){
            mysqlx::Session sess(host, 33060, username, password);

        }
};

#endif