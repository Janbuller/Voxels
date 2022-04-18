#include "VoxelGame/GameApp.h"
#include "VoxelGame/Block.h"
#include "VoxelGame/Chunk.h"
#include "engine/Application.h"
#include "engine/Camera.h"
#include "engine/Mesh.h"
#include "glcore/Shader.h"
#include "glcore/Window.h"
#include <functional>

namespace VoxelGame {
    void GameApp::onCreate() {
        AppWindow.CaptureMouse(true);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        glFrontFace(GL_CW);

	Block::blocks[1] = Block{};
    }

    bool GameApp::onUpdate(double deltaTime) {
        DoInput(deltaTime);

        glClearColor(0.2, 0.3, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(mainCam.Zoom), (float) AppWindow.width / (float) AppWindow.height, 0.1f, 100.0f);
        glm::mat4 view = mainCam.GetViewMatrix();

	chunk.Draw(0, 0, 0, view, projection);

        // glm::mat4 model{1.0};
        // model = glm::mat4{1.0};
        // model = glm::translate(model, {0, 0, 0});
        // model = glm::scale(model, {3, 3, 3});

        // mainCube.bind();
        // mainCube.setMat4("view", view);
        // mainCube.setMat4("projection", projection);

        // for (int z = 0; z < 16; z++) {
        //     for (int y = 0; y < 16; y++) {
        //         for (int x = 0; x < 16; x++) {
        //             model = glm::mat4{1.0};
        //             model = glm::translate(model, {x, y, z});
        //             mainCube.setMat4("model", model);
        //             cubeMesh.Draw(mainCube);
        //         }
        //     }
        // }

        return true;
    }

    void GameApp::DoKeyboardInput(double deltaTime) {
        if (AppWindow.GetKeyState(GLFW_KEY_W) == glcore::Window::KeyState::KEY_PRESS)
            mainCam.ProcessKeyboard(engine::Camera::MovDir::FORWARD, deltaTime);
        if (AppWindow.GetKeyState(GLFW_KEY_S) == glcore::Window::KeyState::KEY_PRESS)
            mainCam.ProcessKeyboard(engine::Camera::MovDir::BACKWARD, deltaTime);
        if (AppWindow.GetKeyState(GLFW_KEY_A) == glcore::Window::KeyState::KEY_PRESS)
            mainCam.ProcessKeyboard(engine::Camera::MovDir::LEFT, deltaTime);
        if (AppWindow.GetKeyState(GLFW_KEY_D) == glcore::Window::KeyState::KEY_PRESS)
            mainCam.ProcessKeyboard(engine::Camera::MovDir::RIGHT, deltaTime);
    }

    void GameApp::DoMouseInput() {
      // Get the relative mouse movement from the ~RelativeMouse~
      // ~DeltaVariable~.
      auto [x, y] = RelativeMouse.GetDelta(AppWindow.GetCursorPos());

      mainCam.ProcessMouseMovement(x, -y, true);
    }
}// namespace VoxelGame
