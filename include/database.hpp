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
            try{
            mysqlx::Session sess(host, 33060, username, password);
            mysqlx::Schema db = sess.getSchema(database);
            sess.close();
                } catch (const mysqlx::Error &err) {
            std::cerr << "Error: " << err.what() << std::endl;
        } catch (std::exception &ex) {
            std::cerr << "STD Exception: " << ex.what() << std::endl;
        } catch (...) {
            std::cerr << "Unexpected error!" << std::endl;
        }
        }

        

};

#endif