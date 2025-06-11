#ifndef _DECK_H
#define _DECK_H
// Definizione della struttura
typedef struct {
    char* seme;
    char* valore;
    int punti;
} Carta;

// Dichiarazione delle funzioni
void creaMazzo(Carta mazzo[]);
void mescolaMazzo(Carta mazzo[]);
void rimuoviCarteInizio(Carta** mazzo, int* size, int n);
#endif
