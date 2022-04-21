#define _CRT_SECURE_NO_WARNINGS

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "Game.h"
#include "WhiteMarker.h"

#define DOWN_ARROW 0x50
#define UP_ARROW 0x48
#define LEFT_ARROW 0x4B
#define RIGHT_ARROW 0x4D
#define ENTER 0x0D

#define INVALID_ASCII -32

#define WELCOME_STRING "*** AVOIDANCE TIC-TAC-TOE ***\n\n"
#define SETTINGS_STRING "*** Settings ***\n\n"
#define OPTION_START 0
#define OPTION_LOAD 1
#define OPTION_HELP 2
#define OPTION_SETTINGS 3
#define OPTION_EXIT 4

#define UNI_PAD 10
#define SCREEN_SIZE 80

void StartGame();
void SettingsMenu();
void PrintOptions(char* title, uint8_t choice, char options[][50], int len, int screenWidth);
uint8_t Welcome();
void DoTurn(Game* gameTemp, Slot* slt);
bool CheckSpot(Game* gme, Slot tmp);
Slot MoveInput(Game* gme, uint8_t style, uint8_t padding, uint16_t prex, uint16_t prey);
void MainLoop(Game* gme);


#endif // !CONTROLLER_H
