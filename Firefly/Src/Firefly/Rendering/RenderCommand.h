#pragma once
#include "RenderBackend.h"

namespace Firefly {
namespace Rendering {
class RenderCommand {
  public:
    static void InitAPI() { s_backend->InitAPI(); }

    static void SetViewport(uint32 x, uint32 y, uint32 width, uint32 height) {
        s_backend->SetViewport(x, y, width, height);
    }

    static void SetClearColor(float r, float g, float b, float a) {
        s_backend->SetClearColor(r, g, b, a);
    }

    static void ClearBuffers(bool color_buffer = true, bool depth_buffer = false,
                             bool stencil_buffer = false) {
        s_backend->ClearBuffers(color_buffer, depth_buffer, stencil_buffer);
    }

    static void Draw(const VertexArray& VAO, uint vertice_count = 3) {
        s_backend->Draw(VAO, vertice_count);
    }

    static void DrawIndexed(const VertexArray& VAO) { s_backend->DrawIndexed(VAO); }

  private:
    static std::unique_ptr<RenderBackend> s_backend;
};
} // namespace Rendering
} // namespace Firefly