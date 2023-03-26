#include "VoxelGame/Block.h"
#include "VoxelGame/BlockSideInfo.h"
#include "engine/RawMesh.h"
#include "glcore/Shader.h"
#include "glcore/Texture.h"
#include <algorithm>
#include <map>
#include <vector>

namespace VoxelGame {

    Block::Block(glcore::Texture Texture, int TexSize, std::array<int, 6> TextureIDs) {
        Init(Texture, TexSize, TextureIDs);
    }

    Block::Block(glcore::Texture Texture, int TexSize, int TextureID) {
        Init(Texture, TexSize, {TextureID, TextureID, TextureID, TextureID, TextureID, TextureID});
    }

    void Block::Init(glcore::Texture Texture, int TexSize, std::array<int, 6> Textures) {
        m_Sides.push_back(
                BlockSideInfo{
                        BlockSide::POS_X,
                        engine::RawMesh::LoadOBJ("cube-xp.obj", "res/models/cube-faces"),
                        Textures[0]});
        m_Sides.push_back(
                BlockSideInfo{
                        BlockSide::NEG_X,
                        engine::RawMesh::LoadOBJ("cube-xn.obj", "res/models/cube-faces"),
                        Textures[1]});
        m_Sides.push_back(
                BlockSideInfo{
                        BlockSide::POS_Y,
                        engine::RawMesh::LoadOBJ("cube-yp.obj", "res/models/cube-faces"),
                        Textures[2]});
        m_Sides.push_back(
                BlockSideInfo{
                        BlockSide::NEG_Y,
                        engine::RawMesh::LoadOBJ("cube-yn.obj", "res/models/cube-faces"),
                        Textures[3]});
        m_Sides.push_back(
                BlockSideInfo{
                        BlockSide::POS_Z,
                        engine::RawMesh::LoadOBJ("cube-zp.obj", "res/models/cube-faces"),
                        Textures[4]});
        m_Sides.push_back(
                BlockSideInfo{
                        BlockSide::NEG_Z,
                        engine::RawMesh::LoadOBJ("cube-zn.obj", "res/models/cube-faces"),
                        Textures[5]});

        for (int i = 0; i < m_Sides.size(); i++) {
            m_Sides[i].SetupTextureCoords(Texture, TexSize);
        }
    }

    std::map<unsigned int, Block> Block::m_Blocks = {};
}// namespace VoxelGame
