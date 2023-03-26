#include "VoxelGame/Chunk.h"
#include "VoxelGame/Block.h"
#include "VoxelGame/BlockSideInfo.h"
#include "VoxelGame/Map.h"
#include "engine/Mesh.h"
#include "engine/RawMesh.h"
#include "glcore/Shader.h"
#include "glcore/Texture.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "siv/PerlinNoise.hpp"
#include <array>
#include <map>
#include <memory>

namespace VoxelGame {
    Chunk::Chunk(glcore::Texture BlockAtlas, int ChunkOffsetX, int ChunkOffsetZ, unsigned long Seed) : BlockAtlas(BlockAtlas) {
        ChunkMesh.textures.push_back(BlockAtlas);

        ChunkBlocks.fill(0);

        siv::PerlinNoise::seed_type seed = Seed;
        siv::PerlinNoise perlin{seed};

        for (int z = 0; z < SIZE_Z; z++) {
	    for (int x = 0; x < SIZE_X; x++) {
	        double noise = perlin.octave2D_01(((x + ChunkOffsetX * 16)) * 0.02, ((z + ChunkOffsetZ * 16)) * 0.02, 4);
                noise *= 40;
                noise += 20;

		noise = (int)noise;
                for (int y = 0; y <= noise; y++) {
		  unsigned int BlockID = 0;

		  // Lowest layer is bedrock
		  if(y == 0)
		    BlockID = 4;
		  // Below top 5 layer is stone.
		  else if(y < noise-5)
		    BlockID = 3;
		  // Above stone and belove grass is dirt.
		  else if(y < noise)
		    BlockID = 2;
		  // Top Layer is grass
		  else if(y == noise) {
		    BlockID = 1;
		  }

		  SetBlockID(BlockID, x, y, z);
                }
            }
        }
    }


    void Chunk::GenerateChunkMesh(int ChunkOffsetX, int ChunkOffsetZ, const Map *Map) {
      ChunkMesh = engine::Mesh{};
      ChunkMesh.textures.push_back(BlockAtlas);
        int indiciesAmount = 0;
        for (int z = 0; z < SIZE_Z; z++) {
            for (int y = 0; y < SIZE_Y; y++) {
                for (int x = 0; x < SIZE_X; x++) {
                    glm::vec3 curBlockPos{x, y, z};

                    unsigned int currentBlockID = Map->GetBlockID(ChunkOffsetX, ChunkOffsetZ, x, y, z);
		    // unsigned int currentBlockID = Map->GetBlockID((ChunkOffsetX * Chunk::SIZE_X) + x, y, (ChunkOffsetZ * Chunk::SIZE_Z) + z);


                    if (currentBlockID == 0)
                        continue;

                    const Block &currentBlock = Block::blocks.at(currentBlockID);

                    for (int side = 0; side < currentBlock.Sides.size(); side++) {

                        const auto &curSide = currentBlock.Sides[side];
                        const auto &dirOffset = BlockSideInfo::SideToUnitVector.at(curSide.Side);
                        auto posToCurSide = curBlockPos + dirOffset;
                        auto blockIdCurSide = Map->GetBlockID((ChunkOffsetX * Chunk::SIZE_X) + posToCurSide.x, posToCurSide.y, (ChunkOffsetZ * Chunk::SIZE_Z) + posToCurSide.z);
			// auto blockIdCurSide = Map->GetBlockID(ChunkOffsetX, ChunkOffsetZ, posToCurSide.x, posToCurSide.y, posToCurSide.z);

                        if (blockIdCurSide == 0) {
                            for (int i = 0; i < currentBlock.Sides[side].Mesh.vertices.size(); i++) {
                                auto currentVert = currentBlock.Sides[side].Mesh.vertices[i];
                                currentVert.position += curBlockPos;
                                ChunkMesh.vertices.push_back(currentVert);
                            }
                            for (int i = 0; i < currentBlock.Sides[side].Mesh.indicies.size(); i++) {
                                ChunkMesh.indicies.push_back(currentBlock.Sides[side].Mesh.indicies[i] + indiciesAmount);
                            }

                            indiciesAmount += currentBlock.Sides[side].Mesh.indicies.size();
                        }
                    }
                }
            }
        }

    }

    unsigned int Chunk::GetBlockID(int x, int y, int z) const {
        if (x < 0 || x >= SIZE_X ||
            y < 0 || y >= SIZE_Y ||
            z < 0 || z >= SIZE_Z) {
            return 0;
        }
        return ChunkBlocks[(z * SIZE_X * SIZE_Y) + (y * SIZE_X) + x];
    }

    void Chunk::SetBlockID(unsigned int id, int x, int y, int z) {
        ChunkBlocks[(z * SIZE_X * SIZE_Y) + (y * SIZE_X) + x] = id;
    }

  void Chunk::Draw(glcore::Shader shader, int xOffset, int yOffset, int zOffset, glm::mat4 view, glm::mat4 projection, int RenderDistance) {
        shader.bind();
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        glm::mat4 model = glm::mat4{1.0};
        model = glm::translate(model, (glm::vec3{xOffset * SIZE_X, yOffset * SIZE_Y, zOffset * SIZE_Z}));
        shader.setMat4("model", model);

	shader.setFloat("FogDistance", RenderDistance);
        ChunkMesh.Draw(shader);
    }

}// namespace VoxelGame
