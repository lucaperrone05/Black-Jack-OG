// Interfaccia con SQLite
#include <stdio.h>
#include "sqlite3.h"
#include "user.h"

//funzione che apre il database
void apriDatabase(sqlite3** db) {
	int rc = sqlite3_open("blackjack.db", db); // Corretto: passa il doppio puntatore
	if (rc != SQLITE_OK) {
		printf("Database non aperto correttamente: %s\n", sqlite3_errmsg(*db));
		sqlite3_close(*db);
	}
}


//funzione per creare la tabella utenti se non esiste
void creaTabellaUser(sqlite3* db) {
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
// Cambia i tipi da 'char' a 'char*'
void registraUtente(sqlite3* db, char* nome, char* cognome, char* username, char* password) {
	sqlite3_stmt* stmt;

	const char* sqlInsert = "INSERT INTO utenti(nome, cognome, username, saldo, password) VALUES (?, ?, ?, ?, ?);";
	int rc = sqlite3_prepare_v2(db, sqlInsert, -1, &stmt, 0);

	if (rc != SQLITE_OK) {
		printf("Errore preparazione query: %s\n", sqlite3_errmsg(db));
		return;
	}

	sqlite3_bind_text(stmt, 1, nome, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, cognome, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, username, -1, SQLITE_STATIC);
	sqlite3_bind_int(stmt, 4, 4000); // saldo iniziale
	sqlite3_bind_text(stmt, 5, password, -1, SQLITE_STATIC);

	rc = sqlite3_step(stmt);

	if (rc != SQLITE_DONE) {
		printf("Errore inserimento: %s\n", sqlite3_errmsg(db));
	}
	else {
		printf("Dati inseriti con successo.\n");
	}

	sqlite3_finalize(stmt);
}



//funzione per cercare l'utente nel database
int loginDb(sqlite3* db, const char* username, const char* password) {
	sqlite3_stmt* stmt;
	int loginValido = 0;

	const char* sql = "SELECT COUNT(*) FROM utenti WHERE username = ? AND password = ?;";
	int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		printf("Errore nella preparazione della query: %s\n", sqlite3_errmsg(db));
		return 0;
	}

	sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW) {
		int count = sqlite3_column_int(stmt, 0); // Legge il valore di COUNT(*)
		if (count == 1) {
			loginValido = 1; // Login riuscito
		}
		else {
			printf("Credenziali errate.\n");
			Sleep(2000);
		}
	}
	else {
		printf("Errore durante l'esecuzione della query.\n");
		Sleep(2000);
	}

	sqlite3_finalize(stmt);
	return loginValido;
}


int caricaUtente(sqlite3* db, const char* username, Utente* utente) {
	sqlite3_stmt* stmt;
	const char* sql = "SELECT id, nome, cognome, username, saldo FROM utenti WHERE username = ?;";

	int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) {
		printf("Errore preparazione query: %s\n", sqlite3_errmsg(db));
		return 0;
	}

	sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

	rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW) {
		utente->id = sqlite3_column_int(stmt, 0); // ID
		strcpy(utente->nome, (const char*)sqlite3_column_text(stmt, 1)); // nome
		strcpy(utente->cognome, (const char*)sqlite3_column_text(stmt, 2)); // cognome
		strcpy(utente->username, (const char*)sqlite3_column_text(stmt, 3)); // username
		utente->saldo = sqlite3_column_int(stmt, 4); // saldo
		sqlite3_finalize(stmt);
		return 1;
	}
	else {
		printf("Utente non trovato.\n");
		sqlite3_finalize(stmt);
		return 0;
	}
}
