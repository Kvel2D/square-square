#ifndef CORE_RENDER_H
#define CORE_RENDER_H


#include "../system.h"

class RenderSystem : public System {
public:
    Family *family;

    RenderSystem();
    void update(float deltaTime);
    void processEntity(Uint16 id);
};


#endif //CORE_RENDER_H
