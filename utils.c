// Utility varie (input, stampa, ecc.)
#include <windows.h>
#include <stdio.h>
#include <string.h>

void printCentered(const char *message) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;

    GetConsoleScreenBufferInfo(hConsole, &csbi);
    columns = csbi.dwSize.X;

    int position = (columns - strlen(message)) / 2;

    COORD coord = {position, csbi.dwCursorPosition.Y};
    SetConsoleCursorPosition(hConsole, coord);

    printf("%s\n", message);
}

