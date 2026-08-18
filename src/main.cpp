// System Headers
#include <cstddef>
#include <print>

#include "Animation.h"
#include "AnimationSystem.h"
#include "Camera.h"
#include "MovementSystem.h"
#include "Player.h"
#include "StartupConfig.h"
#include "TextureStore.h"
#include "TileMap.h"

// Local Headers
#include "raylib.h"

int main()
{
   TextureStore_t textureStore;

   Player_t player{ .position{ 350, 200 },
                    .velocity{ 0, 0 },
                    .facing   = Facing_t::DOWN,
                    .activity = Activity_t::Idle,
                    .hitboxSize{ 12, 10 },
                    .currentFrame = 0,
                    .frameTimer   = 0 };

   InitWindow( 800, 450, "Endless" );

   Camera2D camera = { 0 };
   camera.target   = { player.position.x + 20.0f, player.position.y + 20.0f };
   camera.offset   = { 800 / 2.0f, 450 / 2.0f };
   camera.rotation = 0.0f;
   camera.zoom     = 1.0f;

   auto tileset =
       assets::loadTileset( "../assets/map/sampleSheet.tsx", textureStore );
   if ( !tileset.has_value() )
   {
      std::println( "Error loading tileset with error {}",
                    std::to_underlying( tileset.error() ) );
      return 1;
   }

   auto map_expected = assets::parseMap( "../assets/map/sampleMap.tmx" );
   if ( !map_expected.has_value() )
   {
      std::println( "Failed to parse map with error {}",
                    std::to_underlying( map_expected.error() ) );
      return 1;
   }

   auto map = std::move( map_expected.value() );

   auto animations = assets::prepareAnimations( textureStore );

   SetTargetFPS( 60 );

   while ( !WindowShouldClose() )
   {
      BeginDrawing();
      ClearBackground( RAYWHITE );
      BeginMode2D( camera );
      DrawText( "Endless", 350, 200, 20, DARKGRAY );

      input::handleInput( player );

      float dt = GetFrameTime();

      render::drawMap( map, tileset.value(), 1, textureStore );

      movement::step( player.position, player.hitboxSize, player.velocity, map,
                      tileset.value(), dt );

      camera::followPosition( camera, player.position );
      camera.zoom = expf( logf( camera.zoom ) +
                          ( ( float ) GetMouseWheelMove() * 0.1f ) );
      if ( camera.zoom > 3.0f )
         camera.zoom = 3.0f;
      else if ( camera.zoom < 1.5f )
         camera.zoom = 1.5f;

      anim::advanceAnimation( player.activity, player.facing, player.frameTimer,
                              player.currentFrame, dt, animations );

      render::drawEntity( player.position, player.activity, player.facing,
                          player.currentFrame, animations, textureStore );

      EndMode2D();
      EndDrawing();
   }

   unloadAll( textureStore );
   CloseWindow();
   return 0;
}
