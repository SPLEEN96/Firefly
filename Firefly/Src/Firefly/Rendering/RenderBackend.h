#pragma once
#include "FFLY_CORE.h"

namespace Firefly {
namespace Rendering {
class RenderBackend {
  public:
    RenderBackend();
    ~RenderBackend();

    void InitAPI();

    void SetViewport(uint32 x, uint32 y, uint32 width, uint32 height);
    void SetClearColor(float r, float g, float b, float a);
    void ClearBuffers(bool color_buffer = true, bool depth_buffer = false,
                      bool stencil_buffer = false);

    void DrawIndexed();

  private:
};
} // namespace Rendering

/* === FACTORY === */
namespace Factory {
namespace RenderBackend {
Rendering::RenderBackend*                 Create();
std::unique_ptr<Rendering::RenderBackend> CreateUnique();
} // namespace RenderBackend
} // namespace Factory
} // namespace Firefly