#include "Renderer.h"

namespace Firefly {
namespace Rendering {
void Renderer::BeginScene() {
}

void Renderer::EndScene() {
}

void Renderer::Submit(const VertexArray& VAO,uint vertice_count) {
    RenderCommand::Draw(VAO,vertice_count);
}

} // namespace Rendering
} // namespace Firefly