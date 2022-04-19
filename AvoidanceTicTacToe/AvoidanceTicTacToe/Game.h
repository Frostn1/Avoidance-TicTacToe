#ifndef GAME_H
#define GAME_H

#include "Collection.h"
#include <stdint.h>
#define MAX_BOARD_SIZE 11
#define MIN_BOARD_SIZE 1
#define BOXED_STYLE 0x01
#define CROSSED_STYLE 0x02
typedef struct Game {
	Collection* memory;
	Board* currentBoard;
	char currentTurn;
	int numberOfTurns;
	int currentPlayer;
}Game;

void LoadBoardFromMemory(Game* gme, int amount);
void PrintBoard(Game* gme, uint8_t style, uint8_t padding);
void AddTurn(Game* gme, Slot slt);
void freeGame(Game* gme);


// Styling
void printPadding(int gameSize, uint8_t padding);

#endif // !GAME_H


