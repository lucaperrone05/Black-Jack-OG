#include "deck.h"
#include "user.h"

void printCentered(const char* message);
void getPassword(char* password, int maxLength);
void getScelta(int* menu);
void printMenuLogin();
void printMenuGioco(char* username, int saldo);
void printChiusuraProgramma();
void printUsernameSaldo(Utente utente);
void printMescolamento();
void manoIniziale(Utente utente, Carta** mazzo, Carta** cartaEstratta, Carta manoBanco[], Carta manoGiocatore[]);
void printCarteBancoGiocatore(Carta manoBanco[], Carta manoGiocatore[], int offsetBanco, int offsetGiocatore);
int getPuntata(Utente* utente);