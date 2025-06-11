#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "user.h"
#include "db.h"
#include "deck.h"
#include "game.h"


int main() {

    int exit, menu = 0;

	Utente utente = { 0 }; // Inizializza la struttura utente


    do {
        exit = 0;

		printMenuLogin();  // Stampa il menu di login

		getScelta(&menu); // Ottiene la scelta dell'utente

        switch (menu) {
        case 1:
			login(&utente);  // Funzione per il login
            break;

        case 2:
            signUp(&utente);
            break;

        case 3:
			printChiusuraProgramma(); // Stampa il messaggio di chiusura
            exit = 1;
            break;

        default:
            printf("\nOpzione non valida!\n");
            Sleep(1500);
            system("cls"); // Pulisce lo schermo
			break;
        }
    } while (exit==0 && utente.loggato==0);


    if (utente.loggato) {
    
        exit = 0; // reset exit per il gioco
        menu = 0; // reset menu per il gioco

        do {
			
            printMenuGioco(utente.username, utente.saldo);
            getScelta(&menu);


            switch (menu) {
                case 1:
					system("cls"); // Pulisce lo schermo
				    
                    nuovaPartita();

					system("pause"); // Pausa per visualizzare la carta

                    break;
                case 2:

                    break;
                case 3:

                    break;
                case 4:
                    printChiusuraProgramma(); // Stampa il messaggio di chiusura
                    exit = 1;
                    break;
                defualt:
                    printf("\nOpzione non valida!\n");
                    Sleep(1500);
					system("cls"); // Pulisce lo schermo
					break;
            }
        }while(exit == 0);
        
    }

    return 0;
}
