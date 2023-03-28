#pragma once

#include "VoxelGame/Player.h"
#include "glcore/Texture.h"

namespace VoxelGame {
    struct GameContext{
        Player m_MainPlayer{{0.0f, 64.0f, 0.0f}};

        glcore::Texture m_BlockAtlas = glcore::Texture::LoadTextureFromFile("res/textures.png");
        int m_BlockAtlasTexSize = 16;

        Map m_MainMap{m_BlockAtlas, 123456u};
    };
}
