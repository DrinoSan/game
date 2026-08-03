#include "TileMap.h"
#include "raylib.h"
#include "tinyxml2.h"

#include <cctype>
#include <print>
#include <sstream>
#include <vector>

void drawMap( const TileMap_t& map, const Tileset_t& tileset, int scale )
{
   for ( int y = 0; y < map.height; ++y )
   {
      for ( int x = 0; x < map.width; ++x )
      {
         int index = map.tiles[ y * map.width + x ];
         if ( index == -1 )
         {
            // -1 means we dont draw it, just skip, check parsing to understand
            continue;
         }

         float destX = x * tileset.tileSize * scale;
         float destY = y * tileset.tileSize * scale;

         // Example we have index 49
         // To get the column and row
         // Column: 49 % 12 = 1
         // Row: 49 / 12 = 4.somehing
         // Se we are in column 1 row 4
         // To get the correct starting coordinates to draw
         // sourceX = 1 * (tileSize + spacing) = 17
         // sourceY = 4 * 17 = 68
         int col = index % tileset.columns;
         int row = index / tileset.columns;

         float sourceX = col * ( tileset.tileSize + tileset.spacing );
         float sourceY = row * ( tileset.tileSize + tileset.spacing );

         float destSize = tileset.tileSize * scale;

         DrawTexturePro( tileset.texture,
                         { sourceX, sourceY, ( float ) tileset.tileSize,
                           ( float ) tileset.tileSize },
                         { destX, destY, destSize, destSize }, { 0, 0 }, 0,
                         WHITE );
      }
   }
}

Tileset_t loadTileset( const std::string& tsxPath )
{
   tinyxml2::XMLDocument doc;
   auto                  err = doc.LoadFile( tsxPath.c_str() );
   if ( err )
   {
      std::println( "Error Loading path" );
      return Tileset_t{};
   }

   tinyxml2::XMLElement* tileset = doc.FirstChildElement( "tileset" );

   if ( !tileset )
   {
      std::println( "no <tileset> element" );
      return Tileset_t{};
   }

   int                   tileSize  = tileset->IntAttribute( "tilewidth" );
   int                   spacing   = tileset->IntAttribute( "spacing" );
   int                   columns   = tileset->IntAttribute( "columns" );
   int                   tileCount = tileset->IntAttribute( "tilecount" );
   tinyxml2::XMLElement* image     = tileset->FirstChildElement( "image" );

   if ( !image )
   {
      std::println( "no <image> element" );
      return Tileset_t{};
   }

   const char* src = image->Attribute( "source" );

   std::println( "Image {} TileSize {}, spacing {}, columns {}, source {}",
                 image->FirstAttribute()->Value(), tileSize, spacing, columns,
                 src );

   Tileset_t tileSet{ LoadTexture( "../assets/map/tilemap.png" ), tileSize,
                      spacing, columns, std::vector<TileDef_t>( tileCount ) };

   for ( auto* tile = tileset->FirstChildElement( "tile" ); tile != nullptr;
         tile       = tileset->NextSiblingElement( "tileset" ) )
   {
      if ( tile->FirstChildElement( "objectgroup" ) != nullptr )
      {
         int id                          = tile->IntAttribute( "id" );
         tileSet.tileDefs[ id ].walkable = false;
      }
   }

   return tileSet;
}

TileMap_t parseMap( const std::string& path )
{
   tinyxml2::XMLDocument doc;
   auto                  err = doc.LoadFile( path.c_str() );

   if ( err )
   {
      std::println( "Error Loading path" );
      return TileMap_t{};
   }

   TileMap_t             tileMap;
   tinyxml2::XMLElement* map      = doc.FirstChildElement( "map" );
   tinyxml2::XMLElement* tileset  = map->FirstChildElement( "tileset" );
   int                   firstgid = tileset->IntAttribute( "firstgid" );

   tinyxml2::XMLElement* layer  = map->FirstChildElement( "layer" );
   int                   width  = layer->IntAttribute( "width" );
   int                   height = layer->IntAttribute( "height" );

   tileMap.width  = width;
   tileMap.height = height;

   std::string data = layer->FirstChildElement( "data" )->GetText();

   // std::println( "firstgid {} data {}", firstgid, data );

   std::stringstream ss( data );
   std::string       token;
   while ( getline( ss, token, ',' ) )
   {
      // If we have an empty token stoll would throw, and i dont like exceptions
      if ( token.empty() )
      {
         continue;
      }

      auto parsedInt = std::stoll( token );

      int tileIndex = ( parsedInt & 0x1FFFFFFF ) - firstgid;
      tileMap.tiles.push_back( tileIndex );
   }

   return tileMap;
}
