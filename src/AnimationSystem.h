#pragma once

#include "Animation.h"

AnimId selectAnimation( Activity_t activity, Facing_t facing );

void advanceAnimation(
    Activity_t activity, Facing_t facing, float& frametimer, int& currentframe,
    float                                                    dt,
    const std::array<Animation_t, ( size_t ) AnimId::Count>& animations );

void drawEntity(
    const Vector2& position, const Activity_t& activity, const Facing_t& facing,
    int                                                      currentFrame,
    const std::array<Animation_t, ( size_t ) AnimId::Count>& animations );
