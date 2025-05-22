#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "user.h"
#include "db.h"

int main() {

    printCentered("Gioca a BlackJack!\n\n");

    printf("Selezionare un'opzione:\n");

    printCentered("1. Login\n");
    printCentered("2. Sign Up\n");
    printCentered("3. Exit\n");

    int menu;
    Utente utente = { 0 };

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
        printf("\nChiusura del programma...\n");
        return 0;

    default:
        printf("\nOpzione non valida!\n");
        return 0;
    }

 
    printf("----- DATI UTENTE -----\n");
    printf("ID: %d\n", utente.id);
    printf("Nome: %s\n", utente.nome);
    printf("Cognome: %s\n", utente.cognome);
    printf("Username: %s\n", utente.username);
    printf("Saldo: %d\n", utente.saldo);


    return 0;
}
