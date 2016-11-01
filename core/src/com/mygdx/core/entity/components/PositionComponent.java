package com.mygdx.core.entity.components;

import com.badlogic.ashley.core.Component;

public class PositionComponent implements Component
{
    public int x;
    public int y;

    public PositionComponent() {
        this.x = 0;
        this.y = 0;
    }

    public PositionComponent(int x, int y) {
        this.x = x;
        this.y = y;
    }
}