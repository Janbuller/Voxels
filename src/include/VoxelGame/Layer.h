#pragma once

#include "VoxelGame/GameContext.h"
#include "engine/Base.h"
#include <string>
#include <glm/glm.hpp>
#include <functional>
#include "glcore/Window.h"

namespace VoxelGame {
    class Layer {
    public:
        int m_Width = 0, m_Height = 0;
        std::string m_Title = "";

	sptr<GameContext> m_Context;

    public:
        virtual void onCreate() = 0;
        virtual void onUpdate(float DeltaTime) = 0;
	virtual void onDraw() = 0;
        virtual void onExit() = 0;

        virtual void onKeyPressed(int Key, int Scancode, int Action, int Mods) = 0;
        virtual void onMouseButtonPressed(int Button, int Action, int Mods) = 0;

	virtual void DoMouseMovement(double DeltaTime, glm::vec2 AbsLoc, glm::vec2 RelMov) = 0;
        virtual void DoKeyboardInput(double DeltaTime, std::function<glcore::Window::KeyState(int)> GetKeyState) = 0;
    };
}// namespace engine
