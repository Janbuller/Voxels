#pragma once

#include "VoxelGame/Map.h"
#include "engine/Camera.h"
#include "glm/glm.hpp"

namespace VoxelGame {
    class Player {
    private:
        void CastRay(const Map *RaycastMap);
        const double RayDistance = 4.0;
        const int RaycastQuality = 512;

    public:
        engine::Camera PlayerCam;

        bool RayHit = false;
        glm::vec3 LookRayHitLoc;
        glm::vec3 LookRaySide = glm::vec3{0, 1, 0};

        Player(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
               glm::vec3 up       = glm::vec3(0.0f, 1.0f, 0.0f));

        void Update(const Map *RaycastMap);

        void HandleKeyboard(engine::Camera::MovDir dir, double DeltaTime);
    };
}// namespace VoxelGame
