// System Headers
#include <print>

#include "Animation.h"
#include "Player.h"

// Local Headers
#include "raylib.h"

int main( int argc, char* argv[] )
{
   std::array<Animation_t, ( size_t ) AnimId::Count> animations;
   Animation_t walkUp;
   Animation_t walkRight;
   Animation_t walkDown;
   Animation_t walkLeft;


   std::println( "Init" );
   InitWindow( 800, 450, "Endless" );
   SetTargetFPS( 60 );

   while ( !WindowShouldClose() )
   {
      BeginDrawing();
      ClearBackground( RAYWHITE );
      DrawText( "Endless", 350, 200, 20, DARKGRAY );
      EndDrawing();
   }

   CloseWindow();
   return 0;
}
