package com.mygdx.core;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input;
import com.badlogic.gdx.Preferences;
import com.badlogic.gdx.ScreenAdapter;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.graphics.g2d.BitmapFont;
import com.badlogic.gdx.graphics.g2d.GlyphLayout;
import com.mygdx.core.entity.systems.ExpansionSystem;
import com.mygdx.core.entity.systems.GameoverSystem;
import com.mygdx.core.entity.systems.SpawnSystem;

public class MenuScreen extends ScreenAdapter
{
    OrthographicCamera camera;
    BitmapFont font = Main.assets.get(AssetPaths.FONT);
    GlyphLayout layout = new GlyphLayout();
    int lastScore = 0;
    int highScore = 0;
    String lastScoreString = "";
    String highScoreString = "";
    Preferences prefs;

    public MenuScreen()
    {
        float camWidth = Gdx.graphics.getWidth();
        float camHeight = Gdx.graphics.getHeight();
        camera = new OrthographicCamera(camWidth, camHeight);
        camera.position.set(camWidth / 2 / Constants.ZOOM, camHeight / 2 / Constants.ZOOM, 0f);
        camera.zoom = 1f / Constants.ZOOM;
        camera.update();
        prefs = Gdx.app.getPreferences("score");
        lastScore = prefs.getInteger("lastscore", 0);
        highScore = prefs.getInteger("highscore", 0);
    }

    public void render(float deltaTime)
    {
        Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);

        Main.batch.setProjectionMatrix(camera.combined);
        Main.batch.begin();
        layout.setText(font, highScoreString);
        font.draw(Main.batch, highScoreString, 32f - layout.width/2, 42f + layout.height / 2);
        layout.setText(font, lastScoreString);
        font.draw(Main.batch, lastScoreString, 32f - layout.width/2, 22f + layout.height / 2);
        Main.batch.end();

        Main.engine.update(deltaTime);

        if (Gdx.input.isKeyPressed(Input.Keys.ENTER) || Gdx.input.isKeyPressed(Input.Keys.UP)) {
            // Reactivate game systems
            Main.engine.getSystem(SpawnSystem.class).setProcessing(true);
            Main.engine.getSystem(ExpansionSystem.class).setProcessing(true);
            Main.engine.getSystem(GameoverSystem.class).setProcessing(true);
            Main.game.setScreen(Main.gameScreen);
        }
    }

    public void show() {
        lastScore = (int)Gamedata.lastScore;
        if (lastScore > highScore) {
            highScore = lastScore;
        }
        lastScoreString = Integer.toString(lastScore);
        highScoreString = Integer.toString(highScore);
        prefs.putInteger("highscore", highScore);
        prefs.putInteger("lastscore", lastScore);
        prefs.flush();
    }
}