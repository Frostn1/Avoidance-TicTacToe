#define _CRT_SECURE_NO_WARNINGS
#include "Game.h"
#include <stdio.h>
Game InitGame(unsigned int size)
{
	Game gme;
	gme.numberOfTurns = 0;
	gme.currentTurn = 'X';
	gme.currentPlayer = 1;
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
void DoTurn(Game* gameTemp, Slot* slt)
{
	if (slt->row < 0)
	{
		LoadBoardFromMemory(gameTemp, slt->row * (-1));
		return;
	}
	else
	{
		slt->type = gameTemp->currentTurn;
		AddTurn(gameTemp, *slt);
		return;
	}
	if (gameTemp->currentPlayer == 1)
		gameTemp->currentPlayer = 2;
	else
		gameTemp->currentPlayer = 1;
}

bool CheckSpot(Game* gme,Slot tmp)
{
	if (tmp.row > gme->currentBoard->maxSize || tmp.column > gme->currentBoard->maxSize || tmp.row < 0 && tmp.row * (-1) > gme->memory->spot)
	{
		printf("Illegal move!!!\n");
		return true;
	}
	else if (!(tmp.row < 0 && tmp.row * (-1) > gme->memory->spot))
	{
		return false;
	}
	else if (gme->currentBoard->pieces[tmp.row * 3 - 3 + tmp.column-1].type != '_')
	{
		printf("Illegal move!!!\n");
		return true;
	}
}
void MoveInput(Game* gme)
{
	Slot sltTemp;
	do
	{
		printf("Player ** %d **, enter next move:\n", gme->currentPlayer);
		scanf("%d %d", &sltTemp.row, &sltTemp.column);
	} while (sltTemp.row > gme->currentBoard->maxSize || sltTemp.column > gme->currentBoard->maxSize || sltTemp.row < 0 && sltTemp.row * (-1) > gme->memory->spot || CheckSpot(gme,sltTemp) == true);
	DoTurn(gme, &sltTemp);
	putchar('\n');
}
void MainLoop(Game* gme)
{
	Capsule answer;
	
	while (true)
	{	
		printf("Current Board:\n");
		PrintBoard(gme);
		putchar('\n');
		answer = ValidateBoard(gme->currentBoard);
		if (answer.end == true)
		{
			printf("Player %d Wins! Hooray!\n", answer.winner);
			break;
		}
		MoveInput(gme);
		

	}
}

void freeGame(Game* gme)
{
	for (int i = gme->memory->spot; i > 0; i--)
	{
		free(gme->memory->boards[i - 1].pieces);
	}
	//free(gme->currentBoard->pieces);
	//free(gme.currentBoard);
	free(gme->memory->boards);
	free(gme->memory);
}
int main() 
{
	Game gme;
	int boardSize;
	Welcome();
	do
	{
		printf("Please enter board size (1 to 11):\n");
		scanf("%d", &boardSize);
	} while (boardSize < 1 || boardSize > 11);
	putchar('\n');
	gme = InitGame(boardSize);
	MainLoop(&gme);
	freeGame(&gme);
	//int* array;
	//array = (int*)malloc(sizeof(int) * 3);
	//array = (int*)realloc(array, sizeof(int) * 5);
	
	/*
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
	*/
		
	return 0;
}