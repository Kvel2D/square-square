#include <algorithm>
#include <chrono>
#include "engine.h"
#include "systems/rendersystem.h"
#include "family.h"
#include "systems/inputsystem.h"
#include "systems/spawnsystem.h"
#include "systems/expansionsystem.h"
#include "systems/gameoversystem.h"
#include "../main.h"

// ENTITY STRUCTS
Transform transformList[MAX_ENTITY_COUNT];
Texture textureList[MAX_ENTITY_COUNT];
Particle particleList[MAX_ENTITY_COUNT];

// ENTITY STATE
Uint32 mask[MAX_ENTITY_COUNT]; // components mask
bool status[MAX_ENTITY_COUNT]; // alive/dead
bool dirty[MAX_ENTITY_COUNT]; // needs family membership update

// ENGINE RESOURCES
Family families[MAX_FAMILY_COUNT];
System *systems[SYSTEM_COUNT];
// ENTITIES SCHEDULED FOR REMOVAL
std::vector<Uint16> removedEntities;

bool updating = false;

std::chrono::high_resolution_clock::time_point currentTime;

void initEngine() {
    systems[RENDER_SYSTEM] = new RenderSystem();
    systems[INPUT_SYSTEM] = new InputSystem();
    systems[SPAWN_SYSTEM] = new SpawnSystem();
    systems[EXPANSION_SYSTEM] = new ExpansionSystem();
    systems[GAMEOVER_SYSTEM] = new GameoverSystem();
    currentTime = std::chrono::high_resolution_clock::now();
}

void updateEngine() {
    updating = true;

    // Find deltaTime(in milliseconds)
    std::chrono::high_resolution_clock::time_point newTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float, std::milli> duration = newTime - currentTime;
    float deltaTime = duration.count() / 1000;
    currentTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < SYSTEM_COUNT; i++) {
        if (systems[i]->active) {
            systems[i]->update(deltaTime);
        }
    }

    // Update families for any entities whose masks changed
    for (Uint16 id = 0; id < MAX_ENTITY_COUNT; id++) {
        if (dirty[id]) {
            updateFamilyForEntity(id);
        }
    }
    // Process removed entities
    for (int i = 0; i < removedEntities.size(); i++) {
        removeEntityInternal(removedEntities[i]);
    }
    removedEntities.clear();

    updating = false;
}

Family *getFamily(Uint32 mask) {
    for (int i = 0; i < MAX_FAMILY_COUNT; i++) {
        if (families[i].mask == mask) {
            // Family already exists
            return &families[i];
        } else if (families[i].mask == 0) {
            // Unregistered family
            families[i].mask = mask;
            return &families[i];
        }
    }
    printf("Engine error: went over max family count\n");
    exitApp(1);
}

Uint16 createEntity() {
    for (Uint16 i = 1; i <= MAX_ENTITY_COUNT; i++) {
        if (!status[i]) {
            status[i] = true;
            return i;
        }
    }
    printf("Engine error: went over max entity count\n");
    exitApp(1);
}

void removeEntity(Uint16 id) {
    // Delay removal until the end of the entity update
    // Outside of an update remove immediately
    if (updating) {
        removedEntities.insert(removedEntities.end(), id);
    } else {
        removeEntityInternal(id);
    }
}

void removeAllEntities() {
    for (Uint16 id = 0; id < MAX_ENTITY_COUNT; id++) {
        if (status[id]) {
            removeEntity(id);
        }
    }
}

void removeEntityInternal(Uint16 id) {
    if (!status[id]) {
        printf("Engine error: Attempted to remove entity twice\n");
    }
    status[id] = false;
    // Remove entity from it's families
    for (int i = 0; i < MAX_FAMILY_COUNT; i++) {
        // Find removed entity in the family
        for (int j = 0; j < families[i].size; j++) {
            if (families[i].entities[j] == id) {
                // Replace removed entity with the last entity;
                families[i].entities[j] = families[i].entities[families[i].size - 1];
                families[i].entities[families[i].size - 1] = 0;
                families[i].size--;
                j = families[i].size; // exit the loop
            }
        }
    }
    mask[id] = 0; // Clear component bits
}

void addComponent(Uint16 id, COMPONENT_BIT bit) {
    if (!status[id]) {
        printf("Engine error: Attempted to activate component on an inactive entity\n");
        return;
    }
    // Set the component bit in entity's mask and make it dirty
    mask[id] |= 1 << bit;
    dirty[id] = true;
}

void removeComponent(Uint16 id, COMPONENT_BIT bit) {
    if (!status[id]) {
        printf("Engine error: Attempted to deactivate component on an inactive entity\n");
        return;
    }
    // Clear the component bit in entity's mask
    mask[id] &= ~(1 << bit);
    // Update the families for this entity later
    dirty[id] = true;
}

bool hasComponent(Uint16 id, COMPONENT_BIT bit) {
    // Check if the component bit is set in entity's mask
    return ((mask[id] >> bit) & 1) == 1;
}

void updateFamilyForEntity(Uint16 id) {
    Uint16 idIndex = 0;
    // Go through each family, removing or inserting entity
    for (int i = 0; i < MAX_FAMILY_COUNT; i++) {
        // Skip empty families
        if (families[i].mask == 0) {
            continue;
        }

        // Find entity in the family
        idIndex = 0;
        for (Uint16 j = 0; j < families[i].size; j++, idIndex++) {
            if (families[i].entities[j] == id) {
                idIndex = j;
                j = families[i].size; // exit loop
            }
        }

        // Entity belongs to the family
        if ((mask[id] & families[i].mask) == families[i].mask) {
            // Insert entity if at the end of the array
            if (families[i].entities[idIndex] == 0) {
                families[i].entities[idIndex] = id;
                families[i].size++;
            }
        } else if (families[i].entities[idIndex] != 0) {
            // Entity exited the family
            families[i].entities[idIndex] = families[i].entities[families[i].size - 1];
            families[i].entities[families[i].size - 1] = 0;
            families[i].size--;
        }
    }
    dirty[id] = false;
}














