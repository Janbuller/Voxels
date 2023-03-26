#include "engine/Application.h"
#include "glcore/Window.h"
#include <string>
#include <iostream>

namespace engine {
    Application::Application(int Width, int Height, std::string Title) : m_AppWindow{Width, Height, Title} {

        auto keyCallback = [this](int Key, int Scancode, int Action, int Mods) {
            onKeyPressed(Key, Scancode, Action, Mods);
        };
        m_AppWindow.SetKeyPressedCallback(keyCallback);

        auto mouseButtonCallback = [this](int Button, int Action, int Mods) {
            onMouseButtonPressed(Button, Action, Mods);
        };
        m_AppWindow.SetMouseButtonPressedCallback(mouseButtonCallback);
    }

    void Application::run() {
        onCreate();
        while (!m_AppWindow.ShouldClose()) {
            m_AppWindow.Update();

	    m_DeltaTime = m_AppWindow.GetDeltaTime();
            if (!onUpdate()) {
                m_AppWindow.SetShouldClose(true);
            }

            m_AppWindow.SwapBuffers();
        }
        onExit();
    }

    void Application::onCreate() {
    }
    bool Application::onUpdate() {
        glClearColor(0.2, 0.3, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Key 256 is the escape key.
        // This is used to avoid pulling in the glfw headers
        if (m_AppWindow.GetKeyState(256) == glcore::Window::KeyState::KEY_PRESS) {
            return false;
        }

        return true;
    }
    void Application::onExit() {
    }

  void Application::onKeyPressed(int Key, int Scancode, int Action, int Mods) {

  }

  void Application::onMouseButtonPressed(int Button, int Action, int Mods) {
    
  }
}// namespace engine
