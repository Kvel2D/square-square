package com.mygdx.core.entity.systems;

import com.badlogic.ashley.core.EntitySystem;
import com.mygdx.core.Main;
import com.mygdx.core.entity.EntityFactory;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class SpawnSystem extends EntitySystem {
    final int UP = 0;
    final int DOWN = 1;
    final int LEFT = 2;
    final int RIGHT = 3;
    final int B = 5;
    final int UPHALF1 = 6;
    final int DOWNHALF1 = 7;
    final int LEFTHALF1 = 8;
    final int RIGHTHALF1 = 9;
    final int UPHALF2 = 10;
    final int DOWNHALF2 = 11;
    final int LEFTHALF2 = 12;
    final int RIGHTHALF2 = 13;
    final int HB = 14;
    final int QB = 15;

    Integer[] OPENING1 = new Integer[]{
        LEFTHALF1, DOWNHALF2, UPHALF2, RIGHTHALF1, QB,
        DOWN, UP, HB,
        LEFTHALF2, DOWNHALF1, UPHALF1, RIGHTHALF2, QB,
        LEFT, RIGHT, HB,
        LEFTHALF1, DOWNHALF2, UPHALF2, RIGHTHALF1, QB,
        DOWN, UP, B
    };
    Integer[] OPENING2 = new Integer[]{
        LEFTHALF2, DOWNHALF1, UPHALF1, RIGHTHALF2, QB,
        LEFT, RIGHT, HB,
        LEFTHALF1, DOWNHALF2, UPHALF2, RIGHTHALF1, QB,
        DOWN, UP, HB,
        LEFTHALF2, DOWNHALF1, UPHALF1, RIGHTHALF2, QB,
        LEFT, RIGHT, B
    };
    Integer[][] OPENINGS = new Integer[][]{OPENING1, OPENING2};

    Integer[] OPPOSITE1 = new Integer[]{
        LEFT, RIGHT, QB, LEFT, RIGHT, QB,
        UP, DOWN, QB, UP, DOWN, B
    };
    Integer[] OPPOSITE2 = new Integer[]{
        UP, DOWN, QB, UP, DOWN, QB,
        LEFT, RIGHT, QB, LEFT, RIGHT, B
    };
    Integer[][] OPPOSITES = new Integer[][]{OPPOSITE1, OPPOSITE2};

    Integer[] ROSE1 = new Integer[]{
        UPHALF1, RIGHTHALF1, DOWNHALF1, LEFTHALF1, HB, UPHALF2, RIGHTHALF2, DOWNHALF2, LEFTHALF2, HB,
        UPHALF1, RIGHTHALF1, DOWNHALF1, LEFTHALF1, HB, UPHALF2, RIGHTHALF2, DOWNHALF2, LEFTHALF2, HB,
        UPHALF1, RIGHTHALF1, DOWNHALF1, LEFTHALF1, HB, UPHALF2, RIGHTHALF2, DOWNHALF2, LEFTHALF2, B
    };
    Integer[] ROSE2 = new Integer[]{
        UPHALF2, RIGHTHALF2, DOWNHALF2, LEFTHALF2, HB, UPHALF1, RIGHTHALF1, DOWNHALF1, LEFTHALF1, HB,
        UPHALF2, RIGHTHALF2, DOWNHALF2, LEFTHALF2, HB, UPHALF1, RIGHTHALF1, DOWNHALF1, LEFTHALF1, HB,
        UPHALF2, RIGHTHALF2, DOWNHALF2, LEFTHALF2, HB, UPHALF1, RIGHTHALF1, DOWNHALF1, LEFTHALF1, B
    };
    Integer[][] ROSES = new Integer[][]{ROSE1, ROSE2};

    Integer[] SPIRAL1 = new Integer[]{
        DOWN, QB, RIGHT, QB, UP, QB, LEFT, QB,
        DOWN, QB, RIGHT, QB, UP, QB, LEFT, B
    };
    Integer[] SPIRAL2 = new Integer[]{
        RIGHT, QB, UP, QB, LEFT, QB, DOWN, QB,
        RIGHT, QB, UP, QB, LEFT, QB, DOWN, B
    };
    Integer[] SPIRAL3 = new Integer[]{
        UP, QB, LEFT, QB, DOWN, QB, RIGHT, QB,
        UP, QB, LEFT, QB, DOWN, QB, RIGHT, B
    };
    Integer[] SPIRAL4 = new Integer[]{
        LEFT, QB, DOWN, QB, RIGHT, QB, UP, QB,
        LEFT, QB, DOWN, QB, RIGHT, QB, UP, B
    };
    Integer[][] SPIRALS = new Integer[][]{SPIRAL1, SPIRAL2, SPIRAL3, SPIRAL4};


    //    SIMPLE
    Integer[] MAZE1 = new Integer[]{
        UP, RIGHT, DOWN, LEFTHALF1, B
    };
    Integer[] MAZE2 = new Integer[]{
        UP, RIGHT, DOWN, LEFTHALF2, B
    };
    Integer[] MAZE3 = new Integer[]{
        UP, RIGHT, DOWNHALF1, LEFT, B
    };
    Integer[] MAZE4 = new Integer[]{
        UP, RIGHT, DOWNHALF2, LEFT, B
    };
    Integer[] MAZE5 = new Integer[]{
        UP, RIGHTHALF1, DOWN, LEFT, B
    };
    Integer[] MAZE6 = new Integer[]{
        UP, RIGHTHALF2, DOWN, LEFT, B
    };
    Integer[] MAZE7 = new Integer[]{
        UPHALF1, RIGHT, DOWN, LEFT, B
    };
    Integer[] MAZE8 = new Integer[]{
        UPHALF2, RIGHT, DOWN, LEFT, B
    };
    Integer[][] MAZES = new Integer[][]{MAZE1, MAZE2, MAZE3, MAZE4, MAZE5, MAZE6, MAZE7, MAZE8};

    Integer[] THREE1 = new Integer[]{
        UP, DOWN, LEFT, B
    };
    Integer[] THREE2 = new Integer[]{
        RIGHT, DOWN, LEFT, B
    };
    Integer[] THREE3 = new Integer[]{
        UP, RIGHT, LEFT, B
    };
    Integer[] THREE4 = new Integer[]{
        UP, RIGHT, DOWN, B
    };
    Integer[][] THREES = new Integer[][]{THREE1, THREE2, THREE3, THREE4};

    Integer[] CORNER1 = new Integer[]{
        LEFTHALF1, DOWN, RIGHT, UPHALF2, B
    };
    Integer[] CORNER2 = new Integer[]{
        UPHALF1, LEFT, DOWN, RIGHTHALF2, B
    };
    Integer[] CORNER3 = new Integer[]{
        RIGHTHALF1, UP, LEFT, DOWNHALF2, B
    };
    Integer[] CORNER4 = new Integer[]{
        LEFTHALF2, UP, RIGHT, DOWNHALF1, B
    };
    Integer[][] CORNERS = new Integer[][]{CORNER1, CORNER2, CORNER3, CORNER4};

    List<Integer> level = new ArrayList<Integer>();
    int i = 0;
    boolean randomized = true;
    final float timerMax = 1f;
    float timer = timerMax;

    public SpawnSystem() {
    }

    public SpawnSystem(int priority) {
        super(priority);
        if (randomized) {
            level.clear();
            generateLevel();
        }
    }

    private void generateLevel() {
        int k;
        int totalPatterns = 100;
        int simpleStreak = 0;
        int specialStreak = 0;
        while (totalPatterns > 0) {
            totalPatterns--;
            k = Main.rand.nextInt(4);
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
                k = Main.rand.nextInt(3);
                switch (k) {
                    case 0: {
                        k = Main.rand.nextInt(4);
                        addPattern(THREES[k]);
                        break;
                    }
                    case 1: {
                        k = Main.rand.nextInt(8);
                        addPattern(MAZES[k]);
                        break;
                    }
                    case 2: {
                        k = Main.rand.nextInt(4);
                        addPattern(CORNERS[k]);
                        break;
                    }
                }
            } else { // Special patterns
                specialStreak++;
                k = Main.rand.nextInt(4);
                switch (k) {
                    case 0: {
                        k = Main.rand.nextInt(2);
                        addPattern(OPENINGS[k]);
                        break;
                    }
                    case 1: {
                        k = Main.rand.nextInt(2);
                        addPattern(ROSES[k]);
                        break;
                    }
                    case 2: {
                        k = Main.rand.nextInt(4);
                        addPattern(SPIRALS[k]);
                        break;
                    }
                    case 3: {
                        k = Main.rand.nextInt(2);
                        addPattern(OPPOSITES[k]);
                        break;
                    }
                }
            }
        }
    }

    private void addPattern(Integer[] pattern) {
        level.addAll(Arrays.asList(pattern));
    }


    public void update(float deltaTime) {
        timer -= deltaTime;
        if (timer > 0) {
            return;
        }

        while (i < level.size()) {
            // Breaks, exit the while loop
            if (level.get(i) == B) {
                timer += timerMax;
                i++;
                if (i == level.size()) {
                    i = 0;
                }
                break;
            } else if (level.get(i) == HB) {
                timer += timerMax / 2;
                i++;
                if (i == level.size()) {
                    i = 0;
                }
                break;
            } else if (level.get(i) == QB) {
                timer += timerMax / 4;
                i++;
                if (i == level.size()) {
                    i = 0;
                }
                break;
            }
            // Pattern spawn as long as there are more
            switch (level.get(i)) {
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

    // Line is spawned clockwise
    // line(0, 10, UP) will spawn a 10 long line on the top border starting from the top left corner
    private void line(int start, int end, int direction) {
        if (direction == UP) {
            for (int i = start; i < end; i++) {
                EntityFactory.particle(i, 63);
            }
        } else if (direction == DOWN) {
            for (int i = start; i < end; i++) {
                EntityFactory.particle(63 - i, 0);
            }
        } else if (direction == LEFT) {
            for (int i = start; i < end; i++) {
                EntityFactory.particle(0, i);
            }
        } else if (direction == RIGHT) {
            for (int i = start; i < end; i++) {
                EntityFactory.particle(63, 63 - i);
            }
        }
    }
}
