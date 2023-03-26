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
    Chunk::Chunk(glcore::Texture BlockAtlas, int ChunkOffsetX, int ChunkOffsetZ, unsigned long Seed) : m_BlockAtlas(BlockAtlas) {
        m_ChunkMesh.m_Textures.push_back(BlockAtlas);

        m_ChunkBlocks.fill(0);

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
      m_ChunkMesh = engine::Mesh{};
      m_ChunkMesh.m_Textures.push_back(m_BlockAtlas);
        int indiciesAmount = 0;
        for (int z = 0; z < SIZE_Z; z++) {
            for (int y = 0; y < SIZE_Y; y++) {
                for (int x = 0; x < SIZE_X; x++) {
                    glm::vec3 curBlockPos{x, y, z};

                    unsigned int currentBlockID = Map->GetBlockID(ChunkOffsetX, ChunkOffsetZ, x, y, z);
		    // unsigned int currentBlockID = Map->GetBlockID((ChunkOffsetX * Chunk::SIZE_X) + x, y, (ChunkOffsetZ * Chunk::SIZE_Z) + z);


                    if (currentBlockID == 0)
                        continue;

                    const Block &currentBlock = Block::m_Blocks.at(currentBlockID);

                    for (int side = 0; side < currentBlock.m_Sides.size(); side++) {

                        const auto &curSide = currentBlock.m_Sides[side];
                        const auto &dirOffset = BlockSideInfo::SideToUnitVector.at(curSide.m_Side);
                        auto posToCurSide = curBlockPos + dirOffset;
                        auto blockIdCurSide = Map->GetBlockID((ChunkOffsetX * Chunk::SIZE_X) + posToCurSide.x, posToCurSide.y, (ChunkOffsetZ * Chunk::SIZE_Z) + posToCurSide.z);
			// auto blockIdCurSide = Map->GetBlockID(ChunkOffsetX, ChunkOffsetZ, posToCurSide.x, posToCurSide.y, posToCurSide.z);

                        if (blockIdCurSide == 0) {
                            for (int i = 0; i < currentBlock.m_Sides[side].m_Mesh.m_Vertices.size(); i++) {
                                auto currentVert = currentBlock.m_Sides[side].m_Mesh.m_Vertices[i];
                                currentVert.Position += curBlockPos;
                                m_ChunkMesh.m_Vertices.push_back(currentVert);
                            }
                            for (int i = 0; i < currentBlock.m_Sides[side].m_Mesh.m_Indicies.size(); i++) {
                                m_ChunkMesh.m_Indicies.push_back(currentBlock.m_Sides[side].m_Mesh.m_Indicies[i] + indiciesAmount);
                            }

                            indiciesAmount += currentBlock.m_Sides[side].m_Mesh.m_Indicies.size();
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
        return m_ChunkBlocks[(z * SIZE_X * SIZE_Y) + (y * SIZE_X) + x];
    }

    void Chunk::SetBlockID(unsigned int ID, int x, int y, int z) {
        m_ChunkBlocks[(z * SIZE_X * SIZE_Y) + (y * SIZE_X) + x] = ID;
    }

  void Chunk::Draw(glcore::Shader Shader, int OffsetX, int OffsetY, int OffsetZ, glm::mat4 View, glm::mat4 Projection, int RenderDistance) {
        Shader.Bind();
        Shader.SetMat4("view", View);
        Shader.SetMat4("projection", Projection);

        glm::mat4 model = glm::mat4{1.0};
        model = glm::translate(model, (glm::vec3{OffsetX * SIZE_X, OffsetY * SIZE_Y, OffsetZ * SIZE_Z}));
        Shader.SetMat4("model", model);

	Shader.SetFloat("FogDistance", RenderDistance);
        m_ChunkMesh.Draw(Shader);
    }

}// namespace VoxelGame
