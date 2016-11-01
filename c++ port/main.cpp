#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "main.h"
#include "entity/engine.h"
#include "assets.h"
#include "globals.h"

SDL_Window *window = NULL;
SDL_GLContext glContext;
const Uint8 *keyboardState;
GAME_STATE gameState;

Rectangle numberClips[10];
int highScoreX = 0;
int lastScoreX = 0;
int highScoreDigits[3];
int lastScoreDigits[3];

void initApp() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) > 0) {
        printf("SDL initialization failed. SDL_Error: %s\n", SDL_GetError());
        exitApp(1);
    }
    // Set OpenGL version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    // Initialize window
    window = SDL_CreateWindow("Core", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window creation failed. SDL_Error: %s\n", SDL_GetError());
        exitApp(1);
    }
    // Create gl context
    glContext = SDL_GL_CreateContext(window);
    if (glContext == NULL) {
        printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
        exitApp(1);
    }
    glewExperimental = GL_TRUE;
    // Init GLEW
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
    }
    //Use Vsync for OpenGL
    if (SDL_GL_SetSwapInterval(1) < 0) {
        printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
    }
    // Initialize OpenGL
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("Error initializing OpenGL: %s\n", gluErrorString(error));
        exitApp(1);
    }
    // Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image initialization failed. SDL_image Error: %s\n", IMG_GetError());
        exitApp(1);
    }
    //Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
        printf("SDL_mixer initialization failed. SDL_image Error: %s\n", SDL_GetError());
        exitApp(1);
    }
    Mix_AllocateChannels(2);
}

void exitApp(int exitCode) {
    // Save highScore
    char buffer[4] = {0};
    FILE * scoreFile;
    scoreFile = fopen( "assets/score.txt" , "w");
    sprintf(buffer, "%d", (int)(highScore));
    fputs(buffer, scoreFile);
    fclose(scoreFile);

    freeAssets();

    if (window != NULL) {
        SDL_DestroyWindow(window);
    }
    SDL_CloseAudio();
    IMG_Quit();
    SDL_Quit();
    exit(exitCode);
}

int getDigits(int *digits, int num) {
    digits[0] = -1;
    digits[1] = -1;
    digits[2] = -1;
    if (num < 10) {
        digits[0] = num;
        return 1;
    } else if (num < 100) {
        digits[0] = num % 10;
        digits[1] = (num + digits[0]) / 10;
        return 2;
    } else if (num < 1000){
        digits[0] = num % 10;
        digits[1] = (num - digits[0]) / 10 % 10;
        digits[2] = (num - digits[1]) / 100;
        return 3;
    } else {
        digits[0] = 9;
        digits[1] = 9;
        digits[2] = 9;
        return 3;
    }
}

int main(int, char **) {
    initApp();
    initEngine();
    loadAssets();
    keyboardState = SDL_GetKeyboardState(NULL); // Global keyboardState state pointer
    gameState = NORMAL;

    // Load highScore
    int score;
    FILE * scoreFile;
    scoreFile = fopen( "assets/score.txt" , "r");
    fscanf (scoreFile, "%d", &score);
    fclose (scoreFile);
    highScore = score;

    // Create player entity
    Uint16 player = createEntity();
    addComponent(player, TRANSFORM);
    transformList[player].x = 0;
    transformList[player].y = 0;
    addComponent(player, TEXTURE);
    textureList[player].texture = &glTextureList[PIXEL];
    addComponent(player, INPUT);

    // Set up clips for number texture
    for (int i = 0; i < 10; i++) {
        numberClips[i].width = glTextureList[NUMBERS].imageWidth / 10;
        numberClips[i].height = glTextureList[NUMBERS].imageHeight;
        numberClips[i].x = numberClips[i].width * i;
        numberClips[i].y = 0;
    }


    SDL_Event event;
    while (true) {
        SDL_PumpEvents();
        // Handle "close window" input
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                exitApp(1);
            }
        }

        switch (gameState) {

            case (NORMAL): {
                glClear(GL_COLOR_BUFFER_BIT);
                updateEngine();
                SDL_GL_SwapWindow(window);
                break;
            }

            case (GAMEOVER): {
                // Stop wave spawn
                systems[SPAWN_SYSTEM]->active = false;
                systems[EXPANSION_SYSTEM]->active = false;
                systems[GAMEOVER_SYSTEM]->active = false;
                for (int id = 0; id < MAX_ENTITY_COUNT; id++) {
                    if (status[id] && hasComponent(id, PARTICLE)) {
                        removeEntityInternal(id);
                    }
                }

                // Update highScore
                if (lastScore > highScore) {
                    highScore = lastScore;
                }

                // Set up score variables for drawing
                int highScoreSize = getDigits(&highScoreDigits[0], (int)highScore);
                if (highScoreSize == 1) {
                    highScoreX = (int) (SCREEN_WIDTH / 2 - numberClips->width / 2);
                } else if (highScoreSize == 2){
                    highScoreX = SCREEN_WIDTH / 2;
                } else {
                    highScoreX = (int) (SCREEN_WIDTH / 2 + numberClips->width / 2 + 10);
                }
                int lastScoreSize = getDigits(&lastScoreDigits[0], (int)lastScore);
                if (lastScoreSize == 1) {
                    lastScoreX = (int) (SCREEN_WIDTH / 2 - numberClips->width / 2);
                } else if (lastScoreSize == 2){
                    lastScoreX = SCREEN_WIDTH / 2;
                } else {
                    lastScoreX = (int) (SCREEN_WIDTH / 2 + numberClips->width / 2 + 10);
                }

                gameState = SCORE;
                break;
            }

            case (SCORE): {
                glClear(GL_COLOR_BUFFER_BIT);
                updateEngine();

                // Draw scores
                int y = SCREEN_HEIGHT / 2 - glTextureList[NUMBERS].imageHeight;
                int i = 0;
                while (highScoreDigits[i] != -1 && i < 3) {
                    GLTexture::textureProgram->modelViewMatrix = glm::mat4();
                    glTextureList[NUMBERS].render(highScoreX - i * (numberClips[0].width + 10), y, &numberClips[highScoreDigits[i]]);
                    i++;
                }
                y += 60;
                i = 0;
                while (lastScoreDigits[i] != -1 && i < 3) {
                    GLTexture::textureProgram->modelViewMatrix = glm::mat4();
                    glTextureList[NUMBERS].render(lastScoreX - i * (numberClips[0].width + 10), y, &numberClips[lastScoreDigits[i]]);
                    i++;
                }

                SDL_GL_SwapWindow(window);

                // Restart the game if UP arrow key pressed
                if (keyboardState[SDL_SCANCODE_UP]) {
                    lastScore = 0;
                    systems[SPAWN_SYSTEM]->active = true;
                    systems[EXPANSION_SYSTEM]->active = true;
                    systems[GAMEOVER_SYSTEM]->active = true;
                    gameState = NORMAL;
                }
                break;
            }
        }
    }
}