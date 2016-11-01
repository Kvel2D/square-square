#ifndef CORE_INPUTSYSTEM_H
#define CORE_INPUTSYSTEM_H


#include "../system.h"

class InputSystem : public System {
public:
    Family *family;

    InputSystem();
    void update(float deltaTime);
    void processEntity(Uint16 id, float deltaTime);
private:
    bool left;
    bool right;
};


#endif //CORE_INPUTSYSTEM_H
