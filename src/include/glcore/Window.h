#pragma once

#include "engine/DeltaVariable.h"
#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <tuple>

namespace glcore {
  class Window {
  private:
    bool MouseCaptured = true;
    float lastFrame;
    void onWindowResize(int width, int height);

    engine::DeltaVariable<double, 1> deltaTime;

  public:
    int width = 640, height = 480;
    std::string title;

    GLFWwindow* window;
    
    Window(int width = 640, int height = 480, std::string title = "Window");
    ~Window();
    void SwapBuffers();
    void Update();

    double GetDeltaTime();

    bool ShouldClose();
    void SetShouldClose(bool close);

    void CaptureMouse(bool capture);
    bool IsMouseCaptured();

    void SetTitle(std::string title);

    enum class KeyState {
      KEY_PRESS,
      KEY_RELEASE,

      NONE
    };
    KeyState GetKeyState(int key);
    std::array<double, 2> GetCursorPos();
  };
} // namespace glcore
