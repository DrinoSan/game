#pragma once

#include <vector>
#include <string>

#include "raylib.h"

using TextureIndex = int;

struct TextureStore_t
{
   std::vector<Texture2D>   textures;
   std::vector<std::string> paths;

   ~TextureStore_t();

   TextureStore_t() = default;

   TextureStore_t( const TextureStore_t& other )          = delete;
   TextureStore_t& operator=( const TextureStore_t& other ) = delete;
};

TextureIndex getTextureIndex( TextureStore_t&    store,
                              const std::string& path );

void unloadAll( TextureStore_t& store );
