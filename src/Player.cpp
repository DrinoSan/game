#include <cmath>

#include "Animation.h"
#include "Player.h"
#include "raylib.h"

struct FacingAndActivity_t
{
   Facing_t   facing;
   Activity_t activity;
};

FacingAndActivity_t getFacingAndActivity( const Vector2& velocity )
{
   if ( velocity.x == 0 && velocity.y == 0 )
   {
      return { Facing_t::DOWN, Activity_t::Idle };
   }

   auto absX = std::abs( velocity.x );
   auto absY = std::abs( velocity.y );

   if ( absX > absY )
   {
      // We know X is bigger meaning we move mainly left or right
      if ( velocity.x > 0 )
      {
         return { Facing_t::RIGHT, Activity_t::Walk };
      }

      if ( velocity.x < 0 )
      {
         return { Facing_t::LEFT, Activity_t::Walk };
      }
   }

   // We know we move mainly up or down
   if ( velocity.y < 0 )
   {
      return { Facing_t::UP, Activity_t::Walk };
   }

   return { Facing_t::DOWN, Activity_t::Walk };
}

namespace input
{

void handleInput( Player_t& player )
{
   player.velocity = { 0, 0 };

   if ( IsKeyDown( KEY_W ) )
   {
      player.velocity.y -= 100;
   }
   if ( IsKeyDown( KEY_D ) )
   {
      player.velocity.x += 100;
   }
   if ( IsKeyDown( KEY_S ) )
   {
      player.velocity.y += 100;
   }
   if ( IsKeyDown( KEY_A ) )
   {
      player.velocity.x -= 100;
   }

   auto [ facing, activity ] = getFacingAndActivity( player.velocity );
   player.facing             = facing;
   player.activity           = activity;

   // Normalize velocity
   auto hyp = std::sqrt( ( player.velocity.x * player.velocity.x ) +
                         ( player.velocity.y * player.velocity.y ) );

   if ( hyp != 0 )
   {
      player.velocity.x = player.velocity.x / hyp * 100;
      player.velocity.y = player.velocity.y / hyp * 100;
   }
}

};   // namespace input
