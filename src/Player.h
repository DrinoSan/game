#pragma once
#include "raylib.h"

#include "Animation.h"

struct Player_t
{
   Vector2    position;
   Vector2    velocity;
   Facing_t   facing;
   Activity_t activity;
   Vector2    hitboxSize;

   AnimId animID;

   int   currentFrame;
   float frameTimer;
};

namespace input
{
void handleInput( Player_t& player );
};
