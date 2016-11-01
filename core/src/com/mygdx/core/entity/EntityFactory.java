package com.mygdx.core.entity;

import com.badlogic.ashley.core.Entity;
import com.badlogic.gdx.math.Vector2;
import com.mygdx.core.Main;
import com.mygdx.core.entity.components.*;

public class EntityFactory {

    public static Entity particle(int x, int y) {
        Entity entity = new Entity();

        PositionComponent positionC = new PositionComponent();
        if (x >= 32) {
            positionC.x = 32;
        } else {
            positionC.x = 31;
        }
        if (y >= 32) {
            positionC.y = 32;
        } else {
            positionC.y = 31;
        }
        PixelComponent squareC = new PixelComponent();
        ParticleComponent waveC = new ParticleComponent(new Vector2(positionC.x, positionC.y), new Vector2(x, y));

        entity.add(positionC)
            .add(squareC)
            .add(waveC);

        Main.engine.addEntity(entity);

        return entity;
    }

    public static Entity player() {
        Entity entity = new Entity();

        PositionComponent positionC = new PositionComponent();
        positionC.x = 0;
        positionC.y = 0;
        PixelComponent squareC = new PixelComponent();
        PlayerInputComponent playerInputC = new PlayerInputComponent();

        entity.add(positionC)
            .add(squareC)
            .add(playerInputC);

        Main.engine.addEntity(entity);

        return entity;
    }
}