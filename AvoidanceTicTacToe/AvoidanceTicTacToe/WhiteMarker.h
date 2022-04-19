#define _CRT_SECURE_NO_WARNINGS
#ifndef WHITEMARKER_H
#define WHITEMARKER_H

#include <stdio.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <wchar.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>

#define BOLD 1
#define RESET_BOLD 22
#define ITALIC 3
#define RESET_ITALIC 23
#define UNDERLINE 4
#define FLASHING 5
#define INVERTED 7
#define STRIKE_THROUGH 9
#define DOUBLE_UNDERLINE 21
#define DARK_GRAY 30
#define RED 31
#define LIGHT_GREEN 32
#define YELLOW 33
#define BLUE 34
#define LIGHT_PURPLE 35
#define LIGHT_BLUE 36
#define WHITE 37
#define DEFAULT 39




// Private
void _c(int color);
int __SETUP__();
void __CLS__();
void __CURSOR_STATE__(bool state);
void __RGB__(uint8_t R, uint8_t G, uint8_t B);
void __SAVE_POS__();
void __MOVE_POS__();

// Public
void moveCursor(int x, int y);

// moves cursor left n columns
void moveColumnsLeft(int n);

// moves cursor right n columns
void moveColumnsRight(int n);

// moves cursor down n lines
void moveLinesDown(int n);

// moves cursor up n lines
void moveLinesUp(int n);

#endif // !WHITEMARKER_H




