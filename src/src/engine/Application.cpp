#include "engine/Application.h"
#include "glcore/Window.h"
#include <string>

namespace engine {
    Application::Application(int width, int height, std::string title) : AppWindow{width, height, title} {
    }
    void Application::run() {
        onCreate();
        while (!AppWindow.ShouldClose()) {
            AppWindow.Update();

            if (!onUpdate(AppWindow.GetDeltaTime())) {
                AppWindow.SetShouldClose(true);
            }

            AppWindow.SwapBuffers();
        }
        onExit();
    }

    void Application::onCreate() {
    }
    bool Application::onUpdate(double deltaTime) {
        glClearColor(0.2, 0.3, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Key 256 is the escape key.
        // This is used to avoid pulling in the glfw headers
        if (AppWindow.GetKeyState(256) == glcore::Window::KeyState::KEY_PRESS) {
            return false;
        }

        return true;
    }
    void Application::onExit() {
    }
}// namespace engine
