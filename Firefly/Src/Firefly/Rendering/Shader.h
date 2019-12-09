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

    void SetUniform3fv(const char* name, float x, float y, float z);

    void SetProgram(uint32 program_handle) {
        if (!initialized) {
            m_handle = program_handle;
        }
        initialized = true;
    }

  private:
    uint32 m_handle;
    bool   initialized = false;
};
} // namespace Rendering

namespace Shader {
Firefly::Rendering::Shader* Create(const char* file_path);
} // namespace Shader
} // namespace Firefly
