#ifndef CORE_RANDOM_H
#define CORE_RANDOM_H

#include <stdlib.h>

#define random(min, max) \
        ((rand()%(int)(((max) + 1)-(min)))+ (min))

#endif //CORE_RANDOM_H
