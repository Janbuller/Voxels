#include "VoxelGame/Chunk.h"
#include "VoxelGame/Block.h"
#include "VoxelGame/BlockSideInfo.h"
#include "engine/Mesh.h"
#include "glcore/Shader.h"
#include "glcore/Texture.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "siv/PerlinNoise.hpp"
#include <array>
#include <map>

namespace VoxelGame {
  Chunk::Chunk(glcore::Texture BlockAtlas, int xOffset, int zOffset, unsigned long Seed) : BlockAtlas(BlockAtlas) {
        ChunkMesh.textures.push_back(BlockAtlas);

        ChunkBlocks.fill(0);

        siv::PerlinNoise::seed_type seed = Seed;
        siv::PerlinNoise perlin{seed};

        for (int z = 0; z < SIZE_Z; z++) {
            for (int x = 0; x < SIZE_X; x++) {
                double noise = perlin.octave2D_01(((x + xOffset * 16)) * 0.02, ((z + zOffset * 16)) * 0.02, 4);
                noise *= 20;
                noise += 40;

                for (int y = 0; y < noise; y++) {
                    SetBlockID(1, x, y, z);
                }
            }
        }
	GenerateChunkMesh();
    }


    void Chunk::GenerateChunkMesh() {
        int indiciesAmount = 0;
        for (int z = 0; z < SIZE_Z; z++) {
            for (int y = 0; y < SIZE_Y; y++) {
                for (int x = 0; x < SIZE_X; x++) {
                    glm::vec3 curBlockPos{x, y, z};

                    unsigned int currentBlockID = GetBlockID(x, y, z);

                    if (currentBlockID == 0)
                        continue;

                    Block& currentBlock = Block::blocks.at(currentBlockID);

                    for (int side = 0; side < currentBlock.Sides.size(); side++) {

                        const auto& curSide = currentBlock.Sides[side];
                        const auto& dirOffset = BlockSideInfo::unitVectorDir.at(curSide.Side);
                        auto posToCurSide = curBlockPos + dirOffset;
                        auto blockIdCurSide = GetBlockID(posToCurSide.x, posToCurSide.y, posToCurSide.z);

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

        ChunkMesh.SetupBuffers();
    }

    unsigned int Chunk::GetBlockID(int x, int y, int z) {
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

    void Chunk::Draw(glcore::Shader shader, int xOffset, int yOffset, int zOffset, glm::mat4 view, glm::mat4 projection) {
        // for (int z = 0; z < SIZE_Z; z++) {
        //     for (int y = 0; y < SIZE_Y; y++) {
        //         for (int x = 0; x < SIZE_X; x++) {
        //             unsigned int currentBlockID = GetBlockID(x, y, z);

        //             if (currentBlockID == 0)
        //                 continue;

        //             Block currentBlock = Block::blocks[currentBlockID];
        //             currentBlock.mainCube.bind();
        //             currentBlock.mainCube.setMat4("view", view);
        //             currentBlock.mainCube.setMat4("projection", projection);

        //             glm::mat4 model = glm::mat4{1.0};
        //             model = glm::translate(model, {x, y, z});
        //             currentBlock.mainCube.setMat4("model", model);

        //             currentBlock.cubeMesh.Draw(currentBlock.mainCube);
        //         }
        //     }
        // }

        shader.bind();
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        glm::mat4 model = glm::mat4{1.0};
        model = glm::translate(model, (glm::vec3{xOffset * SIZE_X, yOffset * SIZE_Y, zOffset * SIZE_Z}));
        shader.setMat4("model", model);

        ChunkMesh.Draw(shader);


        // int indiciesAmount = 0;
        // for (int z = 0; z < SIZE_Z; z++) {
        //     for (int y = 0; y < SIZE_Y; y++) {
        //         for (int x = 0; x < SIZE_X; x++) {

        //             unsigned int currentBlockID = GetBlockID(x, y, z);

        //             if (currentBlockID == 0)
        //                 continue;

        //             Block currentBlock = Block::blocks.at(currentBlockID);

        //             for (int side = 0; side < currentBlock.Sides.size(); side++) {
        // 	      engine::Mesh::FromRawMesh(currentBlock.Sides[side].Mesh);
        // 	    }

        //         }
        //     }
        // }
        // std::cout << ChunkMesh.vertices[1050].position.x << std::endl;
        // std::cout << ChunkMesh.vertices[1050].position.y << std::endl;
        // std::cout << ChunkMesh.vertices[1050].position.z << std::endl;
    }

}// namespace VoxelGame
