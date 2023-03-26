#pragma once
#include "engine/RawMesh.h"
#include "glcore/Texture.h"
#include "glm/fwd.hpp"
#include <map>
#include <unordered_map>
namespace VoxelGame {

    enum class BlockSide {
        POS_X,
        NEG_X,
        POS_Y,
        NEG_Y,
        POS_Z,
        NEG_Z
    };

    struct BlockSideInfo {
        BlockSide Side;
        engine::RawMesh Mesh;
        int TextureIdx;

        void SetupTextureCoords(glcore::Texture texture, int texSize);

        BlockSideInfo(BlockSide Side, engine::RawMesh Mesh, int TextureIdx);
      static std::map<BlockSide, glm::vec3> SideToUnitVector;
    };
}// namespace VoxelGame
