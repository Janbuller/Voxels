#include "VoxelGame/Block.h"
#include "VoxelGame/BlockSideInfo.h"
#include "engine/RawMesh.h"
#include "glcore/Shader.h"
#include "glcore/Texture.h"
#include <algorithm>
#include <map>
#include <vector>

namespace VoxelGame {

    Block::Block(glcore::Texture texture, int texSize) {
        Sides.push_back(
                BlockSideInfo{
                        BlockSide::POS_X,
                        engine::RawMesh::LoadOBJ("cube-xp.obj", "res/models/cube-faces"),
                        2});
        Sides.push_back(
                BlockSideInfo{
                        BlockSide::NEG_X,
                        engine::RawMesh::LoadOBJ("cube-xn.obj", "res/models/cube-faces"),
                        2});
        Sides.push_back(
                BlockSideInfo{
                        BlockSide::POS_Y,
                        engine::RawMesh::LoadOBJ("cube-yp.obj", "res/models/cube-faces"),
                        0});
        Sides.push_back(
                BlockSideInfo{
                        BlockSide::NEG_Y,
                        engine::RawMesh::LoadOBJ("cube-yn.obj", "res/models/cube-faces"),
                        1});
        Sides.push_back(
                BlockSideInfo{
                        BlockSide::POS_Z,
                        engine::RawMesh::LoadOBJ("cube-zp.obj", "res/models/cube-faces"),
                        2});
        Sides.push_back(
                BlockSideInfo{
                        BlockSide::NEG_Z,
                        engine::RawMesh::LoadOBJ("cube-zn.obj", "res/models/cube-faces"),
                        2});

        for (int i = 0; i < Sides.size(); i++) {
	  Sides[i].SetupTextureCoords(texture, texSize);
        }
    }

    std::map<unsigned int, Block> Block::blocks = {};
}// namespace VoxelGame
