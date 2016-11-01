package com.mygdx.core.desktop;

import com.badlogic.gdx.backends.lwjgl.LwjglApplication;
import com.badlogic.gdx.backends.lwjgl.LwjglApplicationConfiguration;
import com.mygdx.core.Constants;
import com.mygdx.core.Main;

public class DesktopLauncher {
	public static void main (String[] arg) {
		LwjglApplicationConfiguration config = new LwjglApplicationConfiguration();
		config.width = Constants.VIEWPORT_WIDTH * Constants.ZOOM;
		config.height = Constants.VIEWPORT_HEIGHT * Constants.ZOOM;
		config.resizable = false;
		config.title = "SQUARE SQUARE";

		new LwjglApplication(new Main(), config);
	}
}
