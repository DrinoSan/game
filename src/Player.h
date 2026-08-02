#pragma once
#include "raylib.h"

#include "Animation.h"

enum class Facing_t
{
   UP,
   RIGHT,
   DOWN,
   LEFT
};

enum class Activity_t
{
   Idle,
   Walk,
   Attack,
   Hurt,
   Die
};

struct Player_t
{
   Vector2  position;
   Vector2  velocity;
   Facing_t facing;
   Activity_t activity;

   AnimId id;

   int   currentFrame;
   float frameTimer;
};


AnimationChoice_t selectAnimation(Activity_t activity, Facing_t facing);
