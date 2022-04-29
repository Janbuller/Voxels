#pragma once
#include "VoxelGame/Chunk.h"
#include "glcore/Texture.h"
#include "glm/fwd.hpp"
#include <string>
#include <tuple>
#include <vector>
namespace VoxelGame {
  class Map {
  private:
    std::map<std::pair<int, int>, Chunk> Chunks;
    unsigned long Seed;
    glcore::Texture BlockAtlas;
  public:
    Map(glcore::Texture BlockAtlas, unsigned long Seed);

    void Draw(glcore::Shader Shader, glm::mat4 view, glm::mat4 projection, glm::vec3 PlayerPosition, int RenderDistance);

    void GenerateChunk(int x, int y);
    void GenerateChunk(std::pair<int, int> pos);
  };
}
