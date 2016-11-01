package com.mygdx.core.entity.components;

import com.badlogic.ashley.core.Component;
import com.badlogic.gdx.math.Vector2;

public class ParticleComponent implements Component{
    public Vector2 start;
    public Vector2 destination;
    public float timer = 0f;

    public ParticleComponent(Vector2 start, Vector2 destination) {
        this.start = start;
        this.destination = destination;
    }
}
