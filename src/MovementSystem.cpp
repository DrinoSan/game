#include "MovementSystem.h"

namespace movement
{

void moveEntity( Vector2& position, const Vector2& velocity, float dt )
{
   position.x += velocity.x * dt;
   position.y += velocity.y * dt;
}
};   // namespace movement

namespace collision
{
bool collides( Rectangle hitbox, const TileMap_t& map,
               const Tileset_t& tileset )
{

   return false;
}

};   // namespace collision
