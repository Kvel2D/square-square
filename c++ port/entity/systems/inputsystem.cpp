#include <SDL2/SDL_scancode.h>
#include <cstdio>
#include "inputsystem.h"
#include "../family.h"
#include "../../main.h"

const int DEFAULT_SPEED = 6;

InputSystem::InputSystem() {
    Uint32 mask = 0;
    mask |= 1 << TRANSFORM;
    mask |= 1 << INPUT;
    family = getFamily(mask);
}


void InputSystem::update(float deltaTime) {
    left = keyboardState[SDL_SCANCODE_LEFT];
    right = keyboardState[SDL_SCANCODE_RIGHT];
    for (int i = 0; i < family->size; i++) {
        processEntity(family->entities[i], deltaTime);
    }
}

void InputSystem::processEntity(Uint16 id, float deltaTime) {
    // Adjust speed with a preference for lower values
    // higher fps reduces speed but lower fps doesn't affect it
    int adjustedSpeed = (int) (DEFAULT_SPEED * deltaTime / (1 / 60.0f));
    if (adjustedSpeed > DEFAULT_SPEED) {
        adjustedSpeed = DEFAULT_SPEED;
    }

    if (left && !right) {
        Transform *transformC = &transformList[id];

        if (transformC->y == 0) {
            if (transformC->x < adjustedSpeed) {
                transformC->x = 0;
                transformC->y += adjustedSpeed;
            } else {
                transformC->x -= adjustedSpeed;
            }
        } else if (transformC->y == 63) {
            if (transformC->x > 63 - adjustedSpeed) {
                transformC->x = 63;
                transformC->y -= adjustedSpeed;
            } else {
                transformC->x += adjustedSpeed;
            }
        } else if (transformC->x == 0) {
            if (transformC->y > 63 - adjustedSpeed) {
                transformC->y = 63;
                transformC->x += adjustedSpeed;
            } else {
                transformC->y += adjustedSpeed;
            }
        } else if (transformC->x == 63) {
            if (transformC->y < adjustedSpeed) {
                transformC->y = 0;
                transformC->x -= adjustedSpeed;
            } else {
                transformC->y -= adjustedSpeed;
            }
        }
        // RIGHT
    } else if (right && !left) {
        Transform *transformC = &transformList[id];

        if (transformC->y == 0) {
            if (transformC->x > 63 - adjustedSpeed) {
                transformC->x = 63;
                transformC->y += adjustedSpeed;
            } else {
                transformC->x += adjustedSpeed;
            }
        } else if (transformC->y == 63) {
            if (transformC->x < adjustedSpeed) {
                transformC->x = 0;
                transformC->y -= adjustedSpeed;
            } else {
                transformC->x -= adjustedSpeed;
            }
        } else if (transformC->x == 0) {
            if (transformC->y < adjustedSpeed) {
                transformC->y = 0;
                transformC->x += adjustedSpeed;
            } else {
                transformC->y -= adjustedSpeed;
            }
        } else if (transformC->x == 63) {
            if (transformC->y > 63 - adjustedSpeed) {
                transformC->y = 63;
                transformC->x -= adjustedSpeed;
            } else {
                transformC->y += adjustedSpeed;
            }
        }
    }
}