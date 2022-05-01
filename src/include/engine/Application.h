#pragma once

#include "glcore/Window.h"
#include <string>

namespace engine {
  class Application {
  protected:
    glcore::Window AppWindow;
    double DeltaTime;

  public:
    Application(int width, int height, std::string title);
    void run();

  public:
    virtual void onCreate();

    virtual bool onUpdate();

    virtual void onExit();

    virtual void onKeyPressed(int key, int scancode, int action, int mods);
  };
}// namespace engine
