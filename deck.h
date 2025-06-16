#ifndef _DECK_H
#define _DECK_H

// Definizione della struttura
typedef struct Carta {
    char* seme;
    char* valore;
    int punti;
    struct Carta* next; // per la pila
} Carta;

// Dichiarazione delle funzioni
Carta** pilaToArray(Carta* top, int size);
int contaCarte(Carta* top);
void mescolaMazzo(Carta** top);
void creaMazzo(Carta** top);
void push(Carta** top, char* seme, char* valore, int punti);
Carta* pop(Carta** top);
#endif
