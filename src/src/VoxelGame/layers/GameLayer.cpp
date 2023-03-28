#include "VoxelGame/layers/GameLayer.h"
#include "GLFW/glfw3.h"
#include "VoxelGame/Block.h"
#include "glcore/Window.h"
#include <algorithm>

namespace VoxelGame::layers {
    void GameLayer::onCreate() {
        auto &BlockAtlas        = m_Context->m_BlockAtlas;
        auto &BlockAtlasTexSize = m_Context->m_BlockAtlasTexSize;
        // Grass
        Block::m_Blocks.insert(std::make_pair(1, Block{BlockAtlas, BlockAtlasTexSize, {2, 2, 0, 1, 2, 2}}));
        // Dirt
        Block::m_Blocks.insert(std::make_pair(2, Block{BlockAtlas, BlockAtlasTexSize, 1}));
        // Stone
        Block::m_Blocks.insert(std::make_pair(3, Block{BlockAtlas, BlockAtlasTexSize, 3}));
        // Bedrock
        Block::m_Blocks.insert(std::make_pair(4, Block{BlockAtlas, BlockAtlasTexSize, 4}));
        // Log
        Block::m_Blocks.insert(std::make_pair(5, Block{BlockAtlas, BlockAtlasTexSize, {6, 6, 5, 5, 6, 6}}));
        // Plank
        Block::m_Blocks.insert(std::make_pair(6, Block{BlockAtlas, BlockAtlasTexSize, 7}));
    }
    void GameLayer::onUpdate(float DeltaTime) {
        auto &MainPlayer = m_Context->m_MainPlayer;
        MainPlayer.Update(&m_Context->m_MainMap);
    }
    void GameLayer::onDraw() {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        glFrontFace(GL_CW);

        glClearColor(0.7, 0.7, 0.7, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto &MainPlayer = m_Context->m_MainPlayer;

        glm::mat4 projection = MainPlayer.m_PlayerCam.GetProjectionMatrix(m_Width, m_Height);
        glm::mat4 view       = MainPlayer.m_PlayerCam.GetViewMatrix();
        m_Context->m_MainMap.Draw(m_MainCube, view, projection, MainPlayer.m_PlayerCam.m_Position, 8);

        if (MainPlayer.m_RayHit) {
            m_MainCube.Bind();
            m_MainCube.SetMat4("view", view);
            m_MainCube.SetMat4("projection", projection);

            glm::mat4 model = glm::mat4{1.0};
            int x           = MainPlayer.m_LookRayHitLoc.x;
            int y           = MainPlayer.m_LookRayHitLoc.y;
            int z           = MainPlayer.m_LookRayHitLoc.z;
            model           = glm::translate(model, glm::vec3{x, y, z});
            model           = glm::scale(model, glm::vec3{1.1});
            m_MainCube.SetMat4("model", model);

            m_MainCube.SetFloat("FogDistance", 6);

            m_IndicatorMesh.Draw(m_MainCube);
        }
    }
    void GameLayer::onExit() {
    }

    void GameLayer::onKeyPressed(int Key, int Scancode, int Action, int Mods) {
        auto &MainPlayer = m_Context->m_MainPlayer;

        if (Key == GLFW_KEY_R && Action == GLFW_PRESS)
            m_MainCube.Reload();

        if (Key == GLFW_KEY_LEFT_SHIFT) {
            if (Action == GLFW_PRESS)
                MainPlayer.m_PlayerCam.SetSpeed(25);
            else if (Action == GLFW_RELEASE)
                MainPlayer.m_PlayerCam.SetSpeed(5);
        }
    }
    void GameLayer::onMouseButtonPressed(int Button, int Action, int Mods) {
        auto &MainPlayer = m_Context->m_MainPlayer;
        if (Button == GLFW_MOUSE_BUTTON_LEFT && Action == GLFW_PRESS) {
            if (MainPlayer.m_RayHit) {
                m_Context->m_MainMap.SetBlockID(0,
                                                MainPlayer.m_LookRayHitLoc.x,
                                                MainPlayer.m_LookRayHitLoc.y,
                                                MainPlayer.m_LookRayHitLoc.z);
            }
        }

        if (Button == GLFW_MOUSE_BUTTON_RIGHT && Action == GLFW_PRESS) {
            if (MainPlayer.m_RayHit) {
                auto PlaceLoc = MainPlayer.m_LookRayHitLoc + MainPlayer.m_LookRaySide;
                m_Context->m_MainMap.SetBlockID(6,
                                                PlaceLoc.x,
                                                PlaceLoc.y,
                                                PlaceLoc.z);
            }
        }
    }

    void GameLayer::DoMouseMovement(double DeltaTime, glm::vec2 AbsLoc, glm::vec2 RelMov) {
        auto &MainPlayer = m_Context->m_MainPlayer;
        MainPlayer.m_PlayerCam.ProcessMouseMovement(RelMov.x, -RelMov.y, true);
    }

    void GameLayer::DoKeyboardInput(double DeltaTime, std::function<glcore::Window::KeyState(int)> GetKeyState) {
	using KeyState = glcore::Window::KeyState;
	using MovDir = engine::Camera::MovDir;

        auto &MainPlayer = m_Context->m_MainPlayer;

        if (GetKeyState(GLFW_KEY_W) == KeyState::KEY_PRESS)
            MainPlayer.HandleKeyboard(MovDir::FORWARD, DeltaTime);
        if (GetKeyState(GLFW_KEY_S) == KeyState::KEY_PRESS)
            MainPlayer.HandleKeyboard(MovDir::BACKWARD, DeltaTime);
        if (GetKeyState(GLFW_KEY_A) == KeyState::KEY_PRESS)
            MainPlayer.HandleKeyboard(MovDir::LEFT, DeltaTime);
        if (GetKeyState(GLFW_KEY_D) == KeyState::KEY_PRESS)
            MainPlayer.HandleKeyboard(MovDir::RIGHT, DeltaTime);
    }
}// namespace VoxelGame::layers
