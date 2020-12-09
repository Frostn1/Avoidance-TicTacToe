#include "Board.h"


void PushSlot(Board* brd, Slot slt)
{
	
	brd->pieces[slt.column+slt.row*brd->maxSize-brd->maxSize-1] =  slt;
	//Push a slot into the board
	//Push it into the correct slot 
}


void FillEmpty(Board* brd)
{
	Slot tempSlot;
	tempSlot.column = 1;
	tempSlot.row = 1;
	tempSlot.type = EMPTYSLOT;
	int i = 0, j = 0;
	for  (i = 0; i < brd->maxSize; i++)
	{
		for (j = 0; j < brd->maxSize; j++)
		{
			PushSlot(brd, tempSlot);
			tempSlot.column++;
		}
		tempSlot.column = 1;
		tempSlot.row++;
	}
}
