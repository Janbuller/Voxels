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
    bool m_MouseCaptured = true;
    float m_LastFrame;

    void onWindowResize(int Width, int Height);
    void onKeyPressed(int Key, int Scancode, int Action, int Mods);
    void onMouseButtonPressed(int Button, int Action, int Mods);

    std::function<void(int Key, int Scandcode, int Action, int Mods)> KeyPressedCallback;
    std::function<void(int Button, int Action, int Mods)> MouseButtonPressedCallback;

    engine::DeltaVariable<double, 1> m_DeltaTime;

  public:
    int m_Width = 640, m_Height = 480;
    std::string m_Title;

    GLFWwindow* m_Window;
    
    Window(int Width = 640, int Height = 480, std::string Title = "Window");
    ~Window();
    void SwapBuffers();
    void Update();

    double GetDeltaTime();

    bool ShouldClose();
    void SetShouldClose(bool Close);

    void CaptureMouse(bool Capture);
    bool IsMouseCaptured();

    void SetTitle(std::string Title);

    enum class KeyState {
      KEY_PRESS,
      KEY_RELEASE,

      NONE
    };
    KeyState GetKeyState(int Key);
    std::array<double, 2> GetCursorPos();

    void SetKeyPressedCallback(std::function<void(int Key, int Scandcode, int Action, int Mods)> Callback);
    void SetMouseButtonPressedCallback(std::function<void(int Button, int Action, int Mods)> Callback);
  };
} // namespace glcore
