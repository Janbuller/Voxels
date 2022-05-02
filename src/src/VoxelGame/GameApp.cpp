#include "VoxelGame/GameApp.h"
#include "GLFW/glfw3.h"
#include "VoxelGame/Block.h"
#include "VoxelGame/Chunk.h"
#include "VoxelGame/Player.h"
#include "engine/Application.h"
#include "engine/Camera.h"
#include "engine/Mesh.h"
#include "glcore/Shader.h"
#include "glcore/Window.h"
#include <functional>
#include <utility>

namespace VoxelGame {
    using std::endl;

    void GameApp::onCreate() {
        AppWindow.CaptureMouse(true);
        glEnable(GL_DEPTH_TEST);
        // glEnable(GL_CULL_FACE);
        // glCullFace(GL_FRONT);
        // glFrontFace(GL_CW);
        // Grass
        Block::blocks.insert(std::make_pair(1, Block{BlockAtlas, BlockAtlasTexSize, {2, 2, 0, 1, 2, 2}}));
        // Dirt
        Block::blocks.insert(std::make_pair(2, Block{BlockAtlas, BlockAtlasTexSize, 1}));
        // Stone
        Block::blocks.insert(std::make_pair(3, Block{BlockAtlas, BlockAtlasTexSize, 3}));
        // Bedrock
        Block::blocks.insert(std::make_pair(4, Block{BlockAtlas, BlockAtlasTexSize, 4}));
    }

    bool GameApp::onUpdate() {
        DoInput(DeltaTime);
        glClearColor(0.7, 0.7, 0.7, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        MainPlayer.Update(&map, &mainCube, &indicator, AppWindow.width, AppWindow.height);

        glm::mat4 projection = MainPlayer.PlayerCam.GetProjectionMatrix(AppWindow.width, AppWindow.height);
        glm::mat4 view = MainPlayer.PlayerCam.GetViewMatrix();
        map.Draw(mainCube, view, projection, MainPlayer.PlayerCam.Position, 6);

        if (MainPlayer.RayHit) {
            mainCube.bind();
            mainCube.setMat4("view", view);
            mainCube.setMat4("projection", projection);

            glm::mat4 model = glm::mat4{1.0};
            int x = MainPlayer.LookRayHitLoc.x;
            int y = MainPlayer.LookRayHitLoc.y;
            int z = MainPlayer.LookRayHitLoc.z;
            model = glm::translate(model, glm::vec3{x, y, z});
            model = glm::scale(model, glm::vec3{1.1});
            mainCube.setMat4("model", model);

            mainCube.setFloat("FogDistance", 6);

            indicator.Draw(mainCube);
        }

        return true;
    }

    void GameApp::onKeyPressed(int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_R && action == GLFW_PRESS)
            mainCube.reload();
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            AppWindow.CaptureMouse(!AppWindow.IsMouseCaptured());

        if (key == GLFW_KEY_LEFT_SHIFT) {
            if (action == GLFW_PRESS)
                MainPlayer.PlayerCam.SetSpeed(25);
            else if (action == GLFW_RELEASE)
                MainPlayer.PlayerCam.SetSpeed(5);
        }
    }

    void GameApp::onMouseButtonPressed(int button, int action, int mods) {
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
            if (MainPlayer.RayHit) {
                map.SetBlockID(0,
                               MainPlayer.LookRayHitLoc.x,
                               MainPlayer.LookRayHitLoc.y,
                               MainPlayer.LookRayHitLoc.z);
            }
        }
    }

    void GameApp::DoKeyboardInput(double deltaTime) {
        if (AppWindow.GetKeyState(GLFW_KEY_W) == glcore::Window::KeyState::KEY_PRESS)
            MainPlayer.HandleKeyboard(engine::Camera::MovDir::FORWARD, deltaTime);
        if (AppWindow.GetKeyState(GLFW_KEY_S) == glcore::Window::KeyState::KEY_PRESS)
            MainPlayer.HandleKeyboard(engine::Camera::MovDir::BACKWARD, deltaTime);
        if (AppWindow.GetKeyState(GLFW_KEY_A) == glcore::Window::KeyState::KEY_PRESS)
            MainPlayer.HandleKeyboard(engine::Camera::MovDir::LEFT, deltaTime);
        if (AppWindow.GetKeyState(GLFW_KEY_D) == glcore::Window::KeyState::KEY_PRESS)
            MainPlayer.HandleKeyboard(engine::Camera::MovDir::RIGHT, deltaTime);
    }

    void GameApp::DoMouseInput() {
        // Get the relative mouse movement from the ~RelativeMouse~
        // ~DeltaVariable~.
        auto [x, y] = RelativeMouse.GetDelta(AppWindow.GetCursorPos());

        MainPlayer.PlayerCam.ProcessMouseMovement(x, -y, true);
    }
}// namespace VoxelGame
