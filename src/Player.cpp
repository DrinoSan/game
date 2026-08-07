#include "Player.h"
#include "TileMap.h"

void handleInput( Player_t& player )
{
   player.velocity = { 0, 0 };

   if ( IsKeyDown( KEY_W ) )
   {
      player.velocity.y -= 5;
      player.facing   = Facing_t::UP;
      player.activity = Activity_t::Walk;
   }
   if ( IsKeyDown( KEY_D ) )
   {
      player.velocity.x += 5;
      player.facing   = Facing_t::RIGHT;
      player.activity = Activity_t::Walk;
   }
   if ( IsKeyDown( KEY_S ) )
   {
      player.velocity.y += 5;
      player.facing   = Facing_t::DOWN;
      player.activity = Activity_t::Walk;
   }
   if ( IsKeyDown( KEY_A ) )
   {
      player.velocity.x -= 5;
      player.facing   = Facing_t::LEFT;
      player.activity = Activity_t::Walk;
   }
}
