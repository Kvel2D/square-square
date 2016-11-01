#ifndef CORE_ENGINE_H
#define CORE_ENGINE_H

#include <vector>
#include <SDL2/SDL_stdinc.h>
#include "system.h"
#include "components/transform.h"
#include "components/texture.h"
#include "components/particle.h"

class System;
struct Family;

typedef enum {
    TRANSFORM, TEXTURE, INPUT, PARTICLE
} COMPONENT_BIT;
typedef enum {
    INPUT_SYSTEM, SPAWN_SYSTEM, EXPANSION_SYSTEM, GAMEOVER_SYSTEM, RENDER_SYSTEM, SYSTEM_COUNT
} SYSTEM;
const Uint16 MAX_ENTITY_COUNT = 500;
const int MAX_FAMILY_COUNT = 3; // adjust this when adding new systems


extern Transform transformList[MAX_ENTITY_COUNT];
extern Texture textureList[MAX_ENTITY_COUNT];
extern Particle particleList[MAX_ENTITY_COUNT];

extern Uint32 mask[MAX_ENTITY_COUNT];
extern bool status[MAX_ENTITY_COUNT];
extern System* systems[SYSTEM_COUNT];


// Engine functions
void initEngine();
void freeEngine();
void updateEngine();
void removeAllEntities();

// Entity operations
Uint16 createEntity();
void removeEntity(Uint16 id);
void addComponent(Uint16 id, COMPONENT_BIT bit);
void removeComponent(Uint16 id, COMPONENT_BIT bit);
bool hasComponent(Uint16 id, COMPONENT_BIT bit);

// Internal(entity/system) use only
void updateFamilyForEntity(Uint16 id);
void removeEntityInternal(Uint16 id);
Family *getFamily(Uint32 mask);


#endif //CORE_ENGINE_H
