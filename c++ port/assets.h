#ifndef CORE_ASSETS_H
#define CORE_ASSETS_H


#include "graphics/gltexture.h"
#include "sound/sound.h"

const int PATH_LENGTH_MAX = 100;

typedef enum {
    PIXEL,
    NUMBERS,
    TEXTURE_TOTAL
} TEXTURE_NAMES;
extern GLTexture glTextureList[TEXTURE_TOTAL];

typedef enum {
    SOUND1,
    SOUND2,
    GAMEOVER_SOUND,
    SOUND_TOTAL
} SOUND_NAMES;
extern Sound soundList[SOUND_TOTAL];

void loadAssets();
void freeAssets();


#endif //CORE_ASSETS_H
