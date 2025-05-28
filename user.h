#include <stdio.h>

typedef struct {
	int id;
	char nome[20];
	char cognome[20];
	char username[20];
	int saldo;
	int loggato; // 1 se loggato, 0 altrimenti
} Utente;

void registraUtente();

void getPassword(char* password, int maxLength);

int login(Utente* utente);

void signUp(Utente* utente);
