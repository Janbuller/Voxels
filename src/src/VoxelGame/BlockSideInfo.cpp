#include "VoxelGame/BlockSideInfo.h"
#include "engine/RawMesh.h"
#include "glcore/Texture.h"
#include "glm/fwd.hpp"
#include <array>
#include <unordered_map>
namespace VoxelGame {
    void BlockSideInfo::SetupTextureCoords(glcore::Texture texture, int texSize) {
        // Get the amount of textures on the atlas.
        int TexAmountX = texture.width / texSize;
        int TexAmountY = texture.height / texSize;

        // Get the change in texcoord per change in texture.
        double ChangePerTexX = 1.0 / (double) TexAmountX;
        double ChangePerTexY = 1.0 / (double) TexAmountY;

        double MiddleOffsetX = (ChangePerTexX / texSize) / 2;
	double MiddleOffsetY = (ChangePerTexY / texSize) / 2;

        // Get the 2d-index of the texture on the atlas.
        int TexIdxX = TextureIdx % TexAmountX;
        int TexIdxY = TextureIdx / TexAmountY;

        double Left   = ChangePerTexX * TexIdxX;
        double Right  = ChangePerTexX * (TexIdxX + 1);
        double Top    = ChangePerTexY * TexIdxY;
        double Bottom = ChangePerTexY * (TexIdxY + 1);

        Mesh.vertices[0].texCoords = glm::vec2{Right, Top};
        Mesh.vertices[1].texCoords = glm::vec2{Left,  Bottom};
        Mesh.vertices[2].texCoords = glm::vec2{Right, Bottom};

        Mesh.vertices[3].texCoords = glm::vec2{Right, Top};
        Mesh.vertices[4].texCoords = glm::vec2{Left,  Top};
        Mesh.vertices[5].texCoords = glm::vec2{Left,  Bottom};
    }

    BlockSideInfo::BlockSideInfo(BlockSide Side, engine::RawMesh Mesh, int TextureIdx) : Side(Side), Mesh(Mesh), TextureIdx(TextureIdx) {
    }

    std::map<BlockSide, glm::vec3> BlockSideInfo::SideToUnitVector = {
            {BlockSide::POS_X, glm::ivec3{1, 0, 0}},
            {BlockSide::POS_Y, glm::ivec3{0, 1, 0}},
            {BlockSide::POS_Z, glm::ivec3{0, 0, 1}},

            {BlockSide::NEG_X, glm::ivec3{-1, 0, 0}},
            {BlockSide::NEG_Y, glm::ivec3{0, -1, 0}},
            {BlockSide::NEG_Z, glm::ivec3{0, 0, -1}},
    };
}// namespace VoxelGame
