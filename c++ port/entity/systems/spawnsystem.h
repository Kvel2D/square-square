#ifndef CORE_SPAWNSYSTEM_H
#define CORE_SPAWNSYSTEM_H


#include <SDL2/SDL_stdinc.h>
#include "../family.h"

class SpawnSystem : public System {
public:

    SpawnSystem();
    void update(float deltaTime);
};


#endif //CORE_SPAWNSYSTEM_H
