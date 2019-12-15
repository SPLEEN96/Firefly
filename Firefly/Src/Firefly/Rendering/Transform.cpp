#include "Rendering/Transform.h"

namespace Firefly {
namespace Rendering {

Transform::~Transform() {
}

void Transform::Translate(float axes[3]) {
    glm::vec3 glm_axes = glm::make_vec3(axes);
    m_translate        = glm::mat4(1.f);
    m_translate        = glm::translate(m_translate, glm_axes);

    m_position += glm_axes;
}

void Transform::Scale(float axes[3]) {
    glm::vec3 glm_axes = glm::make_vec3(axes);

    m_scale = glm::mat4(1.f);
    m_scale = glm::scale(m_scale, glm_axes);
}

void Transform::Rotate(const float& angle, float axes[3]) {
    glm::vec3 glm_axes = glm::make_vec3(axes);

    m_rotate = glm::mat4(1.f);
    m_rotate = glm::rotate(m_rotate, glm::radians(angle), glm_axes);

    m_angle += angle;
}

void Transform::SetPosition(float new_position[3]) {
    m_position = glm::make_vec3(new_position);
}

float Transform::GetDistanceFrom(float target[3]) {
    float distance = 0.f;
    distance       = sqrt(target[0] * target[0] + target[1] * target[1]);
    return distance;
}

glm::mat4 Transform::GetTransformMatrix() {
    this->Translate(glm::value_ptr(m_position));
    glm::mat4 transform(m_translate * m_scale * m_rotate);
    return transform;
}

} // namespace Rendering

namespace Factory {
namespace Transform {
Rendering::Transform* Create() {
}
} // namespace Transform
} // namespace Factory

} // namespace Firefly