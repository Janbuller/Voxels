#pragma once
#include "engine/Mesh.h"
#include "glcore/Shader.h"
#include <map>
namespace VoxelGame {
  class Block {
  public:
    static std::map<unsigned int, Block> blocks;

    Block();

    engine::Mesh cubeMesh;
    glcore::Shader mainCube;
  };
}
