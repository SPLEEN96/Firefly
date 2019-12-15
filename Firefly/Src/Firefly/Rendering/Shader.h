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

    void SetUniform1i(const char* name, const float& x);
    void SetUniform3fv(const char* name, const float& x, const float& y, const float& z);

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
