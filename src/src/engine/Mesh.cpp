#include "engine/Mesh.h"
#include "engine/Vertex.h"
#include "glcore/Shader.h"
#include "glcore/Texture.h"
#include <fstream>
#include <glad/glad.h>
#include <sstream>
#include <vector>

namespace engine {
    Mesh::Mesh(std::vector<Vertex> Vertices, std::vector<unsigned int> Indicies,
               std::vector<glcore::Texture> Textures) {
        this->m_Vertices = Vertices;
        this->m_Indicies = Indicies;
        this->m_Textures = Textures;

        SetupBuffers();
    }

    void Mesh::SetupBuffers() {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), &m_Vertices[0],
                     GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indicies.size() * sizeof(unsigned int),
                     &m_Indicies[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) 0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              (void *) offsetof(Vertex, Normal));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              (void *) offsetof(Vertex, TexCoords));

        glBindVertexArray(0);

        m_Initialized = true;
    }

    void Mesh::Draw(glcore::Shader &Shader) {
        if (!m_Initialized)
            SetupBuffers();

        int diffuseNr = 1;

        for (unsigned int i = 0; i < m_Textures.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + i);

            std::string number;
            std::string type = "texture_diffuse";
            if (type == "texture_diffuse") {
                number = std::to_string(diffuseNr++);

                Shader.SetInt(("material." + type + number).c_str(), i);
                glBindTexture(GL_TEXTURE_2D, m_Textures[i].m_ID);
            }
            glActiveTexture(GL_TEXTURE0);

            glBindVertexArray(m_VAO);
            glDrawElements(GL_TRIANGLES, m_Indicies.size(), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }
    }

}// namespace engine
