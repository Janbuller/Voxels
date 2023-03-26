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
    void GameApp::onCreate() {
        m_AppWindow.CaptureMouse(true);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        glFrontFace(GL_CW);
        // Grass
        Block::m_Blocks.insert(std::make_pair(1, Block{m_BlockAtlas, m_BlockAtlasTexSize, {2, 2, 0, 1, 2, 2}}));
        // Dirt
        Block::m_Blocks.insert(std::make_pair(2, Block{m_BlockAtlas, m_BlockAtlasTexSize, 1}));
        // Stone
        Block::m_Blocks.insert(std::make_pair(3, Block{m_BlockAtlas, m_BlockAtlasTexSize, 3}));
        // Bedrock
        Block::m_Blocks.insert(std::make_pair(4, Block{m_BlockAtlas, m_BlockAtlasTexSize, 4}));
        // Log
        Block::m_Blocks.insert(std::make_pair(5, Block{m_BlockAtlas, m_BlockAtlasTexSize, {6, 6, 5, 5, 6, 6}}));
    }

    bool GameApp::onUpdate() {
        DoInput(m_DeltaTime);
        glClearColor(0.7, 0.7, 0.7, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_MainPlayer.Update(&m_MainMap);

        glm::mat4 projection = m_MainPlayer.m_PlayerCam.GetProjectionMatrix(m_AppWindow.m_Width, m_AppWindow.m_Height);
        glm::mat4 view = m_MainPlayer.m_PlayerCam.GetViewMatrix();
        m_MainMap.Draw(m_MainCube, view, projection, m_MainPlayer.m_PlayerCam.m_Position, 8);

        if (m_MainPlayer.m_RayHit) {
            m_MainCube.Bind();
            m_MainCube.SetMat4("view", view);
            m_MainCube.SetMat4("projection", projection);

            glm::mat4 model = glm::mat4{1.0};
            int x = m_MainPlayer.m_LookRayHitLoc.x;
            int y = m_MainPlayer.m_LookRayHitLoc.y;
            int z = m_MainPlayer.m_LookRayHitLoc.z;
            model = glm::translate(model, glm::vec3{x, y, z});
            model = glm::scale(model, glm::vec3{1.1});
            m_MainCube.SetMat4("model", model);

            m_MainCube.SetFloat("FogDistance", 6);

            m_IndicatorMesh.Draw(m_MainCube);
        }

        return true;
    }

    void GameApp::onKeyPressed(int Key, int Scancode, int Action, int Mods) {
        if (Key == GLFW_KEY_R && Action == GLFW_PRESS)
            m_MainCube.Reload();
        if (Key == GLFW_KEY_ESCAPE && Action == GLFW_PRESS)
            m_AppWindow.CaptureMouse(!m_AppWindow.IsMouseCaptured());

        if (Key == GLFW_KEY_LEFT_SHIFT) {
            if (Action == GLFW_PRESS)
                m_MainPlayer.m_PlayerCam.SetSpeed(25);
            else if (Action == GLFW_RELEASE)
                m_MainPlayer.m_PlayerCam.SetSpeed(5);
        }
    }

    void GameApp::onMouseButtonPressed(int Button, int Action, int Mods) {
        if (Button == GLFW_MOUSE_BUTTON_LEFT && Action == GLFW_PRESS) {
            if (m_MainPlayer.m_RayHit) {
                m_MainMap.SetBlockID(0,
                               m_MainPlayer.m_LookRayHitLoc.x,
                               m_MainPlayer.m_LookRayHitLoc.y,
                               m_MainPlayer.m_LookRayHitLoc.z);
            }
        }

        if (Button == GLFW_MOUSE_BUTTON_RIGHT && Action == GLFW_PRESS) {
            if (m_MainPlayer.m_RayHit) {
		auto PlaceLoc = m_MainPlayer.m_LookRayHitLoc + m_MainPlayer.m_LookRaySide;
                m_MainMap.SetBlockID(5,
                               PlaceLoc.x,
                               PlaceLoc.y,
                               PlaceLoc.z);
            }
        }
    }

    void GameApp::DoKeyboardInput(double DeltaTime) {
        if (m_AppWindow.GetKeyState(GLFW_KEY_W) == glcore::Window::KeyState::KEY_PRESS)
            m_MainPlayer.HandleKeyboard(engine::Camera::MovDir::FORWARD, DeltaTime);
        if (m_AppWindow.GetKeyState(GLFW_KEY_S) == glcore::Window::KeyState::KEY_PRESS)
            m_MainPlayer.HandleKeyboard(engine::Camera::MovDir::BACKWARD, DeltaTime);
        if (m_AppWindow.GetKeyState(GLFW_KEY_A) == glcore::Window::KeyState::KEY_PRESS)
            m_MainPlayer.HandleKeyboard(engine::Camera::MovDir::LEFT, DeltaTime);
        if (m_AppWindow.GetKeyState(GLFW_KEY_D) == glcore::Window::KeyState::KEY_PRESS)
            m_MainPlayer.HandleKeyboard(engine::Camera::MovDir::RIGHT, DeltaTime);
    }

    void GameApp::DoMouseInput() {
        // Get the relative mouse movement from the ~RelativeMouse~
        // DeltaVariable.
        auto [x, y] = m_RelativeMouse.GetDelta(m_AppWindow.GetCursorPos());

        m_MainPlayer.m_PlayerCam.ProcessMouseMovement(x, -y, true);
    }
}// namespace VoxelGame
