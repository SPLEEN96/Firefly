#pragma once
#include "Core/Window.h"
#include "Rendering/RenderBackend.h"
#include "RenderCommand.h"

namespace Firefly {
namespace Rendering {
class RenderModule {
  public:
    enum API { NONE = 0, OPENGL };

  public:
    void Load(Window window);
    void OnUpdate();

  private:
    bool  m_is_loaded      = false;
    float m_clear_color[4] = {0.15f, 0.12f, 0.14f, 1.f};
};
} // namespace Rendering
} // namespace Firefly