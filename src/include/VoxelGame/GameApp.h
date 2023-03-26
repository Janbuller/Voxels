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
        Player m_MainPlayer{{0.0f, 64.0f, 0.0f}};
        glcore::Shader m_MainCube{"res/shaders/mainCube.vert", "res/shaders/mainCube.frag"};

        engine::DeltaVariable<double, 2> m_RelativeMouse{std::array<double, 2>{0, 0}};

        glcore::Texture m_BlockAtlas = glcore::Texture::LoadTextureFromFile("res/textures.png");
        int m_BlockAtlasTexSize = 16;

        Map m_MainMap{m_BlockAtlas, 123456u};

        engine::Mesh m_IndicatorMesh = engine::Mesh::FromRawMesh(engine::RawMesh::LoadOBJ("cube.obj", "res"), {glcore::Texture::LoadTextureFromFile("res/texture.png")});

    private:
        void onCreate() override;
        bool onUpdate() override;

        void DoInput(double DeltaTime) {
            DoKeyboardInput(DeltaTime);
            DoMouseInput();
        }

        void onKeyPressed(int Key, int Scancode, int Action, int Mods) override;
        void onMouseButtonPressed(int Button, int Action, int Mods) override;

        void DoKeyboardInput(double DeltaTime);
        void DoMouseInput();
    };
}// namespace VoxelGame
