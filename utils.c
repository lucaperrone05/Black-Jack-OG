// Utility varie (input, stampa, ecc.)
#include <windows.h>
#include <conio.h> // Per _getch()
#include <stdio.h>
#include <string.h>
#include "user.h"
#include "db.h"


void getPassword(char* password, int maxLength) {
    HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    char ch;
    int i = 0;

    // Disattiva l'echo e l'input bufferizzato
    GetConsoleMode(hConsole, &mode);
    SetConsoleMode(hConsole, mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));

    while (i < maxLength - 1) {
        ch = _getch(); // Legge un carattere senza mostrarlo

        if (ch == '\r') {
            // Invio → termina input
            break;
        }
        else if (ch == 8) {
            // Backspace
            if (i > 0) {
                i--;
                printf("\b \b"); // Cancella un asterisco
            }
        }
        else if (ch >= 32 && ch <= 126) {
            // Carattere stampabile
            password[i++] = ch;
            printf("*"); // Mostra un asterisco subito
        }
        // Altri caratteri (es. frecce) vengono ignorati
    }

    password[i] = '\0'; // Chiude la stringa
    SetConsoleMode(hConsole, mode); // Ripristina modalità normale
    printf("\n");
}


void printCentered(const char* message) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;

    GetConsoleScreenBufferInfo(hConsole, &csbi);
    columns = csbi.dwSize.X;

    int position = (columns - strlen(message)) / 2;

    COORD coord = { position, csbi.dwCursorPosition.Y };
    SetConsoleCursorPosition(hConsole, coord);

    printf("%s\n", message);
}


void getScelta(int* menu) {
    printf("\nScelta: ");

    if (scanf("%d", menu) != 1) {
        menu = -1; // forza default
    }

    // svuota completamente il buffer
    while (getchar() != '\n');

}