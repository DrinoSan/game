#pragma once
#include "raylib.h"
#include <array>

#include "Animation.h"
#include "AnimationSystem.h"
#include "TileMap.h"

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

void handleInput( Player_t& player );

void drawPlayer(
    const Player_t&                                          player,
    const std::array<Animation_t, ( size_t ) AnimId::Count>& animations );
