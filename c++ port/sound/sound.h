#ifndef CORE_SOUND_H
#define CORE_SOUND_H

#include <string>
#include <SDL2/SDL_mixer.h>

class Sound {
public:
    void loadFromFile(std::string path);
    void freeSound();
    void play();
private:
    Mix_Music *music;
};


#endif //CORE_SOUND_H
