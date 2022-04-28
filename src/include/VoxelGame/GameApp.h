#pragma once

#include "VoxelGame/Chunk.h"
#include "engine/Application.h"
#include "engine/Camera.h"
#include "engine/DeltaVariable.h"
#include "engine/Mesh.h"
#include "glcore/Shader.h"
#include "glcore/Texture.h"
#include <array>


namespace VoxelGame {
    class GameApp : public engine::Application {

        using engine::Application::Application;

    private:
        // engine::Mesh cubeMesh = engine::Mesh::LoadOBJ("cube.obj", "res/");
        engine::Camera mainCam{{0.0f, 64.0f, 1.0f}};
        glcore::Shader mainCube{"res/shaders/mainCube.vert", "res/shaders/mainCube.frag"};

        engine::DeltaVariable<double, 2> RelativeMouse{std::array<double, 2>{0, 0}};

        glcore::Texture BlockAtlas = glcore::Texture::LoadTextureFromFile("res/textures.png");
        int BlockAtlasTexSize = 16;

      Chunk chunk1{BlockAtlas, 0, 0};
      Chunk chunk2{BlockAtlas, 1, 0};
      Chunk chunk3{BlockAtlas, 0, 1};
      Chunk chunk4{BlockAtlas, 1, 1};

    private:
        void onCreate() override;
        bool onUpdate(double deltaTime) override;

        void DoInput(double deltaTime) {
            DoKeyboardInput(deltaTime);
            DoMouseInput();
        }

        void DoKeyboardInput(double deltaTime);
        void DoMouseInput();
    };
}// namespace VoxelGame
