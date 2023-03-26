#pragma once

#include "VoxelGame/Map.h"
#include "engine/Camera.h"
#include "glm/glm.hpp"

namespace VoxelGame {
    class Player {
    private:
        void CastRay(const Map *RaycastMap);
        const double m_RayDistance = 4.0;
        const int m_RaycastQuality = 512;

    public:
        engine::Camera m_PlayerCam;

        bool m_RayHit = false;
        glm::vec3 m_LookRayHitLoc;
        glm::vec3 m_LookRaySide = glm::vec3{0, 1, 0};

        Player(glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f),
               glm::vec3 Up       = glm::vec3(0.0f, 1.0f, 0.0f));

        void Update(const Map *RaycastMap);

        void HandleKeyboard(engine::Camera::MovDir Dir, double DeltaTime);
    };
}// namespace VoxelGame
