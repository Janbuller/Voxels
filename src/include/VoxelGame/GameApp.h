#pragma once

#include "VoxelGame/Chunk.h"
#include "VoxelGame/Map.h"
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

      // Chunk chunk1{BlockAtlas, 0, 0};
      Map map{BlockAtlas, 123456u};
    private:
        void onCreate() override;
        bool onUpdate() override;

        void DoInput(double deltaTime) {
            DoKeyboardInput(deltaTime);
            DoMouseInput();
        }

        void onKeyPressed(int key, int scancode, int action, int mods) override;
        void DoKeyboardInput(double deltaTime);
        void DoMouseInput();
    };
}// namespace VoxelGame
