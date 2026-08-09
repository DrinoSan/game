#pragma once
#include <vector>

#include "raylib.h"
#include "TextureStore.h"

struct TileDef_t
{
   bool walkable = true;
   // damage
   // friction
   // usw
};

// one specific map's layout
struct TileMap_t
{
   int              width;
   int              height;
   std::vector<int> tiles;
};

// source art
// Describes where the tile is in the png when index is provided
struct Tileset_t
{
   TextureIndex           textureIndex;
   int                    tileSize;
   int                    spacing;
   int                    columns;
   std::vector<TileDef_t> tileDefs;
};

void drawMap( const TileMap_t& map, const Tileset_t& tileset, int scale,
              const TextureStore_t& store );

Tileset_t loadTileset( const std::string& tsxPath, TextureStore_t& store );

TileMap_t parseMap( const std::string& path );
