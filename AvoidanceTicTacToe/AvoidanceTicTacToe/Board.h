#ifndef BOARD_H
#define BOARD_H

#include "Slot.h"

#define EMPTYSLOT '_'
typedef struct Board
{
	Slot* pieces;
	int maxSize;
	int spot;

}Board;
 
void PushSlot(Board* brd, Slot slt);
void FillEmpty(Board* brd);
#endif // !BOARD_H



