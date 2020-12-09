#define _CRT_SECURE_NO_WARNINGS
#include "Game.h"
#include <stdio.h>
Game InitGame(unsigned int size)
{
	Game gme;
	gme.numberOfTurns = 0;
	gme.currentTurn = 'X';
	gme.currentBoard = (Board*)malloc(sizeof(Board));
	gme.currentBoard->maxSize = size;
	gme.currentBoard->pieces = (Slot*)malloc(sizeof(Slot) * gme.currentBoard->maxSize * gme.currentBoard->maxSize);
	gme.memory = (Collection*)malloc(sizeof(Collection));
	gme.memory->boards = (Board*)malloc(sizeof(Board) * gme.currentBoard->maxSize * gme.currentBoard->maxSize);
	gme.memory->spot = 0;
	FillEmpty(gme.currentBoard);
	return gme;
}
void Welcome()
{
	printf("*** Welcome to AVOIDANCE TIC-TAC-TOE game ***\n\n");
}
int main() 
{
	Game gme;
	Welcome();
	do
	{
		printf("Please enter board size (1 to 11):\n");
	}

	//int* array;
	//array = (int*)malloc(sizeof(int) * 3);
	//array = (int*)realloc(array, sizeof(int) * 5);
	
	
	int i = 0, counter = 0, j = 0, k = 0;
	Capsule answer;
	
	PrintBoard(&gme);
	putchar('\n');
	Slot sltTemp;
	for (int h = 0; h < 8; h++)
	{
		printf("Enter Choice for %c \n", gme.currentTurn);
		scanf("%d %d", &sltTemp.row, &sltTemp.column);
		sltTemp.type = gme.currentTurn;
		AddTurn(&gme, sltTemp);
		PrintBoard(&gme);
		putchar('\n');
		answer = ValidateBoard(gme.currentBoard);
		if (answer.end == true)
		{
			printf("%c won!!\n", answer.winner);
			break;
		}
	}
	
	
	putchar('\n');
	putchar('$');
	putchar('\n');
	for (k = 0; k < gme.memory->spot; k++)
	{
		//PrintBoard(gme.memory->boards[i]);
		counter = 0;
		for (i = 0; i < gme.memory->boards[k].maxSize; i++)
		{

			//printf("|");
			putchar('|');
			for (j = 0; j < gme.memory->boards[k].maxSize; j++)
			{
				putchar(gme.memory->boards[k].pieces[counter].type);
				//printf("%c", gme->currentBoard->pieces[i].type);
				putchar('|');
				counter++;
			}
			putchar('\n');
		}
		putchar('\n');
	}
	LoadBoardFromMemory(&gme, 1);
	PrintBoard(&gme);
	for ( i = gme.memory->spot; i > 0; i--)
	{
		free(gme.memory->boards[i-1].pieces);
	}
	free(gme.currentBoard->pieces);
	//free(gme.currentBoard);
	free(gme.memory->boards);
	free(gme.memory);

		
	return 0;
}