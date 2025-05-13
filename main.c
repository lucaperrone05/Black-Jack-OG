#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "user.h"

int main() {
    printCentered("Gioca a BlackJack!\n\n");

    printf("Selezionare un'opzione:\n");
    printCentered("1. Login\n");
    printCentered("2. Sign Up\n");
    printCentered("3. Exit\n");

    int menu;
    printf("\nScelta: ");
    scanf("%d", &menu);
    getchar(); // ?? Svuota il buffer per evitare problemi con fgets()

	char nome [20];
	char cognome [20];
	char username[20];
	char password[20];
	char ripeti_password[20];
			
    switch(menu) {
        case 1:
            login();
            break;

        case 2:
            signUp();
            break;

        case 3:
            printf("\nChiusura del programma...\n");
            return 0;
	
        default:
            printf("\nOpzione non valida! Riprova.\n");
            break;
    }

    return 0;
}
