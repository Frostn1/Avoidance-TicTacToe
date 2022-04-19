#include "Game.h"
#include <stdio.h>
/*
Function that loades a board from the memory of the game
*/
void LoadBoardFromMemory(Game* gme, int amount) {
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
void PrintBoard(Game* gme, uint8_t style, uint8_t padding) {

	if (style & BOXED_STYLE) {
		int i = 0, j = 0, counter = 0;

		for (i = 0; i < gme->currentBoard->maxSize; i++) {
			putchar('|');
			for (j = 0; j < gme->currentBoard->maxSize; j++) {
				putchar(gme->currentBoard->pieces[counter].type);
				putchar('|');
				counter++;
			}
			putchar('\n');
		}
	} else if (style & CROSSED_STYLE) {
		int i = 0, j = 0, counter = 0;
		/*
		 x | x | x
		___|___|___
		   |   |   
		 x | x | x 
		___|___|___
		   |   |   
		 x | x | x

		
		*/
		printPadding(gme->currentBoard->maxSize, padding);
		for (i = 0; i < gme->currentBoard->maxSize; i++) {
			//putchar('|');
			
			printf("%*s", padding, "");
			for (j = 0; j < gme->currentBoard->maxSize; j++) {
				printf(" %c ", gme->currentBoard->pieces[counter].type != EMPTYSLOT ? gme->currentBoard->pieces[counter].type : SPACE);
				j < gme->currentBoard->maxSize - 1 ? putchar('|') : j;
				counter++;
			}
			putchar('\n');
			if (i < gme->currentBoard->maxSize - 1) {
				printf("%*s", padding, "");
				for (j = 0; j < gme->currentBoard->maxSize; j++) {
					printf("___");
					j < gme->currentBoard->maxSize - 1 ? putchar('|') : j;
				}
				putchar('\n');
				printPadding(gme->currentBoard->maxSize, padding);
				
			}
			
		}
		printPadding(gme->currentBoard->maxSize, padding);


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


/*
Freeing all of the memory allocated before
*/
void freeGame(Game* gme) {
	for (int i = gme->memory->spot; i > 0; i--) {
		free(gme->memory->boards[i - 1].pieces);
	}
	//free(gme->currentBoard->pieces);
	//free(gme.currentBoard);
	free(gme->memory->boards);
	free(gme->memory);
}

void printPadding(int gameSize, uint8_t padding) {
	printf("%*s", padding, "");

	for (int j = 0; j < gameSize; j++) {
		printf("   ");
		j < gameSize - 1 ? putchar('|') : j;
	}
	putchar('\n');
}
