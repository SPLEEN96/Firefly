#include "Rendering/RenderModule.h"
#include "PCH_CORE.h"

namespace Firefly {
namespace Rendering {
RenderModule::API RenderModule::m_API = RenderModule::API::OPENGL;

void RenderModule::Load(Window window) {
    m_is_loaded = true;

    switch (m_API) {
    case RenderModule::API::NONE:
        FFLY_LOG_CORE_CRITICAL("RenderModule::API::NONE is not a valid API");

    case RenderModule::API::OPENGL:
        m_backend = std::make_unique<RenderBackend>();
    }

    m_backend->InitAPI();
    m_backend->SetViewport(0, 0, window.Data().Width, window.Data().Height);
    m_backend->SetClearColor(m_clear_color[0], m_clear_color[1], m_clear_color[2],
                             m_clear_color[3]);
}

void RenderModule::OnUpdate() {
    m_backend->ClearBuffers(true, true);

    // Iterate through m_commands
}

} // namespace Rendering
}; // namespace Firefly