// Interfaccia con SQLite
#include <stdio.h>
#include "sqlite3.h"

void apriDatabase(sqlite3* db){
	
	
	int rc = sqlite3_open("blackjack.db", &db);
	
	if(rc != SQLITE_OK){
		printf("Database non aperto correttamente: %s\n ", sqlite3_errmsg(db));
		sqlite3_close(db);
	}
	
}

void creaTabellaUser(db){
	char* sqlCreate = "CREATE TABLE IF NOT EXISTS utenti ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "username TEXT NOT NULL UNIQUE, "
                      "password TEXT NOT NULL, "
                      "email TEXT);";
    char* errMsg = 0;
    int rc = sqlite3_exec(db, sql_create, 0, &errMsg);
    
    if(rc != SQLITE_OK)
    {
    	printf("Errore nella creazione della tabella utenti: %s", errMsg);
    	sqlite3_free(errMsg);
    	sqlite3_close(db);
	}
	
	
}
















