#pragma once
#include "RENDER_CORE.h"
#include "RenderBackend.h"

#include "Firefly/Window.h"

namespace Firefly {
namespace Rendering {
class RenderModule {
  public:
    void Load(Window window) {
        RenderBackend backend = RenderBackend::GetInstance();
        backend.Init(window);
    }
};
} // namespace Rendering
} // namespace Firefly