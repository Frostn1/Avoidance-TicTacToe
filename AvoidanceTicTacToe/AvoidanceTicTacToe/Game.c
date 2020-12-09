#include "Game.h"
#include <stdio.h>

void LoadBoardFromMemory(Game* gme, int amount)
{
	if (amount >= gme->memory->boards->spot)
		return;

	
	gme->currentBoard = &gme->memory->boards[gme->memory->spot - amount];
	gme->numberOfTurns -= amount;
	if (gme->currentTurn == 'X')
		gme->currentTurn = 'O';
	else
		gme->currentTurn = 'X';
	
}

void PrintBoard(Game* gme)
{
	int i = 0, j = 0, counter = 0;
	
	for (i = 0; i < gme->currentBoard->maxSize; i++)
	{

		//printf("|");
		putchar('|');
		for (j = 0; j < gme->currentBoard->maxSize; j++)
		{
			putchar(gme->currentBoard->pieces[counter].type);
			//printf("%c", gme->currentBoard->pieces[i].type);
			putchar('|');
			counter++;
		}
		putchar('\n');
	}
	
}


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