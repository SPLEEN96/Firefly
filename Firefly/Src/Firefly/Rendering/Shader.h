#pragma once
#include "FFLY_CORE.h"

#include <glm/glm.hpp>

namespace Firefly {
namespace Rendering {
class Shader {
  public:
    Shader() {}
    ~Shader();

    void Bind();
    void Unbind();

    void SetVector1i(const char* name, const float& x);
    void SetVector1f(const char* name, const float& x);
    void SetVector2f(const char* name, const float& x, const float& y);
    void SetVector3f(const char* name, const float& x, const float& y, const float& z);
    void SetVector4f(const char* name, const float& x, const float& y, const float& z,
                     const float& w);
    void SetMatrix4f(const char* name, float* mat);

    void SetAPIHandle(const uint32& program_handle) {
        if (!initialized) {
            m_handle    = program_handle;
            initialized = true;
        }
    }

  private:
    uint32 m_handle    = 0;
    bool   initialized = false;
};
} // namespace Rendering

/* === FACTORY === */
namespace Factory {
namespace Shader {
Rendering::Shader* Create(const char* file_path);
} // namespace Shader
} // namespace Factory
} // namespace Firefly
