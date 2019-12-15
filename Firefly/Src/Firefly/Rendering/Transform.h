#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Firefly {
namespace Rendering {
class Transform {
  public:
    Transform() {}
    ~Transform();

    void Translate(float axes[3]);
    void Scale(float axes[3]);
    void Rotate(const float& angle, float axes[3]);

    void  SetPosition(float new_position[3]);
    float GetDistanceFrom(float target_coord[3]);

    glm::mat4 GetTransformMatrix();

    glm::vec3 GetPosition() { return m_position; }
    glm::vec3 GetScale() {
        return glm::vec3(m_scale[0][0], m_scale[1][1], m_scale[2][2]);
    }
    float GetAngle() { return m_angle; }

  private:
    glm::vec3 m_position = glm::vec3(0.f);
    float     m_angle    = 0.f;

    glm::mat4 m_translate = glm::mat4(1.f);
    glm::mat4 m_scale     = glm::mat4(1.f);
    glm::mat4 m_rotate    = glm::mat4(1.f);
};
} // namespace Rendering

namespace Factory {
namespace Transform {
Rendering::Transform* Create();
} // namespace Transform
} // namespace Factory

} // namespace Firefly