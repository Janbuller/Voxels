#pragma once

#include <string>
#include <SDL2/SDL.h>

namespace glcore {
    struct Texture {
      unsigned int id;
      std::string path;

      int width, height;

      Texture(unsigned int id, std::string path, int width, int height);

      static Texture LoadTextureFromFile(const char* path);
      static Texture LoadTextureFromFile(const char* path, const std::string &directory);
    };
}

