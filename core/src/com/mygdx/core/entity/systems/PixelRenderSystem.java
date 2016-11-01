package com.mygdx.core.entity.systems;

import com.badlogic.ashley.core.Entity;
import com.badlogic.ashley.core.Family;
import com.badlogic.ashley.systems.IteratingSystem;
import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.graphics.glutils.ShapeRenderer;
import com.mygdx.core.entity.Mappers;
import com.mygdx.core.entity.components.PixelComponent;
import com.mygdx.core.entity.components.PositionComponent;

/*
 * Draws a pixel at the position of the entity
 */
public class PixelRenderSystem extends IteratingSystem {
    ShapeRenderer shapeRenderer = new ShapeRenderer();
    OrthographicCamera camera;

    public PixelRenderSystem(OrthographicCamera camera) {
        super(Family.all(PixelComponent.class, PositionComponent.class).get());
        this.camera = camera;
    }

    public PixelRenderSystem(int priority, OrthographicCamera camera) {
        super(Family.all(PixelComponent.class, PositionComponent.class).get(), priority);
        this.camera = camera;
    }

    @Override
    public void update(float deltaTime) {
        shapeRenderer.setProjectionMatrix(camera.combined);
        shapeRenderer.begin(ShapeRenderer.ShapeType.Filled);
        shapeRenderer.setColor(Color.WHITE);
        super.update(deltaTime);
        shapeRenderer.setColor(Color.BLACK);
        shapeRenderer.rect(31, 31, 1f, 1f);
        shapeRenderer.rect(31, 32, 1f, 1f);
        shapeRenderer.rect(32, 31, 1f, 1f);
        shapeRenderer.rect(32, 32, 1f, 1f);
        shapeRenderer.end();
    }

    public void processEntity(Entity entity, float deltaTime) {
        PositionComponent positionC = Mappers.position.get(entity);

        shapeRenderer.rect(positionC.x, positionC.y, 1f, 1f);
    }
}
