#pragma once

#include "VoxelGame/Chunk.h"
#include "engine/Application.h"
#include "engine/Camera.h"
#include "engine/DeltaVariable.h"
#include "engine/Mesh.h"
#include "glcore/Shader.h"
#include <array>

namespace VoxelGame {
    class GameApp : public engine::Application {

        using engine::Application::Application;

    private:
        engine::Mesh cubeMesh = engine::Mesh::LoadOBJ("cube.obj", "res/");
        engine::Camera mainCam{{0.0f, 2.0f, 1.0f}};
        glcore::Shader mainCube{"res/shaders/mainCube.vert", "res/shaders/mainCube.frag"};

	engine::DeltaVariable<double, 2> RelativeMouse{std::array<double, 2>{0, 0}};

	Chunk chunk{};

    private:
        void onCreate() override;
        bool onUpdate(double deltaTime) override;

	void DoInput(double deltaTime) {
	  DoKeyboardInput(deltaTime);
	  DoMouseInput();
	}

    void DoKeyboardInput(double deltaTime);
	void DoMouseInput();
    };
}// namespace VoxelGame
