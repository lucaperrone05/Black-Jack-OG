#include <windows.h>
#include <conio.h> // Per _getch()
#include <stdio.h>
#include <string.h>


// Funzione per nascondere password con pallini
void getPassword(char *password, int maxLength) {
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
    system("cls");
    printCentered("Login\n\n");

    char username[20], password[20];

    printf("Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Password: ");
    getPassword(password, sizeof(password));
}


// Funzione Sign Up
void signUp() {
    system("cls");
    printCentered("Sign Up\n\n");

    char nome[20], cognome[20], username[20], password[20], ripeti_password[20];

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
        printf("\nErrore: le password non corrispondono, riprova.\n");
    }
}

