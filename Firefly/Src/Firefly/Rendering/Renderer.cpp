#include "Renderer.h"

namespace Firefly {
namespace Rendering {
void Renderer::BeginScene() {
}

void Renderer::EndScene() {
}

void Renderer::Submit(const VertexArray& VAO) {
    RenderCommand::Draw(VAO);
}

} // namespace Rendering
} // namespace Firefly