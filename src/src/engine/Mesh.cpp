#include "engine/Mesh.h"
#include "glcore/Texture.h"
#include "engine/Vertex.h"
#include "glcore/Shader.h"
#include <fstream>
#include <glad/glad.h>
#include <sstream>
#include <vector>

engine::Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indicies,
                   std::vector<glcore::Texture> textures) {
  this->vertices = vertices;
  this->indicies = indicies;
  this->textures = textures;

  SetupBuffers();
}

engine::Mesh engine::Mesh::LoadOBJ(const char* path, const std::string directory) {

  std::string filename = std::string(path);
  filename = directory + '/' + filename;

  std::vector<glm::vec3> vertPosLoaded;
  std::vector<glm::vec3> vertNormLoaded;
  std::vector<glm::vec2> vertTexLoaded;
  std::vector<unsigned int> faces;

  std::ifstream file{ filename };

  if(!file.is_open())
    throw -1;

  while (!file.eof()) {

    // Read lines, assuming them to be less than 256 chars.
    char line[256];
    file.getline(line, 256);

    // Add line to a strstream
    std::stringstream lineStream;
    lineStream << line;

    // Variable to hold the first character, which is
    // unnecessary. This makes uing the streams easier.
    std::string firstChar;

    if (std::string{line}.substr(0, 2) == "v ") {
      glm::vec3 vert;
      lineStream >> firstChar >> vert.x >> vert.y >> vert.z;
      vertPosLoaded.push_back(vert);
    }

    if (std::string{line}.substr(0, 2) == "vn") {
      glm::vec3 vert{0, 0, 0};
      lineStream >> firstChar >> vert.x >> vert.y >> vert.z;
      vertNormLoaded.push_back(vert);
    }

    if (std::string{line}.substr(0, 2) == "vt") {
      glm::vec3 vert;
      lineStream >> firstChar >> vert.x >> vert.y >> vert.z;
      vertTexLoaded.push_back(vert);
    }

    if (line[0] == 'f') {
      std::string faceStr[3];
      std::string tmp;
      unsigned int tmpNr;
      lineStream >> firstChar >> faceStr[0] >> faceStr[1] >> faceStr[2];
      for(int i = 0; i < 3; i++)
	{
	  std::stringstream oneFace{faceStr[i]};
	  while(std::getline(oneFace, tmp, '/')) {
	    std::stringstream(tmp) >> tmpNr;
	    faces.push_back(tmpNr-1);

	    }
	}
    }
  }

  std::vector<Vertex> vertices;
  std::vector<unsigned int> indicies;
  std::vector<glcore::Texture> tex;

  glm::vec3 vertPos [faces.size()/3];
  glm::vec3 vertNorm[faces.size()/3];
  glm::vec2 vertTex [faces.size()/3];

  for(int i = 0; i < faces.size(); i+=3) {
    indicies.push_back(i/3);
    vertPos [i/3] = vertPosLoaded [faces[i+0]];
    vertTex [i/3] = vertTexLoaded [faces[i+1]];
    vertNorm[i/3] = vertNormLoaded[faces[i+2]];
  }

  for(int i = 0; i < faces.size()/3; i++) {
    vertices.push_back(Vertex{vertPos[i], vertNorm[i], vertTex[i]});
  }

  tex.push_back(
          glcore::Texture{glcore::Texture::LoadTextureFromFile("texture.png", directory), "texture_diffuse", filename});

  return engine::Mesh{vertices, indicies, tex};
}

void engine::Mesh::SetupBuffers() {
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
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, normal));
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void *)offsetof(Vertex, texCoords));

  glBindVertexArray(0);
}

void engine::Mesh::Draw(glcore::Shader &shader) {
  int diffuseNr = 1;

  for (unsigned int i = 0; i < textures.size(); i++) {
    glActiveTexture(GL_TEXTURE0 + i);

    std::string number;
    std::string type = textures[i].type;
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
