#include <iostream>
#include <sqlite3.h>
#include <config.hpp>
#include <dbs.hpp>

#define INSERTED


void sqliteEnter(){
    Database interface;
    interface.connect();
}

int main(int argc,char* argv[]) {
    std::cout<<Logo;
    for (int i = 0; i < argc; ++i){
        if (strcmp("--manual",argv[i]) == 0){
            Database interface;
            interface.createTable("user",2,false);
        }
    }

    #ifdef SQLITE
    sqliteEnter();
    #endif  
    sqlite3* db;
    char* errMsg = 0;
    int rc;

    rc = sqlite3_open(PATH, &db);

    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return(0);
    } else {
        std::cout << "Opened database successfully" << std::endl;
    }

    const char* sqlCreateTable = "CREATE TABLE IF NOT EXISTS items(id INTEGER PRIMARY KEY, name TEXT);";
    rc = sqlite3_exec(db, sqlCreateTable, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Table created successfully" << std::endl;
    }

    #ifndef INSERTED
    const char* sqlInsert1 = "INSERT INTO items(name) VALUES('Name 1');";
    const char* sqlInsert2 = "INSERT INTO items(name) VALUES('Name 2');";
    sqlite3_exec(db, sqlInsert1, 0, 0, &errMsg);
    sqlite3_exec(db, sqlInsert2, 0, 0, &errMsg);

    #endif

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Records created successfully" << std::endl;
    }

    sqlite3_int64 lastRowId = sqlite3_last_insert_rowid(db);
    std::cout << "The last inserted row ID is " << lastRowId << "." << std::endl;

    const char* sqlSelect = "SELECT * FROM items;";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sqlSelect, -1, &stmt, 0);

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

    #ifdef DELETE_INSERTED  

    const char* sqlDelete = "DELETE FROM items;";
    rc = sqlite3_exec(db, sqlDelete, 0, 0, &errMsg);
    #endif

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        int changes = sqlite3_changes(db);
        std::cout << "The DELETE statement removed " << changes << " rows." << std::endl;
    }

    sqlite3_close(db);
    return 0;


}
