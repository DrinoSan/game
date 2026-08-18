#include "Camera.h"

namespace camera{

   void followPosition( Camera2D& camera, const Vector2& position)
   {
      camera.target = { position.x + 20, position.y + 20 };
   }
};
