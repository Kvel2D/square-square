package com.mygdx.core.entity.systems;

import com.badlogic.ashley.core.Engine;
import com.badlogic.ashley.core.Entity;
import com.badlogic.ashley.core.EntitySystem;
import com.badlogic.ashley.core.Family;
import com.badlogic.ashley.utils.ImmutableArray;
import com.badlogic.gdx.audio.Sound;
import com.badlogic.gdx.math.MathUtils;
import com.mygdx.core.AssetPaths;
import com.mygdx.core.Constants;
import com.mygdx.core.Gamedata;
import com.mygdx.core.Main;
import com.mygdx.core.entity.Mappers;
import com.mygdx.core.entity.components.ParticleComponent;
import com.mygdx.core.entity.components.PositionComponent;

/*
 * Expands all particles outwards from the center
 * removes particles when they hit the border and plays a sound
 * fills the Gamedata grid with particle locations
 */
public class ExpansionSystem extends EntitySystem {
    ImmutableArray<Entity> entities;
    Sound sound1;
    Sound sound2;
    boolean soundPlayed = false;
    int soundNumber = 1;
    float particleTime = 1f; // time it takes for the particle to go from center to the edge of the screen

    public ExpansionSystem() {
        sound1 = Main.assets.get(AssetPaths.SOUND1);
        sound2 = Main.assets.get(AssetPaths.SOUND2);
    }

    public ExpansionSystem(int priority) {
        super(priority);
        sound1 = Main.assets.get(AssetPaths.SOUND1);
        sound2 = Main.assets.get(AssetPaths.SOUND2);
    }

    @Override
    public void addedToEngine(Engine engine) {
        entities = engine.getEntitiesFor(Family.all(ParticleComponent.class, PositionComponent.class).get());
    }

    public void update(float deltaTime) {
        soundPlayed = false;

        // Clear Gamedata.grid
        for (int j = 0; j < Gamedata.grid.length; j++) {
            for (int k = 0; k < Gamedata.grid[j].length; k++) {
                Gamedata.grid[j][k] = false;
            }
        }
        // Expand all pixels on the grid
        for (int i = 0; i < entities.size(); ++i) {
            processEntity(entities.get(i), deltaTime);
        }
        // Fill Gamedata.grid
        for (int i = 0; i < entities.size(); ++i) {
            PositionComponent positionC = Mappers.position.get(entities.get(i));
            Gamedata.grid[positionC.x][positionC.y] = true;
        }
    }

    private void processEntity(Entity entity, float deltaTime) {
        PositionComponent positionC = Mappers.position.get(entity);
        ParticleComponent particleC = Mappers.particle.get(entity);

        particleC.timer += deltaTime;

        // Increase position away from center
        // Timer value is multiplied by 1.5f to increase top speed
        int x = MathUtils.round(MathUtils.lerp(particleC.start.x, particleC.destination.x, (particleC.timer * 1.5f) / particleTime));
        int y = MathUtils.round(MathUtils.lerp(particleC.start.y, particleC.destination.y, (particleC.timer * 1.5f) / particleTime));

        // Remove particles exiting the grid
        if (x < 0 || y < 0 || x >= Constants.VIEWPORT_WIDTH || y >= Constants.VIEWPORT_HEIGHT) {
            getEngine().removeEntity(entity);
            if (!soundPlayed) {
                if (soundNumber == 1) {
                    sound1.play();
                    soundNumber = 2;
                } else {
                    sound2.play();
                    soundNumber = 1;
                }
                soundPlayed = true;
            }
        } else {
            positionC.x = x;
            positionC.y = y;
        }
    }
}
