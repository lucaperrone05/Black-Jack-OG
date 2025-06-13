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


void nuovaPartita(Utente utente) {
    Carta* mazzo = NULL;
    Carta manoBanco[MAX_MANO] = { 0 }; // Mano del banco
	Carta manoGiocatore[MAX_MANO] = { 0 }; // Mano del giocatore


    creaMazzo(&mazzo); // Crea il mazzo di carte
    mescolaMazzo(&mazzo); // Mescola il mazzo di carte

    printCentered("BlackJack\n");
    printf("%s\nSaldo:%d\n\n\n", utente.username, utente.saldo);
	printCentered("Procedo al mescolamento delle carte . . .");
	Sleep(2000); // Attendi 2 secondi per dare tempo di leggere il messaggio
	system("cls"); // Pulisci la console

    printCentered("BlackJack\n\n");
    printf("%s\nSaldo:%d\n\n\n", utente.username, utente.saldo);

    printf("       Banco:\n");
    
    Carta* cartaEstratta;
    cartaEstratta = pop(&mazzo);
    manoBanco[0] = *cartaEstratta;  // copia il contenuto della struttura
   
    cartaEstratta = pop(&mazzo);
    manoBanco[1] = *cartaEstratta; // Prima carta del banco

    stampaCarteAffiancate(manoBanco, 2);

	printf("\n\n\n       Giocatore:\n");

    int scelta;

    for (int i=0; i < 2; i++) {
        cartaEstratta = pop(&mazzo);
        manoGiocatore[i] = *cartaEstratta;  // copia il contenuto della struttura
    }
    stampaCarteAffiancate(manoGiocatore, 2);

    int offset = 2;
    do {
		printf("Inserisci 1 per chiedere carta");
        getScelta(&scelta);

        if (scelta == 1) {
            cartaEstratta = pop(&mazzo);
            manoGiocatore[offset] = *cartaEstratta; // Aggiungi una carta alla mano del giocatore
            offset++;
			system("cls"); // Pulisci la console
            printf("       Banco:\n");
            stampaCarteAffiancate(manoBanco, 2);
            printf("\n\n\n       Giocatore:\n");
            stampaCarteAffiancate(manoGiocatore, offset);
		}

    } while (scelta==1);

}

