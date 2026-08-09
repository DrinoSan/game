#pragma once

#include "Animation.h"
#include "TextureStore.h"
#include <utility>

namespace anim
{
AnimId selectAnimation( Activity_t activity, Facing_t facing );

void advanceAnimation(
    Activity_t activity, Facing_t facing, float& frametimer, int& currentframe,
    float dt,
    const std::array<Animation_t, std::to_underlying( AnimId::Count )>&
        animations );
};   // namespace anim

namespace render
{
void drawEntity(
    const Vector2& position, const Activity_t& activity, const Facing_t& facing,
    int                                                      currentFrame,
    const std::array<Animation_t, ( size_t ) AnimId::Count>& animations,
    const TextureStore_t&                                    store );

};   // namespace render
