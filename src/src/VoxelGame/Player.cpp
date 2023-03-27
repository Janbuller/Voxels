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

        for (int i = 0; i < m_RayDistance * m_RaycastQuality; i++) {
            CurrentRaycastPosition += RayMovement;

            glm::ivec3 BlockPos = CurrentRaycastPosition + glm::vec3{
								   sgn(CurrentRaycastPosition.x) * 0.5,
								   sgn(CurrentRaycastPosition.y) * 0.5,
								   sgn(CurrentRaycastPosition.z) * 0.5};
            if (RaycastMap->GetBlockID(BlockPos.x, BlockPos.y, BlockPos.z)) {
		CurrentRaycastPosition += glm::vec3{
			sgn(CurrentRaycastPosition.x) * 0.5,
			sgn(CurrentRaycastPosition.y) * 0.5,
			sgn(CurrentRaycastPosition.z) * 0.5};
                m_RayHit        = true;
                m_LookRayHitLoc = BlockPos;

		// TODO: Add all the prints here to future debug screen.
		// std::cout << glm::to_string(CurrentRaycastPosition - RayMovement * (float)i) << std::endl;
		// std::cout << glm::to_string(CurrentRaycastPosition) << std::endl;
		// std::cout << glm::to_string(BlockPos) << std::endl;

                auto RelativeLocVec = CurrentRaycastPosition - (glm::vec3) BlockPos;
                RelativeLocVec -= glm::vec3{
                        sgn(CurrentRaycastPosition.x) * 0.5,
                        sgn(CurrentRaycastPosition.y) * 0.5,
                        sgn(CurrentRaycastPosition.z) * 0.5};

		// std::cout << glm::to_string(RelativeLocVec) << std::endl;
		
                auto RelativeLocVecAbs = glm::vec3{
		    std::abs(RelativeLocVec.x),
		    std::abs(RelativeLocVec.y),
		    std::abs(RelativeLocVec.z),
		};

                m_LookRaySide = glm::vec3(
		    (int) (RelativeLocVecAbs.x > RelativeLocVecAbs.y && RelativeLocVecAbs.x > RelativeLocVecAbs.z && RelativeLocVecAbs.x > 0) * sgn(RelativeLocVec.x),
		    (int) (RelativeLocVecAbs.y > RelativeLocVecAbs.x && RelativeLocVecAbs.y > RelativeLocVecAbs.z && RelativeLocVecAbs.y > 0) * sgn(RelativeLocVec.y),
		    (int) (RelativeLocVecAbs.z > RelativeLocVecAbs.y && RelativeLocVecAbs.z > RelativeLocVecAbs.x && RelativeLocVecAbs.z > 0) * sgn(RelativeLocVec.z));
		// std::cout << glm::to_string(m_LookRaySide) << std::endl;
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
