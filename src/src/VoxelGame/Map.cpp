#include "VoxelGame/Map.h"
#include "glcore/Shader.h"
#include "glcore/Texture.h"
#include <string>
#include <tuple>
#include <utility>
namespace VoxelGame {
  Map::Map(glcore::Texture BlockAtlas, unsigned long Seed) : Seed{Seed}, BlockAtlas(BlockAtlas) {
  }

  void Map::Draw(glcore::Shader Shader, glm::mat4 view, glm::mat4 projection, glm::vec3 PlayerPosition, int RenderDistance) {
    glm::vec3 PlayerChunkPos{
      PlayerPosition.x / Chunk::SIZE_X,
      PlayerPosition.y / Chunk::SIZE_Y,
      PlayerPosition.z / Chunk::SIZE_Z
    };

    for(int z = PlayerChunkPos.z - RenderDistance; z < PlayerChunkPos.z + RenderDistance; z++) {
      for(int x = PlayerChunkPos.x - RenderDistance; x < PlayerChunkPos.x + RenderDistance; x++) {
	auto RenderedChunkPos = std::make_pair(x, z);
	if(Chunks.count(RenderedChunkPos) == 0) {
	  GenerateChunk(RenderedChunkPos);
	} else {
	  Chunks.at(RenderedChunkPos).Draw(Shader, RenderedChunkPos.first, 0, RenderedChunkPos.second, view, projection);
	}
      }
    }
  }

  void Map::GenerateChunk(int x, int z) {
    Chunks.insert({std::make_pair(x, z), Chunk{BlockAtlas, x, z, Seed}});
  }

  void Map::GenerateChunk(std::pair<int, int> pos) {
    Chunks.insert({pos, Chunk{BlockAtlas, pos.first, pos.second, Seed}});
  }

}
