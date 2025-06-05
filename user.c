#include <windows.h>
#include <conio.h> // Per _getch()
#include <stdio.h>
#include <string.h>
#include "user.h"
#include "db.h"
#include "utils.h"


// Funzione Login
void login(Utente* utente) {

    sqlite3* db;

    int temp;
    char username[20], password[20];

    apriDatabase(&db);

    do{
        system("cls");
        printCentered("Login\n\n");

        printf("Username: ");
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = 0;

        printf("Password: ");
        getPassword(password, sizeof(password));
        
        temp = loginDb(db, username, password); 

    } while (temp == 0);

    caricaUtente(db, username, utente);
	utente->loggato = 1; // Imposta lo stato di login dell'utente

	sqlite3_close(db);

    system("cls");
    printCentered("Login effettuato con successo!\n\n");
	printf("Benvenuto, %s!\n", utente->nome);
    
    Sleep(1500);
	
}


// Funzione Sign Up
void signUp(Utente* utente) {
    char nome[20], cognome[20], username[20], password[20], ripeti_password[20];
    sqlite3* db;
    apriDatabase(&db);

    creaTabellaUser(db);                   // fuori dal ciclo va bene

    int ok, inputValido;                   // 0 se errori, 1 se tutto valido
    do {
        ok = 1;                            // presupponiamo sia tutto valido
       
        do {
			inputValido = 1;               // resetta il flag di input valido
            system("cls");
            printCentered("Sign Up\n\n");
            printf("Nome: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = 0;

            printf("Cognome: ");
            fgets(cognome, sizeof(cognome), stdin);
            cognome[strcspn(cognome, "\n")] = 0;

            printf("Username: ");
            fgets(username, sizeof(username), stdin);
            username[strcspn(username, "\n")] = 0;

            if (strlen(nome) <= 2 || strlen(cognome) <= 1 || strlen(username) <= 2 || strchr(nome, ' ') || strchr(username, ' ')){
                printf("\nErrore: dati non corretti\n");
                Sleep(2000);
                inputValido = 0; // qualcosa non va
            }

		} while (inputValido==0);

        if (utenteEsiste(db, username)) {
            printf("\nErrore: username gia' utilizzato.\n");
            Sleep(2000);
            ok = 0;
        }

        if (ok) {                         // chiedi la password solo se l'username è libero
            printf("Password: ");
            getPassword(password, sizeof(password));

            printf("Ripetere la password: ");
            getPassword(ripeti_password, sizeof(ripeti_password));

            if (strcmp(password, ripeti_password) != 0) {
                printf("\nErrore: le password non corrispondono.\n");
                Sleep(2000);
                ok = 0;
            }
            else if (strlen(password) < 6) {
                printf("\nErrore: la password deve avere almeno 6 caratteri.\n");
                Sleep(2500);
                ok = 0;
            }
        }

    } while (!ok);                        // ripeti finché qualcosa non va

    /* Arrivi qui solo se tutto è valido */
    registraUtente(db, nome, cognome, username, password);
	system("cls");
    printCentered("Registrazione effettuata correttamente.\n\n");
    printCentered("Hai ricevuto 1000 monete bonus");
    Sleep(3000);
    login(utente);                        // login immediato

    sqlite3_close(db);
}
