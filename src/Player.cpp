#include "Player.h"

AnimId selectAnimation( Activity_t activity, Facing_t facing )
{
   if ( activity == Activity_t::Walk )
   {
      if ( facing == Facing_t::UP )
      {
         return AnimId::WalkBack;
      }
      else if ( facing == Facing_t::RIGHT )
      {
         return AnimId::WalkRight;
      }
      else if ( facing == Facing_t::DOWN )
      {
         return AnimId::WalkFront;
      }
      else if ( facing == Facing_t::LEFT )
      {
         return AnimId::WalkLeft;
      }
   }

   // For now i dont care
   return AnimId::WalkFront;
}
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

void updatePlayer(
    Player_t& player, float dt,
    const std::array<Animation_t, ( size_t ) AnimId::Count>& animations )
{
   player.position.x += player.velocity.x * dt;
   player.position.y += player.velocity.y * dt;

   player.animID = selectAnimation( player.activity, player.facing );
   const auto& playerAnimation = animations[ ( size_t ) player.animID ];
   Rectangle   source          = { 0, 0, ( float ) playerAnimation.frameWidth,
                                   ( float ) playerAnimation.frameHeight };
   player.frameTimer += dt;
   if ( player.frameTimer > playerAnimation.frameDuration )
   {
      player.frameTimer -= playerAnimation.frameDuration;
      player.currentFrame++;
      if ( player.currentFrame >= playerAnimation.frameCount )
      {
         player.currentFrame = 0;
      }
   }
}

void drawPlayer(
    const Player_t&                                          player,
    const std::array<Animation_t, ( size_t ) AnimId::Count>& animations )
{
   const auto& playerAnimation = animations[ ( size_t ) player.animID ];
   Rectangle   source          = { 0, 0, ( float ) playerAnimation.frameWidth,
                                   ( float ) playerAnimation.frameHeight };

   if ( player.facing == Facing_t::LEFT )
   {
      source.width = -playerAnimation.frameWidth;
   }

   source.x = player.currentFrame * playerAnimation.frameWidth;

   // the true center (where position says the player is)
   DrawCircle( ( int ) player.position.x, ( int ) player.position.y, 3, RED );
   // the dest rectangle's left edge, so we can see the frame box
   float destX = player.position.x - playerAnimation.frameWidth / 2.0f;
   DrawRectangleLines(
       ( int ) destX,
       ( int ) ( player.position.y - playerAnimation.frameHeight / 2.0f ),
       playerAnimation.frameWidth, playerAnimation.frameHeight, GREEN );

   DrawTexturePro( playerAnimation.texture, source,
                   { player.position.x - playerAnimation.frameWidth / 2.0f,
                     player.position.y - playerAnimation.frameHeight / 2.0f,
                     ( float ) playerAnimation.frameWidth,
                     ( float ) playerAnimation.frameHeight },
                   { 0, 0 }, 0, WHITE );
}
