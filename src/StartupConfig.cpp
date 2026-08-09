#include <print>

#include "StartupConfig.h"
#include "TextureStore.h"

namespace assets
{

static constexpr std::array<assetConfigData_t,
                            std::to_underlying( AnimId::Count )>
    assetConfigPaths{
        { { AnimId::WalkFront, 8, 0.1,
            "../assets/Wizard_Front_Walk_No_Weapon.png" },
          { AnimId::WalkRight, 8, 0.1,
            "../assets/Wizard_Side_Walk_No_Weapon.png" },
          { AnimId::WalkBack, 8, 0.1,
            "../assets/Wizard_Back_Walk_No_Weapon.png" },
          { AnimId::WalkLeft, 8, 0.1,
            "../assets/Wizard_Side_Walk_No_Weapon.png" },
          { AnimId::Idle, 7, 0.1, "../assets/Wizard_Idle.png" } } };

std::array<Animation_t, std::to_underlying( AnimId::Count )>
prepareAnimations( TextureStore_t& textureStore )
{
   std::array<Animation_t, std::to_underlying( AnimId::Count )> animations;
   for ( const auto& assetConfig : assetConfigPaths )
   {
      auto res = getTextureIndex( textureStore, assetConfig.path );
      if ( res == -1 )
      {
         std::println( "Cant load texture at path {}", assetConfig.path );
         return {};
      }

      auto& animation = animations[ std::to_underlying( assetConfig.animID ) ];
      animation.textureIndex  = res;
      animation.frameCount    = assetConfig.frameCount;
      animation.frameDuration = assetConfig.frameDuration;
      animation.frameWidth =
          textureStore.textures[ res ].width / animation.frameCount;
      animation.frameHeight = textureStore.textures[ res ].height;
   }

   return animations;
}

};   // namespace assets
