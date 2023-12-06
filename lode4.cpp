// lode4.cpp : Defines the entry point for the application.
//

#include "lode4.h"
#include "game.h"
#include "board.h"
#include "battleship.h"


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main() {
    srand(time(NULL));

    printf("Vitajte v hre lode!\n");

    while (1) {
        printf("Vyberte si herny mod:\n");
        printf("1. Single-player\n");
        printf("2. Multi-player\n");
        printf("3. Koniec\n");

        int choice;
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            singlePlayerGame();
            break;
        case 2:
            multiPlayerGame();
            break;
        case 3:
            printf("Ahoj!\n");
            return 0;
        default:
            printf("Neplatny vyber. Zadajte cisla 1, 2 alebo 3.\n");
        }
    }

    return 0;
}
