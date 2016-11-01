#ifndef CORE_EXPANSIONSYSTEM_H
#define CORE_EXPANSIONSYSTEM_H

#include "../system.h"

class ExpansionSystem : public System {
public:
    Family *family;

    ExpansionSystem();
    void update(float deltaTime);
    void processEntity(Uint16 id, float deltaTime);
};


#endif //CORE_EXPANSIONSYSTEM_H
