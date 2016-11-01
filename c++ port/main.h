#pragma once

typedef uint8_t Uint8;

typedef enum {
    NORMAL, GAMEOVER, SCORE
} GAME_STATE;
extern GAME_STATE gameState;

const int SCREEN_WIDTH = 256;
const int SCREEN_HEIGHT = 256;
extern const Uint8* keyboardState;

void exitApp(int exitCode);
