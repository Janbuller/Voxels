#include "VoxelGame/BlockSideInfo.h"
#include "engine/RawMesh.h"
#include "glcore/Texture.h"
#include "glm/fwd.hpp"
#include <array>
#include <unordered_map>
namespace VoxelGame {
    void BlockSideInfo::SetupTextureCoords(glcore::Texture Texture, int TexSize) {
        // Get the amount of textures on the atlas.
        int TexAmountX = Texture.m_Width / TexSize;
        int TexAmountY = Texture.m_Height / TexSize;

        // Get the change in texcoord per change in texture.
        double ChangePerTexX = 1.0 / (double) TexAmountX;
        double ChangePerTexY = 1.0 / (double) TexAmountY;

        double MiddleOffsetX = (ChangePerTexX / TexSize) / 2;
        double MiddleOffsetY = (ChangePerTexY / TexSize) / 2;

        // Get the 2d-index of the texture on the atlas.
        int TexIdxX = m_TextureIdx % TexAmountX;
        int TexIdxY = m_TextureIdx / TexAmountY;

        double Left   = ChangePerTexX * TexIdxX;
        double Right  = ChangePerTexX * (TexIdxX + 1);
        double Top    = ChangePerTexY * TexIdxY;
        double Bottom = ChangePerTexY * (TexIdxY + 1);

        m_Mesh.m_Vertices[0].TexCoords = glm::vec2{Right, Top};
        m_Mesh.m_Vertices[1].TexCoords = glm::vec2{Left, Bottom};
        m_Mesh.m_Vertices[2].TexCoords = glm::vec2{Right, Bottom};

        m_Mesh.m_Vertices[3].TexCoords = glm::vec2{Right, Top};
        m_Mesh.m_Vertices[4].TexCoords = glm::vec2{Left, Top};
        m_Mesh.m_Vertices[5].TexCoords = glm::vec2{Left, Bottom};
    }

    BlockSideInfo::BlockSideInfo(BlockSide Side, engine::RawMesh Mesh, int TextureIdx) : m_Side(Side), m_Mesh(Mesh), m_TextureIdx(TextureIdx) {}

    std::map<BlockSide, glm::vec3> BlockSideInfo::SideToUnitVector = {
            {BlockSide::POS_X, glm::ivec3{1, 0, 0}},
            {BlockSide::POS_Y, glm::ivec3{0, 1, 0}},
            {BlockSide::POS_Z, glm::ivec3{0, 0, 1}},

            {BlockSide::NEG_X, glm::ivec3{-1, 0, 0}},
            {BlockSide::NEG_Y, glm::ivec3{0, -1, 0}},
            {BlockSide::NEG_Z, glm::ivec3{0, 0, -1}},
    };
}// namespace VoxelGame
