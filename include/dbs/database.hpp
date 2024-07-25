#ifndef __DATABASE_HPP
#define __DATABASE_HPP


#include <iostream>

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
            
        }
};

#endif