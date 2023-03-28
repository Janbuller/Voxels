#include "VoxelGame/GameApp.h"
#include "glcore/Window.h"
#include "glcore/Shader.h"
#include "engine/Camera.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "engine/Mesh.h"
#include "engine/Application.h"

int main(void) {

  VoxelGame::GameApp app{640, 480, "Voxels!"};
  app.run();

  return 0;
}
