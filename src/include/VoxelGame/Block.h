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

    Block(glcore::Texture texture, int texSize);

    std::vector<BlockSideInfo> Sides;
  };
}
