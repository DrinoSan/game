#pragma once

#include "TileMap.h"
#include "raylib.h"

namespace movement
{
void moveEntity( Vector2& position, const Vector2& velocity, float dt );

void step( Vector2& position, const Vector2& hitboxSize, const Vector2& velocity,
           const TileMap_t& map, const Tileset_t& set, float dt );
};   // namespace movement

namespace collision
{
Rectangle getHitboxByPositionAndSize( const Vector2& position,
                                      const Vector2& hitboxSize );

bool collides( Rectangle& hitbox, const TileMap_t& map,
               const Tileset_t& tileset );
};   // namespace collision
