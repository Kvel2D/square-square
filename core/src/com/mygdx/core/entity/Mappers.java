package com.mygdx.core.entity;

import com.badlogic.ashley.core.ComponentMapper;
import com.mygdx.core.entity.components.*;

public class Mappers
{
    public static ComponentMapper<PlayerInputComponent> playerInput = ComponentMapper.getFor(PlayerInputComponent.class);
    public static ComponentMapper<PixelComponent> pixel = ComponentMapper.getFor(PixelComponent.class);
    public static ComponentMapper<PositionComponent> position = ComponentMapper.getFor(PositionComponent.class);
    public static ComponentMapper<ParticleComponent> particle = ComponentMapper.getFor(ParticleComponent.class);
}
