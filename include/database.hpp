#ifndef __DATABASE_HPP
#define __DATABASE_HPP

#include <iostream>
#include <xdevapi.h>  // Make sure this is the correct path for your MySQL Connector/C++ header
#include "config.hpp" // If you have specific configurations

class Database {
public:
    std::string username;
    std::string password;
    std::string host;
    std::string dbName;
    int port;

private:
    void getDbsInfo() {
        std::cout << "Username: ";
        std::cin >> username;

        std::cout << "Password: ";
        std::cin >> password;

        std::cout << "Host: ";
        std::cin >> host;

        std::cout << "Database: ";
        std::cin >> dbName;

        std::cout << "Port: ";
        std::cin >> port;
    }

public:
    void connect() {
        try {
            getDbsInfo();

            // Establish the session
            mysqlx::Session sess(host, port, username, password);

            // Select the schema (database)
            mysqlx::Schema db = sess.getSchema(dbName);

            // Perform operations with 'db' here
            std::cout << "Connected to database '" << dbName << "' successfully." << std::endl;

            // Example operation: Listing tables in the selected database
            std::cout << "Tables in database '" << dbName << "':" << std::endl;
            for (const auto& table : db.getTables()) {
                std::cout << " - " << table.getName() << std::endl;
            }

            sess.close();
        } catch (const mysqlx::Error &err) {
            std::cerr << "MySQL Error: " << err.what() << std::endl;
        } catch (std::exception &ex) {
            std::cerr << "Standard Exception: " << ex.what() << std::endl;
        } catch (...) {
            std::cerr << "Unexpected error!" << std::endl;
        }
    }

    void getInfo() {
        getDbsInfo();
        // Assuming CONNECT_TO_AND_GET is a macro or function you have defined elsewhere
        CONNECT_TO_AND_GET(host, port, username, password, dbName);
    }
};
#endif
