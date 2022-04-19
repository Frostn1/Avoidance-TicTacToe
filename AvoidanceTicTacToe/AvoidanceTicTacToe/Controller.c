#include "Controller.h"




void StartGame() {
	Game gme;
	int boardSize;
	do {
		printf("Please enter board size (%d to %d):\n", MIN_BOARD_SIZE, MAX_BOARD_SIZE);
		scanf("%d", &boardSize);
	} while (boardSize < MIN_BOARD_SIZE || boardSize > MAX_BOARD_SIZE);
	putchar('\n');
	gme = InitGame(boardSize);
	MainLoop(&gme);
	freeGame(&gme);
}





/*
Init function of a game struct, by getting a size of the board and allocating all of the memory
*/
Game InitGame(unsigned int size) {
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


void PrintOptions(uint8_t choice, char options[][50], int len) {
	int width = strlen(WELCOME_STRING), length = 0, pad = 0;
	//char options[][50] = { "Start Game", "Load Game", "Help", "Exit" };

	for (size_t i = 0; i < sizeof(options); i++) {
		//printf("%.%d", 4, "");
		length = strlen(options[i]);  // Discount the terminal '\0'
		pad = (length >= width) ? 0 : (width - length) / 2;
		if (i == choice) {
			_c(ITALIC);
			_c(BOLD);
		}
			
		printf("%*.*s%s\n", pad, pad, " ", options[i]);
		if (i == choice) {
			_c(RESET_ITALIC);
			_c(RESET_BOLD);
		}
			
		//printf("%*s%s\n",4 + (strlen(WELCOME_STRING)/2 + 4 - strlen(options[i])),"", options[i]);
	}
}
/*
Welcome messgae to start the game
*/
uint8_t Welcome() {
	__SETUP__();
	__CLS__();
	printf("%*s%s", 4, "",WELCOME_STRING);
	__SAVE_POS__();
	bool flag = true;
	char ch = 'a';
	uint8_t choice = 0;
	int limit = 4, width = strlen(WELCOME_STRING), length = 0, pad = 0;
	char options[][50] = { "Start Game", "Load Game", "Help", "Exit" };
	
	PrintOptions(choice, options, sizeof(options) / sizeof(*options));
	
	while (flag) {
		ch = getch();
		if(ch == INVALID_ASCII)
			ch = getch();
		//printf("%d %c", ch, ch);
		switch (ch) {
		case ENTER:
			// ENTER
			//printf("ENTER KEY is pressed.\n");
			flag = false;
			break;
		case DOWN_ARROW:
			// DOWN
			//printf("DOWN\n");
			if (choice < limit - 1) choice++;
			else choice = 0;
			
			__MOVE_POS__();
			PrintOptions(choice, options, sizeof(options) / sizeof(*options));
			break;

		case UP_ARROW:
			// UP
			if (choice) choice--;
			else choice = limit - 1;

			__MOVE_POS__();
			PrintOptions(choice, options, sizeof(options) / sizeof(*options));
			break;
		}
	}
			
	//printf("Option choosed %d\n", choice);
	return choice;
}
/*
Making the turn, either valid turn or valid undo turn
*/
void DoTurn(Game* gameTemp, Slot* slt) {
	if (gameTemp->currentPlayer == 1)
		gameTemp->currentPlayer = 2;
	else
		gameTemp->currentPlayer = 1;
	if (slt->row < 0) {
		LoadBoardFromMemory(gameTemp, slt->row * (-1));
		return;
	}
	else {
		slt->type = gameTemp->currentTurn;
		AddTurn(gameTemp, *slt);
		return;
	}

}

/*
Checking the input is valid
*/
bool CheckSpot(Game* gme, Slot tmp) {
	if (tmp.row > gme->currentBoard->maxSize || tmp.column > gme->currentBoard->maxSize || tmp.row < 0 && tmp.row * (-1) > gme->memory->spot) {
		printf("Illegal move!!!\n");
		return true;
	}
	else if (gme->currentBoard->pieces[tmp.row * gme->currentBoard->maxSize - gme->currentBoard->maxSize + tmp.column - 1].type != '_') {
		printf("Illegal move!!!\n");
		return true;
	}
	else if (!(tmp.row < 0 && tmp.row * (-1) > gme->memory->spot)) {
		return false;
	}
}
/*
Input loop for x y system of the game
*/
void MoveInput(Game* gme) {
	Slot sltTemp;
	do {
		printf("Player ** %d **, enter next move:\n", gme->currentPlayer);
		scanf("%d %d", &sltTemp.row, &sltTemp.column);
	} while (sltTemp.row > gme->currentBoard->maxSize || sltTemp.column > gme->currentBoard->maxSize || sltTemp.row < 0 && sltTemp.row * (-1) > gme->memory->spot || CheckSpot(gme, sltTemp) == true);
	DoTurn(gme, &sltTemp);
	putchar('\n');
}
/*
Main loop of the game, calls all of the other functions
*/
void MainLoop(Game* gme) {
	Capsule answer;

	while (true) {
		printf("Current Board:\n");
		PrintBoard(gme, CROSSED_STYLE,5);
		putchar('\n');
		answer = ValidateBoard(gme->currentBoard);
		if (answer.end) {
			printf("Player %d Wins! Hooray!\n", answer.winner);
			break;
		}
		MoveInput(gme);


	}
}