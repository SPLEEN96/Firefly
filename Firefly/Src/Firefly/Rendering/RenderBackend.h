#pragma once
#include "FFLY_CORE.h"

namespace Firefly {
namespace Rendering {
class RenderBackend {
  public:
    RenderBackend();
    ~RenderBackend();

    static RenderBackend* Create();

    void InitAPI();

    void SetViewport(uint32 x, uint32 y, uint32 width, uint32 height);
    void SetClearColor(float r, float g, float b, float a);
    void ClearBuffers(bool color_buffer = true, bool depth_buffer = false,
                      bool stencil_buffer = false);

    void DrawIndexed();

  private:
};
} // namespace Rendering
} // namespace Firefly