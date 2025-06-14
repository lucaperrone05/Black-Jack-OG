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
    Carta manoBanco[MAX_MANO] = { 0 }; // Mano del banco
    Carta manoGiocatore[MAX_MANO] = { 0 }; // Mano del giocatore
    int scelta, offset = 2;

    if (nuova==1) {
        creaMazzo(&mazzo); // Crea il mazzo di carte
        mescolaMazzo(&mazzo); // Mescola il mazzo di carte
    }
    else {
        //mazzo = carichiamo il mazzo salvato nel DB
    }
    

    printUsernameSaldo(*utente);

    printMescolamento();

	getPuntata(&utente);

    manoIniziale(*utente, &mazzo, &cartaEstratta, manoBanco, manoGiocatore);

    do {
        printf("\n\n");
        printCentered("Inserisci:");

        printf("\n");
        printCentered("1. Carta      2. Stai      3. Raddioppio      4. Split");
        getScelta(&scelta);

        if (scelta == 1) {
            cartaEstratta = pop(&mazzo);
            manoGiocatore[offset] = *cartaEstratta; // Aggiungi una carta alla mano del giocatore
            offset++;
            system("cls"); // Pulisci la console
            
            printUsernameSaldo(*utente);

            printCarteBancoGiocatore(manoBanco, manoGiocatore, 2, offset);
        }

    } while (scelta == 1 && calcolaPunteggio(manoGiocatore, offset) <= 21);

    int numCarteGiocatore = offset;

    if (calcolaPunteggio(manoGiocatore, offset) > 21) {
        printf("\nHai sballato! Hai perso.\n");
    }
    else {
		system("cls"); // Pulisci la console
		
        printUsernameSaldo(*utente);

		printCarteBancoGiocatore(manoBanco, manoGiocatore, 2, numCarteGiocatore);
        offset = 2; // Reset offset per il banco
		
        Sleep(1000); 
        
        int punteggioBanco = calcolaPunteggio(manoBanco, 2);
        
        while (punteggioBanco < 17) { // Il banco deve pescare fino a raggiungere almeno 17
            cartaEstratta = pop(&mazzo);
            manoBanco[offset] = *cartaEstratta; // Aggiungi una carta alla mano del banco
            offset++;
            system("cls"); // Pulisci la console
            printCentered("BlackJack\n");
            printf("%s\nSaldo:%d\n\n\n", utente->username, utente->saldo);
            printf("       Banco:\n");
            stampaCarteAffiancate(manoBanco, offset);
            printf("\n\n\n       Giocatore:\n");
            stampaCarteAffiancate(manoGiocatore, numCarteGiocatore);
            punteggioBanco = calcolaPunteggio(manoBanco, offset);
            Sleep(1000);
        }
    }
}