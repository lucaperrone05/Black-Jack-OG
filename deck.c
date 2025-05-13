#include "deck.h"
#include <stdlib.h>
#include <time.h>
#define NUM_CARTE 52
#define MAX_MANO 11

// Creazione del mazzo
void creaMazzo(Carta mazzo[]) {
    char *semi[] = {"\x06", "\x03", "\x04", "\x05"};
    char *valori[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    int punteggi[] = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};

    int index = 0;
    for (int s = 0; s < 4; s++) {
        for (int v = 0; v < 13; v++) {
            mazzo[index].seme = semi[s];
            mazzo[index].valore = valori[v];
            mazzo[index].punti = punteggi[v];
            index++;
        }
    }
}

// Mescolatura del mazzo
void mescolaMazzo(Carta mazzo[]) {
    srand(time(NULL)); // ?? Aggiunta dichiarazione di `time()`
    for (int i = 0; i < NUM_CARTE; i++) {
        int j = rand() % NUM_CARTE;
        Carta temp = mazzo[i];
        mazzo[i] = mazzo[j];
        mazzo[j] = temp;
    }
}

