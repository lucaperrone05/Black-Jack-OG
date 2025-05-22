#include <stdio.h>

typedef struct {
	int id;
	char nome[20];
	char cognome[20];
	char username[20];
	int saldo;
} Utente;

void registraUtente();

void getPassword(char* password, int maxLength);

void login(Utente* utente);

void signUp(Utente* utente);
