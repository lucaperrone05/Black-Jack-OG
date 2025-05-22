// Interfaccia con SQLite
#include <stdio.h>
#include "sqlite3.h"

//funzione che apre il database
void apriDatabase(sqlite3* db) {


	int rc = sqlite3_open("blackjack.db", &db); // Apre il database (crea il file se non esiste)

	if (rc != SQLITE_OK) {
		printf("Database non aperto correttamente: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
	}

}


//funzione per creare la tabella utenti se non esiste
void creaTabellaUser(db) {
	char* sqlCreate = "CREATE TABLE IF NOT EXISTS utenti ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT, "
		"nome TEXT NOT NULL, "
		"cognome TEXT NOT NULL, "
		"username TEXT UNIQUE NOT NULL, "
		"saldo TEXT NOT NULL, "
		"password TEXT NOT NULL);";
	char* errMsg = 0;
	int rc = sqlite3_exec(db, sqlCreate, 0, 0, &errMsg); // Esegue la query di creazione della tabella

	if (rc != SQLITE_OK) {
		printf("Errore nella creazione della tabella utenti: %s\n", errMsg);
		sqlite3_free(errMsg);
		sqlite3_close(db);
	}


}

//funzione per inserire il nuovo utente nel database
void registraUtente(sqlite3* db, char nome, char cognome, char username, char password) {
	sqlite3_stmt* stmt; // Dichiarazione del puntatore per la query

	// Query SQL per inserire i dati dell'utente
	char sqlInsert = "INSERT INTO utenti(nome, cognome, username, saldo, password) VALUES (?, ?, ?, ?, ?);";
	int rc = sqlite3_prepare_v2(db, sqlInsert, -1, &stmt, 0); // Prepara la query SQL

	if (rc != SQLITE_OK) {
		printf("Errore preparazione query: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);

	}

	sqlite3_bind_text(stmt, 1, nome, -1, SQLITE_STATIC); // Associa il parametro nome
	sqlite3_bind_text(stmt, 2, cognome, -1, SQLITE_STATIC); // Associa il parametro cognome
	sqlite3_bind_text(stmt, 3, username, -1, SQLITE_STATIC); // Associa il parametro username
	sqlite3_bind_int(stmt, 4, 4000); // Associa il parametro saldo 
	sqlite3_bind_text(stmt, 5, password, -1, SQLITE_STATIC); // Associa il parametro password


	rc = sqlite3_step(stmt); // Esegue la query

	if (rc != SQLITE_OK) {

		printf("Errore inserimento: %s\n", sqlite3_errmsg(db));

	}
	else {

		printf("Dati inseriti con successo.\n");

	}

	sqlite3_close(db); // Chiude il database
}


//funzione per cercare l'utente nel database
void loginDb(sqlite3* db, const char* username, const char* password) {
	sqlite3_stmt* stmt; // Dichiarazione del puntatore per la query

	const char* sql = "SELECT COUNT(*) FROM utenti WHERE username = ? AND password = ?;";
	int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL); // Prepara la query SQL
	if (rc != SQLITE_OK) {
		printf("Errore nella preparazione della query: %s\n", sqlite3_errmsg(db));

	}

	sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC); // Associa il parametro username
	sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC); // Associa il parametro password
	sqlite3_step(stmt); // Esegue la query
	sqlite3_finalize(stmt); // Libera la memoria allocata per la query
}













