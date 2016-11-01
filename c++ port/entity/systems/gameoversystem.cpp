#include "gameoversystem.h"
#include "../family.h"
#include "../../globals.h"
#include "../../main.h"
#include "../../assets.h"

GameoverSystem::GameoverSystem() {
    Uint32 mask = 0;
    mask |= 1 << TRANSFORM;
    mask |= 1 << INPUT;
    family = getFamily(mask);
}

void GameoverSystem::update(float deltaTime) {
    lastScore += deltaTime; // meh, nowhere else to put it
    for (int i = 0; i < family->size; i++) {
        processEntity(family->entities[i], deltaTime);
    }
}

void GameoverSystem::processEntity(Uint16 id, float deltaTime) {
    Transform *transformC = &transformList[id];

    if (grid[transformC->x][transformC->y]) {
        soundList[GAMEOVER_SOUND].play();
        gameState = GAMEOVER;
    }
}



