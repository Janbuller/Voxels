#include "VoxelGame/Player.h"
#include "VoxelGame/Map.h"
#include "engine/Camera.h"
#include "engine/Mesh.h"
#include "glcore/Shader.h"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include <glm/gtx/string_cast.hpp>

namespace VoxelGame {

    template<typename T>
    int sgn(T val) {
        return (T(0) < val) - (val < T(0));
    }

    void Player::CastRay(const Map *RaycastMap) {
        glm::vec3 RayMovement            = m_PlayerCam.m_Front / (float) m_RaycastQuality;
        glm::vec3 CurrentRaycastPosition = m_PlayerCam.m_Position;
        CurrentRaycastPosition += glm::vec3{
                sgn(CurrentRaycastPosition.x) * 0.5,
                sgn(CurrentRaycastPosition.y) * 0.5,
                sgn(CurrentRaycastPosition.z) * 0.5};

        for (int i = 0; i < m_RayDistance * m_RaycastQuality; i++) {
            CurrentRaycastPosition += RayMovement;

            glm::ivec3 BlockPos = CurrentRaycastPosition;
            if (RaycastMap->GetBlockID(BlockPos.x, BlockPos.y, BlockPos.z)) {
                m_RayHit        = true;
                m_LookRayHitLoc = BlockPos;

                auto RelativeLocVec = CurrentRaycastPosition - (glm::vec3) BlockPos;
                RelativeLocVec -= glm::vec3{
                        sgn(BlockPos.x) * 0.5,
                        sgn(BlockPos.y) * 0.5,
                        sgn(BlockPos.z) * 0.5};

                std::cout << glm::to_string(RelativeLocVec) << std::endl;
                m_LookRaySide = glm::vec3(
                        (int) (RelativeLocVec.x > RelativeLocVec.y && RelativeLocVec.x > RelativeLocVec.z && RelativeLocVec.x > 0) - (int) (RelativeLocVec.x < RelativeLocVec.y && RelativeLocVec.x < RelativeLocVec.z && RelativeLocVec.x < 0),
                        (int) (RelativeLocVec.y > RelativeLocVec.x && RelativeLocVec.y > RelativeLocVec.z && RelativeLocVec.y > 0) - (int) (RelativeLocVec.y < RelativeLocVec.x && RelativeLocVec.y < RelativeLocVec.z && RelativeLocVec.y < 0),
                        (int) (RelativeLocVec.z > RelativeLocVec.y && RelativeLocVec.z > RelativeLocVec.x && RelativeLocVec.z > 0) - (int) (RelativeLocVec.z < RelativeLocVec.y && RelativeLocVec.z < RelativeLocVec.x && RelativeLocVec.z < 0));
                return;
            }
        }

        m_RayHit = false;
    }

    Player::Player(glm::vec3 Position, glm::vec3 Up) : m_PlayerCam(Position, Up) {}

    void Player::Update(const Map *RaycastMap) {
        CastRay(RaycastMap);
    }

    void Player::HandleKeyboard(engine::Camera::MovDir Dir, double DeltaTime) {
        m_PlayerCam.ProcessKeyboard(Dir, DeltaTime);
    }
}// namespace VoxelGame
