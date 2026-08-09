#include "TextureStore.h"
#include "raylib.h"

TextureStore_t::~TextureStore_t()
{
   unloadAll( *this );
}

TextureIndex getTextureIndex( TextureStore_t& store, const std::string& path )
{
   for ( TextureIndex i = 0; ( size_t ) i < store.paths.size(); ++i )
   {
      if ( store.paths[ i ] == path )
      {
         return i;
      }
   }

   auto texture = LoadTexture( path.c_str() );
   if ( texture.id == 0 )
   {
      return -1;
   }

   store.paths.push_back( path );
   store.textures.push_back( texture );

   return store.paths.size() - 1;
}

void unloadAll( TextureStore_t& store )
{
   for ( auto& texture : store.textures )
   {
      UnloadTexture( texture );
   }

   store.paths.clear();
   store.textures.clear();
}
