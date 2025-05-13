// Login, registrazione, gestione saldo
#include <stdio.h>
#include "db.h"
#include "string.h"



void registraUtente(){
	
	sqlite3* db;
	char nome[50];
	char cognome[50];
	char username[50];
	char password[50];
	sqlite3* sql_create;
	
	apriDatabase(db);
	creaTabellaUser(db);
	
	//form registrazione
	puts("Nome:");
	fgets(nome, sizeof(nome), stdin);
	nome[strcspn(nome, "\n")] = '\0';
	
	puts("Cognome:");
	fgets(cognome, sizeof(cognome), stdin);
	nome[strcspn(cognome, "\n")] = '\0';
	
	puts("Username:");
	fgets(usename, sizeof(username), stdin);
	nome[strcspn(username, "\n")] = '\0';
	
	puts("Password:");
	fgets(password, sizeof(password), stdin);
	nome[strcspn(password, "\n")] = '\0';
	

	
	
}
