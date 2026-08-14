#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum class CameraMovement {
    Forward,
    Backward,
    Left,
    Right,
    Up,
    Down
};

class Camera {
    public:
        Camera();

        glm::mat4 getViewMatrix() const;
        glm::mat4 getProjectionMatrix(float aspectRatio) const;
        
        void processKeyboard(CameraMovement direction, float deltaTime);
        void processMouse(float xOffset, float yOffset);

    private:
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;

        float yaw; // left/right rotation
        float pitch; // up/down rotation
        float movementSpeed;
};