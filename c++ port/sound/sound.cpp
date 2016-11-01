#include <SDL2/SDL_audio.h>
#include <stdio.h>
#include "sound.h"
#include "../main.h"

void Sound::loadFromFile(std::string path) {
    music = Mix_LoadMUS(path.c_str());

    if (music == NULL) {
        printf("Failed loading sound from %s\n", path.c_str());
        exitApp(1);
    }
}

void Sound::play() {
    Mix_PlayMusic(music, 0);
}

void Sound::freeSound() {
    if (music != NULL) {
        Mix_FreeMusic(music);
        music = NULL;
    }
}



