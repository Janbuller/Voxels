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
    std::map<std::pair<int, int>, Chunk> m_Chunks;
    unsigned long m_Seed;
    glcore::Texture m_BlockAtlas;

    std::deque<std::pair<int, int>> m_ChunkGenQueue{};

    bool m_ThreadRunning = false;
    std::thread m_ChunkGenerator;

    void GenerateChunk(int x, int y);
    void GenerateChunk(std::pair<int, int> Pos);
    void GenerateMissingChunks();

  public:
    Map(glcore::Texture BlockAtlas, unsigned long Seed);

    void Draw(glcore::Shader Shader, glm::mat4 View, glm::mat4 Projection, glm::vec3 PlayerPosition, int RenderDistance);
    unsigned int GetBlockID(int ChunkX, int ChunkZ, int x, int y, int z) const;
    unsigned int GetBlockID(int x, int y, int z) const;
    void SetBlockID(unsigned int ID, int ChunkX, int ChunkZ, int x, int y, int z);
    void SetBlockID(unsigned int ID, int x, int y, int z);
  };
}
