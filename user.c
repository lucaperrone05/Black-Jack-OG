#include <windows.h>
#include <conio.h> // Per _getch()
#include <stdio.h>
#include <string.h>
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
void login() {
    
    sqlite3* db;
    apriDatabase(&db);
    int temp;

    do{
        system("cls");
        printCentered("Login\n\n");

        char username[20], password[20];

        printf("Username: ");
        fgets(username, sizeof(username), stdin);
        username[strcspn(username, "\n")] = 0;

        printf("Password: ");
        getPassword(password, sizeof(password));
        
        temp = loginDb(db, username, password); 

    } while (temp == 0);
    
	sqlite3_close(db);

}


// Funzione Sign Up
void signUp() {
    char nome[20], cognome[20], username[20], password[20], ripeti_password[20];
    sqlite3* db;
    apriDatabase(&db);

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
        Sleep(2000);
    }
    else if (strlen(password) < 8) {
        printf("\nErrore: la password deve essere lunga almeno 8 caratteri.\n");
        Sleep(3000);
    }
    else {
        registraUtente(db, nome, cognome, username, password);
        Sleep(3000);

		login(); // Reindirizza alla funzione di login dopo la registrazione
    }

    sqlite3_close(db);
}
