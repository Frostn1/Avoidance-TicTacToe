#ifndef GAME_H
#define GAME_H
#include "Collection.h"
typedef struct Game
{
	Collection* memory;
	Board* currentBoard;
	char currentTurn;
	int numberOfTurns;
}Game;

void LoadBoardFromMemory(Game* gme, int amount);
void PrintBoard(Game* gme);
void AddTurn(Game* gme, Slot slt);

#endif // !GAME_H


