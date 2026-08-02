#pragma once
#include "raylib.h"
#include <array>

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
   Vector2    position;
   Vector2    velocity;
   Facing_t   facing;
   Activity_t activity;

   AnimId animID;

   int   currentFrame;
   float frameTimer;
};

void handleInput( Player_t& player );

void updatePlayer(
    Player_t& player, float dt,
    const std::array<Animation_t, ( size_t ) AnimId::Count>& animations );

void drawPlayer(
    const Player_t&                                          player,
    const std::array<Animation_t, ( size_t ) AnimId::Count>& animations );
