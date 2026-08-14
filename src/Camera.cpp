#include "Camera.hpp"
#include <GLFW/glfw3.h>

Camera::Camera() {
    // starting position is at (0, 0, 3) 
    // front with -1 at z so camera is facing particles
    position = glm::vec3(0.0f, 0.0f, 3.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);

    movementSpeed = 2.5f;

    // Why -90? becuase the camera will start looking down the negative Z axis.
    yaw = -90.0f;
    pitch = 0.0f;
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProjectionMatrix(float aspectRatio) const {
    return glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime) {
    float speed = movementSpeed * deltaTime;
    glm::vec3 right = glm::normalize(glm::cross(front, up));


    switch(direction) {
        case CameraMovement::Forward:
            position += front * speed;
            break;
        
        case CameraMovement::Backward:
            position -= front * speed;
            break;
        
        case CameraMovement::Left:
            position -= right * speed;
            break;
        
        case CameraMovement::Right:
            position += right * speed;
            break;
        
        case CameraMovement::Up:
            position += up * speed;
            break;

        case CameraMovement::Down:
            position -= up * speed;
            break;
    }
}

void Camera::processMouse(float xOffset, float yOffset) {
    const float sensitivity = 0.1f;

    xOffset *= sensitivity;
    yOffset *= sensitivity;

    yaw += xOffset;
    pitch += yOffset;

    // make it so that the camera can't flip upside down
    if (pitch > 89.0f)
        pitch = 89.0f;

    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;

    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            
    direction.y = sin(glm::radians(pitch));

    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(direction);
}