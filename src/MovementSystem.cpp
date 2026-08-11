#include <cmath>
#include <print>

#include "MovementSystem.h"
#include "TileMap.h"
#include "raylib.h"

namespace movement
{

void moveEntity( Vector2& position, const Vector2& velocity, float dt )
{
   position.x += velocity.x * dt;
   position.y += velocity.y * dt;
}

void step( Vector2& position, const Vector2& hitboxSize,
           const Vector2& velocity, const TileMap_t& map, const Tileset_t& set,
           float dt )
{
   auto oldPosition = position;
   position.x += velocity.x * dt;

   Rectangle hitbox =
       collision::getHitboxByPositionAndSize( position, hitboxSize );

   if ( collision::collides( hitbox, map, set ) )
   {
      position.x = oldPosition.x;
   }

   position.y += velocity.y * dt;

   hitbox = collision::getHitboxByPositionAndSize( position, hitboxSize );
   if ( collision::collides( hitbox, map, set ) )
   {
      position.y = oldPosition.y;
   }
}
};   // namespace movement

namespace collision
{
Rectangle getHitboxByPositionAndSize( const Vector2& position,
                                      const Vector2& hitboxSize )
{
   return { position.x - hitboxSize.x / 2, position.y - hitboxSize.y,
            hitboxSize.x, hitboxSize.y };
}

bool collides( Rectangle hitbox, const TileMap_t& map,
               const Tileset_t& tileset )
{
   auto tileSize = tileset.tileSize;
   DrawRectangleLinesEx( hitbox, 100.0f, GOLD );

   double minTileX = std::floor( hitbox.x / tileSize );
   double maxTileX = std::floor( ( hitbox.x + hitbox.width - 0.001 ) / tileSize );

   double minTileY = std::floor( hitbox.y / tileSize );
   double maxTileY =
       std::floor( ( hitbox.y + hitbox.height - 0.001 ) / tileSize );

   for ( auto y = minTileY; y <= maxTileY; ++y )
   {
      if ( y >= map.height || y < 0 )
      {
         return true;
      }

      for ( auto x = minTileX; x <= maxTileX; ++x )
      {
         if ( x >= map.width || x < 0 )
         {
            return true;
         }
         const auto& index = map.tiles[ y * map.width + x ];
         if ( index == -1 )
         {
            continue;
         }

         if ( tileset.tileDefs[ index ].walkable == false )
         {
            return true;
         }
      }
   }

   return false;
}

};   // namespace collision
