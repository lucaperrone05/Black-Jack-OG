// Logica del gioco (Blackjack)
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "deck.h"
#include "utils.h"
#include "user.h"
#define NUM_CARTE 52
#define MAX_MANO 10

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

void stampaCarteAffiancate(Carta carte[], int n) {

    system("chcp 65001 >nul"); // UTF-8 per la console

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
        printf("\n");
    }
}


void stampaCarteAffiancateConCoperta(Carta carte[], int n) {
    system("chcp 65001 >nul"); // UTF-8 per la console

    for (int riga = 0; riga < 8; riga++) {
        for (int i = 0; i < n; i++) {
            Carta c = carte[i];
            int coperta = (i == 1); // la seconda carta (indice 1) è sempre coperta

            if (coperta) {
                switch (riga) {
                case 0: printf(" _________ "); break;
                case 1: printf("|         |"); break;
                case 2: printf("|         |"); break;
                case 3: printf("|         |"); break;
                case 4: printf("|   ? ?   |"); break;
                case 5: printf("|         |"); break;
                case 6: printf("|         |"); break;
                case 7: printf("|_________|"); break;
                }
            }
            else {
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
        }
        printf("\n");
    }
}


void partita(Utente* utente, int nuova) {
    Carta* mazzo = NULL;
    Carta* cartaEstratta;
    Carta manoBanco[MAX_MANO] = { 0 };
    Carta manoGiocatore[MAX_MANO] = { 0 };
    
    if (nuova == 1) {
        creaMazzo(&mazzo);
        printUsernameSaldo(*utente);
        printMescolamento();
        mescolaMazzo(&mazzo);
    }
    else {
        // mazzo = carichiamo il mazzo salvato nel DB
    }


    do {
        int scelta;
        int numCarteGiocatore = 2;
        int numCarteBanco = 2;
        int punteggioGiocatore = 0;
        int punteggioBanco = 0;

        int puntata = getPuntata(utente);

        manoIniziale(*utente, &mazzo, &cartaEstratta, manoBanco, manoGiocatore);

        do {
            printMenuGiocatore();
            getScelta(&scelta);

            if (scelta == 1) {
                cartaEstratta = pop(&mazzo);
                manoGiocatore[numCarteGiocatore++] = *cartaEstratta;

                printCarteBancoGiocatore(utente, punteggioBanco, punteggioGiocatore, puntata, manoBanco, manoGiocatore, numCarteBanco, numCarteGiocatore, 0);
            }

            punteggioGiocatore = calcolaPunteggio(manoGiocatore, numCarteGiocatore);
        } while (scelta == 1 && punteggioGiocatore <= 21);


        if (punteggioGiocatore <= 21) {

            printCarteBancoGiocatore(utente, punteggioBanco, punteggioGiocatore, puntata, manoBanco, manoGiocatore, numCarteBanco, numCarteGiocatore, 0);

            punteggioBanco = calcolaPunteggio(manoBanco, numCarteBanco);

            Sleep(1000);

            while (punteggioBanco < 17) {
                cartaEstratta = pop(&mazzo);
                manoBanco[numCarteBanco++] = *cartaEstratta;

                printCarteBancoGiocatore(utente, punteggioBanco, punteggioGiocatore, puntata, manoBanco, manoGiocatore, numCarteBanco, numCarteGiocatore, 0);

                punteggioBanco = calcolaPunteggio(manoBanco, numCarteBanco);
                Sleep(1000);
            }
        }

        printCarteBancoGiocatore(utente, punteggioBanco, punteggioGiocatore, puntata, manoBanco, manoGiocatore, numCarteBanco, numCarteGiocatore, 1);

    } while (continuaPartita(utente) == 1);
}