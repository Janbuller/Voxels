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

  void Player::CastRay(const Map* RaycastMap) {
    glm::vec3 RayMovement = PlayerCam.Front / (float)RaycastQuality;
    glm::vec3 CurrentRaycastPosition = PlayerCam.Position;
    CurrentRaycastPosition += glm::vec3{
	    sgn(CurrentRaycastPosition.x) * 0.5,
	    sgn(CurrentRaycastPosition.y) * 0.5,
	    sgn(CurrentRaycastPosition.z) * 0.5};

    for(int i = 0; i < RayDistance * RaycastQuality; i++) {
      CurrentRaycastPosition += RayMovement;

      glm::ivec3 BlockPos = CurrentRaycastPosition;
      if(RaycastMap->GetBlockID(BlockPos.x, BlockPos.y, BlockPos.z)) {
	RayHit = true;
	LookRayHitLoc = BlockPos;
	return;
      }
    }

    RayHit = false;
  }

  Player::Player(glm::vec3 position, glm::vec3 up) : PlayerCam(position, up) {
    
  }

void Player::Update(const Map* RaycastMap) {
    CastRay(RaycastMap);
  }

  void Player::HandleKeyboard(engine::Camera::MovDir dir, double DeltaTime) {
    PlayerCam.ProcessKeyboard(dir, DeltaTime);
  }
}
