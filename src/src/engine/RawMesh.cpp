#include "engine/RawMesh.h"
#include "engine/Vertex.h"
#include "glcore/Shader.h"
#include "glcore/Texture.h"
#include <fstream>
#include <glad/glad.h>
#include <sstream>
#include <vector>

engine::RawMesh::RawMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indicies) {
  this->vertices = vertices;
  this->indicies = indicies;
}

engine::RawMesh engine::RawMesh::LoadOBJ(const char* path, const std::string directory) {

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

  return engine::RawMesh{vertices, indicies};
}

