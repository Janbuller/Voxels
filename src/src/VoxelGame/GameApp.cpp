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
        Block::blocks.insert(std::make_pair(1, Block{BlockAtlas, BlockAtlasTexSize}));

	// lasse: 8.309 sec.
	double timestart = glfwGetTime();
	for(int i = 0; i < 25; i++) {
	  chunk1.GenerateChunkMesh();
	  chunk2.GenerateChunkMesh();
	  chunk3.GenerateChunkMesh();
	  chunk4.GenerateChunkMesh();
	}
	std::cout << glfwGetTime() - timestart << std::endl;
    }
    bool GameApp::onUpdate(double deltaTime) {
        DoInput(deltaTime);
        glClearColor(0.2, 0.3, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 projection = glm::perspective(glm::radians(mainCam.Zoom), (float) AppWindow.width / (float) AppWindow.height, 0.1f, 10000.0f);
        glm::mat4 view = mainCam.GetViewMatrix();

        chunk1.Draw(mainCube, 0, 0, 0, view, projection);
        chunk2.Draw(mainCube, 1, 0, 0, view, projection);
        chunk3.Draw(mainCube, 0, 0, 1, view, projection);
        chunk4.Draw(mainCube, 1, 0, 1, view, projection);
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
