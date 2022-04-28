#pragma once

#include "Vertex.h"
#include "engine/RawMesh.h"
#include "glcore/Shader.h"
#include "glcore/Texture.h"
#include <vector>

namespace engine {
    class Mesh {
    public:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indicies;
        std::vector<glcore::Texture> textures;

        Mesh() {}
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indicies, std::vector<glcore::Texture> textures);
        void Draw(glcore::Shader &shader);

        static Mesh FromRawMesh(RawMesh raw, std::vector<glcore::Texture> tex) {
            return Mesh(raw.vertices, raw.indicies, tex);
        }

        void SetupBuffers();
    private:
        unsigned int VAO, VBO, EBO;

    };
}// namespace engine
