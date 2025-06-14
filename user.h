#ifndef _USER_H
#define _USER_H

typedef struct {
	int id;
	char nome[20];
	char cognome[20];
	char username[20];
	int saldo;
	int loggato; // 1 se loggato, 0 altrimenti
} Utente;

void registraUtente();

void login(Utente* utente);

void signUp(Utente* utente);

#endif
