#pragma once
#include "VoxelGame/BlockSideInfo.h"
#include "engine/Mesh.h"
#include "glcore/Shader.h"
#include <array>
#include <map>
namespace VoxelGame {
  class Block {
  public:
    static std::map<unsigned int, Block> blocks;

    Block(glcore::Texture texture, int texSize, std::array<int, 6> textureIDs);
    Block(glcore::Texture texture, int texSize, int textureID);

    std::vector<BlockSideInfo> Sides;
  private:
    void Init(glcore::Texture texture, int texSize, std::array<int, 6> textureIDs);
  };
}
