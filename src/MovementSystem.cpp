#include "MovementSystem.h"

namespace movement
{

void moveEntity( Vector2& position, const Vector2& velocity, float dt )
{
   position.x += velocity.x * dt;
   position.y += velocity.y * dt;
}

bool collides( Rectangle hitbox, const TileMap_t& map, const Tileset_t& tileset,
               int scale )
{

   return false;
}

};   // namespace movement
