#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Core/Window.h"

namespace Firefly {
namespace Rendering {
class RenderModule {
  public:
    void Load(Window window) {
        m_is_loaded = true;

        FFLY_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress),
                    "Failed to initialize glad");

        glViewport(0, 0, window.Data().Width, window.Data().Height);
        glClearColor(m_clear_color[0], m_clear_color[1], m_clear_color[2],
                     m_clear_color[3]);
    }

    void OnUpdate() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

  private:
    bool  m_is_loaded      = false;
    float m_clear_color[4] = {0.3f, 0.1f, 0.2f, 1.f};
};
} // namespace Rendering
} // namespace Firefly