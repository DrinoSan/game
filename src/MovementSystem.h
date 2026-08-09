#pragma once

#include "TileMap.h"
#include "raylib.h"

namespace movement
{
void moveEntity( Vector2& position, const Vector2& velocity, float dt );

bool collides( Rectangle hitbox, const TileMap_t& map, const Tileset_t& tileset,
               int scale );
};   // namespace movement
