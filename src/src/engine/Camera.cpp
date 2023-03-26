#include "engine/Camera.h"

glm::mat4 engine::Camera::GetProjectionMatrix(int Width, int Height) {
  return glm::perspective(glm::radians(m_Zoom), (float) Width / (float) Height, 0.1f, 5000.0f);
}

glm::mat4 engine::Camera::GetViewMatrix() {
  return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

void engine::Camera::ProcessKeyboard(MovDir Direction, float DeltaTime) {
  float velocity = m_MovementSpeed * DeltaTime;
  if (Direction == Camera::MovDir::FORWARD)
    m_Position += m_Front * velocity;
  if (Direction == Camera::MovDir::BACKWARD)
    m_Position -= m_Front * velocity;
  if (Direction == Camera::MovDir::LEFT)
    m_Position -= m_Right * velocity;
  if (Direction == Camera::MovDir::RIGHT)
    m_Position += m_Right * velocity;

  UpdateCameraVectors();
}

void engine::Camera::ProcessMouseMovement(float OffsetX, float OffsetY, bool LimitPitch = true) {
  OffsetX *= m_MouseSensitivity;
  OffsetY *= m_MouseSensitivity;

  m_Yaw += OffsetX;
  m_Pitch += OffsetY;

  if (LimitPitch) {
    if (m_Pitch > 89.0f)
      m_Pitch = 89.0f;
    if (m_Pitch < -89.0f)
      m_Pitch = -89.0f;
  }

  UpdateCameraVectors();
}

void engine::Camera::UpdateCameraVectors() {
  glm::vec3 front;
  front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
  front.y = sin(glm::radians(m_Pitch));
  front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
  m_Front = glm::normalize(front);

  m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
  m_Up = glm::normalize((glm::cross(m_Right, m_Front)));
}

void engine::Camera::SetSpeed(float Speed) {
  m_MovementSpeed = Speed;
}
