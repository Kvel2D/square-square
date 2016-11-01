#include <glm/gtc/matrix_transform.hpp>
#include <string.h>
#include "assets.h"
#include "main.h"

char texturePaths[TEXTURE_TOTAL][PATH_LENGTH_MAX];
GLTexture glTextureList[TEXTURE_TOTAL];
char soundPaths[SOUND_TOTAL][PATH_LENGTH_MAX];
Sound soundList[SOUND_TOTAL];
TextureProgram textureProgram;

void loadAssets() {
    // Declare paths here
    strcpy(texturePaths[PIXEL], "assets/pixel.png");
    strcpy(texturePaths[NUMBERS], "assets/numbers.png");

    strcpy(soundPaths[SOUND1], "assets/sound1.ogg");
    strcpy(soundPaths[SOUND2], "assets/sound2.ogg");
    strcpy(soundPaths[GAMEOVER_SOUND], "assets/gameover.ogg");

    // Init texture shader program
    textureProgram.loadProgram();
    textureProgram.bind();
    textureProgram.projectionMatrix = glm::ortho<GLfloat>(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0);
    textureProgram.updateProjection();
    textureProgram.modelViewMatrix = glm::mat4();
    textureProgram.updateModelView();
    textureProgram.setTextureUnit(0);
    GLTexture::textureProgram = &textureProgram;

    // Load all declared texture files
    for (int i = 0; i < TEXTURE_TOTAL; i++) {
        glTextureList[i].loadFromFile(texturePaths[i]);
    }

    // Load all declared sound files
    for (int i = 0; i < SOUND_TOTAL; i++) {
        soundList[i].loadFromFile(soundPaths[i]);
    }
}

void freeAssets() {
    for (int i = 0; i < TEXTURE_TOTAL; i++) {
        glTextureList[i].freeTexture();
    }
    for (int i = 0; i < SOUND_TOTAL; i++) {
        soundList[i].freeSound();
    }
}

