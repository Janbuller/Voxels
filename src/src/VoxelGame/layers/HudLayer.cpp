#include "VoxelGame/layers/HudLayer.h"
namespace VoxelGame::layers {
    void HudLayer::onCreate(){

    };
    void HudLayer::onUpdate(float DeltaTime){

    };
    void HudLayer::onDraw(){
	glDisable(GL_DEPTH_TEST);
    };
    void HudLayer::onExit(){

    };

    void HudLayer::onKeyPressed(int Key, int Scancode, int Action, int Mods){

    };
    void HudLayer::onMouseButtonPressed(int Button, int Action, int Mods){

    };

    void HudLayer::DoMouseMovement(double DeltaTime, glm::vec2 AbsLoc, glm::vec2 RelMov){

    };
    void HudLayer::DoKeyboardInput(double DeltaTime, std::function<glcore::Window::KeyState(int)> GetKeyState){

    };
}// namespace VoxelGame::layers
