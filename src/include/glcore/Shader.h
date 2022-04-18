#pragma once

#include <glad/glad.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <glm/glm.hpp>

namespace glcore {
  class Shader {
  private:
    const char *vertexPath;
    const char *fragmentPath;
  public:
    unsigned int ID;
    
    Shader(const char *vertexPath, const char *fragmentPath);
    
    GLuint loadShaderFromFiles(const char *vertexPath, const char *fragmentPath);
    
    void bind();
    
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec2(const std::string &name, float x, float y) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec3(const std::string &name, const float value[]) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;
    
    void reload();
  };
}
