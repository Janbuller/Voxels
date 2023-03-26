#include "glcore/Window.h"
#include <cstdint>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <tuple>

namespace glcore {
  void Window::onWindowResize(int Width, int Height) {
    this->m_Width = Width;
    this->m_Height = Height;
    
    glViewport(0, 0, Width, Height);
  }

  void Window::onKeyPressed(int Key, int Scancode, int Action, int Mods) {
    if(KeyPressedCallback != nullptr) {
      KeyPressedCallback(Key, Scancode, Action, Mods);
    }
  }

  void Window::onMouseButtonPressed(int Button, int Action, int Mods) {
    if(MouseButtonPressedCallback != nullptr) {
      MouseButtonPressedCallback(Button, Action, Mods);
    }
  }

  Window::Window(int Width, int Height, std::string Title) :
    m_Width(Width), m_Height(Height), m_Title(Title),
    m_DeltaTime(std::array<double, 1>{ glfwGetTime() }){
    if (!glfwInit())
      throw -1;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(Width, Height, Title.c_str(), NULL, NULL);
    if (!m_Window) {
        glfwTerminate();
        throw -1;
    }

    glfwMakeContextCurrent(m_Window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cerr << "Failed to initialize GLAD." << std::endl;
      throw -1;
    }

    glViewport(0, 0, Width, Height);
    m_LastFrame = glfwGetTime();

    // Use c++ lambda function as callback for glfw, forwarding it to
    // the onWindowResize function of this class, since glfw is a
    // c-library and doesn't support methods.

    glfwSetWindowUserPointer(m_Window, this);

    auto windowSizeCallback = [](GLFWwindow* w, int width, int height)
    {
      static_cast<Window*>(glfwGetWindowUserPointer(w))->onWindowResize(width, height);
    };
    glfwSetWindowSizeCallback(m_Window, windowSizeCallback);

    auto keyCallback = [](GLFWwindow* w, int key, int scancode, int action, int mods)
    {
      static_cast<Window*>(glfwGetWindowUserPointer(w))->onKeyPressed(key, scancode, action, mods);
    };
    glfwSetKeyCallback(m_Window, keyCallback);

    auto mouseButtonCallback = [](GLFWwindow* w, int button, int action, int mods)
    {
      static_cast<Window*>(glfwGetWindowUserPointer(w))->onMouseButtonPressed(button, action, mods);
    };
    glfwSetMouseButtonCallback(m_Window, mouseButtonCallback);
  }

  Window::~Window() {
    glfwDestroyWindow(m_Window);
    glfwTerminate();
  }

  void Window::SwapBuffers() {
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
  }

  void Window::Update() {
  }

  double Window::GetDeltaTime() {
    return m_DeltaTime.GetDelta( {glfwGetTime()} )[0];
  }

  bool Window::ShouldClose() {
    return glfwWindowShouldClose(m_Window);
  }

  void Window::SetShouldClose(bool Close) {
    glfwSetWindowShouldClose(m_Window, Close);
  }
    

  void Window::CaptureMouse(bool Capture) {
    if(Capture)
      glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    else
      glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  }

  bool Window::IsMouseCaptured() {
    int inputMode = glfwGetInputMode(m_Window, GLFW_CURSOR);
    return inputMode == GLFW_CURSOR_NORMAL ? false : true;
  }

  void Window::SetTitle(std::string Title) {
    glfwSetWindowTitle(m_Window, Title.c_str());
  }

  Window::KeyState Window::GetKeyState(int Key) {
    int state = glfwGetKey(m_Window, Key);

    if(state == GLFW_PRESS)
      return Window::KeyState::KEY_PRESS;
    if(state == GLFW_RELEASE)
      return Window::KeyState::KEY_RELEASE;

    return Window::KeyState::NONE;
  }

  std::array<double, 2> Window::GetCursorPos() {
    double x, y;
    glfwGetCursorPos(m_Window, &x, &y);

    return {x, y};
  }


  void Window::SetKeyPressedCallback(std::function<void(int Key, int Scandcode, int Action, int Mods)> Callback) {
    KeyPressedCallback = Callback;
  }

  void Window::SetMouseButtonPressedCallback(std::function<void(int Button, int Action, int Mods)> Callback) {
    MouseButtonPressedCallback = Callback;
  }
} // namespace glcore
