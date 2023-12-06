// game.cpp
#include "game.h"
#include "board.h"
#include "battleship.h"
#include <stdio.h>

void singlePlayerGame() {
    char playerBoard[BOARD_SIZE][BOARD_SIZE];
    char computerBoard[BOARD_SIZE][BOARD_SIZE];

    // Nastavenie hernych dosiek
    initializeBoard(playerBoard);
    initializeBoard(computerBoard);

    // Umiestnenie lodi pocitaca
    srand(time(NULL));
    Ship computerShips[] = { {{0, 0}, {0, 2}},
                            {{3, 5}, {6, 5}},
                            {{9, 9}, {9, 9}} };

    for (int i = 0; i < sizeof(computerShips) / sizeof(computerShips[0]); i++) {
        placeShip(computerBoard, computerShips[i]);
    }

    // Umiestnenie lodi hraca
    printf("Umiestni svoje lode na plochu.\n");
    Ship playerShips[] = { {{0, 0}, {0, 2}},
                          {{3, 5}, {6, 5}},
                          {{9, 9}, {9, 9}} };

    for (int i = 0; i < sizeof(playerShips) / sizeof(playerShips[0]); i++) {
        printPlayerBoard(playerBoard, 0);
        printf("Zadaj suradnice pre lod: %d (zaciatocny riadok, zaciatocny stlpec, konecny riadok, konecny stlpec): ", i + 1);
        scanf_s("%d %d %d %d", &playerShips[i].start.row, &playerShips[i].start.col,
            &playerShips[i].end.row, &playerShips[i].end.col);

        placeShip(playerBoard, playerShips[i]);
    }

    //loop
    int playerTurn = 1;
    while (1) {
        if (playerTurn) {
            // Hracov tah
            printf("Tvoj tah!\n");
            printComputerBoard(computerBoard, 1);

            Coordinate shot;
            printf("Zadaj svoj tip (riadok a stlpec): ");
            scanf_s("%d %d", &shot.row, &shot.col);

            if (!isValidShot(computerBoard, shot)) {
                printf("Neplatny tip. Skus znovu\n");
                continue;
            }

            updateBoard(computerBoard, shot);

            // Kontrola, ci su vsetky lode pocitaca potopene
            int shipsRemaining = 0;
            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    if (computerBoard[i][j] == SHIP) {
                        shipsRemaining = 1;
                        break;
                    }
                }
                if (shipsRemaining) {
                    break;
                }
            }

            if (!shipsRemaining) {
                printf("Gratulujem, potopil si vsetky lode pocitaca a vyhravas.\n");
                break;
            }
        }
        else {
            // Tah pocitacu
            printf("Tah pocitaca!\n");

            Coordinate shot;
            do {
                shot.row = rand() % BOARD_SIZE;
                shot.col = rand() % BOARD_SIZE;
            } while (!isValidShot(playerBoard, shot));

            updateBoard(playerBoard, shot);

            // Kontrola, ci su vsetky lode hraca potopene
            int shipsRemaining = 0;
            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    if (playerBoard[i][j] == SHIP) {
                        shipsRemaining = 1;
                        break;
                    }
                }
                if (shipsRemaining) {
                    break;
                }
            }

            if (!shipsRemaining) {
                printf("Prepacte, pocitac potopil vsetky vase lode. Vela stastia nabuduce!\n");
                break;
            }
        }

        playerTurn =!playerTurn; // Prepnutie tahu
    }
}

void multiPlayerGame() {
    char player1Board[BOARD_SIZE][BOARD_SIZE];
    char player2Board[BOARD_SIZE][BOARD_SIZE];

    initializeBoard(player1Board);
    initializeBoard(player2Board);

    // Umiestnenie lodi oboch hracov
    printf("Hrac 1, umiestni svoje lode na plochu.\n");
    Ship player1Ships[] = { {{0, 0}, {0, 2}},
                           {{3, 5}, {6, 5}},
                           {{9, 9}, {9, 9}} };

    for (int i = 0; i < sizeof(player1Ships) / sizeof(player1Ships[0]); i++) {
        printPlayerBoard(player1Board, 0);
        printf("Zadaj suradnice pre lod: %d (zaciatocny riadok, zaciatocny stlpec, konecny riadok, konecny stlpec): ", i + 1);
        scanf_s("%d %d %d %d", &player1Ships[i].start.row, &player1Ships[i].start.col,
            &player1Ships[i].end.row, &player1Ships[i].end.col);

        placeShip(player1Board, player1Ships[i]);
    }

    printf("Hrac 2, umiestni svoje lode na plochu.\n");
    Ship player2Ships[] = { {{0, 0}, {0, 2}},
                           {{3, 5}, {6, 5}},
                           {{9, 9}, {9, 9}} };

    for (int i = 0; i < sizeof(player2Ships) / sizeof(player2Ships[0]); i++) {
        printPlayerBoard(player2Board, 0);
        printf("Zadaj suradnice pre lod: %d (zaciatocny riadok, zaciatocny stlpec, konecny riadok, konecny stlpec): ", i + 1);
        scanf_s("%d %d %d %d", &player2Ships[i].start.row, &player2Ships[i].start.col,
            &player2Ships[i].end.row, &player2Ships[i].end.col);

        placeShip(player2Board, player2Ships[i]);
    }

    //loop
    int playerTurn = 1;
    while (1) {
        if (playerTurn) {
            // Tah hraca 1
            printf("Tah Hraca 1!\n");
            printPlayerBoard(player2Board, 1);

            Coordinate shot;
            printf("Zadaj svoj tip (riadok a stlpec): ");
            scanf_s("%d %d", &shot.row, &shot.col);

            if (!isValidShot(player2Board, shot)) {
                printf("Neplatny tip. Skus znova.\n");
                continue;
            }

            updateBoard(player2Board, shot);

            // Kontrola, ci su vsetky lode hraca 2 potopene
            int shipsRemaining = 0;
            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    if (player2Board[i][j] == SHIP) {
                        shipsRemaining = 1;
                        break;
                    }
                }
                if (shipsRemaining) {
                    break;
                }
            }

            if (!shipsRemaining) {
                printf("Vyhrava Hrac 1! Vsetky lode Hraca 2 su potopene.\n");
                break;
            }
        }
        else {
            // tah hraca 2
            printf("Tah Hraca 2!\n");
            printPlayerBoard(player1Board, 1);

            Coordinate shot;
            printf("Zadaj svoj tip (riadok a stlpec): ");
            scanf_s("%d %d", &shot.row, &shot.col);

            if (!isValidShot(player1Board, shot)) {
                printf("Neplatny tip. Skus znova.\n");
                continue;
            }

            updateBoard(player1Board, shot);

            // Kontrola, ci su vsetky lode hraca 1 potopene
            int shipsRemaining = 0;
            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    if (player1Board[i][j] == SHIP) {
                        shipsRemaining = 1;
                        break;
                    }
                }
                if (shipsRemaining) {
                    break;
                }
            }

            if (!shipsRemaining) {
                printf("Vyhrava Hrac 2! Vsetky lode Hraca 1 su potopene.\n");
                break;
            }
        }

        playerTurn =! playerTurn; // vymena tahu
    }
}
