#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "user.h"
#include "db.h"

int main() {

    int exit, menu;

    Utente utente = { 0 };


    do {
        exit = 0;
        printCentered("Gioca a BlackJack!\n\n");

        printf("Selezionare un'opzione:\n");

        printCentered("1. Login\n");
        printCentered("2. Sign Up\n");
        printCentered("3. Exit\n");

        printf("\nScelta: ");

        scanf("%d", &menu);
        getchar(); // ?? Svuota il buffer per evitare problemi con fgets()

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
        }
    } while (exit==0 && utente.loggato==0);

    return 0;
}
