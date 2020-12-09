#ifndef COLLECTION_H
#define COLLECTION_H

#include "Board.h"

typedef struct Collection
{
	Board* boards;
	int spot;

}Collection;

void PushBoard(Collection* clt, Board brd);
#endif // !COLLECTION_H
