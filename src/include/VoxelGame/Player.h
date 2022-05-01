#pragma once

#include "engine/Camera.h"
#include "glm/glm.hpp"

namespace VoxelGame {
  class Player {
  public:
    engine::Camera PlayerCam;

    Player(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
	   glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
  };
}
