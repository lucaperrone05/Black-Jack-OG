#include <stdio.h>
#include "sqlite3.h"
#include "deck.h"


void apriDatabase(sqlite3** db);
void creaTabellaUser(sqlite3* db);
void registraUtente(sqlite3* db, char* nome, char* cognome, char* username, char* password);
int loginDb(sqlite3* db, const char* username, const char* password);
int caricaUtente(sqlite3* db, const char* username, Utente* utente);
int utenteEsiste(sqlite3* db, const char* username);
void aggiornaSaldo(sqlite3* db, const char* username, int nuovoSaldo);
int salvaMazzoUtente(sqlite3* db, Carta* mazzo, const char* username);
Carta* caricaMazzoUtente(sqlite3* db, const char* username);
void creaTabellaMano(sqlite3* db);
void aggiungi_mano(sqlite3* db, int user_id, int puntata, const char* esito);