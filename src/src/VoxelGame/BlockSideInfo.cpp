#include "VoxelGame/BlockSideInfo.h"
#include "engine/RawMesh.h"
#include "glcore/Texture.h"
#include "glm/fwd.hpp"
#include <array>
namespace VoxelGame {
    void BlockSideInfo::SetupTextureCoords(glcore::Texture texture, int texSize) {
        // Get the amount of textures on the atlas.
        int TexAmountX = texture.width / texSize;
        int TexAmountY = texture.height / texSize;

        // Get the change in texcoord per change in texture.
        double ChangePerTexX = 1.0 / (double) TexAmountX;
        double ChangePerTexY = 1.0 / (double) TexAmountY;

        // Get the 2d-index of the texture on the atlas.
        int TexIdxX = TextureIdx % TexAmountX;
        int TexIdxY = TextureIdx / TexAmountY;

	std::cout << "x: " << TexIdxX << " : y: " << TexIdxY << std::endl;

        Mesh.vertices[0].texCoords = glm::vec2{
                ChangePerTexX * (TexIdxX+1),
                ChangePerTexY * (TexIdxY)};
        Mesh.vertices[1].texCoords = glm::vec2{
                ChangePerTexX * (TexIdxX),
                ChangePerTexY * (TexIdxY+1)};
        Mesh.vertices[2].texCoords = glm::vec2{
                ChangePerTexX * (TexIdxX+1),
                ChangePerTexY * (TexIdxY + 1)};

        Mesh.vertices[3].texCoords = glm::vec2{
                ChangePerTexX * (TexIdxX+1),
                ChangePerTexY * (TexIdxY)};
        Mesh.vertices[4].texCoords = glm::vec2{
                ChangePerTexX * (TexIdxX),
                ChangePerTexY * (TexIdxY)};
        Mesh.vertices[5].texCoords = glm::vec2{
                ChangePerTexX * (TexIdxX),
                ChangePerTexY * (TexIdxY+1)};
    }

    BlockSideInfo::BlockSideInfo(BlockSide Side, engine::RawMesh Mesh, int TextureIdx) : Side(Side), Mesh(Mesh), TextureIdx(TextureIdx) {
    }

    std::map<BlockSide, glm::vec3> BlockSideInfo::unitVectorDir = {
            {BlockSide::POS_X, glm::vec3{1, 0, 0}},
            {BlockSide::POS_Y, glm::vec3{0, 1, 0}},
            {BlockSide::POS_Z, glm::vec3{0, 0, 1}},

            {BlockSide::NEG_X, glm::vec3{-1, 0, 0}},
            {BlockSide::NEG_Y, glm::vec3{0, -1, 0}},
            {BlockSide::NEG_Z, glm::vec3{0, 0, -1}},
    };
}// namespace VoxelGame
