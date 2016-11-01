#include "expansionsystem.h"
#include "../family.h"
#include "../../globals.h"
#include "../../assets.h"

const float particleTime = 1.0f;
bool soundPlayed = false;
int soundNumber = 1;

ExpansionSystem::ExpansionSystem() {
    Uint32 mask = 0;
    mask |= 1 << TRANSFORM;
    mask |= 1 << PARTICLE;
    family = getFamily(mask);
}

void ExpansionSystem::update(float deltaTime) {
    // Clear the grid
    for (int j = 0; j < 64; j++) {
        for (int k = 0; k < 64; k++) {
            grid[j][k] = false;
        }
    }

    // Expand particles
    for (int i = 0; i < family->size; i++) {
        processEntity(family->entities[i], deltaTime);
    }

    soundPlayed = false;
}

float lerp(float from, float to, float alpha) {
    return from + (to - from) * alpha;
}

void ExpansionSystem::processEntity(Uint16 id, float deltaTime) {
    Transform *transformC = &transformList[id];
    Particle *particleC = &particleList[id];

    particleC->timer += deltaTime;

    // Increase position away from center
    // Timer value is multiplied by 1.5f to increase top speed
    int x = (int) round(
                lerp(particleC->start.x, particleC->destination.x, (particleC->timer * 1.5f) / particleTime));
    int y = (int) round(
                lerp(particleC->start.y, particleC->destination.y, (particleC->timer * 1.5f) / particleTime));

    // Remove particles exiting the grid
    if (x < 0 || y < 0 || x >= 64 || y >= 64) {
        removeEntity(id);
        if (!soundPlayed) {
            if (soundNumber == 1) {
                soundList[SOUND1].play();
                soundNumber = 2;
            } else {
                soundList[SOUND2].play();
                soundNumber = 1;
            }
            soundPlayed = true;
        }
    } else {
        transformC->x = x;
        transformC->y = y;
        // Mark current position in the grid
        grid[x][y] = true;
    }
}

