#include "Collection.h"

/*
Saving a new board onto the collection, and transfering all of the data from a board ,onto a board inside of the board array of the collection
*/
void PushBoard(Collection* clt, Board brd)
{
	//clt->boards[clt->spot++] = brd;
	clt->boards[clt->spot].pieces = (Slot*)malloc(sizeof(Slot) * brd.maxSize * brd.maxSize);
	clt->boards[clt->spot].maxSize = brd.maxSize;
	int i = 0;
	for ( i = 0; i < brd.maxSize * brd.maxSize; i++)
	{
		clt->boards[clt->spot].pieces[i] = brd.pieces[i];
	}
	clt->spot++;
}








