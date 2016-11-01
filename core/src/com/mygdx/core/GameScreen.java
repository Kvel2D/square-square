package com.mygdx.core;

import com.badlogic.ashley.core.Entity;
import com.badlogic.ashley.core.Family;
import com.badlogic.ashley.utils.ImmutableArray;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.ScreenAdapter;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.OrthographicCamera;
import com.mygdx.core.entity.EntityFactory;
import com.mygdx.core.entity.components.ParticleComponent;
import com.mygdx.core.entity.systems.*;

public class GameScreen extends ScreenAdapter {
    public enum STATE {
        NORMAL, GAMEOVER
    }
    public STATE state = STATE.NORMAL;
    OrthographicCamera camera;

    public GameScreen() {
        float camWidth = Gdx.graphics.getWidth();
        float camHeight = Gdx.graphics.getHeight();
        camera = new OrthographicCamera(camWidth, camHeight);
        camera.position.set(camWidth / 2 / Constants.ZOOM, camHeight / 2 / Constants.ZOOM, 0f);
        camera.zoom = 1f / Constants.ZOOM;
        camera.update();

        Main.engine.addSystem(new PlayerInputSystem(0));
        Main.engine.addSystem(new SpawnSystem(20));
        Main.engine.addSystem(new ExpansionSystem(40));
        Main.engine.addSystem(new GameoverSystem(41));
        Main.engine.addSystem(new PixelRenderSystem(60, camera));

        EntityFactory.player();
        Main.engine.getSystem(SpawnSystem.class).setProcessing(true);
        Main.engine.getSystem(ExpansionSystem.class).setProcessing(true);
        Main.engine.getSystem(GameoverSystem.class).setProcessing(true);
        PlayerInputSystem playerInputSystem = Main.engine.getSystem(PlayerInputSystem.class);
        Gdx.input.setInputProcessor(playerInputSystem.inputProcessor);
    }

    public void render(float deltaTime) {
        switch (state) {
            case NORMAL: {
                Gamedata.lastScore += deltaTime;
                Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);
                Main.engine.update(deltaTime);
                break;
            }
            case GAMEOVER: {
                ImmutableArray<Entity> particles = Main.engine.getEntitiesFor(Family.all(ParticleComponent.class).get());
                for (int i = particles.size() - 1; i >= 0; i--) {
                    Main.engine.removeEntity(particles.get(i));
                }
                Main.engine.getSystem(SpawnSystem.class).setProcessing(false);
                Main.engine.getSystem(ExpansionSystem.class).setProcessing(false);
                Main.engine.getSystem(GameoverSystem.class).setProcessing(false);
                Main.game.setScreen(Main.menuScreen);
                state = STATE.NORMAL;
                break;
            }
        }
    }
}
