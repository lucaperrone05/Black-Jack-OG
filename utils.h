#include "deck.h"
#include "user.h"

void printCentered(const char* message);
void getPassword(char* password, int maxLength);
void getScelta(int* menu);
void printMenuLogin();
void printMenuScelta(char* username, int saldo);
void printChiusuraProgramma();
void printOpzioneNonValida();
void printUsernameSaldo(Utente utente);
void printMescolamento();
void manoIniziale(Utente utente, Carta** mazzo, Carta** cartaEstratta, Carta manoBanco[], Carta manoGiocatore[]);
void printCarteBancoGiocatore(Utente* utente, int punteggioBanco, int punteggioGiocatore, int puntata, Carta manoBanco[], Carta manoGiocatore[], int offsetBanco, int offsetGiocatore, int finale);
void printCarteBancoGiocatoreCoperta(Utente* utente, Carta manoBanco[], Carta manoGiocatore[], int offsetBanco, int offsetGiocatore);
int getPuntata(Utente* utente);
void risultato(Utente* utente, int punteggioBanco, int punteggioGiocatore, int puntata, int numCarteGiocatore);
void printMenuGiocatore(int numCarteGiocatore);
int contaCarteNelMazzo(Carta* mazzo);
