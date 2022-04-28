#pragma once

#include <vector>
#include "Vertex.h"
#include "glcore/Shader.h"

namespace engine {
    class RawMesh {
    public:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indicies;

        RawMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indicies);

        static RawMesh LoadOBJ(const char* path, const std::string directory);
    private:
        unsigned int VAO, VBO, EBO;
    };
}
