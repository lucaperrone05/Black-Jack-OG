// Logica del gioco (Blackjack)
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "deck.h"
#define NUM_CARTE 52
#define MAX_MANO 2


int calcolaPunteggio(Carta mano[], int numCarte) {
    int punteggio = 0, numAssi = 0;
    for (int i = 0; i < numCarte; i++) {
        punteggio += mano[i].punti;
        if (strcmp(mano[i].valore, "A") == 0) numAssi++;
    }
    while (punteggio > 21 && numAssi > 0) {
        punteggio -= 10;
        numAssi--;
    }
    return punteggio;
}

void setColor(int colore) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colore);
}

//void stampaCarta(Carta c) {
//    // Cambia colore in ROSSO per cuori ?? e quadri ??
//    if (strcmp(c.seme, "?") == 0 || strcmp(c.seme, "?") == 0) {
//        setColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
//    }
//    else {
//        setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Bianco (default)
//    }
//
//    printf(" _________\n");
//    printf("|         |\n");
//    printf("| %-2s      |\n", c.valore);
//    printf("|         |\n");
//    printf("|    %s    |\n", c.seme);
//    printf("|         |\n");
//    printf("|      %-2s |\n", c.valore);
//    printf("|_________|\n");
//
//    // Reset al colore standard
//    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
//}


void stampaCarteAffiancate(Carta carte[], int n) {
    for (int riga = 0; riga < 8; riga++) {
        for (int i = 0; i < n; i++) {
            Carta c = carte[i];
            switch (riga) {
            case 0: printf(" _________ "); break;
            case 1: printf("|         |"); break;
            case 2: printf("| %-2s      |", c.valore); break;
            case 3: printf("|         |"); break;
            case 4: printf("|    %s    |", c.seme); break;
            case 5: printf("|         |"); break;
            case 6: printf("|      %-2s |", c.valore); break;
            case 7: printf("|_________|"); break;
            }
        }
        printf("\n"); // Vai a capo dopo ogni riga
    }
}

void nuovaPartita() {
    Carta mazzo[52] = { 0 }; // Inizializza il mazzo di carte

    creaMazzo(mazzo); // Crea il mazzo di carte
    mescolaMazzo(mazzo); // Mescola il mazzo di carte

    stampaCarteAffiancate(mazzo, 2);

}
