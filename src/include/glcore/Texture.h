#pragma once

#include <string>

namespace glcore {
    struct Texture {
      unsigned int m_ID;
      std::string m_Path;

      int m_Width, m_Height;

      Texture(unsigned int ID, std::string Path, int Width, int Height);

      static Texture LoadTextureFromFile(const char* Path);
      static Texture LoadTextureFromFile(const char* Path, const std::string &Directory);
    };
}

