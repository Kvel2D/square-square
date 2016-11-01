#ifndef CORE_PARTICLE_H
#define CORE_PARTICLE_H

#include "../../math/vector2.h"

struct Particle {
    Vector2 start;
    Vector2 destination;
    float timer;
};

#endif //CORE_PARTICLE_H
