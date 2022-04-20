#include "Board.h"



/*
Saving a slot inside of the board array
*/
void PushSlot(Board* brd, Slot slt)
{
	//Push a slot into the board
	//Push it into the correct slot 
	brd->pieces[slt.column+slt.row*brd->maxSize] = slt;
}

/*
Function that is used in the init stage and is filling the board with "empty" slots ( Check out the empty define ) 
*/
void FillEmpty(Board* brd)
{
	Slot tempSlot;
	tempSlot.column = 0;
	tempSlot.row = 0;
	tempSlot.type = EMPTYSLOT;
	int i = 0, j = 0;
	for  (i = 0; i < brd->maxSize; i++) {
		for (j = 0; j < brd->maxSize; j++) {
			PushSlot(brd, tempSlot);
			tempSlot.column++;
		}
		tempSlot.column = 0;
		tempSlot.row++;
	}
}

/*
Function that validates the board and checks if there is a winner condition on the board
*/
Capsule ValidateBoard(Board* brd) {
	
	Capsule ansr;

	//Row Check
	bool rowFlag;
	char pre;
	for (int i = 0; i < brd->maxSize; i++) {
		rowFlag = true;
		pre = brd->pieces[i * brd->maxSize].type;
		for (int j = 1; j < brd->maxSize; j++) {
			if (pre == brd->pieces[j  + i * brd->maxSize].type)
				pre = brd->pieces[j  + i * brd->maxSize].type;
			else {
				rowFlag = false;
				break;
			}		
		}
		if (rowFlag && pre != '_')
		{
			if (pre != 'X')
				ansr.winner = WINNER2;
			else
				ansr.winner = WINNER1;
			ansr.end = true;
			return ansr;			
		}		
	}


	//Column Check
	bool colFlag;
	

	for (int i = 0; i < brd->maxSize; i++)
	{
		colFlag = true;
		pre = brd->pieces[i * brd->maxSize].type;
		for (int j = 1; j < brd->maxSize; j++)
		{
			if (pre == brd->pieces[i + j * brd->maxSize].type)
				pre = brd->pieces[i + j * brd->maxSize].type;
			else
			{
				colFlag = false;
				break;
			}
		}
		if (colFlag && pre != '_')
		{
			if (pre != 'X')
				ansr.winner = WINNER2;
			else
				ansr.winner = WINNER1;
			ansr.end = true;
			return ansr;
		}
	}


	//Diagonal Check
	bool diaFlag = true;
	//First Diagonal from top left to bottom right
	pre = brd->pieces[0].type;
	for (int j = 1; j < brd->maxSize; j++) {
		if (pre == brd->pieces[j * brd->maxSize + j].type)
			pre = brd->pieces[j * brd->maxSize + j].type;
		else {
			diaFlag = false;
			break;
		}
	}
	if (diaFlag && pre != '_') {
		if (pre != 'X')
			ansr.winner = WINNER2;
		else
			ansr.winner = WINNER1;
		ansr.end = true;
		return ansr;
	}
	
	//Second Diagonal from top right to bottom left
	diaFlag = true;
	pre = brd->pieces[brd->maxSize-1].type;
	for (int j = 1; j < brd->maxSize; j++) {
		if (pre == brd->pieces[j*2 + brd->maxSize-1].type)
			pre = brd->pieces[j*2 + brd->maxSize-1].type;
		else {
			diaFlag = false;
			break;
		}
	}
	if (diaFlag && pre != '_') {
		if (pre != 'X')
			ansr.winner = WINNER2;
		else
			ansr.winner = WINNER1;
		ansr.end = true;
		return ansr;
	}

	ansr.end = false;
	ansr.winner = '_';
	return ansr;
}
