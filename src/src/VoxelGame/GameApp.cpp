#include "VoxelGame/GameApp.h"
#include "GLFW/glfw3.h"
#include "VoxelGame/Block.h"
#include "VoxelGame/Chunk.h"
#include "VoxelGame/Player.h"
#include "engine/Application.h"
#include "engine/Camera.h"
#include "engine/Mesh.h"
#include "glcore/Shader.h"
#include "glcore/Window.h"
#include <functional>
#include <utility>

namespace VoxelGame {
    void GameApp::onCreate() {
        m_AppWindow.CaptureMouse(true);

	for(auto& Layer : m_Layers)
	    Layer->onCreate();
    }

    bool GameApp::onUpdate() {
        DoInput(m_DeltaTime);

	for(auto& Layer : m_Layers)
	    Layer->onUpdate(m_DeltaTime);

	for(auto& Layer : m_Layers) {
	    Layer->m_Width = m_AppWindow.m_Width;
	    Layer->m_Height = m_AppWindow.m_Height;
	    Layer->onDraw();
	}

        return true;
    }

    void GameApp::onKeyPressed(int Key, int Scancode, int Action, int Mods) {
        if (Key == GLFW_KEY_ESCAPE && Action == GLFW_PRESS)
            m_AppWindow.CaptureMouse(!m_AppWindow.IsMouseCaptured());

	for(auto& Layer : m_Layers)
	    Layer->onKeyPressed(Key, Scancode, Action, Mods);
    }

    void GameApp::onMouseButtonPressed(int Button, int Action, int Mods) {
	for(auto& Layer : m_Layers)
	    Layer->onMouseButtonPressed(Button, Action, Mods);
    }

    void GameApp::DoKeyboardInput(double DeltaTime) {
	for(auto& Layer : m_Layers)
	    Layer->DoKeyboardInput(DeltaTime, [this](int Key){return m_AppWindow.GetKeyState(Key);});
    }

    void GameApp::DoMouseInput(double DeltaTime) {
        // Get the relative mouse movement from the ~RelativeMouse~
        // DeltaVariable.
	auto [AbsX, AbsY] = m_AppWindow.GetCursorPos();
        auto [x, y] = m_RelativeMouse.GetDelta(m_AppWindow.GetCursorPos());

	for(auto& Layer : m_Layers)
	    Layer->DoMouseMovement(m_DeltaTime, glm::vec2{AbsX, AbsY}, glm::vec2{x, y});
    }
}// namespace VoxelGame
