#ifndef __DATABASE_HPP
#define __DATABASE_HPP

#include <iostream>
#include <xdevapi.h>  // Make sure this is the correct path for your MySQL Connector/C++ header

class Database {
public:
    std::string username;
    std::string password;
    std::string host;
    std::string dbName;
    std::string unixSocket;
    int port;
    bool raiseOnWarnings;

    // Constructor to initialize the database configuration
    Database() : 
        username("root"),
        password("root"),
        host("localhost"),
        dbName("mydatabase"),
        unixSocket("/Applications/MAMP/tmp/mysql/mysql.sock"),
        port(3306),  // Default MySQL port
        raiseOnWarnings(true)
    {}

    void connect() {
        try {
            // Establish the session using unixSocket for UNIX socket connections
            mysqlx::Session sess(host, port, username, password);

            // If using UNIX socket
            // mysqlx::Session sess(mysqlx::Socket(unixSocket), username, password);

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
};

#endif
