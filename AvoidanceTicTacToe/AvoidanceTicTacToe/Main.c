#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

#include "Game.h"
#include "Controller.h"



int main() {
	uint8_t optionSelected;
	while (true) {
		optionSelected = Welcome();
		if (optionSelected == OPTION_EXIT) return 0;
		else if (optionSelected == OPTION_START) StartGame();
		else if (optionSelected == OPTION_SETTINGS) SettingsMenu();
		//else if (optionSelected == OPTION_HELP) // RUN HELP;
		

	}
	
	
		
	return 0;
}