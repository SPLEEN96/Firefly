#pragma once
#include "RenderBackend.h"

namespace Firefly {
namespace Rendering {
class RenderModule {
  public:
    void Load(Window window) { RenderBackend::GetInstance().Init(window); }
};
} // namespace Rendering
} // namespace Firefly