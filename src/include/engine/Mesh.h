#pragma once

#include <vector>
#include "glcore/Texture.h"
#include "Vertex.h"
#include "glcore/Shader.h"

namespace engine {
    class Mesh {
    public:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indicies;
        std::vector<glcore::Texture> textures;

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indicies, std::vector<glcore::Texture> textures);
        void Draw(glcore::Shader &shader);

        static Mesh LoadOBJ(const char* path, const std::string directory);
    private:
        unsigned int VAO, VBO, EBO;

        void SetupBuffers();
    };
}

