package com.mygdx.core;

import com.badlogic.ashley.core.Engine;
import com.badlogic.gdx.ApplicationAdapter;
import com.badlogic.gdx.Game;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.assets.AssetManager;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;

import java.util.Random;

public class Main extends ApplicationAdapter
{
    public static Game game = new Game()
    {
        public void create()
        {
            this.setScreen(new LoadScreen());
        }
    };
    public static AssetManager assets = new AssetManager();
    public static Engine engine = new Engine();
    public static SpriteBatch batch;
    public static Random rand = new Random();
    public static GameScreen gameScreen;
    public static MenuScreen menuScreen;

    public void create()
    {
        batch = new SpriteBatch();
        Texture.setAssetManager(assets);
        game.create();
        Gdx.gl.glClearColor(0f, 0f, 0f, 1f);
    }

    public void render()
    {
        game.render();
    }

    public void dispose()
    {
        assets.dispose();
        batch.dispose();
    }
}