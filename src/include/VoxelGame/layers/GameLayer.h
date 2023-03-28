#pragma once
#include "VoxelGame/GameContext.h"
#include "VoxelGame/Layer.h"
#include "engine/Camera.h"
#include "engine/Mesh.h"
#include "glcore/Window.h"
#include "glcore/Shader.h"
#include <functional>

namespace VoxelGame::layers {
    class GameLayer : public VoxelGame::Layer {

    private:
        glcore::Shader m_MainCube{"res/shaders/mainCube.vert", "res/shaders/mainCube.frag"};
        engine::Mesh m_IndicatorMesh = engine::Mesh::FromRawMesh(engine::RawMesh::LoadOBJ("cube.obj", "res"), {glcore::Texture::LoadTextureFromFile("res/texture.png")});

    protected:
        std::string m_Title = "Game";

    public:
        GameLayer(int Width, int Height, sptr<GameContext> Context) {
            m_Width = Width;
            m_Height = Height;
            m_Context = Context;
        }

        void onCreate() override;
        void onUpdate(float DeltaTime) override;
        void onDraw() override;
        void onExit() override;

        void onKeyPressed(int Key, int Scancode, int Action, int Mods) override;
        void onMouseButtonPressed(int Button, int Action, int Mods) override;

        void DoMouseMovement(double DeltaTime, glm::vec2 AbsLoc, glm::vec2 RelMov) override;
        void DoKeyboardInput(double DeltaTime, std::function<glcore::Window::KeyState(int)> GetKeyState) override;
    };
}// namespace VoxelGame::layers
