#include <array>
#include <utility>

#include "Animation.h"
#include "AnimationSystem.h"
#include "TextureStore.h"
#include "raylib.h"

namespace anim
{
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
   return AnimId::Idle;
}

void advanceAnimation(
    Activity_t activity, Facing_t facing, float& frametimer, int& currentframe,
    float                                                    dt,
    const std::array<Animation_t, ( size_t ) AnimId::Count>& animations )
{
   AnimId      animid          = selectAnimation( activity, facing );
   const auto& playeranimation = animations[ std::to_underlying( animid ) ];

   frametimer += dt;
   if ( frametimer > playeranimation.frameDuration )
   {
      frametimer -= playeranimation.frameDuration;
      currentframe++;
      if ( currentframe >= playeranimation.frameCount )
      {
         currentframe = 0;
      }
   }
}

};   // namespace anim

namespace render
{
void drawEntity(
    const Vector2& position, const Activity_t& activity, const Facing_t& facing,
    int                                                      currentFrame,
    const std::array<Animation_t, ( size_t ) AnimId::Count>& animations,
    const TextureStore_t&                                    store )
{
   AnimId      animID          = anim::selectAnimation( activity, facing );
   const auto& playerAnimation = animations[ ( size_t ) animID ];
   Rectangle   source          = { 0, 0, ( float ) playerAnimation.frameWidth,
                                   ( float ) playerAnimation.frameHeight };

   if ( facing == Facing_t::LEFT )
   {
      source.width = -playerAnimation.frameWidth;
   }

   source.x = currentFrame * playerAnimation.frameWidth;

   // the true center (where position says the player is)
   DrawCircle( ( int ) position.x, ( int ) position.y, 3, RED );
   // the dest rectangle's left edge, so we can see the frame box
   float destX = position.x - playerAnimation.frameWidth / 2.0f;
   DrawRectangleLines(
       ( int ) destX,
       ( int ) ( position.y - playerAnimation.frameHeight / 2.0f ),
       playerAnimation.frameWidth, playerAnimation.frameHeight, GREEN );

   DrawTexturePro( store.textures[ playerAnimation.textureIndex ], source,
                   { position.x - playerAnimation.frameWidth / 2.0f,
                     position.y - playerAnimation.frameHeight / 2.0f,
                     ( float ) playerAnimation.frameWidth,
                     ( float ) playerAnimation.frameHeight },
                   { 0, 0 }, 0, WHITE );
}

};   // namespace render
