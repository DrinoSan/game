// System Headers
#include <array>
#include <cstddef>
#include <print>
#include <utility>

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

   auto tileset =
       update::loadTileset( "../assets/map/sampleSheet.tsx", textureStore );
   if ( !tileset.has_value() )
   {
      std::println( "Error loading tileset with error {}",
                    std::to_underlying( tileset.error() ) );
      return 1;
   }

   auto map_expected = update::parseMap( "../assets/map/sampleMap.tmx" );
   if ( !map_expected.has_value() )
   {
      std::println( "Failed to parse map with error {}",
                    std::to_underlying( map_expected.error() ) );
      return 1;
   }

   auto map = map_expected.value();

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
      movement::moveEntity( player.position, player.velocity, dt );

      render::drawMap( map, tileset.value(), 1, textureStore );
      update::advanceAnimation( player.activity, player.facing,
                                player.frameTimer, player.currentFrame, dt,
                                animations );

      render::drawEntity( player.position, player.activity, player.facing,
                          player.currentFrame, animations, textureStore );

      EndDrawing();
   }

   unloadAll( textureStore );
   CloseWindow();
   return 0;
}
