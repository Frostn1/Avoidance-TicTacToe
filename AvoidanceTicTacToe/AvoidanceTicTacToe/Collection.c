#include "Collection.h"

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








