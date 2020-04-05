#include "RenderCommand.h"

namespace Firefly {
namespace Rendering {
std::unique_ptr<RenderBackend> RenderCommand::s_backend =
    Factory::RenderBackend::CreateUnique();
} // namespace Rendering
} // namespace Firefly