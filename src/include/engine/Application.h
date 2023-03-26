#pragma once

#include "glcore/Window.h"
#include <string>

namespace engine {
  class Application {
  protected:
    glcore::Window m_AppWindow;
    double m_DeltaTime;

  public:
    Application(int Width, int Height, std::string Title);
    void run();

  public:
    virtual void onCreate();

    virtual bool onUpdate();

    virtual void onExit();

    virtual void onKeyPressed(int Key, int Scancode, int Action, int Mods);
    virtual void onMouseButtonPressed(int Button, int Action, int Mods);
  };
}// namespace engine
