#include "VoxelGame/GameApp.h"
#include "GLFW/glfw3.h"
#include "VoxelGame/Block.h"
#include "VoxelGame/Chunk.h"
#include "engine/Application.h"
#include "engine/Camera.h"
#include "engine/Mesh.h"
#include "glcore/Shader.h"
#include "glcore/Window.h"
#include <functional>
#include <utility>

namespace VoxelGame {
    void GameApp::onCreate() {
        AppWindow.CaptureMouse(true);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        glFrontFace(GL_CW);
	// Grass
        Block::blocks.insert(std::make_pair(1, Block{BlockAtlas, BlockAtlasTexSize, {2, 2, 0, 1, 2, 2}}));
	// Dirt
        Block::blocks.insert(std::make_pair(2, Block{BlockAtlas, BlockAtlasTexSize, 1}));
	// Stone
        Block::blocks.insert(std::make_pair(3, Block{BlockAtlas, BlockAtlasTexSize, 3}));
	// Bedrock
        Block::blocks.insert(std::make_pair(4, Block{BlockAtlas, BlockAtlasTexSize, 4}));
    }

    bool GameApp::onUpdate(double deltaTime) {
        DoInput(deltaTime);
        glClearColor(0.7, 0.7, 0.7, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 projection = glm::perspective(glm::radians(mainCam.Zoom), (float) AppWindow.width / (float) AppWindow.height, 0.1f, 10000.0f);
        glm::mat4 view = mainCam.GetViewMatrix();

        map.Draw(mainCube, view, projection, mainCam.Position, 5);
        return true;
    }

  void GameApp::onKeyPressed(int key, int scancode, int action, int mods) {
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

        if (AppWindow.GetKeyState(GLFW_KEY_LEFT_SHIFT) == glcore::Window::KeyState::KEY_PRESS)
            mainCam.SetSpeed(25);
        else
            mainCam.SetSpeed(5);

        if (AppWindow.GetKeyState(GLFW_KEY_R) == glcore::Window::KeyState::KEY_PRESS)
	  mainCube.reload();
        if (AppWindow.GetKeyState(GLFW_KEY_ESCAPE) == glcore::Window::KeyState::KEY_PRESS)
	  AppWindow.CaptureMouse(!AppWindow.IsMouseCaptured());
    }

    void GameApp::DoMouseInput() {
        // Get the relative mouse movement from the ~RelativeMouse~
        // ~DeltaVariable~.
        auto [x, y] = RelativeMouse.GetDelta(AppWindow.GetCursorPos());

        mainCam.ProcessMouseMovement(x, -y, true);
    }
}// namespace VoxelGame
