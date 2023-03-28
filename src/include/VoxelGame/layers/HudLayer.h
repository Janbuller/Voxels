#pragma once
#include "VoxelGame/GameContext.h"
#include "VoxelGame/Layer.h"
#include "engine/Mesh.h"
#include "glcore/Shader.h"

namespace VoxelGame::layers {
    class HudLayer : public VoxelGame::Layer {
    protected:
        std::string m_Title = "HUD";

    public:
        HudLayer(int Width, int Height, sptr<GameContext> Context) {
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
