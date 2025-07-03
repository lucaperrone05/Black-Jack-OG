// Logica del gioco (Blackjack)
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "deck.h"
#include "utils.h"
#include "user.h"
#include "db.h"
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

int turnoGiocatore(Utente* utente, Carta** mazzo, Carta manoGiocatore[], Carta manoBanco[], int* numCarteGiocatore,
    int numCarteBanco,Carta* cartaEstratta, int *puntata) {

	int exit = 0, scelta;
    int punteggioGiocatore = calcolaPunteggio(manoGiocatore, 2);

    while (exit == 0 && punteggioGiocatore < 21) {
        printMenuGiocatore(*numCarteGiocatore);
        getScelta(&scelta);

        switch (scelta) {
        case 1:
            cartaEstratta = pop(mazzo);
            manoGiocatore[(*numCarteGiocatore)++] = *cartaEstratta;
            printCarteBancoGiocatoreCoperta(utente, manoBanco, manoGiocatore, numCarteBanco, *numCarteGiocatore);
            break;

        case 2:
            exit = 1; // Il giocatore decide di fermarsi
            break;

        case 3:
            if (*numCarteGiocatore == 2) {
                utente->saldo -= *puntata; // Sottrae la puntata raddoppiata dal saldo dell'utente
                *puntata *= 2; // Raddoppia la puntata
                cartaEstratta = pop(mazzo);
                manoGiocatore[(*numCarteGiocatore)++] = *cartaEstratta;
                printCarteBancoGiocatoreCoperta(utente, manoBanco, manoGiocatore, numCarteBanco, *numCarteGiocatore);
                exit = 1; // Il giocatore decide di fermarsi dopo il raddoppio
            }
            else {
                printOpzioneNonValida();
                printCarteBancoGiocatoreCoperta(utente, manoBanco, manoGiocatore, numCarteBanco, *numCarteGiocatore);
            }
            break;

        default:
            printOpzioneNonValida();
            printCarteBancoGiocatoreCoperta(utente, manoBanco, manoGiocatore, numCarteBanco, *numCarteGiocatore);
        }
        punteggioGiocatore = calcolaPunteggio(manoGiocatore, *numCarteGiocatore);
    };

	return punteggioGiocatore;
}

int turnoBanco(Utente* utente, Carta** mazzo, Carta manoBanco[], Carta manoGiocatore[], int numCarteBanco, int numCarteGiocatore,
    Carta* cartaEstratta, int punteggioGiocatore, int puntata) {

    int punteggioBanco = calcolaPunteggio(manoBanco, numCarteBanco);

    if (punteggioGiocatore <= 21) {

        printCarteBancoGiocatore(utente, punteggioBanco, punteggioGiocatore, puntata, manoBanco, manoGiocatore, numCarteBanco, numCarteGiocatore, 0);

        Sleep(1000);

        while (punteggioBanco < 17) {
            cartaEstratta = pop(mazzo);
            manoBanco[numCarteBanco++] = *cartaEstratta;

            punteggioBanco = calcolaPunteggio(manoBanco, numCarteBanco);
            printCarteBancoGiocatore(utente, punteggioBanco, punteggioGiocatore, puntata, manoBanco, manoGiocatore,
                numCarteBanco, numCarteGiocatore, 0);

            Sleep(1300);
        }
    }

    printCarteBancoGiocatore(utente, punteggioBanco, punteggioGiocatore, puntata, manoBanco, manoGiocatore,
        numCarteBanco, numCarteGiocatore, 1);
}


void partita(Utente* utente, int caricaPartita) {
    Carta* mazzo = NULL;
    Carta* cartaEstratta;
    Carta manoBanco[MAX_MANO] = { 0 };
    Carta manoGiocatore[MAX_MANO] = { 0 };
    sqlite3* db;
    
    if (caricaPartita == 1) {
        apriDatabase(&db);
        mazzo = caricaMazzoUtente(db, utente->username);
        sqlite3_close(db);

        if(mazzo == NULL) {
			printUsernameSaldo(*utente);
            printCentered("Nessun mazzo da caricare. Verra' creato un nuovo mazzo.");
			Sleep(2500);
			system("cls");
		}
    }
  
    do {

        int scelta, exit = 0;
        int numCarteGiocatore = 2;
        int numCarteBanco = 2;
        int punteggioGiocatore = 0;
        int punteggioBanco = 0;
		int puntata = 0;

        if (mazzo == NULL || contaCarte(mazzo) < 20) {
            creaMazzo(&mazzo);
            printUsernameSaldo(*utente);
            printMescolamento();
            mescolaMazzo(&mazzo);
        }

        puntata = getPuntata(utente);

        manoIniziale(*utente, &mazzo, &cartaEstratta, manoBanco, manoGiocatore);

        punteggioGiocatore = turnoGiocatore(utente, &mazzo, manoGiocatore, manoBanco, &numCarteGiocatore, numCarteBanco, 
            cartaEstratta, &puntata);

		turnoBanco(utente, &mazzo, manoBanco, manoGiocatore, numCarteBanco, numCarteGiocatore, cartaEstratta,
            punteggioGiocatore, puntata);

		apriDatabase(&db);
        salvaMazzoUtente(db, mazzo, utente->username);
        aggiungi_mano(db, utente->id, puntata, (punteggioGiocatore > 21) ? "LOSE" : (punteggioBanco > 21 || punteggioGiocatore > punteggioBanco) ? "WIN" : "PUSH");
		sqlite3_close(db);


    } while (continuaPartita(utente) == 1);
}