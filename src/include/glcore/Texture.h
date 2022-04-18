#pragma once

#include <string>
#include <SDL2/SDL.h>

namespace glcore {
    struct Texture {
      unsigned int id;
      std::string type;
      std::string path;

      static unsigned int LoadTextureFromFile(const char* path);
      static unsigned int LoadTextureFromFile(const char* path, const std::string &directory);
    };
}

