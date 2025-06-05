#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "user.h"
#include "db.h"


int main() {

    int exit, menu = 0;

    Utente utente = { 0 };

    

    do {
        exit = 0;
        printCentered("Gioca a BlackJack!\n\n");

        printf("Selezionare un'opzione:\n");

        printCentered("1. Login\n");
        printCentered("2. Sign Up\n");
        printCentered("3. Exit\n");

        getScelta(&menu);

        switch (menu) {
        case 1:
            login(&utente);
            break;

        case 2:
            signUp(&utente);
            break;

        case 3:
            system("cls");
			printf("\n\n\n");
            printCentered("Chiusura del programma...");
            printf("\n\n\n");
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

       
        system("cls");
        printCentered("Benvenuto nel gioco di BlackJack!\n\n");
        printf("Nome utente: %s\n", utente.username);
        printf("Saldo: %d\n", utente.saldo);
        printf("\n\n");

        printCentered("Selezionare un'opzione:\n\n");
        printCentered("1. Nuova partita\n");
        printCentered("2. Carica partita\n");
        printCentered("3. Visualizza storico partite\n");
        printCentered("4. Exit\n");
    
        exit = 0; // reset exit per il gioco
        menu = 0; // reset menu per il gioco

        do {
            getScelta(&menu);


            switch (menu) {
                case 1:
                    
					break;
                case 2:

                    break;
                case 3:

                    break;
                case 4:
                    system("cls");
                    printf("\n\n\n");
                    printCentered("Chiusura del programma...");
                    printf("\n\n\n");
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
