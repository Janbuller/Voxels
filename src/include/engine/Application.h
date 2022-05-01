#pragma once

#include "glcore/Window.h"
#include <string>

namespace engine {
  class Application {
  protected:
    glcore::Window AppWindow;

  public:
    Application(int width, int height, std::string title);
    void run();

  public:
    virtual void onCreate();

    virtual bool onUpdate(double deltaTime);

    virtual void onExit();

    virtual void onKeyPressed(int key, int scancode, int action, int mods);
  };
}// namespace engine
