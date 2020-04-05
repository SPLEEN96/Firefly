#pragma once
#include "FFLY_CORE.h"
#include "VertexArray.h"

namespace Firefly {
namespace Rendering {
class RenderBackend {
  public:
    enum API { none = 0, OPENGL };

    RenderBackend();
    ~RenderBackend();

    void InitAPI();

    void SetViewport(uint32 x, uint32 y, uint32 width, uint32 height);
    void SetClearColor(float r, float g, float b, float a);
    void ClearBuffers(bool color_buffer = true, bool depth_buffer = false,
                      bool stencil_buffer = false);

    void DrawIndexed(const VertexArray& VAO);
    void Draw(const VertexArray& VAO, uint vertice_count = 3);

    static API GetAPI() { return s_API; }

  private:
    static API s_API;
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