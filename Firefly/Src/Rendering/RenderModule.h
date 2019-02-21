#pragma once
#include "RenderBackend.h"

namespace Firefly {
namespace Rendering {
class RenderModule {
  public:
    void Load(Window window) {
        if (!is_loaded) {
            backend.Init(window);
            is_loaded = true;
        }
    }

  private:
    RenderBackend backend;
    bool          is_loaded = false;
};
} // namespace Rendering
} // namespace Firefly