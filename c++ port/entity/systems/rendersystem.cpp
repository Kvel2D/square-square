#include "rendersystem.h"
#include "../family.h"
#include "../../main.h"

Color textureColor = {1.0f, 1.0f, 1.0f, 1.0f};

RenderSystem::RenderSystem() {
    Uint32 mask = 0;
    mask |= 1 << TRANSFORM;
    mask |= 1 << TEXTURE;
    family = getFamily(mask);
}

void RenderSystem::update(float deltaTime) {
    GLTexture::textureProgram->setTextureColor(textureColor);
    for (int i = 0; i < family->size; i++) {
        processEntity(family->entities[i]);
    }
}

void RenderSystem::processEntity(Uint16 id) {
    GLTexture::textureProgram->modelViewMatrix = glm::mat4();

    GLTexture *texture = textureList[id].texture;
    int x = transformList[id].x * 4;
    int y = SCREEN_HEIGHT - transformList[id].y * 4 - texture->imageHeight;
    texture->render(x, y);
}





