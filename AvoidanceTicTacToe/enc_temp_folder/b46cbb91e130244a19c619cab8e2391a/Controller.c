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

void SettingsMenu() {
	/*
		Settings

	Grid Style ... Crossed / Boxed
	Player Characters ... Choice
	ForeGroundColor ... Selection
	Reverse Mode On / Off
	
	*/
	// Start by printing a demo settings screen
	uint8_t choice = 0;
	char options[][50] = { "Grid Style", "Player Characters", "ForeGroundColor", "Reverse", "Exit" };
	int limit = sizeof(options) / sizeof(*options);
	bool flag = true;
	char ch = 'a';
	__CLS__();
	__SAVE_POS__();
	PrintOptions(SETTINGS_STRING, choice, options, limit, SCREEN_SIZE);
	while (flag) {
		ch = getch();
		if (ch == INVALID_ASCII)
			ch = getch();
		switch (ch) {
		case ENTER:
			// ENTER
			flag = false;
			break;
		case DOWN_ARROW:
			// DOWN
			if (choice < limit - 1) choice++;
			else choice = 0;

			__MOVE_POS__();
			PrintOptions(SETTINGS_STRING, choice, options, sizeof(options) / sizeof(*options), SCREEN_SIZE);
			break;

		case UP_ARROW:
			// UP
			if (choice) choice--;
			else choice = limit - 1;

			__MOVE_POS__();
			PrintOptions(SETTINGS_STRING, choice, options, sizeof(options) / sizeof(*options), SCREEN_SIZE);
			break;
		}
	}
	getch();

}



void PrintOptions(char* title, uint8_t choice, char options[][50], int len, int screenWidth) {
	int length = 0, pad = 0;
	//titleWidth += UNI_PAD*1.5; // Acounting for length difference
	length = strlen(title);  // Discount the terminal '\0'
	pad = (length >= screenWidth) ? 0 : (screenWidth - length) / 2;
	printf("%*.*s%s\n", pad, pad, " ", title);
	for (size_t i = 0; i < len; i++) {
		length = strlen(options[i]);  // Discount the terminal '\0'
		pad = (length >= screenWidth) ? 0 : (screenWidth - length) / 2;
		if (i == choice) {
			_c(ITALIC);
			_c(BOLD);
		}
			
		printf("%*.*s%s\n", pad, pad, " ", options[i]);
		if (i == choice) {
			_c(RESET_ITALIC);
			_c(RESET_BOLD);
		}
	}
}
/*
Welcome messgae to start the game
*/
uint8_t Welcome() {
	__SETUP__();
	__CLS__();
	__SAVE_POS__();
	bool flag = true;
	char ch = 'a';
	uint8_t choice = 0;
	char options[][50] = { "Start Game", "Load Game", "Help", "Settings", "Exit" };
	int limit = sizeof(options) / sizeof(*options), width = strlen(WELCOME_STRING), length = 0, pad = 0;
	
	PrintOptions(WELCOME_STRING,choice, options, sizeof(options) / sizeof(*options), SCREEN_SIZE);
	
	while (flag) {
		ch = getch();
		if(ch == INVALID_ASCII)
			ch = getch();
		switch (ch) {
		case ENTER:
			// ENTER
			flag = false;
			break;
		case DOWN_ARROW:
			// DOWN
			if (choice < limit - 1) choice++;
			else choice = 0;
			
			__MOVE_POS__();
			PrintOptions(WELCOME_STRING, choice, options, sizeof(options) / sizeof(*options), SCREEN_SIZE);
			break;

		case UP_ARROW:
			// UP
			if (choice) choice--;
			else choice = limit - 1;

			__MOVE_POS__();
			PrintOptions(WELCOME_STRING, choice, options, sizeof(options) / sizeof(*options), SCREEN_SIZE);
			break;
		}
	}
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
	else if (gme->currentBoard->pieces[tmp.column + tmp.row * gme->currentBoard->maxSize].type != '_') {
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
Slot MoveInput(Game* gme, uint8_t style, uint8_t padding, uint16_t prex, uint16_t prey) {

	bool flag = true;
	char ch = 'a';
	Slot sltTemp = { EMPTYSLOT,prey,prex };
	
	PrintBoard(gme, style, padding, sltTemp.row, sltTemp.column);
	while (flag || CheckSpot(gme, sltTemp)) {
		ch = getch();
		if (ch == INVALID_ASCII)
			ch = getch();
		//printf("%d %c", ch, ch);
		switch (ch) {
		case ENTER:
			// ENTER
			flag = false;
			break;
		case DOWN_ARROW:
			// RIGHT
			flag = true;
			if (sltTemp.row < gme->currentBoard->maxSize - 1) sltTemp.row++;
			else sltTemp.row = 0;
			__MOVE_POS__();
			PrintBoard(gme, style, padding, sltTemp.row, sltTemp.column);
			break;
		case UP_ARROW:
			// LEFT
			flag = true;
			if (sltTemp.row) sltTemp.row--;
			else sltTemp.row = gme->currentBoard->maxSize - 1;
			__MOVE_POS__();
			PrintBoard(gme, style, padding, sltTemp.row, sltTemp.column);
			break;
		case RIGHT_ARROW:
			// DOWN
			flag = true;
			if (sltTemp.column < gme->currentBoard->maxSize - 1) sltTemp.column++;
			else sltTemp.column = 0;
			__MOVE_POS__();
			PrintBoard(gme, style, padding, sltTemp.row, sltTemp.column);
			break;
		case LEFT_ARROW:
			// UP
			flag = true;
			if (sltTemp.column) sltTemp.column--;
			else sltTemp.column = gme->currentBoard->maxSize - 1;
			__MOVE_POS__();
			PrintBoard(gme, style, padding, sltTemp.row, sltTemp.column);
			break;
		}
	}
	return sltTemp;
}
/*
Main loop of the game, calls all of the other functions
*/
void MainLoop(Game* gme) {
	Capsule answer;
	Slot sltTemp = { EMPTYSLOT,0,0 };
	PrintBoard(gme, CROSSED_STYLE, 5, 0, 0);
	while (gme->numberOfTurns < gme->currentBoard->maxSize * gme->currentBoard->maxSize) {
		//printf("Current Board:\n");
		sltTemp = MoveInput(gme, CROSSED_STYLE, 5, sltTemp.column, sltTemp.row);
		DoTurn(gme, &sltTemp);
		putchar('\n');
		answer = ValidateBoard(gme->currentBoard);
		if (answer.end) {
			PrintBoard(gme, CROSSED_STYLE, 5, sltTemp.column, sltTemp.row);
			printf("Player %d Wins! Hooray!\n", answer.winner);
			getch();
			break;
		}
		PrintBoard(gme, CROSSED_STYLE, 5, sltTemp.column, sltTemp.row);
	}
	printf("Tie Game.\n");
	getch();
}