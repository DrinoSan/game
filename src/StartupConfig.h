#pragma once

#include <array>
#include <utility>

#include "Animation.h"
#include "TextureStore.h"

namespace assets
{
struct assetConfigData_t
{
   AnimId      animID;
   int         frameCount;
   float       frameDuration;
   const char* path;
};


std::array<Animation_t, std::to_underlying( AnimId::Count )>
prepareAnimations( TextureStore_t& textureStore );

};   // namespace assets
