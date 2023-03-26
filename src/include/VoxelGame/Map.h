#pragma once
#include "VoxelGame/Chunk.h"
#include "glcore/Texture.h"
#include "glm/fwd.hpp"
#include <string>
#include <tuple>
#include <vector>
#include <deque>
#include <thread>

namespace VoxelGame {
  class Chunk;
  
  class Map {
  private:
    std::map<std::pair<int, int>, Chunk> Chunks;
    unsigned long Seed;
    glcore::Texture BlockAtlas;

    std::deque<std::pair<int, int>> ChunkGenQueue{};

    bool ThreadRunning = false;
    std::thread ChunkGenerator;

    void GenerateChunk(int x, int y);
    void GenerateChunk(std::pair<int, int> pos);
    void GenerateMissingChunks();

  public:
    Map(glcore::Texture BlockAtlas, unsigned long Seed);

    void Draw(glcore::Shader Shader, glm::mat4 view, glm::mat4 projection, glm::vec3 PlayerPosition, int RenderDistance);
    unsigned int GetBlockID(int ChunkX, int ChunkZ, int x, int y, int z) const;
    unsigned int GetBlockID(int x, int y, int z) const;
    void SetBlockID(unsigned int id, int ChunkX, int ChunkZ, int x, int y, int z);
    void SetBlockID(unsigned int id, int x, int y, int z);
  };
}
