#include "deck.h"
#include "user.h"
#include "sqlite3.h"

// Stampa un messaggio centrato
void printCentered(const char* message); 

// Funzione per ottenere la password in modo sicuro
void getPassword(char* password, int maxLength); 

// Funzione per ottenere la scelta dell'utente
void getScelta(int* menu);

// Stampa il menu di login
void printMenuLogin(); 

// Stampa il menu di scelta dopo il login
void printMenuScelta(char* username, int saldo); 

// Stampa un messaggio di chiusura del programma
void printChiusuraProgramma(); 

// Stampa un messaggio per opzione non valida
void printOpzioneNonValida(); 

// Stampa l'username e il saldo dell'utente
void printUsernameSaldo(Utente utente); 

// Stampa il menu di scelta del gioco
void printMescolamento(); 

// Gestisce la mano iniziale del gioco
void manoIniziale(Utente utente, Carta** mazzo, Carta** cartaEstratta, Carta manoBanco[], Carta manoGiocatore[]);

// Gestisce il turno del giocatore
void printCarteBancoGiocatore(Utente* utente, int punteggioBanco, int punteggioGiocatore, int puntata, Carta manoBanco[], Carta manoGiocatore[], int offsetBanco, int offsetGiocatore, int finale);

// Stampa le carte del banco e del giocatore, con offset per la visualizzazione
void printCarteBancoGiocatoreCoperta(Utente* utente, Carta manoBanco[], Carta manoGiocatore[], int offsetBanco, int offsetGiocatore);

// Ottiene la puntata dell'utente
int getPuntata(Utente* utente); 

// Gestisce il turno del banco
void risultato(Utente* utente, int punteggioBanco, int punteggioGiocatore, int puntata, int numCarteGiocatore);

// Stampa il risultato del turno
void printMenuGiocatore(int numCarteGiocatore);

// Stampa il menu delle opzioni del giocatore
int contaCarteNelMazzo(Carta* mazzo);

// Conta il numero di carte nel mazzo
char* serializzaMazzo(Carta* mazzo);

// Serializza il mazzo di carte in una stringa
Carta* deserializzaMazzo(const char* str);

// Deserializza una stringa in un mazzo di carte
void liberaMazzo(Carta* mazzo);

// Stampa le ultime 10 mani di blackjack di un utente
void stampaUltime10Mani(sqlite3* db, Utente utente);
