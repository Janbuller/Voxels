#pragma once
#include "VoxelGame/Block.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include <array>
#include <map>
namespace VoxelGame {
    class Chunk {
    public:
        static const int SIZE_X = 16;
        static const int SIZE_Y = 128;
        static const int SIZE_Z = 16;

    private:
        std::array<unsigned int, SIZE_X * SIZE_Y * SIZE_Z> chunkBlocks;

    public:
	Chunk() {
	  chunkBlocks.fill(1);
	}

	unsigned int GetBlockID(int x, int y, int z) {
	  /* std::cout << "max: " << SIZE_X * SIZE_Y * SIZE_Z << " : val: " << (z * SIZE_X * SIZE_Y) + (y * SIZE_X) + x << std::endl; */
	  return chunkBlocks[(z * SIZE_X * SIZE_Y) + (y * SIZE_X) + x];
	}

        void Draw(int xOffset, int yOffset, int zOffset, glm::mat4 view, glm::mat4 projection) {
            for (int z = 0; z < SIZE_Z; z++) {
                for (int y = 0; y < SIZE_Y; y++) {
                    for (int x = 0; x < SIZE_X; x++) {
		      unsigned int currentBlockID = GetBlockID(x, y, z);

		      if(currentBlockID == 0)
			continue;

		      Block currentBlock = Block::blocks[currentBlockID];
		      currentBlock.mainCube.bind();
		      currentBlock.mainCube.setMat4("view", view);
		      currentBlock.mainCube.setMat4("projection", projection);

		      glm::mat4 model = glm::mat4{1.0};
		      model = glm::translate(model, {x, y, z});
		      currentBlock.mainCube.setMat4("model", model);

		      currentBlock.cubeMesh.Draw(currentBlock.mainCube);
                    }
                }
            }
        }
    };
}// namespace VoxelGame
