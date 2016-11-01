package com.mygdx.core;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.ScreenAdapter;
import com.badlogic.gdx.audio.Sound;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.g2d.BitmapFont;

public class LoadScreen extends ScreenAdapter
{
    float minimumShowTime = 0f;

    public LoadScreen()
    {
        Main.assets.load(AssetPaths.SOUND1, Sound.class);
        Main.assets.load(AssetPaths.SOUND2, Sound.class);
        Main.assets.load(AssetPaths.GAMEOVER_SOUND, Sound.class);
        Main.assets.load(AssetPaths.FONT, BitmapFont.class);
        Main.assets.finishLoading();

        Main.gameScreen = new GameScreen();
        Main.menuScreen = new MenuScreen();
    }

    public void render(float deltaTime)
    {
        Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);

        minimumShowTime -= deltaTime;
        if (Gdx.input.justTouched())
            minimumShowTime = 0f;
        if (minimumShowTime <= 0 && Main.assets.update())
            Main.game.setScreen(Main.gameScreen);
    }
}
