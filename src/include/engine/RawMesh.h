#pragma once

#include <vector>
#include "Vertex.h"
#include "glcore/Shader.h"

namespace engine {
    class RawMesh {
    public:
        std::vector<Vertex> m_Vertices;
        std::vector<unsigned int> m_Indicies;

        RawMesh(std::vector<Vertex> Vertices, std::vector<unsigned int> Indicies);

        static RawMesh LoadOBJ(const char* Path, const std::string Directory);
    private:
    };
}
