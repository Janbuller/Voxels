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
    const char *m_VertexPath;
    const char *m_FragmentPath;
  public:
    unsigned int ID;
    
    Shader(const char *VertexPath, const char *FragmentPath);
    
    GLuint LoadShaderFromFiles(const char *VertexPath, const char *FragmentPath);
    
    void Bind();
    
    void SetBool (const std::string &Name, bool Value) const;
    void SetInt  (const std::string &Name, int Value) const;
    void SetFloat(const std::string &Name, float Value) const;
    void SetVec2 (const std::string &Name, float x, float y) const;
    void SetVec3 (const std::string &Name, float x, float y, float z) const;
    void SetVec3 (const std::string &Name, const glm::vec3 &Value) const;
    void SetVec3 (const std::string &Name, const float Value[]) const;
    void SetMat4 (const std::string &Name, const glm::mat4 &Mat) const;
    
    void Reload();
  };
}
