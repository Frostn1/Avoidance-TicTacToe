#ifndef GAME_H
#define GAME_H

#include <stdint.h>

#include "Collection.h"
#include "WhiteMarker.h"
#include "Board.h"

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
void PrintBoard(Game* gme, uint8_t style, uint8_t padding, uint16_t xcord, uint16_t ycord);
void AddTurn(Game* gme, Slot slt);
void freeGame(Game* gme);


// Styling
void printPadding(int gameSize, uint8_t padding);

#endif // !GAME_H


