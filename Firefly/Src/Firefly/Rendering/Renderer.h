#pragma once

#include "RenderBackend.h"
#include "RenderCommand.h"
#include "VertexArray.h"

namespace Firefly {
namespace Rendering {
class Renderer {
  public:
    static void BeginScene();
    static void EndScene();

    static void Submit(const VertexArray& VAO, uint vertice_count = 3);

    static RenderBackend::API GetAPI() { return RenderBackend::GetAPI(); };

  private:
};
} // namespace Rendering
} // namespace Firefly