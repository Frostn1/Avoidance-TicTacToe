#ifndef BOARD_H
#define BOARD_H

#include "Slot.h"
#include <stdbool.h>

#define EMPTYSLOT '_'



typedef struct Board
{
	Slot* pieces;
	int maxSize;
	

}Board;

typedef struct Capsule
{
	bool end;
	int winner;
}Capsule;
 
void PushSlot(Board* brd, Slot slt);
void FillEmpty(Board* brd);
Capsule ValidateBoard(Board* brd);

#endif // !BOARD_H



