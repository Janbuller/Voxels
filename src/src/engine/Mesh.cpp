#include "engine/Mesh.h"
#include "engine/Vertex.h"
#include "glcore/Shader.h"
#include "glcore/Texture.h"
#include <fstream>
#include <glad/glad.h>
#include <sstream>
#include <vector>

namespace engine {
    Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indicies,
                       std::vector<glcore::Texture> textures) {
        this->vertices = vertices;
        this->indicies = indicies;
        this->textures = textures;

        SetupBuffers();
    }

    void Mesh::SetupBuffers() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0],
                     GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(unsigned int),
                     &indicies[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) 0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              (void *) offsetof(Vertex, normal));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                              (void *) offsetof(Vertex, texCoords));

        glBindVertexArray(0);
    }

    void Mesh::Draw(glcore::Shader &shader) {
        int diffuseNr = 1;

        for (unsigned int i = 0; i < textures.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + i);

            std::string number;
            std::string type = "texture_diffuse";
            if (type == "texture_diffuse") {
                number = std::to_string(diffuseNr++);

                shader.setInt(("material." + type + number).c_str(), i);
                glBindTexture(GL_TEXTURE_2D, textures[i].id);
            }
            glActiveTexture(GL_TEXTURE0);

            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }
    }

}// namespace engine
