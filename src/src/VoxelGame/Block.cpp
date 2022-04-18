#include "VoxelGame/Block.h"
#include "glcore/Shader.h"
#include <map>

namespace VoxelGame {

    Block::Block() : cubeMesh(engine::Mesh::LoadOBJ("cube.obj", "res")), mainCube("res/shaders/mainCube.vert", "res/shaders/mainCube.frag") {
    }

    std::map<unsigned int, Block> Block::blocks = {
            // {1, Block{}}
    };
}// namespace VoxelGame
