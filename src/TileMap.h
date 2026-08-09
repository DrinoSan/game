#pragma once
#include <expected>
#include <vector>

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

// This can be extended to have a precise info about the error
enum class TilesetError_t
{
   general_error,
};

namespace render
{
void drawMap( const TileMap_t& map, const Tileset_t& tileset, int scale,
              const TextureStore_t& store );
};

enum class TileMapError_t
{
   general_error,
};

namespace assets
{
std::expected<Tileset_t, TilesetError_t>
loadTileset( const std::string& tsxPath, TextureStore_t& store );

std::expected<TileMap_t, TileMapError_t> parseMap( const std::string& path );
};   // namespace assets
