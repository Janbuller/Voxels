#include "VoxelGame/Map.h"
#include "glcore/Shader.h"
#include "glcore/Texture.h"
#include <chrono>
#include <execution>
#include <memory>
#include <pstl/glue_execution_defs.h>
#include <stdexcept>
#include <string>
#include <thread>
#include <tuple>
#include <utility>

namespace VoxelGame {
    Map::Map(glcore::Texture BlockAtlas, unsigned long Seed) : Seed{Seed}, BlockAtlas(BlockAtlas) {

        // ChunkGenerator = std::thread{[this]() { GenerateMissingChunks(); }};
    }

    void Map::Draw(glcore::Shader Shader, glm::mat4 view, glm::mat4 projection, glm::vec3 PlayerPosition, int RenderDistance) {
        glm::vec3 PlayerChunkPos{
                PlayerPosition.x / Chunk::SIZE_X,
                PlayerPosition.y / Chunk::SIZE_Y,
                PlayerPosition.z / Chunk::SIZE_Z};

        for (int z = PlayerChunkPos.z - RenderDistance-1; z < PlayerChunkPos.z + RenderDistance; z++) {
            for (int x = PlayerChunkPos.x - RenderDistance-1; x < PlayerChunkPos.x + RenderDistance; x++) {
                auto RenderedChunkPos = std::make_pair(x, z);
                if (Chunks.count(RenderedChunkPos) == 0) {
                    if (std::find(ChunkGenQueue.begin(), ChunkGenQueue.end(), RenderedChunkPos) == ChunkGenQueue.end()) {
                        // ChunkGenQueue.push_back(RenderedChunkPos);
		      GenerateChunk(RenderedChunkPos);
                    }
                } else {
		  Chunks.at(RenderedChunkPos).Draw(Shader, RenderedChunkPos.first, 0, RenderedChunkPos.second, view, projection, RenderDistance);
                }
            }
        }

        // ChunkGenerator.join();
        // ChunkGenerator = std::thread{[this]() { GenerateMissingChunks(); }};
        GenerateMissingChunks();
    }

    void Map::GenerateChunk(int x, int z) {
      auto ChunkPos = std::make_pair(x, z);
      Chunks.insert({ChunkPos, Chunk{BlockAtlas, x, z, Seed}});
      Chunks.at(ChunkPos).GenerateChunkMesh(x, z, this);
    }

    void Map::GenerateChunk(std::pair<int, int> pos) {
      Chunks.insert({pos, Chunk{BlockAtlas, pos.first, pos.second, Seed}});
      Chunks.at(pos).GenerateChunkMesh(pos.first, pos.second, this);

      auto xPos = std::make_pair(pos.first + 1, pos.second);
      auto xNeg = std::make_pair(pos.first - 1, pos.second);
      auto zPos = std::make_pair(pos.first, pos.second + 1);
      auto zNeg = std::make_pair(pos.first, pos.second - 1);
      try {
          Chunks.at(xPos).GenerateChunkMesh(xPos.first, xPos.second, this);
      } catch (std::out_of_range e) {}
      try {
          Chunks.at(xNeg).GenerateChunkMesh(xNeg.first, xNeg.second, this);
      } catch (std::out_of_range e) {}
      try {
          Chunks.at(zPos).GenerateChunkMesh(zPos.first, zPos.second, this);
      } catch (std::out_of_range e) {}
      try {
          Chunks.at(zNeg).GenerateChunkMesh(zNeg.first, zNeg.second, this);
      } catch (std::out_of_range e) {}
    }

    void Map::GenerateMissingChunks() {
        std::for_each(
                std::execution::seq,
                ChunkGenQueue.begin(),
                ChunkGenQueue.end(),
                [this](auto &&item) {
                    GenerateChunk(ChunkGenQueue.front());
                    ChunkGenQueue.pop_front();
                });
    }


  unsigned int Map::GetBlockID(int ChunkX, int ChunkZ, int x, int y, int z) const {
    // return Chunks.at(std::make_pair(ChunkX, ChunkZ)).GetBlockID(x, y, z);

    auto ChunkPos = std::make_pair(ChunkX, ChunkZ);
    unsigned int id = 1;
    if (Chunks.count(ChunkPos) != 0) {
      id = Chunks.at(ChunkPos).GetBlockID(x, y, z);
    }
    return id;
  }

  unsigned int Map::GetBlockID(int x, int y, int z) const {
    int ChunkX = (x + (x<0)) / Chunk::SIZE_X;
    int ChunkZ = (z + (z<0)) / Chunk::SIZE_Z;

    ChunkX -= x < 0;
    ChunkZ -= z < 0;

    // This is the same as a modulo, which ignores the sign.
    x &= 0xf;
    z &= 0xf;

    return GetBlockID(ChunkX, ChunkZ, x, y, z);
  }
}// namespace VoxelGame
