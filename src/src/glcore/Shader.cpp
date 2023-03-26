#include "glcore/Shader.h"

namespace glcore {
    Shader::Shader(const char *vertexPath, const char *fragmentPath) {
        ID = LoadShaderFromFiles(vertexPath, fragmentPath);
    }

    GLuint Shader::LoadShaderFromFiles(const char *vertexPath,
                                       const char *fragmentPath) {
        m_VertexPath = vertexPath;
        m_FragmentPath = fragmentPath;

        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;

            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            vShaderFile.close();
            fShaderFile.close();

            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        } catch (std::ifstream::failure &e) {
            std::cout << "Shader file could not be successfully loaded!" << std::endl;
        }
        const char *vShaderCode = vertexCode.c_str();
        const char *fShaderCode = fragmentCode.c_str();

        unsigned int vertex, fragment;
        int success;
        char infoLog[512];

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);

        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                      << infoLog << std::endl;
        }

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);

        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                      << infoLog << std::endl;
        }

        GLuint ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);

        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                      << infoLog << std::endl;
        }

        glDeleteShader(vertex);
        glDeleteShader(fragment);

        return ID;
    }
    void Shader::Bind() { glUseProgram(ID); }

    void Shader::SetBool(const std::string &Name, bool Value) const {
        glUniform1i(glGetUniformLocation(ID, Name.c_str()), (int) Value);
    }
    void Shader::SetInt(const std::string &Name, int Value) const {
        glUniform1i(glGetUniformLocation(ID, Name.c_str()), Value);
    }
    void Shader::SetFloat(const std::string &Name, float Value) const {
        glUniform1f(glGetUniformLocation(ID, Name.c_str()), Value);
    }
    void Shader::SetVec2(const std::string &Name, float x, float y) const {
        glUniform2f(glGetUniformLocation(ID, Name.c_str()), x, y);
    }
    void Shader::SetVec3(const std::string &Name, float x, float y, float z) const {
        glUniform3f(glGetUniformLocation(ID, Name.c_str()), x, y, z);
    }
    void Shader::SetVec3(const std::string &Name, const glm::vec3 &Value) const {
        glUniform3fv(glGetUniformLocation(ID, Name.c_str()), 1, &Value[0]);
    }
    void Shader::SetVec3(const std::string &Name, const float Value[]) const {
        glUniform3fv(glGetUniformLocation(ID, Name.c_str()), 1, &Value[0]);
    }
    void Shader::SetMat4(const std::string &Name, const glm::mat4 &Mat) const {
        glUniformMatrix4fv(glGetUniformLocation(ID, Name.c_str()), 1, GL_FALSE,
                           &Mat[0][0]);
    }
    void Shader::Reload() {
        glDeleteProgram(ID);
        ID = LoadShaderFromFiles(m_VertexPath, m_FragmentPath);
    }
}// namespace glcore
