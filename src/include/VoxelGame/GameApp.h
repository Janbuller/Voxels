#pragma once
#include "VoxelGame/Chunk.h"
#include "VoxelGame/GameContext.h"
#include "VoxelGame/Layer.h"
#include "VoxelGame/Map.h"
#include "VoxelGame/Player.h"
#include "VoxelGame/layers/GameLayer.h"
#include "engine/Application.h"
#include "engine/Camera.h"
#include "engine/DeltaVariable.h"
#include "VoxelGame/Layer.h"
#include "engine/Mesh.h"
#include "engine/RawMesh.h"
#include "glcore/Shader.h"
#include "glcore/Texture.h"
#include <array>
#include "engine/Base.h"

namespace VoxelGame {
    class GameApp : public engine::Application {

        using engine::Application::Application;

    private:
        engine::DeltaVariable<double, 2> m_RelativeMouse{std::array<double, 2>{0, 0}};

    private:
	sptr<GameContext> m_Context = MkSptr<GameContext>();

	std::array<uptr<Layer>, 1> m_Layers = {
	    MkUptr<layers::GameLayer>(m_AppWindow.m_Width, m_AppWindow.m_Height, m_Context)
	};

    private:
        void onCreate() override;
        bool onUpdate() override;

        void DoInput(double DeltaTime) {
            DoKeyboardInput(DeltaTime);
            DoMouseInput(DeltaTime);
        }

        void onKeyPressed(int Key, int Scancode, int Action, int Mods) override;
        void onMouseButtonPressed(int Button, int Action, int Mods) override;

        void DoKeyboardInput(double DeltaTime);
        void DoMouseInput(double DeltaTime);
    };
}// namespace VoxelGame
