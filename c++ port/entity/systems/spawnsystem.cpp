#include <vector>
#include <cstdio>
#include <time.h>
#include "spawnsystem.h"
#include "../../math/random.h"
#include "../../assets.h"

const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;
const int B = 5;
const int UPHALF1 = 6;
const int DOWNHALF1 = 7;
const int LEFTHALF1 = 8;
const int RIGHTHALF1 = 9;
const int UPHALF2 = 10;
const int DOWNHALF2 = 11;
const int LEFTHALF2 = 12;
const int RIGHTHALF2 = 13;
const int HB = 14;
const int QB = 15;

int OPENING1[] = {
        LEFTHALF1, DOWNHALF2, UPHALF2, RIGHTHALF1, QB,
        DOWN, UP, HB,
        LEFTHALF2, DOWNHALF1, UPHALF1, RIGHTHALF2, QB,
        LEFT, RIGHT, HB,
        LEFTHALF1, DOWNHALF2, UPHALF2, RIGHTHALF1, QB,
        DOWN, UP, B
};
int OPENING2[] = {
        LEFTHALF2, DOWNHALF1, UPHALF1, RIGHTHALF2, QB,
        LEFT, RIGHT, HB,
        LEFTHALF1, DOWNHALF2, UPHALF2, RIGHTHALF1, QB,
        DOWN, UP, HB,
        LEFTHALF2, DOWNHALF1, UPHALF1, RIGHTHALF2, QB,
        LEFT, RIGHT, B
};
int *OPENINGS[] = {OPENING1, OPENING2};

int OPPOSITE1[] = {
        LEFT, RIGHT, QB, LEFT, RIGHT, QB,
        UP, DOWN, QB, UP, DOWN, B
};
int OPPOSITE2[] = {
        UP, DOWN, QB, UP, DOWN, QB,
        LEFT, RIGHT, QB, LEFT, RIGHT, B
};
int *OPPOSITES[] = {OPPOSITE1, OPPOSITE2};

int ROSE1[] = {
        UPHALF1, RIGHTHALF1, DOWNHALF1, LEFTHALF1, HB, UPHALF2, RIGHTHALF2, DOWNHALF2, LEFTHALF2, HB,
        UPHALF1, RIGHTHALF1, DOWNHALF1, LEFTHALF1, HB, UPHALF2, RIGHTHALF2, DOWNHALF2, LEFTHALF2, HB,
        UPHALF1, RIGHTHALF1, DOWNHALF1, LEFTHALF1, HB, UPHALF2, RIGHTHALF2, DOWNHALF2, LEFTHALF2, B
};
int ROSE2[] = {
        UPHALF2, RIGHTHALF2, DOWNHALF2, LEFTHALF2, HB, UPHALF1, RIGHTHALF1, DOWNHALF1, LEFTHALF1, HB,
        UPHALF2, RIGHTHALF2, DOWNHALF2, LEFTHALF2, HB, UPHALF1, RIGHTHALF1, DOWNHALF1, LEFTHALF1, HB,
        UPHALF2, RIGHTHALF2, DOWNHALF2, LEFTHALF2, HB, UPHALF1, RIGHTHALF1, DOWNHALF1, LEFTHALF1, B
};
int *ROSES[] = {ROSE1, ROSE2};

int SPIRAL1[] = {
        DOWN, QB, RIGHT, QB, UP, QB, LEFT, QB,
        DOWN, QB, RIGHT, QB, UP, QB, LEFT, B
};
int SPIRAL2[] = {
        RIGHT, QB, UP, QB, LEFT, QB, DOWN, QB,
        RIGHT, QB, UP, QB, LEFT, QB, DOWN, B
};
int SPIRAL3[] = {
        UP, QB, LEFT, QB, DOWN, QB, RIGHT, QB,
        UP, QB, LEFT, QB, DOWN, QB, RIGHT, B
};
int SPIRAL4[] = {
        LEFT, QB, DOWN, QB, RIGHT, QB, UP, QB,
        LEFT, QB, DOWN, QB, RIGHT, QB, UP, B
};
int *SPIRALS[] = {SPIRAL1, SPIRAL2, SPIRAL3, SPIRAL4};


//    SIMPLE
int MAZE1[] = {
        UP, RIGHT, DOWN, LEFTHALF1, B
};
int MAZE2[] = {
        UP, RIGHT, DOWN, LEFTHALF2, B
};
int MAZE3[] = {
        UP, RIGHT, DOWNHALF1, LEFT, B
};
int MAZE4[] = {
        UP, RIGHT, DOWNHALF2, LEFT, B
};
int MAZE5[] = {
        UP, RIGHTHALF1, DOWN, LEFT, B
};
int MAZE6[] = {
        UP, RIGHTHALF2, DOWN, LEFT, B
};
int MAZE7[] = {
        UPHALF1, RIGHT, DOWN, LEFT, B
};
int MAZE8[] = {
        UPHALF2, RIGHT, DOWN, LEFT, B
};
int *MAZES[] = {MAZE1, MAZE2, MAZE3, MAZE4, MAZE5, MAZE6, MAZE7, MAZE8};

int THREE1[] = {
        UP, DOWN, LEFT, B
};
int THREE2[] = {
        RIGHT, DOWN, LEFT, B
};
int THREE3[] = {
        UP, RIGHT, LEFT, B
};
int THREE4[] = {
        UP, RIGHT, DOWN, B
};
int *THREES[] = {THREE1, THREE2, THREE3, THREE4};

int CORNER1[] = {
        LEFTHALF1, DOWN, RIGHT, UPHALF2, B
};
int CORNER2[] = {
        UPHALF1, LEFT, DOWN, RIGHTHALF2, B
};
int CORNER3[] = {
        RIGHTHALF1, UP, LEFT, DOWNHALF2, B
};
int CORNER4[] = {
        LEFTHALF2, UP, RIGHT, DOWNHALF1, B
};
int *CORNERS[] = {CORNER1, CORNER2, CORNER3, CORNER4};

std::vector<int> level;

int i = 0;
bool randomized = true;
const float timerMax = 1.0f;
float timer = timerMax;

void generateLevel() {
    srand((unsigned int) time(0)); // Set the random seed
    int k;
    int totalPatterns = 100;
    int simpleStreak = 0;
    int specialStreak = 0;
    while (totalPatterns > 0) {
        totalPatterns--;
        k = random(0, 3);
        if (simpleStreak > 6) {
            k = 1;
            simpleStreak = 0;
        }
        if (specialStreak > 2) {
            k = 0;
            specialStreak = 0;
        }
        // Standard patterns
        if (k != 0) {
            simpleStreak++;
            k = random(0, 2);
            switch (k) {
                case 0: {
                    k = random(0, 3);
                    int size = sizeof(THREE1) / sizeof(int);
                    level.insert(level.end(), &THREES[k][0], &THREES[k][size]);
                    break;
                }
                case 1: {
                    k = random(0, 7);
                    int size = sizeof(MAZE1) / sizeof(int);
                    level.insert(level.end(), &MAZES[k][0], &MAZES[k][size]);
                    break;
                }
                case 2: {
                    k = random(0, 3);
                    int size = sizeof(CORNER1) / sizeof(int);
                    level.insert(level.end(), &CORNERS[k][0], &CORNERS[k][size]);
                    break;
                }
            }
        } else { // Special patterns
            specialStreak++;
            k = random(0, 3);
            switch (k) {
                case 0: {
                    k = random(0, 1);
                    int size = sizeof(OPENING1) / sizeof(int);
                    level.insert(level.end(), &OPENINGS[k][0], &OPENINGS[k][size]);
                    break;
                }
                case 1: {
                    k = random(0, 1);
                    int size = sizeof(ROSE1) / sizeof(int);
                    level.insert(level.end(), &ROSES[k][0], &ROSES[k][size]);
                    break;
                }
                case 2: {
                    k = random(0, 3);
                    int size = sizeof(SPIRAL1) / sizeof(int);
                    level.insert(level.end(), &SPIRALS[k][0], &SPIRALS[k][size]);
                    break;
                }
                case 3: {
                    k = random(0, 1);
                    int size = sizeof(OPPOSITE1) / sizeof(int);
                    level.insert(level.end(), &OPPOSITES[k][0], &OPPOSITES[k][size]);
                    break;
                }
            }
        }
    }
}

SpawnSystem::SpawnSystem() {
    if (randomized) {
        level.clear();
        generateLevel();
    }
}

void createParticleEntity(int x, int y) {
    Uint16 id = createEntity();

    addComponent(id, TRANSFORM);
    if (x >= 32) {
        transformList[id].x = 32;
    } else {
        transformList[id].x = 31;
    }
    if (y >= 32) {
        transformList[id].y = 32;
    } else {
        transformList[id].y = 31;
    }

    addComponent(id, TEXTURE);
    textureList[id].texture = &glTextureList[PIXEL];

    addComponent(id, PARTICLE);
    particleList[id].start.x = transformList[id].x;
    particleList[id].start.y = transformList[id].y;
    particleList[id].destination.x = x;
    particleList[id].destination.y = y;
    particleList[id].timer = 0.0f;
}

// Line is spawned clockwise
// line(0, 10, UP) will spawn a 10 long line on the top border starting from the top left corner
void line(int start, int end, int direction) {
    if (direction == UP) {
        for (int i = start; i < end; i++) {
            createParticleEntity(i, 63);
        }
    } else if (direction == DOWN) {
        for (int i = start; i < end; i++) {
            createParticleEntity(63 - i, 0);
        }
    } else if (direction == LEFT) {
        for (int i = start; i < end; i++) {
            createParticleEntity(0, i);
        }
    } else if (direction == RIGHT) {
        for (int i = start; i < end; i++) {
            createParticleEntity(63, 63 - i);
        }
    }
}

void SpawnSystem::update(float deltaTime) {
    // Limit deltaTime during frametime spikes
    if (deltaTime < 1 / 60.0f * 2) {
        timer -= deltaTime;
    } else {
        timer -= 1 / 60.0f;
    }

    if (timer > 0.0f) {
        return;
    }

    while (i < level.size()) {
        // Breaks, exit the while loop
        if (level[i] == B) {
            timer += timerMax;
            i++;
            if (i == level.size()) {
                i = 0;
            }
            break;
        } else if (level[i] == HB) {
            timer += timerMax / 2;
            i++;
            if (i == level.size()) {
                i = 0;
            }
            break;
        } else if (level[i] == QB) {
            timer += timerMax / 4;
            i++;
            if (i == level.size()) {
                i = 0;
            }
            break;
        }
        // Pattern spawn as long as there are more
        switch (level[i]) {
            case (UP): {
                line(0, 63, UP);
                break;
            }
            case (DOWN): {
                line(0, 63, DOWN);
                break;
            }
            case (LEFT): {
                line(0, 63, LEFT);
                break;
            }
            case (RIGHT): {
                line(0, 63, RIGHT);
                break;
            }
            case (UPHALF1): {
                line(0, 31, UP);
                break;
            }
            case (DOWNHALF1): {
                line(0, 31, DOWN);
                break;
            }
            case (LEFTHALF1): {
                line(0, 31, LEFT);
                break;
            }
            case (RIGHTHALF1): {
                line(0, 31, RIGHT);
                break;
            }
            case (UPHALF2): {
                line(32, 63, UP);
                break;
            }
            case (DOWNHALF2): {
                line(32, 63, DOWN);
                break;
            }
            case (LEFTHALF2): {
                line(32, 63, LEFT);
                break;
            }
            case (RIGHTHALF2): {
                line(32, 63, RIGHT);
                break;
            }
        }
        // No more level left, generate more
        i++;
        if (i == level.size()) {
            level.clear();
            generateLevel();
            i = 0;
        }
    }
}
