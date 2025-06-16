#include "deck.h"
#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include <stdio.h>
#define NUM_CARTE 104 // 2 mazzi da 52 carte
#define MAX_MANO 11

// Creazione del mazzo
void  creaMazzo(Carta** top) {
    const char* semi[] = { "♠", "♥", "♦", "♣" };
    char* valori[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
    int punteggi[] = { 11, 2, 3, 4, 5, 6, 7, 8,  9, 10, 10, 10, 10 };

    for (int copia = 0; copia < 2; copia++) {
        for (int s = 0; s < 4; s++) {
            for (int v = 0; v < 13; v++) {
                // Nota: cast via (char*) per evitare warning const/non-const
                push(top, (char*)semi[s], valori[v], punteggi[v]);
            }
        }
    }
}


// Mescolatura del mazzo
void mescolaMazzo(Carta** top) {
    srand(time(NULL));

    int size = contaCarte(*top);
    Carta** array = pilaToArray(*top, size);

    // Fisher-Yates Shuffle
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Carta* tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }

    // Ricostruzione pila
    *top = NULL;
    for (int i = 0; i < size; i++) {
        array[i]->next = *top;
        *top = array[i];
    }

    free(array);
}

// Conversione della pila in array per la mescolatura
Carta** pilaToArray(Carta* top, int size) {
    Carta** array = malloc(size * sizeof(Carta*));
    int i = 0;
    while (top) {
        array[i++] = top;
        top = top->next;
    }
    return array;
}

int contaCarte(Carta* top) {
    int count = 0;
    while (top) {
        count++;
        top = top->next;
    }
    return count;
}

void push(Carta** top, char* seme, char* valore, int punti) {
    Carta* nuova = malloc(sizeof(Carta));
    nuova->seme = seme;
    nuova->valore = valore;
    nuova->punti = punti;
    nuova->next = *top;
    *top = nuova;
}

Carta* pop(Carta** top) {
    if (*top == NULL) return NULL;  // pila vuota

    Carta* primo = *top;       // prendi il primo elemento
    *top = primo->next;        // aggiorna la testa della pila al prossimo elemento
    primo->next = NULL;        // stacca il nodo estratto dalla lista

    return primo;              // ritorna il nodo estratto
}
