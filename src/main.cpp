// System Headers
#include <array>
#include <cstddef>
#include <print>

#include "Animation.h"
#include "AnimationSystem.h"
#include "MovementSystem.h"
#include "Player.h"
#include "TextureStore.h"
#include "TileMap.h"

// Local Headers
#include "raylib.h"

int main()
{
   TextureStore_t textureStore;

   Player_t player;
   player.activity     = Activity_t::Idle;
   player.currentFrame = 0;
   player.frameTimer   = 0;
   player.facing       = Facing_t::DOWN;
   player.position     = { 350, 200 };
   player.velocity     = { 0, 0 };

   std::println( "Init" );
   InitWindow( 800, 450, "Endless" );

   auto tileset = loadTileset( "../assets/map/sampleSheet.tsx", textureStore );
   auto map     = parseMap( "../assets/map/sampleMap.tmx" );

   std::array<Animation_t, ( size_t ) AnimId::Count>       animations;
   std::array<const std::string, ( size_t ) AnimId::Count> texturePaths{
       "../assets/Wizard_Front_Walk_No_Weapon.png",
       "../assets/Wizard_Back_Walk_No_Weapon.png",
       "../assets/Wizard_Side_Walk_No_Weapon.png",
       "../assets/Wizard_Side_Walk_No_Weapon.png" };

   int textureCounter = 0;
   for ( const auto& path : texturePaths )
   {
      auto res = getTextureIndex( textureStore, path );
      if ( res == -1 )
      {
         std::println( "Cant load texture at path {}", path );
         return 0;
      }

      auto& animation         = animations[ textureCounter ];
      animation.textureIndex  = res;
      animation.frameCount    = 8;
      animation.frameDuration = 0.1;
      animation.frameWidth =
          textureStore.textures[ res ].width / animation.frameCount;
      animation.frameHeight = textureStore.textures[ res ].height;

      ++textureCounter;
   }

   SetTargetFPS( 60 );

   while ( !WindowShouldClose() )
   {
      BeginDrawing();
      ClearBackground( RAYWHITE );
      DrawText( "Endless", 350, 200, 20, DARKGRAY );

      handleInput( player );

      float dt = GetFrameTime();
      moveEntity( player.position, player.velocity, dt );

      drawMap( map, tileset, 1, textureStore );
      advanceAnimation( player.activity, player.facing, player.frameTimer,
                        player.currentFrame, dt, animations );

      drawEntity( player.position, player.activity, player.facing,
                  player.currentFrame, animations, textureStore );

      EndDrawing();
   }

   unloadAll( textureStore );
   CloseWindow();
   return 0;
}
