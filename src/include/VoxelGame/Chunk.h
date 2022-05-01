#pragma once
#include "VoxelGame/Block.h"
#include "VoxelGame/Map.h"
#include "engine/Mesh.h"
#include "glcore/Shader.h"
#include "glcore/Texture.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "siv/PerlinNoise.hpp"
#include <array>
#include <map>
#include <memory>

namespace VoxelGame {
  class Map;

    class Chunk {
    public:
        static const int SIZE_X = 16;
        static const int SIZE_Y = 128;
        static const int SIZE_Z = 16;

    private:
        std::array<unsigned int, SIZE_X * SIZE_Y * SIZE_Z> ChunkBlocks;
        engine::Mesh ChunkMesh;
        glcore::Texture BlockAtlas;

    public:
      Chunk(glcore::Texture BlockAtlas, int ChunkOffsetX, int ChunkOffsetZ, unsigned long Seed);

      void GenerateChunkMesh(int ChunkOffsetX, int ChunkOffsetZ, const Map* Map);

        unsigned int GetBlockID(int x, int y, int z) const;

        void SetBlockID(unsigned int id, int x, int y, int z);

      void Draw(glcore::Shader shader, int xOffset, int yOffset, int zOffset, glm::mat4 view, glm::mat4 projection, int RenderDistance);
    };
}// namespace VoxelGame
