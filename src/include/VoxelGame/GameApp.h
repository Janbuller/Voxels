#pragma once
#include "VoxelGame/Chunk.h"
#include "VoxelGame/Map.h"
#include "VoxelGame/Player.h"
#include "engine/Application.h"
#include "engine/Camera.h"
#include "engine/DeltaVariable.h"
#include "engine/Mesh.h"
#include "engine/RawMesh.h"
#include "glcore/Shader.h"
#include "glcore/Texture.h"
#include <array>


namespace VoxelGame {
    class GameApp : public engine::Application {

        using engine::Application::Application;

    private:
        // engine::Mesh cubeMesh = engine::Mesh::LoadOBJ("cube.obj", "res/");
        Player MainPlayer{{0.0f, 64.0f, 0.0f}};
        glcore::Shader MainCube{"res/shaders/mainCube.vert", "res/shaders/mainCube.frag"};

        engine::DeltaVariable<double, 2> RelativeMouse{std::array<double, 2>{0, 0}};

        glcore::Texture BlockAtlas = glcore::Texture::LoadTextureFromFile("res/textures.png");
        int BlockAtlasTexSize = 16;

        Map MainMap{BlockAtlas, 123456u};

        engine::Mesh indicator = engine::Mesh::FromRawMesh(engine::RawMesh::LoadOBJ("cube.obj", "res"), {glcore::Texture::LoadTextureFromFile("res/texture.png")});

    private:
        void onCreate() override;
        bool onUpdate() override;

        void DoInput(double deltaTime) {
            DoKeyboardInput(deltaTime);
            DoMouseInput();
        }

        void onKeyPressed(int key, int scancode, int action, int mods) override;
        void onMouseButtonPressed(int button, int action, int mods) override;

        void DoKeyboardInput(double deltaTime);
        void DoMouseInput();
    };
}// namespace VoxelGame
