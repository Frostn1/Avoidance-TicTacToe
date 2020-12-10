#include "Game.h"
#include <stdio.h>
/*
Function that loades a board from the memory of the game
*/
void LoadBoardFromMemory(Game* gme, int amount)
{
	if (amount > gme->memory->spot)
		return;

	
	gme->currentBoard = &gme->memory->boards[gme->memory->spot - amount];
	gme->numberOfTurns -= amount;
	gme->memory->spot -= amount;
	if (gme->currentTurn == 'X')
		gme->currentTurn = 'O';
	else
		gme->currentTurn = 'X';
	
}
/*
Function that prints the current board in the game
*/
void PrintBoard(Game* gme)
{
	int i = 0, j = 0, counter = 0;
	
	for (i = 0; i < gme->currentBoard->maxSize; i++)
	{
		putchar('|');
		for (j = 0; j < gme->currentBoard->maxSize; j++)
		{
			putchar(gme->currentBoard->pieces[counter].type);
			putchar('|');
			counter++;
		}
		putchar('\n');
	}
	
}

/*
The turn cycle function of the game, saving the current board and adding the new slot to the current one
*/
void AddTurn(Game* gme, Slot slt)
{
	PushBoard(gme->memory, *gme->currentBoard);
	PushSlot(gme->currentBoard, slt);
	gme->numberOfTurns++;
	if (gme->currentTurn == 'X')
		gme->currentTurn = 'O';
	else
		gme->currentTurn = 'X';
}