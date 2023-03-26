#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>

namespace engine {
    class Camera {
    private:
        // Default values
        const float YAW = -90.0f;
        const float PITCH = 0.0f;
        const float SPEED = 5.0f;
        const float SENSITIVITY = 0.05f;
        const float ZOOM = 60.0f;

    public:
        enum class MovDir { FORWARD,
                            BACKWARD,
                            LEFT,
                            RIGHT };

        glm::vec3 m_Position;
        glm::vec3 m_Front;
        glm::vec3 m_Up;
        glm::vec3 m_Right;
        glm::vec3 m_WorldUp;

        float m_Yaw = YAW;
        float m_Pitch = PITCH;

        float m_MovementSpeed;
        float m_MouseSensitivity;
        float m_Zoom;

        Camera(glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f),
               glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f))
            : m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(SPEED),
              m_MouseSensitivity(SENSITIVITY), m_Zoom(ZOOM) {

            m_Position = Position;
            m_WorldUp = Up;
            UpdateCameraVectors();
        }
        Camera(float PosX, float PosY, float PosZ, float UpX, float UpY, float UpZ)
            : m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(SPEED),
              m_MouseSensitivity(SENSITIVITY), m_Zoom(ZOOM) {

            m_Position = glm::vec3(PosX, PosY, PosZ);
            m_WorldUp = glm::vec3(UpX, UpY, UpZ);
            UpdateCameraVectors();
        }

      glm::mat4 GetProjectionMatrix(int Width, int Height);
        glm::mat4 GetViewMatrix();

        void ProcessKeyboard(MovDir Direction, float DeltaTime);

        void ProcessMouseMovement(float OffsetX, float OffseteY, bool LimitPitch);

        void SetSpeed(float Speed);

    private:
        void UpdateCameraVectors();
    };
}// namespace engine
