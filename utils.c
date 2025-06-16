// Utility varie (input, stampa, ecc.)
#include <windows.h>
#include <conio.h> // Per _getch()
#include <stdio.h>
#include <string.h>
#include "user.h"
#include "db.h"
#include "deck.h"


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

void printMenuLogin() {
    printCentered("Gioca a BlackJack!\n\n");

    printf("Selezionare un'opzione:");

    printCentered("1. Login\n");
    printCentered("2. Sign Up\n");
    printCentered("3. Exit\n");
}

void printMenuScelta(char* username, int saldo) {
    
    system("cls");
    printCentered("Benvenuto nel gioco di BlackJack!\n\n");
    printf("Username: %s\n", username);
    printf("Saldo: %d\n", saldo);
    printf("\n\n");

    printCentered("Selezionare un'opzione:\n\n");
    printCentered("1. Nuova partita\n");
    printCentered("2. Carica partita\n");
    printCentered("3. Visualizza storico partite\n");
    printCentered("4. Exit\n");
}

void printChiusuraProgramma() {
    system("cls");
    printf("\n\n\n");
    printCentered("Chiusura del programma...");
    printf("\n\n\n");
}

void printOpzioneNonValida() {
    printf("\nOpzione non valida!\n");
    Sleep(1500);
    system("cls"); // Pulisce lo schermo
}

void printUsernameSaldo(Utente utente) {
    printCentered("BlackJack");
    printf("%s\nSaldo:%d\n\n", utente.username, utente.saldo);
}

void printMescolamento() {
	printf("\n\n");
    printCentered("Procedo al mescolamento delle carte . . .");
    Sleep(2000); // Attendi 2 secondi per dare tempo di leggere il messaggio
    system("cls"); // Pulisci la console
}

void manoIniziale(Utente utente ,Carta** mazzo, Carta** cartaEstratta, Carta manoBanco[], Carta manoGiocatore[]) {
    
	printUsernameSaldo(utente);

    printf("       Banco:\n");
    
    for (int i = 0; i < 2; i++) {
        *cartaEstratta = pop(mazzo);
        manoBanco[i] = **cartaEstratta;  // copia il contenuto della struttura
    }
    stampaCarteAffiancateConCoperta(manoBanco, 2);

    printf("\n       Giocatore:\n");

    for (int i = 0; i < 2; i++) {
        *cartaEstratta = pop(mazzo);
        manoGiocatore[i] = **cartaEstratta;  // copia il contenuto della struttura
    }
    stampaCarteAffiancate(manoGiocatore, 2);
}

void risultato(Utente* utente, int punteggioBanco, int punteggioGiocatore, int puntata) {
    if (punteggioBanco > punteggioGiocatore && punteggioBanco <= 21) {
        printCentered("Ha vinto il banco!");
    }
    else if (punteggioGiocatore > punteggioBanco && punteggioGiocatore <= 21) {
        printCentered("Hai vinto tu!");
        utente->saldo += puntata * 2; // Il giocatore vince la puntata
    }
    else if (punteggioGiocatore > 21 && punteggioBanco <= 21) {
        printCentered("Hai sballato. Vince il banco!");
    }
    else if (punteggioBanco > 21 && punteggioGiocatore <= 21) {
        printCentered("Il banco ha sballato. Hai vinto tu!");
        utente->saldo += puntata * 2;
    }
    else {
        printCentered("Avete pareggiato!");
        utente->saldo += puntata; // Recupera la puntata
    }
}

void printCarteBancoGiocatore(Utente* utente, int punteggioBanco, int punteggioGiocatore, int puntata, Carta manoBanco[], Carta manoGiocatore[], int offsetBanco, int offsetGiocatore, int finale) {   

    system("cls");

    printUsernameSaldo(*utente);

    printf("       Banco:\n");
    stampaCarteAffiancate(manoBanco, offsetBanco);

    if (finale==1) {
        risultato(utente, punteggioBanco, punteggioGiocatore, puntata);
    }

    printf("\n       Giocatore:\n");
    stampaCarteAffiancate(manoGiocatore, offsetGiocatore);
}

int getPuntata(Utente* utente) {
    
    int puntata;
    int exit;
    
    do {
        puntata = 0;
        exit = 1;

        printUsernameSaldo(*utente);

        printf("\n\n");
        printCentered("Inserire puntata: ");

        printf("\n");
        printCentered("Puntate disponibili:");

		printf("\n");
        printCentered(" ______    ______    ______    _______    _______");
        printCentered("|      |  |      |  |      |  |       |  |       |");
        printCentered("|  10  |  |  20  |  |  50  |  |  100  |  |  200  |");
        printCentered("|______|  |______|  |______|  |_______|  |_______|");
        printf("\n");

        getScelta(&puntata);

        if (puntata <= utente->saldo) {

			switch (puntata) {  // Controlla se la puntata è valida
            case 10:
            case 20:
            case 50:
            case 100:
            case 200:
				exit = 1; // Puntata valida, esci dal ciclo
                break;
            default:
                printCentered("\nPuntata non valida");
                Sleep(1500);
                system("cls");
                exit = 0;
                break;
            }
        }
        else {
            exit = 0;
			printCentered("\nPuntata superiore al saldo disponibile.\n");
            Sleep(1500);
            system("cls");
        }

    } while (exit==0);

    utente->saldo -= puntata; // Sottrae la puntata dal saldo dell'utente

    system("cls");

	return puntata;
}

void printMenuGiocatore() {
    printf("\n\n");
    printCentered("Inserisci:");
    printf("\n");
    printCentered("1. Carta      2. Stai      3. Raddoppio      4. Split");
}

int continuaPartita(Utente* utente) {
    char risposta;
	int scelta = -1;

    do {
		Sleep(2000);
		system("cls");
		printUsernameSaldo(*utente);
        printf("\n\n\n");
        printCentered("Vuoi continuare la partita?");
        printf("\n(S/N): ");
        scanf("%c", &risposta);  // Spazio prima di %c per ignorare newline precedenti
		while (getchar() != '\n'); // Svuota il buffer di input

        if (risposta == 's' || risposta == 'S') {
            scelta = 1;
        }
        else if (risposta == 'n' || risposta == 'N') {
            scelta = 0;
        }
        else {
			system("cls");
            printf("\n\n\n");
            printCentered("Input non valido. Inserisci 'S' per si o 'N' per no.\n");
        }
	} while (scelta == -1);
    
	system("cls");
    return scelta;
}