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
  VoxelGame::GameApp app{640, 480, "Hello, World!"};
  app.run();
  return 0;
  // glcore::Window window{};
  // window.CaptureMouse(true);

  // glEnable(GL_DEPTH_TEST);
  // glEnable(GL_CULL_FACE);
  // glCullFace(GL_FRONT); 
  // glFrontFace(GL_CW);  

  // engine::Mesh cubeMesh = engine::Mesh::LoadOBJ("cube.obj", "res/");

  // engine::Camera mainCam{{0.0f, 2.0f, 1.0f}};

  // glcore::Shader mainCube{"res/shaders/mainCube.vert", "res/shaders/mainCube.frag"};

  // auto [lastxpos, lastypos] = window.GetCursorPos();

  // while (!window.ShouldClose()) {
  //   if (window.GetKeyState(GLFW_KEY_W) == glcore::Window::KeyState::KEY_PRESS)
  //     mainCam.ProcessKeyboard(engine::Camera::MovDir::FORWARD, window.deltaTime);
  //   if (window.GetKeyState(GLFW_KEY_S) == glcore::Window::KeyState::KEY_PRESS)
  //     mainCam.ProcessKeyboard(engine::Camera::MovDir::BACKWARD, window.deltaTime);
  //   if (window.GetKeyState(GLFW_KEY_A) == glcore::Window::KeyState::KEY_PRESS)
  //     mainCam.ProcessKeyboard(engine::Camera::MovDir::LEFT, window.deltaTime);
  //   if (window.GetKeyState(GLFW_KEY_D) == glcore::Window::KeyState::KEY_PRESS)
  //     mainCam.ProcessKeyboard(engine::Camera::MovDir::RIGHT, window.deltaTime);

  //   auto [xpos, ypos] = window.GetCursorPos();

  //   double x = xpos - lastxpos;
  //   double y = ypos - lastypos;

  //   lastxpos = xpos;
  //   lastypos = ypos;

  //   mainCam.ProcessMouseMovement(x, -y, true);

  //   glClearColor(0.2, 0.3, 0.1, 1.0);
  //   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
  //   glm::mat4 projection = glm::perspective(glm::radians(mainCam.Zoom), (float)window.width / (float)window.height, 0.1f, 100.0f);
  //   glm::mat4 view = mainCam.GetViewMatrix();
  //   glm::mat4 model{1.0};
  //   model = glm::mat4{1.0};
  //   model = glm::translate(model, {0, 0, 0});
  //   // model = glm::scale(model, {3, 3, 3});

  //   mainCube.bind();
  //   mainCube.setMat4("view", view);
  //   mainCube.setMat4("projection", projection);

  //   for    (int z = 0; z < 16; z++) {
  //     for  (int y = 0; y < 16; y++) {
  // 	for(int x = 0; x < 16; x++) {
  // 	  model = glm::mat4{1.0};
  // 	  model = glm::translate(model, {x, y, z});
  // 	  mainCube.setMat4("model", model);
  // 	  cubeMesh.Draw(mainCube);
  // 	}
  //     }
  //   }

  //   window.Update();
  //   window.SwapBuffers();
  // }
  
  return 0;
}
