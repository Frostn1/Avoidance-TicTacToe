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
#define ENTER 0x0D

#define INVALID_ASCII -32

#define WELCOME_STRING "*** Welcome to AVOIDANCE TIC-TAC-TOE game ***\n\n"
#define OPTION_START 0
#define OPTION_LOAD 1
#define OPTION_HELP 2
#define OPTION_EXIT 3

void StartGame();
Game InitGame(unsigned int size);

uint8_t Welcome();
void DoTurn(Game* gameTemp, Slot* slt);
bool CheckSpot(Game* gme, Slot tmp);
void MoveInput(Game* gme);
void MainLoop(Game* gme);


#endif // !CONTROLLER_H
