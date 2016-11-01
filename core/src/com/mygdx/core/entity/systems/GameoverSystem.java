package com.mygdx.core.entity.systems;

import com.badlogic.ashley.core.Entity;
import com.badlogic.ashley.core.Family;
import com.badlogic.ashley.systems.IteratingSystem;
import com.badlogic.gdx.audio.Sound;
import com.mygdx.core.AssetPaths;
import com.mygdx.core.GameScreen;
import com.mygdx.core.Gamedata;
import com.mygdx.core.Main;
import com.mygdx.core.entity.Mappers;
import com.mygdx.core.entity.components.PlayerInputComponent;
import com.mygdx.core.entity.components.PositionComponent;

/*
 * Ends the game and plays a sound, if the player collides with a particle
 */
public class GameoverSystem extends IteratingSystem {
    Sound gameoverSound = Main.assets.get(AssetPaths.GAMEOVER_SOUND);

    public GameoverSystem() {
        super(Family.all(PlayerInputComponent.class).get());
    }

    public GameoverSystem(int priority) {
        super(Family.all(PlayerInputComponent.class, PositionComponent.class).get(), priority);
    }

    public void processEntity(Entity entity, float deltaTime) {
        PositionComponent transformC = Mappers.position.get(entity);

        if (Gamedata.grid[transformC.x][transformC.y]) {
            gameoverSound.play();
            Main.gameScreen.state = GameScreen.STATE.GAMEOVER;
        }
    }
}