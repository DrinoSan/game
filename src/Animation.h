#pragma once
#include "raylib.h"

#include <string>

enum class AnimId
{
   WalkFront,
   WalkBack,
   WalkLeft,
   WalkRight,
   /* Idle, Attack later */ Count
};

struct Animation_t
{
   Texture2D texture;
   int       frameWidth;      // 32
   int       frameHeight;     // 32
   int       frameCount;      // 8
   float     frameDuration;   // 0.1s

   Animation_t( const std::string texturePath )
   {
      frameCount    = 8;
      frameDuration = 0.1f;
      texture       = LoadTexture( texturePath.c_str() );
      frameWidth    = texture.width / frameCount;
      frameHeight   = texture.height;
   }

   Animation_t() = default;
};
