#include "deck.h"

int calcolaPunteggio(Carta mano[], int numCarte);
void stampaCarteAffiancate(Carta carte[], int n);
void stampaCarteAffiancateConCoperta(Carta carte[], int n);
int turnoGiocatore(Utente* utente, Carta** mazzo, Carta manoGiocatore[], Carta manoBanco[], int* numCarteGiocatore, int numCarteBanco,
    Carta* cartaEstratta, int* puntata);
int turnoBanco(Utente* utente, Carta** mazzo, Carta manoBanco[], Carta manoGiocatore[], int numCarteBanco, int numCarteGiocatore,
    Carta* cartaEstratta, int punteggioGiocatore);
void partita(Utente* utente, int nuova);
