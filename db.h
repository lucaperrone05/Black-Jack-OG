#include <stdio.h>
#include "sqlite3.h"


void apriDatabase(sqlite3** db);
void creaTabellaUser(sqlite3* db);
void registraUtente(sqlite3* db, char* nome, char* cognome, char* username, char* password);
int loginDb(sqlite3* db, const char* username, const char* password);
