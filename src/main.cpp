// System Headers
#include <array>
#include <cstddef>
#include <print>

#include "Animation.h"
#include "AnimationSystem.h"
#include "MovementSystem.h"
#include "Player.h"
#include "TileMap.h"

// Local Headers
#include "raylib.h"

int main( int argc, char* argv[] )
{
   Player_t player;
   player.activity     = Activity_t::Idle;
   player.currentFrame = 0;
   player.frameTimer   = 0;
   player.facing       = Facing_t::DOWN;
   player.position     = { 350, 200 };
   player.velocity     = { 0, 0 };

   std::println( "Init" );
   InitWindow( 800, 450, "Endless" );

   auto tileset = loadTileset( "../assets/map/sampleSheet.tsx" );
   auto map     = parseMap( "../assets/map/sampleMap.tmx" );

   std::array<Animation_t, ( size_t ) AnimId::Count> animations;
   auto walkUp    = Animation_t( "../assets/Wizard_Back_Walk_No_Weapon.png" );
   auto walkRight = Animation_t( "../assets/Wizard_Side_Walk_No_Weapon.png" );
   auto walkDown  = Animation_t( "../assets/Wizard_Front_Walk_No_Weapon.png" );
   auto walkLeft  = Animation_t( "../assets/Wizard_Side_Walk_No_Weapon.png" );

   std::println( "texture id: {}, width: {}", walkDown.texture.id,
                 walkDown.texture.width );
   std::println( "-----test {}", ( int ) tileset.texture.id );
   animations[ 0 ] = walkDown;
   animations[ 1 ] = walkUp;
   animations[ 2 ] = walkLeft;
   animations[ 3 ] = walkRight;

   SetTargetFPS( 60 );

   while ( !WindowShouldClose() )
   {
      BeginDrawing();
      ClearBackground( RAYWHITE );
      DrawText( "Endless", 350, 200, 20, DARKGRAY );

      handleInput( player );

      float dt = GetFrameTime();
      moveEntity( player.position, player.velocity, dt );

      drawMap( map, tileset, 1 );
      advanceAnimation( player.activity, player.facing, player.frameTimer,
                        player.currentFrame, dt, animations );

      drawEntity( player.position, player.activity, player.facing,
                  player.currentFrame, animations );

      EndDrawing();
   }

   CloseWindow();
   return 0;
}
