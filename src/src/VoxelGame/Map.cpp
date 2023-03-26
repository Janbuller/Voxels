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

	if(ThreadRunning)
	  ChunkGenerator.join();

        for (int z = PlayerChunkPos.z - RenderDistance-1; z < PlayerChunkPos.z + RenderDistance; z++) {
            for (int x = PlayerChunkPos.x - RenderDistance-1; x < PlayerChunkPos.x + RenderDistance; x++) {
                auto RenderedChunkPos = std::make_pair(x, z);
                if (Chunks.count(RenderedChunkPos) == 0) {
                    if (std::find(ChunkGenQueue.begin(), ChunkGenQueue.end(), RenderedChunkPos) == ChunkGenQueue.end()) {
                      ChunkGenQueue.push_back(RenderedChunkPos);
                    }
                } else {
		  Chunks.at(RenderedChunkPos).Draw(Shader, RenderedChunkPos.first, 0, RenderedChunkPos.second, view, projection, RenderDistance);
                }
            }
        }

	
	// TODO: Profile whether to use threads or not.
	// ChunkGenerator = std::thread(&Map::GenerateMissingChunks, this);
	// ThreadRunning = true;
        GenerateMissingChunks();
    }

    void Map::GenerateChunk(int x, int z) {
      auto ChunkPos = std::make_pair(x, z);
      GenerateChunk(ChunkPos);
    }

    // TODO: Make a way for chunks to only regenerate the sides of
    //       their mesh when neighboor mesh is changed.
    void Map::GenerateChunk(std::pair<int, int> pos) {
      Chunks.insert({pos, Chunk{BlockAtlas, pos.first, pos.second, Seed}});
      Chunks.at(pos).GenerateChunkMesh(pos.first, pos.second, this);

      auto xPos = std::make_pair(pos.first + 1, pos.second);
      auto xNeg = std::make_pair(pos.first - 1, pos.second);
      auto zPos = std::make_pair(pos.first, pos.second + 1);
      auto zNeg = std::make_pair(pos.first, pos.second - 1);

      if(Chunks.count(xPos))

          Chunks.at(xPos).GenerateChunkMesh(xPos.first, xPos.second, this);
      if(Chunks.count(xNeg))
          Chunks.at(xNeg).GenerateChunkMesh(xNeg.first, xNeg.second, this);
      if(Chunks.count(zPos))
          Chunks.at(zPos).GenerateChunkMesh(zPos.first, zPos.second, this);
      if(Chunks.count(zNeg))
          Chunks.at(zNeg).GenerateChunkMesh(zNeg.first, zNeg.second, this);
    }

    void Map::GenerateMissingChunks() {
      for(int i = 0; i < 1; i++) {
	if(ChunkGenQueue.size()) {
	  GenerateChunk(ChunkGenQueue.front());
	  ChunkGenQueue.pop_front();
	}
      }
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

  void Map::SetBlockID(unsigned int id, int ChunkX, int ChunkZ, int x, int y, int z) {
    auto ChunkPos = std::make_pair(ChunkX, ChunkZ);
    if (Chunks.count(ChunkPos) != 0) {
      Chunks.at(ChunkPos).SetBlockID(id, x, y, z);
    }
  }

  void Map::SetBlockID(unsigned int id, int x, int y, int z) {
    int ChunkX = (x + (x<0)) / Chunk::SIZE_X;
    int ChunkZ = (z + (z<0)) / Chunk::SIZE_Z;

    ChunkX -= x < 0;
    ChunkZ -= z < 0;

    // This is the same as a modulo, which ignores the sign.
    x &= 0xf;
    z &= 0xf;

    SetBlockID(id, ChunkX, ChunkZ, x, y, z);
    GenerateChunk(ChunkX, ChunkZ);
  }
}// namespace VoxelGame
