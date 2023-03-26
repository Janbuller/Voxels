#pragma once

#include "Vertex.h"
#include "engine/RawMesh.h"
#include "glcore/Shader.h"
#include "glcore/Texture.h"
#include <vector>

namespace engine {
    class Mesh {
    public:
        std::vector<Vertex> m_Vertices;
        std::vector<unsigned int> m_Indicies;
        std::vector<glcore::Texture> m_Textures;

        Mesh() {}
        Mesh(std::vector<Vertex> Vertices, std::vector<unsigned int> Indicies, std::vector<glcore::Texture> Textures);
        void Draw(glcore::Shader &Shader);

        static Mesh FromRawMesh(RawMesh Raw, std::vector<glcore::Texture> Tex) {
            return Mesh(Raw.m_Vertices, Raw.m_Indicies, Tex);
        }

        void SetupBuffers();
      bool m_Initialized = false;
    private:
        unsigned int m_VAO, m_VBO, m_EBO;

    };
}// namespace engine
