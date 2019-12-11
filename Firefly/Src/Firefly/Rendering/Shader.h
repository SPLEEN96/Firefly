#pragma once
#include "FFLY_CORE.h"

namespace Firefly {
namespace Rendering {
class Shader {
  public:
    Shader() {}
    ~Shader();

    void Bind();
    void Unbind();

    void SetUniform1i(const char* name, float x);
    void SetUniform3fv(const char* name, float x, float y, float z);

    void SetAPIHandle(uint32 program_handle) {
        if (!initialized) {
            m_handle    = program_handle;
            initialized = true;
        }
    }

  private:
    uint32 m_handle;
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
