#ifndef CORE_FAMILY_H
#define CORE_FAMILY_H

#include "engine.h"

struct Family {
    Uint32 mask;
    Uint16 entities[MAX_ENTITY_COUNT];
    Uint16 size;
};

#endif //CORE_FAMILY_H
