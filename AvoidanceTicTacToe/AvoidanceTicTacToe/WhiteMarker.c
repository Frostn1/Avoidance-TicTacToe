#include "WhiteMarker.h"


void _c(int color) {
    printf("\033[%dm", color);
}
int __SETUP__() {

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) {
        return GetLastError();
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) {
        return GetLastError();
    }

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode)) {
        return GetLastError();
    }

    return -1;
}
void __CLS__() {
    printf("\033[1;1H\033[2J");
}

// 1 for show, 0 for hide
void __CURSOR_STATE__(bool state) {
    state ? printf("\033[?25h") : printf("\033[?25l");
}

void __RGB__(uint8_t R, uint8_t G, uint8_t B) {
    printf("\033[38;2;%d;%d;%dm", R, G, B);
}


void __SAVE_POS__() {
    printf("\0337");
}

void __MOVE_POS__() {
    printf("\0338");
}


void moveCursor(int x, int y) {
    printf("\033[%d;%dH", x, y);
}

// moves cursor left n columns
void moveColumnsLeft(int n) {
    printf("\033[%dD", n);
}

// moves cursor right n columns
void moveColumnsRight(int n) {
    printf("\033[%dC", n);
}

// moves cursor down n lines
void moveLinesDown(int n) {
    printf("\033[%dB", n);
}

// moves cursor up n lines
void moveLinesUp(int n) {
    printf("\033[%dA", n);
}
