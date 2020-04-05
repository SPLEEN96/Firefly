#include "Rendering/RenderModule.h"
#include "PCH_CORE.h"

namespace Firefly {
namespace Rendering {
void RenderModule::Load(Window window) {
    m_is_loaded = true;

    RenderCommand::InitAPI();
    RenderCommand::SetViewport(0, 0, window.Data().Width, window.Data().Height);
    RenderCommand::SetClearColor(m_clear_color[0], m_clear_color[1], m_clear_color[2],
                                 m_clear_color[3]);
}

void RenderModule::OnUpdate() {
    RenderCommand::ClearBuffers(true, true);

    // Iterate through m_commands
}

} // namespace Rendering
}; // namespace Firefly