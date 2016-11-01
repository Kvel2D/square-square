package com.mygdx.core.entity.systems;

import com.badlogic.ashley.core.Entity;
import com.badlogic.ashley.core.Family;
import com.badlogic.ashley.systems.IteratingSystem;
import com.badlogic.gdx.InputAdapter;
import com.mygdx.core.Constants;
import com.mygdx.core.entity.Mappers;
import com.mygdx.core.entity.components.PlayerInputComponent;
import com.mygdx.core.entity.components.PositionComponent;

/*
 * Moves the player around the borders
 */
public class PlayerInputSystem extends IteratingSystem {
    public MyInputProcessor inputProcessor = new MyInputProcessor();
    boolean left = false;
    boolean right = false;

    public PlayerInputSystem() {
        super(Family.all(PlayerInputComponent.class).get());
    }

    public PlayerInputSystem(int priority) {
        super(Family.all(PlayerInputComponent.class).get(), priority);
    }

    public void processEntity(Entity entity, float deltaTime) {
        // LEFT
        if (left && !right) {
            PositionComponent positionC = Mappers.position.get(entity);

            if (positionC.y == 0) {
                if (positionC.x < Constants.PLAYER_SPEED) {
                    positionC.x = 0;
                    positionC.y += Constants.PLAYER_SPEED;
                } else {
                    positionC.x -= Constants.PLAYER_SPEED;
                }
            } else if (positionC.y == 63) {
                if (positionC.x > 63 - Constants.PLAYER_SPEED) {
                    positionC.x = 63;
                    positionC.y -= Constants.PLAYER_SPEED;
                } else {
                    positionC.x += Constants.PLAYER_SPEED;
                }
            } else if (positionC.x == 0) {
                if (positionC.y > 63 - Constants.PLAYER_SPEED) {
                    positionC.y = 63;
                    positionC.x += Constants.PLAYER_SPEED;
                } else {
                    positionC.y += Constants.PLAYER_SPEED;
                }
            } else if (positionC.x == 63) {
                if (positionC.y < Constants.PLAYER_SPEED) {
                    positionC.y = 0;
                    positionC.x -= Constants.PLAYER_SPEED;
                } else {
                    positionC.y -= Constants.PLAYER_SPEED;
                }
            }
            // RIGHT
        } else if (right && !left) {
            PositionComponent positionC = Mappers.position.get(entity);

            if (positionC.y == 0) {
                if (positionC.x > 63 - Constants.PLAYER_SPEED) {
                    positionC.x = 63;
                    positionC.y += Constants.PLAYER_SPEED;
                } else {
                    positionC.x += Constants.PLAYER_SPEED;
                }
            } else if (positionC.y == 63) {
                if (positionC.x < Constants.PLAYER_SPEED) {
                    positionC.x = 0;
                    positionC.y -= Constants.PLAYER_SPEED;
                } else {
                    positionC.x -= Constants.PLAYER_SPEED;
                }
            } else if (positionC.x == 0) {
                if (positionC.y < Constants.PLAYER_SPEED) {
                    positionC.y = 0;
                    positionC.x += Constants.PLAYER_SPEED;
                } else {
                    positionC.y -= Constants.PLAYER_SPEED;
                }
            } else if (positionC.x == 63) {
                if (positionC.y > 63 - Constants.PLAYER_SPEED) {
                    positionC.y = 63;
                    positionC.x -= Constants.PLAYER_SPEED;
                } else {
                    positionC.y += Constants.PLAYER_SPEED;
                }
            }
        }
    }

    public class MyInputProcessor extends InputAdapter {

        public boolean keyDown(int keycode) {
            if (keycode == Constants.CONTROL_LEFT) {
                left = true;
            } else if (keycode == Constants.CONTROL_RIGHT) {
                right = true;
            }
            return false;
        }

        public boolean keyUp(int keycode) {
            if (keycode == Constants.CONTROL_LEFT) {
                left = false;
            } else if (keycode == Constants.CONTROL_RIGHT) {
                right = false;
            }
            return false;
        }
    }
}
