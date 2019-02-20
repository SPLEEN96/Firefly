#pragma once
#include "RenderBackend.h"

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