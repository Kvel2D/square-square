#ifndef CORE_GAMEOVERSYSTEM_H
#define CORE_GAMEOVERSYSTEM_H


#include "../system.h"

class GameoverSystem: public System {
public:
    Family *family;

    GameoverSystem();
    void update(float deltaTime);
    void processEntity(Uint16 id, float deltaTime);
};


#endif //CORE_GAMEOVERSYSTEM_H
