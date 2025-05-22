#include <windows.h>
#include <conio.h> // Per _getch()
#include <stdio.h>
#include <string.h>
#include "user.h"
#include "db.h"


// Funzione per nascondere password con pallini
void getPassword(char* password, int maxLength) {
    HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    char ch;
    int i = 0;

    // Disabilita l'echo dei caratteri
    GetConsoleMode(hConsole, &mode);
    SetConsoleMode(hConsole, mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));

    while (i < maxLength - 1) {
        ch = _getch(); // Legge un carattere senza mostrarlo

        if (ch == '\r') break; // Termina con "Invio"

        password[i++] = ch;
        printf("*"); // Mostra pallino invece del carattere
    }

    password[i] = '\0'; // Chiude la stringa

    // Riabilita l'echo dei caratteri
    SetConsoleMode(hConsole, mode);
    printf("\n");
}


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
    
	sqlite3_close(db);

}


// Funzione Sign Up
void signUp(Utente* utente) {
    char nome[20], cognome[20], username[20], password[20], ripeti_password[20];
	int flag = 0;
    
    sqlite3* db;
    apriDatabase(&db);


    do{
        system("cls");
        printCentered("Sign Up\n\n");

        creaTabellaUser(db); // Crea la tabella se non esiste

        printf("Nome: ");
        fgets(nome, sizeof(nome), stdin);
        nome[strcspn(nome, "\n")] = 0;

        printf("Cognome: ");
        fgets(cognome, sizeof(cognome), stdin);
        cognome[strcspn(cognome, "\n")] = 0;

        printf("Username: ");
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = 0;

        printf("Password: ");
        getPassword(password, sizeof(password));

        printf("Ripetere la password: ");
        getPassword(ripeti_password, sizeof(ripeti_password));

        if (strcmp(password, ripeti_password) != 0) {
            printf("\nErrore: le password non corrispondono.\n");
			flag = 1;
            Sleep(2000);
        }
        else if (strlen(password) < 6) {
            printf("\nErrore: la password deve essere lunga almeno 6 caratteri.\n");
			flag = 1;
            Sleep(2500);
        }

    }while (flag == 1);
        
    
    registraUtente(db, nome, cognome, username, password);
		
    system("cls");
	printf("\n\n\n");
    printCentered("Registrazione completata con successo!\n\n");
    printCentered("4000 gettoni bonus per te!");
    Sleep(2500);

    login(utente); // Reindirizza alla funzione di login dopo la registrazione

}
