#pragma once
#include "VoxelGame/BlockSideInfo.h"
#include "engine/Mesh.h"
#include "glcore/Shader.h"
#include <array>
#include <map>
namespace VoxelGame {
  class Block {
  public:
    static std::map<unsigned int, Block> m_Blocks;

    Block(glcore::Texture Texture, int TexSize, std::array<int, 6> TextureIDs);
    Block(glcore::Texture Texture, int TexSize, int TextureID);

    std::vector<BlockSideInfo> m_Sides;
  private:
    void Init(glcore::Texture Texture, int TexSize, std::array<int, 6> TextureIDs);
  };
}
