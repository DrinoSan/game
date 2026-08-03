#pragma once
#include "raylib.h"
#include <vector>

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
   Texture2D              texture;
   int                    tileSize;
   int                    spacing;
   int                    columns;
   std::vector<TileDef_t> tileDefs;
};

void drawMap( const TileMap_t& map, const Tileset_t& tileset, int scale );

Tileset_t loadTileset( const std::string& tsxPath );

TileMap_t parseMap( const std::string& path );
