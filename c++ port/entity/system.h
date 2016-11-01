#ifndef CORE_SYSTEM_H
#define CORE_SYSTEM_H

#include <string>
#include "engine.h"

class Engine;

class System {
public:
    bool active;

    System() : active(true) { }
    virtual void update(float deltaTime) = 0;
};


#endif //CORE_SYSTEM_H
