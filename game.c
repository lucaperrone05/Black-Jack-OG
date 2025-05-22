// Logica del gioco (Blackjack)
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "deck.h"
#define NUM_CARTE 2
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

void stampaCarta(Carta c) {
    // Cambia colore in ROSSO per cuori ?? e quadri ??
    if (strcmp(c.seme, "?") == 0 || strcmp(c.seme, "?") == 0) {
        setColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    }
    else {
        setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Bianco (default)
    }

    printf("+---------+\n");
    printf("¦ %-2s      ¦\n", c.valore);
    printf("¦         ¦\n");
    printf("¦    %s    ¦\n", c.seme);
    printf("¦         ¦\n");
    printf("¦      %-2s ¦\n", c.valore);
    printf("+---------+\n");

    // Reset al colore standard
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}


void blackjackGame() {
    Carta mazzo[NUM_CARTE];
    creaMazzo(mazzo);
    mescolaMazzo(mazzo);

    Carta manoGiocatore[MAX_MANO], manoBanco[MAX_MANO];
    int carteGiocatore = 2, carteBanco = 2;

    manoGiocatore[0] = mazzo[0];
    manoGiocatore[1] = mazzo[1];
    manoBanco[0] = mazzo[2];
    manoBanco[1] = mazzo[3];

    printf("Le tue carte:\n");
    stampaCarta(manoGiocatore[0]);
    stampaCarta(manoGiocatore[1]);
    printf("Punteggio: %d\n", calcolaPunteggio(manoGiocatore, carteGiocatore));

    printf("\nBanco mostra:\n");
    stampaCarta(manoBanco[0]);

    while (calcolaPunteggio(manoGiocatore, carteGiocatore) < 21) {
        int scelta;
        printf("\nVuoi pescare una carta? (1 = Sì, 2 = No): ");
        scanf("%d", &scelta);

        if (scelta == 1) {
            manoGiocatore[carteGiocatore++] = mazzo[4 + carteGiocatore - 2];
            stampaCarta(manoGiocatore[carteGiocatore - 1]);
            printf("Punteggio aggiornato: %d\n", calcolaPunteggio(manoGiocatore, carteGiocatore));
        }
        else {
            break;
        }
    }

    if (calcolaPunteggio(manoGiocatore, carteGiocatore) > 21) {
        printf("\nHai sballato! Il Banco vince.\n");
        return;
    }

    while (calcolaPunteggio(manoBanco, carteBanco) < 17) {
        manoBanco[carteBanco++] = mazzo[4 + carteGiocatore - 2 + carteBanco - 2];
    }

    printf("\nBanco ha:\n");
    for (int i = 0; i < carteBanco; i++) {
        stampaCarta(manoBanco[i]);
    }
    printf("Punteggio Banco: %d\n", calcolaPunteggio(manoBanco, carteBanco));

    int punteggioGiocatore = calcolaPunteggio(manoGiocatore, carteGiocatore);
    int punteggioBanco = calcolaPunteggio(manoBanco, carteBanco);

    if (punteggioBanco > 21 || punteggioGiocatore > punteggioBanco) {
        printf("\nHai vinto!\n");
    }
    else if (punteggioGiocatore == punteggioBanco) {
        printf("\nPareggio!\n");
    }
    else {
        printf("\nIl Banco vince!\n");
    }
}
